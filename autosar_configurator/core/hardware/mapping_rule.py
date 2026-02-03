"""
Mapping Rule Model and Loader
Defines the structure for hardware-to-AUTOSAR mapping rules and loads them from YAML
"""
from dataclasses import dataclass, field
from typing import Dict, List, Any, Optional
from pathlib import Path
import yaml


@dataclass
class UIColumnConfig:
    """Configuration for a table column in the UI"""
    field: str                   # Field path (e.g., "resource.resource_id", "CanControllerBaudRate")
    header: str                  # Column header text
    width: int = 100             # Column width in pixels


@dataclass
class UIOptionConfig:
    """Configuration for an option in the UI"""
    name: str                    # Option name (used in user_config)
    label: str                   # Display label
    type: str                    # UI type: combo, checkbox, spinbox, text
    options: List[Any] = field(default_factory=list)  # Options for combo/radio
    default: Any = None          # Default value
    min_value: Any = None        # Min value for spinbox
    max_value: Any = None        # Max value for spinbox


@dataclass
class UIConfig:
    """UI configuration for a mapping rule"""
    title: str                   # Section title
    layout: str = "table"        # Layout type: table, form, list_with_options
    columns: List[UIColumnConfig] = field(default_factory=list)  # For table layout
    options: List[UIOptionConfig] = field(default_factory=list)  # Additional options
    list_field: str = "resource" # Field to use for list items


@dataclass
class ParameterMapping:
    """Mapping rule for a single parameter"""
    name: str                    # AUTOSAR parameter name
    source: Optional[str] = None # Source path (e.g., "resource.properties.controller_id")
    default: Any = None          # Default value
    transform: Optional[str] = None  # Value transformation expression
    condition: Optional[str] = None  # Condition for including this parameter

    # UI configuration
    ui_type: str = "text"        # UI component type
    ui_options: Dict[str, Any] = field(default_factory=dict)


@dataclass
class ContainerRule:
    """Rule for generating a container"""
    path_template: str           # Container path template with variables
    condition: Optional[str] = None  # Condition for generating this container

    # Parameter mappings
    parameters: List[ParameterMapping] = field(default_factory=list)

    # Sub-container rules (for nested containers)
    sub_containers: List['ContainerRule'] = field(default_factory=list)

    # Iteration configuration
    iterate: Optional[str] = None    # Expression to iterate (e.g., "range(resource.properties.pin_count)")
    iterate_var: str = "item"        # Variable name for iteration item


@dataclass
class MappingRule:
    """Complete mapping rule for a module"""
    module: str                  # Target AUTOSAR module name (e.g., "Can", "Port")
    resource_type: str           # Corresponding chip resource type (e.g., "can_controller")
    description: str = ""        # Rule description

    # Container generation rules
    containers: List[ContainerRule] = field(default_factory=list)

    # UI configuration
    ui_config: Optional[UIConfig] = None

    # Rule extension (inherit from another rule)
    extends: Optional[str] = None


