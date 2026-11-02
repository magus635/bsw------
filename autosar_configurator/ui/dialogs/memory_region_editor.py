"""
Memory region editor

Page of the chip definition designer for the chip's ``memory_regions``: the physical
memories with their address windows (name, start, size, type, core, cacheable, window
label, source), grouped by memory, with add, change, rename and remove, hexadecimal
input, a list of problems, and import from the comment table of an ADS scatter file.

The widget owns a working copy and gives out only what the chip YAML loader accepts.  A
problem that makes the data unloadable stops the save (``blocking_problems``); one that
only makes it doubtful is listed and never stops it, because the vendor tables are partly
unconfirmed and the user must be able to enter what they are not sure of.
"""
import copy
from dataclasses import replace
from pathlib import Path
from typing import List, Optional

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QBrush, QColor
from PySide6.QtWidgets import (
    QCheckBox,
    QComboBox,
    QDialog,
    QDialogButtonBox,
    QFileDialog,
    QHBoxLayout,
    QInputDialog,
    QLabel,
    QLineEdit,
    QListWidget,
    QMessageBox,
    QPushButton,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...core.hardware.memory_regions import (
    LOCAL,
    REGION_TYPES,
    MemoryRegionDef,
    group_memories,
    region_problems,
    rename_memory,
)
from ...core.hardware.memory_regions_import import ImportResult, merge_import, parse_comment_table

COLUMNS = ["名称", "起始", "大小", "类型", "核心", "可缓存", "窗口", "来源"]
CORE_CHOICES = [("共享", None), ("核心本地", LOCAL), ("核心 0", 0), ("核心 1", 1), ("核心 2", 2), ("核心 3", 3)]
_DOUBT_BRUSH = QBrush(QColor("#fff3cd"))


def parse_hex(text: str, what: str) -> int:
    """A number typed as hexadecimal, with or without the ``0x`` prefix (``30100000`` and
    ``0x30100000`` are the same address): addresses and sizes are entered in hexadecimal.

    Raises:
        ValueError: with a message that names ``what``
    """
    text = (text or "").strip()
    if not text:
        raise ValueError(f"{what}不能为空")
    try:
        return int(text, 16)            # int(x, 16) accepts the 0x prefix itself
    except ValueError:
        raise ValueError(f"{what}不是十六进制数：{text!r}") from None


class RegionDialog(QDialog):
    """Add or change one window."""

    def __init__(self, region: Optional[MemoryRegionDef], memories: List[str], parent=None):
        super().__init__(parent)
        self.setWindowTitle("改窗口" if region else "加窗口")
        self.resize(420, 380)
        self._region = region
        layout = QVBoxLayout(self)
        self.name_edit = QLineEdit(region.name if region else "")
        self.memory_combo = QComboBox()
        self.memory_combo.setEditable(True)
        self.memory_combo.addItems(memories)
        self.memory_combo.setCurrentText(region.memory_name if region else "")
        self.start_edit = QLineEdit(hex(region.start) if region else "")
        self.size_edit = QLineEdit(hex(region.size) if region else "")
        self.type_combo = QComboBox()
        self.type_combo.addItems(REGION_TYPES)
        self.type_combo.setCurrentText(region.type if region else "ram")      # as the loader's default
        self.core_combo = QComboBox()
        for label, value in CORE_CHOICES:
            self.core_combo.addItem(label, value)
        if region:
            self.core_combo.setCurrentIndex(max(self.core_combo.findData(region.core), 0))
        self.cacheable = QCheckBox("可缓存")
        self.cacheable.setChecked(region.cacheable if region else True)
        self.window_edit = QLineEdit(region.window or "" if region else "")
        self.window_edit.setPlaceholderText("local、normal、device …（仅显示）")
        self.source_edit = QLineEdit(region.source or "" if region else "")
        self.source_edit.setPlaceholderText("数据来源，如 LinkerAdsPf.scat 注释表")
        for label, widget in (("名称", self.name_edit), ("所属存储", self.memory_combo),
                              ("起始地址（十六进制）", self.start_edit), ("大小（十六进制）", self.size_edit),
                              ("类型", self.type_combo), ("核心", self.core_combo), ("", self.cacheable),
                              ("窗口标签", self.window_edit), ("来源", self.source_edit)):
            row = QHBoxLayout()
            if label:
                row.addWidget(QLabel(label + "："))
            row.addWidget(widget, 1)
            layout.addLayout(row)
        self.error_label = QLabel("")
        self.error_label.setStyleSheet("color: #b00020;")
        self.error_label.setWordWrap(True)
        layout.addWidget(self.error_label)
        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self._accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)
        self.result_region: Optional[MemoryRegionDef] = None

    def build(self) -> MemoryRegionDef:
        """The window as typed.

        Raises:
            ValueError: the input cannot be a window; the message says which field
        """
        name = self.name_edit.text().strip()
        if not name:
            raise ValueError("名称不能为空")
        start = parse_hex(self.start_edit.text(), "起始地址")
        size = parse_hex(self.size_edit.text(), "大小")
        if size <= 0:
            raise ValueError(f"窗口 {name} 的大小必须为正数")
        memory = self.memory_combo.currentText().strip() or None
        return MemoryRegionDef(
            name, start, size, self.type_combo.currentText(), self.core_combo.currentData(),
            self.cacheable.isChecked(), memory if memory != name else None,
            self.window_edit.text().strip() or None, self.source_edit.text().strip() or None)

    def _accept(self):
        try:
            self.result_region = self.build()
        except ValueError as e:
            self.error_label.setText(str(e))
            return
        self.accept()


