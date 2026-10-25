"""'and' / 'or' inside a predicate belong to the predicate, not to the enclosing expression.

Before the fix, count(X[a or b]) > 0 was split at the 'or' inside the brackets.
"""
import pytest

from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable
from autosar_configurator.generator.eb.xpath_engine import XPathEngine


def _tree():
    root = ConfigurationNode(short_name="M", node_type="module", path="/M")
    config_set = ConfigurationNode(short_name="Set", node_type="container", path="/M/Set")
    root.add_child(config_set)
    for i, prio in enumerate((0, 10, 20)):
        c = ConfigurationNode(short_name=f"C_{i}", node_type="container", path=f"/M/Set/C_{i}")
        p = ConfigurationNode(short_name="Prio", node_type="parameter", path=f"/M/Set/C_{i}/Prio")
        p.value = str(prio)
        c.add_child(p)
        config_set.add_child(c)
    return root


@pytest.fixture
def renderer():
    r = Renderer(strict=False)
    r.symbol_table = SymbolTable()
    root = _tree()
    r.symbol_table.register_module("M", root)
    return r, root


@pytest.mark.parametrize("expr, expected", [
    ("count(Set/*[num:i(Prio) < 5 or num:i(Prio) > 15]) = 2", True),
    ("count(Set/*[num:i(Prio) < 5 or num:i(Prio) > 15]) > 2", False),
    ("count(Set/*[num:i(Prio) > 5 and num:i(Prio) < 15]) = 1", True),
    ("count(Set/*[num:i(Prio) > 5 and num:i(Prio) < 15]) > 1", False),
    ("true() and count(Set/*[num:i(Prio) > 25 or num:i(Prio) < 0]) > 0", False),
    ("false() or count(Set/*[num:i(Prio) = 10 and Prio = '10']) = 1", True),
    ("count(Set/*[(num:i(Prio) < 5) or (num:i(Prio) > 15)]) = 2", True),
])
def test_logic_inside_predicates(renderer, expr, expected):
    r, root = renderer
    assert r.evaluate_condition_at(root, expr, {}) is expected


def test_word_operator_inside_brackets_is_not_top_level():
    engine = XPathEngine(SymbolTable(), ContextStack(None))
    assert engine._find_word_outside_context("count(X[a or b]) > 0", "or") == -1
    assert engine._find_word_outside_context("X[a and b] and Y", "and") == len("X[a and b] ")
