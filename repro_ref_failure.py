import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具')))

from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode
from autosar_configurator.generator.eb.overlay_engine import OverlayEngine
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser

def test_resolve():
    st = SymbolTable()
    oe = OverlayEngine(st)
    
    # Mock data
    # 1. Module Def
    from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucReferenceDef, EcucParameterDef, EcucParameterType
    
    can_def = EcucModuleDef("Can", "/THA6/Can")
    set_def = EcucContainerDef("CanConfigSet", "/THA6/Can/CanConfigSet")
    ctrl_def = EcucContainerDef("CanController", "/THA6/Can/CanConfigSet/CanController")
    ctrl_id_def = EcucParameterDef("CanControllerId", EcucParameterType.INTEGER)
    ctrl_id_def.definition_ref = "/THA6/Can/CanConfigSet/CanController/CanControllerId"
    ctrl_def.parameters["CanControllerId"] = ctrl_id_def
    set_def.sub_containers["CanController"] = ctrl_def
    can_def.containers["CanConfigSet"] = set_def
    
    # 2. Config
    from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue, EcucParameterValue
    
    can_cfg = EcucModuleConfiguration("Can", "/Can/Can")
    set_val = EcucContainerValue("CanConfigSet", "/THA6/Can/CanConfigSet")
    ctrl_val = EcucContainerValue("CanController_0", "/THA6/Can/CanConfigSet/CanController")
    ctrl_val.parameter_values["CanControllerId"] = EcucParameterValue("0", "CanControllerId")
    
    set_val.sub_containers = [ctrl_val]
    can_cfg.containers = [set_val]
    
    # Build tree
    root = oe.build_configuration_tree(can_def, can_cfg)
    
    print(f"Module root path: {root.path}")
    print("Tree structure:")
    def dump(node, indent=0):
        print("  " * indent + f"{node.short_name} ({node.path})")
        for child in node.children.values():
            dump(child, indent + 1)
    dump(root)
    
    # Test resolution
    test_path = "/Can/Can/CanConfigSet/CanController_0"
    resolved = st.resolve_reference(test_path)
    
    if resolved:
        print(f"SUCCESS: Resolved {test_path} to {resolved.path}")
    else:
        print(f"FAILURE: Could not resolve {test_path}")

if __name__ == "__main__":
    test_resolve()
