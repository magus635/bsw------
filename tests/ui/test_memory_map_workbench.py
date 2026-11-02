"""Memory map workbench: the settings and the background scan, the diagnostics tab, the
layout tab, the links between them and the exports.

The first 13 tests are those of the two windows the workbench replaces (the memory map
check dialog and the layout dialog, with the layout dialog's link symbol tests), with the
same assertions on the widgets that moved into the tabs.
"""
from pathlib import Path
from types import SimpleNamespace

from PySide6.QtCore import Qt

from autosar_configurator.core.hardware.chip_dependency_scan import ScanCancelled
from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import check
from autosar_configurator.core.memmap.check import CheckResult, Finding, RowPlacement, SectionRow
from autosar_configurator.core.memmap.symbols import merge, scan_needs
from autosar_configurator.ui.dialogs import memory_map_workbench as module
from autosar_configurator.ui.dialogs.memory_map_workbench import DIAGNOSTICS, LAYOUT, MemoryMapWorkbench


# --- data ------------------------------------------------------------------------

def _check_result():
    """The result of the old check dialog tests."""
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


def _layout_result():
    """The result of the old layout dialog tests; the findings are those the rows hold."""
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


def _mixed_result():
    """Findings that sections hold, and findings that belong to no section."""
    result = _layout_result()
    result.findings += [
        Finding(check.UNMAPPED, "Mcal/Can.c", 21, "CAN_START_SEC_CONFIG_DATA_UNSPECIFIED 在 Can_MemMap.h 中没有映射"),
        Finding(check.SYMBOL, "startup.c", 5, "链接文件缺少执行区域 LMU2_CACHED_DATA", possible=True),
        Finding(check.USAGE, "Mcal/Can.c", 30, "CAN_START_SEC_X 没有对应的 STOP"),
    ]
    return result


def _project(tmp_path):
    return SimpleNamespace(path=tmp_path / "p.dpa", memmap_source_dirs=["../Mcal"],
                           memmap_header_dirs=[], memmap_linker_file=None)


def _open(qtbot, tmp_path, result=None):
    workbench = MemoryMapWorkbench(_project(tmp_path))
    qtbot.addWidget(workbench)
    if result is not None:
        workbench.show_result(result)
    return workbench


def _top(tree):
    return [tree.topLevelItem(i).text(0) for i in range(tree.topLevelItemCount())]


def _all_items(tree):
    found, stack = [], [tree.topLevelItem(i) for i in range(tree.topLevelItemCount())]
    while stack:
        item = stack.pop(0)
        found.append(item)
        stack.extend(item.child(i) for i in range(item.childCount()))
    return found


# --- settings (from the check dialog) ---------------------------------------------

def test_settings_shown_and_saved(qtbot, tmp_path):
    project = _project(tmp_path)
    workbench = MemoryMapWorkbench(project)
    qtbot.addWidget(workbench)
    assert workbench.source_dirs.entries() == ["../Mcal"]
    assert workbench.source_dirs.list.item(0).toolTip() == "目录不存在，扫描时会跳过"

    workbench.source_dirs.add(str(tmp_path / "SDK"))
    workbench.source_dirs.add(str(tmp_path / "SDK"))                # no duplicate
    workbench.header_dirs.add(str(tmp_path / "CommonFile" / "Memmap"))
    workbench.set_linker_file(str(tmp_path / "generateCode" / "Os" / "scatter.scat"))
    with qtbot.waitSignal(workbench.settings_changed):
        workbench.reject()
    assert project.memmap_source_dirs == ["../Mcal", "SDK"]
    assert project.memmap_header_dirs == ["CommonFile/Memmap"]
    assert project.memmap_linker_file == "generateCode/Os/scatter.scat"


