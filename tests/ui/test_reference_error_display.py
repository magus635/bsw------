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

    def test_missing_target_shown_in_combo_instead_of_not_set(
        self, panel, container_def_with_ref, instance_with_error, mock_config_manager, qtbot
    ):
        """Unresolved target path is displayed as Missing in Target combo rather than '(Not set)'."""
        panel.show_instance(instance_with_error, container_def_with_ref, mock_config_manager)

        combo = panel.refs_table.cellWidget(0, 1)
        assert combo is not None
        assert combo.currentText() != "(Not set)"
        assert "/Config/NonExistentTarget" in combo.currentText()
        assert "Missing" in combo.currentText()
        assert combo.currentData() == "/Config/NonExistentTarget"
        assert combo.currentData(DaVinciConfigPanel.UNRESOLVED_REF_ROLE) is True
        assert combo.itemText(0) == "(Not set)" and combo.itemData(0) is None

    def test_choice_reference_displays_all_types_count_and_tooltip(self, panel, mock_config_manager, qtbot):
        """Choice references show 'Choice (N types)' in Destination Type and list all targets in tooltips."""
        choice_paths = [
            "/AUTOSAR/EcucDefs/Gpt/GptChannelConfigSet/GptChannelConfiguration",
            "/AUTOSAR/EcucDefs/Can/CanConfigSet/CanController",
            "/THA6_AS440_FuSa/Spi/SpiDriver/SpiHwUnitConfig",
        ]
        cdef = EcucContainerDef(short_name="ResourceAllocation", definition_ref="/Test/ResourceAllocation")
        cdef.references["ResourceModuleRef"] = EcucReferenceDef(
            short_name="ResourceModuleRef",
            definition_ref="/Test/ResourceAllocation/ResourceModuleRef",
            destination_ref=choice_paths[0],
            choice_destination_refs=choice_paths,
        )
        inst = EcucContainerValue(short_name="ResourceAllocation_2", definition_ref="/Test/ResourceAllocation")
        panel.show_instance(inst, cdef, mock_config_manager)

        dest_item = panel.refs_table.item(0, 2)
        name_item = panel.refs_table.item(0, 0)
        assert dest_item.text() == "Choice (3 types)"
        for path in choice_paths:
            assert path in dest_item.toolTip()
            assert path in name_item.toolTip()

    def test_foreign_reference_displays_globe_badge_in_combo(self, panel, mock_config_manager, qtbot):
        """External non-ECUC references without error display 🌐 <path> rather than '(Not set)'."""
        cdef = EcucContainerDef(short_name="SwcMapping", definition_ref="/Test/SwcMapping")
        cdef.references["MemAddrRef"] = EcucReferenceDef(
            short_name="MemAddrRef",
            definition_ref="/Test/SwcMapping/MemAddrRef",
            destination_ref="/AUTOSAR/EcucDefs/MemMap/SwAddrMethod",
        )
        inst = EcucContainerValue(short_name="SwcMapping_0", definition_ref="/Test/SwcMapping")
        inst.reference_values["MemAddrRef"] = EcucReferenceValue(
            definition_ref="/Test/SwcMapping/MemAddrRef",
            value_ref="/MICROSAR/MemMap/SwAddrMethods/VAR_CLEARED",
            dest_type="ECUC-FOREIGN-REFERENCE-DEF",
        )
        panel.show_instance(inst, cdef, mock_config_manager)

        combo = panel.refs_table.cellWidget(0, 1)
        assert combo is not None
        assert "🌐" in combo.currentText()
        assert "/MICROSAR/MemMap/SwAddrMethods/VAR_CLEARED" in combo.currentText()
        assert combo.currentData(DaVinciConfigPanel.UNRESOLVED_REF_ROLE) is True



if __name__ == "__main__":
    pytest.main([__file__, "-v"])
