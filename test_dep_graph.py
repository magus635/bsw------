#!/usr/bin/env python3
"""
Test script to verify dependency graph edge creation
"""
from pathlib import Path
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from lxml import etree

def test_dependency_analysis():
    # Load configuration
    config_path = Path('Adc_Test_WithReferences.arxml')
    if not config_path.exists():
        print(f"❌ {config_path} not found")
        return
    
    parser = ArxmlParser()
    tree = etree.parse(str(config_path))
    root = tree.getroot()
    namespaces = {'ar': 'http://autosar.org/schema/r4.0'}
    config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', namespaces)
    
    if config_elem is None:
        print("❌ No configuration found")
        return
    
    config = parser.parse_ecuc_configuration_values(config_elem)
    print(f"✅ Loaded configuration: {config.short_name}")
    
    # Manual dependency analysis (without creating widget)
    def collect_names(container, names, prefix=""):
        full_name = f"{prefix}/{container.short_name}" if prefix else container.short_name
        names.add(full_name)
        for sub in container.sub_containers:
            collect_names(sub, names, full_name)
    
    def analyze_deps(container, deps, module_name, prefix=""):
        full_name = f"{prefix}/{container.short_name}" if prefix else container.short_name
        
        for ref_name, ref_value in container.reference_values.items():
            target = ref_value.value_ref
            if target:
                print(f"🔗 Found reference: {full_name} --[{ref_name}]--> {target}")
                
                # Parse target
                parts = [p for p in target.split('/') if p]
                
                # Skip 'Config' prefix
                if len(parts) > 0 and parts[0] == 'Config':
                    parts = parts[1:]
                
                target_name = None
                if len(parts) >= 2:
                    if parts[0] == module_name:
                        target_name = '/'.join(parts[1:])
                    else:
                        # Cross-module reference - keep module prefix
                        target_name = '/'.join(parts)
                        print(f"   → Cross-module reference to {parts[0]}")
                elif len(parts) > 0:
                    target_name = '/'.join(parts)
                
                if target_name:
                    print(f"   → Parsed target: {target_name}")
                    if full_name not in deps:
                        deps[full_name] = []
                    deps[full_name].append((target_name, ref_name))
        
        for sub in container.sub_containers:
            analyze_deps(sub, deps, module_name, full_name)
    
    print("\n🔍 Analyzing dependencies...")
    deps = {}
    for container in config.containers:
        analyze_deps(container, deps, config.short_name)
    
    print(f"\n📊 Found {len(deps)} containers with references:")
    for source, targets in deps.items():
        print(f"  {source} -> {len(targets)} references")
        for target, ref_name in targets:
            print(f"    - [{ref_name}] -> {target}")
    
    # Collect all node names
    node_names = set()
    for container in config.containers:
        collect_names(container, node_names)
    node_names.add(config.short_name)
    
    # Add external reference targets as nodes (like the actual graph does)
    for source, targets in deps.items():
        for target, ref_name in targets:
            node_names.add(target)
    
    print(f"\n📦 Total nodes: {len(node_names)}")
    print("Node names:")
    for name in sorted(node_names):
        print(f"  - {name}")
    
    # Check which references will create edges
    print(f"\n✅ Edges that will be created:")
    edge_count = 0
    for source, targets in deps.items():
        if source in node_names:
            for target, ref_name in targets:
                if target in node_names:
                    print(f"  {source} --[{ref_name}]--> {target}")
                    edge_count += 1
                else:
                    print(f"  ⚠️  MISSING TARGET: {source} --[{ref_name}]--> {target} (not in nodes)")
        else:
            print(f"  ⚠️  MISSING SOURCE: {source}")
    
    print(f"\n📈 Total edges: {edge_count}")

if __name__ == "__main__":
    test_dependency_analysis()