def test_background_scan_fills_the_diagnostics_tab(qtbot, tmp_path, monkeypatch):
    def fake_check(project, progress):
        progress(0, 1, "x.c")
        return _check_result()

    monkeypatch.setattr(module, "check_project", fake_check)
    workbench = _open(qtbot, tmp_path)
    workbench.start_scan()
    qtbot.waitUntil(lambda: workbench.result is not None, timeout=5000)
    assert workbench.diagnostics.export_button.isEnabled()
    assert _top(workbench.diagnostics.tree) == [
        "用到但没有映射的段（1）", "核心数据不在本核心内存（1）", "未显式放置的段（1）"]
    core = workbench.diagnostics.tree.topLevelItem(1).child(0).child(0)
    assert core.text(0) == "第 246 行" and core.text(1).endswith("（可能）")
    assert "待确认" in workbench.notes_label.text()


def test_cancelled_scan(qtbot, tmp_path, monkeypatch):
    def fake_check(project, progress):
        while progress(0, 10, "x.c"):
            pass
        raise ScanCancelled()

    monkeypatch.setattr(module, "check_project", fake_check)
    workbench = _open(qtbot, tmp_path)
    workbench.start_scan()
    workbench.cancel_scan()
    qtbot.waitUntil(lambda: workbench.scan_button.isEnabled(), timeout=5000)
    assert workbench.result is None and not workbench.diagnostics.export_button.isEnabled()
    assert workbench.progress_bar.format() == "已取消"


def test_category_filter_and_checklist_export(qtbot, tmp_path, monkeypatch):
    target = tmp_path / "list.md"
    monkeypatch.setattr(module.QFileDialog, "getSaveFileName", lambda *a, **k: (str(target), ""))
    monkeypatch.setattr(module.QMessageBox, "information", lambda *a, **k: None)
    workbench = _open(qtbot, tmp_path, _check_result())
    diagnostics = workbench.diagnostics
    diagnostics.category_combo.setCurrentIndex(diagnostics.category_combo.findData(check.WILDCARD))
    assert len(diagnostics.filtered()) == 1
    workbench.export_checklist()
    text = Path(target).read_text(encoding="utf-8")
    assert "## 未显式放置的段（1）" in text and "## 用到但没有映射的段" not in text
    assert ("- [ ] `generateCode/Os/Default/Os/scatter.scat:246` .mcal_bss_asil_d_unspecified_core0 "
            "未显式放置") in text


# --- layout tab (from the layout dialog) -------------------------------------------

def test_default_grouping_is_physical_region(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _layout_result())
    tab = workbench.layout_tab
    assert tab.mode() == "region"
    assert _top(tab.tree)[0].startswith("CPUXPFLASH0")
    assert _top(tab.tree)[1].startswith("GMU_NORMAL")
    region = tab.tree.topLevelItem(1).child(0)
    assert region.text(0) == "UNDEFINE_RAM_BSS @ 0x10000000（2）"
    assert tab.summary_label.text() == "输出段 3 / 3，有问题 2"
    assert tab.export_button.isEnabled()


def test_switch_to_module_grouping(qtbot, tmp_path):
    tab = _open(qtbot, tmp_path, _layout_result()).layout_tab
    tab.mode_combo.setCurrentIndex(tab.mode_combo.findData("module"))
    assert _top(tab.tree) == ["CAN（3）", "SPI（1）"]
    assert tab.tree.topLevelItem(1).child(0).text(0) == ".mcal_bss_asil_d_unspecified_core0"


def test_layout_filters(qtbot, tmp_path):
    tab = _open(qtbot, tmp_path, _layout_result()).layout_tab
    assert [tab.module_combo.itemText(i) for i in range(tab.module_combo.count())] == ["全部", "CAN", "SPI"]
    tab.only_findings.setChecked(True)
    assert tab.summary_label.text() == "输出段 2 / 3，有问题 2"
    tab.core_combo.setCurrentIndex(tab.core_combo.findData(0))
    assert tab.summary_label.text() == "输出段 1 / 3，有问题 1"
    tab.only_findings.setChecked(False)
    tab.core_combo.setCurrentIndex(0)
    tab.kind_combo.setCurrentIndex(tab.kind_combo.findData("TEXT"))
    assert tab.summary_label.text() == "输出段 1 / 3，有问题 0"


