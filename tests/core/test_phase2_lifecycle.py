"""Tests for Phase 2 lifecycle features (W5 REC on container create, W7 delete/restore, W8 v7->v8 upgrade) and MCAL properties extraction."""
import json
from pathlib import Path

import pytest

from autosar_configurator.core.davinci_importer import McalResourceExtractor
from autosar_configurator.core.packages.library import LibraryRef, scan_library
from autosar_configurator.core.workspace_manager import WorkspaceManager


_PKG_DEF = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Vendor</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>Mod</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>ModGeneral</SHORT-NAME>
          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          <PARAMETERS>
            <ECUC-STRING-PARAM-DEF><SHORT-NAME>PreParam</SHORT-NAME></ECUC-STRING-PARAM-DEF>
            <ECUC-STRING-PARAM-DEF><SHORT-NAME>Mode</SHORT-NAME><DEFAULT-VALUE>Slow</DEFAULT-VALUE></ECUC-STRING-PARAM-DEF>
            <ECUC-INTEGER-PARAM-DEF><SHORT-NAME>RecOnly</SHORT-NAME></ECUC-INTEGER-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>ModChannel</SHORT-NAME>
          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
          <PARAMETERS>
            <ECUC-STRING-PARAM-DEF><SHORT-NAME>ChannelMode</SHORT-NAME><DEFAULT-VALUE>Normal</DEFAULT-VALUE></ECUC-STRING-PARAM-DEF>
            <ECUC-INTEGER-PARAM-DEF><SHORT-NAME>BaudRate</SHORT-NAME></ECUC-INTEGER-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

_PKG_VALUES = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Vendor</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Mod_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Mod</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>ModGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/Mod/ModGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/Mod/ModGeneral/PreParam</DEFINITION-REF>
              <VALUE>LockedPre</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Mod_Rec</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Mod</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>ModGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/Mod/ModGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/Mod/ModGeneral/PreParam</DEFINITION-REF>
              <VALUE>RecShouldNotOverridePre</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/Mod/ModGeneral/Mode</DEFINITION-REF>
              <VALUE>Fast</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/Vendor/Mod/ModGeneral/RecOnly</DEFINITION-REF>
              <VALUE>42</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>ModChannel</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/Mod/ModChannel</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/Mod/ModChannel/ChannelMode</DEFINITION-REF>
              <VALUE>Turbo</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/Vendor/Mod/ModChannel/BaudRate</DEFINITION-REF>
              <VALUE>500000</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""


def _setup_v8_project(tmp_path: Path):
    lib = tmp_path / "lib"
    pkg_dir = lib / "Mod"
    (pkg_dir / "def").mkdir(parents=True)
    (pkg_dir / "config").mkdir(parents=True)
    (pkg_dir / "def" / "Mod.arxml").write_text(_PKG_DEF, encoding="utf-8")
    (pkg_dir / "config" / "Mod_values.arxml").write_text(_PKG_VALUES, encoding="utf-8")
    (pkg_dir / "module.json").write_text(
        json.dumps({
            "schema": 1,
            "module": "Mod",
            "definition": "/Vendor/Mod",
            "files": ["def/Mod.arxml", "config/Mod_values.arxml"],
            "pre": ["/Vendor/Mod_Pre"],
            "rec": ["/Vendor/Mod_Rec"],
        }),
        encoding="utf-8",
    )

    wm = WorkspaceManager()
    project = wm.create_project("Proj", tmp_path / "proj" / "Proj.dpa", format_version=8)
    project.selected_chip = None
    lib_ref = LibraryRef(path=lib.as_posix(), kind="package")
    project.module_libraries.append(lib_ref)
    pkg = scan_library(lib_ref, project.path.parent)[0]
    mgr = project.add_module_from_package(pkg, 0)
    return wm, project, mgr


def test_w5_create_container_uses_package_rec_initial_values(tmp_path):
    """Creating a new container instance applies package REC initial values without touching Pre locks."""
    _, _, mgr = _setup_v8_project(tmp_path)

    # Create a brand new ModChannel instance -> should receive ChannelMode=Turbo & BaudRate=500000 from REC
    ch_def = mgr.module_def.containers["ModChannel"]
    ch = mgr.create_container_instance(ch_def, instance_name="ModChannel_1")
    assert ch.parameter_values["ChannelMode"].value == "Turbo"
    assert ch.parameter_values["BaudRate"].value == 500000

    # Pre key on ModGeneral remained locked with LockedPre
    gen = next(c for c in mgr.configuration.containers if c.short_name == "ModGeneral")
    assert gen.parameter_values["PreParam"].value == "LockedPre"


def test_w7_remove_module_archives_and_restore_recovers_config(tmp_path):
    """Removing a Format 8 module archives to .history/deleted/ and restore_deleted_module recovers it."""
    wm, project, mgr = _setup_v8_project(tmp_path)
    ch = mgr.create_container_instance(mgr.module_def.containers["ModChannel"], instance_name="CustomCh")
    mgr.set_parameter_value(ch, "BaudRate", 1000000)
    wm.save_project()

    # Remove with archive_move=True so active config/<M>.arxml is cleared and archived
    project.remove_module("Mod", archive_move=True)
    assert "Mod" not in project.module_managers
    assert not (tmp_path / "proj" / "config" / "Mod.arxml").exists()

    archives = project.list_deleted_archives("Mod")
    assert len(archives) == 1
    assert archives[0].parent == tmp_path / "proj" / ".history" / "deleted"

    restored_mgr = project.restore_deleted_module(archives[0])
    assert "Mod" in project.module_managers
    custom_ch = next(c for c in restored_mgr.configuration.containers if c.short_name == "CustomCh")
    assert custom_ch.parameter_values["BaudRate"].value == 1000000


