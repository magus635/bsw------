"""
Tests for EB value file import fidelity and round-trip preservation
(openspec change: improve-eb-value-roundtrip)
"""
import pytest
from pathlib import Path

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType,
)


def _make_demo_module_def() -> EcucModuleDef:
    """Module 'Demo' with one container 'DemoGeneral' knowing only 'KnownParam'"""
    param_def = EcucParameterDef(
        short_name="KnownParam",
        param_type=EcucParameterType.INTEGER,
    )
    container_def = EcucContainerDef(short_name="DemoGeneral")
    container_def.parameters["KnownParam"] = param_def

    module_def = EcucModuleDef(
        short_name="Demo",
        definition_ref="/AUTOSAR/EcucDefs/Demo",
    )
    module_def.containers["DemoGeneral"] = container_def
    return module_def


CONFIG_WITH_UNKNOWN_PARAM = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Demo_Config</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Demo</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Demo</DEFINITION-REF>
          <IMPLEMENTATION-CONFIG-VARIANT>VARIANT-PRE-COMPILE</IMPLEMENTATION-CONFIG-VARIANT>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DemoGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Demo/DemoGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Demo/DemoGeneral/KnownParam</DEFINITION-REF>
                  <VALUE>42</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
                <ECUC-TEXTUAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/EcucDefs/Demo/DemoGeneral/VendorOnlyParam</DEFINITION-REF>
                  <VALUE>vendor_secret</VALUE>
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


class TestUnknownParameterPreservation:
    """Unknown parameters survive import → save → reload (no silent data loss)"""

    def _load(self, tmp_path: Path) -> ConfigurationManager:
        config_file = tmp_path / "Demo_import.arxml"
        config_file.write_text(CONFIG_WITH_UNKNOWN_PARAM, encoding="utf-8")
        manager = ConfigurationManager(_make_demo_module_def())
        manager.load_configuration(config_file)
        return manager

    def _find_container(self, manager, name="DemoGeneral"):
        for c in manager.configuration.containers:
            if c.short_name == name:
                return c
        raise AssertionError(f"container {name} not found")

    def test_unknown_param_quarantined_on_import(self, tmp_path):
        manager = self._load(tmp_path)
        container = self._find_container(manager)

        # Known parameter stays in parameter_values
        assert "KnownParam" in container.parameter_values
        # Unknown parameter is flagged, but its value REMAINS in
        # parameter_values so the generator/templates can still read it
        # (Os vendor defs are incomplete; moving values would break codegen).
        assert "VendorOnlyParam" in container.unknown_parameters
        assert "VendorOnlyParam" in container.parameter_values
        assert container.unknown_parameters["VendorOnlyParam"].value == "vendor_secret"

    def test_unknown_param_survives_save_and_reload(self, tmp_path):
        manager = self._load(tmp_path)

        saved = tmp_path / "Demo_Config.arxml"
        manager.save_configuration(saved)

        # The raw file must still contain the unknown parameter
        text = saved.read_text(encoding="utf-8")
        assert "VendorOnlyParam" in text
        assert "vendor_secret" in text

        # Reload into a fresh manager: value intact, quarantined again
        manager2 = ConfigurationManager(_make_demo_module_def())
        manager2.load_configuration(saved)
        container2 = self._find_container(manager2)
        assert container2.unknown_parameters["VendorOnlyParam"].value == "vendor_secret"
        assert container2.parameter_values["KnownParam"].value == 42

    def test_double_save_is_stable(self, tmp_path):
        manager = self._load(tmp_path)
        first = tmp_path / "first.arxml"
        manager.save_configuration(first)

        manager2 = ConfigurationManager(_make_demo_module_def())
        manager2.load_configuration(first)
        second = tmp_path / "second.arxml"
        manager2.save_configuration(second)

        assert first.read_text(encoding="utf-8") == second.read_text(encoding="utf-8")


