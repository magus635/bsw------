"""EB tresos value XDM import and EPC export: definition paths, disabled items,
module-level parameters and the implementation configuration variant."""
from pathlib import Path

import pytest
from lxml import etree

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.configuration_model import (
    EcucModuleConfiguration,
    normalize_config_variant,
)
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer
from autosar_configurator.generator.eb.overlay_engine import OverlayEngine

AR = "{http://autosar.org/schema/r4.0}"
NS = ('xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd" '
      'xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd" '
      'xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd" '
      'xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"')

DEFINITION = f"""<?xml version='1.0'?>
<datamodel version="7.0" {NS}>
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="TS_X" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Os" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF">
              <v:var name="OsResourceSubderivative" type="ENUMERATION">
                <a:da name="DEFAULT" value="Os_THA6206"/>
                <a:da name="RANGE"><a:v>Os_THA6206</a:v><a:v>Os_SC300</a:v></a:da>
              </v:var>
              <v:lst name="OsCoreIdMappingConfig" type="MAP">
                <v:ctr name="OsCoreIdMappingConfig" type="IDENTIFIABLE">
                  <v:var name="OsPhysicalCoreId" type="INTEGER"/>
                  <v:ref name="OsTpCounterRef" type="REFERENCE"/>
                  <v:ctr name="OsCoreHookStackConfig" type="IDENTIFIABLE">
                    <v:var name="OsStartupHookSize" type="INTEGER"/>
                  </v:ctr>
                </v:ctr>
              </v:lst>
              <v:lst name="OsMemoryMap" type="MAP">
                <v:ctr name="OsMemoryMap" type="IDENTIFIABLE">
                  <v:var name="OsMemorySectionName" type="STRING"/>
                  <v:var name="MemoryBlockAlign" type="ENUMERATION">
                    <a:da name="RANGE"><a:v>8</a:v><a:v>64</a:v></a:da>
                  </v:var>
                  <v:var name="OsIsrHandler" type="FUNCTION-NAME"/>
                  <v:var name="OsMemoryEnabled" type="BOOLEAN"/>
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


def _values(module_vars: str) -> str:
    return f"""<?xml version='1.0'?>
<datamodel version="7.0" {NS}>
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="Os" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Os" type="AR-ELEMENT" value="MODULE-CONFIGURATION">
            <d:ctr type="MODULE-CONFIGURATION">
              <a:a name="DEF" value="ASPath:/TS_X/Os"/>
              {module_vars}
              <d:lst name="OsCoreIdMappingConfig" type="MAP">
                <d:ctr name="OsCoreIdMappingConfig_0" type="IDENTIFIABLE">
                  <d:var name="OsPhysicalCoreId" type="INTEGER" value="0"/>
                  <d:ref name="OsTpCounterRef" type="REFERENCE" value="ASPath:/Os/Os/OsCounter_Hrt">
                    <a:a name="ENABLE" value="false"/>
                  </d:ref>
                  <d:ctr name="OsCoreHookStackConfig" type="IDENTIFIABLE">
                    <d:var name="OsStartupHookSize" type="INTEGER" value="1024"/>
                  </d:ctr>
                </d:ctr>
              </d:lst>
              <d:lst name="OsMemoryMap" type="MAP">
                <d:ctr name="CODE_QM_CORE0" type="IDENTIFIABLE">
                  <d:var name="OsMemorySectionName" type="STRING" value=".text"/>
                  <d:var name="MemoryBlockAlign" type="ENUMERATION" value="64"/>
                  <d:var name="OsIsrHandler" type="FUNCTION-NAME">
                    <a:a name="IMPORTER_INFO" value="@DEF"/>
                  </d:var>
                  <d:var name="OsMemoryEnabled" type="BOOLEAN" value="true"/>
                </d:ctr>
                <d:ctr name="DISABLED_MAP" type="IDENTIFIABLE">
                  <a:a name="ENABLE" value="false"/>
                  <d:var name="OsMemorySectionName" type="STRING" value=".x"/>
                </d:ctr>
              </d:lst>
            </d:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>
