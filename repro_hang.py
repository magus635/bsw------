import sys
from pathlib import Path

# Add project root to path
project_root = Path("/Users/qlwang/Desktop/bsw图形配置工具")
sys.path.append(str(project_root))

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode

def test_hang():
    print("Testing hang reproduction...")
    renderer = Renderer(strict=False)
    
    # Mock node
    node = ConfigurationNode(short_name='Block', node_type='container', path='/Block')
    from autosar_configurator.generator.eb.context import ContextStack
    from autosar_configurator.generator.eb.builtins import BuiltinFunctions
    renderer._context_stack = ContextStack(node)
    renderer._builtins = BuiltinFunctions(renderer.symbol_table, renderer._context_stack)
    renderer._xpath_engine = None # Use fallback
    
    # This expression should trigger the loop if my theory is correct:
    # count(Block/*)
    # It has '(' and '/' but it ends with ')' so it SHOULD be caught by the function call check.
    # What if it's count(Block/*) + 1?
    expr = "count(Block/*) + 1"
    
    print(f"Evaluating: {expr}")
    try:
        result = renderer._evaluate_expression(expr)
        print(f"Result: {result}")
    except RecursionError:
        print("❌ FAILED: RecursionError detected (Infinite Loop)")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    test_hang()
