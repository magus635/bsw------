"""Qt UI tests for the 4-tab RteSchmWorkbench and DaVinciMainWindow integration."""

from unittest.mock import MagicMock, patch

from PySide6.QtCore import Qt

from autosar_configurator.ui.dialogs.rte_schm_workbench import RteSchmWorkbench
from tests.generator.test_rte_workbench_service import _build_synthetic_project


def test_workbench_four_tabs_populate_and_tab1_syncs(qtbot, tmp_path, monkeypatch):
    project, _, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    assert wb.tabs.count() == 6
    # Tab 1 shows Com (active), CanNm (unloaded), Dcm (unregistered)
    mods = {wb.modules_tab.table.item(r, 0).text(): r for r in range(wb.modules_tab.table.rowCount())}
    assert {"Com", "CanNm", "Dcm"}.issubset(mods)

    changed_hits = []
    wb.config_changed.connect(lambda: changed_hits.append(True))

    # Select unregistered Dcm and add it
    wb.modules_tab.table.selectRow(mods["Dcm"])
    assert wb.modules_tab.add_btn.isEnabled()
    wb.modules_tab.add_btn.click()

    assert changed_hits
    assert wb.service._find_bsw_instance("Dcm") is not None
    # Tab 2 & Tab 4 should now include Dcm / SchM_Dcm.h
    ea_mods = {wb.ea_tab.table.item(r, 0).text() for r in range(wb.ea_tab.table.rowCount())}
    assert "Dcm" in ea_mods
    preview_names = {
        wb.generate_tab.files_table.item(r, 0).text()
        for r in range(wb.generate_tab.files_table.rowCount())
    }
    assert "SchM_Dcm.h" in preview_names

    # Remove unloaded CanNm
    mods2 = {wb.modules_tab.table.item(r, 0).text(): r for r in range(wb.modules_tab.table.rowCount())}
    wb.modules_tab.table.selectRow(mods2["CanNm"])
    assert wb.modules_tab.remove_btn.isEnabled()
    wb.modules_tab.remove_btn.click()
    assert wb.service._find_bsw_instance("CanNm") is None


def test_workbench_tab2_exclusive_area_edit_updates_live_preview(qtbot, tmp_path):
    project, _, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    # Locate COM_EXCLUSIVE_AREA_TX row in Tab 2
    target_row = next(
        r
        for r in range(wb.ea_tab.table.rowCount())
        if wb.ea_tab.table.item(r, 2).text() == "COM_EXCLUSIVE_AREA_TX"
    )
    mech_combo = wb.ea_tab.table.cellWidget(target_row, 4)
    mech_combo.setCurrentIndex(mech_combo.findData("OS_RESOURCE"))

    # After reload, select OsResource_Can in column 5
    target_row2 = next(
        r
        for r in range(wb.ea_tab.table.rowCount())
        if wb.ea_tab.table.item(r, 2).text() == "COM_EXCLUSIVE_AREA_TX"
    )
    res_combo = wb.ea_tab.table.cellWidget(target_row2, 5)
    assert res_combo.isEnabled()
    res_combo.setCurrentIndex(res_combo.findData("OsResource_Can"))

    # Verify SchM_Com.h live preview in Tab 4 updated immediately
    schm_row = next(
        r
        for r in range(wb.generate_tab.files_table.rowCount())
        if wb.generate_tab.files_table.item(r, 0).text() == "SchM_Com.h"
    )
    wb.generate_tab.files_table.selectRow(schm_row)
    assert "GetResource(OsResource_Can)" in wb.generate_tab.preview_edit.toPlainText()


