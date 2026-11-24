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


def test_supported_config_variants_parsing_and_direct_child_param_value(tmp_path):
    """EcucDefParser parses SUPPORTED-CONFIG-VARIANTS; ArxmlParser reads direct child <VALUE>
    even when a parameter element also contains a nested <VARIATION-POINT>."""
    from lxml import etree
    from autosar_configurator.core.parser.arxml_parser import ArxmlParser
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

    def_xml = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>Can</SHORT-NAME>
      <SUPPORTED-CONFIG-VARIANTS>
        <SUPPORTED-CONFIG-VARIANT>VARIANT-PRE-COMPILE</SUPPORTED-CONFIG-VARIANT>
        <SUPPORTED-CONFIG-VARIANT>VARIANT-POST-BUILD</SUPPORTED-CONFIG-VARIANT>
      </SUPPORTED-CONFIG-VARIANTS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    def_path = tmp_path / "Can_bswmd.arxml"
    def_path.write_text(def_xml, encoding="utf-8")
    mod_def = EcucDefParser().parse_module_def_file(def_path)
    assert mod_def.supported_config_variants == ["VARIANT-PRE-COMPILE", "VARIANT-POST-BUILD"]

    ecuc_xml = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Can</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Can</DEFINITION-REF>
      <IMPLEMENTATION-CONFIG-VARIANT>VARIANT-POST-BUILD</IMPLEMENTATION-CONFIG-VARIANT>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Can/CanGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <VARIATION-POINT>
                <POST-BUILD-VARIANT-CONDITIONS>
                  <POST-BUILD-VARIANT-CONDITION>
                    <MATCHING-CRITERION-REF DEST="POST-BUILD-VARIANT-CRITERION">/ActiveEcuC/SideCriterion</MATCHING-CRITERION-REF>
                    <VALUE>0</VALUE>
                  </POST-BUILD-VARIANT-CONDITION>
                </POST-BUILD-VARIANT-CONDITIONS>
              </VARIATION-POINT>
              <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/Can/CanGeneral/CanTimeout</DEFINITION-REF>
              <VALUE>100</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <VARIATION-POINT>
                <POST-BUILD-VARIANT-CONDITIONS>
                  <POST-BUILD-VARIANT-CONDITION>
                    <MATCHING-CRITERION-REF DEST="POST-BUILD-VARIANT-CRITERION">/ActiveEcuC/SideCriterion</MATCHING-CRITERION-REF>
                    <VALUE>1</VALUE>
                  </POST-BUILD-VARIANT-CONDITION>
                </POST-BUILD-VARIANT-CONDITIONS>
              </VARIATION-POINT>
              <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/Can/CanGeneral/CanTimeout</DEFINITION-REF>
              <VALUE>200</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE>
              <VARIATION-POINT><SHORT-LABEL>VP_A</SHORT-LABEL></VARIATION-POINT>
              <DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/MICROSAR/Can/CanGeneral/CanClockRef</DEFINITION-REF>
              <VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Mcu/ClockA</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
            <ECUC-REFERENCE-VALUE>
              <VARIATION-POINT><SHORT-LABEL>VP_B</SHORT-LABEL></VARIATION-POINT>
              <DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/MICROSAR/Can/CanGeneral/CanClockRef</DEFINITION-REF>
              <VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Mcu/ClockB</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    root = etree.fromstring(ecuc_xml.encode("utf-8"))
    configs = ArxmlParser().parse_all_module_configurations(root)
    assert len(configs) == 1
    assert configs[0].implementation_config_variant == "VARIANT-POST-BUILD"
    c = configs[0].containers[0]
    assert c.parameter_values["CanTimeout"].value == 100
    assert "CanTimeout" not in c.multi_parameter_values
    assert c.reference_values["CanClockRef"].value_ref == "/ActiveEcuC/Mcu/ClockA"
    assert "CanClockRef" not in c.multi_reference_values
    assert configs[0].variant_overrides == {}


