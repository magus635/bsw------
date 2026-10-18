"""complete-chip-yaml-as-single-source: one YAML per chip is enough."""
from pathlib import Path

import pytest
import yaml

from autosar_configurator.core.chip_constraint_service import ChipConstraintService
from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.chip_exporter import (
    ChipDefinitionExporter,
    chip_checksum,
)
from autosar_configurator.core.hardware.ecu_resource_data import parse_selectors
from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
    check_selectors,
    typed_field_differences,
    typed_fields_from_ecu,
)
from autosar_configurator.core.hardware.ecu_resource_resolver import (
    available_chip_names,
    selector_values,
)
from autosar_configurator.core.hardware.project_chip_store import ProjectChipStore
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
)
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.xdm_expression_resolver import (
    XdmExpressionResolver,
)
from autosar_configurator.core.workspace_manager import (
    WorkspaceManager,
    WorkspaceProject,
)

REPO = Path(__file__).resolve().parent.parent.parent
IMPORT_PROJECT = REPO / "test_import_project"
RESOURCE_XDM = IMPORT_PROJECT / "Def/plugins/Resource_THA6_AS440/config/Resource.xdm"
CHIPS = ["THA610X_LFBGA180", "THA6206_LFBGA292", "THA6412_BGA516"]


def _library(*chips) -> ChipDatabase:
    db = ChipDatabase()
    for chip in chips:
        db.register_chip(chip)
    return db


def _project(path: Path, chip=None, db=None) -> WorkspaceProject:
    project = WorkspaceProject("p", path / "p.dpa")
    project.selected_chip = chip
    project.chip_database = db
    return project


# --- D1: UI constraints from the same resources -------------------------------------

@pytest.mark.parametrize("chip", CHIPS)
def test_existing_project_keeps_every_constraint(chip):
    old = ChipConstraintService()
    old.set_project_path(IMPORT_PROJECT)
    old.set_chip(chip)
    before = dict(old.get_all_constraints())

    project = _project(IMPORT_PROJECT, chip, ChipDatabase())
    project.load_ecu_resources()
    new = ChipConstraintService()
    new.set_project(project)
    new.set_chip(chip)
    after = dict(new.get_all_constraints())

    assert before, "the old path must find this chip's properties"
    assert {k: after.get(k) for k in before} == before        # nothing lost or changed
    # the only additions come from non-resource files (build configs) the generator reads anyway
    from autosar_configurator.core.hardware.tresos_properties_parser import (
        TresosPropertiesParser,
    )
    build_keys = set()
    for f in (IMPORT_PROJECT / "Def").rglob("*.properties"):
        if "resource" not in str(f.parent).lower():
            build_keys.update(TresosPropertiesParser().parse_file(f).properties)
    assert set(after) - set(before) <= build_keys


def test_project_with_only_chip_yaml_feeds_definition_expressions(tmp_path):
    db = _library(ChipDefinition(name="C", ecu_resources={
        "OsResource": {"NumOfCores": 4, "AvailableCores": ["CORE0", "CORE1", "CORE2", "CORE3"]}}))
    project = _project(tmp_path, "C", db)
    project.load_ecu_resources()
    service = ChipConstraintService()
    service.set_project(project)
    service.set_chip("C")

    resolver = XdmExpressionResolver(service.get_all_constraints())
    assert resolver.resolve_expression("ecu:get('OsResource.NumOfCores')") == 4
    assert resolver.resolve_expression("num:i(count(ecu:list('OsResource.AvailableCores')))") == 4


def test_constraints_follow_the_project_live(tmp_path):
    db = _library(ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}),
                  ChipDefinition(name="D", ecu_resources={"Os": {"A": 2}}))
    project = _project(tmp_path, "C", db)
    project.load_ecu_resources()
    service = ChipConstraintService()
    service.set_project(project)
    service.set_chip("C")
    assert service.get_constraint("Os.A") == 1
    service.set_chip("D")                 # the UI switches first: resolved for D on its own
    assert service.get_constraint("Os.A") == 2
    project.selected_chip = "D"           # then the project follows and recomputes
    project.chip_changed()
    assert service.get_constraint("Os.A") == 2


def test_chip_list_combines_library_project_and_properties(tmp_path):
    db = _library(ChipDefinition(name="LIB"))
    ProjectChipStore(tmp_path).save(ChipDefinition(name="LOCAL"))
    project = _project(tmp_path, None, db)
    project.available_chips = ["FROM_PROPS"]
    assert available_chip_names(project) == ["FROM_PROPS", "LIB", "LOCAL"]
    service = ChipConstraintService()
    service.set_project(project)
    assert service.available_chips == ["FROM_PROPS", "LIB", "LOCAL"]


# --- D2: selectors ---------------------------------------------------------------------