def test_workbench_tab3_map_reorder_and_unmap(qtbot, tmp_path):
    project, _, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    assert wb.task_tab.unmapped_table.rowCount() == 2
    wb.task_tab.target_task_combo.setCurrentIndex(
        wb.task_tab.target_task_combo.findData("OsTask_10ms")
    )

    # Map both unmapped events
    for _ in range(2):
        wb.task_tab.unmapped_table.selectRow(0)
        assert wb.task_tab.map_btn.isEnabled()
        wb.task_tab.map_btn.click()

    assert wb.task_tab.unmapped_table.rowCount() == 0

    # Find Com_MainFunctionTxTimingEvent0 in tree and move up
    root_10ms = next(
        wb.task_tab.mapped_tree.topLevelItem(i)
        for i in range(wb.task_tab.mapped_tree.topLevelItemCount())
        if wb.task_tab.mapped_tree.topLevelItem(i).text(0) == "OsTask_10ms"
    )
    tx_child = next(
        root_10ms.child(j)
        for j in range(root_10ms.childCount())
        if root_10ms.child(j).text(0) == "Com_MainFunctionTxTimingEvent0"
    )
    wb.task_tab.mapped_tree.setCurrentItem(tx_child)
    assert wb.task_tab.move_up_btn.isEnabled()
    wb.task_tab.move_up_btn.click()

    mapped, _ = wb.service.list_task_mappings(include_swc=False)
    assert [r.event_name for r in mapped["OsTask_10ms"]] == [
        "Com_MainFunctionTxTimingEvent0",
        "Com_MainFunctionRxTimingEvent0",
    ]

    # Now unmap currently selected TX event
    wb.task_tab.unmap_btn.click()
    assert wb.task_tab.unmapped_table.rowCount() == 1


def test_workbench_tab4_toggle_flag_and_generate_files(qtbot, tmp_path):
    project, proj_dir, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    wb.generate_tab.chk_multi_core.setChecked(True)
    main_row = next(
        r
        for r in range(wb.generate_tab.files_table.rowCount())
        if wb.generate_tab.files_table.item(r, 0).text() == "Rte_Main.h"
    )
    wb.generate_tab.files_table.selectRow(main_row)
    preview_text = wb.generate_tab.preview_edit.toPlainText()
    assert "SchM_StartTimingCore0" in preview_text
    assert "SchM_StartTimingCore1" in preview_text

    completed = []
    wb.generation_completed.connect(lambda rep: completed.append(rep))

    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.QMessageBox") as mock_msg:
        wb.generate_tab.generate_btn.click()

    assert mock_msg.information.called
    assert len(completed) == 1
    assert (proj_dir / "gen" / "Rte" / "include" / "Rte.h").is_file()
    assert (proj_dir / "gen" / "Rte" / "include" / "SchM_Com.h").is_file()


def test_main_window_rte_workbench_action_wiring_and_launch(qtbot, tmp_path, monkeypatch):
    from PySide6.QtWidgets import QMenu, QMessageBox
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)
    win = DaVinciMainWindow()
    qtbot.addWidget(win)

    assert hasattr(win, "rte_workbench_action")
    assert win.rte_workbench_action.isEnabled() is False

    menus = {m.title(): m for m in win.menuBar().findChildren(QMenu)}
    assert win.rte_workbench_action in menus["Generate"].actions()
    assert win.rte_workbench_action in menus["Tools"].actions()

    project, _, _ = _build_synthetic_project(tmp_path)
    win.current_project = project
    win._update_mode_actions()
    assert win.rte_workbench_action.isEnabled() is True

    # Launching with patched RteSchmWorkbench triggers change callback cleanly
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmWorkbench") as mock_cls:
        dlg = mock_cls.return_value
        dlg.exec.side_effect = lambda: win._on_rte_workbench_changed()
        win._launch_rte_schm_workbench()

    assert mock_cls.called
    assert win._has_unsaved_changes is True
    assert win.save_project_action.isEnabled() is True


