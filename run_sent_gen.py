#!/usr/bin/env python3
"""Run Sent module generation."""

import sys
import os
from pathlib import Path

# Add project root to path
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.hardware.tresos_properties_parser import TresosPropertiesParser
from lxml import etree

def main():
    module_name = "Sent"
    project_root = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa")
    def_file = project_root / "Def/plugins/Sent_THA6_AS440/autosar/Sent_THA6206_LFBGA292.arxml"
    cfg_file = project_root / "ConfigValue/Sent_Config.arxml"
    template_dir = project_root / "templates/Sent"
    output_dir = project_root / "generateCode/Sent"

    # Resource module for cross-module lookup
    resource_def_file = project_root / "Def/plugins/Resource_THA6_AS440/autosar/Resource_THA6206_LFBGA292.arxml"
    resource_cfg_file = project_root / "ConfigValue/Resource_Config.arxml"
    
    # ECU Resource Properties
    properties_file = project_root / "Def/plugins/Resource_THA6_AS440/resource/CotexR52_THA6206_LFBGA292.properties"

    print(f"--- Running generation for {module_name} ---")
    print(f"Template dir: {template_dir}")
    print(f"Include search paths will be: [{template_dir}, {template_dir.parent}]")

    # Create engine with template_dir for INCLUDE resolution
    # Using strict=True to catch rendering errors!
    eb_engine = EBTemplateEngine(strict=True, template_dir=template_dir)

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

    # Register modules with correct API: add_module(module_def, configuration, variant)
    variant = "v"
    eb_engine.add_module(module_def, module_cfg, variant=variant)
    eb_engine.add_module(res_def, res_cfg, variant=variant)

    # Load ECU resources
    ecu_resources = {}
    if os.path.exists(properties_file):
        print(f"Loading ECU resources from {properties_file}...")
        parser = TresosPropertiesParser()
        parser.parse_file(Path(properties_file))
        ecu_resources = parser.get_ecu_resources_dict()
        print(f"  Loaded {len(ecu_resources)} properties")
    else:
        print(f"WARNING: Properties file not found: {properties_file}")

    # Template files to generate
    templates = [
        ("include/Sent_Cfg.h", "v/include/Sent_Cfg.h"),
        ("include/Sent_Cfg.h", "Default/include/Sent_Cfg.h"),
    ]

    context = {
        'module_def': module_def,
        'configuration': module_cfg,
        'active_variant': variant,
        'module_name': module_name,
        'all_modules': {
            'Sent': (module_def, module_cfg),
            'Resource': (res_def, res_cfg)
        }
    }

    for tpl_rel, out_rel in templates:
        tpl_path = template_dir / tpl_rel
        out_path = output_dir / out_rel

        if not tpl_path.exists():
            print(f"Template not found: {tpl_path}")
            continue

        os.makedirs(out_path.parent, exist_ok=True)
        print(f"\nGenerating {out_path} from {tpl_path}...")

        try:
            content = eb_engine.render_file(str(tpl_path), context, ecu_resources=ecu_resources)
            with open(out_path, 'w') as f:
                f.write(content)
            print(f"  Success! ({len(content)} bytes)")

            # Quick validation
            if "Cfg.h" in str(out_path):
                if "(NoneU)" in content:
                    print("  WARNING: (NoneU) found in output")
                if "#define SENT_SAFETY_ENABLE          /*" in content:
                    print("  WARNING: CALL macro output is empty (INCLUDE may have failed)")
                elif "(STD_ON)" in content or "(STD_OFF)" in content:
                    print("  OK: Macro values are present")

        except Exception as e:
            print(f"  ERROR: {e}")
            import traceback
            traceback.print_exc()

if __name__ == "__main__":
    main()
