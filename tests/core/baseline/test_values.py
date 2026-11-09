"""Tests for value flattening (core/baseline/values.py)."""
from autosar_configurator.core.baseline.values import flatten, values_equal
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
    EcucReferenceValue,
)
from autosar_configurator.core.packages.value_index import container_key, param_key, ref_key


def _config():
    cfg = EcucModuleConfiguration(short_name="Mcu", definition_ref="/X/Mcu")
    general = EcucContainerValue(short_name="McuGeneral", definition_ref="/X/Mcu/McuGeneral")
    general.parameter_values["Zeta"] = EcucParameterValue("/X/Mcu/McuGeneral/Zeta", 5)
    general.parameter_values["Alpha"] = EcucParameterValue("/X/Mcu/McuGeneral/Alpha", True)
    general.multi_parameter_values["List"] = [
        EcucParameterValue("/X/Mcu/McuGeneral/List", "b", index=0),
        EcucParameterValue("/X/Mcu/McuGeneral/List", "a", index=1),
    ]
    general.reference_values["Ref"] = EcucReferenceValue("/X/Mcu/McuGeneral/Ref", "/Os/OsCore")
    general.multi_reference_values["Refs"] = [
        EcucReferenceValue("/X/Mcu/McuGeneral/Refs", "/Port/P1"),
        EcucReferenceValue("/X/Mcu/McuGeneral/Refs", "/Port/P0"),
    ]
    sub = EcucContainerValue(short_name="McuSub", definition_ref="/X/Mcu/McuGeneral/McuSub")
    sub.parent = general
    general.sub_containers.append(sub)
    cfg.add_container(general)
    cfg.set_parameter_value("ModParam", "X", "/X/Mcu/ModParam")
    return cfg, general, sub


def test_flatten_keys_sorted_and_multi_as_tuple():
    cfg, general, sub = _config()
    flat = flatten(cfg)

    assert list(flat) == sorted(flat)
    assert flat[container_key(general)] is True
    assert flat[container_key(sub)] is True
    assert flat[param_key(general, "Zeta")] == 5
    assert flat[param_key(general, "Alpha")] is True
    # multi-value parameters and references keep their order, as tuples
    assert flat[param_key(general, "List")] == ("b", "a")
    assert flat[ref_key(general, "Ref")] == "/Os/OsCore"
    assert flat[ref_key(general, "Refs")] == ("/Port/P1", "/Port/P0")
    assert container_key(general) == "C:/Mcu/McuGeneral"
    assert param_key(sub, "x") == "P:/Mcu/McuGeneral/McuSub.x"


def test_flatten_module_level_parameter_key():
    cfg, _, _ = _config()
    flat = flatten(cfg)
    assert flat["P:/Mcu.ModParam"] == "X"


def test_flatten_does_not_mutate():
    cfg, general, _ = _config()
    flatten(cfg)
    assert list(general.parameter_values) == ["Zeta", "Alpha"]


def test_values_equal_reuses_workspace_semantics():
    from autosar_configurator.core import workspace_manager
    assert values_equal("TRUE", True)
    assert values_equal(" 5 ", 5)
    assert not values_equal("1", "2")
    assert values_equal(("a", "b"), ("a", "b"))
    assert workspace_manager._same_value is values_equal


def test_flatten_re_roots_on_the_module():
    """A Pre fragment saved as its own value collection flattens onto the module's keys."""
    from autosar_configurator.core.model.configuration_model import EcucContainerValue

    fragment = EcucModuleConfiguration(short_name="McuPreConfiguration", definition_ref="/X/Mcu")
    general = EcucContainerValue(short_name="McuGeneral", definition_ref="/X/Mcu/McuGeneral")
    general.parameter_values["Speed"] = EcucParameterValue("/X/Mcu/McuGeneral/Speed", 2)
    fragment.add_container(general)                      # containers carry the fragment's name
    module = EcucModuleConfiguration(short_name="Mcu", definition_ref="/X/Mcu")
    own = EcucContainerValue(short_name="McuGeneral", definition_ref="/X/Mcu/McuGeneral")
    own.parameter_values["Speed"] = EcucParameterValue("/X/Mcu/McuGeneral/Speed", 1)
    module.add_container(own)                            # here the containers carry "Mcu"

    assert "C:/McuPreConfiguration/McuGeneral" in flatten(fragment)
    assert set(flatten(fragment, "Mcu")) == set(flatten(module))
    assert flatten(fragment, "Mcu")["P:/Mcu/McuGeneral.Speed"] == 2
    # the source configuration is untouched
    assert "C:/McuPreConfiguration/McuGeneral" in flatten(fragment)


def test_flatten_module_name_re_roots_whatever_containers_carry():
    fragment = EcucModuleConfiguration(short_name="McuPreConfiguration", definition_ref="/X/Mcu")
    general = EcucContainerValue(short_name="McuGeneral", definition_ref="/X/Mcu/McuGeneral")
    general.parameter_values["Speed"] = EcucParameterValue("/X/Mcu/McuGeneral/Speed", 2)
    sub = EcucContainerValue(short_name="McuSub", definition_ref="/X/Mcu/McuGeneral/McuSub",
                             parent=general)
    general.sub_containers.append(sub)
    fragment.add_container(general)
    fragment.set_parameter_value("ModFlag", True, "/X/Mcu/ModFlag")

    flat = flatten(fragment, "Mcu")
    assert list(flat) == sorted(flat)
    assert flat["C:/Mcu/McuGeneral"] is True
    assert flat["C:/Mcu/McuGeneral/McuSub"] is True
    assert flat["P:/Mcu/McuGeneral.Speed"] == 2
    assert flat["P:/Mcu.ModFlag"] is True
