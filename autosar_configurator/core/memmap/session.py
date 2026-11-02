"""
Layout configuration of a project

The glue between a project, its scan result and its memory layout configuration: where the
file is, loading it (or starting an empty one), bringing it up to date with the scan and the
chip (``factory.prepare``), placing every section, and saving.  The configuration page of the
memory map window uses only this, so it can be tested without a window.
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional

from . import rules as rl
from .check import CheckResult, SectionRow
from .config import ConfigError, MemoryMapConfig, config_path, load_config, save_config
from .factory import Prepared, prepare


def project_dir(project) -> Optional[Path]:
    path = getattr(project, "path", None)
    if not path:
        return None
    path = Path(path)
    return path.parent if path.suffix == ".dpa" else path


def chip_cores(project) -> Optional[int]:
    """The core count of the project's chip (``metadata.cores.count``); None when unknown."""
    from ..hardware.ecu_resource_resolver import chip_for_project
    try:
        chip = chip_for_project(project, getattr(project, "chip_database", None))[1]
    except Exception:  # noqa: BLE001 - without chip data nothing is trimmed
        return None
    cores = ((getattr(chip, "metadata", None) or {}).get("cores") or {}) if chip is not None else {}
    count = cores.get("count") if isinstance(cores, dict) else None
    return int(count) if isinstance(count, int) else None


@dataclass
class LayoutSession:
    """A project's layout configuration while the memory map window is open."""
    project: object
    config: MemoryMapConfig = field(default_factory=MemoryMapConfig)
    path: Optional[Path] = None
    load_error: str = ""                # the file could not be read: the window says so
    prepared: Optional[Prepared] = None
    dirty: bool = False

    @classmethod
    def open(cls, project) -> "LayoutSession":
        base = project_dir(project)
        session = cls(project, path=config_path(base) if base is not None else None)
        if session.path is not None:
            try:
                session.config = load_config(session.path)
            except ConfigError as e:
                session.load_error = str(e)
                session.config = MemoryMapConfig()
        return session

    # --- bringing it up to date ---------------------------------------------------

    def update(self, result: CheckResult) -> Prepared:
        """Bring the configuration up to date with a scan result and the project's chip.

        This may add required regions and, the first time, copy the factory rules; it marks
        the session as changed only when it did.
        """
        from .config import config_dict
        before = config_dict(self.config)
        chip = getattr(self.project, "selected_chip", None) or ""
        self.prepared = prepare(self.config, chip, result.needs, chip_cores(self.project))
        if config_dict(self.config) != before:
            self.dirty = True
        return self.prepared

    # --- placing ------------------------------------------------------------------------

    def placements(self, rows: List[SectionRow]) -> Dict[str, rl.Placement]:
        return {p.section: p for p in rl.place_all(self.config, rows)}

    def place(self, rows: List[SectionRow], region: str) -> List[str]:
        """Place ``rows`` by hand in ``region``.  Returns the refusals (one line each); the rows
        that fit are placed even when others are refused."""
        refused = []
        for row in rows:
            problem = rl.check_manual(self.config, row, region)
            if problem:
                refused.append(f"{row.output}：{problem}")
                continue
            if self.config.manual.get(row.output) != region:
                self.config.manual[row.output] = region
                self.dirty = True
        return refused

    def unplace(self, sections: List[str]) -> None:
        """Remove the manual placements of ``sections``: they go back to the rules."""
        for name in sections:
            if name in self.config.manual:
                rl.clear_manual(self.config, name)
                self.dirty = True

    def changed(self) -> None:
        """The rules or the regions were changed through the configuration object directly."""
        self.dirty = True

    # --- saving --------------------------------------------------------------------------

    def save(self) -> Path:
        """Write the configuration.

        Raises:
            ConfigError: no project directory, or the file could not be written
        """
        if self.path is None:
            raise ConfigError("工程还没有保存位置，无法保存内存布局配置")
        save_config(self.config, self.path)
        self.dirty = False
        self.load_error = ""
        return self.path
