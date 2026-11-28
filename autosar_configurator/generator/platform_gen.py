"""Model-driven platform generators for ComStack_Cfg.h, <Mod>_MemMap.h, and vBRS / LlvmHighTec."""

from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple


@dataclass
class PlatformGenReport:
    """Summary of generated, unchanged, or skipped platform files."""

    generated_files: List[Path] = field(default_factory=list)
    unchanged_files: List[Path] = field(default_factory=list)
    skipped: List[str] = field(default_factory=list)
    warnings: List[str] = field(default_factory=list)


def _ar_leaf(path: Optional[str]) -> str:
    if not path:
        return ""
    return str(path).strip().rstrip("/").rsplit("/", 1)[-1]


def _iter_by_def(cfg: Any, def_leaf: str) -> List[Any]:
    if cfg is None:
        return []
    out: List[Any] = []

    def _walk(c: Any) -> None:
        if _ar_leaf(getattr(c, "definition_ref", None)) == def_leaf:
            out.append(c)
        for sub in getattr(c, "sub_containers", []) or []:
            _walk(sub)

    for top in getattr(cfg, "containers", []) or []:
        _walk(top)
    return out


def _first_by_def(cfg: Any, def_leaf: str) -> Optional[Any]:
    hits = _iter_by_def(cfg, def_leaf)
    return hits[0] if hits else None


def _param_val(c: Any, name: str, default: Any = None) -> Any:
    if c is None:
        return default
    pv = getattr(c, "parameter_values", {}).get(name)
    return default if pv is None or pv.value is None else pv.value


def _param_bool(c: Any, name: str, default: bool = False) -> bool:
    raw = _param_val(c, name, None)
    if raw is None:
        return default
    if isinstance(raw, bool):
        return raw
    if isinstance(raw, (int, float)):
        return bool(raw)
    text = str(raw).strip().lower()
    if text in ("true", "1", "yes", "on"):
        return True
    if text in ("false", "0", "no", "off"):
        return False
    return default


def _param_int(c: Any, name: str, default: Optional[int] = None) -> Optional[int]:
    raw = _param_val(c, name, None)
    if raw is None or isinstance(raw, bool):
        return default
    try:
        return int(str(raw).strip(), 0)
    except ValueError:
        try:
            return int(float(str(raw).strip()))
        except ValueError:
            return default


def _ref_leaf(c: Any, name: str) -> str:
    if c is None:
        return ""
    rv = getattr(c, "reference_values", {}).get(name)
    if rv is not None and getattr(rv, "value_ref", None):
        return _ar_leaf(rv.value_ref)
    for r in getattr(c, "multi_reference_values", {}).get(name, []) or []:
        if getattr(r, "value_ref", None):
            return _ar_leaf(r.value_ref)
    return ""


def _to_mhz(freq_raw: Optional[int], default_mhz: int) -> int:
    if freq_raw is None or freq_raw <= 0:
        return default_mhz
    if freq_raw >= 1_000_000:
        return freq_raw // 1_000_000
    return freq_raw


def _cfg_for(project: Any, module_name: str) -> Optional[Any]:
    mgrs = getattr(project, "module_managers", {}) or {}
    mgr = mgrs.get(module_name)
    return getattr(mgr, "configuration", None) if mgr is not None else None


# ----------------------------------------------------------------------
# ComStack_Cfg.h (from EcuC/EcucPduCollection)
# ----------------------------------------------------------------------

_INT_ENUM_MAP = {
    "UINT8": "uint8",
    "UINT16": "uint16",
    "UINT32": "uint32",
}


