"""Three-way merge of Base, Base' and Active (design §6.5).

Loading a project recomputes the baseline Base' (``compose_base``) and merges it with the
snapshot Base and the live configuration Active, one ``ValueKey`` at a time. The merge
itself is pure — dictionaries in, a :class:`MergeResult` out — and :func:`apply_merge` is
the only function that writes, into Active, the values the result says to adopt:

| condition                                        | kind                | Active changes |
| ---                                              | ---                 | ---            |
| key is PRE (and not unlocked), Active ≠ Base'    | ``PRE_FORCED``      | yes, to Base'  |
| new in Base', and Pre introduces its container   | ``CREATE``          | yes, copied    |
| Base ≠ Base', Active = Base                      | ``ADOPT``           | yes, to Base'  |
| Base ≠ Base', Active ≠ Base                      | ``KEPT_USER``       | no             |
| in Base, gone from Base'                         | ``REMOVED_IN_BASE`` | **never**      |
| Base = Base'                                     | *(no item)*         | no             |

Three rules are easy to get wrong, so they are stated here:

- **Nothing is ever deleted.** A value or container that Base has and Base' lacks is only
  reported (``REMOVED_IN_BASE``). That is what lets a user who renamed or removed a
  container keep it (design §6.5, "Pre 删除了容器").
- **The Pre rule outranks "Base = Base' → unchanged".** A value the user may not edit is
  forced back even when the baseline did not change, e.g. after a value file import
  overwrote it.
- **Only Pre creates containers.** A container that is new in Base' but comes from Rec or a
  default is not forced into Active — that would recreate a container the user deleted. Its
  values are reported as ``KEPT_USER`` and Active keeps lacking them; a snapshot-less
  (``base=None``) merge reports them the same way.

A multi-value parameter or reference is one ordered value: it is compared as a whole and
replaced as a whole, so ``(1, 2)`` and ``(2, 1)`` differ.

``base=None`` means first enable or a project migrated without a snapshot: Active's values
are all USER, so no ``ADOPT`` is emitted; only Pre values and the containers Pre introduces
change.

All three dictionaries must be flattened with the *same* module name
(``flatten(config, module_name)``), because the keys are compared as strings: a value
collection whose ``short_name`` is not the module name (``McuPreConfiguration`` flattened
without re-rooting) would give ``/McuPreConfiguration/...`` keys and the merge would see
every Active key as removed and every Base' key as new.
"""
from dataclasses import dataclass, field
from enum import Enum
from typing import Any, Dict, List, Optional, Set

from ..model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
    EcucReferenceValue,
)
from ..model.definition_model import EcucModuleDef
from .compose import Layer
from .values import ValueKey, values_equal

__all__ = ["MergeKind", "MergeItem", "MergeResult", "three_way_merge", "apply_merge"]


class MergeKind(Enum):
    """What the merge decided for one key."""
    ADOPT = "adopt"                       # take Base' (the user had not touched the value)
    KEPT_USER = "kept_user"               # keep Active (the user changed the value)
    PRE_FORCED = "pre_forced"             # force Base' (a Pre value the user may not edit)
    CREATE = "create"                     # bring over something Base' adds
    REMOVED_IN_BASE = "removed_in_base"   # Base has it, Base' does not: reported, never deleted


_CHANGING = frozenset({MergeKind.ADOPT, MergeKind.PRE_FORCED, MergeKind.CREATE})

_KIND_LABELS = {
    MergeKind.ADOPT: "采用新基线（用户未修改）",
    MergeKind.KEPT_USER: "基线变化但已被用户覆盖（保留用户值）",
    MergeKind.PRE_FORCED: "预设强制",
    MergeKind.CREATE: "创建",
    MergeKind.REMOVED_IN_BASE: "新基线中没有（不删除，请用户决定）",
}


@dataclass(frozen=True)
class MergeItem:
    """One merge decision. ``new_value`` is Base'; ``None`` there means "not present"."""
    key: ValueKey
    kind: MergeKind
    base_value: Any = None
    new_value: Any = None
    active_value: Any = None


