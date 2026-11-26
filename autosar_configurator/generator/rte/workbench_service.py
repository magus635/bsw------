"""Pure-Python domain service backing the 4-tab RTE / SchM Configuration Workbench."""

from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

from ...core import project_paths
from ...core.model.configuration_model import EcucContainerValue
from ...core.model.ecuc_paths import strip_ecuc_prefixes
from .extractor import RteModelExtractor, _ar_leaf, _as_bool, _parse_int
from .generator import (
    RteSchMGenerator,
    has_project_overlay_templates,
    run_rte_schm_pipeline,
)
from .ib_parser import BswIbEventData, BswIbImplData, BswIbIndex, BswIbModuleData
from .model import RteGenerationReport, RtePreviewFile

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
class SyncSummary:
    """Result counts returned by :meth:`RteWorkbenchService.sync_bsw_instances`."""

    added_instances: int = 0
    added_exclusive_areas: int = 0
    removed_instances: int = 0


class RteWorkbenchService:
    """Qt-free ECUC/InternalBehavior coordinator for the RTE/SchM Workbench."""

    def __init__(self, project: Any) -> None:
        self.project = project
        self._ib_cache: Optional[BswIbIndex] = None

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

    def _set_param(
        self,
        container: EcucContainerValue,
        name: str,
        value: Any,
        dest_type: str,
    ) -> None:
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
        ib_index = self.reload_ib_index()
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
        self._set_ref(
            inst,
            "RteBswModuleConfigurationRef",
            f"/ActiveEcuC/{module_name}",
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

        rte_cfg.add_container(inst)
        self._mark_rte_modified()

        if populate_exclusive_areas and ib_data is not None:
            path_by_ea = {ea_sn: ea_path for ea_path, ea_sn in ib_data.exclusive_area_paths.items()}
            for ea_name in ib_data.exclusive_areas:
                self._create_exclusive_area_sub(inst, ea_name, ea_ref=path_by_ea.get(ea_name))

        return inst

    def remove_bsw_instance(self, instance_name: str) -> bool:
        """Remove the named ``RteBswModuleInstance`` from ``Rte`` configuration."""
        rte_cfg = self._rte_cfg()
        if rte_cfg is None:
            return False
        inst = self._find_bsw_instance(instance_name)
        if inst is None:
            return False
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
                if row.status == "unloaded" and self.remove_bsw_instance(row.instance_name):
                    summary.removed_instances += 1

        if add_missing_modules:
            for row in rows:
                if row.status == "unregistered":
                    self.add_bsw_instance(row.module_name, populate_exclusive_areas=False)
                    summary.added_instances += 1

        if sync_exclusive_areas:
            summary.added_exclusive_areas = self.sync_missing_exclusive_areas()

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
        sub = EcucContainerValue(
            short_name=ea_name,
            definition_ref=f"{inst.definition_ref.rstrip('/')}/RteBswExclusiveAreaImpl",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        inst.add_sub_container(sub)
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
        self._set_param(sub, "RteExclusiveAreaImplMechanism", mech, "ECUC-ENUMERATION-PARAM-DEF")
        self._set_param(
            sub,
            "RteExclusiveAreaGenerateFunction",
            bool(generate_function),
            "ECUC-BOOLEAN-PARAM-DEF",
        )
        if mech == "OS_RESOURCE":
            self._remove_ref(sub, "RteBswExclusiveAreaOsSpinlockRef")
            if os_resource:
                self._set_ref(
                    sub,
                    "RteBswExclusiveAreaOsResourceRef",
                    f"/ActiveEcuC/Os/{os_resource}",
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
                    f"/ActiveEcuC/Os/{os_spinlock}",
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

    def sync_missing_exclusive_areas(self) -> int:
        """Create default ``RteBswExclusiveAreaImpl`` entries for IB-only ExclusiveAreas."""
        created = 0
        for row in self.list_exclusive_area_rows():
            if row.configured:
                continue
            self.update_exclusive_area(
                row.instance_name,
                row.ea_name,
                mechanism="ALL_INTERRUPT_BLOCKING",
                generate_function=False,
                ea_ref=row.ea_ref,
            )
            created += 1
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
    ) -> Tuple[Dict[str, List[TaskEventMappingRow]], List[TaskEventMappingRow]]:
        """Return ``(mapped_by_task, unmapped_bsw_events)`` across ``Rte`` and IB models."""
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
            for swc_inst in self._swc_instance_containers():
                swc_name = swc_inst.short_name
                for sub in getattr(swc_inst, "sub_containers", []) or []:
                    if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteEventToTaskMapping":
                        continue
                    task_ref_v = sub.reference_values.get("RteMappedToTaskRef")
                    task_name = _ar_leaf(task_ref_v.value_ref) if task_ref_v and task_ref_v.value_ref else None
                    if not task_name:
                        continue
                    ev_ref_v = sub.reference_values.get("RteEventRef")
                    ev_ref = ev_ref_v.value_ref.strip().rstrip("/") if ev_ref_v and ev_ref_v.value_ref else None
                    ev_name = _ar_leaf(ev_ref) or sub.short_name
                    pos_p = sub.parameter_values.get("RtePositionInTask")
                    pos = None
                    if pos_p and pos_p.value is not None:
                        try:
                            pos = int(pos_p.value)
                        except (ValueError, TypeError):
                            pos = None
                    imm_p = sub.parameter_values.get("RteImmediateRestart")
                    imm = _as_bool(imm_p.value if imm_p else None, False)
                    mapped_by_task.setdefault(task_name, []).append(
                        TaskEventMappingRow(
                            instance_name=swc_name,
                            module_name=swc_name,
                            api_name=swc_name,
                            mapping_name=sub.short_name,
                            event_name=ev_name,
                            event_ref=ev_ref,
                            event_kind=(ev_ref_v.value_ref_dest if ev_ref_v and ev_ref_v.value_ref_dest else "SWC-EVENT"),
                            entity_name=None,
                            period_sec=None,
                            task_name=task_name,
                            position=pos,
                            immediate_restart=imm,
                            is_swc=True,
                            has_ecuc_container=True,
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
        if sub is None:
            sub = EcucContainerValue(
                short_name=event_name,
                definition_ref=f"{inst.definition_ref.rstrip('/')}/RteBswEventToTaskMapping",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            inst.add_sub_container(sub)
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
            f"/ActiveEcuC/Os/{task_name}",
            dest_type="ECUC-REFERENCE-DEF",
            value_ref_dest="ECUC-CONTAINER-VALUE",
        )
        self._set_param(sub, "RteBswPositionInTask", int(position), "ECUC-INTEGER-PARAM-DEF")
        return sub

    def unmap_event(self, instance_name: str, mapping_name: str) -> bool:
        """Clear task mapping reference and position while retaining the mapping container."""
        inst = self._find_bsw_instance(instance_name)
        if inst is None:
            return False
        sub = self._find_mapping_sub(inst, mapping_name)
        if sub is None:
            return False
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
        apply_overlay: bool = True,
    ) -> Tuple[List[RtePreviewFile], RteGenerationReport]:
        """Compute non-mutating Phase 1 file previews and extraction diagnostics."""
        default_dir, default_flat, overlay_root, pkg_dir_name = self.default_output_layout()
        target_dir = Path(output_dir) if output_dir is not None else default_dir
        is_flat = default_flat if flat is None else flat
        gen = RteSchMGenerator(self.project, generate_type_stub=generate_type_stub)
        return gen.preview(
            target_dir,
            flat=is_flat,
            overlay_root=overlay_root if apply_overlay else None,
            package_dir_name=pkg_dir_name,
        )

    def run_generation(
        self,
        *,
        output_dir: Optional[Path] = None,
        flat: Optional[bool] = None,
        generate_type_stub: bool = True,
        force: bool = False,
        apply_overlay: bool = True,
    ) -> Tuple[bool, RteGenerationReport, str]:
        """Execute Phase 1 RTE/SchM generation (with optional overlay override pass)."""
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
        )
        return ok, report, detail
