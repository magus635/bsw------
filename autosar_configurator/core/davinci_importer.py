"""DaVinci project import: parse .dpa, scan SIP, merge, write packages.

Real design (per MERGE_DESIGN_REVIEW.md):
- Task 0 (前置修复)：Fix痛点 1-2 in project_controller + config_manager
- Task 1 (this module)：DaVinciProject parser + SipScanner content-driven grouping
- Task 2：Value import + baseline integration
"""

from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple
from lxml import etree
import json
import logging
import io

logger = logging.getLogger(__name__)


class SipMergeError(Exception):
    """Raised when merge conflict detected during SIP ingestion."""

    def __init__(
        self,
        ar_path: str,
        reason: str,
        file1: Optional[Path] = None,
        file2: Optional[Path] = None,
    ):
        self.ar_path = ar_path
        self.reason = reason
        self.file1 = file1
        self.file2 = file2
        msg = f"Merge conflict at {ar_path}: {reason}"
        if file1 is not None:
            msg += f"\n  file1: {file1}"
        if file2 is not None:
            msg += f"\n  file2: {file2}"
        super().__init__(msg)


class SipDerivativeMappingError(SipMergeError):
    """Raised when a DerivativeMapping XML exists but cannot resolve the requested UUID."""


def normalize_version(version: Optional[str]) -> Tuple[Any, ...]:
    """Normalize dotted version strings so '1.2.0' compares equal to '1.02.00'."""
    if not version:
        return ()
    parts: List[Any] = []
    for token in str(version).strip().split("."):
        token = token.strip()
        if token.isdigit():
            parts.append((0, int(token)))
        else:
            parts.append((1, token.lower()))
    return tuple(parts)


def versions_match(v1: Optional[str], v2: Optional[str]) -> bool:
    """Return True when two non-empty version strings represent the same normalized version."""
    n1 = normalize_version(v1)
    n2 = normalize_version(v2)
    return bool(n1 and n2 and n1 == n2)


def compare_module_values(
    source_cfg,
    imported_cfg,
    module_name: str,
    expected_pre_keys: Optional[Set[str]] = None,
) -> List[Dict[str, Any]]:
    """Compare source configuration values against imported Active values (W12)."""
    from .baseline.values import flatten, values_equal

    skip_keys = expected_pre_keys or set()
    src_flat = flatten(source_cfg, module_name)
    dst_flat = flatten(imported_cfg, module_name)
    diffs: List[Dict[str, Any]] = []
    for key in sorted(src_flat):
        if key in skip_keys:
            continue
        src_val = src_flat[key]
        if key not in dst_flat:
            diffs.append({
                "key": key,
                "kind": "missing",
                "source": src_val,
                "imported": None,
            })
        elif not values_equal(src_val, dst_flat[key]):
            diffs.append({
                "key": key,
                "kind": "different",
                "source": src_val,
                "imported": dst_flat[key],
            })
    return diffs


@dataclass
class SipFile:
    """A single ARXML/XDM file from SIP."""
    path: Path
    module: str  # Extracted from the file content, not from path
    content: Optional[bytes] = None
    role: str = "def"  # "def" (has ECUC-MODULE-DEF) | "config" (only value collections)


class DaVinciProject:
    """Parse real DaVinci .dpa XML and extract project metadata."""

    def __init__(
        self,
        dpa_path: Path,
        derivative_uuid: Optional[str],
        derivative_name: Optional[str],
        sip_root: Optional[Path],
        module_definitions: Dict[str, str],
        ecuc_split_map: Dict[str, str],
        main_ecuc_file: Optional[str],
        active_modules: Optional[Set[str]] = None,
        bsw_impl_versions: Optional[Dict[str, str]] = None,
    ):
        self.dpa_path = Path(dpa_path)
        self.derivative_uuid = derivative_uuid
        self.derivative_name = derivative_name
        self.sip_root = sip_root
        self.module_definitions = module_definitions  # {name -> definition_ref}
        self.ecuc_split_map = ecuc_split_map  # {name -> ecuc_arxml_file}
        self.main_ecuc_file = main_ecuc_file
        self.active_modules = active_modules or set()
        self.bsw_impl_versions = bsw_impl_versions or {}

    @classmethod
    def from_file(cls, dpa_path: Path) -> "DaVinciProject":
        """Parse .dpa file.

        Args:
            dpa_path: Path to .dpa XML

        Returns:
            DaVinciProject instance

        Raises:
            FileNotFoundError: If dpa_path doesn't exist
            etree.XMLSyntaxError: If XML is malformed
        """
        dpa_path = Path(dpa_path)
        if not dpa_path.exists():
            raise FileNotFoundError(f"DaVinci project not found: {dpa_path}")

        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        tree = etree.parse(str(dpa_path), parser)
        root = tree.getroot()

        # Extract SIP root (normalize Windows backslashes on POSIX hosts)
        sip_root = None
        sip_elem = root.find(".//Folders/SIP")
        if sip_elem is None:
            sip_elem = root.find(".//SIP")
        if sip_elem is not None and sip_elem.text:
            rel_path = sip_elem.text.strip().replace("\\", "/")
            try:
                sip_root = (dpa_path.parent / rel_path).resolve()
            except (OSError, ValueError):
                pass

        # Validate that sip_root actually holds Components/ or DemoComponents/.
        # Some DaVinci projects (e.g. Applications/SipAddon/StartApplication) have
        # <SIP>.\..\..</SIP> which lands on Applications/ one level below the real SIP root.
        def _is_sip_root(p: Optional[Path]) -> bool:
            return bool(
                p is not None
                and p.is_dir()
                and ((p / "Components").is_dir() or (p / "DemoComponents").is_dir())
            )

        if not _is_sip_root(sip_root):
            candidates: List[Path] = []
            if sip_root is not None:
                candidates.extend(list(sip_root.parents)[:4])
            candidates.extend(list(dpa_path.parent.parents)[:5])
            for cand in candidates:
                if _is_sip_root(cand):
                    sip_root = cand
                    break

        # Extract derivative info
        derivative_uuid = None
        derivative_name = None
        deriv_elem = root.find(".//Environment/Derivative[@UUID]")
        if deriv_elem is None:
            deriv_elem = root.find(".//Derivative[@UUID]")
        if deriv_elem is not None:
            derivative_uuid = deriv_elem.get("UUID")
            if deriv_elem.text:
                derivative_name = deriv_elem.text.strip()

        # Extract module definitions from both ModuleDefinitionMappings and ECUC/Active/ModuleRef
        module_definitions: Dict[str, str] = {}
        for mapping in root.findall(".//ModuleDefinitionMappings/ModuleDefinitionMapping"):
            mod_name = mapping.get("ModuleConfigName", "").strip()
            def_ref = mapping.get("ModuleDefinitionRef", "").strip()
            if mod_name and def_ref:
                module_definitions[mod_name] = def_ref
        for mod_ref in root.findall(".//ECUC/Active/ModuleRef"):
            mod_name = mod_ref.get("name", "").strip()
            def_ref = mod_ref.get("definitionRef", "").strip()
            if mod_name and def_ref and mod_name not in module_definitions:
                module_definitions[mod_name] = def_ref

        # Extract ECUC split mapping from both Splitter/Module and Entry schemas
        ecuc_split_map: Dict[str, str] = {}
        for splitter in root.findall(".//EcucSplitter/Splitter"):
            file_path = splitter.get("File", "").strip().replace("\\", "/")
            mod_elem = splitter.find("Module")
            if mod_elem is not None:
                mod_name = mod_elem.get("Name", "").strip()
                if mod_name and file_path:
                    ecuc_split_map[mod_name] = file_path
        for entry in root.findall(".//EcucSplitter/Entry"):
            mod_name = entry.get("module", "").strip()
            file_path = entry.get("file", "").strip().replace("\\", "/")
            if mod_name and file_path and mod_name not in ecuc_split_map:
                ecuc_split_map[mod_name] = file_path

        # Extract main ECUC file
        main_ecuc_file = None
        config_elem = root.find(".//EcucSplitter/Configuration")
        if config_elem is not None and config_elem.text:
            main_ecuc_file = config_elem.text.strip().replace("\\", "/")
        else:
            active_elem = root.find(".//ECUC/Active")
            if active_elem is not None and active_elem.text and active_elem.text.strip():
                main_ecuc_file = active_elem.text.strip().replace("\\", "/")

        # Extract active modules:
        # 1. Authoritative: ECUC-VALUE-COLLECTION refs in main_ecuc_file (e.g. StartApplication.ecuc.arxml)
        # 2. Fallback: EcucSplitter module list
        # 3. Last resort (minimal .dpa): ModuleDefinitionMappings keys
        active_modules: Set[str] = set()
        if main_ecuc_file:
            main_norm = main_ecuc_file[2:] if main_ecuc_file.startswith("./") else main_ecuc_file
            main_path = (dpa_path.parent / main_norm).resolve()
            if main_path.is_file():
                try:
                    main_tree = etree.parse(str(main_path), parser)
                    for elem in main_tree.getroot().iter():
                        if (
                            isinstance(elem.tag, str)
                            and elem.tag.rsplit("}", 1)[-1] == "ECUC-MODULE-CONFIGURATION-VALUES-REF"
                            and elem.text
                        ):
                            ref_leaf = elem.text.strip().rstrip("/").rsplit("/", 1)[-1]
                            if ref_leaf:
                                active_modules.add(ref_leaf)
                except Exception:
                    pass
                if not active_modules:
                    try:
                        from .config_manager import EpcFileScanner
                        active_modules.update(EpcFileScanner.list_module_names(main_path))
                    except Exception:
                        pass
        if not active_modules and ecuc_split_map:
            active_modules.update(ecuc_split_map.keys())
        if not active_modules and module_definitions:
            active_modules.update(module_definitions.keys())

        # Fallback: infer missing ModuleDefinitionMapping entries from split/main ECUC files
        # (some .dpa files omit MCAL entries like Can/Resource from ModuleDefinitionMappings).
        ecuc_file_entries_cache: Dict[Path, List[Tuple[str, str]]] = {}
        for mod_name in sorted(active_modules | set(ecuc_split_map.keys())):
            if mod_name in module_definitions:
                continue
            rel = ecuc_split_map.get(mod_name) or main_ecuc_file
            if not rel:
                continue
            norm = rel[2:] if rel.startswith("./") else rel
            try:
                ecuc_path = (dpa_path.parent / norm).resolve()
            except (OSError, ValueError):
                continue
            if not ecuc_path.is_file():
                continue
            if ecuc_path not in ecuc_file_entries_cache:
                parsed_entries: List[Tuple[str, str]] = []
                try:
                    ecuc_tree = etree.parse(str(ecuc_path), parser)
                    for elem in ecuc_tree.getroot().iter():
                        if not isinstance(elem.tag, str) or elem.tag.rsplit("}", 1)[-1] != "ECUC-MODULE-CONFIGURATION-VALUES":
                            continue
                        sn = ""
                        dref = ""
                        for child in elem:
                            if not isinstance(child.tag, str):
                                continue
                            ctag = child.tag.rsplit("}", 1)[-1]
                            if ctag == "SHORT-NAME" and child.text:
                                sn = child.text.strip()
                            elif ctag == "DEFINITION-REF" and child.text:
                                dref = child.text.strip()
                        if dref:
                            parsed_entries.append((sn, dref))
                except (etree.XMLSyntaxError, OSError, ValueError):
                    pass
                ecuc_file_entries_cache[ecuc_path] = parsed_entries
            for sn, dref in ecuc_file_entries_cache[ecuc_path]:
                def_leaf = dref.rstrip("/").rsplit("/", 1)[-1]
                if sn == mod_name or def_leaf == mod_name:
                    module_definitions[mod_name] = dref
                    break

        # Extract BswImplSwVersion entries from BswImplVersionPersistor
        bsw_impl_versions: Dict[str, str] = {}
        persistor = root.find(
            ".//Settings[@Name='com.vector.cfg.gen.core.bswmdmigration.internal.service.BswImplVersionPersistor']"
        )
        if persistor is not None:
            for mod_settings in persistor.findall("Settings"):
                raw_name = (mod_settings.get("Name") or "").strip()
                if not raw_name:
                    continue
                ar_path = raw_name.replace("|", "/").rstrip("/")
                if not ar_path.startswith("/"):
                    ar_path = "/" + ar_path
                for setting in mod_settings.findall("Setting"):
                    if (setting.get("Name") or "").strip() == "BswImplSwVersion":
                        val = (setting.get("Value") or "").strip()
                        if val:
                            bsw_impl_versions[ar_path] = val
                        break

        return cls(
            dpa_path=dpa_path,
            derivative_uuid=derivative_uuid,
            derivative_name=derivative_name,
            sip_root=sip_root,
            module_definitions=module_definitions,
            ecuc_split_map=ecuc_split_map,
            main_ecuc_file=main_ecuc_file,
            active_modules=active_modules,
            bsw_impl_versions=bsw_impl_versions,
        )

    def resolve_ecuc_file(self, module_name: str) -> Optional[Path]:
        """Resolve the DaVinci ECUC ARXML path for ``module_name``, or main ECUC file."""
        rel = self.ecuc_split_map.get(module_name)
        if rel:
            norm = rel.replace("\\", "/")
            if norm.startswith("./"):
                norm = norm[2:]
            cand = (self.dpa_path.parent / norm).resolve()
            if cand.is_file():
                return cand
        if self.main_ecuc_file:
            norm_main = self.main_ecuc_file.replace("\\", "/")
            if norm_main.startswith("./"):
                norm_main = norm_main[2:]
            cand_main = (self.dpa_path.parent / norm_main).resolve()
            if cand_main.is_file():
                return cand_main
        return None

    def bsw_modules(self) -> List[str]:
        """Modules with /MICROSAR/ definition path."""
        return [name for name, defref in self.module_definitions.items()
                if defref.startswith("/MICROSAR/")]

    def mcal_modules(self) -> List[str]:
        """Modules with /THA6_AS440_FuSa/ or other chip-specific path."""
        return [name for name, defref in self.module_definitions.items()
                if not defref.startswith("/MICROSAR/") and not defref.startswith("/AUTOSAR/")]


