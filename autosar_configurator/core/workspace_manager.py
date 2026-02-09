"""
Workspace Manager
Manages the overall project workspace, including multiple BSW module configurations.
"""
import json
from typing import Dict, List, Optional
from pathlib import Path

from .config_manager import ConfigurationManager
from .model.definition_model import EcucModuleDef
from .parser.ecuc_def_parser import EcucDefParser

class WorkspaceProject:
    """Represents a DaVinci-style project containing multiple modules"""
    
    def __init__(self, name: str, path: Optional[Path] = None):
        self.name = name
        self.path = path
        # Map module name to its manager
        self.module_managers: Dict[str, ConfigurationManager] = {}
        # Map module name to its definition file path (for reloading)
        self.module_defs: Dict[str, Path] = {}
        
        # Project type (Vector or EB)
        from .config_manager import ProjectType
        self.project_type: ProjectType = ProjectType.VECTOR
        
        # Definition search paths (for EB projects with external plugins)
        self.def_search_paths: List[Path] = []
        
        # Variant Management
        self.variants: List[str] = ["Default"]  # Always have at least Default variant
        self.active_variant: Optional[str] = "Default"  # Currently selected variant
        
        # Metadata
        from datetime import datetime
        self.created_date: str = datetime.now().isoformat()
        self.author: str = ""
        self.description: str = ""
        self.version: str = "1.0.0"
        
        # Cross-module dependency rules (cached results from analysis)
        self.dependency_rules: List[Dict] = []
        
        # Chip/Variant Selection (for projects with multiple chip .properties files)
        self.available_chips: List[str] = []  # Discovered chip variants from .properties
        self.selected_chip: Optional[str] = None  # User's selected chip
    
    def discover_available_chips(self) -> List[str]:
        """Scan project for available chip .properties files.
        
        Looks in Def/plugins/*/resource/*.properties for chip definition files.
        Returns list of chip names (derived from filename).
        """
        if not self.path:
            return []
        
        # self.path is the .dpa file path, so project_dir is its parent
        project_dir = self.path.parent if self.path.is_file() else self.path
        
        chips = []
        def_dir = project_dir / "Def" / "plugins"
        if def_dir.exists():
            # Look for resource/*.properties files
            for props_file in def_dir.rglob("resource/*.properties"):
                # Extract chip name from filename (e.g., CotexR52_THA6206_LFBGA292.properties -> THA6206_LFBGA292)
                name = props_file.stem
                # Try to extract chip identifier (THAxxxx pattern)
                parts = name.split('_')
                for i, part in enumerate(parts):
                    if part.startswith('THA') or part.startswith('tha'):
                        chip_name = '_'.join(parts[i:])
                        chips.append(chip_name)
                        break
                else:
                    # If no THA pattern, use the full stem
                    chips.append(name)
        
        self.available_chips = sorted(set(chips))
        return self.available_chips


    
    def ensure_default_variant(self):
        """Ensure Default variant exists for all modules
        
        Called when loading projects or adding modules to ensure
        the Default variant is properly initialized.
        """
        for name, manager in self.module_managers.items():
            config = manager.configuration
            if "Default" not in config.variant_overrides:
                config.variant_overrides["Default"] = {}
        
        # Ensure Default is in variants list
        if "Default" not in self.variants:
            self.variants.insert(0, "Default")
        
        # Set active variant to Default if not set
        if not self.active_variant:
            self.active_variant = "Default"
    
    def _copy_container_to_base(self, container, base_dict: dict):
        """Recursively copy container parameter values to Base dict"""
        for param_name, param_val in container.parameter_values.items():
            param_path = f"{container.get_path()}.{param_name}"
            base_dict[param_path] = param_val.value
        
        for sub in container.sub_containers:
            self._copy_container_to_base(sub, base_dict)
        
    def add_module(self, module_def: EcucModuleDef, def_path: Path, def_missing: bool = False) -> ConfigurationManager:
        """Add a new module to the project"""
        if module_def.short_name in self.module_managers:
            raise ValueError(f"Module {module_def.short_name} already exists in project")
            
        manager = ConfigurationManager(module_def, project_context=self, def_missing=def_missing)
        self.module_managers[module_def.short_name] = manager
        self.module_defs[module_def.short_name] = def_path
        return manager
        
    def remove_module(self, module_name: str):
        """Remove a module from the project"""
        if module_name in self.module_managers:
            del self.module_managers[module_name]
            del self.module_defs[module_name]

    def get_manager(self, module_name: str) -> Optional[ConfigurationManager]:
        return self.module_managers.get(module_name)
        
    def get_all_managers(self) -> List[ConfigurationManager]:
        return list(self.module_managers.values())
    
    def get_instance_by_path(self, path: str) -> Optional['EcucContainerValue']:
        """Get container instance by its full path from any module
        
        EMF-style global resolver: enables cross-module reference resolution.
        Supports multiple path formats:
        - Module-aware paths: /Adc/AdcConfigSet
        - Legacy /Config paths: /Config/AdcConfigSet
        - EB Tresos paths: /Adc_Config/Adc/AdcConfigSet (config file prefix)
        """
        from .model.configuration_model import EcucContainerValue
        
        # 1. Try exact match (best for module-aware paths)
        for manager in self.module_managers.values():
            config = manager.configuration
            instance = config.get_instance_by_path(path)
            if instance is not None:
                return instance
        
        # 2. Fallback for legacy /Config/ paths
        if path.startswith("/Config/"):
            suffix = path[8:]  # Remove "/Config/"
            for module_name, manager in self.module_managers.items():
                alt_path = f"/{module_name}/{suffix}"
                instance = manager.configuration.get_instance_by_path(alt_path)
                if instance is not None:
                    return instance
        
        # 3. Fallback for EB Tresos paths: /ModuleName_Config/ModuleName/Container...
        # Pattern: /{prefix}/{module_name}/... where prefix ends with _Config
        parts = path.split('/')
        if len(parts) >= 3 and parts[0] == '':
            prefix = parts[1]  # e.g., "I2c_Config"
            module_name = parts[2]  # e.g., "I2c"
            
            # Check if it matches the EB pattern (prefix_Config/prefix/...)
            if prefix.endswith('_Config') or prefix.endswith('_Values'):
                # Try stripping the config file prefix
                suffix = '/'.join(parts[2:])  # e.g., "I2c/I2cGlobalConfig/I2cChannel_0"
                for mgr_name, manager in self.module_managers.items():
                    alt_path = f"/{suffix}"
                    instance = manager.configuration.get_instance_by_path(alt_path)
                    if instance is not None:
                        return instance
            
            # Also try if module_name matches a loaded module, search with remaining path
            if module_name in self.module_managers:
                # Try with just module_name + rest of path
                rest_path = '/' + '/'.join(parts[2:])  # e.g., "/I2c/I2cGlobalConfig/I2cChannel_0"
                instance = self.module_managers[module_name].configuration.get_instance_by_path(rest_path)
                if instance is not None:
                    return instance
        
        return None

    
    def resolve_all_references(self) -> tuple:
        """Resolve all cross-module references in all loaded configurations
        
        EMF-style reference resolution: converts string paths to object pointers
        across all modules in the project.
        
        Returns:
            Tuple of (total_resolved, total_errors)
        """
        total_resolved = 0
        total_errors = 0
        
        for manager in self.module_managers.values():
            resolved, errors = manager.configuration.resolve_references(self.get_instance_by_path)
            total_resolved += resolved
            total_errors += errors
        
        return total_resolved, total_errors
    
    def get_all_resolution_errors(self) -> list:
        """Get all resolution errors across all modules
        
        Returns:
            List of ResolutionError objects for UI/AI display
        """
        all_errors = []
        for manager in self.module_managers.values():
            all_errors.extend(manager.configuration.get_resolution_errors())
        return all_errors
    
    def build_reverse_reference_index(self) -> int:
        """Build reverse reference index: populate 'referenced_by' on each container
        
        For each resolved reference, add the reference to the target's 'referenced_by' list.
        This enables queries like "who references this container?"
        
        Must be called AFTER resolve_all_references().
        
        Returns:
            Number of reverse references indexed
        """
        indexed_count = 0
        
        # First, clear all existing referenced_by lists to avoid stale entries
        def clear_referenced_by(container):
            container.referenced_by.clear()
            for sub in container.sub_containers:
                clear_referenced_by(sub)
        
        for manager in self.module_managers.values():
            for container in manager.configuration.containers:
                clear_referenced_by(container)
        
        # Now build fresh index
        def process_container(container):
            nonlocal indexed_count
            
            for ref_name, ref_value in container.reference_values.items():
                # Only process resolved references with valid target
                if ref_value.is_resolved and ref_value.target is not None:
                    # Add this reference to the target's referenced_by list
                    if ref_value not in ref_value.target.referenced_by:
                        ref_value.target.referenced_by.append(ref_value)
                        indexed_count += 1
            
            # Recurse into sub-containers
            for sub in container.sub_containers:
                process_container(sub)
        
        # Process all containers in all modules
        for manager in self.module_managers.values():
            for container in manager.configuration.containers:
                process_container(container)
        
        return indexed_count

    def find_global_references_to(self, target_container: 'EcucContainerValue') -> List[tuple]:
        """Find all references pointing to a specific container across ALL modules
        
        Args:
            target_container: Container to search references for
            
        Returns:
            List of tuples (source_container, reference_name)
        """
        target_path = target_container.get_path()
        references = []
        
        from .rules.reference_rules import ReferenceIntegrityRule
        for manager in self.module_managers.values():
            refs = ReferenceIntegrityRule.find_references_to(target_container, manager.configuration)
            references.extend(refs)
            
        return references



    def register_container_references(self, container: 'EcucContainerValue'):
        """Recursively register all references in a container tree to their targets' referenced_by list"""
        for ref_name, ref_value in container.reference_values.items():
            if ref_value.is_resolved and ref_value.target is not None:
                if ref_value not in ref_value.target.referenced_by:
                    ref_value.target.referenced_by.append(ref_value)
        
        for sub in container.sub_containers:
            self.register_container_references(sub)

    def unregister_container_references(self, container: 'EcucContainerValue'):
        """Recursively remove all references in a container tree from their targets' referenced_by list"""
        for ref_name, ref_value in container.reference_values.items():
            if ref_value.is_resolved and ref_value.target is not None:
                if ref_value in ref_value.target.referenced_by:
                    ref_value.target.referenced_by.remove(ref_value)
        
        for sub in container.sub_containers:
            self.unregister_container_references(sub)


