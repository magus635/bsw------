"""
Integration Wizard
Add BSW modules from libraries (DaVinci SIP, EB Tresos, module packages) with baseline merge.
"""
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Any, Optional, List, Set

from PySide6.QtWidgets import (
    QVBoxLayout, QHBoxLayout, QLabel, QComboBox, QLineEdit,
    QFormLayout, QPushButton, QTextEdit, QTableWidget,
    QTableWidgetItem, QHeaderView, QGroupBox, QFileDialog,
    QProgressBar, QWidget, QCheckBox, QRadioButton, QTreeWidget,
    QTreeWidgetItem, QSplitter, QTextBrowser, QMessageBox,
    QAbstractItemView, QInputDialog, QWizard, QDialog
)
from PySide6.QtCore import Qt, Signal, QThread
from PySide6.QtGui import QBrush, QColor

from .wizard_base import ConfigWizard, WizardPage
from ...core.workspace_manager import WorkspaceProject
from ...core.packages.library import LibraryRef, scan_library
from ...core.packages.package import ModulePackage
from ...core.packages.types import ModuleManifest
from ...core.baseline import session as baseline_session
from ...core.baseline.merge import MergeResult


@dataclass
class ModuleCandidate:
    """A module available for integration."""
    package: ModulePackage
    lib_index: int
    is_compatible: bool  # chip filter passed
    is_installed: bool   # already in project (exact same definition)
    category: str        # "MCAL", "Communication", "System", "Diagnostic", etc.
    has_pre: bool
    has_rec: bool
    is_other_variant: bool = False  # same module short_name installed with different definition
    conflict: Optional[str] = None  # if incompatible with selection


def _variant_label(pkg: ModulePackage) -> str:
    """Short human-readable identifier for a module package's variant."""
    definition = (pkg.manifest.definition or "").strip("/")
    segs = [s for s in definition.split("/") if s]
    if len(segs) >= 3:
        return segs[-2]
    dir_name = pkg.root.name if getattr(pkg, "root", None) else ""
    if dir_name and dir_name != pkg.manifest.module:
        return dir_name
    if len(segs) == 2:
        return segs[0]
    return pkg.manifest.definition or ""


class LibrarySelectionPage(WizardPage):
    """Page 1: Select module libraries to scan."""

    libraries_changed = Signal(list)  # List[LibraryRef]

    def __init__(self, project: WorkspaceProject):
        self.project = project
        self._libraries: List[LibraryRef] = list(project.module_libraries)
        self.lib_table = QTableWidget()
        self.add_btn = QPushButton()
        self.remove_btn = QPushButton()
        super().__init__(
            "Select Module Libraries",
            "Choose which libraries to scan for available modules"
        )

    def _setup_ui(self):
        # Current libraries
        group = QGroupBox("Module Libraries")
        layout = QVBoxLayout()

        self.lib_table.setColumnCount(3)
        self.lib_table.setHorizontalHeaderLabels(["Path", "Type", "Modules"])
        self.lib_table.horizontalHeader().setStretchLastSection(False)
        self.lib_table.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        self.lib_table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.lib_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        layout.addWidget(self.lib_table)

        btn_layout = QHBoxLayout()
        self.add_btn = QPushButton("Add Library...")
        self.add_btn.clicked.connect(self._add_library)
        btn_layout.addWidget(self.add_btn)

        self.remove_btn = QPushButton("Remove")
        self.remove_btn.clicked.connect(self._remove_library)
        self.remove_btn.setEnabled(False)
        btn_layout.addWidget(self.remove_btn)
        btn_layout.addStretch()

        layout.addLayout(btn_layout)
        group.setLayout(layout)
        self.layout.addWidget(group)

        # Info label
        info = QLabel(
            "Libraries from the project are already listed. "
            "Add more to discover additional modules."
        )
        info.setWordWrap(True)
        info.setStyleSheet("color: gray; font-size: 10pt;")
        self.layout.addWidget(info)

        self.lib_table.itemSelectionChanged.connect(self._on_selection_changed)
        self._refresh_table()

    def _refresh_table(self):
        """Populate table with project libraries."""
        self.lib_table.setRowCount(0)
        project_root = self.project.path.parent if self.project.path else Path.cwd()
        for lib in self._libraries:
            row = self.lib_table.rowCount()
            self.lib_table.insertRow(row)
            self.lib_table.setItem(row, 0, QTableWidgetItem(lib.path))
            self.lib_table.setItem(row, 1, QTableWidgetItem(lib.kind))
            try:
                count = str(len(scan_library(lib, project_root)))
            except Exception:
                count = "—"
            self.lib_table.setItem(row, 2, QTableWidgetItem(count))

    def _add_library(self):
        """Add a new library (package or EB plugins)."""
        start_dir = str(self.project.path.parent) if self.project.path else str(Path.home())
        path = QFileDialog.getExistingDirectory(
            self, "Select Module Library", start_dir
        )
        if not path:
            return

        chosen = Path(path)
        is_eb = False
        if chosen.is_dir():
            is_eb = (chosen / "plugin.xml").is_file() or any(
                (d / "plugin.xml").is_file() for d in chosen.iterdir() if d.is_dir()
            )
        default_idx = 1 if is_eb else 0

        kind, ok = QInputDialog.getItem(
            self, "Library Type", "Select library type:",
            ["package", "eb-plugins"], default_idx, False
        )
        if not ok:
            return

        stored_path = chosen.as_posix()
        if self.project.path:
            proj_root = self.project.path.parent.resolve()
            try:
                rel = chosen.resolve().relative_to(proj_root)
                stored_path = rel.as_posix() or "."
            except ValueError:
                pass

        lib = LibraryRef(path=stored_path, kind=kind, exclude=[])
        self._libraries.append(lib)
        self._refresh_table()
        self.libraries_changed.emit(list(self._libraries))

    def _remove_library(self):
        """Remove selected library."""
        row = self.lib_table.currentRow()
        if 0 <= row < len(self._libraries):
            self._libraries.pop(row)
            self._refresh_table()
            self.libraries_changed.emit(list(self._libraries))

    def _on_selection_changed(self):
        self.remove_btn.setEnabled(len(self.lib_table.selectedItems()) > 0)

    def get_data(self) -> Dict[str, Any]:
        return {"libraries": list(self._libraries)}


