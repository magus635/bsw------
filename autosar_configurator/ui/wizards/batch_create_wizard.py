"""
Batch Create Wizard
Create multiple container instances with automatic ID/naming increments
"""
from enum import Enum
from dataclasses import dataclass, field
from typing import Dict, Any, Optional, List

from PySide6.QtWidgets import (
    QVBoxLayout, QHBoxLayout, QLabel, QComboBox, QLineEdit,
    QFormLayout, QSpinBox, QDoubleSpinBox, QCheckBox, QTextEdit, QTableWidget,
    QTableWidgetItem, QHeaderView, QGroupBox, QRadioButton,
    QButtonGroup, QWidget
)
from PySide6.QtCore import Qt

from .wizard_base import ConfigWizard, WizardPage
from ...core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterType
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager


class ParameterRule(Enum):
    """Rule for parameter value generation"""
    FIXED = "Fixed Value"
    INCREMENT = "Auto Increment"
    SKIP = "Skip (Use Default)"


@dataclass
class ParameterRuleConfig:
    """Configuration for a parameter rule"""
    param_name: str
    rule_type: ParameterRule = ParameterRule.SKIP
    base_value: Any = None
    step: Any = 1


@dataclass
class BatchConfig:
    """Configuration for batch creation"""
    container_def: Optional[EcucContainerDef] = None
    count: int = 1
    naming_template: str = "{name}_{i}"
    start_index: int = 0
    parameter_rules: Dict[str, ParameterRuleConfig] = field(default_factory=dict)


class ContainerTypePage(WizardPage):
    """Page 1: Select container type to create"""

    def __init__(self, module_def: EcucModuleDef, config_manager: ConfigurationManager,
                 parent_instance: Optional[EcucContainerValue] = None):
        self.module_def = module_def
        self.config_manager = config_manager
        self.parent_instance = parent_instance
        self.container_combo = QComboBox()

        super().__init__(
            "Select Container Type",
            "Choose the type of container to create in batch"
        )

    def _setup_ui(self):
        form = QFormLayout()

        # Determine which definitions to show
        if self.parent_instance:
            container_def_obj = self.config_manager.get_container_def(self.parent_instance.definition_ref)
            defs = container_def_obj.sub_containers.values() if container_def_obj else []
        else:
            defs = self.module_def.containers.values()

        # Filter to only show containers that allow multiple instances
        for container_def in defs:
            if container_def.upper_multiplicity == -1 or container_def.upper_multiplicity > 1:
                label = f"{container_def.short_name} ({container_def.multiplicity_str})"
                self.container_combo.addItem(label, container_def)

        if self.container_combo.count() == 0:
            self.container_combo.addItem("No multi-instance containers available", None)
            self.container_combo.setEnabled(False)

        form.addRow("Container Type:", self.container_combo)

        # Info label
        info_label = QLabel(
            "Only containers that allow multiple instances (0..*, 1..*, etc.) are shown."
        )
        info_label.setWordWrap(True)
        info_label.setStyleSheet("color: gray; font-style: italic;")

        self.layout.addLayout(form)
        self.layout.addWidget(info_label)
        self.layout.addStretch()

    def get_data(self) -> Dict[str, Any]:
        return {
            "container_def": self.container_combo.currentData()
        }

    def validatePage(self) -> bool:
        return self.container_combo.currentData() is not None


