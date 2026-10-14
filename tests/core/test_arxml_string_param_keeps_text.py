"""A parameter whose definition is a string type keeps its text when the ARXML is parsed.

"TRUE" in an ArtiConstantString (a C constant such as the OsStackMonitoring OS_CONFIG value) used to be turned
into the Python bool True by the parser and written back as "true".
"""
import pytest
from lxml import etree

from autosar_configurator.core.parser.arxml_parser import ArxmlParser

DEF = "/AUTOSAR/EcucDefs/Arti"


def _arxml(*params):
    body = "".join(params)
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Arti</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>Arti</SHORT-NAME>
<DEFINITION-REF DEST="ECUC-MODULE-DEF">{DEF}</DEFINITION-REF>
<CONTAINERS><ECUC-CONTAINER-VALUE><SHORT-NAME>C</SHORT-NAME>
<DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{DEF}/C</DEFINITION-REF>
<PARAMETER-VALUES>{body}</PARAMETER-VALUES></ECUC-CONTAINER-VALUE></CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES></ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>"""


def _p(kind, dest, name, value):
    return (f"<ECUC-{kind}-PARAM-VALUE><DEFINITION-REF DEST=\"{dest}\">{DEF}/C/{name}</DEFINITION-REF>"
            f"<VALUE>{value}</VALUE></ECUC-{kind}-PARAM-VALUE>")


def _values(*params):
    root = etree.fromstring(_arxml(*params).encode("utf-8"))
    (module,) = ArxmlParser().parse_all_module_configurations(root)
    (container,) = module.containers
    return {n: pv.value for n, pv in container.parameter_values.items()}


@pytest.mark.parametrize("dest", ["ECUC-STRING-PARAM-DEF", "ECUC-MULTILINE-STRING-PARAM-DEF",
                                  "ECUC-FUNCTION-NAME-DEF", "ECUC-LINKER-SYMBOL-DEF"])
@pytest.mark.parametrize("text", ["TRUE", "true", "False", "FALSE"])
def test_string_parameters_keep_their_text(dest, text):
    assert _values(_p("TEXTUAL", dest, "S", text))["S"] == text


def test_boolean_parameters_still_become_bool():
    values = _values(
        _p("NUMERICAL", "ECUC-BOOLEAN-PARAM-DEF", "B1", "true"),
        _p("NUMERICAL", "ECUC-BOOLEAN-PARAM-DEF", "B2", "false"),
        _p("NUMERICAL", "ECUC-BOOLEAN-PARAM-DEF", "B3", "1"),
        _p("NUMERICAL", "ECUC-BOOLEAN-PARAM-DEF", "B4", "0"),
        _p("NUMERICAL", "ECUC-BOOLEAN-PARAM-DEF", "B5", "TRUE"),
    )
    assert values == {"B1": True, "B2": False, "B3": True, "B4": False, "B5": True}
    assert all(type(v) is bool for v in values.values())


def test_other_parameters_are_unchanged():
    values = _values(_p("TEXTUAL", "ECUC-ENUMERATION-PARAM-DEF", "E", "true"),
                     _p("NUMERICAL", "ECUC-INTEGER-PARAM-DEF", "I", "42"))
    assert values["E"] is True       # enumerations keep the previous behaviour
    assert values["I"] == 42
