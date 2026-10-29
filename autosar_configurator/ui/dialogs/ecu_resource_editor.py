"""
ECU resource editor

Page of the chip definition designer for the chip's ``ecu_resources``: all keys
of all modules, grouped by module, with editing by value shape (scalar, list,
index range view of long lists, multi-line string), search and filters,
consistency hints and a guide that lists the keys the modules need.

The widget owns a working copy of the resources and writes only values that the
chip YAML loader would accept, so whatever can be entered can also be saved and
loaded again.
"""
import copy
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QBrush, QColor, QFont
from PySide6.QtWidgets import (
    QCheckBox,
    QComboBox,
    QDialog,
    QDialogButtonBox,
    QFileDialog,
    QHBoxLayout,
    QHeaderView,
    QInputDialog,
    QLabel,
    QLineEdit,
    QListWidget,
    QListWidgetItem,
    QMessageBox,
    QPlainTextEdit,
    QPushButton,
    QSplitter,
    QStackedWidget,
    QTableWidget,
    QTableWidgetItem,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...core.hardware.ecu_resource_data import (
    PLACEHOLDER,
    EcuResources,
    check_key_name,
    check_module_name,
    delete_entry,
    flatten_ecu_resources,
    infer_scalar,
    list_to_range_rows,
    range_rows_to_list,
    rename_entry,
    rename_module,
    set_entry,
    value_type_name,
)
from ...core.hardware.ecu_resource_diagnostics import (
    DYNAMIC_KEYS_NOTE,
    check_consistency,
    collect_referenced_keys,
    collect_referenced_keys_in_dirs,
)
from ...core.hardware.ecu_resource_resolver import library_other_chip_keys

FILTER_ALL, FILTER_EMPTY, FILTER_PROBLEMS = 0, 1, 2
_PAGE_EMPTY, _PAGE_SCALAR, _PAGE_TEXT, _PAGE_LIST = range(4)
_MONO = QFont("Menlo, Monaco, Consolas, Courier New", 10)
_LONG_TEXT = 80           # strings longer than this are edited in the multi-line field
_MISSING_BRUSH = QBrush(QColor("#fff3cd"))
_PROBLEM_BRUSH = QBrush(QColor("#f8d7da"))


def _summary(value: Any, max_len: int = 60) -> str:
    if value is None:
        return "(to fill in)"
    if isinstance(value, list):
        text = ", ".join(str(v) for v in value)
        if len(text) > max_len:
            return text[:max_len].rstrip(", ") + f" ... ({len(value)} items)"
        return text
    text = str(value).replace("\n", " ")
    return text if len(text) <= max_len else text[:max_len] + " ..."


class NeededKeysDialog(QDialog):
    """Pick keys that modules reference but the chip has no value for."""

    def __init__(self, keys: List[Tuple[str, List[str]]], parent=None):
        super().__init__(parent)
        self.setWindowTitle("所需键 (Needed Keys)")
        self.resize(560, 460)
        layout = QVBoxLayout(self)
        note = QLabel(
            "以下键被模块的 xdm 或模板引用，但当前芯片没有值。选中后加入为“待填写”条目。\n"
            + DYNAMIC_KEYS_NOTE + "\n被芯片条件保护的键也可能出现在这里。")
        note.setWordWrap(True)
        layout.addWidget(note)
        self.list = QListWidget()
        for key, modules in keys:
            item = QListWidgetItem(f"{key}    ({', '.join(modules)})")
            item.setData(Qt.UserRole, key)
            item.setFlags(item.flags() | Qt.ItemIsUserCheckable)
            item.setCheckState(Qt.Unchecked)
            self.list.addItem(item)
        layout.addWidget(self.list, 1)

        row = QHBoxLayout()
        all_btn = QPushButton("全选")
        all_btn.clicked.connect(lambda: self._check_all(Qt.Checked))
        none_btn = QPushButton("全不选")
        none_btn.clicked.connect(lambda: self._check_all(Qt.Unchecked))
        row.addWidget(all_btn)
        row.addWidget(none_btn)
        row.addStretch()
        layout.addLayout(row)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.button(QDialogButtonBox.Ok).setText("加入待填写 (Add)")
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)

    def _check_all(self, state):
        for i in range(self.list.count()):
            self.list.item(i).setCheckState(state)

    def selected_keys(self) -> List[str]:
        return [self.list.item(i).data(Qt.UserRole) for i in range(self.list.count())
                if self.list.item(i).checkState() == Qt.Checked]


