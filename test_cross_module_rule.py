"""
Test Suite for Cross-Module Validation
Functionality: Verifies that Python-based rules can be loaded and access cross-module data.
"""
import sys
import unittest
import tempfile
import shutil
from pathlib import Path
from unittest.mock import MagicMock

# Add parent directory to path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.validation_engine import ValidationEngine, ValidationSeverity, ValidationRule
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
from autosar_configurator.core.model.definition_model import EcucModuleDef

# Define a cross-module rule class to be written to a file
CROSS_MODULE_RULE_CONTENT = """
from autosar_configurator.core.validation_engine import ValidationRule, ValidationResult, ValidationSeverity

class CheckDependencyRule(ValidationRule):
    def __init__(self):
        super().__init__("CheckDependency", "Checks if dependent module exists")
        
    def validate(self, module_def, configuration, project_context=None):
        result = ValidationResult()
        # Mock logic: Check if 'Can' module exists in project
        if project_context:
            if 'Can' not in project_context.module_managers:
                result.add_message(self._create_error("Missing required module 'Can'"))
        return result
"""

class TestCrossModuleRule(unittest.TestCase):
    def setUp(self):
        self.test_dir = tempfile.mkdtemp()
        self.rule_file = Path(self.test_dir) / "check_dep_rule.py"
        self.rule_file.write_text(CROSS_MODULE_RULE_CONTENT)
        
    def tearDown(self):
        shutil.rmtree(self.test_dir)
        
    def test_cross_module_validation(self):
        # Mock modules
        module_def = MagicMock(spec=EcucModuleDef)
        config = MagicMock(spec=EcucModuleConfiguration)
        
        # Mock Project Context
        project_context = MagicMock()
        project_context.module_managers = {} # Empty project
        
        # Init engine
        engine = ValidationEngine(module_def, config, project_context=project_context)
        
        # Load rule
        count = engine.load_custom_rules(str(self.rule_file))
        self.assertEqual(count, 1)
        
        # Validate - Should fail because 'Can' is missing
        result = engine.validate()
        self.assertFalse(result.is_valid)
        self.assertEqual(result.messages[0].message, "Missing required module 'Can'")
        
        # Add Can module
        project_context.module_managers['Can'] = MagicMock()
        
        # Validate again - Should pass
        result = engine.validate()
        self.assertTrue(result.is_valid)

if __name__ == '__main__':
    unittest.main()