def test_w8_upgrade_v7_project_to_v8_preserves_modules(tmp_path):
    """Explicit upgrade_project_to_v8 converts a Format 7 project into Format 8 cleanly."""
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

    proj_dir = tmp_path / "legacy_proj"
    def_dir = proj_dir / "Def" / "plugins" / "Dio_THA6_AS440" / "config"
    def_dir.mkdir(parents=True)
    (proj_dir / "Def" / "plugins" / "Dio_THA6_AS440" / "plugin.xml").write_text("""<?xml version="1.0"?>
<plugin>
  <extension point="dreisoft.tresos.launcher2.plugin.configuration" id="DioCfg">
    <configuration moduleId="Dio">
      <schema><resource type="xdm" value="config/Dio.xdm"/></schema>
      <data><schemaNode path="ASPath:/THA6/Dio"/></data>
    </configuration>
  </extension>
</plugin>""", encoding="utf-8")
    xdm_path = def_dir / "Dio.xdm"
    xdm_path.write_text("""<?xml version="1.0"?>
<datamodel version="7.0"
           xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
           xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES"><d:ctr name="THA6" type="AR-PACKAGE"><d:lst type="ELEMENTS">
      <d:chc name="Dio" type="AR-ELEMENT" value="MODULE-DEF"><v:ctr type="MODULE-DEF">
        <v:ctr name="DioGeneral" type="IDENTIFIABLE">
          <v:var name="DioDevErrorDetect" type="BOOLEAN"><a:da name="DEFAULT" value="false"/></v:var>
        </v:ctr>
      </v:ctr></d:chc>
    </d:lst></d:ctr></d:lst>
  </d:ctr>
</datamodel>""", encoding="utf-8")

    wm = WorkspaceManager()
    dpa_path = proj_dir / "Legacy.dpa"
    project = wm.create_project("Legacy", dpa_path, format_version=7)
    module_def = EcucDefParser().parse_module_def_file(xdm_path)
    mgr = project.add_module(module_def, xdm_path)
    gen = mgr.create_container_instance(module_def.containers["DioGeneral"], instance_name="DioGeneral")
    mgr.set_parameter_value(gen, "DioDevErrorDetect", True)
    wm.save_project()

    assert (proj_dir / "ConfigValue" / "Dio_Config.arxml").is_file()

    report = wm.upgrade_project_to_v8()
    assert report["format_version"] == 8
    assert report["upgraded_modules"] == ["Dio"]
    assert project.format_version == 8
    assert (proj_dir / "config" / "Dio.arxml").is_file()
    assert (proj_dir / "config" / "base").is_dir()

    reloaded, failed = WorkspaceManager().load_project(dpa_path)
    assert failed == []
    assert reloaded.format_version == 8
    assert reloaded.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True


def test_mcal_resource_extractor_supports_eb_cotexr52_properties(tmp_path):
    """McalResourceExtractor handles real EB Resource_*/resource/CotexR52_<Chip>.properties with _source."""
    res_dir = tmp_path / "Def" / "plugins" / "Resource_THA6_AS440" / "resource"
    res_dir.mkdir(parents=True)
    prop_file = res_dir / "CotexR52_THA6206_LFBGA292.properties"
    prop_file.write_text(
        "Port.AvailablePortsID: _0_ _1_ _2_\nSpi.MaxHwUnit: 9\n",
        encoding="utf-8",
    )

    extractor = McalResourceExtractor(tmp_path)
    all_res = extractor.extract_all_chips_resources()
    assert "THA6206_LFBGA292" in all_res
    assert all_res["THA6206_LFBGA292"]["Port"]["AvailablePortsID"] == "_0_ _1_ _2_"
    assert all_res["THA6206_LFBGA292"]["Port"]["_source"] == prop_file.as_posix()


def test_restore_deleted_module_refuses_overwrite_when_already_loaded(tmp_path):
    """restore_deleted_module must reject restoring an already-loaded module without touching config/<M>.arxml."""
    wm, project, mgr = _setup_v8_project(tmp_path)
    proj_dir = project.path.parent

    gen = next(c for c in mgr.configuration.containers if c.short_name == "ModGeneral")
    mgr.set_parameter_value(gen, "RecOnly", 111)
    wm.save_project()

    # Delete once to create an archive with value 111, then restore and modify active to 222
    project.remove_module("Mod", archive_move=True)
    archive_path = project.list_deleted_archives("Mod")[0]
    restored_mgr = project.restore_deleted_module(archive_path)
    restored_gen = next(c for c in restored_mgr.configuration.containers if c.short_name == "ModGeneral")
    restored_mgr.set_parameter_value(restored_gen, "RecOnly", 222)
    wm.save_project()

    cfg_before = (proj_dir / "config" / "Mod.arxml").read_text(encoding="utf-8")
    assert "222" in cfg_before

    with pytest.raises(ValueError, match="already loaded"):
        project.restore_deleted_module(archive_path)

    # Disk config must remain untouched
    cfg_after = (proj_dir / "config" / "Mod.arxml").read_text(encoding="utf-8")
    assert cfg_after == cfg_before
