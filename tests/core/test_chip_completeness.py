"""Chip data completeness: unconfirmed fields, selector values outside the
definition, Os selector without Os resources, core counts; read-only; shown in
the chip dependency scan."""
import copy
import hashlib
from pathlib import Path
from types import SimpleNamespace

import pytest

from autosar_configurator.core.hardware import chip_dependency_scan as scan
from autosar_configurator.core.hardware.chip_completeness import check_chip, check_chips
from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucParameterDef, EcucParameterType)

PLUGIN_XML = """<?xml version="1.0"?>
<plugin>
   <extension point="dreisoft.tresos.autosar2.api.plugin.ecuresource">
      <ecuresource derivate="THA6XXX" file="resource/Os_Resource_THA6206.properties"
                   moduleId="Os_THA6_ASR21" target="ARM">
         <parameter name="subderivative" value="Os_THA6206"></parameter>
      </ecuresource>
   </extension>
</plugin>
"""


def _project(tmp_path):
    plugin = tmp_path / "plugins" / "Os_THA6_ASR21"
    (plugin / "config").mkdir(parents=True)
    xdm = plugin / "config" / "Os.xdm"
    xdm.write_text("<datamodel/>", encoding="utf-8")
    (plugin / "plugin.xml").write_text(PLUGIN_XML, encoding="utf-8")
    module_def = EcucModuleDef(short_name="Os")
    module_def.parameters["OsResourceSubderivative"] = EcucParameterDef(
        short_name="OsResourceSubderivative", param_type=EcucParameterType.ENUMERATION,
        literals=["Os_THA6206", "Os_THA6412", "Os_SC300"])
    return SimpleNamespace(path=tmp_path / "proj" / "p.dpa", module_defs={"Os": xdm},
                           module_managers={"Os": SimpleNamespace(module_def=module_def)})


def _fields(items):
    return [item.field for item in items]


def test_complete_chip_has_no_items(tmp_path):
    chip = ChipDefinition(name="THA6206_LFBGA292",
                          selectors={"Os.OsResourceSubderivative": "Os_THA6206"},
                          metadata={"cores": {"count": 2}},
                          ecu_resources={"OsResource": {"NumOfCores": 2}})
    assert check_chip(chip, _project(tmp_path)) == []


def test_unconfirmed_fields_are_listed_with_their_notes():
    chip = ChipDefinition(name="THA610X_LFBGA180", metadata={"unconfirmed": {
        "metadata.flash_size": "SDK: PFLASH0/1 2 MB each", "ports": None}})
    items = check_chip(chip)
    assert _fields(items) == ["metadata.flash_size", "ports"]
    assert "SDK: PFLASH0/1 2 MB each" in items[0].text
    assert items[1].text == "ports 待确认"


def test_unconfirmed_as_a_list():
    chip = ChipDefinition(name="X", metadata={"unconfirmed": ["ports"]})
    assert _fields(check_chip(chip)) == ["ports"]


def test_selector_value_outside_the_definition(tmp_path):
    chip = ChipDefinition(name="NEW", selectors={"Os.OsResourceSubderivative": "Os_NEW"},
                          ecu_resources={"OsResource": {"NumOfCores": 1}})
    items = check_chip(chip, _project(tmp_path))
    assert _fields(items) == ["selectors.Os.OsResourceSubderivative"]
    assert "Os_NEW" in items[0].text


def test_selector_not_checked_without_the_module(tmp_path):
    project = _project(tmp_path)
    project.module_managers = {}
    chip = ChipDefinition(name="NEW", selectors={"Os.OsResourceSubderivative": "Os_NEW"},
                          ecu_resources={"OsResource": {"NumOfCores": 1}})
    assert check_chip(chip, project) == []


def test_os_selector_without_os_resources(tmp_path):
    project = _project(tmp_path)
    chip = ChipDefinition(name="SC300", selectors={"Os.OsResourceSubderivative": "Os_SC300"})
    assert _fields(check_chip(chip, project)) == ["ecu_resources.Os"]
    # Registered in plugin.xml: the plugin supplies the resources
    chip.selectors = {"Os.OsResourceSubderivative": "Os_THA6206"}
    assert check_chip(chip, project) == []


def test_os_only_chip_without_pins_is_complete(tmp_path):
    chip = ChipDefinition(name="SC300", selectors={"Os.OsResourceSubderivative": "Os_SC300"},
                          metadata={"cores": {"count": 1}},
                          ecu_resources={"OsResource": {"NumOfCores": 1}})
    assert check_chip(chip, _project(tmp_path)) == []


def test_core_count_must_match_one_of_the_counts():
    lockstep = ChipDefinition(name="L", metadata={"cores": {"count": 2}}, ecu_resources={
        "Resource": {"NumOfCores": 2}, "OsResource": {"NumOfCores": 1}})
    assert check_chip(lockstep) == []
    wrong = ChipDefinition(name="W", metadata={"cores": {"count": 4}}, ecu_resources={
        "Resource": {"NumOfCores": 2}, "OsResource": {"NumOfCores": 1}})
    items = check_chip(wrong)
    assert _fields(items) == ["metadata.cores.count"]
    assert "OsResource.NumOfCores = 1" in items[0].text


def test_check_does_not_change_the_chip_or_its_file(tmp_path):
    chips_dir = tmp_path / "chips"
    chips_dir.mkdir()
    yaml_file = chips_dir / "SC300.yaml"
    yaml_file.write_text(
        "name: SC300\nselectors: {Os.OsResourceSubderivative: Os_NEW}\n"
        "metadata:\n  cores: {count: 3}\n  unconfirmed: {ports: copied}\n", encoding="utf-8")
    digest = hashlib.sha256(yaml_file.read_bytes()).hexdigest()
    chip = ChipDatabase(chips_dir).get_chip("SC300")
    before = copy.deepcopy(chip)
    result = check_chips([chip], _project(tmp_path))
    assert _fields(result["SC300"]) == [
        "ports", "selectors.Os.OsResourceSubderivative", "ecu_resources.Os"]
    assert chip == before
    assert hashlib.sha256(yaml_file.read_bytes()).hexdigest() == digest


def test_library_chips_are_all_confirmed():
    from autosar_configurator.core.hardware.chip_database import default_chips_dir

    db = ChipDatabase(default_chips_dir())
    assert check_chip(db.get_chip("THA610X_LFBGA180")) == []
    assert check_chip(db.get_chip("THA6206_LFBGA292")) == []
    assert check_chip(db.get_chip("THA6412_BGA516")) == []
    # Os only: no pins or peripherals is not missing data; the 73 external interrupts are confirmed
    sc300 = db.get_chip("SC300")
    assert sc300.selectors == {"Os.OsResourceSubderivative": "Os_SC300"}
    assert check_chip(sc300) == []
    assert len(sc300.ecu_resources["Os"]["IsrTriggerMethodList"]) == 16 + 73


def test_scan_lists_completeness_under_coverage(tmp_path):
    project = _project(tmp_path)
    chip = ChipDefinition(name="SC300", selectors={"Os.OsResourceSubderivative": "Os_SC300"},
                          metadata={"unconfirmed": {"ecu_resources.Os.IsrTriggerMethodList": "NVIC"}},
                          ecu_resources={"OsResource": {"NumOfCores": 1}})
    result = scan.scan_project(project, chips=[chip])
    texts = [f.text for f in result.by_category(scan.COVERAGE) if f.chips == ("SC300",)]
    assert texts == ["芯片 SC300 资料不完整：ecu_resources.Os.IsrTriggerMethodList 待确认：NVIC"]
