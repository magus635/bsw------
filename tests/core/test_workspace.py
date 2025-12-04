"""
Tests for Workspace Manager
"""
import pytest
from pathlib import Path
from autosar_configurator.core.workspace_manager import WorkspaceManager, WorkspaceProject
from autosar_configurator.core.model.definition_model import EcucModuleDef


def test_create_project(tmp_path):
    """Test creating a new project"""
    manager = WorkspaceManager()
    project_file = tmp_path / "test.dpa"
    
    project = manager.create_project("TestProject", project_file)
    
    assert project.name == "TestProject"
    assert project.path == project_file
    assert len(project.module_managers) == 0


def test_add_module_to_project(tmp_path):
    """Test adding a module to a project"""
    manager = WorkspaceManager()
    project_file = tmp_path / "test.dpa"
    project = manager.create_project("TestProject", project_file)
    
    # Create a simple module def
    module_def = EcucModuleDef(
        short_name="TestModule",
        definition_ref="/AUTOSAR/EcucDefs/TestModule"
    )
    
    def_path = tmp_path / "TestModule_Def.arxml"
    config_manager = project.add_module(module_def, def_path)
    
    assert "TestModule" in project.module_managers
    assert config_manager is not None
    assert config_manager.module_def == module_def


def test_save_and_load_project(tmp_path):
    """Test saving and loading a project"""
    manager = WorkspaceManager()
    project_file = tmp_path / "test.dpa"
    
    # Create project and add module
    project = manager.create_project("TestProject", project_file)
    module_def = EcucModuleDef(
        short_name="TestModule",
        definition_ref="/AUTOSAR/EcucDefs/TestModule"
    )
    def_path = tmp_path / "TestModule_Def.arxml"
    
    # We need to actually create the def file for loading to work
    # For now, just test the save mechanism
    project.add_module(module_def, def_path)
    
    # Save project
    manager.save_project()
    
    assert project_file.exists()
    
    # Verify project file structure
    import json
    with open(project_file, 'r') as f:
        data = json.load(f)
    
    assert data["name"] == "TestProject"
    assert len(data["modules"]) == 1
    assert data["modules"][0]["name"] == "TestModule"


def test_remove_module(tmp_path):
    """Test removing a module from project"""
    manager = WorkspaceManager()
    project_file = tmp_path / "test.dpa"
    project = manager.create_project("TestProject", project_file)
    
    module_def = EcucModuleDef(
        short_name="TestModule",
        definition_ref="/AUTOSAR/EcucDefs/TestModule"
    )
    def_path = tmp_path / "TestModule_Def.arxml"
    project.add_module(module_def, def_path)
    
    assert "TestModule" in project.module_managers
    
    project.remove_module("TestModule")
    
    assert "TestModule" not in project.module_managers
