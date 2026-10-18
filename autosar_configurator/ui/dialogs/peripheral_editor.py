"""
Peripheral instance editor

Page of the chip definition designer for the chip's peripheral instances of any
type (``resources`` in the chip YAML): CAN controllers, ADC units, GPT/PWM/ICU
channels, interrupt sources, clock sources, ...  The hardware mapping rules
tell which resource types exist and which instance properties each rule reads;
the editor offers those types, pre-fills those properties and points out
instances that lack one.  Pins are not edited here (pin table page).
"""
import copy
from typing import Any, Dict, List, Optional, Tuple

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QBrush, QColor
from PySide6.QtWidgets import (
    QAbstractItemView,
    QHBoxLayout,
    QHeaderView,
    QInputDialog,
    QLabel,
    QListWidget,
    QListWidgetItem,
    QMessageBox,
    QPushButton,
    QSplitter,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...core.hardware.ecu_resource_data import infer_scalar, normalize_value
from ...core.hardware.generic_resource import GenericResourceDef

# Derived from the pin table, never edited as peripheral instances
PIN_TYPES = {"gpio_port", "gpio_pin"}

_ID_COL, _NAME_COL = 0, 1
_MISSING = QBrush(QColor("#fff3cd"))
_INVALID = QBrush(QColor("#f8d7da"))

Rows = List[Dict[str, Any]]      # {"id": str, "name": str, "props": {name: value}}


def _text(value: Any) -> str:
    if value is None:
        return ""
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, list):
        return ", ".join(_text(v) for v in value)
    return str(value)


def _parse(text: str) -> Any:
    """Cell text -> property value: comma separated text is a list."""
    text = text.strip()
    if not text:
        return None
    if "," in text:
        return [infer_scalar(part) for part in text.split(",") if part.strip()]
    return infer_scalar(text)


