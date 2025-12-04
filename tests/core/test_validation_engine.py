"""
Tests for Validation Engine

Tests the core validation engine framework and integration with ConfigurationManager.
"""
import pytest

from autosar_configurator.core.validation_engine import (
    ValidationEngine,
    ValidationRule,
    ValidationResult,
    ValidationMessage,
    ValidationSeverity
)
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType
)
from autosar_configurator.core.model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue
)


class TestValidationResult:
    """Test ValidationResult class"""
    
    def test_create_empty_result(self):
        """Test creating empty result"""
        result = ValidationResult()
        assert result.is_valid
        assert result.error_count == 0
        assert result.warning_count == 0
    
    def test_add_error(self):
        """Test adding error message"""
        result = ValidationResult()
        result.add_message(ValidationMessage(
            severity=ValidationSeverity.ERROR,
            message="Test error",
            rule_name="TestRule"
        ))
        assert not result.is_valid
        assert result.error_count == 1
    
    def test_add_warning(self):
        """Test adding warning message"""
        result = ValidationResult()
        result.add_message(ValidationMessage(
            severity=ValidationSeverity.WARNING,
            message="Test warning",
            rule_name="TestRule"
        ))
        assert result.is_valid  # Warnings don't make it invalid
        assert result.warning_count == 1
    
    def test_merge_results(self):
        """Test merging two results"""
        result1 = ValidationResult()
        result1.add_message(ValidationMessage(
            severity=ValidationSeverity.ERROR,
            message="Error 1",
            rule_name="Rule1"
        ))
        
        result2 = ValidationResult()
        result2.add_message(ValidationMessage(
            severity=ValidationSeverity.WARNING,
            message="Warning 1",
            rule_name="Rule2"
        ))
        
        result1.merge(result2)
        assert result1.error_count == 1
        assert result1.warning_count == 1


class DummyValidationRule(ValidationRule):
    """Dummy rule for testing"""
    
    def __init__(self, should_fail=False):
        super().__init__("DummyRule", "Dummy rule for testing")
        self.should_fail = should_fail
    
    def validate(self, module_def, configuration):
        result = ValidationResult()
        if self.should_fail:
            result.add_message(self._create_error("Dummy error"))
        return result


class TestValidationEngine:
    """Test ValidationEngine class"""
    
    @pytest.fixture
    def module_def(self):
        """Create test module definition"""
        module = EcucModuleDef(
            short_name="TestModule",
            definition_ref="/AUTOSAR/EcucDefs/TestModule"
        )
        
        container_def = EcucContainerDef(
            short_name="TestContainer",
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer",
            lower_multiplicity=1,
            upper_multiplicity=1
        )
        
        param_def = EcucParameterDef(
            short_name="TestParam",
            param_type=EcucParameterType.INTEGER,
            lower_multiplicity=1,
            upper_multiplicity=1,
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer/TestParam"
        )
        
        container_def.add_parameter(param_def)
        module.add_container(container_def)
        
        return module
    
    @pytest.fixture
    def configuration(self, module_def):
        """Create test configuration"""
        config = EcucModuleConfiguration(
            short_name="TestModule",
            definition_ref="/AUTOSAR/EcucDefs/TestModule"
        )
        
        container = EcucContainerValue(
            short_name="TestContainer_0",
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer"
        )
        container.set_parameter_value("TestParam", 42, "/AUTOSAR/EcucDefs/TestModule/TestContainer/TestParam")
        
        config.add_container(container)
        
        return config
    
    def test_engine_initialization(self, module_def, configuration):
        """Test creating validation engine"""
        engine = ValidationEngine(module_def, configuration)
        assert engine.module_def == module_def
        assert engine.configuration == configuration
        assert len(engine.rules) == 0
    
    def test_register_rule(self, module_def, configuration):
        """Test registering a rule"""
        engine = ValidationEngine(module_def, configuration)
        rule = DummyValidationRule()
        engine.register_rule(rule)
        assert len(engine.rules) == 1
    
    def test_validate_with_passing_rule(self, module_def, configuration):
        """Test validation with passing rule"""
        engine = ValidationEngine(module_def, configuration)
        engine.register_rule(DummyValidationRule(should_fail=False))
        
        result = engine.validate()
        assert result.is_valid
    
    def test_validate_with_failing_rule(self, module_def, configuration):
        """Test validation with failing rule"""
        engine = ValidationEngine(module_def, configuration)
        engine.register_rule(DummyValidationRule(should_fail=True))
        
        result = engine.validate()
        assert not result.is_valid
        assert result.error_count == 1
    
    def test_validate_with_multiple_rules(self, module_def, configuration):
        """Test validation with multiple rules"""
        engine = ValidationEngine(module_def, configuration)
        engine.register_rule(DummyValidationRule(should_fail=False))
        engine.register_rule(DummyValidationRule(should_fail=True))
        engine.register_rule(DummyValidationRule(should_fail=True))
        
        result = engine.validate()
        assert not result.is_valid
        assert result.error_count == 2
    
    def test_register_default_rules(self, module_def, configuration):
        """Test registering default rules"""
        engine = ValidationEngine(module_def, configuration)
        engine.register_default_rules()
        
        # Should have registered several default rules
        assert len(engine.rules) > 0
        
        # Validate should work
        result = engine.validate()
        # Result may or may not be valid depending on configuration
        assert isinstance(result, ValidationResult)


class TestConfigurationManagerIntegration:
    """Test validation engine integration with ConfigurationManager"""
    
    @pytest.fixture
    def module_def(self):
        """Create test module definition"""
        module = EcucModuleDef(
            short_name="TestModule",
            definition_ref="/AUTOSAR/EcucDefs/TestModule"
        )
        
        container_def = EcucContainerDef(
            short_name="TestContainer",
            definition_ref="/AUTOSAR/EcucDefs/TestModule/TestContainer",
            lower_multiplicity=0,
            upper_multiplicity=-1  # Unlimited
        )
        
        module.add_container(container_def)
        return module
    
    def test_validate_configuration_method(self, module_def):
        """Test ConfigurationManager.validate_configuration"""
        from autosar_configurator.core.config_manager import ConfigurationManager
        
        manager = ConfigurationManager(module_def)
        result = manager.validate_configuration()
        
        assert isinstance(result, ValidationResult)
        # Empty configuration should be valid
        assert result.is_valid
