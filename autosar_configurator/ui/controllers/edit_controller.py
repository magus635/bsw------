"""Edit controller — extracted from DaVinciMainWindow (P2-6, phase 9).

Owns model-editing command handlers (parameter change, container create / delete /
batch-delete / move / rename, module delete, copy / paste) routed through the
undo stack, plus the undo clean-state handler and the instance-enumeration
helper. Holds a back-reference to the main window (``self.win``) for shared
state (config_manager, current_project, undo_stack, tree_view, config_panel,
dep_graph_controller) and Qt parenting.
"""
from typing import Any, List, Optional

from PySide6.QtWidgets import QMessageBox

from ..commands import (
    SetParameterCommand, SetReferenceCommand,
    CreateContainerCommand, DeleteContainerCommand,
    MoveContainerCommand, PasteContainerCommand,
)
from ...core.model.configuration_model import EcucContainerValue
from ...core.model.definition_model import EcucContainerDef


class EditController:
    """Model-editing command handlers for the main window."""

    def __init__(self, win):
        self.win = win

    def _on_undo_clean_changed(self, clean):
        """Handle undo stack clean state change"""
        # If stack is clean, it means we are back to saved state (if we set clean on save)
        # But we handle is_modified manually for now, so maybe just update UI?
        pass

    def handle_parameter_change(self, instance: EcucContainerValue, param_name: str, value: Any):
        """Handle parameter change request via command"""
        if not self.win.config_manager:
            return
            
        if param_name.startswith('ref:'):
            # Reference change
            ref_name = param_name[4:]
            command = SetReferenceCommand(self.win.config_manager, instance, ref_name, value)
        else:
            # Parameter change
            command = SetParameterCommand(self.win.config_manager, instance, param_name, value)
        
        try:
            self.win.undo_stack.push(command)
            self.win._has_unsaved_changes = True
            self.win.statusbar.showMessage(f"Set {param_name}", 2000)
        except Exception as e:
            # Handle validation errors gracefully
            error_msg = str(e)
            # Extract the meaningful part of the error message
            if "Error calling Python override" in error_msg:
                # Extract the actual validation message
                parts = error_msg.split(":")
                if len(parts) >= 2:
                    error_msg = ":".join(parts[-2:]).strip()
            
            QMessageBox.warning(self.win, "验证失败", f"参数值无效:\n{error_msg}")
            self.win.statusbar.showMessage(f"验证失败: {param_name}", 3000)
            return
        
        # Refresh UI if needed (e.g. if reference changed, might need to update other views)
        # For now, config panel updates itself, but tree view might need refresh if name changed (not supported yet)
        self.win.dep_graph_controller._update_dependency_graph_if_open()
        
    def handle_create_container(self, container_def: EcucContainerDef, parent_instance: Optional[EcucContainerValue], name: str):
        """Handle container creation request via command"""
        if not self.win.config_manager:
            return

        # Pre-validate: check if instance with this name already exists
        if self.win.config_manager._instance_exists(name, container_def, parent_instance):
            QMessageBox.warning(self.win, "创建失败", f"名称 '{name}' 已存在，请使用其他名称")
            self.win.statusbar.showMessage(f"创建失败: 名称已存在", 3000)
            return

        command = CreateContainerCommand(self.win.config_manager, container_def, parent_instance, name)
        self.win.undo_stack.push(command)
        
        self.win._has_unsaved_changes = True
        self.win.statusbar.showMessage(f"Created {name}", 2000)
        
        # Refresh tree view
        self.win.tree_view.refresh()
        
        # Select the new instance
        if command.created_instance:
            self.win.tree_view._select_instance(command.created_instance)
        
        self.win.dep_graph_controller._update_dependency_graph_if_open()
            
    def handle_delete_container(self, instance: EcucContainerValue, parent_instance: Optional[EcucContainerValue]):
        """Handle container deletion request via command"""
        # Find the appropriate config_manager
        config_manager = self.win.config_manager
        
        if not config_manager and self.win.current_project:
            # In project mode, find the manager for this instance
            for module_name, manager in self.win.current_project.module_managers.items():
                if manager.configuration and instance in self._get_all_instances(manager.configuration):
                    config_manager = manager
                    break
        
        if not config_manager:
            self.win.statusbar.showMessage("无法删除：未找到配置管理器", 3000)
            return
        
        # PRE-VALIDATE deletion to provide user feedback
        try:
            # Check if instance is referenced by others
            refs = config_manager._find_references_to(instance)
            if refs:
                ref_list = '\n'.join([f"  • {src.short_name}.{ref_name}" for src, ref_name in refs])
                QMessageBox.warning(
                    self.win,
                    "Cannot Delete Container",
                    f"Cannot delete '{instance.short_name}' because it is referenced by:\n\n"
                    f"{ref_list}\n\n"
                    f"Please remove these references first."
                )
                return
            
            # Note: lower_multiplicity check is skipped to give users more flexibility
            # Validation will warn about missing required instances separately
        except Exception as e:
            # If validation check fails, show error and abort
            QMessageBox.critical(
                self.win,
                "Validation Error",
                f"Failed to validate deletion:\n{str(e)}\n\nDeletion cancelled."
            )
            return
            
        command = DeleteContainerCommand(config_manager, instance, parent_instance)
        self.win.undo_stack.push(command)
        
        self.win._has_unsaved_changes = True
        self.win.statusbar.showMessage(f"已删除 {instance.short_name}", 2000)
        
        # Refresh tree view
        self.win.tree_view.refresh()
        # Clear config panel if deleted instance was selected
        if self.win.config_panel.current_instance == instance:
            self.win.config_panel.clear()

        self.win.dep_graph_controller._update_dependency_graph_if_open()
    
    def handle_delete_containers_batch(self, instances_list: list):
        """Handle batch deletion of multiple container instances
        
        Args:
            instances_list: List of (instance, parent_instance) tuples
        """
        if not instances_list:
            return
        
        # Validate all instances before deleting
        blocked_instances = []
        valid_instances = []
        
        for instance, parent_instance in instances_list:
            # Find the appropriate config_manager for this instance
            config_manager = None
            if self.win.current_project:
                # Find which module this instance belongs to
                for module_name, manager in self.win.current_project.module_managers.items():
                    if manager.configuration and instance in self._get_all_instances(manager.configuration):
                        config_manager = manager
                        break
            else:
                config_manager = self.win.config_manager
            
            if not config_manager:
                continue
            
            # Check if instance is referenced (this is a hard constraint)
            refs = config_manager._find_references_to(instance)
            if refs:
                ref_names = [f"{src.short_name}.{ref_name}" for src, ref_name in refs]
                blocked_instances.append((instance, f"被引用: {', '.join(ref_names[:3])}"))
                continue
            
            # Note: lower_multiplicity check is skipped for batch delete to give users more flexibility
            # Users can delete instances even if it would violate lower_multiplicity
            
            valid_instances.append((instance, parent_instance, config_manager))
        
        # Report blocked instances
        if blocked_instances:
            blocked_msg = "\n".join([f"  • {inst.short_name}: {reason}" for inst, reason in blocked_instances[:5]])
            if len(blocked_instances) > 5:
                blocked_msg += f"\n  ... 及其他 {len(blocked_instances) - 5} 个"
            QMessageBox.warning(
                self.win,
                "部分实例无法删除",
                f"以下实例因约束无法删除:\n\n{blocked_msg}\n\n"
                f"将继续删除其他 {len(valid_instances)} 个有效实例。"
            )
        
        if not valid_instances:
            return
        
        # Begin macro command for undo grouping
        self.win.undo_stack.beginMacro(f"批量删除 {len(valid_instances)} 个实例")
        
        deleted_count = 0
        for instance, parent_instance, config_manager in valid_instances:
            try:
                command = DeleteContainerCommand(config_manager, instance, parent_instance)
                self.win.undo_stack.push(command)
                deleted_count += 1
            except Exception as e:
                logger.warning(f"Failed to delete {instance.short_name}: {e}")
        
        self.win.undo_stack.endMacro()
        
        self.win._has_unsaved_changes = True
        self.win.statusbar.showMessage(f"已删除 {deleted_count} 个实例", 3000)
        
        # Refresh tree view
        self.win.tree_view.refresh()
        
        # Clear config panel
        self.win.config_panel.clear()
        
        self.win.dep_graph_controller._update_dependency_graph_if_open()
    
    def _get_all_instances(self, config) -> list:
        """Get all instances recursively from a configuration"""
        instances = []
        def collect(container):
            instances.append(container)
            for sub in container.sub_containers:
                collect(sub)
        for c in config.containers:
            collect(c)
        return instances
    
    def handle_delete_module(self, module_name: str):
        """Handle module deletion request from tree view"""
        if not self.win.current_project:
            QMessageBox.warning(
                self.win,
                "无法删除模块",
                "请先打开一个项目才能删除模块。"
            )
            return
        
        if module_name not in self.win.current_project.module_managers:
            QMessageBox.warning(
                self.win,
                "模块未找到",
                f"模块 '{module_name}' 不在当前项目中。"
            )
            return

        # Check for cross-module references pointing to this module
        if hasattr(self.win.current_project, 'find_references_to_module'):
            incoming_refs = self.win.current_project.find_references_to_module(module_name)
            if incoming_refs:
                ref_summary = "\n".join(
                    f"  • {src_module}: {src_container} -> {ref_name}"
                    for src_module, src_container, ref_name in incoming_refs[:10]
                )
                if len(incoming_refs) > 10:
                    ref_summary += f"\n  ... 还有 {len(incoming_refs) - 10} 个其余引用 / and {len(incoming_refs) - 10} more"
                
                reply = QMessageBox.warning(
                    self.win,
                    "检测到跨模块引用 / Cross-Module References Detected",
                    f"以下其他模块中的引用指向了模块 '{module_name}':\n\n"
                    f"{ref_summary}\n\n"
                    f"删除此模块将导致这些引用悬空，建议先清理或修改这些引用。\n"
                    f"您确定要继续删除吗？\n\n"
                    f"Deleting this module will leave references dangling in other modules:\n\n"
                    f"{ref_summary}\n\n"
                    f"Are you sure you want to proceed?",
                    QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
                    QMessageBox.StandardButton.No
                )
                if reply != QMessageBox.StandardButton.Yes:
                    return
        
        # Remove module from project (routed through undo stack)
        from ..commands import DeleteModuleCommand
        command = DeleteModuleCommand(self.win.current_project, module_name)
        self.win.undo_stack.push(command)
        
        self.win._has_unsaved_changes = True
        self.win.statusbar.showMessage(f"已删除模块: {module_name}", 3000)
        
        # Refresh tree view
        self.win.tree_view.refresh()
        
        # Clear config panel 
        self.win.config_panel.clear()
        
        # Update dependency graph if open
        self.win.dep_graph_controller._update_dependency_graph_if_open()
        
        # Update search widget index
        if self.win.search_widget:
            self.win.search_widget.build_project_index(self.win.current_project)

    def handle_move_container(self, instance: EcucContainerValue, new_parent, new_index):
        """Handle container move request via command"""
        # Resolve the config_manager that owns this instance (project mode may
        # not have an active config_manager until a module node is selected).
        config_manager = self.win.config_manager
        if not config_manager and self.win.current_project:
            for module_name, manager in self.win.current_project.module_managers.items():
                if manager.configuration and instance in self._get_all_instances(manager.configuration):
                    config_manager = manager
                    break

        if not config_manager:
            self.win.statusbar.showMessage("无法移动：未找到配置管理器", 3000)
            return

        command = MoveContainerCommand(config_manager, instance, new_parent, new_index)
        self.win.undo_stack.push(command)
        
        self.win._has_unsaved_changes = True
        self.win.statusbar.showMessage(f"Moved {instance.short_name}", 2000)
        
        # Refresh tree view
        self.win.tree_view.refresh()
        
        # Reselect
        self.win.tree_view._select_instance(instance)
        
        self.win.dep_graph_controller._update_dependency_graph_if_open()
    
    def handle_rename_container(self, instance: EcucContainerValue, new_name: str):
        """Handle container rename request — routed through undo stack."""
        if not instance or not new_name or new_name == instance.short_name:
            return

        # Resolve the config_manager that owns this instance (project mode may
        # not have an active config_manager until a module node is selected).
        config_manager = self.win.config_manager
        if not config_manager and self.win.current_project:
            for module_name, manager in self.win.current_project.module_managers.items():
                if manager.configuration and instance in self._get_all_instances(manager.configuration):
                    config_manager = manager
                    break

        if not config_manager:
            self.win.statusbar.showMessage("无法重命名：未找到配置管理器", 3000)
            return

        from ..commands import RenameContainerCommand
        cmd = RenameContainerCommand(config_manager, instance, new_name)
        self.win.undo_stack.push(cmd)

        self.win.statusbar.showMessage(f"已重命名: {instance.short_name}", 2000)

        # Refresh tree view
        self.win.tree_view.refresh()
        self.win.tree_view._select_instance(instance)

        if self.win.config_panel.current_instance == instance:
            self.win.config_panel.refresh()
        
    def copy_container(self):
        """Copy selected container to internal clipboard"""
        current_instance = self.win.tree_view.get_selected_instance()
        if not current_instance:
            self.win.statusbar.showMessage("Select a container to copy", 2000)
            return
            
        self.win.clipboard_instance = current_instance
        self.win.statusbar.showMessage(f"Copied {current_instance.short_name} to clipboard", 2000)
        
    def paste_container(self):
        """Paste container from internal clipboard"""
        if not self.win.clipboard_instance:
            self.win.statusbar.showMessage("Clipboard is empty", 2000)
            return
            
        if not self.win.config_manager:
            return
            
        # Determine target parent
        target_parent = None
        selected_instance = self.win.tree_view.get_selected_instance()
        
        # Try to prepare paste
        # Logic: 
        # 1. If selected allows child of clipboard type -> Target = Selected
        # 2. Else -> Target = Selected.parent (sibling paste)
        
        clip_def_ref = self.win.clipboard_instance.definition_ref
        clip_def = self.win.config_manager.get_container_def(clip_def_ref)
        if not clip_def:
             self.win.statusbar.showMessage("Error: Definition of copied item not found", 3000)
             return

        if selected_instance:
             # Check if selected can hold this type
             selected_def = self.win.config_manager.get_container_def(selected_instance.definition_ref)
             if selected_def and clip_def.short_name in selected_def.sub_containers:
                 target_parent = selected_instance
             else:
                 target_parent = selected_instance.parent
        else:
             # If top level selected or nothing selected (paste to root if allowed)
             # Basic logic: Paste to root if clipboard item is allowed at root
             # Check if clipboard item is a root container
             is_root_allowed = clip_def.short_name in self.win.config_manager.module_def.containers
             
             if is_root_allowed:
                 target_parent = None
             else:
                 self.win.statusbar.showMessage("Cannot paste here: Select a valid parent container", 3000)
                 return
        
        # Check multiplicity before paste
        try:
            if target_parent:
                self.win.config_manager._check_multiplicity_before_add(clip_def, target_parent)
            else:
                self.win.config_manager._check_multiplicity_before_add_toplevel(clip_def)
        except ValidationError as e:
            QMessageBox.warning(
                self.win,
                "无法粘贴",
                f"无法粘贴 '{self.win.clipboard_instance.short_name}'：\n\n{str(e)}"
            )
            return
                  
        # Clone and Rename
        try:
            new_instance = self.win.clipboard_instance.clone()
            
            # Generate a numbered name instead of _Copy suffix
            # Extract base name (remove any existing _N suffix or _Copy suffix)
            base_name = new_instance.short_name
            
            # Strip existing _Copy or _CopyN suffix
            import re
            base_name = re.sub(r'_Copy\d*$', '', base_name)
            # Strip existing _N suffix (where N is a number)
            base_name = re.sub(r'_\d+$', '', base_name)
            
            # Find next available number
            counter = 1
            candidate_name = f"{base_name}_{counter}"
            while self.win.config_manager._instance_exists(candidate_name, clip_def, target_parent):
                counter += 1
                candidate_name = f"{base_name}_{counter}"
            
            # Use auto-generated name directly (no dialog)
            new_instance.short_name = candidate_name
             
            # Command
            command = PasteContainerCommand(self.win.config_manager, target_parent, new_instance)
            self.win.undo_stack.push(command)
            
            self.win._has_unsaved_changes = True
            self.win.statusbar.showMessage(f"已粘贴 {new_instance.short_name}", 2000)
            
            # Refresh and select
            self.win.tree_view.refresh()
            self.win.tree_view._select_instance(new_instance)
            
            self.win.dep_graph_controller._update_dependency_graph_if_open()
            
        except Exception as e:
            QMessageBox.critical(self.win, "Paste Error", f"Failed to paste:\n{str(e)}")
