#!/usr/bin/env python3
"""Debug script to dump Dsadc ConfigurationNode tree structure."""

import sys
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from lxml import etree
from pathlib import Path

def dump_tree(node, indent=0, max_depth=5):
    """Print tree structure recursively."""
    if indent > max_depth:
        return
    prefix = "  " * indent
    val = node.get_value() if hasattr(node, 'get_value') else None
    print(f"{prefix}- {node.short_name} ({node.node_type}) [{len(node.children)} children] val={val}")
    for child in node.children.values():
        dump_tree(child, indent + 1, max_depth)

def main():
    def_file = "/Users/qlwang/Desktop/eclipse/Dsadc_THA6_AS440/autosar/Dsadc_THA6206_LFBGA292.arxml"
    cfg_file = "/Users/qlwang/Desktop/project/t5/ConfigValue/Dsadc_Config.arxml"
    
    # Check if files exist
    if not Path(def_file).exists():
        print(f"ERROR: Definition file not found at {def_file}")
        return
    if not Path(cfg_file).exists():
        print(f"ERROR: Configuration file not found at {cfg_file}")
        return
    
    # Init parser
    def_parser = EcucDefParser()
    module_def = def_parser.parse_module_def_file(Path(def_file))
    if module_def is None:
        print("ERROR: Failed to parse definition file")
        return
    print(f"Parsed definition: {module_def.short_name}, containers: {list(module_def.containers.keys())}")
    
    # Parse configuration
    cfg_parser = ArxmlParser()
    tree = etree.parse(cfg_file)
    root = tree.getroot()
    # Find ECUC-MODULE-CONFIGURATION-VALUES
    ns = {'ar': 'http://autosar.org/schema/r4.0'}
    cfg_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', ns)
    if cfg_elem is None:
        print("ERROR: No ECUC-MODULE-CONFIGURATION-VALUES found in config file")
        return
    module_cfg = cfg_parser.parse_ecuc_configuration_values(cfg_elem)
    print(f"Parsed configuration: {module_cfg.short_name}, containers: {len(module_cfg.containers)}")
    
    renderer = Renderer(strict=False)
    renderer.load_module(module_def, module_cfg, variant="v")
    
    dsadc = renderer.symbol_table.get_module("Dsadc")
    if dsadc:
        print("=== Dsadc Module Tree ===")
        dump_tree(dsadc)
        
        # Specifically check DsadcConfigSet
        config_set = dsadc.get_child("DsadcConfigSet")
        if config_set:
            print("\n=== DsadcConfigSet children ===")
            for name, child in config_set.children.items():
                print(f"  {name}: {child.node_type}, {len(child.children)} children")
                
            # Check for DsadcChannel
            dsadc_channel = config_set.get_child("DsadcChannel")
            if dsadc_channel:
                print("\n=== DsadcChannel children ===")
                for name, child in dsadc_channel.children.items():
                    print(f"  {name}: {child.node_type}")
                    # Print DsadcChannelId if exists
                    ch_id = child.get_child("DsadcChannelId")
                    if ch_id:
                        print(f"    DsadcChannelId = {ch_id.get_value()}")
            else:
                print("\n!!! DsadcChannel NOT FOUND under DsadcConfigSet !!!")
    else:
        print("ERROR: Dsadc module not loaded")

if __name__ == "__main__":
    main()
