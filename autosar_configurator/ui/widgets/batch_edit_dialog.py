"""
Batch edit dialog for modifying multiple configuration elements
"""
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, 
    QPushButton, QComboBox, QFormLayout, QMessageBox, QGroupBox
)
from PySide6.QtCore import Qt
from typing import List, Optional, Any

from ...core.model.container import Container, Parameter
from ...core.command import CommandManager, ModifyParameterCommand, ModifyContainerCommand, BatchCommand


class BatchEditDialog(QDialog):
    """Dialog for batch editing configuration elements"""
    
    def __init__(self, elements: List[Any], command_manager: CommandManager, parent=None):
        super().__init__(parent)
        
        self.elements = elements
        self.command_manager = command_manager
        self.target_type = self._determine_target_type()
        
        self._setup_ui()
        
        self.setWindowTitle("Batch Edit")
        self.setMinimumSize(400, 300)
        self.setModal(True)
        
    def _determine_target_type(self):
        """Determine the common type of selected elements"""
        if not self.elements:
            return None
            
        first_type = type(self.elements[0])
        if all(isinstance(e, first_type) for e in self.elements):
            return first_type
        return None
        
    def _setup_ui(self):
        """Setup the user interface"""
        layout = QVBoxLayout(self)
        
        # Info section
        info_group = QGroupBox("Selection Info")
        info_layout = QFormLayout(info_group)
        info_layout.addRow("Selected Items:", QLabel(str(len(self.elements))))
        
        type_str = "Mixed"
        if self.target_type == Container:
            type_str = "Containers"
        elif self.target_type == Parameter:
            type_str = "Parameters"
            
        info_layout.addRow("Item Type:", QLabel(type_str))
        layout.addWidget(info_group)
        
        if not self.target_type:
            layout.addWidget(QLabel("Cannot batch edit mixed types."))
            self.ok_button = QPushButton("Close")
            self.ok_button.clicked.connect(self.reject)
            layout.addWidget(self.ok_button)
            return
            
        # Edit section
        edit_group = QGroupBox("Edit Properties")
        edit_layout = QFormLayout(edit_group)
        
        self.property_combo = QComboBox()
        
        self.value_input = QLineEdit()
        
        # Connect signal after creating value_input
        self.property_combo.currentIndexChanged.connect(self._on_property_changed)
        
        if self.target_type == Parameter:
            self.property_combo.addItems(["value", "description", "value_type"])
        elif self.target_type == Container:
            self.property_combo.addItems(["description"])
            
        edit_layout.addRow("Property:", self.property_combo)
        edit_layout.addRow("New Value:", self.value_input)
        
        layout.addWidget(edit_group)
        
        # Buttons
        button_layout = QHBoxLayout()
        button_layout.addStretch()
        
        self.cancel_button = QPushButton("Cancel")
        self.cancel_button.clicked.connect(self.reject)
        button_layout.addWidget(self.cancel_button)
        
        self.apply_button = QPushButton("Apply")
        self.apply_button.setDefault(True)
        self.apply_button.clicked.connect(self._apply_changes)
        button_layout.addWidget(self.apply_button)
        
        layout.addLayout(button_layout)
        
    def _on_property_changed(self):
        """Handle property selection change"""
        self.value_input.clear()
        self.value_input.setPlaceholderText(f"Enter new {self.property_combo.currentText()}")
        
    def _apply_changes(self):
        """Apply changes to all selected elements"""
        prop_name = self.property_combo.currentText()
        new_value = self.value_input.text()
        
        # Type conversion for parameters
        if self.target_type == Parameter and prop_name == "value":
            # Try to infer type from first element or keep as string
            # In a real app, we would check value_type of each parameter
            pass
            
        commands = []
        for element in self.elements:
            old_value = getattr(element, prop_name, None)
            
            # Skip if value hasn't changed
            if str(old_value) == new_value:
                continue
                
            if self.target_type == Parameter:
                # Simple type conversion
                final_value = new_value
                if element.value_type == "INTEGER":
                    try:
                        final_value = int(new_value)
                    except ValueError:
                        pass # Keep as string or handle error
                elif element.value_type == "BOOLEAN":
                    final_value = new_value.lower() in ('true', '1', 'yes')
                    
                cmd = ModifyParameterCommand(element, prop_name, old_value, final_value)
                commands.append(cmd)
                
            elif self.target_type == Container:
                cmd = ModifyContainerCommand(element, prop_name, old_value, new_value)
                commands.append(cmd)
                
        if commands:
            batch_cmd = BatchCommand(commands, description=f"Batch modify {prop_name} for {len(commands)} items")
            self.command_manager.execute_command(batch_cmd)
            self.accept()
        else:
            QMessageBox.information(self, "No Changes", "No changes were made.")
