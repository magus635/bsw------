"""Editing helpers and directory scan behind the designer's ECU resource page."""
from pathlib import Path

import pytest

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter
from autosar_configurator.core.hardware.ecu_resource_data import (
    PLACEHOLDER,
    check_module_name,
    count_placeholders,
    delete_entry,
    infer_scalar,
    list_to_range_rows,
    range_rows_to_list,
    rename_entry,
    rename_module,
    set_entry,
    value_type_name,
)
from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
    collect_referenced_keys,
    collect_referenced_keys_in_dirs,
)
from autosar_configurator.core.hardware.ecu_resource_resolver import (
    library_other_chip_keys,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject

# --- type inference -----------------------------------------------------------

@pytest.mark.parametrize("text, expected", [
    ("4", 4), ("-1", -1), ("0x10", 16), ("0X1f", 31), ("1.5", 1.5),
    ("true", True), ("Off", False), ("yes", True),
    ("CORE0", "CORE0"), ("(0U)", "(0U)"), ("0x1234UL", "0x1234UL"), ("", PLACEHOLDER),
    ("  7  ", 7),
])
def test_infer_scalar_follows_properties_rules(text, expected):
    got = infer_scalar(text)
    assert got == expected and type(got) is type(expected)


def test_keep_string_overrides_inference():
    assert infer_scalar("007", keep_string=True) == "007"
    assert infer_scalar("true", keep_string=True) == "true"


def test_value_type_names():
    assert [value_type_name(v) for v in (None, True, 3, 1.5, "x", [1, 2])] == [
        "empty", "bool", "int", "float", "string", "list[2]"]


# --- set / delete / rename -----------------------------------------------------

def test_set_and_delete_entries():
    res = {}
    set_entry(res, "OsResource", "NumOfCores", 4)
    set_entry(res, "Mcu", "PllFreq", [1, 2])
    assert res == {"OsResource": {"NumOfCores": 4}, "Mcu": {"PllFreq": [1, 2]}}
    delete_entry(res, "Mcu", "PllFreq")
    assert "Mcu" not in res                        # an empty module disappears
    delete_entry(res, "Nope", "x")                 # deleting nothing is not an error


@pytest.mark.parametrize("module, name, value", [
    ("Os.X", "k", 1),            # dot in module name
    ("", "k", 1),
    ("Os", "", 1),
    ("Os", "k", [[1], [2]]),     # nested list
    ("Os", "k", {"bad": 1}),     # mapping that is not an index range
])
def test_set_entry_rejects_what_the_loader_rejects(module, name, value):
    res = {}
    with pytest.raises(ValueError):
        set_entry(res, module, name, value)
    assert res == {}


def test_set_entry_accepts_range_mapping_and_expands_it():
    res = {}
    set_entry(res, "Os", "L", {"0-1": 1, 2: 2})
    assert res["Os"]["L"] == [1, 1, 2]


def test_rename_key_keeps_position_and_refuses_overwrite():
    res = {"M": {"a": 1, "b": 2, "c": 3}}
    rename_entry(res, "M", "b", "z")
    assert list(res["M"]) == ["a", "z", "c"] and res["M"]["z"] == 2
    with pytest.raises(ValueError):
        rename_entry(res, "M", "a", "c")
    assert list(res["M"]) == ["a", "z", "c"]


def test_rename_module_keeps_order_and_refuses_merge():
    res = {"A": {"k": 1}, "B": {"k": 2}}
    rename_module(res, "A", "C")
    assert list(res) == ["C", "B"]
    with pytest.raises(ValueError):
        rename_module(res, "C", "B")
    with pytest.raises(ValueError):
        check_module_name("a.b")


def test_placeholders_are_counted():
    assert count_placeholders({"M": {"a": None, "b": 1, "c": None}, "N": {"d": None}}) == 3


# --- range rows -----------------------------------------------------------------

def test_range_rows_roundtrip():
    values = [1] * 20 + [2, 2, 3]
    rows = list_to_range_rows(values)
    assert rows == [("0-19", 1), ("20-21", 2), ("22", 3)]
    assert range_rows_to_list("Os.L", rows) == values


def test_range_rows_edit_one_range_leaves_the_rest():
    values = [1] * 16 + [2, 2, 2] + [4] * 973          # 992 elements
    rows = list_to_range_rows(values)
    rows[1] = (rows[1][0], 9)
    edited = range_rows_to_list("Os.IsrTriggerMethodList", rows)
    assert len(edited) == 992
    assert edited[16:19] == [9, 9, 9]
    assert edited[:16] == values[:16] and edited[19:] == values[19:]


@pytest.mark.parametrize("rows, text", [
    ([("0-3", 1), ("5-7", 2)], "missing index 4"),
    ([("0-3", 1), ("3-5", 2)], "overlap"),
    ([("0-3", 1), ("0-3", 2)], "overlap"),          # the same range twice
    ([("x", 1)], "not an index range"),
])
def test_bad_range_rows_are_rejected(rows, text):
    with pytest.raises(ValueError) as err:
        range_rows_to_list("Os.L", rows)
    assert text in str(err.value)


# --- directory scan ---------------------------------------------------------------

def _plugin(root: Path, name: str, module: str, xdm: str, template: str = "") -> Path:
    plugin = root / name
    (plugin / "config").mkdir(parents=True)
    (plugin / "generate_PB").mkdir()
    (plugin / "config" / f"{module}.xdm").write_text(xdm, encoding="utf-8")
    if template:
        (plugin / "generate_PB" / f"{module}_Cfg.h").write_text(template, encoding="utf-8")
    return plugin


def test_scan_directory_finds_keys_of_every_plugin(tmp_path):
    _plugin(tmp_path, "Mcu_X", "Mcu", "ecu:get('Mcu.PllFreq')")
    _plugin(tmp_path, "Os_X", "Os", "<x/>", "[!\"ecu:list('OsResource.AvailableCores')\"!]")
    keys = collect_referenced_keys_in_dirs([tmp_path])
    assert keys == {"Mcu.PllFreq": {"Mcu"}, "OsResource.AvailableCores": {"Os"}}


def test_scan_directory_ignores_dynamic_keys_and_missing_dirs(tmp_path):
    _plugin(tmp_path, "Adc_X", "Adc", "ecu:get(concat('Adc.SyncGroup.', $u))")
    assert collect_referenced_keys_in_dirs([tmp_path, tmp_path / "missing"]) == {}


def test_directory_scan_agrees_with_project_scan(tmp_path):
    plugin = _plugin(tmp_path / "Def" / "plugins", "Mcu_X", "Mcu",
                     "ecu:get('Mcu.A')", "ecu:get('Mcu.B')")
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.module_defs = {"Mcu": plugin / "config" / "Mcu.xdm"}
    assert collect_referenced_keys(project) == collect_referenced_keys_in_dirs([tmp_path])


def test_library_other_chip_keys_excludes_the_edited_chip():
    db = ChipDatabase()
    db.register_chip(ChipDefinition(name="A", ecu_resources={"Port": {"OnlyA": 1}}))
    db.register_chip(ChipDefinition(name="B", ecu_resources={"Port": {"OnlyB": 1}}))
    assert library_other_chip_keys(db, "A") == {"port.onlyb": ["B"]}
    assert library_other_chip_keys(db, None) == {"port.onlya": ["A"], "port.onlyb": ["B"]}


# --- fallback derivation uses the chip's data ------------------------------------

def test_fallback_adc_resolution_comes_from_the_chip():
    from autosar_configurator.core.hardware.chip_database import AdcResourceDef

    chip = ChipDefinition(name="C", adc_resources=[
        AdcResourceDef(name="SARADC0", unit_id=0, channel_count=8, resolution_bits=10)])
    assert "Adc.MaxResolution: 10" in ChipDefinitionExporter().to_properties_string(chip)
    assert "Adc.MaxResolution: 12" in ChipDefinitionExporter().to_properties_string(
        ChipDefinition(name="D"))
