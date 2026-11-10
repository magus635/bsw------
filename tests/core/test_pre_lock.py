"""Task 11: the Pre read-only lock and the value origin the UI shows (design §6.5, §6.8).

A Pre value is read-only until the user unlocks its key. The lock has to hold at every
entry that writes a value — ``ConfigurationManager.set_parameter_value``,
``delete_container_instance``, ``apply_recommended_values`` — and at every undo command
constructor, so a blocked edit never reaches the undo stack at all. Unlocking is recorded
per key in ``.dpa`` (``modules[].pre_unlocked``), survives a save/reopen cycle, and makes
the merge treat the value as the user's own (``KEPT_USER``).

Importing a value file is deliberately *not* blocked: it writes, and the next merge forces
the Pre value back (``PRE_FORCED``) and reports it.

The last group of tests is the text the panel shows: "基线不可用" when the layers of a
snapshot could not be trusted (every value is then USER, and the lock is off) — the pure
helper lives in ``core/baseline/display.py`` so it is testable without a display.
"""
import json
from pathlib import Path

import pytest

from autosar_configurator.core.baseline import session
from autosar_configurator.core.baseline.display import (
    UNAVAILABLE_TEXT, module_note, origin_text, partition_locked, pre_file_names)
from autosar_configurator.core.baseline.merge import MergeKind
from autosar_configurator.core.baseline.origin import Origin
from autosar_configurator.core.baseline.session import ModuleBaseline
from autosar_configurator.core.config_manager import PreLockedError
from autosar_configurator.core.packages.library import LibraryRef, scan_library
from autosar_configurator.core.workspace_manager import WorkspaceManager

LEVEL = "P:/Trk/TrkGeneral.Level"
PARTNER = "R:/Trk/TrkGeneral.Partner"
MODE = "P:/Trk/TrkGeneral.Mode"
RATIO = "P:/Trk/TrkGeneral.Ratio"
GENERAL = "C:/Trk/TrkGeneral"

_DEF = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Vendor</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>Trk</SHORT-NAME>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>TrkGeneral</SHORT-NAME>
              <PARAMETERS>
                <ECUC-STRING-PARAM-DEF>
                  <SHORT-NAME>Mode</SHORT-NAME>
                  <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
                  <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                </ECUC-STRING-PARAM-DEF>
                <ECUC-STRING-PARAM-DEF>
                  <SHORT-NAME>Ratio</SHORT-NAME>
                  <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
                  <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                </ECUC-STRING-PARAM-DEF>
                <ECUC-STRING-PARAM-DEF>
                  <SHORT-NAME>Level</SHORT-NAME>
                  <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
                  <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                </ECUC-STRING-PARAM-DEF>
              </PARAMETERS>
              <REFERENCES>
                <ECUC-REFERENCE-DEF>
                  <SHORT-NAME>Partner</SHORT-NAME>
                  <DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/Trk/TrkGeneral</DESTINATION-REF>
                  <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
                  <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                </ECUC-REFERENCE-DEF>
              </REFERENCES>
              <SUB-CONTAINERS>
                <ECUC-PARAM-CONF-CONTAINER-DEF>
                  <SHORT-NAME>TrkChild</SHORT-NAME>
                  <UPPER-MULTIPLICITY>-1</UPPER-MULTIPLICITY>
                  <PARAMETERS>
                    <ECUC-STRING-PARAM-DEF>
                      <SHORT-NAME>Note</SHORT-NAME>
                      <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
                      <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
                    </ECUC-STRING-PARAM-DEF>
                  </PARAMETERS>
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

_COLLECTION = """        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>{name}</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Trk</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>TrkGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/Trk/TrkGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
{params}
              </PARAMETER-VALUES>
{refs}
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>"""

_CHILD = """              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                  <SHORT-NAME>TrkChild</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/Trk/TrkGeneral/TrkChild</DEFINITION-REF>
                  <PARAMETER-VALUES>
                    <ECUC-TEXTUAL-PARAM-VALUE>
                      <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/Trk/TrkGeneral/TrkChild/Note</DEFINITION-REF>
                      <VALUE>from-pre</VALUE>
                    </ECUC-TEXTUAL-PARAM-VALUE>
                  </PARAMETER-VALUES>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>"""

