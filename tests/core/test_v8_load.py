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
    # The Pre container is in Active by initialisation (baseline, D8), not only the one
    # the test created
    assert [c.short_name for c in mcu.configuration.containers] == [
        "McuPublishedInformation", "McuGeneralConfiguration"]
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


def test_v8_discover_available_chips_and_package_record(tmp_path):
    """Format 8 projects discover chips from package resource dirs and record package_record on add."""
    lib_dir = tmp_path / "lib"
    pkg_dir = lib_dir / "Res"
    (pkg_dir / "def").mkdir(parents=True)
    shutil.copy(EB_PLUGINS / "Resource_THA6_AS440" / "config" / "Resource.xdm",
                pkg_dir / "def" / "Resource.xdm")
    (pkg_dir / "resource").mkdir()
    (pkg_dir / "resource" / "Res_THA6206_LFBGA292.properties").write_text("K=1\n", encoding="utf-8")
    (pkg_dir / "resource" / "Res_THA6412_BGA516.properties").write_text("K=2\n", encoding="utf-8")
    (pkg_dir / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "Resource",
        "definition": "/THA6_AS440_FuSa/Resource",
        "files": ["def/Resource.xdm"],
        "resources": "resource",
        "origin": {"sw_version": "2.3.4"},
    }), encoding="utf-8")

    wm = WorkspaceManager()
    project = wm.create_project("P", tmp_path / "proj" / "P.dpa", format_version=8)
    project.module_libraries.append(LibraryRef(path="../lib", kind="package"))

    chips = project.discover_available_chips()
    assert chips == ["THA6206_LFBGA292", "THA6412_BGA516"]

    [pkg] = scan_library(project.module_libraries[0], tmp_path / "proj")
    project.add_module_from_package(pkg, 0)
    record = project.module_entries["Resource"].package_record
    assert record["sw_version"] == "2.3.4"
    assert "def/Resource.xdm" in record["files"]
    assert record["files"]["def/Resource.xdm"].startswith("sha256:")


def test_ensure_package_for_path_registers_library_on_new_v8_project(tmp_path):
    """Adding a module via file selection on a new v8 project auto-registers its package library."""
    from autosar_configurator.core.workspace_manager import ensure_package_for_path

    project_file = tmp_path / "proj" / "P.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("P", project_file, format_version=8)
    project.selected_chip = CHIP
    assert project.module_libraries == []

    hit = ensure_package_for_path(project, EB_PLUGINS / "Mcu_THA6_AS440" / "config" / "Mcu.xdm")
    assert hit is not None
    lib_index, pkg = hit
    assert lib_index == 0
    assert pkg.manifest.module == "Mcu"
    assert len(project.module_libraries) == 1
    assert project.module_libraries[0].kind == "eb-plugins"

    manager = project.add_module_from_package(pkg, lib_index)
    assert any(c.short_name == "McuPublishedInformation" for c in manager.configuration.containers)
    wm.save_project()

    reloaded, failed = WorkspaceManager().load_project(project_file)
    assert failed == []
    assert "Mcu" in reloaded.module_managers
    assert any(
        c.short_name == "McuPublishedInformation"
        for c in reloaded.module_managers["Mcu"].configuration.containers
    )


