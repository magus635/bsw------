## Context

In AUTOSAR Classic / Vector MICROSAR projects, `Components/Rte/` ships no static `.c`/`.h` `Implementation/` and instead relies on a compiled synthesis engine (`DVCfgRteGen`) combining SWC, System, BSW InternalBehavior (`_ib_bswmd`), `Os`, and `Rte` ECUC models. Importing a `.dpa` project already archives all non-ECUC ARXML models under `system/` and populates `RteBswModuleInstance` / `BSW-IMPLEMENTATION` metadata.

## Goals / Non-Goals

- Goals:
  - Synthesize deterministic, compilable Phase 1 headers (`SchM_<ApiName>.h`, `SchM_<ApiName>_Type.h`, `Rte.h`, `Rte_Main.h`, `Rte_Cfg.h`, `Rte_Cbk.h`, and non-destructive `Rte_UserTypes.h` / `Rte_Type.h` stubs) from real project models.
  - Eliminate C preprocessor bare-identifier bugs from `Rte_Cfg.h` by matching Vector's minimal `#include "Std_Types.h"` header.
  - Follow `directories.gen_layout` (`per-module` -> `gen/Rte/include/`, `flat` -> `gen/include/`) and let project `templates/Rte/` overlays override matching generated files.
- Non-Goals:
  - Phase 2 SWC contract headers (`Components/Rte_<Swc>.h`, full `Rte_Type.h` type definitions) and Phase 3 runtime scheduling/communication (`Rte.c`, `Rte_SystemApplication_*.c`).
  - Changing EB Tresos template lookup semantics in `CodeGenerator`.

## Decisions

- **Separate `generator/rte/` pipeline instead of extending `CodeGenerator`**: Keeps EB template resolution clean (`code-generation` spec retains no built-in EB fallback content) and models multi-source AUTOSAR joins (`_ib_bswmd` + `Rte` + `Os` + `MemMap`) cleanly in Python.
- **Confirmed Option A (`Rte_Cfg.h`)**: Emit Vector-compatible minimal `Rte_Cfg.h` (`#if !defined (RTE_CFG_H)` + `# include "Std_Types.h"`), avoiding unconsumed or bare-identifier macros.
- **Confirmed Option A (`Rte_Type.h` & `Rte_UserTypes.h` stubs)**: Create minimal compilable header stubs only when missing on disk so Phase 1 headers compile standalone without clobbering user edits or future Phase 2 output.
- **Confirmed Option A (Output layout)**: Route all Phase 1 headers cleanly into the project's `Rte/include` (`per-module`) or `include` (`flat`) directory.

## Risks / Trade-offs

- Unloaded module references in `RteBswModuleInstance` (e.g., `CanNm` when disabled in `.dpa`) -> Skip unloaded module cleanly, record in `skipped_modules`, emit warning rather than guessing or crashing.
- Missing `OsResourceRef` / `OsSpinlockRef` for `OS_RESOURCE` / `OS_SPINLOCK` ExclusiveArea mechanisms -> Record explicit error in `RteGenerationReport.errors` and abort writing invalid macros.
