"""Tests for multi-ECUC-MODULE-DEF SIP scanning, slicing, import, and Rte_Cfg.h generation."""

import json
from pathlib import Path
from lxml import etree

from autosar_configurator.core.davinci_import_cli import DaVinciImportCLI
from autosar_configurator.core.davinci_importer import (
    DaVinciProjectImporter,
    SipFile,
    SipMerger,
    SipPackageWriter,
    SipScanner,
)
from autosar_configurator.core.packages.manifest import load_manifest
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.rules.reference_rules import ReferenceIntegrityRule
from autosar_configurator.core.validation_engine import ValidationEngine
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

AR_NS = "http://autosar.org/schema/r4.0"


RTE_MULTI_DEF_BSWMD = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>Rte</SHORT-NAME>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>RteBswGeneral</SHORT-NAME>
              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              <PARAMETERS>
                <ECUC-BOOLEAN-PARAM-DEF>
                  <SHORT-NAME>RteSchMVersionInfoApi</SHORT-NAME>
                  <DEFAULT-VALUE>false</DEFAULT-VALUE>
                </ECUC-BOOLEAN-PARAM-DEF>
              </PARAMETERS>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>RteGeneration</SHORT-NAME>
              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              <PARAMETERS>
                <ECUC-BOOLEAN-PARAM-DEF>
                  <SHORT-NAME>RteEnableMultiCore</SHORT-NAME>
                  <DEFAULT-VALUE>false</DEFAULT-VALUE>
                </ECUC-BOOLEAN-PARAM-DEF>
                <ECUC-BOOLEAN-PARAM-DEF>
                  <SHORT-NAME>RteEnableMemoryProtection</SHORT-NAME>
                  <DEFAULT-VALUE>false</DEFAULT-VALUE>
                </ECUC-BOOLEAN-PARAM-DEF>
                <ECUC-INTEGER-PARAM-DEF>
                  <SHORT-NAME>RteCodeVendorId</SHORT-NAME>
                  <DEFAULT-VALUE>30</DEFAULT-VALUE>
                </ECUC-INTEGER-PARAM-DEF>
              </PARAMETERS>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>RteInitializationBehavior</SHORT-NAME>
              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
              <PARAMETERS>
                <ECUC-ENUMERATION-PARAM-DEF>
                  <SHORT-NAME>RteInitializationStrategy</SHORT-NAME>
                  <DEFAULT-VALUE>RTE_INITIALIZATION_STRATEGY_AT_RTE_START_AND_PARTITION_RESTART</DEFAULT-VALUE>
                </ECUC-ENUMERATION-PARAM-DEF>
              </PARAMETERS>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>RteOsInteraction</SHORT-NAME>
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              <SUB-CONTAINERS>
                <ECUC-PARAM-CONF-CONTAINER-DEF>
                  <SHORT-NAME>RteUsedOsActivation</SHORT-NAME>
                  <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
                  <UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
                  <REFERENCES>
                    <ECUC-REFERENCE-DEF>
                      <SHORT-NAME>RteActivationOsTaskRef</SHORT-NAME>
                      <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsTask</DESTINATION-REF>
                    </ECUC-REFERENCE-DEF>
                  </REFERENCES>
                </ECUC-PARAM-CONF-CONTAINER-DEF>
              </SUB-CONTAINERS>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>RteBswModuleInstance</SHORT-NAME>
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
              <REFERENCES>
                <ECUC-FOREIGN-REFERENCE-DEF>
                  <SHORT-NAME>RteBswImplementationRef</SHORT-NAME>
                  <DESTINATION-TYPE>BSW-IMPLEMENTATION</DESTINATION-TYPE>
                </ECUC-FOREIGN-REFERENCE-DEF>
              </REFERENCES>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>RteSwComponentInstance</SHORT-NAME>
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
          </CONTAINERS>
        </ECUC-MODULE-DEF>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>Rte_Impl</SHORT-NAME>
          <SW-VERSION>4.38.02</SW-VERSION>
          <PRECONFIGURED-CONFIGURATION-REFS>
            <PRECONFIGURED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/Rte_Pre</PRECONFIGURED-CONFIGURATION-REF>
          </PRECONFIGURED-CONFIGURATION-REFS>
          <RECOMMENDED-CONFIGURATION-REFS>
            <RECOMMENDED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/Rte_Rec</RECOMMENDED-CONFIGURATION-REF>
          </RECOMMENDED-CONFIGURATION-REFS>
          <VENDOR-SPECIFIC-MODULE-DEF-REFS>
            <VENDOR-SPECIFIC-MODULE-DEF-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Rte</VENDOR-SPECIFIC-MODULE-DEF-REF>
          </VENDOR-SPECIFIC-MODULE-DEF-REFS>
        </BSW-IMPLEMENTATION>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Rte_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Rte</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>RteGeneration</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteGeneration</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Rte_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Rte</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>RteBswGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteBswGeneral</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>RteCalculation</SHORT-NAME>
        </ECUC-MODULE-DEF>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>RteChecks</SHORT-NAME>
        </ECUC-MODULE-DEF>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


