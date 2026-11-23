"""Tests for DaVinci CanTrcv_Tja1041 / Tja1043 / Tja1048 / Tja1145 EB templates."""

from pathlib import Path
import json
import re
from lxml import etree as ET

import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.packages import load_manifest
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.generator.generator import CodeGenerator

MCAL_ROOT = Path("/Users/qlwang/Desktop/test2/MCAL_R440_FuSa")
DAVINCI_ROOT = MCAL_ROOT / "modules/davinci"
DIO_DEF_PATH = MCAL_ROOT / "modules/eb/Dio_THA6_AS440/config/Dio.xdm"
DIO_CFG_PATH = MCAL_ROOT / "config/Dio.arxml"

AR_NS = "http://autosar.org/schema/r4.0"

FAMILY_SPECS = [
    ("CanTrcv_Tja1041", "Tja1041", "5.03.00", "/MICROSAR/CanTrcv_Tja1041/CanTrcv"),
    ("CanTrcv_Tja1043", "Tja1043", "4.06.01", "/MICROSAR/CanTrcv_Tja1043/CanTrcv"),
    ("CanTrcv_Tja1048", "Tja1048", "3.01.00", "/MICROSAR/CanTrcv_Tja1048/CanTrcv"),
    ("CanTrcv_Tja1145", "Tja1145", "3.08.00", "/MICROSAR/CanTrcv_Tja1145/CanTrcv"),
]

pytestmark = pytest.mark.skipif(
    not all((DAVINCI_ROOT / mod / "config/CanTrcv.arxml").exists() for mod, *_ in FAMILY_SPECS),
    reason="Real DaVinci CanTrcv_Tja* BSWMD fixtures not present on this machine",
)


def _parse_module_def_xml(xml_str: str):
    root = ET.fromstring(xml_str.encode("utf-8"))
    mod_def_elem = root.find(f".//{{{AR_NS}}}ECUC-MODULE-DEF")
    assert mod_def_elem is not None
    return EcucDefParser().parse_module_def(mod_def_elem)


def _parse_module_cfg_xml(xml_str: str):
    root = ET.fromstring(xml_str.encode("utf-8"))
    cfg_elem = root.find(f".//{{{AR_NS}}}ECUC-MODULE-CONFIGURATION-VALUES")
    assert cfg_elem is not None
    return ArxmlParser().parse_ecuc_configuration_values(cfg_elem)


def _load_real_dio():
    assert DIO_DEF_PATH.exists() and DIO_CFG_PATH.exists()
    dio_def = EcucDefParser().parse_module_def_file(DIO_DEF_PATH)
    dio_root = ET.parse(str(DIO_CFG_PATH)).getroot()
    dio_cfg_elem = dio_root.find(f".//{{{AR_NS}}}ECUC-MODULE-CONFIGURATION-VALUES")
    assert dio_cfg_elem is not None
    dio_cfg = ArxmlParser().parse_ecuc_configuration_values(dio_cfg_elem)
    return dio_def, dio_cfg


