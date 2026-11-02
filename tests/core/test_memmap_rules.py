"""Placement rules: matching, priority, the checks before a placement, the statuses, shadowing,
and the rules' own editing (change, add, remove, reorder, factory copy and restore)."""
import copy

import pytest

from autosar_configurator.core.memmap import config as cfg
from autosar_configurator.core.memmap import rules as rl
from autosar_configurator.core.memmap.check import SectionRow
from autosar_configurator.core.memmap.config import ExecRegion, MemoryMapConfig, Rule


def _row(output, kind="BSS", core=None, non_cacheable=False, modules=("CAN",)):
    return SectionRow(output=output, kind=kind, names=(), modules=tuple(modules), core=core,
                      non_cacheable=non_cacheable, uses=())


def _config(rules=(), manual=None):
    return MemoryMapConfig(
        regions=[ExecRegion("PRIVATE_BSS_CORE0", "CPU0BTCM", "CPU0BTCM", "bss", 3),
                 ExecRegion("PRIVATE_DATA_CORE0", "CPU0BTCM", "CPU0BTCM", "data", 2),
                 ExecRegion("UNDEFINE_RAM_BSS", "GMU", "GMU_NORMAL", "bss", 2),
                 ExecRegion("UNDEFINE_RAM_DATA", "GMU", "GMU_NORMAL", "data", 1),
                 ExecRegion("CORE0_USER_STACK", "CPU0BTCM", "CPU0BTCM", "stack", 9),
                 ExecRegion("EX_CODE", "PFLASH0", "PFLASH0_NORMAL", "code", 1)],
        rules=list(rules), manual=dict(manual or {}))


# --- matching ---------------------------------------------------------------------------------

def test_an_empty_match_matches_everything():
    assert rl.matches({}, _row(".x"))


@pytest.mark.parametrize("match, row, expected", [
    ({"kind": ["BSS"]}, _row(".a", "BSS"), True),
    ({"kind": ["BSS"]}, _row(".a", "DATA"), False),
    ({"kind": ["DATA", "BSS"]}, _row(".a", "DATA"), True),
    ({"core": 0}, _row(".a", core=0), True),
    ({"core": 0}, _row(".a", core=1), False),
    ({"core": 0}, _row(".a", core=None), False),
    ({"core": None}, _row(".a", core=None), True),
    ({"core": None}, _row(".a", core=0), False),
    ({"cacheable": False}, _row(".a", non_cacheable=True), True),
    ({"cacheable": False}, _row(".a", non_cacheable=False), False),
    ({"cacheable": True}, _row(".a", non_cacheable=False), True),
    ({"name": "*_core0"}, _row(".mcal_bss_core0"), True),
    ({"name": "*_core0"}, _row(".mcal_bss_core1"), False),
    ({"name": ".mcal_*"}, _row(".MCAL_BSS"), True),            # case does not matter, as in the linker file
    ({"module": "CAN"}, _row(".a", modules=("CAN", "SPI")), True),
    ({"module": "ADC"}, _row(".a", modules=("CAN", "SPI")), False),
])
def test_one_condition(match, row, expected):
    assert rl.matches(match, row) is expected


def test_all_given_conditions_must_hold():
    match = {"kind": ["BSS"], "core": 0, "name": "*_core0"}
    assert rl.matches(match, _row(".x_core0", "BSS", core=0))
    assert not rl.matches(match, _row(".x_core0", "DATA", core=0))
    assert not rl.matches(match, _row(".x_core0", "BSS", core=1))


def test_an_unknown_condition_never_matches_rather_than_everything():
    assert not rl.matches({"colour": "red"}, _row(".a"))


# --- priority and status ---------------------------------------------------------------------------

def test_a_manual_placement_beats_a_rule():
    config = _config([Rule("r", {"kind": ["BSS"]}, "PRIVATE_BSS_CORE0")],
                     {".mcal_bss": "UNDEFINE_RAM_BSS"})
    placed = rl.place(config, _row(".mcal_bss"))
    assert (placed.status, placed.target) == (rl.MANUAL, "UNDEFINE_RAM_BSS")


