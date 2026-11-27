"""Non-destructive preview and multi-module derivation from DBC databases to ECUC."""

import re
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

from ..config_manager import PreLockedError
from ..importers.dbc_importer import DbcMessage, DbcParser, DbcSignal
from ..model.configuration_model import EcucContainerValue
from .models import DbcSyncItem, DbcSyncPlan, DbcSyncResult
from .service import (
    CommunicationWorkbenchService,
    _ar_leaf,
    _iter_containers_by_def,
    _param_int,
    _param_str,
)


def _sanitize_id(name: str) -> str:
    cleaned = re.sub(r"[^A-Za-z0-9_]", "_", (name or "").strip())
    return cleaned or "Unnamed"


def _strip_davinci_pdu_suffix(name: str) -> str:
    # Matches e.g. MCU_Temp_0x227_oMotorDomain_6bf380d4_Tx -> MCU_Temp_0x227
    s = re.sub(r"_(?:Tx|Rx)$", "", name or "")
    s = re.sub(r"_o[^_]+(?:_[0-9a-fA-F]{6,12})?$", "", s)
    return s.lower()


def _infer_com_signal_type(sig: DbcSignal) -> str:
    if sig.length == 1:
        return "BOOLEAN"
    prefix = "SINT" if sig.value_type == "signed" else "UINT"
    if sig.length <= 8:
        return f"{prefix}8"
    if sig.length <= 16:
        return f"{prefix}16"
    if sig.length <= 32:
        return f"{prefix}32"
    return f"{prefix}64"


def _format_init_value(sig: DbcSignal) -> str:
    if sig.init_value is None:
        return "0"
    if abs(sig.init_value - round(sig.init_value)) < 1e-9:
        return str(int(round(sig.init_value)))
    return str(sig.init_value)


def _infer_transfer_property(direction: str, msg: DbcMessage, sig: DbcSignal) -> str:
    if direction != "TX":
        return "PENDING"
    st = (sig.send_type or msg.send_type or "").lower()
    if any(k in st for k in ("onwrite", "onchange", "event", "triggered")):
        return "TRIGGERED"
    return "PENDING"


def _can_id_type_for(msg: DbcMessage) -> str:
    if msg.is_fd:
        return "EXTENDED_FD_CAN" if msg.is_extended else "STANDARD_FD_CAN"
    return "EXTENDED_CAN" if msg.is_extended else "STANDARD_CAN"


def _infer_com_tx_mode(msg: DbcMessage) -> Tuple[str, float]:
    st = (msg.send_type or "").lower()
    if msg.cycle_time_ms is not None and msg.cycle_time_ms > 0:
        mode = "MIXED" if ("event" in st or "onwrite" in st or "ce" == st) else "PERIODIC"
        return mode, float(msg.cycle_time_ms)
    if "periodic" in st or "cyclic" in st:
        return "PERIODIC", 10.0
    return "DIRECT", 0.0