def _build_aux_modules():
    """Create synthetic Icu, EcuM, Dem, Spi, vSet, and EcuC modules for cross-ref resolution."""
    icu_def = _parse_module_def_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>AUTOSAR</SHORT-NAME><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>EcucDefs</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>Icu</SHORT-NAME><CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>IcuConfigSet</SHORT-NAME><SUB-CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>IcuChannel</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF>
      </SUB-CONTAINERS></ECUC-PARAM-CONF-CONTAINER-DEF>
    </CONTAINERS></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )
    icu_cfg = _parse_module_cfg_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Icu</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Icu</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>IcuConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Icu/IcuConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>IcuCh_CanWu</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Icu/IcuConfigSet/IcuChannel</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )

    ecum_def = _parse_module_def_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>AUTOSAR</SHORT-NAME><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>EcucDefs</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>EcuM</SHORT-NAME><CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcuMConfiguration</SHORT-NAME><SUB-CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcuMCommonConfiguration</SHORT-NAME><SUB-CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcuMWakeupSource</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF>
        </SUB-CONTAINERS></ECUC-PARAM-CONF-CONTAINER-DEF>
      </SUB-CONTAINERS></ECUC-PARAM-CONF-CONTAINER-DEF>
    </CONTAINERS></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )
    ecum_cfg = _parse_module_cfg_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>EcuM</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/EcuM</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>EcuMConfiguration</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>EcuMCommonConfiguration</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration</DEFINITION-REF>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>WU_CAN0</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DEFINITION-REF>
                </ECUC-CONTAINER-VALUE>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>WU_POR</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DEFINITION-REF>
                </ECUC-CONTAINER-VALUE>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>WU_SYSERR</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DEFINITION-REF>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )

    dem_def = _parse_module_def_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>AUTOSAR</SHORT-NAME><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>EcucDefs</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>Dem</SHORT-NAME><CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>DemConfigSet</SHORT-NAME><SUB-CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>DemEventParameter</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF>
      </SUB-CONTAINERS></ECUC-PARAM-CONF-CONTAINER-DEF>
    </CONTAINERS></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )
    dem_cfg = _parse_module_cfg_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Dem</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Dem</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>DemConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dem/DemConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>DEM_CANTRCV_BUS_ERR</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )

    spi_def = _parse_module_def_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>AUTOSAR</SHORT-NAME><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>EcucDefs</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>Spi</SHORT-NAME><CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiDriver</SHORT-NAME><SUB-CONTAINERS>
        <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiChannel</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF>
        <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiJob</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE><SUB-CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiChannelList</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
            <PARAMETERS><ECUC-INTEGER-PARAM-DEF><SHORT-NAME>SpiChannelIndex</SHORT-NAME><DEFAULT-VALUE>0</DEFAULT-VALUE></ECUC-INTEGER-PARAM-DEF></PARAMETERS>
            <REFERENCES><ECUC-REFERENCE-DEF><SHORT-NAME>SpiChannelAssignment</SHORT-NAME><DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DESTINATION-REF></ECUC-REFERENCE-DEF></REFERENCES>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </SUB-CONTAINERS></ECUC-PARAM-CONF-CONTAINER-DEF>
        <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiSequence</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
          <REFERENCES><ECUC-REFERENCE-DEF><SHORT-NAME>SpiJobAssignment</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE><DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob</DESTINATION-REF></ECUC-REFERENCE-DEF></REFERENCES>
        </ECUC-PARAM-CONF-CONTAINER-DEF>
      </SUB-CONTAINERS></ECUC-PARAM-CONF-CONTAINER-DEF>
    </CONTAINERS></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )
    spi_cfg = _parse_module_cfg_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Spi</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Spi</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiDriver</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiCh_Tja_0</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiCh_Tja_1</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiCh_Tja_2</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiCh_Tja_3</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiJob_Large</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob</DEFINITION-REF>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>ChList_3</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList</DEFINITION-REF>
                  <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelIndex</DEFINITION-REF><VALUE>3</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
                  <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiCh_Tja_3</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                </ECUC-CONTAINER-VALUE>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>ChList_0</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList</DEFINITION-REF>
                  <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelIndex</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
                  <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiCh_Tja_0</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                </ECUC-CONTAINER-VALUE>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>ChList_2</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList</DEFINITION-REF>
                  <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelIndex</DEFINITION-REF><VALUE>2</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
                  <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiCh_Tja_2</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                </ECUC-CONTAINER-VALUE>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>ChList_1</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList</DEFINITION-REF>
                  <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelIndex</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
                  <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiCh_Tja_1</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiSeq_Tja_Large</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence</DEFINITION-REF>
              <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence/SpiJobAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiJob_Large</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiSeq_Tja_Medium</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiSeq_Tja_Normal</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )

    vset_def = _parse_module_def_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>vSet</SHORT-NAME><CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>vSetGeneral</SHORT-NAME><PARAMETERS>
        <ECUC-ENUMERATION-PARAM-DEF><SHORT-NAME>vSetDummyStatementKind</SHORT-NAME><DEFAULT-VALUE>SelfAssignment</DEFAULT-VALUE></ECUC-ENUMERATION-PARAM-DEF>
      </PARAMETERS></ECUC-PARAM-CONF-CONTAINER-DEF>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>vSetPlatform</SHORT-NAME><PARAMETERS>
        <ECUC-ENUMERATION-PARAM-DEF><SHORT-NAME>vSetBitOrder</SHORT-NAME><DEFAULT-VALUE>LSB_to_MSB</DEFAULT-VALUE></ECUC-ENUMERATION-PARAM-DEF>
      </PARAMETERS></ECUC-PARAM-CONF-CONTAINER-DEF>
    </CONTAINERS></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )
    vset_cfg = _parse_module_cfg_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>vSet</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vSet</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>vSetGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/vSet/vSetGeneral</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind</DEFINITION-REF><VALUE>VoidCast</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>vSetPlatform</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/vSet/vSetPlatform</DEFINITION-REF>
          <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/vSet/vSetPlatform/vSetBitOrder</DEFINITION-REF><VALUE>MSB_to_LSB</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )

    ecuc_def = _parse_module_def_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-DEF><SHORT-NAME>EcuC</SHORT-NAME><CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcucGeneral</SHORT-NAME><PARAMETERS>
        <ECUC-BOOLEAN-PARAM-DEF><SHORT-NAME>AtomicBitAccessInBitfield</SHORT-NAME><DEFAULT-VALUE>false</DEFAULT-VALUE></ECUC-BOOLEAN-PARAM-DEF>
        <ECUC-ENUMERATION-PARAM-DEF><SHORT-NAME>AtomicVariableAccess</SHORT-NAME><DEFAULT-VALUE>Atomic32BitAccess</DEFAULT-VALUE></ECUC-ENUMERATION-PARAM-DEF>
      </PARAMETERS></ECUC-PARAM-CONF-CONTAINER-DEF>
    </CONTAINERS></ECUC-MODULE-DEF>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )
    ecuc_cfg = _parse_module_cfg_xml(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>EcuC</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuC</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>EcucGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess</DEFINITION-REF><VALUE>Atomic16BitAccess</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""
    )

    return {
        "Icu": (icu_def, icu_cfg),
        "EcuM": (ecum_def, ecum_cfg),
        "Dem": (dem_def, dem_cfg),
        "Spi": (spi_def, spi_cfg),
        "vSet": (vset_def, vset_cfg),
        "EcuC": (ecuc_def, ecuc_cfg),
    }


