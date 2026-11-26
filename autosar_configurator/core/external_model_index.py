"""Lightweight read-only index of non-ECUC AUTOSAR ARXML models stored under ``system/``.

Indexes referrable elements (e.g., SW-ADDR-METHOD, MODE-DECLARATION, I-SIGNAL,
CAN-FRAME, PDU-TO-FRAME-MAPPING, IMPLEMENTATION-DATA-TYPE, BSW-MODULE-ENTRY) by
full AUTOSAR path without importing non-ECUC models into the ECUC container tree.
"""

from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Tuple
import logging
from lxml import etree

logger = logging.getLogger(__name__)

_SKIP_CONTAINER_TAGS = frozenset({
    "ADMIN-DATA",
    "ANNOTATIONS",
    "DESC",
    "INTRODUCTION",
    "TRACE",
    "TRACE-REFS",
    "VARIATION-POINT",
})

_METADATA_TAGS = frozenset({
    "BASE-TYPE-ENCODING",
    "BASE-TYPE-SIZE",
    "CALL-TYPE",
    "CATEGORY",
    "DATA-TYPE-POLICY",
    "EXECUTION-CONTEXT",
    "FRAME-LENGTH",
    "I-SIGNAL-REF",
    "IS-REENTRANT",
    "IS-SYNCHRONOUS",
    "LENGTH",
    "MEMORY-ALLOCATION-KEYWORD-POLICY",
    "NATIVE-DECLARATION",
    "PACKING-BYTE-ORDER",
    "PDU-REF",
    "SECTION-INITIALIZATION-POLICY",
    "SECTION-TYPE",
    "SERVICE-ID",
    "START-POSITION",
    "SW-ADDRMETHOD-REF",
    "TRANSFER-PROPERTY",
    "TYPE-TREF",
    "VALUE",
})


def _local_tag(elem: etree._Element) -> str:
    tag = elem.tag
    if not isinstance(tag, str):
        return ""
    return tag.rsplit("}", 1)[-1]


def _direct_short_name(elem: etree._Element) -> Optional[str]:
    for child in elem:
        if _local_tag(child) == "SHORT-NAME" and child.text:
            text = child.text.strip()
            if text:
                return text
    return None


def _extract_attributes(elem: etree._Element, max_depth: int = 2) -> Dict[str, str]:
    """Collect curated scalar child tags without crossing into nested SHORT-NAME sub-elements."""
    attrs: Dict[str, str] = {}

    def _walk(node: etree._Element, depth: int) -> None:
        if depth > max_depth:
            return
        for child in node:
            tag = _local_tag(child)
            if not tag or tag == "SHORT-NAME" or tag in _SKIP_CONTAINER_TAGS:
                continue
            if depth > 0 and _direct_short_name(child) is not None:
                continue
            if tag in _METADATA_TAGS and tag not in attrs and child.text and child.text.strip():
                attrs[tag] = child.text.strip()
            if len(child) > 0:
                _walk(child, depth + 1)

    _walk(elem, 0)
    return attrs


@dataclass(frozen=True)
class ExternalModelElement:
    """Read-only descriptor for an addressable non-ECUC AUTOSAR model element."""

    ar_path: str
    short_name: str
    tag: str
    source_file: str
    category: str = ""
    uuid: Optional[str] = None
    attributes: Dict[str, str] = field(default_factory=dict)


