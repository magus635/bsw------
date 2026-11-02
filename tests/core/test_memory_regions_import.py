"""Memory regions imported from the comment table at the head of an ADS scatter file.

The texts are the forms found in the vendor script LinkerAdsPf.scat (``start end - length``)
and in the Os template scatter.scat (``start start + length``), written here as plain
strings so that the tests do not depend on the doc directory."""
import pytest

from autosar_configurator.core.hardware.memory_regions import LOCAL, MemoryRegionDef
from autosar_configurator.core.hardware.memory_regions_import import (
    ImportResult,
    merge_import,
    parse_comment_table,
    parse_size,
)

VENDOR = """\
#! armclang --target=arm-arm-none-eabi -march=armv8-a -E -x c

;/******* Memory ************** Start Address ****************************    End Address *******************************
;        CPUXATCM                0x00000000                0x00000000 - 0x00010000 (64K)          local access CPUXATCM address
;        CPUXPFLASH0             0x08000000                0x08000000 - 0x08300000 (3MB)          local access PF0 address
;
;        CPU0BTCM                0x30100000                0x30100000 - 0x30130000 (192K)         AXI access CPU0BTCM address   set  it as internel address for CPU0 in startup code.
;        CPU1ATCM                0x30400000                0x30400000 - 0x30410000 (64K)          AXI access CPU1ATCM address
;        GMU_NORMAL              0x10000000                0x10000000 - 0x10040000 (256K)         AXI access global memory address(Cacheable)
;        LMU1_NORMAL             0x10054000                0x10054000 - 0x10058000 (16k)          AXI Cacheable
;        PFLASH0_NORMAL          0x40400000                0x40400000 - 0x40700000 (3MB)          AXI access PF0 address(Cacheable)
;        DFLASH_NORMAL           0x44000000                0x44000000 - 0x44080000 (512KB)        AXI access DF address(Cacheable)
;        GMU_DEVICE              0x82000000                0x82000000 - 0x82040000 (256K)         AXI access global memory address(Non-Cacheable)
;        PFLASH0_DEVICE          0x90400000                0x90400000 - 0x90700000 (3MB)          AXI access PF0 address(Non-Cacheable)
;        LMU1_DEVICE             0xB0020000                0xB0020000 - 0xB0024000 (16KB)         AXI access LMU address(Non-Cacheable)
;
;**********************************************************************************************************************/

#define STARTUP_ADDRESS                0x00000000
"""

OS_TEMPLATE = """\
;/******* Memory ************** Start Address ****************************    End Address *******************************
;        CPUXATCM                0x00000000                0x00000000 + 64K          local access CPUXATCM address
;        CPUXBTCM                0x00100000                0x00100000 + 192K         local access CPUXBTCM address
;        CPU0ATCM                0x30000000                0x30000000 + 64K          AXI access CPU0ATCM address
;        GMU_NORMAL              0x10000000                0x10000000 + 256K         AXI access global memory address(Cacheable)
;        PFLASH0_NORMAL          0x40400000                0x40400000 + 3MB          AXI access PF0 address(Cacheable)
;        DFLASH_DEVICE           0x94000000                0x94000000 + 512KB        AXI access DF address(Non-Cacheable)
"""


def _by_name(result: ImportResult):
    return {r.name: r for r in result.regions}


# --- sizes ------------------------------------------------------------------------------

@pytest.mark.parametrize("text, expected", [
    ("64K", 0x10000), ("16k", 0x4000), ("16KB", 0x4000), ("3MB", 0x300000), ("512KB", 0x80000),
    ("1M", 0x100000), ("0x1000", 0x1000), ("4096", 4096), ("2GB", 0x80000000),
])
def test_sizes(text, expected):
    assert parse_size(text) == expected


@pytest.mark.parametrize("text", ["", "K", "3TB", "x", "-4K"])
def test_bad_sizes(text):
    assert parse_size(text) is None


# --- the two forms of the table -------------------------------------------------------------

def test_vendor_form_reads_start_and_the_size_from_the_end_address():
    regions = _by_name(parse_comment_table(VENDOR, "LinkerAdsPf.scat"))
    btcm = regions["CPU0BTCM"]
    assert (btcm.start, btcm.size) == (0x30100000, 0x30000)
    assert regions["LMU1_NORMAL"].size == 0x4000 and regions["DFLASH_NORMAL"].size == 0x80000


def test_the_size_comes_from_the_addresses_when_they_disagree_with_the_bracket():
    text = ";        X   0x1000   0x1000 - 0x3000 (4K)   AXI access X address\n"
    region = _by_name(parse_comment_table(text, "f.scat"))["X"]
    assert region.size == 0x2000                 # the addresses are the table's own arithmetic


def test_offset_form():
    regions = _by_name(parse_comment_table(OS_TEMPLATE, "scatter.scat"))
    assert (regions["CPUXATCM"].start, regions["CPUXATCM"].size) == (0x0, 0x10000)
    assert regions["CPUXBTCM"].size == 0x30000 and regions["GMU_NORMAL"].size == 0x40000


def test_only_comment_lines_inside_the_table_are_read():
    result = parse_comment_table(VENDOR, "LinkerAdsPf.scat")
    assert "STARTUP_ADDRESS" not in {r.name for r in result.regions}
    assert len(result.regions) == 11


