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
    module: str  # Extracted from DEFINITION-REF in the file, not from path
    content: Optional[bytes] = None


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

    def scan_all_modules(self) -> Dict[str, List[SipFile]]:
        """Scan all BSWMD directories and return files grouped by module.

        Returns:
            {module_name: [SipFile, ...]}
        """
        result = {}

        # Walk both Components/ and DemoComponents/
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

                # Walk all arxml/xdm files in BSWMD (root + subdirs)
                for arxml_file in bswmd_dir.rglob("*.arxml"):
                    try:
                        module = self._extract_module_from_file(arxml_file)
                        if module:
                            content = arxml_file.read_bytes()
                            sip_file = SipFile(path=arxml_file, module=module, content=content)
                            if module not in result:
                                result[module] = []
                            result[module].append(sip_file)
                    except (OSError, etree.XMLSyntaxError, AttributeError):
                        # XMLSyntaxError: malformed XML
                        # OSError: file read error
                        # AttributeError: lxml Cython object issues
                        pass

        # Sort each module's files deterministically
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
    def _extract_module_from_file(file_path: Path) -> Optional[str]:
        """Extract module name from ARXML file.

        Looks for ECUC-MODULE-DEF or ECUC-MODULE-CONFIGURATION-VALUES.
        Prefers DEFINITION-REF (full path); falls back to SHORT-NAME.

        Returns:
            Module name (e.g., "Os", "vBRS"), or None if not found.
        """
        try:
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(str(file_path), parser)
            root = tree.getroot()

            # Find ECUC-MODULE-DEF or ECUC-MODULE-CONFIGURATION-VALUES
            for elem in root.iter():
                # Guard: elem.tag must be a string (not a Cython method object)
                if not isinstance(elem.tag, str):
                    continue

                if elem.tag.endswith("ECUC-MODULE-DEF") or elem.tag.endswith("ECUC-MODULE-CONFIGURATION-VALUES"):
                    # Try DEFINITION-REF first
                    for child in elem:
                        if child.tag.endswith("DEFINITION-REF"):
                            def_ref = child.text
                            if def_ref:
                                # Extract module name: last segment
                                # e.g., "/MICROSAR/Os" -> "Os"
                                return def_ref.rstrip("/").rsplit("/", 1)[-1]

                    # Fallback: SHORT-NAME (for simple test ARXML without DEFINITION-REF)
                    for child in elem:
                        if child.tag.endswith("SHORT-NAME"):
                            short_name = child.text
                            if short_name:
                                return short_name.strip()

            return None
        except (etree.XMLSyntaxError, OSError):
            return None


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
    def separate_definition_and_config(merged_arxml: bytes) -> tuple[Optional[bytes], Optional[bytes], Optional[bytes]]:
        """Separate ECUC-MODULE-DEF and ECUC-MODULE-CONFIGURATION-VALUES from merged ARXML.

        Returns:
            Tuple of (definition_bytes, pre_config_bytes, rec_config_bytes)
            Each can be None if not present.
        """
        try:
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(io.BytesIO(merged_arxml), parser)
            root = tree.getroot()

            # Create three separate trees
            ns = {'ar': 'http://autosar.org/schema/r4.0'}

            def_root = etree.Element(root.tag, nsmap=root.nsmap)
            pre_root = etree.Element(root.tag, nsmap=root.nsmap)
            rec_root = etree.Element(root.tag, nsmap=root.nsmap)

            def_has_content = False
            pre_has_content = False
            rec_has_content = False

            # Process each AR-PACKAGE
            for pkg in root.findall('.//ar:AR-PACKAGE', ns):
                # Create clean packages for each output
                def_pkg = etree.Element(pkg.tag, nsmap=pkg.nsmap)
                pre_pkg = etree.Element(pkg.tag, nsmap=pkg.nsmap)
                rec_pkg = etree.Element(pkg.tag, nsmap=pkg.nsmap)

                # Copy SHORT-NAME
                sn = pkg.find('./ar:SHORT-NAME', ns)
                if sn is not None:
                    etree.SubElement(def_pkg, sn.tag).text = sn.text
                    etree.SubElement(pre_pkg, sn.tag).text = sn.text
                    etree.SubElement(rec_pkg, sn.tag).text = sn.text

                # Process ELEMENTS
                elements = pkg.find('./ar:ELEMENTS', ns)
                if elements is not None:
                    def_elements = etree.SubElement(def_pkg, elements.tag)
                    pre_elements = etree.SubElement(pre_pkg, elements.tag)
                    rec_elements = etree.SubElement(rec_pkg, elements.tag)

                    for child in elements:
                        tag_name = child.tag.split('}')[-1] if '}' in child.tag else child.tag

                        if tag_name == "ECUC-MODULE-DEF":
                            def_elements.append(etree.fromstring(etree.tostring(child)))
                            def_has_content = True
                        elif tag_name == "BSW-IMPLEMENTATION":
                            # Include implementation in def only
                            def_elements.append(etree.fromstring(etree.tostring(child)))
                            def_has_content = True
                        elif tag_name == "ECUC-MODULE-CONFIGURATION-VALUES":
                            # Determine if Pre or Rec by checking DEFINITION-REF or SHORT-NAME
                            def_ref = child.findtext('./ar:DEFINITION-REF', "", ns)
                            short_name = child.findtext('./ar:SHORT-NAME', "", ns)

                            is_pre = "Pre" in short_name or "Pre" in def_ref

                            if is_pre:
                                pre_elements.append(etree.fromstring(etree.tostring(child)))
                                pre_has_content = True
                            else:
                                rec_elements.append(etree.fromstring(etree.tostring(child)))
                                rec_has_content = True

                # Only add package if it has content
                if def_has_content and len(def_elements):
                    def_root.append(def_pkg)
                if pre_has_content and len(pre_elements):
                    pre_root.append(pre_pkg)
                if rec_has_content and len(rec_elements):
                    rec_root.append(rec_pkg)

            # Convert to bytes
            def_bytes = etree.tostring(def_root, encoding='utf-8', xml_declaration=True, pretty_print=True) if def_has_content else None
            pre_bytes = etree.tostring(pre_root, encoding='utf-8', xml_declaration=True, pretty_print=True) if pre_has_content else None
            rec_bytes = etree.tostring(rec_root, encoding='utf-8', xml_declaration=True, pretty_print=True) if rec_has_content else None

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

        # Write module.json matching load_manifest schema
        manifest = {
            "schema": 1,
            "module": module_name,
            "definition": f"config/{module_name}.arxml",
            "files": files_list,
            "pre": pre_list,
            "rec": rec_list,
        }

        manifest_path = output_dir / "module.json"
        with open(manifest_path, "w", encoding="utf-8") as f:
            json.dump(manifest, f, indent=2)

        return output_dir


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