def test_v8_detects_package_record_drift_and_prompts_without_baseline_value_change(tmp_path):
    """R4: changing package file or sw_version without changing baseline values records drift and prompts."""
    lib_dir = tmp_path / "lib"
    pkg_dir = lib_dir / "Res"
    (pkg_dir / "def").mkdir(parents=True)
    xdm_path = pkg_dir / "def" / "Resource.xdm"
    shutil.copy(EB_PLUGINS / "Resource_THA6_AS440" / "config" / "Resource.xdm", xdm_path)
    manifest_path = pkg_dir / "module.json"
    manifest_data = {
        "schema": 1,
        "module": "Resource",
        "definition": "/THA6_AS440_FuSa/Resource",
        "files": ["def/Resource.xdm"],
        "origin": {"sw_version": "1.0.0"},
    }
    manifest_path.write_text(json.dumps(manifest_data), encoding="utf-8")

    project_file = tmp_path / "proj" / "P.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("P", project_file, format_version=8)
    project.module_libraries.append(LibraryRef(path="../lib", kind="package"))
    [pkg] = scan_library(project.module_libraries[0], tmp_path / "proj")
    project.add_module_from_package(pkg, 0)
    wm.save_project()

    saved_before = json.loads(project_file.read_text(encoding="utf-8"))
    old_record = saved_before["modules"][0]["package_record"]
    assert old_record["sw_version"] == "1.0.0"

    # Bump version and append an XML comment to the definition without changing baseline values
    manifest_data["origin"]["sw_version"] = "1.0.1"
    manifest_path.write_text(json.dumps(manifest_data), encoding="utf-8")
    xdm_path.write_text(xdm_path.read_text(encoding="utf-8") + "\n<!-- updated -->\n", encoding="utf-8")

    # 1. Headless (confirm_package_change=None): opens with current content, records drift, keeps old record
    reloaded_none, failed_none = WorkspaceManager().load_project(project_file)
    assert failed_none == []
    assert "Resource" in reloaded_none.package_drifts
    drift = reloaded_none.package_drifts["Resource"]
    assert drift.old_version == "1.0.0"
    assert drift.new_version == "1.0.1"
    assert "def/Resource.xdm" in drift.changed_files
    assert reloaded_none.module_entries["Resource"].package_record == old_record

    # 2. User rejects update -> keeps old package_record, next open still sees drift
    seen = []
    reloaded_reject, failed_rej = WorkspaceManager().load_project(
        project_file,
        confirm_package_change=lambda d: seen.append(d) or False,
    )
    assert failed_rej == []
    assert len(seen) == 1
    assert "Resource" in seen[0]
    assert reloaded_reject.module_entries["Resource"].package_record == old_record
    assert "Resource" in reloaded_reject.package_drifts

    # 3. User accepts update -> updates package_record, marks modified, save clears drift on subsequent load
    wm2 = WorkspaceManager()
    reloaded_accept, failed_acc = wm2.load_project(
        project_file,
        confirm_package_change=lambda d: True,
    )
    assert failed_acc == []
    assert reloaded_accept.package_drifts == {}
    assert reloaded_accept.is_modified is True
    assert reloaded_accept.module_entries["Resource"].package_record["sw_version"] == "1.0.1"
    wm2.save_project()

    called_after_save = []
    reloaded_clean, failed_clean = WorkspaceManager().load_project(
        project_file,
        confirm_package_change=lambda d: called_after_save.append(d) or True,
    )
    assert failed_clean == []
    assert called_after_save == []
    assert reloaded_clean.package_drifts == {}


