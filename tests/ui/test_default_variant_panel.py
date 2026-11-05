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
