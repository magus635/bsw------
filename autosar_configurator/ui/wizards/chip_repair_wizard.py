"""
Chip repair wizard (add-chip-repair-wizard)

Repairs a chip of the chip library in six steps: chip, sources, changes,
unconfirmed marks, views and completeness, save.  All logic is in
core.hardware.chip_repair.RepairSession; the pages only show it and collect
the user's choices.  Nothing is written before the last page.
"""
import logging
from pathlib import Path
from typing import List, Optional

from PySide6.QtCore import Qt, Signal
from PySide6.QtWidgets import (
    QAbstractItemView, QCheckBox, QComboBox, QFileDialog, QFormLayout, QHBoxLayout,
    QHeaderView, QLabel, QLineEdit, QListWidget, QMessageBox, QPushButton,
    QTableWidget, QTableWidgetItem, QTextEdit, QTreeWidget, QTreeWidgetItem,
    QVBoxLayout, QWizard, QWizardPage,
)

from ...core.hardware import chip_repair as repair
from ...core.hardware.chip_database import ChipDatabase

logger = logging.getLogger(__name__)

MAX_VALUE_TEXT = 80
KIND_TEXT = {repair.ADDED: "新增", repair.CHANGED: "变化", repair.REMOVED: "删除"}
VIEW_STATE_TEXT = {repair.UNCHANGED: "未变", repair.UPDATED: "已更新", repair.NOT_DERIVED: "未推导"}
FILTER_ALL = "全部"
KEEP, CONFIRM = "保留", "确认"


def value_text(value) -> str:
    """Short text of an ECU resource value for a table cell."""
    if value is repair.PLACEHOLDER:
        return "（待填写）"
    text = ", ".join(str(v) for v in value) if isinstance(value, list) else str(value)
    return text if len(text) <= MAX_VALUE_TEXT else text[:MAX_VALUE_TEXT - 3] + "..."


def project_copy_notice(project, database: ChipDatabase, chip_name: str) -> Optional[str]:
    """Message when the project keeps its own copy of the chip that differs from the
    library's (repaired) one; the copy is never updated automatically."""
    from ...core.hardware.chip_exporter import chip_checksum

    store = getattr(project, "chip_store", None) if project is not None else None
    local = store.load(chip_name) if store is not None else None
    library = database.get_chip(chip_name)
    if local is None or library is None or chip_checksum(local) == chip_checksum(library):
        return None
    return (f"项目的 chips/ 里保存着 {chip_name} 的副本，仍是修复前的数据。\n"
            "需要时请在“项目属性”里点 “Update from Library” 同步到项目。")


def _items_text(items) -> str:
    return "\n".join(f"  • {i.text}" for i in items) or "  （无）"


class _Page(QWizardPage):
    def __init__(self, title: str, subtitle: str = ""):
        super().__init__()
        self.setTitle(title)
        if subtitle:
            self.setSubTitle(subtitle)
        self.box = QVBoxLayout(self)

    @property
    def session(self) -> Optional[repair.RepairSession]:
        return self.wizard().session


# --- 1. chip --------------------------------------------------------------------------

