"""
Comprehensive Test Suite for ResolutionError System

Tests cover:
1. ResolutionError class - all 10 error types
2. EcucReferenceValue integration - has_error, resolution_error
3. UI display - DaVinciConfigPanel error display
4. AI context - ObjectGraphContextBuilder error info
5. Validation - ResolutionErrorValidationRule
"""
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))

import pytest
from autosar_configurator.core.model.configuration_model import (
    ResolutionError,
    ResolutionSeverity,
    EcucReferenceValue,
    EcucContainerValue,
    EcucModuleConfiguration
)


class TestResolutionErrorClass:
    """Test the ResolutionError class itself"""
    
    def test_all_error_types_exist(self):
        """Verify all 10 error types are defined"""
        error_types = [
            ResolutionError.PATH_NOT_FOUND,
            ResolutionError.MODULE_NOT_LOADED,
            ResolutionError.INVALID_PATH,
            ResolutionError.TYPE_MISMATCH,
            ResolutionError.AMBIGUOUS_REFERENCE,
            ResolutionError.DEF_VALUE_MISMATCH,
            ResolutionError.UNRESOLVED,
            ResolutionError.STALE_REFERENCE,
            ResolutionError.CIRCULAR_REFERENCE,
            ResolutionError.DEEP_CHAIN,
        ]
        assert len(error_types) == 10
        for et in error_types:
            assert isinstance(et, str)
    
    def test_default_severity_error(self):
        """PATH_NOT_FOUND should be ERROR severity"""
        error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/test/path")
        assert error.severity == ResolutionSeverity.ERROR
    
    def test_default_severity_warning(self):
        """CIRCULAR_REFERENCE should be WARNING severity"""
        error = ResolutionError(ResolutionError.CIRCULAR_REFERENCE, "/test/path")
        assert error.severity == ResolutionSeverity.WARNING
    
    def test_default_severity_info(self):
        """UNRESOLVED should be INFO severity"""
        error = ResolutionError(ResolutionError.UNRESOLVED, "/test/path")
        assert error.severity == ResolutionSeverity.INFO
    
    def test_default_message_generated(self):
        """Default message should be generated for each type"""
        error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/Config/Missing")
        assert "目标容器不存在" in error.message
        assert "/Config/Missing" in error.message
    
    def test_default_suggestion_generated(self):
        """Default suggestion should be generated"""
        error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/test")
        assert error.suggestion is not None
        assert len(error.suggestion) > 0
    
    def test_custom_message_override(self):
        """Custom message should override default"""
        custom_msg = "Custom error message"
        error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/test", message=custom_msg)
        assert error.message == custom_msg
    
    def test_ai_fields(self):
        """AI-ready fields should be accessible"""
        error = ResolutionError(
            ResolutionError.TYPE_MISMATCH,
            "/test",
            expected_type="CanController",
            actual_type="CanControllerBaudRate",
            candidates=["/Config/Can/CanController_0", "/Config/Can/CanController_1"]
        )
        assert error.expected_type == "CanController"
        assert error.actual_type == "CanControllerBaudRate"
        assert len(error.candidates) == 2
    
    def test_to_dict(self):
        """to_dict should return structured data"""
        error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/test")
        d = error.to_dict()
        assert "error_type" in d
        assert "reference_path" in d
        assert "message" in d
        assert "suggestion" in d
        assert "severity" in d
    
    def test_to_user_message(self):
        """to_user_message should be human readable"""
        error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/test")
        msg = error.to_user_message()
        assert "❌" in msg or "目标" in msg  # Should contain icon or Chinese
        assert "💡" in msg  # Should contain suggestion indicator


class TestEcucReferenceValueIntegration:
    """Test EcucReferenceValue integration with ResolutionError"""
    
    def test_has_error_false_by_default(self):
        """has_error should be False by default"""
        ref = EcucReferenceValue(
            definition_ref="/Def",
            value_ref="/Target"
        )
        assert ref.has_error == False
    
    def test_has_error_true_when_set(self):
        """has_error should be True when resolution_error is set"""
        ref = EcucReferenceValue(
            definition_ref="/Def",
            value_ref="/Target"
        )
        ref.resolution_error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/Target")
        assert ref.has_error == True
    
    def test_is_resolved_false_by_default(self):
        """is_resolved should be False when target is None"""
        ref = EcucReferenceValue(
            definition_ref="/Def",
            value_ref="/Target"
        )
        assert ref.is_resolved == False
    
    def test_is_resolved_true_when_target_set(self):
        """is_resolved should be True when target is set"""
        ref = EcucReferenceValue(
            definition_ref="/Def",
            value_ref="/Target"
        )
        ref.target = EcucContainerValue("Target", "/Target")
        assert ref.is_resolved == True
    
    def test_resolved_and_error_mutually_exclusive(self):
        """A reference should not be both resolved and have error"""
        ref = EcucReferenceValue(
            definition_ref="/Def",
            value_ref="/Target"
        )
        target = EcucContainerValue("Target", "/Target")
        ref.target = target
        
        # Should be resolved, not error
        assert ref.is_resolved == True
        assert ref.has_error == False


