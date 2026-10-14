"""Reference destinations of EB tresos .xdm definitions.

- The attribute namespace carries the DataModel version of the plugin that wrote the file
  (…/DataModel2/10/attribute.xsd for the t1 EcuC.xdm, …/16/… for Os.xdm); the parser used to read version 16 only,
  so every <a:…> attribute of a version 10 file (the REF of EcucCoreRef, defaults, scopes) was ignored.
- A reference that may point to several container types lists them as <a:da name="REF"><a:v>…</a:v>…</a:da>
  (OsTaskAutostartAppModeRef: OsAppMode, OSDEFAULTAPPMODE, OSALLRUNNINGMODE); it used to get no destination at all.
"""
import pytest

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

XDM = """<?xml version='1.0'?>
<datamodel version="4.0" xmlns="http://www.tresos.de/_projects/DataModel2/10/root.xsd"
           xmlns:a="http://www.tresos.de/_projects/DataModel2/{ver}/attribute.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd">
  <d:ctr type="AUTOSAR" factory="autosar"><d:lst type="TOP-LEVEL-PACKAGES">
    <d:ctr name="Pkg" type="AR-PACKAGE"><d:lst type="ELEMENTS">
      <d:chc name="Mod" type="AR-ELEMENT" value="MODULE-DEF">
        <v:ctr type="MODULE-DEF">
          <a:a name="LOWER-MULTIPLICITY" value="1"/><a:a name="UPPER-MULTIPLICITY" value="1"/>
          <v:ctr name="Cont" type="IDENTIFIABLE">
            <a:a name="DESC" value="EN: the container"/>
            <v:var name="Flag" type="BOOLEAN"><a:da name="DEFAULT" value="false"/></v:var>
            <v:ref name="Single" type="REFERENCE">
              <a:da name="REF" value="ASPathDataOfSchema:/AUTOSAR/EcucDefs/Mod/Target"/>
            </v:ref>
            <v:ref name="Typed" type="REFERENCE">
              <a:da name="REF" value="ASTyped:PredefinedVariant"/>
            </v:ref>
            <v:lst name="Several">
              <v:ref name="Several" type="REFERENCE">
                <a:da name="REF">
                  <a:v>ASPathDataOfSchema:/AUTOSAR/EcucDefs/Mod/Mode</a:v>
                  <a:v>ASPathDataOfSchema:/AUTOSAR/EcucDefs/Mod/ModeDefault</a:v>
                  <a:v>ASPathDataOfSchema:/AUTOSAR/EcucDefs/Mod/ModeAll</a:v>
                </a:da>
              </v:ref>
            </v:lst>
            <v:lst name="OneOfList">
              <v:ref name="OneOfList" type="REFERENCE">
                <a:da name="REF"><a:v>ASPathDataOfSchema:/AUTOSAR/EcucDefs/Mod/Only</a:v></a:da>
              </v:ref>
            </v:lst>
          </v:ctr>
        </v:ctr>
      </d:chc>
    </d:lst></d:ctr>
  </d:lst></d:ctr>
</datamodel>
"""


def parse(tmp_path, version):
    f = tmp_path / f"Mod_{version}.xdm"
    f.write_text(XDM.format(ver=version), encoding="utf-8")
    module = EcucDefParser().parse_module_def_file(f)
    return module.containers["Cont"]


@pytest.mark.parametrize("version", ["10", "16"])
def test_single_destination_is_read_for_every_attribute_namespace_version(tmp_path, version):
    cont = parse(tmp_path, version)
    assert cont.references["Single"].destination_ref == "/AUTOSAR/EcucDefs/Mod/Target"
    assert cont.description == "EN: the container"
    assert cont.parameters["Flag"].default_value is False


def test_a_later_file_with_another_version_is_not_affected_by_the_earlier_one(tmp_path):
    parser = EcucDefParser()
    for version in ("10", "16", "10"):
        f = tmp_path / f"M{version}.xdm"
        f.write_text(XDM.format(ver=version), encoding="utf-8")
        cont = parser.parse_module_def_file(f).containers["Cont"]
        assert cont.references["Single"].destination_ref == "/AUTOSAR/EcucDefs/Mod/Target", version


@pytest.mark.parametrize("version", ["10", "16"])
def test_several_destinations_become_a_choice(tmp_path, version):
    ref = parse(tmp_path, version).references["Several"]
    expected = ["/AUTOSAR/EcucDefs/Mod/Mode", "/AUTOSAR/EcucDefs/Mod/ModeDefault", "/AUTOSAR/EcucDefs/Mod/ModeAll"]
    assert ref.choice_destination_refs == expected
    assert ref.destination_ref == expected[0]


def test_a_list_with_one_destination_is_a_plain_reference(tmp_path):
    ref = parse(tmp_path, "16").references["OneOfList"]
    assert ref.destination_ref == "/AUTOSAR/EcucDefs/Mod/Only"
    assert ref.choice_destination_refs == []


def test_a_typed_destination_is_kept_as_written(tmp_path):
    """A single-valued REF keeps its text, also when it is no container path (ASTyped:PredefinedVariant); no module
    is derived from it downstream, so it offers no targets (unchanged behaviour)"""
    ref = parse(tmp_path, "16").references["Typed"]
    assert ref.destination_ref == "ASTyped:PredefinedVariant" and ref.choice_destination_refs == []


def test_the_default_namespace_still_applies_to_element_input():
    """parse_module_def(element) is used without a file: the class default (version 16) stays in effect"""
    assert EcucDefParser().NAMESPACES["a"].endswith("/16/attribute.xsd")
