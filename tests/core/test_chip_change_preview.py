"""add-chip-switch-disabled-report: a chip change is simulated on copies of the
project, and ENABLE conditions show which configured containers it disables."""
import pickle
from pathlib import Path

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.chip_selectors import preview_chip_change
from autosar_configurator.core.hardware.project_chip_store import ProjectChipStore
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.generator.eb.enable_conditions import (
    DisabledContainer,
    disabled_containers,
)

THA6206 = ChipDefinition(name="THA6206_LFBGA292",
                         selectors={"Os.OsResourceSubderivative": "Os_THA6206"},
                         ecu_resources={"OsResource": {"NumOfCores": 2}})
THA6412 = ChipDefinition(name="THA6412_BGA516",
                         selectors={"Os.OsResourceSubderivative": "Os_THA6412"},
                         ecu_resources={"OsResource": {"NumOfCores": 4}})

# Like T1's Os.xdm: the memory layout exists only for Os_THA6206; a core list
# that needs more than two cores reads the chip's ECU resources
OS_XDM = """<?xml version='1.0'?>
<datamodel version="7.0" xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd"
  xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd"
  xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
  xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd">
  <d:ctr type="AUTOSAR" factory="autosar">
    <d:lst type="TOP-LEVEL-PACKAGES">
      <d:ctr name="TS_X" type="AR-PACKAGE">
        <d:lst type="ELEMENTS">
          <d:chc name="Os" type="AR-ELEMENT" value="MODULE-DEF">
            <v:ctr type="MODULE-DEF">
              <v:var name="OsResourceSubderivative" type="ENUMERATION">
                <a:da name="DEFAULT" value="Os_THA6206"/>
                <a:da name="RANGE"><a:v>Os_THA6206</a:v><a:v>Os_THA6412</a:v></a:da>
              </v:var>
              <v:lst name="MemoryBlock" type="MAP">
                <a:da name="ENABLE" type="XPath"
                      expr="node:value(./../OsResourceSubderivative) = 'Os_THA6206'"/>
                <v:ctr name="MemoryBlock" type="IDENTIFIABLE">
                  <v:var name="MemoryBlockSize" type="INTEGER"/>
                  <v:lst name="MemorySection" type="MAP">
                    <v:ctr name="MemorySection" type="IDENTIFIABLE">
                      <v:var name="MemorySectionSize" type="INTEGER"/>
                    </v:ctr>
                  </v:lst>
                </v:ctr>
              </v:lst>
              <v:lst name="OsExtraCore" type="MAP">
                <a:da name="ENABLE" type="XPath" expr="ecu:get('OsResource.NumOfCores') &gt; 2"/>
                <v:ctr name="OsExtraCore" type="IDENTIFIABLE">
                  <v:var name="OsExtraCoreId" type="INTEGER"/>
                </v:ctr>
              </v:lst>
              <v:ctr name="OsOS" type="IDENTIFIABLE">
                <v:var name="OsNumberOfCores" type="INTEGER"/>
              </v:ctr>
            </v:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>
"""


def _project(tmp_path: Path, chip=THA6206, *, blocks=2, extra_cores=1, chips_dir=False):
    db = ChipDatabase()
    db.register_chip(THA6206)
    db.register_chip(THA6412)
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = chip.name
    if chips_dir:
        ProjectChipStore(tmp_path).save(chip)
    xdm = tmp_path / "Os" / "config" / "Os.xdm"
    xdm.parent.mkdir(parents=True)
    xdm.write_text(OS_XDM, encoding="utf-8")
    parser = EcucDefParser()
    parser.set_selector_values({})
    manager = project.add_module(parser.parse_module_def_file(xdm), xdm)
    module_def = manager.module_def
    manager.create_container_instance(module_def.containers["OsOS"])
    for _ in range(blocks):
        block = manager.create_container_instance(module_def.containers["MemoryBlock"])
        manager.create_container_instance(
            module_def.containers["MemoryBlock"].sub_containers["MemorySection"], block)
    for _ in range(extra_cores):
        manager.create_container_instance(module_def.containers["OsExtraCore"])
    project.apply_chip_selectors()
    project.chip_changed()
    return project


def _state(project, tmp_path):
    chips = sorted(p.name for p in (tmp_path / "chips").glob("*")) if (tmp_path / "chips").exists() else []
    configs = {n: m.configuration for n, m in project.module_managers.items()}
    return (pickle.dumps(configs), project.selected_chip,
            sorted(project.ecu_resources.items()), chips)


def _change(project, chip_name):
    preview = preview_chip_change(project, chip_name)
    before = set(disabled_containers(preview.current_modules, preview.current_ecu_resources))
    after = set(disabled_containers(preview.modules, preview.ecu_resources))
    return preview, sorted(after - before), sorted(before - after)


def test_switch_disables_memory_blocks_and_enables_extra_cores(tmp_path):
    project = _project(tmp_path)
    preview, disabled, enabled = _change(project, THA6412.name)
    assert preview.selector_result.changed == [("Os.OsResourceSubderivative", "Os_THA6206", "Os_THA6412")]
    assert [(d.module, d.definition) for d in disabled] == [("Os", "MemoryBlock")] * 2
    assert all(d.path.startswith("/Os/MemoryBlock") for d in disabled)
    assert [(d.module, d.definition) for d in enabled] == [("Os", "OsExtraCore")]


def test_preview_does_not_change_the_project(tmp_path):
    project = _project(tmp_path, chips_dir=True)
    before = _state(project, tmp_path)
    _change(project, THA6412.name)
    assert _state(project, tmp_path) == before
    assert not (tmp_path / "chips" / "THA6412_BGA516.yaml").exists()


def test_preview_matches_the_applied_change(tmp_path):
    project = _project(tmp_path)
    preview, disabled, _ = _change(project, THA6412.name)
    project.selected_chip = THA6412.name
    project.chip_changed()
    assert project.apply_chip_selectors().changed == preview.selector_result.changed
    modules = {n: (m.module_def, m.configuration) for n, m in project.module_managers.items()}
    assert set(disabled) <= set(disabled_containers(modules, project.ecu_resources))
    assert len(project.module_managers["Os"].configuration.containers) == 1 + 2 + 1   # kept


def test_switching_back_enables_them_again(tmp_path):
    project = _project(tmp_path, THA6412)
    _, disabled, enabled = _change(project, THA6206.name)
    assert [d.definition for d in enabled] == ["MemoryBlock", "MemoryBlock"]
    assert [d.definition for d in disabled] == ["OsExtraCore"]


def test_containers_disabled_under_both_chips_are_not_listed(tmp_path):
    project = _project(tmp_path, THA6412)
    _, disabled, _ = _change(project, THA6412.name)        # "Apply Chip Selectors"
    assert disabled == []


def test_topmost_container_only(tmp_path):
    project = _project(tmp_path, THA6412, blocks=1, extra_cores=0)
    modules = {n: (m.module_def, m.configuration) for n, m in project.module_managers.items()}
    found = disabled_containers(modules, project.ecu_resources)
    assert found == [DisabledContainer("Os", "/Os/" + found[0].path.rsplit("/", 1)[-1], "MemoryBlock")]
