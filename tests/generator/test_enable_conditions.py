"""Definition ENABLE conditions: parsed from the XDM definition, evaluated on the
configuration tree before rendering, left out of the EPC export."""
import os
from pathlib import Path

import pytest
from lxml import etree

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer
from autosar_configurator.generator.eb.enable_conditions import (
    disabled_configuration_objects,
)
from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
from autosar_configurator.generator.generator import CodeGenerator

AR = "{http://autosar.org/schema/r4.0}"
NS = ('xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd" '
      'xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd" '
      'xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd" '
      'xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"')


def _definition(module: str, body: str) -> str:
    return f"""<?xml version='1.0'?>
<datamodel version="7.0" {NS}>
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="TS_X" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="{module}" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF">{body}</v:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>
"""


def _values(module: str, body: str) -> str:
    return f"""<?xml version='1.0'?>
<datamodel version="7.0" {NS}>
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="{module}" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="{module}" type="AR-ELEMENT" value="MODULE-CONFIGURATION">
            <d:ctr type="MODULE-CONFIGURATION">
              <a:a name="DEF" value="ASPath:/TS_X/{module}"/>
              {body}
            </d:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>
"""


SC = "(../../../OsOS/OsScalabilityClass = 'SC4') or (../../../OsOS/OsScalabilityClass = 'SC2')"

OS_DEF = _definition("Os", f"""
  <v:ctr name="OsOS" type="IDENTIFIABLE">
    <v:var name="OsScalabilityClass" type="ENUMERATION">
      <a:da name="RANGE"><a:v>SC1</a:v><a:v>SC2</a:v></a:da>
    </v:var>
  </v:ctr>
  <v:lst name="OsTask" type="MAP">
    <v:ctr name="OsTask" type="IDENTIFIABLE">
      <v:var name="OsTaskUseAutostart" type="BOOLEAN"/>
      <v:var name="OsTaskBad" type="INTEGER">
        <a:da name="ENABLE" type="XPath" expr="foo:bar(.)"/>
      </v:var>
      <v:var name="OsTaskOptional" type="INTEGER">
        <a:da name="ENABLE" value="false"/>
      </v:var>
      <v:var name="OsTaskOnEcuc" type="INTEGER">
        <a:da name="ENABLE" type="XPath"
              expr="node:value(as:modconf('EcuC')[1]/EcucGeneral/EcucFlag) = 'true'"/>
      </v:var>
      <v:lst name="OsTaskAppModeRef">
        <a:da name="ENABLE" type="XPath" expr="node:value(../OsTaskUseAutostart) = 'true'"/>
        <v:ref name="OsTaskAppModeRef" type="REFERENCE"/>
      </v:lst>
      <v:lst name="OsTaskTimingProtection" type="MAP">
        <a:da name="MAX" value="1"/>
        <a:da name="ENABLE" type="XPath" expr="{SC}" true="true" false="false"/>
        <v:ctr name="OsTaskTimingProtection" type="IDENTIFIABLE">
          <v:var name="OsTaskExecutionBudget" type="FLOAT"/>
        </v:ctr>
      </v:lst>
      <v:ctr name="OsTaskHooks" type="IDENTIFIABLE">
        <v:var name="OsTaskHook" type="BOOLEAN">
          <a:da name="ENABLE" type="XPath" expr="node:value(../../OsTaskUseAutostart) = 'true'"
                true="false" false="true"/>
        </v:var>
      </v:ctr>
    </v:ctr>
  </v:lst>
  <v:lst name="OsResource" type="MAP">
    <v:ctr name="OsResource" type="IDENTIFIABLE">
      <v:var name="OsResourceProperty" type="ENUMERATION">
        <a:da name="RANGE"><a:v>STANDARD</a:v><a:v>LINKED</a:v></a:da>
      </v:var>
      <v:var name="OsResourceLinkedToResScheduler" type="BOOLEAN"/>
      <v:ref name="OsResourceCoreRef" type="REFERENCE">
        <a:da name="ENABLE" type="XPath"
              expr="(../OsResourceProperty != 'LINKED') or (../OsResourceLinkedToResScheduler = 'true')"/>
      </v:ref>
      <v:ref name="OsResourceLinkedResourceRef" type="REFERENCE">
        <a:da name="ENABLE" type="XPath"
              expr="(../OsResourceProperty = 'LINKED') and (../OsResourceLinkedToResScheduler = 'false')"/>
      </v:ref>
    </v:ctr>
  </v:lst>
""")

ECUC_DEF = _definition("EcuC", """
  <v:ctr name="EcucGeneral" type="IDENTIFIABLE">
    <v:var name="EcucFlag" type="BOOLEAN"/>
  </v:ctr>
""")


