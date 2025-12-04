"""
Unit tests for command pattern implementation
"""
import pytest
from autosar_configurator.core.command import (
    Command, CommandManager, AddContainerCommand, RemoveContainerCommand,
    AddParameterCommand, RemoveParameterCommand, ModifyParameterCommand,
    ModifyContainerCommand, BatchCommand
)
from autosar_configurator.core.model.container import Container, Parameter


class TestCommandManager:
    """Test CommandManager functionality"""
    
    def test_execute_command(self):
        """Test executing a command"""
        manager = CommandManager()
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        
        cmd = AddContainerCommand(root, child)
        manager.execute_command(cmd)
        
        assert "Child" in root.sub_containers
        assert manager.can_undo()
        assert not manager.can_redo()
    
    def test_undo(self):
        """Test undoing a command"""
        manager = CommandManager()
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        
        cmd = AddContainerCommand(root, child)
        manager.execute_command(cmd)
        
        result = manager.undo()
        
        assert result is True
        assert "Child" not in root.sub_containers
        assert not manager.can_undo()
        assert manager.can_redo()
    
    def test_redo(self):
        """Test redoing a command"""
        manager = CommandManager()
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        
        cmd = AddContainerCommand(root, child)
        manager.execute_command(cmd)
        manager.undo()
        
        result = manager.redo()
        
        assert result is True
        assert "Child" in root.sub_containers
        assert manager.can_undo()
        assert not manager.can_redo()
    
    def test_multiple_undo_redo(self):
        """Test multiple undo/redo operations"""
        manager = CommandManager()
        root = Container(short_name="Root")
        
        # Execute multiple commands
        for i in range(3):
            child = Container(short_name=f"Child{i}")
            cmd = AddContainerCommand(root, child)
            manager.execute_command(cmd)
        
        assert len(root.sub_containers) == 3
        
        # Undo all
        manager.undo()
        manager.undo()
        manager.undo()
        
        assert len(root.sub_containers) == 0
        
        # Redo all
        manager.redo()
        manager.redo()
        manager.redo()
        
        assert len(root.sub_containers) == 3
    
    def test_redo_stack_cleared_on_new_command(self):
        """Test that redo stack is cleared when new command is executed"""
        manager = CommandManager()
        root = Container(short_name="Root")
        child1 = Container(short_name="Child1")
        child2 = Container(short_name="Child2")
        
        cmd1 = AddContainerCommand(root, child1)
        manager.execute_command(cmd1)
        manager.undo()
        
        assert manager.can_redo()
        
        # Execute new command
        cmd2 = AddContainerCommand(root, child2)
        manager.execute_command(cmd2)
        
        # Redo stack should be cleared
        assert not manager.can_redo()
    
    def test_max_stack_size(self):
        """Test that command stack respects max size"""
        manager = CommandManager(max_stack_size=5)
        root = Container(short_name="Root")
        
        # Execute more commands than max stack size
        for i in range(10):
            child = Container(short_name=f"Child{i}")
            cmd = AddContainerCommand(root, child)
            manager.execute_command(cmd)
        
        # Should only be able to undo max_stack_size times
        undo_count = 0
        while manager.undo():
            undo_count += 1
        
        assert undo_count == 5
    
    def test_get_descriptions(self):
        """Test getting command descriptions"""
        manager = CommandManager()
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        
        cmd = AddContainerCommand(root, child)
        manager.execute_command(cmd)
        
        assert manager.get_undo_description() == "Add Container 'Child'"
        assert manager.get_redo_description() is None
        
        manager.undo()
        
        assert manager.get_undo_description() is None
        assert manager.get_redo_description() == "Add Container 'Child'"
    
    def test_clear(self):
        """Test clearing command history"""
        manager = CommandManager()
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        
        cmd = AddContainerCommand(root, child)
        manager.execute_command(cmd)
        
        manager.clear()
        
        assert not manager.can_undo()
        assert not manager.can_redo()


class TestAddContainerCommand:
    """Test AddContainerCommand"""
    
    def test_execute(self):
        """Test executing add container command"""
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        
        cmd = AddContainerCommand(root, child)
        cmd.execute()
        
        assert "Child" in root.sub_containers
        assert child.parent == root
    
    def test_undo(self):
        """Test undoing add container command"""
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        
        cmd = AddContainerCommand(root, child)
        cmd.execute()
        cmd.undo()
        
        assert "Child" not in root.sub_containers


class TestRemoveContainerCommand:
    """Test RemoveContainerCommand"""
    
    def test_execute(self):
        """Test executing remove container command"""
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        root.add_sub_container(child)
        
        cmd = RemoveContainerCommand(root, "Child")
        cmd.execute()
        
        assert "Child" not in root.sub_containers
    
    def test_undo(self):
        """Test undoing remove container command"""
        root = Container(short_name="Root")
        child = Container(short_name="Child")
        root.add_sub_container(child)
        
        cmd = RemoveContainerCommand(root, "Child")
        cmd.execute()
        cmd.undo()
        
        assert "Child" in root.sub_containers