def test_tab2_inplace_update_custom_mechanism_and_pre_lock_revert(qtbot, tmp_path):
    from autosar_configurator.core.config_manager import PreLockedError
    from PySide6.QtWidgets import QCheckBox

    project, _, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    row_idx = next(
        r
        for r in range(wb.ea_tab.table.rowCount())
        if wb.ea_tab.table.item(r, 2).text() == "COM_EXCLUSIVE_AREA_RX"
    )
    mech_combo = wb.ea_tab.table.cellWidget(row_idx, 4)
    gen_chk = wb.ea_tab.table.cellWidget(row_idx, 6).findChild(QCheckBox)
    orig_combo_id = id(mech_combo)

    # Switching to CUSTOM keeps exact combo instance (in-place update) and locks generate_function=True
    mech_combo.setCurrentIndex(mech_combo.findData("CUSTOM"))
    assert id(wb.ea_tab.table.cellWidget(row_idx, 4)) == orig_combo_id
    assert gen_chk.isChecked() is True
    assert gen_chk.isEnabled() is False

    schm_row = next(
        r
        for r in range(wb.generate_tab.files_table.rowCount())
        if wb.generate_tab.files_table.item(r, 0).text() == "SchM_Com.h"
    )
    wb.generate_tab.files_table.selectRow(schm_row)
    assert "FUNC(void, RTE_CODE) SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX(void);" in wb.generate_tab.preview_edit.toPlainText()

    # Switching back to NONE re-enables gen_chk in place
    mech_combo.setCurrentIndex(mech_combo.findData("NONE"))
    assert id(wb.ea_tab.table.cellWidget(row_idx, 4)) == orig_combo_id
    assert gen_chk.isEnabled() is True

    # Pre-lock error on Tab 4 settings reverts checkbox cleanly with warning
    def _deny_det(instance, name=None):
        if name == "RteDevErrorDetect":
            raise PreLockedError("P:/Rte/Rte/RteGeneration/RteDevErrorDetect")

    project.module_managers["Rte"].check_editable = _deny_det
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.QMessageBox.warning") as warn_mock:
        wb.generate_tab.chk_det.setChecked(True)
    assert warn_mock.called
    assert wb.generate_tab.chk_det.isChecked() is False


def test_workbench_cancel_revert_and_mainwindow_undo_redo_and_new_project(qtbot, tmp_path, monkeypatch):
    from PySide6.QtWidgets import QDialog, QMessageBox
    from autosar_configurator.core.config_manager import ProjectType
    from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    project, _, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    # Modify and revert via Revert button
    mods = {wb.modules_tab.table.item(r, 0).text(): r for r in range(wb.modules_tab.table.rowCount())}
    wb.modules_tab.table.selectRow(mods["CanNm"])
    wb.modules_tab.remove_btn.click()
    assert wb.has_edits is True
    assert wb.revert_btn.isEnabled() is True
    assert wb.service._find_bsw_instance("CanNm") is None

    wb.revert_btn.click()
    assert wb.has_edits is False
    assert wb.revert_btn.isEnabled() is False
    assert wb.service._find_bsw_instance("CanNm") is not None

    # Modify and reject (Cancel) rolls back cleanly
    mods2 = {wb.modules_tab.table.item(r, 0).text(): r for r in range(wb.modules_tab.table.rowCount())}
    wb.modules_tab.table.selectRow(mods2["CanNm"])
    wb.modules_tab.remove_btn.click()
    assert wb.service._find_bsw_instance("CanNm") is None
    wb.reject()
    assert wb.service._find_bsw_instance("CanNm") is not None

    # Full MainWindow Undo/Redo + reference resolution integration
    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    resolve_hits = []
    rev_hits = []
    project.resolve_all_references = lambda force=False: resolve_hits.append(force) or (0, 0)
    project.build_reverse_reference_index = lambda: rev_hits.append(True) or 0
    win.current_project = project
    win._update_mode_actions()

    def _simulate_user_edit_and_accept(self_dlg):
        self_dlg.service.remove_bsw_instance("CanNm")
        self_dlg.has_edits = True
        return QDialog.Accepted

    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmWorkbench.exec", _simulate_user_edit_and_accept):
        win._launch_rte_schm_workbench()

    assert win.undo_stack.count() == 1
    assert win.current_project.module_managers["Rte"].configuration.get_instance_by_path("/Rte/CanNm") is None
    assert True in resolve_hits and True in rev_hits

    win.undo_stack.undo()
    assert any(
        c.short_name == "CanNm"
        for c in win.current_project.module_managers["Rte"].configuration.containers
    )

    # New project enables rte_workbench_action immediately via _update_mode_actions()
    win2 = DaVinciMainWindow()
    qtbot.addWidget(win2)
    win2.workspace_manager = WorkspaceManager()
    db = ChipDatabase()
    db.register_chip(ChipDefinition(name="TestChip", ecu_resources={}))
    proj_folder = tmp_path / "new_proj"
    proj_folder.mkdir()
    with patch("autosar_configurator.ui.wizards.new_project_wizard.NewProjectWizard") as wiz_cls:
        wiz_cls.Accepted = 1
        wiz = wiz_cls.return_value
        wiz.exec.return_value = 1
        wiz.chip_database = db
        wiz.get_result.return_value = {
            "project_name": "demo_new",
            "project_type": ProjectType.VECTOR,
            "folder_path": proj_folder,
            "selected_chip": "TestChip",
        }
        ProjectController(win2).new_project()
    assert win2.rte_workbench_action.isEnabled() is True


