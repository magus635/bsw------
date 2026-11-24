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


def test_module_implementation_config_variant_in_tree_menu_and_not_on_container_panel(qtbot):
    """Module IMPLEMENTATION-CONFIG-VARIANT is controlled at the module level (DaVinciTreeView context menu,
    read-only when single SUPPORTED-CONFIG-VARIANT, switchable with undo/redo when multiple) and not exposed
    on individual container instances in DaVinciConfigPanel."""
    from PySide6.QtGui import QUndoStack
    from PySide6.QtWidgets import QMenu
    from autosar_configurator.ui.commands import SetModuleConfigVariantCommand
    from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView

    project = WorkspaceProject("demo")
    mod_def = _ecuc_def()
    mod_def.supported_config_variants = ["VARIANT-PRE-COMPILE"]
    manager = project.add_module(mod_def, Path("EcuC.arxml"))
    general = manager.create_container_instance(mod_def.containers["EcucGeneral"])

    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    panel.show_instance(general, mod_def.containers["EcucGeneral"], manager, project)
    assert not hasattr(panel, "impl_config_variant_combo")
    assert panel.variant_combo.isHidden() is True
    assert panel.compare_btn.isHidden() is True

    tree = DaVinciTreeView()
    qtbot.addWidget(tree)
    tree.set_project(project)

    # 1. Single SUPPORTED-CONFIG-VARIANT -> menu item is checked but disabled (read-only)
    menu_single = QMenu(tree)
    tree._populate_module_menu(menu_single, "EcuC")
    icv_submenus = [a.menu() for a in menu_single.actions() if a.menu() and "实现配置变体" in a.text()]
    assert len(icv_submenus) == 1
    single_actions = icv_submenus[0].actions()
    assert [a.text() for a in single_actions] == ["VARIANT-PRE-COMPILE"]
    assert single_actions[0].isChecked() is True
    assert single_actions[0].isEnabled() is False

    # 2. Multiple SUPPORTED-CONFIG-VARIANTS -> menu items are enabled and switchable with undo/redo
    mod_def.supported_config_variants = ["VARIANT-PRE-COMPILE", "VARIANT-POST-BUILD"]
    undo_stack = QUndoStack()
    triggered = []
    tree.change_module_config_variant_requested.connect(lambda m, v: triggered.append((m, v)))
    menu_multi = QMenu(tree)
    tree._populate_module_menu(menu_multi, "EcuC")
    icv_submenus_multi = [a.menu() for a in menu_multi.actions() if a.menu() and "实现配置变体" in a.text()]
    sub_actions = icv_submenus_multi[0].actions()
    assert [a.text() for a in sub_actions] == ["VARIANT-PRE-COMPILE", "VARIANT-POST-BUILD"]
    assert all(a.isEnabled() for a in sub_actions)
    sub_actions[1].trigger()
    assert triggered == [("EcuC", "VARIANT-POST-BUILD")]

    cmd = SetModuleConfigVariantCommand(manager, manager.configuration, "VARIANT-POST-BUILD")
    undo_stack.push(cmd)
    assert manager.configuration.implementation_config_variant == "VARIANT-POST-BUILD"
    undo_stack.undo()
    assert manager.configuration.implementation_config_variant == "VARIANT-PRE-COMPILE"
    undo_stack.redo()
    assert manager.configuration.implementation_config_variant == "VARIANT-POST-BUILD"

    # 3. Main window handler updates window title dirty indicator
    from types import SimpleNamespace
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    title_updated = []
    fake_win = SimpleNamespace(
        current_project=project,
        config_manager=manager,
        undo_stack=undo_stack,
        _has_unsaved_changes=False,
        _update_window_title=lambda: title_updated.append(True),
        tree_view=SimpleNamespace(refresh=lambda: None),
        config_panel=None,
        statusbar=SimpleNamespace(showMessage=lambda *_a, **_kw: None),
    )
    DaVinciMainWindow._on_tree_module_config_variant_requested(fake_win, "EcuC", "VARIANT-PRE-COMPILE")
    assert manager.configuration.implementation_config_variant == "VARIANT-PRE-COMPILE"
    assert fake_win._has_unsaved_changes is True
    assert title_updated == [True]


