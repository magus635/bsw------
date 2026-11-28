"""Tests for P4-2 Batch 3 MICROSAR CSL EB templates (CanTp & PduR) and parity audit."""

from pathlib import Path
import shutil
import subprocess

import pytest

from autosar_configurator.core.model.configuration_model import EcucContainerValue, EcucModuleConfiguration
from autosar_configurator.core.model.definition_model import EcucModuleDef
from autosar_configurator.generator import CodeGenerator, audit_project_templates


_REPO_ROOT = Path(__file__).resolve().parent.parent.parent
_TEMPLATE_PACK = _REPO_ROOT / "template_packs" / "davinci"
_REAL_DPA = Path("/Users/qlwang/Desktop/test3/StartApplication1/StartApplication1.dpa")
_REAL_GENDATA = Path("/Users/qlwang/Desktop/未命名文件夹/mcuapp/Applications/SipAddon/StartApplication/Appl/GenData")


def _c(parent, short_name: str, def_ref: str) -> EcucContainerValue:
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


def _p(c: EcucContainerValue, name: str, val, dest_type: str = "ECUC-INTEGER-PARAM-DEF") -> None:
    c.set_parameter_value(name, val, f"{c.definition_ref}/{name}")
    c.parameter_values[name].dest_type = dest_type


def _r(c: EcucContainerValue, name: str, val_ref: str) -> None:
    c.set_reference_value(name, val_ref, f"{c.definition_ref}/{name}")


