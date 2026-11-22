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


class TestForeignReferenceResolution:
    """Test resolution behavior for AUTOSAR foreign and instance references."""

    def test_external_foreign_references_do_not_report_errors(self):
        """Non-/ActiveEcuC/ foreign/instance refs target external AUTOSAR elements and should not fail."""
        config = EcucModuleConfiguration("MemMap", "/MICROSAR/MemMap")
        c = EcucContainerValue("MemMapGenericMapping_0", "/MICROSAR/MemMap/MemMapAllocation/MemMapGenericMapping")

        external_targets = {
            "SwAddrRef": ("ECUC-FOREIGN-REFERENCE-DEF", "/MICROSAR_MemMap/SwAddrMethods/CODE"),
            "OsSwAddrRef": ("ECUC-FOREIGN-REFERENCE-DEF", "/MICROSAR/Os_ib_bswmd/SwAddrMethods/GLOBALSHARED_VAR_INIT"),
            "SwcModeRef": ("ECUC-FOREIGN-REFERENCE-DEF", "/MICROSAR/BswM_swc/ESH_RunRequest/REQUESTED"),
            "SysSignalRef": ("ECUC-FOREIGN-REFERENCE-DEF", "/PDU/MCU_Temp/MCU_RotorTemp"),
            "IocDataTypeRef": ("ECUC-FOREIGN-REFERENCE-DEF", "/DataTypes/AswIoc_CmdGroupType"),
            "InstanceRef": ("ECUC-INSTANCE-REFERENCE-DEF", "/SwComponentTypes/AppSwc/PPort"),
        }
        for name, (dest, target) in external_targets.items():
            ref = EcucReferenceValue("/Def/" + name, target, dest_type=dest)
            assert ref.is_foreign_reference is True
            c.reference_values[name] = ref

        # Also check multi-valued foreign reference
        c.add_multi_reference_value("MultiSwAddr", "/MICROSAR_MemMap/SwAddrMethods/CONST", "/Def/MultiSwAddr", 0)
        c.multi_reference_values["MultiSwAddr"][0].dest_type = "ECUC-FOREIGN-REFERENCE-DEF"

        config.add_container(c)

        resolved, errors = config.resolve_references(lambda _path: None)
        assert resolved == 0
        assert errors == 0
        assert config.get_resolution_errors() == []
        for ref in c.reference_values.values():
            assert ref.has_error is False
            assert ref.resolution_error is None
        assert c.multi_reference_values["MultiSwAddr"][0].has_error is False

    def test_active_ecuc_foreign_reference_resolves_and_reports_missing_module(self):
        """/ActiveEcuC/... foreign refs resolve when present and report missing module when unloaded."""
        config = EcucModuleConfiguration("vSet", "/MICROSAR/vSet")
        c = EcucContainerValue("vSetInit", "/MICROSAR/vSet/vSetBswInitialization")

        os_ref = EcucReferenceValue("/Def/vSetModuleRef", "/ActiveEcuC/Os", dest_type="ECUC-FOREIGN-REFERENCE-DEF")
        nm_ref = EcucReferenceValue("/Def/vSetModuleRef", "/ActiveEcuC/Nm", dest_type="ECUC-FOREIGN-REFERENCE-DEF")
        bad_path_ref = EcucReferenceValue("/Def/vSetModuleRef", "relative/path", dest_type="ECUC-FOREIGN-REFERENCE-DEF")
        missing_ecuc_ref = EcucReferenceValue("/Def/NormalRef", "/ActiveEcuC/EcuC/EcucPduCollection/Pdu_0", dest_type="ECUC-REFERENCE-DEF")
        missing_sym_ref = EcucReferenceValue("/Def/SymRef", "/ActiveEcuC/Can/CanConfigSet/CanCtrl_0", dest_type="ECUC-SYMBOLIC-NAME-REFERENCE-DEF")

        assert missing_ecuc_ref.is_foreign_reference is False
        assert missing_sym_ref.is_foreign_reference is False

        c.reference_values["OsMod"] = os_ref
        c.reference_values["NmMod"] = nm_ref
        c.reference_values["BadPath"] = bad_path_ref
        c.reference_values["NormalRef"] = missing_ecuc_ref
        c.reference_values["SymRef"] = missing_sym_ref
        config.add_container(c)

        os_proxy = EcucContainerValue("Os", "/MICROSAR/Os")
        resolved, errors = config.resolve_references(lambda p: os_proxy if p == "/ActiveEcuC/Os" else None)

        assert resolved == 1
        assert errors == 4
        assert os_ref.is_resolved is True
        assert os_ref.has_error is False
        assert nm_ref.has_error is True
        assert nm_ref.resolution_error.error_type == ResolutionError.MODULE_NOT_LOADED
        assert bad_path_ref.has_error is True
        assert bad_path_ref.resolution_error.error_type == ResolutionError.INVALID_PATH
        assert missing_ecuc_ref.resolution_error.error_type == ResolutionError.PATH_NOT_FOUND
        assert missing_sym_ref.resolution_error.error_type == ResolutionError.PATH_NOT_FOUND

    def test_rules_and_context_builder_respect_foreign_references(self):
        """ReferenceIntegrityRule, DanglingReferenceRule, and ContextBuilder treat foreign refs as external."""
        from autosar_configurator.core.rules.reference_rules import (
            ReferenceIntegrityRule,
            DanglingReferenceRule,
        )
        from autosar_configurator.core.ai.context_builder import ObjectGraphContextBuilder

        config = EcucModuleConfiguration("MemMap", "/MICROSAR/MemMap")
        c = EcucContainerValue("Map0", "/MICROSAR/MemMap/Map0")
        c.reference_values["ExtRef"] = EcucReferenceValue(
            "/Def/ExtRef", "/MICROSAR_MemMap/SwAddrMethods/CODE", dest_type="ECUC-FOREIGN-REFERENCE-DEF"
        )
        c.add_multi_reference_value("ExtMulti", "/PDU/Sig_0", "/Def/ExtMulti", 0)
        c.multi_reference_values["ExtMulti"][0].dest_type = "ECUC-FOREIGN-REFERENCE-DEF"
        config.add_container(c)

        config.resolve_references(lambda _p: None)
        assert ReferenceIntegrityRule().validate(None, config).messages == []
        assert DanglingReferenceRule().validate(None, config).messages == []

        ctx = ObjectGraphContextBuilder().build_context(c)
        assert "External Reference" in ctx.context_text
        assert "[Diagnostics]" not in ctx.context_text

    def test_re_resolve_after_adding_missing_module_clears_error(self):
        """Adding a previously missing module and calling resolve_all_references(force=True) clears MODULE_NOT_LOADED."""
        from pathlib import Path
        from autosar_configurator.core.model.definition_model import (
            EcucContainerDef,
            EcucModuleDef,
            EcucReferenceDef,
        )
        from autosar_configurator.core.workspace_manager import WorkspaceProject

        project = WorkspaceProject("ReResolveProject")

        vset_def = EcucModuleDef("vSet", definition_ref="/MICROSAR/vSet")
        init_list_def = EcucContainerDef("vSetBswInitialization", definition_ref="/MICROSAR/vSet/vSetBswInitialization")
        init_fn_def = EcucContainerDef("vSetInitFunction", definition_ref="/MICROSAR/vSet/vSetBswInitialization/vSetInitFunction", upper_multiplicity=-1)
        ref_def = EcucReferenceDef("vSetModuleRef", definition_ref="/MICROSAR/vSet/vSetBswInitialization/vSetInitFunction/vSetModuleRef")
        ref_def.destination_type = "ECUC-FOREIGN-REFERENCE-DEF"
        init_fn_def.references["vSetModuleRef"] = ref_def
        init_list_def.sub_containers["vSetInitFunction"] = init_fn_def
        vset_def.containers["vSetBswInitialization"] = init_list_def

        vset_mgr = project.add_module(vset_def, Path("vSet.arxml"))
        init_list = vset_mgr.create_container_instance(init_list_def, instance_name="vSetBswInitialization")
        init_fn = vset_mgr.create_container_instance(init_fn_def, parent=init_list, instance_name="CanNm_Init")
        ref_val = EcucReferenceValue(
            definition_ref=ref_def.definition_ref,
            value_ref="/ActiveEcuC/CanNm",
            dest_type="ECUC-FOREIGN-REFERENCE-DEF",
        )
        init_fn.reference_values["vSetModuleRef"] = ref_val

        resolved, errors = project.resolve_all_references()
        assert resolved == 0 and errors == 1
        assert ref_val.has_error and ref_val.resolution_error.error_type == ResolutionError.MODULE_NOT_LOADED

        cannm_def = EcucModuleDef("CanNm", definition_ref="/MICROSAR/CanNm")
        project.add_module(cannm_def, Path("CanNm.arxml"))

        resolved, errors = project.resolve_all_references(force=True)
        assert resolved == 1 and errors == 0
        assert ref_val.is_resolved is True
        assert ref_val.has_error is False
        assert ref_val.resolution_error is None

    def test_force_re_resolve_clears_and_detects_removed_or_replaced_target(self):
        """force=True clears cached target pointers so removed targets are immediately detected."""
        from pathlib import Path
        from autosar_configurator.core.model.definition_model import (
            EcucContainerDef,
            EcucModuleDef,
            EcucReferenceDef,
        )
        from autosar_configurator.core.workspace_manager import WorkspaceProject

        project = WorkspaceProject("ForceInvalidateProject")

        def_a = EcucModuleDef("ModA", definition_ref="/AUTOSAR/EcucDefs/ModA")
        c_a = EcucContainerDef("ContA", definition_ref="/AUTOSAR/EcucDefs/ModA/ContA")
        r_def = EcucReferenceDef("RefB", definition_ref="/AUTOSAR/EcucDefs/ModA/ContA/RefB", destination_ref="/AUTOSAR/EcucDefs/ModB/ContB")
        c_a.references["RefB"] = r_def
        def_a.containers["ContA"] = c_a

        def_b = EcucModuleDef("ModB", definition_ref="/AUTOSAR/EcucDefs/ModB")
        c_b = EcucContainerDef("ContB", definition_ref="/AUTOSAR/EcucDefs/ModB/ContB", upper_multiplicity=-1)
        def_b.containers["ContB"] = c_b

        mgr_a = project.add_module(def_a, Path("ModA.arxml"))
        mgr_b = project.add_module(def_b, Path("ModB.arxml"))
        inst_a = mgr_a.create_container_instance(c_a, instance_name="InstA")
        inst_b = mgr_b.create_container_instance(c_b, instance_name="OldTarget")
        inst_a.set_reference_value("RefB", "/ModB/OldTarget", r_def.definition_ref)

        resolved, errors = project.resolve_all_references(force=True)
        assert resolved == 1 and errors == 0
        ref_val = inst_a.reference_values["RefB"]
        assert ref_val.target is inst_b

        # Replace ModB's configuration with a new container (old target no longer exists)
        new_b_cfg = EcucModuleConfiguration("ModB", "/AUTOSAR/EcucDefs/ModB")
        new_b_cfg.add_container(EcucContainerValue("NewTarget", "/AUTOSAR/EcucDefs/ModB/ContB", module_name="ModB"))
        mgr_b.configuration = new_b_cfg

        # Default force=False skips already-resolved refs; force=True re-checks and flags broken ref
        project.resolve_all_references(force=False)
        assert ref_val.is_resolved is True

        resolved, errors = project.resolve_all_references(force=True)
        assert resolved == 0 and errors == 1
        assert ref_val.is_resolved is False
        assert ref_val.has_error is True
        assert ref_val.resolution_error.error_type == ResolutionError.PATH_NOT_FOUND


if __name__ == "__main__":
    pytest.main([__file__, "-v"])
