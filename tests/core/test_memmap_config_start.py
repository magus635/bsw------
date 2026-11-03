"""The model part of update-linker-generator-authority: start kind, offset, fixed address, size,
load region and limit alignment of an execution region, and the configuration's load regions."""
import json

import pytest

from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import config as cfg
from autosar_configurator.core.memmap.config import (
    AFTER,
    FIXED,
    OFFSET,
    ConfigError,
    ExecRegion,
    LoadRegion,
    MemoryMapConfig,
    config_dict,
    load_config,
    region_doubts,
    save_config,
)

WINDOWS = [MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
           MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True),
           MemoryRegionDef("DFLASH_NORMAL", 0x44000000, 0x80000, "flash", None, True)]


def _region(**kw):
    base = dict(name="R", memory="CPU0BTCM", window="CPU0BTCM", kind="data", order=1)
    base.update(kw)
    return ExecRegion(**base)


# --- defaults --------------------------------------------------------------------------

def test_the_new_fields_default_to_the_old_behaviour():
    region = _region()
    assert (region.start_mode, region.offset, region.address, region.size, region.load_region,
            region.limit_align) == (AFTER, 0, None, None, "", 64)


def test_a_region_written_without_the_new_fields_reads_back_as_before(tmp_path):
    path = tmp_path / "m.json"
    path.write_text(json.dumps({"schema": 1, "regions": [
        {"name": "R", "memory": "GMU", "window": "GMU_NORMAL", "kind": "data", "order": 1, "align": 64,
         "required": False, "origin": "user"}]}), encoding="utf-8")
    region = load_config(path).regions[0]
    assert (region.start_mode, region.offset, region.address, region.size, region.load_region,
            region.limit_align) == (AFTER, 0, None, None, "", 64)
    assert load_config(path).load_regions == []


def test_an_old_configuration_writes_no_new_keys():
    data = config_dict(MemoryMapConfig(regions=[_region()]))
    assert set(data["regions"][0]) == {"name", "memory", "window", "kind", "order", "align", "required", "origin"}
    assert "load_regions" not in data


# --- round trip ----------------------------------------------------------------------------

def test_every_new_field_survives_the_file(tmp_path):
    config = MemoryMapConfig(
        load_regions=[LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x300000), LoadRegion("DFLASH_CODE", "DFLASH_NORMAL", 0x10000)],
        regions=[_region(name="A", start_mode=OFFSET, offset=0x20000, size=0x8000, load_region="ROM_CODE"),
                 _region(name="B", start_mode=FIXED, address=0x30129000, size=0x1000, kind="stack", limit_align=8),
                 _region(name="C", window="DFLASH_NORMAL", load_region="DFLASH_CODE")])
    path = tmp_path / "m.json"
    save_config(config, path)
    again = load_config(path)
    assert again.load_regions == config.load_regions
    assert {r.name: r for r in again.regions} == {r.name: r for r in config.regions}


def test_the_load_regions_keep_their_order(tmp_path):
    config = MemoryMapConfig(load_regions=[LoadRegion("Z", "A", 1), LoadRegion("A", "B", 1)])
    path = tmp_path / "m.json"
    save_config(config, path)
    assert [l.name for l in load_config(path).load_regions] == ["Z", "A"]


def test_addresses_are_written_as_hex_text(tmp_path):
    path = tmp_path / "m.json"
    save_config(MemoryMapConfig(regions=[_region(start_mode=FIXED, address=0x30129000, size=0x1000)]), path)
    text = path.read_text(encoding="utf-8")
    assert '"address": "0x30129000"' in text and '"size": "0x1000"' in text


@pytest.mark.parametrize("entry, message", [
    ({"start_mode": "somewhere"}, "start_mode"),
    ({"start_mode": "offset", "offset": "-0x10"}, "offset"),
    ({"start_mode": "fixed"}, "address"),
    ({"size": "0"}, "size"),
    ({"size": "zz"}, "size"),
    ({"limit_align": 0}, "limit_align"),
])
def test_a_bad_field_in_the_file_is_reported(tmp_path, entry, message):
    region = {"name": "R", "memory": "M", "window": "W", "kind": "data", "order": 1, **entry}
    path = tmp_path / "m.json"
    path.write_text(json.dumps({"schema": 1, "regions": [region]}), encoding="utf-8")
    with pytest.raises(ConfigError, match=message):
        load_config(path)