def render_comstack_cfg_h(project: Any) -> Optional[str]:
    """Render ``ComStack_Cfg.h`` from ``EcuC/EcucPduCollection``."""
    ecuc_cfg = _cfg_for(project, "EcuC")
    if ecuc_cfg is None:
        return None
    pdu_coll = _first_by_def(ecuc_cfg, "EcucPduCollection")
    id_enum = str(_param_val(pdu_coll, "PduIdTypeEnum", "UINT8") or "UINT8").strip().upper()
    len_enum = str(_param_val(pdu_coll, "PduLengthTypeEnum", "UINT16") or "UINT16").strip().upper()
    id_c = _INT_ENUM_MAP.get(id_enum, "uint8")
    len_c = _INT_ENUM_MAP.get(len_enum, "uint16")

    lines = [
        "/**********************************************************************************************************************",
        " *  FILE DESCRIPTION",
        " *  -------------------------------------------------------------------------------------------------------------------",
        " *              File: ComStack_Cfg.h",
        " *            Module: EcuC",
        " *         Generator: AUTOSAR BSW Configurator (Platform Generator)",
        " *********************************************************************************************************************/",
        "#if !defined (COMSTACK_CFG_H)",
        "#define COMSTACK_CFG_H",
        "",
        '#include "Std_Types.h"',
        "",
        f"typedef {id_c} PduIdType;   /**< PduIdTypeEnum = {id_enum} */",
        f"typedef {len_c} PduLengthType;   /**< PduLengthTypeEnum = {len_enum} */",
        "",
        "#endif  /* COMSTACK_CFG_H */",
        "",
    ]
    return "\n".join(lines)


# ----------------------------------------------------------------------
# Batch <Mod>_MemMap.h (with LlvmHighTec #pragma clang section support)
# ----------------------------------------------------------------------

_MEMMAP_SECTIONS: Tuple[Tuple[str, str, str], ...] = (
    ("CODE", "text", ".MSR_CODE"),
    ("APPL_CODE", "text", ".MSR_CODE"),
    ("CONST_8", "rodata", ".MSR_CONST"),
    ("CONST_16", "rodata", ".MSR_CONST"),
    ("CONST_32", "rodata", ".MSR_CONST"),
    ("CONST_BOOLEAN", "rodata", ".MSR_CONST"),
    ("CONST_UNSPECIFIED", "rodata", ".MSR_CONST"),
    ("PBCFG", "rodata", ".MSR_PBCFG_CONST"),
    ("VAR_NOINIT_8", "bss", ".MSR_VAR_NOINIT"),
    ("VAR_NOINIT_16", "bss", ".MSR_VAR_NOINIT"),
    ("VAR_NOINIT_32", "bss", ".MSR_VAR_NOINIT"),
    ("VAR_NOINIT_BOOLEAN", "bss", ".MSR_VAR_NOINIT"),
    ("VAR_NOINIT_UNSPECIFIED", "bss", ".MSR_VAR_NOINIT"),
    ("VAR_INIT_8", "data", ".MSR_VAR_INIT"),
    ("VAR_INIT_16", "data", ".MSR_VAR_INIT"),
    ("VAR_INIT_32", "data", ".MSR_VAR_INIT"),
    ("VAR_INIT_BOOLEAN", "data", ".MSR_VAR_INIT"),
    ("VAR_INIT_UNSPECIFIED", "data", ".MSR_VAR_INIT"),
    ("VAR_ZERO_INIT_8", "bss", ".MSR_VAR_ZERO_INIT"),
    ("VAR_ZERO_INIT_16", "bss", ".MSR_VAR_ZERO_INIT"),
    ("VAR_ZERO_INIT_32", "bss", ".MSR_VAR_ZERO_INIT"),
    ("VAR_ZERO_INIT_BOOLEAN", "bss", ".MSR_VAR_ZERO_INIT"),
    ("VAR_ZERO_INIT_UNSPECIFIED", "bss", ".MSR_VAR_ZERO_INIT"),
    ("APPL_DATA", "data", ".MSR_VAR_INIT"),
)


