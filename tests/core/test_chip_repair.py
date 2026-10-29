"""Repair of an existing chip (add-chip-repair-core)."""
import copy
import shutil
from pathlib import Path

import pytest
import yaml

from autosar_configurator.core.hardware import chip_repair as repair
from autosar_configurator.core.hardware.chip_completeness import check_chip, unconfirmed_marks
from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
    default_chips_dir,
    ecu_resources_from_properties,
)
from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter, chip_checksum
from autosar_configurator.core.hardware.generic_resource import GenericResourceDef
from autosar_configurator.core.hardware.project_chip_store import ProjectChipStore
from autosar_configurator.core.workspace_manager import WorkspaceProject
from tools import chip_repair as cli

THA610X = "THA610X_LFBGA180"
MARK = "ecu_resources.Os.IsrTriggerMethodList"


def _props(path: Path, text: str) -> Path:
    path.write_text(text, encoding="utf-8")
    return path


def _library(tmp_path: Path, *chips: ChipDefinition) -> ChipDatabase:
    """A chip library directory under tmp_path holding the given chips."""
    lib = tmp_path / "chips"
    lib.mkdir(exist_ok=True)
    for chip in chips:
        ChipDefinitionExporter().save_yaml(chip, lib / f"{chip.name}.yaml")
    return ChipDatabase(lib)


def _builtin_copy(tmp_path: Path, name: str = THA610X) -> ChipDatabase:
    lib = tmp_path / "chips"
    lib.mkdir(exist_ok=True)
    shutil.copy2(default_chips_dir() / f"{name}.yaml", lib / f"{name}.yaml")
    return ChipDatabase(lib)


def _base(db: ChipDatabase, name: str) -> ChipDefinition:
    return copy.deepcopy(db.get_chip(name))


# --- sources and difference -------------------------------------------------------

def test_difference_added_removed_changed_in_key_order():
    old = {"Port": {"MaxAvailablePinID": 15}, "Mcu": {"ClockCount": 3}}
    new = {"Port": {"MaxAvailablePinID": 16, "AvailableReadOnlyPorts": "_40_"}}
    diff = repair.diff_ecu_resources(old, new)
    assert [(c.key, c.kind) for c in diff.changes] == [
        ("Mcu.ClockCount", repair.REMOVED),
        ("Port.AvailableReadOnlyPorts", repair.ADDED),
        ("Port.MaxAvailablePinID", repair.CHANGED),
    ]
    changed = diff.get("Port.MaxAvailablePinID")
    assert (changed.old, changed.new, changed.type_only) == (15, 16, False)


def test_range_notation_equals_list(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"L": [1] * 20}}))
    assert "0-19" in (tmp_path / "chips" / "C.yaml").read_text(encoding="utf-8")   # written as a range
    assert not repair.diff_ecu_resources(db.get_chip("C").ecu_resources, {"Os": {"L": [1, 1, 1, 1] * 5}})


@pytest.mark.parametrize("a, b", [(1, "1"), ([1, 2], ["1", "2"]), (True, "True")])
def test_type_only_difference(a, b):
    change = repair.diff_ecu_resources({"OsResource": {"NumOfCores": a}},
                                       {"OsResource": {"NumOfCores": b}}).changes[0]
    assert change.kind == repair.CHANGED and change.type_only


def test_bool_and_int_differ():
    assert repair.diff_ecu_resources({"M": {"K": 1}}, {"M": {"K": True}})


def test_partial_source_compares_only_its_modules():
    diff = repair.diff_from_source({"Port": {"A": 1}, "Mcu": {"B": 2}}, {"Port": {"A": 2}})
    assert diff.keys() == ["Port.A"]


def test_properties_read_without_changing_any_chip_later_file_wins(tmp_path):
    a = _props(tmp_path / "a.properties", "Port.A: 1\nPort.B: 2\n")
    b = _props(tmp_path / "b.properties", "Port.B: 3\nMcu.C: 4\n")
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Port": {"A": 0}}))
    before = (tmp_path / "chips" / "C.yaml").read_text(encoding="utf-8")
    assert ecu_resources_from_properties([a, b]) == {"Port": {"A": 1, "B": 3}, "Mcu": {"C": 4}}
    assert db.get_chip("C").ecu_resources == {"Port": {"A": 0}}
    assert (tmp_path / "chips" / "C.yaml").read_text(encoding="utf-8") == before


