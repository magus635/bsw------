"""Wizard controller — extracted from DaVinciMainWindow (P2-6, phase 2).

Owns the launch + completion handling for every configuration wizard
(quick-config, batch-create, hardware-mapping, template, import). Holds a
back-reference to the main window (``self.win``) for shared state
(config_manager, module_def, tree_view, current_project, undo_stack, statusbar)
and Qt parenting.
"""
from PySide6.QtCore import Qt


class WizardController:
    """Groups all wizard launch/completion behaviour for the main window."""

    def __init__(self, win):
        self.win = win

    def launch_quick_config_wizard(self):
        """Launch the quick configuration wizard."""
        win = self.win
        if not win.config_manager or not win.module_def:
            return

        from ..wizards.quick_config_wizard import QuickConfigWizard

        # Determine parent context from tree selection
        parent_instance = None
        selected = win.tree_view.selectedItems()
        if selected:
            data = selected[0].data(0, Qt.UserRole)
            if isinstance(data, dict):
                item_type = data.get("type")
                if item_type == "VALUE":
                    parent_instance = data.get("instance")
                elif item_type in ["DEF", "ADD_PROMPT"]:
                    parent_instance = data.get("parent_instance")

        wizard = QuickConfigWizard(win.module_def, win.config_manager, parent_instance, win)
        wizard.wizard_completed.connect(self._on_wizard_completed)
        wizard.exec()

    def _on_wizard_completed(self, data: dict):
        """Handle wizard completion."""
        win = self.win
        # Refresh tree view to show new instance
        win.tree_view.refresh()

        # Select the newly created instance
        instance = data.get("instance")
        if instance:
            win.tree_view._select_instance(instance)

        # Handle multiple instances (from batch create)
        instances = data.get("instances")
        if instances and len(instances) > 0:
            win.tree_view._select_instance(instances[0])
            win.statusbar.showMessage(
                f"Created {len(instances)} instances successfully", 3000
            )
        else:
            win.statusbar.showMessage("Configuration created successfully", 3000)

    def launch_batch_create_wizard(self):
        """Launch the batch create wizard."""
        win = self.win
        if not win.config_manager or not win.module_def:
            return

        from ..wizards.batch_create_wizard import BatchCreateWizard

        # Determine parent context from tree selection
        parent_instance = self._get_selected_parent_instance()

        wizard = BatchCreateWizard(
            win.module_def, win.config_manager, parent_instance, win
        )
        wizard.wizard_completed.connect(self._on_wizard_completed)
        wizard.exec()

    def launch_hardware_mapping_wizard(self):
        """Launch the hardware mapping wizard."""
        win = self.win
        from ..wizards.hardware_mapping_wizard import HardwareMappingWizard
        from pathlib import Path

        project_path = None
        if win.current_project:
            project_path = Path(win.current_project.path)

        wizard = HardwareMappingWizard(
            config_manager=win.config_manager,
            project_path=project_path,
            undo_stack=win.undo_stack,
            parent=win
        )
        wizard.wizard_completed.connect(self._on_hardware_wizard_completed)
        wizard.exec()

    def _on_hardware_wizard_completed(self, data: dict):
        """Handle hardware mapping wizard completion."""
        win = self.win
        chip = data.get("chip", "Unknown")
        actions = data.get("actions_count", 0)
        applied = data.get("applied_count", 0)
        skipped = data.get("skipped_count", 0)
        failed = data.get("failed_count", 0)

        win.tree_view.refresh()
        msg = f"Hardware mapping for {chip}: {applied}/{actions} actions applied"
        if skipped:
            msg += f", {skipped} skipped (not yet implemented)"
        if failed:
            msg += f", {failed} failed"
        win.statusbar.showMessage(msg, 5000)

    def launch_template_wizard(self):
        """Launch the template wizard."""
        win = self.win
        if not win.config_manager:
            return

        from ..wizards.template_wizard import TemplateWizard
        from ...core.template_manager import TemplateManager

        # Get current module filter
        module_filter = None
        if win.module_def:
            module_filter = win.module_def.short_name

        # Determine parent context
        parent_instance = self._get_selected_parent_instance()

        template_manager = TemplateManager()

        wizard = TemplateWizard(
            config_manager=win.config_manager,
            template_manager=template_manager,
            module_filter=module_filter,
            parent_instance=parent_instance,
            parent=win
        )
        wizard.wizard_completed.connect(self._on_wizard_completed)
        wizard.exec()

    def launch_import_wizard(self):
        """Launch the import wizard."""
        win = self.win
        if not win.config_manager:
            return

        from ..wizards.import_wizard import ImportWizard

        parent_instance = self._get_selected_parent_instance()

        wizard = ImportWizard(
            config_manager=win.config_manager,
            parent_instance=parent_instance,
            parent=win
        )
        wizard.wizard_completed.connect(self._on_import_wizard_completed)
        wizard.exec()

    def _on_import_wizard_completed(self, data: dict):
        """Handle import wizard completion."""
        win = self.win
        success = data.get("success", False)
        imported = data.get("records_imported", 0)
        skipped = data.get("records_skipped", 0)

        win.tree_view.refresh()

        if success:
            win.statusbar.showMessage(
                f"Import complete: {imported} records imported, {skipped} skipped", 5000
            )
        else:
            win.statusbar.showMessage("Import failed - see wizard for details", 5000)

    def _get_selected_parent_instance(self):
        """Get parent instance from tree selection for wizard context."""
        parent_instance = None
        selected = self.win.tree_view.selectedItems()
        if selected:
            data = selected[0].data(0, Qt.UserRole)
            if isinstance(data, dict):
                item_type = data.get("type")
                if item_type == "VALUE":
                    parent_instance = data.get("instance")
                elif item_type in ["DEF", "ADD_PROMPT"]:
                    parent_instance = data.get("parent_instance")
        return parent_instance
