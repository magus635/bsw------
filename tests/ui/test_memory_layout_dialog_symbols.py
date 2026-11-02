"""Memory layout dialog: link symbol needs shown on execution regions."""
from pathlib import Path
from types import SimpleNamespace

from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import check
from autosar_configurator.core.memmap.check import CheckResult, Finding
from autosar_configurator.core.memmap.symbols import merge, scan_needs
from autosar_configurator.ui.dialogs import memory_layout_dialog as dialog_module
from autosar_configurator.ui.dialogs.memory_layout_dialog import MemoryLayoutDialog


def _project(tmp_path):
    return SimpleNamespace(path=tmp_path / "p.dpa", memmap_source_dirs=[],
                           memmap_header_dirs=[], memmap_linker_file=None)


def _top(dialog):
    return [dialog.tree.topLevelItem(i).text(0) for i in range(dialog.tree.topLevelItemCount())]


def _symbols_result():

    needs = merge(scan_needs(
        "STARTUP_GETCOPYDATAINFO(UNDEFINE_RAM_DATA, x);\nSTARTUP_GETCOPYDATAINFO(LMU2_CACHED_DATA, y);\n",
        "startup.c"))
    findings = [Finding(check.SYMBOL, "startup.c", 2, "链接文件缺少执行区域 LMU2_CACHED_DATA")]
    return CheckResult(
        findings=findings, needs=needs, scatter_read=True,
        scatter_addresses={"UNDEFINE_RAM_DATA": 0x10000000, "NOBODY_USES_ME": 0x10010000},
        regions=[MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram")],
        linker_file="scatter.scat", files_scanned=1)


def _all_items(dialog):
    found = []

    def walk(item):
        found.append(item)
        for i in range(item.childCount()):
            walk(item.child(i))

    for i in range(dialog.tree.topLevelItemCount()):
        walk(dialog.tree.topLevelItem(i))
    return found


def test_execution_regions_show_references_and_missing_group(qtbot, tmp_path):
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_symbols_result())
    by_text = {item.text(0): item for item in _all_items(dialog)}
    referenced = next(i for t, i in by_text.items() if t.startswith("UNDEFINE_RAM_DATA @ 0x10000000"))
    assert referenced.text(3) == "被引用：复制、基址、界限、加载地址（startup.c:1）"
    unreferenced = next(i for t, i in by_text.items() if t.startswith("NOBODY_USES_ME"))
    assert unreferenced.text(3) == "无代码引用" and unreferenced.text(4) == ""
    assert _top(dialog)[-1].startswith("链接文件缺少的区域")
    missing = next(i for t, i in by_text.items() if t.startswith("LMU2_CACHED_DATA"))
    assert missing.text(4) == "链接文件里没有这个执行区域" and "startup.c:2" in missing.text(3)


def test_export_carries_references(qtbot, tmp_path, monkeypatch):
    target = tmp_path / "layout.md"
    monkeypatch.setattr(dialog_module.QFileDialog, "getSaveFileName", lambda *a, **k: (str(target), ""))
    monkeypatch.setattr(dialog_module.QMessageBox, "information", lambda *a, **k: None)
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_symbols_result())
    dialog.export_layout()
    text = Path(target).read_text(encoding="utf-8")
    assert "- 被引用：复制、基址、界限、加载地址（startup.c:1）" in text
    assert "### LMU2_CACHED_DATA" in text and "- 无代码引用" in text