LINIF_MULTI_DEF_BSWMD = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>LinIf</SHORT-NAME>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>LinIfGeneral</SHORT-NAME></ECUC-PARAM-CONF-CONTAINER-DEF>
          </CONTAINERS>
        </ECUC-MODULE-DEF>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>LinIf_Impl</SHORT-NAME>
          <SW-VERSION>10.00.00</SW-VERSION>
          <PRECONFIGURED-CONFIGURATION-REFS>
            <PRECONFIGURED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/LinIf_Pre</PRECONFIGURED-CONFIGURATION-REF>
          </PRECONFIGURED-CONFIGURATION-REFS>
          <RECOMMENDED-CONFIGURATION-REFS>
            <RECOMMENDED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/LinIf_Rec</RECOMMENDED-CONFIGURATION-REF>
          </RECOMMENDED-CONFIGURATION-REFS>
          <VENDOR-SPECIFIC-MODULE-DEF-REFS>
            <VENDOR-SPECIFIC-MODULE-DEF-REF DEST="ECUC-MODULE-DEF">/MICROSAR/LinIf</VENDOR-SPECIFIC-MODULE-DEF-REF>
          </VENDOR-SPECIFIC-MODULE-DEF-REFS>
        </BSW-IMPLEMENTATION>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>LinIf_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/LinIf</DEFINITION-REF>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>LinIf_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/LinIf</DEFINITION-REF>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>LinTp</SHORT-NAME>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>LinTpGeneral</SHORT-NAME></ECUC-PARAM-CONF-CONTAINER-DEF>
          </CONTAINERS>
        </ECUC-MODULE-DEF>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>LinTp_Impl</SHORT-NAME>
          <SW-VERSION>10.00.00</SW-VERSION>
          <PRECONFIGURED-CONFIGURATION-REFS>
            <PRECONFIGURED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/LinTp_Pre</PRECONFIGURED-CONFIGURATION-REF>
          </PRECONFIGURED-CONFIGURATION-REFS>
          <RECOMMENDED-CONFIGURATION-REFS>
            <RECOMMENDED-CONFIGURATION-REF DEST="ECUC-MODULE-CONFIGURATION-VALUES">/MICROSAR/LinTp_Rec</RECOMMENDED-CONFIGURATION-REF>
          </RECOMMENDED-CONFIGURATION-REFS>
          <VENDOR-SPECIFIC-MODULE-DEF-REFS>
            <VENDOR-SPECIFIC-MODULE-DEF-REF DEST="ECUC-MODULE-DEF">/MICROSAR/LinTp</VENDOR-SPECIFIC-MODULE-DEF-REF>
          </VENDOR-SPECIFIC-MODULE-DEF-REFS>
        </BSW-IMPLEMENTATION>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>LinTp_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/LinTp</DEFINITION-REF>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>LinTp_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/LinTp</DEFINITION-REF>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


LINIF_MULTI_IMPL_MEMMAP = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>LinIf_Impl</SHORT-NAME>
          <RESOURCE-CONSUMPTION>
            <SHORT-NAME>ResourceConsumption</SHORT-NAME>
            <MEMORY-SECTIONS>
              <MEMORY-SECTION><SHORT-NAME>LINIF_CODE</SHORT-NAME></MEMORY-SECTION>
            </MEMORY-SECTIONS>
          </RESOURCE-CONSUMPTION>
        </BSW-IMPLEMENTATION>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>LinTp_Impl</SHORT-NAME>
          <RESOURCE-CONSUMPTION>
            <SHORT-NAME>ResourceConsumption</SHORT-NAME>
            <MEMORY-SECTIONS>
              <MEMORY-SECTION><SHORT-NAME>LINTP_CODE</SHORT-NAME></MEMORY-SECTION>
            </MEMORY-SECTIONS>
          </RESOURCE-CONSUMPTION>
        </BSW-IMPLEMENTATION>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


