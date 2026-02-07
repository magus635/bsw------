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


def _resolve_container_def(definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
    """Common helper to resolve container definition from reference path.

    Handles various path formats:
    - /AUTOSAR/EcucDefs/Module/Container (standard AUTOSAR)
    - /PackageName/Module/Container (custom package like THA6_AS440_FuSa)
    - Container/SubContainer (relative paths)
    """
    if not definition_ref:
        return None

    parts = definition_ref.split('/')

    # Handle absolute paths (starts with /)
    if parts[0] == '' and len(parts) >= 3:
        # Try to find module name in path
        module_name = module_def.short_name
        try:
            module_idx = parts.index(module_name)
            relative_path = '/'.join(parts[module_idx + 1:])
            if relative_path:
                return module_def.get_container_def(relative_path)
        except ValueError:
            pass

        # Fallback: assume format /Package/Module/Container...
        if len(parts) >= 4:
            relative_path = '/'.join(parts[3:])
            if relative_path:
                return module_def.get_container_def(relative_path)

    # Handle relative paths
    if not definition_ref.startswith('/'):
        return module_def.get_container_def(definition_ref)

    return None


class TypeValidationRule(ValidationRule):
    """Validate parameter types match their definitions"""
    
    def __init__(self):
        super().__init__(
            name="TypeValidation",
            description="Validates that parameter values match their defined types"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
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
                # Try to find where this parameter should be defined
                correct_location = self._find_parameter_location(param_name, module_def)
                if correct_location:
                    result.add_message(self._create_warning(
                        f"Parameter '{param_name}' is in wrong container. "
                        f"It should be in '{correct_location}', not '{container_def.short_name}'",
                        container_path=container.get_path(),
                        parameter_name=param_name,
                        suggested_fix=f"Move parameter to {correct_location}"
                    ))
                else:
                    result.add_message(self._create_warning(
                        f"Parameter '{param_name}' not defined in container '{container_def.short_name}'",
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
            # Accept int directly, or string representations of integers
            is_valid = isinstance(value, int) and not isinstance(value, bool)
            if isinstance(value, str):
                try:
                    int(value)
                    is_valid = True
                except ValueError:
                    pass
            if not is_valid:
                result.add_message(self._create_error(
                    f"Expected INTEGER, got {type(value).__name__}",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
        
        elif param_def.param_type == EcucParameterType.FLOAT:
            # Accept int/float directly, or string representations of floats
            is_valid = isinstance(value, (int, float)) and not isinstance(value, bool)
            if isinstance(value, str):
                try:
                    float(value)
                    is_valid = True
                except ValueError:
                    pass
            if not is_valid:
                result.add_message(self._create_error(
                    f"Expected FLOAT, got {type(value).__name__}",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
        
        elif param_def.param_type == EcucParameterType.BOOLEAN:
            # Accept bool, int (0/1), or string ('true'/'false', '0'/'1')
            # This is common in AUTOSAR configurations where booleans are stored as integers
            is_valid_bool = isinstance(value, bool)
            is_valid_int_bool = isinstance(value, int) and value in (0, 1)
            is_valid_str_bool = isinstance(value, str) and value.lower() in ('true', 'false', '0', '1')
            
            if not (is_valid_bool or is_valid_int_bool or is_valid_str_bool):
                result.add_message(self._create_error(
                    f"Expected BOOLEAN, got {type(value).__name__} (value: {value})",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
        
        elif param_def.param_type == EcucParameterType.STRING:
            # Accept str directly, and also int/float/bool which can be used as string values
            # This is common in AUTOSAR for fields like CryptoKeyElementInitValue, FlsExpectedHwId
            # where numeric IDs might be stored
            if not isinstance(value, (str, int, float, bool)):
                result.add_message(self._create_error(
                    f"Expected STRING, got {type(value).__name__}",
                    container_path=container_path,
                    parameter_name=param_def.short_name
                ))
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path

        Handles various path formats:
        - /AUTOSAR/EcucDefs/Module/Container (standard AUTOSAR)
        - /PackageName/Module/Container (custom package like THA6_AS440_FuSa)
        - Container/SubContainer (relative paths)
        """
        if not definition_ref:
            return None

        parts = definition_ref.split('/')

        # Handle absolute paths (starts with /)
        if parts[0] == '' and len(parts) >= 3:
            # Format: /PackageName/ModuleName/ContainerPath...
            # Extract container path after module name (parts[2] is module name)
            # Try to match module name with module_def
            module_name = module_def.short_name

            # Find module name position in path
            try:
                module_idx = parts.index(module_name)
                # Container path is everything after module name
                container_path = '/'.join(parts[module_idx + 1:])
                if container_path:
                    return module_def.get_container_def(container_path)
            except ValueError:
                # Module name not found in path, try fallback
                pass

            # Fallback: assume format /Package/Module/Container...
            # Take parts after position 2 (skip '', PackageName, ModuleName)
            if len(parts) >= 4:
                container_path = '/'.join(parts[3:])
                if container_path:
                    return module_def.get_container_def(container_path)

        # Handle relative paths
        if not definition_ref.startswith('/'):
            return module_def.get_container_def(definition_ref)

        return None

    def _find_parameter_location(self, param_name: str, module_def: EcucModuleDef) -> Optional[str]:
        """Search all containers to find where a parameter should be defined

        Args:
            param_name: Parameter name to search for
            module_def: Module definition to search in

        Returns:
            Container path where the parameter is defined, or None
        """
        def search_container(container_def: EcucContainerDef, path: str) -> Optional[str]:
            # Check if parameter is in this container
            if param_name in container_def.parameters:
                return path

            # Search sub-containers
            for sub_name, sub_def in container_def.sub_containers.items():
                result = search_container(sub_def, f"{path}/{sub_name}")
                if result:
                    return result

            return None

        # Search all top-level containers
        for container_name, container_def in module_def.containers.items():
            result = search_container(container_def, container_name)
            if result:
                return result

        return None


class RangeValidationRule(ValidationRule):
    """Validate numeric parameter ranges (min/max)"""
    
    def __init__(self):
        super().__init__(
            name="RangeValidation",
            description="Validates that numeric parameters are within min/max bounds"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
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
                
                # Convert string to number if needed
                if isinstance(value, str):
                    try:
                        if param_def.param_type == EcucParameterType.INTEGER:
                            value = int(value)
                        else:
                            value = float(value)
                    except (ValueError, TypeError):
                        # Skip range validation if value can't be converted
                        continue
                
                # Ensure we have a numeric value
                if not isinstance(value, (int, float)):
                    continue
                
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
        return _resolve_container_def(definition_ref, module_def)


class EnumerationValidationRule(ValidationRule):
    """Validate enumeration parameter values"""
    
    def __init__(self):
        super().__init__(
            name="EnumerationValidation",
            description="Validates that enumeration parameters have allowed literal values"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
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
        return _resolve_container_def(definition_ref, module_def)


class RequiredParameterRule(ValidationRule):
    """Validate that required parameters are present"""
    
    def __init__(self):
        super().__init__(
            name="RequiredParameter",
            description="Validates that all required parameters are configured"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
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
        return _resolve_container_def(definition_ref, module_def)
