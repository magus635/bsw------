# Change: Add 5-Tab Communication Workbench and Multi-Module DBC Derivation

## Why

In Vector DaVinci projects such as `StartApplication.dpa`, CAN communication spans `Com`, `PduR`, `CanIf`, `CanSM`, `ComM`, `CanTp`, `CanTrcv`, `Can`, and `EcuC`. Editing ECUC containers separately in the generic tree forces engineers to manually stitch together PDU references, HandleIds, Motorola/Intel bit layouts, and TX timing, while `DbcImporter` only imports flat fields into a single module and does not parse `BU_`, `BA_DEF_`, `BA_`, `CM_`, or OEM encodings (`GB18030`).

## What Changes

- **Upgrade `DbcParser` (`autosar_configurator/core/importers/dbc_importer.py`)**: Backwards-compatibly add `DbcDatabase` and `parse_database(path)` with multi-encoding decoding (`utf-8-sig`, `utf-8`, `gb18030`, `cp1252`), `BU_` node lists, `CM_` comments, `BA_DEF_`/`BA_DEF_DEF_`/`BA_` attributes (`DBName`, `BusType`, `GenMsgCycleTime`, `GenMsgSendType`, `VFrameFormat`, `DiagRequest`, `DiagResponse`, `DiagState`, `GenSigStartValue`, `GenSigInactiveValue`, `GenSigSendType`), and FD detection (`dlc > 8` or `VFrameFormat`).
- **Add Communication Domain Package (`autosar_configurator/core/communication/`)**:
  - `models.py`: Data models for channels, end-to-end message chains, signals, PduR routing paths, diagnostics, and DBC sync plans/results.
  - `bit_layout.py`: AUTOSAR Motorola (`BIG_ENDIAN`) & Intel (`LITTLE_ENDIAN` / `OPAQUE`) bit occupancy calculation plus frame overlap/out-of-bounds detection.
  - `service.py`: `CommunicationWorkbenchService` aggregating cross-module chains across Vector `/ActiveEcuC/...` and EB Tresos paths, supporting inline edits, sequential HandleId recomputation, multi-module snapshotting/restoration, and 10 cross-module communication diagnostics.
  - `dbc_sync.py`: `plan_dbc_sync()` & `apply_dbc_sync()` generating non-destructive preview diffs and deriving/updating `EcuC`, `CanIf`, `PduR`, and `Com` (`ComIPdu` multi-ref `ComIPduSignalRef` and `ComSignal` items) per selected ECU node.
- **Add `CommunicationValidationRule` & `ReplaceMultipleModulesCommand`**:
  - Anchor `CommunicationRule` once per project validation pass via `ValidationEngine.register_default_rules()`.
  - Route `ProblemsView.problem_activated` findings directly to the matching `CommunicationWorkbench` tab.
  - Add `ReplaceMultipleModulesCommand` to push multi-module workbench edits atomically onto `DaVinciMainWindow.undo_stack`.
- **Add 5-Tab `CommunicationWorkbench` UI & Navigation Entry Points**:
  - Tabs: `1. 总线与通道`, `2. 报文与全链路`, `3. 信号矩阵与位图`, `4. PduR 路由矩阵`, `5. DBC 同步派生`.
  - Wire left rail (`📡 通信配置`), `HomeDashboardWidget` quick-tools button, `Tools` menu action, tree context menu (`📡 打开通信配置工作台...`), and `UserManualDialog`.

## Impact

- Affected specs: `communication-workbench` (new capability)
- Affected code:
  - `autosar_configurator/core/importers/dbc_importer.py`
  - `autosar_configurator/core/communication/{__init__.py,models.py,bit_layout.py,service.py,dbc_sync.py}`
  - `autosar_configurator/core/rules/{communication_rules.py,__init__.py}`, `autosar_configurator/core/validation_engine.py`
  - `autosar_configurator/ui/{commands.py,davinci_main_window.py}`
  - `autosar_configurator/ui/dialogs/{communication_tabs.py,communication_workbench.py,user_manual_dialog.py}`
  - `autosar_configurator/ui/widgets/{navigation_bar.py,home_dashboard.py,davinci_tree_view.py}`
  - `autosar_configurator/ui/controllers/impact_problems_controller.py`
  - `tests/core/{test_dbc_importer.py,test_communication_service.py}`, `tests/ui/{test_communication_workbench.py,test_left_navigation_bar.py}`
