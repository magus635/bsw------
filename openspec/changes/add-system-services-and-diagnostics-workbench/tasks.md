## 1. OpenSpec & Architecture
- [ ] 1.1 Create and validate `openspec/changes/add-system-services-and-diagnostics-workbench/` (`openspec validate add-system-services-and-diagnostics-workbench --strict`)

## 2. Core System Services Domain Package (`autosar_configurator/core/services/`)
- [ ] 2.1 Implement data models in `autosar_configurator/core/services/models.py` for EcuM, BswM, Os, Dcm/CanTp, Det/CDD, and `ServiceDiagnostic`
- [ ] 2.2 Implement `SystemServicesWorkbenchService` extraction, editing, ordering, batch DET toggle, CDD->EcuM registration, snapshot/restore, and 16 diagnostic rules in `autosar_configurator/core/services/service.py` and export via `__init__.py`

## 3. Validation Rule & Problems Navigation
- [ ] 3.1 Implement `SystemServicesValidationRule` in `autosar_configurator/core/rules/system_services_rules.py`, export in `__init__.py`, and register in `ValidationEngine.register_default_rules()`
- [ ] 3.2 Extend `ProblemsView._show_context_menu()` and `ImpactProblemsController._on_problem_activated()` to route `SystemServicesRule` findings to the matching workbench tab

## 4. 5-Tab UI & Main Window Integration
- [ ] 4.1 Implement `EcuMTab`, `BswMTab`, `OsResourcesTab`, `DiagDcmCanTpTab`, and `DetCddTab` in `autosar_configurator/ui/dialogs/system_services_tabs.py`
- [ ] 4.2 Implement `SystemServicesWorkbench` in `autosar_configurator/ui/dialogs/system_services_workbench.py` with header health pills, lazy dirty-tab refresh, and Cancel/Revert snapshot rollback
- [ ] 4.3 Wire left navigation rail (`navigation_bar.py`), home dashboard (`home_dashboard.py`), tree context menu (`davinci_tree_view.py`), main window launch + `ReplaceMultipleModulesCommand` Undo/Redo (`davinci_main_window.py`), and manual (`user_manual_dialog.py`)

## 5. Verification
- [ ] 5.1 Add comprehensive domain & validation tests plus read-only `StartApplication1.dpa` verification in `tests/core/test_system_services_service.py`
- [ ] 5.2 Add Qt UI & Undo/Redo/Problems routing tests in `tests/ui/test_system_services_workbench.py` and update `tests/ui/test_left_navigation_bar.py`
- [ ] 5.3 Run pytest suite and `openspec validate add-system-services-and-diagnostics-workbench --strict` and mark all tasks complete
