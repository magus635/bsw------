"""Validation controller — extracted from DaVinciMainWindow (P2-6, phase 7).

Owns configuration validation (single-module and project-wide) with results
shown in the Problems dock, and loading of custom validation rule files. Holds
a back-reference to the main window (``self.win``) for shared state
(current_project, config_manager, problems_view/problems_dock,
validation_status_label, statusbar) and Qt parenting.
"""
from pathlib import Path

from PySide6.QtWidgets import QFileDialog, QMessageBox


class ValidationController:
    """Configuration validation and custom-rule loading for the main window."""

    def __init__(self, win):
        self.win = win

    def validate_configuration(self):
        """Validate all modules in the project and show results in the Problems View."""
        win = self.win
        from ...core.validation_engine import ValidationResult, ValidationEngine
        all_results = ValidationResult()

        if not win.current_project:
            # Single-module mode: validate the active config_manager directly
            if win.config_manager and win.config_manager.configuration and win.config_manager.module_def:
                engine = ValidationEngine(
                    win.config_manager.module_def,
                    win.config_manager.configuration,
                )
                engine.register_default_rules()
                all_results = engine.validate()
            win.problems_view.set_messages(all_results.messages)
            win.problems_dock.show()
            win.problems_dock.raise_()
            if all_results.is_valid:
                win.statusBar().showMessage("✅ Validation complete: No errors found.", 5000)
                win.validation_status_label.setText("✅ Valid")
                win.validation_status_label.setStyleSheet("QLabel { color: green; padding: 2px 10px; }")
            else:
                win.statusBar().showMessage(
                    f"❌ Validation: {all_results.error_count} errors, {all_results.warning_count} warnings.", 5000
                )
                win.validation_status_label.setText(f"❌ {all_results.error_count} Errors")
                win.validation_status_label.setStyleSheet("QLabel { color: red; padding: 2px 10px; }")
            return

        # 1. Run validation for each module
        for module_name, manager in win.current_project.module_managers.items():
            if manager.configuration and manager.module_def:
                from ...core.validation_engine import ValidationEngine
                engine = ValidationEngine(manager.module_def, manager.configuration, win.current_project)
                engine.register_default_rules()

                # Execute validation
                module_result = engine.validate()
                all_results.merge(module_result)

        # 2. Cross-module AI rules are already merged if rules handle them.

        # 3. Update Problems View
        win.problems_view.set_messages(all_results.messages)
        win.problems_dock.show()
        win.problems_dock.raise_()

        # 4. Update status bar/icons
        if all_results.is_valid:
            win.statusBar().showMessage(f"✅ Validation complete: No errors found in {len(win.current_project.module_managers)} modules.", 5000)
            win.validation_status_label.setText("✅ Valid")
            win.validation_status_label.setStyleSheet("QLabel { color: green; padding: 2px 10px; }")
        else:
            win.statusBar().showMessage(f"❌ Validation complete: Found {all_results.error_count} errors, {all_results.warning_count} warnings.", 5000)
            win.validation_status_label.setText(f"❌ {all_results.error_count} Errors")
            win.validation_status_label.setStyleSheet("QLabel { color: red; padding: 2px 10px; }")

    def load_custom_rules(self):
        """Load custom validation rules from file."""
        win = self.win
        if not win.config_manager:
            return

        file_path, _ = QFileDialog.getOpenFileName(
            win,
            "Load Custom Rules",
            str(Path.home()),
            "Custom Rules (*.json *.py);;JSON Files (*.json);;Python Scripts (*.py);;All Files (*)"
        )

        if not file_path:
            return

        try:
            win.config_manager.add_custom_rule_file(Path(file_path))
            win.statusbar.showMessage(f"Loaded custom rules from {Path(file_path).name}", 3000)

            # Trigger validation to see effect
            self.validate_configuration()

        except Exception as e:
            QMessageBox.critical(
                win,
                "Load Rules Error",
                f"Failed to load custom rules:\n{str(e)}"
            )
