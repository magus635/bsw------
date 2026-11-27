# Design: System Services & Diagnostics Workbench (BswM / EcuM / Os / Dcm+CanTp / Det+CDD)

## Context

`CommunicationWorkbench` and `RteSchmWorkbench` established a modular pattern: pure-Python domain services decoupled from PySide6 dialogs, snapshot-based rollback paired with `ReplaceMultipleModulesCommand` on `DaVinciMainWindow.undo_stack`, and single-anchor `ValidationRule` integration with `ProblemsView`. P3 brings the same structured editing, visualization, and cross-module diagnostics to System Services (`EcuM`, `BswM`, `Os`), Diagnostics (`Dcm` + `CanTp` + `PduR` TP), and `Det` / `CDD` / Platform extension modules.

## Goals / Non-Goals

- **Goals**:
  - Decode and safely edit deeply nested Vector MICROSAR & AUTOSAR / EB Tresos structures (`EcuMDriverInitList*`, `BswMRule`/`BswMLogicalExpression`/`BswMActionList`, `OsCore`/`OsTask`/`OsIsr`/`OsScheduleTable`/`OsAlarm`, `Dcm` ↔ `PduR` TP ↔ `CanTp` ↔ `CanIf`, `Det` + `*DevErrorDetect`, CDD + `vBRS`/`vBaseEnv`/`vSet`/`VX1000`/`Crc`).
  - Handle Vector choice containers accurately (e.g., `BswMConditionValue` -> `BswMBswMode`/`BswMIntMode`/`BswMRteMode`, `BswMAvailableActions` -> `BswMUserCallout`, `OsAlarmAction` -> `OsAlarmActivateTask`).
  - Guard all diagnostics against empty/stub modules so newly created or minimal configurations do not suffer false-positive errors.
  - Keep `LeftNavigationBar` completely visible on standard laptop displays when adding a 12th item.
- **Non-Goals**:
  - `Dem` / `NvM` / `WdgM` dedicated code generation (beyond showing existing EcuM/Det/CDD metadata and existing templates).
  - Modifying external read-only fixtures such as `/Users/qlwang/Desktop/test3/StartApplication1/StartApplication1.dpa`.

## Decisions

1. **Snapshot-based multi-module transaction**: `SystemServicesWorkbenchService.capture_snapshots()` captures `snapshot_rte_config()` across all loaded modules in `SYSTEM_SERVICE_MODULES` plus any detected CDD modules (`_is_cdd_module`), enabling instant Cancel/Revert rollback and single-command `ReplaceMultipleModulesCommand` Undo/Redo in `DaVinciMainWindow`.
2. **Vector + EB path & reference parity**: Shared helpers inspect both `reference_values` and `multi_reference_values`, normalize `/ActiveEcuC/...` and EB `/<Module>/<Module>/...` paths via `strip_ecuc_prefixes()`, and detect both dual-PDU `PduR` TP routing (`PduRSrcPduRef` -> `PduRDestPduRef` on `TRANSPORT_PROTOCOL` paths) and single-PDU direct sharing between `Dcm` and `CanTp`.
3. **Recursive cycle-guarded BswM expression decoding**: `_format_bswm_expression` walks `BswMRuleExpressionRef` -> `BswMLogicalExpression` (`BswMArgumentRef`) -> `BswMModeCondition` (`BswMConditionMode` + `BswMConditionValue`) with a `visited` set of normalized container paths so self-referential or cyclic `BswMLogicalExpression` graphs return `"(CYCLE)"` instead of overflowing the call stack and report `BSWM_CYCLE_DETECTED`.
4. **Ordered `BswMActionList` and `EcuMDriverInitList*` edits**: `move_bswm_action_item` updates both `sub_containers` order and sequential `BswMActionListItemIndex` values (`0..N-1`); `move_ecum_init_item` reorders `sub_containers` directly inside `EcuMDriverInitList*`, checking `PreLockedError` before mutating.
5. **Dual workbench access on `CanTp`**: Right-clicking `CanTp` in `DaVinciTreeView` continues offering `📡 打开通信配置工作台...` alongside `🛠️ 打开系统服务与诊断工作台...` so users can reach either CAN matrix or Dcm/CanTp ISO-TP diagnostics effortlessly.
6. **12-item `LeftNavigationBar` height budget**: Compacting `NavRailButton` fixed size height from `50px` to `46px` keeps all 12 navigation items plus separators visible within ~680px viewport height.

## Risks / Trade-offs

- **Real-world Vector BSWMD choice sub-containers**: Some Vector choice wrappers (e.g., `BswMConditionValue`, `BswMAvailableActions`, `OsAlarmAction`) nest parameters 1-2 levels below the choice container. Inspecting child containers recursively avoids brittle hardcoding of a single choice name.
- **Per-core OS stack calculation**: When `OsStackSummary/OsStack` is present (e.g., MICROSAR `Os`), per-core stack sums `OsStackSize` grouped by `OsStackCore`; otherwise it falls back to summing owned `OsTaskStackSize` + `OsIsrStackSize` + `OsCoreStacks` so both Vector and simplified/EB OS configurations compute meaningful budgets.
