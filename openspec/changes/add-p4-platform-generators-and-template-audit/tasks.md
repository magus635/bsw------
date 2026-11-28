## 1. OpenSpec
- [x] 1.1 Create and validate `openspec/changes/add-p4-platform-generators-and-template-audit/` (`openspec validate add-p4-platform-generators-and-template-audit --strict`)

## 2. RTE Companion Headers & Per-SWC MemMap
- [x] 2.1 Implement `render_rte_compiler_cfg_h()`, `render_rte_hook_h()`, and `render_swc_memmap_h()` in `autosar_configurator/generator/rte/renderers_phase23.py`
- [x] 2.2 Wire companion headers and `Components/<Swc>_MemMap.h` into `RteSchMGenerator._build_outputs()` (`generator.py`) and export them in `rte/__init__.py`

## 3. Platform Artifact Generator (`autosar_configurator/generator/platform_gen.py`)
- [x] 3.1 Implement `render_comstack_cfg_h()`, `render_module_memmap_h()`, `render_vbrs_files()` (`vBrsCfg.h`, `vBrs_Lcfg.h`, `vBrs_Lcfg.c`, `Makefile.config.generated`), and `generate_platform_artifacts()`

## 4. Template Audit Service & CLI
- [x] 4.1 Implement `audit_project_templates()` with variant routing (`package_dir_name`), unexpanded EB tag scanning, `#define`/symbol parity, and optional `clang -fsyntax-only` checks in `autosar_configurator/generator/template_audit.py`
- [x] 4.2 Export `platform_gen` / `template_audit` APIs in `generator/__init__.py` and add CLI script `tools/audit_templates.py`

## 5. Verification
- [x] 5.1 Create `tests/generator/test_p4_platform_and_audit.py` covering synthetic unit checks, `clang` MemMap syntax verification, and read-only `StartApplication1.dpa` vs `StartApplication/Appl/GenData` parity
- [x] 5.2 Run pytest suite & `openspec validate add-p4-platform-generators-and-template-audit --strict` and mark all tasks complete