_REF = """              <REFERENCE-VALUES>
                <ECUC-REFERENCE-VALUE>
                  <DEFINITION-REF DEST="ECUC-REFERENCE-DEF">/Vendor/Trk/TrkGeneral/Partner</DEFINITION-REF>
                  <VALUE-REF DEST="ECUC-CONTAINER-VALUE">{value}</VALUE-REF>
                </ECUC-REFERENCE-VALUE>
              </REFERENCE-VALUES>"""

_PARAM = """                <ECUC-TEXTUAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/Trk/TrkGeneral/{name}</DEFINITION-REF>
                  <VALUE>{value}</VALUE>
                </ECUC-TEXTUAL-PARAM-VALUE>"""

_VALUES = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Vendor</SHORT-NAME>
      <ELEMENTS>
{collections}
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


def _collection(name, params):
    body = "\n".join(_PARAM.format(name=k, value=v) for k, v in params.items())
    refs = _REF.format(value="/Trk/TrkGeneral") if params else ""
    child = _CHILD if params and "Level" in params else ""
    return _COLLECTION.format(name=name, params=body, refs=refs + child)


def _write(root, rel, text):
    path = root / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def make_package(lib, rec, pre=None, module="Trk"):
    """(Re)write the package under ``lib/<module>`` with the given Rec and Pre values."""
    path = lib / module
    _write(path, f"def/{module}.arxml", _DEF.replace("Trk", module))
    _write(path, f"config/{module}_values.arxml",
           _VALUES.format(collections="\n".join(
               [_collection(f"{module}_Rec", rec)]
               + ([_collection(f"{module}_Pre", pre)] if pre else []))
           ).replace("Trk", module))
    (path / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": module,
        "definition": f"/Vendor/{module}",
        "files": [f"def/{module}.arxml", f"config/{module}_values.arxml"],
        "rec": [f"/Vendor/{module}_Rec"],
        "pre": [f"/Vendor/{module}_Pre"] if pre else [],
    }), encoding="utf-8")


def new_project(tmp_path):
    wm = WorkspaceManager()
    project = wm.create_project("P", tmp_path / "proj" / "P.dpa", format_version=8)
    project.selected_chip = None
    project.module_libraries.append(LibraryRef(path=(tmp_path / "lib").as_posix(), kind="package"))
    return wm


def add_trk(project, confirm=None, persist=True):
    [pkg] = [p for p in scan_library(project.module_libraries[0], Path(project.path).parent)
             if p.manifest.module == "Trk"]
    return project.add_module_from_package(pkg, 0, persist=persist, confirm=confirm)


def project_file(tmp_path):
    return tmp_path / "proj" / "P.dpa"


def general(manager):
    config = manager.configuration
    (container,) = [c for c in config.containers if c.short_name == "TrkGeneral"]
    return container


def level(manager):
    return general(manager).parameter_values["Level"].value


