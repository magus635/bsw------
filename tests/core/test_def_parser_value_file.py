"""Choosing an EB tresos value file as a module definition gives a clear message."""
import pytest

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

VALUE_XDM = """<?xml version='1.0'?>
<datamodel version="7.0"
  xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
  xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
  xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
  xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="Os" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Os" type="AR-ELEMENT" value="MODULE-CONFIGURATION">
            <d:ctr type="MODULE-CONFIGURATION">
              <a:a name="DEF" value="ASPath:/THA6_ASR21/Os"/>
              <d:var name="OsResourceSubderivative" type="ENUMERATION" value="Os_THA6206"/>
            </d:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>
"""


def test_value_file_is_named_and_points_to_its_definition(tmp_path):
    path = tmp_path / "Os.xdm"
    path.write_text(VALUE_XDM, encoding="utf-8")
    with pytest.raises(ValueError) as err:
        EcucDefParser().parse_module_def_file(path)
    message = str(err.value)
    assert "configuration value file" in message
    assert "ASPath:/THA6_ASR21/Os" in message
    assert "Import Value File" in message


def test_file_without_any_module_keeps_the_generic_message(tmp_path):
    path = tmp_path / "empty.xdm"
    path.write_text(VALUE_XDM.replace('value="MODULE-CONFIGURATION"', 'value="SOMETHING-ELSE"'),
                    encoding="utf-8")
    with pytest.raises(ValueError) as err:
        EcucDefParser().parse_module_def_file(path)
    assert "No ECUC-MODULE-DEF found" in str(err.value)
