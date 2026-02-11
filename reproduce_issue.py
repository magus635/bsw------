import sys
import os

# Add project root to path
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode

def test_template_parsing():
    renderer = Renderer()
    symbol_table = renderer.symbol_table
    
    # Mock Data Model
    root = ConfigurationNode("Root", "module", "/")
    
    # AdcConfigSet container
    adc_config_set = ConfigurationNode("AdcConfigSet", "container", "/AdcConfigSet")
    root.add_child(adc_config_set)
    
    symbol_table.register_module("Root", root)
    
    # Mock ECU Resources
    ecu_resources = {
        'Resource.NumOfCores': 2
    }
    
    # Initial Variables
    initial_vars = {
        'Var_AdcConfigShortName': '_',  # Simulating the underscore issue
        'AdcHwUnitMappedCore0': 1,
        'AdcHwUnitMappedCore1': 0,
        'Var_CoreIdx': 0 # Initialize loop var? No, FOR loop does it.
    }
    
    template = """
[!/* Container: AdcConfiguration */!][!//
/*
ADC configuration data set
*/
[!INDENT "0"!][!//
const Adc_ConfigType Adc_ConfigSet[!"$Var_AdcConfigShortName"!][ADC_CONFIG_COUNT] =
{
    [!INDENT "4"!][!//
    [!SELECT "AdcConfigSet"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i(0)"!][!//
                [!IF "$Var_CoreIdx = num:i(0)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore0)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore1)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore2)"!][!//
                [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
                    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore3)"!][!//
                [!ENDIF!][!//
                [!IF "num:i($CoreUsedForAdcHwUnitFlg) != num:i(0)"!][!//
                    /* ADC configuration information of core[!"num:i($Var_CoreIdx)"!] */
                    &Adc_ConfigSetCore[!"num:i($Var_CoreIdx)"!][!//
                [!ELSE!][!//
                    /* No configuration information for core[!"num:i($Var_CoreIdx)"!] */
                    NULL_PTR[!//
                [!ENDIF!][!//
                [!IF "num:i($Var_CoreIdx) < num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                    ,
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
            [!/* Line feed */!]
        },
        /* Pointer to Adc HwUnit mapped to core configuration */
        &Adc_HwUnitToCoreMap[0]
        [!ENDINDENT!][!//
    }
    [!ENDSELECT!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
[!//
[!ENDSELECT!][!//
"""

    print("Starting rendering...")
    try:
        # Pass ecu_resources
        result = renderer.render(template, module_name="Root", initial_variables=initial_vars, ecu_resources=ecu_resources)
        print("Rendering successful!")
        print("-" * 20)
        print(result)
        print("-" * 20)
        
    except Exception as e:
        print(f"ERROR: Rendering failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    test_template_parsing()