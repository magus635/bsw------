## 1. Implementation

- [x] 1.1 Extend `autosar_configurator/generator/rte/ib_parser.py` (`BswIbEventData`), `model.py` (`RtePreviewFile`), and `generator.py` (`RteSchMGenerator.preview()`)
- [x] 1.2 Implement `autosar_configurator/generator/rte/workbench_service.py` (`RteWorkbenchService` for BSW instance sync, ExclusiveArea matrix, OS Task event mapping/ordering, `RteGeneration` settings, preview, and execution)
- [x] 1.3 Implement `autosar_configurator/ui/dialogs/rte_schm_tabs.py` (`ExclusiveAreasTab`, `TaskMappingTab`) and `rte_schm_workbench.py` (`BswInstancesTab`, `GeneratePreviewTab`, `RteSchmWorkbench`)
- [x] 1.4 Wire `RTE / SchM 工作台...` into `DaVinciMainWindow` (`Generate` and `Tools` menus, mode gating, main window sync) and add optional stub/force/overlay flags to `GenerationController._run_rte_schm_generation()`
- [x] 1.5 Add unit tests (`tests/generator/test_rte_workbench_service.py`) and Qt UI tests (`tests/ui/test_rte_schm_workbench.py`) including real-project read-only verification
- [x] 1.6 Validate OpenSpec change strictly and verify all pytest suites pass
- [x] 1.7 Implement P0 improvements: `ib_index` caching, `PreLockedError` checks, EB ref prefix support, `RteConfigSnapshot` Cancel/Revert/`ReplaceModuleContainersCommand` Undo, `resolve_all_references` + `new_project()` action enablement, `CUSTOM` checkbox lock, Tab 2 in-place update, Tab 4 Phase-1 vs ECUC grouping, doc sync, and P0 tests
- [x] 1.8 Implement P1 ergonomics & integration: top health-check quick-jump bar, bilingual Tab 2 mechanism labels/tooltips, Tab 3 `ExtendedSelection` batch mapping + period-aware `OsTask` recommendation & mixed-period summary, Tab 4 `compute_preview_diff()` + `CAndDiffHighlighter`, built-in `RteSchmGuideDialog` (`使用说明 (?)`), left-tree right-click `Rte` shortcut, `UserManualDialog` update, doc/spec sync, and P1 unit/UI tests