def _write_stubs(inc_dir: Path) -> None:
    inc_dir.mkdir(parents=True, exist_ok=True)
    (inc_dir / "Std_Types.h").write_text(
        "#ifndef STD_TYPES_H\n"
        "#define STD_TYPES_H\n"
        "typedef unsigned char boolean;\n"
        "typedef unsigned char uint8;\n"
        "typedef unsigned short uint16;\n"
        "typedef unsigned long uint32;\n"
        "typedef signed long sint32;\n"
        "typedef unsigned long uint8_least;\n"
        "typedef unsigned long uint16_least;\n"
        "typedef uint8 Std_ReturnType;\n"
        "#ifndef TRUE\n#define TRUE ((boolean)1u)\n#endif\n"
        "#ifndef FALSE\n#define FALSE ((boolean)0u)\n#endif\n"
        "#ifndef STD_ON\n#define STD_ON 1u\n#endif\n"
        "#ifndef STD_OFF\n#define STD_OFF 0u\n#endif\n"
        "#ifndef NULL_PTR\n#define NULL_PTR ((void*)0)\n#endif\n"
        "#define AUTOMATIC\n"
        "#define LOCAL_INLINE static inline\n"
        "#define CONST(t, m) const t\n"
        "#define VAR(t, m) t\n"
        "#define P2CONST(t, a, m) const t *\n"
        "#define P2VAR(t, a, m) t *\n"
        "#define P2FUNC(r, m, fn) r (*fn)\n"
        "#define FUNC(r, m) r\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "ComStack_Types.h").write_text(
        "#ifndef COMSTACK_TYPES_H\n"
        "#define COMSTACK_TYPES_H\n"
        '#include "Std_Types.h"\n'
        "typedef uint8 PduIdType;\n"
        "typedef uint16 PduLengthType;\n"
        "typedef uint8 NetworkHandleType;\n"
        "typedef uint8 TPParameterType;\n"
        "typedef enum { BUFREQ_OK = 0, BUFREQ_E_NOT_OK = 1, BUFREQ_E_BUSY = 2, BUFREQ_E_OVFL = 3 } BufReq_ReturnType;\n"
        "typedef enum { TP_DATACONF = 0, TP_DATARETRY = 1, TP_CONFPENDING = 2 } TpDataStateType;\n"
        "typedef struct { TpDataStateType TpDataState; PduLengthType TxTpDataCnt; } RetryInfoType;\n"
        "typedef struct { uint8 *SduDataPtr; PduLengthType SduLength; } PduInfoType;\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "Os.h").write_text("#ifndef OS_H\n#define OS_H\ntypedef uint8 ApplicationType;\n#endif\n", encoding="utf-8")
    (inc_dir / "Det.h").write_text("#ifndef DET_H\n#define DET_H\n#endif\n", encoding="utf-8")
    (inc_dir / "CanTp_MemMap.h").write_text("/* stub CanTp memmap */\n", encoding="utf-8")
    (inc_dir / "PduR_MemMap.h").write_text("/* stub PduR memmap */\n", encoding="utf-8")
    (inc_dir / "CanTp_Types.h").write_text(
        "#ifndef CANTP_TYPES_H\n#define CANTP_TYPES_H\n"
        '#include "ComStack_Types.h"\n'
        '#include "CanTp_Cfg.h"\n'
        "typedef struct { uint8 State; } CanTp_RxStateType;\n"
        "typedef struct { uint8 Locked; } CanTp_TxSemaphoreType;\n"
        "typedef struct { uint8 State; } CanTp_TxStateType;\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "CanIf.h").write_text(
        "#ifndef CANIF_H\n#define CANIF_H\n"
        '#include "ComStack_Types.h"\n'
        "#define CanIfConf_CanIfTxPduCfg_CanIfTx_DiagResp 0u\n"
        "#define CanIfConf_CanIfTxPduCfg_CanIfTx_ComMsg 1u\n"
        "Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "CanTp.h").write_text(
        "#ifndef CANTP_H\n#define CANTP_H\n"
        '#include "ComStack_Types.h"\n'
        "#define CanTpConf_CanTpTxNSdu_CanTpTxNSdu_Phys 0u\n"
        "Std_ReturnType CanTp_Transmit(PduIdType TxSduId, const PduInfoType *PduInfoPtr);\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "Com_Cbk.h").write_text(
        "#ifndef COM_CBK_H\n#define COM_CBK_H\n"
        '#include "ComStack_Types.h"\n'
        "#define ComConf_ComIPdu_Com_RxPdu 0u\n"
        "#define ComConf_ComIPdu_Com_TxPdu 0u\n"
        "void Com_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);\n"
        "void Com_TxConfirmation(PduIdType TxPduId);\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "Dcm_Cbk.h").write_text(
        "#ifndef DCM_CBK_H\n#define DCM_CBK_H\n"
        '#include "ComStack_Types.h"\n'
        "#define DcmConf_DcmDslProtocolRx_Dcm_RxPhys 1u\n"
        "#define DcmConf_DcmDslProtocolRx_Dcm_RxFunc 0u\n"
        "#define DcmConf_DcmDslProtocolTx_Dcm_TxResp 0u\n"
        "BufReq_ReturnType Dcm_StartOfReception(PduIdType id, PduInfoType *info, PduLengthType len, PduLengthType *bufSize);\n"
        "BufReq_ReturnType Dcm_CopyRxData(PduIdType id, PduInfoType *info, PduLengthType *bufSize);\n"
        "BufReq_ReturnType Dcm_CopyTxData(PduIdType id, PduInfoType *info, RetryInfoType *retry, PduLengthType *avail);\n"
        "void Dcm_TpRxIndication(PduIdType id, Std_ReturnType result);\n"
        "void Dcm_TpTxConfirmation(PduIdType id, Std_ReturnType result);\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "SchM_PduR.h").write_text(
        "#ifndef SCHM_PDUR_H\n#define SCHM_PDUR_H\n"
        "void SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void);\n"
        "void SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void);\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "PduR_CanTp.h").write_text(
        "#ifndef PDUR_CANTP_H\n#define PDUR_CANTP_H\n"
        '#include "PduR.h"\n'
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "PduR.h").write_text(
        "#ifndef PDUR_H\n#define PDUR_H\n"
        '#include "ComStack_Types.h"\n'
        "#define PduRConf_PduRSrcPdu_PduR_TpRxPhys 1u\n"
        "#define PduRConf_PduRSrcPdu_PduR_TpRxFunc 0u\n"
        "#define PduRConf_PduRDestPdu_PduR_TpTxResp 0u\n"
        "Std_ReturnType PduR_UpTransmit(PduIdType id, const PduInfoType *info);\n"
        "Std_ReturnType PduR_CancelTransmit(PduIdType id);\n"
        "void PduR_LoIfRxIndication(PduIdType RxPduId, const PduInfoType *info);\n"
        "void PduR_LoIfTxConfirmation(PduIdType TxPduId);\n"
        "BufReq_ReturnType PduR_LoTpStartOfReception(PduIdType id, PduInfoType *info, PduLengthType TpSduLength, PduLengthType *bufferSizePtr);\n"
        "BufReq_ReturnType PduR_LoTpCopyRxData(PduIdType id, PduInfoType *info, PduLengthType *bufferSizePtr);\n"
        "BufReq_ReturnType PduR_LoTpCopyTxData(PduIdType id, PduInfoType *info, RetryInfoType *retry, PduLengthType *availableDataPtr);\n"
        "void PduR_LoTpRxIndication(PduIdType id, Std_ReturnType result);\n"
        "void PduR_LoTpTxConfirmation(PduIdType id, Std_ReturnType result);\n"
        "#endif\n",
        encoding="utf-8",
    )


def _clang_check(c_files, include_dirs) -> None:
    clang_bin = shutil.which("clang")
    if not clang_bin:
        pytest.skip("clang not found in PATH")
    cmd = [clang_bin, "--target=armv8r-none-eabi", "-fsyntax-only", "-Wall", "-Wextra", "-Werror"]
    cmd.extend(f"-I{d}" for d in include_dirs)
    for cf in c_files:
        proc = subprocess.run(cmd + [str(cf)], capture_output=True, text=True)
        assert proc.returncode == 0, f"clang failed for {cf}:\n{proc.stderr}"


def _build_shared_modules():
    ecuc_def = EcucModuleDef("EcuC", definition_ref="/MICROSAR/EcuC")
    ecuc_cfg = EcucModuleConfiguration("EcuC", definition_ref="/MICROSAR/EcuC")
    pcoll = _c(ecuc_cfg, "EcucPduCollection", "/MICROSAR/EcuC/EcucPduCollection")
    ep_tp_rx_phys = _c(pcoll, "Pdu_TpRxPhys", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_tp_rx_phys, "PduLength", 8)
    ep_tp_rx_func = _c(pcoll, "Pdu_TpRxFunc", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_tp_rx_func, "PduLength", 7)
    ep_tp_rx_npdu_phys = _c(pcoll, "Pdu_TpNPduPhys", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_tp_rx_npdu_phys, "PduLength", 8)
    ep_tp_rx_npdu_func = _c(pcoll, "Pdu_TpNPduFunc", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_tp_rx_npdu_func, "PduLength", 8)
    ep_tp_tx = _c(pcoll, "Pdu_TpTxResp", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_tp_tx, "PduLength", 8)
    ep_tp_tx_npdu = _c(pcoll, "Pdu_TpTxNPduResp", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_tp_tx_npdu, "PduLength", 8)
    ep_if_rx = _c(pcoll, "Pdu_IfRx", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_if_rx, "PduLength", 8)
    ep_if_rx_com = _c(pcoll, "Pdu_IfRxCom", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_if_rx_com, "PduLength", 8)
    ep_if_tx_com = _c(pcoll, "Pdu_IfTxCom", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_if_tx_com, "PduLength", 8)
    ep_if_tx_canif = _c(pcoll, "Pdu_IfTxCanIf", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_if_tx_canif, "PduLength", 8)
    ep_dcm_rx_phys = _c(pcoll, "Pdu_DcmRxPhys", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_dcm_rx_phys, "PduLength", 8)
    ep_dcm_rx_func = _c(pcoll, "Pdu_DcmRxFunc", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_dcm_rx_func, "PduLength", 7)
    ep_dcm_tx = _c(pcoll, "Pdu_DcmTxResp", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    _p(ep_dcm_tx, "PduLength", 8)

    canif_def = EcucModuleDef("CanIf", definition_ref="/MICROSAR/CanIf")
    canif_cfg = EcucModuleConfiguration("CanIf", definition_ref="/MICROSAR/CanIf")
    ci = _c(canif_cfg, "CanIfInitCfg", "/MICROSAR/CanIf/CanIfInitCfg")
    ci_tp = _c(ci, "CanIfTx_DiagResp", "/MICROSAR/CanIf/CanIfInitCfg/CanIfTxPduCfg")
    _p(ci_tp, "CanIfTxPduId", 0)
    _p(ci_tp, "CanIfTxPduCanId", 2015)
    _r(ci_tp, "CanIfTxPduRef", ep_tp_tx_npdu.get_path())
    ci_com = _c(ci, "CanIfTx_ComMsg", "/MICROSAR/CanIf/CanIfInitCfg/CanIfTxPduCfg")
    _p(ci_com, "CanIfTxPduId", 1)
    _p(ci_com, "CanIfTxPduCanId", 548)
    _r(ci_com, "CanIfTxPduRef", ep_if_tx_canif.get_path())

    com_def = EcucModuleDef("Com", definition_ref="/MICROSAR/Com")
    com_cfg = EcucModuleConfiguration("Com", definition_ref="/MICROSAR/Com")
    com_cc = _c(com_cfg, "ComConfig", "/MICROSAR/Com/ComConfig")
    com_rx = _c(com_cc, "Com_RxPdu", "/MICROSAR/Com/ComConfig/ComIPdu")
    _p(com_rx, "ComIPduHandleId", 0)
    _r(com_rx, "ComPduIdRef", ep_if_rx_com.get_path())
    com_tx = _c(com_cc, "Com_TxPdu", "/MICROSAR/Com/ComConfig/ComIPdu")
    _p(com_tx, "ComIPduHandleId", 0)
    _r(com_tx, "ComPduIdRef", ep_if_tx_com.get_path())

    dcm_def = EcucModuleDef("Dcm", definition_ref="/MICROSAR/Dcm")
    dcm_cfg = EcucModuleConfiguration("Dcm", definition_ref="/MICROSAR/Dcm")
    dset = _c(dcm_cfg, "DcmConfigSet", "/MICROSAR/Dcm/DcmConfigSet")
    ddsl = _c(dset, "DcmDsl", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl")
    dproto = _c(ddsl, "DcmDslProtocol", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol")
    drow = _c(dproto, "DcmDslProtocolRow", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow")
    dconn = _c(drow, "DcmDslConnection", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection")
    dmain = _c(dconn, "DcmDslMainConnection", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection/DcmDslMainConnection")
    drx_phys = _c(dmain, "Dcm_RxPhys", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection/DcmDslMainConnection/DcmDslProtocolRx")
    _r(drx_phys, "DcmDslProtocolRxPduRef", ep_dcm_rx_phys.get_path())
    drx_func = _c(dmain, "Dcm_RxFunc", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection/DcmDslMainConnection/DcmDslProtocolRx")
    _r(drx_func, "DcmDslProtocolRxPduRef", ep_dcm_rx_func.get_path())
    dtx = _c(dmain, "Dcm_TxResp", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection/DcmDslMainConnection/DcmDslProtocolTx")
    _r(dtx, "DcmDslProtocolTxPduRef", ep_dcm_tx.get_path())

    return {
        "EcuC": (ecuc_def, ecuc_cfg),
        "CanIf": (canif_def, canif_cfg),
        "Com": (com_def, com_cfg),
        "Dcm": (dcm_def, dcm_cfg),
        "pdus": {
            "tp_rx_phys": ep_tp_rx_phys,
            "tp_rx_func": ep_tp_rx_func,
            "tp_rx_npdu_phys": ep_tp_rx_npdu_phys,
            "tp_rx_npdu_func": ep_tp_rx_npdu_func,
            "tp_tx": ep_tp_tx,
            "tp_tx_npdu": ep_tp_tx_npdu,
            "if_rx": ep_if_rx,
            "if_rx_com": ep_if_rx_com,
            "if_tx_com": ep_if_tx_com,
            "if_tx_canif": ep_if_tx_canif,
            "dcm_rx_phys": ep_dcm_rx_phys,
            "dcm_rx_func": ep_dcm_rx_func,
            "dcm_tx": ep_dcm_tx,
        },
    }


def _build_cantp(pdus):
    cantp_def = EcucModuleDef("CanTp", definition_ref="/MICROSAR/CanTp")
    cantp_cfg = EcucModuleConfiguration("CanTp", definition_ref="/MICROSAR/CanTp")
    gen = _c(cantp_cfg, "CanTpGeneral", "/MICROSAR/CanTp/CanTpGeneral")
    for pname, bval in [
        ("CanTpVersionInfoApi", False),
        ("CanTpDevErrorDetect", True),
        ("CanTpTc", False),
        ("CanTpRc", False),
        ("CanTpPaddingActive", True),
        ("CanTpHavePaddingByte", True),
        ("CanTpEnableSplitMainFunction", False),
        ("CanTpSupportStandardAddressing", True),
        ("CanTpSupportExtendedAddressing", True),
        ("CanTpSupportMixed11Addressing", True),
        ("CanTpSupportMixed29Addressing", True),
        ("CanTpSupportNormalFixedAddressing", True),
        ("CanTpSupportCustomAddressing", False),
        ("CanTpUseOnlyFirstFc", True),
        ("CanTpChangeParameterApi", False),
        ("CanTpReadParameterApi", False),
        ("CanTpOnlyNotifyInformedAppl", True),
    ]:
        _p(gen, pname, bval, "ECUC-BOOLEAN-PARAM-DEF")
    _p(gen, "CanTpPaddingByte", 204)

    cfg = _c(cantp_cfg, "CanTpConfig", "/MICROSAR/CanTp/CanTpConfig")
    _p(cfg, "CanTpMainFunctionPeriod", 0.005, "ECUC-FLOAT-PARAM-DEF")

    ch0 = _c(cfg, "TPCH_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel")
    _p(ch0, "CanTpChannelMode", "CANTP_MODE_FULL_DUPLEX", "ECUC-ENUMERATION-PARAM-DEF")
    rx0 = _c(ch0, "CanTpRxNSdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu")
    _p(rx0, "CanTpRxNSduId", 0)
    _p(rx0, "CanTpRxDl", 8)
    _p(rx0, "CanTpRxTaType", "CANTP_PHYSICAL", "ECUC-ENUMERATION-PARAM-DEF")
    _p(rx0, "CanTpBs", 255)
    _p(rx0, "CanTpRxWftMax", 0)
    _p(rx0, "CanTpNar", 0.03, "ECUC-FLOAT-PARAM-DEF")
    _p(rx0, "CanTpNbr", 0.05, "ECUC-FLOAT-PARAM-DEF")
    _p(rx0, "CanTpNcr", 0.15, "ECUC-FLOAT-PARAM-DEF")
    _p(rx0, "CanTpSTmin", 0.01, "ECUC-FLOAT-PARAM-DEF")
    _r(rx0, "CanTpRxNSduRef", pdus["tp_rx_phys"].get_path())
    rx0_npdu = _c(rx0, "CanTpRxNPdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu/CanTpRxNPdu")
    _p(rx0_npdu, "CanTpRxNPduId", 0)
    _r(rx0_npdu, "CanTpRxNPduRef", pdus["tp_rx_npdu_phys"].get_path())
    rx0_txfc = _c(rx0, "CanTpTxFcNPdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu/CanTpTxFcNPdu")
    _p(rx0_txfc, "CanTpTxFcNPduConfirmationPduId", 0)
    _r(rx0_txfc, "CanTpTxFcNPduRef", pdus["tp_tx_npdu"].get_path())

    tx0 = _c(ch0, "CanTpTxNSdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpTxNSdu")
    _p(tx0, "CanTpTxNSduId", 0)
    _p(tx0, "CanTpTxDl", 8)
    _p(tx0, "CanTpTxTaType", "CANTP_PHYSICAL", "ECUC-ENUMERATION-PARAM-DEF")
    _p(tx0, "CanTpTc", False, "ECUC-BOOLEAN-PARAM-DEF")
    _p(tx0, "CanTpNas", 0.03, "ECUC-FLOAT-PARAM-DEF")
    _p(tx0, "CanTpNbs", 0.09, "ECUC-FLOAT-PARAM-DEF")
    _p(tx0, "CanTpNcs", 0.10, "ECUC-FLOAT-PARAM-DEF")
    _r(tx0, "CanTpTxNSduRef", pdus["tp_tx"].get_path())
    tx0_rxfc = _c(tx0, "CanTpRxFcNPdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpTxNSdu/CanTpRxFcNPdu")
    _p(tx0_rxfc, "CanTpRxFcNPduId", 0)
    _r(tx0_rxfc, "CanTpRxFcNPduRef", pdus["tp_rx_npdu_phys"].get_path())
    tx0_npdu = _c(tx0, "CanTpTxNPdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpTxNSdu/CanTpTxNPdu")
    _p(tx0_npdu, "CanTpTxNPduConfirmationPduId", 0)
    _r(tx0_npdu, "CanTpTxNPduRef", pdus["tp_tx_npdu"].get_path())

    ch1 = _c(cfg, "TPCH_Func", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel")
    _p(ch1, "CanTpChannelMode", "CANTP_MODE_FULL_DUPLEX", "ECUC-ENUMERATION-PARAM-DEF")
    rx1 = _c(ch1, "CanTpRxNSdu_Func", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu")
    _p(rx1, "CanTpRxNSduId", 1)
    _p(rx1, "CanTpRxDl", 8)
    _p(rx1, "CanTpRxTaType", "CANTP_FUNCTIONAL", "ECUC-ENUMERATION-PARAM-DEF")
    _p(rx1, "CanTpNar", 0.03, "ECUC-FLOAT-PARAM-DEF")
    _p(rx1, "CanTpNbr", 0.05, "ECUC-FLOAT-PARAM-DEF")
    _p(rx1, "CanTpNcr", 0.15, "ECUC-FLOAT-PARAM-DEF")
    _p(rx1, "CanTpSTmin", 0.01, "ECUC-FLOAT-PARAM-DEF")
    _r(rx1, "CanTpRxNSduRef", pdus["tp_rx_func"].get_path())
    rx1_npdu = _c(rx1, "CanTpRxNPdu_Func", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu/CanTpRxNPdu")
    _p(rx1_npdu, "CanTpRxNPduId", 1)
    _r(rx1_npdu, "CanTpRxNPduRef", pdus["tp_rx_npdu_func"].get_path())

    return cantp_def, cantp_cfg


def _build_pdur(pdus):
    pdur_def = EcucModuleDef("PduR", definition_ref="/MICROSAR/PduR")
    pdur_cfg = EcucModuleConfiguration("PduR", definition_ref="/MICROSAR/PduR")
    gen = _c(pdur_cfg, "PduRGeneral", "/MICROSAR/PduR/PduRGeneral")
    _p(gen, "PduRDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(gen, "PduRVersionInfoApi", False, "ECUC-BOOLEAN-PARAM-DEF")
    _p(gen, "PduRExtendedErrorChecks", False, "ECUC-BOOLEAN-PARAM-DEF")
    _p(gen, "PduRSupportMulticore", False, "ECUC-BOOLEAN-PARAM-DEF")
    _p(gen, "PduRSpinlockRetryCounter", 4294967295)

    for mname, lo_if, lo_tp, up_if, up_tp, txcfm, cxltx in [
        ("CanIf", True, False, False, False, True, False),
        ("CanTp", False, True, False, False, False, False),
        ("Com", False, False, True, False, True, False),
        ("Dcm", False, False, False, True, False, True),
    ]:
        bm = _c(pdur_cfg, mname, "/MICROSAR/PduR/PduRBswModules")
        _p(bm, "PduRLowerModule", lo_if or lo_tp, "ECUC-BOOLEAN-PARAM-DEF")
        _p(bm, "PduRUpperModule", up_if or up_tp, "ECUC-BOOLEAN-PARAM-DEF")
        _p(bm, "PduRCommunicationInterface", lo_if or up_if, "ECUC-BOOLEAN-PARAM-DEF")
        _p(bm, "PduRTransportProtocol", lo_tp or up_tp, "ECUC-BOOLEAN-PARAM-DEF")
        _p(bm, "PduRTxConfirmation", txcfm, "ECUC-BOOLEAN-PARAM-DEF")
        _p(bm, "PduRCancelTransmit", cxltx, "ECUC-BOOLEAN-PARAM-DEF")

    rts = _c(pdur_cfg, "PduRRoutingTables", "/MICROSAR/PduR/PduRRoutingTables")
    _p(rts, "PduRConfigurationId", 0)
    rt = _c(rts, "PduRRoutingTable", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable")

    def add_path(name, ctype, src_name, src_id, src_dir, src_mod, src_pdu, dst_name, dst_id, dst_dir, dst_mod, dst_pdu, lstrat):
        rp = _c(rt, name, "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
        _p(rp, "PduRRoutingPathCommunicationType", ctype, "ECUC-ENUMERATION-PARAM-DEF")
        sp = _c(rp, src_name, f"{rp.definition_ref}/PduRSrcPdu")
        _p(sp, "PduRSourcePduHandleId", src_id)
        _p(sp, "PduRSrcPduDirection", src_dir, "ECUC-ENUMERATION-PARAM-DEF")
        _r(sp, "PduRSrcPduPduRBswModulesRef", f"/ActiveEcuC/PduR/{src_mod}")
        _r(sp, "PduRSrcPduRef", src_pdu.get_path())
        dp = _c(rp, dst_name, f"{rp.definition_ref}/PduRDestPdu")
        _p(dp, "PduRDestPduHandleId", dst_id)
        _p(dp, "PduRDestPduDirection", dst_dir, "ECUC-ENUMERATION-PARAM-DEF")
        _p(dp, "PduRPduLengthHandlingStrategy", lstrat, "ECUC-ENUMERATION-PARAM-DEF")
        _r(dp, "PduRDestPduPduRBswModulesRef", f"/ActiveEcuC/PduR/{dst_mod}")
        _r(dp, "PduRDestPduRef", dst_pdu.get_path())

    add_path("Path_IfRx", "COMMUNICATION_INTERFACE", "Src_IfRx", 0, "RECEIVE", "CanIf", pdus["if_rx"], "Dst_IfRx", 0, "RECEIVE", "Com", pdus["if_rx_com"], "IGNORE")
    add_path("Path_IfTx", "COMMUNICATION_INTERFACE", "Src_IfTx", 0, "TRANSMIT", "Com", pdus["if_tx_com"], "Dst_IfTx", 0, "TRANSMIT", "CanIf", pdus["if_tx_canif"], "IGNORE")
    add_path("Path_TpRxFunc", "TRANSPORT_PROTOCOL", "PduR_TpRxFunc", 0, "RECEIVE", "CanTp", pdus["tp_rx_func"], "Dst_TpRxFunc", 0, "RECEIVE", "Dcm", pdus["dcm_rx_func"], "UNUSED")
    add_path("Path_TpRxPhys", "TRANSPORT_PROTOCOL", "PduR_TpRxPhys", 1, "RECEIVE", "CanTp", pdus["tp_rx_phys"], "Dst_TpRxPhys", 1, "RECEIVE", "Dcm", pdus["dcm_rx_phys"], "UNUSED")
    add_path("Path_TpTxResp", "TRANSPORT_PROTOCOL", "Src_TpTxResp", 1, "TRANSMIT", "Dcm", pdus["dcm_tx"], "PduR_TpTxResp", 0, "TRANSMIT", "CanTp", pdus["tp_tx"], "UNUSED")

    return pdur_def, pdur_cfg


def test_cantp_csl_generation_and_clang(tmp_path):
    stubs = tmp_path / "stubs"
    _write_stubs(stubs)
    shared = _build_shared_modules()
    cantp_def, cantp_cfg = _build_cantp(shared["pdus"])
    pdur_def, pdur_cfg = _build_pdur(shared["pdus"])

    all_cfgs = {
        "EcuC": shared["EcuC"],
        "CanIf": shared["CanIf"],
        "CanTp": (cantp_def, cantp_cfg),
        "PduR": (pdur_def, pdur_cfg),
    }

    out_dir = tmp_path / "out_cantp"
    gen = CodeGenerator(cantp_def, cantp_cfg, project_template_dir=_TEMPLATE_PACK, all_configurations=all_cfgs)
    assert gen.generate_all(out_dir, force=True) is True

    inc_dir = out_dir / "CanTp" / "include"
    src_dir = out_dir / "CanTp" / "src"
    assert {p.name for p in inc_dir.iterdir()} == {"CanTp_Cfg.h", "CanTp_Lcfg.h", "CanTp_PBcfg.h"}
    assert {p.name for p in src_dir.iterdir()} == {"CanTp_Lcfg.c", "CanTp_PBcfg.c"}

    for p in list(inc_dir.iterdir()) + list(src_dir.iterdir()):
        txt = p.read_text(encoding="utf-8")
        assert "[!" not in txt and "!]" not in txt, f"Unexpanded EB tag in {p.name}"

    cfg_h = (inc_dir / "CanTp_Cfg.h").read_text(encoding="utf-8")
    assert "#define CANTP_PADDING_PATTERN                                                  0xCCu" in cfg_h
    assert "#define CANTP_EQ2_CANIDOFTXPDUMAP                                                                   0x000007DFu" in cfg_h
    assert "#define CANTP_EQ2_NAROFRXSDUCFG                                                                     7u" in cfg_h
    assert "#define CANTP_EQ2_NBROFRXSDUCFG                                                                     11u" in cfg_h
    assert "#define CANTP_EQ2_NCROFRXSDUCFG                                                                     31u" in cfg_h
    assert "#define CANTP_EQ2_STMINOFRXSDUCFG                                                                   10u" in cfg_h
    assert "#define CANTP_EQ2_NASOFTXSDUCFG                                                                     7u" in cfg_h
    assert "#define CANTP_EQ2_NBSOFTXSDUCFG                                                                     19u" in cfg_h
    assert "#define CANTP_EQ2_NCSOFTXSDUCFG                                                                     21u" in cfg_h
    assert "#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_Phys 0u" in cfg_h
    assert "#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_Func 1u" in cfg_h

    lcfg_c = (src_dir / "CanTp_Lcfg.c").read_text(encoding="utf-8")
    assert "CanIfConf_CanIfTxPduCfg_CanIfTx_DiagResp" in lcfg_c
    assert "PduRConf_PduRSrcPdu_PduR_TpRxPhys" in lcfg_c
    assert "PduRConf_PduRSrcPdu_PduR_TpRxFunc" in lcfg_c
    assert "CANTP_FUNCTIONAL_RXTATYPEOFRXSDUCFG" in lcfg_c

    _clang_check([src_dir / "CanTp_Lcfg.c", src_dir / "CanTp_PBcfg.c"], [inc_dir, stubs])


def test_pdur_csl_generation_and_clang(tmp_path):
    stubs = tmp_path / "stubs"
    _write_stubs(stubs)
    shared = _build_shared_modules()
    cantp_def, cantp_cfg = _build_cantp(shared["pdus"])
    pdur_def, pdur_cfg = _build_pdur(shared["pdus"])

    all_cfgs = {
        "EcuC": shared["EcuC"],
        "CanIf": shared["CanIf"],
        "CanTp": (cantp_def, cantp_cfg),
        "Com": shared["Com"],
        "Dcm": shared["Dcm"],
        "PduR": (pdur_def, pdur_cfg),
    }

    out_dir = tmp_path / "out_pdur"
    gen = CodeGenerator(pdur_def, pdur_cfg, project_template_dir=_TEMPLATE_PACK, all_configurations=all_cfgs)
    assert gen.generate_all(out_dir, force=True) is True

    inc_dir = out_dir / "PduR" / "include"
    src_dir = out_dir / "PduR" / "src"
    assert {p.name for p in inc_dir.iterdir()} == {
        "PduR_Types.h",
        "PduR_Cfg.h",
        "PduR_Lcfg.h",
        "PduR_PBcfg.h",
        "PduR_CanIf.h",
        "PduR_CanTp.h",
        "PduR_Com.h",
        "PduR_Dcm.h",
    }
    assert {p.name for p in src_dir.iterdir()} == {"PduR_Lcfg.c", "PduR_PBcfg.c"}

    for p in list(inc_dir.iterdir()) + list(src_dir.iterdir()):
        txt = p.read_text(encoding="utf-8")
        assert "[!" not in txt and "!]" not in txt, f"Unexpanded EB tag in {p.name}"

    cfg_h = (inc_dir / "PduR_Cfg.h").read_text(encoding="utf-8")
    assert "#define PDUR_FCT_COMTX 0x89u" in cfg_h
    assert "#define PDUR_FCT_CANIFTX 0x09u" in cfg_h
    assert "#define PDUR_FCT_CANTPSOR 0x06u" in cfg_h
    assert "#define PDUR_FCT_DCMCTX 0x9Au" in cfg_h

    lcfg_h = (inc_dir / "PduR_Lcfg.h").read_text(encoding="utf-8")
    assert "#define PduR_GetSizeOfMmRomOfPCPartitionConfig()" in lcfg_h
    assert "4u" in lcfg_h
    assert "#define PduR_GetSizeOfRmDestRomOfPCPartitionConfig()" in lcfg_h
    assert "5u" in lcfg_h
    assert "PduR_RxTp2Src[2]" in lcfg_h

    lcfg_c = (src_dir / "PduR_Lcfg.c").read_text(encoding="utf-8")
    assert "PduR_MmRom[4]" in lcfg_c
    assert "PduR_RmDestRom[5]" in lcfg_c
    assert "PduR_RmGDestRom[5]" in lcfg_c
    assert "PduR_RmSrcRom[5]" in lcfg_c
    assert "DcmConf_DcmDslProtocolRx_Dcm_RxFunc" in lcfg_c
    assert "DcmConf_DcmDslProtocolTx_Dcm_TxResp" in lcfg_c
    assert "PduR_DcmCancelTransmit" in lcfg_c

    _clang_check([src_dir / "PduR_Lcfg.c", src_dir / "PduR_PBcfg.c"], [inc_dir, stubs])


@pytest.mark.skipif(not _REAL_DPA.exists() or not _REAL_GENDATA.exists(), reason="Real reference project unavailable")
def test_startapplication1_cantp_pdur_parity():
    report = audit_project_templates(
        _REAL_DPA,
        ref_gendata_dir=_REAL_GENDATA,
        template_pack_dir=_TEMPLATE_PACK,
        include_platform_gen=False,
        include_rte_phase2_3=False,
    )

    by_mod = {m.module_name: m for m in report.module_results}

    cantp = by_mod["CanTp"]
    assert cantp.status == "OK" and not cantp.unexpanded_files
    assert cantp.matched_ref_count == 5
    assert cantp.define_ref_total > 0 and cantp.define_match_total / cantp.define_ref_total >= 0.95
    assert cantp.sym_match_total == cantp.sym_ref_total

    pdur = by_mod["PduR"]
    assert pdur.status == "OK" and not pdur.unexpanded_files
    assert pdur.matched_ref_count == 10
    assert pdur.define_ref_total > 0 and pdur.define_match_total / pdur.define_ref_total >= 0.95
    assert pdur.sym_match_total == pdur.sym_ref_total
