import sys
import os
from pathlib import Path

# Add project root to sys.path
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

dpa_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa')
out_dir = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/generateCode')
template_root = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/templates')

print(f"Loading project from {dpa_path}...")
workspace = WorkspaceManager()
project, _ = workspace.load_project(dpa_path)

all_cfgs = {
    mgr.module_def.short_name: (mgr.module_def, mgr.configuration)
    for mgr in project.get_all_managers()
}

# The modules that we want to generate
modules_to_gen = [
    "Adc", "Base", "Can", "CanIf", "Crc", "Dio", "Dma", "Dsadc", "EcuC",
    "Eth", "Fee", "Fls", "Gpt", "I2c", "Intc", "Lin", "Mcu", "Ocu",
    "Os", "Port", "Pwm", "Sent", "Spi", "Uart", "Wdg"
]

print(f"Starting generation for {len(modules_to_gen)} modules...")

for mod_name in modules_to_gen:
    mgr = project.get_manager(mod_name)
    if not mgr:
        print(f"  [Skip] Module {mod_name} not found in project.")
        continue
        
    template_dir = template_root / mod_name
    if not template_dir.exists():
        print(f"  [Skip] Template dir {template_dir} not found.")
        continue
        
    print(f"  [Gen] {mod_name}...")
    
    gen = CodeGenerator(
        module_def=mgr.module_def,
        configuration=mgr.configuration,
        project_template_dir=template_dir,
        all_configurations=all_cfgs
    )
    
    try:
        # Pass base out_dir and let generator handle /Module/Variant nesting
        gen.generate_all(out_dir, variant="Default")
        print(f"    -> Success: {mod_name}")
    except Exception as e:
        print(f"    -> Failed: {e}")

print("All done!")