@pytest.fixture
def project(tmp_path):
    """A project whose Trk module is Pre-owned for ``Level`` and Rec-owned otherwise."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast", "Ratio": "10"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    manager = add_trk(wm.current_project)
    wm.save_project()
    return wm, manager


@pytest.fixture
def unlocked_project(project):
    """The same project with ``Level`` unlocked through the manager (recorded, not saved)."""
    wm, manager = project
    assert manager.pre_unlock_state(general(manager), "Level") == "locked"
    assert manager.set_pre_unlocked(general(manager), "Level", True)
    assert manager.pre_unlock_state(general(manager), "Level") == "unlocked"
    assert wm.current_project.module_entries["Trk"].pre_unlocked == [LEVEL]
    assert wm.current_project.is_modified is True
    return wm, manager


# --- the lock ---------------------------------------------------------------

def test_pre_value_is_locked(project):
    _, manager = project
    with pytest.raises(PreLockedError) as raised:
        manager.check_editable(general(manager), "Level")
    assert raised.value.key == LEVEL
    assert str(level(manager)) == "3"


def test_lock_blocks_set_parameter_value(project):
    _, manager = project
    with pytest.raises(PreLockedError) as raised:
        manager.set_parameter_value(general(manager), "Level", "9")
    assert raised.value.key == LEVEL
    assert level(manager) == "3"


def test_rec_and_default_values_are_not_locked(project):
    """Only Pre owns a key: Rec and default values stay editable."""
    _, manager = project
    manager.set_parameter_value(general(manager), "Mode", "Slow")
    manager.set_parameter_value(general(manager), "Ratio", "20")
    assert general(manager).parameter_values["Mode"].value == "Slow"


def test_lock_blocks_container_deletion(project):
    _, manager = project
    with pytest.raises(PreLockedError) as raised:
        manager.check_editable(general(manager))          # name=None: the container itself
    assert raised.value.key == GENERAL
    with pytest.raises(PreLockedError):
        manager.delete_container_instance(general(manager))
    assert general(manager) is not None


def test_lock_allows_adding_below_a_pre_container(project):
    """Design §6.5: Pre containers may get sub-containers Pre does not have (CREATE path)."""
    _, manager = project
    general_instance = general(manager)
    child_def = manager.module_def.containers["TrkGeneral"].sub_containers["TrkChild"]
    child = manager.create_container_instance(child_def, parent=general_instance,
                                              instance_name="TrkChild_1")
    assert child in general_instance.sub_containers
    manager.set_parameter_value(child, "Note", "mine")


def test_lock_blocks_replacing_the_pre_child(project):
    """A container Pre owns, nested one level down, is not deletable either."""
    _, manager = project
    general_instance = general(manager)
    (child,) = general_instance.sub_containers
    assert child.short_name == "TrkChild"
    with pytest.raises(PreLockedError):
        manager.delete_container_instance(child, parent=general_instance)


def test_apply_recommended_values_skips_pre_keys(project):
    _, manager = project
    from autosar_configurator.core.model.configuration_model import (
        EcucContainerValue, EcucModuleConfiguration, EcucParameterValue)

    rec = EcucModuleConfiguration(short_name="Trk", definition_ref="/Vendor/Trk")
    container = EcucContainerValue(short_name="TrkGeneral", definition_ref="/Vendor/Trk/TrkGeneral")
    for name, value in (("Mode", "Silent"), ("Level", "42")):
        container.parameter_values[name] = EcucParameterValue(
            definition_ref=f"/Vendor/Trk/TrkGeneral/{name}", value=value)
    rec.add_container(container)

    updated = manager.apply_recommended_values(rec)
    assert updated == 1                                  # Mode only
    assert general(manager).parameter_values["Mode"].value == "Silent"
    assert level(manager) == "3"


def test_lock_blocks_all_mutation_entries(project):
    """Every undo command constructor refuses a Pre edit, so nothing enters the undo stack."""
    pytest.importorskip("PySide6")
    from autosar_configurator.ui.commands import (
        DeleteContainerCommand, MoveContainerCommand, PasteContainerCommand,
        RenameContainerCommand, SetReferenceCommand)

    _, manager = project
    instance = general(manager)
    with pytest.raises(PreLockedError):
        RenameContainerCommand(manager, instance, "TrkGeneral2")
    with pytest.raises(PreLockedError):
        DeleteContainerCommand(manager, instance, None)
    with pytest.raises(PreLockedError):
        MoveContainerCommand(manager, instance, None, 0)
    with pytest.raises(PreLockedError):
        PasteContainerCommand(manager, instance, instance.clone())
    # A reference is locked by its R: key, resolved against the container definition
    with pytest.raises(PreLockedError) as raised:
        SetReferenceCommand(manager, instance, "Partner", "/Trk/TrkGeneral")
    assert raised.value.key == PARTNER


def test_reference_lock_follows_the_unlock(unlocked_project):
    wm, manager = unlocked_project
    from autosar_configurator.ui.commands import SetReferenceCommand

    with pytest.raises(PreLockedError):
        manager.check_editable(general(manager), "Partner")        # still locked
    wm.current_project.module_entries["Trk"].pre_unlocked.append(PARTNER)
    manager.check_editable(general(manager), "Partner")
    SetReferenceCommand(manager, general(manager), "Partner", "/Trk/TrkGeneral")


def test_no_baseline_means_no_lock(tmp_path):
    """A module whose package gives no Pre has no lock at all (format ≤7 behaviour)."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast"})
    wm = new_project(tmp_path)
    manager = add_trk(wm.current_project)
    manager.set_parameter_value(general(manager), "Level", "7")
    manager.check_editable(general(manager))


