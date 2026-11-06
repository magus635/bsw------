"""Two definitions that share a SHORT-NAME are shown as two distinct nodes, each
listing only its own instances (vBaseEnv: vBaseEnvMemLayoutHwRegion directly under
vBaseEnvGeneral and again under vBaseEnvDerivativeInformation)."""
import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView

NAME = "vBaseEnvMemLayoutHwRegion"


def _param(name):
    return EcucParameterDef(short_name=name, param_type=EcucParameterType.INTEGER,
                            lower_multiplicity=0, upper_multiplicity=1)


@pytest.fixture
def manager():
    module_def = EcucModuleDef(short_name="vBaseEnv", definition_ref="/MICROSAR/vBaseEnv")
    module_def.ar_path = "/MICROSAR/vBaseEnv"

    general = EcucContainerDef(short_name="vBaseEnvGeneral", lower_multiplicity=1,
                               upper_multiplicity=1,
                               definition_ref="vBaseEnvGeneral")
    derivative = EcucContainerDef(short_name="vBaseEnvDerivativeInformation", lower_multiplicity=1,
                                  upper_multiplicity=-1,
                                  definition_ref="vBaseEnvGeneral/vBaseEnvDerivativeInformation")

    nested = EcucContainerDef(short_name=NAME, lower_multiplicity=0, upper_multiplicity=-1,
                               definition_ref="vBaseEnvGeneral/vBaseEnvDerivativeInformation/" + NAME)
    nested.add_parameter(_param("vBaseEnvHwRegionSize"))
    stub = EcucContainerDef(short_name=NAME, lower_multiplicity=0, upper_multiplicity=-1,
                            definition_ref="vBaseEnvGeneral/" + NAME)

    derivative.add_sub_container(nested)
    general.add_sub_container(derivative)
    general.add_sub_container(stub)
    module_def.add_container(general)

    manager = ConfigurationManager(module_def)
    general_instance = manager.create_container_instance(general, instance_name="General")
    derivative_instance = manager.create_container_instance(derivative, parent=general_instance,
                                                          instance_name="Derivative")
    manager.create_container_instance(nested, parent=derivative_instance, instance_name="CORE0_ATCM")
    manager.create_container_instance(stub, parent=general_instance, instance_name="CORE0_ATCM")
    return module_def, manager


@pytest.fixture
def tree(qtbot, manager):
    module_def, config_manager = manager
    widget = DaVinciTreeView()
    qtbot.addWidget(widget)
    widget.set_module_def(module_def, config_manager)
    return widget


def _def_nodes(tree):
    """Every DEF node in the tree, by its definition."""
    found = {}

    def walk(item):
        data = item.data(0, 0x0100)  # Qt.UserRole
        if isinstance(data, dict) and data.get("type") == "DEF":
            found.setdefault(data["def"].definition_ref, item)
        for i in range(item.childCount()):
            walk(item.child(i))

    for i in range(tree.topLevelItemCount()):
        walk(tree.topLevelItem(i))
    return found


def test_both_definitions_get_their_own_node(tree):
    nodes = _def_nodes(tree)
    assert "vBaseEnvGeneral/" + NAME in nodes
    assert "vBaseEnvGeneral/vBaseEnvDerivativeInformation/" + NAME in nodes


def test_each_node_lists_only_its_own_instances(tree):
    module_def, config_manager = _module_and_manager(tree)
    nodes = _def_nodes(tree)
    stub_node = nodes["vBaseEnvGeneral/" + NAME]
    nested_node = nodes["vBaseEnvGeneral/vBaseEnvDerivativeInformation/" + NAME]
    assert [c.text(0) for c in _children(stub_node) if c.text(0).startswith(("✅", "⚠️"))] == \
        ["✅ CORE0_ATCM"]
    assert [c.text(0) for c in _children(nested_node) if c.text(0).startswith(("✅", "⚠️"))] == \
        ["✅ CORE0_ATCM"]


def test_same_named_nodes_are_told_apart(tree):
    nodes = _def_nodes(tree)
    stub_text = nodes["vBaseEnvGeneral/" + NAME].text(0)
    nested_text = nodes["vBaseEnvGeneral/vBaseEnvDerivativeInformation/" + NAME].text(0)
    assert stub_text != nested_text
    assert "DerivativeInformation" in nested_text


def test_a_definition_without_parameters_is_marked(tree):
    nodes = _def_nodes(tree)
    assert "0 parameters" in nodes["vBaseEnvGeneral/" + NAME].toolTip(0)


def _children(item):
    return [item.child(i) for i in range(item.childCount())]


def _module_and_manager(tree):
    data = tree.topLevelItem(0).data(0, 0x0100)
    return data["def"], data["manager"]
