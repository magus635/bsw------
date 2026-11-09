"""Module manifest loading and writing."""

import json
from pathlib import Path

from .errors import PackageError
from .types import PackageFile, ModuleManifest


def load_manifest(pkg_dir: Path) -> ModuleManifest:
    """Load module.json manifest from package directory.

    Args:
        pkg_dir: Package directory path

    Returns:
        ModuleManifest instance

    Raises:
        PackageError: If manifest missing, schema version unsupported
    """
    manifest_path = pkg_dir / "module.json"
    if not manifest_path.exists():
        raise PackageError(f"No module.json in {pkg_dir}")

    with open(manifest_path, "r", encoding="utf-8") as f:
        data = json.load(f)

    schema = data.get("schema")
    if schema != 1:
        raise PackageError(
            f"Unsupported manifest schema {schema} in {manifest_path}, expected 1"
        )

    # Convert file entries to PackageFile instances
    files = []
    for f_entry in data.get("files", []):
        if isinstance(f_entry, str):
            files.append(PackageFile(path=f_entry))
        else:
            files.append(PackageFile(
                path=f_entry["path"],
                chips=f_entry.get("chips", [])
            ))

    return ModuleManifest(
        module=data["module"],
        definition=data["definition"],
        implementation_path=data.get("implementation_path"),
        files=files,
        pre=data.get("pre", []),
        rec=data.get("rec", []),
        templates=data.get("templates"),
        resources=data.get("resources"),
        implementation=data.get("implementation"),
        exchange_copies=data.get("exchange_copies", []),
        origin=data.get("origin", {}),
        inferred=data.get("inferred", False),
        chip_selector=data.get("chip_selector"),
    )


def write_manifest(pkg_dir: Path, m: ModuleManifest) -> None:
    """Write module manifest to package directory.

    Args:
        pkg_dir: Package directory path
        m: ModuleManifest to write
    """
    manifest_path = pkg_dir / "module.json"

    # Convert to dict and handle PackageFile serialization
    data = {
        "schema": 1,
        "module": m.module,
        "definition": m.definition,
    }

    if m.implementation_path is not None:
        data["implementation_path"] = m.implementation_path

    # Serialize files
    files_data = []
    for pf in m.files:
        if not pf.chips:
            files_data.append(pf.path)
        else:
            files_data.append({"path": pf.path, "chips": pf.chips})
    data["files"] = files_data

    if m.pre:
        data["pre"] = m.pre
    if m.rec:
        data["rec"] = m.rec
    if m.templates is not None:
        data["templates"] = m.templates
    if m.resources is not None:
        data["resources"] = m.resources
    if m.implementation is not None:
        data["implementation"] = m.implementation
    if m.exchange_copies:
        data["exchange_copies"] = m.exchange_copies
    if m.origin:
        data["origin"] = m.origin
    if m.inferred:
        data["inferred"] = m.inferred
    if m.chip_selector is not None:
        data["chip_selector"] = m.chip_selector

    # Sort keys for deterministic output, use POSIX-style paths
    with open(manifest_path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2, sort_keys=True, ensure_ascii=False)
        f.write("\n")


def infer_package(pkg_dir: Path) -> ModuleManifest:
    """Infer package manifest from directory structure.

    Tries module.json first, falls back to plugin.xml inference.

    Args:
        pkg_dir: Package directory path

    Returns:
        ModuleManifest instance

    Raises:
        PackageError: If neither module.json nor plugin.xml found
    """
    manifest_path = pkg_dir / "module.json"
    if manifest_path.exists():
        return load_manifest(pkg_dir)

    # Avoid circular import by importing here
    from .eb_plugin import infer_from_plugin_xml

    plugin_xml = pkg_dir / "plugin.xml"
    if plugin_xml.exists():
        return infer_from_plugin_xml(pkg_dir)

    raise PackageError(
        f"No module.json or plugin.xml found in {pkg_dir}"
    )