def _task(name: str, autostart: str) -> str:
    return f"""
    <d:ctr name="{name}" type="IDENTIFIABLE">
      <d:var name="OsTaskUseAutostart" type="BOOLEAN" value="{autostart}"/>
      <d:var name="OsTaskBad" type="INTEGER" value="1"/>
      <d:var name="OsTaskOptional" type="INTEGER" value="2"/>
      <d:var name="OsTaskOnEcuc" type="INTEGER" value="3"/>
      <d:lst name="OsTaskAppModeRef">
        <d:ref type="REFERENCE" value="ASPath:/Os/Os/OsOS"/>
      </d:lst>
      <d:lst name="OsTaskTimingProtection" type="MAP">
        <d:ctr name="OsTaskTimingProtection_0" type="IDENTIFIABLE">
          <d:var name="OsTaskExecutionBudget" type="FLOAT" value="0.008"/>
        </d:ctr>
      </d:lst>
      <d:ctr name="OsTaskHooks" type="IDENTIFIABLE">
        <d:var name="OsTaskHook" type="BOOLEAN" value="true"/>
      </d:ctr>
    </d:ctr>"""


def _os_values(sc: str) -> str:
    return _values("Os", f"""
      <d:ctr name="OsOS" type="IDENTIFIABLE">
        <d:var name="OsScalabilityClass" type="ENUMERATION" value="{sc}"/>
      </d:ctr>
      <d:lst name="OsTask" type="MAP">{_task("TaskAuto", "true")}{_task("TaskManual", "false")}
      </d:lst>
      <d:lst name="OsResource" type="MAP">
        <d:ctr name="ResStd" type="IDENTIFIABLE">
          <d:var name="OsResourceProperty" type="ENUMERATION" value="STANDARD"/>
          <d:var name="OsResourceLinkedToResScheduler" type="BOOLEAN" value="false"/>
          <d:ref name="OsResourceCoreRef" type="REFERENCE" value="ASPath:/Os/Os/OsOS"/>
          <d:ref name="OsResourceLinkedResourceRef" type="REFERENCE" value="ASPath:/Os/Os/OsOS"/>
        </d:ctr>
        <d:ctr name="ResLinked" type="IDENTIFIABLE">
          <d:var name="OsResourceProperty" type="ENUMERATION" value="LINKED"/>
          <d:var name="OsResourceLinkedToResScheduler" type="BOOLEAN" value="false"/>
          <d:ref name="OsResourceCoreRef" type="REFERENCE" value="ASPath:/Os/Os/OsOS"/>
          <d:ref name="OsResourceLinkedResourceRef" type="REFERENCE" value="ASPath:/Os/Os/ResStd"/>
        </d:ctr>
      </d:lst>
    """)


def _load(tmp_path: Path, sc: str = "SC1", ecuc_flag: str = "true"):
    """module name -> (definition, configuration manager)"""
    modules = {}
    for name, definition, values in (
            ("Os", OS_DEF, _os_values(sc)),
            ("EcuC", ECUC_DEF, _values("EcuC", f"""
              <d:ctr name="EcucGeneral" type="IDENTIFIABLE">
                <d:var name="EcucFlag" type="BOOLEAN" value="{ecuc_flag}"/>
              </d:ctr>"""))):
        (tmp_path / f"{name}_def.xdm").write_text(definition, encoding="utf-8")
        (tmp_path / f"{name}.xdm").write_text(values, encoding="utf-8")
        module_def = EcucDefParser().parse_module_def_file(tmp_path / f"{name}_def.xdm")
        manager = ConfigurationManager(module_def)
        manager.load_configuration(tmp_path / f"{name}.xdm")
        modules[name] = (module_def, manager)
    return modules


def _render(modules, template: str):
    engine = EBTemplateEngine(strict=False)
    os_def, os_manager = modules["Os"]
    out = engine.render(template, {
        "module_def": os_def, "configuration": os_manager.configuration,
        "all_modules": {n: (d, m.configuration) for n, (d, m) in modules.items()}})
    return out.strip(), engine.enable_result


TASK = "as:modconf('Os')[1]/OsTask/"


# --- definition parsing ------------------------------------------------------------------

