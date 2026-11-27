"""Qt UI tests for the DaVinci-style left functional navigation bar and Home dashboard."""

from unittest.mock import patch

from PySide6.QtWidgets import QMessageBox

from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.controllers.validation_controller import ValidationController
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
from tests.generator.test_rte_workbench_service import _build_synthetic_project


def test_startup_defaults_to_home_and_recent_files_render(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    sample_dpa = tmp_path / "RecentDemo.dpa"
    sample_dpa.write_text('{"format_version": 8}', encoding="utf-8")

    opened = []
    monkeypatch.setattr(ProjectController, "_open_recent_file", lambda _self, p: opened.append(p))

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    prev_recent = win.settings.value("recent_files", [])
    try:
        win.settings.setValue("recent_files", [str(sample_dpa)])
        win.project_controller._update_recent_files_menu()

        # Initial page is Home empty state
        assert win.nav_bar.active_page() == "home"
        assert win.workspace_stack.currentWidget() is win.home_dashboard
        assert win.home_dashboard.stack.currentWidget() is win.home_dashboard.empty_page

        # Project-scoped rail buttons disabled initially; Home / Basic Editor / Help enabled
        for pid in ("home", "basic_editor", "help"):
            assert win.nav_bar.buttons[pid].isEnabled() is True
        for aid in (
            "communication",
            "rte_workbench",
            "system_services",
            "memmap",
            "hw_mapping",
            "settings",
            "validate",
            "dep_graph",
            "generate",
        ):
            assert win.nav_bar.buttons[aid].isEnabled() is False

        # View -> Navigation Bar toggles rail visibility cleanly
        assert not win.nav_bar.isHidden()
        win.toggle_nav_bar_action.trigger()
        assert win.nav_bar.isHidden()
        win.toggle_nav_bar_action.trigger()
        assert not win.nav_bar.isHidden()

        # Recent project renders in Home list and clicking dispatches to _open_recent_file
        assert win.home_dashboard.recent_list.count() == 1
        assert "RecentDemo.dpa" in win.home_dashboard.recent_list.item(0).text()
        win.home_dashboard.recent_list.itemClicked.emit(win.home_dashboard.recent_list.item(0))
        assert opened == [str(sample_dpa)]
    finally:
        win.settings.setValue("recent_files", prev_recent)


def _build_tree_ready_project(tmp_path):
    project, proj_dir, rte_cfg = _build_synthetic_project(tmp_path)
    project.ecu_resources = None
    return project, proj_dir, rte_cfg


def test_loading_project_switches_to_basic_editor_and_home_cards_navigate(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)

    project, _, _ = _build_tree_ready_project(tmp_path)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    # A1: opening a project switches automatically to Basic Editor and enables rail tools
    assert win.workspace_stack.currentWidget() is win.basic_editor_page
    assert win.nav_bar.active_page() == "basic_editor"
    for aid in (
        "communication",
        "rte_workbench",
        "system_services",
        "memmap",
        "hw_mapping",
        "validate",
        "dep_graph",
        "generate",
        "settings",
    ):
        assert win.nav_bar.buttons[aid].isEnabled() is True

    # Switching manually to Home stays on Home across repeated _update_mode_actions calls on same project
    win.nav_bar.buttons["home"].click()
    assert win.workspace_stack.currentWidget() is win.home_dashboard
    assert win.nav_bar.active_page() == "home"
    assert win.home_dashboard.stack.currentWidget() is win.home_dashboard.project_page
    assert {"Com", "Dcm", "Os", "Rte"}.issubset(win.home_dashboard.module_buttons.keys())

    win._update_mode_actions()
    assert win.workspace_stack.currentWidget() is win.home_dashboard

    # Clicking module card jumps to Basic Editor and selects that module in tree view
    win.home_dashboard.module_buttons["Com"].click()
    assert win.workspace_stack.currentWidget() is win.basic_editor_page
    assert win.nav_bar.active_page() == "basic_editor"
    assert win.config_manager is project.module_managers["Com"]


def test_nav_bar_actions_validation_badge_and_search_problem_switch(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, _, _ = _build_tree_ready_project(tmp_path)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    # Action rail clicks invoke the underlying workbench / dialog handlers
    with patch.object(win, "_launch_communication_workbench") as comm_launch:
        win.nav_bar.buttons["communication"].click()
        assert comm_launch.called

    with patch.object(win, "_launch_rte_schm_workbench") as rte_launch:
        win.nav_bar.buttons["rte_workbench"].click()
        assert rte_launch.called

    with patch.object(win, "_launch_system_services_workbench") as sys_launch:
        win.nav_bar.buttons["system_services"].click()
        assert sys_launch.called

    with patch.object(win, "_launch_memory_map") as mem_launch:
        win.nav_bar.buttons["memmap"].click()
        assert mem_launch.called

    with patch.object(win, "_show_user_manual") as help_launch:
        win.nav_bar.buttons["help"].click()
        assert help_launch.called

    # Triggering an ExclusiveArea error populates validation badge and Home summary
    from autosar_configurator.core.validation_engine import ValidationSeverity
    from autosar_configurator.generator.rte import RteWorkbenchService

    RteWorkbenchService(project).update_exclusive_area(
        "Com", "COM_EXCLUSIVE_AREA_RX", mechanism="OS_RESOURCE"
    )
    ValidationController(win).validate_configuration()
    err_cnt = sum(1 for m in win.problems_view.messages if m.severity == ValidationSeverity.ERROR)
    assert err_cnt >= 1
    assert any(m.rule_name == "RteSchmRule" and m.severity == ValidationSeverity.ERROR for m in win.problems_view.messages)
    assert win.nav_bar.buttons["validate"].badge() == str(err_cnt)
    assert f"{err_cnt} 个错误" in win.home_dashboard.proj_validation_label.text()

    win.update_validation_badge(0, 2)
    assert win.nav_bar.buttons["validate"].badge() == "2W"
    win.update_validation_badge(0, 0)
    assert win.nav_bar.buttons["validate"].badge() == ""

    # Search toggle and Problems navigation automatically return user from Home to Basic Editor
    win.show_home()
    assert win.workspace_stack.currentWidget() is win.home_dashboard
    win.nav_controller.toggle_search(True)
    assert win.workspace_stack.currentWidget() is win.basic_editor_page

    win.show_home()
    assert win.workspace_stack.currentWidget() is win.home_dashboard
    win.impact_problems_controller._on_problems_item_requested("/Rte/Com", "")
    assert win.workspace_stack.currentWidget() is win.basic_editor_page
