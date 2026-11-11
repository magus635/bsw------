"""Library reference for module packages.

Defines LibraryRef, which records metadata about a module library (package or EB plugins).
"""
from dataclasses import dataclass, field, asdict
from pathlib import Path
from typing import TYPE_CHECKING, List, Optional, Any, Dict, Tuple

from .errors import PackageConflictError, PackageError

if TYPE_CHECKING:
    from .package import ModulePackage


@dataclass
class LibraryRef:
    """Reference to a module library (package or EB plugins directory).

    Attributes:
        path: POSIX-style path to the library root (relative to project dir if inside,
              absolute otherwise).
        kind: Type of library: "package" (native module packages) or "eb-plugins"
              (EB Tresos plugin directory).
        exclude: Directories of the library not to scan, as paths relative to the library
            root (POSIX; a first-level directory is just its name). Matched against the
            directory, never against a module's short name — a wrapper directory named
            after its module must not hide the package that really provides it.
    """
    path: str
    kind: str
    exclude: List[str] = field(default_factory=list)

    def to_dict(self) -> Dict[str, Any]:
        """Convert to dictionary for JSON serialization."""
        return asdict(self)

    @classmethod
    def from_dict(cls, d: Dict[str, Any]) -> "LibraryRef":
        """Create from dictionary."""
        return cls(
            path=d.get("path", ""),
            kind=d.get("kind", "package"),
            exclude=d.get("exclude", []),
        )


_MARKER_BY_KIND = {"package": "module.json", "eb-plugins": "plugin.xml"}


def _excluded_dirs(exclude: List[str]) -> set:
    """``exclude`` entries as normalised relative directory paths (``./X/`` → ``X``)."""
    result = set()
    for entry in exclude:
        text = str(entry).replace("\\", "/").strip().strip("/")
        while text.startswith("./"):
            text = text[2:]
        if text:
            result.add(text)
    return result


def scan_library(ref: LibraryRef, base: Path) -> List["ModulePackage"]:
    """Scan first-level subdirectories of a library for module packages.

    Only manifests / plugin.xml are read; definitions are not parsed. A subdirectory
    is skipped when its path relative to the library root is in ``ref.exclude``, or when
    it has no marker file or its manifest cannot be read.

    Returns:
        Packages sorted by directory name.
    """
    from .manifest import infer_package
    from .package import ModulePackage

    marker = _MARKER_BY_KIND.get(ref.kind)
    if marker is None:
        raise PackageError(f"Unknown module library kind {ref.kind!r} for {ref.path}")

    lib_root = Path(ref.path)
    if not lib_root.is_absolute():
        lib_root = Path(base) / lib_root
    if not lib_root.is_dir():
        return []

    excluded = _excluded_dirs(ref.exclude)
    packages = []
    for sub in sorted(lib_root.iterdir(), key=lambda p: p.name):
        if not sub.is_dir() or sub.relative_to(lib_root).as_posix() in excluded:
            continue
        if not (sub / marker).is_file():
            continue
        try:
            manifest = infer_package(sub)
        except PackageError:
            continue
        packages.append(ModulePackage(sub, manifest))
    return packages


def find_package(
    libraries: List[Tuple[int, List["ModulePackage"]]], definition: str
) -> Tuple[int, "ModulePackage"]:
    """Locate the package whose manifest definition equals ``definition``.

    Args:
        libraries: (library index, scanned packages) pairs

    Raises:
        PackageConflictError: the definition is provided by more than one package
        PackageError: no package provides it
    """
    matches = [
        (index, pkg)
        for index, packages in libraries
        for pkg in packages
        if pkg.manifest.definition == definition
    ]
    if len(matches) > 1:
        roots = [pkg.root.as_posix() for _, pkg in matches]
        raise PackageConflictError(
            f"Definition {definition} provided by multiple packages: {', '.join(roots)}",
            path=definition,
            files=roots,
        )
    if not matches:
        raise PackageError(f"No module package provides definition {definition}")
    return matches[0]
