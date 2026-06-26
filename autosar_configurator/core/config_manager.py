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

        # Check for .dpa file — but read stored metadata first, because EB imports
        # also save as .dpa with "project_type" set to "EB Tresos".  Extension-only
        # detection would wrongly reclassify those as Vector on re-open.
        dpa_files = list(project_root.glob("*.dpa"))
        if dpa_files:
            # Try to read the saved project_type from the first .dpa file found.
            stored_type = ProjectTypeDetector._read_stored_project_type(dpa_files[0])
            if stored_type is not None:
                return stored_type
            # Metadata absent or unreadable — fall back to extension heuristic.
            return ProjectType.VECTOR

        # Check for EB Tresos markers
        if (project_root / ".tresos").exists() or (project_root / ".project").exists():
            # Could check content of .project for tresos nature, but existence is a strong hint
            return ProjectType.EB_TRESOS

        return ProjectType.UNKNOWN

    @staticmethod
    def _read_stored_project_type(dpa_path: Path) -> Optional['ProjectType']:
        """Read the project_type field saved inside a .dpa JSON file.

        Returns the matching ProjectType if the field is present and recognised,
        or None if the file cannot be read or the field is missing.
        """
        import json
        try:
            with open(dpa_path, 'r', encoding='utf-8') as f:
                data = json.load(f)
            raw = data.get("project_type", "")
            if not isinstance(raw, str):
                return None
            raw_lower = raw.lower()
            if "eb" in raw_lower or "tresos" in raw_lower:
                return ProjectType.EB_TRESOS
            if "vector" in raw_lower or "davinci" in raw_lower:
                return ProjectType.VECTOR
            return None
        except Exception:
            return None


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


class EpcFileScanner:
    """Scanner for EPC configuration files (*.epc) in EB Tresos output directories"""

    @staticmethod
    def find_epc_files(project_root: Path, chip_name: Optional[str] = None) -> Dict[str, Path]:
        """Find all .epc files, return dict: module_name -> epc_path

        Search order:
        1. Config/{chip_name}/output/*.epc (if chip_name given)
        2. Config/*/output/*.epc (auto-detect)
        3. project_root/**/*.epc (fallback)
        """
        epc_files = {}

        # Strategy 1: specific chip directory
        if chip_name:
            chip_output = project_root / "Config" / chip_name / "output"
            if chip_output.exists():
                for epc_path in chip_output.glob("*.epc"):
                    module_name = epc_path.stem
                    epc_files[module_name] = epc_path
                if epc_files:
                    return epc_files

        # Strategy 2: auto-detect from Config/*/output/
        config_dir = project_root / "Config"
        if config_dir.exists():
            for chip_dir in sorted(config_dir.iterdir()):
                output_dir = chip_dir / "output"
                if output_dir.exists():
                    for epc_path in output_dir.glob("*.epc"):
                        module_name = epc_path.stem
                        if module_name not in epc_files:
                            epc_files[module_name] = epc_path
            if epc_files:
                return epc_files

        # Strategy 3: fallback recursive search
        for epc_path in project_root.rglob("*.epc"):
            module_name = epc_path.stem
            if module_name not in epc_files:
                epc_files[module_name] = epc_path

        # Strategy 4: fallback to *_Config.arxml (native XDM configurations)
        for arxml_path in project_root.rglob("*_Config.arxml"):
            module_name = arxml_path.stem.replace("_Config", "")
            if module_name not in epc_files:
                epc_files[module_name] = arxml_path

        return epc_files

    @staticmethod
    def detect_available_chips(project_root: Path) -> List[str]:
        """Detect available chips from Config/ subdirectories"""
        chips = []
        config_dir = project_root / "Config"
        if config_dir.exists():
            for chip_dir in sorted(config_dir.iterdir()):
                if chip_dir.is_dir() and (chip_dir / "output").exists():
                    chips.append(chip_dir.name)
        return chips


