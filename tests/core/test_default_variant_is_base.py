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
    project = workspace.create_project("demo", tmp_path / "demo.dpa", format_version=7)
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


def test_container_variant_persists_through_arxml_and_project_save_load(tmp_path):
    """EcucContainerValue.variant round-trips through ARXML serialization/parsing and project load."""
    workspace = WorkspaceManager()
    project = workspace.create_project("demo", tmp_path / "demo.dpa", format_version=7)
    project.variants = ["Default", "V1", "V2"]
    manager = project.add_module(_ecuc_def(), tmp_path / "EcuC_def_not_on_disk.arxml")
    general = manager.create_container_instance(manager.module_def.containers["EcucGeneral"])
    general.variant = "V2"
    manager.set_parameter_value(general, "ByteOrder", "BIG_ENDIAN")
    workspace.save_project()

    reopened, failed = WorkspaceManager().load_project(tmp_path / "demo.dpa")
    assert failed == []
    loaded_general = _general(reopened.module_managers["EcuC"])
    assert loaded_general.variant == "V2"


def test_eb_template_engine_applies_variant_overrides_and_filters_container_variants():
    """EBTemplateEngine/OverlayEngine applies parameter and reference variant_overrides and filters container.variant."""
    from autosar_configurator.core.model.definition_model import EcucReferenceDef
    from autosar_configurator.generator.eb_template_engine import EBTemplateEngine

    mod_def = _ecuc_def()
    general_def = mod_def.containers["EcucGeneral"]
    general_def.upper_multiplicity = -1
    general_def.add_reference(
        EcucReferenceDef(
            short_name="TargetRef",
            definition_ref="/MICROSAR/EcuC/EcucGeneral/TargetRef",
            destination_ref="/MICROSAR/EcuC/EcucGeneral",
        )
    )

    project = WorkspaceProject("demo")
    project.variants = ["Default", "V1", "V2"]
    mgr = project.add_module(mod_def, Path("EcuC.arxml"))

    inst_all = mgr.create_container_instance(general_def, instance_name="EcucGeneral_All")
    mgr.set_parameter_value(inst_all, "CPUType", "CPU32Bit")
    inst_all.set_reference_value("TargetRef", "/EcuC/EcucGeneral_All", "/MICROSAR/EcuC/EcucGeneral/TargetRef")

    inst_v2 = mgr.create_container_instance(general_def, instance_name="EcucGeneral_OnlyV2")
    inst_v2.variant = "V2"
    mgr.set_parameter_value(inst_v2, "CPUType", "CPU16Bit")

    mgr.configuration.variant_overrides = {
        "V2": {
            f"{inst_all.get_path()}.CPUType": "CPU64Bit",
            f"{inst_all.get_path()}.ref:TargetRef": "/EcuC/EcucGeneral_OnlyV2",
        }
    }

    tpl = (
        '[!LOOP "EcucGeneral/*"!]'
        '[!"node:name(.)"!]:[!"node:value(CPUType)"!]:[!"TargetRef"!];'
        '[!ENDLOOP!]'
        'vname=[!"variant:name()"!];vsize=[!"num:i(variant:size())"!];'
        'v1=[!"variant:exists(\'V1\')"!];v9=[!"variant:exists(\'V9\')"!]'
    )

    out_default = EBTemplateEngine(strict=False).render(
        tpl,
        {
            "module_def": mod_def,
            "configuration": mgr.configuration,
            "module_name": "EcuC",
            "active_variant": "Default",
            "project_variants": project.variants,
        },
    )
    assert "EcucGeneral_All:CPU32Bit:/EcuC/EcucGeneral_All;" in out_default
    assert "EcucGeneral_OnlyV2" not in out_default
    assert "vname=;vsize=3;v1=true;v9=false" in out_default

    out_v2 = EBTemplateEngine(strict=False).render(
        tpl,
        {
            "module_def": mod_def,
            "configuration": mgr.configuration,
            "module_name": "EcuC",
            "active_variant": "V2",
            "project_variants": project.variants,
        },
    )
    assert "EcucGeneral_All:CPU64Bit:/EcuC/EcucGeneral_OnlyV2;" in out_v2
    assert "EcucGeneral_OnlyV2:CPU16Bit:" in out_v2
    assert "vname=V2;vsize=3;v1=true;v9=false" in out_v2

