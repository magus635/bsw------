## Context
The Phase 1 RTE/SchM generator (`autosar_configurator/generator/rte/`) synthesizes core RTE and per-BSW SchM headers from `Rte`, `Os`, `MemMap`, and `system/**/*_ib_bswmd.arxml`. Projects imported from Vector DaVinci (e.g. `StartApplication`) also store read-only SWC definitions (`system/Developer/`, `system/ServiceComponents/`), flat system compositions (`system/System/FlatExtract.arxml`), communication signal mappings (`system/System/Communication.arxml`), and ECUC SWC mappings (`RteSwComponentInstance/RteEventToTaskMapping`, `RteExclusiveAreaImplementation`) alongside `OsApplication` core/task partitions in `Os` ECUC and `ComSystemTemplateSystemSignalRef` on `ComSignal`.

## Goals / Non-Goals
- **Goals**:
  - Extract typed SWC data types, interfaces, ports, runnables, events, assembly/delegation connectors, and SR-to-Signal mappings via `SwcSystemIndex`.
  - Keep OEM/user `system/**/*.arxml` files strictly read-only; persist GUI Data Mapping and Service Connector edits as non-destructive overlay records (`rte_data_mappings`, `rte_service_connectors`) in `.dpa` and include them in `RteConfigSnapshot` for Revert/Cancel/Undo/Redo.
  - Generate ANSI/C99 (`-Wall -Wextra -Werror` clean) Phase 2 SWC contract headers (`Components/Rte_<Swc>.h`, `Components/Rte_<Swc>_Type.h`, `Rte_DataHandleType.h`, full `Rte_Type.h`) and Phase 3 multi-core scheduling & communication files (`Rte.c`, `Rte_<OsApplication>.c`).
  - Surface Data Mapping, Service Port Connection, and SWC Event-to-Task editing in `RteSchmWorkbench` without breaking existing Phase 1 workflows or tests.
- **Non-Goals**:
  - Rewriting `system/System/FlatExtract.arxml` or `system/Developer/*.arxml` source ARXML files directly.
  - Implementing full AUTOSAR E2E/Transformer code or Complex Queued SR FIFOs (Phase 2/3 focuses on non-queued SR signals, inter-SWC shared buffers, synchronous C/S direct calls, mode switch helpers, ExclusiveAreas, and multi-core OS Task dispatch).
  - Modifying user files under `/Users/qlwang/Desktop/未命名文件夹/` or `/Users/qlwang/Desktop/test3/`.

## Decisions
- **Read-Only ARXML Base + `.dpa` Overlay Persistence**: Vector `system/` ARXMLs are treated as immutable imported artifacts. User additions, overrides, and removals (`action="map"` / `action="unmap"`) live on `WorkspaceProject` (`rte_data_mappings`, `rte_service_connectors`), serialize into `.dpa` JSON, and participate in `snapshot_rte_config()` / `restore_rte_config()`.
- **Dual-Path SystemSignal Resolution**: Vector's `ComSignal.ComSystemTemplateSystemSignalRef` frequently points to an `I-SIGNAL-TO-I-PDU-MAPPING` path (e.g. `/PDU/<Pdu>/<Sig>`) while `FlatExtract.arxml` `SENDER-RECEIVER-TO-SIGNAL-MAPPING` references `/Signal/<Sig>`. `SwcSystemIndex` resolves `/PDU/...` -> `I-SIGNAL` -> `/Signal/...` automatically while also matching direct `/Signal/...` paths or leaf names.
- **Preservation of Existing `Rte_Type.h`**: Consistent with Phase 1 stub semantics, existing custom `Rte_Type.h` on disk is preserved; when absent and `model.rte_type_defs` is populated, `RteSchMGenerator` emits full C `typedef` declarations sorted topologically (`VALUE` -> `TYPE_REFERENCE` -> `ARRAY` -> `STRUCTURE`), avoiding collisions with standard `Std_Types.h` primitive names.
- **Opt-In SWC Editing in Tab 3**: `TaskMappingTab` adds `edit_swc_check` (unchecked by default) and `list_task_mappings(..., include_unmapped_swc=False)` defaults to `False`, preserving existing BSW task-mapping test contracts while giving full interactive SWC Event-to-Task control when toggled on.

## Risks / Trade-offs
- **C Identifier & Type Dependency Cycles**: Complex struct/array types must be sorted after their member/element base types and standard `Std_Types.h` types (`uint8`..`float64`, `boolean`, `Std_ReturnType`) must not be re-typedefed. Topological sort + primitive exclusion handles this safely.
- **Single-Core vs Multi-Core `OsApplication`**: Projects lacking `OsApplication` partitions fall back cleanly to Core 0 and emit tasks inside `Rte.c` (or a default partition) so generation works for both simple single-core and complex dual-core ECUs.
