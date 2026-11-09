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


def _mcu_entry(**extra):
    entry = {
        "name": "Mcu",
        "definition": "/THA6_AS440_FuSa/Mcu",
        "library": 0,
        "config_path": "config/Mcu.arxml",
    }
    entry.update(extra)
    return entry


def _saved_modules(project_file: Path):
    return json.loads(project_file.read_text(encoding="utf-8"))["modules"]


def test_v8_variant_overrides_round_trip(tmp_path):
    project_file = tmp_path / "proj" / "P.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("P", project_file, format_version=8)
    project.selected_chip = CHIP
    project.variants = ["Default", "V1"]
    project.module_libraries.append(_eb_library())
    manager = project.add_module_from_package(_package("Mcu"), 0)
    overrides = {"V1": {"/Mcu/McuGeneralConfiguration.McuDevErrorDetect": True}}
    manager.configuration.variant_overrides = overrides
    wm.save_project()

    loaded, failed = WorkspaceManager().load_project(project_file)
    assert failed == []
    assert loaded.module_managers["Mcu"].configuration.variant_overrides == overrides


def test_v8_failed_module_keeps_variant_overrides(tmp_path):
    project_file = tmp_path / "P.dpa"
    overrides = {"V1": {"/Mcu/McuGeneralConfiguration.McuDevErrorDetect": True}}
    _write_dpa(project_file, [_eb_library()],
               [_mcu_entry(definition="/Nowhere/Mcu", variant_overrides=overrides)])

    wm = WorkspaceManager()
    project, failed = wm.load_project(project_file)
    assert [name for name, _ in failed] == ["Mcu"]
    wm.save_project()

    (saved,) = _saved_modules(project_file)
    assert saved["definition"] == "/Nowhere/Mcu"
    assert saved["variant_overrides"] == overrides


def test_v8_corrupt_config_is_not_overwritten(tmp_path):
    project_file = tmp_path / "P.dpa"
    _write_dpa(project_file, [_eb_library()], [_mcu_entry()])
    config = tmp_path / "config" / "Mcu.arxml"
    config.parent.mkdir()
    corrupt = b"<AUTOSAR><broken"
    config.write_bytes(corrupt)

    wm = WorkspaceManager()
    project, failed = wm.load_project(project_file)
    assert [name for name, _ in failed] == ["Mcu"]
    assert "Mcu" not in project.module_managers
    assert "Mcu" in project.module_entries
    wm.save_project()

    assert config.read_bytes() == corrupt
    assert [m["name"] for m in _saved_modules(project_file)] == ["Mcu"]


def test_v8_save_writes_modules_sorted_by_name(tmp_path):
    project_file = tmp_path / "P.dpa"
    _write_dpa(project_file, [_eb_library()], [
        _mcu_entry(name="Zeta", definition="/Nowhere/Zeta", config_path="config/Zeta.arxml"),
        _mcu_entry(),
        _mcu_entry(name="Adc", definition="/Nowhere/Adc", config_path="config/Adc.arxml"),
    ])

    wm = WorkspaceManager()
    project, failed = wm.load_project(project_file)
    assert "Mcu" in project.module_managers
    wm.save_project()

    assert [m["name"] for m in _saved_modules(project_file)] == ["Adc", "Mcu", "Zeta"]


def test_v8_removed_module_stays_removed(tmp_path):
    project_file = tmp_path / "proj" / "P.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("P", project_file, format_version=8)
    project.selected_chip = CHIP
    project.module_libraries.append(_eb_library())
    project.add_module_from_package(_package("Mcu"), 0)
    project.add_module_from_package(_package("Dio"), 0)
    wm.save_project()

    wm = WorkspaceManager()
    project, failed = wm.load_project(project_file)
    assert failed == []
    assert sorted(project.module_managers) == ["Dio", "Mcu"]
    project.remove_module("Dio")
    assert "Dio" not in project.module_entries
    assert "Dio" not in project.packages
    wm.save_project()

    assert [m["name"] for m in _saved_modules(project_file)] == ["Mcu"]
    reloaded, failed = WorkspaceManager().load_project(project_file)
    assert failed == []
    assert sorted(reloaded.module_managers) == ["Mcu"]
    assert sorted(reloaded.module_entries) == ["Mcu"]