OS_DEF_BSWMD = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>Os</SHORT-NAME>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>OsTask</SHORT-NAME>
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
          </CONTAINERS>
        </ECUC-MODULE-DEF>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


def _write_sip_and_dpa(tmp_path: Path) -> Path:
    sip = tmp_path / "sip"
    (sip / "Components" / "Rte" / "BSWMD").mkdir(parents=True)
    (sip / "Components" / "Rte" / "BSWMD" / "Rte_bswmd.arxml").write_text(
        RTE_MULTI_DEF_BSWMD, encoding="utf-8"
    )
    (sip / "Components" / "LinIf" / "BSWMD").mkdir(parents=True)
    (sip / "Components" / "LinIf" / "BSWMD" / "LinIf_bswmd.arxml").write_text(
        LINIF_MULTI_DEF_BSWMD, encoding="utf-8"
    )
    (sip / "Components" / "LinIf" / "BSWMD" / "LinIf_MemMap.arxml").write_text(
        LINIF_MULTI_IMPL_MEMMAP, encoding="utf-8"
    )
    (sip / "Components" / "Os" / "BSWMD").mkdir(parents=True)
    (sip / "Components" / "Os" / "BSWMD" / "Os_bswmd.arxml").write_text(
        OS_DEF_BSWMD, encoding="utf-8"
    )

    app_dir = sip / "Applications" / "DemoApp"
    (app_dir / "Config" / "ECUC").mkdir(parents=True)
    (app_dir / "Config" / "InternalBehavior").mkdir(parents=True)

    (app_dir / "Config" / "InternalBehavior" / "BswM_ib_bswmd.arxml").write_text(
        """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
      <AR-PACKAGE><SHORT-NAME>BswM_ib_bswmd</SHORT-NAME><AR-PACKAGES>
        <AR-PACKAGE><SHORT-NAME>BswModuleDescriptions</SHORT-NAME><ELEMENTS>
          <BSW-IMPLEMENTATION><SHORT-NAME>BswM_Impl</SHORT-NAME></BSW-IMPLEMENTATION>
        </ELEMENTS></AR-PACKAGE>
      </AR-PACKAGES></AR-PACKAGE>
    </AR-PACKAGES></AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>""",
        encoding="utf-8",
    )

    (app_dir / "Config" / "ECUC" / "DemoApp_Os_Os_ecuc.arxml").write_text(
        """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Os</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>OsTask_10ms</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsTask</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""",
        encoding="utf-8",
    )

    (app_dir / "Config" / "ECUC" / "DemoApp_Rte_Rte_ecuc.arxml").write_text(
        """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Rte</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Rte</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>RteBswGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteBswGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/Rte/RteBswGeneral/RteSchMVersionInfoApi</DEFINITION-REF>
              <VALUE>true</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>RteGeneration</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteGeneration</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/Rte/RteGeneration/RteEnableMultiCore</DEFINITION-REF>
              <VALUE>true</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/Rte/RteGeneration/RteEnableMemoryProtection</DEFINITION-REF>
              <VALUE>true</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/Rte/RteGeneration/RteCodeVendorId</DEFINITION-REF>
              <VALUE>30</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>RteInitializationBehavior</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteInitializationBehavior</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/Rte/RteInitializationBehavior/RteInitializationStrategy</DEFINITION-REF>
              <VALUE>RTE_INITIALIZATION_STRATEGY_AT_DATA_DECLARATION</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>RteOsInteraction</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteOsInteraction</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>Act_10ms</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation</DEFINITION-REF>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE>
                  <DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation/RteActivationOsTaskRef</DEFINITION-REF>
                  <VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Os/OsTask_10ms</VALUE-REF>
                </ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>BswM</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteBswModuleInstance</DEFINITION-REF>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE>
              <DEFINITION-REF DEST="ECUC-FOREIGN-REFERENCE-DEF">/MICROSAR/Rte/RteBswModuleInstance/RteBswImplementationRef</DEFINITION-REF>
              <VALUE-REF DEST="BSW-IMPLEMENTATION">/MICROSAR/BswM_ib_bswmd/BswModuleDescriptions/BswM_Impl</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>SwcInst1</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Rte/RteSwComponentInstance</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""",
        encoding="utf-8",
    )

    dpa_path = app_dir / "DemoApp.dpa"
    dpa_path.write_text(
        """<?xml version="1.0" encoding="UTF-8"?>
<ProjectAssistant Version="5.0">
  <General><Name>DemoApp</Name></General>
  <Folders>
    <SIP>..\\..\\</SIP>
    <ECUC>.\\Config\\ECUC</ECUC>
  </Folders>
  <Tools>
    <DEV>.\\Config\\InternalBehavior\\BswM_ib_bswmd.arxml</DEV>
  </Tools>
  <EcucSplitter>
    <Splitter File="./Config/ECUC/DemoApp_Os_Os_ecuc.arxml">
      <Module Name="Os"/>
    </Splitter>
    <Splitter File="./Config/ECUC/DemoApp_Rte_Rte_ecuc.arxml">
      <Module Name="Rte"/>
    </Splitter>
  </EcucSplitter>
  <ExecutionEnvironment>
    <ModuleDefinitionMappings>
      <ModuleDefinitionMapping ModuleConfigName="Os" ModuleDefinitionRef="/MICROSAR/Os"/>
      <ModuleDefinitionMapping ModuleConfigName="Rte" ModuleDefinitionRef="/MICROSAR/Rte"/>
    </ModuleDefinitionMappings>
    <BswImplSwVersion>
      <BswImpl ModuleDefinitionRef="/MICROSAR/Rte" SwVersion="4.38.02"/>
    </BswImplSwVersion>
  </ExecutionEnvironment>
</ProjectAssistant>""",
        encoding="utf-8",
    )
    return dpa_path


