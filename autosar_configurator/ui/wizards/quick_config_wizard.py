"""
Quick Configuration Wizard
Helps users quickly configure common container instances
"""
from PySide6.QtWidgets import (
    QVBoxLayout, QLabel, QComboBox, QLineEdit,
    QFormLayout, QSpinBox, QDoubleSpinBox, QCheckBox, QTextEdit
)
from typing import Dict, Any, Optional

from .wizard_base import ConfigWizard, WizardPage
from ...core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterType
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager


class ContainerSelectionPage(WizardPage):
    """Page 1: Select container type to configure"""
    
    def __init__(self, module_def: EcucModuleDef, config_manager: ConfigurationManager, parent_instance: Optional[EcucContainerValue] = None):
        self.module_def = module_def
        self.config_manager = config_manager
        self.parent_instance = parent_instance
        self.container_combo = QComboBox()
        self.name_edit = QLineEdit()
        
        title = "Select Container Type"
        if parent_instance:
            title += f" for {parent_instance.short_name}"
            
        super().__init__(
            title,
            "Choose the type of container you want to configure"
        )
    
    def _setup_ui(self):
        form = QFormLayout()
        
        # Determine which definitions to show
        if self.parent_instance:
            container_def_obj = self.config_manager.get_container_def(self.parent_instance.definition_ref)
            defs = container_def_obj.sub_containers.values() if container_def_obj else []
        else:
            defs = self.module_def.containers.values()

        # Populate container types
        for container_def in defs:
            # Check if we can add more instances
            if self.parent_instance:
                current_count = sum(
                    1 for c in self.parent_instance.sub_containers
                    if c.definition_ref == container_def.definition_ref
                )
            else:
                current_count = sum(
                    1 for c in self.config_manager.configuration.containers
                    if c.definition_ref == container_def.definition_ref
                )
            
            label = f"{container_def.short_name} ({container_def.multiplicity_str})"
            limit_reached = container_def.upper_multiplicity != -1 and current_count >= container_def.upper_multiplicity
            
            if limit_reached:
                label += " [ALREADY CONFIGURED]"
                
            self.container_combo.addItem(label, container_def)
            
            # Disable item if limit reached
            if limit_reached:
                from PySide6.QtGui import QStandardItemModel
                model = self.container_combo.model()
                if isinstance(model, QStandardItemModel):
                    item = model.item(self.container_combo.count() - 1)
                    item.setEnabled(False)
        
        form.addRow("Container Type:", self.container_combo)
        
        # Instance name
        self.name_edit.setPlaceholderText("e.g., MyConfig_0")
        form.addRow("Instance Name:", self.name_edit)
        
        self.layout.addLayout(form)
        
        # Register fields for wizard
        self.registerField("container_type", self.container_combo)
        self.registerField("instance_name*", self.name_edit)
    
    def get_data(self) -> Dict[str, Any]:
        return {
            "container_def": self.container_combo.currentData(),
            "instance_name": self.name_edit.text()
        }
    
    def validatePage(self) -> bool:
        """Prevent proceeding if container limit reached"""
        container_def = self.container_combo.currentData()
        if not container_def:
            return False
            
        if self.parent_instance:
            current_count = sum(
                1 for c in self.parent_instance.sub_containers
                if c.definition_ref == container_def.definition_ref
            )
        else:
            current_count = sum(
                1 for c in self.config_manager.configuration.containers
                if c.definition_ref == container_def.definition_ref
            )
        
        if container_def.upper_multiplicity != -1 and current_count >= container_def.upper_multiplicity:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.warning(
                self, 
                "Multiplicity Limit", 
                f"Cannot add more instances of {container_def.short_name}.\n"
                f"Limit: {container_def.upper_multiplicity}"
            )
            return False
            
        return True


class ParameterConfigPage(WizardPage):
    """Page 2: Configure parameters"""
    
    def __init__(self):
        self.param_widgets: Dict[str, Any] = {}
        super().__init__(
            "Configure Parameters",
            "Set values for the container parameters"
        )
    
    def _setup_ui(self):
        self.form = QFormLayout()
        self.layout.addLayout(self.form)
        
        # Note: Parameters will be populated dynamically in initializePage
        self.info_label = QLabel("Parameters will be shown after selecting container type")
        self.layout.addWidget(self.info_label)
    
    def initializePage(self):
        """Called when page is shown - populate parameters dynamically"""
        wizard = self.wizard()
        
        # Proactively pull data from selection page to avoid signal timing issues
        if hasattr(wizard, 'selection_page'):
            data = wizard.selection_page.get_data()
            wizard.container_def = data.get("container_def")
            wizard.instance_name = data.get("instance_name")
            
        # Clear existing widgets
        while self.form.count():
            self.form.removeRow(0)
        self.param_widgets.clear()
        
        # Get selected container
        if wizard.container_def:
            container_def = wizard.container_def
            
            # Create widgets for each parameter
            for param_name, param_def in container_def.parameters.items():
                widget = self._create_param_widget(param_def)
                if widget:
                    self.param_widgets[param_name] = widget
                    label = f"{param_name}:"
                    if param_def.is_required:
                        label += " *"
                    self.form.addRow(label, widget)
    
    def _create_param_widget(self, param_def):
        """Create appropriate widget for parameter type"""
        if param_def.param_type == EcucParameterType.INTEGER:
            widget = QDoubleSpinBox()
            widget.setDecimals(0)
            if param_def.min_value is not None:
                widget.setMinimum(float(param_def.min_value))
            if param_def.max_value is not None:
                widget.setMaximum(float(param_def.max_value))
            else:
                widget.setMaximum(1e15) # Safety default
            if param_def.default_value is not None:
                widget.setValue(float(param_def.default_value))
            return widget
            
        elif param_def.param_type == EcucParameterType.BOOLEAN:
            widget = QCheckBox()
            if param_def.default_value is not None:
                widget.setChecked(bool(param_def.default_value))
            return widget
            
        elif param_def.param_type == EcucParameterType.ENUMERATION:
            widget = QComboBox()
            if param_def.literals:
                widget.addItems(param_def.literals)
            if param_def.default_value:
                index = widget.findText(str(param_def.default_value))
                if index >= 0:
                    widget.setCurrentIndex(index)
            return widget
            
        else:  # STRING, FLOAT, etc.
            widget = QLineEdit()
            if param_def.default_value is not None:
                widget.setText(str(param_def.default_value))
            return widget
    
    def get_data(self) -> Dict[str, Any]:
        """Get parameter values"""
        params = {}
        for param_name, widget in self.param_widgets.items():
            if isinstance(widget, (QSpinBox, QDoubleSpinBox)):
                params[param_name] = int(widget.value())
            elif isinstance(widget, QCheckBox):
                params[param_name] = widget.isChecked()
            elif isinstance(widget, QComboBox):
                params[param_name] = widget.currentText()
            elif isinstance(widget, QLineEdit):
                params[param_name] = widget.text()
        return {"parameters": params}


