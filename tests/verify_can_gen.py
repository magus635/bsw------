
import sys
import os
from pathlib import Path
from lxml import etree

# Add project root to path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

# Mock yaml
try:
    import yaml
except ImportError:
    from unittest.mock import MagicMock
    sys.modules['yaml'] = MagicMock()

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
import autosar_configurator.generator.eb.xpath_engine
print(f"DEBUG: sys.path: {sys.path}")
print(f"DEBUG: xpath_engine file: {autosar_configurator.generator.eb.xpath_engine.__file__}")

from autosar_configurator.generator.generator import CodeGenerator

def run_can_gen():
    xdm_path = Path("/Users/qlwang/Desktop/t1/Def/plugins/Can_THA6_AS440/config/Can.xdm")
    arxml_path = Path("/Users/qlwang/Desktop/t1/ConfigValue/Can_Config.arxml")
    template_dir = Path("/Users/qlwang/Desktop/t1/templates")
    output_base_dir = Path("/Users/qlwang/Desktop/t1/output")
    
    print(f"Loading XDM: {xdm_path}")
    def_parser = EcucDefParser()
    can_def = def_parser.parse_module_def_file(xdm_path)
    
    print(f"Loading ARXML: {arxml_path}")
    config_parser = ArxmlParser()
    tree = etree.parse(str(arxml_path))
    # Find the ECUC-MODULE-CONFIGURATION-VALUES element for Can
    module_config_elem = tree.xpath("//*[local-name()='ECUC-MODULE-CONFIGURATION-VALUES' and *[local-name()='SHORT-NAME' and text()='Can']]")[0]
    can_config = config_parser.parse_ecuc_configuration_values(module_config_elem)
    
    # Create Generator
    generator = CodeGenerator(
        module_def=can_def,
        configuration=can_config,
        project_template_dir=template_dir
    )
    
    # Generate
    generator.generate_all(output_base_dir)
    
    output_file = output_base_dir / "Can" / "src" / "Can_PBcfg.c"
    if output_file.exists():
        print(f"SUCCESS: Generated {output_file}")
        content = output_file.read_text()
        
        # Check CAN4_Tx_Stand_Test0
        print("\nChecking CAN4_Tx_Stand_Test0 in output...")
        start_idx = content.find("/*CAN4_Tx_Stand_Test0*/")
        if start_idx != -1:
            end_idx = content.find("}", start_idx) + 1
            node_content = content[start_idx:end_idx]
            print(node_content)
            
            # Expectations:
            # .fdPaddingEnable should be FALSE
            # .CanFdPaddingValue should be 0xFF (due to line 212 of template)
            if "(boolean)FALSE" in node_content and "0xFFU" in node_content:
                print("\nVERIFIED: CAN4_Tx_Stand_Test0 has padding DISABLED (FALSE, 0xFF).")
            else:
                print("\nISSUE: CAN4_Tx_Stand_Test0 still has padding enabled or incorrect values.")
        else:
            print("Could not find CAN4_Tx_Stand_Test0 in output.")
            
        # Check Can_BaudrateCfgSet_Controller0
        print("\nChecking Can_BaudrateCfgSet_Controller0 in output...")
        br_start = content.find("static CONST(Can_ControllerBaudrateType, CAN_CONST) Can_BaudrateCfgSet_Controller0")
        if br_start != -1:
            br_end = content.find("};", br_start) + 2
            br_content = content[br_start:br_end]
            print(br_content)
            
            if "ControllerBaudRateConfigID" in br_content:
                print("\nVERIFIED: ControllerBaudRateConfigID is present.")
            else:
                print("\nISSUE: ControllerBaudRateConfigID is MISSING!")
        else:
            print("Could not find Can_BaudrateCfgSet_Controller0 in output.")
            
    else:
        print(f"FAILURE: {output_file} not generated.")

if __name__ == "__main__":
    run_can_gen()
