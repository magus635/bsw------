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
    
    template_content = """
    Alarms: [!LOOP "node:order(./OsAlarm/*,'@index')"!][!"name(.)"!]=[!"num:i(./@index)"!], [!ENDLOOP!]
    Counters: [!LOOP "node:order(./OsCounter/*,'@index')"!][!"name(.)"!]=[!"num:i(./@index)"!], [!ENDLOOP!]
    Tasks: [!LOOP "node:order(./OsTask/*,'@index')"!][!"name(.)"!]=[!"num:i(./@index)"!], [!ENDLOOP!]
    ISRs: [!LOOP "node:order(./OsIsr/*,'@index')"!][!"name(.)"!]=[!"num:i(./@index)"!], [!ENDLOOP!]
    """
    
    engine = EBTemplateEngine(strict=False, template_dir=Path("."))
    engine.add_module(os_manager.module_def, os_manager.configuration)
    
    # Inspect the index natively
    os_module = engine.renderer.symbol_table.get_module("Os")
    os_app_wrapper = os_module.get_child("OsApplication")
    if os_app_wrapper:
        print(f"\nOsApplication wrapper: is_wrapper={os_app_wrapper.is_wrapper}, node_type={os_app_wrapper.node_type}")
        children = list(os_app_wrapper.children) if hasattr(os_app_wrapper, 'children') else []
        print(f"  Children count: {len(children)}")
        for app in children[:2]:
            print(f"  App {app.short_name}: node_type={app.node_type}, index={getattr(app, 'index', 'N/A')}")
            print(f"    parent={app.parent.short_name if app.parent else 'None'}, parent.is_wrapper={getattr(app.parent, 'is_wrapper', 'N/A')}")
            # Check alarm ref
            for child_name in list(app.children)[:3] if hasattr(app, 'children') else []:
                c = app.children[child_name] if isinstance(app.children, dict) else child_name
                print(f"    child: {c.short_name if hasattr(c, 'short_name') else c}, type={getattr(c, 'node_type', '?')}, is_wrapper={getattr(c, 'is_wrapper', '?')}")
            
    result = engine.renderer.render(template_content, "Os")
    print("\nRENDERED:\n")
    print(result)

if __name__ == "__main__":
    main()
