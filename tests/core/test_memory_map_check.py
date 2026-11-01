"""Memory map check: section usage, MemMap header mapping, ADS scatter placement,
chip memory regions, project settings, checklist and read-only behaviour."""
import hashlib
import json

import pytest

from autosar_configurator.core.hardware.chip_dependency_scan import ScanCancelled
from autosar_configurator.core.hardware.memory_regions import (
    LOCAL,
    MemoryRegionDef,
    memory_region_dict,
    parse_memory_regions,
    region_at,
)
from autosar_configurator.core.memmap import check
from autosar_configurator.core.memmap.headers import parse_header
from autosar_configurator.core.memmap.scatter import parse_scatter, placements
from autosar_configurator.core.memmap.usage import exclusive, scan_source

CAN_C = """\
#include "Can.h"
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"
void Can_Init(void) {}
#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Can_MemMap.h"
static int Can_Status_Core0;
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED
#include "Can_MemMap.h"
static int Can_DmaBuffer;
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED
#include "Can_MemMap.h"
"""


def _branch(name, kind, output):
    return f"""
#elif defined {name}
    #undef {name}
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    MEMMAP_START_{kind}("{output}")
"""


CAN_MEMMAP_H = ("/* MEMMAP_START_BSS(\".commented_out\") */\n#define MEMMAP_ERROR\n#if 0\n"
                + _branch("CAN_START_SEC_CODE_ASIL_D_GLOBAL", "TEXT", ".mcal_text_asil_d")
                + _branch("CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED", "BSS",
                          ".mcal_bss_asil_d_unspecified_core0")
                + _branch("CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED", "BSS",
                          ".mcal_bss_asil_d_unspecified_uncached")
                + "\n#endif\n")

T1_SCAT = """\
#! armclang --target=arm-arm-none-eabi -march=armv8-a -E -x c
#define PFLASH0                    0x8000000
#define CPU0BTCM                    0x30100000
#define GMU_NORMAL                    0x10000000
#define GMU_UNCACHED                    0x82020400
;        GMU_NORMAL              0x10000000   comment { not a region }
FLASH_IMAGE PFLASH0 0x300000
{
    CORE0_USER_STACK CPU0BTCM ALIGN 8 EMPTY 0x1000 {}

    EX_CODE AlignExpr(PFLASH0+ImageLength(CORE0_USER_STACK), 64) ALIGN 64 0x34000
    {
        *(.user_code,+First)
        *(+RO-CODE)
    }

    PRIVATE_DATA_CORE0 CPU0BTCM ALIGN 64 0x8000
    {
        *(.os_data_qm_32_core0)
    }

    UNDEFINE_RAM_DATA GMU_NORMAL ALIGN 64 0x10000
    {
        *(+RW-DATA)
    }

    UNDEFINE_RAM_BSS AlignExpr(ImageLimit(UNDEFINE_RAM_DATA), 64) ALIGN 64 0x10000
    {
        *(+BSS)
        *(.os_bss)
    }

    GLOBAL_UNCACHED_BSS GMU_UNCACHED ALIGN 64 0x10000
    {
        *(.uncached_bss)
    }
}
"""

REGIONS = [
    MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", LOCAL, False),
    MemoryRegionDef("CPUXPFLASH0", 0x08000000, 0x300000, "flash", None, True),
    MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True),
    MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
    MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False),
]


def _workspace(tmp_path, scat=T1_SCAT, can_c=CAN_C):
    src = tmp_path / "Mcal" / "Can" / "src"
    src.mkdir(parents=True)
    (src / "Can.c").write_text(can_c, encoding="utf-8")
    headers = tmp_path / "CommonFile" / "Memmap"
    headers.mkdir(parents=True)
    (headers / "Can_MemMap.h").write_text(CAN_MEMMAP_H, encoding="utf-8")
    linker = tmp_path / "scatter.scat"
    linker.write_text(scat, encoding="utf-8")
    return tmp_path / "Mcal", headers, linker


# --- usage -----------------------------------------------------------------------

def test_usage_pairs_and_header():
    uses, problems = scan_source(CAN_C, "Can.c")
    assert problems == []
    assert [(u.name, u.line, u.header, u.conditional) for u in uses][:2] == [
        ("CAN_START_SEC_CODE_ASIL_D_GLOBAL", 2, "Can_MemMap.h", False),
        ("CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED", 9, "Can_MemMap.h", False)]


