"""DEFINITION-REF / DEST written into configuration files (openspec fix-config-definition-refs)."""
from pathlib import Path

import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model import definition_refs as defrefs
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

XDM = """<?xml version="1.0"?>
<datamodel version="7.0"
           xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
           xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="THA6_ASR21" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Os" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF">
              <v:ctr name="OsOS" type="IDENTIFIABLE">
                <v:var name="OsUseArti" type="BOOLEAN"><a:da name="DEFAULT" value="false"/></v:var>
                <v:var name="OsVendorArtiTraceTask" type="BOOLEAN"><a:da name="DEFAULT" value="true"/></v:var>
                <v:var name="OsNumberOfCores" type="INTEGER"><a:da name="DEFAULT" value="1"/></v:var>
                <v:var name="OsStatus" type="ENUMERATION">
                  <a:da name="DEFAULT" value="STANDARD"/>
                  <a:da name="RANGE"><a:v>STANDARD</a:v><a:v>EXTENDED</a:v></a:da>
                </v:var>
                <v:var name="OsStackAlign" type="ENUMERATION">
                  <a:da name="DEFAULT" value="64"/>
                  <a:da name="RANGE"><a:v>NON</a:v><a:v>128</a:v><a:v>64</a:v></a:da>
                </v:var>
                <v:var name="OsTimeBudget" type="FLOAT"/>
                <v:var name="OsHookName" type="FUNCTION-NAME"/>
                <v:var name="OsComment" type="STRING"/>
                <v:var name="ArMajorVersion" type="INTEGER_LABEL"><a:da name="DEFAULT" value="4"/></v:var>
                <v:ctr name="OsHooks" type="IDENTIFIABLE">
                  <v:var name="OsErrorHook" type="BOOLEAN"><a:da name="DEFAULT" value="false"/></v:var>
                </v:ctr>
              </v:ctr>
              <v:lst name="OsTask" type="MAP">
                <v:ctr name="OsTask" type="IDENTIFIABLE">
                  <v:var name="OsTaskPriority" type="INTEGER"/>
                </v:ctr>
              </v:lst>
            </v:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>
"""


@pytest.fixture
def os_def(tmp_path):
    path = tmp_path / "Os.xdm"
    path.write_text(XDM, encoding="utf-8")
    return EcucDefParser().parse_module_def_file(path)


# ---- helpers ------------------------------------------------------------------------------------

@pytest.mark.parametrize("ref, rel", [
    ("OsOS/OsUseArti", "OsOS/OsUseArti"),
    ("/AUTOSAR/EcucDefs/Os/OsOS/OsUseArti", "OsOS/OsUseArti"),
    ("/THA6_ASR21/Os/OsOS/OsUseArti", "OsOS/OsUseArti"),
    ("/THA6_ASR21/Os", ""),
    ("", ""),
])
def test_module_relative(ref, rel):
    assert defrefs.module_relative(ref, "Os") == rel


def test_same_definition_ignores_the_form():
    assert defrefs.same_definition("OsOS/OsHooks", "/THA6_ASR21/Os/OsOS/OsHooks", "Os")
    assert defrefs.same_definition("/AUTOSAR/EcucDefs/Os/OsOS", "/THA6_ASR21/Os/OsOS")
    assert not defrefs.same_definition("/THA6_ASR21/Os/OsOS", "/THA6_ASR21/Os/OsTask")


def test_xdm_module_path_and_label_types(os_def):
    assert os_def.ar_path == "/THA6_ASR21/Os"
    assert os_def.containers["OsOS"].parameters["ArMajorVersion"].param_type.value == "ECUC-INTEGER-PARAM-DEF"