def test_add_custom_module_from_file_packages_into_modules_custom(tmp_path):
    """Standalone custom definition files are packaged under modules/custom/ with unified config/."""
    from autosar_configurator.core.baseline.origin import Origin
    from autosar_configurator.core.packages.manifest import load_manifest

    src_dir = tmp_path / "standalone"
    src_dir.mkdir()
    def_arxml = src_dir / "MyMod.arxml"
    def_arxml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Custom</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>MyMod</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>General</SHORT-NAME>
          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <PARAMETERS>
            <ECUC-INTEGER-PARAM-DEF><SHORT-NAME>TimeoutMs</SHORT-NAME></ECUC-INTEGER-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    pre_arxml = src_dir / "MyMod_Pre.arxml"
    pre_arxml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Custom</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>MyMod_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Custom/MyMod</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>General</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Custom/MyMod/General</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/Custom/MyMod/General/TimeoutMs</DEFINITION-REF>
          <VALUE>250</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    proj_dir = tmp_path / "Proj"
    project_file = proj_dir / "Proj.dpa"
    wm = WorkspaceManager()
    project = wm.create_project("Proj", project_file, format_version=8)
    wm.save_project()

    mgr = project.add_custom_module_from_file(def_arxml, pre_files=[pre_arxml])
    assert mgr.module_def.short_name == "MyMod"
    assert mgr.configuration.containers[0].parameter_values["TimeoutMs"].value == 250
    assert mgr.value_origin(mgr.configuration.containers[0], "TimeoutMs") is Origin.PRE

    pkg_dir = proj_dir / "modules" / "custom" / "MyMod"
    assert (pkg_dir / "config" / "MyMod.arxml").is_file()
    assert (pkg_dir / "config" / "MyMod_Pre.arxml").is_file()
    assert not (pkg_dir / "def").exists()
    assert not (pkg_dir / "sources.json").exists()

    manifest = load_manifest(pkg_dir)
    assert manifest.definition == "/Custom/MyMod"
    assert [f.path for f in manifest.files] == ["config/MyMod.arxml", "config/MyMod_Pre.arxml"]
    assert manifest.pre == ["/Custom/MyMod_Pre"]
    assert manifest.origin["source"] == "custom"
    assert project.module_provenance["MyMod"]["origin"] == "custom"
    assert [lib.to_dict() for lib in project.module_libraries] == [
        {"path": "modules/custom", "kind": "package", "exclude": []}
    ]

    wm.save_project()
    assert (proj_dir / "config" / "MyMod.arxml").is_file()

    # Merging an EB copy tree into the same project keeps modules/custom/ untouched
    eb_root = tmp_path / "EbSrc"
    eb_plugin = eb_root / "Def" / "plugins" / "Dio_TS"
    (eb_plugin / "config").mkdir(parents=True)
    (eb_plugin / "plugin.xml").write_text(
        '<?xml version="1.0"?><plugin>'
        '<extension point="dreisoft.tresos.launcher2.plugin.module">'
        '<module id="Dio_TS" label="Dio" swVersionMajor="1" swVersionMinor="0" swVersionPatch="0"/>'
        '</extension>'
        '<extension point="dreisoft.tresos.launcher2.plugin.configuration">'
        '<configuration moduleId="Dio_TS">'
        '<schema><resource type="xdm" value="config/Dio.xdm"/></schema>'
        '<data><schemaNode path="ASPath:/Vendor/Dio"/></data>'
        '</configuration></extension></plugin>',
        encoding="utf-8",
    )
    (eb_plugin / "config" / "Dio.xdm").write_text("""<?xml version="1.0"?>
<datamodel version="7.0"
           xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES"><d:ctr name="Vendor" type="AR-PACKAGE"><d:lst type="ELEMENTS">
      <d:chc name="Dio" type="AR-ELEMENT" value="MODULE-DEF"><v:ctr type="MODULE-DEF"/></d:chc>
    </d:lst></d:ctr></d:lst>
  </d:ctr>
</datamodel>""", encoding="utf-8")
    (eb_root / "Config" / "C1" / "output").mkdir(parents=True)
    (eb_root / "Config" / "C1" / "output" / "Dio.epc").write_text("""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Dio</SHORT-NAME><ELEMENTS>
  <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Dio</SHORT-NAME>
    <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Dio</DEFINITION-REF>
  </ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""", encoding="utf-8")

    wm2 = WorkspaceManager()
    reloaded, failed = wm2.load_project(project_file)
    assert failed == []
    assert "MyMod" in reloaded.module_managers
    assert reloaded.module_defs["MyMod"] == pkg_dir / "config" / "MyMod.arxml"

    _, eb_loaded, eb_failed = wm2.import_eb_project(eb_root, mode="copy", into_project=reloaded)
    assert eb_failed == [] and eb_loaded == ["Dio"]
    assert (pkg_dir / "module.json").is_file()
    assert (proj_dir / "modules" / "eb" / "Dio_TS" / "plugin.xml").is_file()
    assert [lib.path for lib in reloaded.module_libraries] == ["modules/custom", "modules/eb"]


