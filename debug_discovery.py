
from pathlib import Path
import sys
import shutil
import logging

# Configure logging
logging.basicConfig(level=logging.INFO)

# Add the project root to sys.path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

def debug_canfd():
    project_path = Path('/Users/qlwang/Desktop/project/t5/t5.dpa')
    wm = WorkspaceManager()
    project, failed = wm.load_project(project_path)
    
    if not project:
        print("Failed to load project")
        return
        
    can_manager = project.module_managers.get('Can')
    if not can_manager:
        print("Can module not found in project")
        return
        
    project_dir = project_path.parent
    project_template_dir = project_dir / "templates"
    
    # 1. Clean previous generation
    output_dir = Path('/Users/qlwang/Desktop/project/t5/generateCode')
    if output_dir.exists():
        print(f"Cleaning output directory: {output_dir}")
        shutil.rmtree(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    generator = CodeGenerator(
        can_manager.module_def,
        can_manager.configuration,
        project_template_dir=project_template_dir
    )
    
    print("\nTriggering FULL code generation for Can with variant='Default'...")
    
    # Simulate UI call
    try:
        success = generator.generate_all(output_dir, variant='Default')
        print(f"Generation result: {success}")
    except Exception as e:
        print(f"Generation crashed: {e}")
    
    # Check if Can_PBcfg.c exists
    pbcfg = output_dir / 'Can' / 'Default' / 'src' / 'Can_PBcfg.c'
    if pbcfg.exists():
        print(f"✅ FOUND Can_PBcfg.c at {pbcfg}")
    else:
        print(f"❌ Can_PBcfg.c NOT generated.")

if __name__ == "__main__":
    debug_canfd()
