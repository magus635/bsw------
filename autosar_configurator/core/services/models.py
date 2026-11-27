"""Pure-Python data models for the 5-tab System Services & Diagnostics Workbench."""

from dataclasses import dataclass, field
from typing import List, Optional


@dataclass
class ServiceDiagnostic:
    """Single cross-module validation finding surfaced by SystemServicesWorkbenchService."""

    severity: str  # "error" | "warning" | "info"
    code: str
    message: str
    module_name: str
    container_path: str = ""
    parameter_name: str = ""
    workbench_tab: int = 0  # 0: EcuM, 1: BswM, 2: Os, 3: Dcm/CanTp, 4: Det/CDD
    suggested_fix: str = ""


# ----------------------------------------------------------------------
# Tab 1: EcuM (Startup, Init Lists, Wakeup Sources, Reset/Shutdown)
# ----------------------------------------------------------------------


@dataclass
class EcuMGeneralInfo:
    """Aggregated EcuM general switches and global references."""

    loaded: bool = False
    main_function_period: Optional[float] = None
    dev_error_detect: bool = False
    slave_core_handling: bool = False
    include_dem: bool = False
    include_det: bool = False
    alarm_clock_present: bool = False
    default_shutdown_state: str = ""
    default_app_mode_ref: str = ""
    os_resource_ref: str = ""
    normal_mcu_mode_ref: str = ""
    flex_module_cfg_ref: str = ""
    partition_refs: List[str] = field(default_factory=list)
    general_path: str = ""
    shutdown_target_path: str = ""
    common_cfg_path: str = ""
    flex_cfg_path: str = ""


@dataclass
class EcuMInitItemRow:
    """Ordered initialization entry inside EcuMDriverInitListZero..Three."""

    list_name: str
    order_index: int
    short_name: str
    module_id: str
    service_name: str = ""
    header_file: str = ""
    additional_code: str = ""
    module_loaded: bool = True
    is_pseudo_module: bool = False
    container_path: str = ""


@dataclass
class EcuMWakeupSourceRow:
    """Wakeup source configured inside EcuMCommonConfiguration."""

    short_name: str
    wakeup_id: Optional[int] = None
    polling: bool = False
    validation_timeout: Optional[float] = None
    check_wakeup_timeout: Optional[float] = None
    comm_channel_ref: str = ""
    comm_channel_name: str = ""
    has_broken_ref: bool = False
    container_path: str = ""


@dataclass
class EcuMModeCauseRow:
    """EcuMResetMode or EcuMShutdownCause row."""

    kind: str  # "ResetMode" | "ShutdownCause"
    short_name: str
    mode_or_cause_id: Optional[int] = None
    container_path: str = ""


# ----------------------------------------------------------------------
# Tab 2: BswM (Mode Rules, Action Lists, Mode Ports & Groups)
# ----------------------------------------------------------------------


@dataclass
class BswMRuleRow:
    """BswM arbitration rule with decoded expression tree."""

    short_name: str
    rule_id: Optional[int] = None
    init_state: str = "BSWM_FALSE"
    nested_only: bool = False
    expression_name: str = ""
    expression_ref: str = ""
    decoded_expression: str = ""
    true_action_list: str = ""
    true_action_list_ref: str = ""
    false_action_list: str = ""
    false_action_list_ref: str = ""
    has_broken_ref: bool = False
    has_cycle: bool = False
    container_path: str = ""


@dataclass
class BswMActionListItemRow:
    """Ordered action entry inside a BswMActionList."""

    action_list_name: str
    short_name: str
    item_index: int
    abort_on_fail: bool = False
    target_ref: str = ""
    target_name: str = ""
    action_kind: str = ""
    action_summary: str = ""
    has_broken_ref: bool = False
    container_path: str = ""


@dataclass
class BswMActionListRow:
    """BswMActionList container summary."""

    short_name: str
    execution: str = "BSWM_CONDITION"
    item_count: int = 0
    is_init_list: bool = False
    container_path: str = ""


@dataclass
class BswMModePortRow:
    """BswMModeRequestPort summary."""

    short_name: str
    processing: str = ""
    arbitrate_on_init: bool = False
    source_kind: str = ""
    init_value: str = ""
    container_path: str = ""


@dataclass
class BswMModeGroupRow:
    """BswMRteModeDclGroup summary."""

    short_name: str
    init_mode: str = ""
    modes: List[str] = field(default_factory=list)
    container_path: str = ""


# ----------------------------------------------------------------------
# Tab 3: Os (Multi-Core, Applications, Tasks, ISRs, Timing, Sync)
# ----------------------------------------------------------------------


@dataclass
class OsGeneralInfo:
    """Global OsOS and OsHooks settings."""

    loaded: bool = False
    status: str = ""
    scalability_class: str = ""
    use_case: str = ""
    number_of_cores: Optional[int] = None
    actual_core_count: int = 0
    stack_monitoring: bool = False
    service_protection: bool = False
    error_hook: bool = False
    startup_hook: bool = False
    shutdown_hook: bool = False
    pre_task_hook: bool = False
    post_task_hook: bool = False
    master_core: str = ""
    system_timer: str = ""
    osos_path: str = ""


@dataclass
class OsCoreSummaryRow:
    """Per-core aggregation of OsCore, OsApplication, Partition, and stack budget."""

    core_name: str
    core_id: Optional[int] = None
    is_autostart: bool = False
    is_autosar: bool = False
    system_app: str = ""
    partition_name: str = ""
    idle_task: str = ""
    task_count: int = 0
    isr_count: int = 0
    alarm_count: int = 0
    total_stack_bytes: int = 0
    container_path: str = ""


