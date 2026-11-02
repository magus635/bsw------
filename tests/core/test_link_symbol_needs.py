"""Link symbol needs: macro and symbol recognition, merging, the compiler convention
table, and the check against an ADS scatter file."""
import hashlib

from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import check, layout, symbols
from autosar_configurator.core.memmap.layout import LayoutFilter
from autosar_configurator.core.memmap.symbols import (
    ADS,
    BASE,
    CLEAR,
    COPY,
    GHS,
    LIMIT,
    LOAD,
    STACK,
    merge,
    scan_needs,
    symbols_for,
)

STARTUP_C = """\
#include "startup.h"
/* STARTUP_GETCOPYDATAINFO(IN_A_COMMENT, x) */
void Startup_Init(void)
{
    STARTUP_GETCOPYDATAINFO(UNDEFINE_RAM_DATA, (globalData));
    STARTUP_GETBSSDATAINFO(UNDEFINE_RAM_BSS, (globalBss));
#if (CORES > 1)
    STARTUP_GETCOPYDATAINFO(LMU2_CACHED_DATA, globalData);
#endif
    STARTUP_GETIMAGEBASEADDR(CORE0_USER_STACK, stackInit.clearImageAddr);
    STARTUP_GETIMAGEBSSLIMITADDR(CORE0_FIQ_STACK, stackInit.clearLimitAddr);
    STARTUP_SETSTACK(MODE_SYS, CORE0_USER_STACK);
    STARTUP_SETHYPMODESP(CORE0_HYP_STACK);
}
"""

OS_LINK = """\
extern uint32 Image$$OS_DATA_CORE0$$Base;
extern uint32 Image$$OS_DATA_CORE0_LIMIT$$Base;
extern uint32 Load$$OS_DATA_CORE0$$Base;
extern uint32 Load$$OS_DATA_CORE0$$Limit;
extern uint32 Image$$OS_BSS_CORE0_LIMIT$$ZI$$Base;
extern uint32 Image$$CORE0_USER_STACK$$ZI$$Limit;
"""

STARTUP_H = """\
#ifndef STARTUP_H
#define STARTUP_H
#define STARTUP_GETIMAGEBASEADDR(RegionName, address) \\
    { ASM_VOLATILE("ldr %0, =Image$$" #RegionName "$$Base" : "+r"(address)::"memory"); }
#define STARTUP_GETCOPYDATAINFO(RegionName, InitSection) \\
    { STARTUP_GETIMAGEBASEADDR(RegionName, InitSection.copyDataImageAddr); }
#endif
"""

SCAT = """\
LR 0x0 0x100000
{
    UNDEFINE_RAM_DATA 0x10000000 0x1000 { *(+RW-DATA) }
    UNDEFINE_RAM_DATA_LIMIT +0 EMPTY 0x0 {}
    UNDEFINE_RAM_BSS +0 0x1000 { *(+BSS) }
    UNDEFINE_RAM_BSS_LIMIT +0 EMPTY 0x0 {}
    CORE0_USER_STACK 0x30129000 EMPTY 0x1000 {}
    CORE0_FIQ_STACK +0 EMPTY 0x1000 {}
    CORE0_FIQ_STACK_LIMIT +0 EMPTY 0x0 {}
    CORE0_HYP_STACK +0 EMPTY 0x1000 {}
    NOBODY_USES_ME 0x20000000 0x100 { *(.x) }
}
"""
# CORE0_FIQ_STACK_LIMIT is there because startup.c asks for the FIQ stack's cleared limit
# (STARTUP_GETIMAGEBSSLIMITADDR); the vendor script declares it the same way.


def _by(needs):
    return {n.region: n for n in needs}


# --- recognition -----------------------------------------------------------------

def test_startup_macros_and_uses():
    refs = scan_needs(STARTUP_C, "startup.c")
    needs = _by(merge(refs))
    # uses come in the fixed order of symbols.USES: copy, clear, base, limit, load, stack
    assert needs["UNDEFINE_RAM_DATA"].uses == [COPY, BASE, LIMIT, LOAD]
    assert needs["UNDEFINE_RAM_BSS"].uses == [CLEAR, BASE]
    assert needs["CORE0_USER_STACK"].uses == [BASE, STACK]
    assert needs["CORE0_FIQ_STACK"].uses == [CLEAR]
    assert needs["CORE0_HYP_STACK"].uses == [STACK]
    first = needs["UNDEFINE_RAM_DATA"].references[0]
    assert (first.path, first.line, first.how, first.conditional) == (
        "startup.c", 5, "STARTUP_GETCOPYDATAINFO", False)


