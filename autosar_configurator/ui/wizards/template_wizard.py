"""
Template Wizard
Apply predefined configuration templates
"""
from typing import Dict, Any, Optional, List
from pathlib import Path

from PySide6.QtWidgets import (
    QVBoxLayout, QHBoxLayout, QLabel, QComboBox, QLineEdit,
    QFormLayout, QSpinBox, QCheckBox, QTextEdit, QTreeWidget,
    QTreeWidgetItem, QListWidget, QListWidgetItem, QGroupBox,
    QSplitter, QWidget, QRadioButton, QButtonGroup
)
from PySide6.QtCore import Qt, Signal

from .wizard_base import ConfigWizard, WizardPage
from ...core.model.definition_model import EcucModuleDef, EcucContainerDef
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager
from ...core.template_manager import TemplateManager, ConfigTemplate, TemplateParameter


class TemplateCategoryPage(WizardPage):
    """Page 1: Browse and select a template"""

    template_selected = Signal(object)  # ConfigTemplate

    def __init__(self, template_manager: TemplateManager, module_filter: str = None):
        self.template_manager = template_manager
        self.module_filter = module_filter
        self.category_tree = QTreeWidget()
        self.template_list = QListWidget()
        self.description_text = QTextEdit()
        self.selected_template: Optional[ConfigTemplate] = None

        super().__init__(
            "Select Template",
            "Browse and select a configuration template"
        )

    def _setup_ui(self):
        # Main splitter
        splitter = QSplitter(Qt.Horizontal)

        # Left: Category tree
        left_widget = QWidget()
        left_layout = QVBoxLayout(left_widget)
        left_layout.setContentsMargins(0, 0, 0, 0)

        left_layout.addWidget(QLabel("Categories:"))
        self.category_tree.setHeaderHidden(True)
        self.category_tree.itemClicked.connect(self._on_category_selected)
        left_layout.addWidget(self.category_tree)

        # Middle: Template list
        middle_widget = QWidget()
        middle_layout = QVBoxLayout(middle_widget)
        middle_layout.setContentsMargins(0, 0, 0, 0)

        middle_layout.addWidget(QLabel("Templates:"))
        self.template_list.itemClicked.connect(self._on_template_selected)
        middle_layout.addWidget(self.template_list)

        # Right: Description
        right_widget = QWidget()
        right_layout = QVBoxLayout(right_widget)
        right_layout.setContentsMargins(0, 0, 0, 0)

        right_layout.addWidget(QLabel("Description:"))
        self.description_text.setReadOnly(True)
        right_layout.addWidget(self.description_text)

        splitter.addWidget(left_widget)
        splitter.addWidget(middle_widget)
        splitter.addWidget(right_widget)
        splitter.setSizes([150, 200, 250])

        self.layout.addWidget(splitter)

        # Populate categories
        self._populate_categories()

    def _populate_categories(self):
        """Populate category tree"""
        self.category_tree.clear()

        # Add "All" category
        all_item = QTreeWidgetItem(["All Templates"])
        all_item.setData(0, Qt.UserRole, None)
        self.category_tree.addTopLevelItem(all_item)

        # Group by module first
        modules_item = QTreeWidgetItem(["By Module"])
        self.category_tree.addTopLevelItem(modules_item)

        for module in self.template_manager.list_modules():
            if self.module_filter and module != self.module_filter:
                continue
            module_item = QTreeWidgetItem([module])
            module_item.setData(0, Qt.UserRole, ("module", module))
            modules_item.addChild(module_item)

        # Group by category
        categories_item = QTreeWidgetItem(["By Category"])
        self.category_tree.addTopLevelItem(categories_item)

        for category in self.template_manager.list_categories():
            cat_item = QTreeWidgetItem([category])
            cat_item.setData(0, Qt.UserRole, ("category", category))
            categories_item.addChild(cat_item)

        self.category_tree.expandAll()

        # Select "All" by default
        all_item.setSelected(True)
        self._on_category_selected(all_item, 0)

    def _on_category_selected(self, item: QTreeWidgetItem, column: int):
        """Handle category selection"""
        self.template_list.clear()

        data = item.data(0, Qt.UserRole)

        if data is None:
            # All templates
            templates = self.template_manager.list_templates(module=self.module_filter)
        elif isinstance(data, tuple):
            filter_type, filter_value = data
            if filter_type == "module":
                templates = self.template_manager.list_templates(module=filter_value)
            else:
                templates = self.template_manager.list_templates(category=filter_value)
        else:
            templates = []

        for template in templates:
            item = QListWidgetItem(template.name)
            item.setData(Qt.UserRole, template)
            self.template_list.addItem(item)

    def _on_template_selected(self, item: QListWidgetItem):
        """Handle template selection"""
        self.selected_template = item.data(Qt.UserRole)

        if self.selected_template:
            desc = f"<b>{self.selected_template.name}</b><br><br>"
            desc += f"<b>Module:</b> {self.selected_template.module}<br>"
            desc += f"<b>Category:</b> {self.selected_template.category}<br><br>"
            desc += f"{self.selected_template.description}<br><br>"

            if self.selected_template.tags:
                desc += f"<b>Tags:</b> {', '.join(self.selected_template.tags)}<br>"

            desc += f"<br><b>Adjustable Parameters:</b> {len(self.selected_template.adjustable_params)}<br>"
            desc += f"<b>Fixed Parameters:</b> {len(self.selected_template.fixed_params)}"

            self.description_text.setHtml(desc)
            self.template_selected.emit(self.selected_template)
        else:
            self.description_text.clear()

        self.completeChanged.emit()

    def get_data(self) -> Dict[str, Any]:
        return {
            "template": self.selected_template
        }

    def isComplete(self) -> bool:
        return self.selected_template is not None


