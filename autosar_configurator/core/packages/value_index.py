"""Value collection indexing and in-package merge by AUTOSAR path."""
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional
from lxml import etree

from ..parser.arxml_parser import ArxmlParser
from ..parser.xdm_config_parser import XdmConfigParser
from ..model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucParameterValue,
    EcucReferenceValue,
)
from .errors import PackageConflictError


def container_key(container: EcucContainerValue) -> str:
    """Generate a unique key for a container based on its path.

    Args:
        container: Container value object

    Returns:
        String key "C:<container_path>"
    """
    return "C:" + container.get_path()


def param_key(container: EcucContainerValue, name: str) -> str:
    """Generate a unique key for a parameter within a container.

    Args:
        container: Parent container
        name: Parameter name

    Returns:
        String key "P:<container_path>.<param_name>"
    """
    return f"P:{container.get_path()}.{name}"


def ref_key(container: EcucContainerValue, name: str) -> str:
    """Generate a unique key for a reference within a container.

    Args:
        container: Parent container
        name: Reference name

    Returns:
        String key "R:<container_path>.<ref_name>"
    """
    return f"R:{container.get_path()}.{name}"


def _local(tag) -> str:
    return tag.rsplit("}", 1)[-1] if isinstance(tag, str) else ""


def _clone_param(param: EcucParameterValue) -> EcucParameterValue:
    return EcucParameterValue(
        definition_ref=param.definition_ref,
        value=param.value,
        index=param.index,
        dest_type=param.dest_type,
    )


def _clone_ref(ref: EcucReferenceValue) -> EcucReferenceValue:
    return EcucReferenceValue(
        definition_ref=ref.definition_ref,
        value_ref=ref.value_ref,
        dest_type=ref.dest_type,
        index=ref.index,
    )


def _clone_container(src: EcucContainerValue, parent: Optional[EcucContainerValue],
                     module_name: str) -> EcucContainerValue:
    clone = EcucContainerValue(
        short_name=src.short_name,
        definition_ref=src.definition_ref,
        def_dest_type=src.def_dest_type,
        parent=parent,
        module_name=module_name,
        index=src.index,
        uuid=src.uuid,
        variant=src.variant,
    )
    for name, param in src.parameter_values.items():
        clone.parameter_values[name] = _clone_param(param)
    for name, params in src.multi_parameter_values.items():
        clone.multi_parameter_values[name] = [_clone_param(p) for p in params]
    for name, ref in src.reference_values.items():
        clone.reference_values[name] = _clone_ref(ref)
    for name, refs in src.multi_reference_values.items():
        clone.multi_reference_values[name] = [_clone_ref(r) for r in refs]
    for name in src.unknown_parameters:
        if name in clone.parameter_values:
            clone.unknown_parameters[name] = clone.parameter_values[name]
        elif name in clone.multi_parameter_values:
            clone.unknown_parameters[name] = clone.multi_parameter_values[name]
    for sub in src.sub_containers:
        clone.sub_containers.append(_clone_container(sub, clone, module_name))
    return clone


def _record_container_origins(container: EcucContainerValue, container_path: str,
                              src_file: Path, origin_files: Dict[str, Path]) -> None:
    for name in container.parameter_values:
        origin_files[f"P:{container_path}.{name}"] = src_file
    for name in container.multi_parameter_values:
        origin_files[f"MP:{container_path}.{name}"] = src_file
    for name in container.reference_values:
        origin_files[f"R:{container_path}.{name}"] = src_file
    for name in container.multi_reference_values:
        origin_files[f"MR:{container_path}.{name}"] = src_file
    for sub in container.sub_containers:
        _record_container_origins(sub, f"{container_path}/{sub.short_name}", src_file, origin_files)


def _record_config_origins(config: EcucModuleConfiguration, ar_path: str,
                           src_file: Path, origin_files: Dict[str, Path]) -> None:
    for name in config.parameter_values:
        origin_files[f"P:{ar_path}.{name}"] = src_file
    for container in config.containers:
        _record_container_origins(container, f"{ar_path}/{container.short_name}", src_file, origin_files)


