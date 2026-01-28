
import sys
import os

# Add project path to sys.path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.lexer import Lexer, TokenType

template_path = '/Users/qlwang/Desktop/project/t5/templates/Can/src/Can_PBcfg.c'
with open(template_path, 'r') as f:
    content = f.read()

lexer = Lexer()
tokens = lexer.tokenize(content)

print(f"Total tokens: {len(tokens)}")

# Look for tokens around line 268-280
for i, tok in enumerate(tokens):
    if 260 <= tok.line <= 280:
        print(f"[{i}] Line {tok.line}, Col {tok.column}: {tok.type} | Content: {repr(tok.content)} | Raw: {repr(tok.raw)}")

# Look for any OUTPUT tokens that might evaluate to False
print("\n--- Potential False Outputs ---")
for i, tok in enumerate(tokens):
    if tok.type == TokenType.OUTPUT:
        content = tok.content.strip().lower()
        if content == 'false' or content == '0' or content == 'off':
             print(f"[{i}] Line {tok.line}: OUTPUT with '{tok.content}'")
