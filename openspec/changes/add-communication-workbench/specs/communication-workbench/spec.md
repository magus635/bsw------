# Communication Workbench Capability

## ADDED Requirements

### Requirement: Enhanced Multi-Encoding DBC Database Parsing
`DbcParser` SHALL remain backwards-compatible for existing `parse(path) -> List[DbcMessage]` callers while providing `parse_database(path) -> DbcDatabase` to decode `utf-8-sig`, `utf-8`, `gb18030`, and `cp1252` files and extract `BU_` nodes, `CM_` comments, `BA_DEF_`/`BA_DEF_DEF_`/`BA_` global/message/signal attributes (`DBName`, `BusType`, `GenMsgCycleTime`, `GenMsgSendType`, `VFrameFormat`, `DiagRequest`, `DiagResponse`, `DiagState`, `GenSigStartValue`, `GenSigInactiveValue`, `GenSigSendType`), and CAN-FD flags (`dlc > 8` or `VFrameFormat`).

#### Scenario: Parsing OEM DBC with attributes and diagnostic flags
- **WHEN** `DbcParser.parse_database()` parses a GB18030 or UTF-8 DBC containing `BU_`, `BA_DEF_` enums, `BA_` message cycle times/diagnostic flags, and signal initial values
- **THEN** `DbcDatabase.ecu_nodes`, message `cycle_time_ms`, `send_type`, `is_diag`, `diag_role`, `is_fd`, and signal `init_value`/`send_type`/`comment` are populated accurately
- **AND** `DbcParser.parse(path)` continues to return the flat `List[DbcMessage]` with all legacy fields intact

### Requirement: Cross-Module Communication Stack Model Aggregation
`CommunicationWorkbenchService` SHALL aggregate loaded modules across `Can`, `CanTrcv`, `CanIf`, `CanSM`, `CanTp`, `PduR`, `Com`, `ComM`, and `EcuC` to surface end-to-end channel chains, TX/RX/Diagnostic message chains, `ComSignal` rows (reading both single and multi `ComIPduSignalRef` references), Motorola (`BIG_ENDIAN`) and Intel (`LITTLE_ENDIAN`/`OPAQUE`) bit occupancy grids, and `PduR` routing tables.

#### Scenario: Aggregating full TX and RX chains across Com, PduR, CanIf, EcuC, CanSM, ComM, Can, and CanTrcv
- **WHEN** a project contains Vector `/ActiveEcuC/...` or EB Tresos `/<Module>/<Module>/...` communication modules
- **THEN** `list_channel_rows()`, `list_message_rows()`, `list_signal_rows()`, `list_pdur_routing_rows()`, and `get_ipdu_bit_grid()` resolve cross-module references and report accurate CAN IDs, DLC/PDU lengths, cycles, HandleIds, and bit layouts

### Requirement: Communication Stack Editing, HandleId Normalization, and Atomic Undo
`CommunicationWorkbenchService` SHALL support inline editing of message parameters (`CanIf` CAN ID/type/DLC + synced `EcuC/Pdu/PduLength` + `ComTxMode`), signal layout/type/init/timeout properties, `PduRRoutingPath` CRUD, sequential `0..N-1` HandleId recomputation (`recompute_handle_ids()`), and pre-compile lock checks (`PreLockedError`), while `CommunicationWorkbench` supports multi-module Cancel rollback and pushes a single `ReplaceMultipleModulesCommand` onto `DaVinciMainWindow.undo_stack` upon acceptance.

#### Scenario: Multi-module edit and single-step undo
- **WHEN** an engineer modifies a message DLC and period across `CanIf`, `EcuC`, and `Com` inside `CommunicationWorkbench` and accepts the dialog
- **THEN** a single `ReplaceMultipleModulesCommand` is pushed to `undo_stack` so `undo()` reverts all modified communication modules together

### Requirement: Previewable Multi-Module DBC Derivation
`plan_dbc_sync()` and `apply_dbc_sync()` SHALL filter a parsed `DbcDatabase` by selected `ecu_node` direction (`TX`/`RX`), exclude diagnostic frames unless `include_diag=True`, match existing ECUC messages by `(direction, can_id, is_extended)` or sanitized message name without creating duplicates, preview `create`/`update`/`unchanged`/`skip` actions, and atomically create or update `EcuC` PDUs, `CanIf` TX/RX PDUs, `PduR` routing paths, and `Com` IPDUs/signals with sequential HandleIds.

#### Scenario: Deriving a new TX/RX DBC frame across EcuC, CanIf, PduR, and Com
- **WHEN** `plan_dbc_sync()` and `apply_dbc_sync()` execute on a DBC containing a new TX periodic frame with Motorola signals for the selected ECU node
- **THEN** `EcuC/Pdu`, `CanIfTxPduCfg`, `PduRRoutingPath`, `ComIPdu` (including `ComTxMode`), and `ComSignal` containers are created with valid cross-module references
- **AND** re-running `plan_dbc_sync()` on the updated project classifies that frame as unchanged rather than duplicating containers

### Requirement: Cross-Module Communication Validation Rule and Problems Navigation
`CommunicationValidationRule` (`CommunicationRule`) SHALL run once per project validation pass (anchored on the first present module in `Com`, `PduR`, `CanIf`, `CanSM`, `ComM`, `Can`) to detect duplicate CAN IDs, PDU length mismatches, broken `PduR` chains, orphan `ComIPdu`/`CanIf` PDUs, Motorola/Intel signal bit overlaps and out-of-bounds layouts, duplicate HandleIds, broken channel links, and zero-period TX modes, emitting `workbench_tab` metadata so double-clicking in `ProblemsView` opens `CommunicationWorkbench` on the matching tab.

#### Scenario: Signal bit overlap triggers CommunicationRule error and jumps to Signals tab
- **WHEN** two `ComSignal` instances in the same `ComIPdu` occupy overlapping Motorola or Intel bits and validation runs
- **THEN** `ValidationEngine` emits a `CommunicationRule` error containing `workbench_tab=2; code=SIGNAL_BIT_OVERLAP` exactly once across the project
- **AND** activating that problem in `ProblemsView` launches `CommunicationWorkbench` directly on Tab 3 (Signals)

### Requirement: 5-Tab Communication Workbench UI and Main Window Integration
`DaVinciMainWindow` SHALL expose `📡 通信配置` on `LeftNavigationBar`, a quick-launch card button on `HomeDashboardWidget`, a `Tools` menu action, and a tree context-menu action on communication modules opening the 5-tab `CommunicationWorkbench` (`1. 总线与通道`, `2. 报文与全链路`, `3. 信号矩阵与位图`, `4. PduR 路由矩阵`, `5. DBC 同步派生`), and offer guided module addition when no communication module is loaded.

#### Scenario: Opening Communication Workbench from left navigation rail and jumping tabs from health banner
- **WHEN** a user with loaded communication modules clicks `📡 通信配置` on `LeftNavigationBar` (or right-clicks `Com` in `DaVinciTreeView`)
- **THEN** `CommunicationWorkbench` opens showing all 5 tabs, an 8xN byte-bit layout grid for the selected IPdu, clickable health-check badges, and interactive DBC sync preview/apply controls