@dataclass
class OsTaskRow:
    """OsTask row with owner OsApplication/Core and Alarm/ScheduleTable triggers."""

    short_name: str
    owner_app: str = ""
    core_name: str = ""
    priority: Optional[int] = None
    stack_size: Optional[int] = None
    activation: Optional[int] = None
    schedule: str = ""
    task_type: str = ""
    uses_fpu: bool = False
    triggers: List[str] = field(default_factory=list)
    has_invalid_stack: bool = False
    container_path: str = ""


@dataclass
class OsIsrRow:
    """OsIsr row with owner OsApplication/Core and interrupt properties."""

    short_name: str
    owner_app: str = ""
    core_name: str = ""
    category: str = ""
    interrupt_type: str = ""
    interrupt_source: Optional[int] = None
    priority: Optional[int] = None
    stack_size: Optional[int] = None
    enable_nesting: bool = False
    initial_enable: bool = False
    has_invalid_stack: bool = False
    container_path: str = ""


@dataclass
class OsTimingRow:
    """Unified row for OsCounter, OsAlarm, and OsScheduleTable."""

    kind: str  # "Counter" | "Alarm" | "ScheduleTable"
    short_name: str
    owner_app: str = ""
    counter_ref_name: str = ""
    detail: str = ""
    duration_or_max: Optional[int] = None
    repeating: Optional[bool] = None
    seconds_per_tick: Optional[float] = None
    has_broken_ref: bool = False
    container_path: str = ""


@dataclass
class OsSyncResourceRow:
    """Unified row for OsResource, OsSpinlock, and OsIocCommunication."""

    kind: str  # "Resource" | "Spinlock" | "Ioc"
    short_name: str
    policy_or_method: str = ""
    accessing_apps: List[str] = field(default_factory=list)
    detail: str = ""
    container_path: str = ""


# ----------------------------------------------------------------------
# Tab 4: Diagnostics (Dcm + CanTp + PduR TP + CanIf)
# ----------------------------------------------------------------------


@dataclass
class DiagChannelRow:
    """End-to-end UDS diagnostic chain across CanIf, CanTp, PduR TP, and Dcm."""

    name: str
    direction: str  # "RX" | "TX"
    addr_type: str = ""  # "PHYSICAL" | "FUNCTIONAL"
    protocol_name: str = ""
    dcm_pdu_name: str = ""
    dcm_pdu_id: Optional[int] = None
    pdur_path_name: str = ""
    cantp_channel_name: str = ""
    cantp_nsdu_name: str = ""
    cantp_npdu_name: str = ""
    cantp_fc_npdu_name: str = ""
    canif_pdu_name: str = ""
    can_id: Optional[int] = None
    can_id_hex: str = "-"
    can_id_type: str = ""
    dlc: Optional[int] = None
    bs: Optional[int] = None
    stmin: Optional[float] = None
    padding: str = ""
    dl: Optional[int] = None
    nar: Optional[float] = None
    nbr: Optional[float] = None
    ncr: Optional[float] = None
    nas: Optional[float] = None
    nbs: Optional[float] = None
    ncs: Optional[float] = None
    buffer_name: str = ""
    buffer_size: Optional[int] = None
    comm_channel_name: str = ""
    chain_complete: bool = True
    chain_note: str = ""
    dcm_container_path: str = ""
    cantp_nsdu_path: str = ""


@dataclass
class DcmServiceRow:
    """DcmDsdService row in UDS service table."""

    table_name: str
    short_name: str
    sid: Optional[int] = None
    sid_hex: str = "-"
    service_label: str = ""
    subfunc_avail: bool = False
    used: bool = True
    subservice_count: int = 0
    subservice_summary: str = ""
    container_path: str = ""


@dataclass
class DcmSessionRow:
    """DcmDspSessionRow entry."""

    short_name: str
    level: Optional[int] = None
    level_hex: str = "-"
    p2_server_max: Optional[float] = None
    p2_star_server_max: Optional[float] = None
    for_boot: str = ""
    container_path: str = ""


@dataclass
class DcmSecurityRow:
    """DcmDspSecurityRow entry."""

    short_name: str
    level: Optional[int] = None
    num_attempts: Optional[int] = None
    delay_time: Optional[float] = None
    seed_size: Optional[int] = None
    key_size: Optional[int] = None
    container_path: str = ""


@dataclass
class DcmDidRoutineRow:
    """DcmDspDid or DcmDspRoutine entry."""

    kind: str  # "DID" | "Routine"
    short_name: str
    identifier: Optional[int] = None
    identifier_hex: str = "-"
    used: bool = True
    detail: str = ""
    container_path: str = ""


# ----------------------------------------------------------------------
# Tab 5: Det, CDD & Platform Service Extensions
# ----------------------------------------------------------------------


@dataclass
class DetGeneralInfo:
    """DetGeneral and registered DetModule summary."""

    loaded: bool = False
    enable_det: bool = False
    version_info_api: bool = False
    ext_debug_support: bool = False
    global_filter_size: Optional[int] = None
    break_filter_size: Optional[int] = None
    log_buffer_size: Optional[int] = None
    module_ids: List[int] = field(default_factory=list)
    general_path: str = ""


@dataclass
class ModuleDetFlagRow:
    """Per-module DevErrorDetect / DET enablement flag."""

    module_name: str
    param_name: str
    enabled: bool = False
    container_path: str = ""
    locked: bool = False


@dataclass
class CddPlatformModuleRow:
    """Inventory row for CDD and platform/service-extension modules."""

    module_name: str
    kind: str  # "CDD" | "Platform" | "Service"
    definition_ref: str = ""
    config_variant: str = ""
    container_count: int = 0
    in_ecum_init: bool = False
    in_rte_bsw: bool = False
    in_pdur: bool = False
    summary: str = ""
    first_container_path: str = ""