def test_p1_health_bar_bilingual_mechanisms_batch_mapping_diff_and_help(qtbot, tmp_path):
    from PySide6.QtCore import QItemSelectionModel
    from PySide6.QtWidgets import QDialog
    from autosar_configurator.ui.dialogs.rte_schm_workbench import RteSchmGuideDialog

    project, _, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    # 1. Top health bar exposes actionable issues initially
    assert not wb.btn_clean_unloaded.isHidden()
    assert not wb.btn_sync_missing_ea.isHidden()
    assert not wb.btn_assign_unmapped.isHidden()
    assert wb.btn_fix_ea_errors.isHidden()
    assert wb.health_ok_label.isHidden()

    # Click unloaded jump -> switches to Tab 1 and selects CanNm -> remove it
    wb.btn_clean_unloaded.click()
    assert wb.tabs.currentWidget() is wb.modules_tab
    sel_mod = wb.modules_tab.table.item(wb.modules_tab.table.currentRow(), 0).text()
    assert sel_mod == "CanNm"
    wb.modules_tab.remove_btn.click()
    assert wb.btn_clean_unloaded.isHidden()

    # Click sync missing EAs -> syncs COM_EXCLUSIVE_AREA_TX and hides sync button
    with patch("autosar_configurator.ui.dialogs.rte_schm_tabs.QMessageBox.information"):
        wb.btn_sync_missing_ea.click()
    assert wb.tabs.currentWidget() is wb.ea_tab
    assert wb.btn_sync_missing_ea.isHidden()

    # 2. Tab 2 bilingual labels preserve canonical enum in userData + health error jump
    rx_row = next(
        r
        for r in range(wb.ea_tab.table.rowCount())
        if wb.ea_tab.table.item(r, 2).text() == "COM_EXCLUSIVE_AREA_RX"
    )
    mech_combo = wb.ea_tab.table.cellWidget(rx_row, 4)
    assert "关全部中断" in mech_combo.currentText()
    assert mech_combo.currentData() == "ALL_INTERRUPT_BLOCKING"

    mech_combo.setCurrentIndex(mech_combo.findData("OS_RESOURCE"))
    assert not wb.btn_fix_ea_errors.isHidden()
    assert wb.btn_goto_generate.isHidden()

    wb.tabs.setCurrentWidget(wb.modules_tab)
    wb.btn_fix_ea_errors.click()
    assert wb.tabs.currentWidget() is wb.ea_tab
    assert wb.ea_tab.only_issues_check.isChecked() is True
    assert wb.ea_tab.table.rowCount() == 1
    res_combo = wb.ea_tab.table.cellWidget(0, 5)
    res_combo.setCurrentIndex(res_combo.findData("OsResource_Can"))
    assert wb.btn_fix_ea_errors.isHidden()
    assert not wb.btn_goto_generate.isHidden()
    wb.ea_tab.only_issues_check.setChecked(False)

    # 3. Tab 3 unmapped jump, period recommendation switch button, and multi-select batch mapping
    wb.btn_assign_unmapped.click()
    assert wb.tabs.currentWidget() is wb.task_tab
    assert wb.task_tab.unmapped_table.rowCount() == 2

    tx_row_idx = next(
        r
        for r in range(wb.task_tab.unmapped_table.rowCount())
        if wb.task_tab.unmapped_table.item(r, 1).text() == "Com_MainFunctionTxTimingEvent0"
    )
    wb.task_tab.target_task_combo.setCurrentIndex(
        wb.task_tab.target_task_combo.findData("OsTask_10ms")
    )
    wb.task_tab.unmapped_table.selectRow(tx_row_idx)
    assert not wb.task_tab.apply_rec_task_btn.isHidden()
    assert "OsTask_20ms" in wb.task_tab.apply_rec_task_btn.text()
    wb.task_tab.apply_rec_task_btn.click()
    assert wb.task_tab.target_task_combo.currentData() == "OsTask_20ms"

    # Switch back to OsTask_10ms and select BOTH unmapped events to test batch mapping + mixed-period badge
    wb.task_tab.target_task_combo.setCurrentIndex(
        wb.task_tab.target_task_combo.findData("OsTask_10ms")
    )
    wb.task_tab.unmapped_table.selectAll()
    assert "批量映射到选中 Task (2 项)" == wb.task_tab.map_btn.text()
    wb.task_tab.map_btn.click()

    assert wb.task_tab.unmapped_table.rowCount() == 0
    assert wb.btn_assign_unmapped.isHidden()
    assert not wb.health_ok_label.isHidden()

    task_10_item = next(
        wb.task_tab.mapped_tree.topLevelItem(i)
        for i in range(wb.task_tab.mapped_tree.topLevelItemCount())
        if wb.task_tab.mapped_tree.topLevelItem(i).text(0) == "OsTask_10ms"
    )
    assert "混合: 10 ms/20 ms" in task_10_item.text(4)

    # 4. Tab 4 Diff toggle (new + updated) and C/Diff highlighter state
    wb.btn_goto_generate.click()
    assert wb.tabs.currentWidget() is wb.generate_tab
    schm_row = next(
        r
        for r in range(wb.generate_tab.files_table.rowCount())
        if wb.generate_tab.files_table.item(r, 0).text() == "SchM_Com.h"
    )
    wb.generate_tab.files_table.selectRow(schm_row)
    wb.generate_tab.chk_diff_mode.setChecked(True)
    assert wb.generate_tab.preview_highlighter._diff_mode is True
    assert "--- /dev/null" in wb.generate_tab.preview_edit.toPlainText()

    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.QMessageBox"):
        wb.generate_tab.generate_btn.click()

    # Edit EA in Tab 2 so SchM_Com.h becomes 'updated' and check unified diff against disk
    wb.tabs.setCurrentWidget(wb.ea_tab)
    tx_ea_row = next(
        r
        for r in range(wb.ea_tab.table.rowCount())
        if wb.ea_tab.table.item(r, 2).text() == "COM_EXCLUSIVE_AREA_TX"
    )
    tx_combo = wb.ea_tab.table.cellWidget(tx_ea_row, 4)
    tx_combo.setCurrentIndex(tx_combo.findData("NONE"))

    wb.tabs.setCurrentWidget(wb.generate_tab)
    schm_row2 = next(
        r
        for r in range(wb.generate_tab.files_table.rowCount())
        if wb.generate_tab.files_table.item(r, 0).text() == "SchM_Com.h"
    )
    wb.generate_tab.files_table.selectRow(schm_row2)
    diff_text = wb.generate_tab.preview_edit.toPlainText()
    assert "--- disk/SchM_Com.h" in diff_text
    assert "+++ generated/SchM_Com.h" in diff_text

    # 5. Built-in guide dialog & help button
    guide = RteSchmGuideDialog(wb)
    qtbot.addWidget(guide)
    assert "RTE / SchM" in guide.browser.toPlainText()
    assert "健康检查" in guide.browser.toPlainText()
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmGuideDialog.exec", return_value=QDialog.Accepted) as help_exec:
        wb.help_btn.click()
    assert help_exec.called


