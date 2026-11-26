"""Tests for ECUC reference serialization fidelity and DaVinci external model indexing."""

from pathlib import Path
from lxml import etree

from autosar_configurator.core.baseline.compose import _clone_ref as compose_clone_ref
from autosar_configurator.core.baseline.merge import _clone_ref as merge_clone_ref, _set_value
from autosar_configurator.core.davinci_importer import DaVinciProject, DaVinciProjectImporter
from autosar_configurator.core.external_model_index import ExternalModelIndex
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucReferenceValue,
)
from autosar_configurator.core.packages.value_index import _clone_ref as value_index_clone_ref
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer
from autosar_configurator.core.workspace_manager import (
    WorkspaceManager,
    _clone_container_for_switch,
)


class TestReferenceFidelityRoundTrip:
    """Verify VALUE-REF DEST and ECUC-INSTANCE-REFERENCE-VALUE (VALUE-IREF) round-trip."""

    def test_foreign_ref_dest_preserved_through_parse_clone_and_serialize(self, tmp_path: Path):
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>MemMap</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/MemMap</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>MemMapAllocation_0</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/MemMap/MemMapAllocation</DEFINITION-REF>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE>
              <DEFINITION-REF DEST="ECUC-FOREIGN-REFERENCE-DEF">/MICROSAR/MemMap/MemMapAllocation/MemMapSwAddressMethodRef</DEFINITION-REF>
              <VALUE-REF DEST="SW-ADDR-METHOD">/MICROSAR_MemMap/SwAddrMethods/CODE</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
            <ECUC-REFERENCE-VALUE>
              <INDEX>0</INDEX>
              <DEFINITION-REF DEST="ECUC-FOREIGN-REFERENCE-DEF">/MICROSAR/MemMap/MemMapAllocation/MemMapSignalListRef</DEFINITION-REF>
              <VALUE-REF DEST="I-SIGNAL">/ISignal/Sig_A</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
            <ECUC-REFERENCE-VALUE>
              <INDEX>1</INDEX>
              <DEFINITION-REF DEST="ECUC-FOREIGN-REFERENCE-DEF">/MICROSAR/MemMap/MemMapAllocation/MemMapSignalListRef</DEFINITION-REF>
              <VALUE-REF DEST="PDU-TO-FRAME-MAPPING">/CanFrame/Frame_0/PduMap_1</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        parser = ArxmlParser()
        root = etree.fromstring(xml.encode("utf-8"))
        cfg = parser.parse_all_module_configurations(root)[0]

        orig = cfg.containers[0]
        single_ref = orig.reference_values["MemMapSwAddressMethodRef"]
        assert single_ref.dest_type == "ECUC-FOREIGN-REFERENCE-DEF"
        assert single_ref.value_ref_dest == "SW-ADDR-METHOD"
        assert single_ref.is_foreign_reference is True
        assert single_ref.is_instance_reference is False

        multi_refs = orig.multi_reference_values["MemMapSignalListRef"]
        assert [r.value_ref_dest for r in multi_refs] == ["I-SIGNAL", "PDU-TO-FRAME-MAPPING"]

        # Verify all clone helpers preserve metadata
        cloned_container = orig.clone()
        switched_container = _clone_container_for_switch(cloned_container)
        assert switched_container.reference_values["MemMapSwAddressMethodRef"].value_ref_dest == "SW-ADDR-METHOD"
        assert switched_container.multi_reference_values["MemMapSignalListRef"][1].value_ref_dest == "PDU-TO-FRAME-MAPPING"

        for clone_fn in (merge_clone_ref, compose_clone_ref, value_index_clone_ref):
            c_ref = clone_fn(single_ref)
            assert c_ref.dest_type == "ECUC-FOREIGN-REFERENCE-DEF"
            assert c_ref.value_ref_dest == "SW-ADDR-METHOD"

        # Serialize switched clone and verify XML attributes
        out_cfg = EcucModuleConfiguration(
            short_name="MemMap",
            definition_ref=cfg.definition_ref,
            containers=[switched_container],
        )
        out_file = tmp_path / "MemMap_out.arxml"
        EcucValueSerializer().serialize_to_file(out_cfg, out_file)
        out_root = etree.parse(str(out_file)).getroot()
        ns = {"ar": "http://autosar.org/schema/r4.0"}

        val_refs = out_root.xpath(".//ar:ECUC-REFERENCE-VALUE/ar:VALUE-REF", namespaces=ns)
        assert [(e.get("DEST"), e.text) for e in val_refs] == [
            ("SW-ADDR-METHOD", "/MICROSAR_MemMap/SwAddrMethods/CODE"),
            ("I-SIGNAL", "/ISignal/Sig_A"),
            ("PDU-TO-FRAME-MAPPING", "/CanFrame/Frame_0/PduMap_1"),
        ]

        reparsed = parser.parse_all_module_configurations(out_root)[0]
        assert reparsed.containers[0].reference_values["MemMapSwAddressMethodRef"].value_ref_dest == "SW-ADDR-METHOD"
        assert [r.value_ref_dest for r in reparsed.containers[0].multi_reference_values["MemMapSignalListRef"]] == [
            "I-SIGNAL",
            "PDU-TO-FRAME-MAPPING",
        ]

    def test_set_reference_value_and_baseline_set_value_preserve_existing_metadata(self):
        c = EcucContainerValue(
            short_name="Cfg",
            definition_ref="/MICROSAR/MemMap/MemMapAllocation",
        )
        c.set_reference_value(
            "MemMapSwAddressMethodRef",
            "/MICROSAR_MemMap/SwAddrMethods/CODE",
            "/MICROSAR/MemMap/MemMapAllocation/MemMapSwAddressMethodRef",
            dest_type="ECUC-FOREIGN-REFERENCE-DEF",
            value_ref_dest="SW-ADDR-METHOD",
        )
        # Simulate UI command updating path without knowing DEST metadata
        c.set_reference_value(
            "MemMapSwAddressMethodRef",
            "/MICROSAR_MemMap/SwAddrMethods/VAR_INIT",
            "/MICROSAR/MemMap/MemMapAllocation/MemMapSwAddressMethodRef",
        )
        ref = c.reference_values["MemMapSwAddressMethodRef"]
        assert ref.value_ref == "/MICROSAR_MemMap/SwAddrMethods/VAR_INIT"
        assert ref.dest_type == "ECUC-FOREIGN-REFERENCE-DEF"
        assert ref.value_ref_dest == "SW-ADDR-METHOD"

        # Simulate baseline _set_value when source is None
        _set_value(c, "MemMapSwAddressMethodRef", "/MICROSAR_MemMap/SwAddrMethods/CONST", source=None)
        ref_after = c.reference_values["MemMapSwAddressMethodRef"]
        assert ref_after.value_ref == "/MICROSAR_MemMap/SwAddrMethods/CONST"
        assert ref_after.dest_type == "ECUC-FOREIGN-REFERENCE-DEF"
        assert ref_after.value_ref_dest == "SW-ADDR-METHOD"

    def test_instance_reference_value_iref_round_trip(self, tmp_path: Path):
        xml = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>BswM</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/BswM</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>BswMModeRequestPort_0</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/BswM/BswMConfig/BswMModeRequestPort</DEFINITION-REF>
          <REFERENCE-VALUES>
            <ECUC-INSTANCE-REFERENCE-VALUE>
              <DEFINITION-REF DEST="ECUC-INSTANCE-REFERENCE-DEF">/MICROSAR/BswM/BswMConfig/BswMModeRequestPort/BswMBswRequestedModeRef</DEFINITION-REF>
              <VALUE-IREF>
                <CONTEXT-ELEMENT-REF DEST="SW-COMPONENT-PROTOTYPE">/TopLevel/AppSwc</CONTEXT-ELEMENT-REF>
                <CONTEXT-ELEMENT-REF DEST="R-PORT-PROTOTYPE">/ComponentTypes/AppSwc/ModePort</CONTEXT-ELEMENT-REF>
                <TARGET-REF DEST="MODE-DECLARATION">/MICROSAR/BswM_swc/BswMSwitchModeGroup/STARTUP</TARGET-REF>
              </VALUE-IREF>
            </ECUC-INSTANCE-REFERENCE-VALUE>
            <ECUC-INSTANCE-REFERENCE-VALUE>
              <INDEX>0</INDEX>
              <DEFINITION-REF DEST="ECUC-INSTANCE-REFERENCE-DEF">/MICROSAR/BswM/BswMConfig/BswMModeRequestPort/BswMExtraIrefList</DEFINITION-REF>
              <VALUE-IREF>
                <CONTEXT-ELEMENT-REF DEST="SW-COMPONENT-PROTOTYPE">/TopLevel/CompA</CONTEXT-ELEMENT-REF>
                <TARGET-REF DEST="P-PORT-PROTOTYPE">/ComponentTypes/CompA/OutPort</TARGET-REF>
              </VALUE-IREF>
            </ECUC-INSTANCE-REFERENCE-VALUE>
            <ECUC-INSTANCE-REFERENCE-VALUE>
              <INDEX>1</INDEX>
              <DEFINITION-REF DEST="ECUC-INSTANCE-REFERENCE-DEF">/MICROSAR/BswM/BswMConfig/BswMModeRequestPort/BswMExtraIrefList</DEFINITION-REF>
              <VALUE-IREF>
                <CONTEXT-ELEMENT-REF DEST="SW-COMPONENT-PROTOTYPE">/TopLevel/CompB</CONTEXT-ELEMENT-REF>
                <TARGET-REF DEST="P-PORT-PROTOTYPE">/ComponentTypes/CompB/OutPort</TARGET-REF>
              </VALUE-IREF>
            </ECUC-INSTANCE-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
        parser = ArxmlParser()
        root = etree.fromstring(xml.encode("utf-8"))
        cfg = parser.parse_all_module_configurations(root)[0]

        cont = cfg.containers[0]
        iref = cont.reference_values["BswMBswRequestedModeRef"]
        assert iref.is_instance_reference is True
        assert iref.dest_type == "ECUC-INSTANCE-REFERENCE-DEF"
        assert iref.value_ref == "/MICROSAR/BswM_swc/BswMSwitchModeGroup/STARTUP"
        assert iref.value_ref_dest == "MODE-DECLARATION"
        assert iref.context_element_refs == [
            ("SW-COMPONENT-PROTOTYPE", "/TopLevel/AppSwc"),
            ("R-PORT-PROTOTYPE", "/ComponentTypes/AppSwc/ModePort"),
        ]

        multi_irefs = cont.multi_reference_values["BswMExtraIrefList"]
        assert len(multi_irefs) == 2
        assert all(r.is_instance_reference for r in multi_irefs)

        # Clone via all clone helpers
        for clone_fn in (merge_clone_ref, compose_clone_ref, value_index_clone_ref):
            c_iref = clone_fn(iref)
            assert c_iref.is_instance_reference is True
            assert c_iref.context_element_refs == iref.context_element_refs
            assert c_iref.value_ref_dest == "MODE-DECLARATION"

        cloned = _clone_container_for_switch(cont.clone())
        out_cfg = EcucModuleConfiguration(
            short_name="BswM",
            definition_ref=cfg.definition_ref,
            containers=[cloned],
        )
        out_file = tmp_path / "BswM_out.arxml"
        EcucValueSerializer().serialize_to_file(out_cfg, out_file)
        out_root = etree.parse(str(out_file)).getroot()
        ns = {"ar": "http://autosar.org/schema/r4.0"}

        iref_nodes = out_root.xpath(".//ar:ECUC-INSTANCE-REFERENCE-VALUE", namespaces=ns)
        assert len(iref_nodes) == 3

        first_ctx = iref_nodes[0].xpath("./ar:VALUE-IREF/ar:CONTEXT-ELEMENT-REF", namespaces=ns)
        assert [(e.get("DEST"), e.text) for e in first_ctx] == [
            ("SW-COMPONENT-PROTOTYPE", "/TopLevel/AppSwc"),
            ("R-PORT-PROTOTYPE", "/ComponentTypes/AppSwc/ModePort"),
        ]
        first_tgt = iref_nodes[0].xpath("./ar:VALUE-IREF/ar:TARGET-REF", namespaces=ns)[0]
        assert first_tgt.get("DEST") == "MODE-DECLARATION"
        assert first_tgt.text == "/MICROSAR/BswM_swc/BswMSwitchModeGroup/STARTUP"

        reparsed = parser.parse_all_module_configurations(out_root)[0]
        r_iref = reparsed.containers[0].reference_values["BswMBswRequestedModeRef"]
        assert r_iref.context_element_refs == iref.context_element_refs
        assert r_iref.value_ref_dest == "MODE-DECLARATION"
        assert r_iref.value_ref == iref.value_ref

    def test_standard_container_ref_defaults_to_ecuc_container_value_dest(self, tmp_path: Path):
        cont = EcucContainerValue(short_name="C1", definition_ref="/AUTOSAR/EcucDefs/Com/ComCfg")
        cont.set_reference_value("ComTaskRef", "/ActiveEcuC/Os/InitTask", "/AUTOSAR/EcucDefs/Com/ComCfg/ComTaskRef")
        out_cfg = EcucModuleConfiguration(
            short_name="Com",
            definition_ref="/AUTOSAR/EcucDefs/Com",
            containers=[cont],
        )
        out_file = tmp_path / "Com_out.arxml"
        EcucValueSerializer().serialize_to_file(out_cfg, out_file)
        root = etree.parse(str(out_file)).getroot()
        ns = {"ar": "http://autosar.org/schema/r4.0"}
        val_ref = root.xpath(".//ar:ECUC-REFERENCE-VALUE/ar:VALUE-REF", namespaces=ns)[0]
        assert val_ref.get("DEST") == "ECUC-CONTAINER-VALUE"
        assert val_ref.text == "/ActiveEcuC/Os/InitTask"


