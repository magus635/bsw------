"""update-linker-generator-authority, section 2: the generator follows the configured start mode,
size, load region and limit alignment of each execution region; an older configuration gives
the previous output apart from the limit region alignment; round trip through the scatter reader."""
import copy

from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import plan as pl
from autosar_configurator.core.memmap.config import (
    FIXED,
    OFFSET,
    ExecRegion,
    LoadRegion,
    MemoryMapConfig,
)
from autosar_configurator.core.memmap.generators import ads
from autosar_configurator.core.memmap.scatter import parse_scatter

from tests.core.test_ads_generator import EXPECTED
from tests.core.test_linker_plan import CHIP, NEEDS, ROWS, _config

DFLASH = MemoryRegionDef("DFLASH_NORMAL", 0x0A000000, 0x40000, "flash", None, True)
CHIP2 = CHIP + [DFLASH]


def _plan(config, rows=ROWS, needs=NEEDS, chip=CHIP):
    return pl.build_plan(config, rows, chip, needs)


def _lines(config, **kw):
    return ads.generate(_plan(config, **kw)).splitlines()


def _stacks(config):
    """Two more stacks after CORE0_USER_STACK on CPU0BTCM."""
    config.regions += [
        ExecRegion("CORE0_IRQ_STACK", "CPU0BTCM", "CPU0BTCM", "stack", 11, align=8),
        ExecRegion("CORE0_FIQ_STACK", "CPU0BTCM", "CPU0BTCM", "stack", 12, align=8),
    ]
    return config


# --- start modes ------------------------------------------------------------------------------

def test_after_is_the_default_and_unchanged():
    plan = _plan(_config())
    region = plan.region("UNDEFINE_RAM_BSS")
    assert (region.start_mode, region.start_window, region.after, region.offset, region.address) == (
        "after", None, "UNDEFINE_RAM_DATA", 0, None)
    assert ("    UNDEFINE_RAM_BSS AlignExpr(ImageLimit(UNDEFINE_RAM_DATA), 64) ALIGN 64 0x40000"
            in _lines(_config()))


def test_offset_from_the_window_base():
    config = _config()
    config.set_start("UNDEFINE_RAM_DATA", OFFSET, offset=0x20000)
    region = _plan(config).region("UNDEFINE_RAM_DATA")
    assert (region.start_mode, region.start_window, region.after, region.offset) == (
        OFFSET, "GMU_NORMAL", None, 0x20000)
    lines = _lines(config)
    assert "    UNDEFINE_RAM_DATA GMU_NORMAL_ADDRESS+0x20000 ALIGN 64 0x40000" in lines
    # the next region of the window still follows it
    assert "    UNDEFINE_RAM_BSS AlignExpr(ImageLimit(UNDEFINE_RAM_DATA), 64) ALIGN 64 0x40000" in lines


def test_offset_not_first_in_its_window():
    config = _config()
    config.set_start("UNDEFINE_RAM_BSS", OFFSET, offset=0x30000)
    region = _plan(config).region("UNDEFINE_RAM_BSS")
    assert (region.start_window, region.after) == ("GMU_NORMAL", None)
    assert "    UNDEFINE_RAM_BSS GMU_NORMAL_ADDRESS+0x30000 ALIGN 64 0x40000" in _lines(config)


def test_fixed_address_defined_and_used():
    config = _config()
    config.set_start("CORE0_USER_STACK", FIXED, address=0x30129000)
    region = _plan(config).region("CORE0_USER_STACK")
    assert (region.start_mode, region.start_window, region.after, region.address) == (
        FIXED, None, None, 0x30129000)
    lines = _lines(config)
    assert "#define CORE0_USER_STACK_ADDRESS       0x30129000" in lines
    # the region defines come after the window defines, before the load region
    assert lines.index("#define CORE0_USER_STACK_ADDRESS       0x30129000") == \
        lines.index("#define CPU0BTCM_ADDRESS               0x30100000") + 1
    assert "    CORE0_USER_STACK CORE0_USER_STACK_ADDRESS ALIGN 8 EMPTY 0x1000 {}" in lines


def test_after_follows_a_fixed_region():
    config = _stacks(_config())
    config.set_start("CORE0_USER_STACK", FIXED, address=0x30129000)
    plan = _plan(config)
    assert plan.region("CORE0_IRQ_STACK").after == "CORE0_USER_STACK"
    assert plan.region("CORE0_FIQ_STACK").after == "CORE0_IRQ_STACK"
    lines = _lines(config)
    assert "    CORE0_IRQ_STACK AlignExpr(ImageLimit(CORE0_USER_STACK), 8) ALIGN 8 EMPTY 0x1000 {}" in lines
    assert "    CORE0_FIQ_STACK AlignExpr(ImageLimit(CORE0_IRQ_STACK), 8) ALIGN 8 EMPTY 0x1000 {}" in lines


