"""Chip ECU resources: YAML section, range notation, properties import/export."""
from pathlib import Path

import pytest
import yaml

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter
from autosar_configurator.core.hardware.ecu_resource_data import (
    compress_ranges,
    expand_ranges,
    flatten_ecu_resources,
    parse_ecu_resources,
    should_compress,
)
from autosar_configurator.core.hardware.tresos_properties_parser import (
    TresosPropertiesParser,
)

FIXTURES = Path(__file__).resolve().parent.parent / "fixtures" / "ecu_resources"
OS_FILE = FIXTURES / "Os_Resource_THA6412.properties"
RES_FILE = FIXTURES / "CotexR52_THA6412_BGA516.properties"


def _load_yaml_text(tmp_path: Path, text: str) -> ChipDefinition:
    path = tmp_path / "chip.yaml"
    path.write_text(text, encoding="utf-8")
    chip = ChipDatabase()._load_chip_from_yaml(path)
    assert chip is not None
    return chip


def _roundtrip_yaml(chip: ChipDefinition, tmp_path: Path) -> ChipDefinition:
    exporter = ChipDefinitionExporter()
    path = tmp_path / "roundtrip.yaml"
    exporter.save_yaml(chip, path)
    return ChipDatabase()._load_chip_from_yaml(path)


def _import(paths) -> ChipDefinition:
    db = ChipDatabase()
    chip = ChipDefinition(name="THA6412_BGA516")
    db.import_ecu_resources_from_properties(chip, list(paths))
    return chip


# --- 1. YAML section ---------------------------------------------------------

def test_legacy_yaml_has_no_ecu_resources(tmp_path):
    chip = _load_yaml_text(tmp_path, "name: OLD\nfamily: THA6\n")
    assert chip.ecu_resources == {}
    assert chip.resource_version == ""
    assert "ecu_resources" not in ChipDefinitionExporter().to_yaml_dict(chip)


def test_yaml_section_scalar_list_and_dotted_keys_roundtrip(tmp_path):
    chip = _load_yaml_text(tmp_path, """
name: C1
resource_version: 1.2.0
ecu_resources:
  OsResource:
    NumOfCores: 4
    AvailableCores: [CORE0, CORE1, CORE2, CORE3]
    Flag: true
  Adc:
    SyncGroup.Master.SARADC0: [0, 1, 1, 1]
""")
    assert chip.resource_version == "1.2.0"
    assert flatten_ecu_resources(chip.ecu_resources) == {
        "OsResource.NumOfCores": 4,
        "OsResource.AvailableCores": ["CORE0", "CORE1", "CORE2", "CORE3"],
        "OsResource.Flag": True,
        "Adc.SyncGroup.Master.SARADC0": [0, 1, 1, 1],
    }
    again = _roundtrip_yaml(chip, tmp_path)
    assert again.ecu_resources == chip.ecu_resources
    assert again.resource_version == "1.2.0"


@pytest.mark.parametrize("value", ["{a: 1}", "[[1, 2], [3]]", "{bad: 1}"])
def test_unsupported_value_type_names_file_and_key(tmp_path, value):
    path = tmp_path / "bad.yaml"
    path.write_text(f"name: C\necu_resources:\n  Os:\n    Key: {value}\n", encoding="utf-8")
    with pytest.raises(ValueError) as err:
        ChipDatabase()._load_chip_from_yaml(path)
    assert "bad.yaml" in str(err.value)
    assert "Os.Key" in str(err.value)


def test_failed_chip_is_not_added_to_directory_database(tmp_path):
    (tmp_path / "bad.yaml").write_text(
        "name: BAD\necu_resources:\n  Os:\n    Key: {x: 1}\n", encoding="utf-8")
    (tmp_path / "good.yaml").write_text("name: GOOD\n", encoding="utf-8")
    db = ChipDatabase(tmp_path)
    assert db.list_chips() == ["GOOD"]


def test_module_name_must_not_contain_dot():
    with pytest.raises(ValueError):
        parse_ecu_resources({"Os.X": {"A": 1}})


# --- 1.5-1.7 range notation --------------------------------------------------

def test_range_form_equals_plain_list():
    assert expand_ranges("Os.L", {"0-1": 1, 2: 2, "3-4": 4}) == [1, 1, 2, 4, 4]


def test_gap_names_key_and_missing_index():
    with pytest.raises(ValueError) as err:
        expand_ranges("Os.IsrTriggerMethodList", {"0-3": 1, "5-7": 2})
    assert "Os.IsrTriggerMethodList" in str(err.value)
    assert "missing index 4" in str(err.value)


@pytest.mark.parametrize("mapping", [
    {"0-3": 1, "3-5": 2},        # overlap
    {"1-3": 1},                  # does not start at 0
    {"a-b": 1},                  # invalid key
    {"3-1": 1},                  # reversed
    {"0-3": [1]},                # non-scalar
])
def test_invalid_ranges_fail(mapping):
    with pytest.raises(ValueError):
        expand_ranges("Os.L", mapping)


def test_yaml_range_and_plain_list_load_identically(tmp_path):
    a = _load_yaml_text(tmp_path, "name: A\necu_resources:\n  Os:\n    L: {0-1: 1, 2: 2, 3-4: 4}\n")
    b = _load_yaml_text(tmp_path, "name: B\necu_resources:\n  Os:\n    L: [1, 1, 2, 4, 4]\n")
    assert a.ecu_resources == b.ecu_resources == {"Os": {"L": [1, 1, 2, 4, 4]}}


def test_compression_threshold():
    short = [1] * 8
    assert not should_compress(short)
    long_runs = [1] * 20
    assert should_compress(long_runs)
    assert compress_ranges(long_runs) == {"0-19": 1}
    no_gain = list(range(16))
    assert not should_compress(no_gain)
    # bool and int are different values even though True == 1
    assert compress_ranges([True, 1, 1]) == {0: True, "1-2": 1}