class TestExternalModelIndex:
    """Verify lightweight read-only external ARXML indexing under system/."""

    def test_indexes_autosar_ib_swc_developer_and_system_files(self, tmp_path: Path):
        system_dir = tmp_path / "system"
        (system_dir / "AUTOSAR").mkdir(parents=True)
        (system_dir / "InternalBehavior").mkdir(parents=True)
        (system_dir / "ServiceComponents").mkdir(parents=True)
        (system_dir / "Developer").mkdir(parents=True)
        (system_dir / "System").mkdir(parents=True)

        (system_dir / "AUTOSAR" / "MemMap_SwAddrMethods.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR_MemMap</SHORT-NAME>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>SwAddrMethods</SHORT-NAME>
          <ELEMENTS>
            <SW-ADDR-METHOD UUID="u-code">
              <SHORT-NAME>CODE</SHORT-NAME>
              <SECTION-INITIALIZATION-POLICY>NO-INIT</SECTION-INITIALIZATION-POLICY>
              <SECTION-TYPE>CODE</SECTION-TYPE>
            </SW-ADDR-METHOD>
          </ELEMENTS>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (system_dir / "InternalBehavior" / "Os_ib_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>Os_ib_bswmd</SHORT-NAME>
          <AR-PACKAGES>
            <AR-PACKAGE>
              <SHORT-NAME>SwAddrMethods</SHORT-NAME>
              <ELEMENTS>
                <SW-ADDR-METHOD>
                  <SHORT-NAME>OS_CONST</SHORT-NAME>
                  <SECTION-TYPE>CONST</SECTION-TYPE>
                </SW-ADDR-METHOD>
              </ELEMENTS>
            </AR-PACKAGE>
          </AR-PACKAGES>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (system_dir / "ServiceComponents" / "BswM_swc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>BswM_swc</SHORT-NAME>
          <ELEMENTS>
            <MODE-DECLARATION-GROUP>
              <SHORT-NAME>ESH_Mode</SHORT-NAME>
              <CATEGORY>EXPLICIT_ORDER</CATEGORY>
              <MODE-DECLARATIONS>
                <MODE-DECLARATION>
                  <SHORT-NAME>STARTUP</SHORT-NAME>
                  <VALUE>0</VALUE>
                </MODE-DECLARATION>
              </MODE-DECLARATIONS>
            </MODE-DECLARATION-GROUP>
          </ELEMENTS>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (system_dir / "Developer" / "DataTypes.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>DataTypes</SHORT-NAME>
      <ELEMENTS>
        <IMPLEMENTATION-DATA-TYPE>
          <SHORT-NAME>AswIoc_CmdGroupType</SHORT-NAME>
          <CATEGORY>STRUCTURE</CATEGORY>
        </IMPLEMENTATION-DATA-TYPE>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (system_dir / "System" / "Communication.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>PDU</SHORT-NAME>
      <ELEMENTS>
        <I-SIGNAL-I-PDU>
          <SHORT-NAME>MCU_TxPdu_01</SHORT-NAME>
          <LENGTH>8</LENGTH>
        </I-SIGNAL-I-PDU>
      </ELEMENTS>
    </AR-PACKAGE>
    <AR-PACKAGE>
      <SHORT-NAME>CanFrame</SHORT-NAME>
      <ELEMENTS>
        <CAN-FRAME>
          <SHORT-NAME>MCU_Frame_01</SHORT-NAME>
          <FRAME-LENGTH>8</FRAME-LENGTH>
          <PDU-TO-FRAME-MAPPINGS>
            <PDU-TO-FRAME-MAPPING>
              <SHORT-NAME>PduMap_01</SHORT-NAME>
              <PDU-REF DEST="I-SIGNAL-I-PDU">/PDU/MCU_TxPdu_01</PDU-REF>
              <START-POSITION>0</START-POSITION>
            </PDU-TO-FRAME-MAPPING>
          </PDU-TO-FRAME-MAPPINGS>
        </CAN-FRAME>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        # Malformed file should not abort indexing of valid files
        (system_dir / "System" / "Broken.arxml").write_text("<NOT_CLOSED", encoding="utf-8")

        index = ExternalModelIndex.load_directory(system_dir)
        assert len(index.errors) == 1
        assert index.errors[0][0] == "System/Broken.arxml"

        code = index.get("/MICROSAR_MemMap/SwAddrMethods/CODE")
        assert code is not None
        assert code.tag == "SW-ADDR-METHOD"
        assert code.source_file == "AUTOSAR/MemMap_SwAddrMethods.arxml"
        assert code.uuid == "u-code"
        assert code.attributes["SECTION-TYPE"] == "CODE"
        assert code.attributes["SECTION-INITIALIZATION-POLICY"] == "NO-INIT"

        assert "/MICROSAR/Os_ib_bswmd/SwAddrMethods/OS_CONST" in index
        mode = index.get("/MICROSAR/BswM_swc/ESH_Mode/STARTUP")
        assert mode is not None
        assert mode.tag == "MODE-DECLARATION"
        assert mode.attributes["VALUE"] == "0"

        dtype = index.get("/DataTypes/AswIoc_CmdGroupType")
        assert dtype is not None
        assert dtype.tag == "IMPLEMENTATION-DATA-TYPE"
        assert dtype.category == "STRUCTURE"

        pdu_map = index.get("/CanFrame/MCU_Frame_01/PduMap_01")
        assert pdu_map is not None
        assert pdu_map.tag == "PDU-TO-FRAME-MAPPING"
        assert pdu_map.attributes["PDU-REF"] == "/PDU/MCU_TxPdu_01"

        assert len(index.find_by_tag("SW-ADDR-METHOD")) == 2


class TestDaVinciImportExternalModelsE2E:
    """End-to-end verification that DaVinci import archives non-ECUC models & preserves foreign refs."""

    def test_davinci_import_archives_system_models_indexes_and_preserves_dest(self, tmp_path: Path):
        sip = tmp_path / "sip"

        # 1. Minimal SIP BSW modules: MemMap + Os
        memmap_bswmd = sip / "Components" / "MemMap" / "BSWMD"
        memmap_bswmd.mkdir(parents=True)
        (memmap_bswmd / "MemMap_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>MemMap</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>MemMapAllocation</SHORT-NAME>
          <REFERENCES>
            <ECUC-FOREIGN-REFERENCE-DEF>
              <SHORT-NAME>MemMapSwAddressMethodRef</SHORT-NAME>
              <DESTINATION-TYPE>SW-ADDR-METHOD</DESTINATION-TYPE>
            </ECUC-FOREIGN-REFERENCE-DEF>
          </REFERENCES>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        os_bswmd = sip / "Components" / "Os" / "BSWMD"
        os_bswmd.mkdir(parents=True)
        (os_bswmd / "Os_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF>
      <SHORT-NAME>Os</SHORT-NAME>
      <CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF>
          <SHORT-NAME>OsOS</SHORT-NAME>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </CONTAINERS>
    </ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        # 2. Source DaVinci application with Config/ECUC + non-ECUC directories
        app_dir = sip / "Applications" / "StartApp"
        cfg_dir = app_dir / "Config"
        (cfg_dir / "ECUC").mkdir(parents=True)
        (cfg_dir / "AUTOSAR").mkdir(parents=True)
        (cfg_dir / "InternalBehavior").mkdir(parents=True)
        (cfg_dir / "ServiceComponents").mkdir(parents=True)
        (cfg_dir / "Developer").mkdir(parents=True)
        (cfg_dir / "System").mkdir(parents=True)

        (cfg_dir / "ECUC" / "StartApp_MemMap_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>MemMap</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/MemMap</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>Alloc_Code</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/MemMap/MemMapAllocation</DEFINITION-REF>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE>
              <DEFINITION-REF DEST="ECUC-FOREIGN-REFERENCE-DEF">/MICROSAR/MemMap/MemMapAllocation/MemMapSwAddressMethodRef</DEFINITION-REF>
              <VALUE-REF DEST="SW-ADDR-METHOD">/MICROSAR_MemMap/SwAddrMethods/CODE</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>Alloc_Os</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/MemMap/MemMapAllocation</DEFINITION-REF>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE>
              <DEFINITION-REF DEST="ECUC-FOREIGN-REFERENCE-DEF">/MICROSAR/MemMap/MemMapAllocation/MemMapSwAddressMethodRef</DEFINITION-REF>
              <VALUE-REF DEST="SW-ADDR-METHOD">/MICROSAR/Os_ib_bswmd/SwAddrMethods/OS_CODE</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (cfg_dir / "ECUC" / "StartApp_Os_ecuc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Os</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Os</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>OsOS</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Os/OsOS</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (cfg_dir / "AUTOSAR" / "MemMap_SwAddrMethods.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR_MemMap</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>SwAddrMethods</SHORT-NAME><ELEMENTS>
      <SW-ADDR-METHOD><SHORT-NAME>CODE</SHORT-NAME><SECTION-TYPE>CODE</SECTION-TYPE></SW-ADDR-METHOD>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (cfg_dir / "InternalBehavior" / "Os_ib_bswmd.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>Os_ib_bswmd</SHORT-NAME><AR-PACKAGES>
      <AR-PACKAGE><SHORT-NAME>SwAddrMethods</SHORT-NAME><ELEMENTS>
        <SW-ADDR-METHOD><SHORT-NAME>OS_CODE</SHORT-NAME><SECTION-TYPE>CODE</SECTION-TYPE></SW-ADDR-METHOD>
      </ELEMENTS></AR-PACKAGE>
    </AR-PACKAGES></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (cfg_dir / "ServiceComponents" / "BswM_swc.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>BswM_swc</SHORT-NAME><ELEMENTS>
      <APPLICATION-SW-COMPONENT-TYPE><SHORT-NAME>BswM</SHORT-NAME></APPLICATION-SW-COMPONENT-TYPE>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (cfg_dir / "Developer" / "StartApp.dcf").write_text("<DCF/>", encoding="utf-8")
        (cfg_dir / "Developer" / "DataTypes.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>DataTypes</SHORT-NAME><ELEMENTS>
    <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>App_StatusType</SHORT-NAME></IMPLEMENTATION-DATA-TYPE>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        (cfg_dir / "System" / "SystemExtract.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>PDU</SHORT-NAME><ELEMENTS>
    <I-SIGNAL-I-PDU><SHORT-NAME>MCU_Status_Pdu</SHORT-NAME></I-SIGNAL-I-PDU>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")

        dpa_file = app_dir / "StartApp.dpa"
        dpa_file.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<ProjectAssistant Version="5.30.35 SP2">
  <Folders>
    <SIP>.\\..\\..</SIP>
    <ECUC>.\\Config\\ECUC</ECUC>
    <BswInternalBehaviour>.\\Config\\InternalBehavior</BswInternalBehaviour>
    <ServiceComponents>.\\Config\\ServiceComponents</ServiceComponents>
    <AUTOSAR>.\\Config\\AUTOSAR</AUTOSAR>
  </Folders>
  <Input>
    <ECUEX>Config\\System\\SystemExtract.arxml</ECUEX>
  </Input>
  <References>
    <DVWorkspace>.\\Config\\Developer\\StartApp.dcf</DVWorkspace>
  </References>
  <Environment>
    <Derivative UUID="UUID-1">THA6206</Derivative>
  </Environment>
  <Display>
    <ModuleDefinitionMappings>
      <ModuleDefinitionMapping ModuleConfigName="MemMap" ModuleDefinitionRef="/MICROSAR/MemMap"/>
      <ModuleDefinitionMapping ModuleConfigName="Os" ModuleDefinitionRef="/MICROSAR/Os"/>
    </ModuleDefinitionMappings>
  </Display>
  <EcucSplitter>
    <Splitter File=".\\Config\\ECUC\\StartApp_MemMap_ecuc.arxml"><Module Name="MemMap"/></Splitter>
    <Splitter File=".\\Config\\ECUC\\StartApp_Os_ecuc.arxml"><Module Name="Os"/></Splitter>
  </EcucSplitter>
</ProjectAssistant>""", encoding="utf-8")

        dv = DaVinciProject.from_file(dpa_file)
        ext_files = [rel for rel, _ in dv.external_model_files()]
        assert ext_files == [
            "AUTOSAR/MemMap_SwAddrMethods.arxml",
            "Developer/DataTypes.arxml",
            "InternalBehavior/Os_ib_bswmd.arxml",
            "ServiceComponents/BswM_swc.arxml",
            "System/SystemExtract.arxml",
        ]
        # ECUC files must never be classified as external model files
        assert not any("ECUC" in rel or rel.endswith("_ecuc.arxml") for rel in ext_files)

        wm = WorkspaceManager()
        target_dir = tmp_path / "out_projects"
        project, report = DaVinciProjectImporter.import_project(
            wm,
            dpa_file,
            target_dir=target_dir,
            project_name="ImportedStartApp",
            include_resources=False,
        )

        # Verify files copied into system/
        system_dir = target_dir / "ImportedStartApp" / "system"
        assert (system_dir / "AUTOSAR" / "MemMap_SwAddrMethods.arxml").is_file()
        assert (system_dir / "InternalBehavior" / "Os_ib_bswmd.arxml").is_file()
        assert (system_dir / "ServiceComponents" / "BswM_swc.arxml").is_file()
        assert (system_dir / "Developer" / "DataTypes.arxml").is_file()
        assert (system_dir / "System" / "SystemExtract.arxml").is_file()
        assert not (system_dir / "ECUC").exists()

        # Verify external model index & lookup helpers on WorkspaceProject
        assert project.external_models.count >= 5
        assert project.get_external_element("/MICROSAR_MemMap/SwAddrMethods/CODE") is not None
        assert project.get_external_element("/MICROSAR/Os_ib_bswmd/SwAddrMethods/OS_CODE") is not None
        assert project.get_external_element("/MICROSAR/BswM_swc/BswM") is not None
        assert project.get_external_element("/DataTypes/App_StatusType") is not None
        assert project.get_external_element("/PDU/MCU_Status_Pdu") is not None
        # get_instance_by_path must remain ECUC-container-only
        assert project.get_instance_by_path("/MICROSAR_MemMap/SwAddrMethods/CODE") is None

        memmap_mgr = project.get_manager("MemMap")
        assert memmap_mgr is not None
        alloc_code = memmap_mgr.configuration.containers[0]
        ref_code = alloc_code.reference_values["MemMapSwAddressMethodRef"]
        resolved_ext = project.resolve_foreign_reference(ref_code)
        assert resolved_ext is not None
        assert resolved_ext.ar_path == "/MICROSAR_MemMap/SwAddrMethods/CODE"
        assert project.build_reverse_reference_index() == 0

        # Verify report metadata and Markdown output
        assert len(report.external_model_files) == 5
        assert report.external_model_elements >= 5
        assert report.resolved_foreign_references == 2
        assert report.unresolved_foreign_references == []
        md = report.to_markdown()
        assert "外部非 ECUC 模型归档与外部引用解析" in md
        assert "已解析外部引用 (Foreign/Instance Ref)：2" in md.replace("**", "")

        # Verify saved config/MemMap.arxml preserves VALUE-REF DEST="SW-ADDR-METHOD"
        saved_memmap = (target_dir / "ImportedStartApp" / "config" / "MemMap.arxml").read_text(encoding="utf-8")
        assert 'DEST="SW-ADDR-METHOD"' in saved_memmap

        # Verify reopening the project reloads external_models automatically
        wm2 = WorkspaceManager()
        reloaded, failed = wm2.load_project(project.path)
        assert failed == []
        assert reloaded.external_models.count == project.external_models.count
        assert reloaded.get_external_element("/PDU/MCU_Status_Pdu") is not None
        assert reloaded.list_external_elements("SW-ADDR-METHOD")[0].tag == "SW-ADDR-METHOD"