def _def_short_names(xml_bytes: bytes) -> list[str]:
    root = etree.fromstring(xml_bytes)
    return [
        el.findtext(f"{{{AR_NS}}}SHORT-NAME")
        for el in root.iter(f"{{{AR_NS}}}ECUC-MODULE-DEF")
    ]


def _cfg_short_names(xml_bytes: bytes) -> list[str]:
    root = etree.fromstring(xml_bytes)
    return [
        el.findtext(f"{{{AR_NS}}}SHORT-NAME")
        for el in root.iter(f"{{{AR_NS}}}ECUC-MODULE-CONFIGURATION-VALUES")
    ]


def test_sip_scanner_and_merger_split_rte_multi_def(tmp_path):
    dpa_path = _write_sip_and_dpa(tmp_path)
    sip_root = dpa_path.parents[2]
    rte_bswmd = sip_root / "Components" / "Rte" / "BSWMD" / "Rte_bswmd.arxml"

    assert SipScanner._extract_module_and_role(rte_bswmd) == ("Rte", "def")

    scanner = SipScanner(sip_root)
    all_modules = scanner.scan_all_modules()
    assert {"Rte", "RteCalculation", "RteChecks"}.issubset(all_modules.keys())

    out_dir = tmp_path / "pkgs"
    for mod in ("Rte", "RteCalculation", "RteChecks"):
        files = all_modules[mod]
        def_content = SipMerger.merge_definition(files, mod)
        assert def_content is not None
        assert _def_short_names(def_content) == [mod]

        vals = SipMerger.extract_value_collections(files, mod)
        impl_meta = SipMerger.extract_bsw_implementation_metadata(files, module_name=mod)
        SipPackageWriter.write_package(
            module_name=mod,
            definition_content=def_content,
            pre_config=vals.get("pre"),
            rec_config=vals.get("rec"),
            output_dir=out_dir,
            impl_metadata=impl_meta,
        )

    rte_manifest = load_manifest(out_dir / "Rte")
    assert rte_manifest.module == "Rte"
    assert rte_manifest.definition == "/MICROSAR/Rte"
    assert rte_manifest.implementation_path == "/MICROSAR/Rte_Impl"
    assert rte_manifest.pre == ["/MICROSAR/Rte_Pre"]
    assert rte_manifest.rec == ["/MICROSAR/Rte_Rec"]
    assert rte_manifest.templates == "templates"
    assert (out_dir / "Rte" / "templates" / "include" / "Rte_Cfg.h").is_file()

    for empty_mod in ("RteCalculation", "RteChecks"):
        m = load_manifest(out_dir / empty_mod)
        assert m.module == empty_mod
        assert m.definition == f"/MICROSAR/{empty_mod}"
        assert m.pre == []
        assert m.rec == []
        assert m.implementation_path is None
        assert not (out_dir / empty_mod / "templates").exists()


