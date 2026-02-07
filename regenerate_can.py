import sys
from pathlib import Path
import os

# Add project root to path
project_root = Path('/Users/qlwang/Desktop/bsw图形配置工具')
sys.path.insert(0, str(project_root))

from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

def main():
    project_path = Path('/Users/qlwang/Desktop/t1/t1.dpa')
    wm = WorkspaceManager()
    
    print(f"Loading project: {project_path}")
    project, failed = wm.load_project(project_path)
    
    if failed:
        print(f"Failed to load modules: {failed}")
        # return
    
    can_mgr = project.module_managers.get('Can')
    if not can_mgr:
        print("Can module not found in project")
        return
        
    print("Generating code for Can module...")
    
    # Setup generator
    project_dir = project_path.parent
    project_template_dir = project_dir / "templates"
    output_dir = project_dir / "generateCode"
    
    variant_name = project.active_variant
    variant_overrides = {}
    if variant_name and can_mgr.configuration:
        variant_overrides = can_mgr.configuration.variant_overrides.get(variant_name, {})
        
    all_configs = {name: (mgr.module_def, mgr.configuration) for name, mgr in project.module_managers.items()}
    
    generator = CodeGenerator(
        can_mgr.module_def,
        can_mgr.configuration,
        project_template_dir=project_template_dir if project_template_dir.exists() else None,
        variant_overrides=variant_overrides,
        all_configurations=all_configs
    )
    
    # Generate
    generator.generate_all(output_dir, variant=variant_name)
    print(f"Generation complete. Output at: {output_dir / 'Can' / variant_name / 'src' / 'Can_PBcfg.c'}")

if __name__ == "__main__":
    main()
