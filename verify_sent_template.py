
import sys
import os
from pathlib import Path

# Add project root to sys.path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from autosar_configurator.core.model.definition_model import EcucModuleDef

def test_sent_snippet():
    # Setup dummy model
    module_def = EcucModuleDef("Sent", "/Sent/Sent")
    module_config = EcucModuleConfiguration("Sent", "/Sent/Sent")
    # We need a context node for the renderer
    root_node = EcucContainerValue("SentConfigSet", "/Sent/Sent/SentConfigSet", None)
    
    renderer = Renderer()
    # Mocking necessary parts for standalone execution
    renderer.load_module(module_def, module_config)
    
    # User's snippet
    template = """
[!VAR "CGCoreUsed" = "'CORE0 CORE1 CORE2'"!][!//
[!FOR "CoreIndex" = "num:i(1)" TO "num:i(2)"!][!//
        [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!]
        [!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!]
        [!IF "text:match($CGCoreUsed, $matchCore)"!] [!// Fetch all strings matching the core.
          [!CODE!]
            /* #Violation: Sent_Cfg_h_REF_1 */
            #define SENT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_ON)
          [!ENDCODE!]
        [!ELSE!]
          [!CODE!]
            /* #Violation: Sent_Cfg_h_REF_1 */
            #define SENT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_OFF)
          [!ENDCODE!]
        [!ENDIF!]
      [!ENDFOR!]
"""
    
    print("--- Input Template ---")
    print(template)
    
    try:
        output = renderer.render(template)
        print("\n--- Rendered Output ---")
        print(output)
        
        # Validate output
        expected_outputs = [
            "#define SENT_CONFIGURED_CORE0                              (STD_ON)",
            "#define SENT_CONFIGURED_CORE1                              (STD_ON)"
        ]
        
        for expected in expected_outputs:
            if expected in output:
                print(f"PASS: Found '{expected}'")
            else:
                print(f"FAIL: Could not find '{expected}'")
                
    except Exception as e:
        print(f"ERROR: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    test_sent_snippet()
