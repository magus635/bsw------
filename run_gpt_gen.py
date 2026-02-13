#!/usr/bin/env python3
"""Run Gpt module generation to verify XPath and Resource fixes."""

import sys
import os
from pathlib import Path

sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.hardware.tresos_properties_parser import TresosPropertiesParser
from lxml import etree

def main():
    module_name = "Gpt"
    def_file = "/Users/qlwang/Desktop/t1/Def/plugins/Gpt_THA6_AS440/autosar/Gpt_THA6206_LFBGA292.arxml"
    cfg_file = "/Users/qlwang/Desktop/t1/ConfigValue/Gpt_Config.arxml"
    template_dir = "/Users/qlwang/Desktop/t1/templates/Gpt"
    output_dir = "/Users/qlwang/Desktop/t1/generateCode_debug/Gpt"

    resource_cfg_file = "/Users/qlwang/Desktop/t1/ConfigValue/Resource_Config.arxml"
    resource_def_file = "/Users/qlwang/Desktop/t1/Def/plugins/Resource_THA6_AS440/autosar/Resource_THA6206_LFBGA292.arxml"

    # Load properties file for ecu:list/ecu:get
    props_file = "/Users/qlwang/Desktop/t1/Def/plugins/Resource_THA6_AS440/resource/CotexR52_THA6206_LFBGA292.properties"

    print(f"--- Running generation for {module_name} ---")

    # Load ecu_resources from properties
    parser = TresosPropertiesParser()
    parser.parse_file(Path(props_file))
    ecu_resources = parser.get_ecu_resources_dict()
    print(f"Loaded {len(ecu_resources)} ECU resources")

    eb_engine = EBTemplateEngine(strict=False, template_dir=Path(template_dir))

    def_parser = EcucDefParser()
    module_def = def_parser.parse_module_def_file(Path(def_file))

    cfg_parser = ArxmlParser()
    tree = etree.parse(cfg_file)
    cfg_elem = tree.getroot().find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', {'ar': 'http://autosar.org/schema/r4.0'})
    module_cfg = cfg_parser.parse_ecuc_configuration_values(cfg_elem)

    res_def = def_parser.parse_module_def_file(Path(resource_def_file))
    res_tree = etree.parse(resource_cfg_file)
    res_cfg_elem = res_tree.getroot().find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', {'ar': 'http://autosar.org/schema/r4.0'})
    res_cfg = cfg_parser.parse_ecuc_configuration_values(res_cfg_elem)

    mcu_def_file = "/Users/qlwang/Desktop/t1/Def/plugins/Mcu_THA6_AS440/autosar/Mcu_THA6206_LFBGA292.arxml"
    mcu_cfg_file = "/Users/qlwang/Desktop/t1/ConfigValue/Mcu_Config.arxml"
    mcu_def = def_parser.parse_module_def_file(Path(mcu_def_file))
    mcu_tree = etree.parse(mcu_cfg_file)
    mcu_cfg_elem = mcu_tree.getroot().find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', {'ar': 'http://autosar.org/schema/r4.0'})
    mcu_cfg = cfg_parser.parse_ecuc_configuration_values(mcu_cfg_elem)

    eb_engine.add_module(module_def, module_cfg, variant="Default")
    eb_engine.add_module(res_def, res_cfg, variant="Default")
    eb_engine.add_module(mcu_def, mcu_cfg, variant="Default")


    # Generate Gpt_PBcfg.c
    template_file = "src/Gpt_PBcfg.c"
    full_template_path = os.path.join(template_dir, template_file)
    output_file = os.path.join(output_dir, "Default/src/Gpt_PBcfg.c")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    print(f"Generating {output_file} from {full_template_path}...")
    context = {
        'module_def': module_def,
        'configuration': module_cfg,
        'active_variant': 'Default',
        'module_name': 'Gpt'
    }

    try:
        content = eb_engine.render_file(full_template_path, context, ecu_resources=ecu_resources)
        with open(output_file, 'w') as f:
            f.write(content)
        print(f"Generation successful! Output: {output_file}")
        
        # Quick verification
        lines = content.splitlines()
        notification_lines = [l for l in lines if 'Notification' in l and 'extern' in l]
        core1_lines = [l for l in lines if 'CORE1' in l or 'Core1' in l or 'core1' in l]
        comma_only = [i for i, l in enumerate(lines) if l.strip() == ',']
        
        print(f"\n--- Quick Verification ---")
        print(f"extern Notification declarations: {len(notification_lines)}")
        for l in notification_lines[:5]:
            print(f"  {l.strip()}")
        print(f"Core1 references: {len(core1_lines)}")
        for l in core1_lines[:5]:
            print(f"  {l.strip()}")
        print(f"Lines with only comma: {len(comma_only)}")
        if comma_only:
            print(f"  At lines: {comma_only[:10]}")
            
    except Exception as e:
        print(f"Generation failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()
