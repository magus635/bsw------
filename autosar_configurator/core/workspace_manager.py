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
        
        # Metadata
        from datetime import datetime
        self.created_date: str = datetime.now().isoformat()
        self.author: str = ""
        self.description: str = ""
        self.version: str = "1.0.0"
        
    def add_module(self, module_def: EcucModuleDef, def_path: Path) -> ConfigurationManager:
        """Add a new module to the project"""
        if module_def.short_name in self.module_managers:
            raise ValueError(f"Module {module_def.short_name} already exists in project")
            
        manager = ConfigurationManager(module_def)
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
            "format_version": 1,
            "tool_version": "1.0.0",
            "name": self.current_project.name,
            "created": self.current_project.created_date,
            "last_modified": datetime.now().isoformat(),
            "author": getattr(self.current_project, 'author', ''),
            "description": getattr(self.current_project, 'description', ''),
            "version": getattr(self.current_project, 'version', '1.0.0'),
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
        if format_version > 1:
            raise ValueError(
                f"Unsupported project format version {format_version}. "
                f"Please upgrade the tool."
            )
        
        project_name = data.get("name", "Untitled")
        project = WorkspaceProject(project_name, project_path)
        
        # Store metadata
        from datetime import datetime
        project.created_date = data.get("created", datetime.now().isoformat())
        project.author = data.get("author", "")
        project.description = data.get("description", "")
        project.version = data.get("version", "1.0.0")
        
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
                
        self.current_project = project
        return project, failed_modules
