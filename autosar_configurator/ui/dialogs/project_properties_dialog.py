"""
Project Properties Dialog
Allows editing project metadata
"""
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QFormLayout,
    QLineEdit, QTextEdit, QDialogButtonBox, QLabel, QGroupBox
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
        
        # General info group
        general_group = QGroupBox("General Information")
        general_layout = QFormLayout(general_group)
        
        self.name_edit = QLineEdit()
        general_layout.addRow("Project Name:", self.name_edit)
        
        self.version_edit = QLineEdit()
        general_layout.addRow("Version:", self.version_edit)
        
        self.author_edit = QLineEdit()
        general_layout.addRow("Author:", self.author_edit)
        
        layout.addWidget(general_group)
        
        # Description group
        desc_group = QGroupBox("Description")
        desc_layout = QVBoxLayout(desc_group)
        
        self.description_edit = QTextEdit()
        self.description_edit.setPlaceholderText("Enter project description...")
        desc_layout.addWidget(self.description_edit)
        
        layout.addWidget(desc_group)
        
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
        
        layout.addWidget(meta_group)
        
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
    
    def get_data(self):
        """Get updated project data"""
        return {
            'name': self.name_edit.text(),
            'version': self.version_edit.text(),
            'author': self.author_edit.text(),
            'description': self.description_edit.toPlainText()
        }
