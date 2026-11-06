"""EB functions node:when and text:concat."""
import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.generator.eb.renderer import Renderer


@pytest.fixture
def at():
    """Evaluate an expression at the node of parameter P of a container that has Mode = 'SUB_LVDS'
    and a list parameter Ids = 1, 2."""
    module = EcucModuleDef(short_name="M", definition_ref="/V/M")
    group = EcucContainerDef(short_name="G", definition_ref="/V/M/G", lower_multiplicity=0, upper_multiplicity=4)
    for name in ("P", "Mode"):
        group.add_parameter(EcucParameterDef(short_name=name, param_type=EcucParameterType.STRING,
                                             definition_ref=f"/V/M/G/{name}"))
    group.add_parameter(EcucParameterDef(short_name="Ids", param_type=EcucParameterType.STRING,
                                         definition_ref="/V/M/G/Ids", upper_multiplicity=-1))
    module.add_container(group)
    manager = ConfigurationManager(module)
    instance = manager.create_container_instance(group, instance_name="G_0")
    manager.set_parameter_value(instance, "Mode", "SUB_LVDS")
    instance.add_multi_parameter_value("Ids", "1", "/V/M/G/Ids", 0)
    instance.add_multi_parameter_value("Ids", "2", "/V/M/G/Ids", 1)
    renderer = Renderer(strict=False)
    renderer.load_module(module, manager.configuration)
    root = renderer.symbol_table.get_module("M")
    container = next(n for n in [root] + root.get_children_recursive() if n.source is instance)
    node = next(c for c in container.children if c.short_name == "P")
    return lambda expr: renderer.evaluate_value_at(node, expr, {"M.Cs": ["CS0", "CS1"]})


def test_when_picks_the_branch_of_the_condition(at):
    assert at("node:when(1 = 1, 'yes', 'no')") == "yes"
    assert at("node:when(1 = 2, 'yes', 'no')") == "no"


def test_when_with_a_node_condition_as_in_the_port_definition(at):
    expr = "node:when(node:fallback(../Mode, 'LVDS') != 'SUB_LVDS', 'LDVS_RTERM_103ohm', 'SUBLDVS_RTERM_83ohm')"
    assert at(expr) == "SUBLDVS_RTERM_83ohm"
    assert at(expr.replace("../Mode", "../Missing")) == "LDVS_RTERM_103ohm"


def test_when_nested(at):
    assert at("node:when(1 = 2, 'a', node:when(2 = 2, 'b', 'c'))") == "b"


def test_when_condition_is_an_xpath_boolean(at):
    assert at("node:when(../Missing, 'set', 'empty')") == "empty"     # empty node set: false
    assert at("node:when(../Mode, 'set', 'empty')") == "set"


def test_concat_of_texts(at):
    assert at("text:concat('SLSO_', 'X')") == "SLSO_X"
    assert at("text:concat('Adc.AdcChannels_Adc', text:split('SARADC3', 'SARADC')[1])") == "Adc.AdcChannels_Adc3"


def test_concat_repeats_a_text_for_every_item_of_a_list(at):
    assert at("text:concat('SLSO_', ecu:list('M.Cs'))") == ["SLSO_CS0", "SLSO_CS1"]
    assert at("text:concat('SLSO_', ecu:list('M.Cs')[1])") == "SLSO_CS0"


def test_concat_pairs_two_lists(at):
    assert at("text:concat(../Ids/*, ecu:list('M.Cs'))") == ["1CS0", "2CS1"]


def test_concat_with_an_empty_sequence_gives_nothing(at):
    """An index past the end is an empty sequence: no half-built text such as 'SLSO_'."""
    assert at("text:concat('SLSO_', ecu:list('M.Missing')[1])") == []
    assert at("text:concat('SLSO_', ecu:list('M.Missing'))") == []
