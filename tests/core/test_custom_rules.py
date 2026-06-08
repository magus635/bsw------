"""
Tests for Custom Validation Rules
"""
import pytest
import json
from pathlib import Path
from autosar_configurator.core.rules.custom_rules import (
    CustomRule, RuleEvaluator, RuleLoader, PythonRuleLoader, SecurityError,
)
from autosar_configurator.core.model.configuration_model import EcucContainerValue, EcucParameterValue
from autosar_configurator.core.validation_engine import ValidationSeverity

class MockContainer:
    def __init__(self, name, definition_ref, params):
        self.short_name = name
        self.definition_ref = definition_ref
        self.parameter_values = params
        self.sub_containers = []
        
    def get_path(self):
        return f"/{self.short_name}"

def test_evaluator_basic():
    """Test basic expression evaluation"""
    context = {'a': 10, 'b': 20, 'c': 'hello'}
    evaluator = RuleEvaluator(context)
    
    assert evaluator.evaluate('a < b') is True
    assert evaluator.evaluate('a > b') is False
    assert evaluator.evaluate('a == 10') is True
    assert evaluator.evaluate('c == "hello"') is True
    assert evaluator.evaluate('a + 10 == b') is True

def test_evaluator_logic():
    """Test logical operators"""
    context = {'enabled': True, 'count': 5}
    evaluator = RuleEvaluator(context)
    
    assert evaluator.evaluate('enabled and count > 0') is True
    assert evaluator.evaluate('not enabled or count < 10') is True
    assert evaluator.evaluate('count in [1, 2, 3, 4, 5]') is True

def test_evaluator_dot_notation():
    """Test dot notation access"""
    context = {'config': {'param': 100}}
    evaluator = RuleEvaluator(context)
    
    assert evaluator.evaluate('config.param == 100') is True

def test_custom_rule_validation(tmp_path):
    """Test custom rule validation logic"""
    # Define rule
    rule_def = {
        "name": "MaxSpeedCheck",
        "description": "Speed must not exceed 120",
        "target_container": "SpeedControl",
        "check": "max_speed <= 120",
        "message": "Speed limit exceeded",
        "severity": "error"
    }
    
    rule = CustomRule(rule_def)
    
    # Create matching container
    params = {
        'max_speed': EcucParameterValue('max_speed', 130, 'ref')
    }
    container = MockContainer('SpeedControl_0', '/Defs/SpeedControl', params)
    
    # Validate
    from autosar_configurator.core.validation_engine import ValidationResult
    result = ValidationResult()
    rule._evaluate_rule(container, result)
    
    assert result.error_count == 1
    assert result.errors[0].message == "Speed limit exceeded"
    
    # Fix value
    params['max_speed'].value = 100
    result = ValidationResult()
    rule._evaluate_rule(container, result)
    
    assert result.error_count == 0

def test_rule_loader(tmp_path):
    """Test loading rules from file"""
    rule_file = tmp_path / "rules.json"
    rules_data = [
        {
            "name": "Rule1",
            "check": "x > 0",
            "message": "Must be positive"
        },
        {
            "name": "Rule2",
            "check": "y < 10",
            "message": "Must be less than 10"
        }
    ]
    rule_file.write_text(json.dumps(rules_data))
    
    rules = RuleLoader.load_from_file(rule_file)
    assert len(rules) == 2
    assert rules[0].name == "Rule1"
    assert rules[1].name == "Rule2"


def test_python_rule_loader_blocks_globals_access(tmp_path):
    """A rule file using __globals__ (a sandbox-bypass dunder) must be rejected."""
    rule_file = tmp_path / "evil_rule.py"
    rule_file.write_text(
        "from autosar_configurator.core.rules.custom_rules import ValidationRule\n"
        "def validate():\n"
        "    return None\n"
        "x = validate.__globals__\n"
    )

    with pytest.raises(SecurityError):
        PythonRuleLoader.load_from_file(rule_file)


def test_python_rule_loader_blocks_dangerous_import(tmp_path):
    """A rule file importing a forbidden module (os) must be rejected before execution."""
    rule_file = tmp_path / "evil_import.py"
    rule_file.write_text("import os\n")

    with pytest.raises(SecurityError):
        PythonRuleLoader.load_from_file(rule_file)