def test_code_generator_forwards_project_variants_and_pulls_configuration_variant_overrides(tmp_path):
    """CodeGenerator forwards project_variants to EB templates and pulls configuration.variant_overrides
    for active variant without requiring explicit variant_overrides in __init__."""
    from autosar_configurator.core.model.definition_model import EcucReferenceDef
    from autosar_configurator.generator.generator import CodeGenerator

    mod_def = EcucModuleDef(short_name="Can", definition_ref="/Vendor/Can")
    general_def = EcucContainerDef(
        short_name="CanGeneral",
        definition_ref="/Vendor/Can/CanGeneral",
        lower_multiplicity=1,
        upper_multiplicity=1,
    )
    general_def.add_parameter(
        EcucParameterDef(
            short_name="CanBaud",
            param_type=EcucParameterType.INTEGER,
            definition_ref="/Vendor/Can/CanGeneral/CanBaud",
            config_class="PRE-COMPILE",
        )
    )
    general_def.add_parameter(
        EcucParameterDef(
            short_name="CanRates",
            param_type=EcucParameterType.INTEGER,
            definition_ref="/Vendor/Can/CanGeneral/CanRates",
            lower_multiplicity=0,
            upper_multiplicity=-1,
        )
    )
    general_def.add_reference(
        EcucReferenceDef(
            short_name="CanClockRef",
            definition_ref="/Vendor/Can/CanGeneral/CanClockRef",
            destination_ref="/Vendor/Mcu/Clk",
        )
    )
    mod_def.add_container(general_def)

    project = WorkspaceProject("demo")
    mgr = project.add_module(mod_def, Path("Can.arxml"))
    general = mgr.create_container_instance(general_def)
    mgr.set_parameter_value(general, "CanBaud", 500)
    general.add_multi_parameter_value("CanRates", 125, "/Vendor/Can/CanGeneral/CanRates", 0)
    general.add_multi_parameter_value("CanRates", 250, "/Vendor/Can/CanGeneral/CanRates", 1)
    general.set_reference_value("CanClockRef", "/Mcu/ClkA", "/Vendor/Can/CanGeneral/CanClockRef")

    mgr.configuration.variant_overrides = {
        "V2": {
            "/Can/CanGeneral.CanBaud": 1000,
            "/Can/CanGeneral.CanRates[1]": 500,
            "/Can/CanGeneral.ref:CanClockRef": "/Mcu/ClkB",
        }
    }

    tpl_dir = tmp_path / "templates" / "Can"
    tpl_dir.mkdir(parents=True)
    (tpl_dir / "Can_Cfg.h.tpl").write_text(
        'baud=[!"num:i(node:value(CanGeneral/CanBaud))"!];'
        'rate1=[!"num:i(node:value(CanGeneral/CanRates/*[2]))"!];'
        'ref=[!"CanGeneral/CanClockRef"!];'
        'vsize=[!"num:i(variant:size())"!];'
        'vc1=[!"variant:check(\'V1\')"!];'
        'vc2=[!"variant:check(\'V2\')"!];'
        'vc9=[!"variant:check(\'V9\')"!]',
        encoding="utf-8",
    )

    gen = CodeGenerator(
        mod_def,
        mgr.configuration,
        project_template_dir=tmp_path / "templates",
        project_variants=["Default", "V1", "V2"],
    )
    out_dir = tmp_path / "out"
    assert gen.generate_all(out_dir, variant="V2") is True
    rendered = (out_dir / "Can" / "V2" / "include" / "Can_Cfg.h").read_text(encoding="utf-8")
    assert "baud=1000;rate1=500;ref=/Mcu/ClkB;vsize=3;vc1=false;vc2=true;vc9=false" in rendered

    ctx_v2 = gen._prepare_context(variant="V2")
    assert ("CanGeneral", "CanBaud", "1000") in ctx_v2["precompile_params"]
    assert ("CanGeneral", "CanClockRef", "/Mcu/ClkB") in ctx_v2["references"]
    assert gen._calculate_fingerprint(variant="V2") != gen._calculate_fingerprint(variant="Default")


