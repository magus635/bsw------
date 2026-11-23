import re
from pathlib import Path

import pytest
from lxml import etree

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
)
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator


REPO_ROOT = Path(__file__).resolve().parents[2]
TEST2_PROJECT_DPA = Path("/Users/qlwang/Desktop/test2/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
TLE9255_PKG_DIR = Path(
    "/Users/qlwang/Desktop/test2/MCAL_R440_FuSa/modules/davinci/CanTrcv_Tle9255"
)
TLE9255_TEMPLATE_DIR = TLE9255_PKG_DIR / "templates"
SIP_BSWMD = Path(
    "/Users/qlwang/Desktop/未命名文件夹/mcuapp/Components/CanTrcv_30_Tle9255/BSWMD/CanTrcv_Tle9255CanAsr_bswmd.arxml"
)
REF_CFG_H = Path(
    "/Users/qlwang/Desktop/未命名文件夹/mcuapp/Applications/SipAddon/StartApplication/Appl/GenData/CanTrcv_30_Tle9255_Cfg.h"
)
REF_CFG_C = Path(
    "/Users/qlwang/Desktop/未命名文件夹/mcuapp/Applications/SipAddon/StartApplication/Appl/GenData/CanTrcv_30_Tle9255_Cfg.c"
)


def _find_tle9255_bswmd() -> Path:
    for candidate in (TLE9255_PKG_DIR / "config" / "CanTrcv.arxml", SIP_BSWMD):
        if candidate.is_file():
            return candidate
    pytest.skip("CanTrcv_Tle9255 BSWMD fixture not available locally")


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


def _synthetic_can_trcv_bswmd():
    """Self-contained minimal CanTrcv BSWMD matching BSWMD schema & defaults."""
    return _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME>
          <ELEMENTS>
            <ECUC-MODULE-DEF>
              <SHORT-NAME>CanTrcv</SHORT-NAME>
              <CONTAINERS>
                <ECUC-PARAM-CONF-CONTAINER-DEF>
                  <SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
                  <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY>
                  <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                  <SUB-CONTAINERS>
                    <ECUC-PARAM-CONF-CONTAINER-DEF>
                      <SHORT-NAME>CanTrcvChannel</SHORT-NAME>
                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY>
                      <UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
                      <PARAMETERS>
                        <ECUC-INTEGER-PARAM-DEF>
                          <SHORT-NAME>CanTrcvChannelId</SHORT-NAME>
                          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DEFAULT-VALUE>0</DEFAULT-VALUE>
                        </ECUC-INTEGER-PARAM-DEF>
                        <ECUC-BOOLEAN-PARAM-DEF>
                          <SHORT-NAME>CanTrcvChannelUsed</SHORT-NAME>
                          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DEFAULT-VALUE>true</DEFAULT-VALUE>
                        </ECUC-BOOLEAN-PARAM-DEF>
                        <ECUC-BOOLEAN-PARAM-DEF>
                          <SHORT-NAME>CanTrcvHwPnSupport</SHORT-NAME>
                          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DEFAULT-VALUE>true</DEFAULT-VALUE>
                        </ECUC-BOOLEAN-PARAM-DEF>
                        <ECUC-BOOLEAN-PARAM-DEF>
                          <SHORT-NAME>CanTrcvWakeupByBusUsed</SHORT-NAME>
                          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DEFAULT-VALUE>false</DEFAULT-VALUE>
                        </ECUC-BOOLEAN-PARAM-DEF>
                        <ECUC-ENUMERATION-PARAM-DEF>
                          <SHORT-NAME>CanTrcvBaudrateRatio</SHORT-NAME>
                          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DEFAULT-VALUE>RATIO_LOWER_EQUALS_4</DEFAULT-VALUE>
                          <LITERALS>
                            <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>RATIO_LOWER_EQUALS_4</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
                            <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>RATIO_LOWER_EQUALS_10</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
                          </LITERALS>
                        </ECUC-ENUMERATION-PARAM-DEF>
                      </PARAMETERS>
                      <REFERENCES>
                        <ECUC-REFERENCE-DEF>
                          <SHORT-NAME>CanTrcvWakeupSourceRef</SHORT-NAME>
                          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DESTINATION-REF>
                        </ECUC-REFERENCE-DEF>
                        <ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                          <SHORT-NAME>CanTrcvIcuChannelRef</SHORT-NAME>
                          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Icu/IcuConfigSet/IcuChannel</DESTINATION-REF>
                        </ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                        <ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                          <SHORT-NAME>CanTrcvPorWakeupSourceRef</SHORT-NAME>
                          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DESTINATION-REF>
                        </ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                        <ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                          <SHORT-NAME>CanTrcvSyserrWakeupSourceRef</SHORT-NAME>
                          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource</DESTINATION-REF>
                        </ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                      </REFERENCES>
                      <SUB-CONTAINERS>
                        <ECUC-PARAM-CONF-CONTAINER-DEF>
                          <SHORT-NAME>CanTrcvPartialNetwork</SHORT-NAME>
                          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <PARAMETERS>
                            <ECUC-INTEGER-PARAM-DEF>
                              <SHORT-NAME>CanTrcvBaudRate</SHORT-NAME>
                              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <DEFAULT-VALUE>500</DEFAULT-VALUE>
                            </ECUC-INTEGER-PARAM-DEF>
                            <ECUC-BOOLEAN-PARAM-DEF>
                              <SHORT-NAME>CanTrcvBusErrFlag</SHORT-NAME>
                              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <DEFAULT-VALUE>false</DEFAULT-VALUE>
                            </ECUC-BOOLEAN-PARAM-DEF>
                            <ECUC-BOOLEAN-PARAM-DEF>
                              <SHORT-NAME>CanTrcvPnCanIdIsExtended</SHORT-NAME>
                              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <DEFAULT-VALUE>false</DEFAULT-VALUE>
                            </ECUC-BOOLEAN-PARAM-DEF>
                            <ECUC-BOOLEAN-PARAM-DEF>
                              <SHORT-NAME>CanTrcvPnEnabled</SHORT-NAME>
                              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <DEFAULT-VALUE>false</DEFAULT-VALUE>
                            </ECUC-BOOLEAN-PARAM-DEF>
                            <ECUC-INTEGER-PARAM-DEF>
                              <SHORT-NAME>CanTrcvPnFrameCanId</SHORT-NAME>
                              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <DEFAULT-VALUE>0</DEFAULT-VALUE>
                            </ECUC-INTEGER-PARAM-DEF>
                            <ECUC-INTEGER-PARAM-DEF>
                              <SHORT-NAME>CanTrcvPnFrameCanIdMask</SHORT-NAME>
                              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <DEFAULT-VALUE>0</DEFAULT-VALUE>
                            </ECUC-INTEGER-PARAM-DEF>
                            <ECUC-INTEGER-PARAM-DEF>
                              <SHORT-NAME>CanTrcvPnFrameDlc</SHORT-NAME>
                              <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <DEFAULT-VALUE>8</DEFAULT-VALUE>
                            </ECUC-INTEGER-PARAM-DEF>
                          </PARAMETERS>
                          <SUB-CONTAINERS>
                            <ECUC-PARAM-CONF-CONTAINER-DEF>
                              <SHORT-NAME>CanTrcvPnFrameDataMaskSpec</SHORT-NAME>
                              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>8</UPPER-MULTIPLICITY>
                              <PARAMETERS>
                                <ECUC-INTEGER-PARAM-DEF>
                                  <SHORT-NAME>CanTrcvPnFrameDataMask</SHORT-NAME>
                                  <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                                  <DEFAULT-VALUE>0</DEFAULT-VALUE>
                                </ECUC-INTEGER-PARAM-DEF>
                                <ECUC-INTEGER-PARAM-DEF>
                                  <SHORT-NAME>CanTrcvPnFrameDataMaskIndex</SHORT-NAME>
                                  <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                                  <DEFAULT-VALUE>0</DEFAULT-VALUE>
                                </ECUC-INTEGER-PARAM-DEF>
                              </PARAMETERS>
                            </ECUC-PARAM-CONF-CONTAINER-DEF>
                          </SUB-CONTAINERS>
                        </ECUC-PARAM-CONF-CONTAINER-DEF>
                        <ECUC-CHOICE-CONTAINER-DEF>
                          <SHORT-NAME>CanTrcvAccess</SHORT-NAME>
                          <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <CHOICES>
                            <ECUC-PARAM-CONF-CONTAINER-DEF>
                              <SHORT-NAME>CanTrcvSpiSequence</SHORT-NAME>
                              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                              <PARAMETERS>
                                <ECUC-BOOLEAN-PARAM-DEF>
                                  <SHORT-NAME>CanTrcvSpiAccessSynchronous</SHORT-NAME>
                                  <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                                  <DEFAULT-VALUE>false</DEFAULT-VALUE>
                                </ECUC-BOOLEAN-PARAM-DEF>
                              </PARAMETERS>
                              <SUB-CONTAINERS>
                                <ECUC-PARAM-CONF-CONTAINER-DEF>
                                  <SHORT-NAME>CanTrcvSpiSequenceAccess</SHORT-NAME>
                                  <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>3</UPPER-MULTIPLICITY>
                                  <PARAMETERS>
                                    <ECUC-BOOLEAN-PARAM-DEF>
                                      <SHORT-NAME>CanTrcvSpiAccessSynchronous</SHORT-NAME>
                                      <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                                      <DEFAULT-VALUE>false</DEFAULT-VALUE>
                                    </ECUC-BOOLEAN-PARAM-DEF>
                                    <ECUC-STRING-PARAM-DEF>
                                      <SHORT-NAME>CanTrcvSpiSequenceIdentifier</SHORT-NAME>
                                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                                    </ECUC-STRING-PARAM-DEF>
                                  </PARAMETERS>
                                  <REFERENCES>
                                    <ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                                      <SHORT-NAME>CanTrcvSpiSequenceName</SHORT-NAME>
                                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                                      <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence</DESTINATION-REF>
                                    </ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                                  </REFERENCES>
                                </ECUC-PARAM-CONF-CONTAINER-DEF>
                              </SUB-CONTAINERS>
                            </ECUC-PARAM-CONF-CONTAINER-DEF>
                          </CHOICES>
                        </ECUC-CHOICE-CONTAINER-DEF>
                      </SUB-CONTAINERS>
                    </ECUC-PARAM-CONF-CONTAINER-DEF>
                    <ECUC-PARAM-CONF-CONTAINER-DEF>
                      <SHORT-NAME>CanTrcvDemEventParameterRefs</SHORT-NAME>
                      <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                      <REFERENCES>
                        <ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                          <SHORT-NAME>CANTRCV_E_BUS_ERROR</SHORT-NAME>
                          <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                          <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter</DESTINATION-REF>
                        </ECUC-SYMBOLIC-NAME-REFERENCE-DEF>
                      </REFERENCES>
                    </ECUC-PARAM-CONF-CONTAINER-DEF>
                  </SUB-CONTAINERS>
                </ECUC-PARAM-CONF-CONTAINER-DEF>
                <ECUC-PARAM-CONF-CONTAINER-DEF>
                  <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
                  <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                  <PARAMETERS>
                    <ECUC-BOOLEAN-PARAM-DEF>
                      <SHORT-NAME>CanTrcvDevErrorDetect</SHORT-NAME>
                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                      <DEFAULT-VALUE>true</DEFAULT-VALUE>
                    </ECUC-BOOLEAN-PARAM-DEF>
                    <ECUC-BOOLEAN-PARAM-DEF>
                      <SHORT-NAME>CanTrcvGetVersionInfo</SHORT-NAME>
                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                      <DEFAULT-VALUE>false</DEFAULT-VALUE>
                    </ECUC-BOOLEAN-PARAM-DEF>
                    <ECUC-ENUMERATION-PARAM-DEF>
                      <SHORT-NAME>CanTrcvWakeUpSupport</SHORT-NAME>
                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                      <DEFAULT-VALUE>CANTRCV_WAKEUP_BY_POLLING</DEFAULT-VALUE>
                      <LITERALS>
                        <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>CANTRCV_WAKEUP_BY_POLLING</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
                        <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>CANTRCV_WAKEUP_NOT_SUPPORTED</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
                      </LITERALS>
                    </ECUC-ENUMERATION-PARAM-DEF>
                    <ECUC-STRING-PARAM-DEF>
                      <SHORT-NAME>CanTrcvUserConfigFile</SHORT-NAME>
                      <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                    </ECUC-STRING-PARAM-DEF>
                    <ECUC-INTEGER-PARAM-DEF>
                      <SHORT-NAME>CanTrcvIndex</SHORT-NAME>
                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                      <DEFAULT-VALUE>0</DEFAULT-VALUE>
                    </ECUC-INTEGER-PARAM-DEF>
                    <ECUC-ENUMERATION-PARAM-DEF>
                      <SHORT-NAME>CanTrcvTimerType</SHORT-NAME>
                      <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                      <DEFAULT-VALUE>None</DEFAULT-VALUE>
                      <LITERALS>
                        <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>None</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
                        <ECUC-ENUMERATION-LITERAL-DEF><SHORT-NAME>Timer_1us16bit</SHORT-NAME></ECUC-ENUMERATION-LITERAL-DEF>
                      </LITERALS>
                    </ECUC-ENUMERATION-PARAM-DEF>
                    <ECUC-BOOLEAN-PARAM-DEF>
                      <SHORT-NAME>CanTrcvSafeBswChecks</SHORT-NAME>
                      <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                      <DEFAULT-VALUE>false</DEFAULT-VALUE>
                    </ECUC-BOOLEAN-PARAM-DEF>
                  </PARAMETERS>
                </ECUC-PARAM-CONF-CONTAINER-DEF>
              </CONTAINERS>
            </ECUC-MODULE-DEF>
          </ELEMENTS>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>"""
    )


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


def _audit_rendered_output(h_text: str, c_text: str):
    for label, text in (("header", h_text), ("source", c_text)):
        assert "[!" not in text and "!]" not in text, f"Unrendered EB tag found in {label}"
        assert "0x0x" not in text, f"Double 0x prefix found in {label}"
        assert "Vector Informatik GmbH" not in text
        assert "BETA VERSION" not in text

    # Ensure each `#define NAME` in the generated header is unique (excluding AUTOSAR MemMap START/STOP_SEC_* switches)
    defines = [
        d
        for d in re.findall(r"^\s*#define\s+([A-Za-z_][A-Za-z0-9_]*)", h_text, flags=re.MULTILINE)
        if "_START_SEC_" not in d and "_STOP_SEC_" not in d
    ]
    duplicates = sorted({d for d in defines if defines.count(d) > 1})
    assert not duplicates, f"Duplicate #define macros in generated header: {duplicates}"


def test_ecuc_def_parser_parses_symbolic_name_references():
    mod_def = _synthetic_can_trcv_bswmd()
    cfg_set = mod_def.containers["CanTrcvConfigSet"]
    ch_def = cfg_set.sub_containers["CanTrcvChannel"]
    assert "CanTrcvIcuChannelRef" in ch_def.references
    assert "CanTrcvPorWakeupSourceRef" in ch_def.references
    assert "CanTrcvSyserrWakeupSourceRef" in ch_def.references
    assert (
        ch_def.references["CanTrcvIcuChannelRef"].destination_ref
        == "/AUTOSAR/EcucDefs/Icu/IcuConfigSet/IcuChannel"
    )
    spi_acc = (
        ch_def.sub_containers["CanTrcvAccess"]
        .sub_containers["CanTrcvSpiSequence"]
        .sub_containers["CanTrcvSpiSequenceAccess"]
    )
    assert "CanTrcvSpiSequenceName" in spi_acc.references
    dem_refs = cfg_set.sub_containers["CanTrcvDemEventParameterRefs"]
    assert "CANTRCV_E_BUS_ERROR" in dem_refs.references


@pytest.mark.skipif(
    not TLE9255_TEMPLATE_DIR.is_dir(),
    reason="CanTrcv_Tle9255 templates directory not present locally",
)
def test_template_syntax_balanced():
    h_tpl = TLE9255_TEMPLATE_DIR / "include" / "CanTrcv_30_Tle9255_Cfg.h"
    c_tpl = TLE9255_TEMPLATE_DIR / "src" / "CanTrcv_30_Tle9255_Cfg.c"
    assert h_tpl.is_file()
    assert c_tpl.is_file()
    _check_template_directives_balanced(h_tpl)
    _check_template_directives_balanced(c_tpl)


@pytest.mark.skipif(
    not TLE9255_TEMPLATE_DIR.is_dir(),
    reason="CanTrcv_Tle9255 templates directory not present locally",
)
def test_minimal_default_config_rendering(tmp_path):
    mod_def = _synthetic_can_trcv_bswmd()
    cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvConfigSet</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>CanTrcvChannel_Default</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""",
        mod_def,
    )

    gen = CodeGenerator(mod_def, cfg, package_template_dir=TLE9255_TEMPLATE_DIR)
    assert gen.generate_all(tmp_path, flat=True) is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    h_text = (tmp_path / "include" / "CanTrcv_30_Tle9255_Cfg.h").read_text(encoding="utf-8")
    c_text = (tmp_path / "src" / "CanTrcv_30_Tle9255_Cfg.c").read_text(encoding="utf-8")
    _audit_rendered_output(h_text, c_text)

    # Verify BSWMD defaults
    assert "#define CANTRCV_30_TLE9255_MAX_CHANNEL                       1u" in h_text
    assert (
        "#define CANTRCV_30_TLE9255_GENERAL_WAKE_UP_SUPPORT           CANTRCV_30_TLE9255_WAKEUP_BY_POLLING"
        in h_text
    )
    assert "#define CANTRCV_30_TLE9255_WAKEUP_BY_BUS_USED                STD_OFF" in h_text
    assert "#define CANTRCV_30_TLE9255_DEV_ERROR_DETECT                  STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_DEV_ERROR_REPORT                  STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_HW_PN_SUPPORT                     STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_SPI_ACCESS_SYNCHRONOUS            STD_OFF" in h_text
    assert "#define CanTrcv_30_Tle9255_CanTrcvChannel_Default 0u" in h_text
    assert "#define CANTRCV_30_TLE9255_PNENABLED                                  STD_ON" in h_text
    assert "#define CanTrcv_30_Tle9255_IsPnEnabled(Index)" in h_text
    assert "CanTrcv_30_Tle9255_SpiIndicationN_CanTrcvChannel_Default(void);" in h_text
    assert "CanTrcv_30_Tle9255_SpiIndicationL_CanTrcvChannel_Default(void);" in h_text

    # Async SPI indication definitions + default tables
    assert "FUNC(void, CANTRCV_30_TLE9255_CODE) CanTrcv_30_Tle9255_SpiIndicationN_CanTrcvChannel_Default(void)" in c_text
    assert "CanTrcv_30_Tle9255_SpiIndication(CanTrcv_30_Tle9255_CanTrcvChannel_Default);" in c_text
    assert "4u  /* (=500 KBit/s) */" in c_text
    assert "0x08u" in c_text
    assert "/* 0 */ FALSE" in c_text
    assert "{ /* 0 */ 0xFFu, 0xFFu, 0xFFu }" in c_text
    assert "typedef uint8 CanTrcv_30_Tle9255_WakeupSourceType;" in h_text
    assert "/* 0 */ 0x00u" in c_text


