
import sys
import os
from pathlib import Path

# Add project root to sys.path
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer, _DEBUG_LOG_PATH
from autosar_configurator.generator.eb.lexer import tokenize
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode

def test_trace():
    print(f"Debug log path: {_DEBUG_LOG_PATH}")
    if os.path.exists(_DEBUG_LOG_PATH):
        os.remove(_DEBUG_LOG_PATH)
        
    symbol_table = SymbolTable()
    renderer = Renderer(strict=False)
    
    # Simple variable trace
    template = '[!TRACE "$MyVar"!]'
    initial_vars = {"MyVar": "HelloWorld"}
    
    print("Testing basic trace...")
    output = renderer.render(template, initial_variables=initial_vars)
    print(f"Output: {repr(output)}")
    
    # Check log
    if os.path.exists(_DEBUG_LOG_PATH):
        with open(_DEBUG_LOG_PATH, 'r') as f:
            log_content = f.read()
        print(f"Log content:\n{log_content}")
    else:
        print("Log file NOT created!")

    # Complex variable trace (the one the user asked about)
    print("\nTesting user specific trace...")
    template2 = '[!TRACE "$CanFD_Controller_Supported"!]'
    initial_vars2 = {"CanFD_Controller_Supported": True}
    output2 = renderer.render(template2, initial_variables=initial_vars2)
    print(f"Output2: {repr(output2)}")
    
    if os.path.exists(_DEBUG_LOG_PATH):
        with open(_DEBUG_LOG_PATH, 'r') as f:
            log_content = f.read()
        print(f"Updated Log content:\n{log_content}")

    # Unquoted variable trace
    print("\nTesting unquoted variable trace...")
    template3 = '[!TRACE $CanFD_Controller_Supported!]'
    output3 = renderer.render(template3, initial_variables=initial_vars2)
    print(f"Output3: {repr(output3)}")

    # Expression trace
    print("\nTesting expression trace...")
    template4 = '[!TRACE "$MyVar" + "_Suffix"!]'
    output4 = renderer.render(template4, initial_variables=initial_vars)
    print(f"Output4: {repr(output4)}")

if __name__ == "__main__":
    test_trace()
