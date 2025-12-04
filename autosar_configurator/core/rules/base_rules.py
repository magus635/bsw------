"""
Base Validation Rules - Fundamental parameter and type validation

These rules implement basic validation logic for parameters,
migrating and extending existing validation from ConfigurationManager.
"""
from typing import Optional

from ..validation_engine import ValidationRule, ValidationResult
from ..model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType
)
from ..model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucParameterValue
)


class TypeValidationRule(ValidationRule):
    """Validate parameter types match their definitions"""
    
    def __init__(self):
        super().__init__(
            name="TypeValidation",
            description="Validates that parameter values match their defined types"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        for container in configuration.containers:
            self._validate_container(container, module_def, result)
        
        return result
    
    def _validate_container(self, container: EcucContainerValue, module_def: EcucModuleDef, result: ValidationResult):
        """Recursively validate container and its sub-containers"""
        # Get container definition
        container_def = self._get_container_def(container.definition_ref, module_def)
        if not container_def:
            result.add_message(self._create_error(
                f"Container definition not found: {container.definition_ref}",
                container_path=container.get_path()
            ))
            return
        
        # Validate each parameter
        for param_name, param_value in container.parameter_values.items():
            param_def = container_def.parameters.get(param_name)
            if not param_def:
                result.add_message(self._create_warning(
                    f"Parameter '{param_name}' not defined in container definition",
                    container_path=container.get_path(),
                    parameter_name=param_name
                ))
                continue
            
            # Type-specific validation
            self._validate_type(param_def, param_value, container.get_path(), result)
        
        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            self._validate_container(sub_container, module_def, result)
    
    def _validate_type(self, param_def: EcucParameterDef, param_value: EcucParameterValue, 
                      container_path: str, result: ValidationResult):
        """Validate parameter value against its type"""
        value = param_value.value
        
        if param_def.param_type == EcucParameterType.INTEGER:
            if not isinstance(value, int):
                result.add_message(self._create_error(
                    f"Expected INTEGER, got {type(value).__name__}",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
        
        elif param_def.param_type == EcucParameterType.FLOAT:
            if not isinstance(value, (int, float)):
                result.add_message(self._create_error(
                    f"Expected FLOAT, got {type(value).__name__}",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
        
        elif param_def.param_type == EcucParameterType.BOOLEAN:
            if not isinstance(value, bool):
                result.add_message(self._create_error(
                    f"Expected BOOLEAN, got {type(value).__name__}",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
        
        elif param_def.param_type == EcucParameterType.STRING:
            if not isinstance(value, str):
                result.add_message(self._create_error(
                    f"Expected STRING, got {type(value).__name__}",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path
        
        Handles both absolute (/AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcHwUnit)
        and relative (AdcConfigSet/AdcHwUnit) paths
        """
        parts = definition_ref.split('/')
        
        # Handle absolute AUTOSAR paths
        if len(parts) >= 4 and parts[0] == '' and parts[1] == 'AUTOSAR':
            relative_path = '/'.join(parts[4:])
            if relative_path:
                return module_def.get_container_def(relative_path)
        
        # Handle relative paths
        if definition_ref and not definition_ref.startswith('/'):
            return module_def.get_container_def(definition_ref)
        
        return None


class RangeValidationRule(ValidationRule):
    """Validate numeric parameter ranges (min/max)"""
    
    def __init__(self):
        super().__init__(
            name="RangeValidation",
            description="Validates that numeric parameters are within min/max bounds"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        for container in configuration.containers:
            self._validate_container(container, module_def, result)
        
        return result
    
    def _validate_container(self, container: EcucContainerValue, module_def: EcucModuleDef, result: ValidationResult):
        """Recursively validate container parameters"""
        container_def = self._get_container_def(container.definition_ref, module_def)
        if not container_def:
            return
        
        for param_name, param_value in container.parameter_values.items():
            param_def = container_def.parameters.get(param_name)
            if not param_def:
                continue
            
            # Only validate numeric types
            if param_def.param_type in (EcucParameterType.INTEGER, EcucParameterType.FLOAT):
                value = param_value.value
                
                # Check min value
                if param_def.min_value is not None and value < param_def.min_value:
                    result.add_message(self._create_error(
                        f"Value {value} is below minimum {param_def.min_value}",
                        container_path=container.get_path(),
                        parameter_name=param_name,
                        suggested_fix=f"Set value to at least {param_def.min_value}"
                    ))
                
                # Check max value
                if param_def.max_value is not None and value > param_def.max_value:
                    result.add_message(self._create_error(
                        f"Value {value} is above maximum {param_def.max_value}",
                        container_path=container.get_path(),
                        parameter_name=param_name,
                        suggested_fix=f"Set value to at most {param_def.max_value}"
                    ))
        
        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            self._validate_container(sub_container, module_def, result)
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path"""
        parts = definition_ref.split('/')
        if len(parts) >= 4 and parts[0] == '' and parts[1] == 'AUTOSAR':
            relative_path = '/'.join(parts[4:])
            if relative_path:
                return module_def.get_container_def(relative_path)
        if definition_ref and not definition_ref.startswith('/'):
            return module_def.get_container_def(definition_ref)
        return None


class EnumerationValidationRule(ValidationRule):
    """Validate enumeration parameter values"""
    
    def __init__(self):
        super().__init__(
            name="EnumerationValidation",
            description="Validates that enumeration parameters have allowed literal values"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        for container in configuration.containers:
            self._validate_container(container, module_def, result)
        
        return result
    
    def _validate_container(self, container: EcucContainerValue, module_def: EcucModuleDef, result: ValidationResult):
        """Recursively validate container parameters"""
        container_def = self._get_container_def(container.definition_ref, module_def)
        if not container_def:
            return
        
        for param_name, param_value in container.parameter_values.items():
            param_def = container_def.parameters.get(param_name)
            if not param_def:
                continue
            
            # Only validate enumeration types
            if param_def.param_type == EcucParameterType.ENUMERATION:
                value = param_value.value
                
                if param_def.literals and value not in param_def.literals:
                    result.add_message(self._create_error(
                        f"Value '{value}' is not in allowed literals: {param_def.literals}",
                        container_path=container.get_path(),
                        parameter_name=param_name,
                        suggested_fix=f"Choose from: {', '.join(param_def.literals)}"
                    ))
        
        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            self._validate_container(sub_container, module_def, result)
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path"""
        parts = definition_ref.split('/')
        if len(parts) >= 4 and parts[0] == '' and parts[1] == 'AUTOSAR':
            relative_path = '/'.join(parts[4:])
            if relative_path:
                return module_def.get_container_def(relative_path)
        if definition_ref and not definition_ref.startswith('/'):
            return module_def.get_container_def(definition_ref)
        return None


class RequiredParameterRule(ValidationRule):
    """Validate that required parameters are present"""
    
    def __init__(self):
        super().__init__(
            name="RequiredParameter",
            description="Validates that all required parameters are configured"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        for container in configuration.containers:
            self._validate_container(container, module_def, result)
        
        return result
    
    def _validate_container(self, container: EcucContainerValue, module_def: EcucModuleDef, result: ValidationResult):
        """Recursively validate container parameters"""
        container_def = self._get_container_def(container.definition_ref, module_def)
        if not container_def:
            return
        
        # Check for required parameters
        for param_name, param_def in container_def.parameters.items():
            if param_def.is_required:
                if param_name not in container.parameter_values:
                    result.add_message(self._create_error(
                        f"Required parameter '{param_name}' is missing",
                        container_path=container.get_path(),
                        parameter_name=param_name,
                        suggested_fix=f"Add parameter '{param_name}'"
                    ))
        
        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            self._validate_container(sub_container, module_def, result)
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path"""
        parts = definition_ref.split('/')
        if len(parts) >= 4 and parts[0] == '' and parts[1] == 'AUTOSAR':
            relative_path = '/'.join(parts[4:])
            if relative_path:
                return module_def.get_container_def(relative_path)
        if definition_ref and not definition_ref.startswith('/'):
            return module_def.get_container_def(definition_ref)
        return None
