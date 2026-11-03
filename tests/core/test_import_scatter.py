"""Importing a layout from an ADS scatter file (update-linker-generator-authority, task 3).

Synthetic scatter texts only; the vendor file in doc/ is never read here."""
import copy

import pytest

from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap.config import (
    AFTER,
    FIXED,
    KINDS,
    OFFSET,
    ExecRegion,
    LoadRegion,
    MemoryMapConfig,
    Rule,
    config_dict,
)
from autosar_configurator.core.memmap.import_scatter import (
    IMPORTED,
    apply_import,
    infer_kind,
    preview_import,
)
from autosar_configurator.core.memmap.scatter import Selector

CHIP = [
    MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", "local", False),
    MemoryRegionDef("CPUXPFLASH0", 0x08000000, 0x300000, "flash", "local", True, memory="PFLASH0"),
    MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True, memory="GMU", window="normal"),
    MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
    MemoryRegionDef("DFLASH_NORMAL", 0x44000000, 0x80000, "flash", None, True, memory="DFLASH"),
    MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False, memory="GMU", window="device"),
]

DEFINES = """\
#define STARTUP_ADDRESS        0x00000000
#define CPUXPFLASH0_ADDRESS    0x08000000
#define GMU_NORMAL_ADDRESS     0x10000000
#define GMU_DEVICE_ADDRESS     0x82000000
#define CPU0BTCM_ADDRESS       0x30100000
#define CPU0_STACK_ADDRESS     0x30129000
#define DFLASH_ADDRESS         0x44000000
"""


def _scat(body: str, load: str = "ROM_CODE CPUXPFLASH0_ADDRESS 0x300000") -> str:
    return DEFINES + f"\n{load}\n{{\n{body}\n}}\n"


def _preview(body: str, config=None, **kw):
    return preview_import(config or MemoryMapConfig(), _scat(body, **kw), "x.scat", CHIP)


def _region(preview, name) -> ExecRegion:
    found = [r for r in preview.regions if r.name == name]
    assert found, f"{name} not in {[r.name for r in preview.regions]}"
    return found[0]


def _reasons(preview):
    return [n.text() for n in preview.not_imported]


# --- window and start ---------------------------------------------------------------------

def test_window_and_memory_from_the_address():
    p = _preview("D GMU_DEVICE_ADDRESS 0x1000 { *(.d_data) }")
    r = _region(p, "D")
    assert (r.window, r.memory, r.origin) == ("GMU_DEVICE", "GMU", IMPORTED)


def test_a_define_at_a_window_base_starting_the_window_is_after():
    r = _region(_preview("A GMU_NORMAL_ADDRESS 0x1000 { *(.a_data) }"), "A")
    assert (r.start_mode, r.offset, r.address) == (AFTER, 0, None)


def test_the_three_start_kinds():
    p = _preview("""
    A GMU_NORMAL_ADDRESS ALIGN 64 0x1000 { *(.a_data) }
    B AlignExpr(ImageLimit(A), 64) ALIGN 64 0x1000 { *(.b_data) }
    C GMU_NORMAL_ADDRESS+0x20000 ALIGN 64 0x1000 { *(.c_data) }
    S 0x30129000 ALIGN 8 EMPTY 0x1000 {}
    """)
    b, c, s = _region(p, "B"), _region(p, "C"), _region(p, "S")
    assert (b.start_mode, b.window) == (AFTER, "GMU_NORMAL")
    assert (c.start_mode, c.offset, c.window) == (OFFSET, 0x20000, "GMU_NORMAL")
    assert (s.start_mode, s.address, s.window) == (FIXED, 0x30129000, "CPU0BTCM")


def test_a_define_that_is_not_a_window_base_is_a_fixed_address():
    r = _region(_preview("CORE0_USER_STACK CPU0_STACK_ADDRESS ALIGN 8 EMPTY 0x1000 {}"), "CORE0_USER_STACK")
    assert (r.start_mode, r.address, r.window) == (FIXED, 0x30129000, "CPU0BTCM")


def test_image_limit_and_plus_zero_follow():
    p = _preview("""
    S1 CPU0_STACK_ADDRESS ALIGN 8 EMPTY 0x1000 {}
    S2 ImageLimit(S1) ALIGN 8 EMPTY 0x1000 {}
    S3 +0 EMPTY 0x800 {}
    """)
    assert [(_region(p, n).start_mode, _region(p, n).window) for n in ("S2", "S3")] == [
        (AFTER, "CPU0BTCM"), (AFTER, "CPU0BTCM")]