def test_usage_missing_stop_and_include():
    text = """\
#ifndef CAN_H
#define CAN_H
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
#include "Can_MemMap.h"
#define CAN_START_SEC_CONST_ASIL_D_GLOBAL_32
int x;
#define CAN_STOP_SEC_CONST_ASIL_D_GLOBAL_32
#include "Can_MemMap.h"
#define CAN_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32
#include "Can_MemMap.h"
#endif
"""
    uses, problems = scan_source(text, "Can.h")
    assert [u.conditional for u in uses] == [False, False]      # include guard is not a branch
    assert [(p.line, p.text) for p in problems] == [
        (5, "CAN_START_SEC_CONST_ASIL_D_GLOBAL_32 之后没有 #include MemMap 头文件"),
        (3, "CAN_START_SEC_CODE_ASIL_D_GLOBAL 没有对应的 STOP，第 5 行又开始了 CAN_START_SEC_CONST_ASIL_D_GLOBAL_32"),
        (9, "CAN_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32 前面没有对应的 START")]


def test_usage_core_chosen_by_elif_chain():
    """Fee.c chooses the core section in an #if/#elif chain and includes after #endif."""
    text = """\
#if (0U == FEE_CORE_ALLOCATION)
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE0_8
#elif (1U == FEE_CORE_ALLOCATION)
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE1_8
#endif
#include "Fee_MemMap.h"
static int buffer;
#if (0U == FEE_CORE_ALLOCATION)
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_8
#elif (1U == FEE_CORE_ALLOCATION)
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_8
#endif
#include "Fee_MemMap.h"
"""
    uses, problems = scan_source(text, "Fee.c")
    assert problems == []
    assert [(u.header, u.conditional) for u in uses] == [("Fee_MemMap.h", True)] * 2


def test_exclusive_branches():
    assert exclusive(((1, 0),), ((1, 1),))
    assert not exclusive(((1, 0),), ((2, 0),))
    assert not exclusive((), ((1, 0),))


def test_usage_start_and_stop_at_different_levels():
    text = """\
#define X_START_SEC_CODE
#include "X_MemMap.h"
#if A
#define X_STOP_SEC_CODE
#include "X_MemMap.h"
#endif
"""
    _, problems = scan_source(text, "x.c")
    assert [p.text for p in problems] == ["X_START_SEC_CODE 与第 4 行的 STOP 不在同一 #if 层级"]


# --- headers ---------------------------------------------------------------------

def test_header_mapping_and_repeats():
    text = CAN_MEMMAP_H.replace("\n#endif\n", _branch("CAN_START_SEC_CODE_ASIL_D_GLOBAL", "TEXT", ".again")
                                + "\n#endif\n")
    mappings, repeated = parse_header(text, "Can_MemMap.h")
    assert [(m.name, m.kind, m.output) for m in mappings] == [
        ("CAN_START_SEC_CODE_ASIL_D_GLOBAL", "TEXT", ".mcal_text_asil_d"),
        ("CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED", "BSS", ".mcal_bss_asil_d_unspecified_core0"),
        ("CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED", "BSS",
         ".mcal_bss_asil_d_unspecified_uncached")]
    assert [m.line for m in mappings] == [5, 14, 23]
    assert [(m.output, m.line) for m in repeated] == [(".again", 32)]


def test_header_os_style_if_defined():
    text = """\
#if defined OS_START_SEC_CODE_QM_GLOBAL
    #undef OS_START_SEC_CODE_QM_GLOBAL
    MEMMAP_START_TEXT(".os_text_qm")
#elif defined OS_STOP_SEC_CODE_QM_GLOBAL
    MEMMAP_STOP_TEXT()
#elif defined(OS_START_SEC_VAR_INIT_QM_CORE0_32)
    MEMMAP_START_DATA(".os_data_qm_32_core0")
#endif
"""
    mappings, _ = parse_header(text, "Os_memmap.h")
    assert [(m.name, m.output) for m in mappings] == [
        ("OS_START_SEC_CODE_QM_GLOBAL", ".os_text_qm"),
        ("OS_START_SEC_VAR_INIT_QM_CORE0_32", ".os_data_qm_32_core0")]


# --- scatter ---------------------------------------------------------------------

