from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QListWidget, QListWidgetItem,
    QPushButton, QDialogButtonBox, QInputDialog, QMessageBox,
    QLabel, QLineEdit, QFrame, QStyle
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QIcon

class VariantManagementDialog(QDialog):
    """
    Advanced Variant Management Dialog with override statistics.
    """
    
    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.setWindowTitle("Manage Project Variants")
        self.setMinimumWidth(500)
        self.setMinimumHeight(400)
        
        self._setup_ui()
        self._load_variants()
        
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
            return
            
        variant_name = self.list_widget.item(index).text()
        self.variant_title.setText(f"Variant: {variant_name}")
        
        # Calculate stats
        total_overrides = 0
        module_stats = []
        
        for name, manager in self.project.module_managers.items():
            count = manager.configuration.get_variant_overrides_count(variant_name)
            if count > 0:
                total_overrides += count
                module_stats.append(f" - {name}: {count} overrides")
                
        status = "Active" if variant_name == self.project.active_variant else "Inactive"
        
        stats_text = f"Status: {status}\n\n"
        stats_text += f"Total Parameter Overrides: {total_overrides}\n"
        if module_stats:
            stats_text += "\nModule Breakdown:\n" + "\n".join(module_stats)
        else:
            stats_text += "\nNo overrides defined for this variant."
            
        self.stats_label.setText(stats_text)
        
    def _add_variant(self):
        name, ok = QInputDialog.getText(self, "Add Variant", "Enter unique variant name:")
        if ok and name.strip():
            name = name.strip()
            if name in self.project.variants:
                QMessageBox.warning(self, "Error", "Variant already exists!")
                return
            self.project.variants.append(name)
            self._load_variants()
            
    def _clone_variant(self):
        current = self.list_widget.currentItem()
        if not current:
            return
            
        src_name = current.text()
        new_name, ok = QInputDialog.getText(self, "Clone Variant", f"New name for clone of '{src_name}':")
        if ok and new_name.strip():
            new_name = new_name.strip()
            if new_name in self.project.variants:
                QMessageBox.warning(self, "Error", "Variant already exists!")
                return
                
            # Add to list
            self.project.variants.append(new_name)
            
            # Clone overrides across all modules
            for manager in self.project.module_managers.values():
                config = manager.configuration
                if src_name in config.variant_overrides:
                    config.variant_overrides[new_name] = config.variant_overrides[src_name].copy()
            
            self._load_variants()
            
    def _remove_variant(self):
        current = self.list_widget.currentItem()
        if not current:
            return
            
        name = current.text()
        if QMessageBox.question(self, "Confirm", f"Delete variant '{name}' and all its overrides?") == QMessageBox.Yes:
            self.project.variants.remove(name)
            if self.project.active_variant == name:
                self.project.active_variant = None
            
            # Remove from all modules
            for manager in self.project.module_managers.values():
                if name in manager.configuration.variant_overrides:
                    del manager.configuration.variant_overrides[name]
                    
            self._load_variants()
