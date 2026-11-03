"""Linker plan: built from the layout configuration, the scan rows, the chip's memory regions and
the link symbol needs; compiler independent; refusals and warnings before generating."""
import pytest

from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import plan as pl
from autosar_configurator.core.memmap.check import SectionRow
from autosar_configurator.core.memmap.config import (
    ExecRegion,
    MemoryMapConfig,
    Rule,
    config_path,
    load_config,
    save_config,
)
from autosar_configurator.core.memmap.symbols import BASE, CLEAR, COPY, LIMIT, LOAD, STACK, Reference, RegionNeed

CHIP = [
    MemoryRegionDef("CPUXPFLASH0", 0x08000000, 0x300000, "flash", None, True),
    MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True),
    MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
]


def _row(output, kind, core=None):
    return SectionRow(output=output, kind=kind, names=(), modules=("Can",), core=core,
                      non_cacheable=False, uses=(("Can.c", 1),))


def _need(region, *uses):
    return RegionNeed(region, list(uses), [Reference(region, tuple(uses), "startup.c", 1, "X")])


def _config():
    config = MemoryMapConfig(chip="THA6206_LFBGA292")
    config.regions = [
        ExecRegion("EX_CODE", "PFLASH0", "CPUXPFLASH0", "code", 1, required=True),
        ExecRegion("UNDEFINE_RAM_DATA", "GMU", "GMU_NORMAL", "data", 1, required=True),
        ExecRegion("UNDEFINE_RAM_BSS", "GMU", "GMU_NORMAL", "bss", 2, required=True),
        ExecRegion("PRIVATE_DATA_CORE0", "CPU0BTCM", "CPU0BTCM", "data", 1, required=True),
        ExecRegion("PRIVATE_BSS_CORE0", "CPU0BTCM", "CPU0BTCM", "bss", 2, required=True),
        ExecRegion("CORE0_USER_STACK", "CPU0BTCM", "CPU0BTCM", "stack", 10, align=8, required=True),
    ]
    config.rules = [
        Rule("core0 bss", {"kind": ["BSS"], "core": 0}, "PRIVATE_BSS_CORE0"),
        Rule("core0 data", {"kind": ["DATA"], "core": 0}, "PRIVATE_DATA_CORE0"),
        Rule("code", {"kind": ["TEXT"]}, "EX_CODE"),
        Rule("bss", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS"),
        Rule("data", {"kind": ["DATA"]}, "UNDEFINE_RAM_DATA"),
    ]
    config.trimmed = ["PRIVATE_DATA_CORE2"]
    return config


ROWS = [
    _row(".mcal_text_asil_d", "TEXT"),
    _row(".mcal_bss_asil_d_unspecified_core0", "BSS", 0),
    _row(".mcal_bss_asil_d_8_core0", "BSS", 0),
    _row(".mcal_data_asil_d_32", "DATA"),
    _row(".mcal_bss_asil_d_32", "BSS"),
]
NEEDS = [
    _need("UNDEFINE_RAM_DATA", BASE, LIMIT, LOAD, COPY),
    _need("UNDEFINE_RAM_BSS", BASE, CLEAR),
    _need("PRIVATE_DATA_CORE0", BASE, LIMIT, LOAD, COPY),
    _need("PRIVATE_BSS_CORE0", BASE, CLEAR),
    _need("CORE0_USER_STACK", STACK),
    _need("PRIVATE_DATA_CORE2", BASE, LIMIT, LOAD, COPY),
]


def _plan(config=None, rows=ROWS, needs=NEEDS, **kw):
    return pl.build_plan(config or _config(), rows, CHIP, needs, **kw)


def test_regions_in_window_order_with_start():
    plan = _plan()
    assert [(r.name, r.window, r.start_window, r.after) for r in plan.regions] == [
        ("EX_CODE", "CPUXPFLASH0", "CPUXPFLASH0", None),
        ("UNDEFINE_RAM_DATA", "GMU_NORMAL", "GMU_NORMAL", None),
        ("UNDEFINE_RAM_BSS", "GMU_NORMAL", None, "UNDEFINE_RAM_DATA"),
        ("PRIVATE_DATA_CORE0", "CPU0BTCM", "CPU0BTCM", None),
        ("PRIVATE_BSS_CORE0", "CPU0BTCM", None, "PRIVATE_DATA_CORE0"),
        ("CORE0_USER_STACK", "CPU0BTCM", None, "PRIVATE_BSS_CORE0"),
    ]
    assert [w.name for w in plan.windows] == ["CPUXPFLASH0", "GMU_NORMAL", "CPU0BTCM"]
    assert plan.load_regions == (pl.LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x08000000, 0x300000),)


def test_sections_sorted_by_name_in_their_region():
    plan = _plan()
    assert plan.region("PRIVATE_BSS_CORE0").sections == (
        ".mcal_bss_asil_d_8_core0", ".mcal_bss_asil_d_unspecified_core0")
    assert plan.region("EX_CODE").sections == (".mcal_text_asil_d",)
    assert plan.region("CORE0_USER_STACK").sections == ()


