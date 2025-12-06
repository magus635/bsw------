import unittest
from PySide6.QtWidgets import QApplication, QDockWidget
from PySide6.QtCore import Qt
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
from autosar_configurator.ui.widgets.ai_assistant import AIAssistantWidget

class TestAIAssistant(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not QApplication.instance():
            cls.app = QApplication([])
        else:
            cls.app = QApplication.instance()
            
    def setUp(self):
        self.window = DaVinciMainWindow()
        
    def tearDown(self):
        self.window.close()
        
    def test_dock_toggle(self):
        """Test toggling the AI assistant dock"""
        # Initially hidden
        self.assertTrue(self.window.ai_assistant_dock.isHidden())
        
        # Toggle via action
        self.window.toggle_ai_action.trigger()
        self.assertFalse(self.window.ai_assistant_dock.isHidden())
        
        # Toggle back
        self.window.toggle_ai_action.trigger()
        self.assertTrue(self.window.ai_assistant_dock.isHidden())
        
    def test_send_message(self):
        """Test sending a message in the widget"""
        widget = self.window.ai_assistant_widget
        
        # Spy on signal
        messages = []
        widget.message_sent.connect(messages.append)
        
        # Simulate input
        widget.input_field.setText("Create Adc")
        widget.send_btn.click()
        
        # Verify signal emitted
        self.assertEqual(messages, ["Create Adc"])
        
        # Verify chat history updated (basic check)
        self.assertIn("Create Adc", widget.chat_history.toPlainText())
        
        # Verify input cleared
        self.assertEqual(widget.input_field.text(), "")
        
        # Verify busy status
        self.assertIn("Thinking", widget.status_label.text())

if __name__ == '__main__':
    unittest.main()
