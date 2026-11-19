"""End-to-end integration tests for W12 DaVinci project import."""
import json
from pathlib import Path

from autosar_configurator.core.workspace_manager import WorkspaceManager


def _create_sample_sip_and_davinci(root: Path):
    """Build a realistic Vector SIP + DaVinci XML .dpa + EB MCAL tree."""
    sip = root / "sip"

    # 1. Os (BSW with DerivativeMapping + Pre)
    os_dir = sip / "Components" / "Os"
    (os_dir / "BSWMD").mkdir(parents=True)
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

    # 1. Active BSW modules (Os, Com) + EB MCAL (Dio) imported; UnusedMod NOT added
    assert set(project.module_managers.keys()) == {"Os", "Com", "Dio"}
    assert "UnusedMod" not in project.module_managers

    # 2. Derivative metadata recorded and persisted in .dpa
    assert project.derivative_uuid == "UUID-THA6206"
    assert project.derivative_name == "Tongxin_THA6206"
    saved_dpa = json.loads((out_parent / "MigratedApp" / "MigratedApp.dpa").read_text(encoding="utf-8"))
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

    # 5. Report written with per-module stats
    report_path = out_parent / "MigratedApp" / ".import_report.md"
    assert report_path.is_file()
    md = report_path.read_text(encoding="utf-8")
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
