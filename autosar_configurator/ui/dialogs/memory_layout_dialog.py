"""Memory layout window: the sections of the project laid out by physical region or by
module, with their findings.  Read-only: it runs the memory map check with the
project's settings (set in the memory map check dialog) and only shows the result."""
import logging
from pathlib import Path
from typing import Optional

from PySide6.QtCore import QThread, Qt
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QCheckBox,
    QComboBox,
    QDialog,
    QFileDialog,
    QHBoxLayout,
    QLabel,
    QMessageBox,
    QProgressBar,
    QPushButton,
    QTextEdit,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
)

from ...core.memmap import layout
from ...core.memmap.check import STATIC_NOTE, CheckResult
from ...core.memmap.layout import BY_MODULE, BY_REGION, LayoutFilter
from .memory_map_check_dialog import ALL, _CheckWorker

logger = logging.getLogger(__name__)

PROBLEM_COLOR = QColor("#b00020")
KINDS = ("TEXT", "RODATA", "DATA", "BSS")


class MemoryLayoutDialog(QDialog):
    """Tools → 内存布局…"""

    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.result: Optional[CheckResult] = None
        self._thread: Optional[QThread] = None
        self._worker: Optional[_CheckWorker] = None
        path = getattr(project, "path", None)
        self.base = (Path(path).parent if path and Path(path).suffix == ".dpa" else
                     Path(path) if path else None)
        self.setWindowTitle("内存布局")
        self.resize(1200, 780)
        self._build()

    # --- layout ----------------------------------------------------------------

    def _build(self):
        outer = QVBoxLayout(self)
        row = QHBoxLayout()
        self.load_button = QPushButton("读取布局")
        self.load_button.clicked.connect(self.start_load)
        self.cancel_button = QPushButton("取消")
        self.cancel_button.setEnabled(False)
        self.cancel_button.clicked.connect(self.cancel_load)
        row.addWidget(self.load_button)
        row.addWidget(self.cancel_button)
        row.addWidget(QLabel("目录和链接文件在“检查内存映射”中设置。"))
        row.addStretch()
        outer.addLayout(row)

        self.progress_bar = QProgressBar()
        self.progress_bar.setTextVisible(True)
        self.progress_bar.setFormat("")
        outer.addWidget(self.progress_bar)

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
            combo.currentIndexChanged.connect(self._fill_tree)
        self.only_findings.toggled.connect(self._fill_tree)

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["输出段 / 区域", "属性", "来源模块", "放置", "问题"])
        for column, width in enumerate((330, 150, 130, 330, 260)):
            self.tree.setColumnWidth(column, width)
        self.tree.currentItemChanged.connect(self._show_detail)
        outer.addWidget(self.tree, 1)

        self.detail = QTextEdit()
        self.detail.setReadOnly(True)
        self.detail.setMaximumHeight(130)
        self.detail.setPlaceholderText("选中一个输出段，查看它的映射、使用位置和问题")
        outer.addWidget(self.detail)

        self.notes_label = QLabel("")
        self.notes_label.setWordWrap(True)
        outer.addWidget(self.notes_label)
        note = QLabel(STATIC_NOTE)
        note.setWordWrap(True)
        note.setStyleSheet("color: gray;")
        outer.addWidget(note)

        row = QHBoxLayout()
        row.addStretch()
        self.export_button = QPushButton("导出布局…")
        self.export_button.setEnabled(False)
        self.export_button.clicked.connect(self.export_layout)
        close = QPushButton("关闭")
        close.clicked.connect(self.reject)
        row.addWidget(self.export_button)
        row.addWidget(close)
        outer.addLayout(row)

    def _reset_filters(self):
        for combo in (self.module_combo, self.core_combo):
            combo.blockSignals(True)
            combo.clear()
            combo.addItem(ALL, None)
            combo.blockSignals(False)

    # --- load ------------------------------------------------------------------

    def start_load(self):
        self.load_button.setEnabled(False)
        self.cancel_button.setEnabled(True)
        self.export_button.setEnabled(False)
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

    def cancel_load(self):
        if self._worker is not None:
            self._worker.cancelled = True
            self.cancel_button.setEnabled(False)

    def _on_progress(self, index: int, total: int, path: str):
        self.progress_bar.setRange(0, max(total, 1))
        self.progress_bar.setValue(index)
        self.progress_bar.setFormat(f"{index}/{total}  {path}" if path else "正在检查放置…")

    def _ended(self):
        self.load_button.setEnabled(True)
        self.cancel_button.setEnabled(False)
        self.progress_bar.setRange(0, 1)

    def _on_failed(self, message: str):
        self._ended()
        self.progress_bar.setValue(0)
        self.progress_bar.setFormat("读取失败")
        QMessageBox.warning(self, "内存布局", f"读取失败：{message}")

    def _on_finished(self, result: Optional[CheckResult]):
        self._ended()
        if result is None:
            self.progress_bar.setValue(0)
            self.progress_bar.setFormat("已取消")
            return
        self.progress_bar.setValue(1)
        self.progress_bar.setFormat(f"已扫描 {result.files_scanned} 个文件，输出段 {len(result.rows)} 个")
        self.show_result(result)

    # --- result ----------------------------------------------------------------

    def show_result(self, result: CheckResult):
        self.result = result
        self.export_button.setEnabled(True)
        self.notes_label.setText("\n".join(result.notes))
        self._reset_filters()
        for module in layout.modules_of(result):
            self.module_combo.addItem(module, module)
        for core in layout.cores_of(result):
            self.core_combo.addItem(f"核心 {core}", core)
        self._fill_tree()

    def mode(self) -> str:
        return self.mode_combo.currentData()

    def current_filter(self) -> LayoutFilter:
        return LayoutFilter(self.module_combo.currentData(), self.core_combo.currentData(),
                            self.kind_combo.currentData(), self.only_findings.isChecked())

    @staticmethod
    def _row_item(row) -> QTreeWidgetItem:
        problems = "；".join(f.text + ("（可能）" if f.possible else "") for f in row.findings)
        item = QTreeWidgetItem([row.output, layout.row_attributes(row), "、".join(row.modules),
                                layout.placement_text(row), problems])
        item.setData(0, Qt.UserRole, row)
        item.setToolTip(4, problems)
        if row.findings:
            item.setForeground(4, PROBLEM_COLOR)
        return item

    def _fill_tree(self):
        self.tree.clear()
        self.detail.clear()
        if self.result is None:
            return
        flt = self.current_filter()
        shown = layout.filter_rows(self.result, flt)
        bad = sum(1 for r in shown if r.findings)
        self.summary_label.setText(
            f"输出段 {len(shown)} / {len(self.result.rows)}，有问题 {bad}")
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
                    parent = QTreeWidgetItem([f"{execution.name}{address}（{len(execution.rows)}）"])
                    if execution.note:
                        # the references sit in the placement column, which is wide enough
                        parent.setText(3, execution.note)
                        parent.setToolTip(3, execution.note)
                        if execution.unreferenced:
                            parent.setForeground(3, QColor("gray"))
                    if group.name == layout.MISSING_GROUP:
                        parent.setText(4, "链接文件里没有这个执行区域")
                        parent.setForeground(4, PROBLEM_COLOR)
                    top.addChild(parent)
                for row in execution.rows:
                    parent.addChild(self._row_item(row))
                parent.setExpanded(len(execution.rows) <= 40)
            top.setExpanded(True)

    def _show_detail(self, current, _previous=None):
        row = current.data(0, Qt.UserRole) if current is not None else None
        if row is None:
            self.detail.clear()
            return
        lines = [f"输出段：{row.output}（{layout.row_attributes(row)}）",
                 f"放置：{layout.placement_text(row)}",
                 f"映射自：{', '.join(row.names)}"]
        lines += [f"使用：{path}:{line}" for path, line in row.uses[:10]]
        if len(row.uses) > 10:
            lines.append(f"……共 {len(row.uses)} 处")
        lines += [f"问题：{f.text}{'（可能）' if f.possible else ''}（{f.path}:{f.line}）" for f in row.findings]
        self.detail.setPlainText("\n".join(lines))

    # --- export ----------------------------------------------------------------

    def layout_text(self) -> str:
        return layout.to_markdown(self.result, self.mode(), self.current_filter())

    def export_layout(self):
        if self.result is None:
            return
        default = str((self.base or Path.cwd()) / "内存布局.md")
        path, _ = QFileDialog.getSaveFileName(self, "导出布局", default, "Markdown (*.md)")
        if not path:
            return
        try:
            Path(path).write_text(self.layout_text(), encoding="utf-8")
        except OSError as e:
            QMessageBox.warning(self, "导出布局", f"写入失败：{e}")
            return
        QMessageBox.information(self, "导出布局", f"已导出：{path}")

    def reject(self):
        self.cancel_load()
        if self._thread is not None and self._thread.isRunning():
            self._thread.quit()
            self._thread.wait(5000)
        super().reject()