def test_comment_and_unconditional_flag():
    needs = _by(merge(scan_needs(STARTUP_C, "startup.c")))
    assert "IN_A_COMMENT" not in needs
    assert needs["LMU2_CACHED_DATA"].conditional is True
    assert needs["UNDEFINE_RAM_DATA"].conditional is False


def test_macro_definitions_are_not_uses():
    """startup.h defines the macros with parameter names; those are not regions."""
    assert scan_needs(STARTUP_H, "startup.h") == []


def test_expression_argument_is_not_a_region():
    text = "STARTUP_GETIMAGEBASEADDR(REGION_OF(core), x);\nSTARTUP_GETIMAGEBASEADDR(a + b, x);\n"
    assert scan_needs(text, "x.c") == []


def test_direct_ads_symbols():
    needs = _by(merge(scan_needs(OS_LINK, "Os_link_Lcfg.c")))
    assert needs["OS_DATA_CORE0"].uses == [BASE, LIMIT, LOAD]
    assert needs["OS_BSS_CORE0"].uses == [CLEAR]
    assert needs["CORE0_USER_STACK"].uses == [STACK]
    assert needs["OS_DATA_CORE0"].references[0].how == "Image$$OS_DATA_CORE0$$Base"
    assert "OS_DATA_CORE0_LIMIT" not in needs        # the limit region belongs to OS_DATA_CORE0


def test_direct_ghs_symbols():
    text = ("x = &__PRIVATE_DATA_CORE0_ADDRESS_START;\n"
            "y = &__PRIVATE_DATA_CORE0_ADDRESS_END;\n"
            "z = &__PRIVATE_DATA_CORE0_LOAD_ADDRESS_START;\n")
    need = _by(merge(scan_needs(text, "g.c")))["PRIVATE_DATA_CORE0"]
    assert need.uses == [BASE, LIMIT, LOAD]


def test_several_uses_merge_with_both_sources():
    text = ("STARTUP_GETIMAGEBASEADDR(PRIVATE_DATA_CORE0, a);\n"
            "STARTUP_GETIMAGELIMITADDR(PRIVATE_DATA_CORE0, b);\n"
            "p = &Image$$PRIVATE_DATA_CORE0_LIMIT$$Base;\n")
    need = _by(merge(scan_needs(text, "m.c")))["PRIVATE_DATA_CORE0"]
    assert need.uses == [BASE, LIMIT]
    assert [(r.line, r.how) for r in need.references] == [
        (1, "STARTUP_GETIMAGEBASEADDR"), (2, "STARTUP_GETIMAGELIMITADDR"),
        (3, "Image$$PRIVATE_DATA_CORE0_LIMIT$$Base")]
    assert need.uses_text() == "基址、界限"


def test_include_guard_is_not_a_condition():
    text = "#ifndef A_H\n#define A_H\nSTARTUP_GETIMAGEBASEADDR(R1, x);\n#endif\n"
    assert scan_needs(text, "a.h")[0].conditional is False


# --- convention table ----------------------------------------------------------------

def test_convention_for_a_copy_region_in_both_compilers():
    uses = [BASE, LIMIT, LOAD, COPY]
    assert symbols_for(ADS, "PRIVATE_DATA_CORE0", uses) == [
        "Image$$PRIVATE_DATA_CORE0$$Base", "Image$$PRIVATE_DATA_CORE0_LIMIT$$Base",
        "Load$$PRIVATE_DATA_CORE0$$Base"]
    assert symbols_for(GHS, "PRIVATE_DATA_CORE0", uses) == [
        "__PRIVATE_DATA_CORE0_ADDRESS_START", "__PRIVATE_DATA_CORE0_ADDRESS_END",
        "__PRIVATE_DATA_CORE0_LOAD_ADDRESS_START"]


def test_convention_clear_and_stack():
    assert symbols_for(ADS, "B", [CLEAR]) == ["Image$$B_LIMIT$$ZI$$Base"]
    assert symbols_for(GHS, "B", [CLEAR]) == ["__B_ADDRESS_END"]
    assert symbols_for(ADS, "S", [STACK]) == ["Image$$S$$ZI$$Limit"]
    assert symbols_for(GHS, "S", [STACK]) == ["__S_ADDRESS_END"]
    # the same GHS symbol serves limit and stack top: listed once
    assert symbols_for(GHS, "S", [LIMIT, STACK]) == ["__S_ADDRESS_END"]


def test_every_use_has_a_symbol_in_every_compiler():
    for compiler in (ADS, GHS):
        for use in symbols.USES:
            if use != COPY:         # a copy region is asked for base, limit and load address
                assert symbols_for(compiler, "R", [use]), (compiler, use)


# --- check -----------------------------------------------------------------------

