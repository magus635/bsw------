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
