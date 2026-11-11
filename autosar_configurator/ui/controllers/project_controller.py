"""Project controller — extracted from DaVinciMainWindow (P2-6, phase 8).

Owns project lifecycle (new / open / load / save), project properties, variant
management, module add, EB import, recommended-value loading, single-config
save, session restore, and the recent-files menu. Holds a back-reference to the
main window (``self.win``) for shared state (current_project, workspace_manager,
config_manager, tree_view, settings, statusbar, actions, chip_constraint_service)
and Qt parenting.
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Tuple

from PySide6.QtCore import Qt
from PySide6.QtGui import QAction
from PySide6.QtWidgets import (
    QFileDialog, QMessageBox, QInputDialog, QLineEdit, QDialog,
)

import logging

from ...core.config_manager import PreLockedError, ValidationError
from ...core.model.configuration_model import EcucContainerValue
from ..commands import SetParameterCommand

logger = logging.getLogger(__name__)


@dataclass
class RecommendedApplyResult:
    updated: int = 0
    skipped: List[Tuple[str, str]] = field(default_factory=list)          # (path, why)
    locked: List[str] = field(default_factory=list)                       # Pre keys skipped
    containers: List[EcucContainerValue] = field(default_factory=list)    # touched, in visiting order


def apply_recommended_changes(manager, rec_config, only_empty: bool, undo_stack) -> RecommendedApplyResult:
    """Write the recommended values of ``rec_config`` into ``manager``'s configuration as one undo step.

    A container the configuration lacks is created, and then all its values are written whatever
    ``only_empty`` says (its smart defaults are not the user's).  A value its definition refuses is
    skipped and reported; it never reaches the undo stack.

    A value of a locked Pre key is skipped the same way and listed in ``result.locked``: the
    merge owns it, so writing it would only be forced back on the next open. The check runs
    before the command is built (the command constructor would raise, and raising from inside
    the macro would leave ``endMacro`` unrun), and the push loop is guarded a second time so a
    ``PreLockedError`` can never escape into a Qt slot.
    """
    result = RecommendedApplyResult()
    changes = []

    def create(container_def, parent, name, path):
        if container_def is None:
            result.skipped.append((path, "no such container in the module definition"))
            return None
        try:
            return manager.create_container_instance(container_def, parent=parent, instance_name=name)
        except ValidationError as e:
            result.skipped.append((path, str(e)))
            return None

    def collect(current: EcucContainerValue, recommended: EcucContainerValue, path: str, is_new: bool):
        result.containers.append(current)
        for name, rec_param in recommended.parameter_values.items():
            current_param = current.parameter_values.get(name)
            current_value = current_param.value if current_param else None
            if rec_param.value is None:
                continue
            if only_empty and not is_new and current_value not in (None, ""):
                continue
            # Pre owns this value and the user has not unlocked it: neither this path nor the
            # merge may set it, so it is reported rather than turned into a command.
            try:
                manager.check_editable(current, name)
            except PreLockedError as exc:
                result.locked.append(exc.key)
                continue
            try:
                changes.append((current, name, manager.convert_parameter_value(current, name, rec_param.value)))
            except ValidationError as e:
                result.skipped.append((f"{path}/{name}", str(e)))
        for rec_sub in recommended.sub_containers:
            sub_path = f"{path}/{rec_sub.short_name}"
            sub = next((c for c in current.sub_containers if c.short_name == rec_sub.short_name), None)
            created = sub is None
            if created:
                current_def = manager.get_container_def(current.definition_ref)
                sub_def = current_def.sub_containers.get(rec_sub.short_name) if current_def else None
                sub = create(sub_def, current, rec_sub.short_name, sub_path)
            if sub is not None:
                collect(sub, rec_sub, sub_path, created)

    for rec_container in rec_config.containers:
        path = rec_container.short_name
        current = next((c for c in manager.configuration.containers if c.short_name == path), None)
        created = current is None
        if created:
            current = create(manager.module_def.containers.get(path), None, path, path)
        if current is not None:
            collect(current, rec_container, path, created)

    pushed = 0
    if changes:
        undo_stack.beginMacro("Apply Recommended Values")
        try:
            for instance, name, value in changes:
                try:
                    undo_stack.push(SetParameterCommand(manager, instance, name, value))
                except PreLockedError as exc:
                    # The pre-check above already skipped these; this is the second line of
                    # defence, so a change in the lock between the check and the push can
                    # never escape the macro half-open.
                    result.locked.append(exc.key)
                    continue
                pushed += 1
        finally:
            undo_stack.endMacro()
    result.updated = pushed
    result.locked.sort()
    return result


class ProjectController:
    """Project I/O, session, and recent-files behaviour for the main window."""

    def __init__(self, win):
        self.win = win

    def _confirm_merge(self, preview: str, result) -> bool:
        """Ask the user to accept a baseline merge (design §6.5, preview and confirm).

        The preview is ``MergeResult.to_markdown`` — what would be adopted, forced or
        created. Rejecting the dialog leaves the configuration and the snapshot as they
        are; the next open asks again. A caller that must not raise dialogs (an automatic
        session restore) passes ``confirm=None`` instead of this method, which makes the
        merge reject by itself.
        """
        return self._ask_merge(
            preview, "基线已变化",
            "模块包改变了该模块的基线。\n要把合并结果写入配置吗？\n"
            "（“保留当前”不改配置，下次打开会再次询问。）")

    def _confirm_import_merge(self, preview: str, result) -> bool:
        """The same question for an EB import (design §6.10): the plugin's Pre values would
        change the imported EPC values. Rejecting keeps the EPC values as imported; the
        next open of the project asks again."""
        from PySide6.QtWidgets import QApplication
        # The import runs under a wait cursor; the question must not look busy
        busy = QApplication.overrideCursor() is not None
        if busy:
            QApplication.restoreOverrideCursor()
        try:
            return self._ask_merge(
                preview, "导入：预设值与 EPC 值不同",
                "插件的预设（Pre）值与导入的 EPC 值不同，或 EPC 中缺少预设容器。\n"
                "要按预设修改导入的配置吗？\n"
                "（“保留当前”保留 EPC 值不变，下次打开工程会再次询问。）")
        finally:
            if busy:
                QApplication.setOverrideCursor(Qt.WaitCursor)

    def _import_target_dir(self, project_root: Path, chosen: Path):
        """The project directory for the destination folder the user chose, or None (with a
        warning) when it is the EB tree or inside it: the import only reads the EB tree.
        A folder that holds the EB tree gives the sibling ``<EB tree>_imported``."""
        from ...core.eb_import import import_target
        try:
            return import_target(project_root, chosen)
        except ValueError as exc:
            QMessageBox.warning(self.win, "目标目录不可用", str(exc))
            return None

    def _ask_merge(self, preview: str, title: str, text: str) -> bool:
        box = QMessageBox(self.win)
        box.setWindowTitle(title)
        box.setIcon(QMessageBox.Icon.Question)
        box.setText(text)
        box.setDetailedText(preview)
        confirm_button = box.addButton("应用合并", QMessageBox.ButtonRole.AcceptRole)
        box.addButton("保留当前（拒绝）", QMessageBox.ButtonRole.RejectRole)
        box.exec()
        return box.clickedButton() is confirm_button

    def _ecu_resource_status(self) -> str:
        """Run the ECU resource diagnosis for the current project.

        Returns a short suffix for the status bar ("" when nothing is wrong).
        The details (missing keys, consistency problems) are written to the log.
        """
        project = self.win.current_project
        if not project:
            return ""
        report = project.diagnose_ecu_resources()
        hint = ""
        if project.selected_chip and project.chip_source() != "project":
            hint = "  |  Chip data is not saved in the project yet (Project Properties > Save Chip to Project)"
        if not report or not report.has_warnings:
            return hint
        return (f"  |  ECU resources: {len(report.missing)} missing key(s), "
                f"{len(report.consistency)} warning(s) - see log{hint}")

    def apply_project_chip(self, chip_name, write_selectors: bool):
        """The one way the project's chip takes effect (update-unified-chip-selection).

        Sets ``selected_chip``, recomputes the ECU resources, reloads the UI
        constraints and, for an explicit selection by the user
        (``write_selectors``), writes the chip's declared selector values into the
        loaded modules.  Opening or importing a project passes False: the
        configuration is left as it is and only checked.

        Returns:
            SelectorResult when selectors were written, else None
        """
        project = self.win.current_project
        if not project:
            return None
        project.selected_chip = chip_name
        project.chip_changed()

        result = None
        if write_selectors and chip_name:
            result = project.apply_chip_selectors()
            if result.changed:
                self.win._has_unsaved_changes = True
            segments = self._selector_result_lines(result)
            if segments:
                self.win.statusbar.showMessage("; ".join(segments), 5000)

        service = getattr(self.win, 'chip_constraint_service', None)
        if service is None:
            return result
        service.set_project(project)
        if service.current_chip != chip_name:
            service.set_chip(chip_name)     # emits constraints_changed -> UI refresh
        else:
            self.win._on_chip_constraints_changed(chip_name or "")
        return result

    def selector_mismatches(self) -> list:
        """Selector parameters configured differently from what the project's chip declares."""
        from ...core.hardware.ecu_resource_diagnostics import check_selectors
        from ...core.hardware.ecu_resource_resolver import chip_for_project

        project = self.win.current_project
        if not project:
            return []
        return check_selectors(project, chip_for_project(project, project.chip_database)[1])

    @staticmethod
    def _selector_result_lines(result) -> list:
        """Status-bar segments for an applied selector pass: what changed, what a lock refused.

        A skipped selector is logged by core at ``info``; the user only sees it if the UI
        says so, and a locked Pre selector changes nothing else, so it would otherwise be
        dropped entirely (``add_module_to_project`` used to show a suffix only when values
        changed). ``result.locked`` is the explicit collection — never a word matched in the
        reason text. Keys are sorted, so the message is stable.
        """
        if result is None:
            return []
        segments = []
        if result.changed:
            segments.append(f"Chip selectors: {len(result.changed)} written")
        locked = sorted(getattr(result, "locked", None) or [])
        if locked:
            segments.append(
                f"{len(locked)} 预配置（PRE）选择器已锁定，未写入: {', '.join(locked)}")
        return segments

    @classmethod
    def _selector_result_status(cls, result) -> str:
        """``_selector_result_lines`` joined as a status suffix (``""`` when nothing to say)."""
        segments = cls._selector_result_lines(result)
        return ("  |  " + "; ".join(segments)) if segments else ""

    def _selector_status(self) -> str:
        """Status bar suffix when the configuration's chip selectors differ from the chip."""
        mismatches = self.selector_mismatches()
        if not mismatches:
            return ""
        return (f"  |  {len(mismatches)} chip selector(s) differ from the project's chip "
                f"(Project Properties > Apply Chip Selectors)")

    def preview_chip_change(self, chip_name):
        """What selecting ``chip_name`` would do, computed on copies of the project
        (add-chip-switch-disabled-report): selector values written and configured
        containers that ENABLE conditions would disable or enable again.

        Returns:
            ChipChangeReport; its ``error`` is set when the effect could not be computed
        """
        from ...core.hardware.chip_selectors import preview_chip_change
        from ...generator.eb.enable_conditions import disabled_containers
        from ..dialogs.chip_change_preview_dialog import ChipChangeReport, summary_lines

        project = self.win.current_project
        report = ChipChangeReport(chip_name, getattr(project, "selected_chip", None))
        if not project:
            return report
        try:
            preview = preview_chip_change(project, chip_name)
            report.selector_result = preview.selector_result
            before = set(disabled_containers(preview.current_modules,
                                             preview.current_ecu_resources or None))
            after = set(disabled_containers(preview.modules, preview.ecu_resources or None))
        except Exception as e:  # noqa: BLE001 - the preview must not block the change
            logger.exception("Could not preview the change to chip %s", chip_name)
            report.error = str(e) or type(e).__name__
            return report
        report.disabled = sorted(after - before)
        report.enabled = sorted(before - after)
        changes = self._changed_inputs(preview)
        files = self._definition_files(project)
        report.disabled_reasons = self._reasons(report.disabled, changes, files)
        report.enabled_reasons = self._reasons(report.enabled, changes, files)
        report.unavailable = self._unavailable_kinds(report.disabled, after, preview.modules)
        report.descriptions = self._container_descriptions(
            project, {(d.module, d.definition) for d in report.disabled + report.enabled})
        self._layout_preview(project, chip_name, report)
        for title, items in (("disabled", report.disabled), ("enabled again", report.enabled)):
            if items:
                logger.info("Chip %s: %d configured container(s) %s: %s", chip_name, len(items),
                            title, "; ".join(summary_lines(items)))
                for item in items:
                    logger.info("  %s %s", title, item.path)
        return report

    @staticmethod
    def _layout_preview(project, chip_name, report) -> None:
        """The "内存布局" section of the preview (add-memory-layout-config): what the change
        does to the project's layout configuration.  Nothing is written; when the project
        has no configuration file, or anything fails, the section is left out (logged) so
        that the preview never blocks the change."""
        from types import SimpleNamespace

        from ...core.hardware.ecu_resource_resolver import chip_for_project
        from ...core.memmap import chipchange
        from ...core.memmap.session import LayoutSession

        if not chip_name or chip_name == getattr(project, "selected_chip", None):
            return
        try:
            session = LayoutSession.open(project)
            if (session.path is None or not session.path.is_file() or session.load_error
                    or not session.config.regions):
                return
            database = getattr(project, "chip_database", None)
            old_chip = chip_for_project(project, database)[1]
            new_project = SimpleNamespace(path=getattr(project, "path", None), selected_chip=chip_name,
                                          chip_database=database)
            new_chip = chip_for_project(new_project, database)[1]
            change = chipchange.compare(session.config,
                                        list(getattr(old_chip, "memory_regions", None) or []),
                                        list(getattr(new_chip, "memory_regions", None) or []))
        except Exception:  # noqa: BLE001 - the preview must not block the change
            logger.exception("Could not preview the memory layout for chip %s", chip_name)
            return
        report.layout_change = change
        report.layout_lines = change.summary_lines()

    def apply_layout_change(self, report) -> bool:
        """After a confirmed chip change: record the layout change of the preview on the
        project's layout configuration and save it.  Returns whether it was written."""
        from ...core.memmap import chipchange
        from ...core.memmap.session import LayoutSession

        project = self.win.current_project
        change = getattr(report, "layout_change", None) if report is not None else None
        if not project or change is None or not report.chip_name:
            return False
        try:
            session = LayoutSession.open(project)
            if session.load_error or session.path is None or not session.path.is_file():
                return False
            chipchange.apply(session.config, report.chip_name, change)
            session.save()
        except Exception:  # noqa: BLE001 - the chip is changed already; say so in the log
            logger.exception("Could not update the memory layout for chip %s", report.chip_name)
            return False
        logger.info("Memory layout updated for chip %s: %s", report.chip_name,
                    "; ".join(report.layout_lines))
        return True

    @staticmethod
    def _changed_inputs(preview) -> dict:
        """What a condition may read that the chip change alters:
        ``{"selector": {param: (old, new)}, "ecu": {key: (old, new)}}``."""
        def default_of(module, param):
            """Definition default of a selector (what conditions read while it is unset)."""
            module_def = (preview.modules.get(module) or (None, None))[0]
            if module_def is None:
                return None
            param_def = (getattr(module_def, "parameters", None) or {}).get(param)
            stack = list(module_def.containers.values())
            while param_def is None and stack:
                container_def = stack.pop()
                param_def = container_def.parameters.get(param)
                stack.extend(container_def.sub_containers.values())
            return getattr(param_def, "default_value", None)

        selectors = {}
        for key, old, new in preview.selector_result.changed:
            module, _, param = key.partition(".")
            selectors[param] = (old, new, default_of(module, param) if old is None else None)
        before, after = preview.current_ecu_resources or {}, preview.ecu_resources or {}
        ecu = {key: (before.get(key), after.get(key)) for key in set(before) | set(after)
               if before.get(key) != after.get(key)}
        return {"selector": selectors, "ecu": ecu}

    @staticmethod
    def _reasons(items, changes, files=None) -> dict:
        """(module, definition) -> [(condition, [changed inputs it reads], location)],
        one entry per distinct condition, the inputs as display text, the location as
        (definition file, line) or None when unknown."""
        import re

        from ..dialogs.chip_change_preview_dialog import UNSET, short_value

        def inputs(condition):
            found = []
            for param, (old, new, default) in sorted(changes["selector"].items()):
                if re.search(rf"\b{re.escape(param)}\b", condition):
                    if old is not None:
                        before = old
                    elif default is not None:
                        before = f"（未设置，默认 {default}）"
                    else:
                        before = UNSET
                    found.append(f"{param}：{before} → {new}")
            for key in sorted(set(re.findall(r"ecu:(?:get|list|has)\('([^']+)'\)", condition))):
                if key in changes["ecu"]:
                    old, new = changes["ecu"][key]
                    found.append(f"芯片资源 {key}："
                                 f"{'（无）' if old is None else short_value(old)} → "
                                 f"{'（无）' if new is None else short_value(new)}")
            return found

        reasons: dict = {}
        for item in items:
            entries = reasons.setdefault((item.module, item.definition), [])
            file = (files or {}).get(item.module)
            location = (file, item.condition_line) if file and item.condition_line else None
            if item.condition and all((c, loc) != (item.condition, location) for c, _, loc in entries):
                entries.append((item.condition, inputs(item.condition), location))
        return reasons

    @staticmethod
    def _definition_files(project) -> dict:
        """Module name -> its definition file, relative to the project directory when
        inside it, as a POSIX path."""
        project_dir = Path(project.path).parent if getattr(project, "path", None) else None
        files = {}
        for module, def_path in (getattr(project, "module_defs", None) or {}).items():
            if not def_path:
                continue
            path = Path(def_path)
            try:
                path = path.resolve().relative_to(project_dir.resolve()) if project_dir else path
            except ValueError:
                pass
            files[module] = path.as_posix()
        return files

    @staticmethod
    def _unavailable_kinds(newly_disabled, disabled_after, modules_after) -> list:
        """(module, definition) of the newly disabled kinds of container that have no
        enabled instance left after the change."""
        from ...generator.eb.enable_conditions import container_paths, is_disabled

        topmost = {d.path for d in disabled_after}
        paths = container_paths(modules_after)
        kinds = sorted({(d.module, d.definition) for d in newly_disabled})
        return [kind for kind in kinds
                if all(is_disabled(path, topmost) for path in paths.get(kind, []))]

    @staticmethod
    def _container_descriptions(project, kinds) -> dict:
        """(module, definition) -> description of the container definition (DESC)."""
        from ..dialogs.chip_change_preview_dialog import clean_description

        def find(container_defs, name):
            for container_def in container_defs:
                if container_def.short_name == name:
                    return container_def
                found = find(container_def.sub_containers.values(), name)
                if found is not None:
                    return found
            return None

        descriptions = {}
        for module, definition in sorted(kinds):
            manager = project.module_managers.get(module)
            module_def = getattr(manager, "module_def", None)
            container_def = find(module_def.containers.values(), definition) if module_def else None
            text = clean_description(getattr(container_def, "description", "") or "")
            if text:
                descriptions[(module, definition)] = text
        return descriptions

    def confirm_chip_change(self, chip_name, parent=None, title="切换芯片",
                            accept_text="切换") -> bool:
        """Preview a chip change and ask the user to confirm it."""
        from PySide6.QtWidgets import QApplication

        QApplication.setOverrideCursor(Qt.WaitCursor)
        try:
            report = self.preview_chip_change(chip_name)
        finally:
            QApplication.restoreOverrideCursor()
        self.last_chip_report = report
        return self._show_chip_change_preview(report, parent, title, accept_text)

    def _show_chip_change_preview(self, report, parent, title, accept_text) -> bool:
        from ..dialogs.chip_change_preview_dialog import ChipChangePreviewDialog

        dialog = ChipChangePreviewDialog(report, parent or self.win, title, accept_text)
        return dialog.exec() == QDialog.Accepted

    def new_project(self):
        """Create a new project using the guided NewProjectWizard"""
        from ..wizards.new_project_wizard import NewProjectWizard
        from ...core.config_manager import ProjectType, ConfigLoader

        # Resolve chip database (reuse from chip_constraint_service if available)
        chip_db = None
        if hasattr(self.win, 'chip_constraint_service') and self.win.chip_constraint_service:
            chip_db = getattr(self.win.chip_constraint_service, '_chip_database', None)

        wizard = NewProjectWizard(chip_database=chip_db, parent=self.win)
        if wizard.exec() != NewProjectWizard.Accepted:
            return

        result = wizard.get_result()
        name = result["project_name"]
        project_type = result["project_type"]
        folder = result["folder_path"]
        selected_chip = result["selected_chip"]

        if not name or not folder:
            return

        project_path = folder / f"{name}.dpa"

        # The chosen path must be a folder (or not exist yet)
        if folder.exists() and not folder.is_dir():
            QMessageBox.warning(self.win, "Invalid Folder",
                                f"The selected path is not a folder:\n{folder}")
            return

        # Check if folder has existing content (warn user)
        existing_items = list(folder.iterdir()) if folder.is_dir() else []
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

        # Chips imported or created in the wizard live in its database; build
        # ecu:get()/ecu:list() data from the selected chip's YAML resources.
        self.win.current_project.chip_database = wizard.chip_database
        if selected_chip:
            self.win.current_project.selected_chip = selected_chip
            # A new project keeps its own copy of the chip from the start
            try:
                self.win.current_project.adopt_selected_chip()
            except ValueError as e:
                logger.warning(f"Chip {selected_chip} was not saved in the project: {e}")
        # Explicit selection: modules added later get the chip's selector values
        self.apply_project_chip(selected_chip, write_selectors=True)
        logger.info(f"New project chip set to: {selected_chip}")
        ecu_status = self._ecu_resource_status()

        self.win.save_project_action.setEnabled(True)
        self.win.add_module_action.setEnabled(True)
        self.win.manage_variants_action.setEnabled(True)
        self.win.manage_variants_btn.setEnabled(True)
        self.win.project_properties_action.setEnabled(True)

        # Update variant selector
        self.win._update_variant_selector()

        # Update mode label
        self.win.mode_label.setText(f"Project: {project_type.value}")

        # Update window title
        self.win._update_window_title()

        chip_info = f", Chip: {selected_chip}" if selected_chip else ""
        self.win.statusbar.showMessage(
            f"Created {project_type.value} project: {name}{chip_info}{ecu_status}", 5000)
        
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
                self.win.current_project, failed_modules = self.win.workspace_manager.load_project(
                    load_path, confirm=self._confirm_merge)
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
                target_dir = self._import_target_dir(project_root, Path(target_dir_str))
                if target_dir is None:
                    return
                target_dir.mkdir(parents=True, exist_ok=True)

                # Batch import with progress
                self.win.statusbar.showMessage("Importing EB project...")
                from PySide6.QtWidgets import QApplication
                QApplication.processEvents()

                self.win.current_project, loaded_modules, failed_modules = \
                    self.win.workspace_manager.import_eb_project(
                        project_root, chip_name=chip_name,
                        target_dir=target_dir,
                        progress_callback=lambda msg: self.win.statusbar.showMessage(msg),
                        confirm=self._confirm_import_merge,
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
                report = self.win.workspace_manager.last_import_report
                if report is not None:
                    summary += f"\n\n导入报告：{report}"

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

            # "Default" is the base configuration: old Default overrides were dropped at load
            conflicts = getattr(self.win.current_project, "default_override_conflicts", None)
            if conflicts:
                shown = conflicts[:20]
                details = "\n".join(
                    f"• {module} {path}：覆盖值 {override}，基础值 {'未配置' if base is None else base}"
                    for module, path, override, base in shown)
                if len(conflicts) > len(shown):
                    details += f"\n… 以及另外 {len(conflicts) - len(shown)} 处"
                QMessageBox.information(
                    self.win, "Default 变体已并入基础配置",
                    "Default 变体就是基础配置，不再单独保存覆盖值。\n"
                    f"以下 {len(conflicts)} 处旧覆盖值与基础值不同，已按基础值保留"
                    "（生成的代码一直使用基础值）：\n\n"
                    f"{details}\n\n保存工程后不再提示。")
            
            # The project's chip: the saved one, else (older projects) the one chip
            # whose declared selectors match the configuration.  Opening never
            # changes the configuration.
            if self.win.current_project:
                initial_chip = self.win.current_project.selected_chip
                if not initial_chip:
                    initial_chip = self.win.current_project.chip_from_configuration()
                self.apply_project_chip(initial_chip, write_selectors=False)
                logger.info(f"Project chip: {initial_chip}")

            status_msg += self._ecu_resource_status() + self._selector_status()
            self.win.statusbar.showMessage(status_msg, 5000)

            # Auto-select first module
            self.win.tree_view.select_first_module()

            # Save as last loaded project for auto-loading next time
            self.win.settings.setValue("last_project_path", str(self.win.current_project_file))

            # Add to recent files
            self._add_to_recent_files(str(self.win.current_project_file))

            # Update window title after project load
            if self.win.current_project:
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

                    # Move the project to the new location; a format 8 project takes its
                    # module library, baseline and unloaded values along
                    self.win.workspace_manager.relocate_project(new_dpa_path)
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
        
        import importlib
        from ..dialogs import project_properties_dialog
        importlib.reload(project_properties_dialog)
        ProjectPropertiesDialog = project_properties_dialog.ProjectPropertiesDialog
        
        dialog = ProjectPropertiesDialog(self.win.current_project, self.win,
                                         apply_selectors=self.apply_chip_selectors_now,
                                         selector_mismatches=self.selector_mismatches)
        if dialog.exec():
            # Update project with new data
            data = dialog.get_data()
            self.win.current_project.name = data['name']
            self.win.current_project.version = data['version']
            self.win.current_project.author = data['author']
            self.win.current_project.description = data['description']
            chip = data.get('selected_chip')
            chip_status = ""
            if chip != self.win.current_project.selected_chip:
                # Explicit chip selection, previewed first: ECU resources, constraints
                # and selectors follow only when the user confirms
                if self.confirm_chip_change(chip):
                    self.apply_project_chip(chip, write_selectors=True)
                    self.apply_layout_change(getattr(self, "last_chip_report", None))
                    chip_status = f"  |  已切换芯片为 {chip}"
                else:
                    chip_status = "  |  已取消切换芯片"

            # Update tree header
            self.win.tree_view.setHeaderLabel(f"Project: {self.win.current_project.name}")

            self.win.statusbar.showMessage(
                f"Project properties updated{chip_status}{self._ecu_resource_status()}"
                f"{self._selector_status()}", 3000)

    def apply_chip_selectors_now(self, parent=None):
        """'Apply Chip Selectors': preview, then write the project chip's declared
        selector values.  Returns None when the user cancels."""
        project = self.win.current_project
        if not project:
            return None
        if not self.confirm_chip_change(project.selected_chip, parent,
                                        "写入芯片选择器", "写入"):
            return None
        result = project.apply_chip_selectors()
        if result.changed:
            self.win._has_unsaved_changes = True
            self.win._refresh_config_views()
        return result

    
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
            project = self.win.current_project
            from ...core.workspace_manager import package_for_path
            hit = package_for_path(project, Path(file_path)) if project.module_libraries else None
            manager = None
            if hit is not None:
                # The file lies inside a package of a registered library: add through it.
                # A configuration file already on disk is merged with the package's
                # baseline, so the user is asked to confirm it, exactly as on open.
                lib_index, pkg = hit
                manager = project.add_module_from_package(
                    pkg, lib_index, confirm=self._confirm_merge)
                module_def = manager.module_def
            else:
                # Ensure parser has latest chip constraints before parsing
                constraints = self.win.chip_constraint_service.get_all_constraints()
                if constraints:
                    self.win.def_parser._resolver.set_constraints(constraints)
                from ...core.hardware.ecu_resource_resolver import selector_values
                self.win.def_parser.set_selector_values(selector_values(project))
                module_def = self.win.def_parser.parse_module_def_file(Path(file_path))
                project.add_module(module_def, Path(file_path))
            # The new module may ship its own .properties resources
            self.win.current_project.load_ecu_resources()
            # Its chip selector parameters follow the project's chip
            result = self.win.current_project.apply_chip_selectors(modules=[module_def.short_name])
            if result.changed:
                self.win._has_unsaved_changes = True
            self.win.tree_view.set_project(self.win.current_project)
            selectors = self._selector_result_status(result)
            baseline_error = getattr(manager, "baseline_error", None)
            if baseline_error:
                QMessageBox.warning(
                    self.win, "Baseline Not Applied",
                    f"模块 {module_def.short_name} 的基线合并未完成，配置保持不变：\n"
                    f"{baseline_error}")
            self.win.statusbar.showMessage(
                f"Added module: {module_def.short_name}{selectors}{self._ecu_resource_status()}", 3000)
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
            source_epc = file_path.as_posix()
            eb_root = win.current_project.eb_source_root
            if eb_root:
                try:
                    source_epc = file_path.relative_to(eb_root).as_posix()
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

    @staticmethod
    def _disabled_items(project) -> set:
        """Configuration objects whose definition ENABLE condition is false (left out of
        the EPC export, as EB does); evaluated over the whole project."""
        from ...generator.eb.enable_conditions import disabled_configuration_objects

        modules = {name: (m.module_def, m.configuration)
                   for name, m in project.module_managers.items()
                   if m.module_def and m.configuration}
        try:
            resources = project.load_ecu_resources()
        except Exception:  # noqa: BLE001 - conditions rarely need ECU resources
            logger.exception("Could not resolve ECU resources for ENABLE conditions")
            resources = None
        return disabled_configuration_objects(modules, dict(resources) if resources else None)

    def export_epc_files(self):
        """Export module configurations as EB Tresos-compatible .epc files"""
        project = self.win.workspace_manager.current_project
        if not project:
            QMessageBox.warning(self.win, "Export EPC", "No project loaded.")
            return

        # Scope selection: all modules or a single one
        ALL = "All Modules"
        choices = [ALL] + sorted(project.module_managers)
        choice, ok = QInputDialog.getItem(
            self.win, "Export EPC",
            "Which module(s) to export?",
            choices, 0, False
        )
        if not ok:
            return
        module_name = None if choice == ALL else choice

        output_dir = QFileDialog.getExistingDirectory(
            self.win, "Select EPC Output Directory",
            str(Path.home()),
            QFileDialog.ShowDirsOnly
        )
        if not output_dir:
            return

        try:
            written = self.win.workspace_manager.export_epc(
                Path(output_dir), module_name=module_name, skip=self._disabled_items(project))
        except Exception as e:
            logger.error("EPC export failed: %s", e, exc_info=True)
            QMessageBox.critical(self.win, "Export EPC", f"Export failed:\n{e}")
            return

        names = ", ".join(p.name for p in written[:10]) + (" …" if len(written) > 10 else "")
        QMessageBox.information(
            self.win, "Export EPC",
            f"Exported {len(written)} EPC file(s) to:\n{output_dir}\n\n{names}"
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

        # A project subdirectory inside the chosen target — never the EB tree itself
        target_dir = self._import_target_dir(project_root, Path(target_dir_str))
        if target_dir is None:
            return
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
                    mode=import_mode,
                    confirm=self._confirm_import_merge,
                )

            self.win.current_project = project
            self.win.current_project_file = project.path

            # Set up UI
            self.win.tree_view.set_project(self.win.current_project)

            # Chip takes effect (ECU resources, UI constraints); the imported
            # configuration is kept as it is and only checked
            self.apply_project_chip(chip_name, write_selectors=False)

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
            mismatches = self.selector_mismatches()
            if mismatches:
                summary += ("\n\nChip selector parameters differ from the chip (kept as "
                            "imported; Project Properties > Apply Chip Selectors):\n  "
                            + "\n  ".join(mismatches))
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
            report = self.win.workspace_manager.last_import_report
            if report is not None:
                summary += f"\n\n导入报告：{report}"

            QMessageBox.information(self.win, "EB Project Imported", summary)
            self.win.statusbar.showMessage(
                f"Imported: {len(loaded_modules)} modules to {target_dir.name}"
                f"{self._ecu_resource_status()}", 5000
            )

        except Exception as e:
            QMessageBox.critical(self.win, "Import Error", f"Failed to import EB project:\n{str(e)}")
        finally:
            QApplication.restoreOverrideCursor()

    def _recommended_values_target(self, rec_file: Path):
        """The configuration manager of the module ``rec_file`` configures; None (after telling
        the user why) when the file is for no module here.

        The module selected in the tree is used when the file configures it; otherwise the
        project's module of the file, so the values never land in an unrelated module.
        """
        from ...core.config_manager import RecFileScanner

        modules = RecFileScanner.modules_in_file(rec_file)
        active = self.win.config_manager
        if active and active.module_def and (not modules or active.module_def.short_name in modules):
            return active
        managers = getattr(self.win.current_project, "module_managers", None) or {}
        candidates = [name for name in modules if name in managers]
        if len(candidates) == 1:
            return managers[candidates[0]]
        if len(candidates) > 1:
            name, ok = QInputDialog.getItem(
                self.win, "Select Module",
                "The file holds recommended values for several modules. Apply them to:",
                candidates, 0, False)
            return managers[name] if ok else None
        found = ", ".join(modules) or "none recognised"
        QMessageBox.warning(
            self.win, "Module Not Found",
            f"The file holds recommended values for: {found}.\n"
            f"None of these modules is in the current configuration.")
        return None

    def load_recommended_values(self):
        """Load and apply recommended values from _rec.arxml file"""
        from PySide6.QtWidgets import (QDialog, QVBoxLayout, QTableWidget, QTableWidgetItem,
                                       QDialogButtonBox, QHeaderView, QCheckBox)

        # Need an active configuration, or a project whose modules the file can belong to
        if not self.win.config_manager and not getattr(self.win.current_project, "module_managers", None):
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

        manager = self._recommended_values_target(Path(file_path))
        if manager is None:
            return

        # Load recommended values
        rec_config = manager.load_recommended_values(Path(file_path))
        if not rec_config:
            QMessageBox.warning(self.win, "Load Failed", "Could not parse recommended values file.")
            return

        # Get comparison
        comparisons = manager.get_recommended_value_comparison(rec_config)

        if not comparisons:
            QMessageBox.information(self.win, "No Values", "No comparable values found in rec file.")
            return

        # Show comparison dialog
        dialog = QDialog(self.win)
        dialog.setWindowTitle(f"Recommended Values Comparison — {manager.module_def.short_name}")
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
        
        # Checkbox for only_empty option (unchecked by default so differing recommended values are applied)
        only_empty_cb = QCheckBox("Only apply to empty/unset parameters")
        only_empty_cb.setChecked(False)
        layout.addWidget(only_empty_cb)
        
        # Buttons
        buttons = QDialogButtonBox(QDialogButtonBox.Apply | QDialogButtonBox.Cancel)
        buttons.button(QDialogButtonBox.Apply).clicked.connect(dialog.accept)
        buttons.rejected.connect(dialog.reject)
        layout.addWidget(buttons)
        
        if dialog.exec() == QDialog.Accepted:
            result = apply_recommended_changes(manager, rec_config, only_empty_cb.isChecked(),
                                               self.win.undo_stack)
            self.win._has_unsaved_changes = True

            # Refresh UI and select updated container so right-hand config panel displays new values
            self.win.tree_view.refresh()
            if result.containers:
                self.win.tree_view.select_container(result.containers[0])
            elif self.win.tree_view.currentItem():
                self.win.tree_view._on_item_clicked(self.win.tree_view.currentItem(), 0)

            text = f"Updated {result.updated} parameter(s) with recommended values."
            if result.skipped:
                shown = result.skipped[:15]
                text += f"\n\nSkipped {len(result.skipped)} item(s):\n" + "\n".join(
                    f"• {path}: {why}" for path, why in shown)
                if len(result.skipped) > len(shown):
                    text += f"\n… and {len(result.skipped) - len(shown)} more"
            if result.locked:
                shown = result.locked[:15]
                text += (f"\n\n未修改 {len(result.locked)} 个预配置（PRE）值，它们已锁定：\n"
                         + "\n".join(f"• {key}" for key in shown)
                         + ("\n… 及其他" if len(result.locked) > len(shown) else "")
                         + "\n\n如需修改，请在参数面板中右键选择“解锁此参数”。")
            QMessageBox.information(self.win, "Applied", text)
            status = f"Applied {result.updated} recommended values"
            if result.locked:
                status += f", {len(result.locked)} locked PRE value(s) skipped"
            self.win.statusbar.showMessage(status, 3000)
    
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
