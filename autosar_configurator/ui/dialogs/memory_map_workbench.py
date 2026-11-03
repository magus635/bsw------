"""Memory map workbench: one window for the check and the layout.

The settings (source and MemMap header directories, linker file) and one background scan
are shared; the "诊断" tab lists the findings by category, the "布局" tab lays the output
sections out by physical region or by module.  Both only read the same ``CheckResult``.
The scan reads; nothing in the project or in the files it reads is changed, and the
settings are saved with the project when the window closes.  The "配置" tab edits the memory
layout configuration (``memorymap.json``) through a ``LayoutSession``; unsaved changes are
asked about when the window closes.
"""
import logging
from pathlib import Path
from typing import List, Optional

from PySide6.QtCore import QObject, Qt, QThread, Signal
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QDialog,
    QFileDialog,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QListWidget,
    QMessageBox,
    QProgressBar,
    QPushButton,
    QTabWidget,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...core.hardware.chip_dependency_scan import ScanCancelled, resolve_scan_dir
from ...core.memmap import layout
from ...core.memmap.check import (
    CATEGORIES,
    CATEGORY_LABELS,
    ERROR,
    GENERATION_DIR,
    INFO,
    NO_SECTION_CATEGORIES,
    SEVERITIES,
    SEVERITY_LABELS,
    STATIC_NOTE,
    WARNING,
    CheckResult,
    Finding,
    check_project,
    to_markdown,
)
from ...core.memmap.config import ConfigError
from ...core.memmap.layout import BY_MODULE, BY_REGION, LayoutFilter
from ...core.memmap.session import LayoutSession
from .chip_dependency_scan_dialog import scan_dir_entry
from .memory_map_config_tab import ConfigTab

logger = logging.getLogger(__name__)

ALL = "全部"
KINDS = ("TEXT", "RODATA", "DATA", "BSS")
DIAGNOSTICS, LAYOUT, CONFIG = 0, 1, 2
SEVERITY_COLORS = {ERROR: QColor("#b00020"), WARNING: QColor("#a65e00"), INFO: QColor("gray")}
STALE_NOTICE = "设置已改动，结果可能过时，请重新开始扫描。"
NO_SECTION_REASON = "该发现不对应某个输出段，只能在诊断页签查看"


class _CheckWorker(QObject):
    progress = Signal(int, int, str)
    finished = Signal(object)        # CheckResult, or None when cancelled
    failed = Signal(str)

    def __init__(self, project):
        super().__init__()
        self.project = project
        self.cancelled = False

    def _progress(self, index, total, path):
        self.progress.emit(index, total, path)
        return not self.cancelled

    def run(self):
        try:
            result = check_project(self.project, progress=self._progress)
        except ScanCancelled:
            self.finished.emit(None)
        except Exception as e:  # shown to the user, never crashes the UI
            logger.exception("Memory map scan failed")
            self.failed.emit(str(e))
        else:
            self.finished.emit(result)


class _DirList(QHBoxLayout):
    """A directory list with add and remove buttons."""

    def __init__(self, workbench: "MemoryMapWorkbench", entries: List[str], title: str):
        super().__init__()
        self.workbench, self.title = workbench, title
        self.list = QListWidget()
        self.list.setSelectionMode(QAbstractItemView.ExtendedSelection)
        self.list.setMaximumHeight(90)
        self.list.addItems(entries)
        self.addWidget(self.list, 1)
        buttons = QVBoxLayout()
        self.add_button = QPushButton("添加目录…")
        self.add_button.clicked.connect(self._choose)
        self.remove_button = QPushButton("移除")
        self.remove_button.clicked.connect(self._remove)
        buttons.addWidget(self.add_button)
        buttons.addWidget(self.remove_button)
        buttons.addStretch()
        self.addLayout(buttons)
        self.mark_missing()

    def entries(self) -> List[str]:
        return [self.list.item(i).text() for i in range(self.list.count())]

    def mark_missing(self):
        """Directories that do not exist are shown red (the scan skips them)."""
        for i in range(self.list.count()):
            item = self.list.item(i)
            missing = not resolve_scan_dir(item.text(), self.workbench.base).is_dir()
            item.setForeground(QColor("red") if missing else self.workbench.palette().text().color())
            item.setToolTip("目录不存在，扫描时会跳过" if missing else "")

    def _choose(self):
        directory = QFileDialog.getExistingDirectory(self.workbench, self.title,
                                                     str(self.workbench.base or ""))
        if directory:
            self.add(directory)

    def add(self, directory: str):
        entry = scan_dir_entry(directory, self.workbench.base)
        if entry not in self.entries():
            self.list.addItem(entry)
            self.mark_missing()
            self.workbench.settings_edited()

    def _remove(self):
        for item in self.list.selectedItems():
            self.list.takeItem(self.list.row(item))
        self.workbench.settings_edited()


