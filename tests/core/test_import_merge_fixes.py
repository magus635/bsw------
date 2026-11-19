"""前置修复 P0：容器定义匹配 + 多块合并。

验证痛点 1-2 的修正方案：
- 用 matches_container_def 而非短名查找容器定义
- 多个模块块合并成一个配置
"""

import pytest
from autosar_configurator.core.config_manager import (
    find_container_def,
    merge_module_configurations,
    ValidationError,
)
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
    EcucReferenceValue,
)
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucModuleDef,
    EcucParameterDef,
    EcucParameterType,
)


class TestContainerDefMatching:
    """用 matches_container_def 匹配容器定义。"""

    def test_find_container_def_by_definition_ref(self):
        """按 DEFINITION-REF 找容器定义，处理作用域差异。"""
        param_def = EcucParameterDef(
            short_name="OsAlarmName",
            param_type=EcucParameterType.STRING,
            definition_ref="/MICROSAR/Os/OsAlarm/OsAlarmName",
        )

        alarm_def = EcucContainerDef(
            short_name="OsAlarm",
            definition_ref="/MICROSAR/Os/OsAlarm",
            parameters={"OsAlarmName": param_def},
        )

        os_def = EcucModuleDef(
            short_name="Os",
            containers={"OsAlarm": alarm_def},
            definition_ref="/MICROSAR/Os",
        )

        # 待导入的容器实例
        config = EcucContainerValue(
            short_name="OsAlarm_0",
            definition_ref="/MICROSAR/Os/OsAlarm",
        )

        # 查找定义
        found = find_container_def(os_def, config)

        assert found is not None
        assert found.short_name == "OsAlarm"

    def test_find_container_def_handles_eb_suffix(self):
        """EB 的 _0 后缀不影响查找。"""
        container_def = EcucContainerDef(
            short_name="TestContainer",
            definition_ref="/MICROSAR/Test/TestContainer",
        )

        module_def = EcucModuleDef(
            short_name="Test",
            containers={"TestContainer": container_def},
        )

        # EB 导出时可能加 _N 后缀
        config = EcucContainerValue(
            short_name="TestContainer_1",
            definition_ref="/MICROSAR/Test/TestContainer",
        )

        found = find_container_def(module_def, config)
        assert found is not None

    def test_find_container_def_fallback_to_short_name(self):
        """无 DEFINITION-REF 时 fallback 到短名。"""
        container_def = EcucContainerDef(
            short_name="OldStyle",
            definition_ref="/MICROSAR/Os/OldStyle",
        )

        module_def = EcucModuleDef(
            short_name="Os",
            containers={"OldStyle": container_def},
        )

        # 没有 DEFINITION-REF 的旧文件
        config = EcucContainerValue(
            short_name="OldStyle",
            definition_ref="",  # Empty, will trigger fallback
        )

        found = find_container_def(module_def, config)
        assert found is not None