class BatchSettingsPage(WizardPage):
    """Page 2: Configure batch settings (count, naming)"""

    def __init__(self):
        self.count_spin = QSpinBox()
        self.template_edit = QLineEdit()
        self.start_index_spin = QSpinBox()

        super().__init__(
            "Batch Settings",
            "Configure the number of instances and naming pattern"
        )

    def _setup_ui(self):
        form = QFormLayout()

        # Instance count
        self.count_spin.setMinimum(1)
        self.count_spin.setMaximum(100)
        self.count_spin.setValue(5)
        form.addRow("Number of Instances:", self.count_spin)

        # Naming template
        self.template_edit.setText("{name}_{i}")
        self.template_edit.setPlaceholderText("e.g., CanController_{i}")
        form.addRow("Naming Template:", self.template_edit)

        # Start index
        self.start_index_spin.setMinimum(0)
        self.start_index_spin.setMaximum(999)
        self.start_index_spin.setValue(0)
        form.addRow("Starting Index:", self.start_index_spin)

        self.layout.addLayout(form)

        # Template help
        help_group = QGroupBox("Naming Template Variables")
        help_layout = QVBoxLayout()
        help_text = QLabel(
            "<b>{name}</b> - Container type name (e.g., CanController)<br>"
            "<b>{i}</b> - Instance index (starts from Starting Index)<br>"
            "<b>{I}</b> - Zero-padded index (e.g., 00, 01, 02)<br>"
            "<br>"
            "Examples:<br>"
            "• {name}_{i} → CanController_0, CanController_1, ...<br>"
            "• Channel_{I} → Channel_00, Channel_01, ...<br>"
            "• HwUnit{i} → HwUnit0, HwUnit1, ..."
        )
        help_text.setWordWrap(True)
        help_layout.addWidget(help_text)
        help_group.setLayout(help_layout)

        self.layout.addWidget(help_group)
        self.layout.addStretch()

        # Connect for preview updates
        self.count_spin.valueChanged.connect(self._update_preview)
        self.template_edit.textChanged.connect(self._update_preview)
        self.start_index_spin.valueChanged.connect(self._update_preview)

    def _update_preview(self):
        """Update preview of generated names"""
        # Preview will be shown on the preview page
        pass

    def initializePage(self):
        """Initialize page with container name"""
        wizard = self.wizard()
        if hasattr(wizard, 'container_type_page'):
            data = wizard.container_type_page.get_data()
            container_def = data.get("container_def")
            if container_def:
                self.template_edit.setText(f"{container_def.short_name}_{{i}}")

    def get_data(self) -> Dict[str, Any]:
        return {
            "count": self.count_spin.value(),
            "naming_template": self.template_edit.text(),
            "start_index": self.start_index_spin.value()
        }

    def validatePage(self) -> bool:
        template = self.template_edit.text().strip()
        if not template:
            return False
        if "{i}" not in template and "{I}" not in template:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.warning(
                self,
                "Invalid Template",
                "Naming template must contain {i} or {I} for unique instance names."
            )
            return False
        return True


