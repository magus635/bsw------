"""Flatten a module configuration into ``{ValueKey: value}``.

``ValueKey`` forms (built with the ``core.packages.value_index`` helpers, so the lock
checks and the baseline agree on keys):

- ``"C:<container path>"``: the container exists (value ``True``);
- ``"P:<container path>.<parameter>"``: a parameter value;
- ``"R:<container path>.<reference>"``: a reference value (its ``value_ref`` string).

The container path is ``EcucContainerValue.get_path()``, which starts with the module
name (``/Mcu/McuGeneral/McuSub``). Module-level parameters
(``EcucModuleConfiguration.parameter_values``) use the module itself as the container
path: ``"P:/<config.short_name>.<parameter>"`` (e.g. ``"P:/Os.OsResourceSubderivative"``),
the same prefix ``get_path()`` gives the module's top-level containers.

Multi-value parameters and references flatten to an ordered ``tuple``; single values
stay scalars.
"""
from typing import Any, Dict

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


def _flatten_container(container: EcucContainerValue, out: Dict[ValueKey, Any]) -> None:
    out[container_key(container)] = True
    for name, param in container.parameter_values.items():
        out[param_key(container, name)] = param.value
    for name, params in container.multi_parameter_values.items():
        out[param_key(container, name)] = tuple(p.value for p in params)
    for name, ref in container.reference_values.items():
        out[ref_key(container, name)] = ref.value_ref
    for name, refs in container.multi_reference_values.items():
        out[ref_key(container, name)] = tuple(r.value_ref for r in refs)
    for sub in container.sub_containers:
        _flatten_container(sub, out)


def flatten(config: EcucModuleConfiguration) -> Dict[ValueKey, Any]:
    """All values of ``config`` as ``{ValueKey: value}``, sorted by key.

    Containers are expected to carry ``module_name == config.short_name`` (as
    ``EcucModuleConfiguration.add_container`` and the parsers ensure), so container
    keys and module-level parameter keys share the ``/<module>`` prefix.
    """
    out: Dict[ValueKey, Any] = {}
    for name, param in config.parameter_values.items():
        out[module_param_key(config.short_name, name)] = param.value
    for container in config.containers:
        _flatten_container(container, out)
    return {key: out[key] for key in sorted(out)}