def test_add_custom_module_from_file_multiple_rec_and_error_guards(tmp_path):
    """Multiple Rec files get unique config/ filenames and Pre/Rec/path guards fail explicitly."""
    from autosar_configurator.core.baseline.origin import Origin
    from autosar_configurator.core.packages.manifest import load_manifest

    src_dir = tmp_path / "custom_src"
    src_dir.mkdir()
    def_arxml = src_dir / "RecMod.arxml"
    def_arxml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Custom</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>RecMod</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>GeneralA</SHORT-NAME>
          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <PARAMETERS>
            <ECUC-STRING-PARAM-DEF><SHORT-NAME>Mode</SHORT-NAME></ECUC-STRING-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>GeneralB</SHORT-NAME>
          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <PARAMETERS>
            <ECUC-INTEGER-PARAM-DEF><SHORT-NAME>Limit</SHORT-NAME></ECUC-INTEGER-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    rec1 = src_dir / "rec1.arxml"
    rec1.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Custom</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>RecMod_Rec1</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Custom/RecMod</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>GeneralA</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Custom/RecMod/GeneralA</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Custom/RecMod/GeneralA/Mode</DEFINITION-REF>
          <VALUE>FAST</VALUE>
        </ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    rec2 = src_dir / "rec2.arxml"
    rec2.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Custom</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>RecMod_Rec2</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Custom/RecMod</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>GeneralB</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Custom/RecMod/GeneralB</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/Custom/RecMod/GeneralB/Limit</DEFINITION-REF>
          <VALUE>99</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    wm = WorkspaceManager()
    proj_dir = tmp_path / "MultiRecProj"
    project = wm.create_project("MultiRecProj", proj_dir / "MultiRecProj.dpa", format_version=8)
    wm.save_project()

    mgr = project.add_custom_module_from_file(def_arxml, rec_files=[rec1, rec2])
    by_name = {c.short_name: c for c in mgr.configuration.containers}
    assert by_name["GeneralA"].parameter_values["Mode"].value == "FAST"
    assert by_name["GeneralB"].parameter_values["Limit"].value == 99
    assert mgr.value_origin(by_name["GeneralA"], "Mode") is Origin.REC
    assert mgr.value_origin(by_name["GeneralB"], "Limit") is Origin.REC

    pkg_dir = proj_dir / "modules" / "custom" / "RecMod"
    assert (pkg_dir / "config" / "RecMod.arxml").is_file()
    assert (pkg_dir / "config" / "RecMod_Rec.arxml").is_file()
    assert (pkg_dir / "config" / "RecMod_Rec_2.arxml").is_file()
    manifest = load_manifest(pkg_dir)
    assert [f.path for f in manifest.files] == [
        "config/RecMod.arxml",
        "config/RecMod_Rec.arxml",
        "config/RecMod_Rec_2.arxml",
    ]
    assert manifest.rec == ["/Custom/RecMod_Rec1", "/Custom/RecMod_Rec2"]

    # Validation guards
    v7 = WorkspaceManager().create_project("V7", tmp_path / "V7" / "V7.dpa", format_version=7)
    with pytest.raises(ValueError, match="Format 8"):
        v7.add_custom_module_from_file(def_arxml)

    unsaved = WorkspaceManager().create_project("Unsaved", None, format_version=8)
    with pytest.raises(ValueError, match="Format 8"):
        unsaved.add_custom_module_from_file(def_arxml)

    with pytest.raises(FileNotFoundError):
        project.add_custom_module_from_file(src_dir / "Missing.arxml")

    with pytest.raises(FileNotFoundError):
        project.add_custom_module_from_file(def_arxml, pre_files=[src_dir / "Missing_Pre.arxml"])


