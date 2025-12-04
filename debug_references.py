from lxml import etree
from pathlib import Path
import sys
import os

# Add current directory to path
sys.path.append(os.getcwd())

from autosar_configurator.core.parser.arxml_parser import ArxmlParser

def test_load_config():
    file_path = Path('Adc_Test_WithReferences.arxml')
    if not file_path.exists():
        print(f"❌ File not found: {file_path}")
        return

    print(f"📂 Loading {file_path}...")
    
    try:
        parser = ArxmlParser()
        tree = etree.parse(str(file_path))
        root = tree.getroot()
        namespaces = {'ar': 'http://autosar.org/schema/r4.0'}
        config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', namespaces)
        
        if config_elem is None:
            print("❌ ECUC-MODULE-CONFIGURATION-VALUES not found")
            return
            
        config = parser.parse_ecuc_configuration_values(config_elem)
        print(f"✅ Configuration loaded: {config.short_name}")
        
        # Inspect containers and references
        print("\n🔍 Inspecting Containers and References:")
        
        def inspect_container(container, indent=""):
            print(f"{indent}📦 {container.short_name}")
            
            # Check references
            if container.reference_values:
                for ref_name, ref_val in container.reference_values.items():
                    print(f"{indent}  🔗 {ref_name} -> {ref_val.value_ref}")
            
            # Recurse
            for sub in container.sub_containers:
                inspect_container(sub, indent + "  ")
                
        for container in config.containers:
            inspect_container(container)
            
    except Exception as e:
        print(f"❌ Error: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    test_load_config()
