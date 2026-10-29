"""
Repair of an existing chip (add-chip-repair-core)

``ecu_resources`` is the authority of a chip's data; ``resources``,
``metadata.cores`` and ``ports`` are views derived from it.  A repair takes a
source (vendor .properties, keys the modules reference), shows the difference
per flat key, applies only the selected changes, synchronizes the views,
confirms or adds unconfirmed marks, and saves the chip with a backup and an
entry in ``history/<name>.yaml`` next to the chip files.

Every function returns a new chip; its input is never changed.  Missing or
unconfirmed data is marked, never removed, and a repair never renames a chip.
"""
import copy
import datetime
import getpass
import logging
import shutil
import subprocess
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Tuple

import yaml

from .chip_completeness import unconfirmed_marks
from .chip_database import ChipDatabase, ChipDefinition, ecu_resources_from_properties
from .ecu_resource_data import PLACEHOLDER, EcuResources, delete_entry, flatten_ecu_resources

logger = logging.getLogger(__name__)

ADDED, REMOVED, CHANGED = "added", "removed", "changed"
UNCHANGED, UPDATED, NOT_DERIVED = "unchanged", "updated", "not derived"
HISTORY_DIR = "history"
# Note of the unconfirmed mark of an entry added without a value because the modules
# reference its key; an empty value read from a vendor file is data and not marked.
TO_FILL_IN = "待填写"
FILLED_NOTE, GONE_NOTE = "已填写", "条目已删除"     # history notes of a mark removed automatically
_ECU_FIELD = "ecu_resources."

__all__ = [
    "ADDED", "REMOVED", "CHANGED", "UNCHANGED", "UPDATED", "NOT_DERIVED", "TO_FILL_IN",
    "PLACEHOLDER", "view_text", "KeyChange", "EcuDiff", "ViewStatus", "RepairRecord", "SaveResult", "ChipFileChanged",
    "ecu_resources_from_properties", "diff_ecu_resources", "diff_from_source", "missing_key_changes",
    "apply_changes", "derive_views", "confirm_fields", "mark_unconfirmed",
    "mark_to_fill_in", "drop_filled_marks", "to_fill_in_keys",
    "next_version", "git_author", "history_path", "save_repaired_chip", "read_history", "RepairSession",
]


# --- difference -------------------------------------------------------------------

@dataclass(frozen=True)
class KeyChange:
    key: str                # flat key "<module>.<name>"
    kind: str               # ADDED, REMOVED or CHANGED
    old: Any = None
    new: Any = None
    type_only: bool = False     # CHANGED only: same text, different type (1 vs "1")
    to_fill_in: bool = False    # ADDED only: referenced by the modules, no value from any source


@dataclass
class EcuDiff:
    changes: List[KeyChange] = field(default_factory=list)     # ordered by key

    def __bool__(self) -> bool:
        return bool(self.changes)

    def keys(self, *kinds: str) -> List[str]:
        """Keys of the changes, of the given kinds only when kinds are given."""
        return [c.key for c in self.changes if not kinds or c.kind in kinds]

    def get(self, key: str) -> Optional[KeyChange]:
        return next((c for c in self.changes if c.key == key), None)


def _same(a: Any, b: Any) -> bool:
    """Equal value and type; lists item by item (True != 1, 1 != 1.0, 1 != "1")."""
    if isinstance(a, list) or isinstance(b, list):
        return (isinstance(a, list) and isinstance(b, list) and len(a) == len(b)
                and all(_same(x, y) for x, y in zip(a, b)))
    return type(a) is type(b) and a == b


def _text(value: Any) -> Any:
    return [str(v) for v in value] if isinstance(value, list) else str(value)


def diff_ecu_resources(old: EcuResources, new: EcuResources) -> EcuDiff:
    """Per flat key: added, removed or changed between ``old`` and ``new``, ordered by key.

    Both sides are loaded chips or parsed .properties, so range notation is already
    expanded; values of different types differ (``ecu:get`` returns them differently).
    """
    flat_old, flat_new = flatten_ecu_resources(old or {}), flatten_ecu_resources(new or {})
    changes: List[KeyChange] = []
    for key in sorted(set(flat_old) | set(flat_new)):
        if key not in flat_old:
            changes.append(KeyChange(key, ADDED, new=flat_new[key]))
        elif key not in flat_new:
            changes.append(KeyChange(key, REMOVED, old=flat_old[key]))
        elif not _same(flat_old[key], flat_new[key]):
            a, b = flat_old[key], flat_new[key]
            changes.append(KeyChange(key, CHANGED, old=a, new=b, type_only=_text(a) == _text(b)))
    return EcuDiff(changes)


