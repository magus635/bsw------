import unittest
from unittest.mock import MagicMock
from autosar_configurator.core.ai.nlp_processor import NaturalLanguageProcessor
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
from autosar_configurator.core.model.configuration_model import EcucContainerValue

class TestNlpSetParameter(unittest.TestCase):
    def setUp(self):
        # Mock Config Manager and Undo Stack
        self.mock_config_manager = MagicMock(spec=ConfigurationManager)
        self.mock_config_manager.module_def = MagicMock()
        self.mock_config_manager.module_def.containers = {}
        
        self.mock_undo_stack = MagicMock()
        
        self.nlp = NaturalLanguageProcessor(self.mock_config_manager, self.mock_undo_stack)
        
        # Setup common mocks
        self.mock_def = MagicMock(spec=EcucContainerDef)
        self.mock_def.short_name = "TestContainerDef"
        self.mock_def.parameters = {}
        
        self.mock_instance = MagicMock(spec=EcucContainerValue)
        self.mock_instance.short_name = "TestInstance"
        self.mock_instance.definition = self.mock_def

    def _add_param_def(self, name, param_type, literals=None):
        p = MagicMock(spec=EcucParameterDef)
        p.param_type = param_type
        p.short_name = name
        p.literals = literals
        self.mock_def.parameters[name] = p
        return p

    def test_set_integer(self):
        self._add_param_def("IntParam", EcucParameterType.INTEGER)
        
        # Test valid
        resp = self.nlp._handle_set_intent("IntParam", "123", self.mock_instance)
        self.assertIn("Set **IntParam** to **123**", resp)
        
        # Test hex
        resp = self.nlp._handle_set_intent("IntParam", "0x10", self.mock_instance)
        self.assertIn("Set **IntParam** to **16**", resp)
        
        # Test invalid
        resp = self.nlp._handle_set_intent("IntParam", "abc", self.mock_instance)
        self.assertIn("Invalid format for INTEGER", resp)

    def test_set_boolean(self):
        self._add_param_def("BoolParam", EcucParameterType.BOOLEAN)
        
        # Test True variants
        for val in ["true", "True", "1", "yes", "on"]:
            resp = self.nlp._handle_set_intent("BoolParam", val, self.mock_instance)
            self.assertIn("Set **BoolParam** to **True**", resp)
            
        # Test False variants
        for val in ["false", "False", "0", "no", "off"]:
            resp = self.nlp._handle_set_intent("BoolParam", val, self.mock_instance)
            self.assertIn("Set **BoolParam** to **False**", resp)
            
        # Test Invalid
        resp = self.nlp._handle_set_intent("BoolParam", "maybe", self.mock_instance)
        self.assertIn("Invalid format for BOOLEAN", resp)

    def test_set_float(self):
        self._add_param_def("FloatParam", EcucParameterType.FLOAT)
        
        resp = self.nlp._handle_set_intent("FloatParam", "3.14", self.mock_instance)
        self.assertIn("Set **FloatParam** to **3.14**", resp)
        
        resp = self.nlp._handle_set_intent("FloatParam", "invalid", self.mock_instance)
        self.assertIn("Invalid format for FLOAT", resp)
        
    def test_set_enumeration(self):
        self._add_param_def("EnumParam", EcucParameterType.ENUMERATION, literals=["RED", "GREEN", "BLUE"])
        
        # Valid (Case insensitive)
        resp = self.nlp._handle_set_intent("EnumParam", "red", self.mock_instance)
        self.assertIn("Set **EnumParam** to **RED**", resp)
        
        # Invalid
        resp = self.nlp._handle_set_intent("EnumParam", "YELLOW", self.mock_instance)
        self.assertIn("Invalid enum value 'YELLOW'", resp)

    def test_param_not_found(self):
        resp = self.nlp._handle_set_intent("UnknownParam", "123", self.mock_instance)
        self.assertIn("Parameter 'UnknownParam' not found", resp)

    def test_case_insensitive_param_name(self):
        self._add_param_def("MyParam", EcucParameterType.STRING)
        
        resp = self.nlp._handle_set_intent("myparam", "value", self.mock_instance)
        self.assertIn("Set **MyParam** to **value**", resp)

if __name__ == '__main__':
    unittest.main()
