"""The THA6206 factory rules, run against section names from the vendor's own linker script.

The section names below are the ones the vendor script selects (read from LinkerAdsPf.scat); the
expected region is the execution region that script puts them in.  The rules are the initial
ones and open to change, so a failure here means "adjust the rule", but it is the closest check
available without running the vendor files through the tool."""
import pytest

from autosar_configurator.core.memmap import factory as fy
from autosar_configurator.core.memmap import rules as rl
from autosar_configurator.core.memmap.check import SectionRow, is_non_cacheable, section_core
from autosar_configurator.core.memmap.config import MemoryMapConfig, load_config, save_config
from autosar_configurator.core.memmap.symbols import COPY, BASE, CLEAR, STACK, RegionNeed, Reference


def _row(output, kind):
    """A row as the scan would build it for the vendor's output section ``output``."""
    return SectionRow(output=output, kind=kind, names=(), modules=("MCAL",), core=section_core(output),
                      non_cacheable=is_non_cacheable(output), uses=())


def _config(cores=2):
    config = MemoryMapConfig()
    factory = fy.load_factory("THA6206_LFBGA292")
    config.regions = fy.factory_regions(factory)
    config.rules = list(factory.rules)
    return config


# section, kind, the region LinkerAdsPf.scat puts it in
VENDOR = [
    (".mcal_bss_asil_d_unspecified", "BSS", "UNDEFINE_RAM_BSS"),
    (".mcal_bss_asil_d_bool", "BSS", "UNDEFINE_RAM_BSS"),
    (".mcal_data_asil_d_32", "DATA", "UNDEFINE_RAM_DATA"),
    (".mcal_no_init_asil_d_unspecified", "BSS", "UNCLEAR_RAM_BSS"),
    (".mcal_bss_asil_d_unspecified_core0", "BSS", "PRIVATE_BSS_CORE0"),
    (".mcal_bss_asil_d_8_core1", "BSS", "PRIVATE_BSS_CORE1"),
    (".mcal_data_asil_d_16_core0", "DATA", "PRIVATE_DATA_CORE0"),
    (".mcal_data_asil_d_unspecified_core1", "DATA", "PRIVATE_DATA_CORE1"),
    (".mcal_no_init_asil_d_32_core0", "BSS", "PRIVATE_NO_INIT_CORE0"),
    (".mcal_no_init_asil_d_unspecified_core1", "BSS", "PRIVATE_NO_INIT_CORE1"),
    (".mcal_text_asil_d_core0", "TEXT", "PRIVATE_CODE_CORE0"),
    (".mcal_text_fast_asil_d_core1", "TEXT", "PRIVATE_CODE_CORE1"),
    (".mcal_text_asil_d", "TEXT", "EX_CODE"),
    (".mcal_const_asil_d_32", "RODATA", "EX_CONST_DATA"),
    (".mcal_const_cfg_asil_d_unspecified", "RODATA", "EX_CONST_DATA"),
    (".mcal_bss_asil_d_unspecified_lmu1", "BSS", "LMU1_CACHED_BSS"),
    (".mcal_data_asil_d_32_lmu2", "DATA", "LMU2_CACHED_DATA"),
    (".mcal_bss_asil_d_8_lmu3_uncached", "BSS", "LMU3_UNCACHED_BSS"),
    (".mcal_data_asil_d_unspecified_lmu1_uncached", "DATA", "LMU1_UNCACHED_DATA"),
    (".mcal_bss_asil_d_unspecified_uncached", "BSS", "GLOBAL_UNCACHED_BSS"),
    (".mcal_data_asil_d_16_uncached", "DATA", "GLOBAL_UNCACHED_DATA"),
    (".mcal_no_init_asil_d_unspecified_uncached", "BSS", "GLOBAL_UNCACHED_NOINIT"),
]


@pytest.mark.parametrize("section, kind, expected", VENDOR)
def test_the_vendor_sections_land_where_the_vendor_script_puts_them(section, kind, expected):
    placed = rl.place(_config(), _row(section, kind))
    assert (placed.status, placed.target) == (rl.BY_RULE, expected), placed


def test_an_uncached_core_no_init_section_is_in_the_vendor_scripts_core_region():
    """LinkerAdsPf.scat puts .mcal_no_init_asil_d_*_uncached_core0 in PRIVATE_NO_INIT_CORE0."""
    placed = rl.place(_config(), _row(".mcal_no_init_asil_d_8_uncached_core0", "BSS"))
    assert placed.target == "PRIVATE_NO_INIT_CORE0"


def test_every_factory_rule_points_at_a_region_of_the_factory_layout_that_takes_its_kind():
    config = _config()
    info = rl.rule_info(config, [])
    assert [(name, i.invalid) for name, i in info.items() if i.invalid] == []


