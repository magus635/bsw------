"""
Chip Database
Manages chip definitions and provides chip information for hardware mapping
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Dict, Optional, Any
import yaml


@dataclass
class PortPinDef:
    """Port pin definition"""
    name: str
    port: str
    pin: int
    alternate_functions: List[str] = field(default_factory=list)
    default_direction: str = "INPUT"  # INPUT, OUTPUT, INOUT


@dataclass
class IntcSourceDef:
    """Interrupt controller source definition"""
    name: str
    vector_number: int
    priority_bits: int = 4
    is_configurable: bool = True


@dataclass
class CanResourceDef:
    """CAN controller resource definition"""
    name: str
    controller_id: int
    max_baudrate: int = 1000000
    supports_fd: bool = False
    mailbox_count: int = 32


@dataclass
class AdcResourceDef:
    """ADC resource definition"""
    name: str
    unit_id: int
    channel_count: int
    resolution_bits: int = 12
    channels: List[int] = field(default_factory=list)


@dataclass
class SpiResourceDef:
    """SPI resource definition"""
    name: str
    unit_id: int
    max_baudrate: int = 10000000
    supports_dma: bool = True


@dataclass
class ChipDefinition:
    """Complete chip definition"""
    name: str
    family: str = ""
    package: str = ""
    description: str = ""

    # Port resources
    ports: Dict[str, List[PortPinDef]] = field(default_factory=dict)

    # Peripheral resources
    intc_sources: List[IntcSourceDef] = field(default_factory=list)
    can_resources: List[CanResourceDef] = field(default_factory=list)
    adc_resources: List[AdcResourceDef] = field(default_factory=list)
    spi_resources: List[SpiResourceDef] = field(default_factory=list)

    # Additional metadata
    metadata: Dict[str, Any] = field(default_factory=dict)

    def get_port_pins(self, port_name: str) -> List[PortPinDef]:
        """Get pins for a specific port"""
        return self.ports.get(port_name, [])

    def get_all_pins(self) -> List[PortPinDef]:
        """Get all pins across all ports"""
        pins = []
        for port_pins in self.ports.values():
            pins.extend(port_pins)
        return pins

    def get_can_controller(self, controller_id: int) -> Optional[CanResourceDef]:
        """Get CAN controller by ID"""
        for can in self.can_resources:
            if can.controller_id == controller_id:
                return can
        return None


class ChipDatabase:
    """Database of chip definitions"""

    def __init__(self, data_dir: Optional[Path] = None):
        """Initialize chip database

        Args:
            data_dir: Directory containing chip YAML files
        """
        self._chips: Dict[str, ChipDefinition] = {}
        self._data_dir = data_dir

        if data_dir:
            self._load_chips_from_directory(data_dir)

    def _load_chips_from_directory(self, data_dir: Path):
        """Load chip definitions from YAML files"""
        if not data_dir.exists():
            return

        for yaml_file in data_dir.glob("*.yaml"):
            try:
                chip = self._load_chip_from_yaml(yaml_file)
                if chip:
                    self._chips[chip.name] = chip
            except Exception as e:
                print(f"Warning: Failed to load chip from {yaml_file}: {e}")

    def _load_chip_from_yaml(self, yaml_path: Path) -> Optional[ChipDefinition]:
        """Load a chip definition from YAML file"""
        with open(yaml_path, 'r', encoding='utf-8') as f:
            data = yaml.safe_load(f)

        if not data or 'name' not in data:
            return None

        chip = ChipDefinition(
            name=data['name'],
            family=data.get('family', ''),
            package=data.get('package', ''),
            description=data.get('description', ''),
        )

        # Load ports
        if 'ports' in data:
            for port_name, pins_data in data['ports'].items():
                chip.ports[port_name] = [
                    PortPinDef(
                        name=p.get('name', f"{port_name}_{p.get('pin', 0)}"),
                        port=port_name,
                        pin=p.get('pin', 0),
                        alternate_functions=p.get('alternate_functions', []),
                        default_direction=p.get('default_direction', 'INPUT')
                    )
                    for p in pins_data
                ]

        # Load INTC sources
        if 'intc_sources' in data:
            chip.intc_sources = [
                IntcSourceDef(
                    name=i['name'],
                    vector_number=i['vector_number'],
                    priority_bits=i.get('priority_bits', 4),
                    is_configurable=i.get('is_configurable', True)
                )
                for i in data['intc_sources']
            ]

        # Load CAN resources
        if 'can_resources' in data:
            chip.can_resources = [
                CanResourceDef(
                    name=c['name'],
                    controller_id=c['controller_id'],
                    max_baudrate=c.get('max_baudrate', 1000000),
                    supports_fd=c.get('supports_fd', False),
                    mailbox_count=c.get('mailbox_count', 32)
                )
                for c in data['can_resources']
            ]

        # Load ADC resources
        if 'adc_resources' in data:
            chip.adc_resources = [
                AdcResourceDef(
                    name=a['name'],
                    unit_id=a['unit_id'],
                    channel_count=a.get('channel_count', 16),
                    resolution_bits=a.get('resolution_bits', 12),
                    channels=a.get('channels', [])
                )
                for a in data['adc_resources']
            ]

        # Load SPI resources
        if 'spi_resources' in data:
            chip.spi_resources = [
                SpiResourceDef(
                    name=s['name'],
                    unit_id=s['unit_id'],
                    max_baudrate=s.get('max_baudrate', 10000000),
                    supports_dma=s.get('supports_dma', True)
                )
                for s in data['spi_resources']
            ]

        chip.metadata = data.get('metadata', {})

        return chip

    def register_chip(self, chip: ChipDefinition):
        """Register a chip definition"""
        self._chips[chip.name] = chip

    def get_chip(self, name: str) -> Optional[ChipDefinition]:
        """Get chip definition by name"""
        return self._chips.get(name)

    def list_chips(self) -> List[str]:
        """List all available chip names"""
        return sorted(self._chips.keys())

    def list_chips_by_family(self, family: str) -> List[str]:
        """List chips belonging to a specific family"""
        return sorted([
            name for name, chip in self._chips.items()
            if chip.family == family
        ])

    def detect_chip_from_project(self, project_path: Path) -> Optional[str]:
        """Attempt to detect chip from project files

        Looks for .dpa file or other configuration files that specify the chip.
        """
        # Try to find .dpa file
        dpa_files = list(project_path.glob("*.dpa"))
        if dpa_files:
            # Parse .dpa file to extract chip info
            try:
                with open(dpa_files[0], 'r', encoding='utf-8') as f:
                    content = f.read()
                    # Look for derivative or chip name patterns
                    # This is a simplified detection - real implementation
                    # would parse the XML structure
                    for chip_name in self._chips.keys():
                        if chip_name in content:
                            return chip_name
            except Exception:
                pass

        # Try to find in Mcu configuration
        mcu_configs = list(project_path.rglob("*Mcu*.arxml"))
        for mcu_config in mcu_configs:
            try:
                with open(mcu_config, 'r', encoding='utf-8') as f:
                    content = f.read()
                    for chip_name in self._chips.keys():
                        if chip_name in content:
                            return chip_name
            except Exception:
                pass

        return None

    @staticmethod
    def create_default_database() -> 'ChipDatabase':
        """Create a database with built-in chip definitions"""
        db = ChipDatabase()

        # THA6206 - Medium package
        tha6206 = ChipDefinition(
            name="THA6206_LFBGA292",
            family="THA6",
            package="LFBGA292",
            description="Automotive MCU with CAN/LIN/SPI",
        )

        # Add port definitions
        for port_letter in ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']:
            tha6206.ports[f"PORT_{port_letter}"] = [
                PortPinDef(
                    name=f"P{port_letter}{i}",
                    port=f"PORT_{port_letter}",
                    pin=i,
                    alternate_functions=[f"GPIO", f"ALT1", f"ALT2"]
                )
                for i in range(16)
            ]

        # Add CAN controllers
        tha6206.can_resources = [
            CanResourceDef(name="CAN0", controller_id=0, max_baudrate=1000000, supports_fd=True, mailbox_count=64),
            CanResourceDef(name="CAN1", controller_id=1, max_baudrate=1000000, supports_fd=True, mailbox_count=64),
            CanResourceDef(name="CAN2", controller_id=2, max_baudrate=1000000, supports_fd=False, mailbox_count=32),
        ]

        # Add ADC
        tha6206.adc_resources = [
            AdcResourceDef(name="ADC0", unit_id=0, channel_count=16, resolution_bits=12,
                          channels=list(range(16))),
            AdcResourceDef(name="ADC1", unit_id=1, channel_count=16, resolution_bits=12,
                          channels=list(range(16))),
        ]

        # Add SPI
        tha6206.spi_resources = [
            SpiResourceDef(name="SPI0", unit_id=0, max_baudrate=20000000, supports_dma=True),
            SpiResourceDef(name="SPI1", unit_id=1, max_baudrate=20000000, supports_dma=True),
            SpiResourceDef(name="SPI2", unit_id=2, max_baudrate=10000000, supports_dma=True),
        ]

        db.register_chip(tha6206)

        # THA610X - Small package
        tha610x = ChipDefinition(
            name="THA610X_LFBGA180",
            family="THA6",
            package="LFBGA180",
            description="Automotive MCU - Entry level",
        )

        for port_letter in ['A', 'B', 'C', 'D']:
            tha610x.ports[f"PORT_{port_letter}"] = [
                PortPinDef(
                    name=f"P{port_letter}{i}",
                    port=f"PORT_{port_letter}",
                    pin=i,
                    alternate_functions=[f"GPIO", f"ALT1"]
                )
                for i in range(16)
            ]

        tha610x.can_resources = [
            CanResourceDef(name="CAN0", controller_id=0, max_baudrate=1000000, supports_fd=False, mailbox_count=32),
            CanResourceDef(name="CAN1", controller_id=1, max_baudrate=500000, supports_fd=False, mailbox_count=16),
        ]

        tha610x.adc_resources = [
            AdcResourceDef(name="ADC0", unit_id=0, channel_count=8, resolution_bits=12,
                          channels=list(range(8))),
        ]

        tha610x.spi_resources = [
            SpiResourceDef(name="SPI0", unit_id=0, max_baudrate=10000000, supports_dma=True),
        ]

        db.register_chip(tha610x)

        # THA6412 - Large package
        tha6412 = ChipDefinition(
            name="THA6412_BGA516",
            family="THA6",
            package="BGA516",
            description="Automotive MCU - High Performance",
        )

        for port_letter in ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L']:
            tha6412.ports[f"PORT_{port_letter}"] = [
                PortPinDef(
                    name=f"P{port_letter}{i}",
                    port=f"PORT_{port_letter}",
                    pin=i,
                    alternate_functions=[f"GPIO", f"ALT1", f"ALT2", f"ALT3"]
                )
                for i in range(16)
            ]

        tha6412.can_resources = [
            CanResourceDef(name=f"CAN{i}", controller_id=i, max_baudrate=1000000, supports_fd=True, mailbox_count=64)
            for i in range(6)
        ]

        tha6412.adc_resources = [
            AdcResourceDef(name=f"ADC{i}", unit_id=i, channel_count=24, resolution_bits=12,
                          channels=list(range(24)))
            for i in range(3)
        ]

        tha6412.spi_resources = [
            SpiResourceDef(name=f"SPI{i}", unit_id=i, max_baudrate=25000000, supports_dma=True)
            for i in range(4)
        ]

        db.register_chip(tha6412)

        return db

    def load_from_properties_file(self, properties_path: Path) -> Optional[ChipDefinition]:
        """Load a chip definition from an EB Tresos properties file.

        Args:
            properties_path: Path to the .properties file

        Returns:
            ChipDefinition if successful, None otherwise
        """
        from .tresos_properties_parser import build_chip_from_properties

        try:
            chip = build_chip_from_properties(properties_path)
            self.register_chip(chip)
            return chip
        except Exception as e:
            print(f"Warning: Failed to load chip from properties {properties_path}: {e}")
            return None

    def scan_for_properties_files(self, search_path: Path) -> List[str]:
        """Scan a directory for properties files and load chip definitions.

        Args:
            search_path: Directory to scan (e.g., EB Tresos plugins path)

        Returns:
            List of chip names that were loaded
        """
        from .tresos_properties_parser import find_properties_files

        loaded = []
        for props_file in find_properties_files(search_path):
            chip = self.load_from_properties_file(props_file)
            if chip:
                loaded.append(chip.name)

        return loaded

    def detect_and_load_from_project(self, project_path: Path) -> Optional[ChipDefinition]:
        """Detect chip from project and load from properties if available.

        Searches for properties files in the project's Def/plugins directory
        and loads the chip definition.

        Args:
            project_path: Path to the EB Tresos project

        Returns:
            ChipDefinition if found, None otherwise
        """
        # Common locations for properties files in EB Tresos projects
        search_paths = [
            project_path / "Def" / "plugins",
            project_path / "plugins",
            project_path.parent / "Def" / "plugins",
        ]

        # Also check TRESOS_PLUGINS_PATH environment variable
        import os
        tresos_plugins = os.environ.get('TRESOS_PLUGINS_PATH')
        if tresos_plugins:
            search_paths.append(Path(tresos_plugins))

        for search_path in search_paths:
            if search_path.exists():
                # Look for Resource plugin directories
                for resource_dir in search_path.glob("Resource_*"):
                    if resource_dir.is_dir():
                        props_files = list(resource_dir.glob("resource/*.properties"))
                        if props_files:
                            # Load the first matching properties file
                            chip = self.load_from_properties_file(props_files[0])
                            if chip:
                                return chip

        return None
