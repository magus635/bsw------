import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.workspace_manager import WorkspaceManager

manager = WorkspaceManager()
dpa_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa')
project, failed = manager.load_project(dpa_path)

print("\n--- Loaded modules ---")
print([m for m in project.module_managers.keys()])
print("\n--- Failed modules ---")
print(failed)

if 'Os' in project.module_managers:
    os_mgr = project.module_managers['Os']
    print(f"\n--- Os Module Config ---")
    print(f"Containers: {len(os_mgr.configuration.containers)}")