def test_every_factory_rule_is_used_by_some_vendor_section():
    config = _config()
    rows = [_row(s, k) for s, k, _ in VENDOR] + [_row(".mcal_no_init_asil_d_8_uncached_core0", "BSS"),
                                                   _row(".mcal_bss_asil_d_unspecified_lmu2", "BSS"),
                                                   _row(".mcal_bss_asil_d_unspecified_lmu3", "BSS"),
                                                   _row(".mcal_data_asil_d_unspecified_lmu3", "DATA"),
                                                   _row(".mcal_bss_asil_d_unspecified_lmu2_uncached", "BSS"),
                                                   _row(".mcal_data_asil_d_unspecified_lmu2_uncached", "DATA"),
                                                   _row(".mcal_bss_asil_d_unspecified_lmu3_uncached", "BSS"),
                                                   _row(".mcal_data_asil_d_unspecified_lmu3_uncached", "DATA"),
                                                   _row(".mcal_bss_asil_d_unspecified_lmu1_uncached", "BSS"),
                                                   _row(".mcal_data_asil_d_unspecified_lmu1", "DATA"),
                                                   _row(".mcal_data_asil_d_unspecified_lmu2", "DATA"),
                                                   _row(".mcal_data_asil_d_unspecified_core0", "DATA"),
                                                   _row(".mcal_bss_asil_d_unspecified_core1", "BSS"),
                                                   _row(".mcal_data_asil_d_unspecified_core0", "DATA"),
                                                   _row(".mcal_text_asil_d_core1", "TEXT")]
    unused = [n for n, i in rl.rule_info(config, rows).items() if i.matched == 0 and not i.shadowed]
    assert unused == [], unused


# --- the data -----------------------------------------------------------------------------------

def test_the_factory_data_loads_with_its_notes():
    data = fy.load_factory("THA6206_LFBGA292")
    assert data is not None and data.version == 2           # 2: corrected and completed (update-linker-generator-authority)
    assert all(r.origin == "factory" and r.note for r in data.rules)
    assert all(e.get("note") for e in data.layout)
    assert all(e.get("note") for e in data.load_regions)


# --- the corrections and additions of update-linker-generator-authority -------------------

def _layout():
    return {e["name"]: e for e in fy.load_factory("THA6206_LFBGA292").layout}


def test_the_vector_table_is_at_address_zero_in_the_local_atcm():
    region = next(r for r in fy.factory_regions(fy.load_factory("THA6206_LFBGA292")) if r.name == "INT_VECTOR_TABLE")
    assert (region.window, region.order, region.size) == ("CPUXATCM", 1, 0x2080)


def test_the_user_stacks_start_at_a_fixed_address_and_the_others_follow():
    regions = {r.name: r for r in fy.factory_regions(fy.load_factory("THA6206_LFBGA292"))}
    for core, base in ((0, 0x30129000), (1, 0x30529000)):
        user = regions[f"CORE{core}_USER_STACK"]
        assert (user.start_mode, user.address, user.size) == ("fixed", base, 0x1000)
        assert (regions[f"CORE{core}_IRQ_STACK"].start_mode, regions[f"CORE{core}_IRQ_STACK"].size) == ("after", 0x1000)


def test_undefine_ram_data_starts_at_an_offset_in_gmu_normal():
    region = next(r for r in fy.factory_regions(fy.load_factory("THA6206_LFBGA292")) if r.name == "UNDEFINE_RAM_DATA")
    assert (region.window, region.start_mode, region.offset) == ("GMU_NORMAL", "offset", 0x20000)


def test_the_regions_that_were_missing_are_there():
    assert {"CODE_CLONE", "DATA_CLONE", "BSS_CLONE", "RAM_CODE", "EX_CODE_CORE1",
            "EX_CONST_DATA_CORE1", "DFLASH_DATA"} <= set(_layout())


def test_dflash_data_is_in_its_own_load_region():
    data = fy.load_factory("THA6206_LFBGA292")
    assert [l.name for l in fy.factory_load_regions(data)] == ["ROM_CODE", "DFLASH_CODE"]
    assert next(r for r in fy.factory_regions(data) if r.name == "DFLASH_DATA").load_region == "DFLASH_CODE"


def test_the_fixed_addresses_and_offsets_lie_in_their_windows():
    from autosar_configurator.core.hardware.chip_database import ChipDatabase, default_chips_dir
    from autosar_configurator.core.memmap.config import MemoryMapConfig, region_doubts
    chip = ChipDatabase(default_chips_dir()).get_chip("THA6206_LFBGA292")
    config = MemoryMapConfig(regions=fy.factory_regions(fy.load_factory("THA6206_LFBGA292")))
    assert region_doubts(config, chip.memory_regions) == []


def test_the_first_preparation_brings_the_load_regions_and_keeps_them_after():
    config = MemoryMapConfig()
    fy.prepare(config, "THA6206_LFBGA292", [], cores=2)
    assert [l.name for l in config.load_regions] == ["ROM_CODE", "DFLASH_CODE"]
    config.remove_load_region("DFLASH_CODE")
    fy.prepare(config, "THA6206_LFBGA292", [], cores=2)
    assert [l.name for l in config.load_regions] == ["ROM_CODE"]            # the project's own now


