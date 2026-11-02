"""The layout configuration: execution regions, rules, manual placements, and their text file."""
import json

import pytest

from autosar_configurator.core.memmap import config as cfg
from autosar_configurator.core.memmap.config import (
    ConfigError,
    ExecRegion,
    MemoryMapConfig,
    Rule,
    accepts,
    config_path,
    load_config,
    save_config,
)


def _config():
    return MemoryMapConfig(
        chip="THA6206_LFBGA292",
        regions=[
            ExecRegion("PRIVATE_DATA_CORE0", "CPU0BTCM", "CPU0BTCM", "data", 2, 64, required=True, origin="required"),
            ExecRegion("PRIVATE_BSS_CORE0", "CPU0BTCM", "CPU0BTCM", "bss", 3, 64, required=True, origin="required"),
            ExecRegion("MY_FAST_DATA", "GMU", "GMU_NORMAL", "data", 1, 64, origin="user"),
        ],
        rules=[
            Rule("核私有 BSS", {"kind": ["BSS"], "core": 0}, "PRIVATE_BSS_CORE0", origin="factory",
                 note="LinkerAdsPf.scat: *(.mcal_bss_*_core0)"),
            Rule("其余 BSS", {"kind": ["BSS"]}, "UNDEFINE_RAM_BSS", origin="user"),
        ],
        manual={".mcal_bss_asil_d_unspecified_core0": "UNDEFINE_RAM_BSS"},
    )


# --- what a region accepts ------------------------------------------------------------------

@pytest.mark.parametrize("kind, section, expected", [
    ("code", "TEXT", True), ("code", "RODATA", False), ("const", "RODATA", True), ("const", "DATA", False),
    ("data", "DATA", True), ("data", "BSS", False), ("bss", "BSS", True), ("bss", "DATA", False),
    ("noinit", "BSS", True), ("noinit", "DATA", False),
    ("stack", "BSS", False), ("stack", "DATA", False), ("stack", "TEXT", False),
    ("reserved", "DATA", False), ("reserved", "BSS", False),
])
def test_region_kind_decides_what_it_accepts(kind, section, expected):
    assert accepts(kind, section) is expected


def test_the_refusal_says_why():
    assert "data" in cfg.refusal("data", "BSS") and "BSS" in cfg.refusal("data", "BSS")
    assert "栈" in cfg.refusal("stack", "DATA")
    assert cfg.refusal("data", "DATA") == ""


def test_every_kind_is_known():
    assert set(cfg.KINDS) == {"code", "const", "data", "bss", "noinit", "stack", "reserved"}


# --- regions and lookup -------------------------------------------------------------------

def test_region_lookup_by_name():
    c = _config()
    assert c.region("PRIVATE_BSS_CORE0").kind == "bss" and c.region("NOPE") is None


def test_required_regions_cannot_be_removed():
    c = _config()
    with pytest.raises(ConfigError, match="必需"):
        c.remove_region("PRIVATE_DATA_CORE0")
    assert c.region("PRIVATE_DATA_CORE0") is not None


def test_required_regions_cannot_be_renamed():
    with pytest.raises(ConfigError, match="必需"):
        _config().rename_region("PRIVATE_DATA_CORE0", "OTHER")


def test_a_user_region_can_be_removed_and_renamed():
    c = _config()
    c.rename_region("MY_FAST_DATA", "FAST")
    assert c.region("FAST") is not None and c.region("MY_FAST_DATA") is None
    c.remove_region("FAST")
    assert c.region("FAST") is None


def test_rename_to_an_existing_name_is_refused():
    with pytest.raises(ConfigError, match="已存在"):
        _config().rename_region("MY_FAST_DATA", "PRIVATE_BSS_CORE0")


def test_removing_a_region_keeps_the_placements_that_pointed_at_it():
    c = _config()
    c.manual[".x"] = "MY_FAST_DATA"
    c.remove_region("MY_FAST_DATA")
    assert c.manual[".x"] == "MY_FAST_DATA"          # kept, now to be placed again; never dropped


def test_adding_a_region_with_a_taken_name_is_refused():
    with pytest.raises(ConfigError, match="已存在"):
        _config().add_region(ExecRegion("MY_FAST_DATA", "GMU", "GMU_NORMAL", "data", 9, 64))


def test_a_user_region_name_must_be_an_identifier():
    for bad in ("", "1X", "a b", "A$B", "A-B"):
        with pytest.raises(ConfigError, match="名称"):
            _config().add_region(ExecRegion(bad, "GMU", "GMU_NORMAL", "data", 9, 64))


