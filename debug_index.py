#!/usr/bin/env python3
"""Debug script to trace @index behavior for OsApplication containers."""
import sys
sys.path.insert(0, '/Users/qlwang/Desktop/bsw图形配置工具')

from pathlib import Path
from autosar_configurator.core.workspace_manager import WorkspaceManager

ws = WorkspaceManager()
dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
project, failed = ws.load_project(dpa_path)

os_mgr = project.get_manager("Os")
os_module = os_mgr.module_def
os_config = os_mgr.configuration

print(f"Os module containers: {list(os_module.containers.keys())[:10]}")

# Show OsApplication containers in config
print("\n=== OsApplication containers in config ===")
for c in os_config.containers:
    if 'application' in c.short_name.lower() or 'OsApplication' in c.definition_ref:
        params = list(c.parameter_values.keys())
        refs = list(c.reference_values.keys())
        mrefs = list(getattr(c, 'multi_reference_values', {}).keys())
        print(f"  short_name={c.short_name}, def_ref={c.definition_ref}")
        print(f"    params={params[:5]}, refs={refs[:5]}, mrefs={mrefs[:5]}")

# Build overlay tree
from autosar_configurator.generator.eb.symbol_table import SymbolTable
from autosar_configurator.generator.eb.overlay_engine import OverlayEngine

st = SymbolTable()
engine = OverlayEngine(symbol_table=st, strict=False)
root = engine.build_configuration_tree(os_module, os_config)

print("\n=== Os root direct children ===")
for child in root.children:
    print(f"  {child.short_name} (is_wrapper={child.is_wrapper}, index={child.index}, n_children={len(child.children)})")

print("\n=== OsApplication wrapper children ===")
osa_wrapper = root.get_child('OsApplication')
if osa_wrapper:
    print(f"  OsApplication wrapper found with {len(osa_wrapper.children)} children")
    for child in osa_wrapper.children:
        print(f"  {child.short_name}: index={child.index}, parent.short_name={child.parent.short_name if child.parent else None}")
        alarm_wrapper = child.get_child('OsAppAlarmRef')
        if alarm_wrapper:
            print(f"    OsAppAlarmRef wrapper: {len(alarm_wrapper.children)} children, parent={alarm_wrapper.parent.short_name if alarm_wrapper.parent else None}, is_wrapper={alarm_wrapper.is_wrapper}")
else:
    print("  OsApplication wrapper NOT FOUND in root")

print("\n=== OsCounter wrapper ===")
osc_wrapper = root.get_child('OsCounter')
if osc_wrapper:
    print(f"  OsCounter wrapper found with {len(osc_wrapper.children)} children")
    for child in osc_wrapper.children:
        print(f"  {child.short_name}: index={child.index}")
else:
    print("  OsCounter NOT found. Checking root singletons:")
    for c in root.children:
        if 'counter' in c.short_name.lower():
            print(f"    Singleton: {c.short_name} index={c.index}")

print("\n=== Simulate ../../@index ===")
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.xpath_engine import XPathEngine

if osa_wrapper and len(osa_wrapper.children) >= 2:
    app1 = osa_wrapper.children[1]
    print(f"\nProcessing {app1.short_name} (index={app1.index})")

    # Build context stack as the renderer would
    ctx_stack = ContextStack(root_node=root)
    ctx_stack.push(root)              # SELECT context
    ctx_stack.push(app1)              # OsApplication loop, app1
    ctx_stack.set_loop_info(1, 4)     # loop_index=1

    alarm_wrapper = app1.get_child('OsAppAlarmRef')
    if alarm_wrapper and alarm_wrapper.children:
        ref0 = alarm_wrapper.children[0]
        ctx_stack.push(ref0)           # OsAppAlarmRef loop
        ctx_stack.set_loop_info(0, len(alarm_wrapper.children))

        print(f"Stack depth: {len(ctx_stack._stack)}")
        for i, s in enumerate(ctx_stack._stack):
            print(f"  stack[{i}]: context_node={s.context_node.short_name if s.context_node else None}, loop_index={s.loop_index}")

        # Navigate ../../ (with wrapper skipping)
        n = ref0
        print(f"\nStarting from: {n.short_name}")

        # Step 1: ..
        p = n.parent
        print(f"  n.parent = {p.short_name if p else None} (is_wrapper={getattr(p,'is_wrapper',False)})")
        while p and getattr(p, 'is_wrapper', False):
            p = p.parent
        print(f"  After wrapper skip 1: {p.short_name if p else None}")

        # Step 2: ..
        if p:
            p2 = p.parent
            print(f"  p.parent = {p2.short_name if p2 else None} (is_wrapper={getattr(p2,'is_wrapper',False)})")
            while p2 and getattr(p2, 'is_wrapper', False):
                p2 = p2.parent
            print(f"  After wrapper skip 2 (../../ result): {p2.short_name if p2 else None}")

            if p2:
                xe = XPathEngine(st, ctx_stack)
                loop_idx = xe._find_context_loop_index(p2)
                print(f"\n_find_context_loop_index({p2.short_name}) = {loop_idx}")
                print(f"getattr(result, 'index', 0) = {getattr(p2, 'index', 0)}")

                # Check each scope manually
                print("\nManual stack search:")
                stack = ctx_stack._stack
                for i in range(len(stack) - 2, -1, -1):
                    scope = stack[i]
                    ctx_node = scope.context_node
                    print(f"  i={i}: loop_index={scope.loop_index}, ctx_node={ctx_node.short_name if ctx_node else None}")
                    if scope.loop_index < 0:
                        print(f"    -> skip (not loop scope)")
                        continue
                    if ctx_node is p2:
                        print(f"    -> DIRECT MATCH! return {scope.loop_index}")
                        break
                    if ctx_node and ctx_node.parent:
                        cp = ctx_node.parent
                        while cp and getattr(cp, 'is_wrapper', False):
                            cp = cp.parent
                        print(f"    -> ctx_node.parent (skip wrappers) = {cp.short_name if cp else None}")
                        if cp is p2:
                            print(f"    -> PARENT MATCH! return {scope.loop_index}")
                            break
                        else:
                            print(f"    -> no match")

        ctx_stack.pop()
    ctx_stack.pop()
ctx_stack.pop()
ctx_stack.pop()