def test_selecting_a_row_shows_its_details(qtbot, tmp_path):
    tab = _open(qtbot, tmp_path, _layout_result()).layout_tab
    row = tab.tree.topLevelItem(1).child(0).child(1)
    assert row.data(0, Qt.UserRole).output == ".mcal_bss_asil_d_unspecified_core0"
    tab.tree.setCurrentItem(row)
    text = "\n".join(tab.detail.topLevelItem(i).text(0) for i in range(tab.detail.topLevelItemCount()))
    assert "映射自：CAN_START_SEC_Y, SPI_START_SEC_Y" in text
    assert "使用：Mcal/Spi.c:4" in text and "核心 0 的" in text


def test_layout_export_follows_grouping_and_filter(qtbot, tmp_path, monkeypatch):
    target = tmp_path / "layout.md"
    monkeypatch.setattr(module.QFileDialog, "getSaveFileName", lambda *a, **k: (str(target), ""))
    monkeypatch.setattr(module.QMessageBox, "information", lambda *a, **k: None)
    workbench = _open(qtbot, tmp_path, _layout_result())
    tab = workbench.layout_tab
    tab.mode_combo.setCurrentIndex(tab.mode_combo.findData("module"))
    tab.module_combo.setCurrentIndex(tab.module_combo.findData("SPI"))
    workbench.export_layout()
    text = Path(target).read_text(encoding="utf-8")
    assert "- 分组：按模块；过滤：模块 SPI；输出段 1 / 3" in text


def test_execution_regions_show_references_and_missing_group(qtbot, tmp_path):
    tab = _open(qtbot, tmp_path, _symbols_result()).layout_tab
    by_text = {item.text(0): item for item in _all_items(tab.tree)}
    referenced = next(i for t, i in by_text.items() if t.startswith("UNDEFINE_RAM_DATA @ 0x10000000"))
    assert referenced.text(3) == "被引用：复制、基址、界限、加载地址（startup.c:1）"
    unreferenced = next(i for t, i in by_text.items() if t.startswith("NOBODY_USES_ME"))
    assert unreferenced.text(3) == "无代码引用" and unreferenced.text(4) == ""
    assert _top(tab.tree)[-1].startswith("链接文件缺少的区域")
    missing = next(i for t, i in by_text.items() if t.startswith("LMU2_CACHED_DATA"))
    assert missing.text(4) == "链接文件里没有这个执行区域" and "startup.c:2" in missing.text(3)


def test_layout_export_carries_references(qtbot, tmp_path, monkeypatch):
    target = tmp_path / "layout.md"
    monkeypatch.setattr(module.QFileDialog, "getSaveFileName", lambda *a, **k: (str(target), ""))
    monkeypatch.setattr(module.QMessageBox, "information", lambda *a, **k: None)
    workbench = _open(qtbot, tmp_path, _symbols_result())
    workbench.export_layout()
    text = Path(target).read_text(encoding="utf-8")
    assert "- 被引用：复制、基址、界限、加载地址（startup.c:1）" in text
    assert "### LMU2_CACHED_DATA" in text and "- 无代码引用" in text


# --- one scan, two tabs ------------------------------------------------------------

def test_one_scan_feeds_both_tabs(qtbot, tmp_path, monkeypatch):
    calls = []

    def fake_check(project, progress):
        calls.append(1)
        progress(0, 1, "x.c")
        return _mixed_result()

    monkeypatch.setattr(module, "check_project", fake_check)
    workbench = _open(qtbot, tmp_path)
    workbench.start_scan()
    qtbot.waitUntil(lambda: workbench.result is not None, timeout=5000)
    assert len(calls) == 1
    assert workbench.diagnostics.result is workbench.layout_tab.result is workbench.result
    assert workbench.diagnostics.tree.topLevelItemCount() > 0 and workbench.layout_tab.tree.topLevelItemCount() > 0


