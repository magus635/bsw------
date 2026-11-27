# System Services & Diagnostics Workbench Capability

## ADDED Requirements

### Requirement: EcuM Startup, Shutdown, and Wakeup Source Management
`SystemServicesWorkbenchService` SHALL inspect `EcuM` (`EcuMGeneral`, `EcuMFlexConfiguration`, `EcuMCommonConfiguration`), list ordered `EcuMDriverInitListZero`–`EcuMDriverInitListThree` items along with loaded-module status (treating `Code`, `User`, and `Brs` as valid pseudo-modules), add/remove/reorder init items, and inspect/update `EcuMWakeupSource`, `EcuMResetMode`, `EcuMShutdownCause`, and default shutdown targets while enforcing `PreLockedError`.

#### Scenario: Reordering and adding an EcuM DriverInit item
- **WHEN** an engineer calls `move_ecum_init_item()` or `add_ecum_init_item()` on `EcuMDriverInitListOne`
- **THEN** the underlying `EcuMDriverInitItem` sub-containers update order/contents accordingly and `EcuM` is marked modified
- **AND** `list_ecum_init_items()` flags items whose `EcuMModuleID` is absent from loaded modules (excluding `Code`, `User`, `Brs`) with `ECUM_INIT_MODULE_NOT_LOADED`

### Requirement: BswM Rule Decoding, ActionList Ordering, and Mode Port Control
`SystemServicesWorkbenchService` SHALL decode `BswMRule` -> `BswMLogicalExpression` -> `BswMModeCondition` (`BswMConditionMode` + `BswMConditionValue`) trees into readable expressions with cycle detection (`visited` path guard), sort `BswMActionListItem` entries by `(BswMActionListItemIndex, sub_index)`, reorder action list items with sequential index renumbering, and edit `BswMGeneral` switches, rules, action lists, and `BswMModeRequestPort` settings.

#### Scenario: Recursive BswM expression decoding and cycle detection
- **WHEN** a `BswMRule` references nested `BswMLogicalExpression` nodes and `BswMModeCondition` leaf conditions
- **THEN** `list_bswm_rules()` renders a readable boolean expression string (e.g., `(ESH_State == ESH_WAIT_FOR_NVM) AND ...`)
- **AND** if a cyclic `BswMArgumentRef` exists, expression decoding terminates safely with `(CYCLE)` and diagnostics emit `BSWM_CYCLE_DETECTED`

### Requirement: Multi-Core OS Resource, Task, ISR, and Stack Overview
`SystemServicesWorkbenchService` SHALL aggregate `OsOS`, `OsHooks`, `OsCore`, `OsApplication`, `EcucPartition`, `OsTask` (with owner application/core and Alarm/ScheduleTable triggers), `OsIsr`, `OsCounter`/`OsAlarm`/`OsScheduleTable`, and `OsResource`/`OsSpinlock`, compute per-core stack budgets (`OsStackSummary` when present or `Task + ISR + CoreStacks`), and allow inline editing of Task, ISR, ScheduleTable, and general OS parameters.

#### Scenario: Aggregating OsCore, OsApplication owners, triggers, and stack totals
- **WHEN** `list_os_core_summaries()` and `list_os_tasks()` run on a multi-core `Os` configuration with `OsAlarm` and `OsScheduleTable` activations
- **THEN** each core reports its system application, partition, task/ISR counts, and summed stack budget, while each `OsTaskRow` lists its owner `OsApplication` and activating alarms/schedule tables

### Requirement: Dcm + CanTp + PduR TP End-to-End Diagnostic Chain & Service Editing
`SystemServicesWorkbenchService` SHALL stitch end-to-end UDS diagnostic channels across `DcmDslProtocolRow`, `PduRRoutingPath` (`TRANSPORT_PROTOCOL` or shared-PDU fallback), `CanTpRxNSdu`/`CanTpTxNSdu` (plus FlowControl NPdus), and `CanIf` CAN IDs/DLCs, support inline editing of `CanTp` timing/BS/STmin/Padding and `DcmDslBuffer` sizes, and provide UDS `DcmDsdService` and `DcmDspSessionRow` management plus `DcmDspSecurityRow` and DID/Routine visibility.

