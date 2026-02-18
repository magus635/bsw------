
import sys
import os
# Add project root to path
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from autosar_configurator.generator.eb.overlay_engine import OverlayEngine
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode

def test_deep_nesting():
    print("--- Test Deep Nesting (Port -> PortConfigSet -> PortContainer -> PortPin -> MSC0_FCLN) ---")
    module_name = "Port"
    
    # Definitions
    module_def = EcucModuleDef(short_name=module_name)
    module_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_name}"
    
    pcs_def = EcucContainerDef(short_name="PortConfigSet")
    pcs_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_name}/PortConfigSet"
    module_def.add_container(pcs_def)
    
    pc_def = EcucContainerDef(short_name="PortContainer")
    pc_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_name}/PortConfigSet/PortContainer"
    pcs_def.add_sub_container(pc_def)
    
    pp_def = EcucContainerDef(short_name="PortPin")
    pp_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_name}/PortConfigSet/PortContainer/PortPin"
    pc_def.add_sub_container(pp_def)
    
    # Configuration
    config = EcucModuleConfiguration(short_name=module_name, definition_ref=f"/AUTOSAR/EcucDefs/{module_name}")
    
    # PortConfigSet
    pcs_val = EcucContainerValue(short_name="PortConfigSet", definition_ref=pcs_def.definition_ref)
    config.add_container(pcs_val)
    
    # PortContainer
    pc_val = EcucContainerValue(short_name="PortContainer_0", definition_ref=pc_def.definition_ref)
    pcs_val.add_sub_container(pc_val)
    
    # PortPin (MSC0_FCLN)
    pp_val = EcucContainerValue(short_name="MSC0_FCLN", definition_ref=pp_def.definition_ref)
    pc_val.add_sub_container(pp_val)
    
    # Build Tree
    engine = OverlayEngine(strict=False)
    root = engine.build_configuration_tree(module_def, config)
    
    print(f"Root: {root.short_name} (path={root.path})")
    
    def find_node(start_node, name):
        if start_node.short_name == name:
            return start_node
        for child in start_node.children:
            res = find_node(child, name)
            if res: return res
        return None

    # Check PortConfigSet
    pcs_node = find_node(root, "PortConfigSet")
    # Note: there might be wrapper and instance. 
    # Since they have same name, find_node returns first found (which is Wrapper added first now).
    
    # Let's find specifically the INSTANCE (child of wrapper)
    # Wrapper is at root.children
    wrapper = None
    for c in root.children:
        if c.short_name == "PortConfigSet" and c.is_wrapper:
            wrapper = c
            break
            
    if not wrapper:
        print("ERROR: PortConfigSet wrapper not found")
        return
        
    print(f"Wrapper: {wrapper.short_name} (path={wrapper.path}, parent={wrapper.parent.path if wrapper.parent else 'None'})")
    
    if not wrapper.children:
        print("ERROR: Wrapper has no children")
        return
        
    pcs_instance = wrapper.children[0]
    print(f"Instance: {pcs_instance.short_name} (path={pcs_instance.path})")
    print(f"Instance Parent: {pcs_instance.parent.path if pcs_instance.parent else 'None'}")
    
    # Check deeply nested node
    pin_node = find_node(pcs_instance, "MSC0_FCLN")
    if pin_node:
        print(f"Pin Node: {pin_node.short_name} (path={pin_node.path})")
        print(f"Pin Parent: {pin_node.parent.path if pin_node.parent else 'None'}")
        
        # Verify no cycle
        curr = pin_node
        path = []
        while curr:
            path.append(curr.short_name)
            curr = curr.parent
            if curr and curr.short_name in path:
                print(f"CYCLE DETECTED: {curr.short_name} is repeated in path {path}")
                break
        print(f"Path to Root: {' -> '.join(path)}")
    else:
        print("Pin Node not found")

if __name__ == "__main__":
    test_deep_nesting()
