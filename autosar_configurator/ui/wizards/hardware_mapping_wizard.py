"""
Hardware Mapping Wizard
Configure AUTOSAR modules based on chip hardware resources

Version 2.0 - Generic/Data-driven implementation using YAML mapping rules
"""
from pathlib import Path
from typing import Dict, Any, Optional, List

from PySide6.QtWidgets import (
    QVBoxLayout, QHBoxLayout, QLabel, QComboBox, QLineEdit,
    QFormLayout, QSpinBox, QCheckBox, QTextEdit, QTableWidget,
    QTableWidgetItem, QHeaderView, QGroupBox, QListWidget,
    QListWidgetItem, QTabWidget, QWidget, QTreeWidget,
    QTreeWidgetItem, QPushButton, QDoubleSpinBox, QScrollArea
)
from PySide6.QtCore import Qt, Signal

from .wizard_base import ConfigWizard, WizardPage
from ...core.model.definition_model import EcucModuleDef
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager
from ...core.hardware import (
    # Legacy types (for backward compatibility with properties files)
    ChipDatabase, ChipDefinition,
    # New generic types
    GenericChipDefinition, GenericResourceDef,
    GenericResourceMapper, GenericMappingAction, GenericMappingActionType,
    MappingResult,
    MappingRuleLoader, get_default_rule_loader,
    ChipDefinitionLoader, convert_legacy_chip
)


