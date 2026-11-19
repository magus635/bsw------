"""DaVinci project import: parse .dpa, scan SIP, merge, write packages.

Real design (per MERGE_DESIGN_REVIEW.md):
- Task 0 (前置修复)：Fix痛点 1-2 in project_controller + config_manager
- Task 1 (this module)：DaVinciProject parser + SipScanner content-driven grouping
- Task 2：Value import + baseline integration
"""

from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Set
from lxml import etree
import json
import logging
import io

logger = logging.getLogger(__name__)


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
    ):
        self.dpa_path = Path(dpa_path)
        self.derivative_uuid = derivative_uuid
        self.derivative_name = derivative_name
        self.sip_root = sip_root
        self.module_definitions = module_definitions  # {name -> definition_ref}
        self.ecuc_split_map = ecuc_split_map  # {name -> ecuc_arxml_file}
        self.main_ecuc_file = main_ecuc_file
        self.active_modules = active_modules or set()

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

        # Extract SIP root
        sip_root = None
        sip_elem = root.find(".//Folders/SIP")
        if sip_elem is not None and sip_elem.text:
            rel_path = sip_elem.text.strip()
            try:
                sip_root = (dpa_path.parent / rel_path).resolve()
            except (OSError, ValueError):
                pass

        # Extract derivative info
        derivative_uuid = None
        derivative_name = None
        deriv_elem = root.find(".//Environment/Derivative[@UUID]")
        if deriv_elem is not None:
            derivative_uuid = deriv_elem.get("UUID")
            if deriv_elem.text:
                derivative_name = deriv_elem.text.strip()

        # Extract module definitions
        module_definitions = {}
        for mapping in root.findall(".//ModuleDefinitionMappings/ModuleDefinitionMapping"):
            mod_name = mapping.get("ModuleConfigName", "").strip()
            def_ref = mapping.get("ModuleDefinitionRef", "").strip()
            if mod_name and def_ref:
                module_definitions[mod_name] = def_ref

        # Extract ECUC split mapping
        ecuc_split_map = {}
        for splitter in root.findall(".//EcucSplitter/Splitter"):
            file_path = splitter.get("File", "").strip()
            mod_elem = splitter.find("Module")
            if mod_elem is not None:
                mod_name = mod_elem.get("Name", "").strip()
                if mod_name and file_path:
                    ecuc_split_map[mod_name] = file_path

        # Extract main ECUC file
        main_ecuc_file = None
        config_elem = root.find(".//EcucSplitter/Configuration")
        if config_elem is not None and config_elem.text:
            main_ecuc_file = config_elem.text.strip()

        # Extract active modules from ECUC collection
        active_modules = set()
        active_elem = root.find(".//ECUC/Active[@RootPackageName]")
        if active_elem is not None:
            # The root package name identifies the active config
            # (e.g., "/ActiveEcuC/ActiveEcuC")
            # Module list comes from the actual ECUC file content (Task 2)
            pass

        return cls(
            dpa_path=dpa_path,
            derivative_uuid=derivative_uuid,
            derivative_name=derivative_name,
            sip_root=sip_root,
            module_definitions=module_definitions,
            ecuc_split_map=ecuc_split_map,
            main_ecuc_file=main_ecuc_file,
            active_modules=active_modules,
        )

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

    def scan_all_modules(self) -> Dict[str, List["SipFile"]]:
        """Scan all BSWMD directories and return files grouped by module.

        Each file is classified:
        - role="def"   : contains ECUC-MODULE-DEF (definitions)
        - role="config": contains only ECUC-MODULE-CONFIGURATION-VALUES (pre/rec)

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

        for module in result:
            result[module].sort(key=lambda f: str(f.path))

        return result

    def scan_module(self, module_name: str, derivative_uuid: Optional[str] = None) -> List[SipFile]:
        """Get all SipFile for one module, optionally filtered by derivative UUID.

        If derivative_uuid is provided, loads only the chip folder specified in
        DerivativeMapping_<Module>.xml for that UUID.

        Args:
            module_name: Module name (e.g., "Os", "vBRS")
            derivative_uuid: Optional derivative UUID to filter chip folder

        Returns:
            List of SipFile matching the module and optional derivative
        """
        all_by_module = self.scan_all_modules()
        files = all_by_module.get(module_name, [])

        # Task 2 改法：按 DerivativeMapping 过滤 chip 文件夹
        if derivative_uuid and files:
            # 尝试加载 DerivativeMapping_<Module>.xml
            mapping_file = self.sip_root / "Components" / module_name / "GeneratorMsr" / f"DerivativeMapping_{module_name}.xml"
            if not mapping_file.exists():
                mapping_file = self.sip_root / "DemoComponents" / module_name / "GeneratorMsr" / f"DerivativeMapping_{module_name}.xml"

            if mapping_file.exists():
                try:
                    chip_folder = self._get_chip_folder_from_mapping(mapping_file, derivative_uuid)
                    if chip_folder:
                        # 只保留路径包含该 chip 文件夹的文件
                        files = [f for f in files if chip_folder in str(f.path)]
                except Exception:
                    # 解析 mapping 失败，返回全部（fallback）
                    pass

        return files

    @staticmethod
    def _get_chip_folder_from_mapping(mapping_file: Path, derivative_uuid: str) -> Optional[str]:
        """从 DerivativeMapping XML 提取 UUID 对应的 chip 文件夹名。

        XML 格式：
        <Settings Name="ModuleList">
            <Settings Name="<Module>">
                <Settings Name="<ChipFolder>">
                    <Settings Name="<UUID>">
                        <Setting Name="SIP_Folder" Value="<ChipFolder>"/>
                    </Settings>
                </Settings>
            </Settings>
        </Settings>

        Args:
            mapping_file: DerivativeMapping XML 文件路径
            derivative_uuid: UUID 字符串

        Returns:
            Chip 文件夹名（如 "Generic_CortexR52_ASIMD"），或 None
        """
        try:
            from lxml import etree
            tree = etree.parse(str(mapping_file))
            root = tree.getroot()

            # 查找 UUID 节点并读取 SIP_Folder 值
            for uuid_node in root.iter():
                if uuid_node.text and uuid_node.text.strip() == derivative_uuid:
                    # 找到 UUID，返回其父节点（ChipFolder Settings）的 Name
                    chip_settings = uuid_node.getparent()
                    if chip_settings is not None:
                        chip_name = chip_settings.get("Name")
                        if chip_name:
                            return chip_name

            # 替代方法：直接搜索值为 UUID 的属性
            for settings in root.iter():
                if settings.get("Name") == derivative_uuid:
                    # 其父节点是 ChipFolder Settings
                    parent = settings.getparent()
                    if parent is not None:
                        return parent.get("Name")
        except Exception:
            pass

        return None

    @staticmethod
    def _extract_module_and_role(file_path: Path) -> tuple[Optional[str], str]:
        """Extract module name and classify the file's role.

        Returns:
            (module_name, role) where role is "def" if the file contains
            ECUC-MODULE-DEF, or "config" if it only has CONFIGURATION-VALUES.
            Returns (None, "unknown") if the file has no relevant elements.
        """
        try:
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(str(file_path), parser)
            root = tree.getroot()

            has_def = False
            module_from_def = None
            module_from_config = None

            for elem in root.iter():
                if not isinstance(elem.tag, str):
                    continue

                tag = elem.tag.split('}')[-1] if '}' in elem.tag else elem.tag

                if tag == "ECUC-MODULE-DEF":
                    has_def = True
                    # Module name from SHORT-NAME directly (not nested)
                    for child in elem:
                        c_tag = child.tag.split('}')[-1] if '}' in child.tag else child.tag
                        if c_tag == "SHORT-NAME" and child.text:
                            module_from_def = child.text.strip()
                            break

                elif tag == "ECUC-MODULE-CONFIGURATION-VALUES" and not module_from_config:
                    # Get module name from DEFINITION-REF last segment
                    for child in elem:
                        c_tag = child.tag.split('}')[-1] if '}' in child.tag else child.tag
                        if c_tag == "DEFINITION-REF" and child.text:
                            module_from_config = child.text.rstrip("/").rsplit("/", 1)[-1]
                            break
                    if not module_from_config:
                        # Fallback: SHORT-NAME of the config block
                        for child in elem:
                            c_tag = child.tag.split('}')[-1] if '}' in child.tag else child.tag
                            if c_tag == "SHORT-NAME" and child.text:
                                module_from_config = child.text.strip()
                                break

            if has_def and module_from_def:
                return module_from_def, "def"
            elif module_from_config:
                return module_from_config, "config"
            return None, "unknown"

        except (etree.XMLSyntaxError, OSError, AttributeError):
            return None, "unknown"

    @staticmethod
    def _extract_module_from_file(file_path: Path) -> Optional[str]:
        """Backward-compatible wrapper that returns module name."""
        name, _ = SipScanner._extract_module_and_role(file_path)
        return name


class SipMerger:
    """Merge BSWMD files by AUTOSAR path.

    Prerequisite: caller has grouped files by module (scanner output).
    Merger's job: combine all files for one module into a single ECUC-MODULE-DEF tree.
    """

    @staticmethod
    def merge_module(files: List[SipFile], module_name: str) -> Optional[bytes]:
        """Merge multiple ARXML files for one module.

        Args:
            files: SipFile list for this module
            module_name: Module name (for error reporting)

        Returns:
            Merged ARXML bytes, or None if no files
        """
        if not files:
            return None

        if len(files) == 1:
            # Single file: return as-is
            return files[0].content

        # Multiple files: merge by collecting all ECUC-MODULE-DEF into one root
        # (Full implementation deferred; for now return first file)
        # TODO: Implement proper AUTOSAR path-based merge (Task 2)
        return files[0].content

    @staticmethod
    def merge_definition(files: List[SipFile], module_name: str) -> Optional[bytes]:
        """Collect every ECUC-MODULE-DEF / BSW-IMPLEMENTATION from all files into one document.

        Unlike :meth:`merge_module`, this never drops a file: every AR-PACKAGE that
        carries a definition or implementation element is copied into the result,
        deduplicated by its AR path.

        Returns:
            ARXML bytes, or None when no file holds a definition.
        """
        by_path: Dict[str, Any] = {}
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
                if not SipMerger._package_has_definition(pkg):
                    continue
                key = SipMerger._package_path(pkg)
                if key not in by_path:
                    by_path[key] = etree.fromstring(etree.tostring(pkg))

        if not by_path or root_tag is None:
            return None

        out_root = etree.Element(root_tag, nsmap=nsmap)
        packages = etree.SubElement(out_root, SipMerger._ns_tag(root_tag, "AR-PACKAGES"))
        for key in sorted(by_path):
            packages.append(by_path[key])
        return etree.tostring(out_root, encoding="utf-8", xml_declaration=True, pretty_print=True)

    @staticmethod
    def extract_value_collections(files: List[SipFile], module_name: str) -> Dict[str, bytes]:
        """Split the value collections of all files into Pre / Rec / other documents.

        The role of a collection comes from the module's own BSW-IMPLEMENTATION:
        ``PRECONFIGURED-CONFIGURATION-REFS`` names the Pre paths,
        ``RECOMMENDED-CONFIGURATION-REFS`` the Rec paths (SIP spec §6.2 — by AUTOSAR
        path, never by file name or SHORT-NAME). A collection named by neither is kept
        under ``"values"`` so nothing is silently dropped.

        Returns:
            {"pre": bytes, "rec": bytes, "values": bytes} — only non-empty keys.
        """
        pre_paths: Set[str] = set()
        rec_paths: Set[str] = set()
        collections: Dict[str, Any] = {}
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

            # Collect every value collection with its full AR path
            for pkg in SipMerger._walk_packages(root):
                pkg_path = SipMerger._package_path(pkg)
                for elem in pkg.iter():
                    if not isinstance(elem.tag, str):
                        continue
                    if SipMerger._local(elem.tag) != "ECUC-MODULE-CONFIGURATION-VALUES":
                        continue
                    short = SipMerger._child_text(elem, "SHORT-NAME")
                    if not short:
                        continue
                    ar_path = f"{pkg_path}/{short}" if pkg_path else f"/{short}"
                    if ar_path not in collections:
                        collections[ar_path] = etree.fromstring(etree.tostring(elem))

        if not collections or root_tag is None:
            return {}

        buckets: Dict[str, List[Any]] = {"pre": [], "rec": [], "values": []}
        for ar_path in sorted(collections):
            elem = collections[ar_path]
            if ar_path in pre_paths:
                buckets["pre"].append(elem)
            elif ar_path in rec_paths:
                buckets["rec"].append(elem)
            else:
                buckets["values"].append(elem)

        result: Dict[str, bytes] = {}
        for role, elems in buckets.items():
            if not elems:
                continue
            out_root = etree.Element(root_tag, nsmap=nsmap)
            packages = etree.SubElement(out_root, SipMerger._ns_tag(root_tag, "AR-PACKAGES"))
            pkg_elem = etree.SubElement(packages, SipMerger._ns_tag(root_tag, "AR-PACKAGE"))
            etree.SubElement(pkg_elem, SipMerger._ns_tag(root_tag, "SHORT-NAME")).text = module_name
            elements_elem = etree.SubElement(pkg_elem, SipMerger._ns_tag(root_tag, "ELEMENTS"))
            for elem in elems:
                elements_elem.append(elem)
            result[role] = etree.tostring(out_root, encoding="utf-8", xml_declaration=True, pretty_print=True)
        return result

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
    ) -> Path:
        """Write a module package with separate def/ and config/ directories.

        Args:
            module_name: Module name (e.g., "Os")
            definition_content: ARXML bytes of ECUC-MODULE-DEF
            pre_config: Optional pre configuration ARXML
            rec_config: Optional rec configuration ARXML
            output_dir: Output directory; defaults to ./packages/<module_name>

        Returns:
            Path to package root
        """
        if output_dir is None:
            output_dir = Path.cwd() / "packages" / module_name
        else:
            output_dir = Path(output_dir) / module_name

        output_dir.mkdir(parents=True, exist_ok=True)
        def_dir = output_dir / "def"
        config_dir = output_dir / "config"
        def_dir.mkdir(exist_ok=True)
        config_dir.mkdir(exist_ok=True)

        # Write definition file to def/ directory
        files_list = []
        pre_list = []
        rec_list = []

        if definition_content:
            def_path = def_dir / f"{module_name}.arxml"
            def_path.write_bytes(definition_content)
            files_list.append(f"def/{module_name}.arxml")

        # Write pre/rec to config/ directory
        if pre_config:
            pre_path = config_dir / f"{module_name}_Pre.arxml"
            pre_path.write_bytes(pre_config)
            pre_list.append(f"config/{module_name}_Pre.arxml")
            files_list.append(f"config/{module_name}_Pre.arxml")

        if rec_config:
            rec_path = config_dir / f"{module_name}_Rec.arxml"
            rec_path.write_bytes(rec_config)
            rec_list.append(f"config/{module_name}_Rec.arxml")
            files_list.append(f"config/{module_name}_Rec.arxml")

        # Extract AUTOSAR definition path from definition content
        def_ar_path = SipPackageWriter._extract_definition_path(definition_content, module_name) if definition_content else None
        if not def_ar_path:
            # Fallback: guess /MICROSAR/<Module>
            def_ar_path = f"/MICROSAR/{module_name}"

        # Write module.json matching load_manifest schema
        manifest = {
            "schema": 1,
            "module": module_name,
            "definition": def_ar_path,
            "files": files_list,
            "pre": pre_list,
            "rec": rec_list,
        }

        manifest_path = output_dir / "module.json"
        with open(manifest_path, "w", encoding="utf-8") as f:
            json.dump(manifest, f, indent=2)

        return output_dir

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

    def extract_from_properties(self, properties_file: Path) -> Dict[str, Dict[str, str]]:
        """Extract resources from a single .properties file.

        Parses key=value format and groups by module name (prefix before dot).

        Args:
            properties_file: Path to resources.properties

        Returns:
            {module_name: {property_name: value, ...}, ...}
            Empty dict if file missing or parse error.
        """
        if not properties_file.exists():
            return {}

        resources = {}
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

        return resources

    def extract_all_chips_resources(self) -> Dict[str, Dict[str, Dict[str, str]]]:
        """Extract resources from all chip directories.

        Walks Components/<Module>/GeneratorMsr/resource/<chip>/resources.properties
        and groups by chip name.

        Returns:
            {chip_name: {module_name: {property: value, ...}, ...}, ...}
        """
        all_resources = {}

        # Walk Components/
        components_dir = self.sip_root / "Components"
        if components_dir.exists():
            for module_dir in components_dir.iterdir():
                if not module_dir.is_dir():
                    continue

                resource_base = module_dir / "GeneratorMsr" / "resource"
                if not resource_base.exists():
                    continue

                # Each subdirectory is a chip
                for chip_dir in resource_base.iterdir():
                    if not chip_dir.is_dir():
                        continue

                    chip_name = chip_dir.name
                    props_file = chip_dir / "resources.properties"
                    if props_file.exists():
                        resources = self.extract_from_properties(props_file)
                        if resources:
                            if chip_name not in all_resources:
                                all_resources[chip_name] = {}
                            # Merge resources (later modules override earlier ones if duplicate keys)
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
