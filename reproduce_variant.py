
import sys
import os

# Add project root to path
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode

def reproduce_variant_issue():
    renderer = Renderer()
    symbol_table = renderer.symbol_table
    
    # 1. Mock Data Model
    root = ConfigurationNode("Adc", "module", "/Adc")
    symbol_table.register_module("Adc", root)
    
    # 2. Set Variant to "Default"
    # This simulates what happens when project has a default variant
    # We need to access builtins through renderer (renderer creates them on first use or we set them)
    # Actually, EBTemplateEngine usually handles this. Let's do it manually on renderer.
    
    # Initialize builtins first
    renderer._builtins = None # Force re-init in render call if needed, or init manually
    
    # We will use render() which initializes builtins. 
    # But we need to inject the variant. 
    # Renderer.load_module() sets _variant.
    renderer._variant = "Default"
    
    # 3. The Template Snippet
    # Note: We need a mock "Adc_HwUnitResultHandlingMethodEnStatus" macro or just comment it out for this test
    # since we are testing the variant logic.
    template = """
[!VAR "VariantSize" = "num:i(variant:size())"!]
[!VAR "VariantName" = "variant:name()"!]
DEBUG: Size=[!"$VariantSize"!], Name='[!"$VariantName"!]'

[!IF "num:i(variant:size()) != num:i(0)"!][!//
    [!VAR "Var_AdcConfigShortName"="concat('_', variant:name())"!][!//
[!ELSE!][!//
    [!VAR "Var_AdcConfigShortName"="''"!][!//
[!ENDIF!][!//
DEBUG: Resulting Suffix='[!"$Var_AdcConfigShortName"!]'
"""

    print("Starting variant reproduction...")
    try:
        # Render
        # Passing module_name to ensure context is set
        result = renderer.render(template, module_name="Adc")
        print("Rendering successful!")
        print("-" * 20)
        print(result)
        print("-" * 20)
        
        if "Suffix='_'" in result:
             print("SUCCESS: Reproduced the issue (Suffix is '_')")
        elif "Suffix=''" in result:
             print("FAILED: Suffix is empty (Correct behavior?)")
        else:
             print(f"Unknown result")
             
    except Exception as e:
        print(f"ERROR: Rendering failed: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    reproduce_variant_issue()