def test_p1_tree_rte_context_menu_and_f1_manual(qtbot, tmp_path, monkeypatch):
    from PySide6.QtWidgets import QMenu, QMessageBox
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
    from autosar_configurator.ui.dialogs.user_manual_dialog import UserManualDialog
    from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView

    project, _, _ = _build_synthetic_project(tmp_path)
    tree = DaVinciTreeView()
    qtbot.addWidget(tree)
    tree.project = project

    hits = []
    tree.open_rte_workbench_requested.connect(lambda: hits.append(True))

    menu_rte = QMenu()
    tree._populate_module_menu(menu_rte, "Rte")
    rte_actions = [a for a in menu_rte.actions() if "RTE / SchM 工作台" in a.text()]
    assert len(rte_actions) == 1
    rte_actions[0].trigger()
    assert hits == [True]

    menu_com = QMenu()
    tree._populate_module_menu(menu_com, "Com")
    com_actions = [a for a in menu_com.actions() if "RTE / SchM 工作台" in a.text()]
    assert com_actions == []

    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    win.current_project = project
    win._update_mode_actions()

    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmWorkbench") as mock_cls:
        dlg = mock_cls.return_value
        dlg.exec.return_value = 0
        win.tree_view.open_rte_workbench_requested.emit()
    assert mock_cls.called

    manual = UserManualDialog()
    qtbot.addWidget(manual)
    manual_text = manual.browser.toPlainText()
    assert "RTE / SchM" in manual_text
    assert "使用说明 (?)" in manual_text