def test_a_line_that_is_not_a_region_is_left_out():
    text = (";  Copyright (c) Tongxin 0x1234\n"
            ";        X                0x1000     0x1000 + 4K      local access X address\n")
    assert [r.name for r in parse_comment_table(text, "f.scat").regions] == ["X"]


def test_no_table_gives_nothing():
    assert parse_comment_table("LR 0x0 0x100 { }\n", "f.scat").regions == []


# --- what the text says, and what it does not ------------------------------------------------

def test_cacheable_and_non_cacheable_are_read_from_the_text():
    regions = _by_name(parse_comment_table(VENDOR, "f.scat"))
    assert regions["GMU_NORMAL"].cacheable is True and regions["GMU_DEVICE"].cacheable is False
    assert regions["LMU1_NORMAL"].cacheable is True        # "AXI Cacheable"
    assert regions["LMU1_DEVICE"].cacheable is False and regions["DFLASH_DEVICE" if False else "PFLASH0_DEVICE"].cacheable is False


def test_the_core_is_read_from_the_name_and_the_text():
    regions = _by_name(parse_comment_table(VENDOR, "f.scat"))
    assert regions["CPU0BTCM"].core == 0 and regions["CPU1ATCM"].core == 1
    assert regions["CPUXATCM"].core == LOCAL and regions["CPUXPFLASH0"].core == LOCAL
    assert regions["GMU_NORMAL"].core is None


def test_flash_and_ram_from_the_name_and_the_text():
    regions = _by_name(parse_comment_table(VENDOR, "f.scat"))
    assert regions["PFLASH0_NORMAL"].type == "flash" and regions["DFLASH_DEVICE" if False else "DFLASH_NORMAL"].type == "flash"
    assert regions["CPUXPFLASH0"].type == "flash"
    assert regions["GMU_NORMAL"].type == "ram" and regions["CPU0BTCM"].type == "ram"


def test_what_the_text_does_not_say_is_not_guessed_and_is_reported():
    """CPUXPFLASH0 says "local access PF0 address": nothing about the cache."""
    result = parse_comment_table(VENDOR, "f.scat")
    flash = _by_name(result)["CPUXPFLASH0"]
    assert flash.cacheable is True                    # the loader's own default, not read from the text
    assert "CPUXPFLASH0" in result.unstated_cache
    assert "GMU_NORMAL" not in result.unstated_cache


def test_every_imported_entry_carries_its_source():
    for region in parse_comment_table(VENDOR, "LinkerAdsPf.scat").regions:
        assert region.source == "LinkerAdsPf.scat 注释表"


def test_the_source_is_the_file_name_only():
    region = parse_comment_table(VENDOR, "D:/x/LinkFiles/Ads/LinkerAdsPf.scat").regions[0]
    assert region.source == "LinkerAdsPf.scat 注释表"


def test_names_are_taken_as_written():
    assert [r.name for r in parse_comment_table(VENDOR, "f.scat").regions][:2] == ["CPUXATCM", "CPUXPFLASH0"]


# --- merging ------------------------------------------------------------------------------

def _existing():
    return [MemoryRegionDef("CPU0BTCM", 0x30100000, 0x20000, "ram", 0, False)]


def test_merge_adds_the_new_and_skips_the_existing():
    merged, report = merge_import(_existing(), parse_comment_table(VENDOR, "f.scat"))
    assert report.skipped == ["CPU0BTCM"]
    assert "CPU0BTCM" not in report.added and len(report.added) == 10
    assert len(merged) == 11


def test_an_existing_entry_is_kept_with_its_own_values():
    merged, _ = merge_import(_existing(), parse_comment_table(VENDOR, "f.scat"))
    kept = next(r for r in merged if r.name == "CPU0BTCM")
    assert kept.size == 0x20000                       # not 0x30000 from the file


def test_merge_keeps_the_order_existing_first():
    merged, report = merge_import(_existing(), parse_comment_table(VENDOR, "f.scat"))
    assert merged[0].name == "CPU0BTCM" and [r.name for r in merged[1:]] == report.added


def test_merge_does_not_change_its_inputs():
    existing = _existing()
    parsed = parse_comment_table(VENDOR, "f.scat")
    before = (list(existing), list(parsed.regions))
    merge_import(existing, parsed)
    assert (existing, parsed.regions) == before


def test_merge_into_nothing_adds_everything():
    merged, report = merge_import([], parse_comment_table(OS_TEMPLATE, "scatter.scat"))
    assert report.skipped == [] and len(merged) == 6


def test_names_repeated_inside_the_file_are_added_once_and_reported():
    text = (";        X   0x1000   0x1000 + 4K   local access X address\n"
            ";        X   0x2000   0x2000 + 4K   local access X address\n")
    merged, report = merge_import([], parse_comment_table(text, "f.scat"))
    assert len(merged) == 1 and merged[0].start == 0x1000 and report.skipped == ["X"]


def test_the_unconfirmed_note_names_the_fields_the_text_did_not_state():
    result = parse_comment_table(VENDOR, "LinkerAdsPf.scat")
    note = result.unconfirmed_note()
    assert "LinkerAdsPf.scat" in note and "CPUXPFLASH0" in note
