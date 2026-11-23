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
    # id() of a removed configuration object -> the condition that was false (that of
    # the topmost removed node of its subtree)
    removed_conditions: dict[int, str] = field(default_factory=dict)
    # id() of a removed configuration object -> line of that condition in the
    # definition file (absent when unknown)
    removed_condition_lines: dict[int, int] = field(default_factory=dict)
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


def _conditions(node: ConfigurationNode, parent: ConfigurationNode,
                defs: dict[str, Any]) -> list[tuple[str, int | None]]:
    """Conditions to evaluate at ``node`` (its structural parent is ``parent``), each with
    its line in the definition file.

    - list wrapper of containers: the v:lst condition
    - container instance inside such a wrapper: its own v:ctr condition
    - container without a wrapper: both (the list and the node share their parent)
    - parameter / reference: its condition, except for the values inside a
      multi-value wrapper (the wrapper carries it)
    """
    definition = defs.get(node.definition_ref) if node.definition_ref else None
    if definition is None:
        return []
    mod_name = getattr(defs, 'module_name', None)
    in_wrapper_of_same_def = parent.is_wrapper and same_definition(parent.definition_ref, node.definition_ref, mod_name)
    own = (definition.enable_expr, getattr(definition, 'enable_line', None))
    if isinstance(definition, EcucContainerDef):
        listed = (definition.list_enable_expr, getattr(definition, 'list_enable_line', None))
        if node.is_wrapper:
            exprs = [listed]
        elif in_wrapper_of_same_def:
            exprs = [own]
        else:
            exprs = [listed, own]
    else:
        exprs = [] if in_wrapper_of_same_def else [own]
    return [(e, line) for e, line in exprs if e]


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
            if child.parent is wrapper and same_definition(
                child.definition_ref,
                wrapper.definition_ref,
                getattr(defs, "module_name", None) if hasattr(defs, "module_name") else None,
            ):
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
            failed, failed_line = next(((expr, line) for expr, line in _conditions(child, parent, defs)
                                        if not enabled(child, expr)), (None, None))
            if failed is None:
                walk(child, defs, removed)
                continue
            parent.remove_child(child)
            result.removed_paths.append(child.path)
            for n in _subtree(child):
                removed.add(id(n))
                if n.source is not None:
                    result.removed_sources.add(id(n.source))
                    result.removed_conditions.setdefault(id(n.source), failed)
                    if failed_line is not None:
                        result.removed_condition_lines.setdefault(id(n.source), failed_line)

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
    return _evaluate(modules, ecu_resources).removed_sources


def _evaluate(modules: dict[str, Any], ecu_resources: dict[str, Any] | None) -> EnableResult:
    from .renderer import Renderer

    renderer = Renderer(strict=False)
    for module_def, configuration in modules.values():
        if module_def is not None and configuration is not None:
            renderer.load_module(module_def, configuration)
    return apply_enable_conditions(renderer, [d for d, _ in modules.values()], ecu_resources)


@dataclass(frozen=True, order=True)
class DisabledContainer:
    """Topmost configured container of a subtree disabled by an ENABLE condition."""
    module: str
    path: str           # /<Module>/<Container>/... by short names
    definition: str     # short name of the container definition, e.g. MemoryBlock
    # the ENABLE condition that was false; not part of the identity, so the same
    # container compares equal whatever disabled it
    condition: str = field(default="", compare=False)
    condition_line: int | None = field(default=None, compare=False)   # in the definition file


def disabled_containers(modules: dict[str, Any],
                        ecu_resources: dict[str, Any] | None = None) -> list[DisabledContainer]:
    """Configured containers disabled by ENABLE conditions, topmost of each disabled
    subtree only, sorted by module and path.

    Args:
        modules: module name -> (EcucModuleDef, EcucModuleConfiguration) of the
            whole project (conditions may read other modules)
    """
    result = _evaluate(modules, ecu_resources)
    removed = result.removed_sources
    found: list[DisabledContainer] = []

    def walk(containers, path: str, module: str):
        for container in containers or []:
            container_path = f"{path}/{container.short_name}"
            if id(container) in removed:
                definition = (container.definition_ref or "").rstrip("/").rsplit("/", 1)[-1]
                found.append(DisabledContainer(module, container_path, definition,
                                               result.removed_conditions.get(id(container), ""),
                                               result.removed_condition_lines.get(id(container))))
            else:
                walk(container.sub_containers, container_path, module)

    for name, (_, configuration) in modules.items():
        if configuration is not None:
            walk(configuration.containers, f"/{name}", name)
    return sorted(found)


def container_paths(modules: dict[str, Any]) -> dict[tuple[str, str], list[str]]:
    """(module, container definition short name) -> paths of every configured container
    of that definition, at any depth, in the same path form as DisabledContainer."""
    paths: dict[tuple[str, str], list[str]] = {}

    def walk(containers, path: str, module: str):
        for container in containers or []:
            container_path = f"{path}/{container.short_name}"
            definition = (container.definition_ref or "").rstrip("/").rsplit("/", 1)[-1]
            paths.setdefault((module, definition), []).append(container_path)
            walk(container.sub_containers, container_path, module)

    for name, (_, configuration) in modules.items():
        if configuration is not None:
            walk(configuration.containers, f"/{name}", name)
    return paths


