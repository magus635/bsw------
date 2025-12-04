"""
DaVinci-style Tree View with dual-mode display
Shows both DEF nodes (templates) and VALUE instances
"""
from PySide6.QtWidgets import QTreeWidget, QTreeWidgetItem, QMenu, QInputDialog, QMessageBox
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QColor, QFont, QBrush
from typing import Optional, Dict

from ...core.model.definition_model import EcucModuleDef, EcucContainerDef
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager, ValidationError


class DaVinciTreeView(QTreeWidget):
    """Tree view displaying DEF nodes and VALUE instances in dual mode"""
    
    # Signals
    instance_selected = Signal(EcucContainerValue, EcucContainerDef)  # instance, definition
    def_selected = Signal(EcucContainerDef)  # definition only
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.module_def: Optional[EcucModuleDef] = None
        self.config_manager: Optional[ConfigurationManager] = None
        
        # Mappings
        self.def_to_item: Dict[str, QTreeWidgetItem] = {}
        self.item_to_def: Dict[QTreeWidgetItem, EcucContainerDef] = {}
        self.item_to_instance: Dict[QTreeWidgetItem, EcucContainerValue] = {}
        
        self._setup_ui()
    
    def _setup_ui(self):
        """Setup UI"""
        self.setHeaderLabel("Module Configuration")
        self.setContextMenuPolicy(Qt.CustomContextMenu)
        self.customContextMenuRequested.connect(self._show_context_menu)
        self.itemClicked.connect(self._on_item_clicked)
        
        # Styling
        self.setAlternatingRowColors(True)
        self.setAnimated(True)
    
    def set_module_def(self, module_def: EcucModuleDef, config_manager: ConfigurationManager):
        """Set module definition and configuration manager"""
        self.module_def = module_def
        self.config_manager = config_manager
        
        self.refresh()
    
    def refresh(self):
        """Refresh entire tree"""
        self.clear()
        self.def_to_item.clear()
        self.item_to_def.clear()
        self.item_to_instance.clear()
        
        if not self.module_def or not self.config_manager:
            return
        
        # Create module root
        root_item = QTreeWidgetItem([f"📦 {self.module_def.short_name}"])
        root_item.setFont(0, self._get_bold_font())
        self.addTopLevelItem(root_item)
        root_item.setExpanded(True)
        
        # Add top-level container definitions
        for container_def in self.module_def.containers.values():
            def_item = self._create_def_node(container_def)
            root_item.addChild(def_item)
    
    def _create_def_node(self, container_def: EcucContainerDef) -> QTreeWidgetItem:
        """Create a DEF node (template node, gray italic)"""
        # Display with multiplicity
        display_name = f"📋 {container_def.short_name} [{container_def.multiplicity_str}]"
        
        item = QTreeWidgetItem([display_name])
        
        # Style: gray + italic
        item.setForeground(0, QBrush(QColor("#888888")))
        item.setFont(0, self._get_italic_font())
        item.setToolTip(0, container_def.description or "Container definition")
        
        # Store mapping
        self.item_to_def[item] = container_def
        self.def_to_item[container_def.definition_ref] = item
        
        # Store data
        item.setData(0, Qt.UserRole, {"type": "DEF", "def": container_def})
        
        # Add existing instances under this DEF node
        self._populate_instances(item, container_def)
        
        # Add "Add Instance..." node if multiple instances allowed or no instances yet
        instances = self._get_instances_for_def(container_def)
        if container_def.is_multiple or len(instances) == 0:
            add_node = QTreeWidgetItem(["➕ Add Instance..."])
            add_node.setForeground(0, QBrush(QColor("#0066CC")))
            add_node.setData(0, Qt.UserRole, {"type": "ADD_PROMPT", "def": container_def, "parent_item": item})
            item.addChild(add_node)
        
        return item
    
    def _populate_instances(self, def_item: QTreeWidgetItem, container_def: EcucContainerDef):
        """Populate existing container instances under a DEF node"""
        instances = self._get_instances_for_def(container_def)
        
        for instance in instances:
            instance_item = self._create_instance_node(instance, container_def)
            def_item.addChild(instance_item)
            def_item.setExpanded(True)  # Auto-expand if has instances
    
    def _create_instance_node(self, instance: EcucContainerValue, container_def: EcucContainerDef) -> QTreeWidgetItem:
        """Create a VALUE instance node (bold green)"""
        display_name = f"✅ {instance.short_name}"
        
        item = QTreeWidgetItem([display_name])
        
        # Style: bold + green checkmark
        item.setFont(0, self._get_bold_font())
        item.setToolTip(0, f"Container instance\nDefinition: {container_def.short_name}")
        
        # Store mapping
        self.item_to_instance[item] = instance
        self.item_to_def[item] = container_def  # Also store definition for easy access
        
        # Store data
        item.setData(0, Qt.UserRole, {"type": "VALUE", "instance": instance, "def": container_def})
        
        # Add sub-containers (if any)
        for sub_def in container_def.sub_containers.values():
            sub_def_item = self._create_def_node_under_instance(sub_def, instance)
            item.addChild(sub_def_item)
        
        return item
    
    def _create_def_node_under_instance(self, container_def: EcucContainerDef, parent_instance: EcucContainerValue) -> QTreeWidgetItem:
        """Create a DEF node under an instance (for sub-containers)"""
        display_name = f"📋 {container_def.short_name} [{container_def.multiplicity_str}]"
        
        item = QTreeWidgetItem([display_name])
        item.setForeground(0, QBrush(QColor("#888888")))
        item.setFont(0, self._get_italic_font())
        item.setToolTip(0, container_def.description or "")
        
        # Store mapping
        self.item_to_def[item] = container_def
        item.setData(0, Qt.UserRole, {
            "type": "DEF",
            "def": container_def,
            "parent_instance": parent_instance
        })
        
        # Add existing sub-instances
        sub_instances = [sc for sc in parent_instance.sub_containers if sc.definition_ref == container_def.definition_ref]
        for sub_instance in sub_instances:
            sub_instance_item = self._create_instance_node(sub_instance, container_def)
            item.addChild(sub_instance_item)
        
        # Add "Add Instance..." prompt
        if container_def.is_multiple or len(sub_instances) < container_def.upper_multiplicity:
            add_node = QTreeWidgetItem(["➕ Add Instance..."])
            add_node.setForeground(0, QBrush(QColor("#0066CC")))
            add_node.setData(0, Qt.UserRole, {
                "type": "ADD_PROMPT",
                "def": container_def,
                "parent_item": item,
                "parent_instance": parent_instance
            })
            item.addChild(add_node)
        
        return item
    
    def _get_instances_for_def(self, container_def: EcucContainerDef) -> list:
        """Get all instances of a container definition at top level"""
        if not self.config_manager:
            return []
        
        return [
            c for c in self.config_manager.configuration.containers
            if c.definition_ref == container_def.definition_ref
        ]
    
    # Event handlers
    
    def _on_item_clicked(self, item: QTreeWidgetItem, column: int):
        """Handle item click"""
        data = item.data(0, Qt.UserRole)
        if not data:
            return
        
        item_type = data.get("type")
        
        if item_type == "VALUE":
            # Instance selected - show editable parameters
            instance = data["instance"]
            container_def = data["def"]
            self.instance_selected.emit(instance, container_def)
        
        elif item_type == "DEF":
            # DEF node selected - show definition info
            container_def = data["def"]
            self.def_selected.emit(container_def)
        
        elif item_type == "ADD_PROMPT":
            # Clicked "Add Instance..." - trigger add
            self._add_instance_from_prompt(item)
    
    def _show_context_menu(self, position):
        """Show context menu"""
        item = self.itemAt(position)
        if not item:
            return
        
        data = item.data(0, Qt.UserRole)
        if not data:
            return
        
        menu = QMenu(self)
        item_type = data.get("type")
        
        if item_type == "DEF" or item_type == "ADD_PROMPT":
            # Right-click on DEF node - offer "Add Instance"
            container_def = data["def"]
            add_action = menu.addAction("Add Instance")
            add_action.triggered.connect(lambda: self._add_instance(container_def, data.get("parent_instance")))
        
        elif item_type == "VALUE":
            # Right-click on instance - offer "Delete Instance"
            instance = data["instance"]
            container_def = data["def"]
            delete_action = menu.addAction("Delete Instance")
            delete_action.triggered.connect(lambda: self._delete_instance(instance, container_def, data.get("parent_instance")))
        
        menu.exec(self.viewport().mapToGlobal(position))
    
    def _add_instance_from_prompt(self, prompt_item: QTreeWidgetItem):
        """Add instance when clicking "Add Instance..." prompt"""
        data = prompt_item.data(0, Qt.UserRole)
        container_def = data["def"]
        parent_instance = data.get("parent_instance")
        
        self._add_instance(container_def, parent_instance)
    
    def _add_instance(self, container_def: EcucContainerDef, parent_instance: Optional[EcucContainerValue] = None):
        """Add a new container instance"""
        # Ask for instance name
        default_name = self.config_manager._generate_instance_name(container_def, parent_instance)
        
        while True:
            name, ok = QInputDialog.getText(
                self,
                "Create Instance",
                f"Enter name for new {container_def.short_name} instance:",
                text=default_name
            )
            
            if not ok or not name:
                return
            
            try:
                # Create instance
                instance = self.config_manager.create_container_instance(
                    container_def,
                    parent=parent_instance,
                    instance_name=name
                )
                
                # Save current expansion state
                expanded_items = self._save_expansion_state()
                
                # Refresh tree
                self.refresh()
                
                # Restore expansion state
                self._restore_expansion_state(expanded_items)
                
                # Find and select the new instance
                self._select_instance(instance)
                
                # Success - break loop
                break
                
            except ValidationError as e:
                QMessageBox.warning(self, "Cannot Add Instance", str(e))
                # Update default name to what user typed so they can edit it
                default_name = name
    
    def _save_expansion_state(self) -> set:
        """Save which items are currently expanded"""
        expanded = set()
        
        def traverse(item):
            if item.isExpanded():
                data = item.data(0, Qt.UserRole)
                if data:
                    # Create a unique key
                    if data.get("type") == "DEF":
                        key = ("DEF", data["def"].definition_ref)
                    elif data.get("type") == "VALUE":
                        key = ("VALUE", data["instance"].short_name, data["instance"].definition_ref)
                    else:
                        key = None
                    if key:
                        expanded.add(key)
            
            for i in range(item.childCount()):
                traverse(item.child(i))
        
        for i in range(self.topLevelItemCount()):
            traverse(self.topLevelItem(i))
        
        return expanded
    
    def _restore_expansion_state(self, expanded_items: set):
        """Restore expansion state"""
        def traverse(item):
            data = item.data(0, Qt.UserRole)
            if data:
                # Check if this item should be expanded
                key = None
                if data.get("type") == "DEF":
                    key = ("DEF", data["def"].definition_ref)
                elif data.get("type") == "VALUE":
                    key = ("VALUE", data["instance"].short_name, data["instance"].definition_ref)
                
                if key and key in expanded_items:
                    item.setExpanded(True)
            
            for i in range(item.childCount()):
                traverse(item.child(i))
        
        for i in range(self.topLevelItemCount()):
            traverse(self.topLevelItem(i))
    
    def _select_instance(self, instance: EcucContainerValue):
        """Find and select a specific instance in the tree"""
        def traverse(item):
            data = item.data(0, Qt.UserRole)
            if data and data.get("type") == "VALUE":
                if data["instance"] == instance:
                    # Found it! Select and scroll to it
                    self.setCurrentItem(item)
                    self.scrollToItem(item)
                    # Also expand it
                    item.setExpanded(True)
                    return True
            
            for i in range(item.childCount()):
                if traverse(item.child(i)):
                    return True
            return False
        
        for i in range(self.topLevelItemCount()):
            if traverse(self.topLevelItem(i)):
                break
    
    def _delete_instance(self, instance: EcucContainerValue, container_def: EcucContainerDef, parent_instance: Optional[EcucContainerValue] = None):
        """Delete a container instance"""
        reply = QMessageBox.question(
            self,
            "Delete Instance",
            f"Delete instance '{instance.short_name}'?",
            QMessageBox.Yes | QMessageBox.No
        )
        
        if reply == QMessageBox.No:
            return
        
        try:
            self.config_manager.delete_container_instance(instance, parent=parent_instance)
            self.refresh()
        except ValidationError as e:
            QMessageBox.warning(self, "Cannot Delete Instance", str(e))
    
    # Styling helpers
    
    def _get_bold_font(self) -> QFont:
        """Get bold font"""
        font = self.font()
        font.setBold(True)
        return font
    
    def _get_italic_font(self) -> QFont:
        """Get italic font"""
        font = self.font()
        font.setItalic(True)
        return font
