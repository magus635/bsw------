"""THA6206's memory regions after add-chip-memory-editor: only the grouping, window and
source fields were added; no address, size, type, core or cache value changed."""
from autosar_configurator.core.hardware.chip_completeness import unconfirmed_marks
from autosar_configurator.core.hardware.chip_database import ChipDatabase, default_chips_dir
from autosar_configurator.core.hardware.memory_regions import group_memories, region_at

# the 25 entries as they were before (add-memory-map-check): name, start, size, type, core, cacheable
BEFORE = [
    ("CPUXATCM", 0x0, 0x10000, "ram", "local", False), ("CPUXBTCM", 0x100000, 0x30000, "ram", "local", False),
    ("CPUXCTCM", 0x200000, 0x10000, "ram", "local", False),
    ("CPUXPFLASH0", 0x8000000, 0x300000, "flash", None, True), ("CPUXPFLASH1", 0x8300000, 0x300000, "flash", None, True),
    ("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True), ("LMU1_NORMAL", 0x10054000, 0x4000, "ram", None, True),
    ("LMU2_NORMAL", 0x10058000, 0x4000, "ram", None, True), ("LMU3_NORMAL", 0x1005C000, 0x4000, "ram", None, True),
    ("CPU0ATCM", 0x30000000, 0x10000, "ram", 0, False), ("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
    ("CPU0CTCM", 0x30200000, 0x10000, "ram", 0, False), ("CPU1ATCM", 0x30400000, 0x10000, "ram", 1, False),
    ("CPU1BTCM", 0x30500000, 0x30000, "ram", 1, False), ("CPU1CTCM", 0x30600000, 0x10000, "ram", 1, False),
    ("PFLASH0_NORMAL", 0x40400000, 0x300000, "flash", None, True), ("PFLASH1_NORMAL", 0x40700000, 0x300000, "flash", None, True),
    ("DFLASH_NORMAL", 0x44000000, 0x80000, "flash", None, True), ("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False),
    ("PFLASH0_DEVICE", 0x90400000, 0x300000, "flash", None, False), ("PFLASH1_DEVICE", 0x90700000, 0x300000, "flash", None, False),
    ("DFLASH_DEVICE", 0x94000000, 0x80000, "flash", None, False), ("LMU1_DEVICE", 0xB0020000, 0x4000, "ram", None, False),
    ("LMU2_DEVICE", 0xC00D0000, 0x4000, "ram", None, False), ("LMU3_DEVICE", 0xD0040000, 0x4000, "ram", None, False),
]


def _chip():
    return ChipDatabase(default_chips_dir()).get_chip("THA6206_LFBGA292")


def test_no_value_changed():
    regions = _chip().memory_regions
    assert [(r.name, r.start, r.size, r.type, r.core, r.cacheable) for r in regions] == BEFORE


def test_every_entry_names_its_source():
    assert {r.source for r in _chip().memory_regions} == {"LinkerAdsPf.scat 注释表"}


def test_the_data_is_still_marked_to_be_confirmed():
    assert "memory_regions" in unconfirmed_marks(_chip())


def test_the_two_windows_of_a_memory_are_grouped():
    groups = {g.name: [w.name for w in g.windows] for g in group_memories(_chip().memory_regions)}
    assert groups["GMU"] == ["GMU_NORMAL", "GMU_DEVICE"]
    assert groups["PFLASH0"] == ["CPUXPFLASH0", "PFLASH0_NORMAL", "PFLASH0_DEVICE"]
    assert groups["LMU2"] == ["LMU2_NORMAL", "LMU2_DEVICE"]


def test_cacheability_follows_the_window():
    gmu = next(g for g in group_memories(_chip().memory_regions) if g.name == "GMU")
    assert {w.window: w.cacheable for w in gmu.windows} == {"normal": True, "device": False}


def test_the_per_core_axi_windows_are_not_grouped_with_the_local_alias():
    """The vendor table does not say whether CPU0BTCM is the same memory as CPUXBTCM, so
    nothing was decided for the user: they stay memories of their own until confirmed."""
    regions = {r.name: r for r in _chip().memory_regions}
    for name in ("CPU0ATCM", "CPU0BTCM", "CPU1CTCM"):
        assert regions[name].memory is None and regions[name].memory_name == name


def test_lookup_by_address_is_unchanged():
    regions = _chip().memory_regions
    assert region_at(regions, 0x30100000).core == 0
    assert region_at(regions, 0x10000000).cacheable
    assert not region_at(regions, 0x82020400).cacheable


def test_the_chip_is_not_flagged_as_modified():
    chip = _chip()
    assert chip.resource_version == "1.0.3" and not chip.content_modified


def test_other_chips_are_untouched():
    db = ChipDatabase(default_chips_dir())
    for name in db.list_chips():
        if name == "THA6206_LFBGA292":
            continue
        assert all(r.memory is None and r.window is None and r.source is None
                   for r in db.get_chip(name).memory_regions), name