class SipScanner:
    """Scan SIP tree and group files by content (DEFINITION-REF), not by path.

    Real layout: vBRS files may live in DemoComponents/vBaseEnv/BSWMD/, not DemoComponents/vBRS/.
    Solution: walk all Components/*/BSWMD and DemoComponents/*/BSWMD, parse each file,
    extract DEFINITION-REF, group by module name derived from def ref.
    """

    def __init__(self, sip_root: Path):
        self.sip_root = Path(sip_root)

    def scan_all_modules(self, derivative_uuid: Optional[str] = None) -> Dict[str, List["SipFile"]]:
        """Scan all BSWMD directories and return files grouped by module.

        Each file is classified:
        - role="def"   : contains ECUC-MODULE-DEF or BSW-IMPLEMENTATION
        - role="config": contains only ECUC-MODULE-CONFIGURATION-VALUES (pre/rec)

        Args:
            derivative_uuid: Optional derivative UUID used to filter chip-specific
                subdirectories via ``DerivativeMapping_<Module>.xml``.

        Returns:
            {module_name: [SipFile, ...]}
        """
        result: Dict[str, List[SipFile]] = {}

        for root_dir in ["Components", "DemoComponents"]:
            base = self.sip_root / root_dir
            if not base.exists():
                continue

            for component_dir in base.iterdir():
                if not component_dir.is_dir():
                    continue

                bswmd_dir = component_dir / "BSWMD"
                if not bswmd_dir.exists():
                    continue

                for arxml_file in bswmd_dir.rglob("*.arxml"):
                    try:
                        module, role = self._extract_module_and_role(arxml_file)
                        if module:
                            content = arxml_file.read_bytes()
                            sip_file = SipFile(
                                path=arxml_file,
                                module=module,
                                content=content,
                                role=role,
                            )
                            if module not in result:
                                result[module] = []
                            result[module].append(sip_file)
                    except (OSError, etree.XMLSyntaxError, AttributeError):
                        pass

        # Re-home IMPL-only modules (e.g. infixed MemMap ARXMLs without ECUC-MODULE-DEF
        # and without VENDOR-SPECIFIC-MODULE-DEF-REF) when their BSW-IMPLEMENTATION AR
        # path or unique package prefix matches a module that defines an ECUC-MODULE-DEF.
        def_modules: Dict[str, Dict[str, Set[str]]] = {}
        orphan_modules: Dict[str, Dict[str, Set[str]]] = {}
        for mod_name, sfiles in result.items():
            metas = [self._extract_file_partition_meta(sf) for sf in sfiles]
            has_def = any(m["def_paths"] for m in metas)
            info = {
                "def_paths": {dp for m in metas for dp in m["def_paths"]},
                "impl_ar_paths": {p for m in metas for p in m["impl_ar_paths"]},
                "impl_def_refs": {r for m in metas for r in m["impl_def_refs"]},
                "pkg_prefixes": {
                    dp.rsplit("/", 1)[0] for m in metas for dp in m["def_paths"] if "/" in dp
                },
            }
            if has_def:
                def_modules[mod_name] = info
            elif info["impl_ar_paths"] or info["impl_def_refs"]:
                orphan_modules[mod_name] = info

        for orphan_mod, oinfo in sorted(orphan_modules.items()):
            candidates: Set[str] = set()
            for def_mod, dinfo in def_modules.items():
                if (oinfo["impl_ar_paths"] & dinfo["impl_ar_paths"]) or (
                    oinfo["impl_def_refs"] & dinfo["def_paths"]
                ):
                    candidates.add(def_mod)
            if not candidates and oinfo["impl_ar_paths"]:
                orphan_prefixes = {
                    p.rsplit("/", 1)[0] for p in oinfo["impl_ar_paths"] if "/" in p
                }
                for def_mod, dinfo in def_modules.items():
                    if orphan_prefixes & dinfo["pkg_prefixes"]:
                        candidates.add(def_mod)
            if len(candidates) == 1:
                target_mod = next(iter(candidates))
                result[target_mod].extend(result.pop(orphan_mod))

        for module in list(result.keys()):
            result[module].sort(key=lambda f: str(f.path))
            if derivative_uuid:
                result[module] = self._filter_by_derivative_mapping(
                    module, result[module], derivative_uuid
                )

        return result

    def _filter_by_derivative_mapping(
        self, module_name: str, files: List[SipFile], derivative_uuid: str
    ) -> List[SipFile]:
        """Filter chip subdirectory files using ``DerivativeMapping_<Module>.xml``.

        Common module files directly under ``BSWMD/`` or ``BSWMD/<Module>/`` are
        always preserved; only files inside deeper chip-variant subdirectories are
        filtered by ``chip_folder``.
        """
        if not derivative_uuid or not files:
            return files

        mapping_file = (
            self.sip_root / "Components" / module_name / "GeneratorMsr" / f"DerivativeMapping_{module_name}.xml"
        )
        if not mapping_file.exists():
            mapping_file = (
                self.sip_root / "DemoComponents" / module_name / "GeneratorMsr" / f"DerivativeMapping_{module_name}.xml"
            )

        if not mapping_file.exists():
            return files

        try:
            chip_folder = self._get_chip_folder_from_mapping(mapping_file, derivative_uuid)
        except (etree.XMLSyntaxError, OSError) as exc:
            raise SipDerivativeMappingError(
                ar_path=f"/{module_name}",
                reason=f"Failed to parse {mapping_file.name}: {exc}",
                file1=mapping_file,
            ) from exc

        if not chip_folder:
            raise SipDerivativeMappingError(
                ar_path=f"/{module_name}",
                reason=f"Derivative UUID '{derivative_uuid}' not found in {mapping_file.name}",
                file1=mapping_file,
            )

        filtered: List[SipFile] = []
        for f in files:
            parts = f.path.parts
            # Check relative path after BSWMD[/<module_name>]
            rel_parts: Tuple[str, ...] = ()
            for idx, part in enumerate(parts):
                if part == "BSWMD":
                    rel_parts = parts[idx + 1 :]
                    break
            if rel_parts and rel_parts[0] == module_name:
                rel_parts = rel_parts[1:]

            # Keep top-level common files (len <= 1) or files matching chip_folder
            if len(rel_parts) <= 1 or chip_folder in rel_parts or chip_folder in str(f.path):
                filtered.append(f)
        return filtered

    def scan_module(self, module_name: str, derivative_uuid: Optional[str] = None) -> List[SipFile]:
        """Get all SipFile for one module, optionally filtered by derivative UUID.

        If derivative_uuid is provided, loads only the chip folder specified in
        DerivativeMapping_<Module>.xml for that UUID (plus common BSWMD files).

        Args:
            module_name: Module name (e.g., "Os", "vBRS")
            derivative_uuid: Optional derivative UUID to filter chip folder

        Returns:
            List of SipFile matching the module and optional derivative
        """
        # Filter only the requested module so unrelated modules' mapping errors do not block single-module scans.
        all_by_module = self.scan_all_modules(derivative_uuid=None)
        files = all_by_module.get(module_name, [])
        if derivative_uuid:
            return self._filter_by_derivative_mapping(module_name, files, derivative_uuid)
        return files

    @staticmethod
    def _get_chip_folder_from_mapping(mapping_file: Path, derivative_uuid: str) -> Optional[str]:
        """从 DerivativeMapping XML 提取 UUID 对应的 chip 文件夹名。"""
        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        tree = etree.parse(str(mapping_file), parser)
        root = tree.getroot()
        target_uuid = derivative_uuid.strip().lower()

        # Pattern 1: <Settings Name="<ChipFolder>"><Settings Name="<UUID>"><Setting Name="SIP_Folder" Value="..."/>
        for settings in root.iter():
            if not isinstance(settings.tag, str):
                continue
            if (settings.get("Name") or "").strip().lower() == target_uuid:
                for child in settings:
                    if (child.get("Name") or "") == "SIP_Folder" and child.get("Value"):
                        return child.get("Value").strip()
                parent = settings.getparent()
                if parent is not None and parent.get("Name"):
                    return parent.get("Name").strip()

        # Pattern 2: text node containing UUID
        for uuid_node in root.iter():
            if not isinstance(uuid_node.tag, str):
                continue
            if uuid_node.text and uuid_node.text.strip().lower() == target_uuid:
                chip_settings = uuid_node.getparent()
                if chip_settings is not None and chip_settings.get("Name"):
                    return chip_settings.get("Name").strip()

        return None

    @staticmethod
    def _extract_module_and_role(file_path: Path) -> tuple[Optional[str], str]:
        """Extract module name and classify the file's role.

        Returns:
            (module_name, role) where role is "def" if the file contains
            ECUC-MODULE-DEF or BSW-IMPLEMENTATION, or "config" if it only has
            CONFIGURATION-VALUES. Returns (None, "unknown") if no relevant elements.
        """
        try:
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(str(file_path), parser)
            root = tree.getroot()

            has_def = False
            module_from_def = None
            module_from_impl = None
            module_from_config = None

            for elem in root.iter():
                if not isinstance(elem.tag, str):
                    continue

                tag = elem.tag.split('}')[-1] if '}' in elem.tag else elem.tag

                if tag == "ECUC-MODULE-DEF":
                    has_def = True
                    for child in elem:
                        c_tag = child.tag.split('}')[-1] if isinstance(child.tag, str) and '}' in child.tag else child.tag
                        if c_tag == "SHORT-NAME" and child.text:
                            module_from_def = child.text.strip()
                            break

                elif tag == "BSW-IMPLEMENTATION" and not module_from_impl:
                    vsmd_ref = None
                    impl_sn = None
                    for child in elem:
                        c_tag = child.tag.split('}')[-1] if isinstance(child.tag, str) and '}' in child.tag else child.tag
                        if c_tag == "VENDOR-SPECIFIC-MODULE-DEF-REFS":
                            for ref_child in child:
                                rc_tag = ref_child.tag.split('}')[-1] if isinstance(ref_child.tag, str) and '}' in ref_child.tag else ref_child.tag
                                if rc_tag == "VENDOR-SPECIFIC-MODULE-DEF-REF" and ref_child.text:
                                    vsmd_ref = ref_child.text.strip().rstrip("/")
                                    break
                        elif c_tag == "SHORT-NAME" and child.text:
                            impl_sn = child.text.strip()
                    if vsmd_ref:
                        module_from_impl = vsmd_ref.rsplit("/", 1)[-1]
                    elif impl_sn:
                        module_from_impl = impl_sn[:-5] if impl_sn.endswith("_Impl") else impl_sn

                elif tag == "ECUC-MODULE-CONFIGURATION-VALUES" and not module_from_config:
                    for child in elem:
                        c_tag = child.tag.split('}')[-1] if isinstance(child.tag, str) and '}' in child.tag else child.tag
                        if c_tag == "DEFINITION-REF" and child.text:
                            module_from_config = child.text.rstrip("/").rsplit("/", 1)[-1]
                            break
                    if not module_from_config:
                        for child in elem:
                            c_tag = child.tag.split('}')[-1] if isinstance(child.tag, str) and '}' in child.tag else child.tag
                            if c_tag == "SHORT-NAME" and child.text:
                                module_from_config = child.text.strip()
                                break

            if has_def and module_from_def:
                return module_from_def, "def"
            if module_from_impl and not module_from_config:
                return module_from_impl, "def"
            if module_from_config:
                return module_from_config, "config"
            return None, "unknown"

        except (etree.XMLSyntaxError, OSError, AttributeError):
            return None, "unknown"

    @staticmethod
    def _extract_module_from_file(file_path: Path) -> Optional[str]:
        """Backward-compatible wrapper that returns module name."""
        name, _ = SipScanner._extract_module_and_role(file_path)
        return name

    @staticmethod
    def _element_ar_path(elem) -> Optional[str]:
        """Compute full AUTOSAR path ``/Pkg/.../ShortName`` for an ARXML element."""
        sn = None
        for child in elem:
            if isinstance(child.tag, str) and child.tag.rsplit("}", 1)[-1] == "SHORT-NAME" and child.text:
                sn = child.text.strip()
                break
        if not sn:
            return None
        segments = [sn]
        parent = elem.getparent()
        while parent is not None:
            if isinstance(parent.tag, str) and parent.tag.rsplit("}", 1)[-1] == "AR-PACKAGE":
                for child in parent:
                    if isinstance(child.tag, str) and child.tag.rsplit("}", 1)[-1] == "SHORT-NAME" and child.text:
                        segments.append(child.text.strip())
                        break
            parent = parent.getparent()
        return "/" + "/".join(reversed(segments))

    @staticmethod
    def _extract_file_partition_meta(sip_file: SipFile) -> Dict[str, List[str]]:
        """Extract definition, config, and BSW-IMPLEMENTATION paths/refs for variant partitioning."""
        empty: Dict[str, List[str]] = {
            "def_paths": [],
            "cfg_def_refs": [],
            "cfg_ar_paths": [],
            "impl_def_refs": [],
            "impl_ar_paths": [],
            "impl_cfg_refs": [],
        }
        if not sip_file.content:
            return empty
        try:
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            root = etree.fromstring(sip_file.content, parser)
        except (etree.XMLSyntaxError, ValueError):
            return empty

        def _append_unique(lst: List[str], value: Optional[str]) -> None:
            norm = value.strip().rstrip("/") if value else ""
            if norm and norm not in lst:
                lst.append(norm)

        meta = {k: [] for k in empty}
        for elem in root.iter():
            if not isinstance(elem.tag, str):
                continue
            tag = elem.tag.rsplit("}", 1)[-1]
            if tag == "ECUC-MODULE-DEF":
                _append_unique(meta["def_paths"], SipScanner._element_ar_path(elem))
            elif tag == "ECUC-MODULE-CONFIGURATION-VALUES":
                _append_unique(meta["cfg_ar_paths"], SipScanner._element_ar_path(elem))
                for child in elem:
                    if isinstance(child.tag, str) and child.tag.rsplit("}", 1)[-1] == "DEFINITION-REF" and child.text:
                        _append_unique(meta["cfg_def_refs"], child.text)
                        break
            elif tag == "BSW-IMPLEMENTATION":
                _append_unique(meta["impl_ar_paths"], SipScanner._element_ar_path(elem))
                for child in elem:
                    if not isinstance(child.tag, str):
                        continue
                    c_tag = child.tag.rsplit("}", 1)[-1]
                    if c_tag == "VENDOR-SPECIFIC-MODULE-DEF-REFS":
                        for ref_child in child:
                            if isinstance(ref_child.tag, str) and ref_child.tag.rsplit("}", 1)[-1] == "VENDOR-SPECIFIC-MODULE-DEF-REF" and ref_child.text:
                                _append_unique(meta["impl_def_refs"], ref_child.text)
                    elif c_tag in ("PRECONFIGURED-CONFIGURATION-REFS", "RECOMMENDED-CONFIGURATION-REFS"):
                        for ref_child in child:
                            if isinstance(ref_child.tag, str) and ref_child.tag.rsplit("}", 1)[-1] in (
                                "PRECONFIGURED-CONFIGURATION-REF",
                                "RECOMMENDED-CONFIGURATION-REF",
                            ) and ref_child.text:
                                _append_unique(meta["impl_cfg_refs"], ref_child.text)
        return meta

    @staticmethod
    def _extract_file_def_and_cfg_refs(sip_file: SipFile) -> Tuple[List[str], List[str]]:
        """Extract ECUC-MODULE-DEF AR paths and ECUC-MODULE-CONFIGURATION-VALUES DEFINITION-REFs."""
        meta = SipScanner._extract_file_partition_meta(sip_file)
        return meta["def_paths"], meta["cfg_def_refs"]

    @staticmethod
    def _package_dir_name_for_def(mod_name: str, def_path: str, used: Set[str]) -> str:
        """Choose a filesystem-safe, unique package folder name for a definition AR path."""
        import re

        segs = [s for s in def_path.strip("/").split("/") if s]
        if len(segs) >= 3:
            qual = segs[-2]
            candidate = qual if qual.lower().startswith(mod_name.lower()) else f"{mod_name}__{qual}"
        elif len(segs) == 2:
            candidate = mod_name if segs[0] == "MICROSAR" else f"{mod_name}__{segs[0]}"
        else:
            candidate = mod_name

        candidate = re.sub(r"[^A-Za-z0-9_-]", "_", candidate) or mod_name
        unique = candidate
        idx = 2
        while unique in used:
            unique = f"{candidate}_{idx}"
            idx += 1
        used.add(unique)
        return unique

    @staticmethod
    def partition_module_files(
        mod_name: str, files: List[SipFile]
    ) -> List[Tuple[str, str, List[SipFile]]]:
        """Partition SIP files of ``mod_name`` into separate packages when multiple distinct
        ``ECUC-MODULE-DEF`` AR paths exist across different single-def files (e.g. ``CanTrcv``
        having ``CanTrcv_GenericCan``, ``CanTrcv_Tle9255``, etc.).

        Returns ``[(package_dir_name, module_short_name, files)]``.
        """
        meta: List[Tuple[SipFile, Dict[str, List[str]]]] = [
            (sf, SipScanner._extract_file_partition_meta(sf))
            for sf in files
        ]

        def_groups: Dict[str, List[SipFile]] = {}
        def_group_metas: Dict[str, List[Dict[str, List[str]]]] = {}
        remaining: List[Tuple[SipFile, Dict[str, List[str]]]] = []
        for sf, m in meta:
            if len(m["def_paths"]) == 1:
                dp = m["def_paths"][0].rstrip("/")
                def_groups.setdefault(dp, []).append(sf)
                def_group_metas.setdefault(dp, []).append(m)
            else:
                remaining.append((sf, m))

        if len(def_groups) < 2:
            return [(mod_name, mod_name, list(files))]

        comp_to_defs: Dict[str, List[str]] = {}
        pkg_prefix_to_defs: Dict[str, List[str]] = {}
        impl_ar_to_defs: Dict[str, Set[str]] = {}
        impl_cfg_to_defs: Dict[str, Set[str]] = {}

        def _index_meta(dp: str, m: Dict[str, List[str]]) -> None:
            for ia in m["impl_ar_paths"]:
                impl_ar_to_defs.setdefault(ia, set()).add(dp)
            for cr in m["impl_cfg_refs"]:
                impl_cfg_to_defs.setdefault(cr, set()).add(dp)

        for dp in sorted(def_groups):
            if "/" in dp:
                pkg_prefix = dp.rsplit("/", 1)[0]
                pkg_prefix_to_defs.setdefault(pkg_prefix, [])
                if dp not in pkg_prefix_to_defs[pkg_prefix]:
                    pkg_prefix_to_defs[pkg_prefix].append(dp)
            for sf, m in zip(def_groups[dp], def_group_metas[dp]):
                _index_meta(dp, m)
                comp = SipMerger._component_name(sf.path)
                if comp:
                    lst = comp_to_defs.setdefault(comp, [])
                    if dp not in lst:
                        lst.append(dp)

        std_ref = f"/AUTOSAR/EcucDefs/{mod_name}"

        def _resolve_targets(sf: SipFile, m: Dict[str, List[str]], allow_fallback: bool) -> Tuple[List[str], bool]:
            explicit_refs = (set(m["cfg_def_refs"]) | set(m["impl_def_refs"])) - {std_ref}
            if explicit_refs:
                return [dp for dp in sorted(def_groups) if dp in explicit_refs], True

            matched: Set[str] = set()
            for ia in m["impl_ar_paths"]:
                matched.update(impl_ar_to_defs.get(ia, ()))
            for ca in m["cfg_ar_paths"]:
                matched.update(impl_cfg_to_defs.get(ca, ()))
            if matched:
                return sorted(matched), False

            if not allow_fallback:
                return [], False

            # Unique AR-package prefix match (e.g. /MICROSAR/CanTrcv_Tle9255)
            prefix_targets: Set[str] = set()
            for ar in m["impl_ar_paths"] + m["cfg_ar_paths"]:
                if "/" in ar:
                    prefix = ar.rsplit("/", 1)[0]
                    dps = pkg_prefix_to_defs.get(prefix, [])
                    if len(dps) == 1:
                        prefix_targets.add(dps[0])
            if prefix_targets:
                return sorted(prefix_targets), False

            comp = SipMerger._component_name(sf.path)
            if comp and comp in comp_to_defs:
                return list(comp_to_defs[comp]), False
            return [], False

        # Pass 1: assign explicitly-attributed fragments first so their BSW-IMPLEMENTATION
        # PRE/REC refs can inform Pass 2 for remaining fragments without explicit DEFINITION-REF.
        unresolved: List[Tuple[SipFile, Dict[str, List[str]]]] = []
        for sf, m in remaining:
            targets, had_explicit = _resolve_targets(sf, m, allow_fallback=False)
            if targets:
                for dp in targets:
                    def_groups[dp].append(sf)
                    _index_meta(dp, m)
            elif had_explicit:
                logger.warning(
                    "SIP partition for %s: skipping file %s with explicit ref(s) not matching any variant %s",
                    mod_name,
                    sf.path.name,
                    sorted((set(m["cfg_def_refs"]) | set(m["impl_def_refs"])) - {std_ref}),
                )
            else:
                unresolved.append((sf, m))

        for sf, m in unresolved:
            targets, _ = _resolve_targets(sf, m, allow_fallback=True)
            if targets:
                for dp in targets:
                    def_groups[dp].append(sf)
                    _index_meta(dp, m)
            else:
                logger.warning(
                    "SIP partition for %s: unmatched fragment %s left out of variant packages",
                    mod_name,
                    sf.path.name,
                )

        used_dirs: Set[str] = set()
        partitions: List[Tuple[str, str, List[SipFile]]] = []
        for dp in sorted(def_groups):
            pkg_dir = SipScanner._package_dir_name_for_def(mod_name, dp, used_dirs)
            grp_sorted = sorted(def_groups[dp], key=lambda f: str(f.path))
            partitions.append((pkg_dir, mod_name, grp_sorted))
        return partitions


