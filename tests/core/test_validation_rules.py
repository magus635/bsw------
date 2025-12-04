"""
Tests for Validation Rules

Tests all validation rule implementations including:
- Base rules (type, range, enumeration, required parameter)
- Structural rules (multiplicity)
- Reference rules (reference integrity, dangling references)
- Dependency rules (circular dependency detection)
"""
import pytest

from autosar_configurator.core.validation_engine import ValidationSeverity
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType,
    EcucReferenceDef
)
from autosar_configurator.core.model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue
)
from autosar_configurator.core.rules.base_rules import (
    TypeValidationRule,
    RangeValidationRule,
    EnumerationValidationRule,
    RequiredParameterRule
)
from autosar_configurator.core.rules.structural_rules import MultiplicityValidationRule
from autosar_configurator.core.rules.reference_rules import (
    ReferenceIntegrityRule,
    DanglingReferenceRule,
    RequiredReferenceRule
)
from autosar_configurator.core.rules.dependency_rules import CircularDependencyRule


class TestTypeValidationRule:
    """Test type validation rule"""
    
    @pytest.fixture
    def module_def(self):
        """Create module with INTEGER parameter"""
        module = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container_def = EcucContainerDef(
            short_name="Container",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        param_def = EcucParameterDef(
            short_name="IntParam",
            param_type=EcucParameterType.INTEGER,
            definition_ref="/AUTOSAR/EcucDefs/Test/Container/IntParam"
        )
        container_def.add_parameter(param_def)
        module.add_container(container_def)
        return module
    
    def test_valid_integer_type(self, module_def):
        """Test valid INTEGER parameter"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("IntParam", 42, "/AUTOSAR/EcucDefs/Test/Container/IntParam")
        config.add_container(container)
        
        rule = TypeValidationRule()
        result = rule.validate(module_def, config)
        assert result.is_valid
    
    def test_invalid_type(self, module_def):
        """Test invalid parameter type (string instead of integer)"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("IntParam", "not_an_int", "/AUTOSAR/EcucDefs/Test/Container/IntParam")
        config.add_container(container)
        
        rule = TypeValidationRule()
        result = rule.validate(module_def, config)
        assert not result.is_valid
        assert result.error_count == 1


class TestRangeValidationRule:
    """Test range validation rule"""
    
    @pytest.fixture
    def module_def(self):
        """Create module with range-constrained parameter"""
        module = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container_def = EcucContainerDef(
            short_name="Container",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        param_def = EcucParameterDef(
            short_name="RangeParam",
            param_type=EcucParameterType.INTEGER,
            min_value=0,
            max_value=100,
            definition_ref="/AUTOSAR/EcucDefs/Test/Container/RangeParam"
        )
        container_def.add_parameter(param_def)
        module.add_container(container_def)
        return module
    
    def test_value_in_range(self, module_def):
        """Test value within range"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("RangeParam", 50, "/AUTOSAR/EcucDefs/Test/Container/RangeParam")
        config.add_container(container)
        
        rule = RangeValidationRule()
        result = rule.validate(module_def, config)
        assert result.is_valid
    
    def test_value_below_min(self, module_def):
        """Test value below minimum"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("RangeParam", -10, "/AUTOSAR/EcucDefs/Test/Container/RangeParam")
        config.add_container(container)
        
        rule = RangeValidationRule()
        result = rule.validate(module_def, config)
        assert not result.is_valid
        assert result.error_count == 1
    
    def test_value_above_max(self, module_def):
        """Test value above maximum"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("RangeParam", 200, "/AUTOSAR/EcucDefs/Test/Container/RangeParam")
        config.add_container(container)
        
        rule = RangeValidationRule()
        result = rule.validate(module_def, config)
        assert not result.is_valid
        assert result.error_count == 1


class TestEnumerationValidationRule:
    """Test enumeration validation rule"""
    
    @pytest.fixture
    def module_def(self):
        """Create module with ENUM parameter"""
        module = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container_def = EcucContainerDef(
            short_name="Container",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        param_def = EcucParameterDef(
            short_name="EnumParam",
            param_type=EcucParameterType.ENUMERATION,
            literals=["OPTION_A", "OPTION_B", "OPTION_C"],
            definition_ref="/AUTOSAR/EcucDefs/Test/Container/EnumParam"
        )
        container_def.add_parameter(param_def)
        module.add_container(container_def)
        return module
    
    def test_valid_enum_value(self, module_def):
        """Test valid enumeration value"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("EnumParam", "OPTION_B", "/AUTOSAR/EcucDefs/Test/Container/EnumParam")
        config.add_container(container)
        
        rule = EnumerationValidationRule()
        result = rule.validate(module_def, config)
        assert result.is_valid
    
    def test_invalid_enum_value(self, module_def):
        """Test invalid enumeration value"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("EnumParam", "OPTION_X", "/AUTOSAR/EcucDefs/Test/Container/EnumParam")
        config.add_container(container)
        
        rule = EnumerationValidationRule()
        result = rule.validate(module_def, config)
        assert not result.is_valid
        assert result.error_count == 1


class TestReferenceIntegrityRule:
    """Test reference integrity rule - implements TODO from config_manager.py:123"""
    
    @pytest.fixture
    def module_with_references(self):
        """Create module definition with references"""
        module = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        # Container A
        container_a_def = EcucContainerDef(
            short_name="ContainerA",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerA"
        )
        
        # Container B
        container_b_def = EcucContainerDef(
            short_name="ContainerB",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerB"
        )
        
        # Add reference from A to B
        ref_def = EcucReferenceDef(
            short_name="RefToB",
            destination_ref="/AUTOSAR/EcucDefs/Test/ContainerB",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerA/RefToB"
        )
        container_a_def.add_reference(ref_def)
        
        module.add_container(container_a_def)
        module.add_container(container_b_def)
        
        return module
    
    def test_valid_reference(self, module_with_references):
        """Test valid reference to existing container"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        # Create container B (target)
        container_b = EcucContainerValue(
            short_name="ContainerB_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerB"
        )
        config.add_container(container_b)
        
        # Create container A with reference to B
        container_a = EcucContainerValue(
            short_name="ContainerA_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerA"
        )
        container_a.set_reference_value(
            "RefToB",
            "/Config/ContainerB_0",
            "/AUTOSAR/EcucDefs/Test/ContainerA/RefToB"
        )
        config.add_container(container_a)
        
        rule = ReferenceIntegrityRule()
        result = rule.validate(module_with_references, config)
        assert result.is_valid
    
    def test_dangling_reference(self, module_with_references):
        """Test dangling reference (target doesn't exist)"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        # Create container A with reference to non-existent B
        container_a = EcucContainerValue(
            short_name="ContainerA_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerA"
        )
        container_a.set_reference_value(
            "RefToB",
            "/Config/ContainerB_0",  # This doesn't exist
            "/AUTOSAR/EcucDefs/Test/ContainerA/RefToB"
        )
        config.add_container(container_a)
        
        rule = ReferenceIntegrityRule()
        result = rule.validate(module_with_references, config)
        assert not result.is_valid
        assert result.error_count == 1
    
    def test_find_references_to(self, module_with_references):
        """Test finding references to a container (TODO functionality)"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        # Create container B (target)
        container_b = EcucContainerValue(
            short_name="ContainerB_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerB"
        )
        config.add_container(container_b)
        
        # Create container A with reference to B
        container_a = EcucContainerValue(
            short_name="ContainerA_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/ContainerA"
        )
        container_a.set_reference_value(
            "RefToB",
            "/Config/ContainerB_0",
            "/AUTOSAR/EcucDefs/Test/ContainerA/RefToB"
        )
        config.add_container(container_a)
        
        # Find references to B
        refs = ReferenceIntegrityRule.find_references_to(container_b, config)
        assert len(refs) == 1
        assert refs[0][0] == container_a
        assert refs[0][1] == "RefToB"


class TestCircularDependencyRule:
    """Test circular dependency detection"""
    
    def test_no_circular_dependency(self):
        """Test linear reference chain: A -> B -> C"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        container_a = EcucContainerValue(short_name="A", definition_ref="/Test/A")
        container_b = EcucContainerValue(short_name="B", definition_ref="/Test/B")
        container_c = EcucContainerValue(short_name="C", definition_ref="/Test/C")
        
        container_a.set_reference_value("refToB", "/Config/B", "/ref")
        container_b.set_reference_value("refToC", "/Config/C", "/ref")
        
        config.add_container(container_a)
        config.add_container(container_b)
        config.add_container(container_c)
        
        module_def = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        rule = CircularDependencyRule()
        result = rule.validate(module_def, config)
        assert result.is_valid
    
    def test_circular_dependency(self):
        """Test circular dependency: A -> B -> C -> A"""
        config = EcucModuleConfiguration(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        container_a = EcucContainerValue(short_name="A", definition_ref="/Test/A")
        container_b = EcucContainerValue(short_name="B", definition_ref="/Test/B")
        container_c = EcucContainerValue(short_name="C", definition_ref="/Test/C")
        
        container_a.set_reference_value("refToB", "/Config/B", "/ref")
        container_b.set_reference_value("refToC", "/Config/C", "/ref")
        container_c.set_reference_value("refToA", "/Config/A", "/ref")  # Creates cycle
        
        config.add_container(container_a)
        config.add_container(container_b)
        config.add_container(container_c)
        
        module_def = EcucModuleDef(short_name="Test", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        rule = CircularDependencyRule()
        result = rule.validate(module_def, config)
        assert not result.is_valid
        assert result.error_count > 0
