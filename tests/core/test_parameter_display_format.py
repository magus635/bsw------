"""DV:Display metadata (DefaultFormat, Unit, BaseUnit) is read from the definition."""
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
       <SHORT-NAME>DemoAddress</SHORT-NAME>
       <ADMIN-DATA><SDGS><SDG GID="DV:Display">
        <SD GID="DV:DefaultFormat">HEX</SD>
       </SDG></SDGS></ADMIN-DATA>
       <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
       <DEFAULT-VALUE>0</DEFAULT-VALUE><MIN>0</MIN><MAX>18446744073709551615</MAX>
      </ECUC-INTEGER-PARAM-DEF>
      <ECUC-INTEGER-PARAM-DEF>
       <SHORT-NAME>DemoFrequency</SHORT-NAME>
       <ADMIN-DATA><SDGS><SDG GID="DV:Display">
        <SD GID="DV:BaseUnit">HZ</SD><SD GID="DV:Unit">MHZ</SD>
       </SDG></SDGS></ADMIN-DATA>
       <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
       <MIN>0</MIN><MAX>400000000</MAX>
      </ECUC-INTEGER-PARAM-DEF>
      <ECUC-INTEGER-PARAM-DEF>
       <SHORT-NAME>DemoPlain</SHORT-NAME>
       <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
       <MIN>0</MIN><MAX>10</MAX>
      </ECUC-INTEGER-PARAM-DEF>
     </PARAMETERS>
    </ECUC-PARAM-CONF-CONTAINER-DEF>
   </CONTAINERS>
  </ECUC-MODULE-DEF>
 </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>
"""


def _params(tmp_path):
    path = tmp_path / "Demo_bswmd.arxml"
    path.write_text(BSWMD, encoding="utf-8")
    module = EcucDefParser().parse_module_def_file(path)
    return module.containers["DemoGeneral"].parameters


def test_hex_default_format_is_read(tmp_path):
    assert _params(tmp_path)["DemoAddress"].display_format == "HEX"


def test_unit_and_base_unit_are_read(tmp_path):
    frequency = _params(tmp_path)["DemoFrequency"]
    assert (frequency.display_base_unit, frequency.display_unit) == ("HZ", "MHZ")


def test_no_display_metadata_leaves_the_format_unset(tmp_path):
    plain = _params(tmp_path)["DemoPlain"]
    assert plain.display_format is None and plain.display_unit is None
