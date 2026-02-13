#!/usr/bin/env python3
"""Run Intc module generation to debug text:contains issue."""

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
    module_name = "Intc"
    def_file = "/Users/qlwang/Desktop/t1/Def/plugins/Intc_THA6_AS440/autosar/Intc_THA6206_LFBGA292.arxml"
    cfg_file = "/Users/qlwang/Desktop/t1/ConfigValue/Intc_config.arxml"
    template_dir = "/Users/qlwang/Desktop/t1/templates/Intc"
    output_dir = "/Users/qlwang/Desktop/t1/generateCode_debug/Intc"

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
    # Print the CoreFixedIntClass entry
    key = 'Intc.CoreFixedIntClass'
    if key in ecu_resources:
        print(f"  {key} = {ecu_resources[key]!r}")
    else:
        print(f"  WARNING: {key} NOT in ecu_resources!")
        # Show available Intc keys
        for k, v in ecu_resources.items():
            if k.startswith('Intc.'):
                print(f"    {k} = {v!r}")

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

    eb_engine.add_module(module_def, module_cfg, variant="Default")
    eb_engine.add_module(res_def, res_cfg, variant="Default")

    # Generate Intc_PBcfg.c
    template_file = "src/Intc_PBcfg.c"
    full_template_path = os.path.join(template_dir, template_file)
    output_file = os.path.join(output_dir, "Default/src/Intc_PBcfg.c")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    print(f"Generating {output_file} from {full_template_path}...")
    context = {
        'module_def': module_def,
        'configuration': module_cfg,
        'active_variant': 'Default',
        'module_name': 'Intc'
    }

    try:
        content = eb_engine.render_file(full_template_path, context, ecu_resources=ecu_resources)
        with open(output_file, 'w') as f:
            f.write(content)
        print("Generation successful!")
    except Exception as e:
        print(f"Generation failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()