def test_a_bad_load_region_in_the_file_is_reported(tmp_path):
    path = tmp_path / "m.json"
    path.write_text(json.dumps({"schema": 1, "load_regions": [{"name": "X"}]}), encoding="utf-8")
    with pytest.raises(ConfigError, match="window"):
        load_config(path)


# --- checks ----------------------------------------------------------------------------------

def test_set_the_start_validates_it():
    config = MemoryMapConfig(regions=[_region()])
    config.set_start("R", OFFSET, offset=0x100)
    assert (config.region("R").start_mode, config.region("R").offset) == (OFFSET, 0x100)
    config.set_start("R", FIXED, address=0x30100100)
    assert config.region("R").address == 0x30100100
    with pytest.raises(ConfigError, match="偏移"):
        config.set_start("R", OFFSET, offset=-1)
    with pytest.raises(ConfigError, match="地址"):
        config.set_start("R", FIXED)
    with pytest.raises(ConfigError, match="起点方式"):
        config.set_start("R", "nowhere")


def test_set_the_size():
    config = MemoryMapConfig(regions=[_region()])
    config.set_size("R", 0x2000)
    assert config.region("R").size == 0x2000
    config.set_size("R", None)
    assert config.region("R").size is None
    with pytest.raises(ConfigError, match="大小"):
        config.set_size("R", 0)


def test_a_region_names_an_existing_load_region():
    config = MemoryMapConfig(load_regions=[LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x300000)], regions=[_region()])
    config.set_load_region("R", "ROM_CODE")
    assert config.region("R").load_region == "ROM_CODE"
    with pytest.raises(ConfigError, match="加载区域"):
        config.set_load_region("R", "NONE")


def test_load_regions_are_added_renamed_and_removed():
    config = MemoryMapConfig(regions=[_region(load_region="")])
    config.add_load_region(LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x300000))
    config.add_load_region(LoadRegion("DFLASH_CODE", "DFLASH_NORMAL", 0x10000))
    config.set_load_region("R", "DFLASH_CODE")
    with pytest.raises(ConfigError, match="已存在"):
        config.add_load_region(LoadRegion("ROM_CODE", "X", 1))
    config.rename_load_region("DFLASH_CODE", "DF")
    assert config.region("R").load_region == "DF"                       # the region follows
    config.remove_load_region("DF")
    assert config.region("R").load_region == ""                         # back to the first
    assert [l.name for l in config.load_regions] == ["ROM_CODE"]


def test_a_load_region_needs_a_name_and_a_positive_size():
    config = MemoryMapConfig()
    for bad in (LoadRegion("", "W", 1), LoadRegion("1X", "W", 1), LoadRegion("A", "W", 0)):
        with pytest.raises(ConfigError):
            config.add_load_region(bad)


def test_a_fixed_address_outside_its_window_is_doubtful_not_wrong():
    config = MemoryMapConfig(regions=[_region(start_mode=FIXED, address=0x10000000)])
    assert region_doubts(config, WINDOWS) == ["区域 R 的固定地址 0x10000000 不在窗口 CPU0BTCM（0x30100000–0x30130000）内"]


def test_an_offset_past_the_window_end_is_doubtful():
    config = MemoryMapConfig(regions=[_region(start_mode=OFFSET, offset=0x40000)])
    assert region_doubts(config, WINDOWS) == ["区域 R 的偏移 0x40000 超出窗口 CPU0BTCM 的大小 0x30000"]


def test_a_size_beyond_the_window_is_doubtful():
    config = MemoryMapConfig(regions=[_region(size=0x40000)])
    assert region_doubts(config, WINDOWS) == ["区域 R 的大小 0x40000 超过窗口 CPU0BTCM 的大小 0x30000"]


def test_clean_regions_have_no_doubts():
    config = MemoryMapConfig(regions=[_region(start_mode=FIXED, address=0x30129000, size=0x1000),
                                      _region(name="Q", start_mode=OFFSET, offset=0x100)])
    assert region_doubts(config, WINDOWS) == []


def test_the_constants_are_the_three_kinds():
    assert cfg.START_MODES == (AFTER, OFFSET, FIXED)
    assert cfg.DEFAULT_LIMIT_ALIGN == 64