def diff_from_source(current: EcuResources, source: EcuResources) -> EcuDiff:
    """Difference to a partial source: only the modules the source has are compared,
    so a Port-only file does not report every other module as removed."""
    return diff_ecu_resources({m: e for m, e in (current or {}).items() if m in source}, source)


def missing_key_changes(chip: ChipDefinition, referenced_keys: Iterable[str]) -> EcuDiff:
    """Keys the modules reference but the chip lacks, as added entries still to fill in."""
    flat = flatten_ecu_resources(chip.ecu_resources)
    changes = []
    for key in sorted(set(referenced_keys)):
        if "." not in key:
            logger.warning("referenced ECU resource key '%s' has no module prefix and is skipped", key)
        elif key not in flat:
            changes.append(KeyChange(key, ADDED, new=PLACEHOLDER, to_fill_in=True))
    return EcuDiff(changes)


# --- merge ------------------------------------------------------------------------

def apply_changes(chip: ChipDefinition, diff: EcuDiff, selected_keys: Iterable[str]) -> ChipDefinition:
    """A copy of ``chip`` with only the selected changes of ``diff`` applied.

    Removals happen only when selected.  Existing keys keep their position; added
    keys go to the end of their module in key order, new modules to the end.

    Raises:
        ValueError: a selected key is not in ``diff``
    """
    selected = set(selected_keys)
    unknown = sorted(selected - set(diff.keys()))
    if unknown:
        raise ValueError(f"not in the difference: {', '.join(unknown)}")

    result = copy.deepcopy(chip)
    resources = result.ecu_resources
    for change in diff.changes:         # ordered by key, so appended keys are too
        if change.key not in selected:
            continue
        module, name = change.key.split(".", 1)
        if change.kind == REMOVED:
            delete_entry(resources, module, name)
        else:
            resources.setdefault(module, {})[name] = copy.deepcopy(change.new)
    return result


# --- views ------------------------------------------------------------------------

@dataclass(frozen=True)
class ViewStatus:
    view: str       # "resources", "metadata.cores" or "ports"
    state: str      # UNCHANGED, UPDATED or NOT_DERIVED
    detail: str = ""


def view_text(status: ViewStatus) -> str:
    """``updated: can_controller 6→12`` / ``unchanged``."""
    return f"{status.state}: {status.detail}" if status.detail else status.state


def _instances_key(instances) -> List[Tuple[Any, ...]]:
    return [(r.resource_id, r.display_name, r.properties) for r in instances]


def _derive_resources(chip: ChipDefinition) -> ViewStatus:
    from .ecu_resource_diagnostics import peripherals_from_ecu

    derived = peripherals_from_ecu(chip.ecu_resources)
    if not derived:
        return ViewStatus("resources", NOT_DERIVED, "ECU 资源中没有可推导的外设")
    current = chip.effective_resources()
    changed = []
    for res_type, instances in derived.items():
        before = current.get(res_type, [])
        if _instances_key(before) != _instances_key(instances):
            changed.append(f"{res_type} {len(before)}→{len(instances)}")
        current[res_type] = instances
    chip.resources = current
    chip.can_resources, chip.adc_resources, chip.spi_resources, chip.intc_sources = [], [], [], []
    if not changed:
        return ViewStatus("resources", UNCHANGED)
    return ViewStatus("resources", UPDATED, ", ".join(changed))


