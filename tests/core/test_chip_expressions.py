"""resolve-chip-expressions-in-projects: definition chip expressions follow the project's chip."""
from pathlib import Path

import pytest

from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType)
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.xdm_expression_resolver import (
    XdmExpressionResolver, _walk_containers, apply_chip_expressions, typed_value, upper_limit)
from autosar_configurator.core.workspace_manager import WorkspaceProject

REPO = Path(__file__).resolve().parents[2]
PLUGINS = REPO / "test_import_project" / "Def" / "plugins"
REF = "/AUTOSAR/EcucDefs/Wdg/WdgSettings"


def _module(static_default=None):
    module = EcucModuleDef(short_name="Wdg", definition_ref="/AUTOSAR/EcucDefs/Wdg")
    container = EcucContainerDef(short_name="WdgSettings", definition_ref=REF, upper_multiplicity=-1)
    container.upper_multiplicity_expr = "num:i(count(ecu:list('Wdg.Units')))"
    timeout = EcucParameterDef(short_name="WdgTimeout", param_type=EcucParameterType.FLOAT,
                               definition_ref=f"{REF}/WdgTimeout", default_value=static_default)
    timeout.default_expr = "ecu:get('Wdg.Timeout')"
    timeout.static_default = static_default
    unit = EcucParameterDef(short_name="WdgUnit", param_type=EcucParameterType.ENUMERATION,
                            definition_ref=f"{REF}/WdgUnit", literals=[])
    unit.range_expr = "ecu:list('Wdg.Units')"
    unit.static_literals = []
    container.add_parameter(timeout)
    container.add_parameter(unit)
    module.add_container(container)
    return module, container, timeout, unit


CHIP_A = {"Wdg.Timeout": "2", "Wdg.Units": ["WDG0", "WDG1"]}
CHIP_B = {"Wdg.Timeout": 5, "Wdg.Units": "WDG0, WDG1, WDG2"}


def test_defaults_ranges_and_maxima_follow_the_resources():
    module, container, timeout, unit = _module()
    assert apply_chip_expressions(module, CHIP_A) == 3
    assert timeout.default_value == 2.0 and isinstance(timeout.default_value, float)
    assert unit.literals == ["WDG0", "WDG1"]
    assert container.upper_multiplicity == 2

    apply_chip_expressions(module, CHIP_B)            # another chip
    assert timeout.default_value == 5.0
    assert unit.literals == ["WDG0", "WDG1", "WDG2"]
    assert container.upper_multiplicity == 3
    assert apply_chip_expressions(module, CHIP_B) == 0    # nothing left to change


def test_unresolvable_expressions_fall_back_to_static_values():
    module, container, timeout, unit = _module(static_default=1.5)
    apply_chip_expressions(module, CHIP_A)
    apply_chip_expressions(module, {})
    assert timeout.default_value == 1.5
    assert unit.literals == []
    assert container.upper_multiplicity == -1


@pytest.mark.parametrize("value, ptype, expected", [
    ("15", EcucParameterType.INTEGER, 15),
    ("0x10", EcucParameterType.INTEGER, 16),
    ("2", EcucParameterType.FLOAT, 2.0),
    ("true", EcucParameterType.BOOLEAN, True),
    (3, EcucParameterType.STRING, "3"),
    ("REF_VOLTAGE_GND", EcucParameterType.ENUMERATION, "REF_VOLTAGE_GND"),
    ("abc", EcucParameterType.INTEGER, "abc"),            # does not convert: kept as it is
    (["A", "B"], EcucParameterType.STRING, ["A", "B"]),
])
def test_typed_value(value, ptype, expected):
    assert typed_value(value, ptype) == expected


@pytest.mark.parametrize("resolved, expected", [(12, 12), ("41", 41), (0, -1), (None, -1), ("x", -1), (True, -1)])
def test_upper_limit(resolved, expected):
    assert upper_limit(resolved) == expected


def test_enclosing_parentheses_are_removed_and_case_ignored():
    resolver = XdmExpressionResolver({"dsadc.hwunitlist": ["D0", "D1", "D2"]})
    assert resolver.resolve_expression("(num:i(count(ecu:list('Dsadc.HwUnitList'))))") == 3
    assert resolver.resolve_expression("(a) or (b)") is None


