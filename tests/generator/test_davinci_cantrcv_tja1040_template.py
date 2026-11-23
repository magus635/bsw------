import re
from pathlib import Path

import pytest
from lxml import etree

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
from autosar_configurator.core.packages import load_manifest
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.generator.generator import CodeGenerator


TJA1040_PKG_DIR = Path(
    "/Users/qlwang/Desktop/test2/MCAL_R440_FuSa/modules/davinci/CanTrcv_Tja1040"
)
TJA1040_TEMPLATE_DIR = TJA1040_PKG_DIR / "templates"
TJA1040_BSWMD = TJA1040_PKG_DIR / "config" / "CanTrcv.arxml"
SIP_TJA1040_BSWMD = Path(
    "/Users/qlwang/Desktop/未命名文件夹/mcuapp/Components/CanTrcv_30_Tja1040/BSWMD/CanTrcv_30_Tja1040_bswmd.arxml"
)
TEST2_DIO_XDM = Path(
    "/Users/qlwang/Desktop/test2/MCAL_R440_FuSa/modules/eb/Dio_THA6_AS440/config/Dio.xdm"
)
TEST2_DIO_ARXML = Path(
    "/Users/qlwang/Desktop/test2/MCAL_R440_FuSa/config/Dio.arxml"
)


def _find_tja1040_bswmd() -> Path:
    for candidate in (TJA1040_BSWMD, SIP_TJA1040_BSWMD):
        if candidate.is_file():
            return candidate
    pytest.skip("CanTrcv_Tja1040 BSWMD fixture not available locally")


def _parse_module_def_from_xml(xml_text: str):
    parser = etree.XMLParser(remove_blank_text=False)
    root = etree.fromstring(xml_text.encode("utf-8"), parser=parser)
    elem = root.xpath('//*[local-name()="ECUC-MODULE-DEF"]')[0]
    return EcucDefParser().parse_module_def(elem)


def _parse_module_cfg_from_xml(xml_text: str, mod_def) -> EcucModuleConfiguration:
    parser = etree.XMLParser(remove_blank_text=False)
    root = etree.fromstring(xml_text.encode("utf-8"), parser=parser)
    elem = root.xpath('//*[local-name()="ECUC-MODULE-CONFIGURATION-VALUES"]')[0]
    mgr = ConfigurationManager(mod_def)
    cfg = ArxmlParser().parse_ecuc_configuration_values(elem)
    mgr.configuration = cfg
    return cfg


def _parse_module_cfg_from_file(arxml_path: Path, mod_def) -> EcucModuleConfiguration:
    parser = etree.XMLParser(resolve_entities=False, no_network=True)
    tree = etree.parse(str(arxml_path), parser)
    elem = tree.getroot().xpath('//*[local-name()="ECUC-MODULE-CONFIGURATION-VALUES"]')[0]
    mgr = ConfigurationManager(mod_def)
    cfg = ArxmlParser().parse_ecuc_configuration_values(elem)
    mgr.configuration = cfg
    return cfg


def _check_template_directives_balanced(template_path: Path):
    text = template_path.read_text(encoding="utf-8")
    tokens = re.findall(r"\[!(IF|ENDIF|LOOP|ENDLOOP|SELECT|ENDSELECT)\b", text)
    stack = []
    close_to_open = {"ENDIF": "IF", "ENDLOOP": "LOOP", "ENDSELECT": "SELECT"}
    for tok in tokens:
        if tok in ("IF", "LOOP", "SELECT"):
            stack.append(tok)
        else:
            assert stack and stack[-1] == close_to_open[tok], (
                f"Unbalanced directive {tok} in {template_path}: stack={stack}"
            )
            stack.pop()
    assert stack == [], f"Unclosed directives in {template_path}: {stack}"
    assert "ecu:get" not in text, f"Forbidden ecu:get found in {template_path}"
    assert "Vector Informatik GmbH" not in text
    assert "BETA VERSION" not in text


