"""Library reference for module packages.

Defines LibraryRef, which records metadata about a module library (package or EB plugins).
"""
from dataclasses import dataclass, field, asdict
from typing import List, Optional, Any, Dict


@dataclass
class LibraryRef:
    """Reference to a module library (package or EB plugins directory).

    Attributes:
        path: POSIX-style path to the library root (relative to project dir if inside,
              absolute otherwise).
        kind: Type of library: "package" (native module packages) or "eb-plugins"
              (EB Tresos plugin directory).
        exclude: List of module short names to exclude from loading.
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
