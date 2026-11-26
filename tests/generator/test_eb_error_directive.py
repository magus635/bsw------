"""Tests for expression interpolation inside EB [!ERROR!] and [!ASSERT!] blocks."""
import pytest

from autosar_configurator.generator.eb.errors import TemplateExecutionError, TemplateParseError
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode


def _renderer_with_can_node(child_name: str = "CN_Test_Tx") -> Renderer:
    renderer = Renderer(strict=True)
    can_root = ConfigurationNode(short_name="Can", node_type="module", path="/Can")
    cfg_set = ConfigurationNode(short_name="CanConfigSet", node_type="container", path="/Can/CanConfigSet")
    hoh_list = ConfigurationNode(
        short_name="CanHardwareObject",
        node_type="container_list",
        path="/Can/CanConfigSet/CanHardwareObject",
    )
    hoh = ConfigurationNode(
        short_name=child_name,
        node_type="container",
        path=f"/Can/CanConfigSet/CanHardwareObject/{child_name}",
    )
    can_root.add_child(cfg_set)
    cfg_set.add_child(hoh_list)
    hoh_list.add_child(hoh)
    renderer.symbol_table.register_module("Can", can_root)
    return renderer


def test_error_block_evaluates_quoted_output_expressions():
    renderer = _renderer_with_can_node("CN_Test_Tx")
    tpl = (
        '[!SELECT "CanConfigSet"!][!LOOP "CanHardwareObject/*"!]'
        '[!ERROR!]080-00-04-ERROR: [!"node:name(.)"!] failed[!ENDERROR!]'
        '[!ENDLOOP!][!ENDSELECT!]'
    )
    with pytest.raises(TemplateExecutionError) as exc_info:
        renderer.render(tpl, module_name="Can")

    msg = str(exc_info.value)
    assert "CN_Test_Tx failed" in msg
    assert "node:name(.)" not in msg


def test_assert_block_evaluates_quoted_output_expressions():
    renderer = _renderer_with_can_node("CN_Assert_Rx")
    tpl = (
        '[!SELECT "CanConfigSet"!][!LOOP "CanHardwareObject/*"!]'
        '[!ASSERT "1 = 2"!]Bad node: [!"node:name(.)"!][!ENDASSERT!]'
        '[!ENDLOOP!][!ENDSELECT!]'
    )
    with pytest.raises(TemplateExecutionError) as exc_info:
        renderer.render(tpl, module_name="Can")

    assert isinstance(exc_info.value.cause, TemplateParseError)
    msg = str(exc_info.value)
    assert "Bad node: CN_Assert_Rx" in msg
    assert "node:name(.)" not in msg
