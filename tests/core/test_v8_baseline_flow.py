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


def add_module(project, module):
    [pkg] = [p for p in scan_library(project.module_libraries[0], Path(project.path).parent)
             if p.manifest.module == module]
    return project.add_module_from_package(pkg, 0)


def add_trk(project, confirm=None, persist=True):
    [pkg] = [p for p in scan_library(project.module_libraries[0], Path(project.path).parent)
             if p.manifest.module == "Trk"]
    return project.add_module_from_package(pkg, 0, persist=persist, confirm=confirm)


def add_arg(project):
    return add_module(project, "Arg")


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


def test_baseline_failure_never_aborts_the_project(tmp_path, monkeypatch):
    """One module's baseline error is reported; the rest of the project still opens."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast"})
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, module="Arg")
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    [arg] = [p for p in scan_library(wm.current_project.module_libraries[0],
                                     Path(wm.current_project.path).parent)
             if p.manifest.module == "Arg"]
    wm.current_project.add_module_from_package(arg, 0)
    wm.save_project()

    real = session.compute_new_base

    def boom(pkg, *args, **kwargs):
        if pkg.manifest.module == "Trk":
            raise RuntimeError("package exploded")
        return real(pkg, *args, **kwargs)

    monkeypatch.setattr(session, "compute_new_base", boom)
    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path))

    assert [name for name, _ in failed] == ["Trk"]
    assert "package exploded" in failed[0][1]
    assert "Trk" not in loaded.module_managers       # reported, not half-merged
    assert "Arg" in loaded.module_managers           # the rest of the project loaded
    assert "Trk" in loaded.module_entries            # kept so a save does not drop it
    assert "Trk" not in loaded.baselines


def test_readd_with_existing_config_reconciles_and_keeps_base(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()
    base_hash = wm.current_project.module_entries["Trk"].base_hash
    before_base = snapshot(wm.current_project).read_bytes()

    # remove_module drops the entry but leaves config/Trk.arxml on disk
    wm.current_project.remove_module("Trk")
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "9"})
    [pkg] = scan_library(wm.current_project.module_libraries[0],
                         Path(wm.current_project.path).parent)

    seen = []

    def confirm(text, result):
        seen.append(result)
        return True

    manager = wm.current_project.add_module_from_package(pkg, 0, confirm=confirm)

    assert len(seen) == 1 and seen[0].has_changes       # the change is reported, not silent
    (general,) = manager.configuration.containers
    assert general.parameter_values["Level"].value == "9"
    # Base is still the accepted one until the next save
    assert snapshot(wm.current_project).read_bytes() == before_base
    assert wm.current_project.module_entries["Trk"].base_hash == base_hash
    wm.save_project()
    assert snapshot(wm.current_project).read_bytes() != before_base


def test_readd_reject_keeps_the_accepted_base(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()
    before_base = snapshot(wm.current_project).read_bytes()

    wm.current_project.remove_module("Trk")
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "9"})
    [pkg] = scan_library(wm.current_project.module_libraries[0],
                         Path(wm.current_project.path).parent)

    manager = wm.current_project.add_module_from_package(pkg, 0, confirm=lambda text, r: False)

    (general,) = manager.configuration.containers
    assert general.parameter_values["Level"].value == "3"    # nothing written
    assert snapshot(wm.current_project).read_bytes() == before_base
    wm.save_project()
    assert snapshot(wm.current_project).read_bytes() == before_base


def test_orphan_baseline_is_not_written(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()

    # A baseline whose module entry is gone must not become a snapshot nobody records
    project = wm.current_project
    stale = project.baselines["Trk"]
    stale.dirty = True
    project.module_entries.pop("Trk")
    project.module_managers.pop("Trk")
    project.module_defs.pop("Trk")
    wm.save_project()

    assert snapshot(project).is_file()              # the old one is still there
    saved = json.loads(project_file(tmp_path).read_text(encoding="utf-8"))["modules"]
    assert [m["name"] for m in saved] == []


def test_layers_file_is_tied_to_its_snapshot(tmp_path):
    """Crash window A (layers written, snapshot not renamed) and a legacy layers file."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    project = wm.current_project
    baseline = project.baselines["Trk"]
    digest = project.module_entries["Trk"].base_hash
    layers_file = session.base_layers_path(project, "Trk")

    # A matching pair loads, layers included
    loaded = session.load_baseline(project, "Trk", digest)
    assert loaded.base_config is not None
    assert loaded.snapshot_hash == digest
    assert loaded.layers == baseline.layers
    assert loaded.pre_keys == baseline.pre_keys

    # Window A: the layers name a snapshot that is not the one on disk. The snapshot was
    # verified, so it stays Base; the layers are dropped (every value USER, only Pre forced)
    session.write_layers(layers_file, baseline, snapshot_hash="sha256:" + "0" * 64)
    stale = session.load_baseline(project, "Trk", digest)
    assert stale.base_config is not None
    assert flatten(stale.base_config, "Trk") == flatten(baseline.base_config, "Trk")
    assert stale.layers == {}
    assert stale.pre_keys == set()
    assert not stale.has_layers

    # A legacy layers file (no snapshot_hash) cannot prove which snapshot it describes
    data = json.loads(layers_file.read_text(encoding="utf-8"))
    data.pop("snapshot_hash")
    layers_file.write_text(json.dumps(data), encoding="utf-8")
    legacy = session.load_baseline(project, "Trk", digest)
    assert legacy.base_config is not None
    assert legacy.layers == {}
    assert legacy.pre_keys == set()