def test_v8_removing_a_failed_module_forgets_its_entry(tmp_path):
    project_file = tmp_path / "P.dpa"
    overrides = {"V1": {"/Mcu/McuGeneralConfiguration.McuDevErrorDetect": True}}
    _write_dpa(project_file, [_eb_library()],
               [_mcu_entry(definition="/Nowhere/Mcu", variant_overrides=overrides)])
    wm = WorkspaceManager()
    project, _ = wm.load_project(project_file)

    project.remove_module("Mcu")
    assert "Mcu" not in project.module_entries
    assert "Mcu" not in project.unloaded_variant_overrides
    wm.save_project()
    assert _saved_modules(project_file) == []


def test_v8_readded_module_gets_stashed_overrides(tmp_path):
    project_file = tmp_path / "P.dpa"
    overrides = {"V1": {"/Mcu/McuGeneralConfiguration.McuDevErrorDetect": True}}
    _write_dpa(project_file, [_eb_library()],
               [_mcu_entry(definition="/Nowhere/Mcu", variant_overrides=overrides)])
    project, failed = WorkspaceManager().load_project(project_file)
    assert [name for name, _ in failed] == ["Mcu"]
    assert project.unloaded_variant_overrides["Mcu"] == overrides

    manager = project.add_module_from_package(_package("Mcu"), 0)

    assert manager.configuration.variant_overrides == overrides
    assert "Mcu" not in project.unloaded_variant_overrides
    assert project.module_entries["Mcu"].definition == "/THA6_AS440_FuSa/Mcu"


def _mcu_config_with_value(tmp_path) -> bytes:
    """Write config/Mcu.arxml holding one McuGeneralConfiguration with a set value."""
    wm = WorkspaceManager()
    project = wm.create_project("Src", tmp_path / "src" / "Src.dpa", format_version=8)
    project.selected_chip = CHIP
    project.module_libraries.append(_eb_library())
    manager = project.add_module_from_package(_package("Mcu"), 0)
    general = manager.create_container_instance(manager.module_def.containers["McuGeneralConfiguration"])
    manager.set_parameter_value(general, "McuDevErrorDetect", True)
    wm.save_project()
    return (tmp_path / "src" / "config" / "Mcu.arxml").read_bytes()


def _dev_error_detect(manager):
    (general,) = [c for c in manager.configuration.containers
                  if c.short_name == "McuGeneralConfiguration"]
    return str(general.parameter_values["McuDevErrorDetect"].value).lower()


def test_v8_readd_loads_existing_config(tmp_path):
    content = _mcu_config_with_value(tmp_path)
    project_file = tmp_path / "P.dpa"
    _write_dpa(project_file, [_eb_library()], [_mcu_entry(definition="/Nowhere/Mcu")])
    config = tmp_path / "config" / "Mcu.arxml"
    config.parent.mkdir()
    config.write_bytes(content)

    wm = WorkspaceManager()
    project, failed = wm.load_project(project_file)
    assert [name for name, _ in failed] == ["Mcu"]

    manager = project.add_module_from_package(_package("Mcu"), 0)
    assert _dev_error_detect(manager) == "true"
    wm.save_project()

    reloaded, failed = WorkspaceManager().load_project(project_file)
    assert failed == []
    assert _dev_error_detect(reloaded.module_managers["Mcu"]) == "true"


def test_v8_new_module_picks_up_config_file_in_place(tmp_path):
    content = _mcu_config_with_value(tmp_path)
    project_file = tmp_path / "P.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("P", project_file, format_version=8)
    project.selected_chip = CHIP
    project.module_libraries.append(_eb_library())
    (tmp_path / "config").mkdir()
    (tmp_path / "config" / "Mcu.arxml").write_bytes(content)

    manager = project.add_module_from_package(_package("Mcu"), 0)
    assert _dev_error_detect(manager) == "true"