class ExternalModelIndex:
    """In-memory read-only lookup index built from ``system/**/*.arxml``."""

    def __init__(self) -> None:
        self.elements: Dict[str, ExternalModelElement] = {}
        self.files: List[str] = []
        self.errors: List[Tuple[str, str]] = []
        self._by_tag: Dict[str, List[ExternalModelElement]] = {}

    @property
    def count(self) -> int:
        return len(self.elements)

    def __len__(self) -> int:
        return len(self.elements)

    def __bool__(self) -> bool:
        return bool(self.elements)

    def __contains__(self, path: object) -> bool:
        if not isinstance(path, str):
            return False
        return self.get(path) is not None

    def get(self, path: str) -> Optional[ExternalModelElement]:
        """Look up an external element by its AUTOSAR path."""
        if not path:
            return None
        normalized = path.strip().rstrip("/")
        if not normalized:
            return None
        return self.elements.get(normalized)

    def find_by_tag(self, tag: str) -> List[ExternalModelElement]:
        """Return all indexed elements matching an AUTOSAR XML tag name."""
        if not tag:
            return []
        return list(self._by_tag.get(tag.strip(), ()))

    def all_elements(self) -> List[ExternalModelElement]:
        """Return all indexed external elements in insertion order."""
        return list(self.elements.values())

    def _register(self, item: ExternalModelElement) -> None:
        prev = self.elements.get(item.ar_path)
        if prev is not None:
            prev_list = self._by_tag.get(prev.tag)
            if prev_list:
                self._by_tag[prev.tag] = [e for e in prev_list if e.ar_path != item.ar_path]
        self.elements[item.ar_path] = item
        self._by_tag.setdefault(item.tag, []).append(item)

    def index_file(self, arxml_path: Path, rel_source: Optional[str] = None) -> int:
        """Parse and index one ARXML file. Returns number of elements added/updated."""
        source_label = rel_source or Path(arxml_path).as_posix()
        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        try:
            tree = etree.parse(str(arxml_path), parser)
        except (etree.XMLSyntaxError, OSError, ValueError) as exc:
            logger.warning("Failed to parse external ARXML %s: %s", arxml_path, exc)
            self.errors.append((source_label, str(exc)))
            return 0

        root = tree.getroot()
        if root is None:
            return 0

        added = 0

        def _visit_referrable(node: etree._Element, current_path: str) -> None:
            nonlocal added
            for child in node:
                tag = _local_tag(child)
                if not tag or tag in _SKIP_CONTAINER_TAGS:
                    continue
                if tag == "AR-PACKAGES":
                    _visit_package_container(child, current_path)
                    continue
                short_name = _direct_short_name(child)
                if short_name is not None:
                    elem_path = f"{current_path}/{short_name}"
                    attrs = _extract_attributes(child)
                    item = ExternalModelElement(
                        ar_path=elem_path,
                        short_name=short_name,
                        tag=tag,
                        source_file=source_label,
                        category=attrs.get("CATEGORY", ""),
                        uuid=child.get("UUID"),
                        attributes=attrs,
                    )
                    self._register(item)
                    added += 1
                    _visit_referrable(child, elem_path)
                elif len(child) > 0:
                    _visit_referrable(child, current_path)

        def _visit_package_container(node: etree._Element, prefix: str) -> None:
            for child in node:
                tag = _local_tag(child)
                if not tag or tag in _SKIP_CONTAINER_TAGS:
                    continue
                if tag == "AR-PACKAGE":
                    pkg_name = _direct_short_name(child)
                    if not pkg_name:
                        continue
                    pkg_path = f"{prefix}/{pkg_name}"
                    for sub in child:
                        sub_tag = _local_tag(sub)
                        if sub_tag == "AR-PACKAGES":
                            _visit_package_container(sub, pkg_path)
                        elif sub_tag == "ELEMENTS":
                            _visit_referrable(sub, pkg_path)
                elif tag == "AR-PACKAGES":
                    _visit_package_container(child, prefix)

        if _local_tag(root) == "AR-PACKAGES":
            _visit_package_container(root, "")
        else:
            for child in root:
                if _local_tag(child) == "AR-PACKAGES":
                    _visit_package_container(child, "")

        if source_label not in self.files:
            self.files.append(source_label)
        return added

    @classmethod
    def load_directory(cls, system_dir: Path) -> "ExternalModelIndex":
        """Recursively scan all ``*.arxml`` files under ``system_dir``."""
        index = cls()
        root_dir = Path(system_dir)
        if not root_dir.is_dir():
            return index

        arxml_files = sorted(
            (p for p in root_dir.rglob("*") if p.is_file() and p.suffix.lower() == ".arxml"),
            key=lambda p: p.relative_to(root_dir).as_posix(),
        )
        for path in arxml_files:
            rel_posix = path.relative_to(root_dir).as_posix()
            index.index_file(path, rel_source=rel_posix)
        return index