class WorkspaceManager:
    """Manages the active project and workspace operations"""
    
    def __init__(self):
        self.current_project: Optional[WorkspaceProject] = None
        self.def_parser = EcucDefParser()
        
    def create_project(self, name: str, path: Path) -> WorkspaceProject:
        """Create a new empty project"""
        self.current_project = WorkspaceProject(name, path)
        return self.current_project
        
    def close_project(self):
        """Close current project"""
        self.current_project = None
        
    def save_project(self):
        """Save current project to file"""
        if not self.current_project or not self.current_project.path:
            return
        
        from datetime import datetime
        
        data = {
            "format_version": 6,  # Bumped version: removed has_base, use Default variant
            "tool_version": "1.0.0",
            "project_type": self.current_project.project_type.value,
            "name": self.current_project.name,
            "created": self.current_project.created_date,
            "last_modified": datetime.now().isoformat(),
            "author": getattr(self.current_project, 'author', ''),
            "description": getattr(self.current_project, 'description', ''),
            "version": getattr(self.current_project, 'version', '1.0.0'),
            "def_search_paths": [str(p) for p in self.current_project.def_search_paths],
            "variants": self.current_project.variants,
            "active_variant": self.current_project.active_variant,
            "dependency_rules": self.current_project.dependency_rules,
            "available_chips": self.current_project.available_chips,
            "selected_chip": self.current_project.selected_chip,
            "modules": []
        }
        
        # Save each module
        project_dir = self.current_project.path.parent
        config_value_dir = project_dir / "ConfigValue"
        config_value_dir.mkdir(exist_ok=True)
        
        for name, manager in self.current_project.module_managers.items():
            # Determine paths
            def_path = self.current_project.module_defs[name]
            
            # Module config is saved in ConfigValue folder
            config_filename = f"{name}_Config.arxml"
            # Use Path for cross-platform compatibility (converts to correct separator)
            relative_config_path = str(Path("ConfigValue") / config_filename)
            config_path = project_dir / "ConfigValue" / config_filename
            
            # Save the actual config content
            manager.save_configuration(config_path)
            
            # Try to make def_path relative to project root for better portability
            try:
                # project_dir is already defined as current_project.path.parent
                save_def_path = str(def_path.relative_to(project_dir))
            except (ValueError, AttributeError):
                save_def_path = str(def_path)
            
            # Record in project file
            data["modules"].append({
                "name": name,
                "def_path": save_def_path,
                "config_path": relative_config_path,
                "variant_overrides": manager.configuration.variant_overrides
            })
            
        # Write project file
        with open(self.current_project.path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)
            
    def _resolve_path(self, path_str: str, project_dir: Path) -> Path:
        """Robustly resolve paths that might be relative or absolute from another platform"""
        import re
        
        # 1. Normalize separators
        norm_str = path_str.replace('\\', '/')
        
        # 2. Check for Windows absolute path (e.g., C:/...) ON NON-WINDOWS
        # If it's a Windows-style absolute path but we are on a system where it's not absolute
        if re.match(r'^[a-zA-Z]:/', norm_str):
            parts = norm_str.split('/')
            
            # Try to resolve relative to current project root
            # Look for common anchor points: project name or standard BSW folders
            project_name = project_dir.name
            anchors = [project_name, 'Def', 'plugins', 'ConfigValue', 'autosar']
            
            for anchor in anchors:
                if anchor in parts:
                    idx = parts.index(anchor)
                    # For project_name, use everything AFTER it
                    # For others, use everything FROM it (inclusive)
                    rel_parts = parts[idx+1:] if anchor == project_name else parts[idx:]
                    potential_path = project_dir.joinpath(*rel_parts)
                    if potential_path.exists():
                        return potential_path
            
            # If no anchor found or file doesn't exist, just return it as a Path object
            # It will likely fail exists() check later, allowing it to be handled gracefully
            return Path(norm_str)
            
        # 3. Handle normal paths (both absolute and relative)
        p = Path(norm_str)
        if p.is_absolute():
            return p
        return project_dir / p

    def load_project(self, project_path: Path) -> tuple[WorkspaceProject, list]:
        """Load project from file
        
        Returns:
            tuple: (project, failed_modules list)
            failed_modules: List of tuples (module_name, error_message)
        """
        with open(project_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        # Check format version (Current version is 6, removed has_base)
        format_version = data.get("format_version", 0)
        if format_version > 6:
            raise ValueError(
                f"Unsupported project format version {format_version}. "
                f"Please upgrade the tool."
            )
        
        project_name = data.get("name", "Untitled")
        project = WorkspaceProject(project_name, project_path)
        
        # Store metadata
        from datetime import datetime
        from .config_manager import ProjectType
        
        project.created_date = data.get("created", datetime.now().isoformat())
        project.author = data.get("author", "")
        project.description = data.get("description", "")
        project.version = data.get("version", "1.0.0")
        
        # Load project type (new in format v2)
        project_type_str = data.get("project_type", "Vector DaVinci")
        for pt in ProjectType:
            if pt.value == project_type_str:
                project.project_type = pt
                break
        
        # Load def search paths
        project.def_search_paths = [Path(p) for p in data.get("def_search_paths", [])]
        
        # Load variants with backward compatibility
        loaded_variants = data.get("variants", [])
        loaded_active = data.get("active_variant", None)
        
        # Migrate old projects: ensure Default variant exists
        if not loaded_variants:
            # Old project with no variants - create Default
            project.variants = ["Default"]
            project.active_variant = "Default"
        elif "Base" in loaded_variants and "Default" not in loaded_variants:
            # Old project with Base - rename Base to Default
            project.variants = ["Default" if v == "Base" else v for v in loaded_variants]
            project.active_variant = "Default" if loaded_active == "Base" else (loaded_active or "Default")
        else:
            project.variants = loaded_variants if "Default" in loaded_variants else ["Default"] + loaded_variants
            project.active_variant = loaded_active or "Default"
        
        # Ignore has_base from old projects (no longer used)
        # data.get("has_base", False) - deprecated
        
        # Load dependency rules (new in format v4)
        project.dependency_rules = data.get("dependency_rules", [])
        if project.dependency_rules:
            print(f"Loaded {len(project.dependency_rules)} confirmed dependency rules")
        
        # Load chip selection (new in format v7)
        project.available_chips = data.get("available_chips", [])
        project.selected_chip = data.get("selected_chip", None)
        
        # If no available chips in file, try to discover them
        if not project.available_chips:
            project.path = project_path  # Ensure path is set before discovery
            project.discover_available_chips()

        
        project_dir = project_path.parent
        failed_modules = []
        
        for module_data in data.get("modules", []):
            name = module_data["name"]
            def_path_str = module_data["def_path"]
            config_path_str = module_data["config_path"]
            
            # Resolve paths robustly (handles cross-platform absolute paths)
            def_path = self._resolve_path(def_path_str, project_dir)
            config_path = self._resolve_path(config_path_str, project_dir)
            
            # Fallback for legacy projects (files in project root)
            # Check for both / and \ for cross-platform compatibility
            has_separator = "/" in config_path_str or "\\" in config_path_str
            if not config_path.exists() and not has_separator:
                legacy_path = project_dir / Path(config_path_str).name
                if legacy_path.exists():
                    config_path = legacy_path
                    print(f"Loading legacy config location: {config_path}")
            # Extended fallback: if ConfigValue is missing but file is in root
            # Check for both ConfigValue/ and ConfigValue\ for cross-platform compatibility
            elif not config_path.exists() and ("ConfigValue/" in config_path_str or "ConfigValue\\" in config_path_str):
                legacy_path = project_dir / Path(config_path_str).name
                if legacy_path.exists():
                    config_path = legacy_path
                    print(f"Fallback to legacy config location: {config_path}")
            
            if def_path.exists():
                try:
                    # Load definition
                    module_def = self.def_parser.parse_module_def_file(def_path)
                    
                    # Create manager
                    manager = project.add_module(module_def, def_path)
                    
                    # Load configuration if exists
                    if config_path.exists():
                        manager.load_configuration(config_path)
                    
                    # Restore variant overrides if saved
                    if "variant_overrides" in module_data:
                        manager.configuration.variant_overrides = module_data["variant_overrides"]
                        
                except Exception as e:
                    error_msg = f"Failed to load: {str(e)}"
                    failed_modules.append((name, error_msg))
                    print(f"Failed to load module {name}: {e}")
            else:
                # Stub load: Create a surrogate module definition so we can still see the values
                try:
                    from .model.definition_model import EcucModuleDef
                    # Try to infer correct definition_ref if possible, or use standard pattern
                    module_def = EcucModuleDef(
                        short_name=name, 
                        definition_ref=f"/AUTOSAR/EcucDefs/{name}"
                    )
                    
                    # Create manager with def_missing=True
                    manager = project.add_module(module_def, def_path, def_missing=True)
                    
                    # Load configuration if exists (skip cleanup since def is a stub)
                    if config_path.exists():
                        manager.load_configuration(config_path, skip_cleanup=True)
                    
                    # Restore variant overrides if saved
                    if "variant_overrides" in module_data:
                        manager.configuration.variant_overrides = module_data["variant_overrides"]
                    
                    print(f"Loaded module {name} with stub definition (DEF file missing)")
                    
                except Exception as e:
                    error_msg = f"Failed to load stub: {str(e)}"
                    failed_modules.append((name, error_msg))
                    print(f"Failed to load stub module {name}: {e}")
        
        # EMF-style reference resolution: resolve cross-module references
        try:
            resolved_count, error_count = project.resolve_all_references()
            if resolved_count > 0:
                print(f"Resolved {resolved_count} cross-module reference(s)")
            if error_count > 0:
                print(f"⚠️ {error_count} reference(s) could not be resolved")
            
            # Build reverse reference index for "who references me?" queries
            reverse_count = project.build_reverse_reference_index()
            if reverse_count > 0:
                print(f"Indexed {reverse_count} reverse reference(s)")
        except Exception as e:
            print(f"Warning: Reference resolution failed: {e}")
                
        self.current_project = project
        return project, failed_modules