class ChipSelectionPage(WizardPage):
    """Page 1: Select chip model"""

    chip_selected = Signal(object)  # GenericChipDefinition

    def __init__(self, chip_database: ChipDatabase, project_path: Optional[Path] = None):
        self.chip_database = chip_database
        self.project_path = project_path
        self.chip_combo = QComboBox()
        self.chip_info_text = QTextEdit()
        self.selected_chip: Optional[GenericChipDefinition] = None
        self._generic_chips: Dict[str, GenericChipDefinition] = {}

        super().__init__(
            "Select Chip",
            "Choose the target chip for hardware configuration"
        )

    def _setup_ui(self):
        # Chip selection
        chip_group = QGroupBox("Target Chip")
        chip_layout = QVBoxLayout()

        chip_select_layout = QHBoxLayout()
        chip_select_layout.addWidget(QLabel("Chip:"))
        chip_select_layout.addWidget(self.chip_combo, 1)

        detect_btn = QPushButton("Detect from Project")
        detect_btn.clicked.connect(self._detect_chip)
        chip_select_layout.addWidget(detect_btn)

        load_btn = QPushButton("Load from File...")
        load_btn.clicked.connect(self._load_chip_from_file)
        chip_select_layout.addWidget(load_btn)

        chip_layout.addLayout(chip_select_layout)
        chip_group.setLayout(chip_layout)
        self.layout.addWidget(chip_group)

        # Chip info
        info_group = QGroupBox("Chip Information")
        info_layout = QVBoxLayout()

        self.chip_info_text.setReadOnly(True)
        self.chip_info_text.setMaximumHeight(250)
        info_layout.addWidget(self.chip_info_text)

        info_group.setLayout(info_layout)
        self.layout.addWidget(info_group)

        self.layout.addStretch()

        # Populate chips
        self._populate_chips()

        # Connect signals
        self.chip_combo.currentIndexChanged.connect(self._on_chip_changed)

    def _populate_chips(self):
        """Populate chip combo box with available chips"""
        self.chip_combo.clear()
        self._generic_chips.clear()

        # Load chips from database and convert to generic format
        for chip_name in self.chip_database.list_chips():
            legacy_chip = self.chip_database.get_chip(chip_name)
            if legacy_chip:
                generic_chip = convert_legacy_chip(legacy_chip)
                self._generic_chips[chip_name] = generic_chip

                label = f"{generic_chip.name}"
                if generic_chip.description:
                    label += f" - {generic_chip.description[:40]}"
                self.chip_combo.addItem(label, chip_name)

        # Also load from YAML chip directory
        chip_yaml_dir = Path(__file__).parent.parent.parent / "data" / "chips"
        if chip_yaml_dir.exists():
            loader = ChipDefinitionLoader()
            for yaml_file in chip_yaml_dir.glob("*.yaml"):
                try:
                    generic_chip = loader.load_from_yaml(yaml_file)
                    if generic_chip and generic_chip.name not in self._generic_chips:
                        self._generic_chips[generic_chip.name] = generic_chip
                        label = f"{generic_chip.name}"
                        if generic_chip.description:
                            label += f" - {generic_chip.description[:40]}"
                        self.chip_combo.addItem(label, generic_chip.name)
                except Exception as e:
                    print(f"Warning: Failed to load chip from {yaml_file}: {e}")

        if self.chip_combo.count() > 0:
            self._on_chip_changed()

    def _detect_chip(self):
        """Try to detect chip from project"""
        if not self.project_path:
            return

        # Try to detect and load from properties file
        chip = self.chip_database.detect_and_load_from_project(self.project_path)
        if chip:
            # Convert to generic and add
            generic_chip = convert_legacy_chip(chip)
            self._generic_chips[chip.name] = generic_chip

            # Check if already in combo
            found = False
            for i in range(self.chip_combo.count()):
                if self.chip_combo.itemData(i) == chip.name:
                    self.chip_combo.setCurrentIndex(i)
                    found = True
                    break

            if not found:
                label = f"{chip.name} (detected)"
                self.chip_combo.addItem(label, chip.name)
                self.chip_combo.setCurrentIndex(self.chip_combo.count() - 1)
            return

        # Try legacy detection
        detected = self.chip_database.detect_chip_from_project(self.project_path)
        if detected:
            for i in range(self.chip_combo.count()):
                if self.chip_combo.itemData(i) == detected:
                    self.chip_combo.setCurrentIndex(i)
                    break

    def _load_chip_from_file(self):
        """Load chip definition from a YAML file or properties file"""
        from PySide6.QtWidgets import QFileDialog

        # Use wizard as parent for better dialog behavior
        parent_widget = self.wizard() if self.wizard() else self

        file_path, _ = QFileDialog.getOpenFileName(
            parent_widget,
            "Load Chip Definition",
            str(Path.home()),  # Start from home directory
            "YAML Files (*.yaml *.yml);;Properties Files (*.properties);;All Files (*)"
        )

        if not file_path:
            return

        path = Path(file_path)
        try:
            if path.suffix == '.properties':
                from ...core.hardware import build_chip_from_properties
                legacy_chip = build_chip_from_properties(path)
                generic_chip = convert_legacy_chip(legacy_chip)
            else:
                loader = ChipDefinitionLoader()
                generic_chip = loader.load_from_yaml(path)

            if generic_chip:
                self._generic_chips[generic_chip.name] = generic_chip
                label = f"{generic_chip.name} (loaded)"
                self.chip_combo.addItem(label, generic_chip.name)
                self.chip_combo.setCurrentIndex(self.chip_combo.count() - 1)
        except Exception as e:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.warning(parent_widget, "Load Error", f"Failed to load chip:\n{str(e)}")

    def _on_chip_changed(self):
        """Handle chip selection change"""
        chip_name = self.chip_combo.currentData()
        self.selected_chip = self._generic_chips.get(chip_name) if chip_name else None

        if self.selected_chip:
            info = f"<b>{self.selected_chip.name}</b><br><br>"
            info += f"<b>Family:</b> {self.selected_chip.family}<br>"
            info += f"<b>Package:</b> {self.selected_chip.package}<br><br>"

            info += f"<b>Resources:</b><br>"
            for resource_type, resources in sorted(self.selected_chip.resources.items()):
                info += f"• {resource_type}: {len(resources)} items<br>"

            if self.selected_chip.metadata:
                info += f"<br><b>Metadata:</b><br>"
                for key, value in self.selected_chip.metadata.items():
                    info += f"• {key}: {value}<br>"

            self.chip_info_text.setHtml(info)
            self.chip_selected.emit(self.selected_chip)
        else:
            self.chip_info_text.clear()

        self.completeChanged.emit()

    def get_data(self) -> Dict[str, Any]:
        return {
            "chip": self.selected_chip
        }

    def isComplete(self) -> bool:
        return self.selected_chip is not None