def _derive_cores(chip: ChipDefinition) -> ViewStatus:
    """Core fields from their ECU resource keys; a field already agreeing with one of
    its keys is kept, since MCAL may count lockstep cores that the Os does not use
    (THA610X: ``Resource.NumOfCores`` 2, ``OsResource.NumOfCores`` 1)."""
    from .ecu_resource_diagnostics import TYPED_FIELD_MAP, _typed_value

    flat = flatten_ecu_resources(chip.ecu_resources)
    cores = dict(chip.metadata.get("cores") or {})
    found, changed = False, []
    for field_path, keys in TYPED_FIELD_MAP.items():
        candidates = [convert(flat[key]) for key, convert in keys if key in flat]
        if not candidates:
            continue
        found = True
        if _typed_value(chip, field_path) in candidates:
            continue
        leaf = field_path.rsplit(".", 1)[-1]
        changed.append(f"{leaf} {cores.get(leaf)!r}→{candidates[0]!r}")
        cores[leaf] = candidates[0]
    if not found:
        return ViewStatus("metadata.cores", NOT_DERIVED, "ECU 资源中没有核数、可用核或主核的键")
    chip.metadata["cores"] = cores
    if not changed:
        return ViewStatus("metadata.cores", UNCHANGED)
    return ViewStatus("metadata.cores", UPDATED, ", ".join(changed))


def _derive_ports(chip: ChipDefinition) -> ViewStatus:
    from . import ecu_resource_diagnostics

    ports_from_ecu = getattr(ecu_resource_diagnostics, "ports_from_ecu", None)
    if ports_from_ecu is None:
        return ViewStatus("ports", NOT_DERIVED, "尚无引脚表推导，见 add-chip-ports-from-ecu-resources")
    ports = ports_from_ecu(chip.ecu_resources)
    if not ports:
        return ViewStatus("ports", NOT_DERIVED, "ECU 资源中没有 Port 数据")
    if ports == chip.ports:
        return ViewStatus("ports", UNCHANGED)
    before = sum(len(p) for p in chip.ports.values())
    after = sum(len(p) for p in ports.values())
    chip.ports = ports
    return ViewStatus("ports", UPDATED, f"{len(chip.ports)} 个端口，引脚 {before}→{after}")


def derive_views(chip: ChipDefinition) -> Tuple[ChipDefinition, List[ViewStatus]]:
    """A copy of ``chip`` whose views are rebuilt from its ECU resources, and a status per view.

    Peripheral types that can be derived replace the chip's instances of that type
    (other types are kept); core fields are replaced only where the ECU resources
    have their key; the pin table only when it can be derived.
    """
    result = copy.deepcopy(chip)
    return result, [_derive_resources(result), _derive_cores(result), _derive_ports(result)]


# --- unconfirmed marks -----------------------------------------------------------

def _set_marks(chip: ChipDefinition, marks: Dict[str, str]) -> None:
    if marks:
        chip.metadata["unconfirmed"] = marks
    else:
        chip.metadata.pop("unconfirmed", None)


def confirm_fields(chip: ChipDefinition, fields: Iterable[str]) -> ChipDefinition:
    """A copy of ``chip`` without the marks of ``fields``; the marked data is unchanged.

    The confirmation notes belong to the repair history (``RepairRecord.confirm_notes``).

    Raises:
        ValueError: a field is not marked
    """
    marks = unconfirmed_marks(chip)
    fields = list(fields)
    unknown = [f for f in fields if f not in marks]
    if unknown:
        raise ValueError(f"not marked as unconfirmed: {', '.join(unknown)}")
    result = copy.deepcopy(chip)
    _set_marks(result, {f: n for f, n in marks.items() if f not in fields})
    return result


def mark_unconfirmed(chip: ChipDefinition, field_path: str, note: str = "") -> ChipDefinition:
    """A copy of ``chip`` with ``field_path`` marked as unconfirmed (an existing mark gets the new note)."""
    result = copy.deepcopy(chip)
    marks = unconfirmed_marks(result)
    marks[field_path] = note
    _set_marks(result, marks)
    return result


def _entry_key(field_path: str) -> Optional[str]:
    """``ecu_resources.Os.Key`` -> ``Os.Key``; None for any other field (``ecu_resources.Os`` too)."""
    if not field_path.startswith(_ECU_FIELD):
        return None
    key = field_path[len(_ECU_FIELD):]
    return key if "." in key else None


