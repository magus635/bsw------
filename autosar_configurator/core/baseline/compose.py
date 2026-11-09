"""Layered baseline composition: DEFAULT < REC < DERIVED < PRE (design §6.5).

``compose_base`` overlays the value collections of each layer, lowest layer first, and
records for every ``ValueKey`` the layer it came from. Containers are matched by their
short-name path and merged recursively; a higher layer replaces a lower layer's value
key by key (a multi-value parameter or reference is replaced as a whole). Afterwards,
each container in the result gets the static ``default_value`` of every parameter its
definition declares but no layer set; those values are marked ``Layer.DEFAULT``.

Two kinds of default are deliberately left out, so a package and a chip always give the
same baseline:

- ``default_expr`` (XPath) defaults: never evaluated here;
- defaults a chip expression already wrote into ``default_value``
  (``EcucParameterDef.default_is_computed``), which depend on the selected chip.
"""
import re
from enum import Enum
from typing import Dict, Iterable, List, Optional, Tuple

from ..model.configuration_model import (
    DEFAULT_CONFIG_VARIANT,
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
    EcucReferenceValue,
)
from ..model.definition_model import EcucContainerDef, EcucModuleDef, EcucParameterDef
from ..model.definition_refs import (
    absolute_ref,
    matches_container_def,
    module_path,
    parameter_dest,
)
from .values import ValueKey, container_key, module_param_key, param_key, ref_key

__all__ = ["Layer", "compose_base"]

_INSTANCE_INDEX = re.compile(r'_\d+$')
_MULTI = (-1,)


class Layer(Enum):
    """Source layer of a baseline value; a higher value wins."""
    DEFAULT = 0
    REC = 1
    DERIVED = 2
    PRE = 3


Origins = Dict[ValueKey, Layer]


def _copy_value(value):
    """A value that a later edit of the result cannot reach back into the input through."""
    if isinstance(value, (list, tuple)):
        return type(value)(_copy_value(v) for v in value)
    if isinstance(value, dict):
        return {k: _copy_value(v) for k, v in value.items()}
    return value


def _clone_param(param: EcucParameterValue) -> EcucParameterValue:
    return EcucParameterValue(definition_ref=param.definition_ref, value=_copy_value(param.value),
                              index=param.index, dest_type=param.dest_type)


def _clone_ref(ref: EcucReferenceValue) -> EcucReferenceValue:
    return EcucReferenceValue(definition_ref=ref.definition_ref, value_ref=ref.value_ref,
                              dest_type=ref.dest_type, index=ref.index)


def _shell(src: EcucContainerValue, parent: Optional[EcucContainerValue],
           module_name: str) -> EcucContainerValue:
    """A new, empty container with ``src``'s identity, placed under ``parent``."""
    shell = EcucContainerValue(short_name=src.short_name, definition_ref=src.definition_ref,
                               def_dest_type=src.def_dest_type, parent=parent,
                               module_name=module_name, index=src.index, uuid=src.uuid,
                               variant=src.variant)
    return shell



def _merge_container(target: EcucContainerValue, src: EcucContainerValue,
                     layer: Layer, module_name: str, origins: Origins) -> None:
    """Overlay ``src`` (one layer) onto ``target`` (the result), recording origins.

    The container's own origin is the layer that first introduced it and is not
    overwritten by a later layer that merely adds values inside it.
    """
    origins.setdefault(container_key(target), layer)
    for name, param in src.parameter_values.items():
        target.multi_parameter_values.pop(name, None)
        target.parameter_values[name] = _clone_param(param)
        origins[param_key(target, name)] = layer
    for name, params in src.multi_parameter_values.items():
        target.parameter_values.pop(name, None)
        target.multi_parameter_values[name] = [_clone_param(p) for p in params]
        origins[param_key(target, name)] = layer
    for name, ref in src.reference_values.items():
        target.multi_reference_values.pop(name, None)
        target.reference_values[name] = _clone_ref(ref)
        origins[ref_key(target, name)] = layer
    for name, refs in src.multi_reference_values.items():
        target.reference_values.pop(name, None)
        target.multi_reference_values[name] = [_clone_ref(r) for r in refs]
        origins[ref_key(target, name)] = layer
    for name, param in src.unknown_parameters.items():
        if name in src.parameter_values:
            target.unknown_parameters[name] = target.parameter_values[name]
    _merge_children(target.sub_containers, src.sub_containers, target, layer, module_name, origins)


def _merge_children(targets: List[EcucContainerValue], sources: Iterable[EcucContainerValue],
                    parent: EcucContainerValue, layer: Layer, module_name: str,
                    origins: Origins) -> None:
    by_name = {c.short_name: c for c in targets}
    for src in sources:
        target = by_name.get(src.short_name)
        if target is None:
            target = _shell(src, parent, module_name)
            targets.append(target)
            by_name[src.short_name] = target
        _merge_container(target, src, layer, module_name, origins)