def test_add_custom_module_from_file_readd_and_inplace_source(tmp_path):
    """Re-adding an excluded/removed custom module from in-place config/ paths un-excludes without SameFileError."""
    src_dir = tmp_path / "src"
    src_dir.mkdir()
    def_arxml = src_dir / "ReAddMod.arxml"
    def_arxml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Custom</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>ReAddMod</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>General</SHORT-NAME>
          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <PARAMETERS>
            <ECUC-INTEGER-PARAM-DEF><SHORT-NAME>TimeoutMs</SHORT-NAME></ECUC-INTEGER-PARAM-DEF>
            <ECUC-STRING-PARAM-DEF><SHORT-NAME>UserNote</SHORT-NAME></ECUC-STRING-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    pre_arxml = src_dir / "ReAddMod_Pre.arxml"
    pre_arxml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Custom</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>ReAddMod_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Custom/ReAddMod</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>General</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Custom/ReAddMod/General</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/Custom/ReAddMod/General/TimeoutMs</DEFINITION-REF>
          <VALUE>250</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    wm = WorkspaceManager()
    proj_dir = tmp_path / "ReAddProj"
    dpa_path = proj_dir / "ReAddProj.dpa"
    project = wm.create_project("ReAddProj", dpa_path, format_version=8)
    wm.save_project()

    mgr = project.add_custom_module_from_file(def_arxml, pre_files=[pre_arxml])
    mgr.set_parameter_value(mgr.configuration.containers[0], "UserNote", "keep_me")
    wm.save_project()

    # Remove module and simulate its package being excluded in modules/custom
    project.remove_module("ReAddMod", archive=False)
    project.module_libraries[0].exclude.append("ReAddMod")
    wm.save_project()

    # Re-add directly from the in-place package paths under modules/custom/ReAddMod/config/
    pkg_dir = proj_dir / "modules" / "custom" / "ReAddMod"
    readded_mgr = project.add_custom_module_from_file(
        pkg_dir / "config" / "ReAddMod.arxml",
        pre_files=[pkg_dir / "config" / "ReAddMod_Pre.arxml"],
        confirm=lambda *_: True,
    )
    assert len(project.module_libraries) == 1
    assert "ReAddMod" not in project.module_libraries[0].exclude
    assert readded_mgr.configuration.containers[0].parameter_values["TimeoutMs"].value == 250
    assert readded_mgr.configuration.containers[0].parameter_values["UserNote"].value == "keep_me"

    wm.save_project()
    reloaded, failed = WorkspaceManager().load_project(dpa_path)
    assert failed == []
    assert reloaded.module_managers["ReAddMod"].configuration.containers[0].parameter_values["UserNote"].value == "keep_me"


def test_add_custom_module_multiple_variants_do_not_overwrite_each_other(tmp_path):
    """Adding two custom definitions with the same SHORT-NAME but different AR package paths
    must place them in separate directories under modules/custom/ so both remain switchable."""
    src_dir = tmp_path / "src"
    src_dir.mkdir()
    def_a = src_dir / "CustomMod_VendorA.arxml"
    def_a.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>VendorA</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>CustomMod</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>General</SHORT-NAME>
          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <PARAMETERS><ECUC-INTEGER-PARAM-DEF><SHORT-NAME>ParamA</SHORT-NAME></ECUC-INTEGER-PARAM-DEF></PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    def_b = src_dir / "CustomMod_VendorB.arxml"
    def_b.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>VendorB</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>CustomMod</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>General</SHORT-NAME>
          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <PARAMETERS><ECUC-INTEGER-PARAM-DEF><SHORT-NAME>ParamB</SHORT-NAME></ECUC-INTEGER-PARAM-DEF></PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    wm = WorkspaceManager()
    proj_dir = tmp_path / "CustomVariants"
    project = wm.create_project("CustomVariants", proj_dir / "CustomVariants.dpa", format_version=8)
    wm.save_project()

    project.add_custom_module_from_file(def_a)
    wm.save_project()
    project.remove_module("CustomMod")

    project.add_custom_module_from_file(def_b)
    wm.save_project()

    variants = project.list_module_variant_packages("CustomMod")
    defs = {pkg.manifest.definition for _idx, pkg in variants}
    assert defs == {"/VendorA/CustomMod", "/VendorB/CustomMod"}
    idx_a, pkg_a = next((i, p) for i, p in variants if p.manifest.definition == "/VendorA/CustomMod")
    sw = project.switch_module_variant("CustomMod", pkg_a, target_lib_index=idx_a, preview_only=False, confirm=lambda *_: True)
    assert sw.applied is True
    assert project.module_entries["CustomMod"].definition == "/VendorA/CustomMod"