def mark_to_fill_in(chip: ChipDefinition, keys: Iterable[str]) -> ChipDefinition:
    """A copy of ``chip`` whose entries of ``keys`` still without a value are marked ``待填写``.

    An entry that has a value, is absent or is already marked keeps its marks.
    """
    flat = flatten_ecu_resources(chip.ecu_resources)
    result = copy.deepcopy(chip)
    marks = unconfirmed_marks(result)
    for key in keys:
        if key in flat and flat[key] is PLACEHOLDER:
            marks.setdefault(_ECU_FIELD + key, TO_FILL_IN)
    _set_marks(result, marks)
    return result


def drop_filled_marks(chip: ChipDefinition) -> ChipDefinition:
    """A copy of ``chip`` without the ``待填写`` marks of entries that have a value or are gone.

    Marks with any other note stay: only a person confirms them.
    """
    flat = flatten_ecu_resources(chip.ecu_resources)

    def done(field_path: str, note: str) -> bool:
        key = _entry_key(field_path)
        return note == TO_FILL_IN and key is not None and (key not in flat or flat[key] is not PLACEHOLDER)

    result = copy.deepcopy(chip)
    _set_marks(result, {f: n for f, n in unconfirmed_marks(result).items() if not done(f, n)})
    return result


def to_fill_in_keys(chip) -> List[str]:
    """Flat keys of the entries marked ``待填写`` that still have no value, in key order."""
    flat = flatten_ecu_resources(getattr(chip, "ecu_resources", None) or {})
    keys = (_entry_key(f) for f, n in unconfirmed_marks(chip).items() if n == TO_FILL_IN)
    return sorted(k for k in keys if k and k in flat and flat[k] is PLACEHOLDER)


# --- saving -----------------------------------------------------------------------

class ChipFileChanged(Exception):
    """The chip file is missing or no longer holds the chip the repair started from."""


@dataclass
class RepairRecord:
    source: str                         # e.g. "MCAL R440 CotexR52_THA6412_BGA516.properties"
    note: str = ""
    author: str = ""                    # empty: git config user.name, else the OS user
    version: str = ""                   # new resource_version; empty: next_version()
    views: List[ViewStatus] = field(default_factory=list)
    confirm_notes: Dict[str, str] = field(default_factory=dict)    # field -> confirmation note


@dataclass
class SaveResult:
    saved: bool                 # False: the chip equals the one it was repaired from
    path: Path
    backup: Optional[Path] = None
    history: Optional[Path] = None
    version: str = ""
    checksum: str = ""


def next_version(old: str) -> str:
    """``1.0.0`` -> ``1.0.1``; a non-numeric last part gets ``.1`` appended; empty -> ``1.0.0``."""
    if not old:
        return "1.0.0"
    parts = old.split(".")
    if parts[-1].isdigit():
        parts[-1] = str(int(parts[-1]) + 1)
    else:
        parts.append("1")
    return ".".join(parts)


def git_author(cwd: Optional[Path] = None) -> str:
    """``git config user.name`` (seen from ``cwd``), else the OS user name."""
    try:
        out = subprocess.run(["git", "config", "user.name"], cwd=cwd, capture_output=True,
                             text=True, timeout=5, check=False)
        name = out.stdout.strip()
        if out.returncode == 0 and name:
            return name
    except (OSError, subprocess.SubprocessError) as e:
        logger.debug("git config user.name failed: %s", e)
    return getpass.getuser()


def history_path(chip_file: Path) -> Path:
    """Repair history of a chip file: ``<dir>/history/<name>.yaml`` (not scanned by the library)."""
    return chip_file.parent / HISTORY_DIR / chip_file.name


def _history_entry(base: ChipDefinition, saved: ChipDefinition, record: RepairRecord,
                   author: str, checksum: str) -> Dict[str, Any]:
    diff = diff_ecu_resources(base.ecu_resources, saved.ecu_resources)
    ecu: Dict[str, List[Dict[str, Any]]] = {ADDED: [], CHANGED: [], REMOVED: []}
    for c in diff.changes:
        entry: Dict[str, Any] = {"key": c.key}
        if c.kind != ADDED:
            entry["old"] = c.old
        if c.kind != REMOVED:
            entry["new"] = c.new
        ecu[c.kind].append(entry)
    before, after = unconfirmed_marks(base), unconfirmed_marks(saved)
    flat_saved = flatten_ecu_resources(saved.ecu_resources)

    def confirm_note(field_path: str) -> str:
        if field_path in record.confirm_notes or before[field_path] != TO_FILL_IN:
            return record.confirm_notes.get(field_path, "")
        return FILLED_NOTE if _entry_key(field_path) in flat_saved else GONE_NOTE

    return {
        "date": datetime.date.today().isoformat(),
        "author": author,
        "source": record.source,
        "note": record.note,
        "resource_version": {"old": base.resource_version, "new": saved.resource_version},
        "base_modified_outside": bool(base.content_modified),
        "ecu_resources": ecu,
        "views": {v.view: view_text(v) for v in record.views},
        "confirmed": [{"field": f, "note": confirm_note(f)} for f in before if f not in after],
        "marked": [{"field": f, "note": n} for f, n in after.items() if before.get(f) != n],
        "checksum": checksum,
    }