def _audit_rendered_output(h_text: str, c_text: str):
    for label, text in (("header", h_text), ("source", c_text)):
        assert "[!" not in text and "!]" not in text, f"Unrendered EB tag found in {label}"
        assert "0x0x" not in text, f"Double 0x prefix found in {label}"
        assert "Vector Informatik GmbH" not in text
        assert "BETA VERSION" not in text

    defines = [
        d
        for d in re.findall(r"^\s*#define\s+([A-Za-z_][A-Za-z0-9_]*)", h_text, flags=re.MULTILINE)
        if "_START_SEC_" not in d and "_STOP_SEC_" not in d
    ]
    duplicates = sorted({d for d in defines if defines.count(d) > 1})
    assert not duplicates, f"Duplicate #define macros in generated header: {duplicates}"


@pytest.mark.skipif(
    not TJA1040_TEMPLATE_DIR.is_dir(),
    reason="CanTrcv_Tja1040 templates directory not present locally",
)
def test_template_syntax_balanced():
    h_tpl = TJA1040_TEMPLATE_DIR / "include" / "CanTrcv_30_Tja1040_Cfg.h"
    c_tpl = TJA1040_TEMPLATE_DIR / "src" / "CanTrcv_30_Tja1040_Cfg.c"
    assert h_tpl.is_file()
    assert c_tpl.is_file()
    _check_template_directives_balanced(h_tpl)
    _check_template_directives_balanced(c_tpl)


