"""
DaVinci-style Config Panel
Shows editable parameters for selected container instance
"""
from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QFormLayout, QLabel, QLineEdit,
    QComboBox, QSpinBox, QDoubleSpinBox, QCheckBox, QTextEdit,
    QGroupBox, QTableWidget, QTableWidgetItem, QScrollArea,
    QHeaderView, QPushButton, QListWidget, QListWidgetItem,
    QToolButton, QMessageBox
)
from PySide6.QtCore import Qt, Signal, Slot
from PySide6.QtGui import QColor
from typing import Optional, List, Any

from ...core.model.definition_model import EcucContainerDef, EcucParameterDef, EcucParameterType
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager
from PySide6.QtCore import QSettings


class DaVinciConfigPanel(QWidget):
    """Config panel for editing container instance parameters"""
    
    # Signals
    parameter_changed = Signal(EcucContainerValue, str, object)  # instance, param_name, value
    ai_help_requested = Signal(str, str)  # container_name, param_name - request AI help for parameter
    check_impact_requested = Signal(str, str)  # container_path, param_name - request impact analysis
    reference_jump_requested = Signal(str)  # target_path - request navigation to referenced container
    instance_variant_changed = Signal(EcucContainerValue)  # instance - its assigned variant was changed, needs tree refresh
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.current_instance: Optional[EcucContainerValue] = None
        self.current_def: Optional[EcucContainerDef] = None
        self.config_manager: Optional[ConfigurationManager] = None
        self.chip_constraint_service = None  # Will be set from main window
        self.ai_help_cache: dict = {}  # Cache AI help responses
        self.reference_variant: Optional[str] = None  # Reference variant for comparison (None = Base)
        
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
        
        self.variant_label_tag = QLabel("Assigned Variant (归属变体):")
        self.variant_combo = QComboBox()
        self.variant_combo.addItem("None (All Variants)")
        self.variant_combo.setToolTip("Assign this container instance to a specific variant (or None for all variants)")
        self.variant_combo.currentTextChanged.connect(self._on_instance_variant_changed)
        general_layout.addRow(self.variant_label_tag, self.variant_combo)
        
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
        self.type_filter.addItems(["All Types", "Required Only", "⚡ Overridden Only", "Integer", "Float", "Boolean", "Enum", "String"])
        self.type_filter.currentTextChanged.connect(self._filter_parameters)
        toolbar_layout.addWidget(self.type_filter, 1)
        
        # Sort combo
        self.sort_combo = QComboBox()
        self.sort_combo.addItems(["Name ↑", "Name ↓", "Type"])
        self.sort_combo.currentTextChanged.connect(self._sort_parameters)
        toolbar_layout.addWidget(self.sort_combo, 1)
        
        # Compare button
        self.compare_btn = QPushButton("⚡ Check Diff")
        self.compare_btn.setToolTip("Compare current variant with reference (Base or defined reference)")
        self.compare_btn.clicked.connect(self._run_comparison)
        # Use a checkable button to show state
        self.compare_btn.setCheckable(True)
        toolbar_layout.addWidget(self.compare_btn, 1)
        
        # Comparison results: {param_name: {'current': val, 'reference': val}}
        self.comparison_results = {}
        
        params_layout.addLayout(toolbar_layout)
        
        # Parameters table
        self.params_table = QTableWidget()
        self.params_table.setColumnCount(6)
        self.params_table.setHorizontalHeaderLabels([
            "Parameter", "Value", "Chip", "Constraint", "Type", "Required"
        ])
        self.params_table.horizontalHeader().setStretchLastSection(True)
        self.params_table.setAlternatingRowColors(True)
        self.params_table.verticalHeader().setVisible(False)
        self.params_table.setSortingEnabled(False)  # We handle sorting manually
        
        # Enable context menu for impact analysis
        self.params_table.setContextMenuPolicy(Qt.CustomContextMenu)
        self.params_table.customContextMenuRequested.connect(self._on_table_context_menu)
        
        params_layout.addWidget(self.params_table)
        
        # AI Help panel (shows contextual info when parameter is selected)
        self.ai_help_group = QGroupBox("💡 AI 配置建议")
        ai_help_layout = QVBoxLayout(self.ai_help_group)
        self.ai_help_label = QLabel("点击参数名称获取 AI 配置建议...")
        self.ai_help_label.setWordWrap(True)
        self.ai_help_label.setStyleSheet("color: #666; padding: 8px; background: #f8f8f8; border-radius: 4px;")
        ai_help_layout.addWidget(self.ai_help_label)
        
        # Button row
        btn_layout = QHBoxLayout()
        
        # Cancel button (only active during request)
        self.ai_cancel_btn = QPushButton("🛑 取消请求")
        self.ai_cancel_btn.setMaximumWidth(100)
        self.ai_cancel_btn.clicked.connect(self._cancel_ai_request)
        self.ai_cancel_btn.hide()
        btn_layout.addWidget(self.ai_cancel_btn)
        
        # Close button
        close_btn = QPushButton("❌ 关闭")
        close_btn.setMaximumWidth(80)
        close_btn.clicked.connect(self._close_ai_help)
        btn_layout.addWidget(close_btn)
        btn_layout.addStretch()
        
        ai_help_layout.addLayout(btn_layout)
        
        # Enable right-click context menu
        self.ai_help_group.setContextMenuPolicy(Qt.CustomContextMenu)
        self.ai_help_group.customContextMenuRequested.connect(self._show_ai_help_menu)
        
        params_layout.addWidget(self.ai_help_group)
        self.ai_help_group.hide()  # Initially hidden
        self.ai_pending_request = False  # Track if request is pending
        self.ai_request_cancelled = False  # Track if request was cancelled
        
        # Connect cell click to AI help request
        self.params_table.cellClicked.connect(self._on_param_cell_clicked)
        
        self.content_layout.addWidget(self.parameters_group)
    
    def _create_references_group(self):
        """Create references table group"""
        self.references_group = QGroupBox("🔗 References")
        refs_layout = QVBoxLayout(self.references_group)
        
        self.refs_table = QTableWidget()
        self.refs_table.setColumnCount(5)
        self.refs_table.setHorizontalHeaderLabels([
            "Reference", "Target", "Destination Type", "Required", "Status"
        ])
        self.refs_table.horizontalHeader().setStretchLastSection(True)
        self.refs_table.setAlternatingRowColors(True)
        self.refs_table.verticalHeader().setVisible(False)
        
        # Connect cell click to AI help request
        self.refs_table.cellClicked.connect(self._on_ref_cell_clicked)
        
        # Connect double-click for navigation
        self.refs_table.cellDoubleClicked.connect(self._on_ref_cell_double_clicked)
        
        refs_layout.addWidget(self.refs_table)
        self.content_layout.addWidget(self.references_group)
    
    def show_instance(self, instance: EcucContainerValue, container_def: EcucContainerDef, config_manager: ConfigurationManager, project=None):
        """Show container instance for editing"""
        try:
            self.current_instance = instance
            self.current_def = container_def
            self.config_manager = config_manager
            self.project = project
            
            # Reset UI state first to prevent stale data
            self.empty_label.hide()
            self.references_group.hide()
            self.parameters_group.hide()
            self.general_group.hide()
            
            # Hide AI help panel when switching containers (stale context)
            self.ai_help_group.hide()
            
            # Reset comparison state only if not in comparison mode
            # (comparison mode preserves results during refresh)
            if hasattr(self, 'compare_btn') and not self.compare_btn.isChecked():
                self.comparison_results = {}
            
            # Update general info
            self.name_label.setText(instance.short_name)
            self.def_label.setText(container_def.short_name)
            self.mult_label.setText(container_def.multiplicity_str)
            
            # Show variant info
            if hasattr(self, 'variant_combo'):
                self._update_variant_selector(instance)
            
            self.general_group.show()

            
            # Populate parameters table
            self._populate_parameters(instance, container_def)
            self.parameters_group.setTitle(f"⚙️ Parameters ({len(container_def.parameters)})")
            self.parameters_group.show()
            
            # Populate references table (sets title with error count)
            self._populate_references(instance, container_def)
            if len(container_def.references) > 0 or len(instance.multi_reference_values) > 0:
                self.references_group.show()
                
        except Exception as e:
            print(f"Error showing instance {instance.short_name}: {e}")
            import traceback
            traceback.print_exc()
            # Show error in panel?
            self.empty_label.setText(f"Error displaying instance:\n{e}")
            self.empty_label.show()
    
    def show_definition(self, container_def: EcucContainerDef):
        """Show container definition (read-only info)"""
        self.current_instance = None
        self.current_def = container_def
        self.project = None

        self.empty_label.hide()

        # Show definition info
        self.name_label.setText(f"{container_def.short_name} (Definition)")
        self.def_label.setText(container_def.definition_ref)
        self.mult_label.setText(f"{container_def.multiplicity_str} {'(Required)' if container_def.is_required else '(Optional)'}")
        self.general_group.show()

        # Clear existing cell widgets before repopulating (prevent ghost overlays)
        for row in range(self.params_table.rowCount()):
            self.params_table.removeCellWidget(row, 1)

        # Show parameter definitions (no values)
        self.params_table.setRowCount(len(container_def.parameters))
        for row, (param_name, param_def) in enumerate(container_def.parameters.items()):
            # Name
            name_item = QTableWidgetItem(param_def.short_name)
            name_item.setToolTip(self._get_parameter_tooltip(param_def))
            self.params_table.setItem(row, 0, name_item)

            # Value column: show "Not set" for definition view
            # First remove any cellWidget that might exist from instance view
            self.params_table.removeCellWidget(row, 1)
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
        self.references_group.hide()  # Ensure references are hidden in definition mode
    
    def _run_comparison(self):
        """Compare current variant with reference (Base or another variant).

        Only compares parameters in the currently selected container.
        Results stored in self.comparison_results dict.
        
        PRECONDITION: Comparison only makes sense if the instance is applicable
        to BOTH variants (i.e., instance.variant is None). If the instance is
        assigned to a specific variant, it doesn't exist in other variants.
        """
        self.comparison_results = {}

        if not self.compare_btn.isChecked():
            # Button unchecked - clear highlights
            self.refresh()
            return

        if not self.current_instance or not self.current_def:
            return

        instance = self.current_instance
        module_config = instance.module_config
        variant = getattr(self.project, 'active_variant', None) if self.project else None

        # PRECONDITION CHECK: Instance must be applicable to all variants (variant=None)
        # to allow meaningful comparison between v1 and v2
        if instance.variant is not None:
            # Instance is exclusive to a specific variant - comparison is meaningless
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.information(
                self, 
                "无法比较 / Cannot Compare",
                f"该实例 '{instance.short_name}' 专属于变体 '{instance.variant}'，\n"
                f"因此无法与其他变体进行比较。\n\n"
                f"只有归属变体为 'None (All Variants)' 的实例才能进行变体间参数比对。"
            )
            self.compare_btn.setChecked(False)
            return

        for param_name, param_def in self.current_def.parameters.items():
            # 1. Get base value (from ARXML or default)
            base_value = None
            if param_name in instance.parameter_values:
                base_value = instance.parameter_values[param_name].value
            elif param_def.default_value is not None:
                base_value = param_def.default_value

            # 2. Get current value (variant override or base)
            current_value = base_value
            param_path = f"{instance.get_path()}.{param_name}"
            
            if variant and module_config:
                override, is_override = module_config.get_value_for_variant(param_path, variant)
                if not is_override:
                    short_path = f"{instance.short_name}.{param_name}"
                    override, is_override = module_config.get_value_for_variant(short_path, variant)
                if is_override:
                    current_value = override

            # 3. Get reference value
            # Priority: reference_variant > "Base" variant > parameter_values/default
            reference_value = base_value
            
            if self.reference_variant and module_config:
                # Reference is another variant (e.g., compare v1 vs v2)
                ref_override, is_ref = module_config.get_value_for_variant(param_path, self.reference_variant)
                if not is_ref:
                    short_path = f"{instance.short_name}.{param_name}"
                    ref_override, is_ref = module_config.get_value_for_variant(short_path, self.reference_variant)
                if is_ref:
                    reference_value = ref_override
            elif module_config:
                # No reference_variant selected - try to read from "Base" variant
                base_override, is_base = module_config.get_value_for_variant(param_path, "Base")
                if not is_base:
                    short_path = f"{instance.short_name}.{param_name}"
                    base_override, is_base = module_config.get_value_for_variant(short_path, "Base")
                if is_base:
                    reference_value = base_override

            # 4. Compare values (robust)
            if self._values_differ(current_value, reference_value):
                self.comparison_results[param_name] = {
                    'current': current_value,
                    'reference': reference_value
                }
        
        # Refresh display to apply highlights (but don't reset comparison_results)
        if self.current_instance and self.current_def:
            self._populate_parameters(self.current_instance, self.current_def)

    def _values_differ(self, val1, val2) -> bool:
        """Compare two values robustly, handling type differences"""
        if val1 == val2:
            return False
        if str(val1) == str(val2):
            return False
        try:
            if float(val1) == float(val2):
                return False
        except (ValueError, TypeError):
            pass
        return True

    def _populate_parameters(self, instance: EcucContainerValue, container_def: EcucContainerDef):
        """Populate parameters table with editable widgets"""
        self.params_table.setRowCount(len(container_def.parameters))
        self._override_rows = set()  # Track rows with variant overrides


        for row, (param_name, param_def) in enumerate(container_def.parameters.items()):
            # Check if parameter is deprecated
            is_deprecated = self._is_deprecated_parameter(param_def)

            # Column 0: Parameter name
            display_name = f"[废弃] {param_def.short_name}" if is_deprecated else param_def.short_name
            name_item = QTableWidgetItem(display_name)
            tooltip = self._get_parameter_tooltip(param_def)
            if is_deprecated:
                tooltip = "⚠️ 此参数已废弃，请勿使用\n\n" + tooltip
            name_item.setToolTip(tooltip)
            self.params_table.setItem(row, 0, name_item)

            # Column 1: Editable value widget
            # Check for variant override first, then base value
            current_value = None
            is_variant_override = False

            # Check if there's an active variant with an override
            if self.project and hasattr(self.project, 'active_variant') and self.project.active_variant:
                variant = self.project.active_variant
                module_config = instance.module_config
                if module_config:
                    # Try full path first (new format)
                    param_path = f"{instance.get_path()}.{param_name}"
                    override_value, is_override = module_config.get_value_for_variant(param_path, variant)

                    # Fallback to short path for backward compatibility with old saved data
                    if not is_override:
                        short_path = f"{instance.short_name}.{param_name}"
                        override_value, is_override = module_config.get_value_for_variant(short_path, variant)

                    if is_override:
                        current_value = override_value
                        is_variant_override = True

            # Fall back to base value if no variant override
            if current_value is None:
                if param_name in instance.parameter_values:
                    current_value = instance.parameter_values[param_name].value
                elif param_def.is_required and param_def.default_value is not None:
                    # Only use default for required parameters
                    current_value = param_def.default_value
                # For optional parameters without configured value, leave as None
                # The editor will show "(未配置)" option

            # Clear any existing item in the value cell to prevent "shadow" text
            self.params_table.setItem(row, 1, QTableWidgetItem(""))

            try:
                editor = self._create_parameter_editor(param_name, param_def, current_value, instance)
                self.params_table.setCellWidget(row, 1, editor)
                # Disable editor for deprecated parameters
                if is_deprecated:
                    editor.setEnabled(False)
            except Exception as e:
                print(f"Error creating editor for {param_name}: {e}")
                error_item = QTableWidgetItem(f"Error: {e}")
                error_item.setForeground(Qt.red)
                self.params_table.setItem(row, 1, error_item)

            # Column 2: Chip Constraint (from chip constraint service)
            chip_constraint = self._get_chip_constraint_text(param_name, container_def)
            chip_item = QTableWidgetItem(chip_constraint)
            if chip_constraint and chip_constraint != "-":
                chip_item.setToolTip(f"芯片约束: {chip_constraint}")
            self.params_table.setItem(row, 2, chip_item)

            # Column 3: Constraint (from param def)
            constraint = self._get_constraint_text(param_def)
            constraint_item = QTableWidgetItem(constraint)
            constraint_item.setToolTip(constraint)
            self.params_table.setItem(row, 3, constraint_item)

            # Column 4: Type
            type_item = QTableWidgetItem(param_def.param_type.name)
            self.params_table.setItem(row, 4, type_item)

            # Column 5: Required
            req_item = QTableWidgetItem("*" if param_def.is_required else "")
            req_item.setTextAlignment(Qt.AlignCenter)
            self.params_table.setItem(row, 5, req_item)

            # Apply gray styling for deprecated parameters
            if is_deprecated:
                gray_color = QColor("#CCCCCC")
                gray_text = QColor("#888888")
                for col in range(self.params_table.columnCount()):
                    item = self.params_table.item(row, col)
                    if item:
                        item.setBackground(gray_color)
                        item.setForeground(gray_text)

            # Apply comparison highlighting
            if param_name in self.comparison_results:
                self._override_rows.add(row)
                diff_info = self.comparison_results[param_name]

                # Update name with indicator
                new_name = f"⚡ {param_def.short_name}"
                name_item.setText(new_name)

                # Build detailed tooltip showing actual values
                reference_display = "Base" if not self.reference_variant else self.reference_variant
                tooltip_extra = (
                    f"\n\n⚡ 与 {reference_display} 不同:\n"
                    f"  当前值: {diff_info['current']}\n"
                    f"  参考值: {diff_info['reference']}"
                )
                name_item.setToolTip(self._get_parameter_tooltip(param_def) + tooltip_extra)

                # Set yellow background for all cells in row
                override_color = QColor("#FFF3CD")  # Soft warning yellow
                for col in range(self.params_table.columnCount()):
                    item = self.params_table.item(row, col)
                    if item:
                        item.setBackground(override_color)

        self.params_table.resizeColumnsToContents()

    def _is_deprecated_parameter(self, param_def: EcucParameterDef) -> bool:
        """Check if a parameter is deprecated based on its description"""
        if not param_def.description:
            return False
        desc_lower = param_def.description.lower()
        deprecated_keywords = [
            "not used",
            "deprecated",
            "replaced by",
            "obsolete",
            "do not use"
        ]
        return any(keyword in desc_lower for keyword in deprecated_keywords)

    def _is_list_parameter(self, param_def: EcucParameterDef) -> bool:
        """Check if parameter supports multiple values"""
        return param_def.upper_multiplicity == -1 or param_def.upper_multiplicity > 1

    def _create_parameter_editor(self, param_name: str, param_def: EcucParameterDef, current_value: any, instance: EcucContainerValue) -> QWidget:
        """Create appropriate editor widget based on parameter type"""
        
        # Check for list/array type
        if self._is_list_parameter(param_def):
            initial_list = current_value if isinstance(current_value, list) else []
            if current_value is not None and not isinstance(current_value, list):
                initial_list = [current_value]
                
            list_editor = ListEditorWidget(param_name, param_def, initial_list, self)
            list_editor.valueChanged.connect(
                lambda val, pname=param_name: self._on_value_changed(pname, val)
            )
            return list_editor

        # Single value editor
        widget, value_getter, signal = self._create_single_value_editor(param_name, param_def, current_value)
        
        # Note: We intentionally do NOT auto-create parameters here.
        # Parameters should only be added when the user explicitly changes them.
        # The UI widget may show a default/placeholder value, but it is NOT written
        # to the instance until the user actually modifies it via the signal handler.

        # Connect signal
        # Use nested function for reliable closure capture
        def on_change(*args):
             val = value_getter()
             self._on_value_changed(param_name, val)
             
        # Keep reference to prevent GC (Crucial for reliable signal handling)
        widget._on_change_slot = on_change
        
        signal.connect(on_change)
        
        return widget

    def _create_single_value_editor(self, param_name: str, param_def: EcucParameterDef, current_value: Any):
        """Create a single value editor widget
        
        Args:
            param_name: Parameter name (used to identify baudrate params)
            param_def: Parameter definition
            current_value: Current value of the parameter
        
        Returns:
            (widget, value_getter_func, changed_signal)
        """
        if param_def.param_type == EcucParameterType.ENUMERATION:
            # ComboBox for enumerations
            combo = QComboBox()

            # For optional parameters, add "(未配置)" option at the beginning
            if not param_def.is_required:
                combo.addItem("(未配置)")

            # Get allowed literals from chip constraints
            literals = param_def.literals or []
            if self.chip_constraint_service:
                allowed_values = self._get_allowed_literals(param_name, self.current_def, param_def)
                if allowed_values:
                    # DEBUG
                    
                    if literals:
                        # Filter: only keep literals that are in the allowed list
                        allowed_values_upper = [av.upper() for av in allowed_values]
                        literals = [lit for lit in literals if lit in allowed_values or lit.upper() in allowed_values_upper]
                    else:
                        # No static literals — use chip constraints
                        literals = allowed_values
                    

            combo.addItems(literals)

            # Set current value
            if current_value is not None:
                combo.setCurrentText(str(current_value))
            elif not param_def.is_required:
                combo.setCurrentIndex(0)  # Select "(未配置)"

            return combo, combo.currentText, combo.currentTextChanged
            
        elif param_def.param_type == EcucParameterType.BOOLEAN:
            # Centered CheckBox for booleans
            container = QWidget()
            layout = QHBoxLayout(container)
            layout.setContentsMargins(0, 0, 0, 0)
            layout.setAlignment(Qt.AlignCenter)
            checkbox = QCheckBox()
            # Robust boolean check
            is_checked = False
            if isinstance(current_value, bool):
                is_checked = current_value
            elif isinstance(current_value, (int, float)):
                is_checked = (current_value != 0)
            elif isinstance(current_value, str):
                is_checked = current_value.upper() in ('TRUE', '1', 'YES', 'ON')
                
            checkbox.setChecked(is_checked)
            layout.addWidget(checkbox)
            
            # Helper to return bool instead of Qt.CheckState
            def get_bool():
                return checkbox.isChecked()
                
            return container, get_bool, checkbox.toggled
            
        elif param_def.param_type == EcucParameterType.INTEGER:
            # Handle integers, using QLineEdit for large ranges
            min_val = param_def.min_value if param_def.min_value is not None else -2147483648
            max_val = param_def.max_value if param_def.max_value is not None else 2147483647
            
            # Special handling for CanControllerBaseAddress - show chip-based options (PRIORITY)
            if param_name == 'CanControllerBaseAddress' and self.chip_constraint_service:
                chip_addresses = self._get_chip_can_base_addresses()
                if chip_addresses:
                    combo = QComboBox()
                    combo.setEditable(True)  # Allow custom input as fallback
                    
                    # Add "未配置" option
                    combo.addItem("(未配置)", None)
                    
                    # Add chip-specific addresses
                    for addr_name, addr_val in chip_addresses:
                        # Display as hex if value is integer
                        if isinstance(addr_val, int):
                            display_val = f"0x{addr_val:08X}"
                        else:
                            display_val = str(addr_val)
                        combo.addItem(f"{addr_name}: {display_val}", addr_val)
                    
                    # Set current value
                    current_hex = hex(current_value) if current_value else None
                    idx = 0
                    for i in range(combo.count()):
                        if combo.itemData(i) == current_hex:
                            idx = i
                            break
                    combo.setCurrentIndex(idx)
                    
                    def get_combo_value():
                        data = combo.currentData()
                        if data is None:
                            # Try parsing custom input
                            text = combo.currentText()
                            try:
                                return int(text, 16) if text.startswith('0x') else int(text)
                            except:
                                return None
                        # Convert hex string to int
                        return int(data, 16) if isinstance(data, str) else data
                    
                    return combo, get_combo_value, combo.currentIndexChanged
            
            # Use QLineEdit for values exceeding 32-bit signed limits (e.g. 0..4294967295)
            if min_val < -2147483648 or max_val > 2147483647:
                lineedit = QLineEdit()
                lineedit.setText(str(current_value) if current_value is not None else "0")
                lineedit.setPlaceholderText(f"Range: {min_val} to {max_val}")
                return lineedit, lineedit.text, lineedit.textChanged
            
            # Standard case: QSpinBox
            spinbox = QSpinBox()
            spinbox.setRange(int(min_val), int(max_val))
            
            try:
                # Robust conversion and clamping
                val = int(current_value) if current_value is not None else 0
                val = max(int(min_val), min(int(max_val), val))
                spinbox.setValue(val)
            except (ValueError, TypeError):
                spinbox.setValue(0)
            
            # Check if this is a baudrate parameter that supports calculation
            if param_name in ('CanControllerBaudRate', 'CanControllerFdBaudRate'):
                container = QWidget()
                layout = QHBoxLayout(container)
                layout.setContentsMargins(0, 0, 0, 0)
                layout.setSpacing(2)
                layout.addWidget(spinbox)
                
                calc_btn = QToolButton()
                calc_btn.setText("🔢")
                calc_btn.setToolTip("Calculate timing parameters")
                calc_btn.setFixedSize(24, 24)
                is_fd = (param_name == 'CanControllerFdBaudRate')
                calc_btn.clicked.connect(lambda checked, sp=spinbox, fd=is_fd: self._on_calc_baudrate_clicked(sp, fd))
                layout.addWidget(calc_btn)
                
                return container, spinbox.value, spinbox.valueChanged
            
            return spinbox, spinbox.value, spinbox.valueChanged
            
        elif param_def.param_type == EcucParameterType.FLOAT:
            # DoubleSpinBox for floats
            spinbox = QDoubleSpinBox()
            spinbox.setRange(
                param_def.min_value if param_def.min_value is not None else -1e308,
                param_def.max_value if param_def.max_value is not None else 1e308
            )
            spinbox.setDecimals(4)
            
            try:
                val = float(current_value) if current_value is not None else 0.0
                spinbox.setValue(val)
            except (ValueError, TypeError):
                spinbox.setValue(0.0)
                
            # Check if this is a baudrate parameter that supports calculation
            if param_name in ('CanControllerBaudRate', 'CanControllerFdBaudRate'):
                container = QWidget()
                layout = QHBoxLayout(container)
                layout.setContentsMargins(0, 0, 0, 0)
                layout.setSpacing(2)
                layout.addWidget(spinbox)
                
                calc_btn = QToolButton()
                calc_btn.setText("🔢")
                calc_btn.setToolTip("Calculate timing parameters")
                calc_btn.setFixedSize(24, 24)
                is_fd = (param_name == 'CanControllerFdBaudRate')
                calc_btn.clicked.connect(lambda checked, sp=spinbox, fd=is_fd: self._on_calc_baudrate_clicked(sp, fd))
                layout.addWidget(calc_btn)
                
                return container, spinbox.value, spinbox.valueChanged
                
            return spinbox, spinbox.value, spinbox.valueChanged
            
        else:
            # Default: LineEdit for strings, functions, etc.
            lineedit = QLineEdit()
            lineedit.setText(str(current_value) if current_value is not None else "")
            return lineedit, lineedit.text, lineedit.textChanged
        
    def _update_variant_selector(self, instance: EcucContainerValue):
        """Update variant combo box with project variants and current selection"""
        self.variant_combo.blockSignals(True)
        self.variant_combo.clear()
        self.variant_combo.addItem("None (All Variants)")
        
        # Get project variants if available
        if self.project and hasattr(self.project, 'variants'):
            for v in self.project.variants:
                self.variant_combo.addItem(v)
        elif self.project and hasattr(self.project, 'get_variants'):
             for v in self.project.get_variants():
                self.variant_combo.addItem(v)
        
        # Select current
        if instance.variant:
            index = self.variant_combo.findText(instance.variant)
            if index >= 0:
                self.variant_combo.setCurrentIndex(index)
            else:
                # Variant might have been deleted or manually set
                self.variant_combo.addItem(instance.variant)
                self.variant_combo.setCurrentText(instance.variant)
        else:
            self.variant_combo.setCurrentIndex(0)
            
        self.variant_combo.blockSignals(False)

    def _on_instance_variant_changed(self, variant_text: str):
        """Handle change of variant for the current instance"""
        if not self.current_instance:
            return
            
        new_variant = None if variant_text == "None (All Variants)" else variant_text
        if self.current_instance.variant != new_variant:
            self.current_instance.variant = new_variant
            self.current_instance.mark_modified()
            if self.project:
                self.project.is_modified = True
            # Emit signal to notify the main window to refresh the tree
            self.instance_variant_changed.emit(self.current_instance)


    
    def _is_boolean_parameter(self, param_def: EcucParameterDef) -> bool:
        """Check if parameter is boolean type"""
        return param_def.param_type == EcucParameterType.BOOLEAN
    
    def _filter_parameters(self):
        """Filter parameters based on search text and type filter"""
        if not hasattr(self, 'params_table'):
            return

        search_text = self.param_search.text().lower()
        type_filter = self.type_filter.currentText()

        # Map friendly names to internal Enum names
        type_map = {
            "Integer": "INTEGER",
            "Float": "FLOAT",
            "Boolean": "BOOLEAN",
            "Enum": "ENUMERATION",
            "String": "STRING"
        }

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
            elif type_filter == "⚡ Overridden Only":
                type_match = hasattr(self, '_override_rows') and row in self._override_rows
            elif type_filter != "All Types":
                target_type = type_map.get(type_filter, type_filter.upper())
                type_match = param_type == target_type

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
    
    def _get_chip_constraint_text(self, param_name: str, container_def: EcucContainerDef) -> str:
        """Get chip-specific constraint for a parameter from ChipConstraintService.
        
        Tries multiple path patterns:
        - {ModuleName}.{ParamName} (e.g., Can.MaxNodes)
        - {ModuleName}.{ContainerName}.{ParamName} (e.g., Can.CanGeneral.MaxNodes)
        """
        if not self.chip_constraint_service:
            return "-"
        
        # Get module name from container definition path or current instance
        module_name = None
        if self.current_instance and hasattr(self.current_instance, 'module_config'):
            module_config = self.current_instance.module_config
            if module_config and hasattr(module_config, 'module_name'):
                module_name = module_config.module_name
        
        # Fallback: extract from container def short_name pattern or any path-like attribute
        if not module_name and hasattr(container_def, 'path') and container_def.path:
            # Path like "/AUTOSAR/Can/CanGeneral" -> "Can"
            parts = container_def.path.strip('/').split('/')
            if len(parts) >= 2:
                module_name = parts[1] if parts[0] == 'AUTOSAR' else parts[0]
        
        # Last fallback: try to infer from instance path
        if not module_name and self.current_instance:
            instance_path = self.current_instance.get_path() if hasattr(self.current_instance, 'get_path') else ""
            if instance_path:
                # Path like "/Can/CanGeneral/CanGeneral" -> "Can"
                parts = instance_path.strip('/').split('/')
                if parts:
                    module_name = parts[0]
        
        if not module_name:
            return "-"
        
        # Special case: CanControllerBaseAddress - display that it's chip-constrained
        if param_name == 'CanControllerBaseAddress' and module_name == 'Can':
            chip_addrs = self._get_chip_can_base_addresses()
            if chip_addrs:
                return f"Chip Nodes ({len(chip_addrs)})"
        
        # Special case: CanHardwareChannel - mapping to Can.HwUnitNode
        if param_name == 'CanHardwareChannel' and module_name == 'Can':
            allowed = self.chip_constraint_service.get_enum_constraint(f"{module_name}.HwUnitNode")
            if allowed:
                return f"Allowed: {', '.join(allowed[:2])}..."
        
        # Try looking up constraint with various path patterns
        paths_to_try = [
            f"{module_name}.{param_name}",  # e.g., Can.MaxNodes
            f"{module_name}.{container_def.short_name}.{param_name}",  # e.g., Can.CanGeneral.MaxNodes
        ]
        
        for path in paths_to_try:
            constraint_val = self.chip_constraint_service.get_constraint(path)
            if constraint_val is not None:
                return str(constraint_val)
        
        return "-"

    def _get_allowed_literals(self, param_name: str, container_def: EcucContainerDef,
                              param_def=None) -> List[str]:
        """Get allowed enum values for a parameter from chip constraints.

        Tries multiple path patterns to find a matching constraint list.
        If param_def has a range_expr (from XDM), uses it for precise lookup.
        """
        if not self.chip_constraint_service:
            return []

        # Fast path: if param_def carries a range_expr, extract the ecu:list path directly
        if param_def and getattr(param_def, 'range_expr', None):
            from autosar_configurator.core.parser.xdm_expression_resolver import XdmExpressionResolver
            ecu_path = XdmExpressionResolver().extract_ecu_path(param_def.range_expr)
            if ecu_path:
                allowed = self.chip_constraint_service.get_enum_constraint(ecu_path)
                if allowed:
                    return allowed

            # Complex expression: try to extract string prefix from text:concat patterns
            # e.g., text:concat('Adc.AdcChannels_Adc', ...) -> search keys starting with 'Adc.AdcChannels_Adc'
            import re
            concat_strings = re.findall(r"text:concat\s*\(\s*'([^']+)'", param_def.range_expr)
            if concat_strings:
                all_constraints = self.chip_constraint_service.get_all_constraints()
                for prefix in concat_strings:
                    # Collect all matching lists, pick the most comprehensive (largest)
                    best = None
                    for key, val in all_constraints.items():
                        if key.startswith(prefix) and isinstance(val, list):
                            if best is None or len(val) > len(best):
                                best = val
                    if best:
                        return best

        # Get module name (reuse same resolution logic)
        module_name = None
        if self.current_instance and hasattr(self.current_instance, 'module_config'):
            module_config = self.current_instance.module_config
            if module_config and hasattr(module_config, 'module_name'):
                module_name = module_config.module_name

        if not module_name and hasattr(container_def, 'path') and container_def.path:
            parts = container_def.path.strip('/').split('/')
            if len(parts) >= 2:
                module_name = parts[1] if parts[0] == 'AUTOSAR' else parts[0]

        if not module_name:
            return []

        # Try various patterns
        paths_to_try = [
            f"{module_name}.{param_name}",
            f"{module_name}.{container_def.short_name}.{param_name}",
        ]

        # Also try stripping module name prefix from param name
        # e.g., "AdcResolution" with module "Adc" -> try "Adc.Resolution"
        stripped = param_name
        if param_name.lower().startswith(module_name.lower()):
            stripped = param_name[len(module_name):]
            if stripped:
                paths_to_try.append(f"{module_name}.{stripped}")

        # Also try stripping container-level prefixes from the param name
        # Derive prefixes dynamically from the actual container hierarchy path
        # e.g., container path ".../AdcHwUnit/AdcChannel" -> prefixes ["Channel", "HwUnit"]
        # so "AdcChannelRefVoltsrcLow" -> stripped="ChannelRefVoltsrcLow" -> try "Adc.RefVoltsrcLow"
        if hasattr(container_def, 'definition_ref') and container_def.definition_ref:
            ref_parts = container_def.definition_ref.strip('/').split('/')
            for part in ref_parts:
                # Strip module prefix from container name to get the container-level prefix
                ctr_prefix = part
                if ctr_prefix.lower().startswith(module_name.lower()):
                    ctr_prefix = ctr_prefix[len(module_name):]
                if ctr_prefix and stripped.startswith(ctr_prefix):
                    further = stripped[len(ctr_prefix):]
                    if further:
                        paths_to_try.append(f"{module_name}.{further}")

        for path in paths_to_try:
            allowed = self.chip_constraint_service.get_enum_constraint(path)
            if allowed:
                return allowed

        # Fallback: case-insensitive search across all constraints
        all_constraints = self.chip_constraint_service.get_all_constraints()
        for path in paths_to_try:
            path_lower = path.lower()
            for key, val in all_constraints.items():
                if key.lower() == path_lower:
                    if isinstance(val, list):
                        return val
                    if isinstance(val, str) and val:
                        return [val]

        return []
    
    def _get_chip_can_base_addresses(self) -> list:
        """Get list of CAN node base addresses from chip constraints.
        
        Returns:
            List of tuples: [(node_name, hex_address), ...]
            e.g., [('Node00', '0xC0090000'), ('Node01', '0xC0091800'), ...]
        """
        if not self.chip_constraint_service:
            return []
        
        addresses = []
        
        # Get all constraints that match Can.NodeXXBaseAddress pattern
        all_constraints = self.chip_constraint_service.get_all_constraints()
        
        for key, value in all_constraints.items():
            if key.startswith('Can.Node') and 'BaseAddress' in key:
                # Extract node name from key like "Can.Node00BaseAddress"
                node_name = key.replace('Can.', '').replace('BaseAddress', '')
                addresses.append((node_name, value))
        
        # Sort by node name (Node00, Node01, Node10, Node11, etc.)
        addresses.sort(key=lambda x: x[0])
        
        return addresses
    
    def _get_parameter_tooltip(self, param_def: EcucParameterDef) -> str:
        """Generate rich tooltip content for a parameter"""
        lines = []
        
        # Description (if available)
        if param_def.description:
            lines.append(param_def.description)
            lines.append("")  # Empty line separator
        
        # Type
        lines.append(f"Type: {param_def.param_type.name}")
        
        # Default value
        if param_def.default_value is not None:
            lines.append(f"Default: {param_def.default_value}")
        
        # Constraints based on type
        if param_def.param_type == EcucParameterType.ENUMERATION:
            if param_def.literals:
                lines.append(f"Values: {', '.join(param_def.literals[:5])}")
                if len(param_def.literals) > 5:
                    lines.append(f"  ... and {len(param_def.literals) - 5} more")
        elif param_def.param_type in (EcucParameterType.INTEGER, EcucParameterType.FLOAT):
            if param_def.min_value is not None or param_def.max_value is not None:
                min_str = str(param_def.min_value) if param_def.min_value is not None else "-∞"
                max_str = str(param_def.max_value) if param_def.max_value is not None else "+∞"
                lines.append(f"Range: [{min_str}, {max_str}]")
        
        # Required status
        lines.append(f"Required: {'Yes' if param_def.is_required else 'No'}")
        
        return "\n".join(lines)
    
    def _on_value_changed(self, param_name: str, value: Any):
        """Handle parameter value change"""
        if not self.current_instance or not self.config_manager:
             return

        # Handle "(未配置)" selection - remove the parameter value
        if value == "(未配置)":
            self.current_instance.remove_parameter_value(param_name)
            if self.project:
                self.project.is_modified = True
            self.parameter_changed.emit(self.current_instance, param_name, None)
            return

        # Check if we should write to variant override instead of base config
        if self.project and hasattr(self.project, 'active_variant') and self.project.active_variant:
            variant = self.project.active_variant
            module_config = self.current_instance.module_config

            if module_config:
                param_path = f"{self.current_instance.get_path()}.{param_name}"
                module_config.set_value_for_variant(param_path, value, variant)

                # NOTE: In explicit comparison mode, we do NOT refresh automatically.
                # User must click "Check Diff" to see updated highlights.

                # Still emit signal for UI updates (status bar, etc.)
                self.parameter_changed.emit(self.current_instance, param_name, value)
                return

        # No variant active - emit signal for base config modification
        self.parameter_changed.emit(self.current_instance, param_name, value)
    
    def refresh(self):
        """Refresh the panel to reflect current variant values"""
        if self.current_instance and self.current_def and self.config_manager:
            self.show_instance(self.current_instance, self.current_def, self.config_manager, self.project)
    
    def clear(self):
        """Clear panel"""
        self.current_instance = None
        self.current_def = None
        self.general_group.hide()
        self.parameters_group.hide()
        self.references_group.hide()
        self.ai_help_group.hide()
        self.empty_label.show()
    
    def _on_param_cell_clicked(self, row: int, column: int):
        """Handle parameter cell click - request AI help for first column (name)"""
        if column != 0 or not self.current_def:
            return
        
        # Check if AI suggestions are enabled in settings
        settings = QSettings("AUTOSAR", "DaVinciConfigurator")
        if not settings.value("ai_suggestions_enabled", False, type=bool):
            return  # AI suggestions disabled
        
        name_item = self.params_table.item(row, 0)
        if not name_item:
            return
        
        param_name = name_item.text()
        container_name = self.current_def.short_name
        cache_key = f"{container_name}.{param_name}"
        
        # Check cache first
        if cache_key in self.ai_help_cache:
            self.update_ai_help(self.ai_help_cache[cache_key])
            return
        
        # Show loading state with cancel button
        self.ai_help_group.show()
        self.ai_cancel_btn.show()
        self.ai_pending_request = True
        self.ai_request_cancelled = False
        self.ai_help_label.setText(f"⏳ 正在获取 **{param_name}** 的配置建议...")
        self.ai_help_label.setStyleSheet("color: #666; padding: 8px; background: #f0f8ff; border-radius: 4px;")
        
        # Emit signal to request AI help
        self.ai_help_requested.emit(container_name, param_name)
    
    def _on_ref_cell_clicked(self, row: int, column: int):
        """Handle click on references table - trigger AI help for reference name"""
        # Only trigger on Reference name column (column 0)
        if column != 0:
            return
        
        # Check if AI suggestions are enabled in settings
        settings = QSettings("AUTOSAR", "DaVinciConfigurator")
        if not settings.value("ai_suggestions_enabled", False, type=bool):
            return  # AI suggestions disabled
        
        name_item = self.refs_table.item(row, 0)
        if not name_item:
            return
        
        ref_name = name_item.text()
        # Strip index suffix like "[0]", "[1]" for multi-valued refs
        import re as _re
        base_ref_name = _re.sub(r'\[\d+\]$', '', ref_name)
        container_name = self.current_def.short_name
        cache_key = f"{container_name}.ref.{base_ref_name}"
        
        # Check cache first
        if cache_key in self.ai_help_cache:
            self.update_ai_help(self.ai_help_cache[cache_key])
            return
        
        # Get destination type from column 2
        dest_type_item = self.refs_table.item(row, 2)
        dest_type = dest_type_item.text() if dest_type_item else "unknown"
        
        # Show loading state with cancel button
        self.ai_help_group.show()
        self.ai_cancel_btn.show()
        self.ai_pending_request = True
        self.ai_request_cancelled = False
        self.ai_help_label.setText(f"⏳ 正在获取 Reference **{base_ref_name}** 的配置建议...")
        self.ai_help_label.setStyleSheet("color: #666; padding: 8px; background: #f0f8ff; border-radius: 4px;")
        
        # Emit signal with special format for reference
        # Format: container_name, "REF:ref_name:dest_type"
        self.ai_help_requested.emit(container_name, f"REF:{base_ref_name}:{dest_type}")
    
    def _on_ref_cell_double_clicked(self, row: int, column: int):
        """Handle double-click on references table - navigate to target container"""
        if not self.current_instance:
            return
        
        # Get the reference name from column 0
        name_item = self.refs_table.item(row, 0)
        if not name_item:
            return
        
        # Use stored UserRole data for navigation (works for both single and multi-ref)
        ref_value = name_item.data(Qt.UserRole)
        if isinstance(ref_value, EcucReferenceValue):
            if ref_value.is_resolved and ref_value.target is not None:
                target_path = ref_value.target.get_path()
                self.reference_jump_requested.emit(target_path)
            elif ref_value.value_ref:
                self.reference_jump_requested.emit(ref_value.value_ref)
            return
        
        # Fallback: look up by name in single-valued references
        ref_name = name_item.text()
        if ref_name in self.current_instance.reference_values:
            rv = self.current_instance.reference_values[ref_name]
            if rv.is_resolved and rv.target is not None:
                self.reference_jump_requested.emit(rv.target.get_path())
            elif rv.value_ref:
                self.reference_jump_requested.emit(rv.value_ref)

    
    def update_ai_help(self, help_text: str):
        """Update AI help panel with response"""
        # Ignore if cancelled
        if self.ai_request_cancelled:
            return
        
        self.ai_help_group.show()
        self.ai_cancel_btn.hide()
        self.ai_pending_request = False
        self.ai_help_label.setText(help_text)
        self.ai_help_label.setStyleSheet("color: #333; padding: 8px; background: #f0fff0; border-radius: 4px; border-left: 3px solid #4CAF50;")
    
    def cache_ai_help(self, container_name: str, param_name: str, help_text: str):
        """Cache AI help response"""
        # Don't cache if cancelled
        if self.ai_request_cancelled:
            return
        cache_key = f"{container_name}.{param_name}"
        self.ai_help_cache[cache_key] = help_text
        self.ai_pending_request = False
        self.current_ai_process = None  # Track current QProcess for cancellation
    
    def _cancel_ai_request(self):
        """Cancel the current AI request by killing the subprocess"""
        self.ai_request_cancelled = True
        self.ai_pending_request = False
        
        # Kill the QProcess if running - this truly terminates the subprocess
        if hasattr(self, 'current_ai_process') and self.current_ai_process:
            self.current_ai_process.kill()  # SIGKILL - force termination
            self.current_ai_process = None
        
        # Also handle legacy worker if exists
        if hasattr(self, 'current_ai_worker') and self.current_ai_worker:
            self.current_ai_worker.cancelled = True
        
        self.ai_cancel_btn.hide()
        self.ai_help_label.setText("✅ 请求已强制终止")
        self.ai_help_label.setStyleSheet("color: #28a745; padding: 8px; background: #d4edda; border-radius: 4px;")
    
    def _close_ai_help(self):
        """Close the AI help panel"""
        # Also cancel any pending request
        if self.ai_pending_request:
            self._cancel_ai_request()
        self.ai_help_group.hide()
        self.ai_pending_request = False
    
    def _show_ai_help_menu(self, position):
        """Show context menu for AI help panel"""
        from PySide6.QtWidgets import QMenu
        
        menu = QMenu(self)
        
        # Cancel option (only if request is pending)
        if self.ai_pending_request:
            cancel_action = menu.addAction("🛑 取消请求")
            cancel_action.triggered.connect(self._cancel_ai_request)
            menu.addSeparator()
        
        close_action = menu.addAction("❌ 关闭提示")
        close_action.triggered.connect(self._close_ai_help)
        
        clear_cache_action = menu.addAction("🗑️ 清除缓存")
        clear_cache_action.triggered.connect(self._clear_ai_cache)
        
        menu.exec(self.ai_help_group.mapToGlobal(position))
    
    def _clear_ai_cache(self):
        """Clear AI help cache"""
        self.ai_help_cache.clear()
        self.ai_help_label.setText("✅ 缓存已清除")
        self.ai_help_label.setStyleSheet("color: #666; padding: 8px; background: #f8f8f8; border-radius: 4px;")
    
    def _on_calc_baudrate_clicked(self, spinbox: QDoubleSpinBox, is_fd: bool = False):
        """Handle calculate button click for baudrate parameters
        
        Calculates optimal timing parameters (PRESDIV, PropSeg, Seg1, Seg2, SJW)
        based on the current baudrate value and clock frequency.
        """
        try:
            from ...core.can_baudrate_calculator import calculate_can_timing
        except ImportError:
            QMessageBox.warning(self, "模块缺失", "找不到波特率计算模块 can_baudrate_calculator.py")
            return
        
        baudrate_kbps = spinbox.value()
        if baudrate_kbps <= 0:
            QMessageBox.warning(self, "无效值", "请先输入有效的波特率 (> 0)")
            return
        
        # Get clock frequency from CanCpuClockRef reference
        clock_hz = self._get_can_clock_frequency()
        if clock_hz is None or clock_hz <= 0:
            # Use default common clock frequency
            clock_hz = 80_000_000  # 80 MHz default
            QMessageBox.information(
                self, "使用默认时钟",
                f"未能获取 CanCpuClockRef 引用的时钟频率，将使用默认值 {clock_hz/1e6:.0f} MHz"
            )
        
        # Calculate timing parameters
        result = calculate_can_timing(clock_hz, int(baudrate_kbps * 1000), is_fd=is_fd)
        
        if not result:
            QMessageBox.warning(
                self, "计算失败",
                f"无法为 {baudrate_kbps} kbps 找到有效的时序参数组合\n"
                f"时钟频率: {clock_hz/1e6:.0f} MHz"
            )
            return
        
        # Update sibling timing parameters in the table
        timing_params = {
            'CanControllerPRESDIV': result['PRESDIV'],
            'CanControllerPropSeg': result['PropSeg'],
            'CanControllerSeg1': result['Seg1'],
            'CanControllerSeg2': result['Seg2'],
            'CanControllerSyncJumpWidth': result['SJW'],
        }
        
        # If FD, update FD-specific params instead
        if is_fd:
            timing_params = {
                'CanControllerFdBaudRatePRESDIV': result['PRESDIV'],
                'CanControllerPropSeg': result['PropSeg'],  # FD shares this
                'CanControllerSeg1': result['Seg1'],
                'CanControllerSeg2': result['Seg2'],
                'CanControllerSyncJumpWidth': result['SJW'],
            }
        
        updated_count = 0
        for param_name, param_value in timing_params.items():
            if self._update_parameter_in_table(param_name, param_value):
                updated_count += 1
        
        # Show result dialog
        QMessageBox.information(
            self, "✅ 计算完成",
            f"已更新 {updated_count} 个时序参数:\n\n"
            f"PRESDIV = {result['PRESDIV']}\n"
            f"PropSeg = {result['PropSeg']}\n"
            f"Seg1 = {result['Seg1']}\n"
            f"Seg2 = {result['Seg2']}\n"
            f"SJW = {result['SJW']}\n\n"
            f"────────────────\n"
            f"实际波特率: {result['actual_baudrate']/1000:.2f} kbps\n"
            f"采样点: {result['sample_point']:.1f}%\n"
            f"误差: {result['error_ppm']:.1f} ppm"
        )
    
    def _get_can_clock_frequency(self) -> Optional[int]:
        """Get CAN clock frequency from CanCpuClockRef reference
        
        Returns:
            Clock frequency in Hz, or None if not found
        """
        if not self.current_instance:
            return None
        
        # Try to find parent CanController container to get CanCpuClockRef
        # The current instance should be CanControllerBaudrateConfig,
        # and its parent should be CanController which has CanCpuClockRef
        try:
            parent = self.current_instance.parent
            if parent and hasattr(parent, 'reference_values'):
                if 'CanCpuClockRef' in parent.reference_values:
                    ref_value = parent.reference_values['CanCpuClockRef']
                    if ref_value.is_resolved and ref_value.target:
                        # Get McuClockReferencePointFrequency from target
                        target = ref_value.target
                        if 'McuClockReferencePointFrequency' in target.parameter_values:
                            freq_val = target.parameter_values['McuClockReferencePointFrequency'].value
                            return int(float(freq_val))
        except Exception as e:
            print(f"Error getting CAN clock frequency: {e}")
        
        return None
    
    def _update_parameter_in_table(self, param_name: str, value: int) -> bool:
        """Update a parameter value in the params table
        
        Args:
            param_name: Name of the parameter to update
            value: New value to set
            
        Returns:
            True if parameter was found and updated
        """
        for row in range(self.params_table.rowCount()):
            name_item = self.params_table.item(row, 0)
            if name_item and name_item.text() == param_name:
                # Get the widget in column 1
                widget = self.params_table.cellWidget(row, 1)
                if widget:
                    # Handle different widget types
                    if isinstance(widget, QSpinBox):
                        widget.setValue(value)
                        return True
                    elif isinstance(widget, QDoubleSpinBox):
                        widget.setValue(float(value))
                        return True
                    elif hasattr(widget, 'findChild'):
                        # Check for nested spinbox in container widget
                        spinbox = widget.findChild(QSpinBox)
                        if spinbox:
                            spinbox.setValue(value)
                            return True
                        dspinbox = widget.findChild(QDoubleSpinBox)
                        if dspinbox:
                            dspinbox.setValue(float(value))
                            return True
        return False

    def _populate_references(self, instance: EcucContainerValue, container_def: EcucContainerDef):
        """Populate references table with resolution error display.
        
        Multi-valued refs (upper_multiplicity > 1) are expanded into individual rows
        with indexed names like RefName[0], RefName[1], etc. and read-only target labels.
        """
        # Build a flat list of (display_name, ref_def, ref_value_or_None, is_multi) rows
        rows_data = []
        
        for ref_name, ref_def in container_def.references.items():
            is_multi = getattr(ref_def, 'upper_multiplicity', 1) > 1 or \
                       getattr(ref_def, 'upper_multiplicity', 1) == -1  # -1 = INFINITE
            
            if is_multi and ref_name in instance.multi_reference_values:
                # Expand each indexed value into its own row
                multi_refs = instance.multi_reference_values[ref_name]
                if multi_refs:
                    for idx, ref_val in enumerate(multi_refs):
                        rows_data.append((f"{ref_name}[{idx}]", ref_def, ref_val, True))
                else:
                    # No values yet, show empty placeholder
                    rows_data.append((ref_name, ref_def, None, True))
            else:
                # Single-valued reference (normal path)
                ref_val = instance.reference_values.get(ref_name)
                rows_data.append((ref_name, ref_def, ref_val, False))
        
        self.refs_table.setRowCount(len(rows_data))
        error_count = 0
        
        for row, (display_name, ref_def, ref_val, is_multi) in enumerate(rows_data):
            # Column 0: Reference name (store ref_value in UserRole for navigation)
            name_item = QTableWidgetItem(display_name)
            name_item.setToolTip(f"Destination: {ref_def.destination_ref}")
            if ref_val is not None:
                name_item.setData(Qt.UserRole, ref_val)
            self.refs_table.setItem(row, 0, name_item)
            
            # Column 1: Target selector or read-only label
            if is_multi and ref_val is not None:
                # Multi-valued ref: show read-only label with the target path
                target_label = ref_val.value_ref or "(Not set)"
                if ref_val.is_resolved and ref_val.target:
                    target_label = ref_val.target.get_path()
                label_item = QTableWidgetItem(target_label)
                label_item.setFlags(label_item.flags() & ~Qt.ItemIsEditable)
                label_item.setToolTip(ref_val.value_ref or "")
                self.refs_table.setItem(row, 1, label_item)
                self.refs_table.removeCellWidget(row, 1)
            else:
                # Single-valued ref: editable ComboBox selector
                current_value = None
                is_variant_override = False
                
                ref_name_base = display_name  # For single-valued, display_name == ref_name
                
                if self.project and hasattr(self.project, 'active_variant') and self.project.active_variant:
                    variant = self.project.active_variant
                    module_config = instance.module_config
                    if module_config:
                        ref_path = f"{instance.get_path()}.ref:{ref_name_base}"
                        override_value, is_override = module_config.get_value_for_variant(ref_path, variant)
                        if is_override:
                            current_value = override_value
                            is_variant_override = True
                
                if current_value is None and ref_val is not None:
                    current_value = ref_val.value_ref
                
                self.refs_table.setItem(row, 1, QTableWidgetItem(""))
                selector = self._create_reference_selector(ref_name_base, ref_def, current_value)
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
            
            # Column 4: Status (resolution error indicator)
            status_icon = ""
            status_tooltip = ""
            status_color = None
            
            if ref_val is not None:
                if ref_val.has_error:
                    error = ref_val.resolution_error
                    error_count += 1
                    severity_icons = {
                        "error": "❌",
                        "warning": "⚠️",
                        "info": "ℹ️"
                    }
                    status_icon = severity_icons.get(error.severity, "❓")
                    status_tooltip = error.to_user_message()
                    status_color = {
                        "error": QColor(255, 200, 200),
                        "warning": QColor(255, 240, 200),
                        "info": QColor(240, 240, 240),
                    }.get(error.severity)
                elif ref_val.is_resolved:
                    status_icon = "✅"
                    status_tooltip = "引用解析成功"
                else:
                    status_icon = "⏳"
                    status_tooltip = "引用尚未解析"
            else:
                status_icon = "◯"
                status_tooltip = "未配置"
            
            status_item = QTableWidgetItem(status_icon)
            status_item.setTextAlignment(Qt.AlignCenter)
            status_item.setToolTip(status_tooltip)
            if status_color:
                status_item.setBackground(status_color)
            self.refs_table.setItem(row, 4, status_item)
        
        # Update title with total count (single + multi-expanded)
        total_refs = len(rows_data)
        title = f"🔗 References ({total_refs})"
        if error_count > 0:
            title += f" ⚠️ {error_count} error{'s' if error_count > 1 else ''}"
        self.references_group.setTitle(title)
        
        # Adjust column widths
        self.refs_table.resizeColumnsToContents()
    
    def _create_reference_selector(self, ref_name: str, ref_def, current_value: str) -> QComboBox:
        """Create ComboBox for reference selection"""
        combo = QComboBox()
        combo.addItem("(Not set)", None)
        
        # Helper to search containers in a manager
        def search_in_manager(manager):
            for container in manager.configuration.containers:
                self._add_reference_targets(combo, container, ref_def, added_paths=added_paths)

        # Get available targets - keep track of added paths to avoid duplicates
        added_paths = set()
        
        if hasattr(self, 'project') and self.project:
            # Search all modules in project
            for module_name, manager in self.project.module_managers.items():
                if manager.configuration:
                    search_in_manager(manager)
        elif self.config_manager:
            # Single module mode
            search_in_manager(self.config_manager)
        
        # Set current value - handle legacy /Config/ paths
        if current_value:
            index = combo.findData(current_value)
            
            # Try legacy path conversion if not found
            if index < 0 and current_value.startswith("/Config/"):
                # Try to find matching module-aware path
                suffix = current_value[8:]  # Remove "/Config/"
                for i in range(1, combo.count()):  # Skip "(Not set)"
                    item_path = combo.itemData(i)
                    if item_path and item_path.endswith("/" + suffix):
                        index = i
                        break
            
            if index >= 0:
                combo.setCurrentIndex(index)
            # If still not found, keep at "Not set" (index 0)
        
        # Connect signal
        combo.currentIndexChanged.connect(
            lambda idx, rname=ref_name: self._on_reference_changed(rname, combo.itemData(idx))
        )
        
        return combo

    
    def _add_reference_targets(self, combo: QComboBox, container: EcucContainerValue, ref_def, prefix="", added_paths=None):
        """Recursively add matching containers to combobox"""
        # Calculate full path for display
        display_name = f"{prefix}/{container.short_name}" if prefix else container.short_name

        # Use container's actual absolute path for value
        path = container.get_path()

        # Avoid duplicate entries
        if added_paths is not None:
            if path in added_paths:
                return
            added_paths.add(path)

        # Check if this container is a valid target
        container_def_ref = container.definition_ref or ""

        # Get all valid destination refs (for choice references, check all destinations)
        destination_refs = []
        if hasattr(ref_def, 'choice_destination_refs') and ref_def.choice_destination_refs:
            destination_refs = ref_def.choice_destination_refs
        elif ref_def.destination_ref:
            destination_refs = [ref_def.destination_ref]

        # Match strategies - check against all destination refs
        is_match = False

        for dest_ref in destination_refs:
            if is_match:
                break

            # Strategy 1: Exact match
            if container_def_ref == dest_ref:
                is_match = True
                break

            # Strategy 2: Container def ref ends with destination ref (for partial paths)
            elif dest_ref and container_def_ref.endswith(dest_ref):
                is_match = True
                break

            # Strategy 3: Destination ref ends with container's definition ref path
            # (more strict - require the full container type path to match)
            elif container_def_ref and dest_ref:
                # Extract container type from definition_ref (e.g., "AdcChannel" from ".../AdcChannel")
                container_type = container_def_ref.split('/')[-1] if container_def_ref else ""
                dest_type = dest_ref.split('/')[-1] if dest_ref else ""

                # Only match if types are equal AND the container's module path matches
                # This prevents matching AdcChannel from Crypto module when looking for Adc's AdcChannel
                if container_type and dest_type and container_type == dest_type:
                    # Additional check: verify the module context makes sense
                    # Extract module name from destination ref (e.g., /AUTOSAR/EcucDefs/Adc/... -> Adc)
                    dest_parts = dest_ref.split('/')
                    container_parts = container_def_ref.split('/')

                    # Get module name (typically after /AUTOSAR/EcucDefs/)
                    dest_module = None
                    for i, part in enumerate(dest_parts):
                        if part == "EcucDefs" and i + 1 < len(dest_parts):
                            dest_module = dest_parts[i + 1]
                            break

                    container_module = None
                    for i, part in enumerate(container_parts):
                        if part == "EcucDefs" and i + 1 < len(container_parts):
                            container_module = container_parts[i + 1]
                            break

                    # Only match if modules are the same (or if we couldn't determine module)
                    if dest_module is None or container_module is None or dest_module == container_module:
                        is_match = True
                        break

        if is_match:
            # Build enhanced display name with parameter values
            enhanced_name = self._build_enhanced_display_name(container, display_name)
            combo.addItem(enhanced_name, path)

        # Add sub-containers recursively
        for sub in container.sub_containers:
            self._add_reference_targets(combo, sub, ref_def, display_name, added_paths=added_paths)

    def _on_table_context_menu(self, pos):
        """Show context menu for parameter table"""
        item = self.params_table.itemAt(pos)
        if not item:
            return

        row = item.row()
        name_item = self.params_table.item(row, 0)
        if not name_item:
            return

        param_name = name_item.text().replace("⚡ ", "")  # Strip override indicator if present

        from PySide6.QtWidgets import QMenu
        from PySide6.QtGui import QAction

        menu = QMenu(self)

        # Check if this row is a variant override
        is_override = hasattr(self, '_override_rows') and row in self._override_rows

        if is_override:
            revert_action = QAction("↩️ 恢复基础值 (Revert to Base)", self)
            revert_action.triggered.connect(lambda: self._revert_to_base_value(param_name))
            menu.addAction(revert_action)
            menu.addSeparator()

        impact_action = QAction("🔍 Check Change Impact", self)
        impact_action.triggered.connect(lambda: self._emit_check_impact(param_name))
        menu.addAction(impact_action)

        menu.exec(self.params_table.viewport().mapToGlobal(pos))
        
    def _emit_check_impact(self, param_name: str):
        """Emit signal for impact analysis"""
        if self.current_instance:
            self.check_impact_requested.emit(self.current_instance.get_path(), param_name)

    def _revert_to_base_value(self, param_name: str):
        """Revert a variant-overridden parameter to its base value
        
        Removes the variant override entry and refreshes the panel to show the base value.
        """
        if not self.current_instance or not self.project:
            return
        
        variant = getattr(self.project, 'active_variant', None)
        if not variant:
            return
        
        module_config = self.current_instance.module_config
        if not module_config:
            return
        
        # Try both path formats
        param_path = f"{self.current_instance.get_path()}.{param_name}"
        short_path = f"{self.current_instance.short_name}.{param_name}"
        
        # Clear the override
        module_config.clear_variant_override(param_path, variant)
        module_config.clear_variant_override(short_path, variant)
        
        # Refresh the panel to show base value
        self.refresh()
        
        # Show confirmation
        QMessageBox.information(
            self, "✅ 已恢复",
            f"参数 '{param_name}' 已恢复为基础配置值\n\n"
            f"变体 '{variant}' 中的覆盖值已移除"
        )
    
    def _build_enhanced_display_name(self, container: EcucContainerValue, base_name: str) -> str:
        """Build a descriptive display name - show full path"""
        # Return the full path for clarity
        return container.get_path()
    
    def _on_reference_changed(self, ref_name: str, target_path: str):
        """Handle reference value change"""
        if not self.current_instance or not self.config_manager:
            return
        
        try:
            # Check if we should write to variant override instead of base config
            if self.project and hasattr(self.project, 'active_variant') and self.project.active_variant:
                variant = self.project.active_variant
                module_config = self.current_instance.module_config
                
                if module_config:
                    # Use ref: prefix to distinguish from parameters
                    ref_path = f"{self.current_instance.get_path()}.ref:{ref_name}"
                    module_config.set_value_for_variant(ref_path, target_path, variant)
                    
                    # Emit signal for UI updates
                    self.parameter_changed.emit(self.current_instance, f"ref:{ref_name}", target_path)
                    
                    # Refresh the Status column after a short delay
                    from PySide6.QtCore import QTimer
                    QTimer.singleShot(100, self._refresh_reference_status)
                    return
            
            # No variant active - use command for base config modification
            self.parameter_changed.emit(self.current_instance, f"ref:{ref_name}", target_path)
            
            # Refresh the Status column after a short delay to allow command to execute
            from PySide6.QtCore import QTimer
            QTimer.singleShot(100, self._refresh_reference_status)
            
        except Exception as e:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.warning(self, "Reference Error", f"Failed to set reference: {e}")

    
    def _refresh_reference_status(self):
        """Refresh reference status indicators"""
        if not self.current_instance or not self.current_def:
            return
        
        self._populate_references(self.current_instance, self.current_def)

