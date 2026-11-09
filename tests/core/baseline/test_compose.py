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
    assert origins["C:/Mcu/McuGeneral"] is Layer.REC


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
    # a container's origin is the layer that first introduced it
    assert origins["C:/Mcu/McuGeneral"] is Layer.REC
    assert origins["C:/Mcu/McuGeneral/McuSub"] is Layer.REC
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
    rec.containers[0].multi_parameter_values["L"] = [
        EcucParameterValue("/X/L", "a"), EcucParameterValue("/X/L", "b")]
    extra = EcucParameterValue("/X/Mcu/McuGeneral/Extra", [1, 2])
    rec.containers[0].parameter_values["Extra"] = extra
    rec.containers[0].unknown_parameters["Extra"] = extra
    pre = _layer_config("Mcu_Pre", Speed=2)
    before_rec, before_pre = flatten(rec), flatten(pre)
    base, _ = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    target = base.containers[0]
    target.parameter_values["Speed"].value = 99
    target.multi_parameter_values["L"][0].value = "changed"
    target.multi_parameter_values["L"].append(EcucParameterValue("/X/L", "c"))
    target.unknown_parameters["Extra"].value = "also changed"
    assert base.containers[0] is not rec.containers[0]
    assert flatten(rec) == before_rec
    assert flatten(pre) == before_pre
    assert rec.containers[0].module_config is rec
    # the copied list is a new list of new objects
    assert base.containers[0].multi_parameter_values["L"][0] is not \
        rec.containers[0].multi_parameter_values["L"][0]
    assert target.unknown_parameters["Extra"] is not rec.containers[0].unknown_parameters["Extra"]


def test_layer_order():
    assert [l.value for l in (Layer.DEFAULT, Layer.REC, Layer.DERIVED, Layer.PRE)] == [0, 1, 2, 3]