def test_a_limit_name_is_refused_for_a_user_region():
    """<name>_LIMIT belongs to the generator: a user region of that name would clash with it."""
    with pytest.raises(ConfigError, match="_LIMIT"):
        _config().add_region(ExecRegion("X_LIMIT", "GMU", "GMU_NORMAL", "data", 9, 64))


def test_an_unknown_kind_is_refused():
    with pytest.raises(ConfigError, match="种类"):
        _config().add_region(ExecRegion("X", "GMU", "GMU_NORMAL", "weird", 9, 64))


# --- the file ---------------------------------------------------------------------------------

def test_round_trip(tmp_path):
    """Everything comes back; the regions by name, because the file orders them so, and the
    rules in their own order, which is their priority."""
    path = tmp_path / "memorymap.json"
    original = _config()
    save_config(original, path)
    loaded = load_config(path)
    assert sorted(loaded.regions, key=lambda r: r.name) == sorted(original.regions, key=lambda r: r.name)
    assert (loaded.chip, loaded.rules, loaded.manual, loaded.trimmed, loaded.options) == (
        original.chip, original.rules, original.manual, original.trimmed, original.options)


def test_the_text_is_ordered_by_name_so_versions_compare_cleanly(tmp_path):
    path = tmp_path / "memorymap.json"
    c = _config()
    save_config(c, path)
    first = path.read_text(encoding="utf-8")
    c.regions.reverse()
    save_config(c, path)
    assert path.read_text(encoding="utf-8") == first


def test_the_rule_order_is_kept_because_it_matters(tmp_path):
    path = tmp_path / "memorymap.json"
    save_config(_config(), path)
    assert [r.name for r in load_config(path).rules] == ["核私有 BSS", "其余 BSS"]


def test_the_file_carries_a_schema_version_and_the_chip(tmp_path):
    path = tmp_path / "memorymap.json"
    save_config(_config(), path)
    data = json.loads(path.read_text(encoding="utf-8"))
    assert data["schema"] == cfg.SCHEMA and data["chip"] == "THA6206_LFBGA292"


def test_the_text_is_stable_and_ends_with_a_newline(tmp_path):
    path = tmp_path / "memorymap.json"
    save_config(_config(), path)
    text = path.read_text(encoding="utf-8")
    assert text.endswith("\n") and "\r" not in text and '  "chip"' in text
    save_config(load_config(path), path)
    assert path.read_text(encoding="utf-8") == text


def test_a_missing_file_gives_an_empty_configuration(tmp_path):
    c = load_config(tmp_path / "none.json")
    assert c.regions == [] and c.rules == [] and c.manual == {} and c.chip == ""


def test_loading_writes_nothing(tmp_path):
    load_config(tmp_path / "sub" / "none.json")
    assert not (tmp_path / "sub").exists()


@pytest.mark.parametrize("text, message", [
    ("{not json", "不是有效的 JSON"),
    ("[]", "顶层必须是对象"),
    ('{"schema": 999}', "schema"),
    ('{"schema": 1, "regions": 5}', "regions"),
    ('{"schema": 1, "regions": [{"name": "A"}]}', "kind"),
    ('{"schema": 1, "rules": [{"name": "r"}]}', "target"),
    ('{"schema": 1, "manual": []}', "manual"),
])
def test_a_damaged_file_gives_a_clear_error(tmp_path, text, message):
    path = tmp_path / "memorymap.json"
    path.write_text(text, encoding="utf-8")
    with pytest.raises(ConfigError, match=message) as error:
        load_config(path)
    assert "memorymap.json" in str(error.value)


def test_save_is_atomic_when_it_fails(tmp_path, monkeypatch):
    path = tmp_path / "memorymap.json"
    save_config(_config(), path)
    before = path.read_text(encoding="utf-8")

    def fail(*a, **k):
        raise OSError("disk full")

    monkeypatch.setattr(cfg.os, "replace", fail)
    with pytest.raises(ConfigError, match="disk full"):
        save_config(MemoryMapConfig(chip="OTHER"), path)
    assert path.read_text(encoding="utf-8") == before
    assert not list(tmp_path.glob("*.tmp"))


def test_save_creates_the_directory(tmp_path):
    path = tmp_path / "a" / "b" / "memorymap.json"
    save_config(_config(), path)
    assert path.is_file()


# --- where it lives ---------------------------------------------------------------------------------

def test_the_path_is_in_the_integration_project(tmp_path):
    assert config_path(tmp_path) == tmp_path / "IntegrationProject" / "linkedFile" / "memorymap.json"


def test_the_directory_names_are_defined_once():
    assert cfg.INTEGRATION_DIR == "IntegrationProject" and cfg.LINKED_FILE_DIR == "linkedFile"
    assert cfg.CONFIG_FILE == "memorymap.json"
