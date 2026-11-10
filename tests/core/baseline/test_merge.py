"""Tests for the three-way merge of Base, Base' and Active (core/baseline/merge.py).

Every case of design §6.5's merge table has one test. The fixtures are small in-code
``EcucModuleConfiguration`` trees; no vendor files are needed.
"""
from autosar_configurator.core.baseline.compose import Layer
from autosar_configurator.core.baseline.merge import (
    MergeItem,
    MergeKind,
    MergeResult,
    apply_merge,
    three_way_merge,
)
from autosar_configurator.core.baseline.values import flatten, values_equal
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
SUB = "P:/Mcu/McuGeneral/McuSub."
OTHER = "P:/Mcu/McuOther."
MOD = "P:/Mcu."


# --- fixtures -------------------------------------------------------------------

def _module_def():
    mdef = EcucModuleDef(short_name="Mcu", definition_ref="/AUTOSAR/EcucDefs/Mcu")
    general = EcucContainerDef(short_name="McuGeneral", definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral")
    general.add_parameter(EcucParameterDef("Speed", EcucParameterType.INTEGER, default_value=1,
                                           definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/Speed"))
    general.add_parameter(EcucParameterDef("Mode", EcucParameterType.ENUMERATION, default_value="A",
                                           definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/Mode"))
    general.add_parameter(EcucParameterDef("L", EcucParameterType.INTEGER, upper_multiplicity=-1,
                                           definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/L"))
    general.add_parameter(EcucParameterDef("Flag", EcucParameterType.BOOLEAN,
                                           definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/Flag"))
    sub = EcucContainerDef(short_name="McuSub", definition_ref="/AUTOSAR/EcucDefs/Mcu/McuGeneral/McuSub")
    sub.add_parameter(EcucParameterDef("Depth", EcucParameterType.INTEGER, default_value=2,
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


def _config(name="Mcu", container="McuGeneral", extra=()):
    """A value collection with the named top-level containers; ``None`` gives none."""
    cfg = EcucModuleConfiguration(short_name=name, definition_ref="/X/Mcu")
    for short_name in ([container] if isinstance(container, str) else list(container or ())) + list(extra):
        cfg.add_container(EcucContainerValue(short_name=short_name, definition_ref=f"/X/Mcu/{short_name}"))
    return cfg


def _top(cfg, name="McuGeneral"):
    return next(c for c in cfg.containers if c.short_name == name)


def _set(cfg, name, value, container="McuGeneral"):
    """Write ``value`` as parameter ``name`` of a top-level container (a list = multi-value)."""
    if container not in [c.short_name for c in cfg.containers]:
        cfg.add_container(EcucContainerValue(short_name=container, definition_ref=f"/X/Mcu/{container}"))
    target = _top(cfg, container)
    if isinstance(value, list):
        target.multi_parameter_values[name] = [
            EcucParameterValue(f"/X/{name}", v, index=i) for i, v in enumerate(value)]
    else:
        target.parameter_values[name] = EcucParameterValue(f"/X/{name}", value)

def _set_module(cfg, name, value):
    cfg.set_parameter_value(name, value, f"/X/Mcu/{name}")


def _apply(base_cfg, active_cfg, new_cfg, new_layers=None, unlocked=()):
    """Flatten, merge, apply; return ``(result, flatten(active) after the merge)``."""
    result = three_way_merge(flatten(base_cfg) if base_cfg is not None else None,
                             flatten(new_cfg), flatten(active_cfg),
                             new_layers or {}, set(unlocked))
    apply_merge(active_cfg, _module_def(), new_cfg, result)
    return result, flatten(active_cfg)


def _kinds(result):
    return {(item.key, item.kind) for item in result.items}


# --- the merge table ------------------------------------------------------------

def test_unchanged_base_no_items():
    """Base = Base' → nothing at all, not even a KEPT_USER for an untouched value."""
    base = _config()
    _set(base, "Speed", 1)
    new = _config()
    _set(new, "Speed", 1)
    active = _config()
    _set(active, "Speed", 1)

    result, merged = _apply(base, active, new)
    assert result.items == []
    assert result.has_changes is False
    assert merged == flatten(active)
    assert merged[GEN + "Speed"] == 1


def test_unchanged_base_but_active_deviates_is_not_a_change():
    """Base = Base' → the merge does not care what Active says; nothing to confirm."""
    base = _config()
    _set(base, "Speed", 1)
    new = _config()
    _set(new, "Speed", 1)
    active = _config()
    _set(active, "Speed", 3)

    result, merged = _apply(base, active, new)
    assert result.items == []
    assert result.has_changes is False
    assert merged[GEN + "Speed"] == 3


def test_adopt_when_user_untouched():
    """Base ≠ Base', Active = Base → take Base'."""
    base = _config()
    _set(base, "Speed", 1)
    new = _config()
    _set(new, "Speed", 2)
    active = _config()
    _set(active, "Speed", 1)

    result, merged = _apply(base, active, new)
    assert result.items == [MergeItem(GEN + "Speed", MergeKind.ADOPT, 1, 2, 1)]
    assert result.has_changes is True
    assert merged[GEN + "Speed"] == 2
    assert merged == flatten(new)


def test_adopt_covers_references_too():
    base = _config()
    _top(base).reference_values["Ref"] = EcucReferenceValue("/X/Ref", "/Os/C0")
    new = _config()
    _top(new).reference_values["Ref"] = EcucReferenceValue("/X/Ref", "/Os/C1")
    active = _config()
    _top(active).reference_values["Ref"] = EcucReferenceValue("/X/Ref", "/Os/C0")

    result, merged = _apply(base, active, new)
    assert _kinds(result) == {("R:/Mcu/McuGeneral.Ref", MergeKind.ADOPT)}
    assert merged["R:/Mcu/McuGeneral.Ref"] == "/Os/C1"


def test_keep_user_when_user_changed():
    """Base ≠ Base', Active ≠ Base, not Pre → keep the user value and report it."""
    base = _config()
    _set(base, "Speed", 1)
    new = _config()
    _set(new, "Speed", 5)
    active = _config()
    _set(active, "Speed", 3)

    result, merged = _apply(base, active, new)
    assert result.items == [MergeItem(GEN + "Speed", MergeKind.KEPT_USER, 1, 5, 3)]
    assert result.has_changes is False
    assert merged[GEN + "Speed"] == 3


def test_pre_forced_over_user():
    """A Pre value wins over the user value, and over 'Base = Base' → unchanged'."""
    base = _config()
    _set(base, "Speed", 1)
    new = _config()
    _set(new, "Speed", 9)
    active = _config()
    _set(active, "Speed", 4)

    result, merged = _apply(base, active, new, {GEN + "Speed": Layer.PRE})
    assert result.items == [MergeItem(GEN + "Speed", MergeKind.PRE_FORCED, 1, 9, 4)]
    assert result.has_changes is True
    assert merged[GEN + "Speed"] == 9

    # Base = Base' but Active deviates from Pre: still forced, because Pre wins over that rule
    same = _config()
    _set(same, "Speed", 4)
    result, merged = _apply(base, same, base, {GEN + "Speed": Layer.PRE})
    assert result.items == [MergeItem(GEN + "Speed", MergeKind.PRE_FORCED, 1, 1, 4)]
    assert merged[GEN + "Speed"] == 1

    # Active already equals Pre: no item, nothing to confirm
    result, merged = _apply(base, base, base, {GEN + "Speed": Layer.PRE})
    assert result.items == []
    assert result.has_changes is False


def test_unlocked_pre_kept_user():
    """An unlocked Pre key is an ordinary key: the user value survives, nothing changes."""
    base = _config()
    _set(base, "Speed", 1)
    new = _config()
    _set(new, "Speed", 9)
    active = _config()
    _set(active, "Speed", 4)

    result, merged = _apply(base, active, new, {GEN + "Speed": Layer.PRE}, unlocked={GEN + "Speed"})
    assert result.items == [MergeItem(GEN + "Speed", MergeKind.KEPT_USER, 1, 9, 4)]
    assert result.has_changes is False
    assert merged[GEN + "Speed"] == 4

    # and once the user has not touched it, an unlocked Pre key follows Base' like any other
    untouched = _config()
    _set(untouched, "Speed", 1)
    result, merged = _apply(base, untouched, new, {GEN + "Speed": Layer.PRE},
                            unlocked={GEN + "Speed"})
    assert result.items == [MergeItem(GEN + "Speed", MergeKind.ADOPT, 1, 9, 1)]
    assert merged[GEN + "Speed"] == 9


def test_create_new_pre_container():
    """A container Pre introduces is created with its whole subtree; first as a C: item."""
    base = _config()
    new = _config()
    _set(new, "Never", 5, container="McuOther")
    active = _config()

    result, merged = _apply(base, active, new, {"C:/Mcu/McuOther": Layer.PRE, OTHER + "Never": Layer.PRE})
    assert result.items == [
        MergeItem("C:/Mcu/McuOther", MergeKind.CREATE, None, True, None),
        MergeItem(OTHER + "Never", MergeKind.CREATE, None, 5, None),
    ]
    assert result.has_changes is True
    # the container and its value exist, attached as a top-level container of Active
    assert [c.short_name for c in active.containers] == ["McuGeneral", "McuOther"]
    assert merged["C:/Mcu/McuOther"] is True
    assert merged[OTHER + "Never"] == 5
    assert merged == flatten(new)
    assert active.get_instance_by_path("/Mcu/McuOther") is _top(active, "McuOther")
    # a deep copy, not the Base' object itself
    assert _top(active, "McuOther") is not _top(new, "McuOther")


def test_create_nested_pre_container_under_an_existing_parent():
    """A Pre container nested under a container Active already has is attached under it."""
    base = _config()
    new = _config()
    sub = EcucContainerValue(short_name="McuSub", definition_ref="/X/Mcu/McuGeneral/McuSub")
    sub.parameter_values["Depth"] = EcucParameterValue("/X/Depth", 4)
    _top(new).add_sub_container(sub)
    active = _config()

    result, merged = _apply(base, active, new,
                            {"C:/Mcu/McuGeneral/McuSub": Layer.PRE, SUB + "Depth": Layer.PRE})
    assert _kinds(result) == {("C:/Mcu/McuGeneral/McuSub", MergeKind.CREATE),
                              (SUB + "Depth", MergeKind.CREATE)}
    assert merged[SUB + "Depth"] == 4
    assert active.get_instance_by_path("/Mcu/McuGeneral/McuSub") is not None


def test_whole_pre_subtree_created_under_a_new_parent():
    """A Pre container Active never had comes over with its sub-containers and values."""
    base = _config(container=None)
    new = _config()
    sub = EcucContainerValue(short_name="McuSub", definition_ref="/X/Mcu/McuGeneral/McuSub")
    sub.parameter_values["Depth"] = EcucParameterValue("/X/Depth", 3)
    _top(new).add_sub_container(sub)
    _set(new, "Speed", 4)
    active = _config(container=None)

    result, merged = _apply(base, active, new, {"C:/Mcu/McuGeneral": Layer.PRE,
                                                "C:/Mcu/McuGeneral/McuSub": Layer.PRE,
                                                SUB + "Depth": Layer.PRE, GEN + "Speed": Layer.PRE})
    assert _kinds(result) == {("C:/Mcu/McuGeneral", MergeKind.CREATE),
                              ("C:/Mcu/McuGeneral/McuSub", MergeKind.CREATE),
                              (SUB + "Depth", MergeKind.CREATE),
                              (GEN + "Speed", MergeKind.CREATE)}
    assert merged == flatten(new)
    assert active.get_instance_by_path("/Mcu/McuGeneral/McuSub").parent is _top(active)


def test_container_never_created_without_pre():
    """Only Pre creates containers: a container new in Base' but not Pre is left to the user."""
    base = _config()
    new = _config()
    _set(new, "Never", 5, container="McuOther")
    active = _config()

    result, merged = _apply(base, active, new)
    assert _kinds(result) == {("C:/Mcu/McuOther", MergeKind.KEPT_USER),
                              (OTHER + "Never", MergeKind.KEPT_USER)}
    assert result.has_changes is False
    assert [c.short_name for c in active.containers] == ["McuGeneral"]


def test_merge_never_deletes_renamed_or_removed():
    """Review Focus 1: Base has X, Base' has not, Active renamed X to Y. Y survives."""
    base = _config()
    _top(base).parameter_values["Flag"] = EcucParameterValue("/X/Flag", True)
    new = _config(container=None)
    active = _config("Mcu", container="Y")             # the user renamed X to Y
    _top(active, "Y").parameter_values["Flag"] = EcucParameterValue("/X/Flag", True)

    result, merged = _apply(base, active, new)
    assert _kinds(result) == {("C:/Mcu/McuGeneral", MergeKind.REMOVED_IN_BASE),
                              (GEN + "Flag", MergeKind.REMOVED_IN_BASE)}
    assert result.has_changes is False
    # nothing was deleted: Y and its value are still there, X was not resurrected
    assert [c.short_name for c in active.containers] == ["Y"]
    assert merged["C:/Mcu/Y"] is True
    assert merged["P:/Mcu/Y.Flag"] is True


def test_merge_never_deletes_a_value_removed_from_base():
    """A parameter that disappeared from Base' stays in Active and is only reported."""
    base = _config()
    _set(base, "Mode", "B")
    new = _config()
    active = _config()
    _set(active, "Mode", "B")

    result, merged = _apply(base, active, new)
    assert result.items == [MergeItem(GEN + "Mode", MergeKind.REMOVED_IN_BASE, "B", None, "B")]
    assert result.has_changes is False
    assert merged[GEN + "Mode"] == "B"


def test_merge_multi_values_compared_as_list():
    """Review Focus 2: a multi-value parameter is one ordered value, forced back as a whole."""
    base = _config()
    new = _config()
    _set(new, "L", [1, 2])
    active = _config()
    _set(active, "L", [2, 1])

    result, merged = _apply(base, active, new, {GEN + "L": Layer.PRE})
    assert result.items == [MergeItem(GEN + "L", MergeKind.PRE_FORCED, None, (1, 2), (2, 1))]
    assert merged[GEN + "L"] == (1, 2)
    assert _top(active).multi_parameter_values["L"][0].value == 1

    # same order = no change; a reordering is a change, not two equal sets
    same = _config()
    _set(same, "L", [1, 2])
    result, _ = _apply(new, same, new, {GEN + "L": Layer.PRE})
    assert result.items == []


def test_merge_multi_reference_compared_as_list():
    base = _config()
    new = _config()
    _top(new).multi_reference_values["Refs"] = [
        EcucReferenceValue("/X/Refs", "/Port/P0", index=0),
        EcucReferenceValue("/X/Refs", "/Port/P1", index=1)]
    active = _config()
    _top(active).multi_reference_values["Refs"] = [
        EcucReferenceValue("/X/Refs", "/Port/P1", index=0),
        EcucReferenceValue("/X/Refs", "/Port/P0", index=1)]

    result, merged = _apply(base, active, new, {"R:/Mcu/McuGeneral.Refs": Layer.PRE})
    assert result.items == [MergeItem("R:/Mcu/McuGeneral.Refs", MergeKind.PRE_FORCED, None,
                                      ("/Port/P0", "/Port/P1"), ("/Port/P1", "/Port/P0"))]
    assert merged["R:/Mcu/McuGeneral.Refs"] == ("/Port/P0", "/Port/P1")
    assert [r.value_ref for r in _top(active).multi_reference_values["Refs"]] == ["/Port/P0", "/Port/P1"]


def test_first_enable_all_user_except_pre():
    """base=None (first enable / migration): no ADOPT at all, only Pre changes anything."""
    new = _config()
    _set(new, "Speed", 1)
    _set(new, "Mode", "C")
    active = _config()
    _set(active, "Speed", 2)
    _set(active, "Mode", "A")

    result, merged = _apply(None, active, new, {GEN + "Mode": Layer.PRE})
    assert _kinds(result) == {(GEN + "Speed", MergeKind.KEPT_USER),
                              (GEN + "Mode", MergeKind.PRE_FORCED)}
    assert merged[GEN + "Speed"] == 2                  # the Rec/default value does not override
    assert merged[GEN + "Mode"] == "C"                 # Pre does

    # a value Active already holds equal to Base' is not reported at all
    same = _config()
    _set(same, "Speed", 1)
    result, _ = _apply(None, same, new, {GEN + "Mode": Layer.PRE})
    assert _kinds(result) == {(GEN + "Mode", MergeKind.PRE_FORCED)}


def test_first_enable_creates_only_pre_containers():
    base = None
    new = _config()
    new.add_container(EcucContainerValue(short_name="McuOther", definition_ref="/X/Mcu/McuOther"))
    _set(new, "Never", 5, container="McuOther")
    active = _config()

    result, merged = _apply(base, active, new, {"C:/Mcu/McuOther": Layer.PRE, OTHER + "Never": Layer.PRE})
    assert _kinds(result) == {("C:/Mcu/McuOther", MergeKind.CREATE),
                              (OTHER + "Never", MergeKind.CREATE)}
    assert merged[OTHER + "Never"] == 5


# --- module-level parameters (P:/<Module>.<name>) -------------------------------

def test_module_level_parameter_adopted_when_untouched():
    base = _config()
    _set_module(base, "ModFlag", False)
    new = _config()
    _set_module(new, "ModFlag", True)
    active = _config()
    _set_module(active, "ModFlag", False)

    result, merged = _apply(base, active, new)
    assert result.items == [MergeItem(MOD + "ModFlag", MergeKind.ADOPT, False, True, False)]
    assert merged[MOD + "ModFlag"] is True
    assert active.parameter_values["ModFlag"].value is True


def test_module_level_parameter_kept_when_user_changed():
    base = _config()
    _set_module(base, "ModFlag", False)
    new = _config()
    _set_module(new, "ModFlag", True)

    # values_equal decides: "FALSE" is the same value as False, so the user did not change it
    untouched = _config()
    _set_module(untouched, "ModFlag", "FALSE")
    result, merged = _apply(base, untouched, new)
    assert result.items == [MergeItem(MOD + "ModFlag", MergeKind.ADOPT, False, True, "FALSE")]
    assert merged[MOD + "ModFlag"] is True

    changed = _config()
    _set_module(changed, "ModFlag", True)
    result, merged = _apply(base, changed, new)
    assert result.items == [MergeItem(MOD + "ModFlag", MergeKind.KEPT_USER, False, True, True)]
    assert result.has_changes is False
    assert merged[MOD + "ModFlag"] is True


def test_module_level_parameter_pre_forced():
    base = _config()
    _set_module(base, "ModFlag", False)
    new = _config()
    _set_module(new, "ModFlag", False)
    active = _config()
    _set_module(active, "ModFlag", True)

    result, merged = _apply(base, active, new, {MOD + "ModFlag": Layer.PRE})
    assert result.items == [MergeItem(MOD + "ModFlag", MergeKind.PRE_FORCED, False, False, True)]
    assert result.has_changes is True
    assert merged[MOD + "ModFlag"] is False
    assert active.parameter_values["ModFlag"] is not None


def test_module_level_parameter_created_or_added():
    """A module-level value new in Base' is added to Active; Pre forces its value."""
    base = _config()
    new = _config()
    _set_module(new, "ModFlag", True)
    active = _config()

    result, merged = _apply(base, active, new, {MOD + "ModFlag": Layer.PRE})
    assert result.items == [MergeItem(MOD + "ModFlag", MergeKind.PRE_FORCED, None, True, None)]
    assert result.has_changes is True
    assert merged[MOD + "ModFlag"] is True

    # not Pre → a base-side addition the user never had: adopted like any untouched value
    result, merged = _apply(base, _config(), new)
    assert result.items == [MergeItem(MOD + "ModFlag", MergeKind.ADOPT, None, True, None)]
    assert merged[MOD + "ModFlag"] is True


def test_module_level_parameter_first_enable():
    new = _config()
    _set_module(new, "ModFlag", True)
    active = _config()
    _set_module(active, "ModFlag", False)

    result, merged = _apply(None, active, new)
    assert result.items == [MergeItem(MOD + "ModFlag", MergeKind.KEPT_USER, None, True, False)]
    assert merged[MOD + "ModFlag"] is False


def test_pre_forcing_restores_a_value_the_user_removed():
    """A Pre value the user deleted from Active is put back; without Pre it is not."""
    base = _config()
    new = _config()
    _set(new, "Mode", "B")
    active = _config()                                  # the user deleted Mode
    _set(active, "Speed", 1)

    result, merged = _apply(base, active, new, {GEN + "Mode": Layer.PRE})
    assert result.items == [MergeItem(GEN + "Mode", MergeKind.PRE_FORCED, None, "B", None)]
    assert merged[GEN + "Mode"] == "B"

    plain = _config()
    _set(plain, "Speed", 1)
    result, merged = _apply(base, plain, new)
    assert _kinds(result) == {(GEN + "Mode", MergeKind.ADOPT)}
    assert merged[GEN + "Mode"] == "B"


def test_base_and_new_base_equal_but_active_moved_on():
    """Base = Base' and the user changed the value: no item, so no confirmation."""
    base = _config()
    _set(base, "Speed", 1)
    active = _config()
    _set(active, "Speed", 7)
    result, merged = _apply(base, active, base)
    assert result.items == []
    assert merged[GEN + "Speed"] == 7


def test_apply_merge_leaves_untouched_values_alone():
    """KEPT_USER and REMOVED_IN_BASE never write; only the changing kinds do."""
    base = _config()
    _set(base, "Speed", 1)
    _set(base, "Mode", "A")
    _set(base, "Flag", True)
    _top(base).reference_values["Ref"] = EcucReferenceValue("/X/Ref", "/Os/C0")
    new = _config()
    _set(new, "Speed", 2)                                # ADOPT
    _set(new, "Mode", "B")                               # KEPT_USER
    _top(new).reference_values["Ref"] = EcucReferenceValue("/X/Ref", "/Os/C1")   # ADOPT
    active = _config()
    _set(active, "Speed", 1)
    _set(active, "Mode", "Z")
    _set(active, "Flag", True)
    _top(active).reference_values["Ref"] = EcucReferenceValue("/X/Ref", "/Os/C0")

    result, merged = _apply(base, active, new)
    assert _kinds(result) == {(GEN + "Speed", MergeKind.ADOPT),
                              (GEN + "Mode", MergeKind.KEPT_USER),
                              (GEN + "Flag", MergeKind.REMOVED_IN_BASE),
                              ("R:/Mcu/McuGeneral.Ref", MergeKind.ADOPT)}
    changed = {item.key for item in result.items if item.kind is not MergeKind.KEPT_USER
               and item.kind is not MergeKind.REMOVED_IN_BASE}
    expected = flatten(new)
    for key in changed:
        assert merged[key] == expected[key], key
    assert merged[GEN + "Mode"] == "Z"                  # the user value survived
    assert merged[GEN + "Flag"] is True                 # the removed value survived
    # Base' was not touched by applying the merge
    assert flatten(new) == expected


def test_deep_copy_of_created_container_is_not_shared():
    """Editing Active after the merge cannot reach back into Base'."""
    base = _config()
    new = _config()
    _set(new, "Never", 5, container="McuOther")
    active = _config()
    before = flatten(new)

    result, _ = _apply(base, active, new, {"C:/Mcu/McuOther": Layer.PRE, OTHER + "Never": Layer.PRE})
    created = active.get_instance_by_path("/Mcu/McuOther")
    created.parameter_values["Never"].value = 99
    created.sub_containers.append(EcucContainerValue(short_name="Child", definition_ref="/X/Child"))
    assert flatten(new) == before
    assert created is not _top(new, "McuOther")


def test_the_task_10_scenario():
    """A Rec value and a Pre value upgraded in the package, one Rec value user-edited."""
    base = _config()
    _set(base, "Speed", 1)
    _set(base, "Mode", "A")
    _set(base, "L", [1, 2])
    new = _config()
    _set(new, "Speed", 2)                                # the package's Rec changed
    _set(new, "Mode", "B")                               # the package's Pre changed
    _set(new, "L", [1, 3])                               # another untouched value follows
    active = _config()
    _set(active, "Speed", 9)                             # the user changed this one
    _set(active, "Mode", "A")
    _set(active, "L", [1, 2])

    result, merged = _apply(base, active, new, {GEN + "Mode": Layer.PRE})
    assert _kinds(result) == {(GEN + "Speed", MergeKind.KEPT_USER),
                              (GEN + "Mode", MergeKind.PRE_FORCED),
                              (GEN + "L", MergeKind.ADOPT)}
    assert merged[GEN + "Speed"] == 9                    # user value kept
    assert merged[GEN + "Mode"] == "B"                   # Pre forced
    assert merged[GEN + "L"] == (1, 3)                   # untouched values follow
    report = result.to_markdown("Mcu")
    assert "预设强制" in report and "用户覆盖" in report


# --- result shape ---------------------------------------------------------------

def test_result_items_sorted_and_has_changes_reasons():
    base = _config()
    _set(base, "Speed", 1)
    _set(base, "Mode", "A")
    new = _config()
    _set(new, "Speed", 2)
    _set(new, "Mode", "B")
    active = _config()
    _set(active, "Speed", 1)
    _set(active, "Mode", "Z")

    result = three_way_merge(flatten(base), flatten(new), flatten(active), {}, set())
    assert [item.key for item in result.items] == sorted(item.key for item in result.items)
    assert _kinds(result) == {(GEN + "Speed", MergeKind.ADOPT),
                              (GEN + "Mode", MergeKind.KEPT_USER)}
    assert result.has_changes is True                   # one ADOPT is enough

    report = result.to_markdown("Mcu")
    assert "Mcu" in report
    assert GEN + "Speed" in report
    assert GEN + "Mode" in report

    kept = MergeResult([item for item in result.items if item.kind is MergeKind.KEPT_USER])
    assert kept.has_changes is False
    removed = MergeResult([MergeItem("C:/Mcu/X", MergeKind.REMOVED_IN_BASE, True, None, True)])
    assert removed.has_changes is False
    assert MergeResult([]).has_changes is False
    assert MergeResult([]).to_markdown("Mcu")


def test_values_equal_semantics_are_used():
    """The merge compares with values_equal: "TRUE" is True, " 5 " is 5."""
    assert values_equal("TRUE", True) and values_equal(" 5 ", 5)
    base = _config()
    _set(base, "Speed", 1)
    new = _config()
    _set(new, "Speed", " 2 ")
    active = _config()
    _set(active, "Speed", 1)

    result, merged = _apply(base, active, new)
    assert _kinds(result) == {(GEN + "Speed", MergeKind.ADOPT)}
    assert merged[GEN + "Speed"] == " 2 "