@pytest.mark.skipif(
    not TLE9255_TEMPLATE_DIR.is_dir(),
    reason="CanTrcv_Tle9255 templates directory not present locally",
)
def test_custom_enabled_multi_channel_config_rendering(tmp_path):
    ct_def = _synthetic_can_trcv_bswmd()

    spi_def = _parse_module_def_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>AUTOSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-DEF><SHORT-NAME>Spi</SHORT-NAME><CONTAINERS>
  <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiDriver</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
    <SUB-CONTAINERS>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiChannel</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE></ECUC-PARAM-CONF-CONTAINER-DEF>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiJob</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
        <SUB-CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiChannelList</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
            <PARAMETERS><ECUC-INTEGER-PARAM-DEF><SHORT-NAME>SpiChannelIndex</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY><DEFAULT-VALUE>0</DEFAULT-VALUE></ECUC-INTEGER-PARAM-DEF></PARAMETERS>
            <REFERENCES><ECUC-REFERENCE-DEF><SHORT-NAME>SpiChannelAssignment</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY><DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DESTINATION-REF></ECUC-REFERENCE-DEF></REFERENCES>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </SUB-CONTAINERS>
      </ECUC-PARAM-CONF-CONTAINER-DEF>
      <ECUC-PARAM-CONF-CONTAINER-DEF><SHORT-NAME>SpiSequence</SHORT-NAME><LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE>
        <REFERENCES><ECUC-REFERENCE-DEF><SHORT-NAME>SpiJobAssignment</SHORT-NAME><LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY-INFINITE>true</UPPER-MULTIPLICITY-INFINITE><DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob</DESTINATION-REF></ECUC-REFERENCE-DEF></REFERENCES>
      </ECUC-PARAM-CONF-CONTAINER-DEF>
    </SUB-CONTAINERS>
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

    spi_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Spi</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Spi</SHORT-NAME>
  <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Spi</DEFINITION-REF>
  <CONTAINERS>
    <ECUC-CONTAINER-VALUE><SHORT-NAME>SpiDriver</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver</DEFINITION-REF>
      <SUB-CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>ChA</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>ChB</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>ChC</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>JobLarge</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob</DEFINITION-REF>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CL2</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList</DEFINITION-REF>
              <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelIndex</DEFINITION-REF><VALUE>2</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
              <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Spi/Spi/SpiDriver/ChC</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CL0</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList</DEFINITION-REF>
              <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelIndex</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
              <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Spi/Spi/SpiDriver/ChA</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CL1</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList</DEFINITION-REF>
              <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelIndex</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
              <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiJob/SpiChannelList/SpiChannelAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Spi/Spi/SpiDriver/ChB</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>SEQ_L</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence</DEFINITION-REF>
          <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence/SpiJobAssignment</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Spi/Spi/SpiDriver/JobLarge</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>SEQ_M</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence</DEFINITION-REF></ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>SEQ_N</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Spi/SpiDriver/SpiSequence</DEFINITION-REF></ECUC-CONTAINER-VALUE>
      </SUB-CONTAINERS>
    </ECUC-CONTAINER-VALUE>
  </CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        spi_def,
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

    icu_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Icu</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Icu</DEFINITION-REF>
  <CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>IcuConfigSet</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Icu/IcuConfigSet</DEFINITION-REF>
    <SUB-CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>IcuCh_Wakeup</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Icu/IcuConfigSet/IcuChannel</DEFINITION-REF></ECUC-CONTAINER-VALUE></SUB-CONTAINERS>
  </ECUC-CONTAINER-VALUE></CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        icu_def,
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

    # Multi-channel CanTrcv config placed in reverse ChannelId order (Ch1 before Ch0)
    # to test deterministic sorting by CanTrcvChannelId.
    ct_cfg = _parse_module_cfg_from_xml(
        """<?xml version="1.0" encoding="utf-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ActiveEcuC</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>CanTrcv</SHORT-NAME><DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv</DEFINITION-REF>
  <CONTAINERS>
    <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvConfigSet</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet</DEFINITION-REF>
      <SUB-CONTAINERS>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvChannel_Ch1</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>1</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvHwPnSupport</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupByBusUsed</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvBaudrateRatio</DEFINITION-REF><VALUE>RATIO_LOWER_EQUALS_4</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvPartialNetwork</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvBaudRate</DEFINITION-REF><VALUE>1000</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnCanIdIsExtended</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnEnabled</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanId</DEFINITION-REF><VALUE>1365</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanIdMask</DEFINITION-REF><VALUE>2047</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDlc</DEFINITION-REF><VALUE>4</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvChannel_Ch0</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelId</DEFINITION-REF><VALUE>0</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvChannelUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvHwPnSupport</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupByBusUsed</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
            <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvBaudrateRatio</DEFINITION-REF><VALUE>RATIO_LOWER_EQUALS_10</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
          <REFERENCE-VALUES>
            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WS_BUS</VALUE-REF></ECUC-REFERENCE-VALUE>
            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvIcuChannelRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Icu/IcuConfigSet/IcuCh_Wakeup</VALUE-REF></ECUC-REFERENCE-VALUE>
            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPorWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WS_POR</VALUE-REF></ECUC-REFERENCE-VALUE>
            <ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvSyserrWakeupSourceRef</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/EcuM/EcuMConfiguration/EcuMCommonConfiguration/WS_SYS</VALUE-REF></ECUC-REFERENCE-VALUE>
          </REFERENCE-VALUES>
          <SUB-CONTAINERS>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvPartialNetwork</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvBaudRate</DEFINITION-REF><VALUE>250</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvBusErrFlag</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnCanIdIsExtended</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnEnabled</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanId</DEFINITION-REF><VALUE>305419896</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameCanIdMask</DEFINITION-REF><VALUE>536870911</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDlc</DEFINITION-REF><VALUE>6</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>Mask0</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec</DEFINITION-REF>
                  <PARAMETER-VALUES>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMaskIndex</DEFINITION-REF><VALUE>2</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMask</DEFINITION-REF><VALUE>171</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                  </PARAMETER-VALUES>
                </ECUC-CONTAINER-VALUE>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>Mask1</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec</DEFINITION-REF>
                  <PARAMETER-VALUES>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMaskIndex</DEFINITION-REF><VALUE>7</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                    <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvPartialNetwork/CanTrcvPnFrameDataMaskSpec/CanTrcvPnFrameDataMask</DEFINITION-REF><VALUE>205</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
                  </PARAMETER-VALUES>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvAccess</SHORT-NAME><DEFINITION-REF DEST="ECUC-CHOICE-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess</DEFINITION-REF>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvSpiSequence</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence</DEFINITION-REF>
                  <PARAMETER-VALUES><ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiAccessSynchronous</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE></PARAMETER-VALUES>
                  <SUB-CONTAINERS>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>SeqRWDataLarge</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess</DEFINITION-REF>
                      <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceIdentifier</DEFINITION-REF><VALUE>SeqRWDataLarge</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
                      <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceName</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Spi/Spi/SpiDriver/SEQ_L</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                    </ECUC-CONTAINER-VALUE>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>SeqRWDataMedium</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess</DEFINITION-REF>
                      <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceIdentifier</DEFINITION-REF><VALUE>SeqRWDataMedium</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
                      <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceName</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Spi/Spi/SpiDriver/SEQ_M</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                    </ECUC-CONTAINER-VALUE>
                    <ECUC-CONTAINER-VALUE><SHORT-NAME>SeqRWDataNormal</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess</DEFINITION-REF>
                      <PARAMETER-VALUES><ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceIdentifier</DEFINITION-REF><VALUE>SeqRWDataNormal</VALUE></ECUC-TEXTUAL-PARAM-VALUE></PARAMETER-VALUES>
                      <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvChannel/CanTrcvAccess/CanTrcvSpiSequence/CanTrcvSpiSequenceAccess/CanTrcvSpiSequenceName</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/Spi/Spi/SpiDriver/SEQ_N</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
                    </ECUC-CONTAINER-VALUE>
                  </SUB-CONTAINERS>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
          </SUB-CONTAINERS>
        </ECUC-CONTAINER-VALUE>
        <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvDemEventParameterRefs</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvDemEventParameterRefs</DEFINITION-REF>
          <REFERENCE-VALUES><ECUC-REFERENCE-VALUE><DEFINITION-REF DEST="ECUC-SYMBOLIC-NAME-REFERENCE-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvConfigSet/CanTrcvDemEventParameterRefs/CANTRCV_E_BUS_ERROR</DEFINITION-REF><VALUE-REF DEST="ECUC-CONTAINER-VALUE">/ActiveEcuC/Dem/DemConfigSet/CANTRCV_E_BUS_ERROR</VALUE-REF></ECUC-REFERENCE-VALUE></REFERENCE-VALUES>
        </ECUC-CONTAINER-VALUE>
      </SUB-CONTAINERS>
    </ECUC-CONTAINER-VALUE>
    <ECUC-CONTAINER-VALUE><SHORT-NAME>CanTrcvGeneral</SHORT-NAME><DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
      <PARAMETER-VALUES>
        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvDevErrorDetect</DEFINITION-REF><VALUE>false</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvGetVersionInfo</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
        <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvWakeUpSupport</DEFINITION-REF><VALUE>CANTRCV_WAKEUP_NOT_SUPPORTED</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvIndex</DEFINITION-REF><VALUE>2</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
        <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvTimerType</DEFINITION-REF><VALUE>Timer_1us16bit</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
        <ECUC-NUMERICAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvSafeBswChecks</DEFINITION-REF><VALUE>true</VALUE></ECUC-NUMERICAL-PARAM-VALUE>
        <ECUC-TEXTUAL-PARAM-VALUE><DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral/CanTrcvUserConfigFile</DEFINITION-REF><VALUE>CanTrcv_UserCfg.h</VALUE></ECUC-TEXTUAL-PARAM-VALUE>
      </PARAMETER-VALUES>
    </ECUC-CONTAINER-VALUE>
  </CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>
</ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>""",
        ct_def,
    )

    gen = CodeGenerator(
        ct_def,
        ct_cfg,
        package_template_dir=TLE9255_TEMPLATE_DIR,
        all_configurations={
            "CanTrcv": (ct_def, ct_cfg),
            "Spi": (spi_def, spi_cfg),
            "EcuM": (ecum_def, ecum_cfg),
            "Icu": (icu_def, icu_cfg),
            "Dem": (dem_def, dem_cfg),
            "vSet": (vset_def, vset_cfg),
            "EcuC": (ecuc_def, ecuc_cfg),
        },
    )
    assert gen.generate_all(tmp_path, flat=True) is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    h_text = (tmp_path / "include" / "CanTrcv_30_Tle9255_Cfg.h").read_text(encoding="utf-8")
    c_text = (tmp_path / "src" / "CanTrcv_30_Tle9255_Cfg.c").read_text(encoding="utf-8")
    _audit_rendered_output(h_text, c_text)

    # Header switches & conditional includes
    assert '#include "Icu.h"' in h_text
    assert '#include "Dem.h"' in h_text
    assert "#define CANTRCV_30_TLE9255_MAX_CHANNEL                       2u" in h_text
    assert (
        "#define CANTRCV_30_TLE9255_GENERAL_WAKE_UP_SUPPORT           CANTRCV_30_TLE9255_WAKEUP_NOT_SUPPORTED"
        in h_text
    )
    assert "#define CANTRCV_30_TLE9255_WAKEUP_BY_BUS_USED                STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_GET_VERSION_INFO                  STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_DEV_ERROR_DETECT                  STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_DEV_ERROR_REPORT                  STD_OFF" in h_text
    assert "#define CANTRCV_30_TLE9255_ECUC_SAFE_BSW_CHECKS              STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_PROD_ERROR_DETECT                 STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_INSTANCE_ID                       2" in h_text
    assert "#define CANTRCV_30_TLE9255_HW_PN_SUPPORT                     STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_BUS_ERR_FLAG                      STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_SPI_ACCESS_SYNCHRONOUS            STD_OFF" in h_text
    assert "#define CANTRCV_30_TLE9255_USE_ICU                           STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_USE_EXTENDED_WU_SRC               STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_SET_OP_MODE_WAIT_TIME_SUPPORT     STD_ON" in h_text

    # Symbolic channel ordering & vSet/EcuC overrides
    idx_ch0 = h_text.index("#define CanTrcv_30_Tle9255_CanTrcvChannel_Ch0 0u")
    idx_ch1 = h_text.index("#define CanTrcv_30_Tle9255_CanTrcvChannel_Ch1 1u")
    assert idx_ch0 < idx_ch1
    assert "#define CANTRCV_30_TLE9255_DUMMY_STATEMENT(v) (void)(v)" in h_text
    assert "#define CANTRCV_30_TLE9255_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_ATOMIC_VARIABLE_ACCESS 16u" in h_text
    assert "#define CANTRCV_30_TLE9255_CPUTYPE_BITORDER_MSB2LSB" in h_text
    assert '#include "CanTrcv_UserCfg.h"\n#endif /* CANTRCV_30_TLE9255_CFG_H */' in h_text.replace("\r\n", "\n")

    # Conditional CSL switches & prototypes
    assert "#define CANTRCV_30_TLE9255_CHANNEL                                    STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_PNENABLED                                  STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_WUSRCPOR                                   STD_ON" in h_text
    assert "#define CANTRCV_30_TLE9255_WUSRCSYSERR                                STD_ON" in h_text
    assert "typedef EcuM_WakeupSourceType CanTrcv_30_Tle9255_WakeupSourceType;" in h_text
    assert "extern CONST(CanTrcv_30_Tle9255_ChannelType, CANTRCV_30_TLE9255_CONST) CanTrcv_30_Tle9255_Channel[2];" in h_text
    assert "extern CONST(CanTrcv_30_Tle9255_PnEnabledType, CANTRCV_30_TLE9255_CONST) CanTrcv_30_Tle9255_PnEnabled[2];" in h_text
    assert "extern CONST(CanTrcv_30_Tle9255_WuSrcPorType, CANTRCV_30_TLE9255_CONST) CanTrcv_30_Tle9255_WuSrcPor[2];" in h_text
    assert "extern CONST(CanTrcv_30_Tle9255_WuSrcSyserrType, CANTRCV_30_TLE9255_CONST) CanTrcv_30_Tle9255_WuSrcSyserr[2];" in h_text

    # Source file computed values: Ch0 (extended 0x12345678, mask 0x1FFFFFFF, 250kbps | RATIO_LOWER_EQUALS_10 -> 19u, dlc 6)
    assert "/* 0 */ 19u  /* (=250 KBit/s) */, 0x78u  /* (CanId = 0x12345678u) */, 0x56u, 0x34u, 0x32u, 0xFFu  /* (MASK=0x1FFFFFFFu) */, 0xFFu, 0xFFu, 0x1Fu, 0x06u" in c_text
    # Ch1 (standard 0x555, mask 0x7FF, 1000kbps | RATIO_LOWER_EQUALS_4 -> 5u, dlc 4)
    assert "/* 1 */ 5u  /* (=1000 KBit/s) */, 0x00u  /* (CanId = 0x00000555u) */, 0x00u, 0x54u, 0x15u, 0x00u  /* (MASK=0x000007FFu) */, 0x00u, 0xFCu, 0x1Fu, 0x04u" in c_text
    # PnPayloadCfg DataMaskSpec on Ch0 (index 2=0xAB, 7=0xCD)
    assert "{ /* 0 */ 0x00u, 0x00u, 0xABu, 0x00u, 0x00u, 0x00u, 0x00u, 0xCDu }," in c_text
    # PnEnabled
    assert "/* 0 */ TRUE,\n  /* 1 */ FALSE" in c_text.replace("\r\n", "\n")
    # Resolved SPI channels ordered by SpiChannelIndex (ChA, ChB, ChC) and sequences
    assert "{ /* 0 */ SpiConf_SpiChannel_ChA, SpiConf_SpiChannel_ChB, SpiConf_SpiChannel_ChC }," in c_text
    assert "{ /* 0 */ SpiConf_SpiSequence_SEQ_L, SpiConf_SpiSequence_SEQ_M, SpiConf_SpiSequence_SEQ_N }," in c_text
    # ICU & wakeup sources
    assert "{ /* 0 */ IcuConf_IcuChannel_IcuCh_Wakeup, TRUE }," in c_text
    assert "/* 0 */ ((EcuM_WakeupSourceType)1u << EcuMConf_EcuMWakeupSource_WS_BUS)," in c_text
    assert "/* 0 */ ((EcuM_WakeupSourceType)1u << EcuMConf_EcuMWakeupSource_WS_POR)," in c_text
    assert "/* 0 */ ((EcuM_WakeupSourceType)1u << EcuMConf_EcuMWakeupSource_WS_SYS)," in c_text


