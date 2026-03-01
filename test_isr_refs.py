import sys
from pathlib import Path

PROJECT_ROOT = Path("/Users/qlwang/Desktop/bsw图形配置工具")
sys.path.append(str(PROJECT_ROOT))

from autosar_configurator.core.workspace_manager import WorkspaceManager

def main():
    workspace = WorkspaceManager()
    dpa_path = Path("/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
    project, failed = workspace.load_project(dpa_path)
    
    os_manager = project.get_manager("Os")
    
    for app in os_manager.configuration.containers:
        if app.short_name.startswith("OsApplication"):
            print(f"App: {app.short_name}")
            for sub in app.sub_containers:
                if sub.short_name.startswith("OsAppIsrRef"):
                    print(f"  - Has IsrRef subcontainer: {sub.short_name}")
                    for ref in sub.references:
                        print(f"    * Ref: {ref.definition_ref} -> {ref.value}")
                        resolved = os_manager.configuration.get_path(ref.value)
                        print(f"    * Resolved: {resolved.short_name if resolved else 'None'}")
                        
if __name__ == "__main__":
    main()