def index_value_collections(file: Path) -> Dict[str, List[EcucModuleConfiguration]]:
    """Index all value collections in a file by their AUTOSAR path.

    The key is the full AR path (e.g., "/MICROSAR/X_Pre", "/THA6_AS440_FuSa/McuPreConfiguration").
    For .arxml files, walks AR-PACKAGE ancestors and parses each ECUC-MODULE-CONFIGURATION-VALUES
    element directly so same-named configs in different packages never shadow one another.
    For .xdm files, uses XdmConfigParser.parse_all.

    Args:
        file: Path to .arxml or .xdm file

    Returns:
        Dictionary mapping AR path to list of EcucModuleConfiguration objects
    """
    result = defaultdict(list)

    suffix = file.suffix.lower()

    if suffix == '.arxml':
        parser = ArxmlParser()
        _parser = etree.XMLParser(resolve_entities=False, no_network=True)
        tree = etree.parse(str(file), _parser)
        root = tree.getroot()

        for config_elem in parser._findall_descendants(root, 'ECUC-MODULE-CONFIGURATION-VALUES'):
            config = parser.parse_ecuc_configuration_values(config_elem)
            if config is None:
                continue

            ar_packages = []
            current = config_elem.getparent()
            while current is not None:
                if _local(current.tag) == 'AR-PACKAGE':
                    pkg_sn = parser._get_short_name(current)
                    if pkg_sn:
                        ar_packages.append(pkg_sn)
                current = current.getparent()

            if ar_packages:
                if config.package_name is None:
                    config.package_name = ar_packages[0]
                ar_path = '/' + '/'.join(reversed(ar_packages)) + '/' + config.short_name
            else:
                ar_path = '/' + config.short_name

            result[ar_path].append(config)

    elif suffix == '.xdm':
        parser = XdmConfigParser()
        configs_with_paths = parser.parse_all(file)

        for ar_path, config in configs_with_paths:
            result[ar_path].append(config)

    else:
        raise ValueError(f"Unsupported file type: {suffix}")

    return dict(result)


def load_value_collection(files: List[Path], ar_path: str) -> Optional[EcucModuleConfiguration]:
    """Merge all fragments for a given AR path from multiple files.

    Containers with the same short_name are merged recursively. Single-value parameters,
    multi-value parameters, single-value references and multi-value references with
    different values raise PackageConflictError. Multi-value entries are treated as
    ordered tuples and conflict if they differ.

    Args:
        files: List of files to load from
        ar_path: AUTOSAR path to load (e.g., "/MICROSAR/X_Pre")

    Returns:
        Merged EcucModuleConfiguration, or None if no fragments found

    Raises:
        PackageConflictError: If same parameter or reference has different values in different files
    """
    all_configs = []
    source_files: List[Path] = []

    for file in files:
        index = index_value_collections(file)
        if ar_path in index:
            for config in index[ar_path]:
                all_configs.append(config)
                source_files.append(file)

    if not all_configs:
        return None

    merged = all_configs[0]
    first_file = source_files[0]
    origin_files: Dict[str, Path] = {}
    _record_config_origins(merged, ar_path, first_file, origin_files)

    for config, src_file in zip(all_configs[1:], source_files[1:]):
        merged = _merge_configs(
            merged, config, first_file, src_file, ar_path, origin_files
        )

    return merged


def _merge_configs(base: EcucModuleConfiguration,
                   other: EcucModuleConfiguration,
                   base_file: Path,
                   other_file: Path,
                   ar_path: str,
                   origin_files: Optional[Dict[str, Path]] = None) -> EcucModuleConfiguration:
    """Merge two EcucModuleConfiguration objects.

    Containers with same short_name are merged recursively.
    Parameters with same name must have same value or PackageConflictError is raised.
    """
    if origin_files is None:
        origin_files = {}

    for param_name, param_value in other.parameter_values.items():
        origin_key = f"P:{ar_path}.{param_name}"
        if param_name in base.parameter_values:
            if base.parameter_values[param_name].value != param_value.value:
                first = origin_files.get(origin_key, base_file)
                raise PackageConflictError(
                    f"Conflict in module parameter {param_name}",
                    path=f"{ar_path}.{param_name}",
                    files=[str(first), str(other_file)]
                )
        else:
            base.parameter_values[param_name] = _clone_param(param_value)
            origin_files[origin_key] = other_file

    base_containers_by_name = {c.short_name: c for c in base.containers}

    for other_container in other.containers:
        container_path = f"{ar_path}/{other_container.short_name}"
        if other_container.short_name in base_containers_by_name:
            base_container = base_containers_by_name[other_container.short_name]
            _merge_containers(
                base_container, other_container, base_file, other_file,
                container_path, origin_files
            )
        else:
            cloned = _clone_container(other_container, None, base.short_name)
            base.add_container(cloned)
            base_containers_by_name[cloned.short_name] = cloned
            _record_container_origins(cloned, container_path, other_file, origin_files)

    return base