class ChipPage(_Page):
    def __init__(self):
        super().__init__("1. 选择芯片", "选择芯片库中要修复的芯片。修复不会改名；要改名请在芯片定义设计器里另存为新芯片。")
        form = QFormLayout()
        self.chip_combo = QComboBox()
        self.chip_combo.currentIndexChanged.connect(self._show_chip)
        form.addRow("芯片:", self.chip_combo)
        self.box.addLayout(form)
        self.info = QTextEdit()
        self.info.setReadOnly(True)
        self.box.addWidget(self.info, 1)

    def initializePage(self):
        wizard = self.wizard()
        self.chip_combo.blockSignals(True)
        self.chip_combo.clear()
        for name in sorted(wizard.database.list_chips()):
            self.chip_combo.addItem(name, name)
        index = self.chip_combo.findData(wizard.initial_chip) if wizard.initial_chip else -1
        self.chip_combo.setCurrentIndex(max(index, 0))
        self.chip_combo.blockSignals(False)
        self._show_chip()

    def chip_name(self) -> str:
        return self.chip_combo.currentData() or ""

    def _show_chip(self, *_):
        wizard = self.wizard()
        chip = wizard.database.get_chip(self.chip_name())
        if chip is None:
            self.info.setPlainText("芯片库中没有芯片。")
            return
        probe = repair.RepairSession(wizard.database, chip.name, wizard.project)
        lines = [f"resource_version: {chip.resource_version or '（无）'}"]
        if chip.content_modified:
            lines.append("⚠ 文件在芯片设计器之外被修改过（内容与校验和不符），修复会以当前文件内容为准。")
        lines += ["", "完整性问题:", _items_text(probe.completeness(chip))]
        history = repair.read_history(probe.chip_file) if probe.chip_file else []
        if history:
            last = history[-1]
            lines += ["", f"最近一次修复（共 {len(history)} 次）: {last.get('date', '')} "
                          f"{last.get('author', '')} — {last.get('source', '')}"
                          + (f"：{last['note']}" if last.get("note") else "")]
        else:
            lines += ["", "尚无修复记录。"]
        self.info.setPlainText("\n".join(lines))

    def isComplete(self) -> bool:
        return bool(self.chip_name())

    def validatePage(self) -> bool:
        wizard = self.wizard()
        name = self.chip_name()
        if wizard.session is not None and wizard.session.base.name == name:
            return True
        session = repair.RepairSession(wizard.database, name, wizard.project)
        if session.chip_file is None or not session.chip_file.is_file():
            QMessageBox.warning(self, "无法修复", f"芯片库目录中没有 {name}.yaml，无法写回修复结果。")
            return False
        wizard.session = session
        return True


# --- 2. sources -----------------------------------------------------------------------

class SourcesPage(_Page):
    def __init__(self):
        super().__init__("2. 修复来源", "可组合多种来源；都不选时只处理待确认标记。"
                                        ".properties 只与其中出现的模块比较。")
        self.box.addWidget(QLabel("厂商 .properties 文件（后列的文件覆盖先列的同名键）:"))
        self.files = QListWidget()
        self.box.addWidget(self.files)
        self.box.addLayout(self._buttons(self._add_files, self.files))

        self.scan_project = QCheckBox("扫描当前项目模块所需、芯片却没有的键")
        self.box.addWidget(self.scan_project)

        self.box.addWidget(QLabel("扫描插件目录所需、芯片却没有的键:"))
        self.dirs = QListWidget()
        self.box.addWidget(self.dirs)
        self.box.addLayout(self._buttons(self._add_dir, self.dirs))

    def _buttons(self, add, widget) -> QHBoxLayout:
        row = QHBoxLayout()
        add_btn = QPushButton("添加…")
        add_btn.clicked.connect(add)
        row.addWidget(add_btn)
        remove_btn = QPushButton("移除所选")
        remove_btn.clicked.connect(lambda: [widget.takeItem(widget.row(i)) for i in widget.selectedItems()])
        row.addWidget(remove_btn)
        row.addStretch()
        return row

    def _add_files(self):
        paths, _ = QFileDialog.getOpenFileNames(self, "选择 .properties 文件", str(Path.home()),
                                                "Properties Files (*.properties);;All Files (*)")
        for p in paths:
            self.add_file(Path(p))

    def _add_dir(self):
        path = QFileDialog.getExistingDirectory(self, "选择插件目录", str(Path.home()))
        if path:
            self.add_dir(Path(path))

    def add_file(self, path: Path):
        self.files.addItem(str(path))

    def add_dir(self, path: Path):
        self.dirs.addItem(str(path))

    def initializePage(self):
        has_project = self.wizard().project is not None
        self.scan_project.setEnabled(has_project)
        if not has_project:
            self.scan_project.setChecked(False)
            self.scan_project.setToolTip("没有打开项目")

    def file_paths(self) -> List[Path]:
        return [Path(self.files.item(i).text()) for i in range(self.files.count())]

    def validatePage(self) -> bool:
        session = self.session
        session.properties = self.file_paths()
        session.scan_project = self.scan_project.isChecked()
        session.scan_dirs = [Path(self.dirs.item(i).text()) for i in range(self.dirs.count())]
        try:
            session.load_sources()
        except Exception as e:  # noqa: BLE001 - a bad file is reported, the wizard stays usable
            logger.exception("loading the repair sources failed")
            QMessageBox.critical(self, "来源读取失败", str(e))
            return False
        return True