@pytest.mark.skipif(
    not (
        TEST2_PROJECT_DPA.is_file()
        and TLE9255_TEMPLATE_DIR.is_dir()
        and REF_CFG_H.is_file()
        and REF_CFG_C.is_file()
    ),
    reason="Local test2 project and DaVinci reference fixtures not present",
)
def test_test2_project_generation_matches_davinci_reference(tmp_path):
    project, _ = WorkspaceManager().load_project(TEST2_PROJECT_DPA)
    assert "CanTrcv" in project.packages
    pkg = project.packages["CanTrcv"]
    assert pkg.template_dir() == TLE9255_TEMPLATE_DIR

    ct_mgr = project.module_managers["CanTrcv"]
    all_cfgs = {name: (m.module_def, m.configuration) for name, m in project.module_managers.items()}
    gen = CodeGenerator(
        ct_mgr.module_def,
        ct_mgr.configuration,
        all_configurations=all_cfgs,
        package_template_dir=pkg.template_dir(),
    )
    assert gen.generate_all(tmp_path) is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    gen_h = (tmp_path / "CanTrcv" / "include" / "CanTrcv_30_Tle9255_Cfg.h").read_text(encoding="utf-8")
    gen_c = (tmp_path / "CanTrcv" / "src" / "CanTrcv_30_Tle9255_Cfg.c").read_text(encoding="utf-8")
    _audit_rendered_output(gen_h, gen_c)

    ref_h = REF_CFG_H.read_text(encoding="utf-8")
    ref_c = REF_CFG_C.read_text(encoding="utf-8")

    def _normalize_body(text: str, marker: str) -> str:
        body = text[text.index(marker) :].replace("\r\n", "\n")
        # Collapse blank lines for strict structural/token comparison
        lines = [ln.rstrip() for ln in body.splitlines() if ln.strip()]
        return "\n".join(lines)

    assert _normalize_body(gen_h, "#if !defined(CANTRCV_30_TLE9255_CFG_H)") == _normalize_body(
        ref_h, "#if !defined(CANTRCV_30_TLE9255_CFG_H)"
    )

    def _normalize_c_ws(text: str, marker: str) -> str:
        body = text[text.index(marker) :].replace("\r\n", "\n")
        lines = [re.sub(r"[ \t]+", " ", ln.strip()) for ln in body.splitlines() if ln.strip()]
        return "\n".join(lines)

    assert _normalize_c_ws(gen_c, '#include "CanTrcv_30_Tle9255.h"') == _normalize_c_ws(
        ref_c, '#include "CanTrcv_30_Tle9255.h"'
    )
