import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

os_config_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml')

try:
    parser = EcucDefParser()
    # It parses module definitions. Will it fail on our file?
    module_def = parser.parse_module_def_file(os_config_path)
    if module_def:
        print(f"Parsed as def: {module_def.short_name}")
except Exception as e:
    print(f"Error parsing: {e}")

