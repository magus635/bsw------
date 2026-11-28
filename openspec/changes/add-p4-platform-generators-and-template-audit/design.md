# Design: P4-1 Platform Generators & Template Audit Engine

## Context

`StartApplication1.dpa` stores Format 8 variant metadata via `project_paths.package_dir_name(project, module)` (for example `CanTrcv -> CanTrcv_Tle9255`), while `StartApplication/Appl/` compiles under `LlvmHighTec` using MICROSAR headers (`ComStack_Cfg.h`, `Rte_Compiler_Cfg.h`, `Rte_Hook.h`, `<Mod>_MemMap.h`, `Components/<Swc>_MemMap.h`, `vBrsCfg.h`, `vBrs_Lcfg.h/.c`, and `Makefile.config.generated`).

## Goals / Non-Goals

- **Goals**:
  - Generate companion RTE headers and per-SWC MemMap wrappers whenever `include_phase2_3=True`.
  - Generate deterministic, write-if-changed platform files (`ComStack_Cfg.h`, `<Mod>_MemMap.h`, `vBrsCfg.h`, `vBrs_Lcfg.h/.c`, `Makefile.config.generated`) cleanly from `EcuC`, `vBRS`, `vBaseEnv`, and `Os` ECUC configurations without touching external read-only directories.
  - Provide `audit_project_templates()` + CLI to measure real generation coverage (fixing `CanTrcv_Tle9255` lookup via `package_dir_name`), spaced `# define` parity (`^\s*#\s*define\s+`), and optional `clang -fsyntax-only` results.
- **Non-Goals**:
  - Wiring full MICROSAR BSW ComStackLib (`Com`/`PduR`/`CanIf`/`Dcm`) EB templates (deferred to P4-2).
  - Full `Os` 96-file kernel generation or full ELF linking in this change.

## Decisions

1. **Non-breaking stub vs output choice for RTE companions**: Place `Rte_Compiler_Cfg.h`, `Rte_Hook.h`, and `Components/<Swc>_MemMap.h` inside `RteSchMGenerator._build_outputs(..., include_phase2_3=True)` when SWCs exist (while `Rte_Compiler_Cfg.h` and `Rte_Hook.h` emit unconditionally whenever `include_phase2_3=True`). Legacy Phase-1 callers setting `include_phase2_3=False` remain 100% untouched.
2. **Variant routing in audit service**: Always pass `package_dir_name=project_paths.package_dir_name(proj, mod_name)` and `project_root=project_paths.project_root(proj)` into `CodeGenerator(...)` just as `generation_controller.py` does, preventing false skips on `CanTrcv` (`CanTrcv_Tle9255`).
3. **Microsar spaced preprocessor matching**: Vector generators emit indented `# define MACRO`; `template_audit.py` matches `^\s*#\s*define\s+([A-Za-z0-9_]+)` so parity counts are accurate.
4. **`LlvmHighTec` MemMap pragmas**: `render_module_memmap_h()` emits `# pragma clang section text/rodata/data/bss` when `compiler` targets LLVM/Clang/HighTec, paired with nested-section guards (`MEMMAP_SECTION_OPEN` / `<MOD>_<SEC>_OPEN` / `MEMMAP_ERROR`).
5. **Exact `vBrs` + `vBaseEnv` clock unit handling**: `vBRSHwConfig` stores frequencies in Hz (`25000000`, `400000000`) whereas `vBrsCfg.h` and `Makefile.config.generated` use MHz integers (`25`, `400`); values `>= 1_000_000` convert via `// 1_000_000`.
