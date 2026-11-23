"""End-to-end integration tests for W12 DaVinci project import."""
import json
from pathlib import Path

from autosar_configurator.core.workspace_manager import WorkspaceManager


def _create_sample_sip_and_davinci(root: Path):
    """Build a realistic Vector SIP + DaVinci XML .dpa + EB MCAL tree."""
    sip = root / "sip"

    # 1. Os (BSW with DerivativeMapping + Pre + Implementation dir)
    os_dir = sip / "Components" / "Os"
    (os_dir / "BSWMD").mkdir(parents=True)
    (os_dir / "Implementation").mkdir(parents=True)
    (os_dir / "BSWMD" / "Os_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>Os</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>OsOS</SHORT-NAME>
          <PARAMETERS>
            <ECUC-ENUMERATION-PARAM-DEF><SHORT-NAME>OsStatus</SHORT-NAME><LITERALS>
              <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>STANDARD</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
              <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>EXTENDED</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
            </LITERALS></ECUC-ENUMERATION-PARAM-DEF>
            <ECUC-INTEGER-PARAM-DEF><SHORT-NAME>OsCoreCount</SHORT-NAME></ECUC-INTEGER-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>OsTask</SHORT-NAME>
          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
          <PARAMETERS>
            <ECUC-INTEGER-PARAM-DEF><SHORT-NAME>OsTaskPriority</SHORT-NAME></ECUC-INTEGER-PARAM-DEF>
          </PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
    <BSW-IMPLEMENTATION>
      <SHORT-NAME>Os_Impl</SHORT-NAME>
      <SW-VERSION>2.10.00</SW-VERSION>
      <PRECONFIGURED-CONFIGURATION-REFS>
        <PRECONFIGURED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/Os_Pre</PRECONFIGURED-CONFIGURATION-REF>
      </PRECONFIGURED-CONFIGURATION-REFS>
    </BSW-IMPLEMENTATION>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # Wrong chip subdir vs matching chip subdir via DerivativeMapping
    (os_dir / "BSWMD" / "Os" / "WrongChip").mkdir(parents=True)
    (os_dir / "BSWMD" / "Os" / "WrongChip" / "Os_Wrong_pre.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Os</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>OsOS</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsOS</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/Os/OsOS/OsCoreCount</DEFINITION-REF>
          <VALUE>99</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    (os_dir / "BSWMD" / "Os" / "THA6206_Sub").mkdir(parents=True)
    (os_dir / "BSWMD" / "Os" / "THA6206_Sub" / "Os_THA_pre.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Os</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>OsOS</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsOS</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/Os/OsOS/OsCoreCount</DEFINITION-REF>
          <VALUE>2</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    (os_dir / "GeneratorMsr").mkdir()
    (os_dir / "GeneratorMsr" / "DerivativeMapping_Os.xml").write_text("""<?xml version="1.0"?>
<Settings Name="ModuleList"><Settings Name="Os">
  <Settings Name="THA6206_Sub">
    <Settings Name="UUID-THA6206"><Setting Name="SIP_Folder" Value="THA6206_Sub"/></Settings>
  </Settings>
</Settings></Settings>""", encoding="utf-8")

    # 2. Com (BSW with reference to OsTask)
    com_dir = sip / "Components" / "Com" / "BSWMD"
    com_dir.mkdir(parents=True)
    (com_dir / "Com_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>Com</SHORT-NAME>
      <CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF>
        <SHORT-NAME>ComMainFunction</SHORT-NAME>
        <PARAMETERS><ECUC-STRING-PARAM-DEF><SHORT-NAME>ComMode</SHORT-NAME></ECUC-STRING-PARAM-DEF></PARAMETERS>
        <REFERENCES><ECUC-REFERENCE-DEF>
          <SHORT-NAME>ComTaskRef</SHORT-NAME>
          <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsTask</DESTINATION-REF>
        </ECUC-REFERENCE-DEF></REFERENCES>
      </ECUC-PARAM-CONF-CONTAINER-DEF></CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # 3. UnusedMod (present in SIP, NOT active in DaVinci .dpa -> must NOT be added to project)
    unused_dir = sip / "Components" / "UnusedMod" / "BSWMD"
    unused_dir.mkdir(parents=True)
    (unused_dir / "UnusedMod_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>UnusedMod</SHORT-NAME></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # 4. DaVinci project (.dpa + Config/ECUC/*_ecuc.arxml)
    app_dir = sip / "Applications" / "MyApp"
    ecuc_dir = app_dir / "Config" / "ECUC"
    ecuc_dir.mkdir(parents=True)

    (ecuc_dir / "MyApp_Os_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Os</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>OsOS</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsOS</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/Os/OsOS/OsStatus</DEFINITION-REF>
              <VALUE>EXTENDED</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/Os/OsOS/OsCoreCount</DEFINITION-REF>
              <VALUE>2</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>InitTask</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsTask</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/Os/OsTask/OsTaskPriority</DEFINITION-REF>
              <VALUE>15</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    (ecuc_dir / "MyApp_Com_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Com</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Com</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>ComMainFunction</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Com/ComMainFunction</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/Com/ComMainFunction/ComMode</DEFINITION-REF>
              <VALUE>CYCLIC_FROM_ECUC</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE>
              <DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/MICROSAR/Com/ComMainFunction/ComTaskRef</DEFINITION-REF>
              <VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Os/InitTask</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    dpa_file = app_dir / "MyApp.dpa"
    dpa_file.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<ProjectAssistant Version="5.30.35 SP2">
  <Folders>
    <SIP>.\\..\\..</SIP>
    <ECUC>.\\Config\\ECUC</ECUC>
  </Folders>
  <Environment>
    <Derivative UUID="UUID-THA6206">Tongxin_THA6206</Derivative>
  </Environment>
  <Display>
    <ModuleDefinitionMappings>
      <ModuleDefinitionMapping ModuleConfigName="Os" ModuleDefinitionRef="/MICROSAR/Os"/>
      <ModuleDefinitionMapping ModuleConfigName="Com" ModuleDefinitionRef="/MICROSAR/Com"/>
      <ModuleDefinitionMapping ModuleConfigName="Dio" ModuleDefinitionRef="/THA6_AS440_FuSa/Dio"/>
    </ModuleDefinitionMappings>
  </Display>
  <EcucSplitter>
    <Splitter File=".\\Config\\ECUC\\MyApp_Os_ecuc.arxml"><Module Name="Os"/></Splitter>
    <Splitter File=".\\Config\\ECUC\\MyApp_Com_ecuc.arxml"><Module Name="Com"/></Splitter>
    <Splitter File=".\\Config\\ECUC\\MyApp_Dio_ecuc.arxml"><Module Name="Dio"/></Splitter>
  </EcucSplitter>
</ProjectAssistant>""", encoding="utf-8")

    # 5. Minimal EB MCAL project with Dio plugin + EPC
    eb_root = root / "eb_mcal"
    dio_plugin = eb_root / "Def" / "plugins" / "Dio_THA6_AS440"
    (dio_plugin / "config").mkdir(parents=True)
    (dio_plugin / "autosar").mkdir(parents=True)
    (dio_plugin / "plugin.xml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<plugin>
  <extension point="dreisoft.tresos.launcher2.plugin.module" id="Dio_THA6_AS440" name="Dio_THA6_AS440">
    <module id="Dio_THA6_AS440" label="Dio" mandatory="false" allowMultiple="false"
            swVersionMajor="1" swVersionMinor="0" swVersionPatch="0"
            specVersionMajor="4" specVersionMinor="4" specVersionPatch="0"/>
  </extension>
  <extension point="dreisoft.tresos.launcher2.plugin.configuration" id="Dio_Config">
    <configuration moduleId="Dio_THA6_AS440">
      <schema><resource type="xdm" value="config/Dio.xdm"/></schema>
      <data><schemaNode path="ASPath:/THA6_AS440_FuSa/Dio"/></data>
    </configuration>
  </extension>
</plugin>""", encoding="utf-8")
    (dio_plugin / "config" / "Dio.xdm").write_text("""<?xml version="1.0"?>
<datamodel version="7.0"
           xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
           xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="THA6_AS440_FuSa" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Dio" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF">
              <v:ctr name="DioGeneral" type="IDENTIFIABLE">
                <v:var name="DioDevErrorDetect" type="BOOLEAN"><a:da name="DEFAULT" value="false"/></v:var>
              </v:ctr>
            </v:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>""", encoding="utf-8")
    epc_dir = eb_root / "Config" / "THA6206_LFBGA292" / "output"
    epc_dir.mkdir(parents=True)
    (epc_dir / "Dio.epc").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Dio</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Dio</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Dio</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>DioGeneral</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_AS440_FuSa/Dio/DioGeneral</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/THA6_AS440_FuSa/Dio/DioGeneral/DioDevErrorDetect</DEFINITION-REF>
          <VALUE>true</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    return dpa_file, eb_root


def test_import_davinci_project_preserves_ecuc_values_mcal_and_report(tmp_path):
    dpa_file, eb_root = _create_sample_sip_and_davinci(tmp_path)
    out_parent = tmp_path / "out"

    wm = WorkspaceManager()
    project, report = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=out_parent,
        project_name="MigratedApp",
        mcal_source_dir=eb_root,
    )

    # 1. Active BSW modules (Os, Com) + EB MCAL (Dio) imported; UnusedMod NOT active,
    #    yet full SIP modules reside under modules/davinci/ with unified config/ layout.
    assert set(project.module_managers.keys()) == {"Os", "Com", "Dio"}
    assert "UnusedMod" not in project.module_managers
    proj_root = out_parent / "MigratedApp"
    assert not (proj_root / "DaVinciImport").exists()
    assert not (proj_root / ".import_report.md").exists()
    assert project.module_libraries[0].path == "modules/davinci"
    os_pkg = proj_root / "modules" / "davinci" / "Os"
    assert (os_pkg / "config" / "Os.arxml").is_file()
    assert (os_pkg / "config" / "Os_Pre.arxml").is_file()
    assert not (os_pkg / "def").exists()
    assert not (os_pkg / "sources.json").exists()
    assert (proj_root / "modules" / "davinci" / "UnusedMod" / "module.json").is_file()
    assert project.packages["Os"].manifest.implementation == (
        tmp_path / "sip" / "Components" / "Os" / "Implementation"
    ).resolve().as_posix()

    # 2. Derivative metadata recorded and persisted in .dpa
    assert project.derivative_uuid == "UUID-THA6206"
    assert project.derivative_name == "Tongxin_THA6206"
    saved_dpa = json.loads((proj_root / "MigratedApp.dpa").read_text(encoding="utf-8"))
    assert saved_dpa["format_version"] == 8
    assert saved_dpa["derivative_uuid"] == "UUID-THA6206"
    assert saved_dpa["derivative_name"] == "Tongxin_THA6206"

    # 3. Real DaVinci ECUC values imported (not overwritten with empty/WrongChip values)
    os_mgr = project.module_managers["Os"]
    os_os = next(c for c in os_mgr.configuration.containers if c.short_name == "OsOS")
    assert os_os.parameter_values["OsStatus"].value == "EXTENDED"
    assert os_os.parameter_values["OsCoreCount"].value == 2
    init_task = next(c for c in os_mgr.configuration.containers if c.short_name == "InitTask")
    assert init_task.parameter_values["OsTaskPriority"].value == 15

    com_mgr = project.module_managers["Com"]
    com_main = com_mgr.configuration.containers[0]
    assert com_main.parameter_values["ComMode"].value == "CYCLIC_FROM_ECUC"
    assert com_main.reference_values["ComTaskRef"].target is init_task

    # 4. DaVinci Dio skipped in favor of EB MCAL Dio with its EPC value
    assert any(item["module"] == "Dio" for item in report.skipped_mcal_modules)
    dio_mgr = project.module_managers["Dio"]
    assert dio_mgr.configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True

    # 5. Report written with per-module stats and zero inconsistencies/value diffs on clean import
    assert report.pre_inconsistencies == []
    assert report.version_mismatches == []
    assert report.value_diffs == []
    reports = sorted((proj_root / ".history" / "reports").glob("*_davinci_import.md"))
    assert len(reports) == 1
    assert report.report_files == [reports[0].as_posix()]
    assert not (proj_root / ".history" / "reports" / "davinci_import_report.md").exists()
    md = reports[0].read_text(encoding="utf-8")
    assert "Os" in md and "davinci_ecuc" in md
    assert "Dio" in md and "eb_mcal" in md

    # 6. Reload preserves everything cleanly
    reloaded, failed = WorkspaceManager().load_project(out_parent / "MigratedApp" / "MigratedApp.dpa")
    assert failed == []
    assert reloaded.derivative_uuid == "UUID-THA6206"
    assert set(reloaded.module_managers.keys()) == {"Os", "Com", "Dio"}


def test_import_davinci_project_rejecting_pre_merge_skips_module(tmp_path):
    dpa_file, _ = _create_sample_sip_and_davinci(tmp_path)
    # Force a Pre vs Active conflict on OsCoreCount (Active=2 in ECUC -> make Pre=4)
    pre_file = tmp_path / "sip" / "Components" / "Os" / "BSWMD" / "Os" / "THA6206_Sub" / "Os_THA_pre.arxml"
    pre_file.write_text(pre_file.read_text(encoding="utf-8").replace("<VALUE>2</VALUE>", "<VALUE>4</VALUE>"),
                        encoding="utf-8")

    wm = WorkspaceManager()
    seen_modules = []

    def reject_merge(preview_text, merge_result):
        seen_modules.append(preview_text)
        return False

    project, report = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=tmp_path / "rejected_out",
        project_name="RejectedTest",
        confirm=reject_merge,
    )

    assert len(seen_modules) == 1
    assert report.rejected_modules == ["Os"]
    assert "Os" not in project.module_managers
    assert "Os" not in project.module_entries
    assert "Com" in project.module_managers
    # Rejecting a module during import must not leave ghost files under .history/deleted/
    assert project.list_deleted_archives() == []


def test_davinci_dpa_resolves_parent_sip_root_and_respects_active_collection(tmp_path):
    """Real StartApplication.dpa layout: <SIP>.\\..\\..</SIP> lands on Applications/ (one level below SIP root),
    and ModuleDefinitionMappings has unused entries while <Configuration> ECUC-VALUE-COLLECTION lists only active ones."""
    from autosar_configurator.core.davinci_importer import DaVinciProject

    sip_root = tmp_path / "mcuapp"
    (sip_root / "Components" / "Os" / "BSWMD").mkdir(parents=True)
    app_dir = sip_root / "Applications" / "SipAddon" / "StartApplication"
    (app_dir / "Config" / "ECUC").mkdir(parents=True)

    (app_dir / "Config" / "ECUC" / "StartApplication.ecuc.arxml").write_text("""<?xml version="1.0"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-VALUE-COLLECTION>
      <SHORT-NAME>ActiveEcuC</SHORT-NAME>
      <ECUC-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
          <ECUC-MODULE-CONFIGURATION-VALUES-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/ActiveEcuC/Os</ECUC-MODULE-CONFIGURATION-VALUES-REF>
        </ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
      </ECUC-VALUES>
    </ECUC-VALUE-COLLECTION>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    dpa_path = app_dir / "StartApplication.dpa"
    dpa_path.write_text("""<?xml version="1.0"?>
<ProjectAssistant Version="5.30.35 SP2">
  <Folders><SIP>.\\..\\..</SIP></Folders>
  <Settings>
    <ModuleDefinitionMappings>
      <ModuleDefinitionMapping ModuleConfigName="Os" ModuleDefinitionRef="/MICROSAR/Os"/>
      <ModuleDefinitionMapping ModuleConfigName="UnusedEthIf" ModuleDefinitionRef="/MICROSAR/EthIf"/>
      <ModuleDefinitionMapping ModuleConfigName="UnusedFrIf" ModuleDefinitionRef="/AUTOSAR/EcucDefs/FrIf"/>
    </ModuleDefinitionMappings>
  </Settings>
  <EcucSplitter>
    <Configuration>Config\\ECUC\\StartApplication.ecuc.arxml</Configuration>
    <Splitter File=".\\Config\\ECUC\\StartApplication_Os_Os_ecuc.arxml"><Module Name="Os"/></Splitter>
  </EcucSplitter>
</ProjectAssistant>""", encoding="utf-8")

    dv = DaVinciProject.from_file(dpa_path)
    assert dv.sip_root == sip_root.resolve()
    assert dv.active_modules == {"Os"}
    assert "UnusedEthIf" not in dv.active_modules
    assert "UnusedFrIf" not in dv.active_modules


def test_import_davinci_project_selects_chip_by_derivative_uuid_without_mcal(tmp_path, monkeypatch):
    """Pure DaVinci import without mcal_source_dir still selects matching chip by derivative_uuid."""
    from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition

    dpa_file, _ = _create_sample_sip_and_davinci(tmp_path)
    db = ChipDatabase()
    db.register_chip(
        ChipDefinition(
            name="CUSTOM_THA6206_CHIP",
            derivative_uuid="uuid-tha6206",  # verify case-insensitive match
            ecu_resources={"OsResource": {"NumOfCores": 2}},
        )
    )
    monkeypatch.setattr(
        "autosar_configurator.core.hardware.chip_database.get_default_chip_database",
        lambda: db,
    )
    monkeypatch.setattr(
        "autosar_configurator.core.hardware.ecu_resource_resolver.get_default_chip_database",
        lambda: db,
    )

    wm = WorkspaceManager()
    project, report = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=tmp_path / "uuid_out",
        project_name="UuidChipApp",
        confirm=lambda p, r: True,
    )

    assert project.selected_chip == "CUSTOM_THA6206_CHIP"
    assert "CUSTOM_THA6206_CHIP" in project.available_chips
    assert project.ecu_resources.get("OsResource.NumOfCores") == 2


def _create_overlapping_sip_and_eb(root: Path):
    """Extend _create_sample_sip_and_davinci with a Vector-wrapped SIP Dio + ECUC (value=false)
    matching EB Dio's definition /THA6_AS440_FuSa/Dio (value=true)."""
    dpa_file, eb_root = _create_sample_sip_and_davinci(root)
    sip = root / "sip"

    # SIP Components/Mcal_Tha62x/BSWMD/Dio_bswmd.arxml
    mcal_bswmd = sip / "Components" / "Mcal_Tha62x" / "BSWMD"
    mcal_bswmd.mkdir(parents=True)
    (mcal_bswmd / "Dio_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>THA6_AS440_FuSa</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>Dio</SHORT-NAME>
      <CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF>
        <SHORT-NAME>DioGeneral</SHORT-NAME>
        <PARAMETERS><ECUC-BOOLEAN-PARAM-DEF>
          <SHORT-NAME>DioDevErrorDetect</SHORT-NAME>
          <DEFAULT-VALUE>false</DEFAULT-VALUE>
        </ECUC-BOOLEAN-PARAM-DEF></PARAMETERS>
      </ECUC-PARAM-CONF-CONTAINER-DEF></CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # DaVinci ECUC for Dio (DioDevErrorDetect = false)
    ecuc_dir = sip / "Applications" / "MyApp" / "Config" / "ECUC"
    (ecuc_dir / "MyApp_Dio_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Dio</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Dio</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>DioGeneral</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_AS440_FuSa/Dio/DioGeneral</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/THA6_AS440_FuSa/Dio/DioGeneral/DioDevErrorDetect</DEFINITION-REF>
          <VALUE>false</VALUE>
        </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    return dpa_file, eb_root


def test_import_davinci_then_merge_eb_into_same_project(tmp_path):
    """Order 1: Import DaVinci first (Os, Com, SIP Dio), then merge EB MCAL (Dio) replacing Dio."""
    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    out_parent = tmp_path / "combo1_out"

    wm = WorkspaceManager()
    project, dv_report = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=out_parent,
        project_name="Combo1",
        confirm=lambda *_: True,
    )
    assert set(project.module_managers.keys()) == {"Os", "Com", "Dio"}
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False

    merged, loaded, failed = wm.import_eb_project(
        eb_root,
        mode="copy",
        into_project=project,
        on_conflict="replace",
        confirm=lambda *_: True,
    )
    assert merged is project
    assert project.path == out_parent / "Combo1" / "Combo1.dpa"
    assert failed == []
    assert "Dio" in loaded
    assert len(project.module_libraries) == 2
    assert project.module_libraries[0].path == "modules/davinci"
    assert project.module_libraries[1].path == "modules/eb"
    assert project.module_libraries[1].kind == "eb-plugins"
    assert "Dio" in project.module_libraries[0].exclude

    # BSW keeps DaVinci values + cross-module ref; Dio now uses EB EPC value (true)
    assert project.module_entries["Dio"].library == 1
    assert project.module_provenance["Dio"]["origin"] == "eb-import"
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True
    os_init = next(c for c in project.module_managers["Os"].configuration.containers if c.short_name == "InitTask")
    com_main = project.module_managers["Com"].configuration.containers[0]
    assert com_main.parameter_values["ComMode"].value == "CYCLIC_FROM_ECUC"
    assert com_main.reference_values["ComTaskRef"].target is os_init

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    assert set(reloaded.module_managers.keys()) == {"Os", "Com", "Dio"}
    assert reloaded.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True


def test_import_davinci_then_merge_eb_keep_existing(tmp_path):
    """Order 1 with on_conflict='keep': DaVinci Dio stays, EB plugin package is excluded cleanly."""
    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    out_parent = tmp_path / "combo1_keep_out"

    wm = WorkspaceManager()
    project, _ = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=out_parent,
        project_name="Combo1Keep",
        confirm=lambda *_: True,
    )

    _, _, failed = wm.import_eb_project(
        eb_root,
        mode="copy",
        into_project=project,
        on_conflict="keep",
        confirm=lambda *_: True,
    )
    assert failed == []
    assert project.module_entries["Dio"].library == 0
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False
    assert "Dio_THA6_AS440" in project.module_libraries[1].exclude

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    assert reloaded.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False


def test_import_eb_then_merge_davinci_into_same_project(tmp_path):
    """Order 2: Import EB MCAL first (Dio), then merge DaVinci .dpa (keeps EB Dio, adds Os & Com)."""
    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    target_dir = tmp_path / "Combo2"

    wm = WorkspaceManager()
    project, loaded, failed = wm.import_eb_project(
        eb_root,
        target_dir=target_dir,
        mode="copy",
        confirm=lambda *_: True,
    )
    assert failed == [] and "Dio" in loaded
    assert len(project.module_libraries) == 1

    merged, dv_report = wm.import_davinci_project(
        dpa_path=dpa_file,
        into_project=project,
        on_conflict="auto",
        confirm=lambda *_: True,
    )
    assert merged is project
    assert project.path == target_dir / "Combo2.dpa"
    assert dv_report.failed_modules == []
    assert len(project.module_libraries) == 2
    assert project.module_libraries[0].path == "modules/eb"
    assert project.module_libraries[0].kind == "eb-plugins"
    assert project.module_libraries[1].path == "modules/davinci"
    assert project.derivative_uuid == "UUID-THA6206"

    # EB Dio kept at library 0 with value=True; DaVinci Os & Com imported at library 1
    assert any(item["module"] == "Dio" for item in dv_report.skipped_mcal_modules)
    assert project.module_entries["Dio"].library == 0
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True
    assert project.module_entries["Os"].library == 1
    assert project.module_entries["Com"].library == 1
    os_init = next(c for c in project.module_managers["Os"].configuration.containers if c.short_name == "InitTask")
    com_main = project.module_managers["Com"].configuration.containers[0]
    assert com_main.parameter_values["ComMode"].value == "CYCLIC_FROM_ECUC"
    assert com_main.reference_values["ComTaskRef"].target is os_init

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    assert set(reloaded.module_managers.keys()) == {"Os", "Com", "Dio"}
    assert reloaded.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True
    assert reloaded.derivative_uuid == "UUID-THA6206"


def test_import_eb_then_merge_davinci_replace_conflict(tmp_path):
    """Order 2 with on_conflict='replace': DaVinci Dio replaces EB Dio and excludes EB plugin dir."""
    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    target_dir = tmp_path / "Combo2Replace"

    wm = WorkspaceManager()
    project, _, _ = wm.import_eb_project(
        eb_root,
        target_dir=target_dir,
        mode="copy",
        confirm=lambda *_: True,
    )
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True

    _, dv_report = wm.import_davinci_project(
        dpa_path=dpa_file,
        into_project=project,
        on_conflict="replace",
        confirm=lambda *_: True,
    )
    assert dv_report.failed_modules == []
    assert project.module_entries["Dio"].library == 1
    assert project.module_provenance["Dio"]["origin"] == "davinci-import"
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False
    assert "Dio_THA6_AS440" in project.module_libraries[0].exclude

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    assert reloaded.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False


def test_merge_eb_epc_only_stub_does_not_overwrite_existing_davinci_module(tmp_path):
    """An EB Config/*.epc stub without a plugin must never purge/overwrite an existing DaVinci module."""
    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    out_parent = tmp_path / "epc_stub_out"

    wm = WorkspaceManager()
    project, _ = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=out_parent,
        project_name="EpcStubSafe",
        confirm=lambda *_: True,
    )

    # Add an Os.epc stub with no corresponding Os plugin in eb_root
    epc_dir = eb_root / "Config" / "THA6206_LFBGA292" / "output"
    (epc_dir / "Os.epc").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Os</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Os</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>OsOS</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsOS</DEFINITION-REF>
        <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE>
          <DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/Os/OsOS/OsStatus</DEFINITION-REF>
          <VALUE>STANDARD</VALUE>
        </ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    _, loaded, failed = wm.import_eb_project(
        eb_root,
        mode="copy",
        into_project=project,
        on_conflict="replace",
        confirm=lambda *_: True,
    )
    assert failed == []
    assert "Dio" in loaded
    assert project.module_entries["Dio"].library == 1
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True

    # Existing DaVinci Os remains intact
    assert project.module_entries["Os"].library == 0
    assert project.module_provenance["Os"]["origin"] == "davinci-import"
    os_os = next(c for c in project.module_managers["Os"].configuration.containers if c.short_name == "OsOS")
    assert os_os.parameter_values["OsStatus"].value == "EXTENDED"

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    reloaded_os = next(c for c in reloaded.module_managers["Os"].configuration.containers if c.short_name == "OsOS")
    assert reloaded_os.parameter_values["OsStatus"].value == "EXTENDED"


def test_remerge_switching_conflict_winner_unexcludes_and_reloads_cleanly(tmp_path):
    """Switching winner between DaVinci and EB across re-merges updates exclude lists cleanly."""
    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    out_parent = tmp_path / "remerge_switch_out"

    wm = WorkspaceManager()
    # Step 1: Import DaVinci (Dio=False at lib 0)
    project, _ = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=out_parent,
        project_name="SwitchWinner",
        confirm=lambda *_: True,
    )
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False

    # Step 2: Merge EB with keep (DaVinci stays winner at lib 0; EB excluded)
    _, _, failed_keep = wm.import_eb_project(
        eb_root,
        mode="copy",
        into_project=project,
        on_conflict="keep",
        confirm=lambda *_: True,
    )
    assert failed_keep == []
    assert project.module_entries["Dio"].library == 0
    assert "Dio_THA6_AS440" in project.module_libraries[1].exclude

    # Step 3: Re-merge EB with replace (EB becomes winner at lib 1; un-excluded in lib 1, DaVinci excluded in lib 0)
    _, _, failed_eb_rep = wm.import_eb_project(
        eb_root,
        mode="copy",
        into_project=project,
        on_conflict="replace",
        confirm=lambda *_: True,
    )
    assert failed_eb_rep == []
    assert project.module_entries["Dio"].library == 1
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True
    assert "Dio_THA6_AS440" not in project.module_libraries[1].exclude
    assert "Dio" in project.module_libraries[0].exclude

    reloaded1, rf1 = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert rf1 == []
    assert reloaded1.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True

    # Step 4: Re-merge DaVinci with replace (DaVinci becomes winner at lib 0; un-excluded in lib 0, EB excluded in lib 1)
    _, dv_rep = wm.import_davinci_project(
        dpa_path=dpa_file,
        into_project=reloaded1,
        on_conflict="replace",
        confirm=lambda *_: True,
    )
    assert dv_rep.failed_modules == []
    assert reloaded1.module_entries["Dio"].library == 0
    assert reloaded1.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False
    assert "Dio" not in reloaded1.module_libraries[0].exclude
    assert "Dio_THA6_AS440" in reloaded1.module_libraries[1].exclude

    reloaded2, rf2 = WorkspaceManager().load_project(reloaded1.path, confirm=lambda *_: True)
    assert rf2 == []
    assert reloaded2.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False


def test_merge_eb_replace_failure_restores_existing_davinci_module(tmp_path):
    """If replacing an existing DaVinci module with a broken EB plugin fails, restore DaVinci module & files."""
    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    out_parent = tmp_path / "replace_fail_out"

    wm = WorkspaceManager()
    project, _ = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=out_parent,
        project_name="ReplaceFailRollback",
        confirm=lambda *_: True,
    )
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False
    before_dio_cfg = (project.path.parent / "config" / "Dio.arxml").read_bytes()

    # Corrupt EB Dio.xdm after plugin scanning still finds plugin.xml
    (eb_root / "Def" / "plugins" / "Dio_THA6_AS440" / "config" / "Dio.xdm").write_text(
        "<broken-xml", encoding="utf-8"
    )

    _, _, failed = wm.import_eb_project(
        eb_root,
        mode="copy",
        into_project=project,
        on_conflict="replace",
        confirm=lambda *_: True,
    )
    assert any(name == "Dio" for name, _ in failed)
    assert project.module_entries["Dio"].library == 0
    assert project.module_provenance["Dio"]["origin"] == "davinci-import"
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False
    assert (project.path.parent / "config" / "Dio.arxml").read_bytes() == before_dio_cfg

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    assert reloaded.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is False


def test_import_davinci_report_checks_pre_inconsistencies_versions_and_values(tmp_path):
    """W12: report tracks Active-vs-Pre overrides, BswImplSwVersion mismatches, and zero unexpected value diffs."""
    dpa_file, eb_root = _create_sample_sip_and_davinci(tmp_path)

    # Inject Pre disagreement on OsCoreCount (Active=2 in ECUC, Pre=4) -> PRE_FORCED when accepted
    pre_file = tmp_path / "sip" / "Components" / "Os" / "BSWMD" / "Os" / "THA6206_Sub" / "Os_THA_pre.arxml"
    pre_file.write_text(
        pre_file.read_text(encoding="utf-8").replace("<VALUE>2</VALUE>", "<VALUE>4</VALUE>"),
        encoding="utf-8",
    )

    # Add BswImplVersionPersistor to .dpa: Os matches normalized (2.10.0 vs 2.10.00), Com mismatches
    com_bswmd = tmp_path / "sip" / "Components" / "Com" / "BSWMD" / "Com_bswmd.arxml"
    com_bswmd.write_text(
        com_bswmd.read_text(encoding="utf-8").replace(
            "</ECUC-MODULE-DEF>",
            "</ECUC-MODULE-DEF>\n    <BSW-IMPLEMENTATION><SHORT-NAME>Com_Impl</SHORT-NAME><SW-VERSION>3.01.00</SW-VERSION></BSW-IMPLEMENTATION>",
        ),
        encoding="utf-8",
    )
    dpa_text = dpa_file.read_text(encoding="utf-8").replace(
        "</ProjectAssistant>",
        """  <ToolSettings>
    <Settings Name="Misc">
      <Settings Name="com.vector.cfg.gen.core.bswmdmigration.internal.service.BswImplVersionPersistor">
        <Settings Name="|MICROSAR|Os">
          <Setting Name="BswImplSwVersion" Value="2.10.0"/>
        </Settings>
        <Settings Name="|MICROSAR|Com">
          <Setting Name="BswImplSwVersion" Value="2.0.0"/>
        </Settings>
      </Settings>
    </Settings>
  </ToolSettings>
</ProjectAssistant>""",
    )
    dpa_file.write_text(dpa_text, encoding="utf-8")

    wm = WorkspaceManager()
    project, report = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=tmp_path / "checked_out",
        project_name="CheckedImport",
        mcal_source_dir=eb_root,
        confirm=lambda *_: True,
    )

    # 1. Active vs Pre inconsistency captured for OsCoreCount (2 -> 4)
    assert any(
        item["module"] == "Os" and "OsCoreCount" in item["key"]
        and item["active"] == 2 and item["pre"] == 4
        for item in report.pre_inconsistencies
    )

    # 2. Normalized Os version (2.10.0 == 2.10.00) does NOT flag mismatch, whereas Com (2.0.0 != 3.01.00) DOES
    assert all(m["module"] != "Os" for m in report.version_mismatches)
    assert any(
        m["module"] == "Com" and m["dpa_version"] == "2.0.0" and m["package_version"] == "3.01.00"
        for m in report.version_mismatches
    )

    # 3. Value diffs are empty (the expected PRE_FORCED override is excluded from loss/drift diffs)
    assert report.value_diffs == []

    # 4. Markdown report renders all verification sections at timestamped history path
    checked_root = tmp_path / "checked_out" / "CheckedImport"
    assert not (checked_root / ".import_report.md").exists()
    (report_path,) = sorted((checked_root / ".history" / "reports").glob("*_davinci_import.md"))
    md = report_path.read_text(encoding="utf-8")
    assert "Active 与 Pre 不一致项" in md
    assert "OsCoreCount" in md
    assert "BswImplSwVersion 版本不一致" in md
    assert "3.01.00" in md


def test_compare_module_values_detects_missing_and_mismatched_and_normalizes_booleans():
    from autosar_configurator.core.davinci_importer import compare_module_values
    from autosar_configurator.core.model.configuration_model import (
        EcucContainerValue,
        EcucModuleConfiguration,
        EcucParameterValue,
    )

    src = EcucModuleConfiguration(short_name="Mod", definition_ref="/V/Mod")
    src_c = EcucContainerValue(short_name="Gen", definition_ref="/V/Mod/Gen", module_name="Mod")
    src_c.parameter_values["Flag"] = EcucParameterValue("/V/Mod/Gen/Flag", "true")
    src_c.parameter_values["Rate"] = EcucParameterValue("/V/Mod/Gen/Rate", 100)
    src_c.parameter_values["MissingKey"] = EcucParameterValue("/V/Mod/Gen/MissingKey", "abc")
    src_c.parameter_values["PreKey"] = EcucParameterValue("/V/Mod/Gen/PreKey", "from_src")
    src.add_container(src_c)

    dst = EcucModuleConfiguration(short_name="Mod", definition_ref="/V/Mod")
    dst_c = EcucContainerValue(short_name="Gen", definition_ref="/V/Mod/Gen", module_name="Mod")
    dst_c.parameter_values["Flag"] = EcucParameterValue("/V/Mod/Gen/Flag", True)  # normalized equal
    dst_c.parameter_values["Rate"] = EcucParameterValue("/V/Mod/Gen/Rate", 200)   # diff
    dst_c.parameter_values["PreKey"] = EcucParameterValue("/V/Mod/Gen/PreKey", "from_pre")  # expected_pre_keys
    dst.add_container(dst_c)

    diffs = compare_module_values(src, dst, "Mod", expected_pre_keys={"P:/Mod/Gen.PreKey"})
    by_key = {d["key"]: d for d in diffs}
    assert "P:/Mod/Gen.Flag" not in by_key
    assert "P:/Mod/Gen.PreKey" not in by_key
    assert by_key["P:/Mod/Gen.Rate"]["kind"] == "different"
    assert by_key["P:/Mod/Gen.Rate"]["source"] == 100
    assert by_key["P:/Mod/Gen.Rate"]["imported"] == 200
    assert by_key["P:/Mod/Gen.MissingKey"]["kind"] == "missing"


def test_legacy_davinci_import_and_root_modules_v8_project_still_load(tmp_path):
    """Pre-partition Format 8 projects referencing DaVinciImport/, def/, sources.json, and root modules/ still load."""
    proj_dir = tmp_path / "LegacyV8"
    (proj_dir / "config").mkdir(parents=True)

    # Legacy DaVinciImport/Os package with def/ + sources.json
    os_pkg = proj_dir / "DaVinciImport" / "Os"
    (os_pkg / "def").mkdir(parents=True)
    os_def = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>Os</SHORT-NAME></ECUC-MODULE-DEF>
    <BSW-IMPLEMENTATION><SHORT-NAME>Os_Impl</SHORT-NAME><SW-VERSION>1.0.0</SW-VERSION></BSW-IMPLEMENTATION>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    (os_pkg / "def" / "Os.arxml").write_text(os_def, encoding="utf-8")
    (os_pkg / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "Os",
        "definition": "/MICROSAR/Os",
        "files": ["def/Os.arxml"],
    }), encoding="utf-8")
    (os_pkg / "sources.json").write_text(json.dumps({
        "module": "Os",
        "implementation": {"ar_path": "/MICROSAR/Os_Impl", "sw_version": "1.0.0"},
    }), encoding="utf-8")
    (proj_dir / "config" / "Os.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Os</DEFINITION-REF>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # Legacy EB plugin copied directly into modules/<Plugin>
    dio_plugin = proj_dir / "modules" / "Dio_TS_T40D11M7I0R0"
    (dio_plugin / "config").mkdir(parents=True)
    (dio_plugin / "plugin.xml").write_text(
        '<?xml version="1.0" encoding="UTF-8"?>\n'
        '<plugin>\n'
        '  <extension point="dreisoft.tresos.launcher2.plugin.module" id="Dio_TS" name="Dio_TS">\n'
        '    <module id="Dio_TS" label="Dio" swVersionMajor="1" swVersionMinor="0" swVersionPatch="0"/>\n'
        '  </extension>\n'
        '  <extension point="dreisoft.tresos.launcher2.plugin.configuration" id="Dio_Config">\n'
        '    <configuration moduleId="Dio_TS">\n'
        '      <schema><resource type="xdm" value="config/Dio.xdm"/></schema>\n'
        '      <data><schemaNode path="ASPath:/THA6_AS440_FuSa/Dio"/></data>\n'
        '    </configuration>\n'
        '  </extension>\n'
        '</plugin>\n',
        encoding="utf-8",
    )
    (dio_plugin / "config" / "Dio.xdm").write_text("""<?xml version="1.0"?>
<datamodel version="7.0"
           xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
           xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="THA6_AS440_FuSa" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Dio" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF"/>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>""", encoding="utf-8")
    (proj_dir / "config" / "Dio.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Dio</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Dio</DEFINITION-REF>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    dpa = proj_dir / "LegacyV8.dpa"
    dpa.write_text(json.dumps({
        "format_version": 8,
        "name": "LegacyV8",
        "project_type": "Vector DaVinci",
        "module_libraries": [
            {"path": "DaVinciImport", "kind": "package", "exclude": []},
            {"path": "modules", "kind": "eb-plugins", "exclude": []},
        ],
        "modules": [
            {"name": "Os", "definition": "/MICROSAR/Os", "library": 0, "config_path": "config/Os.arxml"},
            {"name": "Dio", "definition": "/THA6_AS440_FuSa/Dio", "library": 1, "config_path": "config/Dio.arxml"},
        ],
    }), encoding="utf-8")

    loaded, failed = WorkspaceManager().load_project(dpa)
    assert failed == []
    assert set(loaded.module_managers.keys()) == {"Os", "Dio"}
    assert loaded.packages["Os"].read_impl_metadata()["sw_version"] == "1.0.0"
    assert loaded.module_defs["Os"] == os_pkg / "def" / "Os.arxml"
    assert loaded.module_defs["Dio"] == dio_plugin / "config" / "Dio.xdm"


def test_dpa_parser_infers_missing_definition_ref_from_split_ecuc(tmp_path):
    """DaVinciProject.from_file infers DEFINITION-REF from split ECUC files when omitted from ModuleDefinitionMappings."""
    from autosar_configurator.core.davinci_importer import DaVinciProject

    dpa_file, eb_root = _create_overlapping_sip_and_eb(tmp_path)
    app_dir = dpa_file.parent
    ecuc_dir = app_dir / "Config" / "ECUC"

    # Build a synthetic .dpa with Can & Resource missing from ModuleDefinitionMappings
    (ecuc_dir / "App_Can_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Can</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Can</DEFINITION-REF>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (ecuc_dir / "App_Resource_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Resource</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Resource</DEFINITION-REF>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (ecuc_dir / "App.ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-VALUE-COLLECTION><SHORT-NAME>ActiveEcuC</SHORT-NAME><ECUC-VALUES>
      <ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
        <ECUC-MODULE-CONFIGURATION-VALUES-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/ActiveEcuC/Os</ECUC-MODULE-CONFIGURATION-VALUES-REF>
      </ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
      <ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
        <ECUC-MODULE-CONFIGURATION-VALUES-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/ActiveEcuC/Can</ECUC-MODULE-CONFIGURATION-VALUES-REF>
      </ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
      <ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
        <ECUC-MODULE-CONFIGURATION-VALUES-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/ActiveEcuC/Resource</ECUC-MODULE-CONFIGURATION-VALUES-REF>
      </ECUC-MODULE-CONFIGURATION-VALUES-REF-CONDITIONAL>
    </ECUC-VALUES></ECUC-VALUE-COLLECTION>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # Test Case A: explicit .dpa parsing infers /THA6_AS440_FuSa/Can & /THA6_AS440_FuSa/Resource
    dpa_missing_map = app_dir / "MissingMaps.dpa"
    dpa_missing_map.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<ProjectAssistant Version="5.30.35 SP2">
  <Folders><SIP>.\\..\\..</SIP></Folders>
  <Display>
    <ModuleDefinitionMappings>
      <ModuleDefinitionMapping ModuleConfigName="Os" ModuleDefinitionRef="/MICROSAR/Os"/>
    </ModuleDefinitionMappings>
  </Display>
  <EcucSplitter>
    <Configuration>.\\Config\\ECUC\\App.ecuc.arxml</Configuration>
    <Splitter File=".\\Config\\ECUC\\MyApp_Os_ecuc.arxml"><Module Name="Os"/></Splitter>
    <Splitter File=".\\Config\\ECUC\\App_Can_ecuc.arxml"><Module Name="Can"/></Splitter>
    <Splitter File=".\\Config\\ECUC\\App_Resource_ecuc.arxml"><Module Name="Resource"/></Splitter>
  </EcucSplitter>
</ProjectAssistant>""", encoding="utf-8")

    dv = DaVinciProject.from_file(dpa_missing_map)
    assert dv.module_definitions["Can"] == "/THA6_AS440_FuSa/Can"
    assert dv.module_definitions["Resource"] == "/THA6_AS440_FuSa/Resource"
    assert "Can" in dv.mcal_modules()
    assert "Resource" in dv.mcal_modules()

    # Test Case B: strip Dio from ModuleDefinitionMappings of MyApp.dpa and merge into EB project
    dpa_text = dpa_file.read_text(encoding="utf-8").replace(
        '<ModuleDefinitionMapping ModuleConfigName="Dio" ModuleDefinitionRef="/THA6_AS440_FuSa/Dio"/>',
        "",
    )
    dpa_file.write_text(dpa_text, encoding="utf-8")
    dv2 = DaVinciProject.from_file(dpa_file)
    assert dv2.module_definitions["Dio"] == "/THA6_AS440_FuSa/Dio"
    assert "Dio" in dv2.mcal_modules()

    wm = WorkspaceManager()
    project, _, failed = wm.import_eb_project(
        eb_root, target_dir=tmp_path / "EbForMissingMap", mode="copy", confirm=lambda *_: True
    )
    assert failed == []
    _, dv_report = wm.import_davinci_project(
        dpa_path=dpa_file, into_project=project, on_conflict="auto", confirm=lambda *_: True
    )
    assert dv_report.failed_modules == []
    assert any(item["module"] == "Dio" for item in dv_report.skipped_mcal_modules)


def _create_sip_and_eb_with_ecuc_stub(root: Path):
    """Extend _create_overlapping_sip_and_eb with:
    - SIP /MICROSAR/EcuC (with EcucPduCollection/Pdu_0) & /MICROSAR/CanIf referencing it
    - EB empty stub plugin Ecuc_THA6_AS440 (0 containers, no EcuC.epc, no Pre/Rec).
    """
    dpa_file, eb_root = _create_overlapping_sip_and_eb(root)
    sip = root / "sip"
    app_dir = dpa_file.parent
    ecuc_dir = app_dir / "Config" / "ECUC"

    # SIP EcuC definition
    ecuc_bswmd = sip / "Components" / "EcuC" / "BSWMD"
    ecuc_bswmd.mkdir(parents=True)
    (ecuc_bswmd / "EcuC_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>EcuC</SHORT-NAME>
      <CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF>
        <SHORT-NAME>EcucPduCollection</SHORT-NAME>
        <SUB-CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>Pdu</SHORT-NAME>
          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
          <PARAMETERS><ECUC-INTEGER-PARAM-DEF><SHORT-NAME>PduLength</SHORT-NAME></ECUC-INTEGER-PARAM-DEF></PARAMETERS>
        </ECUC-PARAM-CONF-CONTAINER-DEF></SUB-CONTAINERS>
      </ECUC-PARAM-CONF-CONTAINER-DEF></CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # SIP CanIf definition referencing EcuC Pdu
    canif_bswmd = sip / "Components" / "CanIf" / "BSWMD"
    canif_bswmd.mkdir(parents=True)
    (canif_bswmd / "CanIf_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>CanIf</SHORT-NAME>
      <CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF>
        <SHORT-NAME>CanIfTxPduCfg</SHORT-NAME>
        <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
        <REFERENCES><ECUC-REFERENCE-DEF>
          <SHORT-NAME>CanIfTxPduRef</SHORT-NAME>
          <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucPduCollection/Pdu</DESTINATION-REF>
        </ECUC-REFERENCE-DEF></REFERENCES>
      </ECUC-PARAM-CONF-CONTAINER-DEF></CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # DaVinci ECUC for EcuC and CanIf
    (ecuc_dir / "MyApp_EcuC_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>EcuC</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuC</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>EcucPduCollection</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucPduCollection</DEFINITION-REF>
        <SUB-CONTAINERS><ECUC-CONTAINER-VALUE>
          <SHORT-NAME>Pdu_0</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucPduCollection/Pdu</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/EcuC/EcucPduCollection/Pdu/PduLength</DEFINITION-REF>
            <VALUE>8</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE></SUB-CONTAINERS>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    (ecuc_dir / "MyApp_CanIf_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanIf</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanIf</DEFINITION-REF>
      <CONTAINERS><ECUC-CONTAINER-VALUE>
        <SHORT-NAME>CanIfTxPduCfg_0</SHORT-NAME>
        <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanIf/CanIfTxPduCfg</DEFINITION-REF>
        <REFERENCE-VALUES><ECUC-REFERENCE-VALUE>
          <DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/MICROSAR/CanIf/CanIfTxPduCfg/CanIfTxPduRef</DEFINITION-REF>
          <VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuC/EcucPduCollection/Pdu_0</VALUE-REF>
        </ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
      </ECUC-CONTAINER-VALUE></CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    dpa_text = dpa_file.read_text(encoding="utf-8")
    dpa_text = dpa_text.replace(
        "</ModuleDefinitionMappings>",
        '      <ModuleDefinitionMapping ModuleConfigName="EcuC" ModuleDefinitionRef="/MICROSAR/EcuC"/>\n'
        '      <ModuleDefinitionMapping ModuleConfigName="CanIf" ModuleDefinitionRef="/MICROSAR/CanIf"/>\n'
        "    </ModuleDefinitionMappings>",
    ).replace(
        "</EcucSplitter>",
        '    <Splitter File=".\\Config\\ECUC\\MyApp_EcuC_ecuc.arxml"><Module Name="EcuC"/></Splitter>\n'
        '    <Splitter File=".\\Config\\ECUC\\MyApp_CanIf_ecuc.arxml"><Module Name="CanIf"/></Splitter>\n'
        "  </EcucSplitter>",
    )
    dpa_file.write_text(dpa_text, encoding="utf-8")

    # EB empty stub plugin: Ecuc_THA6_AS440 (no EcuC.epc, optional containers -> 0 containers created)
    ecuc_plugin = eb_root / "Def" / "plugins" / "Ecuc_THA6_AS440"
    (ecuc_plugin / "config").mkdir(parents=True)
    (ecuc_plugin / "plugin.xml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<plugin>
  <extension point="dreisoft.tresos.launcher2.plugin.module" id="Ecuc_THA6_AS440" name="Ecuc_THA6_AS440">
    <module id="Ecuc_THA6_AS440" label="EcuC" mandatory="false" allowMultiple="false"
            swVersionMajor="1" swVersionMinor="0" swVersionPatch="0"
            specVersionMajor="4" specVersionMinor="4" specVersionPatch="0"/>
  </extension>
  <extension point="dreisoft.tresos.launcher2.plugin.configuration" id="Ecuc_Config">
    <configuration moduleId="Ecuc_THA6_AS440">
      <schema><resource type="xdm" value="config/EcuC.xdm"/></schema>
      <data><schemaNode path="ASPath:/THA6_AS440_FuSa/EcuC"/></data>
    </configuration>
  </extension>
</plugin>""", encoding="utf-8")
    (ecuc_plugin / "config" / "EcuC.xdm").write_text("""<?xml version="1.0"?>
<datamodel version="7.0"
           xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
           xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
           xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
           xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="THA6_AS440_FuSa" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="EcuC" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF"/>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>""", encoding="utf-8")

    return dpa_file, eb_root


def test_merge_davinci_replaces_empty_eb_ecuc_stub_in_auto_mode(tmp_path):
    """Order 2 (EB -> DaVinci, on_conflict='auto'): empty EB EcuC stub is replaced by DaVinci /MICROSAR/EcuC."""
    dpa_file, eb_root = _create_sip_and_eb_with_ecuc_stub(tmp_path)

    wm = WorkspaceManager()
    project, _, failed = wm.import_eb_project(
        eb_root, target_dir=tmp_path / "EbWithStub", mode="copy", confirm=lambda *_: True
    )
    assert failed == []
    assert len(project.module_managers["EcuC"].configuration.containers) == 0

    _, dv_report = wm.import_davinci_project(
        dpa_path=dpa_file, into_project=project, on_conflict="auto", confirm=lambda *_: True
    )
    assert dv_report.failed_modules == []
    assert dv_report.unresolved_references == []
    assert project.module_entries["Dio"].library == 0
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True
    assert project.module_entries["EcuC"].library == 1
    assert project.module_entries["EcuC"].definition == "/MICROSAR/EcuC"
    assert "EcucPduCollection" in [c.short_name for c in project.module_managers["EcuC"].configuration.containers]
    assert project.module_managers["CanIf"].configuration.containers[0].reference_values["CanIfTxPduRef"].is_resolved is True

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    assert "EcucPduCollection" in [c.short_name for c in reloaded.module_managers["EcuC"].configuration.containers]
    assert reloaded.module_managers["CanIf"].configuration.containers[0].reference_values["CanIfTxPduRef"].is_resolved is True


def test_merge_eb_empty_ecuc_stub_does_not_clobber_davinci_ecuc(tmp_path):
    """Order 1 (DaVinci -> EB, on_conflict='replace'): empty EB EcuC stub without EPC must not overwrite DaVinci EcuC."""
    dpa_file, eb_root = _create_sip_and_eb_with_ecuc_stub(tmp_path)

    wm = WorkspaceManager()
    project, dv_report = wm.import_davinci_project(
        dpa_path=dpa_file, target_dir=tmp_path / "DvWithEcuc", project_name="DvEcuc", confirm=lambda *_: True
    )
    assert dv_report.failed_modules == []

    _, loaded, failed = wm.import_eb_project(
        eb_root, mode="copy", into_project=project, on_conflict="replace", confirm=lambda *_: True
    )
    assert failed == []
    assert "Dio" in loaded
    assert project.module_managers["Dio"].configuration.containers[0].parameter_values["DioDevErrorDetect"].value is True
    assert project.module_entries["EcuC"].library == 0
    assert "EcucPduCollection" in [c.short_name for c in project.module_managers["EcuC"].configuration.containers]
    assert project.module_managers["CanIf"].configuration.containers[0].reference_values["CanIfTxPduRef"].is_resolved is True

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    assert "EcucPduCollection" in [c.short_name for c in reloaded.module_managers["EcuC"].configuration.containers]
    assert reloaded.module_managers["CanIf"].configuration.containers[0].reference_values["CanIfTxPduRef"].is_resolved is True


def test_sip_multi_variant_module_selects_matching_definition_by_dpa(tmp_path):
    """Multi-variant SIP module (CanTrcv_GenericCan vs CanTrcv_Tle9255) is partitioned by def path
    and .dpa binds to the exact variant definition so ValidationEngine finds 0 errors/warnings."""
    from autosar_configurator.core.validation_engine import ValidationEngine

    dpa_file, _ = _create_sample_sip_and_davinci(tmp_path)
    sip = tmp_path / "sip"

    # GenericCan variant (earlier alphabetically): has required CanTrcvHwInterface, lacks CanTrcvBaudrateRatio
    gen_bswmd = sip / "Components" / "CanTrcv_30_Generic" / "BSWMD"
    gen_bswmd.mkdir(parents=True)
    (gen_bswmd / "CanTrcv_30_Generic_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_GenericCan</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            <PARAMETERS><ECUC-STRING-PARAM-DEF>
              <SHORT-NAME>CanTrcvHwInterface</SHORT-NAME>
              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            </ECUC-STRING-PARAM-DEF></PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # Tle9255 variant: has CanTrcvBaudrateRatio on CanTrcvChannel, does NOT have CanTrcvHwInterface
    tle_bswmd = sip / "Components" / "CanTrcv_30_Tle9255" / "BSWMD"
    tle_bswmd.mkdir(parents=True)
    (tle_bswmd / "CanTrcv_Tle9255CanAsr_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            <PARAMETERS><ECUC-BOOLEAN-PARAM-DEF>
              <SHORT-NAME>CanTrcvDevErrorDetect</SHORT-NAME>
              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            </ECUC-BOOLEAN-PARAM-DEF></PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvChannel</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
            <PARAMETERS><ECUC-INTEGER-PARAM-DEF>
              <SHORT-NAME>CanTrcvBaudrateRatio</SHORT-NAME>
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            </ECUC-INTEGER-PARAM-DEF></PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    # Add CanTrcv ECUC targeting /MICROSAR/CanTrcv_Tle9255/CanTrcv
    ecuc_dir = dpa_file.parent / "Config" / "ECUC"
    (ecuc_dir / "MyApp_CanTrcv_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvDevErrorDetect</DEFINITION-REF>
            <VALUE>true</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvChannel_0</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvChannel</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvChannel/CanTrcvBaudrateRatio</DEFINITION-REF>
            <VALUE>10</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    dpa_text = dpa_file.read_text(encoding="utf-8")
    dpa_text = dpa_text.replace(
        "</ModuleDefinitionMappings>",
        '      <ModuleDefinitionMapping ModuleConfigName="CanTrcv" ModuleDefinitionRef="/MICROSAR/CanTrcv_Tle9255/CanTrcv"/>\n'
        "    </ModuleDefinitionMappings>",
    ).replace(
        "</EcucSplitter>",
        '    <Splitter File=".\\Config\\ECUC\\MyApp_CanTrcv_ecuc.arxml"><Module Name="CanTrcv"/></Splitter>\n'
        "  </EcucSplitter>",
    )
    dpa_file.write_text(dpa_text, encoding="utf-8")

    wm = WorkspaceManager()
    project, dv_report = wm.import_davinci_project(
        dpa_path=dpa_file,
        target_dir=tmp_path / "can_trcv_out",
        project_name="CanTrcvVariantApp",
        confirm=lambda *_: True,
    )
    assert dv_report.failed_modules == []
    dv_lib = tmp_path / "can_trcv_out" / "CanTrcvVariantApp" / "modules" / "davinci"
    assert (dv_lib / "CanTrcv_GenericCan" / "module.json").is_file()
    assert (dv_lib / "CanTrcv_Tle9255" / "module.json").is_file()
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"

    cantrcv_mgr = project.module_managers["CanTrcv"]
    engine = ValidationEngine(cantrcv_mgr.module_def, cantrcv_mgr.configuration, project)
    engine.register_default_rules()
    val_res = engine.validate()
    assert val_res.error_count == 0
    assert val_res.warning_count == 0

    reloaded, reload_failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    rel_mgr = reloaded.module_managers["CanTrcv"]
    rel_engine = ValidationEngine(rel_mgr.module_def, rel_mgr.configuration, reloaded)
    rel_engine.register_default_rules()
    rel_res = rel_engine.validate()
    assert rel_res.error_count == 0
    assert rel_res.warning_count == 0


def test_sip_package_writer_detects_and_preserves_templates_dir(tmp_path):
    """SipPackageWriter records 'templates' when present on disk and preserves custom templates."""
    from autosar_configurator.core.davinci_importer import SipPackageWriter

    # 1. Existing templates/ directory is recorded in module.json
    pkg_dir = tmp_path / "packages" / "BswM"
    (pkg_dir / "templates" / "include").mkdir(parents=True)
    (pkg_dir / "templates" / "include" / "BswM_Cfg.h").write_text("// tpl", encoding="utf-8")

    SipPackageWriter.write_package(
        module_name="BswM",
        definition_content=b'<?xml version="1.0"?><AUTOSAR><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS><ECUC-MODULE-DEF><SHORT-NAME>BswM</SHORT-NAME></ECUC-MODULE-DEF></ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>',
        output_dir=tmp_path / "packages",
    )
    manifest = json.loads((pkg_dir / "module.json").read_text(encoding="utf-8"))
    assert manifest.get("templates") == "templates"

    # 2. Custom templates directory recorded in previous module.json is preserved across rewrites
    custom_pkg = tmp_path / "packages" / "CustomTpl"
    (custom_pkg / "generate_PB").mkdir(parents=True)
    (custom_pkg / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "CustomTpl",
        "definition": "/MICROSAR/CustomTpl",
        "files": [],
        "templates": "generate_PB",
    }), encoding="utf-8")

    SipPackageWriter.write_package(
        module_name="CustomTpl",
        definition_content=b'<?xml version="1.0"?><AUTOSAR><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS><ECUC-MODULE-DEF><SHORT-NAME>CustomTpl</SHORT-NAME></ECUC-MODULE-DEF></ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>',
        output_dir=tmp_path / "packages",
    )
    custom_manifest = json.loads((custom_pkg / "module.json").read_text(encoding="utf-8"))
    assert custom_manifest.get("templates") == "generate_PB"


def test_sip_infixed_memmap_bsw_implementation_attributed_to_variant(tmp_path):
    """Infixed BSW-IMPLEMENTATION MemMap files belong to their VENDOR-SPECIFIC-MODULE-DEF-REF
    variant partition, and unmatched fragments are never broadcast across all variants."""
    from autosar_configurator.core.davinci_importer import SipMerger, SipScanner

    sip = tmp_path / "sip"

    gen_bswmd = sip / "Components" / "CanTrcv_30_Generic" / "BSWMD"
    gen_bswmd.mkdir(parents=True)
    (gen_bswmd / "CanTrcv_30_Generic_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_GenericCan</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF><SHORT-NAME>CanTrcv</SHORT-NAME></ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    tle_bswmd = sip / "Components" / "CanTrcv_30_Tle9255" / "BSWMD"
    tle_bswmd.mkdir(parents=True)
    (tle_bswmd / "CanTrcv_Tle9255CanAsr_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF><SHORT-NAME>CanTrcv</SHORT-NAME></ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (tle_bswmd / "CanTrcv_30_Tle9255_MemMap.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <BSW-IMPLEMENTATION>
        <SHORT-NAME>CanTrcv_30_Tle9255_Impl</SHORT-NAME>
        <VENDOR-SPECIFIC-MODULE-DEF-REFS>
          <VENDOR-SPECIFIC-MODULE-DEF-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv</VENDOR-SPECIFIC-MODULE-DEF-REF>
        </VENDOR-SPECIFIC-MODULE-DEF-REFS>
        <RESOURCE-CONSUMPTION>
          <MEMORY-SECTIONS>
            <MEMORY-SECTION><SHORT-NAME>CANTRCV_30_TLE9255_CODE</SHORT-NAME></MEMORY-SECTION>
          </MEMORY-SECTIONS>
        </RESOURCE-CONSUMPTION>
      </BSW-IMPLEMENTATION>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    other_bswmd = sip / "Components" / "CanTrcv_30_Other" / "BSWMD"
    other_bswmd.mkdir(parents=True)
    (other_bswmd / "CanTrcv_Other_pre.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv_Other_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Other/CanTrcv</DEFINITION-REF>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    all_modules = SipScanner(sip).scan_all_modules()
    assert "CanTrcv_30_Tle9255" not in all_modules
    assert "CanTrcv" in all_modules

    partitions = SipScanner.partition_module_files("CanTrcv", all_modules["CanTrcv"])
    by_dir = {pkg_dir: files for pkg_dir, _mod, files in partitions}
    assert "CanTrcv_GenericCan" in by_dir
    assert "CanTrcv_Tle9255" in by_dir

    gen_names = {f.path.name for f in by_dir["CanTrcv_GenericCan"]}
    tle_names = {f.path.name for f in by_dir["CanTrcv_Tle9255"]}

    assert "CanTrcv_30_Tle9255_MemMap.arxml" in tle_names
    assert "CanTrcv_30_Tle9255_MemMap.arxml" not in gen_names
    assert "CanTrcv_Other_pre.arxml" not in gen_names
    assert "CanTrcv_Other_pre.arxml" not in tle_names

    impl_meta = SipMerger.extract_bsw_implementation_metadata(by_dir["CanTrcv_Tle9255"])
    sec_names = {s["short_name"] for s in impl_meta.get("memory_sections", [])}
    assert "CANTRCV_30_TLE9255_CODE" in sec_names


def test_extract_and_load_single_file_with_two_variant_blocks(tmp_path):
    """When one ARXML holds two sibling variant blocks, exact DEFINITION-REF selects only the matching one."""
    from autosar_configurator.core.config_manager import ConfigurationManager
    from autosar_configurator.core.davinci_importer import DaVinciProjectImporter
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

    def_arxml = tmp_path / "CanTrcv_Tle9255_bswmd.arxml"
    def_arxml.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <PARAMETERS><ECUC-BOOLEAN-PARAM-DEF><SHORT-NAME>CanTrcvDevErrorDetect</SHORT-NAME></ECUC-BOOLEAN-PARAM-DEF></PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvChannel</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
            <PARAMETERS><ECUC-INTEGER-PARAM-DEF><SHORT-NAME>CanTrcvBaudrateRatio</SHORT-NAME></ECUC-INTEGER-PARAM-DEF></PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    tle_def = EcucDefParser().parse_module_def_file(def_arxml)

    multi_cfg = tmp_path / "MultiVariant_CanTrcv.arxml"
    multi_cfg.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral/CanTrcvHwInterface</DEFINITION-REF>
            <VALUE>SPI</VALUE>
          </ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvDevErrorDetect</DEFINITION-REF>
            <VALUE>true</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvChannel_0</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvChannel</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvChannel/CanTrcvBaudrateRatio</DEFINITION-REF>
            <VALUE>10</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    extracted = DaVinciProjectImporter._extract_module_config(
        multi_cfg, "CanTrcv", "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    )
    assert extracted is not None
    assert extracted.definition_ref == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    gen_c = next(c for c in extracted.containers if c.short_name == "CanTrcvGeneral")
    assert "CanTrcvHwInterface" not in gen_c.parameter_values
    assert gen_c.parameter_values["CanTrcvDevErrorDetect"].value is True

    mgr = ConfigurationManager(tle_def)
    mgr.load_configuration(multi_cfg)
    assert mgr.configuration.definition_ref == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    loaded_gen = next(c for c in mgr.configuration.containers if c.short_name == "CanTrcvGeneral")
    assert "CanTrcvHwInterface" not in loaded_gen.parameter_values
    assert loaded_gen.parameter_values["CanTrcvDevErrorDetect"].value is True


def _setup_cantrcv_variant_project(tmp_path: Path):
    """Create a saved Format 8 project whose modules/ library contains CanTrcv_GenericCan and CanTrcv_Tle9255."""
    from autosar_configurator.core.packages.library import LibraryRef, scan_library

    proj_dir = tmp_path / "VariantProj"
    mods_dir = proj_dir / "modules"

    gen_dir = mods_dir / "CanTrcv_GenericCan" / "config"
    gen_dir.mkdir(parents=True)
    (gen_dir / "CanTrcv.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_GenericCan</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            <PARAMETERS>
              <ECUC-STRING-PARAM-DEF>
                <SHORT-NAME>CanTrcvHwInterface</SHORT-NAME>
                <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              </ECUC-STRING-PARAM-DEF>
              <ECUC-BOOLEAN-PARAM-DEF>
                <SHORT-NAME>CanTrcvDevErrorDetect</SHORT-NAME>
                <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              </ECUC-BOOLEAN-PARAM-DEF>
              <ECUC-BOOLEAN-PARAM-DEF>
                <SHORT-NAME>CanTrcvPreFlag</SHORT-NAME>
                <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              </ECUC-BOOLEAN-PARAM-DEF>
            </PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (gen_dir / "CanTrcv_Pre.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv_GenericCan_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE>
            <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral/CanTrcvPreFlag</DEFINITION-REF>
            <VALUE>true</VALUE>
          </ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (mods_dir / "CanTrcv_GenericCan" / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "CanTrcv",
        "definition": "/MICROSAR/CanTrcv_GenericCan/CanTrcv",
        "files": ["config/CanTrcv.arxml", "config/CanTrcv_Pre.arxml"],
        "pre": ["/MICROSAR/CanTrcv_GenericCan_Pre"],
        "rec": [],
    }), encoding="utf-8")

    tle_dir = mods_dir / "CanTrcv_Tle9255" / "config"
    tle_dir.mkdir(parents=True)
    (tle_dir / "CanTrcv.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            <PARAMETERS><ECUC-BOOLEAN-PARAM-DEF>
              <SHORT-NAME>CanTrcvDevErrorDetect</SHORT-NAME>
              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            </ECUC-BOOLEAN-PARAM-DEF></PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvChannel</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
            <PARAMETERS><ECUC-INTEGER-PARAM-DEF>
              <SHORT-NAME>CanTrcvBaudrateRatio</SHORT-NAME>
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            </ECUC-INTEGER-PARAM-DEF></PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (mods_dir / "CanTrcv_Tle9255" / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "CanTrcv",
        "definition": "/MICROSAR/CanTrcv_Tle9255/CanTrcv",
        "files": ["config/CanTrcv.arxml"],
        "pre": [],
        "rec": [],
    }), encoding="utf-8")

    wm = WorkspaceManager()
    project = wm.create_project("VariantProj", proj_dir / "VariantProj.dpa", format_version=8)
    lib_ref = LibraryRef(path="modules", kind="package")
    project.module_libraries.append(lib_ref)

    pkgs = {p.manifest.definition: p for p in scan_library(lib_ref, proj_dir)}
    tle_pkg = pkgs["/MICROSAR/CanTrcv_Tle9255/CanTrcv"]
    gen_pkg = pkgs["/MICROSAR/CanTrcv_GenericCan/CanTrcv"]

    mgr = project.add_module_from_package(tle_pkg, lib_index=0, persist=True, confirm=lambda *_: True)
    gen_c = mgr.create_container_instance(mgr.module_def.containers["CanTrcvGeneral"], None, "CanTrcvGeneral")
    mgr.set_parameter_value(gen_c, "CanTrcvDevErrorDetect", True)
    ch_c = mgr.create_container_instance(mgr.module_def.containers["CanTrcvChannel"], None, "CanTrcvChannel_0")
    mgr.set_parameter_value(ch_c, "CanTrcvBaudrateRatio", 10)
    wm.save_project()
    return wm, project, gen_pkg, tle_pkg


def test_restore_deleted_module_preserves_exact_variant_and_rejects_ambiguous(tmp_path):
    """Restoring a deleted module selects the archived DEFINITION-REF variant and rejects ambiguous archives."""
    import pytest

    wm, project, _gen_pkg, _tle_pkg = _setup_cantrcv_variant_project(tmp_path)
    project.remove_module("CanTrcv", archive=True)
    archives = project.list_deleted_archives("CanTrcv")
    assert len(archives) == 1

    restored_mgr = project.restore_deleted_module(archives[0], confirm=lambda *_: True)
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    assert restored_mgr.module_def.ar_path == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    ch = next(c for c in restored_mgr.configuration.containers if c.short_name == "CanTrcvChannel_0")
    assert ch.parameter_values["CanTrcvBaudrateRatio"].value == 10
    assert ch.unknown_parameters == {}

    # Remove again and try restoring an ambiguous archive with generic /AUTOSAR/EcucDefs/CanTrcv
    project.remove_module("CanTrcv", archive=False)
    ambig_archive = tmp_path / "ambig_CanTrcv.arxml"
    ambig_archive.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>CanTrcv_Config</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    with pytest.raises(ValueError) as exc_info:
        project.restore_deleted_module(ambig_archive, confirm=lambda *_: True)
    msg = str(exc_info.value)
    assert "/MICROSAR/CanTrcv_GenericCan/CanTrcv" in msg
    assert "/MICROSAR/CanTrcv_Tle9255/CanTrcv" in msg


def test_switch_module_variant_preview_apply_and_rollback(tmp_path):
    """switch_module_variant previews compatibility, rolls back on rejection, and switches atomically on confirm."""
    wm, project, gen_pkg, _tle_pkg = _setup_cantrcv_variant_project(tmp_path)

    variants = project.list_module_variant_packages("CanTrcv")
    assert [pkg.manifest.definition for _idx, pkg in variants] == [
        "/MICROSAR/CanTrcv_GenericCan/CanTrcv",
        "/MICROSAR/CanTrcv_Tle9255/CanTrcv",
    ]

    # 1. Preview only: reports kept, unknown, missing required, and baseline changes without mutating project
    plan = project.switch_module_variant("CanTrcv", gen_pkg, target_lib_index=0, preview_only=True)
    assert plan.applied is False
    assert any("CanTrcvGeneral" in c for c in plan.kept_containers)
    assert any("CanTrcvDevErrorDetect" in p for p in plan.kept_parameters)
    assert any("CanTrcvChannel_0" in c for c in plan.unknown_containers)
    assert any("CanTrcvBaudrateRatio" in p for p in plan.unknown_parameters)
    assert any("CanTrcvHwInterface" in p for p in plan.missing_required_parameters)
    assert plan.baseline_has_changes is True
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"

    # 2. Rejection: full atomic rollback to Tle9255
    rejected = project.switch_module_variant(
        "CanTrcv", gen_pkg, target_lib_index=0, preview_only=False, confirm=lambda *_: False
    )
    assert rejected.applied is False
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    assert project.module_managers["CanTrcv"].module_def.ar_path == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    assert project.packages["CanTrcv"].manifest.definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    ch = next(c for c in project.module_managers["CanTrcv"].configuration.containers if c.short_name == "CanTrcvChannel_0")
    assert ch.parameter_values["CanTrcvBaudrateRatio"].value == 10
    assert ch.unknown_parameters == {}

    # 3. Confirmed apply: switches to GenericCan, preserves incompatible values in unknown_parameters, applies Pre
    applied = project.switch_module_variant(
        "CanTrcv", gen_pkg, target_lib_index=0, preview_only=False, confirm=lambda *_: True
    )
    assert applied.applied is True
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"
    new_mgr = project.module_managers["CanTrcv"]
    assert new_mgr.module_def.ar_path == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"
    new_gen = next(c for c in new_mgr.configuration.containers if c.short_name == "CanTrcvGeneral")
    assert new_gen.parameter_values["CanTrcvDevErrorDetect"].value is True
    assert new_gen.parameter_values["CanTrcvPreFlag"].value is True
    old_ch = next(c for c in new_mgr.configuration.containers if c.short_name == "CanTrcvChannel_0")
    assert "CanTrcvBaudrateRatio" in old_ch.unknown_parameters

    wm.save_project()
    reloaded, failed = WorkspaceManager().load_project(project.path, confirm=lambda *_: True)
    assert failed == []
    assert reloaded.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"
    assert reloaded.module_managers["CanTrcv"].module_def.ar_path == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"


def test_extract_module_config_strict_vendor_mismatch_and_fallbacks(tmp_path):
    """_extract_module_config matches ConfigurationManager.load_configuration rules:
    rejects 1 or more incompatible vendor defs with ValueError, allows standard/empty fallbacks,
    ignores unrelated modules, and treats standard expected_def_ref as permissive."""
    import pytest
    from autosar_configurator.core.davinci_importer import DaVinciProjectImporter

    def _write_cfg(filename: str, blocks_xml: str) -> Path:
        p = tmp_path / filename
        p.write_text(f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
{blocks_xml}
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
        return p

    tle_ref = "/MICROSAR/CanTrcv_Tle9255/CanTrcv"

    # 1. Single incompatible vendor variant -> raises ValueError
    single_wrong = _write_cfg("single_wrong.arxml", """
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>""")
    with pytest.raises(ValueError, match="CanTrcv_GenericCan"):
        DaVinciProjectImporter._extract_module_config(single_wrong, "CanTrcv", tle_ref)

    # 2. Multiple incompatible vendor variants -> raises ValueError listing all
    multi_wrong = _write_cfg("multi_wrong.arxml", """
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/VendorB/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>""")
    with pytest.raises(ValueError) as exc_info:
        DaVinciProjectImporter._extract_module_config(multi_wrong, "CanTrcv", tle_ref)
    assert "/MICROSAR/CanTrcv_GenericCan/CanTrcv" in str(exc_info.value)
    assert "/VendorB/CanTrcv" in str(exc_info.value)

    # 3. Unrelated vendor module (Port) + standard CanTrcv -> extracts CanTrcv cleanly
    mixed_std = _write_cfg("mixed_std.arxml", """
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Port</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Port</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>""")
    std_cfg = DaVinciProjectImporter._extract_module_config(mixed_std, "CanTrcv", tle_ref)
    assert std_cfg is not None
    assert std_cfg.short_name == "CanTrcv"

    # 4. Empty DEFINITION-REF fallback -> extracts cleanly
    empty_def = _write_cfg("empty_def.arxml", """
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>""")
    empty_cfg = DaVinciProjectImporter._extract_module_config(empty_def, "CanTrcv", tle_ref)
    assert empty_cfg is not None
    assert empty_cfg.short_name == "CanTrcv"

    # 5. Unrelated module only -> returns None (not ValueError)
    only_port = _write_cfg("only_port.arxml", """
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Port</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Port</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>""")
    assert DaVinciProjectImporter._extract_module_config(only_port, "CanTrcv", tle_ref) is None

    # 6. Standard expected_def_ref is permissive for vendor-specific ECUC blocks
    single_tle = _write_cfg("single_tle.arxml", """
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>""")
    permissive = DaVinciProjectImporter._extract_module_config(
        single_tle, "CanTrcv", "/AUTOSAR/EcucDefs/CanTrcv"
    )
    assert permissive is not None
    assert permissive.definition_ref == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"


def test_import_project_fails_module_on_ecuc_variant_mismatch_instead_of_silent_baseline(tmp_path):
    """DaVinci import rejects ECUC files carrying an incompatible vendor variant rather than
    silently falling back to a blank sip_baseline, both with and without <ModuleDefinitionMapping>."""
    from autosar_configurator.core.davinci_importer import DaVinciProjectImporter

    def _run_scenario(subdir: str, with_mapping: bool):
        root = tmp_path / subdir
        sip = root / "sip"
        bswmd = sip / "Components" / "CanTrcv_30_Tle9255" / "BSWMD"
        bswmd.mkdir(parents=True)
        (bswmd / "CanTrcv_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        app_dir = sip / "Applications" / "MyApp"
        ecuc_dir = app_dir / "Config" / "ECUC"
        ecuc_dir.mkdir(parents=True)
        (ecuc_dir / "CanTrcv_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        mapping_xml = (
            '      <ModuleDefinitionMapping ModuleConfigName="CanTrcv" '
            'ModuleDefinitionRef="/MICROSAR/CanTrcv_Tle9255/CanTrcv"/>\n'
            if with_mapping
            else ""
        )
        dpa_file = app_dir / "MyApp.dpa"
        dpa_file.write_text(f"""<?xml version="1.0" encoding="UTF-8"?>
<ProjectAssistant Version="5.30.35 SP2">
  <Folders>
    <SIP>.\\..\\..</SIP>
    <ECUC>.\\Config\\ECUC</ECUC>
  </Folders>
  <Display>
    <ModuleDefinitionMappings>
{mapping_xml}    </ModuleDefinitionMappings>
  </Display>
  <EcucSplitter>
    <Splitter File=".\\Config\\ECUC\\CanTrcv_ecuc.arxml"><Module Name="CanTrcv"/></Splitter>
  </EcucSplitter>
</ProjectAssistant>""", encoding="utf-8")

        wm = WorkspaceManager()
        project, report = DaVinciProjectImporter.import_project(
            workspace_manager=wm,
            dpa_path=dpa_file,
            target_dir=root / "out",
            project_name="OutApp",
            confirm=lambda *_: True,
        )
        assert "CanTrcv" not in project.module_managers
        assert any(mod == "CanTrcv" and "CanTrcv_GenericCan" in err for mod, err in report.failed_modules)

    _run_scenario("with_mapping", with_mapping=True)
    _run_scenario("without_mapping", with_mapping=False)


def test_import_project_missing_mapped_variant_does_not_fallback_to_other_variant(tmp_path):
    """Explicit <ModuleDefinitionMapping> must not silently fall back to another variant package
    even if another variant of the same module exists in the SIP."""
    from autosar_configurator.core.davinci_importer import DaVinciProjectImporter

    root = tmp_path / "missing_mapped"
    sip = root / "sip"
    bswmd = sip / "Components" / "CanTrcv_30_Generic" / "BSWMD"
    bswmd.mkdir(parents=True)
    (bswmd / "CanTrcv_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_GenericCan</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    app_dir = sip / "Applications" / "MyApp"
    ecuc_dir = app_dir / "Config" / "ECUC"
    ecuc_dir.mkdir(parents=True)
    (ecuc_dir / "CanTrcv_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/CanTrcv</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

    dpa_file = app_dir / "MyApp.dpa"
    dpa_file.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<ProjectAssistant Version="5.30.35 SP2">
  <Folders>
    <SIP>.\\..\\..</SIP>
    <ECUC>.\\Config\\ECUC</ECUC>
  </Folders>
  <Display>
    <ModuleDefinitionMappings>
      <ModuleDefinitionMapping ModuleConfigName="CanTrcv" ModuleDefinitionRef="/MICROSAR/CanTrcv_Tle9255/CanTrcv"/>
    </ModuleDefinitionMappings>
  </Display>
  <EcucSplitter>
    <Splitter File=".\\Config\\ECUC\\CanTrcv_ecuc.arxml"><Module Name="CanTrcv"/></Splitter>
  </EcucSplitter>
</ProjectAssistant>""", encoding="utf-8")

    wm = WorkspaceManager()
    project, report = DaVinciProjectImporter.import_project(
        workspace_manager=wm,
        dpa_path=dpa_file,
        target_dir=root / "out",
        project_name="OutApp",
        confirm=lambda *_: True,
    )
    assert "CanTrcv" not in project.module_managers
    assert any(
        mod == "CanTrcv"
        and "/MICROSAR/CanTrcv_Tle9255/CanTrcv" in err
        and "/MICROSAR/CanTrcv_GenericCan/CanTrcv" in err
        for mod, err in report.failed_modules
    )


def test_import_project_unmapped_multi_variant_disambiguates_by_ecuc_or_fails_ambiguous(tmp_path):
    """Without <ModuleDefinitionMapping>, multi-variant SIP modules use ECUC DEFINITION-REF to
    disambiguate; if ECUC lacks a specific variant def (or is missing), import fails unambiguously."""
    from autosar_configurator.core.davinci_importer import DaVinciProjectImporter

    def _run_unmapped(subdir: str, ecuc_def_ref: str):
        root = tmp_path / subdir
        sip = root / "sip"

        gen_bswmd = sip / "Components" / "CanTrcv_30_Generic" / "BSWMD"
        gen_bswmd.mkdir(parents=True)
        (gen_bswmd / "CanTrcv_30_Generic_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_GenericCan</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        tle_bswmd = sip / "Components" / "CanTrcv_30_Tle9255" / "BSWMD"
        tle_bswmd.mkdir(parents=True)
        (tle_bswmd / "CanTrcv_30_Tle9255_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        app_dir = sip / "Applications" / "MyApp"
        ecuc_dir = app_dir / "Config" / "ECUC"
        ecuc_dir.mkdir(parents=True)
        (ecuc_dir / "CanTrcv_ecuc.arxml").write_text(f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{ecuc_def_ref}</DEFINITION-REF>
      <CONTAINERS/>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        dpa_file = app_dir / "MyApp.dpa"
        dpa_file.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<ProjectAssistant Version="5.30.35 SP2">
  <Folders>
    <SIP>.\\..\\..</SIP>
    <ECUC>.\\Config\\ECUC</ECUC>
  </Folders>
  <Display><ModuleDefinitionMappings/></Display>
  <EcucSplitter>
    <Splitter File=".\\Config\\ECUC\\CanTrcv_ecuc.arxml"><Module Name="CanTrcv"/></Splitter>
  </EcucSplitter>
</ProjectAssistant>""", encoding="utf-8")

        wm = WorkspaceManager()
        return DaVinciProjectImporter.import_project(
            workspace_manager=wm,
            dpa_path=dpa_file,
            target_dir=root / "out",
            project_name="OutApp",
            confirm=lambda *_: True,
        )

    # Scenario A: ECUC explicitly selects Tle9255 -> disambiguates cleanly
    proj_a, rep_a = _run_unmapped("ecuc_specific", "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    assert rep_a.failed_modules == []
    assert proj_a.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"

    # Scenario B: ECUC only has standard AUTOSAR path -> ambiguous, reported as failed
    proj_b, rep_b = _run_unmapped("ecuc_ambiguous", "/AUTOSAR/EcucDefs/CanTrcv")
    assert "CanTrcv" not in proj_b.module_managers
    assert any(
        mod == "CanTrcv"
        and "/MICROSAR/CanTrcv_GenericCan/CanTrcv" in err
        and "/MICROSAR/CanTrcv_Tle9255/CanTrcv" in err
        for mod, err in rep_b.failed_modules
    )


def test_variant_switch_preserves_unknown_params_after_reload_and_defers_baseline_delete(tmp_path):
    """After switching variant and reloading, parameters inside unknown containers retain their
    unknown_parameters marker; switching back to a baseline-less variant defers snapshot deletion until save."""
    wm, project, gen_pkg, tle_pkg = _setup_cantrcv_variant_project(tmp_path)
    proj_dir = project.path.parent

    # 1. Switch Tle9255 -> GenericCan (has Pre baseline; CanTrcvChannel_0 becomes unknown container)
    applied = project.switch_module_variant(
        "CanTrcv", gen_pkg, target_lib_index=0, preview_only=False, confirm=lambda *_: True
    )
    assert applied.applied is True
    wm.save_project()

    base_snapshot = proj_dir / "config" / "base" / "CanTrcv.arxml"
    base_layers = proj_dir / "config" / "base" / "CanTrcv.layers.json"
    assert base_snapshot.is_file()
    assert base_layers.is_file()

    # 2. Reload project: CanTrcvBaudrateRatio inside unknown CanTrcvChannel_0 must stay flagged
    reloaded_wm = WorkspaceManager()
    reloaded, reload_failed = reloaded_wm.load_project(project.path, confirm=lambda *_: True)
    assert reload_failed == []
    reloaded_ch = next(
        c for c in reloaded.module_managers["CanTrcv"].configuration.containers
        if c.short_name == "CanTrcvChannel_0"
    )
    assert reloaded_ch.parameter_values["CanTrcvBaudrateRatio"].value == 10
    assert "CanTrcvBaudrateRatio" in reloaded_ch.unknown_parameters

    # 3. Switch back GenericCan -> Tle9255 (no Pre/Rec layers): disk snapshot stays until save_project()
    reverted = reloaded.switch_module_variant(
        "CanTrcv", tle_pkg, target_lib_index=0, preview_only=False, confirm=lambda *_: True
    )
    assert reverted.applied is True
    assert base_snapshot.is_file()
    assert base_layers.is_file()

    reloaded_wm.save_project()
    assert not base_snapshot.exists()
    assert not base_layers.exists()


def test_variant_switch_rollback_removes_added_baseline_and_restores_library_excludes(tmp_path, monkeypatch):
    """When switching from a baseline-less variant to one with Pre layers fails late (e.g. during
    resolve_all_references), rollback must remove newly added baseline/merge state and restore
    module_libraries[*].exclude mutated by deduplicate_library_definitions."""
    import pytest

    wm, project, gen_pkg, _tle_pkg = _setup_cantrcv_variant_project(tmp_path)
    assert "CanTrcv" not in project.baselines
    assert "CanTrcv" not in project.last_merge_results
    original_excludes = [list(lib.exclude) for lib in project.module_libraries]

    def _mutate_excludes_and_keep():
        project.module_libraries[0].exclude.append("CanTrcv_Tle9255")

    def _fail_resolve(force: bool = False):
        raise RuntimeError("boom during resolve_all_references")

    monkeypatch.setattr(project, "deduplicate_library_definitions", _mutate_excludes_and_keep)
    monkeypatch.setattr(project, "resolve_all_references", _fail_resolve)

    with pytest.raises(RuntimeError, match="boom during resolve_all_references"):
        project.switch_module_variant(
            "CanTrcv", gen_pkg, target_lib_index=0, preview_only=False, confirm=lambda *_: True
        )

    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    assert "CanTrcv" not in project.baselines
    assert "CanTrcv" not in project.last_merge_results
    assert [list(lib.exclude) for lib in project.module_libraries] == original_excludes


def test_variant_switch_plan_reports_stale_variant_overrides(tmp_path):
    """VariantSwitchPlan surfaces ECU variant_overrides keys that reference containers/parameters
    dropped in the target implementation variant."""
    _wm, project, gen_pkg, _tle_pkg = _setup_cantrcv_variant_project(tmp_path)
    cfg = project.module_managers["CanTrcv"].configuration
    cfg.variant_overrides = {
        "V2": {
            "/CanTrcv/CanTrcvGeneral.CanTrcvDevErrorDetect": False,
            "/CanTrcv/CanTrcvChannel_0.CanTrcvBaudrateRatio": 20,
        }
    }

    plan = project.switch_module_variant(
        "CanTrcv", gen_pkg, target_lib_index=0, preview_only=True
    )
    assert plan.applied is False
    assert plan.stale_variant_overrides == ["[V2] /CanTrcv/CanTrcvChannel_0.CanTrcvBaudrateRatio"]
    assert "可能失效的变体覆盖项" in plan.to_markdown()
    assert "[V2] /CanTrcv/CanTrcvChannel_0.CanTrcvBaudrateRatio" in plan.to_markdown()