#### Scenario: Stitching Dcm Rx/Tx channels through PduR TP to CanTp and CanIf
- **WHEN** `Dcm` physical/functional Rx and Tx PDUs route through `PduR` `TRANSPORT_PROTOCOL` paths to `CanTpRxNSdu`/`CanTpTxNSdu` and `CanIfRxPduCfg`/`CanIfTxPduCfg`
- **THEN** `list_diag_channels()` pairs each `DcmDslProtocolRx`/`DcmDslProtocolTx` with its `CanTp` NSdu parameters (`BS`, `STmin`, `Padding`), `PduR` path, and `CanIf` CAN ID & DLC

### Requirement: Det Batch Matrix and CDD / Platform Extension Visibility
`SystemServicesWorkbenchService` SHALL inspect `DetGeneral`, scan all loaded modules for `DevErrorDetect`/`Det` enablement flags supporting per-module and batch toggling (`set_all_module_det_flags()`), classify loaded CDD (`Cdd*`) and platform extension modules (`VX1000`, `vBRS`, `vBaseEnv`, `vSet`, `Crc`, `Det`, custom modules), and register a selected module into `EcuMDriverInitListOne`.

#### Scenario: Batch toggling module DevErrorDetect flags and registering a CDD init item
- **WHEN** an engineer runs `set_all_module_det_flags(True)` and calls `add_ecum_init_item()` for a loaded `CddMotor` module
- **THEN** every discovered module `*DevErrorDetect` parameter is set to `True` and `CddMotor_Init` appears in `EcuMDriverInitListOne` marked as loaded

### Requirement: Cross-Module System Services Validation Rule and Problems Navigation
`SystemServicesValidationRule` (`SystemServicesRule`) SHALL run once per project validation pass (anchored on the first loaded module in `BswM`, `EcuM`, `Os`, `Dcm`, `CanTp`, `Det`), emit zero false-positive errors on empty/stub modules, detect all 16 diagnostic codes across EcuM, BswM, Os, Dcm/CanTp, and Det, and embed `workbench_tab=<idx>; code=<code>` metadata so `ProblemsView` routes directly to the corresponding `SystemServicesWorkbench` tab.

#### Scenario: BswM duplicate rule ID and broken Dcm ref route to matching workbench tabs
- **WHEN** validation runs on a project with a duplicate `BswMRuleId` and a broken `DcmDslProtocolRxPduRef`
- **THEN** `SystemServicesRule` emits `workbench_tab=1; code=BSWM_DUP_RULE_ID` and `workbench_tab=3; code=DIAG_BROKEN_DCM_REF` once across the project
- **AND** activating either problem in `ProblemsView` opens `SystemServicesWorkbench` directly on Tab 2 (BswM) or Tab 4 (Dcm & CanTp)

### Requirement: 5-Tab System Services Workbench UI and Atomic Multi-Module Undo
`DaVinciMainWindow` SHALL expose `🛠️ 服务与诊断` on `LeftNavigationBar` (fitting all 12 rail buttons compactly), a quick button on `HomeDashboardWidget`, a `Tools` menu item, and tree context menu actions (`🛠️ 打开系统服务与诊断工作台...`) launching the 5-tab `SystemServicesWorkbench` (`1. EcuM 启动与休眠`, `2. BswM 规则与模式`, `3. Os 多核与调度资源`, `4. Dcm 与 CanTp 诊断`, `5. Det / CDD 与平台服务`) with Cancel/Revert snapshot rollback and single `ReplaceMultipleModulesCommand` Undo/Redo.

#### Scenario: Multi-module edit in SystemServicesWorkbench and single-step Undo/Redo
- **WHEN** an engineer reorders `EcuMDriverInitListOne`, edits an `OsTask` priority, and tunes `CanTpBs` inside `SystemServicesWorkbench` and clicks OK
- **THEN** a single `ReplaceMultipleModulesCommand` is pushed onto `DaVinciMainWindow.undo_stack` so `undo()` and `redo()` revert or replay all edited service/diagnostic modules together