@pytest.mark.skipif(
    not TJA1040_TEMPLATE_DIR.is_dir(),
    reason="CanTrcv_Tja1040 templates directory not present locally",
)
def test_minimal_default_config_rendering(tmp_path):
    mod_def = EcucDefParser().parse_module_def_file(_find_tja1040_bswmd())
    assert mod_def is not None

    ch_def = mod_def.containers["CanTrcvConfigSet"].sub_containers["CanTrcvChannel"]
    dio_ch_access = (
        ch_def.sub_containers["CanTrcvAccess"]
        .sub_containers["CanTrcvDioAccess"]
        .sub_containers["CanTrcvDioChannelAccess"]
    )
    assert "CanTrcvDioSymNameRef" in dio_ch_access.references

    cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>CanTrcvChannel_Default</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""",
        mod_def,
    )

    gen = CodeGenerator(mod_def, cfg, package_template_dir=TJA1040_TEMPLATE_DIR)
    assert gen.generate_all(tmp_path, flat=True) is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    h_text = (tmp_path / "include" / "CanTrcv_30_Tja1040_Cfg.h").read_text(encoding="utf-8")
    c_text = (tmp_path / "src" / "CanTrcv_30_Tja1040_Cfg.c").read_text(encoding="utf-8")
    _audit_rendered_output(h_text, c_text)

    # Includes
    assert '#include "Dio.h"' in h_text
    assert '#include "Spi.h"' not in h_text
    assert '#include "Icu.h"' not in h_text
    assert '#include "Dem.h"' not in h_text

    # Exact version defines (DrvTrans_Tja1040CanDioAsr 3.02.00, Base 0x0105u, HW 0x0103u)
    assert "#define DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_MAJOR_VERSION 0x03u" in h_text
    assert "#define DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_MINOR_VERSION 0x02u" in h_text
    assert "#define DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_PATCH_VERSION 0x00u" in h_text
    assert "#define CANTRCV_30_TJA1040_GENTOOL_CFG5_BASE_COMP_VERSION 0x0105u" in h_text
    assert "#define CANTRCV_30_TJA1040_GENTOOL_CFG5_HW_COMP_VERSION   0x0103u" in h_text
    assert "#define CanTrcv_30_Tja1040_GetGeneratorCompatibilityVersionOfPCConfig() 0x01050103u" in h_text

    # BSWMD defaults preserved
    assert "#define CANTRCV_30_TJA1040_MAX_CHANNEL                       1u" in h_text
    assert (
        "#define CANTRCV_30_TJA1040_GENERAL_WAKE_UP_SUPPORT           CANTRCV_30_TJA1040_WAKEUP_BY_POLLING"
        in h_text
    )
    assert "#define CANTRCV_30_TJA1040_WAKEUP_BY_BUS_USED                STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_GET_VERSION_INFO                  STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_DEV_ERROR_DETECT                  STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_DEV_ERROR_REPORT                  STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_ECUC_SAFE_BSW_CHECKS              STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_PROD_ERROR_DETECT                 STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_INSTANCE_ID                       0" in h_text
    assert "#define CANTRCV_30_TJA1040_HW_PN_SUPPORT                     STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS            STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_USE_ICU                           STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_USE_EXTENDED_WU_SRC               STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_SET_OP_MODE_WAIT_TIME_SUPPORT     STD_OFF" in h_text
    assert "#define CanTrcv_30_Tja1040_CanTrcvChannel_Default 0u" in h_text
    assert "typedef uint8 CanTrcv_30_Tja1040_WakeupSourceType;" in h_text

    # C version checks and default CSL tables
    assert "#if (DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_MAJOR_VERSION != 0x03u)" in c_text
    assert "#if (DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_MINOR_VERSION != 0x02u)" in c_text
    assert "#if (DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_PATCH_VERSION != 0x00u)" in c_text
    assert "CanTrcv_30_Tja1040_ChannelUsed[1]" in c_text
    assert "/* 0 */ TRUE" in c_text
    assert "CanTrcv_30_Tja1040_DioConfiguration[1]" in c_text
    assert "{ /* 0 */ 0xFFu, 0xFFu }" in c_text
    assert "CanTrcv_30_Tja1040_WakeupByBusUsed[1]" in c_text
    assert "/* 0 */ FALSE" in c_text
    assert "CanTrcv_30_Tja1040_WakeupSource[1]" in c_text
    assert "/* 0 */ 0x00u" in c_text
    assert "CanTrcv_30_Tja1040_Channel[" not in c_text
    assert "CanTrcv_30_Tja1040_WuSrcPor[" not in c_text
    assert "CanTrcv_30_Tja1040_WuSrcSyserr[" not in c_text


@pytest.mark.skipif(
    not TJA1040_TEMPLATE_DIR.is_dir(),
    reason="CanTrcv_Tja1040 templates directory not present locally",
)
def test_full_custom_multichannel_config_rendering(tmp_path):
    ct_def = EcucDefParser().parse_module_def_file(_find_tja1040_bswmd())

    dio_def = _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>AUTOSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-DEF><SHORT-NAME>Dio</SHORT-NAME><CONTAINERS>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>DioConfig</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <SUB-CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>DioPort</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
        <SUB-CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>DioChannel</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF>
        </SUB-CONTAINERS>
      </ECUC-PARAM-CONF-CONTAINER-DEF>
    </SUB-CONTAINERS>
  </ECUC-PARAM-CONF-CONTAINER-DEF>
</CONTAINERS></ECUC-MODULE-DEF>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
    )

    icu_def = _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>AUTOSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-DEF><SHORT-NAME>Icu</SHORT-NAME><CONTAINERS>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>IcuConfigSet</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <SUB-CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>IcuChannel</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF></SUB-CONTAINERS>
  </ECUC-PARAM-CONF-CONTAINER-DEF>
</CONTAINERS></ECUC-MODULE-DEF>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
    )

    ecum_def = _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-DEF><SHORT-NAME>EcuM</SHORT-NAME><CONTAINERS>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcuMConfiguration</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <SUB-CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcuMCommonConfiguration</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
      <SUB-CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcuMWakeupSource</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF></SUB-CONTAINERS>
    </ECUC-PARAM-CONF-CONTAINER-DEF></SUB-CONTAINERS>
  </ECUC-PARAM-CONF-CONTAINER-DEF>
</CONTAINERS></ECUC-MODULE-DEF>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
    )

    dem_def = _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-DEF><SHORT-NAME>Dem</SHORT-NAME><CONTAINERS>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>DemConfigSet</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <SUB-CONTAINERS><ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>DemEventParameter</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF></SUB-CONTAINERS>
  </ECUC-PARAM-CONF-CONTAINER-DEF>
</CONTAINERS></ECUC-MODULE-DEF>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
    )

    vset_def = _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-DEF><SHORT-NAME>vSet</SHORT-NAME><CONTAINERS>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>vSetGeneral</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <PARAMETERS><ECUC-ENUMERATION-PARAM-DEF><SHORT-NAME>vSetDummyStatementKind</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY><DEFAULT-VALUE>VoidCast</DEFAULT-VALUE></ECUC-ENUMERATION-PARAM-DEF></PARAMETERS>
  </ECUC-PARAM-CONF-CONTAINER-DEF>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>vSetPlatform</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <PARAMETERS><ECUC-ENUMERATION-PARAM-DEF><SHORT-NAME>vSetBitOrder</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY><DEFAULT-VALUE>MSB_to_LSB</DEFAULT-VALUE></ECUC-ENUMERATION-PARAM-DEF></PARAMETERS>
  </ECUC-PARAM-CONF-CONTAINER-DEF>
</CONTAINERS></ECUC-MODULE-DEF>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
    )

    ecuc_def = _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-DEF><SHORT-NAME>EcuC</SHORT-NAME><CONTAINERS>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>EcucGeneral</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <PARAMETERS>
      <ECUC-BOOLEAN-PARAM-DEF><SHORT-NAME>AtomicBitAccessInBitfield</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY><DEFAULT-VALUE>true</DEFAULT-VALUE></ECUC-BOOLEAN-PARAM-DEF>
      <ECUC-ENUMERATION-PARAM-DEF><SHORT-NAME>AtomicVariableAccess</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY><DEFAULT-VALUE>Atomic16BitAccess</DEFAULT-VALUE></ECUC-ENUMERATION-PARAM-DEF>
    </PARAMETERS>
  </ECUC-PARAM-CONF-CONTAINER-DEF>
</CONTAINERS></ECUC-MODULE-DEF>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
    )

    dio_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Dio</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Dio</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Dio</DEFINITION-REF>
  <CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>DioConfig</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dio/DioConfig</DEFINITION-REF>
    <SUB-CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>DioPort_0</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dio/DioConfig/DioPort</DEFINITION-REF>
      <SUB-CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>DioChannel_CAN0_STB</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dio/DioConfig/DioPort/DioChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>DioChannel_CAN0_RXD</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dio/DioConfig/DioPort/DioChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>DioChannel_CAN1_STB</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dio/DioConfig/DioPort/DioChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>DioChannel_CAN1_RXD</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dio/DioConfig/DioPort/DioChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
      </SUB-CONTAINERS>
    </ECUC-CONTAINER-VALUE></SUB-CONTAINERS>
  </ECUC-CONTAINER-VALUE></CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        dio_def,
    )

    icu_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Icu</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Icu</DEFINITION-REF>
  <CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>IcuConfigSet</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Icu/IcuConfigSet</DEFINITION-REF>
    <SUB-CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>IcuCh_CAN0</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Icu/IcuConfigSet/IcuChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE></SUB-CONTAINERS>
  </ECUC-CONTAINER-VALUE></CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        icu_def,
    )

    ecum_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>EcuM</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuM</DEFINITION-REF>
  <CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>EcuMConfiguration</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuM/EcuMConfiguration</DEFINITION-REF>
    <SUB-CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>EcuMCommonConfiguration</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration</DEFINITION-REF>
      <SUB-CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>WS_BUS</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>WS_POR</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>WS_SYS</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DEFINITION-REF></ECUC-CONTAINER-VALUE>
      </SUB-CONTAINERS>
    </ECUC-CONTAINER-VALUE></SUB-CONTAINERS>
  </ECUC-CONTAINER-VALUE></CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        ecum_def,
    )

    dem_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Dem</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Dem</DEFINITION-REF>
  <CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>DemConfigSet</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Dem/DemConfigSet</DEFINITION-REF>
    <SUB-CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>CANTRCV_E_BUS_ERROR</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Dem/DemConfigSet/DemEventParameter</DEFINITION-REF></ECUC-CONTAINER-VALUE></SUB-CONTAINERS>
  </ECUC-CONTAINER-VALUE></CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        dem_def,
    )

    vset_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>vSet</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/vSet</DEFINITION-REF>
  <CONTAINERS>
    <ECUC-CONTAINER-VALUE><SHORT-NAME>vSetGeneral</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/vSet/vSetGeneral</DEFINITION-REF></ECUC-CONTAINER-VALUE>
    <ECUC-CONTAINER-VALUE><SHORT-NAME>vSetPlatform</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/vSet/vSetPlatform</DEFINITION-REF></ECUC-CONTAINER-VALUE>
  </CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        vset_def,
    )

    ecuc_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>EcuC</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuC</DEFINITION-REF>
  <CONTAINERS>
    <ECUC-CONTAINER-VALUE><SHORT-NAME>EcucGeneral</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucGeneral</DEFINITION-REF></ECUC-CONTAINER-VALUE>
  </CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        ecuc_def,
    )

    # Channels deliberately stored out of order (id=1 first, id=0 second) to verify sorting.
    ct_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral/CanTrcvWakeUpSupport</DEFINITION-REF><VALUE>CANTRCV_WAKEUP_NOT_SUPPORTED</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral/CanTrcvGetVersionInfo</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral/CanTrcvDevErrorDetect</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral/CanTrcvSafeBswChecks</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral/CanTrcvIndex</DEFINITION-REF><VALUE>2</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral/CanTrcvUserConfigFile</DEFINITION-REF><VALUE>CanTrcv_UserCfg.h</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>CanTrcvChannel_B</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelUsed</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupByBusUsed</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                  <SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE>
                      <SHORT-NAME>CanTrcvDioAccess</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess</DEFINITION-REF>
                      <SUB-CONTAINERS>
                        <ECUC-CONTAINER-VALUE>
                          <SHORT-NAME>PinSTB</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess</DEFINITION-REF>
                          <REFERENCE-VALUES>
                            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-CHOICE-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvDioSymNameRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Dio/Dio/DioConfig/DioPort_0/DioChannel_CAN1_STB</VALUE-REF></ECUC-REFERENCE-VALUE>
                          </REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                        <ECUC-CONTAINER-VALUE>
                          <SHORT-NAME>PinRXD</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess</DEFINITION-REF>
                          <REFERENCE-VALUES>
                            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-CHOICE-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvDioSymNameRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Dio/Dio/DioConfig/DioPort_0/DioChannel_CAN1_RXD</VALUE-REF></ECUC-REFERENCE-VALUE>
                          </REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                      </SUB-CONTAINERS>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>CanTrcvChannel_A</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupByBusUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WS_BUS</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvIcuChannelRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Icu/IcuConfigSet/IcuCh_CAN0</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPorWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WS_POR</VALUE-REF></ECUC-REFERENCE-VALUE>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvSyserrWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WS_SYS</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                  <SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE>
                      <SHORT-NAME>CanTrcvDioAccess</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess</DEFINITION-REF>
                      <SUB-CONTAINERS>
                        <ECUC-CONTAINER-VALUE>
                          <SHORT-NAME>DioCh_STB_Custom</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess</DEFINITION-REF>
                          <PARAMETER-VALUES>
                            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvHardwareInterfaceName</DEFINITION-REF><VALUE>PinSTB</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
                          </PARAMETER-VALUES>
                          <REFERENCE-VALUES>
                            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-CHOICE-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvDioSymNameRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Dio/Dio/DioConfig/DioPort_0/DioChannel_CAN0_STB</VALUE-REF></ECUC-REFERENCE-VALUE>
                          </REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                        <ECUC-CONTAINER-VALUE>
                          <SHORT-NAME>DioCh_RXD_Custom</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess</DEFINITION-REF>
                          <PARAMETER-VALUES>
                            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvHardwareInterfaceName</DEFINITION-REF><VALUE>PinRXD</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
                          </PARAMETER-VALUES>
                          <REFERENCE-VALUES>
                            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-CHOICE-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvDioSymNameRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Dio/Dio/DioConfig/DioPort_0/DioChannel_CAN0_RXD</VALUE-REF></ECUC-REFERENCE-VALUE>
                          </REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                      </SUB-CONTAINERS>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>CanTrcvDemEventParameterRefs</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvDemEventParameterRefs</DEFINITION-REF>
              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvDemEventParameterRefs/CANTRCV_E_BUS_ERROR</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Dem/DemConfigSet/CANTRCV_E_BUS_ERROR</VALUE-REF></ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""",
        ct_def,
    )

    gen = CodeGenerator(
        ct_def,
        ct_cfg,
        all_configurations={
            "Dio": (dio_def, dio_cfg),
            "Icu": (icu_def, icu_cfg),
            "EcuM": (ecum_def, ecum_cfg),
            "Dem": (dem_def, dem_cfg),
            "vSet": (vset_def, vset_cfg),
            "EcuC": (ecuc_def, ecuc_cfg),
        },
        package_template_dir=TJA1040_TEMPLATE_DIR,
    )
    assert gen.generate_all(tmp_path, flat=True) is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    h_text = (tmp_path / "include" / "CanTrcv_30_Tja1040_Cfg.h").read_text(encoding="utf-8")
    c_text = (tmp_path / "src" / "CanTrcv_30_Tja1040_Cfg.c").read_text(encoding="utf-8")
    _audit_rendered_output(h_text, c_text)

    # Conditional includes & switches
    assert '#include "Dio.h"' in h_text
    assert '#include "Icu.h"' in h_text
    assert '#include "Dem.h"' in h_text
    assert "#define CANTRCV_30_TJA1040_MAX_CHANNEL                       2u" in h_text
    assert (
        "#define CANTRCV_30_TJA1040_GENERAL_WAKE_UP_SUPPORT           CANTRCV_30_TJA1040_WAKEUP_NOT_SUPPORTED"
        in h_text
    )
    assert "#define CANTRCV_30_TJA1040_WAKEUP_BY_BUS_USED                STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_GET_VERSION_INFO                  STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_DEV_ERROR_DETECT                  STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_DEV_ERROR_REPORT                  STD_OFF" in h_text
    assert "#define CANTRCV_30_TJA1040_ECUC_SAFE_BSW_CHECKS              STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_PROD_ERROR_DETECT                 STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_INSTANCE_ID                       2" in h_text
    assert "#define CANTRCV_30_TJA1040_USE_ICU                           STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_USE_EXTENDED_WU_SRC               STD_ON" in h_text

    # Channel ordering + vSet / EcuC overrides + UserConfigFile
    idx_a = h_text.index("#define CanTrcv_30_Tja1040_CanTrcvChannel_A 0u")
    idx_b = h_text.index("#define CanTrcv_30_Tja1040_CanTrcvChannel_B 1u")
    assert idx_a < idx_b
    assert "#define CANTRCV_30_TJA1040_DUMMY_STATEMENT(v) (void)(v)" in h_text
    assert "#define CANTRCV_30_TJA1040_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_ATOMIC_VARIABLE_ACCESS 16u" in h_text
    assert "#define CANTRCV_30_TJA1040_CPUTYPE_BITORDER_MSB2LSB" in h_text
    assert '#include "CanTrcv_UserCfg.h"\n#endif /* CANTRCV_30_TJA1040_CFG_H */' in h_text.replace(
        "\r\n", "\n"
    )

    # Optional CSL switches & declarations
    assert "#define CANTRCV_30_TJA1040_CHANNEL                                    STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_WUSRCPOR                                   STD_ON" in h_text
    assert "#define CANTRCV_30_TJA1040_WUSRCSYSERR                                STD_ON" in h_text
    assert "typedef EcuM_WakeupSourceType CanTrcv_30_Tja1040_WakeupSourceType;" in h_text
    assert "extern CONST(CanTrcv_30_Tja1040_ChannelType, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_Channel[2];" in h_text
    assert "extern CONST(CanTrcv_30_Tja1040_WuSrcPorType, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_WuSrcPor[2];" in h_text
    assert "extern CONST(CanTrcv_30_Tja1040_WuSrcSyserrType, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_WuSrcSyserr[2];" in h_text

    # C tables in sorted channel order (Channel A idx 0, Channel B idx 1)
    assert "{ /* 0 */ IcuConf_IcuChannel_IcuCh_CAN0, TRUE }," in c_text
    assert "{ /* 1 */ 0u, FALSE }" in c_text
    assert "/* 0 */ TRUE,\n  /* 1 */ FALSE" in c_text.replace("\r\n", "\n")
    assert "{ /* 0 */ DioConf_DioChannel_DioChannel_CAN0_RXD, DioConf_DioChannel_DioChannel_CAN0_STB }," in c_text
    assert "{ /* 1 */ DioConf_DioChannel_DioChannel_CAN1_RXD, DioConf_DioChannel_DioChannel_CAN1_STB }" in c_text
    assert "/* 0 */ ((EcuM_WakeupSourceType)1u << EcuMConf_EcuMWakeupSource_WS_BUS)," in c_text
    assert "/* 0 */ ((EcuM_WakeupSourceType)1u << EcuMConf_EcuMWakeupSource_WS_POR)," in c_text
    assert "/* 0 */ ((EcuM_WakeupSourceType)1u << EcuMConf_EcuMWakeupSource_WS_SYS)," in c_text
    assert "/* 1 */ ((EcuM_WakeupSourceType)0x00u)" in c_text


