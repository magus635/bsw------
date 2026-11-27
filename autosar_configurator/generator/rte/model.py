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
    """BSW schedulable entity or SWC runnable whose prototype is declared in header."""

    short_name: str
    entry_name: str
    return_type: str = "void"
    port_arg_types: List[str] = field(default_factory=list)
    arguments: List["SwcClientCallArgModel"] = field(default_factory=list)


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
class SwcDataEndpointModel:
    """Resolved SWC Sender-Receiver port data endpoint for Rte_<Swc>.h and Rte_<App>.c."""

    component_name: str
    swc_type_name: str
    port_name: str
    data_element_name: str
    direction: str  # "TX" | "RX"
    c_type: str = "uint8"
    init_value: str = "0U"
    binding_kind: str = "UNCONNECTED"  # "COM" | "INTER_SWC" | "UNCONNECTED"
    com_signal_name: str = ""
    com_signal_macro: str = ""
    shared_var_name: str = ""
    is_array: bool = False


@dataclass
class SwcClientCallArgModel:
    """Typed argument of a Client-Server operation."""

    name: str
    c_type: str = "uint8"
    direction: str = "IN"  # "IN" | "OUT" | "INOUT"


@dataclass
class SwcClientCallModel:
    """Resolved Client-Server R-Port operation call endpoint."""

    component_name: str
    swc_type_name: str
    port_name: str
    operation_name: str
    connected: bool = False
    server_component_name: str = ""
    server_port_name: str = ""
    server_symbol: str = ""
    port_defined_args: List[str] = field(default_factory=list)
    arguments: List[SwcClientCallArgModel] = field(default_factory=list)
    has_errors: bool = True


@dataclass
class SwcModePointModel:
    """Mode-switch / mode-access endpoint on an SWC P/R port."""

    component_name: str
    swc_type_name: str
    port_name: str
    mode_group_name: str
    kind: str  # "SWITCH" | "ACCESS"
    initial_mode: str = ""
    modes: List[str] = field(default_factory=list)


@dataclass
class SwcSharedBufferModel:
    """Global inter-SWC shared variable emitted in owner OsApplication C file."""

    var_name: str
    c_type: str
    init_value: str
    owner_os_application: str


@dataclass
class SwcComponentModel:
    """Phase 2/3 SWC component contract & implementation IR."""

    instance_name: str
    swc_type_name: str
    is_service: bool = False
    os_application: str = "SystemApplication_OsCore0"
    core_id: int = 0
    memmap_header: str = ""
    reads: List[SwcDataEndpointModel] = field(default_factory=list)
    writes: List[SwcDataEndpointModel] = field(default_factory=list)
    calls: List[SwcClientCallModel] = field(default_factory=list)
    mode_points: List[SwcModePointModel] = field(default_factory=list)
    runnables: List[SchedulableEntityModel] = field(default_factory=list)
    exclusive_areas: List[ExclusiveAreaModel] = field(default_factory=list)


@dataclass
class TaskCallEntry:
    """Ordered runnable or BSW schedulable entity invoked inside an OS Task body."""

    owner_name: str
    symbol: str
    position: Optional[int] = None
    is_swc: bool = False
    immediate_restart: bool = False


@dataclass
class OsTaskScheduleModel:
    """Executable OS Task schedule partitioned onto an OsApplication/Core."""

    task_name: str
    os_application: str = "SystemApplication_OsCore0"
    core_id: int = 0
    priority: int = 0
    task_type: str = "BASIC"
    is_init_task: bool = False
    os_events: List[str] = field(default_factory=list)
    calls: List[TaskCallEntry] = field(default_factory=list)


@dataclass
class OsActivationScheduleModel:
    """OS Alarm / ScheduleTable timing activation per Core/OsApplication."""

    name: str
    task_name: str
    os_application: str = "SystemApplication_OsCore0"
    core_id: int = 0
    alarm_name: Optional[str] = None
    schedule_table_name: Optional[str] = None
    offset_ms: float = 0.0
    period_ms: float = 10.0
    is_bsw: bool = True


@dataclass
class RteTypeDefEntry:
    """C typedef entry emitted into full ``Rte_Type.h``."""

    name: str
    category: str  # "VALUE" | "TYPE_REFERENCE" | "ARRAY" | "STRUCTURE" | "UNION"
    c_type: str = "uint8"
    array_size: Optional[int] = None
    fields: List[Tuple[str, str, Optional[int]]] = field(default_factory=list)
    enum_literals: List[Tuple[str, int]] = field(default_factory=list)


@dataclass
class RteProjectModel:
    """Aggregated cross-module model for Phase 1-3 RTE/SchM generation."""

    meta: RteMeta
    bsw_modules: List[BswModuleSchmModel] = field(default_factory=list)
    os_cores: List[str] = field(default_factory=list)
    os_applications: List[str] = field(default_factory=list)
    has_com: bool = False
    swc_components: List[SwcComponentModel] = field(default_factory=list)
    task_schedules: List[OsTaskScheduleModel] = field(default_factory=list)
    os_activations: List[OsActivationScheduleModel] = field(default_factory=list)
    rte_type_defs: List[RteTypeDefEntry] = field(default_factory=list)
    shared_buffers: List[SwcSharedBufferModel] = field(default_factory=list)


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