class ModuleSelectionPage(WizardPage):
    """Page 2: Select modules to integrate."""

    def __init__(self, project: WorkspaceProject):
        self.project = project
        self.candidates: List[ModuleCandidate] = []
        self.tree = QTreeWidget()
        self.detail_browser = QTextBrowser()
        self.select_all_btn = QPushButton()
        self.deselect_all_btn = QPushButton()
        self.filter_edit = QLineEdit()
        self.selected_count_label = QLabel()
        self._updating_checks = False
        self.last_skipped_ambiguous: List[str] = []

        super().__init__(
            "Select Modules",
            f"Choose modules to add (chip: {project.selected_chip or 'None'})"
        )

    def _setup_ui(self):
        # Filter bar
        filter_layout = QHBoxLayout()
        filter_layout.addWidget(QLabel("Filter:"))
        self.filter_edit.setPlaceholderText("Filter by module, definition path, package dir, or category...")
        self.filter_edit.textChanged.connect(self._apply_filter)
        filter_layout.addWidget(self.filter_edit)
        self.layout.addLayout(filter_layout)

        # Splitter: tree on left, details on right
        splitter = QSplitter(Qt.Horizontal)

        # Tree: categories with module children
        self.tree.setHeaderLabels(["Module", "Variant / Definition", "Pre", "Rec", "Status"])
        self.tree.setColumnWidth(0, 150)
        self.tree.setColumnWidth(1, 220)
        self.tree.itemSelectionChanged.connect(self._on_selection_changed)
        self.tree.itemChanged.connect(self._on_item_checked)
        splitter.addWidget(self.tree)

        # Detail panel
        detail_group = QGroupBox("Module Details")
        detail_layout = QVBoxLayout()
        self.detail_browser.setReadOnly(True)
        self.detail_browser.setOpenExternalLinks(False)
        detail_layout.addWidget(self.detail_browser)
        detail_group.setLayout(detail_layout)
        splitter.addWidget(detail_group)

        splitter.setStretchFactor(0, 2)
        splitter.setStretchFactor(1, 1)
        self.layout.addWidget(splitter, stretch=1)

        # Action buttons
        btn_layout = QHBoxLayout()
        self.select_all_btn = QPushButton("Select All Compatible")
        self.select_all_btn.clicked.connect(self._select_all)
        btn_layout.addWidget(self.select_all_btn)

        self.deselect_all_btn = QPushButton("Deselect All")
        self.deselect_all_btn.clicked.connect(self._deselect_all)
        btn_layout.addWidget(self.deselect_all_btn)

        btn_layout.addStretch()
        self.selected_count_label.setStyleSheet("font-weight: bold;")
        btn_layout.addWidget(self.selected_count_label)
        self.layout.addLayout(btn_layout)

    def initializePage(self):
        """Scan libraries when page is shown."""
        self._scan_modules()

    def _scan_modules(self):
        """Scan all libraries and populate tree."""
        self.candidates.clear()
        self.last_skipped_ambiguous.clear()
        self.tree.clear()

        chip_name = self.project.selected_chip
        module_entries = getattr(self.project, "module_entries", None) or {}
        project_pkgs = getattr(self.project, "packages", None) or {}
        installed_defs: Dict[str, str] = {}
        for mod_name, mgr in self.project.module_managers.items():
            entry = module_entries.get(mod_name)
            pkg = project_pkgs.get(mod_name)
            mdef = getattr(mgr, "module_def", None)
            def_ref = (
                (entry.definition if entry is not None and entry.definition else None)
                or (pkg.manifest.definition if pkg is not None else None)
                or getattr(mdef, "ar_path", None)
                or getattr(mdef, "definition_ref", None)
                or ""
            )
            installed_defs[mod_name] = def_ref.rstrip("/")

        libraries = self.project.module_libraries
        wizard = self.wizard()
        if wizard is not None and wizard.pageIds():
            lib_page = wizard.page(wizard.pageIds()[0])
            if hasattr(lib_page, "get_data"):
                libraries = lib_page.get_data().get("libraries", libraries)

        project_root = self.project.path.parent if self.project.path else Path.cwd()

        all_packages = []
        for lib_idx, lib in enumerate(libraries):
            try:
                packages = scan_library(lib, project_root)
                all_packages.extend((pkg, lib_idx) for pkg in packages)
            except Exception as e:
                print(f"Warning: Failed to scan {lib.path}: {e}")

        # Build candidates
        for pkg, lib_idx in all_packages:
            mod_name = pkg.manifest.module
            cand_def = (pkg.manifest.definition or "").rstrip("/")
            is_compatible = self._check_chip_compatibility(pkg, chip_name)
            if mod_name not in installed_defs:
                is_installed = False
                is_other_variant = False
            else:
                active_def = installed_defs[mod_name]
                is_installed = (not active_def) or (cand_def == active_def)
                is_other_variant = not is_installed
            category = self._infer_category(mod_name)

            candidate = ModuleCandidate(
                package=pkg,
                lib_index=lib_idx,
                is_compatible=is_compatible,
                is_installed=is_installed,
                category=category,
                has_pre=len(pkg.manifest.pre) > 0,
                has_rec=len(pkg.manifest.rec) > 0,
                is_other_variant=is_other_variant,
            )
            self.candidates.append(candidate)

        # Populate tree by category
        categories = {}
        self.tree.blockSignals(True)
        try:
            for cand in sorted(
                self.candidates,
                key=lambda c: (
                    c.category,
                    c.package.manifest.module,
                    c.package.manifest.definition,
                    c.lib_index,
                ),
            ):
                if cand.category not in categories:
                    cat_item = QTreeWidgetItem(self.tree, [cand.category])
                    cat_item.setFlags(cat_item.flags() | Qt.ItemIsAutoTristate)
                    cat_item.setExpanded(True)
                    categories[cand.category] = cat_item

                status = self._status_text(cand)
                item = QTreeWidgetItem(categories[cand.category], [
                    cand.package.manifest.module,
                    cand.package.manifest.definition,
                    "✓" if cand.has_pre else "",
                    "✓" if cand.has_rec else "",
                    status,
                ])
                pkg_dir_name = cand.package.root.name if getattr(cand.package, "root", None) else ""
                tip = f"Definition: {cand.package.manifest.definition}\nPackage Dir: {pkg_dir_name}"
                item.setToolTip(0, tip)
                item.setToolTip(1, tip)
                item.setData(0, Qt.UserRole, cand)
                item.setFlags(item.flags() | Qt.ItemIsUserCheckable)
                item.setCheckState(0, Qt.Unchecked)

                # Color-code (keep installed/sibling variants enabled so user can merge/replace/switch)
                if cand.is_installed:
                    item.setForeground(0, QBrush(QColor("gray")))
                elif cand.is_other_variant:
                    item.setForeground(0, QBrush(QColor("#7C3AED")))
                    item.setForeground(4, QBrush(QColor("#7C3AED")))
                elif not cand.is_compatible:
                    item.setForeground(0, QBrush(QColor("orange")))
        finally:
            self.tree.blockSignals(False)

        self._update_count()

    def _check_chip_compatibility(self, pkg: ModulePackage, chip_name: Optional[str]) -> bool:
        """Check if package files include the chip."""
        if not chip_name:
            return True  # no chip filter
        try:
            pkg.definition_file(chip_name)
            return True
        except Exception:
            return False

    def _infer_category(self, module_name: str) -> str:
        """Categorize module by name prefix."""
        CATEGORIES = {
            "MCAL": ["Adc", "Can", "Dio", "Gpt", "Icu", "Mcu", "Port", "Pwm", "Spi", "Wdg", "Fls", "Eth"],
            "Communication": ["CanIf", "CanTp", "CanTrcv", "Com", "PduR", "CanSM", "CanNm", "FrIf", "FrTp", "LinIf", "LinTrcv", "EthIf", "EthTrcv"],
            "System": ["Os", "EcuC", "Rte", "SchM", "BswM", "ComM", "EcuM"],
            "Diagnostic": ["Dcm", "Dem", "Det", "Fim"],
            "Memory": ["Ea", "Fee", "Fls", "MemIf", "NvM"],
            "Security": ["Csm", "Crypto", "KeyM", "SecOC"],
            "Other": [],
        }
        for cat, modules in CATEGORIES.items():
            if module_name in modules:
                return cat
        return "Other"

    def _status_text(self, cand: ModuleCandidate) -> str:
        if cand.is_installed:
            return "Installed"
        if cand.is_other_variant:
            return "Other Variant"
        if not cand.is_compatible:
            return "Incompatible"
        return "Available"

    def _on_selection_changed(self):
        """Update detail panel when selection changes."""
        items = self.tree.selectedItems()
        if not items:
            self.detail_browser.clear()
            return

        item = items[0]
        cand = item.data(0, Qt.UserRole)
        if not cand:
            self.detail_browser.clear()
            return

        origin = getattr(cand.package.manifest, "origin", None) or {}
        impl_meta = dict(origin.get("implementation") or {}) if isinstance(origin, dict) else {}
        if not (impl_meta.get("sw_version") or impl_meta.get("vendor_api_infix")):
            try:
                disk_impl = cand.package.read_impl_metadata() or {}
                for k, v in disk_impl.items():
                    impl_meta.setdefault(k, v)
            except Exception:
                pass
        sw_version = (
            impl_meta.get("sw_version")
            or (origin.get("sw_version") if isinstance(origin, dict) else None)
            or "—"
        )
        vendor_infix = impl_meta.get("vendor_api_infix") or "—"
        variant_label = _variant_label(cand.package)
        pkg_dir_name = cand.package.root.name if getattr(cand.package, "root", None) else ""

        html = f"""
        <h3>{cand.package.manifest.module} ({variant_label})</h3>
        <table>
        <tr><td><b>Category:</b></td><td>{cand.category}</td></tr>
        <tr><td><b>Variant:</b></td><td>{variant_label}</td></tr>
        <tr><td><b>Definition:</b></td><td><code>{cand.package.manifest.definition}</code></td></tr>
        <tr><td><b>Package Dir:</b></td><td><code>{pkg_dir_name}</code></td></tr>
        <tr><td><b>SW Version:</b></td><td>{sw_version}</td></tr>
        <tr><td><b>Vendor API Infix:</b></td><td>{vendor_infix}</td></tr>
        <tr><td><b>Status:</b></td><td>{self._status_text(cand)}</td></tr>
        <tr><td><b>Library:</b></td><td>{cand.package.root}</td></tr>
        <tr><td><b>Chip Compatible:</b></td><td>{'Yes' if cand.is_compatible else 'No'}</td></tr>
        <tr><td><b>Pre Config:</b></td><td>{'Yes' if cand.has_pre else 'No'}</td></tr>
        <tr><td><b>Rec Config:</b></td><td>{'Yes' if cand.has_rec else 'No'}</td></tr>
        <tr><td><b>Templates:</b></td><td>{'Yes' if cand.package.manifest.templates else 'No'}</td></tr>
        </table>
        """
        self.detail_browser.setHtml(html)

    def _on_item_checked(self, item: QTreeWidgetItem, column: int):
        """Enforce single-variant selection per module and update count."""
        if self._updating_checks or column != 0:
            return
        self._updating_checks = True
        try:
            changed_cand = item.data(0, Qt.UserRole)
            if changed_cand is not None and item.checkState(0) == Qt.Checked:
                target_mod = changed_cand.package.manifest.module
                for i in range(self.tree.topLevelItemCount()):
                    cat_item = self.tree.topLevelItem(i)
                    for j in range(cat_item.childCount()):
                        other = cat_item.child(j)
                        if other is item or other.checkState(0) != Qt.Checked:
                            continue
                        other_cand = other.data(0, Qt.UserRole)
                        if other_cand and other_cand.package.manifest.module == target_mod:
                            other.setCheckState(0, Qt.Unchecked)
            elif changed_cand is None and item.checkState(0) == Qt.Checked:
                # Category checkbox toggled: keep at most one variant per module name
                seen_mods: Set[str] = set()
                for i in range(self.tree.topLevelItemCount()):
                    cat_item = self.tree.topLevelItem(i)
                    for j in range(cat_item.childCount()):
                        child = cat_item.child(j)
                        if child.checkState(0) != Qt.Checked:
                            continue
                        cand = child.data(0, Qt.UserRole)
                        if cand:
                            mname = cand.package.manifest.module
                            if mname in seen_mods:
                                child.setCheckState(0, Qt.Unchecked)
                            else:
                                seen_mods.add(mname)
        finally:
            self._updating_checks = False
        self._update_count()

    def _update_count(self):
        """Update selected count label."""
        selected = self._get_selected_candidates()
        text = f"{len(selected)} module(s) selected"
        if self.last_skipped_ambiguous:
            text += f" (skipped multi-variant: {', '.join(self.last_skipped_ambiguous)})"
        self.selected_count_label.setText(text)

    def _select_all(self):
        """Check all compatible, not-installed, unambiguous modules (skip multi-variant modules)."""
        compat_counts: Dict[str, int] = {}
        for i in range(self.tree.topLevelItemCount()):
            cat_item = self.tree.topLevelItem(i)
            for j in range(cat_item.childCount()):
                cand = cat_item.child(j).data(0, Qt.UserRole)
                if cand and cand.is_compatible and not cand.is_installed and not cand.is_other_variant:
                    mname = cand.package.manifest.module
                    compat_counts[mname] = compat_counts.get(mname, 0) + 1

        self.last_skipped_ambiguous = sorted(
            mname for mname, cnt in compat_counts.items() if cnt > 1
        )
        self._updating_checks = True
        try:
            for i in range(self.tree.topLevelItemCount()):
                cat_item = self.tree.topLevelItem(i)
                for j in range(cat_item.childCount()):
                    item = cat_item.child(j)
                    cand = item.data(0, Qt.UserRole)
                    if (
                        cand
                        and cand.is_compatible
                        and not cand.is_installed
                        and not cand.is_other_variant
                        and compat_counts.get(cand.package.manifest.module, 0) == 1
                    ):
                        item.setCheckState(0, Qt.Checked)
        finally:
            self._updating_checks = False
        self._update_count()

    def _deselect_all(self):
        """Uncheck all."""
        self.last_skipped_ambiguous.clear()
        self._updating_checks = True
        try:
            for i in range(self.tree.topLevelItemCount()):
                cat_item = self.tree.topLevelItem(i)
                for j in range(cat_item.childCount()):
                    item = cat_item.child(j)
                    item.setCheckState(0, Qt.Unchecked)
        finally:
            self._updating_checks = False
        self._update_count()

    def _apply_filter(self, text: str):
        """Filter tree by module name, definition path, package dir name, or category."""
        text = text.lower()
        for i in range(self.tree.topLevelItemCount()):
            cat_item = self.tree.topLevelItem(i)
            cat_match = text in cat_item.text(0).lower()
            any_child_visible = False
            for j in range(cat_item.childCount()):
                item = cat_item.child(j)
                cand = item.data(0, Qt.UserRole)
                pkg_dir = cand.package.root.name.lower() if getattr(cand.package, "root", None) else ""
                match = (
                    not text
                    or cat_match
                    or text in cand.package.manifest.module.lower()
                    or text in (cand.package.manifest.definition or "").lower()
                    or text in pkg_dir
                )
                item.setHidden(not match)
                if match:
                    any_child_visible = True
            cat_item.setHidden(not any_child_visible)

    def _get_selected_candidates(self) -> List[ModuleCandidate]:
        """Get checked candidates."""
        selected = []
        for i in range(self.tree.topLevelItemCount()):
            cat_item = self.tree.topLevelItem(i)
            for j in range(cat_item.childCount()):
                item = cat_item.child(j)
                if item.checkState(0) == Qt.Checked:
                    cand = item.data(0, Qt.UserRole)
                    if cand:
                        selected.append(cand)
        return selected

    def get_data(self) -> Dict[str, Any]:
        return {"selected": self._get_selected_candidates()}

    def validatePage(self) -> bool:
        selected = self._get_selected_candidates()
        if not selected:
            QMessageBox.warning(self, "No Modules Selected",
                                "Please select at least one module to integrate.")
            return False
        return True


