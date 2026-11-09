"""Tests for .dpa format 8 (directories, libraries, module entries)."""
import json
import pytest
from pathlib import Path

from autosar_configurator.core.workspace_manager import WorkspaceManager, WorkspaceProject, ModuleEntry
from autosar_configurator.core.project_paths import ProjectDirectories
from autosar_configurator.core.packages.library import LibraryRef


@pytest.fixture
def manager():
    """Create a WorkspaceManager for testing."""
    return WorkspaceManager()


def test_v8_roundtrip_fields(tmp_path, manager):
    """Test that format 8 directories, libraries, and module entries round-trip in JSON."""
    project_file = tmp_path / "test_v8.dpa"

    # Create format 8 project
    project = manager.create_project("TestV8", project_file, format_version=8)
    assert project.format_version == 8
    assert project.directories == ProjectDirectories.default_v8()

    # Add a library
    lib = LibraryRef(path="modules", kind="package", exclude=[])
    project.module_libraries.append(lib)

    # Add a module entry (without actual module manager, just the entry)
    entry = ModuleEntry(
        name="TestMcu",
        definition="/AUTOSAR/EcucDefs/Mcu",
        library=0,
        config_path="config/Mcu.arxml",
        pre_unlocked=["EnablePto"],
        package_record={"version": "1.0"},
        base_hash="abc123",
    )
    project.module_entries["TestMcu"] = entry

    # Save project
    manager.save_project()
    assert project_file.exists()

    # Verify the JSON has the fields (format 8 module loading deferred to Task 6)
    with open(project_file, 'r') as f:
        saved_data = json.load(f)

    assert saved_data["format_version"] == 8
    assert "directories" in saved_data
    assert "module_libraries" in saved_data
    assert "modules" in saved_data

    # Check directories
    dirs_data = saved_data["directories"]
    assert dirs_data["config"] == "config"
    assert dirs_data["base"] == "config/base"
    assert dirs_data["templates"] == "templates"

    # Check module_libraries
    assert len(saved_data["module_libraries"]) == 1
    lib_data = saved_data["module_libraries"][0]
    assert lib_data["path"] == "modules"
    assert lib_data["kind"] == "package"

    # Check modules (should have our entry)
    assert len(saved_data["modules"]) == 1
    mod_data = saved_data["modules"][0]
    assert mod_data["name"] == "TestMcu"
    assert mod_data["definition"] == "/AUTOSAR/EcucDefs/Mcu"
    assert mod_data["library"] == 0
    assert mod_data["config_path"] == "config/Mcu.arxml"
    assert mod_data["pre_unlocked"] == ["EnablePto"]
    assert mod_data["package_record"] == {"version": "1.0"}
    assert mod_data["base_hash"] == "abc123"

    # Load project back
    loaded_project, failed = manager.load_project(project_file)

    # Verify format and fields loaded from JSON
    assert loaded_project.format_version == 8
    assert loaded_project.directories == ProjectDirectories.default_v8()

    # Verify libraries loaded
    assert len(loaded_project.module_libraries) == 1
    loaded_lib = loaded_project.module_libraries[0]
    assert loaded_lib.path == "modules"
    assert loaded_lib.kind == "package"

    # Verify module_entries loaded (format 8 module loading deferred to Task 6)
    assert "TestMcu" in loaded_project.module_entries
    loaded_entry = loaded_project.module_entries["TestMcu"]
    assert loaded_entry.name == "TestMcu"
    assert loaded_entry.definition == "/AUTOSAR/EcucDefs/Mcu"
    assert loaded_entry.library == 0
    assert loaded_entry.config_path == "config/Mcu.arxml"
    assert loaded_entry.pre_unlocked == ["EnablePto"]
    assert loaded_entry.package_record == {"version": "1.0"}
    assert loaded_entry.base_hash == "abc123"


def test_v7_stays_v7_on_save(tmp_path, manager):
    """Test that format 7 projects stay format 7 after save (no module loading)."""
    # Create a v7 project file without modules (so we don't need def files)
    project_file = tmp_path / "test_v7.dpa"
    v7_data = {
        "format_version": 7,
        "name": "TestV7",
        "created": "2025-01-01T00:00:00",
        "last_modified": "2025-01-01T00:00:00",
        "project_type": "Vector DaVinci",
        "author": "",
        "description": "",
        "version": "1.0.0",
        "def_search_paths": [],
        "variants": ["Default"],
        "active_variant": "Default",
        "dependency_rules": [],
        "available_chips": [],
        "selected_chip": None,
        "chip_data": None,
        "eb_source_root": None,
        "import_mode": "copy",
        "chip_scan_dirs": [],
        "chip_scan_keywords": [],
        "memmap_source_dirs": [],
        "memmap_header_dirs": [],
        "memmap_linker_file": None,
        "modules": [],
    }

    with open(project_file, 'w') as f:
        json.dump(v7_data, f)

    # Load the v7 project
    loaded_project, failed = manager.load_project(project_file)
    assert loaded_project.format_version == 7

    # Save it back
    manager.save_project()

    # Verify format_version is still 7
    with open(project_file, 'r') as f:
        saved_data = json.load(f)

    assert saved_data["format_version"] == 7
    assert "directories" not in saved_data
    assert "module_libraries" not in saved_data


