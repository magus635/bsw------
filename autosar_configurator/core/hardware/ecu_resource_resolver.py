"""
ECU resource resolver

The single place that builds ``project.ecu_resources`` (the flat dict behind
``ecu:get()`` / ``ecu:list()``).  Sources, lowest priority first:

1. ``*.properties`` files found in the project and in the plugin directories of
   the loaded modules (resource files must match the selected chip).
2. The ``ecu_resources`` section of the selected chip's YAML definition.

On a conflicting key the chip YAML wins and the difference is logged.
"""
import logging
from pathlib import Path
from typing import Any, Dict, List, Optional

from .chip_database import ChipDatabase, get_default_chip_database
from .ecu_resource_data import flatten_ecu_resources
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

    add(project_dir / "Def" / "plugins")        # project-local EB plugins
    add(project_dir / "Def")
    add(project_dir / "Define")
    # Plugin roots of the loaded modules (handles external plugins such as Os):
    # typical EB layout is plugin_dir/config/module.xdm
    for def_path in getattr(project, "module_defs", {}).values():
        if def_path:
            add(Path(def_path).parent.parent)
    add(project_dir / "templates")
    return dirs


def scan_properties(project) -> Dict[str, Any]:
    """Flat key/value dict from the ``*.properties`` files that apply to ``project``."""
    project_dir = _project_dir(project)
    if project_dir is None:
        return {}

    search_dirs = _search_dirs(project, project_dir)
    if not search_dirs:
        return {}

    all_props: List[Path] = []
    seen = set()
    for d in search_dirs:
        for pf in d.rglob("*.properties"):
            resolved = pf.resolve()
            if resolved not in seen:
                seen.add(resolved)
                all_props.append(pf)

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
            else:
                filtered.append(pf)
        all_props = filtered

    parser = TresosPropertiesParser()
    accumulated: Dict[str, Any] = {}
    for pf in all_props:
        try:
            # Later files override earlier ones for the same key
            accumulated.update(parser.parse_file(pf).properties)
        except Exception as e:  # noqa: BLE001 - one bad file must not hide the others
            logger.warning(f"Failed to parse properties file {pf}: {e}")
    return accumulated


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
        selected_chip = getattr(project, "selected_chip", None)
        if not selected_chip:
            return {}
        chip = self._database(project).get_chip(selected_chip)
        if chip is None:
            logger.info("Selected chip %s is not in the chip database; "
                        "no chip ECU resources applied", selected_chip)
            return {}
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
