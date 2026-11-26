## Context

The workspace already exposes a headless Phase 1 RTE/SchM generator (`autosar_configurator/generator/rte/`) and a workbench dialog precedent (`autosar_configurator/ui/dialogs/memory_map_workbench.py`). Editing RTE/SchM requires joining multiple sources: `Rte` ECUC (`RteBswModuleInstance`, `RteBswExclusiveAreaImpl`, `RteBswEventToTaskMapping`, `RteSwComponentInstance`, `RteGeneration`, `RteBswGeneral`), loaded `Os` ECUC (`OsTask`, `OsResource`, `OsSpinlock`), `MemMap` ECUC, module `module.json` implementation metadata, and `system/**/*_ib_bswmd.arxml` InternalBehavior files.

## Goals / Non-Goals

- Goals:
  - Keep all ECUC/IB join logic and write-back mutations in a Qt-free service (`RteWorkbenchService`) so both unit tests and Qt UI share a single source of truth.
  - Ensure every UI action mutates `Rte` ECUC containers cleanly (`definition_ref`, `dest_type`, `value_ref_dest`, registry sync, `is_modified = True`) so ARXML save/reload round-trips without losing AUTOSAR foreign reference `DEST` attributes.
  - Provide live non-destructive header preview and standalone RTE/SchM generation (respecting `directories.gen_layout` and `templates/Rte/` overlays) in Tab 4.
  - Show SWC `RteSwComponentInstance/RteEventToTaskMapping` rows alongside BSW mappings in the `OsTask` order tree (marked read-only so users see true task execution positions without corrupting SWC mappings).
- Non-Goals:
  - Phase 2 SWC contract generation (`Rte_<Swc>.h`) or Phase 3 `Rte.c` generation.
  - Editing `RteSwComponentInstance` / SWC Data Mapping inside this Phase 1 workbench (left read-only in Tab 3 for visibility).
  - Modifying user files under `/Users/qlwang/Desktop/test3/`.

## Decisions

- **Two-module UI split (`rte_schm_tabs.py` + `rte_schm_workbench.py`) + pure-Python service (`workbench_service.py`)**: Keeps each file concise, modular, and easy to test in headless CI (`QT_QPA_PLATFORM=offscreen`) as well as pure-Python unit tests.
- **Immediate in-memory write-back to `Rte` ECUC**: Matches existing panel/wizard conventions (`config_changed` enables `Save Project` and refreshes main tree/panel) rather than inventing a parallel sidecar JSON format; users persist changes cleanly via `Save Project`.
- **Non-destructive `RteSchMGenerator.preview()`**: Reuses `RteModelExtractor.extract()` and `_build_outputs()` and inspects destination/overlay paths read-only so Tab 4 stays responsive as flags or ExclusiveAreas change without touching `gen/` until the user clicks generate.
- **Standalone generation shares overlay/layout semantics with `GenerationController`**: Both single-workbench generation and full-project generation follow `project_paths.dirs(project).gen_layout` and `templates/Rte/` overlay priority.

## Risks / Trade-offs

- SWC and BSW mappings can share an `OsTask` and have interleaving `RteBswPositionInTask` / `RtePositionInTask` numbers; moving a BSW event up/down in Tab 3 only mutates `RteBswEventToTaskMapping` containers and resolves ties only among BSW siblings so SWC configurations remain untouched.
- Some modules' `OsTask` names referenced in `RteBswMappedToTaskRef` may not exist in `Os` ECUC (e.g., partial project); `list_os_tasks()` marks those with `missing_in_os=True` so mappings remain inspectable and editable instead of disappearing silently.
