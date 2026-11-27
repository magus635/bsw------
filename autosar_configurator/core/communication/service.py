"""Pure-Python domain service aggregating and editing the AUTOSAR communication stack."""

from typing import Any, Dict, Iterable, List, Optional, Set, Tuple

from ..config_manager import PreLockedError
from ..model.configuration_model import EcucContainerValue, EcucReferenceValue
from ..model.ecuc_paths import strip_ecuc_prefixes
from ...generator.rte.workbench_service import snapshot_rte_config, restore_rte_config
from .bit_layout import analyze_pdu_bit_layout
from .models import (
    CommChannelRow,
    CommDiagnostic,
    CommMessageRow,
    CommSignalRow,
    PduRRoutingRow,
)

COMM_MODULES: Tuple[str, ...] = (
    "Can",
    "CanTrcv",
    "CanIf",
    "CanSM",
    "CanTp",
    "PduR",
    "Com",
    "ComM",
    "EcuC",
)

ANCHOR_PRIORITY: Tuple[str, ...] = ("Com", "PduR", "CanIf", "CanSM", "ComM", "Can")

CAN_ID_TYPES: Tuple[str, ...] = (
    "STANDARD_CAN",
    "EXTENDED_CAN",
    "STANDARD_FD_CAN",
    "EXTENDED_FD_CAN",
)

COM_TX_MODES: Tuple[str, ...] = ("PERIODIC", "DIRECT", "MIXED", "NONE")

COM_SIGNAL_TYPES: Tuple[str, ...] = (
    "BOOLEAN",
    "UINT8",
    "UINT16",
    "UINT32",
    "UINT64",
    "SINT8",
    "SINT16",
    "SINT32",
    "SINT64",
    "FLOAT32",
    "FLOAT64",
    "UINT8_N",
)

COM_ENDIANNESS: Tuple[str, ...] = ("BIG_ENDIAN", "LITTLE_ENDIAN", "OPAQUE")

COM_TRANSFER_PROPS: Tuple[str, ...] = (
    "PENDING",
    "TRIGGERED",
    "TRIGGERED_ON_CHANGE",
    "TRIGGERED_ON_CHANGE_WITHOUT_REPETITION",
    "TRIGGERED_WITHOUT_REPETITION",
)


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


def _iter_containers_by_def(cfg: Any, def_leaf: str) -> Iterable[EcucContainerValue]:
    if cfg is None:
        return []
    found: List[EcucContainerValue] = []

    def _walk(c: EcucContainerValue) -> None:
        if _ar_leaf(getattr(c, "definition_ref", None)) == def_leaf:
            found.append(c)
        for sub in getattr(c, "sub_containers", []) or []:
            _walk(sub)

    for top in getattr(cfg, "containers", []) or []:
        _walk(top)
    return found


def _get_all_refs(container: EcucContainerValue, ref_name: str) -> List[EcucReferenceValue]:
    refs: List[EcucReferenceValue] = []
    single = getattr(container, "reference_values", {}).get(ref_name)
    if single is not None:
        refs.append(single)
    multi = getattr(container, "multi_reference_values", {}).get(ref_name, []) or []
    refs.extend(multi)
    return refs


def _ref_leaf(container: Optional[EcucContainerValue], ref_name: str) -> str:
    if container is None:
        return ""
    refs = _get_all_refs(container, ref_name)
    for r in refs:
        if r.value_ref:
            return _ar_leaf(r.value_ref)
    return ""


def _param_str(container: Optional[EcucContainerValue], param_name: str, default: str = "") -> str:
    if container is None:
        return default
    pv = container.parameter_values.get(param_name)
    if pv is None or pv.value is None:
        return default
    text = str(pv.value).strip()
    return text if text else default


def _param_int(container: Optional[EcucContainerValue], param_name: str) -> Optional[int]:
    if container is None:
        return None
    pv = container.parameter_values.get(param_name)
    return _parse_int(pv.value) if pv is not None else None


def _param_float(container: Optional[EcucContainerValue], param_name: str) -> Optional[float]:
    if container is None:
        return None
    pv = container.parameter_values.get(param_name)
    return _parse_float(pv.value) if pv is not None else None


def _container_path(module_name: str, container: EcucContainerValue) -> str:
    try:
        p = container.get_path()
        if p:
            stripped = strip_ecuc_prefixes(p)
            if stripped.startswith(f"/{module_name}/"):
                return stripped
            return f"/{module_name}{stripped}" if stripped.startswith("/") else f"/{module_name}/{stripped}"
    except Exception:
        pass
    return f"/{module_name}/{container.short_name}"