def _row_text(findings: List[Finding]) -> str:
    return "；".join(f.text + ("（可能）" if f.possible else "") for f in findings)


class DiagnosticsTab(QWidget):
    """The findings by category; filters by category and severity; the checklist export."""

    show_in_layout = Signal(object)         # a Finding

    def __init__(self, parent=None):
        super().__init__(parent)
        self.result: Optional[CheckResult] = None
        self._has_section = set()           # ids of the findings a section row holds
        outer = QVBoxLayout(self)
        row = QHBoxLayout()
        row.addWidget(QLabel("类别："))
        self.category_combo = QComboBox()
        self.category_combo.addItem(ALL, None)
        for category in CATEGORIES:
            self.category_combo.addItem(CATEGORY_LABELS[category], category)
        row.addWidget(self.category_combo)
        row.addWidget(QLabel("级别："))
        self.severity_combo = QComboBox()
        self.severity_combo.addItem(ALL, None)
        for severity in SEVERITIES:
            self.severity_combo.addItem(SEVERITY_LABELS[severity], severity)
        row.addWidget(self.severity_combo)
        row.addStretch()
        self.summary_label = QLabel("")
        row.addWidget(self.summary_label)
        outer.addLayout(row)
        self.category_combo.currentIndexChanged.connect(self.refill)
        self.severity_combo.currentIndexChanged.connect(self.refill)

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["位置", "内容", "说明"])
        self.tree.setColumnWidth(0, 360)
        self.tree.setColumnWidth(1, 470)
        self.tree.currentItemChanged.connect(self._selection_changed)
        outer.addWidget(self.tree, 1)

        row = QHBoxLayout()
        self.locate_button = QPushButton("在布局中显示")
        self.locate_button.setEnabled(False)
        self.locate_button.clicked.connect(self._locate)
        self.locate_label = QLabel("")
        self.locate_label.setStyleSheet("color: gray;")
        row.addWidget(self.locate_button)
        row.addWidget(self.locate_label, 1)
        self.export_button = QPushButton("导出检查清单…")
        self.export_button.setEnabled(False)
        row.addWidget(self.export_button)
        outer.addLayout(row)

    # --- result ----------------------------------------------------------------

    def set_result(self, result: Optional[CheckResult]):
        self.result = result
        self._has_section = ({id(f) for r in result.rows for f in r.findings} if result else set())
        self.export_button.setEnabled(result is not None)
        self.refill()

    def filtered(self) -> List[Finding]:
        if self.result is None:
            return []
        category, severity = self.category_combo.currentData(), self.severity_combo.currentData()
        return [f for f in self.result.findings
                if (category is None or f.category == category)
                and (severity is None or f.severity == severity)]

    def set_filter(self, categories=None, severity=None):
        """Show only these categories (none: all) and this severity (none: all)."""
        self._only_categories = tuple(categories) if categories else None
        self.category_combo.blockSignals(True)
        self.category_combo.setCurrentIndex(0)
        self.category_combo.blockSignals(False)
        self.severity_combo.setCurrentIndex(self.severity_combo.findData(severity))
        self.refill()

    _only_categories = None

    def refill(self):
        self.tree.clear()
        self.locate_button.setEnabled(False)
        self.locate_label.setText("")
        if self.result is None:
            self.summary_label.setText("")
            return
        findings = self.filtered()
        if self._only_categories and self.category_combo.currentData() is None:
            findings = [f for f in findings if f.category in self._only_categories]
        counts = self.result.severity_counts(findings)
        self.summary_label.setText("，".join(f"{SEVERITY_LABELS[s]} {counts[s]}" for s in SEVERITIES)
                                   if findings else "没有发现问题")
        for category in CATEGORIES:
            items = [f for f in findings if f.category == category]
            if not items:
                continue
            group = QTreeWidgetItem([f"{CATEGORY_LABELS[category]}（{len(items)}）"])
            self.tree.addTopLevelItem(group)
            files = {}
            for f in items:
                parent = files.get(f.path)
                if parent is None:
                    parent = files[f.path] = QTreeWidgetItem([f.path])
                    group.addChild(parent)
                where = f"第 {f.line} 行" if f.line else ""
                text = f"[{SEVERITY_LABELS[f.severity]}] {f.text}" + ("（可能）" if f.possible else "")
                child = QTreeWidgetItem([where, text, f.note])
                child.setData(0, Qt.UserRole, f)
                child.setForeground(1, SEVERITY_COLORS[f.severity])
                child.setToolTip(1, text)
                child.setToolTip(2, f.note)
                parent.addChild(child)
            for parent in files.values():
                parent.setText(0, f"{parent.text(0)}（{parent.childCount()}）")
            group.setExpanded(len(items) <= 30)
        if self.result.skipped:
            group = QTreeWidgetItem([f"未扫描（超过 2 MB）（{len(self.result.skipped)}）"])
            for path in self.result.skipped:
                group.addChild(QTreeWidgetItem([path]))
            self.tree.addTopLevelItem(group)

    # --- locate ----------------------------------------------------------------

    def selected_finding(self) -> Optional[Finding]:
        item = self.tree.currentItem()
        return item.data(0, Qt.UserRole) if item is not None else None

    def select_finding(self, finding: Finding) -> bool:
        """Select ``finding`` (by identity), widening the filters if they hide it."""
        if self.result is None:
            return False
        if finding not in self.filtered():
            self.category_combo.blockSignals(True)
            self.severity_combo.blockSignals(True)
            self.category_combo.setCurrentIndex(0)
            self.severity_combo.setCurrentIndex(0)
            self.category_combo.blockSignals(False)
            self.severity_combo.blockSignals(False)
            self._only_categories = None
            self.refill()
        stack = [self.tree.topLevelItem(i) for i in range(self.tree.topLevelItemCount())]
        while stack:
            item = stack.pop()
            if item.data(0, Qt.UserRole) is finding:
                self.tree.setCurrentItem(item)
                return True
            stack.extend(item.child(i) for i in range(item.childCount()))
        return False

    def _selection_changed(self, *_):
        finding = self.selected_finding()
        if finding is None:
            self.locate_button.setEnabled(False)
            self.locate_label.setText("")
        elif id(finding) in self._has_section:
            self.locate_button.setEnabled(True)
            self.locate_label.setText("")
        else:
            self.locate_button.setEnabled(False)
            self.locate_label.setText(NO_SECTION_REASON)

    def _locate(self):
        finding = self.selected_finding()
        if finding is not None:
            self.show_in_layout.emit(finding)

    def checklist_text(self) -> str:
        return to_markdown(self.result, findings=self.filtered())


