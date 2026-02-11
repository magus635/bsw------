
import sys
import os

# Add project root to path
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode

def verify_hierarchy():
    renderer = Renderer()
    symbol_table = renderer.symbol_table
    
    # Mock Data Model Structure
    # Root -> AdcConfigSet -> AdcHwUnit -> AdcChannel
    
    root = ConfigurationNode("Adc", "module", "/Adc")
    
    # 1. Grandparent (where AdcResultHandlingImplementation resides?)
    # Assuming AdcHwUnit level
    hw_unit = ConfigurationNode("AdcHwUnit", "container", "/Adc/AdcConfigSet/AdcHwUnit")
    
    # Param at Grandparent level
    dma_param = ConfigurationNode("AdcResultHandlingImplementation", "parameter", "/Adc/AdcConfigSet/AdcHwUnit/AdcResultHandlingImplementation")
    dma_param.value = "DMA_MODE"
    hw_unit.add_child(dma_param)
    
    # 2. Parent (AdcGroup?) - just a container in between
    group = ConfigurationNode("AdcGroup", "container", "/Adc/AdcConfigSet/AdcHwUnit/AdcGroup")
    hw_unit.add_child(group)
    
    # 3. Child (Current Context - AdcChannel?)
    # Case A: Parameter exists and is true
    channel_a = ConfigurationNode("AdcChannel_A", "container", "/Adc/AdcConfigSet/AdcHwUnit/AdcGroup/AdcChannel_A")
    res_reg_a = ConfigurationNode("AdcResultRegisterManual", "parameter", "/Adc/AdcConfigSet/AdcHwUnit/AdcGroup/AdcChannel_A/AdcResultRegisterManual")
    res_reg_a.value = "true"
    channel_a.add_child(res_reg_a)
    group.add_child(channel_a)

    # Case B: Parameter exists and is '1'
    channel_b = ConfigurationNode("AdcChannel_B", "container", "/Adc/AdcConfigSet/AdcHwUnit/AdcGroup/AdcChannel_B")
    res_reg_b = ConfigurationNode("AdcResultRegisterManual", "parameter", "/Adc/AdcConfigSet/AdcHwUnit/AdcGroup/AdcChannel_B/AdcResultRegisterManual")
    res_reg_b.value = "1"
    channel_b.add_child(res_reg_b)
    group.add_child(channel_b)

    symbol_table.register_module("Adc", root)
    
    # Initial vars needed for the template snippet
    initial_vars = {
        "Var_DmaModeEn": "STD_ON",
        "UnitId": "0",
        "SymbolicName": "AdcCh1"
    }

    # The Template to Test
    # Context should be set to the Channel node
    template = """
Case A (Value='true'):
[!SELECT "AdcConfigSet/AdcHwUnit/AdcGroup/AdcChannel_A"!][!//
    DEBUG: Current Path: [!"node:path(.)"!]
    DEBUG: ../../AdcResultHandlingImplementation: '[!"../../AdcResultHandlingImplementation"!]'
    DEBUG: node:exists(./AdcResultRegisterManual): [!"node:exists(./AdcResultRegisterManual)"!]
    DEBUG: ./AdcResultRegisterManual: '[!"./AdcResultRegisterManual"!]'
    
    [!IF "($Var_DmaModeEn = 'STD_ON')"!][!//
        [!IF "(../../AdcResultHandlingImplementation = 'DMA_MODE')"!][!//
            [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!][!//
                RESULT: MATCHED (Correct)
            [!ELSE!][!//
                RESULT: FAILED (Inner IF)
            [!ENDIF!][!//
        [!ELSE!][!//
            RESULT: FAILED (Middle IF - DMA Mode check)
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//

Case B (Value='1'):
[!SELECT "AdcConfigSet/AdcHwUnit/AdcGroup/AdcChannel_B"!][!//
    DEBUG: Current Path: [!"node:path(.)"!]
    DEBUG: ../../AdcResultHandlingImplementation: '[!"../../AdcResultHandlingImplementation"!]'
    DEBUG: node:exists(./AdcResultRegisterManual): [!"node:exists(./AdcResultRegisterManual)"!]
    DEBUG: ./AdcResultRegisterManual: '[!"./AdcResultRegisterManual"!]'

    [!IF "($Var_DmaModeEn = 'STD_ON')"!][!//
        [!IF "(../../AdcResultHandlingImplementation = 'DMA_MODE')"!][!//
            [!IF "(node:exists(./AdcResultRegisterManual) and (./AdcResultRegisterManual = 'true'))"!][!//
                RESULT: MATCHED (Correct)
            [!ELSE!][!//
                RESULT: FAILED (Inner IF)
            [!ENDIF!][!//
        [!ELSE!][!//
            RESULT: FAILED (Middle IF - DMA Mode check)
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
"""

    print("Starting hierarchy verification...")
    try:
        # Start context at Root
        result = renderer.render(template, module_name="Adc", initial_variables=initial_vars)
        print("Rendering successful!")
        print("-" * 20)
        print(result)
        print("-" * 20)
        
    except Exception as e:
        print(f"ERROR: Rendering failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    verify_hierarchy()