def test_nested_subcontainer_variant_override_isolates_bare_short_name_keys(qtbot):
    """Nested sub-containers with the same short_name as a top-level container must never read
    or delete the top-level container's legacy bare ``<ShortName>.<Param>`` override key."""
    from types import SimpleNamespace
    from PySide6.QtGui import QUndoStack
    from PySide6.QtWidgets import QLineEdit
    from autosar_configurator.core.model.definition_model import EcucReferenceDef
    from autosar_configurator.ui.controllers.edit_controller import EditController

    mod_def = EcucModuleDef(short_name="Can", definition_ref="/MICROSAR/Can")

    top_sub_def = EcucContainerDef(
        short_name="SubItem",
        definition_ref="/MICROSAR/Can/SubItem",
        lower_multiplicity=0,
        upper_multiplicity=1,
    )
    top_sub_def.add_parameter(EcucParameterDef(
        short_name="Mode",
        param_type=EcucParameterType.STRING,
        definition_ref="/MICROSAR/Can/SubItem/Mode",
    ))
    top_sub_def.references["TargetRef"] = EcucReferenceDef(
        short_name="TargetRef",
        definition_ref="/MICROSAR/Can/SubItem/TargetRef",
        destination_ref="/MICROSAR/Can/Target",
    )
    mod_def.add_container(top_sub_def)

    parent_def = EcucContainerDef(
        short_name="ParentBox",
        definition_ref="/MICROSAR/Can/ParentBox",
        lower_multiplicity=0,
        upper_multiplicity=1,
    )
    nested_sub_def = EcucContainerDef(
        short_name="SubItem",
        definition_ref="/MICROSAR/Can/ParentBox/SubItem",
        lower_multiplicity=0,
        upper_multiplicity=1,
    )
    nested_sub_def.add_parameter(EcucParameterDef(
        short_name="Mode",
        param_type=EcucParameterType.STRING,
        definition_ref="/MICROSAR/Can/ParentBox/SubItem/Mode",
    ))
    nested_sub_def.references["TargetRef"] = EcucReferenceDef(
        short_name="TargetRef",
        definition_ref="/MICROSAR/Can/ParentBox/SubItem/TargetRef",
        destination_ref="/MICROSAR/Can/Target",
    )
    parent_def.sub_containers["SubItem"] = nested_sub_def
    mod_def.add_container(parent_def)

    project = WorkspaceProject("demo")
    project.variants = ["Default", "V2"]
    project.active_variant = "V2"
    manager = project.add_module(mod_def, Path("Can.arxml"))
    parent_box = manager.create_container_instance(parent_def)
    nested_sub = manager.create_container_instance(nested_sub_def, parent=parent_box)
    manager.set_parameter_value(nested_sub, "Mode", "NESTED_BASE")

    manager.configuration.variant_overrides = {
        "V2": {
            "SubItem.Mode": "TOP_LEGACY",
            "SubItem.ref:TargetRef": "/Can/TopTarget",
        }
    }

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

    panel.show_instance(nested_sub, nested_sub_def, manager, project)
    mode_row = next(
        r for r in range(panel.params_table.rowCount())
        if panel.params_table.item(r, 0).data(0x0100) == "Mode"
    )
    mode_widget = panel.params_table.cellWidget(mode_row, 1)
    assert isinstance(mode_widget, QLineEdit)
    assert mode_widget.text() == "NESTED_BASE"

    # Comparison must not pick up top-level bare "SubItem.Mode" override
    panel.reference_variant = None
    panel.compare_btn.setChecked(True)
    panel._run_comparison()
    assert "Mode" not in panel.comparison_results

    # Setting then clearing nested Mode/ref must keep top-level bare keys untouched
    panel._on_value_changed("Mode", "NESTED_V2")
    assert manager.configuration.variant_overrides["V2"]["/Can/ParentBox/SubItem.Mode"] == "NESTED_V2"
    assert manager.configuration.variant_overrides["V2"]["SubItem.Mode"] == "TOP_LEGACY"

    panel._on_value_changed("Mode", "(未配置)")
    assert "/Can/ParentBox/SubItem.Mode" not in manager.configuration.variant_overrides["V2"]
    assert manager.configuration.variant_overrides["V2"]["SubItem.Mode"] == "TOP_LEGACY"
    undo_stack.undo()
    assert manager.configuration.variant_overrides["V2"]["/Can/ParentBox/SubItem.Mode"] == "NESTED_V2"
    assert manager.configuration.variant_overrides["V2"]["SubItem.Mode"] == "TOP_LEGACY"
    undo_stack.redo()
    assert manager.configuration.variant_overrides["V2"]["SubItem.Mode"] == "TOP_LEGACY"

    panel._on_reference_changed("TargetRef", None)
    assert manager.configuration.variant_overrides["V2"]["SubItem.ref:TargetRef"] == "/Can/TopTarget"