def test_fixed_address_outside_the_window_is_only_warned():
    config = _config()
    config.set_start("PRIVATE_DATA_CORE0", FIXED, address=0x10000000)
    plan = _plan(config)
    refusals, warnings = pl.check_plan(plan)
    assert refusals == []
    assert any("PRIVATE_DATA_CORE0" in w and "0x10000000" in w and "CPU0BTCM" in w for w in warnings)
    assert "    PRIVATE_DATA_CORE0 PRIVATE_DATA_CORE0_ADDRESS ALIGN 64 0x30000" in ads.generate(plan).splitlines()


def test_fixed_address_inside_the_window_is_not_warned():
    config = _config()
    config.set_start("CORE0_USER_STACK", FIXED, address=0x30129000)
    assert pl.check_plan(_plan(config)) == ([], [])


# --- size -------------------------------------------------------------------------------------

def test_size_of_a_data_region():
    config = _config()
    assert _plan(config).region("UNDEFINE_RAM_DATA").size == 0x40000       # no size: the window's
    config.set_size("UNDEFINE_RAM_DATA", 0x8000)
    assert _plan(config).region("UNDEFINE_RAM_DATA").size == 0x8000
    assert "    UNDEFINE_RAM_DATA GMU_NORMAL_ADDRESS ALIGN 64 0x8000" in _lines(config)


def test_size_of_a_stack():
    config = _config()
    config.set_size("CORE0_USER_STACK", 0x2000)
    assert ("    CORE0_USER_STACK AlignExpr(ImageLimit(PRIVATE_BSS_CORE0), 8) ALIGN 8 EMPTY 0x2000 {}"
            in _lines(config))


def test_configured_size_wins_over_the_factory_layout():
    config = _config()
    config.set_size("CORE0_USER_STACK", 0x3000)
    plan = pl.build_plan(config, ROWS, CHIP, NEEDS, layout=[{"name": "CORE0_USER_STACK", "size": "0x2000"}])
    assert plan.region("CORE0_USER_STACK").size == 0x3000


# --- load regions -----------------------------------------------------------------------------

def _two_loads():
    config = _config()
    config.regions.append(ExecRegion("DFLASH_DATA", "DFLASH", "DFLASH_NORMAL", "const", 1))
    config.add_load_region(LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x300000))
    config.add_load_region(LoadRegion("DFLASH_CODE", "DFLASH_NORMAL", 0x40000))
    config.set_load_region("DFLASH_DATA", "DFLASH_CODE")
    return config


def test_two_load_regions_in_the_plan():
    plan = _plan(_two_loads(), needs=[], chip=CHIP2)
    assert plan.load_regions == (pl.LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x08000000, 0x300000),
                                 pl.LoadRegion("DFLASH_CODE", "DFLASH_NORMAL", 0x0A000000, 0x40000))
    assert plan.region("DFLASH_DATA").load_region == "DFLASH_CODE"
    assert plan.region("DFLASH_DATA").start_window == "DFLASH_NORMAL"
    assert {r.load_region for r in plan.regions if r.name != "DFLASH_DATA"} == {"ROM_CODE"}
    assert pl.check_plan(plan)[0] == []


def test_two_load_regions_in_the_file():
    text = ads.generate(_plan(_two_loads(), needs=[], chip=CHIP2))
    lines = text.splitlines()
    first, second = lines.index("ROM_CODE CPUXPFLASH0_ADDRESS 0x300000"), lines.index(
        "DFLASH_CODE DFLASH_NORMAL_ADDRESS 0x40000")
    assert first < second
    assert "#define DFLASH_NORMAL_ADDRESS          0x0A000000" in lines
    block1, block2 = lines[first:second], lines[second:]
    assert block2 == [
        "DFLASH_CODE DFLASH_NORMAL_ADDRESS 0x40000",
        "{",
        ";DFLASH_NORMAL",
        "    DFLASH_DATA DFLASH_NORMAL_ADDRESS ALIGN 64 0x40000",
        "    {",
        "    }",
        "",
        "; Limit regions: their Image$$<name>_LIMIT$$Base symbols mark where a region ends.",
        "    DFLASH_DATA_LIMIT AlignExpr(ImageLimit(DFLASH_DATA), 64) EMPTY 0x0 {}",
        "}",
    ]
    assert not any("DFLASH_DATA" in line for line in block1)
    # the first block: its regions, then its own limit regions, then the reserved regions, then "}"
    limit_lines = [i for i, line in enumerate(block1) if line.endswith("EMPTY 0x0 {}") and "_LIMIT Align" in line
                   and "CORE2" not in line]
    region_lines = [i for i, line in enumerate(block1) if line.startswith("    ") and " ALIGN " in line]
    assert limit_lines and max(region_lines) < min(limit_lines)
    reserved = block1.index("    PRIVATE_DATA_CORE2 AlignExpr(ImageLimit(CORE0_USER_STACK), 64) EMPTY 0x0 {}")
    assert max(limit_lines) < reserved
    assert block1[-2:] == ["}", ""]        # then the blank line before the next load region


