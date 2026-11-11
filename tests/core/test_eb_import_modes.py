"""
Tests for EB import modes (copy/link) and module provenance.

Since task 13 (W9) the import writes a format 8 project: the plugins directory is an
``eb-plugins`` module library (link mode) or is copied into ``modules/`` (copy mode); no
``Def/plugins`` directory, no symlink, no template copy.  Format <= 7 projects written by
the earlier import still open and save as format 7.
(openspec changes: add-eb-import-modes, add-integration-module-packages)
"""
import json
import os
import shutil
from pathlib import Path

import pytest

from autosar_configurator.core.workspace_manager import WorkspaceManager

REPO_ROOT = Path(__file__).resolve().parents[2]
DIO_DEF_SAMPLE = REPO_ROOT / "Dio_Definition_Test.arxml"

DIO_EPC = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Dio</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Dio</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Dio</DEFINITION-REF>
          <IMPLEMENTATION-CONFIG-VARIANT>VARIANT-PRE-COMPILE</IMPLEMENTATION-CONFIG-VARIANT>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DioConfig</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_AS440_FuSa/Dio/DioConfig</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""

DIO_PLUGIN_XML = """<?xml version="1.0" encoding="UTF-8"?>
<plugin>
  <extension point="dreisoft.tresos.launcher2.plugin.module" id="Dio_TS_ModuleID">
    <module id="Dio_TS" label="Dio" swVersionMajor="1" swVersionMinor="0" swVersionPatch="0"/>
  </extension>
  <extension point="dreisoft.tresos.launcher2.plugin.configuration" id="Dio_TS_ConfigurationID">
    <configuration moduleId="Dio_TS">
      <schema>
        <resource type="xdm" value="config/Dio.arxml"/>
      </schema>
      <data>
        <schemaNode path="ASPath:/THA6_AS440_FuSa/Dio"/>
      </data>
    </configuration>
  </extension>
</plugin>
"""


def write_dio_plugin(plugin: Path) -> Path:
    """An EB plugin directory for Dio: plugin.xml, its definition under config/, an
    autosar/ exchange copy (never loaded) and a generate_PB template."""
    (plugin / "config").mkdir(parents=True)
    (plugin / "plugin.xml").write_text(DIO_PLUGIN_XML, encoding="utf-8")
    shutil.copy(DIO_DEF_SAMPLE, plugin / "config" / "Dio.arxml")
    (plugin / "autosar").mkdir()
    shutil.copy(DIO_DEF_SAMPLE, plugin / "autosar" / "Dio_THA6206_LFBGA292.arxml")
    (plugin / "generate_PB" / "Dio").mkdir(parents=True)
    (plugin / "generate_PB" / "Dio" / "Dio_Cfg.h.tpl").write_text("/* tpl */", encoding="utf-8")
    return plugin


def write_v7_imported_project(proj_dir: Path, source_epc: str = "Config/THA6206/output/Dio.epc") -> Path:
    """A project as the format 7 import wrote it (copy mode): plugins copied into
    ``Def/plugins``, values in ``ConfigValue/``, ``def_path`` per module. Returns the .dpa."""
    plugin = proj_dir / "Def" / "plugins" / "Dio_TS_T40D11M7I0R0"
    (plugin / "autosar").mkdir(parents=True)
    shutil.copy(DIO_DEF_SAMPLE, plugin / "autosar" / "Dio_THA6206_LFBGA292.arxml")
    (proj_dir / "ConfigValue").mkdir()
    (proj_dir / "ConfigValue" / "Dio_Config.arxml").write_text(DIO_EPC, encoding="utf-8")
    dpa = proj_dir / f"{proj_dir.name}.dpa"
    dpa.write_text(json.dumps({
        "format_version": 7,
        "project_type": "EB Tresos",
        "name": proj_dir.name,
        "variants": ["Default"],
        "active_variant": "Default",
        "eb_source_root": (proj_dir.parent / "EbSourceGone").as_posix(),
        "import_mode": "copy",
        "modules": [{
            "name": "Dio",
            "def_path": "Def/plugins/Dio_TS_T40D11M7I0R0/autosar/Dio_THA6206_LFBGA292.arxml",
            "config_path": "ConfigValue/Dio_Config.arxml",
            "variant_overrides": {},
            "origin": "eb-import",
            "source_epc": source_epc,
            "imported_at": "2026-10-01T10:00:00",
        }],
    }), encoding="utf-8")
    return dpa


@pytest.fixture
def eb_source_tree(tmp_path):
    """Minimal EB Tresos project tree with one Dio plugin + EPC output"""
    src_root = tmp_path / "EbSource"
    write_dio_plugin(src_root / "Define" / "EbPlugins" / "eclipse" / "Dio_TS_T40D11M7I0R0")

    output = src_root / "Config" / "THA6206" / "output"
    output.mkdir(parents=True)
    (output / "Dio.epc").write_text(DIO_EPC, encoding="utf-8")
    return src_root


def _import(eb_source_tree, tmp_path, mode):
    manager = WorkspaceManager()
    target = tmp_path / f"Imported_{mode}"
    target.mkdir()
    project, loaded, failed = manager.import_eb_project(
        eb_source_tree, chip_name=None, target_dir=target, mode=mode)
    assert "Dio" in loaded, f"failed: {failed}"
    return manager, project, target


def _has_symlink(root: Path) -> bool:
    return any((Path(d) / n).is_symlink()
               for d, dirs, files in os.walk(root) for n in dirs + files)


