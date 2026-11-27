# Change: Add DaVinci-Style Left Navigation Rail and Home Dashboard

## Why

Currently `DaVinciMainWindow` presents only the `DaVinciTreeView` + `DaVinciConfigPanel` split pane (equivalent to DaVinci Configurator's Basic Editor), while specialized workbenches (`RteSchmWorkbench`, `MemoryMapWorkbench`, `HardwareMappingWizard`), validation, dependency graph, code generation, and project properties are scattered across top menus. Beginners and daily integrators lack a clear left-side functional navigation rail and an inline Home dashboard showing recent projects, recommended workflow steps, and loaded module overview cards.

## What Changes

- **Add `LeftNavigationBar` (`autosar_configurator/ui/widgets/navigation_bar.py`)**: A 92px left-side vertical navigation rail organized into 3 functional groups (`Home`/`Basic Editor`, specialized workbenches `RTE/SchM`/`MemMap`/`HW Mapping`, and `Validation`/`Dependency Graph`/`Code Generation`) plus bottom-pinned `Project Settings` and `User Manual`, with active-page highlight, dynamic enable/disable sync, and validation error/warning badge display.
- **Add `HomeDashboardWidget` (`autosar_configurator/ui/widgets/home_dashboard.py`)**: Scrollable inline landing dashboard with an empty-project welcome view (quick actions + clickable recent projects list) and a project-loaded overview (project metadata, 4-step workflow guide, clickable module cards that jump into Basic Editor and select that module in `DaVinciTreeView`, and quick-launch tool cards).
- **Integrate into `DaVinciMainWindow`, `DaVinciTreeView`, and Controllers**:
  - Replace the central widget container with `LeftNavigationBar` + `QStackedWidget(HomeDashboardWidget, basic_editor_page)` and add `View -> Navigation Bar` visibility toggle.
  - Default to `Home` when no project is open; automatically switch to `Basic Editor` when opening or creating a project, clicking a module card, or triggering search/`Problems` navigation, while preserving manual `Home` visits while working within the same project.
  - Push validation error/warning counts to `LeftNavigationBar` badge and `HomeDashboardWidget`, keep recent-files list synced, and update `UserManualDialog` layout documentation.

## Impact

- Affected specs: `main-window-navigation` (new capability under `openspec/specs/` once archived)
- Affected code:
  - `autosar_configurator/ui/widgets/{navigation_bar.py,home_dashboard.py,davinci_tree_view.py}`
  - `autosar_configurator/ui/davinci_main_window.py`
  - `autosar_configurator/ui/controllers/{validation_controller.py,navigation_controller.py,impact_problems_controller.py,project_controller.py}`
  - `autosar_configurator/ui/dialogs/user_manual_dialog.py`
  - `tests/ui/test_left_navigation_bar.py`