# --- 3. changes -----------------------------------------------------------------------

class ChangesPage(_Page):
    COL_KEY, COL_KIND, COL_OLD, COL_NEW = range(4)

    def __init__(self):
        super().__init__("3. 差异与选择", "勾选要应用的改动。默认勾选新增和变化；删除和（待填写）项需要手动勾选，"
                                          "待填写项保存后标为“待填写”，填值后自动消除。")
        row = QHBoxLayout()
        row.addWidget(QLabel("显示:"))
        self.filter_combo = QComboBox()
        self.filter_combo.addItems([FILTER_ALL] + list(KIND_TEXT.values()))
        self.filter_combo.currentIndexChanged.connect(self._apply_filter)
        row.addWidget(self.filter_combo)
        row.addStretch()
        self.count_label = QLabel()
        row.addWidget(self.count_label)
        self.box.addLayout(row)

        self.tree = QTreeWidget()
        self.tree.setColumnCount(4)
        self.tree.setHeaderLabels(["键", "类型", "旧值", "新值"])
        self.tree.header().setSectionResizeMode(QHeaderView.Interactive)
        self.tree.setColumnWidth(self.COL_KEY, 300)
        self.tree.setColumnWidth(self.COL_KIND, 120)
        self.tree.itemChanged.connect(self._on_item_changed)
        self.box.addWidget(self.tree, 1)

    def initializePage(self):
        session = self.session
        self.tree.blockSignals(True)
        self.tree.clear()
        modules = {}
        for change in session.diff.changes:
            module, name = change.key.split(".", 1)
            parent = modules.get(module)
            if parent is None:
                parent = QTreeWidgetItem(self.tree, [module])
                parent.setFlags(parent.flags() | Qt.ItemIsUserCheckable | Qt.ItemIsAutoTristate)
                modules[module] = parent
            kind = KIND_TEXT[change.kind] + ("（仅类型不同）" if change.type_only else "")
            item = QTreeWidgetItem(parent, [name, kind,
                                            "" if change.kind == repair.ADDED else value_text(change.old),
                                            "" if change.kind == repair.REMOVED else value_text(change.new)])
            item.setData(self.COL_KEY, Qt.UserRole, change.key)
            item.setData(self.COL_KIND, Qt.UserRole, change.kind)
            item.setFlags(item.flags() | Qt.ItemIsUserCheckable)
            item.setCheckState(self.COL_KEY, Qt.Checked if change.key in session.selected else Qt.Unchecked)
            item.setToolTip(self.COL_OLD, repr(change.old))
            item.setToolTip(self.COL_NEW, repr(change.new))
        for parent in modules.values():
            parent.setExpanded(len(modules) == 1)
        self.tree.blockSignals(False)
        self._apply_filter()
        self._update_count()

    def key_items(self):
        for i in range(self.tree.topLevelItemCount()):
            parent = self.tree.topLevelItem(i)
            for j in range(parent.childCount()):
                yield parent.child(j)

    def _on_item_changed(self, *_):
        self.session.selected = {item.data(self.COL_KEY, Qt.UserRole) for item in self.key_items()
                                 if item.checkState(self.COL_KEY) == Qt.Checked}
        self._update_count()

    def _apply_filter(self, *_):
        wanted = self.filter_combo.currentText()
        kind = next((k for k, t in KIND_TEXT.items() if t == wanted), None)
        for i in range(self.tree.topLevelItemCount()):
            parent = self.tree.topLevelItem(i)
            visible = 0
            for j in range(parent.childCount()):
                child = parent.child(j)
                hidden = kind is not None and child.data(self.COL_KIND, Qt.UserRole) != kind
                child.setHidden(hidden)
                visible += not hidden
            parent.setHidden(visible == 0)

    def _update_count(self):
        session = self.session
        if not session.diff:
            self.count_label.setText("没有差异：只处理待确认标记")
            return
        counts = {k: len(session.diff.keys(k)) for k in KIND_TEXT}
        self.count_label.setText(
            f"已勾选 {len(session.selected)} / {len(session.diff.changes)}（新增 {counts[repair.ADDED]}，"
            f"变化 {counts[repair.CHANGED]}，删除 {counts[repair.REMOVED]}）")


