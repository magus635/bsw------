import pytest
from pathlib import Path
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer
from autosar_configurator.core.parser.arxml_parser import ArxmlParser

@pytest.fixture
def sample_module_def():
    """Create a sample module definition"""
    module = EcucModuleDef(short_name="TestModule", definition_ref="/AUTOSAR/EcucDefs/TestModule")
    
    # Container definition
    container = EcucContainerDef(short_name="TestContainer", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer")
    
    # Parameters
    param_int = EcucParameterDef(short_name="IntParam", param_type="INTEGER", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/IntParam")
    param_int.min_value = 0
    param_int.max_value = 100
    container.add_parameter(param_int)
    
    param_str = EcucParameterDef(short_name="StrParam", param_type="STRING", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/StrParam")
    container.add_parameter(param_str)
    
    param_bool = EcucParameterDef(short_name="BoolParam", param_type="BOOLEAN", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/BoolParam")
    container.add_parameter(param_bool)
    
    module.add_container(container)
    return module

def test_save_load_roundtrip(sample_module_def, tmp_path):
    """Test saving and loading configuration"""
    # 1. Create configuration
    manager = ConfigurationManager(sample_module_def)
    
    # Add instance
    container_def = sample_module_def.containers["TestContainer"]
    instance = manager.create_container_instance(container_def, instance_name="TestContainer_0")
    
    # Set values
    instance.set_parameter_value("IntParam", 42, container_def.parameters["IntParam"].definition_ref)
    instance.set_parameter_value("StrParam", "Hello World", container_def.parameters["StrParam"].definition_ref)
    instance.set_parameter_value("BoolParam", True, container_def.parameters["BoolParam"].definition_ref)
    
    # 2. Save to file
    output_file = tmp_path / "TestConfig.arxml"
    manager.save_configuration(output_file)
    
    assert output_file.exists()
    
    # 3. Load back
    # Create new manager
    new_manager = ConfigurationManager(sample_module_def)
    new_manager.load_configuration(output_file)
    
    # 4. Verify
    assert len(new_manager.configuration.containers) == 1
    loaded_instance = new_manager.configuration.containers[0]
    
    assert loaded_instance.short_name == "TestContainer_0"
    assert loaded_instance.parameter_values["IntParam"].value == 42
    assert loaded_instance.parameter_values["StrParam"].value == "Hello World"
    assert loaded_instance.parameter_values["BoolParam"].value is True

def test_save_load_complex_structure(sample_module_def, tmp_path):
    """Test saving and loading nested containers"""
    # Add sub-container def
    parent_def = sample_module_def.containers["TestContainer"]
    sub_def = EcucContainerDef(short_name="SubContainer", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/SubContainer")
    parent_def.add_sub_container(sub_def)
    
    manager = ConfigurationManager(sample_module_def)
    
    # Create parent
    parent = manager.create_container_instance(parent_def, instance_name="Parent_0")
    
    # Create child
    child = manager.create_container_instance(sub_def, parent=parent, instance_name="Child_0")
    
    # Save
    output_file = tmp_path / "ComplexConfig.arxml"
    manager.save_configuration(output_file)
    
    # Load
    new_manager = ConfigurationManager(sample_module_def)
    new_manager.load_configuration(output_file)
    
    # Verify
    assert len(new_manager.configuration.containers) == 1
    loaded_parent = new_manager.configuration.containers[0]
    assert len(loaded_parent.sub_containers) == 1
    loaded_child = loaded_parent.sub_containers[0]
    
    assert loaded_parent.short_name == "Parent_0"
    assert loaded_child.short_name == "Child_0"