def _workspace(tmp_path, startup=STARTUP_C, os_link=OS_LINK, scat=SCAT):
    src = tmp_path / "src"
    src.mkdir()
    (src / "startup.c").write_text(startup, encoding="utf-8")
    (src / "Os_link_Lcfg.c").write_text(os_link, encoding="utf-8")
    linker = tmp_path / "scatter.scat"
    linker.write_text(scat, encoding="utf-8")
    return src, linker


def _symbol_findings(result):
    return [(f.text, f.path, f.line, f.possible) for f in result.by_category(check.SYMBOL)]


def test_missing_region_and_missing_limit_region(tmp_path):
    src, linker = _workspace(tmp_path)
    result = check.run_check([src], [], linker, base=tmp_path)
    # ordered by file, then line: the OS file comes before startup.c
    assert _symbol_findings(result) == [
        ("链接文件缺少执行区域 OS_DATA_CORE0", "src/Os_link_Lcfg.c", 1, False),
        ("链接文件缺少执行区域 OS_BSS_CORE0", "src/Os_link_Lcfg.c", 5, False),
        ("链接文件缺少执行区域 LMU2_CACHED_DATA", "src/startup.c", 8, True)]
    note = result.by_category(check.SYMBOL)[0].note
    assert "用途：基址、界限、加载地址" in note and "引用于 src/Os_link_Lcfg.c:1" in note


def test_cleared_limit_of_a_stack_region_needs_a_limit_region(tmp_path):
    """startup.c asks for the FIQ stack's cleared limit, so the stack is not asked only
    for its top and ADS needs CORE0_FIQ_STACK_LIMIT."""
    scat = SCAT.replace("    CORE0_FIQ_STACK_LIMIT +0 EMPTY 0x0 {}\n", "")
    src, linker = _workspace(tmp_path, scat=scat)
    result = check.run_check([src], [], linker, base=tmp_path)
    assert "链接文件缺少界限区域 CORE0_FIQ_STACK_LIMIT" in [
        f.text for f in result.by_category(check.SYMBOL)]


def test_limit_region_missing(tmp_path):
    scat = SCAT.replace("    UNDEFINE_RAM_DATA_LIMIT +0 EMPTY 0x0 {}\n", "")
    src, linker = _workspace(tmp_path, scat=scat)
    result = check.run_check([src], [], linker, base=tmp_path)
    texts = [f.text for f in result.by_category(check.SYMBOL)]
    assert "链接文件缺少界限区域 UNDEFINE_RAM_DATA_LIMIT" in texts


def test_stack_region_needs_no_limit_region(tmp_path):
    src, linker = _workspace(tmp_path)
    result = check.run_check([src], [], linker, base=tmp_path)
    assert not any("CORE0_HYP_STACK" in f.text or "CORE0_USER_STACK" in f.text
                   for f in result.by_category(check.SYMBOL))


def test_unreferenced_region_is_not_a_problem(tmp_path):
    src, linker = _workspace(tmp_path)
    result = check.run_check([src], [], linker, base=tmp_path)
    assert "NOBODY_USES_ME" in result.scatter_regions
    assert not any("NOBODY_USES_ME" in f.text for f in result.findings)


def test_complete_linker_file_has_no_symbol_findings(tmp_path):
    scat = SCAT + "\n".join([
        "LR2 0x0 0x100 {",
        "    LMU2_CACHED_DATA 0x10058000 0x100 { *(.a) }",
        "    LMU2_CACHED_DATA_LIMIT +0 EMPTY 0x0 {}",
        "    OS_BSS_CORE0 0x30000000 0x100 { *(.b) }",
        "    OS_BSS_CORE0_LIMIT +0 EMPTY 0x0 {}",
        "    OS_DATA_CORE0 0x30001000 0x100 { *(.c) }",
        "    OS_DATA_CORE0_LIMIT +0 EMPTY 0x0 {}",
        "}", ""])
    src, linker = _workspace(tmp_path, scat=scat)
    result = check.run_check([src], [], linker, base=tmp_path)
    assert not result.by_category(check.SYMBOL)


def test_needs_read_without_a_linker_file(tmp_path):
    src, _ = _workspace(tmp_path)
    result = check.run_check([src], [], None, base=tmp_path)
    assert {n.region for n in result.needs} >= {"UNDEFINE_RAM_DATA", "OS_DATA_CORE0"}
    assert not result.by_category(check.SYMBOL) and not result.scatter_read
    assert "没有设置链接文件，放置检查已跳过" in result.notes