class SipMerger:
    """Merge BSWMD files by AUTOSAR path with conflict detection."""

    _DEF_ELEMENT_TAGS = (
        "ECUC-MODULE-DEF",
        "BSW-IMPLEMENTATION",
        "ECUC-DEFINITION-COLLECTION",
        "MEMORY-SECTION-REFINEMENT",
    )
    _SCALAR_CONFLICT_FIELDS = (
        "SW-VERSION",
        "AR-RELEASE-VERSION",
        "VENDOR-ID",
        "VENDOR-API-INFIX",
    )
    _MERGEABLE_CONTAINER_TAGS = {
        "CONTAINERS",
        "RESOURCE-CONSUMPTION",
        "MEMORY-SECTIONS",
        "REQUIRED-ARTIFACTS",
        "ARTIFACT-DESCRIPTORS",
        "PRECONFIGURED-CONFIGURATION-REFS",
        "RECOMMENDED-CONFIGURATION-REFS",
        "SECTION-NAME-PREFIXS",
        "ADMIN-DATA",
        "SDGS",
    }

    @staticmethod
    def _component_name(path: Optional[Path]) -> Optional[str]:
        if path is None:
            return None
        parts = Path(path).parts
        for idx, part in enumerate(parts):
            if part in ("Components", "DemoComponents") and idx + 1 < len(parts):
                return f"{part}/{parts[idx + 1]}"
        return None

    @staticmethod
    def _clone(elem) -> Any:
        return etree.fromstring(etree.tostring(elem))

    @staticmethod
    def _elem_signature(elem) -> bytes:
        try:
            return etree.tostring(elem, method="c14n")
        except Exception:
            return etree.tostring(elem)

    @staticmethod
    def _merge_collection_children(target_wrapper, src_wrapper) -> None:
        """Append non-duplicate children from src_wrapper into target_wrapper."""
        seen_signatures = {
            SipMerger._elem_signature(c)
            for c in target_wrapper if isinstance(c.tag, str)
        }
        existing_by_sn = {}
        for child in target_wrapper:
            if not isinstance(child.tag, str):
                continue
            sn = SipMerger._child_text(child, "SHORT-NAME")
            if sn:
                existing_by_sn[(SipMerger._local(child.tag), sn)] = child

        for child in src_wrapper:
            if not isinstance(child.tag, str):
                continue
            ctag = SipMerger._local(child.tag)
            sn = SipMerger._child_text(child, "SHORT-NAME")
            if sn and (ctag, sn) in existing_by_sn:
                # Recurse if container wrapper (e.g. MEMORY-SECTIONS inside RESOURCE-CONSUMPTION)
                existing_child = existing_by_sn[(ctag, sn)]
                if ctag in ("RESOURCE-CONSUMPTION", "ECUC-PARAM-CONF-CONTAINER-DEF"):
                    SipMerger._merge_def_children(existing_child, child)
                continue
            sig = SipMerger._elem_signature(child)
            if sig not in seen_signatures:
                seen_signatures.add(sig)
                target_wrapper.append(SipMerger._clone(child))

    @staticmethod
    def _merge_def_children(target_elem, src_elem) -> None:
        """Merge container-like child blocks of two compatible definition/impl elements."""
        existing_wrappers: Dict[str, Any] = {}
        for child in target_elem:
            if isinstance(child.tag, str):
                existing_wrappers[SipMerger._local(child.tag)] = child

        for child in src_elem:
            if not isinstance(child.tag, str):
                continue
            ctag = SipMerger._local(child.tag)
            if ctag in ("SHORT-NAME", *SipMerger._SCALAR_CONFLICT_FIELDS):
                if ctag not in existing_wrappers and (child.text or "").strip():
                    target_elem.append(SipMerger._clone(child))
                continue
            if ctag in SipMerger._MERGEABLE_CONTAINER_TAGS:
                if ctag not in existing_wrappers:
                    cloned = SipMerger._clone(child)
                    target_elem.append(cloned)
                    existing_wrappers[ctag] = cloned
                else:
                    if ctag == "RESOURCE-CONSUMPTION":
                        SipMerger._merge_def_children(existing_wrappers[ctag], child)
                    else:
                        SipMerger._merge_collection_children(existing_wrappers[ctag], child)
            elif ctag not in existing_wrappers:
                cloned = SipMerger._clone(child)
                target_elem.append(cloned)
                existing_wrappers[ctag] = cloned

    @staticmethod
    def _build_arxml_from_package_elements(
        root_tag: str,
        nsmap: Optional[dict],
        pkg_elements: Dict[str, List[Any]],
    ) -> bytes:
        """Assemble a normalized AUTOSAR XML document from {pkg_path: [elem, ...]}."""
        out_root = etree.Element(root_tag, nsmap=nsmap)
        root_pkgs = etree.SubElement(out_root, SipMerger._ns_tag(root_tag, "AR-PACKAGES"))
        pkg_nodes: Dict[str, Any] = {}

        def _ensure_package(pkg_path: str):
            norm = pkg_path.strip("/")
            if not norm:
                norm = "AUTOSAR"
            full = "/" + norm
            if full in pkg_nodes:
                return pkg_nodes[full]
            segments = norm.split("/")
            parent_pkgs = root_pkgs
            acc = ""
            node = None
            for seg in segments:
                acc = f"{acc}/{seg}"
                if acc not in pkg_nodes:
                    pkg_el = etree.SubElement(parent_pkgs, SipMerger._ns_tag(root_tag, "AR-PACKAGE"))
                    etree.SubElement(pkg_el, SipMerger._ns_tag(root_tag, "SHORT-NAME")).text = seg
                    pkg_nodes[acc] = pkg_el
                node = pkg_nodes[acc]
                # Find or prepare nested AR-PACKAGES only if more segments follow
                sub_pkgs = None
                for ch in node:
                    if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "AR-PACKAGES":
                        sub_pkgs = ch
                        break
                if sub_pkgs is None:
                    sub_pkgs = etree.SubElement(node, SipMerger._ns_tag(root_tag, "AR-PACKAGES"))
                parent_pkgs = sub_pkgs
            return node

        # Track order deterministically; clean unused trailing AR-PACKAGES wrappers afterward
        for pkg_path in sorted(pkg_elements):
            elems = pkg_elements[pkg_path]
            if not elems:
                continue
            pkg_el = _ensure_package(pkg_path)
            elements_el = None
            for ch in pkg_el:
                if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "ELEMENTS":
                    elements_el = ch
                    break
            if elements_el is None:
                # Insert ELEMENTS before AR-PACKAGES if AR-PACKAGES exists
                ar_pkgs_idx = next(
                    (i for i, ch in enumerate(pkg_el)
                     if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "AR-PACKAGES"),
                    None,
                )
                elements_el = etree.Element(SipMerger._ns_tag(root_tag, "ELEMENTS"))
                if ar_pkgs_idx is not None:
                    pkg_el.insert(ar_pkgs_idx, elements_el)
                else:
                    pkg_el.append(elements_el)
            for e in elems:
                elements_el.append(e)

        # Prune empty AR-PACKAGES elements
        for el in list(out_root.iter()):
            if isinstance(el.tag, str) and SipMerger._local(el.tag) == "AR-PACKAGES" and len(el) == 0:
                parent = el.getparent()
                if parent is not None:
                    parent.remove(el)

        return etree.tostring(out_root, encoding="utf-8", xml_declaration=True, pretty_print=True)

    @staticmethod
    def merge_module(files: List[SipFile], module_name: str) -> Optional[bytes]:
        """Merge multiple ARXML files for one module by AUTOSAR path.

        Raises SipMergeError on element type mismatch, scalar field conflicts,
        or duplicate ECUC-MODULE-DEF across different components.
        """
        if not files:
            return None

        merged = SipMerger.merge_definition(files, module_name)
        if merged is not None:
            return merged
        return files[0].content

    @staticmethod
    def merge_definition(files: List[SipFile], module_name: str) -> Optional[bytes]:
        """Merge ECUC-MODULE-DEF / BSW-IMPLEMENTATION elements by AUTOSAR path.

        Detects conflicts:
        - Different element types at the same AUTOSAR path -> SipMergeError
        - Differing single-value fields (SW-VERSION, AR-RELEASE-VERSION, VENDOR-ID) -> SipMergeError
        - Duplicate ECUC-MODULE-DEF from different components -> SipMergeError
        """
        elements_by_ar_path: Dict[str, Tuple[str, Any, Optional[Path]]] = {}
        pkg_elements: Dict[str, List[Any]] = {}
        nsmap = None
        root_tag = None

        for sip_file in files:
            if not sip_file.content:
                continue
            try:
                parser = etree.XMLParser(resolve_entities=False, no_network=True)
                root = etree.fromstring(sip_file.content, parser)
            except (etree.XMLSyntaxError, ValueError):
                continue

            if nsmap is None:
                nsmap = root.nsmap
                root_tag = root.tag

            for pkg in SipMerger._walk_packages(root):
                pkg_path = SipMerger._package_path(pkg)
                elements_el = None
                for ch in pkg:
                    if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "ELEMENTS":
                        elements_el = ch
                        break
                if elements_el is None:
                    continue

                for elem in elements_el:
                    if not isinstance(elem.tag, str):
                        continue
                    elem_tag = SipMerger._local(elem.tag)
                    if elem_tag == "ECUC-MODULE-CONFIGURATION-VALUES":
                        continue
                    if elem_tag not in SipMerger._DEF_ELEMENT_TAGS and not SipMerger._package_has_definition(pkg):
                        continue

                    sn = SipMerger._child_text(elem, "SHORT-NAME")
                    ar_path = f"{pkg_path}/{sn}" if sn else f"{pkg_path}/__{elem_tag}"

                    if ar_path not in elements_by_ar_path:
                        cloned = SipMerger._clone(elem)
                        elements_by_ar_path[ar_path] = (pkg_path, cloned, sip_file.path)
                        pkg_elements.setdefault(pkg_path, []).append(cloned)
                        continue

                    _, prev_elem, prev_file = elements_by_ar_path[ar_path]
                    if prev_file == sip_file.path:
                        continue

                    prev_tag = SipMerger._local(prev_elem.tag)
                    if prev_tag != elem_tag:
                        raise SipMergeError(
                            ar_path,
                            f"Element type mismatch ({prev_tag} vs {elem_tag})",
                            prev_file,
                            sip_file.path,
                        )

                    if elem_tag == "ECUC-MODULE-DEF":
                        c1 = SipMerger._component_name(prev_file)
                        c2 = SipMerger._component_name(sip_file.path)
                        if c1 and c2 and c1 != c2:
                            raise SipMergeError(
                                ar_path,
                                f"Duplicate ECUC-MODULE-DEF across components ({c1} vs {c2})",
                                prev_file,
                                sip_file.path,
                            )

                    for field_name in SipMerger._SCALAR_CONFLICT_FIELDS:
                        v1 = SipMerger._child_text(prev_elem, field_name)
                        v2 = SipMerger._child_text(elem, field_name)
                        if v1 is not None and v2 is not None and v1 != v2:
                            raise SipMergeError(
                                ar_path,
                                f"Conflicting {field_name} ({v1!r} vs {v2!r})",
                                prev_file,
                                sip_file.path,
                            )

                    SipMerger._merge_def_children(prev_elem, elem)

        if not pkg_elements or root_tag is None:
            return None

        return SipMerger._build_arxml_from_package_elements(root_tag, nsmap, pkg_elements)

    @staticmethod
    def _merge_xml_container_value(target_containers_el, src_container_el) -> None:
        """Recursively merge <ECUC-CONTAINER-VALUE> nodes by <SHORT-NAME>."""
        src_sn = SipMerger._child_text(src_container_el, "SHORT-NAME")
        existing = None
        if src_sn:
            for cand in target_containers_el:
                if not isinstance(cand.tag, str) or SipMerger._local(cand.tag) != "ECUC-CONTAINER-VALUE":
                    continue
                if SipMerger._child_text(cand, "SHORT-NAME") == src_sn:
                    existing = cand
                    break

        if existing is None:
            target_containers_el.append(SipMerger._clone(src_container_el))
            return

        def _ensure_child(parent, local_name: str):
            for ch in parent:
                if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == local_name:
                    return ch
            return etree.SubElement(parent, SipMerger._ns_tag(parent.tag, local_name))

        def _merge_value_children(
            src_wrapper,
            wrapper_tag: str,
            value_tag: str,
            kind_label: str,
        ) -> None:
            tgt_wrapper = _ensure_child(existing, wrapper_tag)
            tgt_elems = [e for e in tgt_wrapper if isinstance(e.tag, str)]
            src_elems = [e for e in src_wrapper if isinstance(e.tag, str)]

            # Count occurrences per DEFINITION-REF inside each side to detect multi-valued items
            tgt_def_counts: Dict[Optional[str], int] = {}
            for e in tgt_elems:
                d = SipMerger._child_text(e, "DEFINITION-REF")
                tgt_def_counts[d] = tgt_def_counts.get(d, 0) + 1
            src_def_counts: Dict[Optional[str], int] = {}
            for e in src_elems:
                d = SipMerger._child_text(e, "DEFINITION-REF")
                src_def_counts[d] = src_def_counts.get(d, 0) + 1

            seen_full = set()
            by_slot: Dict[Tuple[Optional[str], Optional[str]], Optional[str]] = {}
            for e in tgt_elems:
                d = SipMerger._child_text(e, "DEFINITION-REF")
                idx = SipMerger._child_text(e, "INDEX")
                val = SipMerger._child_text(e, value_tag)
                seen_full.add((d, idx, val))
                by_slot[(d, idx)] = val

            for e in src_elems:
                d = SipMerger._child_text(e, "DEFINITION-REF")
                idx = SipMerger._child_text(e, "INDEX")
                val = SipMerger._child_text(e, value_tag)
                full_sig = (d, idx, val)
                if full_sig in seen_full:
                    continue
                is_multi = (
                    idx is None
                    and (tgt_def_counts.get(d, 0) > 1 or src_def_counts.get(d, 0) > 1)
                )
                if not is_multi and (d, idx) in by_slot and by_slot[(d, idx)] != val:
                    raise SipMergeError(
                        f"{src_sn or ''}/{d or ''}",
                        f"Conflicting {kind_label} value ({by_slot[(d, idx)]!r} vs {val!r})",
                    )
                seen_full.add(full_sig)
                by_slot[(d, idx)] = val
                tgt_wrapper.append(SipMerger._clone(e))

        # Merge PARAMETER-VALUES
        src_params = next(
            (ch for ch in src_container_el
             if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "PARAMETER-VALUES"),
            None,
        )
        if src_params is not None:
            _merge_value_children(src_params, "PARAMETER-VALUES", "VALUE", "parameter")

        # Merge REFERENCE-VALUES
        src_refs = next(
            (ch for ch in src_container_el
             if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "REFERENCE-VALUES"),
            None,
        )
        if src_refs is not None:
            _merge_value_children(src_refs, "REFERENCE-VALUES", "VALUE-REF", "reference")

        # Merge SUB-CONTAINERS recursively
        src_subs = next(
            (ch for ch in src_container_el
             if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "SUB-CONTAINERS"),
            None,
        )
        if src_subs is not None:
            tgt_subs = _ensure_child(existing, "SUB-CONTAINERS")
            for sub in src_subs:
                if isinstance(sub.tag, str) and SipMerger._local(sub.tag) == "ECUC-CONTAINER-VALUE":
                    SipMerger._merge_xml_container_value(tgt_subs, sub)

    @staticmethod
    def _merge_xml_value_collection(target_elem, src_elem) -> None:
        """Merge a same-path ECUC-MODULE-CONFIGURATION-VALUES fragment into target_elem."""
        src_variant = SipMerger._child_text(src_elem, "IMPLEMENTATION-CONFIG-VARIANT")
        if src_variant and SipMerger._child_text(target_elem, "IMPLEMENTATION-CONFIG-VARIANT") is None:
            v_el = etree.Element(SipMerger._ns_tag(target_elem.tag, "IMPLEMENTATION-CONFIG-VARIANT"))
            v_el.text = src_variant
            target_elem.append(v_el)

        src_containers = next(
            (ch for ch in src_elem
             if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "CONTAINERS"),
            None,
        )
        if src_containers is None:
            return

        tgt_containers = next(
            (ch for ch in target_elem
             if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "CONTAINERS"),
            None,
        )
        if tgt_containers is None:
            tgt_containers = etree.SubElement(target_elem, SipMerger._ns_tag(target_elem.tag, "CONTAINERS"))

        for c in src_containers:
            if isinstance(c.tag, str) and SipMerger._local(c.tag) == "ECUC-CONTAINER-VALUE":
                SipMerger._merge_xml_container_value(tgt_containers, c)

    @staticmethod
    def extract_value_collections(files: List[SipFile], module_name: str) -> Dict[str, bytes]:
        """Split the value collections of all files into Pre / Rec / other documents.

        Same-path ``ECUC-MODULE-CONFIGURATION-VALUES`` across multiple files (e.g.
        multi-file Pre/Rec fragments) are merged recursively and preserved in their
        original ``AR-PACKAGE`` hierarchy.
        """
        pre_paths: Set[str] = set()
        rec_paths: Set[str] = set()
        collections: Dict[str, Tuple[str, Any]] = {}
        nsmap = None
        root_tag = None

        for sip_file in files:
            if not sip_file.content:
                continue
            try:
                parser = etree.XMLParser(resolve_entities=False, no_network=True)
                root = etree.fromstring(sip_file.content, parser)
            except (etree.XMLSyntaxError, ValueError):
                continue

            if nsmap is None:
                nsmap = root.nsmap
                root_tag = root.tag

            # Learn the Pre/Rec paths from every BSW-IMPLEMENTATION in the module
            for elem in root.iter():
                if not isinstance(elem.tag, str):
                    continue
                tag = SipMerger._local(elem.tag)
                if tag == "BSW-IMPLEMENTATION":
                    for child in elem.iter():
                        if not isinstance(child.tag, str):
                            continue
                        c_tag = SipMerger._local(child.tag)
                        if c_tag == "PRECONFIGURED-CONFIGURATION-REF" and child.text:
                            pre_paths.add(child.text.strip())
                        elif c_tag == "RECOMMENDED-CONFIGURATION-REF" and child.text:
                            rec_paths.add(child.text.strip())

            # Collect and merge every value collection with its full AR path
            for pkg in SipMerger._walk_packages(root):
                pkg_path = SipMerger._package_path(pkg)
                elements_el = next(
                    (ch for ch in pkg if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "ELEMENTS"),
                    None,
                )
                if elements_el is None:
                    continue
                for elem in elements_el:
                    if not isinstance(elem.tag, str):
                        continue
                    if SipMerger._local(elem.tag) != "ECUC-MODULE-CONFIGURATION-VALUES":
                        continue
                    short = SipMerger._child_text(elem, "SHORT-NAME")
                    if not short:
                        continue
                    ar_path = f"{pkg_path}/{short}" if pkg_path else f"/{short}"
                    if ar_path not in collections:
                        collections[ar_path] = (pkg_path or f"/{module_name}", SipMerger._clone(elem))
                    else:
                        SipMerger._merge_xml_value_collection(collections[ar_path][1], elem)

        if not collections or root_tag is None:
            return {}

        buckets: Dict[str, Dict[str, List[Any]]] = {"pre": {}, "rec": {}, "values": {}}
        for ar_path in sorted(collections):
            pkg_path, elem = collections[ar_path]
            if ar_path in pre_paths:
                target_bucket = buckets["pre"]
            elif ar_path in rec_paths:
                target_bucket = buckets["rec"]
            else:
                target_bucket = buckets["values"]
            target_bucket.setdefault(pkg_path, []).append(elem)

        result: Dict[str, bytes] = {}
        for role, grouped in buckets.items():
            if not grouped:
                continue
            result[role] = SipMerger._build_arxml_from_package_elements(root_tag, nsmap, grouped)
        return result

    @staticmethod
    def extract_bsw_implementation_metadata(files: List[SipFile]) -> Dict[str, Any]:
        """Extract structured BSW-IMPLEMENTATION metadata (W10) from SIP files.

        Returns a dict containing ``ar_path``, ``short_name``, ``sw_version``,
        ``ar_release_version``, ``vendor_id``, ``vendor_api_infix``,
        ``memory_sections``, ``required_artifacts``, ``preconfigured_refs``,
        and ``recommended_refs``. Empty dict if no ``BSW-IMPLEMENTATION`` is present.
        """
        meta: Dict[str, Any] = {}
        mem_sections: List[Dict[str, Any]] = []
        seen_sections: Set[str] = set()
        artifacts: List[Dict[str, Any]] = []
        seen_artifacts: Set[str] = set()
        pre_refs: List[str] = []
        rec_refs: List[str] = []

        for sip_file in files:
            if not sip_file.content:
                continue
            try:
                parser = etree.XMLParser(resolve_entities=False, no_network=True)
                root = etree.fromstring(sip_file.content, parser)
            except (etree.XMLSyntaxError, ValueError):
                continue

            for pkg in SipMerger._walk_packages(root):
                pkg_path = SipMerger._package_path(pkg)
                elements_el = next(
                    (ch for ch in pkg if isinstance(ch.tag, str) and SipMerger._local(ch.tag) == "ELEMENTS"),
                    None,
                )
                if elements_el is None:
                    continue
                for elem in elements_el:
                    if not isinstance(elem.tag, str) or SipMerger._local(elem.tag) != "BSW-IMPLEMENTATION":
                        continue
                    sn = SipMerger._child_text(elem, "SHORT-NAME")
                    if sn and "short_name" not in meta:
                        meta["short_name"] = sn
                        meta["ar_path"] = f"{pkg_path}/{sn}" if pkg_path else f"/{sn}"
                    for field_key, tag_name in (
                        ("sw_version", "SW-VERSION"),
                        ("ar_release_version", "AR-RELEASE-VERSION"),
                        ("vendor_id", "VENDOR-ID"),
                        ("vendor_api_infix", "VENDOR-API-INFIX"),
                    ):
                        val = SipMerger._child_text(elem, tag_name)
                        if val and field_key not in meta:
                            meta[field_key] = val

                    for sub in elem.iter():
                        if not isinstance(sub.tag, str):
                            continue
                        stag = SipMerger._local(sub.tag)
                        if stag == "MEMORY-SECTION":
                            sec_name = SipMerger._child_text(sub, "SHORT-NAME") or ""
                            if sec_name and sec_name not in seen_sections:
                                seen_sections.add(sec_name)
                                opts = [
                                    (o.text or "").strip()
                                    for o in sub.iter()
                                    if isinstance(o.tag, str)
                                    and SipMerger._local(o.tag) == "OPTION"
                                    and (o.text or "").strip()
                                ]
                                mem_sections.append({
                                    "short_name": sec_name,
                                    "alignment": SipMerger._child_text(sub, "ALIGNMENT"),
                                    "sw_addr_method_ref": SipMerger._child_text(sub, "SW-ADDRMETHOD-REF"),
                                    "options": opts,
                                })
                        elif stag == "AUTOSAR-ENGINEERING-OBJECT":
                            art_label = SipMerger._child_text(sub, "SHORT-LABEL") or SipMerger._child_text(sub, "SHORT-NAME") or ""
                            art_cat = SipMerger._child_text(sub, "CATEGORY")
                            art_key = f"{art_label}|{art_cat or ''}"
                            if art_label and art_key not in seen_artifacts:
                                seen_artifacts.add(art_key)
                                artifacts.append({
                                    "short_label": art_label,
                                    "category": art_cat,
                                })
                        elif stag == "PRECONFIGURED-CONFIGURATION-REF" and sub.text:
                            ref = sub.text.strip()
                            if ref and ref not in pre_refs:
                                pre_refs.append(ref)
                        elif stag == "RECOMMENDED-CONFIGURATION-REF" and sub.text:
                            ref = sub.text.strip()
                            if ref and ref not in rec_refs:
                                rec_refs.append(ref)

        if not meta and not mem_sections and not artifacts and not pre_refs and not rec_refs:
            return {}

        meta["memory_sections"] = mem_sections
        meta["required_artifacts"] = artifacts
        meta["preconfigured_refs"] = pre_refs
        meta["recommended_refs"] = rec_refs
        return meta

    # --- small XML helpers -------------------------------------------------------------

    @staticmethod
    def _local(tag) -> str:
        return tag.split('}')[-1] if isinstance(tag, str) and '}' in tag else (tag if isinstance(tag, str) else "")

    @staticmethod
    def _ns_tag(root_tag: str, name: str) -> str:
        if isinstance(root_tag, str) and root_tag.startswith('{'):
            return '{' + root_tag[1:].split('}')[0] + '}' + name
        return name

    @staticmethod
    def _walk_packages(root):
        """Every AR-PACKAGE in document order (nested ones included)."""
        for elem in root.iter():
            if isinstance(elem.tag, str) and SipMerger._local(elem.tag) == "AR-PACKAGE":
                yield elem

    @staticmethod
    def _package_path(pkg) -> str:
        """Full AR path of a package, e.g. ``/MICROSAR/VTT``."""
        names = []
        node = pkg
        while node is not None:
            if isinstance(node.tag, str) and SipMerger._local(node.tag) == "AR-PACKAGE":
                short = SipMerger._child_text(node, "SHORT-NAME")
                if short:
                    names.append(short)
            node = node.getparent()
        return '/' + '/'.join(reversed(names)) if names else ''

    @staticmethod
    def _child_text(elem, name: str) -> Optional[str]:
        for child in elem:
            if isinstance(child.tag, str) and SipMerger._local(child.tag) == name:
                return (child.text or '').strip() or None
        return None

    @staticmethod
    def _package_has_definition(pkg) -> bool:
        for child in pkg:
            if not isinstance(child.tag, str):
                continue
            if SipMerger._local(child.tag) != "ELEMENTS":
                continue
            for elem in child:
                if not isinstance(elem.tag, str):
                    continue
                if SipMerger._local(elem.tag) in (
                        "ECUC-MODULE-DEF", "BSW-IMPLEMENTATION", "ECUC-DEFINITION-COLLECTION"):
                    return True
        return False

    @staticmethod
    def separate_definition_and_config(merged_arxml: bytes) -> tuple[Optional[bytes], Optional[bytes], Optional[bytes]]:
        """Backward-compatible helper: split one document into def / pre / rec.

        Only used by older call sites; the CLI uses :meth:`merge_definition` and
        :meth:`extract_value_collections`, which work across several files.
        """
        try:
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            root = etree.fromstring(merged_arxml, parser)
            nsmap, root_tag = root.nsmap, root.tag

            # Build Pre/Rec path sets from BSW-IMPLEMENTATION references
            pre_paths: set = set()
            rec_paths: set = set()
            for elem in root.iter():
                if not isinstance(elem.tag, str):
                    continue
                tag = SipMerger._local(elem.tag)
                if tag == "BSW-IMPLEMENTATION":
                    for child in elem.iter():
                        if not isinstance(child.tag, str):
                            continue
                        c_tag = SipMerger._local(child.tag)
                        if c_tag == "PRECONFIGURED-CONFIGURATION-REF" and child.text:
                            pre_paths.add(child.text.strip())
                        elif c_tag == "RECOMMENDED-CONFIGURATION-REF" and child.text:
                            rec_paths.add(child.text.strip())

            def_has = False
            pre_elems: list = []
            rec_elems: list = []

            # Walk packages: separate definitions from value collections
            def_pkgs: list = []
            for pkg in SipMerger._walk_packages(root):
                has_def_child = SipMerger._package_has_definition(pkg)
                pkg_path = SipMerger._package_path(pkg)

                # Strip ECUC-MODULE-CONFIGURATION-VALUES out of def; collect them separately
                clean_pkg = etree.Element(pkg.tag, nsmap=pkg.nsmap)
                for child in pkg:
                    # Skip non-element nodes (comments, processing instructions) — their tag is a function
                    if not isinstance(child.tag, str):
                        continue
                    c_tag = SipMerger._local(child.tag)
                    if c_tag == "ELEMENTS":
                        elements_elem = etree.SubElement(clean_pkg, child.tag)
                        for sub in child:
                            # Skip non-element nodes
                            if not isinstance(sub.tag, str):
                                continue
                            s_tag = SipMerger._local(sub.tag)
                            if s_tag == "ECUC-MODULE-CONFIGURATION-VALUES":
                                # Route to pre/rec
                                sn = SipMerger._child_text(sub, "SHORT-NAME") or ""
                                ar_path = f"{pkg_path}/{sn}" if sn else ""
                                if ar_path and ar_path in pre_paths:
                                    pre_elems.append((etree.fromstring(etree.tostring(sub)), pkg_path))
                                elif ar_path and ar_path in rec_paths:
                                    rec_elems.append((etree.fromstring(etree.tostring(sub)), pkg_path))
                                # (If role unknown, skip — config files handle it)
                            else:
                                if s_tag in ("ECUC-MODULE-DEF", "BSW-IMPLEMENTATION", "ECUC-DEFINITION-COLLECTION"):
                                    def_has = True
                                elements_elem.append(etree.fromstring(etree.tostring(sub)))
                    else:
                        clean_pkg.append(etree.fromstring(etree.tostring(child)))

                if has_def_child:
                    def_pkgs.append(clean_pkg)

            # Build output documents
            def _make_doc(pairs_or_pkgs, is_packages=False):
                out = etree.Element(root_tag, nsmap=nsmap)
                packages = etree.SubElement(out, SipMerger._ns_tag(root_tag, "AR-PACKAGES"))
                if is_packages:
                    for pkg in pairs_or_pkgs:
                        packages.append(pkg)
                else:
                    # Group by package path
                    by_path: dict = {}
                    for elem, pkg_path in pairs_or_pkgs:
                        if pkg_path not in by_path:
                            by_path[pkg_path] = []
                        by_path[pkg_path].append(elem)
                    for path, elems in sorted(by_path.items()):
                        pkg_elem = etree.SubElement(packages, SipMerger._ns_tag(root_tag, "AR-PACKAGE"))
                        name = path.rsplit("/", 1)[-1] if "/" in path else path
                        etree.SubElement(pkg_elem, SipMerger._ns_tag(root_tag, "SHORT-NAME")).text = name
                        elements_elem = etree.SubElement(pkg_elem, SipMerger._ns_tag(root_tag, "ELEMENTS"))
                        for e in elems:
                            elements_elem.append(e)
                return etree.tostring(out, encoding='utf-8', xml_declaration=True, pretty_print=True)

            def_bytes = _make_doc(def_pkgs, is_packages=True) if def_has else None
            pre_bytes = _make_doc(pre_elems) if pre_elems else None
            rec_bytes = _make_doc(rec_elems) if rec_elems else None

            return def_bytes, pre_bytes, rec_bytes

        except Exception as e:
            logger.debug(f"Failed to separate ARXML: {e}")
            return None, None, None