class ModuleSelectionPage(WizardPage):
    """Page 2: Select modules to configure"""

    def __init__(self, rule_loader: MappingRuleLoader):
        self.rule_loader = rule_loader
        self.module_list = QListWidget()
        self.selected_modules: List[str] = []

        super().__init__(
            "Select Modules",
            "Choose which modules to configure for the selected chip"
        )

    def _setup_ui(self):
        self.module_list.setSelectionMode(QListWidget.MultiSelection)
        self.layout.addWidget(self.module_list)

        # Help text
        help_label = QLabel(
            "Select the modules you want to configure. "
            "Modules without matching chip resources are grayed out."
        )
        help_label.setWordWrap(True)
        help_label.setStyleSheet("color: gray; font-style: italic;")
        self.layout.addWidget(help_label)

    def initializePage(self):
        """Populate available modules based on chip resources"""
        wizard = self.wizard()

        self.module_list.clear()
        self.selected_modules = []

        chip = None
        if hasattr(wizard, 'chip_page'):
            data = wizard.chip_page.get_data()
            chip = data.get("chip")

        if not chip:
            return

        # Create mapper to check resource availability
        mapper = GenericResourceMapper(chip=chip, rule_loader=self.rule_loader)
        available_modules = mapper.get_available_modules()

        # Show all modules from rules, but disable those without resources
        all_modules = self.rule_loader.get_all_modules()

        for module in sorted(all_modules):
            rule = self.rule_loader.get_rule(module)
            if not rule:
                continue

            info = mapper.get_module_resource_info(module)
            count = info.get('count', 0)
            resource_type = info.get('resource_type', '')

            item = QListWidgetItem()
            item.setData(Qt.UserRole, module)

            if count > 0:
                item.setText(f"{module} ({count} {resource_type})")
                item.setFlags(item.flags() | Qt.ItemIsEnabled | Qt.ItemIsSelectable)
            else:
                item.setText(f"{module} (no {resource_type} available)")
                item.setFlags(item.flags() & ~Qt.ItemIsEnabled)
                item.setForeground(Qt.gray)

            self.module_list.addItem(item)

            # Select common modules by default
            if module in available_modules and module in ["Can", "Port", "Mcu", "Adc"]:
                item.setSelected(True)

    def get_data(self) -> Dict[str, Any]:
        selected = []
        for item in self.module_list.selectedItems():
            selected.append(item.data(Qt.UserRole))
        return {
            "selected_modules": selected
        }


