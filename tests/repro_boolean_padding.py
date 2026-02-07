
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

def test_boolean_comparison():
    symbol_table = SymbolTable()
    root = ConfigurationNode("root", "module", "/root")
    
    # Create a controller with FD support set to 1 (like in ARXML)
    controller = ConfigurationNode("CanController_0", "container", "/root/CanController_0")
    fd_support = ConfigurationNode("CanFDSupport", "parameter", "/root/CanController_0/CanFDSupport")
    fd_support.value = "1" # ARXML often gives strings or integers that look like "1"
    controller.add_child(fd_support)
    root.add_child(controller)
    
    context_stack = ContextStack(controller) 
    engine = XPathEngine(symbol_table, context_stack)
    
    # Test cases
    cases = [
        # This is what's in the template: CanFDSupport = 'true'
        ("CanFDSupport = 'true'", True),
        # Numeric equality
        ("CanFDSupport = 1", True),
        ("CanFDSupport = '1'", True),
    ]
    
    print("Running XPath Boolean Comparison Tests...")
    failures = 0
    for expr, expected in cases:
        try:
            # We want to test how _evaluate_condition handles these
            # evaluate() for an IF condition will call _evaluate_condition
            result = engine._evaluate_condition(expr)
            status = "PASS" if result == expected else "FAIL"
            if status == "FAIL": failures += 1
            print(f"Expression: {expr:<30} | Expected: {expected} | Got: {result} | {status}")
        except Exception as e:
            print(f"Expression: {expr:<30} | Error: {e}")
            failures += 1

    # Also test the count() expression from the template
    # (num:i(count(../../CanController/*[CanFDSupport ='true'])) > 0)
    # Mapping to our test structure: count(/root/CanController_0[CanFDSupport = 'true'])
    engine_root = XPathEngine(symbol_table, ContextStack(root))
    expr_count = "count(CanController_0[CanFDSupport = 'true'])"
    try:
        count_res = engine_root.evaluate(expr_count)
        status = "PASS" if count_res == 1 else "FAIL"
        if status == "FAIL": failures += 1
        print(f"Expression: {expr_count:<30} | Expected: 1 | Got: {count_res} | {status}")
    except Exception as e:
        print(f"Expression: {expr_count:<30} | Error: {e}")
        failures += 1

    if failures == 0:
        print("\nAll tests passed!")
        sys.exit(0)
    else:
        print(f"\n{failures} tests failed.")
        sys.exit(1)

if __name__ == "__main__":
    test_boolean_comparison()