def test_limit_regions_follow_the_needs_and_stack_tops_need_none():
    plan = _plan()
    assert plan.limit_regions() == ["UNDEFINE_RAM_DATA", "UNDEFINE_RAM_BSS", "PRIVATE_DATA_CORE0",
                                    "PRIVATE_BSS_CORE0", "PRIVATE_DATA_CORE2"]
    assert not plan.region("CORE0_USER_STACK").needs_limit
    assert not plan.region("EX_CODE").needs_limit           # no code asks for it


def test_named_limit_need_marks_its_region():
    plan = _plan(needs=NEEDS + [_need("EX_CODE_LIMIT", BASE)])
    assert plan.region("EX_CODE").needs_limit
    assert "EX_CODE_LIMIT" not in plan.missing_needed


def test_sizes_window_bound_and_stack_default_and_layout():
    plan = _plan()
    assert plan.region("EX_CODE").size == 0x300000            # the window's size
    assert plan.region("CORE0_USER_STACK").size == 0x1000     # the vendor's stack size
    plan = _plan(layout=[{"name": "CORE0_USER_STACK", "size": "0x2000"},
                         {"name": "EX_CODE", "size": 0x100000}])
    assert plan.region("CORE0_USER_STACK").size == 0x2000
    assert plan.region("EX_CODE").size == 0x100000


def test_same_input_same_plan_whatever_the_input_order():
    config = _config()
    shuffled = _config()
    shuffled.regions.reverse()
    assert _plan(config) == _plan(config)
    assert _plan(config) == _plan(shuffled, rows=list(reversed(ROWS)), needs=list(reversed(NEEDS)))


def test_reserved_region_for_a_missing_core_by_default():
    plan = _plan()
    assert pl.reserve_missing_cores(_config())
    assert plan.reserved == (pl.ReservedRegion("PRIVATE_DATA_CORE2", "CORE0_USER_STACK", 64, True,
                                               (COPY, BASE, LIMIT, LOAD)),)


def test_reserved_option_off():
    config = _config()
    pl.set_reserve_missing_cores(config, False)
    plan = _plan(config)
    assert plan.reserved == ()
    assert not plan.reserve_missing_cores


def test_reserved_option_kept_with_the_project(tmp_path):
    config = _config()
    pl.set_reserve_missing_cores(config, False)
    save_config(config, config_path(tmp_path))
    assert not pl.reserve_missing_cores(load_config(config_path(tmp_path)))


def test_complete_configuration_is_neither_refused_nor_warned():
    assert pl.check_plan(_plan()) == ([], [])


def test_section_to_place_again_is_refused_by_name():
    config = _config()
    config.manual[".mcal_data_asil_d_32"] = "GONE_REGION"
    refusals, _ = pl.check_plan(_plan(config))
    assert len(refusals) == 1 and ".mcal_data_asil_d_32" in refusals[0] and "待重新放置" in refusals[0]


def test_required_region_without_window_is_refused():
    config = _config()
    config.region("UNDEFINE_RAM_BSS").window = ""
    plan = _plan(config)
    refusals, _ = pl.check_plan(plan)
    assert any("UNDEFINE_RAM_BSS" in r and "没有落到" in r for r in refusals)
    assert plan.region("UNDEFINE_RAM_BSS") is None


def test_window_not_on_the_chip_is_refused():
    config = _config()
    config.region("UNDEFINE_RAM_BSS").window = "LMU9_NORMAL"
    refusals, _ = pl.check_plan(_plan(config))
    assert any("LMU9_NORMAL" in r for r in refusals)


def test_no_region_at_all_is_refused():
    refusals, _ = pl.check_plan(pl.build_plan(MemoryMapConfig(), [], CHIP, []))
    assert refusals


def test_section_not_placed_is_only_warned():
    rows = ROWS + [_row(".mcal_const_asil_d_32", "RODATA")]
    plan = _plan(rows=rows)
    refusals, warnings = pl.check_plan(plan)
    assert refusals == []
    assert any(".mcal_const_asil_d_32" in w and "未放置" in w for w in warnings)


def test_without_scanned_needs_every_region_gets_a_limit_and_a_warning():
    plan = _plan(needs=[])
    assert all(r.needs_limit for r in plan.regions)
    _, warnings = pl.check_plan(plan)
    assert pl.DEFAULT_LAYOUT_WARNING in warnings


def test_needed_region_not_configured_is_warned():
    plan = _plan(needs=NEEDS + [_need("CODE_CLONE", BASE)])
    _, warnings = pl.check_plan(plan)
    assert any("CODE_CLONE" in w for w in warnings)


def test_spec_scenario_bss_core0_after_previous_in_cpu0btcm():
    region = _plan().region("PRIVATE_BSS_CORE0")
    assert region.window == "CPU0BTCM" and region.after == "PRIVATE_DATA_CORE0"
    assert ".mcal_bss_asil_d_unspecified_core0" in region.sections