class ResourceMappingPage(WizardPage):
    """Page 3: Configure resources for each module - Dynamic UI generation"""

    def __init__(self, rule_loader: MappingRuleLoader):
        self.rule_loader = rule_loader
        self.tab_widget = QTabWidget()
        self.module_configs: Dict[str, Dict[str, Any]] = {}
        self._widgets: Dict[str, Dict[str, Any]] = {}  # Store widget references

        super().__init__(
            "Configure Resources",
            "Configure hardware resources for each selected module"
        )

    def _setup_ui(self):
        self.layout.addWidget(self.tab_widget)

    def initializePage(self):
        """Create configuration tabs for each selected module"""
        wizard = self.wizard()

        self.tab_widget.clear()
        self.module_configs.clear()
        self._widgets.clear()

        chip = None
        selected_modules = []

        if hasattr(wizard, 'chip_page'):
            data = wizard.chip_page.get_data()
            chip = data.get("chip")

        if hasattr(wizard, 'module_page'):
            data = wizard.module_page.get_data()
            selected_modules = data.get("selected_modules", [])

        if not chip or not selected_modules:
            return

        # Create mapper for resource info
        mapper = GenericResourceMapper(chip=chip, rule_loader=self.rule_loader)

        # Create tab for each module
        for module in selected_modules:
            rule = self.rule_loader.get_rule(module)
            if not rule:
                continue

            tab = self._create_module_tab(module, chip, mapper, rule)
            self.tab_widget.addTab(tab, module)
            self.module_configs[module] = {}

    def _create_module_tab(self, module: str, chip: GenericChipDefinition,
                           mapper: GenericResourceMapper, rule) -> QWidget:
        """Create configuration tab dynamically based on rule's ui_config"""
        tab = QWidget()
        layout = QVBoxLayout(tab)

        # Get resources for this module
        info = mapper.get_module_resource_info(module)
        resources = info.get('resources', [])

        if not resources:
            layout.addWidget(QLabel(f"No resources available for {module}"))
            layout.addStretch()
            return tab

        ui_config = rule.ui_config
        self._widgets[module] = {'resources': {}}

        if ui_config and ui_config.layout == "table":
            widget = self._create_table_layout(module, resources, ui_config, rule)
            layout.addWidget(widget)
        elif ui_config and ui_config.layout == "list_with_options":
            widget = self._create_list_with_options_layout(module, resources, ui_config, rule)
            layout.addWidget(widget)
        else:
            # Default: simple table layout
            widget = self._create_default_table(module, resources, rule)
            layout.addWidget(widget)

        layout.addStretch()
        return tab

    def _create_table_layout(self, module: str, resources: List[GenericResourceDef],
                             ui_config, rule) -> QWidget:
        """Create table-based configuration UI"""
        group = QGroupBox(ui_config.title if ui_config else module)
        layout = QVBoxLayout()

        table = QTableWidget()
        columns = ui_config.columns if ui_config else []

        # Build column headers
        headers = ["Enable"]
        for col in columns:
            if col.field != "enable":
                headers.append(col.header)
        table.setColumnCount(len(headers))
        table.setHorizontalHeaderLabels(headers)
        table.setRowCount(len(resources))

        for row, resource in enumerate(resources):
            self._widgets[module]['resources'][resource.resource_id] = {}

            # Enable checkbox (always first column)
            enable_check = QCheckBox()
            enable_check.setChecked(True)
            enable_widget = QWidget()
            enable_layout = QHBoxLayout(enable_widget)
            enable_layout.addWidget(enable_check)
            enable_layout.setAlignment(Qt.AlignCenter)
            enable_layout.setContentsMargins(0, 0, 0, 0)
            table.setCellWidget(row, 0, enable_widget)
            self._widgets[module]['resources'][resource.resource_id]['enable'] = enable_check

            # Other columns
            col_idx = 1
            for col in columns:
                if col.field == "enable":
                    continue

                value = self._get_field_value(resource, col.field)
                widget = self._create_cell_widget(resource, col, rule)

                if widget:
                    table.setCellWidget(row, col_idx, widget)
                    self._widgets[module]['resources'][resource.resource_id][col.field] = widget
                else:
                    item = QTableWidgetItem(str(value) if value is not None else "")
                    item.setFlags(item.flags() & ~Qt.ItemIsEditable)
                    table.setItem(row, col_idx, item)

                col_idx += 1

        header = table.horizontalHeader()
        header.setSectionResizeMode(QHeaderView.Stretch)

        layout.addWidget(table)
        group.setLayout(layout)

        self._widgets[module]['table'] = table
        return group

    def _create_list_with_options_layout(self, module: str, resources: List[GenericResourceDef],
                                         ui_config, rule) -> QWidget:
        """Create list with options configuration UI"""
        group = QGroupBox(ui_config.title if ui_config else module)
        layout = QVBoxLayout()

        # Resource selection list
        resource_list = QListWidget()
        resource_list.setSelectionMode(QListWidget.MultiSelection)

        for resource in resources:
            props = resource.properties
            extra_info = ""
            if 'pin_count' in props:
                extra_info = f" ({props['pin_count']} pins)"
            elif 'channel_count' in props:
                extra_info = f" ({props['channel_count']} channels)"

            item = QListWidgetItem(f"{resource.display_name}{extra_info}")
            item.setData(Qt.UserRole, resource.resource_id)
            resource_list.addItem(item)
            item.setSelected(True)

        layout.addWidget(QLabel("Select resources to configure:"))
        layout.addWidget(resource_list)

        self._widgets[module]['resource_list'] = resource_list

        # Additional options from ui_config
        if ui_config and ui_config.options:
            options_group = QGroupBox("Options")
            options_layout = QFormLayout()

            for opt in ui_config.options:
                widget = self._create_option_widget(opt)
                if widget:
                    options_layout.addRow(f"{opt.label}:", widget)
                    self._widgets[module][opt.name] = widget

            options_group.setLayout(options_layout)
            layout.addWidget(options_group)

        group.setLayout(layout)
        return group

    def _create_default_table(self, module: str, resources: List[GenericResourceDef],
                              rule) -> QWidget:
        """Create default table when no ui_config is specified"""
        group = QGroupBox(f"{module} Resources")
        layout = QVBoxLayout()

        table = QTableWidget()
        table.setColumnCount(3)
        table.setHorizontalHeaderLabels(["Enable", "Resource", "Properties"])
        table.setRowCount(len(resources))

        for row, resource in enumerate(resources):
            self._widgets[module]['resources'][resource.resource_id] = {}

            # Enable
            enable_check = QCheckBox()
            enable_check.setChecked(True)
            enable_widget = QWidget()
            enable_layout = QHBoxLayout(enable_widget)
            enable_layout.addWidget(enable_check)
            enable_layout.setAlignment(Qt.AlignCenter)
            enable_layout.setContentsMargins(0, 0, 0, 0)
            table.setCellWidget(row, 0, enable_widget)
            self._widgets[module]['resources'][resource.resource_id]['enable'] = enable_check

            # Resource name
            name_item = QTableWidgetItem(resource.display_name)
            name_item.setFlags(name_item.flags() & ~Qt.ItemIsEditable)
            table.setItem(row, 1, name_item)

            # Properties summary
            props_str = ", ".join(f"{k}={v}" for k, v in list(resource.properties.items())[:3])
            props_item = QTableWidgetItem(props_str)
            props_item.setFlags(props_item.flags() & ~Qt.ItemIsEditable)
            table.setItem(row, 2, props_item)

        header = table.horizontalHeader()
        header.setSectionResizeMode(QHeaderView.Stretch)

        layout.addWidget(table)
        group.setLayout(layout)

        self._widgets[module]['table'] = table
        return group

    def _get_field_value(self, resource: GenericResourceDef, field: str) -> Any:
        """Get field value from resource using dot notation"""
        if field.startswith("resource."):
            path = field[9:]  # Remove "resource." prefix
            if path == "resource_id":
                return resource.resource_id
            elif path == "display_name":
                return resource.display_name
            elif path == "resource_type":
                return resource.resource_type
            elif path.startswith("properties."):
                prop_name = path[11:]
                return resource.properties.get(prop_name)
        return None

    def _create_cell_widget(self, resource: GenericResourceDef, col, rule) -> Optional[QWidget]:
        """Create appropriate widget for a table cell based on field type"""
        field = col.field

        # Check if this field has a parameter mapping in the rule
        for container in rule.containers:
            for param in container.parameters:
                if param.name == field or field.endswith(param.name):
                    return self._create_param_widget(param, resource)

        # For resource fields, return None (use QTableWidgetItem)
        if field.startswith("resource."):
            return None

        return None

    def _create_param_widget(self, param, resource: GenericResourceDef) -> Optional[QWidget]:
        """Create widget based on parameter's ui_type"""
        ui_type = param.ui_type
        ui_options = param.ui_options or {}

        if ui_type == "readonly":
            return None  # Use QTableWidgetItem

        elif ui_type == "checkbox":
            check = QCheckBox()
            default = param.default
            if isinstance(default, bool):
                check.setChecked(default)
            # Check condition for enabling
            if param.condition:
                # Simple condition check
                prop_value = self._eval_simple_condition(param.condition, resource)
                check.setEnabled(bool(prop_value))
            return check

        elif ui_type == "combo":
            combo = QComboBox()
            options = ui_options.get('options', [])
            for opt in options:
                combo.addItem(str(opt))
            if param.default is not None:
                combo.setCurrentText(str(param.default))
            return combo

        elif ui_type == "spinbox":
            spin = QSpinBox()
            spin.setMinimum(ui_options.get('min', 0))
            spin.setMaximum(ui_options.get('max', 999999))
            if param.default is not None:
                spin.setValue(int(param.default))
            return spin

        elif ui_type == "text":
            edit = QLineEdit()
            if param.default is not None:
                edit.setText(str(param.default))
            return edit

        return None

    def _create_option_widget(self, opt) -> Optional[QWidget]:
        """Create widget for ui_config option"""
        if opt.type == "combo":
            combo = QComboBox()
            for o in opt.options:
                combo.addItem(str(o))
            if opt.default:
                combo.setCurrentText(str(opt.default))
            return combo
        elif opt.type == "checkbox":
            check = QCheckBox()
            check.setChecked(bool(opt.default))
            return check
        elif opt.type == "spinbox":
            spin = QSpinBox()
            spin.setMinimum(opt.min_value or 0)
            spin.setMaximum(opt.max_value or 999999)
            if opt.default is not None:
                spin.setValue(int(opt.default))
            return spin
        return None

    def _eval_simple_condition(self, condition: str, resource: GenericResourceDef) -> bool:
        """Evaluate a simple condition expression"""
        try:
            # Handle "resource.properties.xxx == value"
            if "resource.properties." in condition:
                import re
                match = re.match(r'resource\.properties\.(\w+)\s*==\s*(\w+)', condition)
                if match:
                    prop_name = match.group(1)
                    expected = match.group(2)
                    actual = resource.properties.get(prop_name)
                    if expected.lower() == 'true':
                        return actual == True
                    elif expected.lower() == 'false':
                        return actual == False
                    return str(actual) == expected

                # Handle "resource.properties.xxx" (truthy check)
                match = re.match(r'resource\.properties\.(\w+)$', condition)
                if match:
                    prop_name = match.group(1)
                    return bool(resource.properties.get(prop_name))
        except Exception:
            pass
        return True

    def get_data(self) -> Dict[str, Any]:
        """Collect user configuration from all widgets"""
        user_configs = {}

        for module, widgets in self._widgets.items():
            user_configs[module] = {}

            if 'resources' in widgets:
                for resource_id, resource_widgets in widgets['resources'].items():
                    config = {}

                    for field, widget in resource_widgets.items():
                        if isinstance(widget, QCheckBox):
                            config[field] = widget.isChecked()
                        elif isinstance(widget, QComboBox):
                            config[field] = widget.currentText()
                        elif isinstance(widget, QSpinBox):
                            config[field] = widget.value()
                        elif isinstance(widget, QLineEdit):
                            config[field] = widget.text()

                    user_configs[module][resource_id] = config

            # Handle list_with_options layout
            if 'resource_list' in widgets:
                resource_list = widgets['resource_list']
                selected = []
                for i in range(resource_list.count()):
                    item = resource_list.item(i)
                    if item.isSelected():
                        selected.append(item.data(Qt.UserRole))

                # Mark selected resources as enabled
                for res_id in selected:
                    if res_id not in user_configs[module]:
                        user_configs[module][res_id] = {}
                    user_configs[module][res_id]['enable'] = True

                # Additional options
                for key, widget in widgets.items():
                    if key in ('resource_list', 'resources', 'table'):
                        continue
                    if isinstance(widget, QComboBox):
                        user_configs[module][f'_option_{key}'] = widget.currentText()
                    elif isinstance(widget, QCheckBox):
                        user_configs[module][f'_option_{key}'] = widget.isChecked()
                    elif isinstance(widget, QSpinBox):
                        user_configs[module][f'_option_{key}'] = widget.value()

        return {
            "user_configs": user_configs
        }