def plan_dbc_sync(
    project: Any,
    dbc_path: Path,
    *,
    ecu_node: str,
    channel_name: Optional[str] = None,
    include_diag: bool = False,
    update_existing: bool = True,
) -> DbcSyncPlan:
    """Parse ``dbc_path`` and preview multi-module ECUC creation/updates for ``ecu_node``."""
    svc = CommunicationWorkbenchService(project)
    db = DbcParser().parse_database(Path(dbc_path))

    target_modules = [m for m in ("EcuC", "CanIf", "PduR", "Com") if svc._cfg(m) is not None]
    missing_modules = [m for m in ("EcuC", "CanIf", "PduR", "Com") if m not in target_modules]

    warnings: List[str] = []
    if not ecu_node:
        warnings.append("未选择 ECU 节点（BU_），无法判断报文收发方向")

    existing_rows = svc.list_message_rows()
    by_id_key: Dict[Tuple[str, int, bool], Any] = {}
    by_name_key: Dict[Tuple[str, str], Any] = {}
    for row in existing_rows:
        if row.can_id is not None:
            is_ext = "EXTENDED" in (row.can_id_type or "").upper()
            by_id_key.setdefault((row.direction, row.can_id, is_ext), row)
        if row.name:
            by_name_key.setdefault((row.direction, _strip_davinci_pdu_suffix(row.name)), row)

    signals_by_name = {s.signal_name: s for s in svc.list_signal_rows()}

    items: List[DbcSyncItem] = []
    for msg in db.messages:
        is_tx = bool(ecu_node and msg.transmitter == ecu_node)
        is_rx = bool(ecu_node and any(ecu_node in sig.receivers for sig in msg.signals))
        directions: List[str] = []
        if is_tx:
            directions.append("TX")
        if is_rx and not is_tx:
            directions.append("RX")
        if not directions:
            continue

        for direction in directions:
            can_hex = f"0x{msg.id:08X}" if msg.is_extended else f"0x{msg.id:03X}"
            if msg.is_diag and not include_diag:
                items.append(
                    DbcSyncItem(
                        action="skip",
                        module_name="CanTp",
                        direction=direction,
                        category="DIAG_TP",
                        message_name=msg.name,
                        can_id=msg.id,
                        can_id_hex=can_hex,
                        is_extended=msg.is_extended,
                        dlc=msg.dlc,
                        cycle_time_ms=msg.cycle_time_ms,
                        signal_count=len(msg.signals),
                        target_summary="诊断 TP 报文（默认跳过）",
                        message_obj=msg,
                    )
                )
                continue

            match = by_id_key.get((direction, msg.id, msg.is_extended))
            if match is None:
                match = by_name_key.get((direction, _sanitize_id(msg.name).lower()))

            category = "DIAG_TP" if msg.is_diag else "COM"
            if match is None:
                if not target_modules:
                    action = "skip"
                    summary = "工程未加载 EcuC/CanIf/PduR/Com"
                else:
                    action = "create"
                    summary = f"新建 ({'+'.join(target_modules)}): {len(msg.signals)} 信号"
                items.append(
                    DbcSyncItem(
                        action=action,
                        module_name="+".join(target_modules) or "Com",
                        direction=direction,
                        category=category,
                        message_name=msg.name,
                        can_id=msg.id,
                        can_id_hex=can_hex,
                        is_extended=msg.is_extended,
                        dlc=msg.dlc,
                        cycle_time_ms=msg.cycle_time_ms,
                        signal_count=len(msg.signals),
                        target_summary=summary,
                        message_obj=msg,
                    )
                )
            else:
                diffs: List[str] = []
                if match.canif_dlc is not None and match.canif_dlc != msg.dlc:
                    diffs.append(f"DLC {match.canif_dlc}→{msg.dlc}")
                if direction == "TX" and msg.cycle_time_ms is not None and msg.cycle_time_ms > 0:
                    if match.cycle_time_ms is None or abs(match.cycle_time_ms - msg.cycle_time_ms) > 1e-3:
                        diffs.append(f"周期 {match.cycle_time_ms}→{msg.cycle_time_ms}ms")
                if match.com_ipdu_name:
                    ipdu_sigs = {
                        s.signal_name
                        for s in svc.list_signal_rows(ipdu_name=match.com_ipdu_name)
                    }
                    missing_sigs = 0
                    for s in msg.signals:
                        s_cand = _sanitize_id(s.name)
                        if s_cand not in ipdu_sigs and not any(
                            k.startswith(f"{s_cand}_o") or k == f"{s_cand}_{_sanitize_id(msg.name)}"
                            for k in ipdu_sigs
                        ):
                            missing_sigs += 1
                    if missing_sigs:
                        diffs.append(f"+{missing_sigs} 新信号")
                action = "update" if (diffs and update_existing) else "unchanged"
                summary = (
                    f"更新 ({', '.join(diffs)})"
                    if action == "update"
                    else (f"存在差异已保留 ({', '.join(diffs)})" if diffs else f"已匹配 ({match.name})")
                )
                items.append(
                    DbcSyncItem(
                        action=action,
                        module_name=match.com_ipdu_name and "CanIf+Com" or "CanIf",
                        direction=direction,
                        category=category,
                        message_name=msg.name,
                        can_id=msg.id,
                        can_id_hex=can_hex,
                        is_extended=msg.is_extended,
                        dlc=msg.dlc,
                        cycle_time_ms=msg.cycle_time_ms,
                        signal_count=len(msg.signals),
                        target_summary=summary,
                        existing_canif_pdu=match.canif_pdu_name,
                        existing_com_ipdu=match.com_ipdu_name,
                        existing_pdur_path=match.pdur_path_name,
                        existing_ecuc_lower_pdu=match.ecuc_lower_pdu_name,
                        existing_ecuc_upper_pdu=match.ecuc_upper_pdu_name,
                        message_obj=msg,
                    )
                )

    return DbcSyncPlan(
        dbc_path=Path(dbc_path),
        db_name=db.db_name,
        ecu_node=ecu_node,
        channel_name=channel_name,
        include_diag=include_diag,
        update_existing=update_existing,
        target_modules=target_modules,
        missing_modules=missing_modules,
        items=items,
        warnings=warnings,
    )


