#!/usr/bin/env python3
"""Run Dsadc module generation to capture debug logs."""

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
    module_name = "Dsadc"
    def_file = "/Users/qlwang/Desktop/eclipse/Dsadc_THA6_AS440/autosar/Dsadc_THA6206_LFBGA292.arxml"
    cfg_file = "/Users/qlwang/Desktop/project/t5/ConfigValue/Dsadc_Config.arxml"
    template_dir = "/Users/qlwang/Desktop/project/t5/templates/Dsadc"
    output_dir = "/Users/qlwang/Desktop/project/t5/generateCode/Dsadc"
    
    print(f"--- Running generation for {module_name} ---")
    
    # Init generator
    # gen = CodeGenerator(...) # We'll use eb_engine directly to keep it simple
    
    # Use EBTemplateEngine directly to generate a specific file and see the trace
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
    
    # Register module in engine
    eb_engine.add_module(module_def, module_cfg, variant="v")
    
    # Generate Dsadc_Cfg.h
    template_file = "include/Dsadc_Cfg.h"
    full_template_path = os.path.join(template_dir, template_file)
    output_file = os.path.join(output_dir, "v/include/Dsadc_Cfg.h")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    print(f"Generating {output_file} from {full_template_path}...")

    context = {
        'module_def': module_def,
        'configuration': module_cfg,
        'active_variant': 'v'
    }

    try:
        content = eb_engine.render_file(full_template_path, context)
        with open(output_file, 'w') as f:
            f.write(content)
        print("Dsadc_Cfg.h generation successful!")
    except Exception as e:
        print(f"Dsadc_Cfg.h generation failed: {e}")
        import traceback
        traceback.print_exc()

    # Generate Dsadc_PBcfg.h
    template_file = "include/Dsadc_PBcfg.h"
    full_template_path = os.path.join(template_dir, template_file)
    output_file = os.path.join(output_dir, "v/include/Dsadc_PBcfg.h")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    print(f"Generating {output_file} from {full_template_path}...")

    try:
        content = eb_engine.render_file(full_template_path, context)
        with open(output_file, 'w') as f:
            f.write(content)
        print("Dsadc_PBcfg.h generation successful!")
    except Exception as e:
        print(f"Dsadc_PBcfg.h generation failed: {e}")
        import traceback
        traceback.print_exc()

    # Generate Dsadc_PBcfg.c
    template_file = "src/Dsadc_PBcfg.c"
    full_template_path = os.path.join(template_dir, template_file)
    output_file = os.path.join(output_dir, "v/src/Dsadc_PBcfg.c")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    print(f"Generating {output_file} from {full_template_path}...")

    try:
        content = eb_engine.render_file(full_template_path, context)
        with open(output_file, 'w') as f:
            f.write(content)
        print("Dsadc_PBcfg.c generation successful!")
    except Exception as e:
        print(f"Dsadc_PBcfg.c generation failed: {e}")
        import traceback
        traceback.print_exc()

    print("\nAll generation completed!")

if __name__ == "__main__":
    main()