def test_the_factory_layout_has_the_regions_startup_refers_to():
    names = {e["name"] for e in fy.load_factory("THA6206_LFBGA292").layout}
    assert {"UNDEFINE_RAM_DATA", "UNDEFINE_RAM_BSS", "PRIVATE_DATA_CORE0", "PRIVATE_BSS_CORE0",
            "PRIVATE_CODE_CORE1", "CORE0_USER_STACK", "CORE1_FIQ_STACK", "UNCLEAR_RAM_BSS",
            "GLOBAL_UNCACHED_DATA", "LMU2_CACHED_DATA", "EX_CODE"} <= names


def test_the_factory_layout_has_no_regions_of_cores_the_chip_lacks():
    names = {e["name"] for e in fy.load_factory("THA6206_LFBGA292").layout}
    assert not any("CORE2" in n or "CORE3" in n for n in names)


def test_the_factory_layout_names_a_window_the_chip_has():
    from autosar_configurator.core.hardware.chip_database import ChipDatabase, default_chips_dir
    chip = ChipDatabase(default_chips_dir()).get_chip("THA6206_LFBGA292")
    windows = {r.name for r in chip.memory_regions}
    for entry in fy.load_factory("THA6206_LFBGA292").layout:
        assert entry["window"] in windows, entry["name"]


def test_a_chip_without_factory_data_has_none():
    assert fy.load_factory("THA6412_BGA516") is None and fy.load_factory("") is None


def test_the_data_of_another_chip_is_refused(tmp_path):
    (tmp_path / "X_default.json").write_text('{"chip": "Y", "rules": []}', encoding="utf-8")
    with pytest.raises(Exception, match="芯片不是"):
        fy.load_factory("X", tmp_path)


def test_a_damaged_factory_file_is_reported(tmp_path):
    (tmp_path / "X_default.json").write_text("{nope", encoding="utf-8")
    with pytest.raises(Exception, match="无法读取"):
        fy.load_factory("X", tmp_path)


# --- preparing a project -----------------------------------------------------------------------------

def _need(name, uses):
    return RegionNeed(name, list(uses), [Reference(name, tuple(uses), "startup.c", 1, "X")])


def test_the_first_preparation_copies_the_rules_and_adds_the_regions():
    config = MemoryMapConfig()
    needs = [_need("PRIVATE_DATA_CORE0", [COPY]), _need("PRIVATE_DATA_CORE2", [COPY]),
             _need("CORE0_USER_STACK", [BASE])]
    prepared = fy.prepare(config, "THA6206_LFBGA292", needs, cores=2)
    assert prepared.rules_installed and len(config.rules) == 28
    assert config.region("PRIVATE_DATA_CORE0").window == "CPU0BTCM"
    assert config.region("CORE0_USER_STACK").kind == "stack"
    assert config.trimmed == ["PRIVATE_DATA_CORE2"] and config.region("PRIVATE_DATA_CORE2") is None
    assert config.chip == "THA6206_LFBGA292"


def test_a_second_preparation_keeps_the_users_changes():
    config = MemoryMapConfig()
    fy.prepare(config, "THA6206_LFBGA292", [_need("PRIVATE_DATA_CORE0", [COPY])], cores=2)
    rl.change_rule(config, "代码", target="PRIVATE_CODE_CORE0")
    rl.add_rule(config, rl_rule("mine"))
    prepared = fy.prepare(config, "THA6206_LFBGA292", [_need("PRIVATE_DATA_CORE0", [COPY])], cores=2)
    assert not prepared.rules_installed
    assert next(r for r in config.rules if r.name == "代码").target == "PRIVATE_CODE_CORE0"
    assert any(r.name == "mine" for r in config.rules)


def rl_rule(name):
    from autosar_configurator.core.memmap.config import Rule
    return Rule(name, {}, "UNDEFINE_RAM_BSS")


def test_a_chip_without_factory_data_gets_regions_from_the_code_and_no_rules():
    config = MemoryMapConfig()
    prepared = fy.prepare(config, "THA6412_BGA516", [_need("UNDEFINE_RAM_DATA", [COPY])], cores=4)
    assert prepared.factory is None and config.rules == [] and config.region("UNDEFINE_RAM_DATA") is not None
    assert any("没有出厂规则" in n for n in prepared.notes())


def test_without_code_the_factory_layout_stands_in_and_the_notes_say_so():
    config = MemoryMapConfig()
    prepared = fy.prepare(config, "THA6206_LFBGA292", [], cores=2)
    assert config.region("PRIVATE_BSS_CORE1") is not None and config.region("CORE1_FIQ_STACK") is not None
    assert any("未经代码核对" in n for n in prepared.notes())


def test_the_prepared_configuration_survives_the_file(tmp_path):
    config = MemoryMapConfig()
    fy.prepare(config, "THA6206_LFBGA292", [], cores=2)
    path = tmp_path / "memorymap.json"
    save_config(config, path)
    again = load_config(path)
    assert [r.name for r in again.rules] == [r.name for r in config.rules]
    assert sorted(r.name for r in again.regions) == sorted(r.name for r in config.regions)