@dataclass
class MergeResult:
    """Every decision of one module's merge, sorted by key."""
    items: List[MergeItem] = field(default_factory=list)

    @property
    def has_changes(self) -> bool:
        """Whether confirmation is needed: some key is adopted, forced or created."""
        return any(item.kind in _CHANGING for item in self.items)

    def of_kind(self, kind: MergeKind) -> List[MergeItem]:
        """The items of one kind, in key order."""
        return [item for item in self.items if item.kind is kind]

    def to_markdown(self, module: str) -> str:
        """The preview shown before the merge is applied (§6.5, preview and confirm)."""
        lines = [f"# {module} 基线合并预演", ""]
        if not self.items:
            lines.append("基线没有变化，活配置无需改动。")
            return "\n".join(lines)
        counts = [f"{_KIND_LABELS[kind]} {len(self.of_kind(kind))}"
                  for kind in MergeKind if self.of_kind(kind)]
        lines += ["，".join(counts), ""]
        for kind in MergeKind:
            items = self.of_kind(kind)
            if not items:
                continue
            lines += [f"## {_KIND_LABELS[kind]}（{len(items)}）", ""]
            if kind is MergeKind.REMOVED_IN_BASE:
                lines += ["基线中已不存在，但**不会自动删除**，请自行决定是否删除：", ""]
            for item in items:
                if kind is MergeKind.REMOVED_IN_BASE:
                    lines.append(f"- `{item.key}`（基线值 {_show(item.base_value)}）")
                elif kind is MergeKind.CREATE:
                    lines.append(f"- `{item.key}` → {_show(item.new_value)}")
                else:
                    lines.append(f"- `{item.key}`：{_show(item.active_value)} → {_show(item.new_value)}")
            lines.append("")
        return "\n".join(lines)


def _show(value: Any) -> str:
    """A value as it reads in the report; ``None`` is also how "absent" shows."""
    if value is None:
        return "（无）"
    if isinstance(value, tuple):
        return "(" + ", ".join(_show(v) for v in value) + ")"
    return str(value)


# --- key helpers ----------------------------------------------------------------

def _is_container(key: ValueKey) -> bool:
    return key.startswith("C:")


def _path_of(key: ValueKey) -> str:
    """``"P:/Mcu/McuGeneral.Speed"`` → ``"/Mcu/McuGeneral"``.

    The path/name split is the *first* dot: a ``C:`` key has none, a module-level key is
    ``/Mcu.Speed`` and a container key ``/Mcu/McuGeneral.Speed``, so a dot inside a
    container name never confuses the two.
    """
    rest = key.split(":", 1)[1]
    return rest if _is_container(key) else rest.split(".", 1)[0]


def _name_of(key: ValueKey) -> str:
    """``"P:/Mcu/McuGeneral.Speed"`` → ``"Speed"`` ("" for a container key)."""
    rest = key.split(":", 1)[1]
    return "" if _is_container(key) else rest.split(".", 1)[-1]


def _container_path_of(key: ValueKey) -> str:
    """The container a key belongs to; a container key names itself.

    A module-level parameter (``P:/Mcu.Flag``) belongs to no container: ``"/Mcu"``.
    """
    if _is_container(key):
        return key.split(":", 1)[1]
    return _path_of(key)


def _is_container_path_missing(active: Dict[ValueKey, Any], path: str) -> bool:
    """Whether ``path`` names a container Active does not have.

    ``/Mcu`` alone is the module (a module-level parameter), not a container.
    """
    return path.count("/") > 1 and active.get("C:" + path) is None


# --- the merge ------------------------------------------------------------------

def _forced_by_pre(key: ValueKey, new_value: Any, active_value: Any, has_target: bool,
                   new_layers: Dict[ValueKey, Layer], unlocked: Set[ValueKey]) -> bool:
    """Pre and not unlocked, and Active differs from Base' (or lacks the value entirely).

    ``has_target`` says whether Active has somewhere to put the value; a Pre value the user
    removed is restored, one whose container Active never had is left to ``CREATE``.
    """
    if (new_value is None or _is_container(key) or new_layers.get(key) is not Layer.PRE
            or key in unlocked):
        return False
    if active_value is None:
        return has_target
    return not values_equal(active_value, new_value)


