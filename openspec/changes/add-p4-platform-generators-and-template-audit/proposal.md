# Change: Add P4-1 Platform Generators (vBRS / ComStack / Batch MemMap / RTE Companions) and Template Audit Engine

## Why

Empirical dry-run auditing of `StartApplication1.dpa` against real `StartApplication/Appl/GenData` (434 files) revealed four immediate gaps solvable without guessing or modifying upstream templates:
1. Variant-scoped modules such as `CanTrcv` (`CanTrcv_Tle9255`) are skipped unless callers pass `package_dir_name` into `CodeGenerator`.
2. Self-authored RTE Phase 2/3 code generation lacks companion headers (`Rte_Compiler_Cfg.h`, `Rte_Hook.h`, `Components/<Swc>_MemMap.h`).
3. Platform infrastructure files needed by MICROSAR builds (`ComStack_Cfg.h`, `<Mod>_MemMap.h` with `LlvmHighTec` clang pragmas, `vBrsCfg.h`, `vBrs_Lcfg.h/.c`, and `Makefile.config.generated`) are missing or misaligned.
4. There is no reusable automated audit service/CLI to quantify per-module dry-run coverage, unexpanded EB tags, `#define`/`CONST` parity against reference `GenData`, and `clang -fsyntax-only` compilation health.

## What Changes

- **RTE Companion Headers (`autosar_configurator/generator/rte/`)**:
  - Add `render_rte_compiler_cfg_h()`, `render_rte_hook_h()`, and `render_swc_memmap_h()` in `renderers_phase23.py` and emit `Rte_Compiler_Cfg.h`, `Rte_Hook.h`, and `Components/<Swc>_MemMap.h` inside `RteSchMGenerator` when `include_phase2_3=True`.
- **Platform Artifact Generator (`autosar_configurator/generator/platform_gen.py`)**:
  - Implement `render_comstack_cfg_h()`, `render_module_memmap_h()` (`LlvmHighTec` `#pragma clang section` support), `render_vbrs_files()` (`vBrsCfg.h`, `vBrs_Lcfg.h`, `vBrs_Lcfg.c`, `Makefile.config.generated`), and `generate_platform_artifacts()`.
- **Template Quality & Parity Audit Engine (`autosar_configurator/generator/template_audit.py`, `tools/audit_templates.py`)**:
  - Implement `audit_project_templates()` performing non-destructive `.dpa` dry-run generation (respecting `project_paths.package_dir_name`), unexpanded EB tag scanning (`[!`/`!]`), reference `GenData` file/`#define`/`CONST` parity measurement, optional `clang -fsyntax-only` checks, and Markdown/JSON reporting CLI.

## Impact

- Affected specs: `platform-generators-and-audit` (new capability)
- Affected code:
  - `autosar_configurator/generator/rte/{renderers_phase23.py,generator.py,__init__.py}`
  - `autosar_configurator/generator/{platform_gen.py,template_audit.py,__init__.py}`
  - `tools/audit_templates.py`
  - `tests/generator/test_p4_platform_and_audit.py`