class HardwareMappingPreviewPage(WizardPage):
    """Page 4: Preview mapping actions"""

    def __init__(self, rule_loader: MappingRuleLoader):
        self.rule_loader = rule_loader
        self.preview_text = QTextEdit()
        self.actions: List[GenericMappingAction] = []

        super().__init__(
            "Preview Configuration",
            "Review the configuration that will be created"
        )

    def _setup_ui(self):
        self.preview_text.setReadOnly(True)
        self.preview_text.setStyleSheet("font-family: monospace;")
        self.layout.addWidget(self.preview_text)

    def initializePage(self):
        """Generate preview of mapping actions using GenericResourceMapper"""
        wizard = self.wizard()

        chip = None
        selected_modules = []
        user_configs = {}

        if hasattr(wizard, 'chip_page'):
            data = wizard.chip_page.get_data()
            chip = data.get("chip")

        if hasattr(wizard, 'module_page'):
            data = wizard.module_page.get_data()
            selected_modules = data.get("selected_modules", [])

        if hasattr(wizard, 'resource_page'):
            data = wizard.resource_page.get_data()
            user_configs = data.get("user_configs", {})

        if not chip:
            self.preview_text.setPlainText("No chip selected")
            return

        # Create generic mapper
        mapper = GenericResourceMapper(chip=chip, rule_loader=self.rule_loader)
        self.actions = []

        preview = "Hardware Mapping Preview\n"
        preview += "=" * 60 + "\n\n"
        preview += f"Chip: {chip.name}\n"
        preview += f"Family: {chip.family}\n"
        preview += f"Modules: {', '.join(selected_modules)}\n\n"
        preview += "-" * 60 + "\n\n"

        for module in selected_modules:
            rule = self.rule_loader.get_rule(module)
            if not rule:
                preview += f"## {module} (no rule found)\n\n"
                continue

            # Get user config for this module
            module_config = user_configs.get(module, {})

            # Convert to mapper's expected format: {resource_id: {param: value}}
            mapper_config = {}
            for key, value in module_config.items():
                if not key.startswith('_option_'):
                    mapper_config[key] = value

            # Generate mapping actions
            actions = mapper.generate_mapping(module, mapper_config)
            self.actions.extend(actions)

            info = mapper.get_module_resource_info(module)
            preview += f"## {module} ({info.get('count', 0)} {info.get('resource_type', '')})\n\n"

            # Group actions by container
            container_actions = {}
            for action in actions:
                path = action.container_path
                if path not in container_actions:
                    container_actions[path] = []
                container_actions[path].append(action)

            # Display actions
            displayed = 0
            for container_path, path_actions in container_actions.items():
                if displayed >= 20:
                    preview += f"  ... and {len(actions) - displayed} more actions\n"
                    break

                for action in path_actions:
                    if action.action_type == GenericMappingActionType.CREATE_CONTAINER:
                        preview += f"  [CREATE] {action.container_path}\n"
                    elif action.action_type == GenericMappingActionType.SET_PARAMETER:
                        preview += f"    [SET] {action.parameter_name} = {action.value}\n"
                    elif action.action_type == GenericMappingActionType.SET_REFERENCE:
                        preview += f"    [REF] {action.parameter_name} -> {action.value}\n"
                    displayed += 1

            preview += f"\n  Subtotal: {len(actions)} actions\n\n"

        preview += "-" * 60 + "\n"
        preview += f"Total actions: {len(self.actions)}\n"

        self.preview_text.setPlainText(preview)

    def get_data(self) -> Dict[str, Any]:
        return {
            "actions": self.actions
        }