def test_p2_problems_view_jump_stage3_ui_and_memmap_closed_loop(qtbot, tmp_path, monkeypatch):
    from PySide6.QtWidgets import QDialog, QMessageBox
    from autosar_configurator.core.model.configuration_model import EcucContainerValue
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.controllers.validation_controller import ValidationController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    project, proj_dir, _ = _build_synthetic_project(tmp_path)
    os_cfg = project.module_managers["Os"].configuration
    ext_task = EcucContainerValue(short_name="OsTask_Ext", definition_ref="/MICROSAR/Os/OsTask")
    ext_task.set_parameter_value("OsTaskPriority", 30, "/MICROSAR/Os/OsTask/OsTaskPriority")
    ext_task.set_parameter_value("OsTaskType", "EXTENDED", "/MICROSAR/Os/OsTask/OsTaskType")
    os_cfg.add_container(ext_task)

    # Map both Com events (10ms + 20ms) onto EXTENDED task without RteOsInteraction or UsedOsEventRef
    svc = RteSchmWorkbench(project).service
    _, unmapped = svc.list_task_mappings(include_swc=False)
    for ev in unmapped:
        if ev.module_name == "Com":
            svc.map_event_to_task(
                ev.instance_name,
                ev.event_name,
                "OsTask_Ext",
                event_ref=ev.event_ref,
                event_kind=ev.event_kind,
            )

    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    win.current_project = project
    win._update_mode_actions()

    ValidationController(win).validate_configuration()
    rte_msgs = [m for m in win.problems_view.messages if m.rule_name == "RteSchmRule"]
    assert rte_msgs
    tab2_msg = next(m for m in rte_msgs if "workbench_tab=2" in (m.details or ""))

    # Activating/double-clicking an RteSchmRule item launches RteSchmWorkbench directly on that tab
    opened_tabs = []

    def _capture_exec(self_dlg):
        opened_tabs.append(self_dlg.tabs.currentIndex())
        return QDialog.Rejected

    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmWorkbench.exec", _capture_exec):
        win.problems_view.problem_activated.emit(tab2_msg)
    assert opened_tabs == [2]

    # Tab 3 UI displays Stage-3 activation warning and missing UsedOsEventRef badge
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)
    ext_item = next(
        wb.task_tab.mapped_tree.topLevelItem(i)
        for i in range(wb.task_tab.mapped_tree.topLevelItemCount())
        if wb.task_tab.mapped_tree.topLevelItem(i).text(0) == "OsTask_Ext"
    )
    assert "混合: 10 ms/20 ms" in ext_item.text(4)
    assert "缺激活源" in ext_item.text(5)
    assert "缺OsEvent" in ext_item.child(0).text(5)

    # Tab 4 surfaces [阶段3调度告警] without blocking Phase-1 generation
    diag_texts = [wb.generate_tab.diag_list.item(i).text() for i in range(wb.generate_tab.diag_list.count())]
    assert any("[阶段3调度告警]" in txt for txt in diag_texts)
    assert wb.generate_tab.generate_btn.isEnabled() is True

    # Clicking MemMap check before generating headers shows info dialog without opening MemoryMapWorkbench
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.QMessageBox.information") as info_mock, \
         patch("autosar_configurator.ui.dialogs.memory_map_workbench.MemoryMapWorkbench") as mm_cls:
        wb.generate_tab.check_memmap_btn.click()
    assert info_mock.called
    assert not mm_cls.called

    # Generate headers into custom output dir, then verify MemMap check launches MemoryMapWorkbench(auto_scan=True)
    custom_out = tmp_path / "custom_gen"
    wb.generate_tab._custom_output_dir = custom_out
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.QMessageBox"):
        wb.generate_tab.generate_btn.click()

    memmap_dirty = []
    created_dlgs = []
    wb.memmap_settings_changed.connect(lambda: memmap_dirty.append(True))

    def _fake_memmap_ctor(proj, parent=None, *, auto_scan=False):
        dlg = MagicMock()
        dlg._auto_scan = auto_scan
        dlg.source_dirs = MagicMock()
        dlg.settings_changed = MagicMock()

        def _connect(slot):
            dlg._slot = slot

        dlg.settings_changed.connect.side_effect = _connect
        dlg.exec.side_effect = lambda: dlg._slot()
        created_dlgs.append(dlg)
        return dlg

    with patch(
        "autosar_configurator.ui.dialogs.memory_map_workbench.MemoryMapWorkbench",
        side_effect=_fake_memmap_ctor,
    ) as mm_factory:
        wb.generate_tab.check_memmap_btn.click()

    assert mm_factory.called
    assert mm_factory.call_args.kwargs.get("auto_scan") is True
    created_dlgs[0].source_dirs.add.assert_called_once_with(str(custom_out))
    assert memmap_dirty == [True]


