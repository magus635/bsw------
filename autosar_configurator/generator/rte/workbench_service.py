"""Pure-Python domain service backing the 4-tab RTE / SchM Configuration Workbench."""

import copy
import difflib
import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

from ...core import project_paths
from ...core.config_manager import PreLockedError
from ...core.model.configuration_model import (
    EcucContainerValue,
    EcucParameterValue,
    EcucReferenceValue,
)
from ...core.model.ecuc_paths import strip_ecuc_prefixes
from .extractor import RteModelExtractor, _ar_leaf, _as_bool, _parse_int
from .generator import (
    RteSchMGenerator,
    has_project_overlay_templates,
    run_rte_schm_pipeline,
)
from .ib_parser import BswIbEventData, BswIbImplData, BswIbIndex, BswIbModuleData
from .model import RteGenerationReport, RtePreviewFile
from .swc_parser import SwcSystemIndex, SwcTypeData

EA_MECHANISMS: Tuple[str, ...] = (
    "ALL_INTERRUPT_BLOCKING",
    "OS_INTERRUPT_BLOCKING",
    "OS_RESOURCE",
    "OS_SPINLOCK",
    "COOPERATIVE_RUNNABLE_PLACEMENT",
    "NONE",
    "CUSTOM",
)
GENERATION_MODES: Tuple[str, ...] = ("COMPATIBILITY_MODE", "VENDOR_MODE")
OPTIMIZATION_MODES: Tuple[str, ...] = ("RUNTIME", "MEMORY", "NONE")
_NON_BSW_AUTO_SUGGEST = frozenset({"Rte", "Os", "EcuC", "MemMap"})


@dataclass
class BswInstanceRow:
    """Summary row for Tab 1 (BSW instances vs loaded modules and IB metadata)."""

    module_name: str
    instance_name: str
    status: str  # "active" | "unloaded" | "unregistered"
    api_name: str
    memmap_header: str
    entity_count: int
    ea_configured_count: int
    ea_ib_count: int
    mapping_count: int
    ib_source: str


@dataclass
class ExclusiveAreaRow:
    """Matrix row for Tab 2 (SchM ExclusiveArea protection settings)."""

    module_name: str
    api_name: str
    instance_name: str
    ea_name: str
    ea_ref: Optional[str]
    configured: bool
    mechanism: str
    os_resource: Optional[str]
    os_spinlock: Optional[str]
    generate_function: bool
    validation_error: Optional[str] = None


@dataclass
class OsTaskInfo:
    """OS Task metadata for Tab 3 (Event-to-Task mapping)."""

    name: str
    priority: Optional[int] = None
    task_type: Optional[str] = None
    stack_size: Optional[int] = None
    missing_in_os: bool = False


@dataclass
class TaskEventMappingRow:
    """Mapping row for Tab 3 (mapped BSW/SWC events and unmapped BSW events)."""

    instance_name: str
    module_name: str
    api_name: str
    mapping_name: str
    event_name: str
    event_ref: Optional[str]
    event_kind: str
    entity_name: Optional[str]
    period_sec: Optional[float]
    task_name: Optional[str]
    position: Optional[int]
    immediate_restart: bool
    is_swc: bool = False
    has_ecuc_container: bool = True
    used_os_event: Optional[str] = None
    used_os_alarm: Optional[str] = None
    used_os_schtbl_ep: Optional[str] = None


@dataclass
class OsActivationInfo:
    """Stage-3 ``RteOsInteraction/RteUsedOsActivation`` summary row."""

    name: str
    container_path: str
    task_name: Optional[str] = None
    alarm_name: Optional[str] = None
    schedule_table_name: Optional[str] = None
    expected_tick_duration: Optional[float] = None
    expected_offset: Optional[float] = None


@dataclass
class RteSchmDiagnostic:
    """Structured diagnostic emitted by :meth:`RteWorkbenchService.collect_diagnostics`."""

    severity: str  # "error" | "warning" | "info"
    code: str
    message: str
    container_path: str
    parameter_name: Optional[str] = None
    workbench_tab: int = 0
    suggested_fix: Optional[str] = None


@dataclass
class RteGenerationSettings:
    """Global flags from ``RteGeneration`` and ``RteBswGeneral`` for Tab 4."""

    enable_multi_core: bool = False
    enable_memory_protection: bool = False
    dev_error_detect: bool = False
    dev_error_detect_uninit: bool = False
    disable_rte_init_memory: bool = False
    vfb_trace_enabled: bool = False
    schm_version_info_api: bool = False
    generation_mode: str = "COMPATIBILITY_MODE"
    optimization_mode: str = "RUNTIME"


@dataclass
class RteConfigSnapshot:
    """Deep-cloned snapshot of ``Rte`` top-level containers, dirty flag, and Phase 2/3 overlays."""

    containers: List[EcucContainerValue]
    is_modified: bool
    data_mappings: List[Dict[str, Any]] = field(default_factory=list)
    service_connectors: List[Dict[str, Any]] = field(default_factory=list)


def _clone_param_value(param: EcucParameterValue) -> EcucParameterValue:
    return EcucParameterValue(
        definition_ref=param.definition_ref,
        value=param.value[:] if isinstance(param.value, list) else param.value,
        index=param.index,
        dest_type=param.dest_type,
        is_modified=param.is_modified,
        last_modified=param.last_modified,
    )


def _clone_ref_value(ref: EcucReferenceValue) -> EcucReferenceValue:
    return EcucReferenceValue(
        definition_ref=ref.definition_ref,
        value_ref=ref.value_ref,
        dest_type=ref.dest_type,
        value_ref_dest=ref.value_ref_dest,
        context_element_refs=list(ref.context_element_refs),
        is_instance_reference=ref.is_instance_reference,
        index=ref.index,
        is_modified=ref.is_modified,
    )


def _clone_container_tree(src: EcucContainerValue) -> EcucContainerValue:
    """Clone an ``EcucContainerValue`` tree preserving ARXML metadata without runtime pointers."""
    cloned = EcucContainerValue(
        short_name=src.short_name,
        definition_ref=src.definition_ref,
        def_dest_type=src.def_dest_type,
        index=src.index,
        variant=src.variant,
        uuid=src.uuid,
        is_modified=src.is_modified,
        last_modified=src.last_modified,
        unknown_parameters=copy.deepcopy(src.unknown_parameters),
    )
    for pname, pval in src.parameter_values.items():
        cloned.parameter_values[pname] = _clone_param_value(pval)
    for pname, plist in src.multi_parameter_values.items():
        cloned.multi_parameter_values[pname] = [_clone_param_value(p) for p in plist]
    for rname, rval in src.reference_values.items():
        cloned.reference_values[rname] = _clone_ref_value(rval)
    for rname, rlist in src.multi_reference_values.items():
        cloned.multi_reference_values[rname] = [_clone_ref_value(r) for r in rlist]
    for sub in getattr(src, "sub_containers", []) or []:
        cloned.add_sub_container(_clone_container_tree(sub))
    cloned.is_modified = src.is_modified
    cloned.last_modified = src.last_modified
    return cloned


def snapshot_rte_config(rte_cfg: Any, *, project: Any = None) -> RteConfigSnapshot:
    """Capture an isolated snapshot of ``rte_cfg`` containers, dirty flag, and Phase 2/3 overlays."""
    mappings = [copy.deepcopy(x) for x in (getattr(project, "rte_data_mappings", []) or [])] if project is not None else []
    connectors = [copy.deepcopy(x) for x in (getattr(project, "rte_service_connectors", []) or [])] if project is not None else []
    return RteConfigSnapshot(
        containers=[_clone_container_tree(c) for c in getattr(rte_cfg, "containers", []) or []],
        is_modified=bool(getattr(rte_cfg, "is_modified", False)),
        data_mappings=mappings,
        service_connectors=connectors,
    )


def restore_rte_config(
    rte_cfg: Any,
    snapshot: RteConfigSnapshot,
    *,
    project: Any = None,
) -> None:
    """Restore ``rte_cfg`` containers/registry and Phase 2/3 overlays to ``snapshot``."""
    if project is not None and hasattr(project, "unregister_container_references"):
        for existing in list(getattr(rte_cfg, "containers", []) or []):
            project.unregister_container_references(existing)
    rte_cfg.containers.clear()
    if hasattr(rte_cfg, "_instance_registry"):
        rte_cfg._instance_registry.clear()
    for snap_c in snapshot.containers:
        rte_cfg.add_container(_clone_container_tree(snap_c))
    rte_cfg.is_modified = snapshot.is_modified
    if project is not None:
        if hasattr(project, "rte_data_mappings"):
            project.rte_data_mappings = [copy.deepcopy(x) for x in (getattr(snapshot, "data_mappings", []) or [])]
        if hasattr(project, "rte_service_connectors"):
            project.rte_service_connectors = [copy.deepcopy(x) for x in (getattr(snapshot, "service_connectors", []) or [])]
        resolve_fn = getattr(project, "resolve_all_references", None)
        if callable(resolve_fn):
            resolve_fn(force=True)
        build_fn = getattr(project, "build_reverse_reference_index", None)
        if callable(build_fn):
            build_fn()


@dataclass
class SyncSummary:
    """Result counts returned by :meth:`RteWorkbenchService.sync_bsw_instances`."""

    added_instances: int = 0
    added_exclusive_areas: int = 0
    removed_instances: int = 0
    skipped_locked: List[str] = field(default_factory=list)


@dataclass
class DataMappingRow:
    """Tab 4 row mapping an SWC SR P/R port to a ComSignal or inter-SWC connector."""

    component_name: str
    swc_type_name: str
    port_name: str
    data_element_name: str
    direction: str  # "TX" | "RX"
    c_type: str
    system_signal_name: str = ""
    system_signal_ref: str = ""
    com_signal_name: str = ""
    com_signal_direction: str = ""
    status: str = "unmapped"  # "mapped" | "inter_swc" | "unmapped" | "broken_com" | "direction_mismatch"
    source: str = "none"  # "arxml" | "overlay" | "none"


@dataclass
class ServicePortRow:
    """Tab 5 row describing an SWC Client/Mode/Service R-Port and its connected provider."""

    requester_component: str
    requester_swc_type: str
    requester_port: str
    interface_name: str
    interface_kind: str  # "CS" | "MODE" | "SR"
    is_service: bool
    provider_component: str = ""
    provider_port: str = ""
    server_symbol: str = ""
    status: str = "unconnected"  # "connected" | "unconnected" | "broken"
    source: str = "none"  # "arxml" | "overlay" | "none"


@dataclass
class SwcInstanceSummaryRow:
    """Tab 5 bottom summary of SWC instances, OsApplication core partitioning, and mappings."""

    instance_name: str
    swc_type_name: str
    is_service: bool
    os_application: str
    core_id: int
    port_count: int
    runnable_count: int
    mapped_events: int
    unmapped_events: int


def format_period_label(period_sec: Optional[float]) -> str:
    """Format a timing period in seconds into a human-friendly ``ms`` / ``s`` label."""
    if period_sec is None:
        return "-"
    if period_sec == 0:
        return "0 s"
    if period_sec < 1.0:
        return f"{period_sec * 1000:g} ms"
    return f"{period_sec:g} s"


def compute_preview_diff(preview_file: RtePreviewFile) -> str:
    """Compute a non-mutating unified diff against the existing file on disk."""
    if preview_file.status == "unchanged":
        return "/* 与磁盘现有文件完全一致，无差异 */\n"
    if preview_file.status == "preserved":
        return "/* 磁盘已存在既有桩文件，生成时将保留原文件不覆盖 */\n"

    new_lines = preview_file.content.splitlines()
    if preview_file.status == "new" or not preview_file.target_path.is_file():
        diff_lines = list(
            difflib.unified_diff(
                [],
                new_lines,
                fromfile="/dev/null",
                tofile=f"generated/{preview_file.filename}",
                lineterm="",
            )
        )
    else:
        old_lines = preview_file.target_path.read_text(encoding="utf-8", errors="replace").splitlines()
        diff_lines = list(
            difflib.unified_diff(
                old_lines,
                new_lines,
                fromfile=f"disk/{preview_file.filename}",
                tofile=f"generated/{preview_file.filename}",
                lineterm="",
            )
        )
        if not diff_lines:
            return "/* 与磁盘现有文件完全一致，无差异 */\n"

    return ("\n".join(diff_lines) + "\n") if diff_lines else ""