def test_keys_referenced_but_missing():
    chip = ChipDefinition(name="C", ecu_resources={"OsResource": {"MasterCore": "OS_CORE_ID_0"}})
    diff = repair.missing_key_changes(chip, ["OsResource.NumOfCores", "OsResource.MasterCore", "NoModule"])
    assert [(c.key, c.kind, c.new) for c in diff.changes] == [("OsResource.NumOfCores", repair.ADDED, None)]


# --- merge ------------------------------------------------------------------------

def _merge_case():
    chip = ChipDefinition(name="C", family="F", ecu_resources={
        "Mcu": {"ClockCount": 3, "Z": 0}, "Port": {"B": 1, "D": 2}})
    new = {"Mcu": {"Z": 0}, "Port": {"B": 9, "D": 2, "C": 5, "A": 4}, "Can": {"N": 1}}
    return chip, repair.diff_ecu_resources(chip.ecu_resources, new)


def test_only_selected_keys_applied_and_input_unchanged():
    chip, diff = _merge_case()
    before = copy.deepcopy(chip)
    merged = repair.apply_changes(chip, diff, ["Port.B"])
    assert merged.ecu_resources == {"Mcu": {"ClockCount": 3, "Z": 0}, "Port": {"B": 9, "D": 2}}
    assert merged.family == "F"
    assert chip == before


def test_removal_only_when_selected():
    chip, diff = _merge_case()
    merged = repair.apply_changes(chip, diff, diff.keys(repair.ADDED, repair.CHANGED))
    assert merged.ecu_resources["Mcu"]["ClockCount"] == 3
    removed = repair.apply_changes(chip, diff, ["Mcu.ClockCount"])
    assert "ClockCount" not in removed.ecu_resources["Mcu"]


def test_positions_kept_added_keys_appended_in_key_order():
    chip, diff = _merge_case()
    merged = repair.apply_changes(chip, diff, diff.keys())
    assert list(merged.ecu_resources) == ["Mcu", "Port", "Can"]
    assert list(merged.ecu_resources["Port"]) == ["B", "D", "A", "C"]


def test_nothing_selected_and_unknown_key():
    chip, diff = _merge_case()
    assert repair.apply_changes(chip, diff, []) == chip
    with pytest.raises(ValueError, match="Port.X"):
        repair.apply_changes(chip, diff, ["Port.X"])


# --- unconfirmed marks ------------------------------------------------------------

def test_confirm_removes_only_the_mark():
    chip = ChipDefinition(name="C", metadata={"flash_size": "4MB", "ram_size": "512KB",
                                              "unconfirmed": {"metadata.flash_size": "a", "metadata.ram_size": "b"}})
    confirmed = repair.confirm_fields(chip, ["metadata.flash_size"])
    assert "metadata.flash_size" not in unconfirmed_marks(confirmed)
    assert "metadata.ram_size" in unconfirmed_marks(confirmed)
    assert confirmed.metadata["flash_size"] == chip.metadata["flash_size"]
    assert all(i.field != "metadata.flash_size" for i in check_chip(confirmed))
    assert "metadata.flash_size" in unconfirmed_marks(chip)          # input unchanged
    with pytest.raises(ValueError):
        repair.confirm_fields(chip, ["metadata.nothing"])


def test_confirm_list_form_and_last_mark():
    chip = ChipDefinition(name="C", metadata={"unconfirmed": ["ports"]})
    assert "unconfirmed" not in repair.confirm_fields(chip, ["ports"]).metadata


def test_mark_unconfirmed_reports_incomplete():
    chip = ChipDefinition(name="C", ecu_resources={"Intc": {"A": 1}})
    marked = repair.mark_unconfirmed(chip, "ecu_resources.Intc", "待核对")
    assert unconfirmed_marks(marked) == {"ecu_resources.Intc": "待核对"}
    assert marked.ecu_resources == chip.ecu_resources
    assert any(i.field == "ecu_resources.Intc" for i in check_chip(marked))


# --- views ------------------------------------------------------------------------

def _view(report, name):
    return next(v for v in report if v.view == name)


