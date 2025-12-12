"""
Configuration Manager - Manages user-created configuration instances
Provides CRUD operations for container instances with validation
"""
from typing import Optional, List, Dict, Tuple
from pathlib import Path

from .model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType
)
from .model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucParameterValue
)


class ValidationError(Exception):
    """Custom exception for configuration validation errors"""
    pass


class ConfigurationManager:
    """Manages ECUC configuration instances based on definitions"""
    
    def __init__(self, module_def: EcucModuleDef):
        """Initialize configuration manager
        
        Args:
            module_def: Module definition (template)
        """
        self.module_def = module_def
        
        # Create empty configuration
        self.configuration = EcucModuleConfiguration(
            short_name=module_def.short_name,
            definition_ref=module_def.definition_ref
        )
        
        # Instance counters for auto-naming
        self._instance_counters: Dict[str, int] = {}
        
        # Custom rules
        self.custom_rule_files: List[Path] = []
    
    def create_container_instance(self,
                                  container_def: EcucContainerDef,
                                  parent: Optional[EcucContainerValue] = None,
                                  instance_name: Optional[str] = None) -> EcucContainerValue:
        """Create a new container instance based on definition
        
        Args:
            container_def: Container definition (template)
            parent: Parent container instance (None for top-level)
            instance_name: Custom name, or auto-generate if None
            
        Returns:
            Created EcucContainerValue instance
            
        Raises:
            ValidationError if constraints are violated
        """
        # Check multiplicity constraints
        if parent:
            self._check_multiplicity_before_add(container_def, parent)
        else:
            self._check_multiplicity_before_add_toplevel(container_def)
        
        # Generate instance name if not provided
        if not instance_name:
            instance_name = self._generate_instance_name(container_def, parent)
        
        # Check for duplicate name
        self._check_duplicate_name(instance_name, container_def, parent)
        
        # Create instance
        instance = EcucContainerValue(
            short_name=instance_name,
            definition_ref=container_def.definition_ref,
            index=self._get_next_index(container_def.short_name)
        )
        
        # Initialize with default parameter values (smart defaults)
        for param_name, param_def in container_def.parameters.items():
            value = None
            
            # Determine default value
            if param_def.default_value is not None:
                # Use explicit default from DEF
                value = param_def.default_value
            elif param_def.param_type == EcucParameterType.ENUMERATION:
                # Use first enumeration literal
                if param_def.literals and len(param_def.literals) > 0:
                    value = param_def.literals[0]
            elif param_def.param_type == EcucParameterType.INTEGER:
                # Use min value or 0
                value = param_def.min_value if param_def.min_value is not None else 0
            elif param_def.param_type == EcucParameterType.FLOAT:
                # Use min value or 0.0
                value = param_def.min_value if param_def.min_value is not None else 0.0
            elif param_def.param_type == EcucParameterType.BOOLEAN:
                # Default to False
                value = False
            elif param_def.param_type == EcucParameterType.STRING:
                # Default to empty string
                value = ""
            
            # Set the value if determined
            if value is not None:
                instance.set_parameter_value(
                    param_name,
                    value,
                    param_def.definition_ref
                )
        
        # Add to parent or top-level
        if parent:
            parent.add_sub_container(instance)
        else:
            self.configuration.add_container(instance)
        
        return instance
    
    def delete_container_instance(self,
                                  instance: EcucContainerValue,
                                  parent: Optional[EcucContainerValue] = None):
        """Delete a container instance
        
        Args:
            instance: Instance to delete
            parent: Parent container (None for top-level)
            
        Raises:
            ValidationError if constraints are violated
        """
        # Get container definition
        container_def = self.get_container_def(instance.definition_ref)
        if not container_def:
            raise ValidationError(f"Container definition not found: {instance.definition_ref}")
        
        # Check lower multiplicity
        if parent:
            current_count = self._count_instances_in_parent(container_def, parent)
            if current_count <= container_def.lower_multiplicity:
                raise ValidationError(
                    f"Cannot delete: must have at least {container_def.lower_multiplicity} "
                    f"instances of {container_def.short_name}"
                )
        
        
        # Check if instance is referenced by other containers
        refs = self._find_references_to(instance)
        if refs:
            ref_details = ', '.join([f"{src.short_name}.{ref_name}" for src, ref_name in refs])
            raise ValidationError(
                f"Cannot delete {instance.short_name}: "
                f"Referenced by {len(refs)} other container(s): {ref_details}"
            )
        
        # Remove instance
        if parent:
            parent.remove_sub_container(instance)
            # Unregister from configuration registry
            self.configuration._unregister_instance(instance)
        else:
            self.configuration.remove_container(instance)
            
    def add_container_instance(self, instance: EcucContainerValue, parent: Optional[EcucContainerValue] = None):
        """Add an existing container instance (e.g. from paste/undo)
        
        Args:
            instance: Instance to add
            parent: Parent container (None for top-level)
        """
        # Validate multiplicity if needed (optional here as undo implies valid state, but paste needs check)
        # For robustness, we could check. But paste logic handles duplication/naming.
        
        if parent:
            parent.add_sub_container(instance)
            # Register in configuration registry
            self.configuration._register_instance(instance)
        else:
            self.configuration.add_container(instance)
    
    def set_parameter_value(self,
                           container: EcucContainerValue,
                           param_name: str,
                           value: any):
        """Set parameter value with validation and type conversion
        
        Args:
            container: Container instance
            param_name: Parameter name
            value: New value (will be converted to appropriate type)
            
        Raises:
            ValidationError if parameter not found or value invalid
        """
        # Get container definition
        container_def = self.get_container_def(container.definition_ref)
        if not container_def:
            raise ValidationError(f"Container definition not found: {container.definition_ref}")
        
        # Get parameter definition
        param_def = container_def.parameters.get(param_name)
        if not param_def:
            raise ValidationError(
                f"Parameter '{param_name}' not found in {container_def.short_name}"
            )
        
        # Type conversion and validation
        try:
            if param_def.param_type == EcucParameterType.INTEGER:
                value = int(value)
                if param_def.min_value is not None and value < param_def.min_value:
                    raise ValidationError(f"{param_name}: value {value} < minimum {param_def.min_value}")
                if param_def.max_value is not None and value > param_def.max_value:
                    raise ValidationError(f"{param_name}: value {value} > maximum {param_def.max_value}")
                    
            elif param_def.param_type == EcucParameterType.FLOAT:
                value = float(value)
                if param_def.min_value is not None and value < param_def.min_value:
                    raise ValidationError(f"{param_name}: value {value} < minimum {param_def.min_value}")
                if param_def.max_value is not None and value > param_def.max_value:
                    raise ValidationError(f"{param_name}: value {value} > maximum {param_def.max_value}")
                    
            elif param_def.param_type == EcucParameterType.BOOLEAN:
                # Convert to bool (handle various inputs)
                if isinstance(value, str):
                    value = value.lower() in ('true', '1', 'yes')
                else:
                    value = bool(value)
                    
            elif param_def.param_type == EcucParameterType.ENUMERATION:
                value = str(value)
                if param_def.literals and value not in param_def.literals:
                    raise ValidationError(
                        f"{param_name}: '{value}' not in allowed values: {param_def.literals}"
                    )
                    
            elif param_def.param_type == EcucParameterType.STRING:
                value = str(value)
                
        except (ValueError, TypeError) as e:
            raise ValidationError(f"{param_name}: Invalid value type - {e}")
        
        # Set value in container
        container.set_parameter_value(param_name, value, param_def.definition_ref)
    
    def get_container_def(self, definition_ref: str) -> Optional[EcucContainerDef]:
        """Get container definition by reference path
        
        Args:
            definition_ref: Definition reference path (absolute or relative)
            
        Returns:
            EcucContainerDef or None
        """
        # Check if it's a relative path (doesn't start with /)
        if not definition_ref.startswith('/'):
            return self.module_def.get_container_def(definition_ref)
            
        # Parse absolute path: /AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcHwUnit
        parts = definition_ref.split('/')
        if len(parts) < 4:  # Minimum: ['', 'AUTOSAR', 'EcucDefs', 'Module']
            return None
        
        # Remove prefix and get relative path
        # Example: AdcConfigSet or AdcConfigSet/AdcHwUnit
        relative_path = '/'.join(parts[4:])  # Skip '', 'AUTOSAR', 'EcucDefs', 'ModuleName'
        
        if not relative_path:
            return None
        
        return self.module_def.get_container_def(relative_path)
    
    def _get_parameter_def(self, container: EcucContainerValue, param_name: str) -> Optional[EcucParameterDef]:
        """Get parameter definition from container's definition"""
        container_def = self.get_container_def(container.definition_ref)
        if not container_def:
            return None
        return container_def.parameters.get(param_name)
    
    def _validate_parameter_value(self, param_def: EcucParameterDef, value: any):
        """Validate parameter value against definition
        
        Raises:
            ValidationError if value is invalid
        """
        if param_def.param_type == EcucParameterType.INTEGER:
            if not isinstance(value, int):
                raise ValidationError(f"{param_def.short_name}: Expected integer, got {type(value).__name__}")
            
            if param_def.min_value is not None and value < param_def.min_value:
                raise ValidationError(
                    f"{param_def.short_name}: Value {value} below minimum {param_def.min_value}"
                )
            
            if param_def.max_value is not None and value > param_def.max_value:
                raise ValidationError(
                    f"{param_def.short_name}: Value {value} above maximum {param_def.max_value}"
                )
        
        elif param_def.param_type == EcucParameterType.ENUMERATION:
            if value not in param_def.literals:
                raise ValidationError(
                    f"{param_def.short_name}: Value '{value}' not in allowed literals: {param_def.literals}"
                )
        
        elif param_def.param_type == EcucParameterType.BOOLEAN:
            if not isinstance(value, bool):
                raise ValidationError(f"{param_def.short_name}: Expected boolean, got {type(value).__name__}")
    
    def _check_multiplicity_before_add(self, container_def: EcucContainerDef, parent: EcucContainerValue):
        """Check if adding another instance would violate multiplicity"""
        current_count = self._count_instances_in_parent(container_def, parent)
        
        if container_def.upper_multiplicity != -1:  # -1 means unlimited
            if current_count >= container_def.upper_multiplicity:
                raise ValidationError(
                    f"Cannot add more instances: maximum {container_def.upper_multiplicity} "
                    f"instances of {container_def.short_name} allowed"
                )
    
    def _check_multiplicity_before_add_toplevel(self, container_def: EcucContainerDef):
        """Check multiplicity for top-level containers"""
        current_count = sum(
            1 for c in self.configuration.containers
            if c.definition_ref == container_def.definition_ref
        )
        
        if container_def.upper_multiplicity != -1:
            if current_count >= container_def.upper_multiplicity:
                raise ValidationError(
                    f"Cannot add more instances: maximum {container_def.upper_multiplicity} "
                    f"instances of {container_def.short_name} allowed"
                )
    
    def _count_instances_in_parent(self, container_def: EcucContainerDef, parent: EcucContainerValue) -> int:
        """Count existing instances of a container definition in parent"""
        return sum(
            1 for c in parent.sub_containers
            if c.definition_ref == container_def.definition_ref
        )
    
    def _generate_instance_name(self, container_def: EcucContainerDef, parent: Optional[EcucContainerValue] = None) -> str:
        """Auto-generate unique instance name (e.g., AdcHwUnit_0, AdcHwUnit_1)"""
        base_name = container_def.short_name
        
        if not container_def.is_multiple:
            return base_name
            
        # Find next available index
        counter = 0
        while True:
            candidate_name = f"{base_name}_{counter}"
            if not self._instance_exists(candidate_name, container_def, parent):
                return candidate_name
            counter += 1
    
    def _instance_exists(self, name: str, container_def: EcucContainerDef, parent: Optional[EcucContainerValue] = None) -> bool:
        """Check if instance with name exists in the same scope"""
        # Get siblings
        if parent:
            siblings = parent.sub_containers
        else:
            siblings = self.configuration.containers
            
        # Check for name match
        for sibling in siblings:
            if sibling.definition_ref == container_def.definition_ref and sibling.short_name == name:
                return True
        return False

    def _check_duplicate_name(self, name: str, container_def: EcucContainerDef, parent: Optional[EcucContainerValue] = None):
        """Check if name is duplicate and raise ValidationError"""
        if self._instance_exists(name, container_def, parent):
            raise ValidationError(f"Instance with name '{name}' already exists")

    def _get_next_index(self, container_name: str) -> int:
        """Get next index for sorting"""
        # Simple counter is fine for sorting index, or we could use len()
        return self._instance_counters.get(container_name, 0)
    
    def add_custom_rule_file(self, file_path: Path):
        """Add a custom rule file"""
        if file_path not in self.custom_rule_files:
            self.custom_rule_files.append(file_path)

    def validate_configuration(self) -> 'ValidationResult':
        """Validate current configuration"""
        from .validation_engine import ValidationEngine
        
        engine = ValidationEngine(self.module_def, self.configuration)
        engine.register_default_rules()
        
        # Load custom rules
        for rule_file in self.custom_rule_files:
            try:
                engine.load_custom_rules(rule_file)
            except Exception as e:
                print(f"Warning: Failed to load rules from {rule_file}: {e}")
                
        return engine.validate()

    def save_configuration(self, file_path: Path):
        """Save configuration to ARXML file
        
        Args:
            file_path: Output file path
        """
        from .serializer.ecuc_serializer import EcucValueSerializer
        
        serializer = EcucValueSerializer()
        serializer.serialize_to_file(self.configuration, file_path)
        
        # Mark as saved to reset is_modified flag
        self.configuration.mark_saved()
        
    def load_configuration(self, file_path: Path):
        """Load configuration from ARXML file
        
        Args:
            file_path: Input file path
        """
        from .parser.arxml_parser import ArxmlParser
        
        parser = ArxmlParser()
        # Parse the file to find ECUC-MODULE-CONFIGURATION-VALUES
        # We need to parse the whole file first
        try:
            # Use lxml directly to find the element first, or extend parser
            # Actually ArxmlParser.parse_file returns a Container, but we need EcucModuleConfiguration
            # Let's use a helper in parser or parse manually here
            # Better: use the new method in ArxmlParser
            
            import lxml.etree as etree
            tree = etree.parse(str(file_path))
            root = tree.getroot()
            
            # Find ECUC-MODULE-CONFIGURATION-VALUES
            namespaces = {'ar': 'http://autosar.org/schema/r4.0'}
            config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', namespaces)
            if config_elem is None:
                config_elem = root.find('.//ECUC-MODULE-CONFIGURATION-VALUES')
                
            if config_elem is None:
                raise ValueError("No ECUC-MODULE-CONFIGURATION-VALUES found in file")
                
            new_config = parser.parse_ecuc_configuration_values(config_elem)
            if new_config:
                self.configuration = new_config
                # Reset counters
                self._instance_counters.clear()
                # Rebuild counters based on loaded configuration
                for container in self.configuration.containers:
                    self._update_counters_recursive(container)
                    
                # Mark as saved (just loaded, no modifications)
                self.configuration.mark_saved()
                    
        except Exception as e:
            raise ValueError(f"Failed to load configuration: {e}")

    def _update_counters_recursive(self, container: EcucContainerValue):
        """Update instance counters based on existing container"""
        # Parse index from name (e.g. Unit_0 -> 0)
        try:
            base_name = container.short_name.rsplit('_', 1)[0]
            index = int(container.short_name.rsplit('_', 1)[1])
            
            current_max = self._instance_counters.get(base_name, 0)
            if index >= current_max:
                self._instance_counters[base_name] = index + 1
        except (ValueError, IndexError):
            pass
            
        for sub in container.sub_containers:
            self._update_counters_recursive(sub)
    
    def _validate_container_multiplicity(self, container_def: EcucContainerDef, parent: Optional[EcucContainerValue]) -> List[str]:
        """Validate container multiplicity constraints"""
        errors = []
        
        if parent:
            count = self._count_instances_in_parent(container_def, parent)
        else:
            count = sum(
                1 for c in self.configuration.containers
                if c.definition_ref == container_def.definition_ref
            )
        
        if count < container_def.lower_multiplicity:
            errors.append(
                f"{container_def.short_name}: Requires at least {container_def.lower_multiplicity} "
                f"instances, but only {count} exist"
            )
        
        if container_def.upper_multiplicity != -1 and count > container_def.upper_multiplicity:
            errors.append(
                f"{container_def.short_name}: Allows at most {container_def.upper_multiplicity} "
                f"instances, but {count} exist"
            )
        
        return errors
    
    def _validate_container_instance(self, container: EcucContainerValue) -> List[str]:
        """Validate a single container instance"""
        errors = []
        
        # Get definition
        container_def = self.get_container_def(container.definition_ref)
        if not container_def:
            errors.append(f"{container.short_name}: Definition not found")
            return errors
        
        # Validate required parameters
        for param_name, param_def in container_def.parameters.items():
            if param_def.is_required:
                if param_name not in container.parameter_values:
                    errors.append(f"{container.short_name}.{param_name}: Required parameter missing")
        
        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            errors.extend(self._validate_container_instance(sub_container))
        
        return errors
    
    def _find_references_to(self, target_container: EcucContainerValue) -> List[Tuple[EcucContainerValue, str]]:
        """Find all references pointing to a specific container
        
        This implements the TODO check: finds which containers reference the target,
        preventing deletion if any references exist.
        
        Args:
            target_container: Container to search references for
            
        Returns:
            List of tuples (source_container, reference_name) that reference the target
        """
        from .rules.reference_rules import ReferenceIntegrityRule
        return ReferenceIntegrityRule.find_references_to(target_container, self.configuration)
