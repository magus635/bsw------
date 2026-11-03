"""Writing the generated linker file (preview, backup, atomic write, cancel) and the self-check
against the memory map check, on a small synthetic project."""
import os

import pytest

from autosar_configurator.core.memmap import check, linkfile
from autosar_configurator.core.memmap import plan as pl
from autosar_configurator.core.memmap.config import ExecRegion, MemoryMapConfig, Rule
from autosar_configurator.core.memmap.generators import UnsupportedCompiler

from tests.core.test_linker_plan import CHIP


def _branch(name, kind, output):
    return f"#elif defined {name}\n    #undef {name}\n    MEMMAP_START_{kind}(\"{output}\")\n"


CAN_MEMMAP_H = ("#if 0\n"
                + _branch("CAN_START_SEC_CODE", "TEXT", ".mcal_text_asil_d")
                + _branch("CAN_START_SEC_VAR_CLEARED_CORE0", "BSS", ".mcal_bss_asil_d_unspecified_core0")
                + _branch("CAN_START_SEC_VAR_INIT_32", "DATA", ".mcal_data_asil_d_32")
                + _branch("CAN_START_SEC_CONST_32", "RODATA", ".mcal_const_asil_d_32")
                + "#endif\n")


def _section(name):
    return (f"#define CAN_START_SEC_{name}\n#include \"Can_MemMap.h\"\nint x_{name};\n"
            f"#define CAN_STOP_SEC_{name}\n#include \"Can_MemMap.h\"\n")


STARTUP_C = """\
void Startup(void)
{
    STARTUP_GETCOPYDATAINFO(UNDEFINE_RAM_DATA, globalData);
    STARTUP_GETBSSDATAINFO(PRIVATE_BSS_CORE0, globalBss);
    STARTUP_SETSTACK(MODE_SYS, CORE0_USER_STACK);
    STARTUP_GETCOPYDATAINFO(PRIVATE_DATA_CORE2, core2Data);
}
"""


def _project(tmp_path, with_const=False):
    src = tmp_path / "src"
    src.mkdir()
    sections = ["CODE", "VAR_CLEARED_CORE0", "VAR_INIT_32"] + (["CONST_32"] if with_const else [])
    (src / "Can.c").write_text("".join(_section(s) for s in sections), encoding="utf-8")
    (src / "startup.c").write_text(STARTUP_C, encoding="utf-8")
    (src / "Can_MemMap.h").write_text(CAN_MEMMAP_H, encoding="utf-8")
    return src


def _config():
    config = MemoryMapConfig(chip="THA6206_LFBGA292")
    config.regions = [
        ExecRegion("EX_CODE", "PFLASH0", "CPUXPFLASH0", "code", 1, required=True),
        ExecRegion("UNDEFINE_RAM_DATA", "GMU", "GMU_NORMAL", "data", 1, required=True),
        ExecRegion("PRIVATE_BSS_CORE0", "CPU0BTCM", "CPU0BTCM", "bss", 1, required=True),
        ExecRegion("CORE0_USER_STACK", "CPU0BTCM", "CPU0BTCM", "stack", 10, align=8, required=True),
    ]
    config.rules = [Rule("bss", {"kind": ["BSS"], "core": 0}, "PRIVATE_BSS_CORE0"),
                    Rule("code", {"kind": ["TEXT"]}, "EX_CODE"),
                    Rule("data", {"kind": ["DATA"]}, "UNDEFINE_RAM_DATA")]
    config.trimmed = ["PRIVATE_DATA_CORE2"]
    return config


def _generate(src, config):
    scan = check.run_check([src], regions=CHIP)
    generation = linkfile.prepare_generation("ads", config, scan.rows, CHIP, scan.needs)
    return scan, generation


# --- self-check -------------------------------------------------------------------------------

def test_self_check_clean_for_a_complete_configuration(tmp_path):
    src = _project(tmp_path)
    scan, generation = _generate(src, _config())
    assert generation.refusals == [] and generation.warnings == []
    result = linkfile.self_check_text(generation.file.text, [src], regions=CHIP)
    assert result.result.placement_checked
    assert result.missing_symbols == [] and result.unplaced == []
    assert result.clean
    assert "不能证明" in result.note


def test_self_check_on_the_written_file(tmp_path):
    src = _project(tmp_path)
    _, generation = _generate(src, _config())
    target = linkfile.target_path(tmp_path, "ads")
    linkfile.write_linker_file(target, generation.file.text)
    assert linkfile.self_check(target, [src], regions=CHIP).clean


def test_self_check_finds_the_missing_reserved_region_when_switched_off(tmp_path):
    src = _project(tmp_path)
    config = _config()
    pl.set_reserve_missing_cores(config, False)
    _, generation = _generate(src, config)
    result = linkfile.self_check_text(generation.file.text, [src], regions=CHIP)
    assert [f.text for f in result.missing_symbols] == ["链接文件缺少执行区域 PRIVATE_DATA_CORE2"]