def _append_history(path: Path, chip_name: str, entry: Dict[str, Any]) -> None:
    from .chip_exporter import _atomic_write_text

    data: Dict[str, Any] = {}
    if path.exists():
        data = yaml.safe_load(path.read_text(encoding="utf-8")) or {}
    entries = list(data.get("entries") or [])
    entries.append(entry)
    text = yaml.safe_dump({"chip": chip_name, "entries": entries}, sort_keys=False,
                          allow_unicode=True, default_flow_style=None, width=4096)
    path.parent.mkdir(parents=True, exist_ok=True)
    _atomic_write_text(path, text)


def save_repaired_chip(database: ChipDatabase, chip: ChipDefinition, base: ChipDefinition,
                       record: RepairRecord, path: Optional[Path] = None) -> SaveResult:
    """Write ``chip``, repaired from ``base``, over ``base``'s file in the library.

    The previous file is kept as ``<name>.yaml.bak``, ``resource_version`` and the
    checksum are renewed, one entry is appended to the repair history, and the
    library returns the new chip.  Nothing is written when ``chip`` equals ``base``.

    Raises:
        ValueError: the chip was renamed, or the library has no directory
        ChipFileChanged: the file is missing or changed since ``base`` was loaded
    """
    from .chip_exporter import ChipDefinitionExporter, chip_checksum

    if chip.name != base.name:
        raise ValueError(f"a repair does not rename a chip ({base.name} -> {chip.name}); "
                         "save it as a new chip instead")
    if path is None:
        if database.data_dir is None:
            raise ValueError("the chip library has no directory to save into")
        path = Path(database.data_dir) / f"{chip.name}.yaml"
    path = Path(path)
    if not path.exists():
        raise ChipFileChanged(f"{path} does not exist")
    on_disk = ChipDatabase()._load_chip_from_yaml(path)
    if on_disk is None or chip_checksum(on_disk) != chip_checksum(base):
        raise ChipFileChanged(f"{path} has changed since {base.name} was loaded for repair; "
                              "load it again and repeat the repair")

    if chip_checksum(chip) == chip_checksum(base):
        return SaveResult(saved=False, path=path, version=base.resource_version,
                          checksum=chip_checksum(base))

    saved = copy.deepcopy(chip)
    saved.resource_version = record.version or next_version(base.resource_version)
    saved.checksum = chip_checksum(saved)
    saved.content_modified = False

    backup = path.with_name(path.name + ".bak")
    shutil.copy2(path, backup)
    ChipDefinitionExporter().save_yaml(saved, path)

    author = record.author or git_author(path.parent)
    hist = history_path(path)
    _append_history(hist, saved.name, _history_entry(base, saved, record, author, saved.checksum))

    database.register_chip(copy.deepcopy(saved))
    logger.info("repaired chip %s saved to %s (resource_version %s)", saved.name, path, saved.resource_version)
    return SaveResult(saved=True, path=path, backup=backup, history=hist,
                      version=saved.resource_version, checksum=saved.checksum)


def read_history(chip_file: Path) -> List[Dict[str, Any]]:
    """Entries of a chip's repair history, oldest first (empty without a history)."""
    path = history_path(Path(chip_file))
    if not path.is_file():
        return []
    try:
        return list((yaml.safe_load(path.read_text(encoding="utf-8")) or {}).get("entries") or [])
    except (OSError, yaml.YAMLError) as e:
        logger.warning("%s: cannot read the repair history: %s", path, e)
        return []


# --- session (state shared by the steps of the repair wizard and the command line) --

