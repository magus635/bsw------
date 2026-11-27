"""Unit tests for CommunicationWorkbenchService, DBC sync derivation, and CommunicationValidationRule."""

from pathlib import Path
from textwrap import dedent

import pytest

from autosar_configurator.core.communication import (
    CommunicationWorkbenchService,
    analyze_pdu_bit_layout,
    apply_dbc_sync,
    compute_signal_bits,
    plan_dbc_sync,
)
from autosar_configurator.core.config_manager import PreLockedError
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucReferenceValue,
)
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucModuleDef,
    EcucParameterDef,
    EcucReferenceDef,
)
from autosar_configurator.core.rules.communication_rules import CommunicationValidationRule
from autosar_configurator.core.validation_engine import ValidationEngine, ValidationSeverity
from autosar_configurator.core.workspace_manager import WorkspaceManager


def _add_container(parent, short_name: str, def_ref: str) -> EcucContainerValue:
    c = EcucContainerValue(
        short_name=short_name,
        definition_ref=def_ref,
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    if isinstance(parent, EcucModuleConfiguration):
        parent.add_container(c)
    else:
        parent.add_sub_container(c)
    return c


def _set_p(c: EcucContainerValue, name: str, val, dest_type: str = "ECUC-INTEGER-PARAM-DEF"):
    c.set_parameter_value(name, val, f"{c.definition_ref}/{name}")
    c.parameter_values[name].dest_type = dest_type


def _set_r(c: EcucContainerValue, name: str, val_ref: str):
    c.set_reference_value(name, val_ref, f"{c.definition_ref}/{name}")


def _append_r(c: EcucContainerValue, name: str, val_ref: str):
    idx = len(c.multi_reference_values.get(name, []))
    c.add_multi_reference_value(name, val_ref, f"{c.definition_ref}/{name}", idx)


def build_synthetic_comm_project(tmp_path: Path):
    """Create an 8-module CAN/ComM/CanSM/CanIf/CanTrcv/PduR/Com/EcuC project."""
    proj_dir = tmp_path / "comm_proj"
    proj_dir.mkdir(parents=True, exist_ok=True)
    ws = WorkspaceManager()
    project = ws.create_project("CommTestProj", proj_dir / "CommTestProj.dpa", format_version=8)

    mods = {}
    for mod in ("Can", "CanTrcv", "CanIf", "CanSM", "ComM", "PduR", "Com", "EcuC"):
        mdef = EcucModuleDef(mod, definition_ref=f"/MICROSAR/{mod}")
        mgr = project.add_module(mdef, proj_dir / "Config" / "ECUC" / f"{mod}.arxml")
        mods[mod] = mgr.configuration

    # --- Can ---
    can_cfg_set = _add_container(mods["Can"], "CanConfigSet", "/MICROSAR/Can/CanConfigSet")
    can_ctrl = _add_container(can_cfg_set, "CanController_0", "/MICROSAR/Can/CanConfigSet/CanController")
    _set_p(can_ctrl, "CanControllerId", 0)
    _set_p(can_ctrl, "CanControllerActivation", True, "ECUC-BOOLEAN-PARAM-DEF")
    _set_p(can_ctrl, "CanRxProcessing", "INTERRUPT", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(can_ctrl, "CanTxProcessing", "INTERRUPT", "ECUC-ENUMERATION-PARAM-DEF")
    baud_cfg = _add_container(can_ctrl, "CanControllerBaudrateConfig", "/MICROSAR/Can/CanConfigSet/CanController/CanControllerBaudrateConfig")
    _set_p(baud_cfg, "CanControllerBaudRate", 500, "ECUC-FLOAT-PARAM-DEF")
    fd_cfg = _add_container(baud_cfg, "CanControllerFdBaudrateConfig", "/MICROSAR/Can/CanConfigSet/CanController/CanControllerBaudrateConfig/CanControllerFdBaudrateConfig")
    _set_p(fd_cfg, "CanControllerFdBaudRate", 2000, "ECUC-FLOAT-PARAM-DEF")

    # --- CanTrcv ---
    trcv_set = _add_container(mods["CanTrcv"], "CanTrcvConfigSet", "/MICROSAR/CanTrcv/CanTrcvConfigSet")
    trcv_ch = _add_container(trcv_set, "CanTrcvChannel_0", "/MICROSAR/CanTrcv/CanTrcvConfigSet/CanTrcvChannel")
    _set_p(trcv_ch, "CanTrcvInitState", "CANTRCV_TRCVMODE_NORMAL", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(trcv_ch, "CanTrcvMaxBaudrate", 500, "ECUC-INTEGER-PARAM-DEF")

    # --- ComM ---
    comm_set = _add_container(mods["ComM"], "ComMConfigSet", "/MICROSAR/ComM/ComMConfigSet")
    comm_ch = _add_container(comm_set, "CN_CAN00", "/MICROSAR/ComM/ComMConfigSet/ComMChannel")
    _set_p(comm_ch, "ComMChannelId", 0)
    _set_p(comm_ch, "ComMBusType", "COMM_BUS_TYPE_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    nm_c = _add_container(comm_ch, "ComMNetworkManagement", "/MICROSAR/ComM/ComMConfigSet/ComMChannel/ComMNetworkManagement")
    _set_p(nm_c, "ComMNmVariant", "FULL", "ECUC-ENUMERATION-PARAM-DEF")

    # --- CanIf ---
    canif_ctrl_drv = _add_container(mods["CanIf"], "CanIfCtrlDrvCfg", "/MICROSAR/CanIf/CanIfCtrlDrvCfg")
    canif_ctrl = _add_container(canif_ctrl_drv, "CanIfCtrlCfg_0", "/MICROSAR/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg")
    _set_r(canif_ctrl, "CanIfCtrlCanCtrlRef", "/ActiveEcuC/Can/CanConfigSet/CanController_0")
    _set_r(canif_ctrl, "CanIfCtrlTrcvCfgRef", "/ActiveEcuC/CanIf/CanIfTrcvDrvCfg/CanIfTrcvCfg_0")

    canif_trcv_drv = _add_container(mods["CanIf"], "CanIfTrcvDrvCfg", "/MICROSAR/CanIf/CanIfTrcvDrvCfg")
    canif_trcv = _add_container(canif_trcv_drv, "CanIfTrcvCfg_0", "/MICROSAR/CanIf/CanIfTrcvDrvCfg/CanIfTrcvCfg")
    _set_r(canif_trcv, "CanIfTrcvCanTrcvRef", "/ActiveEcuC/CanTrcv/CanTrcvConfigSet/CanTrcvChannel_0")

    canif_init = _add_container(mods["CanIf"], "CanIfInitCfg", "/MICROSAR/CanIf/CanIfInitCfg")
    hth_drv = _add_container(canif_init, "CanIfInitHohCfg", "/MICROSAR/CanIf/CanIfInitCfg/CanIfInitHohCfg")
    hth = _add_container(hth_drv, "CanIfHthCfg_0", "/MICROSAR/CanIf/CanIfInitCfg/CanIfInitHohCfg/CanIfHthCfg")
    _set_r(hth, "CanIfHthCanCtrlIdRef", "/ActiveEcuC/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg_0")
    hrh = _add_container(hth_drv, "CanIfHrhCfg_0", "/MICROSAR/CanIf/CanIfInitCfg/CanIfInitHohCfg/CanIfHrhCfg")
    _set_r(hrh, "CanIfHrhCanCtrlIdRef", "/ActiveEcuC/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg_0")
    buf = _add_container(canif_init, "CanIfBufferCfg_0", "/MICROSAR/CanIf/CanIfInitCfg/CanIfBufferCfg")
    _set_r(buf, "CanIfBufferHthRef", "/ActiveEcuC/CanIf/CanIfInitCfg/CanIfInitHohCfg/CanIfHthCfg_0")

    # --- CanSM ---
    cansm_cfg = _add_container(mods["CanSM"], "CanSMConfiguration", "/MICROSAR/CanSM/CanSMConfiguration")
    cansm_net = _add_container(cansm_cfg, "CanSMManagerNetwork_0", "/MICROSAR/CanSM/CanSMConfiguration/CanSMManagerNetwork")
    _set_r(cansm_net, "CanSMComMNetworkHandleRef", "/ActiveEcuC/ComM/ComMConfigSet/CN_CAN00")
    cansm_ctrl = _add_container(cansm_net, "CanSMController_0", "/MICROSAR/CanSM/CanSMConfiguration/CanSMManagerNetwork/CanSMController")
    _set_r(cansm_ctrl, "CanSMControllerId", "/ActiveEcuC/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg_0")

    # --- EcuC ---
    ecuc_coll = _add_container(mods["EcuC"], "EcucPduCollection", "/MICROSAR/EcuC/EcucPduCollection")
    pdu_tx_low = _add_container(ecuc_coll, "MCU_Status_Tx_CanIf", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _set_p(pdu_tx_low, "PduLength", 8)
    pdu_tx_up = _add_container(ecuc_coll, "MCU_Status_Tx", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _set_p(pdu_tx_up, "PduLength", 8)

    pdu_rx_low = _add_container(ecuc_coll, "VCU_Cmd_Rx_CanIf", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _set_p(pdu_rx_low, "PduLength", 8)
    pdu_rx_up = _add_container(ecuc_coll, "VCU_Cmd_Rx", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _set_p(pdu_rx_up, "PduLength", 8)

    # --- CanIf PDUs ---
    tx_pdu = _add_container(canif_init, "MCU_Status_Tx", "/MICROSAR/CanIf/CanIfInitCfg/CanIfTxPduCfg")
    _set_p(tx_pdu, "CanIfTxPduCanId", 0x227)
    _set_p(tx_pdu, "CanIfTxPduCanIdType", "STANDARD_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(tx_pdu, "CanIfTxPduDlc", 8)
    _set_p(tx_pdu, "CanIfTxPduId", 0)
    _set_p(tx_pdu, "CanIfTxPduUserTxConfirmationUL", "PDUR", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(tx_pdu, "CanIfTxPduBufferRef", "/ActiveEcuC/CanIf/CanIfInitCfg/CanIfBufferCfg_0")
    _set_r(tx_pdu, "CanIfTxPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/MCU_Status_Tx_CanIf")

    rx_pdu = _add_container(canif_init, "VCU_Cmd_Rx", "/MICROSAR/CanIf/CanIfInitCfg/CanIfRxPduCfg")
    _set_p(rx_pdu, "CanIfRxPduCanId", 0x224)
    _set_p(rx_pdu, "CanIfRxPduCanIdType", "STANDARD_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(rx_pdu, "CanIfRxPduDlc", 8)
    _set_p(rx_pdu, "CanIfRxPduId", 0)
    _set_p(rx_pdu, "CanIfRxPduUserRxIndicationUL", "PDUR", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(rx_pdu, "CanIfRxPduHrhIdRef", "/ActiveEcuC/CanIf/CanIfInitCfg/CanIfInitHohCfg/CanIfHrhCfg_0")
    _set_r(rx_pdu, "CanIfRxPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/VCU_Cmd_Rx_CanIf")

    # --- PduR ---
    pdur_tables = _add_container(mods["PduR"], "PduRRoutingTables", "/MICROSAR/PduR/PduRRoutingTables")
    for bm in ("Com", "CanIf", "CanTp", "Dcm"):
        bm_c = _add_container(pdur_tables, bm, "/MICROSAR/PduR/PduRRoutingTables/PduRBswModules")
        _set_r(bm_c, "PduRBswModuleRef", f"/MICROSAR/{bm}")
    pdur_table = _add_container(pdur_tables, "PduRRoutingTable", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable")

    rp_tx = _add_container(pdur_table, "MCU_Status_Tx", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
    _set_p(rp_tx, "PduRRoutingPathCommunicationType", "COMMUNICATION_INTERFACE", "ECUC-ENUMERATION-PARAM-DEF")
    src_tx = _add_container(rp_tx, "PduRSrc_MCU_Status_Tx", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRSrcPdu")
    _set_p(src_tx, "PduRSrcPduHandleId", 0)
    _set_p(src_tx, "PduRSrcPduDirection", "TRANSMIT", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(src_tx, "PduRSrcPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/MCU_Status_Tx")
    _set_r(src_tx, "PduRSrcPduPduRBswModulesRef", "/ActiveEcuC/PduR/PduRRoutingTables/Com")
    dst_tx = _add_container(rp_tx, "MCU_Status_Tx_CanIf", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRDestPdu")
    _set_p(dst_tx, "PduRDestPduHandleId", 0)
    _set_p(dst_tx, "PduRDestPduDirection", "TRANSMIT", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(dst_tx, "PduRDestPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/MCU_Status_Tx_CanIf")
    _set_r(dst_tx, "PduRDestPduPduRBswModulesRef", "/ActiveEcuC/PduR/PduRRoutingTables/CanIf")

    rp_rx = _add_container(pdur_table, "VCU_Cmd_Rx", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
    _set_p(rp_rx, "PduRRoutingPathCommunicationType", "COMMUNICATION_INTERFACE", "ECUC-ENUMERATION-PARAM-DEF")
    src_rx = _add_container(rp_rx, "PduRSrc_VCU_Cmd_Rx", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRSrcPdu")
    _set_p(src_rx, "PduRSrcPduHandleId", 1)
    _set_p(src_rx, "PduRSrcPduDirection", "RECEIVE", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(src_rx, "PduRSrcPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/VCU_Cmd_Rx_CanIf")
    _set_r(src_rx, "PduRSrcPduPduRBswModulesRef", "/ActiveEcuC/PduR/PduRRoutingTables/CanIf")
    dst_rx = _add_container(rp_rx, "VCU_Cmd_Rx", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRDestPdu")
    _set_p(dst_rx, "PduRDestPduHandleId", 1)
    _set_p(dst_rx, "PduRDestPduDirection", "RECEIVE", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(dst_rx, "PduRDestPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/VCU_Cmd_Rx")
    _set_r(dst_rx, "PduRDestPduPduRBswModulesRef", "/ActiveEcuC/PduR/PduRRoutingTables/Com")

    # --- Com ---
    com_cfg = _add_container(mods["Com"], "ComConfig", "/MICROSAR/Com/ComConfig")
    sig_moto = _add_container(com_cfg, "MCU_MaxTrq_EST", "/MICROSAR/Com/ComConfig/ComSignal")
    _set_p(sig_moto, "ComBitPosition", 27)
    _set_p(sig_moto, "ComBitSize", 12)
    _set_p(sig_moto, "ComSignalEndianness", "BIG_ENDIAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_moto, "ComSignalType", "UINT16", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_moto, "ComSignalInitValue", "0", "ECUC-STRING-PARAM-DEF")
    _set_p(sig_moto, "ComTransferProperty", "PENDING", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_moto, "ComHandleId", 0)

    sig_intel = _add_container(com_cfg, "MCU_StatusByte", "/MICROSAR/Com/ComConfig/ComSignal")
    _set_p(sig_intel, "ComBitPosition", 40)
    _set_p(sig_intel, "ComBitSize", 8)
    _set_p(sig_intel, "ComSignalEndianness", "LITTLE_ENDIAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_intel, "ComSignalType", "UINT8", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_intel, "ComSignalInitValue", "1", "ECUC-STRING-PARAM-DEF")
    _set_p(sig_intel, "ComTransferProperty", "PENDING", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_intel, "ComHandleId", 1)

    sig_rx = _add_container(com_cfg, "VCU_GearSelectorReq", "/MICROSAR/Com/ComConfig/ComSignal")
    _set_p(sig_rx, "ComBitPosition", 2)
    _set_p(sig_rx, "ComBitSize", 4)
    _set_p(sig_rx, "ComSignalEndianness", "BIG_ENDIAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_rx, "ComSignalType", "UINT8", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_rx, "ComSignalInitValue", "0", "ECUC-STRING-PARAM-DEF")
    _set_p(sig_rx, "ComTimeout", 0.1, "ECUC-FLOAT-PARAM-DEF")
    _set_p(sig_rx, "ComHandleId", 2)

    ipdu_tx = _add_container(com_cfg, "MCU_Status_Tx", "/MICROSAR/Com/ComConfig/ComIPdu")
    _set_p(ipdu_tx, "ComIPduDirection", "SEND", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(ipdu_tx, "ComIPduHandleId", 0)
    _set_p(ipdu_tx, "ComIPduType", "NORMAL", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(ipdu_tx, "ComPduIdRef", "/ActiveEcuC/EcuC/EcucPduCollection/MCU_Status_Tx")
    _append_r(ipdu_tx, "ComIPduSignalRef", "/ActiveEcuC/Com/ComConfig/MCU_MaxTrq_EST")
    _append_r(ipdu_tx, "ComIPduSignalRef", "/ActiveEcuC/Com/ComConfig/MCU_StatusByte")
    tx_ipdu = _add_container(ipdu_tx, "ComTxIPdu", "/MICROSAR/Com/ComConfig/ComIPdu/ComTxIPdu")
    tm_true = _add_container(tx_ipdu, "ComTxModeTrue", "/MICROSAR/Com/ComConfig/ComIPdu/ComTxIPdu/ComTxModeTrue")
    tm = _add_container(tm_true, "ComTxMode", "/MICROSAR/Com/ComConfig/ComIPdu/ComTxIPdu/ComTxModeTrue/ComTxMode")
    _set_p(tm, "ComTxModeMode", "PERIODIC", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(tm, "ComTxModeTimePeriod", 0.01, "ECUC-FLOAT-PARAM-DEF")

    ipdu_rx = _add_container(com_cfg, "VCU_Cmd_Rx", "/MICROSAR/Com/ComConfig/ComIPdu")
    _set_p(ipdu_rx, "ComIPduDirection", "RECEIVE", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(ipdu_rx, "ComIPduHandleId", 1)
    _set_p(ipdu_rx, "ComIPduType", "NORMAL", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(ipdu_rx, "ComPduIdRef", "/ActiveEcuC/EcuC/EcucPduCollection/VCU_Cmd_Rx")
    _append_r(ipdu_rx, "ComIPduSignalRef", "/ActiveEcuC/Com/ComConfig/VCU_GearSelectorReq")

    project.resolve_all_references(force=True)
    return project, mods


def test_bit_layout_motorola_and_intel():
    # Motorola BIG_ENDIAN MSB forward stepping: start at bit 27 -> Byte 3 bit 3, step 12 bits into Byte 4 bits 7..0
    cells = compute_signal_bits(27, 12, "BIG_ENDIAN")
    assert len(cells) == 12
    assert cells[:4] == [(3, 3), (3, 2), (3, 1), (3, 0)]
    assert cells[4:] == [(4, 7), (4, 6), (4, 5), (4, 4), (4, 3), (4, 2), (4, 1), (4, 0)]

    # Intel LITTLE_ENDIAN: start at bit 40 -> Byte 5 bits 0..7
    intel_cells = compute_signal_bits(40, 8, "LITTLE_ENDIAN")
    assert intel_cells == [(5, b) for b in range(8)]

    # Overlap & out-of-bounds checks
    grid, overlaps, oob = analyze_pdu_bit_layout(
        [
            ("A", 27, 12, "BIG_ENDIAN"),
            ("B", 36, 8, "LITTLE_ENDIAN"),  # collides in Byte 4 bits 7..4
            ("C", 60, 8, "LITTLE_ENDIAN"),  # spills into Byte 8 >= DLC 8
        ],
        pdu_length_bytes=8,
    )
    assert overlaps == {"A", "B"}
    assert oob == {"C"}
    assert (4, 4) in grid and set(grid[(4, 4)]) == {"A", "B"}


def test_service_aggregates_channels_messages_signals_pdur(tmp_path):
    project, _ = build_synthetic_comm_project(tmp_path)
    svc = CommunicationWorkbenchService(project)

    assert svc.has_comm_modules() is True
    assert CommunicationWorkbenchService.anchor_module_for_project(project) == "Com"

    channels = svc.list_channel_rows()
    assert len(channels) == 1
    ch = channels[0]
    assert ch.channel_name == "CN_CAN00"
    assert ch.comm_channel_id == 0
    assert ch.baudrate_kbps == 500.0
    assert ch.fd_baudrate_kbps == 2000.0
    assert ch.trcv_init_state == "CANTRCV_TRCVMODE_NORMAL"
    assert ch.has_broken_link is False

    msgs = {m.name: m for m in svc.list_message_rows()}
    assert {"MCU_Status_Tx", "VCU_Cmd_Rx"} == set(msgs.keys())
    tx = msgs["MCU_Status_Tx"]
    assert tx.direction == "TX"
    assert tx.category == "COM"
    assert tx.can_id == 0x227
    assert tx.canif_dlc == 8
    assert tx.ecuc_lower_length == 8
    assert tx.ecuc_upper_length == 8
    assert tx.tx_mode == "PERIODIC"
    assert tx.cycle_time_ms == pytest.approx(10.0)
    assert tx.signal_count == 2
    assert tx.has_length_mismatch is False
    assert tx.has_broken_chain is False

    sigs_tx = svc.list_signal_rows("MCU_Status_Tx")
    assert [s.signal_name for s in sigs_tx] == ["MCU_MaxTrq_EST", "MCU_StatusByte"]
    assert all(not s.has_overlap and not s.out_of_bounds for s in sigs_tx)

    routes = svc.list_pdur_routing_rows()
    assert len(routes) == 2
    assert all(not r.has_broken_ref for r in routes)
    assert svc.collect_diagnostics() == []


def test_service_edits_handle_ids_pdur_crud_and_snapshots(tmp_path):
    project, _ = build_synthetic_comm_project(tmp_path)
    svc = CommunicationWorkbenchService(project)
    snaps = svc.capture_snapshots()

    # Cross-module message edit updates CanIf + EcuC lower/upper + ComTxMode
    svc.update_message_properties(
        "MCU_Status_Tx",
        "MCU_Status_Tx",
        can_id="0x333",
        can_id_type="EXTENDED_FD_CAN",
        dlc=16,
        tx_mode="MIXED",
        cycle_time_ms=25.0,
    )
    tx_after = next(m for m in svc.list_message_rows() if m.name == "MCU_Status_Tx")
    assert tx_after.can_id == 0x333
    assert tx_after.can_id_type == "EXTENDED_FD_CAN"
    assert tx_after.canif_dlc == 16
    assert tx_after.ecuc_lower_length == 16
    assert tx_after.ecuc_upper_length == 16
    assert tx_after.tx_mode == "MIXED"
    assert tx_after.cycle_time_ms == pytest.approx(25.0)

    # Signal edit
    svc.update_signal_properties("MCU_StatusByte", bit_position=48, bit_size=16, signal_type="UINT16", init_value="7")
    sig_row = next(s for s in svc.list_signal_rows("MCU_Status_Tx") if s.signal_name == "MCU_StatusByte")
    assert sig_row.bit_position == 48
    assert sig_row.bit_size == 16
    assert sig_row.init_value == "7"

    # PduR CRUD
    svc.add_pdur_routing_path("Custom_Tx_Route", "Com", "MCU_Status_Tx", "CanIf", "MCU_Status_Tx_CanIf")
    assert any(r.path_name == "Custom_Tx_Route" for r in svc.list_pdur_routing_rows())
    svc.update_pdur_routing_path("Custom_Tx_Route", src_module="Dcm", comm_type="TRANSPORT_PROTOCOL")
    updated = next(r for r in svc.list_pdur_routing_rows() if r.path_name == "Custom_Tx_Route")
    assert updated.src_module == "Dcm"
    assert updated.comm_type == "TRANSPORT_PROTOCOL"
    assert svc.remove_pdur_routing_path("Custom_Tx_Route") is True
    assert not any(r.path_name == "Custom_Tx_Route" for r in svc.list_pdur_routing_rows())

    # Snapshot rollback restores CanIf/EcuC/Com atomically
    svc.restore_snapshots(snaps)
    tx_restored = next(m for m in svc.list_message_rows() if m.name == "MCU_Status_Tx")
    assert tx_restored.can_id == 0x227
    assert tx_restored.canif_dlc == 8
    assert tx_restored.cycle_time_ms == pytest.approx(10.0)


def test_diagnostics_all_ten_codes_and_validation_rule(tmp_path):
    project, mods = build_synthetic_comm_project(tmp_path)
    svc = CommunicationWorkbenchService(project)

    # 1. CHANNEL_BROKEN_LINK
    canif_ctrl = next(c for c in mods["CanIf"].containers[0].sub_containers)
    canif_ctrl.reference_values.pop("CanIfCtrlCanCtrlRef", None)

    # 2. CAN_ID_DUPLICATE + 3. PDU_LENGTH_MISMATCH + 10. HANDLE_ID_DUPLICATE
    canif_init = next(c for c in mods["CanIf"].containers if c.short_name == "CanIfInitCfg")
    dup_tx = _add_container(canif_init, "Dup_Tx", "/MICROSAR/CanIf/CanIfInitCfg/CanIfTxPduCfg")
    _set_p(dup_tx, "CanIfTxPduCanId", 0x227)  # duplicate ID
    _set_p(dup_tx, "CanIfTxPduCanIdType", "STANDARD_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(dup_tx, "CanIfTxPduDlc", 4)  # length mismatch against 8-byte EcuC PDU
    _set_p(dup_tx, "CanIfTxPduId", 0)  # duplicate HandleId
    _set_p(dup_tx, "CanIfTxPduUserTxConfirmationUL", "PDUR", "ECUC-ENUMERATION-PARAM-DEF")
    _set_r(dup_tx, "CanIfTxPduBufferRef", "/ActiveEcuC/CanIf/CanIfInitCfg/CanIfBufferCfg_0")
    _set_r(dup_tx, "CanIfTxPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/MCU_Status_Tx_CanIf")  # also orphan because MCU_Status_Tx_CanIf maps PduR -> MCU_Status_Tx

    # 4. COM_ORPHAN_IPDU + 6. COM_TX_PERIOD_ZERO
    com_cfg = mods["Com"].containers[0]
    orphan_ipdu = _add_container(com_cfg, "Orphan_ComIPdu", "/MICROSAR/Com/ComConfig/ComIPdu")
    _set_p(orphan_ipdu, "ComIPduDirection", "SEND", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(orphan_ipdu, "ComIPduHandleId", 0)  # duplicate handle id too
    tx_sub = _add_container(orphan_ipdu, "ComTxIPdu", "/MICROSAR/Com/ComConfig/ComIPdu/ComTxIPdu")
    tm_true = _add_container(tx_sub, "ComTxModeTrue", "/MICROSAR/Com/ComConfig/ComIPdu/ComTxIPdu/ComTxModeTrue")
    tm = _add_container(tm_true, "ComTxMode", "/MICROSAR/Com/ComConfig/ComIPdu/ComTxIPdu/ComTxModeTrue/ComTxMode")
    _set_p(tm, "ComTxModeMode", "PERIODIC", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(tm, "ComTxModeTimePeriod", 0.0, "ECUC-FLOAT-PARAM-DEF")

    # 5. CANIF_ORPHAN_PDU (unlinked CanIf RX PDU)
    orphan_canif = _add_container(canif_init, "Orphan_CanIfRx", "/MICROSAR/CanIf/CanIfInitCfg/CanIfRxPduCfg")
    _set_p(orphan_canif, "CanIfRxPduCanId", 0x399)
    _set_p(orphan_canif, "CanIfRxPduCanIdType", "STANDARD_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(orphan_canif, "CanIfRxPduDlc", 8)
    _set_p(orphan_canif, "CanIfRxPduId", 9)

    # 7. PDUR_BROKEN_CHAIN
    pdur_table = mods["PduR"].containers[0].sub_containers[-1]
    broken_rp = _add_container(pdur_table, "Broken_Route", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
    broken_src = _add_container(broken_rp, "Src", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRSrcPdu")
    _set_r(broken_src, "PduRSrcPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/Missing_Pdu")

    # 8. SIGNAL_BIT_OVERLAP & 9. SIGNAL_OUT_OF_BOUNDS
    svc.update_signal_properties("MCU_StatusByte", bit_position=32, bit_size=8)  # collides with MCU_MaxTrq_EST in Byte 4
    sig_oob = _add_container(com_cfg, "Oob_Sig", "/MICROSAR/Com/ComConfig/ComSignal")
    _set_p(sig_oob, "ComBitPosition", 60)
    _set_p(sig_oob, "ComBitSize", 8)
    _set_p(sig_oob, "ComSignalEndianness", "LITTLE_ENDIAN", "ECUC-ENUMERATION-PARAM-DEF")
    _set_p(sig_oob, "ComHandleId", 99)
    ipdu_tx = next(c for c in com_cfg.sub_containers if c.short_name == "MCU_Status_Tx")
    _append_r(ipdu_tx, "ComIPduSignalRef", "/ActiveEcuC/Com/ComConfig/Oob_Sig")

    diags = svc.collect_diagnostics()
    codes = {d.code for d in diags}
    expected_codes = {
        "CHANNEL_BROKEN_LINK",
        "CAN_ID_DUPLICATE",
        "PDU_LENGTH_MISMATCH",
        "COM_ORPHAN_IPDU",
        "CANIF_ORPHAN_PDU",
        "COM_TX_PERIOD_ZERO",
        "PDUR_BROKEN_CHAIN",
        "SIGNAL_BIT_OVERLAP",
        "SIGNAL_OUT_OF_BOUNDS",
        "HANDLE_ID_DUPLICATE",
    }
    missing_codes = expected_codes - codes
    assert not missing_codes, f"Missing diagnostics: {sorted(missing_codes)}, got: {sorted(codes)}"

    # ValidationEngine runs CommunicationValidationRule once on anchor module "Com"
    can_engine = ValidationEngine(
        project.module_managers["Can"].module_def,
        project.module_managers["Can"].configuration,
        project_context=project,
    )
    can_engine.register_default_rules()
    assert any(r.name == "CommunicationRule" for r in can_engine.rules)
    can_res = can_engine.validate()
    assert not any(m.rule_name == "CommunicationRule" for m in can_res.messages)

    com_engine = ValidationEngine(
        project.module_managers["Com"].module_def,
        project.module_managers["Com"].configuration,
        project_context=project,
    )
    com_engine.register_default_rules()
    com_res = com_engine.validate()
    comm_msgs = [m for m in com_res.messages if m.rule_name == "CommunicationRule"]
    assert comm_msgs
    assert all("workbench_tab=" in (m.details or "") for m in comm_msgs)
    assert any(m.severity == ValidationSeverity.ERROR for m in comm_msgs)

    # Recompute HandleIds fixes HANDLE_ID_DUPLICATE
    svc.recompute_handle_ids()
    assert not any(d.code == "HANDLE_ID_DUPLICATE" for d in svc.collect_diagnostics())


def test_plan_and_apply_dbc_sync_multi_module_and_pre_lock(tmp_path, monkeypatch):
    project, mods = build_synthetic_comm_project(tmp_path)
    dbc_file = tmp_path / "sync_test.dbc"
    dbc_file.write_text(
        dedent("""\
            VERSION ""
            NS_ :
            BS_:
            BU_: Tester VCU MCU

            BO_ 551 MCU_Status: 8 MCU
             SG_ MCU_MaxTrq_EST : 27|12@0+ (1,0) [0|4095] "Nm" VCU
             SG_ MCU_StatusByte : 40|8@1+ (1,0) [0|255] "" VCU
             SG_ MCU_NewFault : 48|8@1+ (1,0) [0|255] "" VCU

            BO_ 768 BMS_Heartbeat: 8 VCU
             SG_ BMS_AliveCnt : 0|8@1+ (1,0) [0|255] "" MCU

            BO_ 500 Other_Frame: 8 VCU
             SG_ TesterOnly : 0|8@1+ (1,0) [0|255] "" Tester

            BO_ 2015 DiagFunc: 8 Tester
             SG_ DiagReq : 7|64@0+ (1,0) [0|0] "" MCU

            BA_DEF_ BO_ "GenMsgCycleTime" INT 0 60000;
            BA_DEF_ BO_ "DiagRequest" INT 0 1;
            BA_ "GenMsgCycleTime" BO_ 551 20;
            BA_ "GenMsgCycleTime" BO_ 768 50;
            BA_ "DiagRequest" BO_ 2015 1;
        """),
        encoding="utf-8",
    )

    # Preview without diag: DiagFunc is skipped, Other_Frame is excluded, MCU_Status -> update, BMS_Heartbeat -> create
    plan = plan_dbc_sync(project, dbc_file, ecu_node="MCU", include_diag=False, update_existing=True)
    by_msg = {i.message_name: i for i in plan.items}
    assert "Other_Frame" not in by_msg
    assert by_msg["DiagFunc"].action == "skip"
    assert by_msg["MCU_Status"].action == "update"
    assert by_msg["BMS_Heartbeat"].action == "create"
    assert by_msg["BMS_Heartbeat"].direction == "RX"

    res = apply_dbc_sync(project, plan)
    assert res.created_ecuc_pdus >= 2
    assert res.created_canif_pdus == 1
    assert res.created_pdur_paths == 1
    assert res.created_com_ipdus == 1
    assert res.created_com_signals >= 2  # MCU_NewFault + BMS_AliveCnt

    svc = CommunicationWorkbenchService(project)
    rows = {m.name: m for m in svc.list_message_rows()}
    assert "BMS_Heartbeat_Rx" in rows
    bms = rows["BMS_Heartbeat_Rx"]
    assert bms.can_id == 768
    assert bms.direction == "RX"
    assert bms.signal_count == 1
    assert rows["MCU_Status_Tx"].cycle_time_ms == pytest.approx(20.0)
    assert rows["MCU_Status_Tx"].signal_count == 3

    # Re-planning same DBC now yields unchanged for both MCU_Status and BMS_Heartbeat
    plan2 = plan_dbc_sync(project, dbc_file, ecu_node="MCU", include_diag=False, update_existing=True)
    by_msg2 = {i.message_name: i for i in plan2.items}
    assert by_msg2["MCU_Status"].action == "unchanged"
    assert by_msg2["BMS_Heartbeat"].action == "unchanged"

    # PreLockedError resilience: locked module item is recorded in skipped_locked instead of crashing
    dbc2 = tmp_path / "locked_new.dbc"
    dbc2.write_text(
        dedent("""\
            VERSION ""
            NS_ :
            BS_:
            BU_: MCU VCU

            BO_ 800 MCU_NewLocked: 8 MCU
             SG_ SigL : 0|8@1+ (1,0) [0|255] "" VCU
        """),
        encoding="utf-8",
    )
    canif_mgr = project.module_managers["CanIf"]
    monkeypatch.setattr(canif_mgr, "check_editable", lambda *_a, **_k: (_ for _ in ()).throw(PreLockedError("CanIf locked")))
    plan_locked = plan_dbc_sync(project, dbc2, ecu_node="MCU")
    res_locked = apply_dbc_sync(project, plan_locked)
    assert res_locked.skipped_locked


def test_real_startapplication1_dpa_readonly():
    real_dpa = Path("/Users/qlwang/Desktop/test3/StartApplication1/StartApplication1.dpa")
    if not real_dpa.is_file():
        pytest.skip("External StartApplication1.dpa fixture not available")
    project, _ = WorkspaceManager().load_project(real_dpa)
    svc = CommunicationWorkbenchService(project)
    assert svc.has_comm_modules() is True
    channels = svc.list_channel_rows()
    messages = svc.list_message_rows()
    signals = svc.list_signal_rows()
    routes = svc.list_pdur_routing_rows()
    assert len(channels) >= 1
    assert len(messages) >= 5
    assert len(signals) >= 5
    assert len(routes) >= 3
