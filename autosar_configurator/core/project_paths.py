"""Project directory resolution.

The one place that knows where a project keeps its configuration values, templates,
generated code, chips, ... .  Format 8 projects carry a ``directories`` table in the
``.dpa`` file; older projects (and every project without that table) use the legacy
names returned by :meth:`ProjectDirectories.legacy`.

All directory values are POSIX-style strings relative to the project root (the
directory holding the ``.dpa`` file).  This module must not import PySide6.
"""
from dataclasses import dataclass, fields
from pathlib import Path, PurePosixPath
from typing import Any, Dict, Optional

GEN_LAYOUT_FLAT = "flat"
GEN_LAYOUT_PER_MODULE = "per-module"

# Keys written to / read from the .dpa ``directories`` table (format 8)
_DPA_KEYS = ("config", "base", "templates", "gen", "gen_layout", "chips",
             "integration", "system", "history", "modules")
# Keys that name a directory (everything except the gen layout switch)
_DIR_KEYS = tuple(k for k in _DPA_KEYS if k != "gen_layout") + ("legacy_plugins",)


@dataclass(frozen=True)
class ProjectDirectories:
    config: str
    base: str
    templates: str
    gen: str
    gen_layout: str
    chips: str
    integration: str
    system: str
    history: str
    modules: str
    legacy_plugins: str

    @classmethod
    def default_v8(cls) -> "ProjectDirectories":
        """Defaults of a new format 8 project."""
        return cls(config="config", base="config/base", templates="templates", gen="gen",
                   gen_layout=GEN_LAYOUT_FLAT, chips="chips", integration="integration",
                   system="system", history=".history", modules="modules",
                   legacy_plugins="Def/plugins")

    @classmethod
    def legacy(cls) -> "ProjectDirectories":
        """Directory names of format <= 7 projects (ConfigValue/, generateCode/<Module>/, ...)."""
        return cls(config="ConfigValue", base="ConfigValue/base", templates="templates",
                   gen="generateCode", gen_layout=GEN_LAYOUT_PER_MODULE, chips="chips",
                   integration="integration", system="system", history=".history",
                   modules="modules", legacy_plugins="Def/plugins")

    @classmethod
    def from_dict(cls, d: Optional[Dict[str, Any]], fallback: "ProjectDirectories") -> "ProjectDirectories":
        """Table from a .dpa ``directories`` dict; missing, empty or non-string values come
        from ``fallback``, unknown keys are ignored, backslashes become slashes."""
        values = {}
        for f in fields(cls):
            raw = (d or {}).get(f.name) if isinstance(d, dict) else None
            if isinstance(raw, str) and raw.strip():
                values[f.name] = _posix(raw)
            else:
                values[f.name] = getattr(fallback, f.name)
        return cls(**values)

    def to_dict(self) -> Dict[str, str]:
        """The .dpa ``directories`` table (``legacy_plugins`` is not part of it)."""
        return {k: getattr(self, k) for k in _DPA_KEYS}


def _posix(value: str) -> str:
    text = value.strip().replace("\\", "/")
    return str(PurePosixPath(text)) if text else text


def project_root(project) -> Path:
    """Directory holding the project's ``.dpa`` file (``project.path`` may also be the
    project directory itself, e.g. for EB projects)."""
    path = Path(project.path)
    if path.suffix != ".dpa" and path.is_dir():
        return path
    return path.parent


def dirs(project) -> ProjectDirectories:
    """The project's directory table; legacy names when it has none."""
    table = getattr(project, "directories", None)
    return table if table is not None else ProjectDirectories.legacy()


def resolve(project, key: str) -> Path:
    """Absolute path of directory ``key`` (e.g. ``"templates"``) of ``project``."""
    if key not in _DIR_KEYS:
        raise KeyError(f"Unknown project directory key: {key!r}")
    return project_root(project) / getattr(dirs(project), key)


def config_file(project, module: str) -> Path:
    """Configuration value file of ``module``: ``config/<M>.arxml`` with a directory
    table, ``ConfigValue/<M>_Config.arxml`` for legacy projects."""
    if getattr(project, "directories", None) is None:
        return resolve(project, "config") / f"{module}_Config.arxml"
    return resolve(project, "config") / f"{module}.arxml"


def gen_dir(project, module: str) -> Path:
    """Directory that receives ``module``'s generated code."""
    gen = resolve(project, "gen")
    return gen if dirs(project).gen_layout == GEN_LAYOUT_FLAT else gen / module


# --- helpers for callers that only have a directory, not a project object ----------

def legacy_def_dir(project_dir: Path) -> Path:
    """``<project_dir>/Def`` (the EB-style definition tree of legacy projects)."""
    return Path(project_dir) / PurePosixPath(ProjectDirectories.legacy().legacy_plugins).parts[0]


def legacy_plugins_dir(project_dir: Path) -> Path:
    """``<project_dir>/Def/plugins`` (EB plugins copied or linked into legacy projects)."""
    return Path(project_dir) / ProjectDirectories.legacy().legacy_plugins