def test_lock_is_off_while_the_layers_are_untrusted(project):
    """With the layers dropped nothing is known to be Pre — the lock must not fire."""
    wm, manager = project
    baseline = wm.current_project.baselines["Trk"]
    wm.current_project.baselines["Trk"] = ModuleBaseline(
        base_config=baseline.base_config, layers={}, pre_keys=set(),
        module_name="Trk", layers_untrusted=True)
    manager.set_parameter_value(general(manager), "Level", "9")
    assert level(manager) == "9"


# --- unlocking --------------------------------------------------------------

def test_unlock_allows_edit_and_persists(unlocked_project):
    wm, manager = unlocked_project
    manager.check_editable(general(manager), "Level")
    manager.set_parameter_value(general(manager), "Level", "9")
    assert level(manager) == "9"
    assert manager.value_origin(general(manager), "Level") is Origin.USER

    wm.save_project()
    opened, failed = WorkspaceManager().load_project(Path(wm.current_project.path))
    assert failed == []
    assert opened.module_entries["Trk"].pre_unlocked == [LEVEL]
    reopened = opened.module_managers["Trk"]
    assert level(reopened) == "9"                    # kept: the merge did not force it back

    # The stored value is the user's now, so the baseline is not what says it
    from autosar_configurator.core.baseline.origin import origins_for
    baseline = opened.baselines["Trk"]
    origins = origins_for(
        reopened.configuration, baseline.base_config, baseline.layers,
        set(opened.module_entries["Trk"].pre_unlocked), baseline.pre_keys, "Trk")
    assert origins[LEVEL] is Origin.USER


def test_unlocked_value_merges_as_kept_user(tmp_path):
    """A baseline change to an unlocked key keeps the user's value (KEPT_USER, not PRE_FORCED)."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    manager = add_trk(wm.current_project)
    wm.current_project.module_entries["Trk"].pre_unlocked.append(LEVEL)
    manager.set_parameter_value(general(manager), "Level", "9")
    wm.save_project()

    # The package moves the Pre value; the unlocked key is the user's and must not follow
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "5"})

    def confirm(text, result):
        return True

    opened, failed = WorkspaceManager().load_project(Path(wm.current_project.path), confirm=confirm)
    assert failed == []
    assert level(opened.module_managers["Trk"]) == "9"


def test_import_value_file_then_pre_restored(tmp_path):
    """Importing a value file writes (no lock), and the next merge forces Pre back."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast", "Ratio": "10"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    manager = add_trk(wm.current_project)
    wm.save_project()

    imported = tmp_path / "Imported.arxml"
    imported.write_text(_VALUES.format(collections=_collection(
        "Imported", {"Mode": "Fast", "Ratio": "10", "Level": "9"})), encoding="utf-8")
    manager.load_configuration(imported)             # not blocked
    assert level(manager) == "9"
    wm.save_project()

    def confirm(text, result):
        assert "预设强制" in text                      # the report names the forced key
        return True

    opened, failed = WorkspaceManager().load_project(Path(wm.current_project.path), confirm=confirm)
    assert failed == []
    assert level(opened.module_managers["Trk"]) == "3"       # Pre wins again
    reports = sorted(session.report_path(opened, "Trk").parent.glob("*_merge_Trk.md"))
    assert reports, "the merge that forced a Pre value must write a report"
    assert "预设强制" in reports[0].read_text(encoding="utf-8")


def test_pre_forced_is_reported_by_the_merge(tmp_path):
    """The pure merge says PRE_FORCED for a Pre key the user overwrote."""
    from autosar_configurator.core.baseline.merge import three_way_merge
    from autosar_configurator.core.baseline.compose import Layer

    result = three_way_merge({LEVEL: "3"}, {LEVEL: "3"}, {LEVEL: "9"},
                             {LEVEL: Layer.PRE}, set())
    (item,) = result.items
    assert item.kind is MergeKind.PRE_FORCED and item.key == LEVEL


# --- the text the panel shows ------------------------------------------------

def test_layers_untrusted_reports_baseline_unavailable():
    baseline = ModuleBaseline(base_config=object(), layers={}, pre_keys=set(),
                              module_name="Trk", layers_untrusted=True)
    assert module_note(baseline) == UNAVAILABLE_TEXT
    assert UNAVAILABLE_TEXT == "基线不可用"


