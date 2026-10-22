"""Definition ENABLE conditions (EB tresos XDM ``<a:da name="ENABLE" type="XPath">``).

An item whose condition is false is not part of the configuration: EB keeps its
data in the XDM but neither templates nor the EPC export see it. Here such nodes
are removed from the configuration tree, top-down in document order, after all
modules are loaded and before any template is rendered. The removed nodes'
configuration objects are reported so the EPC export can leave them out as well.

A condition that cannot be evaluated keeps its item enabled (the behaviour before
conditions were evaluated) and produces a warning, once per expression.
"""
import logging
from collections.abc import Iterable
from dataclasses import dataclass, field
from typing import Any

from ...core.model.definition_model import EcucContainerDef, EcucModuleDef
from ...core.model.definition_refs import module_relative, same_definition
from .symbol_table import ConfigurationNode

logger = logging.getLogger(__name__)

ALWAYS_FALSE = 'false()'


@dataclass
class EnableResult:
    removed_paths: list[str] = field(default_factory=list)
    # id() of the configuration objects (containers, parameter and reference values)
    # in removed subtrees
    removed_sources: set[int] = field(default_factory=set)
    warnings: list[str] = field(default_factory=list)


class _DefinitionsByRef(dict):
    """Definitions keyed by their path inside the module: a configuration value finds its
    definition whatever the form of its DEFINITION-REF (relative, /AUTOSAR/EcucDefs/...,
    or the definition file's own /<AR-PACKAGE>/<Module>/... of EB values)."""

    def __init__(self, module_name: str):
        super().__init__()
        self.module_name = module_name

    def __setitem__(self, ref, definition):
        super().__setitem__(module_relative(ref, self.module_name), definition)

    def get(self, ref, default=None):
        return super().get(module_relative(ref, self.module_name), default)


def _definitions_by_ref(module_def: EcucModuleDef) -> dict[str, Any]:
    """definition_ref -> container / parameter / reference definition of a module."""
    defs: dict[str, Any] = _DefinitionsByRef(module_def.short_name)

    def walk(container_def: EcucContainerDef):
        defs[container_def.definition_ref] = container_def
        for d in list(container_def.parameters.values()) + list(container_def.references.values()):
            defs[d.definition_ref] = d
        for sub in container_def.sub_containers.values():
            walk(sub)

    for param_def in getattr(module_def, 'parameters', {}).values():
        defs[param_def.definition_ref] = param_def
    for container_def in module_def.containers.values():
        walk(container_def)
    return defs


def _has_conditions(defs: dict[str, Any]) -> bool:
    return any(getattr(d, 'enable_expr', None) or getattr(d, 'list_enable_expr', None)
               for d in defs.values())


def _conditions(node: ConfigurationNode, parent: ConfigurationNode, defs: dict[str, Any]) -> list[str]:
    """Conditions to evaluate at ``node`` (its structural parent is ``parent``).

    - list wrapper of containers: the v:lst condition
    - container instance inside such a wrapper: its own v:ctr condition
    - container without a wrapper: both (the list and the node share their parent)
    - parameter / reference: its condition, except for the values inside a
      multi-value wrapper (the wrapper carries it)
    """
    definition = defs.get(node.definition_ref) if node.definition_ref else None
    if definition is None:
        return []
    in_wrapper_of_same_def = parent.is_wrapper and same_definition(parent.definition_ref, node.definition_ref)
    if isinstance(definition, EcucContainerDef):
        if node.is_wrapper:
            exprs = [definition.list_enable_expr]
        elif in_wrapper_of_same_def:
            exprs = [definition.enable_expr]
        else:
            exprs = [definition.list_enable_expr, definition.enable_expr]
    else:
        exprs = [] if in_wrapper_of_same_def else [definition.enable_expr]
    return [e for e in exprs if e]


def _subtree(node: ConfigurationNode) -> list[ConfigurationNode]:
    return [node] + node.get_children_recursive()


def _purge_names(root: ConfigurationNode, removed: set[int]):
    """Drop name-map entries (aliases) that point into removed subtrees."""
    for node in _subtree(root):
        names = node._children_by_name
        if any(id(v) in removed for v in names.values()):
            node._children_by_name = {k: v for k, v in names.items() if id(v) not in removed}
            for child in reversed(node.children):
                node._children_by_name.setdefault(child.short_name, child)