def three_way_merge(base: Optional[Dict[ValueKey, Any]], new_base: Dict[ValueKey, Any],
                    active: Dict[ValueKey, Any], new_layers: Dict[ValueKey, Layer],
                    unlocked: Set[ValueKey]) -> MergeResult:
    """Merge Base (snapshot), Base' (``new_base``) and Active, one ``ValueKey`` at a time.

    Args:
        base: Flattened snapshot, or ``None`` for first enable / migration (every Active
            value is then USER and only Pre may change it).
        new_base: Flattened baseline just composed from the module package.
        active: Flattened live configuration.
        new_layers: The layer each key of ``new_base`` comes from (``compose_base``
            origins).
        unlocked: Pre keys the user unlocked; they merge like ordinary keys.

    Returns:
        A :class:`MergeResult` sorted by key. A key that needs no attention gets no entry:
        Base = Base', Active already equals Base', or only Active has it (a user value the
        baseline never knew stays untouched).
    """
    keys = set(new_base)
    if base is not None:
        keys |= set(base)

    # The containers only Pre has and Active lacks: those, and only those, are created.
    # A nested container counts as new when Active lacks it, whatever its parent's story.
    created = {key for key in new_base
               if _is_container(key) and key not in active
               and (base is None or key not in base)
               and new_layers.get(key) is Layer.PRE and key not in unlocked}

    def has_target(key: ValueKey) -> bool:
        """Whether Active already has the container this key's value lives in.

        A module-level parameter (``P:/<Module>.<name>``) always has one. A value inside a
        container this merge creates does not: it comes over with the ``CREATE`` whole,
        instead of being forced into a container that does not exist yet.
        """
        path = _path_of(key)
        if path.count("/") <= 1:                     # module level: Active always holds it
            return True
        return "C:" + path in active

    def inside_created(key: ValueKey) -> bool:
        """Whether the key's container is created, or sits inside a created container."""
        path = _container_path_of(key)
        while path.count("/") > 1:                   # walk up to the outermost container
            if "C:" + path in created:
                return True
            path = path.rpartition("/")[0]
        return False

    items: List[MergeItem] = []
    for key in sorted(keys):
        new_value = new_base.get(key)
        active_value = active.get(key)
        base_value = None if base is None else base.get(key)

        # 1. Pre is read-only: it wins over every other rule, even "Base = Base'".
        if _forced_by_pre(key, new_value, active_value, has_target(key), new_layers, unlocked):
            items.append(MergeItem(key, MergeKind.PRE_FORCED, base_value, new_value, active_value))
            continue

        # 2. Keys Base' no longer has: report only, never delete.
        if new_value is None:
            items.append(MergeItem(key, MergeKind.REMOVED_IN_BASE, base_value, None, active_value))
            continue

        # 3. Containers: present or not, nothing else to compare.
        if _is_container(key):
            if key in active:
                continue
            if key in created:
                items.append(MergeItem(key, MergeKind.CREATE, None, True, None))
            elif base is None or key not in base:
                items.append(MergeItem(key, MergeKind.KEPT_USER, None, True, None))
            # else: Base' still has a container Active lacks (the user deleted or renamed
            # it). Not resurrected, not reported — the REMOVED_IN_BASE rule is about the
            # other direction, and a value Base' merely repeats is not news.
            continue

        # 4. Without a snapshot every Active value is USER, so equal values need no
        #    report; a value Active already holds as Base' needs none either.
        if values_equal(active_value, new_value) and (base is None or key not in base):
            continue

        # 5. Everything inside a container this merge creates comes with it.
        if inside_created(key):
            items.append(MergeItem(key, MergeKind.CREATE, None, new_value, None))
            continue

        # 6. A value whose container Active does not have cannot be adopted or forced:
        #    only a container Pre introduces is created, so it is only reported.
        if _is_container_path_missing(active, _path_of(key)):
            items.append(MergeItem(key, MergeKind.KEPT_USER, base_value, new_value, active_value))
            continue

        if base is not None and key in base:
            if values_equal(base_value, new_value):
                continue                                     # the baseline did not change
            if values_equal(active_value, base_value):
                items.append(MergeItem(key, MergeKind.ADOPT, base_value, new_value, active_value))
            else:
                items.append(MergeItem(key, MergeKind.KEPT_USER, base_value, new_value, active_value))
            continue

        # New in Base' and not in Base: a base-side addition, or a value the user already
        # has. With no snapshot (first enable, migration) every Active value is USER, so
        # the value is only reported and Base' does not overwrite it.
        if base is not None and (active_value is None or values_equal(active_value, new_value)):
            items.append(MergeItem(key, MergeKind.ADOPT, base_value, new_value, active_value))
        else:
            items.append(MergeItem(key, MergeKind.KEPT_USER, base_value, new_value, active_value))

    return MergeResult(items)


