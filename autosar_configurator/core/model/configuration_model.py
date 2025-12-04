"""
Configuration Model - ECUC Configuration (VALUE) layer
Represents user-created instances and their configured values
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Any, Set
from datetime import datetime

from .definition_model import VariantType


@dataclass
class EcucParameterValue:
    """ECUC Parameter Value (ECUC-TEXTUAL-PARAM-VALUE / ECUC-NUMERICAL-PARAM-VALUE)
    
    Stores the actual configured value for a parameter
    """
    definition_ref: str  # Path to EcucParameterDef, e.g., "/AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcPrescale"
    value: Any  # Actual value: "SARADC0", 14, True, etc.
    
    # Metadata
    is_modified: bool = False
    last_modified: Optional[datetime] = None
    
    def mark_modified(self):
        """Mark this value as modified"""
        self.is_modified = True
        self.last_modified = datetime.now()


@dataclass
class EcucReferenceValue:
    """ECUC Reference Value (ECUC-REFERENCE-VALUE)
    
    Stores a reference to another container instance
    """
    definition_ref: str  # Path to EcucReferenceDef
    value_ref: str  # Path to target container instance, e.g., "/Config/Mcu/McuModuleConfiguration/McuClockReferencePoint_0"
    
    # Metadata
    is_modified: bool = False


@dataclass
class EcucContainerValue:
    """ECUC Container Value (ECUC-CONTAINER-VALUE)
    
    Represents a user-created instance of a container definition
    """
    short_name: str  # User-defined instance name, e.g., "AdcHwUnit_0", "AdcConfigSet"
    definition_ref: str  # Path to EcucContainerDef, e.g., "/AUTOSAR/EcucDefs/Adc/AdcHwUnit"
    
    # Configured parameter values
    parameter_values: Dict[str, EcucParameterValue] = field(default_factory=dict)
    
    # Configured reference values
    reference_values: Dict[str, EcucReferenceValue] = field(default_factory=dict)
    
    # Sub-container instances
    sub_containers: List['EcucContainerValue'] = field(default_factory=list)
    
    # Metadata
    index: int = 0  # Instance index (for sorting)
    is_modified: bool = False
    last_modified: Optional[datetime] = None
    
    # Validation state
    validation_errors: List[str] = field(default_factory=list)
    
    def get_path(self) -> str:
        """Get full path of this container instance"""
        # This will be set by ConfigurationManager based on hierarchy
        return f"/Config/{self.short_name}"
    
    def set_parameter_value(self, param_name: str, value: Any, definition_ref: str):
        """Set or update a parameter value"""
        if param_name in self.parameter_values:
            param_value = self.parameter_values[param_name]
            param_value.value = value
            param_value.mark_modified()
        else:
            self.parameter_values[param_name] = EcucParameterValue(
                definition_ref=definition_ref,
                value=value,
                is_modified=True,
                last_modified=datetime.now()
            )
        self.mark_modified()
    
    def set_reference_value(self, ref_name: str, value_ref: str, definition_ref: str):
        """Set or update a reference value"""
        self.reference_values[ref_name] = EcucReferenceValue(
            definition_ref=definition_ref,
            value_ref=value_ref,
            is_modified=True
        )
        self.mark_modified()
    
    def add_sub_container(self, sub_container: 'EcucContainerValue'):
        """Add a sub-container instance"""
        self.sub_containers.append(sub_container)
        self.mark_modified()
    
    def remove_sub_container(self, sub_container: 'EcucContainerValue'):
        """Remove a sub-container instance"""
        self.sub_containers.remove(sub_container)
        self.mark_modified()
    
    def mark_modified(self):
        """Mark this container as modified"""
        self.is_modified = True
        self.last_modified = datetime.now()
    
    def has_validation_errors(self) -> bool:
        """Check if this container has validation errors"""
        return len(self.validation_errors) > 0


@dataclass
class EcucModuleConfiguration:
    """ECUC Module Configuration Values (ECUC-MODULE-CONFIGURATION-VALUES)
    
    Top-level configuration for a BSW module, containing all user-created instances
    """
    short_name: str  # e.g., "Adc"
    definition_ref: str  # Path to EcucModuleDef, e.g., "/AUTOSAR/EcucDefs/Adc"
    
    # Top-level container instances
    containers: List[EcucContainerValue] = field(default_factory=list)
    
    # Metadata
    implementation_config_variant: str = "VariantPostBuild"
    is_modified: bool = False
    last_saved: Optional[datetime] = None
    
    # All created instance paths (for quick lookup)
    _instance_registry: Dict[str, EcucContainerValue] = field(default_factory=dict)
    
    def add_container(self, container: EcucContainerValue):
        """Add a top-level container instance"""
        self.containers.append(container)
        self._register_instance(container)
        self.is_modified = True
    
    def remove_container(self, container: EcucContainerValue):
        """Remove a container instance"""
        self.containers.remove(container)
        self._unregister_instance(container)
        self.is_modified = True
    
    def _register_instance(self, container: EcucContainerValue):
        """Register a container instance and all its sub-containers"""
        path = container.get_path()
        self._instance_registry[path] = container
        
        # Recursively register sub-containers
        for sub_container in container.sub_containers:
            self._register_instance(sub_container)
    
    def _unregister_instance(self, container: EcucContainerValue):
        """Unregister a container instance and all its sub-containers"""
        path = container.get_path()
        if path in self._instance_registry:
            del self._instance_registry[path]
        
        # Recursively unregister sub-containers
        for sub_container in container.sub_containers:
            self._unregister_instance(sub_container)
    
    def get_instance_by_path(self, path: str) -> Optional[EcucContainerValue]:
        """Get a container instance by its full path"""
        return self._instance_registry.get(path)
    
    def get_all_instances_of_def(self, definition_ref: str) -> List[EcucContainerValue]:
        """Get all instances of a specific container definition"""
        instances = []
        for container in self.containers:
            instances.extend(self._find_instances_by_def(container, definition_ref))
        return instances
    
    def _find_instances_by_def(self, container: EcucContainerValue, definition_ref: str) -> List[EcucContainerValue]:
        """Recursively find all instances matching a definition"""
        instances = []
        if container.definition_ref == definition_ref:
            instances.append(container)
        
        for sub_container in container.sub_containers:
            instances.extend(self._find_instances_by_def(sub_container, definition_ref))
        
        return instances
    
    def mark_saved(self):
        """Mark configuration as saved"""
        self.is_modified = False
        self.last_saved = datetime.now()
