import os
import json
from pathlib import Path
from autosar_configurator.core.workspace_manager import WorkspaceManager

def test_single_quote_json():
    filename = "bad_project.dpa"
    # Create a project file with Python-style dictionary repr (single quotes)
    # This causes: Expecting property name enclosed in double quotes
    content = "{'name': 'Bad Project', 'version': '1.0'}"
    
    with open(filename, 'w') as f:
        f.write(content)
        
    wm = WorkspaceManager()
    
    try:
        print(f"Attempting to load {filename}...")
        project, errors = wm.load_project(Path(filename))
        print("SUCCESS: Loaded project successfully (as expected with fix)!")
        print(f"Project Name: {project.name}")
    except ValueError as e:
        print(f"FAILURE: Should have loaded, but failed with: {e}")
    except Exception as e:
        print(f"CAUGHT UNEXPECTED ERROR: {type(e).__name__}: {e}")
    finally:
        if os.path.exists(filename):
            os.remove(filename)

if __name__ == "__main__":
    test_single_quote_json()
