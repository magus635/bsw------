"""
Undo/Redo Commands for AUTOSAR Configurator
"""
from PySide6.QtGui import QUndoCommand
from typing import Optional, Any
from ..core.model.configuration_model import EcucContainerValue, EcucModuleConfiguration
from ..core.model.definition_model import EcucContainerDef
from ..core.config_manager import ConfigurationManager

class SetParameterCommand(QUndoCommand):
    """Command to set a parameter value"""
    
    def __init__(self, 
                 config_manager: ConfigurationManager,
                 instance: EcucContainerValue,
                 param_name: str,
                 new_value: Any):
        super().__init__()
        self.config_manager = config_manager
        self.instance = instance
        self.param_name = param_name
        self.new_value = new_value
        self.old_value = None
        
        # Capture old value
        if param_name in instance.parameter_values:
            self.old_value = instance.parameter_values[param_name].value
        else:
            # If not set, try to get default from definition
            param_def = config_manager._get_parameter_def(instance, param_name)
            if param_def:
                self.old_value = param_def.default_value
        
        self.setText(f"Set {param_name}")

    def redo(self):
        self.config_manager.set_parameter_value(self.instance, self.param_name, self.new_value)

    def undo(self):
        if self.old_value is not None:
            self.config_manager.set_parameter_value(self.instance, self.param_name, self.old_value)
        # If old value was None (not set and no default), we might want to unset it?
        # But set_parameter_value handles setting values. 
        # For now assuming reverting to old value (even if default) is fine.

class SetReferenceCommand(QUndoCommand):
    """Command to set a reference value"""
    
    def __init__(self,
                 config_manager: ConfigurationManager,
                 instance: EcucContainerValue,
                 ref_name: str,
                 new_target: str):
        super().__init__()
        self.config_manager = config_manager
        self.instance = instance
        self.ref_name = ref_name
        self.new_target = new_target
        self.old_target = None
        
        # Capture old target
        if ref_name in instance.reference_values:
            self.old_target = instance.reference_values[ref_name].value_ref
            
        self.setText(f"Set Reference {ref_name}")

    def redo(self):
        if self.new_target:
            # We need the definition ref for the reference
            container_def = self.config_manager.get_container_def(self.instance.definition_ref)
            if container_def and self.ref_name in container_def.references:
                ref_def = container_def.references[self.ref_name]
                self.instance.set_reference_value(self.ref_name, self.new_target, ref_def.definition_ref)
                
                # Immediately resolve the reference to update status to ✅
                ref_value = self.instance.reference_values.get(self.ref_name)
                if ref_value:
                    # Try to resolve via project (cross-module) or config_manager (single module)
                    target = None
                    if hasattr(self.config_manager, 'project_context') and self.config_manager.project_context:
                        target = self.config_manager.project_context.get_instance_by_path(self.new_target)
                    
                    if target is None:
                        # Try single-module resolution
                        target = self.config_manager.configuration.get_instance_by_path(self.new_target)
                    
                    if target:
                        ref_value.target = target
                        ref_value.resolution_error = None
                    else:
                        # Set resolution error
                        from ..core.model.configuration_model import ResolutionError
                        ref_value.resolution_error = ResolutionError(
                            ResolutionError.PATH_NOT_FOUND,
                            self.new_target
                        )
        else:
            # Clear reference
            if self.ref_name in self.instance.reference_values:
                del self.instance.reference_values[self.ref_name]
                self.instance.mark_modified()

    def undo(self):
        if self.old_target:
            container_def = self.config_manager.get_container_def(self.instance.definition_ref)
            if container_def and self.ref_name in container_def.references:
                ref_def = container_def.references[self.ref_name]
                self.instance.set_reference_value(self.ref_name, self.old_target, ref_def.definition_ref)
        else:
            # Clear reference
            if self.ref_name in self.instance.reference_values:
                del self.instance.reference_values[self.ref_name]
                self.instance.mark_modified()