class TemplateParameterPage(WizardPage):
    """Page 2: Adjust template parameters"""

    def __init__(self):
        self.param_widgets: Dict[str, QWidget] = {}

        super().__init__(
            "Configure Parameters",
            "Adjust the template parameters to your needs"
        )

    def _setup_ui(self):
        self.form = QFormLayout()
        self.layout.addLayout(self.form)

        self.info_label = QLabel("Select a template first")
        self.layout.addWidget(self.info_label)
        self.layout.addStretch()

    def initializePage(self):
        """Populate parameters from selected template"""
        wizard = self.wizard()

        # Clear existing widgets
        while self.form.count():
            self.form.removeRow(0)
        self.param_widgets.clear()

        template = None
        if hasattr(wizard, 'category_page'):
            data = wizard.category_page.get_data()
            template = data.get("template")

        if not template:
            self.info_label.setVisible(True)
            self.info_label.setText("No template selected")
            return

        self.info_label.setVisible(False)

        # Create widgets for adjustable parameters
        for param in template.adjustable_params:
            widget = self._create_param_widget(param)
            if widget:
                self.param_widgets[param.name] = widget

                label = param.display_name or param.name
                if param.description:
                    label += f" <small style='color: gray;'>({param.description})</small>"

                label_widget = QLabel(label)
                label_widget.setTextFormat(Qt.RichText)
                self.form.addRow(label_widget, widget)

        if not template.adjustable_params:
            self.info_label.setVisible(True)
            self.info_label.setText("This template has no adjustable parameters")

    def _create_param_widget(self, param: TemplateParameter) -> QWidget:
        """Create appropriate widget for parameter type"""
        if param.param_type == "integer":
            widget = QSpinBox()
            if param.min_value is not None:
                widget.setMinimum(int(param.min_value))
            else:
                widget.setMinimum(-999999)
            if param.max_value is not None:
                widget.setMaximum(int(param.max_value))
            else:
                widget.setMaximum(999999)
            if param.default_value is not None:
                widget.setValue(int(param.default_value))
            return widget

        elif param.param_type == "boolean":
            widget = QCheckBox()
            if param.default_value:
                widget.setChecked(bool(param.default_value))
            return widget

        elif param.param_type == "enumeration":
            widget = QComboBox()
            if param.options:
                widget.addItems(param.options)
            if param.default_value:
                idx = widget.findText(str(param.default_value))
                if idx >= 0:
                    widget.setCurrentIndex(idx)
            return widget

        elif param.param_type == "float":
            widget = QLineEdit()
            if param.default_value is not None:
                widget.setText(str(param.default_value))
            widget.setPlaceholderText("Enter decimal number")
            return widget

        else:  # string
            widget = QLineEdit()
            if param.default_value is not None:
                widget.setText(str(param.default_value))
            return widget

    def get_data(self) -> Dict[str, Any]:
        """Get adjusted parameter values"""
        values = {}

        for param_name, widget in self.param_widgets.items():
            if isinstance(widget, QSpinBox):
                values[param_name] = widget.value()
            elif isinstance(widget, QCheckBox):
                values[param_name] = widget.isChecked()
            elif isinstance(widget, QComboBox):
                values[param_name] = widget.currentText()
            elif isinstance(widget, QLineEdit):
                text = widget.text()
                # Try to convert to float if applicable
                try:
                    values[param_name] = float(text)
                except ValueError:
                    values[param_name] = text

        return {"parameter_values": values}


