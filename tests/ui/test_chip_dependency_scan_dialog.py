"""Chip dependency scan dialog: settings, background scan, filters, export."""
from pathlib import Path
from types import SimpleNamespace

from autosar_configurator.core.hardware import chip_dependency_scan as scan
from autosar_configurator.core.hardware.chip_dependency_scan import Finding, ScanResult
from autosar_configurator.ui.dialogs import chip_dependency_scan_dialog as dialog_module
from autosar_configurator.ui.dialogs.chip_dependency_scan_dialog import (
    ChipDependencyScanDialog, parse_keywords, scan_dir_entry)


def _result():
    return ScanResult(
        findings=[
            Finding(scan.CHECK, "templates/Port/src/Port_PBcfg.c", 81,
                    "IF \"ResourceSubderivative != 'THA6206_LFBGA292'\"", ("THA6206_LFBGA292",)),
            Finding(scan.CHECK, "../OS_Kernel/Os/isr/Os_isr_hal.c", 215, "#ifdef OS_THA6206",
                    ("OS_THA6206",)),
            Finding(scan.DEFAULT_BRANCH, "templates/Os/Os/isr/Os_isr_Lcfg.c", 362, "[!ELSE!]",
                    ("Os_THA6206",), "对应第 359 行的 IF；新芯片会走这个分支"),
            Finding(scan.COVERAGE, "Os.xdm", 0,
                    "Os.OsResourceSubderivative = Os_SC300：芯片库中没有声明此值的芯片", ("Os_SC300",)),
        ],
        keywords=["THA6206"], files_scanned=3)


def _project(tmp_path):
    return SimpleNamespace(path=tmp_path / "p.dpa", chip_scan_dirs=["../OS_Kernel"],
                           chip_scan_keywords=["THA6XXX"], module_defs={}, module_managers={})


def test_helpers(tmp_path):
    assert parse_keywords(" A， B,,C ") == ["A", "B", "C"]
    assert scan_dir_entry(str(tmp_path / "k"), tmp_path / "proj") == "../k"


def test_settings_shown_and_saved(qtbot, tmp_path):
    project = _project(tmp_path)
    dialog = ChipDependencyScanDialog(project)
    qtbot.addWidget(dialog)
    assert dialog.scan_dirs() == ["../OS_Kernel"]
    assert dialog.keyword_edit.text() == "THA6XXX"

    dialog.add_dir(str(tmp_path / "SDK"))
    dialog.add_dir(str(tmp_path / "SDK"))                    # no duplicate
    dialog.keyword_edit.setText("THA6XXX, NEWCHIP")
    with qtbot.waitSignal(dialog.settings_changed):
        dialog.reject()
    assert project.chip_scan_dirs == ["../OS_Kernel", "SDK"]
    assert project.chip_scan_keywords == ["THA6XXX", "NEWCHIP"]


def test_background_scan_fills_tree(qtbot, tmp_path, monkeypatch):
    calls = {}

    def fake_scan(project, extra_dirs, extra_keywords, progress):
        calls["args"] = (list(extra_dirs), list(extra_keywords))
        progress(0, 1, "x.c")
        return _result()

    monkeypatch.setattr(dialog_module, "scan_project", fake_scan)
    dialog = ChipDependencyScanDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.start_scan()
    qtbot.waitUntil(lambda: dialog.result is not None, timeout=5000)
    assert calls["args"] == (["../OS_Kernel"], ["THA6XXX"])
    assert dialog.export_button.isEnabled()
    groups = [dialog.tree.topLevelItem(i).text(0) for i in range(dialog.tree.topLevelItemCount())]
    assert groups == ["芯片名判断（2）", "隐含默认分支（1）", "资源覆盖（1）"]


def test_cancelled_scan(qtbot, tmp_path, monkeypatch):
    def fake_scan(project, extra_dirs, extra_keywords, progress):
        while progress(0, 10, "x.c"):
            pass
        raise scan.ScanCancelled()

    monkeypatch.setattr(dialog_module, "scan_project", fake_scan)
    dialog = ChipDependencyScanDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.start_scan()
    dialog.cancel_scan()
    qtbot.waitUntil(lambda: dialog.scan_button.isEnabled(), timeout=5000)
    assert dialog.result is None and not dialog.export_button.isEnabled()
    assert dialog.progress_bar.format() == "已取消"


def test_filters_and_checklist(qtbot, tmp_path):
    dialog = ChipDependencyScanDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    assert [dialog.chip_combo.itemText(i) for i in range(dialog.chip_combo.count())] == [
        "全部", "OS_THA6206", "Os_SC300", "Os_THA6206", "THA6206_LFBGA292"]

    dialog.chip_combo.setCurrentText("OS_THA6206")
    assert [f.line for f in dialog.filtered()] == [215]
    dialog.chip_combo.setCurrentText("全部")
    dialog.category_combo.setCurrentIndex(dialog.category_combo.findData(scan.COVERAGE))
    assert len(dialog.filtered()) == 1

    text = dialog.checklist_text()
    assert "## 资源覆盖（1）" in text and "## 芯片名判断" not in text
    assert "- [ ] `Os.xdm` Os.OsResourceSubderivative = Os_SC300" in text


def test_export_writes_file(qtbot, tmp_path, monkeypatch):
    target = tmp_path / "list.md"
    monkeypatch.setattr(dialog_module.QFileDialog, "getSaveFileName",
                        lambda *a, **k: (str(target), ""))
    monkeypatch.setattr(dialog_module.QMessageBox, "information", lambda *a, **k: None)
    dialog = ChipDependencyScanDialog(_project(tmp_path))
    qtbot.addWidget(dialog)
    dialog.show_result(_result())
    dialog.export_checklist()
    assert "- [ ] `../OS_Kernel/Os/isr/Os_isr_hal.c:215` #ifdef OS_THA6206" in \
        Path(target).read_text(encoding="utf-8")


def test_missing_directory_marked(qtbot, tmp_path):
    (tmp_path / "SDK").mkdir()
    project = _project(tmp_path)
    project.chip_scan_dirs = ["../OS_Kernel", "SDK"]
    dialog = ChipDependencyScanDialog(project)
    qtbot.addWidget(dialog)
    assert dialog.dir_list.item(0).toolTip() == "目录不存在，扫描时会跳过"
    assert dialog.dir_list.item(1).toolTip() == ""
