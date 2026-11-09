"""Module package: chip-conditional file selection and PRE/REC loading."""

from pathlib import Path
from typing import List, Optional

from lxml import etree

from ..model.configuration_model import EcucModuleConfiguration
from .errors import PackageConflictError, PackageError
from .types import ModuleManifest
from .value_index import index_value_collections, load_value_collection

_XDM_DATA_NS = "http://www.tresos.de/_projects/DataModel2/06/data.xsd"


def _secure_parser() -> etree.XMLParser:
    return etree.XMLParser(resolve_entities=False, no_network=True, huge_tree=True)


def _local(tag) -> str:
    if not isinstance(tag, str):
        return ""
    return tag.rsplit("}", 1)[-1]


def _child_short_name(elem) -> Optional[str]:
    for child in elem:
        if _local(child.tag) == "SHORT-NAME":
            return (child.text or "").strip()
    return None


def _arxml_module_def_paths(file_path: Path) -> List[str]:
    """Return AR paths of every ECUC-MODULE-DEF in an ARXML file."""
    root = etree.parse(str(file_path), _secure_parser()).getroot()
    paths = []
    for elem in root.iter():
        if _local(elem.tag) != "ECUC-MODULE-DEF":
            continue
        name = _child_short_name(elem)
        if not name:
            continue
        segments = [name]
        parent = elem.getparent()
        while parent is not None:
            if _local(parent.tag) == "AR-PACKAGE":
                pkg_name = _child_short_name(parent)
                if pkg_name:
                    segments.append(pkg_name)
            parent = parent.getparent()
        paths.append("/" + "/".join(reversed(segments)))
    return paths


def _xdm_module_def_paths(file_path: Path) -> List[str]:
    """Return AR paths of every MODULE-DEF choice in an XDM file."""
    root = etree.parse(str(file_path), _secure_parser()).getroot()
    chc_tag = f"{{{_XDM_DATA_NS}}}chc"
    ctr_tag = f"{{{_XDM_DATA_NS}}}ctr"
    paths = []
    for elem in root.iter(chc_tag):
        if elem.get("value") != "MODULE-DEF" or not elem.get("name"):
            continue
        segments = [elem.get("name")]
        parent = elem.getparent()
        while parent is not None:
            if parent.tag == ctr_tag and parent.get("type") == "AR-PACKAGE":
                segments.append(parent.get("name") or "")
            parent = parent.getparent()
        paths.append("/" + "/".join(reversed(segments)))
    return paths


def module_def_paths(file_path: Path) -> List[str]:
    """Return AR paths of module definitions found in an .arxml or .xdm file."""
    suffix = file_path.suffix.lower()
    if suffix == ".arxml":
        return _arxml_module_def_paths(file_path)
    if suffix == ".xdm":
        return _xdm_module_def_paths(file_path)
    return []


class ModulePackage:
    """A module package rooted at ``root`` and described by ``manifest``.

    Attributes:
        root: Package root directory
        manifest: Package manifest
        warnings: Non-fatal messages accumulated while loading PRE/REC
    """

    def __init__(self, root: Path, manifest: ModuleManifest):
        self.root = Path(root)
        self.manifest = manifest
        self.warnings: List[str] = []

    def __repr__(self) -> str:
        return f"ModulePackage({self.root.as_posix()!r}, {self.manifest.definition!r})"

    def selected_files(self, chip: Optional[str]) -> List[Path]:
        """Files active for ``chip``: unconditional files plus those listing ``chip``."""
        selected = [
            self.root / pf.path
            for pf in self.manifest.files
            if not pf.chips or (chip is not None and chip in pf.chips)
        ]
        return sorted(selected, key=lambda p: p.as_posix())

    def _check_files_exist(self) -> None:
        """Raise if any file listed in the manifest is missing on disk (no silent miss)."""
        missing = sorted(pf.path for pf in self.manifest.files if not (self.root / pf.path).is_file())
        if missing:
            raise PackageError(
                f"{self.manifest.module}: manifest lists missing file(s) "
                f"{', '.join(missing)} in package {self.root.as_posix()}"
            )

    def definition_file(self, chip: Optional[str]) -> Path:
        """The single selected file holding the ECUC-MODULE-DEF at ``manifest.definition``.

        Raises:
            PackageConflictError: more than one selected file holds the definition
            PackageError: no selected file holds it
        """
        self._check_files_exist()
        definition = self.manifest.definition
        matches = []
        for path in self.selected_files(chip):
            try:
                found = module_def_paths(path)
            except etree.XMLSyntaxError as exc:
                raise PackageError(f"Cannot parse package file {path}: {exc}") from exc
            if definition in found:
                matches.append(path)

        if len(matches) > 1:
            raise PackageConflictError(
                f"Definition {definition} found in {len(matches)} selected files "
                f"(chip={chip}): {', '.join(p.as_posix() for p in matches)}",
                path=definition,
                files=[p.as_posix() for p in matches],
            )
        if not matches:
            raise PackageError(
                f"No selected file in package {self.root.as_posix()} contains "
                f"definition {definition} (chip={chip})"
            )
        return matches[0]

    def load_pre(self, chip: Optional[str]) -> List[EcucModuleConfiguration]:
        """Merged PRE value collections for ``chip``; missing paths only warn."""
        return self._load_collections(self.manifest.pre, chip, "pre")

    def load_rec(self, chip: Optional[str]) -> List[EcucModuleConfiguration]:
        """Merged REC value collections for ``chip``; missing paths only warn."""
        return self._load_collections(self.manifest.rec, chip, "rec")

    def _load_collections(
        self, ar_paths: List[str], chip: Optional[str], role: str
    ) -> List[EcucModuleConfiguration]:
        self._check_files_exist()
        files = [
            p for p in self.selected_files(chip)
            if p.suffix.lower() in (".arxml", ".xdm")
        ]
        result = []
        for ar_path in ar_paths:
            config = load_value_collection(files, ar_path)
            if config is None:
                holders = self._unselected_files_with(ar_path, chip)
                if holders:
                    raise PackageError(
                        f"{self.manifest.module}: {role} path {ar_path} exists only in "
                        f"files not selected for chip {chip}: "
                        f"{', '.join(p.as_posix() for p in holders)}"
                    )
                self.warnings.append(
                    f"{self.manifest.module}: {role} path {ar_path} not found in "
                    f"selected package files (chip={chip})"
                )
                continue
            result.append(config)
        return result

    def _unselected_files_with(self, ar_path: str, chip: Optional[str]) -> List[Path]:
        selected = set(self.selected_files(chip))
        holders = []
        for pf in self.manifest.files:
            path = self.root / pf.path
            if path in selected:
                continue
            if path.suffix.lower() not in (".arxml", ".xdm"):
                continue
            if ar_path in index_value_collections(path):
                holders.append(path)
        return sorted(holders, key=lambda p: p.as_posix())

    def template_dir(self) -> Optional[Path]:
        return self._optional_dir(self.manifest.templates)

    def resource_dir(self) -> Optional[Path]:
        return self._optional_dir(self.manifest.resources)

    def _optional_dir(self, rel: Optional[str]) -> Optional[Path]:
        if not rel:
            return None
        path = self.root / rel
        return path if path.is_dir() else None
