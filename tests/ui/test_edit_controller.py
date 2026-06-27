"""Unit tests for EditController (P2-6 phase 9).

Exercise the pure instance-enumeration helper and the clipboard copy logic with
a stub window — no QApplication required. The full command/undo paths are
covered by tests/ui/test_undo_commands.py.
"""
from unittest.mock import MagicMock

from autosar_configurator.ui.controllers.edit_controller import EditController


def _container(name, subs=None):
    c = MagicMock()
    c.short_name = name
    c.sub_containers = subs or []
    return c


def test_get_all_instances_flattens_tree():
    leaf = _container("Leaf")
    mid = _container("Mid", subs=[leaf])
    root = _container("Root", subs=[mid])
    config = MagicMock()
    config.containers = [root]
    ctrl = EditController(MagicMock())

    result = ctrl._get_all_instances(config)
    names = [c.short_name for c in result]
    assert names == ["Root", "Mid", "Leaf"]


def test_get_all_instances_empty():
    config = MagicMock()
    config.containers = []
    ctrl = EditController(MagicMock())
    assert ctrl._get_all_instances(config) == []


def test_copy_container_sets_clipboard():
    inst = MagicMock()
    inst.short_name = "CanController"
    win = MagicMock()
    win.tree_view.get_selected_instance.return_value = inst
    ctrl = EditController(win)

    ctrl.copy_container()
    assert win.clipboard_instance is inst


def test_copy_container_no_selection_is_noop():
    win = MagicMock()
    win.tree_view.get_selected_instance.return_value = None
    # Pre-set clipboard to a sentinel; copy with no selection must not overwrite it.
    win.clipboard_instance = "sentinel"
    ctrl = EditController(win)

    ctrl.copy_container()
    assert win.clipboard_instance == "sentinel"
