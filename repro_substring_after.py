
import sys
import os
from pathlib import Path

# Add project root to sys.path
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode

def test_substring_after():
    renderer = Renderer(strict=False)
    
    # Create a dummy node with a value
    node = ConfigurationNode(short_name="TestNode", node_type="parameter", path="/TestNode")
    node.value = "SENT_CHANNEL_0"
    
    renderer.render("", module_name="TestModule", initial_variables={"SentChPhyIndex": "SENT_CHANNEL_0"})
    
    renderer._context_stack.push(node)
    
    # Test cases
    exprs = [
        'substring-after("SENT_CHANNEL_0", "SENT")',
        '"substring-after($SentChPhyIndex, \\"SENT\\")"',
        'substring-after(node:name(.), "Test")',
    ]
    
    for expr in exprs:
        try:
            result = renderer._evaluate_expression(expr)
            print(f"Expr: {expr} => Result: {result} (Type: {type(result)})")
        except Exception as e:
            print(f"Expr: {expr} => Error: {e}")

if __name__ == "__main__":
    test_substring_after()