# --- 4. unconfirmed marks ----------------------------------------------------------------

class MarksPage(_Page):
    COL_FIELD, COL_NOTE, COL_ACTION, COL_CONFIRM = range(4)

    def __init__(self):
        super().__init__("4. 待确认标记", "核实过的数据选“确认”并写明依据；确认只去掉标记，不改动数据。")
        self.table = QTableWidget(0, 4)
        self.table.setHorizontalHeaderLabels(["字段", "待确认说明", "处理", "确认说明"])
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.setSelectionMode(QAbstractItemView.NoSelection)
        self.box.addWidget(self.table, 1)

        self.box.addWidget(QLabel("新增待确认标记:"))
        self.new_table = QTableWidget(0, 2)
        self.new_table.setHorizontalHeaderLabels(["字段（如 ecu_resources.Intc）", "说明"])
        self.new_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.box.addWidget(self.new_table)
        row = QHBoxLayout()
        add_btn = QPushButton("增加一行")
        add_btn.clicked.connect(lambda: self.new_table.insertRow(self.new_table.rowCount()))
        row.addWidget(add_btn)
        del_btn = QPushButton("删除所选行")
        del_btn.clicked.connect(self._remove_new_rows)
        row.addWidget(del_btn)
        row.addStretch()
        self.box.addLayout(row)

    def initializePage(self):
        from ...core.hardware.chip_completeness import unconfirmed_marks

        session = self.session
        marks = unconfirmed_marks(session.base)
        self.table.setRowCount(0)
        for field_path, note in marks.items():
            row = self.table.rowCount()
            self.table.insertRow(row)
            for col, text in ((self.COL_FIELD, field_path), (self.COL_NOTE, note)):
                item = QTableWidgetItem(text)
                item.setFlags(item.flags() & ~Qt.ItemIsEditable)
                item.setToolTip(text)
                self.table.setItem(row, col, item)
            combo = QComboBox()
            combo.addItems([KEEP, CONFIRM])
            combo.setCurrentText(CONFIRM if field_path in session.confirm_notes else KEEP)
            self.table.setCellWidget(row, self.COL_ACTION, combo)
            self.table.setItem(row, self.COL_CONFIRM, QTableWidgetItem(session.confirm_notes.get(field_path, "")))
        if not marks:
            self.setSubTitle("这颗芯片没有待确认标记；可以在下方新增。")

    def set_action(self, field_path: str, action: str, note: str = ""):
        for row in range(self.table.rowCount()):
            if self.table.item(row, self.COL_FIELD).text() == field_path:
                self.table.cellWidget(row, self.COL_ACTION).setCurrentText(action)
                self.table.item(row, self.COL_CONFIRM).setText(note)
                return
        raise KeyError(field_path)

    def add_mark(self, field_path: str, note: str = ""):
        row = self.new_table.rowCount()
        self.new_table.insertRow(row)
        self.new_table.setItem(row, 0, QTableWidgetItem(field_path))
        self.new_table.setItem(row, 1, QTableWidgetItem(note))

    def _remove_new_rows(self):
        for row in sorted({i.row() for i in self.new_table.selectedIndexes()}, reverse=True):
            self.new_table.removeRow(row)

    def validatePage(self) -> bool:
        session = self.session
        confirm = {}
        for row in range(self.table.rowCount()):
            if self.table.cellWidget(row, self.COL_ACTION).currentText() == CONFIRM:
                item = self.table.item(row, self.COL_CONFIRM)
                confirm[self.table.item(row, self.COL_FIELD).text()] = item.text().strip() if item else ""
        marks = {}
        for row in range(self.new_table.rowCount()):
            field_item, note_item = self.new_table.item(row, 0), self.new_table.item(row, 1)
            field_path = field_item.text().strip() if field_item else ""
            if field_path:
                marks[field_path] = note_item.text().strip() if note_item else ""
        session.confirm_notes, session.new_marks = confirm, marks
        return True


