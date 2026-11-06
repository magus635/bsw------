"""Defaults an EB definition computes (XDM ``<a:da name="DEFAULT" type="XPath">``), evaluated for a
new container instance in its place in the configuration, as EB does when it creates one.

An expression often depends on where the instance is (``node:current()/../@index``), on other
modules or on the chip's ``ecu:list``/``ecu:get`` data, so it is evaluated with the EB engine on
the whole configuration, the parameter's node as context.
"""
from typing import Any, Dict, Iterable, Tuple

from ...core.parser.xdm_expression_resolver import typed_value
from .renderer import Renderer


def computed_defaults(modules: Iterable[Tuple[Any, Any]], instance, container_def, names,
                      ecu_resources: Dict[str, Any] = None) -> Tuple[Dict[str, Any], Dict[str, str]]:
    """(values, failures) of the XPath defaults of parameters ``names`` of ``instance``.

    Args:
        modules: (module definition, configuration) pairs; ``instance`` is in one of them
        container_def: the definition of ``instance``
        ecu_resources: data of ecu:list() / ecu:get()

    Returns:
        name -> value converted to the parameter type, and name -> why it has no value
    """
    renderer = Renderer(strict=False)
    module_names = []
    for module_def, configuration in modules:
        renderer.load_module(module_def, configuration)
        module_names.append(module_def.short_name)
    container = _node_of(renderer, module_names, instance)

    values: Dict[str, Any] = {}
    failures: Dict[str, str] = {}
    for name in names:
        param_def = container_def.parameters[name]
        node = next((c for c in container.children if c.short_name == name), None) if container else None
        if node is None:
            failures[name] = "not found in the configuration tree"
            continue
        try:
            value = renderer.evaluate_value_at(node, param_def.default_expr, ecu_resources)
        except Exception as e:  # noqa: BLE001 - one expression must not stop the others
            failures[name] = f"{type(e).__name__}: {e}"
            continue
        value = typed_value(_single(value), param_def.param_type)
        if value is None or value == "":
            failures[name] = f"no value from {param_def.default_expr}"
        elif isinstance(value, str) and value.lstrip().startswith("->"):
            # EB's deferred "->path" (node:fallback's first argument) came back as text
            failures[name] = f"deferred expression not evaluated: {value}"
        else:
            values[name] = value
    return values, failures


def _node_of(renderer: Renderer, module_names, instance):
    for name in module_names:
        root = renderer.symbol_table.get_module(name)
        if root is None:
            continue
        for node in [root] + root.get_children_recursive():
            if node.source is instance:
                return node
    return None


def _single(value: Any) -> Any:
    """A node set's first item, and a node's value."""
    if isinstance(value, (list, tuple)):
        value = value[0] if value else None
    return getattr(value, "value", value)
