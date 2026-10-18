"""
ECU resource diagnostics

``ecu:get()`` on a key without a value silently yields an empty result, so a
chip that lacks a key produces plausible-looking but wrong code.  This module
reports

* keys referenced by the loaded modules' xdm files and templates that have no
  value (warning),
* keys that have a value but are referenced by nothing (information), and
* violations of a few declared consistency rules between related keys.

Diagnostics only report; they never block generation.  Only keys written as a
literal (``ecu:get('Os.Key')``) are found; keys built by string concatenation
are not scanned.
"""
import logging
import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Callable, Dict, Iterable, List, Optional, Set, Tuple

logger = logging.getLogger(__name__)

DYNAMIC_KEYS_NOTE = ("Keys built by string concatenation in templates are not scanned, "
                     "so 'unused' keys may in fact be referenced dynamically.")

_ECU_REF = re.compile(r"""ecu:(?:get|list)\s*\(\s*['"]([^'"]+)['"]\s*\)""")
_MAX_SCAN_BYTES = 2 * 1024 * 1024
_CORE_FORM = re.compile(r"^CORE\d+$")
_OS_CORE_ID_FORM = re.compile(r"^OS_CORE_ID_(\d+)$")


@dataclass
class EcuResourceReport:
    """Outcome of one diagnosis run."""
    missing: Dict[str, List[str]] = field(default_factory=dict)   # key -> referencing modules
    # Referenced, no value for the selected chip, but defined for other chips
    # (key -> those chips).  Usually the template guards the use with a chip
    # condition that a static scan cannot evaluate, so this is information only.
    chip_specific: Dict[str, List[str]] = field(default_factory=dict)
    unused: List[str] = field(default_factory=list)
    consistency: List[str] = field(default_factory=list)
    note: str = DYNAMIC_KEYS_NOTE

    @property
    def has_warnings(self) -> bool:
        return bool(self.missing or self.consistency)

    def warning_lines(self) -> List[str]:
        lines = [f"ECU resource '{key}' has no value (used by {', '.join(modules)})"
                 for key, modules in sorted(self.missing.items())]
        lines.extend(self.consistency)
        return lines

    def summary(self) -> str:
        return (f"ECU resources: {len(self.missing)} missing key(s), "
                f"{len(self.consistency)} consistency warning(s), "
                f"{len(self.chip_specific)} chip-specific key(s) not defined for this chip, "
                f"{len(self.unused)} unreferenced key(s)")


# --- reference scan -----------------------------------------------------------

def _read_text(path: Path) -> str:
    try:
        if path.stat().st_size > _MAX_SCAN_BYTES:
            return ""
        return path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return ""


def _files_under(directory: Path) -> Iterable[Path]:
    if directory.is_dir():
        for f in directory.rglob("*"):
            if f.is_file():
                yield f


def _module_sources(project, module: str, def_path: Path) -> List[Path]:
    """xdm and template files that belong to one module."""
    def_path = Path(def_path)
    files: List[Path] = []
    if def_path.suffix.lower() == ".xdm":
        files.append(def_path)
    plugin_dir = def_path.parent.parent
    files.extend(_files_under(plugin_dir / "generate_PB"))
    files.extend(_files_under(plugin_dir / "generate_PC"))
    project_path = getattr(project, "path", None)
    if project_path:
        project_path = Path(project_path)
        project_dir = project_path.parent if project_path.suffix == ".dpa" else project_path
        files.extend(_files_under(project_dir / "templates" / module))
    return files


def _collect(sources: Iterable[Tuple[str, List[Path]]]) -> Dict[str, Set[str]]:
    """Literal ``ecu:get/ecu:list`` keys of ``(module, files)`` pairs -> referencing modules."""
    referenced: Dict[str, Set[str]] = {}
    seen: Set[Tuple[str, Path]] = set()
    for module, files in sources:
        for f in files:
            resolved = f.resolve()
            if (module, resolved) in seen:
                continue
            seen.add((module, resolved))
            for key in _ECU_REF.findall(_read_text(f)):
                referenced.setdefault(key, set()).add(module)
    return referenced


def collect_referenced_keys(project) -> Dict[str, Set[str]]:
    """Map every literal ``ecu:get/ecu:list`` key to the modules referencing it."""
    return _collect(
        (module, _module_sources(project, module, def_path))
        for module, def_path in sorted(getattr(project, "module_defs", {}).items())
        if def_path
    )