def test_derived_types_replaced_other_types_kept():
    pwm = GenericResourceDef("pwm_channel", "PWM0", "PWM0", {})
    old_can = GenericResourceDef("can_controller", "CAN0", "CAN0", {})
    chip = ChipDefinition(name="C", resources={"pwm_channel": [pwm], "can_controller": [old_can]},
                          ecu_resources={"Can": {"MaxModules": 2}})
    derived, report = repair.derive_views(chip)
    assert [r.resource_id for r in derived.resources["can_controller"]] == ["CAN0", "CAN1"]
    assert derived.resources["pwm_channel"] == [pwm]
    assert _view(report, "resources").state == repair.UPDATED
    assert chip.resources["can_controller"] == [old_can]


def test_core_fields_only_where_a_key_exists_or_disagrees():
    chip = ChipDefinition(name="C", metadata={"cores": {"count": 2, "available": ["CORE0", "CORE1"],
                                                        "master": "CORE0"}})
    assert _view(repair.derive_views(chip)[1], "metadata.cores").state == repair.NOT_DERIVED

    chip.ecu_resources = {"OsResource": {"NumOfCores": 4}}
    derived, report = repair.derive_views(chip)
    assert derived.metadata["cores"] == {"count": 4, "available": ["CORE0", "CORE1"], "master": "CORE0"}
    assert _view(report, "metadata.cores").state == repair.UPDATED


def test_core_count_kept_when_one_key_agrees():
    # THA610X: MCAL counts the lockstep cores (2), the Os uses one
    chip = ChipDefinition(name="C", metadata={"cores": {"count": 2}},
                          ecu_resources={"OsResource": {"NumOfCores": 1}, "Resource": {"NumOfCores": 2}})
    derived, report = repair.derive_views(chip)
    assert derived.metadata["cores"]["count"] == 2
    assert _view(report, "metadata.cores").state == repair.UNCHANGED


def test_ports_not_derived_without_derivation(monkeypatch):
    from autosar_configurator.core.hardware import ecu_resource_diagnostics

    monkeypatch.delattr(ecu_resource_diagnostics, "ports_from_ecu", raising=False)
    chip = ChipDefinition(name="C", ecu_resources={"Port": {"AvailablePortsID": "_0_"}})
    derived, report = repair.derive_views(chip)
    assert _view(report, "ports").state == repair.NOT_DERIVED
    assert derived.ports == chip.ports


@pytest.mark.parametrize("name", ["SC300", "THA610X_LFBGA180", "THA6206_LFBGA292", "THA6412_BGA516"])
def test_builtin_chip_views_already_match_their_ecu_resources(name):
    chip = ChipDatabase()._load_chip_from_yaml(default_chips_dir() / f"{name}.yaml")
    derived, report = repair.derive_views(chip)
    assert all(v.state != repair.UPDATED for v in report), report
    assert chip_checksum(derived) == chip_checksum(chip)


# --- saving and history -----------------------------------------------------------

def _record(**kw):
    kw.setdefault("source", "test.properties")
    kw.setdefault("author", "tester")
    return repair.RepairRecord(**kw)


def test_save_with_backup_version_checksum_and_library(tmp_path):
    _builtin_copy(tmp_path)
    # the library chips are all confirmed, so mark one field to have something to confirm
    chip_file = tmp_path / "chips" / f"{THA610X}.yaml"
    marked = chip_file.read_text(encoding="utf-8").replace(
        "    master: CORE0\n", f"    master: CORE0\n  unconfirmed:\n    {MARK}: 待核对\n", 1)
    chip_file.write_text(marked, encoding="utf-8")
    db = ChipDatabase(tmp_path / "chips")
    base = _base(db, THA610X)
    assert MARK in base.metadata["unconfirmed"]
    old_text = chip_file.read_text(encoding="utf-8")
    diff = repair.diff_from_source(base.ecu_resources, {"Port": {"MaxAvailablePinID": 99}})
    chip = repair.confirm_fields(repair.apply_changes(base, diff, diff.keys()), [MARK])

    result = repair.save_repaired_chip(db, chip, base, _record(
        note="n", confirm_notes={MARK: "按 SDK 链接脚本核对"}))
    assert result.saved and result.version == repair.next_version(base.resource_version)
    assert result.backup.read_text(encoding="utf-8") == old_text
    reloaded = ChipDatabase()._load_chip_from_yaml(result.path)
    assert not reloaded.content_modified
    assert reloaded.resource_version == result.version
    assert reloaded.ecu_resources["Port"]["MaxAvailablePinID"] == 99
    assert db.get_chip(THA610X).ecu_resources["Port"]["MaxAvailablePinID"] == 99

    history = yaml.safe_load(result.history.read_text(encoding="utf-8"))
    assert history["chip"] == THA610X and len(history["entries"]) == 1
    entry = history["entries"][0]
    assert entry["author"] == "tester" and entry["source"] == "test.properties"
    assert entry["resource_version"] == {"old": base.resource_version, "new": result.version}
    assert entry["ecu_resources"]["changed"] == [{"key": "Port.MaxAvailablePinID", "old": 15, "new": 99}]
    assert entry["confirmed"] == [{"field": MARK, "note": "按 SDK 链接脚本核对"}]
    assert entry["checksum"] == chip_checksum(reloaded)


