"""Memory layout view data: rows, the two groupings, filters, the two extra checks,
Markdown export and the read-only guarantee."""
import hashlib

from autosar_configurator.core.hardware.memory_regions import LOCAL, MemoryRegionDef
from autosar_configurator.core.memmap import check, layout
from autosar_configurator.core.memmap.layout import LayoutFilter

CAN_MEMMAP = """\
#if 0
#elif defined CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
    MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_core0")
#elif defined CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED
    MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_uncached")
#elif defined CAN_START_SEC_CODE_ASIL_D_GLOBAL
    MEMMAP_START_TEXT(".mcal_text_asil_d")
#elif defined CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
    MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified")
#endif
"""
# Spi maps its core 0 section to the same output section as Can
SPI_MEMMAP = """\
#if 0
#elif defined SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
    MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_core0")
#endif
"""
SOURCE = """\
#define {m}_START_SEC_{s}
#include "{m}_MemMap.h"
#define {m}_STOP_SEC_{s}
#include "{m}_MemMap.h"
"""
CAN_C = (SOURCE.format(m="CAN", s="VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED")
         + SOURCE.format(m="CAN", s="VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED")
         + SOURCE.format(m="CAN", s="CODE_ASIL_D_GLOBAL")
         + SOURCE.format(m="CAN", s="VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED"))
SPI_C = SOURCE.format(m="SPI", s="VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED")

REGIONS = [
    MemoryRegionDef("CPUXPFLASH0", 0x08000000, 0x300000, "flash", None, True),
    MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True),
    MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
    MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False),
]

SCAT = """\
#define PFLASH0 0x8000000
#define GMU_NORMAL 0x10000000
#define CPU0BTCM 0x30100000
#define GMU_DEVICE 0x82000000
LR PFLASH0 0x300000
{
    EX_CODE PFLASH0 0x1000
    {
        *(+RO-CODE)
    }
    PRIVATE_BSS_CORE0 CPU0BTCM 0x8000
    {
        *(.mcal_bss_asil_d_unspecified_core0)
    }
    UNDEFINE_RAM_BSS GMU_NORMAL 0x10000
    {
        *(+BSS)
    }
    GLOBAL_UNCACHED_BSS GMU_DEVICE 0x10000
    {
        *(.mcal_bss_asil_d_unspecified_uncached)
    }
}
"""


def _workspace(tmp_path, scat=SCAT, spi=True):
    src = tmp_path / "Mcal"
    src.mkdir()
    (src / "Can.c").write_text(CAN_C, encoding="utf-8")
    if spi:
        (src / "Spi.c").write_text(SPI_C, encoding="utf-8")
    headers = tmp_path / "Memmap"
    headers.mkdir()
    (headers / "Can_MemMap.h").write_text(CAN_MEMMAP, encoding="utf-8")
    if spi:
        (headers / "Spi_MemMap.h").write_text(SPI_MEMMAP, encoding="utf-8")
    linker = tmp_path / "scatter.scat"
    linker.write_text(scat, encoding="utf-8")
    return src, headers, linker


def _check(tmp_path, regions=REGIONS, **kwargs):
    src, headers, linker = _workspace(tmp_path, **kwargs)
    return check.run_check([src], [headers], linker, regions, base=tmp_path)


def _row(result, output):
    return next(r for r in result.rows if r.output == output)


# --- rows ------------------------------------------------------------------------

def test_rows_hold_attributes_and_placement(tmp_path):
    result = _check(tmp_path)
    assert [r.output for r in result.rows] == [
        ".mcal_bss_asil_d_unspecified", ".mcal_bss_asil_d_unspecified_core0",
        ".mcal_bss_asil_d_unspecified_uncached", ".mcal_text_asil_d"]
    core0 = _row(result, ".mcal_bss_asil_d_unspecified_core0")
    assert (core0.kind, core0.core, core0.non_cacheable) == ("BSS", 0, False)
    place = core0.placement
    assert (place.region, place.chip_region, place.explicit, place.address) == (
        "PRIVATE_BSS_CORE0", "CPU0BTCM", True, 0x30100000)
    assert core0.findings == []
    uncached = _row(result, ".mcal_bss_asil_d_unspecified_uncached")
    assert uncached.non_cacheable and uncached.findings == []


def test_section_shared_by_modules_is_one_row(tmp_path):
    result = _check(tmp_path)
    shared = _row(result, ".mcal_bss_asil_d_unspecified_core0")
    assert shared.modules == ("CAN", "SPI")
    assert shared.names == ("CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED",
                            "SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED")
    assert len([r for r in result.rows if r.output == shared.output]) == 1
    assert len(shared.uses) == 2


def test_wildcard_row_names_region_chip_region_and_selector(tmp_path):
    result = _check(tmp_path)
    row = _row(result, ".mcal_bss_asil_d_unspecified")
    place = row.placement
    assert (place.region, place.chip_region, place.explicit, place.selector) == (
        "UNDEFINE_RAM_BSS", "GMU_NORMAL", False, "*(+BSS)")
    assert [f.category for f in row.findings] == [check.WILDCARD]
    assert layout.placement_text(row) == "UNDEFINE_RAM_BSS（GMU_NORMAL，通配 *(+BSS)）"