def test_region_with_no_load_region_goes_to_the_first():
    config = _two_loads()
    config.region("EX_CODE").load_region = ""
    assert _plan(config, chip=CHIP2).region("EX_CODE").load_region == "ROM_CODE"


def test_missing_load_region_is_refused():
    config = _two_loads()
    config.region("UNDEFINE_RAM_BSS").load_region = "NO_SUCH_LOAD"
    plan = _plan(config, chip=CHIP2)
    refusals, _ = pl.check_plan(plan)
    assert any("UNDEFINE_RAM_BSS" in r and "NO_SUCH_LOAD" in r for r in refusals)
    assert plan.region("UNDEFINE_RAM_BSS") is None


def test_without_configured_load_regions_only_the_implicit_one_may_be_named():
    config = _config()
    config.region("EX_CODE").load_region = "ROM_CODE"      # the implicit load region: accepted
    assert pl.check_plan(_plan(config)) == ([], [])
    config.region("EX_CODE").load_region = "DFLASH_CODE"
    refusals, _ = pl.check_plan(_plan(config))
    assert any("EX_CODE" in r and "DFLASH_CODE" in r for r in refusals)


def test_load_region_on_a_window_not_on_the_chip_is_refused():
    config = _two_loads()
    refusals, _ = pl.check_plan(_plan(config, chip=CHIP))      # no DFLASH_NORMAL on this chip
    assert any("DFLASH_CODE" in r and "DFLASH_NORMAL" in r for r in refusals)


def test_empty_load_region_left_out_with_a_warning():
    config = _two_loads()
    config.set_load_region("DFLASH_DATA", "")
    plan = _plan(config, chip=CHIP2)
    assert [l.name for l in plan.load_regions] == ["ROM_CODE"]
    assert any("DFLASH_CODE" in w for w in pl.check_plan(plan)[1])
    assert "DFLASH_CODE" not in ads.generate(plan)


# --- limit alignment --------------------------------------------------------------------------

def test_limit_alignment_64_for_a_stack_with_align_8():
    plan = _plan(_config(), needs=[])       # no needs: every region gets a limit region
    assert plan.region("CORE0_USER_STACK").align == 8
    assert plan.region("CORE0_USER_STACK").limit_align == 64
    assert ("    CORE0_USER_STACK_LIMIT AlignExpr(ImageLimit(CORE0_USER_STACK), 64) EMPTY 0x0 {}"
            in ads.generate(plan).splitlines())


def test_limit_alignment_configured():
    config = _config()
    config.region("UNDEFINE_RAM_DATA").limit_align = 256
    assert ("    UNDEFINE_RAM_DATA_LIMIT AlignExpr(ImageLimit(UNDEFINE_RAM_DATA), 256) EMPTY 0x0 {}"
            in _lines(config))


# --- an older configuration -------------------------------------------------------------------

def _previous_output(text_now, regions):
    """The output before this change: limit regions were aligned to the region's own alignment."""
    lines = []
    for line in text_now.split("\n"):
        for region in regions:
            if line == f"    {region.name}_LIMIT AlignExpr(ImageLimit({region.name}), 64) EMPTY 0x0 {{}}":
                line = f"    {region.name}_LIMIT AlignExpr(ImageLimit({region.name}), {region.align}) EMPTY 0x0 {{}}"
        lines.append(line)
    return "\n".join(lines)


def test_older_configuration_same_output_with_the_needs():
    """With the scanned needs no region of align other than 64 needs a limit: no byte changes."""
    assert ads.generate(_plan(_config())) == EXPECTED


