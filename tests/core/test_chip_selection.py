"""update-unified-chip-selection: the selected chip drives the selector parameters."""
from pathlib import Path

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.chip_selectors import (
    apply_selectors,
    chip_from_selectors,
    is_selector,
)
from autosar_configurator.core.hardware.ecu_resource_diagnostics import check_selectors
from autosar_configurator.core.hardware.project_chip_store import ProjectChipStore
from autosar_configurator.core.model.configuration_model import EcucContainerValue
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.workspace_manager import WorkspaceProject

REPO = Path(__file__).resolve().parent.parent.parent
RESOURCE_XDM = REPO / "test_import_project/Def/plugins/Resource_THA6_AS440/config/Resource.xdm"

THA6206 = ChipDefinition(name="THA6206_LFBGA292", selectors={
    "Os.OsResourceSubderivative": "Os_THA6206",
    "Resource.ResourceSubderivative": "THA6206_LFBGA292"})
THA6412 = ChipDefinition(name="THA6412_BGA516", selectors={
    "Os.OsResourceSubderivative": "Os_THA6412",
    "Resource.ResourceSubderivative": "THA6412_BGA516"})


def _library(*chips) -> ChipDatabase:
    db = ChipDatabase()
    for chip in chips:
        db.register_chip(chip)
    return db


def _os_xdm(tmp_path: Path) -> Path:
    xdm = tmp_path / "Os" / "config" / "Os.xdm"
    xdm.parent.mkdir(parents=True)
    xdm.write_text("""<?xml version='1.0'?>
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
""", encoding="utf-8")
    return xdm


def _parser() -> EcucDefParser:
    parser = EcucDefParser()
    parser.set_selector_values({})
    return parser


def _subderivative_holder(manager):
    """Create the container instance holding ResourceSubderivative (if not there)."""
    def find(container_def, path):
        if "ResourceSubderivative" in container_def.parameters:
            return path + [container_def]
        for sub in container_def.sub_containers.values():
            found = find(sub, path + [container_def])
            if found:
                return found
        return None

    chain = None
    for top in manager.module_def.containers.values():
        chain = find(top, [])
        if chain:
            break
    assert chain, "Resource.xdm has no ResourceSubderivative"
    siblings = manager.configuration.containers
    container = None
    for cdef in chain:
        container = next((c for c in siblings if c.short_name == cdef.short_name), None)
        if container is None:
            container = EcucContainerValue(short_name=cdef.short_name,
                                           definition_ref=cdef.definition_ref)
            siblings.append(container)
        siblings = container.sub_containers
    return container


def _project(tmp_path: Path, chip, db, *, resource_value=None, os_value=None, os=True):
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = chip.name if chip else None
    resource = project.add_module(_parser().parse_module_def_file(RESOURCE_XDM), RESOURCE_XDM)
    if resource_value is not None:
        holder = _subderivative_holder(resource)
        resource.set_parameter_value(holder, "ResourceSubderivative", resource_value)
    if os:
        xdm = _os_xdm(tmp_path)
        manager = project.add_module(_parser().parse_module_def_file(xdm), xdm)
        if os_value is not None:
            manager.configuration.set_parameter_value(
                "OsResourceSubderivative", os_value, "/TS_X/Os/OsResourceSubderivative")
    return project


def _resource_value(project):
    from autosar_configurator.core.hardware.chip_selectors import (
        configured_selector_values,
    )
    return configured_selector_values(project, "Resource.ResourceSubderivative")


def test_resource_and_os_selectors_written(tmp_path):
    project = _project(tmp_path, THA6412, _library(THA6206, THA6412),
                       resource_value="THA6206_LFBGA292", os_value="Os_THA6206")
    result = project.apply_chip_selectors()
    assert _resource_value(project) == ["THA6412_BGA516"]
    assert project.module_managers["Os"].configuration.get_module_parameter(
        "OsResourceSubderivative") == "Os_THA6412"
    assert sorted(result.changed) == [
        ("Os.OsResourceSubderivative", "Os_THA6206", "Os_THA6412"),
        ("Resource.ResourceSubderivative", "THA6206_LFBGA292", "THA6412_BGA516"),
    ]
    assert result.skipped == []
    assert check_selectors(project, THA6412) == []


def test_unset_values_are_created(tmp_path):
    project = _project(tmp_path, THA6412, _library(THA6412))
    _subderivative_holder(project.module_managers["Resource"])     # container, no value
    result = project.apply_chip_selectors()
    assert _resource_value(project) == ["THA6412_BGA516"]
    assert ("Resource.ResourceSubderivative", None, "THA6412_BGA516") in result.changed
    assert ("Os.OsResourceSubderivative", None, "Os_THA6412") in result.changed


def test_holder_container_created_for_a_module_just_added(tmp_path):
    project = _project(tmp_path, THA6412, _library(THA6412), os=False)
    assert project.module_managers["Resource"].configuration.containers == []
    result = project.apply_chip_selectors(modules=["Resource"])
    assert _resource_value(project) == ["THA6412_BGA516"]
    assert result.changed == [("Resource.ResourceSubderivative", None, "THA6412_BGA516")]
    assert project.apply_chip_selectors(modules=["Resource"]).changed == []     # idempotent