def _lift_single_containers(root: ConfigurationNode, defs: dict[str, Any]) -> list[tuple]:
    """Let '..' of single (non-list) container instances reach their real parent.

    The configuration tree puts every sub-container instance under a wrapper node;
    in EB only list items (v:lst) have that level, and a single v:ctr sits directly
    in its parent, which is what the conditions' relative paths count on. Returns
    (node, original parent) pairs for restoring.
    """
    lifted = []
    for wrapper in _subtree(root):
        if not wrapper.is_wrapper or wrapper.parent is None:
            continue
        definition = defs.get(wrapper.definition_ref)
        if not isinstance(definition, EcucContainerDef) or definition.in_list:
            continue
        for child in wrapper.children:
            if child.parent is wrapper and same_definition(child.definition_ref, wrapper.definition_ref):
                lifted.append((child, wrapper))
                child.parent = wrapper.parent
    return lifted


def apply_enable_conditions(renderer, module_defs: Iterable[EcucModuleDef],
                            ecu_resources: dict[str, Any] | None = None) -> EnableResult:
    """Evaluate the ENABLE conditions of the loaded modules and remove disabled nodes.

    Args:
        renderer: eb.renderer.Renderer with every module of the project loaded
        module_defs: definitions of those modules
        ecu_resources: ecu:get()/ecu:list() data for the conditions
    """
    result = EnableResult()
    reported: set[str] = set()

    def enabled(node: ConfigurationNode, expr: str) -> bool:
        if expr.replace(' ', '') == ALWAYS_FALSE:
            return False
        try:
            return renderer.evaluate_condition_at(node, expr, ecu_resources)
        except Exception as e:  # noqa: BLE001 - keep the item, report the condition
            if expr not in reported:
                reported.add(expr)
                result.warnings.append(
                    f"ENABLE condition of {node.path} could not be evaluated ({e}); "
                    f"kept enabled: {expr}")
            return True

    def walk(parent: ConfigurationNode, defs: dict[str, Any], removed: set[int]):
        for child in list(parent.children):
            if all(enabled(child, expr) for expr in _conditions(child, parent, defs)):
                walk(child, defs, removed)
                continue
            parent.remove_child(child)
            result.removed_paths.append(child.path)
            for n in _subtree(child):
                removed.add(id(n))
                if n.source is not None:
                    result.removed_sources.add(id(n.source))

    seen = set()
    for module_def in module_defs:
        if module_def is None or module_def.short_name in seen:
            continue
        seen.add(module_def.short_name)
        root = renderer.symbol_table.get_module(module_def.short_name)
        defs = _definitions_by_ref(module_def)
        if root is None or not _has_conditions(defs):
            continue
        removed: set[int] = set()
        lifted = _lift_single_containers(root, defs)
        try:
            walk(root, defs, removed)
        finally:
            for node, parent in lifted:
                node.parent = parent
        if removed:
            _purge_names(root, removed)

    if result.removed_paths:
        renderer.symbol_table.rebuild_path_index()
        logger.debug("ENABLE conditions: %d item(s) disabled", len(result.removed_paths))
    # warnings are reported by the caller (CodeGenerator logs each once per run)
    return result


def disabled_configuration_objects(modules: dict[str, Any],
                                   ecu_resources: dict[str, Any] | None = None) -> set[int]:
    """id() of the configuration objects whose ENABLE condition is false.

    Args:
        modules: module name -> (EcucModuleDef, EcucModuleConfiguration) of the
            whole project (conditions may read other modules)
    """
    from .renderer import Renderer

    renderer = Renderer(strict=False)
    for module_def, configuration in modules.values():
        if module_def is not None and configuration is not None:
            renderer.load_module(module_def, configuration)
    return apply_enable_conditions(
        renderer, [d for d, _ in modules.values()], ecu_resources).removed_sources


@dataclass(frozen=True, order=True)
class DisabledContainer:
    """Topmost configured container of a subtree disabled by an ENABLE condition."""
    module: str
    path: str           # /<Module>/<Container>/... by short names
    definition: str     # short name of the container definition, e.g. MemoryBlock


def disabled_containers(modules: dict[str, Any],
                        ecu_resources: dict[str, Any] | None = None) -> list[DisabledContainer]:
    """Configured containers disabled by ENABLE conditions, topmost of each disabled
    subtree only, sorted by module and path.

    Args:
        modules: module name -> (EcucModuleDef, EcucModuleConfiguration) of the
            whole project (conditions may read other modules)
    """
    removed = disabled_configuration_objects(modules, ecu_resources)
    found: list[DisabledContainer] = []

    def walk(containers, path: str, module: str):
        for container in containers or []:
            container_path = f"{path}/{container.short_name}"
            if id(container) in removed:
                definition = (container.definition_ref or "").rstrip("/").rsplit("/", 1)[-1]
                found.append(DisabledContainer(module, container_path, definition))
            else:
                walk(container.sub_containers, container_path, module)

    for name, (_, configuration) in modules.items():
        if configuration is not None:
            walk(configuration.containers, f"/{name}", name)
    return sorted(found)
