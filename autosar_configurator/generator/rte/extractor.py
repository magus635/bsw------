"""Cross-model synthesizer producing :class:`RteProjectModel` for Phase 1 generation."""

from pathlib import Path
import re
from typing import Any, Dict, List, Optional, Set, Tuple

from ...core import project_paths
from ...core.model.ecuc_paths import strip_ecuc_prefixes
from .ib_parser import BswIbImplData, BswIbIndex, BswIbModuleData
from .model import (
    BswModuleSchmModel,
    ExclusiveAreaModel,
    OsActivationScheduleModel,
    OsTaskScheduleModel,
    RteGenerationReport,
    RteMeta,
    RteProjectModel,
    RteTypeDefEntry,
    SchedulableEntityModel,
    SwcClientCallArgModel,
    SwcClientCallModel,
    SwcComponentModel,
    SwcDataEndpointModel,
    SwcModePointModel,
    SwcSharedBufferModel,
    TaskCallEntry,
)
from .swc_parser import AssemblyConnectorData, SwcDataType, SwcSystemIndex, SwcTypeData

_STD_PRIMITIVE_TYPES = frozenset({
    "boolean",
    "uint8",
    "uint16",
    "uint32",
    "uint64",
    "sint8",
    "sint16",
    "sint32",
    "sint64",
    "float32",
    "float64",
    "Std_ReturnType",
    "void",
    "uint8_least",
    "uint16_least",
    "uint32_least",
    "sint8_least",
    "sint16_least",
    "sint32_least",
})

_VALID_EA_MECHANISMS = frozenset({
    "ALL_INTERRUPT_BLOCKING",
    "OS_INTERRUPT_BLOCKING",
    "OS_RESOURCE",
    "OS_SPINLOCK",
    "COOPERATIVE_RUNNABLE_PLACEMENT",
    "NONE",
    "CUSTOM",
})

_OS_HEADER_MECHANISMS = frozenset({
    "ALL_INTERRUPT_BLOCKING",
    "OS_INTERRUPT_BLOCKING",
    "OS_RESOURCE",
    "OS_SPINLOCK",
})


def _parse_version_triple(raw: Optional[str], default: Tuple[int, int, int]) -> Tuple[int, int, int]:
    if not raw:
        return default
    parts: List[int] = []
    for tok in str(raw).strip().split("."):
        tok = tok.strip()
        if tok.isdigit():
            parts.append(int(tok))
    while len(parts) < 3:
        parts.append(0)
    return parts[0], parts[1], parts[2]


def _parse_int(raw: Any, default: int) -> int:
    if raw is None:
        return default
    try:
        return int(str(raw).strip(), 0)
    except (ValueError, TypeError):
        return default


def _as_bool(raw: Any, default: bool = False) -> bool:
    if raw is None:
        return default
    if isinstance(raw, bool):
        return raw
    s = str(raw).strip().lower()
    if s in ("true", "1", "yes"):
        return True
    if s in ("false", "0", "no"):
        return False
    return default


def _ar_leaf(path: Optional[str]) -> Optional[str]:
    if not path:
        return None
    leaf = path.strip().rstrip("/").rsplit("/", 1)[-1]
    return leaf or None


