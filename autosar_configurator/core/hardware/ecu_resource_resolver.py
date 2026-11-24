"""
ECU resource resolver

The single place that builds ``project.ecu_resources`` (the flat dict behind
``ecu:get()`` / ``ecu:list()``).  Sources, lowest priority first:

1. ``*.properties`` files found in the project and in the plugin directories of
   the loaded modules (resource files must match the selected chip).
2. The ``ecu_resources`` section of the selected chip's YAML definition: the
   project's own copy (``<project dir>/chips/<chip>.yaml``) if it has one,
   otherwise the packaged chip library.

On a conflicting key the chip YAML wins and the difference is logged.
"""
import logging
from pathlib import Path
from typing import Any, Dict, List, Optional, Set

from .. import project_paths
from .chip_database import ChipDatabase, get_default_chip_database
from .ecu_resource_data import flatten_ecu_resources
from .project_chip_store import (
    SOURCE_LIBRARY,
    SOURCE_NONE,
    SOURCE_PROJECT,
    SOURCE_PROPERTIES,
    ProjectChipStore,
)
from .tresos_properties_parser import TresosPropertiesParser, resource_file_matches_chip

logger = logging.getLogger(__name__)


def _project_dir(project) -> Optional[Path]:
    path = getattr(project, "path", None)
    if not path:
        return None
    path = Path(path)
    return path.parent if path.suffix == ".dpa" else path


def _search_dirs(project, project_dir: Path) -> List[Path]:
    """Directories scanned for .properties files, in priority order (later wins)."""
    dirs: List[Path] = []

    def add(d: Path):
        if d.exists() and d not in dirs:
            dirs.append(d)

    add(project_paths.legacy_plugins_dir(project_dir))  # project-local EB plugins
    add(project_paths.legacy_def_dir(project_dir))
    add(project_dir / "Define")
    # Plugin/package roots of the loaded modules:
    # - Format 8 package modules stay strictly bounded to pkg.root so flat packages
    #   (modules/<Variant>/<Mod>.arxml) never escape into modules/ and leak sibling variants.
    # - Non-package modules step up two levels only when def_path sits inside a config/defs
    #   subdirectory (typical EB layout: plugin_dir/config/module.xdm).
    packages = getattr(project, "packages", None) or {}
    for mod_name, def_path in sorted((getattr(project, "module_defs", None) or {}).items()):
        pkg = packages.get(mod_name)
        if pkg is not None and getattr(pkg, "root", None) is not None:
            add(Path(pkg.root))
        elif def_path:
            def_p = Path(def_path)
            if def_p.parent.name.lower() in ("config", "bswmd", "defs", "definition", "definitions"):
                add(def_p.parent.parent)
            else:
                add(def_p.parent)
    # Resource directories of the module packages (format 8 projects)
    for _, pkg in sorted(getattr(project, "packages", {}).items()):
        resource_dir = pkg.resource_dir()
        if resource_dir is not None:
            add(resource_dir)
    return dirs


def _iter_template_properties(project, project_dir: Path, templates_dir: Path) -> List[Path]:
    """Collect ``.properties`` under ``templates_dir``, excluding inactive variant dirs
    and placing active variant overlay dirs after generic ``templates/<Module>/`` dirs."""
    if not templates_dir.is_dir():
        return []

    packages = getattr(project, "packages", None) or {}
    managers = getattr(project, "module_managers", None) or {}
    libraries = getattr(project, "module_libraries", None) or []

    active_names: Set[str] = {mod.lower() for mod in managers}
    active_variant_dirs: Set[str] = set()
    for mod, pkg in packages.items():
        active_names.add(mod.lower())
        if getattr(pkg, "root", None) is not None:
            pkg_dir_lower = Path(pkg.root).name.lower()
            active_names.add(pkg_dir_lower)
            if pkg_dir_lower != mod.lower():
                active_variant_dirs.add(pkg_dir_lower)

    inactive_dirs: Set[str] = set()
    if libraries:
        from ..packages.errors import PackageError
        from ..packages.library import scan_library

        for ref in libraries:
            try:
                pkgs = scan_library(ref, project_dir)
            except PackageError:
                continue
            for pkg in pkgs:
                pkg_dir_lower = Path(pkg.root).name.lower()
                if pkg_dir_lower not in active_names and pkg_dir_lower != pkg.manifest.module.lower():
                    inactive_dirs.add(pkg_dir_lower)

    active_prefixes = tuple(f"{mod.lower()}_" for mod in (set(managers) | set(packages)))

    regular_props: List[Path] = []
    variant_props: List[Path] = []
    try:
        entries = sorted(templates_dir.iterdir(), key=lambda p: p.as_posix())
    except OSError:
        return []

    for item in entries:
        if item.is_file() and item.suffix.lower() == ".properties":
            regular_props.append(item)
            continue
        if not item.is_dir():
            continue
        name_lower = item.name.lower()
        if name_lower in active_variant_dirs:
            variant_props.extend(
                sorted(item.rglob("*.properties"), key=lambda p: p.as_posix())
            )
            continue
        if name_lower in inactive_dirs:
            continue
        if name_lower not in active_names and active_prefixes and name_lower.startswith(active_prefixes):
            continue
        regular_props.extend(
            sorted(item.rglob("*.properties"), key=lambda p: p.as_posix())
        )

    return regular_props + variant_props


