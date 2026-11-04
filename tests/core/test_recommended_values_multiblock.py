import pytest
from pathlib import Path
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType,
)

DEF_PATH = Path("D:/davinci/mcuapp/Components/EcuC/BSWMD/EcuC_bswmd.arxml")
REC_PATH = Path("D:/davinci/mcuapp/Components/EcuC/BSWMD/EcuC_preo_Arm32_LlvmHighTec.arxml")


def _build_mock_ecuc_module_def() -> EcucModuleDef:
    """Create a self-contained EcucModuleDef with nested sub-containers for unit testing."""
    module_def = EcucModuleDef(short_name="EcuC", definition_ref="/MICROSAR/EcuC")

    general_def = EcucContainerDef(
        short_name="EcucGeneral",
        definition_ref="/MICROSAR/EcuC/EcucGeneral",
        lower_multiplicity=1,
        upper_multiplicity=1,
    )
    general_def.add_parameter(
        EcucParameterDef(
            short_name="CPUType",
            param_type=EcucParameterType.ENUMERATION,
            definition_ref="/MICROSAR/EcuC/EcucGeneral/CPUType",
            literals=["CPU8Bit", "CPU16Bit", "CPU32Bit", "CPU64Bit"],
        )
    )
    general_def.add_parameter(
        EcucParameterDef(
            short_name="ByteOrder",
            param_type=EcucParameterType.ENUMERATION,
            definition_ref="/MICROSAR/EcuC/EcucGeneral/ByteOrder",
            literals=["BIG_ENDIAN", "LITTLE_ENDIAN"],
        )
    )
    general_def.add_parameter(
        EcucParameterDef(
            short_name="DummyFunction",
            param_type=EcucParameterType.BOOLEAN,
            definition_ref="/MICROSAR/EcuC/EcucGeneral/DummyFunction",
        )
    )

    sub_def = EcucContainerDef(
        short_name="EcucBswInitialization",
        definition_ref="/MICROSAR/EcuC/EcucGeneral/EcucBswInitialization",
        lower_multiplicity=0,
        upper_multiplicity=1,
    )
    sub_def.add_parameter(
        EcucParameterDef(
            short_name="InitPhase",
            param_type=EcucParameterType.STRING,
            definition_ref="/MICROSAR/EcuC/EcucGeneral/EcucBswInitialization/InitPhase",
        )
    )
    general_def.add_sub_container(sub_def)
    module_def.add_container(general_def)
    return module_def


@pytest.mark.skipif(not DEF_PATH.exists() or not REC_PATH.exists(), reason="EcuC ARXML files not found")
def test_load_recommended_values_real_ecuc_files():
    def_parser = EcucDefParser()
    module_def = def_parser.parse_module_def_file(DEF_PATH)
    cm = ConfigurationManager(module_def)

    assert len(cm.configuration.containers) == 0

    rec_config = cm.load_recommended_values(REC_PATH)
    assert rec_config is not None

    general_container = next((c for c in rec_config.containers if c.short_name == "EcucGeneral"), None)
    assert general_container is not None
    assert len(general_container.parameter_values) == 15
    assert "CPUType" in general_container.parameter_values
    assert "DummyFunction" in general_container.parameter_values

    comparisons = cm.get_recommended_value_comparison(rec_config)
    assert len(comparisons) == 15
    for comp in comparisons:
        assert comp["current_value"] is None
        assert comp["differs"] is True

    applied = cm.apply_recommended_values(rec_config, only_empty=False)
    assert applied == 15
    assert len(cm.configuration.containers) == 1
    applied_container = cm.configuration.containers[0]
    assert applied_container.short_name == "EcucGeneral"
    assert applied_container.parameter_values["CPUType"].value == "CPU32Bit"
    assert applied_container.parameter_values["DummyFunction"].value == 0