def render_module_memmap_h(module_name: str, *, compiler: str = "LlvmHighTec") -> str:
    """Render ``<Mod>_MemMap.h`` compatible with MICROSAR section-open guards and LlvmHighTec."""
    mod_upper = "".join(ch if ch.isalnum() else "_" for ch in module_name).upper()
    use_clang_pragma = any(k in (compiler or "").lower() for k in ("llvm", "clang", "hightec"))

    lines: List[str] = [
        "/* AUTOSAR BSW Configurator generated Memory Mapping header (no include guard by design) */",
        "#ifndef MICROSAR_DISABLE_MEMMAP",
        "# define MEMMAP_ERROR",
    ]
    for idx, (sec, kind, elf_sec) in enumerate(_MEMMAP_SECTIONS):
        branch = "#if" if idx == 0 else "#elif"
        start_sym = f"{mod_upper}_START_SEC_{sec}"
        stop_sym = f"{mod_upper}_STOP_SEC_{sec}"
        open_sym = f"{mod_upper}_{sec}_OPEN"

        lines.extend([
            f"{branch} defined {start_sym}",
            "# ifdef MEMMAP_SECTION_OPEN",
            f"#  error Using {start_sym} is not possible as a memory section has already been opened.",
            "# endif",
            "# define MEMMAP_SECTION_OPEN",
            f"# define {open_sym}",
        ])
        if use_clang_pragma and kind in ("rodata", "data", "bss"):
            lines.append(f'# pragma clang section {kind} = "{elf_sec}"')
        elif use_clang_pragma and kind == "text":
            lines.append(f'# pragma clang section text = "{elf_sec}"')
        lines.extend([
            f"# undef {start_sym}",
            "# undef MEMMAP_ERROR",
            f"#elif defined {stop_sym}",
            "# ifndef MEMMAP_SECTION_OPEN",
            f"#  error Using {stop_sym} is not possible as no memory section has been opened.",
            "# endif",
            "# undef MEMMAP_SECTION_OPEN",
            f"# ifndef {open_sym}",
            f"#  error Using {stop_sym} is not possible as the corresponding memory section has not been opened.",
            "# endif",
            f"# undef {open_sym}",
        ])
        if use_clang_pragma and kind in ("text", "rodata", "data", "bss"):
            lines.append(f'# pragma clang section {kind} = ""')
        lines.extend([
            f"# undef {stop_sym}",
            "# undef MEMMAP_ERROR",
        ])

    lines.extend([
        "#endif /* section match */",
        "#ifdef MEMMAP_ERROR",
        f'# error "Error in {module_name}_MemMap.h: MemMap section not mapped"',
        "#endif",
        "#endif /* MICROSAR_DISABLE_MEMMAP */",
        "",
    ])
    return "\n".join(lines)


# ----------------------------------------------------------------------
# vBRS Headers & Makefile.config.generated (from vBRS + vBaseEnv + Os)
# ----------------------------------------------------------------------


