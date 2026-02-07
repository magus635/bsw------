
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
from autosar_configurator.generator.eb.symbol_table import SymbolTable
from autosar_configurator.generator.eb.context import ContextStack

def test_parens():
    symbol_table = SymbolTable()
    # Create a dummy root node for the context stack
    from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
    root = ConfigurationNode("root", "module", "/root")
    context_stack = ContextStack(root) 
    
    engine = XPathEngine(symbol_table, context_stack)
    
    # Test cases
    cases = [
        # Simple OR without parens (Should pass)
        ("1 = 1 or 2 = 3", True),
        # Simple AND without parens (Should pass)
        ("1 = 1 and 2 = 2", True),
        # Parens around single condition (Should FAIL currently)
        ("(1 = 1)", True),
        # Parens in complex logic (Should FAIL currently)
        ("(1 = 1) or (2 = 3)", True),
        # Nested parens (Should FAIL currently)
        ("((1 = 1))", True),
        # Mixed parens and Logic
        ("(1 = 1) and (2 = 2)", True)
    ]
    
    print("Running XPath Parentheses Tests...")
    failures = 0
    for expr, expected in cases:
        try:
            result = engine._evaluate_condition(expr)
            status = "PASS" if result == expected else "FAIL"
            if status == "FAIL": failures += 1
            print(f"Expression: {expr:<30} | Expected: {expected} | Got: {result} | {status}")
        except Exception as e:
            print(f"Expression: {expr:<30} | Error: {e}")
            failures += 1

    if failures == 0:
        print("\nAll tests passed!")
        sys.exit(0)
    else:
        print(f"\n{failures} tests failed.")
        sys.exit(1)

if __name__ == "__main__":
    test_parens()
