"""Unit tests for ValidationController (P2-6 phase 7).

Exercise the single-module validation flow and custom-rule loading guards with
a stub window — no QApplication required.
"""
from unittest.mock import MagicMock, patch

from autosar_configurator.ui.controllers.validation_controller import ValidationController


def test_validate_single_module_publishes_results_to_problems_view():
    win = MagicMock()
    win.current_project = None
    # config_manager present so the engine path runs
    win.config_manager = MagicMock()

    fake_result = MagicMock()
    fake_result.is_valid = True
    fake_result.messages = ["m1"]
    engine = MagicMock()
    engine.validate.return_value = fake_result
    ctrl = ValidationController(win)

    with patch(
        "autosar_configurator.core.validation_engine.ValidationEngine",
        return_value=engine,
    ):
        ctrl.validate_configuration()

    win.problems_view.set_messages.assert_called_once_with(fake_result.messages)
    win.problems_dock.show.assert_called_once()


def test_load_custom_rules_guards_without_config_manager():
    win = MagicMock()
    win.config_manager = None
    ctrl = ValidationController(win)

    with patch(
        "autosar_configurator.ui.controllers.validation_controller.QFileDialog"
    ) as fd:
        ctrl.load_custom_rules()
        fd.getOpenFileName.assert_not_called()


def test_load_custom_rules_cancelled_dialog_is_noop():
    win = MagicMock()
    win.config_manager = MagicMock()
    ctrl = ValidationController(win)

    with patch(
        "autosar_configurator.ui.controllers.validation_controller.QFileDialog"
    ) as fd:
        fd.getOpenFileName.return_value = ("", "")  # user cancelled
        ctrl.load_custom_rules()
        win.config_manager.add_custom_rule_file.assert_not_called()


def test_validate_project_re_resolves_references_before_validation():
    """Project-mode validation re-resolves references first so newly added modules clear stale errors."""
    from pathlib import Path
    from autosar_configurator.core.model.configuration_model import EcucReferenceValue
    from autosar_configurator.core.model.definition_model import (
        EcucContainerDef,
        EcucModuleDef,
        EcucReferenceDef,
    )
    from autosar_configurator.core.workspace_manager import WorkspaceProject

    project = WorkspaceProject("ValProject")
    vset_def = EcucModuleDef("vSet", definition_ref="/MICROSAR/vSet")
    init_list_def = EcucContainerDef("vSetBswInitialization", definition_ref="/MICROSAR/vSet/vSetBswInitialization")
    init_fn_def = EcucContainerDef("vSetInitFunction", definition_ref="/MICROSAR/vSet/vSetBswInitialization/vSetInitFunction", upper_multiplicity=-1)
    ref_def = EcucReferenceDef("vSetModuleRef", definition_ref="/MICROSAR/vSet/vSetBswInitialization/vSetInitFunction/vSetModuleRef")
    ref_def.destination_type = "ECUC-FOREIGN-REFERENCE-DEF"
    init_fn_def.references["vSetModuleRef"] = ref_def
    init_list_def.sub_containers["vSetInitFunction"] = init_fn_def
    vset_def.containers["vSetBswInitialization"] = init_list_def

    vset_mgr = project.add_module(vset_def, Path("vSet.arxml"))
    init_list = vset_mgr.create_container_instance(init_list_def, instance_name="vSetBswInitialization")
    init_fn = vset_mgr.create_container_instance(init_fn_def, parent=init_list, instance_name="CanNm_Init")
    init_fn.reference_values["vSetModuleRef"] = EcucReferenceValue(
        definition_ref=ref_def.definition_ref,
        value_ref="/ActiveEcuC/CanNm",
        dest_type="ECUC-FOREIGN-REFERENCE-DEF",
    )

    # Cache MODULE_NOT_LOADED before CanNm exists
    _, errors = project.resolve_all_references()
    assert errors == 1

    # Add CanNm directly on the project (without pre-calling resolve_all_references)
    project.add_module(EcucModuleDef("CanNm", definition_ref="/MICROSAR/CanNm"), Path("CanNm.arxml"))

    win = MagicMock()
    win.current_project = project
    ctrl = ValidationController(win)
    ctrl.validate_configuration()

    messages = win.problems_view.set_messages.call_args[0][0]
    res_errors = [m for m in messages if m.rule_name == "ResolutionError"]
    assert res_errors == []
    win.validation_status_label.setText.assert_called_with("✅ Valid")
    win.config_panel._refresh_reference_status.assert_called_once()