def test_layers_untrusted_project_says_baseline_unavailable(project):
    """The whole path: a dropped layer set on the project makes the module say it."""
    wm, manager = project
    baseline = wm.current_project.baselines["Trk"]
    wm.current_project.baselines["Trk"] = ModuleBaseline(
        base_config=baseline.base_config, layers={}, pre_keys=set(),
        module_name="Trk", layers_untrusted=True)

    assert module_note(wm.current_project.baselines["Trk"]) == UNAVAILABLE_TEXT
    # ...and the lock and the per-value origin both stand down with it
    assert manager.value_origin(general(manager), "Level") is None
    manager.set_parameter_value(general(manager), "Level", "9")


def test_trusted_baseline_has_no_note(project):
    wm, _ = project
    assert module_note(wm.current_project.baselines["Trk"]) is None


def test_no_baseline_has_no_note():
    """A format ≤7 module, a module the package gave nothing to: nothing to say."""
    assert module_note(None) is None
    assert module_note(ModuleBaseline()) is None


def test_origin_text_names_the_source_and_pre_files():
    text = origin_text(Origin.PRE, pre_files=["McuPreConfiguration.xdm"], locked=True)
    assert "PRE" in text and "McuPreConfiguration.xdm" in text
    assert "锁定" in text
    assert origin_text(Origin.REC).startswith("来源：REC")


def test_pre_file_names_from_the_package(project):
    wm, _ = project
    package = wm.current_project.packages["Trk"]
    assert pre_file_names(package, None) == ["Trk_values.arxml"]


def test_partition_locked_splits_and_sorts(project):
    """Batch edit skips locked values and lists them in a stable order."""
    _, manager = project
    instance = general(manager)
    editable, skipped = partition_locked(
        manager, [(instance, "Level"), (instance, "Mode"), (instance, "Ratio")])
    assert [name for _, name in editable] == ["Mode", "Ratio"]
    assert skipped == [LEVEL]


def test_no_snapshot_but_no_layers_reports_unavailable():
    """A snapshot with no layers beside it cannot say where any value came from (§6.5)."""
    assert module_note(ModuleBaseline(base_config=object(), layers={},
                                      module_name="Trk")) == UNAVAILABLE_TEXT
    assert module_note(ModuleBaseline(pre_keys={"P:/Trk/TrkGeneral.Level"})) == UNAVAILABLE_TEXT


# --- the lock never blocks a replay -------------------------------------------

def test_undo_redo_survive_a_relock(unlocked_project):
    """解锁 → 编辑 → 恢复锁定 → Ctrl+Z must still undo (the lock gates new edits only)."""
    pytest.importorskip("PySide6")
    from PySide6.QtGui import QUndoStack

    from autosar_configurator.ui.commands import SetParameterCommand

    wm, manager = unlocked_project
    instance = general(manager)
    stack = QUndoStack()
    stack.push(SetParameterCommand(manager, instance, "Level", "9"))
    assert level(manager) == "9"

    # Re-lock: the value is Pre-owned and locked again
    assert manager.set_pre_unlocked(instance, "Level", False)
    assert manager.pre_unlock_state(instance, "Level") == "locked"
    with pytest.raises(PreLockedError):
        manager.set_parameter_value(instance, "Level", "42")      # a new edit is refused

    stack.undo()                                                 # a replay is not
    assert level(manager) == "3"
    stack.redo()
    assert level(manager) == "9"
    stack.undo()
    assert level(manager) == "3"


# --- apply recommended values (UI path) ---------------------------------------

def test_apply_recommended_changes_skips_locked_and_keeps_the_macro_closed(project):
    """The UI apply must skip Pre keys and never leave the undo macro half-open."""
    pytest.importorskip("PySide6")
    from PySide6.QtGui import QUndoStack

    from autosar_configurator.core.model.configuration_model import (
        EcucContainerValue, EcucModuleConfiguration, EcucParameterValue)
    from autosar_configurator.ui.controllers.project_controller import \
        apply_recommended_changes

    _, manager = project
    rec = EcucModuleConfiguration(short_name="Trk", definition_ref="/Vendor/Trk")
    container = EcucContainerValue(short_name="TrkGeneral", definition_ref="/Vendor/Trk/TrkGeneral")
    for name, value in (("Mode", "Silent"), ("Level", "42")):
        container.parameter_values[name] = EcucParameterValue(
            definition_ref=f"/Vendor/Trk/TrkGeneral/{name}", value=value)
    rec.add_container(container)

    stack = QUndoStack()
    result = apply_recommended_changes(manager, rec, only_empty=False, undo_stack=stack)

    assert result.locked == [LEVEL]
    assert result.updated == 1
    assert general(manager).parameter_values["Mode"].value == "Silent"
    assert level(manager) == "3"
    assert stack.count() == 1                     # one macro, closed and undoable
    stack.undo()
    assert general(manager).parameter_values["Mode"].value == "Fast"


