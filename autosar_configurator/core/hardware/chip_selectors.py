"""
Chip selector parameters (update-unified-chip-selection)

A chip YAML's ``selectors`` section declares, per ``<Module>.<parameter>``, the
value a module's chip selector parameter takes for that chip (e.g.
``Resource.ResourceSubderivative: THA6412_BGA516``, ``Os.OsResourceSubderivative:
Os_THA6412``).  The project's ``selected_chip`` is the single source of the chip;
the selector parameters follow it:

* ``apply_selectors`` writes the declared values into the loaded modules.  Only
  called when the user explicitly selects a chip; opening or importing a project
  only checks (``ecu_resource_diagnostics.check_selectors``).
* ``chip_from_selectors`` finds the chip of an older project that has no
  ``selected_chip`` from its configured selector values.
* ``is_selector`` tells the configuration panel which parameters are read-only.
"""
import logging
from dataclasses import dataclass, field
from typing import Any, Iterable, List, Optional, Tuple

from ..model import definition_refs as defrefs

logger = logging.getLogger(__name__)


@dataclass
class SelectorResult:
    """What ``apply_selectors`` did: ``changed`` holds ``(key, old, new)`` for every
    value written (``old`` is None for a value that did not exist), ``skipped``
    holds ``(key, reason)`` for every declared selector that was not written."""
    changed: List[Tuple[str, Any, str]] = field(default_factory=list)
    skipped: List[Tuple[str, str]] = field(default_factory=list)

    def messages(self) -> List[str]:
        lines = [f"{key}: {'(unset)' if old is None else old} -> {new}" for key, old, new in self.changed]
        lines += [f"{key} not written: {reason}" for key, reason in self.skipped]
        return lines


def _walk(containers) -> Iterable:
    for container in containers or []:
        yield container
        yield from _walk(getattr(container, "sub_containers", []))


def _not_allowed(param_def, value: str) -> Optional[str]:
    literals = getattr(param_def, "literals", None)
    if literals and value not in literals:
        return f"'{value}' is not an allowed value of the definition"
    return None


def _apply_module_level(manager, key: str, param: str, declared: str, result: SelectorResult):
    configuration = manager.configuration
    param_def = manager.module_def.parameters[param]
    reason = _not_allowed(param_def, declared)
    if reason:
        result.skipped.append((key, reason))
        return
    current = configuration.parameter_values.get(param)
    old = current.value if current is not None else None
    if current is not None and str(old) == declared:
        return
    definition_ref = (current.definition_ref if current is not None
                      else defrefs.absolute_ref(manager.module_def, param_def.definition_ref))
    configuration.set_parameter_value(param, declared, definition_ref)
    configuration.is_modified = True
    result.changed.append((key, old, declared))


def _holders(manager, param: str) -> List:
    """Container values whose definition has ``param``."""
    holders = []
    for container in _walk(manager.configuration.containers):
        container_def = manager.get_container_def(container.definition_ref)
        if container_def is not None and param in container_def.parameters:
            holders.append(container)
    return holders


def _definition_chain(container_defs, param: str) -> Optional[List]:
    """Container definitions from the top down to the one defining ``param``."""
    for container_def in container_defs:
        if param in container_def.parameters:
            return [container_def]
        below = _definition_chain(container_def.sub_containers.values(), param)
        if below:
            return [container_def] + below
    return None


def _create_holder(manager, param: str):
    """Create the missing container instances down to the one defining ``param``
    (e.g. ResourceGeneral of a module just added).  Only along single-instance
    containers, where there is no choice of which instance to create."""
    chain = _definition_chain(manager.module_def.containers.values(), param)
    if not chain or any(cdef.is_multiple for cdef in chain):
        return None
    parent = None
    siblings = manager.configuration.containers
    for cdef in chain:
        existing = [c for c in siblings
                    if (c.definition_ref or "").rstrip("/").rsplit("/", 1)[-1] == cdef.short_name]
        if len(existing) > 1:
            return None
        instance = existing[0] if existing else manager.create_container_instance(cdef, parent)
        parent, siblings = instance, instance.sub_containers
    return parent