class TestAddParameterCommand:
    """Test AddParameterCommand"""
    
    def test_execute(self):
        """Test executing add parameter command"""
        container = Container(short_name="Container")
        param = Parameter(short_name="Param", value=100)
        
        cmd = AddParameterCommand(container, param)
        cmd.execute()
        
        assert "Param" in container.parameters
        assert param.parent == container
    
    def test_undo(self):
        """Test undoing add parameter command"""
        container = Container(short_name="Container")
        param = Parameter(short_name="Param", value=100)
        
        cmd = AddParameterCommand(container, param)
        cmd.execute()
        cmd.undo()
        
        assert "Param" not in container.parameters


class TestRemoveParameterCommand:
    """Test RemoveParameterCommand"""
    
    def test_execute(self):
        """Test executing remove parameter command"""
        container = Container(short_name="Container")
        param = Parameter(short_name="Param", value=100)
        container.add_parameter(param)
        
        cmd = RemoveParameterCommand(container, "Param")
        cmd.execute()
        
        assert "Param" not in container.parameters
    
    def test_undo(self):
        """Test undoing remove parameter command"""
        container = Container(short_name="Container")
        param = Parameter(short_name="Param", value=100)
        container.add_parameter(param)
        
        cmd = RemoveParameterCommand(container, "Param")
        cmd.execute()
        cmd.undo()
        
        assert "Param" in container.parameters


class TestModifyParameterCommand:
    """Test ModifyParameterCommand"""
    
    def test_execute(self):
        """Test executing modify parameter command"""
        param = Parameter(short_name="Param", value=100)
        
        cmd = ModifyParameterCommand(param, "value", 100, 200)
        cmd.execute()
        
        assert param.value == 200
    
    def test_undo(self):
        """Test undoing modify parameter command"""
        param = Parameter(short_name="Param", value=100)
        
        cmd = ModifyParameterCommand(param, "value", 100, 200)
        cmd.execute()
        cmd.undo()
        
        assert param.value == 100
    
    def test_multiple_properties(self):
        """Test modifying multiple properties"""
        param = Parameter(short_name="Param", value=100, unit="ms")
        
        cmd1 = ModifyParameterCommand(param, "value", 100, 200)
        cmd2 = ModifyParameterCommand(param, "unit", "ms", "s")
        
        cmd1.execute()
        cmd2.execute()
        
        assert param.value == 200
        assert param.unit == "s"
        
        cmd2.undo()
        cmd1.undo()
        
        assert param.value == 100
        assert param.unit == "ms"


class TestModifyContainerCommand:
    """Test ModifyContainerCommand"""
    
    def test_execute(self):
        """Test executing modify container command"""
        container = Container(short_name="Container", description="Old")
        
        cmd = ModifyContainerCommand(container, "description", "Old", "New")
        cmd.execute()
        
        assert container.description == "New"
    
    def test_undo(self):
        """Test undoing modify container command"""
        container = Container(short_name="Container", description="Old")
        
        cmd = ModifyContainerCommand(container, "description", "Old", "New")
        cmd.execute()
        cmd.undo()
        
        assert container.description == "Old"


class TestBatchCommand:
    """Test BatchCommand"""
    
    def test_execute_multiple_commands(self):
        """Test executing multiple commands as batch"""
        root = Container(short_name="Root")
        child1 = Container(short_name="Child1")
        child2 = Container(short_name="Child2")
        
        commands = [
            AddContainerCommand(root, child1),
            AddContainerCommand(root, child2)
        ]
        
        batch = BatchCommand(commands, "Add Multiple Containers")
        batch.execute()
        
        assert "Child1" in root.sub_containers
        assert "Child2" in root.sub_containers
    
    def test_undo_batch(self):
        """Test undoing batch command"""
        root = Container(short_name="Root")
        child1 = Container(short_name="Child1")
        child2 = Container(short_name="Child2")
        
        commands = [
            AddContainerCommand(root, child1),
            AddContainerCommand(root, child2)
        ]
        
        batch = BatchCommand(commands, "Add Multiple Containers")
        batch.execute()
        batch.undo()
        
        assert "Child1" not in root.sub_containers
        assert "Child2" not in root.sub_containers
    
    def test_batch_with_manager(self):
        """Test batch command with command manager"""
        manager = CommandManager()
        root = Container(short_name="Root")
        child1 = Container(short_name="Child1")
        child2 = Container(short_name="Child2")
        
        commands = [
            AddContainerCommand(root, child1),
            AddContainerCommand(root, child2)
        ]
        
        batch = BatchCommand(commands, "Add Multiple Containers")
        manager.execute_command(batch)
        
        assert len(root.sub_containers) == 2
        
        manager.undo()
        
        assert len(root.sub_containers) == 0
        
        manager.redo()
        
        assert len(root.sub_containers) == 2
