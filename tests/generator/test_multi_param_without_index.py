"""Tests for multi-valued ECUC parameters without <INDEX> in ARXML and EB overlay."""
from lxml import etree

from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
)
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucModuleDef,
    EcucParameterDef,
    EcucParameterType,
)
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.generator.eb_template_engine import EBTemplateEngine


def _build_det_xml(param_entries_xml: str) -> etree._Element:
    xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>ActiveEcuC</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Det</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Det</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DetNotification</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Det/DetNotification</DEFINITION-REF>
              <PARAMETER-VALUES>
                {param_entries_xml}
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""
    root = etree.fromstring(xml.encode("utf-8"))
    return root.xpath('//*[local-name()="ECUC-MODULE-CONFIGURATION-VALUES"]')[0]


def _param_entry(value: str, index: int = None) -> str:
    index_xml = f"<INDEX>{index}</INDEX>" if index is not None else ""
    return f"""
<ECUC-TEXTUAL-PARAM-VALUE>
  <DEFINITION-REF DEST="ECUC-FUNCTION-NAME-DEF">/MICROSAR/Det/DetNotification/DetErrorHook</DEFINITION-REF>
  {index_xml}
  <VALUE>{value}</VALUE>
</ECUC-TEXTUAL-PARAM-VALUE>
"""


def _build_det_module_def() -> EcucModuleDef:
    mod_def = EcucModuleDef(short_name="Det", definition_ref="/MICROSAR/Det")
    notif_def = EcucContainerDef(
        short_name="DetNotification",
        lower_multiplicity=0,
        upper_multiplicity=1,
        definition_ref="/MICROSAR/Det/DetNotification",
    )
    hook_def = EcucParameterDef(
        short_name="DetErrorHook",
        param_type=EcucParameterType.FUNCTION,
        lower_multiplicity=0,
        upper_multiplicity=255,
        definition_ref="/MICROSAR/Det/DetNotification/DetErrorHook",
    )
    notif_def.add_parameter(hook_def)
    mod_def.add_container(notif_def)
    return mod_def


def test_parser_promotes_repeated_unindexed_parameters_to_multi():
    elem = _build_det_xml(_param_entry("Appl_ErrorHook1") + _param_entry("Appl_ErrorHook2"))
    cfg = ArxmlParser().parse_ecuc_configuration_values(elem)
    container = cfg.containers[0]

    assert "DetErrorHook" not in container.parameter_values
    assert "DetErrorHook" in container.multi_parameter_values
    items = container.multi_parameter_values["DetErrorHook"]
    assert [p.value for p in items] == ["Appl_ErrorHook1", "Appl_ErrorHook2"]
    assert [p.index for p in items] == [0, 1]
    assert all(p.dest_type == "ECUC-FUNCTION-NAME-DEF" for p in items)


def test_parser_promotes_unindexed_first_entry_when_subsequent_entry_has_index():
    elem = _build_det_xml(_param_entry("Hook0") + _param_entry("Hook1", index=1))
    cfg = ArxmlParser().parse_ecuc_configuration_values(elem)
    container = cfg.containers[0]

    assert "DetErrorHook" not in container.parameter_values
    items = container.multi_parameter_values["DetErrorHook"]
    assert [p.value for p in items] == ["Hook0", "Hook1"]
    assert [p.index for p in items] == [0, 1]
    assert all(p.dest_type == "ECUC-FUNCTION-NAME-DEF" for p in items)


def test_parser_keeps_three_unindexed_parameters_in_order():
    elem = _build_det_xml(
        _param_entry("H1") + _param_entry("H2") + _param_entry("H3")
    )
    cfg = ArxmlParser().parse_ecuc_configuration_values(elem)
    container = cfg.containers[0]

    assert "DetErrorHook" not in container.parameter_values
    items = container.multi_parameter_values["DetErrorHook"]
    assert [p.value for p in items] == ["H1", "H2", "H3"]
    assert [p.index for p in items] == [0, 1, 2]


def test_overlay_and_eb_template_handles_zero_one_and_many_unindexed_multi_params():
    mod_def = _build_det_module_def()
    template = (
        '[!SELECT "as:modconf(\'Det\')[1]"!]'
        'CNT=[!"num:i(count(DetNotification/DetErrorHook/*))"!]|'
        '[!LOOP "DetNotification/DetErrorHook/*"!][!"."!];[!ENDLOOP!]'
        '[!ENDSELECT!]'
    )

    # 0 configured values
    cfg_zero = ArxmlParser().parse_ecuc_configuration_values(_build_det_xml(""))
    rendered_zero = EBTemplateEngine(strict=False).render(
        template,
        {"module_def": mod_def, "configuration": cfg_zero, "module_name": "Det"},
    )
    assert rendered_zero == "CNT=0|"

    # 1 unindexed value (stored in parameter_values)
    cfg_one = ArxmlParser().parse_ecuc_configuration_values(_build_det_xml(_param_entry("HookA")))
    assert "DetErrorHook" in cfg_one.containers[0].parameter_values
    rendered_one = EBTemplateEngine(strict=False).render(
        template,
        {"module_def": mod_def, "configuration": cfg_one, "module_name": "Det"},
    )
    assert rendered_one == "CNT=1|HookA;"

    # 2 unindexed values (stored in multi_parameter_values)
    cfg_two = ArxmlParser().parse_ecuc_configuration_values(
        _build_det_xml(_param_entry("HookA") + _param_entry("HookB"))
    )
    rendered_two = EBTemplateEngine(strict=False).render(
        template,
        {"module_def": mod_def, "configuration": cfg_two, "module_name": "Det"},
    )
    assert rendered_two == "CNT=2|HookA;HookB;"


def test_overlay_skips_none_single_value_for_multi_param():
    mod_def = _build_det_module_def()
    cfg = EcucModuleConfiguration(short_name="Det", definition_ref="/MICROSAR/Det")
    notif = EcucContainerValue(
        short_name="DetNotification",
        definition_ref="/MICROSAR/Det/DetNotification",
    )
    notif.set_parameter_value(
        "DetErrorHook", None, "/MICROSAR/Det/DetNotification/DetErrorHook"
    )
    cfg.add_container(notif)

    template = (
        '[!SELECT "as:modconf(\'Det\')[1]"!]'
        'CNT=[!"num:i(count(DetNotification/DetErrorHook/*))"!]'
        '[!ENDSELECT!]'
    )
    rendered = EBTemplateEngine(strict=False).render(
        template,
        {"module_def": mod_def, "configuration": cfg, "module_name": "Det"},
    )
    assert rendered == "CNT=0"

