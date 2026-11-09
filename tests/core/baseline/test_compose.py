"""Tests for layered baseline composition (core/baseline/compose.py)."""
from autosar_configurator.core.baseline.compose import Layer, compose_base
from autosar_configurator.core.baseline.values import flatten
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

GEN = "P:/Mcu/McuGeneral."


def _module_def():
    mdef = EcucModuleDef(short_name="Mcu", definition_ref="/AUTOSAR/EcucDefs/Mcu")
    general = EcucContainerDef(short_name="McuGeneral", definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral")
    general.add_parameter(EcucParameterDef("Speed", EcucParameterType.INTEGER, default_value=7,
                                           definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/Speed"))
    general.add_parameter(EcucParameterDef("Dyn", EcucParameterType.INTEGER,
                                           default_expr="ecu:get('X')",
                                           definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/Dyn"))
    general.add_parameter(EcucParameterDef("Mode", EcucParameterType.ENUMERATION, default_value="A",
                                           definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/Mode"))
    sub = EcucContainerDef(short_name="McuSub", definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/McuSub")
    sub.add_parameter(EcucParameterDef("Depth", EcucParameterType.INTEGER, default_value=3,
                                       definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/McuSub/Depth"))
    general.add_sub_container(sub)
    other = EcucContainerDef(short_name="McuOther", definition_ref="/AUTOSAR/EcucDefs/Mcu/McuOther")
    other.add_parameter(EcucParameterDef("Never", EcucParameterType.INTEGER, default_value=1,
                                         definition_ref="/AUTOSAR/EcucDefs/Mcu/McuOther/Never"))
    mdef.add_container(general)
    mdef.add_container(other)
    mdef.parameters["ModFlag"] = EcucParameterDef("ModFlag", EcucParameterType.BOOLEAN, default_value=False,
                                                  definition_ref="/AUTOSAR/EcucDefs/Mcu/ModFlag")
    return mdef


def _layer_config(name, **params):
    """A value collection with McuGeneral holding the given parameters."""
    cfg = EcucModuleConfiguration(short_name=name, definition_ref="/X/Mcu")
    general = EcucContainerValue(short_name="McuGeneral", definition_ref="/X/Mcu/McuGeneral")
    for key, value in params.items():
        general.parameter_values[key] = EcucParameterValue(f"/X/Mcu/McuGeneral/{key}", value)
    cfg.add_container(general)
    return cfg


def test_pre_overrides_rec():
    rec = _layer_config("Mcu_Rec", Speed=1)
    pre = _layer_config("Mcu_Pre", Speed=2)
    base, origins = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    flat = flatten(base)
    assert flat[GEN + "Speed"] == 2
    assert origins[GEN + "Speed"] is Layer.PRE
    assert origins["C:/Mcu/McuGeneral"] is Layer.PRE


def test_derived_between_rec_and_pre():
    rec = _layer_config("Mcu_Rec", Speed=1)
    derived = _layer_config("Mcu_Derived", Speed=3)
    base, origins = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.DERIVED: [derived]})
    assert flatten(base)[GEN + "Speed"] == 3
    assert origins[GEN + "Speed"] is Layer.DERIVED

    pre = _layer_config("Mcu_Pre", Speed=2)
    base, origins = compose_base(_module_def(), "Mcu",
                                 {Layer.PRE: [pre], Layer.REC: [rec], Layer.DERIVED: [derived]})
    assert flatten(base)[GEN + "Speed"] == 2
    assert origins[GEN + "Speed"] is Layer.PRE


def test_defaults_fill_only_base_containers():
    rec = _layer_config("Mcu_Rec", Mode="B")
    base, origins = compose_base(_module_def(), "Mcu", {Layer.REC: [rec]})
    flat = flatten(base)
    assert flat[GEN + "Speed"] == 7
    assert origins[GEN + "Speed"] is Layer.DEFAULT
    assert flat[GEN + "Mode"] == "B"
    assert origins[GEN + "Mode"] is Layer.REC
    # default_expr is never evaluated
    assert GEN + "Dyn" not in flat
    assert GEN + "Dyn" not in origins
    # containers that no layer contributed are not created, so their defaults stay out
    assert "C:/Mcu/McuOther" not in flat
    assert "P:/Mcu/McuOther.Never" not in flat
    assert "C:/Mcu/McuGeneral/McuSub" not in flat
    # module-level defaults are filled too
    assert flat["P:/Mcu.ModFlag"] is False
    assert origins["P:/Mcu.ModFlag"] is Layer.DEFAULT
    # the filled value carries its definition reference
    speed = base.containers[0].parameter_values["Speed"]
    assert speed.definition_ref == "/AUTOSAR/EcucDefs/Mcu/McuGeneral/Speed"


def test_defaults_fill_sub_containers_from_layers():
    rec = _layer_config("Mcu_Rec")
    sub = EcucContainerValue(short_name="McuSub_0", definition_ref="/X/Mcu/McuGeneral/McuSub")
    sub.parent = rec.containers[0]
    rec.containers[0].sub_containers.append(sub)
    base, origins = compose_base(_module_def(), "Mcu", {Layer.REC: [rec]})
    flat = flatten(base)
    assert flat["P:/Mcu/McuGeneral/McuSub_0.Depth"] == 3
    assert origins["C:/Mcu/McuGeneral/McuSub_0"] is Layer.REC


def test_empty_derived_layer_changes_nothing():
    rec = _layer_config("Mcu_Rec", Speed=1)
    pre = _layer_config("Mcu_Pre", Mode="C")
    a, oa = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    b, ob = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre], Layer.DERIVED: []})
    assert flatten(a) == flatten(b)
    assert oa == ob


def test_containers_merged_recursively_and_new_ones_added():
    rec = _layer_config("Mcu_Rec", Speed=1)
    rec_sub = EcucContainerValue(short_name="McuSub", definition_ref="/X/Mcu/McuGeneral/McuSub")
    rec_sub.parameter_values["Depth"] = EcucParameterValue("/X/Mcu/McuGeneral/McuSub/Depth", 9)
    rec_sub.parent = rec.containers[0]
    rec.containers[0].sub_containers.append(rec_sub)

    pre = _layer_config("Mcu_Pre")
    pre_sub = EcucContainerValue(short_name="McuSub", definition_ref="/X/Mcu/McuGeneral/McuSub")
    pre_sub.reference_values["R"] = EcucReferenceValue("/X/Mcu/McuGeneral/McuSub/R", "/Os/C0")
    pre_sub.multi_reference_values["Rs"] = [EcucReferenceValue("/X/Mcu/McuGeneral/McuSub/Rs", "/Os/C1")]
    pre_sub.parent = pre.containers[0]
    pre.containers[0].sub_containers.append(pre_sub)
    pre_other = EcucContainerValue(short_name="McuOther", definition_ref="/X/Mcu/McuOther")
    pre.add_container(pre_other)

    base, origins = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    flat = flatten(base)
    assert [c.short_name for c in base.containers] == ["McuGeneral", "McuOther"]
    assert len(base.containers[0].sub_containers) == 1
    assert flat["P:/Mcu/McuGeneral/McuSub.Depth"] == 9
    assert origins["P:/Mcu/McuGeneral/McuSub.Depth"] is Layer.REC
    assert flat["R:/Mcu/McuGeneral/McuSub.R"] == "/Os/C0"
    assert origins["R:/Mcu/McuGeneral/McuSub.R"] is Layer.PRE
    assert flat["R:/Mcu/McuGeneral/McuSub.Rs"] == ("/Os/C1",)
    assert origins["C:/Mcu/McuGeneral/McuSub"] is Layer.PRE
    assert origins["C:/Mcu/McuOther"] is Layer.PRE
    assert flat["P:/Mcu/McuOther.Never"] == 1
    assert origins["P:/Mcu/McuOther.Never"] is Layer.DEFAULT
    # result is a proper module configuration: registered and named after the module
    assert base.short_name == "Mcu"
    assert base.get_instance_by_path("/Mcu/McuGeneral/McuSub") is base.containers[0].sub_containers[0]
    # every flattened key has an origin, and vice versa
    assert set(flat) == set(origins)


def test_multi_value_replaced_whole_by_higher_layer():
    rec = _layer_config("Mcu_Rec")
    rec.containers[0].multi_parameter_values["L"] = [
        EcucParameterValue("/X/L", "a"), EcucParameterValue("/X/L", "b")]
    pre = _layer_config("Mcu_Pre")
    pre.containers[0].multi_parameter_values["L"] = [EcucParameterValue("/X/L", "z")]
    base, origins = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    assert flatten(base)[GEN + "L"] == ("z",)
    assert origins[GEN + "L"] is Layer.PRE


def test_inputs_not_mutated():
    rec = _layer_config("Mcu_Rec", Speed=1)
    pre = _layer_config("Mcu_Pre", Speed=2)
    before_rec, before_pre = flatten(rec), flatten(pre)
    base, _ = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    base.containers[0].parameter_values["Speed"].value = 99
    assert flatten(rec) == before_rec
    assert flatten(pre) == before_pre
    assert base.containers[0] is not rec.containers[0]
    assert rec.containers[0].module_config is rec


def test_layer_order():
    assert [l.value for l in (Layer.DEFAULT, Layer.REC, Layer.DERIVED, Layer.PRE)] == [0, 1, 2, 3]
