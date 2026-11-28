"""Tests for P4-1 platform generators (ComStack/MemMap/vBRS), RTE companion headers, and TemplateAuditService."""

from pathlib import Path
import re
import shutil
import subprocess

import pytest

from autosar_configurator.core.model.configuration_model import EcucContainerValue, EcucModuleConfiguration
from autosar_configurator.core.model.definition_model import EcucModuleDef
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator import (
    audit_project_templates,
    generate_platform_artifacts,
    render_comstack_cfg_h,
    render_module_memmap_h,
    render_vbrs_files,
)
from autosar_configurator.generator.rte import RteSchMGenerator
from tests.generator.test_rte_phase2_phase3 import build_phase23_project
from tools.audit_templates import main as audit_cli_main


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


def _build_platform_project(tmp_path: Path):
    proj_dir = tmp_path / "plat_proj"
    proj_dir.mkdir(parents=True, exist_ok=True)
    ws = WorkspaceManager()
    project = ws.create_project("PlatProj", proj_dir / "PlatProj.dpa", format_version=8)

    mods = {}
    for mod in ("EcuC", "vBRS", "vBaseEnv", "Os", "BswM"):
        mdef = EcucModuleDef(mod, definition_ref=f"/MICROSAR/{mod}")
        mgr = project.add_module(mdef, proj_dir / "config" / f"{mod}.arxml")
        mods[mod] = mgr.configuration

    pdu_coll = _c(mods["EcuC"], "EcucPduCollection", "/MICROSAR/EcuC/EcucPduCollection")
    _p(pdu_coll, "PduIdTypeEnum", "UINT16", "ECUC-ENUMERATION-PARAM-DEF")
    _p(pdu_coll, "PduLengthTypeEnum", "UINT32", "ECUC-ENUMERATION-PARAM-DEF")

    vbrs_gen = _c(mods["vBRS"], "vBRSGeneral", "/MICROSAR/vBRS/vBRSGeneral")
    _p(vbrs_gen, "vBRSEnableMultiCoreSupport", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(vbrs_gen, "vBRSFirstInstance", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(vbrs_gen, "vBRSExecutionInstance", "Application", "ECUC-ENUMERATION-PARAM-DEF")

    hw = _c(mods["vBRS"], "vBRSHwConfig", "/MICROSAR/vBRS/vBRSHwConfig")
    _p(hw, "vBRSOscClock", 25000000)
    _p(hw, "vBRSTimebaseClock", 400000000)
    _p(hw, "vBRSPeriphClock", 25000000)
    _p(hw, "vBRSCompilerInstructionSet", "ARM", "ECUC-ENUMERATION-PARAM-DEF")
    _p(hw, "vBRSCompilerEnableFPU", True, "ECUC-BOOLEAN-PARAM-DEF")

    mi = _c(mods["vBRS"], "vBRSMemoryInit", "/MICROSAR/vBRS/vBRSMemoryInit")
    _p(mi, "vBRSInitPatternBlocks", 0)
    _p(mi, "vBRSInitPatternHardResetBlocks", 0)
    _p(mi, "vBRSInitPatternAreas", 0)
    _p(mi, "vBRSInitPatternHardResetAreas", 0)

    vb_gen = _c(mods["vBaseEnv"], "vBaseEnvGeneral", "/MICROSAR/vBaseEnv/vBaseEnvGeneral")
    _r(vb_gen, "vBaseEnvTestedDerivativeRef", "/ActiveEcuC/vBaseEnv/vBaseEnvGeneral/Tongxin_THA6206")
    deriv = _c(vb_gen, "Tongxin_THA6206", "/MICROSAR/vBaseEnv/vBaseEnvGeneral/vBaseEnvDerivativeInformation")
    _p(deriv, "vBaseEnvTestedDerivative", "Tongxin_THA6206", "ECUC-STRING-PARAM-DEF")
    _p(deriv, "vBaseEnvCpuCore", "CORTEX_R52", "ECUC-STRING-PARAM-DEF")
    _p(deriv, "vBaseEnvCpuMaxFrequency", 400000000)
    _p(deriv, "vBaseEnvCpuCoreAmount", 2)

    _c(mods["Os"], "OsCore0", "/MICROSAR/Os/OsCore")
    _c(mods["Os"], "OsCore1", "/MICROSAR/Os/OsCore")
    return project, proj_dir


def test_comstack_cfg_and_vbrs_generators(tmp_path):
    project, _ = _build_platform_project(tmp_path)

    cs = render_comstack_cfg_h(project)
    assert cs is not None
    assert "typedef uint16 PduIdType;" in cs
    assert "typedef uint32 PduLengthType;" in cs

    vbrs_files = render_vbrs_files(project)
    assert set(vbrs_files.keys()) == {
        "vBrsCfg.h",
        "vBrs_Lcfg.h",
        "vBrs_Lcfg.c",
        "Makefile.config.generated",
    }
    cfg_h = vbrs_files["vBrsCfg.h"]
    assert "#define BRS_OSC_CLK 25" in cfg_h
    assert "#define BRS_TIMEBASE_CLOCK 400" in cfg_h
    assert "#define BRS_PERIPH_CLOCK 25" in cfg_h
    assert "#define BRS_DERIVATIVE_Tongxin_THA6206" in cfg_h
    assert "#define BRS_CPU_CORE_CORTEX_R52" in cfg_h
    assert "#define BRS_CPU_CORE_AMOUNT 2" in cfg_h
    assert "#define BRS_ENABLE_OS_MULTICORESUPPORT" in cfg_h
    assert "#define BRS_INSTRUCTION_SET_ARM" in cfg_h
    assert "#define BRS_FPU_USED" in cfg_h

    mk = vbrs_files["Makefile.config.generated"]
    assert "DERIVATIVE = Tongxin_THA6206" in mk
    assert "BRS_CPU_CORE_0_USED = 1" in mk
    assert "BRS_CPU_CORE_1_USED = 1" in mk
    assert "BRS_CPU_CORE_2_USED = 0" in mk
    assert "CPU_CORE = CORTEX_R52" in mk
    assert "FPU_USED = 1" in mk

    out_dir = tmp_path / "out"
    rep = generate_platform_artifacts(project, out_dir, flat=False)
    assert (out_dir / "EcuC/include/ComStack_Cfg.h").is_file()
    assert (out_dir / "vBRS/include/vBrsCfg.h").is_file()
    assert (out_dir / "vBRS/src/vBrs_Lcfg.c").is_file()
    assert (out_dir / "Makefile.config.generated").is_file()
    assert (out_dir / "MemMap/include/BswM_MemMap.h").is_file()
    assert (out_dir / "MemMap/include/Rte_MemMap.h").is_file()
    assert len(rep.generated_files) >= 10

    # Second run reports unchanged files cleanly
    rep2 = generate_platform_artifacts(project, out_dir, flat=False)
    assert rep2.generated_files == []
    assert len(rep2.unchanged_files) == len(rep.generated_files)


def test_module_memmap_h_clang_syntax_check(tmp_path):
    clang = shutil.which("clang")
    if not clang:
        pytest.skip("clang not installed")

    mm_text = render_module_memmap_h("BswM", compiler="LlvmHighTec")
    assert '# pragma clang section text = ".MSR_CODE"' in mm_text
    assert '# pragma clang section rodata = ".MSR_CONST"' in mm_text

    mm_path = tmp_path / "BswM_MemMap.h"
    mm_path.write_text(mm_text, encoding="utf-8")

    c_path = tmp_path / "bswm_memmap_check.c"
    c_path.write_text(
        '\n'.join([
            '#define BSWM_START_SEC_CONST_16',
            '#include "BswM_MemMap.h"',
            'static const unsigned short kVal = 42U;',
            '#define BSWM_STOP_SEC_CONST_16',
            '#include "BswM_MemMap.h"',
            '#define BSWM_START_SEC_CODE',
            '#include "BswM_MemMap.h"',
            'unsigned short get_val(void) { return kVal; }',
            '#define BSWM_STOP_SEC_CODE',
            '#include "BswM_MemMap.h"',
        ]),
        encoding="utf-8",
    )
    proc = subprocess.run(
        [
            clang,
            "--target=armv8r-none-eabi",
            "-fsyntax-only",
            "-Wall",
            "-Wextra",
            "-Werror",
            f"-I{tmp_path}",
            str(c_path),
        ],
        capture_output=True,
        text=True,
    )
    assert proc.returncode == 0, f"clang failed:\n{proc.stderr}"


def test_rte_companion_headers_and_audit_service(tmp_path):
    project, proj_dir, _mods = build_phase23_project(tmp_path)
    out_dir = tmp_path / "rte_out"
    rep = RteSchMGenerator(project, include_phase2_3=True).generate(out_dir, flat=False)
    assert rep.ok

    inc = out_dir / "Rte/include"
    assert (inc / "Rte_Compiler_Cfg.h").is_file()
    assert (inc / "Rte_Hook.h").is_file()
    assert (inc / "Components/MotorCtrl_MemMap.h").is_file()

    comp_cfg = (inc / "Rte_Compiler_Cfg.h").read_text(encoding="utf-8")
    assert "# define RTE_MOTORCTRL_APPL_VAR" in comp_cfg
    assert "# define MotorCtrl_CODE" in comp_cfg
    swc_mm = (inc / "Components/MotorCtrl_MemMap.h").read_text(encoding="utf-8")
    assert "MotorCtrl_START_SEC_VAR_NOINIT_UNSPECIFIED" in swc_mm
    assert "OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED" in swc_mm

    # Audit a project containing an unexpanded template tag and a reference header
    tpl_dir = proj_dir / "templates/Com"
    tpl_dir.mkdir(parents=True, exist_ok=True)
    (tpl_dir / "Com_Cfg.h").write_text(
        '#define COM_PRESENT 1\n/* [!"\'[!UNEXPANDED_TAG!]\'"!] */\n',
        encoding="utf-8",
    )
    ref_dir = tmp_path / "ref_gendata"
    ref_dir.mkdir()
    (ref_dir / "Com_Cfg.h").write_text("# define COM_PRESENT 1\n# define COM_OTHER 2\n", encoding="utf-8")

    # Save .dpa so audit_project_templates can load from path
    dpa_path = project.path
    ws = WorkspaceManager()
    ws.current_project = project
    ws.save_project()

    audit_rep = audit_project_templates(dpa_path, ref_gendata_dir=ref_dir, include_platform_gen=True)
    assert audit_rep.error_modules == 0
    assert audit_rep.total_unexpanded_files >= 1
    com_res = next(m for m in audit_rep.module_results if m.module_name == "Com")
    assert com_res.status == "OK"
    assert com_res.define_match_total == 1 and com_res.define_ref_total == 2
    assert "# Template Audit Report:" in audit_rep.to_markdown()
    assert isinstance(audit_rep.to_dict(), dict)

    # CLI test (--fail-on-error returns 1 because of unexpanded tag)
    json_out = tmp_path / "audit.json"
    rc = audit_cli_main(["--dpa", str(dpa_path), "--json", str(json_out), "--fail-on-error"])
    assert rc == 1
    assert json_out.is_file()


def test_real_startapplication1_p4_1_audit_and_parity_readonly(tmp_path):
    real_dpa = Path("/Users/qlwang/Desktop/test3/StartApplication1/StartApplication1.dpa")
    ref_gendata = Path("/Users/qlwang/Desktop/未命名文件夹/mcuapp/Applications/SipAddon/StartApplication/Appl/GenData")
    if not real_dpa.is_file() or not ref_gendata.is_dir():
        pytest.skip("External StartApplication1.dpa or StartApplication GenData fixture not available")

    rep = audit_project_templates(
        real_dpa,
        ref_gendata_dir=ref_gendata,
        include_platform_gen=True,
        include_rte_phase2_3=True,
        run_clang=False,
    )

    assert rep.total_loaded_modules == 28
    assert rep.ok_modules == 28
    assert rep.skipped_modules == 0
    assert rep.error_modules == 0
    assert rep.total_unexpanded_files == 0

    # CanTrcv must route through CanTrcv_Tle9255 and render CanTrcv_30_Tle9255_Cfg.h/.c
    trcv = next(m for m in rep.module_results if m.module_name == "CanTrcv")
    assert trcv.status == "OK"
    assert trcv.template_dir_name == "CanTrcv_Tle9255"
    assert trcv.generated_count >= 2

    # Platform + RTE companion files achieve full coverage for P4-1 targets
    by_file = {d.filename: d for d in rep.file_details}
    assert by_file["ComStack_Cfg.h"].status == "matched"
    assert by_file["Rte_Compiler_Cfg.h"].status == "matched"
    assert by_file["Rte_Hook.h"].status == "matched"
    assert by_file["McuFsmComponent_MemMap.h"].status == "matched"
    assert by_file["BswM_MemMap.h"].status == "matched"
    assert by_file["vBrsCfg.h"].status == "matched"
    assert by_file["vBrs_Lcfg.h"].status == "matched"
    assert by_file["vBrs_Lcfg.c"].status == "matched"
    assert by_file["vBrsCfg.h"].define_match == by_file["vBrsCfg.h"].define_total
    assert by_file["Det_Cfg.h"].define_match == by_file["Det_Cfg.h"].define_total
    assert by_file["Crc_Cfg.h"].define_match == by_file["Crc_Cfg.h"].define_total
    assert "Makefile.config.generated" in by_file

    # CLI run passes with exit 0 (--fail-on-error) on StartApplication1
    md_out = tmp_path / "sa1_audit.md"
    rc = audit_cli_main(["--dpa", str(real_dpa), "--ref-gendata", str(ref_gendata), "--md", str(md_out), "--fail-on-error"])
    assert rc == 0
    assert md_out.is_file()
