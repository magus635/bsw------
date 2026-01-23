
import unittest
import os
import json
from pathlib import Path
from autosar_configurator.core.workspace_manager import WorkspaceManager

class TestProjectLoadError(unittest.TestCase):
    def setUp(self):
        self.bad_file = Path("test_bad_project.dpa")
        # Write invalid JSON (like an XML file)
        with open(self.bad_file, "w") as f:
            f.write("<project><name>Bad</name></project>")
            
    def tearDown(self):
        if self.bad_file.exists():
            os.remove(self.bad_file)
            
    def test_load_bad_json(self):
        manager = WorkspaceManager()
        print(f"\nAttempting to load invalid JSON from {self.bad_file}...")
        try:
            manager.load_project(self.bad_file)
            print("❌ Failure: Should have raised an exception")
        except json.JSONDecodeError:
            print("✅ Success (Reproduction): Catching raw json.JSONDecodeError as expected behavior before fix.")
            # Once fixed, we might expect a ValueError instead of raw JSON error, 
            # but for reproduction, seeing this is good.
        except ValueError as e:
            print(f"ℹ️ Caught ValueError: {e}")
            if "Invalid project file" in str(e) or "Expecting property name" in str(e): 
                 print("✅ Validated clean error message.")
        except Exception as e:
            print(f"❌ Unexpected exception type: {type(e).__name__}: {e}")

if __name__ == "__main__":
    unittest.main()