def test_one_reconcile_per_module_per_open(tmp_path, monkeypatch):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()

    real = session.compute_new_base
    calls = []

    def counting(pkg, *args, **kwargs):
        calls.append(pkg.manifest.module)
        return real(pkg, *args, **kwargs)

    monkeypatch.setattr(session, "compute_new_base", counting)
    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path))

    assert failed == []
    assert "Trk" in loaded.module_managers
    assert calls == ["Trk"]                      # composed once, merged once


def test_missing_base_hash_stays_a_migrated_project(tmp_path):
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    wm.save_project()
    data = json.loads(project_file(tmp_path).read_text(encoding="utf-8"))
    data["modules"][0].pop("base_hash")
    project_file(tmp_path).write_text(json.dumps(data), encoding="utf-8")
    assert snapshot(wm.current_project).is_file()          # the snapshot is still on disk

    seen = []

    def confirm(text, result):
        seen.append(result)
        return True

    # A Rec change would be ADOPT for a project whose Base is known; without the hash the
    # project is migrated, every value is USER, and nothing may be adopted silently.
    make_package(tmp_path / "lib", rec={"Mode": "Faster"}, pre={"Level": "3"})
    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path), confirm=confirm)

    assert failed == []
    assert flat(loaded)[GEN + "Mode"] == "Fast"            # USER, kept
    assert all(not r.has_changes for r in seen)


def test_save_survives_an_unwritable_snapshot(tmp_path, monkeypatch):
    """One module's snapshot failure must not cost the project file or the other modules."""
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, pre={"Level": "3"})
    make_package(tmp_path / "lib", rec={"Mode": "Fast"}, module="Arg")
    wm = new_project(tmp_path)
    add_trk(wm.current_project)
    add_arg(wm.current_project)
    wm.save_project()
    trk_hash = wm.current_project.module_entries["Trk"].base_hash

    # A merge is applied for Trk, so its baseline is dirty and would be written
    make_package(tmp_path / "lib", rec={"Mode": "Faster"}, pre={"Level": "3"})
    loaded, failed = WorkspaceManager().load_project(project_file(tmp_path),
                                                    confirm=lambda text, r: True)
    assert failed == []

    def boom(project, module, baseline):
        raise OSError("disk full")

    monkeypatch.setattr(session, "write_baseline", boom)
    wm2 = WorkspaceManager()
    wm2.current_project = loaded
    wm2.save_project()

    saved = {m["name"]: m for m in
             json.loads(project_file(tmp_path).read_text(encoding="utf-8"))["modules"]}
    assert sorted(saved) == ["Arg", "Trk"]          # the project file was written
    assert saved["Trk"]["base_hash"] == trk_hash    # the old hash is kept, not None


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

    session.write_layers(path, baseline, snapshot_hash=project.module_entries["Trk"].base_hash)
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
