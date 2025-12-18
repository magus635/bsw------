
import unittest
import tempfile
import shutil
import json
import os
from pathlib import Path
from autosar_configurator.generator.generator import CodeGenerator
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue, EcucParameterValue

class MockModuleDef:
    pass

class TestIncrementalGeneration(unittest.TestCase):
    def setUp(self):
        self.test_dir = tempfile.mkdtemp()
        self.output_dir = Path(self.test_dir) / "output"
        self.output_dir.mkdir()
        
    def tearDown(self):
        shutil.rmtree(self.test_dir)

    def create_mock_config(self):
        config = EcucModuleConfiguration(short_name="TestModule", definition_ref="/Def/TestModule")
        
        # Container 1
        c1 = EcucContainerValue(short_name="Container1", definition_ref="/Def/Container1")
        c1.parameter_values["Param1"] = EcucParameterValue(definition_ref="/Def/Param1", value=10)
        config.add_container(c1)
        
        return config

    def test_fingerprint_stability(self):
        config = self.create_mock_config()
        gen = CodeGenerator(MockModuleDef(), config)
        hash1 = gen._calculate_fingerprint()
        
        # Same config, same hash
        hash2 = gen._calculate_fingerprint()
        self.assertEqual(hash1, hash2)
        
        # Clone (manual) should produce same hash
        config2 = self.create_mock_config()
        gen2 = CodeGenerator(MockModuleDef(), config2)
        hash3 = gen2._calculate_fingerprint()
        self.assertEqual(hash1, hash3)

    def test_fingerprint_change(self):
        config = self.create_mock_config()
        gen = CodeGenerator(MockModuleDef(), config)
        hash1 = gen._calculate_fingerprint()
        
        # Modify param
        config.containers[0].parameter_values["Param1"].value = 20
        hash2 = gen._calculate_fingerprint()
        
        self.assertNotEqual(hash1, hash2)

    def test_generate_skip(self):
        # Create generator with mock templates logic (since we don't have templates)
        config = self.create_mock_config()
        gen = CodeGenerator(MockModuleDef(), config)
        
        # Mock methods that write files to avoid needing actual templates
        gen.generate_config_header = lambda p: (p / "TestModule_Cfg.h").touch()
        gen.generate_lcfg_source = lambda p: (p / "TestModule_Lcfg.c").touch()
        gen.generate_pbcfg_source = lambda p: (p / "TestModule_PBcfg.c").touch()
        
        # 1. First Run: Should generate
        result = gen.generate_all(self.output_dir)
        self.assertTrue(result)
        self.assertTrue((self.output_dir / "TestModule_Cfg.h").exists())
        self.assertTrue((self.output_dir / ".TestModule.meta").exists())
        
        # 2. Second Run: Should skip
        result = gen.generate_all(self.output_dir)
        self.assertFalse(result)
        
        # 3. Force Run: Should generate
        result = gen.generate_all(self.output_dir, force=True)
        self.assertTrue(result)
        
        # 4. Modify and Run: Should generate
        config.containers[0].parameter_values["Param1"].value = 99
        result = gen.generate_all(self.output_dir)
        self.assertTrue(result)
        
        # 5. Verify Meta updated
        with open(self.output_dir / ".TestModule.meta") as f:
            meta = json.load(f)
            self.assertEqual(meta['hash'], gen._calculate_fingerprint())

if __name__ == '__main__':
    unittest.main()
