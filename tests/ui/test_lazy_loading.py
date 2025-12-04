"""
Tests for lazy loading in tree view
"""
import pytest
from PySide6.QtWidgets import QTreeWidgetItem
from autosar_configurator.core.model.container import Container, Parameter
from autosar_configurator.ui.widgets.tree_view import ModuleTreeView

class TestLazyLoading:
    """Test lazy loading functionality"""
    
    @pytest.fixture
    def tree_view(self, qtbot):
        tree = ModuleTreeView()
        qtbot.addWidget(tree)
        return tree
        
    def test_lazy_population(self, tree_view):
        """Test that items are populated only when expanded"""
        # Create nested structure
        root = Container(short_name="Root")
        c1 = Container(short_name="Container1")
        c2 = Container(short_name="Container2")
        p1 = Parameter(short_name="Param1", value="val")
        
        c1.add_sub_container(c2)
        c2.add_parameter(p1)
        root.add_sub_container(c1)
        
        tree_view.set_root_container(root)
        
        # Get root item
        root_item = tree_view.topLevelItem(0)
        assert root_item.text(0) == "Root"
        
        # Check c1 item
        assert root_item.childCount() == 1
        c1_item = root_item.child(0)
        assert c1_item.text(0) == "Container1"
        
        # Verify c1 has dummy child (loading indicator)
        assert c1_item.childCount() == 1
        assert c1_item.child(0).text(0) == "Loading..."
        
        # Expand c1
        c1_item.setExpanded(True)
        
        # Verify dummy removed and real child added
        assert c1_item.childCount() == 1
        c2_item = c1_item.child(0)
        assert c2_item.text(0) == "Container2"
        
        # Verify c2 has dummy child
        assert c2_item.childCount() == 1
        assert c2_item.child(0).text(0) == "Loading..."
        
        # Expand c2
        c2_item.setExpanded(True)
        
        # Verify parameter added
        assert c2_item.childCount() == 1
        p1_item = c2_item.child(0)
        assert "Param1" in p1_item.text(0)
