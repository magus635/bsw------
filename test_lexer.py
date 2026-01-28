#!/usr/bin/env python3
import sys
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from autosar_configurator.generator.eb.lexer import tokenize, TokenType

# 测试 NOCODE 块的 tokenization
template = """[!NOCODE!]
[!INCLUDE "Mcu.m"!]
[!ENDNOCODE!]
[!IF "$test != 0"!]
hello
[!ENDIF!]
"""

print("=== Template ===")
print(repr(template))
print()

tokens = tokenize(template)
print("=== Tokens ===")
for i, tok in enumerate(tokens):
    content = tok.content[:50] if len(tok.content) > 50 else tok.content
    print(f"{i}: {tok.type.name:15} | {repr(content)}")
