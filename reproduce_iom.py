import sys
import os
from pathlib import Path

# Add project root to path
sys.path.append("/Users/qlwang/Desktop/bsw图形配置工具")

from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
)

def create_dummy_def():
    """Create a dummy definition to match the ARXML structure"""
    module_def = EcucModuleDef("Iom")
    
    # IomModuleConfiguration
    module_config_def = EcucContainerDef("IomModuleConfiguration")
    module_config_def.definition_ref = "/THA6_AS440_FuSa/Iom/IomModuleConfiguration"
    module_def.add_container(module_config_def)
    
    # IomLPUConfiguration
    lpu_config_def = EcucContainerDef("IomLPUConfiguration")
    lpu_config_def.upper_multiplicity = -1
    lpu_config_def.definition_ref = "/THA6_AS440_FuSa/Iom/IomModuleConfiguration/IomLPUConfiguration"
    module_config_def.add_sub_container(lpu_config_def)
    
    # IomLPUEventWinSelect
    param_def = EcucParameterDef(
        "IomLPUEventWinSelect", 
        param_type=EcucParameterType.ENUMERATION
    )
    param_def.definition_ref = "/THA6_AS440_FuSa/Iom/IomModuleConfiguration/IomLPUConfiguration/IomLPUEventWinSelect"
    lpu_config_def.add_parameter(param_def)
    
    return module_def

def reproduce():
    # Load ARXML
    arxml_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/ConfigValue/Iom_Config.arxml")
    parser = ArxmlParser()
    print(f"Loading {arxml_path}...")
    
    # The parser returns a generic Container(AUTOSAR) -> AR-PACKAGE -> ...
    # But parse_ecuc_configuration_values expects ECUC-MODULE-CONFIGURATION-VALUES element
    # We need to manually traverse to find the Iom config
    
    from lxml import etree
    tree = etree.parse(str(arxml_path))
    root = tree.getroot()
    
    # Find ECUC-MODULE-CONFIGURATION-VALUES for Iom
    ns = {'ns': 'http://autosar.org/schema/r4.0'}
    # Try with and without namespace for robustness
    iom_configs = root.findall(".//ns:ECUC-MODULE-CONFIGURATION-VALUES", namespaces=ns)
    if not iom_configs:
         iom_configs = root.findall(".//ECUC-MODULE-CONFIGURATION-VALUES")
         
    target_config_elem = None
    for config in iom_configs:
        short_name = config.find("ns:SHORT-NAME", namespaces=ns)
        if short_name is None:
             short_name = config.find("SHORT-NAME")
             
        if short_name is not None and short_name.text == "Iom":
            target_config_elem = config
            break
            
    if target_config_elem is None:
        print("Error: Could not find Iom configuration in ARXML")
        return

    # Parse configuration
    config = parser.parse_ecuc_configuration_values(target_config_elem)
    print(f"Loaded configuration: {config.short_name}")
    print(f"Top-level containers: {len(config.containers)}")
    def print_hierarchy(containers, indent=0):
        for c in containers:
            print(f"{' ' * indent}Container: {c.short_name}, DefRef: {c.definition_ref}")
            print_hierarchy(c.sub_containers, indent + 2)
            
    print_hierarchy(config.containers)
    
    # Create dummy definition
    module_def = create_dummy_def()
    
    # Setup Renderer
    renderer = Renderer(strict=False)
    renderer.load_module(module_def, config)
    
    # Test Template
    # We want to emulate being inside IomLPUConfiguration_0
    # Container Path: /Iom/IomConfigSet/IomLPUConfiguration_0
    
    # Find the container to use as context
    # Iom -> IomConfigSet -> IomLPUConfiguration_0
    # Note: EcucModuleConfiguration has 'containers' list (top-level)
    
    # Flatten containers to find the one we want (recursively)
    def find_container(containers, name):
        for c in containers:
            if c.short_name == name:
                return c
            found = find_container(c.sub_containers, name)
            if found:
                return found
        return None
        
    context_container = find_container(config.containers, "IomLPUConfiguration_0")
    
    if not context_container:
        print("Error: Could not find container 'IomLPUConfiguration_0'")
        # Debug: list all containers
        def list_cons(cons, indent=0):
            for c in cons:
                print(" " * indent + c.short_name)
                list_cons(c.sub_containers, indent + 2)
        print("Available containers:")
        list_cons(config.containers)
        return

    print(f"Found context container: {context_container.short_name}")
    
    # Construct an XPath that simulates navigating to this container and accessing the parameter
    # Since we can pass a context object to renderer via initial loop or just test xpath directly
    # But renderer.render() starts from module root or provided context_path.
    # The user is likely inside a loop over IomLPUConfiguration.
    
    # Let's try to verify the value of the parameter first
    if "IomLPUEventWinSelect" in context_container.parameter_values:
        param_value = context_container.parameter_values["IomLPUEventWinSelect"].value
        print(f"Direct parameter access: {param_value}")
    else:
        print("Parameter 'IomLPUEventWinSelect' not found in container")
    
    # Now try via Renderer/XPath
    template = '[!"./IomLPUEventWinSelect"!]'
    
    # We can inject the container as the initial context by using a trick or modifying renderer to accept node
    # Or we can just use a large template that iterates to it:
    # [!LOOP "IomConfigSet/IomLPUConfiguration/*"!][!IF "node:name(.)='IomLPUConfiguration_0'"!][!"./IomLPUEventWinSelect"!][!ENDIF][!ENDLOOP]
    
    full_template = """
    [!LOOP "IomModuleConfiguration/IomLPUConfiguration/*"!]
        [!TRACE "context node: " . " name: " . node:name(.)!]
        [!TRACE "parameter path: ./IomLPUEventWinSelect"!]
        [!IF "node:name(.)='IomLPUConfiguration_0'"!]
            Found target!
            Value: [!"./IomLPUEventWinSelect"!]
        [!ELSE!]
            Skipping [!"node:name(.)"!]
        [!ENDIF]
    [!ENDLOOP]
    """
    
    print("\nRendering template...")
    result = renderer.render(full_template, module_name="Iom")
    print("Result:")
    print(result)

if __name__ == "__main__":
    reproduce()
