import os
import json
from pathlib import Path
from autosar_configurator.core.workspace_manager import WorkspaceManager

def test_valid_json():
    filename = "valid_project.dpa"
    # Create a valid JSON project file
    content = '{"name": "Valid Project", "version": "1.0"}'
    
    with open(filename, 'w') as f:
        f.write(content)
        
    wm = WorkspaceManager()
    
    try:
        print(f"Attempting to load {filename}...")
        project, errors = wm.load_project(Path(filename))
        print("SUCCESS: Loaded valid project successfully!")
        if project.name == "Valid Project":
            print("VERIFIED: Project name correct.")
        else:
            print(f"FAILURE: Project name mismatch. Got '{project.name}'")
    except Exception as e:
        print(f"FAILURE: Failed to load valid JSON: {e}")
    finally:
        if os.path.exists(filename):
            os.remove(filename)

if __name__ == "__main__":
    test_valid_json()