class ImportPreviewDialog(QDialog):
    """What an import would add and skip; nothing is merged until the user confirms."""

    def __init__(self, parsed: ImportResult, report, parent=None):
        super().__init__(parent)
        self.setWindowTitle("导入内存区域 — 预览")
        self.resize(560, 460)
        layout = QVBoxLayout(self)
        layout.addWidget(QLabel(f"来源：{parsed.source}。确认后才加入芯片；导入的项标为待确认。"))
        self.list = QListWidget()
        by_name = {r.name: r for r in parsed.regions}
        for name in report.added:
            r = by_name[name]
            notes = []
            if name in parsed.unstated_cache:
                notes.append("缓存属性原文未说明")
            if name in parsed.unstated_type:
                notes.append("flash/ram 原文未说明")
            self.list.addItem(f"加入  {name}  {r.start:#x}  {r.size:#x}  {r.type}"
                              + (f"    （{'；'.join(notes)}）" if notes else ""))
        for name in report.skipped:
            self.list.addItem(f"跳过  {name}  （芯片里已有同名项，不覆盖）")
        layout.addWidget(self.list, 1)
        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.button(QDialogButtonBox.Ok).setText("合并")
        buttons.button(QDialogButtonBox.Ok).setEnabled(bool(report.added))
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)