class LayoutTab(QWidget):
    """The sections by physical region or by module, with the findings of each."""

    show_in_diagnostics = Signal(object)     # a Finding, or a tuple of categories

    def __init__(self, parent=None):
        super().__init__(parent)
        self.result: Optional[CheckResult] = None
        outer = QVBoxLayout(self)

        self.loose_row = QWidget()
        loose = QHBoxLayout(self.loose_row)
        loose.setContentsMargins(0, 0, 0, 0)
        self.loose_label = QLabel("")
        self.loose_label.setStyleSheet("color: #b00020;")
        self.loose_button = QPushButton("在诊断中查看")
        self.loose_button.clicked.connect(self._show_loose)
        loose.addWidget(self.loose_label, 1)
        loose.addWidget(self.loose_button)
        self.loose_row.setVisible(False)
        outer.addWidget(self.loose_row)

        row = QHBoxLayout()
        row.addWidget(QLabel("分组："))
        self.mode_combo = QComboBox()
        self.mode_combo.addItem("按物理区域", BY_REGION)
        self.mode_combo.addItem("按模块", BY_MODULE)
        row.addWidget(self.mode_combo)
        row.addWidget(QLabel("模块："))
        self.module_combo = QComboBox()
        row.addWidget(self.module_combo)
        row.addWidget(QLabel("核心："))
        self.core_combo = QComboBox()
        row.addWidget(self.core_combo)
        row.addWidget(QLabel("种类："))
        self.kind_combo = QComboBox()
        self.kind_combo.addItem(ALL, None)
        for kind in KINDS:
            self.kind_combo.addItem(kind, kind)
        row.addWidget(self.kind_combo)
        self.only_findings = QCheckBox("只看有问题的")
        row.addWidget(self.only_findings)
        row.addStretch()
        self.summary_label = QLabel("")
        row.addWidget(self.summary_label)
        outer.addLayout(row)
        self._reset_filters()
        for combo in (self.mode_combo, self.module_combo, self.core_combo, self.kind_combo):
            combo.currentIndexChanged.connect(self.refill)
        self.only_findings.toggled.connect(self.refill)

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["输出段 / 区域", "属性", "来源模块", "放置", "问题"])
        for column, width in enumerate((330, 150, 130, 330, 260)):
            self.tree.setColumnWidth(column, width)
        self.tree.currentItemChanged.connect(self._show_detail)
        outer.addWidget(self.tree, 1)

        self.detail = QTreeWidget()
        self.detail.setHeaderLabels(["选中的输出段", "说明"])
        self.detail.setColumnWidth(0, 520)
        self.detail.setMaximumHeight(150)
        self.detail.itemActivated.connect(self._detail_activated)
        outer.addWidget(self.detail)
        self.detail_hint = QLabel("双击问题行，在诊断页签中定位它")
        self.detail_hint.setStyleSheet("color: gray;")
        outer.addWidget(self.detail_hint)

        row = QHBoxLayout()
        row.addStretch()
        self.export_button = QPushButton("导出布局…")
        self.export_button.setEnabled(False)
        row.addWidget(self.export_button)
        outer.addLayout(row)

    def _reset_filters(self):
        for combo in (self.module_combo, self.core_combo):
            combo.blockSignals(True)
            combo.clear()
            combo.addItem(ALL, None)
            combo.blockSignals(False)

    # --- result ----------------------------------------------------------------

    def set_result(self, result: Optional[CheckResult]):
        self.result = result
        self.export_button.setEnabled(result is not None)
        self._reset_filters()
        if result is not None:
            for module in layout.modules_of(result):
                self.module_combo.addItem(module, module)
            for core in layout.cores_of(result):
                self.core_combo.addItem(f"核心 {core}", core)
        self.refill()

    def mode(self) -> str:
        return self.mode_combo.currentData()

    def current_filter(self) -> LayoutFilter:
        return LayoutFilter(self.module_combo.currentData(), self.core_combo.currentData(),
                            self.kind_combo.currentData(), self.only_findings.isChecked())

    def clear_filters(self):
        for combo in (self.module_combo, self.core_combo, self.kind_combo):
            combo.blockSignals(True)
            combo.setCurrentIndex(0)
            combo.blockSignals(False)
        self.only_findings.blockSignals(True)
        self.only_findings.setChecked(False)
        self.only_findings.blockSignals(False)
        self.refill()

    def _row_item(self, row) -> QTreeWidgetItem:
        problems = _row_text(row.findings)
        item = QTreeWidgetItem([row.output, layout.row_attributes(row), "、".join(row.modules),
                                layout.placement_text(row, self.result), problems])
        item.setData(0, Qt.UserRole, row)
        item.setToolTip(4, problems)
        if row.findings:
            worst = min((f.severity for f in row.findings), key=SEVERITIES.index)
            item.setForeground(4, SEVERITY_COLORS[worst])
        return item

    def _update_loose(self):
        """The findings no section holds are not hidden by the section filters."""
        loose = self.result.findings_without_section() if self.result is not None else []
        self.loose_row.setVisible(bool(loose))
        if loose:
            counts = self.result.severity_counts(loose)
            parts = "，".join(f"{SEVERITY_LABELS[s]} {counts[s]}" for s in SEVERITIES if counts[s])
            self.loose_label.setText(f"另有 {len(loose)} 条发现不对应某个输出段（{parts}），在诊断页签查看")

    def refill(self):
        self.tree.clear()
        self.detail.clear()
        self._update_loose()
        if self.result is None:
            self.summary_label.setText("")
            return
        flt = self.current_filter()
        shown = layout.filter_rows(self.result, flt)
        bad = sum(1 for r in shown if r.findings)
        self.summary_label.setText(f"输出段 {len(shown)} / {len(self.result.rows)}，有问题 {bad}")
        if self.mode() == BY_MODULE:
            for group in layout.by_module(self.result, flt):
                top = QTreeWidgetItem([f"{group.name}（{len(group.rows)}）"])
                self.tree.addTopLevelItem(top)
                for row in group.rows:
                    top.addChild(self._row_item(row))
                top.setExpanded(len(group.rows) <= 40)
            return
        for group in layout.by_region(self.result, flt):
            text = group.name + (f"（{group.attributes}）" if group.attributes else "")
            top = QTreeWidgetItem([f"{text}（{group.row_count}）"])
            self.tree.addTopLevelItem(top)
            for execution in group.executions:
                parent = top
                if execution.name:
                    address = f" @ {execution.address:#x}" if execution.address is not None else ""
                    window = f" [{execution.window}]" if execution.window else ""
                    parent = QTreeWidgetItem([f"{execution.name}{address}{window}（{len(execution.rows)}）"])
                    if execution.note:
                        parent.setText(3, execution.note)
                        parent.setToolTip(3, execution.note)
                        if execution.unreferenced:
                            parent.setForeground(3, QColor("gray"))
                    if group.name == layout.MISSING_GROUP:
                        parent.setText(4, "链接文件里没有这个执行区域")
                        parent.setForeground(4, SEVERITY_COLORS[ERROR])
                    top.addChild(parent)
                for row in execution.rows:
                    parent.addChild(self._row_item(row))
                parent.setExpanded(len(execution.rows) <= 40)
            top.setExpanded(True)

    # --- detail and locate -------------------------------------------------------

    def _show_detail(self, current, _previous=None):
        self.detail.clear()
        row = current.data(0, Qt.UserRole) if current is not None else None
        if row is None:
            return
        for text in (f"输出段：{row.output}（{layout.row_attributes(row)}）",
                     f"放置：{layout.placement_text(row, self.result)}",
                     f"映射自：{', '.join(row.names)}"):
            self.detail.addTopLevelItem(QTreeWidgetItem([text]))
        for path, line in row.uses[:10]:
            self.detail.addTopLevelItem(QTreeWidgetItem([f"使用：{path}:{line}"]))
        if len(row.uses) > 10:
            self.detail.addTopLevelItem(QTreeWidgetItem([f"……共 {len(row.uses)} 处"]))
        for f in row.findings:
            item = QTreeWidgetItem([f"[{SEVERITY_LABELS[f.severity]}] {f.text}"
                                    + ("（可能）" if f.possible else ""), f"{f.path}:{f.line}"])
            item.setData(0, Qt.UserRole, f)
            item.setForeground(0, SEVERITY_COLORS[f.severity])
            self.detail.addTopLevelItem(item)

    def detail_findings(self) -> List[Finding]:
        found = []
        for i in range(self.detail.topLevelItemCount()):
            f = self.detail.topLevelItem(i).data(0, Qt.UserRole)
            if f is not None:
                found.append(f)
        return found

    def _detail_activated(self, item, _column=0):
        finding = item.data(0, Qt.UserRole)
        if finding is not None:
            self.show_in_diagnostics.emit(finding)

    def _show_loose(self):
        self.show_in_diagnostics.emit(NO_SECTION_CATEGORIES)

    def select_row_of(self, finding: Finding) -> bool:
        """Select the section row that holds ``finding`` (filters cleared first)."""
        if self.result is None:
            return False
        self.clear_filters()
        stack = [self.tree.topLevelItem(i) for i in range(self.tree.topLevelItemCount())]
        while stack:
            item = stack.pop()
            row = item.data(0, Qt.UserRole)
            if row is not None and any(f is finding for f in row.findings):
                parent = item.parent()
                while parent is not None:
                    parent.setExpanded(True)
                    parent = parent.parent()
                self.tree.setCurrentItem(item)
                return True
            stack.extend(item.child(i) for i in range(item.childCount()))
        return False

    def layout_text(self) -> str:
        return layout.to_markdown(self.result, self.mode(), self.current_filter())