def test_base_plus_align_expr_takes_the_window_of_the_base():
    p = _preview("""
    V STARTUP_ADDRESS ALIGN 64 0x2080 { *(.v_code) }
    X CPUXPFLASH0_ADDRESS+AlignExpr(ImageLimit(V), 64) ALIGN 64 0x300000 { *(.x_code) }
    """)
    assert _region(p, "V").window == "CPUXATCM"
    x = _region(p, "X")
    assert (x.window, x.start_mode) == ("CPUXPFLASH0", AFTER)
    assert any("X" in n for n in p.notes)         # it followed V, which is on another window


def test_order_is_the_file_order_inside_a_window():
    p = _preview("""
    B GMU_NORMAL_ADDRESS 0x100 { *(.b_data) }
    Z CPU0BTCM_ADDRESS 0x100 { *(.z_data) }
    A AlignExpr(ImageLimit(B), 64) 0x100 { *(.a_data) }
    Y AlignExpr(ImageLimit(Z), 64) 0x100 { *(.y_data) }
    """)
    assert [(r.name, r.order) for r in p.regions] == [("B", 1), ("Z", 1), ("A", 2), ("Y", 2)]


def test_order_continues_after_regions_already_on_the_window():
    config = MemoryMapConfig(regions=[ExecRegion("OLD", "GMU", "GMU_NORMAL", "data", 5)])
    p = _preview("N GMU_NORMAL_ADDRESS+0x1000 0x100 { *(.n_data) }", config)
    assert _region(p, "N").order == 6


# --- alignment and size ---------------------------------------------------------------------

def test_align_and_size_from_the_header():
    p = _preview("""
    A GMU_NORMAL_ADDRESS ALIGN 128 0x2000 { *(.a_data) }
    B +0 4096 { *(.b_data) }
    """)
    assert (_region(p, "A").align, _region(p, "A").size) == (128, 0x2000)
    assert (_region(p, "B").align, _region(p, "B").size) == (64, 4096)


def test_without_align_stacks_get_8_and_others_64():
    p = _preview("""
    MY_STACK CPU0_STACK_ADDRESS EMPTY 0x400 {}
    GAP +0 EMPTY 0x400 {}
    """)
    assert _region(p, "MY_STACK").align == 8
    assert _region(p, "GAP").align == 64


def test_no_size_stays_none():
    assert _region(_preview("A GMU_NORMAL_ADDRESS { *(.a_data) }"), "A").size is None


# --- kind -------------------------------------------------------------------------------------

def test_empty_regions_are_stack_or_reserved():
    p = _preview("""
    CORE0_IRQ_STACK CPU0_STACK_ADDRESS ALIGN 8 EMPTY 0x1000 {}
    HOLE +0 EMPTY 0x2000 {}
    """)
    assert (_region(p, "CORE0_IRQ_STACK").kind, _region(p, "CORE0_IRQ_STACK").size) == ("stack", 0x1000)
    assert (_region(p, "HOLE").kind, _region(p, "HOLE").size) == ("reserved", 0x2000)
    assert p.unconfirmed == []


@pytest.mark.parametrize("selectors, kind", [
    ("*(+RO-CODE)", "code"),
    ("*(+CODE, .mcal_text_asil_d)", "code"),
    ("*(.mcal_ramcode_asil_d_core0)", "code"),
    ("*(.private_Core0_code)", "code"),
    ("*(+RO-DATA, .mcal_const_asil_d_8)", "const"),
    ("*(.mcal_no_init_asil_d_8)", "noinit"),
    ("*(+ZI) *(.global_bss)", "bss"),
    ("*(+BSS)", "bss"),
    ("*(.mcal_cleared)", "bss"),
    ("*(+RW-DATA) *(.mcal_data)", "data"),
    ("*(.unclear_bss) *(.mcal_no_init_a) *(.mcal_no_init_b)", "noinit"),     # majority
])
def test_kind_inferred_from_the_selectors(selectors, kind):
    p = _preview(f"R GMU_NORMAL_ADDRESS 0x1000 {{ {selectors} }}")
    assert _region(p, "R").kind == kind
    assert p.unconfirmed == []


def test_kind_that_cannot_be_told_is_imported_to_be_confirmed():
    p = _preview("R GMU_NORMAL_ADDRESS 0x1000 { *(.foo) *(.bar) }")
    r = _region(p, "R")
    assert r.kind in KINDS and r.kind == "data"
    assert p.unconfirmed == ["R"]


def test_a_tie_is_to_be_confirmed():
    p = _preview("R GMU_NORMAL_ADDRESS 0x1000 { *(.x_data) *(.y_bss) }")
    assert _region(p, "R").kind in KINDS
    assert p.unconfirmed == ["R"]


