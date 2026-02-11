
import sys
import os

# Add project root to path
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode

def test_template_parsing():
    # 1. Setup the Renderer and SymbolTable
    renderer = Renderer()
    symbol_table = renderer.symbol_table
    
    # 2. Mock the Data Model (Symbol Table)
    # We need:
    # - Adc (Module)
    #   - AdcGroupDefinition (container)
    #     - Child 1 (with AdcAnChannelNum = 5)
    #     - Child 2 (with AdcAnChannelNum = 3)
    
    # Create Root Module Node
    adc_module = ConfigurationNode("Adc", "module", "/Adc")
    
    # Create AdcGroupDefinition container
    adc_group_def = ConfigurationNode("AdcGroupDefinition", "container", "/Adc/AdcGroupDefinition")
    adc_module.add_child(adc_group_def)
    
    # Add children to AdcGroupDefinition
    # Child 1
    child1 = ConfigurationNode("GroupDef0", "container", "/Adc/AdcGroupDefinition/GroupDef0")
    # Add AdcAnChannelNum to child 1
    chan_num1 = ConfigurationNode("AdcAnChannelNum", "parameter", "/Adc/AdcGroupDefinition/GroupDef0/AdcAnChannelNum")
    chan_num1.value = 5
    child1.add_child(chan_num1)
    # Important: index attribute for node:ref lookup (mocking internal attribute)
    # In the actual engine, node:ref resolves references. 
    # The template uses `AdcGroupDefinition/*[@index=$GroupDef]`. 
    # This implies the children have an 'index' attribute or we are iterating by index.
    # The snippet: [!FOR "GroupDef" = "num:i(0)" TO "num:i($TotalAdcGroupDef - 1)"!]
    #            [!VAR "AnalogInputChannelNumber" = "node:ref(AdcGroupDefinition/*[@index=$GroupDef])/AdcAnChannelNum"!]
    #
    # Wait, `node:ref` usually takes a PATH or a REFERENCE node.
    # `AdcGroupDefinition/*[@index=$GroupDef]` is an XPath expression returning a node.
    # If `node:ref` receives a NODE, it should probably return it or resolve it if it's a reference.
    # Here `AdcGroupDefinition/*` are containers, not reference parameters.
    # So `node:ref` might be redundant or used to ensure we have a node.
    #
    # However, `*[@index=...]` syntax suggests filtering by an attribute 'index'.
    # ConfigurationNode has an 'index' attribute. Let's set it.
    child1.index = 0
    adc_group_def.add_child(child1)
    
    # Child 2
    child2 = ConfigurationNode("GroupDef1", "container", "/Adc/AdcGroupDefinition/GroupDef1")
    chan_num2 = ConfigurationNode("AdcAnChannelNum", "parameter", "/Adc/AdcGroupDefinition/GroupDef1/AdcAnChannelNum")
    chan_num2.value = 3
    child2.add_child(chan_num2)
    child2.index = 1
    adc_group_def.add_child(child2)

    # Register the module
    symbol_table.register_module("Adc", adc_module)

    # Set external variable $UnitId
    initial_vars = {"UnitId": 0}
    
    # 3. Define the template snippet
    # We include a dummy definition for CG_FindHwUnitChannelID to satisfy the CALL
    # The macro must set 'ChannelPosition' variable as the snippet uses it.
    
    macro_def = """
[!MACRO "CG_FindHwUnitChannelID", "ChannelListName", "ChannelName"!]
    [!VAR "ChannelPosition" = "$ChannelName"!]
[!ENDMACRO!]
"""

    user_snippet = """
/* Internal channel mask from group definition - derived from the tool */
                    [!NOCODE!][!//
                        [!VAR "TotalAdcGroupDef"= "num:i(count(AdcGroupDefinition/*))"!][!//
                        [!VAR "GroupMask" = "num:i(0)"!][!//
                        [!VAR "ChIndex" = "num:i(1)"!][!//
                        [!VAR "ShiftMask" = "num:i(0)"!][!//
                        [!VAR "EcuListName" = "concat('Adc.AdcChannels_Adc', $UnitId)"!][!//
                        [!FOR "GroupDef" = "num:i(0)" TO "num:i($TotalAdcGroupDef - 1)"!][!//
                            [!VAR "AnalogInputChannelNumber" = "node:ref(AdcGroupDefinition/*[@index=$GroupDef])/AdcAnChannelNum"!][!//
                            [!CALL "CG_FindHwUnitChannelID", "ChannelListName" = "$EcuListName", "ChannelName" = "$AnalogInputChannelNumber"!][!//
                            [!VAR "ChannelNumber"= "$ChannelPosition"!][!//
                            [!VAR "ShiftMask" = "bit:shl(num:i($ChIndex), num:i($ChannelNumber))"!][!//
                            [!VAR "GroupMask" = "bit:or(num:i($GroupMask), num:i($ShiftMask))"!][!//
                        [!ENDFOR!][!//
                    [!ENDNOCODE!][!//
                    (uint16)[!"num:inttohex($GroupMask)"!],
"""
    
    full_template = macro_def + user_snippet
    
    print("Starting rendering...")
    try:
        # Render
        # We start with context at Adc module root to allow relative paths like AdcGroupDefinition/*
        result = renderer.render(full_template, module_name="Adc", initial_variables=initial_vars)
        print("Rendering successful!")
        print("-" * 20)
        print(result)
        print("-" * 20)
        
        # Verify the result
        # Channel 5 and Channel 3
        # (1 << 5) | (1 << 3) = 32 | 8 = 40 = 0x28
        if "0x28" in result or "0X28" in result:
             print("SUCCESS: Calculation is correct (found 0x28)")
        else:
             print("WARNING: Result might be incorrect, expected 0x28")
             
    except Exception as e:
        print(f"ERROR: Rendering failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    test_template_parsing()
