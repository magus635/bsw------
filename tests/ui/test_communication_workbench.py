"""Qt UI tests for the 5-tab CommunicationWorkbench and DaVinciMainWindow integration."""

from pathlib import Path
from textwrap import dedent
from unittest.mock import patch

from PySide6.QtCore import QTimer, Qt
from PySide6.QtWidgets import QApplication, QMessageBox

from autosar_configurator.core.communication import CommunicationWorkbenchService
from autosar_configurator.core.validation_engine import ValidationMessage, ValidationSeverity
from autosar_configurator.ui.commands import ReplaceMultipleModulesCommand
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
from autosar_configurator.ui.dialogs.communication_workbench import CommunicationWorkbench
from tests.core.test_communication_service import build_synthetic_comm_project
from tests.ui.test_rte_schm_workbench import _build_project_without_rte


def test_workbench_five_tabs_edits_bit_grid_and_revert(qtbot, tmp_path):
    project, _ = build_synthetic_comm_project(tmp_path)
    wb = CommunicationWorkbench(project)
    qtbot.addWidget(wb)
    wb.show()

    assert wb.tabs.count() == 5
    assert wb.channels_tab.table.rowCount() == 1
    assert wb.messages_tab.table.rowCount() == 2
    assert wb.signals_tab.table.rowCount() == 3
    assert wb.pdur_tab.table.rowCount() == 2
    assert wb.health_ok_label.isVisible() is True

    # Edit MCU_Status_Tx inline in Tab 2
    wb.select_tab(1)
    tx_row = next(
        r for r in range(wb.messages_tab.table.rowCount())
        if wb.messages_tab.table.item(r, 2).text() == "MCU_Status_Tx"
    )
    wb.messages_tab.table.selectRow(tx_row)
    wb.messages_tab.edit_can_id.setText("0x255")
    wb.messages_tab.spin_dlc.setValue(16)
    wb.messages_tab.spin_cycle_ms.setValue(20.0)
    wb.messages_tab.apply_btn.click()

    assert wb.has_edits is True
    assert wb.revert_btn.isEnabled() is True
    after_edit = next(m for m in wb.service.list_message_rows() if m.name == "MCU_Status_Tx")
    assert after_edit.can_id == 0x255
    assert after_edit.canif_dlc == 16
    assert after_edit.cycle_time_ms == 20.0

    # Jump to Tab 3 via "查看信号位图" button and provoke overlap error
    wb.messages_tab.table.selectRow(tx_row)
    wb.messages_tab.signals_btn.click()
    assert wb.tabs.currentWidget() is wb.signals_tab
    assert wb.signals_tab.ipdu_combo.currentData() == "MCU_Status_Tx"

    intel_row = next(
        r for r in range(wb.signals_tab.table.rowCount())
        if wb.signals_tab.table.item(r, 0).text() == "MCU_StatusByte"
    )
    wb.signals_tab.table.selectRow(intel_row)
    wb.signals_tab.spin_bit_pos.setValue(32)  # overlaps MCU_MaxTrq_EST in Byte 4 bits 7..0
    wb.signals_tab.apply_sig_btn.click()

    # Overlap should surface error badge in header & red highlight in 8xN grid
    assert wb.btn_fix_sig_errors.isVisible() is True
    overlap_cell = wb.signals_tab.bit_grid_table.item(4, 0)  # Byte 4, Bit 7
    assert overlap_cell is not None
    assert "⚠️" in overlap_cell.text()

    # Revert restores pre-open state across all tabs
    wb.revert_btn.click()
    assert wb.has_edits is False
    assert wb.health_ok_label.isVisible() is True
    restored = next(m for m in wb.service.list_message_rows() if m.name == "MCU_Status_Tx")
    assert restored.can_id == 0x227
    assert restored.canif_dlc == 8


