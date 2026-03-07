import sys
import logging
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent.parent))

from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

def main():
    workspace = WorkspaceManager()
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    project, _ = workspace.load_project(dpa_path)
    os_manager = project.get_manager("Os")
    
    template_dir = dpa_path.parent / "templates"
    all_configs = {name: (mgr.module_def, mgr.configuration) for name, mgr in project.module_managers.items()}
    generator = CodeGenerator(
        configuration=os_manager.configuration,
        module_def=os_manager.module_def,
        all_configurations=all_configs,
        project_template_dir=template_dir,
        selected_chip="THA6206_LFBGA292"
    )
    generator._setup_eb_renderer()
    
    os_node = generator.renderer._symbol_table.get_by_path('/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os')
    
    def walk_tree(node, indent=0):
        if 'OsTaskTimingProtection' in node.path or 'Task1' in node.path:
            is_wrapper = getattr(node, 'is_wrapper', False)
            print('  ' * indent + node.short_name + f' (type: {node.node_type}, is_wrapper: {is_wrapper}) path: {node.path}')
        for child in getattr(node, 'children', []):
            walk_tree(child, indent + 1)
            
    task_container = os_node.get_child('OsTask')
    if task_container:
        for task in task_container.children:
            if 'Task1' == task.short_name:
                 walk_tree(task, 0)

if __name__ == "__main__":
    main()
