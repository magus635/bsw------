import sys
from pathlib import Path
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.xpath_engine import XPathEngine
from autosar_configurator.generator.eb.context import ContextStack

def test_engine():
    workspace = WorkspaceManager()
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    project, failed = workspace.load_project(dpa_path)
    os_manager = project.get_manager("Os")
    
    r = Renderer(strict=False)
    r.load_module(os_manager.module_def, os_manager.configuration)
    
    context = ContextStack()
    context.push(os_manager.configuration)
    
    engine = XPathEngine(r.symbol_table, context)
    
    alarms = engine.evaluate("/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsAlarm", return_node=True)
    if not isinstance(alarms, list):
         alarms = [alarms] if alarms else []
    
    print(f"\nAlarms nodes found: {len(alarms)}")
    for a in alarms[:2]:
         print(f"  {a.short_name}")
         children = getattr(a, 'children', [])
         print(f"    Children count: {len(children)}")
         for c in children[:2]:
              print(f"      {c.short_name}")

test_engine()
