"""Value collection indexing and in-package merge by AUTOSAR path."""
from pathlib import Path
from typing import Dict, List, Optional
from lxml import etree
from collections import defaultdict

from ..parser.arxml_parser import ArxmlParser
from ..parser.xdm_config_parser import XdmConfigParser
from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue, EcucParameterValue
from .errors import PackageConflictError


def container_key(container: EcucContainerValue) -> str:
    """Generate a unique key for a container based on its path.

    Args:
        container: Container value object

    Returns:
        String key representing the container's path
    """
    return container.get_path()


def param_key(container: EcucContainerValue, name: str) -> str:
    """Generate a unique key for a parameter within a container.

    Args:
        container: Parent container
        name: Parameter name

    Returns:
        String key in format "container_path.param_name"
    """
    return f"{container.get_path()}.{name}"


def ref_key(container: EcucContainerValue, name: str) -> str:
    """Generate a unique key for a reference within a container.

    Args:
        container: Parent container
        name: Reference name

    Returns:
        String key in format "container_path.ref_name"
    """
    return f"{container.get_path()}.{name}"


def index_value_collections(file: Path) -> Dict[str, List[EcucModuleConfiguration]]:
    """Index all value collections in a file by their AUTOSAR path.

    The key is the full AR path (e.g., "/MICROSAR/X_Pre", "/THA6_AS440_FuSa/McuPreConfiguration").
    For .arxml files, uses ArxmlParser.parse_all_module_configurations and builds AR paths
    by walking AR-PACKAGE ancestors. For .xdm files, uses XdmConfigParser.parse_all.

    Args:
        file: Path to .arxml or .xdm file

    Returns:
        Dictionary mapping AR path to list of EcucModuleConfiguration objects
    """
    result = defaultdict(list)

    suffix = file.suffix.lower()

    if suffix == '.arxml':
        # Parse ARXML file
        parser = ArxmlParser()
        _parser = etree.XMLParser(resolve_entities=False, no_network=True)
        tree = etree.parse(str(file), _parser)
        root = tree.getroot()

        # Get all module configurations
        configs = parser.parse_all_module_configurations(root)

        # For each config, build AR path by walking up to AR-PACKAGE ancestors
        for config_elem in root.xpath(".//ar:ECUC-MODULE-CONFIGURATION-VALUES",
                                       namespaces={'ar': 'http://autosar.org/schema/r4.0'}):
            # Get SHORT-NAME
            sn_elem = config_elem.find('.//{http://autosar.org/schema/r4.0}SHORT-NAME')
            if sn_elem is None or not sn_elem.text:
                continue

            short_name = sn_elem.text

            # Walk up to find AR-PACKAGE ancestors
            ar_packages = []
            current = config_elem
            while current is not None:
                current = current.getparent()
                if current is None:
                    break

                # Check if this is an AR-PACKAGE
                tag = current.tag
                if isinstance(tag, str) and tag.endswith('AR-PACKAGE'):
                    sn = current.find('.//{http://autosar.org/schema/r4.0}SHORT-NAME')
                    if sn is not None and sn.text:
                        ar_packages.append(sn.text)

            # Build the AR path
            if ar_packages:
                ar_path = '/' + '/'.join(reversed(ar_packages)) + '/' + short_name
            else:
                ar_path = '/' + short_name

            # Find the corresponding parsed config
            matching_config = next((c for c in configs if c.short_name == short_name), None)
            if matching_config:
                result[ar_path].append(matching_config)

    elif suffix == '.xdm':
        # Parse XDM file
        parser = XdmConfigParser()
        configs_with_paths = parser.parse_all(file)

        for ar_path, config in configs_with_paths:
            result[ar_path].append(config)

    else:
        raise ValueError(f"Unsupported file type: {suffix}")

    return dict(result)


