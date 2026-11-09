"""EB plugin.xml inference as module package."""

from pathlib import Path
from typing import List, Set
from lxml import etree

from .errors import PackageError
from .types import ModuleManifest, PackageFile


def infer_from_plugin_xml(plugin_dir: Path) -> ModuleManifest:
    """Infer ModuleManifest from EB plugin.xml.

    Inference rules:
    - schema <resource type="xdm"> not referenced by preconfig → files
    - preconfig resource files → files
    - <preconfig path="ASPath:X"> → pre (X is AR path)
    - <data><schemaNode path> → definition
    - autosar/*.arxml → exchange_copies
    - generate_PB/ exists → templates="generate_PB"
    - resource/ exists → resources="resource"
    - module = last segment of definition
    - inferred = True

    Args:
        plugin_dir: EB plugin directory path

    Returns:
        ModuleManifest instance

    Raises:
        PackageError: If plugin.xml missing or malformed
    """
    plugin_xml = plugin_dir / "plugin.xml"
    if not plugin_xml.exists():
        raise PackageError(f"No plugin.xml in {plugin_dir}")

    # Parse with secure settings
    parser = etree.XMLParser(resolve_entities=False, no_network=True)
    try:
        tree = etree.parse(str(plugin_xml), parser)
    except Exception as e:
        raise PackageError(f"Failed to parse {plugin_xml}: {e}")

    root = tree.getroot()

    # Find schema and data sections
    schema_resources: List[str] = []
    preconfig_resource_ids: Set[str] = set()
    pre_paths: List[str] = []
    definition_path: str = ""

    # Find configuration extension
    for ext in root.findall(".//extension[@point='dreisoft.tresos.launcher2.plugin.configuration']"):
        config = ext.find("configuration")
        if config is None:
            continue

        # Schema section
        schema = config.find("schema")
        if schema is not None:
            # Collect schema resources
            for res in schema.findall("resource[@type='xdm']"):
                value = res.get("value")
                if value:
                    res_id = res.get("id")
                    schema_resources.append(value)

            # Collect preconfig references
            for preconf in schema.findall("preconfig"):
                res_id = preconf.get("resourceId")
                if res_id:
                    preconfig_resource_ids.add(res_id)

                # Extract pre path
                path = preconf.get("path")
                if path and path.startswith("ASPath:"):
                    ar_path = path[7:]  # Strip "ASPath:" prefix
                    pre_paths.append(ar_path)

        # Data section
        data_elem = config.find("data")
        if data_elem is not None:
            schema_node = data_elem.find("schemaNode")
            if schema_node is not None:
                path = schema_node.get("path")
                if path and path.startswith("ASPath:"):
                    definition_path = path[7:]

    if not definition_path:
        raise PackageError(f"No definition path found in {plugin_xml}")

    # Build files list: schema resources not referenced by preconfig
    files: List[PackageFile] = []
    for res_path in schema_resources:
        # Check if this resource has an id that's referenced by preconfig
        # We need to re-scan to match resource value to id
        is_preconfig = False
        for ext in root.findall(".//extension[@point='dreisoft.tresos.launcher2.plugin.configuration']"):
            config = ext.find("configuration")
            if config is None:
                continue
            schema = config.find("schema")
            if schema is not None:
                for res in schema.findall("resource[@type='xdm']"):
                    if res.get("value") == res_path:
                        res_id = res.get("id")
                        if res_id and res_id in preconfig_resource_ids:
                            is_preconfig = True
                            break
            if is_preconfig:
                break

        files.append(PackageFile(path=res_path))

    # Check for exchange copies in autosar/
    exchange_copies: List[str] = []
    autosar_dir = plugin_dir / "autosar"
    if autosar_dir.exists():
        for arxml_file in autosar_dir.glob("*.arxml"):
            exchange_copies.append(f"autosar/{arxml_file.name}")

    # Check for template and resource directories
    templates = "generate_PB" if (plugin_dir / "generate_PB").exists() else None
    resources = "resource" if (plugin_dir / "resource").exists() else None

    # Extract module name from definition
    module = definition_path.rstrip("/").split("/")[-1]

    return ModuleManifest(
        module=module,
        definition=definition_path,
        files=files,
        pre=pre_paths,
        rec=[],
        templates=templates,
        resources=resources,
        exchange_copies=sorted(exchange_copies),
        inferred=True,
    )
