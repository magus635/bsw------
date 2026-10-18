"""
Generic Resource Model
Provides a universal model for describing hardware resources
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional

import yaml


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
        port_index = ord(port_name[-1]) - ord('A') if port_name.endswith(tuple('ABCDEFGHIJKLMNOP')) else 0
        chip.add_resource(GenericResourceDef(
            resource_type='gpio_port',
            resource_id=port_name,
            display_name=f"Port {port_name[-1] if port_name else port_name}",
            properties={
                'port_index': port_index,
                'pin_count': len(pins)
            }
        ))
        for pin in pins:
            chip.add_resource(GenericResourceDef(
                resource_type='gpio_pin',
                resource_id=pin.name,
                display_name=pin.name,
                properties={
                    'port': pin.port,
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
                chip.add_resource(GenericResourceDef(
                    resource_type=res_type,
                    resource_id=res.resource_id,
                    display_name=res.display_name,
                    properties=dict(res.properties),
                ))

    return chip
