"""
Test Reference Error Display in DaVinci Config Panel

Verifies that resolution errors are correctly displayed with:
- Status icons based on severity
- Tooltips with error messages
- Background colors for errors
- Error count in GroupBox title
"""
import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent.parent.parent))

import pytest
from PySide6.QtCore import Qt
from PySide6.QtWidgets import QApplication

from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue, 
    EcucReferenceValue,
    ResolutionError,
    ResolutionSeverity
)
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucReferenceDef
)
from autosar_configurator.core.config_manager import ConfigurationManager


@pytest.fixture
def mock_config_manager():
    """Create a mock ConfigurationManager"""
    class MockConfiguration:
        containers = []
    
    class MockConfigManager:
        configuration = MockConfiguration()
    
    return MockConfigManager()


@pytest.fixture
def panel(qtbot):
    """Create a DaVinciConfigPanel instance"""
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    return panel


@pytest.fixture
def container_def_with_ref():
    """Create a container definition with one reference"""
    container_def = EcucContainerDef(
        short_name="TestContainer",
        definition_ref="/Test/TestContainer"
    )
    ref_def = EcucReferenceDef(
        short_name="TestRef",
        definition_ref="/Test/TestContainer/TestRef",
        destination_ref="/Other/TargetContainer"
    )
    container_def.references["TestRef"] = ref_def
    return container_def


@pytest.fixture
def instance_with_error(container_def_with_ref):
    """Create an instance with a broken reference"""
    instance = EcucContainerValue(
        short_name="TestInstance_0",
        definition_ref="/Test/TestContainer"
    )
    
    # Create a reference value with an error
    ref_value = EcucReferenceValue(
        definition_ref="/Test/TestContainer/TestRef",
        value_ref="/Config/NonExistentTarget"
    )
    ref_value.resolution_error = ResolutionError(
        ResolutionError.PATH_NOT_FOUND,
        "/Config/NonExistentTarget"
    )
    instance.reference_values["TestRef"] = ref_value
    
    return instance


@pytest.fixture
def instance_with_resolved_ref(container_def_with_ref):
    """Create an instance with a successfully resolved reference"""
    instance = EcucContainerValue(
        short_name="TestInstance_0",
        definition_ref="/Test/TestContainer"
    )
    
    # Create a resolved reference
    target = EcucContainerValue(
        short_name="Target_0",
        definition_ref="/Other/TargetContainer"
    )
    ref_value = EcucReferenceValue(
        definition_ref="/Test/TestContainer/TestRef",
        value_ref="/Config/Target_0"
    )
    ref_value.target = target  # Mark as resolved
    instance.reference_values["TestRef"] = ref_value
    
    return instance


class TestReferenceErrorDisplay:
    """Test suite for reference error display functionality"""
    
    def test_status_column_exists(self, panel, container_def_with_ref, instance_with_error, mock_config_manager, qtbot):
        """Test that refs table has 5 columns including Status"""
        panel.show_instance(instance_with_error, container_def_with_ref, mock_config_manager)
        
        assert panel.refs_table.columnCount() == 5
        assert panel.refs_table.horizontalHeaderItem(4).text() == "Status"
    
    def test_error_icon_displayed(self, panel, container_def_with_ref, instance_with_error, mock_config_manager, qtbot):
        """Test that error icon is displayed for broken reference"""
        panel.show_instance(instance_with_error, container_def_with_ref, mock_config_manager)
        
        # Check status column (column 4)
        status_item = panel.refs_table.item(0, 4)
        assert status_item is not None
        assert "❌" in status_item.text()
    
    def test_success_icon_displayed(self, panel, container_def_with_ref, instance_with_resolved_ref, mock_config_manager, qtbot):
        """Test that success icon is displayed for resolved reference"""
        panel.show_instance(instance_with_resolved_ref, container_def_with_ref, mock_config_manager)
        
        status_item = panel.refs_table.item(0, 4)
        assert status_item is not None
        assert "✅" in status_item.text()
    
    def test_error_tooltip_contains_message(self, panel, container_def_with_ref, instance_with_error, mock_config_manager, qtbot):
        """Test that error tooltip contains useful information"""
        panel.show_instance(instance_with_error, container_def_with_ref, mock_config_manager)
        
        status_item = panel.refs_table.item(0, 4)
        tooltip = status_item.toolTip()
        
        # Should contain error message and suggestion
        assert "目标容器不存在" in tooltip or "NonExistentTarget" in tooltip
        assert "💡" in tooltip  # Suggestion indicator
    
    def test_error_count_in_title(self, panel, container_def_with_ref, instance_with_error, mock_config_manager, qtbot):
        """Test that error count appears in GroupBox title"""
        panel.show_instance(instance_with_error, container_def_with_ref, mock_config_manager)
        
        title = panel.references_group.title()
        assert "1 error" in title
        assert "⚠️" in title
    
    def test_no_error_count_when_resolved(self, panel, container_def_with_ref, instance_with_resolved_ref, mock_config_manager, qtbot):
        """Test that no error count when all references are resolved"""
        panel.show_instance(instance_with_resolved_ref, container_def_with_ref, mock_config_manager)
        
        title = panel.references_group.title()
        assert "error" not in title.lower()



if __name__ == "__main__":
    pytest.main([__file__, "-v"])
