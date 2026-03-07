import sys
from pathlib import Path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

def main():
    workspace = WorkspaceManager()
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    project, failed = workspace.load_project(dpa_path)
    
    # Get the OS manager
    os_mgr = project.get_manager("Os")
    
    # Pass all modules for cross-module reference resolution
    all_configs = {mgr.module_def.short_name: (mgr.module_def, mgr.configuration) for mgr in project.get_all_managers()}
    
    gen = CodeGenerator(
        module_def=os_mgr.module_def,
        configuration=os_mgr.configuration,
        project_template_dir=Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/templates/Os"),
        all_configurations=all_configs,
        selected_chip=project.selected_chip,
        ecu_resources=project.ecu_resources
    )
    
    # Generate code for Os module
    out_dir = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/generateCode/Os/Default")
    gen.generate_all(out_dir)
    print("Generation complete")

if __name__ == "__main__":
    main()
