"""
Tests for batch operations
"""
import pytest
from PySide6.QtCore import Qt
from PySide6.QtWidgets import QTreeWidget, QTreeWidgetItem

from autosar_configurator.core.model.container import Container, Parameter
from autosar_configurator.core.command import CommandManager
from autosar_configurator.ui.widgets.tree_view import ModuleTreeView
from autosar_configurator.ui.widgets.batch_edit_dialog import BatchEditDialog


class TestBatchOperations:
    """Test batch operations in tree view and dialog"""
    
    @pytest.fixture
    def command_manager(self):
        return CommandManager()
        
    @pytest.fixture
    def tree_view(self, command_manager, qtbot):
        tree = ModuleTreeView()
        qtbot.addWidget(tree)
        tree.set_command_manager(command_manager)
        
        # Setup data
        root = Container(short_name="Root")
        
        # Add some items
        c1 = Container(short_name="Container1")
        c2 = Container(short_name="Container2")
        root.add_sub_container(c1)
        root.add_sub_container(c2)
        
        p1 = Parameter(short_name="Param1", value=10, value_type="INTEGER")
        p2 = Parameter(short_name="Param2", value=20, value_type="INTEGER")
        c1.add_parameter(p1)
        c1.add_parameter(p2)
        
        tree.set_root_container(root)
        return tree
        
    def test_multi_selection_mode(self, tree_view):
        """Test that multi-selection is enabled"""
        assert tree_view.selectionMode() == QTreeWidget.ExtendedSelection
        
    def test_batch_delete(self, tree_view, command_manager):
        """Test batch delete operation"""
        root = tree_view.root_container
        c1 = root.sub_containers["Container1"]
        c2 = root.sub_containers["Container2"]
        
        # Select both containers
        item1 = tree_view.element_to_item[id(c1)]
        item2 = tree_view.element_to_item[id(c2)]
        
        item1.setSelected(True)
        item2.setSelected(True)
        
        # Execute batch delete
        tree_view._batch_delete()
        
        # Verify removed from model
        assert "Container1" not in root.sub_containers
        assert "Container2" not in root.sub_containers
        
        # Verify undo
        command_manager.undo()
        assert "Container1" in root.sub_containers
        assert "Container2" in root.sub_containers
        
    def test_batch_edit_dialog_init(self, command_manager, qtbot):
        """Test batch edit dialog initialization"""
        p1 = Parameter(short_name="P1", value=10, value_type="INTEGER")
        p2 = Parameter(short_name="P2", value=20, value_type="INTEGER")
        
        dialog = BatchEditDialog([p1, p2], command_manager)
        qtbot.addWidget(dialog)
        
        assert dialog.target_type == Parameter
        assert dialog.property_combo.count() > 0
        
    def test_batch_edit_execution(self, command_manager, qtbot):
        """Test batch edit execution"""
        p1 = Parameter(short_name="P1", value=10, value_type="INTEGER")
        p2 = Parameter(short_name="P2", value=20, value_type="INTEGER")
        
        dialog = BatchEditDialog([p1, p2], command_manager)
        qtbot.addWidget(dialog)
        
        # Simulate user input
        # Select "value" property (assuming it's in the combo)
        index = dialog.property_combo.findText("value")
        if index >= 0:
            dialog.property_combo.setCurrentIndex(index)
            dialog.value_input.setText("50")
            
            # Apply changes
            dialog._apply_changes()
            
            # Verify changes
            assert p1.value == 50
            assert p2.value == 50
            
            # Verify undo
            command_manager.undo()
            assert p1.value == 10
            assert p2.value == 20
            
    def test_mixed_type_selection(self, command_manager, qtbot):
        """Test mixed type selection handling"""
        c1 = Container(short_name="C1")
        p1 = Parameter(short_name="P1", value=10, value_type="INTEGER")
        
        dialog = BatchEditDialog([c1, p1], command_manager)
        qtbot.addWidget(dialog)
        
        assert dialog.target_type is None
        # Should show error message or disable controls
