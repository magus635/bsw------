#!/usr/bin/env python3
import sys
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from pathlib import Path
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.lexer import tokenize

# 读取模板
template_path = Path('/Users/qlwang/Desktop/project/t5/templates/Mcu/src/Mcu_PBcfg.c')
template_dir = template_path.parent.parent  # templates/Mcu

print(f"Template dir: {template_dir}")
print(f"Template exists: {template_path.exists()}")

# 检查 Mcu.m 是否存在
mcu_m_path = template_dir / "Mcu.m"
print(f"Mcu.m path: {mcu_m_path}")
print(f"Mcu.m exists: {mcu_m_path.exists()}")

# 创建简单的渲染器测试
renderer = Renderer(strict=False, template_dir=template_dir)

# 测试简单模板
simple_template = """Before NOCODE
[!NOCODE!]
This should not appear
[!ENDNOCODE!]
After NOCODE
"""

print("\n=== Simple NOCODE Test ===")
try:
    result = renderer.render(simple_template)
    print("Result:")
    print(repr(result))
except Exception as e:
    print(f"Error: {e}")
    import traceback
    traceback.print_exc()

# 测试 INCLUDE
print("\n=== INCLUDE Test ===")
include_template = """[!INCLUDE "Mcu.m"!]
After include
"""
try:
    result = renderer.render(include_template)
    print(f"Result length: {len(result)}")
    print(f"Result preview: {result[:200] if result else 'empty'}")
except Exception as e:
    print(f"Error: {e}")
    import traceback
    traceback.print_exc()
