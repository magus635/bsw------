"""EB plugin.xml inference as module package."""

from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple
from lxml import etree

from .errors import PackageError
from .types import ModuleManifest, PackageFile


def infer_from_plugin_xml(plugin_dir: Path) -> ModuleManifest:
    """Infer ModuleManifest from EB plugin.xml.

    Inference rules:
    - schema <resource type="xdm"> (and preconfig resources) → files
    - <preconfig path="ASPath:X"> → pre (X is AR path)
    - <data><schemaNode path> → definition
    - autosar/*.arxml → exchange_copies when xdm exists; otherwise definition files
      with chip conditions inferred from ``<Module>_<Chip>.arxml``
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

    parser = etree.XMLParser(resolve_entities=False, no_network=True)
    try:
        tree = etree.parse(str(plugin_xml), parser)
    except Exception as e:
        raise PackageError(f"Failed to parse {plugin_xml}: {e}")

    root = tree.getroot()

    schema_resources: List[Tuple[str, str]] = []  # (res_id, value)
    resource_by_id: Dict[str, str] = {}
    preconfig_resource_ids: List[str] = []
    pre_paths: List[str] = []
    definition_path: str = ""

    for ext in root.findall(".//extension[@point='dreisoft.tresos.launcher2.plugin.configuration']"):
        config = ext.find("configuration")
        if config is None:
            continue

        schema = config.find("schema")
        if schema is not None:
            for res in schema.findall("resource"):
                value = res.get("value")
                res_id = res.get("id") or ""
                res_type = (res.get("type") or "").lower()
                if value and res_id:
                    resource_by_id[res_id] = value
                if value and res_type == "xdm":
                    schema_resources.append((res_id, value))

            for preconf in schema.findall("preconfig"):
                res_id = preconf.get("resourceId")
                if res_id:
                    preconfig_resource_ids.append(res_id)

                path = preconf.get("path")
                if path and path.startswith("ASPath:"):
                    pre_paths.append(path[7:])

        data_elem = config.find("data")
        if data_elem is not None:
            schema_node = data_elem.find("schemaNode")
            if schema_node is not None:
                path = schema_node.get("path")
                if path and path.startswith("ASPath:"):
                    definition_path = path[7:]

    # Also resolve any preconfig resourceId declared outside <schema>
    if not all(rid in resource_by_id for rid in preconfig_resource_ids):
        for res in root.findall(".//resource"):
            res_id = res.get("id")
            value = res.get("value")
            if res_id and value and res_id not in resource_by_id:
                resource_by_id[res_id] = value

    if not definition_path:
        raise PackageError(f"No definition path found in {plugin_xml}")

    module = definition_path.rstrip("/").split("/")[-1]

    preconfig_id_set: Set[str] = set(preconfig_resource_ids)
    files: List[PackageFile] = []
    seen_paths: Set[str] = set()

    def add_file(path: str, chips: Optional[List[str]] = None) -> None:
        norm = path.replace("\\", "/")
        if norm not in seen_paths:
            seen_paths.add(norm)
            files.append(PackageFile(path=norm, chips=chips or []))

    # Non-preconfig schema xdm resources first, then preconfig resources
    for res_id, res_path in schema_resources:
        if not (res_id and res_id in preconfig_id_set):
            add_file(res_path)
    for res_id, res_path in schema_resources:
        if res_id and res_id in preconfig_id_set:
            add_file(res_path)
    for res_id in preconfig_resource_ids:
        res_path = resource_by_id.get(res_id)
        if res_path:
            add_file(res_path)

    # Check autosar/*.arxml: exchange copies when xdm exists, chip-conditional defs otherwise
    exchange_copies: List[str] = []
    autosar_dir = plugin_dir / "autosar"
    autosar_arxmls = (
        sorted(autosar_dir.glob("*.arxml"), key=lambda p: p.name)
        if autosar_dir.is_dir()
        else []
    )
    has_xdm_on_disk = any(
        (plugin_dir / pf.path).suffix.lower() == ".xdm" and (plugin_dir / pf.path).is_file()
        for pf in files
    )
    if autosar_arxmls:
        if has_xdm_on_disk or any(pf.path.lower().endswith(".xdm") for pf in files):
            for arxml_file in autosar_arxmls:
                exchange_copies.append(f"autosar/{arxml_file.name}")
        else:
            prefix = f"{module}_"
            for arxml_file in autosar_arxmls:
                stem = arxml_file.stem
                chips = [stem[len(prefix):]] if stem.startswith(prefix) and len(stem) > len(prefix) else []
                add_file(f"autosar/{arxml_file.name}", chips=chips)

    templates = "generate_PB" if (plugin_dir / "generate_PB").exists() else None
    resources = "resource" if (plugin_dir / "resource").exists() else None

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
