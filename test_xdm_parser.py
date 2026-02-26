import sys
from pathlib import Path

sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具').absolute()))
from autosar_configurator.core.parser.xdm_config_parser import XdmConfigParser

os_config_path = Path('/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Os_Config.arxml')

try:
    parser = XdmConfigParser()
    config = parser.parse_file(os_config_path)
    if config:
        print(f"Parsed Config: {config.short_name}")
        print(f"Top-level containers: {len(config.containers)}")
        for cont in config.containers:
            print(f" - {cont.short_name}")
            if cont.short_name == 'OsAlarm':
                print(f"   Alarms: {len(cont.sub_containers)}")
                for sub in cont.sub_containers:
                    print(f"    - {sub.short_name}")
                    for ref_name, ref_val in sub.reference_values.items():
                        print(f"      Ref {ref_name}: {ref_val}")
                    for mr_name, mr_vals in sub.multi_reference_values.items():
                        print(f"      MultiRef {mr_name}: {mr_vals}")

    else:
        print("Not an XDM config file")
except Exception as e:
    print(f"Error parsing: {e}")
    import traceback
    traceback.print_exc()