def test_needs_read_with_a_non_ads_linker_file(tmp_path):
    src, _ = _workspace(tmp_path)
    ld = tmp_path / "Linker.ld"
    ld.write_text("SECTIONS {}", encoding="utf-8")
    result = check.run_check([src], [], ld, base=tmp_path)
    assert result.needs and not result.by_category(check.SYMBOL) and not result.scatter_read
    assert result.notes[0].startswith("目前只支持 ADS")


def test_template_files_are_not_read_for_needs(tmp_path):
    src, linker = _workspace(tmp_path)
    (src / "Os_link_Tmpl.c").write_text(
        'extern uint32 Image$$[!"node:name(.)"!]$$Base;\nSTARTUP_GETIMAGEBASEADDR(TEMPLATE_ONLY, x);\n',
        encoding="utf-8")
    result = check.run_check([src], [], linker, base=tmp_path)
    assert "TEMPLATE_ONLY" not in {n.region for n in result.needs}
    assert result.templates_skipped == 1


def test_symbol_category_in_markdown_and_labels(tmp_path):
    src, linker = _workspace(tmp_path)
    result = check.run_check([src], [], linker, base=tmp_path)
    assert check.SYMBOL in check.CATEGORIES and check.CATEGORY_LABELS[check.SYMBOL] == "链接符号缺失"
    text = check.to_markdown(result)
    assert "## 链接符号缺失（" in text
    assert "- [ ] `src/Os_link_Lcfg.c:1` 链接文件缺少执行区域 OS_DATA_CORE0" in text


def test_symbol_check_is_read_only(tmp_path):
    src, linker = _workspace(tmp_path)
    files = sorted(p for p in tmp_path.rglob("*") if p.is_file())
    before = {p: hashlib.sha256(p.read_bytes()).hexdigest() for p in files}
    check.run_check([src], [], linker, base=tmp_path)
    assert {p: hashlib.sha256(p.read_bytes()).hexdigest() for p in files} == before


# --- layout view -----------------------------------------------------------------

REGIONS = [
    MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True),
    MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
]


def _groups(tmp_path, **kwargs):
    src, linker = _workspace(tmp_path, **kwargs)
    result = check.run_check([src], [], linker, REGIONS, base=tmp_path)
    return result, layout.by_region(result)


def _execution(groups, name):
    return next(e for g in groups for e in g.executions if e.name == name)


def test_execution_region_shows_who_refers_to_it(tmp_path):
    _, groups = _groups(tmp_path)
    data = _execution(groups, "UNDEFINE_RAM_DATA")
    assert data.need is not None
    assert data.note == "被引用：复制、基址、界限、加载地址（src/startup.c:5）"
    assert [g.name for g in groups if data in g.executions] == ["GMU_NORMAL"]


def test_regions_without_sections_are_listed_and_limit_markers_are_not(tmp_path):
    result, groups = _groups(tmp_path)
    names = {e.name for g in groups for e in g.executions}
    assert {"UNDEFINE_RAM_DATA", "CORE0_USER_STACK", "CORE0_HYP_STACK", "NOBODY_USES_ME"} <= names
    assert not any(n.endswith("_LIMIT") for n in names)


def test_unreferenced_region_is_marked_not_reported(tmp_path):
    result, groups = _groups(tmp_path)
    region = _execution(groups, "NOBODY_USES_ME")
    assert region.unreferenced and region.note == layout.UNREFERENCED
    assert not any("NOBODY_USES_ME" in f.text for f in result.findings)


def test_missing_regions_form_their_own_group_last(tmp_path):
    _, groups = _groups(tmp_path)
    assert groups[-1].name == layout.MISSING_GROUP
    assert [e.name for e in groups[-1].executions] == ["LMU2_CACHED_DATA", "OS_BSS_CORE0", "OS_DATA_CORE0"]
    assert groups[-1].executions[0].note.startswith("被引用：复制、基址、界限、加载地址")


def test_no_linker_file_means_no_missing_group(tmp_path):
    src, _ = _workspace(tmp_path)
    result = check.run_check([src], [], None, base=tmp_path)
    assert result.needs
    assert layout.MISSING_GROUP not in [g.name for g in layout.by_region(result)]


def test_filter_leaves_out_regions_without_sections(tmp_path):
    result, _ = _groups(tmp_path)
    groups = layout.by_region(result, LayoutFilter(only_findings=True))
    assert groups == []                         # no section rows, and a filter is about sections


def test_markdown_carries_the_references(tmp_path):
    result, _ = _groups(tmp_path)
    text = layout.to_markdown(result)
    assert "### UNDEFINE_RAM_DATA @ 0x10000000" in text
    assert "- 被引用：复制、基址、界限、加载地址（src/startup.c:5）" in text
    assert "- 无代码引用" in text
    assert f"## {layout.MISSING_GROUP}（0）" in text and "### OS_DATA_CORE0" in text
