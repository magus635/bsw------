"""
DaVinci-style Config Panel
Shows editable parameters for selected container instance
"""
from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QFormLayout, QLabel, QLineEdit,
    QComboBox, QSpinBox, QDoubleSpinBox,QCheckBox, QTextEdit,
    QGroupBox, QTableWidget, QTableWidgetItem, QScrollArea,
    QHeaderView
)
from PySide6.QtCore import Qt, Signal
from typing import Optional

from ...core.model.definition_model import EcucContainerDef, EcucParameterDef, EcucParameterType
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager


class DaVinciConfigPanel(QWidget):
    """Config panel for editing container instance parameters"""
    
    # Signals
    parameter_changed = Signal(EcucContainerValue, str, object)  # instance, param_name, value
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.current_instance: Optional[EcucContainerValue] = None
        self.current_def: Optional[EcucContainerDef] = None
        self.config_manager: Optional[ConfigurationManager] = None
        
        self._setup_ui()
    
    def _setup_ui(self):
        """Setup UI"""
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        
        # Scroll area
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setFrameShape(QScrollArea.NoFrame)
        
        # Content widget
        content = QWidget()
        self.content_layout = QVBoxLayout(content)
        
        # Empty message
        self.empty_label = QLabel("Select a container instance to edit parameters")
        self.empty_label.setAlignment(Qt.AlignCenter)
        self.content_layout.addWidget(self.empty_label)
        
        scroll.setWidget(content)
        layout.addWidget(scroll)
        
        # Create widgets (initially hidden)
        self._create_general_group()
        self._create_parameters_group()
        
        self.general_group.hide()
        self.parameters_group.hide()
    
    def _create_general_group(self):
        """Create general information group"""
        self.general_group = QGroupBox("📋 General Information")
        general_layout = QFormLayout(self.general_group)
        
        self.name_label = QLabel()
        self.name_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        general_layout.addRow("Instance Name:", self.name_label)
        
        self.def_label = QLabel()
        self.def_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        general_layout.addRow("Definition:", self.def_label)
        
        self.mult_label = QLabel()
        general_layout.addRow("Multiplicity:", self.mult_label)
        
        self.content_layout.addWidget(self.general_group)
    
    def _create_parameters_group(self):
        """Create parameters table group"""
        self.parameters_group = QGroupBox("⚙️ Parameters")
        params_layout = QVBoxLayout(self.parameters_group)
        
        self.params_table = QTableWidget()
        self.params_table.setColumnCount(5)
        self.params_table.setHorizontalHeaderLabels([
            "Parameter", "Value", "Type", "Constraint", "Required"
        ])
        self.params_table.horizontalHeader().setStretchLastSection(True)
        self.params_table.setAlternatingRowColors(True)
        self.params_table.verticalHeader().setVisible(False)
        
        params_layout.addWidget(self.params_table)
        self.content_layout.addWidget(self.parameters_group)
    
    def show_instance(self, instance: EcucContainerValue, container_def: EcucContainerDef, config_manager: ConfigurationManager):
        """Show container instance for editing"""
        self.current_instance = instance
        self.current_def = container_def
        self.config_manager = config_manager
        
        # Hide empty message
        self.empty_label.hide()
        
        # Update general info
        self.name_label.setText(instance.short_name)
        self.def_label.setText(container_def.short_name)
        self.mult_label.setText(container_def.multiplicity_str)
        self.general_group.show()
        
        # Populate parameters table
        self._populate_parameters(instance, container_def)
        self.parameters_group.setTitle(f"⚙️ Parameters ({len(container_def.parameters)})")
        self.parameters_group.show()
    
    def show_definition(self, container_def: EcucContainerDef):
        """Show container definition (read-only info)"""
        self.current_instance = None
        self.current_def = container_def
        
        self.empty_label.hide()
        
        # Show definition info
        self.name_label.setText(f"{container_def.short_name} (Definition)")
        self.def_label.setText(container_def.definition_ref)
        self.mult_label.setText(f"{container_def.multiplicity_str} {'(Required)' if container_def.is_required else '(Optional)'}")
        self.general_group.show()
        
        # Show parameter definitions (no values)
        self.params_table.setRowCount(len(container_def.parameters))
        for row, (param_name, param_def) in enumerate(container_def.parameters.items()):
            # Name
            name_item = QTableWidgetItem(param_def.short_name)
            name_item.setToolTip(param_def.description)
            self.params_table.setItem(row, 0, name_item)
            
            # Value column: show "Not set" for definition view
            value_item = QTableWidgetItem("(No instance selected)")
            value_item.setForeground(Qt.gray)
            self.params_table.setItem(row, 1, value_item)
            
            # Type
            type_item = QTableWidgetItem(param_def.param_type.name)
            self.params_table.setItem(row, 2, type_item)
            
            # Constraint
            constraint = self._get_constraint_text(param_def)
            constraint_item = QTableWidgetItem(constraint)
            self.params_table.setItem(row, 3, constraint_item)
            
            # Required
            req_item = QTableWidgetItem("*" if param_def.is_required else "")
            self.params_table.setItem(row, 4, req_item)
        
        self.params_table.resizeColumnsToContents()
        self.parameters_group.show()
    
    def _populate_parameters(self, instance: EcucContainerValue, container_def: EcucContainerDef):
        """Populate parameters table with editable widgets"""
        self.params_table.setRowCount(len(container_def.parameters))
        
        for row, (param_name, param_def) in enumerate(container_def.parameters.items()):
            # Column 0: Parameter name
            name_item = QTableWidgetItem(param_def.short_name)
            name_item.setToolTip(param_def.description)
            self.params_table.setItem(row,0, name_item)
            
            # Column 1: Editable value widget
            current_value = None
            if param_name in instance.parameter_values:
                current_value = instance.parameter_values[param_name].value
            elif param_def.default_value is not None:
                current_value = param_def.default_value
            
            
            editor = self._create_parameter_editor(param_name, param_def, current_value)
            self.params_table.setCellWidget(row, 1, editor)
            
            # Column 2: Type
            type_item = QTableWidgetItem(param_def.param_type.name)
            self.params_table.setItem(row, 2, type_item)
            
            # Column 3: Constraint
            constraint = self._get_constraint_text(param_def)
            constraint_item = QTableWidgetItem(constraint)
            constraint_item.setToolTip(constraint)
            self.params_table.setItem(row, 3, constraint_item)
            
            # Column 4: Required
            req_item = QTableWidgetItem("*" if param_def.is_required else "")
            req_item.setTextAlignment(Qt.AlignCenter)
            self.params_table.setItem(row, 4, req_item)
        
        self.params_table.resizeColumnsToContents()
        # Set column resize modes
        header = self.params_table.horizontalHeader()
        header.setSectionResizeMode(0, header.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(1, header.ResizeMode.Stretch)  # Value column stretches
    
    def _create_parameter_editor(self, param_name: str, param_def: EcucParameterDef, current_value: any) -> QWidget:
        """Create appropriate editor widget based on parameter type
        
        Args:
            param_name: Parameter name (key in container_def.parameters dict)
            param_def: Parameter definition
            current_value: Current value or default
        """
        
        if param_def.param_type == EcucParameterType.ENUMERATION:
            # ComboBox for enumerations
            combo = QComboBox()
            combo.addItems(param_def.literals or [])
            if current_value in (param_def.literals or []):
                combo.setCurrentText(current_value)
            combo.currentTextChanged.connect(
                lambda value, pname=param_name: self._on_value_changed(pname, value)
            )
            return combo
        
        elif param_def.param_type == EcucParameterType.INTEGER:
            # SpinBox for integers
            spinbox = QSpinBox()
            # Limit range to avoid overflow (QSpinBox uses 32-bit int)
            min_val = param_def.min_value if param_def.min_value is not None else -2147483648
            max_val = param_def.max_value if param_def.max_value is not None else 2147483647
            # Clamp to safe 32-bit range
            min_val = max(min_val, -2147483648)
            max_val = min(max_val, 2147483647)
            spinbox.setRange(int(min_val), int(max_val))
            spinbox.setValue(int(current_value) if current_value is not None else 0)
            spinbox.valueChanged.connect(
                lambda value, pname=param_name: self._on_value_changed(pname, value)
            )
            return spinbox
        
        elif param_def.param_type == EcucParameterType.FLOAT:
            # DoubleSpinBox for floats
            spinbox = QDoubleSpinBox()
            spinbox.setRange(
                param_def.min_value if param_def.min_value is not None else -1e308,
                param_def.max_value if param_def.max_value is not None else 1e308
            )
            spinbox.setValue(float(current_value) if current_value is not None else 0.0)
            spinbox.valueChanged.connect(
                lambda value, pname=param_name: self._on_value_changed(pname, value)
            )
            return spinbox
        
        elif param_def.param_type == EcucParameterType.BOOLEAN:
            # CheckBox for booleans - centered in container widget
            container = QWidget()
            layout = QHBoxLayout(container)
            layout.setContentsMargins(0, 0, 0, 0)
            layout.setAlignment(Qt.AlignCenter)
            
            checkbox = QCheckBox()
            checkbox.setChecked(bool(current_value) if current_value is not None else False)
            checkbox.stateChanged.connect(
                lambda state, pname=param_name: self._on_value_changed(pname, state == Qt.Checked)
            )
            
            layout.addWidget(checkbox)
            return container
        
        else:
            # Default: LineEdit for strings
            lineedit = QLineEdit()
            lineedit.setText(str(current_value) if current_value is not None else "")
            lineedit.textChanged.connect(
                lambda text, pname=param_name: self._on_value_changed(pname, text)
            )
            return lineedit
    
    def _get_constraint_text(self, param_def: EcucParameterDef) -> str:
        """Get constraint description for parameter"""
        if param_def.param_type == EcucParameterType.ENUMERATION:
            if param_def.literals:
                preview = ", ".join(param_def.literals[:3])
                if len(param_def.literals) > 3:
                    preview += f"... ({len(param_def.literals)} total)"
                return preview
            return "Enum"
        
        elif param_def.param_type in (EcucParameterType.INTEGER, EcucParameterType.FLOAT):
            if param_def.min_value is not None and param_def.max_value is not None:
                return f"{param_def.min_value}..{param_def.max_value}"
            elif param_def.min_value is not None:
                return f">= {param_def.min_value}"
            elif param_def.max_value is not None:
                return f"<= {param_def.max_value}"
            return "-"
        
        return "-"
    
    def _on_value_changed(self, param_name: str, value: any):
        """Handle parameter value change"""
        if not self.current_instance or not self.config_manager:
            return
        
        # Emit signal - main window will handle validation and update
        self.parameter_changed.emit(self.current_instance, param_name, value)
    
    def clear(self):
        """Clear panel"""
        self.current_instance = None
        self.current_def = None
        self.general_group.hide()
        self.parameters_group.hide()
        self.empty_label.show()
