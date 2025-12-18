"""
Test Suite for DefFileScanner
Functionality: Verifies discovery of both .arxml and .xdm definition files.
"""
import sys
import unittest
import tempfile
import shutil
from pathlib import Path

# Add parent directory to path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.config_manager import DefFileScanner

class TestDefFileScanner(unittest.TestCase):
    def setUp(self):
        self.test_dir = tempfile.mkdtemp()
        self.root = Path(self.test_dir)
        
        # Create dummy files
        self.files = [
            "Adc.arxml",            # Standard DEF
            "Dio.xdm",              # EB DEF
            "Can_Config.arxml",     # Config (Should be ignored)
            "Mcu_rec.arxml",        # Rec (Should be ignored)
            "subdir/Spi.xdm"        # Nested EB DEF
        ]
        
        for f in self.files:
            path = self.root / f
            path.parent.mkdir(parents=True, exist_ok=True)
            path.touch()
            
    def tearDown(self):
        shutil.rmtree(self.test_dir)
        
    def test_scanner(self):
        """Test scanning for definitions"""
        results = DefFileScanner.find_def_files([self.root])
        
        # Should find: Adc, Dio, Spi
        self.assertIn("Adc", results)
        self.assertIn("Dio", results)
        self.assertIn("Spi", results)
        
        # Should NOT find: Can_Config, Mcu_rec
        self.assertNotIn("Can", results) # Can_Config
        self.assertNotIn("Mcu", results) # Mcu_rec
        
        # Check extensions
        self.assertTrue(str(results["Adc"]).endswith(".arxml"))
        self.assertTrue(str(results["Dio"]).endswith(".xdm"))
        self.assertTrue(str(results["Spi"]).endswith(".xdm"))

if __name__ == '__main__':
    unittest.main()