def _vendor(module):
    xdm = PLUGINS / f"{module}_THA6_AS440" / "config" / f"{module}.xdm"
    if not xdm.exists():
        pytest.skip("vendor definition not available")
    return EcucDefParser().parse_module_def_file(xdm)


def _container(module_def, name):
    return next(c for c in _walk_containers(module_def.containers.values()) if c.short_name == name)


def _chip_resources(name):
    from autosar_configurator.core.hardware.chip_database import ChipDatabase, default_chips_dir
    from autosar_configurator.core.hardware.ecu_resource_data import flatten_ecu_resources
    return flatten_ecu_resources(ChipDatabase(default_chips_dir()).get_chip(name).ecu_resources)


def test_vendor_maxima_for_the_chip():
    adc, dma = _vendor("Adc"), _vendor("Dma")
    assert _container(adc, "AdcHwUnit").upper_multiplicity == -1        # parsed without a chip
    apply_chip_expressions(adc, _chip_resources("THA6412_BGA516"))
    apply_chip_expressions(dma, _chip_resources("THA6412_BGA516"))
    assert _container(adc, "AdcHwUnit").upper_multiplicity == 12
    assert _container(dma, "DmaChannel").upper_multiplicity == 128
    apply_chip_expressions(adc, _chip_resources("THA610X_LFBGA180"))
    assert _container(adc, "AdcHwUnit").upper_multiplicity == 4


def test_project_applies_expressions_and_keeps_configured_values(tmp_path):
    adc = _vendor("Adc")
    project = WorkspaceProject("p", tmp_path)
    manager = project.add_module(adc, tmp_path / "Adc.xdm")
    hw_def = _container(adc, "AdcHwUnit")
    parent_def = next(c for c in adc.containers.values() if "AdcHwUnit" in c.sub_containers)
    parent = manager.create_container_instance(parent_def)
    unit = manager.create_container_instance(hw_def, parent=parent)
    unit.set_parameter_value("AdcRefVoltsrcHigh", "CONFIGURED", f"{hw_def.definition_ref}/AdcRefVoltsrcHigh")

    project.selected_chip = "THA6412_BGA516"
    project.load_ecu_resources()
    assert hw_def.upper_multiplicity == 12
    assert hw_def.parameters["AdcRefVoltsrcHigh"].default_value == "REF_VOLTAGE_VAREF"
    assert unit.parameter_values["AdcRefVoltsrcHigh"].value == "CONFIGURED"
    fresh = manager.create_container_instance(hw_def, parent=parent)          # new container: chip default
    assert fresh.parameter_values["AdcRefVoltsrcLow"].value == "REF_VOLTAGE_GND"

    project.selected_chip = "THA610X_LFBGA180"
    project.load_ecu_resources()
    assert hw_def.upper_multiplicity == 4
    assert unit.parameter_values["AdcRefVoltsrcHigh"].value == "CONFIGURED"


def test_more_instances_than_the_chip_has_are_reported(tmp_path):
    from autosar_configurator.core.rules.structural_rules import MultiplicityValidationRule
    adc = _vendor("Adc")
    project = WorkspaceProject("p", tmp_path)
    manager = project.add_module(adc, tmp_path / "Adc.xdm")
    project.selected_chip = "THA610X_LFBGA180"
    project.load_ecu_resources()
    hw_def = _container(adc, "AdcHwUnit")
    parent = manager.create_container_instance(next(c for c in adc.containers.values() if "AdcHwUnit" in c.sub_containers))
    for _ in range(4):
        manager.create_container_instance(hw_def, parent=parent)
    with pytest.raises(Exception):
        manager.create_container_instance(hw_def, parent=parent)              # a fifth one is refused
    from autosar_configurator.core.model.configuration_model import EcucContainerValue
    parent.sub_containers.append(EcucContainerValue(short_name="AdcHwUnit_extra",
                                                    definition_ref=hw_def.definition_ref))
    result = MultiplicityValidationRule().validate(adc, manager.configuration)
    assert any("AdcHwUnit" in m.message and "4" in m.message for m in result.errors)
