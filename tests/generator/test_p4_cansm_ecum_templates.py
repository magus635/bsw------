"""Tests for P4-2 Batch 1 MICROSAR CSL EB templates (CanSM & EcuM) and template-pack audit."""

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


def _write_common_stubs(inc_dir: Path) -> None:
    inc_dir.mkdir(parents=True, exist_ok=True)
    (inc_dir / "Std_Types.h").write_text(
        "#ifndef STD_TYPES_H\n"
        "#define STD_TYPES_H\n"
        "typedef unsigned char boolean;\n"
        "typedef unsigned char uint8;\n"
        "typedef unsigned short uint16;\n"
        "typedef unsigned long uint32;\n"
        "typedef unsigned long uint8_least;\n"
        "typedef uint8 Std_ReturnType;\n"
        "#ifndef TRUE\n#define TRUE ((boolean)1u)\n#endif\n"
        "#ifndef FALSE\n#define FALSE ((boolean)0u)\n#endif\n"
        "#ifndef STD_ON\n#define STD_ON 1u\n#endif\n"
        "#ifndef STD_OFF\n#define STD_OFF 0u\n#endif\n"
        "#ifndef NULL_PTR\n#define NULL_PTR ((void*)0)\n#endif\n"
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
        '#include "Std_Types.h"\n'
        "typedef uint8 NetworkHandleType;\n",
        encoding="utf-8",
    )
    (inc_dir / "ComM.h").write_text(
        '#include "Std_Types.h"\n'
        "typedef uint8 ComM_ModeType;\n"
        "#define ComMConf_ComMChannel_CN_MotorDomain_7dbd6036 0u\n",
        encoding="utf-8",
    )
    (inc_dir / "CanSM_Int.h").write_text(
        '#include "ComM.h"\n'
        "typedef struct { uint16 CanSM_UniversalTimer; uint8 CanSM_CurrentState; } CanSM_ChannelVarRecordType;\n",
        encoding="utf-8",
    )
    (inc_dir / "CanSM_EcuM.h").write_text('#include "CanSM_Cfg.h"\n', encoding="utf-8")
    (inc_dir / "CanSM_MemMap.h").write_text("/* stub memmap */\n", encoding="utf-8")
    (inc_dir / "Rte_EcuM_Type.h").write_text(
        '#include "Std_Types.h"\n'
        "typedef uint8 EcuM_StateType;\n"
        "typedef uint8 EcuM_ModeType;\n",
        encoding="utf-8",
    )
    (inc_dir / "Os.h").write_text(
        '#include "Std_Types.h"\n'
        "typedef uint32 AppModeType;\n"
        "#define OSDEFAULTAPPMODE ((AppModeType)1u)\n"
        "#define SystemApplication_OsCore0 0u\n"
        "#define SystemApplication_OsCore1 1u\n"
        "void SuspendAllInterrupts(void);\n"
        "void ResumeAllInterrupts(void);\n",
        encoding="utf-8",
    )
    (inc_dir / "Mcu.h").write_text(
        '#include "Std_Types.h"\n'
        "typedef uint8 Mcu_ModeType;\n"
        "#define McuConf_McuModeSettingConf_McuModeSettingConf_0 0u\n",
        encoding="utf-8",
    )
    (inc_dir / "Det.h").write_text(
        '#include "Std_Types.h"\n'
        "#define ECUM_MODULE_ID 10u\n"
        "#define ECUM_INSTANCE_ID 0u\n"
        "void Det_ReportError(uint16 m, uint8 i, uint8 a, uint8 e);\n",
        encoding="utf-8",
    )
    (inc_dir / "EcuM.h").write_text(
        '#include "EcuM_Generated_Types.h"\n'
        '#include "EcuM_Cfg.h"\n'
        "#define ECUM_PRIVATE_CFG_INCLUDE\n"
        '#include "EcuM_PrivateCfg.h"\n'
        "#undef ECUM_PRIVATE_CFG_INCLUDE\n",
        encoding="utf-8",
    )
    (inc_dir / "EcuM_Cbk.h").write_text(
        '#include "EcuM_Generated_Types.h"\n'
        '#include "EcuM_Cfg.h"\n',
        encoding="utf-8",
    )
    (inc_dir / "EcuM_MemMap.h").write_text("/* stub memmap */\n", encoding="utf-8")


