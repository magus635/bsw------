"""The layout groups the sections by physical memory when the chip says which windows belong
together, and shows the chip as before when it does not."""
from autosar_configurator.core.hardware.memory_regions import LOCAL, MemoryRegionDef
from autosar_configurator.core.memmap import check, layout

MEMMAP = """\
#if 0
#elif defined CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
    MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified")
#elif defined CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED
    MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_uncached")
#endif
"""
SOURCE = """\
#define CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
#define CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED
#include "Can_MemMap.h"
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_NO_CACHEABLE_UNSPECIFIED
#include "Can_MemMap.h"
"""
SCAT = """\
#define GMU_NORMAL 0x10000000
#define GMU_DEVICE 0x82000000
LR GMU_NORMAL 0x1000
{
    UNDEFINE_RAM_BSS GMU_NORMAL 0x1000 { *(+BSS) }
    GLOBAL_UNCACHED_BSS GMU_DEVICE 0x1000 { *(.mcal_bss_asil_d_unspecified_uncached) }
}
"""
PLAIN = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True),
         MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False)]
GROUPED = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True, "GMU", "normal"),
           MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False, "GMU", "device")]


def _check(tmp_path, regions):
    src = tmp_path / "src"
    src.mkdir()
    (src / "Can.c").write_text(SOURCE, encoding="utf-8")
    headers = tmp_path / "Memmap"
    headers.mkdir()
    (headers / "Can_MemMap.h").write_text(MEMMAP, encoding="utf-8")
    linker = tmp_path / "scatter.scat"
    linker.write_text(SCAT, encoding="utf-8")
    return check.run_check([src], [headers], linker, regions, base=tmp_path)


def test_windows_of_one_memory_share_one_top_group(tmp_path):
    groups = layout.by_region(_check(tmp_path, GROUPED))
    assert [g.name for g in groups] == ["GMU"]
    assert groups[0].row_count == 2


def test_the_execution_regions_show_which_window_they_lie_in(tmp_path):
    groups = layout.by_region(_check(tmp_path, GROUPED))
    by_name = {e.name: e.window for e in groups[0].executions}
    assert by_name == {"UNDEFINE_RAM_BSS": "GMU_NORMAL", "GLOBAL_UNCACHED_BSS": "GMU_DEVICE"}


def test_the_group_lists_its_windows_with_their_cacheability(tmp_path):
    group = layout.by_region(_check(tmp_path, GROUPED))[0]
    assert group.attributes == "共享，ram；窗口：GMU_NORMAL 可缓存，GMU_DEVICE 不可缓存"


def test_a_chip_without_grouping_is_shown_as_before(tmp_path):
    groups = layout.by_region(_check(tmp_path, PLAIN))
    assert [g.name for g in groups] == ["GMU_NORMAL", "GMU_DEVICE"]
    assert groups[0].attributes == "共享，可缓存，ram"
    assert all(e.window == "" for g in groups for e in g.executions)


def test_the_group_sits_where_its_first_window_is(tmp_path):
    other = [MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False)]
    groups = layout.by_region(_check(tmp_path, other + GROUPED))
    assert [g.name for g in groups][:1] == ["GMU"]            # 0x10000000 comes before 0x30100000


def test_findings_are_unchanged_by_the_grouping(tmp_path):
    grouped = _check(tmp_path / "a", GROUPED) if (tmp_path / "a").mkdir() is None else None
    plain = _check(tmp_path / "b", PLAIN) if (tmp_path / "b").mkdir() is None else None
    assert [(f.category, f.text) for f in grouped.findings] == [(f.category, f.text) for f in plain.findings]


def test_the_markdown_names_the_window(tmp_path):
    text = layout.to_markdown(_check(tmp_path, GROUPED))
    assert "## GMU（共享，ram；窗口：GMU_NORMAL 可缓存，GMU_DEVICE 不可缓存）（2）" in text
    assert "### UNDEFINE_RAM_BSS @ 0x10000000（窗口 GMU_NORMAL）" in text


def test_a_memory_with_a_local_alias_and_an_axi_window(tmp_path):
    atcm = [MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", LOCAL, False, "ATCM", "local"),
            MemoryRegionDef("CPU0ATCM", 0x30000000, 0x10000, "ram", 0, False, "ATCM", "axi")]
    result = _check(tmp_path, atcm + GROUPED)
    from autosar_configurator.core.hardware.memory_regions import group_memories
    assert [(g.name, [w.name for w in g.windows]) for g in group_memories(result.regions)][0] == (
        "ATCM", ["CPUXATCM", "CPU0ATCM"])
