"""
Generic Resource Model
Provides a universal model for describing hardware resources
"""
import logging
import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional

import yaml

logger = logging.getLogger(__name__)

_TRAILING_DIGITS = re.compile(r"(\d+)$")
_PORT_LETTERS = "ABCDEFGHIJKLMNOP"


def port_number_of(port_name: str) -> int:
    """Port number from a pin table port name.

    Digits ending the name give the number (``P10`` -> 10); a final letter A-P
    counts from A = 0 (``PORT_B`` -> 1); anything else is 0, with a warning.
    """
    match = _TRAILING_DIGITS.search(port_name or "")
    if match:
        return int(match.group(1))
    if port_name and port_name[-1] in _PORT_LETTERS:
        return _PORT_LETTERS.index(port_name[-1])
    logger.warning("port '%s': no port number in its name, using 0", port_name)
    return 0


@dataclass
class GenericResourceDef:
    """Generic hardware resource definition

    This is a universal model that can describe any type of hardware resource
    (CAN controller, GPIO port, ADC unit, etc.) using a flexible properties dict.
    """
    resource_type: str          # Resource type identifier (e.g., "can_controller", "gpio_port")
    resource_id: str            # Unique resource identifier (e.g., "CAN0", "PORT_A")
    display_name: str           # Human-readable name
    properties: Dict[str, Any] = field(default_factory=dict)  # Flexible key-value properties

    def get_property(self, key: str, default: Any = None) -> Any:
        """Get a property value with optional default"""
        return self.properties.get(key, default)

    def __str__(self) -> str:
        return f"{self.resource_type}:{self.resource_id}"


@dataclass
class ChipDefinition:
    """Chip definition using generic resource model"""
    name: str
    family: str = ""
    package: str = ""
    description: str = ""

    # Generic resources: {resource_type: [GenericResourceDef, ...]}
    resources: Dict[str, List[GenericResourceDef]] = field(default_factory=dict)

    # Additional metadata
    metadata: Dict[str, Any] = field(default_factory=dict)

    def get_resources(self, resource_type: str) -> List[GenericResourceDef]:
        """Get all resources of a specific type"""
        return self.resources.get(resource_type, [])

    def get_resource(self, resource_type: str, resource_id: str) -> Optional[GenericResourceDef]:
        """Get a specific resource by type and ID"""
        for res in self.get_resources(resource_type):
            if res.resource_id == resource_id:
                return res
        return None

    def get_resource_types(self) -> List[str]:
        """Get all available resource types"""
        return list(self.resources.keys())

    def get_resource_count(self, resource_type: str) -> int:
        """Get count of resources of a specific type"""
        return len(self.get_resources(resource_type))

    def add_resource(self, resource: GenericResourceDef):
        """Add a resource to the chip"""
        if resource.resource_type not in self.resources:
            self.resources[resource.resource_type] = []
        self.resources[resource.resource_type].append(resource)


class ChipDefinitionLoader:
    """Loads chip definitions from YAML files"""

    @staticmethod
    def load_from_yaml(yaml_path: Path) -> Optional[ChipDefinition]:
        """Load a chip definition from a YAML file"""
        if not yaml_path.exists():
            return None

        with open(yaml_path, 'r', encoding='utf-8') as f:
            data = yaml.safe_load(f)

        if not data or 'name' not in data:
            return None

        chip = ChipDefinition(
            name=data['name'],
            family=data.get('family', ''),
            package=data.get('package', ''),
            description=data.get('description', ''),
            metadata=data.get('metadata', {})
        )

        # Load resources
        resources_data = data.get('resources', {})
        for resource_type, resources_list in resources_data.items():
            for res_data in resources_list:
                resource = GenericResourceDef(
                    resource_type=resource_type,
                    resource_id=res_data.get('resource_id', ''),
                    display_name=res_data.get('display_name', res_data.get('resource_id', '')),
                    properties=res_data.get('properties', {})
                )
                chip.add_resource(resource)

        return chip

    @staticmethod
    def save_to_yaml(chip: ChipDefinition, yaml_path: Path):
        """Save a chip definition to a YAML file"""
        data = {
            'name': chip.name,
            'family': chip.family,
            'package': chip.package,
            'description': chip.description,
            'resources': {},
            'metadata': chip.metadata
        }

        for resource_type, resources in chip.resources.items():
            data['resources'][resource_type] = [
                {
                    'resource_id': res.resource_id,
                    'display_name': res.display_name,
                    'properties': res.properties
                }
                for res in resources
            ]

        with open(yaml_path, 'w', encoding='utf-8') as f:
            yaml.dump(data, f, default_flow_style=False, allow_unicode=True, sort_keys=False)


# Legacy compatibility: Convert old-style chip definitions to new format
def convert_legacy_chip(legacy_chip) -> ChipDefinition:
    """Build the generic chip the hardware mapping uses from a chip definition.

    Peripheral instances come from the chip's effective resources (its
    ``resources`` plus any legacy typed lists); ``gpio_port`` / ``gpio_pin``
    instances are derived from its pin table.
    """
    chip = ChipDefinition(
        name=legacy_chip.name,
        family=getattr(legacy_chip, 'family', ''),
        package=getattr(legacy_chip, 'package', ''),
        description=getattr(legacy_chip, 'description', ''),
        metadata=getattr(legacy_chip, 'metadata', {})
    )

    effective = legacy_chip.effective_resources() if hasattr(legacy_chip, 'effective_resources') else {}
    pin_types = {'gpio_port', 'gpio_pin'}

    for res_type, instances in effective.items():
        if res_type in pin_types:
            continue        # derived from the pin table below
        for res in instances:
            chip.add_resource(GenericResourceDef(
                resource_type=res_type,
                resource_id=res.resource_id,
                display_name=res.display_name,
                properties=dict(res.properties),
            ))

    for port_name, pins in getattr(legacy_chip, 'ports', {}).items():
        port_index = port_number_of(port_name)
        chip.add_resource(GenericResourceDef(
            resource_type='gpio_port',
            resource_id=port_name,
            display_name=f"Port {port_name}",
            properties={
                'port_index': port_index,
                'pin_count': len(pins),
                'pins': sorted(p.pin for p in pins),     # real pin numbers; a port may have gaps
            }
        ))
        for pin in pins:
            chip.add_resource(GenericResourceDef(
                resource_type='gpio_pin',
                resource_id=pin.name,
                display_name=pin.name,
                properties={
                    'port': pin.port,
                    'port_index': port_index,
                    'pin': pin.pin,
                    'alternate_functions': pin.alternate_functions,
                    'default_direction': pin.default_direction
                }
            ))

    # Pin-type instances described directly in "resources" (a chip without a pin
    # table, or ports/pins the table does not have) are mapped as well
    derived = {(r.resource_type, r.resource_id)
               for t in pin_types for r in chip.get_resources(t)}
    for res_type in sorted(pin_types):
        for res in effective.get(res_type, []):
            if (res_type, res.resource_id) not in derived:
                properties = dict(res.properties)
                # The Port rule iterates real pin numbers: a port given only by its
                # pin count has pins 0 .. pin_count-1
                if (res_type == 'gpio_port' and 'pins' not in properties
                        and isinstance(properties.get('pin_count'), int)):
                    properties['pins'] = list(range(properties['pin_count']))
                chip.add_resource(GenericResourceDef(
                    resource_type=res_type,
                    resource_id=res.resource_id,
                    display_name=res.display_name,
                    properties=properties,
                ))

    return chip