def test_selectors_load_export_and_validate(tmp_path):
    chip = ChipDefinition(name="C", selectors={"Os.OsResourceSubderivative": "Os_THA6412",
                                               "Resource.ResourceSubderivative": "C"})
    path = tmp_path / "C.yaml"
    ChipDefinitionExporter().save_yaml(chip, path)
    assert ChipDatabase()._load_chip_from_yaml(path).selectors == chip.selectors
    for bad in ({"NoDot": "x"}, {"A.b.c": "x"}, {"A.b": ""}, {"A.b": True}, ["x"]):
        with pytest.raises(ValueError):
            parse_selectors(bad)
    assert parse_selectors(None) == {}


def _subderivative(module_def):
    def find(container):
        for p in container.parameters.values():
            if p.short_name == "ResourceSubderivative":
                return p
        for sub in container.sub_containers.values():
            found = find(sub)
            if found:
                return found
    for container in module_def.containers.values():
        found = find(container)
        if found:
            return found


def test_new_chip_selectable_without_editing_the_definition():
    plain = _subderivative(EcucDefParser().parse_module_def_file(RESOURCE_XDM))
    parser = EcucDefParser()
    parser.set_selector_values({"Resource.ResourceSubderivative": ["THA6999_BGA100", "THA6412_BGA516"]})
    extended = _subderivative(parser.parse_module_def_file(RESOURCE_XDM))
    assert extended.literals == plain.literals + ["THA6999_BGA100"]     # originals kept, in order
    assert extended.default_value == plain.default_value


def test_os_selector_with_its_own_naming(tmp_path):
    xdm = tmp_path / "Os" / "config" / "Os.xdm"
    xdm.parent.mkdir(parents=True)
    xdm.write_text(_os_xdm(), encoding="utf-8")
    parser = EcucDefParser()
    parser.set_selector_values({"Os.OsResourceSubderivative": ["Os_THA6999"]})
    module_def = parser.parse_module_def_file(xdm)
    param = module_def.parameters["OsResourceSubderivative"]
    assert param.literals == ["Os_THA6206", "Os_THA6412", "Os_THA6999"]
    assert param.default_value == "Os_THA6206"


def _os_xdm() -> str:
    return """<?xml version='1.0'?>
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
            </v:ctr>
          </d:chc>
        </d:lst>
      </d:ctr>
    </d:lst>
  </d:ctr>
</datamodel>
"""


def test_parser_uses_the_packaged_library_by_default():
    module_def = EcucDefParser().parse_module_def_file(RESOURCE_XDM)
    assert set(_subderivative(module_def).literals) >= set(CHIPS)


def test_selector_values_merge_library_and_project_chips(tmp_path):
    db = _library(ChipDefinition(name="A", selectors={"Resource.ResourceSubderivative": "A"}))
    ProjectChipStore(tmp_path).save(
        ChipDefinition(name="B", selectors={"Resource.ResourceSubderivative": "B"}))
    project = _project(tmp_path, None, db)
    assert selector_values(project) == {"Resource.ResourceSubderivative": ["A", "B"]}


def _resource_config(value) -> EcucModuleConfiguration:
    general = EcucContainerValue(short_name="ResourceGeneral",
                                 definition_ref="/AUTOSAR/EcucDefs/Resource/ResourceGeneral")
    general.parameter_values["ResourceSubderivative"] = EcucParameterValue(
        definition_ref="/AUTOSAR/EcucDefs/Resource/ResourceGeneral/ResourceSubderivative", value=value)
    config = EcucModuleConfiguration(short_name="Resource", definition_ref="/AUTOSAR/EcucDefs/Resource")
    config.containers.append(general)
    return config


class _Manager:
    def __init__(self, configuration):
        self.configuration = configuration


def test_configured_selector_differs_from_chip(tmp_path):
    chip = ChipDefinition(name="THA6412_BGA516",
                          selectors={"Resource.ResourceSubderivative": "THA6412_BGA516"})
    project = _project(tmp_path, chip.name, _library(chip))
    project.module_managers = {"Resource": _Manager(_resource_config("THA6206_LFBGA292"))}
    messages = check_selectors(project, chip)
    assert len(messages) == 1
    assert "THA6206_LFBGA292" in messages[0] and "THA6412_BGA516" in messages[0]
    assert project.module_managers["Resource"].configuration.containers[0] \
        .parameter_values["ResourceSubderivative"].value == "THA6206_LFBGA292"      # not changed

    project.module_managers = {"Resource": _Manager(_resource_config("THA6412_BGA516"))}
    assert check_selectors(project, chip) == []


def test_builtin_chips_declare_their_resource_selector():
    from autosar_configurator.core.hardware.chip_database import default_chips_dir

    db = ChipDatabase(default_chips_dir())
    os_values = {"THA610X_LFBGA180": "Os_THA610X", "THA6206_LFBGA292": "Os_THA6206",
                 "THA6412_BGA516": "Os_THA6412"}
    for name in CHIPS:
        assert db.get_chip(name).selectors == {"Resource.ResourceSubderivative": name,
                                               "Os.OsResourceSubderivative": os_values[name]}


# --- D3: ecu_resources prevail over typed fields ----------------------------------------

def _cores_chip(count=2, available=("CORE0", "CORE1"), master="CORE0", **ecu):
    return ChipDefinition(name="C", metadata={"cores": {
        "count": count, "available": list(available), "master": master}}, ecu_resources=ecu)