def test_infer_kind_directly():
    assert infer_kind([Selector("*", (".a_text",), (), 1)]) == ("code", True)
    assert infer_kind([]) == ("data", False)


# --- limit regions and names ------------------------------------------------------------------

def test_limit_regions_are_not_imported():
    p = _preview("""
    PRIVATE_DATA_CORE0 CPU0BTCM_ADDRESS 0x8000 { *(.p_data) }
    PRIVATE_DATA_CORE0_LIMIT +0 ALIGN 64 EMPTY 0 {}
    """)
    assert [r.name for r in p.regions] == ["PRIVATE_DATA_CORE0"]
    assert any("PRIVATE_DATA_CORE0_LIMIT" in t and "界限" in t for t in _reasons(p))


def test_invalid_region_name_is_reported():
    p = _preview("1BAD GMU_NORMAL_ADDRESS 0x100 { *(.b_data) }")
    assert p.regions == [] and p.placements == []
    assert any("1BAD" in t for t in _reasons(p))


# --- placements --------------------------------------------------------------------------------

def test_explicit_selectors_become_manual_placements():
    p = _preview("""
    PRIVATE_BSS_CORE0 CPU0BTCM_ADDRESS 0x9000
    {
        *(.mcal_bss_asil_d_unspecified_core0)
        *(+ZI, .private_bss_Core0)
        *(.a_bss .b_bss)
    }
    """)
    assert p.placements == [(".mcal_bss_asil_d_unspecified_core0", "PRIVATE_BSS_CORE0"),
                            (".private_bss_Core0", "PRIVATE_BSS_CORE0"),
                            (".a_bss", "PRIVATE_BSS_CORE0"), (".b_bss", "PRIVATE_BSS_CORE0")]


@pytest.mark.parametrize("selector, word", [
    ("*(+BSS)", "通配"),
    (".ANY(+RW-DATA)", ".ANY"),
    ("exception.o(.IRQ_init_vector)", "exception.o"),
    ("*(.init_default_vector, +First)", "+First"),
    ("*(+RO-DATA, .sdk_const_*)", "模式"),
])
def test_what_cannot_be_placed_is_reported(selector, word):
    p = _preview(f"R GMU_NORMAL_ADDRESS 0x1000 {{ {selector} }}")
    assert p.placements == []
    assert [r.name for r in p.regions] == ["R"]          # the region itself is imported
    assert any(word in t for t in _reasons(p)), _reasons(p)


def test_a_region_on_no_window_is_reported_with_its_selectors():
    p = _preview("FAR 0x70000000 0x100 { *(.far_data) }")
    assert p.regions == [] and p.placements == []
    texts = _reasons(p)
    assert any("FAR" in t and "0x70000000" in t for t in texts)
    assert any(".far_data" in t for t in texts)


def test_a_region_following_one_on_no_window_is_reported():
    p = _preview("""
    FAR 0x70000000 0x100 { *(.far_data) }
    NEXT AlignExpr(ImageLimit(FAR), 64) 0x100 { *(.next_data) }
    """)
    assert p.regions == []
    assert any("NEXT" in t for t in _reasons(p))


def test_a_section_selected_twice_in_the_file_is_placed_once():
    p = _preview("""
    A GMU_NORMAL_ADDRESS 0x100 { *(.x_data) }
    B +0 0x100 { *(.x_data) }
    """)
    assert p.placements == [(".x_data", "A")]
    assert [(s.section, s.region, s.existing) for s in p.skipped_placements] == [(".x_data", "B", "A")]


# --- never overwrite ----------------------------------------------------------------------------

def _existing_config():
    return MemoryMapConfig(
        regions=[ExecRegion("UNDEFINE_RAM_BSS", "GMU", "GMU_DEVICE", "bss", 1, align=32)],
        rules=[Rule("r", {"kind": "BSS"}, "UNDEFINE_RAM_BSS")],
        manual={".global_bss": "SOMEWHERE"})


def test_existing_region_and_manual_placement_are_kept_and_reported():
    config = _existing_config()
    p = _preview("""
    UNDEFINE_RAM_BSS GMU_NORMAL_ADDRESS 0x20000 { *(+ZI) *(.global_bss) *(.mcal_bss) }
    """, config)
    assert p.regions == [] and p.skipped_regions == ["UNDEFINE_RAM_BSS"]
    assert [(s.section, s.existing) for s in p.skipped_placements] == [(".global_bss", "SOMEWHERE")]
    assert p.placements == [(".mcal_bss", "UNDEFINE_RAM_BSS")]
    apply_import(config, p)
    kept = config.region("UNDEFINE_RAM_BSS")
    assert (kept.window, kept.align) == ("GMU_DEVICE", 32)
    assert config.manual == {".global_bss": "SOMEWHERE", ".mcal_bss": "UNDEFINE_RAM_BSS"}


