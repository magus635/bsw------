"""Typed IR models and generation report for Phase 1 RTE/SchM header synthesis."""

from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional, Tuple


@dataclass
class RteMeta:
    """Module version and core configuration flags for core RTE header generation."""

    sw_major: int = 4
    sw_minor: int = 0
    sw_patch: int = 0
    vendor_id: int = 30
    module_id: int = 2
    ar_major: int = 4
    ar_minor: int = 2
    ar_patch: int = 2
    enable_multi_core: bool = False
    enable_memory_protection: bool = False
    disable_rte_init_memory: bool = False
    dev_error_detect: bool = False


@dataclass
class SchedulableEntityModel:
    """BSW schedulable entity whose entry prototype is declared in ``SchM_<ApiName>.h``."""

    short_name: str
    entry_name: str


@dataclass
class ExclusiveAreaModel:
    """BSW exclusive area protection binding for ``SchM_Enter_*`` / ``SchM_Exit_*``."""

    short_name: str
    mechanism: str = "ALL_INTERRUPT_BLOCKING"
    os_resource: Optional[str] = None
    os_spinlock: Optional[str] = None
    generate_function: bool = False


@dataclass
class BswModuleSchmModel:
    """Resolved scheduler header model for a single active BSW module instance."""

    module_name: str
    api_name: str
    upper_prefix: str
    memmap_header: str
    schedulable_entities: List[SchedulableEntityModel] = field(default_factory=list)
    exclusive_areas: List[ExclusiveAreaModel] = field(default_factory=list)
    requires_os_header: bool = False


@dataclass
class RteProjectModel:
    """Aggregated cross-module model for Phase 1 RTE/SchM header generation."""

    meta: RteMeta
    bsw_modules: List[BswModuleSchmModel] = field(default_factory=list)
    os_cores: List[str] = field(default_factory=list)
    os_applications: List[str] = field(default_factory=list)
    has_com: bool = False


@dataclass
class RteGenerationReport:
    """Outcome summary and diagnostics produced by :class:`RteSchMGenerator`."""

    generated_files: List[Path] = field(default_factory=list)
    unchanged_files: List[Path] = field(default_factory=list)
    preserved_files: List[Path] = field(default_factory=list)
    overridden_files: List[Path] = field(default_factory=list)
    skipped_modules: List[Tuple[str, str]] = field(default_factory=list)
    warnings: List[str] = field(default_factory=list)
    errors: List[str] = field(default_factory=list)

    @property
    def ok(self) -> bool:
        return not self.errors


@dataclass
class RtePreviewFile:
    """In-memory preview entry for one Phase 1 RTE/SchM output file."""

    filename: str
    target_path: Path
    content: str
    status: str  # "new" | "updated" | "unchanged" | "preserved" | "overlay"
    source: str  # "model" | "stub" | "overlay"
