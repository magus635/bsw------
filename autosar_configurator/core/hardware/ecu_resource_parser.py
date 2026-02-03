"""
ECU Resource Parser
Parses ECU resource definitions from EB Tresos XDM files, properties files,
and Resource module configurations to provide data for ecu:get() and ecu:list() functions.
"""
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Any, Optional, Tuple
import re
import xml.etree.ElementTree as ET


@dataclass
class EcuResource:
    """A single ECU resource entry"""
    path: str  # e.g., "Can.MaxModules"
    value: Any  # Can be int, str, list, etc.
    source: str = ""  # Where this came from


class EcuResourceParser:
    """Parses ECU resources from various EB Tresos sources"""

    # Namespace prefixes used in XDM files
    NAMESPACES = {
        'd': 'http://www.tresos.de/_projects/DataModel2/06/data.xsd',
        'a': 'http://www.tresos.de/_projects/DataModel2/16/attribute.xsd',
        'v': 'http://www.tresos.de/_projects/DataModel2/06/schema.xsd',
    }

    def __init__(self):
        self._resources: Dict[str, EcuResource] = {}

    def parse_xdm_file(self, xdm_path: Path) -> Dict[str, Any]:
        """Parse an XDM file to extract ecu:get and ecu:list values.

        XDM files contain expressions like:
        - ecu:get('Can.MaxModules')
        - ecu:list('Can.HwUnitNode')

        We extract the referenced paths and try to find their default/valid values.

        Args:
            xdm_path: Path to the XDM file

        Returns:
            Dict mapping resource paths to their values
        """
        if not xdm_path.exists():
            return {}

        resources = {}

        try:
            tree = ET.parse(xdm_path)
            root = tree.getroot()

            # Find all XPath expressions containing ecu:get or ecu:list
            content = xdm_path.read_text(encoding='utf-8')

            # Extract ecu:get paths
            ecu_get_pattern = r"ecu:get\s*\(\s*['\"]([^'\"]+)['\"]\s*\)"
            for match in re.finditer(ecu_get_pattern, content):
                path = match.group(1)
                if path not in resources:
                    resources[path] = self._find_default_value(root, path)

            # Extract ecu:list paths
            ecu_list_pattern = r"ecu:list\s*\(\s*['\"]([^'\"]+)['\"]\s*\)"
            for match in re.finditer(ecu_list_pattern, content):
                path = match.group(1)
                if path not in resources:
                    resources[path] = self._find_list_values(root, path, content)

            # Store in internal dict
            for path, value in resources.items():
                self._resources[path] = EcuResource(
                    path=path,
                    value=value,
                    source=str(xdm_path)
                )

        except Exception as e:
            print(f"Warning: Failed to parse XDM file {xdm_path}: {e}")

        return resources

    def _find_default_value(self, root: ET.Element, path: str) -> Any:
        """Try to find the default value for an ecu:get path.

        Searches the XDM structure for parameter definitions that might
        provide default values or valid ranges.
        """
        parts = path.split('.')
        if len(parts) < 2:
            return None

        module_name = parts[0]
        param_name = parts[-1]

        # Common default values based on known patterns
        defaults = {
            'MaxModules': 1,
            'MaxNodes': 8,
            'MaxControllers': 8,
            'MaxChannels': 32,
            'MaxHwObjects': 128,
            'MaxHwUnits': 4,
        }

        for pattern, value in defaults.items():
            if pattern in param_name:
                return value

        return None

    def _find_list_values(self, root: ET.Element, path: str, content: str) -> List[str]:
        """Try to find the list values for an ecu:list path.

        For paths like 'Can.HwUnitNode', search for enumeration definitions.
        """
        parts = path.split('.')
        if len(parts) < 2:
            return []

        param_name = parts[-1]

        # Look for RANGE definitions near where this ecu:list is used
        # Pattern: ecu:list('X.Y') ... followed by DEFAULT value
        values = []

        # Look for enumeration values in the same section
        # Common pattern: CAN_CONTROLLER_00, CAN_CONTROLLER_01, etc.
        if 'HwUnit' in param_name or 'Controller' in param_name or 'Channel' in param_name:
            prefix = parts[0].upper()
            # Generate default hardware IDs
            for i in range(8):
                values.append(f"{prefix}_CONTROLLER_{i:02d}")

        return values

    def parse_properties_file(self, props_path: Path) -> Dict[str, Any]:
        """Parse a Java properties file from EB Tresos plugins.

        Properties files contain key=value pairs defining hardware resources.

        Args:
            props_path: Path to the .properties file

        Returns:
            Dict mapping resource paths to their values
        """
        if not props_path.exists():
            return {}

        resources = {}

        try:
            with open(props_path, 'r', encoding='utf-8') as f:
                for line in f:
                    line = line.strip()

                    # Skip comments and empty lines
                    if not line or line.startswith('#') or line.startswith('!'):
                        continue

                    # Handle line continuations
                    while line.endswith('\\'):
                        line = line[:-1] + f.readline().strip()

                    # Parse key=value or key:value
                    if '=' in line:
                        key, value = line.split('=', 1)
                    elif ':' in line:
                        key, value = line.split(':', 1)
                    else:
                        continue

                    key = key.strip()
                    value = value.strip()

                    # Convert to appropriate type
                    parsed_value = self._parse_property_value(value)
                    resources[key] = parsed_value

                    # Store in internal dict
                    self._resources[key] = EcuResource(
                        path=key,
                        value=parsed_value,
                        source=str(props_path)
                    )

        except Exception as e:
            print(f"Warning: Failed to parse properties file {props_path}: {e}")

        return resources

    def _parse_property_value(self, value: str) -> Any:
        """Parse a property value to appropriate Python type"""
        # Try integer
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

        # Try list (comma-separated)
        if ',' in value:
            return [v.strip() for v in value.split(',')]

        return value

    def parse_resource_module(self, resource_def_path: Path, resource_config_path: Path = None) -> Dict[str, Any]:
        """Parse Resource module ARXML files.

        The Resource module typically defines:
        - Core configurations
        - Peripheral allocations
        - Hardware unit mappings

        Args:
            resource_def_path: Path to Resource definition ARXML
            resource_config_path: Path to Resource configuration ARXML

        Returns:
            Dict mapping resource paths to their values
        """
        resources = {}

        # Parse definition file for structure
        if resource_def_path and resource_def_path.exists():
            try:
                tree = ET.parse(resource_def_path)
                root = tree.getroot()

                # Extract module structure info
                # This is a simplified parser - real implementation would
                # use the full ARXML parser from core module
                resources.update(self._parse_arxml_resources(root, "Resource"))

            except Exception as e:
                print(f"Warning: Failed to parse Resource definition: {e}")

        # Parse configuration for actual values
        if resource_config_path and resource_config_path.exists():
            try:
                tree = ET.parse(resource_config_path)
                root = tree.getroot()
                resources.update(self._parse_arxml_resources(root, "Resource"))

            except Exception as e:
                print(f"Warning: Failed to parse Resource configuration: {e}")

        return resources

    def _parse_arxml_resources(self, root: ET.Element, module_name: str) -> Dict[str, Any]:
        """Extract resource definitions from ARXML content"""
        resources = {}

        # Common ARXML namespaces
        ns = {'ar': 'http://autosar.org/schema/r4.0'}

        # Try without namespace prefix first
        for elem in root.iter():
            tag = elem.tag.split('}')[-1] if '}' in elem.tag else elem.tag

            # Look for parameter values
            if tag == 'VALUE':
                parent = elem.getparent() if hasattr(elem, 'getparent') else None
                if parent is not None:
                    parent_tag = parent.tag.split('}')[-1] if '}' in parent.tag else parent.tag
                    if 'PARAMETER-VALUE' in parent_tag:
                        # Get definition ref
                        def_ref = parent.find('.//{*}DEFINITION-REF')
                        if def_ref is not None and def_ref.text:
                            path_parts = def_ref.text.split('/')
                            if path_parts:
                                param_path = f"{module_name}.{path_parts[-1]}"
                                resources[param_path] = elem.text

        return resources

    def scan_plugin_directory(self, plugins_path: Path) -> Dict[str, Any]:
        """Scan EB Tresos plugins directory for resource files.

        Looks for:
        - resource/*.properties
        - resource/*.xml
        - *.xdm

        Args:
            plugins_path: Path to EB Tresos plugins directory

        Returns:
            Dict of all found resources
        """
        if not plugins_path.exists():
            return {}

        all_resources = {}

        # Scan for properties files
        for props_file in plugins_path.rglob("resource/*.properties"):
            resources = self.parse_properties_file(props_file)
            all_resources.update(resources)

        # Scan for XDM files
        for xdm_file in plugins_path.rglob("*.xdm"):
            resources = self.parse_xdm_file(xdm_file)
            all_resources.update(resources)

        return all_resources

    def get_resource(self, path: str) -> Any:
        """Get a resource value by path"""
        if path in self._resources:
            return self._resources[path].value
        return None

    def get_resource_list(self, path: str) -> List[Any]:
        """Get a resource list by path"""
        value = self.get_resource(path)
        if value is None:
            return []
        if isinstance(value, list):
            return value
        return [value]

    def get_all_resources(self) -> Dict[str, Any]:
        """Get all loaded resources as a simple dict"""
        return {path: res.value for path, res in self._resources.items()}

    def load_from_environment(self) -> Dict[str, Any]:
        """Load resources from TRESOS_PLUGINS_PATH environment variable"""
        import os

        plugins_path = os.environ.get('TRESOS_PLUGINS_PATH')
        if not plugins_path:
            return {}

        return self.scan_plugin_directory(Path(plugins_path))


