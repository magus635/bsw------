"""Regression test for GEN-1: node:exists() must treat a configured 0.0 as present.

EB Tresos does not treat 0.0 as absent. A parameter with value '0.0' (e.g. a
timeout/offset of 0.0) is a legitimately configured parameter and node:exists()
must return True for it.
"""
import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..')))

try:
    import yaml  # noqa: F401
except ImportError:
    from unittest.mock import MagicMock
    sys.modules['yaml'] = MagicMock()

from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.builtins import BuiltinFunctions


def _make_builtins():
    symbol_table = SymbolTable()
    root = ConfigurationNode("root", "module", "/root")
    container = ConfigurationNode("TestContainer", "container", "/root/TestContainer")
    root.add_child(container)
    context_stack = ContextStack(container)
    return BuiltinFunctions(symbol_table, context_stack), container


def test_zero_float_value_exists():
    builtins, container = _make_builtins()
    p = ConfigurationNode(
        "ZeroOffset", "parameter", "/root/TestContainer/ZeroOffset", value="0.0"
    )
    container.add_child(p)
    assert builtins.node_exists(p) is True


def test_integer_zero_value_exists():
    builtins, container = _make_builtins()
    p = ConfigurationNode(
        "ZeroCount", "parameter", "/root/TestContainer/ZeroCount", value="0"
    )
    container.add_child(p)
    assert builtins.node_exists(p) is True


def test_none_value_does_not_exist():
    builtins, container = _make_builtins()
    p = ConfigurationNode(
        "Optional", "parameter", "/root/TestContainer/Optional", value=None
    )
    container.add_child(p)
    assert builtins.node_exists(p) is False