class ParameterRulesPage(WizardPage):
    """Page 3: Configure parameter rules"""

    def __init__(self):
        self.rules_table = QTableWidget()
        self.param_rules: Dict[str, ParameterRuleConfig] = {}

        super().__init__(
            "Parameter Rules",
            "Configure how parameter values should be generated"
        )

    def _setup_ui(self):
        # Setup table
        self.rules_table.setColumnCount(4)
        self.rules_table.setHorizontalHeaderLabels([
            "Parameter", "Rule", "Base Value", "Step"
        ])

        header = self.rules_table.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(3, QHeaderView.ResizeToContents)

        self.layout.addWidget(self.rules_table)

        # Legend
        legend = QLabel(
            "<b>Rules:</b><br>"
            "• <b>Skip</b> - Use default value from definition<br>"
            "• <b>Fixed</b> - Use the same value for all instances<br>"
            "• <b>Increment</b> - Increment value by Step for each instance"
        )
        legend.setWordWrap(True)
        self.layout.addWidget(legend)

    def initializePage(self):
        """Populate table with parameters from selected container"""
        wizard = self.wizard()

        # Get container definition
        container_def = None
        if hasattr(wizard, 'container_type_page'):
            data = wizard.container_type_page.get_data()
            container_def = data.get("container_def")

        if not container_def:
            return

        self.rules_table.setRowCount(0)
        self.param_rules.clear()

        for param_name, param_def in container_def.parameters.items():
            row = self.rules_table.rowCount()
            self.rules_table.insertRow(row)

            # Parameter name
            name_item = QTableWidgetItem(param_name)
            name_item.setFlags(name_item.flags() & ~Qt.ItemIsEditable)
            self.rules_table.setItem(row, 0, name_item)

            # Rule type combo
            rule_combo = QComboBox()
            rule_combo.addItem(ParameterRule.SKIP.value, ParameterRule.SKIP)
            rule_combo.addItem(ParameterRule.FIXED.value, ParameterRule.FIXED)

            # Only allow increment for numeric types
            if param_def.param_type in [EcucParameterType.INTEGER, EcucParameterType.FLOAT]:
                rule_combo.addItem(ParameterRule.INCREMENT.value, ParameterRule.INCREMENT)

            self.rules_table.setCellWidget(row, 1, rule_combo)

            # Base value
            base_edit = self._create_value_widget(param_def)
            self.rules_table.setCellWidget(row, 2, base_edit)

            # Step (for increment)
            step_spin = QSpinBox()
            step_spin.setMinimum(1)
            step_spin.setMaximum(1000)
            step_spin.setValue(1)
            step_spin.setEnabled(False)
            self.rules_table.setCellWidget(row, 3, step_spin)

            # Connect rule change to enable/disable fields
            rule_combo.currentIndexChanged.connect(
                lambda idx, be=base_edit, ss=step_spin, rc=rule_combo: self._on_rule_changed(rc, be, ss)
            )

            # Store rule config
            self.param_rules[param_name] = ParameterRuleConfig(
                param_name=param_name,
                rule_type=ParameterRule.SKIP,
                base_value=param_def.default_value
            )

    def _create_value_widget(self, param_def) -> QWidget:
        """Create appropriate widget for parameter type"""
        if param_def.param_type == EcucParameterType.INTEGER:
            widget = QDoubleSpinBox()
            widget.setDecimals(0)
            widget.setMinimum(float(param_def.min_value or 0))
            widget.setMaximum(float(param_def.max_value or 1e15))  # Use large value instead of 999999
            if param_def.default_value is not None:
                widget.setValue(float(param_def.default_value))
            return widget

        elif param_def.param_type == EcucParameterType.BOOLEAN:
            widget = QCheckBox()
            if param_def.default_value:
                widget.setChecked(bool(param_def.default_value))
            return widget

        elif param_def.param_type == EcucParameterType.ENUMERATION:
            widget = QComboBox()
            if param_def.literals:
                widget.addItems(param_def.literals)
            if param_def.default_value:
                idx = widget.findText(str(param_def.default_value))
                if idx >= 0:
                    widget.setCurrentIndex(idx)
            return widget

        else:
            widget = QLineEdit()
            if param_def.default_value is not None:
                widget.setText(str(param_def.default_value))
            return widget

    def _on_rule_changed(self, rule_combo: QComboBox, base_widget: QWidget, step_widget: QSpinBox):
        """Handle rule type change"""
        rule = rule_combo.currentData()

        # Enable/disable based on rule
        base_widget.setEnabled(rule != ParameterRule.SKIP)
        step_widget.setEnabled(rule == ParameterRule.INCREMENT)

    def get_data(self) -> Dict[str, Any]:
        """Collect parameter rules"""
        rules = {}

        for row in range(self.rules_table.rowCount()):
            param_name = self.rules_table.item(row, 0).text()

            rule_combo = self.rules_table.cellWidget(row, 1)
            rule_type = rule_combo.currentData()

            base_widget = self.rules_table.cellWidget(row, 2)
            if isinstance(base_widget, (QSpinBox, QDoubleSpinBox)):
                base_value = int(base_widget.value())
            elif isinstance(base_widget, QCheckBox):
                base_value = base_widget.isChecked()
            elif isinstance(base_widget, QComboBox):
                base_value = base_widget.currentText()
            elif isinstance(base_widget, QLineEdit):
                base_value = base_widget.text()
            else:
                base_value = None

            step_widget = self.rules_table.cellWidget(row, 3)
            step = step_widget.value() if step_widget else 1

            rules[param_name] = ParameterRuleConfig(
                param_name=param_name,
                rule_type=rule_type,
                base_value=base_value,
                step=step
            )

        return {"parameter_rules": rules}