class TestModuleConfigurationMerge:
    """多个模块块合并成一个配置。"""

    def test_merge_two_module_configs(self):
        """合并两个块：容器/参数取并集，冲突报错。"""
        # 块 1：Pre 配置（空）
        config1 = EcucModuleConfiguration(
            short_name="vBRS_Pre",
            definition_ref="/MICROSAR/vBRS",
        )

        # 块 2：Rec 配置（有参数）
        config2 = EcucModuleConfiguration(
            short_name="vBRS_Rec",
            definition_ref="/MICROSAR/vBRS",
            parameter_values={
                "EnableFeature": EcucParameterValue(
                    definition_ref="/MICROSAR/vBRS/EnableFeature",
                    value="true",
                ),
            },
        )

        result = merge_module_configurations([config1, config2])

        assert result is not None
        assert "EnableFeature" in result.parameter_values
        assert result.parameter_values["EnableFeature"].value == "true"

    def test_merge_detects_parameter_conflict(self):
        """冲突时抛错，不覆盖。"""
        config1 = EcucModuleConfiguration(
            short_name="vBRS_1",
            definition_ref="/MICROSAR/vBRS",
            parameter_values={
                "Clock": EcucParameterValue(definition_ref="/MICROSAR/vBRS/Clock", value="100"),
            },
        )

        config2 = EcucModuleConfiguration(
            short_name="vBRS_2",
            definition_ref="/MICROSAR/vBRS",
            parameter_values={
                "Clock": EcucParameterValue(definition_ref="/MICROSAR/vBRS/Clock", value="200"),
            },
        )

        with pytest.raises(ValidationError, match="Clock"):
            merge_module_configurations([config1, config2])

    def test_merge_single_config_unchanged(self):
        """单个块直接返回。"""
        config = EcucModuleConfiguration(
            short_name="vBRS",
            definition_ref="/MICROSAR/vBRS",
        )

        result = merge_module_configurations([config])

        assert result is config

    def test_merge_empty_list_returns_none(self):
        """空列表返回 None。"""
        result = merge_module_configurations([])
        assert result is None

    def test_merge_containers_union(self):
        """容器取并集（新增容器）。"""
        sub1 = EcucContainerValue(
            short_name="Config1",
            definition_ref="/MICROSAR/vBRS/Config1",
        )

        config1 = EcucModuleConfiguration(
            short_name="vBRS_1",
            definition_ref="/MICROSAR/vBRS",
            containers=[sub1],
        )

        sub2 = EcucContainerValue(
            short_name="Config2",
            definition_ref="/MICROSAR/vBRS/Config2",
        )

        config2 = EcucModuleConfiguration(
            short_name="vBRS_2",
            definition_ref="/MICROSAR/vBRS",
            containers=[sub2],
        )

        result = merge_module_configurations([config1, config2])

        assert len(result.containers) == 2
        assert any(c.short_name == "Config1" for c in result.containers)
        assert any(c.short_name == "Config2" for c in result.containers)

    def test_merge_same_named_containers_recursively(self):
        """同名容器应递归合并参数、引用、多值项和子容器，而不是整块跳过。"""
        child1 = EcucContainerValue(
            short_name="SubA",
            definition_ref="/MICROSAR/vBRS/General/SubA",
            parameter_values={
                "P1": EcucParameterValue(definition_ref="/MICROSAR/vBRS/General/SubA/P1", value="a"),
            },
        )
        c1 = EcucContainerValue(
            short_name="vBRSGeneral",
            definition_ref="/MICROSAR/vBRS/vBRSGeneral",
            parameter_values={
                "Clock": EcucParameterValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Clock", value="100"),
            },
            reference_values={
                "Ref1": EcucReferenceValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Ref1", value_ref="/Target/A"),
            },
            sub_containers=[child1],
        )

        child2_same = EcucContainerValue(
            short_name="SubA",
            definition_ref="/MICROSAR/vBRS/General/SubA",
            parameter_values={
                "P2": EcucParameterValue(definition_ref="/MICROSAR/vBRS/General/SubA/P2", value="b"),
            },
        )
        child2_new = EcucContainerValue(
            short_name="SubB",
            definition_ref="/MICROSAR/vBRS/General/SubB",
        )
        c2 = EcucContainerValue(
            short_name="vBRSGeneral",
            definition_ref="/MICROSAR/vBRS/vBRSGeneral",
            parameter_values={
                "Clock": EcucParameterValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Clock", value="100"),
                "Mode": EcucParameterValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Mode", value="FAST"),
            },
            reference_values={
                "Ref2": EcucReferenceValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Ref2", value_ref="/Target/B"),
            },
            multi_parameter_values={
                "Tags": [EcucParameterValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Tags", value="T1")],
            },
            sub_containers=[child2_same, child2_new],
        )

        cfg1 = EcucModuleConfiguration(short_name="vBRS_Pre", definition_ref="/MICROSAR/vBRS", containers=[c1])
        cfg2 = EcucModuleConfiguration(short_name="vBRS_Rec", definition_ref="/MICROSAR/vBRS", containers=[c2])

        merged = merge_module_configurations([cfg1, cfg2])
        assert len(merged.containers) == 1
        gen = merged.containers[0]
        assert gen.parameter_values["Clock"].value == "100"
        assert gen.parameter_values["Mode"].value == "FAST"
        assert gen.reference_values["Ref1"].value_ref == "/Target/A"
        assert gen.reference_values["Ref2"].value_ref == "/Target/B"
        assert [p.value for p in gen.multi_parameter_values["Tags"]] == ["T1"]
        sub_a = next(s for s in gen.sub_containers if s.short_name == "SubA")
        assert sub_a.parameter_values["P1"].value == "a"
        assert sub_a.parameter_values["P2"].value == "b"
        assert any(s.short_name == "SubB" for s in gen.sub_containers)

    def test_merge_same_named_containers_raises_on_nested_conflict(self):
        """同名容器内的嵌套参数或引用冲突应抛出 ValidationError。"""
        c1 = EcucContainerValue(
            short_name="vBRSGeneral",
            definition_ref="/MICROSAR/vBRS/vBRSGeneral",
            parameter_values={
                "Clock": EcucParameterValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Clock", value="100"),
            },
        )
        c2 = EcucContainerValue(
            short_name="vBRSGeneral",
            definition_ref="/MICROSAR/vBRS/vBRSGeneral",
            parameter_values={
                "Clock": EcucParameterValue(definition_ref="/MICROSAR/vBRS/vBRSGeneral/Clock", value="200"),
            },
        )
        cfg1 = EcucModuleConfiguration(short_name="vBRS_Pre", definition_ref="/MICROSAR/vBRS", containers=[c1])
        cfg2 = EcucModuleConfiguration(short_name="vBRS_Rec", definition_ref="/MICROSAR/vBRS", containers=[c2])

        with pytest.raises(ValidationError, match="Clock"):
            merge_module_configurations([cfg1, cfg2])