def test_section_not_placed_warns_and_the_self_check_shows_it(tmp_path):
    src = _project(tmp_path, with_const=True)
    _, generation = _generate(src, _config())
    assert generation.refusals == []
    assert any(".mcal_const_asil_d_32" in w for w in generation.warnings)
    result = linkfile.self_check_text(generation.file.text, [src], regions=CHIP)
    assert [f.text.split("（")[0] for f in result.unplaced] == [".mcal_const_asil_d_32"]


def test_refused_generation_has_no_text(tmp_path):
    src = _project(tmp_path)
    config = _config()
    config.manual[".mcal_data_asil_d_32"] = "GONE"
    _, generation = _generate(src, config)
    assert generation.refused and generation.file is None


def test_unsupported_compiler_refused_before_planning(tmp_path):
    with pytest.raises(UnsupportedCompiler):
        linkfile.prepare_generation("ghs", _config(), [], CHIP)


# --- writing ------------------------------------------------------------------------------------

def test_target_path():
    assert linkfile.target_path("P", "ads").as_posix() == "P/IntegrationProject/linkedFile/Ads/scatter.scat"


def test_preview_new_file_writes_nothing(tmp_path):
    target = linkfile.target_path(tmp_path, "ads")
    shown = linkfile.preview(target, "abc\n")
    assert (shown.replaces, shown.backup, shown.size, shown.unchanged) == (False, None, 4, False)
    assert not (tmp_path / "IntegrationProject").exists()


def test_preview_counts_bytes_not_characters(tmp_path):
    assert linkfile.preview(tmp_path / "x.scat", "; 区域\n").size == len("; 区域\n".encode("utf-8"))


def test_cancel_leaves_nothing(tmp_path):
    """The user sees the preview and cancels: write_linker_file is never called."""
    src = _project(tmp_path)
    before = sorted(p.relative_to(tmp_path) for p in tmp_path.rglob("*"))
    _, generation = _generate(src, _config())
    linkfile.preview(linkfile.target_path(tmp_path, "ads"), generation.file.text)
    assert sorted(p.relative_to(tmp_path) for p in tmp_path.rglob("*")) == before


def test_write_new_file(tmp_path):
    target = linkfile.target_path(tmp_path, "ads")
    shown = linkfile.write_linker_file(target, "new\n")
    assert target.read_bytes() == b"new\n"
    assert not shown.replaces
    assert sorted(p.name for p in target.parent.iterdir()) == ["scatter.scat"]


def test_existing_file_backed_up(tmp_path):
    target = linkfile.target_path(tmp_path, "ads")
    target.parent.mkdir(parents=True)
    target.write_bytes(b"old\n")
    shown = linkfile.preview(target, "new\n")
    assert shown.replaces and shown.backup == target.with_name("scatter.scat.bak")
    linkfile.write_linker_file(target, "new\n")
    assert target.read_bytes() == b"new\n"
    assert target.with_name("scatter.scat.bak").read_bytes() == b"old\n"
    assert sorted(p.name for p in target.parent.iterdir()) == ["scatter.scat", "scatter.scat.bak"]


def test_preview_says_when_nothing_changes(tmp_path):
    target = tmp_path / "scatter.scat"
    target.write_bytes(b"same\n")
    assert linkfile.preview(target, "same\n").unchanged


def test_failed_write_leaves_the_old_file_and_no_temp(tmp_path, monkeypatch):
    target = linkfile.target_path(tmp_path, "ads")
    target.parent.mkdir(parents=True)
    target.write_bytes(b"old\n")

    def broken(src, dst):
        raise OSError("disk full")

    monkeypatch.setattr(linkfile.os, "replace", broken)
    with pytest.raises(linkfile.LinkFileError, match="disk full"):
        linkfile.write_linker_file(target, "new\n")
    assert target.read_bytes() == b"old\n"
    assert not any(p.suffix == ".tmp" for p in target.parent.iterdir())


def test_failed_temp_write_leaves_no_backup_change(tmp_path, monkeypatch):
    target = linkfile.target_path(tmp_path, "ads")
    target.parent.mkdir(parents=True)
    target.write_bytes(b"old\n")

    def broken(*args, **kwargs):
        raise OSError("no space")

    monkeypatch.setattr(linkfile.tempfile, "mkstemp", broken)
    with pytest.raises(linkfile.LinkFileError):
        linkfile.write_linker_file(target, "new\n")
    assert target.read_bytes() == b"old\n"
    assert sorted(p.name for p in target.parent.iterdir()) == ["scatter.scat"]


def test_written_bytes_are_identical_each_time(tmp_path):
    src = _project(tmp_path)
    _, first = _generate(src, _config())
    _, second = _generate(src, _config())
    a, b = tmp_path / "a.scat", tmp_path / "b.scat"
    linkfile.write_linker_file(a, first.file.text)
    linkfile.write_linker_file(b, second.file.text)
    assert a.read_bytes() == b.read_bytes()
    assert b"\r\n" not in a.read_bytes()
