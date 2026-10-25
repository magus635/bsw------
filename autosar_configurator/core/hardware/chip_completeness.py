"""
Chip data completeness (add-sc300-chip)

Incomplete chip data is flagged, never removed: nothing here changes a chip or its
file, and a flagged chip stays selectable.  A chip is reported when:

* its YAML lists fields under ``metadata.unconfirmed`` (field -> note, or a list
  of fields), e.g. data copied from another chip that its owner still has to check;
* a declared selector value is not a declared value of that parameter in the
  loaded definition (the selector would be skipped when the chip is applied);
* it declares an Os selector but has no Os resources: no ``Os`` / ``OsResource``
  section in ``ecu_resources`` and no resource file registered in the Os
  plugin's ``plugin.xml``;
* ``metadata.cores.count`` matches neither ``OsResource.NumOfCores`` nor
  ``Resource.NumOfCores`` (only the keys the chip has are compared; one match is
  enough, since MCAL may count lockstep cores that the Os does not use).

Pins and peripherals are not required: a chip that runs the Os only (SC300) has
none, and that is not missing data.
"""
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional

from .ecu_resource_data import flatten_ecu_resources

INCOMPLETE_SUFFIX = "（资料不完整）"
OS_RESOURCE_MODULES = ("Os", "OsResource")
CORE_COUNT_KEYS = ("OsResource.NumOfCores", "Resource.NumOfCores")


@dataclass(frozen=True)
class CompletenessItem:
    field: str      # e.g. "metadata.flash_size", "selectors.Os.OsResourceSubderivative"
    text: str       # what is missing or unconfirmed, for the user


def unconfirmed_fields(chip) -> List[CompletenessItem]:
    """The fields the chip YAML marks as unconfirmed, in the order written."""
    marked = (getattr(chip, "metadata", None) or {}).get("unconfirmed") or {}
    if isinstance(marked, dict):
        pairs = [(str(k), "" if v is None else str(v)) for k, v in marked.items()]
    elif isinstance(marked, (list, tuple)):
        pairs = [(str(k), "") for k in marked]
    else:
        pairs = [(str(marked), "")]
    return [CompletenessItem(f, f"{f} 待确认" + (f"：{note}" if note else "")) for f, note in pairs]


def plugin_entries(project) -> List[Any]:
    """``ecuresource`` entries of the plugin.xml next to each loaded module definition."""
    from .chip_dependency_scan import read_plugin_xml

    seen = {}
    for def_path in (getattr(project, "module_defs", {}) or {}).values():
        if def_path:
            candidate = Path(def_path).parent.parent / "plugin.xml"
            if candidate.is_file():
                seen.setdefault(candidate.resolve(), candidate)
    return [e for p in sorted(seen) for e in read_plugin_xml(seen[p])]


def _selector_items(chip, project) -> List[CompletenessItem]:
    from .chip_dependency_scan import selector_values

    items = []
    for key, value in sorted((getattr(chip, "selectors", None) or {}).items()):
        allowed = selector_values(project, key)
        if allowed and value not in allowed:
            items.append(CompletenessItem(
                f"selectors.{key}",
                f"{key} = {value} 不在模块定义的取值范围内（{', '.join(allowed)}），切换芯片时不会写入"))
    return items


def _os_resource_items(chip, entries: Iterable[Any]) -> List[CompletenessItem]:
    selectors = getattr(chip, "selectors", None) or {}
    os_values = sorted(v for k, v in selectors.items() if k.split(".", 1)[0] == "Os")
    if not os_values:
        return []
    resources = getattr(chip, "ecu_resources", None) or {}
    if any(resources.get(m) for m in OS_RESOURCE_MODULES):
        return []
    registered = {e.subderivative for e in entries}
    return [CompletenessItem(
        "ecu_resources.Os",
        f"声明了 Os 选择器 {value}，但芯片没有 Os 资源，Os 插件也没有为它登记资源文件")
        for value in os_values if value not in registered]


def _core_count_items(chip) -> List[CompletenessItem]:
    cores = (getattr(chip, "metadata", None) or {}).get("cores") or {}
    if "count" not in cores:
        return []
    flat = flatten_ecu_resources(getattr(chip, "ecu_resources", None) or {})
    present = {k: flat[k] for k in CORE_COUNT_KEYS if k in flat}
    if not present or any(str(v) == str(cores["count"]) for v in present.values()):
        return []
    given = "、".join(f"{k} = {v}" for k, v in present.items())
    return [CompletenessItem("metadata.cores.count",
                             f"metadata.cores.count = {cores['count']}，与 {given} 都不一致")]


def check_chip(chip, project=None, entries: Optional[List[Any]] = None) -> List[CompletenessItem]:
    """Everything incomplete or unconfirmed about ``chip``; empty when complete.

    Args:
        project: gives the loaded definitions (selector values) and the plugin.xml
            files; without it only the chip's own data is checked
        entries: ``ecuresource`` entries to use instead of reading the project's
            plugin.xml files (to read them once for many chips)
    """
    if chip is None:
        return []
    if entries is None:
        entries = plugin_entries(project) if project is not None else []
    items = unconfirmed_fields(chip)
    if project is not None:
        items += _selector_items(chip, project)
    items += _os_resource_items(chip, entries)
    items += _core_count_items(chip)
    return items


def check_chips(chips: Iterable[Any], project=None) -> Dict[str, List[CompletenessItem]]:
    """Chip name -> items, for the chips that have any (plugin.xml read once)."""
    entries = plugin_entries(project) if project is not None else []
    result = {}
    for chip in chips:
        items = check_chip(chip, project, entries)
        if items:
            result[chip.name] = items
    return result
