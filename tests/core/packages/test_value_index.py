"""Tests for value collection indexing and in-package merge by AUTOSAR path."""
import pytest
from pathlib import Path
from lxml import etree

from autosar_configurator.core.packages.value_index import (
    index_value_collections,
    load_value_collection,
)
from autosar_configurator.core.packages.errors import PackageConflictError
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration


def test_one_file_holds_pre_and_rec(tmp_path: Path):
    """One arxml file contains both /MICROSAR/X_Pre and /MICROSAR/X_Rec.

    Index should return two separate keys, each with its own containers.
    """
    arxml_file = tmp_path / "both.arxml"
    arxml_file.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://autosar.org/schema/r4.0 AUTOSAR_00048.xsd">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>X_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/X</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>PreContainer</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/X/XConfig</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>X_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/X</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>RecContainer</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/X/XConfig</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
""", encoding="utf-8")

    index = index_value_collections(arxml_file)

    assert "/MICROSAR/X_Pre" in index
    assert "/MICROSAR/X_Rec" in index

    # Each key should have exactly one config
    assert len(index["/MICROSAR/X_Pre"]) == 1
    assert len(index["/MICROSAR/X_Rec"]) == 1

    # Check containers are separate
    pre_config = index["/MICROSAR/X_Pre"][0]
    rec_config = index["/MICROSAR/X_Rec"][0]

    assert len(pre_config.containers) == 1
    assert pre_config.containers[0].short_name == "PreContainer"

    assert len(rec_config.containers) == 1
    assert rec_config.containers[0].short_name == "RecContainer"


def test_same_path_two_files_merged(tmp_path: Path):
    """Two files both declare /MICROSAR/X_Pre with different containers.

    Merge should combine both containers.
    """
    file1 = tmp_path / "file1.arxml"
    file1.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>X_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/X</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>Container1</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/X/XConfig</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
""", encoding="utf-8")

    file2 = tmp_path / "file2.arxml"
    file2.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>X_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/X</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>Container2</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/X/XConfig</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
""", encoding="utf-8")

    merged = load_value_collection([file1, file2], "/MICROSAR/X_Pre")

    assert merged is not None
    assert len(merged.containers) == 2
    container_names = {c.short_name for c in merged.containers}
    assert container_names == {"Container1", "Container2"}


def test_same_param_conflict_raises(tmp_path: Path):
    """Two files have the same parameter with different values.

    Should raise PackageConflictError with the parameter path and file list.
    """
    file1 = tmp_path / "file1.arxml"
    file1.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>X_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/X</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>MyContainer</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/X/XConfig</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/X/XConfig/MyParam</DEFINITION-REF>
                  <VALUE>1</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
""", encoding="utf-8")

    file2 = tmp_path / "file2.arxml"
    file2.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>X_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/X</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>MyContainer</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/X/XConfig</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/MICROSAR/X/XConfig/MyParam</DEFINITION-REF>
                  <VALUE>2</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
""", encoding="utf-8")

    with pytest.raises(PackageConflictError) as exc_info:
        load_value_collection([file1, file2], "/MICROSAR/X_Pre")

    error = exc_info.value
    assert "MyContainer.MyParam" in error.path or "/MyParam" in error.path
    assert len(error.files) == 2
    assert any("file1.arxml" in str(f) for f in error.files)
    assert any("file2.arxml" in str(f) for f in error.files)


def test_xdm_preconfiguration_indexed(tmp_path: Path):
    """Real fixture: McuPreConfiguration.xdm indexed with path /THA6_AS440_FuSa/McuPreConfiguration."""
    fixture_path = Path("test_import_project/Def/plugins/Mcu_THA6_AS440/config/McuPreConfiguration.xdm")
    if not fixture_path.exists():
        pytest.skip(f"Fixture not found: {fixture_path}")

    index = index_value_collections(fixture_path)

    assert "/THA6_AS440_FuSa/McuPreConfiguration" in index
    configs = index["/THA6_AS440_FuSa/McuPreConfiguration"]
    assert len(configs) == 1

    config = configs[0]
    assert config.short_name == "McuPreConfiguration"

    # Check for McuPublishedInformation container
    assert any(c.short_name == "McuPublishedInformation" for c in config.containers)


def test_nested_package_path(tmp_path: Path):
    """Nested package /MICROSAR/VTT/X_Pre has correct AR path."""
    arxml_file = tmp_path / "nested.arxml"
    arxml_file.write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>VTT</SHORT-NAME>
          <ELEMENTS>
            <ECUC-MODULE-CONFIGURATION-VALUES>
              <SHORT-NAME>X_Pre</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/X</DEFINITION-REF>
              <CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                  <SHORT-NAME>NestedContainer</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/X/XConfig</DEFINITION-REF>
                </ECUC-CONTAINER-VALUE>
              </CONTAINERS>
            </ECUC-MODULE-CONFIGURATION-VALUES>
          </ELEMENTS>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
""", encoding="utf-8")

    index = index_value_collections(arxml_file)

    assert "/MICROSAR/VTT/X_Pre" in index
    assert len(index["/MICROSAR/VTT/X_Pre"]) == 1
    assert index["/MICROSAR/VTT/X_Pre"][0].short_name == "X_Pre"


def test_key_helpers_use_container_path():
    from autosar_configurator.core.model.configuration_model import EcucContainerValue
    from autosar_configurator.core.packages.value_index import container_key, param_key, ref_key

    parent = EcucContainerValue(short_name="McuGeneralConfiguration", definition_ref="/V/Mcu/G")
    parent.module_name = "Mcu"
    child = EcucContainerValue(short_name="Clk", definition_ref="/V/Mcu/G/Clk")
    child.parent = parent
    assert container_key(child) == "C:/Mcu/McuGeneralConfiguration/Clk"
    assert param_key(child, "McuFreq") == "P:/Mcu/McuGeneralConfiguration/Clk.McuFreq"
    assert ref_key(child, "McuRef") == "R:/Mcu/McuGeneralConfiguration/Clk.McuRef"
    assert param_key(child, "Same") != ref_key(child, "Same")