def test_preview_does_not_change_the_config():
    config = _existing_config()
    before = copy.deepcopy(config_dict(config))
    _preview("""
    UNDEFINE_RAM_BSS GMU_NORMAL_ADDRESS 0x20000 { *(.global_bss) }
    NEW +0 0x100 { *(.new_data) }
    """, config)
    assert config_dict(config) == before


def test_apply_adds_exactly_the_preview_and_keeps_the_rules():
    config = _existing_config()
    rules = copy.deepcopy(config.rules)
    p = _preview("""
    UNDEFINE_RAM_BSS GMU_NORMAL_ADDRESS 0x20000 { *(.global_bss) }
    NEW GMU_NORMAL_ADDRESS+0x20000 0x100 { *(.new_data) }
    """, config)
    apply_import(config, p)
    assert [r.name for r in config.regions] == ["UNDEFINE_RAM_BSS", "NEW"]
    assert config.region("NEW") == p.regions[0] and config.region("NEW") is not p.regions[0]
    assert config.manual == {".global_bss": "SOMEWHERE", ".new_data": "NEW"}
    assert [l.name for l in config.load_regions] == ["ROM_CODE"]
    assert config.rules == rules


def test_apply_does_not_overwrite_what_appeared_after_the_preview():
    config = MemoryMapConfig()
    p = _preview("A GMU_NORMAL_ADDRESS 0x100 { *(.a_data) }", config)
    config.add_region(ExecRegion("A", "GMU", "GMU_DEVICE", "bss", 1))
    config.manual[".a_data"] = "ELSE"
    skipped = apply_import(config, p)
    assert config.region("A").window == "GMU_DEVICE" and config.manual[".a_data"] == "ELSE"
    assert len(skipped) == 2


# --- load regions ---------------------------------------------------------------------------------

def test_two_load_regions():
    text = DEFINES + """
ROM_CODE CPUXPFLASH0_ADDRESS 0x300000
{
    CODE CPUXPFLASH0_ADDRESS ALIGN 64 0x100000 { *(.c_text) }
}
DFLASH_LOAD DFLASH_ADDRESS 0x80000
{
    DFLASH_DATA DFLASH_ADDRESS ALIGN 64 0x80000 { *(.dflash_const) }
}
"""
    p = preview_import(MemoryMapConfig(), text, "x.scat", CHIP)
    assert p.load_regions == [LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x300000),
                              LoadRegion("DFLASH_LOAD", "DFLASH_NORMAL", 0x80000)]
    assert [(r.name, r.load_region, r.kind) for r in p.regions] == [
        ("CODE", "ROM_CODE", "code"), ("DFLASH_DATA", "DFLASH_LOAD", "const")]
    config = MemoryMapConfig()
    apply_import(config, p)
    assert [l.name for l in config.load_regions] == ["ROM_CODE", "DFLASH_LOAD"]


def test_load_region_on_no_window_is_reported_and_its_regions_get_the_first():
    p = _preview("A GMU_NORMAL_ADDRESS 0x100 { *(.a_data) }", load="FAR_LOAD 0x70000000 0x1000")
    assert p.load_regions == []
    assert any("FAR_LOAD" in t for t in _reasons(p))
    assert _region(p, "A").load_region == ""


def test_existing_load_region_is_kept():
    config = MemoryMapConfig(load_regions=[LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x1000)])
    p = _preview("A GMU_NORMAL_ADDRESS 0x100 { *(.a_data) }", config)
    assert p.load_regions == [] and p.skipped_load_regions == ["ROM_CODE"]
    assert _region(p, "A").load_region == "ROM_CODE"
    apply_import(config, p)
    assert config.load_regions == [LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x1000)]


# --- end to end -------------------------------------------------------------------------------------

