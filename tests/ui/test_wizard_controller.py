"""Unit tests for WizardController (P2-6 phase 2).

Exercise the controller's guard clauses and tree-selection helper with a stub
window — no QApplication required — showing wizard launch logic is now testable
in isolation from the main window.
"""
from unittest.mock import MagicMock

from PySide6.QtCore import Qt

from autosar_configurator.ui.controllers.wizard_controller import WizardController


def test_launch_guards_when_no_config_manager():
    win = MagicMock()
    win.config_manager = None
    win.module_def = None
    ctrl = WizardController(win)

    # All launchers must no-op (return) without constructing any wizard/Qt object.
    ctrl.launch_quick_config_wizard()
    ctrl.launch_batch_create_wizard()
    ctrl.launch_template_wizard()
    ctrl.launch_import_wizard()
    # tree_view must not be touched on the guarded path.
    win.tree_view.selectedItems.assert_not_called()


def test_get_selected_parent_instance_none_when_empty():
    win = MagicMock()
    win.tree_view.selectedItems.return_value = []
    ctrl = WizardController(win)

    assert ctrl._get_selected_parent_instance() is None


def test_get_selected_parent_instance_reads_value_item():
    instance = object()
    item = MagicMock()
    item.data.return_value = {"type": "VALUE", "instance": instance}
    win = MagicMock()
    win.tree_view.selectedItems.return_value = [item]
    ctrl = WizardController(win)

    assert ctrl._get_selected_parent_instance() is instance
    item.data.assert_called_with(0, Qt.UserRole)


def test_get_selected_parent_instance_reads_parent_for_def_item():
    parent = object()
    item = MagicMock()
    item.data.return_value = {"type": "DEF", "parent_instance": parent}
    win = MagicMock()
    win.tree_view.selectedItems.return_value = [item]
    ctrl = WizardController(win)

    assert ctrl._get_selected_parent_instance() is parent