def test_scatter_regions_and_addresses():
    scatter = parse_scatter(T1_SCAT, "scatter.scat")
    assert [r.name for r in scatter.regions] == [
        "CORE0_USER_STACK", "EX_CODE", "PRIVATE_DATA_CORE0", "UNDEFINE_RAM_DATA",
        "UNDEFINE_RAM_BSS", "GLOBAL_UNCACHED_BSS"]
    bss = scatter.region("UNDEFINE_RAM_BSS")
    assert (bss.follows, bss.address, bss.line) == ("UNDEFINE_RAM_DATA", 0x10000000, 27)
    assert scatter.region("EX_CODE").address == 0x8000000
    assert scatter.region("GLOBAL_UNCACHED_BSS").address == 0x82020400
    assert [s.text() for s in bss.selectors] == ["*(+BSS)", "*(.os_bss)"]
    assert bss.selectors[0].line == 29


def test_placement_explicit_wildcard_and_none():
    scatter = parse_scatter(T1_SCAT, "scatter.scat")
    explicit = placements(scatter, ".os_data_qm_32_core0", "DATA")
    assert [(p.region.name, p.explicit) for p in explicit] == [("PRIVATE_DATA_CORE0", True)]
    caught = placements(scatter, ".mcal_bss_asil_d_unspecified_core0", "BSS")
    assert [(p.region.name, p.selector.text(), p.explicit) for p in caught] == [
        ("UNDEFINE_RAM_BSS", "*(+BSS)", False)]
    assert placements(scatter, ".mcal_const_asil_d", "RODATA") == []


def test_placement_vendor_forms_and_any():
    text = """\
LR 0x0 {
  ER_A 0x100 { *(+CODE, .mcal_text_asil_d) }
  ER_B +0 {
    *  ( +RO-DATA , .mcal_const_*  )
  }
  ER_C 0x30100000 { .ANY(+RW +ZI) }
  ER_D 0x0 { startup.o(+ZI) }
}
"""
    scatter = parse_scatter(text, "v.scat")
    assert scatter.region("ER_B").follows == "ER_A" and scatter.region("ER_B").address == 0x100
    assert placements(scatter, ".mcal_text_asil_d", "TEXT")[0].explicit
    assert placements(scatter, ".mcal_const_asil_d_32", "RODATA")[0].region.name == "ER_B"
    # a file-specific attribute selector catches nothing in general; .ANY does
    caught = placements(scatter, ".mcal_bss_x", "BSS")
    assert [(p.region.name, p.explicit) for p in caught] == [("ER_C", False)]


# --- memory regions ----------------------------------------------------------------

def test_memory_regions_round_trip():
    data = [memory_region_dict(r) for r in REGIONS]
    assert data[3] == {"name": "CPU0BTCM", "start": "0x30100000", "size": "0x30000",
                       "type": "ram", "core": 0, "cacheable": False}
    assert data[0]["core"] == "local" and "core" not in data[2]
    assert parse_memory_regions(data) == REGIONS
    assert parse_memory_regions(None) == []
    assert region_at(REGIONS, 0x82020400).name == "GMU_DEVICE"
    assert region_at(REGIONS, 0x50000000) is None


@pytest.mark.parametrize("entry, message", [
    ({"start": 0, "size": 1}, "with a name"),
    ({"name": "A", "start": 0, "size": 1, "type": "rom"}, "type must be"),
    ({"name": "A", "start": "zz", "size": 1}, "start must be a number"),
    ({"name": "A", "start": 0, "size": 0}, "size must be positive"),
    ({"name": "A", "start": 0, "size": 1, "cacheable": "yes"}, "cacheable must be"),
])
def test_memory_regions_invalid(entry, message):
    with pytest.raises(ValueError, match=message):
        parse_memory_regions([entry])


def test_chip_yaml_keeps_regions(tmp_path):
    from autosar_configurator.core.hardware.chip_database import (
        ChipDatabase,
        ChipDefinition,
    )
    from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter

    chip = ChipDefinition(name="DEMO", memory_regions=REGIONS,
                          metadata={"unconfirmed": {"memory_regions": "按注释表填写"}})
    path = tmp_path / "DEMO.yaml"
    ChipDefinitionExporter().save_yaml(chip, path)
    loaded = ChipDatabase()._load_chip_from_yaml(path)
    assert loaded.memory_regions == REGIONS and not loaded.content_modified
    assert loaded.metadata["unconfirmed"] == {"memory_regions": "按注释表填写"}

    ChipDefinitionExporter().save_yaml(ChipDefinition(name="OLD"), tmp_path / "OLD.yaml")
    assert "memory_regions" not in (tmp_path / "OLD.yaml").read_text(encoding="utf-8")
    assert ChipDatabase()._load_chip_from_yaml(tmp_path / "OLD.yaml").memory_regions == []