def test_sip_scanner_and_merger_split_linif_and_lintp_with_memmap(tmp_path):
    dpa_path = _write_sip_and_dpa(tmp_path)
    sip_root = dpa_path.parents[2]

    scanner = SipScanner(sip_root)
    all_modules = scanner.scan_all_modules()
    assert "LinIf" in all_modules
    assert "LinTp" in all_modules

    out_dir = tmp_path / "pkgs"
    for mod in ("LinIf", "LinTp"):
        files = all_modules[mod]
        partitions = SipScanner.partition_module_files(mod, files)
        assert len(partitions) == 1
        pkg_dir_name, pkg_mod_name, group_files = partitions[0]
        assert pkg_dir_name == mod
        assert pkg_mod_name == mod

        def_content = SipMerger.merge_definition(group_files, pkg_mod_name)
        vals = SipMerger.extract_value_collections(group_files, pkg_mod_name)
        impl_meta = SipMerger.extract_bsw_implementation_metadata(group_files, module_name=pkg_mod_name)
        SipPackageWriter.write_package(
            module_name=pkg_mod_name,
            definition_content=def_content,
            pre_config=vals.get("pre"),
            rec_config=vals.get("rec"),
            output_dir=out_dir,
            impl_metadata=impl_meta,
            package_dir_name=pkg_dir_name,
        )

    linif_m = load_manifest(out_dir / "LinIf")
    assert linif_m.definition == "/MICROSAR/LinIf"
    assert linif_m.implementation_path == "/MICROSAR/LinIf_Impl"
    assert linif_m.pre == ["/MICROSAR/LinIf_Pre"]
    assert linif_m.rec == ["/MICROSAR/LinIf_Rec"]
    linif_secs = {s["short_name"] for s in SipPackageWriter.read_impl_metadata(out_dir / "LinIf")["memory_sections"]}
    assert linif_secs == {"LINIF_CODE"}

    lintp_m = load_manifest(out_dir / "LinTp")
    assert lintp_m.definition == "/MICROSAR/LinTp"
    assert lintp_m.implementation_path == "/MICROSAR/LinTp_Impl"
    assert lintp_m.pre == ["/MICROSAR/LinTp_Pre"]
    assert lintp_m.rec == ["/MICROSAR/LinTp_Rec"]
    lintp_secs = {s["short_name"] for s in SipPackageWriter.read_impl_metadata(out_dir / "LinTp")["memory_sections"]}
    assert lintp_secs == {"LINTP_CODE"}

    assert _cfg_short_names((out_dir / "LinIf" / "config" / "LinIf_Pre.arxml").read_bytes()) == ["LinIf_Pre"]
    assert _cfg_short_names((out_dir / "LinTp" / "config" / "LinTp_Pre.arxml").read_bytes()) == ["LinTp_Pre"]


def test_davinci_import_cli_matches_sliced_packages(tmp_path):
    dpa_path = _write_sip_and_dpa(tmp_path)
    cli_out = tmp_path / "cli_out"

    rc = DaVinciImportCLI().run(["--project", str(dpa_path), "--output", str(cli_out)])
    assert rc == 0

    rte_m = load_manifest(cli_out / "Rte")
    assert rte_m.module == "Rte"
    assert rte_m.definition == "/MICROSAR/Rte"
    assert rte_m.implementation_path == "/MICROSAR/Rte_Impl"
    assert rte_m.pre == ["/MICROSAR/Rte_Pre"]
    assert rte_m.rec == ["/MICROSAR/Rte_Rec"]
    assert rte_m.templates == "templates"
    assert (cli_out / "Rte" / "templates" / "include" / "Rte_Cfg.h").is_file()

    assert load_manifest(cli_out / "LinIf").implementation_path == "/MICROSAR/LinIf_Impl"
    assert load_manifest(cli_out / "LinTp").implementation_path == "/MICROSAR/LinTp_Impl"


