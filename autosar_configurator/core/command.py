"""
Command Pattern implementation for Undo/Redo functionality
"""
from abc import ABC, abstractmethod
from typing import List, Optional, Any
from threading import RLock
from .model.container import Container, Parameter


class Command(ABC):
    """Abstract base class for all commands"""
    
    def __init__(self):
        self._executed = False
    
    @abstractmethod
    def execute(self) -> None:
        """Execute the command"""
        pass
    
    @abstractmethod
    def undo(self) -> None:
        """Undo the command"""
        pass
    
    def redo(self) -> None:
        """Redo the command (default implementation re-executes)"""
        self.execute()
    
    @property
    def executed(self) -> bool:
        """Check if command has been executed"""
        return self._executed
    
    @abstractmethod
    def description(self) -> str:
        """Get a human-readable description of the command"""
        pass


class CommandManager:
    """Manages command execution and undo/redo stacks"""
    
    def __init__(self, max_stack_size: int = 50):
        """
        Initialize command manager
        
        Args:
            max_stack_size: Maximum number of commands to keep in history
        """
        self._undo_stack: List[Command] = []
        self._redo_stack: List[Command] = []
        self._max_stack_size = max_stack_size
        self._lock = RLock()
    
    def execute_command(self, command: Command) -> None:
        """
        Execute a command and add it to the undo stack
        
        Args:
            command: Command to execute
        """
        with self._lock:
            command.execute()
            self._undo_stack.append(command)
            
            # Clear redo stack when new command is executed
            self._redo_stack.clear()
            
            # Limit stack size
            if len(self._undo_stack) > self._max_stack_size:
                self._undo_stack.pop(0)
    
    def undo(self) -> bool:
        """
        Undo the last command
        
        Returns:
            True if undo was successful, False if nothing to undo
        """
        with self._lock:
            if not self._undo_stack:
                return False
            
            command = self._undo_stack.pop()
            command.undo()
            self._redo_stack.append(command)
            return True
    
    def redo(self) -> bool:
        """
        Redo the last undone command
        
        Returns:
            True if redo was successful, False if nothing to redo
        """
        with self._lock:
            if not self._redo_stack:
                return False
            
            command = self._redo_stack.pop()
            command.redo()
            self._undo_stack.append(command)
            return True
    
    def can_undo(self) -> bool:
        """Check if undo is available"""
        return len(self._undo_stack) > 0
    
    def can_redo(self) -> bool:
        """Check if redo is available"""
        return len(self._redo_stack) > 0
    
    def clear(self) -> None:
        """Clear all command history"""
        with self._lock:
            self._undo_stack.clear()
            self._redo_stack.clear()
    
    def get_undo_description(self) -> Optional[str]:
        """Get description of the command that would be undone"""
        if self._undo_stack:
            return self._undo_stack[-1].description()
        return None
    
    def get_redo_description(self) -> Optional[str]:
        """Get description of the command that would be redone"""
        if self._redo_stack:
            return self._redo_stack[-1].description()
        return None


class AddContainerCommand(Command):
    """Command to add a sub-container"""
    
    def __init__(self, parent: Container, container: Container):
        """
        Initialize command
        
        Args:
            parent: Parent container
            container: Container to add
        """
        super().__init__()
        self.parent = parent
        self.container = container
        self.container_name = container.short_name
    
    def execute(self) -> None:
        """Add the container to parent"""
        self.parent.add_sub_container(self.container)
        self._executed = True
    
    def undo(self) -> None:
        """Remove the container from parent"""
        self.parent.remove_sub_container(self.container_name)
        self._executed = False
    
    def description(self) -> str:
        return f"Add Container '{self.container_name}'"


class RemoveContainerCommand(Command):
    """Command to remove a sub-container"""
    
    def __init__(self, parent: Container, container_name: str):
        """
        Initialize command
        
        Args:
            parent: Parent container
            container_name: Name of container to remove
        """
        super().__init__()
        self.parent = parent
        self.container_name = container_name
        self.container: Optional[Container] = None
    
    def execute(self) -> None:
        """Remove the container from parent"""
        self.container = self.parent.remove_sub_container(self.container_name)
        self._executed = True
    
    def undo(self) -> None:
        """Re-add the container to parent"""
        if self.container:
            self.parent.add_sub_container(self.container)
        self._executed = False
    
    def description(self) -> str:
        return f"Remove Container '{self.container_name}'"