# --- applying -------------------------------------------------------------------

def _clone_param(param: EcucParameterValue) -> EcucParameterValue:
    return EcucParameterValue(definition_ref=param.definition_ref, value=param.value,
                              index=param.index, dest_type=param.dest_type)


def _clone_ref(ref: EcucReferenceValue) -> EcucReferenceValue:
    return EcucReferenceValue(definition_ref=ref.definition_ref, value_ref=ref.value_ref,
                              dest_type=ref.dest_type, index=ref.index)


def _clone_subtree(src: EcucContainerValue, parent: Optional[EcucContainerValue],
                   module_name: str) -> EcucContainerValue:
    """A deep copy of ``src`` and its subtree, placed under ``parent``.

    The clone approach of ``compose._shell`` / ``_merge_container``: new value objects, so
    a later edit of Active cannot reach back into Base', and the same identity fields. The
    parent goes to the constructor, not a later assignment, so a nested ``get_path()``
    already sees its final place.
    """
    clone = EcucContainerValue(
        short_name=src.short_name, definition_ref=src.definition_ref,
        def_dest_type=src.def_dest_type, parent=parent, module_name=module_name,
        index=src.index, uuid=src.uuid, variant=src.variant)
    for name, param in src.parameter_values.items():
        clone.parameter_values[name] = _clone_param(param)
    for name, params in src.multi_parameter_values.items():
        clone.multi_parameter_values[name] = [_clone_param(p) for p in params]
    for name, ref in src.reference_values.items():
        clone.reference_values[name] = _clone_ref(ref)
    for name, refs in src.multi_reference_values.items():
        clone.multi_reference_values[name] = [_clone_ref(r) for r in refs]
    for sub in src.sub_containers:
        clone.sub_containers.append(_clone_subtree(sub, clone, module_name))
    return clone


def _create_container(active_config: EcucModuleConfiguration,
                      new_base_config: EcucModuleConfiguration, key: ValueKey) -> Optional[EcucContainerValue]:
    """Copy the container ``key`` names, with its subtree, from Base' into Active.

    Keys are applied in order, and ``"C:" + parent`` sorts before ``"C:" + parent + "/child"``,
    so the parent of a nested container already exists when its turn comes. The copy is
    re-rooted on Active's own name, not the name the key happens to carry.
    """
    existing = active_config.get_instance_by_path(_container_path(key, active_config.short_name))
    if existing is not None:
        return existing
    source = new_base_config.get_instance_by_path(key.split(":", 1)[1])
    if source is None:
        return None                       # Base' does not have it: nothing to copy
    parent_path = _container_path(key, active_config.short_name).rpartition("/")[0]
    parent = active_config.get_instance_by_path(parent_path)
    clone = _clone_subtree(source, parent, active_config.short_name)
    if parent is None:
        active_config.add_container(clone)
    else:
        parent.add_sub_container(clone)
    return clone


def _container_path(key: ValueKey, module_name: str) -> str:
    """A ``C:`` key re-rooted on ``module_name``: ``/Other/X`` → ``/Mcu/X``."""
    parts = key.split(":", 1)[1].lstrip("/").split("/")
    return "/" + "/".join([module_name] + parts[1:])