def apply_dbc_sync(project: Any, plan: DbcSyncPlan) -> DbcSyncResult:
    """Apply ``create`` and ``update`` actions from ``plan`` across EcuC/CanIf/PduR/Com."""
    svc = CommunicationWorkbenchService(project)
    result = DbcSyncResult()

    ecuc_cfg = svc._cfg("EcuC")
    canif_cfg = svc._cfg("CanIf")
    pdur_cfg = svc._cfg("PduR")
    com_cfg = svc._cfg("Com")

    # Locate/create helper parent containers upfront per module
    pdu_coll: Optional[EcucContainerValue] = None
    if ecuc_cfg is not None:
        pdu_coll = next(iter(_iter_containers_by_def(ecuc_cfg, "EcucPduCollection")), None)
        if pdu_coll is None:
            svc._check_editable("EcuC", ecuc_cfg, None)
            pdu_coll = EcucContainerValue(
                short_name="EcucPduCollection",
                definition_ref=f"{svc._module_base_def('EcuC')}/EcucPduCollection",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            ecuc_cfg.add_container(pdu_coll)
            svc._mark_modified("EcuC")

    canif_init: Optional[EcucContainerValue] = None
    default_buf: Optional[EcucContainerValue] = None
    default_hrh: Optional[EcucContainerValue] = None
    if canif_cfg is not None:
        canif_init = next(iter(_iter_containers_by_def(canif_cfg, "CanIfInitCfg")), None)
        if canif_init is None:
            svc._check_editable("CanIf", canif_cfg, None)
            canif_init = EcucContainerValue(
                short_name="CanIfInitCfg",
                definition_ref=f"{svc._module_base_def('CanIf')}/CanIfInitCfg",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            canif_cfg.add_container(canif_init)
            svc._mark_modified("CanIf")

        ch_rows = svc.list_channel_rows()
        chosen_ch = next((r for r in ch_rows if plan.channel_name and r.channel_name == plan.channel_name), ch_rows[0] if ch_rows else None)
        target_ctrl = chosen_ch.canif_ctrl_name if chosen_ch else ""

        hth_ctrl = {
            c.short_name: (c.reference_values.get("CanIfHthCanCtrlIdRef").value_ref.rsplit("/", 1)[-1]
                           if c.reference_values.get("CanIfHthCanCtrlIdRef") and c.reference_values.get("CanIfHthCanCtrlIdRef").value_ref else "")
            for c in _iter_containers_by_def(canif_cfg, "CanIfHthCfg")
        }
        bufs = list(_iter_containers_by_def(canif_cfg, "CanIfBufferCfg"))
        if target_ctrl:
            default_buf = next(
                (b for b in bufs if hth_ctrl.get(
                    b.reference_values.get("CanIfBufferHthRef").value_ref.rsplit("/", 1)[-1]
                    if b.reference_values.get("CanIfBufferHthRef") and b.reference_values.get("CanIfBufferHthRef").value_ref else ""
                ) == target_ctrl),
                bufs[0] if bufs else None,
            )
        else:
            default_buf = bufs[0] if bufs else None

        hrhs = list(_iter_containers_by_def(canif_cfg, "CanIfHrhCfg"))
        if target_ctrl:
            default_hrh = next(
                (h for h in hrhs if (
                    h.reference_values.get("CanIfHrhCanCtrlIdRef").value_ref.rsplit("/", 1)[-1]
                    if h.reference_values.get("CanIfHrhCanCtrlIdRef") and h.reference_values.get("CanIfHrhCanCtrlIdRef").value_ref else ""
                ) == target_ctrl),
                hrhs[0] if hrhs else None,
            )
        else:
            default_hrh = hrhs[0] if hrhs else None

    com_config: Optional[EcucContainerValue] = None
    com_mf_tx: Optional[EcucContainerValue] = None
    com_mf_rx: Optional[EcucContainerValue] = None
    com_grp_tx: Optional[EcucContainerValue] = None
    com_grp_rx: Optional[EcucContainerValue] = None
    if com_cfg is not None:
        com_config = next(iter(_iter_containers_by_def(com_cfg, "ComConfig")), None)
        if com_config is None:
            svc._check_editable("Com", com_cfg, None)
            com_config = EcucContainerValue(
                short_name="ComConfig",
                definition_ref=f"{svc._module_base_def('Com')}/ComConfig",
                def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
            )
            com_cfg.add_container(com_config)
            svc._mark_modified("Com")
        com_mf_tx = next(iter(_iter_containers_by_def(com_cfg, "ComMainFunctionTx")), None)
        com_mf_rx = next(iter(_iter_containers_by_def(com_cfg, "ComMainFunctionRx")), None)
        for grp in _iter_containers_by_def(com_cfg, "ComIPduGroup"):
            if "tx" in grp.short_name.lower() and com_grp_tx is None:
                com_grp_tx = grp
            elif "rx" in grp.short_name.lower() and com_grp_rx is None:
                com_grp_rx = grp

    ecuc_pdus = {c.short_name: c for c in _iter_containers_by_def(ecuc_cfg, "Pdu")}
    canif_tx_map = {c.short_name: c for c in _iter_containers_by_def(canif_cfg, "CanIfTxPduCfg")}
    canif_rx_map = {c.short_name: c for c in _iter_containers_by_def(canif_cfg, "CanIfRxPduCfg")}
    com_ipdu_map = {c.short_name: c for c in _iter_containers_by_def(com_cfg, "ComIPdu")}
    com_sig_map = {c.short_name: c for c in _iter_containers_by_def(com_cfg, "ComSignal")}
    pdur_path_map = {c.short_name: c for c in _iter_containers_by_def(pdur_cfg, "PduRRoutingPath")}

    def _ensure_ecuc_pdu(pdu_name: str, length: int) -> EcucContainerValue:
        existing = ecuc_pdus.get(pdu_name)
        if existing is not None:
            cur_len = _param_int(existing, "PduLength")
            if cur_len != length:
                svc._set_param("EcuC", existing, "PduLength", int(length), "ECUC-INTEGER-PARAM-DEF")
            return existing
        base_ecuc = svc._module_base_def("EcuC")
        svc._check_editable("EcuC", pdu_coll, None)
        new_pdu = EcucContainerValue(
            short_name=pdu_name,
            definition_ref=f"{base_ecuc}/EcucPduCollection/Pdu",
            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
        )
        pdu_coll.add_sub_container(new_pdu)
        svc._set_param("EcuC", new_pdu, "PduLength", int(length), "ECUC-INTEGER-PARAM-DEF")
        svc._set_param("EcuC", new_pdu, "DynamicLength", False, "ECUC-BOOLEAN-PARAM-DEF")
        ecuc_pdus[pdu_name] = new_pdu
        result.created_ecuc_pdus += 1
        return new_pdu

    for item in plan.items:
        if item.action not in ("create", "update") or item.message_obj is None:
            continue
        msg: DbcMessage = item.message_obj
        suffix = "Tx" if item.direction == "TX" else "Rx"
        safe_msg = f"{_sanitize_id(msg.name)}_{suffix}"
        can_id_type = _can_id_type_for(msg)

        try:
            # 1. EcuC PDUs
            lower_pdu_name = item.existing_ecuc_lower_pdu or (
                f"{safe_msg}_CanIf" if pdur_cfg is not None else safe_msg
            )
            upper_pdu_name = item.existing_ecuc_upper_pdu or (
                safe_msg if item.category == "COM" else f"{safe_msg}_Upper"
            )
            if pdu_coll is not None:
                _ensure_ecuc_pdu(lower_pdu_name, msg.dlc)
                if pdur_cfg is not None and upper_pdu_name != lower_pdu_name:
                    _ensure_ecuc_pdu(upper_pdu_name, msg.dlc)

            # 2. CanIf TX/RX PDU
            if canif_init is not None:
                base_canif = svc._module_base_def("CanIf")
                if item.direction == "TX":
                    cname = item.existing_canif_pdu or safe_msg
                    canif_c = canif_tx_map.get(cname)
                    created_c = canif_c is None
                    if canif_c is None:
                        svc._check_editable("CanIf", canif_init, None)
                        canif_c = EcucContainerValue(
                            short_name=cname,
                            definition_ref=f"{base_canif}/CanIfInitCfg/CanIfTxPduCfg",
                            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
                        )
                        canif_init.add_sub_container(canif_c)
                        canif_tx_map[cname] = canif_c
                    svc._set_param("CanIf", canif_c, "CanIfTxPduCanId", int(msg.id), "ECUC-INTEGER-PARAM-DEF")
                    svc._set_param("CanIf", canif_c, "CanIfTxPduCanIdType", can_id_type, "ECUC-ENUMERATION-PARAM-DEF")
                    svc._set_param("CanIf", canif_c, "CanIfTxPduDlc", int(msg.dlc), "ECUC-INTEGER-PARAM-DEF")
                    if created_c:
                        ul = "CAN_TP" if item.category == "DIAG_TP" else "PDUR"
                        cbk = "CanTp_TxConfirmation" if item.category == "DIAG_TP" else "PduR_CanIfTxConfirmation"
                        svc._set_param("CanIf", canif_c, "CanIfTxPduUserTxConfirmationUL", ul, "ECUC-ENUMERATION-PARAM-DEF")
                        svc._set_param("CanIf", canif_c, "CanIfTxPduUserTxConfirmationName", cbk, "ECUC-FUNCTION-NAME-DEF")
                        svc._set_param("CanIf", canif_c, "CanIfTxPduType", "STATIC", "ECUC-ENUMERATION-PARAM-DEF")
                        svc._set_ref("CanIf", canif_c, "CanIfTxPduRef", svc._ref_prefix("EcuC", f"EcucPduCollection/{lower_pdu_name}"))
                        if default_buf is not None:
                            svc._set_ref("CanIf", canif_c, "CanIfTxPduBufferRef", svc._container_ref_path("CanIf", default_buf))
                        result.created_canif_pdus += 1
                    else:
                        result.updated_canif_pdus += 1
                else:
                    cname = item.existing_canif_pdu or safe_msg
                    canif_c = canif_rx_map.get(cname)
                    created_c = canif_c is None
                    if canif_c is None:
                        svc._check_editable("CanIf", canif_init, None)
                        canif_c = EcucContainerValue(
                            short_name=cname,
                            definition_ref=f"{base_canif}/CanIfInitCfg/CanIfRxPduCfg",
                            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
                        )
                        canif_init.add_sub_container(canif_c)
                        canif_rx_map[cname] = canif_c
                    svc._set_param("CanIf", canif_c, "CanIfRxPduCanId", int(msg.id), "ECUC-INTEGER-PARAM-DEF")
                    svc._set_param("CanIf", canif_c, "CanIfRxPduCanIdType", can_id_type, "ECUC-ENUMERATION-PARAM-DEF")
                    svc._set_param("CanIf", canif_c, "CanIfRxPduDlc", int(msg.dlc), "ECUC-INTEGER-PARAM-DEF")
                    if created_c:
                        ul = "CAN_TP" if item.category == "DIAG_TP" else "PDUR"
                        cbk = "CanTp_RxIndication" if item.category == "DIAG_TP" else "PduR_CanIfRxIndication"
                        svc._set_param("CanIf", canif_c, "CanIfRxPduUserRxIndicationUL", ul, "ECUC-ENUMERATION-PARAM-DEF")
                        svc._set_param("CanIf", canif_c, "CanIfRxPduUserRxIndicationName", cbk, "ECUC-FUNCTION-NAME-DEF")
                        svc._set_param("CanIf", canif_c, "CanIfRxPduType", "STATIC", "ECUC-ENUMERATION-PARAM-DEF")
                        svc._set_ref("CanIf", canif_c, "CanIfRxPduRef", svc._ref_prefix("EcuC", f"EcucPduCollection/{lower_pdu_name}"))
                        if default_hrh is not None:
                            svc._set_ref("CanIf", canif_c, "CanIfRxPduHrhIdRef", svc._container_ref_path("CanIf", default_hrh))
                        result.created_canif_pdus += 1
                    else:
                        result.updated_canif_pdus += 1

            if item.category == "DIAG_TP":
                continue

            # 3. PduR routing path (Com <-> CanIf)
            if pdur_cfg is not None:
                pname = item.existing_pdur_path or safe_msg
                if pname not in pdur_path_map:
                    src_mod, src_pdu, dst_mod, dst_pdu, dir_kw = (
                        ("Com", upper_pdu_name, "CanIf", lower_pdu_name, "TRANSMIT")
                        if item.direction == "TX"
                        else ("CanIf", lower_pdu_name, "Com", upper_pdu_name, "RECEIVE")
                    )
                    new_rp = svc.add_pdur_routing_path(
                        pname, src_mod, src_pdu, dst_mod, dst_pdu, direction=dir_kw
                    )
                    pdur_path_map[pname] = new_rp
                    result.created_pdur_paths += 1

            # 4. ComIPdu & ComSignals
            if com_config is not None:
                base_com = svc._module_base_def("Com")
                com_name = item.existing_com_ipdu or safe_msg
                com_c = com_ipdu_map.get(com_name)
                created_ipdu = com_c is None
                if com_c is None:
                    svc._check_editable("Com", com_config, None)
                    com_c = EcucContainerValue(
                        short_name=com_name,
                        definition_ref=f"{base_com}/ComConfig/ComIPdu",
                        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
                    )
                    com_config.add_sub_container(com_c)
                    com_ipdu_map[com_name] = com_c
                    svc._set_param(
                        "Com",
                        com_c,
                        "ComIPduDirection",
                        "SEND" if item.direction == "TX" else "RECEIVE",
                        "ECUC-ENUMERATION-PARAM-DEF",
                    )
                    svc._set_param("Com", com_c, "ComIPduType", "NORMAL", "ECUC-ENUMERATION-PARAM-DEF")
                    svc._set_ref("Com", com_c, "ComPduIdRef", svc._ref_prefix("EcuC", f"EcucPduCollection/{upper_pdu_name}"))
                    ch_target = plan.channel_name or next(
                        (c.short_name for c in _iter_containers_by_def(svc._cfg("ComM"), "ComMChannel")), ""
                    )
                    if ch_target:
                        svc._set_ref("Com", com_c, "ComIPduChannelRef", svc._ref_prefix("ComM", f"ComMConfigSet/{ch_target}"))
                    grp = com_grp_tx if item.direction == "TX" else com_grp_rx
                    if grp is not None:
                        svc._set_ref("Com", com_c, "ComIPduGroupRef", svc._container_ref_path("Com", grp))
                    mf = com_mf_tx if item.direction == "TX" else com_mf_rx
                    if mf is not None:
                        svc._set_ref("Com", com_c, "ComIPduMainFunctionRef", svc._container_ref_path("Com", mf))
                    result.created_com_ipdus += 1
                else:
                    result.updated_com_ipdus += 1

                if item.direction == "TX":
                    tx_mode, cycle_ms = _infer_com_tx_mode(msg)
                    svc._apply_com_tx_timing(com_c, tx_mode=tx_mode, cycle_time_ms=cycle_ms if cycle_ms > 0 else None)

                existing_ipdu_sigs = {
                    _ar_leaf(r.value_ref): com_sig_map[_ar_leaf(r.value_ref)]
                    for r in (
                        list(com_c.reference_values.get("ComIPduSignalRef") and [com_c.reference_values["ComIPduSignalRef"]] or [])
                        + list(com_c.multi_reference_values.get("ComIPduSignalRef", []) or [])
                    )
                    if r.value_ref and _ar_leaf(r.value_ref) in com_sig_map
                }

                for sig in msg.signals:
                    base_sig = _sanitize_id(sig.name)
                    sig_c = (
                        existing_ipdu_sigs.get(base_sig)
                        or existing_ipdu_sigs.get(f"{base_sig}_{safe_msg}")
                        or next(
                            (
                                c
                                for k, c in existing_ipdu_sigs.items()
                                if k.startswith(f"{base_sig}_o")
                            ),
                            None,
                        )
                    )
                    if sig_c is None:
                        sig_name = base_sig if base_sig not in com_sig_map else f"{base_sig}_{safe_msg}"
                        if sig_name in com_sig_map and sig_name not in existing_ipdu_sigs:
                            counter = 2
                            while f"{sig_name}_{counter}" in com_sig_map:
                                counter += 1
                            sig_name = f"{sig_name}_{counter}"
                        svc._check_editable("Com", com_config, None)
                        sig_c = EcucContainerValue(
                            short_name=sig_name,
                            definition_ref=f"{base_com}/ComConfig/ComSignal",
                            def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
                        )
                        com_config.add_sub_container(sig_c)
                        com_sig_map[sig_name] = sig_c
                        created_sig = True
                    else:
                        created_sig = False

                    endian = "BIG_ENDIAN" if sig.byte_order == "big_endian" else "LITTLE_ENDIAN"
                    svc._set_param("Com", sig_c, "ComBitPosition", int(sig.start_bit), "ECUC-INTEGER-PARAM-DEF")
                    svc._set_param("Com", sig_c, "ComBitSize", int(sig.length), "ECUC-INTEGER-PARAM-DEF")
                    svc._set_param("Com", sig_c, "ComSignalEndianness", endian, "ECUC-ENUMERATION-PARAM-DEF")
                    svc._set_param("Com", sig_c, "ComSignalType", _infer_com_signal_type(sig), "ECUC-ENUMERATION-PARAM-DEF")
                    svc._set_param("Com", sig_c, "ComSignalInitValue", _format_init_value(sig), "ECUC-STRING-PARAM-DEF")
                    svc._set_param(
                        "Com",
                        sig_c,
                        "ComTransferProperty",
                        _infer_transfer_property(item.direction, msg, sig),
                        "ECUC-ENUMERATION-PARAM-DEF",
                    )
                    svc._append_ref("Com", com_c, "ComIPduSignalRef", svc._container_ref_path("Com", sig_c))
                    if created_sig:
                        result.created_com_signals += 1
                    else:
                        result.updated_com_signals += 1
        except PreLockedError as exc:
            result.skipped_locked.append(str(exc))

    svc.recompute_handle_ids()
    svc._refresh_project_references()
    return result