class ReviewPage(WizardPage):
    """Page 3: Review and confirm"""
    
    def __init__(self):
        self.review_text = QTextEdit()
        super().__init__(
            "Review Configuration",
            "Review your configuration before creating"
        )
    
    def _setup_ui(self):
        self.review_text.setReadOnly(True)
        self.layout.addWidget(self.review_text)
    
    def initializePage(self):
        """Show summary of configuration"""
        wizard = self.wizard()
        
        # Ensure latest data is pulled from previous pages
        if hasattr(wizard, 'selection_page'):
            sel_data = wizard.selection_page.get_data()
            wizard.container_def = sel_data.get("container_def")
            wizard.instance_name = sel_data.get("instance_name")
            
        if hasattr(wizard, 'param_page'):
            param_data = wizard.param_page.get_data()
            wizard.parameters = param_data.get("parameters", {})
            
        summary = "Configuration Summary\n"
        summary += "=" * 50 + "\n\n"
        
        if wizard.instance_name:
            summary += f"Instance Name: {wizard.instance_name}\n"
        if wizard.container_def:
            summary += f"Container Type: {wizard.container_def.short_name}\n\n"
        
        summary += "Parameters:\n"
        summary += "-" * 50 + "\n"
        
        if hasattr(wizard, 'parameters'):
            for name, value in wizard.parameters.items():
                summary += f"  {name}: {value}\n"
        
        self.review_text.setPlainText(summary)
    
    def get_data(self) -> Dict[str, Any]:
        return {}


class QuickConfigWizard(ConfigWizard):
    """Quick configuration wizard for creating container instances"""
    
    def __init__(self, module_def: EcucModuleDef, config_manager: ConfigurationManager, 
                 parent_instance: Optional[EcucContainerValue] = None, parent=None):
        self.module_def = module_def
        self.config_manager = config_manager
        self.parent_instance = parent_instance
        
        # Store intermediate data
        self.container_def: Optional[EcucContainerDef] = None
        self.instance_name: str = ""
        self.parameters: Dict[str, Any] = {}
        
        super().__init__(parent, "Quick Configuration Wizard")
    
    def _setup_pages(self):
        """Setup wizard pages"""
        # Page 1: Container selection
        self.selection_page = ContainerSelectionPage(self.module_def, self.config_manager, self.parent_instance)
        self.addPage(self.selection_page)
        
        # Page 2: Parameter configuration
        self.param_page = ParameterConfigPage()
        self.addPage(self.param_page)
        
        # Page 3: Review
        self.review_page = ReviewPage()
        self.addPage(self.review_page)
        
        # Connect page changes to update intermediate data
        self.currentIdChanged.connect(self._on_page_changed)
    
    def _on_page_changed(self, page_id: int):
        """Update intermediate data when page changes"""
        if page_id == 1:  # Moving to parameter page
            data = self.selection_page.get_data()
            self.container_def = data.get("container_def")
            self.instance_name = data.get("instance_name")
        elif page_id == 2:  # Moving to review page
            data = self.param_page.get_data()
            self.parameters = data.get("parameters", {})
    
    def accept(self):
        """Create the configuration when wizard finishes"""
        try:
            # Create container instance
            instance = self.config_manager.create_container_instance(
                self.container_def,
                parent=self.parent_instance,
                instance_name=self.instance_name
            )
            
            # Set parameter values
            for param_name, value in self.parameters.items():
                try:
                    self.config_manager.set_parameter_value(instance, param_name, value)
                except Exception as e:
                    print(f"Warning: Failed to set {param_name}: {e}")
            
            # Emit completion signal
            self.wizard_completed.emit({
                "instance": instance,
                "container_def": self.container_def
            })
            
        except Exception as e:
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.critical(self, "Error", f"Failed to create configuration:\n{str(e)}")
            return
        
        super().accept()
