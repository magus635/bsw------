"""Parser for BSW InternalBehavior ARXML files under ``system/``."""

from dataclasses import dataclass, field
import logging
from pathlib import Path
from typing import Dict, List, Optional, Tuple
from lxml import etree

logger = logging.getLogger(__name__)


def _local(tag) -> str:
    if not isinstance(tag, str):
        return ""
    return tag.rsplit("}", 1)[-1]


def _child_text(elem: etree._Element, tag_name: str) -> Optional[str]:
    for ch in elem:
        if _local(ch.tag) == tag_name and ch.text:
            text = ch.text.strip()
            if text:
                return text
    return None


def _ar_path(elem: etree._Element) -> Optional[str]:
    sn = _child_text(elem, "SHORT-NAME")
    if not sn:
        return None
    segments = [sn]
    parent = elem.getparent()
    while parent is not None:
        anc_sn = _child_text(parent, "SHORT-NAME")
        if anc_sn:
            segments.append(anc_sn)
        parent = parent.getparent()
    return "/" + "/".join(reversed(segments))


@dataclass
class BswIbEventData:
    """Extracted BSW scheduling event metadata from ``BSW-INTERNAL-BEHAVIOR/EVENTS``."""

    short_name: str
    ar_path: str
    event_kind: str
    entity_ref: Optional[str] = None
    entity_name: Optional[str] = None
    period_sec: Optional[float] = None


@dataclass
class BswIbModuleData:
    """Extracted behavior metadata for a ``BSW-MODULE-DESCRIPTION``."""

    ar_path: str
    module_short_name: str
    behavior_ar_path: Optional[str] = None
    exclusive_areas: List[str] = field(default_factory=list)
    exclusive_area_paths: Dict[str, str] = field(default_factory=dict)
    schedulable_entities: List[Tuple[str, str]] = field(default_factory=list)
    event_paths: List[str] = field(default_factory=list)
    events: List[BswIbEventData] = field(default_factory=list)
    source_file: str = ""


@dataclass
class BswIbImplData:
    """Extracted ``BSW-IMPLEMENTATION`` metadata from InternalBehavior ARXML."""

    ar_path: str
    short_name: str
    vendor_id: Optional[str] = None
    vendor_api_infix: Optional[str] = None
    ar_release_version: Optional[str] = None
    behavior_ref: Optional[str] = None
    memory_section_count: int = 0
    memmap_artifact_header: Optional[str] = None


