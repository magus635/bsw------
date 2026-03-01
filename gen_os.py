import sys
from pathlib import Path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import Generator

def main():
    workspace = WorkspaceManager()
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    project, failed = workspace.load_project(dpa_path)
    
    gen = Generator(project)
    
    # Generate code for Os module
    out_dir = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/generateCode")
    gen.generate_module("Os", out_dir)
    print("Generation complete")

if __name__ == "__main__":
    main()
