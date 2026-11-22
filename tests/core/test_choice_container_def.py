"""ECUC-CHOICE-CONTAINER-DEF <CHOICES> children must be resolvable as sub-containers.

Configurations reference choice targets like ordinary nested containers, e.g.
/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue/BswMBswMode.
The parser used to mark the choice container is_choice=True but drop its <CHOICES>
children, so those definition references failed to resolve.
"""
from pathlib import Path

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

DEF = """<?xml version='1.0' encoding='UTF-8'?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>AUTOSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>BswM</SHORT-NAME>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>BswMConfig</SHORT-NAME>
              <SUB-CONTAINERS>
                <ECUC-PARAM-CONF-CONTAINER-DEF>
                  <SHORT-NAME>BswMArbitration</SHORT-NAME>
                  <SUB-CONTAINERS>
                    <ECUC-PARAM-CONF-CONTAINER-DEF>
                      <SHORT-NAME>BswMModeCondition</SHORT-NAME>
                      <SUB-CONTAINERS>
                        <ECUC-CHOICE-CONTAINER-DEF>
                          <SHORT-NAME>BswMConditionValue</SHORT-NAME>
                          <CHOICES>
                            <ECUC-PARAM-CONF-CONTAINER-DEF>
                              <SHORT-NAME>BswMBswMode</SHORT-NAME>
                            </ECUC-PARAM-CONF-CONTAINER-DEF>
                            <ECUC-PARAM-CONF-CONTAINER-DEF>
                              <SHORT-NAME>BswMModeDeclaration</SHORT-NAME>
                            </ECUC-PARAM-CONF-CONTAINER-DEF>
                          </CHOICES>
                        </ECUC-CHOICE-CONTAINER-DEF>
                      </SUB-CONTAINERS>
                    </ECUC-PARAM-CONF-CONTAINER-DEF>
                  </SUB-CONTAINERS>
                </ECUC-PARAM-CONF-CONTAINER-DEF>
              </SUB-CONTAINERS>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
          </CONTAINERS>
        </ECUC-MODULE-DEF>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


def test_choices_are_parsed_as_sub_containers(tmp_path: Path):
    path = tmp_path / "BswM.arxml"
    path.write_text(DEF, encoding="utf-8")
    module_def = EcucDefParser().parse_module_def_file(path)

    # The choice container itself is flagged is_choice and kept as a sub-container.
    condition_value = module_def.get_container_def(
        "BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue"
    )
    assert condition_value is not None
    assert condition_value.is_choice

    # Its <CHOICES> children resolve as ordinary nested containers.
    for choice in ("BswMBswMode", "BswMModeDeclaration"):
        target = module_def.get_container_def(
            f"BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue/{choice}"
        )
        assert target is not None, f"choice {choice} not resolvable"
        assert target.short_name == choice


def test_container_without_choices_is_unaffected(tmp_path: Path):
    # Remove the entire <CHOICES>…</CHOICES> block; the parent container must parse.
    start = DEF.index("<CHOICES>")
    end = DEF.index("</CHOICES>") + len("</CHOICES>")
    stripped = DEF[:start] + DEF[end:]
    path = tmp_path / "BswM.arxml"
    path.write_text(stripped, encoding="utf-8")
    module_def = EcucDefParser().parse_module_def_file(path)
    condition_value = module_def.get_container_def(
        "BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue"
    )
    assert condition_value is not None


def test_instance_suffix_stripping_accepts_u_index(tmp_path: Path):
    """EB names instances _N (digits) or _U<N>/_<letter>N (e.g. CanTrcvChannel_U12);
    both must resolve to their container definition."""
    path = tmp_path / "BswM.arxml"
    path.write_text(DEF, encoding="utf-8")
    module_def = EcucDefParser().parse_module_def_file(path)

    # Pure-digit suffix still works.
    assert module_def.get_container_def(
        "BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue_0"
    ).short_name == "BswMConditionValue"

    # _U<N> suffix works too.
    assert module_def.get_container_def(
        "BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue_U12"
    ).short_name == "BswMConditionValue"

    # Deeper segment, and a letter+digit suffix on a nested container.
    assert module_def.get_container_def(
        "BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue_U12/BswMBswMode_1"
    ).short_name == "BswMBswMode"