class RepairSession:
    """One repair of one library chip: sources, selection, marks, then build and save.

    Holds no Qt object, so the repair wizard's logic is testable without a display.
    """

    def __init__(self, database: ChipDatabase, chip_name: str, project=None):
        chip = database.get_chip(chip_name)
        if chip is None:
            raise ValueError(f"the chip library has no chip {chip_name}")
        self.database = database
        self.project = project
        self.base = copy.deepcopy(chip)
        self.properties: List[Path] = []
        self.scan_project = False
        self.scan_dirs: List[Path] = []
        self.diff = EcuDiff()
        self.selected: set = set()
        self.confirm_notes: Dict[str, str] = {}     # field -> confirmation note
        self.new_marks: Dict[str, str] = {}         # field -> note

    @property
    def chip_file(self) -> Optional[Path]:
        data_dir = self.database.data_dir
        return None if data_dir is None else Path(data_dir) / f"{self.base.name}.yaml"

    def load_sources(self) -> EcuDiff:
        """Difference to the chosen sources; the selection is reset to the default.

        A key both in a .properties file and among the missing keys takes the file's value.
        """
        from .ecu_resource_diagnostics import collect_referenced_keys, collect_referenced_keys_in_dirs

        changes: Dict[str, KeyChange] = {}
        if self.properties:
            source = ecu_resources_from_properties([Path(p) for p in self.properties])
            changes.update((c.key, c) for c in diff_from_source(self.base.ecu_resources, source).changes)
        referenced = set()
        if self.scan_project and self.project is not None:
            referenced |= set(collect_referenced_keys(self.project))
        if self.scan_dirs:
            referenced |= set(collect_referenced_keys_in_dirs([Path(d) for d in self.scan_dirs]))
        for c in missing_key_changes(self.base, referenced).changes:
            changes.setdefault(c.key, c)
        self.diff = EcuDiff([changes[k] for k in sorted(changes)])
        self.selected = set(self.default_selection())
        return self.diff

    def default_selection(self) -> List[str]:
        """Added and changed keys; removals and entries still to fill in are never preselected."""
        return [c.key for c in self.diff.changes if c.kind in (ADDED, CHANGED) and not c.to_fill_in]

    def build(self) -> Tuple[ChipDefinition, List[ViewStatus]]:
        """The repaired chip: selected changes (entries to fill in marked), views from
        ECU resources, then the marks; ``待填写`` marks of filled entries go last, so a
        confirmation of the base chip's marks never meets a mark already removed."""
        chip = apply_changes(self.base, self.diff, self.selected)
        chip = mark_to_fill_in(chip, [c.key for c in self.diff.changes if c.to_fill_in and c.key in self.selected])
        chip, views = derive_views(chip)
        if self.confirm_notes:
            chip = confirm_fields(chip, self.confirm_notes)
        for field_path, note in self.new_marks.items():
            chip = mark_unconfirmed(chip, field_path, note)
        return drop_filled_marks(chip), views

    def added_to_fill_in(self, chip: ChipDefinition) -> List[str]:
        """Entries of ``chip`` still to fill in that the base chip did not have, in key order."""
        before = set(to_fill_in_keys(self.base))
        return [k for k in to_fill_in_keys(chip) if k not in before]

    def completeness(self, chip: ChipDefinition) -> list:
        from .chip_completeness import check_chip

        return check_chip(chip, self.project)

    def completeness_change(self, chip: ChipDefinition) -> Tuple[list, list, list]:
        """(resolved, remaining, new) completeness items of ``chip`` against the base chip."""
        before, after = self.completeness(self.base), self.completeness(chip)
        before_fields, after_fields = {i.field for i in before}, {i.field for i in after}
        return ([i for i in before if i.field not in after_fields],
                [i for i in after if i.field in before_fields],
                [i for i in after if i.field not in before_fields])

    def has_changes(self, chip: ChipDefinition) -> bool:
        from .chip_exporter import chip_checksum

        return chip_checksum(chip) != chip_checksum(self.base)

    def save(self, record: RepairRecord) -> SaveResult:
        chip, views = self.build()
        if not record.views:
            record.views = views
        record.confirm_notes = dict(self.confirm_notes)
        return save_repaired_chip(self.database, chip, self.base, record)