def test_absolute_ref(os_def):
    assert defrefs.absolute_ref(os_def, "OsOS/OsUseArti") == "/THA6_ASR21/Os/OsOS/OsUseArti"
    assert defrefs.absolute_ref(os_def, "/AUTOSAR/EcucDefs/Os/OsOS") == "/THA6_ASR21/Os/OsOS"
    assert defrefs.absolute_ref(os_def, "/THA6_ASR21/Os/OsOS") == "/THA6_ASR21/Os/OsOS"
    assert defrefs.absolute_ref(os_def, "") == ""
    assert not defrefs.needs_repair(os_def, "/THA6_ASR21/Os/OsOS")
    assert defrefs.needs_repair(os_def, "OsOS/OsUseArti")
    assert defrefs.needs_repair(os_def, "/AUTOSAR/EcucDefs/Os/OsOS")


# ---- new values and saving -----------------------------------------------------------------------

def _saved_refs(manager, tmp_path):
    import re
    out = tmp_path / "Os_Config.arxml"
    manager.save_configuration(out)
    text = out.read_text(encoding="utf-8")
    return text, dict((ref, dest) for dest, ref in
                      re.findall(r'<DEFINITION-REF DEST="([A-Z-]+)">([^<]*)</DEFINITION-REF>', text))


def test_new_values_are_saved_with_absolute_refs_and_types(os_def, tmp_path):
    manager = ConfigurationManager(os_def)
    defs = os_def.containers
    os_os = manager.create_container_instance(defs["OsOS"], None, "OsOS")
    manager.set_parameter_value(os_os, "OsVendorArtiTraceTask", False)
    manager.set_parameter_value(os_os, "OsStatus", "EXTENDED")
    hooks = manager.create_container_instance(defs["OsOS"].sub_containers["OsHooks"], os_os, "OsHooks")
    manager.set_parameter_value(hooks, "OsErrorHook", True)
    task = manager.create_container_instance(defs["OsTask"], None, "Task_A")
    manager.set_parameter_value(task, "OsTaskPriority", 3)

    text, refs = _saved_refs(manager, tmp_path)
    assert refs["/THA6_ASR21/Os"] == "ECUC-MODULE-DEF"
    assert refs["/THA6_ASR21/Os/OsOS"] == "ECUC-PARAM-CONF-CONTAINER-DEF"
    assert refs["/THA6_ASR21/Os/OsOS/OsVendorArtiTraceTask"] == "ECUC-BOOLEAN-PARAM-DEF"
    assert refs["/THA6_ASR21/Os/OsOS/OsStatus"] == "ECUC-ENUMERATION-PARAM-DEF"
    assert refs["/THA6_ASR21/Os/OsOS/OsNumberOfCores"] == "ECUC-INTEGER-PARAM-DEF"
    assert refs["/THA6_ASR21/Os/OsOS/OsHooks"] == "ECUC-PARAM-CONF-CONTAINER-DEF"
    assert refs["/THA6_ASR21/Os/OsOS/OsHooks/OsErrorHook"] == "ECUC-BOOLEAN-PARAM-DEF"
    assert refs["/THA6_ASR21/Os/OsTask/OsTaskPriority"] == "ECUC-INTEGER-PARAM-DEF"
    assert "ECUC-PARAMETER-DEF" not in text
    assert not any(not r.startswith("/") for r in refs)


def test_values_set_directly_on_the_model_are_completed_on_save(os_def, tmp_path):
    manager = ConfigurationManager(os_def)
    os_os = manager.create_container_instance(os_def.containers["OsOS"], None, "OsOS")
    # as earlier versions and other code paths did: the definition's internal path, no DEST
    os_os.set_parameter_value("OsUseArti", True, "OsOS/OsUseArti")
    _, refs = _saved_refs(manager, tmp_path)
    assert refs["/THA6_ASR21/Os/OsOS/OsUseArti"] == "ECUC-BOOLEAN-PARAM-DEF"


# ---- repair on load ------------------------------------------------------------------------------

BROKEN = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Os</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Os</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>OsOS</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Os/OsOS</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/THA6_ASR21/Os/OsOS/OsUseArti</DEFINITION-REF>
              <VALUE>true</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-PARAMETER-DEF">OsOS/OsVendorArtiTraceTask</DEFINITION-REF>
              <VALUE>false</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>OsHooks</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">OsOS/OsHooks</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>
