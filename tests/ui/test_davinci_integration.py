
import pytest
from PySide6.QtCore import Qt
from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef
from autosar_configurator.core.model.configuration_model import EcucContainerValue

class TestDaVinciIntegration:
    
    @pytest.fixture
    def mock_data(self):
        # Create mock definition
        module_def = EcucModuleDef("TestModule", "TestModule")
        container_def = EcucContainerDef("TestContainer", "TestContainer")
        module_def.add_container(container_def)
        
        # Create manager
        manager = ConfigurationManager(module_def)
        
        # Create instance
        instance = manager.create_container_instance(container_def, instance_name="TestInstance")
        
        return module_def, manager, instance, container_def

    def test_tree_view_signals(self, qtbot, mock_data):
        """Test that tree view emits manager in signals"""
        module_def, manager, instance, container_def = mock_data
        
        tree = DaVinciTreeView()
        qtbot.addWidget(tree)
        
        # Setup single module mode
        tree.set_module_def(module_def, manager)
        
        # Find the instance item
        # Root -> Def -> Instance
        root = tree.topLevelItem(0)
        def_item = root.child(0)
        instance_item = def_item.child(0)
        
        # Verify item data has manager
        data = instance_item.data(0, Qt.UserRole)
        assert data["manager"] == manager
        
        # Test signal emission
        with qtbot.waitSignal(tree.instance_selected) as blocker:
            tree._on_item_clicked(instance_item, 0)
            
        # Verify signal args: instance, def, manager
        assert blocker.args[0] == instance
        assert blocker.args[1] == container_def
        assert blocker.args[2] == manager

    def test_main_window_integration(self, qtbot, mock_data):
        """Test that main window updates context on signal"""
        module_def, manager, instance, container_def = mock_data
        
        window = DaVinciMainWindow()
        qtbot.addWidget(window)
        
        # Initially actions disabled
        assert not window.show_dep_graph_action.isEnabled()
        assert window.config_manager is None
        
        # Simulate signal from tree view
        # We call the handler directly to test the logic
        window._on_instance_selected(instance, container_def, manager)
        
        # Verify context updated
        assert window.config_manager == manager
        assert window.module_def == module_def
        
        # Verify actions enabled
        assert window.show_dep_graph_action.isEnabled()
        assert window.validate_action.isEnabled()