def test_reimport_over_stale_rtechecks_preserves_rte_ecuc_validates_and_generates(tmp_path):
    dpa_path = _write_sip_and_dpa(tmp_path)
    proj_dir = tmp_path / "projects"

    # Simulate an older buggy project where RteChecks hijacked /MICROSAR/Rte and left stale files.
    target_root = proj_dir / "DemoProj"
    stale_rtechecks = target_root / "modules" / "davinci" / "RteChecks"
    (stale_rtechecks / "config").mkdir(parents=True)
    (stale_rtechecks / "config" / "RteChecks.arxml").write_text("<AUTOSAR/>", encoding="utf-8")
    (stale_rtechecks / "config" / "RteChecks_Pre.arxml").write_text("<AUTOSAR/>", encoding="utf-8")
    (stale_rtechecks / "config" / "RteChecks_Rec.arxml").write_text("<AUTOSAR/>", encoding="utf-8")
    (stale_rtechecks / "module.json").write_text(
        json.dumps({
            "schema": 1,
            "module": "RteChecks",
            "definition": "/MICROSAR/Rte",
            "files": ["config/RteChecks.arxml"],
            "pre": ["/MICROSAR/Rte_Pre"],
            "rec": ["/MICROSAR/Rte_Rec"],
        }),
        encoding="utf-8",
    )

    wm = WorkspaceManager()
    proj, report1 = DaVinciProjectImporter.import_project(
        wm,
        dpa_path=dpa_path,
        target_dir=proj_dir,
        project_name="DemoProj",
    )
    assert report1.failed_modules == []
    assert "Rte" in proj.module_managers
    assert report1.module_stats["Rte"]["config_source"] == "davinci_ecuc"
    assert report1.module_stats["Rte"]["definition"] == "/MICROSAR/Rte"
    assert report1.module_stats["Rte"]["containers"] == 7
    assert [d for d in report1.value_diffs if d["module"] == "Rte"] == []
    assert len(report1.external_model_files) == 1

    # Also verify re-import into an existing project cleanly heals stale RteChecks without conflicts.
    stale_extra = target_root / "modules" / "davinci" / "LegacyMisnamedRte"
    (stale_extra / "config").mkdir(parents=True)
    (stale_extra / "module.json").write_text(
        json.dumps({"schema": 1, "module": "LegacyMisnamedRte", "definition": "/MICROSAR/Rte", "files": []}),
        encoding="utf-8",
    )
    (stale_rtechecks / "config" / "RteChecks_Pre.arxml").write_text("<AUTOSAR/>", encoding="utf-8")

    proj2, report2 = DaVinciProjectImporter.import_project(wm, dpa_path=dpa_path, into_project=proj)
    assert report2.failed_modules == []
    assert not stale_extra.exists()
    assert not (stale_rtechecks / "config" / "RteChecks_Pre.arxml").exists()
    assert not (stale_rtechecks / "config" / "RteChecks_Rec.arxml").exists()
    assert load_manifest(stale_rtechecks).definition == "/MICROSAR/RteChecks"
    assert load_manifest(target_root / "modules" / "davinci" / "Rte").templates == "templates"

    rte_mgr = proj2.module_managers["Rte"]
    assert rte_mgr.module_def.short_name == "Rte"
    val_engine = ValidationEngine(rte_mgr.module_def, rte_mgr.configuration, proj2)
    val_engine.register_rule(ReferenceIntegrityRule())
    val_res = val_engine.validate()
    assert val_res.error_count == 0

    pkg = ModulePackage(target_root / "modules" / "davinci" / "Rte", load_manifest(target_root / "modules" / "davinci" / "Rte"))
    gen = CodeGenerator(
        rte_mgr.module_def,
        rte_mgr.configuration,
        package_template_dir=pkg.template_dir(),
        all_configurations={
            k: (m.module_def, m.configuration) for k, m in proj2.module_managers.items()
        },
        project_root=target_root,
    )
    gen_out = target_root / "gen"
    assert gen.generate_all(gen_out, flat=True) is True
    assert gen.last_status == "generated"
    header = (gen_out / "include" / "Rte_Cfg.h").read_text(encoding="utf-8")
    assert "#ifndef RTE_CFG_H" in header
    assert "# define RTE_CFG_H" in header
    assert '# include "Std_Types.h"' in header
    assert "#endif /* RTE_CFG_H */" in header
    assert "COMPATIBILITY_MODE" not in header
    assert "NONE" not in header


