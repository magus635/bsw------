# Change: Add 5-Tab System Services & Diagnostics Workbench (BswM / EcuM / Os / Dcm+CanTp / Det+CDD)

## Why

In Vector DaVinci projects such as `StartApplication.dpa`, system startup/shutdown (`EcuM`), mode arbitration (`BswM`), multi-core OS scheduling and resource budgets (`Os`), UDS/ISO-TP diagnostics (`Dcm` + `CanTp` + `PduR` TP), and development error/CDD/platform extensions (`Det`, `Crc`, `vBRS`, `vBaseEnv`, `vSet`, `VX1000`, `Cdd*`) form tightly linked cross-module chains. Editing deeply nested ARXML trees (such as `BswMRule -> BswMLogicalExpression -> BswMModeCondition`, `DcmDslProtocolRx -> PduRRoutingPath -> CanTpRxNSdu -> CanIfRxPduCfg`, or `EcuMDriverInitList*`) manually is error-prone and opaque.

## What Changes

- **Add System Services Domain Package (`autosar_configurator/core/services/`)**:
  - `models.py`: Data classes for `ServiceDiagnostic`, EcuM (`EcuMGeneralInfo`, `EcuMInitItemRow`, `EcuMWakeupSourceRow`, `EcuMModeCauseRow`), BswM (`BswMRuleRow`, `BswMActionListRow`, `BswMActionListItemRow`, `BswMModePortRow`, `BswMModeGroupRow`), Os (`OsGeneralInfo`, `OsCoreSummaryRow`, `OsTaskRow`, `OsIsrRow`, `OsTimingRow`, `OsSyncResourceRow`), Dcm/CanTp (`DiagChannelRow`, `DcmServiceRow`, `DcmSessionRow`, `DcmSecurityRow`, `DcmDidRoutineRow`), and Det/CDD (`DetGeneralInfo`, `ModuleDetFlagRow`, `CddPlatformModuleRow`).
  - `service.py`: `SystemServicesWorkbenchService` supporting Vector `/ActiveEcuC/...` and EB Tresos `/<Module>/<Module>/...` paths, `PreLockedError` enforcement, multi-module snapshotting/restoration, recursive cycle-guarded `BswM` expression decoding, ordered `EcuM` init-list & `BswMActionList` reordering, dual-PDU `PduR` TP stitching (`Dcm` ↔ `CanTp` ↔ `CanIf`) with single-PDU fallback, batch `DevErrorDetect` toggling, CDD registration into `EcuMDriverInitListOne`, and 16 cross-module diagnostics across Tabs 0–4.
- **Add `SystemServicesValidationRule` & `ProblemsView` Routing**:
  - Add `SystemServicesValidationRule` (`SystemServicesRule`) anchored once per validation pass (`ANCHOR_PRIORITY = ("BswM", "EcuM", "Os", "Dcm", "CanTp", "Det")`) and register it in `ValidationEngine.register_default_rules()`.
  - Update `ProblemsView._show_context_menu()` and `ImpactProblemsController._on_problem_activated()` to route `SystemServicesRule` findings straight to the matching workbench tab.
- **Add 5-Tab `SystemServicesWorkbench` UI & Navigation Entry Points**:
  - Tabs: `1. EcuM 启动与休眠`, `2. BswM 规则与模式`, `3. Os 多核与调度资源`, `4. Dcm 与 CanTp 诊断`, `5. Det / CDD 与平台服务`.
  - Wire left navigation rail (`🛠️ 服务与诊断`, compacting `NavRailButton` height to `46px`), `HomeDashboardWidget` quick-launch button (`🛠️ 服务与诊断工作台`), `Tools` menu action, tree context menu action (`🛠️ 打开系统服务与诊断工作台...` including dual entry on `CanTp`), `DaVinciMainWindow._launch_system_services_workbench` pushing `ReplaceMultipleModulesCommand`, and `UserManualDialog`.

## Impact

- Affected specs: `system-services-workbench` (new capability)
- Affected code:
  - `autosar_configurator/core/services/{__init__.py,models.py,service.py}`
  - `autosar_configurator/core/rules/{system_services_rules.py,__init__.py}`, `autosar_configurator/core/validation_engine.py`
  - `autosar_configurator/ui/{davinci_main_window.py}`
  - `autosar_configurator/ui/controllers/impact_problems_controller.py`
  - `autosar_configurator/ui/dialogs/{system_services_tabs.py,system_services_workbench.py,user_manual_dialog.py}`
  - `autosar_configurator/ui/widgets/{navigation_bar.py,home_dashboard.py,davinci_tree_view.py,problems_view.py}`
  - `tests/core/test_system_services_service.py`, `tests/ui/{test_system_services_workbench.py,test_left_navigation_bar.py}`
