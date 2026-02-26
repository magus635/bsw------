import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import EcucModuleDef

os_config_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml')
os_def_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os.xdm') # Just a dummy or actual if exists?

try:
    # Need a module definition first. Let's create a dummy one if no real one is easily available.
    module_def = EcucModuleDef("Os")
    manager = ConfigurationManager(module_def)
    manager.load_configuration(os_config_path)
    print(f"Loaded config: {manager.configuration.short_name}")
    print(f"Containers count: {len(manager.configuration.containers)}")
except Exception as e:
    print(f"Error loading: {e}")
    import traceback
    traceback.print_exc()

