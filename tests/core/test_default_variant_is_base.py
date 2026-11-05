"""The "Default" variant is the base configuration: it has no override layer of its own."""
from pathlib import Path

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.configuration_model import DEFAULT_VARIANT, override_layer
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.core.workspace_manager import WorkspaceManager, WorkspaceProject


def _ecuc_def() -> EcucModuleDef:
    module = EcucModuleDef(short_name="EcuC", definition_ref="/MICROSAR/EcuC")
    general = EcucContainerDef(short_name="EcucGeneral", definition_ref="/MICROSAR/EcuC/EcucGeneral",
                               lower_multiplicity=1, upper_multiplicity=1)
    general.add_parameter(EcucParameterDef(
        short_name="CPUType", param_type=EcucParameterType.ENUMERATION,
        definition_ref="/MICROSAR/EcuC/EcucGeneral/CPUType",
        literals=["CPU8Bit", "CPU16Bit", "CPU32Bit", "CPU64Bit"]))
    general.add_parameter(EcucParameterDef(
        short_name="ByteOrder", param_type=EcucParameterType.ENUMERATION,
        definition_ref="/MICROSAR/EcuC/EcucGeneral/ByteOrder", literals=["BIG_ENDIAN", "LITTLE_ENDIAN"]))
    module.add_container(general)
    return module


def _general(manager: ConfigurationManager):
    return next(c for c in manager.configuration.containers if c.short_name == "EcucGeneral")


def test_default_has_no_override_layer():
    assert DEFAULT_VARIANT == "Default"
    assert override_layer(None) is None
    assert override_layer("") is None
    assert override_layer("Default") is None
    assert override_layer("V2") == "V2"


def test_folding_keeps_the_base_value_and_lists_what_differed():
    project = WorkspaceProject("demo")
    manager = project.add_module(_ecuc_def(), Path("EcuC.arxml"))
    general = manager.create_container_instance(manager.module_def.containers["EcucGeneral"])
    manager.set_parameter_value(general, "CPUType", "CPU32Bit")
    manager.set_parameter_value(general, "ByteOrder", "BIG_ENDIAN")
    cpu, order = f"{general.get_path()}.CPUType", f"{general.get_path()}.ByteOrder"
    gone = "/EcuC/Removed.CPUType"
    manager.configuration.variant_overrides = {
        "Default": {cpu: "CPU32Bit", order: "LITTLE_ENDIAN", gone: "CPU8Bit",
                    "EcucGeneral.ByteOrder": "BIG_ENDIAN"},
        "V2": {cpu: "CPU64Bit"},
    }

    conflicts = project.fold_default_overrides()

    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert general.parameter_values["ByteOrder"].value == "BIG_ENDIAN"
    assert "Default" not in manager.configuration.variant_overrides
    assert manager.configuration.variant_overrides["V2"] == {cpu: "CPU64Bit"}
    assert conflicts == [("EcuC", order, "LITTLE_ENDIAN", "BIG_ENDIAN"), ("EcuC", gone, "CPU8Bit", None)]


def test_loading_a_project_folds_its_default_overrides(tmp_path):
    workspace = WorkspaceManager()
    project = workspace.create_project("demo", tmp_path / "demo.dpa")
    manager = project.add_module(_ecuc_def(), tmp_path / "EcuC_def_not_on_disk.arxml")
    general = manager.create_container_instance(manager.module_def.containers["EcucGeneral"])
    manager.set_parameter_value(general, "ByteOrder", "BIG_ENDIAN")
    order = f"{general.get_path()}.ByteOrder"
    manager.configuration.variant_overrides = {"Default": {order: "LITTLE_ENDIAN"}, "V2": {order: "LITTLE_ENDIAN"}}
    workspace.save_project()

    reopened, failed = WorkspaceManager().load_project(tmp_path / "demo.dpa")

    assert failed == []
    loaded = reopened.module_managers["EcuC"]
    assert _general(loaded).parameter_values["ByteOrder"].value == "BIG_ENDIAN"
    assert "Default" not in loaded.configuration.variant_overrides
    assert loaded.configuration.variant_overrides["V2"] == {order: "LITTLE_ENDIAN"}
    assert reopened.default_override_conflicts == [("EcuC", order, "LITTLE_ENDIAN", "BIG_ENDIAN")]
