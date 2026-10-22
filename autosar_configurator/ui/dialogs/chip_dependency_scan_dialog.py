"""Chip dependency scan dialog: settings, background scan, filtered result tree and
Markdown checklist export.  The scan only reads; the settings are kept on the
project and saved with it."""
import logging
import os
from pathlib import Path
from typing import List, Optional

from PySide6.QtCore import QObject, QThread, Signal
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QAbstractItemView, QComboBox, QDialog, QFileDialog, QHBoxLayout, QLabel,
    QLineEdit, QListWidget, QMessageBox, QProgressBar, QPushButton, QTreeWidget,
    QTreeWidgetItem, QVBoxLayout)

from ...core.hardware.chip_dependency_scan import (
    CATEGORIES, CATEGORY_LABELS, COVERAGE, HARDCODED, STATIC_NOTE, ScanCancelled,
    ScanResult, resolve_scan_dir, scan_project, to_markdown)

logger = logging.getLogger(__name__)

ALL = "全部"


def scan_dir_entry(directory: str, base: Optional[Path]) -> str:
    """How an added directory is saved: POSIX, relative to the project directory when
    possible (``../`` allowed), absolute on another drive."""
    if base is not None:
        try:
            return Path(os.path.relpath(directory, base)).as_posix()
        except ValueError:
            pass
    return Path(directory).as_posix()


def parse_keywords(text: str) -> List[str]:
    return [k for k in (part.strip() for part in text.replace("，", ",").split(",")) if k]


class _ScanWorker(QObject):
    progress = Signal(int, int, str)
    finished = Signal(object)        # ScanResult, or None when cancelled
    failed = Signal(str)

    def __init__(self, project, dirs, keywords):
        super().__init__()
        self.project, self.dirs, self.keywords = project, dirs, keywords
        self.cancelled = False

    def _progress(self, index, total, path):
        self.progress.emit(index, total, path)
        return not self.cancelled

    def run(self):
        try:
            result = scan_project(self.project, extra_dirs=self.dirs,
                                  extra_keywords=self.keywords, progress=self._progress)
        except ScanCancelled:
            self.finished.emit(None)
        except Exception as e:  # noqa: BLE001 - shown to the user, never crashes the UI
            logger.exception("Chip dependency scan failed")
            self.failed.emit(str(e))
        else:
            self.finished.emit(result)


