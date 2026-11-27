"""Qt UI tests for the 5-tab SystemServicesWorkbench and DaVinciMainWindow integration."""

from unittest.mock import patch

from PySide6.QtCore import QTimer
from PySide6.QtWidgets import QApplication, QMessageBox

from autosar_configurator.core.services import SystemServicesWorkbenchService
from autosar_configurator.core.validation_engine import ValidationMessage, ValidationSeverity
from autosar_configurator.ui.commands import ReplaceMultipleModulesCommand
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
from autosar_configurator.ui.dialogs.system_services_workbench import SystemServicesWorkbench
from tests.core.test_system_services_service import build_synthetic_services_project
from tests.ui.test_rte_schm_workbench import _build_project_without_rte


def test_system_services_workbench_five_tabs_edits_and_revert(qtbot, tmp_path):
    project, _ = build_synthetic_services_project(tmp_path)
    wb = SystemServicesWorkbench(project)
    qtbot.addWidget(wb)
    wb.show()

    assert wb.tabs.count() == 5
    assert wb.ecum_tab.init_table.rowCount() == 3
    assert wb.bswm_tab.rules_table.rowCount() == 1
    assert wb.os_tab.cores_table.rowCount() == 2
    assert wb.diag_tab.diag_channels_table.rowCount() == 2
    assert wb.det_cdd_tab.cdd_table.rowCount() >= 2
    assert wb.health_ok_label.isVisible() is True

    # Tab 1: reorder EcuMDriverInitListOne
    wb.select_tab(0)
    custom_row = next(
        r for r in range(wb.ecum_tab.init_table.rowCount())
        if wb.ecum_tab.init_table.item(r, 2).text() == "Custom_Code"
    )
    wb.ecum_tab.init_table.selectRow(custom_row)
    wb.ecum_tab.btn_move_up.click()
    assert wb.has_edits is True
    assert wb.revert_btn.isEnabled() is True

    # Tab 2: edit BswM Rule
    wb.select_tab(1)
    wb.bswm_tab.rules_table.selectRow(0)
    wb.bswm_tab.rule_init_combo.setCurrentText("BSWM_TRUE")
    wb.bswm_tab.rule_apply_btn.click()
    assert wb.service.list_bswm_rules()[0].init_state == "BSWM_TRUE"

    # Tab 3: edit Os Task stack & priority
    wb.select_tab(2)
    t_row = next(
        r for r in range(wb.os_tab.tasks_table.rowCount())
        if wb.os_tab.tasks_table.item(r, 0).text() == "OsTask_10ms_Core0"
    )
    wb.os_tab.tasks_table.selectRow(t_row)
    wb.os_tab.task_stack_spin.setValue(4096)
    wb.os_tab.btn_task_apply.click()
    assert next(t for t in wb.service.list_os_tasks() if t.short_name == "OsTask_10ms_Core0").stack_size == 4096

    # Tab 4: tune CanTp BS & DcmBufferSize
    wb.select_tab(3)
    rx_row = next(
        r for r in range(wb.diag_tab.diag_channels_table.rowCount())
        if wb.diag_tab.diag_channels_table.item(r, 1).text() == "RX"
    )
    wb.diag_tab.diag_channels_table.selectRow(rx_row)
    wb.diag_tab.cantp_bs_spin.setValue(32)
    wb.diag_tab.dcm_buf_spin.setValue(512)
    wb.diag_tab.btn_diag_apply.click()
    rx_ch = next(c for c in wb.service.list_diag_channels() if c.direction == "RX")
    assert rx_ch.bs == 32 and rx_ch.buffer_size == 512

    # Tab 5: batch toggle DET + register CddMotor into EcuM
    wb.select_tab(4)
    wb.det_cdd_tab.btn_det_all_on.click()
    assert all(f.enabled for f in wb.service.list_module_det_flags())
    cdd_row = next(
        r for r in range(wb.det_cdd_tab.cdd_table.rowCount())
        if wb.det_cdd_tab.cdd_table.item(r, 0).text() == "CddMotor"
    )
    wb.det_cdd_tab.cdd_table.selectRow(cdd_row)
    wb.det_cdd_tab.btn_reg_ecum.click()
    assert any(x.module_id == "CddMotor" for x in wb.service.list_ecum_init_items())

    # Revert restores initial snapshot cleanly
    wb.revert_btn.click()
    assert wb.has_edits is False
    assert wb.service.list_bswm_rules()[0].init_state == "BSWM_FALSE"
    assert next(t for t in wb.service.list_os_tasks() if t.short_name == "OsTask_10ms_Core0").stack_size == 1024
    assert next(c for c in wb.service.list_diag_channels() if c.direction == "RX").bs == 8


