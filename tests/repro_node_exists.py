"""Regression test for node:exists() handling of unset / None-valued parameters.

History: node:exists() used to report a parameter with a None value as existing
(returning True), which made templates emit configuration for parameters the user
never set. This test pins the corrected behavior:

  * a parameter with a concrete value  -> exists  (True)
  * a parameter with value None / unset -> absent  (False)

Previously this file was a one-shot repro that called sys.exit() and *failed* on
the now-correct behavior; it is now a normal pytest/unittest regression test.
"""
import os
import sys

# Add project root to path so the package imports resolve when run directly.
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

# Mock yaml module if missing to allow imports in minimal environments.
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

    # Existing parameter with a value.
    p1 = ConfigurationNode(
        "ParamWithValue", "parameter", "/root/TestContainer/ParamWithValue", value="10")
    container.add_child(p1)

    # Parameter with None value (optional param not present in the config).
    p2 = ConfigurationNode(
        "ParamWithNone", "parameter", "/root/TestContainer/ParamWithNone", value=None)
    container.add_child(p2)

    symbol_table.register_module("root", root)
    builtins = BuiltinFunctions(symbol_table, ContextStack(container))
    return builtins, p1, p2


def test_node_exists_with_value_is_true():
    builtins, p1, _ = _make_builtins()
    assert builtins.node_exists(p1) is True
    assert builtins.node_exists("ParamWithValue") is True


def test_node_exists_with_none_value_is_false():
    builtins, _, p2 = _make_builtins()
    # The core regression: a None-valued parameter must be reported as absent.
    assert builtins.node_exists(p2) is False
    assert builtins.node_exists("ParamWithNone") is False


if __name__ == "__main__":
    test_node_exists_with_value_is_true()
    test_node_exists_with_none_value_is_false()
    print("OK: node:exists() regression tests passed")
