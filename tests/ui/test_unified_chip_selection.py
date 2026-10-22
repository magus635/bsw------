"""update-unified-chip-selection: one way to apply the project's chip; selectors read-only."""
from pathlib import Path
from unittest.mock import MagicMock

import pytest

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.chip_selectors import configured_selector_values
from autosar_configurator.core.model.configuration_model import EcucContainerValue
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType,
)
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.dialogs.project_properties_dialog import (
    ProjectPropertiesDialog,
)
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel

REPO = Path(__file__).resolve().parent.parent.parent
RESOURCE_XDM = REPO / "test_import_project/Def/plugins/Resource_THA6_AS440/config/Resource.xdm"

THA6206 = ChipDefinition(name="THA6206_LFBGA292",
                         selectors={"Resource.ResourceSubderivative": "THA6206_LFBGA292"})
THA6412 = ChipDefinition(name="THA6412_BGA516",
                         selectors={"Resource.ResourceSubderivative": "THA6412_BGA516"})


def _project(tmp_path, chip, resource_value):
    db = ChipDatabase()
    db.register_chip(THA6206)
    db.register_chip(THA6412)
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = chip
    parser = EcucDefParser()
    parser.set_selector_values({})
    project.add_module(parser.parse_module_def_file(RESOURCE_XDM), RESOURCE_XDM)
    project.selected_chip = "THA6206_LFBGA292"
    project.apply_chip_selectors()                 # holder container with the 6206 value
    project.selected_chip = chip
    if resource_value is not None:
        for c in _walk(project.module_managers["Resource"].configuration.containers):
            if "ResourceSubderivative" in c.parameter_values:
                c.parameter_values["ResourceSubderivative"].value = resource_value
    return project


def _walk(containers):
    for c in containers:
        yield c
        yield from _walk(c.sub_containers)


def _value(project):
    return configured_selector_values(project, "Resource.ResourceSubderivative")


def _controller(project):
    win = MagicMock()
    win.current_project = project
    win._has_unsaved_changes = False
    win.chip_constraint_service.current_chip = project.selected_chip
    return ProjectController(win), win


def test_explicit_selection_writes_selectors_and_reloads_constraints(tmp_path):
    project = _project(tmp_path, "THA6206_LFBGA292", "THA6206_LFBGA292")
    ctrl, win = _controller(project)
    result = ctrl.apply_project_chip("THA6412_BGA516", write_selectors=True)
    assert project.selected_chip == "THA6412_BGA516"
    assert _value(project) == ["THA6412_BGA516"]
    assert result.changed == [("Resource.ResourceSubderivative", "THA6206_LFBGA292", "THA6412_BGA516")]
    assert win._has_unsaved_changes is True
    win.chip_constraint_service.set_project.assert_called_with(project)
    win.chip_constraint_service.set_chip.assert_called_once_with("THA6412_BGA516")


def test_open_or_import_keeps_the_configuration(tmp_path):
    project = _project(tmp_path, None, "THA6206_LFBGA292")
    ctrl, _win = _controller(project)
    assert ctrl.apply_project_chip("THA6412_BGA516", write_selectors=False) is None
    assert _value(project) == ["THA6206_LFBGA292"]
    assert len(ctrl.selector_mismatches()) == 1
    assert "Apply Chip Selectors" in ctrl._selector_status()


def test_same_chip_still_refreshes_the_ui(tmp_path):
    project = _project(tmp_path, "THA6412_BGA516", "THA6412_BGA516")
    ctrl, win = _controller(project)
    ctrl.apply_project_chip("THA6412_BGA516", write_selectors=False)
    win.chip_constraint_service.set_chip.assert_not_called()
    win._on_chip_constraints_changed.assert_called_once_with("THA6412_BGA516")


def test_apply_chip_selectors_action_in_project_properties(qtbot, tmp_path):
    project = _project(tmp_path, "THA6412_BGA516", "THA6206_LFBGA292")
    ctrl, _win = _controller(project)
    dialog = ProjectPropertiesDialog(project, None, apply_selectors=ctrl.apply_chip_selectors_now,
                                     selector_mismatches=ctrl.selector_mismatches)
    qtbot.addWidget(dialog)
    assert dialog.apply_selectors_btn.isEnabled()
    assert "THA6206_LFBGA292" in dialog.selector_label.text()

    from unittest.mock import patch
    with patch("autosar_configurator.ui.dialogs.project_properties_dialog.QMessageBox.information"):
        dialog._apply_chip_selectors()
    assert _value(project) == ["THA6412_BGA516"]
    assert not dialog.apply_selectors_btn.isEnabled()
    assert dialog.selector_label.text() == ""


@pytest.fixture
def panel(qtbot):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    return panel


def test_selector_parameter_is_read_only(panel, tmp_path):
    container_def = EcucContainerDef(short_name="ResourceGeneral",
                                     definition_ref="/Resource/ResourceGeneral")
    container_def.parameters["ResourceSubderivative"] = EcucParameterDef(
        short_name="ResourceSubderivative", param_type=EcucParameterType.ENUMERATION,
        definition_ref="/Resource/ResourceGeneral/ResourceSubderivative",
        lower_multiplicity=1, upper_multiplicity=1, literals=["THA6206_LFBGA292", "THA6412_BGA516"])
    container_def.parameters["ResourceOther"] = EcucParameterDef(
        short_name="ResourceOther", param_type=EcucParameterType.INTEGER,
        definition_ref="/Resource/ResourceGeneral/ResourceOther",
        lower_multiplicity=1, upper_multiplicity=1)
    manager = MagicMock()
    manager.module_def.short_name = "Resource"
    db = ChipDatabase()
    db.register_chip(THA6412)
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = "THA6412_BGA516"

    instance = EcucContainerValue(short_name="ResourceGeneral", definition_ref="/Resource/ResourceGeneral")
    panel.show_instance(instance, container_def, manager, project)
    editors = {panel.params_table.item(r, 0).text(): panel.params_table.cellWidget(r, 1)
               for r in range(panel.params_table.rowCount())}
    assert not editors["ResourceSubderivative"].isEnabled()
    assert "Project Properties" in editors["ResourceSubderivative"].toolTip()
    assert editors["ResourceOther"].isEnabled()

    project.selected_chip = None                    # no chip: nothing is locked
    panel.show_instance(instance, container_def, manager, project)
    editors = {panel.params_table.item(r, 0).text(): panel.params_table.cellWidget(r, 1)
               for r in range(panel.params_table.rowCount())}
    assert editors["ResourceSubderivative"].isEnabled()
