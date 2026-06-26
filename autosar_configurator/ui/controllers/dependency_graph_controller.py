"""Dependency-graph controller — extracted from DaVinciMainWindow (P2-6, phase 4).

Owns the dependency-graph window, live graph refresh, the AI-backed
cross-module dependency analysis (with its background worker), and rule-based
cross-module validation. Holds a back-reference to the main window
(``self.win``) for shared state (current_project, config_manager, module_def,
settings, thread_pool) and Qt parenting. The graph dialog/widget are owned by
this controller.
"""
from pathlib import Path

from PySide6.QtCore import Slot, QRunnable, QUrl
from PySide6.QtGui import QDesktopServices
from PySide6.QtWidgets import QDialog, QVBoxLayout, QMessageBox

from ..async_workers import AIWorkerSignals
from ..widgets.dependency_graph import DependencyGraphWidget


class DependencyGraphController:
    """Cross-module dependency graph, analysis, and validation."""

    def __init__(self, win):
        self.win = win
        self.dep_graph_widget = None
        self.dep_graph_dialog = None

    def show_dependency_graph(self):
        """Show dependency graph in a new window."""
        win = self.win
        if not win.current_project and (not win.config_manager or not win.module_def):
            QMessageBox.warning(
                win,
                "No Configuration",
                "Please load a configuration first."
            )
            return

        # Create graph dialog if not exists or was closed
        if not self.dep_graph_dialog:
            self.dep_graph_dialog = QDialog(win)
            self.dep_graph_dialog.setWindowTitle("Dependency Graph")
            self.dep_graph_dialog.resize(800, 600)

            layout = QVBoxLayout(self.dep_graph_dialog)

            self.dep_graph_widget = DependencyGraphWidget()
            layout.addWidget(self.dep_graph_widget)

            # Show dialog
            self.dep_graph_dialog.show()
        else:
            self.dep_graph_dialog.raise_()
            self.dep_graph_dialog.activateWindow()
            if self.dep_graph_dialog.isHidden():
                self.dep_graph_dialog.show()

        # Always update graph data when showing
        if self.dep_graph_widget:
            if win.current_project:
                self.dep_graph_widget.build_graph_project(win.current_project)
            else:
                self.dep_graph_widget.build_graph(
                    win.module_def,
                    win.config_manager.configuration
                )

    def _update_dependency_graph_if_open(self):
        """Update dependency graph if the widget is open/visible."""
        win = self.win
        if (self.dep_graph_dialog is not None and
                self.dep_graph_dialog.isVisible() and
                self.dep_graph_widget is not None):

            if win.current_project:
                self.dep_graph_widget.build_graph_project(win.current_project)
            elif win.module_def and win.config_manager:
                self.dep_graph_widget.build_graph(
                    win.module_def,
                    win.config_manager.configuration
                )

    def _analyze_cross_module_dependencies(self):
        """Analyze project to find potential cross-module dependencies using AI."""
        win = self.win
        if not win.current_project:
            QMessageBox.warning(
                win,
                "需要项目",
                "请先打开一个包含多个模块的项目。\n\n"
                "此功能用于分析跨模块依赖，需要加载多模块项目。"
            )
            return

        from ...core.ai.dependency_analyzer import DependencyAnalyzer

        # Get API key
        api_key = win.settings.value("gemini_api_key")
        gemini_client = None
        if api_key:
            from ...core.ai.gemini_client import GeminiClient
            gemini_client = GeminiClient(api_key)

        # Create analyzer
        analyzer = DependencyAnalyzer(gemini_client)

        # Show progress
        win.statusBar().showMessage("正在分析跨模块依赖（后台运行中）...")

        # Extract parameters (this is fast)
        params = analyzer.extract_project_parameters(win.current_project)

        if not params:
            QMessageBox.information(
                win,
                "无参数",
                "未找到可分析的参数。请确保已加载模块配置。"
            )
            return

        # Store for later use
        project_dir = Path(win.current_project.path).parent if win.current_project.path else Path.cwd()
        output_path = project_dir / "dependencies.md"

        # Run AI analysis in background thread
        class DependencyWorker(QRunnable):
            def __init__(self, analyzer, params, output_path, signals):
                super().__init__()
                self.analyzer = analyzer
                self.params = params
                self.output_path = output_path
                self.signals = signals

            @Slot()
            def run(self):
                try:
                    # This is the slow AI call
                    dependencies = self.analyzer.analyze_with_ai(self.params)
                    # Generate markdown
                    self.analyzer.generate_markdown(dependencies, self.output_path)
                    self.signals.result.emit((dependencies, str(self.output_path)))
                except Exception as e:
                    self.signals.error.emit(str(e))

        # Create worker with signals
        worker = DependencyWorker(analyzer, params, output_path, AIWorkerSignals())
        worker.signals.result.connect(self._on_dependency_analysis_done)
        worker.signals.error.connect(self._on_dependency_analysis_error)

        # Submit to thread pool
        win.thread_pool.start(worker)

    def _on_dependency_analysis_done(self, result: object):
        """Handle completed dependency analysis."""
        win = self.win
        if isinstance(result, tuple):
            dependencies, output_path = result
            count = len(dependencies)
        else:
            # Fallback for string format (legacy)
            parts = str(result).split("|", 1)
            count = int(parts[0])
            output_path = parts[1]
            dependencies = []

        win.statusBar().showMessage(f"依赖分析完成，发现 {count} 条潜在规则", 5000)

        if not dependencies:
            QMessageBox.information(win, "分析完成", "未发现明显的跨模块依赖关系。")
            return

        # Use the new graphical review dialog
        from ..dialogs.dependency_review_dialog import DependencyReviewDialog
        dialog = DependencyReviewDialog(dependencies, win)

        # If dialog is accepted, store the confirmed rules
        if dialog.exec() == QDialog.Accepted:
            confirmed_rules = dialog.confirmed_rules
            if win.current_project:
                win.current_project.dependency_rules = confirmed_rules

                # Regenerate markdown with confirmed status
                from ...core.ai.dependency_analyzer import DependencyAnalyzer
                analyzer = DependencyAnalyzer()

                # Update status for all dependencies based on confirmation
                confirmed_ids = {(r.get('source_param'), r.get('target_param')) for r in confirmed_rules}
                for dep in dependencies:
                    key = (dep.get('source_param'), dep.get('target_param'))
                    if key in confirmed_ids:
                        dep['status'] = 'confirmed'
                    else:
                        dep['status'] = 'rejected'

                # Regenerate the file
                analyzer.generate_markdown(dependencies, Path(output_path))

            QMessageBox.information(
                win,
                "规则已应用",
                f"已成功应用 {len(confirmed_rules)} 条确认的依赖规则。\n"
                f"已更新 {Path(output_path).name} 文件标记确认状态。"
            )

            if output_path and Path(output_path).exists():
                reply = QMessageBox.question(
                    win,
                    "查看完整报告",
                    f"分析报告已生成并包含详细原因建议。\n\n是否打开 {Path(output_path).name} 查阅原始报告？",
                    QMessageBox.Yes | QMessageBox.No,
                    QMessageBox.No
                )

                if reply == QMessageBox.Yes:
                    QDesktopServices.openUrl(QUrl.fromLocalFile(str(output_path)))

    def _on_dependency_analysis_error(self, error: str):
        """Handle dependency analysis error."""
        win = self.win
        win.statusBar().showMessage("依赖分析失败", 3000)
        QMessageBox.critical(
            win,
            "分析失败",
            f"依赖分析过程中出错：\n\n{error}"
        )

    def _validate_cross_module_dependencies(self):
        """Validate project against confirmed dependency rules."""
        win = self.win
        if not win.current_project:
            QMessageBox.warning(
                win,
                "需要项目",
                "请先打开一个包含多个模块的项目。"
            )
            return

        from ...core.rules.cross_module_validator import CrossModuleValidator

        # Find dependencies.md
        project_dir = Path(win.current_project.path).parent if win.current_project.path else Path.cwd()
        dep_file = project_dir / "dependencies.md"

        if not dep_file.exists():
            QMessageBox.warning(
                win,
                "规则文件未找到",
                f"未找到依赖规则文件:\n{dep_file}\n\n"
                "请先执行 '分析跨模块依赖' 生成规则文件，\n"
                "然后在文件中确认规则（将 [ ] 改为 [x]）。"
            )
            return

        # Load and validate
        validator = CrossModuleValidator()
        rule_count = validator.load_rules_from_markdown(dep_file)

        if rule_count == 0:
            QMessageBox.information(
                win,
                "无确认的规则",
                f"文件 {dep_file.name} 中没有已确认的规则。\n\n"
                "请编辑该文件，将要启用的规则状态从 [ ] 改为 [x]。"
            )
            return

        # Validate project
        result = validator.validate_project(win.current_project)

        # Show results
        if result.is_valid:
            QMessageBox.information(
                win,
                "验证通过 ✅",
                f"跨模块依赖验证通过！\n\n"
                f"已检查 {rule_count} 条规则，未发现违规。"
            )
        else:
            # Build error message
            errors = [m for m in result.messages if m.severity == 'error']
            warnings = [m for m in result.messages if m.severity == 'warning']

            error_text = "\n\n".join([
                f"❌ {e.message}\n   建议: {e.suggested_fix}" for e in errors[:5]
            ])

            if len(errors) > 5:
                error_text += f"\n\n...还有 {len(errors) - 5} 个错误"

            QMessageBox.critical(
                win,
                "验证失败 ❌",
                f"发现 {len(errors)} 个错误, {len(warnings)} 个警告:\n\n"
                f"{error_text}"
            )