def test_workbench_pdur_crud_and_dbc_sync_tab(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(QMessageBox, "information", lambda *_a, **_kw: QMessageBox.Ok)
    project, _ = build_synthetic_comm_project(tmp_path)

    dbc_path = tmp_path / "ui_sync.dbc"
    dbc_path.write_text(
        dedent("""\
            VERSION ""
            NS_ :
            BS_:
            BU_: VCU MCU

            BO_ 768 VCU_NewMsg: 8 VCU
             SG_ VCU_TorqueReq : 0|16@1+ (0.5,-500) [-500|500] "Nm" MCU

            BA_DEF_ BO_ "GenMsgCycleTime" INT 0 60000;
            BA_ "GenMsgCycleTime" BO_ 768 10;
        """),
        encoding="utf-8",
    )

    wb = CommunicationWorkbench(project)
    qtbot.addWidget(wb)
    wb.show()

    # Tab 4: add and remove a PduRRoutingPath
    wb.select_tab(3)
    wb.pdur_tab.edit_path_name.setText("Manual_Route_Test")
    wb.pdur_tab.edit_src_pdu.setText("MCU_Status_Tx")
    wb.pdur_tab.edit_dest_pdu.setText("MCU_Status_Tx_CanIf")
    wb.pdur_tab.add_btn.click()
    assert wb.pdur_tab.table.rowCount() == 3

    new_row = next(
        r for r in range(wb.pdur_tab.table.rowCount())
        if wb.pdur_tab.table.item(r, 0).text() == "Manual_Route_Test"
    )
    wb.pdur_tab.table.selectRow(new_row)
    wb.pdur_tab.remove_btn.click()
    assert wb.pdur_tab.table.rowCount() == 2

    # Tab 5: DBC Sync preview & apply
    wb.select_tab(4)
    wb.dbc_tab.edit_dbc_path.setText(str(dbc_path))
    wb.dbc_tab._load_dbc_metadata()
    assert wb.dbc_tab.ecu_combo.currentText() == "MCU"

    wb.dbc_tab.preview_btn.click()
    assert wb.dbc_tab.preview_table.rowCount() == 1
    assert wb.dbc_tab.apply_btn.isEnabled() is True

    wb.dbc_tab.apply_btn.click()
    assert wb.has_edits is True
    assert "报文：3" in wb.header_summary_label.text()
    wb.select_tab(1)
    assert wb.messages_tab.table.rowCount() == 3
    assert any(m.name == "VCU_NewMsg_Rx" for m in wb.service.list_message_rows())


def test_main_window_launch_cancel_rollback_and_undo_redo(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, _ = build_synthetic_comm_project(tmp_path)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    assert win.communication_workbench_action.isEnabled() is True
    assert win.nav_bar.buttons["communication"].isEnabled() is True
    assert win.home_dashboard.tool_comm_btn.isEnabled() is True

    # Cancel rollback leaves modules & undo_stack clean
    wb = CommunicationWorkbench(project)
    qtbot.addWidget(wb)
    wb.show()
    wb.service.update_message_properties("MCU_Status_Tx", "MCU_Status_Tx", can_id="0x444", dlc=12)
    wb.has_edits = True
    wb.reject()
    assert next(m for m in CommunicationWorkbenchService(project).list_message_rows() if m.name == "MCU_Status_Tx").can_id == 0x227

    # Simulate accept from DaVinciMainWindow._launch_communication_workbench -> ReplaceMultipleModulesCommand undo/redo
    def _accept_with_edit(self_dlg):
        self_dlg.service.update_message_properties("MCU_Status_Tx", "MCU_Status_Tx", can_id="0x445", dlc=16)
        self_dlg.has_edits = True
        return 1  # QDialog.Accepted

    with monkeypatch.context() as mp:
        mp.setattr(CommunicationWorkbench, "exec", _accept_with_edit)
        win.home_dashboard.tool_comm_btn.click()

    assert win._has_unsaved_changes is True
    assert win.undo_stack.count() == 1
    assert isinstance(win.undo_stack.command(0), ReplaceMultipleModulesCommand)
    assert next(m for m in CommunicationWorkbenchService(project).list_message_rows() if m.name == "MCU_Status_Tx").can_id == 0x445

    win.undo_stack.undo()
    reverted = next(m for m in CommunicationWorkbenchService(project).list_message_rows() if m.name == "MCU_Status_Tx")
    assert reverted.can_id == 0x227
    assert reverted.canif_dlc == 8

    win.undo_stack.redo()
    redone = next(m for m in CommunicationWorkbenchService(project).list_message_rows() if m.name == "MCU_Status_Tx")
    assert redone.can_id == 0x445
    assert redone.canif_dlc == 16


def test_problems_activation_and_no_comm_modules_prompt(qtbot, tmp_path, monkeypatch):
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, _, _ = _build_project_without_rte(tmp_path)  # contains only Com? Wait: use empty or Com
    # Remove Com so there are zero COMM modules
    project.module_managers.clear()
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    # Clicking nav bar "communication" when no COMM modules shows prompt; Cancel does not open workbench
    def _click_cancel():
        modal = QApplication.activeModalWidget()
        if isinstance(modal, QMessageBox):
            for btn in modal.buttons():
                if btn.text() == "取消":
                    btn.click()
                    return

    QTimer.singleShot(0, _click_cancel)
    with patch("autosar_configurator.ui.dialogs.communication_workbench.CommunicationWorkbench") as mock_cls:
        win.nav_bar.buttons["communication"].click()
    assert not mock_cls.called

    # ProblemsView CommunicationRule routes to matching initial_tab
    msg = ValidationMessage(
        severity=ValidationSeverity.ERROR,
        message="Signal overlap",
        rule_name="CommunicationRule",
        container_path="/Com/ComConfig/Sig",
        details="workbench_tab=2; code=SIGNAL_BIT_OVERLAP",
    )
    with patch.object(win, "_launch_communication_workbench") as launch_mock:
        win.impact_problems_controller._on_problem_activated(msg)
        launch_mock.assert_called_once_with(initial_tab=2)
