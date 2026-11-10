"""Baseline layer: value flattening, layered baseline composition, three-way merge, the
accepted-baseline snapshot store and value origins (design §6.5, §6.7).

Pure functions over configuration and definition models; no UI. ``store`` is the only
module here that does I/O (the arxml snapshot and its hash).
"""
from .values import ValueKey, container_key, flatten, module_param_key, param_key, ref_key, values_equal
from .compose import Layer, compose_base
from .merge import MergeApplyError, MergeItem, MergeKind, MergeResult, apply_merge, three_way_merge
from .store import hash_file, read_base, write_base
from .origin import Origin, classify, origins_for

__all__ = [
    "ValueKey", "container_key", "param_key", "ref_key", "module_param_key",
    "flatten", "values_equal", "Layer", "compose_base",
    "MergeKind", "MergeItem", "MergeResult", "MergeApplyError", "three_way_merge", "apply_merge",
    "hash_file", "read_base", "write_base", "Origin", "classify", "origins_for",
]