def extract_xdm_resources(xdm_content: str) -> Dict[str, Tuple[str, Any]]:
    """Extract ecu:get and ecu:list references from XDM content.

    Args:
        xdm_content: String content of an XDM file

    Returns:
        Dict mapping resource paths to (type, default_value) tuples
        where type is 'get' or 'list'
    """
    resources = {}

    # Find ecu:get references
    ecu_get_pattern = r"ecu:get\s*\(\s*['\"]([^'\"]+)['\"]\s*\)"
    for match in re.finditer(ecu_get_pattern, xdm_content):
        path = match.group(1)
        if path not in resources:
            resources[path] = ('get', _guess_default_value(path))

    # Find ecu:list references
    ecu_list_pattern = r"ecu:list\s*\(\s*['\"]([^'\"]+)['\"]\s*\)"
    for match in re.finditer(ecu_list_pattern, xdm_content):
        path = match.group(1)
        if path not in resources:
            resources[path] = ('list', _guess_list_values(path))

    return resources


def _guess_default_value(path: str) -> Any:
    """Guess a default value based on the resource path pattern"""
    parts = path.split('.')
    param = parts[-1] if parts else path

    # Numeric patterns
    if any(x in param for x in ['Max', 'Count', 'Num', 'Size']):
        if 'Module' in param:
            return 2
        if 'Node' in param or 'Controller' in param:
            return 8
        if 'Channel' in param:
            return 32
        if 'Object' in param:
            return 128
        return 16

    # Boolean patterns
    if any(x in param for x in ['Enable', 'Support', 'Available']):
        return True

    return None


def _guess_list_values(path: str) -> List[str]:
    """Guess list values based on the resource path pattern"""
    parts = path.split('.')
    module = parts[0] if parts else ""
    param = parts[-1] if parts else path

    # Hardware unit patterns
    if 'HwUnit' in param or 'Controller' in param:
        prefix = module.upper()
        return [f"{prefix}_CONTROLLER_{i:02d}" for i in range(8)]

    if 'Channel' in param:
        prefix = module.upper()
        return [f"{prefix}_CHANNEL_{i:02d}" for i in range(16)]

    if 'Node' in param:
        prefix = module.upper()
        return [f"{prefix}_NODE_{i}" for i in range(8)]

    return []