class EcuResourceEditor(QWidget):
    """Tree of modules and keys with a value editor for the selected key."""

    changed = Signal()
    import_requested = Signal()

    def __init__(self, parent=None):
        super().__init__(parent)
        self._res: EcuResources = {}
        self._problem_keys: Set[str] = set()
        self._added_placeholders: Set[str] = set()           # flat keys added by the needed-keys guide
        self._current: Optional[Tuple[str, str]] = None      # (module, name) being edited
        self._chip_database = None
        self._chip_name = None
        self._project = None
        self._build_ui()

    # --------------------------------------------------------------- public API

    def set_resources(self, resources: EcuResources) -> None:
        """Replace the edited data (the editor works on its own copy)."""
        self._res = copy.deepcopy(resources or {})
        self._added_placeholders = set()
        self._current = None
        self._refresh_all()

    def resources(self) -> EcuResources:
        return copy.deepcopy(self._res)

    def added_placeholders(self) -> List[str]:
        """Flat keys added as entries to fill in since the resources were set, in key order."""
        return sorted(self._added_placeholders)

    def set_context(self, chip_database=None, chip_name: Optional[str] = None, project=None) -> None:
        """What the needed-keys guide may use: the chip library, the chip's name (or a
        callable returning it) and the project."""
        self._chip_database = chip_database
        self._chip_name = chip_name
        self._project = project
        self.scan_project_btn.setEnabled(project is not None)

    # ----------------------------------------------------------------- building

    def _build_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 8, 8, 8)

        top = QHBoxLayout()
        self.search_edit = QLineEdit()
        self.search_edit.setPlaceholderText("搜索键名或值… (Search key or value)")
        self.search_edit.textChanged.connect(self._apply_filter)
        top.addWidget(self.search_edit, 1)
        self.filter_combo = QComboBox()
        self.filter_combo.addItems(["全部 (All)", "待填写 (To fill in)", "有问题 (With problems)"])
        self.filter_combo.currentIndexChanged.connect(self._apply_filter)
        top.addWidget(self.filter_combo)
        self.import_btn = QPushButton("📥 导入 .properties…")
        self.import_btn.clicked.connect(self.import_requested.emit)
        top.addWidget(self.import_btn)
        layout.addLayout(top)

        splitter = QSplitter(Qt.Horizontal)

        left = QWidget()
        left_layout = QVBoxLayout(left)
        left_layout.setContentsMargins(0, 0, 0, 0)
        self.tree = QTreeWidget()
        self.tree.setColumnCount(3)
        self.tree.setHeaderLabels(["键 (Key)", "值 (Value)", "类型"])
        self.tree.header().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tree.header().setSectionResizeMode(1, QHeaderView.Stretch)
        self.tree.setUniformRowHeights(True)
        self.tree.currentItemChanged.connect(self._on_current_changed)
        left_layout.addWidget(self.tree, 1)

        buttons = QHBoxLayout()
        for text, slot in (("新增模块", self._add_module), ("新增键", self._add_key),
                           ("重命名", self._rename), ("删除", self._delete)):
            btn = QPushButton(text)
            btn.clicked.connect(slot)
            buttons.addWidget(btn)
        left_layout.addLayout(buttons)

        scan = QHBoxLayout()
        self.scan_project_btn = QPushButton("扫描项目模块所需键")
        self.scan_project_btn.setToolTip("扫描项目已加载模块的 xdm 与模板，列出缺少值的键")
        self.scan_project_btn.clicked.connect(self._scan_project)
        self.scan_project_btn.setEnabled(False)
        scan.addWidget(self.scan_project_btn)
        self.scan_dir_btn = QPushButton("从插件目录扫描所需键…")
        self.scan_dir_btn.setToolTip("选择插件根目录（含 config/*.xdm 与 generate_PB/），列出缺少值的键")
        self.scan_dir_btn.clicked.connect(self._scan_directory)
        scan.addWidget(self.scan_dir_btn)
        left_layout.addLayout(scan)
        splitter.addWidget(left)

        splitter.addWidget(self._build_value_panel())
        splitter.setSizes([520, 420])
        layout.addWidget(splitter, 1)

        self.hint_label = QLabel()
        self.hint_label.setWordWrap(True)
        self.hint_label.setStyleSheet("color: #8a4b00;")
        layout.addWidget(self.hint_label)

    def _build_value_panel(self) -> QWidget:
        panel = QWidget()
        outer = QVBoxLayout(panel)
        outer.setContentsMargins(0, 0, 0, 0)
        self.key_label = QLabel("请选择左侧的键")
        self.key_label.setStyleSheet("font-weight: bold;")
        outer.addWidget(self.key_label)

        self.stack = QStackedWidget()

        empty = QLabel("选择一个键以编辑它的值。")
        empty.setAlignment(Qt.AlignCenter)
        self.stack.addWidget(empty)

        scalar = QWidget()
        s_layout = QVBoxLayout(scalar)
        self.scalar_edit = QLineEdit()
        self.scalar_edit.setFont(_MONO)
        self.scalar_edit.textChanged.connect(self._update_inferred_type)
        s_layout.addWidget(self.scalar_edit)
        self.keep_string_check = QCheckBox("按字符串保存 (Keep as string)")
        self.keep_string_check.toggled.connect(self._update_inferred_type)
        s_layout.addWidget(self.keep_string_check)
        self.inferred_label = QLabel()
        s_layout.addWidget(self.inferred_label)
        s_buttons = QHBoxLayout()
        self.scalar_apply = QPushButton("应用 (Apply)")
        self.scalar_apply.clicked.connect(self._apply_scalar)
        s_buttons.addWidget(self.scalar_apply)
        to_list = QPushButton("转为列表")
        to_list.clicked.connect(self._scalar_to_list)
        s_buttons.addWidget(to_list)
        s_buttons.addStretch()
        s_layout.addLayout(s_buttons)
        s_layout.addStretch()
        self.stack.addWidget(scalar)

        text = QWidget()
        t_layout = QVBoxLayout(text)
        self.text_edit = QPlainTextEdit()
        self.text_edit.setFont(_MONO)
        t_layout.addWidget(self.text_edit, 1)
        self.text_apply = QPushButton("应用 (Apply)")
        self.text_apply.clicked.connect(self._apply_text)
        t_layout.addWidget(self.text_apply)
        self.stack.addWidget(text)

        lst = QWidget()
        l_layout = QVBoxLayout(lst)
        view_row = QHBoxLayout()
        self.range_view_btn = QPushButton("区间视图 (Range view)")
        self.range_view_btn.setCheckable(True)
        self.range_view_btn.toggled.connect(self._on_view_toggled)
        view_row.addWidget(self.range_view_btn)
        self.list_info = QLabel()
        view_row.addWidget(self.list_info, 1)
        l_layout.addLayout(view_row)
        self.list_table = QTableWidget(0, 1)
        self.list_table.setHorizontalHeaderLabels(["值"])
        self.list_table.horizontalHeader().setStretchLastSection(True)
        self.list_table.setFont(_MONO)
        l_layout.addWidget(self.list_table, 1)
        row = QHBoxLayout()
        self.item_buttons: List[QPushButton] = []
        for text_, slot in (("增加一行", self._list_add_row), ("删除所选行", self._list_remove_rows),
                            ("上移", lambda: self._list_move(-1)), ("下移", lambda: self._list_move(1))):
            btn = QPushButton(text_)
            btn.clicked.connect(slot)
            row.addWidget(btn)
            self.item_buttons.append(btn)
        row.addStretch()
        l_layout.addLayout(row)
        row2 = QHBoxLayout()
        self.list_apply = QPushButton("应用 (Apply)")
        self.list_apply.clicked.connect(self._apply_list)
        row2.addWidget(self.list_apply)
        to_scalar = QPushButton("转为标量")
        to_scalar.clicked.connect(self._list_to_scalar)
        row2.addWidget(to_scalar)
        row2.addStretch()
        l_layout.addLayout(row2)
        self.stack.addWidget(lst)

        outer.addWidget(self.stack, 1)
        return panel

    # ------------------------------------------------------------- tree refresh

    def _refresh_all(self):
        """Rebuild the tree, hints and filters from the working copy."""
        keep = self._current
        self.tree.blockSignals(True)
        self.tree.clear()
        for module, entries in self._res.items():
            mod_item = QTreeWidgetItem([module, f"{len(entries)} 项", ""])
            mod_item.setData(0, Qt.UserRole, (module, None))
            font = mod_item.font(0)
            font.setBold(True)
            mod_item.setFont(0, font)
            self.tree.addTopLevelItem(mod_item)
            for name, value in entries.items():
                self._add_key_item(mod_item, module, name, value)
        self.tree.blockSignals(False)
        self._update_hints()
        self._color_items()
        self._apply_filter()
        if keep and self._select(keep[0], keep[1]):
            return
        self._show_page(None)

    def _add_key_item(self, mod_item, module, name, value):
        item = QTreeWidgetItem([name, _summary(value), value_type_name(value)])
        item.setData(0, Qt.UserRole, (module, name))
        mod_item.addChild(item)
        return item

    def _item_for(self, module: str, name: Optional[str]) -> Optional[QTreeWidgetItem]:
        for i in range(self.tree.topLevelItemCount()):
            top = self.tree.topLevelItem(i)
            if tuple(top.data(0, Qt.UserRole)) == (module, None):
                if name is None:
                    return top
                for j in range(top.childCount()):
                    if tuple(top.child(j).data(0, Qt.UserRole)) == (module, name):
                        return top.child(j)
        return None

    def _select(self, module: str, name: Optional[str]) -> bool:
        item = self._item_for(module, name)
        if item is None:
            return False
        self.tree.setCurrentItem(item)
        return True

    def _update_hints(self):
        flat = flatten_ecu_resources(self._res)
        messages = check_consistency(flat)
        self._problem_keys = {key for key in flat for m in messages if key in m}
        self.hint_label.setText("\n".join(messages))

    def _color_items(self):
        for i in range(self.tree.topLevelItemCount()):
            top = self.tree.topLevelItem(i)
            for j in range(top.childCount()):
                child = top.child(j)
                module, name = child.data(0, Qt.UserRole)
                brush = None
                if self._res[module][name] is PLACEHOLDER:
                    brush = _MISSING_BRUSH
                elif f"{module}.{name}" in self._problem_keys:
                    brush = _PROBLEM_BRUSH
                for col in range(3):
                    child.setBackground(col, brush or QBrush())

    def _update_row(self, module: str, name: str):
        item = self._item_for(module, name)
        if item is not None:
            value = self._res[module][name]
            item.setText(1, _summary(value))
            item.setText(2, value_type_name(value))
        top = self._item_for(module, None)
        if top is not None:
            top.setText(1, f"{len(self._res.get(module, {}))} 项")
        self._update_hints()
        self._color_items()
        self._apply_filter()

    # ------------------------------------------------------------------ filters

    def _apply_filter(self, *_):
        needle = self.search_edit.text().strip().lower()
        mode = self.filter_combo.currentIndex()
        for i in range(self.tree.topLevelItemCount()):
            top = self.tree.topLevelItem(i)
            visible_children = 0
            for j in range(top.childCount()):
                child = top.child(j)
                module, name = child.data(0, Qt.UserRole)
                value = self._res[module][name]
                show = True
                if needle:
                    show = needle in name.lower() or needle in f"{module}.{name}".lower() \
                        or needle in _summary(value, 10_000).lower()
                if show and mode == FILTER_EMPTY:
                    show = value is PLACEHOLDER
                elif show and mode == FILTER_PROBLEMS:
                    show = f"{module}.{name}" in self._problem_keys
                child.setHidden(not show)
                visible_children += show
            top.setHidden(visible_children == 0 and (bool(needle) or mode != FILTER_ALL))
            if needle and visible_children:
                top.setExpanded(True)

    # ------------------------------------------------------- selection and pages

    def _on_current_changed(self, current, _previous):
        if current is None:
            self._show_page(None)
            return
        module, name = current.data(0, Qt.UserRole)
        self._show_page((module, name) if name is not None else None)

    def _show_page(self, target: Optional[Tuple[str, str]]):
        self._current = target
        if target is None:
            self.key_label.setText("请选择左侧的键")
            self.stack.setCurrentIndex(_PAGE_EMPTY)
            return
        module, name = target
        value = self._res[module][name]
        self.key_label.setText(f"{module}.{name}    [{value_type_name(value)}]")
        if isinstance(value, list):
            self._load_list(value)
            self.stack.setCurrentIndex(_PAGE_LIST)
        elif isinstance(value, str) and (len(value) > _LONG_TEXT or value != value.strip()):
            self.text_edit.setPlainText(value)
            self.stack.setCurrentIndex(_PAGE_TEXT)
        else:
            self.scalar_edit.setText("" if value is None else str(value))
            self.keep_string_check.setChecked(isinstance(value, str) and infer_scalar(value) != value)
            self._update_inferred_type()
            self.stack.setCurrentIndex(_PAGE_SCALAR)

    def _flat_key(self) -> str:
        module, name = self._current
        return f"{module}.{name}"

    def _store(self, value: Any) -> bool:
        """Write a value of the current key; shows the reason and keeps the old value on failure."""
        module, name = self._current
        try:
            set_entry(self._res, module, name, value)
        except ValueError as e:
            QMessageBox.warning(self, "值无效", str(e))
            return False
        self._update_row(module, name)
        self._show_page(self._current)
        self.changed.emit()
        return True

    # ------------------------------------------------------------ scalar / text

    def _update_inferred_type(self, *_):
        value = infer_scalar(self.scalar_edit.text(), self.keep_string_check.isChecked())
        self.inferred_label.setText(f"将保存为: {value_type_name(value)}"
                                    + ("（空，待填写）" if value is None else ""))

    def _apply_scalar(self):
        if self._current:
            self._store(infer_scalar(self.scalar_edit.text(), self.keep_string_check.isChecked()))

    def _apply_text(self):
        if not self._current:
            return
        text = self.text_edit.toPlainText()
        # a leading space is part of the value (templates match on ' X'); trailing newline is not
        self._store(text.rstrip("\n") if text.strip() else PLACEHOLDER)

    def _scalar_to_list(self):
        if self._current:
            value = infer_scalar(self.scalar_edit.text(), self.keep_string_check.isChecked())
            self._store([] if value is PLACEHOLDER else [value])

    # --------------------------------------------------------------------- list

    def _load_list(self, values: List[Any]):
        self.range_view_btn.blockSignals(True)
        self.range_view_btn.setChecked(False)
        self.range_view_btn.blockSignals(False)
        self._fill_item_table(values)
        self._set_item_buttons(True)

    def _fill_item_table(self, values: List[Any]):
        self.list_table.setColumnCount(1)
        self.list_table.setHorizontalHeaderLabels(["值"])
        self.list_table.setRowCount(len(values))
        for i, v in enumerate(values):
            self.list_table.setItem(i, 0, QTableWidgetItem("" if v is None else str(v)))
        self.list_info.setText(f"{len(values)} 项")

    def _fill_range_table(self, values: List[Any]):
        rows = list_to_range_rows(values)
        self.list_table.setColumnCount(2)
        self.list_table.setHorizontalHeaderLabels(["下标区间", "值"])
        self.list_table.setRowCount(len(rows))
        for i, (rng, v) in enumerate(rows):
            self.list_table.setItem(i, 0, QTableWidgetItem(rng))
            self.list_table.setItem(i, 1, QTableWidgetItem("" if v is None else str(v)))
        self.list_info.setText(f"{len(values)} 项，{len(rows)} 个区间")

    def _set_item_buttons(self, enabled: bool):
        for btn in self.item_buttons[2:]:
            btn.setEnabled(enabled)

    def _table_text(self, row: int, col: int) -> str:
        item = self.list_table.item(row, col)
        return item.text() if item else ""

    def _list_from_table(self) -> List[Any]:
        """The list the table currently shows; raises ValueError with the reason."""
        return self._list_from_table_for_switch(self.range_view_btn.isChecked())

    def _on_view_toggled(self, checked: bool):
        if self._current is None:
            return
        try:
            values = self._list_from_table_for_switch(not checked)
        except ValueError as e:
            QMessageBox.warning(self, "值无效", str(e))
            self.range_view_btn.blockSignals(True)
            self.range_view_btn.setChecked(not checked)
            self.range_view_btn.blockSignals(False)
            return
        if checked:
            self._fill_range_table(values)
        else:
            self._fill_item_table(values)
        self._set_item_buttons(not checked)

    def _list_from_table_for_switch(self, was_range_view: bool) -> List[Any]:
        """Read the table as it was before the view changed."""
        if was_range_view:
            rows = [(self._table_text(r, 0), infer_scalar(self._table_text(r, 1)))
                    for r in range(self.list_table.rowCount())]
            return range_rows_to_list(self._flat_key(), rows)
        values = []
        for r in range(self.list_table.rowCount()):
            value = infer_scalar(self._table_text(r, 0))
            if value is PLACEHOLDER:
                raise ValueError(f"{self._flat_key()}: list item {r} is empty")
            values.append(value)
        return values

    def _list_add_row(self):
        row = self.list_table.rowCount()
        self.list_table.insertRow(row)
        self.list_table.setItem(row, 0, QTableWidgetItem(""))

    def _list_remove_rows(self):
        for row in sorted({i.row() for i in self.list_table.selectedItems()}, reverse=True):
            self.list_table.removeRow(row)

    def _list_move(self, delta: int):
        rows = sorted({i.row() for i in self.list_table.selectedItems()})
        if len(rows) != 1:
            return
        src, dst = rows[0], rows[0] + delta
        if not 0 <= dst < self.list_table.rowCount():
            return
        a, b = self._table_text(src, 0), self._table_text(dst, 0)
        self.list_table.item(src, 0).setText(b)
        self.list_table.item(dst, 0).setText(a)
        self.list_table.selectRow(dst)

    def _apply_list(self):
        if not self._current:
            return
        try:
            values = self._list_from_table()
        except ValueError as e:
            QMessageBox.warning(self, "值无效", str(e))
            return
        self._store(values)

    def _list_to_scalar(self):
        if not self._current:
            return
        try:
            values = self._list_from_table()
        except ValueError as e:
            QMessageBox.warning(self, "值无效", str(e))
            return
        if len(values) > 1:
            QMessageBox.information(self, "转为标量", "列表有多个元素，无法转为标量。")
            return
        self._store(values[0] if values else PLACEHOLDER)

    # ------------------------------------------------------- module / key actions

    def _selected_target(self) -> Optional[Tuple[str, Optional[str]]]:
        item = self.tree.currentItem()
        return item.data(0, Qt.UserRole) if item is not None else None

    def _add_module(self):
        text, ok = QInputDialog.getText(self, "新增模块", "模块名（不含 '.'）:")
        if not ok:
            return
        try:
            module = check_module_name(text)
        except ValueError as e:
            QMessageBox.warning(self, "名称无效", str(e))
            return
        if module in self._res:
            QMessageBox.warning(self, "名称无效", f"模块 {module} 已存在")
            return
        self._res[module] = {}
        self._refresh_all()
        self._select(module, None)
        self.changed.emit()

    def _add_key(self):
        target = self._selected_target()
        module = target[0] if target else None
        if module is None:
            text, ok = QInputDialog.getText(self, "新增键", "模块名:")
            if not ok:
                return
            try:
                module = check_module_name(text)
            except ValueError as e:
                QMessageBox.warning(self, "名称无效", str(e))
                return
        name, ok = QInputDialog.getText(self, "新增键", f"{module} 下的键名:")
        if not ok:
            return
        try:
            name = check_key_name(name)
        except ValueError as e:
            QMessageBox.warning(self, "名称无效", str(e))
            return
        if name in self._res.get(module, {}):
            QMessageBox.warning(self, "名称无效", f"{module}.{name} 已存在")
            return
        set_entry(self._res, module, name, PLACEHOLDER)
        self._refresh_all()
        self._select(module, name)
        self.changed.emit()

    def add_placeholders(self, flat_keys: List[str]) -> int:
        """Add keys as entries to fill in; returns how many were added (keys without a module are skipped)."""
        added = 0
        for key in flat_keys:
            if "." not in key:
                continue
            module, name = key.split(".", 1)
            if name in self._res.get(module, {}):
                continue
            try:
                set_entry(self._res, module, name, PLACEHOLDER)
            except ValueError:
                continue
            self._added_placeholders.add(f"{module}.{name}")
            added += 1
        if added:
            self._refresh_all()
            self.changed.emit()
        return added

    def _rename(self):
        target = self._selected_target()
        if not target:
            return
        module, name = target
        old = name if name is not None else module
        text, ok = QInputDialog.getText(self, "重命名", "新名称:", text=old)
        if not ok or text.strip() == old:
            return
        try:
            if name is None:
                rename_module(self._res, module, text)
                new_target = (check_module_name(text), None)
            else:
                rename_entry(self._res, module, name, text)
                new_target = (module, check_key_name(text))
        except ValueError as e:
            QMessageBox.warning(self, "名称无效", str(e))
            return
        self._current = None
        self._refresh_all()
        self._select(*new_target)
        self.changed.emit()

    def _delete(self):
        target = self._selected_target()
        if not target:
            return
        module, name = target
        what = f"模块 {module}（含 {len(self._res.get(module, {}))} 个键）" if name is None else f"{module}.{name}"
        if QMessageBox.question(self, "删除", f"删除 {what}？",
                                QMessageBox.Yes | QMessageBox.No, QMessageBox.No) != QMessageBox.Yes:
            return
        if name is None:
            self._res.pop(module, None)
        else:
            delete_entry(self._res, module, name)
        self._current = None
        self._refresh_all()
        self.changed.emit()

    # ------------------------------------------------------ needed keys guidance

    def _needed_keys(self, referenced: Dict[str, Set[str]]) -> List[Tuple[str, List[str]]]:
        """Referenced keys the chip has no value for and that no other chip alone defines."""
        have = {k.lower() for k in flatten_ecu_resources(self._res)}
        others: Dict[str, List[str]] = {}
        if self._chip_database is not None:
            name = self._chip_name() if callable(self._chip_name) else self._chip_name
            others = library_other_chip_keys(self._chip_database, name)
        return [(key, sorted(modules)) for key, modules in sorted(referenced.items())
                if key.lower() not in have and key.lower() not in others]

    def _offer_needed_keys(self, referenced: Dict[str, Set[str]], source: str):
        keys = self._needed_keys(referenced)
        if not keys:
            QMessageBox.information(
                self, "所需键", f"{source}中引用的键都已有值，或只属于其他芯片。\n" + DYNAMIC_KEYS_NOTE)
            return
        dialog = NeededKeysDialog(keys, self)
        if dialog.exec():
            added = self.add_placeholders(dialog.selected_keys())
            self.hint_label.setText(f"已加入 {added} 个待填写条目。" + "\n" + self.hint_label.text())

    def _scan_project(self):
        if self._project is not None:
            self._offer_needed_keys(collect_referenced_keys(self._project), "项目已加载的模块")

    def _scan_directory(self):
        directory = QFileDialog.getExistingDirectory(self, "选择插件根目录", str(Path.home()))
        if directory:
            self._offer_needed_keys(collect_referenced_keys_in_dirs([Path(directory)]), "所选目录")
