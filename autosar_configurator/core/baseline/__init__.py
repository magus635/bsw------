"""Baseline layer: value flattening, layered baseline composition and three-way merge
(design §6.5).

Pure functions over configuration and definition models; no I/O, no UI.
"""
from .values import ValueKey, container_key, flatten, module_param_key, param_key, ref_key, values_equal
from .compose import Layer, compose_base
from .merge import MergeApplyError, MergeItem, MergeKind, MergeResult, apply_merge, three_way_merge

__all__ = [
    "ValueKey", "container_key", "param_key", "ref_key", "module_param_key",
    "flatten", "values_equal", "Layer", "compose_base",
    "MergeKind", "MergeItem", "MergeResult", "MergeApplyError", "three_way_merge", "apply_merge",
]
