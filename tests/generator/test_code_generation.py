"""
Tests for code generator
"""
import pytest
from pathlib import Path
from autosar_configurator.generator.template_engine import TemplateEngine
from autosar_configurator.generator.generator import CodeGenerator
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef
from autosar_configurator.core.config_manager import ConfigurationManager


def test_template_variable_substitution():
    """Test basic variable substitution"""
    engine = TemplateEngine()
    template = "Hello {{ name }}!"
    context = {'name': 'World'}
    
    result = engine.render(template, context)
    assert result == "Hello World!"


def test_template_for_loop():
    """Test for loop processing"""
    engine = TemplateEngine()
    template = "{% for item in items %}{{ item }} {% endfor %}"
    context = {'items': ['a', 'b', 'c']}
    
    result = engine.render(template, context)
    assert result == "a b c "


def test_template_if_conditional():
    """Test if conditional"""
    engine = TemplateEngine()
    template = "{% if enabled %}YES{% endif %}"
    
    result = engine.render(template, {'enabled': True})
    assert result == "YES"
    
    result = engine.render(template, {'enabled': False})
    assert result == ""


def test_template_if_else():
    """Test if-else conditional"""
    engine = TemplateEngine()
    template = "{% if enabled %}YES{% else %}NO{% endif %}"
    
    result = engine.render(template, {'enabled': True})
    assert result == "YES"
    
    result = engine.render(template, {'enabled': False})
    assert result == "NO"


def test_code_generation(tmp_path):
    """Test complete code generation"""
    # Create module def
    module = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
    
    # Add container
    container_def = EcucContainerDef(short_name="TestContainer", definition_ref="/AUTOSAR/EcucDefs/Test/TestContainer")
    param = EcucParameterDef(short_name="TestParam", param_type="INTEGER", definition_ref="/AUTOSAR/EcucDefs/Test/TestContainer/TestParam", config_class="PRE-COMPILE")
    container_def.add_parameter(param)
    module.add_container(container_def)
    
    # Create configuration
    manager = ConfigurationManager(module)
    container_instance = manager.create_container_instance(container_def, instance_name="TestContainer_0")
    container_instance.set_parameter_value("TestParam", 42, param.definition_ref)
    
    # Generate code
    generator = CodeGenerator(module, manager.configuration)
    generator.generate_all(tmp_path)
    
    # Verify files exist (root .h -> include/, root .c -> src/)
    cfg_header = tmp_path / "Test" / "include" / "Test_Cfg.h"
    pbcfg_source = tmp_path / "Test" / "src" / "Test_PBcfg.c"
    
    assert cfg_header.exists()
    assert pbcfg_source.exists()
    
    # Verify content
    header_content = cfg_header.read_text()
    assert "Test_Cfg.h" in header_content
    assert "TEST_CFG_H" in header_content
    assert "TestParam" in header_content
    assert "42" in header_content
    
    source_content = pbcfg_source.read_text()
    assert "Test_PBcfg.c" in source_content
    assert "TestContainer_0" in source_content or "TestContainer" in source_content