class SipPackageWriter:
    """Write module package with correct schema."""

    @staticmethod
    def write_package(
        module_name: str,
        definition_content: bytes,
        pre_config: Optional[bytes] = None,
        rec_config: Optional[bytes] = None,
        output_dir: Optional[Path] = None,
        source_files: Optional[List[str]] = None,
        impl_metadata: Optional[Dict[str, Any]] = None,
        implementation_dir: Optional[str] = None,
        source_kind: str = "davinci",
        package_dir_name: Optional[str] = None,
    ) -> Path:
        """Write a module package with definition, pre, and rec unified under config/.

        Args:
            module_name: Module name (e.g., "Os")
            definition_content: ARXML bytes of ECUC-MODULE-DEF
            pre_config: Optional pre configuration ARXML
            rec_config: Optional rec configuration ARXML
            output_dir: Output directory; defaults to ./packages/<package_dir_name or module_name>
            source_files: Optional list of contributing SIP source file paths
            impl_metadata: Optional BSW-IMPLEMENTATION metadata dict
            implementation_dir: Optional POSIX path to SIP Implementation/ directory
            source_kind: Origin tag recorded under manifest ``origin.source``
            package_dir_name: Optional subdirectory name overriding ``module_name`` when
                multiple variant definitions share a module short name (e.g., ``CanTrcv_Tle9255``)

        Returns:
            Path to package root
        """
        dir_name = package_dir_name or module_name
        if output_dir is None:
            output_dir = Path.cwd() / "packages" / dir_name
        else:
            output_dir = Path(output_dir) / dir_name

        output_dir.mkdir(parents=True, exist_ok=True)
        config_dir = output_dir / "config"
        config_dir.mkdir(exist_ok=True)

        # Keep definition, Pre, and Rec files unified under config/
        files_list = []
        pre_list = []
        rec_list = []

        if definition_content:
            def_path = config_dir / f"{module_name}.arxml"
            def_path.write_bytes(definition_content)
            files_list.append(f"config/{module_name}.arxml")

        # Write pre/rec to config/ directory and index their AUTOSAR paths for manifest
        if pre_config:
            pre_path = config_dir / f"{module_name}_Pre.arxml"
            pre_path.write_bytes(pre_config)
            files_list.append(f"config/{module_name}_Pre.arxml")
            pre_list.extend(SipPackageWriter._extract_collection_paths(pre_config))

        if rec_config:
            rec_path = config_dir / f"{module_name}_Rec.arxml"
            rec_path.write_bytes(rec_config)
            files_list.append(f"config/{module_name}_Rec.arxml")
            rec_list.extend(SipPackageWriter._extract_collection_paths(rec_config))

        # Extract AUTOSAR definition path from definition content
        def_ar_path = SipPackageWriter._extract_definition_path(definition_content, module_name) if definition_content else None
        if not def_ar_path:
            # Fallback: guess /MICROSAR/<Module>
            def_ar_path = f"/MICROSAR/{module_name}"

        if impl_metadata is None and definition_content:
            impl_metadata = SipMerger.extract_bsw_implementation_metadata(
                [SipFile(path=Path(f"{module_name}.arxml"), module=module_name, content=definition_content)]
            )

        manifest_path = output_dir / "module.json"
        existing_templates: Optional[str] = None
        if manifest_path.is_file():
            try:
                prev_data = json.loads(manifest_path.read_text(encoding="utf-8"))
                prev_templates = prev_data.get("templates")
                if isinstance(prev_templates, str) and prev_templates.strip():
                    if (output_dir / prev_templates).is_dir():
                        existing_templates = prev_templates
            except (OSError, ValueError, TypeError):
                pass

        # Write module.json matching load_manifest schema (replaces separate sources.json)
        manifest: Dict[str, Any] = {
            "schema": 1,
            "module": module_name,
            "definition": def_ar_path,
            "files": files_list,
            "pre": pre_list,
            "rec": rec_list,
        }
        if existing_templates is not None:
            manifest["templates"] = existing_templates
        elif (output_dir / "templates").is_dir():
            manifest["templates"] = "templates"
        if impl_metadata and impl_metadata.get("ar_path"):
            manifest["implementation_path"] = impl_metadata["ar_path"]
        if impl_metadata and impl_metadata.get("sw_version"):
            manifest["version"] = impl_metadata["sw_version"]
        if implementation_dir:
            manifest["implementation"] = str(implementation_dir).strip().replace("\\", "/")

        origin: Dict[str, Any] = {"source": source_kind}
        if source_files is not None:
            origin["source_files"] = sorted(str(s) for s in source_files)
        if impl_metadata:
            origin["implementation"] = impl_metadata
            if impl_metadata.get("sw_version"):
                origin["sw_version"] = impl_metadata["sw_version"]
        manifest["origin"] = origin

        with open(manifest_path, "w", encoding="utf-8") as f:
            json.dump(manifest, f, indent=2, sort_keys=True, ensure_ascii=False)
            f.write("\n")

        return output_dir

    @staticmethod
    def _extract_collection_paths(content: bytes) -> List[str]:
        """Extract full AUTOSAR paths of ECUC-MODULE-CONFIGURATION-VALUES elements."""
        try:
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            root = etree.fromstring(content, parser)
        except (etree.XMLSyntaxError, ValueError):
            return []

        paths: List[str] = []
        for elem in root.iter():
            if not isinstance(elem.tag, str) or SipMerger._local(elem.tag) != "ECUC-MODULE-CONFIGURATION-VALUES":
                continue
            sn = SipMerger._child_text(elem, "SHORT-NAME")
            if not sn:
                continue
            segments = [sn]
            parent = elem.getparent()
            while parent is not None:
                if isinstance(parent.tag, str) and SipMerger._local(parent.tag) == "AR-PACKAGE":
                    pkg_sn = SipMerger._child_text(parent, "SHORT-NAME")
                    if pkg_sn:
                        segments.append(pkg_sn)
                parent = parent.getparent()
            ar_path = "/" + "/".join(reversed(segments))
            if ar_path not in paths:
                paths.append(ar_path)
        return paths

    @staticmethod
    def read_impl_metadata(package_dir: Path) -> Dict[str, Any]:
        """Read BSW-IMPLEMENTATION metadata (W10) for an ingested module package."""
        pkg_dir = Path(package_dir)

        manifest_path = pkg_dir / "module.json"
        if manifest_path.is_file():
            try:
                data = json.loads(manifest_path.read_text(encoding="utf-8"))
                origin = data.get("origin")
                if isinstance(origin, dict):
                    impl = origin.get("implementation")
                    if isinstance(impl, dict) and impl:
                        return impl
            except (OSError, ValueError, TypeError) as exc:
                logger.debug("Could not read implementation metadata from %s: %s", manifest_path, exc)

        # Backward compatibility for legacy packages that wrote sources.json
        sources_path = pkg_dir / "sources.json"
        if sources_path.is_file():
            try:
                data = json.loads(sources_path.read_text(encoding="utf-8"))
                impl = data.get("implementation")
                if isinstance(impl, dict) and impl:
                    return impl
            except (OSError, ValueError, TypeError) as exc:
                logger.debug("Could not read legacy sources.json from %s: %s", sources_path, exc)

        # Fallback: parse config/*.arxml and legacy def/*.arxml inside package_dir
        sip_files: List[SipFile] = []
        for sub_name in ("config", "def"):
            sub_dir = pkg_dir / sub_name
            if not sub_dir.is_dir():
                continue
            for arxml in sorted(sub_dir.glob("*.arxml")):
                try:
                    sip_files.append(SipFile(path=arxml, module=pkg_dir.name, content=arxml.read_bytes()))
                except OSError as exc:
                    logger.debug("Could not read %s for impl metadata: %s", arxml, exc)
        return SipMerger.extract_bsw_implementation_metadata(sip_files) if sip_files else {}

    @staticmethod
    def _extract_definition_path(content: bytes, module_name: str) -> Optional[str]:
        """Extract AUTOSAR path of ECUC-MODULE-DEF from definition ARXML content.

        Returns:
            AR path like "/MICROSAR/Os", or None if not found
        """
        try:
            root = etree.fromstring(content)
        except etree.XMLSyntaxError:
            return None

        # Find ECUC-MODULE-DEF element
        def_elem = None
        for elem in root.iter():
            if isinstance(elem.tag, str) and elem.tag.endswith("}ECUC-MODULE-DEF"):
                def_elem = elem
                break
            elif elem.tag == "ECUC-MODULE-DEF":
                def_elem = elem
                break

        if def_elem is None:
            return None

        # Extract SHORT-NAME of the definition
        def_name = None
        for child in def_elem:
            tag = child.tag
            if isinstance(tag, str):
                tag = tag.rsplit("}", 1)[-1]
            if tag == "SHORT-NAME":
                def_name = (child.text or "").strip()
                break

        if not def_name:
            return None

        # Build AR-PACKAGE path
        segments = [def_name]
        parent = def_elem.getparent()
        while parent is not None:
            tag = parent.tag
            if isinstance(tag, str):
                tag = tag.rsplit("}", 1)[-1]
            if tag == "AR-PACKAGE":
                for child in parent:
                    child_tag = child.tag
                    if isinstance(child_tag, str):
                        child_tag = child_tag.rsplit("}", 1)[-1]
                    if child_tag == "SHORT-NAME":
                        pkg_name = (child.text or "").strip()
                        if pkg_name:
                            segments.append(pkg_name)
                        break
            parent = parent.getparent()

        return "/" + "/".join(reversed(segments))