class MemoryMapWorkbench(QDialog):
    """Tools → 内存映射…"""

    settings_changed = Signal()

    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.result: Optional[CheckResult] = None
        self._thread: Optional[QThread] = None
        self._worker: Optional[_CheckWorker] = None
        self._scanned_settings = None
        path = getattr(project, "path", None)
        self.base = (Path(path).parent if path and Path(path).suffix == ".dpa" else
                     Path(path) if path else None)
        self.session = self._open_session(project)
        self.setWindowTitle("内存映射")
        self.resize(1200, 820)
        self._build()

    # --- layout ----------------------------------------------------------------

    def _build(self):
        outer = QVBoxLayout(self)
        outer.addWidget(QLabel(f"源码目录（MCAL、SDK、OS 内核、应用等；工程的 {GENERATION_DIR} 总会被扫描）："))
        self.source_dirs = _DirList(self, list(getattr(self.project, "memmap_source_dirs", []) or []),
                                    "添加源码目录")
        outer.addLayout(self.source_dirs)
        outer.addWidget(QLabel("MemMap 头目录（源码目录中的 *MemMap*.h 也会读取）："))
        self.header_dirs = _DirList(self, list(getattr(self.project, "memmap_header_dirs", []) or []),
                                    "添加 MemMap 头目录")
        outer.addLayout(self.header_dirs)

        row = QHBoxLayout()
        row.addWidget(QLabel("链接文件："))
        self.linker_edit = QLineEdit(getattr(self.project, "memmap_linker_file", None) or "")
        self.linker_edit.setReadOnly(True)
        self.linker_edit.setPlaceholderText("ADS 分散加载文件（.scat），例如生成的 Os/scatter.scat")
        self.linker_edit.textChanged.connect(self.settings_edited)
        row.addWidget(self.linker_edit, 1)
        choose = QPushButton("选择…")
        choose.clicked.connect(self._choose_linker)
        clear = QPushButton("清除")
        clear.clicked.connect(lambda: self.linker_edit.setText(""))
        row.addWidget(choose)
        row.addWidget(clear)
        self.scan_button = QPushButton("开始扫描")
        self.scan_button.clicked.connect(self.start_scan)
        self.cancel_button = QPushButton("取消")
        self.cancel_button.setEnabled(False)
        self.cancel_button.clicked.connect(self.cancel_scan)
        row.addWidget(self.scan_button)
        row.addWidget(self.cancel_button)
        outer.addLayout(row)

        self.progress_bar = QProgressBar()
        self.progress_bar.setTextVisible(True)
        self.progress_bar.setFormat("")
        outer.addWidget(self.progress_bar)
        self.stale_label = QLabel(STALE_NOTICE)
        self.stale_label.setStyleSheet("color: #a65e00; font-weight: bold;")
        self.stale_label.setVisible(False)
        outer.addWidget(self.stale_label)

        self.tabs = QTabWidget()
        self.diagnostics = DiagnosticsTab()
        self.layout_tab = LayoutTab()
        self.tabs.addTab(self.diagnostics, "诊断")
        self.tabs.addTab(self.layout_tab, "布局")
        self.config_tab = ConfigTab()
        self.tabs.addTab(self.config_tab, "配置")
        self.config_tab.set_session(self.session)
        outer.addWidget(self.tabs, 1)
        self.diagnostics.export_button.clicked.connect(self.export_checklist)
        self.layout_tab.export_button.clicked.connect(self.export_layout)
        self.diagnostics.show_in_layout.connect(self.locate_in_layout)
        self.layout_tab.show_in_diagnostics.connect(self.locate_in_diagnostics)

        self.notes_label = QLabel("")
        self.notes_label.setWordWrap(True)
        outer.addWidget(self.notes_label)
        note = QLabel(STATIC_NOTE)
        note.setWordWrap(True)
        note.setStyleSheet("color: gray;")
        outer.addWidget(note)
        row = QHBoxLayout()
        row.addStretch()
        close = QPushButton("关闭")
        close.clicked.connect(self.reject)
        row.addWidget(close)
        outer.addLayout(row)

    # --- settings --------------------------------------------------------------

    def _choose_linker(self):
        path, _ = QFileDialog.getOpenFileName(self, "选择链接文件", str(self.base or ""),
                                              "ADS scatter (*.scat *.sct);;所有文件 (*)")
        if path:
            self.set_linker_file(path)

    def set_linker_file(self, path: str):
        self.linker_edit.setText(scan_dir_entry(path, self.base))

    def _settings(self):
        return (tuple(self.source_dirs.entries()), tuple(self.header_dirs.entries()),
                self.linker_edit.text().strip() or None)

    def settings_edited(self, *_):
        """The result on screen no longer matches the settings: say so, scan nothing."""
        if not hasattr(self, "stale_label"):
            return
        self.stale_label.setVisible(self.result is not None and self._settings() != self._scanned_settings)

    def _store_settings(self):
        sources, headers, linker = list(self._settings()[0]), list(self._settings()[1]), self._settings()[2]
        if (sources != list(getattr(self.project, "memmap_source_dirs", []) or [])
                or headers != list(getattr(self.project, "memmap_header_dirs", []) or [])
                or linker != getattr(self.project, "memmap_linker_file", None)):
            self.project.memmap_source_dirs = sources
            self.project.memmap_header_dirs = headers
            self.project.memmap_linker_file = linker
            self.settings_changed.emit()

    # --- scan ------------------------------------------------------------------

    def start_scan(self):
        self._store_settings()
        self._scanned_settings = self._settings()
        self.stale_label.setVisible(False)
        self.scan_button.setEnabled(False)
        self.cancel_button.setEnabled(True)
        self.diagnostics.export_button.setEnabled(False)
        self.layout_tab.export_button.setEnabled(False)
        self.progress_bar.setRange(0, 0)
        self.progress_bar.setFormat("正在列出文件…")
        self._thread = QThread(self)
        self._worker = _CheckWorker(self.project)
        self._worker.moveToThread(self._thread)
        self._thread.started.connect(self._worker.run)
        self._worker.progress.connect(self._on_progress)
        self._worker.finished.connect(self._on_finished)
        self._worker.failed.connect(self._on_failed)
        self._worker.finished.connect(self._thread.quit)
        self._worker.failed.connect(self._thread.quit)
        self._thread.start()

    def cancel_scan(self):
        if self._worker is not None:
            self._worker.cancelled = True
            self.cancel_button.setEnabled(False)

    def _on_progress(self, index: int, total: int, path: str):
        self.progress_bar.setRange(0, max(total, 1))
        self.progress_bar.setValue(index)
        self.progress_bar.setFormat(f"{index}/{total}  {path}" if path else "正在检查放置…")

    def _scan_ended(self):
        self.scan_button.setEnabled(True)
        self.cancel_button.setEnabled(False)
        self.progress_bar.setRange(0, 1)

    def _on_failed(self, message: str):
        self._scan_ended()
        self.progress_bar.setValue(0)
        self.progress_bar.setFormat("扫描失败")
        QMessageBox.warning(self, "内存映射", f"扫描失败：{message}")

    def _on_finished(self, result: Optional[CheckResult]):
        self._scan_ended()
        if result is None:
            self.progress_bar.setValue(0)
            self.progress_bar.setFormat("已取消")
            return
        self.progress_bar.setValue(1)
        self.progress_bar.setFormat(
            f"已扫描 {result.files_scanned} 个文件，用到的段 {result.sections_used} 个，"
            f"输出段 {len(result.rows)} 个")
        self.show_result(result)

    # --- result ----------------------------------------------------------------

    def show_result(self, result: CheckResult):
        self.result = result
        self.notes_label.setText("\n".join(result.notes))
        self.diagnostics.set_result(result)
        self.layout_tab.set_result(result)
        if self.session is not None:
            try:
                self.session.update(result)
            except Exception:  # noqa: BLE001 - the other tabs must still show the result
                logger.exception("Memory layout configuration could not be prepared")
        self.config_tab.set_result(result)
        self.settings_edited()

    # --- layout configuration ----------------------------------------------------

    @staticmethod
    def _open_session(project) -> Optional[LayoutSession]:
        try:
            return LayoutSession.open(project)
        except Exception:  # noqa: BLE001 - the check and layout tabs work without it
            logger.exception("Memory layout configuration could not be opened")
            return None

    def _ask_save(self) -> int:
        """Yes, No or Cancel; a separate method so tests can answer it."""
        return QMessageBox.question(
            self, "内存映射", "内存布局配置有未保存的改动，是否保存？",
            QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel, QMessageBox.Yes)

    def confirm_close(self) -> bool:
        """Whether the window may close: unsaved configuration changes are saved (Yes),
        dropped (No) or keep the window open (Cancel, or a failed save)."""
        if self.session is None or not self.session.dirty:
            return True
        answer = self._ask_save()
        if answer == QMessageBox.Yes:
            try:
                self.session.save()
            except ConfigError as e:
                QMessageBox.warning(self, "内存映射", f"保存失败：{e}")
                return False
            return True
        return answer == QMessageBox.No

    # --- locate ----------------------------------------------------------------

    def locate_in_layout(self, finding: Finding):
        if self.layout_tab.select_row_of(finding):
            self.tabs.setCurrentIndex(LAYOUT)

    def locate_in_diagnostics(self, target):
        """A finding to select, or a tuple of categories to show."""
        if isinstance(target, Finding):
            if self.diagnostics.select_finding(target):
                self.tabs.setCurrentIndex(DIAGNOSTICS)
            return
        self.diagnostics.set_filter(categories=target)
        self.tabs.setCurrentIndex(DIAGNOSTICS)

    # --- export ----------------------------------------------------------------

    def checklist_text(self) -> str:
        return self.diagnostics.checklist_text()

    def layout_text(self) -> str:
        return self.layout_tab.layout_text()

    def _export(self, title: str, default_name: str, text: str):
        default = str((self.base or Path.cwd()) / default_name)
        path, _ = QFileDialog.getSaveFileName(self, title, default, "Markdown (*.md)")
        if not path:
            return
        try:
            Path(path).write_text(text, encoding="utf-8")
        except OSError as e:
            QMessageBox.warning(self, title, f"写入失败：{e}")
            return
        QMessageBox.information(self, title, f"已导出：{path}")

    def export_checklist(self):
        if self.result is not None:
            self._export("导出检查清单", "内存映射检查清单.md", self.checklist_text())

    def export_layout(self):
        if self.result is not None:
            self._export("导出布局", "内存布局.md", self.layout_text())

    def reject(self):
        if not self.confirm_close():
            return
        self.cancel_scan()
        if self._thread is not None and self._thread.isRunning():
            self._thread.quit()
            self._thread.wait(5000)
        self._store_settings()
        super().reject()
