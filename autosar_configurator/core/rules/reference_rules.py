"""
Reference Validation Rules - Reference integrity and dependency checking

These rules validate reference relationships between containers,
including the critical TODO item: checking if an instance is referenced
before allowing deletion.
"""
from typing import Set, Dict, List, Optional

from ..validation_engine import ValidationRule, ValidationResult, ValidationMessage, ValidationSeverity
from ..model.definition_model import EcucModuleDef, EcucContainerDef
from ..model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucReferenceValue
)


class ResolutionErrorValidationRule(ValidationRule):
    """Convert ResolutionError objects to ValidationMessages
    
    This rule leverages the pre-computed resolution status
    on EcucReferenceValue instead of rebuilding path registries.
    
    Benefits:
    - Uses existing resolution_error info
    - Rich error messages with type, severity, suggestion
    - No duplicate path registry building
    """
    
    def __init__(self):
        super().__init__(
            name="ResolutionError",
            description="Converts reference resolution errors to validation messages"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
        result = ValidationResult()
        
        for container in configuration.containers:
            self._check_container(container, result)
        
        return result
    
    def _check_container(self, container: EcucContainerValue, result: ValidationResult):
        """Check references using has_error property"""
        for ref_name, ref_value in container.reference_values.items():
            if ref_value.has_error:
                error = ref_value.resolution_error
                
                # Map ResolutionError severity to ValidationSeverity
                severity_map = {
                    "error": ValidationSeverity.ERROR,
                    "warning": ValidationSeverity.WARNING,
                    "info": ValidationSeverity.INFO
                }
                severity = severity_map.get(error.severity, ValidationSeverity.ERROR)
                
                result.add_message(ValidationMessage(
                    severity=severity,
                    message=f"Reference '{ref_name}': {error.message}",
                    rule_name=self.name,
                    container_path=container.get_path(),
                    details=f"Error type: {error.error_type}",
                    suggested_fix=error.suggestion
                ))
        
        for sub in container.sub_containers:
            self._check_container(sub, result)


class ReferenceIntegrityRule(ValidationRule):
    """Validate reference integrity - all references point to existing containers
    
    This rule implements the TODO from config_manager.py:123:
    "Check if instance is referenced by other containers"
    """
    
    def __init__(self):
        super().__init__(
            name="ReferenceIntegrity",
            description="Validates that all references point to existing container instances"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        # Build registry of all container paths
        all_paths = self._build_path_registry(configuration)
        
        # Check all references
        for container in configuration.containers:
            self._validate_container_references(container, all_paths, result)
        
        return result
    
    def _build_path_registry(self, configuration: EcucModuleConfiguration) -> Set[str]:
        """Build a set of all valid container paths"""
        paths = set()
        
        def collect_paths(container: EcucContainerValue):
            paths.add(container.get_path())
            for sub_container in container.sub_containers:
                collect_paths(sub_container)
        
        for container in configuration.containers:
            collect_paths(container)
        
        return paths
    
    def _validate_container_references(self, container: EcucContainerValue,
                                       all_paths: Set[str],
                                       result: ValidationResult):
        """Recursively validate references in container"""
        # Check each reference
        for ref_name, ref_value in container.reference_values.items():
            target_path = ref_value.value_ref
            
            if target_path not in all_paths:
                result.add_message(self._create_error(
                    f"Reference '{ref_name}' points to non-existent container: {target_path}",
                    container_path=container.get_path(),
                    details="Dangling reference detected",
                    suggested_fix=f"Remove reference or create target container at {target_path}"
                ))
        
        # Recursively check sub-containers
        for sub_container in container.sub_containers:
            self._validate_container_references(sub_container, all_paths, result)
    
    @staticmethod
    def find_references_to(target_container: EcucContainerValue,
                          configuration: EcucModuleConfiguration) -> List[tuple]:
        """Find all references pointing to a specific container
        
        This is a utility method that can be used by ConfigurationManager
        to implement the TODO check before deletion.
        
        Args:
            target_container: Container to search references for
            configuration: Configuration to search in
            
        Returns:
            List of tuples (source_container, reference_name) that reference the target
        """
        target_path = target_container.get_path()
        references = []
        
        def search_references(container: EcucContainerValue):
            for ref_name, ref_value in container.reference_values.items():
                if ref_value.value_ref == target_path:
                    references.append((container, ref_name))
            
            for sub_container in container.sub_containers:
                search_references(sub_container)
        
        for container in configuration.containers:
            search_references(container)
        
        return references


class DanglingReferenceRule(ValidationRule):
    """Detect dangling references (references to deleted containers)
    
    This is related to ReferenceIntegrityRule but focuses specifically
    on detecting references that may have become invalid.
    """
    
    def __init__(self):
        super().__init__(
            name="DanglingReference",
            description="Detects references that point to containers that no longer exist"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        # This is essentially the same as ReferenceIntegrityRule
        # but could be extended with more sophisticated checks
        result = ValidationResult()
        
        all_paths = set()
        for container in configuration.containers:
            self._collect_paths(container, all_paths)
        
        for container in configuration.containers:
            self._check_dangling(container, all_paths, result)
        
        return result
    
    def _collect_paths(self, container: EcucContainerValue, paths: Set[str]):
        """Collect all container paths"""
        paths.add(container.get_path())
        for sub_container in container.sub_containers:
            self._collect_paths(sub_container, paths)
    
    def _check_dangling(self, container: EcucContainerValue, all_paths: Set[str], result: ValidationResult):
        """Check for dangling references"""
        for ref_name, ref_value in container.reference_values.items():
            if ref_value.value_ref not in all_paths:
                result.add_message(self._create_warning(
                    f"Dangling reference '{ref_name}' detected",
                    container_path=container.get_path(),
                    details=f"Target {ref_value.value_ref} does not exist",
                    suggested_fix="Remove this reference or restore the target container"
                ))
        
        for sub_container in container.sub_containers:
            self._check_dangling(sub_container, all_paths, result)


class RequiredReferenceRule(ValidationRule):
    """Validate that required references are set"""
    
    def __init__(self):
        super().__init__(
            name="RequiredReference",
            description="Validates that all required references are configured"
        )
    
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        for container in configuration.containers:
            self._validate_container(container, module_def, result)
        
        return result
    
    def _validate_container(self, container: EcucContainerValue, module_def: EcucModuleDef, result: ValidationResult):
        """Recursively validate required references"""
        container_def = self._get_container_def(container.definition_ref, module_def)
        if not container_def:
            return
        
        # Check for required references
        for ref_name, ref_def in container_def.references.items():
            if ref_def.is_required:
                if ref_name not in container.reference_values:
                    result.add_message(self._create_error(
                        f"Required reference '{ref_name}' is missing",
                        container_path=container.get_path(),
                        details=f"Destination: {ref_def.destination_ref}",
                        suggested_fix=f"Add reference '{ref_name}'"
                    ))
        
        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            self._validate_container(sub_container, module_def, result)
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path"""
        parts = definition_ref.split('/')
        if len(parts) < 4:
            return None
        relative_path = '/'.join(parts[4:])
        if not relative_path:
            return None
        return module_def.get_container_def(relative_path)