class HardwareMappingWizard(ConfigWizard):
    """Wizard for hardware-based configuration using generic mapping rules"""

    def __init__(self, config_manager: Optional[ConfigurationManager] = None,
                 project_path: Optional[Path] = None,
                 undo_stack=None,
                 parent=None):
        self.config_manager = config_manager
        self.project_path = project_path
        self.undo_stack = undo_stack

        # Create chip database (legacy format for backward compatibility)
        self.chip_database = ChipDatabase.create_default_database()

        # Also load from data directory if available
        data_dir = Path(__file__).parent.parent.parent / "data" / "chips"
        if data_dir.exists():
            self.chip_database._load_chips_from_directory(data_dir)

        # Try to extract chip from project
        if project_path:
            self._try_extract_chip_from_project(project_path)

        # Load mapping rules
        self.rule_loader = get_default_rule_loader()

        super().__init__(parent, "Hardware Mapping Wizard")
        self.setMinimumSize(900, 700)

    def _try_extract_chip_from_project(self, project_path: Path):
        """Try to extract chip definition from project"""
        try:
            # First, try to load from properties files
            chip = self.chip_database.detect_and_load_from_project(project_path)
            if chip:
                print(f"Loaded chip from properties: {chip.name}")
                return

            # Fall back to XDM extraction
            from ...core.hardware import extract_chip_from_project, XdmChipExtractor

            extracted = extract_chip_from_project(project_path)
            if extracted:
                self.chip_database.register_chip(extracted)
                return

            # Try eb_test_templates if it exists
            eb_templates = project_path / "eb_test_templates"
            if eb_templates.exists():
                extractor = XdmChipExtractor()
                extracted = extractor.build_chip_from_xdm(
                    eb_templates,
                    chip_name=f"XDM_{project_path.name}"
                )
                if extracted and (extracted.can_resources or extracted.ports):
                    self.chip_database.register_chip(extracted)

        except Exception as e:
            print(f"Warning: Failed to extract chip from project: {e}")

    def _setup_pages(self):
        """Setup wizard pages"""
        # Page 1: Chip selection
        self.chip_page = ChipSelectionPage(self.chip_database, self.project_path)
        self.addPage(self.chip_page)

        # Page 2: Module selection (with rule loader)
        self.module_page = ModuleSelectionPage(self.rule_loader)
        self.addPage(self.module_page)

        # Page 3: Resource configuration (with rule loader)
        self.resource_page = ResourceMappingPage(self.rule_loader)
        self.addPage(self.resource_page)

        # Page 4: Preview (with rule loader)
        self.preview_page = HardwareMappingPreviewPage(self.rule_loader)
        self.addPage(self.preview_page)

    def accept(self):
        """Apply hardware mapping when wizard finishes"""
        try:
            chip_data = self.chip_page.get_data()
            chip = chip_data.get("chip")

            preview_data = self.preview_page.get_data()
            actions = preview_data.get("actions", [])

            if not chip:
                return

            # Apply actions if we have a config manager
            mapping_result = MappingResult()
            if self.config_manager and actions:
                mapper = GenericResourceMapper(chip=chip, rule_loader=self.rule_loader)
                if self.undo_stack is not None:
                    # Route every action through the undo stack so the whole
                    # mapping is a single undoable operation.
                    mapping_result = self._apply_actions_via_undo_stack(mapper, actions)
                else:
                    mapping_result = mapper.apply_actions(actions, self.config_manager)

            # Emit completion signal
            self.wizard_completed.emit({
                "chip": chip.name,
                "actions_count": len(actions),
                "applied_count": mapping_result.applied,
                "skipped_count": mapping_result.skipped,
                "failed_count": mapping_result.failed,
            })

        except Exception as e:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.critical(
                self,
                "Hardware Mapping Error",
                f"Failed to apply hardware mapping:\n{str(e)}"
            )
            return

        super().accept()

    def _apply_actions_via_undo_stack(self, mapper, actions):
        """Apply mapping actions through QUndoCommands inside a single macro.

        Mirrors GenericResourceMapper.apply_actions resolution logic but pushes
        CreateContainerCommand / SetParameterCommand / SetReferenceCommand so the
        whole mapping is undoable via Ctrl+Z. CREATE actions are pushed before the
        SET actions that depend on them, so command redo() runs in the right order.
        """
        from ...core.hardware.generic_mapper import MappingActionType, MappingResult
        from ..commands import (
            CreateContainerCommand, SetParameterCommand, SetReferenceCommand
        )

        result = MappingResult()
        config_manager = self.config_manager

        self.undo_stack.beginMacro("Hardware Mapping")
        try:
            for action in actions:
                try:
                    # Skip actions targeted at a different module
                    if action.module and hasattr(config_manager, 'module_def'):
                        if config_manager.module_def.short_name != action.module:
                            result.skipped += 1
                            continue

                    if action.action_type == MappingActionType.CREATE_CONTAINER:
                        container_def, parent = mapper._resolve_create_target(
                            action.container_path, config_manager)
                        if container_def is None:
                            result.skipped += 1
                            continue
                        instance_name = action.container_path.split('/')[-1]
                        siblings = (parent.sub_containers if parent is not None
                                    else config_manager.configuration.containers)
                        if any(c.short_name == instance_name for c in siblings):
                            result.applied += 1  # idempotent — already there
                            continue
                        self.undo_stack.push(CreateContainerCommand(
                            config_manager, container_def, parent, instance_name))
                        result.applied += 1

                    elif action.action_type == MappingActionType.SET_PARAMETER:
                        container = mapper._find_container_instance(
                            action.container_path, config_manager)
                        if container is None:
                            result.skipped += 1
                            continue
                        self.undo_stack.push(SetParameterCommand(
                            config_manager, container,
                            action.parameter_name, action.value))
                        result.applied += 1

                    elif action.action_type == MappingActionType.SET_REFERENCE:
                        container = mapper._find_container_instance(
                            action.container_path, config_manager)
                        if container is None:
                            result.skipped += 1
                            continue
                        self.undo_stack.push(SetReferenceCommand(
                            config_manager, container,
                            action.parameter_name, action.value))
                        result.applied += 1

                except Exception as e:
                    print(f"Warning: Failed to apply action {action}: {e}")
                    result.failed += 1
        finally:
            self.undo_stack.endMacro()

        return result