def test_library_chips_unchanged_and_tha6206_regions():
    from autosar_configurator.core.hardware.chip_completeness import unconfirmed_marks
    from autosar_configurator.core.hardware.chip_database import (
        get_default_chip_database,
    )

    db = get_default_chip_database()
    for name in db.list_chips():
        assert not db.get_chip(name).content_modified, name
    chip = db.get_chip("THA6206_LFBGA292")
    assert region_at(chip.memory_regions, 0x30100000).core == 0
    assert region_at(chip.memory_regions, 0x10000000).cacheable
    assert not region_at(chip.memory_regions, 0x82020400).cacheable
    assert "memory_regions" in unconfirmed_marks(chip)


# --- check -------------------------------------------------------------------------

def test_check_t1_like_project(tmp_path):
    sources, headers, linker = _workspace(tmp_path)
    result = check.run_check([sources], [headers], linker, REGIONS, True, base=tmp_path)
    found = [(f.category, f.text) for f in result.findings]
    assert found == [
        (check.CORE, ("核心 0 的 .mcal_bss_asil_d_unspecified_core0 放在 UNDEFINE_RAM_BSS，"
                      "位于 GMU_NORMAL（共享）")),
        (check.CACHE, ("不可缓存的 .mcal_bss_asil_d_unspecified_uncached 放在 UNDEFINE_RAM_BSS，"
                       "位于可缓存的 GMU_NORMAL")),
        (check.WILDCARD, ".mcal_text_asil_d 未显式放置，由 EX_CODE 的 *(+RO-CODE) 接收"),
        (check.WILDCARD, ".mcal_bss_asil_d_unspecified_core0 未显式放置，由 UNDEFINE_RAM_BSS 的 *(+BSS) 接收"),
        (check.WILDCARD, ".mcal_bss_asil_d_unspecified_uncached 未显式放置，由 UNDEFINE_RAM_BSS 的 *(+BSS) 接收")]
    wildcard = result.by_category(check.WILDCARD)[1]
    assert (wildcard.path, wildcard.line) == ("scatter.scat", 29)
    assert wildcard.note == ("CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED；"
                             "使用于 Mcal/Can/src/Can.c:9")
    assert result.notes == ["芯片的内存区域数据标记为待确认，核心、缓存和 flash 类型检查的结论需人工核对"]
    assert (result.files_scanned, result.headers_read, result.sections_used) == (2, 1, 3)


def test_check_unmapped_and_missing_header(tmp_path):
    can_c = CAN_C + """
#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Can_MemMap.h"
#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Can_MemMap.h"
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "Dem_MemMap.h"
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "Dem_MemMap.h"
"""
    sources, headers, linker = _workspace(tmp_path, can_c=can_c)
    result = check.run_check([sources], [headers], linker, base=tmp_path)
    unmapped = [(f.line, f.text) for f in result.by_category(check.UNMAPPED)]
    assert unmapped == [(21, "CAN_START_SEC_CONFIG_DATA_UNSPECIFIED 在 Can_MemMap.h 中没有映射"),
                        (25, "找不到 Dem_MemMap.h（已添加的目录中没有）")]
    assert check.NO_REGIONS_NOTE in result.notes
    assert not result.by_category(check.CORE)


def test_check_explicit_placement_has_no_findings(tmp_path):
    scat = T1_SCAT.replace("*(.os_data_qm_32_core0)", "*(.os_data_qm_32_core0)\n"
                           "        *(.mcal_bss_asil_d_unspecified_core0)") \
                  .replace("*(.uncached_bss)", "*(.uncached_bss)\n        *(.mcal_bss_asil_d_unspecified_uncached)") \
                  .replace("*(.user_code,+First)", "*(.user_code,+First)\n        *(.mcal_text_*)")
    sources, headers, linker = _workspace(tmp_path, scat=scat)
    result = check.run_check([sources], [headers], linker, REGIONS, base=tmp_path)
    assert result.findings == []


