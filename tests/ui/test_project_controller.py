"""Unit tests for ProjectController (P2-6 phase 8).

Exercise the recent-files list management with a stub window (settings + menu
update patched). The bulk of ProjectController is dialog-driven Qt I/O; these
tests cover the pure list logic. The full window construction path is covered
by test_davinci_integration.
"""
from unittest.mock import MagicMock, patch

from autosar_configurator.ui.controllers.project_controller import ProjectController


def _controller_with_recent(initial):
    win = MagicMock()
    win.max_recent_files = 3
    store = {"recent_files": list(initial)}
    win.settings.value.side_effect = lambda key, default=None: store.get(key, default)
    win.settings.setValue.side_effect = lambda key, val: store.__setitem__(key, val)
    ctrl = ProjectController(win)
    return ctrl, win, store


def test_add_to_recent_files_inserts_at_front():
    ctrl, win, store = _controller_with_recent(["b", "c"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._add_to_recent_files("a")
    assert store["recent_files"] == ["a", "b", "c"]


def test_add_to_recent_files_moves_existing_to_front():
    ctrl, win, store = _controller_with_recent(["b", "a", "c"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._add_to_recent_files("a")
    assert store["recent_files"] == ["a", "b", "c"]


def test_add_to_recent_files_respects_max():
    ctrl, win, store = _controller_with_recent(["b", "c", "d"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._add_to_recent_files("a")
    assert store["recent_files"] == ["a", "b", "c"]  # capped at max_recent_files=3


def test_remove_from_recent_files():
    ctrl, win, store = _controller_with_recent(["a", "b", "c"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._remove_from_recent_files("b")
    assert store["recent_files"] == ["a", "c"]


def test_remove_missing_is_noop():
    ctrl, win, store = _controller_with_recent(["a", "b"])
    with patch.object(ctrl, "_update_recent_files_menu") as upd:
        ctrl._remove_from_recent_files("zzz")
    assert store["recent_files"] == ["a", "b"]
    upd.assert_not_called()
