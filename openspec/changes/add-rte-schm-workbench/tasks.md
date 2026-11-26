## 1. Implementation

- [x] 1.1 Extend `autosar_configurator/generator/rte/ib_parser.py` (`BswIbEventData`), `model.py` (`RtePreviewFile`), and `generator.py` (`RteSchMGenerator.preview()`)
- [x] 1.2 Implement `autosar_configurator/generator/rte/workbench_service.py` (`RteWorkbenchService` for BSW instance sync, ExclusiveArea matrix, OS Task event mapping/ordering, `RteGeneration` settings, preview, and execution)
- [x] 1.3 Implement `autosar_configurator/ui/dialogs/rte_schm_tabs.py` (`ExclusiveAreasTab`, `TaskMappingTab`) and `rte_schm_workbench.py` (`BswInstancesTab`, `GeneratePreviewTab`, `RteSchmWorkbench`)
- [x] 1.4 Wire `RTE / SchM 工作台...` into `DaVinciMainWindow` (`Generate` and `Tools` menus, mode gating, main window sync) and add optional stub/force/overlay flags to `GenerationController._run_rte_schm_generation()`
- [x] 1.5 Add unit tests (`tests/generator/test_rte_workbench_service.py`) and Qt UI tests (`tests/ui/test_rte_schm_workbench.py`) including real-project read-only verification
- [x] 1.6 Validate OpenSpec change strictly and verify all pytest suites pass
