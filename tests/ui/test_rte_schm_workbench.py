"""Qt UI tests for the 4-tab RteSchmWorkbench and DaVinciMainWindow integration."""

from unittest.mock import MagicMock, patch

from PySide6.QtCore import Qt

from autosar_configurator.ui.dialogs.rte_schm_workbench import RteSchmWorkbench
from tests.generator.test_rte_workbench_service import _build_synthetic_project


def test_workbench_four_tabs_populate_and_tab1_syncs(qtbot, tmp_path, monkeypatch):
    project, _, _ = _build_synthetic_project(tmp_path)
    wb = RteSchmWorkbench(project)
    qtbot.addWidget(wb)

    assert wb.tabs.count() == 4
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
