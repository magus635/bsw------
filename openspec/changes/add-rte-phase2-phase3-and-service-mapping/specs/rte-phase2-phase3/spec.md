## ADDED Requirements

### Requirement: SWC and ServiceComponent ARXML Indexing
The RTE subsystem SHALL index SWC data types, interfaces, ports, runnables, events, composition connectors, SR-to-Signal mappings, and I-SIGNAL mappings read-only from `system/**/*.arxml`.

#### Scenario: Indexing DataTypes, SWCs, Connectors, and Vector I-Signal Mappings
- **WHEN** `SwcSystemIndex.load_directory(system_dir)` scans a project `system/` directory containing `APPLICATION-SW-COMPONENT-TYPE`, `SERVICE-SW-COMPONENT-TYPE`, `COMPOSITION-SW-COMPONENT-TYPE`, and `I-SIGNAL` definitions
- **THEN** it SHALL resolve C types via `DATA-TYPE-MAP` and `SW-BASE-TYPE`, link `DELEGATION-SW-CONNECTOR` outer-port signal mappings onto inner component ports, and map `/PDU/...` `I-SIGNAL-TO-I-PDU-MAPPING` paths to their underlying `SYSTEM-SIGNAL` path without modifying any source ARXML file.

### Requirement: SWC Data Mapping and Service Connector Overlay Persistence
The workspace and RTE service SHALL persist GUI Data Mapping and Service Connector edits in `.dpa` project overlays and include them in snapshot/Undo/Revert operations.

#### Scenario: Overlay Persistence Across Save/Reload and Undo/Redo
- **WHEN** a user binds or unbinds an SWC SR port to a `ComSignal`, or connects/disconnects an assembly/service port in `RteWorkbenchService`
- **THEN** the overlay SHALL serialize in `WorkspaceProject` (`rte_data_mappings`, `rte_service_connectors`) across `.dpa` save/load and SHALL revert atomically via `RteConfigSnapshot` and `ReplaceModuleContainersCommand`.

### Requirement: Interactive Data Mapping, Service Mapping, and SWC Task Mapping
`RteWorkbenchService` and the 6-tab `RteSchmWorkbench` SHALL support inspecting, editing, auto-matching, and diagnosing SWC↔Com Data Mappings (`Tab 4`), Service/Assembly Port Connections (`Tab 5`), and SWC Event-to-Task Mappings (`Tab 3`).

#### Scenario: Data Mapping and Service Port Diagnostics Routing
- **WHEN** a project has SWC ports mapped to missing or wrong-direction `ComSignal`s, unmapped SWC SR ports, or unconnected Service/Client ports
- **THEN** `RteWorkbenchService.collect_diagnostics()` SHALL emit `DATA_MAPPING_BROKEN_COM_SIGNAL`, `DATA_MAPPING_DIRECTION_MISMATCH`, `SWC_PORT_UNMAPPED_COM`, `SERVICE_PORT_UNCONNECTED`, or `SERVICE_CONNECTOR_BROKEN` targeting `workbench_tab=3` or `workbench_tab=4` so `ProblemsView` double-click and workbench health pills open the corresponding tab.

### Requirement: Phase 2 Contract Header and Phase 3 Multi-Core C Source Generation
`RteSchMGenerator` SHALL synthesize Phase 2 SWC contract headers and Phase 3 multi-core RTE implementation sources cleanly alongside Phase 1 headers without breaking Phase 1 parity.

#### Scenario: Generating Compilable Phase 2 Headers and Multi-Core Rte.c / Rte_<OsApplication>.c
- **WHEN** `RteSchMGenerator.generate()` runs with `include_phase2_3=True` on a project with SWC components and `OsApplication` partitions
- **THEN** it SHALL emit `include/Rte_DataHandleType.h`, `include/Components/Rte_<Swc>.h`, `include/Components/Rte_<Swc>_Type.h`, full `include/Rte_Type.h` (preserving existing custom `Rte_Type.h`), `src/Rte.c`, and `src/Rte_<OsApplication>.c` containing `Com_SendSignal`/`Com_ReceiveSignal`, direct server/inter-SWC calls, and `TASK(...)` dispatch loops ordered by position and compilable with `clang -fsyntax-only -Wall -Wextra -Werror`.
