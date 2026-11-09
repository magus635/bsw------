"""Format 8 projects: modules load and are added through module packages."""
import json
import shutil
from pathlib import Path

import pytest

from autosar_configurator.core.packages.library import LibraryRef, scan_library
from autosar_configurator.core.workspace_manager import (
    WorkspaceManager,
    package_for_path,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
EB_PLUGINS = REPO_ROOT / "test_import_project" / "Def" / "plugins"
CHIP = "THA6206_LFBGA292"

pytestmark = pytest.mark.skipif(not EB_PLUGINS.is_dir(), reason="EB plugin fixture missing")


def _eb_library() -> LibraryRef:
    return LibraryRef(path=EB_PLUGINS.as_posix(), kind="eb-plugins", exclude=[])


def _package(module: str):
    for pkg in scan_library(_eb_library(), REPO_ROOT):
        if pkg.manifest.module == module:
            return pkg
    raise AssertionError(f"{module} package not found in fixture")


def _write_dpa(path: Path, libraries, modules, selected_chip=CHIP):
    data = {
        "format_version": 8,
        "name": path.stem,
        "project_type": "Vector DaVinci",
        "variants": ["Default"],
        "active_variant": "Default",
        "available_chips": [CHIP],
        "selected_chip": selected_chip,
        "module_libraries": [lib.to_dict() for lib in libraries],
        "modules": modules,
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data), encoding="utf-8")


def test_v8_loads_definition_from_package(tmp_path):
    project_file = tmp_path / "proj" / "P.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("P", project_file, format_version=8)
    project.selected_chip = CHIP
    project.module_libraries.append(_eb_library())

    manager = project.add_module_from_package(_package("Mcu"), 0)
    assert project.module_entries["Mcu"].definition == "/THA6_AS440_FuSa/Mcu"
    assert project.module_entries["Mcu"].library == 0
    assert project.packages["Mcu"].manifest.module == "Mcu"
    general = manager.module_def.containers["McuGeneralConfiguration"]
    manager.create_container_instance(general)
    wm.save_project()
    assert (tmp_path / "proj" / "config" / "Mcu.arxml").is_file()

    loaded, failed = WorkspaceManager().load_project(project_file)
    assert failed == []
    mcu = loaded.module_managers["Mcu"]
    assert mcu.module_def.ar_path == "/THA6_AS440_FuSa/Mcu"
    assert [c.short_name for c in mcu.configuration.containers] == ["McuGeneralConfiguration"]
    assert loaded.packages["Mcu"].manifest.definition == "/THA6_AS440_FuSa/Mcu"
    assert loaded.module_entries["Mcu"].config_path == "config/Mcu.arxml"


def test_v8_missing_package_reports_failure(tmp_path):
    project_file = tmp_path / "P.dpa"
    _write_dpa(project_file, [_eb_library()], [{
        "name": "Mcu",
        "definition": "/Nowhere/Mcu",
        "library": 0,
        "config_path": "config/Mcu.arxml",
    }])

    project, failed = WorkspaceManager().load_project(project_file)

    assert "Mcu" not in project.module_managers
    assert "Mcu" in project.module_entries  # kept so a save does not drop it
    names = [name for name, _ in failed]
    assert names == ["Mcu"]
    assert "/Nowhere/Mcu" in failed[0][1]


def test_v8_resources_from_package(tmp_path):
    # Native package whose definition is nested, so the resource directory is
    # reached only through the package (not through the definition's plugin root)
    lib_dir = tmp_path / "lib"
    pkg_dir = lib_dir / "Res"
    (pkg_dir / "def" / "xdm").mkdir(parents=True)
    shutil.copy(EB_PLUGINS / "Resource_THA6_AS440" / "config" / "Resource.xdm",
                pkg_dir / "def" / "xdm" / "Resource.xdm")
    (pkg_dir / "resource").mkdir()
    (pkg_dir / "resource" / f"Res_{CHIP}.properties").write_text(
        "PkgTest.Marker=4711\n", encoding="utf-8")
    (pkg_dir / "resource" / "Res_THA6412_BGA516.properties").write_text(
        "PkgTest.Other=1\n", encoding="utf-8")
    (pkg_dir / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "Resource",
        "definition": "/THA6_AS440_FuSa/Resource",
        "files": ["def/xdm/Resource.xdm"],
        "resources": "resource",
    }), encoding="utf-8")

    project_file = tmp_path / "proj" / "P.dpa"
    _write_dpa(project_file, [LibraryRef(path="../lib", kind="package")], [{
        "name": "Resource",
        "definition": "/THA6_AS440_FuSa/Resource",
        "library": 0,
        "config_path": "config/Resource.arxml",
    }])

    project, failed = WorkspaceManager().load_project(project_file)

    assert failed == []
    assert "Resource" in project.module_managers
    assert str(project.ecu_resources.get("PkgTest.Marker")) == "4711"
    assert "PkgTest.Other" not in project.ecu_resources


def test_package_for_path(tmp_path):
    wm = WorkspaceManager()
    project = wm.create_project("P", tmp_path / "P.dpa", format_version=8)
    project.module_libraries.append(_eb_library())

    hit = package_for_path(project, EB_PLUGINS / "Mcu_THA6_AS440" / "config" / "Mcu.xdm")
    assert hit is not None
    index, pkg = hit
    assert index == 0
    assert pkg.manifest.module == "Mcu"

    assert package_for_path(project, tmp_path / "elsewhere" / "Mcu.xdm") is None