def test_overlay_engine_excludes_other_variant_when_none_prevents_phantom_required_and_isolates_nested_short_name():
    """OverlayEngine treats active_variant=None as Default (excluding V2-only instances),
    never synthesizes a phantom default container for required defs hidden by another variant,
    and isolates bare short-name override keys from nested sub-containers."""
    from autosar_configurator.generator.eb_template_engine import EBTemplateEngine

    mod_def = EcucModuleDef(short_name="Can", definition_ref="/Vendor/Can")
    req_def = EcucContainerDef(
        short_name="ReqOnlyV2",
        definition_ref="/Vendor/Can/ReqOnlyV2",
        lower_multiplicity=1,
        upper_multiplicity=1,
    )
    req_def.add_parameter(
        EcucParameterDef(
            short_name="Tag",
            param_type=EcucParameterType.STRING,
            definition_ref="/Vendor/Can/ReqOnlyV2/Tag",
            default_value="GHOST",
        )
    )
    mod_def.add_container(req_def)

    ctrl_def = EcucContainerDef(
        short_name="Ctrl",
        definition_ref="/Vendor/Can/Ctrl",
        lower_multiplicity=0,
        upper_multiplicity=-1,
    )
    filter_def = EcucContainerDef(
        short_name="Filter",
        definition_ref="/Vendor/Can/Ctrl/Filter",
        lower_multiplicity=0,
        upper_multiplicity=1,
    )
    filter_def.add_parameter(
        EcucParameterDef(
            short_name="Mask",
            param_type=EcucParameterType.INTEGER,
            definition_ref="/Vendor/Can/Ctrl/Filter/Mask",
        )
    )
    ctrl_def.add_sub_container(filter_def)
    mod_def.add_container(ctrl_def)

    project = WorkspaceProject("demo")
    mgr = project.add_module(mod_def, Path("Can.arxml"))
    req_inst = mgr.create_container_instance(req_def)
    req_inst.variant = "V2"
    mgr.set_parameter_value(req_inst, "Tag", "REAL_V2")

    ctrl0 = mgr.create_container_instance(ctrl_def, instance_name="Ctrl_0")
    flt0 = mgr.create_container_instance(filter_def, parent=ctrl0, instance_name="Filter")
    mgr.set_parameter_value(flt0, "Mask", 1)

    ctrl1 = mgr.create_container_instance(ctrl_def, instance_name="Ctrl_1")
    flt1 = mgr.create_container_instance(filter_def, parent=ctrl1, instance_name="Filter")
    mgr.set_parameter_value(flt1, "Mask", 2)

    mgr.configuration.variant_overrides = {"V2": {"Filter.Mask": 99}}

    tpl = (
        'cnt=[!"num:i(count(ReqOnlyV2/*))"!];'
        'exists=[!"node:exists(ReqOnlyV2/Tag)"!];'
        'tag=[!IF "node:exists(ReqOnlyV2/Tag)"!][!"node:value(ReqOnlyV2/Tag)"!][!ELSE!]NONE[!ENDIF!];'
        'masks=[!LOOP "Ctrl/*"!][!"node:value(Filter/Mask)"!],[!ENDLOOP!]'
    )

    out_none = EBTemplateEngine(strict=False).render(
        tpl, {"module_def": mod_def, "configuration": mgr.configuration, "module_name": "Can"}
    )
    assert out_none == "cnt=0;exists=false;tag=NONE;masks=1,2,"

    out_default = EBTemplateEngine(strict=False).render(
        tpl,
        {
            "module_def": mod_def,
            "configuration": mgr.configuration,
            "module_name": "Can",
            "active_variant": "Default",
        },
    )
    assert out_default == "cnt=0;exists=false;tag=NONE;masks=1,2,"

    out_v2 = EBTemplateEngine(strict=False).render(
        tpl,
        {
            "module_def": mod_def,
            "configuration": mgr.configuration,
            "module_name": "Can",
            "active_variant": "V2",
        },
    )
    assert out_v2 == "cnt=1;exists=true;tag=REAL_V2;masks=1,2,"


def test_eb_template_engine_evaluates_enable_conditions_with_active_variant_and_recomputes_on_reuse():
    """EBTemplateEngine injects active_variant/project_variants before apply_enable_conditions()
    and recomputes enable_result when the same engine instance is reused across variants."""
    from autosar_configurator.generator.eb_template_engine import EBTemplateEngine

    mod_def = EcucModuleDef(short_name="EcuC", definition_ref="/MICROSAR/EcuC")
    general_def = EcucContainerDef(
        short_name="EcucGeneral",
        definition_ref="/MICROSAR/EcuC/EcucGeneral",
        lower_multiplicity=1,
        upper_multiplicity=1,
    )
    general_def.add_parameter(
        EcucParameterDef(
            short_name="V2OnlyFlag",
            param_type=EcucParameterType.BOOLEAN,
            definition_ref="/MICROSAR/EcuC/EcucGeneral/V2OnlyFlag",
            default_value=True,
            enable_expr="variant:name() = 'V2'",
        )
    )
    mod_def.add_container(general_def)

    project = WorkspaceProject("demo")
    mgr = project.add_module(mod_def, Path("EcuC.arxml"))
    general = mgr.create_container_instance(general_def)
    mgr.set_parameter_value(general, "V2OnlyFlag", True)

    engine = EBTemplateEngine(strict=False)
    tpl = '[!"node:exists(EcucGeneral/V2OnlyFlag)"!]:[!"variant:name()"!]'

    out1 = engine.render(
        tpl,
        {
            "module_def": mod_def,
            "configuration": mgr.configuration,
            "module_name": "EcuC",
            "active_variant": "Default",
            "project_variants": ["Default", "V2"],
        },
    )
    assert out1 == "false:"

    out2 = engine.render(
        tpl,
        {
            "module_def": mod_def,
            "configuration": mgr.configuration,
            "module_name": "EcuC",
            "active_variant": "V2",
            "project_variants": ["Default", "V2"],
        },
    )
    assert out2 == "true:V2"

    out3 = engine.render(
        tpl,
        {
            "module_def": mod_def,
            "configuration": mgr.configuration,
            "module_name": "EcuC",
            "active_variant": "Default",
            "project_variants": ["Default", "V2"],
        },
    )
    assert out3 == "false:"