"""


def test_broken_references_are_corrected_on_load_and_written_on_save(os_def, tmp_path, caplog):
    src = tmp_path / "in.arxml"
    src.write_text(BROKEN, encoding="utf-8")
    manager = ConfigurationManager(os_def)
    with caplog.at_level("INFO", logger="autosar_configurator.core.config_manager"):
        manager.load_configuration(src)
    assert any("corrected" in r.getMessage() for r in caplog.records)

    text, refs = _saved_refs(manager, tmp_path)
    assert refs["/THA6_ASR21/Os"] == "ECUC-MODULE-DEF"
    assert refs["/THA6_ASR21/Os/OsOS"] == "ECUC-PARAM-CONF-CONTAINER-DEF"
    assert refs["/THA6_ASR21/Os/OsOS/OsUseArti"] == "ECUC-BOOLEAN-PARAM-DEF"      # EB value, unchanged
    assert refs["/THA6_ASR21/Os/OsOS/OsVendorArtiTraceTask"] == "ECUC-BOOLEAN-PARAM-DEF"
    assert refs["/THA6_ASR21/Os/OsOS/OsHooks"] == "ECUC-PARAM-CONF-CONTAINER-DEF"
    assert "ECUC-PARAMETER-DEF" not in text


def test_correct_eb_references_are_left_alone(os_def, tmp_path):
    good = (BROKEN.replace(">/AUTOSAR/EcucDefs/Os<", ">/THA6_ASR21/Os<")
            .replace(">/AUTOSAR/EcucDefs/Os/OsOS<", ">/THA6_ASR21/Os/OsOS<")
            .replace('DEST="ECUC-PARAMETER-DEF">OsOS/OsVendorArtiTraceTask',
                     'DEST="ECUC-BOOLEAN-PARAM-DEF">/THA6_ASR21/Os/OsOS/OsVendorArtiTraceTask')
            .replace(">OsOS/OsHooks<", ">/THA6_ASR21/Os/OsOS/OsHooks<"))
    src = tmp_path / "in.arxml"
    src.write_text(good, encoding="utf-8")
    manager = ConfigurationManager(os_def)
    manager.load_configuration(src)
    assert manager.repair_definition_refs() == 0


# Values written under the generic DEST (ECUC-PARAMETER-DEF) were read by the type of their
# text: an enumeration literal 64 in an ECUC-NUMERICAL-PARAM-VALUE became the number 64.
GENERIC_DEST_VALUES = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Os</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_ASR21/Os</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>OsOS</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_ASR21/Os/OsOS</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-PARAMETER-DEF">/THA6_ASR21/Os/OsOS/OsStackAlign</DEFINITION-REF>
              <VALUE>64</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-PARAMETER-DEF">/THA6_ASR21/Os/OsOS/OsUseArti</DEFINITION-REF>
              <VALUE>1</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-PARAMETER-DEF">/THA6_ASR21/Os/OsOS/OsNumberOfCores</DEFINITION-REF>
              <VALUE>2</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>
"""


def test_values_under_the_generic_dest_are_typed_by_their_definition(os_def, tmp_path):
    from autosar_configurator.core.rules.base_rules import EnumerationValidationRule, TypeValidationRule
    src = tmp_path / "in.arxml"
    src.write_text(GENERIC_DEST_VALUES, encoding="utf-8")
    manager = ConfigurationManager(os_def)
    manager.load_configuration(src)

    values = manager.configuration.containers[0].parameter_values
    assert values["OsStackAlign"].value == "64"
    assert values["OsUseArti"].value is True
    assert values["OsNumberOfCores"].value == 2
    for rule in (EnumerationValidationRule(), TypeValidationRule()):
        assert rule.validate(os_def, manager.configuration).messages == []

    # The first save already writes what later saves write
    first = tmp_path / "first.arxml"
    manager.save_configuration(first)
    reloaded = ConfigurationManager(os_def)
    reloaded.load_configuration(first)
    second = tmp_path / "second.arxml"
    reloaded.save_configuration(second)
    assert first.read_text(encoding="utf-8") == second.read_text(encoding="utf-8")
    assert '<ECUC-TEXTUAL-PARAM-VALUE>' in first.read_text(encoding="utf-8")