def test_multi_value_database_entry_points():
    """Multi-value parameters of a database-backed definition get no default."""
    mdef = _module_def()
    mdef.containers["McuGeneral"].add_parameter(EcucParameterDef(
        "Table", EcucParameterType.INTEGER, default_value=4, upper_multiplicity=-1,
        definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/Table"))
    base, origins = compose_base(mdef, "Mcu", {Layer.REC: [_layer_config("Mcu_Rec")]})
    assert "P:/Mcu/McuGeneral.Table" not in flatten(base)
    assert "P:/Mcu/McuGeneral.Table" not in origins


def test_defaults_are_absolute_and_need_no_repair():
    from autosar_configurator.core.model.definition_refs import needs_repair

    mdef = _module_def()
    mdef.ar_path = "/THA6_ASR21/Mcu"
    mdef.containers["McuGeneral"].parameters["Speed"].definition_ref = ""
    base, _ = compose_base(mdef, "Mcu", {Layer.REC: [_layer_config("Mcu_Rec")]})
    general = base.containers[0]
    for name in ("Speed", "Mode"):
        ref = general.parameter_values[name].definition_ref
        assert ref.startswith("/THA6_ASR21/Mcu/McuGeneral/"), ref
        assert not needs_repair(mdef, ref)
    assert general.parameter_values["Speed"].dest_type == "ECUC-INTEGER-PARAM-DEF"
    assert base.parameter_values["ModFlag"].definition_ref == "/THA6_ASR21/Mcu/ModFlag"


def test_unmatched_parent_definition_prunes_the_subtree():
    """A container whose definition is unknown gets no defaults, not even below it."""
    mdef = _module_def()
    rec = _layer_config("Mcu_Rec")
    orphan = EcucContainerValue(short_name="McuGeneral", definition_ref="/Other/Unknown")
    sub = EcucContainerValue(short_name="McuSub", definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/McuSub")
    sub.parent = orphan
    orphan.sub_containers.append(sub)
    rec.containers[0] = orphan
    base, origins = compose_base(mdef, "Mcu", {Layer.REC: [rec]})
    assert "P:/Mcu/McuGeneral/McuSub.Depth" not in flatten(base)
    assert not any(key.startswith("P:/Mcu/McuGeneral") for key in origins)


def test_result_carries_variant_and_package():
    rec = _layer_config("Mcu_Rec", Speed=1)
    rec.implementation_config_variant = "VARIANT-POST-BUILD"
    rec.package_name = "MICROSAR"
    pre = _layer_config("Mcu_Pre", Mode="C")
    base, _ = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    assert base.implementation_config_variant == "VARIANT-POST-BUILD"
    assert base.package_name == "MICROSAR"


def test_pre_fragment_keys_match_the_module():
    """A Pre fragment saved as its own collection lands on the module's keys."""
    rec = _layer_config("Mcu_Rec", Speed=1)
    pre = EcucModuleConfiguration(short_name="McuPreConfiguration", definition_ref="/X/Mcu")
    general = EcucContainerValue(short_name="McuGeneral", definition_ref="/X/Mcu/McuGeneral")
    general.parameter_values["Speed"] = EcucParameterValue("/X/Mcu/McuGeneral/Speed", 2)
    pre.add_container(general)
    base, origins = compose_base(_module_def(), "Mcu", {Layer.REC: [rec], Layer.PRE: [pre]})
    flat = flatten(base, "Mcu")
    assert flat["P:/Mcu/McuGeneral.Speed"] == 2
    assert origins["P:/Mcu/McuGeneral.Speed"] is Layer.PRE
    assert set(flat) == set(origins)


COMPUTED_PARAMS = {"McuSysPllFBDiv", "McuPerPllPostDiv1", "SysClkDiv", "AhbDiv", "GTMClockDiv"}
MCU_XDM = "test_import_project/Def/plugins/Mcu_THA6_AS440/config/Mcu.xdm"


def _mcu_def_with_chip():
    """The vendor Mcu definition after the project applies the THA610X chip expressions."""
    from pathlib import Path

    import pytest

    from autosar_configurator.core.hardware.chip_database import ChipDatabase, default_chips_dir
    from autosar_configurator.core.hardware.ecu_resource_data import flatten_ecu_resources
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
    from autosar_configurator.core.parser.xdm_expression_resolver import apply_chip_expressions

    xdm = Path(MCU_XDM)
    chip = ChipDatabase(default_chips_dir()).get_chip("THA610X_LFBGA180")
    if not xdm.exists() or chip is None:
        pytest.skip("vendor Mcu definition or chip data not available")
    mdef = EcucDefParser().parse_module_def_file(xdm)
    apply_chip_expressions(mdef, flatten_ecu_resources(chip.ecu_resources))
    return mdef


def _def_chain(mdef, short_name):
    """Definition path (root first) of the first container definition called ``short_name``."""
    def walk(cdefs, trail):
        for cdef in cdefs.values():
            path = trail + [cdef]
            yield path
            yield from walk(cdef.sub_containers, path)
    return next(p for p in walk(mdef.containers, []) if p[-1].short_name == short_name)


def _instance_chain(mdef, short_name):
    """A container value chain instantiating that definition, as a REC layer would hold it."""
    root = None
    parent = None
    for cdef in _def_chain(mdef, short_name):
        node = EcucContainerValue(short_name=cdef.short_name, definition_ref=cdef.definition_ref)
        if parent is None:
            root = node
        else:
            node.parent = parent
            parent.sub_containers.append(node)
        parent = node
    return root


def test_chip_expression_defaults_stay_out_of_the_baseline():
    """Expression-only defaults follow the chip and never enter the baseline."""
    from autosar_configurator.core.parser.xdm_expression_resolver import _walk_containers

    mdef = _mcu_def_with_chip()
    expr_only = [p for c in _walk_containers(mdef.containers.values())
                 for p in c.parameters.values() if p.default_expr and p.static_default is None]
    assert COMPUTED_PARAMS <= {p.short_name for p in expr_only}
    assert all(p.default_is_computed for p in expr_only)

    rec = EcucModuleConfiguration(short_name="Mcu_Rec", definition_ref="/X/Mcu")
    rec.add_container(_instance_chain(mdef, "McuSysPllClk_Configuration"))
    rec.add_container(_instance_chain(mdef, "McuSysClkDiv_Configuration"))

    base, origins = compose_base(mdef, "Mcu", {Layer.REC: [rec]})
    flat = flatten(base)
    for name in ("McuSysPllFBDiv", "AhbDiv"):
        assert not any(key.endswith("." + name) for key in flat), name
        assert not any(key.endswith("." + name) for key in origins), name

    # a static default of the very same container is still filled
    cdef = _def_chain(mdef, "McuSysPllClk_Configuration")[-1]
    static = [(name, p) for name, p in cdef.parameters.items()
              if p.default_value is not None and not p.default_expr and p.upper_multiplicity == 1]
    assert static
    name, pdef = static[0]
    key = f"P:/Mcu/McuModuleConfiguration/McuClockSettingConfig/McuSysPllClk_Configuration.{name}"
    assert flat[key] == pdef.default_value
    assert origins[key] is Layer.DEFAULT


def test_chip_expression_flag_is_what_excludes_the_default():
    mdef = _mcu_def_with_chip()
    cdef = _def_chain(mdef, "McuSysPllClk_Configuration")[-1]
    computed = cdef.parameters["McuSysPllFBDiv"]
    assert computed.default_is_computed
    assert computed.default_value == 60          # the value the THA610X chip expression produced

    rec = EcucModuleConfiguration(short_name="Mcu_Rec", definition_ref="/X/Mcu")
    rec.add_container(_instance_chain(mdef, "McuSysPllClk_Configuration"))
    key = ("P:/Mcu/McuModuleConfiguration/McuClockSettingConfig/"
           "McuSysPllClk_Configuration.McuSysPllFBDiv")
    assert key not in flatten(compose_base(mdef, "Mcu", {Layer.REC: [rec]})[0])
    assert computed.default_is_computed                  # the flag, not the value, excluded it

    computed.default_is_computed = False         # as if the chip had never run
    assert flatten(compose_base(mdef, "Mcu", {Layer.REC: [rec]})[0])[key] == 60
