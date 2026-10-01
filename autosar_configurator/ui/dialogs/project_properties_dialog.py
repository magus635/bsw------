"""
Project Properties Dialog
Allows editing project metadata
"""
from pathlib import Path
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QFormLayout,
    QLineEdit, QTextEdit, QDialogButtonBox, QLabel, QGroupBox,
    QWidget, QComboBox, QPushButton, QScrollArea, QAbstractItemView,
    QTabWidget, QTableWidget, QTableWidgetItem, QHeaderView
)
from PySide6.QtCore import Qt, QUrl, QTimer
from PySide6.QtGui import QGuiApplication, QDesktopServices, QColor


class ProjectPropertiesDialog(QDialog):
    """Dialog for editing project properties"""
    
    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.setWindowTitle("Project Properties")
        self.resize(680, 620)
        self.setMinimumWidth(560)
        self.setMinimumHeight(480)
        
        self._setup_ui()
        self._load_data()
    
    def _setup_ui(self):
        """Setup UI"""
        layout = QVBoxLayout(self)
        layout.setContentsMargins(14, 14, 14, 14)
        layout.setSpacing(10)
        
        self.tabs = QTabWidget()
        layout.addWidget(self.tabs)
        
        # --- General Tab ---
        general_tab = QWidget()
        general_tab_layout = QVBoxLayout(general_tab)
        general_tab_layout.setContentsMargins(12, 12, 12, 12)
        general_tab_layout.setSpacing(12)
        
        # General info group
        general_group = QGroupBox("General Information")
        general_layout = QFormLayout(general_group)
        general_layout.setLabelAlignment(Qt.AlignRight)
        general_layout.setFieldGrowthPolicy(QFormLayout.ExpandingFieldsGrow)
        general_layout.setHorizontalSpacing(10)
        general_layout.setVerticalSpacing(8)
        
        self.name_edit = QLineEdit()
        general_layout.addRow("Project Name:", self.name_edit)
        
        self.version_edit = QLineEdit()
        general_layout.addRow("Version:", self.version_edit)
        
        self.author_edit = QLineEdit()
        general_layout.addRow("Author:", self.author_edit)
        
        general_tab_layout.addWidget(general_group)
        
        # Metadata group (read-only)
        meta_group = QGroupBox("Metadata")
        meta_layout = QFormLayout(meta_group)
        meta_layout.setLabelAlignment(Qt.AlignRight)
        meta_layout.setFieldGrowthPolicy(QFormLayout.ExpandingFieldsGrow)
        meta_layout.setHorizontalSpacing(10)
        meta_layout.setVerticalSpacing(8)
        
        self.created_label = QLabel()
        meta_layout.addRow("Created:", self.created_label)
        
        # Location row with path display, copy, and open folder buttons
        path_container = QWidget()
        path_layout = QHBoxLayout(path_container)
        path_layout.setContentsMargins(0, 0, 0, 0)
        path_layout.setSpacing(6)
        
        self.path_edit = QLineEdit()
        self.path_edit.setReadOnly(True)
        self.path_label = self.path_edit  # Backward-compatibility alias
        
        self.copy_path_btn = QPushButton("Copy")
        self.copy_path_btn.setToolTip("Copy path to clipboard")
        self.copy_path_btn.clicked.connect(self._copy_path)
        
        self.open_folder_btn = QPushButton("Open Folder")
        self.open_folder_btn.setToolTip("Open containing folder in file manager")
        self.open_folder_btn.clicked.connect(self._open_folder)
        
        path_layout.addWidget(self.path_edit)
        path_layout.addWidget(self.copy_path_btn)
        path_layout.addWidget(self.open_folder_btn)
        meta_layout.addRow("Location:", path_container)
        
        # Modules row with count label and wrapped multi-line text edit
        modules_container = QWidget()
        modules_layout = QVBoxLayout(modules_container)
        modules_layout.setContentsMargins(0, 0, 0, 0)
        modules_layout.setSpacing(4)
        
        self.modules_label = QLabel()
        self.modules_label.setStyleSheet("color: #666; font-size: 11px;")
        modules_layout.addWidget(self.modules_label)
        
        self.modules_text = QTextEdit()
        self.modules_text.setReadOnly(True)
        self.modules_text.setMinimumHeight(65)
        self.modules_text.setMaximumHeight(90)
        self.modules_text.setPlaceholderText("No modules configured")
        modules_layout.addWidget(self.modules_text)
        
        meta_layout.addRow("Modules:", modules_container)
        
        general_tab_layout.addWidget(meta_group)
        
        # Chip Selection group
        chip_group = QGroupBox("ECU/Chip Selection")
        chip_layout = QHBoxLayout(chip_group)
        chip_layout.setContentsMargins(10, 10, 10, 10)
        chip_layout.setSpacing(8)
        
        chip_label = QLabel("Target ECU / Chip:")
        chip_layout.addWidget(chip_label)
        
        self.chip_combo = QComboBox()
        self.chip_combo.setMinimumWidth(220)
        chip_layout.addWidget(self.chip_combo)
        
        self.refresh_chips_btn = QPushButton("Refresh")
        self.refresh_chips_btn.clicked.connect(self._refresh_chips)
        chip_layout.addWidget(self.refresh_chips_btn)
        
        chip_layout.addStretch()
        general_tab_layout.addWidget(chip_group)
        
        # Description group
        desc_group = QGroupBox("Description")
        desc_layout = QVBoxLayout(desc_group)
        desc_layout.setContentsMargins(10, 10, 10, 10)
        
        self.description_edit = QTextEdit()
        self.description_edit.setPlaceholderText("Enter project description...")
        self.description_edit.setMinimumHeight(60)
        self.description_edit.setMaximumHeight(85)
        desc_layout.addWidget(self.description_edit)
        
        general_tab_layout.addWidget(desc_group)
        
        # Stretch at bottom of scrollable general tab to prevent awkward spacing
        general_tab_layout.addStretch()
        
        # Wrap general tab in QScrollArea
        general_scroll = QScrollArea()
        general_scroll.setWidgetResizable(True)
        general_scroll.setFrameShape(QScrollArea.NoFrame)
        general_scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        general_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        general_scroll.setWidget(general_tab)
        
        self.tabs.addTab(general_scroll, "General")
        
        # --- Templates Tab ---
        templates_tab = QWidget()
        templates_layout = QVBoxLayout(templates_tab)
        templates_layout.setContentsMargins(12, 12, 12, 12)
        
        self.templates_table = QTableWidget()
        self.templates_table.setColumnCount(4)
        self.templates_table.setHorizontalHeaderLabels(["Module", "Template Type", "Engine", "Source Path"])
        self.templates_table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.templates_table.horizontalHeader().setSectionResizeMode(3, QHeaderView.Stretch)
        self.templates_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.templates_table.setAlternatingRowColors(True)
        self.templates_table.setSelectionBehavior(QAbstractItemView.SelectRows)
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
        self.name_edit.setText(getattr(self.project, 'name', '') or '')
        self.version_edit.setText(getattr(self.project, 'version', '1.0.0') or '1.0.0')
        self.author_edit.setText(getattr(self.project, 'author', '') or '')
        self.description_edit.setPlainText(getattr(self.project, 'description', '') or '')
        
        # Metadata (read-only)
        created = getattr(self.project, 'created_date', 'Unknown') or 'Unknown'
        if 'T' in str(created):
            parts = str(created).split('T')
            created = parts[0] + ' ' + parts[1][:8]
        self.created_label.setText(str(created))
        
        module_managers = getattr(self.project, 'module_managers', {}) or {}
        module_count = len(module_managers)
        sorted_modules = sorted(module_managers.keys())
        self.modules_label.setText(f"{module_count} modules configured:")
        if sorted_modules:
            self.modules_text.setPlainText(', '.join(sorted_modules))
        else:
            self.modules_text.setPlainText("No modules configured")
        
        if self.project.path:
            folder_path = str(self.project.path.parent)
            self.path_edit.setText(folder_path)
            self.path_edit.setCursorPosition(0)
            self.path_edit.setToolTip(folder_path)
            self.copy_path_btn.setEnabled(True)
            self.open_folder_btn.setEnabled(True)
        else:
            self.path_edit.setText("Not saved")
            self.path_edit.setToolTip("")
            self.copy_path_btn.setEnabled(False)
            self.open_folder_btn.setEnabled(False)
        
        # Load chip selection
        self._populate_chip_combo()
            
        # --- Populate Templates Table ---
        from ...generator.generator import CodeGenerator
        
        project_template_dir = None
        if self.project.path:
            project_template_dir = self.project.path.parent / "templates"
            
        self.templates_table.setRowCount(0)
        
        for module_name, manager in module_managers.items():
            if not manager or not getattr(manager, 'configuration', None):
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
        available = getattr(self.project, 'available_chips', []) or []
        for chip in available:
            self.chip_combo.addItem(chip, chip)
        
        # Set current selection
        current = getattr(self.project, 'selected_chip', None)
        if current:
            idx = self.chip_combo.findData(current)
            if idx >= 0:
                self.chip_combo.setCurrentIndex(idx)
    
    def _refresh_chips(self):
        """Refresh available chips from project"""
        if hasattr(self.project, 'discover_available_chips'):
            self.project.discover_available_chips()
        self._populate_chip_combo()
    
    def _copy_path(self):
        """Copy project path to clipboard"""
        path = self.path_edit.text()
        if path and path != "Not saved":
            QGuiApplication.clipboard().setText(path)
            self.copy_path_btn.setText("Copied!")
            QTimer.singleShot(1500, lambda: self.copy_path_btn.setText("Copy"))
    
    def _open_folder(self):
        """Open containing folder in system file manager"""
        if self.project and getattr(self.project, 'path', None):
            folder = self.project.path.parent
            if folder.exists():
                QDesktopServices.openUrl(QUrl.fromLocalFile(str(folder)))
    
    def get_data(self):
        """Get updated project data"""
        return {
            'name': self.name_edit.text(),
            'version': self.version_edit.text(),
            'author': self.author_edit.text(),
            'description': self.description_edit.toPlainText(),
            'selected_chip': self.chip_combo.currentData()
        }
