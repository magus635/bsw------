"""Memory map check dialog: settings, background check, filter, export."""
from pathlib import Path
from types import SimpleNamespace

from autosar_configurator.core.hardware.chip_dependency_scan import ScanCancelled
from autosar_configurator.core.memmap import check
from autosar_configurator.core.memmap.check import CheckResult, Finding
from autosar_configurator.ui.dialogs import memory_map_check_dialog as dialog_module
from autosar_configurator.ui.dialogs.memory_map_check_dialog import MemoryMapCheckDialog


def _result():
    return CheckResult(
        findings=[
            Finding(check.UNMAPPED, "generateCode/Can/Default/src/Can_Lcfg.c", 9,
                    "CAN_START_SEC_CONFIG_DATA_UNSPECIFIED 在 Can_MemMap.h 中没有映射",
                    "编译时会触发 MemMap 的 #error"),
            Finding(check.CORE, "generateCode/Os/Default/Os/scatter.scat", 246,
                    "核心 0 的 .mcal_bss_asil_d_unspecified_core0 放在 UNDEFINE_RAM_BSS，位于 GMU_NORMAL（共享）",
                    possible=True),
            Finding(check.WILDCARD, "generateCode/Os/Default/Os/scatter.scat", 246,
                    ".mcal_bss_asil_d_unspecified_core0 未显式放置，由 UNDEFINE_RAM_BSS 的 *(+BSS) 接收"),
        ],
        source_dirs=["../Mcal", "generateCode"], linker_file="generateCode/Os/Default/Os/scatter.scat",
        files_scanned=3, sections_used=2, notes=["芯片的内存区域数据标记为待确认，核心和缓存检查的结论需人工核对"])


def _project(tmp_path):
    return SimpleNamespace(path=tmp_path / "p.dpa", memmap_source_dirs=["../Mcal"],
                           memmap_header_dirs=[], memmap_linker_file=None)


def test_settings_shown_and_saved(qtbot, tmp_path):
    project = _project(tmp_path)
    dialog = MemoryMapCheckDialog(project)
    qtbot.addWidget(dialog)
    assert dialog.source_dirs.entries() == ["../Mcal"]
    assert dialog.source_dirs.list.item(0).toolTip() == "目录不存在，检查时会跳过"

    dialog.source_dirs.add(str(tmp_path / "SDK"))
    dialog.source_dirs.add(str(tmp_path / "SDK"))                # no duplicate
    dialog.header_dirs.add(str(tmp_path / "CommonFile" / "Memmap"))
    dialog.set_linker_file(str(tmp_path / "generateCode" / "Os" / "scatter.scat"))
    with qtbot.waitSignal(dialog.settings_changed):
        dialog.reject()
    assert project.memmap_source_dirs == ["../Mcal", "SDK"]
    assert project.memmap_header_dirs == ["CommonFile/Memmap"]
    assert project.memmap_linker_file == "generateCode/Os/scatter.scat"


def test_background_check_fills_tree(qtbot, tmp_path, monkeypatch):
    def fake_check(project, progress):
        progress(0, 1, "x.c")
        return _result()

    monkeypatch.setattr(dialog_module, "check_project", fake_check)
    dialog = MemoryMapCheckDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.start_check()
    qtbot.waitUntil(lambda: dialog.result is not None, timeout=5000)
    assert dialog.export_button.isEnabled()
    groups = [dialog.tree.topLevelItem(i).text(0) for i in range(dialog.tree.topLevelItemCount())]
    assert groups == ["用到但没有映射的段（1）", "核心数据不在本核心内存（1）", "未显式放置的段（1）"]
    core = dialog.tree.topLevelItem(1).child(0).child(0)
    assert core.text(0) == "第 246 行" and core.text(1).endswith("（可能）")
    assert "待确认" in dialog.notes_label.text()


def test_cancelled_check(qtbot, tmp_path, monkeypatch):
    def fake_check(project, progress):
        while progress(0, 10, "x.c"):
            pass
        raise ScanCancelled()

    monkeypatch.setattr(dialog_module, "check_project", fake_check)
    dialog = MemoryMapCheckDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.start_check()
    dialog.cancel_check()
    qtbot.waitUntil(lambda: dialog.check_button.isEnabled(), timeout=5000)
    assert dialog.result is None and not dialog.export_button.isEnabled()
    assert dialog.progress_bar.format() == "已取消"


def test_filter_and_export(qtbot, tmp_path, monkeypatch):
    target = tmp_path / "list.md"
    monkeypatch.setattr(dialog_module.QFileDialog, "getSaveFileName",
                        lambda *a, **k: (str(target), ""))
    monkeypatch.setattr(dialog_module.QMessageBox, "information", lambda *a, **k: None)
    dialog = MemoryMapCheckDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    dialog.category_combo.setCurrentIndex(dialog.category_combo.findData(check.WILDCARD))
    assert len(dialog.filtered()) == 1
    dialog.export_checklist()
    text = Path(target).read_text(encoding="utf-8")
    assert "## 未显式放置的段（1）" in text and "## 用到但没有映射的段" not in text
    assert ("- [ ] `generateCode/Os/Default/Os/scatter.scat:246` .mcal_bss_asil_d_unspecified_core0 "
            "未显式放置") in text
