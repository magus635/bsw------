"""Renderer.evaluate_value_at: an XPath expression's value with a configuration node as context."""
import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.generator.eb.renderer import Renderer, UnevaluableCondition

RESOURCES = {"M.Ids": ["X", "Y", "Z"]}


@pytest.fixture
def setup():
    module = EcucModuleDef(short_name="M", definition_ref="/V/M")
    group = EcucContainerDef(short_name="G", definition_ref="/V/M/G", lower_multiplicity=0, upper_multiplicity=4)
    group.add_parameter(EcucParameterDef(short_name="Id", param_type=EcucParameterType.STRING,
                                         definition_ref="/V/M/G/Id", default_value="static"))
    module.add_container(group)
    manager = ConfigurationManager(module)
    first = manager.create_container_instance(group, instance_name="G_0")
    second = manager.create_container_instance(group, instance_name="G_1")
    renderer = Renderer(strict=False)
    renderer.load_module(module, manager.configuration)
    root = renderer.symbol_table.get_module("M")

    def param_node(instance):
        container = next(n for n in [root] + root.get_children_recursive() if n.source is instance)
        return next(c for c in container.children if c.short_name == "Id")

    return renderer, param_node(first), param_node(second)


def test_a_list_indexed_by_a_path_inside_the_predicate(setup):
    """func(...)[expr containing '/']: used to fail with UnboundLocalError."""
    renderer, first, second = setup
    expr = "ecu:list('M.Ids')[node:fallback(node:current()/../@index, '0') + 1]"
    assert renderer.evaluate_value_at(first, expr, RESOURCES) == "X"
    assert renderer.evaluate_value_at(second, expr, RESOURCES) == "Y"


def test_a_number_computed_from_the_instance_index(setup):
    renderer, first, second = setup
    expr = "num:i(node:fallback(node:current()/../@index, '0') + 10)"
    assert int(renderer.evaluate_value_at(second, expr, RESOURCES)) == 11


def test_an_unsupported_function_raises(setup):
    renderer, first, _ = setup
    with pytest.raises(UnevaluableCondition):
        renderer.evaluate_value_at(first, "not:a:function('x')", RESOURCES)