def collect_referenced_keys_in_dirs(directories: Iterable[Path]) -> Dict[str, Set[str]]:
    """Same scan for plugin directories instead of a project.

    Every ``config/<Module>.xdm`` found under a directory marks a plugin; the
    plugin's xdm, ``generate_PB/`` and ``generate_PC/`` files belong to the
    module named like the xdm.
    """
    sources: List[Tuple[str, List[Path]]] = []
    for directory in directories:
        directory = Path(directory)
        if not directory.is_dir():
            continue
        for xdm in sorted(directory.rglob("*.xdm")):
            if xdm.parent.name.lower() != "config":
                continue
            sources.append((xdm.stem, _module_sources(None, xdm.stem, xdm)))
    return _collect(sources)


# --- consistency rules --------------------------------------------------------

def _as_list(value: Any) -> List[Any]:
    if value is None:
        return []
    return list(value) if isinstance(value, list) else [value]


def _count_rule(num_key: str, list_key: str) -> Callable[[Dict[str, Any]], List[str]]:
    def check(res: Dict[str, Any]) -> List[str]:
        if num_key not in res or list_key not in res:
            return []
        num, items = res[num_key], _as_list(res[list_key])
        if isinstance(num, bool) or not isinstance(num, int) or num == len(items):
            return []
        return [f"{num_key} is {num} but {list_key} has {len(items)} element(s): {items}"]
    return check


def _master_core_rule(master_key: str, cores_key: str,
                      os_macro_form: bool = False) -> Callable[[Dict[str, Any]], List[str]]:
    """The master core must be one of the available cores.

    ``os_macro_form`` selects the notation: ``OS_CORE_ID_<n>`` for the Os module,
    whose templates emit the value verbatim as a C macro name (so ``CORE0`` would
    be an undefined identifier there), or ``CORE<n>`` for the Resource module.
    """
    def check(res: Dict[str, Any]) -> List[str]:
        if master_key not in res or cores_key not in res:
            return []
        cores = [str(c) for c in _as_list(res[cores_key])]
        messages: List[str] = []
        for master in (str(m) for m in _as_list(res[master_key])):
            if os_macro_form:
                m = _OS_CORE_ID_FORM.match(master)
                if not m:
                    messages.append(
                        f"{master_key} value '{master}' is not in OS_CORE_ID_<n> form "
                        f"(the Os templates emit it verbatim as a C macro name)")
                    continue
                core_name = f"CORE{int(m.group(1))}"
            else:
                if not _CORE_FORM.match(master):
                    messages.append(f"{master_key} value '{master}' is not in CORE<n> form")
                    continue
                core_name = master
            if core_name not in cores:
                messages.append(f"{master_key} value '{master}' is not one of "
                                f"{cores_key}: {cores}")
        return messages
    return check


# Declared as a table so a new rule needs no change to the diagnosis flow.
CONSISTENCY_RULES: List[Callable[[Dict[str, Any]], List[str]]] = [
    _count_rule("OsResource.NumOfCores", "OsResource.AvailableCores"),
    _count_rule("Resource.NumOfCores", "Resource.AvailableCores"),
    _count_rule("Os.IocPrimitiveDataTypeNum", "Os.IocPrimitiveDataType"),
    _master_core_rule("OsResource.MasterCore", "OsResource.AvailableCores", os_macro_form=True),
    _master_core_rule("Resource.MasterCore", "Resource.AvailableCores"),
]


def check_consistency(resources: Dict[str, Any]) -> List[str]:
    messages: List[str] = []
    for rule in CONSISTENCY_RULES:
        messages.extend(rule(resources))
    return messages


# --- diagnosis ----------------------------------------------------------------

def diagnose(project, resources: Optional[Dict[str, Any]] = None,
             other_chip_keys: Optional[Dict[str, List[str]]] = None,
             log: bool = True) -> EcuResourceReport:
    """Compare the keys the loaded modules reference with ``resources``.

    Args:
        other_chip_keys: lower-cased key -> chips that define it, for every chip
            except the selected one.  A referenced key found there is reported
            as chip-specific information instead of a missing-key warning.
        log: write the warnings and the summary to the log
    """
    if resources is None:
        resources = getattr(project, "ecu_resources", {}) or {}

    referenced = collect_referenced_keys(project)
    have = {k.lower() for k in resources}          # ecu:get() matches case-insensitively
    wanted = {k.lower() for k in referenced}

    report = EcuResourceReport()
    other_chip_keys = other_chip_keys or {}
    for key, modules in referenced.items():
        if key.lower() in have:
            continue
        if key.lower() in other_chip_keys:
            report.chip_specific[key] = sorted(other_chip_keys[key.lower()])
        else:
            report.missing[key] = sorted(modules)
    report.unused = sorted(k for k in resources if k.lower() not in wanted)
    report.consistency = check_consistency(resources)

    if log:
        log_report(report)
    return report