class CommunicationWorkbenchService:
    """Qt-free domain coordinator for the 5-tab Communication Workbench."""

    def __init__(self, project: Any) -> None:
        self.project = project

    # ------------------------------------------------------------------
    # Module lookups, snapshots & low-level mutation helpers
    # ------------------------------------------------------------------

    def _managers(self) -> Dict[str, Any]:
        return getattr(self.project, "module_managers", {}) or {}

    def _mgr(self, module_name: str) -> Optional[Any]:
        mgr = self._managers().get(module_name)
        if mgr is not None and getattr(mgr, "configuration", None) is not None:
            return mgr
        return None

    def _cfg(self, module_name: str) -> Optional[Any]:
        mgr = self._mgr(module_name)
        return getattr(mgr, "configuration", None) if mgr is not None else None

    def loaded_comm_modules(self) -> List[str]:
        return [m for m in COMM_MODULES if self._cfg(m) is not None]

    def has_comm_modules(self) -> bool:
        return any(self._cfg(m) is not None for m in COMM_MODULES if m != "EcuC")

    @staticmethod
    def anchor_module_for_project(project: Any) -> Optional[str]:
        managers = getattr(project, "module_managers", {}) or {}
        for mod in ANCHOR_PRIORITY:
            mgr = managers.get(mod)
            if mgr is not None and getattr(mgr, "configuration", None) is not None:
                return mod
        return None

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

    def _ref_prefix(self, module_name: str, sub_path: Optional[str] = None) -> str:
        proj_type = getattr(self.project, "project_type", None)
        type_name = getattr(proj_type, "name", "")
        if type_name == "EB_TRESOS":
            return f"/{module_name}/{sub_path}" if sub_path else f"/{module_name}/{module_name}"
        return f"/ActiveEcuC/{module_name}/{sub_path}" if sub_path else f"/ActiveEcuC/{module_name}"

    def _container_ref_path(self, module_name: str, container: EcucContainerValue) -> str:
        sub_path = _container_path(module_name, container).lstrip("/")
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

    def _append_ref(
        self,
        module_name: str,
        container: EcucContainerValue,
        name: str,
        value_ref: str,
        *,
        dest_type: str = "ECUC-REFERENCE-DEF",
        value_ref_dest: str = "ECUC-CONTAINER-VALUE",
    ) -> None:
        """Append ``value_ref`` to single or multi ``reference_values`` safely without duplicates."""
        existing = _get_all_refs(container, name)
        if any((r.value_ref or "").strip().rstrip("/") == value_ref.strip().rstrip("/") for r in existing):
            return
        self._check_editable(module_name, container, name)
        dref = f"{(container.definition_ref or self._module_base_def(module_name)).rstrip('/')}/{name}"
        if not existing:
            container.set_reference_value(
                name, value_ref, dref, dest_type=dest_type, value_ref_dest=value_ref_dest
            )
        else:
            if name in container.reference_values and name not in container.multi_reference_values:
                first = container.reference_values.pop(name)
                first.index = 0
                container.multi_reference_values[name] = [first]
            idx = len(container.multi_reference_values.get(name, []))
            container.add_multi_reference_value(
                name,
                value_ref,
                dref,
                index=idx,
                dest_type=dest_type,
                value_ref_dest=value_ref_dest,
            )
        self._mark_modified(module_name)

    def _refresh_project_references(self) -> None:
        if self.project is None:
            return
        resolve_fn = getattr(self.project, "resolve_all_references", None)
        if callable(resolve_fn):
            try:
                resolve_fn(force=True)
            except Exception:
                pass
        build_fn = getattr(self.project, "build_reverse_reference_index", None)
        if callable(build_fn):
            try:
                build_fn()
            except Exception:
                pass

    def capture_snapshots(self) -> Dict[str, Any]:
        """Capture isolated snapshots of all loaded communication modules."""
        snaps: Dict[str, Any] = {}
        for mod in COMM_MODULES:
            cfg = self._cfg(mod)
            if cfg is not None:
                snaps[mod] = snapshot_rte_config(cfg)
        return snaps

    def restore_snapshots(self, snapshots: Dict[str, Any]) -> None:
        """Restore all captured communication modules and re-resolve cross-module references."""
        if not snapshots:
            return
        for mod, snap in snapshots.items():
            cfg = self._cfg(mod)
            if cfg is not None and snap is not None:
                restore_rte_config(cfg, snap, project=None)
        self._refresh_project_references()

    def _resolve_target_exists(self, ref_val: Optional[EcucReferenceValue], expected_mod: str) -> bool:
        if ref_val is None or not (ref_val.value_ref or "").strip():
            return False
        if self._cfg(expected_mod) is None:
            return True  # target module isn't loaded at all; avoid blaming broken internal link
        if getattr(ref_val, "is_resolved", False) and getattr(ref_val, "target", None) is not None:
            return True
        get_inst = getattr(self.project, "get_instance_by_path", None)
        if callable(get_inst) and get_inst(ref_val.value_ref) is not None:
            return True
        return False

    # ------------------------------------------------------------------
    # Tab 1: Channels
    # ------------------------------------------------------------------

    def list_channel_rows(self) -> List[CommChannelRow]:
        """Aggregate channel topology across ComM, CanSM, CanIf, Can, and CanTrcv."""
        comm_channels = {
            c.short_name: c for c in _iter_containers_by_def(self._cfg("ComM"), "ComMChannel")
        }
        cansm_nets = list(_iter_containers_by_def(self._cfg("CanSM"), "CanSMManagerNetwork"))
        canif_ctrls = {
            c.short_name: c for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfCtrlCfg")
        }
        canif_trcvs = {
            c.short_name: c for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfTrcvCfg")
        }
        can_ctrls = {
            c.short_name: c for c in _iter_containers_by_def(self._cfg("Can"), "CanController")
        }
        cantrcv_chs = {
            c.short_name: c for c in _iter_containers_by_def(self._cfg("CanTrcv"), "CanTrcvChannel")
        }

        cansm_by_canif_ctrl: Dict[str, EcucContainerValue] = {}
        cansm_by_comm_ch: Dict[str, EcucContainerValue] = {}
        for net in cansm_nets:
            comm_leaf = _ref_leaf(net, "CanSMComMNetworkHandleRef")
            if comm_leaf:
                cansm_by_comm_ch[comm_leaf] = net
            for sub in getattr(net, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) == "CanSMController":
                    ctrl_leaf = _ref_leaf(sub, "CanSMControllerId")
                    if ctrl_leaf:
                        cansm_by_canif_ctrl[ctrl_leaf] = net

        rows: List[CommChannelRow] = []
        used_comm: Set[str] = set()
        used_can_ctrls: Set[str] = set()

        def _extract_baud(can_ctrl: Optional[EcucContainerValue]) -> Tuple[Optional[float], Optional[float]]:
            if can_ctrl is None:
                return None, None
            default_baud_leaf = _ref_leaf(can_ctrl, "CanControllerDefaultBaudrate")
            baud_cfg: Optional[EcucContainerValue] = None
            for sub in getattr(can_ctrl, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) == "CanControllerBaudrateConfig":
                    if not default_baud_leaf or sub.short_name == default_baud_leaf:
                        baud_cfg = sub
                        break
                    if baud_cfg is None:
                        baud_cfg = sub
            if baud_cfg is None:
                return None, None
            arb = _param_float(baud_cfg, "CanControllerBaudRate")
            fd = None
            for sub in getattr(baud_cfg, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) == "CanControllerFdBaudrateConfig":
                    fd = _param_float(sub, "CanControllerFdBaudRate")
                    break
            return arb, fd

        for ctrl_name, canif_ctrl in sorted(canif_ctrls.items()):
            cansm_net = cansm_by_canif_ctrl.get(ctrl_name)
            comm_leaf = _ref_leaf(cansm_net, "CanSMComMNetworkHandleRef")
            comm_ch = comm_channels.get(comm_leaf)
            if comm_ch is not None:
                used_comm.add(comm_ch.short_name)

            can_ctrl_leaf = _ref_leaf(canif_ctrl, "CanIfCtrlCanCtrlRef")
            can_ctrl = can_ctrls.get(can_ctrl_leaf)
            if can_ctrl is not None:
                used_can_ctrls.add(can_ctrl.short_name)

            trcv_cfg_leaf = _ref_leaf(canif_ctrl, "CanIfCtrlTrcvCfgRef") or _ref_leaf(cansm_net, "CanSMTransceiverId")
            canif_trcv = canif_trcvs.get(trcv_cfg_leaf)
            cantrcv_leaf = _ref_leaf(canif_trcv, "CanIfTrcvCanTrcvRef")
            cantrcv_ch = cantrcv_chs.get(cantrcv_leaf)

            nm_variant = "-"
            if comm_ch is not None:
                for sub in getattr(comm_ch, "sub_containers", []) or []:
                    if _ar_leaf(getattr(sub, "definition_ref", None)) == "ComMNetworkManagement":
                        nm_variant = _param_str(sub, "ComMNmVariant", "-")
                        break

            arb_baud, fd_baud = _extract_baud(can_ctrl)

            broken = False
            can_ref_v = canif_ctrl.reference_values.get("CanIfCtrlCanCtrlRef")
            if self._cfg("Can") is not None and (
                can_ref_v is None or not self._resolve_target_exists(can_ref_v, "Can")
            ):
                broken = True
            if cansm_net is not None and self._cfg("ComM") is not None:
                comm_ref_v = cansm_net.reference_values.get("CanSMComMNetworkHandleRef")
                if comm_ref_v is None or not self._resolve_target_exists(comm_ref_v, "ComM"):
                    broken = True

            primary_path = (
                _container_path("ComM", comm_ch)
                if comm_ch is not None
                else _container_path("CanIf", canif_ctrl)
            )
            rows.append(
                CommChannelRow(
                    channel_name=comm_ch.short_name if comm_ch is not None else ctrl_name,
                    bus_type=_param_str(comm_ch, "ComMBusType", "CAN"),
                    comm_channel_id=_param_int(comm_ch, "ComMChannelId") if comm_ch else _param_int(canif_ctrl, "CanIfCtrlId"),
                    nm_variant=nm_variant,
                    cansm_network_name=cansm_net.short_name if cansm_net else "",
                    canif_ctrl_name=ctrl_name,
                    can_controller_name=can_ctrl.short_name if can_ctrl else can_ctrl_leaf,
                    hardware_channel=_param_str(can_ctrl, "CanHardwareChannel", ""),
                    baudrate_kbps=arb_baud,
                    fd_baudrate_kbps=fd_baud,
                    rx_processing=_param_str(can_ctrl, "CanRxProcessing", ""),
                    tx_processing=_param_str(can_ctrl, "CanTxProcessing", ""),
                    trcv_channel_name=cantrcv_ch.short_name if cantrcv_ch else cantrcv_leaf,
                    trcv_init_state=_param_str(cantrcv_ch, "CanTrcvInitState", ""),
                    trcv_max_baudrate=_param_int(cantrcv_ch, "CanTrcvMaxBaudrate"),
                    has_broken_link=broken,
                    primary_container_path=primary_path,
                )
            )

        for comm_name, comm_ch in sorted(comm_channels.items()):
            if comm_name in used_comm:
                continue
            cansm_net = cansm_by_comm_ch.get(comm_name)
            nm_variant = "-"
            for sub in getattr(comm_ch, "sub_containers", []) or []:
                if _ar_leaf(getattr(sub, "definition_ref", None)) == "ComMNetworkManagement":
                    nm_variant = _param_str(sub, "ComMNmVariant", "-")
                    break
            rows.append(
                CommChannelRow(
                    channel_name=comm_name,
                    bus_type=_param_str(comm_ch, "ComMBusType", "CAN"),
                    comm_channel_id=_param_int(comm_ch, "ComMChannelId"),
                    nm_variant=nm_variant,
                    cansm_network_name=cansm_net.short_name if cansm_net else "",
                    has_broken_link=bool(self._cfg("CanSM") is not None and cansm_net is None and "CAN" in _param_str(comm_ch, "ComMBusType", "CAN").upper()),
                    primary_container_path=_container_path("ComM", comm_ch),
                )
            )

        for ctrl_name, can_ctrl in sorted(can_ctrls.items()):
            if ctrl_name in used_can_ctrls:
                continue
            arb_baud, fd_baud = _extract_baud(can_ctrl)
            rows.append(
                CommChannelRow(
                    channel_name=ctrl_name,
                    bus_type="CAN",
                    comm_channel_id=_param_int(can_ctrl, "CanControllerId"),
                    can_controller_name=ctrl_name,
                    hardware_channel=_param_str(can_ctrl, "CanHardwareChannel", ""),
                    baudrate_kbps=arb_baud,
                    fd_baudrate_kbps=fd_baud,
                    rx_processing=_param_str(can_ctrl, "CanRxProcessing", ""),
                    tx_processing=_param_str(can_ctrl, "CanTxProcessing", ""),
                    primary_container_path=_container_path("Can", can_ctrl),
                )
            )

        return rows

    # ------------------------------------------------------------------
    # Internal ECUC chain indexing
    # ------------------------------------------------------------------

    def _index_ecuc_pdus(self) -> Dict[str, EcucContainerValue]:
        return {c.short_name: c for c in _iter_containers_by_def(self._cfg("EcuC"), "Pdu")}

    @staticmethod
    def _extract_com_tx_timing(com_ipdu: Optional[EcucContainerValue]) -> Tuple[str, Optional[float]]:
        if com_ipdu is None:
            return "", None
        for sub in getattr(com_ipdu, "sub_containers", []) or []:
            if _ar_leaf(getattr(sub, "definition_ref", None)) != "ComTxIPdu":
                continue
            for tm_parent in getattr(sub, "sub_containers", []) or []:
                if _ar_leaf(getattr(tm_parent, "definition_ref", None)) == "ComTxModeTrue":
                    for tm in getattr(tm_parent, "sub_containers", []) or []:
                        if _ar_leaf(getattr(tm, "definition_ref", None)) == "ComTxMode":
                            mode = _param_str(tm, "ComTxModeMode", "")
                            period_sec = _param_float(tm, "ComTxModeTimePeriod")
                            cycle_ms = round(period_sec * 1000.0, 6) if period_sec is not None else None
                            return mode, cycle_ms
        return "", None

    def _channel_by_canif_ctrl(self) -> Dict[str, str]:
        mapping: Dict[str, str] = {}
        for row in self.list_channel_rows():
            if row.canif_ctrl_name:
                mapping[row.canif_ctrl_name] = row.channel_name
        return mapping

    # ------------------------------------------------------------------
    # Tab 2: Messages & End-to-End Chains
    # ------------------------------------------------------------------

    def list_message_rows(self) -> List[CommMessageRow]:
        """Aggregate TX/RX CAN messages and diagnostic TP PDUs end-to-end."""
        ecuc_pdus = self._index_ecuc_pdus()
        routing_rows = self.list_pdur_routing_rows()
        com_ipdus = list(_iter_containers_by_def(self._cfg("Com"), "ComIPdu"))
        canif_tx = list(_iter_containers_by_def(self._cfg("CanIf"), "CanIfTxPduCfg"))
        canif_rx = list(_iter_containers_by_def(self._cfg("CanIf"), "CanIfRxPduCfg"))

        com_by_pdu: Dict[str, EcucContainerValue] = {}
        for ipdu in com_ipdus:
            pdu_leaf = _ref_leaf(ipdu, "ComPduIdRef")
            if pdu_leaf:
                com_by_pdu[pdu_leaf] = ipdu

        pdur_by_src: Dict[str, PduRRoutingRow] = {}
        pdur_by_dest: Dict[str, PduRRoutingRow] = {}
        for rr in routing_rows:
            if rr.src_pdu_name and rr.src_pdu_name not in pdur_by_src:
                pdur_by_src[rr.src_pdu_name] = rr
            if rr.dest_pdu_name and rr.dest_pdu_name not in pdur_by_dest:
                pdur_by_dest[rr.dest_pdu_name] = rr

        # Map CanTp NSDU by NPDU leaf
        cantp_by_npdu: Dict[str, str] = {}
        cantp_cfg = self._cfg("CanTp")
        for nsdu_def in ("CanTpRxNSdu", "CanTpTxNSdu"):
            for nsdu in _iter_containers_by_def(cantp_cfg, nsdu_def):
                for sub in getattr(nsdu, "sub_containers", []) or []:
                    for r in getattr(sub, "reference_values", {}).values():
                        if r.value_ref:
                            cantp_by_npdu.setdefault(_ar_leaf(r.value_ref), nsdu.short_name)

        # Resolve CanIf buffer -> HTH -> Ctrl and HRH -> Ctrl
        ctrl_channel = self._channel_by_canif_ctrl()
        hth_ctrl: Dict[str, str] = {
            c.short_name: _ref_leaf(c, "CanIfHthCanCtrlIdRef")
            for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfHthCfg")
        }
        hrh_ctrl: Dict[str, str] = {
            c.short_name: _ref_leaf(c, "CanIfHrhCanCtrlIdRef")
            for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfHrhCfg")
        }
        buf_ctrl: Dict[str, str] = {}
        for buf in _iter_containers_by_def(self._cfg("CanIf"), "CanIfBufferCfg"):
            hth_leaf = _ref_leaf(buf, "CanIfBufferHthRef")
            if hth_leaf in hth_ctrl:
                buf_ctrl[buf.short_name] = hth_ctrl[hth_leaf]

        rows: List[CommMessageRow] = []
        visited_com: Set[str] = set()

        def _make_canif_row(direction: str, pdu_cfg: EcucContainerValue) -> CommMessageRow:
            if direction == "TX":
                can_id = _param_int(pdu_cfg, "CanIfTxPduCanId")
                can_id_type = _param_str(pdu_cfg, "CanIfTxPduCanIdType", "STANDARD_CAN")
                dlc = _param_int(pdu_cfg, "CanIfTxPduDlc")
                hid = _param_int(pdu_cfg, "CanIfTxPduId")
                lower_pdu_leaf = _ref_leaf(pdu_cfg, "CanIfTxPduRef")
                ul = _param_str(pdu_cfg, "CanIfTxPduUserTxConfirmationUL", "")
                ctrl_name = buf_ctrl.get(_ref_leaf(pdu_cfg, "CanIfTxPduBufferRef"), "")
                routing = pdur_by_dest.get(lower_pdu_leaf)
                upper_pdu_leaf = routing.src_pdu_name if routing else lower_pdu_leaf
            else:
                can_id = _param_int(pdu_cfg, "CanIfRxPduCanId")
                can_id_type = _param_str(pdu_cfg, "CanIfRxPduCanIdType", "STANDARD_CAN")
                dlc = _param_int(pdu_cfg, "CanIfRxPduDlc")
                hid = _param_int(pdu_cfg, "CanIfRxPduId")
                lower_pdu_leaf = _ref_leaf(pdu_cfg, "CanIfRxPduRef")
                ul = _param_str(pdu_cfg, "CanIfRxPduUserRxIndicationUL", "")
                ctrl_name = hrh_ctrl.get(_ref_leaf(pdu_cfg, "CanIfRxPduHrhIdRef"), "")
                routing = pdur_by_src.get(lower_pdu_leaf)
                upper_pdu_leaf = routing.dest_pdu_name if routing else lower_pdu_leaf

            cantp_nsdu = cantp_by_npdu.get(lower_pdu_leaf, "")
            is_tp = ("TP" in ul.upper()) or bool(cantp_nsdu)

            com_ipdu = com_by_pdu.get(upper_pdu_leaf) or com_by_pdu.get(lower_pdu_leaf)
            if com_ipdu is not None:
                visited_com.add(com_ipdu.short_name)

            lower_len = _param_int(ecuc_pdus.get(lower_pdu_leaf), "PduLength")
            upper_len = _param_int(ecuc_pdus.get(upper_pdu_leaf), "PduLength")
            ecuc_len = lower_len if lower_len is not None else upper_len

            tx_mode, cycle_ms = ("", None)
            if direction == "TX" and com_ipdu is not None:
                tx_mode, cycle_ms = self._extract_com_tx_timing(com_ipdu)

            sig_count = len(_get_all_refs(com_ipdu, "ComIPduSignalRef")) if com_ipdu is not None else 0
            channel = (
                _ref_leaf(com_ipdu, "ComIPduChannelRef")
                or ctrl_channel.get(ctrl_name, "")
                or ctrl_name
            )

            len_mismatch = False
            if dlc is not None:
                if lower_len is not None and dlc != lower_len:
                    len_mismatch = True
                if upper_len is not None and dlc != upper_len:
                    len_mismatch = True
            if lower_len is not None and upper_len is not None and lower_len != upper_len:
                len_mismatch = True

            broken_chain = bool(
                (routing is not None and routing.has_broken_ref)
                or (not lower_pdu_leaf or (self._cfg("EcuC") is not None and lower_pdu_leaf not in ecuc_pdus))
                or (not is_tp and "PDUR" in ul.upper() and (routing is None or (self._cfg("Com") is not None and com_ipdu is None)))
            )

            category = "DIAG_TP" if is_tp else ("ORPHAN" if (com_ipdu is None and self._cfg("Com") is not None) else "COM")
            return CommMessageRow(
                direction=direction,
                category=category,
                name=com_ipdu.short_name if com_ipdu is not None else pdu_cfg.short_name,
                can_id=can_id,
                can_id_type=can_id_type,
                canif_dlc=dlc,
                ecuc_pdu_length=ecuc_len,
                tx_mode=tx_mode,
                cycle_time_ms=cycle_ms,
                channel_name=channel,
                signal_count=sig_count,
                canif_pdu_name=pdu_cfg.short_name,
                canif_pdu_path=_container_path("CanIf", pdu_cfg),
                canif_handle_id=hid,
                ecuc_lower_pdu_name=lower_pdu_leaf,
                ecuc_lower_length=lower_len,
                ecuc_upper_pdu_name=upper_pdu_leaf if routing else "",
                ecuc_upper_length=upper_len if routing else None,
                pdur_path_name=routing.path_name if routing else "",
                com_ipdu_name=com_ipdu.short_name if com_ipdu is not None else "",
                com_ipdu_path=_container_path("Com", com_ipdu) if com_ipdu is not None else "",
                com_handle_id=_param_int(com_ipdu, "ComIPduHandleId") if com_ipdu is not None else None,
                cantp_nsdu_name=cantp_nsdu,
                has_length_mismatch=len_mismatch,
                has_broken_chain=broken_chain,
                primary_container_path=_container_path("CanIf", pdu_cfg),
            )

        for pdu_cfg in canif_tx:
            rows.append(_make_canif_row("TX", pdu_cfg))
        for pdu_cfg in canif_rx:
            rows.append(_make_canif_row("RX", pdu_cfg))

        for ipdu in com_ipdus:
            if ipdu.short_name in visited_com:
                continue
            dir_raw = _param_str(ipdu, "ComIPduDirection", "SEND").upper()
            direction = "RX" if "REC" in dir_raw or dir_raw == "RX" else "TX"
            pdu_leaf = _ref_leaf(ipdu, "ComPduIdRef")
            upper_len = _param_int(ecuc_pdus.get(pdu_leaf), "PduLength")
            tx_mode, cycle_ms = self._extract_com_tx_timing(ipdu) if direction == "TX" else ("", None)
            routing = pdur_by_src.get(pdu_leaf) if direction == "TX" else pdur_by_dest.get(pdu_leaf)
            rows.append(
                CommMessageRow(
                    direction=direction,
                    category="ORPHAN",
                    name=ipdu.short_name,
                    ecuc_pdu_length=upper_len,
                    tx_mode=tx_mode,
                    cycle_time_ms=cycle_ms,
                    channel_name=_ref_leaf(ipdu, "ComIPduChannelRef"),
                    signal_count=len(_get_all_refs(ipdu, "ComIPduSignalRef")),
                    ecuc_upper_pdu_name=pdu_leaf,
                    ecuc_upper_length=upper_len,
                    pdur_path_name=routing.path_name if routing else "",
                    com_ipdu_name=ipdu.short_name,
                    com_ipdu_path=_container_path("Com", ipdu),
                    com_handle_id=_param_int(ipdu, "ComIPduHandleId"),
                    has_broken_chain=True,
                    primary_container_path=_container_path("Com", ipdu),
                )
            )

        rows.sort(key=lambda r: (0 if r.category != "ORPHAN" else 1, r.direction, r.can_id if r.can_id is not None else 0xFFFFFFFF, r.name))
        return rows

    # ------------------------------------------------------------------
    # Tab 3: Signals & Motorola/Intel Bit Grid
    # ------------------------------------------------------------------

    def _ipdu_byte_length_map(self) -> Dict[str, Optional[int]]:
        lengths: Dict[str, Optional[int]] = {}
        for msg in self.list_message_rows():
            if not msg.com_ipdu_name:
                continue
            cand = msg.ecuc_upper_length if msg.ecuc_upper_length is not None else msg.canif_dlc
            if cand is None:
                cand = msg.ecuc_pdu_length
            lengths[msg.com_ipdu_name] = cand
        return lengths

    def _collect_ipdu_signals(self) -> Tuple[Dict[str, EcucContainerValue], Dict[str, List[EcucContainerValue]], Dict[str, str], Dict[str, str]]:
        com_cfg = self._cfg("Com")
        signals_by_name: Dict[str, EcucContainerValue] = {
            s.short_name: s for s in _iter_containers_by_def(com_cfg, "ComSignal")
        }
        ipdu_signals: Dict[str, List[EcucContainerValue]] = {}
        sig_to_ipdu: Dict[str, str] = {}
        ipdu_dir: Dict[str, str] = {}

        for ipdu in _iter_containers_by_def(com_cfg, "ComIPdu"):
            dir_raw = _param_str(ipdu, "ComIPduDirection", "SEND").upper()
            ipdu_dir[ipdu.short_name] = "RX" if ("REC" in dir_raw or dir_raw == "RX") else "TX"
            attached: List[EcucContainerValue] = []
            seen_s: Set[str] = set()
            for ref_val in _get_all_refs(ipdu, "ComIPduSignalRef"):
                s_leaf = _ar_leaf(ref_val.value_ref)
                sig_c = signals_by_name.get(s_leaf)
                if sig_c is not None and s_leaf not in seen_s:
                    seen_s.add(s_leaf)
                    attached.append(sig_c)
                    sig_to_ipdu.setdefault(s_leaf, ipdu.short_name)
            ipdu_signals[ipdu.short_name] = attached

        return signals_by_name, ipdu_signals, sig_to_ipdu, ipdu_dir

    def list_signal_rows(self, ipdu_name: Optional[str] = None) -> List[CommSignalRow]:
        """List all ComSignals with parent ComIPdu and bit-layout conflict status."""
        signals_by_name, ipdu_signals, sig_to_ipdu, ipdu_dir = self._collect_ipdu_signals()
        len_by_ipdu = self._ipdu_byte_length_map()

        overlap_by_ipdu: Dict[str, Set[str]] = {}
        oob_by_ipdu: Dict[str, Set[str]] = {}
        for pname, sigs in ipdu_signals.items():
            specs = [
                (
                    s.short_name,
                    _param_int(s, "ComBitPosition"),
                    _param_int(s, "ComBitSize"),
                    _param_str(s, "ComSignalEndianness", "BIG_ENDIAN"),
                )
                for s in sigs
            ]
            _, ov, oob = analyze_pdu_bit_layout(specs, len_by_ipdu.get(pname))
            overlap_by_ipdu[pname] = ov
            oob_by_ipdu[pname] = oob

        rows: List[CommSignalRow] = []
        for sig_name in sorted(signals_by_name):
            sig = signals_by_name[sig_name]
            parent_ipdu = sig_to_ipdu.get(sig_name, "")
            if ipdu_name and parent_ipdu != ipdu_name:
                continue
            ov_set = overlap_by_ipdu.get(parent_ipdu, set())
            oob_set = oob_by_ipdu.get(parent_ipdu, set())
            rows.append(
                CommSignalRow(
                    signal_name=sig_name,
                    ipdu_name=parent_ipdu,
                    direction=ipdu_dir.get(parent_ipdu, ""),
                    bit_position=_param_int(sig, "ComBitPosition"),
                    bit_size=_param_int(sig, "ComBitSize"),
                    endianness=_param_str(sig, "ComSignalEndianness", "BIG_ENDIAN"),
                    signal_type=_param_str(sig, "ComSignalType", "UINT8"),
                    init_value=_param_str(sig, "ComSignalInitValue", "0"),
                    transfer_property=_param_str(sig, "ComTransferProperty", "PENDING"),
                    timeout_sec=_param_float(sig, "ComTimeout"),
                    handle_id=_param_int(sig, "ComHandleId"),
                    system_signal_ref=_ref_leaf(sig, "ComSystemTemplateSystemSignalRef"),
                    container_path=_container_path("Com", sig),
                    has_overlap=sig_name in ov_set,
                    out_of_bounds=sig_name in oob_set,
                )
            )
        return rows

    def get_ipdu_bit_grid(
        self, ipdu_name: str
    ) -> Tuple[int, Dict[Tuple[int, int], List[str]], Set[str], Set[str]]:
        """Return ``(byte_len, grid, overlapping_signals, oob_signals)`` for ``ipdu_name``."""
        _, ipdu_signals, _, _ = self._collect_ipdu_signals()
        sigs = ipdu_signals.get(ipdu_name, [])
        len_by_ipdu = self._ipdu_byte_length_map()
        pdu_len = len_by_ipdu.get(ipdu_name)
        specs = [
            (
                s.short_name,
                _param_int(s, "ComBitPosition"),
                _param_int(s, "ComBitSize"),
                _param_str(s, "ComSignalEndianness", "BIG_ENDIAN"),
            )
            for s in sigs
        ]
        grid, ov, oob = analyze_pdu_bit_layout(specs, pdu_len)
        max_byte = max((b for (b, _bit) in grid.keys()), default=-1)
        display_len = max(pdu_len if pdu_len is not None else 8, max_byte + 1, 8)
        return display_len, grid, ov, oob

    # ------------------------------------------------------------------
    # Tab 4: PduR Routing Matrix
    # ------------------------------------------------------------------

    def list_pdur_routing_rows(self) -> List[PduRRoutingRow]:
        """List all PduRRoutingPath entries with source/destination module & PDU status."""
        pdur_cfg = self._cfg("PduR")
        if pdur_cfg is None:
            return []
        ecuc_pdus = self._index_ecuc_pdus()
        bsw_mod_by_name: Dict[str, str] = {}
        for mod_c in _iter_containers_by_def(pdur_cfg, "PduRBswModules"):
            target_leaf = _ref_leaf(mod_c, "PduRBswModuleRef") or mod_c.short_name
            bsw_mod_by_name[mod_c.short_name] = target_leaf

        # Map CanIf CAN IDs by lower PDU leaf for quick cross-reference
        can_id_by_pdu: Dict[str, str] = {}
        for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfTxPduCfg"):
            leaf = _ref_leaf(c, "CanIfTxPduRef")
            cid = _param_int(c, "CanIfTxPduCanId")
            cid_t = _param_str(c, "CanIfTxPduCanIdType", "STANDARD_CAN")
            if leaf and cid is not None:
                can_id_by_pdu[leaf] = f"0x{cid:08X}" if "EXTENDED" in cid_t else f"0x{cid:03X}"
        for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfRxPduCfg"):
            leaf = _ref_leaf(c, "CanIfRxPduRef")
            cid = _param_int(c, "CanIfRxPduCanId")
            cid_t = _param_str(c, "CanIfRxPduCanIdType", "STANDARD_CAN")
            if leaf and cid is not None:
                can_id_by_pdu[leaf] = f"0x{cid:08X}" if "EXTENDED" in cid_t else f"0x{cid:03X}"

        rows: List[PduRRoutingRow] = []
        for path_c in _iter_containers_by_def(pdur_cfg, "PduRRoutingPath"):
            comm_type = _param_str(path_c, "PduRRoutingPathCommunicationType", "COMMUNICATION_INTERFACE")
            src_c = None
            dest_c = None
            for sub in getattr(path_c, "sub_containers", []) or []:
                leaf = _ar_leaf(getattr(sub, "definition_ref", None))
                if leaf == "PduRSrcPdu" and src_c is None:
                    src_c = sub
                elif leaf == "PduRDestPdu" and dest_c is None:
                    dest_c = sub

            src_mod_raw = _ref_leaf(src_c, "PduRSrcPduPduRBswModulesRef")
            dest_mod_raw = _ref_leaf(dest_c, "PduRDestPduPduRBswModulesRef")
            src_mod = bsw_mod_by_name.get(src_mod_raw, src_mod_raw)
            dest_mod = bsw_mod_by_name.get(dest_mod_raw, dest_mod_raw)

            src_pdu = _ref_leaf(src_c, "PduRSrcPduRef")
            dest_pdu = _ref_leaf(dest_c, "PduRDestPduRef")

            direction = _param_str(src_c, "PduRSrcPduDirection", "") or _param_str(dest_c, "PduRDestPduDirection", "")
            if not direction:
                if dest_mod == "CanIf":
                    direction = "TRANSMIT"
                elif src_mod == "CanIf":
                    direction = "RECEIVE"

            broken = False
            if self._cfg("EcuC") is not None:
                if (src_pdu and src_pdu not in ecuc_pdus) or (dest_pdu and dest_pdu not in ecuc_pdus):
                    broken = True
            if not src_pdu or not dest_pdu:
                broken = True

            can_hex = can_id_by_pdu.get(src_pdu) or can_id_by_pdu.get(dest_pdu) or "-"
            rows.append(
                PduRRoutingRow(
                    path_name=path_c.short_name,
                    comm_type=comm_type,
                    direction=direction,
                    src_module=src_mod,
                    src_pdu_name=src_pdu,
                    src_handle_id=_param_int(src_c, "PduRSourcePduHandleId"),
                    dest_module=dest_mod,
                    dest_pdu_name=dest_pdu,
                    dest_handle_id=_param_int(dest_c, "PduRDestPduHandleId"),
                    can_id_hex=can_hex,
                    has_broken_ref=broken,
                    container_path=_container_path("PduR", path_c),
                )
            )
        rows.sort(key=lambda r: (r.direction, r.path_name))
        return rows

    # ------------------------------------------------------------------
    # Interactive Edits & HandleId Recompute
    # ------------------------------------------------------------------

    def update_message_properties(
        self,
        canif_pdu_name: Optional[str],
        com_ipdu_name: Optional[str],
        *,
        can_id: Optional[int] = None,
        can_id_type: Optional[str] = None,
        dlc: Optional[int] = None,
        tx_mode: Optional[str] = None,
        cycle_time_ms: Optional[float] = None,
    ) -> None:
        """Update CAN ID/type/DLC (synced with linked EcuC PDUs) and ComTxMode/period."""
        canif_c: Optional[EcucContainerValue] = None
        is_tx_canif = True
        if canif_pdu_name:
            for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfTxPduCfg"):
                if c.short_name == canif_pdu_name:
                    canif_c = c
                    is_tx_canif = True
                    break
            if canif_c is None:
                for c in _iter_containers_by_def(self._cfg("CanIf"), "CanIfRxPduCfg"):
                    if c.short_name == canif_pdu_name:
                        canif_c = c
                        is_tx_canif = False
                        break

        com_c: Optional[EcucContainerValue] = None
        if com_ipdu_name:
            for c in _iter_containers_by_def(self._cfg("Com"), "ComIPdu"):
                if c.short_name == com_ipdu_name:
                    com_c = c
                    break

        if canif_c is not None:
            if can_id is not None:
                parsed_id = can_id if isinstance(can_id, int) else _parse_int(can_id)
                if parsed_id is None:
                    raise ValueError(f"无效的 CAN ID: {can_id!r}")
                pname = "CanIfTxPduCanId" if is_tx_canif else "CanIfRxPduCanId"
                self._set_param("CanIf", canif_c, pname, parsed_id, "ECUC-INTEGER-PARAM-DEF")
            if can_id_type is not None:
                pname = "CanIfTxPduCanIdType" if is_tx_canif else "CanIfRxPduCanIdType"
                self._set_param("CanIf", canif_c, pname, can_id_type.strip(), "ECUC-ENUMERATION-PARAM-DEF")
            if dlc is not None:
                pname = "CanIfTxPduDlc" if is_tx_canif else "CanIfRxPduDlc"
                self._set_param("CanIf", canif_c, pname, int(dlc), "ECUC-INTEGER-PARAM-DEF")

        if dlc is not None:
            ecuc_pdus = self._index_ecuc_pdus()
            linked_leaves: Set[str] = set()
            if canif_c is not None:
                lower = _ref_leaf(canif_c, "CanIfTxPduRef" if is_tx_canif else "CanIfRxPduRef")
                if lower:
                    linked_leaves.add(lower)
            if com_c is not None:
                upper = _ref_leaf(com_c, "ComPduIdRef")
                if upper:
                    linked_leaves.add(upper)
            for leaf in linked_leaves:
                epdu = ecuc_pdus.get(leaf)
                if epdu is not None:
                    self._set_param("EcuC", epdu, "PduLength", int(dlc), "ECUC-INTEGER-PARAM-DEF")

        if com_c is not None and (tx_mode is not None or cycle_time_ms is not None):
            self._apply_com_tx_timing(com_c, tx_mode=tx_mode, cycle_time_ms=cycle_time_ms)

    def _apply_com_tx_timing(
        self,
        com_c: EcucContainerValue,
        *,
        tx_mode: Optional[str] = None,
        cycle_time_ms: Optional[float] = None,
    ) -> None:
        base_com = self._module_base_def("Com")
        tx_ipdu = next(
            (s for s in getattr(com_c, "sub_containers", []) or [] if _ar_leaf(getattr(s, "definition_ref", None)) == "ComTxIPdu"),
            None,
        )
        if tx_ipdu is None:
            self._check_editable("Com", com_c, None)
            tx_ipdu = EcucContainerValue(
                short_name="ComTxIPdu",
                definition_ref=f"{base_com}/ComConfig/ComIPdu/ComTxIPdu",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            com_c.add_sub_container(tx_ipdu)
            self._mark_modified("Com")

        tm_true = next(
            (s for s in getattr(tx_ipdu, "sub_containers", []) or [] if _ar_leaf(getattr(s, "definition_ref", None)) == "ComTxModeTrue"),
            None,
        )
        if tm_true is None:
            self._check_editable("Com", tx_ipdu, None)
            tm_true = EcucContainerValue(
                short_name="ComTxModeTrue",
                definition_ref=f"{base_com}/ComConfig/ComIPdu/ComTxIPdu/ComTxModeTrue",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            tx_ipdu.add_sub_container(tm_true)
            self._mark_modified("Com")

        tm = next(
            (s for s in getattr(tm_true, "sub_containers", []) or [] if _ar_leaf(getattr(s, "definition_ref", None)) == "ComTxMode"),
            None,
        )
        if tm is None:
            self._check_editable("Com", tm_true, None)
            tm = EcucContainerValue(
                short_name="ComTxMode",
                definition_ref=f"{base_com}/ComConfig/ComIPdu/ComTxIPdu/ComTxModeTrue/ComTxMode",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            tm_true.add_sub_container(tm)
            self._mark_modified("Com")

        if tx_mode is not None:
            self._set_param("Com", tm, "ComTxModeMode", tx_mode.strip(), "ECUC-ENUMERATION-PARAM-DEF")
        if cycle_time_ms is not None:
            self._set_param(
                "Com",
                tm,
                "ComTxModeTimePeriod",
                round(float(cycle_time_ms) / 1000.0, 6),
                "ECUC-FLOAT-PARAM-DEF",
            )

    def update_signal_properties(
        self,
        signal_name: str,
        *,
        bit_position: Optional[int] = None,
        bit_size: Optional[int] = None,
        endianness: Optional[str] = None,
        signal_type: Optional[str] = None,
        init_value: Optional[str] = None,
        transfer_property: Optional[str] = None,
        timeout_sec: Optional[float] = None,
    ) -> EcucContainerValue:
        """Update layout, type, init value, transfer property, or timeout on a ComSignal."""
        sig = next(
            (c for c in _iter_containers_by_def(self._cfg("Com"), "ComSignal") if c.short_name == signal_name),
            None,
        )
        if sig is None:
            raise ValueError(f"未找到 ComSignal '{signal_name}'")
        if bit_position is not None:
            self._set_param("Com", sig, "ComBitPosition", int(bit_position), "ECUC-INTEGER-PARAM-DEF")
        if bit_size is not None:
            self._set_param("Com", sig, "ComBitSize", int(bit_size), "ECUC-INTEGER-PARAM-DEF")
        if endianness is not None:
            self._set_param("Com", sig, "ComSignalEndianness", endianness.strip(), "ECUC-ENUMERATION-PARAM-DEF")
        if signal_type is not None:
            self._set_param("Com", sig, "ComSignalType", signal_type.strip(), "ECUC-ENUMERATION-PARAM-DEF")
        if init_value is not None:
            self._set_param("Com", sig, "ComSignalInitValue", str(init_value).strip(), "ECUC-STRING-PARAM-DEF")
        if transfer_property is not None:
            self._set_param("Com", sig, "ComTransferProperty", transfer_property.strip(), "ECUC-ENUMERATION-PARAM-DEF")
        if timeout_sec is not None:
            if timeout_sec <= 0:
                if "ComTimeout" in sig.parameter_values:
                    self._check_editable("Com", sig, "ComTimeout")
                    sig.remove_parameter_value("ComTimeout")
                    self._mark_modified("Com")
            else:
                self._set_param("Com", sig, "ComTimeout", float(timeout_sec), "ECUC-FLOAT-PARAM-DEF")
        return sig

    def _find_or_create_pdur_table(self) -> Tuple[EcucContainerValue, EcucContainerValue]:
        pdur_cfg = self._cfg("PduR")
        if pdur_cfg is None:
            raise ValueError("当前工程未加载 PduR 模块")
        base = self._module_base_def("PduR")
        tables = next(
            (_iter_containers_by_def(pdur_cfg, "PduRRoutingTables").__iter__()),
            None,
        )
        if tables is None:
            self._check_editable("PduR", pdur_cfg, None)
            tables = EcucContainerValue(
                short_name="PduRRoutingTables",
                definition_ref=f"{base}/PduRRoutingTables",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            pdur_cfg.add_container(tables)
            self._mark_modified("PduR")
        table = next(
            (s for s in getattr(tables, "sub_containers", []) or [] if _ar_leaf(getattr(s, "definition_ref", None)) == "PduRRoutingTable"),
            None,
        )
        if table is None:
            self._check_editable("PduR", tables, None)
            table = EcucContainerValue(
                short_name="PduRRoutingTable",
                definition_ref=f"{base}/PduRRoutingTables/PduRRoutingTable",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            tables.add_sub_container(table)
            self._mark_modified("PduR")
        return tables, table

    def _pdur_bsw_module_ref_path(self, mod_name: str) -> Optional[str]:
        pdur_cfg = self._cfg("PduR")
        if pdur_cfg is None or not mod_name:
            return None
        for mod_c in _iter_containers_by_def(pdur_cfg, "PduRBswModules"):
            target = _ref_leaf(mod_c, "PduRBswModuleRef") or mod_c.short_name
            if mod_c.short_name == mod_name or target == mod_name:
                return self._container_ref_path("PduR", mod_c)
        return None

    def add_pdur_routing_path(
        self,
        path_name: str,
        src_module: str,
        src_pdu_leaf: str,
        dest_module: str,
        dest_pdu_leaf: str,
        *,
        comm_type: str = "COMMUNICATION_INTERFACE",
        direction: str = "TRANSMIT",
    ) -> EcucContainerValue:
        """Create a new PduRRoutingPath container with PduRSrcPdu & PduRDestPdu."""
        tables, table = self._find_or_create_pdur_table()
        for existing in _iter_containers_by_def(self._cfg("PduR"), "PduRRoutingPath"):
            if existing.short_name == path_name:
                raise ValueError(f"PduRRoutingPath '{path_name}' 已存在")

        base = self._module_base_def("PduR")
        self._check_editable("PduR", table, None)
        path_c = EcucContainerValue(
            short_name=path_name,
            definition_ref=f"{base}/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        table.add_sub_container(path_c)
        try:
            self._set_param("PduR", path_c, "PduRRoutingPathCommunicationType", comm_type, "ECUC-ENUMERATION-PARAM-DEF")
            lock_c = next((s for s in getattr(tables, "sub_containers", []) or [] if _ar_leaf(getattr(s, "definition_ref", None)) == "PduRLock"), None)
            if lock_c is not None:
                self._set_ref("PduR", path_c, "PduRLockRef", self._container_ref_path("PduR", lock_c))

            src_c = EcucContainerValue(
                short_name=f"PduRSrc_{src_pdu_leaf}",
                definition_ref=f"{base}/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRSrcPdu",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            path_c.add_sub_container(src_c)
            self._set_param("PduR", src_c, "PduRSrcPduDirection", direction, "ECUC-ENUMERATION-PARAM-DEF")
            self._set_ref("PduR", src_c, "PduRSrcPduRef", self._ref_prefix("EcuC", f"EcucPduCollection/{src_pdu_leaf}"))
            src_mod_ref = self._pdur_bsw_module_ref_path(src_module)
            if src_mod_ref:
                self._set_ref("PduR", src_c, "PduRSrcPduPduRBswModulesRef", src_mod_ref)

            dest_c = EcucContainerValue(
                short_name=dest_pdu_leaf,
                definition_ref=f"{base}/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRDestPdu",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            path_c.add_sub_container(dest_c)
            self._set_param("PduR", dest_c, "PduRDestPduDirection", direction, "ECUC-ENUMERATION-PARAM-DEF")
            self._set_ref("PduR", dest_c, "PduRDestPduRef", self._ref_prefix("EcuC", f"EcucPduCollection/{dest_pdu_leaf}"))
            dest_mod_ref = self._pdur_bsw_module_ref_path(dest_module)
            if dest_mod_ref:
                self._set_ref("PduR", dest_c, "PduRDestPduPduRBswModulesRef", dest_mod_ref)
        except PreLockedError:
            table.remove_sub_container(path_c)
            raise

        self._mark_modified("PduR")
        self._refresh_project_references()
        return path_c

    def update_pdur_routing_path(
        self,
        path_name: str,
        *,
        src_module: Optional[str] = None,
        dest_module: Optional[str] = None,
        comm_type: Optional[str] = None,
    ) -> EcucContainerValue:
        path_c = next(
            (c for c in _iter_containers_by_def(self._cfg("PduR"), "PduRRoutingPath") if c.short_name == path_name),
            None,
        )
        if path_c is None:
            raise ValueError(f"未找到 PduRRoutingPath '{path_name}'")
        if comm_type is not None:
            self._set_param("PduR", path_c, "PduRRoutingPathCommunicationType", comm_type, "ECUC-ENUMERATION-PARAM-DEF")
        for sub in getattr(path_c, "sub_containers", []) or []:
            leaf = _ar_leaf(getattr(sub, "definition_ref", None))
            if leaf == "PduRSrcPdu" and src_module is not None:
                mref = self._pdur_bsw_module_ref_path(src_module)
                if mref:
                    self._set_ref("PduR", sub, "PduRSrcPduPduRBswModulesRef", mref)
            elif leaf == "PduRDestPdu" and dest_module is not None:
                mref = self._pdur_bsw_module_ref_path(dest_module)
                if mref:
                    self._set_ref("PduR", sub, "PduRDestPduPduRBswModulesRef", mref)
        self._refresh_project_references()
        return path_c

    def remove_pdur_routing_path(self, path_name: str) -> bool:
        pdur_cfg = self._cfg("PduR")
        if pdur_cfg is None:
            return False
        path_c = next(
            (c for c in _iter_containers_by_def(pdur_cfg, "PduRRoutingPath") if c.short_name == path_name),
            None,
        )
        if path_c is None or getattr(path_c, "parent", None) is None:
            return False
        self._check_editable("PduR", path_c, None)
        path_c.parent.remove_sub_container(path_c)
        if hasattr(self.project, "unregister_container_references"):
            self.project.unregister_container_references(path_c)
        self._mark_modified("PduR")
        self._refresh_project_references()
        return True

    def recompute_handle_ids(self, modules: Iterable[str] = ("CanIf", "PduR", "Com")) -> Dict[str, int]:
        """Re-assign dense 0..N-1 HandleIds across loaded CanIf, PduR, and Com containers."""
        mod_set = set(modules)
        counts: Dict[str, int] = {}

        def _assign_seq(mod: str, containers: List[EcucContainerValue], param_name: str) -> int:
            changed = 0
            for idx, c in enumerate(containers):
                cur = _param_int(c, param_name)
                if cur == idx:
                    continue
                try:
                    self._set_param(mod, c, param_name, idx, "ECUC-INTEGER-PARAM-DEF")
                    changed += 1
                except PreLockedError:
                    continue
            return changed

        if "CanIf" in mod_set and self._cfg("CanIf") is not None:
            canif_cfg = self._cfg("CanIf")
            tx_cnt = _assign_seq("CanIf", list(_iter_containers_by_def(canif_cfg, "CanIfTxPduCfg")), "CanIfTxPduId")
            rx_cnt = _assign_seq("CanIf", list(_iter_containers_by_def(canif_cfg, "CanIfRxPduCfg")), "CanIfRxPduId")
            counts["CanIf"] = tx_cnt + rx_cnt

        if "PduR" in mod_set and self._cfg("PduR") is not None:
            pdur_cfg = self._cfg("PduR")
            src_cnt = _assign_seq("PduR", list(_iter_containers_by_def(pdur_cfg, "PduRSrcPdu")), "PduRSourcePduHandleId")
            dst_cnt = _assign_seq("PduR", list(_iter_containers_by_def(pdur_cfg, "PduRDestPdu")), "PduRDestPduHandleId")
            counts["PduR"] = src_cnt + dst_cnt

        if "Com" in mod_set and self._cfg("Com") is not None:
            com_cfg = self._cfg("Com")
            ipdu_cnt = _assign_seq("Com", list(_iter_containers_by_def(com_cfg, "ComIPdu")), "ComIPduHandleId")
            sig_cnt = _assign_seq("Com", list(_iter_containers_by_def(com_cfg, "ComSignal")), "ComHandleId")
            counts["Com"] = ipdu_cnt + sig_cnt

        return counts

    # ------------------------------------------------------------------
    # Cross-Module Validation Diagnostics (10 rules)
    # ------------------------------------------------------------------

    def collect_diagnostics(self) -> List[CommDiagnostic]:
        """Collect all 10 communication stack diagnostics across tabs 0..3."""
        if not self.has_comm_modules():
            return []

        diags: List[CommDiagnostic] = []

        # 1. CHANNEL_BROKEN_LINK (Tab 0)
        for ch in self.list_channel_rows():
            if ch.has_broken_link:
                mod_name = "ComM" if ch.primary_container_path.startswith("/ComM/") else "CanIf"
                diags.append(
                    CommDiagnostic(
                        severity="warning",
                        code="CHANNEL_BROKEN_LINK",
                        message=f"通信通道 '{ch.channel_name}' 的 ComM / CanSM / CanIf / Can 关联链路不完整",
                        module_name=mod_name,
                        container_path=ch.primary_container_path,
                        workbench_tab=0,
                        suggested_fix="在通信工作台页签 1 检查 CanIfCtrlCanCtrlRef 或 CanSMComMNetworkHandleRef 引用",
                    )
                )

        messages = self.list_message_rows()

        # 2. CAN_ID_DUPLICATE (Tab 1) - grouped per (direction, channel, is_extended, can_id)
        seen_ids: Dict[Tuple[str, str, bool, int], List[CommMessageRow]] = {}
        for m in messages:
            if not m.canif_pdu_name or m.can_id is None:
                continue
            is_ext = "EXTENDED" in (m.can_id_type or "").upper()
            seen_ids.setdefault((m.direction, m.channel_name or "", is_ext, m.can_id), []).append(m)
        for (_dir, _ch, _ext, _cid), dup_list in seen_ids.items():
            if len(dup_list) <= 1:
                continue
            names = ", ".join(x.canif_pdu_name for x in dup_list[:4])
            first = dup_list[0]
            diags.append(
                CommDiagnostic(
                    severity="error",
                    code="CAN_ID_DUPLICATE",
                    message=f"CanIf {first.direction} 报文存在重复 CAN ID {first.can_id_hex}：{names}",
                    module_name="CanIf",
                    container_path=first.canif_pdu_path or "/CanIf",
                    parameter_name="CanIfTxPduCanId" if first.direction == "TX" else "CanIfRxPduCanId",
                    workbench_tab=1,
                    suggested_fix="在通信工作台页签 2 修改冲突报文的 CAN ID 或帧格式（标准帧/扩展帧）",
                )
            )

        # 3. PDU_LENGTH_MISMATCH, 4. COM_ORPHAN_IPDU, 5. CANIF_ORPHAN_PDU, 6. COM_TX_PERIOD_ZERO (Tab 1)
        for m in messages:
            if m.has_length_mismatch:
                diags.append(
                    CommDiagnostic(
                        severity="warning",
                        code="PDU_LENGTH_MISMATCH",
                        message=(
                            f"报文 '{m.name}' 长度不一致：CanIf DLC={m.canif_dlc}, "
                            f"EcuC下层={m.ecuc_lower_length}, EcuC上层={m.ecuc_upper_length}"
                        ),
                        module_name="CanIf" if m.canif_pdu_path else "Com",
                        container_path=m.canif_pdu_path or m.com_ipdu_path or "/CanIf",
                        parameter_name="CanIfTxPduDlc" if m.direction == "TX" else "CanIfRxPduDlc",
                        workbench_tab=1,
                        suggested_fix="在通信工作台页签 2 重新应用 DLC 以同步 EcuC PduLength",
                    )
                )
            if m.category == "ORPHAN" and m.com_ipdu_name and not m.canif_pdu_name and self._cfg("CanIf") is not None:
                diags.append(
                    CommDiagnostic(
                        severity="warning",
                        code="COM_ORPHAN_IPDU",
                        message=f"ComIPdu '{m.com_ipdu_name}' 未关联到 CanIf / PduR 链路",
                        module_name="Com",
                        container_path=m.com_ipdu_path or f"/Com/ComConfig/{m.com_ipdu_name}",
                        parameter_name="ComPduIdRef",
                        workbench_tab=1,
                        suggested_fix="检查 PduRRoutingPath 与 CanIf PDU 引用，或通过页签 5 DBC 同步补全",
                    )
                )
            elif m.category == "ORPHAN" and m.canif_pdu_name and not m.com_ipdu_name:
                diags.append(
                    CommDiagnostic(
                        severity="warning",
                        code="CANIF_ORPHAN_PDU",
                        message=f"CanIf PDU '{m.canif_pdu_name}' 未关联上层 ComIPdu / CanTp NSDU",
                        module_name="CanIf",
                        container_path=m.canif_pdu_path,
                        parameter_name="CanIfTxPduRef" if m.direction == "TX" else "CanIfRxPduRef",
                        workbench_tab=1,
                        suggested_fix="补全 PduRRoutingPath 与 ComIPdu 或检查 UserRxIndicationUL/TxConfirmationUL",
                    )
                )
            if (
                m.direction == "TX"
                and m.com_ipdu_name
                and m.tx_mode.upper() in ("PERIODIC", "MIXED")
                and (m.cycle_time_ms is None or m.cycle_time_ms <= 0)
            ):
                diags.append(
                    CommDiagnostic(
                        severity="warning",
                        code="COM_TX_PERIOD_ZERO",
                        message=f"TX ComIPdu '{m.com_ipdu_name}' 发送模式为 {m.tx_mode} 但周期 ComTxModeTimePeriod <= 0",
                        module_name="Com",
                        container_path=m.com_ipdu_path,
                        parameter_name="ComTxModeTimePeriod",
                        workbench_tab=1,
                        suggested_fix="在通信工作台页签 2 设置合理的发送周期 (ms)",
                    )
                )

        # 7. PDUR_BROKEN_CHAIN (Tab 3)
        for rr in self.list_pdur_routing_rows():
            if rr.has_broken_ref:
                diags.append(
                    CommDiagnostic(
                        severity="warning",
                        code="PDUR_BROKEN_CHAIN",
                        message=f"PduRRoutingPath '{rr.path_name}' 的源/目的 EcuC PDU 引用缺失或悬空",
                        module_name="PduR",
                        container_path=rr.container_path,
                        workbench_tab=3,
                        suggested_fix="在通信工作台页签 4 核对源/目的模块及 EcuC PDU 引用",
                    )
                )

        # 8. SIGNAL_BIT_OVERLAP & 9. SIGNAL_OUT_OF_BOUNDS (Tab 2)
        for sig in self.list_signal_rows():
            if sig.has_overlap:
                diags.append(
                    CommDiagnostic(
                        severity="error",
                        code="SIGNAL_BIT_OVERLAP",
                        message=f"信号 '{sig.signal_name}'（所属 {sig.ipdu_name}）与其他信号存在位域重叠",
                        module_name="Com",
                        container_path=sig.container_path,
                        parameter_name="ComBitPosition",
                        workbench_tab=2,
                        suggested_fix="在通信工作台页签 3 查看 8xN 帧位图并调整起始位或位长",
                    )
                )
            if sig.out_of_bounds:
                diags.append(
                    CommDiagnostic(
                        severity="error",
                        code="SIGNAL_OUT_OF_BOUNDS",
                        message=f"信号 '{sig.signal_name}'（所属 {sig.ipdu_name or '未挂载'}）位域超出所属报文 DLC 长度",
                        module_name="Com",
                        container_path=sig.container_path,
                        parameter_name="ComBitSize",
                        workbench_tab=2,
                        suggested_fix="在通信工作台页签 3 调整 ComBitPosition / ComBitSize 或增大报文 DLC",
                    )
                )

        # 10. HANDLE_ID_DUPLICATE (Tab 1)
        def _check_dup_hid(mod: str, containers: Iterable[EcucContainerValue], pname: str, label: str) -> None:
            by_id: Dict[int, List[EcucContainerValue]] = {}
            for c in containers:
                hid = _param_int(c, pname)
                if hid is not None:
                    by_id.setdefault(hid, []).append(c)
            for hid, items in sorted(by_id.items()):
                if len(items) > 1:
                    first = items[0]
                    diags.append(
                        CommDiagnostic(
                            severity="error",
                            code="HANDLE_ID_DUPLICATE",
                            message=f"{label}存在重复句柄 {pname}={hid}（共 {len(items)} 项，含 {first.short_name}）",
                            module_name=mod,
                            container_path=_container_path(mod, first),
                            parameter_name=pname,
                            workbench_tab=1,
                            suggested_fix="在通信工作台页签 2 点击「一键重排 HandleId」自动修复",
                        )
                    )

        if self._cfg("CanIf") is not None:
            _check_dup_hid("CanIf", _iter_containers_by_def(self._cfg("CanIf"), "CanIfTxPduCfg"), "CanIfTxPduId", "CanIf TX ")
            _check_dup_hid("CanIf", _iter_containers_by_def(self._cfg("CanIf"), "CanIfRxPduCfg"), "CanIfRxPduId", "CanIf RX ")
        if self._cfg("PduR") is not None:
            _check_dup_hid("PduR", _iter_containers_by_def(self._cfg("PduR"), "PduRSrcPdu"), "PduRSourcePduHandleId", "PduR Src ")
            _check_dup_hid("PduR", _iter_containers_by_def(self._cfg("PduR"), "PduRDestPdu"), "PduRDestPduHandleId", "PduR Dest ")
        if self._cfg("Com") is not None:
            _check_dup_hid("Com", _iter_containers_by_def(self._cfg("Com"), "ComIPdu"), "ComIPduHandleId", "ComIPdu ")
            _check_dup_hid("Com", _iter_containers_by_def(self._cfg("Com"), "ComSignal"), "ComHandleId", "ComSignal ")

        return diags
