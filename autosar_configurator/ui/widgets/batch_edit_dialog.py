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
    """Dialog for batch editing configuration elements

    A locked Pre value (design §6.5 D1) is skipped, never written: the merge would force it
    back on the next open. The skipped items are listed once, sorted, after the batch has run.
    ``check_locked`` is the lock check (``ConfigurationManager.check_editable``, or one of the
    same shape); without it nothing is skipped, which is what the legacy model needs.
    """

    def __init__(self, elements: List[Any], command_manager: CommandManager, parent=None,
                 check_locked=None):
        super().__init__(parent)

        self.elements = elements
        self.command_manager = command_manager
        self.check_locked = check_locked
        self.skipped_locked: List[str] = []
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
        self.skipped_locked = []
        for element in self.elements:
            old_value = getattr(element, prop_name, None)

            # Skip if value hasn't changed
            if str(old_value) == new_value:
                continue

            key = self._locked_key(element, prop_name)
            if key is not None:
                self.skipped_locked.append(key)
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
                
        if self.skipped_locked:
            listed = "\n".join(f"  • {key}" for key in sorted(self.skipped_locked))
            QMessageBox.information(
                self, "已跳过锁定的预配置值",
                f"以下 {len(self.skipped_locked)} 项是预配置（PRE），已锁定，未修改：\n\n"
                f"{listed}\n\n如需修改，请在参数面板中右键选择“解锁此参数”。")

        if commands:
            batch_cmd = BatchCommand(commands, description=f"Batch modify {prop_name} for {len(commands)} items")
            self.command_manager.execute_command(batch_cmd)
            self.accept()
        else:
            QMessageBox.information(self, "No Changes", "No changes were made.")

    def _locked_key(self, element: Any, prop_name: str) -> Optional[str]:
        """The locked Pre key of ``element``, or ``None`` when it may be written.

        Only the value itself is locked, not the description: an editor that renames or
        annotates a container is not changing the Pre value the merge owns.
        """
        if self.check_locked is None or prop_name != "value":
            return None
        name = getattr(element, "name", None) or getattr(element, "short_name", None)
        if not name:
            return None
        try:
            self.check_locked(element, name)
        except ValueError as exc:            # PreLockedError is a ValueError
            return getattr(exc, "key", name)
        return None
