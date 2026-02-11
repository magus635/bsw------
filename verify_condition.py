
import sys
import os

# Add project root to path
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode

def verify_condition():
    renderer = Renderer()
    symbol_table = renderer.symbol_table
    
    # Mock Data Model
    root = ConfigurationNode("Root", "module", "/")
    
    # Case 1: Node exists and value is 'true' (string)
    container1 = ConfigurationNode("Container1", "container", "/Container1")
    param1 = ConfigurationNode("AdcResultRegisterManual", "parameter", "/Container1/AdcResultRegisterManual")
    param1.value = "true"
    container1.add_child(param1)
    root.add_child(container1)

    # Case 2: Node exists and value is True (bool)
    container2 = ConfigurationNode("Container2", "container", "/Container2")
    param2 = ConfigurationNode("AdcResultRegisterManual", "parameter", "/Container2/AdcResultRegisterManual")
    param2.value = True
    container2.add_child(param2)
    root.add_child(container2)

    # Case 3: Node exists and value is '1' (string) - Common in ARXML
    container3 = ConfigurationNode("Container3", "container", "/Container3")
    param3 = ConfigurationNode("AdcResultRegisterManual", "parameter", "/Container3/AdcResultRegisterManual")
    param3.value = "1"
    container3.add_child(param3)
    root.add_child(container3)

    # Case 4: Node exists but value is False
    container4 = ConfigurationNode("Container4", "container", "/Container4")
    param4 = ConfigurationNode("AdcResultRegisterManual", "parameter", "/Container4/AdcResultRegisterManual")
    param4.value = False
    container4.add_child(param4)
    root.add_child(container4)

    # Case 5: Node does not exist
    container5 = ConfigurationNode("Container5", "container", "/Container5")
    root.add_child(container5)

    symbol_table.register_module("Root", root)
    
    template = """
Case 1 (Value='true'):
[!SELECT "Container1"!][!//
    Exists: [!"node:exists(./AdcResultRegisterManual)"!]
    Value: '[!"./AdcResultRegisterManual"!]'
    Result: [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!]TRUE[!ELSE!]FALSE[!ENDIF!]
[!ENDSELECT!][!//

Case 2 (Value=True bool):
[!SELECT "Container2"!][!//
    Exists: [!"node:exists(./AdcResultRegisterManual)"!]
    Value: '[!"./AdcResultRegisterManual"!]'
    Result: [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!]TRUE[!ELSE!]FALSE[!ENDIF!]
[!ENDSELECT!][!//

Case 3 (Value='1'):
[!SELECT "Container3"!][!//
    Exists: [!"node:exists(./AdcResultRegisterManual)"!]
    Value: '[!"./AdcResultRegisterManual"!]'
    Result: [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!]TRUE[!ELSE!]FALSE[!ENDIF!]
[!ENDSELECT!][!//

Case 4 (Value=False):
[!SELECT "Container4"!][!//
    Exists: [!"node:exists(./AdcResultRegisterManual)"!]
    Value: '[!"./AdcResultRegisterManual"!]'
    Result: [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!]TRUE[!ELSE!]FALSE[!ENDIF!]
[!ENDSELECT!][!//

Case 5 (Node Missing):
[!SELECT "Container5"!][!//
    Exists: [!"node:exists(./AdcResultRegisterManual)"!]
    Result: [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!]TRUE[!ELSE!]FALSE[!ENDIF!]
[!ENDSELECT!][!//
"""

    print("Starting verification...")
    try:
        result = renderer.render(template, module_name="Root")
        print("Rendering successful!")
        print("-" * 20)
        print(result)
        print("-" * 20)
        
    except Exception as e:
        print(f"ERROR: Rendering failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    verify_condition()
