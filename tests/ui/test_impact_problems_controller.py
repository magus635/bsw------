"""Unit tests for ImpactProblemsController (P2-6 phase 5).

Exercise the pure-logic helpers (recursive container find, dependency-rule
parsing, navigation dispatch) with a stub window — no QApplication required.
"""
from unittest.mock import MagicMock

from autosar_configurator.ui.controllers.impact_problems_controller import (
    ImpactProblemsController,
)


def _container(name, subs=None):
    c = MagicMock()
    c.short_name = name
    c.sub_containers = subs or []
    return c


def test_find_container_recursive_top_level():
    ctrl = ImpactProblemsController(MagicMock())
    target = _container("Wanted")
    roots = [_container("A"), target, _container("B")]
    assert ctrl._find_container_recursive(roots, "Wanted") is target


def test_find_container_recursive_nested():
    ctrl = ImpactProblemsController(MagicMock())
    deep = _container("Deep")
    roots = [_container("A", subs=[_container("B", subs=[deep])])]
    assert ctrl._find_container_recursive(roots, "Deep") is deep


def test_find_container_recursive_missing_returns_none():
    ctrl = ImpactProblemsController(MagicMock())
    assert ctrl._find_container_recursive([_container("A")], "Nope") is None


def test_load_dependency_rules_confirmed_only(tmp_path):
    md = tmp_path / "dependencies.md"
    md.write_text(
        "| # | Status | Source | Source Param | Cond | Target Param | Req | Reason |\n"
        "| 1 | [x] | CanMod | `Can.A` | != null | `Mcu.B` | exists | confirmed-one |\n"
        "| 2 | [ ] | CanMod | `Can.C` | != null | `Mcu.D` | exists | pending-two |\n",
        encoding="utf-8",
    )
    ctrl = ImpactProblemsController(MagicMock())

    confirmed = ctrl._load_dependency_rules_from_file(md, include_pending=False)
    assert len(confirmed) == 1
    assert confirmed[0]["source_param"] == "Can.A"
    assert confirmed[0]["target_param"] == "Mcu.B"

    both = ctrl._load_dependency_rules_from_file(md, include_pending=True)
    assert len(both) == 2


def test_load_dependency_rules_missing_file_returns_empty(tmp_path):
    ctrl = ImpactProblemsController(MagicMock())
    rules = ctrl._load_dependency_rules_from_file(tmp_path / "nope.md")
    assert rules == []


def test_problems_item_navigates_tree():
    win = MagicMock()
    ctrl = ImpactProblemsController(win)
    ctrl._on_problems_item_requested("/Can/CanConfigSet", "CanBaudrate")
    win.tree_view.select_item_by_path.assert_called_once_with("/Can/CanConfigSet")


def test_problems_item_empty_path_is_noop():
    win = MagicMock()
    ctrl = ImpactProblemsController(win)
    ctrl._on_problems_item_requested("", "x")
    win.tree_view.select_item_by_path.assert_not_called()
