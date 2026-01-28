#!/usr/bin/env python3
import sys
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from pathlib import Path
from autosar_configurator.generator.eb.renderer import Renderer

# 读取模板
template_path = Path('/Users/qlwang/Desktop/project/t5/templates/Mcu/src/Mcu_PBcfg.c')
template_dir = template_path.parent.parent  # templates/Mcu

with open(template_path, 'r', encoding='utf-8') as f:
    template = f.read()

print(f"Template length: {len(template)} chars, {len(template.splitlines())} lines")

# 创建渲染器
renderer = Renderer(strict=False, template_dir=template_dir)

print("\n=== Rendering full template (no config) ===")
try:
    result = renderer.render(template)
    print(f"Result length: {len(result)} chars, {len(result.splitlines())} lines")
    print("\n=== First 100 lines of result ===")
    for i, line in enumerate(result.splitlines()[:100]):
        print(f"{i+1:4}: {line}")
except Exception as e:
    print(f"Error: {e}")
    import traceback
    traceback.print_exc()
