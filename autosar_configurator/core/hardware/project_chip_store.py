"""
Project-local chip definitions

A project keeps its own copy of the selected chip's YAML under
``<project dir>/chips/<chip>.yaml``.  The packaged chip library
(``autosar_configurator/data/chips``) is only the place a copy is made from, so
a project stays self-contained and portable, and a library upgrade never changes
an existing project unless the user asks for it.
"""
import logging
import re
from pathlib import Path
from typing import List, Optional, Tuple

from .chip_database import ChipDatabase, ChipDefinition
from .chip_exporter import ChipDefinitionExporter
from .ecu_resource_data import flatten_ecu_resources, nest_flat_resources

logger = logging.getLogger(__name__)

CHIPS_DIR_NAME = "chips"

# A chip name is used as a file name: no separators, no leading dot
_SAFE_NAME = re.compile(r"^[A-Za-z0-9][A-Za-z0-9_.\-]*$")

# Where a project's chip resources come from
SOURCE_PROJECT = "project"        # <project dir>/chips/<chip>.yaml
SOURCE_LIBRARY = "library"        # packaged chip library, not yet copied into the project
SOURCE_PROPERTIES = "properties"  # no YAML anywhere; only .properties files apply
SOURCE_NONE = "none"              # no chip selected


class ProjectChipStore:
    """Reads and writes the chip YAML files of one project."""

    def __init__(self, project_dir: Path):
        self.project_dir = Path(project_dir)

    @property
    def directory(self) -> Path:
        return self.project_dir / CHIPS_DIR_NAME

    def path_for(self, chip_name: str) -> Path:
        if not _SAFE_NAME.match(chip_name or ""):
            raise ValueError(f"'{chip_name}' is not a valid chip file name")
        return self.directory / f"{chip_name}.yaml"

    def exists(self) -> bool:
        return self.directory.is_dir()

    def has(self, chip_name: str) -> bool:
        try:
            return self.path_for(chip_name).is_file()
        except ValueError:
            return False

    def load(self, chip_name: str) -> Optional[ChipDefinition]:
        """The project's copy of ``chip_name``, or None if absent or unreadable."""
        if not self.has(chip_name):
            return None
        try:
            return ChipDatabase()._load_chip_from_yaml(self.path_for(chip_name))
        except Exception as e:  # noqa: BLE001 - a broken copy must not stop the project loading
            logger.warning("Project chip file %s could not be read: %s",
                           self.path_for(chip_name), e)
            return None

    def save(self, chip: ChipDefinition) -> Path:
        """Write ``chip`` as the project's copy (replacing an existing one)."""
        path = self.path_for(chip.name)
        ChipDefinitionExporter().save_yaml(chip, path)
        return path

    def list_names(self) -> List[str]:
        if not self.directory.is_dir():
            return []
        names = []
        for f in sorted(self.directory.glob("*.yaml")):
            if _SAFE_NAME.match(f.stem):
                names.append(f.stem)
        return names


def chip_from_properties(chip_name: str, flat_resources: dict) -> ChipDefinition:
    """A chip that carries only ECU resources, built from a flat properties dict."""
    nested, skipped = nest_flat_resources(flat_resources)
    for key in skipped:
        logger.warning("Key '%s' has no module prefix and is not stored in the chip", key)
    return ChipDefinition(name=chip_name, ecu_resources=nested)


def describe_differences(project_chip: ChipDefinition, library_chip: ChipDefinition,
                         limit: int = 12) -> Tuple[List[str], int]:
    """ECU resource keys whose value differs between the project's copy and the library's.

    Returns:
        (first ``limit`` lines like "Os.Key: project=1 / library=2", total number of differences)
    """
    mine = flatten_ecu_resources(project_chip.ecu_resources)
    theirs = flatten_ecu_resources(library_chip.ecu_resources)
    lines: List[str] = []
    total = 0
    for key in sorted(set(mine) | set(theirs)):
        a, b = mine.get(key, "<absent>"), theirs.get(key, "<absent>")
        if a == b:
            continue
        total += 1
        if len(lines) < limit:
            lines.append(f"{key}: project={_short(a)} / library={_short(b)}")
    return lines, total


def _short(value, max_len: int = 40) -> str:
    text = str(value)
    return text if len(text) <= max_len else text[:max_len] + "..."
