"""Baseline session wiring: Base' from a package, reconciliation, persistence (design §6.5–§6.7).

This is step ④ of the load flow, the only place where the baseline layer meets a real
project. Three things happen here:

- :func:`compute_new_base` composes Base' for one module from its package's Rec and Pre
  collections (plus any DERIVED collections a caller passes);
- :func:`reconcile` merges Base' with the saved Base and the live Active, asks the caller
  to confirm, and writes the result into Active;
- :func:`write_layers` / :func:`read_layers` keep Base's *layers* beside the snapshot, so a
  later session classifies origins without recomputing them from Base' (a recomputation
  would relabel a value the previous session accepted).

All three flattened views — Active, Base and Base' — use the *same* ``module_name``, because
the merge compares :data:`ValueKey` strings. A Pre fragment saved as its own collection
(``McuPreConfiguration``) flattened without re-rooting would give ``/McuPreConfiguration/...``
keys and every Active value would look removed.

``reconcile`` never applies anything without a ``confirm`` that returns True: a rejected
merge leaves Active and Base untouched, so the next open prompts again. ``confirm=None`` (a
command-line run, a test) counts as a rejection — the result is still returned, so the
caller can report what would have changed.
"""
import json
import logging
from dataclasses import dataclass, field
from datetime import datetime
from pathlib import Path
from typing import Callable, Dict, List, Optional, Set, Tuple

from ..model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
    EcucReferenceValue,
)
from ..model.definition_model import EcucModuleDef
from ..packages.package import ModulePackage
from .. import project_paths
from .compose import Layer, compose_base
from .merge import MergeApplyError, MergeResult, _clone_subtree, apply_merge, three_way_merge
from .values import ValueKey, flatten

__all__ = [
    "ModuleBaseline", "compute_new_base", "reconcile",
    "base_snapshot_path", "base_layers_path", "report_path",
    "write_layers", "read_layers", "adopt_base", "write_baseline", "load_baseline",
]

_log = logging.getLogger(__name__)

Confirm = Callable[[str, MergeResult], bool]

_LAYER_BY_NAME = {layer.name.lower(): layer for layer in Layer}


@dataclass
class ModuleBaseline:
    """One module's baseline: Base' and what produced it.

    Attributes:
        base_config: The composed baseline. ``None`` in a baseline read back from a layers
            file, which stores the layers only (the snapshot holds the values).
        layers: The layer each flattened key of ``base_config`` came from.
        pre_keys: Every key Pre owns, flattened with the module's name — present in the
            baseline or not. This is the ownership set ``origin.classify`` locks, and it
            survives a baseline that dropped a Pre value.
        module_name: Path root the keys were flattened with.
        dirty: Whether the snapshot on disk is older than ``base_config``; set when a merge
            is applied and cleared when the snapshot is written.
        has_layers: Whether the package contributed a Rec, Pre or derived value layer. A
            package with none has no baseline: the module keeps its Active untouched,
            exactly as a format ≤7 project does. It is not ``bool(layers)``: a module def
            with static defaults fills DEFAULT keys even when the package gave nothing.
    """
    base_config: Optional[EcucModuleConfiguration] = None
    layers: Dict[ValueKey, Layer] = field(default_factory=dict)
    pre_keys: Set[ValueKey] = field(default_factory=set)
    module_name: str = ""
    dirty: bool = False
    has_layers: bool = False


# --- paths ----------------------------------------------------------------------

def base_snapshot_path(project, module: str) -> Path:
    """``<base>/<Module>.arxml`` — the accepted baseline snapshot."""
    return project_paths.resolve(project, "base") / f"{module}.arxml"


def base_layers_path(project, module: str) -> Path:
    """``<base>/<Module>.layers.json`` — the layers of the snapshot beside it."""
    return project_paths.resolve(project, "base") / f"{module}.layers.json"


def report_path(project, module: str, now: Optional[datetime] = None) -> Path:
    """``<history>/reports/<YYYYmmdd-HHMMSS>_merge_<Module>.md`` for one merge report."""
    stamp = (now or datetime.now()).strftime("%Y%m%d-%H%M%S")
    return project_paths.resolve(project, "history") / "reports" / f"{stamp}_merge_{module}.md"


