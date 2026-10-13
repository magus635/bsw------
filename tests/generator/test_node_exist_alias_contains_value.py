"""node:exist (alias of node:exists) and node:containsValue."""
from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable


def _builtins():
    root = ConfigurationNode("root", "module", "/root")
    container = ConfigurationNode("C", "container", "/root/C")
    root.add_child(container)
    return BuiltinFunctions(SymbolTable(), ContextStack(container)), container


def _param(container, name, value):
    p = ConfigurationNode(name, "parameter", f"/root/C/{name}", value=value)
    container.add_child(p)
    return p


def test_node_exist_is_registered_as_node_exists():
    b, c = _builtins()
    p = _param(c, "P", "1")
    assert b.has("node:exist")
    assert b.call("node:exist", p) is True
    assert b.call("node:exist", None) is False


def test_contains_value_on_node_list():
    b, c = _builtins()
    nodes = [_param(c, "A", "X"), _param(c, "B", "Y")]
    assert b.call("node:containsValue", nodes, "Y") is True
    assert b.call("node:containsValue", nodes, "Z") is False


def test_contains_value_single_node_and_empty():
    b, c = _builtins()
    assert b.call("node:containsValue", _param(c, "A", "X"), "X") is True
    assert b.call("node:containsValue", [], "X") is False
    assert b.call("node:containsValue", None, "X") is False
