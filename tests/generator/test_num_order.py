"""num:order sorts numerically and, like EB tresos, removes duplicate values."""
from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.symbol_table import (
    ConfigurationNode,
    SymbolTable,
)


def _builtins():
    root = ConfigurationNode("root", "module", "/root")
    return BuiltinFunctions(SymbolTable(), ContextStack(root))


def test_sorts_numerically():
    assert _builtins().num_order(['10', '2', '0x3']) == ['2', '0x3', '10']


def test_duplicate_values_are_removed():
    # Os ORTI: priorities "0,100,1,0" -> 0, 1, 100 (each priority listed once)
    assert _builtins().num_order(['0', '100', '1', '0']) == ['0', '1', '100']
    assert _builtins().num_order(['0', '00', 0]) == ['0']


def test_non_numeric_values_are_kept_apart():
    assert _builtins().num_order(['a', 'b', 'a']) == ['a', 'b']


def test_configuration_nodes_are_not_merged():
    nodes = [ConfigurationNode(f"P{i}", "parameter", f"/root/P{i}", value=v) for i, v in enumerate([3, 1, 3])]
    assert [n.short_name for n in _builtins().num_order(nodes)] == ["P1", "P0", "P2"]