class McalResourceExtractor:
    """Extract MCAL resources from EB plugin Resource .properties files.

    Task 3：从 Components/<Module>/GeneratorMsr/resource/<chip>/ 的 .properties
    文件提取可用资源（如 Port.AvailableModule_0），生成 YAML 约束清单。
    """

    def __init__(self, sip_root: Path):
        """Initialize with SIP root directory.

        Args:
            sip_root: Path to SIP root (contains Components/, DemoComponents/)
        """
        self.sip_root = Path(sip_root)

    def extract_from_properties(
        self, properties_file: Path, record_source: bool = False
    ) -> Dict[str, Dict[str, str]]:
        """Extract resources from a single .properties file.

        Parses key=value or key:value format and groups by module name (prefix before dot).

        Args:
            properties_file: Path to .properties file
            record_source: When True, include ``"_source": <path>`` in each module dict.

        Returns:
            {module_name: {property_name: value, ...}, ...}
            Empty dict if file missing or parse error.
        """
        if not properties_file.exists():
            return {}

        resources: Dict[str, Dict[str, str]] = {}
        try:
            with open(properties_file, encoding="utf-8") as f:
                for line in f:
                    line = line.strip()
                    # Skip comments and empty lines
                    if not line or line.startswith("#"):
                        continue

                    # Parse key: value or key=value (EB format uses colons)
                    separator = None
                    if ":" in line:
                        separator = ":"
                    elif "=" in line:
                        separator = "="
                    else:
                        continue

                    key, value = line.split(separator, 1)
                    key = key.strip()
                    value = value.strip()

                    # Extract module name: "Port.AvailableModule_0" → ("Port", "AvailableModule_0")
                    if "." not in key:
                        continue

                    module_name, prop_name = key.split(".", 1)
                    if module_name not in resources:
                        resources[module_name] = {}

                    resources[module_name][prop_name] = value
        except Exception as e:
            logger.debug("Error parsing %s: %s", properties_file, e)

        if record_source:
            src = Path(properties_file).as_posix()
            for module_dict in resources.values():
                module_dict["_source"] = src

        return resources

    def extract_all_chips_resources(self) -> Dict[str, Dict[str, Dict[str, str]]]:
        """Extract resources from SIP Components/GeneratorMsr/resource AND EB Resource*/resource/*.properties.

        Walks:
        1. ``Components/<Module>/GeneratorMsr/resource/<chip>/resources.properties``
        2. ``**/Resource*/resource/*.properties`` (e.g. ``CotexR52_<Chip>.properties`` / ``CortexR52_<Chip>.properties``)

        Returns:
            {chip_name: {module_name: {property: value, ...}, ...}, ...}
        """
        all_resources: Dict[str, Dict[str, Dict[str, str]]] = {}

        # 1. Walk Components/*/GeneratorMsr/resource/<chip>/resources.properties
        components_dir = self.sip_root / "Components"
        if components_dir.exists():
            for module_dir in components_dir.iterdir():
                if not module_dir.is_dir():
                    continue

                resource_base = module_dir / "GeneratorMsr" / "resource"
                if not resource_base.exists():
                    continue

                for chip_dir in resource_base.iterdir():
                    if not chip_dir.is_dir():
                        continue

                    chip_name = chip_dir.name
                    props_file = chip_dir / "resources.properties"
                    if props_file.exists():
                        resources = self.extract_from_properties(props_file)
                        if resources:
                            all_resources.setdefault(chip_name, {})
                            for module_name, module_resources in resources.items():
                                all_resources[chip_name][module_name] = module_resources

        # 2. Walk EB Resource plugin layout (**/Resource*/resource/*CotexR52_*.properties or CortexR52_*.properties)
        if self.sip_root.exists():
            for props_file in sorted(self.sip_root.rglob("*.properties")):
                if props_file.parent.name != "resource":
                    continue
                if props_file.name == "resources.properties":
                    continue
                parent_plugin = props_file.parent.parent.name
                stem = props_file.stem
                if "Resource" not in parent_plugin and not stem.startswith(("CotexR52_", "CortexR52_")):
                    continue
                chip_name = stem
                for prefix in ("CotexR52_", "CortexR52_"):
                    if chip_name.startswith(prefix):
                        chip_name = chip_name[len(prefix):]
                        break
                resources = self.extract_from_properties(props_file, record_source=True)
                if resources:
                    all_resources.setdefault(chip_name, {})
                    for module_name, module_resources in resources.items():
                        all_resources[chip_name][module_name] = module_resources

        return all_resources

    def extract_and_generate_yaml(self, chip_name: str, output_yaml: Path) -> None:
        """Extract resources for one chip and generate YAML constraint file.

        Args:
            chip_name: Chip folder name (e.g., "Generic_CortexR52_ASIMD")
            output_yaml: Output YAML file path
        """
        all_resources = self.extract_all_chips_resources()

        if chip_name not in all_resources:
            logger.warning("Chip %s not found in resources", chip_name)
            all_resources[chip_name] = {}

        chip_resources = all_resources[chip_name]

        # Generate YAML
        with open(output_yaml, "w", encoding="utf-8") as f:
            import yaml
            yaml.dump(chip_resources, f, default_flow_style=False, sort_keys=True)


