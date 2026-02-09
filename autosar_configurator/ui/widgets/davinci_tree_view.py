"""
DaVinci-style Tree View with dual-mode display
Shows both DEF nodes (templates) and VALUE instances
"""
from PySide6.QtWidgets import QTreeWidget, QTreeWidgetItem, QMenu, QInputDialog, QMessageBox, QAbstractItemView
from PySide6.QtCore import Qt, Signal, QMimeData
from PySide6.QtGui import QColor, QFont, QBrush, QDrag, QPixmap
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QColor, QFont, QBrush
from typing import Optional, Dict

from ...core.model.definition_model import EcucModuleDef, EcucContainerDef
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager, ValidationError
from ...core.workspace_manager import WorkspaceProject


class DaVinciTreeView(QTreeWidget):
    """Tree view displaying DEF nodes and VALUE instances in dual mode"""
    
    # Signals
    instance_selected = Signal(EcucContainerValue, EcucContainerDef, object)  # instance, definition, manager
    def_selected = Signal(EcucContainerDef, object)  # definition, manager
    module_selected = Signal(EcucModuleDef, object)  # definition, manager
    
    # Command signals
    create_instance_requested = Signal(EcucContainerDef, object, str)  # def, parent_instance, name
    delete_instance_requested = Signal(EcucContainerValue, object)  # instance, parent_instance
    delete_instances_requested = Signal(list)  # list of (instance, parent_instance) tuples for batch delete
    delete_module_requested = Signal(str)  # module_name - to remove module from project
    move_instance_requested = Signal(EcucContainerValue, object, int)  # instance, new_parent, new_index
    rename_instance_requested = Signal(EcucContainerValue, str)  # instance, new_name
    view_references_requested = Signal(EcucContainerValue)  # instance - show who references this container
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.module_def: Optional[EcucModuleDef] = None
        self.config_manager: Optional[ConfigurationManager] = None
        self.project: Optional[WorkspaceProject] = None
        self.active_variant: Optional[str] = None
        self.chip_constraint_service = None  # Service for chip-specific constraints
        
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
        
        # Drag & Drop
        self.setDragEnabled(True)
        self.setAcceptDrops(True)
        self.setDropIndicatorShown(True)
        self.setDragDropMode(QAbstractItemView.InternalMove)
        
        # Enable multi-selection with Ctrl/Shift+Click
        self.setSelectionMode(QAbstractItemView.ExtendedSelection)
    
    def set_module_def(self, module_def: EcucModuleDef, config_manager: ConfigurationManager):
        """Set module definition and configuration manager"""
        self.module_def = module_def
        self.config_manager = config_manager
        self.project = None
        
        self.refresh()

    def set_project(self, project: WorkspaceProject):
        """Set workspace project (multi-module mode)"""
        self.project = project
        self.module_def = None
        self.config_manager = None
        
        # Initialize active variant from project
        if self.project:
            self.active_variant = getattr(self.project, 'active_variant', None)
            
        self.refresh()
    
    def set_active_variant(self, variant: Optional[str]):
        """Set active variant and refresh tree filtering"""
        if self.active_variant != variant:
            self.active_variant = variant
            self.refresh()
    
    def refresh(self):
        """Refresh entire tree while preserving expansion state"""
        # Save expansion state before clearing
        expanded_state = self._save_expansion_state()
        
        self.clear()
        self.def_to_item.clear()
        self.item_to_def.clear()
        self.item_to_instance.clear()
        
        if self.project:
            self.setHeaderLabel(f"Project: {self.project.name}")
            # Render all modules in project
            for module_name, manager in self.project.module_managers.items():
                self._create_module_node(manager.module_def, manager)
        elif self.module_def and self.config_manager:
            self.setHeaderLabel("Module Configuration")
            # Render single module
            self._create_module_node(self.module_def, self.config_manager)
        
        # Restore expansion state
        self._restore_expansion_state(expanded_state)
            
    def _create_module_node(self, module_def: EcucModuleDef, config_manager: ConfigurationManager):
        """Create a top-level module node"""
        # Silent fail-safe: hide modules with missing definitions from UI
        if getattr(config_manager, 'def_missing', False):
            return

        # Detect template engine for this module
        from ...generator.generator import CodeGenerator
        from pathlib import Path
        
        project_template_dir = None
        if self.project and self.project.path:
            project_template_dir = self.project.path.parent / "templates"
        
        generator = CodeGenerator(
            module_def,
            config_manager.configuration,
            project_template_dir=project_template_dir if project_template_dir and project_template_dir.exists() else None
        )
        
        infos = generator.get_template_info(module_def.short_name)
        eb_count = sum(1 for info in infos if info['engine'] == "EB")
        std_count = sum(1 for info in infos if info['engine'] == "Standard")
        
        if eb_count > 0 and std_count > 0:
            badge = " [Mixed]"
            color = "#D97706"  # Amber for mixed
            engine_desc = "Mixed (EB + Jinja2)"
        elif eb_count > 0:
            badge = " [EB]"
            color = "#0066CC"  # Blue for EB
            engine_desc = "EB Tresos Compatible"
        else:
            badge = " [Std]"
            color = "#4B5563"  # Dark gray for Standard
            engine_desc = "Standard Jinja2"
        
        display_name = f"📦 {module_def.short_name}{badge}"
        
        # Create module root
        root_item = QTreeWidgetItem([display_name])
        root_item.setFont(0, self._get_bold_font())
        root_item.setForeground(0, QBrush(QColor(color)))
        
        # Build detailed tooltip
        tooltip_lines = [
            f"Module: {module_def.short_name}",
            f"Primary Engine: {engine_desc}",
            "\nTemplates:"
        ]
        for info in infos:
            engine_hint = "EB" if info['engine'] == "EB" else "Std"
            source_hint = "fallback" if "Fallback" in info['path'] else "custom"
            tooltip_lines.append(f"  • {info['type']}: {engine_hint} ({source_hint})")
            
        root_item.setToolTip(0, "\n".join(tooltip_lines))
            
        # Store config manager in root item for retrieval
        root_item.setData(0, Qt.UserRole, {
            "type": "MODULE", 
            "def": module_def,
            "manager": config_manager
        })
        self.addTopLevelItem(root_item)
        root_item.setExpanded(True)
        
        # Add top-level container definitions
        for container_def in module_def.containers.values():
            def_item = self._create_def_node(container_def, config_manager)
            root_item.addChild(def_item)
    
    def _create_def_node(self, container_def: EcucContainerDef, config_manager: ConfigurationManager) -> QTreeWidgetItem:
        """Create a DEF node (template node, gray italic) with instance count"""
        # Get instances for this definition
        instances = self._get_instances_for_def(container_def, config_manager)
        instance_count = len(instances)
        
        # Build display name with multiplicity and count
        mult_str = container_def.multiplicity_str
        count_str = f" ({instance_count})" if instance_count > 0 else ""
        
        # Check if required but missing
        is_required_missing = (container_def.lower_multiplicity >= 1 and instance_count == 0)
        
        if is_required_missing:
            # Required but no instances - show warning
            display_name = f"⚠️ {container_def.short_name} [{mult_str}]{count_str} - Missing!"
            icon_color = QColor("#FF6B6B")  # Red for error
        else:
            display_name = f"📋 {container_def.short_name} [{mult_str}]{count_str}"
            icon_color = QColor("#888888")  # Gray for normal
        
        item = QTreeWidgetItem([display_name])
        
        # Style: gray + italic (or red if missing)
        item.setForeground(0, QBrush(icon_color))
        item.setFont(0, self._get_italic_font())
        
        # Tooltip with more info
        tooltip = container_def.description or "Container definition"
        if is_required_missing:
            tooltip += f"\n⚠️ Required: at least {container_def.lower_multiplicity} instance(s) needed"
        elif instance_count > 0:
            tooltip += f"\n✅ {instance_count} instance(s) created"
        item.setToolTip(0, tooltip)
        
        # Store mapping
        self.item_to_def[item] = container_def
        self.def_to_item[container_def.definition_ref] = item
        
        # Store data
        item.setData(0, Qt.UserRole, {"type": "DEF", "def": container_def, "manager": config_manager})
        
        # Add existing instances under this DEF node
        self._populate_instances(item, container_def, config_manager)
        
        # Add "Add Instance..." node if more instances can be added
        # Check: is_multiple means unlimited OR check if under the limit
        can_add_more = container_def.upper_multiplicity == -1 or instance_count < container_def.upper_multiplicity
        if can_add_more:
            add_node = QTreeWidgetItem(["➕ Add Instance..."])
            add_node.setForeground(0, QBrush(QColor("#0066CC")))
            add_node.setData(0, Qt.UserRole, {"type": "ADD_PROMPT", "def": container_def, "parent_item": item, "manager": config_manager})
            item.addChild(add_node)
        
        return item
    
    def _populate_instances(self, def_item: QTreeWidgetItem, container_def: EcucContainerDef, config_manager: ConfigurationManager):
        """Populate existing container instances under a DEF node"""
        instances = self._get_instances_for_def(container_def, config_manager)
        
        for instance in instances:
            instance_item = self._create_instance_node(instance, container_def, config_manager)
            def_item.addChild(instance_item)
            def_item.setExpanded(True)  # Auto-expand if has instances
    
    def _create_instance_node(self, instance: EcucContainerValue, container_def: EcucContainerDef, config_manager: ConfigurationManager, parent_instance: Optional[EcucContainerValue] = None) -> QTreeWidgetItem:
        """Create a VALUE instance node (bold green)"""
        display_name = f"✅ {instance.short_name}"
        
        item = QTreeWidgetItem([display_name])
        
        # Style: bold + green checkmark
        item.setFont(0, self._get_bold_font())
        
        # Build rich tooltip for instance
        tooltip_lines = [f"Container Instance: {instance.short_name}"]
        if container_def.description:
            tooltip_lines.append(container_def.description)
        tooltip_lines.append(f"Definition: {container_def.short_name}")
        tooltip_lines.append(f"Parameters: {len(instance.parameter_values)}/{len(container_def.parameters)}")
        if len(container_def.sub_containers) > 0:
            tooltip_lines.append(f"Sub-containers: {len(container_def.sub_containers)} types")
        item.setToolTip(0, "\n".join(tooltip_lines))
        
        # Store mapping
        self.item_to_instance[item] = instance
        self.item_to_def[item] = container_def  # Also store definition for easy access
        
        # Store data
        item.setData(0, Qt.UserRole, {"type": "VALUE", "instance": instance, "def": container_def, "manager": config_manager, "parent_instance": parent_instance})
        
        # Add sub-containers (if any)
        for sub_def in container_def.sub_containers.values():
            sub_def_item = self._create_def_node_under_instance(sub_def, instance, config_manager)
            item.addChild(sub_def_item)
        
        return item
    
    def _create_def_node_under_instance(self, container_def: EcucContainerDef, parent_instance: EcucContainerValue, config_manager: ConfigurationManager) -> QTreeWidgetItem:
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
            "parent_instance": parent_instance,
            "manager": config_manager
        })
        
        # Add existing sub-instances (Filtered by active variant)
        sub_instances = []
        container_short_name = container_def.short_name
        for sc in parent_instance.sub_containers:
            if self._definition_refs_match(sc.definition_ref, container_def.definition_ref, container_short_name):
                # Filter by active variant:
                # 1. Match active variant
                # 2. Or instance has no variant (global)
                # 3. Or if no variant is selected in view, show all? 
                #    Actually, standard DaVinci behavior is to show what matches the variant.
                if self.active_variant is None or sc.variant is None or sc.variant == self.active_variant:
                    sub_instances.append(sc)

        
        for sub_instance in sub_instances:
            sub_instance_item = self._create_instance_node(sub_instance, container_def, config_manager, parent_instance)
            item.addChild(sub_instance_item)
        
        # Add "Add Instance..." prompt only if more instances can be added
        can_add_more = container_def.upper_multiplicity == -1 or len(sub_instances) < container_def.upper_multiplicity
        if can_add_more:
            add_node = QTreeWidgetItem(["➕ Add Instance..."])
            add_node.setForeground(0, QBrush(QColor("#0066CC")))
            add_node.setData(0, Qt.UserRole, {
                "type": "ADD_PROMPT",
                "def": container_def,
                "parent_item": item,
                "parent_instance": parent_instance,
                "manager": config_manager
            })
            item.addChild(add_node)
        
        return item
    
    def _get_instances_for_def(self, container_def: EcucContainerDef, config_manager: ConfigurationManager) -> list:
        """Get all instances of a container definition at top level
        
        Note: For EB Tresos projects, definition_ref paths may differ between module definition
        (e.g., /AUTOSAR/EcucDefs/Module/Container) and configuration values 
        (e.g., /Vendor/Module/Container). We match by container short_name instead.
        """
        if not config_manager:
            return []
        
        # Extract container short_name from definition_ref (last part of path)
        container_short_name = container_def.short_name
        
        return [
            c for c in config_manager.configuration.containers
            if self._definition_refs_match(c.definition_ref, container_def.definition_ref, container_short_name) and (
                self.active_variant is None or c.variant is None or c.variant == self.active_variant
            )
        ]
    
    def _definition_refs_match(self, config_ref: str, def_ref: str, short_name: str) -> bool:
        """Check if a config definition_ref matches a module definition's definition_ref.
        
        First tries exact match, then falls back to matching by container short_name
        (last path segment), to handle EB Tresos projects with vendor-specific paths.
        """
        # Try exact match first
        if config_ref == def_ref:
            return True
        
        # Fall back to matching by short_name (last segment of path)
        config_short_name = config_ref.rstrip('/').split('/')[-1] if config_ref else ""
        return config_short_name == short_name

    
    # Event handlers
    
    def _on_item_clicked(self, item: QTreeWidgetItem, column: int):
        """Handle item click"""
        data = item.data(0, Qt.UserRole)
        if not data:
            return
        
        item_type = data.get("type")
        manager = data.get("manager")
        
        if item_type == "MODULE":
             # Module selected - update context
             module_def = data["def"]
             self.module_selected.emit(module_def, manager)
             
        elif item_type == "VALUE":
            # Instance selected - show editable parameters
            instance = data["instance"]
            container_def = data["def"]
            self.instance_selected.emit(instance, container_def, manager)
        
        elif item_type == "DEF":
            # DEF node selected - show definition info
            container_def = data["def"]
            self.def_selected.emit(container_def, manager)
        
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
        
        if item_type == "MODULE":
            # Right-click on module node - offer "Delete Module"
            module_def = data["def"]
            module_name = module_def.short_name
            delete_action = menu.addAction("🗑️ 删除模块 (Remove Module)")
            delete_action.triggered.connect(lambda: self._delete_module(module_name))
        
        elif item_type == "DEF" or item_type == "ADD_PROMPT":
            # Right-click on DEF node - offer "Add Instance"
            container_def = data["def"]
            add_action = menu.addAction("Add Instance")
            add_action.triggered.connect(lambda: self._add_instance(container_def, data.get("parent_instance"), data.get("manager")))
        
        elif item_type == "VALUE":
            # Right-click on instance - offer actions
            instance = data["instance"]
            container_def = data["def"]
            
            # Check if multiple VALUE items are selected
            selected_items = self.selectedItems()
            value_items = [(item, item.data(0, Qt.UserRole)) for item in selected_items 
                          if item.data(0, Qt.UserRole) and item.data(0, Qt.UserRole).get("type") == "VALUE"]
            
            if len(value_items) > 1:
                # Multi-select mode - show batch delete option
                delete_action = menu.addAction(f"🗑️ 删除选中的 {len(value_items)} 个实例")
                delete_action.triggered.connect(lambda: self._delete_selected_instances())
            else:
                # Single selection mode
                # Rename instance
                rename_action = menu.addAction("✏️ 重命名")
                rename_action.triggered.connect(lambda: self._rename_instance(instance, data.get("parent_instance"), data.get("manager")))
                
                # View reverse references
                view_refs_action = menu.addAction("🔍 查看谁引用了此容器")
                view_refs_action.triggered.connect(lambda: self.view_references_requested.emit(instance))
                
                menu.addSeparator()
                
                # Delete instance
                delete_action = menu.addAction("🗑️ 删除实例")
                delete_action.triggered.connect(lambda: self._delete_instance(instance, container_def, data.get("parent_instance"), data.get("manager")))
        
        menu.exec(self.viewport().mapToGlobal(position))
    
    def _add_instance_from_prompt(self, prompt_item: QTreeWidgetItem):
        """Add instance when clicking "Add Instance..." prompt"""
        data = prompt_item.data(0, Qt.UserRole)
        container_def = data["def"]
        parent_instance = data.get("parent_instance")
        
        self._add_instance(container_def, parent_instance, data.get("manager"))
    
    def _add_instance(self, container_def: EcucContainerDef, parent_instance: Optional[EcucContainerValue] = None, config_manager: Optional[ConfigurationManager] = None):
        """Add a new container instance"""
        manager = config_manager or self.config_manager
        if not manager:
            return
        
        # Pre-validation: Check multiplicity limit before showing dialog
        if parent_instance:
            current_count = sum(1 for c in parent_instance.sub_containers if c.definition_ref == container_def.definition_ref)
        else:
            current_count = sum(1 for c in manager.configuration.containers if c.definition_ref == container_def.definition_ref)
        
        if container_def.upper_multiplicity != -1 and current_count >= container_def.upper_multiplicity:
            QMessageBox.information(
                self,
                "无法添加实例",
                f"已达到 {container_def.short_name} 的最大实例数限制 ({container_def.upper_multiplicity})。\n\n"
                f"如需添加更多实例，请先删除现有实例或检查模块定义。",
                QMessageBox.Ok
            )
            return

        # Chip-specific constraint validation
        if self.chip_constraint_service:
            chip_limit = self._get_chip_max_instances(container_def)
            if chip_limit is not None and current_count >= chip_limit:
                QMessageBox.warning(
                    self,
                    "芯片约束限制",
                    f"当前芯片型号不支持添加更多 {container_def.short_name} 实例。\n\n"
                    f"芯片最大限制: {chip_limit}\n"
                    f"当前数量: {current_count}\n\n"
                    f"请更换芯片型号或删除现有实例。",
                    QMessageBox.Ok
                )
                return

        # Ask for instance name
        default_name = manager._generate_instance_name(container_def, parent_instance)
        
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
                # Request creation via signal
                self.create_instance_requested.emit(container_def, parent_instance, name)
                
                # Note: We can't select the new instance immediately here because creation is async (via signal/command)
                # The main window should trigger a refresh and selection after processing the command
                break
                
            except Exception as e:
                QMessageBox.warning(self, "Error", str(e))
    
    def _save_expansion_state(self) -> set:
        """Save which items are currently expanded"""
        expanded = set()
        
        def traverse(item):
            if item.isExpanded():
                data = item.data(0, Qt.UserRole)
                if data:
                    # Create a unique key
                    item_type = data.get("type")
                    if item_type == "MODULE":
                        key = ("MODULE", data["def"].short_name)
                    elif item_type == "DEF":
                        key = ("DEF", data["def"].definition_ref)
                    elif item_type == "VALUE":
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
                item_type = data.get("type")
                key = None
                if item_type == "MODULE":
                    key = ("MODULE", data["def"].short_name)
                elif item_type == "DEF":
                    key = ("DEF", data["def"].definition_ref)
                elif item_type == "VALUE":
                    key = ("VALUE", data["instance"].short_name, data["instance"].definition_ref)
                
                if key and key in expanded_items:
                    item.setExpanded(True)
            
            for i in range(item.childCount()):
                traverse(item.child(i))
        
        for i in range(self.topLevelItemCount()):
            traverse(self.topLevelItem(i))
    
    def select_item_by_path(self, path: str) -> Optional[str]:
        """
        Select tree item by ARXML path.
        Returns the parameter name if the path points to a parameter, else None.
        """
        if not path:
            return None
            
        # Normalize path
        path = path.strip('/')
        parts = path.split('/')
        
        # We need to find the deepest container that matches the path
        # The path might be /Config/Module/Container/SubContainer/Parameter
        
        # Helper to get full path of an instance item
        def get_instance_path(item):
            data = item.data(0, Qt.UserRole)
            if data and data.get("type") == "VALUE":
                return data["instance"].get_path()
            return None

        # Traverse tree to find best match
        best_match_item = None
        best_match_length = 0
        
        # Breadth-first search or recursive traversal
        # Since we need to expand as we go, let's try to match level by level if possible,
        # or just search all instances. Searching all might be slow for huge trees,
        # but robust. Let's try a smart traversal.
        
        # Actually, since we have the full path, we can check if any instance path
        # is a prefix of the target path.
        
        target_path = "/" + path
        
        # We'll use a stack for traversal
        stack = []
        for i in range(self.topLevelItemCount()):
            stack.append(self.topLevelItem(i))
            
        while stack:
            item = stack.pop(0) # BFS
            
            data = item.data(0, Qt.UserRole)
            if not data:
                continue
                
            item_type = data.get("type")
            
            # If it's a VALUE (instance), check its path
            if item_type == "VALUE":
                instance = data["instance"]
                instance_path = instance.get_path()
                
                # Check for exact match
                if instance_path == target_path:
                    best_match_item = item
                    best_match_length = len(instance_path)
                    break # Found exact container match
                
                # Check if it's a parent of target (prefix match)
                # e.g. Instance: /Config/Module/Container
                # Target: /Config/Module/Container/Parameter
                if target_path.startswith(instance_path + "/"):
                    if len(instance_path) > best_match_length:
                        best_match_item = item
                        best_match_length = len(instance_path)
            
            # Add children to stack
            for i in range(item.childCount()):
                stack.append(item.child(i))
        
        if best_match_item:
            # Expand path to this item
            parent = best_match_item.parent()
            while parent:
                parent.setExpanded(True)
                parent = parent.parent()
                
            # Select and scroll
            self.setCurrentItem(best_match_item)
            self.scrollToItem(best_match_item)
            best_match_item.setExpanded(True)
            
            # Manually trigger click handler to update UI (right panel)
            self._on_item_clicked(best_match_item, 0)
            
            # Determine if there is a parameter part remaining
            # instance_path: /Config/Module/Container
            # target_path: /Config/Module/Container/Parameter
            match_path = get_instance_path(best_match_item)
            if len(target_path) > len(match_path):
                # Return the remainder as parameter name
                remainder = target_path[len(match_path):].strip('/')
                return remainder
                
        return None



    def get_selected_instance(self) -> Optional[EcucContainerValue]:
        """Get the currently selected container instance"""
        item = self.currentItem()
        if not item:
            return None
            
        data = item.data(0, Qt.UserRole)
        # Check if it's a VALUE type
        if data and data.get("type") == "VALUE":
            return data.get("instance")
        
        return None

    def select_first_module(self):
        """Select the first module in the tree (for Project mode)"""
        for i in range(self.topLevelItemCount()):
            item = self.topLevelItem(i)
            data = item.data(0, Qt.UserRole)
            if data and data.get("type") == "MODULE":
                self.setCurrentItem(item)
                self._on_item_clicked(item, 0) # Manually trigger click handler
                return
    
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
                    # Manually trigger click handler
                    self._on_item_clicked(item, 0)
                    return True
            
            for i in range(item.childCount()):
                if traverse(item.child(i)):
                    return True
            return False
        
        for i in range(self.topLevelItemCount()):
            if traverse(self.topLevelItem(i)):
                return True
        return False
    
    def select_container(self, container: EcucContainerValue):
        """Public API: Select and navigate to a container in the tree"""
        self._select_instance(container)

    def select_definition(self, definition_ref: str):
        """Find and select a specific definition in the tree (recursive)"""
        def traverse(item):
            data = item.data(0, Qt.UserRole)
            if data and data.get("type") == "DEF":
                if data["def"].definition_ref == definition_ref:
                    # Found it!
                    self.setCurrentItem(item)
                    self.scrollToItem(item)
                    # Expand all parents
                    parent = item.parent()
                    while parent:
                        parent.setExpanded(True)
                        parent = parent.parent()
                    # Manually trigger click handler
                    self._on_item_clicked(item, 0)
                    return True
            
            for i in range(item.childCount()):
                if traverse(item.child(i)):
                    return True
            return False

        # Try to find in all top-level modules
        for i in range(self.topLevelItemCount()):
            if traverse(self.topLevelItem(i)):
                return True
        return False
    
    def _delete_instance(self, instance: EcucContainerValue, container_def: EcucContainerDef, parent_instance: Optional[EcucContainerValue] = None, config_manager: Optional[ConfigurationManager] = None):
        """Delete a container instance"""
        reply = QMessageBox.question(
            self,
            "Delete Instance",
            f"Delete instance '{instance.short_name}'?",
            QMessageBox.Yes | QMessageBox.No
        )
        
        if reply == QMessageBox.No:
            return
        
        # Request deletion via signal
        self.delete_instance_requested.emit(instance, parent_instance)
    
    def _delete_selected_instances(self):
        """Delete all selected container instances (batch delete)"""
        selected_items = self.selectedItems()
        
        # Filter to only VALUE type items
        instances_to_delete = []
        for item in selected_items:
            data = item.data(0, Qt.UserRole)
            if data and data.get("type") == "VALUE":
                instance = data["instance"]
                parent_instance = data.get("parent_instance")
                instances_to_delete.append((instance, parent_instance))
        
        if not instances_to_delete:
            return
        
        # Show confirmation dialog
        names = [inst.short_name for inst, _ in instances_to_delete]
        names_preview = "\n".join(f"  • {name}" for name in names[:10])
        if len(names) > 10:
            names_preview += f"\n  ... 及其他 {len(names) - 10} 个实例"
        
        reply = QMessageBox.question(
            self,
            "批量删除实例",
            f"确定要删除以下 {len(instances_to_delete)} 个实例吗?\n\n{names_preview}",
            QMessageBox.Yes | QMessageBox.No
        )
        
        if reply == QMessageBox.No:
            return
        
        # Emit batch delete signal
        self.delete_instances_requested.emit(instances_to_delete)
    
    def _rename_instance(self, instance: EcucContainerValue, parent_instance: Optional[EcucContainerValue] = None, config_manager: Optional[ConfigurationManager] = None):
        """Rename a container instance"""
        manager = config_manager or self.config_manager
        
        # Get current name
        current_name = instance.short_name
        
        # Show input dialog
        new_name, ok = QInputDialog.getText(
            self,
            "重命名实例",
            f"请输入新名称:",
            text=current_name
        )
        
        if not ok or not new_name.strip():
            return
        
        new_name = new_name.strip()
        
        # Check if name unchanged
        if new_name == current_name:
            return
        
        # Check for name conflict
        container_def = manager.get_container_def(instance.definition_ref) if manager else None
        if manager and container_def and manager._instance_exists(new_name, container_def, parent_instance):
            QMessageBox.warning(
                self,
                "名称冲突",
                f"名称 '{new_name}' 已存在，请选择其他名称。"
            )
            return
        
        # Emit rename signal
        self.rename_instance_requested.emit(instance, new_name)
    
    def _delete_module(self, module_name: str):
        """Delete a module from the project"""
        reply = QMessageBox.question(
            self,
            "删除模块 (Delete Module)",
            f"确定要从项目中删除模块 '{module_name}' 吗?\n\n"
            f"注意: 这将移除该模块的所有配置数据。\n"
            f"(This will remove all configuration data for this module.)",
            QMessageBox.Yes | QMessageBox.No
        )
        
        if reply == QMessageBox.No:
            return
        
        # Request deletion via signal
        self.delete_module_requested.emit(module_name)
    
    # Styling helpers
    
    def _get_bold_font(self) -> QFont:
        """Get bold font"""
        font = self.font()
        font.setBold(True)
        return font
    
    # Drag & Drop Handlers
    
    def dragEnterEvent(self, event):
        """Handle drag enter"""
        item = self.currentItem()
        if item:
            data = item.data(0, Qt.UserRole)
            if data and data.get("type") == "VALUE":
                # Only allow dragging instances
                event.accept()
                return
        event.ignore()

    def dragMoveEvent(self, event):
        """Handle drag move - check drop validity"""
        # Get source item (implicitly trusted as InternalMove)
        source_items = self.selectedItems()
        if not source_items:
            event.ignore()
            return
            
        source_item = source_items[0]
        source_data = source_item.data(0, Qt.UserRole)
        instance = source_data.get("instance")
        
        # Get target info
        target_item = self.itemAt(event.position().toPoint())
        
        if not target_item or not instance:
            event.ignore()
            return
            
        target_data = target_item.data(0, Qt.UserRole)
        if not target_data:
            event.ignore()
            return
            
        target_type = target_data.get("type")
        
        # Determine potential new parent
        new_parent = None
        
        if target_type == "VALUE":
            # Target is an instance. 
            # If dropping ON it, we might be adding as child
            # If dropping BETWEEN, we might be reordering in same parent
            pass
        elif target_type == "DEF":
            # Dropping on a definition node (unlikely target for simple move unless reparenting to root/sub)
            pass
            
        # Simplified validation for now:
        # Just accept if it looks like a valid internal move, main window/model will catch invalid reparenting
        # But for UX, we should try to be stricter.
        
        # NOTE: Proper validation requires checking EcucContainerDef.sub_containers
        # For this prototype, we'll allow the drop event to proceed and validate in dropEvent
        super().dragMoveEvent(event)
        
    def dropEvent(self, event):
        """Handle drop"""
        if event.source() != self:
            return
            
        # Identify source
        source_items = self.selectedItems()
        if not source_items:
            return
        source_item = source_items[0]
        source_data = source_item.data(0, Qt.UserRole)
        instance = source_data.get("instance")
        
        if not instance:
            return
            
        # Identify drop target
        # QTreeWidget.dropEvent logic is complex for InternalMove.
        # We want to intercept it to use our Command.
        
        # Helper to calculate position details
        pos = event.position().toPoint()
        target_item = self.itemAt(pos)
        drop_indicator = self.dropIndicatorPosition()
        
        new_parent = None
        new_index = 0
        
        if target_item:
            target_data = target_item.data(0, Qt.UserRole)
            target_type = target_data.get("type")
            target_parent = target_item.parent()
            
            # Logic to determine new parent and index based on drop position
            # This is non-trivial in TreeWidget because of hierarchy.
            
            # Case 1: Dropped ON an item (OnItem)
            if drop_indicator == QAbstractItemView.OnItem:
                if target_type == "DEF":
                    # Dropped on a definition -> Add as child (if definition matches)
                    # Logic needs to check if this definition matches the instance
                    if target_data["def"].definition_ref == instance.definition_ref:
                        # Should go to parent of this DEF node? No, DEF node usually groups instances.
                        pass
                elif target_type == "VALUE":
                    # Dropped on an instance -> Make child?
                    new_parent = target_data["instance"]
                    new_index = len(new_parent.sub_containers)
            
            # Case 2: Dropped Above/Below (AboveItem, BelowItem)
            else:
                # We are inserting relative to target_item
                # New parent is target_item's parent (or None if top level)
                # But wait, our tree structure has DEF nodes as grouping nodes.
                # Structure: Module -> DEF -> Instance
                # So Instance's immediate parent in UI is a DEF node.
                # Instance's logical parent is Module or Another Instance.
                
                # If we drop relative to an Instance, we stay in same DEF group (usually).
                # New parent is logically the same as target_item's logical parent.
                
                if target_type == "VALUE":
                    target_instance = target_data["instance"]
                    new_parent = target_instance.parent
                    
                    # Calculate index
                    # We need to find where target_item is in the logical list
                    if new_parent:
                        siblings = new_parent.sub_containers
                    else:
                        siblings = self.config_manager.configuration.containers
                        
                    try:
                        target_index = siblings.index(target_instance)
                        if drop_indicator == QAbstractItemView.BelowItem:
                            new_index = target_index + 1
                        else:
                            new_index = target_index
                    except ValueError:
                        new_index = 0
                        
        # Emit signal to handle move
        # Note: This is an approximation. 
        # For simplicity in this iteration, we'll implement reordering within same parent mainly.
        # Reparenting requires checking definition compatibility.
        
        if instance.parent == new_parent:
            # Reordering
             self.move_instance_requested.emit(instance, new_parent, new_index)
             event.setDropAction(Qt.MoveAction)
             event.accept()
        else:
            # Reparenting - TODO check validity
            # For now, allow if parents match (e.g. moving between identical containers?)
            # Or just emit and let Command fail/succeed?
            self.move_instance_requested.emit(instance, new_parent, new_index)
            event.setDropAction(Qt.MoveAction)
            event.accept()

    def _get_chip_max_instances(self, container_def: EcucContainerDef) -> Optional[int]:
        """Get max instances for a container type from chip constraints"""
        if not self.chip_constraint_service:
            return None
        
        # Get module name from container definition path
        module_name = None
        # Use definition_ref (EcucContainerDef doesn't have a .path attribute)
        ref = getattr(container_def, 'definition_ref', None)
        if ref:
            parts = ref.strip('/').split('/')
            if len(parts) >= 1:
                # Handle /AUTOSAR/EcucDefs/ModuleName/...
                if parts[0] == 'AUTOSAR' and len(parts) >= 3 and parts[1] == 'EcucDefs':
                    module_name = parts[2]
                # Handle /AUTOSAR/ModuleName/...
                elif parts[0] == 'AUTOSAR' and len(parts) >= 2:
                    module_name = parts[1]
                # Handle /ModuleName/...
                else:
                    module_name = parts[0]

        
        if not module_name:
            # Try to get from active config manager if available
            if self.config_manager and self.config_manager.module_def:
                module_name = self.config_manager.module_def.short_name
        
        if not module_name:
            return None
            
        # Mapping table for common constraints
        # Key: (Module, ContainerShortName) -> Constraint Path
        mapping = {
            ('Can', 'CanController'): f"{module_name}.MaxNodes",
            ('Resource', 'ResourceCoreConfig'): f"{module_name}.NumOfCores",
            ('Resource', 'ResourceCoreConfigSet'): f"{module_name}.NumOfCores",
            # Add more mappings as needed
        }
        
        # Try specific mapping
        constraint_path = mapping.get((module_name, container_def.short_name))
        if constraint_path:
            val = self.chip_constraint_service.get_constraint(constraint_path)
            if val is not None:
                try:
                    return int(val)
                except (ValueError, TypeError):
                    return None
        
        # General mapping: {Module}.Max{ContainerName}s
        general_path = f"{module_name}.Max{container_def.short_name}s"
        val = self.chip_constraint_service.get_constraint(general_path)
        if val is not None:
            try:
                return int(val)
            except (ValueError, TypeError):
                pass
                
        return None

    def _get_italic_font(self) -> QFont:
        """Get italic font"""
        font = self.font()
        font.setItalic(True)
        return font
