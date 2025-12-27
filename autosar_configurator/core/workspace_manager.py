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
        self.variants: List[str] = []  # e.g., ["Compact_SUV", "Mid_Sedan", "Luxury_Car"]
        self.active_variant: Optional[str] = None  # Currently selected variant
        
        # Metadata
        from datetime import datetime
        self.created_date: str = datetime.now().isoformat()
        self.author: str = ""
        self.description: str = ""
        self.version: str = "1.0.0"
        
        # Cross-module dependency rules (cached results from analysis)
        self.dependency_rules: List[Dict] = []
        
    def add_module(self, module_def: EcucModuleDef, def_path: Path) -> ConfigurationManager:
        """Add a new module to the project"""
        if module_def.short_name in self.module_managers:
            raise ValueError(f"Module {module_def.short_name} already exists in project")
            
        manager = ConfigurationManager(module_def, project_context=self)
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
        Supports both new module-aware paths (e.g., /Adc/AdcConfigSet)
        and legacy /Config paths (e.g., /Config/AdcConfigSet) for backward compatibility.
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
            "format_version": 3,
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
            "modules": []
        }
        
        # Save each module
        project_dir = self.current_project.path.parent
        
        for name, manager in self.current_project.module_managers.items():
            # Determine paths
            def_path = self.current_project.module_defs[name]
            
            # We assume module config is saved next to project or in a subfolder
            # For now, let's just save the config to a file named {ModuleName}_Config.arxml
            config_filename = f"{name}_Config.arxml"
            config_path = project_dir / config_filename
            
            # Save the actual config content
            manager.save_configuration(config_path)
            
            # Record in project file
            data["modules"].append({
                "name": name,
                "def_path": str(def_path),
                "config_path": config_filename
            })
            
        # Write project file
        with open(self.current_project.path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)
            
    def load_project(self, project_path: Path) -> tuple[WorkspaceProject, list]:
        """Load project from file
        
        Returns:
            tuple: (project, failed_modules list)
            failed_modules: List of tuples (module_name, error_message)
        """
        with open(project_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        # Check format version
        format_version = data.get("format_version", 0)
        if format_version > 3:
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
        
        # Load variants (new in format v3)
        project.variants = data.get("variants", [])
        project.active_variant = data.get("active_variant", None)
        
        project_dir = project_path.parent
        failed_modules = []
        
        for module_data in data.get("modules", []):
            name = module_data["name"]
            def_path_str = module_data["def_path"]
            config_path_str = module_data["config_path"]
            
            # Resolve paths (handle relative paths if needed, for now assume absolute or relative to project)
            def_path = Path(def_path_str)
            if not def_path.is_absolute():
                def_path = project_dir / def_path
                
            config_path = project_dir / config_path_str
            
            if def_path.exists():
                try:
                    # Load definition
                    module_def = self.def_parser.parse_module_def_file(def_path)
                    
                    # Create manager
                    manager = project.add_module(module_def, def_path)
                    
                    # Load configuration if exists
                    if config_path.exists():
                        manager.load_configuration(config_path)
                        
                except Exception as e:
                    error_msg = f"Failed to load: {str(e)}"
                    failed_modules.append((name, error_msg))
                    print(f"Failed to load module {name}: {e}")
            else:
                error_msg = f"DEF file not found: {def_path}"
                failed_modules.append((name, error_msg))
                print(f"Definition file not found for {name}: {def_path}")
        
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