def test_row_findings_are_the_check_findings(tmp_path):
    result = _check(tmp_path)
    from_rows = [f for row in result.rows for f in row.findings]
    assert sorted(from_rows, key=check.Finding.sort_key) == [
        f for f in result.findings if f.category in
        (check.WILDCARD, check.CORE, check.CACHE, check.FLASH, check.MULTIPLE, check.UNPLACED)]


def test_unplaced_row_has_no_placement(tmp_path):
    scat = SCAT.replace("*(+RO-CODE)", "*(.other)")
    result = _check(tmp_path, scat=scat)
    row = _row(result, ".mcal_text_asil_d")
    assert row.placement is None and layout.placement_text(row) == "没有区域接收"
    assert [f.category for f in row.findings] == [check.UNPLACED]


def test_region_base_cannot_be_resolved(tmp_path):
    scat = SCAT.replace("UNDEFINE_RAM_BSS GMU_NORMAL", "UNDEFINE_RAM_BSS NOWHERE")
    result = _check(tmp_path, scat=scat)
    row = _row(result, ".mcal_bss_asil_d_unspecified")
    assert row.placement.address is None and row.placement.chip_region is None
    assert any("UNDEFINE_RAM_BSS 的基址无法解析" in n for n in result.notes)
    groups = layout.by_region(result)
    assert groups[-1].name == layout.UNKNOWN_CHIP_REGION
    assert [e.name for e in groups[-1].executions] == ["UNDEFINE_RAM_BSS"]


# --- groupings -------------------------------------------------------------------

def test_by_region_orders_chip_regions_by_address(tmp_path):
    groups = layout.by_region(_check(tmp_path))
    assert [g.name for g in groups] == ["CPUXPFLASH0", "GMU_NORMAL", "CPU0BTCM", "GMU_DEVICE"]
    assert groups[2].attributes == "核心 0，不可缓存，ram"
    assert [(e.name, [r.output for r in e.rows]) for e in groups[2].executions] == [
        ("PRIVATE_BSS_CORE0", [".mcal_bss_asil_d_unspecified_core0"])]
    assert groups[0].executions[0].address == 0x8000000


def test_by_region_unplaced_sections_come_last(tmp_path):
    scat = SCAT.replace("*(+RO-CODE)", "*(.other)")
    groups = layout.by_region(_check(tmp_path, scat=scat))
    assert groups[-1].name == layout.UNPLACED_GROUP
    assert [r.output for r in groups[-1].executions[0].rows] == [".mcal_text_asil_d"]


def test_by_module_lists_shared_section_under_each_module(tmp_path):
    result = _check(tmp_path)
    groups = layout.by_module(result)
    assert [g.name for g in groups] == ["CAN", "SPI"]
    assert [r.output for r in groups[1].rows] == [".mcal_bss_asil_d_unspecified_core0"]
    assert len(groups[0].rows) == 4
    # the same rows as the other grouping, not a second copy of the data
    in_region = {id(r) for g in layout.by_region(result) for e in g.executions for r in e.rows}
    assert {id(r) for g in groups for r in g.rows} == in_region


def test_without_chip_regions_executions_are_listed_without_chip_regions(tmp_path):
    result = _check(tmp_path, regions=[])
    assert check.NO_REGIONS_NOTE in result.notes
    groups = layout.by_region(result)
    assert [g.name for g in groups] == [layout.UNKNOWN_CHIP_REGION]
    # execution regions by resolved base address: 0x8000000, 0x10000000, 0x30100000, 0x82000000
    assert [e.name for e in groups[0].executions] == [
        "EX_CODE", "UNDEFINE_RAM_BSS", "PRIVATE_BSS_CORE0", "GLOBAL_UNCACHED_BSS"]
    assert all(r.placement.chip_region is None for e in groups[0].executions for r in e.rows)


# --- filters ---------------------------------------------------------------------

def test_filters(tmp_path):
    result = _check(tmp_path)
    assert [r.output for r in layout.filter_rows(result, LayoutFilter(module="SPI"))] == [
        ".mcal_bss_asil_d_unspecified_core0"]
    assert [r.output for r in layout.filter_rows(result, LayoutFilter(core=0))] == [
        ".mcal_bss_asil_d_unspecified_core0"]
    assert {r.kind for r in layout.filter_rows(result, LayoutFilter(kind="TEXT"))} == {"TEXT"}
    only = layout.filter_rows(result, LayoutFilter(only_findings=True))
    assert only and all(r.findings for r in only)
    assert layout.modules_of(result) == ["CAN", "SPI"] and layout.cores_of(result) == [0]
    assert [g.name for g in layout.by_module(result, LayoutFilter(module="SPI"))] == ["SPI"]
    assert [g.name for g in layout.by_region(result, LayoutFilter(core=0))] == ["CPU0BTCM"]


# --- the two extra checks ----------------------------------------------------------