class TestCopyMode:
    def test_copy_mode_is_self_contained(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "copy")

        modules_dir = target / "modules"
        assert modules_dir.is_dir() and not modules_dir.is_symlink()
        assert (modules_dir / "Dio_TS_T40D11M7I0R0" / "plugin.xml").is_file()
        assert not (target / "Def").exists()

        # def path resolves inside the project tree, from config/ (never autosar/)
        assert project.module_defs["Dio"] == modules_dir / "Dio_TS_T40D11M7I0R0" / "config" / "Dio.arxml"

    def test_provenance_and_v8_saved(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "copy")
        assert project.module_provenance["Dio"]["origin"] == "eb-import"
        assert project.module_provenance["Dio"]["source_epc"] == "Config/THA6206/output/Dio.epc"
        assert project.module_provenance["Dio"]["imported_at"]
        manager.save_project()

        data = json.loads(project.path.read_text(encoding="utf-8"))
        assert data["format_version"] == 8
        assert data["import_mode"] == "copy"
        (dio_entry,) = [m for m in data["modules"] if m["name"] == "Dio"]
        assert dio_entry["definition"] == "/THA6_AS440_FuSa/Dio"
        assert dio_entry["library"] == 0
        assert dio_entry["config_path"] == "config/Dio.arxml"
        assert (target / "config" / "Dio.arxml").is_file()
        assert not (target / "ConfigValue").exists()

    def test_backslash_source_epc_normalized_on_load(self, tmp_path):
        """Format 7 projects saved on Windows before the POSIX fix stored backslashes"""
        dpa = write_v7_imported_project(
            tmp_path / "OldImport", source_epc="Config\\THA6206\\output\\Dio.epc")

        loaded_project, failed = WorkspaceManager().load_project(dpa)
        assert loaded_project.module_provenance["Dio"]["source_epc"] == "Config/THA6206/output/Dio.epc"

    def test_relocated_copy_project_still_loads(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "copy")
        manager.save_project()

        moved = tmp_path / "Relocated"
        shutil.move(str(target), str(moved))

        loaded_project, failed = WorkspaceManager().load_project(moved / project.path.name)
        assert not failed
        assert "Dio" in loaded_project.module_managers
        assert loaded_project.module_defs["Dio"].is_relative_to(moved / "modules")
        assert loaded_project.module_entries["Dio"].definition == "/THA6_AS440_FuSa/Dio"


class TestLinkMode:
    def test_link_mode_registers_library_without_symlinks(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "link")

        plugins = (eb_source_tree / "Define" / "EbPlugins" / "eclipse").resolve()
        (library,) = project.module_libraries
        assert library.kind == "eb-plugins"
        assert library.path == plugins.as_posix()
        assert project.module_defs["Dio"].resolve().is_relative_to(plugins)

        # Nothing linked or copied: no Def/plugins, no templates/{Module}
        assert not (target / "Def").exists()
        assert not (target / "templates").exists()
        assert not (target / "modules").exists()
        assert not _has_symlink(target)

    def test_link_mode_save_and_reload(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "link")
        manager.save_project()

        data = json.loads(project.path.read_text(encoding="utf-8"))
        assert data["import_mode"] == "link"
        assert data["format_version"] == 8

        loaded_project, failed = WorkspaceManager().load_project(project.path)
        assert not failed
        assert loaded_project.import_mode == "link"
        assert "Dio" in loaded_project.module_managers
        assert not _has_symlink(target)

    def test_link_mode_missing_source_tree_fails_clearly(self, eb_source_tree, tmp_path, monkeypatch):
        manager, project, target = _import(eb_source_tree, tmp_path, "link")
        manager.save_project()

        monkeypatch.delenv("TRESOS_PLUGINS_PATH", raising=False)
        shutil.move(str(eb_source_tree), str(tmp_path / "MovedAway"))

        with pytest.raises(ValueError, match="EB source tree not found"):
            WorkspaceManager().load_project(project.path)


class TestV6Migration:
    def test_v6_project_loads_and_upgrades_to_v7(self, eb_source_tree, tmp_path):
        # Build a v6-era project file by hand
        proj_dir = tmp_path / "OldProject"
        (proj_dir / "ConfigValue").mkdir(parents=True)
        def_file = proj_dir / "Dio_Def.arxml"
        shutil.copy(DIO_DEF_SAMPLE, def_file)
        (proj_dir / "ConfigValue" / "Dio_Config.arxml").write_text(DIO_EPC, encoding="utf-8")

        dpa = proj_dir / "OldProject.dpa"
        dpa.write_text(json.dumps({
            "format_version": 6,
            "project_type": "EB Tresos",
            "name": "OldProject",
            "variants": ["Default"],
            "active_variant": "Default",
            "modules": [{
                "name": "Dio",
                "def_path": "Dio_Def.arxml",
                "config_path": "ConfigValue/Dio_Config.arxml",
                "variant_overrides": {},
            }],
        }), encoding="utf-8")

        manager = WorkspaceManager()
        project, failed = manager.load_project(dpa)
        assert not failed
        # Missing provenance defaults to native; missing mode defaults to copy
        assert project.module_provenance["Dio"]["origin"] == "native"
        assert project.import_mode == "copy"

        manager.save_project()
        data = json.loads(dpa.read_text(encoding="utf-8"))
        assert data["format_version"] == 7
        assert data["modules"][0]["origin"] == "native"

    def test_future_version_rejected(self, tmp_path):
        dpa = tmp_path / "Future.dpa"
        dpa.write_text(json.dumps({"format_version": 9, "name": "X", "modules": []}), encoding="utf-8")
        with pytest.raises(ValueError, match="Unsupported project format version"):
            WorkspaceManager().load_project(dpa)
