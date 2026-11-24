import copy
import re
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QListWidget, QListWidgetItem,
    QPushButton, QDialogButtonBox, QInputDialog, QMessageBox,
    QLabel, QLineEdit, QFrame, QStyle
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QIcon
from ...core.model.configuration_model import DEFAULT_VARIANT

_INVALID_VARIANT_CHARS = re.compile(r'[/\\:*?"<>|]')


def _is_valid_variant_name(name: str) -> bool:
    if not name or name in (".", "..") or ".." in name:
        return False
    return not bool(_INVALID_VARIANT_CHARS.search(name))


class VariantManagementDialog(QDialog):
    """
    Advanced Variant Management Dialog with override statistics.
    """
    
    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.changed = False
        self._snapshot = self._capture_snapshot()
        self.setWindowTitle("Manage Project Variants")
        self.setMinimumWidth(500)
        self.setMinimumHeight(400)
        
        self._setup_ui()
        self._load_variants()

    def _capture_snapshot(self):
        container_variants = []

        def walk(c):
            container_variants.append((c, getattr(c, "variant", None), getattr(c, "is_modified", False)))
            for sub in getattr(c, "sub_containers", []) or []:
                walk(sub)

        mod_overrides = {}
        mod_modified = {}
        for name, mgr in (getattr(self.project, "module_managers", None) or {}).items():
            cfg = getattr(mgr, "configuration", None)
            if cfg is not None:
                mod_overrides[name] = copy.deepcopy(getattr(cfg, "variant_overrides", {}))
                mod_modified[name] = getattr(cfg, "is_modified", False)
                for top in getattr(cfg, "containers", []) or []:
                    walk(top)
        return {
            "variants": list(getattr(self.project, "variants", []) or []),
            "active_variant": getattr(self.project, "active_variant", DEFAULT_VARIANT),
            "is_modified": getattr(self.project, "is_modified", False),
            "unloaded_overrides": copy.deepcopy(getattr(self.project, "unloaded_variant_overrides", {})),
            "mod_overrides": mod_overrides,
            "mod_modified": mod_modified,
            "container_variants": container_variants,
        }

    def _restore_snapshot(self):
        snap = self._snapshot
        self.project.variants = list(snap["variants"])
        self.project.active_variant = snap["active_variant"]
        self.project.is_modified = snap["is_modified"]
        self.changed = False
        if hasattr(self.project, "unloaded_variant_overrides"):
            self.project.unloaded_variant_overrides = copy.deepcopy(snap["unloaded_overrides"])
        for name, mgr in (getattr(self.project, "module_managers", None) or {}).items():
            cfg = getattr(mgr, "configuration", None)
            if cfg is not None and name in snap["mod_overrides"]:
                cfg.variant_overrides = copy.deepcopy(snap["mod_overrides"][name])
                cfg.is_modified = snap["mod_modified"][name]
        for c, var_val, c_mod in snap["container_variants"]:
            c.variant = var_val
            c.is_modified = c_mod

    def reject(self):
        self._restore_snapshot()
        super().reject()
        
    def _setup_ui(self):
        layout = QVBoxLayout(self)
        
        # Header Info
        header = QLabel("Manage variants and view parameter override statistics.")
        header.setStyleSheet("color: #666; margin-bottom: 5px;")
        layout.addWidget(header)
        
        # Search Box
        search_layout = QHBoxLayout()
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Filter variants...")
        self.search_input.textChanged.connect(self._on_filter_changed)
        search_layout.addWidget(self.search_input)
        layout.addLayout(search_layout)
        
        # List and Stats
        content_layout = QHBoxLayout()
        
        # Left: List of Variants
        self.list_widget = QListWidget()
        self.list_widget.currentRowChanged.connect(self._on_variant_selected)
        content_layout.addWidget(self.list_widget, 2)
        
        # Right: Details / Stats
        self.details_frame = QFrame()
        self.details_frame.setFrameShape(QFrame.StyledPanel)
        stats_layout = QVBoxLayout(self.details_frame)
        
        self.variant_title = QLabel("Select a variant")
        self.variant_title.setStyleSheet("font-weight: bold; font-size: 14px;")
        stats_layout.addWidget(self.variant_title)
        
        self.stats_label = QLabel("")
        self.stats_label.setWordWrap(True)
        self.stats_label.setAlignment(Qt.AlignTop)
        stats_layout.addWidget(self.stats_label)
        
        stats_layout.addStretch()
        content_layout.addWidget(self.details_frame, 3)
        
        layout.addLayout(content_layout)
        
        # Action Buttons
        btn_layout = QHBoxLayout()
        
        self.add_btn = QPushButton("Add New")
        self.add_btn.setIcon(self.style().standardIcon(QStyle.SP_FileIcon))
        self.add_btn.clicked.connect(self._add_variant)
        btn_layout.addWidget(self.add_btn)
        
        self.clone_btn = QPushButton("Clone Selected")
        self.clone_btn.setIcon(self.style().standardIcon(QStyle.SP_DialogSaveButton))
        self.clone_btn.clicked.connect(self._clone_variant)
        btn_layout.addWidget(self.clone_btn)
        
        self.remove_btn = QPushButton("Remove")
        self.remove_btn.setIcon(self.style().standardIcon(QStyle.SP_TrashIcon))
        self.remove_btn.clicked.connect(self._remove_variant)
        btn_layout.addWidget(self.remove_btn)
        
        btn_layout.addStretch()
        layout.addLayout(btn_layout)
        
        # Bottom Buttons
        self.buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        self.buttons.accepted.connect(self.accept)
        self.buttons.rejected.connect(self.reject)
        layout.addWidget(self.buttons)
        
    def _load_variants(self):
        self.list_widget.clear()
        for variant in self.project.variants:
            item = QListWidgetItem(variant)
            if variant == self.project.active_variant:
                item.setIcon(self.style().standardIcon(QStyle.SP_ArrowRight))
                item.setToolTip("Active Variant")
            else:
                item.setIcon(self.style().standardIcon(QStyle.SP_DirIcon))
            self.list_widget.addItem(item)
            
    def _on_filter_changed(self, text):
        for i in range(self.list_widget.count()):
            item = self.list_widget.item(i)
            item.setHidden(text.lower() not in item.text().lower())
            
    def _on_variant_selected(self, index):
        if index < 0:
            self.variant_title.setText("Select a variant")
            self.stats_label.setText("")
            self.remove_btn.setEnabled(False)
            return
            
        variant_name = self.list_widget.item(index).text()
        self.variant_title.setText(f"Variant: {variant_name}")
        self.remove_btn.setEnabled(variant_name != DEFAULT_VARIANT)

        def _count_assigned(containers) -> int:
            cnt = 0
            for c in containers or ():
                if getattr(c, "variant", None) == variant_name:
                    cnt += 1
                cnt += _count_assigned(getattr(c, "sub_containers", None))
            return cnt
        
        # Calculate stats
        total_overrides = 0
        total_containers = 0
        module_stats = []
        
        for name, manager in self.project.module_managers.items():
            cfg = getattr(manager, "configuration", None)
            if cfg is None:
                continue
            count = cfg.get_variant_overrides_count(variant_name)
            c_count = _count_assigned(getattr(cfg, "containers", None))
            if count > 0 or c_count > 0:
                total_overrides += count
                total_containers += c_count
                parts = []
                if count > 0:
                    parts.append(f"{count} overrides")
                if c_count > 0:
                    parts.append(f"{c_count} assigned containers")
                module_stats.append(f" - {name}: {', '.join(parts)}")
                
        status = "Active" if variant_name == self.project.active_variant else "Inactive"
        
        stats_text = f"Status: {status}\n\n"
        stats_text += f"Total Parameter Overrides: {total_overrides}\n"
        stats_text += f"Total Assigned Containers: {total_containers}\n"
        if module_stats:
            stats_text += "\nModule Breakdown:\n" + "\n".join(module_stats)
        else:
            stats_text += "\nNo overrides or assigned containers defined for this variant."
            
        self.stats_label.setText(stats_text)
        
    def _add_variant(self):
        name, ok = QInputDialog.getText(self, "Add Variant", "Enter unique variant name:")
        if ok and name.strip():
            name = name.strip()
            if not _is_valid_variant_name(name):
                QMessageBox.warning(self, "Error", "Invalid variant name (path characters are not allowed)!")
                return
            if name in self.project.variants:
                QMessageBox.warning(self, "Error", "Variant already exists!")
                return
            self.project.variants.append(name)
            self.project.is_modified = True
            self.changed = True
            self._load_variants()
            
    def _clone_variant(self):
        current = self.list_widget.currentItem()
        if not current:
            return
            
        src_name = current.text()
        new_name, ok = QInputDialog.getText(self, "Clone Variant", f"New name for clone of '{src_name}':")
        if ok and new_name.strip():
            new_name = new_name.strip()
            if not _is_valid_variant_name(new_name):
                QMessageBox.warning(self, "Error", "Invalid variant name (path characters are not allowed)!")
                return
            if new_name in self.project.variants:
                QMessageBox.warning(self, "Error", "Variant already exists!")
                return
                
            # Add to list
            self.project.variants.append(new_name)
            self.project.is_modified = True
            self.changed = True
            
            # Clone overrides across all modules
            for manager in self.project.module_managers.values():
                config = manager.configuration
                if src_name in config.variant_overrides:
                    config.variant_overrides[new_name] = copy.deepcopy(config.variant_overrides[src_name])
                    config.is_modified = True
            for unloaded_ov in (getattr(self.project, "unloaded_variant_overrides", None) or {}).values():
                if isinstance(unloaded_ov, dict) and src_name in unloaded_ov:
                    unloaded_ov[new_name] = copy.deepcopy(unloaded_ov[src_name])
            
            self._load_variants()
            
    def _remove_variant(self):
        current = self.list_widget.currentItem()
        if not current:
            return
            
        name = current.text()
        if name == DEFAULT_VARIANT:
            QMessageBox.warning(self, "Cannot Delete Default", "The 'Default' base variant cannot be deleted.")
            return
        if QMessageBox.question(self, "Confirm", f"Delete variant '{name}' and all its overrides?") == QMessageBox.Yes:
            self.project.variants.remove(name)
            if self.project.active_variant == name:
                self.project.active_variant = DEFAULT_VARIANT if DEFAULT_VARIANT in self.project.variants else (
                    self.project.variants[0] if self.project.variants else DEFAULT_VARIANT
                )
            self.project.is_modified = True
            self.changed = True

            def clear_container_variant(c, cfg):
                if getattr(c, "variant", None) == name:
                    c.variant = None
                    c.mark_modified()
                    cfg.is_modified = True
                for sub in getattr(c, "sub_containers", []) or []:
                    clear_container_variant(sub, cfg)
            
            # Remove from all modules and clear container.variant assignments
            for manager in self.project.module_managers.values():
                cfg = manager.configuration
                if name in cfg.variant_overrides:
                    del cfg.variant_overrides[name]
                    cfg.is_modified = True
                for top in getattr(cfg, "containers", []) or []:
                    clear_container_variant(top, cfg)
            for unloaded_ov in (getattr(self.project, "unloaded_variant_overrides", None) or {}).values():
                if isinstance(unloaded_ov, dict) and name in unloaded_ov:
                    del unloaded_ov[name]
                    
            self._load_variants()