@dataclass
class DaVinciImportReport:
    """Detailed report of a DaVinci project import (W12)."""

    source_dpa: str
    target_project: str
    project_file: str
    derivative_uuid: Optional[str] = None
    derivative_name: Optional[str] = None
    sip_root: Optional[str] = None
    mcal_source_dir: Optional[str] = None
    module_stats: Dict[str, Dict[str, Any]] = field(default_factory=dict)
    skipped_mcal_modules: List[Dict[str, str]] = field(default_factory=list)
    skipped_existing_modules: List[Dict[str, str]] = field(default_factory=list)
    failed_modules: List[Tuple[str, str]] = field(default_factory=list)
    rejected_modules: List[str] = field(default_factory=list)
    unresolved_references: List[Dict[str, str]] = field(default_factory=list)
    warnings: List[str] = field(default_factory=list)
    mcal_resources_exported: List[str] = field(default_factory=list)
    report_files: List[str] = field(default_factory=list)
    pre_inconsistencies: List[Dict[str, Any]] = field(default_factory=list)
    version_mismatches: List[Dict[str, str]] = field(default_factory=list)
    value_diffs: List[Dict[str, Any]] = field(default_factory=list)

    @property
    def imported_count(self) -> int:
        return len(self.module_stats)

    def to_markdown(self) -> str:
        from datetime import datetime

        lines = [
            "# DaVinci 工程导入报告",
            "",
            f"- **生成时间**：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
            f"- **源工程 (.dpa)**：`{self.source_dpa}`",
            f"- **目标工程目录**：`{self.target_project}`",
            f"- **目标工程文件**：`{self.project_file}`",
            f"- **衍生芯片**：{self.derivative_name or '未指定'} (`{self.derivative_uuid or '无 UUID'}`)",
            f"- **SIP 根目录**：`{self.sip_root or '未指定'}`",
        ]
        if self.mcal_source_dir:
            lines.append(f"- **EB MCAL 来源**：`{self.mcal_source_dir}`")
        lines.extend([
            "",
            f"## 汇总：已导入 {self.imported_count} 个模块，"
            f"跳过 MCAL {len(self.skipped_mcal_modules)} 个，"
            + (
                f"跳过已有模块 {len(self.skipped_existing_modules)} 个，"
                if self.skipped_existing_modules
                else ""
            )
            + f"用户拒绝合并 {len(self.rejected_modules)} 个，"
            f"失败 {len(self.failed_modules)} 个，"
            f"Active/Pre 不一致 {len(self.pre_inconsistencies)} 处，"
            f"版本不一致 {len(self.version_mismatches)} 个，"
            f"逐参数核对差异 {len(self.value_diffs)} 处，"
            f"未决引用 {len(self.unresolved_references)} 条",
            "",
        ])

        if self.module_stats:
            lines.extend([
                "## 已导入模块统计",
                "",
                "| 模块 | 配置来源 | 定义路径 | 容器数 | 参数数 | 引用数 |",
                "|---|---|---|---:|---:|---:|",
            ])
            for mod in sorted(self.module_stats):
                st = self.module_stats[mod]
                lines.append(
                    f"| {mod} | {st.get('config_source', '')} | "
                    f"`{st.get('definition', '')}` | {st.get('containers', 0)} | "
                    f"{st.get('parameters', 0)} | {st.get('references', 0)} |"
                )
            lines.append("")

        if self.skipped_mcal_modules:
            lines.extend(["## 已跳过的 DaVinci MCAL 模块", ""])
            for item in self.skipped_mcal_modules:
                lines.append(f"- **{item['module']}**：{item['reason']}")
            lines.append("")

        if self.skipped_existing_modules:
            lines.extend(["## 已跳过的已有模块", ""])
            for item in self.skipped_existing_modules:
                lines.append(f"- **{item['module']}**：{item['reason']}")
            lines.append("")

        if self.rejected_modules:
            lines.extend(["## 用户拒绝基线合并的模块", ""])
            for mod in self.rejected_modules:
                lines.append(f"- {mod}")
            lines.append("")

        if self.failed_modules:
            lines.extend(["## 导入失败的模块", ""])
            for mod, err in self.failed_modules:
                lines.append(f"- **{mod}**：{err}")
            lines.append("")

        if self.unresolved_references:
            lines.extend(["## 未决跨模块引用", ""])
            for ref in self.unresolved_references:
                lines.append(
                    f"- `{ref.get('module', '')}` / `{ref.get('container', '')}`."
                    f"`{ref.get('reference', '')}` -> `{ref.get('target', '')}`：{ref.get('message', '')}"
                )
            lines.append("")

        if self.warnings:
            lines.extend(["## 警告", ""])
            for w in self.warnings:
                lines.append(f"- {w}")
            lines.append("")

        if self.pre_inconsistencies:
            lines.extend([
                "## Active 与 Pre 不一致项",
                "",
                "| 模块 | 类型 | 路径键 | 源 Active 值 | Pre 预设值 |",
                "|---|---|---|---|---|",
            ])
            for item in self.pre_inconsistencies:
                lines.append(
                    f"| {item.get('module', '')} | {item.get('kind', '')} | "
                    f"`{item.get('key', '')}` | `{item.get('active', '')}` | `{item.get('pre', '')}` |"
                )
            lines.append("")

        if self.version_mismatches:
            lines.extend([
                "## BswImplSwVersion 版本不一致",
                "",
                "| 模块 | 定义路径 | DaVinci .dpa 版本 | 入库包版本 |",
                "|---|---|---|---|",
            ])
            for item in self.version_mismatches:
                lines.append(
                    f"| {item.get('module', '')} | `{item.get('definition', '')}` | "
                    f"`{item.get('dpa_version', '')}` | `{item.get('package_version', '')}` |"
                )
            lines.append("")

        if self.value_diffs:
            lines.extend([
                "## 导入配置逐参数核对差异",
                "",
                "| 模块 | 来源 | 差异类型 | 路径键 | 源值 | 导入后值 |",
                "|---|---|---|---|---|---|",
            ])
            for item in self.value_diffs:
                lines.append(
                    f"| {item.get('module', '')} | {item.get('source', '')} | {item.get('kind', '')} | "
                    f"`{item.get('key', '')}` | `{item.get('source_value', item.get('source', ''))}` | "
                    f"`{item.get('imported', '')}` |"
                )
            lines.append("")

        return "\n".join(lines)