class MappingRuleLoader:
    """Loads mapping rules from YAML files"""

    def __init__(self):
        self._rules: Dict[str, MappingRule] = {}  # module -> rule
        self._rules_by_resource: Dict[str, List[MappingRule]] = {}  # resource_type -> [rules]

    def load_from_yaml(self, yaml_path: Path) -> Optional[MappingRule]:
        """Load a mapping rule from a YAML file"""
        if not yaml_path.exists():
            return None

        with open(yaml_path, 'r', encoding='utf-8') as f:
            data = yaml.safe_load(f)

        if not data or 'module' not in data:
            return None

        rule = self._parse_rule(data)
        self._register_rule(rule)
        return rule

    def load_from_directory(self, directory: Path):
        """Load all mapping rules from a directory"""
        if not directory.exists():
            return

        for yaml_file in directory.glob("*.yaml"):
            try:
                self.load_from_yaml(yaml_file)
            except Exception as e:
                print(f"Warning: Failed to load mapping rule from {yaml_file}: {e}")

    def get_rule(self, module: str) -> Optional[MappingRule]:
        """Get mapping rule for a module"""
        return self._rules.get(module)

    def get_rules_for_resource(self, resource_type: str) -> List[MappingRule]:
        """Get all rules that use a specific resource type"""
        return self._rules_by_resource.get(resource_type, [])

    def get_all_modules(self) -> List[str]:
        """Get all module names with mapping rules"""
        return list(self._rules.keys())

    def get_all_resource_types(self) -> List[str]:
        """Get all resource types used by rules"""
        return list(self._rules_by_resource.keys())

    def _register_rule(self, rule: MappingRule):
        """Register a rule in the internal dictionaries"""
        self._rules[rule.module] = rule

        if rule.resource_type not in self._rules_by_resource:
            self._rules_by_resource[rule.resource_type] = []
        self._rules_by_resource[rule.resource_type].append(rule)

    def _parse_rule(self, data: Dict[str, Any]) -> MappingRule:
        """Parse a mapping rule from dictionary data"""
        rule = MappingRule(
            module=data['module'],
            resource_type=data.get('resource_type', ''),
            description=data.get('description', ''),
            extends=data.get('extends')
        )

        # Parse containers
        containers_data = data.get('containers', [])
        rule.containers = [self._parse_container_rule(c) for c in containers_data]

        # Parse UI config
        ui_data = data.get('ui_config')
        if ui_data:
            rule.ui_config = self._parse_ui_config(ui_data)

        return rule

    def _parse_container_rule(self, data: Dict[str, Any]) -> ContainerRule:
        """Parse a container rule from dictionary data"""
        container = ContainerRule(
            path_template=data.get('path_template', ''),
            condition=data.get('condition'),
            iterate=data.get('iterate'),
            iterate_var=data.get('iterate_var', 'item')
        )

        # Parse parameters
        params_data = data.get('parameters', [])
        container.parameters = [self._parse_parameter_mapping(p) for p in params_data]

        # Parse sub-containers recursively
        sub_data = data.get('sub_containers', [])
        container.sub_containers = [self._parse_container_rule(s) for s in sub_data]

        return container

    def _parse_parameter_mapping(self, data: Dict[str, Any]) -> ParameterMapping:
        """Parse a parameter mapping from dictionary data"""
        return ParameterMapping(
            name=data.get('name', ''),
            source=data.get('source'),
            default=data.get('default'),
            transform=data.get('transform'),
            condition=data.get('condition'),
            ui_type=data.get('ui_type', 'text'),
            ui_options=data.get('ui_options', {})
        )

    def _parse_ui_config(self, data: Dict[str, Any]) -> UIConfig:
        """Parse UI configuration from dictionary data"""
        ui = UIConfig(
            title=data.get('title', ''),
            layout=data.get('layout', 'table'),
            list_field=data.get('list_field', 'resource')
        )

        # Parse columns
        columns_data = data.get('columns', [])
        for col in columns_data:
            if isinstance(col, dict):
                ui.columns.append(UIColumnConfig(
                    field=col.get('field', ''),
                    header=col.get('header', ''),
                    width=col.get('width', 100)
                ))

        # Parse options
        options_data = data.get('options', [])
        for opt in options_data:
            if isinstance(opt, dict):
                ui.options.append(UIOptionConfig(
                    name=opt.get('name', ''),
                    label=opt.get('label', ''),
                    type=opt.get('type', 'text'),
                    options=opt.get('options', []),
                    default=opt.get('default'),
                    min_value=opt.get('min'),
                    max_value=opt.get('max')
                ))

        return ui


# Singleton rule loader instance
_default_rule_loader: Optional[MappingRuleLoader] = None


def get_default_rule_loader() -> MappingRuleLoader:
    """Get the default rule loader (singleton)"""
    global _default_rule_loader
    if _default_rule_loader is None:
        _default_rule_loader = MappingRuleLoader()

        # Load built-in rules
        builtin_rules_dir = Path(__file__).parent.parent.parent / "data" / "mapping_rules"
        if builtin_rules_dir.exists():
            _default_rule_loader.load_from_directory(builtin_rules_dir)

    return _default_rule_loader