class TemplateTargetPage(WizardPage):
    """Page 3: Select application target"""

    def __init__(self, config_manager: ConfigurationManager,
                 parent_instance: Optional[EcucContainerValue] = None):
        self.config_manager = config_manager
        self.parent_instance = parent_instance

        self.create_new_radio = QRadioButton()
        self.update_existing_radio = QRadioButton()
        self.instance_name_edit = QLineEdit()
        self.existing_combo = QComboBox()

        super().__init__(
            "Select Target",
            "Choose where to apply the template"
        )

    def _setup_ui(self):
        # Target type selection
        target_group = QGroupBox("Application Target")
        target_layout = QVBoxLayout()

        button_group = QButtonGroup(self)

        self.create_new_radio = QRadioButton("Create new instance")
        self.create_new_radio.setChecked(True)
        button_group.addButton(self.create_new_radio)
        target_layout.addWidget(self.create_new_radio)

        # New instance name
        new_layout = QHBoxLayout()
        new_layout.addSpacing(20)
        new_layout.addWidget(QLabel("Instance Name:"))
        self.instance_name_edit.setPlaceholderText("Auto-generated if empty")
        new_layout.addWidget(self.instance_name_edit)
        target_layout.addLayout(new_layout)

        target_layout.addSpacing(10)

        self.update_existing_radio = QRadioButton("Update existing instance")
        button_group.addButton(self.update_existing_radio)
        target_layout.addWidget(self.update_existing_radio)

        # Existing instance selection
        existing_layout = QHBoxLayout()
        existing_layout.addSpacing(20)
        existing_layout.addWidget(QLabel("Select Instance:"))
        existing_layout.addWidget(self.existing_combo)
        target_layout.addLayout(existing_layout)

        target_group.setLayout(target_layout)
        self.layout.addWidget(target_group)

        self.layout.addStretch()

        # Connect signals
        self.create_new_radio.toggled.connect(self._on_target_changed)
        self.update_existing_radio.toggled.connect(self._on_target_changed)

        self._on_target_changed()

    def _on_target_changed(self):
        """Handle target type change"""
        is_new = self.create_new_radio.isChecked()
        self.instance_name_edit.setEnabled(is_new)
        self.existing_combo.setEnabled(not is_new)

    def initializePage(self):
        """Populate existing instances"""
        wizard = self.wizard()

        template = None
        if hasattr(wizard, 'category_page'):
            data = wizard.category_page.get_data()
            template = data.get("template")

        self.existing_combo.clear()

        if template and self.config_manager:
            # Find existing instances that match the template's container type
            # This is a simplified implementation
            containers = []
            if self.parent_instance:
                containers = self.parent_instance.sub_containers
            else:
                containers = self.config_manager.configuration.containers

            for container in containers:
                self.existing_combo.addItem(container.short_name, container)

            if self.existing_combo.count() == 0:
                self.update_existing_radio.setEnabled(False)
                self.create_new_radio.setChecked(True)
            else:
                self.update_existing_radio.setEnabled(True)

    def get_data(self) -> Dict[str, Any]:
        return {
            "create_new": self.create_new_radio.isChecked(),
            "instance_name": self.instance_name_edit.text() or None,
            "existing_instance": self.existing_combo.currentData() if not self.create_new_radio.isChecked() else None
        }


