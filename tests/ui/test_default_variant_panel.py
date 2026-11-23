"""In the parameter panel the "Default" variant is the base configuration; "(未配置)" unsets undoably."""
from pathlib import Path

import pytest
from PySide6.QtWidgets import QComboBox

from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.ui.commands import SetParameterCommand
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel


def _ecuc_def() -> EcucModuleDef:
    module = EcucModuleDef(short_name="EcuC", definition_ref="/MICROSAR/EcuC")
    general = EcucContainerDef(short_name="EcucGeneral", definition_ref="/MICROSAR/EcuC/EcucGeneral",
                               lower_multiplicity=1, upper_multiplicity=1)
    general.add_parameter(EcucParameterDef(
        short_name="CPUType", param_type=EcucParameterType.ENUMERATION,
        definition_ref="/MICROSAR/EcuC/EcucGeneral/CPUType",
        literals=["CPU8Bit", "CPU16Bit", "CPU32Bit", "CPU64Bit"]))
    module.add_container(general)
    return module


@pytest.fixture
def setup(qtbot):
    project = WorkspaceProject("demo")
    manager = project.add_module(_ecuc_def(), Path("EcuC.arxml"))
    general = manager.create_container_instance(manager.module_def.containers["EcucGeneral"])
    manager.set_parameter_value(general, "CPUType", "CPU32Bit")
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    changes = []
    panel.parameter_changed.connect(lambda inst, name, value: changes.append((name, value)))
    return project, manager, general, panel, changes


def _shown(panel, name):
    for row in range(panel.params_table.rowCount()):
        if panel.params_table.item(row, 0).text().endswith(name):
            widget = panel.params_table.cellWidget(row, 1)
            combo = widget if isinstance(widget, QComboBox) else widget.findChild(QComboBox)
            return combo.currentText()


def test_an_edit_in_default_writes_no_override(setup):
    project, manager, general, panel, changes = setup
    project.active_variant = "Default"
    panel.show_instance(general, manager.module_def.containers["EcucGeneral"], manager, project)

    panel._on_value_changed("CPUType", "CPU16Bit")

    assert changes == [("CPUType", "CPU16Bit")]
    assert manager.configuration.variant_overrides.get("Default", {}) == {}


def test_default_shows_the_base_value_and_another_variant_its_override(setup):
    project, manager, general, panel, changes = setup
    path = f"{general.get_path()}.CPUType"
    manager.configuration.variant_overrides = {"Default": {path: "CPU16Bit"}, "V2": {path: "CPU64Bit"}}
    container_def = manager.module_def.containers["EcucGeneral"]

    project.active_variant = "Default"
    panel.show_instance(general, container_def, manager, project)
    assert _shown(panel, "CPUType") == "CPU32Bit"

    project.active_variant = "V2"
    panel.show_instance(general, container_def, manager, project)
    assert _shown(panel, "CPUType") == "CPU64Bit"


def test_unset_is_left_to_the_undoable_command(setup):
    project, manager, general, panel, changes = setup
    project.active_variant = "Default"
    panel.show_instance(general, manager.module_def.containers["EcucGeneral"], manager, project)

    panel._on_value_changed("CPUType", "(未配置)")

    assert changes == [("CPUType", None)]
    assert general.parameter_values["CPUType"].value == "CPU32Bit"     # the command does the removal

    command = SetParameterCommand(manager, general, "CPUType", None)
    command.redo()
    assert "CPUType" not in general.parameter_values
    command.undo()
    assert general.parameter_values["CPUType"].value == "CPU32Bit"


def test_undoing_an_unset_of_an_unset_parameter_sets_nothing(setup):
    project, manager, general, panel, changes = setup
    general.remove_parameter_value("CPUType")

    command = SetParameterCommand(manager, general, "CPUType", None)
    command.redo()
    command.undo()

    assert "CPUType" not in general.parameter_values


