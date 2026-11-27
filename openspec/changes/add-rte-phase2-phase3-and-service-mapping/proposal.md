# Change: RTE Phase 2/3 Code Generation, SWC Data Mapping, and Service Mapping (P2)

## Why
Phase 1 delivered `SchM_*.h`, `Rte.h`, `Rte_Main.h`, `Rte_Cfg.h`, `Rte_Cbk.h`, and the 4-tab `RteSchmWorkbench` for BSW instance synchronization, ExclusiveArea protection, and BSW Event-to-Task mapping. However, production AUTOSAR projects (such as `StartApplication`) also require:
1. Indexing read-only `system/` SWC descriptions (`Developer/`, `ServiceComponents/`, `System/FlatExtract.arxml`, `System/Communication.arxml`) into structured models without mutating upstream OEM files.
2. Viewing and editing **SWC Port ↔ ComSignal Data Mapping** and **ServiceComponent / Assembly Port Connections** (`ComM`, `EcuM`, `BswM`, `Dcm`, `Det`, `NvM`, `Os`) plus **SWC Event-to-Task mapping**, persisted safely inside `.dpa` project overlays with snapshot/Undo support.
3. Synthesizing **Phase 2 SWC contract headers** (`Components/Rte_<Swc>.h`, `Components/Rte_<Swc>_Type.h`, `Rte_DataHandleType.h`, full `Rte_Type.h`) and **Phase 3 multi-core scheduling & communication glue C sources** (`Rte.c`, `Rte_<OsApplication>.c`).

## What Changes
- **SWC/System ARXML Indexer** (`autosar_configurator/generator/rte/swc_parser.py`): Parses data types (`SW-BASE-TYPE`, `IMPLEMENTATION-DATA-TYPE`, `DATA-TYPE-MAP`), port interfaces (`SENDER-RECEIVER-INTERFACE`, `CLIENT-SERVER-INTERFACE`, `MODE-SWITCH-INTERFACE`), SWC/ServiceComponent types & runnables, composition connectors (`ASSEMBLY-SW-CONNECTOR`, `DELEGATION-SW-CONNECTOR`), `SENDER-RECEIVER-TO-SIGNAL-MAPPING`, and `I-SIGNAL` / `I-SIGNAL-TO-I-PDU-MAPPING` chains.
- **Project Persistence & Multi-Overlay Undo** (`workspace_manager.py`, `workbench_service.py`, `commands.py`): Persists `rte_data_mappings` and `rte_service_connectors` overlays in `.dpa` files and snapshots/restores them atomically on workbench Revert/Cancel/Undo/Redo.
- **Phase 2/3 IR, Extractor, & C Renderers** (`model.py`, `extractor.py`, `renderers_phase23.py`, `generator.py`): Joins SWCs, Data Mappings, Service Connectors, `Com` ECUC signals, and `OsApplication` core partitions into C headers and multi-core `Rte.c` / `Rte_<OsApplication>.c` while keeping all Phase 1 headers byte-for-byte compatible.
- **6-Tab UI Workbench & Cross-Module Diagnostics** (`rte_schm_phase23_tabs.py`, `rte_schm_tabs.py`, `rte_schm_workbench.py`): Upgrades `RteSchmWorkbench` with `4. 数据映射 (SWC↔Com)` and `5. 服务与端口连接`, adds an opt-in SWC Task Mapping edit toggle on Tab 3, exposes 5 Phase-2/3 health rules routed via `RteSchmRule`, and updates preview/generation.

## Impact
- Affected specs: `rte-phase2-phase3`
- Affected code: `autosar_configurator/core/workspace_manager.py`, `autosar_configurator/ui/commands.py`, `autosar_configurator/generator/rte/`, `autosar_configurator/ui/dialogs/`, `autosar_configurator/ui/widgets/navigation_bar.py`, `autosar_configurator/ui/dialogs/user_manual_dialog.py`.
- Backwards-compatible with all Phase 1 tests, legacy `.dpa` projects without overlay keys, and existing `SchM_*.h` / `Rte_Main.h` parity checks.
