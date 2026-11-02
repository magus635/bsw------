"""A chip change and the layout: what stays valid, what is to be placed again, and that nothing
is ever dropped."""
from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import chipchange as cc
from autosar_configurator.core.memmap import config as cfg
from autosar_configurator.core.memmap.config import ExecRegion, MemoryMapConfig, Rule

OLD = [
    MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True, "GMU", "normal"),
    MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False, "GMU", "device"),
    MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
    MemoryRegionDef("CPU1BTCM", 0x30500000, 0x30000, "ram", 1, False),
]


def _config():
    return MemoryMapConfig(
        chip="OLD",
        regions=[ExecRegion("UNDEFINE_RAM_BSS", "GMU", "GMU_NORMAL", "bss", 1, required=True, origin="required"),
                 ExecRegion("GLOBAL_UNCACHED_BSS", "GMU", "GMU_DEVICE", "bss", 2, required=True, origin="required"),
                 ExecRegion("PRIVATE_BSS_CORE0", "CPU0BTCM", "CPU0BTCM", "bss", 1, required=True, origin="required"),
                 ExecRegion("PRIVATE_BSS_CORE1", "CPU1BTCM", "CPU1BTCM", "bss", 1, required=True, origin="required"),
                 ExecRegion("MINE", "GMU", "GMU_NORMAL", "data", 3, origin="user")],
        rules=[Rule("r", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS")],
        manual={".a": "PRIVATE_BSS_CORE0", ".b": "GLOBAL_UNCACHED_BSS"})


def _by_name(report):
    return {entry.region: entry for entry in report.regions}


def test_the_same_chip_keeps_everything():
    report = cc.compare(_config(), OLD, OLD)
    assert all(e.status == cc.KEPT for e in report.regions) and report.lost == []


def test_a_window_with_other_attributes_is_to_be_placed_again():
    new = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True, "GMU", "normal"),
           MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, True, "GMU", "device"),   # now cacheable
           OLD[2], OLD[3]]
    entries = _by_name(cc.compare(_config(), OLD, new))
    assert entries["GLOBAL_UNCACHED_BSS"].status == cc.AGAIN
    assert "可缓存" in entries["GLOBAL_UNCACHED_BSS"].reason
    assert entries["UNDEFINE_RAM_BSS"].status == cc.KEPT


def test_a_missing_window_is_to_be_placed_again():
    entries = _by_name(cc.compare(_config(), OLD, OLD[:3]))
    assert entries["PRIVATE_BSS_CORE1"].status == cc.AGAIN and "没有窗口 CPU1BTCM" in entries["PRIVATE_BSS_CORE1"].reason


def test_a_window_of_another_core_is_to_be_placed_again():
    new = [OLD[0], OLD[1], OLD[2], MemoryRegionDef("CPU1BTCM", 0x30500000, 0x30000, "ram", 2, False)]
    assert _by_name(cc.compare(_config(), OLD, new))["PRIVATE_BSS_CORE1"].status == cc.AGAIN


def test_a_window_of_another_type_is_to_be_placed_again():
    new = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "flash", None, True, "GMU", "normal"), *OLD[1:]]
    assert _by_name(cc.compare(_config(), OLD, new))["UNDEFINE_RAM_BSS"].status == cc.AGAIN


def test_a_region_is_never_moved_to_another_window_on_its_own():
    """The chip has a GMU_DEVICE too, but a region on GMU_NORMAL stays there or is flagged."""
    new = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, False, "GMU", "normal"), *OLD[1:]]
    entry = _by_name(cc.compare(_config(), OLD, new))["UNDEFINE_RAM_BSS"]
    assert entry.status == cc.AGAIN


def test_the_placements_of_a_region_to_be_placed_again_are_listed():
    report = cc.compare(_config(), OLD, OLD[:3])
    assert {(p.section, p.region) for p in report.lost} == set()          # CPU1's region holds no manual placement
    new = [OLD[0], MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, True, "GMU", "device"), *OLD[2:]]
    report = cc.compare(_config(), OLD, new)
    assert [(p.section, p.region) for p in report.lost] == [(".b", "GLOBAL_UNCACHED_BSS")]


def test_manual_placements_in_valid_regions_are_kept():
    report = cc.compare(_config(), OLD, OLD)
    assert report.kept_manual == [".a", ".b"]


def test_a_user_region_is_judged_like_a_required_one():
    entries = _by_name(cc.compare(_config(), OLD, [OLD[1], OLD[2], OLD[3]]))
    assert entries["MINE"].status == cc.AGAIN


def test_a_region_without_a_window_yet_is_not_flagged():
    config = _config()
    config.regions.append(ExecRegion("NEW", "", "", "data", 9, required=True, origin="required"))
    assert _by_name(cc.compare(config, OLD, OLD))["NEW"].status == cc.UNPLACED


def test_applying_the_change_marks_nothing_it_does_not_have_to_and_deletes_nothing():
    config = _config()
    before = (list(config.regions), dict(config.manual), list(config.rules))
    cc.compare(config, OLD, OLD[:2])
    assert (config.regions, config.manual, config.rules) == before         # a preview changes nothing


def test_apply_keeps_every_region_and_placement():
    config = _config()
    names = [r.name for r in config.regions]
    cc.apply(config, "NEW", cc.compare(config, OLD, OLD[:2]))
    assert [r.name for r in config.regions] == names
    assert config.manual == {".a": "PRIVATE_BSS_CORE0", ".b": "GLOBAL_UNCACHED_BSS"} and config.chip == "NEW"


def test_apply_records_which_regions_are_to_be_placed_again():
    config = _config()
    cc.apply(config, "NEW", cc.compare(config, OLD, OLD[:3]))
    assert config.options[cc.AGAIN_KEY] == ["PRIVATE_BSS_CORE1"]


def test_after_apply_the_placements_into_a_lost_region_show_as_again():
    from autosar_configurator.core.memmap import rules as rl
    from autosar_configurator.core.memmap.check import SectionRow
    config = _config()
    config.manual[".c"] = "PRIVATE_BSS_CORE1"
    cc.apply(config, "NEW", cc.compare(config, OLD, OLD[:3]))
    row = SectionRow(output=".c", kind="BSS", names=(), modules=("X",), core=None, non_cacheable=False, uses=())
    assert rl.place(config, row).target == "PRIVATE_BSS_CORE1"             # still there, not rewritten
    assert config.options[cc.AGAIN_KEY] == ["PRIVATE_BSS_CORE1"]


def test_a_window_back_on_the_chip_clears_the_flag():
    config = _config()
    cc.apply(config, "NEW", cc.compare(config, OLD, OLD[:3]))
    cc.apply(config, "OLD", cc.compare(config, OLD[:3], OLD))
    assert config.options.get(cc.AGAIN_KEY, []) == []


def test_the_report_text_names_the_counts():
    report = cc.compare(_config(), OLD, OLD[:3])
    lines = report.summary_lines()
    assert lines[0] == "内存布局：保留 4 个执行区域，待重新放置 1 个"
    assert lines[1] == "  待重新放置：PRIVATE_BSS_CORE1（新芯片没有窗口 CPU1BTCM）"
