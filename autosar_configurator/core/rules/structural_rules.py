"""
Structural Validation Rules - Container hierarchy and multiplicity validation

These rules validate the structural aspects of the configuration,
including container multiplicity constraints and hierarchy.
"""
from typing import Optional, Dict

from ..validation_engine import ValidationRule, ValidationResult
from ..model.definition_model import EcucModuleDef, EcucContainerDef
from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue


class MultiplicityValidationRule(ValidationRule):
    """Validate container multiplicity constraints"""
    
    def __init__(self):
        super().__init__(
            name="MultiplicityValidation",
            description="Validates that container instances conform to min/max multiplicity constraints"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        # Validate top-level containers
        for container_name, container_def in module_def.containers.items():
            self._validate_top_level_multiplicity(container_def, configuration, result)
        
        # Validate nested containers
        for container in configuration.containers:
            self._validate_container_multiplicity(container, module_def, result)
        
        return result
    
    def _validate_top_level_multiplicity(self, container_def: EcucContainerDef, 
                                         configuration: EcucModuleConfiguration,
                                         result: ValidationResult):
        """Validate multiplicity of top-level containers"""
        # Count instances
        count = sum(
            1 for c in configuration.containers
            if c.definition_ref == container_def.definition_ref
        )
        
        # Check lower bound
        if count < container_def.lower_multiplicity:
            result.add_message(self._create_error(
                f"Container '{container_def.short_name}' requires at least "
                f"{container_def.lower_multiplicity} instance(s), but only {count} exist",
                details=f"Multiplicity: {container_def.multiplicity_str}",
                suggested_fix=f"Add {container_def.lower_multiplicity - count} more instance(s)"
            ))
        
        # Check upper bound
        if container_def.upper_multiplicity != -1 and count > container_def.upper_multiplicity:
            result.add_message(self._create_error(
                f"Container '{container_def.short_name}' allows at most "
                f"{container_def.upper_multiplicity} instance(s), but {count} exist",
                details=f"Multiplicity: {container_def.multiplicity_str}",
                suggested_fix=f"Remove {count - container_def.upper_multiplicity} instance(s)"
            ))
    
    def _validate_container_multiplicity(self, container: EcucContainerValue,
                                         module_def: EcucModuleDef,
                                         result: ValidationResult):
        """Recursively validate multiplicity of sub-containers"""
        container_def = self._get_container_def(container.definition_ref, module_def)
        if not container_def:
            return
        
        # Count instances of each sub-container type
        sub_container_counts: Dict[str, int] = {}
        for sub_container in container.sub_containers:
            def_ref = sub_container.definition_ref
            sub_container_counts[def_ref] = sub_container_counts.get(def_ref, 0) + 1
        
        # Validate each sub-container definition's multiplicity
        for sub_name, sub_def in container_def.sub_containers.items():
            count = sub_container_counts.get(sub_def.definition_ref, 0)
            
            # Check lower bound
            if count < sub_def.lower_multiplicity:
                result.add_message(self._create_error(
                    f"Sub-container '{sub_def.short_name}' requires at least "
                    f"{sub_def.lower_multiplicity} instance(s), but only {count} exist",
                    container_path=container.get_path(),
                    details=f"Multiplicity: {sub_def.multiplicity_str}",
                    suggested_fix=f"Add {sub_def.lower_multiplicity - count} more instance(s)"
                ))
            
            # Check upper bound
            if sub_def.upper_multiplicity != -1 and count > sub_def.upper_multiplicity:
                result.add_message(self._create_error(
                    f"Sub-container '{sub_def.short_name}' allows at most "
                    f"{sub_def.upper_multiplicity} instance(s), but {count} exist",
                    container_path=container.get_path(),
                    details=f"Multiplicity: {sub_def.multiplicity_str}",
                    suggested_fix=f"Remove {count - sub_def.upper_multiplicity} instance(s)"
                ))
        
        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            self._validate_container_multiplicity(sub_container, module_def, result)
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path"""
        parts = definition_ref.split('/')
        if len(parts) < 4:
            return None
        relative_path = '/'.join(parts[4:])
        if not relative_path:
            return None
        return module_def.get_container_def(relative_path)