def load_value_collection(files: List[Path], ar_path: str) -> Optional[EcucModuleConfiguration]:
    """Merge all fragments for a given AR path from multiple files.

    Containers with the same short_name are merged recursively. Single-value parameters
    with different values raise PackageConflictError. Multi-value parameters are treated
    as ordered tuples and conflict if they differ.

    Args:
        files: List of files to load from
        ar_path: AUTOSAR path to load (e.g., "/MICROSAR/X_Pre")

    Returns:
        Merged EcucModuleConfiguration, or None if no fragments found

    Raises:
        PackageConflictError: If same parameter has different values in different files
    """
    all_configs = []
    file_for_config = {}  # Map config to its source file

    # Index all files
    for file in files:
        index = index_value_collections(file)
        if ar_path in index:
            for config in index[ar_path]:
                all_configs.append(config)
                file_for_config[id(config)] = file

    if not all_configs:
        return None

    # Start with the first config as the base
    merged = all_configs[0]

    # Merge remaining configs
    for config in all_configs[1:]:
        merged = _merge_configs(merged, config, file_for_config[id(merged)],
                                file_for_config[id(config)], ar_path)

    return merged


def _merge_configs(base: EcucModuleConfiguration,
                   other: EcucModuleConfiguration,
                   base_file: Path,
                   other_file: Path,
                   ar_path: str) -> EcucModuleConfiguration:
    """Merge two EcucModuleConfiguration objects.

    Containers with same short_name are merged recursively.
    Parameters with same name must have same value or PackageConflictError is raised.
    """
    # Merge module-level parameters
    for param_name, param_value in other.parameter_values.items():
        if param_name in base.parameter_values:
            if base.parameter_values[param_name].value != param_value.value:
                raise PackageConflictError(
                    f"Conflict in module parameter {param_name}",
                    path=f"{ar_path}.{param_name}",
                    files=[str(base_file), str(other_file)]
                )
        else:
            base.parameter_values[param_name] = param_value

    # Merge containers
    base_containers_by_name = {c.short_name: c for c in base.containers}

    for other_container in other.containers:
        if other_container.short_name in base_containers_by_name:
            # Merge containers with same name
            base_container = base_containers_by_name[other_container.short_name]
            _merge_containers(base_container, other_container, base_file, other_file,
                              f"{ar_path}/{other_container.short_name}")
        else:
            # Add new container
            base.containers.append(other_container)
            base_containers_by_name[other_container.short_name] = other_container

    return base


def _merge_containers(base: EcucContainerValue,
                      other: EcucContainerValue,
                      base_file: Path,
                      other_file: Path,
                      container_path: str):
    """Merge two containers with the same short_name recursively."""

    # Merge single-value parameters (it's a dict, so iterate over values)
    for param_name, param in other.parameter_values.items():
        if param_name in base.parameter_values:
            existing = base.parameter_values[param_name]
            if existing.value != param.value:
                raise PackageConflictError(
                    f"Conflict in parameter {param_name}",
                    path=f"{container_path}.{param_name}",
                    files=[str(base_file), str(other_file)]
                )
        else:
            base.parameter_values[param_name] = param

    # Merge multi-value parameters
    for param_name, param_values in other.multi_parameter_values.items():
        if param_name in base.multi_parameter_values:
            # Compare as ordered tuples
            base_tuple = tuple((p.value, p.definition_ref) for p in base.multi_parameter_values[param_name])
            other_tuple = tuple((p.value, p.definition_ref) for p in param_values)

            if base_tuple != other_tuple:
                raise PackageConflictError(
                    f"Conflict in multi-value parameter {param_name}",
                    path=f"{container_path}.{param_name}",
                    files=[str(base_file), str(other_file)]
                )
        else:
            base.multi_parameter_values[param_name] = param_values

    # Merge reference values (also a dict)
    for ref_name, ref in other.reference_values.items():
        if ref_name in base.reference_values:
            existing = base.reference_values[ref_name]
            if existing.value_ref != ref.value_ref:
                raise PackageConflictError(
                    f"Conflict in reference {ref_name}",
                    path=f"{container_path}.{ref_name}",
                    files=[str(base_file), str(other_file)]
                )
        else:
            base.reference_values[ref_name] = ref

    # Merge sub-containers
    base_sub_containers_by_name = {c.short_name: c for c in base.sub_containers}

    for other_sub in other.sub_containers:
        if other_sub.short_name in base_sub_containers_by_name:
            # Recursively merge sub-containers with same name
            base_sub = base_sub_containers_by_name[other_sub.short_name]
            _merge_containers(base_sub, other_sub, base_file, other_file,
                              f"{container_path}/{other_sub.short_name}")
        else:
            # Add new sub-container
            base.sub_containers.append(other_sub)
            base_sub_containers_by_name[other_sub.short_name] = other_sub