def _check_template_directives_balanced(tmpl_path: Path):
    txt = tmpl_path.read_text(encoding="utf-8")
    assert "ecu:get" not in txt
    assert "Vector Informatik" not in txt
    assert "BETA VERSION" not in txt
    assert len(re.findall(r"\[!IF\b", txt)) == len(re.findall(r"\[!ENDIF\b", txt))
    assert len(re.findall(r"\[!LOOP\b", txt)) == len(re.findall(r"\[!ENDLOOP\b", txt))
    assert len(re.findall(r"\[!SELECT\b", txt)) == len(re.findall(r"\[!ENDSELECT\b", txt))


def _audit_rendered_output(text: str, label: str):
    assert "[!" not in text, f"{label}: unrendered [! directive found"
    assert "!]" not in text, f"{label}: unrendered !] directive found"
    assert "0x0x" not in text, f"{label}: double 0x0x hex prefix found"
    # Check balanced #if/#ifdef/#ifndef and #endif
    if_count = len(re.findall(r"^\s*#\s*(?:if|ifdef|ifndef)\b", text, flags=re.M))
    endif_count = len(re.findall(r"^\s*#\s*endif\b", text, flags=re.M))
    assert if_count == endif_count, f"{label}: unbalanced #if ({if_count}) vs #endif ({endif_count})"
    # Check duplicate non-MemMap #define macros
    seen = set()
    for m in re.finditer(r"^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)", text, flags=re.M):
        name = m.group(1)
        if "_START_SEC_" in name or "_STOP_SEC_" in name:
            continue
        assert name not in seen, f"{label}: duplicate #define {name}"
        seen.add(name)


def _render_module(mod_dir_name: str, infix: str, cfg_xml: str, tmp_path: Path, extra_modules=None):
    pkg_dir = DAVINCI_ROOT / mod_dir_name
    manifest = load_manifest(pkg_dir)
    pkg = ModulePackage(pkg_dir, manifest)
    mod_def = EcucDefParser().parse_module_def_file(pkg.definition_file(None))
    cfg = _parse_module_cfg_xml(cfg_xml)
    mgr = ConfigurationManager(mod_def)
    mgr.configuration = cfg

    all_cfgs = {"CanTrcv": (mod_def, cfg)}
    if extra_modules:
        all_cfgs.update(extra_modules)

    gen = CodeGenerator(
        mod_def,
        cfg,
        all_configurations=all_cfgs,
        package_template_dir=pkg.template_dir(),
    )
    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is True, f"Generation failed for {mod_dir_name}: {gen.last_status} {gen.warnings}"
    assert gen.last_status == "generated"
    assert gen.warnings == [], f"Unexpected warnings for {mod_dir_name}: {gen.warnings}"

    h_path = tmp_path / "include" / f"CanTrcv_30_{infix}_Cfg.h"
    c_path = tmp_path / "src" / f"CanTrcv_30_{infix}_Cfg.c"
    assert h_path.exists() and c_path.exists()
    h_txt = h_path.read_text(encoding="utf-8")
    c_txt = c_path.read_text(encoding="utf-8")
    _audit_rendered_output(h_txt, f"{mod_dir_name} Cfg.h")
    _audit_rendered_output(c_txt, f"{mod_dir_name} Cfg.c")
    return h_txt, c_txt


def _dio_pin_xml(def_prefix: str, short_name: str, if_name: str, dio_ref: str) -> str:
    return f"""
        <ECUC-CONTAINER-VALUE><SHORT-NAME>{short_name}</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_prefix}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">{def_prefix}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvHardwareInterfaceName</DEFINITION-REF>
              <VALUE>{if_name}</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE>
              <DEFINITION-REF DEST="ECUC-CHOICE-REFERENCE-DEF">{def_prefix}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvDioSymNameRef</DEFINITION-REF>
              <VALUE-REF DEST="ECUC-CONTAINER-VALUE">{dio_ref}</VALUE-REF>
            </ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>"""