def test_v8_readd_with_corrupt_config_leaves_project_unchanged(tmp_path):
    project_file = tmp_path / "P.dpa"
    overrides = {"V1": {"/Mcu/McuGeneralConfiguration.McuDevErrorDetect": True}}
    _write_dpa(project_file, [_eb_library()], [_mcu_entry(variant_overrides=overrides)])
    config = tmp_path / "config" / "Mcu.arxml"
    config.parent.mkdir()
    config.write_bytes(b"<AUTOSAR><broken")
    project, failed = WorkspaceManager().load_project(project_file)
    assert [name for name, _ in failed] == ["Mcu"]

    with pytest.raises(ValueError):
        project.add_module_from_package(_package("Mcu"), 0)
    assert "Mcu" not in project.module_managers
    assert project.unloaded_variant_overrides["Mcu"] == overrides
    assert config.read_bytes() == b"<AUTOSAR><broken"


def test_v8_snapshot_restore_of_loaded_module(tmp_path):
    project_file = tmp_path / "P.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("P", project_file, format_version=8)
    project.selected_chip = CHIP
    project.module_libraries.append(_eb_library())
    manager = project.add_module_from_package(_package("Mcu"), 0)
    entry = project.module_entries["Mcu"]

    snapshot = project.snapshot_module("Mcu")
    project.remove_module("Mcu")
    project.restore_module(snapshot)

    assert project.module_managers["Mcu"] is manager
    assert project.module_entries["Mcu"] is entry
    assert project.packages["Mcu"].manifest.module == "Mcu"
    assert "Mcu" not in project.unloaded_variant_overrides
    wm.save_project()
    (saved,) = _saved_modules(project_file)
    assert saved["definition"] == "/THA6_AS440_FuSa/Mcu"


def test_v8_snapshot_restore_of_failed_module(tmp_path):
    project_file = tmp_path / "P.dpa"
    overrides = {"V1": {"/Mcu/McuGeneralConfiguration.McuDevErrorDetect": True}}
    _write_dpa(project_file, [_eb_library()],
               [_mcu_entry(definition="/Nowhere/Mcu", variant_overrides=overrides)])
    wm = WorkspaceManager()
    project, _ = wm.load_project(project_file)

    snapshot = project.snapshot_module("Mcu")
    project.remove_module("Mcu")
    project.restore_module(snapshot)

    assert "Mcu" not in project.module_managers
    assert project.module_entries["Mcu"].definition == "/Nowhere/Mcu"
    assert project.unloaded_variant_overrides["Mcu"] == overrides
    wm.save_project()
    (saved,) = _saved_modules(project_file)
    assert saved["variant_overrides"] == overrides


def test_delete_module_command_undo_restores_v8_bookkeeping(tmp_path):
    pytest.importorskip("PySide6")
    from autosar_configurator.ui.commands import DeleteModuleCommand

    project_file = tmp_path / "P.dpa"
    _write_dpa(project_file, [_eb_library()], [
        _mcu_entry(),
        _mcu_entry(name="Gone", definition="/Nowhere/Gone", config_path="config/Gone.arxml",
                   variant_overrides={"V1": {}}),
    ])
    wm = WorkspaceManager()
    project, _ = wm.load_project(project_file)

    for name in ("Mcu", "Gone"):
        command = DeleteModuleCommand(project, name)
        command.redo()
        assert name not in project.module_entries
        command.undo()
        assert name in project.module_entries

    assert "Mcu" in project.module_managers and "Mcu" in project.packages
    assert project.unloaded_variant_overrides["Gone"] == {"V1": {}}
    wm.save_project()
    saved = {m["name"]: m for m in _saved_modules(project_file)}
    assert saved["Mcu"]["definition"] == "/THA6_AS440_FuSa/Mcu"
    assert saved["Gone"]["definition"] == "/Nowhere/Gone"
