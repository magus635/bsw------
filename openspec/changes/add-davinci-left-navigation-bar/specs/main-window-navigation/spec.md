## ADDED Requirements

### Requirement: Left Functional Navigation Bar

`DaVinciMainWindow` SHALL display a vertical `LeftNavigationBar` along the left edge of the central workspace with inline page switching (`Home` and `Basic Editor`), workbench/tool launchers (`RTE/SchM`, `Memory Map`, `HW Mapping`, `Validation`, `Dependency Graph`, `Code Generation`), bottom-pinned `Project Settings` and `User Manual` actions, and a `View -> Navigation Bar` visibility toggle.

#### Scenario: Switching inline views and toggling Navigation Bar visibility

- **WHEN** the user clicks `Home` or `Basic Editor` on `LeftNavigationBar`
- **THEN** the central `QStackedWidget` displays the selected view (`HomeDashboardWidget` or `basic_editor_page`) and marks only that navigation button active
- **WHEN** the user unchecks or re-checks `View -> Navigation Bar`
- **THEN** `LeftNavigationBar` hides or shows cleanly without disturbing menus, toolbars, or bottom docks

#### Scenario: Workbench enablement and live validation badge synchronization

- **WHEN** no project is loaded
- **THEN** project-scoped rail buttons (`rte_workbench`, `memmap`, `hw_mapping`, `settings`, `validate`, `dep_graph`, `generate`) remain disabled while `home`, `basic_editor`, and `help` stay enabled
- **WHEN** `ValidationController` completes a validation run
- **THEN** the `validate` rail button displays an error count badge when `error_count > 0` (or warning count badge when only warnings exist) and clears the badge when valid

### Requirement: Project Home Dashboard and Default Workspace Transitions

`HomeDashboardWidget` SHALL provide quick-start actions and recent project entries when no project is loaded, summarize loaded project status, 4-step workflow, and clickable module cards when a project is open, and follow A1 default workspace transition rules.

#### Scenario: Empty-state Home renders quick actions and recent projects

- **WHEN** `DaVinciMainWindow` starts without an open project
- **THEN** `Home` is active by default showing New, Open, Import DaVinci, Import EB actions and existing recent `.dpa`/config files
- **WHEN** the user activates an entry in the recent projects list
- **THEN** `ProjectController._open_recent_file()` is invoked with that entry's file path

#### Scenario: Project open transitions to Basic Editor and module cards navigate cleanly

- **WHEN** a project is loaded or created in `DaVinciMainWindow`
- **THEN** the workspace switches automatically to `Basic Editor` and enables project-scoped rail items
- **WHEN** the user manually returns to `Home` on the same open project and subsequently refreshes actions on that same project
- **THEN** the workspace stays on `Home` without forcing a switch back to `Basic Editor`
- **WHEN** the user clicks a module card on `Home` (or triggers Search / `Problems` item navigation)
- **THEN** the workspace switches to `Basic Editor` and selects the corresponding module or target container in `DaVinciTreeView`
