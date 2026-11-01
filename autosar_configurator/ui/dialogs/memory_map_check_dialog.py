"""Memory map check dialog: settings, background check, filtered result tree and
Markdown checklist export.  The check only reads; the settings are kept on the
project and saved with it."""
import logging
from pathlib import Path
from typing import List, Optional

from PySide6.QtCore import QObject, QThread, Signal
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QAbstractItemView,
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
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
)

from ...core.hardware.chip_dependency_scan import ScanCancelled, resolve_scan_dir
from ...core.memmap.check import (
    CATEGORIES,
    CATEGORY_LABELS,
    GENERATION_DIR,
    STATIC_NOTE,
    CheckResult,
    check_project,
    to_markdown,
)
from .chip_dependency_scan_dialog import scan_dir_entry

logger = logging.getLogger(__name__)

ALL = "全部"


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
            logger.exception("Memory map check failed")
            self.failed.emit(str(e))
        else:
            self.finished.emit(result)


class _DirList(QHBoxLayout):
    """A directory list with add and remove buttons."""

    def __init__(self, dialog: "MemoryMapCheckDialog", entries: List[str], title: str):
        super().__init__()
        self.dialog, self.title = dialog, title
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
        """Directories that do not exist are shown red (the check skips them)."""
        for i in range(self.list.count()):
            item = self.list.item(i)
            missing = not resolve_scan_dir(item.text(), self.dialog.base).is_dir()
            item.setForeground(QColor("red") if missing else self.dialog.palette().text().color())
            item.setToolTip("目录不存在，检查时会跳过" if missing else "")

    def _choose(self):
        directory = QFileDialog.getExistingDirectory(self.dialog, self.title, str(self.dialog.base or ""))
        if directory:
            self.add(directory)

    def add(self, directory: str):
        entry = scan_dir_entry(directory, self.dialog.base)
        if entry not in self.entries():
            self.list.addItem(entry)
            self.mark_missing()

    def _remove(self):
        for item in self.list.selectedItems():
            self.list.takeItem(self.list.row(item))