# --- chip selectors -----------------------------------------------------------

def test_chip_selector_on_a_pre_value_is_skipped_and_reported(project):
    """Selectors are a derived project-wide write, but a locked Pre value still wins."""
    wm, manager = project

    class _Chip:
        name = "TestChip"
        selectors = {"Trk.Level": "42", "Trk.Mode": "Silent"}

    from autosar_configurator.core.hardware.chip_selectors import apply_selectors
    result = apply_selectors(wm.current_project, _Chip(), log=False)

    written = {key for key, _old, _new in result.changed}
    skipped = dict(result.skipped)
    assert "Trk.Mode" in written                       # not Pre: written
    assert "Trk.Level" not in written
    assert "Trk.Level" in skipped and "锁定" in skipped["Trk.Level"]
    assert level(manager) == "3"

    # Unlocking makes the same selector write again
    manager.set_pre_unlocked(general(manager), "Level", True)
    again = apply_selectors(wm.current_project, _Chip(), log=False)
    assert "Trk.Level" in {key for key, _o, _n in again.changed}
    assert level(manager) == "42"


def test_a_computed_default_on_a_pre_key_is_derived_not_a_user_edit(project, monkeypatch):
    """create_container_instance must not raise for a value the user never touched.

    A computed (XPath) default is DERIVED: it is computed for a new instance and the merge
    owns it like any other baseline value. Without the bypass the lock would raise out of
    create_container_instance — and so out of PasteContainerCommand.redo.
    """
    from autosar_configurator.generator.eb import computed_defaults as module

    _, manager = project
    monkeypatch.setattr(
        module, "computed_defaults",
        lambda modules, instance, container_def, names, resources=None:
            ({name: "9" for name in names}, {}))

    # The very container Pre created, and the Pre-owned parameter: the worst case
    instance = general(manager)
    container_def = manager.module_def.containers["TrkGeneral"]
    with pytest.raises(PreLockedError):
        manager.set_parameter_value(instance, "Level", "7")     # a user edit is refused

    manager._apply_computed_defaults(instance, container_def, ["Level"])

    assert instance.parameter_values["Level"].value == "9"       # the derived default is not


def test_selector_skip_is_a_status_line(project):
    """A locked selector that changes nothing else still reaches the user as a status line."""
    from autosar_configurator.core.hardware.chip_selectors import apply_selectors
    from autosar_configurator.ui.controllers.project_controller import \
        ProjectController

    wm, manager = project

    class _Chip:
        name = "TestChip"
        selectors = {"Trk.Level": "42"}          # the only selector, and it is locked

    result = apply_selectors(wm.current_project, _Chip(), log=False)
    assert result.changed == [] and result.skipped
    assert result.locked == [LEVEL]                  # the explicit collection, not a word match
    status = ProjectController._selector_result_status(result)
    assert "锁定" in status and LEVEL in status


def test_lock_and_badge_agree_when_the_baseline_is_unusable(project):
    """One predicate decides both: no lock may be enforced while the badge is suppressed."""
    wm, manager = project
    baseline = wm.current_project.baselines["Trk"]
    wm.current_project.baselines["Trk"] = ModuleBaseline(
        base_config=baseline.base_config, layers={}, pre_keys=set(),
        module_name="Trk", layers_untrusted=True)

    assert module_note(wm.current_project.baselines["Trk"]) == UNAVAILABLE_TEXT
    assert manager._baseline_lock_info() is None
    assert manager.pre_unlock_state(general(manager), "Level") is None
    manager.set_parameter_value(general(manager), "Level", "9")      # nothing to lock


