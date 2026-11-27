"""Pure-Python domain service aggregating and editing AUTOSAR System Services & Diagnostics."""

from typing import Any, Dict, Iterable, List, Optional, Set, Tuple

from ...generator.rte.workbench_service import restore_rte_config, snapshot_rte_config
from ..config_manager import PreLockedError
from ..model.configuration_model import EcucContainerValue, EcucReferenceValue
from ..model.ecuc_paths import normalize_ecuc_path, strip_ecuc_prefixes
from .models import (
    BswMActionListItemRow,
    BswMActionListRow,
    BswMModeGroupRow,
    BswMModePortRow,
    BswMRuleRow,
    CddPlatformModuleRow,
    DcmDidRoutineRow,
    DcmSecurityRow,
    DcmServiceRow,
    DcmSessionRow,
    DetGeneralInfo,
    DiagChannelRow,
    EcuMGeneralInfo,
    EcuMInitItemRow,
    EcuMModeCauseRow,
    EcuMWakeupSourceRow,
    ModuleDetFlagRow,
    OsCoreSummaryRow,
    OsGeneralInfo,
    OsIsrRow,
    OsSyncResourceRow,
    OsTaskRow,
    OsTimingRow,
    ServiceDiagnostic,
)

SYSTEM_SERVICE_MODULES: Tuple[str, ...] = (
    "EcuM",
    "BswM",
    "Os",
    "Dcm",
    "CanTp",
    "Det",
    "ComM",
    "PduR",
    "CanIf",
    "EcuC",
    "Crc",
    "VX1000",
    "vBRS",
    "vBaseEnv",
    "vSet",
)

PRIMARY_SERVICE_MODULES: Tuple[str, ...] = ("EcuM", "BswM", "Os", "Dcm", "CanTp", "Det")

ANCHOR_PRIORITY: Tuple[str, ...] = ("BswM", "EcuM", "Os", "Dcm", "CanTp", "Det")

ECUM_INIT_LIST_NAMES: Tuple[str, ...] = (
    "EcuMDriverInitListZero",
    "EcuMDriverInitListOne",
    "EcuMDriverInitListTwo",
    "EcuMDriverInitListThree",
)

ECUM_PSEUDO_MODULES: Set[str] = {"Code", "User", "Brs"}

PLATFORM_MODULE_NAMES: Set[str] = {
    "VX1000",
    "vBRS",
    "vBaseEnv",
    "vSet",
    "Crc",
    "Det",
    "VTTMemMap",
    "vLinkGen",
}

STANDARD_BSW_MCAL_MODULES: Set[str] = {
    "Adc",
    "BswM",
    "Can",
    "CanIf",
    "CanNm",
    "CanSM",
    "CanTp",
    "CanTrcv",
    "Com",
    "ComM",
    "Crc",
    "Dcm",
    "Dem",
    "Det",
    "Dio",
    "EcuC",
    "EcuM",
    "Fee",
    "Fls",
    "Gpt",
    "Icu",
    "Lin",
    "Mcu",
    "MemIf",
    "MemMap",
    "Nm",
    "NvM",
    "Os",
    "PduR",
    "Port",
    "Pwm",
    "Resource",
    "Rte",
    "Spi",
    "Wdg",
    "WdgIf",
    "WdgM",
}

UDS_SID_NAMES: Dict[int, str] = {
    0x10: "DiagnosticSessionControl",
    0x11: "ECUReset",
    0x14: "ClearDiagnosticInformation",
    0x19: "ReadDTCInformation",
    0x22: "ReadDataByIdentifier",
    0x23: "ReadMemoryByAddress",
    0x27: "SecurityAccess",
    0x28: "CommunicationControl",
    0x2E: "WriteDataByIdentifier",
    0x2F: "InputOutputControlByIdentifier",
    0x31: "RoutineControl",
    0x34: "RequestDownload",
    0x36: "TransferData",
    0x37: "RequestTransferExit",
    0x3E: "TesterPresent",
    0x85: "ControlDTCSetting",
}

_BSWM_SWITCH_TO_MODULE: Dict[str, str] = {
    "BswMCanSMEnabled": "CanSM",
    "BswMComMEnabled": "ComM",
    "BswMDcmEnabled": "Dcm",
    "BswMEcuMEnabled": "EcuM",
    "BswMCanNmEnabled": "CanNm",
    "BswMNvMEnabled": "NvM",
    "BswMWdgMEnabled": "WdgM",
    "BswMDemEnabled": "Dem",
    "BswMEthIfEnabled": "EthIf",
    "BswMDoIPEnabled": "DoIP",
    "BswMLinSMEnabled": "LinSM",
}

_BSWM_OP_SYMBOLS: Dict[str, str] = {
    "BSWM_AND": "AND",
    "BSWM_OR": "OR",
    "BSWM_XOR": "XOR",
    "BSWM_NAND": "NAND",
}


def _ar_leaf(path: Optional[str]) -> str:
    if not path:
        return ""
    return path.strip().rstrip("/").rsplit("/", 1)[-1]


def _parse_int(raw: Any) -> Optional[int]:
    if raw is None or isinstance(raw, bool):
        return None
    text = str(raw).strip()
    if not text:
        return None
    try:
        return int(text, 0)
    except ValueError:
        try:
            return int(float(text))
        except ValueError:
            return None


def _parse_float(raw: Any) -> Optional[float]:
    if raw is None or isinstance(raw, bool):
        return None
    text = str(raw).strip()
    if not text:
        return None
    try:
        return float(text)
    except ValueError:
        return None


def _parse_bool(raw: Any, default: bool = False) -> bool:
    if isinstance(raw, bool):
        return raw
    if isinstance(raw, (int, float)):
        return bool(raw)
    if raw is None:
        return default
    text = str(raw).strip().lower()
    if text in ("true", "1", "yes", "on"):
        return True
    if text in ("false", "0", "no", "off"):
        return False
    return default


def _iter_containers_by_def(root: Any, def_leaf: str) -> List[EcucContainerValue]:
    if root is None:
        return []
    found: List[EcucContainerValue] = []

    def _walk(c: EcucContainerValue) -> None:
        if _ar_leaf(getattr(c, "definition_ref", None)) == def_leaf:
            found.append(c)
        for sub in getattr(c, "sub_containers", []) or []:
            _walk(sub)

    if isinstance(root, EcucContainerValue):
        seeds = getattr(root, "sub_containers", []) or []
    else:
        seeds = getattr(root, "containers", []) or []
    for top in seeds:
        _walk(top)
    return found


def _first_container_by_def(cfg: Any, def_leaf: str) -> Optional[EcucContainerValue]:
    items = _iter_containers_by_def(cfg, def_leaf)
    return items[0] if items else None


def _get_all_refs(container: Optional[EcucContainerValue], ref_name: str) -> List[EcucReferenceValue]:
    if container is None:
        return []
    refs: List[EcucReferenceValue] = []
    single = getattr(container, "reference_values", {}).get(ref_name)
    if single is not None:
        refs.append(single)
    multi = getattr(container, "multi_reference_values", {}).get(ref_name, []) or []
    refs.extend(multi)
    return refs


def _ref_path(container: Optional[EcucContainerValue], ref_name: str) -> str:
    for r in _get_all_refs(container, ref_name):
        if r.value_ref:
            return str(r.value_ref).strip()
    return ""


def _ref_leaf(container: Optional[EcucContainerValue], ref_name: str) -> str:
    return _ar_leaf(_ref_path(container, ref_name))


def _param_raw(container: Optional[EcucContainerValue], param_name: str) -> Any:
    if container is None:
        return None
    pv = container.parameter_values.get(param_name)
    return None if pv is None else pv.value


def _param_str(container: Optional[EcucContainerValue], param_name: str, default: str = "") -> str:
    raw = _param_raw(container, param_name)
    if raw is None:
        return default
    text = str(raw).strip()
    return text if text else default


def _param_int(container: Optional[EcucContainerValue], param_name: str) -> Optional[int]:
    return _parse_int(_param_raw(container, param_name))


def _param_float(container: Optional[EcucContainerValue], param_name: str) -> Optional[float]:
    return _parse_float(_param_raw(container, param_name))


def _param_bool(container: Optional[EcucContainerValue], param_name: str, default: bool = False) -> bool:
    raw = _param_raw(container, param_name)
    if raw is None:
        return default
    return _parse_bool(raw, default=default)


def _container_path(module_name: str, container: EcucContainerValue, known: Optional[Iterable[str]] = None) -> str:
    try:
        p = container.get_path()
        if p:
            stripped = strip_ecuc_prefixes(p, known_modules=set(known or (module_name,)))
            if stripped.startswith(f"/{module_name}/"):
                return stripped
            return f"/{module_name}{stripped}" if stripped.startswith("/") else f"/{module_name}/{stripped}"
    except Exception:
        pass
    return f"/{module_name}/{container.short_name}"


def _is_cdd_module(module_name: str, mgr: Any = None) -> bool:
    if module_name.lower().startswith("cdd"):
        return True
    mdef = getattr(mgr, "module_def", None) if mgr is not None else None
    cfg = getattr(mgr, "configuration", None) if mgr is not None else None
    dref = str(getattr(mdef, "definition_ref", "") or getattr(cfg, "definition_ref", "") or "").lower()
    return "cdd" in dref.split("/")[-1:]


