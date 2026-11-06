"""A definition that carries no parameters says so, and names the definition that
does (vBaseEnv defines vBaseEnvMemLayoutHwRegion twice: an empty placeholder under
vBaseEnvGeneral, and the real one under vBaseEnvDerivativeInformation)."""
import pytest
from PySide6.QtWidgets import QLabel

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel

NAME = "vBaseEnvMemLayoutHwRegion"


@pytest.fixture
def panel(qtbot):
    widget = DaVinciConfigPanel()
    qtbot.addWidget(widget)
    return widget


def _param(name="P"):
    return EcucParameterDef(short_name=name, param_type=EcucParameterType.INTEGER,
                            lower_multiplicity=0, upper_multiplicity=1)


def _module_with_twin():
    """vBaseEnv's shape: an empty placeholder and a parameterised definition."""
    module_def = EcucModuleDef(short_name="vBaseEnv", definition_ref="/MICROSAR/vBaseEnv")
    module_def.ar_path = "/MICROSAR/vBaseEnv"

    general = EcucContainerDef(short_name="vBaseEnvGeneral", lower_multiplicity=1,
                               upper_multiplicity=1, definition_ref="vBaseEnvGeneral")
    derivative = EcucContainerDef(short_name="vBaseEnvDerivativeInformation",
                                  lower_multiplicity=1, upper_multiplicity=-1,
                                  definition_ref="vBaseEnvGeneral/vBaseEnvDerivativeInformation")
    nested = EcucContainerDef(
        short_name=NAME, lower_multiplicity=0, upper_multiplicity=-1,
        definition_ref="vBaseEnvGeneral/vBaseEnvDerivativeInformation/" + NAME)
    nested.add_parameter(_param("vBaseEnvHwRegionSize"))
    stub = EcucContainerDef(short_name=NAME, lower_multiplicity=0, upper_multiplicity=-1,
                            definition_ref="vBaseEnvGeneral/" + NAME)

    derivative.add_sub_container(nested)
    general.add_sub_container(derivative)
    general.add_sub_container(stub)
    module_def.add_container(general)
    return module_def, general, stub, derivative, nested


def _shown_notice(panel):
    label = panel.findChild(QLabel, "definition_notice")
    return label.text() if label is not None and not label.isHidden() else ""


def test_an_empty_definition_names_the_one_that_has_parameters(panel):
    module_def, general, stub, _, _ = _module_with_twin()
    manager = ConfigurationManager(module_def)
    root = manager.create_container_instance(general, instance_name="General")
    instance = manager.create_container_instance(stub, parent=root, instance_name="Region_0")

    panel.show_instance(instance, stub, manager)

    notice = _shown_notice(panel)
    assert "vBaseEnvGeneral/vBaseEnvDerivativeInformation/" + NAME in notice
    assert "vBaseEnvDerivativeInformation" in notice


def test_a_definition_with_parameters_shows_no_notice(panel):
    module_def, general, _, derivative, nested = _module_with_twin()
    manager = ConfigurationManager(module_def)
    root = manager.create_container_instance(general, instance_name="General")
    mid = manager.create_container_instance(derivative, parent=root, instance_name="Deriv")
    instance = manager.create_container_instance(nested, parent=mid, instance_name="CORE0_ATCM")

    panel.show_instance(instance, nested, manager)

    assert _shown_notice(panel) == ""


def test_a_definition_without_parameters_still_says_so_without_a_twin(panel):
    module_def = EcucModuleDef(short_name="Demo", definition_ref="/MICROSAR/Demo")
    module_def.ar_path = "/MICROSAR/Demo"
    empty = EcucContainerDef(short_name="DemoEmpty", lower_multiplicity=1,
                             upper_multiplicity=1, definition_ref="DemoEmpty")
    module_def.add_container(empty)
    manager = ConfigurationManager(module_def)
    instance = manager.create_container_instance(empty, instance_name="Empty")

    panel.show_instance(instance, empty, manager)

    assert "没有任何参数" in _shown_notice(panel)