def _extract_vbrs_context(project: Any) -> Optional[Dict[str, Any]]:
    vbrs_cfg = _cfg_for(project, "vBRS")
    if vbrs_cfg is None:
        return None
    vbrs_gen = _first_by_def(vbrs_cfg, "vBRSGeneral")
    hw_cfg = _first_by_def(vbrs_cfg, "vBRSHwConfig")
    mem_init = _first_by_def(vbrs_cfg, "vBRSMemoryInit")

    vbase_cfg = _cfg_for(project, "vBaseEnv")
    vbase_gen = _first_by_def(vbase_cfg, "vBaseEnvGeneral")
    sel_deriv_name = _ref_leaf(vbase_gen, "vBaseEnvTestedDerivativeRef")
    deriv_c = None
    for d in _iter_by_def(vbase_cfg, "vBaseEnvDerivativeInformation"):
        if d.short_name == sel_deriv_name or _param_val(d, "vBaseEnvTestedDerivative") == sel_deriv_name:
            deriv_c = d
            break
    if deriv_c is None:
        deriv_c = _first_by_def(vbase_cfg, "vBaseEnvDerivativeInformation")

    os_cfg = _cfg_for(project, "Os")
    os_cores = _iter_by_def(os_cfg, "OsCore")
    osos = _first_by_def(os_cfg, "OsOS")

    derivative = str(_param_val(deriv_c, "vBaseEnvTestedDerivative", sel_deriv_name or "Tongxin_THA6206"))
    cpu_core = str(_param_val(deriv_c, "vBaseEnvCpuCore", "CORTEX_R52")).strip()
    cpu_max_mhz = _to_mhz(_param_int(deriv_c, "vBaseEnvCpuMaxFrequency"), 400)

    core_amount = len(os_cores) if os_cores else (_param_int(osos, "OsNumberOfCores") or _param_int(deriv_c, "vBaseEnvCpuCoreAmount") or 1)
    used_cores: List[int] = []
    for idx in range(8):
        if os_cores:
            has_idx = any(
                c.short_name.endswith(str(idx)) or _ref_leaf(c, "OsCoreEcucCoreRef").endswith(str(idx))
                for c in os_cores
            )
            used_cores.append(1 if has_idx else 0)
        else:
            used_cores.append(1 if idx < core_amount else 0)

    osc_mhz = _to_mhz(_param_int(hw_cfg, "vBRSOscClock"), 25)
    tb_mhz = _to_mhz(_param_int(hw_cfg, "vBRSTimebaseClock"), cpu_max_mhz)
    periph_mhz = _to_mhz(_param_int(hw_cfg, "vBRSPeriphClock"), osc_mhz)
    instr_set = str(_param_val(hw_cfg, "vBRSCompilerInstructionSet", "ARM")).strip().upper()
    fpu_used = _param_bool(hw_cfg, "vBRSCompilerEnableFPU", True)
    if os_cfg is not None and not _param_bool(hw_cfg, "vBRSCompilerEnableFPU", True):
        # Respect explicit False unless OS task enables FPU
        if any(_param_bool(t, "OsTaskUsesFpu", False) for t in _iter_by_def(os_cfg, "OsTask")):
            fpu_used = True

    multicore = _param_bool(vbrs_gen, "vBRSEnableMultiCoreSupport", core_amount > 1)
    first_inst = _param_bool(vbrs_gen, "vBRSFirstInstance", True)
    exec_inst = str(_param_val(vbrs_gen, "vBRSExecutionInstance", "Application")).strip()
    fbl_exc_ram = _param_bool(vbrs_gen, "vBRSFblSupportExceptionTableInRam", False)
    hyp_guest = _param_bool(vbrs_gen, "vBRSHypervisorGuest", False)

    return {
        "hw_version": 404,
        "osc_mhz": osc_mhz,
        "tb_mhz": tb_mhz,
        "periph_mhz": periph_mhz,
        "derivative": derivative,
        "cpu_core": cpu_core,
        "cpu_max_mhz": cpu_max_mhz,
        "core_amount": max(1, core_amount),
        "used_cores": used_cores,
        "instr_set": instr_set,
        "fpu_used": fpu_used,
        "multicore": multicore,
        "first_inst": first_inst,
        "exec_inst": exec_inst,
        "fbl_exc_ram": fbl_exc_ram,
        "hyp_guest": hyp_guest,
        "pat_blocks": _param_int(mem_init, "vBRSInitPatternBlocks", 0) or 0,
        "pat_hr_blocks": _param_int(mem_init, "vBRSInitPatternHardResetBlocks", 0) or 0,
        "pat_areas": _param_int(mem_init, "vBRSInitPatternAreas", 0) or 0,
        "pat_hr_areas": _param_int(mem_init, "vBRSInitPatternHardResetAreas", 0) or 0,
        "init_64bit": _param_bool(mem_init, "vBRSInitEnable64BitInitPattern", False),
        "disable_mem_init": _param_bool(mem_init, "vBRSDisableMemoryInitGlobally", False),
        "support_leds": _param_bool(vbrs_gen, "vBRSEnableSupportLEDs", False),
        "testsuite": False,
        "fbl_support": "fbl" in exec_inst.lower(),
        "hsm_support": "hsm" in exec_inst.lower(),
        "hypervisor_support": False,
    }