def _collect_all_property_files(project, project_dir: Path) -> List[Path]:
    """Collect deduplicated ``.properties`` files in resolver precedence order."""
    all_props: List[Path] = []
    seen: Set[Path] = set()
    for d in _search_dirs(project, project_dir):
        for pf in sorted(d.rglob("*.properties"), key=lambda p: p.as_posix()):
            resolved = pf.resolve()
            if resolved not in seen:
                seen.add(resolved)
                all_props.append(pf)
    templates_dir = project_dir / project_paths.dirs(project).templates
    for pf in _iter_template_properties(project, project_dir, templates_dir):
        resolved = pf.resolve()
        if resolved not in seen:
            seen.add(resolved)
            all_props.append(pf)
    return all_props


def scan_properties(project, resource_only: bool = False) -> Dict[str, Any]:
    """Flat key/value dict from the ``*.properties`` files that apply to ``project``.

    Args:
        resource_only: take only resource files (``.../resource/*.properties``),
            leaving out build configs and similar files that are always loaded
            for ``ecu:get()`` but do not describe the chip
    """
    project_dir = _project_dir(project)
    if project_dir is None:
        return {}

    all_props = _collect_all_property_files(project, project_dir)
    if not all_props:
        return {}

    selected_chip = getattr(project, "selected_chip", None)
    if selected_chip:
        chip_lower = selected_chip.lower()
        filtered = []
        for pf in all_props:
            # A resource properties file MUST match the selected chip (whole
            # underscore-delimited token, so "THA6206" does not match "THA62060x").
            # Other .properties files (build configs, ...) are always loaded.
            if "resource" in str(pf.parent).lower():
                if resource_file_matches_chip(pf.stem, chip_lower):
                    filtered.append(pf)
            elif not resource_only:
                filtered.append(pf)
        all_props = filtered
    elif resource_only:
        all_props = [pf for pf in all_props if "resource" in str(pf.parent).lower()]

    parser = TresosPropertiesParser()
    accumulated: Dict[str, Any] = {}
    for pf in all_props:
        try:
            # Later files override earlier ones for the same key
            accumulated.update(parser.parse_file(pf).properties)
        except Exception as e:  # noqa: BLE001 - one bad file must not hide the others
            logger.warning(f"Failed to parse properties file {pf}: {e}")
    return accumulated


def other_chip_keys(project, chip_database: Optional[ChipDatabase] = None) -> Dict[str, List[str]]:
    """Lower-cased key -> chips that define it, for every chip except the selected one.

    Looks at resource ``.properties`` files that do not match the selected chip
    and at the ``ecu_resources`` of the other chips in the chip database.
    """
    selected = getattr(project, "selected_chip", None)
    result: Dict[str, set] = {}

    project_dir = _project_dir(project)
    if selected and project_dir is not None:
        parser = TresosPropertiesParser()
        for pf in _collect_all_property_files(project, project_dir):
            if "resource" not in str(pf.parent).lower():
                continue
            if resource_file_matches_chip(pf.stem, selected.lower()):
                continue
            try:
                keys = parser.parse_file(pf).properties
            except Exception as e:  # noqa: BLE001 - an unreadable file only means less information
                logger.debug("Skipping unreadable properties file %s: %s", pf, e)
                continue
            for key in keys:
                result.setdefault(key.lower(), set()).add(pf.stem)

    db = chip_database or getattr(project, "chip_database", None) or get_default_chip_database()
    other_chips = {}
    for name in db.list_chips():
        chip = db.get_chip(name)
        if chip is not None and name != selected:
            other_chips[name] = chip
    if project_dir is not None:
        store = ProjectChipStore(project_dir)
        for name in store.list_names():
            chip = store.load(name)
            if chip is not None and name != selected:
                other_chips[name] = chip       # the project's own copy wins over the library's
    for name, chip in other_chips.items():
        for key in flatten_ecu_resources(chip.ecu_resources):
            result.setdefault(key.lower(), set()).add(name)

    return {key: sorted(chips) for key, chips in result.items()}


