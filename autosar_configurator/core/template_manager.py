"""
Template Manager
Manages configuration templates for quick application
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Dict, Any, Optional
import yaml


@dataclass
class TemplateParameter:
    """A configurable parameter in a template"""
    name: str
    display_name: str
    param_type: str  # integer, string, boolean, enumeration, float
    default_value: Any
    description: str = ""
    min_value: Optional[Any] = None
    max_value: Optional[Any] = None
    options: List[str] = field(default_factory=list)  # For enumeration type


@dataclass
class ConfigTemplate:
    """A configuration template"""
    name: str
    module: str
    category: str
    description: str = ""
    container_def: str = ""  # Target container definition path

    # Parameters that can be adjusted by user
    adjustable_params: List[TemplateParameter] = field(default_factory=list)

    # Fixed parameters (always applied as-is)
    fixed_params: Dict[str, Any] = field(default_factory=dict)

    # Sub-container templates (for nested structures)
    sub_templates: List['ConfigTemplate'] = field(default_factory=list)

    # Metadata
    version: str = "1.0"
    author: str = ""
    tags: List[str] = field(default_factory=list)

    def get_all_params(self, user_values: Dict[str, Any] = None) -> Dict[str, Any]:
        """Get all parameters with user values merged in

        Args:
            user_values: User-provided values for adjustable parameters

        Returns:
            Dict of all parameter values
        """
        params = dict(self.fixed_params)

        for adj_param in self.adjustable_params:
            if user_values and adj_param.name in user_values:
                params[adj_param.name] = user_values[adj_param.name]
            else:
                params[adj_param.name] = adj_param.default_value

        return params


class TemplateManager:
    """Manages configuration templates"""

    def __init__(self, templates_dir: Optional[Path] = None):
        """Initialize template manager

        Args:
            templates_dir: Directory containing template YAML files.
                          If None, loads built-in templates and attempts to
                          load from the default data/templates directory.
        """
        self._templates: Dict[str, ConfigTemplate] = {}
        self._categories: Dict[str, List[str]] = {}  # category -> [template_names]
        self._modules: Dict[str, List[str]] = {}  # module -> [template_names]

        if templates_dir:
            self._load_templates_from_directory(templates_dir)
        else:
            # Load built-in templates first
            self._load_builtin_templates()

            # Also try to load from default data directory
            default_dir = Path(__file__).parent.parent / "data" / "templates"
            if default_dir.exists():
                self._load_templates_from_directory(default_dir)

    def _load_templates_from_directory(self, templates_dir: Path):
        """Load templates from YAML files in directory"""
        if not templates_dir.exists():
            return

        for yaml_file in templates_dir.rglob("*.yaml"):
            try:
                template = self._load_template_from_yaml(yaml_file)
                if template:
                    self._register_template(template)
            except Exception as e:
                print(f"Warning: Failed to load template from {yaml_file}: {e}")

    def _load_template_from_yaml(self, yaml_path: Path) -> Optional[ConfigTemplate]:
        """Load a template from YAML file"""
        with open(yaml_path, 'r', encoding='utf-8') as f:
            data = yaml.safe_load(f)

        if not data:
            return None

        metadata = data.get('metadata', {})
        if not metadata.get('name'):
            return None

        template = ConfigTemplate(
            name=metadata['name'],
            module=metadata.get('module', ''),
            category=metadata.get('category', 'General'),
            description=metadata.get('description', ''),
            version=metadata.get('version', '1.0'),
            author=metadata.get('author', ''),
            tags=metadata.get('tags', []),
        )

        # Load applicability
        applicability = data.get('applicability', {})
        template.container_def = applicability.get('container_def', '')

        # Load parameters
        params = data.get('parameters', {})

        # Adjustable parameters
        for adj_data in params.get('adjustable', []):
            adj_param = TemplateParameter(
                name=adj_data['name'],
                display_name=adj_data.get('display_name', adj_data['name']),
                param_type=adj_data.get('type', 'string'),
                default_value=adj_data.get('default'),
                description=adj_data.get('description', ''),
                min_value=adj_data.get('min'),
                max_value=adj_data.get('max'),
                options=adj_data.get('options', []),
            )
            template.adjustable_params.append(adj_param)

        # Fixed parameters
        template.fixed_params = params.get('fixed', {})

        return template

    def _load_builtin_templates(self):
        """Load built-in templates"""
        # CAN 500kbps Standard
        can_500k = ConfigTemplate(
            name="CAN 500kbps Standard",
            module="Can",
            category="Communication",
            description="Standard CAN configuration at 500kbps",
            container_def="CanConfigSet/CanController",
            adjustable_params=[
                TemplateParameter(
                    name="CanControllerDefaultBaudrate",
                    display_name="Baudrate (bps)",
                    param_type="integer",
                    default_value=500000,
                    min_value=10000,
                    max_value=1000000,
                    description="CAN bus baudrate in bits per second"
                ),
                TemplateParameter(
                    name="CanControllerId",
                    display_name="Controller ID",
                    param_type="integer",
                    default_value=0,
                    min_value=0,
                    max_value=7,
                    description="CAN controller hardware ID"
                ),
            ],
            fixed_params={
                "CanControllerActivation": True,
                "CanControllerRxProcessing": "POLLING",
                "CanControllerTxProcessing": "POLLING",
            },
            tags=["can", "communication", "standard"]
        )
        self._register_template(can_500k)

        # CAN 1Mbps High Speed
        can_1m = ConfigTemplate(
            name="CAN 1Mbps High Speed",
            module="Can",
            category="Communication",
            description="High speed CAN configuration at 1Mbps",
            container_def="CanConfigSet/CanController",
            adjustable_params=[
                TemplateParameter(
                    name="CanControllerDefaultBaudrate",
                    display_name="Baudrate (bps)",
                    param_type="integer",
                    default_value=1000000,
                    min_value=500000,
                    max_value=1000000,
                ),
                TemplateParameter(
                    name="CanControllerId",
                    display_name="Controller ID",
                    param_type="integer",
                    default_value=0,
                    min_value=0,
                    max_value=7,
                ),
            ],
            fixed_params={
                "CanControllerActivation": True,
                "CanControllerRxProcessing": "INTERRUPT",
                "CanControllerTxProcessing": "INTERRUPT",
            },
            tags=["can", "communication", "high-speed"]
        )
        self._register_template(can_1m)

        # SPI Master Basic
        spi_master = ConfigTemplate(
            name="SPI Master Basic",
            module="Spi",
            category="Communication",
            description="Basic SPI master configuration",
            container_def="SpiDriver/SpiChannel",
            adjustable_params=[
                TemplateParameter(
                    name="SpiChannelId",
                    display_name="Channel ID",
                    param_type="integer",
                    default_value=0,
                    min_value=0,
                    max_value=15,
                ),
                TemplateParameter(
                    name="SpiDefaultData",
                    display_name="Default Data",
                    param_type="integer",
                    default_value=0xFF,
                    description="Default data to send when no data available"
                ),
                TemplateParameter(
                    name="SpiDataWidth",
                    display_name="Data Width (bits)",
                    param_type="enumeration",
                    default_value="8",
                    options=["8", "16", "32"],
                ),
            ],
            fixed_params={
                "SpiChannelType": "IB",
            },
            tags=["spi", "communication", "master"]
        )
        self._register_template(spi_master)

        # ADC Single Channel
        adc_single = ConfigTemplate(
            name="ADC Single Channel",
            module="Adc",
            category="Analog",
            description="Single ADC channel configuration",
            container_def="AdcConfigSet/AdcHwUnit/AdcGroup/AdcGroupDefinition",
            adjustable_params=[
                TemplateParameter(
                    name="AdcChannelId",
                    display_name="Channel ID",
                    param_type="integer",
                    default_value=0,
                    min_value=0,
                    max_value=31,
                ),
                TemplateParameter(
                    name="AdcGroupConversionMode",
                    display_name="Conversion Mode",
                    param_type="enumeration",
                    default_value="ADC_CONV_MODE_ONESHOT",
                    options=["ADC_CONV_MODE_ONESHOT", "ADC_CONV_MODE_CONTINUOUS"],
                ),
            ],
            fixed_params={
                "AdcGroupAccessMode": "ADC_ACCESS_MODE_SINGLE",
                "AdcStreamingNumSamples": 1,
            },
            tags=["adc", "analog", "single-channel"]
        )
        self._register_template(adc_single)

        # Port GPIO Output
        port_output = ConfigTemplate(
            name="GPIO Output Pin",
            module="Port",
            category="IO",
            description="Configure a GPIO pin as output",
            container_def="PortConfigSet/PortContainer/PortPin",
            adjustable_params=[
                TemplateParameter(
                    name="PortPinId",
                    display_name="Pin ID",
                    param_type="integer",
                    default_value=0,
                    min_value=0,
                    max_value=255,
                ),
                TemplateParameter(
                    name="PortPinLevelValue",
                    display_name="Initial Level",
                    param_type="enumeration",
                    default_value="PORT_PIN_LEVEL_LOW",
                    options=["PORT_PIN_LEVEL_LOW", "PORT_PIN_LEVEL_HIGH"],
                ),
            ],
            fixed_params={
                "PortPinDirection": "PORT_PIN_OUT",
                "PortPinDirectionChangeable": False,
                "PortPinModeChangeable": False,
            },
            tags=["port", "gpio", "output"]
        )
        self._register_template(port_output)

        # Port GPIO Input
        port_input = ConfigTemplate(
            name="GPIO Input Pin",
            module="Port",
            category="IO",
            description="Configure a GPIO pin as input",
            container_def="PortConfigSet/PortContainer/PortPin",
            adjustable_params=[
                TemplateParameter(
                    name="PortPinId",
                    display_name="Pin ID",
                    param_type="integer",
                    default_value=0,
                    min_value=0,
                    max_value=255,
                ),
            ],
            fixed_params={
                "PortPinDirection": "PORT_PIN_IN",
                "PortPinDirectionChangeable": False,
                "PortPinModeChangeable": False,
            },
            tags=["port", "gpio", "input"]
        )
        self._register_template(port_input)

    def _register_template(self, template: ConfigTemplate):
        """Register a template"""
        self._templates[template.name] = template

        # Index by category
        if template.category not in self._categories:
            self._categories[template.category] = []
        if template.name not in self._categories[template.category]:
            self._categories[template.category].append(template.name)

        # Index by module
        if template.module not in self._modules:
            self._modules[template.module] = []
        if template.name not in self._modules[template.module]:
            self._modules[template.module].append(template.name)

    def get_template(self, name: str) -> Optional[ConfigTemplate]:
        """Get template by name"""
        return self._templates.get(name)

    def list_templates(self,
                       module: Optional[str] = None,
                       category: Optional[str] = None) -> List[ConfigTemplate]:
        """List templates, optionally filtered by module or category

        Args:
            module: Filter by module name
            category: Filter by category name

        Returns:
            List of matching templates
        """
        names = set(self._templates.keys())

        if module:
            module_names = set(self._modules.get(module, []))
            names = names.intersection(module_names)

        if category:
            category_names = set(self._categories.get(category, []))
            names = names.intersection(category_names)

        return [self._templates[name] for name in sorted(names)]

    def list_categories(self) -> List[str]:
        """List all template categories"""
        return sorted(self._categories.keys())

    def list_modules(self) -> List[str]:
        """List all modules with templates"""
        return sorted(self._modules.keys())

    def apply_template(self,
                       template: ConfigTemplate,
                       user_values: Dict[str, Any],
                       config_manager,
                       parent_instance=None,
                       instance_name: Optional[str] = None):
        """Apply a template to create a new configuration instance

        Args:
            template: Template to apply
            user_values: User-provided values for adjustable parameters
            config_manager: Configuration manager instance
            parent_instance: Parent container instance (if nested)
            instance_name: Custom instance name

        Returns:
            Created container instance
        """
        # Get container definition
        container_def = config_manager.get_container_def_by_path(template.container_def)
        if not container_def:
            raise ValueError(f"Container definition not found: {template.container_def}")

        # Create instance
        instance = config_manager.create_container_instance(
            container_def,
            parent=parent_instance,
            instance_name=instance_name
        )

        # Apply all parameters
        all_params = template.get_all_params(user_values)
        for param_name, value in all_params.items():
            try:
                config_manager.set_parameter_value(instance, param_name, value)
            except Exception as e:
                print(f"Warning: Failed to set {param_name}: {e}")

        return instance

    def preview_template(self,
                         template: ConfigTemplate,
                         user_values: Dict[str, Any] = None) -> Dict[str, Any]:
        """Preview what a template application would create

        Args:
            template: Template to preview
            user_values: User-provided values

        Returns:
            Dict representing the configuration that would be created
        """
        params = template.get_all_params(user_values)

        return {
            "template_name": template.name,
            "container_def": template.container_def,
            "parameters": params,
            "description": template.description,
        }

    def search_templates(self, query: str) -> List[ConfigTemplate]:
        """Search templates by name, description, or tags

        Args:
            query: Search query string

        Returns:
            List of matching templates
        """
        query_lower = query.lower()
        results = []

        for template in self._templates.values():
            # Check name
            if query_lower in template.name.lower():
                results.append(template)
                continue

            # Check description
            if query_lower in template.description.lower():
                results.append(template)
                continue

            # Check tags
            if any(query_lower in tag.lower() for tag in template.tags):
                results.append(template)
                continue

            # Check module
            if query_lower in template.module.lower():
                results.append(template)
                continue

        return results
