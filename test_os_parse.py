from pathlib import Path
from autosar_configurator.core.parser.xdm_config_parser import XdmConfigParser
parser = XdmConfigParser()
file_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml")
config = parser.parse_file(file_path)
print(f"Config loaded: {config.short_name if config else None}")