def chip_for_project(project, chip_database: Optional[ChipDatabase] = None):
    """The chip definition that supplies the project's chip resources.

    Returns:
        ``(source, chip)`` where ``source`` is SOURCE_PROJECT (the project's own
        copy), SOURCE_LIBRARY (only the packaged library has the chip),
        SOURCE_PROPERTIES (no chip YAML anywhere, only .properties files apply)
        or SOURCE_NONE (no chip selected).  ``chip`` is None for the last two.
    """
    selected = getattr(project, "selected_chip", None)
    if not selected:
        return SOURCE_NONE, None
    project_dir = _project_dir(project)
    if project_dir is not None:
        local = ProjectChipStore(project_dir).load(selected)
        if local is not None:
            return SOURCE_PROJECT, local
    db = chip_database or getattr(project, "chip_database", None) or get_default_chip_database()
    chip = db.get_chip(selected)
    if chip is not None:
        return SOURCE_LIBRARY, chip
    return SOURCE_PROPERTIES, None


class EcuResourceResolver:
    """Builds the ECU resource dict of a project from properties files and chip YAML."""

    def __init__(self, chip_database: Optional[ChipDatabase] = None):
        self._chip_database = chip_database

    def _database(self, project) -> ChipDatabase:
        return (self._chip_database
                or getattr(project, "chip_database", None)
                or get_default_chip_database())

    def chip_resources(self, project) -> Dict[str, Any]:
        """Flat ``ecu_resources`` of the project's selected chip (empty if none)."""
        source, chip = chip_for_project(project, self._database(project))
        if source == SOURCE_NONE:
            return {}
        if chip is None:
            logger.info("Selected chip %s has no chip YAML (project or library); "
                        "only .properties files apply", project.selected_chip)
            return {}
        if source == SOURCE_LIBRARY:
            logger.info("Chip %s is read from the chip library; it is not yet saved in "
                        "the project's chips/ directory", project.selected_chip)
        return flatten_ecu_resources(chip.ecu_resources)

    def resolve(self, project) -> Dict[str, Any]:
        """Recompute the resources from scratch (never layered on an old result)."""
        merged = scan_properties(project)
        for key, value in self.chip_resources(project).items():
            if key in merged and merged[key] != value:
                logger.info("ECU resource %s: chip YAML value %r overrides properties value %r",
                            key, value, merged[key])
            merged[key] = value
        return merged


def library_other_chip_keys(chip_database: ChipDatabase, exclude_chip: Optional[str]) -> Dict[str, List[str]]:
    """Lower-cased key -> chips of the library that define it, leaving out ``exclude_chip``."""
    result: Dict[str, set] = {}
    for name in chip_database.list_chips():
        chip = chip_database.get_chip(name)
        if chip is None or name == exclude_chip:
            continue
        for key in flatten_ecu_resources(chip.ecu_resources):
            result.setdefault(key.lower(), set()).add(name)
    return {key: sorted(chips) for key, chips in result.items()}


def available_chip_names(project, chip_database: Optional[ChipDatabase] = None,
                         extra: Optional[List[str]] = None) -> List[str]:
    """Chips a project can select: the chip library, the project's own chips/ and the
    chip names found in the project's resource .properties files (``available_chips``)."""
    names = set(getattr(project, "available_chips", None) or [])
    names.update(extra or [])
    project_dir = _project_dir(project)
    if project_dir is not None:
        names.update(ProjectChipStore(project_dir).list_names())
    db = chip_database or getattr(project, "chip_database", None) or get_default_chip_database()
    names.update(db.list_chips())
    return sorted(n for n in names if n)


def selector_values(project=None, chip_database: Optional[ChipDatabase] = None) -> Dict[str, List[str]]:
    """"<Module>.<parameter>" -> values declared by the chips of the library (and the
    project's own chips/), sorted, for extending selector enumerations."""
    chips = {}
    db = chip_database or (getattr(project, "chip_database", None) if project is not None else None) \
        or get_default_chip_database()
    for name in db.list_chips():
        chip = db.get_chip(name)
        if chip is not None:
            chips[name] = chip
    project_dir = _project_dir(project) if project is not None else None
    if project_dir is not None:
        store = ProjectChipStore(project_dir)
        for name in store.list_names():
            chip = store.load(name)
            if chip is not None:
                chips[name] = chip
    values: Dict[str, set] = {}
    for chip in chips.values():
        for key, value in chip.selectors.items():
            values.setdefault(key, set()).add(value)
    return {key: sorted(v) for key, v in values.items()}