# --- composing Base' ------------------------------------------------------------

def compute_new_base(pkg: ModulePackage, chip: Optional[str], module_def: Optional[EcucModuleDef],
                     module_name: str,
                     derived: Optional[List[EcucModuleConfiguration]] = None) -> ModuleBaseline:
    """Compose Base' of ``module_name`` from ``pkg``'s Rec and Pre collections.

    Args:
        pkg: The module package.
        chip: Selected chip; the package picks its chip-conditional files with it.
        module_def: The module definition, source of the static default values.
        module_name: Module short name; every key is rooted on it.
        derived: Optional DERIVED-layer collections (empty in phase 1).

    Returns:
        A :class:`ModuleBaseline`. ``layers`` is empty when the package contributes no
        value at all — a package without Rec or Pre leaves a project's configuration as it
        was, exactly like a format ≤7 project.
    """
    layers: Dict[Layer, List[EcucModuleConfiguration]] = {
        Layer.REC: pkg.load_rec(chip),
        Layer.PRE: pkg.load_pre(chip),
    }
    if derived:
        layers[Layer.DERIVED] = list(derived)
    base_config, origins = compose_base(module_def, module_name, layers)

    pre_keys: Set[ValueKey] = {key for key, layer in origins.items() if layer is Layer.PRE}
    for config in layers[Layer.PRE]:
        pre_keys |= set(flatten(config, module_name))
    baseline = ModuleBaseline(base_config=base_config, layers=origins, pre_keys=pre_keys,
                              module_name=module_name)
    # A package with no value layer at all is not a baseline: the module keeps its Active
    # untouched, exactly as a format ≤7 project does, instead of being seeded from the
    # definition's defaults.
    baseline.has_layers = bool(layers[Layer.REC] or layers[Layer.PRE]
                               or layers.get(Layer.DERIVED))
    return baseline

# --- reconciling ----------------------------------------------------------------

def reconcile(manager, old_base: Optional[EcucModuleConfiguration], new: ModuleBaseline,
              unlocked: Set[ValueKey], confirm: Optional[Confirm]) -> Tuple[MergeResult, bool]:
    """Merge Base, Base' and Active; apply the result only when the caller confirms.

    Args:
        manager: The module's ``ConfigurationManager``; its configuration is Active.
        old_base: The accepted snapshot, or ``None`` (first enable / a migrated project).
            It is flattened with the module name, like Base' and Active.
        new: The baseline composed from the package just now.
        unlocked: Pre keys the user unlocked (``ValueKey`` strings from
            ``ModuleEntry.pre_unlocked``); they merge like ordinary keys.
        confirm: Shown the markdown preview and the result; True applies the merge. ``None``
            rejects: nothing is written, and the result is still returned.

    Returns:
        ``(result, applied)``. ``applied`` is False when the merge changes nothing (the
        usual case — no preview is shown then) and when it was rejected.

    Raises:
        MergeApplyError: the merge cannot be applied consistently. That is a defect, not a
            user condition, so it propagates: the caller reports the module as failed
            rather than leaving a half-merged Active behind.
    """
    module_name = manager.module_def.short_name
    old = None if old_base is None else flatten(old_base, module_name)
    result = three_way_merge(old, flatten(new.base_config, module_name),
                             flatten(manager.configuration, module_name),
                             new.layers, unlocked)
    if not result.has_changes or confirm is None:
        return result, False
    if not confirm(result.to_markdown(module_name), result):
        return result, False

    apply_merge(manager.configuration, manager.module_def, new.base_config, result)
    project = getattr(manager, "project_context", None)
    if project is not None:
        _write_report(project, module_name, result)
    return result, True


def _write_report(project, module: str, result: MergeResult) -> None:
    """Write the applied merge's preview to ``<history>/reports`` (never fails the load)."""
    path = report_path(project, module)
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(result.to_markdown(module), encoding="utf-8")
    except OSError as exc:
        _log.warning("合并报告写入失败：%s（%s）", path, exc)


# --- adopting Base' into an empty Active ----------------------------------------

