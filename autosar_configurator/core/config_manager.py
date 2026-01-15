"""
Configuration Manager - Manages user-created configuration instances
Provides CRUD operations for container instances with validation
"""
from typing import Optional, List, Dict, Tuple, Any
from pathlib import Path
import os
from enum import Enum

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


class ProjectType(Enum):
    VECTOR = "Vector DaVinci"
    EB_TRESOS = "EB Tresos"
    UNKNOWN = "Unknown"


class ProjectTypeDetector:
    """Detects the type of AUTOSAR project (Vector vs EB)"""
    
    @staticmethod
    def detect(project_root: Path) -> ProjectType:
        """Detect project type based on marker files"""
        if not project_root.exists():
            return ProjectType.UNKNOWN
            
        # Check for Vector .dpa file
        if list(project_root.glob("*.dpa")):
            return ProjectType.VECTOR
            
        # Check for EB Tresos markers
        if (project_root / ".tresos").exists() or (project_root / ".project").exists():
            # Could check content of .project for tresos nature, but existence is a strong hint
            return ProjectType.EB_TRESOS
            
        return ProjectType.UNKNOWN


class ConfigLoader:
    """Helper to load Definitions and Configurations based on Project Type"""
    
    @staticmethod
    def get_def_search_paths(project_root: Path) -> List[Path]:
        """Get list of paths to search for ECUC-MODULE-DEF files"""
        paths = [project_root]
        
        project_type = ProjectTypeDetector.detect(project_root)
        
        if project_type == ProjectType.EB_TRESOS:
            # Add TRESOS_PLUGINS_PATH
            tresos_plugins = os.environ.get('TRESOS_PLUGINS_PATH')
            if tresos_plugins:
                plugin_path = Path(tresos_plugins)
                if plugin_path.exists():
                    paths.append(plugin_path)
                    # Also search inside subdirectories of plugins often
                    # But globbing handles that usually. 
                    # For now, just adding the root plugins path is a good step.
        
        return paths


class RecFileScanner:
    """Scanner for recommended configuration (*_rec.arxml) files"""
    
    @staticmethod
    def find_rec_files(project_root: Path) -> Dict[str, Path]:
        """Find all _rec.arxml files in project directory
        
        Args:
            project_root: Path to project root directory
            
        Returns:
            Dict mapping module name to rec file path
        """
        rec_files = {}
        
        # Search for *_rec.arxml files
        for rec_path in project_root.rglob("*_rec.arxml"):
            # Extract module name from filename
            # e.g., "CanNm_rec.arxml" -> "CanNm"
            filename = rec_path.stem  # e.g., "CanNm_rec"
            if filename.endswith("_rec"):
                module_name = filename[:-4]  # Remove "_rec" suffix
                rec_files[module_name] = rec_path
        
        return rec_files
    
    @staticmethod
    def find_rec_for_module(project_root: Path, module_name: str) -> Optional[Path]:
        """Find the rec file for a specific module
        
        Args:
            project_root: Path to project root directory
            module_name: Name of the module to find rec file for
            
        Returns:
            Path to rec file if found, None otherwise
        """
        # Try common patterns
        patterns = [
            f"{module_name}_rec.arxml",
            f"{module_name.lower()}_rec.arxml",
            f"{module_name}_Rec.arxml",
        ]
        
        for pattern in patterns:
            matches = list(project_root.rglob(pattern))
            if matches:
                return matches[0]
        
        return None


class DefFileScanner:
    """Scanner for module definition files (*.arxml, *.xdm)"""
    
    @staticmethod
    def find_def_files(search_paths: List[Path]) -> Dict[str, Path]:
        """Find all definition files in search paths
        
        Args:
            search_paths: List of paths to search (files or directories)
            
        Returns:
            Dict mapping module name (from filename) to file path
        """
        def_files = {}
        
        for search_path in search_paths:
            if not search_path.exists():
                continue
                
            if search_path.is_file():
                # Single file
                if search_path.suffix in ['.arxml', '.xdm']:
                    # Heuristic: filename is module name (e.g. Adc.xdm -> Adc)
                    module_name = search_path.stem
                    # Filter out config files (e.g. *_Config.arxml, *_rec.arxml)
                    if not module_name.endswith("_Config") and not module_name.endswith("_rec"):
                        def_files[module_name] = search_path
            else:
                # Directory search
                for ext in ['*.arxml', '*.xdm']:
                    for file_path in search_path.rglob(ext):
                        module_name = file_path.stem
                        # Filter out config/rec files
                        if not module_name.endswith("_Config") and not module_name.endswith("_rec"):
                            # Avoid duplicates (wins first found, but could optimize)
                            if module_name not in def_files:
                                def_files[module_name] = file_path
                                
        return def_files


