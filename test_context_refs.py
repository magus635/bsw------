import sys
from pathlib import Path

PROJECT_ROOT = Path("/Users/qlwang/Desktop/bsw图形配置工具")
sys.path.append(str(PROJECT_ROOT))

from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.eb_template_engine import EBTemplateEngine

def main():
    workspace = WorkspaceManager()
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    project, failed = workspace.load_project(dpa_path)
    
    os_manager = project.get_manager("Os")
    config = os_manager.configuration
    
    app = None
    for c in config.containers:
        if c.short_name == "OsApplication_0":
            app = c
            break
            
    import xml.etree.ElementTree as ET
    from autosar_configurator.generator.eb.overlay_engine import OverlayEngine
    from autosar_configurator.generator.eb.symbol_table import SymbolTable
    
    st = SymbolTable()
    oe = OverlayEngine(symbol_table=st, strict=False)
    
    print("\nTesting Context evaluation:")
    root_node = oe.build_configuration_tree(os_manager.module_def, os_manager.configuration)
    
    app_node = None
    for child in root_node.get_children_recursive():
        if child.short_name == "OsApplication_1":
            app_node = child
            break

    if app_node is not None:
        print("Found OsApplication_1 in context tree:")
        for child in app_node.get_children_list():
            print(f"  - [{child.node_type}] {child.short_name}")
            if child.get_children_list():
                for sub in child.get_children_list():
                    print(f"      - [{sub.node_type}] {sub.short_name}: {sub.get_value()}")
    from autosar_configurator.generator.eb.context import ContextStack
    from autosar_configurator.generator.eb.builtins import BuiltinFunctions
    from autosar_configurator.generator.eb.xpath_engine import XPathEngine
    
    ctx = ContextStack()
    ctx.push(app_node)
    funcs = BuiltinFunctions(st, ctx)
    engine = XPathEngine(st, ctx, funcs)
    
    # Simulate node:order(OsAppAlarmRef/*)
    print("\nEvaluating node:order(OsAppAlarmRef/*, '@index') :")
    isr_refs = engine.evaluate("node:order(OsAppAlarmRef/*, '@index')")
    print(f"Result (len={len(isr_refs) if isinstance(isr_refs, list) else 1}): {isr_refs}")
    
    print("\nEvaluating count(OsAppAlarmRef/*) :")
    count_val = funcs.count(engine.evaluate("OsAppAlarmRef/*"))
    print(f"Result: {count_val}")
    
    print("\nEvaluating node:ref(OsAppAlarmRef/*) in a loop:")
    for ref_node in (isr_refs if isinstance(isr_refs, list) else [isr_refs]):
        target = funcs.node_ref(ref_node)
        print(f"  - {ref_node.short_name} -> {target.short_name if target else 'None'}")
        
    print("\nContext Navigation Test (Inner Loop Context):")
    ref_node = isr_refs[0] if isinstance(isr_refs, list) else isr_refs
    ctx.push(ref_node)
    
    parent_parent = engine.evaluate("../..")    
    pp_node = parent_parent[0] if isinstance(parent_parent, list) else parent_parent
    print(f"  - ../.. short_name: {pp_node.short_name}")
    print(f"  - ../.. index property directly: {getattr(pp_node, 'index', 'NOT_SET')}")
    
    idx = engine.evaluate("../../@index")
    print(f"  - ../../@index evaluates to: {idx}")
    ctx.pop()
    
    print("\nContext Navigation Test (Outer Loop Context):")
    ctx.push(pp_node)
    
    # Let's pretend this node was given index 1 by the LOOP setting its info
    # In the template engine, LOOP sets loop_index!
    idx = getattr(pp_node, 'index', 0)
    print(f"  - Actual getattr(pp_node, 'index', 0) resolves to: {idx}")
    
    # What does num:i(./@index) evaluate to?
    num_i_idx = engine.evaluate("num:i(./@index)")
    print(f"  - num:i(./@index) evaluates to: {num_i_idx}")
    
    # What if the loop index is set?
    ctx.set_loop_info(1, 4) # simulate we are the second item in the loop (index=1)
    
    print(f"  - AFTER set_loop_info(1, 4):")
    this_idx = engine.evaluate("./@index")
    print(f"  - ./@index evaluates to: {this_idx}")
    
    this_index = engine.evaluate("@index")
    print(f"  - @index evaluates to: {this_index}")
    
    num_i_idx = engine.evaluate("num:i(./@index)")
    print(f"  - num:i(./@index) evaluates to: {num_i_idx}")
    
    num_i_var_idx = engine.evaluate("num:i(@index)")
    print(f"  - num:i(@index) evaluates to: {num_i_var_idx}")
    
    ctx.pop()
    
if __name__ == "__main__":
    main()
