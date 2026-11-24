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
        "[!\"num:i(count(ecu:list('OsResource.AvailableCores')))\"!]",   # count() is a Double
        {"module_name": "Os"}, ecu_resources=resources)
    assert out.strip() == "4 2"


def test_resolver_excludes_inactive_variant_template_properties_and_prefers_active_variant(tmp_path):
    """EcuResourceResolver skips .properties inside inactive sibling variant dirs under templates/
    and ensures the active variant overlay directory wins over templates/<Module>/."""
    import json
    from autosar_configurator.core.packages.library import LibraryRef, find_package, scan_library
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    proj_dir = tmp_path / "Proj"
    for pkg_sub in ("CanTrcv_GenericCan", "CanTrcv_Tle9255"):
        cfg_dir = proj_dir / "modules" / pkg_sub / "config"
        cfg_dir.mkdir(parents=True, exist_ok=True)
        (cfg_dir / "CanTrcv.arxml").write_text(f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>{pkg_sub}</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF><SHORT-NAME>CanTrcv</SHORT-NAME></ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
        (proj_dir / "modules" / pkg_sub / "module.json").write_text(json.dumps({
            "schema": 1,
            "module": "CanTrcv",
            "definition": f"/MICROSAR/{pkg_sub}/CanTrcv",
            "files": ["config/CanTrcv.arxml"],
            "pre": [],
            "rec": [],
        }), encoding="utf-8")

    wm = WorkspaceManager()
    project = wm.create_project("VarRes", proj_dir / "VarRes.dpa", format_version=8)
    lib_ref = LibraryRef(path="modules", kind="package")
    project.module_libraries.append(lib_ref)
    pkgs = scan_library(lib_ref, proj_dir)
    _, tle_pkg = find_package([(0, pkgs)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    project.add_module_from_package(tle_pkg, lib_index=0, persist=True, confirm=lambda *_: True)

    tpl_dir = proj_dir / "templates"
    (tpl_dir / "CanTrcv").mkdir(parents=True)
    (tpl_dir / "CanTrcv_Tle9255").mkdir(parents=True)
    (tpl_dir / "CanTrcv_GenericCan").mkdir(parents=True)
    (tpl_dir / "CanTrcv" / "common.properties").write_text(
        "CanTrcv.Shared: FROM_GENERIC\nCanTrcv.CommonOnly: 1\n", encoding="utf-8"
    )
    (tpl_dir / "CanTrcv_Tle9255" / "active.properties").write_text(
        "CanTrcv.Shared: FROM_TLE\nCanTrcv.TleOnly: 2\n", encoding="utf-8"
    )
    (tpl_dir / "CanTrcv_GenericCan" / "inactive.properties").write_text(
        "CanTrcv.Shared: FROM_INACTIVE\nCanTrcv.InactiveOnly: 99\n", encoding="utf-8"
    )

    resources = project.load_ecu_resources()
    assert resources["CanTrcv.Shared"] == "FROM_TLE"
    assert resources["CanTrcv.CommonOnly"] == 1
    assert resources["CanTrcv.TleOnly"] == 2
    assert "CanTrcv.InactiveOnly" not in resources


def test_resolver_flat_package_layout_does_not_leak_sibling_variant_properties(tmp_path):
    """Flat Format 8 packages (modules/<Variant>/<Mod>.arxml, no config/ subdir) must stay
    bounded to pkg.root rather than stepping up to modules/ and scanning inactive siblings."""
    import json
    from autosar_configurator.core.packages.library import LibraryRef, find_package, scan_library
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    proj_dir = tmp_path / "FlatProj"
    for pkg_sub, prop_text in (
        ("CanTrcv_GenericCan", "CanTrcv.ActiveProp: GENERIC\nCanTrcv.InactiveLeak: 1\n"),
        ("CanTrcv_Tle9255", "CanTrcv.ActiveProp: TLE\n"),
    ):
        pkg_dir = proj_dir / "modules" / pkg_sub
        res_dir = pkg_dir / "resource"
        res_dir.mkdir(parents=True, exist_ok=True)
        (pkg_dir / "CanTrcv.arxml").write_text(f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>{pkg_sub}</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF><SHORT-NAME>CanTrcv</SHORT-NAME></ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
        (res_dir / f"{pkg_sub.lower()}.properties").write_text(prop_text, encoding="utf-8")
        (pkg_dir / "module.json").write_text(json.dumps({
            "schema": 1,
            "module": "CanTrcv",
            "definition": f"/MICROSAR/{pkg_sub}/CanTrcv",
            "files": ["CanTrcv.arxml"],
            "pre": [],
            "rec": [],
            "resources": "resource",
        }), encoding="utf-8")

    wm = WorkspaceManager()
    project = wm.create_project("VarFlat", proj_dir / "VarFlat.dpa", format_version=8)
    lib_ref = LibraryRef(path="modules", kind="package")
    project.module_libraries.append(lib_ref)
    pkgs = scan_library(lib_ref, proj_dir)
    _, tle_pkg = find_package([(0, pkgs)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    project.add_module_from_package(tle_pkg, lib_index=0, persist=True, confirm=lambda *_: True)

    resources = project.load_ecu_resources()
    assert resources["CanTrcv.ActiveProp"] == "TLE"
    assert "CanTrcv.InactiveLeak" not in resources