def test_removing_the_manual_placement_returns_the_section_to_the_rules():
    config = _config([Rule("r", {"kind": ["BSS"]}, "PRIVATE_BSS_CORE0")], {".mcal_bss": "UNDEFINE_RAM_BSS"})
    del config.manual[".mcal_bss"]
    placed = rl.place(config, _row(".mcal_bss"))
    assert (placed.status, placed.target, placed.rule) == (rl.BY_RULE, "PRIVATE_BSS_CORE0", "r")


def test_the_first_matching_rule_wins():
    config = _config([Rule("first", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS"),
                      Rule("second", {"kind": ["BSS"]}, "PRIVATE_BSS_CORE0")])
    assert rl.place(config, _row(".a")).target == "UNDEFINE_RAM_BSS"


def test_no_rule_means_not_placed():
    placed = rl.place(_config(), _row(".a"))
    assert (placed.status, placed.target) == (rl.NOT_PLACED, None)


def test_a_rule_with_a_missing_target_places_nothing_and_the_next_one_is_tried():
    config = _config([Rule("bad", {"kind": ["BSS"]}, "NOWHERE"), Rule("good", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS")])
    assert rl.place(config, _row(".a")).target == "UNDEFINE_RAM_BSS"


def test_a_rule_whose_target_takes_another_kind_is_invalid_for_that_section():
    config = _config([Rule("wrong", {}, "UNDEFINE_RAM_DATA"), Rule("right", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS")])
    assert rl.place(config, _row(".a", "BSS")).target == "UNDEFINE_RAM_BSS"


def test_a_placement_whose_region_is_gone_is_to_be_placed_again_and_is_kept():
    config = _config(manual={".a": "GONE"})
    placed = rl.place(config, _row(".a"))
    assert (placed.status, placed.target) == (rl.AGAIN, "GONE")
    assert config.manual[".a"] == "GONE"


def test_a_manual_placement_of_the_wrong_kind_is_to_be_placed_again():
    config = _config(manual={".a": "UNDEFINE_RAM_DATA"})
    assert rl.place(config, _row(".a", "BSS")).status == rl.AGAIN


def test_every_section_has_exactly_one_status():
    config = _config([Rule("r", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS")], {".m": "GONE"})
    rows = [_row(".a"), _row(".b", "DATA"), _row(".m"), _row(".c", "TEXT")]
    statuses = [rl.place(config, r).status for r in rows]
    assert statuses == [rl.BY_RULE, rl.NOT_PLACED, rl.AGAIN, rl.NOT_PLACED]
    assert set(statuses) <= {rl.BY_RULE, rl.MANUAL, rl.NOT_PLACED, rl.AGAIN}


def test_place_all_is_ordered_by_section_name():
    config = _config([Rule("r", {}, "UNDEFINE_RAM_BSS")])
    placed = rl.place_all(config, [_row(".b"), _row(".a")])
    assert [p.section for p in placed] == [".a", ".b"]


# --- the checks before a placement -------------------------------------------------------------------

def test_a_manual_placement_to_a_region_of_the_right_kind_is_allowed():
    assert rl.check_manual(_config(), _row(".a", "BSS"), "UNDEFINE_RAM_BSS") == ""


def test_a_manual_placement_to_a_missing_region_is_refused():
    assert "没有区域" in rl.check_manual(_config(), _row(".a"), "NOPE")


def test_a_manual_placement_of_text_into_a_bss_region_is_refused_with_the_reason():
    reason = rl.check_manual(_config(), _row(".a", "TEXT"), "UNDEFINE_RAM_BSS")
    assert "TEXT" in reason and "bss" in reason


def test_a_manual_placement_into_a_stack_region_is_refused():
    assert "栈" in rl.check_manual(_config(), _row(".a", "BSS"), "CORE0_USER_STACK")


def test_set_manual_stores_only_a_valid_placement():
    config = _config()
    rl.set_manual(config, _row(".a", "BSS"), "UNDEFINE_RAM_BSS")
    assert config.manual == {".a": "UNDEFINE_RAM_BSS"}
    with pytest.raises(cfg.ConfigError, match="栈"):
        rl.set_manual(config, _row(".b", "BSS"), "CORE0_USER_STACK")
    assert ".b" not in config.manual


def test_clear_manual():
    config = _config(manual={".a": "UNDEFINE_RAM_BSS"})
    rl.clear_manual(config, ".a")
    rl.clear_manual(config, ".never")                     # nothing to remove is not an error
    assert config.manual == {}


# --- shadowing and invalid rules ------------------------------------------------------------------------

def test_a_rule_that_matches_only_what_an_earlier_rule_takes_is_shadowed():
    config = _config([Rule("all bss", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS"),
                      Rule("core 0 bss", {"kind": ["BSS"], "core": 0}, "PRIVATE_BSS_CORE0")])
    rows = [_row(".a", core=0), _row(".b")]
    info = rl.rule_info(config, rows)
    assert info["core 0 bss"].shadowed and not info["all bss"].shadowed
    assert info["all bss"].matched == 2


def test_moving_the_specific_rule_first_unshadows_it():
    config = _config([Rule("core 0 bss", {"kind": ["BSS"], "core": 0}, "PRIVATE_BSS_CORE0"),
                      Rule("all bss", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS")])
    info = rl.rule_info(config, [_row(".a", core=0), _row(".b")])
    assert not info["core 0 bss"].shadowed and info["core 0 bss"].matched == 1 and info["all bss"].matched == 1


def test_a_rule_naming_a_missing_region_is_invalid():
    config = _config([Rule("bad", {}, "NOWHERE")])
    assert rl.rule_info(config, [_row(".a")])["bad"].invalid == "没有区域 NOWHERE"


def test_a_rule_that_matches_nothing_is_not_shadowed_or_invalid():
    config = _config([Rule("none", {"core": 9}, "UNDEFINE_RAM_BSS")])
    info = rl.rule_info(config, [_row(".a")])["none"]
    assert (info.matched, info.shadowed, info.invalid) == (0, False, "")


# --- editing the rules ---------------------------------------------------------------------------------------

def _factory():
    return [Rule("核私有 BSS", {"kind": ["BSS"], "core": 0}, "PRIVATE_BSS_CORE0", origin=cfg.FACTORY, note="n1"),
            Rule("其余 BSS", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS", origin=cfg.FACTORY, note="n2")]


def test_changing_a_factory_rule_marks_it_changed_and_keeps_the_original():
    config = _config(_factory())
    rl.change_rule(config, "其余 BSS", target="PRIVATE_BSS_CORE0")
    rule = config.rules[1]
    assert rule.changed and rule.target == "PRIVATE_BSS_CORE0"
    assert rule.original == {"match": {"kind": ["BSS"]}, "target": "UNDEFINE_RAM_BSS"}


def test_changing_it_again_keeps_the_first_original():
    config = _config(_factory())
    rl.change_rule(config, "其余 BSS", target="PRIVATE_BSS_CORE0")
    rl.change_rule(config, "其余 BSS", match={"kind": ["BSS"], "core": 1})
    assert config.rules[1].original["target"] == "UNDEFINE_RAM_BSS"


def test_changing_it_back_to_the_original_clears_the_mark():
    config = _config(_factory())
    rl.change_rule(config, "其余 BSS", target="PRIVATE_BSS_CORE0")
    rl.change_rule(config, "其余 BSS", target="UNDEFINE_RAM_BSS")
    assert not config.rules[1].changed


def test_changing_a_users_own_rule_marks_nothing():
    config = _config([Rule("mine", {}, "UNDEFINE_RAM_BSS", origin=cfg.USER)])
    rl.change_rule(config, "mine", target="PRIVATE_BSS_CORE0")
    assert not config.rules[0].changed


def test_add_a_rule_at_a_position():
    config = _config(_factory())
    rl.add_rule(config, Rule("mine", {"module": "SPI"}, "UNDEFINE_RAM_BSS"), position=0)
    assert [r.name for r in config.rules] == ["mine", "核私有 BSS", "其余 BSS"]


def test_add_a_rule_at_the_end_by_default():
    config = _config(_factory())
    rl.add_rule(config, Rule("mine", {}, "UNDEFINE_RAM_BSS"))
    assert config.rules[-1].name == "mine" and config.rules[-1].origin == cfg.USER


def test_a_rule_name_must_be_new():
    with pytest.raises(cfg.ConfigError, match="已存在"):
        rl.add_rule(_config(_factory()), Rule("其余 BSS", {}, "UNDEFINE_RAM_BSS"))


def test_remove_a_rule():
    config = _config(_factory())
    rl.remove_rule(config, "其余 BSS")
    assert [r.name for r in config.rules] == ["核私有 BSS"]


def test_move_a_rule_changes_the_priority():
    config = _config(_factory() + [Rule("mine", {}, "UNDEFINE_RAM_BSS")])
    rl.move_rule(config, "mine", 0)
    assert [r.name for r in config.rules] == ["mine", "核私有 BSS", "其余 BSS"]
    rl.move_rule(config, "mine", 99)                       # beyond the end: to the end
    assert config.rules[-1].name == "mine"


def test_an_unknown_rule_is_an_error():
    for action in (lambda c: rl.remove_rule(c, "x"), lambda c: rl.change_rule(c, "x", target="y"),
                   lambda c: rl.move_rule(c, "x", 0)):
        with pytest.raises(cfg.ConfigError, match="没有规则"):
            action(_config(_factory()))


# --- factory rules ------------------------------------------------------------------------------------------------

def test_the_factory_rules_are_copied_into_a_configuration_once():
    config = MemoryMapConfig()
    assert rl.install_factory(config, _factory(), version=1) is True
    assert [r.name for r in config.rules] == ["核私有 BSS", "其余 BSS"]
    assert config.options["factory_version"] == 1
    config.rules[0].target = "UNDEFINE_RAM_BSS"
    assert rl.install_factory(config, _factory(), version=1) is False        # not again: the copy is the project's
    assert config.rules[0].target == "UNDEFINE_RAM_BSS"


def test_the_copy_does_not_share_objects_with_the_factory_list():
    factory = _factory()
    config = MemoryMapConfig()
    rl.install_factory(config, factory, version=1)
    config.rules[0].target = "CHANGED"
    assert factory[0].target == "PRIVATE_BSS_CORE0"


def test_a_project_with_its_own_rules_is_not_given_the_factory_ones():
    config = MemoryMapConfig(rules=[Rule("mine", {}, "UNDEFINE_RAM_BSS")])
    assert rl.install_factory(config, _factory(), version=1) is False
    assert [r.name for r in config.rules] == ["mine"]


def test_newer_factory_rules_are_announced_not_applied():
    config = MemoryMapConfig()
    rl.install_factory(config, _factory(), version=1)
    assert rl.factory_update_available(config, version=1) is False
    assert rl.factory_update_available(config, version=2) is True
    assert len(config.rules) == 2                          # nothing changed by asking


def test_restore_previews_what_would_be_lost():
    config = _config(_factory())
    rl.change_rule(config, "其余 BSS", target="PRIVATE_BSS_CORE0")
    rl.add_rule(config, Rule("mine", {}, "UNDEFINE_RAM_BSS"))
    lost = rl.restore_preview(config, _factory())
    assert lost.changed == ["其余 BSS"] and lost.added == ["mine"] and lost.removed == []
    assert len(config.rules) == 3                          # a preview changes nothing


def test_restore_reports_a_removed_factory_rule():
    config = _config(_factory())
    rl.remove_rule(config, "其余 BSS")
    assert rl.restore_preview(config, _factory()).removed == ["其余 BSS"]


def test_an_untouched_copy_loses_nothing():
    lost = rl.restore_preview(_config(_factory()), _factory())
    assert (lost.changed, lost.added, lost.removed) == ([], [], []) and not lost.any


def test_restore_replaces_the_rules_and_leaves_the_manual_placements():
    config = _config(_factory(), {".a": "UNDEFINE_RAM_BSS"})
    rl.add_rule(config, Rule("mine", {}, "UNDEFINE_RAM_BSS"))
    rl.restore_factory(config, _factory())
    assert [r.name for r in config.rules] == ["核私有 BSS", "其余 BSS"]
    assert config.manual == {".a": "UNDEFINE_RAM_BSS"}


def test_restore_gives_back_the_factory_objects_as_copies():
    config = _config()
    factory = _factory()
    rl.restore_factory(config, factory)
    config.rules[0].target = "CHANGED"
    assert factory[0].target == "PRIVATE_BSS_CORE0" and copy.deepcopy(config.rules[1]) == factory[1]