def apply_merge(active_config: EcucModuleConfiguration,
                module_def: Optional[EcucModuleDef],
                new_base_config: EcucModuleConfiguration,
                result: MergeResult) -> None:
    """Write the merge's changes into ``active_config``; delete nothing.

    Only ``ADOPT``, ``PRE_FORCED`` and ``CREATE`` items are applied; ``KEPT_USER`` and
    ``REMOVED_IN_BASE`` leave Active alone. Afterwards Active equals
    ``flatten(new_base_config)`` for exactly those keys.

    Args:
        active_config: The live configuration, modified in place.
        module_def: The module definition, source of the DEFINITION-REF a module-level
            value needs when Active gains one.
        new_base_config: Base', the source of every adopted value and copied subtree.
        result: The merge result to apply.
    """
    changing = [item for item in result.items if item.kind in _CHANGING]

    # Containers first, in key order: "C:/Mcu/A" before "C:/Mcu/A/B", so a nested
    # container always finds its parent. Every value then has somewhere to go.
    for item in changing:
        if _is_container(item.key):
            _create_container(active_config, new_base_config, item.key)

    root = "/" + active_config.short_name
    for item in changing:
        if _is_container(item.key):
            continue
        path = _path_of(item.key)
        name = _name_of(item.key)
        if path == root:                                 # a module-level parameter
            active_config.set_parameter_value(name, item.new_value,
                                              _module_param_ref(module_def, new_base_config, name))
            active_config.parameter_values[name].is_modified = True
            continue
        container = active_config.get_instance_by_path(path)
        if container is None:                            # not reachable for a CREATE; never overwrite
            continue
        source = new_base_config.get_instance_by_path(path)
        _set_value(container, name, item.new_value, source)

    active_config.is_modified = True


def _module_param_ref(module_def: Optional[EcucModuleDef],
                      new_base_config: EcucModuleConfiguration, name: str) -> str:
    """The DEFINITION-REF a module-level value gets in Active: Base','s or the def's."""
    source = new_base_config.parameter_values.get(name)
    if source is not None and source.definition_ref:
        return source.definition_ref
    pdef = module_def.parameters.get(name) if module_def is not None else None
    return (getattr(pdef, "definition_ref", "") or "") if pdef is not None else ""


def _set_value(container: EcucContainerValue, name: str, value: Any,
               source: Optional[EcucContainerValue]) -> None:
    """Write one Base' value into ``container``, keeping Base''s DEFINITION-REF.

    A tuple is a multi-value parameter or multi-reference and replaces the whole list;
    which of the two it is comes from the Base' object, never from the value's shape.
    """
    if isinstance(value, tuple):
        if source is not None and name in source.multi_reference_values:
            container.multi_parameter_values.pop(name, None)
            container.multi_reference_values[name] = [
                _clone_ref(r) for r in source.multi_reference_values[name]]
        elif source is not None and name in source.multi_parameter_values:
            container.reference_values.pop(name, None)
            container.multi_parameter_values[name] = [
                _clone_param(p) for p in source.multi_parameter_values[name]]
        else:                                            # no Base' object: keep Active's shape
            if name in container.reference_values or name in container.multi_reference_values:
                container.multi_parameter_values.pop(name, None)
                container.multi_reference_values[name] = [
                    EcucReferenceValue(definition_ref="", value_ref=v, index=i)
                    for i, v in enumerate(value)]
            else:
                container.reference_values.pop(name, None)
                container.multi_parameter_values[name] = [
                    EcucParameterValue(definition_ref="", value=value, index=i)
                    for i, value in enumerate(value)]
        return

    if source is not None and name in source.reference_values:
        container.multi_reference_values.pop(name, None)
        container.reference_values[name] = _clone_ref(source.reference_values[name])
        return
    if source is not None and name in source.parameter_values:
        container.multi_parameter_values.pop(name, None)
        container.parameter_values[name] = _clone_param(source.parameter_values[name])
        return
    # No Base' object for this value (a fragment re-rooted elsewhere): keep the shape
    # Active had, and fall back to a plain parameter.
    if name in container.reference_values or name in container.multi_reference_values:
        container.multi_reference_values.pop(name, None)
        container.reference_values[name] = EcucReferenceValue(definition_ref="", value_ref=value)
    else:
        container.multi_parameter_values.pop(name, None)
        container.parameter_values[name] = EcucParameterValue(definition_ref="", value=value)
