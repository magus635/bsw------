"""Baseline layer: value flattening and layered baseline composition (design §6.5).

Pure functions over configuration and definition models; no I/O, no UI.
"""
from .values import ValueKey, container_key, flatten, module_param_key, param_key, ref_key, values_equal
from .compose import Layer, compose_base

__all__ = [
    "ValueKey", "container_key", "param_key", "ref_key", "module_param_key",
    "flatten", "values_equal", "Layer", "compose_base",
]
