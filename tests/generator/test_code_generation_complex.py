"""
Tests for code generator with complex configurations
"""
import pytest
from pathlib import Path
from autosar_configurator.generator.generator import CodeGenerator
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucReferenceDef, EcucParameterType
)
from autosar_configurator.core.config_manager import ConfigurationManager


def test_reference_resolution():
    """Test that references are correctly resolved to C symbols"""
    # Create module def
    module = EcucModuleDef(short_name="Adc", definition_ref="/AUTOSAR/EcucDefs/Adc")
    
    # Add containers
    config_set = EcucContainerDef(short_name="AdcConfigSet", definition_ref="/AUTOSAR/EcucDefs/Adc/AdcConfigSet")
    
    # Add reference parameter
    clock_ref = EcucReferenceDef(
        short_name="AdcClockRef",
        destination_ref="/AUTOSAR/EcucDefs/Mcu/McuModuleConfiguration",
        definition_ref="/AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcClockRef"
    )
    config_set.add_reference(clock_ref)
    
    module.add_container(config_set)
    
    # Create configuration
    manager = ConfigurationManager(module)
    container_instance = manager.create_container_instance(config_set, instance_name="AdcConfigSet_0")
    
    # Set reference value
    container_instance.set_reference_value(
        "AdcClockRef", 
        "/Config/Mcu/McuModuleConfiguration/McuClockSettingConfig",
        clock_ref.definition_ref
    )
    
    # Generate code
    generator = CodeGenerator(module, manager.configuration)
    context = generator._prepare_context()
    
    # Verify reference is resolved
    assert len(context['containers']) == 1
    container = context['containers'][0]
    assert len(container.reference_values) == 1
    
    ref_name = list(container.reference_values.keys())[0]
    ref_value = container.reference_values[ref_name]
    assert ref_name == 'AdcClockRef'
    assert f"&{generator.resolve_ref(ref_value.value_ref)}_Config" == '&Mcu_McuModuleConfiguration_McuClockSettingConfig_Config'


def test_value_type_formatting():
    """Test that values are formatted correctly for C code"""
    generator = CodeGenerator(None, None)
    
    # Test boolean
    assert generator._format_value(True) == "TRUE"
    assert generator._format_value(False) == "FALSE"
    
    # Test integer
    assert generator._format_value(42) == "42"
    assert generator._format_value(0) == "0"
    
    # Test float
    assert generator._format_value(3.14) == "3.14"
    
    # Test string (enumeration)
    assert generator._format_value("ENABLED") == "ENABLED"
    assert generator._format_value("SARADC0") == "SARADC0"
    
    # Test string (regular string)
    assert generator._format_value("hello world") == '"hello world"'
    
    # Test NULL
    assert generator._format_value(None) == "NULL"


def test_complete_generation_with_references(tmp_path):
    """Test complete code generation with references"""
    # Create module def
    module = EcucModuleDef(short_name="Adc", definition_ref="/AUTOSAR/EcucDefs/Adc")
    
    # Add container with parameters and references
    config_set = EcucContainerDef(short_name="AdcConfigSet", definition_ref="/AUTOSAR/EcucDefs/Adc/AdcConfigSet")
    
    # Add parameters
    enabled_param = EcucParameterDef(
        short_name="AdcDevEnabled",
        param_type=EcucParameterType.BOOLEAN,
        definition_ref="/AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcDevEnabled",
        config_class="PRE-COMPILE"
    )
    prescaler_param = EcucParameterDef(
        short_name="AdcPrescale",
        param_type=EcucParameterType.INTEGER,
        definition_ref="/AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcPrescale",
        config_class="PRE-COMPILE"
    )
    config_set.add_parameter(enabled_param)
    config_set.add_parameter(prescaler_param)
    
    # Add reference
    clock_ref = EcucReferenceDef(
        short_name="AdcClockRef",
        destination_ref="/AUTOSAR/EcucDefs/Mcu/McuModuleConfiguration",
        definition_ref="/AUTOSAR/EcucDefs/Adc/AdcConfigSet/AdcClockRef"
    )
    config_set.add_reference(clock_ref)
    
    module.add_container(config_set)
    
    # Create configuration
    manager = ConfigurationManager(module)
    container_instance = manager.create_container_instance(config_set, instance_name="AdcConfigSet_0")
    container_instance.set_parameter_value("AdcDevEnabled", True, enabled_param.definition_ref)
    container_instance.set_parameter_value("AdcPrescale", 8, prescaler_param.definition_ref)
    container_instance.set_reference_value(
        "AdcClockRef",
        "/Config/Mcu/McuModuleConfiguration/McuClockReferencePoint_ADC",
        clock_ref.definition_ref
    )
    
    # Provide an explicit template (there are no built-in defaults)
    template_root = tmp_path / "templates"
    mod_dir = template_root / "Adc"
    mod_dir.mkdir(parents=True)
    (mod_dir / "Adc_PBcfg.c.tpl").write_text(
        "/* Adc_PBcfg.c */\n"
        "{% for container in containers %}"
        "/* Container: {{ container.short_name }} */\n"
        "{% for param_name, param_val in container.parameter_values.items() %}"
        "/* {{ param_name }} = {{ param_val.value }} */\n"
        "{% endfor %}"
        "{% for ref_name, ref_val in container.reference_values.items() %}"
        "/* Ref: {{ ref_name }} = &{{ ref_val.value_ref|resolve_ref }}_Config */\n"
        "{% endfor %}"
        "{% endfor %}",
        encoding="utf-8",
    )

    # Generate code
    generator = CodeGenerator(module, manager.configuration, project_template_dir=template_root)
    assert generator.generate_all(tmp_path / "out") is True

    # Root-level templates are promoted into src/
    pbcfg_source = tmp_path / "out" / "Adc" / "src" / "Adc_PBcfg.c"
    assert pbcfg_source.exists()

    source_content = pbcfg_source.read_text()

    # Should contain the boolean and integer parameter values
    assert "True" in source_content or "TRUE" in source_content
    assert "8" in source_content
    
    # Should contain resolved reference
    assert "&Mcu_McuModuleConfiguration_McuClockReferencePoint_ADC_Config" in source_content