def _apply_container_level(manager, key: str, param: str, declared: str, result: SelectorResult):
    from ..config_manager import ValidationError

    targets = [c for c in _walk(manager.configuration.containers) if param in c.parameter_values]
    created = None
    if not targets:
        holders = _holders(manager, param)
        if not holders:
            try:
                created = _create_holder(manager, param)
            except ValidationError as e:     # multiplicity, names
                result.skipped.append((key, str(e)))
                return
            holders = [created] if created is not None else []
        if len(holders) != 1:
            result.skipped.append((key, "no container holds the parameter" if not holders
                                   else f"{len(holders)} containers could hold the parameter"))
            return
        targets = holders
    for container in targets:
        current = container.parameter_values.get(param)
        # A container created here holds the definition default, not a user's value
        old = current.value if current is not None and container is not created else None
        if old is not None and str(old) == declared:
            continue
        try:
            manager.set_parameter_value(container, param, declared)
        except ValidationError as e:     # value or definition not usable
            result.skipped.append((key, str(e)))
            continue
        result.changed.append((key, old, declared))


def apply_selectors(project, chip, modules: Optional[Iterable[str]] = None) -> SelectorResult:
    """Set every selector parameter ``chip`` declares to the declared value.

    Args:
        project: WorkspaceProject (uses ``module_managers``)
        chip: ChipDefinition of the selected chip, or None
        modules: limit to these module names (e.g. a module just added); None = all
    """
    result = SelectorResult()
    selectors = getattr(chip, "selectors", None) or {}
    wanted = set(modules) if modules is not None else None
    managers = getattr(project, "module_managers", {}) or {}
    for key in sorted(selectors):
        module, _, param = key.partition(".")
        if wanted is not None and module not in wanted:
            continue
        declared = str(selectors[key])
        manager = managers.get(module)
        if manager is None or getattr(manager, "configuration", None) is None:
            result.skipped.append((key, f"module {module} is not loaded"))
            continue
        module_def = getattr(manager, "module_def", None)
        if module_def is not None and param in (getattr(module_def, "parameters", None) or {}):
            _apply_module_level(manager, key, param, declared, result)
        else:
            _apply_container_level(manager, key, param, declared, result)
    for line in result.messages():
        logger.info("Chip selector %s", line)
    return result


def configured_selector_values(project, key: str) -> List[Any]:
    """Configured values of the selector ``<Module>.<parameter>`` (module-level and
    container parameters)."""
    module, _, param = key.partition(".")
    manager = (getattr(project, "module_managers", {}) or {}).get(module)
    configuration = getattr(manager, "configuration", None) if manager else None
    if configuration is None:
        return []
    values = [c.parameter_values[param].value for c in _walk(configuration.containers)
              if param in c.parameter_values and c.parameter_values[param].value not in (None, "")]
    module_param = (getattr(configuration, "parameter_values", {}) or {}).get(param)
    if module_param is not None and module_param.value not in (None, ""):
        values.append(module_param.value)
    return values


def chip_from_selectors(project, chips) -> Optional[str]:
    """The one chip whose declared selectors match the project's configuration.

    A chip matches when at least one of its selectors is configured and every
    configured one has the declared value.  Returns None when no chip or more
    than one chip matches.

    Args:
        chips: ChipDefinition objects to consider (e.g. the chip library)
    """
    matches = []
    for chip in chips:
        selectors = getattr(chip, "selectors", None) or {}
        seen = False
        agrees = True
        for key, declared in selectors.items():
            values = configured_selector_values(project, key)
            if not values:
                continue
            seen = True
            if any(str(v) != str(declared) for v in values):
                agrees = False
                break
        if seen and agrees:
            matches.append(chip.name)
    return matches[0] if len(matches) == 1 else None


def is_selector(chip, module: str, param: str) -> bool:
    """Whether ``chip`` declares ``<module>.<param>`` as a selector."""
    return f"{module}.{param}" in (getattr(chip, "selectors", None) or {})