TWO_MODULE_CONFIG = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Bundle</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Demo</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Demo</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DemoGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Demo/DemoGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Demo/DemoGeneral/KnownParam</DEFINITION-REF>
                  <VALUE>1</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Other</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Other</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>OtherGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/AUTOSAR/EcucDefs/Other/OtherGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/AUTOSAR/EcucDefs/Other/OtherGeneral/OtherParam</DEFINITION-REF>
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
"""


def _make_other_module_def() -> EcucModuleDef:
    param_def = EcucParameterDef(short_name="OtherParam", param_type=EcucParameterType.INTEGER)
    container_def = EcucContainerDef(short_name="OtherGeneral")
    container_def.parameters["OtherParam"] = param_def
    module_def = EcucModuleDef(short_name="Other", definition_ref="/AUTOSAR/EcucDefs/Other")
    module_def.containers["OtherGeneral"] = container_def
    return module_def


class TestMultiModuleValueFiles:
    """One value file bundling several module configurations"""

    def test_each_manager_loads_its_own_module(self, tmp_path):
        bundle = tmp_path / "Bundle.epc"
        bundle.write_text(TWO_MODULE_CONFIG, encoding="utf-8")

        demo_mgr = ConfigurationManager(_make_demo_module_def())
        demo_mgr.load_configuration(bundle)
        assert demo_mgr.configuration.short_name == "Demo"
        assert demo_mgr.configuration.containers[0].parameter_values["KnownParam"].value == 1

        other_mgr = ConfigurationManager(_make_other_module_def())
        other_mgr.load_configuration(bundle)
        assert other_mgr.configuration.short_name == "Other"
        assert other_mgr.configuration.containers[0].parameter_values["OtherParam"].value == 2

    def test_scanner_lists_bundled_modules(self, tmp_path):
        from autosar_configurator.core.config_manager import EpcFileScanner

        bundle = tmp_path / "Demo.epc"
        bundle.write_text(TWO_MODULE_CONFIG, encoding="utf-8")
        assert EpcFileScanner.list_module_names(bundle) == ["Demo", "Other"]


INSTANCE_NAMED_REF_CONFIG = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Demo_Config</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Demo</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/EcucDefs/Demo</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DemoCounter_Software</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/EcucDefs/Demo/DemoCounter_Software</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/Vendor/EcucDefs/Demo/DemoCounter_Software/CounterTicks</DEFINITION-REF>
                  <VALUE>1000</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


class TestDefinitionRefResolution:
    """Instance-named DEFINITION-REFs resolve structurally, heuristics only as fallback"""

    def _counter_module_def(self) -> EcucModuleDef:
        ticks = EcucParameterDef(short_name="CounterTicks", param_type=EcucParameterType.INTEGER)
        counter = EcucContainerDef(short_name="DemoCounter", upper_multiplicity=-1)
        counter.parameters["CounterTicks"] = ticks
        module_def = EcucModuleDef(short_name="Demo", definition_ref="/Vendor/EcucDefs/Demo")
        module_def.containers["DemoCounter"] = counter
        return module_def

    def test_instance_named_ref_resolved_without_heuristic(self, tmp_path, caplog):
        import logging
        config_file = tmp_path / "Demo.epc"
        config_file.write_text(INSTANCE_NAMED_REF_CONFIG, encoding="utf-8")

        manager = ConfigurationManager(self._counter_module_def())
        with caplog.at_level(logging.DEBUG, logger="autosar_configurator.core.config_manager"):
            manager.load_configuration(config_file)

        container = manager.configuration.containers[0]
        assert container.definition_ref.endswith("/Demo/DemoCounter")
        # Parameter refs remapped along with the container
        assert container.parameter_values["CounterTicks"].definition_ref.endswith(
            "/Demo/DemoCounter/CounterTicks")
        # No unknown quarantine, no heuristic involved
        assert not container.unknown_parameters
        assert not any("Heuristic DEFINITION-REF remap" in r.message for r in caplog.records)

    def test_heuristic_fallback_is_logged(self, tmp_path, caplog):
        import logging
        # Instance name shares no prefix with the def name -> exact match fails,
        # parameter-signature heuristic must kick in and be logged.
        xml = INSTANCE_NAMED_REF_CONFIG.replace("DemoCounter_Software", "MySpecialCounter")
        config_file = tmp_path / "Demo.epc"
        config_file.write_text(xml, encoding="utf-8")

        manager = ConfigurationManager(self._counter_module_def())
        with caplog.at_level(logging.WARNING, logger="autosar_configurator.core.config_manager"):
            manager.load_configuration(config_file)

        container = manager.configuration.containers[0]
        assert container.definition_ref.endswith("/Demo/DemoCounter")
        assert any("Heuristic DEFINITION-REF remap" in r.message for r in caplog.records)


class TestEpcExport:
    """EB Tresos-compatible EPC export: layout, determinism, lossless round-trip"""

    def _loaded_manager(self, tmp_path) -> ConfigurationManager:
        config_file = tmp_path / "Demo_import.arxml"
        config_file.write_text(CONFIG_WITH_UNKNOWN_PARAM, encoding="utf-8")
        manager = ConfigurationManager(_make_demo_module_def())
        manager.load_configuration(config_file)
        return manager

    def test_epc_layout_matches_eb_conventions(self, tmp_path):
        from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer

        manager = self._loaded_manager(tmp_path)
        epc = tmp_path / "Demo.epc"
        EcucValueSerializer().export_epc(manager.configuration, epc)

        text = epc.read_text(encoding="utf-8")
        # EB layout: package short-name == module name, EB schema file
        assert "<SHORT-NAME>Demo</SHORT-NAME>" in text
        assert "Demo_Config" not in text
        assert "AUTOSAR_00046.xsd" in text

    def test_import_export_reimport_semantic_equality(self, tmp_path):
        from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer

        manager = self._loaded_manager(tmp_path)
        epc = tmp_path / "Demo.epc"
        EcucValueSerializer().export_epc(manager.configuration, epc)

        manager2 = ConfigurationManager(_make_demo_module_def())
        manager2.load_configuration(epc)

        c1 = manager.configuration.containers[0]
        c2 = manager2.configuration.containers[0]
        assert c2.short_name == c1.short_name
        assert c2.definition_ref == c1.definition_ref
        assert {k: v.value for k, v in c2.parameter_values.items()} == \
               {k: v.value for k, v in c1.parameter_values.items()}
        # Unknown parameters survive the EPC round-trip too
        assert c2.unknown_parameters["VendorOnlyParam"].value == "vendor_secret"

    def test_double_export_byte_identical(self, tmp_path):
        from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer

        manager = self._loaded_manager(tmp_path)
        a, b = tmp_path / "a.epc", tmp_path / "b.epc"
        serializer = EcucValueSerializer()
        serializer.export_epc(manager.configuration, a)
        serializer.export_epc(manager.configuration, b)
        assert a.read_bytes() == b.read_bytes()

    def test_workspace_export_all_modules(self, tmp_path):
        from autosar_configurator.core.workspace_manager import WorkspaceManager

        wm = WorkspaceManager()
        project = wm.create_project("Test", tmp_path / "Test.dpa")

        config_file = tmp_path / "Demo_import.arxml"
        config_file.write_text(CONFIG_WITH_UNKNOWN_PARAM, encoding="utf-8")
        manager = project.add_module(_make_demo_module_def(), tmp_path / "Demo.xdm")
        manager.load_configuration(config_file)

        out = tmp_path / "epc_out"
        written = wm.export_epc(out)
        assert written == [out / "Demo.epc"]
        assert (out / "Demo.epc").exists()

        with pytest.raises(ValueError):
            wm.export_epc(out, module_name="NotThere")
