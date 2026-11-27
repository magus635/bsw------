## ADDED Requirements

### Requirement: Extended InternalBehavior Event Parsing and Header Preview

The Phase 1 RTE/SchM subsystem SHALL extract BSW scheduling event metadata (`BswIbEventData`) from `system/**/*_ib_bswmd.arxml` and provide a non-mutating header preview API (`RteSchMGenerator.preview()`).

#### Scenario: BSW timing events resolve entity names and periods

- **WHEN** `BswIbIndex.load_directory()` parses a `BSW-INTERNAL-BEHAVIOR` containing `BSW-TIMING-EVENT` elements referencing `BSW-SCHEDULABLE-ENTITY` and `BSW-MODULE-ENTRY`
- **THEN** each parsed `BswIbEventData` records its `short_name`, `ar_path`, `event_kind`, resolved `entity_name`, and parsed float `period_sec`, and is indexed in `BswIbIndex.events_by_path`

#### Scenario: Non-mutating generation preview reports file statuses and overlays

- **WHEN** `RteSchMGenerator.preview()` is called with an output directory and optional project `overlay_root`
- **THEN** no files on disk are created or overwritten
- **AND** each `RtePreviewFile` accurately classifies disk parity as `new`, `updated`, `unchanged`, `preserved` (for existing stubs), or `overlay` (when overridden by `templates/Rte/`)

### Requirement: BSW Module Instance Discovery and Synchronization Workbench Tab

The RTE/SchM Workbench (`RteWorkbenchService` and Tab 1 `BswInstancesTab`) SHALL compare `RteBswModuleInstance` containers against loaded workspace modules and `InternalBehavior` metadata, supporting registration, removal, and synchronization.

#### Scenario: Add unregistered loaded BSW module instance

- **WHEN** the user adds an unregistered loaded BSW module (such as `Com` or `CanIf`) via the BSW Instances tab or `RteWorkbenchService.add_bsw_instance()`
- **THEN** an `RteBswModuleInstance` container with valid `RteBswModuleConfigurationRef` (`ECUC-MODULE-CONFIGURATION-VALUES`), resolved `RteBswImplementationRef` (`BSW-IMPLEMENTATION`), and initial `RteBswExclusiveAreaImpl` sub-containers from InternalBehavior is added to `Rte` configuration and marked modified

#### Scenario: Clean unloaded BSW instance

- **WHEN** `Rte` references an unloaded module (such as `CanNm`) shown with unloaded status and the user removes that instance
- **THEN** the `RteBswModuleInstance` container is removed cleanly from `Rte` configuration and subsequent extraction no longer warns about that unloaded module

### Requirement: SchM ExclusiveArea Protection Matrix Tab

Tab 2 (`ExclusiveAreasTab`) SHALL display all active BSW ExclusiveAreas across `Rte` ECUC and `InternalBehavior`, allowing direct inline and batch configuration of protection mechanisms, `OsResource` / `OsSpinlock` references, and function-generation flags with validation feedback.

#### Scenario: Configure OS_RESOURCE protection mechanism and validate missing target

- **WHEN** the user changes an ExclusiveArea mechanism to `OS_RESOURCE` without selecting an `OsResource`
- **THEN** the row reports an explicit validation error and blocks invalid generation
- **WHEN** the user selects a valid `OsResource` from the `Os` module list
- **THEN** `RteBswExclusiveAreaImpl` stores `RteExclusiveAreaImplMechanism="OS_RESOURCE"` and `RteBswExclusiveAreaOsResourceRef` pointing to `/ActiveEcuC/Os/<Resource>`, and Tab 4's live `SchM_<ApiName>.h` preview reflects `GetResource(<Resource>)` / `ReleaseResource(<Resource>)`

#### Scenario: Synchronize missing InternalBehavior ExclusiveAreas

- **WHEN** an active module declares ExclusiveAreas in `_ib_bswmd.arxml` that do not yet exist in `Rte` ECUC and the user runs sync
- **THEN** missing `RteBswExclusiveAreaImpl` sub-containers are created under that module's `RteBswModuleInstance` with default `ALL_INTERRUPT_BLOCKING` and `RteBswExclusiveAreaRef` metadata

