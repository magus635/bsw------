"""Project-local chip definitions: <project dir>/chips/<chip>.yaml."""
import shutil

import pytest

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.ecu_resource_resolver import chip_for_project
from autosar_configurator.core.hardware.project_chip_store import (
    SOURCE_LIBRARY,
    SOURCE_NONE,
    SOURCE_PROJECT,
    SOURCE_PROPERTIES,
    ProjectChipStore,
    describe_differences,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject


def _library(**chips) -> ChipDatabase:
    db = ChipDatabase()
    for name, resources in chips.items():
        db.register_chip(ChipDefinition(name=name, family="THA6", ecu_resources=resources))
    return db


def _project(tmp_path, chip=None, db=None) -> WorkspaceProject:
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.selected_chip = chip
    project.chip_database = db
    return project


def test_new_project_stores_its_chip_and_reads_it_from_there(tmp_path):
    project = _project(tmp_path, "THA6412_BGA516",
                       _library(THA6412_BGA516={"OsResource": {"NumOfCores": 4}}))
    path = project.adopt_selected_chip()
    assert path == tmp_path / "chips" / "THA6412_BGA516.yaml"
    assert path.is_file()
    assert project.chip_source() == SOURCE_PROJECT
    assert project.ecu_resources == {"OsResource.NumOfCores": 4}


def test_project_copy_keeps_the_whole_chip(tmp_path):
    db = _library(C={"Os": {"A": 1}})
    db.get_chip("C").package = "BGA9"
    project = _project(tmp_path, "C", db)
    project.adopt_selected_chip()
    copy = ProjectChipStore(tmp_path).load("C")
    assert copy.package == "BGA9" and copy.family == "THA6"


def test_moved_project_gives_identical_resources_without_the_library(tmp_path):
    src = tmp_path / "a"
    src.mkdir()
    project = _project(src, "C", _library(C={"Os": {"A": 1, "L": ["x", "y"]}}))
    project.adopt_selected_chip()
    expected = dict(project.ecu_resources)

    dst = tmp_path / "b"
    shutil.copytree(src, dst)
    moved = _project(dst, "C", _library())          # an empty library: nothing to fall back to
    assert moved.chip_source() == SOURCE_PROJECT
    assert moved.load_ecu_resources() == expected


def test_library_change_does_not_affect_a_project_with_its_own_copy(tmp_path):
    db = _library(C={"Os": {"A": 1}})
    project = _project(tmp_path, "C", db)
    project.adopt_selected_chip()
    db.get_chip("C").ecu_resources["Os"]["A"] = 99
    assert project.load_ecu_resources() == {"Os.A": 1}


def test_update_from_library_replaces_the_copy_after_showing_differences(tmp_path):
    db = _library(C={"Os": {"A": 1, "Gone": 5}})
    project = _project(tmp_path, "C", db)
    project.adopt_selected_chip()
    db.get_chip("C").ecu_resources = {"Os": {"A": 2, "New": 3}}

    lines, total = project.chip_update_differences()
    assert total == 3
    assert any(line.startswith("Os.A:") and "project=1" in line and "library=2" in line
               for line in lines)
    project.update_chip_from_library()
    assert project.ecu_resources == {"Os.A": 2, "Os.New": 3}


def test_old_project_is_not_changed_until_the_user_acts(tmp_path):
    project = _project(tmp_path, "C", _library(C={"Os": {"A": 1}}))
    assert project.chip_source() == SOURCE_LIBRARY
    assert project.load_ecu_resources() == {"Os.A": 1}
    assert not (tmp_path / "chips").exists()          # loading never writes
    project.chip_changed()
    assert not (tmp_path / "chips").exists()          # nor does a chip change without chips/


def test_chip_change_copies_new_chip_when_project_already_keeps_chips(tmp_path):
    db = _library(A={"Os": {"K": "a"}}, B={"Os": {"K": "b"}})
    project = _project(tmp_path, "A", db)
    project.adopt_selected_chip()
    project.selected_chip = "B"
    assert project.chip_changed() == {"Os.K": "b"}
    assert (tmp_path / "chips" / "B.yaml").is_file()
    assert project.chip_source() == SOURCE_PROJECT


def test_adopt_builds_chip_from_resource_properties_when_library_lacks_it(tmp_path):
    res = tmp_path / "Def" / "plugins" / "Os_X" / "resource"
    res.mkdir(parents=True)
    (res / "Os_Resource_THA6206.properties").write_text(
        "OsResource.NumOfCores: 2\n", encoding="utf-8")
    (res / "Os_Resource_THA6412.properties").write_text(
        "OsResource.NumOfCores: 4\n", encoding="utf-8")
    (tmp_path / "Def" / "plugins" / "Os_X" / "build.properties").write_text(
        "bin.includes: plugin.xml\n", encoding="utf-8")
    project = _project(tmp_path, "THA6206_LFBGA292", _library())
    assert project.chip_source() == SOURCE_PROPERTIES

    project.adopt_selected_chip()
    chip = ProjectChipStore(tmp_path).load("THA6206_LFBGA292")
    assert chip.ecu_resources == {"OsResource": {"NumOfCores": 2}}   # no build.properties noise
    assert project.chip_source() == SOURCE_PROJECT


def test_adopt_errors_are_reported_not_silent(tmp_path):
    no_chip = _project(tmp_path, None, _library())
    with pytest.raises(ValueError):
        no_chip.adopt_selected_chip()
    nothing = _project(tmp_path, "UNKNOWN", _library())
    with pytest.raises(ValueError):
        nothing.adopt_selected_chip()
    unsaved = WorkspaceProject("p", None)
    unsaved.selected_chip = "C"
    with pytest.raises(ValueError):
        unsaved.adopt_selected_chip()


def test_chip_file_name_cannot_escape_the_chips_directory(tmp_path):
    store = ProjectChipStore(tmp_path)
    for bad in ("../evil", "a/b", "..", ".hidden", ""):
        with pytest.raises(ValueError):
            store.path_for(bad)
        assert store.has(bad) is False


def test_project_copy_wins_over_library_and_unreadable_copy_falls_back(tmp_path):
    db = _library(C={"Os": {"A": "library"}})
    project = _project(tmp_path, "C", db)
    (tmp_path / "chips").mkdir()
    (tmp_path / "chips" / "C.yaml").write_text("name: C\necu_resources:\n  Os:\n    A: local\n",
                                               encoding="utf-8")
    assert project.load_ecu_resources() == {"Os.A": "local"}

    (tmp_path / "chips" / "C.yaml").write_text("name: [broken", encoding="utf-8")
    assert chip_for_project(project, db)[0] == SOURCE_LIBRARY
    assert project.load_ecu_resources() == {"Os.A": "library"}


def test_no_chip_selected_has_no_source(tmp_path):
    assert chip_for_project(_project(tmp_path), _library())[0] == SOURCE_NONE


def test_store_lists_chip_names(tmp_path):
    store = ProjectChipStore(tmp_path)
    assert store.list_names() == []
    store.save(ChipDefinition(name="B"))
    store.save(ChipDefinition(name="A"))
    assert store.list_names() == ["A", "B"]


def test_other_chip_keys_include_the_projects_own_other_chips(tmp_path):
    from autosar_configurator.core.hardware.ecu_resource_resolver import other_chip_keys

    store = ProjectChipStore(tmp_path)
    store.save(ChipDefinition(name="OTHER", ecu_resources={"Port": {"OnlyOther": 1}}))
    project = _project(tmp_path, "C", _library(C={}))
    assert other_chip_keys(project)["port.onlyother"] == ["OTHER"]


def test_describe_differences_limits_lines_but_counts_all():
    a = ChipDefinition(name="C", ecu_resources={"M": {f"k{i}": 1 for i in range(20)}})
    b = ChipDefinition(name="C", ecu_resources={"M": {f"k{i}": 2 for i in range(20)}})
    lines, total = describe_differences(a, b, limit=5)
    assert len(lines) == 5 and total == 20
