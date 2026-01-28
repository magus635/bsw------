
import sys
import os
import re

# Add project path to sys.path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.lexer import Lexer, TokenType

class MockBuiltins:
    def num_i(self, val): return val

class MockContext:
    def has_variable(self, name): return False
    def push(self, node): pass
    def pop(self): pass

# We can partially initialize Renderer
renderer = Renderer()
renderer._context_stack = MockContext()
renderer._builtins = MockBuiltins()
renderer._xpath_engine = type('MockXpath', (), {'evaluate': lambda self, expr, context_node=None: None})()

# The expression we suspect
expr = "/* Can Controller -> array member */"

# Simulate _evaluate_expression logic for comparison
# (Extracted from renderer.py to see where it goes)
try:
    val = renderer._evaluate_expression(expr)
    print(f"Renderer._evaluate_expression({repr(expr)}) -> {repr(val)}")
except Exception as e:
    print(f"Error evaluating {repr(expr)}: {e}")

# Let's see if splitting by '>' happens
def find_top_level_op(s, ops):
    depth = 0
    in_quote = None
    for i in range(len(s)):
        c = s[i]
        if c in ('"', "'"):
            if in_quote == c: in_quote = None
            elif in_quote is None: in_quote = c
        if in_quote: continue
        if c == '(': depth += 1
        elif c == ')': depth -= 1
        if depth == 0:
            for op in ops:
                if s[i:].startswith(op):
                    return op, s[:i], s[i+len(op):]
    return None

op_found = find_top_level_op(expr, ['>', '<', '==', '!=', '>=', '<=', '='])
if op_found:
    op, left, right = op_found
    print(f"Found operator {repr(op)} | Left: {repr(left)} | Right: {repr(right)}")
    # If it tries to float() them:
    try:
        float(None)
    except Exception as e:
        print(f"float(None) raised: {type(e).__name__}: {e}")
        print("This would return False in the renderer's comparison logic!")

