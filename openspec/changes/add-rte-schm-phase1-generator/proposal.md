## Why

The current `Rte` generation path only produces a static summary `Rte_Cfg.h` from an EB template, whose unguarded bare-identifier enum macros (e.g., `NONE`, `COMPATIBILITY_MODE`) evaluate silently to `0` in C `#if` preprocessor expressions and lack the `SchM_<Module>.h`, `SchM_<Module>_Type.h`, `Rte.h`, `Rte_Main.h`, and `Rte_Cbk.h` headers required to compile BSW modules imported from a Vector SIP.

## What Changes

- Add a model-driven Phase 1 RTE/SchM header generator package (`autosar_configurator/generator/rte/`) that synthesizes C headers directly from `Rte` ECUC, `Os` ECUC, `MemMap` ECUC, `system/**/*_ib_bswmd.arxml` InternalBehavior models, and `BSW-IMPLEMENTATION` package metadata.
- Generate `SchM_<ApiName>.h` and `SchM_<ApiName>_Type.h` for active loaded BSW module instances (supporting `VENDOR-API-INFIX` naming, `BSW-SCHEDULABLE-ENTITY` declarations, all 6 `RteExclusiveAreaImplMechanism` modes, 3-tier `MemMap` header resolution, and skipping unloaded modules with warnings).
- Generate Vector-compatible core RTE headers: `Rte.h`, `Rte_Main.h` (single/multi-core + `OsApplication` `Rte_InitMemory_*`), minimal `Rte_Cfg.h` (replacing bare enum macros), `Rte_Cbk.h`, and non-destructive `Rte_UserTypes.h` / `Rte_Type.h` compile stubs.
- Integrate Phase 1 generation with `GenerationController` while preserving project overlay (`templates/Rte/`) precedence and respecting `per-module` / `flat` output layouts without modifying EB template resolution rules for other modules.

## Impact

- Affected specs: `rte-schm-generation` (new capability, leaving `code-generation` no-built-in-template semantics intact)
- Affected code:
  - `autosar_configurator/generator/rte/` (`__init__.py`, `model.py`, `ib_parser.py`, `extractor.py`, `renderers.py`, `generator.py`)
  - `autosar_configurator/ui/controllers/generation_controller.py`
  - `template_packs/davinci/Rte/include/Rte_Cfg.h`
  - `tests/generator/test_rte_schm_generator.py`, `tests/core/test_sip_multi_module_def.py`, `tests/ui/test_generation_controller.py`
