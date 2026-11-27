"""Qt UI tests for the 6-tab RteSchmWorkbench (Phase 2/3 Data Mapping, Service Mapping, SWC Task Mapping)."""

from unittest.mock import patch

from PySide6.QtWidgets import QMessageBox

from autosar_configurator.core.validation_engine import ValidationMessage, ValidationSeverity
from autosar_configurator.generator.rte import RteWorkbenchService
from autosar_configurator.ui.commands import ReplaceModuleContainersCommand
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
from autosar_configurator.ui.dialogs.rte_schm_workbench import RteSchmWorkbench
from tests.generator.test_rte_phase2_phase3 import build_phase23_project


def test_rte_workbench_six_tabs_data_service_mapping_and_live_preview(qtbot, tmp_path):
    project, _, _ = build_phase23_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)
    wb.show()

    assert wb.tabs.count() == 6

    # Tab 4 (index 3): Data Mapping auto-match binds VcuCmd_Rx
    wb.select_tab(3)
    assert wb.data_mapping_tab.table.rowCount() >= 4
    wb.data_mapping_tab.auto_match_btn.click()
    assert wb.has_edits is True
    vcu_row = next(
        r for r in range(wb.data_mapping_tab.table.rowCount())
        if wb.data_mapping_tab.table.item(r, 1).text() == "SigRP_Proto_VcuCmd"
    )
    assert wb.data_mapping_tab.table.item(vcu_row, 6).text() == "VcuCmd_Rx"
    assert "已映射 Com" in wb.data_mapping_tab.table.item(vcu_row, 7).text()

    # Tab 5 (index 4): Service Mapping auto-connect binds UR_CN_CAN00 -> ComM
    wb.select_tab(4)
    assert wb.service_mapping_tab.ports_table.rowCount() >= 2
    assert wb.service_mapping_tab.swc_table.rowCount() == 3
    wb.service_mapping_tab.auto_connect_btn.click()
    comm_row = next(
        r for r in range(wb.service_mapping_tab.ports_table.rowCount())
        if wb.service_mapping_tab.ports_table.item(r, 1).text() == "UR_CN_CAN00"
    )
    assert wb.service_mapping_tab.ports_table.item(comm_row, 4).text() == "ComM"
    assert "已连接" in wb.service_mapping_tab.ports_table.item(comm_row, 7).text()

    # Tab 3 (index 2): opt-in SWC event mapping checkbox maps Init_MotorCtrl
    wb.select_tab(2)
    assert wb.task_tab.edit_swc_check.isChecked() is False
    wb.task_tab.edit_swc_check.setChecked(True)
    init_u_row = next(
        r for r in range(wb.task_tab.unmapped_table.rowCount())
        if wb.task_tab.unmapped_table.item(r, 1).text() == "Init_MotorCtrl"
    )
    wb.task_tab.unmapped_table.selectRow(init_u_row)
    wb.task_tab.target_task_combo.setCurrentIndex(
        wb.task_tab.target_task_combo.findData("OsTask_ApplicationInit_Core0")
    )
    wb.task_tab.map_btn.click()

    # Tab 6 (index 5): live preview includes Phase 2/3 files with newly bound VcuCmd_Rx & ComM call
    wb.select_tab(5)
    assert wb.generate_tab.chk_phase2_3.isChecked() is True
    c0_row = next(
        r for r in range(wb.generate_tab.files_table.rowCount())
        if wb.generate_tab.files_table.item(r, 0).text() == "Rte_SystemApplication_OsCore0.c"
    )
    wb.generate_tab.files_table.selectRow(c0_row)
    preview_txt = wb.generate_tab.preview_edit.toPlainText()
    assert "Com_ReceiveSignal(ComConf_ComSignal_VcuCmd_Rx" in preview_txt
    assert "ComM_RequestComMode(0U, ComMode)" in preview_txt

    # Revert rolls back overlays and ECUC edits atomically
    wb.revert_btn.click()
    assert wb.has_edits is False
    assert project.rte_data_mappings == []
    assert project.rte_service_connectors == []


def test_rte_workbench_phase23_undo_redo_and_problems_tab_routing(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, _, _ = build_phase23_project(tmp_path)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    # Cancel rollback leaves overlays empty & undo_stack untouched
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)
    wb.service.auto_match_data_mappings()
    wb.has_edits = True
    wb.reject()
    assert project.rte_data_mappings == []

    # Accept pushes ReplaceModuleContainersCommand that undoes/redoes overlays + ECUC together
    def _accept_phase23(self_dlg):
        self_dlg.service.auto_match_data_mappings()
        self_dlg.service.auto_connect_service_ports()
        self_dlg.has_edits = True
        return 1

    with monkeypatch.context() as mp:
        mp.setattr(RteSchmWorkbench, "exec", _accept_phase23)
        win.nav_bar.buttons["rte_workbench"].click()

    assert win.undo_stack.count() == 1
    assert isinstance(win.undo_stack.command(0), ReplaceModuleContainersCommand)
    assert len(project.rte_data_mappings) == 1
    assert len(project.rte_service_connectors) == 1

    win.undo_stack.undo()
    assert project.rte_data_mappings == []
    assert project.rte_service_connectors == []

    win.undo_stack.redo()
    assert len(project.rte_data_mappings) == 1
    assert len(project.rte_service_connectors) == 1

    # ProblemsView RteSchmRule routes directly to Tab 3 (Data Mapping) & Tab 4 (Service Mapping)
    for tab_idx, code in ((3, "DATA_MAPPING_DIRECTION_MISMATCH"), (4, "SERVICE_PORT_UNCONNECTED")):
        msg = ValidationMessage(
            severity=ValidationSeverity.ERROR,
            message="Test",
            rule_name="RteSchmRule",
            container_path="/Rte/MotorCtrl",
            details=f"workbench_tab={tab_idx}; code={code}",
        )
        with patch.object(win, "_launch_rte_schm_workbench") as launch_mock:
            win.impact_problems_controller._on_problem_activated(msg)
            launch_mock.assert_called_once_with(initial_tab=tab_idx)
