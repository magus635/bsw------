"""A new container does not invent a value for a required parameter whose definition gives none."""
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)


def _module() -> EcucModuleDef:
    module = EcucModuleDef(short_name="M", definition_ref="/V/M")
    general = EcucContainerDef(short_name="G", definition_ref="/V/M/G", lower_multiplicity=1, upper_multiplicity=1)

    def add(name, kind, required, **kw):
        general.add_parameter(EcucParameterDef(short_name=name, param_type=kind, definition_ref=f"/V/M/G/{name}",
                                               lower_multiplicity=1 if required else 0, **kw))

    add("ReqEnumNoDefault", EcucParameterType.ENUMERATION, True, literals=["A", "B"])
    add("ReqIntNoDefault", EcucParameterType.INTEGER, True, min_value=1)
    add("ReqEnumDefault", EcucParameterType.ENUMERATION, True, literals=["A", "B"], default_value="B")
    add("ReqEnumXPathDefault", EcucParameterType.ENUMERATION, True, literals=["A", "B"],
        default_expr="ecu:list('M.Ids')[node:current()/../@index + 1]")
    add("OptEnumNoDefault", EcucParameterType.ENUMERATION, False, literals=["A", "B"])
    module.add_container(general)
    return module


def test_new_container_leaves_a_required_parameter_without_any_default_unset():
    manager = ConfigurationManager(_module())
    values = manager.create_container_instance(manager.module_def.containers["G"]).parameter_values

    assert "ReqEnumNoDefault" not in values
    assert "ReqIntNoDefault" not in values
    assert values["ReqEnumDefault"].value == "B"
    # a default the definition computes (EB XPath) is not given up: the first option stands in
    # for it as before, until such defaults are evaluated in the instance's context
    assert values["ReqEnumXPathDefault"].value == "A"
    assert values["OptEnumNoDefault"].value == "A"


def test_the_unset_required_parameter_is_reported_by_validation():
    manager = ConfigurationManager(_module())
    instance = manager.create_container_instance(manager.module_def.containers["G"])

    errors = manager._validate_container_instance(instance)

    assert any("ReqEnumNoDefault" in e for e in errors)
    assert any("ReqIntNoDefault" in e for e in errors)
    assert not any("ReqEnumDefault" in e for e in errors)