def render_vbrs_files(project: Any) -> Dict[str, str]:
    """Render ``vBrsCfg.h``, ``vBrs_Lcfg.h``, ``vBrs_Lcfg.c``, and ``Makefile.config.generated``."""
    ctx = _extract_vbrs_context(project)
    if ctx is None:
        return {}

    n_cores = ctx["core_amount"]
    # 1. vBrsCfg.h
    cfg_h: List[str] = [
        "#ifndef _VBRSCFG_H_",
        "#define _VBRSCFG_H_",
        "",
        "#if !defined (BRS_INCLUDED_BY_ASM_FILE)",
        '# include "Std_Types.h"',
        "#endif",
        "",
        "#define BASIC_RUNTIME_SYSTEM_TYPE_MSR4",
        f"#define BRS_GENERATED_HW_CONFIG_VERSION {ctx['hw_version']}U",
        "",
    ]
    if ctx["first_inst"]:
        cfg_h.append("#define BRS_FIRST_EXECUTION_INSTANCE")
    if ctx["hyp_guest"]:
        cfg_h.append("#define BRS_HYPERVISOR_GUEST_EXECUTION_INSTANCE")
    if ctx["multicore"]:
        cfg_h.append("#define BRS_ENABLE_OS_MULTICORESUPPORT")
    if ctx["support_leds"]:
        cfg_h.append("#define BRS_ENABLE_SUPPORT_LEDS")
    cfg_h.extend([
        f"#define BRS_OSC_CLK {ctx['osc_mhz']}",
        f"#define BRS_TIMEBASE_CLOCK {ctx['tb_mhz']}",
        f"#define BRS_PERIPH_CLOCK {ctx['periph_mhz']}",
        f"#define BRS_DERIVATIVE_{ctx['derivative']}",
        f"#define BRS_CPU_CORE_{ctx['cpu_core']}",
        f"#define BRS_CPU_MAX_FREQUENCY {ctx['cpu_max_mhz']}",
        f"#define BRS_CPU_CORE_AMOUNT {n_cores}",
        f"#define BRS_INSTRUCTION_SET_{ctx['instr_set']}",
    ])
    if ctx["fpu_used"]:
        cfg_h.append("#define BRS_FPU_USED")
    if ctx["init_64bit"]:
        cfg_h.append("#define BRS_ENABLE_64BIT_INIT_PATTERN")
    if ctx["disable_mem_init"]:
        cfg_h.append("#define BRS_DISABLE_MEMORY_INIT_GLOBALLY")
    cfg_h.extend([
        f"#define BRS_INIT_PATTERN_BLOCKS (0x{ctx['pat_blocks']:X}UL)",
        f"#define BRS_INIT_PATTERN_HARDRESET_BLOCKS (0x{ctx['pat_hr_blocks']:X}UL)",
        f"#define BRS_INIT_PATTERN_AREAS (0x{ctx['pat_areas']:X}UL)",
        f"#define BRS_INIT_PATTERN_HARDRESET_AREAS (0x{ctx['pat_hr_areas']:X}UL)",
        "",
        "#endif /*_VBRSCFG_H_*/",
        "",
    ])

    # 2. vBrs_Lcfg.h
    lcfg_h = "\n".join([
        "#ifndef _VBRSLCFG_H_",
        "#define _VBRSLCFG_H_",
        "",
        '#include "Std_Types.h"',
        '#include "BrsMain_Types.h"',
        '#include "BrsHw.h"',
        "",
        "#if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)",
        f"extern const brsMain_CoreType BrsMain_CoreConfig[{n_cores}u];",
        "extern const uint32 BrsMain_CoreConfig_Size;",
        "#endif /*BRSHW_SOURCECODE_TEMPLATE_VERSION>=0x0103u*/",
        "",
        "#endif /* _VBRSLCFG_H_ */",
        "",
    ])

    # 3. vBrs_Lcfg.c
    lcfg_c: List[str] = [
        "#define VBRS_LCFG_SOURCE",
        "",
        '#include "vBrs_Lcfg.h"',
        "",
        "#if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)",
    ]
    for cid in range(n_cores):
        lcfg_c.extend([
            f"extern Brs_AddressOfConstType BRSHW_DEFINE_STARTUP_STACK({cid});",
            f"extern Brs_AddressOfConstType BRSHW_DEFINE_EXCVEC({cid});",
            f"extern Brs_AddressOfConstType BRSHW_DEFINE_INTVEC({cid});",
        ])
    lcfg_c.extend([
        f"const uint32 BrsMain_CoreConfig_Size = {n_cores};",
        "",
        f"const brsMain_CoreType BrsMain_CoreConfig[{n_cores}u] =",
        "{",
    ])
    for cid in range(n_cores):
        comma = "," if cid + 1 < n_cores else ""
        lcfg_c.extend([
            "  {",
            f"    /* PhysicalCoreId */ {cid}u,",
            f"    /* StartupStackEndLabel */ (Brs_AddressOfConstType)BRSHW_SYMBOL_STARTUP_STACK({cid}),",
            f"    /* StartupStackSize */ 1024u,",
            f"    /* ExcVecLabel */ (Brs_AddressOfConstType)BRSHW_SYMBOL_EXCVEC({cid}),",
            f"    /* IntVecLabel */ (Brs_AddressOfConstType)BRSHW_SYMBOL_INTVEC({cid})",
            f"  }}{comma}",
        ])
    lcfg_c.extend([
        "};",
        "#endif /*BRSHW_SOURCECODE_TEMPLATE_VERSION>=0x0103u*/",
        "",
    ])

    # 4. Makefile.config.generated
    mk: List[str] = [
        f"BRS_GENERATED_HW_CONFIG_VERSION = {ctx['hw_version']}",
        f"MAIN_OSC_CLK = {ctx['osc_mhz']}",
        f"TIMEBASE_CLOCK = {ctx['tb_mhz']}",
        f"PERIPH_CLOCK = {ctx['periph_mhz']}",
        f"DERIVATIVE = {ctx['derivative']}",
        f"BRS_CPU_CORE_AMOUNT = {n_cores}",
    ]
    for cid in range(8):
        mk.append(f"BRS_CPU_CORE_{cid}_USED = {ctx['used_cores'][cid]}")
    mk.extend([
        f"CPU_CORE = {ctx['cpu_core']}",
        f"INSTRUCTION_SET = {ctx['instr_set']}",
        f"FPU_USED = {1 if ctx['fpu_used'] else 0}",
        r"APP_SOURCE_LST += $(GENDATA_DIR)\vBrs_Lcfg.c",
        f"BRS_ENABLE_HSM_SUPPORT = {1 if ctx['hsm_support'] else 0}",
        f"BRS_ENABLE_FBL_SUPPORT = {1 if ctx['fbl_support'] else 0}",
        f"BRS_ENABLE_HYPERVISOR_SUPPORT = {1 if ctx['hypervisor_support'] else 0}",
        f"BRS_FBL_EXCEPTIONTABLE_IN_RAM = {1 if ctx['fbl_exc_ram'] else 0}",
        f"BRS_FIRST_EXECUTION_INSTANCE = {1 if ctx['first_inst'] else 0}",
        f"BRS_HYPERVISOR_GUEST_EXECUTION_INSTANCE = {1 if ctx['hyp_guest'] else 0}",
        "",
    ])

    return {
        "vBrsCfg.h": "\n".join(cfg_h),
        "vBrs_Lcfg.h": lcfg_h,
        "vBrs_Lcfg.c": "\n".join(lcfg_c),
        "Makefile.config.generated": "\n".join(mk),
    }


