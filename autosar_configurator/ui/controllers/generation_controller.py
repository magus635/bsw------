"""Code-generation controller — extracted from DaVinciMainWindow (P2-6, phase 6).

Owns single-module and project (incremental, parallel) code generation, the
progress/stats bookkeeping, and the collection of cross-module configurations.
Holds a back-reference to the main window (``self.win``) for shared state
(current_project, config_manager, module_def, current_project_file,
thread_pool, statusbar) and Qt parenting.
"""
import logging
from pathlib import Path
from typing import Any, Dict

from PySide6.QtWidgets import QFileDialog, QMessageBox

logger = logging.getLogger(__name__)


class GenerationController:
    """C/C++ code generation for a single module or an entire project."""

    def __init__(self, win):
        self.win = win
        self._gen_progress = None
        self._gen_stats = None
        self._gen_processed = 0
        self._gen_total = 0
        self._gen_workers = None

    def _get_all_project_configurations(self) -> Dict[str, Any]:
        """Collect all module configurations in the current project for cross-module access."""
        all_configs = {}
        if self.win.current_project:
            for name, manager in self.win.current_project.module_managers.items():
                if manager.module_def and manager.configuration:
                    all_configs[name] = (manager.module_def, manager.configuration)
        return all_configs

    def generate_code(self):
        """Generate C/C++ code for current module or entire project."""
        win = self.win
        # Check if in Project mode
        if win.current_project:
            self._generate_project_code()
        elif win.config_manager:
            self._generate_single_module_code()
        else:
            QMessageBox.warning(win, "No Configuration", "Please load a configuration first.")

    def _generate_single_module_code(self):
        """Generate code for single module."""
        win = self.win
        if not win.config_manager:
            return

        # Select output directory
        output_dir = QFileDialog.getExistingDirectory(
            win,
            "Select Output Directory",
            str(Path.home())
        )

        if not output_dir:
            return

        try:
            from ...generator.generator import CodeGenerator

            win.statusbar.showMessage("Generating code...")

            # Get variant overrides if in project mode with active variant
            variant_overrides = {}
            variant_name = None
            project_template_dir = None

            if win.current_project:
                variant_name = win.current_project.active_variant
                if variant_name and win.config_manager.configuration:
                    variant_overrides = win.config_manager.configuration.variant_overrides.get(variant_name, {})

                # Calculate project template directory (project_dir/templates)
                if win.current_project_file:
                    # Handle both file paths (.dpa) and directory paths (EB projects)
                    if win.current_project_file.is_dir():
                        project_dir = win.current_project_file
                    else:
                        project_dir = win.current_project_file.parent
                    project_template_dir = project_dir / "templates"
                    if not project_template_dir.exists():
                        logger.info(f"Project template directory not found at: {project_template_dir}")
                        project_template_dir = None
                    else:
                        logger.info(f"Using project template directory: {project_template_dir}")

            generator = CodeGenerator(
                win.module_def,
                win.config_manager.configuration,
                project_template_dir=project_template_dir,
                variant_overrides=variant_overrides,
                all_configurations=self._get_all_project_configurations(),
                selected_chip=win.current_project.selected_chip if win.current_project else None
            )

            # Pass parent output directory; generator.generate_all() handles the ModuleName/ subdir
            ok = generator.generate_all(Path(output_dir), variant=variant_name)

            if not ok and generator.last_status == 'skipped':
                searched = [str(d) for d in (generator.project_template_dir, generator.user_template_dir) if d]
                QMessageBox.warning(
                    win,
                    "Code Generation Skipped",
                    "No templates found for this module — nothing was generated.\n\n"
                    "Searched template directories:\n"
                    + ("\n".join(searched) if searched else "(none configured)")
                )
                win.statusbar.showMessage("Code generation skipped (no templates)", 3000)
                return

            QMessageBox.information(
                win,
                "Code Generated",
                f"Code generated successfully in:\n{output_dir}"
            )
            win.statusbar.showMessage("Code generation completed", 3000)

        except Exception as e:
            QMessageBox.critical(
                win,
                "Code Generation Error",
                f"Failed to generate code:\n{str(e)}"
            )
            win.statusbar.showMessage("Code generation failed", 3000)

    def _generate_project_code(self):
        """Generate code for all modules in project (incremental & parallel)."""
        win = self.win
        if not win.current_project:
            return

        # Default output directory is project_path/generateCode (no dialog needed)
        project_dir = win.current_project.path.parent if win.current_project.path else Path.home()
        output_dir = str(project_dir / "generateCode")

        from ...generator.generator import CodeGenerator
        from PySide6.QtWidgets import QProgressDialog
        from PySide6.QtCore import Qt as QtCore_Qt, QObject, Signal, QRunnable, Slot

        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)
        modules = list(win.current_project.module_managers.items())

        # Debug: Log all modules in project
        logger.info(f"[CodeGen] Project has {len(modules)} module(s): {[m[0] for m in modules]}")
        for name, mgr in modules:
            has_config = mgr.configuration is not None
            logger.info(f"[CodeGen]   - {name}: has_config={has_config}")

        if not modules:
            QMessageBox.information(win, "No Modules", "Project has no modules to generate.")
            return

        # --- Worker Classes ---
        class GenSignals(QObject):
            finished = Signal(str, str, str)  # module_name, status (GEN/SKIP/FAIL), message

        class GenWorker(QRunnable):
            def __init__(self, name, manager, out_path, variant_name=None, variant_overrides=None, project_template_dir=None, all_configs=None, selected_chip=None):
                super().__init__()
                self.name = name
                self.manager = manager
                self.out_path = out_path
                self.variant_name = variant_name
                self.variant_overrides = variant_overrides or {}
                self.project_template_dir = project_template_dir
                self.all_configs = all_configs
                self.selected_chip = selected_chip
                self.signals = GenSignals()

            @Slot()
            def run(self):
                try:
                    import logging
                    _log = logging.getLogger(__name__)
                    _log.debug(f"Starting generation for: {self.name}")

                    # Generate with variant overrides, project templates, and directory structure
                    generator = CodeGenerator(
                        self.manager.module_def,
                        self.manager.configuration,
                        project_template_dir=self.project_template_dir,
                        variant_overrides=self.variant_overrides,
                        variant_name=self.variant_name,
                        all_configurations=self.all_configs,
                        selected_chip=self.selected_chip
                    )
                    # Pass parent output path; generator.generate_all() handles the ModuleName/ subdir
                    variant_to_use = self.variant_name if self.variant_name else "Default"
                    generated = generator.generate_all(self.out_path, force=False, variant=variant_to_use)

                    if generated:
                        status, detail = "GEN", ""
                    elif generator.last_status == 'skipped':
                        status, detail = "SKIP", "no templates found"
                    else:
                        status, detail = "FAIL", "generation failed (see log)"
                    self.signals.finished.emit(self.name, status, detail)
                except Exception as e:
                    import traceback
                    traceback.print_exc()
                    self.signals.finished.emit(self.name, "FAIL", str(e))

        # --- Setup Progress ---
        self._gen_progress = QProgressDialog(
            "Initializing code generation...",
            "Cancel",
            0,
            len(modules),
            win
        )
        self._gen_progress.setWindowModality(QtCore_Qt.WindowModal)
        self._gen_progress.setMinimumDuration(0)
        self._gen_progress.setValue(0)

        # Stats tracking
        self._gen_stats = {
            'generated': [],
            'skipped': [],
            'failed': []
        }
        self._gen_processed = 0
        self._gen_total = len(modules)

        # --- Completion Handler ---
        def on_module_done(name, status, msg):
            # Capture reference at start to avoid race condition
            progress = self._gen_progress
            stats = self._gen_stats

            # Check if already cleaned up (race condition with multiple signals)
            if progress is None or stats is None:
                logger.warning(f"[CodeGen] Signal for {name} arrived after cleanup, ignored")
                return
            if progress.wasCanceled():
                return

            # Add to stats BEFORE incrementing counter
            if status == "GEN":
                stats['generated'].append(name)
            elif status == "SKIP":
                stats['skipped'].append(f"{name} ({msg})" if msg else name)
            else:
                stats['failed'].append((name, msg))

            logger.info(f"[CodeGen] Module {name} done: status={status}, processed={self._gen_processed+1}/{self._gen_total}")

            self._gen_processed += 1

            # Update progress UI safely
            try:
                progress.setValue(self._gen_processed)
                progress.setLabelText(f"Processed {name} ({status})...")
            except RuntimeError:
                # Widget may have been deleted
                pass

            # Check if all done - only finalize when ALL modules are processed
            if self._gen_processed >= self._gen_total:
                # Use QTimer to defer finalization, allowing any pending signals to arrive
                from PySide6.QtCore import QTimer
                QTimer.singleShot(100, finalize_generation)

        def finalize_generation():
            # Guard against multiple calls
            if self._gen_stats is None:
                return

            # Capture stats before cleanup
            stats = dict(self._gen_stats)  # Make a copy

            # Cleanup
            self._gen_progress = None
            self._gen_stats = None
            self._gen_workers = None

            summary = "Code generation completed!\n\n"

            if stats['generated']:
                summary += f"✅ Generated: {len(stats['generated'])} module(s)\n"
            if stats['skipped']:
                summary += f"⏩ Skipped (Unchanged): {len(stats['skipped'])} module(s)\n"
            if stats['failed']:
                summary += f"❌ Failed: {len(stats['failed'])} module(s)\n"
                for m, err in stats['failed']:
                    summary += f"  - {m}: {err}\n"

            summary += f"\nOutput: {output_dir}"

            if stats['failed']:
                QMessageBox.warning(win, "Generation Completed with Errors", summary)
            else:
                QMessageBox.information(win, "Generation Successful", summary)

            win.statusbar.showMessage(
                f"Generated: {len(stats['generated'])}, Skipped: {len(stats['skipped'])}, Failed: {len(stats['failed'])}",
                5000
            )

        # --- Start Workers ---
        # Get current variant info
        variant_name = win.current_project.active_variant if win.current_project else None

        # Calculate project template directory (project_dir/templates)
        project_template_dir = None
        if win.current_project and win.current_project.path:
            project_dir = win.current_project.path.parent
            project_template_dir = project_dir / "templates"
            if not project_template_dir.exists():
                logger.info(f"Project template directory not found at: {project_template_dir}")
                project_template_dir = None
            else:
                logger.info(f"Using project template directory: {project_template_dir}")

        # Keep references to prevent garbage collection
        self._gen_workers = []
        all_configs = self._get_all_project_configurations()

        for name, manager in modules:
            if not manager.configuration:
                # Should not happen if strictly managed, but handle safe
                self._gen_stats['skipped'].append(name + " (No Config)")
                self._gen_processed += 1
                continue

            # Get variant overrides for this module
            mod_variant_overrides = {}
            if variant_name and manager.configuration:
                mod_variant_overrides = manager.configuration.variant_overrides.get(variant_name, {})

            worker = GenWorker(
                name, manager, output_path,
                variant_name=variant_name,
                variant_overrides=mod_variant_overrides,
                project_template_dir=project_template_dir,
                all_configs=all_configs,
                selected_chip=win.current_project.selected_chip if win.current_project else None
            )
            worker.setAutoDelete(False)  # Prevent automatic deletion
            # Use QueuedConnection for cross-thread signal delivery
            worker.signals.finished.connect(on_module_done, QtCore_Qt.QueuedConnection)
            self._gen_workers.append(worker)  # Keep reference
            win.thread_pool.start(worker)
