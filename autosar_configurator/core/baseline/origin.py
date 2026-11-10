"""Value origin, derived by comparison rather than stored (design §6.5, §6.7).

A value's origin says who produced it, and the UI and the Pre lock read it off here:

| origin  | when                                                              | editable |
| ---     | ---                                                               | ---      |
| ``PRE`` | the key is in the Pre ownership set and the user has not unlocked it | no    |
| ``REC`` | Active equals Base, and Base's value came from Rec (or from Pre   | yes      |
|         | that the user unlocked — it is then a baseline the user may edit) |          |
| ``DEFAULT`` | Active equals Base, and Base's value is a definition default  | yes      |
| ``DERIVED`` | Active equals Base, and Base's value was derived              | yes      |
| ``USER``    | Active differs from Base, or Base has no such key             | yes      |

``PRE`` needs its own key set (``pre_keys``), not the snapshot's layer map: Pre owns a key
whether or not the current baseline still carries it, so a Pre value the baseline dropped
must still report ``PRE`` and still be restored by the merge. ``merge._forced_by_pre`` works
from just such a set; the two must agree, or the UI would show a value as editable that the
merge immediately reverts.

Nothing is written into the configuration: the origin is recomputed on every compare from
``flatten(active)``, ``flatten(base)`` and the layer map ``compose_base`` returned. That is
why the live arxml keeps its format and EB Tresos round-trips stay unaffected.

Two rules the table implies but that are easy to invert:

- **Unlocked Pre is not PRE.** PRE is exactly what the lock in Task 11 rejects, so an
  unlocked key that still classified PRE would stay read-only — unlocking would do nothing.
  It falls through to the ordinary comparison instead: equal to Base → ``REC`` (a baseline
  value the user may now edit), changed → ``USER``.
- **A key missing from Base or from the layer map is USER.** A value the user added, or one
  an upgrade dropped, cannot be shown to come from the baseline; guessing DEFAULT would let
  an upgrade claim to own it.
"""
from enum import Enum
from typing import Any, Dict, Optional, Set

from ..model.configuration_model import EcucModuleConfiguration
from .compose import Layer
from .values import ValueKey, flatten, values_equal

__all__ = ["Origin", "classify", "origins_for"]


class Origin(Enum):
    """Where a live value came from (design §6.5's origin table)."""
    DEFAULT = "default"       # the definition's static default
    REC = "rec"               # the module package's recommended value
    DERIVED = "derived"       # a derivation / repair step (reserved)
    PRE = "pre"               # Pre: read-only unless the user unlocked the key
    USER = "user"             # the user's own value, or no baseline knows it


# Layer → Origin for a value that still equals Base. ``Layer.PRE`` maps to ``REC``, not
# ``PRE``: reaching this table means the key is NOT a locked Pre value (locked Pre returns
# before the comparison), and an unlocked Pre value behaves like a baseline the user edits.
_ORIGIN_OF_LAYER = {
    Layer.DEFAULT: Origin.DEFAULT,
    Layer.REC: Origin.REC,
    Layer.DERIVED: Origin.DERIVED,
    Layer.PRE: Origin.REC,
}


def classify(key: ValueKey, active: Dict[ValueKey, Any],
             base: Optional[Dict[ValueKey, Any]],
             base_layers: Dict[ValueKey, Layer],
             unlocked: Set[ValueKey],
             pre_keys: Set[ValueKey]) -> Origin:
    """The origin of one flattened key (``flatten`` output on both sides).

    Args:
        key: A ``"C:"``, ``"P:"`` or ``"R:"`` key, as ``flatten`` builds them.
        active: ``flatten(active_config)``.
        base: ``flatten(base_config)``, or ``None`` when there is no snapshot — then no
            key comes from the layers, since nothing connects it to the baseline.
        base_layers: The layer each Base key came from (``compose_base``'s second result,
            or the same map stored alongside the snapshot).
        unlocked: Pre keys the user unlocked; they are no longer PRE.
        pre_keys: Every key Pre owns, flattened with the module's ``module_name`` — present
            in the baseline or not. Ownership, not presence: the set, not ``base_layers``,
            decides PRE.

    Returns:
        ``PRE`` when ``pre_keys`` owns the key and it is locked, whatever Base or Active
        say; else, when Active holds the key and equals Base, the key's layer as an
        :class:`Origin` (``DEFAULT`` / ``REC`` / ``DERIVED``); else ``USER``.

    A locked Pre key that also happens to come from ``Layer.PRE`` in the layers returns
    ``PRE`` from the ownership rule first, so ``base_layers`` never outranks it. An
    *unlocked* Pre key that still equals Base reports the layer's origin — ``REC`` for
    ``Layer.PRE`` — because the value is a baseline the user may now edit. The badge then
    says Rec while provenance is Pre; a caller that must show "from pre, unlocked" (the
    Task 11 lock and the panel's tooltip) has to consult ``unlocked`` itself alongside the
    origin, since :class:`Origin` deliberately has no unlocked-Pre member.
    """
    if key in pre_keys and key not in unlocked:
        return Origin.PRE
    if base is None or key not in base or key not in active:
        return Origin.USER
    if not values_equal(active[key], base[key]):
        return Origin.USER
    layer = base_layers.get(key)
    return _ORIGIN_OF_LAYER[layer] if layer is not None else Origin.USER


def origins_for(config: EcucModuleConfiguration,
                base_config: Optional[EcucModuleConfiguration],
                base_layers: Dict[ValueKey, Layer],
                unlocked: Set[ValueKey],
                pre_keys: Set[ValueKey],
                module_name: Optional[str] = None) -> Dict[ValueKey, Origin]:
    """The origin of every key of ``config``, sorted by key.

    Covers everything ``flatten`` produces — containers (``C:``), parameters (``P:``),
    references (``R:``) and module-level parameters (``P:/<module>.<name>``) — because it is
    built on ``flatten`` itself.

    Args:
        config: The live configuration.
        base_config: The accepted snapshot, or ``None``; it is flattened with the *same*
            ``module_name`` as ``config``, so keys compare as strings. A Pre fragment whose
            ``short_name`` is not the module name must be flattened re-rooted, exactly as the
            merge does it.
        base_layers: The layer map of the baseline.
        unlocked: Pre keys the user unlocked.
        pre_keys: Every key Pre owns, in the same key space (``flatten(pre_fragment,
            module_name)``), including keys the current snapshot no longer has.
        module_name: Path root for every key; ``None`` uses each configuration's own names.

    Returns:
        ``{ValueKey: Origin}`` for every live key, in sorted key order.
    """
    active = flatten(config, module_name)
    base = None if base_config is None else flatten(base_config, module_name)
    return {key: classify(key, active, base, base_layers, unlocked, pre_keys)
            for key in sorted(active)}
