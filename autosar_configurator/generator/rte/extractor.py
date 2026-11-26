"""Cross-model synthesizer producing :class:`RteProjectModel` for Phase 1 generation."""

from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

from ...core import project_paths
from ...core.model.ecuc_paths import strip_ecuc_prefixes
from .ib_parser import BswIbImplData, BswIbIndex, BswIbModuleData
from .model import (
    BswModuleSchmModel,
    ExclusiveAreaModel,
    RteGenerationReport,
    RteMeta,
    RteProjectModel,
    SchedulableEntityModel,
)

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
    def extract(cls, project: Any) -> Tuple[Optional[RteProjectModel], RteGenerationReport]:
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
        ib_index = cls._load_ib_index(project)
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
                ib_index=ib_index,
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
        model = RteProjectModel(
            meta=meta,
            bsw_modules=bsw_modules,
            os_cores=os_cores,
            os_applications=os_apps,
            has_com=("Com" in managers and managers["Com"].configuration is not None),
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
