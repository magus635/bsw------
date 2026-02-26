import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.workspace_manager import WorkspaceManager

manager = WorkspaceManager()
manager.create_project("test_eb_project", Path('/tmp/test_eb_project'))
eb_root = Path('/Users/qlwang/Desktop/ImportEB_1')
_, failed = manager.import_eb_project(eb_root, "MCAL_R440_FuSa")

print("\n--- Failed Modules ---")
for mod, err in failed:
    print(f"- {mod}: {err}")
