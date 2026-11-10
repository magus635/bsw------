"""Format 8 baseline flow: reconcile module packages on load, add-module and save.

The fixture is a hand-written module package (definition, one value file holding both the
Rec and the Pre collection, ``module.json``).  The definition declares no container, so
Base' is exactly Rec over Pre: the assertions are about the merge, not about defaults,
which ``tests/core/baseline/test_compose.py`` already covers.
"""
import json
from pathlib import Path

from autosar_configurator.core.baseline import session
from autosar_configurator.core.baseline.values import flatten
from autosar_configurator.core.packages.library import LibraryRef, scan_library
from autosar_configurator.core.workspace_manager import WorkspaceManager

GEN = "P:/Trk/TrkGeneral."

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
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>"""

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
    return _COLLECTION.format(name=name, params=body)


def _write(root, rel, text):
    path = root / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def make_package(lib, rec, pre=None):
    """(Re)write the package under ``lib/Trk`` with the given Rec and Pre values."""
    collections = [_collection("Trk_Rec", rec)]
    if pre:
        collections.append(_collection("Trk_Pre", pre))
    _write(lib, "Trk/def/Trk.arxml", _DEF)
    _write(lib, "Trk/config/Trk_values.arxml", _VALUES.format(collections="\n".join(collections)))
    (lib / "Trk" / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "Trk",
        "definition": "/Vendor/Trk",
        "files": ["def/Trk.arxml", "config/Trk_values.arxml"],
        "rec": ["/Vendor/Trk_Rec"],
        "pre": ["/Vendor/Trk_Pre"] if pre else [],
    }), encoding="utf-8")


def new_project(tmp_path):
    wm = WorkspaceManager()
    project = wm.create_project("P", tmp_path / "proj" / "P.dpa", format_version=8)
    project.selected_chip = None
    project.module_libraries.append(LibraryRef(path=(tmp_path / "lib").as_posix(), kind="package"))
    return wm


def add_trk(project):
    [pkg] = scan_library(project.module_libraries[0], Path(project.path).parent)
    project.add_module_from_package(pkg, 0)


def flat(project, module="Trk"):
    return flatten(project.module_managers[module].configuration, module)


def snapshot(project, module="Trk"):
    return session.base_snapshot_path(project, module)


def project_file(tmp_path):
    return tmp_path / "proj" / "P.dpa"


def test_add_module_initialises_from_rec_and_pre(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast", "Ratio": "10"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    project = wm.current_project

    values = flat(project)
    assert values[GEN + "Mode"] == "Fast"
    assert values[GEN + "Ratio"] == "10"
    assert values[GEN + "Level"] == "3"
    assert snapshot(project).is_file()
    assert project.module_entries["Trk"].base_hash is not None
    assert project.baselines["Trk"].pre_keys == {"C:/Trk/TrkGeneral", GEN + "Level"}


def test_reopen_without_package_change_no_confirm(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()
    before = snapshot(wm.current_project).read_bytes()
    base_hash = wm.current_project.module_entries["Trk"].base_hash

    def confirm(text, result):
        raise AssertionError("confirm must not be called when the baseline did not change")

    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path), confirm=confirm)

    assert failed == []
    assert flat(loaded)[GEN + "Mode"] == "Fast"
    assert snapshot(loaded).read_bytes() == before
    assert loaded.module_entries["Trk"].base_hash == base_hash


def test_rec_change_follows_untouched_keeps_user(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast", "Ratio": "10"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    manager = wm.current_project.module_managers["Trk"]
    (general,) = manager.configuration.containers
    manager.set_parameter_value(general, "Mode", "Slow")
    wm.save_project()

    make_package(tmp_path / "lib", rec={"Mode": "Faster", "Ratio": "20"}, pre={"Level": "9"})
    seen = []

    def confirm(text, result):
        seen.append(text)
        return True

    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path), confirm=confirm)

    assert failed == []
    assert len(seen) == 1 and "Trk" in seen[0]
    values = flat(loaded)
    assert values[GEN + "Mode"] == "Slow"          # user value kept
    assert values[GEN + "Ratio"] == "20"           # untouched Rec value follows
    assert values[GEN + "Level"] == "9"            # Pre forced
    reports = sorted((tmp_path / "proj" / ".history" / "reports").glob("*_merge_Trk.md"))
    assert len(reports) == 1
    assert "Slow" in reports[0].read_text(encoding="utf-8")


def test_reject_keeps_active_and_base(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()
    config_file = tmp_path / "proj" / "config" / "Trk.arxml"
    before_config = config_file.read_bytes()
    before_base = snapshot(wm.current_project).read_bytes()

    make_package(tmp_path / "lib", rec={"Mode": "Faster"}, pre={"Level": "9"})
    calls = []

    def reject(text, result):
        calls.append(result)
        return False

    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path), confirm=reject)
    assert failed == []
    assert len(calls) == 1 and calls[0].has_changes
    assert flat(loaded)[GEN + "Mode"] == "Fast"
    assert flat(loaded)[GEN + "Level"] == "3"
    assert snapshot(loaded).read_bytes() == before_base
    wm2 = WorkspaceManager()
    wm2.current_project = loaded
    wm2.save_project()
    assert config_file.read_bytes() == before_config

    again = []
    WorkspaceManager().load_project(project_file(tmp_path),
                                    confirm=lambda text, result: again.append(result) or False)
    assert len(again) == 1                       # the next open prompts again


def test_no_snapshot_keeps_user_values_and_records_base(tmp_path):
    """A migrated module (Active, no snapshot): no Rec value is overwritten, Base' is kept."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast", "Ratio": "10"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    manager = wm.current_project.module_managers["Trk"]
    (general,) = manager.configuration.containers
    manager.set_parameter_value(general, "Mode", "Slow")
    manager.set_parameter_value(general, "Ratio", "99")
    wm.save_project()
    # Drop the snapshot and its hash: the project now looks migrated
    for path in (tmp_path / "proj" / "config" / "base").iterdir():
        path.unlink()
    data = json.loads(project_file(tmp_path).read_text(encoding="utf-8"))
    data["modules"][0].pop("base_hash")
    project_file(tmp_path).write_text(json.dumps(data), encoding="utf-8")

    def confirm(text, result):
        raise AssertionError("no Rec value may overwrite a user value without a confirm")

    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path), confirm=confirm)

    assert failed == []
    values = flat(loaded)
    assert values[GEN + "Mode"] == "Slow"          # USER, kept
    assert values[GEN + "Ratio"] == "99"           # USER, kept
    assert values[GEN + "Level"] == "3"            # Pre, already equal
    wm2 = WorkspaceManager()
    wm2.current_project = loaded
    wm2.save_project()
    assert (tmp_path / "proj" / "config" / "base" / "Trk.arxml").is_file()
    assert loaded.module_entries["Trk"].base_hash is not None