class AddParameterCommand(Command):
    """Command to add a parameter"""
    
    def __init__(self, container: Container, parameter: Parameter):
        """
        Initialize command
        
        Args:
            container: Container to add parameter to
            parameter: Parameter to add
        """
        super().__init__()
        self.container = container
        self.parameter = parameter
        self.parameter_name = parameter.short_name
    
    def execute(self) -> None:
        """Add the parameter to container"""
        self.container.add_parameter(self.parameter)
        self._executed = True
    
    def undo(self) -> None:
        """Remove the parameter from container"""
        self.container.remove_parameter(self.parameter_name)
        self._executed = False
    
    def description(self) -> str:
        return f"Add Parameter '{self.parameter_name}'"


class RemoveParameterCommand(Command):
    """Command to remove a parameter"""
    
    def __init__(self, container: Container, parameter_name: str):
        """
        Initialize command
        
        Args:
            container: Container to remove parameter from
            parameter_name: Name of parameter to remove
        """
        super().__init__()
        self.container = container
        self.parameter_name = parameter_name
        self.parameter: Optional[Parameter] = None
    
    def execute(self) -> None:
        """Remove the parameter from container"""
        self.parameter = self.container.remove_parameter(self.parameter_name)
        self._executed = True
    
    def undo(self) -> None:
        """Re-add the parameter to container"""
        if self.parameter:
            self.container.add_parameter(self.parameter)
        self._executed = False
    
    def description(self) -> str:
        return f"Remove Parameter '{self.parameter_name}'"


class ModifyParameterCommand(Command):
    """Command to modify a parameter's properties"""
    
    def __init__(self, parameter: Parameter, property_name: str, 
                 old_value: Any, new_value: Any):
        """
        Initialize command
        
        Args:
            parameter: Parameter to modify
            property_name: Name of property to modify
            old_value: Original value
            new_value: New value
        """
        super().__init__()
        self.parameter = parameter
        self.property_name = property_name
        self.old_value = old_value
        self.new_value = new_value
    
    def execute(self) -> None:
        """Set the new value"""
        setattr(self.parameter, self.property_name, self.new_value)
        self.parameter.mark_dirty()
        self._executed = True
    
    def undo(self) -> None:
        """Restore the old value"""
        setattr(self.parameter, self.property_name, self.old_value)
        self.parameter.mark_dirty()
        self._executed = False
    
    def description(self) -> str:
        return f"Modify Parameter '{self.parameter.short_name}.{self.property_name}'"


class ModifyContainerCommand(Command):
    """Command to modify a container's properties"""
    
    def __init__(self, container: Container, property_name: str,
                 old_value: Any, new_value: Any):
        """
        Initialize command
        
        Args:
            container: Container to modify
            property_name: Name of property to modify
            old_value: Original value
            new_value: New value
        """
        super().__init__()
        self.container = container
        self.property_name = property_name
        self.old_value = old_value
        self.new_value = new_value
    
    def execute(self) -> None:
        """Set the new value"""
        setattr(self.container, self.property_name, self.new_value)
        self.container.mark_dirty()
        self._executed = True
    
    def undo(self) -> None:
        """Restore the old value"""
        setattr(self.container, self.property_name, self.old_value)
        self.container.mark_dirty()
        self._executed = False
    
    def description(self) -> str:
        return f"Modify Container '{self.container.short_name}.{self.property_name}'"


class BatchCommand(Command):
    """Command that executes multiple commands as a single atomic operation"""
    
    def __init__(self, commands: List[Command], description: str = "Batch Operation"):
        """
        Initialize batch command
        
        Args:
            commands: List of commands to execute
            description: Description of the batch operation
        """
        super().__init__()
        self.commands = commands
        self._description = description
    
    def execute(self) -> None:
        """Execute all commands"""
        for command in self.commands:
            command.execute()
        self._executed = True
    
    def undo(self) -> None:
        """Undo all commands in reverse order"""
        for command in reversed(self.commands):
            command.undo()
        self._executed = False
    
    def description(self) -> str:
        return self._description
