"""
Test ConfigPanel container display
"""
import pytest
from autosar_configurator.ui.widgets.config_panel import ConfigPanel
from autosar_configurator.core.model.container import Container

def test_show_container(qtbot):
    """Test that show_container updates the UI correctly"""
    panel = ConfigPanel()
    qtbot.addWidget(panel)
    
    container = Container(short_name="TestContainer", description="Test Description")
    
    panel.show()
    panel.show_container(container)
    
    assert panel.current_container == container
    assert panel.container_name_edit.text() == "TestContainer"
    assert panel.container_desc_edit.toPlainText() == "Test Description"
    assert panel.general_group.isVisible()
    assert not panel.parameter_group.isVisible()