class ChipDependencyScanDialog(QDialog):
    """Tools → 芯片依赖扫描…"""

    settings_changed = Signal()

    def __init__(self, project, parent=None):
        super().__init__(parent)
        self.project = project
        self.result: Optional[ScanResult] = None
        self._thread: Optional[QThread] = None
        self._worker: Optional[_ScanWorker] = None
        path = getattr(project, "path", None)
        self.base = (Path(path).parent if path and Path(path).suffix == ".dpa" else
                     Path(path) if path else None)
        self.setWindowTitle("芯片依赖扫描")
        self.resize(1100, 720)
        self._build()

    # --- layout ----------------------------------------------------------------

    def _build(self):
        layout = QVBoxLayout(self)
        layout.addWidget(QLabel("除已加载模块的定义和模板外，还扫描以下目录（EB 插件、内核、SDK、MCAL 等）："))
        row = QHBoxLayout()
        self.dir_list = QListWidget()
        self.dir_list.setSelectionMode(QAbstractItemView.ExtendedSelection)
        self.dir_list.setMaximumHeight(110)
        self.dir_list.addItems(list(getattr(self.project, "chip_scan_dirs", []) or []))
        self._mark_missing_dirs()
        row.addWidget(self.dir_list, 1)
        buttons = QVBoxLayout()
        self.add_dir_button = QPushButton("添加目录…")
        self.add_dir_button.clicked.connect(self._add_dir)
        self.remove_dir_button = QPushButton("移除")
        self.remove_dir_button.clicked.connect(self._remove_dirs)
        buttons.addWidget(self.add_dir_button)
        buttons.addWidget(self.remove_dir_button)
        buttons.addStretch()
        row.addLayout(buttons)
        layout.addLayout(row)

        row = QHBoxLayout()
        row.addWidget(QLabel("补充芯片关键字（逗号分隔）："))
        self.keyword_edit = QLineEdit(", ".join(getattr(self.project, "chip_scan_keywords", []) or []))
        self.keyword_edit.setPlaceholderText("例如 THA6XXX")
        row.addWidget(self.keyword_edit, 1)
        self.scan_button = QPushButton("开始扫描")
        self.scan_button.clicked.connect(self.start_scan)
        self.cancel_button = QPushButton("取消扫描")
        self.cancel_button.setEnabled(False)
        self.cancel_button.clicked.connect(self.cancel_scan)
        row.addWidget(self.scan_button)
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
        row.addWidget(QLabel("芯片："))
        self.chip_combo = QComboBox()
        self.chip_combo.addItem(ALL)
        self.chip_combo.currentIndexChanged.connect(self._fill_tree)
        row.addWidget(self.chip_combo)
        row.addStretch()
        self.summary_label = QLabel("")
        row.addWidget(self.summary_label)
        layout.addLayout(row)

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["位置", "内容", "芯片", "说明"])
        self.tree.setColumnWidth(0, 360)
        self.tree.setColumnWidth(1, 430)
        self.tree.setColumnWidth(2, 140)
        layout.addWidget(self.tree, 1)

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

    def scan_dirs(self) -> List[str]:
        return [self.dir_list.item(i).text() for i in range(self.dir_list.count())]

    def _mark_missing_dirs(self):
        """Directories that do not exist are shown red (the scan skips them)."""
        for i in range(self.dir_list.count()):
            item = self.dir_list.item(i)
            missing = not resolve_scan_dir(item.text(), self.base).is_dir()
            item.setForeground(QColor("red") if missing else self.palette().text().color())
            item.setToolTip("目录不存在，扫描时会跳过" if missing else "")

    def _add_dir(self):
        directory = QFileDialog.getExistingDirectory(self, "添加扫描目录", str(self.base or ""))
        if directory:
            self.add_dir(directory)

    def add_dir(self, directory: str):
        entry = scan_dir_entry(directory, self.base)
        if entry not in self.scan_dirs():
            self.dir_list.addItem(entry)
            self._mark_missing_dirs()

    def _remove_dirs(self):
        for item in self.dir_list.selectedItems():
            self.dir_list.takeItem(self.dir_list.row(item))

    def _store_settings(self):
        dirs, keywords = self.scan_dirs(), parse_keywords(self.keyword_edit.text())
        if (dirs != list(getattr(self.project, "chip_scan_dirs", []) or [])
                or keywords != list(getattr(self.project, "chip_scan_keywords", []) or [])):
            self.project.chip_scan_dirs = dirs
            self.project.chip_scan_keywords = keywords
            self.settings_changed.emit()

    # --- scan ------------------------------------------------------------------

    def start_scan(self):
        self._store_settings()
        self.scan_button.setEnabled(False)
        self.cancel_button.setEnabled(True)
        self.export_button.setEnabled(False)
        self.progress_bar.setRange(0, 0)
        self.progress_bar.setFormat("正在列出文件…")
        self._thread = QThread(self)
        self._worker = _ScanWorker(self.project, self.project.chip_scan_dirs,
                                   self.project.chip_scan_keywords)
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
        self.progress_bar.setFormat(f"{index}/{total}  {path}" if path else "正在检查资源覆盖…")

    def _scan_ended(self):
        self.scan_button.setEnabled(True)
        self.cancel_button.setEnabled(False)
        self.progress_bar.setRange(0, 1)

    def _on_failed(self, message: str):
        self._scan_ended()
        self.progress_bar.setValue(0)
        self.progress_bar.setFormat("扫描失败")
        QMessageBox.warning(self, "芯片依赖扫描", f"扫描失败：{message}")

    def _on_finished(self, result: Optional[ScanResult]):
        self._scan_ended()
        if result is None:
            self.progress_bar.setValue(0)
            self.progress_bar.setFormat("已取消")
            return
        self.progress_bar.setValue(1)
        self.progress_bar.setFormat(f"已扫描 {result.files_scanned} 个文件")
        self.show_result(result)

    # --- result ----------------------------------------------------------------

    def show_result(self, result: ScanResult):
        self.result = result
        self.chip_combo.blockSignals(True)
        self.chip_combo.clear()
        self.chip_combo.addItem(ALL)
        self.chip_combo.addItems(result.chips())
        self.chip_combo.blockSignals(False)
        self.export_button.setEnabled(True)
        self._fill_tree()

    def filtered(self):
        if self.result is None:
            return []
        category = self.category_combo.currentData()
        chip = self.chip_combo.currentText()
        return [f for f in self.result.findings
                if (category is None or f.category == category)
                and (chip in ("", ALL) or chip in f.chips)]

    def _fill_tree(self):
        self.tree.clear()
        if self.result is None:
            return
        findings = self.filtered()
        counts = {c: sum(1 for f in findings if f.category == c) for c in CATEGORIES}
        self.summary_label.setText("，".join(f"{CATEGORY_LABELS[c]} {n}" for c, n in counts.items()))
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
                child = QTreeWidgetItem([where, f.text, ", ".join(f.chips), f.note])
                child.setToolTip(1, f.text)
                parent.addChild(child)
            if category == HARDCODED:
                for path, more in sorted(self.result.truncated.items()):
                    parent = files.get(path)
                    if parent is not None:
                        parent.addChild(QTreeWidgetItem(["", f"另有 {more} 行未列出"]))
            for parent in files.values():
                parent.setText(0, f"{parent.text(0)}（{parent.childCount()}）")
            group.setExpanded(category == COVERAGE or len(items) <= 30)
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
        default = str((self.base or Path.cwd()) / "芯片依赖检查清单.md")
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
        self.cancel_scan()
        if self._thread is not None and self._thread.isRunning():
            self._thread.quit()
            self._thread.wait(5000)
        self._store_settings()
        super().reject()
