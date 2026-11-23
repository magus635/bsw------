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
        module = EcucModuleDef(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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

    def test_parameter_without_value_is_not_a_type_error(self, module_def):
        """No value (EB writes it without <VALUE>): the default applies"""
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("IntParam", None, "/AUTOSAR/EcucDefs/Test/Container/IntParam")
        config.add_container(container)

        assert TypeValidationRule().validate(module_def, config).messages == []


class TestRangeValidationRule:
    """Test range validation rule"""
    
    @pytest.fixture
    def module_def(self):
        """Create module with range-constrained parameter"""
        module = EcucModuleDef(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        module = EcucModuleDef(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
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

    def test_parameter_without_value_is_not_a_literal_error(self, module_def):
        """No value (EB writes it without <VALUE>): the default applies"""
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        container = EcucContainerValue(
            short_name="Container_0",
            definition_ref="/AUTOSAR/EcucDefs/Test/Container"
        )
        container.set_parameter_value("EnumParam", None, "/AUTOSAR/EcucDefs/Test/Container/EnumParam")
        config.add_container(container)

        assert EnumerationValidationRule().validate(module_def, config).messages == []


class TestReferenceIntegrityRule:
    """Test reference integrity rule - implements TODO from config_manager.py:123"""
    
    @pytest.fixture
    def module_with_references(self):
        """Create module definition with references"""
        module = EcucModuleDef(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
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
            container_b.get_path(),  # Use actual container path
            "/AUTOSAR/EcucDefs/Test/ContainerA/RefToB"
        )
        config.add_container(container_a)
        
        rule = ReferenceIntegrityRule()
        result = rule.validate(module_with_references, config)
        assert result.is_valid
    
    def test_dangling_reference(self, module_with_references):
        """Test dangling reference (target doesn't exist)"""
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
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
            container_b.get_path(),  # Use actual container path
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
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        container_a = EcucContainerValue(short_name="A", definition_ref="/Test/A")
        container_b = EcucContainerValue(short_name="B", definition_ref="/Test/B")
        container_c = EcucContainerValue(short_name="C", definition_ref="/Test/C")
        
        container_a.set_reference_value("refToB", "/Config/B", "/ref")
        container_b.set_reference_value("refToC", "/Config/C", "/ref")
        
        config.add_container(container_a)
        config.add_container(container_b)
        config.add_container(container_c)
        
        module_def = EcucModuleDef(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        rule = CircularDependencyRule()
        result = rule.validate(module_def, config)
        assert result.is_valid
    
    def test_circular_dependency(self):
        """Test circular dependency: A -> B -> C -> A"""
        config = EcucModuleConfiguration(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        container_a = EcucContainerValue(short_name="A", definition_ref="/Test/A")
        container_b = EcucContainerValue(short_name="B", definition_ref="/Test/B")
        container_c = EcucContainerValue(short_name="C", definition_ref="/Test/C")
        
        container_a.set_reference_value("refToB", "/Config/B", "/ref")
        container_b.set_reference_value("refToC", "/Config/C", "/ref")
        container_c.set_reference_value("refToA", "/Config/A", "/ref")  # Creates cycle
        
        config.add_container(container_a)
        config.add_container(container_b)
        config.add_container(container_c)
        
        module_def = EcucModuleDef(short_name="Config", definition_ref="/AUTOSAR/EcucDefs/Test")
        
        rule = CircularDependencyRule()
        result = rule.validate(module_def, config)
        assert not result.is_valid
        assert result.error_count > 0


class TestValidationEnableConditions:
    """Test ENABLE condition evaluation in RequiredParameterRule, ConfigurationManager, and MultiplicityValidationRule."""

    def test_required_parameter_rule_skips_when_enable_expr_is_false(self):
        """Missing required parameter with falsy XDM ENABLE condition is skipped, while enabled missing param errors."""
        from autosar_configurator.core.config_manager import ConfigurationManager
        from autosar_configurator.core.model.definition_model import (
            EcucContainerDef,
            EcucModuleDef,
            EcucParameterDef,
            EcucParameterType,
        )

        mod_def = EcucModuleDef(short_name="Gpt", definition_ref="/THA6_AS440_FuSa/Gpt")
        set_def = EcucContainerDef(
            short_name="GptChannelConfigSet",
            definition_ref="/THA6_AS440_FuSa/Gpt/GptChannelConfigSet",
            lower_multiplicity=1,
            upper_multiplicity=1,
        )
        ch_def = EcucContainerDef(
            short_name="GptChannelConfiguration",
            definition_ref="/THA6_AS440_FuSa/Gpt/GptChannelConfigSet/GptChannelConfiguration",
            lower_multiplicity=0,
            upper_multiplicity=-1,
        )
        ch_def.add_parameter(EcucParameterDef(
            short_name="GptAssignedHwUnit",
            param_type=EcucParameterType.ENUMERATION,
            definition_ref="/THA6_AS440_FuSa/Gpt/GptChannelConfigSet/GptChannelConfiguration/GptAssignedHwUnit",
            literals=["GTM", "BASETIMER"],
            lower_multiplicity=1,
            upper_multiplicity=1,
        ))
        ch_def.add_parameter(EcucParameterDef(
            short_name="BaseTimerUsed",
            param_type=EcucParameterType.ENUMERATION,
            definition_ref="/THA6_AS440_FuSa/Gpt/GptChannelConfigSet/GptChannelConfiguration/BaseTimerUsed",
            literals=["BASETIMER0", "BASETIMER1"],
            lower_multiplicity=1,
            upper_multiplicity=1,
            enable_expr="node:fallback(../GptAssignedHwUnit, 'BASETIMER') = 'BASETIMER'",
        ))
        set_def.add_sub_container(ch_def)
        mod_def.add_container(set_def)

        config = EcucModuleConfiguration(short_name="Gpt", definition_ref="/THA6_AS440_FuSa/Gpt")
        cfg_set = EcucContainerValue("GptChannelConfigSet", "/THA6_AS440_FuSa/Gpt/GptChannelConfigSet")

        gtm_ch = EcucContainerValue("Ch_GTM", "/THA6_AS440_FuSa/Gpt/GptChannelConfigSet/GptChannelConfiguration")
        gtm_ch.set_parameter_value("GptAssignedHwUnit", "GTM", ch_def.parameters["GptAssignedHwUnit"].definition_ref)
        cfg_set.add_sub_container(gtm_ch)

        bt_ch = EcucContainerValue("Ch_BT", "/THA6_AS440_FuSa/Gpt/GptChannelConfigSet/GptChannelConfiguration")
        bt_ch.set_parameter_value("GptAssignedHwUnit", "BASETIMER", ch_def.parameters["GptAssignedHwUnit"].definition_ref)
        cfg_set.add_sub_container(bt_ch)

        config.add_container(cfg_set)

        rule = RequiredParameterRule()
        result = rule.validate(mod_def, config)
        assert result.error_count == 1
        assert result.errors[0].parameter_name == "BaseTimerUsed"
        assert "Ch_BT" in (result.errors[0].container_path or "")

        mgr = ConfigurationManager(mod_def)
        mgr.configuration = config
        assert mgr._validate_container_instance(gtm_ch) == []
        bt_errors = mgr._validate_container_instance(bt_ch)
        assert len(bt_errors) == 1
        assert "BaseTimerUsed" in bt_errors[0]

    def test_required_parameter_rule_keeps_error_when_enable_expr_unevaluable(self):
        """Unevaluable XDM ENABLE expression fails safe and still reports missing required parameter."""
        from autosar_configurator.core.model.definition_model import (
            EcucContainerDef,
            EcucModuleDef,
            EcucParameterDef,
            EcucParameterType,
        )

        mod_def = EcucModuleDef(short_name="TestMod", definition_ref="/V/TestMod")
        cdef = EcucContainerDef(short_name="C", definition_ref="/V/TestMod/C", lower_multiplicity=0, upper_multiplicity=1)
        cdef.add_parameter(EcucParameterDef(
            short_name="ReqBadExpr",
            param_type=EcucParameterType.INTEGER,
            definition_ref="/V/TestMod/C/ReqBadExpr",
            lower_multiplicity=1,
            upper_multiplicity=1,
            enable_expr="unknown:func(.)",
        ))
        mod_def.add_container(cdef)

        config = EcucModuleConfiguration(short_name="TestMod", definition_ref="/V/TestMod")
        config.add_container(EcucContainerValue("C", "/V/TestMod/C"))

        result = RequiredParameterRule().validate(mod_def, config)
        assert result.error_count == 1
        assert result.errors[0].parameter_name == "ReqBadExpr"

    def test_multiplicity_rule_skips_default_disabled_xdm_list_and_false_enable_expr(self, tmp_path):
        """Containers marked ENABLE value='false' or with falsy XPath ENABLE expr do not trigger MIN errors."""
        from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

        xdm = tmp_path / "Can.xdm"
        xdm.write_text("""<?xml version="1.0"?>
<datamodel version="7.0"
           xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
           xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="THA6_AS440_FuSa" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Can" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF">
              <v:ctr name="CanConfigSet" type="IDENTIFIABLE">
                <v:var name="FeatureEnabled" type="BOOLEAN"/>
                <v:ctr name="CanIcom" type="IDENTIFIABLE">
                  <a:da name="ENABLE" value="false"/>
                  <a:a name="OPTIONAL" value="true"/>
                  <v:lst name="CanIcomConfig" type="MAP">
                    <a:da name="ENABLE" value="false"/>
                    <a:da name="MIN" value="1"/>
                    <v:ctr name="CanIcomConfig" type="IDENTIFIABLE"/>
                  </v:lst>
                </v:ctr>
                <v:lst name="ConditionalSub" type="MAP">
                  <a:da name="MIN" value="1"/>
                  <a:da name="ENABLE" type="XPath" expr="../FeatureEnabled = 'true'"/>
                  <v:ctr name="ConditionalSub" type="IDENTIFIABLE"/>
                </v:lst>
              </v:ctr>
            </v:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>""", encoding="utf-8")

        mod_def = EcucDefParser().parse_module_def_file(xdm)
        cfg_set_def = mod_def.containers["CanConfigSet"]
        icom_def = cfg_set_def.sub_containers["CanIcom"]
        icom_cfg_def = icom_def.sub_containers["CanIcomConfig"]

        assert icom_def.default_disabled is True
        assert icom_cfg_def.default_disabled is True
        assert icom_cfg_def.list_enable_expr is None
        assert icom_cfg_def.lower_multiplicity == 1

        # Case 1: FeatureEnabled = false, empty CanIcom, no ConditionalSub -> 0 multiplicity errors
        cfg = EcucModuleConfiguration("Can", "/THA6_AS440_FuSa/Can")
        cfg_set = EcucContainerValue("CanConfigSet", cfg_set_def.definition_ref)
        cfg_set.set_parameter_value("FeatureEnabled", False, cfg_set_def.parameters["FeatureEnabled"].definition_ref)
        cfg_set.add_sub_container(EcucContainerValue("CanIcom", icom_def.definition_ref))
        cfg.add_container(cfg_set)

        res1 = MultiplicityValidationRule().validate(mod_def, cfg)
        assert res1.error_count == 0

        # Case 2: FeatureEnabled = true -> ConditionalSub missing triggers 1 error; CanIcomConfig still skipped
        cfg_set.parameter_values["FeatureEnabled"].value = True
        res2 = MultiplicityValidationRule().validate(mod_def, cfg)
        assert res2.error_count == 1
        assert "ConditionalSub" in res2.errors[0].message


def test_base_and_reference_rules_resolve_three_segment_vendor_ar_path():
    """Type, Range, RequiredParameter, and RequiredReference rules resolve containers using
    module_def.ar_path / module_relative without mis-slicing 3-segment vendor paths."""
    module_def = EcucModuleDef(
        short_name="CanTrcv",
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv",
        ar_path="/CustomPkg/CanTrcv_Tle9255/CanTrcv_Custom",
    )
    gen_def = EcucContainerDef(
        short_name="CanTrcvGeneral",
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral",
    )
    gen_def.add_parameter(EcucParameterDef(
        short_name="BaudRatio",
        param_type=EcucParameterType.INTEGER,
        min_value=1,
        max_value=16,
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral/BaudRatio",
    ))
    gen_def.add_parameter(EcucParameterDef(
        short_name="RequiredFlag",
        param_type=EcucParameterType.BOOLEAN,
        lower_multiplicity=1,
        upper_multiplicity=1,
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral/RequiredFlag",
    ))
    gen_def.add_reference(EcucReferenceDef(
        short_name="CanTrcvWakeupSourceRef",
        lower_multiplicity=1,
        upper_multiplicity=1,
        destination_ref="/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMWakeupSource",
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral/CanTrcvWakeupSourceRef",
    ))
    module_def.add_container(gen_def)

    config = EcucModuleConfiguration(
        short_name="CanTrcv",
        definition_ref="/CustomPkg/CanTrcv_Tle9255/CanTrcv_Custom",
    )
    gen_val = EcucContainerValue(
        short_name="CanTrcvGeneral",
        definition_ref="/CustomPkg/CanTrcv_Tle9255/CanTrcv_Custom/CanTrcvGeneral",
    )
    # Out-of-range BaudRatio (99), missing RequiredFlag, missing Required CanTrcvWakeupSourceRef
    gen_val.set_parameter_value(
        "BaudRatio",
        99,
        "/CustomPkg/CanTrcv_Tle9255/CanTrcv_Custom/CanTrcvGeneral/BaudRatio",
    )
    config.add_container(gen_val)

    type_res = TypeValidationRule().validate(module_def, config)
    assert type_res.is_valid, [m.message for m in type_res.errors]

    range_res = RangeValidationRule().validate(module_def, config)
    assert range_res.error_count == 1
    assert range_res.errors[0].parameter_name == "BaudRatio"
    assert "above maximum 16" in range_res.errors[0].message

    req_param_res = RequiredParameterRule().validate(module_def, config)
    assert req_param_res.error_count == 1
    assert "RequiredFlag" in req_param_res.errors[0].message

    req_ref_res = RequiredReferenceRule().validate(module_def, config)
    assert req_ref_res.error_count == 1
    assert "CanTrcvWakeupSourceRef" in req_ref_res.errors[0].message