def test_rte_cfg_h_template_defaults_and_project_overlay(tmp_path):
    bswmd_file = tmp_path / "Rte_bswmd.arxml"
    bswmd_file.write_text(RTE_MULTI_DEF_BSWMD, encoding="utf-8")
    mod_def = EcucDefParser().parse_module_def_file(bswmd_file)

    from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration

    empty_cfg = EcucModuleConfiguration(short_name="Rte", definition_ref="/MICROSAR/Rte")
    tpl_dir = Path(__file__).resolve().parents[2] / "template_packs" / "davinci" / "Rte"
    gen = CodeGenerator(mod_def, empty_cfg, package_template_dir=tpl_dir)
    out1 = tmp_path / "out_default"
    assert gen.generate_all(out1, flat=True) is True
    text = (out1 / "include" / "Rte_Cfg.h").read_text(encoding="utf-8")
    assert "#ifndef RTE_CFG_H" in text
    assert "# define RTE_CFG_H" in text
    assert '# include "Std_Types.h"' in text
    assert "#endif /* RTE_CFG_H */" in text
    assert "COMPATIBILITY_MODE" not in text
    assert "NONE" not in text

    overlay_root = tmp_path / "templates"
    (overlay_root / "Rte" / "include").mkdir(parents=True)
    (overlay_root / "Rte" / "include" / "Rte_Cfg.h").write_text("/* project overlay */\n", encoding="utf-8")
    gen_ov = CodeGenerator(mod_def, empty_cfg, project_template_dir=overlay_root, package_template_dir=tpl_dir)
    out2 = tmp_path / "out_overlay"
    assert gen_ov.generate_all(out2, flat=True) is True
    assert (out2 / "include" / "Rte_Cfg.h").read_text(encoding="utf-8") == "/* project overlay */\n"


def test_single_module_file_with_multiple_impls_not_filtered_out(tmp_path):
    """Single-ECUC-MODULE-DEF files like VX1000_bswmd (with two impls pointing to VX1000 & VX1000_Next) keep intact."""
    vx_arxml = tmp_path / "VX1000_bswmd.arxml"
    vx_arxml.write_text(
        """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>VX1000</SHORT-NAME></ECUC-MODULE-DEF>
    <BSW-IMPLEMENTATION>
      <SHORT-NAME>VX1000_Impl_Default</SHORT-NAME>
      <VENDOR-SPECIFIC-MODULE-DEF-REFS>
        <VENDOR-SPECIFIC-MODULE-DEF-REF DEST="ECUC-MODULE-DEF">/MICROSAR/VX1000</VENDOR-SPECIFIC-MODULE-DEF-REF>
      </VENDOR-SPECIFIC-MODULE-DEF-REFS>
    </BSW-IMPLEMENTATION>
    <BSW-IMPLEMENTATION>
      <SHORT-NAME>VX1000_Impl</SHORT-NAME>
      <VENDOR-SPECIFIC-MODULE-DEF-REFS>
        <VENDOR-SPECIFIC-MODULE-DEF-REF DEST="ECUC-MODULE-DEF">/MICROSAR/VX1000_Next</VENDOR-SPECIFIC-MODULE-DEF-REF>
      </VENDOR-SPECIFIC-MODULE-DEF-REFS>
    </BSW-IMPLEMENTATION>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""",
        encoding="utf-8",
    )
    sf = SipFile(path=vx_arxml, module="VX1000", content=vx_arxml.read_bytes(), role="def")
    merged = SipMerger.merge_definition([sf], "VX1000")
    assert merged is not None
    root = etree.fromstring(merged)
    impl_names = [
        el.findtext(f"{{{AR_NS}}}SHORT-NAME")
        for el in root.iter(f"{{{AR_NS}}}BSW-IMPLEMENTATION")
    ]
    assert impl_names == ["VX1000_Impl_Default", "VX1000_Impl"]