def test_core_count_difference_is_reported_and_can_be_taken_over():
    chip = _cores_chip(OsResource={"NumOfCores": 4})
    messages = typed_field_differences(chip)
    assert len(messages) == 1 and "OsResource.NumOfCores" in messages[0]
    assert typed_fields_from_ecu(chip) == {"count": 4}


def test_absent_key_is_not_compared():
    assert typed_field_differences(_cores_chip(count=8)) == []


def test_os_master_core_notation_matches_core_field():
    chip = _cores_chip(OsResource={"MasterCore": "OS_CORE_ID_0"},
                       Resource={"MasterCore": ["CORE0", "CORE1"], "NumOfCores": 2,
                                 "AvailableCores": ["CORE0", "CORE1"]})
    assert typed_field_differences(chip) == []
    other = _cores_chip(OsResource={"MasterCore": "OS_CORE_ID_1"})
    assert len(typed_field_differences(other)) == 1


# --- D4: checksum and project record --------------------------------------------------------

def test_designer_save_writes_checksum_and_hand_edits_are_detected(tmp_path):
    chip = ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}})
    path = tmp_path / "C.yaml"
    ChipDefinitionExporter().save_yaml(chip, path)
    data = yaml.safe_load(path.read_text(encoding="utf-8"))
    assert data["checksum"] == chip_checksum(chip)
    loaded = ChipDatabase()._load_chip_from_yaml(path)
    assert not loaded.content_modified

    path.write_text(path.read_text(encoding="utf-8").replace("A: 1", "A: 2"), encoding="utf-8")
    edited = ChipDatabase()._load_chip_from_yaml(path)
    assert edited.content_modified
    assert edited.ecu_resources == {"Os": {"A": 2}}          # still loaded


def test_checksum_ignores_key_order_and_formatting(tmp_path):
    chip = ChipDefinition(name="C", ecu_resources={"Os": {"A": 1, "B": [1, 2]}})
    path = tmp_path / "C.yaml"
    ChipDefinitionExporter().save_yaml(chip, path)
    data = yaml.safe_load(path.read_text(encoding="utf-8"))
    data["ecu_resources"]["Os"] = {"B": [1, 2], "A": 1}       # reordered
    path.write_text(yaml.safe_dump(data, default_flow_style=False), encoding="utf-8")
    assert not ChipDatabase()._load_chip_from_yaml(path).content_modified


def test_old_chip_without_checksum_is_not_flagged(tmp_path):
    path = tmp_path / "OLD.yaml"
    path.write_text("name: OLD\n", encoding="utf-8")
    assert not ChipDatabase()._load_chip_from_yaml(path).content_modified


def test_project_copy_modified_after_it_was_recorded(tmp_path):
    db = _library(ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    project = _project(tmp_path, "C", db)
    project.adopt_selected_chip()
    assert project.chip_data_record["checksum"] == chip_checksum(ProjectChipStore(tmp_path).load("C"))
    assert project.chip_data_findings() == []

    # rewritten by a tool (fresh checksum) - still differs from what the project recorded
    store = ProjectChipStore(tmp_path)
    changed = store.load("C")
    changed.ecu_resources = {"Os": {"A": 9}}
    store.save(changed)
    findings = project.chip_data_findings()
    assert any("was modified" in m for m in findings)
    assert any("different version" in m for m in findings)


def test_newer_library_version_is_reported(tmp_path):
    db = _library(ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    project = _project(tmp_path, "C", db)
    project.adopt_selected_chip()
    db.get_chip("C").ecu_resources = {"Os": {"A": 2}}
    findings = project.chip_data_findings()
    assert len(findings) == 1 and "Update from Library" in findings[0]
    project.update_chip_from_library()
    assert project.chip_data_findings() == []


def test_project_file_keeps_the_chip_record(tmp_path):
    manager = WorkspaceManager()
    project = manager.create_project("demo", tmp_path / "demo.dpa")
    project.chip_database = _library(ChipDefinition(name="C", resource_version="1.2",
                                                    ecu_resources={"Os": {"A": 1}}))
    project.selected_chip = "C"
    project.adopt_selected_chip()
    record = dict(project.chip_data_record)
    manager.save_project()

    saved = __import__("json").loads((tmp_path / "demo.dpa").read_text(encoding="utf-8"))
    assert saved["chip_data"] == record
    assert record["resource_version"] == "1.2" and record["name"] == "C"
    assert "path" not in "".join(saved["chip_data"])              # no paths stored

    reopened, _ = WorkspaceManager().load_project(tmp_path / "demo.dpa")
    assert reopened.chip_data_record == record


def test_findings_reach_the_diagnosis_report(tmp_path):
    db = _library(ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    project = _project(tmp_path, "C", db)
    project.adopt_selected_chip()
    db.get_chip("C").ecu_resources = {"Os": {"A": 2}}
    report = project.diagnose_ecu_resources()
    assert any("Update from Library" in line for line in report.warning_lines())