@pytest.mark.skipif(
    not (
        TJA1040_TEMPLATE_DIR.is_dir()
        and (TJA1040_PKG_DIR / "module.json").is_file()
        and TEST2_DIO_XDM.is_file()
        and TEST2_DIO_ARXML.is_file()
    ),
    reason="Local test2 CanTrcv_Tja1040 package and Dio fixtures not present",
)
def test_package_discovery_and_real_dio_integration(tmp_path):
    manifest = load_manifest(TJA1040_PKG_DIR)
    pkg = ModulePackage(TJA1040_PKG_DIR, manifest)
    assert pkg.template_dir() == TJA1040_TEMPLATE_DIR

    ct_def = EcucDefParser().parse_module_def_file(pkg.definition_file(None))
    assert ct_def is not None
    dio_def = EcucDefParser().parse_module_def_file(TEST2_DIO_XDM)
    assert dio_def is not None
    dio_cfg = _parse_module_cfg_from_file(TEST2_DIO_ARXML, dio_def)

    ct_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>CanTrcvChannel_Tja</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                  <SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE>
                      <SHORT-NAME>CanTrcvDioAccess</SHORT-NAME>
                      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess</DEFINITION-REF>
                      <SUB-CONTAINERS>
                        <ECUC-CONTAINER-VALUE>
                          <SHORT-NAME>PinSTB</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess</DEFINITION-REF>
                          <PARAMETER-VALUES>
                            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvHardwareInterfaceName</DEFINITION-REF><VALUE>PinSTB</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
                          </PARAMETER-VALUES>
                          <REFERENCE-VALUES>
                            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-CHOICE-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvDioSymNameRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_OUT1</VALUE-REF></ECUC-REFERENCE-VALUE>
                          </REFERENCE-VALUES>
                        </ECUC-CONTAINER-VALUE>
                        <ECUC-CONTAINER-VALUE>
                          <SHORT-NAME>PinRXD</SHORT-NAME>
                          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess</DEFINITION-REF>
                          <PARAMETER-VALUES>
                            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvHardwareInterfaceName</DEFINITION-REF><VALUE>PinRXD</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
                          </PARAMETER-VALUES>
                          <REFERENCE-VALUES>
                            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-CHOICE-REFERENCE-DEF">/MICROSAR/CanTrcv_Tja1040/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvDioAccess/CanTrcvDioChannelAccess/CanTrcvDioSymNameRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Dio/Dio/DioConfig/DioPort_14/DIO_TEST_IN1</VALUE-REF></ECUC-REFERENCE-VALUE>
                          </REFERENCE-VALUES>
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
</AUTOSAR>""",
        ct_def,
    )

    gen = CodeGenerator(
        ct_def,
        ct_cfg,
        all_configurations={"Dio": (dio_def, dio_cfg)},
        package_template_dir=pkg.template_dir(),
    )
    assert gen.generate_all(tmp_path) is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    h_text = (tmp_path / "CanTrcv" / "include" / "CanTrcv_30_Tja1040_Cfg.h").read_text(encoding="utf-8")
    c_text = (tmp_path / "CanTrcv" / "src" / "CanTrcv_30_Tja1040_Cfg.c").read_text(encoding="utf-8")
    _audit_rendered_output(h_text, c_text)

    assert "#define CanTrcv_30_Tja1040_CanTrcvChannel_Tja 0u" in h_text
    assert "{ /* 0 */ DioConf_DioChannel_DIO_TEST_IN1, DioConf_DioChannel_DIO_TEST_OUT1 }" in c_text
