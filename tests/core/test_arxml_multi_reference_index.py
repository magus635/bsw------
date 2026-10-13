"""Multi-valued references written by EB tresos: the first element has no INDEX, the next ones INDEX 1, 2, ...

The first element used to stay a single value while the others went to the list, so iterating the
reference (./OsAppIsrRef/* in templates) silently missed it.
"""
from lxml import etree

from autosar_configurator.core.parser.arxml_parser import ArxmlParser

NS = "http://autosar.org/schema/r4.0"
DEF = "/Mod/Container/RefList"


def _module(refs):
    items = ""
    for index, target in refs:
        idx = f"<INDEX>{index}</INDEX>" if index is not None else ""
        items += f"""
        <ECUC-REFERENCE-VALUE>{idx}
          <DEFINITION-REF DEST="ECUC-REFERENCE-DEF">{DEF}</DEFINITION-REF>
          <VALUE-REF DEST="ECUC-CONTAINER-VALUE">{target}</VALUE-REF>
        </ECUC-REFERENCE-VALUE>"""
    return etree.fromstring(f"""
<ECUC-MODULE-CONFIGURATION-VALUES xmlns="{NS}">
  <SHORT-NAME>Mod</SHORT-NAME>
  <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Mod</DEFINITION-REF>
  <CONTAINERS>
    <ECUC-CONTAINER-VALUE>
      <SHORT-NAME>C0</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Mod/Container</DEFINITION-REF>
      <REFERENCE-VALUES>{items}
      </REFERENCE-VALUES>
    </ECUC-CONTAINER-VALUE>
  </CONTAINERS>
</ECUC-MODULE-CONFIGURATION-VALUES>""".encode("utf-8"))


def _targets(refs):
    config = ArxmlParser().parse_ecuc_configuration_values(_module(refs))
    (container,) = config.containers
    return container, [r.value_ref for r in container.multi_reference_values.get("RefList", [])]


def test_first_element_without_index_joins_the_list():
    container, targets = _targets([(None, "/Mod/A"), (1, "/Mod/B"), (2, "/Mod/C")])
    assert targets == ["/Mod/A", "/Mod/B", "/Mod/C"]
    assert "RefList" not in container.reference_values
    assert [r.index for r in container.multi_reference_values["RefList"]] == [0, 1, 2]


def test_single_element_stays_a_single_value():
    container, targets = _targets([(None, "/Mod/A")])
    assert targets == []
    assert container.reference_values["RefList"].value_ref == "/Mod/A"


def test_all_elements_with_index_are_unchanged():
    _, targets = _targets([(0, "/Mod/A"), (1, "/Mod/B")])
    assert targets == ["/Mod/A", "/Mod/B"]
