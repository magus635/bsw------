"""Enumeration values checked against the chip range (validate-enum-against-chip-range)."""
from pathlib import Path
from types import SimpleNamespace

import pytest

from autosar_configurator.core.model.configuration_model import EcucContainerValue, EcucModuleConfiguration
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType)
from autosar_configurator.core.rules.base_rules import EnumerationValidationRule
from autosar_configurator.core.validation_engine import ValidationEngine

REPO = Path(__file__).resolve().parents[2]
PLUGINS = REPO / "test_import_project" / "Def" / "plugins"
DEMO = REPO / "doc" / "THA6XXX_MC_AS440" / "DemoWorkspace" / "CodeProject" / "DemoMcal" / "Config"

REF = "/AUTOSAR/EcucDefs/Adc/AdcHwUnit"


def _module(range_expr="ecu:list('Adc.HwUnitId')", literals=None):
    module = EcucModuleDef(short_name="Adc", definition_ref="/AUTOSAR/EcucDefs/Adc")
    container = EcucContainerDef(short_name="AdcHwUnit", definition_ref=REF)
    param = EcucParameterDef(short_name="AdcHwUnitId", param_type=EcucParameterType.ENUMERATION,
                             literals=list(literals or []), definition_ref=f"{REF}/AdcHwUnitId")
    param.range_expr = range_expr
    container.add_parameter(param)
    module.add_container(container)
    return module


def _config(*values):
    config = EcucModuleConfiguration(short_name="Adc", definition_ref="/AUTOSAR/EcucDefs/Adc")
    for i, value in enumerate(values):
        container = EcucContainerValue(short_name=f"AdcHwUnit_{i}", definition_ref=REF)
        container.set_parameter_value("AdcHwUnitId", value, f"{REF}/AdcHwUnitId")
        config.add_container(container)
    return config


def _project(resources, chip="THA610X_LFBGA180"):
    return SimpleNamespace(ecu_resources=resources, selected_chip=chip)


THA610X_UNITS = {"Adc.HwUnitId": ["SARADC0", "SARADC1", "SARADC2", "SARADC3"]}


def _validate(module, config, project=None):
    return EnumerationValidationRule().validate(module, config, project_context=project)


def test_value_not_on_the_chip_is_an_error_naming_key_and_chip():
    result = _validate(_module(), _config("SARADC1", "SARADC8"), _project(THA610X_UNITS))
    assert result.error_count == 1
    error = result.errors[0]
    assert error.parameter_name == "AdcHwUnitId"
    assert "SARADC8" in error.message and "Adc.HwUnitId" in error.message
    assert "THA610X_LFBGA180" in error.message
    assert error.suggested_fix == "Choose from: SARADC0, SARADC1, SARADC2, SARADC3"


def test_current_chip_prevails_over_parsed_options():
    # Parsed while a chip with SARADC8 was selected
    module = _module(literals=["SARADC0", "SARADC8"])
    assert _validate(module, _config("SARADC3"), _project(THA610X_UNITS)).is_valid
    assert _validate(module, _config("SARADC8"), _project(THA610X_UNITS)).error_count == 1


def test_key_matched_ignoring_case_and_comma_string_split():
    resources = {"adc.hwunitid": "SARADC0, SARADC1"}
    assert _validate(_module(), _config("SARADC1"), _project(resources)).is_valid
    assert _validate(_module(), _config("SARADC2"), _project(resources)).error_count == 1


def test_multi_valued_parameter_checked_value_by_value():
    config = EcucModuleConfiguration(short_name="Adc", definition_ref="/AUTOSAR/EcucDefs/Adc")
    container = EcucContainerValue(short_name="AdcHwUnit_0", definition_ref=REF)
    container.add_multi_parameter_value("AdcHwUnitId", "SARADC0", f"{REF}/AdcHwUnitId", 0)
    container.add_multi_parameter_value("AdcHwUnitId", "SARADC9", f"{REF}/AdcHwUnitId", 1)
    config.add_container(container)
    result = _validate(_module(), config, _project(THA610X_UNITS))
    assert [m.message.split("'")[1] for m in result.errors] == ["SARADC9"]


@pytest.mark.parametrize("module, project", [
    (_module(literals=["SARADC8"]), None),                                         # no project
    (_module("text:concat('x')", literals=["SARADC8"]), _project(THA610X_UNITS)),  # not a plain ecu:list
    (_module(literals=["SARADC8"]), _project({})),                                 # key missing
    (_module(literals=["SARADC8"]), _project({"Adc.HwUnitId": []})),               # empty list
])
def test_range_not_taken_from_the_chip_falls_back_to_definition_options(module, project):
    assert _validate(module, _config("SARADC8"), project).is_valid
    assert _validate(module, _config("SARADC0"), project).error_count == 1


def test_no_options_and_no_chip_range_is_not_checked():
    assert _validate(_module(), _config("ANYTHING"), _project({})).is_valid


def test_engine_passes_the_project_to_the_rule():
    engine = ValidationEngine(_module(), _config("SARADC8"), project_context=_project(THA610X_UNITS))
    engine.register_default_rules()
    assert any("not available on chip" in m.message for m in engine.validate().errors)


def _vendor_adc(config_chip):
    from autosar_configurator.core.config_manager import ConfigurationManager
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
    xdm = PLUGINS / "Adc_THA6_AS440" / "config" / "Adc.xdm"
    epc = DEMO / config_chip / "output" / "Adc.epc"
    if not xdm.exists() or not epc.exists():
        pytest.skip("vendor definition or demo configuration not available")
    manager = ConfigurationManager(EcucDefParser().parse_module_def_file(xdm))
    manager.load_configuration(epc)
    return manager


def _chip_resources(name):
    from autosar_configurator.core.hardware.chip_database import ChipDatabase, default_chips_dir
    from autosar_configurator.core.hardware.ecu_resource_data import flatten_ecu_resources
    return flatten_ecu_resources(ChipDatabase(default_chips_dir()).get_chip(name).ecu_resources)


def _chip_errors(manager, chip):
    result = _validate(manager.module_def, manager.configuration, _project(_chip_resources(chip), chip))
    return [m for m in result.errors if "not available on chip" in m.message]


def test_vendor_demo_configuration_on_its_own_chip_has_no_chip_range_error():
    assert _chip_errors(_vendor_adc("THA6412_BGA516"), "THA6412_BGA516") == []


def test_vendor_demo_configuration_on_another_chip_is_reported():
    errors = _chip_errors(_vendor_adc("THA6412_BGA516"), "THA610X_LFBGA180")
    assert any("'SARADC8'" in m.message and "Adc.HwUnitId" in m.message for m in errors)