def _merge_containers(base: EcucContainerValue,
                      other: EcucContainerValue,
                      base_file: Path,
                      other_file: Path,
                      container_path: str,
                      origin_files: Optional[Dict[str, Path]] = None):
    """Merge two containers with the same short_name recursively."""
    if origin_files is None:
        origin_files = {}

    # Merge single-value parameters
    for param_name, param in other.parameter_values.items():
        origin_key = f"P:{container_path}.{param_name}"
        if param_name in base.parameter_values:
            existing = base.parameter_values[param_name]
            if existing.value != param.value:
                first = origin_files.get(origin_key, base_file)
                raise PackageConflictError(
                    f"Conflict in parameter {param_name}",
                    path=f"{container_path}.{param_name}",
                    files=[str(first), str(other_file)]
                )
        else:
            cloned = _clone_param(param)
            base.parameter_values[param_name] = cloned
            if param_name in other.unknown_parameters:
                base.unknown_parameters[param_name] = cloned
            origin_files[origin_key] = other_file

    # Merge multi-value parameters (ordered tuples compared by value)
    for param_name, param_values in other.multi_parameter_values.items():
        origin_key = f"MP:{container_path}.{param_name}"
        if param_name in base.multi_parameter_values:
            base_tuple = tuple(p.value for p in base.multi_parameter_values[param_name])
            other_tuple = tuple(p.value for p in param_values)
            if base_tuple != other_tuple:
                first = origin_files.get(origin_key, base_file)
                raise PackageConflictError(
                    f"Conflict in multi-value parameter {param_name}",
                    path=f"{container_path}.{param_name}",
                    files=[str(first), str(other_file)]
                )
        else:
            cloned_list = [_clone_param(p) for p in param_values]
            base.multi_parameter_values[param_name] = cloned_list
            if param_name in other.unknown_parameters:
                base.unknown_parameters[param_name] = cloned_list
            origin_files[origin_key] = other_file

    # Merge single-value references
    for ref_name, ref in other.reference_values.items():
        origin_key = f"R:{container_path}.{ref_name}"
        if ref_name in base.reference_values:
            existing = base.reference_values[ref_name]
            if existing.value_ref != ref.value_ref:
                first = origin_files.get(origin_key, base_file)
                raise PackageConflictError(
                    f"Conflict in reference {ref_name}",
                    path=f"{container_path}.{ref_name}",
                    files=[str(first), str(other_file)]
                )
        else:
            base.reference_values[ref_name] = _clone_ref(ref)
            origin_files[origin_key] = other_file

    # Merge multi-value references (ordered tuples compared by value_ref)
    for ref_name, ref_values in other.multi_reference_values.items():
        origin_key = f"MR:{container_path}.{ref_name}"
        if ref_name in base.multi_reference_values:
            base_tuple = tuple(r.value_ref for r in base.multi_reference_values[ref_name])
            other_tuple = tuple(r.value_ref for r in ref_values)
            if base_tuple != other_tuple:
                first = origin_files.get(origin_key, base_file)
                raise PackageConflictError(
                    f"Conflict in multi-value reference {ref_name}",
                    path=f"{container_path}.{ref_name}",
                    files=[str(first), str(other_file)]
                )
        else:
            base.multi_reference_values[ref_name] = [_clone_ref(r) for r in ref_values]
            origin_files[origin_key] = other_file

    # Merge sub-containers
    base_sub_containers_by_name = {c.short_name: c for c in base.sub_containers}

    for other_sub in other.sub_containers:
        sub_path = f"{container_path}/{other_sub.short_name}"
        if other_sub.short_name in base_sub_containers_by_name:
            base_sub = base_sub_containers_by_name[other_sub.short_name]
            _merge_containers(
                base_sub, other_sub, base_file, other_file,
                sub_path, origin_files
            )
        else:
            cloned_sub = _clone_container(other_sub, base, base.module_name)
            base.add_sub_container(cloned_sub)
            base_sub_containers_by_name[cloned_sub.short_name] = cloned_sub
            _record_container_origins(cloned_sub, sub_path, other_file, origin_files)
