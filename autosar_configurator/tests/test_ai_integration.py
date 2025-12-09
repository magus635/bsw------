import unittest
from unittest.mock import MagicMock, patch
from PySide6.QtWidgets import QApplication
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef
from autosar_configurator.core.config_manager import ConfigurationManager

class TestAIIntegration(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not QApplication.instance():
            cls.app = QApplication([])
        else:
            cls.app = QApplication.instance()
            
    def setUp(self):
        self.window = DaVinciMainWindow()
        
        # Mock Config Manager and Definitions
        self.mock_module_def = MagicMock(spec=EcucModuleDef)
        self.mock_module_def.containers = {}
        
        self.mock_container_def = MagicMock(spec=EcucContainerDef)
        self.mock_container_def.short_name = "AdcKernel"
        self.mock_container_def.lower_multiplicity = 0
        self.mock_container_def.upper_multiplicity = 1
        self.mock_container_def.sub_containers = {}
        
        self.mock_module_def.containers = {"AdcKernel": self.mock_container_def}
        
        self.mock_config_manager = MagicMock(spec=ConfigurationManager)
        self.mock_config_manager.module_def = self.mock_module_def
        self.mock_config_manager._generate_instance_name.return_value = "AdcKernel_0"
        
        # Inject mock into window
        self.window.config_manager = self.mock_config_manager
        
        # Mock Settings to avoid API Key Prompt
        self.window.settings = MagicMock()
        self.window.settings.value.return_value = "dummy_key"
        
    def tearDown(self):
        self.window.close()
        
    def test_create_command_integration(self):
        """Test 'Create AdcKernel' command flow"""
        widget = self.window.ai_assistant_widget
        
        # Spy on undo stack
        initial_count = self.window.undo_stack.count()
        
        # User types command
        widget.input_field.setText("Create AdcKernel")
        widget.send_btn.click()
        
        # Verify Processor was called and Command pushed
        # Note: Since we are using a real NaturalLanguageProcessor but with a MOCKED ConfigManager,
        # the NLP will try to push a REAL Command to the REAL UndoStack (window.undo_stack).
        # The Command execution will call methods on the MOCK ConfigManager.
        
        # Check if undo stack has a new command
        self.assertEqual(self.window.undo_stack.count(), initial_count + 1)
        last_command = self.window.undo_stack.command(self.window.undo_stack.count() - 1)
        self.assertIn("Create", last_command.text())
        
        # Verify UI response (Success check)
        chat_text = widget.chat_history.toPlainText()
        self.assertIn("已创建", chat_text)
        self.assertIn("AdcKernel_0", chat_text)

    def test_explain_command_integration(self):
        """Test 'Explain AdcKernel' command flow"""
        widget = self.window.ai_assistant_widget
        self.mock_container_def.description = "Controls ADC hardware."
        self.mock_container_def.multiplicity_str = "0..1"
        
        widget.input_field.setText("Explain AdcKernel")
        widget.send_btn.click()
        
        chat_text = widget.chat_history.toPlainText()
        self.assertIn("Controls ADC hardware", chat_text)
        self.assertIn("0..1", chat_text)

    def test_set_parameter_integration(self):
        """Test 'Set AdcClock to 80000' command flow"""
        widget = self.window.ai_assistant_widget
        
        # Setup context: Mock a selected instance
        mock_instance = MagicMock()
        mock_instance.short_name = "AdcKernel_0"
        mock_instance.definition = self.mock_container_def
        
        # Setup definition with a parameter
        param_def = MagicMock()
        self.mock_container_def.parameters = {"AdcClock": param_def}
        
        # Mock selection in TreeView
        self.window.tree_view.get_selected_instance = MagicMock(return_value=mock_instance)
        
        # Execute command
        widget.input_field.setText("Set AdcClock to 80000")
        widget.send_btn.click()
        
        # Verify Command pushed
        last_command = self.window.undo_stack.command(self.window.undo_stack.count() - 1)
        # Command text key is "Set {param_name}" (Internal command name, likely English)
        self.assertIn("Set AdcClock", last_command.text())
        
        # Verify success message
        chat_text = widget.chat_history.toPlainText()
        self.assertIn("已设置", chat_text)
        self.assertIn("80000", chat_text)

    def test_create_sub_container_integration(self):
        """Test 'Create AdcChannel' (sub-container) with context"""
        widget = self.window.ai_assistant_widget
        
        # Setup Defs: Parent(AdcKernel) -> Sub(AdcChannel)
        mock_sub_def = MagicMock(spec=EcucContainerDef)
        mock_sub_def.short_name = "AdcChannel"
        mock_sub_def.parent = self.mock_container_def
        self.mock_container_def.sub_containers = {"AdcChannel": mock_sub_def}
        
        # Setup Context: Selected AdcKernel_0
        mock_context_instance = MagicMock()
        mock_context_instance.short_name = "AdcKernel_0"
        mock_context_instance.definition = self.mock_container_def
        # Provide sub-containers dict to verification logic if needed
        mock_context_instance.sub_containers = []
        
        # Mock selection
        self.window.tree_view.get_selected_instance = MagicMock(return_value=mock_context_instance)
        
        # Setup generation name
        self.mock_config_manager._generate_instance_name.return_value = "AdcChannel_0"
        
        # Execute Command
        widget.input_field.setText("Create AdcChannel")
        widget.send_btn.click()
        
        # Verify Command
        last_command = self.window.undo_stack.command(self.window.undo_stack.count() - 1)
        self.assertIn("Create AdcChannel_0", last_command.text())
        
        # Verify Message
        chat_text = widget.chat_history.toPlainText()
        self.assertIn("已创建", chat_text)
        self.assertIn("AdcChannel_0", chat_text)
        self.assertIn("在 **AdcKernel_0** 下", chat_text)

if __name__ == '__main__':
    unittest.main()
