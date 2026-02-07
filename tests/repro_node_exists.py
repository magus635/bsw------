
import sys
import os

# Add project root to path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

# Mock yaml module if missing to allow imports
try:
    import yaml
except ImportError:
    from unittest.mock import MagicMock
    sys.modules['yaml'] = MagicMock()

from autosar_configurator.generator.eb.xpath_engine import XPathEngine
from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.builtins import BuiltinFunctions

def test_node_exists():
    symbol_table = SymbolTable()
    root = ConfigurationNode("root", "module", "/root")
    
    container = ConfigurationNode("TestContainer", "container", "/root/TestContainer")
    root.add_child(container)
    
    # Existing parameter with value
    p1 = ConfigurationNode("ParamWithValue", "parameter", "/root/TestContainer/ParamWithValue", value="10")
    container.add_child(p1)
    
    # Parameter with None value (like an optional param not in config)
    p2 = ConfigurationNode("ParamWithNone", "parameter", "/root/TestContainer/ParamWithNone", value=None)
    container.add_child(p2)
    
    context_stack = ContextStack(container)
    builtins = BuiltinFunctions(symbol_table, context_stack)
    
    print("Testing node:exists behavior...")
    
    # Test 1: Parameter with value
    exists_1 = builtins.node_exists(p1)
    print(f"ParamWithValue exists: {exists_1} (Expected: True)")
    
    # Test 2: Parameter with None value
    exists_2 = builtins.node_exists(p2)
    print(f"ParamWithNone exists: {exists_2} (Expected: False - currently returns True)")
    
    # Test 3: Via path lookup
    exists_p1_path = builtins.node_exists("ParamWithValue")
    print(f"Path ParamWithValue exists: {exists_p1_path} (Expected: True)")
    
    exists_p2_path = builtins.node_exists("ParamWithNone")
    print(f"Path ParamWithNone exists: {exists_p2_path} (Expected: False - currently returns True)")

    if exists_2 == True:
        print("\nREPRODUCED: node:exists returns True for parameter with None value.")
        sys.exit(0)
    else:
        print("\nNOT REPRODUCED: node:exists returned False.")
        sys.exit(1)

if __name__ == "__main__":
    test_node_exists()
