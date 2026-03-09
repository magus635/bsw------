"""
EB Tresos Properties File Parser
Parses hardware resource definitions from EB Tresos .properties files.

Format example:
    Module.Parameter: value
    Module.ParamList: val1, val2, val3
    Module.ListFormat: _0_ _1_ _2_   # underscore-wrapped values
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Any, Optional, Tuple
import re


@dataclass
class TresosPropertiesFile:
    """Parsed content of a Tresos properties file"""
    file_path: Path
    chip_name: str = ""
    properties: Dict[str, Any] = field(default_factory=dict)

    # Extracted module resources
    resources: Dict[str, Dict[str, Any]] = field(default_factory=dict)


class TresosPropertiesParser:
    """Parser for EB Tresos .properties files"""

    def __init__(self):
        self._raw_properties: Dict[str, str] = {}
        self._parsed: Optional[TresosPropertiesFile] = None

    def parse_file(self, file_path: Path) -> TresosPropertiesFile:
        """Parse a .properties file.

        Args:
            file_path: Path to the .properties file

        Returns:
            TresosPropertiesFile with parsed content
        """
        result = TresosPropertiesFile(file_path=file_path)
        self._raw_properties = {}

        # Extract chip name from filename
        # e.g., "CortexR52_THA6206_LFBGA292.properties" -> "THA6206_LFBGA292"
        name = file_path.stem
        if '_' in name:
            parts = name.split('_')
            # Find the chip identifier pattern (THAxxxx)
            for i, part in enumerate(parts):
                if part.startswith('THA') or part.startswith('tha'):
                    result.chip_name = '_'.join(parts[i:])
                    break
            if not result.chip_name:
                result.chip_name = name
        else:
            result.chip_name = name

        # Read and parse file
        content = file_path.read_text(encoding='utf-8', errors='replace')
        self._parse_content(content)

        # Convert raw properties to typed values
        for key, value in self._raw_properties.items():
            parsed_value = self._parse_value(value)
            result.properties[key] = parsed_value

            # Organize by module
            if '.' in key:
                module = key.split('.')[0]
                param = key.split('.', 1)[1]
                if module not in result.resources:
                    result.resources[module] = {}
                result.resources[module][param] = parsed_value

        self._parsed = result
        return result

    def _parse_content(self, content: str):
        """Parse properties file content with line continuation support"""
        lines = content.split('\n')
        current_key = None
        current_value = []

        for line in lines:
            # Remove BOM if present
            line = line.lstrip('\ufeff')

            # Skip empty lines
            stripped = line.strip()
            if not stripped:
                # Empty line terminates any pending line continuation
                if current_key and current_value:
                    self._raw_properties[current_key] = ' '.join(current_value)
                    current_key = None
                    current_value = []
                continue

            # Skip comments
            if stripped.startswith('#') or stripped.startswith('!'):
                # Comments also terminate any pending line continuation
                if current_key and current_value:
                    self._raw_properties[current_key] = ' '.join(current_value)
                    current_key = None
                    current_value = []
                continue

            # Check for line continuation
            if current_key and not stripped.startswith((':', '=')):
                # This is a continuation line
                if stripped.endswith('\\'):
                    current_value.append(stripped[:-1].strip())
                else:
                    current_value.append(stripped)
                    # End of continuation
                    self._raw_properties[current_key] = ' '.join(current_value)
                    current_key = None
                    current_value = []
                continue

            # Parse key=value or key:value or key: value
            match = re.match(r'^([^:=]+)[:=]\s*(.*)$', stripped)
            if match:
                key = match.group(1).strip()
                value = match.group(2).strip()

                if value.endswith('\\'):
                    # Line continuation starts
                    current_key = key
                    current_value = [value[:-1].strip()]
                else:
                    self._raw_properties[key] = value
                    current_key = None

        # Handle any remaining continuation
        if current_key and current_value:
            self._raw_properties[current_key] = ' '.join(current_value)

    def _parse_value(self, value: str) -> Any:
        """Parse a property value to appropriate Python type"""
        if not value:
            return None

        # Check for underscore-wrapped list format: _0_ _1_ _2_
        if re.match(r'^_[^_]+_(\s+_[^_]+_)*$', value):
            # For EB Tresos compatibility, these "lists" are often used with contains()
            # in templates. We keep them as strings here.
            return value

        # Check for comma-separated list
        if ',' in value:
            items = [v.strip() for v in value.split(',') if v.strip()]
            return self._convert_list_items(items)

        # Space-separated values: keep as raw string for ecu:get() compatibility.
        # EB Tresos ecu:get() returns the original property string; templates use
        # contains(ecu:get(...), 'VALUE ') with space as delimiter.
        # Only comma-separated values (handled above) are split into lists.

        # Try to convert single value
        return self._convert_single_value(value)

    def _looks_like_list_item(self, value: str) -> bool:
        """Check if value looks like a list item (not a sentence)"""
        # List items are typically short identifiers
        if len(value) > 50:
            return False
        if ' ' in value:
            return False
        return True

    def _convert_list_items(self, items: List[str]) -> List[Any]:
        """Convert a list of string items to appropriate types"""
        result = []
        for item in items:
            converted = self._convert_single_value(item)
            if converted is not None:
                result.append(converted)
        return result

    def _convert_single_value(self, value: str) -> Any:
        """Convert a single string value to appropriate type.

        EB Tresos convention: values like (0U), 0x1234UL are C-literals
        meant to be emitted verbatim. Only convert plain numbers.
        """
        if not value:
            return None

        # Try hex (without stripping C-suffixes)
        if value.startswith('0x') or value.startswith('0X'):
            try:
                return int(value, 16)
            except ValueError:
                pass

        # Try integer (plain numbers like "15", "-1")
        try:
            return int(value)
        except ValueError:
            pass

        # Try float
        try:
            return float(value)
        except ValueError:
            pass

        # Try boolean
        if value.lower() in ('true', 'yes', 'on'):
            return True
        if value.lower() in ('false', 'no', 'off'):
            return False

        # Return as string — preserves C-literals like "(0U)", "0x1234UL"
        return value

    def get_module_resources(self, module_name: str) -> Dict[str, Any]:
        """Get all resources for a specific module"""
        if not self._parsed:
            return {}
        return self._parsed.resources.get(module_name, {})

    def get_property(self, key: str) -> Any:
        """Get a specific property value"""
        if not self._parsed:
            return None
        return self._parsed.properties.get(key)

    def get_ecu_resources_dict(self) -> Dict[str, Any]:
        """Get all properties as a flat dict for ecu:get() lookups"""
        if not self._parsed:
            return {}
        return dict(self._parsed.properties)


def parse_tresos_properties(file_path: Path) -> TresosPropertiesFile:
    """Convenience function to parse a properties file.

    Args:
        file_path: Path to the .properties file

    Returns:
        TresosPropertiesFile with parsed content
    """
    parser = TresosPropertiesParser()
    return parser.parse_file(file_path)


def find_properties_files(search_path: Path) -> List[Path]:
    """Find all .properties files in a directory tree.

    Args:
        search_path: Directory to search

    Returns:
        List of paths to .properties files
    """
    if not search_path.exists():
        return []

    # Look for resource properties files
    patterns = [
        "resource/*.properties",
        "Resource*/**/*.properties",
        "**/*_LFBGA*.properties",
        "**/*_BGA*.properties",
    ]

    found = set()
    for pattern in patterns:
        for match in search_path.glob(pattern):
            if match.is_file():
                found.add(match)

    return sorted(found)


def build_chip_from_properties(file_path: Path) -> 'ChipDefinition':
    """Build a ChipDefinition from an EB Tresos properties file.

    Args:
        file_path: Path to the .properties file

    Returns:
        ChipDefinition populated with resources from the properties file
    """
    from .chip_database import (
        ChipDefinition, PortPinDef, CanResourceDef,
        AdcResourceDef, SpiResourceDef, IntcSourceDef
    )

    parser = TresosPropertiesParser()
    props = parser.parse_file(file_path)

    chip = ChipDefinition(
        name=props.chip_name,
        family="THA6",
        description=f"Chip definition from {file_path.name}"
    )

    # Extract CAN resources
    chip.can_resources = _extract_can_resources(props)

    # Extract Port resources
    chip.ports = _extract_port_resources(props)

    # Extract ADC resources
    chip.adc_resources = _extract_adc_resources(props)

    # Extract SPI resources
    chip.spi_resources = _extract_spi_resources(props)

    # Extract INTC resources
    chip.intc_sources = _extract_intc_resources(props)

    return chip


def _extract_can_resources(props: TresosPropertiesFile) -> List['CanResourceDef']:
    """Extract CAN controller definitions from properties"""
    from .chip_database import CanResourceDef

    resources = []
    can_props = props.resources.get('Can', {})

    # Get hardware unit node list
    hw_units = can_props.get('HwUnitNode', [])
    if isinstance(hw_units, str):
        hw_units = [hw_units]

    # Get max modules and nodes for capacity info
    max_modules = can_props.get('MaxModules', 1)
    max_nodes = can_props.get('MaxNodes', 8)

    # Get FD support info
    fd_support = can_props.get('FDSupport', True)

    for i, unit_name in enumerate(hw_units):
        resources.append(CanResourceDef(
            name=unit_name,
            controller_id=i,
            max_baudrate=1000000,  # 1 Mbps
            supports_fd=fd_support if isinstance(fd_support, bool) else True,
            mailbox_count=64
        ))

    return resources


def _extract_port_resources(props: TresosPropertiesFile) -> Dict[str, List['PortPinDef']]:
    """Extract Port/Pin definitions from properties"""
    from .chip_database import PortPinDef

    ports: Dict[str, List[PortPinDef]] = {}
    port_props = props.resources.get('Port', {})

    # Get available port IDs (format: _0_ _1_ _2_ _10_ etc.)
    port_ids = port_props.get('AvailablePortsID', [])
    if isinstance(port_ids, str):
        if re.match(r'^_[^_]+_(\s+_[^_]+_)*$', port_ids):
            port_ids = re.findall(r'_([^_]+)_', port_ids)
            # Re-convert extracted items to their proper types
            port_ids = parser._convert_list_items(port_ids)
        else:
            port_ids = [port_ids]

    # Get pins per port
    pins_per_port = port_props.get('PinsPerPort', [])
    if isinstance(pins_per_port, str):
        pins_per_port = [int(pins_per_port)]
    elif isinstance(pins_per_port, int):
        pins_per_port = [pins_per_port]

    # Create default mapping if not enough info
    if not port_ids:
        # Default to common ports A-F
        port_ids = list(range(6))

    for idx, port_id in enumerate(port_ids):
        if isinstance(port_id, int):
            # Convert numeric port ID to name
            if port_id < 10:
                port_name = f"PORT_{chr(ord('A') + port_id)}"
            else:
                # Multi-digit port ID (e.g., 10, 11, 12...)
                port_name = f"PORT_{port_id}"
        else:
            port_name = str(port_id)

        # Determine number of pins for this port
        if idx < len(pins_per_port):
            num_pins = pins_per_port[idx] if isinstance(pins_per_port[idx], int) else 16
        else:
            num_pins = 16  # Default

        pins = []
        for pin_num in range(num_pins):
            pin_name = f"P{port_name.replace('PORT_', '')}_{pin_num}"
            pins.append(PortPinDef(
                name=pin_name,
                port=port_name,
                pin=pin_num,
                alternate_functions=["GPIO"]
            ))

        ports[port_name] = pins

    return ports


def _extract_adc_resources(props: TresosPropertiesFile) -> List['AdcResourceDef']:
    """Extract ADC unit definitions from properties"""
    from .chip_database import AdcResourceDef

    resources = []
    adc_props = props.resources.get('Adc', {})

    # Get hardware unit IDs (format: SARADC0, SARADC1, ...)
    hw_unit_ids = adc_props.get('HwUnitId', [])
    if isinstance(hw_unit_ids, str):
        if re.match(r'^_[^_]+_(\s+_[^_]+_)*$', hw_unit_ids):
            hw_unit_ids = re.findall(r'_([^_]+)_', hw_unit_ids)
        else:
            hw_unit_ids = [hw_unit_ids]

    # Get channels per unit - check for unit-specific channels first
    default_channels = 16

    # Get resolution (MaxResolution is the actual value, Resolution is enum names)
    resolution = adc_props.get('MaxResolution', 12)
    if isinstance(resolution, list):
        resolution = resolution[0] if resolution else 12
    if not isinstance(resolution, int):
        # Try to extract number from string like "BITS_12"
        if isinstance(resolution, str) and '_' in resolution:
            try:
                resolution = int(resolution.split('_')[-1])
            except ValueError:
                resolution = 12

    for i, unit_name in enumerate(hw_unit_ids):
        # Try to get unit-specific channel list
        channel_key = f'AdcChannels_Adc{unit_name.replace("SARADC", "")}'
        unit_channels = adc_props.get(channel_key, [])
        if isinstance(unit_channels, list):
            channel_count = len(unit_channels)
            channels = list(range(channel_count))
        else:
            channel_count = default_channels
            channels = list(range(channel_count))

        resources.append(AdcResourceDef(
            name=unit_name,
            unit_id=i,
            channel_count=channel_count,
            resolution_bits=resolution,
            channels=channels
        ))

    return resources


def _extract_spi_resources(props: TresosPropertiesFile) -> List['SpiResourceDef']:
    """Extract SPI unit definitions from properties"""
    from .chip_database import SpiResourceDef

    resources = []
    spi_props = props.resources.get('Spi', {})

    # Get hardware unit IDs
    hw_unit_ids = spi_props.get('HwUnitId', [])
    if isinstance(hw_unit_ids, str):
        hw_unit_ids = [hw_unit_ids]

    # Get max units if no explicit list
    if not hw_unit_ids:
        max_units = spi_props.get('MaxHwUnits', 4)
        if isinstance(max_units, int):
            hw_unit_ids = [f"SPI{i}" for i in range(max_units)]

    # Get DMA support
    dma_support = spi_props.get('DmaSupport', True)

    for i, unit_name in enumerate(hw_unit_ids):
        resources.append(SpiResourceDef(
            name=unit_name,
            unit_id=i,
            max_baudrate=20000000,  # 20 MHz
            supports_dma=dma_support if isinstance(dma_support, bool) else True
        ))

    return resources


def _extract_intc_resources(props: TresosPropertiesFile) -> List['IntcSourceDef']:
    """Extract interrupt controller definitions from properties"""
    from .chip_database import IntcSourceDef

    resources = []
    intc_props = props.resources.get('Intc', {})

    # Get interrupt sources
    sources = intc_props.get('Sources', [])
    if isinstance(sources, str):
        sources = [sources]

    # Get max interrupt number
    max_int = intc_props.get('MaxInterrupt', 256)
    if isinstance(max_int, list):
        max_int = max_int[0] if max_int else 256

    # If no explicit sources, generate from max interrupt number
    if not sources and isinstance(max_int, int):
        # Just add common peripherals as placeholders
        common_sources = [
            ('CAN0_INT', 100),
            ('CAN1_INT', 101),
            ('SPI0_INT', 110),
            ('ADC0_INT', 120),
            ('TIMER0_INT', 130),
        ]
        for name, vector in common_sources:
            resources.append(IntcSourceDef(
                name=name,
                vector_number=vector
            ))
    else:
        for i, source in enumerate(sources):
            resources.append(IntcSourceDef(
                name=source,
                vector_number=i
            ))

    return resources