class BswIbIndex:
    """Indexed lookup across all BSW InternalBehavior files in a project's ``system/`` tree."""

    def __init__(self) -> None:
        self.by_behavior_path: Dict[str, BswIbModuleData] = {}
        self.by_ea_path: Dict[str, BswIbModuleData] = {}
        self.by_event_path: Dict[str, BswIbModuleData] = {}
        self.by_module_name: Dict[str, List[BswIbModuleData]] = {}
        self.impls_by_path: Dict[str, BswIbImplData] = {}
        self.entries_by_path: Dict[str, str] = {}
        self.events_by_path: Dict[str, BswIbEventData] = {}
        self._pending_entities: List[Tuple[BswIbModuleData, List[Tuple[str, Optional[str]]]]] = []
        self._pending_events: List[Tuple[BswIbModuleData, Dict[str, Tuple[str, Optional[str]]]]] = []
        self._all_entity_entries: Dict[str, Tuple[str, Optional[str]]] = {}

    def index_file(self, arxml_path: Path, rel_source: Optional[str] = None) -> None:
        """Parse a single ARXML file and register any BSW descriptions, entries, and impls."""
        source_label = rel_source or Path(arxml_path).as_posix()
        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        try:
            tree = etree.parse(str(arxml_path), parser)
        except (etree.XMLSyntaxError, OSError, ValueError) as exc:
            logger.debug("Skipping unreadable IB ARXML %s: %s", arxml_path, exc)
            return

        root = tree.getroot()
        if root is None:
            return

        for elem in root.iter():
            tag = _local(elem.tag)
            if not tag:
                continue
            if tag == "BSW-MODULE-ENTRY":
                epath = _ar_path(elem)
                sn = _child_text(elem, "SHORT-NAME")
                if epath and sn:
                    self.entries_by_path[epath.rstrip("/")] = sn
            elif tag == "BSW-IMPLEMENTATION":
                impl = self._parse_bsw_impl(elem)
                if impl is not None:
                    self.impls_by_path[impl.ar_path.rstrip("/")] = impl
            elif tag == "BSW-MODULE-DESCRIPTION":
                self._parse_bsw_module_desc(elem, source_label)

    def finalize(self) -> None:
        """Resolve ``<IMPLEMENTED-ENTRY-REF>`` and event target entities after all entries are indexed."""
        for bmd, raw_entities in self._pending_entities:
            resolved: List[Tuple[str, str]] = []
            seen: set = set()
            for entity_sn, entry_ref in raw_entities:
                entry_name = entity_sn
                if entry_ref:
                    entry_name = self.entries_by_path.get(entry_ref.rstrip("/"), entity_sn)
                if entry_name not in seen:
                    seen.add(entry_name)
                    resolved.append((entity_sn, entry_name))
            bmd.schedulable_entities = resolved
        self._pending_entities.clear()

        for bmd, entity_map in self._pending_events:
            for ev in bmd.events:
                resolved_name: Optional[str] = None
                if ev.entity_ref:
                    ent_info = entity_map.get(ev.entity_ref) or self._all_entity_entries.get(ev.entity_ref)
                    if ent_info is not None:
                        se_sn, entry_ref = ent_info
                        resolved_name = (
                            self.entries_by_path.get(entry_ref.rstrip("/"), se_sn)
                            if entry_ref
                            else se_sn
                        )
                    else:
                        resolved_name = ev.entity_ref.rsplit("/", 1)[-1]
                ev.entity_name = resolved_name
        self._pending_events.clear()

    @classmethod
    def load_directory(cls, system_dir: Path) -> "BswIbIndex":
        """Scan ``system_dir/**/*.arxml`` and build a finalized :class:`BswIbIndex`."""
        index = cls()
        root_dir = Path(system_dir)
        if not root_dir.is_dir():
            return index
        arxml_files = sorted(
            (p for p in root_dir.rglob("*") if p.is_file() and p.suffix.lower() == ".arxml"),
            key=lambda p: p.relative_to(root_dir).as_posix(),
        )
        for path in arxml_files:
            index.index_file(path, rel_source=path.relative_to(root_dir).as_posix())
        index.finalize()
        return index

    @staticmethod
    def _parse_bsw_impl(elem: etree._Element) -> Optional[BswIbImplData]:
        ar_path = _ar_path(elem)
        sn = _child_text(elem, "SHORT-NAME")
        if not ar_path or not sn:
            return None
        mem_secs = [
            ch for ch in elem.iter() if _local(ch.tag) == "MEMORY-SECTION"
        ]
        memmap_hdr: Optional[str] = None
        for dep in elem.iter():
            if _local(dep.tag) != "DEPENDENCY-ON-ARTIFACT":
                continue
            dep_cat = _child_text(dep, "CATEGORY") or ""
            for desc in dep.iter():
                if _local(desc.tag) != "ARTIFACT-DESCRIPTOR":
                    continue
                label = _child_text(desc, "SHORT-LABEL")
                if label and (dep_cat.upper() == "MEMMAP" or label.endswith("MemMap.h")):
                    memmap_hdr = label
                    break
            if memmap_hdr:
                break
        return BswIbImplData(
            ar_path=ar_path,
            short_name=sn,
            vendor_id=_child_text(elem, "VENDOR-ID"),
            vendor_api_infix=_child_text(elem, "VENDOR-API-INFIX"),
            ar_release_version=_child_text(elem, "AR-RELEASE-VERSION"),
            behavior_ref=_child_text(elem, "BEHAVIOR-REF"),
            memory_section_count=len(mem_secs),
            memmap_artifact_header=memmap_hdr,
        )

    def _parse_bsw_module_desc(self, elem: etree._Element, source_label: str) -> None:
        ar_path = _ar_path(elem)
        sn = _child_text(elem, "SHORT-NAME")
        if not ar_path or not sn:
            return

        behaviors = [
            ch for ch in elem.iter() if _local(ch.tag) == "BSW-INTERNAL-BEHAVIOR"
        ]
        if not behaviors:
            bmd = BswIbModuleData(ar_path=ar_path, module_short_name=sn, source_file=source_label)
            self.by_module_name.setdefault(sn, []).append(bmd)
            return

        beh = behaviors[0]
        beh_path = _ar_path(beh)

        ea_names: List[str] = []
        ea_paths: Dict[str, str] = {}
        for ea_el in beh.iter():
            if _local(ea_el.tag) != "EXCLUSIVE-AREA":
                continue
            ea_sn = _child_text(ea_el, "SHORT-NAME")
            ea_full = _ar_path(ea_el)
            if ea_sn and ea_sn not in ea_names:
                ea_names.append(ea_sn)
            if ea_full:
                norm_ea = ea_full.rstrip("/")
                if ea_sn:
                    ea_paths[norm_ea] = ea_sn

        raw_entities: List[Tuple[str, Optional[str]]] = []
        entity_map: Dict[str, Tuple[str, Optional[str]]] = {}
        for se_el in beh.iter():
            if _local(se_el.tag) != "BSW-SCHEDULABLE-ENTITY":
                continue
            se_sn = _child_text(se_el, "SHORT-NAME")
            if not se_sn:
                continue
            se_path = _ar_path(se_el)
            entry_ref = _child_text(se_el, "IMPLEMENTED-ENTRY-REF")
            raw_entities.append((se_sn, entry_ref))
            if se_path:
                norm_se = se_path.rstrip("/")
                entity_map[norm_se] = (se_sn, entry_ref)
                self._all_entity_entries[norm_se] = (se_sn, entry_ref)

        event_paths: List[str] = []
        events_data: List[BswIbEventData] = []
        events_el = next((ch for ch in beh if _local(ch.tag) == "EVENTS"), None)
        if events_el is not None:
            for ev in events_el:
                if not isinstance(ev.tag, str):
                    continue
                ev_path = _ar_path(ev)
                if not ev_path:
                    continue
                norm_ev = ev_path.rstrip("/")
                event_paths.append(norm_ev)
                ev_sn = _child_text(ev, "SHORT-NAME") or norm_ev.rsplit("/", 1)[-1]
                ev_kind = _local(ev.tag)
                ent_ref = _child_text(ev, "STARTS-ON-EVENT-REF")
                period_raw = _child_text(ev, "PERIOD")
                period_sec: Optional[float] = None
                if period_raw is not None:
                    try:
                        period_sec = float(period_raw)
                    except ValueError:
                        period_sec = None
                ev_obj = BswIbEventData(
                    short_name=ev_sn,
                    ar_path=norm_ev,
                    event_kind=ev_kind,
                    entity_ref=ent_ref.strip().rstrip("/") if ent_ref else None,
                    period_sec=period_sec,
                )
                events_data.append(ev_obj)

        bmd = BswIbModuleData(
            ar_path=ar_path,
            module_short_name=sn,
            behavior_ar_path=beh_path,
            exclusive_areas=ea_names,
            exclusive_area_paths=ea_paths,
            event_paths=event_paths,
            events=events_data,
            source_file=source_label,
        )
        self._pending_entities.append((bmd, raw_entities))
        self._pending_events.append((bmd, entity_map))
        if beh_path:
            self.by_behavior_path[beh_path.rstrip("/")] = bmd
        for norm_ea in ea_paths:
            self.by_ea_path[norm_ea] = bmd
        for norm_ev in event_paths:
            self.by_event_path[norm_ev] = bmd
        for ev_obj in events_data:
            self.events_by_path[ev_obj.ar_path] = ev_obj
        self.by_module_name.setdefault(sn, []).append(bmd)