class RteWorkbenchService:
    """Qt-free ECUC/InternalBehavior coordinator for the RTE/SchM Workbench."""

    def __init__(self, project: Any) -> None:
        self.project = project
        self._ib_cache: Optional[BswIbIndex] = None
        self._swc_cache: Optional[SwcSystemIndex] = None

    # ------------------------------------------------------------------
    # Internal lookups & ARXML write-back helpers
    # ------------------------------------------------------------------

    def _managers(self) -> Dict[str, Any]:
        return getattr(self.project, "module_managers", {}) or {}

    def _rte_manager(self) -> Optional[Any]:
        return self._managers().get("Rte")

    def _rte_cfg(self) -> Optional[Any]:
        mgr = self._rte_manager()
        return getattr(mgr, "configuration", None) if mgr is not None else None

    def has_rte_module(self) -> bool:
        return self._rte_cfg() is not None

    def reload_ib_index(self) -> BswIbIndex:
        self._ib_cache = RteModelExtractor._load_ib_index(self.project)
        return self._ib_cache

    def _ib_index(self) -> BswIbIndex:
        if self._ib_cache is None:
            return self.reload_ib_index()
        return self._ib_cache

    def reload_swc_index(self) -> SwcSystemIndex:
        self._swc_cache = RteModelExtractor._load_swc_index(self.project)
        return self._swc_cache

    def _swc_index(self) -> SwcSystemIndex:
        if self._swc_cache is None:
            return self.reload_swc_index()
        return self._swc_cache

    def _base_def(self) -> str:
        rte_cfg = self._rte_cfg()
        dref = getattr(rte_cfg, "definition_ref", None) if rte_cfg is not None else None
        return (dref or "/MICROSAR/Rte").rstrip("/")

    def _mark_rte_modified(self) -> None:
        rte_cfg = self._rte_cfg()
        if rte_cfg is not None:
            rte_cfg.is_modified = True
        if self.project is not None and hasattr(self.project, "is_modified"):
            self.project.is_modified = True

    def _check_editable(self, instance: Any, name: Optional[str] = None) -> None:
        rte_mgr = self._rte_manager()
        checker = getattr(rte_mgr, "check_editable", None) if rte_mgr is not None else None
        if callable(checker):
            checker(instance, name)

    def _module_ref_prefix(self, module_name: str, container_name: Optional[str] = None) -> str:
        proj_type = getattr(self.project, "project_type", None)
        type_name = getattr(proj_type, "name", "")
        if type_name == "EB_TRESOS":
            return f"/{module_name}/{container_name}" if container_name else f"/{module_name}/{module_name}"
        return f"/ActiveEcuC/{module_name}/{container_name}" if container_name else f"/ActiveEcuC/{module_name}"

    def capture_snapshot(self) -> Optional[RteConfigSnapshot]:
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            return None
        return snapshot_rte_config(rte_cfg, project=self.project)

    def restore_snapshot(self, snapshot: Optional[RteConfigSnapshot]) -> None:
        rte_cfg = self._rte_cfg()
        if rte_cfg is None or snapshot is None:
            return
        restore_rte_config(rte_cfg, snapshot, project=self.project)

    def _set_param(
        self,
        container: EcucContainerValue,
        name: str,
        value: Any,
        dest_type: str,
    ) -> None:
        self._check_editable(container, name)
        base = (container.definition_ref or self._base_def()).rstrip("/")
        container.set_parameter_value(name, value, f"{base}/{name}")
        pval = container.parameter_values[name]
        pval.dest_type = dest_type
        self._mark_rte_modified()

    def _set_ref(
        self,
        container: EcucContainerValue,
        name: str,
        value_ref: str,
        *,
        dest_type: str,
        value_ref_dest: str,
    ) -> None:
        self._check_editable(container, name)
        base = (container.definition_ref or self._base_def()).rstrip("/")
        container.set_reference_value(
            name,
            value_ref,
            f"{base}/{name}",
            dest_type=dest_type,
            value_ref_dest=value_ref_dest,
        )
        self._mark_rte_modified()

    def _remove_ref(self, container: EcucContainerValue, name: str) -> bool:
        if name in container.reference_values:
            self._check_editable(container, name)
            del container.reference_values[name]
            container.mark_modified()
            self._mark_rte_modified()
            return True
        return False

    def _bsw_instance_containers(self) -> List[EcucContainerValue]:
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            return []
        return [
            c
            for c in getattr(rte_cfg, "containers", []) or []
            if _ar_leaf(getattr(c, "definition_ref", None)) == "RteBswModuleInstance"
        ]

    def _swc_instance_containers(self) -> List[EcucContainerValue]:
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            return []
        return [
            c
            for c in getattr(rte_cfg, "containers", []) or []
            if _ar_leaf(getattr(c, "definition_ref", None)) == "RteSwComponentInstance"
        ]

    @staticmethod
    def _target_mod_of_instance(container: EcucContainerValue) -> str:
        cfg_ref_v = container.reference_values.get("RteBswModuleConfigurationRef")
        cfg_ref = cfg_ref_v.value_ref if cfg_ref_v else None
        return RteModelExtractor._resolve_target_module_name(cfg_ref, container.short_name)

    def _find_bsw_instance(self, instance_name: str) -> Optional[EcucContainerValue]:
        for c in self._bsw_instance_containers():
            if c.short_name == instance_name:
                return c
        return None

    def _find_or_create_top_container(self, short_name: str, def_leaf: str) -> EcucContainerValue:
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            raise ValueError("当前工程未加载 Rte 模块或其配置为空")
        for c in getattr(rte_cfg, "containers", []) or []:
            if _ar_leaf(getattr(c, "definition_ref", None)) == def_leaf:
                return c
        inst = EcucContainerValue(
            short_name=short_name,
            definition_ref=f"{self._base_def()}/{def_leaf}",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        self._check_editable(rte_cfg, None)
        rte_cfg.add_container(inst)
        self._mark_rte_modified()
        return inst

    def _pkg_impl_meta(self, module_name: str) -> Dict[str, Any]:
        pkg = (getattr(self.project, "packages", {}) or {}).get(module_name)
        if pkg is None:
            return {}
        try:
            return pkg.read_impl_metadata() or {}
        except Exception:
            return {}

    def _resolve_module_impl_and_ib(
        self,
        module_name: str,
        container: Optional[EcucContainerValue] = None,
        ib_index: Optional[BswIbIndex] = None,
    ) -> Tuple[str, Optional[BswIbImplData], Optional[BswIbModuleData], Dict[str, Any]]:
        idx = ib_index or self._ib_index()
        pkg_impl = self._pkg_impl_meta(module_name)

        impl_ref: Optional[str] = None
        if container is not None:
            impl_v = container.reference_values.get("RteBswImplementationRef")
            if impl_v and impl_v.value_ref:
                impl_ref = impl_v.value_ref.strip().rstrip("/")
        ib_impl = idx.impls_by_path.get(impl_ref) if impl_ref else None
        if ib_impl is None and pkg_impl.get("ar_path"):
            ib_impl = idx.impls_by_path.get(str(pkg_impl["ar_path"]).strip().rstrip("/"))
        if ib_impl is None:
            for cand in idx.impls_by_path.values():
                if cand.short_name in (f"{module_name}_Impl", module_name):
                    ib_impl = cand
                    break

        vendor_id = pkg_impl.get("vendor_id") or (ib_impl.vendor_id if ib_impl else None)
        vendor_infix = pkg_impl.get("vendor_api_infix") or (ib_impl.vendor_api_infix if ib_impl else None)
        if vendor_infix and vendor_id:
            api_name = f"{module_name}_{str(vendor_id).strip()}_{str(vendor_infix).strip()}"
        else:
            api_name = module_name

        if container is not None:
            ib_data = RteModelExtractor._resolve_ib_data(
                container=container,
                target_mod=module_name,
                api_name=api_name,
                impl_data=ib_impl,
                ib_index=idx,
            )
        else:
            ib_data = None
            if ib_impl is not None and ib_impl.behavior_ref:
                ib_data = idx.by_behavior_path.get(ib_impl.behavior_ref.strip().rstrip("/"))
            if ib_data is None:
                cands = idx.by_module_name.get(module_name, [])
                if cands:
                    ib_data = cands[0]
        return api_name, ib_impl, ib_data, pkg_impl

    # ------------------------------------------------------------------
    # Tab 1: BSW Module Instances & Sync
    # ------------------------------------------------------------------

    def list_bsw_instance_rows(self) -> List[BswInstanceRow]:
        """List active, unloaded, and unregistered loaded BSW modules."""
        if not self.has_rte_module():
            return []
        managers = self._managers()
        ib_index = self._ib_index()
        memmap_mods = RteModelExtractor._collect_memmap_modules(managers.get("MemMap"))

        rows: List[BswInstanceRow] = []
        registered_mods: Set[str] = set()

        for container in self._bsw_instance_containers():
            target_mod = self._target_mod_of_instance(container)
            if not target_mod or target_mod == "Rte":
                continue
            registered_mods.add(target_mod)
            is_loaded = target_mod in managers and getattr(managers[target_mod], "configuration", None) is not None

            ea_subs = [
                sub
                for sub in getattr(container, "sub_containers", []) or []
                if _ar_leaf(getattr(sub, "definition_ref", None)) == "RteBswExclusiveAreaImpl"
            ]
            mapped_ev_count = sum(
                1
                for sub in getattr(container, "sub_containers", []) or []
                if _ar_leaf(getattr(sub, "definition_ref", None)) == "RteBswEventToTaskMapping"
                and (
                    sub.reference_values.get("RteBswMappedToTaskRef") is not None
                    and bool(sub.reference_values["RteBswMappedToTaskRef"].value_ref)
                )
            )

            api_name, ib_impl, ib_data, _ = self._resolve_module_impl_and_ib(
                target_mod, container=container, ib_index=ib_index
            )
            if is_loaded:
                mod_model = RteModelExtractor._build_bsw_module_model(
                    project=self.project,
                    container=container,
                    target_mod=target_mod,
                    ib_index=ib_index,
                    memmap_mods=memmap_mods,
                    report=RteGenerationReport(),
                )
                rows.append(
                    BswInstanceRow(
                        module_name=target_mod,
                        instance_name=container.short_name,
                        status="active",
                        api_name=mod_model.api_name,
                        memmap_header=mod_model.memmap_header,
                        entity_count=len(mod_model.schedulable_entities),
                        ea_configured_count=len(ea_subs),
                        ea_ib_count=len(ib_data.exclusive_areas) if ib_data else 0,
                        mapping_count=mapped_ev_count,
                        ib_source=ib_data.source_file if ib_data else "",
                    )
                )
            else:
                rows.append(
                    BswInstanceRow(
                        module_name=target_mod,
                        instance_name=container.short_name,
                        status="unloaded",
                        api_name=api_name,
                        memmap_header="-",
                        entity_count=len(ib_data.schedulable_entities) if ib_data else 0,
                        ea_configured_count=len(ea_subs),
                        ea_ib_count=len(ib_data.exclusive_areas) if ib_data else 0,
                        mapping_count=mapped_ev_count,
                        ib_source=ib_data.source_file if ib_data else "",
                    )
                )

        for mod_name in sorted(managers):
            if mod_name in registered_mods:
                continue
            mgr = managers[mod_name]
            if getattr(mgr, "configuration", None) is None:
                continue
            api_name, ib_impl, ib_data, _ = self._resolve_module_impl_and_ib(
                mod_name, container=None, ib_index=ib_index
            )
            has_ib_behavior = bool(
                ib_data and (ib_data.schedulable_entities or ib_data.exclusive_areas or ib_data.events)
            )
            if mod_name in _NON_BSW_AUTO_SUGGEST and not has_ib_behavior:
                continue
            rows.append(
                BswInstanceRow(
                    module_name=mod_name,
                    instance_name="",
                    status="unregistered",
                    api_name=api_name,
                    memmap_header=ib_impl.memmap_artifact_header if (ib_impl and ib_impl.memmap_artifact_header) else f"{api_name}_MemMap.h",
                    entity_count=len(ib_data.schedulable_entities) if ib_data else 0,
                    ea_configured_count=0,
                    ea_ib_count=len(ib_data.exclusive_areas) if ib_data else 0,
                    mapping_count=0,
                    ib_source=ib_data.source_file if ib_data else "",
                )
            )

        status_order = {"active": 0, "unloaded": 1, "unregistered": 2}
        rows.sort(key=lambda r: (status_order.get(r.status, 9), r.module_name))
        return rows

    def add_bsw_instance(
        self,
        module_name: str,
        *,
        populate_exclusive_areas: bool = True,
    ) -> EcucContainerValue:
        """Create and register an ``RteBswModuleInstance`` container for ``module_name``."""
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            raise ValueError("当前工程未加载 Rte 模块或其配置为空")

        for existing in self._bsw_instance_containers():
            if existing.short_name == module_name or self._target_mod_of_instance(existing) == module_name:
                return existing

        ib_index = self._ib_index()
        _, ib_impl, ib_data, pkg_impl = self._resolve_module_impl_and_ib(
            module_name, container=None, ib_index=ib_index
        )
        impl_ref = pkg_impl.get("ar_path") or (ib_impl.ar_path if ib_impl else None)

        inst = EcucContainerValue(
            short_name=module_name,
            definition_ref=f"{self._base_def()}/RteBswModuleInstance",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        self._check_editable(rte_cfg, None)
        rte_cfg.add_container(inst)
        try:
            self._set_ref(
                inst,
                "RteBswModuleConfigurationRef",
                self._module_ref_prefix(module_name),
                dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                value_ref_dest="ECUC-MODULE-CONFIGURATION-VALUES",
            )
            if impl_ref:
                self._set_ref(
                    inst,
                    "RteBswImplementationRef",
                    str(impl_ref).strip(),
                    dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                    value_ref_dest="BSW-IMPLEMENTATION",
                )
            if populate_exclusive_areas and ib_data is not None:
                path_by_ea = {ea_sn: ea_path for ea_path, ea_sn in ib_data.exclusive_area_paths.items()}
                for ea_name in ib_data.exclusive_areas:
                    self._create_exclusive_area_sub(inst, ea_name, ea_ref=path_by_ea.get(ea_name))
        except PreLockedError:
            rte_cfg.remove_container(inst)
            raise

        self._mark_rte_modified()
        return inst

    def remove_bsw_instance(self, instance_name: str) -> bool:
        """Remove the named ``RteBswModuleInstance`` from ``Rte`` configuration."""
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            return False
        inst = self._find_bsw_instance(instance_name)
        if inst is None:
            return False
        self._check_editable(inst, None)
        rte_cfg.remove_container(inst)
        rte_mgr = self._rte_manager()
        if rte_mgr is not None and getattr(rte_mgr, "project_context", None) is not None:
            rte_mgr.project_context.unregister_container_references(inst)
        self._mark_rte_modified()
        return True

    def sync_bsw_instances(
        self,
        *,
        add_missing_modules: bool = False,
        sync_exclusive_areas: bool = True,
        remove_unloaded: bool = False,
    ) -> SyncSummary:
        """Synchronize ``RteBswModuleInstance`` rows and IB ExclusiveAreas."""
        summary = SyncSummary()
        rows = self.list_bsw_instance_rows()

        if remove_unloaded:
            for row in rows:
                if row.status != "unloaded":
                    continue
                try:
                    if self.remove_bsw_instance(row.instance_name):
                        summary.removed_instances += 1
                except PreLockedError as exc:
                    summary.skipped_locked.append(str(exc))

        if add_missing_modules:
            for row in rows:
                if row.status != "unregistered":
                    continue
                try:
                    self.add_bsw_instance(row.module_name, populate_exclusive_areas=False)
                    summary.added_instances += 1
                except PreLockedError as exc:
                    summary.skipped_locked.append(str(exc))

        if sync_exclusive_areas:
            added_ea, locked_ea = self._sync_missing_exclusive_areas_detailed()
            summary.added_exclusive_areas = added_ea
            summary.skipped_locked.extend(locked_ea)

        return summary

    # ------------------------------------------------------------------
    # Tab 2: SchM ExclusiveArea Matrix
    # ------------------------------------------------------------------

    def list_os_resources(self) -> List[str]:
        return self._list_os_names("OsResource")

    def list_os_spinlocks(self) -> List[str]:
        return self._list_os_names("OsSpinlock")

    def _list_os_names(self, def_leaf: str) -> List[str]:
        os_mgr = self._managers().get("Os")
        os_cfg = getattr(os_mgr, "configuration", None) if os_mgr is not None else None
        if os_cfg is None:
            return []
        names: List[str] = []
        seen: Set[str] = set()

        def _walk(c: EcucContainerValue) -> None:
            if _ar_leaf(getattr(c, "definition_ref", None)) == def_leaf:
                if c.short_name and c.short_name not in seen:
                    seen.add(c.short_name)
                    names.append(c.short_name)
            for sub in getattr(c, "sub_containers", []) or []:
                _walk(sub)

        for top in getattr(os_cfg, "containers", []) or []:
            _walk(top)
        return sorted(names)

    def _create_exclusive_area_sub(
        self,
        inst: EcucContainerValue,
        ea_name: str,
        *,
        ea_ref: Optional[str] = None,
        mechanism: str = "ALL_INTERRUPT_BLOCKING",
        os_resource: Optional[str] = None,
        os_spinlock: Optional[str] = None,
        generate_function: bool = False,
    ) -> EcucContainerValue:
        self._check_editable(inst, None)
        sub = EcucContainerValue(
            short_name=ea_name,
            definition_ref=f"{inst.definition_ref.rstrip('/')}/RteBswExclusiveAreaImpl",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        inst.add_sub_container(sub)
        try:
            if ea_ref:
                self._set_ref(
                    sub,
                    "RteBswExclusiveAreaRef",
                    ea_ref,
                    dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                    value_ref_dest="EXCLUSIVE-AREA",
                )
            self._apply_ea_fields(
                sub,
                mechanism=mechanism,
                os_resource=os_resource,
                os_spinlock=os_spinlock,
                generate_function=generate_function,
            )
        except PreLockedError:
            inst.remove_sub_container(sub)
            rte_cfg = self._rte_cfg()
            if rte_cfg is not None:
                rte_cfg._unregister_instance(sub)
            raise
        return sub

    def _apply_ea_fields(
        self,
        sub: EcucContainerValue,
        *,
        mechanism: str,
        os_resource: Optional[str],
        os_spinlock: Optional[str],
        generate_function: bool,
    ) -> None:
        mech = mechanism.strip()
        if mech not in EA_MECHANISMS:
            raise ValueError(f"不支持的临界区保护机制: {mech}")
        effective_gen_fn = True if mech == "CUSTOM" else bool(generate_function)
        self._set_param(sub, "RteExclusiveAreaImplMechanism", mech, "ECUC-ENUMERATION-PARAM-DEF")
        self._set_param(
            sub,
            "RteExclusiveAreaGenerateFunction",
            effective_gen_fn,
            "ECUC-BOOLEAN-PARAM-DEF",
        )
        if mech == "OS_RESOURCE":
            self._remove_ref(sub, "RteBswExclusiveAreaOsSpinlockRef")
            if os_resource:
                self._set_ref(
                    sub,
                    "RteBswExclusiveAreaOsResourceRef",
                    self._module_ref_prefix("Os", os_resource),
                    dest_type="ECUC-REFERENCE-DEF",
                    value_ref_dest="ECUC-CONTAINER-VALUE",
                )
            else:
                self._remove_ref(sub, "RteBswExclusiveAreaOsResourceRef")
        elif mech == "OS_SPINLOCK":
            self._remove_ref(sub, "RteBswExclusiveAreaOsResourceRef")
            if os_spinlock:
                self._set_ref(
                    sub,
                    "RteBswExclusiveAreaOsSpinlockRef",
                    self._module_ref_prefix("Os", os_spinlock),
                    dest_type="ECUC-REFERENCE-DEF",
                    value_ref_dest="ECUC-CONTAINER-VALUE",
                )
            else:
                self._remove_ref(sub, "RteBswExclusiveAreaOsSpinlockRef")
        else:
            self._remove_ref(sub, "RteBswExclusiveAreaOsResourceRef")
            self._remove_ref(sub, "RteBswExclusiveAreaOsSpinlockRef")

    def list_exclusive_area_rows(self) -> List[ExclusiveAreaRow]:
        """Collect all configured and IB-declared ExclusiveAreas for active BSW instances."""
        if not self.has_rte_module():
            return []
        managers = self._managers()
        ib_index = self._ib_index()
        rows: List[ExclusiveAreaRow] = []

        for container in self._bsw_instance_containers():
            target_mod = self._target_mod_of_instance(container)
            if not target_mod or target_mod == "Rte":
                continue
            if target_mod not in managers or getattr(managers[target_mod], "configuration", None) is None:
                continue

            api_name, _, ib_data, _ = self._resolve_module_impl_and_ib(
                target_mod, container=container, ib_index=ib_index
            )
            ib_ea_paths: Dict[str, str] = (
                {ea_sn: ea_path for ea_path, ea_sn in ib_data.exclusive_area_paths.items()}
                if ib_data is not None
                else {}
            )

            configured_subs: Dict[str, EcucContainerValue] = {}
            for sub in getattr(container, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswExclusiveAreaImpl":
                    continue
                ea_ref_v = sub.reference_values.get("RteBswExclusiveAreaRef")
                ea_name = _ar_leaf(ea_ref_v.value_ref if ea_ref_v else None) or sub.short_name
                configured_subs[ea_name] = sub

            ib_names = list(ib_data.exclusive_areas) if ib_data is not None else []
            for ea_name in sorted(set(configured_subs) | set(ib_names)):
                sub = configured_subs.get(ea_name)
                if sub is not None:
                    ea_ref_v = sub.reference_values.get("RteBswExclusiveAreaRef")
                    ea_ref = (ea_ref_v.value_ref if ea_ref_v and ea_ref_v.value_ref else None) or ib_ea_paths.get(ea_name)
                    mech_p = sub.parameter_values.get("RteExclusiveAreaImplMechanism")
                    mech = (
                        str(mech_p.value).strip()
                        if mech_p and mech_p.value is not None
                        else "ALL_INTERRUPT_BLOCKING"
                    )
                    gen_fn_p = sub.parameter_values.get("RteExclusiveAreaGenerateFunction")
                    gen_fn = _as_bool(gen_fn_p.value if gen_fn_p else None, False)
                    res_v = sub.reference_values.get("RteBswExclusiveAreaOsResourceRef")
                    spin_v = sub.reference_values.get("RteBswExclusiveAreaOsSpinlockRef")
                    os_res = _ar_leaf(res_v.value_ref if res_v else None)
                    os_spin = _ar_leaf(spin_v.value_ref if spin_v else None)
                    err: Optional[str] = None
                    if mech not in EA_MECHANISMS:
                        err = f"未知机制 '{mech}'"
                    elif mech == "OS_RESOURCE" and not os_res:
                        err = "机制为 OS_RESOURCE 但缺少 RteBswExclusiveAreaOsResourceRef"
                    elif mech == "OS_SPINLOCK" and not os_spin:
                        err = "机制为 OS_SPINLOCK 但缺少 RteBswExclusiveAreaOsSpinlockRef"
                    rows.append(
                        ExclusiveAreaRow(
                            module_name=target_mod,
                            api_name=api_name,
                            instance_name=container.short_name,
                            ea_name=ea_name,
                            ea_ref=ea_ref,
                            configured=True,
                            mechanism=mech,
                            os_resource=os_res,
                            os_spinlock=os_spin,
                            generate_function=gen_fn,
                            validation_error=err,
                        )
                    )
                else:
                    rows.append(
                        ExclusiveAreaRow(
                            module_name=target_mod,
                            api_name=api_name,
                            instance_name=container.short_name,
                            ea_name=ea_name,
                            ea_ref=ib_ea_paths.get(ea_name),
                            configured=False,
                            mechanism="ALL_INTERRUPT_BLOCKING",
                            os_resource=None,
                            os_spinlock=None,
                            generate_function=False,
                            validation_error=None,
                        )
                    )

        rows.sort(key=lambda r: (r.api_name, r.ea_name))
        return rows

    def update_exclusive_area(
        self,
        instance_name: str,
        ea_name: str,
        *,
        mechanism: str,
        os_resource: Optional[str] = None,
        os_spinlock: Optional[str] = None,
        generate_function: bool = False,
        ea_ref: Optional[str] = None,
    ) -> EcucContainerValue:
        """Create or update an ``RteBswExclusiveAreaImpl`` sub-container."""
        inst = self._find_bsw_instance(instance_name)
        if inst is None:
            raise ValueError(f"未找到 BSW 实例 '{instance_name}'")

        target_sub: Optional[EcucContainerValue] = None
        for sub in getattr(inst, "sub_containers", []) or []:
            if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswExclusiveAreaImpl":
                continue
            ref_v = sub.reference_values.get("RteBswExclusiveAreaRef")
            cand_name = _ar_leaf(ref_v.value_ref if ref_v else None) or sub.short_name
            if cand_name == ea_name or sub.short_name == ea_name:
                target_sub = sub
                break

        resolved_ea_ref = ea_ref
        if not resolved_ea_ref:
            target_mod = self._target_mod_of_instance(inst)
            _, _, ib_data, _ = self._resolve_module_impl_and_ib(target_mod, container=inst)
            if ib_data is not None:
                for p, sn in ib_data.exclusive_area_paths.items():
                    if sn == ea_name:
                        resolved_ea_ref = p
                        break

        if target_sub is None:
            return self._create_exclusive_area_sub(
                inst,
                ea_name,
                ea_ref=resolved_ea_ref,
                mechanism=mechanism,
                os_resource=os_resource,
                os_spinlock=os_spinlock,
                generate_function=generate_function,
            )

        if resolved_ea_ref and "RteBswExclusiveAreaRef" not in target_sub.reference_values:
            self._set_ref(
                target_sub,
                "RteBswExclusiveAreaRef",
                resolved_ea_ref,
                dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                value_ref_dest="EXCLUSIVE-AREA",
            )
        self._apply_ea_fields(
            target_sub,
            mechanism=mechanism,
            os_resource=os_resource,
            os_spinlock=os_spinlock,
            generate_function=generate_function,
        )
        return target_sub

    def _sync_missing_exclusive_areas_detailed(self) -> Tuple[int, List[str]]:
        created = 0
        locked: List[str] = []
        for row in self.list_exclusive_area_rows():
            if row.configured:
                continue
            try:
                self.update_exclusive_area(
                    row.instance_name,
                    row.ea_name,
                    mechanism="ALL_INTERRUPT_BLOCKING",
                    generate_function=False,
                    ea_ref=row.ea_ref,
                )
                created += 1
            except PreLockedError as exc:
                locked.append(str(exc))
        return created, locked

    def sync_missing_exclusive_areas(self) -> int:
        """Create default ``RteBswExclusiveAreaImpl`` entries for IB-only ExclusiveAreas."""
        created, _ = self._sync_missing_exclusive_areas_detailed()
        return created

    def batch_set_mechanism(
        self,
        targets: List[Tuple[str, str]],
        mechanism: str,
        *,
        os_resource: Optional[str] = None,
        os_spinlock: Optional[str] = None,
        generate_function: Optional[bool] = None,
    ) -> int:
        """Apply a protection mechanism to multiple ``(instance_name, ea_name)`` targets."""
        existing_map = {
            (r.instance_name, r.ea_name): r for r in self.list_exclusive_area_rows()
        }
        updated = 0
        for instance_name, ea_name in targets:
            prev = existing_map.get((instance_name, ea_name))
            gen_fn = prev.generate_function if (generate_function is None and prev is not None) else bool(generate_function)
            try:
                self.update_exclusive_area(
                    instance_name,
                    ea_name,
                    mechanism=mechanism,
                    os_resource=os_resource if mechanism == "OS_RESOURCE" else None,
                    os_spinlock=os_spinlock if mechanism == "OS_SPINLOCK" else None,
                    generate_function=gen_fn,
                    ea_ref=prev.ea_ref if prev is not None else None,
                )
                updated += 1
            except PreLockedError:
                continue
        return updated

    # ------------------------------------------------------------------
    # Tab 3: OS Task Event Mapping & Execution Order
    # ------------------------------------------------------------------

    def list_os_tasks(self) -> List[OsTaskInfo]:
        """List OS tasks from ``Os`` module plus any referenced-only tasks."""
        tasks: Dict[str, OsTaskInfo] = {}
        os_mgr = self._managers().get("Os")
        os_cfg = getattr(os_mgr, "configuration", None) if os_mgr is not None else None
        if os_cfg is not None:
            def _walk(c: EcucContainerValue) -> None:
                if _ar_leaf(getattr(c, "definition_ref", None)) == "OsTask":
                    prio_p = c.parameter_values.get("OsTaskPriority")
                    type_p = c.parameter_values.get("OsTaskType")
                    stack_p = c.parameter_values.get("OsTaskStackSize")
                    prio = _parse_int(prio_p.value, -1) if prio_p and prio_p.value is not None else None
                    stack = _parse_int(stack_p.value, -1) if stack_p and stack_p.value is not None else None
                    tasks[c.short_name] = OsTaskInfo(
                        name=c.short_name,
                        priority=None if prio == -1 else prio,
                        task_type=str(type_p.value).strip() if type_p and type_p.value is not None else None,
                        stack_size=None if stack == -1 else stack,
                        missing_in_os=False,
                    )
                for sub in getattr(c, "sub_containers", []) or []:
                    _walk(sub)

            for top in getattr(os_cfg, "containers", []) or []:
                _walk(top)

        mapped_by_task, _ = self.list_task_mappings(include_swc=True)
        for task_name in mapped_by_task:
            if task_name and task_name not in tasks:
                tasks[task_name] = OsTaskInfo(name=task_name, missing_in_os=True)

        return [tasks[k] for k in sorted(tasks)]

    def list_task_mappings(
        self,
        *,
        include_swc: bool = True,
        include_unmapped_swc: bool = False,
    ) -> Tuple[Dict[str, List[TaskEventMappingRow]], List[TaskEventMappingRow]]:
        """Return ``(mapped_by_task, unmapped_events)`` across ``Rte``, IB, and SWC models."""
        if not self.has_rte_module():
            return {}, []

        managers = self._managers()
        ib_index = self._ib_index()
        mapped_by_task: Dict[str, List[TaskEventMappingRow]] = {}
        unmapped_events: List[TaskEventMappingRow] = []

        for container in self._bsw_instance_containers():
            target_mod = self._target_mod_of_instance(container)
            if not target_mod:
                continue
            is_loaded = target_mod in managers and getattr(managers[target_mod], "configuration", None) is not None
            api_name, _, ib_data, _ = self._resolve_module_impl_and_ib(
                target_mod, container=container, ib_index=ib_index
            )
            ib_events_by_name: Dict[str, BswIbEventData] = (
                {ev.short_name: ev for ev in ib_data.events} if ib_data is not None else {}
            )

            seen_event_refs: Set[str] = set()
            seen_mapping_names: Set[str] = set()

            for sub in getattr(container, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswEventToTaskMapping":
                    continue
                ev_ref_v = sub.reference_values.get("RteBswEventRef")
                ev_ref = ev_ref_v.value_ref.strip().rstrip("/") if ev_ref_v and ev_ref_v.value_ref else None
                ev_name = _ar_leaf(ev_ref) or sub.short_name
                if ev_ref:
                    seen_event_refs.add(ev_ref)
                seen_mapping_names.add(sub.short_name)
                seen_mapping_names.add(ev_name)

                ib_ev = (
                    ib_index.events_by_path.get(ev_ref) if ev_ref else None
                ) or ib_events_by_name.get(ev_name)

                task_ref_v = sub.reference_values.get("RteBswMappedToTaskRef")
                task_name = _ar_leaf(task_ref_v.value_ref) if task_ref_v and task_ref_v.value_ref else None
                pos_p = sub.parameter_values.get("RteBswPositionInTask")
                pos: Optional[int] = None
                if pos_p and pos_p.value is not None:
                    try:
                        pos = int(pos_p.value)
                    except (ValueError, TypeError):
                        pos = None
                imm_p = sub.parameter_values.get("RteBswImmediateRestart")
                imm = _as_bool(imm_p.value if imm_p else None, False)
                used_ev_v = sub.reference_values.get("RteBswUsedOsEventRef")
                used_al_v = sub.reference_values.get("RteBswUsedOsAlarmRef")
                used_ep_v = sub.reference_values.get("RteBswUsedOsSchTblExpiryPointRef")

                row = TaskEventMappingRow(
                    instance_name=container.short_name,
                    module_name=target_mod,
                    api_name=api_name,
                    mapping_name=sub.short_name,
                    event_name=ev_name,
                    event_ref=ev_ref,
                    event_kind=ib_ev.event_kind if ib_ev else (ev_ref_v.value_ref_dest or "BSW-TIMING-EVENT" if ev_ref_v else "BSW-TIMING-EVENT"),
                    entity_name=ib_ev.entity_name if ib_ev else None,
                    period_sec=ib_ev.period_sec if ib_ev else None,
                    task_name=task_name,
                    position=pos,
                    immediate_restart=imm,
                    is_swc=False,
                    has_ecuc_container=True,
                    used_os_event=_ar_leaf(used_ev_v.value_ref) if used_ev_v and used_ev_v.value_ref else None,
                    used_os_alarm=_ar_leaf(used_al_v.value_ref) if used_al_v and used_al_v.value_ref else None,
                    used_os_schtbl_ep=_ar_leaf(used_ep_v.value_ref) if used_ep_v and used_ep_v.value_ref else None,
                )
                if task_name:
                    mapped_by_task.setdefault(task_name, []).append(row)
                else:
                    unmapped_events.append(row)

            if is_loaded and ib_data is not None:
                for ib_ev in ib_data.events:
                    if ib_ev.ar_path in seen_event_refs or ib_ev.short_name in seen_mapping_names:
                        continue
                    unmapped_events.append(
                        TaskEventMappingRow(
                            instance_name=container.short_name,
                            module_name=target_mod,
                            api_name=api_name,
                            mapping_name=ib_ev.short_name,
                            event_name=ib_ev.short_name,
                            event_ref=ib_ev.ar_path,
                            event_kind=ib_ev.event_kind,
                            entity_name=ib_ev.entity_name,
                            period_sec=ib_ev.period_sec,
                            task_name=None,
                            position=None,
                            immediate_restart=False,
                            is_swc=False,
                            has_ecuc_container=False,
                        )
                    )

        if include_swc:
            swc_index = self._swc_index()
            for swc_inst in self._swc_instance_containers():
                inst_ref_v = swc_inst.reference_values.get("RteSoftwareComponentInstanceRef")
                inst_ref = inst_ref_v.value_ref.strip().rstrip("/") if inst_ref_v and inst_ref_v.value_ref else ""
                proto_name = _ar_leaf(inst_ref) or swc_inst.short_name
                swc_type = swc_index.resolve_swc_type_for_instance(inst_ref, proto_name)
                seen_swc_ev_refs: Set[str] = set()
                seen_swc_map_names: Set[str] = set()
                for sub in getattr(swc_inst, "sub_containers", []) or []:
                    if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteEventToTaskMapping":
                        continue
                    ev_ref_v = sub.reference_values.get("RteEventRef")
                    ev_ref = ev_ref_v.value_ref.strip().rstrip("/") if ev_ref_v and ev_ref_v.value_ref else None
                    ev_name = _ar_leaf(ev_ref) or sub.short_name
                    if ev_ref:
                        seen_swc_ev_refs.add(ev_ref)
                    seen_swc_map_names.add(sub.short_name)
                    seen_swc_map_names.add(ev_name)
                    swc_ev = swc_index.event_by_path.get(ev_ref) if ev_ref else None

                    task_ref_v = sub.reference_values.get("RteMappedToTaskRef")
                    task_name = _ar_leaf(task_ref_v.value_ref) if task_ref_v and task_ref_v.value_ref else None
                    pos_p = sub.parameter_values.get("RtePositionInTask")
                    pos = None
                    if pos_p and pos_p.value is not None:
                        try:
                            pos = int(pos_p.value)
                        except (ValueError, TypeError):
                            pos = None
                    imm_p = sub.parameter_values.get("RteImmediateRestart")
                    imm = _as_bool(imm_p.value if imm_p else None, False)
                    row = TaskEventMappingRow(
                        instance_name=swc_inst.short_name,
                        module_name=proto_name,
                        api_name=swc_type.short_name if swc_type else proto_name,
                        mapping_name=sub.short_name,
                        event_name=ev_name,
                        event_ref=ev_ref,
                        event_kind=(
                            swc_ev.event_kind
                            if swc_ev is not None
                            else (ev_ref_v.value_ref_dest if ev_ref_v and ev_ref_v.value_ref_dest else "SWC-EVENT")
                        ),
                        entity_name=swc_ev.runnable_symbol if swc_ev is not None else None,
                        period_sec=swc_ev.period_sec if swc_ev is not None else None,
                        task_name=task_name,
                        position=pos,
                        immediate_restart=imm,
                        is_swc=True,
                        has_ecuc_container=True,
                    )
                    if task_name:
                        mapped_by_task.setdefault(task_name, []).append(row)
                    elif include_unmapped_swc:
                        unmapped_events.append(row)

                if include_unmapped_swc and swc_type is not None:
                    for swc_ev in swc_type.events:
                        if swc_ev.event_kind == "OPERATION-INVOKED-EVENT":
                            continue
                        if swc_ev.ar_path in seen_swc_ev_refs or swc_ev.short_name in seen_swc_map_names:
                            continue
                        unmapped_events.append(
                            TaskEventMappingRow(
                                instance_name=swc_inst.short_name,
                                module_name=proto_name,
                                api_name=swc_type.short_name,
                                mapping_name=swc_ev.short_name,
                                event_name=swc_ev.short_name,
                                event_ref=swc_ev.ar_path,
                                event_kind=swc_ev.event_kind,
                                entity_name=swc_ev.runnable_symbol,
                                period_sec=swc_ev.period_sec,
                                task_name=None,
                                position=None,
                                immediate_restart=False,
                                is_swc=True,
                                has_ecuc_container=False,
                            )
                        )

        for task_name, task_rows in mapped_by_task.items():
            task_rows.sort(
                key=lambda r: (
                    r.position is None,
                    r.position if r.position is not None else 0,
                    r.is_swc,
                    r.module_name,
                    r.event_name,
                )
            )
        unmapped_events.sort(key=lambda r: (r.module_name, r.event_name))
        return mapped_by_task, unmapped_events

    def _find_mapping_sub(
        self,
        inst: EcucContainerValue,
        mapping_or_event_name: str,
    ) -> Optional[EcucContainerValue]:
        for sub in getattr(inst, "sub_containers", []) or []:
            if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswEventToTaskMapping":
                continue
            ev_ref_v = sub.reference_values.get("RteBswEventRef")
            ev_leaf = _ar_leaf(ev_ref_v.value_ref if ev_ref_v else None)
            if sub.short_name == mapping_or_event_name or ev_leaf == mapping_or_event_name:
                return sub
        return None

    def map_event_to_task(
        self,
        instance_name: str,
        event_name: str,
        task_name: str,
        *,
        event_ref: Optional[str] = None,
        event_kind: Optional[str] = None,
        position: Optional[int] = None,
    ) -> EcucContainerValue:
        """Assign a BSW event to ``task_name`` at ``position`` (appending after max if None)."""
        inst = self._find_bsw_instance(instance_name)
        if inst is None:
            raise ValueError(f"未找到 BSW 实例 '{instance_name}'")
        if not task_name:
            raise ValueError("必须指定目标 OsTask")

        if position is None:
            mapped_by_task, _ = self.list_task_mappings(include_swc=True)
            existing_pos = [
                r.position
                for r in mapped_by_task.get(task_name, [])
                if r.position is not None
            ]
            position = (max(existing_pos) + 1) if existing_pos else 0

        sub = self._find_mapping_sub(inst, event_name)
        created_new = sub is None
        if sub is None:
            self._check_editable(inst, None)
            sub = EcucContainerValue(
                short_name=event_name,
                definition_ref=f"{inst.definition_ref.rstrip('/')}/RteBswEventToTaskMapping",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            inst.add_sub_container(sub)

        try:
            if created_new:
                self._set_param(sub, "RteBswImmediateRestart", False, "ECUC-BOOLEAN-PARAM-DEF")
                if event_ref:
                    self._set_ref(
                        sub,
                        "RteBswEventRef",
                        event_ref,
                        dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                        value_ref_dest=event_kind or "BSW-TIMING-EVENT",
                    )
            elif event_ref and "RteBswEventRef" not in sub.reference_values:
                self._set_ref(
                    sub,
                    "RteBswEventRef",
                    event_ref,
                    dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                    value_ref_dest=event_kind or "BSW-TIMING-EVENT",
                )

            self._set_ref(
                sub,
                "RteBswMappedToTaskRef",
                self._module_ref_prefix("Os", task_name),
                dest_type="ECUC-REFERENCE-DEF",
                value_ref_dest="ECUC-CONTAINER-VALUE",
            )
            self._set_param(sub, "RteBswPositionInTask", int(position), "ECUC-INTEGER-PARAM-DEF")
        except PreLockedError:
            if created_new:
                inst.remove_sub_container(sub)
                rte_cfg = self._rte_cfg()
                if rte_cfg is not None:
                    rte_cfg._unregister_instance(sub)
            raise
        return sub

    def unmap_event(self, instance_name: str, mapping_name: str) -> bool:
        """Clear task mapping reference and position while retaining the mapping container."""
        inst = self._find_bsw_instance(instance_name)
        if inst is None:
            return False
        sub = self._find_mapping_sub(inst, mapping_name)
        if sub is None:
            return False
        if "RteBswMappedToTaskRef" in sub.reference_values:
            self._check_editable(sub, "RteBswMappedToTaskRef")
        if "RteBswPositionInTask" in sub.parameter_values:
            self._check_editable(sub, "RteBswPositionInTask")
        changed = self._remove_ref(sub, "RteBswMappedToTaskRef")
        if sub.remove_parameter_value("RteBswPositionInTask"):
            changed = True
            self._mark_rte_modified()
        return changed

    def set_event_position(self, instance_name: str, mapping_name: str, position: int) -> bool:
        """Update ``RteBswPositionInTask`` on a BSW event mapping."""
        inst = self._find_bsw_instance(instance_name)
        if inst is None:
            return False
        sub = self._find_mapping_sub(inst, mapping_name)
        if sub is None:
            return False
        self._set_param(sub, "RteBswPositionInTask", int(position), "ECUC-INTEGER-PARAM-DEF")
        return True

    def _find_swc_instance(self, instance_or_proto: str) -> Optional[EcucContainerValue]:
        for inst in self._swc_instance_containers():
            if inst.short_name == instance_or_proto:
                return inst
            ref_v = inst.reference_values.get("RteSoftwareComponentInstanceRef")
            if ref_v and _ar_leaf(ref_v.value_ref) == instance_or_proto:
                return inst
        return None

    @staticmethod
    def _find_swc_mapping_sub(inst: EcucContainerValue, mapping_or_event: str) -> Optional[EcucContainerValue]:
        for sub in getattr(inst, "sub_containers", []) or []:
            if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteEventToTaskMapping":
                continue
            ev_ref_v = sub.reference_values.get("RteEventRef")
            ev_leaf = _ar_leaf(ev_ref_v.value_ref if ev_ref_v else None)
            if sub.short_name == mapping_or_event or ev_leaf == mapping_or_event:
                return sub
        return None

    def map_swc_event_to_task(
        self,
        instance_name: str,
        event_name: str,
        task_name: str,
        *,
        event_ref: Optional[str] = None,
        event_kind: Optional[str] = None,
        position: Optional[int] = None,
    ) -> EcucContainerValue:
        """Assign an SWC runnable event to ``task_name`` inside ``RteSwComponentInstance``."""
        inst = self._find_swc_instance(instance_name)
        if inst is None:
            raise ValueError(f"未找到 SWC 实例 '{instance_name}'")
        if not task_name:
            raise ValueError("必须指定目标 OsTask")

        if position is None:
            mapped_by_task, _ = self.list_task_mappings(include_swc=True)
            existing_pos = [
                r.position
                for r in mapped_by_task.get(task_name, [])
                if r.position is not None
            ]
            position = (max(existing_pos) + 1) if existing_pos else 0

        sub = self._find_swc_mapping_sub(inst, event_name)
        created_new = sub is None
        if sub is None:
            self._check_editable(inst, None)
            sub = EcucContainerValue(
                short_name=event_name,
                definition_ref=f"{inst.definition_ref.rstrip('/')}/RteEventToTaskMapping",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            inst.add_sub_container(sub)

        try:
            if created_new:
                self._set_param(sub, "RteImmediateRestart", False, "ECUC-BOOLEAN-PARAM-DEF")
                if event_ref:
                    self._set_ref(
                        sub,
                        "RteEventRef",
                        event_ref,
                        dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                        value_ref_dest=event_kind or "TIMING-EVENT",
                    )
            elif event_ref and "RteEventRef" not in sub.reference_values:
                self._set_ref(
                    sub,
                    "RteEventRef",
                    event_ref,
                    dest_type="ECUC-FOREIGN-REFERENCE-DEF",
                    value_ref_dest=event_kind or "TIMING-EVENT",
                )
            self._set_ref(
                sub,
                "RteMappedToTaskRef",
                self._module_ref_prefix("Os", task_name),
                dest_type="ECUC-REFERENCE-DEF",
                value_ref_dest="ECUC-CONTAINER-VALUE",
            )
            self._set_param(sub, "RtePositionInTask", int(position), "ECUC-INTEGER-PARAM-DEF")
        except PreLockedError:
            if created_new:
                inst.remove_sub_container(sub)
                rte_cfg = self._rte_cfg()
                if rte_cfg is not None:
                    rte_cfg._unregister_instance(sub)
            raise
        return sub

    def unmap_swc_event(self, instance_name: str, mapping_name: str) -> bool:
        """Clear SWC task mapping reference and position on ``RteEventToTaskMapping``."""
        inst = self._find_swc_instance(instance_name)
        if inst is None:
            return False
        sub = self._find_swc_mapping_sub(inst, mapping_name)
        if sub is None:
            return False
        if "RteMappedToTaskRef" in sub.reference_values:
            self._check_editable(sub, "RteMappedToTaskRef")
        if "RtePositionInTask" in sub.parameter_values:
            self._check_editable(sub, "RtePositionInTask")
        changed = self._remove_ref(sub, "RteMappedToTaskRef")
        if sub.remove_parameter_value("RtePositionInTask"):
            changed = True
            self._mark_rte_modified()
        return changed

    def move_swc_event_in_task(
        self,
        task_name: str,
        instance_name: str,
        mapping_name: str,
        delta: int,
    ) -> bool:
        """Move an SWC event earlier (``delta < 0``) or later (``delta > 0``) among SWC siblings in ``task_name``."""
        if delta == 0:
            return False
        mapped_by_task, _ = self.list_task_mappings(include_swc=True)
        swc_rows = [r for r in mapped_by_task.get(task_name, []) if r.is_swc]
        idx = next(
            (i for i, r in enumerate(swc_rows) if r.instance_name == instance_name and r.mapping_name == mapping_name),
            -1,
        )
        if idx < 0:
            return False
        target_idx = idx + (-1 if delta < 0 else 1)
        if target_idx < 0 or target_idx >= len(swc_rows):
            return False

        row_a = swc_rows[idx]
        row_b = swc_rows[target_idx]
        inst_a = self._find_swc_instance(row_a.instance_name)
        inst_b = self._find_swc_instance(row_b.instance_name)
        if inst_a is None or inst_b is None:
            return False
        sub_a = self._find_swc_mapping_sub(inst_a, row_a.mapping_name)
        sub_b = self._find_swc_mapping_sub(inst_b, row_b.mapping_name)
        if sub_a is None or sub_b is None:
            return False

        positions: List[int] = [r.position if r.position is not None else i for i, r in enumerate(swc_rows)]
        for i in range(1, len(positions)):
            if positions[i] <= positions[i - 1]:
                positions[i] = positions[i - 1] + 1
        positions[idx], positions[target_idx] = positions[target_idx], positions[idx]
        self._set_param(sub_a, "RtePositionInTask", int(positions[idx]), "ECUC-INTEGER-PARAM-DEF")
        self._set_param(sub_b, "RtePositionInTask", int(positions[target_idx]), "ECUC-INTEGER-PARAM-DEF")
        return True

    # ------------------------------------------------------------------
    # Tab 4 & Tab 5: SWC Data Mapping (ComSignal) & Service Port Connections
    # ------------------------------------------------------------------

    def _resolve_swc_entries(self) -> List[Tuple[str, Optional[EcucContainerValue], Optional[SwcTypeData], List[str]]]:
        """Collect active SWC prototypes + their Ecuc container, SwcTypeData, and mapped tasks."""
        swc_index = self._swc_index()
        entries: List[Tuple[str, Optional[EcucContainerValue], Optional[SwcTypeData], List[str]]] = []
        seen_protos: Set[str] = set()
        for inst in self._swc_instance_containers():
            ref_v = inst.reference_values.get("RteSoftwareComponentInstanceRef")
            ref_p = ref_v.value_ref.strip().rstrip("/") if ref_v and ref_v.value_ref else ""
            proto_name = _ar_leaf(ref_p) or inst.short_name
            swc_type = swc_index.resolve_swc_type_for_instance(ref_p, proto_name)
            mapped_tasks: List[str] = []
            for sub in getattr(inst, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) == "RteEventToTaskMapping":
                    tv = sub.reference_values.get("RteMappedToTaskRef")
                    if tv and tv.value_ref:
                        tname = _ar_leaf(tv.value_ref)
                        if tname:
                            mapped_tasks.append(tname)
            entries.append((proto_name, inst, swc_type, mapped_tasks))
            seen_protos.add(proto_name)

        if not entries and swc_index.prototypes_by_name:
            for pname in sorted(swc_index.prototypes_by_name):
                if pname in seen_protos:
                    continue
                stype = swc_index.resolve_swc_type_for_instance(swc_index.prototypes_by_name[pname].ar_path, pname)
                entries.append((pname, None, stype, []))
        return entries

    def list_available_com_signals(self, direction: Optional[str] = None) -> List[Tuple[str, str, str]]:
        """Return sorted ``[(com_signal_name, direction, system_signal_leaf)]`` tuples."""
        swc_index = self._swc_index()
        by_name, _, _ = RteModelExtractor.collect_com_signal_catalog(self._managers().get("Com"), swc_index)
        items: List[Tuple[str, str, str]] = []
        for sig_name in sorted(by_name):
            info = by_name[sig_name]
            sdir = info["direction"]
            if direction and sdir and sdir != direction:
                continue
            sys_leaf = _ar_leaf(info["resolved_sys"]) or _ar_leaf(info["raw_sys_ref"])
            items.append((sig_name, sdir, sys_leaf))
        return items

    def list_data_mapping_rows(self) -> List[DataMappingRow]:
        """List all SWC Sender-Receiver ports joined against ComSignals & inter-SWC connectors."""
        swc_index = self._swc_index()
        entries = self._resolve_swc_entries()
        inst_to_type = {p: st.short_name for p, _c, st, _t in entries if st is not None}
        eff_maps = RteModelExtractor.resolve_effective_data_mappings(self.project, swc_index, inst_to_type)
        eff_conns = RteModelExtractor.resolve_effective_connectors(self.project, swc_index)
        inter_ports: Set[Tuple[str, str]] = set()
        for ac in eff_conns:
            if ac.provider_comp_name and ac.provider_port_name:
                inter_ports.add((ac.provider_comp_name, ac.provider_port_name))
            if ac.requester_comp_name and ac.requester_port_name:
                inter_ports.add((ac.requester_comp_name, ac.requester_port_name))

        com_by_name, com_by_sys_path, com_by_sys_leaf = RteModelExtractor.collect_com_signal_catalog(
            self._managers().get("Com"), swc_index
        )

        rows: List[DataMappingRow] = []
        for proto_name, _ecuc, swc_type, _tasks in entries:
            if swc_type is None:
                continue
            for port in sorted(swc_type.ports.values(), key=lambda p: p.short_name):
                iface = swc_index.interfaces_by_path.get(port.interface_ref.strip().rstrip("/")) if port.interface_ref else None
                if iface is None or iface.kind != "SR":
                    continue
                direction = "TX" if port.direction == "P" else "RX"
                for de_name, de in sorted(iface.data_elements.items()):
                    c_type = swc_index.resolve_c_type_name(de.type_ref, "uint8")
                    rec = eff_maps.get((proto_name, port.short_name)) or eff_maps.get((swc_type.short_name, port.short_name))
                    if rec is None:
                        status = "inter_swc" if (proto_name, port.short_name) in inter_ports else "unmapped"
                        rows.append(
                            DataMappingRow(
                                component_name=proto_name,
                                swc_type_name=swc_type.short_name,
                                port_name=port.short_name,
                                data_element_name=de_name,
                                direction=direction,
                                c_type=c_type,
                                status=status,
                                source="none",
                            )
                        )
                        continue

                    sys_ref = rec.get("system_signal_ref", "")
                    sys_name = rec.get("system_signal_name", "")
                    src = rec.get("source", "arxml")
                    explicit_com = rec.get("com_signal", "")
                    com_entry: Optional[Dict[str, str]] = None
                    status = "mapped"
                    com_sig_name = explicit_com
                    com_dir = ""

                    if explicit_com:
                        com_entry = com_by_name.get(explicit_com)
                        if com_entry is None:
                            status = "broken_com"
                        else:
                            com_dir = com_entry["direction"]
                            if com_dir and com_dir != direction:
                                status = "direction_mismatch"
                            sys_name = sys_name or _ar_leaf(com_entry["resolved_sys"])
                            sys_ref = sys_ref or com_entry["resolved_sys"]
                    else:
                        cands = com_by_sys_path.get(sys_ref) or com_by_sys_leaf.get(sys_name) or []
                        dir_matches = [c for c in cands if (not c["direction"] or c["direction"] == direction)]
                        if dir_matches:
                            com_entry = dir_matches[0]
                            com_sig_name = com_entry["name"]
                            com_dir = com_entry["direction"]
                        elif cands:
                            com_entry = cands[0]
                            com_sig_name = com_entry["name"]
                            com_dir = com_entry["direction"]
                            status = "direction_mismatch"
                        else:
                            status = "broken_com"

                    rows.append(
                        DataMappingRow(
                            component_name=proto_name,
                            swc_type_name=swc_type.short_name,
                            port_name=port.short_name,
                            data_element_name=de_name,
                            direction=direction,
                            c_type=c_type,
                            system_signal_name=sys_name,
                            system_signal_ref=sys_ref,
                            com_signal_name=com_sig_name,
                            com_signal_direction=com_dir,
                            status=status,
                            source=src,
                        )
                    )
        rows.sort(key=lambda r: (r.component_name, r.direction, r.port_name, r.data_element_name))
        return rows

    def set_data_mapping(
        self,
        component_name: str,
        port_name: str,
        com_signal: str,
        *,
        data_element: str = "",
        direction: str = "",
        system_signal_ref: str = "",
    ) -> None:
        """Persist a Data Mapping binding in ``project.rte_data_mappings``."""
        if not hasattr(self.project, "rte_data_mappings"):
            self.project.rte_data_mappings = []
        entries = self._resolve_swc_entries()
        inst_to_type = {p: st.short_name for p, _c, st, _t in entries if st is not None}
        aliases = {component_name}
        if component_name in inst_to_type:
            aliases.add(inst_to_type[component_name])

        self.project.rte_data_mappings = [
            x
            for x in self.project.rte_data_mappings
            if not (x.get("component") in aliases and x.get("port") == port_name)
        ]
        self.project.rte_data_mappings.append(
            {
                "component": component_name,
                "port": port_name,
                "data_element": data_element,
                "direction": direction,
                "com_signal": com_signal,
                "system_signal_ref": system_signal_ref,
                "action": "map",
            }
        )
        self._mark_rte_modified()

    def clear_data_mapping(self, component_name: str, port_name: str) -> bool:
        """Unbind an SWC port's Data Mapping (overriding ARXML mapping if inherited)."""
        if not hasattr(self.project, "rte_data_mappings"):
            self.project.rte_data_mappings = []
        swc_index = self._swc_index()
        entries = self._resolve_swc_entries()
        inst_to_type = {p: st.short_name for p, _c, st, _t in entries if st is not None}
        aliases = {component_name}
        if component_name in inst_to_type:
            aliases.add(inst_to_type[component_name])

        prev_len = len(self.project.rte_data_mappings)
        self.project.rte_data_mappings = [
            x
            for x in self.project.rte_data_mappings
            if not (x.get("component") in aliases and x.get("port") == port_name)
        ]
        has_arxml = any((a, port_name) in swc_index.sr_mapping_by_comp_port for a in aliases)
        if has_arxml:
            self.project.rte_data_mappings.append(
                {"component": component_name, "port": port_name, "action": "unmap"}
            )
            self._mark_rte_modified()
            return True
        if len(self.project.rte_data_mappings) != prev_len:
            self._mark_rte_modified()
            return True
        return False

    def auto_match_data_mappings(self) -> int:
        """Match unmapped or broken SR ports to ``ComSignal``s by signal name/direction."""
        rows = self.list_data_mapping_rows()
        avail = self.list_available_com_signals()
        if not avail:
            return 0

        def _norm_tok(text: str) -> str:
            t = re.sub(r"^(?:SigPP|SigRP|PpSignal|RpSignal|Pp|Rp|DeSignal|Sig_VarDataProto)_(?:Proto_)?", "", text or "")
            t = re.sub(r"_(?:Tx|Rx)$", "", t)
            t = re.sub(r"_o[^_]+(?:_[0-9a-fA-F]{6,12})?$", "", t)
            return re.sub(r"[^A-Za-z0-9]", "", t).lower()

        matched = 0
        for r in rows:
            if r.status not in ("unmapped", "broken_com"):
                continue
            cand_tokens = [
                _norm_tok(r.system_signal_name),
                _norm_tok(r.port_name),
                _norm_tok(r.data_element_name),
            ]
            cand_tokens = [t for t in cand_tokens if t]
            chosen: Optional[str] = None
            for sig_name, sig_dir, sys_leaf in avail:
                if sig_dir and sig_dir != r.direction:
                    continue
                sig_toks = {_norm_tok(sig_name), _norm_tok(sys_leaf)}
                if any(ct in sig_toks for ct in cand_tokens):
                    chosen = sig_name
                    break
            if chosen:
                self.set_data_mapping(
                    r.component_name,
                    r.port_name,
                    chosen,
                    data_element=r.data_element_name,
                    direction=r.direction,
                )
                matched += 1
        return matched

    def list_swc_instance_rows(self) -> List[SwcInstanceSummaryRow]:
        """List SWC / ServiceComponent instances, OsApplication core assignment, and event counts."""
        swc_index = self._swc_index()
        entries = self._resolve_swc_entries()
        os_apps: List[str] = []
        os_mgr = self._managers().get("Os")
        if os_mgr and getattr(os_mgr, "configuration", None):
            for c in getattr(os_mgr.configuration, "containers", []) or []:
                if _ar_leaf(getattr(c, "definition_ref", None)) == "OsApplication":
                    os_apps.append(c.short_name)
        _, task_to_app, app_to_core, _, _, default_app = RteModelExtractor._collect_os_partition_info(os_mgr, os_apps)

        rows: List[SwcInstanceSummaryRow] = []
        for proto_name, ecuc_inst, swc_type, mapped_tasks in entries:
            chosen_app = next((task_to_app[t] for t in mapped_tasks if t in task_to_app), None)
            if not chosen_app:
                guess_c = RteModelExtractor._core_num(proto_name, 0)
                chosen_app = next((a for a, cid in app_to_core.items() if cid == guess_c), default_app)
            cid = app_to_core.get(chosen_app, RteModelExtractor._core_num(chosen_app, 0))
            mapped_cnt = len(mapped_tasks)
            total_sched = 0
            if swc_type is not None:
                total_sched = sum(1 for e in swc_type.events if e.event_kind != "OPERATION-INVOKED-EVENT")
            rows.append(
                SwcInstanceSummaryRow(
                    instance_name=proto_name,
                    swc_type_name=swc_type.short_name if swc_type else proto_name,
                    is_service=bool(swc_type.is_service) if swc_type else False,
                    os_application=chosen_app,
                    core_id=cid,
                    port_count=len(swc_type.ports) if swc_type else 0,
                    runnable_count=len(swc_type.runnables) if swc_type else 0,
                    mapped_events=mapped_cnt,
                    unmapped_events=max(0, total_sched - mapped_cnt),
                )
            )
        rows.sort(key=lambda r: (r.is_service, r.core_id, r.instance_name))
        return rows

    def list_service_port_rows(self) -> List[ServicePortRow]:
        """List R-Ports across SWCs (Client-Server, Mode, and inter-SWC SR) with connected provider status."""
        swc_index = self._swc_index()
        entries = self._resolve_swc_entries()
        eff_conns = RteModelExtractor.resolve_effective_connectors(self.project, swc_index)
        eff_data_maps = RteModelExtractor.resolve_effective_data_mappings(
            self.project,
            swc_index,
            {p: st.short_name for p, _c, st, _t in entries if st is not None},
        )
        swc_by_inst: Dict[str, SwcTypeData] = {p: st for p, _c, st, _t in entries if st is not None}

        overlay_keys = {
            (str(x.get("requester_component", "")).strip(), str(x.get("requester_port", "")).strip())
            for x in (getattr(self.project, "rte_service_connectors", []) or [])
            if isinstance(x, dict) and x.get("action", "map") == "map"
        }

        conn_by_req = {
            (ac.requester_comp_name, ac.requester_port_name): ac
            for ac in eff_conns
            if ac.requester_comp_name and ac.requester_port_name
        }

        rows: List[ServicePortRow] = []
        for proto_name, _ecuc, swc_type, _tasks in entries:
            if swc_type is None:
                continue
            for port in sorted(swc_type.ports.values(), key=lambda p: p.short_name):
                if port.direction != "R":
                    continue
                iface = swc_index.interfaces_by_path.get(port.interface_ref.strip().rstrip("/")) if port.interface_ref else None
                if iface is None:
                    continue
                # Skip SR ports mapped cleanly to a ComSignal
                if iface.kind == "SR" and (
                    (proto_name, port.short_name) in eff_data_maps
                    or (swc_type.short_name, port.short_name) in eff_data_maps
                ):
                    continue

                ac = conn_by_req.get((proto_name, port.short_name))
                src = "overlay" if (proto_name, port.short_name) in overlay_keys else ("arxml" if ac else "none")
                prov_c = ac.provider_comp_name if ac else ""
                prov_p = ac.provider_port_name if ac else ""
                prov_swc = swc_by_inst.get(prov_c) or swc_index.swc_types_by_name.get(prov_c) if prov_c else None

                status = "unconnected"
                server_sym = ""
                if ac is not None:
                    if prov_swc is None or prov_p not in prov_swc.ports:
                        status = "broken"
                    else:
                        p_port = prov_swc.ports[prov_p]
                        if p_port.interface_kind and iface.kind and p_port.interface_kind != iface.kind:
                            status = "broken"
                        else:
                            status = "connected"
                            if iface.kind == "CS":
                                syms = [
                                    ev.runnable_symbol
                                    for ev in prov_swc.events
                                    if ev.event_kind == "OPERATION-INVOKED-EVENT" and _ar_leaf(ev.port_ref) == prov_p
                                ]
                                server_sym = ", ".join(sorted({s for s in syms if s})) or ", ".join(sorted(iface.operations.keys()))

                rows.append(
                    ServicePortRow(
                        requester_component=proto_name,
                        requester_swc_type=swc_type.short_name,
                        requester_port=port.short_name,
                        interface_name=iface.short_name,
                        interface_kind=iface.kind,
                        is_service=bool(iface.is_service or (prov_swc.is_service if prov_swc else False)),
                        provider_component=prov_c,
                        provider_port=prov_p,
                        server_symbol=server_sym,
                        status=status,
                        source=src,
                    )
                )
        rows.sort(key=lambda r: (not r.is_service, r.interface_kind, r.requester_component, r.requester_port))
        return rows

    def list_compatible_provider_ports(
        self, requester_component: str, requester_port: str
    ) -> List[Tuple[str, str, str]]:
        """Return compatible provider P-ports ``[(provider_comp, provider_port, interface_name)]``."""
        swc_index = self._swc_index()
        entries = self._resolve_swc_entries()
        swc_by_inst: Dict[str, SwcTypeData] = {p: st for p, _c, st, _t in entries if st is not None}
        req_swc = swc_by_inst.get(requester_component)
        if req_swc is None or requester_port not in req_swc.ports:
            return []
        req_port = req_swc.ports[requester_port]
        req_iface = swc_index.interfaces_by_path.get(req_port.interface_ref.strip().rstrip("/")) if req_port.interface_ref else None
        req_kind = req_iface.kind if req_iface else req_port.interface_kind
        req_iface_name = req_iface.short_name if req_iface else _ar_leaf(req_port.interface_ref)
        req_ops = set(req_iface.operations.keys()) if req_iface else set()

        cands: List[Tuple[int, str, str, str]] = []
        for proto_name, _ecuc, swc_type, _tasks in entries:
            if swc_type is None:
                continue
            for p_name, port in sorted(swc_type.ports.items()):
                if port.direction != "P":
                    continue
                if proto_name == requester_component and p_name == requester_port:
                    continue
                p_iface = swc_index.interfaces_by_path.get(port.interface_ref.strip().rstrip("/")) if port.interface_ref else None
                p_kind = p_iface.kind if p_iface else port.interface_kind
                if req_kind and p_kind and req_kind != p_kind:
                    continue
                p_iface_name = p_iface.short_name if p_iface else _ar_leaf(port.interface_ref)
                p_ops = set(p_iface.operations.keys()) if p_iface else set()
                # Score exact interface ref match > exact op set match > same kind
                score = 2
                if p_iface_name == req_iface_name:
                    score = 0
                elif req_ops and req_ops.issubset(p_ops):
                    score = 1
                cands.append((score, proto_name, p_name, p_iface_name))
        cands.sort(key=lambda x: (x[0], x[1], x[2]))
        return [(c, p, ifn) for _, c, p, ifn in cands]

    def connect_ports(
        self,
        requester_component: str,
        requester_port: str,
        provider_component: str,
        provider_port: str,
    ) -> None:
        """Persist an assembly/service port connection in ``project.rte_service_connectors``."""
        if not hasattr(self.project, "rte_service_connectors"):
            self.project.rte_service_connectors = []
        self.project.rte_service_connectors = [
            x
            for x in self.project.rte_service_connectors
            if not (x.get("requester_component") == requester_component and x.get("requester_port") == requester_port)
        ]
        self.project.rte_service_connectors.append(
            {
                "requester_component": requester_component,
                "requester_port": requester_port,
                "provider_component": provider_component,
                "provider_port": provider_port,
                "action": "map",
            }
        )
        self._mark_rte_modified()

    def disconnect_port(self, requester_component: str, requester_port: str) -> bool:
        """Disconnect an assembly/service R-Port via ``project.rte_service_connectors``."""
        if not hasattr(self.project, "rte_service_connectors"):
            self.project.rte_service_connectors = []
        swc_index = self._swc_index()
        prev_len = len(self.project.rte_service_connectors)
        self.project.rte_service_connectors = [
            x
            for x in self.project.rte_service_connectors
            if not (x.get("requester_component") == requester_component and x.get("requester_port") == requester_port)
        ]
        has_arxml = any(
            ac.requester_comp_name == requester_component and ac.requester_port_name == requester_port
            for ac in swc_index.assembly_connectors
        )
        if has_arxml:
            self.project.rte_service_connectors.append(
                {
                    "requester_component": requester_component,
                    "requester_port": requester_port,
                    "action": "unmap",
                }
            )
            self._mark_rte_modified()
            return True
        if len(self.project.rte_service_connectors) != prev_len:
            self._mark_rte_modified()
            return True
        return False

    def auto_connect_service_ports(self) -> int:
        """Connect unconnected R-ports when a clear compatible Service or single provider port exists."""
        rows = self.list_service_port_rows()
        connected = 0
        for r in rows:
            if r.status not in ("unconnected", "broken"):
                continue
            cands = self.list_compatible_provider_ports(r.requester_component, r.requester_port)
            if not cands:
                continue
            # Prefer exact interface/port name match or unique compatible provider
            chosen: Optional[Tuple[str, str]] = None
            exact_iface = [c for c in cands if c[2] == r.interface_name or c[1] == r.requester_port]
            if len(exact_iface) == 1:
                chosen = (exact_iface[0][0], exact_iface[0][1])
            elif r.requester_port.startswith("UR_"):
                srv_hits = [c for c in cands if c[0] == "ComM"]
                if len(srv_hits) == 1:
                    chosen = (srv_hits[0][0], srv_hits[0][1])
            elif len(cands) == 1:
                chosen = (cands[0][0], cands[0][1])
            if chosen is not None:
                self.connect_ports(r.requester_component, r.requester_port, chosen[0], chosen[1])
                connected += 1
        return connected

    def move_event_in_task(
        self,
        task_name: str,
        instance_name: str,
        mapping_name: str,
        delta: int,
    ) -> bool:
        """Move a BSW event up (``delta < 0``) or down (``delta > 0``) among BSW siblings in ``task_name``."""
        if delta == 0:
            return False
        mapped_by_task, _ = self.list_task_mappings(include_swc=False)
        bsw_rows = mapped_by_task.get(task_name, [])
        idx = next(
            (
                i
                for i, r in enumerate(bsw_rows)
                if r.instance_name == instance_name and r.mapping_name == mapping_name
            ),
            None,
        )
        if idx is None:
            return False
        target_idx = idx + (-1 if delta < 0 else 1)
        if target_idx < 0 or target_idx >= len(bsw_rows):
            return False

        positions: List[int] = []
        raw_positions = [r.position for r in bsw_rows]
        if any(p is None for p in raw_positions) or len(set(raw_positions)) < len(raw_positions):
            positions = list(range(len(bsw_rows)))
        else:
            positions = [int(p) for p in raw_positions if p is not None]

        positions[idx], positions[target_idx] = positions[target_idx], positions[idx]
        for row, new_pos in zip(bsw_rows, positions):
            self.set_event_position(row.instance_name, row.mapping_name, new_pos)
        return True

    def batch_map_events_to_task(
        self,
        events: List[TaskEventMappingRow],
        task_name: str,
    ) -> Tuple[int, List[str]]:
        """Map multiple unmapped BSW events sequentially to ``task_name``, skipping Pre-locked items."""
        mapped_count = 0
        skipped_locked: List[str] = []
        for ev in events:
            try:
                self.map_event_to_task(
                    ev.instance_name,
                    ev.event_name,
                    task_name,
                    event_ref=ev.event_ref,
                    event_kind=ev.event_kind,
                )
                mapped_count += 1
            except PreLockedError as exc:
                skipped_locked.append(str(exc))
        return mapped_count, skipped_locked

    @staticmethod
    def _period_task_patterns(period_sec: float) -> List[re.Pattern]:
        def _tokens(val: float) -> List[str]:
            rounded = round(val, 6)
            base = (
                f"{int(round(rounded))}"
                if abs(rounded - round(rounded)) < 1e-6
                else f"{rounded:g}"
            )
            toks = [base]
            if "." in base:
                toks.append(base.replace(".", "_"))
            return [re.escape(t) for t in toks]

        patterns: List[re.Pattern] = []
        ms_tokens = _tokens(period_sec * 1000.0)
        if period_sec < 1.0:
            patterns.append(
                re.compile(rf"(?<![0-9])(?:{'|'.join(ms_tokens)})\s*ms(?![a-z0-9])", re.IGNORECASE)
            )
        else:
            s_tokens = _tokens(period_sec)
            patterns.append(
                re.compile(rf"(?<![0-9])(?:{'|'.join(s_tokens)})\s*s(?![a-z0-9])", re.IGNORECASE)
            )
            patterns.append(
                re.compile(rf"(?<![0-9])(?:{'|'.join(ms_tokens)})\s*ms(?![a-z0-9])", re.IGNORECASE)
            )
        return patterns

    def recommend_task_for_events(
        self,
        events: List[TaskEventMappingRow],
        tasks: Optional[List[OsTaskInfo]] = None,
        mapped_by_task: Optional[Dict[str, List[TaskEventMappingRow]]] = None,
    ) -> Tuple[Optional[str], str]:
        """Recommend a target ``OsTask`` for ``events`` based on period consistency and naming."""
        if not events:
            return None, "请选择一个或多个未映射 BSW 事件，再点击映射到目标 OsTask（支持 Ctrl/Shift 多选）"

        if tasks is None:
            tasks = self.list_os_tasks()
        if mapped_by_task is None:
            mapped_by_task, _ = self.list_task_mappings(include_swc=False)

        valid_tasks = [t for t in tasks if not t.missing_in_os] or list(tasks)

        distinct_periods: List[float] = []
        seen_periods: Set[float] = set()
        for ev in events:
            if ev.period_sec is None:
                continue
            rounded = round(float(ev.period_sec), 9)
            if rounded not in seen_periods:
                seen_periods.add(rounded)
                distinct_periods.append(rounded)
        distinct_periods.sort()

        if len(distinct_periods) > 1:
            labels = [format_period_label(p) for p in distinct_periods]
            return (
                None,
                f"提示：所选事件包含多种周期（{' / '.join(labels)}），建议按相同周期分批映射到对应 OsTask",
            )

        if len(distinct_periods) == 1:
            p = distinct_periods[0]
            p_label = format_period_label(p)
            patterns = self._period_task_patterns(p)
            name_matches = [
                t for t in valid_tasks if any(pat.search(t.name) for pat in patterns)
            ]
            if name_matches:
                best = sorted(
                    name_matches,
                    key=lambda t: (0 if ("bsw" in t.name.lower() or "schm" in t.name.lower()) else 1, t.name),
                )[0]
                return best.name, f"智能推荐：所选事件周期为 {p_label}，匹配任务名 {best.name}"

            mapped_candidates: List[Tuple[int, int, str]] = []
            for t in valid_tasks:
                bsw_rows = [r for r in mapped_by_task.get(t.name, []) if not r.is_swc]
                same_cnt = sum(
                    1
                    for r in bsw_rows
                    if r.period_sec is not None and abs(round(float(r.period_sec), 9) - p) <= 1e-9
                )
                if same_cnt <= 0:
                    continue
                conflict_cnt = sum(
                    1
                    for r in bsw_rows
                    if r.period_sec is not None and abs(round(float(r.period_sec), 9) - p) > 1e-9
                )
                mapped_candidates.append((0 if conflict_cnt == 0 else 1, -same_cnt, t.name))
            if mapped_candidates:
                best_task = sorted(mapped_candidates)[0][2]
                return best_task, f"智能推荐：与同周期 ({p_label}) 已映射 BSW 事件同属 {best_task}"

            return None, f"所选事件周期：{p_label}（未匹配到同名周期 Task，请手动选择目标 OsTask）"

        bsw_tasks = [t for t in valid_tasks if "bsw" in t.name.lower()]
        if bsw_tasks:
            best = sorted(
                bsw_tasks,
                key=lambda t: (
                    0 if any(k in t.name.lower() for k in ("init", "event", "async")) else 1,
                    t.name,
                ),
            )[0]
            return best.name, f"智能推荐：所选事件无固定周期，匹配 BSW 任务 {best.name}"
        return None, "所选事件无固定周期，请按触发类型手动选择目标 OsTask"

    # ------------------------------------------------------------------
    # Stage-3 OS Activation & Cross-Subsystem Diagnostics
    # ------------------------------------------------------------------

    def has_os_module(self) -> bool:
        os_mgr = self._managers().get("Os")
        return os_mgr is not None and getattr(os_mgr, "configuration", None) is not None

    def list_os_events(self) -> List[str]:
        return self._list_os_names("OsEvent")

    def list_os_alarms(self) -> List[str]:
        return self._list_os_names("OsAlarm")

    def list_os_schedule_tables(self) -> List[str]:
        return self._list_os_names("OsScheduleTable")

    def list_os_activations(self) -> List[OsActivationInfo]:
        """Collect ``RteOsInteraction/RteUsedOsActivation`` entries from ``Rte`` configuration."""
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            return []

        activations: List[OsActivationInfo] = []
        for top in getattr(rte_cfg, "containers", []) or []:
            if _ar_leaf(getattr(top, "definition_ref", None)) != "RteOsInteraction":
                continue
            for sub in getattr(top, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteUsedOsActivation":
                    continue
                task_v = sub.reference_values.get("RteActivationOsTaskRef")
                alarm_v = sub.reference_values.get("RteActivationOsAlarmRef")
                schtbl_v = (
                    sub.reference_values.get("RteActivationOsSchTblRef")
                    or sub.reference_values.get("RteActivationOsScheduleTableRef")
                )

                def _float_p(name: str) -> Optional[float]:
                    pv = sub.parameter_values.get(name)
                    if pv is None or pv.value is None or str(pv.value).strip() == "":
                        return None
                    try:
                        return float(pv.value)
                    except (ValueError, TypeError):
                        return None

                c_path = (
                    sub.get_path()
                    if hasattr(sub, "get_path") and callable(sub.get_path)
                    else f"/Rte/{top.short_name}/{sub.short_name}"
                )
                activations.append(
                    OsActivationInfo(
                        name=sub.short_name,
                        container_path=c_path,
                        task_name=_ar_leaf(task_v.value_ref) if task_v and task_v.value_ref else None,
                        alarm_name=_ar_leaf(alarm_v.value_ref) if alarm_v and alarm_v.value_ref else None,
                        schedule_table_name=(
                            _ar_leaf(schtbl_v.value_ref) if schtbl_v and schtbl_v.value_ref else None
                        ),
                        expected_tick_duration=_float_p("RteExpectedTickDuration"),
                        expected_offset=_float_p("RteExpectedActivationOffset"),
                    )
                )
        return activations

    def collect_diagnostics(self) -> List[RteSchmDiagnostic]:
        """Collect all RTE/SchM readiness and Stage-3 OS-interaction diagnostics."""
        if not self.has_rte_module():
            return []

        diags: List[RteSchmDiagnostic] = []

        # Tab 1: BSW instances
        for row in self.list_bsw_instance_rows():
            if row.status == "unloaded":
                diags.append(
                    RteSchmDiagnostic(
                        severity="warning",
                        code="UNLOADED_INSTANCE",
                        message=f"Rte 中登记了未加载模块 '{row.module_name}'，生成时将跳过",
                        container_path=f"/Rte/{row.instance_name}",
                        parameter_name="RteBswModuleConfigurationRef",
                        workbench_tab=0,
                        suggested_fix="在 RTE / SchM 工作台页签 1 中移除未加载实例或在工程中加载对应模块",
                    )
                )

        # Tab 2: ExclusiveAreas
        for row in self.list_exclusive_area_rows():
            if row.validation_error:
                if row.mechanism == "OS_RESOURCE":
                    p_name = "RteBswExclusiveAreaOsResourceRef"
                elif row.mechanism == "OS_SPINLOCK":
                    p_name = "RteBswExclusiveAreaOsSpinlockRef"
                else:
                    p_name = "RteExclusiveAreaImplMechanism"
                diags.append(
                    RteSchmDiagnostic(
                        severity="error",
                        code="EA_INVALID_CONFIG",
                        message=f"{row.module_name}.{row.ea_name}：{row.validation_error}",
                        container_path=f"/Rte/{row.instance_name}/{row.ea_name}",
                        parameter_name=p_name,
                        workbench_tab=1,
                        suggested_fix="在 RTE / SchM 工作台页签 2 中修正临界区保护机制或补选目标 OsResource / OsSpinlock",
                    )
                )
            elif not row.configured:
                diags.append(
                    RteSchmDiagnostic(
                        severity="warning",
                        code="EA_UNCONFIGURED",
                        message=f"{row.module_name}.{row.ea_name} 仅在 IB 中声明，尚未同步到 Rte ECUC",
                        container_path=f"/Rte/{row.instance_name}",
                        parameter_name=None,
                        workbench_tab=1,
                        suggested_fix="在 RTE / SchM 工作台页签 2 点击「同步缺失临界区」",
                    )
                )

        # Tab 3: Task mappings & Stage-3 RteOsInteraction checks
        tasks = self.list_os_tasks()
        task_map = {t.name: t for t in tasks}
        mapped_by_task, unmapped = self.list_task_mappings(include_swc=False)
        os_loaded = self.has_os_module()

        for ev in unmapped:
            c_path = (
                f"/Rte/{ev.instance_name}/{ev.mapping_name}"
                if ev.has_ecuc_container
                else f"/Rte/{ev.instance_name}"
            )
            diags.append(
                RteSchmDiagnostic(
                    severity="warning",
                    code="UNMAPPED_EVENT",
                    message=f"BSW 调度事件 {ev.module_name}.{ev.event_name} 尚未映射到 OsTask",
                    container_path=c_path,
                    parameter_name="RteBswMappedToTaskRef" if ev.has_ecuc_container else None,
                    workbench_tab=2,
                    suggested_fix="在 RTE / SchM 工作台页签 3 将该事件分配到目标 OsTask",
                )
            )

        os_events = set(self.list_os_events()) if os_loaded else set()
        os_alarms = set(self.list_os_alarms()) if os_loaded else set()
        os_schtbls = set(self.list_os_schedule_tables()) if os_loaded else set()

        for task_name, rows in mapped_by_task.items():
            bsw_rows = [r for r in rows if not r.is_swc]
            if not bsw_rows:
                continue
            task_info = task_map.get(task_name)

            if os_loaded and task_info is not None and task_info.missing_in_os:
                for r in bsw_rows:
                    diags.append(
                        RteSchmDiagnostic(
                            severity="warning",
                            code="MISSING_OS_TASK",
                            message=f"BSW 事件 {r.module_name}.{r.event_name} 引用的 OsTask '{task_name}' 在 Os 模块中未定义",
                            container_path=f"/Rte/{r.instance_name}/{r.mapping_name}",
                            parameter_name="RteBswMappedToTaskRef",
                            workbench_tab=2,
                            suggested_fix="在 RTE / SchM 工作台页签 3 改派至已存在的 OsTask 或在 Os 中创建该任务",
                        )
                    )

            distinct_periods = sorted({
                round(float(r.period_sec), 9)
                for r in bsw_rows
                if r.period_sec is not None and r.period_sec > 0
            })
            if len(distinct_periods) > 1:
                labels = [format_period_label(p) for p in distinct_periods]
                diags.append(
                    RteSchmDiagnostic(
                        severity="warning",
                        code="MIXED_TASK_PERIOD",
                        message=f"OsTask '{task_name}' 同时挂载了不同周期的 BSW 定时事件（{' / '.join(labels)}）",
                        container_path=f"/Rte/{bsw_rows[0].instance_name}/{bsw_rows[0].mapping_name}",
                        parameter_name="RteBswMappedToTaskRef",
                        workbench_tab=2,
                        suggested_fix="建议按周期拆分到独立 OsTask 或确认调度分频逻辑",
                    )
                )

            is_extended = bool(task_info is not None and task_info.task_type == "EXTENDED")
            for r in bsw_rows:
                m_path = f"/Rte/{r.instance_name}/{r.mapping_name}"
                if r.used_os_event:
                    if os_loaded and r.used_os_event not in os_events:
                        diags.append(
                            RteSchmDiagnostic(
                                severity="warning",
                                code="DANGLING_OS_EVENT",
                                message=f"BSW 事件 {r.module_name}.{r.event_name} 引用的 OsEvent '{r.used_os_event}' 在 Os 模块中未定义",
                                container_path=m_path,
                                parameter_name="RteBswUsedOsEventRef",
                                workbench_tab=2,
                                suggested_fix="在 Os 模块补充对应 OsEvent 或修正 RteBswUsedOsEventRef",
                            )
                        )
                elif is_extended:
                    diags.append(
                        RteSchmDiagnostic(
                            severity="warning",
                            code="EXTENDED_TASK_MISSING_EVENT",
                            message=f"BSW 事件 {r.module_name}.{r.event_name} 映射到 EXTENDED 任务 '{task_name}'，但缺少 RteBswUsedOsEventRef",
                            container_path=m_path,
                            parameter_name="RteBswUsedOsEventRef",
                            workbench_tab=2,
                            suggested_fix="为该 RteBswEventToTaskMapping 绑定 OsEvent（面向阶段 3 WaitEvent 调度生成）",
                        )
                    )

        activations = self.list_os_activations()
        activated_tasks: Set[str] = set()
        for act in activations:
            if act.task_name and (act.alarm_name or act.schedule_table_name):
                activated_tasks.add(act.task_name)

            if not act.alarm_name and not act.schedule_table_name:
                diags.append(
                    RteSchmDiagnostic(
                        severity="warning",
                        code="ACTIVATION_MISSING_SOURCE",
                        message=f"RteUsedOsActivation '{act.name}' 未关联 RteActivationOsAlarmRef 或 RteActivationOsSchTblRef",
                        container_path=act.container_path,
                        parameter_name="RteActivationOsAlarmRef",
                        workbench_tab=2,
                        suggested_fix="在 RteOsInteraction 中补充关联 OsAlarm 或 OsScheduleTable",
                    )
                )

            if os_loaded:
                if act.task_name and (act.task_name not in task_map or task_map[act.task_name].missing_in_os):
                    diags.append(
                        RteSchmDiagnostic(
                            severity="warning",
                            code="DANGLING_OS_ACTIVATION",
                            message=f"RteUsedOsActivation '{act.name}' 引用的 OsTask '{act.task_name}' 在 Os 模块中未定义",
                            container_path=act.container_path,
                            parameter_name="RteActivationOsTaskRef",
                            workbench_tab=2,
                            suggested_fix="核对 Os 模块中的 OsTask 名称并更新 RteActivationOsTaskRef",
                        )
                    )
                if act.alarm_name and act.alarm_name not in os_alarms:
                    diags.append(
                        RteSchmDiagnostic(
                            severity="warning",
                            code="DANGLING_OS_ACTIVATION",
                            message=f"RteUsedOsActivation '{act.name}' 引用的 OsAlarm '{act.alarm_name}' 在 Os 模块中未定义",
                            container_path=act.container_path,
                            parameter_name="RteActivationOsAlarmRef",
                            workbench_tab=2,
                            suggested_fix="核对 Os 模块中的 OsAlarm 名称并更新 RteActivationOsAlarmRef",
                        )
                    )
                if act.schedule_table_name and act.schedule_table_name not in os_schtbls:
                    diags.append(
                        RteSchmDiagnostic(
                            severity="warning",
                            code="DANGLING_OS_ACTIVATION",
                            message=f"RteUsedOsActivation '{act.name}' 引用的 OsScheduleTable '{act.schedule_table_name}' 在 Os 模块中未定义",
                            container_path=act.container_path,
                            parameter_name="RteActivationOsSchTblRef",
                            workbench_tab=2,
                            suggested_fix="核对 Os 模块中的 OsScheduleTable 名称并更新 RteActivationOsSchTblRef",
                        )
                    )

            if act.task_name and act.expected_tick_duration is not None and act.expected_tick_duration > 0:
                task_bsw = [r for r in mapped_by_task.get(act.task_name, []) if not r.is_swc]
                tick_periods = sorted({
                    round(float(r.period_sec), 9)
                    for r in task_bsw
                    if r.period_sec is not None and r.period_sec > 0
                })
                for p in tick_periods:
                    ratio = p / act.expected_tick_duration
                    if p < act.expected_tick_duration - 1e-6 or abs(ratio - round(ratio)) > 1e-3:
                        diags.append(
                            RteSchmDiagnostic(
                                severity="warning",
                                code="ACTIVATION_PERIOD_MISMATCH",
                                message=(
                                    f"RteUsedOsActivation '{act.name}' 的期望周期 "
                                    f"{format_period_label(act.expected_tick_duration)} 与任务 '{act.task_name}' "
                                    f"下事件周期 {format_period_label(p)} 不成整数倍关系"
                                ),
                                container_path=act.container_path,
                                parameter_name="RteExpectedTickDuration",
                                workbench_tab=2,
                                suggested_fix="调整 RteExpectedTickDuration 或将不匹配周期的事件迁移至对应 Task",
                            )
                        )

        if os_loaded:
            for task_name, rows in mapped_by_task.items():
                task_info = task_map.get(task_name)
                if task_info is None or task_info.missing_in_os:
                    continue
                periodic_bsw = [
                    r
                    for r in rows
                    if (not r.is_swc) and r.period_sec is not None and r.period_sec > 0
                ]
                if not periodic_bsw:
                    continue
                covered = (task_name in activated_tasks) or all(
                    r.used_os_alarm or r.used_os_schtbl_ep for r in periodic_bsw
                )
                if not covered:
                    periods_str = ", ".join(
                        sorted({format_period_label(r.period_sec) for r in periodic_bsw})
                    )
                    diags.append(
                        RteSchmDiagnostic(
                            severity="warning",
                            code="TASK_MISSING_ACTIVATION",
                            message=(
                                f"周期任务 '{task_name}' 挂载了定时 BSW 事件（{periods_str}），"
                                "但未在 RteOsInteraction/RteUsedOsActivation 中配置 OsAlarm 或 OsScheduleTable 激活源"
                            ),
                            container_path=f"/Rte/{periodic_bsw[0].instance_name}/{periodic_bsw[0].mapping_name}",
                            parameter_name=None,
                            workbench_tab=2,
                            suggested_fix="在 RteOsInteraction/RteUsedOsActivation 中为该任务关联 OsAlarm 或 OsScheduleTable（面向阶段 3 调度生成）",
                        )
                    )

        # Tab 4 & Tab 5: SWC Data Mapping & Service Port diagnostics (only when SWCs or overlays exist)
        has_swc_ctx = bool(self._swc_index()) or bool(getattr(self.project, "rte_data_mappings", None)) or bool(
            getattr(self.project, "rte_service_connectors", None)
        )
        if has_swc_ctx:
            for dm in self.list_data_mapping_rows():
                if dm.status == "broken_com":
                    diags.append(
                        RteSchmDiagnostic(
                            severity="error",
                            code="DATA_MAPPING_BROKEN_COM_SIGNAL",
                            message=f"SWC 数据端口 {dm.component_name}.{dm.port_name} 引用的 ComSignal '{dm.com_signal_name or dm.system_signal_name}' 不存在或未绑定",
                            container_path=f"/Rte/{dm.component_name}",
                            parameter_name=None,
                            workbench_tab=3,
                            suggested_fix="在 RTE 工作台页签 4「数据映射」重新选择有效的 ComSignal 或点击自动匹配",
                        )
                    )
                elif dm.status == "direction_mismatch":
                    diags.append(
                        RteSchmDiagnostic(
                            severity="error",
                            code="DATA_MAPPING_DIRECTION_MISMATCH",
                            message=f"SWC 端口 {dm.component_name}.{dm.port_name} ({dm.direction}) 与 ComSignal '{dm.com_signal_name}' ({dm.com_signal_direction}) 收发方向不一致",
                            container_path=f"/Rte/{dm.component_name}",
                            parameter_name=None,
                            workbench_tab=3,
                            suggested_fix="在 RTE 工作台页签 4「数据映射」重新绑定方向匹配的 ComSignal",
                        )
                    )
                elif dm.status == "unmapped":
                    diags.append(
                        RteSchmDiagnostic(
                            severity="info",
                            code="SWC_PORT_UNMAPPED_COM",
                            message=f"SWC SR 端口 {dm.component_name}.{dm.port_name} ({dm.direction}) 尚未映射到 ComSignal 或 SWC 连接",
                            container_path=f"/Rte/{dm.component_name}",
                            parameter_name=None,
                            workbench_tab=3,
                            suggested_fix="若需经 CAN 发送/接收，请在页签 4 绑定 ComSignal；若为核内/核间通信，请在页签 5 连接端口",
                        )
                    )

            for sp in self.list_service_port_rows():
                if sp.status == "broken":
                    diags.append(
                        RteSchmDiagnostic(
                            severity="error",
                            code="SERVICE_CONNECTOR_BROKEN",
                            message=f"端口连接 {sp.requester_component}.{sp.requester_port} -> {sp.provider_component}.{sp.provider_port} 无效或接口类型不匹配",
                            container_path=f"/Rte/{sp.requester_component}",
                            parameter_name=None,
                            workbench_tab=4,
                            suggested_fix="在 RTE 工作台页签 5「服务与端口连接」重新选择兼容的提供方端口",
                        )
                    )
                elif sp.status == "unconnected" and (sp.is_service or sp.interface_kind in ("CS", "MODE")):
                    diags.append(
                        RteSchmDiagnostic(
                            severity="warning",
                            code="SERVICE_PORT_UNCONNECTED",
                            message=f"{'服务' if sp.is_service else ''}请求端口 {sp.requester_component}.{sp.requester_port} ({sp.interface_name}) 尚未连接到提供方端口",
                            container_path=f"/Rte/{sp.requester_component}",
                            parameter_name=None,
                            workbench_tab=4,
                            suggested_fix="在 RTE 工作台页签 5 连接兼容的服务端口或点击「自动连接服务端口」",
                        )
                    )

        return diags

    # ------------------------------------------------------------------
    # Tab 4: Global RteGeneration Settings, Live Preview & Generation
    # ------------------------------------------------------------------

    def read_rte_generation_settings(self) -> RteGenerationSettings:
        """Read ``RteGeneration`` and ``RteBswGeneral`` parameter values."""
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            return RteGenerationSettings()

        gen_c: Optional[EcucContainerValue] = None
        bsw_gen_c: Optional[EcucContainerValue] = None
        for c in getattr(rte_cfg, "containers", []) or []:
            leaf = _ar_leaf(getattr(c, "definition_ref", None))
            if leaf == "RteGeneration" and gen_c is None:
                gen_c = c
            elif leaf == "RteBswGeneral" and bsw_gen_c is None:
                bsw_gen_c = c

        def _bool_p(c: Optional[EcucContainerValue], key: str, default: bool = False) -> bool:
            if c is None or key not in c.parameter_values:
                return default
            return _as_bool(c.parameter_values[key].value, default)

        def _str_p(c: Optional[EcucContainerValue], key: str, default: str) -> str:
            if c is None or key not in c.parameter_values or c.parameter_values[key].value is None:
                return default
            text = str(c.parameter_values[key].value).strip()
            return text or default

        return RteGenerationSettings(
            enable_multi_core=_bool_p(gen_c, "RteEnableMultiCore", False),
            enable_memory_protection=_bool_p(gen_c, "RteEnableMemoryProtection", False),
            dev_error_detect=_bool_p(gen_c, "RteDevErrorDetect", False),
            dev_error_detect_uninit=_bool_p(gen_c, "RteDevErrorDetectUninit", False),
            disable_rte_init_memory=_bool_p(gen_c, "RteDisableRteInitMemory", False),
            vfb_trace_enabled=_bool_p(gen_c, "RteVfbTraceEnabled", False),
            schm_version_info_api=_bool_p(bsw_gen_c, "RteSchMVersionInfoApi", False),
            generation_mode=_str_p(gen_c, "RteGenerationMode", "COMPATIBILITY_MODE"),
            optimization_mode=_str_p(gen_c, "RteOptimizationMode", "RUNTIME"),
        )

    def update_rte_generation_settings(self, settings: RteGenerationSettings) -> None:
        """Persist ``RteGenerationSettings`` into ``RteGeneration`` and ``RteBswGeneral``."""
        gen_c = self._find_or_create_top_container("RteGeneration", "RteGeneration")
        bsw_gen_c = self._find_or_create_top_container("RteBswGeneral", "RteBswGeneral")

        self._set_param(gen_c, "RteEnableMultiCore", bool(settings.enable_multi_core), "ECUC-BOOLEAN-PARAM-DEF")
        self._set_param(
            gen_c,
            "RteEnableMemoryProtection",
            bool(settings.enable_memory_protection),
            "ECUC-BOOLEAN-PARAM-DEF",
        )
        self._set_param(gen_c, "RteDevErrorDetect", bool(settings.dev_error_detect), "ECUC-BOOLEAN-PARAM-DEF")
        self._set_param(
            gen_c,
            "RteDevErrorDetectUninit",
            bool(settings.dev_error_detect_uninit),
            "ECUC-BOOLEAN-PARAM-DEF",
        )
        self._set_param(
            gen_c,
            "RteDisableRteInitMemory",
            bool(settings.disable_rte_init_memory),
            "ECUC-BOOLEAN-PARAM-DEF",
        )
        self._set_param(gen_c, "RteVfbTraceEnabled", bool(settings.vfb_trace_enabled), "ECUC-BOOLEAN-PARAM-DEF")
        self._set_param(
            gen_c,
            "RteGenerationMode",
            settings.generation_mode or "COMPATIBILITY_MODE",
            "ECUC-ENUMERATION-PARAM-DEF",
        )
        self._set_param(
            gen_c,
            "RteOptimizationMode",
            settings.optimization_mode or "RUNTIME",
            "ECUC-ENUMERATION-PARAM-DEF",
        )
        self._set_param(
            bsw_gen_c,
            "RteSchMVersionInfoApi",
            bool(settings.schm_version_info_api),
            "ECUC-BOOLEAN-PARAM-DEF",
        )

    def default_output_layout(self) -> Tuple[Path, bool, Optional[Path], Optional[str]]:
        """Resolve ``(gen_dir, is_flat, overlay_root, package_dir_name)`` for this project."""
        gen_dir = (
            project_paths.resolve(self.project, "gen")
            if getattr(self.project, "path", None) is not None
            else Path.cwd() / project_paths.dirs(self.project).gen
        )
        is_flat = project_paths.dirs(self.project).gen_layout == project_paths.GEN_LAYOUT_FLAT
        overlay_root: Optional[Path] = None
        if getattr(self.project, "path", None) is not None:
            candidate_overlay, _ = project_paths.template_sources(self.project, "Rte")
            if candidate_overlay.exists():
                overlay_root = candidate_overlay
        pkg_dir_name = project_paths.package_dir_name(self.project, "Rte")
        return gen_dir, is_flat, overlay_root, pkg_dir_name

    def preview_generation(
        self,
        *,
        output_dir: Optional[Path] = None,
        flat: Optional[bool] = None,
        generate_type_stub: bool = True,
        include_phase2_3: bool = True,
        apply_overlay: bool = True,
    ) -> Tuple[List[RtePreviewFile], RteGenerationReport]:
        """Compute non-mutating Phase 1-3 file previews and extraction diagnostics."""
        default_dir, default_flat, overlay_root, pkg_dir_name = self.default_output_layout()
        target_dir = Path(output_dir) if output_dir is not None else default_dir
        is_flat = default_flat if flat is None else flat
        gen = RteSchMGenerator(
            self.project,
            generate_type_stub=generate_type_stub,
            include_phase2_3=include_phase2_3,
        )
        return gen.preview(
            target_dir,
            flat=is_flat,
            overlay_root=overlay_root if apply_overlay else None,
            package_dir_name=pkg_dir_name,
            ib_index=self._ib_index(),
            swc_index=self._swc_index(),
        )

    def run_generation(
        self,
        *,
        output_dir: Optional[Path] = None,
        flat: Optional[bool] = None,
        generate_type_stub: bool = True,
        include_phase2_3: bool = True,
        force: bool = False,
        apply_overlay: bool = True,
    ) -> Tuple[bool, RteGenerationReport, str]:
        """Execute Phase 1-3 RTE/SchM generation (with optional overlay override pass)."""
        default_dir, default_flat, overlay_root, pkg_dir_name = self.default_output_layout()
        target_dir = Path(output_dir) if output_dir is not None else default_dir
        is_flat = default_flat if flat is None else flat

        rte_mgr = self._rte_manager()
        all_configs = {}
        for name, mgr in self._managers().items():
            if getattr(mgr, "module_def", None) and getattr(mgr, "configuration", None):
                all_configs[name] = (mgr.module_def, mgr.configuration)

        variant_name = getattr(self.project, "active_variant", None)
        project_variants = list(getattr(self.project, "variants", None) or []) or None
        variant_overrides: Dict[str, Any] = {}
        if variant_name and rte_mgr is not None and getattr(rte_mgr, "configuration", None) is not None:
            from ...core.model.configuration_model import override_layer

            layer = override_layer(variant_name)
            if layer:
                variant_overrides = rte_mgr.configuration.variant_overrides.get(layer, {})

        ecu_resources: Optional[Dict[str, Any]] = None
        if hasattr(self.project, "load_ecu_resources"):
            try:
                res = self.project.load_ecu_resources()
                ecu_resources = dict(res) if res else None
            except Exception:
                ecu_resources = None

        project_root = (
            project_paths.project_root(self.project)
            if getattr(self.project, "path", None) is not None
            else None
        )
        ok, report, detail = run_rte_schm_pipeline(
            self.project,
            target_dir,
            flat=is_flat,
            generate_type_stub=generate_type_stub,
            include_phase2_3=include_phase2_3,
            force=force,
            apply_overlay=apply_overlay,
            overlay_root=overlay_root if (apply_overlay and has_project_overlay_templates(overlay_root, "Rte", pkg_dir_name)) else None,
            variant_name=variant_name,
            variant_overrides=variant_overrides,
            project_variants=project_variants,
            all_configs=all_configs,
            selected_chip=getattr(self.project, "selected_chip", None),
            ecu_resources=ecu_resources,
            project_root=project_root,
            package_dir_name=pkg_dir_name,
            module_def=getattr(rte_mgr, "module_def", None) if rte_mgr else None,
            configuration=getattr(rte_mgr, "configuration", None) if rte_mgr else None,
            ib_index=self._ib_index(),
            swc_index=self._swc_index(),
        )
        return ok, report, detail