# Earlier versions wrote a parameter without a value as the text "None"
NONE_TEXT_VALUES = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Os</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_ASR21/Os</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>OsOS</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_ASR21/Os/OsOS</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-FLOAT-PARAM-DEF">/THA6_ASR21/Os/OsOS/OsTimeBudget</DEFINITION-REF>
              <VALUE>None</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-FUNCTION-NAME-DEF">/THA6_ASR21/Os/OsOS/OsHookName</DEFINITION-REF>
              <VALUE>None</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/THA6_ASR21/Os/OsOS/OsComment</DEFINITION-REF>
              <VALUE>None</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>Task_A</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_ASR21/Os/OsTask</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-PARAMETER-DEF">/THA6_ASR21/Os/OsTask/OsTaskPriority</DEFINITION-REF>
              <VALUE>None</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>
"""


def test_none_text_is_read_as_no_value(os_def, tmp_path):
    from autosar_configurator.core.rules.base_rules import EnumerationValidationRule, TypeValidationRule
    src = tmp_path / "in.arxml"
    src.write_text(NONE_TEXT_VALUES, encoding="utf-8")
    manager = ConfigurationManager(os_def)
    manager.load_configuration(src)

    os_os, task = manager.configuration.containers
    assert os_os.parameter_values["OsTimeBudget"].value is None
    assert os_os.parameter_values["OsHookName"].value is None
    assert os_os.parameter_values["OsComment"].value == "None"           # free text says it
    # Generic DEST: kept as text until the definition gives the type (INTEGER)
    assert task.parameter_values["OsTaskPriority"].value is None
    assert task.parameter_values["OsTaskPriority"].dest_type == "ECUC-INTEGER-PARAM-DEF"
    for rule in (EnumerationValidationRule(), TypeValidationRule()):
        assert rule.validate(os_def, manager.configuration).messages == []

    # Saved without <VALUE>, as EB writes it; the text stays only where it is text
    out = tmp_path / "out.arxml"
    manager.save_configuration(out)
    text = out.read_text(encoding="utf-8")
    assert text.count("<VALUE>None</VALUE>") == 1
    reloaded = ConfigurationManager(os_def)
    reloaded.load_configuration(out)
    assert reloaded.configuration.containers[0].parameter_values["OsTimeBudget"].value is None


def test_same_definition_handles_three_segment_vendor_paths_without_module_name():
    """3-segment vendor paths (/Pkg/Variant/Module/...) match /AUTOSAR/EcucDefs/<Module>/... even without module_name."""
    assert defrefs.same_definition(
        "/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral",
        "/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral",
    ) is True
    assert defrefs.same_definition(
        "/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral",
        "/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral",
    ) is True
    assert defrefs.same_definition(
        "/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral",
        "/AUTOSAR/EcucDefs/CanTrcv/CanTrcvChannel",
    ) is False
    assert defrefs.same_definition(
        "/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral",
        "/AUTOSAR/EcucDefs/CanIf/CanTrcvGeneral",
    ) is False


def test_multiplicity_validation_rule_handles_three_segment_vendor_def():
    """MultiplicityValidationRule validates nested container multiplicity under a 3-segment vendor module def."""
    from autosar_configurator.core.model.configuration_model import (
        EcucContainerValue,
        EcucModuleConfiguration,
    )
    from autosar_configurator.core.model.definition_model import (
        EcucContainerDef,
        EcucModuleDef,
    )
    from autosar_configurator.core.rules.structural_rules import MultiplicityValidationRule

    module_def = EcucModuleDef(
        short_name="CanTrcv",
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv",
        ar_path="/MICROSAR/CanTrcv_Tle9255/CanTrcv",
    )
    general_def = EcucContainerDef(
        short_name="CanTrcvGeneral",
        lower_multiplicity=1,
        upper_multiplicity=1,
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral",
    )
    sub_def = EcucContainerDef(
        short_name="CanTrcvSub",
        lower_multiplicity=1,
        upper_multiplicity=1,
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral/CanTrcvSub",
    )
    general_def.add_sub_container(sub_def)
    module_def.add_container(general_def)

    config = EcucModuleConfiguration(
        short_name="CanTrcv",
        definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv",
    )
    general = EcucContainerValue(
        short_name="CanTrcvGeneral",
        definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral",
    )
    config.add_container(general)

    rule = MultiplicityValidationRule()
    res_missing = rule.validate(module_def, config)
    assert res_missing.error_count == 1
    assert "CanTrcvSub" in res_missing.errors[0].message

    sub = EcucContainerValue(
        short_name="CanTrcvSub",
        definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvSub",
    )
    general.add_sub_container(sub)
    res_ok = rule.validate(module_def, config)
    assert res_ok.error_count == 0


def test_load_configuration_rejects_single_mismatched_vendor_variant_but_allows_bundle_and_standard(tmp_path):
    """Specific variant def rejects even a single wrong-variant block, while multi-module bundles and standard defs load."""
    from autosar_configurator.core.model.definition_model import (
        EcucContainerDef,
        EcucModuleDef,
        EcucParameterDef,
        EcucParameterType,
    )

    tle_def = EcucModuleDef(
        short_name="CanTrcv",
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv",
        ar_path="/MICROSAR/CanTrcv_Tle9255/CanTrcv",
    )
    gen_def = EcucContainerDef(short_name="CanTrcvGeneral")
    gen_def.parameters["CanTrcvDevErrorDetect"] = EcucParameterDef(
        short_name="CanTrcvDevErrorDetect",
        param_type=EcucParameterType.BOOLEAN,
    )
    tle_def.add_container(gen_def)

    # 1. Single block for a DIFFERENT vendor variant must be rejected
    wrong_single = tmp_path / "wrong_single.arxml"
    wrong_single.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    mgr1 = ConfigurationManager(tle_def)
    with pytest.raises(ValueError, match="CanTrcv_GenericCan"):
        mgr1.load_configuration(wrong_single)

    # 2. Standard /AUTOSAR/EcucDefs/CanTrcv inside a multi-module bundle loads cleanly
    std_bundle = tmp_path / "std_bundle.arxml"
    std_bundle.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Port</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Port</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral/CanTrcvDevErrorDetect</DEFINITION-REF>
            <VALUE>true</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    mgr2 = ConfigurationManager(tle_def)
    mgr2.load_configuration(std_bundle)
    assert mgr2.configuration.definition_ref == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    assert mgr2.configuration.containers[0].parameter_values["CanTrcvDevErrorDetect"].value is True


def test_parameter_dependency_rule_passes_module_name_for_vendor_paths():
    """DependencyRule passes module_name to same_definition so 3-segment and 2-segment vendor paths match."""
    from autosar_configurator.core.model.configuration_model import (
        EcucContainerValue,
        EcucModuleConfiguration,
    )
    from autosar_configurator.core.model.definition_model import EcucModuleDef
    from autosar_configurator.core.rules.dependency_rules import DependencyRule

    module_def = EcucModuleDef(
        short_name="CanTrcv",
        definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv",
        ar_path="/MICROSAR/CanTrcv_Tle9255/CanTrcv",
    )
    cfg = EcucModuleConfiguration(
        short_name="CanTrcv",
        definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv",
    )
    gen = EcucContainerValue(
        short_name="CanTrcvGeneral",
        definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral",
    )
    gen.set_parameter_value("Enable", True, "/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/Enable")
    cfg.add_container(gen)

    rule = DependencyRule()
    rule.add_parameter_dependency(
        "Enable",
        True,
        "Target",
        "/VendorOther/CanTrcv/CanTrcvGeneral",
    )
    res = rule.validate(module_def, cfg)
    assert res.error_count == 1


def test_load_configuration_allows_vendor_config_for_stub_def_missing(tmp_path):
    """Stub module definitions (def_missing=True / /__STUB__/...) must still load vendor configs."""
    from autosar_configurator.core.model.definition_model import EcucModuleDef

    stub_def = EcucModuleDef(
        short_name="CanTrcv",
        definition_ref="/__STUB__/AUTOSAR/EcucDefs/CanTrcv",
    )
    vendor_arxml = tmp_path / "CanTrcv_stub.arxml"
    vendor_arxml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral/CanTrcvDevErrorDetect</DEFINITION-REF>
            <VALUE>true</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    mgr = ConfigurationManager(stub_def, def_missing=True)
    mgr.load_configuration(vendor_arxml, skip_cleanup=True)
    assert len(mgr.configuration.containers) == 1
    gen = mgr.configuration.containers[0]
    assert gen.short_name == "CanTrcvGeneral"
    assert gen.parameter_values["CanTrcvDevErrorDetect"].value is True


def test_restore_deleted_module_rejects_mismatched_single_variant_and_cleans_up_disk(tmp_path, monkeypatch):
    """restore_deleted_module rejects mismatched vendor variant even when only 1 other variant exists,
    and cleans up config/<M>.arxml if post-copy module loading fails."""
    import json
    from autosar_configurator.core.packages.library import LibraryRef
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    proj_dir = tmp_path / "SingleVarProj"
    tle_cfg_dir = proj_dir / "modules" / "CanTrcv_Tle9255" / "config"
    tle_cfg_dir.mkdir(parents=True)
    (tle_cfg_dir / "CanTrcv.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (proj_dir / "modules" / "CanTrcv_Tle9255" / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "CanTrcv",
        "definition": "/MICROSAR/CanTrcv_Tle9255/CanTrcv",
        "files": ["config/CanTrcv.arxml"],
        "pre": [],
        "rec": [],
    }), encoding="utf-8")

    wm = WorkspaceManager()
    project = wm.create_project("SingleVarProj", proj_dir / "SingleVarProj.dpa", format_version=8)
    project.module_libraries.append(LibraryRef(path="modules", kind="package"))
    wm.save_project()

    deleted_dir = proj_dir / ".history" / "deleted"
    deleted_dir.mkdir(parents=True, exist_ok=True)
    mismatched_archive = deleted_dir / "CanTrcv_20260101T000000.arxml"
    mismatched_archive.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    target_cfg = proj_dir / "config" / "CanTrcv.arxml"
    assert not target_cfg.exists()

    with pytest.raises(ValueError) as exc_info:
        project.restore_deleted_module(mismatched_archive, confirm=lambda *_: True)
    msg = str(exc_info.value)
    assert "CanTrcv_GenericCan" in msg
    assert "/MICROSAR/CanTrcv_Tle9255/CanTrcv" in msg
    assert not target_cfg.exists()

    # Standard archive matches single candidate; simulate failure after copy to verify disk cleanup/rollback
    std_archive = deleted_dir / "CanTrcv_20260101T000001.arxml"
    std_archive.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    def _boom(*_args, **_kwargs):
        assert target_cfg.is_file()
        raise ValueError("simulated load failure")

    monkeypatch.setattr(project, "add_module_from_package", _boom)
    with pytest.raises(ValueError, match="simulated load failure"):
        project.restore_deleted_module(std_archive, confirm=lambda *_: True)
    assert not target_cfg.exists()

    # Also preserves any pre-existing file bytes on disk if an error happens after copy
    target_cfg.parent.mkdir(parents=True, exist_ok=True)
    target_cfg.write_bytes(b"PREVIOUS_CONTENT")
    with pytest.raises(ValueError, match="simulated load failure"):
        project.restore_deleted_module(std_archive, confirm=lambda *_: True)
    assert target_cfg.read_bytes() == b"PREVIOUS_CONTENT"