def test_invalid_variant_override_value_rejected_without_corrupting_overrides_or_undo_stack(qtbot, monkeypatch):
    """Out-of-range integer or invalid enum value in non-Default variant is rejected,
    leaving existing variant_overrides and undo_stack uncorrupted."""
    from types import SimpleNamespace
    from PySide6.QtGui import QUndoStack
    from PySide6.QtWidgets import QMessageBox
    from autosar_configurator.ui.controllers.edit_controller import EditController

    mod_def = _ecuc_def()
    mod_def.containers["EcucGeneral"].add_parameter(EcucParameterDef(
        short_name="MaxChannels",
        param_type=EcucParameterType.INTEGER,
        definition_ref="/MICROSAR/EcuC/EcucGeneral/MaxChannels",
        min_value=1,
        max_value=8,
    ))

    project = WorkspaceProject("demo")
    project.variants = ["Default", "V2"]
    project.active_variant = "V2"
    manager = project.add_module(mod_def, Path("EcuC.arxml"))
    general = manager.create_container_instance(mod_def.containers["EcucGeneral"])

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

    warnings = []
    monkeypatch.setattr(QMessageBox, "warning", lambda *_a, **_kw: warnings.append(_a[2]))

    panel.show_instance(general, mod_def.containers["EcucGeneral"], manager, project)
    panel._on_value_changed("MaxChannels", "4")
    assert manager.configuration.variant_overrides["V2"][f"{general.get_path()}.MaxChannels"] == 4
    assert undo_stack.count() == 1

    panel._on_value_changed("MaxChannels", "99")
    panel._on_value_changed("CPUType", "INVALID_CPU")

    assert len(warnings) == 2
    assert manager.configuration.variant_overrides["V2"][f"{general.get_path()}.MaxChannels"] == 4
    assert f"{general.get_path()}.CPUType" not in manager.configuration.variant_overrides["V2"]
    assert undo_stack.count() == 1


def test_locked_pre_container_blocks_instance_variant_change_in_panel(qtbot):
    """A locked Pre container cannot have instance.variant changed from DaVinciConfigPanel."""
    from autosar_configurator.core.config_manager import PreLockedError

    mod_def = _ecuc_def()
    project = WorkspaceProject("demo")
    project.variants = ["Default", "V2"]
    manager = project.add_module(mod_def, Path("EcuC.arxml"))
    general = manager.create_container_instance(mod_def.containers["EcucGeneral"])

    def _check_editable(inst, name=None):
        if name is None:
            raise PreLockedError("P:/EcuC/EcucGeneral")

    manager.check_editable = _check_editable

    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    panel.show_instance(general, mod_def.containers["EcucGeneral"], manager, project)

    panel._on_instance_variant_changed("V2")
    assert general.variant is None
    assert panel.variant_combo.currentText() == "None (All Variants)"


def test_main_window_variant_selector_stays_hidden_for_single_default_and_reveals_for_multivariant_project(
    qtbot, monkeypatch
):
    """Project variant toolbar controls stay hidden for single-Default projects, auto-reveal
    when a multi-variant (or non-Default active) project is loaded, and sync tree active_variant."""
    from PySide6.QtWidgets import QMessageBox
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    monkeypatch.setattr(ProjectController, "_auto_load_last_project", lambda self: None)
    monkeypatch.setattr(ProjectController, "_load_last_session", lambda self: None)
    monkeypatch.setattr(QMessageBox, "question", lambda *_a, **_kw: QMessageBox.Discard)
    win = DaVinciMainWindow()
    qtbot.addWidget(win)

    proj = WorkspaceProject("single")
    mgr = proj.add_module(_ecuc_def(), Path("EcuC.arxml"))
    mgr.create_container_instance(mgr.module_def.containers["EcucGeneral"])
    win.current_project = proj
    win.tree_view.set_project(proj)
    win._update_variant_selector()

    variant_actions = getattr(win, "_variant_toolbar_actions", None)
    assert variant_actions is not None and len(variant_actions) > 0
    assert all(not act.isVisible() for act in variant_actions)
    assert win.variant_label.isHidden() is True
    assert win.tree_view.active_variant == "Default"

    proj.variants = ["Default", "V2"]
    proj.active_variant = "V2"
    win._update_variant_selector()

    assert all(act.isVisible() for act in variant_actions)
    assert win.variant_label.isHidden() is False
    assert win.variant_selector.currentText() == "V2"
    assert win.tree_view.active_variant == "V2"


