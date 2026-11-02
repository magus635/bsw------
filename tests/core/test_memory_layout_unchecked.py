"""Memory layout without a linker file: nothing was placed because nothing was checked, which
is not the same as a section no region receives."""
from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import check, layout

MEMMAP = """\
#if 0
#elif defined CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
    MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_core0")
#endif
"""
SOURCE = """\
#define CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Can_MemMap.h"
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Can_MemMap.h"
"""
SCAT = """\
#define GMU_NORMAL 0x10000000
LR GMU_NORMAL 0x1000
{
    EX_CODE GMU_NORMAL 0x1000 { *(+RO-CODE) }
}
"""
REGIONS = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True)]


def _workspace(tmp_path, scat=None):
    src = tmp_path / "src"
    src.mkdir()
    (src / "Can.c").write_text(SOURCE, encoding="utf-8")
    headers = tmp_path / "Memmap"
    headers.mkdir()
    (headers / "Can_MemMap.h").write_text(MEMMAP, encoding="utf-8")
    linker = None
    if scat is not None:
        linker = tmp_path / "scatter.scat"
        linker.write_text(scat, encoding="utf-8")
    return src, headers, linker


def _check(tmp_path, scat=None, regions=None, unconfirmed=False):
    src, headers, linker = _workspace(tmp_path, scat)
    return check.run_check([src], [headers], linker, regions, unconfirmed, base=tmp_path)


def _row(result):
    return result.rows[0]


# --- the wording --------------------------------------------------------------------

def test_without_a_linker_file_the_row_says_nothing_was_checked(tmp_path):
    result = _check(tmp_path)
    assert result.placement_checked is False
    assert layout.placement_text(_row(result), result) == "未检查放置（没有链接文件）"


def test_with_a_non_ads_linker_file_the_row_says_so(tmp_path):
    src, headers, _ = _workspace(tmp_path)
    ld = tmp_path / "Linker.ld"
    ld.write_text("SECTIONS {}", encoding="utf-8")
    result = check.run_check([src], [headers], ld, base=tmp_path)
    assert result.placement_checked is False
    assert layout.placement_text(_row(result), result) == "未检查放置（链接文件不是 ADS 格式）"


def test_with_a_linker_file_an_unreceived_section_is_still_reported(tmp_path):
    result = _check(tmp_path, scat=SCAT)
    assert result.placement_checked is True
    assert _row(result).placement is None
    assert layout.placement_text(_row(result), result) == "没有区域接收"


def test_text_is_unchanged_when_no_result_is_given(tmp_path):
    """The one-argument form of the older callers keeps its meaning."""
    result = _check(tmp_path, scat=SCAT)
    assert layout.placement_text(_row(result)) == "没有区域接收"


# --- the grouping ------------------------------------------------------------------------

def test_without_a_linker_file_the_sections_are_not_filed_under_no_receiving_region(tmp_path):
    result = _check(tmp_path)
    groups = layout.by_region(result)
    assert [g.name for g in groups] == [layout.NOT_CHECKED_GROUP]
    assert layout.UNPLACED_GROUP not in [g.name for g in groups]
    assert [r.output for g in groups for e in g.executions for r in e.rows] == [
        ".mcal_bss_asil_d_unspecified_core0"]


def test_with_a_linker_file_the_group_is_still_no_receiving_region(tmp_path):
    groups = layout.by_region(_check(tmp_path, scat=SCAT))
    assert groups[-1].name == layout.UNPLACED_GROUP


def test_the_not_checked_group_comes_after_the_placed_ones(tmp_path):
    scat = SCAT.replace("*(+RO-CODE)", "*(.mcal_bss_asil_d_unspecified_core0)")
    result = _check(tmp_path, scat=scat, regions=REGIONS)
    assert [g.name for g in layout.by_region(result)] == ["GMU_NORMAL"]


def test_markdown_says_not_checked(tmp_path):
    text = layout.to_markdown(_check(tmp_path))
    assert f"## {layout.NOT_CHECKED_GROUP}（1）" in text
    assert "未检查放置（没有链接文件）" in text
    assert "没有区域接收" not in text


# --- the notes about the chip regions ------------------------------------------------------

def test_chip_region_notes_show_without_a_linker_file(tmp_path):
    assert check.NO_REGIONS_NOTE in _check(tmp_path).notes


def test_unconfirmed_regions_note_shows_without_a_linker_file(tmp_path):
    result = _check(tmp_path, regions=REGIONS, unconfirmed=True)
    assert any("待确认" in n for n in result.notes)


def test_chip_region_notes_are_not_repeated_with_a_linker_file(tmp_path):
    result = _check(tmp_path, scat=SCAT)
    assert result.notes.count(check.NO_REGIONS_NOTE) == 1
    result = _check(tmp_path / "b", scat=SCAT, regions=REGIONS, unconfirmed=True) \
        if (tmp_path / "b").mkdir() is None else None
    assert sum("待确认" in n for n in result.notes) == 1


def test_confirmed_regions_add_no_note(tmp_path):
    result = _check(tmp_path, regions=REGIONS, unconfirmed=False)
    assert check.NO_REGIONS_NOTE not in result.notes and not any("待确认" in n for n in result.notes)
