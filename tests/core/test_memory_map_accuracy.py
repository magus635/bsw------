"""Memory map accuracy: base address expressions of ADS scatter files, and alternative
branches of a MemMap header that map the same section."""
from autosar_configurator.core.memmap.headers import parse_header
from autosar_configurator.core.memmap.scatter import parse_scatter

DEFINES = "#define RAM 0x10000000\n#define FLASH 0x08000000\n"


def _region(text, name):
    return parse_scatter(DEFINES + text, "x.scat").region(name)


# --- base addresses ----------------------------------------------------------------

def test_offset_after_a_define_is_added():
    region = _region("LR RAM 0x1000\n{\n  B RAM+0x1000 0x100 { *(.b) }\n}\n", "B")
    assert region.address == 0x10001000


def test_offset_may_have_spaces_and_a_define_as_offset():
    text = "#define OFFSET 0x200\nLR RAM 0x1000\n{\n  B RAM + OFFSET 0x100 { *(.b) }\n}\n"
    assert parse_scatter(DEFINES + text, "x.scat").region("B").address == 0x10000200


def test_plus_offset_follows_the_previous_region_not_address_zero():
    text = "LR RAM 0x1000\n{\n  A RAM 0x100 { *(.a) }\n  C AlignExpr(+0, 8) 0x100 { *(.c) }\n}\n"
    region = _region(text, "C")
    assert region.follows == "A" and region.address == 0x10000000


def test_plus_offset_without_align_still_follows():
    text = "LR RAM 0x1000\n{\n  A RAM 0x100 { *(.a) }\n  C +0x10 0x100 { *(.c) }\n}\n"
    region = _region(text, "C")
    assert region.follows == "A" and region.address == 0x10000000


def test_first_region_of_a_load_region_with_plus_offset_is_unresolved():
    """Nothing before it to follow: unresolved, not address zero."""
    region = _region("LR RAM 0x1000\n{\n  C AlignExpr(+0, 8) 0x100 { *(.c) }\n}\n", "C")
    assert region.address is None


def test_align_expr_with_a_base_and_a_length_keeps_the_base():
    region = _region("LR RAM 0x1000\n{\n  A RAM 0x100 { *(.a) }\n"
                     "  D AlignExpr(RAM + ImageLength(A), 64) 0x100 { *(.d) }\n}\n", "D")
    assert region.address == 0x10000000


def test_existing_forms_still_resolve():
    text = ("LR FLASH 0x1000\n{\n  A FLASH 0x100 { *(.a) }\n"
            "  E AlignExpr(ImageLimit(A), 64) 0x100 { *(.e) }\n"
            "  F FLASH+AlignExpr(ImageLimit(A), 64) 0x100 { *(.f) }\n}\n")
    scatter = parse_scatter(DEFINES + text, "x.scat")
    assert scatter.region("E").follows == "A" and scatter.region("E").address == 0x08000000
    assert scatter.region("F").address == 0x08000000


# --- alternative branches of a header --------------------------------------------------

BRANCHES = """\
#if defined(CHIP_A)
 #if defined X_START_SEC_A
 MEMMAP_START_BSS(".a_chip_a")
 #endif
#elif defined(CHIP_B)
 #if defined X_START_SEC_A
 MEMMAP_START_BSS(".a_chip_b")
 #endif
#endif
"""


def test_same_section_in_different_branches_is_not_a_duplicate():
    mappings, repeated = parse_header(BRANCHES, "h")
    assert repeated == []
    assert [m.output for m in mappings] == [".a_chip_a", ".a_chip_b"]


def test_same_section_twice_in_one_branch_is_still_a_duplicate():
    text = ("#if defined(CHIP_A)\n"
            "#elif defined X_START_SEC_A\n MEMMAP_START_BSS(\".one\")\n"
            "#elif defined X_START_SEC_A\n MEMMAP_START_BSS(\".two\")\n"
            "#endif\n")
    _, repeated = parse_header(text, "h")
    assert [m.output for m in repeated] == [".two"]


def test_same_section_outside_any_branch_twice_is_a_duplicate():
    text = ("#if 0\n#elif defined X_START_SEC_A\n MEMMAP_START_BSS(\".one\")\n#endif\n"
            "#if 0\n#elif defined X_START_SEC_A\n MEMMAP_START_BSS(\".two\")\n#endif\n")
    _, repeated = parse_header(text, "h")
    assert [m.output for m in repeated] == [".two"]