def test_no_holder_created_along_multi_instance_containers(tmp_path):
    from autosar_configurator.core.hardware.chip_selectors import _definition_chain

    project = _project(tmp_path, THA6412, _library(THA6412), os=False)
    manager = project.module_managers["Resource"]
    chain = _definition_chain(manager.module_def.containers.values(), "ResourceSubderivative")
    chain[0].upper_multiplicity = -1
    result = project.apply_chip_selectors(modules=["Resource"])
    assert result.changed == []
    assert result.skipped == [("Resource.ResourceSubderivative", "no container holds the parameter")]
    assert manager.configuration.containers == []


def test_module_not_loaded_is_skipped(tmp_path):
    project = _project(tmp_path, THA6412, _library(THA6412),
                       resource_value="THA6206_LFBGA292", os=False)
    result = project.apply_chip_selectors()
    assert _resource_value(project) == ["THA6412_BGA516"]
    assert result.skipped == [("Os.OsResourceSubderivative", "module Os is not loaded")]


def test_limited_to_the_added_module(tmp_path):
    project = _project(tmp_path, THA6412, _library(THA6412),
                       resource_value="THA6206_LFBGA292", os_value="Os_THA6206")
    result = project.apply_chip_selectors(modules=["Os"])
    assert result.changed == [("Os.OsResourceSubderivative", "Os_THA6206", "Os_THA6412")]
    assert _resource_value(project) == ["THA6206_LFBGA292"]


def test_chip_without_selectors_changes_nothing(tmp_path):
    plain = ChipDefinition(name="THA6412_BGA516")
    project = _project(tmp_path, plain, _library(plain),
                       resource_value="THA6206_LFBGA292", os_value="Os_THA6206")
    result = project.apply_chip_selectors()
    assert result.changed == [] and result.skipped == []
    assert _resource_value(project) == ["THA6206_LFBGA292"]


def test_value_outside_the_definition_is_not_written(tmp_path):
    odd = ChipDefinition(name="X", selectors={"Os.OsResourceSubderivative": "Os_NOPE"})
    project = _project(tmp_path, odd, _library(odd), os_value="Os_THA6206")
    result = project.apply_chip_selectors()
    assert result.changed == []
    assert result.skipped[0][0] == "Os.OsResourceSubderivative"
    assert project.module_managers["Os"].configuration.get_module_parameter(
        "OsResourceSubderivative") == "Os_THA6206"


def test_no_selected_chip_changes_nothing(tmp_path):
    project = _project(tmp_path, None, _library(THA6412), resource_value="THA6206_LFBGA292")
    assert project.apply_chip_selectors().changed == []


def test_chip_found_from_the_configuration(tmp_path):
    project = _project(tmp_path, None, _library(THA6206, THA6412),
                       resource_value="THA6412_BGA516", os_value="Os_THA6412")
    assert project.chip_from_configuration() == "THA6412_BGA516"
    assert _resource_value(project) == ["THA6412_BGA516"]      # nothing changed


def test_chip_found_from_the_project_chips(tmp_path):
    custom = ChipDefinition(name="THA6999_BGA100",
                            selectors={"Resource.ResourceSubderivative": "THA6999_BGA100"})
    ProjectChipStore(tmp_path).save(custom)
    project = _project(tmp_path, None, _library(THA6412), os=False)
    holder = _subderivative_holder(project.module_managers["Resource"])
    holder.set_parameter_value("ResourceSubderivative", "THA6999_BGA100", "")
    assert project.chip_from_configuration() == "THA6999_BGA100"


def test_ambiguous_or_unknown_configuration_gives_no_chip(tmp_path):
    twin = ChipDefinition(name="TWIN", selectors={"Resource.ResourceSubderivative": "THA6412_BGA516"})
    project = _project(tmp_path, None, _library(THA6412, twin),
                       resource_value="THA6412_BGA516", os=False)
    assert chip_from_selectors(project, [THA6412, twin]) is None
    assert chip_from_selectors(project, [THA6206]) is None
    empty = _project(tmp_path / "e", None, _library(THA6412), os=False)
    assert chip_from_selectors(empty, [THA6412]) is None


def test_mismatch_in_one_selector_rules_the_chip_out(tmp_path):
    project = _project(tmp_path, None, _library(THA6412),
                       resource_value="THA6412_BGA516", os_value="Os_THA6206")
    assert chip_from_selectors(project, [THA6412]) is None


def test_is_selector():
    assert is_selector(THA6412, "Resource", "ResourceSubderivative")
    assert not is_selector(THA6412, "Resource", "ResourceGeneral")
    assert not is_selector(None, "Resource", "ResourceSubderivative")


def test_apply_without_chip():
    assert apply_selectors(None, None).changed == []