def test_second_repair_appends_history(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    for value in (2, 3):
        base = _base(db, "C")
        chip = copy.deepcopy(base)
        chip.ecu_resources["Os"]["A"] = value
        result = repair.save_repaired_chip(db, chip, base, _record(note=str(value)))
    entries = yaml.safe_load(result.history.read_text(encoding="utf-8"))["entries"]
    assert [e["note"] for e in entries] == ["2", "3"]
    assert [e["resource_version"]["new"] for e in entries] == ["1.0.0", "1.0.1"]


def test_rename_refused(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    base = _base(db, "C")
    chip = copy.deepcopy(base)
    chip.name = "D"
    with pytest.raises(ValueError, match="rename"):
        repair.save_repaired_chip(db, chip, base, _record())
    assert not (tmp_path / "chips" / "D.yaml").exists()


def test_file_changed_meanwhile_refused(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    base = _base(db, "C")
    ChipDefinitionExporter().save_yaml(ChipDefinition(name="C", ecu_resources={"Os": {"A": 5}}),
                                       tmp_path / "chips" / "C.yaml")
    chip = copy.deepcopy(base)
    chip.ecu_resources["Os"]["A"] = 2
    with pytest.raises(repair.ChipFileChanged):
        repair.save_repaired_chip(db, chip, base, _record())
    assert not (tmp_path / "chips" / "C.yaml.bak").exists()


def test_chip_edited_outside_designer_can_be_repaired(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    path = tmp_path / "chips" / "C.yaml"
    path.write_text(path.read_text(encoding="utf-8").replace("A: 1", "A: 7"), encoding="utf-8")
    db = ChipDatabase(tmp_path / "chips")
    base = _base(db, "C")
    assert base.content_modified
    chip = copy.deepcopy(base)
    chip.ecu_resources["Os"]["A"] = 8
    result = repair.save_repaired_chip(db, chip, base, _record())
    entry = yaml.safe_load(result.history.read_text(encoding="utf-8"))["entries"][0]
    assert entry["base_modified_outside"] is True
    assert not ChipDatabase()._load_chip_from_yaml(path).content_modified


def test_unchanged_chip_not_written(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    base = _base(db, "C")
    result = repair.save_repaired_chip(db, copy.deepcopy(base), base, _record())
    assert not result.saved
    assert not (tmp_path / "chips" / "history").exists()


@pytest.mark.parametrize("old, new", [("", "1.0.0"), ("1.0.0", "1.0.1"), ("2.9", "2.10"), ("1.0-rc", "1.0-rc.1")])
def test_next_version(old, new):
    assert repair.next_version(old) == new


def test_given_version_used(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", resource_version="1.0.0", ecu_resources={"Os": {"A": 1}}))
    base = _base(db, "C")
    chip = copy.deepcopy(base)
    chip.ecu_resources["Os"]["A"] = 2
    assert repair.save_repaired_chip(db, chip, base, _record(version="2.0.0")).version == "2.0.0"


def test_author_defaults_to_git_or_os_user(tmp_path, monkeypatch):
    monkeypatch.setattr(repair, "git_author", lambda cwd=None: "git-user")
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    base = _base(db, "C")
    chip = copy.deepcopy(base)
    chip.ecu_resources["Os"]["A"] = 2
    result = repair.save_repaired_chip(db, chip, base, repair.RepairRecord(source="s"))
    assert yaml.safe_load(result.history.read_text(encoding="utf-8"))["entries"][0]["author"] == "git-user"


def test_git_author_falls_back_to_os_user(monkeypatch):
    def fail(*a, **k):
        raise OSError("no git")
    monkeypatch.setattr(repair.subprocess, "run", fail)
    monkeypatch.setattr(repair.getpass, "getuser", lambda: "os-user")
    assert repair.git_author() == "os-user"


def test_library_ignores_history(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    base = _base(db, "C")
    chip = copy.deepcopy(base)
    chip.ecu_resources["Os"]["A"] = 2
    repair.save_repaired_chip(db, chip, base, _record())
    assert (tmp_path / "chips" / "history" / "C.yaml").exists()
    assert ChipDatabase(tmp_path / "chips").list_chips() == ["C"]


def test_project_copy_reports_repaired_library_chip(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}}))
    project_dir = tmp_path / "proj"
    project_dir.mkdir()
    project = WorkspaceProject("p", project_dir / "p.dpa")
    project.selected_chip = "C"
    project.chip_database = db
    project.adopt_selected_chip()
    assert ProjectChipStore(project_dir).load("C") is not None
    assert project.chip_data_findings() == []

    base = _base(db, "C")
    chip = copy.deepcopy(base)
    chip.ecu_resources["Os"]["A"] = 2
    repair.save_repaired_chip(db, chip, base, _record())
    assert any("different version" in m for m in project.chip_data_findings())


# --- command line -----------------------------------------------------------------

def _cli_library(tmp_path):
    db = _library(tmp_path, ChipDefinition(name="C", resource_version="1.0.0", metadata={
        "unconfirmed": {"metadata.flash_size": "x"}}, ecu_resources={"Port": {"A": 1, "B": 2, "Gone": 0}}))
    src = _props(tmp_path / "Port.properties", "Port.A: 1\nPort.B: 5\nPort.New: 7\n")
    return db, src


def test_cli_diff_writes_nothing(tmp_path, capsys):
    db, src = _cli_library(tmp_path)
    before = sorted(p.name for p in (tmp_path / "chips").iterdir())
    assert cli.main(["diff", "C", str(src), "--chips-dir", str(db.data_dir)]) == cli.EXIT_OK
    out = capsys.readouterr().out
    assert "~ Port.B: 2 -> 5" in out and "+ Port.New = 7" in out and "- Port.Gone = 0" in out
    assert sorted(p.name for p in (tmp_path / "chips").iterdir()) == before


def test_cli_apply_without_removals(tmp_path, monkeypatch):
    monkeypatch.setattr(repair, "git_author", lambda cwd=None: "tester")
    db, src = _cli_library(tmp_path)
    code = cli.main(["apply", "C", str(src), "--chips-dir", str(db.data_dir), "--all-added", "--all-changed",
                     "--source", "Port.properties", "--confirm", "metadata.flash_size=核对过"])
    assert code == cli.EXIT_OK
    chip = ChipDatabase(db.data_dir).get_chip("C")
    assert chip.ecu_resources["Port"] == {"A": 1, "B": 5, "Gone": 0, "New": 7}
    assert "unconfirmed" not in chip.metadata
    entry = yaml.safe_load((db.data_dir / "history" / "C.yaml").read_text(encoding="utf-8"))["entries"][0]
    assert entry["ecu_resources"]["removed"] == []
    assert entry["confirmed"] == [{"field": "metadata.flash_size", "note": "核对过"}]


def test_cli_nothing_to_change(tmp_path):
    db, _ = _cli_library(tmp_path)
    same = _props(tmp_path / "same.properties", "Port.A: 1\nPort.B: 2\nPort.Gone: 0\n")
    args = [str(same), "--chips-dir", str(db.data_dir)]
    assert cli.main(["diff", "C"] + args) == cli.EXIT_NOTHING
    assert cli.main(["apply", "C"] + args + ["--all-changed", "--source", "s"]) == cli.EXIT_NOTHING


def test_cli_changed_file_and_bad_arguments(tmp_path, monkeypatch):
    db, src = _cli_library(tmp_path)
    real_save = repair.save_repaired_chip

    def save_after_edit(database, chip, base, record, path=None):
        ChipDefinitionExporter().save_yaml(ChipDefinition(name="C", ecu_resources={"Port": {"A": 9}}),
                                           db.data_dir / "C.yaml")
        return real_save(database, chip, base, record, path)

    monkeypatch.setattr(repair, "save_repaired_chip", save_after_edit)
    args = ["apply", "C", str(src), "--chips-dir", str(db.data_dir), "--source", "s"]
    assert cli.main(args + ["--all-changed"]) == cli.EXIT_ERROR
    assert cli.main(args + ["--keys", "Port.Nope"]) == cli.EXIT_ERROR
    assert cli.main(args + ["--confirm", "no-equals-sign"]) == cli.EXIT_ERROR


# --- session ----------------------------------------------------------------------

def _session_library(tmp_path):
    return _library(tmp_path, ChipDefinition(
        name="C", resource_version="1.0.0",
        metadata={"unconfirmed": {"metadata.flash_size": "x", "ports": "y"}},
        ecu_resources={"Port": {"A": 1, "B": 2, "Gone": 0}}))


def test_session_properties_win_over_missing_keys(tmp_path, monkeypatch):
    from autosar_configurator.core.hardware import ecu_resource_diagnostics

    db = _session_library(tmp_path)
    monkeypatch.setattr(ecu_resource_diagnostics, "collect_referenced_keys_in_dirs",
                        lambda dirs: {"Port.New": {"Port"}, "Os.Missing": {"Os"}})
    session = repair.RepairSession(db, "C")
    session.properties = [_props(tmp_path / "p.properties", "Port.A: 1\nPort.B: 5\nPort.New: 7\n")]
    session.scan_dirs = [tmp_path]
    diff = session.load_sources()
    assert diff.keys() == ["Os.Missing", "Port.B", "Port.Gone", "Port.New"]
    assert diff.get("Port.New").new == 7                      # the file's value, not the placeholder
    assert diff.get("Os.Missing").new is repair.PLACEHOLDER


def test_session_default_selection_excludes_removals(tmp_path):
    session = repair.RepairSession(_session_library(tmp_path), "C")
    session.properties = [_props(tmp_path / "p.properties", "Port.A: 1\nPort.B: 5\nPort.New: 7\n")]
    session.load_sources()
    assert session.selected == {"Port.B", "Port.New"}
    chip, _ = session.build()
    assert chip.ecu_resources["Port"] == {"A": 1, "B": 5, "Gone": 0, "New": 7}


def test_session_marks_only(tmp_path):
    db = _session_library(tmp_path)
    session = repair.RepairSession(db, "C")
    session.load_sources()
    assert not session.diff
    session.confirm_notes = {"metadata.flash_size": "核对过"}
    session.new_marks = {"ecu_resources.Port": "待核对"}
    chip, _ = session.build()
    assert unconfirmed_marks(chip) == {"ports": "y", "ecu_resources.Port": "待核对"}
    assert chip.ecu_resources == session.base.ecu_resources

    resolved, remaining, new = session.completeness_change(chip)
    assert [i.field for i in resolved] == ["metadata.flash_size"]
    assert [i.field for i in remaining] == ["ports"]
    assert [i.field for i in new] == ["ecu_resources.Port"]

    result = session.save(repair.RepairRecord(source="核实", author="tester"))
    entry = yaml.safe_load(result.history.read_text(encoding="utf-8"))["entries"][0]
    assert entry["confirmed"] == [{"field": "metadata.flash_size", "note": "核对过"}]
    assert entry["marked"] == [{"field": "ecu_resources.Port", "note": "待核对"}]
    assert repair.read_history(result.path)[0]["source"] == "核实"


def test_session_unknown_chip_and_unchanged(tmp_path):
    db = _session_library(tmp_path)
    with pytest.raises(ValueError):
        repair.RepairSession(db, "NOPE")
    session = repair.RepairSession(db, "C")
    assert not session.has_changes(session.build()[0])
    assert not session.save(repair.RepairRecord(source="s", author="t")).saved
    assert repair.read_history(session.chip_file) == []