def log_report(report: EcuResourceReport) -> None:
    """Write a report to the log: warnings, chip-specific notes, summary."""
    for line in report.warning_lines():
        logger.warning(line)
    for key, chips in sorted(report.chip_specific.items()):
        logger.info("ECU resource '%s' is not defined for this chip (defined for: %s); "
                    "it is probably used only under a chip condition", key, ", ".join(chips))
    logger.info(report.summary())


def _find_parameter_values(containers, name: str) -> List[Any]:
    """Configured values of every parameter called ``name`` in a container tree."""
    found: List[Any] = []
    for container in containers or []:
        param = container.parameter_values.get(name)
        if param is not None and getattr(param, "value", None) not in (None, ""):
            found.append(param.value)
        found.extend(_find_parameter_values(getattr(container, "sub_containers", []), name))
    return found


def check_selectors(project, chip) -> List[str]:
    """Selector parameters configured differently from what the selected chip declares.

    Only reports; the configuration is the user's and is never changed here.
    """
    if chip is None or not getattr(chip, "selectors", None):
        return []
    messages: List[str] = []
    managers = getattr(project, "module_managers", {}) or {}
    for key, declared in sorted(chip.selectors.items()):
        module, _, param = key.partition(".")
        manager = managers.get(module)
        configuration = getattr(manager, "configuration", None) if manager else None
        if configuration is None:
            continue
        for value in _find_parameter_values(configuration.containers, param):
            if str(value) != declared:
                messages.append(f"{key} is configured as '{value}' but the selected chip "
                                f"{chip.name} declares '{declared}'")
    return messages


# --- typed designer fields vs ecu_resources (ecu_resources prevails) -----------

def _os_core_to_core(value: Any) -> Any:
    m = _OS_CORE_ID_FORM.match(str(value))
    return f"CORE{int(m.group(1))}" if m else value


def _first(value: Any) -> Any:
    return value[0] if isinstance(value, list) and value else value


# typed field -> [(ecu_resources key, function giving the comparable value)]
TYPED_FIELD_MAP = {
    "metadata.cores.count": [("OsResource.NumOfCores", lambda v: v),
                             ("Resource.NumOfCores", lambda v: v)],
    "metadata.cores.available": [("OsResource.AvailableCores", lambda v: [str(x) for x in _as_list(v)]),
                                 ("Resource.AvailableCores", lambda v: [str(x) for x in _as_list(v)])],
    "metadata.cores.master": [("Resource.MasterCore", lambda v: str(_first(v))),
                              ("OsResource.MasterCore", lambda v: str(_os_core_to_core(v)))],
}


def _typed_value(chip, field_path: str) -> Any:
    cores = (getattr(chip, "metadata", None) or {}).get("cores") or {}
    leaf = field_path.rsplit(".", 1)[-1]
    if leaf not in cores:
        return None
    value = cores[leaf]
    if leaf == "available":
        return [str(x) for x in _as_list(value)]
    if leaf == "master":
        return str(value)
    return value


def typed_field_differences(chip) -> List[str]:
    """Differences between the designer's typed fields and ``ecu_resources``.

    Compared only where ``ecu_resources`` has the mapped key; ``ecu_resources``
    is the data templates read, so it is the one that counts.
    """
    from .ecu_resource_data import flatten_ecu_resources

    flat = flatten_ecu_resources(getattr(chip, "ecu_resources", {}) or {})
    messages: List[str] = []
    for field_path, keys in TYPED_FIELD_MAP.items():
        typed = _typed_value(chip, field_path)
        if typed is None:
            continue
        for key, convert in keys:
            if key not in flat:
                continue
            ecu_value = convert(flat[key])
            if ecu_value != typed:
                messages.append(f"{field_path} is {typed!r} but ECU resource {key} gives {ecu_value!r}")
    return messages


def typed_fields_from_ecu(chip) -> Dict[str, Any]:
    """Values for the typed core fields taken from ``ecu_resources`` (only where a key exists)."""
    from .ecu_resource_data import flatten_ecu_resources

    flat = flatten_ecu_resources(getattr(chip, "ecu_resources", {}) or {})
    result: Dict[str, Any] = {}
    for field_path, keys in TYPED_FIELD_MAP.items():
        for key, convert in keys:
            if key in flat:
                result[field_path.rsplit(".", 1)[-1]] = convert(flat[key])
                break
    return result
