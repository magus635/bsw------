import sys
from pathlib import Path
import logging

# Setup basic logging
logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')

# Add project root to path
PROJECT_ROOT = Path("/Users/qlwang/Desktop/bsw图形配置工具")
sys.path.append(str(PROJECT_ROOT))

try:
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    from autosar_configurator.generator.generator import CodeGenerator
except ImportError as e:
    print(f"Import Error: {e}")
    sys.exit(1)

def main():
    workspace = WorkspaceManager()
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    
    print(f"Loading project: {dpa_path}")
    project, failed = workspace.load_project(dpa_path)
    
    if failed:
        for mod, err in failed:
            print(f"Failed to load {mod}: {err}")
    
    print(f"Loaded modules: {[m.module_def.short_name for m in project.get_all_managers()]}")
    os_manager = project.get_manager("Os")
    if not os_manager:
        print("Os module not found in project!")
        # Try finding by name case-insensitive
        for m in project.get_all_managers():
            if m.module_def.short_name.lower() == "os":
                print(f"Found module with similar name: {m.module_def.short_name}")
                os_manager = m
                break
        
    if os_manager:
        print(f"Os module found: {os_manager.module_def.short_name}")
    else:
        print("Os module really not found.")
        return

    print(f"Os module containers count: {len(os_manager.configuration.containers)}")
    for c in os_manager.configuration.containers:
        print(f" - Container: {c.short_name}, Def: {c.definition_ref}, Index: {c.index}")
        if c.short_name.startswith("OsApplication") or c.short_name.startswith("OsCore"):
            for sub in c.sub_containers:
                 print(f"   - Sub: {sub.short_name}, Def: {sub.definition_ref}, Index: {sub.index}")

    print("Initializing CodeGenerator for Os...")
    
    # Template dir is in project_root/templates/Os/
    project_template_dir = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/templates")
    
    # Build all_configurations dict for cross-module access
    all_configs = {}
    for mod_name, mgr in project.module_managers.items():
        all_configs[mod_name] = (mgr.module_def, mgr.configuration)
    
    gen = CodeGenerator(
        module_def=os_manager.module_def,
        configuration=os_manager.configuration,
        project_template_dir=project_template_dir,
        all_configurations=all_configs,
        selected_chip=project.selected_chip
    )
    
    # Output directory
    out_dir = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/generateCode")
    print(f"Generating code to: {out_dir}/Os")
    
    # Note: CodeGenerator.generate_all appends the module name to the path
    gen.generate_all(out_dir)
    print("Generation complete.")

if __name__ == "__main__":
    main()