def _clang_check(c_files, include_dirs) -> None:
    clang_bin = shutil.which("clang")
    if not clang_bin:
        pytest.skip("clang not found in PATH")
    cmd = [clang_bin, "--target=armv8r-none-eabi", "-fsyntax-only", "-Wall", "-Wextra", "-Werror"]
    cmd.extend(f"-I{d}" for d in include_dirs)
    for cf in c_files:
        proc = subprocess.run(cmd + [str(cf)], capture_output=True, text=True)
        assert proc.returncode == 0, f"clang failed for {cf}:\n{proc.stderr}"


def _build_cansm_configs(multi_channel: bool):
    comm_def = EcucModuleDef("ComM", definition_ref="/MICROSAR/ComM")
    comm_cfg = EcucModuleConfiguration("ComM", definition_ref="/MICROSAR/ComM")
    cs_comm = _c(comm_cfg, "ComMConfigSet", "/MICROSAR/ComM/ComMConfigSet")
    ch0 = _c(cs_comm, "CN_MotorDomain_7dbd6036", "/MICROSAR/ComM/ComMConfigSet/ComMChannel")
    _p(ch0, "ComMChannelId", 0)
    ch1 = _c(cs_comm, "CN_DiagDomain_0001", "/MICROSAR/ComM/ComMConfigSet/ComMChannel")
    _p(ch1, "ComMChannelId", 1)

    canif_def = EcucModuleDef("CanIf", definition_ref="/MICROSAR/CanIf")
    canif_cfg = EcucModuleConfiguration("CanIf", definition_ref="/MICROSAR/CanIf")
    ctrl_drv = _c(canif_cfg, "CanIfCtrlDrvCfg_0", "/MICROSAR/CanIf/CanIfCtrlDrvCfg")
    c0 = _c(ctrl_drv, "CT_MotorDomain", "/MICROSAR/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg")
    _p(c0, "CanIfCtrlId", 0)
    c1 = _c(ctrl_drv, "CT_DiagDomain", "/MICROSAR/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg")
    _p(c1, "CanIfCtrlId", 1)
    trcv_drv = _c(canif_cfg, "CanIfTrcvDrvCfg_0", "/MICROSAR/CanIf/CanIfTrcvDrvCfg")
    t0 = _c(trcv_drv, "CanIfTrcvCfg", "/MICROSAR/CanIf/CanIfTrcvDrvCfg/CanIfTrcvCfg")
    _p(t0, "CanIfTrcvId", 0)

    cansm_def = EcucModuleDef("CanSM", definition_ref="/MICROSAR/CanSM")
    cansm_cfg = EcucModuleConfiguration("CanSM", definition_ref="/MICROSAR/CanSM")
    gen = _c(cansm_cfg, "CanSMGeneral", "/MICROSAR/CanSM/CanSMGeneral")
    _p(gen, "CanSMDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(gen, "CanSMVersionInfoApi", False, "ECUC-BOOLEAN-PARAM-DEF")
    _p(gen, "CanSMMainFunctionTimePeriod", 0.01, "ECUC-FLOAT-PARAM-DEF")

    cfg_set = _c(cansm_cfg, "CanSMConfiguration", "/MICROSAR/CanSM/CanSMConfiguration")
    _p(cfg_set, "CanSMModeRequestRepetitionMax", 10)
    _p(cfg_set, "CanSMModeRequestRepetitionTime", 0.1, "ECUC-FLOAT-PARAM-DEF")

    n0 = _c(cfg_set, "CHNL_0", "/MICROSAR/CanSM/CanSMConfiguration/CanSMManagerNetwork")
    _p(n0, "CanSMBorCounterL1ToL2", 5)
    _p(n0, "CanSMBorTimeL1", 1.0, "ECUC-FLOAT-PARAM-DEF")
    _p(n0, "CanSMBorTimeL2", 3.0, "ECUC-FLOAT-PARAM-DEF")
    _p(n0, "CanSMBorTimeTxEnsured", 5.0, "ECUC-FLOAT-PARAM-DEF")
    _p(n0, "CanSMBorTxConfirmationPolling", False, "ECUC-BOOLEAN-PARAM-DEF")
    _r(n0, "CanSMComMNetworkHandleRef", ch0.get_path())
    _r(n0, "CanSMTransceiverId", t0.get_path())
    nc0 = _c(n0, "CT_0", "/MICROSAR/CanSM/CanSMConfiguration/CanSMManagerNetwork/CanSMController")
    _r(nc0, "CanSMControllerId", c0.get_path())

    if multi_channel:
        n1 = _c(cfg_set, "CHNL_1", "/MICROSAR/CanSM/CanSMConfiguration/CanSMManagerNetwork")
        _p(n1, "CanSMBorCounterL1ToL2", 3)
        _p(n1, "CanSMBorTimeL1", 0.5, "ECUC-FLOAT-PARAM-DEF")
        _p(n1, "CanSMBorTimeL2", 2.0, "ECUC-FLOAT-PARAM-DEF")
        _p(n1, "CanSMBorTimeTxEnsured", 4.0, "ECUC-FLOAT-PARAM-DEF")
        _p(n1, "CanSMBorTxConfirmationPolling", True, "ECUC-BOOLEAN-PARAM-DEF")
        _r(n1, "CanSMComMNetworkHandleRef", ch1.get_path())
        nc1 = _c(n1, "CT_1", "/MICROSAR/CanSM/CanSMConfiguration/CanSMManagerNetwork/CanSMController")
        _r(nc1, "CanSMControllerId", c1.get_path())

    all_cfgs = {
        "CanSM": (cansm_def, cansm_cfg),
        "ComM": (comm_def, comm_cfg),
        "CanIf": (canif_def, canif_cfg),
    }
    return cansm_def, cansm_cfg, all_cfgs


def test_cansm_csl_single_and_multi_channel(tmp_path):
    stubs = tmp_path / "stubs"
    _write_common_stubs(stubs)

    for multi in (False, True):
        out_dir = tmp_path / ("multi" if multi else "single")
        mdef, mcfg, all_cfgs = _build_cansm_configs(multi_channel=multi)
        gen = CodeGenerator(
            mdef,
            mcfg,
            project_template_dir=_TEMPLATE_PACK,
            all_configurations=all_cfgs,
        )
        assert gen.generate_all(out_dir, force=True) is True

        cfg_h = (out_dir / "CanSM" / "include" / "CanSM_Cfg.h").read_text(encoding="utf-8")
        lcfg_c = (out_dir / "CanSM" / "src" / "CanSM_Lcfg.c").read_text(encoding="utf-8")
        assert "[!" not in cfg_h and "[!" not in lcfg_c
        assert "CanSM_GetModeRequestRepetitionMaxOfPCConfig()" in cfg_h
        assert "CanSM_ChannelVarRecord" in cfg_h and "CanSM_ChannelVarRecord" in lcfg_c

        if multi:
            assert "CanSM_GetSizeOfChannelConfigOfPCConfig()                                                    2u" in cfg_h
            assert "#define CANSM_ISDEF_BORCOUNTERL1TOL2OFCHANNELCONFIG                                                 STD_OFF" in cfg_h
            assert "extern CONST(CanSM_ChannelConfigType, CANSM_CONST) CanSM_ChannelConfig[2];" in cfg_h
            assert "CONST(CanSM_ChannelConfigType, CANSM_CONST) CanSM_ChannelConfig[2] =" in lcfg_c
        else:
            assert "CanSM_GetSizeOfChannelConfigOfPCConfig()                                                    1u" in cfg_h
            assert "#define CANSM_EQ2_BORTIMEL1OFCHANNELCONFIG                                                          100u" in cfg_h
            assert "CanSM_ChannelConfigNeverUsed" in cfg_h
            assert "CONST(CanSM_ChannelConfigType" not in lcfg_c

        _clang_check(
            [out_dir / "CanSM" / "src" / "CanSM_Lcfg.c"],
            [out_dir / "CanSM" / "include", stubs],
        )


def test_ecum_csl_generation_and_clang(tmp_path):
    stubs = tmp_path / "stubs"
    _write_common_stubs(stubs)

    ecuc_def = EcucModuleDef("EcuC", definition_ref="/MICROSAR/EcuC")
    ecuc_cfg = EcucModuleConfiguration("EcuC", definition_ref="/MICROSAR/EcuC")
    pcoll = _c(ecuc_cfg, "EcucPartitionCollection", "/MICROSAR/EcuC/EcucPartitionCollection")
    ep0 = _c(pcoll, "EcucPartition_core0", "/MICROSAR/EcuC/EcucPartitionCollection/EcucPartition")
    ep1 = _c(pcoll, "EcucPartition_core1", "/MICROSAR/EcuC/EcucPartitionCollection/EcucPartition")

    os_def = EcucModuleDef("Os", definition_ref="/MICROSAR/Os")
    os_cfg = EcucModuleConfiguration("Os", definition_ref="/MICROSAR/Os")
    app0 = _c(os_cfg, "SystemApplication_OsCore0", "/MICROSAR/Os/OsApplication")
    _r(app0, "OsAppEcucPartitionRef", ep0.get_path())
    app1 = _c(os_cfg, "SystemApplication_OsCore1", "/MICROSAR/Os/OsApplication")
    _r(app1, "OsAppEcucPartitionRef", ep1.get_path())
    app_mode = _c(os_cfg, "OSDEFAULTAPPMODE", "/MICROSAR/Os/OsAppMode")
    os_res = _c(os_cfg, "OsResource", "/MICROSAR/Os/OsResource")

    comm_def = EcucModuleDef("ComM", definition_ref="/MICROSAR/ComM")
    comm_cfg = EcucModuleConfiguration("ComM", definition_ref="/MICROSAR/ComM")
    cm_cs = _c(comm_cfg, "ComMConfigSet", "/MICROSAR/ComM/ComMConfigSet")
    cm_ch = _c(cm_cs, "CN_MotorDomain_7dbd6036", "/MICROSAR/ComM/ComMConfigSet/ComMChannel")

    mcu_def = EcucModuleDef("Mcu", definition_ref="/MICROSAR/Mcu")
    mcu_cfg = EcucModuleConfiguration("Mcu", definition_ref="/MICROSAR/Mcu")
    mcu_mc = _c(mcu_cfg, "McuModuleConfiguration", "/MICROSAR/Mcu/McuModuleConfiguration")
    mcu_mode = _c(mcu_mc, "McuModeSettingConf_0", "/MICROSAR/Mcu/McuModuleConfiguration/McuModeSettingConf")

    ecum_def = EcucModuleDef("EcuM", definition_ref="/MICROSAR/EcuM")
    ecum_cfg = EcucModuleConfiguration("EcuM", definition_ref="/MICROSAR/EcuM")
    eg = _c(ecum_cfg, "EcuMGeneral", "/MICROSAR/EcuM/EcuMGeneral")
    _p(eg, "EcuMDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(eg, "EcuMSlaveCoreHandling", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(eg, "EcuMSchMStartInitialization", True, "ECUC-BOOLEAN-PARAM-DEF")
    efg = _c(ecum_cfg, "EcuMFlexGeneral", "/MICROSAR/EcuM/EcuMFlexGeneral")
    _p(efg, "EcuMAlarmClockPresent", False, "ECUC-BOOLEAN-PARAM-DEF")

    ec = _c(ecum_cfg, "EcuMConfiguration", "/MICROSAR/EcuM/EcuMConfiguration")
    ecc = _c(ec, "EcuMCommonConfiguration", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration")
    _r(ecc, "EcuMDefaultAppMode", app_mode.get_path())
    _r(ecc, "EcuMOSResource", os_res.get_path())
    dst = _c(ecc, "EcuMDefaultShutdownTarget", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultShutdownTarget")
    _p(dst, "EcuMDefaultState", "EcuMStateOff", "ECUC-ENUMERATION-PARAM-DEF")

    # Add wakeup sources intentionally out of order
    for name, wkid, has_comm in [
        ("ECUM_WKSOURCE_POWER", 0, False),
        ("ECUM_WKSOURCE_INTERNAL_WDG", 3, False),
        ("ECUM_WKSOURCE_INTERNAL_RESET", 2, False),
        ("ECUM_WKSOURCE_RESET", 1, False),
        ("ECUM_WKSOURCE_EXTERNAL_WDG", 4, False),
        ("CN_MotorDomain_7dbd6036", 5, True),
    ]:
        wk = _c(ecc, name, "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource")
        _p(wk, "EcuMWakeupSourceId", wkid)
        if has_comm:
            _r(wk, "EcuMComMChannelRef", cm_ch.get_path())

    efc = _c(ec, "EcuMFlexConfiguration", "/MICROSAR/EcuM/EcuMConfiguration/EcuMFlexConfiguration")
    _r(efc, "EcuMNormalMcuModeRef", mcu_mode.get_path())
    efc.add_multi_reference_value("EcuMPartitionRef", ep1.get_path(), f"{efc.definition_ref}/EcuMPartitionRef", 0)
    efc.add_multi_reference_value("EcuMPartitionRef", ep0.get_path(), f"{efc.definition_ref}/EcuMPartitionRef", 1)
    for i in range(4):
        rm = _c(efc, f"RESET_{i}", "/MICROSAR/EcuM/EcuMConfiguration/EcuMFlexConfiguration/EcuMResetMode")
        _p(rm, "EcuMResetModeId", i)
        sc = _c(efc, f"CAUSE_{i}", "/MICROSAR/EcuM/EcuMConfiguration/EcuMFlexConfiguration/EcuMShutdownCause")
        _p(sc, "EcuMShutdownCauseId", i)

    all_cfgs = {
        "EcuM": (ecum_def, ecum_cfg),
        "EcuC": (ecuc_def, ecuc_cfg),
        "Os": (os_def, os_cfg),
        "ComM": (comm_def, comm_cfg),
        "Mcu": (mcu_def, mcu_cfg),
    }

    out_dir = tmp_path / "out"
    gen = CodeGenerator(
        ecum_def,
        ecum_cfg,
        project_template_dir=_TEMPLATE_PACK,
        all_configurations=all_cfgs,
    )
    assert gen.generate_all(out_dir, force=True) is True

    inc_dir = out_dir / "EcuM" / "include"
    src_dir = out_dir / "EcuM" / "src"
    expected_inc = {
        "EcuM_Cfg.h",
        "EcuM_PrivateCfg.h",
        "EcuM_Generated_Types.h",
        "EcuM_Init_Cfg.h",
        "EcuM_Init_PBcfg.h",
    }
    expected_src = {
        "EcuM_Cfg.c",
        "EcuM_Init_Cfg.c",
        "EcuM_Init_PBcfg.c",
        "EcuM_PBcfg.c",
    }
    assert {p.name for p in inc_dir.iterdir()} == expected_inc
    assert {p.name for p in src_dir.iterdir()} == expected_src

    for p in list(inc_dir.iterdir()) + list(src_dir.iterdir()):
        txt = p.read_text(encoding="utf-8")
        assert "[!" not in txt and "!]" not in txt, f"Unexpanded tag in {p.name}"

    gen_types = (inc_dir / "EcuM_Generated_Types.h").read_text(encoding="utf-8")
    assert "#define ECUM_WKSOURCE_POWER (EcuM_WakeupSourceType)(1u)" in gen_types
    assert "#define ECUM_WKSOURCE_CN_MotorDomain_7dbd6036 (EcuM_WakeupSourceType)(32u)" in gen_types

    cfg_c = (src_dir / "EcuM_Cfg.c").read_text(encoding="utf-8")
    assert "EcuM_CoreStatus_SystemApplication_OsCore1" in cfg_c
    assert "EcuM_CoreStatus_SystemApplication_OsCore0" in cfg_c
    assert "SystemApplication_OsCore0" in cfg_c
    assert "SystemApplication_OsCore1" in cfg_c

    _clang_check(
        [src_dir / f for f in sorted(expected_src)],
        [inc_dir, stubs],
    )


def test_real_startapplication_cansm_ecum_parity():
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
    cansm = by_mod["CanSM"]
    ecum = by_mod["EcuM"]

    assert cansm.status == "OK" and not cansm.unexpanded_files
    assert cansm.matched_ref_count == 2
    assert cansm.define_ref_total > 0 and cansm.define_match_total / cansm.define_ref_total >= 0.95
    assert cansm.sym_match_total == cansm.sym_ref_total

    assert ecum.status == "OK" and not ecum.unexpanded_files
    assert ecum.matched_ref_count == 9
    assert ecum.define_ref_total > 0 and ecum.define_match_total / ecum.define_ref_total >= 0.95
    assert ecum.sym_match_total == ecum.sym_ref_total