"""


SC300 = '<d:var name="OsResourceSubderivative" type="ENUMERATION" value="Os_SC300"/>'


def _load(tmp_path: Path, module_vars: str = SC300):
    (tmp_path / "def.xdm").write_text(DEFINITION, encoding="utf-8")
    (tmp_path / "val.xdm").write_text(_values(module_vars), encoding="utf-8")
    module_def = EcucDefParser().parse_module_def_file(tmp_path / "def.xdm")
    manager = ConfigurationManager(module_def)
    manager.load_configuration(tmp_path / "val.xdm")
    return module_def, manager


def _export(manager, tmp_path: Path) -> Path:
    out = tmp_path / "Os.epc"
    EcucValueSerializer().export_epc(manager.configuration, out)
    return out


def _def_refs(path: Path):
    return [d.text.strip() for d in etree.parse(str(path)).getroot().iter(f"{AR}DEFINITION-REF")]


# --- definition paths ------------------------------------------------------------------

def test_list_instances_use_the_list_definition(tmp_path):
    _, manager = _load(tmp_path)
    refs = _def_refs(_export(manager, tmp_path))
    assert "/TS_X/Os/OsMemoryMap" in refs
    assert "/TS_X/Os/OsCoreIdMappingConfig" in refs
    assert "/TS_X/Os/OsCoreIdMappingConfig/OsCoreHookStackConfig/OsStartupHookSize" in refs
    assert not [r for r in refs if "CODE_QM_CORE0" in r or "OsCoreIdMappingConfig_0" in r]


# --- disabled items -------------------------------------------------------------------

def test_disabled_reference_and_container_are_not_configuration(tmp_path):
    _, manager = _load(tmp_path)
    refs = _def_refs(_export(manager, tmp_path))
    assert not [r for r in refs if r.endswith("/OsTpCounterRef")]
    names = [c.short_name for c in manager.configuration.containers]
    assert "CODE_QM_CORE0" in names and "DISABLED_MAP" not in names


# --- value kinds ------------------------------------------------------------------------

def _param_elements(path: Path):
    """definition name -> (element tag, DEST, VALUE) of the exported parameter values"""
    rows = {}
    for tag in ("ECUC-TEXTUAL-PARAM-VALUE", "ECUC-NUMERICAL-PARAM-VALUE"):
        for el in etree.parse(str(path)).getroot().iter(f"{AR}{tag}"):
            d = el.find(f"{AR}DEFINITION-REF")
            rows[d.text.rsplit("/", 1)[-1]] = (tag, d.get("DEST"), el.findtext(f"{AR}VALUE"))
    return rows


def test_enumeration_literal_stays_textual(tmp_path):
    _, manager = _load(tmp_path)
    rows = _param_elements(_export(manager, tmp_path))
    assert rows["MemoryBlockAlign"] == ("ECUC-TEXTUAL-PARAM-VALUE", "ECUC-ENUMERATION-PARAM-DEF", "64")
    assert rows["OsPhysicalCoreId"] == ("ECUC-NUMERICAL-PARAM-VALUE", "ECUC-INTEGER-PARAM-DEF", "0")
    assert rows["OsMemoryEnabled"] == ("ECUC-NUMERICAL-PARAM-VALUE", "ECUC-BOOLEAN-PARAM-DEF", "1")
    assert rows["OsMemorySectionName"][:2] == ("ECUC-TEXTUAL-PARAM-VALUE", "ECUC-STRING-PARAM-DEF")


def test_parameter_without_value_is_exported_without_value_element(tmp_path):
    module_def, manager = _load(tmp_path)
    out = _export(manager, tmp_path)
    # as EB writes it: the parameter is there, with no <VALUE> (not the text "None")
    assert _param_elements(out)["OsIsrHandler"] == (
        "ECUC-TEXTUAL-PARAM-VALUE", "ECUC-FUNCTION-NAME-DEF", None)
    assert "<VALUE>None</VALUE>" not in out.read_text(encoding="utf-8")

    again = ConfigurationManager(module_def)
    again.load_configuration(out)
    container = next(c for c in again.configuration.containers if c.short_name == "CODE_QM_CORE0")
    assert container.parameter_values["OsIsrHandler"].value is None


def test_enumeration_literal_survives_project_round_trip(tmp_path):
    module_def, manager = _load(tmp_path)
    again = ConfigurationManager(module_def)
    again.load_configuration(_export(manager, tmp_path))
    (tmp_path / "again").mkdir()
    rows = _param_elements(_export(again, tmp_path / "again"))
    assert rows["MemoryBlockAlign"] == ("ECUC-TEXTUAL-PARAM-VALUE", "ECUC-ENUMERATION-PARAM-DEF", "64")


# --- module-level parameters ------------------------------------------------------------

def test_module_level_parameter_is_kept_exported_and_read_back(tmp_path):
    module_def, manager = _load(tmp_path)
    assert manager.configuration.get_module_parameter("OsResourceSubderivative") == "Os_SC300"

    out = _export(manager, tmp_path)
    root = etree.parse(str(out)).getroot()
    sd = root.find(f".//{AR}ADMIN-DATA/{AR}SDGS/{AR}SDG[@GID='ModuleParameters']/{AR}SD[@GID='OsResourceSubderivative']")
    assert sd is not None and sd.text == "Os_SC300"

    again = ConfigurationManager(module_def)
    again.load_configuration(out)
    assert again.configuration.get_module_parameter("OsResourceSubderivative") == "Os_SC300"


def test_generator_sees_the_configured_module_value_not_the_default(tmp_path):
    module_def, manager = _load(tmp_path)
    tree = OverlayEngine(strict=False).build_configuration_tree(module_def, manager.configuration)
    node = next(c for c in tree.children if c.short_name == "OsResourceSubderivative")
    assert node.value == "Os_SC300"

    plain = OverlayEngine(strict=False).build_configuration_tree(module_def, EcucModuleConfiguration(
        short_name="Os", definition_ref="/TS_X/Os"))
    node = next(c for c in plain.children if c.short_name == "OsResourceSubderivative")
    assert node.value == "Os_THA6206"                  # no configured value: the default


# --- implementation configuration variant ---------------------------------------------------

def test_variant_defaults_to_pre_compile(tmp_path):
    _, manager = _load(tmp_path)
    assert manager.configuration.implementation_config_variant == "VARIANT-PRE-COMPILE"
    root = etree.parse(str(_export(manager, tmp_path))).getroot()
    assert root.findtext(f".//{AR}IMPLEMENTATION-CONFIG-VARIANT") == "VARIANT-PRE-COMPILE"


def test_variant_from_xdm_is_written_in_autosar_spelling(tmp_path):
    _, manager = _load(tmp_path, SC300 + '<d:var name="IMPLEMENTATION_CONFIG_VARIANT" '
                                         'type="ENUMERATION" value="VariantPostBuild"/>')
    assert manager.configuration.implementation_config_variant == "VARIANT-POST-BUILD"
    assert "IMPLEMENTATION_CONFIG_VARIANT" not in manager.configuration.parameter_values
    root = etree.parse(str(_export(manager, tmp_path))).getroot()
    assert root.findtext(f".//{AR}IMPLEMENTATION-CONFIG-VARIANT") == "VARIANT-POST-BUILD"


@pytest.mark.parametrize("raw, expected", [
    ("VariantPreCompile", "VARIANT-PRE-COMPILE"),
    ("VariantLinkTime", "VARIANT-LINK-TIME"),
    ("VariantPostBuild", "VARIANT-POST-BUILD"),
    ("VARIANT-POST-BUILD", "VARIANT-POST-BUILD"),
    ("", "VARIANT-PRE-COMPILE"),
    (None, "VARIANT-PRE-COMPILE"),
    ("Os_THA6206", "Os_THA6206"),           # what one EB export wrote; kept as is
])
def test_normalize_config_variant(raw, expected):
    assert normalize_config_variant(raw) == expected


def test_selector_check_reads_module_level_values(tmp_path):
    from autosar_configurator.core.hardware.chip_database import ChipDefinition
    from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
        check_selectors,
    )

    _, manager = _load(tmp_path)

    class Project:
        module_managers = {"Os": manager}

    chip = ChipDefinition(name="THA6206_LFBGA292", selectors={"Os.OsResourceSubderivative": "Os_THA6206"})
    messages = check_selectors(Project(), chip)
    assert len(messages) == 1 and "Os_SC300" in messages[0]
