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
        self._create_references_group()
        
        self.general_group.hide()
        self.parameters_group.hide()
        self.references_group.hide()
    
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
        """Create parameters table group with search/filter"""
        self.parameters_group = QGroupBox("⚙️ Parameters")
        params_layout = QVBoxLayout(self.parameters_group)
        
        # Toolbar for search/filter/sort
        toolbar_layout = QHBoxLayout()
        
        # Search box
        self.param_search = QLineEdit()
        self.param_search.setPlaceholderText("🔍 Search parameters...")
        self.param_search.setClearButtonEnabled(True)
        self.param_search.textChanged.connect(self._filter_parameters)
        toolbar_layout.addWidget(self.param_search, 3)
        
        # Type filter
        self.type_filter = QComboBox()
        self.type_filter.addItems(["All Types", "Required Only", "Integer", "Float", "Boolean", "Enum", "String"])
        self.type_filter.currentTextChanged.connect(self._filter_parameters)
        toolbar_layout.addWidget(self.type_filter, 1)
        
        # Sort combo
        self.sort_combo = QComboBox()
        self.sort_combo.addItems(["Name ↑", "Name ↓", "Type"])
        self.sort_combo.currentTextChanged.connect(self._sort_parameters)
        toolbar_layout.addWidget(self.sort_combo, 1)
        
        params_layout.addLayout(toolbar_layout)
        
        # Parameters table
        self.params_table = QTableWidget()
        self.params_table.setColumnCount(5)
        self.params_table.setHorizontalHeaderLabels([
            "Parameter", "Value", "Type", "Constraint", "Required"
        ])
        self.params_table.horizontalHeader().setStretchLastSection(True)
        self.params_table.setAlternatingRowColors(True)
        self.params_table.verticalHeader().setVisible(False)
        self.params_table.setSortingEnabled(False)  # We handle sorting manually
        
        params_layout.addWidget(self.params_table)
        self.content_layout.addWidget(self.parameters_group)
    
    def _create_references_group(self):
        """Create references table group"""
        self.references_group = QGroupBox("🔗 References")
        refs_layout = QVBoxLayout(self.references_group)
        
        self.refs_table = QTableWidget()
        self.refs_table.setColumnCount(4)
        self.refs_table.setHorizontalHeaderLabels([
            "Reference", "Target", "Destination Type", "Required"
        ])
        self.refs_table.horizontalHeader().setStretchLastSection(True)
        self.refs_table.setAlternatingRowColors(True)
        self.refs_table.verticalHeader().setVisible(False)
        
        refs_layout.addWidget(self.refs_table)
        self.content_layout.addWidget(self.references_group)
    
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
        
        # Populate references table
        self._populate_references(instance, container_def)
        self.references_group.setTitle(f"🔗 References ({len(container_def.references)})")
        if len(container_def.references) > 0:
            self.references_group.show()
        else:
            self.references_group.hide()
    
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
            
            
            editor = self._create_parameter_editor(param_name, param_def, current_value, instance)
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
    
    def _create_parameter_editor(self, param_name: str, param_def: EcucParameterDef, current_value: any, instance: EcucContainerValue) -> QWidget:
        """Create appropriate editor widget based on parameter type
        
        Args:
            param_name: Parameter name (key in container_def.parameters dict)
            param_def: Parameter definition
            current_value: Current value or default
            instance: Container instance (for initializing value if needed)
        """
        
        if param_def.param_type == EcucParameterType.ENUMERATION:
            # ComboBox for enumerations
            combo = QComboBox()
            combo.addItems(param_def.literals or [])
            
            # Determine initial value
            if current_value in (param_def.literals or []):
                combo.setCurrentText(current_value)
            elif param_def.literals:
                # No value set, use first option as default
                current_value = param_def.literals[0]
                combo.setCurrentText(current_value)
                # IMPORTANT: Initialize the value in the instance
                if param_name not in instance.parameter_values:
                    instance.set_parameter_value(param_name, current_value, param_def.definition_ref)
            
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
            
            # Set value and initialize if needed
            value = int(current_value) if current_value is not None else 0
            spinbox.setValue(value)
            # Initialize value in instance if not set
            if param_name not in instance.parameter_values:
                instance.set_parameter_value(param_name, value, param_def.definition_ref)
            
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
            
            # Set value and initialize if needed
            value = float(current_value) if current_value is not None else 0.0
            spinbox.setValue(value)
            # Initialize value in instance if not set
            if param_name not in instance.parameter_values:
                instance.set_parameter_value(param_name, value, param_def.definition_ref)
            
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
            
            # Set value and initialize if needed
            value = bool(current_value) if current_value is not None else False
            checkbox = QCheckBox()
            checkbox.setChecked(value)
            # Initialize value in instance if not set
            if param_name not in instance.parameter_values:
                instance.set_parameter_value(param_name, value, param_def.definition_ref)
            
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
    
    def _is_boolean_parameter(self, param_def: EcucParameterDef) -> bool:
        """Check if parameter is boolean type"""
        return param_def.param_type == EcucParameterType.BOOLEAN
    
    def _filter_parameters(self):
        """Filter parameters based on search text and type filter"""
        if not hasattr(self, 'params_table'):
            return
        
        search_text = self.param_search.text().lower()
        type_filter = self.type_filter.currentText()
        
        for row in range(self.params_table.rowCount()):
            # Get parameter name and type
            name_item = self.params_table.item(row, 0)
            type_item = self.params_table.item(row, 2)
            required_item = self.params_table.item(row, 4)
            
            if not name_item:
                continue
            
            param_name = name_item.text().lower()
            param_type = type_item.text() if type_item else ""
            is_required = required_item.text() == "*" if required_item else False
            
            # Check search text match
            text_match = search_text == "" or search_text in param_name
            
            # Check type filter match
            type_match = True
            if type_filter == "Required Only":
                type_match = is_required
            elif type_filter != "All Types":
                type_match = param_type == type_filter
            
            # Show/hide row based on both filters
            self.params_table.setRowHidden(row, not (text_match and type_match))
    
    def _sort_parameters(self):
        """Sort parameters table"""
        if not hasattr(self, 'params_table'):
            return
        
        sort_mode = self.sort_combo.currentText()
        
        if sort_mode == "Name ↑":
            self.params_table.sortItems(0, Qt.AscendingOrder)
        elif sort_mode == "Name ↓":
            self.params_table.sortItems(0, Qt.DescendingOrder)
        elif sort_mode == "Type":
            self.params_table.sortItems(2, Qt.AscendingOrder)
    
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
        self.references_group.hide()
        self.empty_label.show()
    
    def _populate_references(self, instance: EcucContainerValue, container_def: EcucContainerDef):
        """Populate references table"""
        self.refs_table.setRowCount(len(container_def.references))
        
        for row, (ref_name, ref_def) in enumerate(container_def.references.items()):
            # Column 0: Reference name
            name_item = QTableWidgetItem(ref_def.short_name)
            name_item.setToolTip(f"Destination: {ref_def.destination_ref}")
            self.refs_table.setItem(row, 0, name_item)
            
            # Column 1: Target selector (ComboBox)
            current_value = None
            if ref_name in instance.reference_values:
                current_value = instance.reference_values[ref_name].value_ref
            
            selector = self._create_reference_selector(ref_name, ref_def, current_value)
            self.refs_table.setCellWidget(row, 1, selector)
            
            # Column 2: Destination type
            dest_parts = ref_def.destination_ref.split('/')
            dest_type = dest_parts[-1] if dest_parts else ref_def.destination_ref
            type_item = QTableWidgetItem(dest_type)
            type_item.setToolTip(ref_def.destination_ref)
            self.refs_table.setItem(row, 2, type_item)
            
            # Column 3: Required
            req_item = QTableWidgetItem("*" if ref_def.is_required else "")
            req_item.setTextAlignment(Qt.AlignCenter)
            self.refs_table.setItem(row, 3, req_item)
        
        # Adjust column widths
        self.refs_table.resizeColumnsToContents()
        header = self.refs_table.horizontalHeader()
        header.setSectionResizeMode(0, header.ResizeMode.ResizeToContents)
        header.setSectionResizeMode(1, header.ResizeMode.Stretch)
    
    def _create_reference_selector(self, ref_name: str, ref_def, current_value: str) -> QComboBox:
        """Create ComboBox for reference selection"""
        combo = QComboBox()
        combo.addItem("(Not set)", None)
        
        # Get available targets (simplified - just show all instances)
        if self.config_manager:
            for container in self.config_manager.configuration.containers:
                self._add_reference_targets(combo, container, ref_def)
        
        # Set current value
        if current_value:
            index = combo.findData(current_value)
            if index >= 0:
                combo.setCurrentIndex(index)
        
        # Connect signal
        combo.currentIndexChanged.connect(
            lambda idx, rname=ref_name: self._on_reference_changed(rname, combo.itemData(idx))
        )
        
        return combo
    
    def _add_reference_targets(self, combo: QComboBox, container: EcucContainerValue, ref_def, prefix=""):
        """Recursively add matching containers to combobox"""
        # Simple implementation: add all containers
        # TODO: Filter by destination_ref type
        display_name = f"{prefix}/{container.short_name}" if prefix else container.short_name
        path = f"/Config/{display_name}"
        combo.addItem(display_name, path)
        
        # Add sub-containers
        for sub in container.sub_containers:
            self._add_reference_targets(combo, sub, ref_def, display_name)
    
    def _on_reference_changed(self, ref_name: str, target_path: str):
        """Handle reference value change"""
        if not self.current_instance or not self.config_manager:
            return
        
        try:
            if target_path:
                # Get reference definition
                ref_def = self.current_def.references.get(ref_name)
                if ref_def:
                    self.current_instance.set_reference_value(
                        ref_name,
                        target_path,
                        ref_def.definition_ref
                    )
            else:
                # Clear reference
                if ref_name in self.current_instance.reference_values:
                    del self.current_instance.reference_values[ref_name]
            
            # Emit parameter changed signal (reuse for references)
            self.parameter_changed.emit(self.current_instance, f"ref:{ref_name}", target_path)
            
        except Exception as e:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.warning(self, "Reference Error", f"Failed to set reference: {e}")
