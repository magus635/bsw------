"""A new container gets the defaults its definition gives, computed where EB computes them, and no
invented value: a parameter without any default stays unset."""
import logging
from pathlib import Path

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject

INDEXED = "ecu:list('M.Ids')[node:fallback(node:current()/../@index, '0') + 1]"


def _module() -> EcucModuleDef:
    module = EcucModuleDef(short_name="M", definition_ref="/V/M")
    group = EcucContainerDef(short_name="G", definition_ref="/V/M/G", lower_multiplicity=0, upper_multiplicity=4)

    def add(name, kind, required, **kw):
        group.add_parameter(EcucParameterDef(short_name=name, param_type=kind, definition_ref=f"/V/M/G/{name}",
                                             lower_multiplicity=1 if required else 0, **kw))

    add("ReqEnumNoDefault", EcucParameterType.ENUMERATION, True, literals=["A", "B"])
    add("ReqIntNoDefault", EcucParameterType.INTEGER, True, min_value=1)
    add("ReqEnumDefault", EcucParameterType.ENUMERATION, True, literals=["A", "B"], default_value="B")
    add("ReqEnumComputed", EcucParameterType.ENUMERATION, True, literals=["X", "Y", "Z"], default_expr=INDEXED)
    add("ReqIntComputed", EcucParameterType.INTEGER, True,
        default_expr="num:i(node:fallback(node:current()/../@index, '0') + 10)")
    add("ReqUnsupported", EcucParameterType.STRING, True, default_expr="not:a:function('x')")
    add("ReqDeferred", EcucParameterType.STRING, True, default_expr="node:fallback(\"->../Nope\", 'x')")
    add("OptEnumNoDefault", EcucParameterType.ENUMERATION, False, literals=["A", "B"])
    add("OptBoolNoDefault", EcucParameterType.BOOLEAN, False)
    add("OptIntDefault", EcucParameterType.INTEGER, False, default_value=7)
    module.add_container(group)
    return module


def _project():
    project = WorkspaceProject("demo")
    project.ecu_resources = {"M.Ids": ["X", "Y", "Z"]}
    return project, project.add_module(_module(), Path("M.xdm"))


def test_a_parameter_without_any_default_stays_unset():
    _, manager = _project()
    values = manager.create_container_instance(manager.module_def.containers["G"]).parameter_values

    for name in ("ReqEnumNoDefault", "ReqIntNoDefault", "OptEnumNoDefault", "OptBoolNoDefault"):
        assert name not in values, name
    assert values["ReqEnumDefault"].value == "B"
    assert values["OptIntDefault"].value == 7


def test_a_computed_default_is_evaluated_for_each_instance_in_its_place():
    _, manager = _project()
    group = manager.module_def.containers["G"]
    first = manager.create_container_instance(group, instance_name="G_0")
    second = manager.create_container_instance(group, instance_name="G_1")

    assert first.parameter_values["ReqEnumComputed"].value == "X"
    assert second.parameter_values["ReqEnumComputed"].value == "Y"
    assert first.parameter_values["ReqIntComputed"].value == 10
    assert second.parameter_values["ReqIntComputed"].value == 11


def test_a_default_that_cannot_be_computed_stays_unset_and_is_logged(caplog):
    _, manager = _project()
    with caplog.at_level(logging.WARNING):
        values = manager.create_container_instance(manager.module_def.containers["G"]).parameter_values

    assert "ReqUnsupported" not in values
    assert "ReqUnsupported" in caplog.text


def test_a_deferred_expression_falls_back_to_its_default_when_it_fails():
    """EB's node:fallback("->path", default): the path is missing, so the default applies."""
    _, manager = _project()
    values = manager.create_container_instance(manager.module_def.containers["G"]).parameter_values

    assert values["ReqDeferred"].value == "x"


def test_without_a_project_a_default_needing_no_chip_data_is_still_computed():
    manager = ConfigurationManager(_module())
    values = manager.create_container_instance(manager.module_def.containers["G"]).parameter_values

    assert values["ReqIntComputed"].value == 10
    assert "ReqEnumComputed" not in values          # needs ecu:list data, which a lone module lacks


def test_an_unset_required_parameter_is_reported_by_validation():
    _, manager = _project()
    instance = manager.create_container_instance(manager.module_def.containers["G"])

    errors = manager._validate_container_instance(instance)

    assert any("ReqEnumNoDefault" in e for e in errors)
    assert any("ReqUnsupported" in e for e in errors)
    assert not any("ReqEnumComputed" in e for e in errors)
    assert not any("OptEnumNoDefault" in e for e in errors)
