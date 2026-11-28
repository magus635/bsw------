"""Tests for P4-2 Batch 2 MICROSAR CSL EB templates (ComM & CanIf) and parity audit."""

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
        "typedef struct { uint8 *SduDataPtr; PduLengthType SduLength; } PduInfoType;\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "Can.h").write_text('#ifndef CAN_H\n#define CAN_H\n#include "ComStack_Types.h"\n#endif\n', encoding="utf-8")
    (inc_dir / "CanIf_Types.h").write_text(
        "#ifndef CANIF_TYPES_H\n"
        "#define CANIF_TYPES_H\n"
        '#include "ComStack_Types.h"\n'
        "typedef enum { CANIF_CS_UNINIT = 0 } CanIf_ControllerModeType;\n"
        "typedef enum { CANIF_GET_OFFLINE = 0 } CanIf_PduGetModeType;\n"
        "typedef enum { CANIF_TxBasicCANMailbox = 0, CANIF_RxBasicCANMailbox } CanIf_MailBoxTypeType;\n"
        "typedef enum { CanIf_SimpleRxIndicationLayout = 0, CanIf_AdvancedRxIndicationLayout } CanIf_RxIndicationLayoutType;\n"
        "typedef void (*CanIf_BusOffNotificationFctType)(uint8 ControllerId);\n"
        "typedef void (*CanIf_CtrlModeIndicationFctType)(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);\n"
        "typedef void (*CanIf_TrcvModeIndicationFctType)(uint8 TransceiverId, uint8 TransceiverMode);\n"
        "typedef void (*CanIf_SimpleRxIndicationFctType)(PduIdType RxPduId, const PduInfoType *PduInfoPtr);\n"
        "typedef union { CanIf_SimpleRxIndicationFctType eSimpleRxIndicationType; } CanIf_RxIndicationFctType;\n"
        "typedef void (*CanIf_TxConfirmationFctType)(PduIdType TxPduId);\n"
        "typedef uint8 CanIf_TxBufferPrioByCanIdBaseType;\n"
        "typedef struct { uint32 CanId; uint8 Sdu[8]; uint8 Length; } CanIf_TxPrioByCanIdType;\n"
        "#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "CanIf_MemMap.h").write_text("/* stub memmap */\n", encoding="utf-8")
    (inc_dir / "CanTp_Cfg.h").write_text(
        "#ifndef CANTP_CFG_H\n#define CANTP_CFG_H\n"
        "#define CanTpConf_CanTpRxNPdu_RxNPdu_0 0u\n"
        "#define CanTpConf_CanTpTxFcNPdu_TxFcNPdu_0 0u\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "CanTp_Cbk.h").write_text(
        "#ifndef CANTP_CBK_H\n#define CANTP_CBK_H\n"
        '#include "ComStack_Types.h"\n'
        "void CanTp_RxIndication(PduIdType id, const PduInfoType *info);\n"
        "void CanTp_TxConfirmation(PduIdType id);\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "PduR_Cfg.h").write_text(
        "#ifndef PDUR_CFG_H\n#define PDUR_CFG_H\n"
        "#define PduRConf_PduRSrcPdu_Src_0 0u\n"
        "#define PduRConf_PduRDestPdu_Dest_0 0u\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "PduR_CanIf.h").write_text(
        "#ifndef PDUR_CANIF_H\n#define PDUR_CANIF_H\n"
        '#include "ComStack_Types.h"\n'
        "void PduR_CanIfRxIndication(PduIdType id, const PduInfoType *info);\n"
        "void PduR_CanIfTxConfirmation(PduIdType id);\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "CanSM_Cbk.h").write_text(
        "#ifndef CANSM_CBK_H\n#define CANSM_CBK_H\n"
        '#include "CanIf_Types.h"\n'
        "void CanSM_ControllerBusOff(uint8 ctrl);\n"
        "void CanSM_ControllerModeIndication(uint8 ctrl, CanIf_ControllerModeType mode);\n"
        "void CanSM_TransceiverModeIndication(uint8 trcv, uint8 mode);\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "Rte_ComM_Type.h").write_text(
        "#ifndef RTE_COMM_TYPE_H\n#define RTE_COMM_TYPE_H\n"
        '#include "Std_Types.h"\n'
        "typedef uint8 ComM_ModeType;\n"
        "typedef uint8 ComM_InhibitionStatusType;\n"
        "typedef uint8 Rte_ModeType_ComMMode;\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "ComM_Types.h").write_text(
        "#ifndef COMM_TYPES_H\n#define COMM_TYPES_H\n"
        '#include "ComStack_Types.h"\n'
        '#include "ComM_GenTypes.h"\n'
        "typedef uint8 ComM_StateType;\n"
        "typedef uint8 ComM_PncModeType;\n"
        "typedef uint8 ComM_InitStatusType;\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "Com_Types.h").write_text("/* stub Com_Types */\n", encoding="utf-8")
    (inc_dir / "Os.h").write_text("/* stub Os */\n", encoding="utf-8")
    (inc_dir / "Det.h").write_text("/* stub Det */\n", encoding="utf-8")
    (inc_dir / "Rte_ComM.h").write_text("/* stub Rte_ComM */\n", encoding="utf-8")
    (inc_dir / "CanSM_ComM.h").write_text(
        "#ifndef CANSM_COMM_H\n#define CANSM_COMM_H\n"
        '#include "ComStack_Types.h"\n'
        '#include "Rte_ComM_Type.h"\n'
        "Std_ReturnType CanSM_GetCurrentComMode(NetworkHandleType Channel, ComM_ModeType *ComMode);\n"
        "Std_ReturnType CanSM_RequestComMode(NetworkHandleType Channel, ComM_ModeType ComMode);\n#endif\n",
        encoding="utf-8",
    )
    (inc_dir / "CanSM.h").write_text("/* stub CanSM */\n", encoding="utf-8")
    (inc_dir / "ComM_MemMap.h").write_text("/* stub ComM memmap */\n", encoding="utf-8")


def _clang_check(c_files, include_dirs) -> None:
    clang_bin = shutil.which("clang")
    if not clang_bin:
        pytest.skip("clang not found in PATH")
    cmd = [clang_bin, "--target=armv8r-none-eabi", "-fsyntax-only", "-Wall", "-Wextra", "-Werror"]
    cmd.extend(f"-I{d}" for d in include_dirs)
    for cf in c_files:
        proc = subprocess.run(cmd + [str(cf)], capture_output=True, text=True)
        assert proc.returncode == 0, f"clang failed for {cf}:\n{proc.stderr}"


def test_canif_csl_generation_and_clang(tmp_path):
    stubs = tmp_path / "stubs"
    _write_stubs(stubs)

    ecuc_def = EcucModuleDef("EcuC", definition_ref="/MICROSAR/EcuC")
    ecuc_cfg = EcucModuleConfiguration("EcuC", definition_ref="/MICROSAR/EcuC")
    pcoll = _c(ecuc_cfg, "EcucPduCollection", "/MICROSAR/EcuC/EcucPduCollection")
    ep_rx_tp = _c(pcoll, "Pdu_RxTp", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    ep_rx_com = _c(pcoll, "Pdu_RxCom", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    ep_tx_tp = _c(pcoll, "Pdu_TxTp", "/MICROSAR/EcuC/EcucPduCollection/Pdu")
    ep_tx_com = _c(pcoll, "Pdu_TxCom", "/MICROSAR/EcuC/EcucPduCollection/Pdu")

    trcv_def = EcucModuleDef("CanTrcv", definition_ref="/MICROSAR/CanTrcv")
    trcv_cfg = EcucModuleConfiguration("CanTrcv", definition_ref="/MICROSAR/CanTrcv")
    cpi = _c(trcv_cfg, "CommonPublishedInformation", "/MICROSAR/CanTrcv/CommonPublishedInformation")
    _p(cpi, "VendorId", 30)
    _p(cpi, "VendorApiInfix", "Tle9255", "ECUC-STRING-PARAM-DEF")

    cantp_def = EcucModuleDef("CanTp", definition_ref="/MICROSAR/CanTp")
    cantp_cfg = EcucModuleConfiguration("CanTp", definition_ref="/MICROSAR/CanTp")
    tpcfg = _c(cantp_cfg, "CanTpConfig", "/MICROSAR/CanTp/CanTpConfig")
    tpch = _c(tpcfg, "TPCH_0", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel")
    tprxns = _c(tpch, "RxNSdu_0", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu")
    tp_rx_npdu = _c(tprxns, "RxNPdu_0", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu/CanTpRxNPdu")
    _r(tp_rx_npdu, "CanTpRxNPduRef", ep_rx_tp.get_path())
    tp_txfc = _c(tprxns, "TxFcNPdu_0", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu/CanTpTxFcNPdu")
    _r(tp_txfc, "CanTpTxFcNPduRef", ep_tx_tp.get_path())

    pdur_def = EcucModuleDef("PduR", definition_ref="/MICROSAR/PduR")
    pdur_cfg = EcucModuleConfiguration("PduR", definition_ref="/MICROSAR/PduR")
    prt = _c(pdur_cfg, "PduRRoutingTables", "/MICROSAR/PduR/PduRRoutingTables")
    prtab = _c(prt, "PduRRoutingTable", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable")
    pr_path_rx = _c(prtab, "PathRx", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
    pr_src = _c(pr_path_rx, "Src_0", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRSrcPdu")
    _r(pr_src, "PduRSrcPduRef", ep_rx_com.get_path())
    pr_path_tx = _c(prtab, "PathTx", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
    pr_dst = _c(pr_path_tx, "Dest_0", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRDestPdu")
    _r(pr_dst, "PduRDestPduRef", ep_tx_com.get_path())

    canif_def = EcucModuleDef("CanIf", definition_ref="/MICROSAR/CanIf")
    canif_cfg = EcucModuleConfiguration("CanIf", definition_ref="/MICROSAR/CanIf")
    priv = _c(canif_cfg, "CanIfPrivateCfg", "/MICROSAR/CanIf/CanIfPrivateCfg")
    _p(priv, "CanIfPrivateDlcCheck", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(priv, "CanIfTransceiverHandling", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(priv, "CanIfSupportExtendedIds", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(priv, "CanIfTxBufferPrioByCanIdSupport", True, "ECUC-BOOLEAN-PARAM-DEF")

    pub = _c(canif_cfg, "CanIfPublicCfg", "/MICROSAR/CanIf/CanIfPublicCfg")
    _p(pub, "CanIfPublicDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(pub, "CanIfPublicTxBuffering", True, "ECUC-BOOLEAN-PARAM-DEF")

    disp = _c(canif_cfg, "CanIfDispatchCfg", "/MICROSAR/CanIf/CanIfDispatchCfg")
    _p(disp, "CanIfDispatchUserCtrlBusOffName", "CanSM_ControllerBusOff", "ECUC-STRING-PARAM-DEF")
    _p(disp, "CanIfDispatchUserCtrlModeIndicationName", "CanSM_ControllerModeIndication", "ECUC-STRING-PARAM-DEF")
    _p(disp, "CanIfDispatchUserTrcvModeIndicationName", "CanSM_TransceiverModeIndication", "ECUC-STRING-PARAM-DEF")

    cdrv = _c(canif_cfg, "CanIfCtrlDrvCfg_0", "/MICROSAR/CanIf/CanIfCtrlDrvCfg")
    _p(cdrv, "CanIfCtrlDrvTxCancellation", False, "ECUC-BOOLEAN-PARAM-DEF")
    ctrl = _c(cdrv, "CT_Motor", "/MICROSAR/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg")
    _p(ctrl, "CanIfCtrlId", 0)

    tdrv = _c(canif_cfg, "CanIfTrcvDrvCfg_0", "/MICROSAR/CanIf/CanIfTrcvDrvCfg")
    trcv = _c(tdrv, "Trcv_0", "/MICROSAR/CanIf/CanIfTrcvDrvCfg/CanIfTrcvCfg")
    _p(trcv, "CanIfTrcvId", 0)

    init = _c(canif_cfg, "CanIfInitCfg", "/MICROSAR/CanIf/CanIfInitCfg")
    hoh = _c(init, "CanIfInitHohCfg", "/MICROSAR/CanIf/CanIfInitCfg/CanIfInitHohCfg")
    hth = _c(hoh, "Hth_0", "/MICROSAR/CanIf/CanIfInitCfg/CanIfInitHohCfg/CanIfHthCfg")
    _r(hth, "CanIfHthCanCtrlIdRef", ctrl.get_path())
    hrh = _c(hoh, "Hrh_0", "/MICROSAR/CanIf/CanIfInitCfg/CanIfInitHohCfg/CanIfHrhCfg")
    _r(hrh, "CanIfHrhCanCtrlIdRef", ctrl.get_path())

    buf = _c(init, "Buf_0", "/MICROSAR/CanIf/CanIfInitCfg/CanIfBufferCfg")
    _r(buf, "CanIfBufferHthRef", hth.get_path())

    rx0 = _c(init, "Rx_Tp", "/MICROSAR/CanIf/CanIfInitCfg/CanIfRxPduCfg")
    _p(rx0, "CanIfRxPduId", 0)
    _p(rx0, "CanIfRxPduCanId", 0x7EC)
    _p(rx0, "CanIfRxPduDlc", 8)
    _p(rx0, "CanIfRxPduUserRxIndicationUL", "CAN_TP", "ECUC-ENUMERATION-PARAM-DEF")
    _p(rx0, "CanIfRxPduUserRxIndicationName", "CanTp_RxIndication", "ECUC-STRING-PARAM-DEF")
    _r(rx0, "CanIfRxPduRef", ep_rx_tp.get_path())

    rx1 = _c(init, "Rx_Com", "/MICROSAR/CanIf/CanIfInitCfg/CanIfRxPduCfg")
    _p(rx1, "CanIfRxPduId", 1)
    _p(rx1, "CanIfRxPduCanId", 0x185)
    _p(rx1, "CanIfRxPduDlc", 8)
    _p(rx1, "CanIfRxPduUserRxIndicationUL", "PDUR", "ECUC-ENUMERATION-PARAM-DEF")
    _p(rx1, "CanIfRxPduUserRxIndicationName", "PduR_CanIfRxIndication", "ECUC-STRING-PARAM-DEF")
    _r(rx1, "CanIfRxPduRef", ep_rx_com.get_path())

    tx0 = _c(init, "Tx_Tp", "/MICROSAR/CanIf/CanIfInitCfg/CanIfTxPduCfg")
    _p(tx0, "CanIfTxPduId", 0)
    _p(tx0, "CanIfTxPduCanId", 0x7DF)
    _p(tx0, "CanIfTxPduDlc", 8)
    _p(tx0, "CanIfTxPduTruncation", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(tx0, "CanIfTxPduUserTxConfirmationUL", "CAN_TP", "ECUC-ENUMERATION-PARAM-DEF")
    _p(tx0, "CanIfTxPduUserTxConfirmationName", "CanTp_TxConfirmation", "ECUC-STRING-PARAM-DEF")
    _r(tx0, "CanIfTxPduBufferRef", buf.get_path())
    _r(tx0, "CanIfTxPduRef", ep_tx_tp.get_path())

    tx1 = _c(init, "Tx_Com", "/MICROSAR/CanIf/CanIfInitCfg/CanIfTxPduCfg")
    _p(tx1, "CanIfTxPduId", 1)
    _p(tx1, "CanIfTxPduCanId", 0x224)
    _p(tx1, "CanIfTxPduDlc", 8)
    _p(tx1, "CanIfTxPduTruncation", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(tx1, "CanIfTxPduUserTxConfirmationUL", "PDUR", "ECUC-ENUMERATION-PARAM-DEF")
    _p(tx1, "CanIfTxPduUserTxConfirmationName", "PduR_CanIfTxConfirmation", "ECUC-STRING-PARAM-DEF")
    _r(tx1, "CanIfTxPduBufferRef", buf.get_path())
    _r(tx1, "CanIfTxPduRef", ep_tx_com.get_path())

    out_dir = tmp_path / "canif_out"
    gen = CodeGenerator(
        canif_def,
        canif_cfg,
        project_template_dir=_TEMPLATE_PACK,
        all_configurations={
            "CanIf": (canif_def, canif_cfg),
            "CanTrcv": (trcv_def, trcv_cfg),
            "CanTp": (cantp_def, cantp_cfg),
            "PduR": (pdur_def, pdur_cfg),
            "EcuC": (ecuc_def, ecuc_cfg),
        },
    )
    assert gen.generate_all(out_dir, force=True) is True

    inc_dir = out_dir / "CanIf" / "include"
    src_dir = out_dir / "CanIf" / "src"
    assert {p.name for p in inc_dir.iterdir()} == {"CanIf_Can.h", "CanIf_CanTrcv.h", "CanIf_Cfg.h"}
    assert {p.name for p in src_dir.iterdir()} == {"CanIf_Lcfg.c", "CanIf_PBcfg.c"}

    for p in list(inc_dir.iterdir()) + list(src_dir.iterdir()):
        txt = p.read_text(encoding="utf-8")
        assert "[!" not in txt and "!]" not in txt, f"Unexpanded tag in {p.name}"

    lcfg_c = (src_dir / "CanIf_Lcfg.c").read_text(encoding="utf-8")
    assert "CanTpConf_CanTpRxNPdu_RxNPdu_0" in lcfg_c
    assert "CanTpConf_CanTpTxFcNPdu_TxFcNPdu_0" in lcfg_c
    assert "PduRConf_PduRSrcPdu_Src_0" in lcfg_c
    assert "PduRConf_PduRDestPdu_Dest_0" in lcfg_c

    _clang_check([src_dir / "CanIf_Lcfg.c", src_dir / "CanIf_PBcfg.c"], [inc_dir, stubs])


def test_comm_csl_generation_and_clang(tmp_path):
    stubs = tmp_path / "stubs"
    _write_stubs(stubs)

    for num_ch in (1, 2):
        out_dir = tmp_path / f"comm_{num_ch}"
        comm_def = EcucModuleDef("ComM", definition_ref="/MICROSAR/ComM")
        comm_cfg = EcucModuleConfiguration("ComM", definition_ref="/MICROSAR/ComM")
        gen_c = _c(comm_cfg, "ComMGeneral", "/MICROSAR/ComM/ComMGeneral")
        _p(gen_c, "ComMDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
        _p(gen_c, "ComMModeLimitationEnabled", True, "ECUC-BOOLEAN-PARAM-DEF")
        _p(gen_c, "ComMEcuGroupClassification", 3)

        cs = _c(comm_cfg, "ComMConfigSet", "/MICROSAR/ComM/ComMConfigSet")
        usr = _c(cs, "Usr_0", "/MICROSAR/ComM/ComMConfigSet/ComMUser")
        _p(usr, "ComMUserIdentifier", 0)
        for ch_idx in range(num_ch):
            ch = _c(cs, f"Ch_{ch_idx}", "/MICROSAR/ComM/ComMConfigSet/ComMChannel")
            _p(ch, "ComMChannelId", ch_idx)

        gen = CodeGenerator(
            comm_def,
            comm_cfg,
            project_template_dir=_TEMPLATE_PACK,
            all_configurations={"ComM": (comm_def, comm_cfg)},
        )
        assert gen.generate_all(out_dir, force=True) is True

        inc_dir = out_dir / "ComM" / "include"
        src_dir = out_dir / "ComM" / "src"
        assert {p.name for p in inc_dir.iterdir()} == {
            "ComM_GenTypes.h",
            "ComM_Lcfg.h",
            "ComM_Cfg.h",
            "ComM_Private_Cfg.h",
        }
        assert {p.name for p in src_dir.iterdir()} == {"ComM_Lcfg.c"}

        for p in list(inc_dir.iterdir()) + list(src_dir.iterdir()):
            txt = p.read_text(encoding="utf-8")
            assert "[!" not in txt and "!]" not in txt, f"Unexpanded tag in {p.name}"

        cfg_h = (inc_dir / "ComM_Cfg.h").read_text(encoding="utf-8")
        lcfg_c = (src_dir / "ComM_Lcfg.c").read_text(encoding="utf-8")
        assert "ComMConf_ComMChannel_Ch_0 0u" in cfg_h
        assert "ComMChannel_0;" in cfg_h
        assert "0x03;" in lcfg_c
        assert "ComM_MainFunction_0(void)" in lcfg_c
        if num_ch == 2:
            assert "ComMChannel_1;" in cfg_h
            assert "ComM_MainFunction_1(void)" in lcfg_c

        _clang_check([src_dir / "ComM_Lcfg.c"], [inc_dir, stubs])


def test_real_startapplication_comm_canif_parity():
    if not _REAL_DPA.exists() or not _REAL_GENDATA.exists():
        pytest.skip("Read-only StartApplication1 reference project not available")

    rep = audit_project_templates(
        _REAL_DPA,
        ref_gendata_dir=_REAL_GENDATA,
        template_pack_dir=_TEMPLATE_PACK,
        include_platform_gen=False,
        include_rte_phase2_3=False,
    )
    by_mod = {m.module_name: m for m in rep.module_results}
    canif = by_mod["CanIf"]
    comm = by_mod["ComM"]

    assert canif.status == "OK" and not canif.unexpanded_files
    assert canif.matched_ref_count == 5
    assert canif.define_ref_total > 0 and canif.define_match_total / canif.define_ref_total >= 0.95
    assert canif.sym_match_total == canif.sym_ref_total

    assert comm.status == "OK" and not comm.unexpanded_files
    assert comm.matched_ref_count == 5
    assert comm.define_ref_total > 0 and comm.define_match_total / comm.define_ref_total >= 0.95
    assert comm.sym_match_total == comm.sym_ref_total