def _build_project_without_rte(tmp_path, *, with_davinci_rte_pkg: bool = False):
    from autosar_configurator.core.davinci_importer import SipPackageWriter
    from autosar_configurator.core.packages.library import LibraryRef
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    from tests.generator.test_rte_bootstrap import _minimal_module_def_arxml

    proj_dir = tmp_path / "ui_no_rte_proj"
    proj_dir.mkdir(parents=True, exist_ok=True)
    dpa_path = proj_dir / "NoRte.dpa"

    wm = WorkspaceManager()
    project = wm.create_project("NoRte", dpa_path, format_version=8)
    com_def = tmp_path / "Com_bswmd.arxml"
    com_def.write_bytes(_minimal_module_def_arxml("Com"))
    project.add_custom_module_from_file(com_def)

    if with_davinci_rte_pkg:
        lib_root = proj_dir / "modules" / "davinci"
        SipPackageWriter.write_package(
            module_name="Rte",
            definition_content=_minimal_module_def_arxml("Rte", pkg_prefix="MICROSAR"),
            output_dir=lib_root,
            seed_builtin_templates=False,
        )
        project.module_libraries.append(LibraryRef(path="modules/davinci", kind="package", exclude=[]))

    wm.save_project()
    project.ecu_resources = None
    return project, proj_dir, dpa_path


