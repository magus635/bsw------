"""Memory layout dialog: grouping, filters, background load, cancel, export."""
from pathlib import Path
from types import SimpleNamespace

from PySide6.QtCore import Qt

from autosar_configurator.core.hardware.chip_dependency_scan import ScanCancelled
from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import check
from autosar_configurator.core.memmap.check import CheckResult, Finding, RowPlacement, SectionRow
from autosar_configurator.ui.dialogs import memory_layout_dialog as dialog_module
from autosar_configurator.ui.dialogs import memory_map_check_dialog as worker_module
from autosar_configurator.ui.dialogs.memory_layout_dialog import MemoryLayoutDialog


def _result():
    wildcard = Finding(check.WILDCARD, "scatter.scat", 29,
                       ".mcal_bss_asil_d_unspecified 未显式放置，由 UNDEFINE_RAM_BSS 的 *(+BSS) 接收")
    core = Finding(check.CORE, "scatter.scat", 29,
                   "核心 0 的 .mcal_bss_asil_d_unspecified_core0 放在 UNDEFINE_RAM_BSS，位于 GMU_NORMAL（共享）")
    rows = [
        SectionRow(".mcal_bss_asil_d_unspecified", "BSS", ("CAN_START_SEC_X",), ("CAN",), None, False,
                   (("Mcal/Can.c", 3),),
                   RowPlacement("UNDEFINE_RAM_BSS", 29, "*(+BSS)", False, 0x10000000, "GMU_NORMAL"),
                   [wildcard]),
        SectionRow(".mcal_bss_asil_d_unspecified_core0", "BSS",
                   ("CAN_START_SEC_Y", "SPI_START_SEC_Y"), ("CAN", "SPI"), 0, False,
                   (("Mcal/Can.c", 9), ("Mcal/Spi.c", 4)),
                   RowPlacement("UNDEFINE_RAM_BSS", 29, "*(+BSS)", False, 0x10000000, "GMU_NORMAL"),
                   [core]),
        SectionRow(".mcal_text_asil_d", "TEXT", ("CAN_START_SEC_Z",), ("CAN",), None, False,
                   (("Mcal/Can.c", 1),),
                   RowPlacement("EX_CODE", 12, "*(+RO-CODE)", False, 0x8000000, "CPUXPFLASH0")),
    ]
    regions = [MemoryRegionDef("CPUXPFLASH0", 0x8000000, 0x300000, "flash"),
               MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram")]
    return CheckResult(findings=[wildcard, core], rows=rows, regions=regions,
                       source_dirs=["../Mcal"], linker_file="scatter.scat", files_scanned=3,
                       notes=["芯片的内存区域数据标记为待确认，核心、缓存和 flash 类型检查的结论需人工核对"])


def _project(tmp_path):
    return SimpleNamespace(path=tmp_path / "p.dpa", memmap_source_dirs=["../Mcal"],
                           memmap_header_dirs=[], memmap_linker_file=None)


def _top(dialog):
    return [dialog.tree.topLevelItem(i).text(0) for i in range(dialog.tree.topLevelItemCount())]


def test_default_grouping_is_physical_region(qtbot, tmp_path):
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    assert dialog.mode() == "region"
    assert _top(dialog) == ["CPUXPFLASH0（0）", "GMU_NORMAL（2）"] or _top(dialog)[0].startswith("CPUXPFLASH0")
    assert _top(dialog)[1].startswith("GMU_NORMAL")
    region = dialog.tree.topLevelItem(1).child(0)
    assert region.text(0) == "UNDEFINE_RAM_BSS @ 0x10000000（2）"
    assert dialog.summary_label.text() == "输出段 3 / 3，有问题 2"
    assert dialog.export_button.isEnabled()


def test_switch_to_module_grouping(qtbot, tmp_path):
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    dialog.mode_combo.setCurrentIndex(dialog.mode_combo.findData("module"))
    assert _top(dialog) == ["CAN（3）", "SPI（1）"]
    assert dialog.tree.topLevelItem(1).child(0).text(0) == ".mcal_bss_asil_d_unspecified_core0"


def test_filters(qtbot, tmp_path):
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    assert [dialog.module_combo.itemText(i) for i in range(dialog.module_combo.count())] == [
        "全部", "CAN", "SPI"]
    dialog.only_findings.setChecked(True)
    assert dialog.summary_label.text() == "输出段 2 / 3，有问题 2"
    dialog.core_combo.setCurrentIndex(dialog.core_combo.findData(0))
    assert dialog.summary_label.text() == "输出段 1 / 3，有问题 1"
    dialog.only_findings.setChecked(False)
    dialog.core_combo.setCurrentIndex(0)
    dialog.kind_combo.setCurrentIndex(dialog.kind_combo.findData("TEXT"))
    assert dialog.summary_label.text() == "输出段 1 / 3，有问题 0"


def test_selecting_a_row_shows_its_details(qtbot, tmp_path):
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    row = dialog.tree.topLevelItem(1).child(0).child(1)
    assert row.data(0, Qt.UserRole).output == ".mcal_bss_asil_d_unspecified_core0"
    dialog.tree.setCurrentItem(row)
    text = dialog.detail.toPlainText()
    assert "映射自：CAN_START_SEC_Y, SPI_START_SEC_Y" in text
    assert "使用：Mcal/Spi.c:4" in text and "核心 0 的" in text


def test_background_load(qtbot, tmp_path, monkeypatch):
    def fake_check(project, progress):
        progress(0, 1, "x.c")
        return _result()

    monkeypatch.setattr(worker_module, "check_project", fake_check)
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.start_load()
    qtbot.waitUntil(lambda: dialog.result is not None, timeout=5000)
    assert dialog.load_button.isEnabled() and dialog.tree.topLevelItemCount() == 2


def test_cancelled_load_shows_nothing(qtbot, tmp_path, monkeypatch):
    def fake_check(project, progress):
        while progress(0, 10, "x.c"):
            pass
        raise ScanCancelled()

    monkeypatch.setattr(worker_module, "check_project", fake_check)
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.start_load()
    dialog.cancel_load()
    qtbot.waitUntil(lambda: dialog.load_button.isEnabled(), timeout=5000)
    assert dialog.result is None and dialog.tree.topLevelItemCount() == 0
    assert not dialog.export_button.isEnabled() and dialog.progress_bar.format() == "已取消"


def test_export_follows_grouping_and_filter(qtbot, tmp_path, monkeypatch):
    target = tmp_path / "layout.md"
    monkeypatch.setattr(dialog_module.QFileDialog, "getSaveFileName", lambda *a, **k: (str(target), ""))
    monkeypatch.setattr(dialog_module.QMessageBox, "information", lambda *a, **k: None)
    dialog = MemoryLayoutDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    dialog.mode_combo.setCurrentIndex(dialog.mode_combo.findData("module"))
    dialog.module_combo.setCurrentIndex(dialog.module_combo.findData("SPI"))
    dialog.export_layout()
    text = Path(target).read_text(encoding="utf-8")
    assert "- 分组：按模块；过滤：模块 SPI；输出段 1 / 3" in text
    assert "## SPI（1）" in text and ".mcal_text_asil_d" not in text
