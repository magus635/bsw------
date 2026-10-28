"""Chip designer: import .properties into ecu_resources, save to YAML, export per module."""
from pathlib import Path
from unittest.mock import MagicMock

from PySide6.QtWidgets import QFileDialog, QMessageBox

from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.core.hardware.ecu_resource_data import flatten_ecu_resources
from autosar_configurator.ui.controllers.generation_controller import (
    GenerationController,
)
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import (
    ChipDefinitionDesignerDialog,
)

FIXTURES = Path(__file__).resolve().parent.parent / "fixtures" / "ecu_resources"
OS_FILE = FIXTURES / "Os_Resource_THA6412.properties"


def _quiet_dialogs(monkeypatch):
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "critical", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Yes)


def test_import_properties_then_save_writes_ecu_resources_to_yaml(qtbot, tmp_path, monkeypatch):
    _quiet_dialogs(monkeypatch)
    db = ChipDatabase(tmp_path)
    dialog = ChipDefinitionDesignerDialog(chip_database=db)
    qtbot.addWidget(dialog)
    dialog.name_edit.setText("MY_CHIP")
    dialog._on_add_pin_clicked()

    monkeypatch.setattr(QFileDialog, "getOpenFileNames",
                        lambda *a, **k: ([str(OS_FILE)], ""))
    dialog._on_import_properties_clicked()
    assert "OsResource.NumOfCores: 4" in dialog.ecu_preview.toPlainText()
    assert "(992 items)" in dialog.ecu_preview.toPlainText()

    dialog._on_save_clicked()
    reloaded = ChipDatabase(tmp_path).get_chip("MY_CHIP")
    flat = flatten_ecu_resources(reloaded.ecu_resources)
    assert flat["OsResource.NumOfCores"] == 4
    assert len(flat["Os.IsrTriggerMethodList"]) == 992


def test_saving_an_edited_chip_keeps_its_ecu_resources(qtbot, tmp_path, monkeypatch):
    _quiet_dialogs(monkeypatch)
    (tmp_path / "CHIP_X.yaml").write_text(
        "name: CHIP_X\nresource_version: 2.0.0\n"
        "ecu_resources:\n  OsResource:\n    NumOfCores: 2\n", encoding="utf-8")
    db = ChipDatabase(tmp_path)
    dialog = ChipDefinitionDesignerDialog(chip_database=db, initial_chip="CHIP_X")
    qtbot.addWidget(dialog)
    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()

    reloaded = ChipDatabase(tmp_path).get_chip("CHIP_X")
    assert reloaded.description == "edited"
    assert reloaded.resource_version == "2.0.1"        # a save of a library chip is a repair
    assert reloaded.ecu_resources == {"OsResource": {"NumOfCores": 2}}


def test_export_writes_one_file_per_module(qtbot, tmp_path, monkeypatch):
    _quiet_dialogs(monkeypatch)
    (tmp_path / "chips").mkdir()
    (tmp_path / "chips" / "CHIP_X.yaml").write_text(
        "name: CHIP_X\necu_resources:\n  OsResource:\n    NumOfCores: 2\n"
        "  Os:\n    Flag: true\n", encoding="utf-8")
    db = ChipDatabase(tmp_path / "chips")
    dialog = ChipDefinitionDesignerDialog(chip_database=db, initial_chip="CHIP_X")
    qtbot.addWidget(dialog)

    out = tmp_path / "out"
    monkeypatch.setattr(QFileDialog, "getExistingDirectory", lambda *a, **k: str(out))
    dialog._on_export_properties_clicked()

    assert sorted(p.name for p in out.iterdir()) == [
        "OsResource_CHIP_X.properties", "Os_CHIP_X.properties"]
    assert "OsResource.NumOfCores: 2" in (out / "OsResource_CHIP_X.properties").read_text(encoding="utf-8")


def test_project_controller_status_reports_missing_keys():
    win = MagicMock()
    report = MagicMock(has_warnings=True, missing={"A.b": ["Os"]}, consistency=["x"])
    win.current_project.diagnose_ecu_resources.return_value = report
    win.current_project.selected_chip = None        # no chip: no "not saved" hint
    text = ProjectController(win)._ecu_resource_status()
    assert "1 missing" in text and "1 warning" in text

    report.has_warnings = False
    assert ProjectController(win)._ecu_resource_status() == ""

    win.current_project = None
    assert ProjectController(win)._ecu_resource_status() == ""