def test_v8_paths_non_ascii_and_external_roundtrip(tmp_path, manager):
    """Test that format 8 paths with non-ASCII chars and external libraries round-trip correctly."""
    # Create project directory with non-ASCII name
    project_dir = tmp_path / "中文 目录"
    project_dir.mkdir()
    project_file = project_dir / "test.dpa"

    # Create project
    project = manager.create_project("TestPath", project_file, format_version=8)

    # Add internal library (inside project)
    internal_lib = LibraryRef(path="modules", kind="package", exclude=[])
    project.module_libraries.append(internal_lib)

    # Add external library (outside project)
    external_lib_dir = tmp_path / "external libs"
    external_lib_dir.mkdir(parents=True, exist_ok=True)
    external_lib = LibraryRef(path=str(external_lib_dir).replace("\\", "/"), kind="eb-plugins", exclude=[])
    project.module_libraries.append(external_lib)

    # Save project
    manager.save_project()

    # Check the JSON has correct paths
    with open(project_file, 'r') as f:
        saved_data = json.load(f)

    libs = saved_data["module_libraries"]
    assert len(libs) == 2

    # Internal library should be relative
    assert libs[0]["path"] == "modules"
    assert "/" in libs[0]["path"] or len(libs[0]["path"].split("/")) == 1
    assert "\\" not in libs[0]["path"]

    # External library should be absolute (and use forward slashes)
    assert "\\" not in libs[1]["path"]
    assert "/" in libs[1]["path"] or external_lib_dir.name in libs[1]["path"]

    # Load project back
    loaded_project, failed = manager.load_project(project_file)

    # Verify both libraries loaded
    assert len(loaded_project.module_libraries) == 2

    # Verify paths resolve correctly
    internal_resolved = project_dir / loaded_project.module_libraries[0].path
    assert internal_resolved == project_dir / "modules"

    external_path_str = loaded_project.module_libraries[1].path
    if Path(external_path_str).is_absolute():
        external_resolved = Path(external_path_str)
    else:
        external_resolved = project_dir / external_path_str
    assert external_resolved == external_lib_dir


def test_v8_create_has_default_directories():
    """Test that creating a format 8 project sets default directories."""
    manager = WorkspaceManager()
    project = manager.create_project("TestDefaults", Path("test.dpa"), format_version=8)

    assert project.directories is not None
    assert project.directories.config == "config"
    assert project.directories.base == "config/base"
    assert project.directories.templates == "templates"
    assert project.directories.gen == "gen"
    assert project.directories.gen_layout == "flat"
    assert project.directories.chips == "chips"
    assert project.directories.integration == "integration"
    assert project.directories.system == "system"
    assert project.directories.history == ".history"
    assert project.directories.modules == "modules"


def test_module_entry_to_from_dict():
    """Test ModuleEntry serialization."""
    entry = ModuleEntry(
        name="Adc",
        definition="/AUTOSAR/EcucDefs/Adc",
        library=1,
        config_path="config/Adc.arxml",
        pre_unlocked=["Group1"],
        package_record={"checksum": "xyz"},
        base_hash="base_hash_value",
    )

    # Serialize
    d = entry.to_dict()
    assert d["name"] == "Adc"
    assert d["definition"] == "/AUTOSAR/EcucDefs/Adc"
    assert d["library"] == 1
    assert d["config_path"] == "config/Adc.arxml"
    assert d["pre_unlocked"] == ["Group1"]
    assert d["package_record"] == {"checksum": "xyz"}
    assert d["base_hash"] == "base_hash_value"

    # Deserialize
    restored = ModuleEntry.from_dict(d)
    assert restored == entry


def test_library_ref_to_from_dict():
    """Test LibraryRef serialization."""
    lib = LibraryRef(path="libs/packages", kind="package", exclude=["TestModule"])

    # Serialize
    d = lib.to_dict()
    assert d["path"] == "libs/packages"
    assert d["kind"] == "package"
    assert d["exclude"] == ["TestModule"]

    # Deserialize
    restored = LibraryRef.from_dict(d)
    assert restored == lib