class TemplatePreviewPage(WizardPage):
    """Page 4: Preview template application"""

    def __init__(self):
        self.preview_text = QTextEdit()

        super().__init__(
            "Preview",
            "Review the configuration that will be created"
        )

    def _setup_ui(self):
        self.preview_text.setReadOnly(True)
        self.layout.addWidget(self.preview_text)

    def initializePage(self):
        """Generate preview"""
        wizard = self.wizard()

        template = None
        param_values = {}
        target_data = {}

        if hasattr(wizard, 'category_page'):
            data = wizard.category_page.get_data()
            template = data.get("template")

        if hasattr(wizard, 'param_page'):
            data = wizard.param_page.get_data()
            param_values = data.get("parameter_values", {})

        if hasattr(wizard, 'target_page'):
            target_data = wizard.target_page.get_data()

        if not template:
            self.preview_text.setPlainText("No template selected")
            return

        preview = f"Template Application Preview\n"
        preview += "=" * 60 + "\n\n"
        preview += f"Template: {template.name}\n"
        preview += f"Module: {template.module}\n"
        preview += f"Target Container: {template.container_def}\n\n"

        if target_data.get("create_new"):
            name = target_data.get("instance_name") or "(auto-generated)"
            preview += f"Action: Create new instance '{name}'\n\n"
        else:
            existing = target_data.get("existing_instance")
            if existing:
                preview += f"Action: Update existing instance '{existing.short_name}'\n\n"

        preview += "-" * 60 + "\n"
        preview += "Parameters to be set:\n\n"

        # Get merged parameters
        all_params = template.get_all_params(param_values)

        for name, value in sorted(all_params.items()):
            is_adjustable = any(p.name == name for p in template.adjustable_params)
            marker = " (adjustable)" if is_adjustable else " (fixed)"
            preview += f"  {name}: {value}{marker}\n"

        self.preview_text.setPlainText(preview)

    def get_data(self) -> Dict[str, Any]:
        return {}


class TemplateWizard(ConfigWizard):
    """Wizard for applying configuration templates"""

    def __init__(self, config_manager: ConfigurationManager,
                 template_manager: Optional[TemplateManager] = None,
                 module_filter: str = None,
                 parent_instance: Optional[EcucContainerValue] = None,
                 parent=None):
        self.config_manager = config_manager
        self.template_manager = template_manager or TemplateManager()
        self.module_filter = module_filter
        self.parent_instance = parent_instance
        self.created_instance = None

        super().__init__(parent, "Template Wizard")
        self.setMinimumSize(800, 500)

    def _setup_pages(self):
        """Setup wizard pages"""
        # Page 1: Template selection
        self.category_page = TemplateCategoryPage(
            self.template_manager, self.module_filter
        )
        self.addPage(self.category_page)

        # Page 2: Parameter configuration
        self.param_page = TemplateParameterPage()
        self.addPage(self.param_page)

        # Page 3: Target selection
        self.target_page = TemplateTargetPage(
            self.config_manager, self.parent_instance
        )
        self.addPage(self.target_page)

        # Page 4: Preview
        self.preview_page = TemplatePreviewPage()
        self.addPage(self.preview_page)

    def accept(self):
        """Apply template when wizard finishes"""
        try:
            template_data = self.category_page.get_data()
            template = template_data.get("template")

            param_data = self.param_page.get_data()
            param_values = param_data.get("parameter_values", {})

            target_data = self.target_page.get_data()

            if not template:
                return

            # Get all parameters
            all_params = template.get_all_params(param_values)

            if target_data.get("create_new"):
                # Create new instance
                # For now, we'll use a simplified approach - find the container def
                # In a full implementation, this would use the template.container_def path

                # Try to find matching container def in module
                container_def = None
                if hasattr(self.config_manager, 'module_def') and self.config_manager.module_def:
                    # Search for container matching the template's target
                    for cdef in self.config_manager.module_def.containers.values():
                        if template.container_def and cdef.short_name in template.container_def:
                            container_def = cdef
                            break

                if container_def:
                    instance_name = target_data.get("instance_name")
                    instance = self.config_manager.create_container_instance(
                        container_def,
                        parent=self.parent_instance,
                        instance_name=instance_name
                    )

                    # Set parameters
                    for param_name, value in all_params.items():
                        try:
                            self.config_manager.set_parameter_value(instance, param_name, value)
                        except Exception as e:
                            print(f"Warning: Failed to set {param_name}: {e}")

                    self.created_instance = instance
                else:
                    # Fallback: just emit the data
                    self.created_instance = None

            else:
                # Update existing instance
                existing = target_data.get("existing_instance")
                if existing:
                    for param_name, value in all_params.items():
                        try:
                            self.config_manager.set_parameter_value(existing, param_name, value)
                        except Exception as e:
                            print(f"Warning: Failed to set {param_name}: {e}")

                    self.created_instance = existing

            # Emit completion signal
            self.wizard_completed.emit({
                "template": template,
                "instance": self.created_instance,
                "parameters": all_params
            })

        except Exception as e:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.critical(
                self,
                "Template Error",
                f"Failed to apply template:\n{str(e)}"
            )
            return

        super().accept()
