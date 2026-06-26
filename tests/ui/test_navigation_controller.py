"""Unit tests for NavigationController (P2-6 phase 3).

Exercise the search-toggle and result-dispatch logic with a stub window — no
QApplication required.
"""
from unittest.mock import MagicMock

from autosar_configurator.ui.controllers.navigation_controller import NavigationController


def test_toggle_search_on_single_module_builds_index():
    win = MagicMock()
    win.current_project = None  # single-module mode
    ctrl = NavigationController(win)

    ctrl.toggle_search(True)

    win.search_widget.show.assert_called_once()
    win.search_widget.build_search_index.assert_called_once()
    win.search_widget.build_project_index.assert_not_called()


def test_toggle_search_on_project_mode_builds_project_index():
    win = MagicMock()
    win.current_project = MagicMock()  # project mode
    ctrl = NavigationController(win)

    ctrl.toggle_search(True)

    win.search_widget.build_project_index.assert_called_once_with(win.current_project)


def test_toggle_search_off_hides_widget():
    win = MagicMock()
    ctrl = NavigationController(win)

    ctrl.toggle_search(False)

    win.search_widget.hide.assert_called_once()
    win.search_widget.build_search_index.assert_not_called()


def test_search_result_dispatches_container_to_navigate_to_container():
    win = MagicMock()
    win.current_project = None
    win.config_manager.module_def.short_name = "Can"
    ctrl = NavigationController(win)

    ctrl._on_search_result_selected("container", "Can/CanConfigSet/CanController")

    # The instance lookup is attempted on the matching manager's configuration.
    win.config_manager.configuration.get_instance_by_path.assert_called_once_with(
        "/Can/CanConfigSet/CanController"
    )


def test_navigate_to_definition_unknown_module_reports_status():
    win = MagicMock()
    win.current_project = None
    win.module_def = None
    ctrl = NavigationController(win)

    ctrl._navigate_to_definition("Nope/SomeContainer")

    # Graceful: a status message is shown, no tree navigation attempted.
    win.statusbar.showMessage.assert_called()
    win.tree_view.select_definition.assert_not_called()


def test_reference_jump_selects_found_container():
    target = object()
    win = MagicMock()
    win.current_project = None
    win.config_manager.configuration.get_instance_by_path.return_value = target
    ctrl = NavigationController(win)

    ctrl._on_reference_jump_requested("/Can/CanConfigSet/CanController")

    win.tree_view.select_container.assert_called_once_with(target)


def test_reference_jump_empty_path_is_noop():
    win = MagicMock()
    ctrl = NavigationController(win)

    ctrl._on_reference_jump_requested("")

    win.tree_view.select_container.assert_not_called()


def test_navigate_to_path_empty_is_noop():
    win = MagicMock()
    ctrl = NavigationController(win)

    ctrl._navigate_to_path("")

    win.tree_view.select_item_by_path.assert_not_called()


def test_search_for_ref_finds_holding_container():
    ref_val = object()
    holder = MagicMock()
    holder.reference_values = {"RefToX": ref_val}
    holder.sub_containers = []
    other = MagicMock()
    other.reference_values = {}
    other.sub_containers = []
    ctrl = NavigationController(MagicMock())

    result = ctrl._search_for_ref_in_containers(ref_val, [other, holder])

    assert result is holder
