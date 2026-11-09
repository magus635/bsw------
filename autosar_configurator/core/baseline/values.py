"""Flatten a module configuration into ``{ValueKey: value}``.

``ValueKey`` forms (the same strings the ``core.packages.value_index`` helpers build, so
the baseline and the lock checks agree on keys):

- ``"C:<container path>"``: the container exists (value ``True``);
- ``"P:<container path>.<parameter>"``: a parameter value;
- ``"R:<container path>.<reference>"``: a reference value (its ``value_ref`` string).

The container path is ``EcucContainerValue.get_path()``, which starts with the module
name (``/Mcu/McuGeneral/McuSub``). Module-level parameters
(``EcucModuleConfiguration.parameter_values``) use the module itself as the container
path: ``"P:/<module>.<parameter>"`` (e.g. ``"P:/Os.OsResourceSubderivative"``), the same
prefix ``get_path()`` gives the module's top-level containers.

Passing ``module_name`` re-roots every key on that module, whatever each container's own
``module_name`` says. That is what makes a Pre fragment saved as a separate value
collection (``McuPreConfiguration``) flatten onto the same keys as the module's own
configuration, which the three-way merge relies on.
"""
from typing import Any, Dict, Optional

from ..model.configuration_model import EcucContainerValue, EcucModuleConfiguration
from ..packages.value_index import container_key, param_key, ref_key

ValueKey = str

__all__ = [
    "ValueKey", "container_key", "param_key", "ref_key", "module_param_key",
    "flatten", "values_equal",
]


def module_param_key(module_name: str, name: str) -> ValueKey:
    """Key of a module-level parameter: ``"P:/<module>.<name>"``."""
    return f"P:/{module_name}.{name}"


def values_equal(a: Any, b: Any) -> bool:
    """Value equality used across the baseline and the workspace.

    Equal when ``a == b`` or their stripped, lower-cased string forms match (so
    ``"TRUE"`` equals ``True`` and ``" 5 "`` equals ``5``). ``workspace_manager._same_value``
    is this function.
    """
    return a == b or str(a).strip().lower() == str(b).strip().lower()


def _flatten_container(container: EcucContainerValue, path: str, out: Dict[ValueKey, Any]) -> None:
    """Add ``container`` (whose path is ``path``) and its subtree to ``out``."""
    if path == container.get_path():
        out[container_key(container)] = True          # the value_index helper, when it applies
    else:
        out["C:" + path] = True                       # same form, re-rooted on another module
    for name, param in container.parameter_values.items():
        out[f"P:{path}.{name}"] = param.value
    for name, params in container.multi_parameter_values.items():
        out[f"P:{path}.{name}"] = tuple(p.value for p in params)
    for name, ref in container.reference_values.items():
        out[f"R:{path}.{name}"] = ref.value_ref
    for name, refs in container.multi_reference_values.items():
        out[f"R:{path}.{name}"] = tuple(r.value_ref for r in refs)
    for sub in container.sub_containers:
        _flatten_container(sub, f"{path}/{sub.short_name}", out)


def flatten(config: EcucModuleConfiguration, module_name: Optional[str] = None) -> Dict[ValueKey, Any]:
    """All values of ``config`` as ``{ValueKey: value}``, sorted by key.

    Args:
        config: The value collection to flatten.
        module_name: Path root for every key. ``None`` (the default) uses each
            container's own ``module_name`` (via ``get_path()``) and
            ``config.short_name`` for module-level parameters. Given a name, all keys
            are re-rooted on it, so fragments of one module flattened with the module's
            name line up key by key.

    Returns:
        ``{ValueKey: value}``: ``True`` for containers, a scalar for single values,
        an ordered ``tuple`` for multi-value parameters and references.
    """
    root = module_name or config.short_name
    out: Dict[ValueKey, Any] = {}
    for name, param in config.parameter_values.items():
        out[module_param_key(root, name)] = param.value
    for container in config.containers:
        path = f"/{module_name}/{container.short_name}" if module_name else container.get_path()
        _flatten_container(container, path, out)
    return {key: out[key] for key in sorted(out)}
