"""Memory map workbench, core side: severity of findings, the findings that belong to
no output section, and the severity counts of the checklist."""
import pytest

from autosar_configurator.core.hardware.memory_regions import LOCAL, MemoryRegionDef
from autosar_configurator.core.memmap import check
from autosar_configurator.core.memmap.check import Finding

ERROR_CATEGORIES = (check.UNMAPPED, check.SYMBOL, check.FLASH, check.USAGE)
WARNING_CATEGORIES = (check.UNPLACED, check.MULTIPLE, check.CORE, check.CACHE, check.DUPLICATE)
INFO_CATEGORIES = (check.WILDCARD,)


def _finding(category, possible=False):
    return Finding(category, "a.c", 1, "x", possible=possible)


# --- severity --------------------------------------------------------------------

@pytest.mark.parametrize("category", ERROR_CATEGORIES)
def test_error_categories(category):
    assert _finding(category).severity == check.ERROR


@pytest.mark.parametrize("category", WARNING_CATEGORIES)
def test_warning_categories(category):
    assert _finding(category).severity == check.WARNING


@pytest.mark.parametrize("category", INFO_CATEGORIES)
def test_info_categories(category):
    assert _finding(category).severity == check.INFO


def test_every_category_has_a_severity():
    assert set(check.SEVERITY) == set(check.CATEGORIES)
    assert set(ERROR_CATEGORIES + WARNING_CATEGORIES + INFO_CATEGORIES) == set(check.CATEGORIES)


def test_possible_findings_are_one_level_lower():
    assert _finding(check.UNMAPPED, possible=True).severity == check.WARNING
    assert _finding(check.CORE, possible=True).severity == check.INFO
    assert _finding(check.WILDCARD, possible=True).severity == check.INFO      # info stays info


def test_severity_is_not_a_stored_field():
    """It follows from the category and the flag: no third place that could disagree."""
    finding = _finding(check.UNMAPPED)
    assert "severity" not in finding.__dataclass_fields__
    assert finding.sort_key() == (check.CATEGORIES.index(check.UNMAPPED), "a.c", 1, "x")


def test_severity_rank_orders_errors_first():
    ranks = [check.SEVERITY_RANK[s] for s in (check.ERROR, check.WARNING, check.INFO)]
    assert ranks == sorted(ranks) and len(set(ranks)) == 3


# --- findings without an output section ---------------------------------------------

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
#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Can_MemMap.h"
#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Can_MemMap.h"
STARTUP_GETIMAGEBASEADDR(NOT_IN_THE_LINKER_FILE, x);
"""
SCAT = """\
#define GMU_NORMAL 0x10000000
LR GMU_NORMAL 0x1000
{
    UNDEFINE_RAM_BSS GMU_NORMAL 0x1000 { *(+BSS) }
}
"""
REGIONS = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True),
           MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", LOCAL, False)]


def _result(tmp_path):
    src = tmp_path / "src"
    src.mkdir()
    (src / "Can.c").write_text(SOURCE, encoding="utf-8")
    headers = tmp_path / "Memmap"
    headers.mkdir()
    (headers / "Can_MemMap.h").write_text(MEMMAP, encoding="utf-8")
    linker = tmp_path / "scatter.scat"
    linker.write_text(SCAT, encoding="utf-8")
    return check.run_check([src], [headers], linker, REGIONS, base=tmp_path)


def test_findings_without_a_section_are_the_four_categories(tmp_path):
    result = _result(tmp_path)
    loose = result.findings_without_section()
    assert {f.category for f in loose} == {check.UNMAPPED, check.SYMBOL}
    assert {f.category for f in loose} <= set(check.NO_SECTION_CATEGORIES)
    assert set(check.NO_SECTION_CATEGORIES) == {check.UNMAPPED, check.USAGE, check.DUPLICATE, check.SYMBOL}


def test_section_findings_are_not_counted_as_loose(tmp_path):
    result = _result(tmp_path)
    attached = [f for row in result.rows for f in row.findings]
    assert attached, "the core 0 section lands in GMU_NORMAL: there should be section findings"
    loose = result.findings_without_section()
    assert not any(f is a for f in loose for a in attached)
    assert len(loose) + len(attached) == len(result.findings)


def test_every_finding_is_either_attached_or_loose(tmp_path):
    """Nothing falls between the two: this is what the layout tab's summary relies on."""
    result = _result(tmp_path)
    attached = {id(f) for row in result.rows for f in row.findings}
    loose = {id(f) for f in result.findings_without_section()}
    assert attached | loose == {id(f) for f in result.findings}
    assert not attached & loose


def test_counts_per_severity(tmp_path):
    result = _result(tmp_path)
    counts = result.severity_counts()
    assert set(counts) == {check.ERROR, check.WARNING, check.INFO}
    assert sum(counts.values()) == len(result.findings)
    loose = result.severity_counts(result.findings_without_section())
    assert loose[check.ERROR] == len(result.findings_without_section())      # unmapped and symbol: errors


def test_counts_of_a_subset_and_of_nothing():
    result = check.CheckResult()
    assert result.severity_counts() == {check.ERROR: 0, check.WARNING: 0, check.INFO: 0}
    subset = [_finding(check.UNMAPPED), _finding(check.UNMAPPED, possible=True), _finding(check.WILDCARD)]
    assert result.severity_counts(subset) == {check.ERROR: 1, check.WARNING: 1, check.INFO: 1}


# --- checklist ---------------------------------------------------------------------

def test_checklist_header_lists_the_severity_counts(tmp_path):
    result = _result(tmp_path)
    text = check.to_markdown(result)
    counts = result.severity_counts()
    assert (f"- 发现：错误 {counts[check.ERROR]}，警告 {counts[check.WARNING]}，"
            f"提示 {counts[check.INFO]}") in text


def test_checklist_items_are_unchanged_by_severity(tmp_path):
    result = _result(tmp_path)
    text = check.to_markdown(result)
    assert text.index("## 用到但没有映射的段") < text.index("## 链接符号缺失")      # category order
    assert "- [ ] `src/Can.c:5` CAN_START_SEC_CONFIG_DATA_UNSPECIFIED 在 Can_MemMap.h 中没有映射" in text
    assert "错误" not in text.split("## ", 1)[1]          # no severity inside the items or the group titles


def test_checklist_counts_follow_the_findings_it_is_given(tmp_path):
    result = _result(tmp_path)
    only_symbol = [f for f in result.findings if f.category == check.SYMBOL]
    text = check.to_markdown(result, findings=only_symbol)
    assert f"- 发现：错误 {len(only_symbol)}，警告 0，提示 0" in text
