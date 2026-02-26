import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.workspace_manager import WorkspaceManager
import inspect

# Get source of import_eb_project
src = inspect.getsource(WorkspaceManager.import_eb_project)
print("--- SOURCE ---")
for i, line in enumerate(src.split('\n')):
    if 'Scanning for module definitions' in line or 'eb_plugins_dir =' in line:
        print(f"{i}: {line}")

