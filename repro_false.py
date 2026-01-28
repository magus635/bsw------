
import sys
import os

# Add project path to sys.path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.lexer import Lexer, TokenType

template = "[!/* Can Controller -> array member */!]"

lexer = Lexer()
tokens = lexer.tokenize(template)
for tok in tokens:
    print(f"Token: {tok.type} | Content: {repr(tok.content)}")

renderer = Renderer()
# Mock symbol table and context stack to avoid render() error
renderer._context_stack = renderer.overlay_engine.context_stack
renderer._builtins = renderer.overlay_engine.builtins
renderer._xpath_engine = renderer.overlay_engine.xpath_engine

for tok in tokens:
    if tok.type == TokenType.OUTPUT:
        val = renderer._evaluate_expression(tok.content)
        print(f"Expression: {repr(tok.content)} | Value: {repr(val)} | Type: {type(val)}")