class ListEditorWidget(QWidget):
    """Widget for editing a list of values"""
    
    valueChanged = Signal(list)
    
    def __init__(self, param_name: str, param_def: EcucParameterDef, initial_value: List[Any], parent_panel: 'DaVinciConfigPanel'):
        super().__init__()
        self.param_name = param_name
        self.param_def = param_def
        self.values = initial_value[:]
        self.parent_panel = parent_panel
        
        self._setup_ui()
        
    def _setup_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        
        # List of values
        self.list_widget = QListWidget()
        self.list_widget.setFixedHeight(120)  # Restricted height
        layout.addWidget(self.list_widget)
        
        # Populate list
        self._refresh_list()
        
        # Buttons
        btn_layout = QHBoxLayout()
        self.add_btn = QPushButton("Add")
        self.remove_btn = QPushButton("Remove")
        self.remove_btn.setEnabled(False)
        
        btn_layout.addWidget(self.add_btn)
        btn_layout.addWidget(self.remove_btn)
        btn_layout.addStretch()
        
        layout.addLayout(btn_layout)
        
        # Connections
        self.add_btn.clicked.connect(self._add_item)
        self.remove_btn.clicked.connect(self._remove_item)
        self.list_widget.itemSelectionChanged.connect(self._update_buttons)
        self.list_widget.itemDoubleClicked.connect(self._edit_item)
        
    def _refresh_list(self):
        self.list_widget.clear()
        for idx, val in enumerate(self.values):
            item = QListWidgetItem(str(val))
            item.setData(Qt.UserRole, idx)
            self.list_widget.addItem(item)
            
    def _update_buttons(self):
        self.remove_btn.setEnabled(len(self.list_widget.selectedItems()) > 0)
        
    def _add_item(self):
        # We need a dialog or usage of the single value editor to get the new value
        # For simplicity, let's use a default value appropriate for the type
        # Or launch a small input dialog using the existing editor logic?
        
        # Simplified: Add default value then let user edit
        default_val = self.param_def.default_value
        if default_val is None:
            if self.param_def.param_type == EcucParameterType.INTEGER: default_val = 0
            elif self.param_def.param_type == EcucParameterType.FLOAT: default_val = 0.0
            elif self.param_def.param_type == EcucParameterType.BOOLEAN: default_val = False
            elif self.param_def.param_type == EcucParameterType.ENUMERATION: 
                default_val = self.param_def.literals[0] if self.param_def.literals else ""
            else: default_val = ""
            
        self.values.append(default_val)
        self._refresh_list()
        self.valueChanged.emit(self.values)
        
        # Auto start edit of new item
        self.list_widget.setCurrentRow(len(self.values)-1)
        self._edit_item(self.list_widget.currentItem())

    def _remove_item(self):
        row = self.list_widget.currentRow()
        if row >= 0:
            self.values.pop(row)
            self._refresh_list()
            self.valueChanged.emit(self.values)

    def _edit_item(self, item):
        if not item: return
        index = item.data(Qt.UserRole)
        current_val = self.values[index]
        
        # Use QInputDialog for simple edits, or custom dialog with the actual editor widget
        # Since we have logic to create specific editors, let's reuse it differently.
        # Actually standard input dialogs are easiest for now.
        
        # TODO: Use proper editor widget in a dialog for better UX (especially Enums)
        # For now, simplistic approach:
        
        from PySide6.QtWidgets import QDialog, QVBoxLayout, QDialogButtonBox
        
        dialog = QDialog(self)
        dialog.setWindowTitle(f"Edit {self.param_def.short_name}")
        dlg_layout = QVBoxLayout(dialog)
        
        # Reuse creation logic
        editor, getter, signal = self.parent_panel._create_single_value_editor(self.param_def, current_val)
        dlg_layout.addWidget(editor)
        
        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(dialog.accept)
        buttons.rejected.connect(dialog.reject)
        dlg_layout.addWidget(buttons)
        
        if dialog.exec():
            new_val = getter()
            self.values[index] = new_val
            self._refresh_list()
            self.valueChanged.emit(self.values)