def test_check_template_skipped_and_unsupported_linker(tmp_path):
    sources, headers, _ = _workspace(tmp_path)
    (sources / "Can" / "src" / "Can_PBcfg.c").write_text(
        '#define CAN_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED\n', encoding="utf-8")
    ld = tmp_path / "Linker.ld"
    ld.write_text("SECTIONS {}", encoding="utf-8")
    result = check.run_check([sources], [headers], ld, base=tmp_path)
    assert result.templates_skipped == 1
    assert result.notes[0] == "目前只支持 ADS 分散加载文件（.scat、.sct），Linker.ld 的放置检查已跳过"
    assert not result.by_category(check.WILDCARD)


def test_check_is_read_only_and_cancellable(tmp_path):
    sources, headers, linker = _workspace(tmp_path)
    files = sorted(p for p in tmp_path.rglob("*") if p.is_file())
    before = {p: hashlib.sha256(p.read_bytes()).hexdigest() for p in files}
    check.run_check([sources], [headers], linker, REGIONS, base=tmp_path)
    assert sorted(p for p in tmp_path.rglob("*") if p.is_file()) == files
    assert {p: hashlib.sha256(p.read_bytes()).hexdigest() for p in files} == before
    with pytest.raises(ScanCancelled):
        check.run_check([sources], [headers], linker, progress=lambda i, n, p: False)


def test_checklist_markdown(tmp_path):
    sources, headers, linker = _workspace(tmp_path)
    result = check.run_check([sources], [headers], linker, REGIONS, base=tmp_path)
    text = check.to_markdown(result)
    assert "- 链接文件：scatter.scat" in text
    assert "## 未显式放置的段（3）" in text
    assert ("- [ ] `scatter.scat:29` .mcal_bss_asil_d_unspecified_core0 未显式放置，由 UNDEFINE_RAM_BSS "
            "的 *(+BSS) 接收 — CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED；使用于 Mcal/Can/src/Can.c:9"
            in text)
    assert text.index("## 核心数据不在本核心内存") < text.index("## 未显式放置的段")


def test_check_project_settings(tmp_path):
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    _workspace(tmp_path)
    gen = tmp_path / "proj" / "generateCode" / "Can" / "src"
    gen.mkdir(parents=True)
    (gen / "Can_Lcfg.c").write_text("#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED\n"
                                    "#include \"Can_MemMap.h\"\n"
                                    "#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED\n"
                                    "#include \"Can_MemMap.h\"\n", encoding="utf-8")
    manager = WorkspaceManager()
    project = manager.create_project("demo", tmp_path / "proj" / "demo.dpa")
    assert (project.memmap_source_dirs, project.memmap_header_dirs, project.memmap_linker_file) == (
        [], [], None)
    project.memmap_source_dirs = ["../Mcal"]
    project.memmap_header_dirs = ["../CommonFile/Memmap"]
    project.memmap_linker_file = "../scatter.scat"
    manager.save_project()

    reopened, _ = WorkspaceManager().load_project(tmp_path / "proj" / "demo.dpa")
    assert reopened.memmap_source_dirs == ["../Mcal"]
    assert reopened.memmap_header_dirs == ["../CommonFile/Memmap"]
    assert reopened.memmap_linker_file == "../scatter.scat"
    result = check.check_project(reopened)
    assert result.source_dirs == ["../Mcal", "generateCode"]
    assert [f.path for f in result.by_category(check.UNMAPPED)] == ["generateCode/Can/src/Can_Lcfg.c"]

    data = json.loads((tmp_path / "proj" / "demo.dpa").read_text(encoding="utf-8"))
    for key in ("memmap_source_dirs", "memmap_header_dirs", "memmap_linker_file"):
        del data[key]
    (tmp_path / "proj" / "demo.dpa").write_text(json.dumps(data), encoding="utf-8")
    older, _ = WorkspaceManager().load_project(tmp_path / "proj" / "demo.dpa")
    assert (older.memmap_source_dirs, older.memmap_header_dirs, older.memmap_linker_file) == (
        [], [], None)


def test_section_attributes_from_names():
    assert check.section_core("CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED") == 0
    assert check.section_core("X", ".os_bss_qm_32_core1") == 1
    assert check.section_core("CAN_START_SEC_CODE_ASIL_D_GLOBAL", ".mcal_text_asil_d") is None
    assert check.is_non_cacheable("X_START_SEC_VAR_CLEARED_GLOBAL_NO_CACHEABLE_32")
    assert check.is_non_cacheable("X", ".os_bss_qm_32_uncached")
    assert not check.is_non_cacheable("X_START_SEC_VAR_CLEARED_GLOBAL_32", ".mcal_bss")