def _write_if_changed(dst: Path, content: str, report: PlatformGenReport, *, force: bool = False) -> None:
    dst.parent.mkdir(parents=True, exist_ok=True)
    if not force and dst.is_file():
        try:
            if dst.read_text(encoding="utf-8") == content:
                report.unchanged_files.append(dst)
                return
        except OSError:
            pass
    dst.write_text(content, encoding="utf-8")
    report.generated_files.append(dst)


def generate_platform_artifacts(
    project: Any,
    output_dir: Path,
    *,
    flat: bool = False,
    include_memmap: bool = True,
    include_comstack: bool = True,
    include_vbrs: bool = True,
    compiler: str = "LlvmHighTec",
    force: bool = False,
) -> PlatformGenReport:
    """Write ``ComStack_Cfg.h``, batch ``<Mod>_MemMap.h``, and ``vBRS`` outputs cleanly."""
    report = PlatformGenReport()
    out_root = Path(output_dir)

    def _inc(mod_folder: str) -> Path:
        return out_root if flat else (out_root / mod_folder / "include")

    def _src(mod_folder: str) -> Path:
        return out_root if flat else (out_root / mod_folder / "src")

    if include_comstack:
        cs = render_comstack_cfg_h(project)
        if cs is not None:
            _write_if_changed(_inc("EcuC") / "ComStack_Cfg.h", cs, report, force=force)
        else:
            report.skipped.append("ComStack_Cfg.h (EcuC not loaded)")

    if include_memmap:
        mgrs = getattr(project, "module_managers", {}) or {}
        memmap_mods = sorted(set(mgrs.keys()) | ({"Rte"} if mgrs else set()))
        for mod_name in memmap_mods:
            content = render_module_memmap_h(mod_name, compiler=compiler)
            _write_if_changed(_inc("MemMap") / f"{mod_name}_MemMap.h", content, report, force=force)

    if include_vbrs:
        vbrs_map = render_vbrs_files(project)
        if not vbrs_map:
            report.skipped.append("vBRS (vBRS not loaded)")
        else:
            for fname, content in vbrs_map.items():
                if fname.endswith(".c"):
                    dst = _src("vBRS") / fname
                elif fname.endswith(".h"):
                    dst = _inc("vBRS") / fname
                else:
                    dst = out_root / fname
                _write_if_changed(dst, content, report, force=force)

    return report