def test_lock_and_badge_agree_when_a_snapshot_has_no_layers(project):
    """The other 基线不可用 trigger: a snapshot whose layers file was never read."""
    wm, manager = project
    baseline = wm.current_project.baselines["Trk"]
    wm.current_project.baselines["Trk"] = ModuleBaseline(
        base_config=baseline.base_config, layers={}, pre_keys=set(),
        module_name="Trk", has_layers=False)          # not layers_untrusted: simply absent

    assert module_note(wm.current_project.baselines["Trk"]) == UNAVAILABLE_TEXT
    assert manager._baseline_lock_info() is None
    assert manager.value_origin(general(manager), "Level") is None
    assert manager.pre_unlock_state(general(manager), "Level") is None
    manager.set_parameter_value(general(manager), "Level", "9")      # nothing to lock


def test_template_create_new_refuses_a_pre_owned_container_path(project, monkeypatch):
    """A template recreating a Pre-owned container path is refused, not silently written.

    The values would land under ``/Trk/TrkGeneral`` — a path Pre owns — so the wizard must
    stop before creating anything, exactly as the existing-instance path does; otherwise the
    lock would leak and only the next merge (PRE_FORCED) would heal it.
    """
    pytest.importorskip("PySide6")
    from autosar_configurator.ui.wizards.template_wizard import TemplateWizard

    _, manager = project
    container_def = manager.module_def.containers["TrkGeneral"]

    class _Template:
        container_def = "TrkGeneral"

        def get_all_params(self, values):
            return {"Level": "9", "Mode": "Silent"}

    class _Page:
        def __init__(self, data):
            self._data = data

        def get_data(self):
            return self._data

    wizard = TemplateWizard.__new__(TemplateWizard)
    wizard.category_page = _Page({"template": _Template()})
    wizard.param_page = _Page({"parameter_values": {}})
    wizard.target_page = _Page({"create_new": True, "instance_name": "TrkGeneral"})
    wizard.config_manager = manager
    wizard.parent_instance = None
    wizard.created_instance = None

    from PySide6 import QtWidgets
    messages = []
    monkeypatch.setattr(QtWidgets.QMessageBox, "warning",
                        staticmethod(lambda *args, **kwargs: messages.append(args[2])))
    monkeypatch.setattr(QtWidgets.QMessageBox, "critical",
                        staticmethod(lambda *args, **kwargs: messages.append(args[2])))

    wizard.accept()

    assert wizard.created_instance is None
    assert len(manager.configuration.containers) == 1          # nothing new was created
    assert manager.configuration.containers[0] is general(manager)
    assert level(manager) == "3"                               # no value was written
    assert any(LEVEL in text for text in messages)              # and the key was named


def test_template_create_new_probe_rejects_a_bad_value(project, monkeypatch):
    """The probe runs the real conversion: a value the definition refuses never gets written.

    This covers the pre-check branch itself — the container is not created either, because
    the probe fails before ``create_container_instance``.
    """
    pytest.importorskip("PySide6")
    from autosar_configurator.ui.wizards.template_wizard import TemplateWizard

    _, manager = project
    container_def = manager.module_def.containers["TrkGeneral"]

    class _Template:
        container_def = "TrkGeneral"

        def get_all_params(self, values):
            return {"Level": "not-a-valid-value"}

    class _Page:
        def __init__(self, data):
            self._data = data

        def get_data(self):
            return self._data

    wizard = TemplateWizard.__new__(TemplateWizard)
    wizard.category_page = _Page({"template": _Template()})
    wizard.param_page = _Page({"parameter_values": {}})
    wizard.target_page = _Page({"create_new": True, "instance_name": "TrkGeneral_1"})
    wizard.config_manager = manager
    wizard.parent_instance = None
    wizard.created_instance = None

    from PySide6 import QtWidgets
    errors = []
    monkeypatch.setattr(QtWidgets.QMessageBox, "critical",
                        staticmethod(lambda *args, **kwargs: errors.append(args[2])))

    # Level is a STRING parameter, so make the probe reject it the way the definition would
    def refuse(container, name, value):
        if value == "not-a-valid-value":
            from autosar_configurator.core.config_manager import ValidationError
            raise ValidationError(f"{name}: not allowed")
        return value
    monkeypatch.setattr(manager, "convert_parameter_value", refuse)

    wizard.accept()

    assert wizard.created_instance is None
    assert len(manager.configuration.containers) == 1          # nothing created
    assert errors                                               # the refusal was reported