class RteModelExtractor:
    """Synthesizes Phase 1 RTE/SchM generation IR from a :class:`WorkspaceProject`."""

    @classmethod
    def extract(
        cls,
        project: Any,
        *,
        ib_index: Optional[BswIbIndex] = None,
        swc_index: Optional[SwcSystemIndex] = None,
    ) -> Tuple[Optional[RteProjectModel], RteGenerationReport]:
        """Extract :class:`RteProjectModel` and diagnostics from ``project``."""
        report = RteGenerationReport()
        if project is None:
            report.errors.append("未提供工程对象，无法提取 RTE/SchM 模型")
            return None, report

        managers = getattr(project, "module_managers", {}) or {}
        rte_mgr = managers.get("Rte")
        if rte_mgr is None or rte_mgr.configuration is None:
            report.errors.append("当前工程未加载 Rte 模块或其配置为空")
            return None, report

        meta = cls._extract_rte_meta(project, rte_mgr.configuration)
        os_cores, os_apps = cls._extract_os_entities(managers.get("Os"))
        resolved_ib = ib_index if ib_index is not None else cls._load_ib_index(project)
        resolved_swc = swc_index if swc_index is not None else cls._load_swc_index(project)
        memmap_mods = cls._collect_memmap_modules(managers.get("MemMap"))

        bsw_modules: List[BswModuleSchmModel] = []
        seen_api_names: Set[str] = set()

        for container in getattr(rte_mgr.configuration, "containers", []) or []:
            if _ar_leaf(getattr(container, "definition_ref", None)) != "RteBswModuleInstance":
                continue

            cfg_ref_val = container.reference_values.get("RteBswModuleConfigurationRef")
            cfg_ref = cfg_ref_val.value_ref if cfg_ref_val else None
            target_mod = cls._resolve_target_module_name(cfg_ref, container.short_name)
            if not target_mod or target_mod == "Rte":
                continue

            if target_mod not in managers or managers[target_mod].configuration is None:
                msg = f"跳过未加载模块 '{target_mod}' 的 SchM 头文件生成（RteBswModuleInstance/{container.short_name}）"
                report.skipped_modules.append((target_mod, "模块尚未加载到当前工程"))
                report.warnings.append(msg)
                continue

            mod_model = cls._build_bsw_module_model(
                project=project,
                container=container,
                target_mod=target_mod,
                ib_index=resolved_ib,
                memmap_mods=memmap_mods,
                report=report,
            )
            if mod_model.api_name in seen_api_names:
                report.warnings.append(
                    f"检测到重复的 SchM API 名称 '{mod_model.api_name}'（容器 '{container.short_name}'），已忽略重复实例"
                )
                continue
            seen_api_names.add(mod_model.api_name)
            bsw_modules.append(mod_model)

        bsw_modules.sort(key=lambda m: m.api_name)

        (
            swc_components,
            task_schedules,
            os_activations,
            rte_type_defs,
            shared_buffers,
        ) = cls._extract_phase23_entities(
            project=project,
            rte_cfg=rte_mgr.configuration,
            managers=managers,
            bsw_modules=bsw_modules,
            ib_index=resolved_ib,
            swc_index=resolved_swc,
            os_apps=os_apps,
            memmap_mods=memmap_mods,
        )

        model = RteProjectModel(
            meta=meta,
            bsw_modules=bsw_modules,
            os_cores=os_cores,
            os_applications=os_apps,
            has_com=("Com" in managers and managers["Com"].configuration is not None),
            swc_components=swc_components,
            task_schedules=task_schedules,
            os_activations=os_activations,
            rte_type_defs=rte_type_defs,
            shared_buffers=shared_buffers,
        )
        return model, report

    @staticmethod
    def _resolve_target_module_name(cfg_ref: Optional[str], fallback: str) -> str:
        if cfg_ref:
            stripped = strip_ecuc_prefixes(cfg_ref).strip("/")
            if stripped:
                return stripped.split("/", 1)[0]
        return fallback

    @staticmethod
    def _extract_rte_meta(project: Any, rte_cfg: Any) -> RteMeta:
        impl: Dict[str, Any] = {}
        packages = getattr(project, "packages", {}) or {}
        rte_pkg = packages.get("Rte")
        if rte_pkg is not None:
            try:
                impl = rte_pkg.read_impl_metadata() or {}
            except Exception:
                impl = {}

        sw_maj, sw_min, sw_pat = _parse_version_triple(impl.get("sw_version"), (4, 0, 0))
        ar_maj, ar_min, ar_pat = _parse_version_triple(impl.get("ar_release_version"), (4, 2, 2))
        vendor_id = _parse_int(impl.get("vendor_id"), 30)

        enable_multi_core = False
        enable_mem_prot = False
        disable_init_mem = False
        dev_error_detect = False
        for c in getattr(rte_cfg, "containers", []) or []:
            if _ar_leaf(getattr(c, "definition_ref", None)) != "RteGeneration":
                continue
            pvals = c.parameter_values
            if "RteEnableMultiCore" in pvals:
                enable_multi_core = _as_bool(pvals["RteEnableMultiCore"].value, False)
            if "RteEnableMemoryProtection" in pvals:
                enable_mem_prot = _as_bool(pvals["RteEnableMemoryProtection"].value, False)
            if "RteDisableRteInitMemory" in pvals:
                disable_init_mem = _as_bool(pvals["RteDisableRteInitMemory"].value, False)
            if "RteDevErrorDetect" in pvals:
                dev_error_detect = _as_bool(pvals["RteDevErrorDetect"].value, False)
            break

        return RteMeta(
            sw_major=sw_maj,
            sw_minor=sw_min,
            sw_patch=sw_pat,
            vendor_id=vendor_id,
            module_id=2,
            ar_major=ar_maj,
            ar_minor=ar_min,
            ar_patch=ar_pat,
            enable_multi_core=enable_multi_core,
            enable_memory_protection=enable_mem_prot,
            disable_rte_init_memory=disable_init_mem,
            dev_error_detect=dev_error_detect,
        )

    @staticmethod
    def _extract_os_entities(os_mgr: Any) -> Tuple[List[str], List[str]]:
        if os_mgr is None or getattr(os_mgr, "configuration", None) is None:
            return [], []
        core_raw: List[str] = []
        apps: List[str] = []
        for c in getattr(os_mgr.configuration, "containers", []) or []:
            leaf = _ar_leaf(getattr(c, "definition_ref", None))
            if leaf == "OsCore":
                core_raw.append(c.short_name)
            elif leaf == "OsApplication":
                apps.append(c.short_name)

        cores: List[str] = []
        for idx, name in enumerate(sorted(core_raw)):
            suffix = name[2:] if name.startswith("OsCore") else f"Core{idx}"
            if suffix and suffix not in cores:
                cores.append(suffix)
        return cores, sorted(set(apps))

    @staticmethod
    def _load_ib_index(project: Any) -> BswIbIndex:
        if getattr(project, "path", None) is None:
            return BswIbIndex()
        try:
            system_dir = project_paths.resolve(project, "system")
        except Exception:
            return BswIbIndex()
        if not Path(system_dir).is_dir():
            return BswIbIndex()
        return BswIbIndex.load_directory(Path(system_dir))

    @staticmethod
    def _collect_memmap_modules(memmap_mgr: Any) -> Set[str]:
        mods: Set[str] = set()
        if memmap_mgr is None or getattr(memmap_mgr, "configuration", None) is None:
            return mods

        def _scan_text(val: Any) -> None:
            if not val:
                return
            text = str(val).strip()
            for part in text.replace("\\", "/").split("/"):
                if not part:
                    continue
                if part.endswith("_MemMap"):
                    mods.add(part[:-7])
                elif part.endswith("MemMap.h") and len(part) > 9:
                    mods.add(part[:-9])
                elif part.endswith("_ib_bswmd"):
                    mods.add(part[:-9])
                elif part.endswith("_Impl"):
                    mods.add(part[:-5])

        def _walk_container(c: Any) -> None:
            _scan_text(c.short_name)
            if c.short_name and not c.short_name.startswith("MemMap"):
                mods.add(c.short_name)
            for p in getattr(c, "parameter_values", {}).values():
                _scan_text(getattr(p, "value", None))
            for plist in getattr(c, "multi_parameter_values", {}).values():
                for p in plist:
                    _scan_text(getattr(p, "value", None))
            for r in getattr(c, "reference_values", {}).values():
                _scan_text(getattr(r, "value_ref", None))
            for rlist in getattr(c, "multi_reference_values", {}).values():
                for r in rlist:
                    _scan_text(getattr(r, "value_ref", None))
            for sub in getattr(c, "sub_containers", []) or []:
                _walk_container(sub)

        for top in getattr(memmap_mgr.configuration, "containers", []) or []:
            _walk_container(top)
        return mods

    @classmethod
    def _resolve_ib_data(
        cls,
        *,
        container: Any,
        target_mod: str,
        api_name: str,
        impl_data: Optional[BswIbImplData],
        ib_index: BswIbIndex,
    ) -> Optional[BswIbModuleData]:
        # 1. Exact EA reference in RteBswExclusiveAreaImpl
        for sub in getattr(container, "sub_containers", []) or []:
            if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswExclusiveAreaImpl":
                continue
            ref_v = sub.reference_values.get("RteBswExclusiveAreaRef")
            if ref_v and ref_v.value_ref:
                hit = ib_index.by_ea_path.get(ref_v.value_ref.strip().rstrip("/"))
                if hit is not None:
                    return hit

        # 2. Exact Event reference in RteBswEventToTaskMapping
        for sub in getattr(container, "sub_containers", []) or []:
            if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswEventToTaskMapping":
                continue
            ref_v = sub.reference_values.get("RteBswEventRef")
            if ref_v and ref_v.value_ref:
                hit = ib_index.by_event_path.get(ref_v.value_ref.strip().rstrip("/"))
                if hit is not None:
                    return hit

        # 3. BSW-IMPLEMENTATION BEHAVIOR-REF
        if impl_data is not None and impl_data.behavior_ref:
            hit = ib_index.by_behavior_path.get(impl_data.behavior_ref.strip().rstrip("/"))
            if hit is not None:
                return hit

        # 4. Module short name fallback (preferring API-name-matched file)
        candidates = ib_index.by_module_name.get(target_mod, [])
        if not candidates:
            return None
        for cand in candidates:
            if api_name != target_mod and api_name in cand.source_file:
                return cand
        for cand in candidates:
            if cand.schedulable_entities or cand.exclusive_areas:
                return cand
        return candidates[0]

    @classmethod
    def _build_bsw_module_model(
        cls,
        *,
        project: Any,
        container: Any,
        target_mod: str,
        ib_index: BswIbIndex,
        memmap_mods: Set[str],
        report: RteGenerationReport,
    ) -> BswModuleSchmModel:
        pkg = (getattr(project, "packages", {}) or {}).get(target_mod)
        pkg_impl: Dict[str, Any] = {}
        if pkg is not None:
            try:
                pkg_impl = pkg.read_impl_metadata() or {}
            except Exception:
                pkg_impl = {}

        impl_ref_v = container.reference_values.get("RteBswImplementationRef")
        impl_ref = impl_ref_v.value_ref.strip().rstrip("/") if impl_ref_v and impl_ref_v.value_ref else None
        ib_impl = ib_index.impls_by_path.get(impl_ref) if impl_ref else None
        if ib_impl is None and pkg_impl.get("ar_path"):
            ib_impl = ib_index.impls_by_path.get(str(pkg_impl["ar_path"]).strip().rstrip("/"))

        vendor_id = pkg_impl.get("vendor_id") or (ib_impl.vendor_id if ib_impl else None)
        vendor_infix = pkg_impl.get("vendor_api_infix") or (ib_impl.vendor_api_infix if ib_impl else None)
        if vendor_infix and vendor_id:
            api_name = f"{target_mod}_{str(vendor_id).strip()}_{str(vendor_infix).strip()}"
        else:
            api_name = target_mod
        upper_prefix = api_name.upper()

        ib_data = cls._resolve_ib_data(
            container=container,
            target_mod=target_mod,
            api_name=api_name,
            impl_data=ib_impl,
            ib_index=ib_index,
        )

        entities: List[SchedulableEntityModel] = []
        if ib_data is not None:
            for entity_sn, entry_name in sorted(ib_data.schedulable_entities, key=lambda x: x[1]):
                entities.append(SchedulableEntityModel(short_name=entity_sn, entry_name=entry_name))

        # Merge ExclusiveAreas from IB definition and Rte ECUC RteBswExclusiveAreaImpl
        configured_eas: Dict[str, ExclusiveAreaModel] = {}
        for sub in getattr(container, "sub_containers", []) or []:
            if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswExclusiveAreaImpl":
                continue
            ea_ref_v = sub.reference_values.get("RteBswExclusiveAreaRef")
            ea_name = _ar_leaf(ea_ref_v.value_ref if ea_ref_v else None) or sub.short_name
            mech_p = sub.parameter_values.get("RteExclusiveAreaImplMechanism")
            mech = str(mech_p.value).strip() if mech_p and mech_p.value is not None else "ALL_INTERRUPT_BLOCKING"
            if mech not in _VALID_EA_MECHANISMS:
                report.errors.append(
                    f"模块 '{api_name}' ExclusiveArea '{ea_name}' 使用了未知机制 '{mech}'"
                )
            gen_fn_p = sub.parameter_values.get("RteExclusiveAreaGenerateFunction")
            gen_fn = _as_bool(gen_fn_p.value if gen_fn_p else None, False)
            res_v = sub.reference_values.get("RteBswExclusiveAreaOsResourceRef")
            spin_v = sub.reference_values.get("RteBswExclusiveAreaOsSpinlockRef")
            os_res = _ar_leaf(res_v.value_ref if res_v else None)
            os_spin = _ar_leaf(spin_v.value_ref if spin_v else None)

            if mech == "OS_RESOURCE" and not os_res:
                report.errors.append(
                    f"模块 '{api_name}' ExclusiveArea '{ea_name}' 机制为 OS_RESOURCE，但缺少 RteBswExclusiveAreaOsResourceRef"
                )
            if mech == "OS_SPINLOCK" and not os_spin:
                report.errors.append(
                    f"模块 '{api_name}' ExclusiveArea '{ea_name}' 机制为 OS_SPINLOCK，但缺少 RteBswExclusiveAreaOsSpinlockRef"
                )

            configured_eas[ea_name] = ExclusiveAreaModel(
                short_name=ea_name,
                mechanism=mech,
                os_resource=os_res,
                os_spinlock=os_spin,
                generate_function=gen_fn,
            )

        ib_ea_names = list(ib_data.exclusive_areas) if ib_data is not None else []
        all_ea_names = sorted(set(configured_eas.keys()) | set(ib_ea_names))
        exclusive_areas: List[ExclusiveAreaModel] = []
        for ea_name in all_ea_names:
            if ea_name in configured_eas:
                exclusive_areas.append(configured_eas[ea_name])
            else:
                report.warnings.append(
                    f"模块 '{api_name}' ExclusiveArea '{ea_name}' 仅在 InternalBehavior 中声明，"
                    f"未在 Rte ECUC 配置 RteBswExclusiveAreaImpl，已按默认 ALL_INTERRUPT_BLOCKING 生成"
                )
                exclusive_areas.append(ExclusiveAreaModel(short_name=ea_name))

        requires_os_header = any(
            not ea.generate_function and ea.mechanism in _OS_HEADER_MECHANISMS
            for ea in exclusive_areas
        )

        # 3-tier MemMap header resolution
        explicit_artifact: Optional[str] = ib_impl.memmap_artifact_header if ib_impl else None
        if not explicit_artifact:
            for art in pkg_impl.get("required_artifacts", []) or []:
                if not isinstance(art, dict):
                    continue
                lbl = (art.get("short_label") or "").strip()
                cat = (art.get("category") or "").strip().upper()
                if lbl and (cat == "MEMMAP" or lbl.endswith("MemMap.h")):
                    explicit_artifact = lbl
                    break

        ar_rel_ver = pkg_impl.get("ar_release_version") or (ib_impl.ar_release_version if ib_impl else None)
        ar_triple = _parse_version_triple(ar_rel_ver, (0, 0, 0))
        pkg_mem_count = len(pkg_impl.get("memory_sections", []) or [])
        ib_mem_count = ib_impl.memory_section_count if ib_impl else 0

        if explicit_artifact:
            memmap_header = explicit_artifact
        elif (
            pkg_mem_count > 0
            or ib_mem_count > 0
            or target_mod in memmap_mods
            or api_name in memmap_mods
            or ar_triple >= (4, 3, 0)
        ):
            memmap_header = f"{api_name}_MemMap.h"
        else:
            memmap_header = "MemMap.h"

        return BswModuleSchmModel(
            module_name=target_mod,
            api_name=api_name,
            upper_prefix=upper_prefix,
            memmap_header=memmap_header,
            schedulable_entities=entities,
            exclusive_areas=exclusive_areas,
            requires_os_header=requires_os_header,
        )

    # ------------------------------------------------------------------
    # Phase 2/3 SWC, Data Mapping, Service Connector & OsTask Extraction
    # ------------------------------------------------------------------

    @staticmethod
    def _load_swc_index(project: Any) -> SwcSystemIndex:
        if getattr(project, "path", None) is None:
            return SwcSystemIndex()
        try:
            system_dir = project_paths.resolve(project, "system")
        except Exception:
            return SwcSystemIndex()
        if not Path(system_dir).is_dir():
            return SwcSystemIndex()
        return SwcSystemIndex.load_directory(Path(system_dir))

    @staticmethod
    def _core_num(name: Optional[str], default: int = 0) -> int:
        if not name:
            return default
        m = re.search(r"(\d+)$", str(name).strip())
        return int(m.group(1)) if m else default

    @classmethod
    def _collect_os_partition_info(
        cls,
        os_mgr: Any,
        os_apps: List[str],
    ) -> Tuple[
        Dict[str, Dict[str, Any]],
        Dict[str, str],
        Dict[str, int],
        Dict[str, str],
        Dict[str, str],
        str,
    ]:
        """Extract OsTask metadata and OsApplication -> Core/Task/Alarm/ScheduleTable partitioning."""
        task_meta: Dict[str, Dict[str, Any]] = {}
        task_to_app: Dict[str, str] = {}
        app_to_core: Dict[str, int] = {}
        alarm_to_app: Dict[str, str] = {}
        schtbl_to_app: Dict[str, str] = {}
        default_app = os_apps[0] if os_apps else "SystemApplication_OsCore0"

        if os_mgr is None or getattr(os_mgr, "configuration", None) is None:
            if default_app:
                app_to_core[default_app] = 0
            return task_meta, task_to_app, app_to_core, alarm_to_app, schtbl_to_app, default_app

        def _all_refs(c: Any, ref_name: str) -> List[str]:
            out: List[str] = []
            single = getattr(c, "reference_values", {}).get(ref_name)
            if single and single.value_ref:
                out.append(single.value_ref)
            for rv in getattr(c, "multi_reference_values", {}).get(ref_name, []) or []:
                if rv.value_ref:
                    out.append(rv.value_ref)
            return out

        def _walk(c: Any) -> None:
            leaf = _ar_leaf(getattr(c, "definition_ref", None))
            if leaf == "OsTask":
                prio_p = c.parameter_values.get("OsTaskPriority")
                type_p = c.parameter_values.get("OsTaskType")
                ev_refs = [_ar_leaf(r) for r in _all_refs(c, "OsTaskEventRef") if _ar_leaf(r)]
                name_low = c.short_name.lower()
                is_init = ("init" in name_low) and ("idle" not in name_low)
                task_meta[c.short_name] = {
                    "priority": _parse_int(prio_p.value if prio_p else None, 0),
                    "task_type": str(type_p.value).strip().upper() if type_p and type_p.value else (
                        "EXTENDED" if ev_refs else "BASIC"
                    ),
                    "events": ev_refs,
                    "is_init": is_init,
                }
            elif leaf == "OsApplication":
                core_refs = _all_refs(c, "OsApplicationCoreRef")
                core_id = cls._core_num(_ar_leaf(core_refs[0]) if core_refs else c.short_name, 0)
                app_to_core[c.short_name] = core_id
                for tref in _all_refs(c, "OsAppTaskRef"):
                    tname = _ar_leaf(tref)
                    if tname:
                        task_to_app[tname] = c.short_name
                for aref in _all_refs(c, "OsAppAlarmRef"):
                    aname = _ar_leaf(aref)
                    if aname:
                        alarm_to_app[aname] = c.short_name
                for sref in _all_refs(c, "OsAppScheduleTableRef"):
                    sname = _ar_leaf(sref)
                    if sname:
                        schtbl_to_app[sname] = c.short_name

            for sub in getattr(c, "sub_containers", []) or []:
                _walk(sub)

        for top in getattr(os_mgr.configuration, "containers", []) or []:
            _walk(top)

        if default_app and default_app not in app_to_core:
            app_to_core[default_app] = 0
        return task_meta, task_to_app, app_to_core, alarm_to_app, schtbl_to_app, default_app

    @staticmethod
    def collect_com_signal_catalog(
        com_mgr: Any,
        swc_index: SwcSystemIndex,
    ) -> Tuple[Dict[str, Dict[str, str]], Dict[str, List[Dict[str, str]]], Dict[str, List[Dict[str, str]]]]:
        """Collect all ``ComSignal`` items with TX/RX direction and resolved SystemSignal path."""
        by_name: Dict[str, Dict[str, str]] = {}
        by_sys_path: Dict[str, List[Dict[str, str]]] = {}
        by_sys_leaf: Dict[str, List[Dict[str, str]]] = {}

        if com_mgr is None or getattr(com_mgr, "configuration", None) is None:
            return by_name, by_sys_path, by_sys_leaf

        sig_dir: Dict[str, str] = {}

        def _walk_com(c: Any) -> None:
            leaf = _ar_leaf(getattr(c, "definition_ref", None))
            if leaf == "ComIPdu":
                dp = c.parameter_values.get("ComIPduDirection")
                d_raw = str(dp.value).upper() if dp and dp.value is not None else "SEND"
                direction = "RX" if ("REC" in d_raw or d_raw == "RX") else "TX"
                refs: List[Any] = []
                if "ComIPduSignalRef" in c.reference_values:
                    refs.append(c.reference_values["ComIPduSignalRef"])
                refs.extend(c.multi_reference_values.get("ComIPduSignalRef", []) or [])
                for rv in refs:
                    s_leaf = _ar_leaf(getattr(rv, "value_ref", None))
                    if s_leaf:
                        sig_dir[s_leaf] = direction
            for sub in getattr(c, "sub_containers", []) or []:
                _walk_com(sub)

        for top in getattr(com_mgr.configuration, "containers", []) or []:
            _walk_com(top)

        def _walk_sigs(c: Any) -> None:
            if _ar_leaf(getattr(c, "definition_ref", None)) == "ComSignal":
                sn = c.short_name
                sys_ref_v = c.reference_values.get("ComSystemTemplateSystemSignalRef")
                raw_sys = (sys_ref_v.value_ref or "").strip().rstrip("/") if sys_ref_v else ""
                resolved_sys = swc_index.resolve_system_signal_for_com_ref(raw_sys) if raw_sys else ""
                direction = sig_dir.get(sn, "RX" if sn.endswith("_Rx") else ("TX" if sn.endswith("_Tx") else ""))
                entry = {
                    "name": sn,
                    "direction": direction,
                    "raw_sys_ref": raw_sys,
                    "resolved_sys": resolved_sys,
                    "macro": f"ComConf_ComSignal_{sn}",
                }
                by_name[sn] = entry
                if resolved_sys:
                    by_sys_path.setdefault(resolved_sys, []).append(entry)
                    s_leaf = _ar_leaf(resolved_sys)
                    if s_leaf:
                        by_sys_leaf.setdefault(s_leaf, []).append(entry)
                if raw_sys and raw_sys != resolved_sys:
                    by_sys_path.setdefault(raw_sys, []).append(entry)
                    r_leaf = _ar_leaf(raw_sys)
                    if r_leaf:
                        by_sys_leaf.setdefault(r_leaf, []).append(entry)
            for sub in getattr(c, "sub_containers", []) or []:
                _walk_sigs(sub)

        for top in getattr(com_mgr.configuration, "containers", []) or []:
            _walk_sigs(top)

        return by_name, by_sys_path, by_sys_leaf

    @staticmethod
    def resolve_effective_data_mappings(
        project: Any,
        swc_index: SwcSystemIndex,
        instance_to_type: Optional[Dict[str, str]] = None,
    ) -> Dict[Tuple[str, str], Dict[str, Any]]:
        """Merge read-only FlatExtract SR signal mappings with ``project.rte_data_mappings`` overlays."""
        effective: Dict[Tuple[str, str], Dict[str, Any]] = {}
        type_map = instance_to_type or {}

        for (comp, port), sr in swc_index.sr_mapping_by_comp_port.items():
            effective[(comp, port)] = {
                "component": comp,
                "port": port,
                "data_element": sr.resolved_data_element_name,
                "system_signal_ref": sr.system_signal_ref,
                "system_signal_name": sr.system_signal_name,
                "com_signal": "",
                "source": "arxml",
            }

        for ov in getattr(project, "rte_data_mappings", []) or []:
            if not isinstance(ov, dict):
                continue
            comp = str(ov.get("component", "")).strip()
            port = str(ov.get("port", "")).strip()
            action = str(ov.get("action", "map")).strip().lower()
            if not comp or not port:
                continue
            keys_to_clear = [(comp, port)]
            # Also match type name if prototype name differs (or vice versa)
            for inst_n, type_n in type_map.items():
                if inst_n == comp:
                    keys_to_clear.append((type_n, port))
                elif type_n == comp:
                    keys_to_clear.append((inst_n, port))
            if action == "unmap":
                for k in keys_to_clear:
                    effective.pop(k, None)
            elif action == "map":
                effective[(comp, port)] = {
                    "component": comp,
                    "port": port,
                    "data_element": str(ov.get("data_element", "")).strip(),
                    "direction": str(ov.get("direction", "")).strip(),
                    "com_signal": str(ov.get("com_signal", "")).strip(),
                    "system_signal_ref": str(ov.get("system_signal_ref", "")).strip(),
                    "system_signal_name": str(ov.get("system_signal_name", "")).strip(),
                    "source": "overlay",
                }
        return effective

    @staticmethod
    def resolve_effective_connectors(
        project: Any,
        swc_index: SwcSystemIndex,
    ) -> List[AssemblyConnectorData]:
        """Merge read-only ARXML assembly connectors with ``project.rte_service_connectors`` overlays."""
        conns = [
            AssemblyConnectorData(
                short_name=c.short_name,
                provider_comp_ref=c.provider_comp_ref,
                provider_port_ref=c.provider_port_ref,
                requester_comp_ref=c.requester_comp_ref,
                requester_port_ref=c.requester_port_ref,
                provider_comp_name=c.provider_comp_name,
                provider_port_name=c.provider_port_name,
                requester_comp_name=c.requester_comp_name,
                requester_port_name=c.requester_port_name,
            )
            for c in swc_index.assembly_connectors
        ]

        for ov in getattr(project, "rte_service_connectors", []) or []:
            if not isinstance(ov, dict):
                continue
            req_c = str(ov.get("requester_component", "")).strip()
            req_p = str(ov.get("requester_port", "")).strip()
            prov_c = str(ov.get("provider_component", "")).strip()
            prov_p = str(ov.get("provider_port", "")).strip()
            action = str(ov.get("action", "map")).strip().lower()
            if not req_c or not req_p:
                continue
            conns = [
                c
                for c in conns
                if not (c.requester_comp_name == req_c and c.requester_port_name == req_p)
            ]
            if action == "map" and prov_c and prov_p:
                conns.append(
                    AssemblyConnectorData(
                        short_name=f"{prov_c}_{prov_p}_{req_c}_{req_p}",
                        provider_comp_ref="",
                        provider_port_ref="",
                        requester_comp_ref="",
                        requester_port_ref="",
                        provider_comp_name=prov_c,
                        provider_port_name=prov_p,
                        requester_comp_name=req_c,
                        requester_port_name=req_p,
                    )
                )
        return conns

    @staticmethod
    def _format_c_init_literal(raw: Optional[str], c_type: str) -> str:
        text = (raw or "0").strip()
        if not text:
            return "0U"
        low = c_type.lower()
        if "boolean" in low:
            return "TRUE" if text.lower() in ("true", "1") else "FALSE"
        if "float" in low:
            return f"{text}F" if "." in text and not text.endswith(("f", "F")) else f"{text}.0F"
        try:
            val = int(text, 0)
            if val >= 0 and not low.startswith("sint"):
                return f"{val}U"
            return str(val)
        except ValueError:
            return text

    @classmethod
    def _extract_phase23_entities(
        cls,
        *,
        project: Any,
        rte_cfg: Any,
        managers: Dict[str, Any],
        bsw_modules: List[BswModuleSchmModel],
        ib_index: BswIbIndex,
        swc_index: SwcSystemIndex,
        os_apps: List[str],
        memmap_mods: Set[str],
    ) -> Tuple[
        List[SwcComponentModel],
        List[OsTaskScheduleModel],
        List[OsActivationScheduleModel],
        List[RteTypeDefEntry],
        List[SwcSharedBufferModel],
    ]:
        task_meta, task_to_app, app_to_core, alarm_to_app, schtbl_to_app, default_app = (
            cls._collect_os_partition_info(managers.get("Os"), os_apps)
        )
        com_by_name, com_by_sys_path, com_by_sys_leaf = cls.collect_com_signal_catalog(
            managers.get("Com"), swc_index
        )

        # Build unified task call lists across BSW & SWC mappings
        task_calls: Dict[str, List[TaskCallEntry]] = {t: [] for t in task_meta}
        swc_inst_tasks: Dict[str, List[str]] = {}
        swc_ea_impls: Dict[str, Dict[str, ExclusiveAreaModel]] = {}
        swc_instances_ecuc: List[Tuple[str, Any, Optional[SwcTypeData]]] = []
        instance_to_type: Dict[str, str] = {}

        bsw_api_by_inst: Dict[str, str] = {}
        for bm in bsw_modules:
            bsw_api_by_inst[bm.module_name] = bm.api_name

        for top in getattr(rte_cfg, "containers", []) or []:
            dleaf = _ar_leaf(getattr(top, "definition_ref", None))
            if dleaf == "RteBswModuleInstance":
                cfg_ref_v = top.reference_values.get("RteBswModuleConfigurationRef")
                mod_name = cls._resolve_target_module_name(cfg_ref_v.value_ref if cfg_ref_v else None, top.short_name)
                if mod_name not in managers or managers[mod_name].configuration is None:
                    continue
                for sub in getattr(top, "sub_containers", []) or []:
                    if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteBswEventToTaskMapping":
                        continue
                    tref = sub.reference_values.get("RteBswMappedToTaskRef")
                    tname = _ar_leaf(tref.value_ref if tref else None)
                    if not tname:
                        continue
                    eref = sub.reference_values.get("RteBswEventRef")
                    epath = eref.value_ref.strip().rstrip("/") if eref and eref.value_ref else ""
                    ev_obj = ib_index.events_by_path.get(epath)
                    symbol = (ev_obj.entity_name if ev_obj and ev_obj.entity_name else _ar_leaf(epath)) or sub.short_name
                    pos_p = sub.parameter_values.get("RteBswPositionInTask")
                    pos = _parse_int(pos_p.value if pos_p else None, None) if pos_p and pos_p.value is not None else None
                    imm_p = sub.parameter_values.get("RteBswImmediateRestart")
                    imm = _as_bool(imm_p.value if imm_p else None, False)
                    task_calls.setdefault(tname, []).append(
                        TaskCallEntry(owner_name=mod_name, symbol=symbol, position=pos, is_swc=False, immediate_restart=imm)
                    )
            elif dleaf == "RteSwComponentInstance":
                inst_ref_v = top.reference_values.get("RteSoftwareComponentInstanceRef")
                inst_ref = inst_ref_v.value_ref.strip().rstrip("/") if inst_ref_v and inst_ref_v.value_ref else ""
                proto_name = _ar_leaf(inst_ref) or top.short_name
                swc_type = swc_index.resolve_swc_type_for_instance(inst_ref, proto_name)
                swc_instances_ecuc.append((proto_name, top, swc_type))
                if swc_type is not None:
                    instance_to_type[proto_name] = swc_type.short_name

                mapped_tasks: List[str] = []
                for sub in getattr(top, "sub_containers", []) or []:
                    sleaf = _ar_leaf(getattr(sub, "definition_ref", None))
                    if sleaf == "RteEventToTaskMapping":
                        tref = sub.reference_values.get("RteMappedToTaskRef")
                        tname = _ar_leaf(tref.value_ref if tref else None)
                        if not tname:
                            continue
                        mapped_tasks.append(tname)
                        eref = sub.reference_values.get("RteEventRef")
                        epath = eref.value_ref.strip().rstrip("/") if eref and eref.value_ref else ""
                        ev_obj = swc_index.event_by_path.get(epath)
                        symbol = (ev_obj.runnable_symbol if ev_obj and ev_obj.runnable_symbol else "")
                        if not symbol:
                            # Fallback strip common Event prefixes
                            ev_leaf = _ar_leaf(epath) or sub.short_name
                            symbol = re.sub(r"^(?:Timer|OIE|DRE|InitEvent|ModeSw)_", "", ev_leaf)
                        pos_p = sub.parameter_values.get("RtePositionInTask")
                        pos = _parse_int(pos_p.value if pos_p else None, None) if pos_p and pos_p.value is not None else None
                        imm_p = sub.parameter_values.get("RteImmediateRestart")
                        imm = _as_bool(imm_p.value if imm_p else None, False)
                        task_calls.setdefault(tname, []).append(
                            TaskCallEntry(owner_name=proto_name, symbol=symbol, position=pos, is_swc=True, immediate_restart=imm)
                        )
                    elif sleaf == "RteExclusiveAreaImplementation":
                        ea_ref_v = sub.reference_values.get("RteExclusiveAreaRef")
                        ea_name = _ar_leaf(ea_ref_v.value_ref if ea_ref_v else None) or sub.short_name
                        mech_p = sub.parameter_values.get("RteExclusiveAreaImplMechanism")
                        mech = str(mech_p.value).strip() if mech_p and mech_p.value else "ALL_INTERRUPT_BLOCKING"
                        swc_ea_impls.setdefault(proto_name, {})[ea_name] = ExclusiveAreaModel(
                            short_name=ea_name, mechanism=mech
                        )
                swc_inst_tasks[proto_name] = mapped_tasks

        # Build OsTaskScheduleModel list
        task_schedules: List[OsTaskScheduleModel] = []
        for tname in sorted(task_calls):
            calls = task_calls[tname]
            calls.sort(key=lambda c: (c.position is None, c.position or 0, c.is_swc, c.owner_name, c.symbol))
            tinfo = task_meta.get(tname, {})
            app = task_to_app.get(tname, default_app)
            cid = app_to_core.get(app, cls._core_num(tname, 0))
            if calls or tinfo.get("is_init"):
                task_schedules.append(
                    OsTaskScheduleModel(
                        task_name=tname,
                        os_application=app,
                        core_id=cid,
                        priority=tinfo.get("priority", 0),
                        task_type=tinfo.get("task_type", "BASIC"),
                        is_init_task=bool(tinfo.get("is_init", False)),
                        os_events=list(tinfo.get("events", [])),
                        calls=calls,
                    )
                )

        # Build OsActivationScheduleModel list from RteOsInteraction/RteUsedOsActivation
        os_activations: List[OsActivationScheduleModel] = []
        for top in getattr(rte_cfg, "containers", []) or []:
            if _ar_leaf(getattr(top, "definition_ref", None)) != "RteOsInteraction":
                continue
            for sub in getattr(top, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) != "RteUsedOsActivation":
                    continue
                t_v = sub.reference_values.get("RteActivationOsTaskRef")
                a_v = sub.reference_values.get("RteActivationOsAlarmRef")
                s_v = sub.reference_values.get("RteActivationOsSchTblRef")
                tname = _ar_leaf(t_v.value_ref if t_v else None) or ""
                aname = _ar_leaf(a_v.value_ref if a_v else None)
                sname = _ar_leaf(s_v.value_ref if s_v else None)
                dur_p = sub.parameter_values.get("RteExpectedTickDuration")
                off_p = sub.parameter_values.get("RteExpectedActivationOffset")
                dur_ms = float(dur_p.value) * 1000.0 if dur_p and dur_p.value is not None else 10.0
                off_ms = float(off_p.value) * 1000.0 if off_p and off_p.value is not None else 0.0
                app = (
                    (alarm_to_app.get(aname) if aname else None)
                    or (schtbl_to_app.get(sname) if sname else None)
                    or task_to_app.get(tname)
                    or default_app
                )
                cid = app_to_core.get(app, cls._core_num(app, 0))
                os_activations.append(
                    OsActivationScheduleModel(
                        name=sub.short_name,
                        task_name=tname,
                        os_application=app,
                        core_id=cid,
                        alarm_name=aname,
                        schedule_table_name=sname,
                        offset_ms=off_ms,
                        period_ms=dur_ms,
                        is_bsw=(sub.short_name.startswith("Rte_Al_TE_") and any(m.module_name in sub.short_name for m in bsw_modules)),
                    )
                )

        # Effective data mappings & assembly connectors
        eff_data_maps = cls.resolve_effective_data_mappings(project, swc_index, instance_to_type)
        eff_connectors = cls.resolve_effective_connectors(project, swc_index)

        # Index connectors by provider & requester
        conn_by_req: Dict[Tuple[str, str], AssemblyConnectorData] = {}
        conn_by_prov: Dict[Tuple[str, str], List[AssemblyConnectorData]] = {}
        for ac in eff_connectors:
            if ac.requester_comp_name and ac.requester_port_name:
                conn_by_req[(ac.requester_comp_name, ac.requester_port_name)] = ac
            if ac.provider_comp_name and ac.provider_port_name:
                conn_by_prov.setdefault((ac.provider_comp_name, ac.provider_port_name), []).append(ac)

        # Lookup SWC type by instance name
        inst_swc_map: Dict[str, SwcTypeData] = {
            proto: stype for proto, _ecuc, stype in swc_instances_ecuc if stype is not None
        }

        def _match_com_sig(comp_name: str, swc_type_name: str, port_name: str, direction: str) -> Optional[Dict[str, str]]:
            rec = eff_data_maps.get((comp_name, port_name)) or eff_data_maps.get((swc_type_name, port_name))
            if not rec:
                return None
            explicit_name = rec.get("com_signal", "")
            if explicit_name and explicit_name in com_by_name:
                return com_by_name[explicit_name]
            sys_ref = rec.get("system_signal_ref", "")
            sys_name = rec.get("system_signal_name", "")
            cands = com_by_sys_path.get(sys_ref) or com_by_sys_leaf.get(sys_name) or []
            for cand in cands:
                if not cand["direction"] or cand["direction"] == direction:
                    return cand
            return cands[0] if cands else None

        # Resolve owner OsApplication for each SWC instance
        swc_app_map: Dict[str, Tuple[str, int]] = {}
        for proto_name, _ecuc, _stype in swc_instances_ecuc:
            tlist = swc_inst_tasks.get(proto_name, [])
            chosen_app = next((task_to_app[t] for t in tlist if t in task_to_app), None)
            if not chosen_app:
                core_guess = cls._core_num(proto_name, 0)
                chosen_app = next((a for a, c in app_to_core.items() if c == core_guess), default_app)
            swc_app_map[proto_name] = (chosen_app, app_to_core.get(chosen_app, cls._core_num(chosen_app, 0)))

        # Build SwcComponentModels and collect shared buffers & used data types
        swc_components: List[SwcComponentModel] = []
        shared_buf_map: Dict[str, SwcSharedBufferModel] = {}
        referenced_type_names: Set[str] = set()

        def _resolve_server_runnable(prov_swc: Optional[SwcTypeData], prov_port_name: str, op_name: str) -> str:
            if prov_swc is None:
                return op_name
            for ev in prov_swc.events:
                if ev.event_kind == "OPERATION-INVOKED-EVENT" and (
                    _ar_leaf(ev.port_ref) == prov_port_name or _ar_leaf(ev.operation_ref) == op_name
                ):
                    if ev.runnable_symbol:
                        return ev.runnable_symbol
            # ServiceComponent fallback: check runnables matching operation name
            for r in prov_swc.runnables:
                if r.short_name == op_name or r.symbol == op_name or r.short_name.endswith(f"_{op_name}"):
                    return r.symbol or r.short_name
            return f"{prov_swc.short_name}_{op_name}"

        for proto_name, _ecuc, swc_type in swc_instances_ecuc:
            if swc_type is None:
                continue
            app_name, core_id = swc_app_map.get(proto_name, (default_app, 0))
            reads: List[SwcDataEndpointModel] = []
            writes: List[SwcDataEndpointModel] = []
            calls: List[SwcClientCallModel] = []
            mode_points: List[SwcModePointModel] = []

            for port in sorted(swc_type.ports.values(), key=lambda p: p.short_name):
                iface = swc_index.interfaces_by_path.get(port.interface_ref.strip().rstrip("/")) if port.interface_ref else None
                if iface is None:
                    continue

                if iface.kind == "SR":
                    direction = "TX" if port.direction == "P" else "RX"
                    com_entry = _match_com_sig(proto_name, swc_type.short_name, port.short_name, direction)

                    for de_name, de in sorted(iface.data_elements.items()):
                        c_type = swc_index.resolve_c_type_name(de.type_ref, "uint8")
                        dt_obj = swc_index.resolve_impl_type(de.type_ref)
                        if dt_obj is not None and dt_obj.short_name not in _STD_PRIMITIVE_TYPES:
                            referenced_type_names.add(dt_obj.short_name)
                        is_arr = bool(dt_obj is not None and dt_obj.category == "ARRAY")
                        init_lit = cls._format_c_init_literal(port.init_values.get(de_name), c_type)

                        binding_kind = "UNCONNECTED"
                        shared_var = ""
                        com_sig_name = ""
                        com_sig_macro = ""

                        if com_entry is not None:
                            binding_kind = "COM"
                            com_sig_name = com_entry["name"]
                            com_sig_macro = com_entry["macro"]
                        elif port.direction == "P" and (proto_name, port.short_name) in conn_by_prov:
                            binding_kind = "INTER_SWC"
                            shared_var = f"Rte_{proto_name}_{port.short_name}_{de_name}"
                            shared_buf_map.setdefault(
                                shared_var,
                                SwcSharedBufferModel(
                                    var_name=shared_var,
                                    c_type=c_type,
                                    init_value=init_lit,
                                    owner_os_application=app_name,
                                ),
                            )
                        elif port.direction == "R" and (proto_name, port.short_name) in conn_by_req:
                            ac = conn_by_req[(proto_name, port.short_name)]
                            prov_c = ac.provider_comp_name
                            prov_p = ac.provider_port_name
                            prov_swc = inst_swc_map.get(prov_c) or swc_index.swc_types_by_name.get(prov_c)
                            prov_de = de_name
                            if prov_swc and prov_p in prov_swc.ports:
                                p_iface = swc_index.interfaces_by_path.get(prov_swc.ports[prov_p].interface_ref.strip().rstrip("/"))
                                if p_iface and prov_de not in p_iface.data_elements and p_iface.data_elements:
                                    prov_de = next(iter(p_iface.data_elements))
                            binding_kind = "INTER_SWC"
                            shared_var = f"Rte_{prov_c}_{prov_p}_{prov_de}"
                            prov_app = swc_app_map.get(prov_c, (app_name, core_id))[0]
                            shared_buf_map.setdefault(
                                shared_var,
                                SwcSharedBufferModel(
                                    var_name=shared_var,
                                    c_type=c_type,
                                    init_value=init_lit,
                                    owner_os_application=prov_app,
                                ),
                            )

                        ep = SwcDataEndpointModel(
                            component_name=proto_name,
                            swc_type_name=swc_type.short_name,
                            port_name=port.short_name,
                            data_element_name=de_name,
                            direction=direction,
                            c_type=c_type,
                            init_value=init_lit,
                            binding_kind=binding_kind,
                            com_signal_name=com_sig_name,
                            com_signal_macro=com_sig_macro,
                            shared_var_name=shared_var,
                            is_array=is_arr,
                        )
                        if direction == "TX":
                            writes.append(ep)
                        else:
                            reads.append(ep)

                elif iface.kind == "CS" and port.direction == "R":
                    ac = conn_by_req.get((proto_name, port.short_name))
                    prov_c = ac.provider_comp_name if ac else ""
                    prov_p = ac.provider_port_name if ac else ""
                    prov_swc = (inst_swc_map.get(prov_c) or swc_index.swc_types_by_name.get(prov_c)) if prov_c else None
                    port_def_args: List[str] = []
                    if prov_swc and prov_p in prov_swc.ports:
                        for vt_ref, val in prov_swc.ports[prov_p].port_arg_values:
                            vt_type = swc_index.resolve_c_type_name(vt_ref, "uint8")
                            port_def_args.append(cls._format_c_init_literal(val, vt_type))

                    for op_name, op in sorted(iface.operations.items()):
                        args_m: List[SwcClientCallArgModel] = []
                        for arg in op.arguments:
                            at = swc_index.resolve_c_type_name(arg.type_ref, "uint8")
                            dt_obj = swc_index.resolve_impl_type(arg.type_ref)
                            if dt_obj is not None and dt_obj.short_name not in _STD_PRIMITIVE_TYPES:
                                referenced_type_names.add(dt_obj.short_name)
                            args_m.append(SwcClientCallArgModel(name=arg.name, c_type=at, direction=arg.direction))
                        server_sym = _resolve_server_runnable(prov_swc, prov_p, op_name) if ac else ""
                        calls.append(
                            SwcClientCallModel(
                                component_name=proto_name,
                                swc_type_name=swc_type.short_name,
                                port_name=port.short_name,
                                operation_name=op_name,
                                connected=ac is not None and bool(server_sym),
                                server_component_name=prov_c,
                                server_port_name=prov_p,
                                server_symbol=server_sym,
                                port_defined_args=list(port_def_args),
                                arguments=args_m,
                                has_errors=op.has_errors,
                            )
                        )

                elif iface.kind == "MODE":
                    mg = swc_index.mode_groups_by_path.get(iface.mode_group_ref.strip().rstrip("/"))
                    mode_points.append(
                        SwcModePointModel(
                            component_name=proto_name,
                            swc_type_name=swc_type.short_name,
                            port_name=port.short_name,
                            mode_group_name=iface.mode_group_name or port.short_name,
                            kind="SWITCH" if port.direction == "P" else "ACCESS",
                            initial_mode=mg.initial_mode if mg else "",
                            modes=list(mg.modes) if mg else [],
                        )
                    )

            # Map server runnable symbols -> C/S signature from OPERATION-INVOKED-EVENTs
            srv_sigs: Dict[str, Tuple[str, List[str], List[SwcClientCallArgModel]]] = {}
            for ev in swc_type.events:
                if ev.event_kind != "OPERATION-INVOKED-EVENT":
                    continue
                p_name = _ar_leaf(ev.port_ref)
                op_name = _ar_leaf(ev.operation_ref)
                r_sym = ev.runnable_symbol or op_name
                p_obj = swc_type.ports.get(p_name)
                if p_obj is None:
                    continue
                p_iface = swc_index.interfaces_by_path.get(p_obj.interface_ref.strip().rstrip("/")) if p_obj.interface_ref else None
                if p_iface is None or op_name not in p_iface.operations:
                    continue
                op_def = p_iface.operations[op_name]
                p_arg_types: List[str] = [
                    swc_index.resolve_c_type_name(vt_ref, "uint8")
                    for vt_ref, _val in p_obj.port_arg_values
                ]
                op_args = [
                    SwcClientCallArgModel(
                        name=arg.name,
                        c_type=swc_index.resolve_c_type_name(arg.type_ref, "uint8"),
                        direction=arg.direction,
                    )
                    for arg in op_def.arguments
                ]
                ret_t = "Std_ReturnType" if op_def.has_errors else "void"
                srv_sigs[r_sym] = (ret_t, p_arg_types, op_args)

            runnable_models = []
            for r in swc_type.runnables:
                sym = r.symbol or r.short_name
                if sym in srv_sigs:
                    ret_t, p_arg_t, op_a = srv_sigs[sym]
                    runnable_models.append(
                        SchedulableEntityModel(
                            short_name=r.short_name,
                            entry_name=sym,
                            return_type=ret_t,
                            port_arg_types=p_arg_t,
                            arguments=op_a,
                        )
                    )
                else:
                    runnable_models.append(SchedulableEntityModel(short_name=r.short_name, entry_name=sym))
            ea_impls = swc_ea_impls.get(proto_name, {})
            eas = [
                ea_impls.get(ea_name, ExclusiveAreaModel(short_name=ea_name))
                for ea_name in sorted(set(swc_type.exclusive_areas.values()) | set(ea_impls.keys()))
            ]
            mem_hdr = f"{swc_type.short_name}_MemMap.h" if (
                swc_type.short_name in memmap_mods or proto_name in memmap_mods or not swc_type.is_service or True
            ) else "MemMap.h"

            swc_components.append(
                SwcComponentModel(
                    instance_name=proto_name,
                    swc_type_name=swc_type.short_name,
                    is_service=swc_type.is_service,
                    os_application=app_name,
                    core_id=core_id,
                    memmap_header=mem_hdr,
                    reads=reads,
                    writes=writes,
                    calls=calls,
                    mode_points=mode_points,
                    runnables=runnable_models,
                    exclusive_areas=eas,
                )
            )

        rte_type_defs = cls._collect_sorted_rte_types(swc_index, referenced_type_names)
        shared_buffers = sorted(shared_buf_map.values(), key=lambda b: b.var_name)
        swc_components.sort(key=lambda s: (s.swc_type_name, s.instance_name))
        return swc_components, task_schedules, os_activations, rte_type_defs, shared_buffers

    @classmethod
    def _collect_sorted_rte_types(
        cls,
        swc_index: SwcSystemIndex,
        seed_names: Set[str],
    ) -> List[RteTypeDefEntry]:
        """Collect and topologically sort needed ``IMPLEMENTATION-DATA-TYPE`` typedefs."""
        if not swc_index.types_by_path:
            return []

        needed: Dict[str, SwcDataType] = {}

        def _visit(dt: Optional[SwcDataType]) -> None:
            if dt is None or dt.category == "APPLICATION" or dt.short_name in _STD_PRIMITIVE_TYPES:
                return
            if dt.short_name.startswith("dtRef_"):
                return
            if dt.short_name in needed:
                return
            needed[dt.short_name] = dt
            if dt.impl_type_ref:
                _visit(swc_index.resolve_impl_type(dt.impl_type_ref))
            if dt.element_type_ref:
                _visit(swc_index.resolve_impl_type(dt.element_type_ref))
            for f in dt.fields:
                _visit(swc_index.resolve_impl_type(f.type_ref))

        for name in sorted(seed_names):
            _visit(swc_index.types_by_name.get(name))

        # Also include user-defined Developer STRUCTURE / ARRAY / VALUE / TYPE_REFERENCE definitions
        for dt in swc_index.types_by_path.values():
            if dt.category in ("VALUE", "TYPE_REFERENCE", "ARRAY", "STRUCTURE"):
                if "Developer/" in dt.source_file or "ServiceComponents/" in dt.source_file:
                    _visit(dt)

        # Topological sort: dependencies before dependents
        ordered: List[RteTypeDefEntry] = []
        visiting: Set[str] = set()
        done: Set[str] = set()

        def _emit(dt: SwcDataType) -> None:
            if dt.short_name in done or dt.short_name in visiting:
                return
            visiting.add(dt.short_name)
            deps: List[SwcDataType] = []
            for ref in [dt.impl_type_ref, dt.element_type_ref] + [f.type_ref for f in dt.fields]:
                if ref:
                    dep_dt = swc_index.resolve_impl_type(ref)
                    if dep_dt and dep_dt.short_name in needed:
                        deps.append(dep_dt)
            for dep_dt in deps:
                _emit(dep_dt)

            base_c = dt.native_decl or (swc_index.resolve_c_type_name(dt.impl_type_ref, "uint8") if dt.impl_type_ref else "uint8")
            if dt.category == "ARRAY":
                elem_c = swc_index.resolve_c_type_name(dt.element_type_ref, "uint8")
                ordered.append(
                    RteTypeDefEntry(
                        name=dt.short_name,
                        category="ARRAY",
                        c_type=elem_c,
                        array_size=dt.array_size or 1,
                    )
                )
            elif dt.category in ("STRUCTURE", "UNION"):
                fields_c = [
                    (f.name, swc_index.resolve_c_type_name(f.type_ref, "uint8"), f.array_size)
                    for f in dt.fields
                ]
                ordered.append(
                    RteTypeDefEntry(
                        name=dt.short_name,
                        category=dt.category,
                        c_type=dt.short_name,
                        fields=fields_c,
                    )
                )
            else:
                ordered.append(
                    RteTypeDefEntry(
                        name=dt.short_name,
                        category=dt.category,
                        c_type=base_c or "uint8",
                        enum_literals=list(dt.compu_literals),
                    )
                )
            visiting.discard(dt.short_name)
            done.add(dt.short_name)

        for dt_name in sorted(needed):
            _emit(needed[dt_name])

        return ordered