def test_conditions_are_read_from_the_definition(tmp_path):
    os_def = _load(tmp_path)["Os"][0]
    task = os_def.containers["OsTask"]
    assert task.sub_containers["OsTaskTimingProtection"].list_enable_expr == SC
    assert task.sub_containers["OsTaskTimingProtection"].in_list
    assert not task.sub_containers["OsTaskHooks"].in_list
    assert task.references["OsTaskAppModeRef"].enable_expr == "node:value(../OsTaskUseAutostart) = 'true'"
    # true="false" false="true": enabled when the expression is false
    assert task.sub_containers["OsTaskHooks"].parameters["OsTaskHook"].enable_expr == \
        "not (node:value(../../OsTaskUseAutostart) = 'true')"
    # a fixed value is the initial state of a new optional item, not a condition
    assert task.parameters["OsTaskOptional"].enable_expr is None
    resource = os_def.containers["OsResource"]
    assert resource.references["OsResourceCoreRef"].enable_expr.startswith("(../OsResourceProperty != 'LINKED')")


@pytest.mark.skipif(not os.environ.get("OS_THA6_DEFINITION_XDM"),
                    reason="set OS_THA6_DEFINITION_XDM to the Os_THA6_ASR21 config/Os.xdm")
def test_real_os_definition_conditions():
    os_def = EcucDefParser().parse_module_def_file(Path(os.environ["OS_THA6_DEFINITION_XDM"]))
    found = {}

    def walk(c):
        if c.list_enable_expr:
            found[("list", c.definition_ref)] = c.list_enable_expr
        if c.enable_expr:
            found[("ctr", c.definition_ref)] = c.enable_expr
        for d in list(c.parameters.values()) + list(c.references.values()):
            if d.enable_expr:
                found[("item", d.definition_ref)] = d.enable_expr
        for s in c.sub_containers.values():
            walk(s)

    for c in os_def.containers.values():
        walk(c)
    assert len(found) == 44                       # every XPath ENABLE of the definition
    assert ("list", "OsTask/OsTaskTimingProtection") in found
    assert found[("item", "OsApplication/OsApplicationHooks/OsAppErrorHook")].startswith("not (")
    assert ("list", "/AUTOSAR/EcucDefs/Os/MemoryRegion") in found
    assert ("ctr", "/AUTOSAR/EcucDefs/Os/SystemModeStack") in found


# --- generation -----------------------------------------------------------------------------

def test_timing_protection_hidden_under_sc1_visible_under_sc2(tmp_path):
    template = f"[!\"num:i(count({TASK}TaskAuto/OsTaskTimingProtection/*))\"!]"
    for sc, expected in (("SC1", "0"), ("SC2", "1")):
        (tmp_path / sc).mkdir()
        assert _render(_load(tmp_path / sc, sc), template)[0] == expected


def test_list_of_references_follows_its_condition(tmp_path):
    out, _ = _render(_load(tmp_path),
                     f"[!\"num:i(count({TASK}TaskAuto/OsTaskAppModeRef/*))\"!]"
                     f"/[!\"num:i(count({TASK}TaskManual/OsTaskAppModeRef/*))\"!]")
    assert out == "1/0"


def test_mutually_exclusive_references(tmp_path):
    res = "as:modconf('Os')[1]/OsResource/"
    out, _ = _render(_load(tmp_path),
                     f"[!\"node:exists({res}ResStd/OsResourceCoreRef)\"!]"
                     f" [!\"node:exists({res}ResStd/OsResourceLinkedResourceRef)\"!]"
                     f" [!\"node:exists({res}ResLinked/OsResourceCoreRef)\"!]"
                     f" [!\"node:exists({res}ResLinked/OsResourceLinkedResourceRef)\"!]")
    assert out == "True False False True"


def test_parameter_in_single_container_sees_its_real_parent(tmp_path):
    # OsTaskHooks is a single v:ctr: ../.. from OsTaskHook is the task; the condition is
    # inverted, so the hook exists only for the task without autostart
    out, _ = _render(_load(tmp_path),
                     f"[!\"node:exists({TASK}TaskAuto/OsTaskHooks/OsTaskHook)\"!]"
                     f" [!\"node:exists({TASK}TaskManual/OsTaskHooks/OsTaskHook)\"!]")
    assert out == "False True"


def test_condition_across_modules(tmp_path):
    (tmp_path / "on").mkdir()
    (tmp_path / "off").mkdir()
    template = f"[!\"node:exists({TASK}TaskAuto/OsTaskOnEcuc)\"!]"
    assert _render(_load(tmp_path / "on", ecuc_flag="true"), template)[0] == "True"
    assert _render(_load(tmp_path / "off", ecuc_flag="false"), template)[0] == "False"


def test_unevaluable_condition_keeps_the_item_and_warns_once(tmp_path):
    out, result = _render(_load(tmp_path), f"[!\"node:exists({TASK}TaskAuto/OsTaskBad)\"!]")
    assert out == "True"
    bad = [w for w in result.warnings if "foo:bar(.)" in w]
    assert len(bad) == 1 and "OsTaskBad" in bad[0]