class BatchPreviewPage(WizardPage):
    """Page 4: Preview the instances to be created"""

    def __init__(self):
        self.preview_text = QTextEdit()
        self.preview_data: List[Dict[str, Any]] = []

        super().__init__(
            "Preview",
            "Review the instances that will be created"
        )

    def _setup_ui(self):
        self.preview_text.setReadOnly(True)
        self.layout.addWidget(self.preview_text)

    def initializePage(self):
        """Generate and display preview"""
        wizard = self.wizard()

        # Collect all data
        container_def = None
        count = 5
        template = "{name}_{i}"
        start_index = 0
        param_rules = {}

        if hasattr(wizard, 'container_type_page'):
            data = wizard.container_type_page.get_data()
            container_def = data.get("container_def")

        if hasattr(wizard, 'batch_settings_page'):
            data = wizard.batch_settings_page.get_data()
            count = data.get("count", 5)
            template = data.get("naming_template", "{name}_{i}")
            start_index = data.get("start_index", 0)

        if hasattr(wizard, 'param_rules_page'):
            data = wizard.param_rules_page.get_data()
            param_rules = data.get("parameter_rules", {})

        # Generate preview
        self.preview_data = []
        preview_text = f"Batch Creation Preview\n"
        preview_text += "=" * 60 + "\n\n"
        preview_text += f"Container Type: {container_def.short_name if container_def else 'Unknown'}\n"
        preview_text += f"Count: {count} instances\n"
        preview_text += f"Naming: {template}\n\n"
        preview_text += "-" * 60 + "\n\n"

        if container_def:
            name = container_def.short_name
            for i in range(count):
                idx = start_index + i

                # Generate instance name
                instance_name = template.replace("{name}", name)
                instance_name = instance_name.replace("{i}", str(idx))
                instance_name = instance_name.replace("{I}", f"{idx:02d}")

                instance_data = {
                    "name": instance_name,
                    "index": idx,
                    "parameters": {}
                }

                preview_text += f"Instance {i+1}: {instance_name}\n"

                # Generate parameter values
                for param_name, rule_config in param_rules.items():
                    if rule_config.rule_type == ParameterRule.SKIP:
                        continue

                    value = rule_config.base_value
                    if rule_config.rule_type == ParameterRule.INCREMENT:
                        if isinstance(value, (int, float)):
                            value = value + (i * rule_config.step)

                    instance_data["parameters"][param_name] = value
                    preview_text += f"  • {param_name}: {value}\n"

                self.preview_data.append(instance_data)
                preview_text += "\n"

        self.preview_text.setPlainText(preview_text)

    def get_data(self) -> Dict[str, Any]:
        return {"preview_data": self.preview_data}


class BatchCreateWizard(ConfigWizard):
    """Wizard for batch creating container instances"""

    def __init__(self, module_def: EcucModuleDef, config_manager: ConfigurationManager,
                 parent_instance: Optional[EcucContainerValue] = None, parent=None):
        self.module_def = module_def
        self.config_manager = config_manager
        self.parent_instance = parent_instance
        self.created_instances: List[EcucContainerValue] = []

        super().__init__(parent, "Batch Create Wizard")
        self.setMinimumSize(700, 500)

    def _setup_pages(self):
        """Setup wizard pages"""
        # Page 1: Container type selection
        self.container_type_page = ContainerTypePage(
            self.module_def, self.config_manager, self.parent_instance
        )
        self.addPage(self.container_type_page)

        # Page 2: Batch settings
        self.batch_settings_page = BatchSettingsPage()
        self.addPage(self.batch_settings_page)

        # Page 3: Parameter rules
        self.param_rules_page = ParameterRulesPage()
        self.addPage(self.param_rules_page)

        # Page 4: Preview
        self.preview_page = BatchPreviewPage()
        self.addPage(self.preview_page)

    def accept(self):
        """Create all instances when wizard finishes"""
        try:
            # Get configuration
            container_def = self.container_type_page.get_data().get("container_def")
            batch_data = self.batch_settings_page.get_data()
            param_rules = self.param_rules_page.get_data().get("parameter_rules", {})
            preview_data = self.preview_page.get_data().get("preview_data", [])

            if not container_def or not preview_data:
                return

            self.created_instances = []

            for instance_info in preview_data:
                # Create instance
                instance = self.config_manager.create_container_instance(
                    container_def,
                    parent=self.parent_instance,
                    instance_name=instance_info["name"]
                )

                # Set parameter values
                for param_name, value in instance_info.get("parameters", {}).items():
                    try:
                        self.config_manager.set_parameter_value(instance, param_name, value)
                    except Exception as e:
                        print(f"Warning: Failed to set {param_name}: {e}")

                self.created_instances.append(instance)

            # Emit completion signal
            self.wizard_completed.emit({
                "instances": self.created_instances,
                "container_def": container_def,
                "count": len(self.created_instances)
            })

        except Exception as e:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.critical(
                self,
                "Batch Create Error",
                f"Failed to create instances:\n{str(e)}"
            )
            return

        super().accept()