# --- 5. views and completeness -------------------------------------------------------------

class ReviewPage(_Page):
    def __init__(self):
        super().__init__("5. 视图与检查", "外设、核与引脚表由 ECU 资源重新推导；下方对比修复前后的完整性。")
        self.text = QTextEdit()
        self.text.setReadOnly(True)
        self.box.addWidget(self.text, 1)

    def initializePage(self):
        session = self.session
        try:
            chip, views = session.build()
        except ValueError as e:
            self.text.setPlainText(f"无法生成修复结果：{e}")
            return
        resolved, remaining, new = session.completeness_change(chip)
        applied = repair.diff_ecu_resources(session.base.ecu_resources, chip.ecu_resources)
        lines = [f"ECU 资源改动：新增 {len(applied.keys(repair.ADDED))}，变化 {len(applied.keys(repair.CHANGED))}，"
                 f"删除 {len(applied.keys(repair.REMOVED))}", "", "视图:"]
        lines += [f"  • {v.view}: {VIEW_STATE_TEXT.get(v.state, v.state)}" + (f"（{v.detail}）" if v.detail else "")
                  for v in views]
        lines += ["", "已解决:", _items_text(resolved), "", "仍存在:", _items_text(remaining),
                  "", "新出现:", _items_text(new)]
        self.text.setPlainText("\n".join(lines))


# --- 6. save -------------------------------------------------------------------------------

