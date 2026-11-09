"""
Module package support: manifests, inference, and loading.

Provides ModuleManifest dataclass and functions to load/infer module packages
from explicit module.json manifests or EB plugin.xml files.
"""

from .errors import PackageError, PackageConflictError
from .types import PackageFile, ModuleManifest
from .manifest import load_manifest, write_manifest, infer_package

__all__ = [
    "PackageError",
    "PackageConflictError",
    "PackageFile",
    "ModuleManifest",
    "load_manifest",
    "write_manifest",
    "infer_package",
]