def test_main_window_launch_cancel_undo_redo_and_problems_routing(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, _ = build_synthetic_services_project(tmp_path)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    assert win.system_services_workbench_action.isEnabled() is True
    assert win.nav_bar.buttons["system_services"].isEnabled() is True
    assert win.home_dashboard.tool_sys_btn.isEnabled() is True

    # Cancel restores snapshot cleanly
    wb = SystemServicesWorkbench(project)
    qtbot.addWidget(wb)
    wb.show()
    wb.service.update_os_task("OsTask_10ms_Core0", priority=88)
    wb.has_edits = True
    wb.reject()
    assert next(t for t in SystemServicesWorkbenchService(project).list_os_tasks() if t.short_name == "OsTask_10ms_Core0").priority == 40

    # Accept pushes single ReplaceMultipleModulesCommand onto undo_stack
    def _accept_with_edits(self_dlg):
        self_dlg.service.update_os_task("OsTask_10ms_Core0", priority=75)
        self_dlg.service.update_cantp_nsdu("CanTpRxNSdu_Phys", bs=24)
        self_dlg.has_edits = True
        return 1

    with monkeypatch.context() as mp:
        mp.setattr(SystemServicesWorkbench, "exec", _accept_with_edits)
        win.home_dashboard.tool_sys_btn.click()

    assert win.undo_stack.count() == 1
    assert isinstance(win.undo_stack.command(0), ReplaceMultipleModulesCommand)
    svc = SystemServicesWorkbenchService(project)
    assert next(t for t in svc.list_os_tasks() if t.short_name == "OsTask_10ms_Core0").priority == 75
    assert next(c for c in svc.list_diag_channels() if c.direction == "RX").bs == 24

    win.undo_stack.undo()
    assert next(t for t in svc.list_os_tasks() if t.short_name == "OsTask_10ms_Core0").priority == 40
    assert next(c for c in svc.list_diag_channels() if c.direction == "RX").bs == 8

    win.undo_stack.redo()
    assert next(t for t in svc.list_os_tasks() if t.short_name == "OsTask_10ms_Core0").priority == 75

    # ProblemsView SystemServicesRule routes straight to matching initial_tab
    msg = ValidationMessage(
        severity=ValidationSeverity.ERROR,
        message="BswM cycle",
        rule_name="SystemServicesRule",
        container_path="/BswM/BswMConfig/BswMArbitration/Rule_Run",
        details="workbench_tab=1; code=BSWM_CYCLE_DETECTED",
    )
    with patch.object(win, "_launch_system_services_workbench") as sys_launch:
        win.impact_problems_controller._on_problem_activated(msg)
        sys_launch.assert_called_once_with(initial_tab=1)

    # Empty project prompt Cancel does not open workbench
    empty_proj, _, _ = _build_project_without_rte(tmp_path)
    empty_proj.module_managers.clear()
    win.current_project = empty_proj
    win.tree_view.set_project(empty_proj)
    win._update_mode_actions()

    def _click_cancel():
        modal = QApplication.activeModalWidget()
        if isinstance(modal, QMessageBox):
            for btn in modal.buttons():
                if btn.text() == "取消":
                    btn.click()
                    return

    QTimer.singleShot(0, _click_cancel)
    with patch("autosar_configurator.ui.dialogs.system_services_workbench.SystemServicesWorkbench") as mock_cls:
        win.nav_bar.buttons["system_services"].click()
    assert not mock_cls.called