def test_pre_takes_precedence_over_rec_and_ignores_other_modules(tmp_path: Path):
    """Verify _Pre overrides _Rec even if _Rec appears first in XML, and unrelated modules are ignored."""
    arxml_content = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>OtherModule_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/OtherModule</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>OtherGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/OtherModule/OtherGeneral</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>EcuC_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuC</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>EcucGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-TEXTUAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/CPUType</DEFINITION-REF>
                  <VALUE>CPU16Bit</VALUE>
                </ECUC-TEXTUAL-PARAM-VALUE>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/DummyFunction</DEFINITION-REF>
                  <VALUE>1</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>EcuC_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuC</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>EcucGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-TEXTUAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/CPUType</DEFINITION-REF>
                  <VALUE>CPU32Bit</VALUE>
                </ECUC-TEXTUAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""
    rec_file = tmp_path / "EcuC_preo.arxml"
    rec_file.write_text(arxml_content, encoding="utf-8")

    cm = ConfigurationManager(_build_mock_ecuc_module_def())
    rec_config = cm.load_recommended_values(rec_file)
    assert rec_config is not None

    # Unrelated module container should be filtered out
    container_names = [c.short_name for c in rec_config.containers]
    assert container_names == ["EcucGeneral"]

    # _Pre value (CPU32Bit) must win over _Rec value (CPU16Bit)
    general = rec_config.containers[0]
    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert general.parameter_values["DummyFunction"].value == 1


def test_sub_container_auto_creation_and_only_empty_flag(tmp_path: Path):
    """Verify nested sub-containers are compared and auto-created, and only_empty is respected."""
    arxml_content = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>EcuC_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuC</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>EcucGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-TEXTUAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/CPUType</DEFINITION-REF>
                  <VALUE>CPU32Bit</VALUE>
                </ECUC-TEXTUAL-PARAM-VALUE>
                <ECUC-TEXTUAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-ENUMERATION-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/ByteOrder</DEFINITION-REF>
                  <VALUE>LITTLE_ENDIAN</VALUE>
                </ECUC-TEXTUAL-PARAM-VALUE>
              </PARAMETER-VALUES>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                  <SHORT-NAME>EcucBswInitialization</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucGeneral/EcucBswInitialization</DEFINITION-REF>
                  <PARAMETER-VALUES>
                    <ECUC-TEXTUAL-PARAM-VALUE>
                      <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/EcuC/EcucGeneral/EcucBswInitialization/InitPhase</DEFINITION-REF>
                      <VALUE>INIT_ONE</VALUE>
                    </ECUC-TEXTUAL-PARAM-VALUE>
                  </PARAMETER-VALUES>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""
    rec_file = tmp_path / "EcuC_rec_nested.arxml"
    rec_file.write_text(arxml_content, encoding="utf-8")

    module_def = _build_mock_ecuc_module_def()
    cm = ConfigurationManager(module_def)

    # Pre-create EcucGeneral with a user-set CPUType="CPU64Bit", leaving ByteOrder unset
    general_inst = cm.create_container_instance(module_def.containers["EcucGeneral"])
    general_inst.set_parameter_value("CPUType", "CPU64Bit", "/MICROSAR/EcuC/EcucGeneral/CPUType")
    # Clear smart default on ByteOrder to simulate an empty parameter
    general_inst.parameter_values.pop("ByteOrder", None)

    rec_config = cm.load_recommended_values(rec_file)
    comparisons = cm.get_recommended_value_comparison(rec_config)
    paths = {c["param_path"]: c for c in comparisons}
    assert "EcucGeneral/CPUType" in paths
    assert "EcucGeneral/ByteOrder" in paths
    assert "EcucGeneral/EcucBswInitialization/InitPhase" in paths
    assert paths["EcucGeneral/EcucBswInitialization/InitPhase"]["current_value"] is None

    # Apply with only_empty=True: CPUType must remain "CPU64Bit", ByteOrder & sub-container InitPhase must be set
    updated = cm.apply_recommended_values(rec_config, only_empty=True)
    assert updated == 2
    assert general_inst.parameter_values["CPUType"].value == "CPU64Bit"
    assert general_inst.parameter_values["ByteOrder"].value == "LITTLE_ENDIAN"
    assert len(general_inst.sub_containers) == 1
    assert general_inst.sub_containers[0].short_name == "EcucBswInitialization"
    assert general_inst.sub_containers[0].parameter_values["InitPhase"].value == "INIT_ONE"
