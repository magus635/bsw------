"""
XDM Chip Extractor
Extracts chip/hardware resource definitions from EB Tresos XDM module files.

XDM files define:
- Hardware unit counts (ecu:get('Module.MaxUnits'))
- Hardware channel lists (ecu:list('Module.HwChannel'))
- Controller IDs and enumerations
- Base addresses and resource mappings
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Any, Optional, Set
import re
import xml.etree.ElementTree as ET

from .chip_database import (
    ChipDefinition, PortPinDef, CanResourceDef,
    AdcResourceDef, SpiResourceDef, IntcSourceDef
)
from .ecu_resource_parser import EcuResourceParser, extract_xdm_resources


@dataclass
class XdmModuleInfo:
    """Information extracted from a single XDM module file"""
    module_name: str
    hw_units: List[str] = field(default_factory=list)
    hw_channels: List[str] = field(default_factory=list)
    parameters: Dict[str, Any] = field(default_factory=dict)
    ecu_resources: Dict[str, Any] = field(default_factory=dict)


class XdmChipExtractor:
    """Extracts chip definitions from XDM module files"""

    def __init__(self):
        self._module_info: Dict[str, XdmModuleInfo] = {}
        self._ecu_parser = EcuResourceParser()

    def scan_xdm_directory(self, xdm_dir: Path) -> Dict[str, XdmModuleInfo]:
        """Scan directory for XDM files and extract module info.

        Args:
            xdm_dir: Directory containing XDM files

        Returns:
            Dict mapping module names to XdmModuleInfo
        """
        if not xdm_dir.exists():
            return {}

        for xdm_file in xdm_dir.glob("*.xdm"):
            try:
                info = self._parse_xdm_file(xdm_file)
                if info:
                    self._module_info[info.module_name] = info
            except Exception as e:
                print(f"Warning: Failed to parse {xdm_file}: {e}")

        return self._module_info

    def _parse_xdm_file(self, xdm_path: Path) -> Optional[XdmModuleInfo]:
        """Parse a single XDM file"""
        content = xdm_path.read_text(encoding='utf-8')

        # Extract module name from file or content
        module_name = xdm_path.stem

        # Also try to find it in the XML
        name_match = re.search(r'<d:chc\s+name="(\w+)"', content)
        if name_match:
            module_name = name_match.group(1)

        info = XdmModuleInfo(module_name=module_name)

        # Extract ecu:get and ecu:list references
        ecu_refs = extract_xdm_resources(content)
        for path, (ref_type, default_value) in ecu_refs.items():
            info.ecu_resources[path] = default_value

        # Parse XML for enumeration values (hardware unit IDs)
        try:
            tree = ET.parse(xdm_path)
            root = tree.getroot()
            info.hw_units = self._extract_hw_units(root, module_name)
            info.hw_channels = self._extract_hw_channels(root, module_name)
            info.parameters = self._extract_parameters(root)
        except ET.ParseError as e:
            print(f"XML parse error in {xdm_path}: {e}")

        return info

    def _extract_hw_units(self, root: ET.Element, module_name: str) -> List[str]:
        """Extract hardware unit IDs from XDM enumerations"""
        units = []
        content = ET.tostring(root, encoding='unicode')

        # Look for patterns like CAN_CONTROLLER_00, ADC_UNIT_0, etc.
        patterns = [
            rf'{module_name.upper()}_CONTROLLER_\d+',
            rf'{module_name.upper()}_UNIT_\d+',
            rf'{module_name.upper()}_HW_\d+',
            rf'{module_name.upper()}_\d+',
        ]

        for pattern in patterns:
            for match in re.finditer(pattern, content):
                unit_id = match.group(0)
                if unit_id not in units:
                    units.append(unit_id)

        return sorted(units)

    def _extract_hw_channels(self, root: ET.Element, module_name: str) -> List[str]:
        """Extract hardware channel IDs from XDM enumerations"""
        channels = []
        content = ET.tostring(root, encoding='unicode')

        # Look for channel patterns
        patterns = [
            rf'{module_name.upper()}_CHANNEL_\d+',
            rf'{module_name.upper()}_CH\d+',
        ]

        for pattern in patterns:
            for match in re.finditer(pattern, content):
                ch_id = match.group(0)
                if ch_id not in channels:
                    channels.append(ch_id)

        return sorted(channels)

    def _extract_parameters(self, root: ET.Element) -> Dict[str, Any]:
        """Extract parameter definitions with defaults and ranges"""
        params = {}
        content = ET.tostring(root, encoding='unicode')

        # Find DEFAULT value definitions
        default_pattern = r'<a:da\s+name="DEFAULT"\s+value="([^"]+)"'
        for match in re.finditer(default_pattern, content):
            # Try to find the associated parameter name
            pos = match.start()
            # Look backwards for the parameter name
            name_match = re.search(r'name="(\w+)"\s+type=', content[max(0, pos-500):pos])
            if name_match:
                param_name = name_match.group(1)
                value = match.group(1)
                # Try to convert to int
                try:
                    params[param_name] = int(value)
                except ValueError:
                    params[param_name] = value

        return params

    def build_chip_from_xdm(self, xdm_dir: Path, chip_name: str = "ExtractedChip") -> ChipDefinition:
        """Build a ChipDefinition by scanning XDM files.

        Args:
            xdm_dir: Directory containing XDM module files
            chip_name: Name for the generated chip

        Returns:
            ChipDefinition with resources extracted from XDM files
        """
        self.scan_xdm_directory(xdm_dir)

        chip = ChipDefinition(
            name=chip_name,
            family="Extracted",
            description=f"Chip definition extracted from XDM files in {xdm_dir}"
        )

        # Extract CAN resources
        if 'Can' in self._module_info:
            can_info = self._module_info['Can']
            chip.can_resources = self._build_can_resources(can_info)

        # Extract Port resources
        if 'Port' in self._module_info:
            port_info = self._module_info['Port']
            chip.ports = self._build_port_resources(port_info)

        # Extract ADC resources
        if 'Adc' in self._module_info:
            adc_info = self._module_info['Adc']
            chip.adc_resources = self._build_adc_resources(adc_info)

        # Extract SPI resources
        if 'Spi' in self._module_info:
            spi_info = self._module_info['Spi']
            chip.spi_resources = self._build_spi_resources(spi_info)

        return chip

    def _build_can_resources(self, info: XdmModuleInfo) -> List[CanResourceDef]:
        """Build CAN resource definitions from module info"""
        resources = []

        # Get count from ecu resources
        max_modules = info.ecu_resources.get('Can.MaxModules', 1)
        max_nodes = info.ecu_resources.get('Can.MaxNodes', 8)
        max_controllers = max_modules * max_nodes if isinstance(max_modules, int) and isinstance(max_nodes, int) else 8

        # Use hardware unit IDs if available
        if info.hw_units:
            for i, unit_id in enumerate(info.hw_units):
                resources.append(CanResourceDef(
                    name=unit_id,
                    controller_id=i,
                    max_baudrate=1000000,
                    supports_fd=True,
                    mailbox_count=64
                ))
        else:
            # Generate from count
            for i in range(min(max_controllers, 8)):
                resources.append(CanResourceDef(
                    name=f"CAN{i}",
                    controller_id=i,
                    max_baudrate=1000000,
                    supports_fd=True,
                    mailbox_count=64
                ))

        return resources

    def _build_port_resources(self, info: XdmModuleInfo) -> Dict[str, List[PortPinDef]]:
        """Build Port resources from module info"""
        ports = {}

        # Look for port group patterns in hw_units
        port_groups: Set[str] = set()
        for unit in info.hw_units:
            # Extract port letter from names like PORT_A, PORTA, etc.
            match = re.search(r'PORT[_]?([A-Z])', unit)
            if match:
                port_groups.add(match.group(1))

        if not port_groups:
            # Default to common ports
            port_groups = {'A', 'B', 'C', 'D'}

        for port_letter in sorted(port_groups):
            port_name = f"PORT_{port_letter}"
            pins = []
            for pin_num in range(16):  # Assume 16 pins per port
                pins.append(PortPinDef(
                    name=f"P{port_letter}{pin_num}",
                    port=port_name,
                    pin=pin_num,
                    alternate_functions=["GPIO"]
                ))
            ports[port_name] = pins

        return ports

    def _build_adc_resources(self, info: XdmModuleInfo) -> List[AdcResourceDef]:
        """Build ADC resource definitions from module info"""
        resources = []

        # Get unit count
        max_units = info.ecu_resources.get('Adc.MaxHwUnits', 2)

        if info.hw_units:
            for i, unit_id in enumerate(info.hw_units):
                resources.append(AdcResourceDef(
                    name=unit_id,
                    unit_id=i,
                    channel_count=16,
                    resolution_bits=12,
                    channels=list(range(16))
                ))
        else:
            for i in range(min(max_units, 4) if isinstance(max_units, int) else 2):
                resources.append(AdcResourceDef(
                    name=f"ADC{i}",
                    unit_id=i,
                    channel_count=16,
                    resolution_bits=12,
                    channels=list(range(16))
                ))

        return resources

    def _build_spi_resources(self, info: XdmModuleInfo) -> List[SpiResourceDef]:
        """Build SPI resource definitions from module info"""
        resources = []

        max_units = info.ecu_resources.get('Spi.MaxHwUnits', 2)

        if info.hw_units:
            for i, unit_id in enumerate(info.hw_units):
                resources.append(SpiResourceDef(
                    name=unit_id,
                    unit_id=i,
                    max_baudrate=20000000,
                    supports_dma=True
                ))
        else:
            for i in range(min(max_units, 4) if isinstance(max_units, int) else 2):
                resources.append(SpiResourceDef(
                    name=f"SPI{i}",
                    unit_id=i,
                    max_baudrate=20000000,
                    supports_dma=True
                ))

        return resources

    def get_ecu_resources_dict(self) -> Dict[str, Any]:
        """Get all extracted ECU resources as a flat dict.

        This can be passed to the template renderer's ecu_resources parameter.
        """
        result = {}
        for module_name, info in self._module_info.items():
            result.update(info.ecu_resources)
        return result


def extract_chip_from_project(project_path: Path) -> Optional[ChipDefinition]:
    """Extract chip definition from an EB Tresos project.

    Scans the project for XDM files and builds a chip definition.

    Args:
        project_path: Path to the EB Tresos project root

    Returns:
        ChipDefinition if successful, None otherwise
    """
    extractor = XdmChipExtractor()

    # Common locations for XDM files in EB Tresos projects
    search_paths = [
        project_path / "Def",
        project_path / "define",
        project_path / "xdm",
        project_path,
    ]

    for search_path in search_paths:
        if search_path.exists():
            xdm_files = list(search_path.rglob("*.xdm"))
            if xdm_files:
                # Use parent directory of first XDM file
                xdm_dir = xdm_files[0].parent
                return extractor.build_chip_from_xdm(
                    xdm_dir,
                    chip_name=f"Extracted_{project_path.name}"
                )

    return None
