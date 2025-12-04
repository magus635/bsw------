"""
Tree view widget for displaying AUTOSAR module hierarchy
"""
from PySide6.QtWidgets import QTreeWidget, QTreeWidgetItem, QMenu, QStyle
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QAction
from typing import Optional, Dict

from ...core.model.container import Container, Parameter
from ...core.model.observers import Observer
from ...core.command import (CommandManager, AddContainerCommand, 
                             AddParameterCommand, RemoveContainerCommand,
                             RemoveParameterCommand, BatchCommand)
from .batch_edit_dialog import BatchEditDialog

class ModuleTreeView(QTreeWidget):
    """Tree view for AUTOSAR module navigation"""

    # Signals
    container_selected = Signal(Container)
    parameter_selected = Signal(Parameter)

    def __init__(self, parent=None):
        super().__init__(parent)

        self.root_container: Optional[Container] = None
        self.command_manager: Optional[CommandManager] = None
        self.item_to_element: Dict[QTreeWidgetItem, object] = {}
        self.element_to_item: Dict[int, QTreeWidgetItem] = {}  # Use id() as key

        self._setup_ui()
        self._setup_context_menu()

    def _setup_ui(self):
        """Setup the tree widget UI"""
        self.setHeaderLabel("Configuration Structure")
        self.setContextMenuPolicy(Qt.CustomContextMenu)
        self.customContextMenuRequested.connect(self._show_context_menu)
        self.itemClicked.connect(self._on_item_clicked)
        self.itemExpanded.connect(self._on_item_expanded)
        self.setAlternatingRowColors(True)
        self.setAnimated(True)
        
        # Enable multi-selection for batch operations
        self.setSelectionMode(QTreeWidget.ExtendedSelection)

    def _setup_context_menu(self):
        """Setup context menu actions"""
        self.add_container_action = QAction("Add Container", self)
        self.add_container_action.triggered.connect(self._add_container)

        self.add_parameter_action = QAction("Add Parameter", self)
        self.add_parameter_action.triggered.connect(self._add_parameter)

        self.remove_action = QAction("Remove", self)
        self.remove_action.triggered.connect(self._remove_item)
        
        self.batch_delete_action = QAction("Batch Delete Selected", self)
        self.batch_delete_action.triggered.connect(self._batch_delete)
        
        self.batch_edit_action = QAction("Batch Edit Selected", self)
        self.batch_edit_action.triggered.connect(self._batch_edit)

        self.expand_all_action = QAction("Expand All", self)
        self.expand_all_action.triggered.connect(self.expandAll)

        self.collapse_all_action = QAction("Collapse All", self)
        self.collapse_all_action.triggered.connect(self.collapseAll)

    def set_root_container(self, container: Container):
        """Set the root container and build the tree"""
        if self.root_container:
            self.root_container.detach(self)

        self.root_container = container
        self.root_container.attach(self)

        self._build_tree()
    
    def set_command_manager(self, command_manager: CommandManager):
        """Set the command manager for undo/redo support"""
        self.command_manager = command_manager

    def _build_tree(self):
        """Build the tree from root container"""
        self.clear()
        self.item_to_element.clear()
        self.element_to_item.clear()

        if self.root_container:
            root_item = self._create_container_item(self.root_container)
            self.addTopLevelItem(root_item)
            # Initial population for root
            self._populate_container(root_item, self.root_container)
            root_item.setExpanded(True)

    def _create_container_item(self, container: Container) -> QTreeWidgetItem:
        """Create a tree item for a container"""
        # Import here to avoid circular dependency
        from ...core.model.ecuc_model import EcucContainer
        
        # Display name with multiplicity for ECUC containers
        display_name = container.short_name
        if isinstance(container, EcucContainer):
            mult_str = container.multiplicity_str
            display_name += f" [{mult_str}]"
        
        item = QTreeWidgetItem([display_name])
        item.setIcon(0, self.style().standardIcon(QStyle.StandardPixmap.SP_DirIcon))
        
        # Set tooltip with description
        if container.description:
            item.setToolTip(0, container.description)
        
        # Add dummy item if container has children to enable expansion
        if container.sub_containers or container.parameters:
            item.setChildIndicatorPolicy(QTreeWidgetItem.ShowIndicator)
            dummy = QTreeWidgetItem(["Loading..."])
            item.addChild(dummy)

        self.item_to_element[item] = container
        self.element_to_item[id(container)] = item

        return item

    def _create_parameter_item(self, parameter: Parameter) -> QTreeWidgetItem:
        """Create a tree item for a parameter"""
        from ...core.model.ecuc_model import EcucParameter
        
        display_text = f"{parameter.short_name}"
        
        # For ECUC parameters, show more details
        if isinstance(parameter, EcucParameter):
            # Show value if present
            if parameter.value is not None:
                display_text += f": {parameter.value}"
            
            # Show range for numeric types
            if parameter.min_value is not None and parameter.max_value is not None:
                display_text += f" ({parameter.min_value}..{parameter.max_value})"
            # Show enum options count
            elif parameter.literals:
                display_text += f" ({len(parameter.literals)} options)"
        else:
            # Regular parameter
            if parameter.value is not None:
                display_text += f" = {parameter.value}"
        
        item = QTreeWidgetItem([display_text])
        item.setIcon(0, self.style().standardIcon(QStyle.StandardPixmap.SP_FileIcon))
        self.item_to_element[item] = parameter
        self.element_to_item[id(parameter)] = item

        return item

    def _on_item_expanded(self, item: QTreeWidgetItem):
        """Handle item expansion for lazy loading"""
        # Check if item has dummy child
        if item.childCount() == 1 and item.child(0).text(0) == "Loading...":
            # Remove dummy
            item.removeChild(item.child(0))
            
            # Populate real children
            element = self.item_to_element.get(item)
            if isinstance(element, Container):
                self._populate_container(item, element)

    def _populate_container(self, parent_item: QTreeWidgetItem, container: Container):
        """Populate container's children (lazy loading with ECUC groups)"""
        from ...core.model.ecuc_model import EcucContainer
        from PySide6.QtGui import QColor
        
        # Remove dummy loading item if present
        if parent_item.childCount() == 1 and parent_item.child(0).text(0) == "Loading...":
            parent_item.removeChild(parent_item.child(0))
        
        # For ECUC containers, organize into groups
        if isinstance(container, EcucContainer):
            # Parameters group
            if container.parameters:
                params_group = QTreeWidgetItem([f"📋 Parameters ({len(container.parameters)})"])
                params_group.setForeground(0, QColor("#666666"))
                parent_item.addChild(params_group)
                
                for param in container.parameters.values():
                    param_item = self._create_parameter_item(param)
                    params_group.addChild(param_item)
            
            # References group
            if hasattr(container, 'references_defs') and container.references_defs:
                refs_group = QTreeWidgetItem([f"🔗 References ({len(container.references_defs)})"])
                refs_group.setForeground(0, QColor("#666666"))
                parent_item.addChild(refs_group)
                
                for ref_name, ref in container.references_defs.items():
                    ref_item = QTreeWidgetItem([f"{ref_name} → {ref.destination_ref}"])
                    ref_item.setIcon(0, self.style().standardIcon(QStyle.StandardPixmap.SP_FileLinkIcon))
                    ref_item.setToolTip(0, ref.description or "")
                    refs_group.addChild(ref_item)
            
            # Sub-containers (add directly, no group unless many)
            for sub_container in container.sub_containers.values():
                sub_item = self._create_container_item(sub_container)
                parent_item.addChild(sub_item)
        else:
            # Regular container: add parameters and sub-containers directly
            for param in container.parameters.values():
                param_item = self._create_parameter_item(param)
                parent_item.addChild(param_item)

            for sub_container in container.sub_containers.values():
                sub_item = self._create_container_item(sub_container)
                parent_item.addChild(sub_item)
            # Do NOT recursively populate sub-containers
            # They will be populated when expanded

    def _on_item_clicked(self, item: QTreeWidgetItem, column: int):
        """Handle item click"""
        element = self.item_to_element.get(item)

        if isinstance(element, Container):
            self.container_selected.emit(element)
        elif isinstance(element, Parameter):
            self.parameter_selected.emit(element)

    def _show_context_menu(self, position):
        """Show context menu"""
        selected_items = self.selectedItems()
        if not selected_items:
            return
            
        menu = QMenu(self)
        
        if len(selected_items) > 1:
            # Multi-selection menu
            menu.addAction(self.batch_edit_action)
            menu.addAction(self.batch_delete_action)
        else:
            # Single selection menu
            item = selected_items[0]
            element = self.item_to_element.get(item)

            if isinstance(element, Container):
                menu.addAction(self.add_container_action)
                menu.addAction(self.add_parameter_action)
                menu.addSeparator()
                
                # Don't allow removing root
                if element != self.root_container:
                    menu.addAction(self.remove_action)
                    
                menu.addSeparator()
                menu.addAction(self.expand_all_action)
                menu.addAction(self.collapse_all_action)
                
            elif isinstance(element, Parameter):
                menu.addAction(self.remove_action)

        menu.exec_(self.viewport().mapToGlobal(position))

    def _add_container(self):
        """Add a new container"""
        current_item = self.currentItem()
        if not current_item:
            return

        element = self.item_to_element.get(current_item)
        if not isinstance(element, Container):
            return

        # Create new container with unique name
        counter = 1
        name = f"NewContainer{counter}"
        while name in element.sub_containers:
            counter += 1
            name = f"NewContainer{counter}"

        new_container = Container(short_name=name)
        
        # Use command if available, otherwise add directly
        if self.command_manager:
            cmd = AddContainerCommand(element, new_container)
            self.command_manager.execute_command(cmd)
        else:
            element.add_sub_container(new_container)

        # Add to tree
        new_item = self._create_container_item(new_container)
        current_item.addChild(new_item)
        current_item.setExpanded(True)
        self.setCurrentItem(new_item)

    def _add_parameter(self):
        """Add a new parameter"""
        current_item = self.currentItem()
        if not current_item:
            return

        element = self.item_to_element.get(current_item)
        if not isinstance(element, Container):
            return

        # Create new parameter with unique name
        counter = 1
        name = f"NewParameter{counter}"
        while name in element.parameters:
            counter += 1
            name = f"NewParameter{counter}"

        new_param = Parameter(short_name=name, value="", value_type="STRING")
        
        # Use command if available, otherwise add directly
        if self.command_manager:
            cmd = AddParameterCommand(element, new_param)
            self.command_manager.execute_command(cmd)
        else:
            element.add_parameter(new_param)

        # Add to tree
        new_item = self._create_parameter_item(new_param)
        current_item.addChild(new_item)
        current_item.setExpanded(True)
        self.setCurrentItem(new_item)

    def _remove_item(self):
        """Remove selected item"""
        current_item = self.currentItem()
        if not current_item:
            return

        element = self.item_to_element.get(current_item)
        if not element:
            return

        # Don't allow removing root
        if element == self.root_container:
            return

        # Remove from model using commands
        if isinstance(element, Container) and element.parent:
            if self.command_manager:
                cmd = RemoveContainerCommand(element.parent, element.short_name)
                self.command_manager.execute_command(cmd)
            else:
                element.parent.remove_sub_container(element.short_name)
        elif isinstance(element, Parameter) and element.parent:
            if self.command_manager:
                cmd = RemoveParameterCommand(element.parent, element.short_name)
                self.command_manager.execute_command(cmd)
            else:
                element.parent.remove_parameter(element.short_name)

        # Remove from tree
        parent_item = current_item.parent()
        if parent_item:
            parent_item.removeChild(current_item)

        # Clean up mappings
        self.item_to_element.pop(current_item, None)
        self.element_to_item.pop(id(element), None)
        
    def _batch_delete(self):
        """Delete all selected items"""
        selected_items = self.selectedItems()
        if not selected_items:
            return
            
        # Collect commands
        commands = []
        items_to_remove = []
        
        for item in selected_items:
            element = self.item_to_element.get(item)
            if not element:
                continue
                
            # Skip root container
            if element == self.root_container:
                continue
                
            if isinstance(element, Container) and element.parent:
                if self.command_manager:
                    cmd = RemoveContainerCommand(element.parent, element.short_name)
                    commands.append(cmd)
                else:
                    element.parent.remove_sub_container(element.short_name)
                items_to_remove.append(item)
                    
            elif isinstance(element, Parameter) and element.parent:
                if self.command_manager:
                    cmd = RemoveParameterCommand(element.parent, element.short_name)
                    commands.append(cmd)
                else:
                    element.parent.remove_parameter(element.short_name)
                items_to_remove.append(item)
        
        # Execute batch command
        if self.command_manager and commands:
            batch_cmd = BatchCommand(commands, description=f"Delete {len(commands)} items")
            self.command_manager.execute_command(batch_cmd)
            
        # No need to manually remove items as observers will trigger tree rebuild
        # via handle_update callback

    def _batch_edit(self):
        """Batch edit selected items"""
        selected_items = self.selectedItems()
        if not selected_items:
            return
            
        elements = []
        for item in selected_items:
            element = self.item_to_element.get(item)
            if element:
                elements.append(element)
                
        if not elements:
            return
            
        if not self.command_manager:
            return
            
        dialog = BatchEditDialog(elements, self.command_manager, self)
        dialog.exec()
        
    def handle_update(self, event: str, data=None):
        """Observer update callback"""
        # Refresh tree when model changes
        if event in ['container_added', 'container_removed', 'parameter_added', 'modified']:
            # For now, do a simple refresh
            # In a production app, we'd do selective updates
            current = self.currentItem()
            selected_element = self.item_to_element.get(current) if current else None

            self._build_tree()

            # Try to restore selection
            if selected_element and id(selected_element) in self.element_to_item:
                item = self.element_to_item[id(selected_element)]
                self.setCurrentItem(item)

    def get_selected_container(self) -> Optional[Container]:
        """Get currently selected container"""
        current_item = self.currentItem()
        if not current_item:
            return None

        element = self.item_to_element.get(current_item)
        if isinstance(element, Container):
            return element

        return None

    def get_selected_parameter(self) -> Optional[Parameter]:
        """Get currently selected parameter"""
        current_item = self.currentItem()
        if not current_item:
            return None

        element = self.item_to_element.get(current_item)
        if isinstance(element, Parameter):
            return element

        return None
    
    def navigate_to_element(self, element):
        """
        Navigate to and select an element in the tree
        
        Args:
            element: The element to navigate to (Container or Parameter)
        """
        element_id = id(element)
        
        if element_id not in self.element_to_item:
            # Element not found in tree, might need to rebuild
            self._build_tree()
        
        if element_id in self.element_to_item:
            item = self.element_to_item[element_id]
            
            # Expand all parent items
            parent = item.parent()
            while parent:
                parent.setExpanded(True)
                parent = parent.parent()
            
            # Select and scroll to the item
            self.setCurrentItem(item)
            self.scrollToItem(item)
            
            # Emit appropriate signal
            if isinstance(element, Container):
                self.container_selected.emit(element)
            elif isinstance(element, Parameter):
                self.parameter_selected.emit(element)
