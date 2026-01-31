#!/usr/bin/env python3
"""Run Mcu module generation to capture debug logs."""

import sys
import os
from pathlib import Path

# Add project root to path
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.generator import CodeGenerator
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from lxml import etree

def main():
    module_name = "Mcu"
    def_file = "/Users/qlwang/Desktop/eclipse/Mcu_THA6_AS440/autosar/Mcu_THA6206_LFBGA292.arxml"
    cfg_file = "/Users/qlwang/Desktop/project/t5/ConfigValue/Mcu_Config.arxml"
    template_dir = "/Users/qlwang/Desktop/project/t5/templates/Mcu"
    output_dir = "/Users/qlwang/Desktop/project/t5/generateCode/Mcu"
    
    # We also need Resource config for cross-module lookup
    resource_cfg_file = "/Users/qlwang/Desktop/project/t5/ConfigValue/Resource_Config.arxml"
    resource_def_file = "/Users/qlwang/Desktop/eclipse/Resource_THA6_AS440/autosar/Resource_THA6206_LFBGA292.arxml"
    
    print(f"--- Running generation for {module_name} ---")
    
    from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
    eb_engine = EBTemplateEngine(strict=False, template_dir=Path(template_dir))
    
    # Load module definition
    def_parser = EcucDefParser()
    module_def = def_parser.parse_module_def_file(Path(def_file))
    
    # Load configuration
    cfg_parser = ArxmlParser()
    tree = etree.parse(cfg_file)
    cfg_elem = tree.getroot().find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', {'ar': 'http://autosar.org/schema/r4.0'})
    module_cfg = cfg_parser.parse_ecuc_configuration_values(cfg_elem)
    
    # Load Resource module for cross-module access
    res_def = def_parser.parse_module_def_file(Path(resource_def_file))
    res_tree = etree.parse(resource_cfg_file)
    res_cfg_elem = res_tree.getroot().find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', {'ar': 'http://autosar.org/schema/r4.0'})
    res_cfg = cfg_parser.parse_ecuc_configuration_values(res_cfg_elem)
    
    # Register modules
    eb_engine.add_module(module_def, module_cfg, variant="v")
    eb_engine.add_module(res_def, res_cfg, variant="v")
    
    # Generate Mcu_PBcfg.c
    template_file = "src/Mcu_PBcfg.c"
    full_template_path = os.path.join(template_dir, template_file)
    output_file = os.path.join(output_dir, "v/src/Mcu_PBcfg.c")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    
    print(f"Generating {output_file} from {full_template_path}...")
    context = {
        'module_def': module_def,
        'configuration': module_cfg,
        'active_variant': 'v',
        'module_name': 'Mcu'
    }
    
    try:
        content = eb_engine.render_file(full_template_path, context)
        with open(output_file, 'w') as f:
            f.write(content)
        print("Generation successful!")
    except Exception as e:
        print(f"Generation failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()