@pytest.mark.parametrize("mod_dir,infix,version,def_ref", FAMILY_SPECS)
def test_family_manifests_and_templates_audit(mod_dir, infix, version, def_ref):
    pkg_dir = DAVINCI_ROOT / mod_dir
    raw = json.loads((pkg_dir / "module.json").read_text(encoding="utf-8"))
    assert raw["templates"] == "templates"
    assert raw["version"] == version

    manifest = load_manifest(pkg_dir)
    assert manifest.templates == "templates"
    assert manifest.definition == def_ref

    pkg = ModulePackage(pkg_dir, manifest)
    tdir = pkg.template_dir()
    assert tdir is not None and tdir.is_dir()

    h_tmpl = tdir / "include" / f"CanTrcv_30_{infix}_Cfg.h"
    c_tmpl = tdir / "src" / f"CanTrcv_30_{infix}_Cfg.c"
    assert h_tmpl.is_file()
    assert c_tmpl.is_file()
    _check_template_directives_balanced(h_tmpl)
    _check_template_directives_balanced(c_tmpl)


def test_tja1041_default_and_custom_wake_pin_configs(tmp_path):
    def_ref = "/MICROSAR/CanTrcv_Tja1041/CanTrcv"

    minimal_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch0</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_min, c_min = _render_module("CanTrcv_Tja1041", "Tja1041", minimal_xml, tmp_path / "min")
    assert "#define DRVTRANS_CAN_30_TJA1041_GENTOOL_CFG5_MAJOR_VERSION 0x03u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1041_GENTOOL_CFG5_MINOR_VERSION 0x02u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1041_GENTOOL_CFG5_PATCH_VERSION 0x00u" in h_min
    assert "0x01050103u" in h_min
    assert "#define CANTRCV_30_TJA1041_WAKE_PIN_USED" in h_min and "STD_OFF" in h_min
    assert "#define CANTRCV_30_TJA1041_WAKEUPWAITTIMEFCTLIST" in h_min
    assert "PinWAKEOfDioConfiguration" not in h_min
    assert "{ /* 0 */ 0xFFu, 0xFFu, 0xFFu }" in c_min
    assert "CanTrcv_30_Tja1041_WakeupWaitTimeFctList" not in c_min

    # Custom 2-channel out-of-order with real Dio, WakePin, deduped wait function, Icu, EcuM, Dem, UserConfigFile
    dio_def, dio_cfg = _load_real_dio()
    aux = _build_aux_modules()
    aux["Dio"] = (dio_def, dio_cfg)

    pins_ch0 = (
        _dio_pin_xml(def_ref, "PinEN", "PinEN", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT1")
        + _dio_pin_xml(def_ref, "PinERR", "PinERR", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_IN1")
        + _dio_pin_xml(def_ref, "PinSTB", "PinSTB", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT2")
        + _dio_pin_xml(def_ref, "PinWAKE", "PinWAKE", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT3")
    )
    custom_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvGetVersionInfo</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvUserConfigFile</DEFINITION-REF><VALUE>CanTrcv_User.h</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch_Second</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-FUNCTION-NAME-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupWaitTimeFunction</DEFINITION-REF><VALUE>Appl_WaitWakePin</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch_First</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupByBusUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-FUNCTION-NAME-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupWaitTimeFunction</DEFINITION-REF><VALUE>Appl_WaitWakePin</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvIcuChannelRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Icu/IcuConfigSet/IcuCh_CanWu</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WU_CAN0</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvDioAccess</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess</DEFINITION-REF>
                      <SUB-CONTAINERS>{pins_ch0}</SUB-CONTAINERS>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvDemEventParameterRefs</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvDemEventParameterRefs</DEFINITION-REF>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvDemEventParameterRefs/CANTRCV_E_BUS_ERROR</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Dem/DemConfigSet/DEM_CANTRCV_BUS_ERR</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_cus, c_cus = _render_module("CanTrcv_Tja1041", "Tja1041", custom_xml, tmp_path / "cus", aux)
    assert '#include "Icu.h"' in h_cus
    assert '#include "Dem.h"' in h_cus
    assert '#include "CanTrcv_User.h"' in h_cus
    assert "#define CANTRCV_30_TJA1041_WAKE_PIN_USED" in h_cus
    assert re.search(r"#define\s+CANTRCV_30_TJA1041_WAKE_PIN_USED\s+STD_ON", h_cus)
    assert "PinWAKEOfDioConfiguration" in h_cus
    assert h_cus.count("Appl_WaitWakePin(void);") == 1
    assert "DioConf_DioChannel_DIO_TEST_OUT1, DioConf_DioChannel_DIO_TEST_IN1, DioConf_DioChannel_DIO_TEST_OUT2, DioConf_DioChannel_DIO_TEST_OUT3" in c_cus
    assert "CanTrcv_30_Tja1041_WakeupWaitTimeFctList[2]" in c_cus
    assert "Appl_WaitWakePin" in c_cus
    assert "IcuConf_IcuChannel_IcuCh_CanWu" in c_cus
    assert "EcuMConf_EcuMWakeupSource_WU_CAN0" in c_cus


def test_tja1043_default_tle9252_and_mixed_variant_configs(tmp_path):
    def_ref = "/MICROSAR/CanTrcv_Tja1043/CanTrcv"

    # 1) Minimal default: ECUC_SAFE_BSW_CHECKS STD_ON, HW_REFERENCE_GROUP_TJA1043, SWETIMERUSED STD_OFF
    minimal_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch0</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_min, c_min = _render_module("CanTrcv_Tja1043", "Tja1043", minimal_xml, tmp_path / "min")
    assert "#define DRVTRANS_CAN_30_TJA1043_GENTOOL_CFG5_MAJOR_VERSION 0x03u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1043_GENTOOL_CFG5_MINOR_VERSION 0x04u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1043_GENTOOL_CFG5_PATCH_VERSION 0x01u" in h_min
    assert "0x01050105u" in h_min
    assert re.search(r"#define\s+CANTRCV_30_TJA1043_ECUC_SAFE_BSW_CHECKS\s+STD_ON", h_min)
    assert "#define CANTRCV_30_TJA1043_HW_REFERENCE_GROUP_TJA1043" in h_min
    assert "HW_REFERENCE_GROUP_TLE9252" not in h_min
    assert re.search(r"#define\s+CANTRCV_30_TJA1043_SET_OP_MODE_WAIT_TIME_SUPPORT\s+STD_OFF", h_min)
    assert "SET_OP_MODE_ANY_WAIT_TIME_USEC" not in h_min
    assert re.search(r"#define\s+CANTRCV_30_TJA1043_SWETIMERUSED\s+STD_OFF", h_min)
    assert "{ /* 0 */ 0xFFu, 0xFFu, 0xFFu, 0xFFu }" in c_min

    # 2) All-TLE9252 with Timer_1us16bit + CanTrcvWaitTime=50 + CanTrcvSweTimerUsed=true (ignored for TLE9252)
    tle_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvTimerType</DEFINITION-REF><VALUE>Timer_1us16bit</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvWaitTime</DEFINITION-REF><VALUE>50</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch0</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvHardwareVariantGroup</DEFINITION-REF><VALUE>TLE9252_REFERENCE_GROUP</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvSweTimerUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_tle, c_tle = _render_module("CanTrcv_Tja1043", "Tja1043", tle_xml, tmp_path / "tle")
    assert "#define CANTRCV_30_TJA1043_HW_REFERENCE_GROUP_TLE9252" in h_tle
    assert "HW_REFERENCE_GROUP_TJA1043" not in h_tle
    assert re.search(r"#define\s+CANTRCV_30_TJA1043_SET_OP_MODE_WAIT_TIME_SUPPORT\s+STD_ON", h_tle)
    assert re.search(r"#define\s+CANTRCV_30_TJA1043_SET_OP_MODE_ANY_WAIT_TIME_USEC\s+50u", h_tle)
    assert re.search(r"#define\s+CANTRCV_30_TJA1043_SWETIMERUSED\s+STD_OFF", h_tle)
    assert "/* 0 */ 0x01u" in c_tle

    # 3) Mixed Ch0 TJA1043 (with CanTrcvSweTimerUsed=true) + Ch1 TLE9252 with real 4-pin Dio
    dio_def, dio_cfg = _load_real_dio()
    pins_ch0 = (
        _dio_pin_xml(def_ref, "PinEN", "PinEN", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT1")
        + _dio_pin_xml(def_ref, "PinERR", "PinERR", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_IN1")
        + _dio_pin_xml(def_ref, "PinRXD", "PinRXD", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT2")
        + _dio_pin_xml(def_ref, "PinSTB", "PinSTB", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT3")
    )
    mixed_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch1_Tle</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvHardwareVariantGroup</DEFINITION-REF><VALUE>TLE9252_REFERENCE_GROUP</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch0_Tja</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvHardwareVariantGroup</DEFINITION-REF><VALUE>TJA1043_REFERENCE_GROUP</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvSweTimerUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvDioAccess</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess</DEFINITION-REF>
                      <SUB-CONTAINERS>{pins_ch0}</SUB-CONTAINERS>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_mix, c_mix = _render_module(
        "CanTrcv_Tja1043", "Tja1043", mixed_xml, tmp_path / "mix", {"Dio": (dio_def, dio_cfg)}
    )
    assert "HW_REFERENCE_GROUP_TJA1043" not in h_mix
    assert "HW_REFERENCE_GROUP_TLE9252" not in h_mix
    assert re.search(r"#define\s+CANTRCV_30_TJA1043_SWETIMERUSED\s+STD_ON", h_mix)
    assert "DioConf_DioChannel_DIO_TEST_OUT1, DioConf_DioChannel_DIO_TEST_IN1, DioConf_DioChannel_DIO_TEST_OUT2, DioConf_DioChannel_DIO_TEST_OUT3" in c_mix
    assert "/* 0 */ 0x00u" in c_mix and "/* 1 */ 0x01u" in c_mix
    assert "CanTrcv_30_Tja1043_SweTimerUsed[2]" in c_mix
    assert "/* 0 */ TRUE," in c_mix and "/* 1 */ FALSE" in c_mix


def test_tja1048_default_and_custom_configs(tmp_path):
    def_ref = "/MICROSAR/CanTrcv_Tja1048/CanTrcv"

    minimal_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch0</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_min, c_min = _render_module("CanTrcv_Tja1048", "Tja1048", minimal_xml, tmp_path / "min")
    assert "#define DRVTRANS_CAN_30_TJA1048_GENTOOL_CFG5_MAJOR_VERSION 0x03u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1048_GENTOOL_CFG5_MINOR_VERSION 0x01u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1048_GENTOOL_CFG5_PATCH_VERSION 0x00u" in h_min
    assert "0x01050102u" in h_min
    assert "{ /* 0 */ 0xFFu, 0xFFu }" in c_min

    dio_def, dio_cfg = _load_real_dio()
    aux = _build_aux_modules()
    aux["Dio"] = (dio_def, dio_cfg)
    pins_ch0 = (
        _dio_pin_xml(def_ref, "PinRXD", "PinRXD", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_IN1")
        + _dio_pin_xml(def_ref, "PinSTB", "PinSTB", "/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT1")
    )
    custom_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvWakeUpSupport</DEFINITION-REF><VALUE>CANTRCV_WAKEUP_NOT_SUPPORTED</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvUserConfigFile</DEFINITION-REF><VALUE>Tja1048_User.h</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch_B</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelUsed</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch_A</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupByBusUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvIcuChannelRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Icu/IcuConfigSet/IcuCh_CanWu</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WU_CAN0</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPorWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WU_POR</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvDioAccess</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess</DEFINITION-REF>
                      <SUB-CONTAINERS>{pins_ch0}</SUB-CONTAINERS>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvDemEventParameterRefs</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvDemEventParameterRefs</DEFINITION-REF>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvDemEventParameterRefs/CANTRCV_E_BUS_ERROR</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Dem/DemConfigSet/DEM_CANTRCV_BUS_ERR</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_cus, c_cus = _render_module("CanTrcv_Tja1048", "Tja1048", custom_xml, tmp_path / "cus", aux)
    assert "#define CANTRCV_30_TJA1048_GENERAL_WAKE_UP_SUPPORT           CANTRCV_30_TJA1048_WAKEUP_NOT_SUPPORTED" in h_cus
    assert "#define CANTRCV_30_TJA1048_DUMMY_STATEMENT(v) (void)(v)" in h_cus
    assert "#define CANTRCV_30_TJA1048_CPUTYPE_BITORDER_MSB2LSB" in h_cus
    assert "#define CANTRCV_30_TJA1048_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON" in h_cus
    assert "#define CANTRCV_30_TJA1048_ATOMIC_VARIABLE_ACCESS 16u" in h_cus
    assert '#include "Icu.h"' in h_cus and '#include "Dem.h"' in h_cus and '#include "Tja1048_User.h"' in h_cus
    assert "#define CanTrcv_30_Tja1048_Ch_A 0u" in h_cus and "#define CanTrcv_30_Tja1048_Ch_B 1u" in h_cus
    assert "{ /* 0 */ DioConf_DioChannel_DIO_TEST_IN1, DioConf_DioChannel_DIO_TEST_OUT1 }," in c_cus
    assert "/* 0 */ TRUE," in c_cus and "/* 1 */ FALSE" in c_cus
    assert "EcuMConf_EcuMWakeupSource_WU_POR" in c_cus


def test_tja1145_default_custom_and_sync_no_pn_configs(tmp_path):
    def_ref = "/MICROSAR/CanTrcv_Tja1145/CanTrcv"

    # 1) Minimal default
    minimal_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch0</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_min, c_min = _render_module("CanTrcv_Tja1145", "Tja1145", minimal_xml, tmp_path / "min")
    assert '#include "Spi.h"' in h_min
    assert "#define DRVTRANS_CAN_30_TJA1145_GENTOOL_CFG5_MAJOR_VERSION 0x03u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1145_GENTOOL_CFG5_MINOR_VERSION 0x04u" in h_min
    assert "#define DRVTRANS_CAN_30_TJA1145_GENTOOL_CFG5_PATCH_VERSION 0x00u" in h_min
    assert "0x01050105u" in h_min
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_HW_PN_SUPPORT\s+STD_ON", h_min)
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_FD_TOLERANCE\s+STD_OFF", h_min)
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_FDTOLERANCEENABLED\s+STD_OFF", h_min)
    assert "CanTrcv_30_Tja1145_SpiIndicationN_Ch0(void);" in h_min
    assert "CanTrcv_30_Tja1145_SpiIndicationM_Ch0(void);" in h_min
    assert "CanTrcv_30_Tja1145_SpiIndicationL_Ch0(void);" in h_min
    assert "CanTrcv_30_Tja1145_SpiIndicationN_Ch0(void)" in c_min
    assert "5u  /* (=500 KBit/s) */" in c_min
    assert "0x48u }" in c_min
    assert "{ /* 0 */ 0xFFu, 0xFFu, 0xFFu, 0xFFu }" in c_min

    # 2) Custom 2-channel out-of-order with Timer/WaitTime=220, FD tolerance, Ext/Std PN, DataMask shift, 4 SPI ch + 3 SPI seq
    aux = _build_aux_modules()
    custom_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvTimerType</DEFINITION-REF><VALUE>Timer_1us16bit</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvGeneral/CanTrcvWaitTime</DEFINITION-REF><VALUE>220</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch_Std</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvFdTolerance</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvEnablePNMD</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvPartialNetwork</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork</DEFINITION-REF>
                  <PARAMETER-VALUES>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvBaudRate</DEFINITION-REF><VALUE>50</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnEnabled</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnCanIdIsExtended</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanId</DEFINITION-REF><VALUE>1365</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanIdMask</DEFINITION-REF><VALUE>2047</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDlc</DEFINITION-REF><VALUE>4</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                  </PARAMETER-VALUES>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>Mask0</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec</DEFINITION-REF>
                      <PARAMETER-VALUES>
                        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMaskIndex</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMask</DEFINITION-REF><VALUE>171</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                      </PARAMETER-VALUES>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch_Ext</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvFdTolerance</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvEnablePNMD</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupByBusUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvIcuChannelRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Icu/IcuConfigSet/IcuCh_CanWu</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WU_CAN0</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvSyserrWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WU_SYSERR</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvSpiSequence</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence</DEFINITION-REF>
                      <SUB-CONTAINERS>
                        <ECUC-CONTAINER-VALUE><SHORT-NAME>SeqLarge</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess</DEFINITION-REF>
                          <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceIdentifier</DEFINITION-REF><VALUE>SeqRWDataLarge</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
                          <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceName</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiSeq_Tja_Large</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                        <ECUC-CONTAINER-VALUE><SHORT-NAME>SeqMedium</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess</DEFINITION-REF>
                          <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceIdentifier</DEFINITION-REF><VALUE>SeqRWDataMedium</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
                          <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceName</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiSeq_Tja_Medium</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                        <ECUC-CONTAINER-VALUE><SHORT-NAME>SeqNormal</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess</DEFINITION-REF>
                          <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceIdentifier</DEFINITION-REF><VALUE>SeqRWDataNormal</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
                          <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceName</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Spi/SpiDriver/SpiSeq_Tja_Normal</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                      </SUB-CONTAINERS>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvPartialNetwork</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork</DEFINITION-REF>
                  <PARAMETER-VALUES>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvBaudRate</DEFINITION-REF><VALUE>1000</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnEnabled</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnCanIdIsExtended</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanId</DEFINITION-REF><VALUE>305419896</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanIdMask</DEFINITION-REF><VALUE>536870911</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDlc</DEFINITION-REF><VALUE>6</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                  </PARAMETER-VALUES>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>Mask0</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec</DEFINITION-REF>
                      <PARAMETER-VALUES>
                        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMaskIndex</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMask</DEFINITION-REF><VALUE>170</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                      </PARAMETER-VALUES>
                    </ECUC-CONTAINER-VALUE>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>Mask5</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec</DEFINITION-REF>
                      <PARAMETER-VALUES>
                        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMaskIndex</DEFINITION-REF><VALUE>5</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMask</DEFINITION-REF><VALUE>85</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                      </PARAMETER-VALUES>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvDemEventParameterRefs</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvDemEventParameterRefs</DEFINITION-REF>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvDemEventParameterRefs/CANTRCV_E_BUS_ERROR</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Dem/DemConfigSet/DEM_CANTRCV_BUS_ERR</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_cus, c_cus = _render_module("CanTrcv_Tja1145", "Tja1145", custom_xml, tmp_path / "cus", aux)
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT\s+STD_ON", h_cus)
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_SET_OP_MODE_ANY_WAIT_TIME_USEC\s+220u", h_cus)
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_FD_TOLERANCE\s+STD_ON", h_cus)
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_FDTOLERANCEENABLED\s+STD_ON", h_cus)
    assert "CanTrcv_30_Tja1145_IsFdToleranceEnabled(Index)" in h_cus
    assert "CanTrcv_30_Tja1145_FdToleranceEnabled[2]" in c_cus
    assert "/* 0 */ TRUE,  /* CanTrcvFdTolerance */" in c_cus
    assert "/* 1 */ FALSE  /* CanTrcvFdTolerance */" in c_cus
    # Ch0: Ext ID 0x12345678, 1000kbps->7u, DLC=6, EN_PNMD=true => id0=0x78, id1=0x56, id2=0x34, id3=0x12, fc=0xC6
    assert "/* 0 */ 7u  /* (=1000 KBit/s) */, 0x78u  /* (CanId = 0x12345678u) */, 0x56u, 0x34u, 0x12u" in c_cus
    assert "0xC6u }," in c_cus
    # Ch0 DataMask: DLC=6 => offset +2 => idx 0 (0xAA)->DM2, idx 5 (0x55)->DM7
    assert "{ /* 0 */ 0x00u, 0x00u, 0xAAu, 0x00u, 0x00u, 0x00u, 0x00u, 0x55u }," in c_cus
    # Ch1: Std ID 0x555, 50kbps->0u, DLC=4, EN_PNMD=false => id2=0x54, id3=0x15, fc=0x04
    assert "/* 1 */ 0u  /* (=50 KBit/s) */, 0x00u  /* (CanId = 0x00000555u) */, 0x00u, 0x54u, 0x15u" in c_cus
    assert "0x04u }" in c_cus
    # Ch1 DataMask: DLC=4 => offset +4 => idx 0 (0xAB)->DM4
    assert "{ /* 1 */ 0x00u, 0x00u, 0x00u, 0x00u, 0xABu, 0x00u, 0x00u, 0x00u }" in c_cus
    # 4 resolved SPI channels + 3 resolved SPI sequences
    assert "{ /* 0 */ SpiConf_SpiChannel_SpiCh_Tja_0, SpiConf_SpiChannel_SpiCh_Tja_1, SpiConf_SpiChannel_SpiCh_Tja_2, SpiConf_SpiChannel_SpiCh_Tja_3 }," in c_cus
    assert "{ /* 0 */ SpiConf_SpiSequence_SpiSeq_Tja_Large, SpiConf_SpiSequence_SpiSeq_Tja_Medium, SpiConf_SpiSequence_SpiSeq_Tja_Normal }," in c_cus
    assert '#include "Icu.h"' in h_cus and '#include "Dem.h"' in h_cus

    # 3) Synchronous SPI + CanTrcvHwPnSupport=false
    sync_no_pn_xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="{AR_NS}">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">{def_ref}</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>Ch0</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvHwPnSupport</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvSpiSequence</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence</DEFINITION-REF>
                      <PARAMETER-VALUES>
                        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiAccessSynchronous</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                      </PARAMETER-VALUES>
                      <SUB-CONTAINERS>
                        <ECUC-CONTAINER-VALUE><SHORT-NAME>SeqSync</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess</DEFINITION-REF>
                          <PARAMETER-VALUES>
                            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiAccessSynchronous</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">{def_ref}/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceIdentifier</DEFINITION-REF><VALUE>SeqRWDataNormal</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
                          </PARAMETER-VALUES>
                        </ECUC-CONTAINER-VALUE>
                      </SUB-CONTAINERS>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    h_sync, c_sync = _render_module("CanTrcv_Tja1145", "Tja1145", sync_no_pn_xml, tmp_path / "sync")
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_HW_PN_SUPPORT\s+STD_OFF", h_sync)
    assert re.search(r"#define\s+CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS\s+STD_ON", h_sync)
    assert "CanTrcv_30_Tja1145_PnEnabled" not in h_sync
    assert "CanTrcv_30_Tja1145_PnEnabled" not in c_sync
    assert "SpiIndicationN_" not in h_sync
    assert "SpiIndicationN_" not in c_sync