class ConfigurationManager:
    """Manages ECUC configuration instances based on definitions"""
    
    def __init__(self, module_def: EcucModuleDef, project_context=None):
        """Initialize configuration manager
        
        Args:
            module_def: Module definition (template)
            project_context: Optional reference to WorkspaceProject
        """
        self.module_def = module_def
        self.project_context = project_context
        
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
            
        # Clean up outgoing references from this container tree (important for project-level reverse indexing)
        if self.project_context:
            self.project_context.unregister_container_references(instance)
            
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
                           value: Any):
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
                # Fuzzy string conversion (handle 'true'/'false' from ARXML)
                if isinstance(value, str):
                    val_lower = value.strip().lower()
                    if val_lower == 'true': value = 1
                    elif val_lower == 'false': value = 0
                
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
    
    def _validate_parameter_value(self, param_def: EcucParameterDef, value: Any):
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
        """Check if instance with name exists in the same scope (name must be unique among siblings)"""
        # Get siblings
        if parent:
            siblings = parent.sub_containers
        else:
            siblings = self.configuration.containers
            
        # Check for name match - AUTOSAR requires short_name to be unique within parent
        for sibling in siblings:
            if sibling.short_name == name:
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
        
        engine = ValidationEngine(self.module_def, self.configuration, project_context=self.project_context)
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
        # If we have a project context, use it for cross-module search
        if self.project_context:
            return self.project_context.find_global_references_to(target_container)
            
        from .rules.reference_rules import ReferenceIntegrityRule
        return ReferenceIntegrityRule.find_references_to(target_container, self.configuration)
    
    # ========== Recommended Values Support ==========
    
    def load_recommended_values(self, rec_file_path: Path) -> Optional['EcucModuleConfiguration']:
        """Load recommended values from a _rec.arxml file
        
        Args:
            rec_file_path: Path to the _rec.arxml file
            
        Returns:
            EcucModuleConfiguration with recommended values, or None if failed
        """
        from .parser.arxml_parser import ArxmlParser
        import lxml.etree as etree
        
        try:
            tree = etree.parse(str(rec_file_path))
            root = tree.getroot()
            
            # Find ECUC-MODULE-CONFIGURATION-VALUES (same structure as _ecuc.arxml)
            config_elem = root.find('.//{http://autosar.org/schema/r4.0}ECUC-MODULE-CONFIGURATION-VALUES')
            if config_elem is None:
                config_elem = root.find('.//ECUC-MODULE-CONFIGURATION-VALUES')
            
            if config_elem is None:
                return None
            
            parser = ArxmlParser()
            return parser.parse_ecuc_configuration_values(config_elem)
            
        except Exception as e:
            print(f"Warning: Failed to load recommended values from {rec_file_path}: {e}")
            return None
    
    def get_recommended_value_comparison(self, rec_config: 'EcucModuleConfiguration') -> List[Dict]:
        """Compare recommended values with current configuration
        
        Args:
            rec_config: Recommended configuration loaded from _rec.arxml
            
        Returns:
            List of dicts with 'param_path', 'current_value', 'recommended_value', 'differs'
        """
        comparisons = []
        
        def compare_container(current: EcucContainerValue, recommended: EcucContainerValue, path_prefix: str):
            for param_name, rec_param_obj in recommended.parameter_values.items():
                current_param_obj = current.parameter_values.get(param_name)
                
                # Extract actual values
                current_value = current_param_obj.value if current_param_obj else None
                rec_value = rec_param_obj.value
                
                param_path = f"{path_prefix}/{param_name}"
                
                comparisons.append({
                    'param_path': param_path,
                    'param_name': param_name,
                    'current_value': current_value,
                    'recommended_value': rec_value,
                    'differs': current_value != rec_value
                })
            
            # Recurse into sub-containers
            for rec_sub in recommended.sub_containers:
                # Find matching current sub-container by short_name
                current_sub = next(
                    (c for c in current.sub_containers if c.short_name == rec_sub.short_name),
                    None
                )
                if current_sub:
                    compare_container(current_sub, rec_sub, f"{path_prefix}/{rec_sub.short_name}")
        
        # Compare top-level containers
        for rec_container in rec_config.containers:
            current_container = next(
                (c for c in self.configuration.containers if c.short_name == rec_container.short_name),
                None
            )
            if current_container:
                compare_container(current_container, rec_container, rec_container.short_name)
        
        return comparisons
    
    def apply_recommended_values(self, rec_config: 'EcucModuleConfiguration', only_empty: bool = True) -> int:
        """Apply recommended values to current configuration
        
        Args:
            rec_config: Recommended configuration loaded from _rec.arxml
            only_empty: If True, only apply to parameters with no current value
            
        Returns:
            Number of parameters updated
        """
        updated_count = 0
        
        def apply_to_container(current: EcucContainerValue, recommended: EcucContainerValue):
            nonlocal updated_count
            
            for param_name, rec_param_obj in recommended.parameter_values.items():
                current_param_obj = current.parameter_values.get(param_name)
                
                current_value = current_param_obj.value if current_param_obj else None
                rec_value = rec_param_obj.value
                
                # Apply if: not only_empty, OR current value is None/empty
                should_apply = not only_empty or current_value is None or current_value == ""
                
                if should_apply and rec_value is not None:
                    # Pass the definition ref from the recommended value if available, or just empty string
                    # The configuration manager will ensure it's valid if we had full robust logic,
                    # but here we rely on existing mechanisms.
                    # Note: We need the definition_ref to create a new EcucParameterValue if one doesn't exist.
                    # Ideally we should look it up from definition.
                    # But for now, let's use the one from rec_value or try to find it.
                    
                    def_ref = rec_param_obj.definition_ref
                    current.set_parameter_value(param_name, rec_value, def_ref)
                    updated_count += 1
            
            # Recurse into sub-containers
            for rec_sub in recommended.sub_containers:
                current_sub = next(
                    (c for c in current.sub_containers if c.short_name == rec_sub.short_name),
                    None
                )
                if current_sub:
                    apply_to_container(current_sub, rec_sub)
        
        # Apply to top-level containers
        for rec_container in rec_config.containers:
            current_container = next(
                (c for c in self.configuration.containers if c.short_name == rec_container.short_name),
                None
            )
            if current_container:
                apply_to_container(current_container, rec_container)
        
        return updated_count