def test_older_configuration_only_the_limit_alignment_changes():
    """Without needs every region gets a limit; only the stack's limit line (align 8) changes."""
    config = _config()
    # the previous output, written by hand (it is EXPECTED with a limit region for every region)
    previous = EXPECTED.replace(
        "\n; Limit regions: their Image$$<name>_LIMIT$$Base symbols mark where a region ends.\n",
        "\n; Limit regions: their Image$$<name>_LIMIT$$Base symbols mark where a region ends.\n"
        "    EX_CODE_LIMIT AlignExpr(ImageLimit(EX_CODE), 64) EMPTY 0x0 {}\n").replace(
        "    PRIVATE_BSS_CORE0_LIMIT AlignExpr(ImageLimit(PRIVATE_BSS_CORE0), 64) EMPTY 0x0 {}\n",
        "    PRIVATE_BSS_CORE0_LIMIT AlignExpr(ImageLimit(PRIVATE_BSS_CORE0), 64) EMPTY 0x0 {}\n"
        "    CORE0_USER_STACK_LIMIT AlignExpr(ImageLimit(CORE0_USER_STACK), 8) EMPTY 0x0 {}\n")
    now = ads.generate(_plan(config, needs=[]))
    now_lines, previous_lines = now.splitlines(), previous.splitlines()
    assert len(now_lines) == len(previous_lines)
    changed = [(a, b) for a, b in zip(previous_lines, now_lines) if a != b]
    assert changed == [("    CORE0_USER_STACK_LIMIT AlignExpr(ImageLimit(CORE0_USER_STACK), 8) EMPTY 0x0 {}",
                        "    CORE0_USER_STACK_LIMIT AlignExpr(ImageLimit(CORE0_USER_STACK), 64) EMPTY 0x0 {}")]
    assert _previous_output(now, config.regions) == previous


def test_older_configuration_plan_has_the_previous_shape():
    plan = _plan(_config())
    assert all(r.start_mode == "after" and r.offset == 0 and r.address is None for r in plan.regions)
    assert plan.load_regions == (pl.LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x08000000, 0x300000),)
    assert plan.doubts == () and plan.empty_load_regions == () and plan.forward_after == ()


def test_determinism_with_the_new_fields():
    config = _stacks(_two_loads())
    config.set_start("CORE0_USER_STACK", FIXED, address=0x30129000)
    config.set_start("UNDEFINE_RAM_DATA", OFFSET, offset=0x20000)
    shuffled = copy.deepcopy(config)
    shuffled.regions.reverse()
    assert _plan(config, chip=CHIP2) == _plan(shuffled, rows=list(reversed(ROWS)),
                                              needs=list(reversed(NEEDS)), chip=CHIP2)
    assert ads.generate(_plan(config, chip=CHIP2)) == ads.generate(_plan(shuffled, chip=CHIP2))


# --- round trip -------------------------------------------------------------------------------

def test_round_trip_through_the_scatter_reader():
    config = _stacks(_two_loads())
    config.set_start("CORE0_USER_STACK", FIXED, address=0x30129000)
    config.set_start("UNDEFINE_RAM_DATA", OFFSET, offset=0x20000)
    config.set_size("CORE0_IRQ_STACK", 0x2000)
    plan = _plan(config, needs=[], chip=CHIP2)
    assert pl.check_plan(plan)[0] == []
    scatter = parse_scatter(ads.generate(plan), "scatter.scat")

    expected = []
    for load in plan.load_regions:
        in_load = [r for r in plan.regions if r.load_region == load.name]
        expected += [r.name for r in in_load] + [r.name + "_LIMIT" for r in in_load if r.needs_limit]
        if load is plan.load_regions[0]:
            for r in plan.reserved:
                expected += [r.name] + ([r.name + "_LIMIT"] if r.needs_limit else [])
    assert [r.name for r in scatter.regions] == expected

    for region in plan.regions:
        read = scatter.region(region.name)
        assert read.load_region == region.load_region
        assert [s.names for s in read.selectors] == [(name,) for name in region.sections]
        assert read.follows == region.after
    assert scatter.region("EX_CODE").address == 0x08000000
    assert scatter.region("UNDEFINE_RAM_DATA").address == 0x10000000 + 0x20000
    assert scatter.region("UNDEFINE_RAM_BSS").follows == "UNDEFINE_RAM_DATA"
    assert scatter.region("UNDEFINE_RAM_BSS").address == 0x10020000      # resolved through follows
    assert scatter.region("CORE0_USER_STACK").address == 0x30129000
    assert scatter.region("CORE0_IRQ_STACK").follows == "CORE0_USER_STACK"
    assert scatter.region("CORE0_IRQ_STACK").address == 0x30129000
    assert scatter.region("DFLASH_DATA").address == 0x0A000000
    assert scatter.region("DFLASH_DATA").load_region == "DFLASH_CODE"
    assert scatter.region("DFLASH_DATA_LIMIT").load_region == "DFLASH_CODE"
    assert scatter.region("CORE0_USER_STACK_LIMIT").follows == "CORE0_USER_STACK"
