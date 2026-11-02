"""Required execution regions: what code refers to by name, the kind each use implies, the
trimming by core count, and the fallback to the chip's default layout."""
from autosar_configurator.core.memmap import config as cfg
from autosar_configurator.core.memmap import regions as rg
from autosar_configurator.core.memmap.symbols import (
    BASE,
    CLEAR,
    COPY,
    LIMIT,
    LOAD,
    STACK,
    RegionNeed,
    Reference,
)


def _need(name, uses):
    ref = Reference(name, tuple(uses), "startup.c", 10, "STARTUP_X")
    return RegionNeed(name, list(uses), [ref])


# --- the kind a use implies ------------------------------------------------------------

def test_a_copy_region_is_a_data_region():
    assert rg.kind_for(_need("PRIVATE_DATA_CORE0", [COPY, BASE, LIMIT, LOAD])) == cfg.DATA


def test_a_clear_region_is_a_bss_region():
    assert rg.kind_for(_need("PRIVATE_BSS_CORE0", [CLEAR, BASE])) == cfg.BSS


def test_a_stack_region_is_a_stack():
    assert rg.kind_for(_need("CORE0_HYP_STACK", [STACK])) == cfg.STACK


def test_a_region_asked_only_for_its_base_and_a_cleared_limit_is_a_stack_by_name():
    """STARTUP_GETIMAGEBASEADDR(CORE0_USER_STACK) and ..BSSLIMITADDR(CORE0_FIQ_STACK): the
    use says "base" and "clear" but the name says stack."""
    assert rg.kind_for(_need("CORE0_USER_STACK", [BASE])) == cfg.STACK
    assert rg.kind_for(_need("CORE0_FIQ_STACK", [CLEAR])) == cfg.STACK


def test_a_code_region_is_known_by_its_name():
    assert rg.kind_for(_need("PRIVATE_CODE_CORE0", [COPY, BASE, LIMIT, LOAD])) == cfg.CODE
    assert rg.kind_for(_need("INT_VECTOR_TABLE", [COPY, BASE, LIMIT, LOAD])) == cfg.CODE


def test_a_region_with_only_a_base_and_no_name_hint_is_reserved():
    assert rg.kind_for(_need("SOMETHING", [BASE])) == cfg.RESERVED


# --- trimming by cores --------------------------------------------------------------------

def test_the_core_of_a_region_name():
    assert rg.core_of("PRIVATE_DATA_CORE2") == 2 and rg.core_of("CORE3_USER_STACK") == 3
    assert rg.core_of("UNDEFINE_RAM_DATA") is None and rg.core_of("LMU2_CACHED_DATA") is None


def test_regions_of_missing_cores_are_trimmed_and_listed():
    needs = [_need("PRIVATE_DATA_CORE0", [COPY]), _need("PRIVATE_DATA_CORE1", [COPY]),
             _need("PRIVATE_DATA_CORE2", [COPY]), _need("CORE3_USER_STACK", [BASE]),
             _need("UNDEFINE_RAM_DATA", [COPY])]
    result = rg.required_regions(needs, cores=2)
    assert [r.name for r in result.regions] == ["PRIVATE_DATA_CORE0", "PRIVATE_DATA_CORE1", "UNDEFINE_RAM_DATA"]
    assert result.trimmed == ["CORE3_USER_STACK", "PRIVATE_DATA_CORE2"]


def test_without_a_core_count_nothing_is_trimmed():
    needs = [_need("PRIVATE_DATA_CORE2", [COPY])]
    result = rg.required_regions(needs, cores=None)
    assert [r.name for r in result.regions] == ["PRIVATE_DATA_CORE2"] and result.trimmed == []


def test_required_regions_are_marked_required_and_from_code():
    result = rg.required_regions([_need("UNDEFINE_RAM_DATA", [COPY])], cores=2)
    region = result.regions[0]
    assert region.required and region.origin == cfg.REQUIRED_ORIGIN and region.kind == cfg.DATA
    assert result.source == rg.FROM_CODE


def test_the_limit_region_is_never_a_configured_region():
    needs = [_need("UNDEFINE_RAM_DATA", [COPY, LIMIT])]
    names = [r.name for r in rg.required_regions(needs, cores=2).regions]
    assert names == ["UNDEFINE_RAM_DATA"] and not any(n.endswith("_LIMIT") for n in names)


def test_a_need_that_is_itself_a_limit_region_name_is_left_out():
    result = rg.required_regions([_need("X_LIMIT", [BASE])], cores=2)
    assert result.regions == []


def test_the_result_is_ordered_by_name():
    needs = [_need("B_DATA", [COPY]), _need("A_DATA", [COPY])]
    assert [r.name for r in rg.required_regions(needs, cores=2).regions] == ["A_DATA", "B_DATA"]


# --- the fallback ------------------------------------------------------------------------------

