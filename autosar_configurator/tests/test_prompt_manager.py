import unittest
from unittest.mock import MagicMock
from autosar_configurator.core.ai.prompt_manager import PromptManager
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef

class TestPromptManager(unittest.TestCase):
    def setUp(self):
        # Mock Config Manager and Definitions
        self.mock_module_def = MagicMock(spec=EcucModuleDef)
        self.mock_module_def.short_name = "Adc"
        
        self.mock_config_manager = MagicMock(spec=ConfigurationManager)
        self.mock_config_manager.module_def = self.mock_module_def
        
        self.prompt_manager = PromptManager(self.mock_config_manager)
        
    def test_build_general_prompt(self):
        prompt = self.prompt_manager.build_general_prompt("How do I configure this?")
        self.assertIn("Adc", prompt)
        self.assertIn("How do I configure this?", prompt)
        self.assertIn("AUTOSAR BSW configuration", prompt)

    def test_build_explain_prompt(self):
        # Setup mock container definition
        container_def = MagicMock(spec=EcucContainerDef)
        container_def.short_name = "AdcKernel"
        container_def.description = "Controls the ADC HW unit."
        container_def.multiplicity_str = "1..*"
        
        # Mock subcontainers and parameters
        sub1 = MagicMock(spec=EcucContainerDef)
        sub1.short_name = "AdcChannel"
        container_def.sub_containers = {"AdcChannel": sub1}
        
        param1 = MagicMock(spec=EcucParameterDef)
        param1.short_name = "AdcClock"
        container_def.parameters = {"AdcClock": param1}
        
        prompt = self.prompt_manager.build_explain_prompt(container_def)
        
        # Verify content
        self.assertIn("AdcKernel", prompt)
        self.assertIn("Controls the ADC HW unit", prompt)
        self.assertIn("1..*", prompt)
        self.assertIn("AdcChannel", prompt)
        self.assertIn("AdcClock", prompt)

if __name__ == '__main__':
    unittest.main()
