"""
Enhanced Configuration panel widget for editing ECUC parameters
"""
from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QFormLayout, QLabel, QLineEdit,
    QComboBox, QSpinBox, QDoubleSpinBox, QTextEdit, QGroupBox,
    QPushButton, QScrollArea, QTableWidget, QTableWidgetItem,
    QListWidget, QListWidgetItem, QTreeWidget, QTreeWidgetItem,
    QHBoxLayout, QHeaderView
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QColor
from typing import Optional

from ...core.model.container import Container, Parameter
from ...core.model.ecuc_model import EcucContainer, EcucParameter


class ConfigPanel(QWidget):
    """Enhanced panel for editing ECUC configuration parameters"""

    # Signals
    parameter_changed = Signal(Parameter)
    parameter_changed = Signal(Parameter)
    container_changed = Signal(Container)
    check_impact_requested = Signal(str, str)  # container_path, param_name

    def __init__(self, parent=None):
        super().__init__(parent)

        self.current_container: Optional[Container] = None
        self.current_parameter: Optional[Parameter] = None

        self._setup_ui()

    def _setup_ui(self):
        """Setup the UI layout"""
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)

        # Create scroll area
        scroll_area = QScrollArea()
        scroll_area.setWidgetResizable(True)
        scroll_area.setFrameShape(QScrollArea.NoFrame)

        # Content widget
        self.content_widget = QWidget()
        self.content_layout = QVBoxLayout(self.content_widget)

        # Initial message
        self.empty_label = QLabel("Select a container or parameter to edit")
        self.empty_label.setAlignment(Qt.AlignCenter)
        self.content_layout.addWidget(self.empty_label)

        scroll_area.setWidget(self.content_widget)
        layout.addWidget(scroll_area)

        # Create ECUC container widgets (5 GroupBoxes)
        self._create_ecuc_container_widgets()

        # Create parameter editing widgets (for backward compatibility)
        self._create_parameter_widgets()

        # Initially hide all editing widgets
        self.general_group.hide()
        self.params_table_group.hide()
        self.refs_group.hide()
        self.subconts_group.hide()
        self.constraints_group.hide()
        self.parameter_group.hide()

    def _create_ecuc_container_widgets(self):
        """Create 5 GroupBox layout for ECUC containers"""
        
        # ===== 1. General Information =====
        self.general_group = QGroupBox("📋 General Information")
        general_layout = QFormLayout(self.general_group)

        self.container_name_edit = QLineEdit()
        self.container_name_edit.textChanged.connect(self._on_container_name_changed)
        general_layout.addRow("Short Name:", self.container_name_edit)

        self.container_path_label = QLabel()
        general_layout.addRow("Path:", self.container_path_label)

        self.container_uuid_label = QLabel()
        self.container_uuid_label.setTextInteractionFlags(Qt.TextSelectableByMouse)
        general_layout.addRow("UUID:", self.container_uuid_label)

        self.container_desc_edit = QTextEdit()
        self.container_desc_edit.setMaximumHeight(80)
        self.container_desc_edit.textChanged.connect(self._on_container_desc_changed)
        general_layout.addRow("Description:", self.container_desc_edit)

        self.content_layout.addWidget(self.general_group)

        # ===== 2. Parameters Table =====
        self.params_table_group = QGroupBox("⚙️ Parameters")
        params_layout = QVBoxLayout(self.params_table_group)

        self.params_table = QTableWidget()
        self.params_table.setColumnCount(6)
        self.params_table.setHorizontalHeaderLabels([
            "Name", "Value", "Type", "Range/Options", "Required", "Description"
        ])
        self.params_table.horizontalHeader().setStretchLastSection(True)
        self.params_table.setAlternatingRowColors(True)
        self.params_table.setSelectionBehavior(QTableWidget.SelectRows)
        # Make cells read-only for now (double-click edit will be added later)
        self.params_table.setEditTriggers(QTableWidget.NoEditTriggers)
        
        # Context menu
        self.params_table.setContextMenuPolicy(Qt.CustomContextMenu)
        self.params_table.customContextMenuRequested.connect(self._on_table_context_menu)
        
        params_layout.addWidget(self.params_table)
        self.content_layout.addWidget(self.params_table_group)

        # ===== 3. References List =====
        self.refs_group = QGroupBox("🔗 References")
        refs_layout = QVBoxLayout(self.refs_group)

        self.refs_list = QListWidget()
        self.refs_list.setAlternatingRowColors(True)
        refs_layout.addWidget(self.refs_list)

        self.content_layout.addWidget(self.refs_group)

        # ===== 4. Sub-Containers Tree =====
        self.subconts_group = QGroupBox("📂 Sub-Containers")
        subconts_layout = QVBoxLayout(self.subconts_group)

        self.subconts_tree = QTreeWidget()
        self.subconts_tree.setHeaderLabel("Container Type [Multiplicity]")
        self.subconts_tree.setAlternatingRowColors(True)
        subconts_layout.addWidget(self.subconts_tree)

        self.content_layout.addWidget(self.subconts_group)

        # ===== 5. Constraints & Metadata =====
        self.constraints_group = QGroupBox("📝 Constraints & Metadata")
        constraints_layout = QFormLayout(self.constraints_group)

        self.multiplicity_label = QLabel()
        constraints_layout.addRow("Multiplicity:", self.multiplicity_label)

        self.variant_label = QLabel()
        constraints_layout.addRow("Variant Support:", self.variant_label)

        self.origin_label = QLabel()
        constraints_layout.addRow("Origin:", self.origin_label)

        self.content_layout.addWidget(self.constraints_group)

    def _create_parameter_widgets(self):
        """Create widgets for editing parameters (backward compatibility)"""
        self.parameter_group = QGroupBox("Parameter Properties")
        parameter_layout = QFormLayout(self.parameter_group)

        self.param_name_edit = QLineEdit()
        self.param_name_edit.textChanged.connect(self._on_param_name_changed)
        parameter_layout.addRow("Short Name:", self.param_name_edit)

        self.param_type_combo = QComboBox()
        self.param_type_combo.addItems(["STRING", "INTEGER", "FLOAT", "BOOLEAN", "ENUM", "REFERENCE", "ARRAY", "STRUCT"])
        self.param_type_combo.currentTextChanged.connect(self._on_param_type_changed)
        parameter_layout.addRow("Type:", self.param_type_combo)

        self.param_value_edit = QLineEdit()
        self.param_value_edit.setPlaceholderText("Enter value (comma-separated for ARRAY, JSON for STRUCT)")
        self.param_value_edit.textChanged.connect(self._on_param_value_changed)
        parameter_layout.addRow("Value:", self.param_value_edit)

        self.content_layout.addWidget(self.parameter_group)

    def show_container(self, container: Container):
        """Show container properties with full ECUC support"""
        self.current_container = container
        self.current_parameter = None

        # Hide all groups first
        self.empty_label.hide()
        self.parameter_group.hide()

        # Check if this is an ECUC container
        if isinstance(container, EcucContainer):
            self._show_ecuc_container(container)
        else:
            # Fallback to basic container display
            self._show_basic_container(container)

    def _show_ecuc_container(self, container: EcucContainer):
        """Show ECUC container with all 5 GroupBoxes"""
        
        # 1. General Information
        self.container_name_edit.blockSignals(True)
        self.container_name_edit.setText(container.short_name)
        self.container_name_edit.blockSignals(False)

        self.container_path_label.setText(container.path)
        self.container_uuid_label.setText(container.uuid)

        self.container_desc_edit.blockSignals(True)
        self.container_desc_edit.setText(container.description or "")
        self.container_desc_edit.blockSignals(False)

        self.general_group.show()

        # 2. Parameters Table
        if container.parameters:
            self.params_table.setRowCount(len(container.parameters))
            for row, (param_name, param) in enumerate(container.parameters.items()):
                # Name
                name_item = QTableWidgetItem(param.short_name)
                self.params_table.setItem(row, 0, name_item)

                # Value
                value_text = str(param.value) if param.value is not None else ""
                value_item = QTableWidgetItem(value_text)
                self.params_table.setItem(row, 1, value_item)

                # Type
                type_item = QTableWidgetItem(param.value_type)
                self.params_table.setItem(row, 2, type_item)

                # Range/Options
                range_str = ""
                if isinstance(param, EcucParameter):
                    if param.literals:
                        range_str = ", ".join(param.literals[:3])
                        if len(param.literals) > 3:
                            range_str += f"... ({len(param.literals)} total)"
                    elif param.min_value is not None and param.max_value is not None:
                        range_str = f"{param.min_value}..{param.max_value}"
                range_item = QTableWidgetItem(range_str)
                range_item.setToolTip(range_str)  # Full text in tooltip
                self.params_table.setItem(row, 3, range_item)

                # Required
                req_text = ""
                if isinstance(param, EcucParameter):
                    req_text = "*" if param.lower_multiplicity >= 1 else ""
                req_item = QTableWidgetItem(req_text)
                req_item.setTextAlignment(Qt.AlignCenter)
                self.params_table.setItem(row, 4, req_item)

                # Description
                desc_item = QTableWidgetItem(param.description or "")
                desc_item.setToolTip(param.description or "")
                self.params_table.setItem(row, 5, desc_item)

            # Resize columns to content
            self.params_table.resizeColumnsToContents()
            self.params_table_group.setTitle(f"⚙️ Parameters ({len(container.parameters)})")
            self.params_table_group.show()
        else:
            self.params_table_group.hide()

        # 3. References List
        if hasattr(container, 'references_defs') and container.references_defs:
            self.refs_list.clear()
            for ref_name, ref in container.references_defs.items():
                item_text = f"{ref_name}\n  → {ref.destination_ref}"
                item = QListWidgetItem(item_text)
                item.setToolTip(ref.description or "")
                self.refs_list.addItem(item)
            
            self.refs_group.setTitle(f"🔗 References ({len(container.references_defs)})")
            self.refs_group.show()
        else:
            self.refs_group.hide()

        # 4. Sub-Containers Tree
        if container.sub_containers:
            self.subconts_tree.clear()
            for subcont_name, subcont in container.sub_containers.items():
                mult_str = ""
                if isinstance(subcont, EcucContainer):
                    mult_str = f" [{subcont.multiplicity_str}]"
                item = QTreeWidgetItem([f"{subcont.short_name}{mult_str}"])
                item.setToolTip(0, subcont.description or "")
                self.subconts_tree.addTopLevelItem(item)
            
            self.subconts_group.setTitle(f"📂 Sub-Containers ({len(container.sub_containers)})")
            self.subconts_group.show()
        else:
            self.subconts_group.hide()

        # 5. Constraints & Metadata
        mult_text = container.multiplicity_str
        if container.is_required:
            mult_text += " (Required)"
        else:
            mult_text += " (Optional)"
        self.multiplicity_label.setText(mult_text)

        self.variant_label.setText(container.config_variant)
        self.origin_label.setText(container.origin)

        self.constraints_group.show()

    def _show_basic_container(self, container: Container):
        """Fallback for non-ECUC containers"""
        # Just show general info
        self.container_name_edit.blockSignals(True)
        self.container_name_edit.setText(container.short_name)
        self.container_name_edit.blockSignals(False)

        self.container_path_label.setText(container.path)
        self.container_uuid_label.setText(container.uuid)

        self.container_desc_edit.blockSignals(True)
        self.container_desc_edit.setText(container.description or "")
        self.container_desc_edit.blockSignals(False)

        self.general_group.show()
        
        # Hide ECUC-specific groups
        self.params_table_group.hide()
        self.refs_group.hide()
        self.subconts_group.hide()
        self.constraints_group.hide()

    def show_parameter(self, parameter: Parameter):
        """Show parameter properties"""
        self.current_parameter = parameter
        self.current_container = None

        # Hide container groups
        self.empty_label.hide()
        self.general_group.hide()
        self.params_table_group.hide()
        self.refs_group.hide()
        self.subconts_group.hide()
        self.constraints_group.hide()

        # Update parameter widgets
        self.param_name_edit.blockSignals(True)
        self.param_name_edit.setText(parameter.short_name)
        self.param_name_edit.blockSignals(False)

        self.param_type_combo.blockSignals(True)
        self.param_type_combo.setCurrentText(parameter.value_type)
        self.param_type_combo.blockSignals(False)

        self.param_value_edit.blockSignals(True)
        # Format value for display
        if parameter.value is None:
            text = ""
        elif parameter.value_type == "ARRAY" and isinstance(parameter.value, list):
            text = ", ".join(map(str, parameter.value))
        elif parameter.value_type == "STRUCT" and isinstance(parameter.value, dict):
            import json
            try:
                text = json.dumps(parameter.value)
            except:
                text = str(parameter.value)
        else:
            text = str(parameter.value)
            
        self.param_value_edit.setText(text)
        self.param_value_edit.blockSignals(False)

        self.parameter_group.show()

    def highlight_parameter(self, param_name: str):
        """Highlight a specific parameter in the table"""
        if not param_name:
            return
            
        # Ensure parameters table is visible
        self.params_table_group.show()
        
        # Find row with parameter name
        for row in range(self.params_table.rowCount()):
            item = self.params_table.item(row, 0) # Name column
            if item and item.text() == param_name:
                # Select row
                self.params_table.selectRow(row)
                
                # Scroll to row
                self.params_table.scrollToItem(item)
                
                # Flash effect (optional, for now just selection is enough)
                return

    def clear(self):
        """Clear the panel"""
        self.current_container = None
        self.current_parameter = None

        self.general_group.hide()
        self.params_table_group.hide()
        self.refs_group.hide()
        self.subconts_group.hide()
        self.constraints_group.hide()
        self.parameter_group.hide()
        self.empty_label.show()

    # Event handlers
    
    def _on_container_name_changed(self, text: str):
        """Handle container name change"""
        if self.current_container and text:
            try:
                # Validate name
                if not text[0].isalpha():
                    return
                if not all(c.isalnum() or c == '_' for c in text):
                    return

                self.current_container.short_name = text
                self.current_container.mark_dirty()
                self.container_changed.emit(self.current_container)
            except Exception:
                pass

    def _on_container_desc_changed(self):
        """Handle container description change"""
        if self.current_container:
            self.current_container.description = self.container_desc_edit.toPlainText()
            self.current_container.mark_dirty()

    def _on_param_name_changed(self, text: str):
        """Handle parameter name change"""
        if self.current_parameter and text:
            try:
                if not text[0].isalpha():
                    return
                if not all(c.isalnum() or c == '_' for c in text):
                    return

                self.current_parameter.short_name = text
                self.current_parameter.mark_dirty()
                self.parameter_changed.emit(self.current_parameter)
            except Exception:
                pass

    def _on_param_type_changed(self, text: str):
        """Handle parameter type change"""
        if self.current_parameter:
            self.current_parameter.value_type = text
            self.current_parameter.mark_dirty()

    def _on_param_value_changed(self, text: str):
        """Handle parameter value change"""
        if self.current_parameter:
            try:
                new_value = text
                
                # Type conversion based on value_type
                if self.current_parameter.value_type == "ARRAY":
                    if text:
                        new_value = [x.strip() for x in text.split(",")]
                        if hasattr(self.current_parameter, 'content_type'):
                            if self.current_parameter.content_type == "INTEGER":
                                new_value = [int(x) for x in new_value if x]
                            elif self.current_parameter.content_type == "FLOAT":
                                new_value = [float(x) for x in new_value if x]
                    else:
                        new_value = []
                        
                elif self.current_parameter.value_type == "STRUCT":
                    import json
                    if text:
                        try:
                            new_value = json.loads(text)
                        except json.JSONDecodeError:
                            pass
                            
                self.current_parameter.value = new_value
                self.current_parameter.mark_dirty()
            except Exception:
                pass

    def _on_table_context_menu(self, pos):
        """Show context menu for parameter table"""
        from PySide6.QtWidgets import QMenu
        from PySide6.QtGui import QAction
        
        item = self.params_table.itemAt(pos)
        if not item:
            return
            
        row = item.row()
        name_item = self.params_table.item(row, 0)
        if not name_item:
            return
            
        param_name = name_item.text()
        
        menu = QMenu(self)
        
        # Check Impact Action
        impact_action = QAction("🔍 Check Change Impact", self)
        impact_action.triggered.connect(lambda: self._emit_check_impact(param_name))
        menu.addAction(impact_action)
        
        menu.exec_(self.params_table.mapToGlobal(pos))
        
    def _emit_check_impact(self, param_name: str):
        """Emit check impact signal"""
        if self.current_container:
            self.check_impact_requested.emit(self.current_container.path, param_name)