class SystemServicesWorkbenchService:
    """Qt-free domain service for EcuM, BswM, Os, Dcm+CanTp diagnostics, and Det/CDD."""

    def __init__(self, project: Any) -> None:
        self.project = project

    # ------------------------------------------------------------------
    # Module lookup, path normalization, edit & snapshot helpers
    # ------------------------------------------------------------------

    def _managers(self) -> Dict[str, Any]:
        return getattr(self.project, "module_managers", {}) or {}

    def _known_module_names(self) -> Set[str]:
        names = set(SYSTEM_SERVICE_MODULES) | set(self._managers().keys())
        for mod, mgr in self._managers().items():
            cfg = getattr(mgr, "configuration", None)
            sn = getattr(cfg, "short_name", None) if cfg is not None else None
            if sn:
                names.add(sn)
            names.add(mod)
        return names

    def _mgr(self, module_name: str) -> Optional[Any]:
        mgr = self._managers().get(module_name)
        if mgr is not None and getattr(mgr, "configuration", None) is not None:
            return mgr
        return None

    def _cfg(self, module_name: str) -> Optional[Any]:
        mgr = self._mgr(module_name)
        return getattr(mgr, "configuration", None) if mgr is not None else None

    def loaded_service_modules(self) -> List[str]:
        mods = [m for m in SYSTEM_SERVICE_MODULES if self._cfg(m) is not None]
        for m, mgr in sorted(self._managers().items()):
            if m not in mods and getattr(mgr, "configuration", None) is not None and _is_cdd_module(m, mgr):
                mods.append(m)
        return mods

    def has_service_modules(self) -> bool:
        return any(self._cfg(m) is not None for m in PRIMARY_SERVICE_MODULES)

    @staticmethod
    def anchor_module_for_project(project: Any) -> Optional[str]:
        managers = getattr(project, "module_managers", {}) or {}
        for mod in ANCHOR_PRIORITY:
            mgr = managers.get(mod)
            if mgr is not None and getattr(mgr, "configuration", None) is not None:
                return mod
        return None

    def _snapshot_module_names(self) -> List[str]:
        names = [m for m in self._managers().keys() if m in SYSTEM_SERVICE_MODULES or _is_cdd_module(m, self._mgr(m))]
        return sorted(set(names))

    def capture_snapshots(self) -> Dict[str, Any]:
        """Capture snapshots across all loaded System Services, Diagnostics, and CDD modules."""
        snaps: Dict[str, Any] = {}
        for mod in self._snapshot_module_names():
            cfg = self._cfg(mod)
            if cfg is not None:
                snaps[mod] = snapshot_rte_config(cfg)
        return snaps

    def restore_snapshots(self, snapshots: Dict[str, Any]) -> None:
        """Restore captured module snapshots and re-resolve cross-module references."""
        if not snapshots:
            return
        for mod, snap in snapshots.items():
            cfg = self._cfg(mod)
            if cfg is not None and snap is not None:
                restore_rte_config(cfg, snap, project=None)
        self._refresh_project_references()

    def _module_base_def(self, module_name: str) -> str:
        mgr = self._mgr(module_name)
        if mgr is not None:
            mdef = getattr(mgr, "module_def", None)
            cfg = getattr(mgr, "configuration", None)
            raw = (
                getattr(mdef, "ar_path", None)
                or getattr(mdef, "definition_ref", None)
                or getattr(cfg, "definition_ref", None)
            )
            if raw:
                return str(raw).rstrip("/")
        return f"/AUTOSAR/EcucDefs/{module_name}"

    def _container_ref_path(self, module_name: str, container: EcucContainerValue) -> str:
        sub_path = _container_path(module_name, container, self._known_module_names()).lstrip("/")
        if sub_path.startswith(f"{module_name}/"):
            sub_path = sub_path[len(module_name) + 1:]
        proj_type = getattr(self.project, "project_type", None)
        type_name = getattr(proj_type, "name", "")
        if type_name == "EB_TRESOS":
            cfg_sn = getattr(self._cfg(module_name), "short_name", None) or module_name
            return f"/{module_name}/{cfg_sn}/{sub_path}"
        return f"/ActiveEcuC/{module_name}/{sub_path}"

    def _check_editable(self, module_name: str, instance: Any, prop: Optional[str] = None) -> None:
        mgr = self._mgr(module_name)
        checker = getattr(mgr, "check_editable", None) if mgr is not None else None
        if callable(checker):
            checker(instance, prop)

    def _mark_modified(self, module_name: str) -> None:
        cfg = self._cfg(module_name)
        if cfg is not None:
            cfg.is_modified = True
        if self.project is not None and hasattr(self.project, "is_modified"):
            self.project.is_modified = True

    def _set_param(
        self,
        module_name: str,
        container: EcucContainerValue,
        name: str,
        value: Any,
        dest_type: str,
        *,
        def_path: Optional[str] = None,
    ) -> None:
        self._check_editable(module_name, container, name)
        dref = def_path or f"{(container.definition_ref or self._module_base_def(module_name)).rstrip('/')}/{name}"
        container.set_parameter_value(name, value, dref)
        container.parameter_values[name].dest_type = dest_type
        self._mark_modified(module_name)

    def _set_ref(
        self,
        module_name: str,
        container: EcucContainerValue,
        name: str,
        value_ref: str,
        *,
        dest_type: str = "ECUC-REFERENCE-DEF",
        value_ref_dest: str = "ECUC-CONTAINER-VALUE",
        def_path: Optional[str] = None,
    ) -> None:
        self._check_editable(module_name, container, name)
        dref = def_path or f"{(container.definition_ref or self._module_base_def(module_name)).rstrip('/')}/{name}"
        container.set_reference_value(
            name,
            value_ref,
            dref,
            dest_type=dest_type,
            value_ref_dest=value_ref_dest,
        )
        self._mark_modified(module_name)

    def _refresh_project_references(self) -> None:
        if self.project is None:
            return
        for attr in ("resolve_all_references", "build_reverse_reference_index"):
            fn = getattr(self.project, attr, None)
            if callable(fn):
                try:
                    if attr == "resolve_all_references":
                        fn(force=True)
                    else:
                        fn()
                except Exception:
                    pass

    def _build_container_index(self) -> Dict[str, EcucContainerValue]:
        """Index all loaded containers by raw and prefix-stripped ECUC paths."""
        known = self._known_module_names()
        idx: Dict[str, EcucContainerValue] = {}
        for mod_name, mgr in self._managers().items():
            cfg = getattr(mgr, "configuration", None)
            if cfg is None:
                continue

            def _walk(c: EcucContainerValue) -> None:
                raw = normalize_ecuc_path(c.get_path())
                if raw:
                    idx[raw] = c
                    idx[strip_ecuc_prefixes(raw, known_modules=known)] = c
                norm_c = _container_path(mod_name, c, known)
                if norm_c:
                    idx[norm_c] = c
                for sub in getattr(c, "sub_containers", []) or []:
                    _walk(sub)

            for top in getattr(cfg, "containers", []) or []:
                _walk(top)
        return idx

    def _resolve_ref(
        self,
        ref_value: Any,
        container_index: Dict[str, EcucContainerValue],
    ) -> Optional[EcucContainerValue]:
        if isinstance(ref_value, EcucReferenceValue):
            if getattr(ref_value, "target", None) is not None and not getattr(
                ref_value.target, "_is_module_root_proxy", False
            ):
                return ref_value.target
            raw_path = ref_value.value_ref
        else:
            raw_path = str(ref_value or "")
        raw_path = raw_path.strip()
        if not raw_path:
            return None
        norm = normalize_ecuc_path(raw_path)
        if norm in container_index:
            return container_index[norm]
        stripped = strip_ecuc_prefixes(norm, known_modules=self._known_module_names())
        if stripped in container_index:
            return container_index[stripped]
        get_inst = getattr(self.project, "get_instance_by_path", None)
        if callable(get_inst):
            try:
                found = get_inst(raw_path)
                if found is not None and not getattr(found, "_is_module_root_proxy", False):
                    return found
            except Exception:
                pass
        return None

    def _norm_key(self, raw_path: Optional[str]) -> str:
        if not raw_path:
            return ""
        return strip_ecuc_prefixes(normalize_ecuc_path(str(raw_path)), known_modules=self._known_module_names())

    # ------------------------------------------------------------------
    # Tab 1: EcuM
    # ------------------------------------------------------------------

    def get_ecum_summary(self) -> EcuMGeneralInfo:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return EcuMGeneralInfo(loaded=False)

        gen = _first_container_by_def(ecum_cfg, "EcuMGeneral")
        flex_gen = _first_container_by_def(ecum_cfg, "EcuMFlexGeneral")
        common = _first_container_by_def(ecum_cfg, "EcuMCommonConfiguration")
        flex = _first_container_by_def(ecum_cfg, "EcuMFlexConfiguration")
        shutdown_t = _first_container_by_def(ecum_cfg, "EcuMDefaultShutdownTarget")
        known = self._known_module_names()

        part_refs = [_ar_leaf(r.value_ref) for r in _get_all_refs(flex, "EcuMPartitionRef") if r.value_ref]
        return EcuMGeneralInfo(
            loaded=True,
            main_function_period=_param_float(gen, "EcuMMainFunctionPeriod"),
            dev_error_detect=_param_bool(gen, "EcuMDevErrorDetect", False),
            slave_core_handling=_param_bool(gen, "EcuMSlaveCoreHandling", False),
            include_dem=_param_bool(gen, "EcuMIncludeDem", False),
            include_det=_param_bool(gen, "EcuMIncludeDet", False),
            alarm_clock_present=_param_bool(flex_gen, "EcuMAlarmClockPresent", False),
            default_shutdown_state=_param_str(shutdown_t, "EcuMDefaultState", ""),
            default_app_mode_ref=_ref_path(common, "EcuMDefaultAppMode"),
            os_resource_ref=_ref_path(common, "EcuMOSResource"),
            normal_mcu_mode_ref=_ref_path(flex, "EcuMNormalMcuModeRef"),
            flex_module_cfg_ref=_ref_path(flex, "EcuMFlexModuleConfigurationRef"),
            partition_refs=part_refs,
            general_path=_container_path("EcuM", gen, known) if gen is not None else "",
            shutdown_target_path=_container_path("EcuM", shutdown_t, known) if shutdown_t is not None else "",
            common_cfg_path=_container_path("EcuM", common, known) if common is not None else "",
            flex_cfg_path=_container_path("EcuM", flex, known) if flex is not None else "",
        )

    def update_ecum_general(
        self,
        *,
        main_function_period: Optional[float] = None,
        dev_error_detect: Optional[bool] = None,
        slave_core_handling: Optional[bool] = None,
        default_shutdown_state: Optional[str] = None,
    ) -> bool:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return False
        changed = False
        gen = _first_container_by_def(ecum_cfg, "EcuMGeneral")
        if gen is not None:
            if main_function_period is not None:
                self._set_param("EcuM", gen, "EcuMMainFunctionPeriod", float(main_function_period), "ECUC-FLOAT-PARAM-DEF")
                changed = True
            if dev_error_detect is not None:
                self._set_param("EcuM", gen, "EcuMDevErrorDetect", bool(dev_error_detect), "ECUC-BOOLEAN-PARAM-DEF")
                changed = True
            if slave_core_handling is not None:
                self._set_param("EcuM", gen, "EcuMSlaveCoreHandling", bool(slave_core_handling), "ECUC-BOOLEAN-PARAM-DEF")
                changed = True

        shutdown_t = _first_container_by_def(ecum_cfg, "EcuMDefaultShutdownTarget")
        if default_shutdown_state is not None and shutdown_t is not None:
            self._set_param(
                "EcuM", shutdown_t, "EcuMDefaultState", default_shutdown_state.strip(), "ECUC-ENUMERATION-PARAM-DEF"
            )
            changed = True
        return changed

    def _ecum_module_is_loaded(self, module_id: str) -> Tuple[bool, bool]:
        if not module_id:
            return True, False
        if module_id in ECUM_PSEUDO_MODULES:
            return True, True
        loaded_keys = set(self._managers().keys())
        if module_id in loaded_keys:
            return True, False
        # Some Vector drivers/wrappers carry an 'If' or vendor suffix in init tables (e.g. VX1000If -> VX1000)
        for lk in loaded_keys:
            if module_id == f"{lk}If" or module_id.startswith(f"{lk}_"):
                return True, False
        return False, False

    def list_ecum_init_items(self) -> List[EcuMInitItemRow]:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[EcuMInitItemRow] = []
        for list_name in ECUM_INIT_LIST_NAMES:
            list_c = _first_container_by_def(ecum_cfg, list_name)
            if list_c is None:
                continue
            for idx, item in enumerate(list_c.sub_containers or []):
                if _ar_leaf(getattr(item, "definition_ref", None)) != "EcuMDriverInitItem":
                    continue
                mod_id = _param_str(item, "EcuMModuleID", "")
                loaded, is_pseudo = self._ecum_module_is_loaded(mod_id)
                rows.append(
                    EcuMInitItemRow(
                        list_name=list_name,
                        order_index=idx,
                        short_name=item.short_name,
                        module_id=mod_id,
                        service_name=_param_str(item, "EcuMModuleService", ""),
                        header_file=_param_str(item, "EcuMModuleHeader", ""),
                        additional_code=_param_str(item, "EcuMAdditionalInitCode", ""),
                        module_loaded=loaded,
                        is_pseudo_module=is_pseudo,
                        container_path=_container_path("EcuM", item, known),
                    )
                )
        return rows

    def _find_or_create_ecum_init_list(self, list_name: str) -> Optional[EcucContainerValue]:
        if list_name not in ECUM_INIT_LIST_NAMES:
            raise ValueError(f"Unsupported EcuM init list: {list_name}")
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return None
        existing = _first_container_by_def(ecum_cfg, list_name)
        if existing is not None:
            return existing
        common = _first_container_by_def(ecum_cfg, "EcuMCommonConfiguration")
        if common is None:
            return None
        self._check_editable("EcuM", common, None)
        dref = f"{(common.definition_ref or self._module_base_def('EcuM') + '/EcuMConfiguration/EcuMCommonConfiguration').rstrip('/')}/{list_name}"
        list_c = EcucContainerValue(
            short_name=list_name,
            definition_ref=dref,
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        common.add_sub_container(list_c)
        self._mark_modified("EcuM")
        return list_c

    def add_ecum_init_item(
        self,
        list_name: str,
        short_name: str,
        module_id: str,
        service_name: str = "",
        header: str = "",
        additional_code: str = "",
    ) -> EcucContainerValue:
        list_c = self._find_or_create_ecum_init_list(list_name)
        if list_c is None:
            raise RuntimeError("EcuM / EcuMCommonConfiguration is not loaded")
        self._check_editable("EcuM", list_c, None)
        clean_name = short_name.strip() or f"{module_id}_Init"
        if any(s.short_name == clean_name for s in list_c.sub_containers or []):
            raise ValueError(f"Init item '{clean_name}' already exists in {list_name}")
        item_dref = f"{(list_c.definition_ref or '').rstrip('/')}/EcuMDriverInitItem"
        item = EcucContainerValue(
            short_name=clean_name,
            definition_ref=item_dref,
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        list_c.add_sub_container(item)
        self._set_param("EcuM", item, "EcuMModuleID", module_id.strip(), "ECUC-STRING-PARAM-DEF")
        if service_name.strip():
            self._set_param("EcuM", item, "EcuMModuleService", service_name.strip(), "ECUC-STRING-PARAM-DEF")
        if header.strip():
            self._set_param("EcuM", item, "EcuMModuleHeader", header.strip(), "ECUC-STRING-PARAM-DEF")
        if additional_code.strip():
            self._set_param("EcuM", item, "EcuMAdditionalInitCode", additional_code.strip(), "ECUC-STRING-PARAM-DEF")
        self._mark_modified("EcuM")
        return item

    def remove_ecum_init_item(self, list_name: str, short_name: str) -> bool:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return False
        list_c = _first_container_by_def(ecum_cfg, list_name)
        if list_c is None:
            return False
        target = next((s for s in list_c.sub_containers or [] if s.short_name == short_name), None)
        if target is None:
            return False
        self._check_editable("EcuM", list_c, None)
        list_c.remove_sub_container(target)
        if hasattr(self.project, "unregister_container_references"):
            self.project.unregister_container_references(target)
        self._mark_modified("EcuM")
        return True

    def move_ecum_init_item(self, list_name: str, short_name: str, delta: int) -> bool:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None or delta == 0:
            return False
        list_c = _first_container_by_def(ecum_cfg, list_name)
        if list_c is None or not list_c.sub_containers:
            return False
        subs = list_c.sub_containers
        idx = next((i for i, s in enumerate(subs) if s.short_name == short_name), None)
        if idx is None:
            return False
        new_idx = idx + delta
        if not (0 <= new_idx < len(subs)):
            return False
        self._check_editable("EcuM", list_c, None)
        subs[idx], subs[new_idx] = subs[new_idx], subs[idx]
        list_c.mark_modified()
        self._mark_modified("EcuM")
        return True

    def list_ecum_wakeup_sources(self) -> List[EcuMWakeupSourceRow]:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return []
        known = self._known_module_names()
        cidx = self._build_container_index()
        rows: List[EcuMWakeupSourceRow] = []
        for ws in _iter_containers_by_def(ecum_cfg, "EcuMWakeupSource"):
            ch_ref = _ref_path(ws, "EcuMComMChannelRef")
            broken = False
            if ch_ref:
                refs = _get_all_refs(ws, "EcuMComMChannelRef")
                broken = self._resolve_ref(refs[0], cidx) is None if refs else True
            rows.append(
                EcuMWakeupSourceRow(
                    short_name=ws.short_name,
                    wakeup_id=_param_int(ws, "EcuMWakeupSourceId"),
                    polling=_param_bool(ws, "EcuMWakeupSourcePolling", False),
                    validation_timeout=_param_float(ws, "EcuMValidationTimeout"),
                    check_wakeup_timeout=_param_float(ws, "EcuMCheckWakeupTimeout"),
                    comm_channel_ref=ch_ref,
                    comm_channel_name=_ar_leaf(ch_ref),
                    has_broken_ref=broken,
                    container_path=_container_path("EcuM", ws, known),
                )
            )
        return rows

    def update_ecum_wakeup_source(
        self,
        short_name: str,
        *,
        polling: Optional[bool] = None,
        validation_timeout: Optional[float] = None,
        check_wakeup_timeout: Optional[float] = None,
        comm_channel_ref: Optional[str] = None,
    ) -> bool:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return False
        ws = next((c for c in _iter_containers_by_def(ecum_cfg, "EcuMWakeupSource") if c.short_name == short_name), None)
        if ws is None:
            return False
        changed = False
        if polling is not None:
            self._set_param("EcuM", ws, "EcuMWakeupSourcePolling", bool(polling), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        if validation_timeout is not None:
            self._set_param("EcuM", ws, "EcuMValidationTimeout", float(validation_timeout), "ECUC-FLOAT-PARAM-DEF")
            changed = True
        if check_wakeup_timeout is not None:
            self._set_param("EcuM", ws, "EcuMCheckWakeupTimeout", float(check_wakeup_timeout), "ECUC-FLOAT-PARAM-DEF")
            changed = True
        if comm_channel_ref is not None:
            if comm_channel_ref.strip():
                self._set_ref("EcuM", ws, "EcuMComMChannelRef", comm_channel_ref.strip())
            elif "EcuMComMChannelRef" in ws.reference_values:
                self._check_editable("EcuM", ws, "EcuMComMChannelRef")
                del ws.reference_values["EcuMComMChannelRef"]
                self._mark_modified("EcuM")
            changed = True
        if changed:
            self._refresh_project_references()
        return changed

    def list_ecum_reset_and_causes(self) -> List[EcuMModeCauseRow]:
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[EcuMModeCauseRow] = []
        for rm in _iter_containers_by_def(ecum_cfg, "EcuMResetMode"):
            rows.append(
                EcuMModeCauseRow(
                    kind="ResetMode",
                    short_name=rm.short_name,
                    mode_or_cause_id=_param_int(rm, "EcuMResetModeId"),
                    container_path=_container_path("EcuM", rm, known),
                )
            )
        for sc in _iter_containers_by_def(ecum_cfg, "EcuMShutdownCause"):
            rows.append(
                EcuMModeCauseRow(
                    kind="ShutdownCause",
                    short_name=sc.short_name,
                    mode_or_cause_id=_param_int(sc, "EcuMShutdownCauseId"),
                    container_path=_container_path("EcuM", sc, known),
                )
            )
        rows.sort(key=lambda r: (r.kind, r.mode_or_cause_id if r.mode_or_cause_id is not None else 999, r.short_name))
        return rows

    # ------------------------------------------------------------------
    # Tab 2: BswM
    # ------------------------------------------------------------------

    def get_bswm_module_switches(self) -> Dict[str, bool]:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return {}
        gen = _first_container_by_def(bswm_cfg, "BswMGeneral")
        if gen is None:
            return {}
        switches: Dict[str, bool] = {}
        for pname, pv in sorted(gen.parameter_values.items()):
            if pname.endswith("Enabled") or pname == "BswMDevErrorDetect":
                switches[pname] = _parse_bool(pv.value, False)
        return switches

    def set_bswm_module_switch(self, param_name: str, enabled: bool) -> bool:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return False
        gen = _first_container_by_def(bswm_cfg, "BswMGeneral")
        if gen is None:
            return False
        self._set_param("BswM", gen, param_name, bool(enabled), "ECUC-BOOLEAN-PARAM-DEF")
        return True

    def _bswm_arbitration_index(self) -> Dict[str, EcucContainerValue]:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return {}
        idx: Dict[str, EcucContainerValue] = {}
        for leaf in ("BswMRule", "BswMLogicalExpression", "BswMModeCondition", "BswMModeRequestPort", "BswMActionList", "BswMAction"):
            for c in _iter_containers_by_def(bswm_cfg, leaf):
                norm = self._norm_key(_container_path("BswM", c, self._known_module_names()))
                if norm:
                    idx[norm] = c
                raw = normalize_ecuc_path(c.get_path())
                if raw:
                    idx[raw] = c
                    idx[self._norm_key(raw)] = c
        return idx

    def _extract_condition_value_text(self, cond: EcucContainerValue) -> str:
        val_wrap = next(
            (s for s in cond.sub_containers or [] if _ar_leaf(s.definition_ref) == "BswMConditionValue"),
            None,
        )
        if val_wrap is None:
            return _param_str(cond, "BswMConditionValue", "?")
        for choice in val_wrap.sub_containers or []:
            for pname in ("BswMBswRequestedMode", "BswMRequestedMode", "BswMIntModeValue", "BswMReqMode"):
                txt = _param_str(choice, pname, "")
                if txt:
                    return txt
            for pv in choice.parameter_values.values():
                if pv.value is not None and str(pv.value).strip():
                    return str(pv.value).strip()
            for rv in choice.reference_values.values():
                if rv.value_ref:
                    return _ar_leaf(rv.value_ref)
            return choice.short_name
        return "?"

    def _format_bswm_expression(
        self,
        expr_container: Optional[EcucContainerValue],
        bswm_idx: Dict[str, EcucContainerValue],
        visited: Set[str],
    ) -> Tuple[str, bool, bool]:
        """Recursively decode a BswMLogicalExpression or BswMModeCondition -> (text, broken_ref, has_cycle)."""
        if expr_container is None:
            return "<Missing Expression>", True, False

        key = self._norm_key(_container_path("BswM", expr_container, self._known_module_names())) or expr_container.short_name
        if key in visited:
            return "(CYCLE)", False, True

        leaf = _ar_leaf(getattr(expr_container, "definition_ref", None))
        if leaf == "BswMModeCondition":
            mode_ref = _ref_path(expr_container, "BswMConditionMode")
            mode_name = _ar_leaf(mode_ref) or "?"
            mode_broken = bool(mode_ref) and self._resolve_ref(
                _get_all_refs(expr_container, "BswMConditionMode")[0], bswm_idx
            ) is None
            if not mode_ref:
                mode_broken = True
            ctype = _param_str(expr_container, "BswMConditionType", "BSWM_EQUALS")
            op_sym = "!=" if "NOT" in ctype.upper() else "=="
            val_txt = self._extract_condition_value_text(expr_container)
            return f"{mode_name} {op_sym} {val_txt}", mode_broken, False

        if leaf == "BswMLogicalExpression":
            op_raw = _param_str(expr_container, "BswMLogicalOperator", "BSWM_AND")
            op = _BSWM_OP_SYMBOLS.get(op_raw, op_raw.replace("BSWM_", ""))
            arg_refs = _get_all_refs(expr_container, "BswMArgumentRef")
            if not arg_refs:
                return f"{expr_container.short_name} ({op} <empty>)", False, False

            next_visited = set(visited)
            next_visited.add(key)
            parts: List[str] = []
            any_broken = False
            any_cycle = False
            for r in arg_refs:
                target = self._resolve_ref(r, bswm_idx)
                if target is None:
                    parts.append(f"<Broken:{_ar_leaf(r.value_ref)}>")
                    any_broken = True
                else:
                    sub_txt, sub_broken, sub_cycle = self._format_bswm_expression(target, bswm_idx, next_visited)
                    any_broken = any_broken or sub_broken
                    any_cycle = any_cycle or sub_cycle
                    parts.append(f"({sub_txt})" if (" " in sub_txt and (" AND " in sub_txt or " OR " in sub_txt or " XOR " in sub_txt)) else sub_txt)
            if len(parts) == 1:
                return f"{op}({parts[0]})" if op in ("NAND", "NOT") else parts[0], any_broken, any_cycle
            return f" {op} ".join(parts), any_broken, any_cycle

        return expr_container.short_name, False, False

    def list_bswm_rules(self) -> List[BswMRuleRow]:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return []
        known = self._known_module_names()
        bswm_idx = self._bswm_arbitration_index()
        rows: List[BswMRuleRow] = []
        for rule in _iter_containers_by_def(bswm_cfg, "BswMRule"):
            expr_ref = _ref_path(rule, "BswMRuleExpressionRef")
            true_ref = _ref_path(rule, "BswMRuleTrueActionList")
            false_ref = _ref_path(rule, "BswMRuleFalseActionList")

            expr_refs = _get_all_refs(rule, "BswMRuleExpressionRef")
            expr_target = self._resolve_ref(expr_refs[0], bswm_idx) if expr_refs else None
            decoded, expr_broken, has_cycle = self._format_bswm_expression(expr_target, bswm_idx, set())

            true_refs = _get_all_refs(rule, "BswMRuleTrueActionList")
            true_broken = bool(true_ref) and self._resolve_ref(true_refs[0], bswm_idx) is None
            false_refs = _get_all_refs(rule, "BswMRuleFalseActionList")
            false_broken = bool(false_ref) and self._resolve_ref(false_refs[0], bswm_idx) is None

            rows.append(
                BswMRuleRow(
                    short_name=rule.short_name,
                    rule_id=_param_int(rule, "BswMRuleId"),
                    init_state=_param_str(rule, "BswMRuleInitState", "BSWM_FALSE"),
                    nested_only=_param_bool(rule, "BswMNestedExecutionOnly", False),
                    expression_name=_ar_leaf(expr_ref),
                    expression_ref=expr_ref,
                    decoded_expression=decoded,
                    true_action_list=_ar_leaf(true_ref),
                    true_action_list_ref=true_ref,
                    false_action_list=_ar_leaf(false_ref),
                    false_action_list_ref=false_ref,
                    has_broken_ref=expr_broken or true_broken or false_broken,
                    has_cycle=has_cycle,
                    container_path=_container_path("BswM", rule, known),
                )
            )
        rows.sort(key=lambda r: (r.rule_id if r.rule_id is not None else 999999, r.short_name))
        return rows

    def update_bswm_rule(
        self,
        rule_name: str,
        *,
        init_state: Optional[str] = None,
        nested_only: Optional[bool] = None,
        true_action_list: Optional[str] = None,
        false_action_list: Optional[str] = None,
    ) -> bool:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return False
        rule = next((r for r in _iter_containers_by_def(bswm_cfg, "BswMRule") if r.short_name == rule_name), None)
        if rule is None:
            return False

        al_by_name = {c.short_name: c for c in _iter_containers_by_def(bswm_cfg, "BswMActionList")}
        changed = False
        if init_state is not None:
            self._set_param("BswM", rule, "BswMRuleInitState", init_state.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            changed = True
        if nested_only is not None:
            self._set_param("BswM", rule, "BswMNestedExecutionOnly", bool(nested_only), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True

        def _set_al_ref(ref_key: str, val: Optional[str]) -> bool:
            if val is None:
                return False
            clean = val.strip()
            if not clean:
                if ref_key in rule.reference_values:
                    self._check_editable("BswM", rule, ref_key)
                    del rule.reference_values[ref_key]
                    self._mark_modified("BswM")
                    return True
                return False
            target_path = clean
            if "/" not in clean and clean in al_by_name:
                target_path = self._container_ref_path("BswM", al_by_name[clean])
            self._set_ref("BswM", rule, ref_key, target_path)
            return True

        if _set_al_ref("BswMRuleTrueActionList", true_action_list):
            changed = True
        if _set_al_ref("BswMRuleFalseActionList", false_action_list):
            changed = True
        if changed:
            self._refresh_project_references()
        return changed

    def _describe_bswm_action_target(self, target: Optional[EcucContainerValue], raw_ref: str) -> Tuple[str, str]:
        if target is None:
            return "Broken", f"<Broken: {_ar_leaf(raw_ref) or raw_ref}>"
        leaf = _ar_leaf(getattr(target, "definition_ref", None))
        if leaf == "BswMRule":
            return "NestedRule", f"[Rule] {target.short_name}"
        if leaf == "BswMActionList":
            return "ActionList", f"[ActionList] {target.short_name}"
        if leaf == "BswMAction":
            avail = next(
                (s for s in target.sub_containers or [] if _ar_leaf(s.definition_ref) == "BswMAvailableActions"),
                None,
            )
            if avail is not None and avail.sub_containers:
                choice = avail.sub_containers[0]
                cleaf = _ar_leaf(getattr(choice, "definition_ref", None)) or choice.short_name
                if cleaf == "BswMUserCallout":
                    fn = _param_str(choice, "BswMUserCalloutFunction", "")
                    return "UserCallout", fn or choice.short_name
                detail_parts: List[str] = []
                for k, pv in list(choice.parameter_values.items())[:2]:
                    if pv.value is not None:
                        detail_parts.append(f"{k.replace('BswM', '')}={pv.value}")
                for k, rv in list(choice.reference_values.items())[:2]:
                    if rv.value_ref:
                        detail_parts.append(f"{_ar_leaf(rv.value_ref)}")
                suffix = f" ({', '.join(detail_parts)})" if detail_parts else ""
                return cleaf.replace("BswM", ""), f"{target.short_name}{suffix}"
        return leaf, target.short_name

    def list_bswm_action_lists(self) -> List[BswMActionListRow]:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return []
        known = self._known_module_names()
        mode_ctrl = _first_container_by_def(bswm_cfg, "BswMModeControl")
        init_al_name = _ref_leaf(mode_ctrl, "BswMInitActionListRef")
        rows: List[BswMActionListRow] = []
        for al in _iter_containers_by_def(bswm_cfg, "BswMActionList"):
            items = [s for s in al.sub_containers or [] if _ar_leaf(s.definition_ref) == "BswMActionListItem"]
            rows.append(
                BswMActionListRow(
                    short_name=al.short_name,
                    execution=_param_str(al, "BswMActionListExecution", "BSWM_CONDITION"),
                    item_count=len(items),
                    is_init_list=(al.short_name == init_al_name and bool(init_al_name)),
                    container_path=_container_path("BswM", al, known),
                )
            )
        rows.sort(key=lambda r: (0 if r.is_init_list else 1, r.short_name))
        return rows

    def list_bswm_action_list_items(self, action_list_name: Optional[str] = None) -> List[BswMActionListItemRow]:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return []
        known = self._known_module_names()
        bswm_idx = self._bswm_arbitration_index()
        rows: List[BswMActionListItemRow] = []
        for al in _iter_containers_by_def(bswm_cfg, "BswMActionList"):
            if action_list_name and al.short_name != action_list_name:
                continue
            sortable: List[Tuple[int, int, EcucContainerValue]] = []
            for sub_idx, item in enumerate(al.sub_containers or []):
                if _ar_leaf(getattr(item, "definition_ref", None)) != "BswMActionListItem":
                    continue
                idx_val = _param_int(item, "BswMActionListItemIndex")
                sortable.append((idx_val if idx_val is not None else sub_idx, sub_idx, item))
            sortable.sort(key=lambda x: (x[0], x[1]))
            for order_pos, (item_idx, _sub_i, item) in enumerate(sortable):
                refs = _get_all_refs(item, "BswMActionListItemRef")
                tref = refs[0].value_ref if refs and refs[0].value_ref else ""
                target = self._resolve_ref(refs[0], bswm_idx) if refs else None
                kind, summary = self._describe_bswm_action_target(target, tref)
                rows.append(
                    BswMActionListItemRow(
                        action_list_name=al.short_name,
                        short_name=item.short_name,
                        item_index=item_idx,
                        abort_on_fail=_param_bool(item, "BswMAbortOnFail", False),
                        target_ref=tref,
                        target_name=_ar_leaf(tref),
                        action_kind=kind,
                        action_summary=summary,
                        has_broken_ref=(target is None),
                        container_path=_container_path("BswM", item, known),
                    )
                )
        return rows

    def update_bswm_action_list(self, action_list_name: str, *, execution: Optional[str] = None) -> bool:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None or execution is None:
            return False
        al = next((a for a in _iter_containers_by_def(bswm_cfg, "BswMActionList") if a.short_name == action_list_name), None)
        if al is None:
            return False
        self._set_param("BswM", al, "BswMActionListExecution", execution.strip(), "ECUC-ENUMERATION-PARAM-DEF")
        return True

    def move_bswm_action_item(self, action_list_name: str, item_name: str, delta: int) -> bool:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None or delta == 0:
            return False
        al = next((a for a in _iter_containers_by_def(bswm_cfg, "BswMActionList") if a.short_name == action_list_name), None)
        if al is None:
            return False
        items = [s for s in al.sub_containers or [] if _ar_leaf(s.definition_ref) == "BswMActionListItem"]
        items.sort(
            key=lambda s: (
                _param_int(s, "BswMActionListItemIndex")
                if _param_int(s, "BswMActionListItemIndex") is not None
                else 999999,
                (al.sub_containers or []).index(s),
            )
        )
        pos = next((i for i, it in enumerate(items) if it.short_name == item_name), None)
        if pos is None:
            return False
        new_pos = pos + delta
        if not (0 <= new_pos < len(items)):
            return False
        self._check_editable("BswM", al, None)
        items[pos], items[new_pos] = items[new_pos], items[pos]
        other_subs = [s for s in al.sub_containers or [] if _ar_leaf(s.definition_ref) != "BswMActionListItem"]
        al.sub_containers = items + other_subs
        for seq_idx, it in enumerate(items):
            self._set_param("BswM", it, "BswMActionListItemIndex", seq_idx, "ECUC-INTEGER-PARAM-DEF")
        al.mark_modified()
        self._mark_modified("BswM")
        return True

    def update_bswm_action_item(
        self, action_list_name: str, item_name: str, *, abort_on_fail: Optional[bool] = None
    ) -> bool:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None or abort_on_fail is None:
            return False
        al = next((a for a in _iter_containers_by_def(bswm_cfg, "BswMActionList") if a.short_name == action_list_name), None)
        if al is None:
            return False
        item = next((s for s in al.sub_containers or [] if s.short_name == item_name), None)
        if item is None:
            return False
        self._set_param("BswM", item, "BswMAbortOnFail", bool(abort_on_fail), "ECUC-BOOLEAN-PARAM-DEF")
        return True

    def list_bswm_mode_ports(self) -> List[BswMModePortRow]:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[BswMModePortRow] = []
        for port in _iter_containers_by_def(bswm_cfg, "BswMModeRequestPort"):
            src_wrap = next(
                (s for s in port.sub_containers or [] if _ar_leaf(s.definition_ref) == "BswMModeRequestSource"),
                None,
            )
            src_kind = ""
            if src_wrap is not None and src_wrap.sub_containers:
                src_kind = _ar_leaf(src_wrap.sub_containers[0].definition_ref) or src_wrap.sub_containers[0].short_name
            init_wrap = next(
                (s for s in port.sub_containers or [] if _ar_leaf(s.definition_ref) == "BswMModeInitValue"),
                None,
            )
            init_val = ""
            if init_wrap is not None and init_wrap.sub_containers:
                ch = init_wrap.sub_containers[0]
                for pv in ch.parameter_values.values():
                    if pv.value is not None:
                        init_val = str(pv.value)
                        break
                if not init_val:
                    for rv in ch.reference_values.values():
                        if rv.value_ref:
                            init_val = _ar_leaf(rv.value_ref)
                            break
            rows.append(
                BswMModePortRow(
                    short_name=port.short_name,
                    processing=_param_str(port, "BswMRequestProcessing", ""),
                    arbitrate_on_init=_param_bool(port, "BswMArbitrateOnInit", False),
                    source_kind=src_kind,
                    init_value=init_val,
                    container_path=_container_path("BswM", port, known),
                )
            )
        rows.sort(key=lambda r: r.short_name)
        return rows

    def update_bswm_mode_port(
        self,
        port_name: str,
        *,
        processing: Optional[str] = None,
        arbitrate_on_init: Optional[bool] = None,
    ) -> bool:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return False
        port = next((p for p in _iter_containers_by_def(bswm_cfg, "BswMModeRequestPort") if p.short_name == port_name), None)
        if port is None:
            return False
        changed = False
        if processing is not None:
            self._set_param("BswM", port, "BswMRequestProcessing", processing.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            changed = True
        if arbitrate_on_init is not None:
            self._set_param("BswM", port, "BswMArbitrateOnInit", bool(arbitrate_on_init), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        return changed

    def list_bswm_mode_groups(self) -> List[BswMModeGroupRow]:
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[BswMModeGroupRow] = []
        for grp in _iter_containers_by_def(bswm_cfg, "BswMRteModeDclGroup"):
            modes: List[str] = []
            for m in grp.sub_containers or []:
                if _ar_leaf(m.definition_ref) == "BswMRteMode":
                    val = _param_int(m, "BswMModePhysicalValue")
                    modes.append(f"{m.short_name}={val}" if val is not None else m.short_name)
            rows.append(
                BswMModeGroupRow(
                    short_name=grp.short_name,
                    init_mode=_ref_leaf(grp, "BswMInitMode"),
                    modes=modes,
                    container_path=_container_path("BswM", grp, known),
                )
            )
        return rows

    # ------------------------------------------------------------------
    # Tab 3: Os
    # ------------------------------------------------------------------

    def get_os_general(self) -> OsGeneralInfo:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return OsGeneralInfo(loaded=False)
        osos = _first_container_by_def(os_cfg, "OsOS")
        hooks = _first_container_by_def(os_cfg, "OsHooks")
        known = self._known_module_names()
        cores = _iter_containers_by_def(os_cfg, "OsCore")
        return OsGeneralInfo(
            loaded=True,
            status=_param_str(osos, "OsStatus", ""),
            scalability_class=_param_str(osos, "OsScalabilityClass", ""),
            use_case=_param_str(osos, "OsUseCase", ""),
            number_of_cores=_param_int(osos, "OsNumberOfCores"),
            actual_core_count=len(cores),
            stack_monitoring=_param_bool(osos, "OsStackMonitoring", False),
            service_protection=_param_bool(osos, "OsServiceProtection", False),
            error_hook=_param_bool(hooks, "OsErrorHook", False),
            startup_hook=_param_bool(hooks, "OsStartupHook", False),
            shutdown_hook=_param_bool(hooks, "OsShutdownHook", False),
            pre_task_hook=_param_bool(hooks, "OsPreTaskHook", False),
            post_task_hook=_param_bool(hooks, "OsPostTaskHook", False),
            master_core=_ref_leaf(osos, "OsMasterCore"),
            system_timer=_ref_leaf(osos, "OsSystemTimer"),
            osos_path=_container_path("Os", osos, known) if osos is not None else "",
        )

    def update_os_general(
        self,
        *,
        status: Optional[str] = None,
        scalability_class: Optional[str] = None,
        stack_monitoring: Optional[bool] = None,
        error_hook: Optional[bool] = None,
        startup_hook: Optional[bool] = None,
        shutdown_hook: Optional[bool] = None,
        pre_task_hook: Optional[bool] = None,
        post_task_hook: Optional[bool] = None,
    ) -> bool:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return False
        changed = False
        osos = _first_container_by_def(os_cfg, "OsOS")
        if osos is not None:
            if status is not None:
                self._set_param("Os", osos, "OsStatus", status.strip(), "ECUC-ENUMERATION-PARAM-DEF")
                changed = True
            if scalability_class is not None:
                self._set_param("Os", osos, "OsScalabilityClass", scalability_class.strip(), "ECUC-ENUMERATION-PARAM-DEF")
                changed = True
            if stack_monitoring is not None:
                self._set_param("Os", osos, "OsStackMonitoring", bool(stack_monitoring), "ECUC-BOOLEAN-PARAM-DEF")
                changed = True

        hooks = _first_container_by_def(os_cfg, "OsHooks")
        if hooks is not None:
            for pname, val in (
                ("OsErrorHook", error_hook),
                ("OsStartupHook", startup_hook),
                ("OsShutdownHook", shutdown_hook),
                ("OsPreTaskHook", pre_task_hook),
                ("OsPostTaskHook", post_task_hook),
            ):
                if val is not None:
                    self._set_param("Os", hooks, pname, bool(val), "ECUC-BOOLEAN-PARAM-DEF")
                    changed = True
        return changed

    def _os_ownership_maps(
        self,
    ) -> Tuple[
        Dict[str, Tuple[str, str]],  # task_name -> (app_name, core_name)
        Dict[str, Tuple[str, str]],  # isr_name -> (app_name, core_name)
        Dict[str, str],  # app_name -> core_name
        Dict[str, str],  # alarm_name -> app_name
    ]:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return {}, {}, {}, {}

        cidx = self._build_container_index()
        core_by_ecuc_core: Dict[str, str] = {}
        app_to_core: Dict[str, str] = {}
        for core in _iter_containers_by_def(os_cfg, "OsCore"):
            ecuc_core = _ref_leaf(core, "OsCoreEcucCoreRef")
            if ecuc_core:
                core_by_ecuc_core[ecuc_core] = core.short_name
            sys_app = _ref_leaf(core, "OsCoreSystemApplication")
            if sys_app:
                app_to_core[sys_app] = core.short_name

        ecuc_cfg = self._cfg("EcuC")
        ecuc_cores = {c.short_name: _param_int(c, "EcucCoreId") for c in _iter_containers_by_def(ecuc_cfg, "EcucCoreDefinition")}

        task_owners: Dict[str, Tuple[str, str]] = {}
        isr_owners: Dict[str, Tuple[str, str]] = {}
        alarm_owners: Dict[str, str] = {}
        for app in _iter_containers_by_def(os_cfg, "OsApplication"):
            core_name = app_to_core.get(app.short_name, "")
            if not core_name:
                ecuc_core_leaf = _ref_leaf(app, "OsApplicationCoreRef")
                core_name = core_by_ecuc_core.get(ecuc_core_leaf, ecuc_core_leaf)
            if not core_name and ecuc_cores:
                for cn, cid in ecuc_cores.items():
                    if cid is not None and f"Core{cid}" in app.short_name:
                        core_name = cn
            app_to_core[app.short_name] = core_name

            for tref in _get_all_refs(app, "OsAppTaskRef"):
                t_c = self._resolve_ref(tref, cidx)
                t_name = t_c.short_name if t_c is not None else _ar_leaf(tref.value_ref)
                if t_name:
                    task_owners[t_name] = (app.short_name, core_name)
            for iref in _get_all_refs(app, "OsAppIsrRef"):
                i_c = self._resolve_ref(iref, cidx)
                i_name = i_c.short_name if i_c is not None else _ar_leaf(iref.value_ref)
                if i_name:
                    isr_owners[i_name] = (app.short_name, core_name)
            for aref in _get_all_refs(app, "OsAppAlarmRef"):
                a_c = self._resolve_ref(aref, cidx)
                a_name = a_c.short_name if a_c is not None else _ar_leaf(aref.value_ref)
                if a_name:
                    alarm_owners[a_name] = app.short_name
        return task_owners, isr_owners, app_to_core, alarm_owners

    def list_os_core_summaries(self) -> List[OsCoreSummaryRow]:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return []
        ecuc_cfg = self._cfg("EcuC")
        known = self._known_module_names()
        cidx = self._build_container_index()
        ecuc_core_ids = {
            c.short_name: _param_int(c, "EcucCoreId") for c in _iter_containers_by_def(ecuc_cfg, "EcucCoreDefinition")
        }
        task_owners, isr_owners, _app_to_core, _alarm_owners = self._os_ownership_maps()

        # Stack totals per OsCore from OsStackSummary/OsStack when present
        stack_summary_by_core: Dict[str, int] = {}
        os_stacks = _iter_containers_by_def(os_cfg, "OsStack")
        for st in os_stacks:
            cname = _ref_leaf(st, "OsStackCore")
            sz = _param_int(st, "OsStackSize") or 0
            if cname:
                stack_summary_by_core[cname] = stack_summary_by_core.get(cname, 0) + sz

        apps_by_name = {a.short_name: a for a in _iter_containers_by_def(os_cfg, "OsApplication")}
        tasks_by_name = {t.short_name: t for t in _iter_containers_by_def(os_cfg, "OsTask")}
        isrs_by_name = {i.short_name: i for i in _iter_containers_by_def(os_cfg, "OsIsr")}

        rows: List[OsCoreSummaryRow] = []
        for core in _iter_containers_by_def(os_cfg, "OsCore"):
            sys_app_name = _ref_leaf(core, "OsCoreSystemApplication")
            app_c = apps_by_name.get(sys_app_name)
            part_name = _ref_leaf(app_c, "OsAppEcucPartitionRef") if app_c is not None else ""
            ecuc_core_ref_name = _ref_leaf(core, "OsCoreEcucCoreRef")
            core_id = ecuc_core_ids.get(ecuc_core_ref_name)
            if core_id is None:
                digits = "".join(ch for ch in core.short_name if ch.isdigit())
                core_id = int(digits) if digits else None

            t_cnt = len(_get_all_refs(app_c, "OsAppTaskRef")) if app_c is not None else sum(
                1 for _, (_a, cn) in task_owners.items() if cn == core.short_name
            )
            i_cnt = len(_get_all_refs(app_c, "OsAppIsrRef")) if app_c is not None else sum(
                1 for _, (_a, cn) in isr_owners.items() if cn == core.short_name
            )
            a_cnt = len(_get_all_refs(app_c, "OsAppAlarmRef")) if app_c is not None else 0

            if core.short_name in stack_summary_by_core:
                total_stack = stack_summary_by_core[core.short_name]
            else:
                total_stack = 0
                c_stacks = next(
                    (s for s in core.sub_containers or [] if _ar_leaf(s.definition_ref) == "OsCoreStacks"), None
                )
                if c_stacks is not None:
                    for pname, pv in c_stacks.parameter_values.items():
                        if pname.endswith("StackSize"):
                            v = _parse_int(pv.value)
                            if v and v > 0:
                                total_stack += v
                if app_c is not None:
                    for tref in _get_all_refs(app_c, "OsAppTaskRef"):
                        tc = self._resolve_ref(tref, cidx) or tasks_by_name.get(_ar_leaf(tref.value_ref))
                        sz = _param_int(tc, "OsTaskStackSize")
                        if sz and sz > 0:
                            total_stack += sz
                    for iref in _get_all_refs(app_c, "OsAppIsrRef"):
                        ic = self._resolve_ref(iref, cidx) or isrs_by_name.get(_ar_leaf(iref.value_ref))
                        sz = _param_int(ic, "OsIsrStackSize")
                        if sz and sz > 0:
                            total_stack += sz

            rows.append(
                OsCoreSummaryRow(
                    core_name=core.short_name,
                    core_id=core_id,
                    is_autostart=_param_bool(core, "OsCoreIsAutostart", False),
                    is_autosar=_param_bool(core, "OsCoreIsAutosar", True),
                    system_app=sys_app_name,
                    partition_name=part_name,
                    idle_task=_ref_leaf(core, "OsCoreIdleTask"),
                    task_count=t_cnt,
                    isr_count=i_cnt,
                    alarm_count=a_cnt,
                    total_stack_bytes=total_stack,
                    container_path=_container_path("Os", core, known),
                )
            )
        rows.sort(key=lambda r: (r.core_id if r.core_id is not None else 999, r.core_name))
        return rows

    def list_os_tasks(self) -> List[OsTaskRow]:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return []
        known = self._known_module_names()
        task_owners, _isr_owners, _app_to_core, _alarm_owners = self._os_ownership_maps()

        # Collect trigger info from OsAlarm and OsScheduleTable
        triggers_by_task: Dict[str, List[str]] = {}
        for alarm in _iter_containers_by_def(os_cfg, "OsAlarm"):
            for act in _iter_containers_by_def(alarm, "OsAlarmActivateTask"):
                t_name = _ref_leaf(act, "OsAlarmActivateTaskRef")
                if t_name:
                    triggers_by_task.setdefault(t_name, []).append(f"Alarm:{alarm.short_name}")
        for st in _iter_containers_by_def(os_cfg, "OsScheduleTable"):
            dur = _param_int(st, "OsScheduleTableDuration")
            for act in _iter_containers_by_def(st, "OsScheduleTableTaskActivation"):
                t_name = _ref_leaf(act, "OsScheduleTableActivateTaskRef")
                if t_name:
                    lbl = f"SchTbl:{st.short_name}({dur}t)" if dur is not None else f"SchTbl:{st.short_name}"
                    triggers_by_task.setdefault(t_name, []).append(lbl)

        rows: List[OsTaskRow] = []
        for t in _iter_containers_by_def(os_cfg, "OsTask"):
            app_name, core_name = task_owners.get(t.short_name, ("", ""))
            ssz = _param_int(t, "OsTaskStackSize")
            act = _param_int(t, "OsTaskActivation")
            prio = _param_int(t, "OsTaskPriority")
            invalid = (ssz is not None and ssz <= 0) or (act is not None and act <= 0) or (prio is not None and prio < 0)
            rows.append(
                OsTaskRow(
                    short_name=t.short_name,
                    owner_app=app_name,
                    core_name=core_name,
                    priority=prio,
                    stack_size=ssz,
                    activation=act,
                    schedule=_param_str(t, "OsTaskSchedule", ""),
                    task_type=_param_str(t, "OsTaskType", ""),
                    uses_fpu=_param_bool(t, "OsTaskUsesFpu", False),
                    triggers=triggers_by_task.get(t.short_name, []),
                    has_invalid_stack=invalid,
                    container_path=_container_path("Os", t, known),
                )
            )
        rows.sort(key=lambda r: (r.core_name, -(r.priority or 0), r.short_name))
        return rows

    def update_os_task(
        self,
        task_name: str,
        *,
        priority: Optional[int] = None,
        stack_size: Optional[int] = None,
        activation: Optional[int] = None,
        schedule: Optional[str] = None,
        task_type: Optional[str] = None,
        uses_fpu: Optional[bool] = None,
    ) -> bool:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return False
        t = next((c for c in _iter_containers_by_def(os_cfg, "OsTask") if c.short_name == task_name), None)
        if t is None:
            return False
        changed = False
        if priority is not None:
            self._set_param("Os", t, "OsTaskPriority", int(priority), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if stack_size is not None:
            self._set_param("Os", t, "OsTaskStackSize", int(stack_size), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if activation is not None:
            self._set_param("Os", t, "OsTaskActivation", int(activation), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if schedule is not None:
            self._set_param("Os", t, "OsTaskSchedule", schedule.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            changed = True
        if task_type is not None:
            self._set_param("Os", t, "OsTaskType", task_type.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            changed = True
        if uses_fpu is not None:
            self._set_param("Os", t, "OsTaskUsesFpu", bool(uses_fpu), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        return changed

    def list_os_isrs(self) -> List[OsIsrRow]:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return []
        known = self._known_module_names()
        _task_owners, isr_owners, _app_to_core, _alarm_owners = self._os_ownership_maps()
        rows: List[OsIsrRow] = []
        for isr in _iter_containers_by_def(os_cfg, "OsIsr"):
            app_name, core_name = isr_owners.get(isr.short_name, ("", ""))
            ssz = _param_int(isr, "OsIsrStackSize")
            invalid = ssz is not None and ssz <= 0
            rows.append(
                OsIsrRow(
                    short_name=isr.short_name,
                    owner_app=app_name,
                    core_name=core_name,
                    category=_param_str(isr, "OsIsrCategory", ""),
                    interrupt_type=_param_str(isr, "OsIsrInterruptType", ""),
                    interrupt_source=_param_int(isr, "OsIsrInterruptSource"),
                    priority=_param_int(isr, "OsIsrInterruptPriority"),
                    stack_size=ssz,
                    enable_nesting=_param_bool(isr, "OsIsrEnableNesting", False),
                    initial_enable=_param_bool(isr, "OsIsrInitialEnableInterruptSource", False),
                    has_invalid_stack=invalid,
                    container_path=_container_path("Os", isr, known),
                )
            )
        rows.sort(key=lambda r: (r.core_name, -(r.priority or 0), r.short_name))
        return rows

    def update_os_isr(
        self,
        isr_name: str,
        *,
        category: Optional[str] = None,
        priority: Optional[int] = None,
        stack_size: Optional[int] = None,
        interrupt_source: Optional[int] = None,
        enable_nesting: Optional[bool] = None,
        initial_enable: Optional[bool] = None,
    ) -> bool:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return False
        isr = next((c for c in _iter_containers_by_def(os_cfg, "OsIsr") if c.short_name == isr_name), None)
        if isr is None:
            return False
        changed = False
        if category is not None:
            self._set_param("Os", isr, "OsIsrCategory", category.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            changed = True
        if priority is not None:
            self._set_param("Os", isr, "OsIsrInterruptPriority", int(priority), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if stack_size is not None:
            self._set_param("Os", isr, "OsIsrStackSize", int(stack_size), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if interrupt_source is not None:
            self._set_param("Os", isr, "OsIsrInterruptSource", int(interrupt_source), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if enable_nesting is not None:
            self._set_param("Os", isr, "OsIsrEnableNesting", bool(enable_nesting), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        if initial_enable is not None:
            self._set_param("Os", isr, "OsIsrInitialEnableInterruptSource", bool(initial_enable), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        return changed

    def list_os_counters_alarms_schedtables(self) -> List[OsTimingRow]:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return []
        known = self._known_module_names()
        cidx = self._build_container_index()
        _task_owners, _isr_owners, _app_to_core, alarm_owners = self._os_ownership_maps()

        st_owners: Dict[str, str] = {}
        for app in _iter_containers_by_def(os_cfg, "OsApplication"):
            for r in _get_all_refs(app, "OsAppScheduleTableRef"):
                st_owners[_ar_leaf(r.value_ref)] = app.short_name

        rows: List[OsTimingRow] = []
        for cnt in _iter_containers_by_def(os_cfg, "OsCounter"):
            drv = next((s for s in cnt.sub_containers or [] if _ar_leaf(s.definition_ref) == "OsDriver"), None)
            isr_ref = _ref_path(drv, "OsDriverIsrRef") if drv is not None else ""
            drv_broken = bool(isr_ref) and self._resolve_ref(
                _get_all_refs(drv, "OsDriverIsrRef")[0], cidx
            ) is None
            rows.append(
                OsTimingRow(
                    kind="Counter",
                    short_name=cnt.short_name,
                    counter_ref_name=_ar_leaf(isr_ref),
                    detail=f"{_param_str(cnt, 'OsCounterType', '')} (ISR={_ar_leaf(isr_ref) or '-'})",
                    duration_or_max=_param_int(cnt, "OsCounterMaxAllowedValue"),
                    seconds_per_tick=_param_float(cnt, "OsSecondsPerTick"),
                    has_broken_ref=drv_broken,
                    container_path=_container_path("Os", cnt, known),
                )
            )

        for alarm in _iter_containers_by_def(os_cfg, "OsAlarm"):
            cnt_refs = _get_all_refs(alarm, "OsAlarmCounterRef")
            cnt_ref = cnt_refs[0].value_ref if cnt_refs and cnt_refs[0].value_ref else ""
            cnt_broken = (not cnt_ref) or (self._resolve_ref(cnt_refs[0], cidx) is None)
            acts = _iter_containers_by_def(alarm, "OsAlarmActivateTask")
            target_task = _ref_leaf(acts[0], "OsAlarmActivateTaskRef") if acts else ""
            task_broken = False
            if acts and _get_all_refs(acts[0], "OsAlarmActivateTaskRef"):
                task_broken = self._resolve_ref(_get_all_refs(acts[0], "OsAlarmActivateTaskRef")[0], cidx) is None
            rows.append(
                OsTimingRow(
                    kind="Alarm",
                    short_name=alarm.short_name,
                    owner_app=alarm_owners.get(alarm.short_name, ""),
                    counter_ref_name=_ar_leaf(cnt_ref),
                    detail=f"ActivateTask -> {target_task}" if target_task else "AlarmAction",
                    has_broken_ref=cnt_broken or task_broken,
                    container_path=_container_path("Os", alarm, known),
                )
            )

        for st in _iter_containers_by_def(os_cfg, "OsScheduleTable"):
            cnt_refs = _get_all_refs(st, "OsScheduleTableCounterRef")
            cnt_ref = cnt_refs[0].value_ref if cnt_refs and cnt_refs[0].value_ref else ""
            cnt_broken = (not cnt_ref) or (self._resolve_ref(cnt_refs[0], cidx) is None)
            ep_details: List[str] = []
            task_broken = False
            for ep in _iter_containers_by_def(st, "OsScheduleTableExpiryPoint"):
                off = _param_int(ep, "OsScheduleTblExpPointOffset")
                t_names: List[str] = []
                for act in _iter_containers_by_def(ep, "OsScheduleTableTaskActivation"):
                    tref_list = _get_all_refs(act, "OsScheduleTableActivateTaskRef")
                    if tref_list:
                        if self._resolve_ref(tref_list[0], cidx) is None:
                            task_broken = True
                        t_names.append(_ar_leaf(tref_list[0].value_ref))
                if t_names:
                    ep_details.append(f"@{off if off is not None else 0}:{','.join(t_names)}")
            rows.append(
                OsTimingRow(
                    kind="ScheduleTable",
                    short_name=st.short_name,
                    owner_app=st_owners.get(st.short_name, ""),
                    counter_ref_name=_ar_leaf(cnt_ref),
                    detail="; ".join(ep_details) or "ExpiryPoints",
                    duration_or_max=_param_int(st, "OsScheduleTableDuration"),
                    repeating=_param_bool(st, "OsScheduleTableRepeating", False),
                    has_broken_ref=cnt_broken or task_broken,
                    container_path=_container_path("Os", st, known),
                )
            )

        return rows

    def update_os_schedule_table(
        self, st_name: str, *, duration: Optional[int] = None, repeating: Optional[bool] = None
    ) -> bool:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return False
        st = next((c for c in _iter_containers_by_def(os_cfg, "OsScheduleTable") if c.short_name == st_name), None)
        if st is None:
            return False
        changed = False
        if duration is not None:
            self._set_param("Os", st, "OsScheduleTableDuration", int(duration), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if repeating is not None:
            self._set_param("Os", st, "OsScheduleTableRepeating", bool(repeating), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        return changed

    def list_os_resources_spinlocks(self) -> List[OsSyncResourceRow]:
        os_cfg = self._cfg("Os")
        if os_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[OsSyncResourceRow] = []
        for res in _iter_containers_by_def(os_cfg, "OsResource"):
            apps = [_ar_leaf(r.value_ref) for r in _get_all_refs(res, "OsResourceAccessingApplication") if r.value_ref]
            rows.append(
                OsSyncResourceRow(
                    kind="Resource",
                    short_name=res.short_name,
                    policy_or_method=_param_str(res, "OsResourceProperty", "STANDARD"),
                    accessing_apps=apps,
                    container_path=_container_path("Os", res, known),
                )
            )
        for sp in _iter_containers_by_def(os_cfg, "OsSpinlock"):
            apps = [_ar_leaf(r.value_ref) for r in _get_all_refs(sp, "OsSpinlockAccessingApplication") if r.value_ref]
            ltype = _param_str(sp, "OsSpinlockLockType", "")
            lmethod = _param_str(sp, "OsSpinlockLockMethod", "")
            rows.append(
                OsSyncResourceRow(
                    kind="Spinlock",
                    short_name=sp.short_name,
                    policy_or_method=f"{lmethod} ({ltype})" if ltype else lmethod,
                    accessing_apps=apps,
                    container_path=_container_path("Os", sp, known),
                )
            )
        for ioc in _iter_containers_by_def(os_cfg, "OsIocCommunication"):
            sp_name = _ref_leaf(ioc, "OsIocSpinlock")
            snd = [
                _ref_leaf(s, "OsIocSendingOsApplicationRef")
                for s in _iter_containers_by_def(ioc, "OsIocSenderProperties")
                if _ref_leaf(s, "OsIocSendingOsApplicationRef")
            ]
            rcv = [
                _ref_leaf(r, "OsIocReceivingOsApplicationRef")
                for r in _iter_containers_by_def(ioc, "OsIocReceiverProperties")
                if _ref_leaf(r, "OsIocReceivingOsApplicationRef")
            ]
            rows.append(
                OsSyncResourceRow(
                    kind="Ioc",
                    short_name=ioc.short_name,
                    policy_or_method=f"Spinlock={sp_name}" if sp_name else "NoSpinlock",
                    accessing_apps=list(dict.fromkeys(snd + rcv)),
                    detail=f"{','.join(snd) or '?'} -> {','.join(rcv) or '?'}",
                    container_path=_container_path("Os", ioc, known),
                )
            )
        return rows

    # ------------------------------------------------------------------
    # Tab 4: Dcm + CanTp + PduR TP + CanIf
    # ------------------------------------------------------------------

    def _pdur_tp_maps(self) -> Tuple[Dict[str, Tuple[str, str]], Dict[str, Tuple[str, str]]]:
        """Return (by_dest_ecuc_pdu -> (path_name, src_ecuc_pdu), by_src_ecuc_pdu -> (path_name, dest_ecuc_pdu))."""
        pdur_cfg = self._cfg("PduR")
        by_dest: Dict[str, Tuple[str, str]] = {}
        by_src: Dict[str, Tuple[str, str]] = {}
        if pdur_cfg is None:
            return by_dest, by_src

        for path_c in _iter_containers_by_def(pdur_cfg, "PduRRoutingPath"):
            ctype = _param_str(path_c, "PduRRoutingPathCommunicationType", "")
            src_c = next((s for s in path_c.sub_containers or [] if _ar_leaf(s.definition_ref) == "PduRSrcPdu"), None)
            dst_cs = [s for s in path_c.sub_containers or [] if _ar_leaf(s.definition_ref) == "PduRDestPdu"]
            if src_c is None or not dst_cs:
                continue
            src_mod = _ref_leaf(src_c, "PduRSrcPduPduRBswModulesRef").lower()
            src_key = self._norm_key(_ref_path(src_c, "PduRSrcPduRef"))
            for dst_c in dst_cs:
                dst_mod = _ref_leaf(dst_c, "PduRDestPduPduRBswModulesRef").lower()
                dst_key = self._norm_key(_ref_path(dst_c, "PduRDestPduRef"))
                is_tp = (
                    "TRANSPORT" in ctype.upper()
                    or "dcm" in (src_mod, dst_mod)
                    or "cantp" in (src_mod, dst_mod)
                )
                if not is_tp:
                    continue
                if dst_key and src_key:
                    by_dest[dst_key] = (path_c.short_name, src_key)
                    by_src[src_key] = (path_c.short_name, dst_key)
        return by_dest, by_src

    def list_diag_channels(self) -> List[DiagChannelRow]:
        dcm_cfg = self._cfg("Dcm")
        cantp_cfg = self._cfg("CanTp")
        canif_cfg = self._cfg("CanIf")
        pdur_cfg = self._cfg("PduR")
        known = self._known_module_names()
        cidx = self._build_container_index()

        # Index CanIf PDUs by referenced EcuC PDU path
        canif_rx_by_pdu: Dict[str, EcucContainerValue] = {}
        canif_tx_by_pdu: Dict[str, EcucContainerValue] = {}
        if canif_cfg is not None:
            for c in _iter_containers_by_def(canif_cfg, "CanIfRxPduCfg"):
                k = self._norm_key(_ref_path(c, "CanIfRxPduRef"))
                if k:
                    canif_rx_by_pdu[k] = c
            for c in _iter_containers_by_def(canif_cfg, "CanIfTxPduCfg"):
                k = self._norm_key(_ref_path(c, "CanIfTxPduRef"))
                if k:
                    canif_tx_by_pdu[k] = c

        # Index CanTp NSdu containers & associated NPdu/FcNPdu
        cantp_rx_by_nsdu_ref: Dict[str, Tuple[str, EcucContainerValue]] = {}
        cantp_tx_by_nsdu_ref: Dict[str, Tuple[str, EcucContainerValue]] = {}
        used_cantp_nsdus: Set[str] = set()
        if cantp_cfg is not None:
            for ch in _iter_containers_by_def(cantp_cfg, "CanTpChannel"):
                for rx in _iter_containers_by_def(ch, "CanTpRxNSdu"):
                    k = self._norm_key(_ref_path(rx, "CanTpRxNSduRef"))
                    if k:
                        cantp_rx_by_nsdu_ref[k] = (ch.short_name, rx)
                for tx in _iter_containers_by_def(ch, "CanTpTxNSdu"):
                    k = self._norm_key(_ref_path(tx, "CanTpTxNSduRef"))
                    if k:
                        cantp_tx_by_nsdu_ref[k] = (ch.short_name, tx)
            # Also scan outside CanTpChannel if user placed them directly
            for rx in _iter_containers_by_def(cantp_cfg, "CanTpRxNSdu"):
                k = self._norm_key(_ref_path(rx, "CanTpRxNSduRef"))
                if k and k not in cantp_rx_by_nsdu_ref:
                    cantp_rx_by_nsdu_ref[k] = (_ar_leaf(getattr(getattr(rx, "parent", None), "short_name", "")), rx)
            for tx in _iter_containers_by_def(cantp_cfg, "CanTpTxNSdu"):
                k = self._norm_key(_ref_path(tx, "CanTpTxNSduRef"))
                if k and k not in cantp_tx_by_nsdu_ref:
                    cantp_tx_by_nsdu_ref[k] = (_ar_leaf(getattr(getattr(tx, "parent", None), "short_name", "")), tx)

        by_dest, by_src = self._pdur_tp_maps()
        rows: List[DiagChannelRow] = []

        def _npdu_and_fc_info(nsdu_c: EcucContainerValue, direction: str) -> Tuple[str, str, Optional[EcucContainerValue]]:
            if direction == "RX":
                npdu_c = next((s for s in nsdu_c.sub_containers or [] if _ar_leaf(s.definition_ref) == "CanTpRxNPdu"), None)
                fc_c = next((s for s in nsdu_c.sub_containers or [] if _ar_leaf(s.definition_ref) == "CanTpTxFcNPdu"), None)
                npdu_ref = _ref_path(npdu_c, "CanTpRxNPduRef") if npdu_c is not None else ""
                fc_ref = _ref_path(fc_c, "CanTpTxFcNPduRef") if fc_c is not None else ""
                npdu_key = self._norm_key(npdu_ref)
                nsdu_key = self._norm_key(_ref_path(nsdu_c, "CanTpRxNSduRef"))
                canif_c = canif_rx_by_pdu.get(npdu_key) or canif_rx_by_pdu.get(nsdu_key)
                return _ar_leaf(npdu_ref), _ar_leaf(fc_ref), canif_c
            npdu_c = next((s for s in nsdu_c.sub_containers or [] if _ar_leaf(s.definition_ref) == "CanTpTxNPdu"), None)
            fc_c = next((s for s in nsdu_c.sub_containers or [] if _ar_leaf(s.definition_ref) == "CanTpRxFcNPdu"), None)
            npdu_ref = _ref_path(npdu_c, "CanTpTxNPduRef") if npdu_c is not None else ""
            fc_ref = _ref_path(fc_c, "CanTpRxFcNPduRef") if fc_c is not None else ""
            npdu_key = self._norm_key(npdu_ref)
            nsdu_key = self._norm_key(_ref_path(nsdu_c, "CanTpTxNSduRef"))
            canif_c = canif_tx_by_pdu.get(npdu_key) or canif_tx_by_pdu.get(nsdu_key)
            return _ar_leaf(npdu_ref), _ar_leaf(fc_ref), canif_c

        if dcm_cfg is not None:
            for prow in _iter_containers_by_def(dcm_cfg, "DcmDslProtocolRow"):
                rx_buf_refs = _get_all_refs(prow, "DcmDslProtocolRxBufferID")
                tx_buf_refs = _get_all_refs(prow, "DcmDslProtocolTxBufferID")
                rx_buf_c = self._resolve_ref(rx_buf_refs[0], cidx) if rx_buf_refs else None
                tx_buf_c = self._resolve_ref(tx_buf_refs[0], cidx) if tx_buf_refs else None

                for rx in _iter_containers_by_def(prow, "DcmDslProtocolRx"):
                    dcm_pdu_ref = _ref_path(rx, "DcmDslProtocolRxPduRef")
                    dcm_key = self._norm_key(dcm_pdu_ref)
                    pdur_name, tp_pdu_key = by_dest.get(dcm_key, ("", ""))
                    ch_name, nsdu_c = cantp_rx_by_nsdu_ref.get(tp_pdu_key, ("", None))
                    if nsdu_c is None and dcm_key in cantp_rx_by_nsdu_ref:
                        ch_name, nsdu_c = cantp_rx_by_nsdu_ref[dcm_key]

                    npdu_name, fc_name, canif_c = ("", "", None)
                    if nsdu_c is not None:
                        used_cantp_nsdus.add(nsdu_c.short_name)
                        npdu_name, fc_name, canif_c = _npdu_and_fc_info(nsdu_c, "RX")

                    can_id = _param_int(canif_c, "CanIfRxPduCanId") if canif_c is not None else None
                    can_id_type = _param_str(canif_c, "CanIfRxPduCanIdType", "") if canif_c is not None else ""
                    dlc = _param_int(canif_c, "CanIfRxPduDlc") if canif_c is not None else None

                    notes: List[str] = []
                    if not dcm_pdu_ref:
                        notes.append("DcmRxPduRef 缺失")
                    if cantp_cfg is not None and nsdu_c is None:
                        notes.append("未找到匹配的 CanTpRxNSdu")
                    elif nsdu_c is not None and canif_cfg is not None and canif_c is None:
                        notes.append("未找到匹配的 CanIfRxPduCfg")
                    if pdur_cfg is not None and not pdur_name and nsdu_c is not None and dcm_key not in cantp_rx_by_nsdu_ref:
                        notes.append("缺少 PduR TP 路由")

                    addr_raw = _param_str(rx, "DcmDslProtocolRxAddrType", "")
                    addr_type = "FUNCTIONAL" if "FUNCTIONAL" in addr_raw.upper() else ("PHYSICAL" if addr_raw else "")
                    rows.append(
                        DiagChannelRow(
                            name=rx.short_name,
                            direction="RX",
                            addr_type=addr_type,
                            protocol_name=prow.short_name,
                            dcm_pdu_name=_ar_leaf(dcm_pdu_ref),
                            dcm_pdu_id=_param_int(rx, "DcmDslProtocolRxPduId"),
                            pdur_path_name=pdur_name,
                            cantp_channel_name=ch_name,
                            cantp_nsdu_name=nsdu_c.short_name if nsdu_c is not None else "",
                            cantp_npdu_name=npdu_name,
                            cantp_fc_npdu_name=fc_name,
                            canif_pdu_name=canif_c.short_name if canif_c is not None else "",
                            can_id=can_id,
                            can_id_hex=f"0x{can_id:X}" if can_id is not None else "-",
                            can_id_type=can_id_type,
                            dlc=dlc,
                            bs=_param_int(nsdu_c, "CanTpBs") if nsdu_c is not None else None,
                            stmin=_param_float(nsdu_c, "CanTpSTmin") if nsdu_c is not None else None,
                            padding=_param_str(nsdu_c, "CanTpRxPaddingActivation", "") if nsdu_c is not None else "",
                            dl=_param_int(nsdu_c, "CanTpRxDl") if nsdu_c is not None else None,
                            nar=_param_float(nsdu_c, "CanTpNar") if nsdu_c is not None else None,
                            nbr=_param_float(nsdu_c, "CanTpNbr") if nsdu_c is not None else None,
                            ncr=_param_float(nsdu_c, "CanTpNcr") if nsdu_c is not None else None,
                            buffer_name=rx_buf_c.short_name if rx_buf_c is not None else _ref_leaf(prow, "DcmDslProtocolRxBufferID"),
                            buffer_size=_param_int(rx_buf_c, "DcmDslBufferSize") if rx_buf_c is not None else None,
                            comm_channel_name=_ref_leaf(rx, "DcmDslProtocolRxComMChannelRef"),
                            chain_complete=(len(notes) == 0),
                            chain_note="; ".join(notes),
                            dcm_container_path=_container_path("Dcm", rx, known),
                            cantp_nsdu_path=_container_path("CanTp", nsdu_c, known) if nsdu_c is not None else "",
                        )
                    )

                for tx in _iter_containers_by_def(prow, "DcmDslProtocolTx"):
                    dcm_pdu_ref = _ref_path(tx, "DcmDslProtocolTxPduRef")
                    dcm_key = self._norm_key(dcm_pdu_ref)
                    pdur_name, tp_pdu_key = by_src.get(dcm_key, ("", ""))
                    ch_name, nsdu_c = cantp_tx_by_nsdu_ref.get(tp_pdu_key, ("", None))
                    if nsdu_c is None and dcm_key in cantp_tx_by_nsdu_ref:
                        ch_name, nsdu_c = cantp_tx_by_nsdu_ref[dcm_key]

                    npdu_name, fc_name, canif_c = ("", "", None)
                    if nsdu_c is not None:
                        used_cantp_nsdus.add(nsdu_c.short_name)
                        npdu_name, fc_name, canif_c = _npdu_and_fc_info(nsdu_c, "TX")

                    can_id = _param_int(canif_c, "CanIfTxPduCanId") if canif_c is not None else None
                    can_id_type = _param_str(canif_c, "CanIfTxPduCanIdType", "") if canif_c is not None else ""
                    dlc = _param_int(canif_c, "CanIfTxPduDlc") if canif_c is not None else None

                    notes = []
                    if not dcm_pdu_ref:
                        notes.append("DcmTxPduRef 缺失")
                    if cantp_cfg is not None and nsdu_c is None:
                        notes.append("未找到匹配的 CanTpTxNSdu")
                    elif nsdu_c is not None and canif_cfg is not None and canif_c is None:
                        notes.append("未找到匹配的 CanIfTxPduCfg")

                    rows.append(
                        DiagChannelRow(
                            name=tx.short_name,
                            direction="TX",
                            addr_type="RESPONSE",
                            protocol_name=prow.short_name,
                            dcm_pdu_name=_ar_leaf(dcm_pdu_ref),
                            dcm_pdu_id=_param_int(tx, "DcmDslTxConfirmationPduId"),
                            pdur_path_name=pdur_name,
                            cantp_channel_name=ch_name,
                            cantp_nsdu_name=nsdu_c.short_name if nsdu_c is not None else "",
                            cantp_npdu_name=npdu_name,
                            cantp_fc_npdu_name=fc_name,
                            canif_pdu_name=canif_c.short_name if canif_c is not None else "",
                            can_id=can_id,
                            can_id_hex=f"0x{can_id:X}" if can_id is not None else "-",
                            can_id_type=can_id_type,
                            dlc=dlc,
                            padding=_param_str(nsdu_c, "CanTpTxPaddingActivation", "") if nsdu_c is not None else "",
                            dl=_param_int(nsdu_c, "CanTpTxDl") if nsdu_c is not None else None,
                            nas=_param_float(nsdu_c, "CanTpNas") if nsdu_c is not None else None,
                            nbs=_param_float(nsdu_c, "CanTpNbs") if nsdu_c is not None else None,
                            ncs=_param_float(nsdu_c, "CanTpNcs") if nsdu_c is not None else None,
                            buffer_name=tx_buf_c.short_name if tx_buf_c is not None else _ref_leaf(prow, "DcmDslProtocolTxBufferID"),
                            buffer_size=_param_int(tx_buf_c, "DcmDslBufferSize") if tx_buf_c is not None else None,
                            chain_complete=(len(notes) == 0),
                            chain_note="; ".join(notes),
                            dcm_container_path=_container_path("Dcm", tx, known),
                            cantp_nsdu_path=_container_path("CanTp", nsdu_c, known) if nsdu_c is not None else "",
                        )
                    )

        # Include any CanTp NSdus not paired with Dcm
        for direction, nsdu_map in (("RX", cantp_rx_by_nsdu_ref), ("TX", cantp_tx_by_nsdu_ref)):
            for _k, (ch_name, nsdu_c) in nsdu_map.items():
                if nsdu_c.short_name in used_cantp_nsdus:
                    continue
                npdu_name, fc_name, canif_c = _npdu_and_fc_info(nsdu_c, direction)
                can_id = (
                    _param_int(canif_c, "CanIfRxPduCanId" if direction == "RX" else "CanIfTxPduCanId")
                    if canif_c is not None
                    else None
                )
                dlc = (
                    _param_int(canif_c, "CanIfRxPduDlc" if direction == "RX" else "CanIfTxPduDlc")
                    if canif_c is not None
                    else None
                )
                ta_raw = _param_str(nsdu_c, "CanTpRxTaType" if direction == "RX" else "CanTpTxTaType", "")
                addr_type = "FUNCTIONAL" if "FUNCTIONAL" in ta_raw.upper() else ("PHYSICAL" if "PHYSICAL" in ta_raw.upper() else "")
                rows.append(
                    DiagChannelRow(
                        name=nsdu_c.short_name,
                        direction=direction,
                        addr_type=addr_type,
                        cantp_channel_name=ch_name,
                        cantp_nsdu_name=nsdu_c.short_name,
                        cantp_npdu_name=npdu_name,
                        cantp_fc_npdu_name=fc_name,
                        canif_pdu_name=canif_c.short_name if canif_c is not None else "",
                        can_id=can_id,
                        can_id_hex=f"0x{can_id:X}" if can_id is not None else "-",
                        dlc=dlc,
                        bs=_param_int(nsdu_c, "CanTpBs") if direction == "RX" else None,
                        stmin=_param_float(nsdu_c, "CanTpSTmin") if direction == "RX" else None,
                        padding=_param_str(
                            nsdu_c, "CanTpRxPaddingActivation" if direction == "RX" else "CanTpTxPaddingActivation", ""
                        ),
                        dl=_param_int(nsdu_c, "CanTpRxDl" if direction == "RX" else "CanTpTxDl"),
                        nar=_param_float(nsdu_c, "CanTpNar"),
                        nbr=_param_float(nsdu_c, "CanTpNbr"),
                        ncr=_param_float(nsdu_c, "CanTpNcr"),
                        nas=_param_float(nsdu_c, "CanTpNas"),
                        nbs=_param_float(nsdu_c, "CanTpNbs"),
                        ncs=_param_float(nsdu_c, "CanTpNcs"),
                        chain_complete=(dcm_cfg is None and canif_c is not None),
                        chain_note="未连接到 DcmDslProtocol" if dcm_cfg is not None else "",
                        cantp_nsdu_path=_container_path("CanTp", nsdu_c, known),
                    )
                )
        return rows

    def update_cantp_nsdu(
        self,
        nsdu_name: str,
        *,
        bs: Optional[int] = None,
        stmin: Optional[float] = None,
        padding: Optional[str] = None,
        dl: Optional[int] = None,
        nar: Optional[float] = None,
        nbr: Optional[float] = None,
        ncr: Optional[float] = None,
        nas: Optional[float] = None,
        nbs: Optional[float] = None,
        ncs: Optional[float] = None,
    ) -> bool:
        cantp_cfg = self._cfg("CanTp")
        if cantp_cfg is None:
            return False
        rx_c = next((c for c in _iter_containers_by_def(cantp_cfg, "CanTpRxNSdu") if c.short_name == nsdu_name), None)
        tx_c = next((c for c in _iter_containers_by_def(cantp_cfg, "CanTpTxNSdu") if c.short_name == nsdu_name), None)
        target = rx_c or tx_c
        if target is None:
            return False
        is_rx = rx_c is not None
        changed = False
        if bs is not None and is_rx:
            self._set_param("CanTp", target, "CanTpBs", int(bs), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if stmin is not None and is_rx:
            self._set_param("CanTp", target, "CanTpSTmin", float(stmin), "ECUC-FLOAT-PARAM-DEF")
            changed = True
        if padding is not None:
            pname = "CanTpRxPaddingActivation" if is_rx else "CanTpTxPaddingActivation"
            self._set_param("CanTp", target, pname, padding.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            changed = True
        if dl is not None:
            pname = "CanTpRxDl" if is_rx else "CanTpTxDl"
            self._set_param("CanTp", target, pname, int(dl), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        for pname, val in (
            ("CanTpNar", nar),
            ("CanTpNbr", nbr),
            ("CanTpNcr", ncr),
            ("CanTpNas", nas),
            ("CanTpNbs", nbs),
            ("CanTpNcs", ncs),
        ):
            if val is not None:
                self._set_param("CanTp", target, pname, float(val), "ECUC-FLOAT-PARAM-DEF")
                changed = True
        return changed

    def update_dcm_buffer(self, buffer_name: str, size: int) -> bool:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            return False
        buf = next((c for c in _iter_containers_by_def(dcm_cfg, "DcmDslBuffer") if c.short_name == buffer_name), None)
        if buf is None:
            return False
        self._set_param("Dcm", buf, "DcmDslBufferSize", int(size), "ECUC-INTEGER-PARAM-DEF")
        return True

    def list_dcm_services(self) -> List[DcmServiceRow]:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[DcmServiceRow] = []
        for tbl in _iter_containers_by_def(dcm_cfg, "DcmDsdServiceTable"):
            for svc in tbl.sub_containers or []:
                if _ar_leaf(getattr(svc, "definition_ref", None)) != "DcmDsdService":
                    continue
                sid = _param_int(svc, "DcmDsdSidTabServiceId")
                subs = [s for s in svc.sub_containers or [] if _ar_leaf(s.definition_ref) == "DcmDsdSubService"]
                sub_txt = ", ".join(
                    f"{s.short_name}(0x{(_param_int(s, 'DcmDsdSubServiceId') or 0):02X})" for s in subs[:4]
                )
                rows.append(
                    DcmServiceRow(
                        table_name=tbl.short_name,
                        short_name=svc.short_name,
                        sid=sid,
                        sid_hex=f"0x{sid:02X}" if sid is not None else "-",
                        service_label=UDS_SID_NAMES.get(sid, "CustomService") if sid is not None else "",
                        subfunc_avail=_param_bool(svc, "DcmDsdSidTabSubfuncAvail", False),
                        used=_param_bool(svc, "DcmDsdSidTabUsed", True),
                        subservice_count=len(subs),
                        subservice_summary=sub_txt,
                        container_path=_container_path("Dcm", svc, known),
                    )
                )
        rows.sort(key=lambda r: (r.table_name, r.sid if r.sid is not None else 999, r.short_name))
        return rows

    def add_dcm_service(
        self,
        table_name: str,
        short_name: str,
        sid: int,
        *,
        subfunc_avail: bool = True,
        used: bool = True,
    ) -> EcucContainerValue:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            raise RuntimeError("Dcm module is not loaded")
        tbls = _iter_containers_by_def(dcm_cfg, "DcmDsdServiceTable")
        tbl = next((t for t in tbls if t.short_name == table_name), tbls[0] if tbls else None)
        if tbl is None:
            raise RuntimeError("No DcmDsdServiceTable found in Dcm")
        self._check_editable("Dcm", tbl, None)
        clean = short_name.strip() or f"Service_0x{sid:02X}"
        if any(s.short_name == clean for s in tbl.sub_containers or []):
            raise ValueError(f"Service '{clean}' already exists in {tbl.short_name}")
        svc = EcucContainerValue(
            short_name=clean,
            definition_ref=f"{(tbl.definition_ref or '').rstrip('/')}/DcmDsdService",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        tbl.add_sub_container(svc)
        self._set_param("Dcm", svc, "DcmDsdSidTabServiceId", int(sid), "ECUC-INTEGER-PARAM-DEF")
        self._set_param("Dcm", svc, "DcmDsdSidTabSubfuncAvail", bool(subfunc_avail), "ECUC-BOOLEAN-PARAM-DEF")
        self._set_param("Dcm", svc, "DcmDsdSidTabUsed", bool(used), "ECUC-BOOLEAN-PARAM-DEF")
        self._mark_modified("Dcm")
        return svc

    def update_dcm_service(
        self,
        service_name: str,
        *,
        used: Optional[bool] = None,
        subfunc_avail: Optional[bool] = None,
        sid: Optional[int] = None,
    ) -> bool:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            return False
        svc = next((c for c in _iter_containers_by_def(dcm_cfg, "DcmDsdService") if c.short_name == service_name), None)
        if svc is None:
            return False
        changed = False
        if used is not None:
            self._set_param("Dcm", svc, "DcmDsdSidTabUsed", bool(used), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        if subfunc_avail is not None:
            self._set_param("Dcm", svc, "DcmDsdSidTabSubfuncAvail", bool(subfunc_avail), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        if sid is not None:
            self._set_param("Dcm", svc, "DcmDsdSidTabServiceId", int(sid), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        return changed

    def list_dcm_sessions(self) -> List[DcmSessionRow]:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[DcmSessionRow] = []
        for s in _iter_containers_by_def(dcm_cfg, "DcmDspSessionRow"):
            lvl = _param_int(s, "DcmDspSessionLevel")
            rows.append(
                DcmSessionRow(
                    short_name=s.short_name,
                    level=lvl,
                    level_hex=f"0x{lvl:02X}" if lvl is not None else "-",
                    p2_server_max=_param_float(s, "DcmDspSessionP2ServerMax"),
                    p2_star_server_max=_param_float(s, "DcmDspSessionP2StarServerMax"),
                    for_boot=_param_str(s, "DcmDspSessionForBoot", "DCM_NO_BOOT"),
                    container_path=_container_path("Dcm", s, known),
                )
            )
        rows.sort(key=lambda r: (r.level if r.level is not None else 999, r.short_name))
        return rows

    def add_dcm_session(
        self,
        short_name: str,
        level: int,
        *,
        p2_max: float = 0.05,
        p2_star_max: float = 5.0,
        for_boot: str = "DCM_NO_BOOT",
    ) -> EcucContainerValue:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            raise RuntimeError("Dcm module is not loaded")
        dsp_sess = _first_container_by_def(dcm_cfg, "DcmDspSession")
        if dsp_sess is None:
            raise RuntimeError("DcmDspSession container not found")
        self._check_editable("Dcm", dsp_sess, None)
        clean = short_name.strip() or f"DcmDspSessionRow_0x{level:02X}"
        if any(s.short_name == clean for s in dsp_sess.sub_containers or []):
            raise ValueError(f"Session '{clean}' already exists")
        row_c = EcucContainerValue(
            short_name=clean,
            definition_ref=f"{(dsp_sess.definition_ref or '').rstrip('/')}/DcmDspSessionRow",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        dsp_sess.add_sub_container(row_c)
        self._set_param("Dcm", row_c, "DcmDspSessionLevel", int(level), "ECUC-INTEGER-PARAM-DEF")
        self._set_param("Dcm", row_c, "DcmDspSessionP2ServerMax", float(p2_max), "ECUC-FLOAT-PARAM-DEF")
        self._set_param("Dcm", row_c, "DcmDspSessionP2StarServerMax", float(p2_star_max), "ECUC-FLOAT-PARAM-DEF")
        self._set_param("Dcm", row_c, "DcmDspSessionForBoot", for_boot.strip(), "ECUC-ENUMERATION-PARAM-DEF")
        self._mark_modified("Dcm")
        return row_c

    def update_dcm_session(
        self,
        session_name: str,
        *,
        p2_max: Optional[float] = None,
        p2_star_max: Optional[float] = None,
        for_boot: Optional[str] = None,
    ) -> bool:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            return False
        s = next((c for c in _iter_containers_by_def(dcm_cfg, "DcmDspSessionRow") if c.short_name == session_name), None)
        if s is None:
            return False
        changed = False
        if p2_max is not None:
            self._set_param("Dcm", s, "DcmDspSessionP2ServerMax", float(p2_max), "ECUC-FLOAT-PARAM-DEF")
            changed = True
        if p2_star_max is not None:
            self._set_param("Dcm", s, "DcmDspSessionP2StarServerMax", float(p2_star_max), "ECUC-FLOAT-PARAM-DEF")
            changed = True
        if for_boot is not None:
            self._set_param("Dcm", s, "DcmDspSessionForBoot", for_boot.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            changed = True
        return changed

    def list_dcm_security_levels(self) -> List[DcmSecurityRow]:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[DcmSecurityRow] = []
        for s in _iter_containers_by_def(dcm_cfg, "DcmDspSecurityRow"):
            rows.append(
                DcmSecurityRow(
                    short_name=s.short_name,
                    level=_param_int(s, "DcmDspSecurityLevel"),
                    num_attempts=_param_int(s, "DcmDspSecurityNumAttDelay"),
                    delay_time=_param_float(s, "DcmDspSecurityDelayTime"),
                    seed_size=_param_int(s, "DcmDspSecuritySeedSize"),
                    key_size=_param_int(s, "DcmDspSecurityKeySize"),
                    container_path=_container_path("Dcm", s, known),
                )
            )
        rows.sort(key=lambda r: (r.level if r.level is not None else 999, r.short_name))
        return rows

    def list_dcm_dids_and_routines(self) -> List[DcmDidRoutineRow]:
        dcm_cfg = self._cfg("Dcm")
        if dcm_cfg is None:
            return []
        known = self._known_module_names()
        rows: List[DcmDidRoutineRow] = []
        for did in _iter_containers_by_def(dcm_cfg, "DcmDspDid"):
            ident = _param_int(did, "DcmDspDidIdentifier")
            sig_cnt = len(_iter_containers_by_def(did, "DcmDspDidSignal"))
            rows.append(
                DcmDidRoutineRow(
                    kind="DID",
                    short_name=did.short_name,
                    identifier=ident,
                    identifier_hex=f"0x{ident:04X}" if ident is not None else "-",
                    used=_param_bool(did, "DcmDspDidUsed", True),
                    detail=f"Signals={sig_cnt}",
                    container_path=_container_path("Dcm", did, known),
                )
            )
        for rt in _iter_containers_by_def(dcm_cfg, "DcmDspRoutine"):
            ident = _param_int(rt, "DcmDspRoutineIdentifier")
            rows.append(
                DcmDidRoutineRow(
                    kind="Routine",
                    short_name=rt.short_name,
                    identifier=ident,
                    identifier_hex=f"0x{ident:04X}" if ident is not None else "-",
                    used=_param_bool(rt, "DcmDspRoutineUsed", True),
                    detail=_param_str(rt, "DcmDspRoutineInfoRef", ""),
                    container_path=_container_path("Dcm", rt, known),
                )
            )
        return rows

    # ------------------------------------------------------------------
    # Tab 5: Det, CDD & Platform Services
    # ------------------------------------------------------------------

    def get_det_info(self) -> DetGeneralInfo:
        det_cfg = self._cfg("Det")
        if det_cfg is None:
            return DetGeneralInfo(loaded=False)
        gen = _first_container_by_def(det_cfg, "DetGeneral")
        known = self._known_module_names()
        mod_ids: List[int] = []
        for dm in _iter_containers_by_def(det_cfg, "DetModule"):
            mid = _param_int(dm, "DetModuleId")
            if mid is not None:
                mod_ids.append(mid)
        return DetGeneralInfo(
            loaded=True,
            enable_det=_param_bool(gen, "DetEnableDet", False),
            version_info_api=_param_bool(gen, "DetVersionInfoApi", False),
            ext_debug_support=_param_bool(gen, "DetExtDebugSupport", False),
            global_filter_size=_param_int(gen, "DetGlobalFilterSize"),
            break_filter_size=_param_int(gen, "DetBreakFilterSize"),
            log_buffer_size=_param_int(gen, "DetLogBufferSize"),
            module_ids=sorted(set(mod_ids)),
            general_path=_container_path("Det", gen, known) if gen is not None else "",
        )

    def update_det_general(
        self,
        *,
        enable_det: Optional[bool] = None,
        version_info_api: Optional[bool] = None,
        ext_debug_support: Optional[bool] = None,
        log_buffer_size: Optional[int] = None,
        global_filter_size: Optional[int] = None,
    ) -> bool:
        det_cfg = self._cfg("Det")
        if det_cfg is None:
            return False
        gen = _first_container_by_def(det_cfg, "DetGeneral")
        if gen is None:
            return False
        changed = False
        if enable_det is not None:
            self._set_param("Det", gen, "DetEnableDet", bool(enable_det), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        if version_info_api is not None:
            self._set_param("Det", gen, "DetVersionInfoApi", bool(version_info_api), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        if ext_debug_support is not None:
            self._set_param("Det", gen, "DetExtDebugSupport", bool(ext_debug_support), "ECUC-BOOLEAN-PARAM-DEF")
            changed = True
        if log_buffer_size is not None:
            self._set_param("Det", gen, "DetLogBufferSize", int(log_buffer_size), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        if global_filter_size is not None:
            self._set_param("Det", gen, "DetGlobalFilterSize", int(global_filter_size), "ECUC-INTEGER-PARAM-DEF")
            changed = True
        return changed

    def _find_module_det_targets(self, module_name: str) -> List[Tuple[EcucContainerValue, str]]:
        cfg = self._cfg(module_name)
        if cfg is None:
            return []
        hits: List[Tuple[EcucContainerValue, str]] = []

        def _walk(c: EcucContainerValue) -> None:
            for pname in sorted(c.parameter_values.keys()):
                pl = pname.lower()
                if pl == "detenabledet" or pl == "comconfigurationusedet" or pl.endswith("deverrordetect"):
                    hits.append((c, pname))
            for sub in getattr(c, "sub_containers", []) or []:
                _walk(sub)

        for top in getattr(cfg, "containers", []) or []:
            _walk(top)
        return hits

    def list_module_det_flags(self) -> List[ModuleDetFlagRow]:
        known = self._known_module_names()
        rows: List[ModuleDetFlagRow] = []
        for mod_name in sorted(self._managers().keys()):
            mgr = self._mgr(mod_name)
            if mgr is None:
                continue
            hits = self._find_module_det_targets(mod_name)
            if not hits:
                continue
            # Pick canonical flag (e.g., *DevErrorDetect over *DevErrorDetectUninit when both exist)
            c, pname = hits[0]
            checker = getattr(mgr, "check_editable", None)
            locked = False
            if callable(checker):
                try:
                    checker(c, pname)
                except PreLockedError:
                    locked = True
                except Exception:
                    pass
            rows.append(
                ModuleDetFlagRow(
                    module_name=mod_name,
                    param_name=pname,
                    enabled=_param_bool(c, pname, False),
                    container_path=_container_path(mod_name, c, known),
                    locked=locked,
                )
            )
        return rows

    def set_module_det_flag(self, module_name: str, enabled: bool) -> bool:
        hits = self._find_module_det_targets(module_name)
        if not hits:
            return False
        c, pname = hits[0]
        self._set_param(module_name, c, pname, bool(enabled), "ECUC-BOOLEAN-PARAM-DEF")
        return True

    def set_all_module_det_flags(self, enabled: bool) -> int:
        changed = 0
        for row in self.list_module_det_flags():
            try:
                if self.set_module_det_flag(row.module_name, enabled):
                    changed += 1
            except PreLockedError:
                continue
        return changed

    def list_cdd_and_platform_modules(self) -> List[CddPlatformModuleRow]:
        known = self._known_module_names()
        ecum_init_ids = {r.module_id for r in self.list_ecum_init_items()}
        rte_cfg = self._cfg("Rte")
        rte_bsw_mods = {
            _ref_leaf(inst, "RteBswModuleInstanceRef") or inst.short_name
            for inst in _iter_containers_by_def(rte_cfg, "RteBswModuleInstance")
        }
        pdur_cfg = self._cfg("PduR")
        pdur_mods = {
            _ref_leaf(bm, "PduRBswModuleRef") or bm.short_name
            for bm in _iter_containers_by_def(pdur_cfg, "PduRBswModules")
        }

        rows: List[CddPlatformModuleRow] = []
        for mod_name, mgr in sorted(self._managers().items()):
            cfg = getattr(mgr, "configuration", None)
            if cfg is None:
                continue
            is_cdd = _is_cdd_module(mod_name, mgr)
            is_plat = mod_name in PLATFORM_MODULE_NAMES
            is_custom = mod_name not in STANDARD_BSW_MCAL_MODULES and not is_plat and not is_cdd
            if not (is_cdd or is_plat or is_custom):
                continue

            kind = "CDD" if is_cdd else ("Platform" if is_plat else "Service")
            mdef = getattr(mgr, "module_def", None)
            dref = str(getattr(cfg, "definition_ref", "") or getattr(mdef, "definition_ref", "") or "")
            icv = str(getattr(cfg, "implementation_config_variant", "") or "")
            tops = getattr(cfg, "containers", []) or []

            summary = ""
            if mod_name == "vBaseEnv":
                deriv = _first_container_by_def(cfg, "vBaseEnvDerivativeInformation")
                gen = _first_container_by_def(cfg, "vBaseEnvGeneral")
                sel_name = _ref_leaf(gen, "vBaseEnvTestedDerivativeRef") or (deriv.short_name if deriv else "")
                core_amt = _param_int(deriv, "vBaseEnvCpuCoreAmount") if deriv is not None else None
                summary = f"Derivative={sel_name}" + (f" ({core_amt} cores)" if core_amt is not None else "")
            elif mod_name == "vBRS":
                hw = _first_container_by_def(cfg, "vBRSHwConfig")
                osc = _param_int(hw, "vBRSOscClock")
                tb = _param_int(hw, "vBRSTimebaseClock")
                summary = f"Timebase={tb or '-'}Hz, Osc={osc or '-'}Hz"
            elif mod_name == "Det":
                dinfo = self.get_det_info()
                summary = f"DetEnableDet={dinfo.enable_det}, Modules={len(dinfo.module_ids)}"

            rows.append(
                CddPlatformModuleRow(
                    module_name=mod_name,
                    kind=kind,
                    definition_ref=dref,
                    config_variant=icv,
                    container_count=len(tops),
                    in_ecum_init=(mod_name in ecum_init_ids),
                    in_rte_bsw=(mod_name in rte_bsw_mods),
                    in_pdur=(mod_name in pdur_mods),
                    summary=summary,
                    first_container_path=_container_path(mod_name, tops[0], known) if tops else "",
                )
            )
        return rows

    # ------------------------------------------------------------------
    # Cross-Module Validation Diagnostics
    # ------------------------------------------------------------------

    def collect_diagnostics(self) -> List[ServiceDiagnostic]:
        """Collect all System Services & Diagnostics consistency checks across Tabs 0..4."""
        if not self.has_service_modules():
            return []

        diags: List[ServiceDiagnostic] = []
        known = self._known_module_names()
        cidx = self._build_container_index()

        # --- Tab 0: EcuM ---
        ecum_cfg = self._cfg("EcuM")
        if ecum_cfg is not None:
            for row in self.list_ecum_init_items():
                if not row.module_loaded:
                    diags.append(
                        ServiceDiagnostic(
                            severity="warning",
                            code="ECUM_INIT_MODULE_NOT_LOADED",
                            message=f"{row.list_name} 中初始化项 '{row.short_name}' 指向未加载模块 '{row.module_id}'",
                            module_name="EcuM",
                            container_path=row.container_path,
                            parameter_name="EcuMModuleID",
                            workbench_tab=0,
                            suggested_fix="在系统服务工作台页签 1 检查或移除未使用的初始化项，或加载对应模块",
                        )
                    )

            common = _first_container_by_def(ecum_cfg, "EcuMCommonConfiguration")
            flex = _first_container_by_def(ecum_cfg, "EcuMFlexConfiguration")
            for c_target, rname in (
                (common, "EcuMDefaultAppMode"),
                (common, "EcuMOSResource"),
                (flex, "EcuMFlexModuleConfigurationRef"),
                (flex, "EcuMNormalMcuModeRef"),
            ):
                if c_target is None:
                    continue
                for ref_v in _get_all_refs(c_target, rname):
                    if ref_v.value_ref and self._resolve_ref(ref_v, cidx) is None:
                        diags.append(
                            ServiceDiagnostic(
                                severity="error",
                                code="ECUM_BROKEN_REF",
                                message=f"EcuM 引用 {rname} 指向无效路径: {ref_v.value_ref}",
                                module_name="EcuM",
                                container_path=_container_path("EcuM", c_target, known),
                                parameter_name=rname,
                                workbench_tab=0,
                                suggested_fix="核对目标 Os/Mcu/Can 容器是否存在并重新关联引用",
                            )
                        )
            for ws_row in self.list_ecum_wakeup_sources():
                if ws_row.has_broken_ref:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="ECUM_BROKEN_REF",
                            message=f"EcuMWakeupSource '{ws_row.short_name}' 的 EcuMComMChannelRef 指向无效通道",
                            module_name="EcuM",
                            container_path=ws_row.container_path,
                            parameter_name="EcuMComMChannelRef",
                            workbench_tab=0,
                            suggested_fix="在页签 1 核对唤醒源关联的 ComMChannel",
                        )
                    )

            by_ws_id: Dict[int, List[EcuMWakeupSourceRow]] = {}
            for ws_row in self.list_ecum_wakeup_sources():
                if ws_row.wakeup_id is not None:
                    by_ws_id.setdefault(ws_row.wakeup_id, []).append(ws_row)
            for wid, dups in sorted(by_ws_id.items()):
                if len(dups) > 1:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="ECUM_DUP_WAKEUP_ID",
                            message=f"EcuMWakeupSourceId={wid} 重复: {', '.join(d.short_name for d in dups)}",
                            module_name="EcuM",
                            container_path=dups[0].container_path,
                            parameter_name="EcuMWakeupSourceId",
                            workbench_tab=0,
                            suggested_fix="为每个唤醒源分配唯一的 EcuMWakeupSourceId",
                        )
                    )

        # --- Tab 1: BswM ---
        bswm_cfg = self._cfg("BswM")
        if bswm_cfg is not None:
            rules = self.list_bswm_rules()
            bswm_idx = self._bswm_arbitration_index()
            for r in rules:
                if r.has_cycle:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="BSWM_CYCLE_DETECTED",
                            message=f"BswMRule '{r.short_name}' 表达式中存在逻辑表达式循环引用",
                            module_name="BswM",
                            container_path=r.container_path,
                            parameter_name="BswMRuleExpressionRef",
                            workbench_tab=1,
                            suggested_fix="检查 BswMLogicalExpression.BswMArgumentRef 并消除闭环引用",
                        )
                    )
                if r.has_broken_ref:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="BSWM_BROKEN_RULE_REF",
                            message=f"BswMRule '{r.short_name}' 的表达式或 True/False ActionList 引用无效",
                            module_name="BswM",
                            container_path=r.container_path,
                            parameter_name="BswMRuleExpressionRef",
                            workbench_tab=1,
                            suggested_fix="在页签 2 检查规则表达式与 True/False ActionList 绑定",
                        )
                    )

            for r in _iter_containers_by_def(bswm_cfg, "BswMRule"):
                # Catch broken expression refs specifically if empty on rule
                if not _get_all_refs(r, "BswMRuleExpressionRef") and not any(
                    d.container_path == _container_path("BswM", r, known) and d.code == "BSWM_BROKEN_RULE_REF"
                    for d in diags
                ):
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="BSWM_BROKEN_RULE_REF",
                            message=f"BswMRule '{r.short_name}' 缺少 BswMRuleExpressionRef",
                            module_name="BswM",
                            container_path=_container_path("BswM", r, known),
                            parameter_name="BswMRuleExpressionRef",
                            workbench_tab=1,
                            suggested_fix="为 BswMRule 指定有效的 BswMLogicalExpression",
                        )
                    )

            by_rule_id: Dict[int, List[BswMRuleRow]] = {}
            for r in rules:
                if r.rule_id is not None:
                    by_rule_id.setdefault(r.rule_id, []).append(r)
            for rid, dups in sorted(by_rule_id.items()):
                if len(dups) > 1:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="BSWM_DUP_RULE_ID",
                            message=f"BswMRuleId={rid} 重复: {', '.join(d.short_name for d in dups[:4])}",
                            module_name="BswM",
                            container_path=dups[0].container_path,
                            parameter_name="BswMRuleId",
                            workbench_tab=1,
                            suggested_fix="确保每个 BswMRule 拥有唯一的 BswMRuleId",
                        )
                    )

            for item in self.list_bswm_action_list_items():
                if item.has_broken_ref:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="BSWM_BROKEN_ACTION_ITEM_REF",
                            message=f"BswMActionList '{item.action_list_name}' 的动作项 '{item.short_name}' 引用失效",
                            module_name="BswM",
                            container_path=item.container_path,
                            parameter_name="BswMActionListItemRef",
                            workbench_tab=1,
                            suggested_fix="在页签 2 检查并修复失效的 BswMActionListItemRef",
                        )
                    )

            # Check BswM<Module>Enabled mismatch with loaded modules
            loaded_mods = set(self._managers().keys())
            gen = _first_container_by_def(bswm_cfg, "BswMGeneral")
            gen_path = _container_path("BswM", gen, known) if gen is not None else "/BswM/BswMGeneral"
            for sw_name, sw_val in self.get_bswm_module_switches().items():
                target_mod = _BSWM_SWITCH_TO_MODULE.get(sw_name)
                if not target_mod:
                    continue
                if sw_val and target_mod not in loaded_mods:
                    diags.append(
                        ServiceDiagnostic(
                            severity="warning",
                            code="BSWM_MODULE_SWITCH_MISMATCH",
                            message=f"BswM 开关 {sw_name}=True，但工程未加载 {target_mod} 模块",
                            module_name="BswM",
                            container_path=gen_path,
                            parameter_name=sw_name,
                            workbench_tab=1,
                            suggested_fix=f"关闭 {sw_name} 或在工程中添加 {target_mod} 模块",
                        )
                    )
                elif (not sw_val) and target_mod in loaded_mods:
                    diags.append(
                        ServiceDiagnostic(
                            severity="warning",
                            code="BSWM_MODULE_SWITCH_MISMATCH",
                            message=f"工程已加载 {target_mod} 模块，但 BswM 开关 {sw_name}=False",
                            module_name="BswM",
                            container_path=gen_path,
                            parameter_name=sw_name,
                            workbench_tab=1,
                            suggested_fix=f"在页签 2 开启 {sw_name} 以启用 BswM 模式交互",
                        )
                    )

        # --- Tab 2: Os ---
        os_cfg = self._cfg("Os")
        if os_cfg is not None:
            os_gen = self.get_os_general()
            if (
                os_gen.number_of_cores is not None
                and os_gen.actual_core_count > 0
                and os_gen.number_of_cores != os_gen.actual_core_count
            ):
                diags.append(
                    ServiceDiagnostic(
                        severity="warning",
                        code="OS_CORE_COUNT_MISMATCH",
                        message=f"OsOS.OsNumberOfCores={os_gen.number_of_cores} 与实际 OsCore 数量 ({os_gen.actual_core_count}) 不一致",
                        module_name="Os",
                        container_path=os_gen.osos_path,
                        parameter_name="OsNumberOfCores",
                        workbench_tab=2,
                        suggested_fix="核对 OsOS.OsNumberOfCores 与 OsCore 配置",
                    )
                )

            has_apps = len(_iter_containers_by_def(os_cfg, "OsApplication")) > 0
            for t in self.list_os_tasks():
                if has_apps and not t.owner_app:
                    diags.append(
                        ServiceDiagnostic(
                            severity="warning",
                            code="OS_UNOWNED_TASK_OR_ISR",
                            message=f"OsTask '{t.short_name}' 未归属任何 OsApplication (OsAppTaskRef)",
                            module_name="Os",
                            container_path=t.container_path,
                            workbench_tab=2,
                            suggested_fix="将该 Task 添加到目标 OsApplication.OsAppTaskRef",
                        )
                    )
                if t.has_invalid_stack:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="OS_INVALID_STACK_SIZE",
                            message=f"OsTask '{t.short_name}' 栈大小/激活数/优先级配置无效 (Stack={t.stack_size}, Act={t.activation}, Prio={t.priority})",
                            module_name="Os",
                            container_path=t.container_path,
                            parameter_name="OsTaskStackSize",
                            workbench_tab=2,
                            suggested_fix="在页签 3 为 OsTask 设置大于 0 的栈大小与激活次数",
                        )
                    )

            seen_isr_src: Dict[Tuple[str, int], List[OsIsrRow]] = {}
            for isr in self.list_os_isrs():
                if has_apps and not isr.owner_app:
                    diags.append(
                        ServiceDiagnostic(
                            severity="warning",
                            code="OS_UNOWNED_TASK_OR_ISR",
                            message=f"OsIsr '{isr.short_name}' 未归属任何 OsApplication (OsAppIsrRef)",
                            module_name="Os",
                            container_path=isr.container_path,
                            workbench_tab=2,
                            suggested_fix="将该 ISR 添加到目标 OsApplication.OsAppIsrRef",
                        )
                    )
                if isr.has_invalid_stack:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="OS_INVALID_STACK_SIZE",
                            message=f"OsIsr '{isr.short_name}' 栈大小无效 (Stack={isr.stack_size})",
                            module_name="Os",
                            container_path=isr.container_path,
                            parameter_name="OsIsrStackSize",
                            workbench_tab=2,
                            suggested_fix="在页签 3 为 OsIsr 设置大于 0 的 OsIsrStackSize",
                        )
                    )
                if isr.interrupt_source is not None:
                    scope = isr.core_name or isr.owner_app or "_global"
                    seen_isr_src.setdefault((scope, isr.interrupt_source), []).append(isr)

            for (scope, src_num), dups in sorted(seen_isr_src.items()):
                if len(dups) > 1:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="OS_DUP_ISR_SOURCE",
                            message=f"核心/应用 '{scope}' 中断源号 {src_num} 重复分配给多个 ISR: {', '.join(d.short_name for d in dups)}",
                            module_name="Os",
                            container_path=dups[0].container_path,
                            parameter_name="OsIsrInterruptSource",
                            workbench_tab=2,
                            suggested_fix="为同一核心下的 ISR 分配唯一的中断源号",
                        )
                    )

            for tr in self.list_os_counters_alarms_schedtables():
                if tr.has_broken_ref:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="OS_BROKEN_TIMING_REF",
                            message=f"OS {tr.kind} '{tr.short_name}' 引用了不存在的 Counter/Task/ISR",
                            module_name="Os",
                            container_path=tr.container_path,
                            workbench_tab=2,
                            suggested_fix="核对 Counter/Alarm/ScheduleTable 中的目标引用",
                        )
                    )

        # --- Tab 3: Dcm + CanTp ---
        dcm_cfg = self._cfg("Dcm")
        cantp_cfg = self._cfg("CanTp")
        if dcm_cfg is not None:
            for prow in _iter_containers_by_def(dcm_cfg, "DcmDslProtocolRow"):
                p_path = _container_path("Dcm", prow, known)
                for rname in ("DcmDslProtocolRxBufferID", "DcmDslProtocolTxBufferID", "DcmDslProtocolSIDTable"):
                    refs = _get_all_refs(prow, rname)
                    if refs and refs[0].value_ref and self._resolve_ref(refs[0], cidx) is None:
                        diags.append(
                            ServiceDiagnostic(
                                severity="error",
                                code="DIAG_BROKEN_DCM_REF",
                                message=f"DcmDslProtocolRow '{prow.short_name}' 引用 {rname} 无效: {refs[0].value_ref}",
                                module_name="Dcm",
                                container_path=p_path,
                                parameter_name=rname,
                                workbench_tab=3,
                                suggested_fix="核对 DcmDslBuffer 或 DcmDsdServiceTable 引用路径",
                            )
                        )
            for rx in _iter_containers_by_def(dcm_cfg, "DcmDslProtocolRx"):
                rx_path = _container_path("Dcm", rx, known)
                for rname in ("DcmDslProtocolRxComMChannelRef", "DcmDslProtocolRxPduRef"):
                    refs = _get_all_refs(rx, rname)
                    if refs and refs[0].value_ref and self._resolve_ref(refs[0], cidx) is None:
                        diags.append(
                            ServiceDiagnostic(
                                severity="error",
                                code="DIAG_BROKEN_DCM_REF",
                                message=f"DcmDslProtocolRx '{rx.short_name}' 引用 {rname} 无效: {refs[0].value_ref}",
                                module_name="Dcm",
                                container_path=rx_path,
                                parameter_name=rname,
                                workbench_tab=3,
                                suggested_fix="核对 ComMChannel 或 EcuC Pdu 引用",
                            )
                        )
            for tx in _iter_containers_by_def(dcm_cfg, "DcmDslProtocolTx"):
                tx_path = _container_path("Dcm", tx, known)
                refs = _get_all_refs(tx, "DcmDslProtocolTxPduRef")
                if refs and refs[0].value_ref and self._resolve_ref(refs[0], cidx) is None:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="DIAG_BROKEN_DCM_REF",
                            message=f"DcmDslProtocolTx '{tx.short_name}' 引用 DcmDslProtocolTxPduRef 无效: {refs[0].value_ref}",
                            module_name="Dcm",
                            container_path=tx_path,
                            parameter_name="DcmDslProtocolTxPduRef",
                            workbench_tab=3,
                            suggested_fix="核对 EcuC Pdu 引用",
                        )
                    )

            for buf in _iter_containers_by_def(dcm_cfg, "DcmDslBuffer"):
                sz = _param_int(buf, "DcmDslBufferSize")
                if sz is not None and sz <= 0:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="DIAG_DCM_CONFIG_INVALID",
                            message=f"DcmDslBuffer '{buf.short_name}' 大小 DcmDslBufferSize={sz} 无效",
                            module_name="Dcm",
                            container_path=_container_path("Dcm", buf, known),
                            parameter_name="DcmDslBufferSize",
                            workbench_tab=3,
                            suggested_fix="在页签 4 将 DcmDslBufferSize 设为大于 0 的字节数",
                        )
                    )
            for sess in self.list_dcm_sessions():
                if sess.p2_server_max is not None and sess.p2_server_max <= 0:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="DIAG_DCM_CONFIG_INVALID",
                            message=f"DcmDspSessionRow '{sess.short_name}' 的 P2ServerMax ({sess.p2_server_max}) 必须大于 0",
                            module_name="Dcm",
                            container_path=sess.container_path,
                            parameter_name="DcmDspSessionP2ServerMax",
                            workbench_tab=3,
                            suggested_fix="设置合理的 P2ServerMax 时间 (如 0.05s)",
                        )
                    )

            by_sid: Dict[Tuple[str, int], List[DcmServiceRow]] = {}
            for svc in self.list_dcm_services():
                if svc.sid is not None:
                    by_sid.setdefault((svc.table_name, svc.sid), []).append(svc)
            for (tbl, sid), dups in sorted(by_sid.items()):
                if len(dups) > 1:
                    diags.append(
                        ServiceDiagnostic(
                            severity="error",
                            code="DIAG_DCM_CONFIG_INVALID",
                            message=f"UDS 服务表 '{tbl}' 存在重复 SID 0x{sid:02X}: {', '.join(d.short_name for d in dups)}",
                            module_name="Dcm",
                            container_path=dups[0].container_path,
                            parameter_name="DcmDsdSidTabServiceId",
                            workbench_tab=3,
                            suggested_fix="在同一 DcmDsdServiceTable 内保持每个 SID 唯一",
                        )
                    )

        if dcm_cfg is not None or cantp_cfg is not None:
            for ch_row in self.list_diag_channels():
                if not ch_row.chain_complete and ch_row.chain_note:
                    diags.append(
                        ServiceDiagnostic(
                            severity="warning",
                            code="DIAG_TP_CHAIN_BROKEN",
                            message=f"诊断通道 '{ch_row.name}' ({ch_row.direction}) 链路不完整: {ch_row.chain_note}",
                            module_name="Dcm" if ch_row.dcm_container_path else "CanTp",
                            container_path=ch_row.dcm_container_path or ch_row.cantp_nsdu_path,
                            workbench_tab=3,
                            suggested_fix="检查 Dcm <-> PduR(TRANSPORT_PROTOCOL) <-> CanTp <-> CanIf 之间的 PDU 引用链",
                        )
                    )

        # --- Tab 4: Det ---
        det_cfg = self._cfg("Det")
        if det_cfg is not None:
            det_info = self.get_det_info()
            mod_flags = self.list_module_det_flags()
            enabled_others = [f.module_name for f in mod_flags if f.module_name != "Det" and f.enabled]
            if not det_info.enable_det and enabled_others:
                diags.append(
                    ServiceDiagnostic(
                        severity="info",
                        code="DET_DISABLED_WITH_MODULE_CHECKS",
                        message=f"DetEnableDet=False，但有 {len(enabled_others)} 个模块启用了 DevErrorDetect ({', '.join(enabled_others[:4])}...)",
                        module_name="Det",
                        container_path=det_info.general_path,
                        parameter_name="DetEnableDet",
                        workbench_tab=4,
                        suggested_fix="在页签 5 开启 DetEnableDet 或统一切换各模块 DET 开关",
                    )
                )

        return diags