def test_main_window_instance_variant_changed_catches_pre_locked_and_rolls_back(qtbot):
    """DaVinciMainWindow._on_instance_variant_changed handles PreLockedError gracefully
    without raising, rolls back instance.variant, and leaves undo stack untouched."""
    from types import SimpleNamespace
    from PySide6.QtGui import QUndoStack
    from autosar_configurator.core.config_manager import PreLockedError
    from autosar_configurator.ui.controllers.edit_controller import EditController
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    mod_def = _ecuc_def()
    project = WorkspaceProject("demo")
    project.variants = ["Default", "V2"]
    manager = project.add_module(mod_def, Path("EcuC.arxml"))
    general = manager.create_container_instance(mod_def.containers["EcucGeneral"])

    def _check_editable(inst, name=None):
        if name is None:
            raise PreLockedError("P:/EcuC/EcucGeneral")

    manager.check_editable = _check_editable

    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    panel.show_instance(general, mod_def.containers["EcucGeneral"], manager, project)
    # Simulate an unguarded caller mutating variant & capturing undo state before main window handler runs
    panel._pending_instance_variant_undo = (general, None, "V2")
    general.variant = "V2"

    messages = []
    undo_stack = QUndoStack()
    fake_win = SimpleNamespace(
        current_project=project,
        config_manager=manager,
        config_panel=panel,
        undo_stack=undo_stack,
        tree_view=SimpleNamespace(refresh=lambda: None),
        statusbar=SimpleNamespace(showMessage=lambda msg, *_a: messages.append(msg)),
        _has_unsaved_changes=False,
        _update_window_title=lambda: None,
    )
    fake_win.edit_controller = EditController(fake_win)

    DaVinciMainWindow._on_instance_variant_changed(fake_win, general)

    assert general.variant is None
    assert undo_stack.count() == 0
    assert fake_win._has_unsaved_changes is False
    assert any("预配置" in m for m in messages)


def test_manage_variants_refreshes_tree_panel_dirty_flag_and_dialog_counts_assigned_containers(
    qtbot, monkeypatch
):
    """VariantManagementDialog reports container.variant counts and ProjectController.manage_variants
    syncs tree active_variant, refreshes/clears config_panel, and marks window dirty on accept."""
    from types import SimpleNamespace
    from PySide6.QtWidgets import QDialog
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.widgets.variant_management_dialog import VariantManagementDialog

    mod_def = _ecuc_def()
    project = WorkspaceProject("demo")
    project.variants = ["Default", "V2"]
    project.active_variant = "V2"
    manager = project.add_module(mod_def, Path("EcuC.arxml"))
    general = manager.create_container_instance(mod_def.containers["EcucGeneral"])
    general.variant = "V2"

    dlg = VariantManagementDialog(project)
    qtbot.addWidget(dlg)
    dlg.list_widget.setCurrentRow(1)
    assert "Total Assigned Containers: 1" in dlg.stats_label.text()
    assert "EcuC" in dlg.stats_label.text()

    events = []

    class _FakeDialog:
        def __init__(self, proj, parent=None):
            self.proj = proj
            self.changed = False

        def exec(self):
            self.proj.variants = ["Default"]
            self.proj.active_variant = "Default"
            self.changed = True
            return QDialog.Accepted

    monkeypatch.setattr(
        "autosar_configurator.ui.widgets.variant_management_dialog.VariantManagementDialog",
        _FakeDialog,
    )

    fake_win = SimpleNamespace(
        current_project=project,
        tree_view=SimpleNamespace(set_active_variant=lambda v: events.append(("tree_active", v))),
        config_panel=SimpleNamespace(
            current_instance=general,
            clear=lambda: events.append(("panel", "clear")),
            refresh=lambda: events.append(("panel", "refresh")),
        ),
        statusbar=SimpleNamespace(showMessage=lambda msg, *_a: events.append(("status", msg))),
        _update_variant_selector=lambda: events.append(("update_selector", True)),
        _update_window_title=lambda: events.append(("update_title", True)),
        _has_unsaved_changes=False,
    )

    ProjectController(fake_win).manage_variants()

    assert ("update_selector", True) in events
    assert ("tree_active", "Default") in events
    assert ("panel", "clear") in events
    assert ("update_title", True) in events
    assert fake_win._has_unsaved_changes is True