def _find_def(candidates: Dict[str, EcucContainerDef], container: EcucContainerValue,
              module_name: str) -> Optional[EcucContainerDef]:
    """The definition among ``candidates`` that ``container`` instantiates, if any.

    A container with no DEFINITION-REF at all is matched by its short name (an EB
    Tresos ``_N`` instance suffix ignored); one whose DEFINITION-REF names nothing in
    ``candidates`` has no definition here, and its subtree gets no defaults.
    """
    if not container.definition_ref:
        for name in (container.short_name, _INSTANCE_INDEX.sub('', container.short_name)):
            if name in candidates:
                return candidates[name]
        return None
    for name in sorted(candidates):
        cdef = candidates[name]
        if matches_container_def(container.definition_ref, cdef.definition_ref,
                                 cdef.short_name, module_name):
            return cdef
    return None


def _default_param(pdef: EcucParameterDef, module_def: EcucModuleDef,
                   owner_ref: str) -> EcucParameterValue:
    """A DEFAULT-layer value for ``pdef`` with the DEFINITION-REF a value file expects."""
    if pdef.definition_ref:
        ref = absolute_ref(module_def, pdef.definition_ref)
    else:
        ref = absolute_ref(module_def, f"{owner_ref}/{pdef.short_name}" if owner_ref else pdef.short_name)
    return EcucParameterValue(definition_ref=ref, value=_copy_value(pdef.default_value),
                              dest_type=parameter_dest(pdef))


def _has_static_default(pdef: EcucParameterDef) -> bool:
    """A value the DEFAULT layer may take: single-valued, static, not chip-computed."""
    if pdef.default_value is None or pdef.default_is_computed:
        return False
    return not (pdef.upper_multiplicity in _MULTI or pdef.upper_multiplicity > 1)


def _fill_defaults(params: Dict[str, EcucParameterValue], multi: Dict[str, list],
                   defs: Dict[str, EcucParameterDef], module_def: EcucModuleDef,
                   owner_ref: str, key_of, origins: Origins) -> None:
    """Add each parameter of ``defs`` that has a static ``default_value`` and is not set."""
    for name in sorted(defs):
        pdef = defs[name]
        if name in params or name in multi or not _has_static_default(pdef):
            continue
        params[name] = _default_param(pdef, module_def, owner_ref)
        origins[key_of(name)] = Layer.DEFAULT


def _fill_container_defaults(container: EcucContainerValue, candidates: Dict[str, EcucContainerDef],
                             module_def: EcucModuleDef, module_name: str, origins: Origins) -> None:
    """Fill defaults below ``container``; an unmatched definition prunes its subtree."""
    cdef = _find_def(candidates, container, module_name)
    if cdef is None:
        return
    _fill_defaults(container.parameter_values, container.multi_parameter_values,
                   cdef.parameters, module_def, cdef.definition_ref or container.definition_ref,
                   lambda name: param_key(container, name), origins)
    for sub in container.sub_containers:
        _fill_container_defaults(sub, cdef.sub_containers, module_def, module_name, origins)


def compose_base(module_def: Optional[EcucModuleDef], module_name: str,
                 layers: Dict[Layer, List[EcucModuleConfiguration]]
                 ) -> Tuple[EcucModuleConfiguration, Dict[ValueKey, Layer]]:
    """Compose the baseline Base' of one module from its value layers.

    Args:
        module_def: The module definition, source of static ``default_value``s
            (``None``: no defaults are filled).
        module_name: Module short name; the result is named after it and all its
            container paths start with ``/<module_name>``.
        layers: Value collections per layer. Any subset of ``Layer`` may be given
            (DERIVED included; an empty list changes nothing). Within one layer the
            collections apply in list order.

    Returns:
        ``(base, origins)``: a new ``EcucModuleConfiguration`` (the inputs are never
        mutated or shared) and the layer each flattened key of ``base`` comes from.
        A ``"C:"`` key gets the layer that first introduced the container.
    """
    origins: Origins = {}
    top: List[EcucContainerValue] = []
    module_params: Dict[str, EcucParameterValue] = {}
    definition_ref = ""
    variant = ""
    package_name = None

    for layer in sorted(layers, key=lambda l: l.value):
        for config in layers[layer]:
            definition_ref = config.definition_ref or definition_ref
            if config.implementation_config_variant != DEFAULT_CONFIG_VARIANT:
                variant = config.implementation_config_variant
            package_name = config.package_name if config.package_name is not None else package_name
            for name, param in config.parameter_values.items():
                module_params[name] = _clone_param(param)
                origins[module_param_key(module_name, name)] = layer
            _merge_children(top, config.containers, None, layer, module_name, origins)

    if module_def is not None:
        if not definition_ref:
            definition_ref = module_path(module_def)
        _fill_defaults(module_params, {}, module_def.parameters, module_def, module_path(module_def),
                       lambda name: module_param_key(module_name, name), origins)
        for container in top:
            _fill_container_defaults(container, module_def.containers, module_def, module_name, origins)

    base = EcucModuleConfiguration(short_name=module_name, definition_ref=definition_ref)
    if variant:
        base.implementation_config_variant = variant
    base.package_name = package_name
    base.parameter_values.update(module_params)
    for container in top:
        base.add_container(container)
    base.is_modified = False
    return base, {key: origins[key] for key in sorted(origins)}
