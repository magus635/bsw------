"""Memory regions grouped into physical memories: the optional memory/window/source
fields, the round trip of old and new entries, grouping and the two levels of checks."""
import copy

import pytest

from autosar_configurator.core.hardware import memory_regions as mr
from autosar_configurator.core.hardware.memory_regions import (
    LOCAL,
    MemoryRegionDef,
    group_memories,
    memory_region_dict,
    parse_memory_regions,
    region_problems,
    rename_memory,
)

OLD = [
    {"name": "CPU0ATCM", "start": "0x30000000", "size": "0x10000", "type": "ram", "core": 0, "cacheable": False},
    {"name": "GMU_NORMAL", "start": "0x10000000", "size": "0x40000", "type": "ram", "cacheable": True},
]
GROUPED = [
    {"name": "GMU_NORMAL", "start": "0x10000000", "size": "0x40000", "type": "ram", "cacheable": True,
     "memory": "GMU", "window": "normal", "source": "LinkerAdsPf.scat 注释表"},
    {"name": "GMU_DEVICE", "start": "0x82000000", "size": "0x40000", "type": "ram", "cacheable": False,
     "memory": "GMU", "window": "device"},
    {"name": "LMU1_NORMAL", "start": "0x10054000", "size": "0x4000", "type": "ram", "cacheable": True},
]


def _regions(entries):
    return parse_memory_regions(copy.deepcopy(entries))


# --- fields and the round trip ---------------------------------------------------------

def test_new_fields_are_read():
    gmu = _regions(GROUPED)[0]
    assert (gmu.memory, gmu.window, gmu.source) == ("GMU", "normal", "LinkerAdsPf.scat 注释表")


def test_an_entry_without_the_new_fields_is_a_memory_of_its_own():
    atcm = _regions(OLD)[0]
    assert (atcm.memory, atcm.window, atcm.source) == (None, None, None)
    assert atcm.memory_name == "CPU0ATCM"


def test_old_entries_are_written_back_unchanged():
    for entry in OLD:
        assert memory_region_dict(_regions([entry])[0]) == {
            **{k: v for k, v in entry.items() if k != "core"}, **({"core": entry["core"]} if "core" in entry else {})}


def test_old_entry_dict_has_no_new_keys():
    for region in _regions(OLD):
        assert not {"memory", "window", "source"} & set(memory_region_dict(region))


def test_new_fields_are_written_only_when_set():
    dicts = [memory_region_dict(r) for r in _regions(GROUPED)]
    assert dicts[0]["memory"] == "GMU" and dicts[0]["window"] == "normal" and "source" in dicts[0]
    assert "source" not in dicts[1] and dicts[1]["window"] == "device"
    assert "memory" not in dicts[2]


def test_memory_equal_to_the_name_is_not_written():
    region = MemoryRegionDef("GMU", 0x10000000, 0x1000, memory="GMU")
    assert "memory" not in memory_region_dict(region)


def test_round_trip_of_grouped_entries():
    regions = _regions(GROUPED)
    assert parse_memory_regions([memory_region_dict(r) for r in regions]) == regions


def test_equal_to_the_old_definition_for_entries_without_new_fields():
    """Positional construction as before still works and compares equal."""
    old_style = MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", LOCAL, False)
    assert old_style == _regions([{"name": "CPUXATCM", "start": 0, "size": 0x10000, "type": "ram",
                                   "core": "local", "cacheable": False}])[0]


@pytest.mark.parametrize("field", ["memory", "window", "source"])
def test_new_fields_must_be_text(field):
    entry = {**OLD[1], field: 5}
    with pytest.raises(ValueError, match=field):
        parse_memory_regions([entry])


def test_blank_new_fields_are_taken_as_unset():
    region = _regions([{**OLD[1], "memory": "  ", "window": ""}])[0]
    assert (region.memory, region.window) == (None, None)


# --- grouping ---------------------------------------------------------------------------

def test_windows_of_one_memory_are_grouped_in_file_order():
    groups = group_memories(_regions(GROUPED))
    assert [(g.name, [w.name for w in g.windows]) for g in groups] == [
        ("GMU", ["GMU_NORMAL", "GMU_DEVICE"]), ("LMU1_NORMAL", ["LMU1_NORMAL"])]