class PeripheralEditor(QWidget):
    """Resource types on the left, the instances of the selected type on the right."""

    changed = Signal()

    def __init__(self, requirements: Optional[Dict[str, Dict[str, Any]]] = None, parent=None):
        """
        Args:
            requirements: ``rule_resource_requirements()`` - per resource type the
                modules of its mapping rules and the properties they read
        """
        super().__init__(parent)
        self._requirements = {t: r for t, r in (requirements or {}).items() if t not in PIN_TYPES}
        self._data: Dict[str, Rows] = {}
        self._columns: Dict[str, List[str]] = {}
        self._current: Optional[str] = None
        # Pin-type instances found in "resources" (normally pins come from the pin
        # table): not shown here, but kept unchanged so saving never drops them
        self._kept_pin_resources: Dict[str, List[GenericResourceDef]] = {}
        self._build_ui()

    # ----------------------------------------------------------------- public API

    def set_resources(self, resources: Dict[str, List[GenericResourceDef]]) -> None:
        self._data, self._columns = {}, {}
        self._kept_pin_resources = {}
        for res_type, instances in (resources or {}).items():
            if res_type in PIN_TYPES:
                self._kept_pin_resources[res_type] = copy.deepcopy(instances)
                continue
            rows = [{"id": r.resource_id,
                     "name": r.display_name if r.display_name != r.resource_id else "",
                     "props": copy.deepcopy(r.properties)} for r in instances]
            self._data[res_type] = rows
            self._columns[res_type] = self._column_order(res_type, rows)
        self._current = None
        self._refresh_types()

    def resources(self) -> Dict[str, List[GenericResourceDef]]:
        """Instances as entered; rows without a usable id are left out."""
        return self._build(strict=False)

    def validated_resources(self) -> Dict[str, List[GenericResourceDef]]:
        """Instances as entered; raises ValueError naming the first problem."""
        return self._build(strict=True)

    def problems(self) -> List[str]:
        """Invalid instances and properties the mapping rules need but are missing."""
        lines = []
        for res_type, rows in self._data.items():
            lines.extend(self._row_problems(res_type, rows))
        return lines

    # ------------------------------------------------------------------ building

    def _build_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 8, 8, 8)
        intro = QLabel("外设实例（任意类型）。可选类型来自硬件映射规则；规则需要的属性会预填，"
                       "缺少时标黄。引脚在“引脚复用矩阵”页编辑。")
        intro.setWordWrap(True)
        layout.addWidget(intro)

        splitter = QSplitter(Qt.Horizontal)

        left = QWidget()
        left_layout = QVBoxLayout(left)
        left_layout.setContentsMargins(0, 0, 0, 0)
        left_layout.addWidget(QLabel("外设类型"))
        self.type_list = QListWidget()
        self.type_list.currentItemChanged.connect(self._on_type_changed)
        left_layout.addWidget(self.type_list, 1)
        type_buttons = QHBoxLayout()
        add_type = QPushButton("新增类型")
        add_type.clicked.connect(self._add_type)
        type_buttons.addWidget(add_type)
        del_type = QPushButton("删除类型")
        del_type.clicked.connect(self._delete_type)
        type_buttons.addWidget(del_type)
        left_layout.addLayout(type_buttons)
        splitter.addWidget(left)

        right = QWidget()
        right_layout = QVBoxLayout(right)
        right_layout.setContentsMargins(0, 0, 0, 0)
        self.type_label = QLabel()
        self.type_label.setStyleSheet("font-weight: bold;")
        right_layout.addWidget(self.type_label)
        self.table = QTableWidget(0, 2)
        self.table.setSelectionBehavior(QAbstractItemView.SelectItems)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Interactive)
        self.table.horizontalHeader().setStretchLastSection(True)
        self.table.cellChanged.connect(self._on_cell_changed)
        right_layout.addWidget(self.table, 1)
        row_buttons = QHBoxLayout()
        for text, slot in (("增加实例", self._add_instance), ("复制实例", self._copy_instance),
                           ("删除实例", self._delete_instances), ("批量添加…", self._batch_add),
                           ("增加属性", self._add_property), ("删除属性", self._delete_property)):
            btn = QPushButton(text)
            btn.clicked.connect(slot)
            row_buttons.addWidget(btn)
        row_buttons.addStretch()
        right_layout.addLayout(row_buttons)
        splitter.addWidget(right)
        splitter.setSizes([260, 680])
        layout.addWidget(splitter, 1)

        self.hint_label = QLabel()
        self.hint_label.setWordWrap(True)
        self.hint_label.setStyleSheet("color: #8a4b00;")
        layout.addWidget(self.hint_label)

    def _rule_props(self, res_type: str) -> List[str]:
        return list(self._requirements.get(res_type, {}).get("properties", []))

    def _type_label(self, res_type: str) -> str:
        modules = self._requirements.get(res_type, {}).get("modules", [])
        return f"{res_type} ({', '.join(modules)})" if modules else res_type

    def _column_order(self, res_type: str, rows: Rows) -> List[str]:
        """Rule properties first (in rule order), then the others by name."""
        present = {k for row in rows for k in row["props"]}
        rule = self._rule_props(res_type)
        return rule + sorted(present - set(rule))

    # ------------------------------------------------------------------ types

    def _refresh_types(self, select: Optional[str] = None):
        keep = select or self._current
        self.type_list.blockSignals(True)
        self.type_list.clear()
        for res_type in self._data:
            item = QListWidgetItem(f"{self._type_label(res_type)}  [{len(self._data[res_type])}]")
            item.setData(Qt.UserRole, res_type)
            self.type_list.addItem(item)
        self.type_list.blockSignals(False)
        target = keep if keep in self._data else (next(iter(self._data), None))
        for i in range(self.type_list.count()):
            if self.type_list.item(i).data(Qt.UserRole) == target:
                self.type_list.setCurrentRow(i)
                break
        else:
            self._current = None
            self._fill_table()
        self._update_hints()

    def _on_type_changed(self, current, _previous):
        self._current = current.data(Qt.UserRole) if current else None
        self._fill_table()

    def _add_type(self):
        offered = [self._type_label(t) for t in self._requirements if t not in self._data]
        text, ok = QInputDialog.getItem(self, "新增外设类型",
                                        "类型（可选规则中的类型，也可直接输入新类型名）:",
                                        offered, 0, True)
        if not ok:
            return
        res_type = text.split(" (", 1)[0].strip()
        if not res_type or res_type in PIN_TYPES:
            QMessageBox.warning(self, "类型无效", f"'{res_type}' 不能作为外设类型（引脚在引脚页编辑）")
            return
        if res_type in self._data:
            QMessageBox.warning(self, "类型已存在", f"类型 {res_type} 已存在")
            return
        self._data[res_type] = []
        self._columns[res_type] = self._rule_props(res_type)
        self._refresh_types(select=res_type)
        self.changed.emit()

    def _delete_type(self):
        if not self._current:
            return
        count = len(self._data[self._current])
        if QMessageBox.question(self, "删除类型", f"删除类型 {self._current}（{count} 个实例）？",
                                QMessageBox.Yes | QMessageBox.No, QMessageBox.No) != QMessageBox.Yes:
            return
        self._data.pop(self._current, None)
        self._columns.pop(self._current, None)
        self._current = None
        self._refresh_types()
        self.changed.emit()

    # ------------------------------------------------------------------ table

    def _fill_table(self):
        self.table.blockSignals(True)
        res_type = self._current
        if res_type is None:
            self.table.setRowCount(0)
            self.table.setColumnCount(2)
            self.table.setHorizontalHeaderLabels(["resource_id", "display_name"])
            self.type_label.setText("请选择或新增外设类型")
            self.table.blockSignals(False)
            return
        columns = self._columns[res_type]
        rows = self._data[res_type]
        rule = set(self._rule_props(res_type))
        self.type_label.setText(self._type_label(res_type))
        self.table.setColumnCount(2 + len(columns))
        self.table.setHorizontalHeaderLabels(
            ["resource_id", "display_name"] + [f"{c} *" if c in rule else c for c in columns])
        self.table.setRowCount(len(rows))
        for r, row in enumerate(rows):
            self.table.setItem(r, _ID_COL, QTableWidgetItem(row["id"]))
            self.table.setItem(r, _NAME_COL, QTableWidgetItem(row["name"]))
            for c, prop in enumerate(columns):
                self.table.setItem(r, 2 + c, QTableWidgetItem(_text(row["props"].get(prop))))
        self.table.blockSignals(False)
        self._color_table()

    def _color_table(self):
        res_type = self._current
        if res_type is None:
            return
        self.table.blockSignals(True)
        rows = self._data[res_type]
        ids = [row["id"].strip() for row in rows]
        rule = set(self._rule_props(res_type))
        for r, row in enumerate(rows):
            bad_id = not ids[r] or ids.count(ids[r]) > 1
            self.table.item(r, _ID_COL).setBackground(_INVALID if bad_id else QBrush())
            for c, prop in enumerate(self._columns[res_type]):
                missing = prop in rule and row["props"].get(prop) is None
                self.table.item(r, 2 + c).setBackground(_MISSING if missing else QBrush())
        self.table.blockSignals(False)

    def _on_cell_changed(self, r: int, c: int):
        res_type = self._current
        if res_type is None:
            return
        row = self._data[res_type][r]
        text = self.table.item(r, c).text()
        if c == _ID_COL:
            row["id"] = text.strip()
        elif c == _NAME_COL:
            row["name"] = text.strip()
        else:
            prop = self._columns[res_type][c - 2]
            old = row["props"].get(prop)
            if text == _text(old):
                return                      # unchanged: keep the original typed value
            value = _parse(text)
            if value is None:
                row["props"].pop(prop, None)
            else:
                try:
                    row["props"][prop] = normalize_value(f"{res_type}.{row['id']}.{prop}", value)
                except ValueError as e:
                    QMessageBox.warning(self, "值无效", str(e))
                    self.table.blockSignals(True)
                    self.table.item(r, c).setText(_text(old))
                    self.table.blockSignals(False)
                    return
        self._color_table()
        self._update_hints()
        self.changed.emit()

    def _selected_rows(self) -> List[int]:
        return sorted({i.row() for i in self.table.selectedItems()})

    def _next_id(self, res_type: str, prefix: str) -> Tuple[str, int]:
        taken = {row["id"] for row in self._data[res_type]}
        n = 0
        while f"{prefix}{n}" in taken:
            n += 1
        return f"{prefix}{n}", n

    def _id_property(self, res_type: str) -> Optional[str]:
        return next((p for p in self._rule_props(res_type) if p.endswith("_id")), None)

    def _default_prefix(self, res_type: str) -> str:
        return res_type.split("_", 1)[0].upper()

    def _append_rows(self, res_type: str, new_rows: Rows):
        self._data[res_type].extend(new_rows)
        for row in new_rows:
            for prop in row["props"]:
                if prop not in self._columns[res_type]:
                    self._columns[res_type].append(prop)
        self._refresh_types(select=res_type)
        self.changed.emit()

    def _add_instance(self):
        res_type = self._current
        if res_type is None:
            return
        suggestion, n = self._next_id(res_type, self._default_prefix(res_type))
        rid, ok = QInputDialog.getText(self, "增加实例", "resource_id:", text=suggestion)
        rid = rid.strip()
        if not ok or not rid:
            return
        if any(row["id"] == rid for row in self._data[res_type]):
            QMessageBox.warning(self, "实例已存在", f"{res_type} 中已有 {rid}")
            return
        props = {}
        id_prop = self._id_property(res_type)
        if id_prop:
            props[id_prop] = n
        self._append_rows(res_type, [{"id": rid, "name": "", "props": props}])

    def _copy_instance(self):
        res_type = self._current
        rows = self._selected_rows()
        if res_type is None or not rows:
            return
        source = self._data[res_type][rows[0]]
        rid = f"{source['id']}_COPY"
        taken = {row["id"] for row in self._data[res_type]}
        k = 2
        while rid in taken:
            rid = f"{source['id']}_COPY{k}"
            k += 1
        self._append_rows(res_type, [{"id": rid, "name": source["name"],
                                      "props": copy.deepcopy(source["props"])}])

    def _delete_instances(self):
        res_type = self._current
        rows = self._selected_rows()
        if res_type is None or not rows:
            return
        for r in reversed(rows):
            del self._data[res_type][r]
        self._refresh_types(select=res_type)
        self.changed.emit()

    def _batch_add(self):
        res_type = self._current
        if res_type is None:
            return
        prefix, ok = QInputDialog.getText(self, "批量添加", "resource_id 前缀:",
                                          text=self._default_prefix(res_type))
        if not ok or not prefix.strip():
            return
        start, ok = QInputDialog.getInt(self, "批量添加", "起始编号:", 0, 0, 100000)
        if not ok:
            return
        count, ok = QInputDialog.getInt(self, "批量添加", "个数:", 1, 1, 4096)
        if not ok:
            return
        self.add_numbered(res_type, prefix.strip(), start, count)

    def add_numbered(self, res_type: str, prefix: str, start: int, count: int) -> int:
        """Add ``prefix<start>`` ... instances; the type's ``*_id`` rule property gets
        the number.  Ids that already exist are skipped.  Returns how many were added."""
        taken = {row["id"] for row in self._data[res_type]}
        id_prop = self._id_property(res_type)
        new_rows = []
        for n in range(start, start + count):
            rid = f"{prefix}{n}"
            if rid in taken:
                continue
            new_rows.append({"id": rid, "name": "", "props": {id_prop: n} if id_prop else {}})
        if new_rows:
            self._append_rows(res_type, new_rows)
        return len(new_rows)

    def _add_property(self):
        res_type = self._current
        if res_type is None:
            return
        name, ok = QInputDialog.getText(self, "增加属性", "属性名:")
        name = name.strip()
        if not ok or not name:
            return
        if name in self._columns[res_type]:
            QMessageBox.warning(self, "属性已存在", f"属性 {name} 已存在")
            return
        self._columns[res_type].append(name)
        self._fill_table()
        self._update_hints()
        self.changed.emit()

    def _delete_property(self):
        res_type = self._current
        c = self.table.currentColumn()
        if res_type is None or c < 2:
            return
        prop = self._columns[res_type][c - 2]
        if QMessageBox.question(self, "删除属性", f"删除所有 {res_type} 实例的属性 {prop}？",
                                QMessageBox.Yes | QMessageBox.No, QMessageBox.No) != QMessageBox.Yes:
            return
        for row in self._data[res_type]:
            row["props"].pop(prop, None)
        self._columns[res_type].remove(prop)
        self._fill_table()
        self._update_hints()
        self.changed.emit()

    # ------------------------------------------------------------- validation

    def _row_problems(self, res_type: str, rows: Rows) -> List[str]:
        lines = []
        ids = [row["id"].strip() for row in rows]
        for i, row in enumerate(rows):
            if not ids[i]:
                lines.append(f"{res_type}: 第 {i + 1} 行的 resource_id 为空")
            elif ids.count(ids[i]) > 1 and ids.index(ids[i]) == i:
                lines.append(f"{res_type}: resource_id '{ids[i]}' 重复")
        missing: Dict[str, List[str]] = {}
        for row in rows:
            for prop in self._rule_props(res_type):
                if row["props"].get(prop) is None:
                    missing.setdefault(prop, []).append(row["id"] or "?")
        for prop, rids in missing.items():
            shown = ", ".join(rids[:6]) + (" ..." if len(rids) > 6 else "")
            lines.append(f"{res_type}: {shown} 缺少 {prop}，硬件映射向导将拿不到 {prop}")
        return lines

    def _update_hints(self):
        self.hint_label.setText("\n".join(self.problems()[:12]))

    def _build(self, strict: bool) -> Dict[str, List[GenericResourceDef]]:
        result: Dict[str, List[GenericResourceDef]] = copy.deepcopy(self._kept_pin_resources)
        for res_type, rows in self._data.items():
            seen = set()
            instances = []
            for i, row in enumerate(rows):
                rid = row["id"].strip()
                if not rid or rid in seen:
                    if strict:
                        what = "为空" if not rid else f"'{rid}' 重复"
                        raise ValueError(f"外设 {res_type} 第 {i + 1} 行：resource_id {what}")
                    continue
                seen.add(rid)
                instances.append(GenericResourceDef(
                    resource_type=res_type, resource_id=rid,
                    display_name=row["name"].strip() or rid,
                    properties=copy.deepcopy(row["props"])))
            result[res_type] = instances
        return result