def test_editing_in_non_default_variant_preserves_base_and_supports_undo_redo_and_rename_delete(qtbot):
    """Editing in variant V2 via EditController never corrupts Base (Default), supports undo/redo,
    and migrates/cleans up variant_overrides when containers are renamed or deleted."""
    from types import SimpleNamespace
    from PySide6.QtGui import QUndoStack
    from autosar_configurator.ui.commands import DeleteContainerCommand, RenameContainerCommand
    from autosar_configurator.ui.controllers.edit_controller import EditController

    project = WorkspaceProject("demo")
    project.variants = ["Default", "V2"]
    project.active_variant = "V2"
    mod_def = _ecuc_def()
    mod_def.containers["EcucGeneral"].upper_multiplicity = -1
    manager = project.add_module(mod_def, Path("EcuC.arxml"))
    general = manager.create_container_instance(mod_def.containers["EcucGeneral"])
    manager.set_parameter_value(general, "CPUType", "CPU32Bit")

    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    undo_stack = QUndoStack()
    fake_win = SimpleNamespace(
        current_project=project,
        config_manager=manager,
        config_panel=panel,
        undo_stack=undo_stack,
        statusbar=SimpleNamespace(showMessage=lambda *_a, **_kw: None),
        dep_graph_controller=SimpleNamespace(_update_dependency_graph_if_open=lambda: None),
        _has_unsaved_changes=False,
    )
    edit_ctrl = EditController(fake_win)
    panel.parameter_changed.connect(edit_ctrl.handle_parameter_change)

    panel.show_instance(general, mod_def.containers["EcucGeneral"], manager, project)
    panel._on_value_changed("CPUType", "CPU16Bit")

    # Base value must stay CPU32Bit; V2 override becomes CPU16Bit
    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert manager.configuration.variant_overrides["V2"][f"{general.get_path()}.CPUType"] == "CPU16Bit"

    # Undo removes V2 override without touching Base
    undo_stack.undo()
    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert f"{general.get_path()}.CPUType" not in manager.configuration.variant_overrides.get("V2", {})

    # Redo restores V2 override
    undo_stack.redo()
    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert manager.configuration.variant_overrides["V2"][f"{general.get_path()}.CPUType"] == "CPU16Bit"

    # Selecting "(未配置)" in V2 clears the V2 override instead of deleting Base parameter
    panel._on_value_changed("CPUType", "(未配置)")
    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert f"{general.get_path()}.CPUType" not in manager.configuration.variant_overrides.get("V2", {})
    undo_stack.undo()
    assert manager.configuration.variant_overrides["V2"][f"{general.get_path()}.CPUType"] == "CPU16Bit"

    # Renaming the container migrates variant_overrides keys on redo and undo
    orig_path = general.get_path()
    rename_cmd = RenameContainerCommand(manager, general, "EcucGeneral_Renamed")
    undo_stack.push(rename_cmd)
    assert manager.configuration.variant_overrides["V2"] == {
        "/EcuC/EcucGeneral_Renamed.CPUType": "CPU16Bit"
    }
    undo_stack.undo()
    assert manager.configuration.variant_overrides["V2"] == {
        f"{orig_path}.CPUType": "CPU16Bit"
    }

    # Deleting the container removes its variant_overrides keys on redo and restores them on undo
    del_cmd = DeleteContainerCommand(manager, general, None)
    undo_stack.push(del_cmd)
    assert manager.configuration.variant_overrides.get("V2", {}) == {}
    undo_stack.undo()
    assert manager.configuration.variant_overrides["V2"] == {
        f"{orig_path}.CPUType": "CPU16Bit"
    }


def test_variant_management_dialog_protects_default_validates_names_and_cancels_transactionally(qtbot, monkeypatch):
    """VariantManagementDialog protects Default from removal, rejects invalid path characters,
    cleans up container.variant on delete, and rolls back all changes on Cancel (reject)."""
    from PySide6.QtWidgets import QInputDialog, QMessageBox
    from autosar_configurator.ui.widgets.variant_management_dialog import VariantManagementDialog

    project = WorkspaceProject("demo")
    project.variants = ["Default", "V2"]
    project.active_variant = "V2"
    manager = project.add_module(_ecuc_def(), Path("EcuC.arxml"))
    general = manager.create_container_instance(manager.module_def.containers["EcucGeneral"])
    general.variant = "V2"
    manager.configuration.variant_overrides = {"V2": {f"{general.get_path()}.CPUType": "CPU16Bit"}}

    dlg = VariantManagementDialog(project)
    qtbot.addWidget(dlg)

    # Selecting "Default" disables remove_btn and refuses removal
    dlg.list_widget.setCurrentRow(0)
    assert dlg.remove_btn.isEnabled() is False
    warnings = []
    monkeypatch.setattr(QMessageBox, "warning", lambda *_a, **_kw: warnings.append(_a[2]))
    dlg._remove_variant()
    assert "Default" in project.variants

    # Invalid variant name with path separator is rejected
    monkeypatch.setattr(QInputDialog, "getText", lambda *_a, **_kw: ("../Bad/Name", True))
    dlg._add_variant()
    assert "../Bad/Name" not in project.variants

    # Removing V2 cascades to active_variant, variant_overrides, and container.variant
    dlg.list_widget.setCurrentRow(1)
    assert dlg.remove_btn.isEnabled() is True
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Yes)
    dlg._remove_variant()
    assert project.variants == ["Default"]
    assert project.active_variant == "Default"
    assert "V2" not in manager.configuration.variant_overrides
    assert general.variant is None

    # Rejecting (Cancel) restores the entire pre-dialog snapshot
    dlg.reject()
    assert project.variants == ["Default", "V2"]
    assert project.active_variant == "V2"
    assert manager.configuration.variant_overrides == {"V2": {f"{general.get_path()}.CPUType": "CPU16Bit"}}
    assert general.variant == "V2"