class MemoryRegionEditor(QWidget):
    """Tree of physical memories and their windows, with the editing buttons."""

    changed = Signal()

    def __init__(self, parent=None):
        super().__init__(parent)
        self._regions: List[MemoryRegionDef] = []
        self._unconfirmed_note = ""
        self._build_ui()

    # --------------------------------------------------------------- public API

    def set_regions(self, regions: List[MemoryRegionDef]) -> None:
        """Replace the edited data (the editor works on its own copy)."""
        self._regions = copy.deepcopy(list(regions or []))
        self._refresh()

    def regions(self) -> List[MemoryRegionDef]:
        return copy.deepcopy(self._regions)

    def blocking_problems(self) -> List[str]:
        """What stops the save: empty when the data can be saved."""
        return region_problems(self._regions)[0]

    def doubts(self) -> List[str]:
        return region_problems(self._regions)[1]

    def import_note(self) -> str:
        """The note of the last import, for the chip's ``unconfirmed`` mark ('' when none)."""
        return self._unconfirmed_note

    # --------------------------------------------------------------- building

    def _build_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(12, 12, 12, 12)
        note = QLabel("物理存储与它的地址窗口：同一块存储（如 GMU）可以有可缓存和不可缓存两个窗口。"
                      "数值待确认时可以先录入，保存时只提示，不阻止。")
        note.setWordWrap(True)
        layout.addWidget(note)
        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(COLUMNS)
        for column, width in enumerate((200, 110, 90, 60, 80, 70, 80, 220)):
            self.tree.setColumnWidth(column, width)
        self.tree.itemDoubleClicked.connect(lambda *_: self.edit_selected())
        layout.addWidget(self.tree, 1)

        row = QHBoxLayout()
        for text, slot in (("加窗口…", self.add_window), ("改…", self.edit_selected),
                           ("删除", self.remove_selected), ("重命名存储…", self.rename_selected),
                           ("导入…", self.import_from_file)):
            button = QPushButton(text)
            button.clicked.connect(slot)
            row.addWidget(button)
        row.addStretch()
        layout.addLayout(row)
        self.problems = QListWidget()
        self.problems.setMaximumHeight(110)
        layout.addWidget(self.problems)

    # --------------------------------------------------------------- showing

    def _refresh(self):
        self.tree.clear()
        doubtful = {name for text in self.doubts() for name in self._names_in(text)}
        for group in group_memories(self._regions):
            top = QTreeWidgetItem([f"{group.name}（{len(group.windows)} 个窗口）"])
            top.setData(0, Qt.UserRole, ("memory", group.name))
            self.tree.addTopLevelItem(top)
            for r in group.windows:
                item = QTreeWidgetItem([
                    r.name, f"{r.start:#x}", f"{r.size:#x}", r.type,
                    r.core_text(), "是" if r.cacheable else "否", r.window or "", r.source or ""])
                item.setData(0, Qt.UserRole, ("window", r.name))
                if r.name in doubtful:
                    for column in range(len(COLUMNS)):
                        item.setBackground(column, _DOUBT_BRUSH)
                top.addChild(item)
            top.setExpanded(True)
        self.problems.clear()
        errors, doubts = region_problems(self._regions)
        for text in errors:
            self.problems.addItem(f"错误（阻止保存）：{text}")
        for text in doubts:
            self.problems.addItem(f"提示：{text}")

    def _names_in(self, text: str) -> List[str]:
        known = {r.name for r in self._regions}
        return [n for n in known if n in text]

    def _selected(self):
        item = self.tree.currentItem()
        return item.data(0, Qt.UserRole) if item is not None else None

    def _memories(self) -> List[str]:
        return [g.name for g in group_memories(self._regions)]

    def _edited(self):
        self._refresh()
        self.changed.emit()

    # --------------------------------------------------------------- editing

    def add_window(self):
        selected = self._selected()
        dialog = RegionDialog(None, self._memories(), self)
        if selected and selected[0] == "memory":
            dialog.memory_combo.setCurrentText(selected[1])
        if dialog.exec() == QDialog.Accepted and dialog.result_region is not None:
            self.add_region(dialog.result_region)

    def add_region(self, region: MemoryRegionDef) -> None:
        self._regions.append(region)
        self._edited()

    def edit_selected(self):
        selected = self._selected()
        if not selected or selected[0] != "window":
            return
        current = next((r for r in self._regions if r.name == selected[1]), None)
        if current is None:
            return
        dialog = RegionDialog(current, self._memories(), self)
        if dialog.exec() == QDialog.Accepted and dialog.result_region is not None:
            self.replace_region(current.name, dialog.result_region)

    def replace_region(self, name: str, region: MemoryRegionDef) -> None:
        self._regions = [region if r.name == name else r for r in self._regions]
        self._edited()

    def remove_selected(self):
        selected = self._selected()
        if not selected:
            return
        if selected[0] == "window":
            self.remove_window(selected[1])
        else:
            self.remove_memory(selected[1])

    def remove_window(self, name: str) -> None:
        self._regions = [r for r in self._regions if r.name != name]
        self._edited()

    def remove_memory(self, memory: str) -> None:
        self._regions = [r for r in self._regions if r.memory_name != memory]
        self._edited()

    def rename_selected(self):
        selected = self._selected()
        if not selected:
            return
        memory = selected[1] if selected[0] == "memory" else next(
            (r.memory_name for r in self._regions if r.name == selected[1]), None)
        if memory is None:
            return
        new, ok = QInputDialog.getText(self, "重命名存储", f"{memory} 改名为：", text=memory)
        if ok and new.strip():
            try:
                self.rename(memory, new)
            except ValueError as e:
                QMessageBox.warning(self, "重命名存储", str(e))

    def rename(self, old: str, new: str) -> None:
        """Rename a memory: every window of it follows.

        Raises:
            ValueError: the new name is empty or taken
        """
        self._regions = rename_memory(self._regions, old, new)
        self._edited()

    # --------------------------------------------------------------- import

    def import_from_file(self):
        path, _ = QFileDialog.getOpenFileName(self, "选择 ADS 链接脚本", str(Path.home()),
                                              "ADS scatter (*.scat *.sct);;所有文件 (*)")
        if path:
            self.import_file(path)

    def import_file(self, path: str) -> bool:
        """Preview the memory table of ``path`` and merge it when the user confirms.

        Returns:
            whether anything was merged
        """
        try:
            text = Path(path).read_text(encoding="utf-8", errors="replace")
        except OSError as e:
            QMessageBox.warning(self, "导入内存区域", f"无法读取文件：{e}")
            return False
        parsed = parse_comment_table(text, path)
        if not parsed.regions:
            QMessageBox.information(self, "导入内存区域", "文件头部没有找到内存区域表。")
            return False
        merged, report = merge_import(self._regions, parsed)
        if not self._confirm_import(parsed, report):
            return False
        self._regions = merged
        self._unconfirmed_note = parsed.unconfirmed_note()
        self._edited()
        return True

    def _confirm_import(self, parsed: ImportResult, report) -> bool:
        return ImportPreviewDialog(parsed, report, self).exec() == QDialog.Accepted