def adopt_base(manager, base_config: EcucModuleConfiguration) -> None:
    """Fill an empty Active from Base' (a newly added module: Active = Base', D8).

    The containers and values are cloned, so a later edit of Active cannot reach back into
    the baseline that is about to be written to disk.
    """
    config = manager.configuration
    config.containers.clear()
    config._instance_registry.clear()
    config.parameter_values.clear()
    for name, param in base_config.parameter_values.items():
        config.parameter_values[name] = EcucParameterValue(
            definition_ref=param.definition_ref, value=param.value,
            index=param.index, dest_type=param.dest_type)
    for container in base_config.containers:
        config.add_container(_clone_subtree(container, None, config.short_name))


# --- persistence of Base and its layers -----------------------------------------

def write_baseline(project, module: str, baseline: ModuleBaseline) -> Optional[str]:
    """Write ``baseline`` as the module's accepted Base; return its hash.

    The snapshot goes to :func:`base_snapshot_path`, the layers to :func:`base_layers_path`;
    the returned hash belongs in ``ModuleEntry.base_hash``. ``dirty`` is cleared.
    """
    from .store import write_base

    path = base_snapshot_path(project, module)
    path.parent.mkdir(parents=True, exist_ok=True)
    digest = write_base(path, baseline.base_config)
    write_layers(base_layers_path(project, module), baseline)
    baseline.dirty = False
    return digest


def write_layers(path: Path, baseline: ModuleBaseline) -> None:
    """Store the layers and the Pre ownership set of ``baseline`` as JSON.

    The values live in the snapshot; this file only says where each came from, so a later
    session can classify origins and lock Pre without recomputing Base' (which would
    relabel whatever Base' now says). Keys are sorted for a stable file.
    """
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    data = {
        "schema": 1,
        "module": baseline.module_name,
        "layers": {key: baseline.layers[key].name.lower() for key in sorted(baseline.layers)},
        "pre_keys": sorted(baseline.pre_keys),
        "has_layers": baseline.has_layers,
    }
    path.write_text(json.dumps(data, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def read_layers(path: Path) -> ModuleBaseline:
    """Read what :func:`write_layers` wrote; a missing or damaged file gives an empty one.

    The returned baseline has no ``base_config``: the snapshot holds the values and the
    caller attaches it. Unknown layer names are ignored, so a file written by a newer tool
    version still yields the layers this one understands.
    """
    path = Path(path)
    if not path.is_file():
        _log.warning("基线层文件不存在，来源按无基线处理：%s", path)
        return ModuleBaseline()
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as exc:
        _log.warning("基线层文件无法读取，来源按无基线处理：%s（%s）", path, exc)
        return ModuleBaseline()
    if not isinstance(data, dict):
        _log.warning("基线层文件格式不对，来源按无基线处理：%s", path)
        return ModuleBaseline()

    layers: Dict[ValueKey, Layer] = {}
    for key, name in sorted((data.get("layers") or {}).items()):
        layer = _LAYER_BY_NAME.get(str(name).lower())
        if layer is not None:
            layers[key] = layer
    pre_keys = {key for key in (data.get("pre_keys") or []) if isinstance(key, str)}
    pre_keys |= {key for key, layer in layers.items() if layer is Layer.PRE}
    has_layers = data.get("has_layers")
    if not isinstance(has_layers, bool):
        has_layers = any(layer is not Layer.DEFAULT for layer in layers.values())
    return ModuleBaseline(base_config=None, layers=layers, pre_keys=pre_keys,
                          module_name=data.get("module") or "", has_layers=has_layers)


def load_baseline(project, module: str, expected_hash: Optional[str]) -> ModuleBaseline:
    """Load the accepted Base of ``module``: its snapshot and the layers beside it.

    A missing snapshot, or one whose hash no longer matches ``expected_hash``, gives
    ``base_config=None`` (``store.read_base`` logs why) — the merge then treats the module
    as first enable. The layers file is read either way: it is what the Pre lock needs, and
    a snapshot restored from version control without it still locks the keys it names.
    """
    from .store import read_base

    layers = read_layers(base_layers_path(project, module))
    layers.base_config = read_base(base_snapshot_path(project, module), expected_hash)
    layers.module_name = layers.module_name or module
    return layers
