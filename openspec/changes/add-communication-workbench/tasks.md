## 1. OpenSpec & DBC Parser
- [x] 1.1 Create and validate `openspec/changes/add-communication-workbench/` (`openspec validate add-communication-workbench --strict`)
- [x] 1.2 Backwards-compatibly upgrade `DbcParser` with `DbcDatabase`, `parse_database()`, multi-encoding support (`utf-8-sig`/`utf-8`/`gb18030`/`cp1252`), `BU_`, `CM_`, `BA_DEF_`/`BA_DEF_DEF_`/`BA_`, CAN-FD & diagnostic classification

## 2. Core Communication Domain & Validation
- [x] 2.1 Implement `autosar_configurator/core/communication/models.py` and `bit_layout.py` (Motorola & Intel bit layout + overlap/OOB detection)
- [x] 2.2 Implement `CommunicationWorkbenchService` in `autosar_configurator/core/communication/service.py` (channels, messages, signals, PduR routing, inline edits, HandleId recomputation, snapshots, 10 diagnostics)
- [x] 2.3 Implement `plan_dbc_sync()` & `apply_dbc_sync()` in `autosar_configurator/core/communication/dbc_sync.py` and package exports in `__init__.py`
- [x] 2.4 Implement `CommunicationValidationRule` in `autosar_configurator/core/rules/communication_rules.py`, register in `ValidationEngine.register_default_rules()`, and add `ReplaceMultipleModulesCommand` in `autosar_configurator/ui/commands.py`

## 3. UI Workbench & Main Window Integration
- [x] 3.1 Implement 5-tab `CommunicationWorkbench` UI (`communication_tabs.py`, `communication_workbench.py`) with clickable health pills, inline editors, 8xN visual bit-layout grid, PduR routing editor, and DBC sync tab
- [x] 3.2 Integrate `📡 通信配置` left rail item, Home Dashboard card button, tree right-click action, Tools menu action, `ProblemsView` double-click jump, and `UserManualDialog` updates

## 4. Verification
- [x] 4.1 Add comprehensive unit & UI tests (`test_dbc_importer.py`, `test_communication_service.py`, `test_communication_workbench.py`, `test_left_navigation_bar.py`) including read-only `StartApplication` smoke checks
- [x] 4.2 Run pytest & `openspec validate add-communication-workbench --strict` and mark all tasks complete