class DaVinciProjectImporter:
    """Import a DaVinci XML .dpa project (BSW definitions + active ECUC values + optional EB MCAL) into Format 8."""

    @staticmethod
    def _locate_eb_plugins_dir(mcal_source_dir: Path) -> Optional[Path]:
        from . import eb_import

        src = Path(mcal_source_dir)
        found = eb_import.find_plugins_dir(src)
        if found is not None and eb_import._holds_plugins(found):
            return found
        if src.is_dir() and eb_import._holds_plugins(src):
            return src
        for ancestor in src.parents:
            cand = eb_import.find_plugins_dir(ancestor)
            if cand is not None and eb_import._holds_plugins(cand):
                return cand
        return None

    @staticmethod
    def _extract_module_config(
        ecuc_file: Path,
        module_name: str,
        expected_def_ref: Optional[str],
    ):
        """Parse ``ecuc_file`` and extract the configuration block(s) for ``module_name``."""
        from .parser.arxml_parser import ArxmlParser
        from .config_manager import merge_module_configurations

        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        root = etree.parse(str(ecuc_file), parser).getroot()
        configs = ArxmlParser().parse_all_module_configurations(root)
        if not configs:
            return None

        norm_expected = (expected_def_ref or "").rstrip("/")
        canonical_module = (
            norm_expected.rsplit("/", 1)[-1] if norm_expected else module_name
        ) or module_name
        std_ref = f"/AUTOSAR/EcucDefs/{canonical_module}" if canonical_module else ""
        is_specific_def = bool(
            canonical_module
            and norm_expected
            and norm_expected != std_ref
            and not norm_expected.startswith("/__STUB__/")
        )

        if is_specific_def:
            exact_matches = [
                cfg for cfg in configs
                if (cfg.definition_ref or "").rstrip("/") == norm_expected
            ]
            if exact_matches:
                return merge_module_configurations(exact_matches)

        matches = []
        mismatched_vendor_defs = set()
        match_names = {n for n in (module_name, canonical_module) if n}
        for cfg in configs:
            cfg_def = (cfg.definition_ref or "").rstrip("/")
            def_leaf = cfg_def.rsplit("/", 1)[-1] if cfg_def else ""
            if not (cfg.short_name in match_names or def_leaf in match_names):
                continue
            if is_specific_def and cfg_def and cfg_def != std_ref:
                mismatched_vendor_defs.add(cfg_def)
                continue
            matches.append(cfg)

        if matches:
            return merge_module_configurations(matches)
        if mismatched_vendor_defs:
            raise ValueError(
                f"{ecuc_file.name}: no configuration matching variant definition "
                f"'{norm_expected}' (found incompatible vendor definition(s): "
                f"{', '.join(sorted(mismatched_vendor_defs))})"
            )
        return None

    @staticmethod
    def _count_module_items(configuration) -> Dict[str, int]:
        containers = 0
        parameters = 0
        references = 0

        def walk(c):
            nonlocal containers, parameters, references
            containers += 1
            parameters += len(c.parameter_values) + sum(
                len(v) for v in c.multi_parameter_values.values()
            )
            references += len(c.reference_values) + sum(
                len(v) for v in c.multi_reference_values.values()
            )
            for sub in c.sub_containers:
                walk(sub)

        parameters += len(getattr(configuration, "parameter_values", {}))
        for top in getattr(configuration, "containers", []):
            walk(top)
        return {
            "containers": containers,
            "parameters": parameters,
            "references": references,
        }

    @classmethod
    def import_project(
        cls,
        workspace_manager,
        dpa_path: Path,
        target_dir: Optional[Path] = None,
        project_name: Optional[str] = None,
        mcal_source_dir: Optional[Path] = None,
        include_resources: bool = False,
        sip_library_dir: Optional[Path] = None,
        confirm=None,
        into_project: Optional[Any] = None,
        on_conflict: str = "auto",
    ) -> Tuple[Any, DaVinciImportReport]:
        """Import a DaVinci .dpa project into a new or existing Format 8 WorkspaceProject."""
        from datetime import datetime
        from . import project_paths, eb_import
        from .packages.library import LibraryRef, scan_library
        from .packages.package import ModulePackage
        from .packages.manifest import infer_package
        from .serializer.ecuc_serializer import EcucValueSerializer
        from .config_manager import EpcFileScanner, ProjectType

        if on_conflict not in ("auto", "keep", "replace"):
            raise ValueError(
                f"Unknown conflict policy: {on_conflict!r} (expected 'auto', 'keep', or 'replace')"
            )

        dpa_path = Path(dpa_path)
        dv = DaVinciProject.from_file(dpa_path)
        previous_wm_project = workspace_manager.current_project

        if into_project is not None:
            if getattr(into_project, "format_version", 0) < 8 or into_project.path is None:
                raise ValueError("只能合并到已保存的 Format 8 工程中")
            new_project = into_project
            out_dpa = new_project.path
            project_root = project_paths.project_root(new_project)
            if dv.derivative_uuid:
                new_project.derivative_uuid = dv.derivative_uuid
            if dv.derivative_name:
                new_project.derivative_name = dv.derivative_name
        else:
            if target_dir is None:
                raise ValueError("target_dir is required when into_project is not specified")
            proj_name = (project_name or dpa_path.stem or "DaVinciImport").strip()
            project_root = Path(target_dir) / proj_name
            project_root.mkdir(parents=True, exist_ok=True)
            out_dpa = project_root / f"{proj_name}.dpa"

            new_project = workspace_manager.create_project(
                name=proj_name,
                path=out_dpa,
                format_version=8,
            )
            new_project.project_type = ProjectType.VECTOR
            new_project.derivative_uuid = dv.derivative_uuid
            new_project.derivative_name = dv.derivative_name

        try:
            return cls._populate_davinci_project(
                workspace_manager=workspace_manager,
                dv=dv,
                dpa_path=dpa_path,
                new_project=new_project,
                project_root=project_root,
                out_dpa=out_dpa,
                mcal_source_dir=mcal_source_dir,
                include_resources=include_resources,
                sip_library_dir=sip_library_dir,
                confirm=confirm,
                into_project=into_project,
                on_conflict=on_conflict,
            )
        except BaseException:
            workspace_manager.current_project = previous_wm_project
            raise

    @staticmethod
    def _detect_sip_implementation_dir(files: List[SipFile]) -> Optional[str]:
        """Locate the sibling ``Implementation/`` directory of the module's SIP component."""
        for sip_file in sorted(files, key=lambda f: f.path.as_posix()):
            for parent in sip_file.path.parents:
                if parent.name == "BSWMD":
                    candidate = parent.parent / "Implementation"
                    if candidate.is_dir():
                        return candidate.resolve().as_posix()
        return None

    @classmethod
    def _populate_davinci_project(
        cls,
        *,
        workspace_manager,
        dv: DaVinciProject,
        dpa_path: Path,
        new_project: Any,
        project_root: Path,
        out_dpa: Path,
        mcal_source_dir: Optional[Path],
        include_resources: bool,
        sip_library_dir: Optional[Path],
        confirm,
        into_project: Optional[Any],
        on_conflict: str,
    ) -> Tuple[Any, DaVinciImportReport]:
        """Populate ``new_project`` with DaVinci SIP BSW modules, values, and optional EB MCAL."""
        from datetime import datetime
        from . import project_paths, eb_import
        from .baseline.merge import MergeKind
        from .packages.library import LibraryRef, scan_library
        from .packages.package import ModulePackage
        from .serializer.ecuc_serializer import EcucValueSerializer
        from .config_manager import ConfigurationManager, EpcFileScanner

        has_existing_eb_lib = any(
            lib.kind == "eb-plugins" for lib in new_project.module_libraries
        )

        # Ensure standard Format 8 subdirectories exist
        for dir_key in ["config", "base", "templates", "gen", "chips", "integration", "system", "history", "modules"]:
            dir_name = getattr(new_project.directories, dir_key)
            if dir_name:
                (project_root / dir_name).mkdir(parents=True, exist_ok=True)

        report = DaVinciImportReport(
            source_dpa=dpa_path.as_posix(),
            target_project=project_root.as_posix(),
            project_file=out_dpa.as_posix(),
            derivative_uuid=dv.derivative_uuid,
            derivative_name=dv.derivative_name,
            sip_root=dv.sip_root.as_posix() if dv.sip_root else None,
            mcal_source_dir=Path(mcal_source_dir).as_posix() if mcal_source_dir else None,
        )

        # 1. Obtain or ingest BSW SIP module packages
        if sip_library_dir is not None:
            lib_dir = Path(sip_library_dir)
            if not lib_dir.is_dir():
                raise FileNotFoundError(f"SIP library directory not found: {lib_dir}")
            bsw_lib_ref = LibraryRef(path=lib_dir.as_posix(), kind="package", exclude=[])
            bsw_packages_list = scan_library(bsw_lib_ref, project_root)
        else:
            if dv.sip_root is None or not dv.sip_root.exists():
                raise FileNotFoundError(f"SIP root not found for DaVinci project: {dv.sip_root}")
            davinci_lib_rel = project_paths.module_source_rel(
                new_project, project_paths.MODULE_SOURCE_DAVINCI
            )
            davinci_import_dir = project_paths.module_source_dir(
                new_project, project_paths.MODULE_SOURCE_DAVINCI
            )
            davinci_import_dir.mkdir(parents=True, exist_ok=True)

            scanner = SipScanner(dv.sip_root)
            all_modules = scanner.scan_all_modules(derivative_uuid=dv.derivative_uuid)
            exclude_wrapped_mcal = mcal_source_dir is not None or (
                into_project is not None and has_existing_eb_lib and on_conflict in ("auto", "keep")
            )
            for mod_name in sorted(all_modules):
                files = all_modules[mod_name]
                # Exclude Vector-wrapped Components/Mcal_Tha62x when EB MCAL is provided
                if exclude_wrapped_mcal:
                    files = [f for f in files if "Mcal_Tha62x" not in f.path.parts]
                if not files:
                    continue

                partitions = SipScanner.partition_module_files(mod_name, files)
                if len(partitions) > 1:
                    # Clean up stale monolithic package dir from earlier imports so it cannot collide on scan
                    stale_dir = davinci_import_dir / mod_name
                    if (
                        mod_name not in {p[0] for p in partitions}
                        and stale_dir.is_dir()
                        and (stale_dir / "module.json").is_file()
                    ):
                        import shutil
                        shutil.rmtree(stale_dir, ignore_errors=True)

                for pkg_dir_name, pkg_mod_name, group_files in partitions:
                    def_files = [f for f in group_files if f.role == "def"]
                    try:
                        def_content = SipMerger.merge_definition(group_files, pkg_mod_name)
                        if not def_content and not def_files:
                            continue
                        value_docs = SipMerger.extract_value_collections(group_files, pkg_mod_name)
                    except SipMergeError as exc:
                        report.warnings.append(f"SIP 模块 {pkg_dir_name} 合并冲突，已跳过：{exc}")
                        continue
                    impl_meta = SipMerger.extract_bsw_implementation_metadata(group_files)
                    SipPackageWriter.write_package(
                        module_name=pkg_mod_name,
                        definition_content=def_content or b"",
                        pre_config=value_docs.get("pre"),
                        rec_config=value_docs.get("rec"),
                        output_dir=davinci_import_dir,
                        source_files=[str(f.path) for f in group_files],
                        impl_metadata=impl_meta,
                        implementation_dir=cls._detect_sip_implementation_dir(group_files),
                        package_dir_name=pkg_dir_name,
                    )

            if include_resources:
                extractor = McalResourceExtractor(dv.sip_root)
                all_resources = extractor.extract_all_chips_resources()
                chips_dir = project_paths.resolve(new_project, "chips")
                chips_dir.mkdir(parents=True, exist_ok=True)
                for chip_name in sorted(all_resources):
                    yaml_file = chips_dir / f"resources_{chip_name}.yaml"
                    extractor.extract_and_generate_yaml(chip_name, yaml_file)
                    report.mcal_resources_exported.append(yaml_file.as_posix())

            bsw_lib_ref = LibraryRef(path=davinci_lib_rel, kind="package", exclude=[])
            bsw_packages_list = scan_library(bsw_lib_ref, project_root)

        bsw_lib_index = new_project.ensure_module_library(bsw_lib_ref)

        bsw_by_def: Dict[str, ModulePackage] = {
            p.manifest.definition.rstrip("/"): p for p in bsw_packages_list
        }
        bsw_by_name: Dict[str, ModulePackage] = {}
        for p in bsw_packages_list:
            prev = bsw_by_name.get(p.manifest.module)
            if prev is None or p.manifest.definition.rstrip("/") == f"/MICROSAR/{p.manifest.module}":
                bsw_by_name[p.manifest.module] = p

        # 2. Optional EB MCAL plugin library + chip discovery BEFORE adding modules
        eb_plugins_dir: Optional[Path] = None
        eb_lib_index: Optional[int] = None
        eb_survey = None
        if mcal_source_dir is not None:
            mcal_src = Path(mcal_source_dir)
            eb_plugins_dir = cls._locate_eb_plugins_dir(mcal_src)
            if eb_plugins_dir is not None:
                eb_survey = eb_import.survey_plugins(eb_plugins_dir)
                eb_lib_ref = LibraryRef(
                    path=eb_plugins_dir.resolve().as_posix(),
                    kind="eb-plugins",
                    exclude=sorted(eb_survey.exclude),
                )
                eb_lib_index = new_project.ensure_module_library(eb_lib_ref)
                new_project.discover_available_chips()
                # Select matching chip: prefer exact derivative_uuid match in chip database,
                # then fall back to device-token prefix match (e.g. THA6206 in Tongxin_THA6206).
                if new_project.selected_chip is None and new_project.available_chips:
                    matched_chip = None
                    if dv.derivative_uuid:
                        try:
                            hit = new_project._chip_library().find_chip_by_derivative_uuid(dv.derivative_uuid)
                        except Exception:
                            hit = None
                        if hit is not None and hit.name in new_project.available_chips:
                            matched_chip = hit.name
                    if matched_chip is None and dv.derivative_name:
                        for chip in new_project.available_chips:
                            prefix = chip.split("_")[0]
                            if prefix and prefix.lower() in dv.derivative_name.lower():
                                matched_chip = chip
                                break
                    new_project.selected_chip = matched_chip or new_project.available_chips[0]
                new_project.load_ecu_resources()
            else:
                report.warnings.append(
                    f"未在指定的 MCAL 目录中找到 EB 插件 (plugin.xml)：{mcal_source_dir}"
                )

        # If no EB MCAL chip was selected (e.g. pure DaVinci BSW import), match chip by derivative_uuid
        if new_project.selected_chip is None and dv.derivative_uuid:
            try:
                hit = new_project._chip_library().find_chip_by_derivative_uuid(dv.derivative_uuid)
            except Exception:
                hit = None
            if hit is not None:
                if hit.name not in new_project.available_chips:
                    new_project.available_chips.append(hit.name)
                new_project.selected_chip = hit.name
                new_project.load_ecu_resources()

        # 3. Determine active BSW modules & record skipped DaVinci MCAL modules
        # Respect dv.active_modules (from ECUC-VALUE-COLLECTION / EcucSplitter) rather than
        # unioning all 100+ unused ModuleDefinitionMappings entries.
        declared_modules = (
            set(dv.active_modules)
            if dv.active_modules
            else (set(dv.ecuc_split_map.keys()) or set(dv.module_definitions.keys()))
        )
        mcal_names = set(dv.mcal_modules())

        if declared_modules:
            target_bsw: List[str] = []
            for mod_name in sorted(declared_modules):
                if mod_name in mcal_names:
                    if mcal_source_dir is not None:
                        report.skipped_mcal_modules.append({
                            "module": mod_name,
                            "reason": f"跳过 DaVinci MCAL（已改用 EB MCAL：{mcal_source_dir}）",
                        })
                    elif (
                        into_project is not None
                        and (mod_name in new_project.module_managers or mod_name in new_project.module_entries)
                        and on_conflict in ("auto", "keep")
                    ):
                        report.skipped_mcal_modules.append({
                            "module": mod_name,
                            "reason": "保留当前工程中已有的 MCAL 模块，跳过 DaVinci 同名 MCAL 模块",
                        })
                    elif mod_name in bsw_by_name or dv.module_definitions.get(mod_name, "").rstrip("/") in bsw_by_def:
                        target_bsw.append(mod_name)
                    else:
                        report.skipped_mcal_modules.append({
                            "module": mod_name,
                            "reason": "未指定 EB MCAL 来源目录，且 SIP 中无对应模块定义",
                        })
                else:
                    target_bsw.append(mod_name)
        else:
            # Minimal .dpa without <ModuleDefinitionMappings> or <EcucSplitter>: import all SIP packages
            target_bsw = sorted(bsw_by_name.keys())

        # 4. Import BSW modules with actual DaVinci ECUC configuration values
        serializer = EcucValueSerializer()
        imported_at = datetime.now().isoformat()

        for mod_name in target_bsw:
            expected_def = dv.module_definitions.get(mod_name)
            pkg = (
                bsw_by_def.get(expected_def.rstrip("/")) if expected_def else None
            ) or bsw_by_name.get(mod_name)
            if pkg is None:
                msg = f"Module {mod_name} definition not found: {expected_def or mod_name}"
                report.failed_modules.append((mod_name, msg))
                continue

            target_name = pkg.manifest.module or mod_name
            replace_backup = None
            if into_project is not None and (
                target_name in new_project.module_managers or target_name in new_project.module_entries
            ):
                existing_entry = new_project.module_entries.get(target_name)
                existing_from_eb = (
                    existing_entry is not None
                    and 0 <= existing_entry.library < len(new_project.module_libraries)
                    and new_project.module_libraries[existing_entry.library].kind == "eb-plugins"
                )
                is_mcal = (mod_name in mcal_names) or (target_name in mcal_names)
                existing_mgr = new_project.module_managers.get(target_name)
                existing_has_config = (
                    existing_mgr is None  # conservative if entry exists without loaded manager
                    or bool(
                        getattr(existing_mgr.configuration, "containers", None)
                        or getattr(existing_mgr.configuration, "parameter_values", None)
                    )
                )
                if on_conflict == "keep":
                    keep_existing = True
                elif on_conflict == "auto":
                    if is_mcal:
                        keep_existing = True
                    elif existing_from_eb:
                        # Keep configured EB modules, but let DaVinci BSW modules (e.g. /MICROSAR/EcuC)
                        # replace empty unconfigured EB stub plugins (0 containers, 0 parameters).
                        keep_existing = existing_has_config
                    else:
                        keep_existing = False
                else:
                    keep_existing = False

                if keep_existing:
                    if existing_from_eb or is_mcal:
                        report.skipped_mcal_modules.append({
                            "module": target_name,
                            "reason": "保留当前工程中已有的 EB/MCAL 模块，跳过 DaVinci 同名模块",
                        })
                    else:
                        report.skipped_existing_modules.append({
                            "module": target_name,
                            "reason": "保留当前工程中已有模块（策略：保留已有）",
                        })
                    continue

                replace_backup = new_project._capture_module_replace_backup(target_name)
                new_project._purge_module_for_replace(target_name)

            config_source = "sip_baseline"
            written_cfg_path: Optional[Path] = None
            ecuc_file = dv.resolve_ecuc_file(mod_name)
            if ecuc_file is not None:
                effective_expected_def = expected_def or pkg.manifest.definition
                try:
                    extracted_cfg = cls._extract_module_config(
                        ecuc_file, mod_name, effective_expected_def
                    )
                except ValueError as exc:
                    new_project._restore_module_replace_backup(replace_backup)
                    report.failed_modules.append((target_name, str(exc)))
                    continue
                except Exception as exc:
                    extracted_cfg = None
                    report.warnings.append(f"{mod_name}: 读取 DaVinci 配置 {ecuc_file.name} 失败：{exc}")
                if extracted_cfg is not None:
                    # Keep module's short_name consistent with definition leaf
                    target_cfg_path = project_paths.config_file(new_project, target_name)
                    target_cfg_path.parent.mkdir(parents=True, exist_ok=True)
                    serializer.serialize_to_file(extracted_cfg, target_cfg_path)
                    written_cfg_path = target_cfg_path
                    config_source = "davinci_ecuc"

            merge_rejected = [False]
            if confirm is not None:
                def confirm_with_tracking(preview_text, merge_result):
                    accepted = bool(confirm(preview_text, merge_result))
                    if not accepted:
                        merge_rejected[0] = True
                    return accepted
                confirm_cb = confirm_with_tracking
            else:
                confirm_cb = None

            new_project.last_merge_results.pop(target_name, None)
            try:
                mgr = new_project.add_module_from_package(
                    pkg=pkg,
                    lib_index=bsw_lib_index,
                    persist=True,
                    confirm=confirm_cb,
                    reconcile=True,
                )
            except Exception as exc:
                if written_cfg_path is not None and written_cfg_path.is_file():
                    written_cfg_path.unlink(missing_ok=True)
                new_project._restore_module_replace_backup(replace_backup)
                report.failed_modules.append((target_name, str(exc)))
                continue

            if merge_rejected[0]:
                new_project.remove_module(mgr.module_def.short_name, archive=False)
                if written_cfg_path is not None and written_cfg_path.is_file():
                    written_cfg_path.unlink(missing_ok=True)
                new_project._restore_module_replace_backup(replace_backup)
                report.rejected_modules.append(target_name)
                continue

            actual_name = mgr.module_def.short_name
            new_project.module_provenance[actual_name] = {
                "origin": "davinci-import",
                "source_epc": ecuc_file.as_posix() if ecuc_file else None,
                "imported_at": imported_at,
            }
            stats = cls._count_module_items(mgr.configuration)
            stats["config_source"] = config_source
            stats["definition"] = pkg.manifest.definition
            report.module_stats[actual_name] = stats

            # W12 verification 1: record Active vs Pre inconsistencies from baseline merge
            pre_forced_keys: Set[str] = set()
            merge_res = new_project.last_merge_results.get(actual_name)
            if merge_res is not None:
                for item in merge_res.items:
                    if item.kind == MergeKind.PRE_FORCED or (
                        config_source == "davinci_ecuc"
                        and item.kind == MergeKind.CREATE
                        and item.new_value is not None
                    ):
                        report.pre_inconsistencies.append({
                            "module": actual_name,
                            "kind": item.kind.value,
                            "key": item.key,
                            "active": item.active_value,
                            "pre": item.new_value,
                        })
                    if item.kind == MergeKind.PRE_FORCED:
                        pre_forced_keys.add(item.key)

            # W12 verification 2: compare .dpa BswImplSwVersion against ingested package SW-VERSION
            def_key = pkg.manifest.definition.rstrip("/")
            dpa_ver = dv.bsw_impl_versions.get(def_key)
            pkg_ver = (
                pkg.read_impl_metadata().get("sw_version")
                or eb_import.package_record(pkg).get("sw_version")
            )
            if dpa_ver and pkg_ver and not versions_match(dpa_ver, str(pkg_ver)):
                report.version_mismatches.append({
                    "module": actual_name,
                    "definition": def_key,
                    "dpa_version": dpa_ver,
                    "package_version": str(pkg_ver),
                })

            # W12 verification 3: parameter-by-parameter comparison against source DaVinci ECUC
            if config_source == "davinci_ecuc" and extracted_cfg is not None:
                for diff in compare_module_values(
                    extracted_cfg,
                    mgr.configuration,
                    actual_name,
                    expected_pre_keys=pre_forced_keys,
                ):
                    report.value_diffs.append({
                        "module": actual_name,
                        "source": "davinci_ecuc",
                        "source_value": diff["source"],
                        **diff,
                    })

        # 5. Import EB MCAL modules (when EB MCAL source directory is supplied and holds plugins)
        if eb_plugins_dir is not None and eb_lib_index is not None and eb_survey is not None:
            for skipped_dir in eb_survey.skipped:
                report.warnings.append(f"EB 插件目录跳过：{skipped_dir.name}（{skipped_dir.reason}）")
            epc_values: Dict[str, Any] = {}
            epc_candidates = sorted(
                set(EpcFileScanner.find_epc_files(Path(mcal_source_dir), new_project.selected_chip).values()),
                key=lambda p: p.as_posix(),
            )
            # Also collect standalone *.xdm config files if mcal_source_dir is a config/ folder
            if Path(mcal_source_dir).is_dir():
                for xdm_path in sorted(Path(mcal_source_dir).glob("*.xdm")):
                    epc_candidates.append(xdm_path)

            for epc in epc_candidates:
                try:
                    configs = eb_import.module_configs_in(epc)
                except Exception:
                    continue
                for sn, def_ref in configs:
                    m_name = def_ref.rstrip("/").rsplit("/", 1)[-1] if def_ref else sn
                    if m_name not in epc_values:
                        epc_values[m_name] = eb_import.EpcValues(epc, sn, def_ref)

            excluded = set(eb_survey.exclude)
            for pkg in eb_survey.packages:
                if pkg.root.name in excluded:
                    continue
                m_name = pkg.manifest.module
                epc = epc_values.get(m_name)
                mcal_backup = None
                if m_name in new_project.module_managers or m_name in new_project.module_entries:
                    if into_project is not None and on_conflict == "replace":
                        existing_mgr = new_project.module_managers.get(m_name)
                        existing_has_config = (
                            existing_mgr is not None
                            and bool(
                                getattr(existing_mgr.configuration, "containers", None)
                                or getattr(existing_mgr.configuration, "parameter_values", None)
                            )
                        )
                        if (
                            epc is None
                            and existing_has_config
                            and not pkg.manifest.pre
                            and not pkg.manifest.rec
                        ):
                            continue
                        mcal_backup = new_project._capture_module_replace_backup(m_name)
                        new_project._purge_module_for_replace(m_name)
                    else:
                        continue
                written_mcal_cfg: Optional[Path] = None
                if epc is not None and eb_import.epc_names_definition(epc.definition_ref, pkg.manifest.definition):
                    written_mcal_cfg = project_paths.config_file(new_project, m_name)
                    written_mcal_cfg.parent.mkdir(parents=True, exist_ok=True)
                    import shutil
                    shutil.copyfile(epc.file, written_mcal_cfg)
                mcal_rejected = [False]
                if confirm is not None:
                    def confirm_mcal(preview_text, merge_result, _flag=mcal_rejected):
                        accepted = bool(confirm(preview_text, merge_result))
                        if not accepted:
                            _flag[0] = True
                        return accepted
                    mcal_confirm_cb = confirm_mcal
                else:
                    mcal_confirm_cb = None

                new_project.last_merge_results.pop(m_name, None)
                try:
                    mgr = new_project.add_module_from_package(
                        pkg=pkg,
                        lib_index=eb_lib_index,
                        persist=True,
                        confirm=mcal_confirm_cb,
                        reconcile=True,
                    )
                    if mcal_rejected[0]:
                        new_project.remove_module(mgr.module_def.short_name, archive=False)
                        if written_mcal_cfg is not None:
                            written_mcal_cfg.unlink(missing_ok=True)
                        new_project._restore_module_replace_backup(mcal_backup)
                        report.rejected_modules.append(m_name)
                        continue
                    actual_mcal_name = mgr.module_def.short_name
                    stats = cls._count_module_items(mgr.configuration)
                    stats["config_source"] = "eb_mcal"
                    stats["definition"] = pkg.manifest.definition
                    report.module_stats[actual_mcal_name] = stats

                    mcal_pre_forced: Set[str] = set()
                    mcal_merge = new_project.last_merge_results.get(actual_mcal_name)
                    if mcal_merge is not None:
                        for item in mcal_merge.items:
                            if item.kind == MergeKind.PRE_FORCED:
                                mcal_pre_forced.add(item.key)
                                report.pre_inconsistencies.append({
                                    "module": actual_mcal_name,
                                    "kind": item.kind.value,
                                    "key": item.key,
                                    "active": item.active_value,
                                    "pre": item.new_value,
                                })

                    if epc is not None and written_mcal_cfg is not None:
                        try:
                            src_mgr = ConfigurationManager(mgr.module_def)
                            src_mgr.load_configuration(epc.file)
                            for diff in compare_module_values(
                                src_mgr.configuration,
                                mgr.configuration,
                                actual_mcal_name,
                                expected_pre_keys=mcal_pre_forced,
                            ):
                                report.value_diffs.append({
                                    "module": actual_mcal_name,
                                    "source": "eb_mcal",
                                    "source_value": diff["source"],
                                    **diff,
                                })
                        except Exception as exc:
                            logger.warning(
                                "Failed to compare EB MCAL source values for %s (%s): %s",
                                actual_mcal_name,
                                epc.file,
                                exc,
                            )
                except Exception as exc:
                    if written_mcal_cfg is not None:
                        written_mcal_cfg.unlink(missing_ok=True)
                    new_project._restore_module_replace_backup(mcal_backup)
                    report.failed_modules.append((m_name, str(exc)))

        new_project.deduplicate_library_definitions()

        # Refresh ECU resources after all modules are loaded so apply_chip_expressions runs on each module_def
        if new_project.module_managers and (new_project.selected_chip or mcal_source_dir is not None):
            try:
                new_project.load_ecu_resources()
            except Exception as exc:
                report.warnings.append(f"刷新 ECU 资源表达式失败：{exc}")

        # 6. Resolve cross-module references & record unresolved ones
        if new_project.module_managers:
            try:
                new_project.resolve_all_references()
                new_project.build_reverse_reference_index()
            except Exception as exc:
                report.warnings.append(f"跨模块引用解析出现异常：{exc}")

            for m_name, mgr in sorted(new_project.module_managers.items()):
                for err in mgr.configuration.get_resolution_errors():
                    report.unresolved_references.append({
                        "module": m_name,
                        "container": "",
                        "reference": "",
                        "target": err.path,
                        "message": err.message,
                    })

        # 7. Write a single timestamped Markdown report under .history/reports/ and persist project
        md_text = report.to_markdown()
        rpath = eb_import.report_path(new_project, kind="davinci_import")
        try:
            rpath.parent.mkdir(parents=True, exist_ok=True)
            rpath.write_text(md_text, encoding="utf-8")
            report.report_files.append(rpath.as_posix())
        except OSError as exc:
            report.warnings.append(f"写入导入报告失败 {rpath}: {exc}")

        workspace_manager.current_project = new_project
        workspace_manager.save_project()
        return new_project, report
