import pytest
from pathlib import Path
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType, EcucReferenceDef
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue, EcucParameterValue, EcucReferenceValue
from autosar_configurator.core.config_manager import ConfigurationManager, ValidationError
from autosar_configurator.core.validation_engine import ValidationSeverity, ValidationResult
from autosar_configurator.ui.commands import RenameContainerCommand, MoveContainerCommand
from PySide6.QtGui import QUndoStack

def test_p1_2_boolean_validation():
    # Setup simple module def with boolean param
    module_def = EcucModuleDef(short_name="TestModule", definition_ref="/AUTOSAR/EcucDefs/TestModule")
    container_def = EcucContainerDef(short_name="TestContainer", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer")
    container_def.upper_multiplicity = -1
    param_def = EcucParameterDef("TestBool", EcucParameterType.BOOLEAN, "/AUTOSAR/EcucDefs/TestModule/TestContainer/TestBool")
    container_def.parameters["TestBool"] = param_def
    module_def.containers["TestContainer"] = container_def

    manager = ConfigurationManager(module_def)
    container = manager.create_container_instance(container_def)

    # Test valid boolean strings
    manager.set_parameter_value(container, "TestBool", "true")
    assert container.parameter_values["TestBool"].value is True
    manager.set_parameter_value(container, "TestBool", "false")
    assert container.parameter_values["TestBool"].value is False
    manager.set_parameter_value(container, "TestBool", "1")
    assert container.parameter_values["TestBool"].value is True
    manager.set_parameter_value(container, "TestBool", "no")
    assert container.parameter_values["TestBool"].value is False

    # Test invalid boolean string
    with pytest.raises(ValidationError) as excinfo:
        manager.set_parameter_value(container, "TestBool", "invalid_bool_str")
    assert "invalid boolean string" in str(excinfo.value)


def test_p1_3_custom_rule_loading_error():
    module_def = EcucModuleDef(short_name="TestModule", definition_ref="/AUTOSAR/EcucDefs/TestModule")
    manager = ConfigurationManager(module_def)

    # Add a non-existent rule file
    manager.add_custom_rule_file(Path("non_existent_rules.py"))
    
    # Validation should continue and record a warning message
    result = manager.validate_configuration()
    assert len(result.messages) == 1
    msg = result.messages[0]
    assert msg.severity == ValidationSeverity.WARNING
    assert "Custom rule file" in msg.message
    assert "failed to load" in msg.message


def test_p1_23_clone_metadata_preservation():
    module_def = EcucModuleDef(short_name="TestModule", definition_ref="/AUTOSAR/EcucDefs/TestModule")
    container_def = EcucContainerDef(short_name="TestContainer", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer")
    module_def.containers["TestContainer"] = container_def

    manager = ConfigurationManager(module_def)
    container = manager.create_container_instance(container_def)

    # Set parameters and references with custom metadata
    container.parameter_values["Param1"] = EcucParameterValue(
        definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/Param1",
        value=42,
        index=3,
        dest_type="ECUC-INTEGER-PARAM-DEF"
    )
    container.multi_parameter_values["MultiParam1"] = [
        EcucParameterValue(
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/MultiParam1",
            value="str_val",
            index=5,
            dest_type="ECUC-STRING-PARAM-DEF"
        )
    ]
    container.reference_values["Ref1"] = EcucReferenceValue(
        definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/Ref1",
        value_ref="/TestModule/TargetContainer",
        dest_type="ECUC-REFERENCE-DEF"
    )
    container.multi_reference_values["MultiRef1"] = [
        EcucReferenceValue(
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/MultiRef1",
            value_ref="/TestModule/TargetContainer2",
            index=2,
            dest_type="ECUC-REFERENCE-DEF"
        )
    ]

    # Clone the container
    cloned = container.clone()

    # Verify cloning preserved metadata
    assert cloned.parameter_values["Param1"].index == 3
    assert cloned.parameter_values["Param1"].dest_type == "ECUC-INTEGER-PARAM-DEF"

    assert cloned.multi_parameter_values["MultiParam1"][0].index == 5
    assert cloned.multi_parameter_values["MultiParam1"][0].dest_type == "ECUC-STRING-PARAM-DEF"

    assert cloned.reference_values["Ref1"].dest_type == "ECUC-REFERENCE-DEF"

    assert cloned.multi_reference_values["MultiRef1"][0].index == 2
    assert cloned.multi_reference_values["MultiRef1"][0].dest_type == "ECUC-REFERENCE-DEF"


def test_p1_24_p1_25_registry_rebuild():
    module_def = EcucModuleDef(short_name="TestModule", definition_ref="/AUTOSAR/EcucDefs/TestModule")
    container_def = EcucContainerDef(short_name="TestContainer", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer")
    container_def.upper_multiplicity = -1
    module_def.containers["TestContainer"] = container_def

    manager = ConfigurationManager(module_def)
    
    container1 = manager.create_container_instance(container_def)
    container1.short_name = "C1"
    # Rebuild registry to ensure it's recorded with the right path
    manager._rebuild_instance_registry()

    assert manager.configuration.get_instance_by_path("/TestModule/C1") is container1

    # Test RenameCommand rebuilds registry
    command = RenameContainerCommand(manager, container1, "C1_Renamed")
    command.redo()
    assert manager.configuration.get_instance_by_path("/TestModule/C1") is None
    assert manager.configuration.get_instance_by_path("/TestModule/C1_Renamed") is container1

    # Test MoveContainerCommand rebuilds registry
    container2 = manager.create_container_instance(container_def)
    container2.short_name = "C2"
    manager._rebuild_instance_registry()
    assert manager.configuration.get_instance_by_path("/TestModule/C2") is container2

    # Move C2 under C1_Renamed
    move_command = MoveContainerCommand(manager, container2, container1, 0)
    move_command.redo()
    assert manager.configuration.get_instance_by_path("/TestModule/C2") is None
    assert manager.configuration.get_instance_by_path("/TestModule/C1_Renamed/C2") is container2


def test_p1_8_multi_ref_validation():
    from autosar_configurator.core.rules.reference_rules import ResolutionErrorValidationRule, ReferenceIntegrityRule
    from autosar_configurator.core.model.configuration_model import ResolutionError

    module_def = EcucModuleDef(short_name="TestModule", definition_ref="/AUTOSAR/EcucDefs/TestModule")
    container_def = EcucContainerDef(short_name="TestContainer", definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer")
    module_def.containers["TestContainer"] = container_def

    manager = ConfigurationManager(module_def)

    container = manager.create_container_instance(container_def)
    ref_value = EcucReferenceValue(
        definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/MultiRef",
        value_ref="/TestModule/NonExistent",
        index=0
    )
    # Add to multi_reference_values
    container.multi_reference_values["MultiRef"] = [ref_value]

    # 1. Test ReferenceIntegrityRule
    rule = ReferenceIntegrityRule()
    result = rule.validate(module_def, manager.configuration)
    assert len(result.messages) == 1
    assert "Multi-Reference 'MultiRef[0]'" in result.messages[0].message
    assert "points to non-existent container" in result.messages[0].message

    # 2. Test ResolutionErrorValidationRule
    # Simulate a resolution error on the multi-reference value
    ref_value.resolution_error = ResolutionError(
        error_type="DanglingReference",
        path="/TestModule/NonExistent",
        message="Dangling reference path",
        severity="error",
        suggestion="Fix path"
    )
    res_rule = ResolutionErrorValidationRule()
    res_result = res_rule.validate(module_def, manager.configuration)
    assert len(res_result.messages) == 1
    assert "Multi-Reference 'MultiRef[0]'" in res_result.messages[0].message