def test_generation_controller_passes_fresh_resources_or_none():
    win = MagicMock()
    win.current_project.load_ecu_resources.return_value = {"Os.A": 1}
    assert GenerationController(win)._project_ecu_resources() == {"Os.A": 1}

    win.current_project.load_ecu_resources.return_value = {}
    assert GenerationController(win)._project_ecu_resources() is None

    win.current_project.load_ecu_resources.side_effect = RuntimeError("boom")
    assert GenerationController(win)._project_ecu_resources() is None

    win.current_project = None
    assert GenerationController(win)._project_ecu_resources() is None


def test_new_project_with_chip_gets_ecu_resources(tmp_path):
    """Wizard -> project: the chip's YAML resources are available without any EB import."""
    from unittest.mock import patch

    from autosar_configurator.core.config_manager import ProjectType
    from autosar_configurator.core.hardware.chip_database import ChipDefinition
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    db = ChipDatabase()
    db.register_chip(ChipDefinition(
        name="THA6412_BGA516", ecu_resources={"OsResource": {"NumOfCores": 4}}))

    folder = tmp_path / "proj"
    folder.mkdir()
    win = MagicMock()
    win.workspace_manager = WorkspaceManager()
    win.chip_constraint_service = None

    with patch("autosar_configurator.ui.wizards.new_project_wizard.NewProjectWizard") as wiz_cls:
        wiz_cls.Accepted = 1
        wizard = wiz_cls.return_value
        wizard.exec.return_value = 1
        wizard.chip_database = db
        wizard.get_result.return_value = {
            "project_name": "demo", "project_type": ProjectType.VECTOR,
            "folder_path": folder, "selected_chip": "THA6412_BGA516",
        }
        ProjectController(win).new_project()

    project = win.current_project
    assert project.selected_chip == "THA6412_BGA516"
    assert project.ecu_resources == {"OsResource.NumOfCores": 4}
    assert (folder / "chips" / "THA6412_BGA516.yaml").is_file()   # the project keeps its own copy


def _props_dialog(qtbot, project):
    from autosar_configurator.ui.dialogs.project_properties_dialog import ProjectPropertiesDialog

    dialog = ProjectPropertiesDialog(project)
    qtbot.addWidget(dialog)
    return dialog


def _library_project(tmp_path, chip="C"):
    from autosar_configurator.core.hardware.chip_database import ChipDefinition
    from autosar_configurator.core.workspace_manager import WorkspaceProject

    db = ChipDatabase()
    db.register_chip(ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    db.register_chip(ChipDefinition(name="D", ecu_resources={"Os": {"A": 2}}))
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = chip
    return project


def test_properties_dialog_lists_library_chips_and_shows_source(qtbot, tmp_path):
    project = _library_project(tmp_path)
    dialog = _props_dialog(qtbot, project)
    assert {dialog.chip_combo.itemData(i) for i in range(dialog.chip_combo.count())} >= {None, "C", "D"}
    assert "chip library" in dialog.chip_source_label.text()
    assert dialog.adopt_chip_btn.isEnabled()
    assert not dialog.update_chip_btn.isEnabled()


def test_properties_dialog_save_chip_to_project_then_update(qtbot, tmp_path, monkeypatch):
    _quiet_dialogs(monkeypatch)
    project = _library_project(tmp_path)
    dialog = _props_dialog(qtbot, project)

    dialog.adopt_chip_btn.click()
    assert (tmp_path / "chips" / "C.yaml").is_file()
    assert "project copy" in dialog.chip_source_label.text()
    assert not dialog.adopt_chip_btn.isEnabled()
    assert dialog.update_chip_btn.isEnabled()

    project.chip_database.get_chip("C").ecu_resources = {"Os": {"A": 5}}
    dialog.update_chip_btn.click()
    assert project.ecu_resources == {"Os.A": 5}


def test_properties_dialog_actions_wait_for_a_pending_chip_change(qtbot, tmp_path):
    project = _library_project(tmp_path)
    dialog = _props_dialog(qtbot, project)
    dialog.chip_combo.setCurrentIndex(dialog.chip_combo.findData("D"))
    assert not dialog.adopt_chip_btn.isEnabled()
    assert "Press OK" in dialog.chip_source_label.text()


def test_status_bar_hints_until_the_chip_is_saved_in_the_project(tmp_path):
    project = _library_project(tmp_path)
    win = MagicMock()
    win.current_project = project
    ctrl = ProjectController(win)
    assert "not saved in the project" in ctrl._ecu_resource_status()
    project.adopt_selected_chip()
    assert "not saved in the project" not in ctrl._ecu_resource_status()