### Requirement: BSW Event-to-Task Mapping and Execution Order Tab

Tab 3 (`TaskMappingTab`) SHALL group mapped events by `OsTask` in execution order, show unmapped BSW events from both `Rte` ECUC and `InternalBehavior`, display SWC task mappings as read-only context, and support mapping, reordering, and unmapping BSW events.

#### Scenario: Map an unmapped BSW event to an OsTask and reorder within task

- **WHEN** the user assigns an unmapped BSW scheduling event to an `OsTask`
- **THEN** an `RteBswEventToTaskMapping` container under the owning `RteBswModuleInstance` is updated (or created) with `RteBswMappedToTaskRef` and the next `RteBswPositionInTask`
- **WHEN** the user moves a BSW event up or down within that `OsTask`
- **THEN** adjacent BSW mappings update their `RteBswPositionInTask` values deterministically without modifying read-only SWC `RteEventToTaskMapping` containers

#### Scenario: Unmap a BSW event from its OsTask

- **WHEN** the user unmaps a BSW mapping from its `OsTask`
- **THEN** `RteBswMappedToTaskRef` and `RteBswPositionInTask` are cleared while retaining `RteBswEventToTaskMapping` and `RteBswEventRef` so the event returns to the unmapped pool

### Requirement: Global Generation Settings, Live Preview, and MainWindow Workbench Entry

Tab 4 (`GeneratePreviewTab`) SHALL clearly separate Phase 1 active generation switches from ECUC-only reservation parameters, preview generated headers and diagnostics live, execute standalone Phase 1 RTE/SchM generation, and integrate into `DaVinciMainWindow`.

#### Scenario: Toggling RteGeneration flag updates live header preview

- **WHEN** the user toggles `RteEnableMultiCore` or `RteDisableRteInitMemory` in Tab 4's Phase 1 active group
- **THEN** `RteGeneration` ECUC parameters are updated immediately and the live `Rte_Main.h` preview reflects the new setting without writing to disk

#### Scenario: MainWindow launches workbench and integrates Undo and Reference Refresh

- **WHEN** a project containing `Rte` is open and the user invokes `RTE / SchM 工作台...` from the `Generate` or `Tools` menu (including right after `New Project...`)
- **THEN** `RteSchmWorkbench` opens with all four tabs populated
- **WHEN** the user confirms workbench edits with `确定`
- **THEN** the edit batch is pushed to `undo_stack` via `ReplaceModuleContainersCommand` (supporting `Ctrl+Z` undo), refreshes cross-module reference resolution and reverse-reference indices, enables project saving, and refreshes main configuration views
- **WHEN** the user clicks `取消` or `恢复打开前状态`
- **THEN** all changes made during the workbench session are rolled back cleanly to the opening snapshot

### Requirement: Baseline Pre-Lock Enforcement and Cached IB Performance

`RteWorkbenchService` and the workbench tabs SHALL enforce `ConfigurationManager.check_editable()` (`PreLockedError`), cache `BswIbIndex` across edits with explicit reload support, and avoid destructive table rebuilds during single-row ExclusiveArea edits.

#### Scenario: Pre-locked Rte parameters refuse modification cleanly

- **WHEN** an `Rte` parameter or container is locked by the Format 8 Pre baseline and the user attempts to edit it via `RteWorkbenchService` or the UI
- **THEN** `PreLockedError` prevents the mutation (skipping locked entries cleanly during batch/sync while reporting skipped counts) and the UI reverts the widget to the locked value with a warning

#### Scenario: Single-row ExclusiveArea edit and CUSTOM mechanism sync in place

- **WHEN** the user changes an ExclusiveArea row's mechanism in Tab 2
- **THEN** the `BswIbIndex` cache is reused without re-scanning `system/` XML files, existing row widgets are updated in place without rebuilding the full table, and selecting `CUSTOM` automatically checks and locks `生成函数` matching `render_schm_h()`'s function-declaration output