class SavePage(_Page):
    def __init__(self):
        super().__init__("6. 保存", "保存前会备份为 <芯片>.yaml.bak，并在 history/<芯片>.yaml 追加一条修改记录。")
        form = QFormLayout()
        self.source_edit = QLineEdit()
        self.source_edit.setPlaceholderText("例：MCAL R440 CotexR52_THA6412_BGA516.properties")
        form.addRow("来源*:", self.source_edit)
        self.note_edit = QLineEdit()
        form.addRow("说明:", self.note_edit)
        self.version_edit = QLineEdit()
        form.addRow("新版本:", self.version_edit)
        self.author_edit = QLineEdit()
        form.addRow("修改人*:", self.author_edit)
        self.box.addLayout(form)
        self.summary = QLabel()
        self.summary.setWordWrap(True)
        self.box.addWidget(self.summary)
        self.box.addStretch()

    def initializePage(self):
        session = self.session
        names = [p.name for p in session.properties]
        if names:
            self.source_edit.setText("; ".join(names))
        elif not self.source_edit.text():
            self.source_edit.setText("插件所需键扫描" if session.scan_project or session.scan_dirs else "待确认项核实")
        self.version_edit.setText(repair.next_version(session.base.resource_version))
        if not self.author_edit.text():
            self.author_edit.setText(repair.git_author(session.chip_file.parent if session.chip_file else None))
        try:
            chip, _ = session.build()
        except ValueError as e:
            self.summary.setText(f"无法生成修复结果：{e}")
            return
        if not session.has_changes(chip):
            self.summary.setText("没有任何改动，无需保存。")
            return
        applied = repair.diff_ecu_resources(session.base.ecu_resources, chip.ecu_resources)
        to_fill_in = session.added_to_fill_in(chip)
        self.summary.setText(
            f"{session.base.name}：ECU 资源改动 {len(applied.changes)} 处，确认 {len(session.confirm_notes)} 项，"
            f"新增标记 {len(session.new_marks)} 项。"
            + (f"\n⚠ 其中 {len(to_fill_in)} 个条目没有值（待填写），保存后标为待填写，"
               "请在芯片定义设计器“4. ECU 资源”页填值。" if to_fill_in else "")
            + f"\n写入 {session.chip_file}")

    def _confirm_to_fill_in(self) -> bool:
        """Ask before saving entries without a value; True when there are none or the user agrees."""
        session = self.session
        try:
            keys = session.added_to_fill_in(session.build()[0])
        except ValueError:
            return True             # the save reports the error
        if not keys:
            return True
        shown = "\n".join(f"  • {k}" for k in keys[:10]) + (f"\n  … 另有 {len(keys) - 10} 个" if len(keys) > 10 else "")
        reply = QMessageBox.question(
            self, "ECU 资源待填写",
            f"本次修复新增 {len(keys)} 个没有值的条目：\n{shown}\n\n"
            "ecu:get() 会得到空值。保存后它们标为“待填写”，芯片显示为资料不完整，直到填写。确定要保存吗？",
            QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        return reply == QMessageBox.Yes

    def validatePage(self) -> bool:
        if self.wizard().result_info is not None:
            return True             # already saved: QWizard.accept() validates the page again
        session = self.session
        source, author = self.source_edit.text().strip(), self.author_edit.text().strip()
        if not source or not author:
            QMessageBox.warning(self, "信息不完整", "请填写来源和修改人。")
            return False
        if not self._confirm_to_fill_in():
            return False
        record = repair.RepairRecord(source=source, note=self.note_edit.text().strip(), author=author,
                                     version=self.version_edit.text().strip())
        try:
            result = session.save(record)
        except repair.ChipFileChanged as e:
            QMessageBox.warning(self, "文件已被修改",
                                f"{e}\n\n请关闭向导，重新打开后再修复（不会覆盖别人的修改）。")
            return False
        except Exception as e:  # noqa: BLE001 - shown to the user, the wizard stays open
            logger.exception("saving the repaired chip failed")
            QMessageBox.critical(self, "保存失败", str(e))
            return False
        if not result.saved:
            QMessageBox.information(self, "没有改动", "芯片没有任何改动，未保存。")
            return False
        self.wizard().result_info = result
        return True


# --- wizard --------------------------------------------------------------------------------

class ChipRepairWizard(QWizard):
    """Repair a chip of the chip library; emits ``chip_repaired(name)`` after saving."""

    chip_repaired = Signal(str)

    def __init__(self, database: Optional[ChipDatabase] = None, chip_name: Optional[str] = None,
                 project=None, parent=None):
        super().__init__(parent)
        from ...core.hardware.chip_database import get_default_chip_database

        self.database = database or get_default_chip_database()
        self.project = project
        self.initial_chip = chip_name
        self.session: Optional[repair.RepairSession] = None
        self.result_info: Optional[repair.SaveResult] = None

        self.setWindowTitle("芯片修复向导")
        self.setWizardStyle(QWizard.ModernStyle)
        self.setOption(QWizard.HaveHelpButton, False)
        self.resize(900, 640)
        self.chip_page, self.sources_page, self.changes_page = ChipPage(), SourcesPage(), ChangesPage()
        self.marks_page, self.review_page, self.save_page = MarksPage(), ReviewPage(), SavePage()
        for page in (self.chip_page, self.sources_page, self.changes_page,
                     self.marks_page, self.review_page, self.save_page):
            self.addPage(page)

    def accept(self):
        super().accept()
        if self.result_info is not None:
            self.chip_repaired.emit(self.session.base.name)
