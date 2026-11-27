## 1. OpenSpec & Persistence Foundation
- [x] 1.1 Create and validate `openspec/changes/add-rte-phase2-phase3-and-service-mapping/` (`openspec validate add-rte-phase2-phase3-and-service-mapping --strict`)
- [x] 1.2 Add `rte_data_mappings` and `rte_service_connectors` persistence to `WorkspaceProject` in `autosar_configurator/core/workspace_manager.py`
- [x] 1.3 Include mapping overlays in `RteConfigSnapshot`, `snapshot_rte_config`, `restore_rte_config`, and `ReplaceModuleContainersCommand` (`workbench_service.py`, `commands.py`)

## 2. SWC Indexer, Extractor & Phase 2/3 Code Generation
- [x] 2.1 Implement `SwcSystemIndex` parser in `autosar_configurator/generator/rte/swc_parser.py` (data types, interfaces, SWC/ServiceComponent runnables/ports/events, connectors, `SENDER-RECEIVER-TO-SIGNAL-MAPPING`, `I-SIGNAL` resolution)
- [x] 2.2 Extend `autosar_configurator/generator/rte/model.py` and `extractor.py` with SWC component IR, Data Mapping / Service Connector overlay merging, `OsApplication` partitioning, and unified multi-core Task schedules
- [x] 2.3 Implement Phase 2/3 ANSI/C99 renderers in `autosar_configurator/generator/rte/renderers_phase23.py` (`Rte_Type.h`, `Rte_DataHandleType.h`, `Components/Rte_<Swc>.h`, `Components/Rte_<Swc>_Type.h`, `Rte.c`, `Rte_<OsApplication>.c`)
- [x] 2.4 Wire `include_phase2_3` generation & preview into `autosar_configurator/generator/rte/generator.py` and update exports in `autosar_configurator/generator/rte/__init__.py`

## 3. Domain Service, Diagnostics & 6-Tab UI Workbench
- [x] 3.1 Add Data Mapping CRUD/auto-match, Service Port CRUD/auto-connect, SWC Event-to-Task mapping, and Phase 2/3 diagnostics (`workbench_tab=3/4`) in `autosar_configurator/generator/rte/workbench_service.py`
- [x] 3.2 Implement `DataMappingTab` and `ServiceMappingTab` in `autosar_configurator/ui/dialogs/rte_schm_phase23_tabs.py`, opt-in SWC editing in `rte_schm_tabs.py`, and upgrade `RteSchmWorkbench` to 6 tabs (`rte_schm_workbench.py`)
- [x] 3.3 Update tooltips and help documentation in `navigation_bar.py` and `user_manual_dialog.py`

## 4. Verification
- [x] 4.1 Update `tests/ui/test_rte_schm_workbench.py` (`tabs.count() == 6`) and add `tests/generator/test_rte_phase2_phase3.py` and `tests/ui/test_rte_phase23_workbench.py` (including clang `-fsyntax-only -Wall -Wextra -Werror` check and read-only `StartApplication1.dpa` verification)
- [x] 4.2 Run pytest suite & `openspec validate add-rte-phase2-phase3-and-service-mapping --strict` and mark all tasks complete