END_TO_END = DEFINES + """
; a small vendor-like file
ROM_CODE CPUXPFLASH0_ADDRESS 0X300000
{
    EX_CODE CPUXPFLASH0_ADDRESS ALIGN 64 0X100000
    {
        *(+RO-CODE)
        *(+CODE, .mcal_text_asil_d)
    }
    EX_CONST_DATA AlignExpr(ImageLimit(EX_CODE), 64) ALIGN 64 0X100000
    {
        *(+RO-DATA, .mcal_const_asil_d_8)
    }
    PRIVATE_DATA_CORE0 CPU0BTCM_ADDRESS ALIGN 64 0x8000
    {
        *(.mcal_data_asil_d_8_core0)
    }
    PRIVATE_BSS_CORE0 AlignExpr(ImageLimit(PRIVATE_DATA_CORE0), 64) ALIGN 64 0x9000
    {
        *(.mcal_bss_asil_d_unspecified_core0)
    }
    PRIVATE_BSS_CORE0_LIMIT +0 ALIGN 64 EMPTY 0 {}
    CORE0_USER_STACK CPU0_STACK_ADDRESS ALIGN 8 EMPTY 0x1000 {}
    CORE0_IRQ_STACK ImageLimit(CORE0_USER_STACK) ALIGN 8 EMPTY 0x1000 {}
}
"""


def test_end_to_end_into_an_empty_config():
    config = MemoryMapConfig()
    p = preview_import(config, END_TO_END, "x.scat", CHIP)
    assert config.regions == []
    apply_import(config, p)
    got = [(r.name, r.window, r.kind, r.order, r.start_mode, r.address, r.align, r.size, r.load_region)
           for r in config.regions]
    assert got == [
        ("EX_CODE", "CPUXPFLASH0", "code", 1, AFTER, None, 64, 0x100000, "ROM_CODE"),
        ("EX_CONST_DATA", "CPUXPFLASH0", "const", 2, AFTER, None, 64, 0x100000, "ROM_CODE"),
        ("PRIVATE_DATA_CORE0", "CPU0BTCM", "data", 1, AFTER, None, 64, 0x8000, "ROM_CODE"),
        ("PRIVATE_BSS_CORE0", "CPU0BTCM", "bss", 2, AFTER, None, 64, 0x9000, "ROM_CODE"),
        ("CORE0_USER_STACK", "CPU0BTCM", "stack", 3, FIXED, 0x30129000, 8, 0x1000, "ROM_CODE"),
        ("CORE0_IRQ_STACK", "CPU0BTCM", "stack", 4, AFTER, None, 8, 0x1000, "ROM_CODE"),
    ]
    assert config.manual == {
        ".mcal_text_asil_d": "EX_CODE",
        ".mcal_const_asil_d_8": "EX_CONST_DATA",
        ".mcal_data_asil_d_8_core0": "PRIVATE_DATA_CORE0",
        ".mcal_bss_asil_d_unspecified_core0": "PRIVATE_BSS_CORE0",
    }
    assert config.load_regions == [LoadRegion("ROM_CODE", "CPUXPFLASH0", 0x300000)]
    assert p.unconfirmed == [] and p.notes == []
    texts = _reasons(p)
    assert any("PRIVATE_BSS_CORE0_LIMIT" in t for t in texts)
    assert any("+RO-CODE" in t for t in texts)                 # the wildcard selector
    assert len(texts) == 2


def test_a_follower_takes_the_window_of_the_region_it_follows():
    # X lies on the flash although it follows V on the ATCM; Y follows X, so it is on the flash too
    p = _preview("""
    V STARTUP_ADDRESS ALIGN 64 0x2080 { *(.v_code) }
    X CPUXPFLASH0_ADDRESS+AlignExpr(ImageLimit(V), 64) ALIGN 64 0x300000 { *(.x_code) }
    Y AlignExpr(ImageLimit(X), 64) ALIGN 64 0x300000 { *(.y_const) }
    """)
    assert [(r.name, r.window, r.order) for r in p.regions] == [
        ("V", "CPUXATCM", 1), ("X", "CPUXPFLASH0", 1), ("Y", "CPUXPFLASH0", 2)]


def test_a_follower_of_an_existing_region_takes_its_window():
    config = MemoryMapConfig(regions=[ExecRegion("OLD", "GMU", "GMU_DEVICE", "data", 1)])
    p = _preview("N AlignExpr(ImageLimit(OLD), 64) 0x100 { *(.n_data) }", config)
    assert (_region(p, "N").window, _region(p, "N").start_mode, _region(p, "N").order) == ("GMU_DEVICE", AFTER, 2)


def test_a_zero_length_empty_stack_is_imported_as_reserved():
    p = _preview("""
    S1 CPU0_STACK_ADDRESS ALIGN 8 EMPTY 0x1000 {}
    CORE2_USER_STACK AlignExpr(ImageLimit(S1), 64) EMPTY 0x0 {}
    """)
    r = _region(p, "CORE2_USER_STACK")
    assert (r.kind, r.size) == ("reserved", None)
    assert any("CORE2_USER_STACK" in n for n in p.notes)
