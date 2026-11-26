# Change: Add 4-Tab RTE / SchM Configuration and Generation Workbench

## Why

Phase 1 introduced the model-driven `RteSchMGenerator` pipeline (`Rte*.h`, `SchM_*.h`, and non-destructive stubs), yet users currently have only the generic ECUC tree and project-wide `Generate Code` button:

- `RteBswModuleInstance` containers can drift from loaded project modules and `system/**/*_ib_bswmd.arxml` InternalBehavior definitions (e.g., disabled modules remaining in `Rte` or newly added BSW modules lacking instances).
- Configuring dozens of `RteBswExclusiveAreaImpl` protection mechanisms (`OS_RESOURCE`, `OS_SPINLOCK`, interrupt blocking) and `RteBswEventToTaskMapping` task order positions across nested containers in the generic tree is tedious and hides cross-module task execution order.
- Users have no dedicated UI to inspect `RteGeneration` global flags, preview synthesized headers/overlays/diagnostics, or run standalone RTE/SchM generation before doing a full project build.

## What Changes

- **Extend `ib_parser` (`autosar_configurator/generator/rte/ib_parser.py`)**: Parse `BSW-INTERNAL-BEHAVIOR/EVENTS/*` into `BswIbEventData` (`short_name`, `ar_path`, `event_kind`, `entity_ref`, `entity_name`, `period_sec`) and index `events_by_path` alongside existing IB structures.
- **Extend `RteSchMGenerator` (`autosar_configurator/generator/rte/model.py`, `generator.py`)**: Add non-mutating `preview()` returning `RtePreviewFile` statuses (`new`, `updated`, `unchanged`, `preserved`, `overlay`) plus `RteGenerationReport`.
- **Add `RteWorkbenchService` (`autosar_configurator/generator/rte/workbench_service.py`)**: Pure-Python domain layer unifying BSW instance synchronization, ExclusiveArea matrix editing/batch assignment, OS Task event mapping/reordering, and `RteGeneration` settings + preview/generation execution with clean ECUC write-back.
- **Add 4-Tab Workbench UI (`autosar_configurator/ui/dialogs/rte_schm_workbench.py`, `rte_schm_tabs.py`)**: `RteSchmWorkbench` dialog with tabs:
  1. BSW 实例与同步 (`BswInstancesTab`)
  2. 临界区矩阵 (SchM) (`ExclusiveAreasTab`)
  3. Task 调度映射 (`TaskMappingTab`)
  4. 全局开关与生成预览 (`GeneratePreviewTab`)
- **Integrate with `DaVinciMainWindow` & `GenerationController`**: Add `RTE / SchM 工作台...` under `Generate` and `Tools` menus, refresh tree/panel & dirty state when ECUC edits occur, and expose optional `generate_type_stub`/`force`/`apply_overlay` options in `_run_rte_schm_generation()`.

## Impact

- Affected specs: `rte-schm-workbench` (new capability under `openspec/specs/` once archived)
- Affected code:
  - `autosar_configurator/generator/rte/{model.py,ib_parser.py,generator.py,workbench_service.py,__init__.py}`
  - `autosar_configurator/ui/controllers/generation_controller.py`
  - `autosar_configurator/ui/dialogs/{rte_schm_tabs.py,rte_schm_workbench.py}`
  - `autosar_configurator/ui/davinci_main_window.py`
  - `tests/generator/test_rte_workbench_service.py`, `tests/ui/test_rte_schm_workbench.py`
