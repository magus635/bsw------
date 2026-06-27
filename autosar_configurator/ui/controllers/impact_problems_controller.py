"""Impact / Problems views controller — extracted from DaVinciMainWindow (P2-6, phase 5).

Owns the Impact Analysis dock and the Problems dock: their construction, the
"check impact" analysis flow, dependency-rule parsing, and item-navigation from
either dock. The dock widgets and their toggle actions are set back onto the
window (``self.win``) so existing references (e.g. validate_configuration using
problems_view/problems_dock) keep working.
"""
import logging
from pathlib import Path
from typing import Dict, List

from PySide6.QtCore import Qt
from PySide6.QtGui import QKeySequence
from PySide6.QtWidgets import QDockWidget, QMessageBox

logger = logging.getLogger(__name__)


class ImpactProblemsController:
    """Impact-analysis and Problems dock behaviour for the main window."""

    def __init__(self, win):
        self.win = win

    # ----- Impact Analysis dock ---------------------------------------------
    def _setup_impact_view(self):
        """Setup Impact Analysis dock widget."""
        win = self.win
        win.impact_dock = QDockWidget("Impact Analysis", win)
        win.impact_dock.setObjectName("ImpactAnalysisDock")
        win.impact_dock.setAllowedAreas(Qt.RightDockWidgetArea | Qt.LeftDockWidgetArea | Qt.BottomDockWidgetArea)

        from ..widgets.impact_view import ImpactView
        win.impact_view = ImpactView()
        win.impact_view.item_requested.connect(self._on_impact_item_requested)
        win.impact_dock.setWidget(win.impact_view)

        win.addDockWidget(Qt.RightDockWidgetArea, win.impact_dock)
        win.impact_dock.hide()

        # Add to view menu
        win.toggle_impact_action = win.impact_dock.toggleViewAction()
        win.toggle_impact_action.setText("Impact Analysis")
        win.toggle_impact_action.setShortcut(QKeySequence("Ctrl+Shift+I"))

        # Find view menu and add action
        menubar = win.menuBar()
        for action in menubar.actions():
            if action.text() == "View":
                action.menu().addAction(win.toggle_impact_action)
                break

    def _on_impact_item_requested(self, logical_path: str):
        """Navigate to an item from the impact view.

        logical_path format: Module.Container.SubContainer.Param
        e.g., Can.CanConfigSet_0.CanController_0.CanControllerBaudrateConfig_0.CanFDBytePayload
        """
        win = self.win
        if '.' not in logical_path:
            return

        parts = logical_path.split('.')
        if len(parts) < 2:
            return

        # Convert dot-separated path to ARXML path format
        # e.g., Can.CanConfigSet_0.CanController_0 -> /Can/CanConfigSet_0/CanController_0
        arxml_path = '/' + '/'.join(parts)

        # Use tree_view's built-in method to select and navigate
        param_name = win.tree_view.select_item_by_path(arxml_path)

        if param_name:
            win.statusbar.showMessage(f"✅ 已导航到参数: {param_name}", 3000)
        else:
            # Check if we found a container
            selected = win.tree_view.currentItem()
            if selected:
                win.statusbar.showMessage(f"✅ 已导航到: {selected.text(0)}", 3000)
            else:
                # Fallback: use search
                search_term = parts[-1]
                if hasattr(win, 'search_widget'):
                    win.search_widget.search_input.setText(search_term)
                    win.toggle_search_action.setChecked(True)
                    win.search_widget.show()
                    win.search_widget.focus_search()
                    win.statusbar.showMessage(f"🔍 搜索: {search_term}", 2000)

    def _find_container_recursive(self, containers, target_name: str):
        """Recursively find a container by short_name."""
        for container in containers:
            if container.short_name == target_name:
                return container
            # Check sub-containers
            found = self._find_container_recursive(container.sub_containers, target_name)
            if found:
                return found
        return None

    def _load_dependency_rules_from_file(self, file_path: Path, include_pending: bool = False) -> List[Dict]:
        """Parse dependency rules from a dependencies.md file.

        Args:
            file_path: Path to the dependencies.md file
            include_pending: If True, also load pending [ ] rules (for impact analysis).
                           If False, only load confirmed [x] rules (for validation).

        Returns list of rule dicts with: source_param, condition, condition_value,
        target_param, requirement, requirement_value, reason
        """
        import re
        rules = []

        try:
            content = file_path.read_text(encoding='utf-8')

            # Parse markdown table rows
            # Format: | # | [x] or [ ] | source | source_param | condition | target_param | requirement | reason |
            if include_pending:
                # Match both [x] (confirmed) and [ ] (pending), but NOT [-] (rejected)
                status_pattern = r'\[\s*x?\s*\]'  # Matches [x], [ x], [ ], etc.
            else:
                # Only match confirmed [x] rules
                status_pattern = r'\[\s*x\s*\]'

            table_pattern = rf'\|\s*\d+\s*\|\s*{status_pattern}\s*\|[^|]+\|\s*`([^`]+)`\s*\|[^|]+\|\s*`([^`]+)`\s*\|[^|]+\|\s*([^|]+)\|'

            for match in re.finditer(table_pattern, content, re.IGNORECASE):
                source_param = match.group(1).strip()
                target_param = match.group(2).strip()
                reason = match.group(3).strip()

                rules.append({
                    'source_param': source_param,
                    'target_param': target_param,
                    'condition': '!= null',
                    'condition_value': '',
                    'requirement': 'exists',
                    'requirement_value': 'true',
                    'reason': reason
                })

            status_desc = "confirmed + pending" if include_pending else "confirmed only"
            logger.info(f"Parsed {len(rules)} rules ({status_desc}) from {file_path}")

        except Exception as e:
            logger.error(f"Error loading dependency rules: {e}")

        return rules

    def _handle_check_impact(self, container_path: str, param_name: str):
        """Analyze and show impact of changing a parameter using the ImpactView dock."""
        win = self.win
        try:
            logger.info(f"Check Impact requested for: {container_path} / {param_name}")

            if not win.config_manager or not win.current_project:
                win.statusbar.showMessage("⚠️ 请先打开项目", 3000)
                logger.warning("Check Impact abort: No active project/manager")
                return

            from ...core.analysis.impact_analyzer import ImpactAnalyzer
            from datetime import datetime

            # Initialize a FRESH analyzer each time to capture latest config state
            analyzer = ImpactAnalyzer()

            # Build structure from all modules in project (using LIVE configuration objects)
            total_containers = 0
            for module_name, manager in win.current_project.module_managers.items():
                if manager.configuration:
                    container_count = len(manager.configuration.containers)
                    total_containers += container_count
                    analyzer.build_from_configuration(manager.configuration, module_name)

            logger.debug(f"[{datetime.now().strftime('%H:%M:%S')}] Fresh graph built: {total_containers} top-level containers")

            # Always reload rules from file for impact analysis to get latest state
            # (File may have been regenerated by cross-module analysis)
            if win.current_project.path:
                deps_file = win.current_project.path.parent / "dependencies.md"
                if deps_file.exists():
                    # For impact analysis, include both confirmed AND pending rules
                    # This allows users to see potential impacts before confirming rules
                    rules = self._load_dependency_rules_from_file(deps_file, include_pending=True)
                    if rules:
                        win.current_project.dependency_rules = rules

            if hasattr(win.current_project, 'dependency_rules') and win.current_project.dependency_rules:
                analyzer.load_dependencies(win.current_project.dependency_rules)

            # Get graph stats for debugging
            stats = analyzer.get_graph_stats()
            logger.info(f"Impact graph: {stats['total_nodes']} nodes, {stats['total_edges']} edges "
                        f"(structural: {stats['structural_edges']}, inferred: {stats.get('inferred_edges', 0)}, logical: {stats['logical_edges']})")

            # Determine source node path - use dot-separated format
            if hasattr(win.config_manager.module_def, 'short_name'):
                module_name = win.config_manager.module_def.short_name
            else:
                # Fallback if module_def missing (shouldn't happen)
                module_name = container_path.split('/')[1] if container_path.startswith('/') else container_path.split('.')[0]

            # Clean container path: remove leading slashes, convert slashes to dots
            clean_cont_path = container_path.lstrip('/').replace('/', '.')

            # Avoid duplicate module name prefix (container_path may already start with module name)
            if clean_cont_path.startswith(module_name + '.'):
                source_node = f"{clean_cont_path}.{param_name}"
            elif clean_cont_path.startswith(module_name):
                # Container path IS just the module name
                source_node = f"{clean_cont_path}.{param_name}"
            else:
                source_node = f"{module_name}.{clean_cont_path}.{param_name}"

            logger.info(f"Analyzing impact for source node: {source_node}")

            # Analyze
            impacts = analyzer.analyze_impact(source_node)
            logger.info(f"Impact analysis result: Found {len(impacts)} items")

            # Show in dock with status info
            win.impact_view.display_impacts(source_node, impacts, stats)
            win.impact_dock.show()
            win.impact_dock.raise_()

            # Status bar message
            if impacts:
                win.statusbar.showMessage(f"找到 {len(impacts)} 个受影响的配置项", 3000)
            else:
                win.statusbar.showMessage(f"未找到受影响的配置项 (图: {stats['total_nodes']} 节点)", 3000)

        except Exception as e:
            import traceback
            error_msg = f"Check Impact failed: {str(e)}"
            logger.error(error_msg)
            logger.error(traceback.format_exc())
            win.statusbar.showMessage(f"⚠️ {error_msg}", 5000)
            QMessageBox.critical(win, "Impact Analysis Error", error_msg)

    # ----- Problems dock -----------------------------------------------------
    def _setup_problems_view(self):
        """Setup the centralized Problems View bottom dock."""
        win = self.win
        win.problems_dock = QDockWidget("Problems", win)
        win.problems_dock.setObjectName("ProblemsDock")
        win.problems_dock.setAllowedAreas(Qt.BottomDockWidgetArea | Qt.TopDockWidgetArea)

        from ..widgets.problems_view import ProblemsView
        win.problems_view = ProblemsView()
        win.problems_view.item_requested.connect(self._on_problems_item_requested)
        win.problems_dock.setWidget(win.problems_view)

        win.addDockWidget(Qt.BottomDockWidgetArea, win.problems_dock)
        win.problems_dock.hide()

        # Add to view menu
        win.toggle_problems_action = win.problems_dock.toggleViewAction()
        win.toggle_problems_action.setText("Problems")
        win.toggle_problems_action.setShortcut(QKeySequence("Ctrl+Shift+M"))

        menubar = win.menuBar()
        for action in menubar.actions():
            if action.text() == "View":
                action.menu().addAction(win.toggle_problems_action)
                break

    def _on_problems_item_requested(self, container_path: str, parameter_name: str):
        """Navigate to a problem source."""
        win = self.win
        if not container_path:
            return

        # 1. Expand/select in tree
        win.tree_view.select_item_by_path(container_path)

        # 2. Highlight in config panel if it's a parameter
        if parameter_name:
            # Note: We rely on the selection triggering the load
            pass
