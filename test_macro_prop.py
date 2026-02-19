
import sys
import os
from pathlib import Path

# Add project root to sys.path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
from autosar_configurator.core.model.definition_model import EcucModuleDef

def test_prop():
    template = """
[!MACRO "SetVar"!][!//
  [!VAR "MyVar" = "'Found'"!][!//
[!ENDMACRO!]
[!CALL "SetVar"!][!//
Result: [!"$MyVar"!]
"""
    renderer = Renderer()
    # Provide a dummy module config to the renderer
    module_def = EcucModuleDef("Test", "/Test/Test")
    module_config = EcucModuleConfiguration("Test", "/Test/Test")
    renderer.load_module(module_def, module_config)
    
    print("--- Input Template ---")
    print(template)
    
    try:
        output = renderer.render(template)
        print(f"\n--- Output ---")
        print(f"'{output.strip()}'")
        if "Found" in output:
            print("\nSUCCESS: Macro variable propagated")
        else:
            print("\nFAILURE: Macro variable lost")
    except Exception as e:
        print(f"\nERROR: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    test_prop()
