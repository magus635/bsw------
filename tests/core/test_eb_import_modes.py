"""
Tests for EB import modes (copy/link), module provenance, and .dpa format v7
(openspec change: add-eb-import-modes)
"""
import json
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


@pytest.fixture
def eb_source_tree(tmp_path):
    """Minimal EB Tresos project tree with one Dio plugin + EPC output"""
    src_root = tmp_path / "EbSource"
    plugin = src_root / "Define" / "EbPlugins" / "eclipse" / "Dio_TS_T40D11M7I0R0"
    (plugin / "autosar").mkdir(parents=True)
    shutil.copy(DIO_DEF_SAMPLE, plugin / "autosar" / "Dio_THA6206_LFBGA292.arxml")
    (plugin / "generate_PB" / "Dio").mkdir(parents=True)
    (plugin / "generate_PB" / "Dio" / "Dio_Cfg.h.tpl").write_text("/* tpl */", encoding="utf-8")

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


class TestCopyMode:
    def test_copy_mode_is_self_contained(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "copy")

        plugins_dir = target / "Def" / "plugins"
        assert plugins_dir.is_dir() and not plugins_dir.is_symlink()
        assert (plugins_dir / "Dio_TS_T40D11M7I0R0" / "autosar").is_dir()

        # def path resolves inside the project tree
        assert str(project.module_defs["Dio"]).startswith(str(target))

    def test_provenance_and_v7_saved(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "copy")
        manager.save_project()

        data = json.loads(project.path.read_text(encoding="utf-8"))
        assert data["format_version"] == 7
        assert data["import_mode"] == "copy"
        (dio_entry,) = [m for m in data["modules"] if m["name"] == "Dio"]
        assert dio_entry["origin"] == "eb-import"
        assert dio_entry["source_epc"] == "Config/THA6206/output/Dio.epc"
        assert dio_entry["imported_at"]

    def test_relocated_copy_project_still_loads(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "copy")
        manager.save_project()

        moved = tmp_path / "Relocated"
        shutil.move(str(target), str(moved))

        loaded_project, failed = WorkspaceManager().load_project(moved / project.path.name)
        assert not failed
        assert "Dio" in loaded_project.module_managers
        assert loaded_project.module_provenance["Dio"]["origin"] == "eb-import"


class TestLinkMode:
    def test_link_mode_symlinks_instead_of_copies(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "link")

        plugins_link = target / "Def" / "plugins"
        assert plugins_link.is_symlink()
        assert plugins_link.resolve() == (
            eb_source_tree / "Define" / "EbPlugins" / "eclipse").resolve()

        # Template dir is a symlink to the plugin's generate_PB
        tpl_link = target / "templates" / "Dio"
        assert tpl_link.is_symlink()
        assert (tpl_link / "Dio" / "Dio_Cfg.h.tpl").exists()

    def test_link_mode_save_and_reload(self, eb_source_tree, tmp_path):
        manager, project, target = _import(eb_source_tree, tmp_path, "link")
        manager.save_project()

        data = json.loads(project.path.read_text(encoding="utf-8"))
        assert data["import_mode"] == "link"

        loaded_project, failed = WorkspaceManager().load_project(project.path)
        assert not failed
        assert loaded_project.import_mode == "link"
        assert "Dio" in loaded_project.module_managers

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
        dpa.write_text(json.dumps({"format_version": 8, "name": "X", "modules": []}), encoding="utf-8")
        with pytest.raises(ValueError, match="Unsupported project format version"):
            WorkspaceManager().load_project(dpa)