def test_long_list_is_written_compactly_and_roundtrips(tmp_path):
    values = [1] * 16 + [2] * 3 + [4] * 3 + [2] * 970
    chip = ChipDefinition(name="C", ecu_resources={"Os": {"IsrTriggerMethodList": values}})
    text = ChipDefinitionExporter().to_yaml_string(chip)
    block = yaml.safe_load(text)["ecu_resources"]["Os"]["IsrTriggerMethodList"]
    assert isinstance(block, dict) and len(block) == 4
    again = _roundtrip_yaml(chip, tmp_path)
    assert again.ecu_resources["Os"]["IsrTriggerMethodList"] == values


# --- 2. properties import ----------------------------------------------------

def test_import_os_resource_file():
    chip = _import([OS_FILE])
    flat = flatten_ecu_resources(chip.ecu_resources)
    assert flat["OsResource.NumOfCores"] == 4
    assert len(flat["OsResource.AvailableCores"]) == 4
    assert len(flat["Os.IsrTriggerMethodList"]) == 992
    assert flat["Os.IocPrimitiveDataTypeNum"] == 23
    assert len(flat["Os.IocPrimitiveDataType"]) == 23


def test_import_keeps_every_key_of_both_vendor_files():
    for path in (OS_FILE, RES_FILE):
        expected = TresosPropertiesParser().parse_file(path).properties
        chip = _import([path])
        assert flatten_ecu_resources(chip.ecu_resources) == {
            k: v for k, v in expected.items() if '.' in k}


def test_import_keeps_unmodelled_keys():
    flat = flatten_ecu_resources(_import([RES_FILE]).ecu_resources)
    assert flat["Adc.SyncGroup.Master.SARADC0"] == [0, 1, 1, 1]
    assert "Resource.Clsuter.C0.Cores" in flat   # original spelling kept


def test_import_later_file_replaces_earlier(tmp_path, caplog):
    a = tmp_path / "a.properties"
    b = tmp_path / "b.properties"
    a.write_text("Os.Key: 1\nOs.Only: x\n", encoding="utf-8")
    b.write_text("Os.Key: 2\n", encoding="utf-8")
    with caplog.at_level("INFO"):
        chip = _import([a, b])
    flat = flatten_ecu_resources(chip.ecu_resources)
    assert flat == {"Os.Key": 2, "Os.Only": "x"}
    assert any("Os.Key" in r.message for r in caplog.records)


def test_import_skips_key_without_module(tmp_path, caplog):
    f = tmp_path / "x.properties"
    f.write_text("NoModule: 1\nOs.Key: 2\n", encoding="utf-8")
    with caplog.at_level("WARNING"):
        chip = _import([f])
    assert flatten_ecu_resources(chip.ecu_resources) == {"Os.Key": 2}
    assert any("NoModule" in r.message for r in caplog.records)


# --- 3. properties export ----------------------------------------------------

def _reimport_exported(chip: ChipDefinition, tmp_path: Path) -> ChipDefinition:
    out_dir = tmp_path / "resource"
    paths = ChipDefinitionExporter().save_module_properties(chip, out_dir)
    return _import(paths)


@pytest.mark.parametrize("source", [OS_FILE, RES_FILE])
def test_properties_roundtrip(source, tmp_path):
    chip = _import([source])
    again = _reimport_exported(chip, tmp_path)
    assert flatten_ecu_resources(again.ecu_resources) == flatten_ecu_resources(chip.ecu_resources)


def test_properties_and_yaml_roundtrip_together(tmp_path):
    chip = _import([OS_FILE, RES_FILE])
    chip = _roundtrip_yaml(chip, tmp_path)
    again = _reimport_exported(chip, tmp_path)
    assert flatten_ecu_resources(again.ecu_resources) == flatten_ecu_resources(chip.ecu_resources)


def test_export_one_file_per_module():
    chip = _import([OS_FILE, RES_FILE])
    files = ChipDefinitionExporter().module_properties_strings(chip)
    assert set(files) == {f"{m}_THA6412_BGA516.properties" for m in chip.ecu_resources}
    assert all(k.split('.')[0] in name for name, text in files.items()
               for k in [line.split(':')[0] for line in text.splitlines()
                         if line and not line.startswith('#') and not line.startswith(' ')])


def test_export_is_deterministic():
    chip = _import([OS_FILE, RES_FILE])
    exporter = ChipDefinitionExporter()
    assert exporter.module_properties_strings(chip) == exporter.module_properties_strings(chip)
    assert exporter.to_yaml_string(chip) == exporter.to_yaml_string(chip)


def test_export_adds_no_invented_values():
    chip = ChipDefinition(name="C", ecu_resources={"Os": {"A": 1}})
    text = ChipDefinitionExporter().to_properties_string(chip)
    assert "Os.A: 1" in text
    assert "Can.MaxHwObjects" not in text
    assert "Resource.NumOfCores" not in text


def test_edge_values_roundtrip(tmp_path):
    chip = ChipDefinition(name="C", ecu_resources={"M": {
        "Single": ["only"], "Empty": [], "Nothing": None, "Flag": False, "Ratio": 1.5,
        "Mixed": ["CORE0", 1, True], "Literal": "(0U)",
    }})
    again = _reimport_exported(chip, tmp_path)
    assert again.ecu_resources == chip.ecu_resources


def test_export_without_ecu_resources_keeps_legacy_output():
    chip = ChipDefinition(name="OLD", family="THA6", package="BGA1")
    text = ChipDefinitionExporter().to_properties_string(chip)
    assert "Resource.NumOfCores: 2" in text