def test_fixed_enable_value_is_not_a_condition(tmp_path):
    out, _ = _render(_load(tmp_path), f"[!\"node:value({TASK}TaskAuto/OsTaskOptional)\"!]")
    assert out == "2"


def test_module_without_conditions_is_unchanged(tmp_path):
    modules = _load(tmp_path)
    ecuc_def, ecuc_manager = modules["EcuC"]
    engine = EBTemplateEngine(strict=False)
    out = engine.render("[!\"node:value(as:modconf('EcuC')[1]/EcucGeneral/EcucFlag)\"!]", {
        "module_def": ecuc_def, "configuration": ecuc_manager.configuration})
    assert out.strip() in ("1", "true", "True")
    assert engine.enable_result.removed_paths == []


def test_generator_reports_unevaluable_conditions(tmp_path):
    modules = _load(tmp_path)
    os_def, os_manager = modules["Os"]
    (tmp_path / "templates" / "Os").mkdir(parents=True)
    (tmp_path / "templates" / "Os" / "Os_Cfg.h").write_text("[!\"'x'\"!]\n", encoding="utf-8")
    generator = CodeGenerator(os_def, os_manager.configuration, project_template_dir=tmp_path / "templates",
                              all_configurations={n: (d, m.configuration) for n, (d, m) in modules.items()},
                              ecu_resources={})
    assert generator.generate_all(tmp_path / "out") is True
    assert len([w for w in generator.warnings if "foo:bar(.)" in w]) == 1


def test_fingerprint_changes_with_the_generator_version(tmp_path, monkeypatch):
    modules = _load(tmp_path)
    os_def, os_manager = modules["Os"]
    generator = CodeGenerator(os_def, os_manager.configuration, ecu_resources={})
    before = generator._calculate_fingerprint()
    monkeypatch.setattr(CodeGenerator, "GENERATOR_VERSION", CodeGenerator.GENERATOR_VERSION + 1)
    assert generator._calculate_fingerprint() != before


# --- EPC export ---------------------------------------------------------------------------

def _exported(modules, tmp_path: Path, name: str = "Os.epc"):
    skip = disabled_configuration_objects({n: (d, m.configuration) for n, (d, m) in modules.items()})
    out = tmp_path / name
    EcucValueSerializer().export_epc(modules["Os"][1].configuration, out, skip=skip)
    return etree.parse(str(out)).getroot()


def _names(root):
    return {e.text for e in root.iter(f"{AR}SHORT-NAME")}


def _defs(root):
    return [d.text.rsplit("/", 1)[-1] for d in root.iter(f"{AR}DEFINITION-REF")]


def test_disabled_items_are_left_out_of_the_epc_export(tmp_path):
    modules = _load(tmp_path)
    root = _exported(modules, tmp_path)
    assert "OsTaskTimingProtection_0" not in _names(root)
    assert "OsTaskExecutionBudget" not in _defs(root)
    assert _defs(root).count("OsTaskAppModeRef") == 1          # TaskAuto only
    assert _defs(root).count("OsResourceCoreRef") == 1          # ResStd only
    assert _defs(root).count("OsTaskBad") == 2                  # unevaluable: kept

    # the project keeps the values
    configuration = modules["Os"][1].configuration
    project_file = tmp_path / "Os_Config.arxml"
    EcucValueSerializer().serialize_to_file(configuration, project_file)
    assert "OsTaskTimingProtection_0" in project_file.read_text(encoding="utf-8")


def test_items_come_back_when_the_condition_is_true_again(tmp_path):
    modules = _load(tmp_path)
    assert "OsTaskTimingProtection_0" not in _names(_exported(modules, tmp_path, "sc1.epc"))
    os_os = next(c for c in modules["Os"][1].configuration.containers if c.short_name == "OsOS")
    os_os.parameter_values["OsScalabilityClass"].value = "SC2"
    root = _exported(modules, tmp_path, "sc2.epc")
    assert "OsTaskTimingProtection_0" in _names(root)
    assert "OsTaskExecutionBudget" in _defs(root)


def test_export_without_skip_is_unchanged(tmp_path):
    configuration = _load(tmp_path)["Os"][1].configuration
    a, b = tmp_path / "a.epc", tmp_path / "b.epc"
    EcucValueSerializer().export_epc(configuration, a)
    EcucValueSerializer().export_epc(configuration, b, skip=set())
    assert a.read_bytes() == b.read_bytes()
