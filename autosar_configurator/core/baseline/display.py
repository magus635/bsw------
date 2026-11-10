"""The words the UI uses for a value's origin and for the Pre lock (design §6.5, §6.8).

Pure text, no Qt: the config panel, the edit controller and the batch dialog ask this
module what to say, and a test can assert it without a display. The origin itself is
computed in :mod:`origin`; nothing here decides whether a value is editable — that is
``ConfigurationManager.check_editable``.

One predicate governs both the badge and the lock: :func:`module_note` returns a note when
the baseline cannot speak for the module. Reading Task 10's ``USER`` rule any other way
presents two situations wrongly:

- **layers dropped** (``layers_untrusted``), **or a snapshot with no layers** beside it: the
  snapshot is Base, but nothing is known to be Pre or REC, so every value reports ``USER``
  and the lock is off. Showing ``USER``-but-unlocked per value would look like a lock the
  user had opened; the module says ``基线不可用`` instead, once, and the per-value badges are
  suppressed. This is the module-level rule, and it is authoritative.
- **layers but no snapshot** (``base_config is None`` with layers): Pre keys are still known
  from the layers file, so the lock and the ``PRE`` badge still work; only comparison
  origins fall back to ``USER``. That is *not* an unavailable baseline.
"""
from typing import Any, Dict, Iterable, List, Optional, Sequence, Tuple

from .origin import Origin
from .session import ModuleBaseline

__all__ = [
    "UNAVAILABLE_TEXT", "ORIGIN_LABELS", "module_note", "origin_text",
    "pre_file_names", "partition_locked",
]

UNAVAILABLE_TEXT = "基线不可用"

ORIGIN_LABELS: Dict[Origin, str] = {
    Origin.DEFAULT: "DEFAULT（定义默认值）",
    Origin.REC: "REC（模块包推荐值）",
    Origin.DERIVED: "DERIVED（派生值）",
    Origin.PRE: "PRE（预配置）",
    Origin.USER: "USER（用户值）",
}


def module_note(baseline: Optional[ModuleBaseline]) -> Optional[str]:
    """The module-wide note, or ``None`` when the baseline can speak for its values.

    Args:
        baseline: The module's baseline, as ``WorkspaceProject.baselines`` holds it.

    Returns:
        ``"基线不可用"`` when the layers of the snapshot were dropped (they named another
        snapshot, or none), or when there are no layers at all while a snapshot or recorded
        Pre keys exist: no key can be told apart from a user value in either case, so the
        module says it once instead of badging values. ``None`` for a project with no
        baseline at all — a format ≤7 module, or a package that contributes no value layer
        has nothing to explain (and no lock either).

        This is the authoritative rule: a caller that shows per-value origins must not do so
        while this returns a note, and the ``USER`` label of
        :data:`ORIGIN_LABELS` is about a *user edit*, not about a missing baseline.
    """
    if baseline is None:
        return None
    if baseline.layers_untrusted:
        return UNAVAILABLE_TEXT
    if not baseline.layers and (baseline.base_config is not None or baseline.pre_keys):
        # A snapshot with no layers beside it (or Pre keys recorded without them): Base
        # exists, but nothing says which value came from where, so every value would report
        # USER and no key would be known to be Pre. A baseline the package never gave a
        # value layer to is not this case: it has no snapshot, no pre keys and no note.
        return UNAVAILABLE_TEXT
    return None


def origin_text(origin: Origin, pre_files: Sequence[str] = (), locked: bool = False) -> str:
    """The one-line badge/tooltip text for a value's origin.

    Args:
        origin: The value's origin.
        pre_files: File names the Pre values came from (``pre_file_names``), the manifest's
            ``pre`` paths' holding files. Named only for ``PRE``; ignored otherwise.
        locked: Whether the key is a locked Pre key. The text says so, and says that the
            value can be unlocked; an unlocked Pre value arrives here as ``REC`` (see
            :mod:`origin`), so the caller passes ``locked=True`` from the lock check.

    Returns:
        ``"来源：<origin>"``, the Pre files when the origin is PRE, and the lock state. A
        locked Pre value says it is locked and how to unlock it; an *unlocked* Pre value
        arrives here with ``locked=False`` and the origin :class:`Origin.REC` (see
        :mod:`origin`), so ``pre_files`` carries the only trace of its Pre provenance.
    """
    text = f"来源：{ORIGIN_LABELS.get(origin, origin.value.upper())}"
    if origin is Origin.PRE and pre_files:
        text += " " + ", ".join(sorted(set(pre_files)))
    if locked:
        text += "\n此值为预配置，已锁定；如需修改请右键选择“解锁此参数”。"
    return text


def pre_file_names(package: Any, chip: Optional[str] = None) -> List[str]:
    """The selected package files that hold the package's Pre value collections.

    Args:
        package: The module package (``ModulePackage``), or ``None``.
        chip: Selected chip; the package picks chip-conditional files with it.

    Returns:
        Sorted, de-duplicated file names (``McuPreConfiguration.xdm``), never a path: the
        tooltip names the file the user would have to look at, not where it lives. A
        package whose collection cannot be located in a selected file gives ``[]`` — the
        tooltip then names the origin without a file, instead of failing.
    """
    if package is None:
        return []
    manifest = getattr(package, "manifest", None)
    ar_paths = list(getattr(manifest, "pre", None) or [])
    if not ar_paths:
        return []
    names = set()
    try:
        from ..packages.value_index import index_value_collections

        for path in package.selected_files(chip):
            if path.suffix.lower() not in (".arxml", ".xdm"):
                continue
            if not any(ar_path in index_value_collections(path) for ar_path in ar_paths):
                continue
            names.add(path.name)
    except Exception:  # noqa: BLE001 - the tooltip must never fail the panel
        return []
    return sorted(names)


def partition_locked(config_manager: Any,
                      items: Iterable[Tuple[Any, Optional[str]]]
                      ) -> Tuple[List[Tuple[Any, Optional[str]]], List[str]]:
    """Split ``(instance, name)`` items into the editable ones and the locked keys.

    The batch dialog and the panel's unlock menu use this instead of calling
    ``check_editable`` in a loop, so "skipped" always carries the same key strings the
    error would: the ValueKey of the locked value, sorted, without duplicates.

    Args:
        config_manager: The ``ConfigurationManager`` that owns the instances.
        items: ``(instance, name)`` pairs; ``name=None`` means the container itself.

    Returns:
        ``(editable, skipped)``: the pairs that may be written, in the given order, and the
        sorted keys of the locked ones. A manager without ``check_editable`` locks nothing.
    """
    from ..config_manager import PreLockedError

    check = getattr(config_manager, "check_editable", None)
    editable: List[Tuple[Any, Optional[str]]] = []
    skipped = set()
    for instance, name in items:
        if check is None:
            editable.append((instance, name))
            continue
        try:
            check(instance, name)
        except PreLockedError as exc:
            skipped.add(exc.key)
            continue
        editable.append((instance, name))
    return editable, sorted(skipped)