class ConfigurationManager:
    """Manages ECUC configuration instances based on definitions"""
    
    def __init__(self, module_def: EcucModuleDef, project_context=None, def_missing: bool = False):
        """Initialize configuration manager
        
        Args:
            module_def: Module definition (template)
            project_context: Optional reference to WorkspaceProject
            def_missing: True if the definition file was missing and this is a stub
        """
        self.module_def = module_def
        self.project_context = project_context
        self.def_missing = def_missing
        
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
        
        # Note: lower_multiplicity check is skipped to give users more flexibility
        # Validation will warn about missing required instances separately
        
        
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
        
        Note:
            Multiplicity validation should be performed by the caller before invoking this method.
            For paste operations, use _check_multiplicity_before_add() beforehand.
            For undo operations, the previous state is assumed valid.
        """
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
                    lower_val = value.lower()
                    if lower_val in ('true', '1', 'yes'):
                        value = True
                    elif lower_val in ('false', '0', 'no'):
                        value = False
                    else:
                        raise ValidationError(
                            f"{param_name}: invalid boolean string '{value}', "
                            f"expected one of: true/false, 1/0, yes/no"
                        )
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
        if not definition_ref:
            return None

        # Check if it's a relative path (doesn't start with /)
        if not definition_ref.startswith('/'):
            return self.module_def.get_container_def(definition_ref)

        # Parse absolute path: /PackageName/ModuleName/ContainerPath...
        parts = definition_ref.split('/')
        if len(parts) < 3:  # Minimum: ['', 'Package', 'Module']
            return None

        # Try to find module name in path and extract container path
        module_name = self.module_def.short_name
        try:
            module_idx = parts.index(module_name)
            # Container path is everything after module name
            relative_path = '/'.join(parts[module_idx + 1:])
            if relative_path:
                return self.module_def.get_container_def(relative_path)
        except ValueError:
            # Module name not found in path
            pass

        # Fallback: assume format /Package/Module/Container...
        # Take parts after position 2 (skip '', PackageName, ModuleName)
        if len(parts) >= 4:
            relative_path = '/'.join(parts[3:])
            if relative_path:
                return self.module_def.get_container_def(relative_path)

        return None
    
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
        """Get and increment the instance counter for container_name."""
        idx = self._instance_counters.get(container_name, 0)
        self._instance_counters[container_name] = idx + 1
        return idx
    
    def add_custom_rule_file(self, file_path: Path):
        """Add a custom rule file"""
        if file_path not in self.custom_rule_files:
            self.custom_rule_files.append(file_path)

    def validate_configuration(self) -> 'ValidationResult':
        """Validate current configuration"""
        from .validation_engine import ValidationEngine, ValidationResult, ValidationMessage, ValidationSeverity

        # When the definition file is missing we have no schema to validate against.
        # Running type/range/multiplicity rules would produce hundreds of false
        # "Container definition not found" errors – one per config container.
        # Instead, emit a single warning and skip deep structural validation.
        if self.def_missing:
            result = ValidationResult()
            result.add_message(ValidationMessage(
                severity=ValidationSeverity.WARNING,
                message=(
                    f"Module definition file not found for '{self.module_def.short_name}'. "
                    f"Type, range and multiplicity validation skipped. "
                    f"Please add the corresponding .xdm / .arxml definition file to the project."
                ),
                rule_name="ValidationEngine"
            ))
            return result

        engine = ValidationEngine(self.module_def, self.configuration, project_context=self.project_context)
        engine.register_default_rules()

        failed_rules = []
        # Load custom rules
        for rule_file in self.custom_rule_files:
            try:
                engine.load_custom_rules(rule_file)
            except Exception as e:
                import logging
                logging.getLogger(__name__).warning(
                    f"Failed to load custom rules from {rule_file}: {e}"
                )
                failed_rules.append((rule_file, e))

        result = engine.validate()
        for rule_file, e in failed_rules:
            result.add_message(ValidationMessage(
                severity=ValidationSeverity.WARNING,
                message=f"Custom rule file '{rule_file}' failed to load: {e}. "
                        f"Constraints defined in this file were NOT checked.",
                rule_name="CustomRuleLoader"
            ))
        return result

    def _rebuild_instance_registry(self):
        """Rebuild the instance registry after structural changes (rename/move)."""
        self.configuration._instance_registry.clear()
        for container in self.configuration.containers:
            self.configuration._register_instance(container)

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
        
    def load_configuration(self, file_path: Path, skip_cleanup: bool = False):
        """Load configuration from ARXML file
        
        Args:
            file_path: Input file path
            skip_cleanup: If True, skip cleaning up parameters that don't match the definition
                          (useful when the definition file is missing or a stub)
        """
        from .parser.arxml_parser import ArxmlParser
        from .parser.xdm_config_parser import XdmConfigParser
        import lxml.etree as etree
        
        parser = ArxmlParser()
        new_config = None
        
        try:
            _xml_parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(str(file_path), _xml_parser)
            root = tree.getroot()

            # Find ECUC-MODULE-CONFIGURATION-VALUES
            namespaces = {'ar': 'http://autosar.org/schema/r4.0'}
            config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', namespaces)
            if config_elem is None:
                config_elem = root.find('.//ECUC-MODULE-CONFIGURATION-VALUES')
                
            if config_elem is not None:
                new_config = parser.parse_ecuc_configuration_values(config_elem)
                if new_config:
                    ar_package = config_elem.getparent()
                    if ar_package is not None:
                        ar_package = ar_package.getparent()
                    if ar_package is not None:
                        pkg_sn = ar_package.find('{http://autosar.org/schema/r4.0}SHORT-NAME')
                        if pkg_sn is None:
                            pkg_sn = ar_package.find('SHORT-NAME')
                        if pkg_sn is not None and pkg_sn.text:
                            new_config.package_name = pkg_sn.text
            else:
                # Fallback to XDM config parser if no standard ARXML element found
                xdm_parser = XdmConfigParser()
                new_config = xdm_parser.parse_file(file_path)
                if not new_config:
                    raise ValueError("No standard configuration or valid XDM configuration found in file")

            if new_config:
                self.configuration = new_config
                # Reset counters
                self._instance_counters.clear()
                # Rebuild counters based on loaded configuration
                for container in self.configuration.containers:
                    self._update_counters_recursive(container)

                # Normalize definition_refs: EB Tresos exports sometimes use
                # instance short names in DEFINITION-REF instead of definition
                # container names.  Fix them before cleanup runs.
                if self.module_def and not skip_cleanup:
                    self._normalize_definition_refs()

                # Clean up invalid parameters (parameters in wrong container level)
                # Skip if requested (e.g. for stub modules where definition is empty)
                if self.module_def and not skip_cleanup:
                    cleanup_count = self._cleanup_invalid_parameters()
                    if cleanup_count > 0:
                        print(f"[ConfigManager] Preserved {cleanup_count} unrecognised parameter(s) in unknown_parameters (not deleted)")

                # Mark as saved (just loaded, no modifications)
                self.configuration.mark_saved()
                    
        except Exception as e:
            raise ValueError(f"Failed to load configuration: {e}")

    def _cleanup_invalid_parameters(self) -> int:
        """Identify parameters that don't belong to their container definition.

        Parameters are NOT deleted — they are moved to container.unknown_parameters
        so callers can present a warning in the UI without causing data loss.
        This handles cases where configuration files have parameters stored at the
        wrong container level (e.g., from import or older versions).

        Returns:
            Number of unrecognised parameters preserved in unknown_parameters
        """
        total_preserved = 0

        def cleanup_container(container: EcucContainerValue) -> int:
            preserved = 0
            container_def = self.get_container_def(container.definition_ref)

            if container_def:
                # Find parameters that don't exist in the container definition.
                # We warn but DO NOT delete: the DEF may be incomplete (stub, partial
                # import, wrong path) and silently dropping values would cause
                # irreversible data loss.  Callers can inspect container.unknown_parameters
                # to decide whether to present a warning in the UI.
                for param_name in list(container.parameter_values.keys()):
                    if param_name not in container_def.parameters:
                        if not hasattr(container, 'unknown_parameters'):
                            container.unknown_parameters = {}
                        container.unknown_parameters[param_name] = container.parameter_values[param_name]
                        preserved += 1
                        print(f"  - Warning: '{param_name}' in '{container.short_name}' is not in DEF '{container_def.short_name}' — preserved in unknown_parameters (not deleted)")

                # Same preservation guarantee for multi-valued parameters.
                for param_name in list(container.multi_parameter_values.keys()):
                    if param_name not in container_def.parameters:
                        if not hasattr(container, 'unknown_parameters'):
                            container.unknown_parameters = {}
                        container.unknown_parameters[f'{param_name}[multi]'] = container.multi_parameter_values[param_name]
                        preserved += 1
                        print(f"  - Warning: multi-param '{param_name}' in '{container.short_name}' is not in DEF '{container_def.short_name}' — preserved in unknown_parameters (not deleted)")

            # Recursively process sub-containers
            for sub in container.sub_containers:
                preserved += cleanup_container(sub)

            return preserved

        for container in self.configuration.containers:
            total_preserved += cleanup_container(container)

        return total_preserved

    def _normalize_definition_refs(self):
        """Normalize definition_refs that use instance names instead of definition names.

        EB Tresos exports sometimes produce DEFINITION-REF values like
        ``/THA6_ASR21/Os/OsCounter_Software`` where ``OsCounter_Software`` is
        the *instance* short-name rather than the *definition* container name
        (``OsCounter``).  This method remaps them to the correct definition
        path after the config is loaded.

        Strategy (applied at each hierarchy level):
        1. If the definition_ref already resolves → keep it.
        2. **Parameter-signature match**: score each candidate definition by
           how many of the container's parameter names appear in it.
        3. **Longest prefix match**: pick the definition whose short_name is
           the longest prefix of the instance name.
        """
        # Extract the definition_ref prefix (everything up to and including the
        # module name).  E.g. for ``/THA6_ASR21/Os/Foo`` the prefix is
        # ``/THA6_ASR21/Os``.
        module_name = self.module_def.short_name

        def _extract_prefix(def_ref: str) -> str:
            """Return the prefix portion of a definition_ref up to and including the module name."""
            parts = def_ref.split('/')
            try:
                idx = parts.index(module_name)
                return '/'.join(parts[:idx + 1])
            except ValueError:
                # Fallback: use first 3 segments
                if len(parts) >= 3:
                    return '/'.join(parts[:3])
                return '/'.join(parts)

        def _best_match_def(container, candidate_defs: dict) -> Optional[EcucContainerDef]:
            """Find the best matching definition for *container* among *candidate_defs*.

            Returns the matching EcucContainerDef, or None.
            """
            if not candidate_defs:
                return None

            param_names = set(container.parameter_values.keys())
            sub_names = {s.short_name for s in container.sub_containers}
            instance_name = container.short_name

            best_def = None
            best_score = -1

            for def_name, cdef in candidate_defs.items():
                score = 0
                # Parameter overlap score
                if param_names:
                    overlap = param_names & set(cdef.parameters.keys())
                    score += len(overlap) * 2  # weight parameter matches
                # Sub-container overlap score
                if sub_names:
                    sub_overlap = sub_names & set(cdef.sub_containers.keys())
                    score += len(sub_overlap)
                # Prefix bonus: definition name is a prefix of instance name
                if instance_name.startswith(def_name):
                    score += len(def_name)

                if score > best_score:
                    best_score = score
                    best_def = cdef

            # Require at least some evidence of a match
            if best_score > 0:
                return best_def
            return None

        def _normalize_container(container, parent_def: Optional[EcucContainerDef],
                                parent_normalized_ref: Optional[str] = None):
            """Normalize a single container and its sub-containers recursively.

            Args:
                container: The container value to normalize.
                parent_def: The EcucContainerDef of the parent (or None for top-level).
                parent_normalized_ref: The already-corrected definition_ref of the
                    PARENT container (or None for top-level).  Used to build
                    sub-container refs when the parent name was also remapped.
            """
            # Determine the pool of candidate definitions at this level
            if parent_def is not None:
                candidate_defs = parent_def.sub_containers
            else:
                candidate_defs = self.module_def.containers

            # Check if current definition_ref already resolves
            resolved_def = self.get_container_def(container.definition_ref)
            if resolved_def is not None:
                # Already valid – recurse into sub-containers using this container's ref
                for sub in container.sub_containers:
                    _normalize_container(sub, resolved_def, container.definition_ref)
                return

            # Try to find the correct definition
            matched_def = _best_match_def(container, candidate_defs)
            if matched_def is not None:
                # Build the correct definition_ref.
                # If the parent was also remapped we must use the already-corrected
                # parent ref as the base, not the stale parent name that is still
                # baked into container.definition_ref.
                if parent_normalized_ref is not None:
                    # Sub-container: base off the normalized parent ref
                    new_ref = parent_normalized_ref + '/' + matched_def.short_name
                elif parent_def is not None:
                    # Sub-container: parent was valid, just replace last segment
                    parts = container.definition_ref.rsplit('/', 1)
                    new_ref = parts[0] + '/' + matched_def.short_name
                else:
                    # Top-level container
                    prefix = _extract_prefix(container.definition_ref)
                    new_ref = prefix + '/' + matched_def.short_name
                container.definition_ref = new_ref

                # Also fix parameter definition_refs
                for param_name, param_val in container.parameter_values.items():
                    param_val.definition_ref = new_ref + '/' + param_name
                for ref_name, ref_val in container.reference_values.items():
                    ref_val.definition_ref = new_ref + '/' + ref_name

                # Recurse with matched definition context, passing the new ref
                for sub in container.sub_containers:
                    _normalize_container(sub, matched_def, new_ref)
            else:
                # Could not match – recurse anyway (sub-containers might still match)
                for sub in container.sub_containers:
                    _normalize_container(sub, None, None)

        for container in self.configuration.containers:
            _normalize_container(container, None)

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
            _xml_parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(str(rec_file_path), _xml_parser)
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
