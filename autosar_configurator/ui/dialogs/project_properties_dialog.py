"""
Project Properties Dialog
Allows editing project metadata
"""
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QFormLayout,
    QLineEdit, QTextEdit, QDialogButtonBox, QLabel, QGroupBox,
    QWidget, QComboBox, QPushButton
)
from PySide6.QtCore import Qt


class ProjectPropertiesDialog(QDialog):
    """Dialog for editing project properties"""
    
    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.setWindowTitle("Project Properties")
        self.setMinimumWidth(500)
        self.setMinimumHeight(400)
        
        self._setup_ui()
        self._load_data()
    
    def _setup_ui(self):
        """Setup UI"""
        layout = QVBoxLayout(self)
        
        from PySide6.QtWidgets import QTabWidget, QTableWidget, QTableWidgetItem, QHeaderView
        self.tabs = QTabWidget()
        layout.addWidget(self.tabs)
        
        # --- General Tab ---
        general_tab = QWidget()
        general_tab_layout = QVBoxLayout(general_tab)
        
        # General info group
        general_group = QGroupBox("General Information")
        general_layout = QFormLayout(general_group)
        
        self.name_edit = QLineEdit()
        general_layout.addRow("Project Name:", self.name_edit)
        
        self.version_edit = QLineEdit()
        general_layout.addRow("Version:", self.version_edit)
        
        self.author_edit = QLineEdit()
        general_layout.addRow("Author:", self.author_edit)
        
        general_tab_layout.addWidget(general_group)
        
        # Description group
        desc_group = QGroupBox("Description")
        desc_layout = QVBoxLayout(desc_group)
        
        self.description_edit = QTextEdit()
        self.description_edit.setPlaceholderText("Enter project description...")
        desc_layout.addWidget(self.description_edit)
        
        general_tab_layout.addWidget(desc_group)
        
        # Metadata group (read-only)
        meta_group = QGroupBox("Metadata")
        meta_layout = QFormLayout(meta_group)
        
        self.created_label = QLabel()
        meta_layout.addRow("Created:", self.created_label)
        
        self.modules_label = QLabel()
        meta_layout.addRow("Modules:", self.modules_label)
        
        self.path_label = QLabel()
        self.path_label.setWordWrap(True)
        meta_layout.addRow("Location:", self.path_label)
        
        general_tab_layout.addWidget(meta_group)
        
        # Chip Selection group
        chip_group = QGroupBox("ECU/Chip Selection")
        chip_layout = QHBoxLayout(chip_group)
        
        self.chip_combo = QComboBox()
        self.chip_combo.setMinimumWidth(200)
        chip_layout.addWidget(self.chip_combo)
        
        self.refresh_chips_btn = QPushButton("Refresh")
        self.refresh_chips_btn.clicked.connect(self._refresh_chips)
        chip_layout.addWidget(self.refresh_chips_btn)
        
        chip_layout.addStretch()
        
        general_tab_layout.addWidget(chip_group)
        
        self.tabs.addTab(general_tab, "General")
        
        # --- Templates Tab ---
        templates_tab = QWidget()
        templates_layout = QVBoxLayout(templates_tab)
        
        self.templates_table = QTableWidget()
        self.templates_table.setColumnCount(4)
        self.templates_table.setHorizontalHeaderLabels(["Module", "Template Type", "Engine", "Source Path"])
        self.templates_table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.templates_table.horizontalHeader().setSectionResizeMode(3, QHeaderView.Stretch)
        templates_layout.addWidget(self.templates_table)
        
        self.tabs.addTab(templates_tab, "Templates")
        
        # Buttons
        buttons = QDialogButtonBox(
            QDialogButtonBox.Ok | QDialogButtonBox.Cancel
        )
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)
    
    def _load_data(self):
        """Load project data into form"""
        self.name_edit.setText(self.project.name)
        self.version_edit.setText(getattr(self.project, 'version', '1.0.0'))
        self.author_edit.setText(getattr(self.project, 'author', ''))
        self.description_edit.setPlainText(getattr(self.project, 'description', ''))
        
        # Metadata (read-only)
        created = getattr(self.project, 'created_date', 'Unknown')
        if 'T' in created:
            # Format ISO datetime
            created = created.split('T')[0] + ' ' + created.split('T')[1][:8]
        self.created_label.setText(created)
        
        module_count = len(self.project.module_managers)
        module_names = ', '.join(self.project.module_managers.keys())
        self.modules_label.setText(f"{module_count} ({module_names})")
        
        if self.project.path:
            self.path_label.setText(str(self.project.path.parent))
        else:
            self.path_label.setText("Not saved")
        
        # Load chip selection
        self._populate_chip_combo()
            
        # --- Populate Templates Table ---
        from ...generator.generator import CodeGenerator
        from pathlib import Path
        
        project_template_dir = None
        if self.project.path:
            project_template_dir = self.project.path.parent / "templates"
            
        self.templates_table.setRowCount(0)
        
        for module_name, manager in self.project.module_managers.items():
            if not manager.configuration:
                continue
                
            generator = CodeGenerator(
                manager.module_def,
                manager.configuration,
                project_template_dir=project_template_dir if project_template_dir and project_template_dir.exists() else None
            )
            
            infos = generator.get_template_info(module_name)
            for info in infos:
                row = self.templates_table.rowCount()
                self.templates_table.insertRow(row)
                
                from PySide6.QtWidgets import QTableWidgetItem
                from PySide6.QtGui import QColor
                
                self.templates_table.setItem(row, 0, QTableWidgetItem(module_name))
                self.templates_table.setItem(row, 1, QTableWidgetItem(info['type']))
                
                engine_item = QTableWidgetItem(info['engine'])
                if info['engine'] == "EB":
                    engine_item.setForeground(QColor("#0066CC"))  # Blue for EB
                self.templates_table.setItem(row, 2, engine_item)
                
                source_item = QTableWidgetItem(info['path'])
                if "Fallback" in info['path']:
                    source_item.setForeground(QColor("#888888"))
                self.templates_table.setItem(row, 3, source_item)
    
    def _populate_chip_combo(self):
        """Populate chip selection combo box"""
        self.chip_combo.clear()
        self.chip_combo.addItem("(Auto-detect / All)", None)
        
        # Read available chips from project
        available = self.project.available_chips or []
        for chip in available:
            self.chip_combo.addItem(chip, chip)
        
        # Set current selection
        current = self.project.selected_chip
        if current:
            idx = self.chip_combo.findData(current)
            if idx >= 0:
                self.chip_combo.setCurrentIndex(idx)
    
    def _refresh_chips(self):
        """Refresh available chips from project"""
        self.project.discover_available_chips()
        self._populate_chip_combo()
    
    def get_data(self):
        """Get updated project data"""
        return {
            'name': self.name_edit.text(),
            'version': self.version_edit.text(),
            'author': self.author_edit.text(),
            'description': self.description_edit.toPlainText(),
            'selected_chip': self.chip_combo.currentData()
        }
