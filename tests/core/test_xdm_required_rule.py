"""EB XDM definitions: a parameter or reference is required unless it is marked OPTIONAL."""
from pathlib import Path

import pytest

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

PLUGINS = Path(__file__).resolve().parent.parent.parent / "test_import_project/Def/plugins"
ADC = PLUGINS / "Adc_THA6_AS440/config/Adc.xdm"
CAN = PLUGINS / "Can_THA6_AS440/config/Can.xdm"


@pytest.fixture(scope="module")
def adc():
    return EcucDefParser().parse_module_def_file(ADC)


@pytest.fixture(scope="module")
def can():
    return EcucDefParser().parse_module_def_file(CAN)


def _hw_unit(adc):
    return adc.containers["AdcConfigSet"].sub_containers["AdcHwUnit"]


def test_a_parameter_without_optional_is_required(adc):
    assert _hw_unit(adc).parameters["AdcHwUnitId"].is_required


def test_an_optional_parameter_is_not_required(adc):
    prescale = _hw_unit(adc).parameters["AdcPrescale"]
    assert not prescale.is_required
    assert prescale.default_value is not None          # a default does not make it required


def test_a_parameter_in_a_list_takes_the_list_minimum(adc):
    group = _hw_unit(adc).sub_containers["AdcGroup"]
    assert group.parameters["AdcResultRegisterDefinition"].lower_multiplicity == 0


def test_a_reference_without_optional_is_required(adc):
    assert adc.containers["AdcConfigSet"].references["AdcAnalogClockSource"].is_required


def test_an_optional_reference_is_not_required(can):
    controller = can.containers["CanConfigSet"].sub_containers["CanController"]
    assert not controller.references["CanWakeupSourceRef"].is_required
