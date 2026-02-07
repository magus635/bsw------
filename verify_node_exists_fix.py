import sys
import os

# Add project root to path
sys.path.insert(0, os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.xpath_engine import XPathEngine

def test_node_exists_xpath():
    print("Initializing test environment...")
    
    # 1. Setup minimal environment
    renderer = Renderer()
    symbol_table = renderer.symbol_table
    
    # Create Root Module 'Can'
    can_module = ConfigurationNode(short_name="Can", node_type="module", path="/Can")
    symbol_table.register_module("Can", can_module)
    
    # Create CanGeneral container
    can_general = ConfigurationNode(short_name="CanGeneral", node_type="container", path="/Can/CanGeneral")
    can_module.add_child(can_general)
    
    # Create CanSetBaudrateApi parameter with value True
    # Important: Ensure value is stored as boolean True
    api_param = ConfigurationNode(short_name="CanSetBaudrateApi", node_type="parameter", 
                                 path="/Can/CanGeneral/CanSetBaudrateApi", value=True)
    can_general.add_child(api_param)
    
    # Initialize Context and Builtins
    context_stack = ContextStack(can_module)
    renderer._context_stack = context_stack
    
    # Manually wire up components usually handled by renderer.render()
    renderer._builtins = BuiltinFunctions(symbol_table, context_stack)
    renderer._builtins.renderer = renderer
    renderer._xpath_engine = XPathEngine(symbol_table, context_stack, renderer._builtins)
    
    print("Environment setup complete.")
    print(f"Symbol Table: {symbol_table.get_all_modules()}")
    print(f"Can Module Children: {can_module.children.keys()}")
    print(f"CanGeneral Children: {can_general.children.keys()}")
    
    # 2. Test node:exists with // path
    path_query = "//CanGeneral/CanSetBaudrateApi"
    print(f"\nTesting node:exists('{path_query}')...")
    
    exists_result = renderer._builtins.node_exists(path_query)
    print(f"node:exists Result: {exists_result}")
    
    if exists_result:
        print("SUCCESS: node:exists found the node via // path")
    else:
        print("FAILURE: node:exists returned False")
        # Debug why
        print("Debugging XPath evaluation...")
        try:
            xpath_res = renderer._xpath_engine.evaluate(path_query, return_node=True)
            print(f"Direct XPath evaluate result: {xpath_res}")
        except Exception as e:
            print(f"XPath evaluate exception: {e}")

    # 3. Test full condition evaluation
    condition = "node:exists(//CanGeneral/CanSetBaudrateApi) and (//CanGeneral/CanSetBaudrateApi ='true')"
    print("\nTesting condition: ", condition)
    
    try:
        raw_cond_result = renderer._evaluate_condition(condition)
        print(f"RAW Condition Result: {raw_cond_result}")
        cond_result = raw_cond_result
        print(f"Condition Result: {cond_result}")
        
        if cond_result:
            print("SUCCESS: Full condition evaluated to True")
        else:
            print("FAILURE: Full condition evaluated to False")
    except Exception as e:
        print(f"Condition evaluation error: {e}")

if __name__ == "__main__":
    test_node_exists_xpath()