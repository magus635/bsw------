"""
Test Suite for Recommended Values Loading
Functionality: Verifies loading, comparing, and applying recommended values
"""
import sys
from pathlib import Path
import unittest

# Add parent directory to path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
)
from autosar_configurator.core.model.configuration_model import (
    EcucModuleConfiguration, EcucContainerValue
)

class TestRecommendedValues(unittest.TestCase):
    def setUp(self):
        # Create a mock module definition
        self.module_def = EcucModuleDef("TestModule")
        self.module_def.definition_ref = "/AUTOSAR/EcucDefs/TestModule"
        
        # Create a container definition
        self.container_def = EcucContainerDef("Container1")
        self.container_def.definition_ref = "/AUTOSAR/EcucDefs/TestModule/Container1"
        self.module_def.containers["Container1"] = self.container_def
        
        # Create parameters
        params = {
            "IntParam": EcucParameterDef("IntParam", EcucParameterType.INTEGER, 
                                        definition_ref="/AUTOSAR/EcucDefs/TestModule/Container1/IntParam"),
            "BoolParam": EcucParameterDef("BoolParam", EcucParameterType.BOOLEAN,
                                         definition_ref="/AUTOSAR/EcucDefs/TestModule/Container1/BoolParam"),
            "StringParam": EcucParameterDef("StringParam", EcucParameterType.STRING,
                                           definition_ref="/AUTOSAR/EcucDefs/TestModule/Container1/StringParam")
        }
        self.container_def.parameters = params
        
        # Initialize Manager
        self.manager = ConfigurationManager(self.module_def)
        
        # Create Current Configuration
        # Container with some values set
        self.current_inst = self.manager.create_container_instance(self.container_def, None, "Instance1")
        self.current_inst.set_parameter_value("IntParam", 10, "")
        self.current_inst.set_parameter_value("BoolParam", False, "")
        # StringParam is left empty/default
        
        # Create Recommended Configuration (Mocking what would be loaded from file)
        self.rec_config = EcucModuleConfiguration("TestModule_Rec", "/AUTOSAR/EcucDefs/TestModule")
        self.rec_inst = EcucContainerValue("Instance1", self.container_def.definition_ref)
        self.rec_config.add_container(self.rec_inst)
        
        # Recommended values:
        # IntParam: 20 (Differs from current 10)
        # BoolParam: True (Differs from current False)
        # StringParam: "Recommended" (Current is empty)
        self.rec_inst.set_parameter_value("IntParam", 20, "")
        self.rec_inst.set_parameter_value("BoolParam", True, "")
        self.rec_inst.set_parameter_value("StringParam", "Recommended", "")
        
    def test_comparison(self):
        """Test comparing current values with recommended values"""
        comparisons = self.manager.get_recommended_value_comparison(self.rec_config)
        
        # Should find 3 comparisons
        self.assertEqual(len(comparisons), 3)
        
        comparisons_map = {c['param_name']: c for c in comparisons}
        
        # Check IntParam
        self.assertEqual(comparisons_map['IntParam']['current_value'], 10)
        self.assertEqual(comparisons_map['IntParam']['recommended_value'], 20)
        self.assertTrue(comparisons_map['IntParam']['differs'])
        
        # Check StringParam (Current is empty string from default init)
        # Note: create_container_instance initializes StringParam to ""
        self.assertEqual(comparisons_map['StringParam']['current_value'], "")
        self.assertEqual(comparisons_map['StringParam']['recommended_value'], "Recommended")
        self.assertTrue(comparisons_map['StringParam']['differs'])

    def test_apply_only_empty(self):
        """Test applying recommended values ONLY to empty fields"""
        # Current: Int=10, Bool=False, String=""
        # Rec: Int=20, Bool=True, String="Recommended"
        
        updated = self.manager.apply_recommended_values(self.rec_config, only_empty=True)
        
        # Only StringParam should be updated because it was "" (empty)
        # IntParam (10) and BoolParam (False) are not None, so they are kept.
        # Wait, check implementation of 'empty' in config_manager.py:
        # should_apply = not only_empty or current_value is None or current_value == ""
        
        self.assertEqual(updated, 1)
        self.assertEqual(self.current_inst.parameter_values['StringParam'].value, "Recommended")
        self.assertEqual(self.current_inst.parameter_values['IntParam'].value, 10) # Unchanged
        self.assertEqual(self.current_inst.parameter_values['BoolParam'].value, False) # Unchanged

    def test_apply_overwrite_all(self):
        """Test applying recommended values to ALL fields (overwrite)"""
        updated = self.manager.apply_recommended_values(self.rec_config, only_empty=False)
        
        self.assertEqual(updated, 3)
        self.assertEqual(self.current_inst.parameter_values['StringParam'].value, "Recommended")
        self.assertEqual(self.current_inst.parameter_values['IntParam'].value, 20)
        self.assertEqual(self.current_inst.parameter_values['BoolParam'].value, True)

if __name__ == '__main__':
    unittest.main()
