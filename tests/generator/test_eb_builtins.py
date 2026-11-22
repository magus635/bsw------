"""Unit and template-rendering tests for EB built-in functions (node:isconsecutive)."""
import pytest

from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.errors import TemplateExecutionError
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable


def _builtins():
    root = ConfigurationNode("Eth", "module", "/Eth")
    container = ConfigurationNode("EthCtrlConfig", "container", "/Eth/EthConfigSet/EthCtrlConfig")
    root.add_child(container)
    return BuiltinFunctions(SymbolTable(), ContextStack(container)), container


def _idx_nodes(container, values):
    nodes = []
    for i, val in enumerate(values):
        n = ConfigurationNode(f"Fifo_{i}", "container", f"{container.path}/Fifo_{i}")
        p = ConfigurationNode(
            "EthCtrlConfigEgressFifoIdx",
            "parameter",
            f"{n.path}/EthCtrlConfigEgressFifoIdx",
            value=val,
        )
        n.add_child(p)
        container.add_child(n)
        nodes.append(p)
    return nodes


def test_node_isconsecutive_basic_and_unsorted():
    b, c = _builtins()
    assert b.has("node:isconsecutive")
    assert b.call("node:isconsecutive", _idx_nodes(c, [0, 1, 2]), 0) is True
    assert b.call("node:isconsecutive", _idx_nodes(c, [2, 0, 1]), 0) is True
    assert b.call("node:isconsecutive", _idx_nodes(c, [1, 2, 3]), 1) is True
    assert b.call("node:isconsecutive", _idx_nodes(c, [1, 2, 3]), 0) is False


def test_node_isconsecutive_gaps_duplicates_and_empty():
    b, c = _builtins()
    assert b.call("node:isconsecutive", _idx_nodes(c, [0, 2]), 0) is False
    assert b.call("node:isconsecutive", _idx_nodes(c, [0, 0, 1]), 0) is False
    assert b.call("node:isconsecutive", [], 0) is True
    assert b.call("node:isconsecutive", None, 0) is True
    assert b.call("node:isconsecutive", [0], 0) is True
    assert b.call("node:isconsecutive", 0, 0) is True
    assert b.call("node:isconsecutive", [1], 0) is False
    assert b.call("node:isconsecutive", _idx_nodes(c, ["00", "01", "08", "02", "03", "04", "05", "06", "07"]), 0) is True
    assert b.call("node:isconsecutive", [True, False], 0) is False


def _render_eth_fifo_template(fifo_indices):
    renderer = Renderer(strict=False)
    st = renderer.symbol_table
    eth = ConfigurationNode("Eth", "module", "/Eth")
    cfg_set = ConfigurationNode("EthConfigSet", "container", "/Eth/EthConfigSet")
    ctrl = ConfigurationNode("EthCtrlConfig_0", "container", "/Eth/EthConfigSet/EthCtrlConfig_0")
    egress = ConfigurationNode("EthCtrlConfigEgress", "container", "/Eth/EthConfigSet/EthCtrlConfig_0/EthCtrlConfigEgress")
    for idx, val in enumerate(fifo_indices):
        fifo = ConfigurationNode(
            f"EthCtrlConfigEgressFifo_{idx}",
            "container",
            f"{egress.path}/EthCtrlConfigEgressFifo_{idx}",
        )
        fifo_idx = ConfigurationNode(
            "EthCtrlConfigEgressFifoIdx",
            "parameter",
            f"{fifo.path}/EthCtrlConfigEgressFifoIdx",
            value=val,
        )
        fifo.add_child(fifo_idx)
        egress.add_child(fifo)
    ctrl.add_child(egress)
    cfg_set.add_child(ctrl)
    eth.add_child(cfg_set)
    st.register_module("Eth", eth)

    tpl = (
        '[!SELECT "/Eth/EthConfigSet/EthCtrlConfig_0"!]\n'
        '[!VAR "EgressVal" = "node:isconsecutive(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*/EthCtrlConfigEgressFifoIdx,0)"!]\n'
        '[!IF "($EgressVal) = \'false\'"!]\n'
        '[!ERROR!]88-000-08-ERROR[!ENDERROR!]\n'
        '[!ENDIF!]\n'
        '[!ENDSELECT!]\n'
        'OK:[!"$EgressVal"!]'
    )
    output = renderer.render(tpl, module_name="Eth")
    return output, renderer


def test_node_isconsecutive_end_to_end_template_rendering():
    out, renderer = _render_eth_fifo_template([2, 0, 1])
    assert "node:isconsecutive" not in renderer._builtins.unimplemented_calls
    assert "OK:true" in out or "OK:True" in out

    with pytest.raises(TemplateExecutionError, match="88-000-08-ERROR"):
        _render_eth_fifo_template([0, 2])
