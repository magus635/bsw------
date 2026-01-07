import sys
from pathlib import Path

# Add project root to path
project_root = Path("/Users/qlwang/Desktop/bsw图形配置工具")
sys.path.append(str(project_root))

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode

def test_logic():
    print("Testing logic evaluation...")
    renderer = Renderer(strict=False)
    
    # Mock nodes for Fee and Fls
    fee_node = ConfigurationNode(short_name='Fee', node_type='container', path='/Fee')
    v_page = ConfigurationNode(short_name='FeeVirtualPageSize', node_type='parameter', path='/Fee/FeeVirtualPageSize', value=8)
    fee_node.children['FeeVirtualPageSize'] = v_page
    
    fls_node = ConfigurationNode(short_name='Fls', node_type='container', path='/Fls')
    p_page = ConfigurationNode(short_name='FlsPageSize', node_type='parameter', path='/Fls/FlsPageSize', value=8)
    fls_node.children['FlsPageSize'] = p_page
    
    renderer.symbol_table.register_module('Fee', fee_node)
    renderer.symbol_table.register_module('Fls', fls_node)
    
    # Set current context to Fee
    from autosar_configurator.generator.eb.context import ContextStack
    from autosar_configurator.generator.eb.builtins import BuiltinFunctions
    renderer._context_stack = ContextStack(fee_node)
    renderer._builtins = BuiltinFunctions(renderer.symbol_table, renderer._context_stack)
    
    # Test cases
    test_exprs = [
        "FeeVirtualPageSize mod 8",
        "(FeeVirtualPageSize mod 8)",
        "(8 mod 8) == 0",
        "(9 mod 8) != 0",
        "as:modconf('Fls')[1]/FlsPageSize"
    ]
    
    for expr in test_exprs:
        try:
            if ' == ' in expr or ' != ' in expr:
                result = renderer._evaluate_condition(expr)
            else:
                result = renderer._evaluate_expression(expr)
            print(f"Expression: {expr} -> Result: {result}")
        except Exception as e:
            print(f"Expression: {expr} -> ERROR: {e}")

if __name__ == "__main__":
    test_logic()
