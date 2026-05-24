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
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
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
        # Count instances (using short_name matching for EB Tresos compatibility)
        count = sum(
            1 for c in configuration.containers
            if self._definition_refs_match(c.definition_ref, container_def.definition_ref, container_def.short_name)
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
            # Count matching sub-containers using short_name matching
            count = sum(
                1 for sc in container.sub_containers
                if self._definition_refs_match(sc.definition_ref, sub_def.definition_ref, sub_def.short_name)
            )
            
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
    
    def _definition_refs_match(self, config_ref: str, def_ref: str, short_name: str) -> bool:
        """Check if a config definition_ref matches a module definition's definition_ref.

        First tries exact match, then falls back to matching by container short_name
        (last path segment), to handle EB Tresos projects with vendor-specific paths.
        EB Tresos also embeds the instance index in the definition_ref last segment
        (e.g. ``OsCoreIdMappingConfig_0``), so we also try after stripping a
        trailing ``_<digits>`` suffix.
        """
        import re

        # Try exact match first
        if config_ref == def_ref:
            return True

        # Fall back to matching by short_name (last segment of path)
        config_short_name = config_ref.rstrip('/').split('/')[-1] if config_ref else ""
        if config_short_name == short_name:
            return True

        # EB Tresos: strip trailing instance-index suffix (_0, _1, …)
        stripped = re.sub(r'_\d+$', '', config_short_name)
        return stripped == short_name
