"""Addresses and sizes typed as 0x… are accepted for integer parameters."""
from pathlib import Path

import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

BSWMD = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
 <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
  <ECUC-MODULE-DEF>
   <SHORT-NAME>Demo</SHORT-NAME>
   <CONTAINERS>
    <ECUC-PARAM-CONF-CONTAINER-DEF>
     <SHORT-NAME>DemoGeneral</SHORT-NAME>
     <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
     <PARAMETERS>
      <ECUC-INTEGER-PARAM-DEF>
       <SHORT-NAME>DemoStartAddress</SHORT-NAME>
       <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
       <MIN>0</MIN><MAX>18446744073709551615</MAX>
      </ECUC-INTEGER-PARAM-DEF>
     </PARAMETERS>
    </ECUC-PARAM-CONF-CONTAINER-DEF>
   </CONTAINERS>
  </ECUC-MODULE-DEF>
 </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>
"""

CFG = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
 <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
  <ECUC-MODULE-CONFIGURATION-VALUES>
   <SHORT-NAME>Demo</SHORT-NAME>
   <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Demo</DEFINITION-REF>
   <CONTAINERS>
    <ECUC-CONTAINER-VALUE>
     <SHORT-NAME>DemoGeneral</SHORT-NAME>
     <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Demo/DemoGeneral</DEFINITION-REF>
    </ECUC-CONTAINER-VALUE>
   </CONTAINERS>
  </ECUC-MODULE-CONFIGURATION-VALUES>
 </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>
"""


@pytest.fixture
def configured(tmp_path):
    def_path = tmp_path / "Demo_bswmd.arxml"
    def_path.write_text(BSWMD, encoding="utf-8")
    cfg_path = tmp_path / "Demo_ecuc.arxml"
    cfg_path.write_text(CFG, encoding="utf-8")

    manager = ConfigurationManager(EcucDefParser().parse_module_def_file(def_path))
    manager.load_configuration(cfg_path)
    return manager, manager.configuration.containers[0]


@pytest.mark.parametrize("text, expected", [
    ("0x30000000", 0x30000000),
    ("0X30000000", 0x30000000),
    ("805306368", 805306368),
    ("  0x10000  ", 0x10000),
])
def test_hex_and_decimal_text_are_both_accepted(configured, text, expected):
    manager, instance = configured
    assert manager.convert_parameter_value(instance, "DemoStartAddress", text) == expected


def test_a_hex_value_is_checked_against_the_range(configured):
    manager, instance = configured
    with pytest.raises(Exception):
        manager.convert_parameter_value(instance, "DemoStartAddress", "0x1FFFFFFFFFFFFFFFF")
