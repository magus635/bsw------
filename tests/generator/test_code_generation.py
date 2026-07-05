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


def _make_test_module():
    """Module 'Test' with one container and one PRE-COMPILE parameter"""
    module = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
    container_def = EcucContainerDef(short_name="TestContainer", definition_ref="/AUTOSAR/EcucDefs/Test/TestContainer")
    param = EcucParameterDef(short_name="TestParam", param_type="INTEGER", definition_ref="/AUTOSAR/EcucDefs/Test/TestContainer/TestParam", config_class="PRE-COMPILE")
    container_def.add_parameter(param)
    module.add_container(container_def)

    manager = ConfigurationManager(module)
    container_instance = manager.create_container_instance(container_def, instance_name="TestContainer_0")
    container_instance.set_parameter_value("TestParam", 42, param.definition_ref)
    return module, manager


def _write_test_templates(template_root: Path):
    """Minimal explicit template dir for module 'Test' (no built-in defaults exist)"""
    mod_dir = template_root / "Test"
    mod_dir.mkdir(parents=True)
    (mod_dir / "Test_Cfg.h.tpl").write_text(
        "/* Test_Cfg.h */\n"
        "#ifndef {{ header_guard }}\n"
        "#define {{ header_guard }}\n"
        "{% for p in precompile_params %}"
        "#define TEST_{{ p.1.upper() }} ({{ p.2 }})\n"
        "{% endfor %}"
        "#endif\n",
        encoding="utf-8",
    )
    (mod_dir / "Test_PBcfg.c.tpl").write_text(
        "/* Test_PBcfg.c */\n"
        "{% for container in containers %}"
        "/* Container: {{ container.short_name }} */\n"
        "{% endfor %}",
        encoding="utf-8",
    )


def test_code_generation_with_explicit_templates(tmp_path):
    """Generation works when a project template directory provides templates"""
    module, manager = _make_test_module()

    template_root = tmp_path / "templates"
    _write_test_templates(template_root)

    generator = CodeGenerator(module, manager.configuration, project_template_dir=template_root)
    assert generator.generate_all(tmp_path / "out") is True
    assert generator.last_status == 'generated'

    # Root-level templates are promoted into include/ and src/
    cfg_header = tmp_path / "out" / "Test" / "include" / "Test_Cfg.h"
    pbcfg_source = tmp_path / "out" / "Test" / "src" / "Test_PBcfg.c"

    assert cfg_header.exists()
    assert pbcfg_source.exists()

    header_content = cfg_header.read_text()
    assert "TEST_CFG_H" in header_content or "TEST_TESTPARAM" in header_content
    assert "42" in header_content

    source_content = pbcfg_source.read_text()
    assert "TestContainer_0" in source_content


def test_no_templates_module_is_skipped(tmp_path):
    """BREAKING behavior: no templates -> no files, skipped status, no fallback"""
    module, manager = _make_test_module()

    generator = CodeGenerator(module, manager.configuration)
    assert generator.generate_all(tmp_path / "out") is False
    assert generator.last_status == 'skipped'
    # No output directory or files are created
    assert not (tmp_path / "out" / "Test").exists()


def test_no_matching_templates_for_module_is_skipped(tmp_path):
    """A template dir without this module's subdirectory also yields skip"""
    module, manager = _make_test_module()

    template_root = tmp_path / "templates"
    (template_root / "OtherModule").mkdir(parents=True)
    (template_root / "OtherModule" / "OtherModule_Cfg.h.tpl").write_text("x", encoding="utf-8")

    generator = CodeGenerator(module, manager.configuration, project_template_dir=template_root)
    assert generator.generate_all(tmp_path / "out") is False
    assert generator.last_status == 'skipped'
    assert not (tmp_path / "out" / "Test").exists()
