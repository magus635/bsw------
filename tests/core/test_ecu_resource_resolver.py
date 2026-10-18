"""EcuResourceResolver: one source of ecu:get()/ecu:list() data for every project."""
import logging
from pathlib import Path
from types import SimpleNamespace

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.ecu_resource_resolver import (
    EcuResourceResolver,
    scan_properties,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
from autosar_configurator.generator.generator import CodeGenerator

REPO = Path(__file__).resolve().parent.parent.parent
IMPORT_PROJECT = REPO / "test_import_project"


def _db(**chips) -> ChipDatabase:
    db = ChipDatabase()
    for name, resources in chips.items():
        db.register_chip(ChipDefinition(name=name, ecu_resources=resources))
    return db


def _project(tmp_path: Path, chip=None, db=None) -> WorkspaceProject:
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.selected_chip = chip
    project.chip_database = db
    return project


def _write_resource_file(project_dir: Path, text: str, name="Os_Resource_THA6412.properties"):
    res = project_dir / "Def" / "plugins" / "Os_X" / "resource"
    res.mkdir(parents=True, exist_ok=True)
    (res / name).write_text(text, encoding="utf-8")


def test_new_project_gets_chip_resources_without_any_eb_import(tmp_path):
    db = _db(THA6412_BGA516={"OsResource": {"NumOfCores": 4}})
    project = _project(tmp_path, "THA6412_BGA516", db)
    resources = project.load_ecu_resources()
    assert resources == {"OsResource.NumOfCores": 4}
    assert project.ecu_resources is resources


def test_no_chip_and_no_files_gives_empty_resources(tmp_path):
    assert _project(tmp_path).load_ecu_resources() == {}


def test_chip_yaml_overrides_properties_and_logs(tmp_path, caplog):
    _write_resource_file(tmp_path, "OsResource.NumOfCores: 2\nOsResource.Other: x\n")
    db = _db(THA6412_BGA516={"OsResource": {"NumOfCores": 4}})
    project = _project(tmp_path, "THA6412_BGA516", db)
    with caplog.at_level(logging.INFO):
        resources = project.load_ecu_resources()
    assert resources == {"OsResource.NumOfCores": 4, "OsResource.Other": "x"}
    assert any("OsResource.NumOfCores" in r.message for r in caplog.records)


def test_chip_change_recomputes_and_drops_old_keys(tmp_path):
    db = _db(CHIP_A={"Os": {"OnlyA": 1, "Shared": "a"}}, CHIP_B={"Os": {"Shared": "b"}})
    project = _project(tmp_path, "CHIP_A", db)
    assert project.load_ecu_resources() == {"Os.OnlyA": 1, "Os.Shared": "a"}
    project.selected_chip = "CHIP_B"
    assert project.load_ecu_resources() == {"Os.Shared": "b"}


def test_unknown_chip_applies_nothing(tmp_path):
    project = _project(tmp_path, "NOT_THERE", _db())
    assert project.load_ecu_resources() == {}


def test_resource_properties_must_match_selected_chip(tmp_path):
    _write_resource_file(tmp_path, "OsResource.NumOfCores: 4\n", "Os_Resource_THA6412.properties")
    _write_resource_file(tmp_path, "OsResource.NumOfCores: 2\n", "Os_Resource_THA6206.properties")
    project = _project(tmp_path, "THA6412_BGA516", _db())
    assert project.load_ecu_resources() == {"OsResource.NumOfCores": 4}


def test_default_database_is_used_when_project_has_none(tmp_path):
    project = _project(tmp_path, "THA6412_BGA516", None)
    resources = project.load_ecu_resources()
    assert resources.get("Resource.NumOfCores") == 4
    assert resources.get("OsResource.NumOfCores") == 4


def test_imported_eb_project_resources_equal_generator_scan():
    """Golden check: the resolver finds exactly what the generator's own scan finds."""
    project = WorkspaceProject("import", IMPORT_PROJECT / "import.dpa")
    project.selected_chip = "THA6412_BGA516"
    resolved = EcuResourceResolver(_db()).resolve(project)

    gen = CodeGenerator.__new__(CodeGenerator)
    gen.project_template_dir = IMPORT_PROJECT / "templates"
    gen.selected_chip = "THA6412_BGA516"
    legacy = gen._load_ecu_resources()

    assert resolved
    assert resolved == legacy
    assert resolved == scan_properties(project)


def test_generator_does_not_rescan_when_resources_are_passed(monkeypatch):
    called = []
    monkeypatch.setattr(CodeGenerator, "_load_ecu_resources",
                        lambda self: called.append(1) or {"scanned": 1})
    gen = CodeGenerator(None, SimpleNamespace(short_name="Os"),
                        ecu_resources={"OsResource.NumOfCores": 4})
    assert gen.ecu_resources == {"OsResource.NumOfCores": 4}
    assert not called


def test_template_renders_chip_value_without_def_directory(tmp_path):
    db = _db(THA6412_BGA516={"OsResource": {"NumOfCores": 4,
                                            "AvailableCores": ["CORE0", "CORE1"]}})
    project = _project(tmp_path, "THA6412_BGA516", db)
    assert not (tmp_path / "Def").exists()
    resources = project.load_ecu_resources()

    out = EBTemplateEngine(strict=False).render(
        "[!\"ecu:get('OsResource.NumOfCores')\"!] "
        "[!\"count(ecu:list('OsResource.AvailableCores'))\"!]",
        {"module_name": "Os"}, ecu_resources=resources)
    assert out.strip() == "4 2"
