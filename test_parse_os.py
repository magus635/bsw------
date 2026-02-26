import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.parser.arxml_parser import ArxmlParser

os_config_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml')

try:
    parser = ArxmlParser()
    root_container = parser.parse_file(os_config_path)
    print(f"Parsed root container: {root_container.short_name}")
    print(f"Sub-containers count: {len(root_container.sub_containers)}")
    for sub in root_container.sub_containers:
        print(f" - {sub.short_name}")
except Exception as e:
    print(f"Error parsing: {e}")
    import traceback
    traceback.print_exc()