class ConfirmationPage(WizardPage):
    """Page 3: Preview modules and configure merge behavior."""

    def __init__(self, project: WorkspaceProject):
        self.project = project
        self.module_list = QTableWidget()
        self.merge_group = QGroupBox()
        self.merge_layout = QVBoxLayout()
        self.collision_text = QTextEdit()
        self.summary_label = QLabel()

        # Merge strategy radio buttons
        self.merge_strategy_merge = None
        self.merge_strategy_replace = None
        self.merge_strategy_skip = None

        super().__init__(
            "Confirm Integration",
            "Review modules to add and configure baseline merge"
        )

    def _setup_ui(self):
        # Module summary table
        group = QGroupBox("Modules to Add")
        layout = QVBoxLayout()

        self.module_list.setColumnCount(6)
        self.module_list.setHorizontalHeaderLabels(["Module", "Definition", "Category", "Pre", "Rec", "Library"])
        self.module_list.horizontalHeader().setStretchLastSection(True)
        self.module_list.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.module_list.setMaximumHeight(150)
        layout.addWidget(self.module_list)

        group.setLayout(layout)
        self.layout.addWidget(group)

        # Merge options
        self.merge_group = QGroupBox("Baseline Merge")
        self.merge_layout = QVBoxLayout()

        merge_info = QLabel(
            "When adding Pre/Rec configs, how should they be integrated?"
        )
        merge_info.setWordWrap(True)
        self.merge_layout.addWidget(merge_info)

        # Strategy radio buttons
        self.merge_strategy_merge = QRadioButton(
            "Merge: Combine Pre/Rec with existing baseline"
        )
        self.merge_strategy_merge.setChecked(True)
        self.merge_layout.addWidget(self.merge_strategy_merge)

        self.merge_strategy_replace = QRadioButton(
            "Replace: Use module's Pre/Rec as new baseline"
        )
        self.merge_layout.addWidget(self.merge_strategy_replace)

        self.merge_strategy_skip = QRadioButton(
            "Skip: Don't load Pre/Rec configurations"
        )
        self.merge_layout.addWidget(self.merge_strategy_skip)

        self.merge_group.setLayout(self.merge_layout)
        self.layout.addWidget(self.merge_group)

        # Collision warnings
        collision_group = QGroupBox("Conflicts & Warnings")
        collision_layout = QVBoxLayout()
        self.collision_text.setReadOnly(True)
        self.collision_text.setMaximumHeight(80)
        collision_layout.addWidget(self.collision_text)
        collision_group.setLayout(collision_layout)
        self.layout.addWidget(collision_group)

        # Summary
        self.summary_label.setStyleSheet("font-size: 11pt; font-weight: bold;")
        self.layout.addWidget(self.summary_label)

        self.layout.addStretch()

    def initializePage(self):
        """Update display with selected modules."""
        # Get selected from previous page
        selected = self.wizard().page(self.wizard().pageIds()[1]).get_data()["selected"]

        # Populate table
        self.module_list.setRowCount(len(selected))
        for row, cand in enumerate(selected):
            self.module_list.setItem(row, 0, QTableWidgetItem(cand.package.manifest.module))
            self.module_list.setItem(row, 1, QTableWidgetItem(cand.package.manifest.definition))
            self.module_list.setItem(row, 2, QTableWidgetItem(cand.category))
            self.module_list.setItem(row, 3, QTableWidgetItem("Yes" if cand.has_pre else ""))
            self.module_list.setItem(row, 4, QTableWidgetItem("Yes" if cand.has_rec else ""))
            self.module_list.setItem(row, 5, QTableWidgetItem(str(cand.package.root.parent.name)))

        # Check for duplicate module selections and variant/install conflicts
        mod_counts: Dict[str, int] = {}
        for cand in selected:
            mod_name = cand.package.manifest.module
            mod_counts[mod_name] = mod_counts.get(mod_name, 0) + 1

        conflicts = []
        for mod_name in sorted(mod_counts):
            if mod_counts[mod_name] > 1:
                conflicts.append(
                    f"• {mod_name}: Multiple variants selected ({mod_counts[mod_name]}); select only one"
                )
        for cand in selected:
            if cand.is_other_variant:
                conflicts.append(
                    f"• {cand.package.manifest.module}: Variant switch -> {cand.package.manifest.definition}"
                )
            elif cand.package.manifest.module in self.project.module_managers:
                conflicts.append(f"• {cand.package.manifest.module}: Already installed")

        if conflicts:
            self.collision_text.setText("\n".join(conflicts))
            self.collision_text.setStyleSheet("background-color: #fff3cd;")
        else:
            self.collision_text.setText("No conflicts detected.")
            self.collision_text.setStyleSheet("background-color: #d4edda;")

        self.summary_label.setText(f"Ready to add {len(selected)} module(s)")

    def get_data(self) -> Dict[str, Any]:
        if self.merge_strategy_skip.isChecked():
            strategy = "skip"
        elif self.merge_strategy_replace.isChecked():
            strategy = "replace"
        else:
            strategy = "merge"
        return {"merge_strategy": strategy}

    def validatePage(self) -> bool:
        selected = self.wizard().page(self.wizard().pageIds()[1]).get_data()["selected"]
        seen: Set[str] = set()
        dups: List[str] = []
        for cand in selected:
            mod_name = cand.package.manifest.module
            if mod_name in seen and mod_name not in dups:
                dups.append(mod_name)
            seen.add(mod_name)
        if dups:
            QMessageBox.warning(
                self,
                "Duplicate Module Variants",
                "Cannot integrate multiple implementation variants for the same module:\n"
                + ", ".join(sorted(dups)),
            )
            return False
        return True


