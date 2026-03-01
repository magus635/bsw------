import sys
import logging
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent.parent))

from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')

def main():
    workspace = WorkspaceManager()
    
    # Path to the ImportEB_1 project
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    
    if not dpa_path.exists():
        logging.error(f"DPA file does not exist: {dpa_path}")
        return
        
    logging.info(f"Loading project from {dpa_path} ...")
    try:
        project, failed = workspace.load_project(dpa_path)
    except Exception as e:
        logging.error(f"Failed to load project: {e}")
        return
        
    if not project:
        logging.error("Failed to load DPA project.")
        return
        
    # Get Os module
    os_manager = project.get_manager("Os")
    logging.info(f"OS Manager: {os_manager}")
    if os_manager:
        logging.info(f"OS Manager Configuration: {os_manager.configuration.short_name if os_manager.configuration else None}")
        
    os_config = os_manager.configuration if os_manager else None
    if not os_config or len(os_config.containers) == 0:
        logging.error("Os configuration not found or is empty in workspace!")
        return
        
    logging.info(f"Found Os configuration. Containers: {len(os_config.containers)}")
    
    # Setup generator
    output_dir = Path(__file__).parent.parent / "output"
    output_dir.mkdir(exist_ok=True)
    
    # Standard template dir for this project
    template_dir = dpa_path.parent / "templates"
    
    logging.info(f"Running generation for Os module into {output_dir}/Os ...")
    
    all_configs = {name: (mgr.module_def, mgr.configuration) for name, mgr in project.module_managers.items()}
    generator = CodeGenerator(
        configuration=os_config,
        module_def=os_manager.module_def,
        all_configurations=all_configs,
        project_template_dir=template_dir,
        selected_chip="THA6206_LFBGA292"
    )
    
    generator.generate_all(output_dir)
    
    # Verify the generated structure
    os_out = output_dir / "Os"
    if os_out.exists():
        logging.info("Generated files:")
        for f in sorted(list(os_out.rglob("*"))):
            if f.is_file():
                logging.info(f"  - {f.relative_to(os_out)}")
    else:
        logging.error("Os output directory was not created!")

if __name__ == "__main__":
    main()
