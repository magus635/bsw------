"""Project controller — extracted from DaVinciMainWindow (P2-6, phase 8).

Owns project lifecycle (new / open / load / save), project properties, variant
management, module add, EB import, recommended-value loading, single-config
save, session restore, and the recent-files menu. Holds a back-reference to the
main window (``self.win``) for shared state (current_project, workspace_manager,
config_manager, tree_view, settings, statusbar, actions, chip_constraint_service)
and Qt parenting.
"""
from pathlib import Path

from PySide6.QtCore import Qt
from PySide6.QtGui import QAction
from PySide6.QtWidgets import (
    QFileDialog, QMessageBox, QInputDialog, QLineEdit, QDialog,
)

import logging

logger = logging.getLogger(__name__)


class ProjectController:
    """Project I/O, session, and recent-files behaviour for the main window."""

    def __init__(self, win):
        self.win = win

    def new_project(self):
        """Create a new project"""
        from PySide6.QtWidgets import QInputDialog, QComboBox, QDialog, QVBoxLayout, QDialogButtonBox, QFormLayout
        from ...core.config_manager import ProjectType, ConfigLoader
        
        # Project type selection dialog
        dialog = QDialog(self.win)
        dialog.setWindowTitle("New Project")
        layout = QVBoxLayout(dialog)
        
        form = QFormLayout()
        
        name_edit = QLineEdit()
        form.addRow("Project Name:", name_edit)
        
        type_combo = QComboBox()
        type_combo.addItem("Vector DaVinci", ProjectType.VECTOR)
        type_combo.addItem("EB Tresos", ProjectType.EB_TRESOS)
        form.addRow("Project Type:", type_combo)
        
        layout.addLayout(form)
        
        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(dialog.accept)
        buttons.rejected.connect(dialog.reject)
        layout.addWidget(buttons)
        
        if dialog.exec() != QDialog.Accepted:
            return
            
        name = name_edit.text().strip()
        project_type = type_combo.currentData()
        
        if not name:
            QMessageBox.warning(self.win, "Error", "Project name cannot be empty")
            return
        
        # Unified folder selection for both project types
        folder_path = QFileDialog.getExistingDirectory(
            self.win,
            f"Select {project_type.value} Project Folder",
            str(Path.home()),
            QFileDialog.ShowDirsOnly
        )
        if not folder_path:
            return
        
        folder = Path(folder_path)
        project_path = folder / f"{name}.dpa"
        
        # Check if folder has existing content (warn user)
        existing_items = list(folder.iterdir()) if folder.exists() else []
        # Filter out hidden files/folders
        visible_items = [f for f in existing_items if not f.name.startswith('.')]
        
        if visible_items:
            reply = QMessageBox.question(
                self.win,
                "Non-empty Folder",
                f"The folder contains {len(visible_items)} item(s).\n\n"
                "Do you want to create the project here anyway?\n"
                "(Existing files will not be deleted)",
                QMessageBox.Yes | QMessageBox.No,
                QMessageBox.No
            )
            if reply != QMessageBox.Yes:
                return
        
        # Create .tresos marker folder for EB projects
        if project_type == ProjectType.EB_TRESOS:
            tresos_marker = folder / ".tresos"
            tresos_marker.mkdir(exist_ok=True)
            
        self.win.current_project = self.win.workspace_manager.create_project(name, project_path)
        self.win.current_project.project_type = project_type
        self.win.current_project.def_search_paths = ConfigLoader.get_def_search_paths(project_path.parent)
        self.win.current_project_file = project_path
        self.win.tree_view.set_project(self.win.current_project)
        
        self.win.save_project_action.setEnabled(True)
        self.win.add_module_action.setEnabled(True)
        self.win.manage_variants_action.setEnabled(True)
        self.win.manage_variants_btn.setEnabled(True)
        self.win.project_properties_action.setEnabled(True)
        
        # Update variant selector
        self.win._update_variant_selector()
        
        # Update mode label
        self.win.mode_label.setText(f"Project: {project_type.value}")
        
        self.win.statusbar.showMessage(f"Created {project_type.value} project: {name}", 3000)
        
    def open_project(self):
        """Open an existing project (Vector .dpa or EB folder)"""
        from ...core.config_manager import ProjectTypeDetector, ConfigLoader, ProjectType
        
        # Allow selecting a file (.dpa) OR a folder (for EB projects)
        file_path, _ = QFileDialog.getOpenFileName(
            self.win,
            "Open Project (.dpa) or select a folder",
            str(Path.home()),
            "DaVinci Project (*.dpa);;All Files (*)"
        )
        
        # If user cancelled file dialog, try folder dialog
        if not file_path:
            folder_path = QFileDialog.getExistingDirectory(
                self.win,
                "Open Project Folder (EB Tresos)",
                str(Path.home()),
                QFileDialog.ShowDirsOnly
            )
            if not folder_path:
                return
            project_path = Path(folder_path)
        else:
            project_path = Path(file_path)
            
        self._load_project_at_path(project_path)

    def _load_project_at_path(self, path: Path):
        """Unified logic to load a project from a path (file or folder)"""
        from ...core.config_manager import ProjectTypeDetector, ConfigLoader, ProjectType
        
        if not path.exists():
            return

        if path.is_file():
            project_root = path.parent
            file_path = str(path)
        else:
            project_root = path
            file_path = None
            
        # Detect project type
        project_type = ProjectTypeDetector.detect(project_root)
        
        if project_type == ProjectType.UNKNOWN:
            QMessageBox.warning(
                self.win,
                "Unknown Project Type",
                f"Could not detect project type for:\n{project_root}\n\n"
                "Expected: .dpa file (Vector) or .tresos/.project marker (EB)"
            )
            return
            
        self.win.statusbar.showMessage(f"Detected {project_type.value} project, loading...")
        
        # Get search paths for definitions
        def_search_paths = ConfigLoader.get_def_search_paths(project_root)
        
        try:
            if file_path or path.is_file():
                # Saved .dpa project file — load directly (works for both Vector and EB-typed saves)
                # Use existing .dpa loading logic
                load_path = Path(file_path) if file_path else path
                self.win.current_project, failed_modules = self.win.workspace_manager.load_project(load_path)
                self.win.current_project_file = load_path
            else:
                # EB project: auto-import all defines + EPC configs
                from ...core.config_manager import EpcFileScanner

                # Check for available chips
                chips = EpcFileScanner.detect_available_chips(project_root)
                chip_name = None

                if len(chips) > 1:
                    # Let user select which chip variant
                    chip_name, ok = QInputDialog.getItem(
                        self.win, "Select Chip Variant",
                        "Multiple chip variants detected.\nSelect one:",
                        chips, 0, False
                    )
                    if not ok:
                        return
                elif len(chips) == 1:
                    chip_name = chips[0]

                # Ask user where to save the imported project
                target_dir_str = QFileDialog.getExistingDirectory(
                    self.win,
                    "Select Target Directory for Imported Project",
                    str(Path.home()),
                    QFileDialog.ShowDirsOnly
                )
                if not target_dir_str:
                    return
                target_dir = Path(target_dir_str) / project_root.name
                target_dir.mkdir(parents=True, exist_ok=True)

                # Batch import with progress
                self.win.statusbar.showMessage("Importing EB project...")
                from PySide6.QtWidgets import QApplication
                QApplication.processEvents()

                self.win.current_project, loaded_modules, failed_modules = \
                    self.win.workspace_manager.import_eb_project(
                        project_root, chip_name=chip_name,
                        target_dir=target_dir,
                        progress_callback=lambda msg: self.win.statusbar.showMessage(msg)
                    )
                self.win.current_project_file = self.win.current_project.path

                # Store search paths
                self.win.current_project.def_search_paths = def_search_paths

                # Show summary
                summary = (
                    f"EB Tresos project imported.\n\n"
                    f"Source: {project_root}\n"
                    f"Target: {target_dir}\n\n"
                    f"Loaded: {len(loaded_modules)} module(s)\n"
                    f"Failed: {len(failed_modules)} module(s)"
                )
                if chip_name:
                    summary += f"\nChip: {chip_name}"
                if loaded_modules:
                    summary += f"\n\nModules: {', '.join(sorted(loaded_modules))}"

                QMessageBox.information(self.win, "EB Project Imported", summary)
            
            self.win.tree_view.set_project(self.win.current_project)
            
            # Set project type on loaded project
            self.win.current_project.project_type = project_type
            
            # Enable project actions
            self.win.save_project_action.setEnabled(True)
            self.win.project_properties_action.setEnabled(True)
            self.win.manage_variants_action.setEnabled(True)
            self.win.manage_variants_btn.setEnabled(True)
            self.win.add_module_action.setEnabled(True)
            
            # Update variant selector
            self.win._update_variant_selector()
            
            # Update mode label
            self.win.mode_label.setText(f"Project: {project_type.value}")
            
            # Update menu/toolbar states for project mode
            self.win._update_mode_actions()
            
            status_msg = f"Loaded project: {self.win.current_project.name} ({project_type.value})"
            
            # Show warning if some modules failed to load
            if failed_modules:
                error_details = "\n".join([f"• {name}: {error}" for name, error in failed_modules])
                QMessageBox.warning(
                    self.win,
                    "Project Loaded with Errors",
                    f"Project loaded, but {len(failed_modules)} module(s) failed:\n\n{error_details}\n\n"
                    f"Successfully loaded: {len(self.win.current_project.module_managers)} module(s)"
                )
                status_msg += f" ({len(failed_modules)} errors)"
            
            self.win.statusbar.showMessage(status_msg, 5000)
            
            # Auto-select first module
            self.win.tree_view.select_first_module()
            
            # Save as last loaded project for auto-loading next time
            self.win.settings.setValue("last_project_path", str(self.win.current_project_file))

            # Add to recent files
            self._add_to_recent_files(str(self.win.current_project_file))
            
            # Initialize chip constraint service with project path
            if self.win.current_project:
                project_dir = self.win.current_project_file.parent if self.win.current_project_file else project_root
                self.win.chip_constraint_service.set_project_path(project_dir)
                
                # Read current chip from project settings or ResourceSubderivative parameter
                initial_chip = self.win.current_project.selected_chip
                if not initial_chip:
                    # Try to read from ResourceSubderivative parameter
                    initial_chip = self.win._get_resource_subderivative()
                
                if initial_chip:
                    self.win.chip_constraint_service.set_chip(initial_chip)
                    logger.info(f"Chip constraint service initialized with chip: {initial_chip}")
                
                # Update window title after project load
                self.win._update_window_title()
            
        except Exception as e:
            QMessageBox.critical(self.win, "Error", f"Failed to load project:\n{str(e)}")
            
    def save_project(self):
        """Save current project and all modified modules"""
        if not self.win.current_project:
            return

        try:
            # For EB-imported projects: first save needs a separate working directory
            # The original EB project directory should remain untouched
            if self.win.current_project.eb_source_root:
                project_dir = self.win.current_project.path.parent
                eb_root = self.win.current_project.eb_source_root

                # Check if project path is still inside the EB source root (not yet saved elsewhere)
                try:
                    project_dir.relative_to(eb_root)
                    needs_save_as = True
                except ValueError:
                    needs_save_as = False

                if needs_save_as:
                    # Prompt user to select a working directory
                    save_dir = QFileDialog.getExistingDirectory(
                        self.win, "Select Save Directory for Project",
                        str(Path.home() / "Desktop"),
                        QFileDialog.ShowDirsOnly
                    )
                    if not save_dir:
                        return

                    save_dir = Path(save_dir)
                    new_dpa_path = save_dir / f"{self.win.current_project.name}.dpa"

                    # Update project path to the new location
                    self.win.current_project.path = new_dpa_path
                    self.win.current_project_file = new_dpa_path

                    # Update window title
                    self.win._update_window_title()

            # Count modified modules for status message
            modified_count = sum(
                1 for manager in self.win.current_project.module_managers.values()
                if manager.configuration.is_modified
            )

            # Save project metadata file (.dpa) and all module configurations
            # workspace_manager.save_project() handles saving to ConfigValue/ directory
            self.win.workspace_manager.save_project()

            # Show result
            if modified_count > 0:
                self.win.statusbar.showMessage(f"Project saved: {modified_count} module(s) updated", 3000)
            else:
                self.win.statusbar.showMessage(f"Project saved (no changes)", 3000)

        except Exception as e:
            QMessageBox.critical(self.win, "Save Error", f"Failed to save project:\n{str(e)}")
    
    def show_project_properties(self):
        """Show project properties dialog"""
        if not self.win.current_project:
            return
        
        from ..dialogs.project_properties_dialog import ProjectPropertiesDialog
        
        dialog = ProjectPropertiesDialog(self.win.current_project, self.win)
        if dialog.exec():
            # Update project with new data
            data = dialog.get_data()
            self.win.current_project.name = data['name']
            self.win.current_project.version = data['version']
            self.win.current_project.author = data['author']
            self.win.current_project.description = data['description']
            self.win.current_project.selected_chip = data.get('selected_chip')
            
            # Update tree header
            self.win.tree_view.setHeaderLabel(f"Project: {self.win.current_project.name}")
            
            self.win.statusbar.showMessage("Project properties updated", 3000)

    
    def manage_variants(self):
        """Show improved dialog to manage project variants"""
        if not self.win.current_project:
            return
            
        from ..widgets.variant_management_dialog import VariantManagementDialog
        
        dialog = VariantManagementDialog(self.win.current_project, self.win)
        if dialog.exec() == QDialog.Accepted:
            # Update UI
            self.win._update_variant_selector()
            self.win.statusbar.showMessage(f"Variants updated: {len(self.win.current_project.variants)} defined", 3000)
    
    def add_module_to_project(self):
        """Add a module to the current project"""
        if not self.win.current_project:
            return
            
        file_path, _ = QFileDialog.getOpenFileName(
            self.win,
            "Select Module DEF File",
            str(Path.home()),
            "All Supported Files (*.arxml *.xdm);;ARXML Files (*.arxml);;EB Tresos Files (*.xdm);;All Files (*)"
        )
        
        if not file_path:
            return
            
        try:
            # Ensure parser has latest chip constraints before parsing
            constraints = self.win.chip_constraint_service.get_all_constraints()
            if constraints:
                self.win.def_parser._resolver.set_constraints(constraints)
            module_def = self.win.def_parser.parse_module_def_file(Path(file_path))
            self.win.current_project.add_module(module_def, Path(file_path))
            self.win.tree_view.set_project(self.win.current_project)
            self.win.statusbar.showMessage(f"Added module: {module_def.short_name}", 3000)
        except Exception as e:
            QMessageBox.critical(self.win, "Error", f"Failed to add module:\n{str(e)}")

    def import_value_file(self):
        """Import an EB value file (.epc/.arxml/.xdm), replacing the current
        module's configuration — the counterpart of Export EPC Files."""
        from datetime import datetime

        win = self.win
        if not win.config_manager or not win.config_manager.module_def:
            QMessageBox.warning(win, "Import Value File", "Please select a module first.")
            return

        module_name = win.config_manager.module_def.short_name

        file_path, _ = QFileDialog.getOpenFileName(
            win, f"Import Value File for {module_name}",
            str(win.current_project.path.parent) if win.current_project and win.current_project.path else str(Path.home()),
            "Value Files (*.epc *.arxml *.xdm);;EPC Files (*.epc);;ARXML Files (*.arxml);;All Files (*)"
        )
        if not file_path:
            return
        file_path = Path(file_path)

        # Verify the file actually contains this module (standard value files;
        # XDM configs are checked by the parser during load instead)
        from ...core.config_manager import EpcFileScanner
        contained = EpcFileScanner.list_module_names(file_path)
        if contained and module_name not in contained:
            QMessageBox.critical(
                win, "Import Value File",
                f"The file contains no configuration for module '{module_name}'.\n\n"
                f"Modules found: {', '.join(contained)}"
            )
            return

        reply = QMessageBox.question(
            win, "Import Value File",
            f"This will REPLACE the current configuration of '{module_name}' "
            f"with the contents of:\n{file_path.name}\n\n"
            "Unsaved changes to this module and the undo history will be lost. Continue?",
            QMessageBox.Yes | QMessageBox.No, QMessageBox.No
        )
        if reply != QMessageBox.Yes:
            return

        try:
            win.config_manager.load_configuration(file_path)
        except Exception as e:
            logger.error("Value file import failed: %s", e, exc_info=True)
            QMessageBox.critical(win, "Import Value File", f"Import failed:\n{e}")
            return

        # The old configuration object is gone — stale undo entries would
        # reference dangling containers.
        win.undo_stack.clear()

        # Record provenance and re-resolve cross-module references
        if win.current_project:
            source_epc = str(file_path)
            eb_root = win.current_project.eb_source_root
            if eb_root:
                try:
                    source_epc = str(file_path.relative_to(eb_root))
                except ValueError:
                    pass
            win.current_project.module_provenance[module_name] = {
                "origin": "eb-import",
                "source_epc": source_epc,
                "imported_at": datetime.now().isoformat(),
            }
            try:
                win.current_project.resolve_all_references()
                win.current_project.build_reverse_reference_index()
            except Exception as e:
                logger.warning("Reference resolution after value import failed: %s", e)
            win.tree_view.set_project(win.current_project)

        win.config_panel.clear()

        # Surface unknown-parameter warnings from the import
        unknown_count = 0
        def _count_unknown(containers):
            nonlocal unknown_count
            for c in containers:
                unknown_count += len(getattr(c, 'unknown_parameters', None) or {})
                _count_unknown(c.sub_containers)
        _count_unknown(win.config_manager.configuration.containers)

        summary = f"Imported {file_path.name} into module '{module_name}'."
        if unknown_count:
            summary += (f"\n\n{unknown_count} parameter(s) are not in the loaded definition; "
                        "they are preserved and marked with ⚠️ in the tree.")
        QMessageBox.information(win, "Import Value File", summary)
        win.statusbar.showMessage(f"Imported value file for {module_name}", 3000)

    def export_epc_files(self):
        """Export module configurations as EB Tresos-compatible .epc files"""
        if not self.win.workspace_manager.current_project:
            QMessageBox.warning(self.win, "Export EPC", "No project loaded.")
            return

        output_dir = QFileDialog.getExistingDirectory(
            self.win, "Select EPC Output Directory",
            str(Path.home()),
            QFileDialog.ShowDirsOnly
        )
        if not output_dir:
            return

        try:
            written = self.win.workspace_manager.export_epc(Path(output_dir))
        except Exception as e:
            logger.error("EPC export failed: %s", e, exc_info=True)
            QMessageBox.critical(self.win, "Export EPC", f"Export failed:\n{e}")
            return

        QMessageBox.information(
            self.win, "Export EPC",
            f"Exported {len(written)} EPC file(s) to:\n{output_dir}"
        )

    def import_eb_project(self):
        """Import an EB Tresos project by selecting its root directory"""
        from ...core.config_manager import EpcFileScanner

        # Select project root directory
        project_root = QFileDialog.getExistingDirectory(
            self.win, "Select EB Tresos Project Root Directory",
            str(Path.home()),
            QFileDialog.ShowDirsOnly
        )
        if not project_root:
            return

        project_root = Path(project_root)

        # Detect available chips
        chips = EpcFileScanner.detect_available_chips(project_root)
        chip_name = None

        if len(chips) > 1:
            chip_name, ok = QInputDialog.getItem(
                self.win, "Select Chip Variant",
                "Multiple chip variants detected.\nSelect one:",
                chips, 0, False
            )
            if not ok:
                return
        elif len(chips) == 1:
            chip_name = chips[0]

        # Import mode: copy (self-contained) vs link (reference original tree)
        mode_labels = [
            "Copy (self-contained — plugins copied into the project, larger but portable)",
            "Link (reference original EB tree — no copy, project depends on the source staying in place)",
        ]
        mode_choice, ok = QInputDialog.getItem(
            self.win, "Import Mode",
            "How should the EB plugin tree be brought into the project?",
            mode_labels, 0, False
        )
        if not ok:
            return
        import_mode = "link" if mode_choice == mode_labels[1] else "copy"

        # Select target directory for the imported project
        target_dir_str = QFileDialog.getExistingDirectory(
            self.win,
            "Select Target Directory for Imported Project",
            str(Path.home()),
            QFileDialog.ShowDirsOnly
        )
        if not target_dir_str:
            return

        # Create a project subdirectory inside the chosen target
        target_dir = Path(target_dir_str) / project_root.name
        target_dir.mkdir(parents=True, exist_ok=True)

        # Show wait cursor and perform import
        from PySide6.QtWidgets import QApplication
        QApplication.setOverrideCursor(Qt.WaitCursor)
        self.win.statusbar.showMessage("Importing EB project...")
        QApplication.processEvents()

        try:
            project, loaded_modules, failed_modules = \
                self.win.workspace_manager.import_eb_project(
                    project_root, chip_name=chip_name,
                    target_dir=target_dir,
                    progress_callback=lambda msg: (
                        self.win.statusbar.showMessage(msg),
                        QApplication.processEvents()
                    ),
                    mode=import_mode
                )

            self.win.current_project = project
            self.win.current_project_file = project.path

            # Set up UI
            self.win.tree_view.set_project(self.win.current_project)

            # Enable project actions
            self.win.save_project_action.setEnabled(True)
            self.win.project_properties_action.setEnabled(True)
            self.win.manage_variants_action.setEnabled(True)
            self.win.manage_variants_btn.setEnabled(True)
            self.win.add_module_action.setEnabled(True)

            # Update variant selector
            self.win._update_variant_selector()

            # Update mode label
            from ...core.config_manager import ProjectType
            self.win.current_project.project_type = ProjectType.EB_TRESOS
            self.win.mode_label.setText(f"Project: EB Tresos")
            self.win._update_mode_actions()

            # Auto-select first module
            self.win.tree_view.select_first_module()

            # Save as last project (record the .dpa file path, not the directory)
            self.win.settings.setValue("last_project_path", str(project.path))
            self._add_to_recent_files(str(project.path))

            # Update window title
            self.win._update_window_title()

            # Show summary
            summary = (
                f"EB Tresos project imported.\n\n"
                f"Source: {project_root}\n"
                f"Target: {target_dir}\n"
                f"Mode: {import_mode}\n\n"
                f"Loaded: {len(loaded_modules)} module(s)\n"
                f"Failed: {len(failed_modules)} module(s)"
            )
            if chip_name:
                summary += f"\nChip: {chip_name}"
            if project.ecu_resources:
                summary += f"\nECU Resources: {len(project.ecu_resources)} properties loaded"
            if loaded_modules:
                summary += f"\n\nModules: {', '.join(sorted(loaded_modules))}"
            if failed_modules:
                summary += f"\n\nFailed:"
                for name, error in failed_modules[:10]:
                    summary += f"\n  {name}: {error}"
                if len(failed_modules) > 10:
                    summary += f"\n  ... and {len(failed_modules) - 10} more"

            QMessageBox.information(self.win, "EB Project Imported", summary)
            self.win.statusbar.showMessage(
                f"Imported: {len(loaded_modules)} modules to {target_dir.name}", 5000
            )

        except Exception as e:
            QMessageBox.critical(self.win, "Import Error", f"Failed to import EB project:\n{str(e)}")
        finally:
            QApplication.restoreOverrideCursor()

    def load_recommended_values(self):
        """Load and apply recommended values from _rec.arxml file"""
        from ...core.config_manager import RecFileScanner
        from PySide6.QtWidgets import (QDialog, QVBoxLayout, QTableWidget, QTableWidgetItem,
                                       QDialogButtonBox, QHeaderView, QCheckBox)
        
        # Need an active configuration
        if not self.win.config_manager:
            QMessageBox.warning(self.win, "No Module Loaded", "Please load a module first.")
            return
        
        # Find rec files
        if self.win.current_project and self.win.current_project.path:
            project_root = self.win.current_project.path.parent
        else:
            project_root = Path.home()
        
        # Let user select rec file
        file_path, _ = QFileDialog.getOpenFileName(
            self.win,
            "Select Recommended Values File",
            str(project_root),
            "Rec Files (*_rec.arxml *.xdm *.epc);;ARXML Files (*.arxml);;EB Tresos Files (*.xdm);;EPC Files (*.epc);;All Files (*)"
        )
        
        if not file_path:
            return
        
        # Load recommended values
        rec_config = self.win.config_manager.load_recommended_values(Path(file_path))
        if not rec_config:
            QMessageBox.warning(self.win, "Load Failed", "Could not parse recommended values file.")
            return
        
        # Get comparison
        comparisons = self.win.config_manager.get_recommended_value_comparison(rec_config)
        
        if not comparisons:
            QMessageBox.information(self.win, "No Values", "No comparable values found in rec file.")
            return
        
        # Show comparison dialog
        dialog = QDialog(self.win)
        dialog.setWindowTitle("Recommended Values Comparison")
        dialog.setMinimumSize(700, 400)
        layout = QVBoxLayout(dialog)
        
        # Table
        table = QTableWidget()
        table.setColumnCount(4)
        table.setHorizontalHeaderLabels(["Parameter", "Current", "Recommended", "Different"])
        table.setRowCount(len(comparisons))
        
        for row, comp in enumerate(comparisons):
            table.setItem(row, 0, QTableWidgetItem(comp['param_path']))
            table.setItem(row, 1, QTableWidgetItem(str(comp['current_value'] or "")))
            table.setItem(row, 2, QTableWidgetItem(str(comp['recommended_value'] or "")))
            table.setItem(row, 3, QTableWidgetItem("Yes" if comp['differs'] else ""))
            
            # Highlight differing rows
            if comp['differs']:
                for col in range(4):
                    table.item(row, col).setBackground(Qt.yellow)
        
        table.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        layout.addWidget(table)
        
        # Checkbox for only_empty option
        only_empty_cb = QCheckBox("Only apply to empty/unset parameters")
        only_empty_cb.setChecked(True)
        layout.addWidget(only_empty_cb)
        
        # Buttons
        buttons = QDialogButtonBox(QDialogButtonBox.Apply | QDialogButtonBox.Cancel)
        buttons.button(QDialogButtonBox.Apply).clicked.connect(dialog.accept)
        buttons.rejected.connect(dialog.reject)
        layout.addWidget(buttons)
        
        if dialog.exec() == QDialog.Accepted:
            only_empty = only_empty_cb.isChecked()
            # Collect the (instance, param_name, value) changes that
            # apply_recommended_values would perform, then push one
            # SetParameterCommand per change inside an undo macro so the whole
            # bulk apply is a single undoable operation.
            changes = []

            def collect(current: EcucContainerValue, recommended: EcucContainerValue):
                for param_name, rec_param_obj in recommended.parameter_values.items():
                    current_param_obj = current.parameter_values.get(param_name)
                    current_value = current_param_obj.value if current_param_obj else None
                    rec_value = rec_param_obj.value
                    should_apply = not only_empty or current_value is None or current_value == ""
                    if should_apply and rec_value is not None:
                        changes.append((current, param_name, rec_value))
                for rec_sub in recommended.sub_containers:
                    current_sub = next(
                        (c for c in current.sub_containers if c.short_name == rec_sub.short_name),
                        None
                    )
                    if current_sub:
                        collect(current_sub, rec_sub)

            for rec_container in rec_config.containers:
                current_container = next(
                    (c for c in self.win.config_manager.configuration.containers
                     if c.short_name == rec_container.short_name),
                    None
                )
                if current_container:
                    collect(current_container, rec_container)

            self.win.undo_stack.beginMacro("Apply Recommended Values")
            for instance, param_name, value in changes:
                self.win.undo_stack.push(
                    SetParameterCommand(self.win.config_manager, instance, param_name, value)
                )
            self.win.undo_stack.endMacro()
            updated = len(changes)
            self.win._has_unsaved_changes = True
            
            # Refresh UI
            if self.win.tree_view.currentItem():
                self.win.tree_view._on_item_clicked(self.win.tree_view.currentItem(), 0)
            
            QMessageBox.information(self.win, "Applied", f"Updated {updated} parameter(s) with recommended values.")
            self.win.statusbar.showMessage(f"Applied {updated} recommended values", 3000)
    
    # File operations
    
    # open_def_file, new_configuration, open_value_file removed - use projects instead
    
    # new_configuration and open_value_file removed - use projects instead
    
    # save_value_file methods removed - use save_project instead
    
    def _save_configuration(self, file_path: Path):
        """Save configuration to file (kept for internal use if needed)"""
        try:
            self.win.statusbar.showMessage("Saving configuration...")
            self.win.config_manager.save_configuration(file_path)
            
            self.win.current_value_file = Path(file_path)
            self.win.value_file_label.setText(f"Config: {Path(file_path).name}")
            self.win.statusbar.showMessage(f"Configuration saved to {file_path.name}", 3000)
            
        except Exception as e:
            QMessageBox.critical(self.win, "Save Error", f"Failed to save configuration:\n{str(e)}")
            self.win.statusbar.showMessage("Save failed", 3000)
            self.win.statusbar.showMessage(f"Saved to {file_path}", 3000)
            
            # Clear unsaved changes flag
            self.win._has_unsaved_changes = False
            
            # Save to recent files
            self.win.settings.setValue("last_value_file", str(file_path))
            
        except Exception as e:
            QMessageBox.critical(self.win, "Error", f"Failed to save configuration:\n{str(e)}")
            self.win.statusbar.showMessage("Save failed", 3000)
            

    def _load_last_session(self):
        """Load last opened DEF file"""
        last_def = self.win.settings.value("last_def_file")
        if last_def and Path(last_def).exists():
            # Auto-load on startup?
            pass  # For now, let user manually open

    def _update_recent_files_menu(self):
        """Update recent files menu with current list"""
        self.win.recent_files_menu.clear()

        # Get recent files from settings
        recent_files = self.win.settings.value("recent_files", [])

        # Handle case where settings returns a string instead of list
        if isinstance(recent_files, str):
            recent_files = [recent_files] if recent_files else []

        if not recent_files:
            no_files_action = QAction("(No recent files)", self.win)
            no_files_action.setEnabled(False)
            self.win.recent_files_menu.addAction(no_files_action)
            return

        # Add recent files to menu (limit to max_recent_files)
        for file_path in recent_files[:self.win.max_recent_files]:
            if Path(file_path).exists():
                action = QAction(file_path, self.win)
                action.triggered.connect(lambda checked, path=file_path: self._open_recent_file(path))
                self.win.recent_files_menu.addAction(action)

        # Add separator and clear action if there are files
        if self.win.recent_files_menu.actions():
            self.win.recent_files_menu.addSeparator()
            clear_action = QAction("Clear Recent Files", self.win)
            clear_action.triggered.connect(self._clear_recent_files)
            self.win.recent_files_menu.addAction(clear_action)

    def _open_recent_file(self, file_path: str):
        """Open a file from recent files menu"""
        path = Path(file_path)
        if not path.exists():
            QMessageBox.warning(self.win, "File Not Found", f"The file no longer exists:\n{file_path}")
            self._remove_from_recent_files(file_path)
            return

        # Determine file type and open accordingly
        if path.suffix.lower() == '.dpa':
            self._load_project_at_path(path)
        elif path.suffix.lower() == '.epc':
            # EPC file: try to load as project from parent directory structure
            # Look for EB project root (parent of Config/)
            candidate = path.parent  # output/
            if candidate.name == 'output':
                candidate = candidate.parent  # chip_name/
                candidate = candidate.parent  # Config/
                if candidate.name == 'Config':
                    candidate = candidate.parent  # project root
                    self._load_project_at_path(candidate)
                    return
            # Fallback: treat as arxml
            self._load_def_file_at_path(path)
        elif path.suffix.lower() in ('.arxml', '.xdm'):
            self._load_def_file_at_path(path)

    def _load_def_file_at_path(self, path: Path):
        """Load a DEF file from a specific path (used by recent files)"""
        # Check if project is active
        if self.win.current_project:
            reply = QMessageBox.question(
                self.win,
                "Close Project?",
                "Opening a DEF file will close the current project.\n\n"
                "Do you want to:\n"
                "• Close project and open DEF file (single-module mode)\n"
                "• Cancel and use 'Add Module to Project' instead",
                QMessageBox.Ok | QMessageBox.Cancel,
                QMessageBox.Cancel
            )

            if reply == QMessageBox.Cancel:
                return

            # User chose to close project
            self.win.current_project = None
            self.win.current_project_file = None
            self.win.tree_view.clear()
            self.win.save_project_action.setEnabled(False)
            self.win.add_module_action.setEnabled(False)

        try:
            # Show loading cursor
            from PySide6.QtWidgets import QApplication
            from PySide6.QtCore import Qt as QtCore_Qt
            QApplication.setOverrideCursor(QtCore_Qt.WaitCursor)
            self.win.statusbar.showMessage("Loading DEF file...")

            # Parse DEF file (ensure parser has latest chip constraints)
            constraints = self.win.chip_constraint_service.get_all_constraints()
            if constraints:
                self.win.def_parser._resolver.set_constraints(constraints)
            self.win.module_def = self.win.def_parser.parse_module_def_file(path)
            self.win.current_def_file = path

            # Create configuration manager
            self.win.config_manager = ConfigurationManager(self.win.module_def)

            # Update UI
            self.win.tree_view.set_module_def(self.win.module_def, self.win.config_manager)
            self.win.def_file_label.setText(f"DEF: {self.win.module_def.short_name}")

            # Enable actions
            self.win.new_config_action.setEnabled(True)
            self.win.open_value_action.setEnabled(True)

            self.win.statusbar.showMessage(f"Loaded DEF: {self.win.module_def.short_name}", 5000)

            # Update mode label for single-module mode
            self.win.mode_label.setText(f"Module: {self.win.module_def.short_name}")

            # Update menu/toolbar states
            self.win._update_mode_actions()

            # Save to settings
            self.win.settings.setValue("last_def_file", str(path))

            # Add to recent files
            self._add_to_recent_files(str(path))

        except Exception as e:
            QMessageBox.critical(self.win, "Error", f"Failed to load DEF file:\n{e}")
            self.win.statusbar.showMessage("Failed to load DEF file", 5000)
        finally:
            from PySide6.QtWidgets import QApplication
            QApplication.restoreOverrideCursor()

    def _add_to_recent_files(self, file_path: str):
        """Add a file to recent files list"""
        recent_files = self.win.settings.value("recent_files", [])

        if isinstance(recent_files, str):
            recent_files = [recent_files] if recent_files else []

        # Remove if already exists (to move to top)
        if file_path in recent_files:
            recent_files.remove(file_path)

        # Add to beginning
        recent_files.insert(0, file_path)

        # Limit to max_recent_files
        recent_files = recent_files[:self.win.max_recent_files]

        # Save and update menu
        self.win.settings.setValue("recent_files", recent_files)
        self._update_recent_files_menu()

    def _remove_from_recent_files(self, file_path: str):
        """Remove a file from recent files list"""
        recent_files = self.win.settings.value("recent_files", [])

        if isinstance(recent_files, str):
            recent_files = [recent_files] if recent_files else []

        if file_path in recent_files:
            recent_files.remove(file_path)
            self.win.settings.setValue("recent_files", recent_files)
            self._update_recent_files_menu()

    def _clear_recent_files(self):
        """Clear all recent files"""
        self.win.settings.setValue("recent_files", [])
        self._update_recent_files_menu()
        
    def _auto_load_last_project(self):
        """Automatically load the last project from settings"""
        last_path = self.win.settings.value("last_project_path")
        if last_path:
            path = Path(last_path)
            if path.exists():
                self.win.statusbar.showMessage(f"Auto-loading last project: {path.name}...")
                self._load_project_at_path(path)