def is_disabled(path: str, topmost: set[str]) -> bool:
    """Whether ``path`` is one of the ``topmost`` disabled container paths or below one."""
    parts = path.split("/")
    return any("/".join(parts[:i]) in topmost for i in range(2, len(parts) + 1))


class EnableConditionEvaluator:
    """Lazy evaluator for XDM ENABLE expressions during configuration validation.

    Evaluates ``enable_expr`` / ``list_enable_expr`` on missing required parameters and
    sub-containers in the context of the container being validated (including cross-module
    XPath references when ``project_context`` provides other modules' managers).
    """

    def __init__(self, module_def: EcucModuleDef, configuration, project_context=None):
        self._module_def = module_def
        self._configuration = configuration
        self._project_context = project_context
        self._initialized = False
        self._renderer = None
        self._root = None
        self._by_source: dict[int, ConfigurationNode] = {}
        self._ecu_resources: dict[str, Any] = {}

    def _ensure_initialized(self) -> None:
        if self._initialized:
            return
        self._initialized = True
        if self._module_def is None or self._configuration is None:
            return

        from .renderer import Renderer

        renderer = Renderer(strict=False)
        loaded_modules: list[tuple[EcucModuleDef, Any]] = []
        seen_names: set[str] = set()

        def _add_module(mdef: EcucModuleDef, cfg) -> None:
            if mdef is None or cfg is None or mdef.short_name in seen_names:
                return
            seen_names.add(mdef.short_name)
            renderer.load_module(mdef, cfg)
            loaded_modules.append((mdef, cfg))

        _add_module(self._module_def, self._configuration)
        managers = getattr(self._project_context, "module_managers", None) or {}
        for mgr in managers.values():
            _add_module(getattr(mgr, "module_def", None), getattr(mgr, "configuration", None))

        for mdef, _ in loaded_modules:
            mod_root = renderer.symbol_table.get_module(mdef.short_name)
            if mod_root is not None:
                _lift_single_containers(mod_root, _definitions_by_ref(mdef))

        self._renderer = renderer
        self._root = renderer.symbol_table.get_module(self._module_def.short_name)
        if self._root is not None:
            self._by_source = {
                id(node.source): node
                for node in _subtree(self._root)
                if node.source is not None
            }
        self._ecu_resources = dict(getattr(self._project_context, "ecu_resources", None) or {})

    def _eval_at_probe(
        self,
        parent_node: ConfigurationNode | None,
        short_name: str,
        node_type: str,
        definition_ref: str,
        expr: str | None,
        is_wrapper: bool = False,
    ) -> bool:
        if not expr:
            return True
        if expr.replace(" ", "") == ALWAYS_FALSE:
            return False
        self._ensure_initialized()
        if self._renderer is None or parent_node is None:
            return True
        probe = ConfigurationNode(
            short_name=short_name,
            node_type=node_type,
            path=f"{parent_node.path}/{short_name}",
            definition_ref=definition_ref,
            parent=parent_node,
            is_wrapper=is_wrapper,
        )
        try:
            return bool(self._renderer.evaluate_condition_at(probe, expr, self._ecu_resources))
        except Exception:  # noqa: BLE001 - fail-safe: unevaluable conditions keep item enabled
            return True

    def is_param_enabled(self, container, param_def) -> bool:
        """Whether ``param_def`` is enabled inside ``container`` according to its ``enable_expr``."""
        expr = getattr(param_def, "enable_expr", None)
        if not expr:
            return True
        if expr.replace(" ", "") == ALWAYS_FALSE:
            return False
        self._ensure_initialized()
        cnode = self._by_source.get(id(container))
        if cnode is None:
            return True
        return self._eval_at_probe(
            cnode,
            param_def.short_name,
            "parameter",
            getattr(param_def, "definition_ref", "") or "",
            expr,
        )

    def is_container_enabled(self, parent_container, container_def: EcucContainerDef) -> bool:
        """Whether ``container_def`` is enabled under ``parent_container`` (None for module root)."""
        list_expr = getattr(container_def, "list_enable_expr", None)
        own_expr = getattr(container_def, "enable_expr", None)
        in_list = getattr(container_def, "in_list", False)
        check_own = bool(own_expr and not in_list)
        if not list_expr and not check_own:
            return True
        if list_expr and list_expr.replace(" ", "") == ALWAYS_FALSE:
            return False
        if check_own and own_expr and own_expr.replace(" ", "") == ALWAYS_FALSE:
            return False
        self._ensure_initialized()
        parent_node = self._root if parent_container is None else self._by_source.get(id(parent_container))
        if parent_node is None:
            return True
        def_ref = getattr(container_def, "definition_ref", "") or ""
        if list_expr and not self._eval_at_probe(
            parent_node, container_def.short_name, "container", def_ref, list_expr, is_wrapper=True
        ):
            return False
        if check_own and not self._eval_at_probe(
            parent_node, container_def.short_name, "container", def_ref, own_expr, is_wrapper=False
        ):
            return False
        return True