def test_launch_rte_workbench_missing_rte_initializes_builtin_and_opens(qtbot, tmp_path, monkeypatch):
    from PySide6.QtCore import QTimer
    from PySide6.QtWidgets import QApplication, QMessageBox
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, proj_dir, _ = _build_project_without_rte(tmp_path)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    assert win.home_dashboard.wf_rte_btn.isEnabled() is True
    assert win.home_dashboard.tool_rte_btn.isEnabled() is True
    assert "初始化" in win.home_dashboard.tool_rte_btn.text()

    def _click_builtin():
        modal = QApplication.activeModalWidget()
        if isinstance(modal, QMessageBox):
            for btn in modal.buttons():
                if "初始化内置 Rte" in btn.text():
                    btn.click()
                    return

    QTimer.singleShot(0, _click_builtin)
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmWorkbench") as mock_cls:
        mock_cls.return_value.exec.return_value = 0
        win.nav_bar.buttons["rte_workbench"].click()

    assert mock_cls.called
    assert "Rte" in project.module_managers
    assert (proj_dir / "modules" / "custom" / "Rte" / "module.json").is_file()
    assert win._has_unsaved_changes is True
    assert win.home_dashboard.tool_rte_btn.text() == "⚡ RTE / SchM 工作台"


def test_launch_rte_workbench_missing_rte_cancel_is_noop(qtbot, tmp_path, monkeypatch):
    from PySide6.QtCore import QTimer
    from PySide6.QtWidgets import QApplication, QMessageBox
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, _, _ = _build_project_without_rte(tmp_path)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    def _click_cancel():
        modal = QApplication.activeModalWidget()
        if isinstance(modal, QMessageBox):
            for btn in modal.buttons():
                if btn.text() == "取消":
                    btn.click()
                    return

    QTimer.singleShot(0, _click_cancel)
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmWorkbench") as mock_cls:
        win.nav_bar.buttons["rte_workbench"].click()

    assert not mock_cls.called
    assert "Rte" not in project.module_managers


def test_launch_rte_workbench_missing_rte_activates_library_package(qtbot, tmp_path, monkeypatch):
    from PySide6.QtCore import QTimer
    from PySide6.QtWidgets import QApplication, QMessageBox
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)

    win = DaVinciMainWindow()
    qtbot.addWidget(win)
    project, proj_dir, _ = _build_project_without_rte(tmp_path, with_davinci_rte_pkg=True)
    win.current_project = project
    win.tree_view.set_project(project)
    win._update_mode_actions()

    seen_buttons = []

    def _click_activate():
        modal = QApplication.activeModalWidget()
        if isinstance(modal, QMessageBox):
            seen_buttons.extend(b.text() for b in modal.buttons())
            for btn in modal.buttons():
                if "从模块库激活 Rte" in btn.text():
                    btn.click()
                    return

    QTimer.singleShot(0, _click_activate)
    with patch("autosar_configurator.ui.dialogs.rte_schm_workbench.RteSchmWorkbench") as mock_cls:
        mock_cls.return_value.exec.return_value = 0
        win.nav_bar.buttons["rte_workbench"].click()

    assert any("从模块库激活 Rte" in txt for txt in seen_buttons)
    assert mock_cls.called
    assert "Rte" in project.module_managers
    assert project.module_managers["Rte"].module_def.ar_path == "/MICROSAR/Rte"
    assert not (proj_dir / "modules" / "custom" / "Rte").exists()