class CreateContainerCommand(QUndoCommand):
    """Command to create a container instance"""
    
    def __init__(self,
                 config_manager: ConfigurationManager,
                 container_def: EcucContainerDef,
                 parent_instance: Optional[EcucContainerValue],
                 instance_name: str):
        super().__init__()
        self.config_manager = config_manager
        self.container_def = container_def
        self.parent_instance = parent_instance
        self.instance_name = instance_name
        self.created_instance = None
        
        self.setText(f"Create {instance_name}")

    def redo(self):
        # If we already created it (redo), we might need to restore it?
        # Actually create_container_instance creates a new object.
        # Ideally we should reuse the object if possible to keep references valid,
        # but for now let's recreate it.
        # Wait, if we recreate it, other commands on the stack referencing the old object will fail.
        # So we MUST reuse the instance if it exists.
        
        if self.created_instance:
            # Restore the previously created instance
            if self.parent_instance:
                self.parent_instance.add_sub_container(self.created_instance)
            else:
                self.config_manager.configuration.add_container(self.created_instance)
        else:
            # First time creation
            self.created_instance = self.config_manager.create_container_instance(
                self.container_def,
                parent=self.parent_instance,
                instance_name=self.instance_name
            )

    def undo(self):
        if self.created_instance:
            self.config_manager.delete_container_instance(
                self.created_instance,
                parent=self.parent_instance
            )

class DeleteContainerCommand(QUndoCommand):
    """Command to delete a container instance"""
    
    def __init__(self,
                 config_manager: ConfigurationManager,
                 instance: EcucContainerValue,
                 parent_instance: Optional[EcucContainerValue]):
        super().__init__()
        self.config_manager = config_manager
        self.instance = instance
        self.parent_instance = parent_instance
        
        self.setText(f"Delete {instance.short_name}")

    def redo(self):
        self.config_manager.delete_container_instance(
            self.instance,
            parent=self.parent_instance
        )

    def undo(self):
        # Restore the instance
        self.config_manager.add_container_instance(self.instance, self.parent_instance)

class MoveContainerCommand(QUndoCommand):
    """Command to move a container to a new parent or reorder"""
    
    def __init__(self,
                 config_manager: ConfigurationManager,
                 instance: EcucContainerValue,
                 new_parent: Optional[EcucContainerValue],
                 new_index: int):
        super().__init__()
        self.config_manager = config_manager
        self.instance = instance
        self.new_parent = new_parent
        self.new_index = new_index
        
        # Capture old state
        self.old_parent = instance.parent
        self.old_index = 0
        
        # Find old index
        if self.old_parent:
            if instance in self.old_parent.sub_containers:
                self.old_index = self.old_parent.sub_containers.index(instance)
        else:
            # Top level
            if instance in self.config_manager.configuration.containers:
                self.old_index = self.config_manager.configuration.containers.index(instance)
        
        self.setText(f"Move {instance.short_name}")

    def redo(self):
        self._move(self.instance, self.old_parent, self.new_parent, self.new_index)

    def undo(self):
        self._move(self.instance, self.new_parent, self.old_parent, self.old_index)
        
    def _move(self, instance, source_parent, target_parent, target_index):
        # Remove from source
        if source_parent:
            if instance in source_parent.sub_containers:
                source_parent.sub_containers.remove(instance)
                source_parent.mark_modified()
        else:
            if instance in self.config_manager.configuration.containers:
                self.config_manager.configuration.containers.remove(instance)
                self.config_manager.configuration.is_modified = True
                
        # Update parent reference
        instance.parent = target_parent
        
        # Add to target at index
        if target_parent:
            # Insert at specific index
            if 0 <= target_index <= len(target_parent.sub_containers):
                target_parent.sub_containers.insert(target_index, instance)
            else:
                target_parent.sub_containers.append(instance)
            target_parent.mark_modified()
        else:
            # Top level
            if 0 <= target_index <= len(self.config_manager.configuration.containers):
                self.config_manager.configuration.containers.insert(target_index, instance)
            else:
                self.config_manager.configuration.add_container(instance)
            self.config_manager.configuration.is_modified = True
        
        instance.mark_modified()

class PasteContainerCommand(QUndoCommand):
    """Command to paste (add) a container instance"""
    
    def __init__(self, config_manager, parent_instance, new_instance):
        super().__init__()
        self.config_manager = config_manager
        self.parent_instance = parent_instance
        self.new_instance = new_instance
        
        self.setText(f"Paste {new_instance.short_name}")
        
    def redo(self):
        self.config_manager.add_container_instance(self.new_instance, self.parent_instance)
        
    def undo(self):
        self.config_manager.delete_container_instance(self.new_instance, self.parent_instance)