def test_v7_project_never_reconciles(tmp_path):
    legacy = tmp_path / "legacy" / "L.dpa"
    legacy.parent.mkdir(parents=True)
    legacy.write_text(json.dumps({
        "format_version": 7, "name": "L", "project_type": "Vector DaVinci",
        "variants": ["Default"], "active_variant": "Default", "modules": [],
    }), encoding="utf-8")

    def confirm(text, result):
        raise AssertionError("a format 7 project must never reconcile")

    project, failed = WorkspaceManager().load_project(legacy, confirm=confirm)

    assert failed == []
    assert project.format_version == 7
    assert project.baselines == {}
    assert not (tmp_path / "legacy" / "config").exists()


def test_merge_apply_error_lands_in_failed_modules(tmp_path, monkeypatch):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()

    make_package(tmp_path / "lib", rec={"Mode": "Faster"}, pre={"Level": "9"})

    def boom(*args, **kwargs):
        raise session.MergeApplyError("planned failure")

    monkeypatch.setattr(session, "apply_merge", boom)
    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path),
                                                    confirm=lambda text, result: True)

    assert [name for name, _ in failed] == ["Trk"]
    assert "planned failure" in failed[0][1]
    assert "Trk" not in loaded.module_managers
    assert "Trk" in loaded.module_entries


def test_layers_file_round_trips(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    project = wm.current_project
    baseline = project.baselines["Trk"]
    path = session.base_layers_path(project, "Trk")

    session.write_layers(path, baseline)
    read_back = session.read_layers(path)

    assert read_back.layers == baseline.layers
    assert read_back.pre_keys == baseline.pre_keys
    assert read_back.module_name == "Trk"
    assert read_back.has_layers

    # The values live in the snapshot, which load_baseline() attaches to the layers
    reloaded = session.load_baseline(project, "Trk", project.module_entries["Trk"].base_hash)
    assert reloaded.base_config is not None
    assert flatten(reloaded.base_config, "Trk") == flatten(baseline.base_config, "Trk")
    assert reloaded.layers == baseline.layers
    assert reloaded.pre_keys == baseline.pre_keys