def test_group_properties():
    gmu = group_memories(_regions(GROUPED))[0]
    assert gmu.start == 0x10000000 and gmu.sizes == {0x40000}
    assert [w.cacheable for w in gmu.windows] == [True, False]


def test_a_group_keeps_the_position_of_its_first_window():
    regions = _regions([GROUPED[0], GROUPED[2], GROUPED[1]])
    assert [g.name for g in group_memories(regions)] == ["GMU", "LMU1_NORMAL"]


def test_chip_without_grouping_gives_one_group_per_entry():
    groups = group_memories(_regions(OLD))
    assert [(g.name, len(g.windows)) for g in groups] == [("CPU0ATCM", 1), ("GMU_NORMAL", 1)]


def test_rename_memory_changes_every_window():
    renamed = rename_memory(_regions(GROUPED), "GMU", "GMU0")
    assert [r.memory for r in renamed] == ["GMU0", "GMU0", None]
    assert [r.name for r in renamed] == ["GMU_NORMAL", "GMU_DEVICE", "LMU1_NORMAL"]


def test_rename_of_a_single_window_memory_keeps_the_entry_name():
    renamed = rename_memory(_regions(GROUPED), "LMU1_NORMAL", "LMU1")
    assert renamed[2].name == "LMU1_NORMAL" and renamed[2].memory == "LMU1"


def test_rename_to_an_existing_memory_is_refused():
    with pytest.raises(ValueError, match="LMU1_NORMAL"):
        rename_memory(_regions(GROUPED), "GMU", "LMU1_NORMAL")


# --- problems: errors stop the save, the doubtful are only listed -------------------------

def test_clean_data_has_no_problems():
    assert region_problems(_regions(GROUPED)) == ([], [])


def test_repeated_name_is_an_error():
    errors, _ = region_problems(_regions([OLD[1], OLD[1]]))
    assert errors == ["名称重复：GMU_NORMAL"]


def test_different_sizes_in_one_memory_are_only_doubtful():
    entries = copy.deepcopy(GROUPED)
    entries[1]["size"] = "0x20000"
    errors, doubts = region_problems(_regions(entries))
    assert errors == [] and doubts == ["存储 GMU 的窗口大小不一致：GMU_NORMAL 0x40000，GMU_DEVICE 0x20000"]


def test_mixed_types_in_one_memory_are_only_doubtful():
    entries = copy.deepcopy(GROUPED)
    entries[1]["type"] = "flash"
    errors, doubts = region_problems(_regions(entries))
    assert errors == [] and doubts == ["存储 GMU 的窗口类型不一致：GMU_NORMAL ram，GMU_DEVICE flash"]


def test_overlap_with_another_memory_is_only_doubtful():
    entries = copy.deepcopy(GROUPED)
    entries[2]["start"] = "0x10001000"
    errors, doubts = region_problems(_regions(entries))
    assert errors == []
    assert doubts == ["窗口重叠：GMU_NORMAL 与 LMU1_NORMAL（不同存储）"]


def test_windows_of_one_memory_at_other_addresses_are_not_an_overlap():
    assert region_problems(_regions(GROUPED))[1] == []


def test_overlap_inside_one_memory_is_doubtful_too():
    entries = copy.deepcopy(GROUPED)
    entries[1]["start"] = "0x10001000"
    _, doubts = region_problems(_regions(entries))
    assert doubts == ["窗口重叠：GMU_NORMAL 与 GMU_DEVICE（同一存储，别名不应相互重叠）"]


def test_problems_come_back_in_a_fixed_order():
    entries = copy.deepcopy(GROUPED)
    entries[1]["size"] = "0x20000"
    entries[2]["start"] = "0x10001000"
    first = region_problems(_regions(entries))
    assert first == region_problems(_regions(entries))
    assert len(first[1]) == 2


def test_unrelated_symbols_are_still_exported():
    assert mr.REGION_TYPES == ("flash", "ram") and mr.LOCAL == "local"