DEFAULT_LAYOUT = [
    {"name": "UNDEFINE_RAM_DATA", "memory": "GMU", "window": "GMU_NORMAL", "kind": "data", "order": 1},
    {"name": "PRIVATE_DATA_CORE0", "memory": "CPU0BTCM", "window": "CPU0BTCM", "kind": "data", "order": 1},
    {"name": "PRIVATE_DATA_CORE2", "memory": "CPU2BTCM", "window": "CPU2BTCM", "kind": "data", "order": 1},
]


def test_no_needs_falls_back_to_the_default_layout_and_says_so():
    result = rg.required_regions([], cores=2, default_layout=DEFAULT_LAYOUT)
    assert result.source == rg.FROM_DEFAULT
    assert [r.name for r in result.regions] == ["PRIVATE_DATA_CORE0", "UNDEFINE_RAM_DATA"]
    assert result.trimmed == ["PRIVATE_DATA_CORE2"]
    assert "未经代码核对" in result.source_note()


def test_the_default_layout_regions_are_required_too():
    result = rg.required_regions([], cores=2, default_layout=DEFAULT_LAYOUT)
    assert all(r.required for r in result.regions)


def test_with_needs_the_default_layout_is_ignored_for_the_names():
    result = rg.required_regions([_need("ONLY_ONE", [COPY])], cores=2, default_layout=DEFAULT_LAYOUT)
    assert [r.name for r in result.regions] == ["ONLY_ONE"] and result.source == rg.FROM_CODE


def test_the_layout_gives_a_code_found_region_its_window_and_order():
    result = rg.required_regions([_need("UNDEFINE_RAM_DATA", [COPY])], cores=2, default_layout=DEFAULT_LAYOUT)
    region = result.regions[0]
    assert (region.memory, region.window, region.order) == ("GMU", "GMU_NORMAL", 1)


def test_a_code_found_region_the_layout_does_not_know_has_no_window_yet():
    result = rg.required_regions([_need("NEW_REGION", [COPY])], cores=2, default_layout=DEFAULT_LAYOUT)
    region = result.regions[0]
    assert (region.memory, region.window) == ("", "") and region.kind == cfg.DATA


def test_the_source_note_for_code():
    assert "代码" in rg.required_regions([_need("A_DATA", [COPY])], cores=2).source_note()


# --- merging into a configuration ------------------------------------------------------------------

def test_merge_adds_new_required_regions_and_keeps_the_users_choices():
    config = cfg.MemoryMapConfig(regions=[
        cfg.ExecRegion("UNDEFINE_RAM_DATA", "LMU1", "LMU1_NORMAL", "data", 5, 64, required=True, origin="required")])
    result = rg.required_regions([_need("UNDEFINE_RAM_DATA", [COPY]), _need("NEW_DATA", [COPY])], cores=2)
    rg.merge_required(config, result)
    kept = config.region("UNDEFINE_RAM_DATA")
    assert (kept.memory, kept.window, kept.order) == ("LMU1", "LMU1_NORMAL", 5)      # the user's choice
    assert config.region("NEW_DATA") is not None and config.region("NEW_DATA").required


def test_merge_marks_regions_no_longer_asked_for_but_keeps_them():
    config = cfg.MemoryMapConfig(regions=[
        cfg.ExecRegion("OLD_DATA", "GMU", "GMU_NORMAL", "data", 1, 64, required=True, origin="required")])
    result = rg.required_regions([_need("NEW_DATA", [COPY])], cores=2)
    gone = rg.merge_required(config, result)
    assert config.region("OLD_DATA") is not None and gone == ["OLD_DATA"]
    assert config.region("OLD_DATA").origin == rg.NO_LONGER_NEEDED


def test_merge_records_the_trimmed_names():
    config = cfg.MemoryMapConfig()
    rg.merge_required(config, rg.required_regions([_need("PRIVATE_DATA_CORE3", [COPY])], cores=2))
    assert config.trimmed == ["PRIVATE_DATA_CORE3"] and config.region("PRIVATE_DATA_CORE3") is None


def test_merge_never_touches_a_user_region():
    config = cfg.MemoryMapConfig(regions=[cfg.ExecRegion("MINE", "GMU", "GMU_NORMAL", "data", 1, 64, origin="user")])
    rg.merge_required(config, rg.required_regions([_need("OTHER", [COPY])], cores=2))
    assert config.region("MINE") is not None and config.region("MINE").origin == "user"


def test_a_user_region_with_the_name_of_a_required_one_is_reported_not_overwritten():
    config = cfg.MemoryMapConfig(regions=[cfg.ExecRegion("CLASH", "GMU", "GMU_NORMAL", "data", 1, 64, origin="user")])
    result = rg.required_regions([_need("CLASH", [COPY])], cores=2)
    clashes = rg.merge_required(config, result)
    assert config.region("CLASH").origin == "user" and config.region("CLASH").required is False
    assert clashes == []                                     # the second list is for regions no longer needed
    assert result.clashed(config) == ["CLASH"]