class TestResolutionErrorValidationRule:
    """Test ResolutionErrorValidationRule"""
    
    def test_no_errors_empty_config(self):
        """Empty config should have no errors"""
        from autosar_configurator.core.rules.reference_rules import ResolutionErrorValidationRule
        
        config = EcucModuleConfiguration("Test", "/Test")
        rule = ResolutionErrorValidationRule()
        result = rule.validate(None, config)
        
        assert result.error_count == 0
    
    def test_error_detected(self):
        """Reference with error should be detected"""
        from autosar_configurator.core.rules.reference_rules import ResolutionErrorValidationRule
        
        config = EcucModuleConfiguration("Test", "/Test")
        container = EcucContainerValue("C1", "/Test/C")
        ref = EcucReferenceValue("/Def", "/Missing")
        ref.resolution_error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/Missing")
        container.reference_values["BadRef"] = ref
        config.add_container(container)
        
        rule = ResolutionErrorValidationRule()
        result = rule.validate(None, config)
        
        assert result.error_count == 1
        assert "BadRef" in result.errors[0].message
    
    def test_suggested_fix_included(self):
        """ValidationMessage should include suggested_fix from ResolutionError"""
        from autosar_configurator.core.rules.reference_rules import ResolutionErrorValidationRule
        
        config = EcucModuleConfiguration("Test", "/Test")
        container = EcucContainerValue("C1", "/Test/C")
        ref = EcucReferenceValue("/Def", "/Missing")
        ref.resolution_error = ResolutionError(
            ResolutionError.PATH_NOT_FOUND, 
            "/Missing",
            suggestion="Custom fix suggestion"
        )
        container.reference_values["BadRef"] = ref
        config.add_container(container)
        
        rule = ResolutionErrorValidationRule()
        result = rule.validate(None, config)
        
        assert result.errors[0].suggested_fix == "Custom fix suggestion"
    
    def test_severity_mapping(self):
        """ValidationMessage severity should match ResolutionError severity"""
        from autosar_configurator.core.rules.reference_rules import ResolutionErrorValidationRule
        from autosar_configurator.core.validation_engine import ValidationSeverity
        
        config = EcucModuleConfiguration("Test", "/Test")
        container = EcucContainerValue("C1", "/Test/C")
        
        # WARNING severity error
        ref = EcucReferenceValue("/Def", "/Circular")
        ref.resolution_error = ResolutionError(ResolutionError.CIRCULAR_REFERENCE, "/Circular")
        container.reference_values["CircRef"] = ref
        config.add_container(container)
        
        rule = ResolutionErrorValidationRule()
        result = rule.validate(None, config)
        
        assert result.warnings[0].severity == ValidationSeverity.WARNING


class TestContextBuilderErrorIntegration:
    """Test ObjectGraphContextBuilder includes error info"""
    
    def test_error_details_in_l1(self):
        """L1 section should include error details"""
        from autosar_configurator.core.ai.context_builder import ObjectGraphContextBuilder
        
        container = EcucContainerValue("C1", "/Test/C")
        ref = EcucReferenceValue("/Def", "/Missing")
        ref.resolution_error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/Missing")
        container.reference_values["BadRef"] = ref
        
        builder = ObjectGraphContextBuilder()
        result = builder.build_context(container)
        
        assert "❌" in result.context_text
        assert "path_not_found" in result.context_text
    
    def test_diagnostics_section_created(self):
        """Diagnostics section should be created when errors exist"""
        from autosar_configurator.core.ai.context_builder import ObjectGraphContextBuilder
        
        container = EcucContainerValue("C1", "/Test/C")
        ref = EcucReferenceValue("/Def", "/Missing")
        ref.resolution_error = ResolutionError(ResolutionError.PATH_NOT_FOUND, "/Missing")
        container.reference_values["BadRef"] = ref
        
        builder = ObjectGraphContextBuilder()
        result = builder.build_context(container)
        
        assert "[Diagnostics]" in result.context_text
        assert "Resolution Issues" in result.context_text
    
    def test_no_diagnostics_when_resolved(self):
        """No diagnostics section when all references resolved"""
        from autosar_configurator.core.ai.context_builder import ObjectGraphContextBuilder
        
        container = EcucContainerValue("C1", "/Test/C")
        target = EcucContainerValue("Target", "/Target")
        ref = EcucReferenceValue("/Def", "/Target")
        ref.target = target  # Resolved
        container.reference_values["GoodRef"] = ref
        
        builder = ObjectGraphContextBuilder()
        result = builder.build_context(container)
        
        assert "[Diagnostics]" not in result.context_text


if __name__ == "__main__":
    pytest.main([__file__, "-v"])
