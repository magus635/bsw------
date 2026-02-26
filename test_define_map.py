import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.workspace_manager import WorkspaceManager

manager = WorkspaceManager()
project_root = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa')

define_map = {}
eb_plugins_dir = project_root / "Define" / "EbPlugins" / "eclipse"
if not eb_plugins_dir.exists():
    eb_plugins_dir = project_root / "Def" / "plugins"

print(f"eb_plugins_dir exists? {eb_plugins_dir.exists()}")
if eb_plugins_dir.exists():
    for module_dir in sorted(eb_plugins_dir.iterdir()):
        if not module_dir.is_dir(): continue
        config_dir = module_dir / "config"
        if config_dir.exists():
            for def_file in config_dir.glob("*.xdm"):
                print(f"Found xdm: {def_file}")
                define_map[def_file.stem] = def_file
        autosar_dir = module_dir / "autosar"
        if autosar_dir.exists():
            for def_file in autosar_dir.glob("*.arxml"):
                print(f"Found arxml: {def_file}")
                module_name = def_file.stem
                base_name = module_name.split('_')[0] if '_' in module_name else module_name
                existing_keys_lower = {k.lower() for k in define_map}
                if base_name.lower() not in existing_keys_lower:
                    define_map[base_name] = def_file

print(f"Map len after primary: {len(define_map)}")
