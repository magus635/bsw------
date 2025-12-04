"""
Quick Configuration Wizard
Helps users quickly configure common container instances
"""
from PySide6.QtWidgets import (
    QVBoxLayout, QLabel, QComboBox, QLineEdit,
    QFormLayout, QSpinBox, QCheckBox, QTextEdit
)
from typing import Dict, Any, Optional

from .wizard_base import ConfigWizard, WizardPage
from ...core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterType
from ...core.config_manager import ConfigurationManager


class ContainerSelectionPage(WizardPage):
    """Page 1: Select container type to configure"""
    
    def __init__(self, module_def: EcucModuleDef):
        self.module_def = module_def
        self.container_combo = QComboBox()
        self.name_edit = QLineEdit()
        super().__init__(
            "Select Container Type",
            "Choose the type of container you want to configure"
        )
    
    def _setup_ui(self):
        form = QFormLayout()
        
        # Populate container types
        for container_def in self.module_def.containers.values():
            self.container_combo.addItem(
                f"{container_def.short_name} ({container_def.multiplicity_str})",
                container_def
            )
        
        form.addRow("Container Type:", self.container_combo)
        
        # Instance name
        self.name_edit.setPlaceholderText("e.g., MyConfig_0")
        form.addRow("Instance Name:", self.name_edit)
        
        self.layout.addLayout(form)
        
        # Register fields for wizard
        self.registerField("container_type*", self.container_combo)
        self.registerField("instance_name*", self.name_edit)
    
    def get_data(self) -> Dict[str, Any]:
        return {
            "container_def": self.container_combo.currentData(),
            "instance_name": self.name_edit.text()
        }


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
        # Clear existing widgets
        while self.form.count():
            self.form.removeRow(0)
        self.param_widgets.clear()
        
        # Get selected container from previous page
        wizard = self.wizard()
        if hasattr(wizard, 'container_def'):
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
            widget = QSpinBox()
            if param_def.min_value is not None:
                widget.setMinimum(int(param_def.min_value))
            if param_def.max_value is not None:
                widget.setMaximum(int(param_def.max_value))
            if param_def.default_value is not None:
                widget.setValue(int(param_def.default_value))
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
            if isinstance(widget, QSpinBox):
                params[param_name] = widget.value()
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
        
        summary = "Configuration Summary\n"
        summary += "=" * 50 + "\n\n"
        
        if hasattr(wizard, 'instance_name'):
            summary += f"Instance Name: {wizard.instance_name}\n"
        if hasattr(wizard, 'container_def'):
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
    
    def __init__(self, module_def: EcucModuleDef, config_manager: ConfigurationManager, parent=None):
        self.module_def = module_def
        self.config_manager = config_manager
        
        # Store intermediate data
        self.container_def: Optional[EcucContainerDef] = None
        self.instance_name: str = ""
        self.parameters: Dict[str, Any] = {}
        
        super().__init__(parent, "Quick Configuration Wizard")
    
    def _setup_pages(self):
        """Setup wizard pages"""
        # Page 1: Container selection
        self.selection_page = ContainerSelectionPage(self.module_def)
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