def test_cancelled_scan_leaves_both_tabs_empty(qtbot, tmp_path, monkeypatch):
    def fake_check(project, progress):
        while progress(0, 10, "x.c"):
            pass
        raise ScanCancelled()

    monkeypatch.setattr(module, "check_project", fake_check)
    workbench = _open(qtbot, tmp_path)
    workbench.start_scan()
    workbench.cancel_scan()
    qtbot.waitUntil(lambda: workbench.scan_button.isEnabled(), timeout=5000)
    assert workbench.diagnostics.tree.topLevelItemCount() == 0
    assert workbench.layout_tab.tree.topLevelItemCount() == 0
    assert not workbench.diagnostics.export_button.isEnabled()
    assert not workbench.layout_tab.export_button.isEnabled()


def test_changed_settings_mark_the_result_stale_without_scanning(qtbot, tmp_path, monkeypatch):
    calls = []
    monkeypatch.setattr(module, "check_project", lambda p, progress: calls.append(1) or _layout_result())
    workbench = _open(qtbot, tmp_path)
    workbench.start_scan()
    qtbot.waitUntil(lambda: workbench.result is not None, timeout=5000)
    assert not workbench.stale_label.isVisible() or workbench.stale_label.isHidden()
    workbench.source_dirs.add(str(tmp_path / "SDK"))
    assert not workbench.stale_label.isHidden()
    assert workbench.result is not None and len(calls) == 1          # the result stays, nothing rescans
    workbench.source_dirs.list.setCurrentRow(workbench.source_dirs.list.count() - 1)
    workbench.source_dirs.list.item(workbench.source_dirs.list.count() - 1).setSelected(True)
    workbench.source_dirs._remove()
    assert workbench.stale_label.isHidden()                          # back to what was scanned


def test_no_stale_notice_before_any_scan(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path)
    workbench.source_dirs.add(str(tmp_path / "SDK"))
    assert workbench.stale_label.isHidden()


# --- severity in the diagnostics tab -------------------------------------------------