class MemoryMapCheckDialog(QDialog):
    """Tools → 检查内存映射…"""

    settings_changed = Signal()

    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.result: Optional[CheckResult] = None
        self._thread: Optional[QThread] = None
        self._worker: Optional[_CheckWorker] = None
        path = getattr(project, "path", None)
        self.base = (Path(path).parent if path and Path(path).suffix == ".dpa" else
                     Path(path) if path else None)
        self.setWindowTitle("检查内存映射")
        self.resize(1100, 760)
        self._build()

    # --- layout ----------------------------------------------------------------

    def _build(self):
        layout = QVBoxLayout(self)
        layout.addWidget(QLabel(f"源码目录（MCAL、SDK、OS 内核、应用等；工程的 {GENERATION_DIR} 总会被检查）："))
        self.source_dirs = _DirList(self, list(getattr(self.project, "memmap_source_dirs", []) or []),
                                    "添加源码目录")
        layout.addLayout(self.source_dirs)
        layout.addWidget(QLabel("MemMap 头目录（源码目录中的 *MemMap*.h 也会读取）："))
        self.header_dirs = _DirList(self, list(getattr(self.project, "memmap_header_dirs", []) or []),
                                    "添加 MemMap 头目录")
        layout.addLayout(self.header_dirs)

        row = QHBoxLayout()
        row.addWidget(QLabel("链接文件："))
        self.linker_edit = QLineEdit(getattr(self.project, "memmap_linker_file", None) or "")
        self.linker_edit.setReadOnly(True)
        self.linker_edit.setPlaceholderText("ADS 分散加载文件（.scat），例如生成的 Os/scatter.scat")
        row.addWidget(self.linker_edit, 1)
        choose = QPushButton("选择…")
        choose.clicked.connect(self._choose_linker)
        clear = QPushButton("清除")
        clear.clicked.connect(lambda: self.linker_edit.setText(""))
        row.addWidget(choose)
        row.addWidget(clear)
        self.check_button = QPushButton("开始检查")
        self.check_button.clicked.connect(self.start_check)
        self.cancel_button = QPushButton("取消检查")
        self.cancel_button.setEnabled(False)
        self.cancel_button.clicked.connect(self.cancel_check)
        row.addWidget(self.check_button)
        row.addWidget(self.cancel_button)
        layout.addLayout(row)

        self.progress_bar = QProgressBar()
        self.progress_bar.setTextVisible(True)
        self.progress_bar.setFormat("")
        layout.addWidget(self.progress_bar)

        row = QHBoxLayout()
        row.addWidget(QLabel("类别："))
        self.category_combo = QComboBox()
        self.category_combo.addItem(ALL, None)
        for category in CATEGORIES:
            self.category_combo.addItem(CATEGORY_LABELS[category], category)
        self.category_combo.currentIndexChanged.connect(self._fill_tree)
        row.addWidget(self.category_combo)
        row.addStretch()
        self.summary_label = QLabel("")
        row.addWidget(self.summary_label)
        layout.addLayout(row)

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["位置", "内容", "说明"])
        self.tree.setColumnWidth(0, 360)
        self.tree.setColumnWidth(1, 470)
        layout.addWidget(self.tree, 1)

        self.notes_label = QLabel("")
        self.notes_label.setWordWrap(True)
        layout.addWidget(self.notes_label)
        note = QLabel(STATIC_NOTE)
        note.setWordWrap(True)
        note.setStyleSheet("color: gray;")
        layout.addWidget(note)

        row = QHBoxLayout()
        row.addStretch()
        self.export_button = QPushButton("导出检查清单…")
        self.export_button.setEnabled(False)
        self.export_button.clicked.connect(self.export_checklist)
        close = QPushButton("关闭")
        close.clicked.connect(self.reject)
        row.addWidget(self.export_button)
        row.addWidget(close)
        layout.addLayout(row)

    # --- settings --------------------------------------------------------------

    def _choose_linker(self):
        path, _ = QFileDialog.getOpenFileName(self, "选择链接文件", str(self.base or ""),
                                              "ADS scatter (*.scat *.sct);;所有文件 (*)")
        if path:
            self.set_linker_file(path)

    def set_linker_file(self, path: str):
        self.linker_edit.setText(scan_dir_entry(path, self.base))

    def _store_settings(self):
        sources, headers = self.source_dirs.entries(), self.header_dirs.entries()
        linker = self.linker_edit.text().strip() or None
        if (sources != list(getattr(self.project, "memmap_source_dirs", []) or [])
                or headers != list(getattr(self.project, "memmap_header_dirs", []) or [])
                or linker != getattr(self.project, "memmap_linker_file", None)):
            self.project.memmap_source_dirs = sources
            self.project.memmap_header_dirs = headers
            self.project.memmap_linker_file = linker
            self.settings_changed.emit()

    # --- check -----------------------------------------------------------------

    def start_check(self):
        self._store_settings()
        self.check_button.setEnabled(False)
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

    def cancel_check(self):
        if self._worker is not None:
            self._worker.cancelled = True
            self.cancel_button.setEnabled(False)

    def _on_progress(self, index: int, total: int, path: str):
        self.progress_bar.setRange(0, max(total, 1))
        self.progress_bar.setValue(index)
        self.progress_bar.setFormat(f"{index}/{total}  {path}" if path else "正在检查放置…")

    def _check_ended(self):
        self.check_button.setEnabled(True)
        self.cancel_button.setEnabled(False)
        self.progress_bar.setRange(0, 1)

    def _on_failed(self, message: str):
        self._check_ended()
        self.progress_bar.setValue(0)
        self.progress_bar.setFormat("检查失败")
        QMessageBox.warning(self, "检查内存映射", f"检查失败：{message}")

    def _on_finished(self, result: Optional[CheckResult]):
        self._check_ended()
        if result is None:
            self.progress_bar.setValue(0)
            self.progress_bar.setFormat("已取消")
            return
        self.progress_bar.setValue(1)
        self.progress_bar.setFormat(f"已扫描 {result.files_scanned} 个文件，用到的段 {result.sections_used} 个")
        self.show_result(result)

    # --- result ----------------------------------------------------------------

    def show_result(self, result: CheckResult):
        self.result = result
        self.export_button.setEnabled(True)
        self.notes_label.setText("\n".join(result.notes))
        self._fill_tree()

    def filtered(self):
        if self.result is None:
            return []
        category = self.category_combo.currentData()
        return [f for f in self.result.findings if category is None or f.category == category]

    def _fill_tree(self):
        self.tree.clear()
        if self.result is None:
            return
        findings = self.filtered()
        counts = {c: sum(1 for f in findings if f.category == c) for c in CATEGORIES}
        self.summary_label.setText("，".join(f"{CATEGORY_LABELS[c]} {n}" for c, n in counts.items() if n)
                                   or "没有发现问题")
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
                text = f.text + ("（可能）" if f.possible else "")
                child = QTreeWidgetItem([where, text, f.note])
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

    def checklist_text(self) -> str:
        return to_markdown(self.result, findings=self.filtered())

    def export_checklist(self):
        if self.result is None:
            return
        default = str((self.base or Path.cwd()) / "内存映射检查清单.md")
        path, _ = QFileDialog.getSaveFileName(self, "导出检查清单", default, "Markdown (*.md)")
        if not path:
            return
        try:
            Path(path).write_text(self.checklist_text(), encoding="utf-8")
        except OSError as e:
            QMessageBox.warning(self, "导出检查清单", f"写入失败：{e}")
            return
        QMessageBox.information(self, "导出检查清单", f"已导出：{path}")

    def reject(self):
        self.cancel_check()
        if self._thread is not None and self._thread.isRunning():
            self._thread.quit()
            self._thread.wait(5000)
        self._store_settings()
        super().reject()
