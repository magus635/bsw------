## 1. Implementation

- [x] 1.1 Scaffold OpenSpec change (`add-davinci-left-navigation-bar`)
- [x] 1.2 Implement `autosar_configurator/ui/widgets/navigation_bar.py` (`NavRailButton`, `LeftNavigationBar` with 10 grouped items, active states, and badges)
- [x] 1.3 Implement `autosar_configurator/ui/widgets/home_dashboard.py` (`HomeDashboardWidget` empty/loaded states, recent projects list, 4-step workflow, and module overview cards)
- [x] 1.4 Add `DaVinciTreeView.select_module()` and wire `LeftNavigationBar` + `HomeDashboardWidget` + `View -> Navigation Bar` into `DaVinciMainWindow`, `ValidationController`, `NavigationController`, `ImpactProblemsController`, `ProjectController`, and `UserManualDialog`
- [x] 1.5 Add Qt UI tests in `tests/ui/test_left_navigation_bar.py`
- [x] 1.6 Validate OpenSpec strictly (`openspec validate add-davinci-left-navigation-bar --strict`) and run all UI verification suites