def test_severity_filter(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    diagnostics = workbench.diagnostics
    diagnostics.severity_combo.setCurrentIndex(diagnostics.severity_combo.findData(check.ERROR))
    shown = diagnostics.filtered()
    assert shown and all(f.severity == check.ERROR for f in shown)
    assert {f.category for f in shown} == {check.UNMAPPED, check.USAGE}
    assert diagnostics.summary_label.text() == f"错误 {len(shown)}，警告 0，提示 0"


def test_severity_shown_in_the_finding_text(qtbot, tmp_path):
    diagnostics = _open(qtbot, tmp_path, _mixed_result()).diagnostics
    texts = [item.text(1) for item in _all_items(diagnostics.tree) if item.data(0, Qt.UserRole) is not None]
    assert any(t.startswith("[错误]") for t in texts)
    assert any(t.startswith("[警告]") and t.endswith("（可能）") for t in texts)      # possible: one level lower


# --- the layout tab does not hide findings without a section ---------------------------

def test_summary_row_counts_findings_without_a_section(qtbot, tmp_path):
    tab = _open(qtbot, tmp_path, _mixed_result()).layout_tab
    assert not tab.loose_row.isHidden()
    assert tab.loose_label.text() == "另有 3 条发现不对应某个输出段（错误 2，警告 1），在诊断页签查看"


def test_summary_row_stays_while_filtering(qtbot, tmp_path):
    tab = _open(qtbot, tmp_path, _mixed_result()).layout_tab
    tab.only_findings.setChecked(True)
    tab.kind_combo.setCurrentIndex(tab.kind_combo.findData("TEXT"))      # no section left
    assert tab.summary_label.text() == "输出段 0 / 3，有问题 0"
    assert not tab.loose_row.isHidden() and "另有 3 条" in tab.loose_label.text()


def test_no_summary_row_when_every_finding_has_a_section(qtbot, tmp_path):
    tab = _open(qtbot, tmp_path, _layout_result()).layout_tab
    assert tab.loose_row.isHidden()


def test_summary_button_shows_those_categories_in_the_diagnostics(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    workbench.layout_tab.loose_button.click()
    assert workbench.tabs.currentIndex() == DIAGNOSTICS
    groups = _top(workbench.diagnostics.tree)
    assert groups == ["用到但没有映射的段（1）", "段声明写法问题（1）", "链接符号缺失（1）"]


# --- locating across the tabs ---------------------------------------------------------

def test_locate_a_section_finding_in_the_layout(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    workbench.layout_tab.only_findings.setChecked(True)
    workbench.layout_tab.kind_combo.setCurrentIndex(workbench.layout_tab.kind_combo.findData("TEXT"))
    core = next(f for f in workbench.result.findings if f.category == check.CORE)
    workbench.diagnostics.select_finding(core)
    assert workbench.diagnostics.locate_button.isEnabled()
    workbench.diagnostics.locate_button.click()
    assert workbench.tabs.currentIndex() == LAYOUT
    assert workbench.layout_tab.kind_combo.currentData() is None            # filters cleared
    assert not workbench.layout_tab.only_findings.isChecked()
    assert workbench.layout_tab.tree.currentItem().data(0, Qt.UserRole).output == (
        ".mcal_bss_asil_d_unspecified_core0")


def test_a_finding_without_a_section_cannot_be_located(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    symbol = next(f for f in workbench.result.findings if f.category == check.SYMBOL)
    workbench.diagnostics.select_finding(symbol)
    assert not workbench.diagnostics.locate_button.isEnabled()
    assert workbench.diagnostics.locate_label.text() == "该发现不对应某个输出段，只能在诊断页签查看"


def test_locate_from_the_layout_details_in_the_diagnostics(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    tab = workbench.layout_tab
    row = tab.tree.topLevelItem(1).child(0).child(1)
    tab.tree.setCurrentItem(row)
    findings = tab.detail_findings()
    assert [f.category for f in findings] == [check.CORE]
    workbench.tabs.setCurrentIndex(LAYOUT)
    for i in range(tab.detail.topLevelItemCount()):
        if tab.detail.topLevelItem(i).data(0, Qt.UserRole) is not None:
            tab._detail_activated(tab.detail.topLevelItem(i))
    assert workbench.tabs.currentIndex() == DIAGNOSTICS
    assert workbench.diagnostics.selected_finding() is findings[0]


def test_locating_widens_the_diagnostics_filter(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    diagnostics = workbench.diagnostics
    diagnostics.severity_combo.setCurrentIndex(diagnostics.severity_combo.findData(check.ERROR))
    core = next(f for f in workbench.result.findings if f.category == check.CORE)
    assert core not in diagnostics.filtered()
    workbench.locate_in_diagnostics(core)
    assert diagnostics.selected_finding() is core and diagnostics.severity_combo.currentData() is None


# --- exports and results -----------------------------------------------------------------

def test_checklist_header_has_the_counts(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    counts = workbench.result.severity_counts()
    assert (f"- 发现：错误 {counts[check.ERROR]}，警告 {counts[check.WARNING]}，"
            f"提示 {counts[check.INFO]}") in workbench.checklist_text()


def test_a_new_result_replaces_the_selection(qtbot, tmp_path):
    workbench = _open(qtbot, tmp_path, _mixed_result())
    workbench.layout_tab.tree.setCurrentItem(workbench.layout_tab.tree.topLevelItem(0).child(0))
    workbench.show_result(_check_result())
    assert workbench.layout_tab.detail.topLevelItemCount() == 0
    assert workbench.diagnostics.selected_finding() is None


def test_unchecked_layout_in_the_window(qtbot, tmp_path):
    """The T1 case: only generateCode was added, no linker file. The sections say that
    their placement was not checked, not that no region receives them."""
    result = _layout_result()
    result.rows[0].placement = None
    result.unchecked_reason = check.NO_LINKER_FILE
    tab = _open(qtbot, tmp_path, result).layout_tab
    groups = _top(tab.tree)
    assert any(g.startswith("未检查放置") for g in groups) and not any(g.startswith("没有区域接收") for g in groups)
    unchecked = next(i for i in _all_items(tab.tree) if i.text(0) == ".mcal_bss_asil_d_unspecified")
    assert unchecked.text(3) == "未检查放置（没有链接文件）"
    tab.tree.setCurrentItem(unchecked)
    text = "\n".join(tab.detail.topLevelItem(i).text(0) for i in range(tab.detail.topLevelItemCount()))
    assert "放置：未检查放置（没有链接文件）" in text