class IntegrationWizard(ConfigWizard):
    """Main wizard: Add BSW modules from libraries."""

    wizard_completed = Signal(dict)  # Emits result dict

    def __init__(self, project: WorkspaceProject, parent=None, confirm_merge=None):
        self.project = project
        self._confirm_merge = confirm_merge
        self._result: Optional[Dict] = None
        super().__init__(parent, title="Integrate BSW Modules")

    def _setup_pages(self):
        """Setup wizard pages."""
        lib_page = LibrarySelectionPage(self.project)
        mod_page = ModuleSelectionPage(self.project)
        conf_page = ConfirmationPage(self.project)

        self.addPage(lib_page)
        self.addPage(mod_page)
        self.addPage(conf_page)

    def accept(self):
        """Perform integration on finish."""
        page_ids = self.pageIds()
        lib_data = self.page(page_ids[0]).get_data() if len(page_ids) > 0 else {}
        mod_data = self.page(page_ids[1]).get_data() if len(page_ids) > 1 else {}
        conf_data = self.page(page_ids[2]).get_data() if len(page_ids) > 2 else {}

        if "libraries" in lib_data:
            self.project.module_libraries = list(lib_data["libraries"])

        selected: List[ModuleCandidate] = mod_data.get("selected", [])
        merge_strategy = conf_data.get("merge_strategy", "merge")

        # Perform integration
        self._result = self._integrate_modules(selected, merge_strategy)
        self.collected_data = self._result

        # Emit once and call QWizard.accept directly so ConfigWizard.accept does not
        # emit a second time with raw page data.
        self.wizard_completed.emit(self._result)
        QWizard.accept(self)

    def _apply_replace_baseline(self, mgr, pkg: ModulePackage, mod_name: str, can_persist: bool) -> None:
        """Replace a module's Active configuration and baseline snapshot with the package baseline."""
        if self.project.format_version < 8:
            return
        baseline = baseline_session.compute_new_base(
            pkg, self.project.selected_chip, mgr.module_def, mod_name
        )
        entry = self.project.module_entries.get(mod_name)
        if baseline.has_layers:
            baseline_session.adopt_base(mgr, baseline.base_config)
            if entry is not None:
                entry.pre_unlocked = [k for k in entry.pre_unlocked if k in baseline.pre_keys]
            if can_persist and entry is not None:
                entry.base_hash = baseline_session.write_baseline(
                    self.project, mod_name, baseline
                )
            else:
                baseline.dirty = True
            self.project.baselines[mod_name] = baseline
            if hasattr(self.project, "_pending_baseline_deletes"):
                self.project._pending_baseline_deletes.discard(mod_name)
        else:
            mgr.configuration.containers.clear()
            mgr.configuration._instance_registry.clear()
            mgr.configuration.parameter_values.clear()
            mgr.repair_definition_refs()
            mgr._instance_counters.clear()
            self.project.baselines.pop(mod_name, None)
            if hasattr(self.project, "last_merge_results"):
                self.project.last_merge_results.pop(mod_name, None)
            if entry is not None:
                entry.base_hash = None
                entry.pre_unlocked = []
            if self.project.path is not None and hasattr(self.project, "_pending_baseline_deletes"):
                self.project._pending_baseline_deletes.add(mod_name)
        mgr.baseline_error = None

    def _integrate_modules(self, candidates: List[ModuleCandidate], merge_strategy: str) -> Dict[str, Any]:
        """Add modules to project (baseline merge).

        Strategies:
        - merge: Reconcile Pre/Rec with existing baseline (via MergePreviewDialog or callback)
        - replace: Force Active and baseline snapshot to package Pre/Rec
        - skip: Don't load Pre/Rec configurations
        """
        result = {
            "added": [],
            "failed": [],
            "merge_conflicts": [],
            "merge_rejected": [],
        }

        can_persist = bool(self.project.path)

        def _make_confirm(module_name: str, rejected_flag: List[bool]):
            def _confirm(preview_text: str, merge_result) -> bool:
                if self._confirm_merge is not None:
                    accepted = bool(self._confirm_merge(preview_text, merge_result))
                elif self.parent() is not None:
                    from ..dialogs.merge_preview_dialog import MergePreviewDialog
                    dialog = MergePreviewDialog(self, module_name, preview_text, merge_result)
                    accepted = dialog.exec() == QDialog.Accepted
                else:
                    # Headless programmatic caller without parent/callback keeps legacy auto-accept behavior
                    accepted = True
                if not accepted:
                    rejected_flag[0] = True
                return accepted
            return _confirm

        for cand in candidates:
            try:
                mod_name = cand.package.manifest.module
                rejected_flag = [False]
                confirm_merge = _make_confirm(mod_name, rejected_flag)

                if mod_name in self.project.module_managers:
                    if cand.is_other_variant and merge_strategy == "merge":
                        plan = self.project.switch_module_variant(
                            mod_name,
                            cand.package,
                            cand.lib_index,
                            preview_only=False,
                            confirm=confirm_merge,
                        )
                        if not plan.applied:
                            result["merge_rejected"].append(mod_name)
                        else:
                            result["added"].append(mod_name)
                        mgr = self.project.module_managers.get(mod_name)
                        if mgr is not None and getattr(mgr, "baseline_error", None):
                            result["merge_conflicts"].append({
                                "module": mod_name,
                                "error": mgr.baseline_error,
                            })
                        continue

                    from ...core.config_manager import ConfigurationManager
                    from ...core.parser.ecuc_def_parser import EcucDefParser
                    from ...core.parser.xdm_expression_resolver import apply_chip_expressions
                    from ...core.workspace_manager import (
                        ModuleEntry,
                        _chip_selector_values,
                        _clone_module_configuration,
                    )
                    from ...core import eb_import

                    capture_backup = getattr(self.project, "_capture_module_replace_backup", None)
                    restore_backup = getattr(self.project, "_restore_module_replace_backup", None)
                    backup = capture_backup(mod_name) if callable(capture_backup) else None
                    old_mgr = self.project.module_managers[mod_name]
                    prev_module_def = old_mgr.module_def
                    prev_config = (
                        _clone_module_configuration(old_mgr.configuration)
                        if not cand.is_other_variant
                        else None
                    )
                    try:
                        def_file = cand.package.definition_file(self.project.selected_chip)
                        parser = EcucDefParser()
                        parser.set_selector_values(_chip_selector_values(self.project))
                        module_def = parser.parse_module_def_file(def_file)
                        if getattr(self.project, "ecu_resources", None):
                            apply_chip_expressions(module_def, self.project.ecu_resources)
                        mod_name = module_def.short_name

                        old_entry = self.project.module_entries.get(mod_name)
                        if cand.is_other_variant:
                            temp_cfg = _clone_module_configuration(old_mgr.configuration)
                            mgr = ConfigurationManager(module_def, project_context=self.project)
                            mgr.configuration = temp_cfg
                            for c in temp_cfg.containers:
                                mgr._update_counters_recursive(c)
                            mgr.repair_definition_refs()
                            mgr._cleanup_invalid_parameters()
                            temp_cfg.is_modified = True
                            self.project.module_managers[mod_name] = mgr
                        else:
                            mgr = old_mgr
                            mgr.module_def = module_def

                        self.project.module_defs[mod_name] = def_file
                        self.project.packages[mod_name] = cand.package

                        entry = None
                        if old_entry is not None:
                            entry = ModuleEntry(
                                name=old_entry.name,
                                definition=cand.package.manifest.definition,
                                library=cand.lib_index,
                                config_path=old_entry.config_path,
                                pre_unlocked=list(old_entry.pre_unlocked),
                                package_record=(
                                    eb_import.package_record(cand.package)
                                    if self.project.format_version >= 8
                                    else dict(old_entry.package_record)
                                ),
                                base_hash=old_entry.base_hash,
                            )
                            self.project.module_entries[mod_name] = entry

                        if merge_strategy == "replace":
                            self._apply_replace_baseline(mgr, cand.package, mod_name, can_persist)
                        elif merge_strategy == "skip" and cand.is_other_variant:
                            self.project.baselines.pop(mod_name, None)
                            if hasattr(self.project, "last_merge_results"):
                                self.project.last_merge_results.pop(mod_name, None)
                            if entry is not None:
                                entry.base_hash = None
                                entry.pre_unlocked = []
                            if self.project.path is not None and hasattr(self.project, "_pending_baseline_deletes"):
                                self.project._pending_baseline_deletes.add(mod_name)
                        elif merge_strategy == "merge" and self.project.format_version >= 8 and entry is not None:
                            try:
                                self.project.reconcile_baseline(
                                    mgr, entry, cand.package, confirm_merge
                                )
                            except Exception as exc:
                                self.project.baselines.pop(mod_name, None)
                                mgr.baseline_error = str(exc)

                        if hasattr(self.project, "deduplicate_library_definitions"):
                            self.project.deduplicate_library_definitions()
                        self.project.is_modified = True
                    except Exception:
                        if callable(restore_backup) and backup is not None:
                            restore_backup(backup)
                        if not cand.is_other_variant and prev_config is not None:
                            old_mgr.module_def = prev_module_def
                            old_mgr.configuration = prev_config
                        raise

                    if rejected_flag[0]:
                        result["merge_rejected"].append(mod_name)
                    else:
                        result["added"].append(mod_name)
                    if merge_strategy != "skip" and hasattr(mgr, 'baseline_error') and mgr.baseline_error:
                        result["merge_conflicts"].append({
                            "module": mod_name,
                            "error": mgr.baseline_error,
                        })
                    continue

                if merge_strategy == "skip":
                    mgr = self.project.add_module_from_package(
                        cand.package,
                        lib_index=cand.lib_index,
                        persist=can_persist,
                        confirm=None,
                        reconcile=False,
                        init_baseline=False,
                    )
                elif merge_strategy == "replace":
                    mgr = self.project.add_module_from_package(
                        cand.package,
                        lib_index=cand.lib_index,
                        persist=can_persist,
                        confirm=None,
                        reconcile=False,
                        init_baseline=True,
                    )
                    self._apply_replace_baseline(mgr, cand.package, mgr.module_def.short_name, can_persist)
                else:
                    mgr = self.project.add_module_from_package(
                        cand.package,
                        lib_index=cand.lib_index,
                        persist=can_persist,
                        confirm=confirm_merge,
                        reconcile=True,
                        init_baseline=True,
                    )

                if rejected_flag[0]:
                    result["merge_rejected"].append(mgr.module_def.short_name)
                result["added"].append(mgr.module_def.short_name)

                # Log baseline merge result if applicable
                if merge_strategy != "skip" and hasattr(mgr, 'baseline_error') and mgr.baseline_error:
                    result["merge_conflicts"].append({
                        "module": mgr.module_def.short_name,
                        "error": mgr.baseline_error,
                    })
            except Exception as e:
                result["failed"].append((cand.package.manifest.module, str(e)))

        if result["added"]:
            try:
                if hasattr(self.project, "resolve_all_references"):
                    self.project.resolve_all_references(force=True)
                if hasattr(self.project, "build_reverse_reference_index"):
                    self.project.build_reverse_reference_index()
            except Exception:
                pass

        return result