def test_duplicate_explicit_placement(tmp_path):
    scat = SCAT.replace("*(+BSS)", "*(+BSS)\n        *(.mcal_bss_asil_d_unspecified_core0)")
    result = _check(tmp_path, scat=scat)
    multiple = result.by_category(check.MULTIPLE)
    assert [f.text for f in multiple] == [
        ".mcal_bss_asil_d_unspecified_core0 被多个执行区域显式选中：PRIVATE_BSS_CORE0、UNDEFINE_RAM_BSS"]
    assert multiple[0] in _row(result, ".mcal_bss_asil_d_unspecified_core0").findings
    assert _row(result, ".mcal_bss_asil_d_unspecified_core0").placement.also == ("UNDEFINE_RAM_BSS",)
    assert "另被 UNDEFINE_RAM_BSS 选中" in layout.placement_text(
        _row(result, ".mcal_bss_asil_d_unspecified_core0"))


def test_duplicate_placement_needs_no_chip_data(tmp_path):
    scat = SCAT.replace("*(+BSS)", "*(+BSS)\n        *(.mcal_bss_asil_d_unspecified_core0)")
    result = _check(tmp_path, scat=scat, regions=[])
    assert len(result.by_category(check.MULTIPLE)) == 1


def test_data_in_flash_is_reported(tmp_path):
    scat = SCAT.replace("PRIVATE_BSS_CORE0 CPU0BTCM", "PRIVATE_BSS_CORE0 PFLASH0")
    result = _check(tmp_path, scat=scat)
    flash = result.by_category(check.FLASH)
    assert [f.text for f in flash] == [
        "BSS 段 .mcal_bss_asil_d_unspecified_core0 放在 PRIVATE_BSS_CORE0，位于 flash 区域 CPUXPFLASH0"]
    assert flash[0] in _row(result, ".mcal_bss_asil_d_unspecified_core0").findings


def test_code_placed_in_ram_reports_nothing(tmp_path):
    scat = SCAT.replace("*(+RO-CODE)", "*(.other)").replace(
        "GLOBAL_UNCACHED_BSS GMU_DEVICE 0x10000\n    {",
        "GLOBAL_UNCACHED_BSS GMU_DEVICE 0x10000\n    {\n        *(.mcal_text_asil_d)")
    result = _check(tmp_path, scat=scat)
    assert not result.by_category(check.FLASH)
    assert _row(result, ".mcal_text_asil_d").findings == []


def test_flash_check_skipped_without_chip_regions(tmp_path):
    scat = SCAT.replace("PRIVATE_BSS_CORE0 CPU0BTCM", "PRIVATE_BSS_CORE0 PFLASH0")
    result = _check(tmp_path, scat=scat, regions=[])
    assert not result.by_category(check.FLASH)
    assert check.NO_REGIONS_NOTE in result.notes


# --- export ----------------------------------------------------------------------

def test_markdown_by_region_and_filter(tmp_path):
    result = _check(tmp_path)
    text = layout.to_markdown(result)
    assert "- 链接文件：scatter.scat" in text
    assert "- 分组：按物理区域；过滤：无；输出段 4 / 4" in text
    assert text.index("## GMU_NORMAL") < text.index("## CPU0BTCM")
    assert "### PRIVATE_BSS_CORE0 @ 0x30100000" in text
    assert "| .mcal_bss_asil_d_unspecified_core0 | BSS，核心 0 | CAN、SPI | PRIVATE_BSS_CORE0（CPU0BTCM，显式） |  |" in text

    filtered = layout.to_markdown(result, layout.BY_MODULE, LayoutFilter(module="SPI"))
    assert "- 分组：按模块；过滤：模块 SPI；输出段 1 / 4" in filtered
    assert "## SPI（1）" in filtered and "## CAN" not in filtered
    assert ".mcal_text_asil_d" not in filtered


def test_markdown_filtered_to_core_with_findings(tmp_path):
    scat = SCAT.replace("PRIVATE_BSS_CORE0 CPU0BTCM", "PRIVATE_BSS_CORE0 GMU_NORMAL")
    result = _check(tmp_path, scat=scat)
    flt = LayoutFilter(core=0, only_findings=True)
    text = layout.to_markdown(result, flt=flt)
    assert "过滤：核心 0、只看有问题的" in text
    assert text.count("| .mcal_") == 1 and "放在 PRIVATE_BSS_CORE0，位于 GMU_NORMAL（共享）" in text


# --- read only -------------------------------------------------------------------

def test_view_data_is_read_only(tmp_path):
    src, headers, linker = _workspace(tmp_path)
    files = sorted(p for p in tmp_path.rglob("*") if p.is_file())
    before = {p: hashlib.sha256(p.read_bytes()).hexdigest() for p in files}
    result = check.run_check([src], [headers], linker, REGIONS, base=tmp_path)
    layout.by_region(result)
    layout.by_module(result)
    layout.to_markdown(result)
    assert sorted(p for p in tmp_path.rglob("*") if p.is_file()) == files
    assert {p: hashlib.sha256(p.read_bytes()).hexdigest() for p in files} == before
    assert LOCAL == "local"
