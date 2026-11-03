"""Memory map workbench, tab "配置": the memory layout configuration (add-memory-layout-config).

Left: the scanned output sections with their status and target.  Right: the chip's physical
memories, their windows and the execution regions on them.  Sections are placed by dragging
them onto an execution region or with "+" / "−"; all three go through ``apply_placement``,
which calls ``LayoutSession.place`` / ``unplace``.  The rules are edited in ``RuleEditorDialog``.

Everything works on the ``LayoutSession`` of the window: changes are kept in memory, the
statuses follow at once, and "保存配置" writes ``memorymap.json``.  The diagnostics and layout
tabs describe the linker file on disk and do not follow the configuration until a linker file
is generated; the tab says so.
"""
import logging
from typing import Dict, List, Optional

from PySide6.QtCore import QItemSelection, QItemSelectionModel, QMimeData, Qt, Signal
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QDialog,
    QFormLayout,
    QGroupBox,
    QHBoxLayout,
    QHeaderView,
    QInputDialog,
    QLabel,
    QLineEdit,
    QListWidget,
    QMessageBox,
    QPushButton,
    QSplitter,
    QTableWidget,
    QTableWidgetItem,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...core.hardware.memory_regions import group_memories
from ...core.memmap import rules as rl
from ...core.memmap.check import CheckResult, SectionRow
from ...core.memmap.config import (
    KIND_LABELS,
    KINDS,
    STACK,
    USER,
    ConfigError,
    ExecRegion,
    Rule,
)
from ...core.memmap.factory import load_factory
from ...core.memmap.regions import NO_LONGER_NEEDED

logger = logging.getLogger(__name__)

ALL = "全部"
SECTION_KINDS = ("TEXT", "RODATA", "DATA", "BSS")
MIME = "application/x-memmap-sections"
DISK_NOTE = ("诊断、布局页签描述的是磁盘上的链接文件，生成链接文件之前不会随这里的配置变化；"
             "这里的状态说明配置生效后段会放到哪里。")
NO_RESULT_NOTE = "还没有扫描结果：先在上方开始扫描，段才会列在左边。"
ORPHAN_GROUP = "未落在芯片窗口上的区域"
NO_CORE = "no-core"
STATUS_COLORS = {rl.MANUAL: QColor("#1f5fbf"), rl.NOT_PLACED: QColor("#a65e00"),
                 rl.AGAIN: QColor("#b00020")}
ERROR_COLOR = "#b00020"
REGION, WINDOW = "region", "window"


def window_attributes(window) -> str:
    return "，".join((window.type, window.core_text(), "可缓存" if window.cacheable else "不可缓存"))


def match_text(match: dict) -> str:
    """A rule's conditions in Chinese."""
    parts = []
    if "name" in match:
        parts.append(f"名称 {match['name']}")
    if "kind" in match:
        kinds = match["kind"] if isinstance(match["kind"], (list, tuple)) else [match["kind"]]
        parts.append("种类 " + "/".join(kinds))
    if "core" in match:
        parts.append("无核" if match["core"] is None else f"核心 {match['core']}")
    if "cacheable" in match:
        parts.append("可缓存" if match["cacheable"] else "不可缓存")
    if "module" in match:
        parts.append(f"模块 {match['module']}")
    unknown = sorted(set(match) - {"name", "kind", "core", "cacheable", "module"})
    parts += [f"未知条件 {key}" for key in unknown]
    return "，".join(parts) or "（任意段）"


def _again(config) -> List[str]:
    return list(config.options.get(rl.AGAIN_KEY, []))


# --- drag and drop ---------------------------------------------------------------------

class SectionTable(QTableWidget):
    """The section table; dragging carries the output names of the selected rows."""

    def __init__(self, parent=None):
        super().__init__(0, 6, parent)
        self.setHorizontalHeaderLabels(["输出段", "种类", "核心", "模块", "状态", "目标"])
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.setSelectionMode(QAbstractItemView.ExtendedSelection)
        self.setDragEnabled(True)
        self.setDragDropMode(QAbstractItemView.DragOnly)
        header = self.horizontalHeader()
        header.setSectionResizeMode(QHeaderView.Interactive)
        for column, width in enumerate((300, 60, 50, 110, 80, 200)):
            self.setColumnWidth(column, width)

    def mimeTypes(self):
        return [MIME]

    def mimeData(self, items):
        names = []
        for item in items:
            row = self.item(item.row(), 0)
            name = row.data(Qt.UserRole).output if row is not None else None
            if name and name not in names:
                names.append(name)
        return section_mime(names)


def section_mime(names: List[str]) -> QMimeData:
    mime = QMimeData()
    mime.setData(MIME, "\n".join(names).encode("utf-8"))
    return mime


class RegionTree(QTreeWidget):
    """Memory → window → execution region; sections are dropped on an execution region."""

    def __init__(self, tab: "ConfigTab"):
        super().__init__()
        self.tab = tab
        self.setHeaderLabels(["存储 / 窗口 / 执行区域", "种类", "标记", "段数"])
        for column, width in enumerate((300, 90, 160, 50)):
            self.setColumnWidth(column, width)
        self.setAcceptDrops(True)
        self.viewport().setAcceptDrops(True)
        self.setDragDropMode(QAbstractItemView.DropOnly)
        self.setDropIndicatorShown(True)

    @staticmethod
    def region_of(item) -> Optional[str]:
        data = item.data(0, Qt.UserRole) if item is not None else None
        return data[1] if data and data[0] == REGION else None

    def _target(self, event) -> Optional[str]:
        if not event.mimeData().hasFormat(MIME):
            return None
        return self.region_of(self.itemAt(event.position().toPoint()))

    def dragEnterEvent(self, event):
        if event.mimeData().hasFormat(MIME):
            event.acceptProposedAction()
        else:
            event.ignore()

    def dragMoveEvent(self, event):
        if self._target(event):
            event.acceptProposedAction()
        else:
            event.ignore()

    def dropEvent(self, event):
        if self.tab.handle_drop(event.mimeData(), self.itemAt(event.position().toPoint())):
            event.acceptProposedAction()
        else:
            event.ignore()


# --- the tab ------------------------------------------------------------------------------

class ConfigTab(QWidget):
    """The configuration page of the memory map window."""

    config_changed = Signal()

    def __init__(self, parent=None):
        super().__init__(parent)
        self.session = None
        self.result: Optional[CheckResult] = None
        self.rule_editor: Optional["RuleEditorDialog"] = None
        self._placements: Dict[str, rl.Placement] = {}
        self._build()

    # --- layout ----------------------------------------------------------------------

    def _build(self):
        outer = QVBoxLayout(self)
        self.notes_label = QLabel("")
        self.notes_label.setWordWrap(True)
        outer.addWidget(self.notes_label)
        self.disk_note = QLabel(DISK_NOTE)
        self.disk_note.setWordWrap(True)
        self.disk_note.setStyleSheet("color: gray;")
        outer.addWidget(self.disk_note)

        row = QHBoxLayout()
        self.module_combo, self.core_combo = QComboBox(), QComboBox()
        self.kind_combo, self.status_combo = QComboBox(), QComboBox()
        self.kind_combo.addItem(ALL, None)
        for kind in SECTION_KINDS:
            self.kind_combo.addItem(kind, kind)
        self.status_combo.addItem(ALL, None)
        for status in (rl.BY_RULE, rl.MANUAL, rl.NOT_PLACED, rl.AGAIN):
            self.status_combo.addItem(rl.STATUS_LABELS[status], status)
        self._reset_filters()
        for label, combo in (("模块：", self.module_combo), ("核心：", self.core_combo),
                             ("种类：", self.kind_combo), ("状态：", self.status_combo)):
            row.addWidget(QLabel(label))
            row.addWidget(combo)
            combo.currentIndexChanged.connect(self._fill_table)
        row.addStretch()
        self.summary_label = QLabel("")
        row.addWidget(self.summary_label)
        outer.addLayout(row)

        splitter = QSplitter(Qt.Horizontal)
        self.table = SectionTable()
        splitter.addWidget(self.table)

        middle = QWidget()
        buttons = QVBoxLayout(middle)
        buttons.setContentsMargins(0, 0, 0, 0)
        buttons.addStretch()
        self.place_button = QPushButton("+")
        self.place_button.setToolTip("把选中的段放到右边选中的执行区域（手动放置）")
        self.place_button.clicked.connect(self.place_selected)
        self.unplace_button = QPushButton("−")
        self.unplace_button.setToolTip("移除选中段的手动放置，回到规则的结果")
        self.unplace_button.clicked.connect(self.unplace_selected)
        for button in (self.place_button, self.unplace_button):
            button.setFixedWidth(36)
            buttons.addWidget(button)
        buttons.addStretch()
        splitter.addWidget(middle)

        right = QWidget()
        right_layout = QVBoxLayout(right)
        right_layout.setContentsMargins(0, 0, 0, 0)
        self.tree = RegionTree(self)
        right_layout.addWidget(self.tree, 1)
        window_row = QHBoxLayout()
        window_row.addWidget(QLabel("窗口："))
        self.window_combo = QComboBox()
        window_row.addWidget(self.window_combo, 1)
        self.window_button = QPushButton("放到此窗口")
        self.window_button.setToolTip("把选中的执行区域放到这个窗口（也清除“待重新放置”）")
        self.window_button.clicked.connect(self._set_window_clicked)
        window_row.addWidget(self.window_button)
        right_layout.addLayout(window_row)
        region_row = QHBoxLayout()
        self.add_region_button = QPushButton("新增区域…")
        self.add_region_button.clicked.connect(self._add_region_clicked)
        self.rename_region_button = QPushButton("改名…")
        self.rename_region_button.clicked.connect(self._rename_region_clicked)
        self.remove_region_button = QPushButton("删除区域")
        self.remove_region_button.clicked.connect(self._remove_region_clicked)
        for button in (self.add_region_button, self.rename_region_button, self.remove_region_button):
            region_row.addWidget(button)
        region_row.addStretch()
        right_layout.addLayout(region_row)
        splitter.addWidget(right)
        splitter.setStretchFactor(0, 3)
        splitter.setStretchFactor(2, 2)
        outer.addWidget(splitter, 1)

        self.message_label = QLabel("")
        self.message_label.setWordWrap(True)
        outer.addWidget(self.message_label)
        self.message_list = QListWidget()
        self.message_list.setMaximumHeight(90)
        self.message_list.setVisible(False)
        outer.addWidget(self.message_list)

        row = QHBoxLayout()
        self.rules_button = QPushButton("规则…")
        self.rules_button.clicked.connect(self.open_rule_editor)
        row.addWidget(self.rules_button)
        row.addStretch()
        self.dirty_label = QLabel("")
        self.dirty_label.setStyleSheet("color: #a65e00;")
        row.addWidget(self.dirty_label)
        self.save_button = QPushButton("保存配置")
        self.save_button.clicked.connect(self.save)
        row.addWidget(self.save_button)
        outer.addLayout(row)
        self._update_buttons()

    def _reset_filters(self):
        for combo in (self.module_combo, self.core_combo):
            combo.blockSignals(True)
            combo.clear()
            combo.addItem(ALL, None)
            combo.blockSignals(False)

    # --- input -------------------------------------------------------------------------

    def set_session(self, session):
        self.session = session
        self.refresh()

    def set_result(self, result: Optional[CheckResult]):
        self.result = result
        self._reset_filters()
        if result is not None:
            for module in sorted({m for r in result.rows for m in r.modules}):
                self.module_combo.addItem(module, module)
            cores = {r.core for r in result.rows}
            if None in cores:
                self.core_combo.addItem("无核", NO_CORE)
            for core in sorted(c for c in cores if c is not None):
                self.core_combo.addItem(f"核心 {core}", core)
        self.window_combo.clear()
        for group in group_memories(result.regions if result else []):
            for window in group.windows:
                self.window_combo.addItem(f"{group.name} / {window.name}（{window_attributes(window)}）",
                                          (group.name, window.name))
        self.clear_messages()
        self.refresh()

    def rows(self) -> List[SectionRow]:
        return list(self.result.rows) if self.result is not None else []

    def factory(self):
        """The chip's factory data, or None."""
        if self.session is None:
            return None
        prepared = self.session.prepared
        if prepared is not None:
            return prepared.factory
        try:
            return load_factory(getattr(self.session.project, "selected_chip", None) or "")
        except ConfigError as e:
            logger.warning("Factory memory map data unreadable: %s", e)
            return None

    # --- refresh ------------------------------------------------------------------------

    def refresh(self):
        self._placements = self.session.placements(self.rows()) if self.session is not None else {}
        self._fill_notes()
        self._fill_table()
        self._fill_tree()
        self._update_buttons()

    def _fill_notes(self):
        notes = []
        if self.session is not None:
            if self.session.load_error:
                notes.append(f"内存布局配置无法读取，当前是空配置：{self.session.load_error}")
            if self.session.prepared is not None:
                notes += self.session.prepared.notes()
                clashed = self.session.prepared.required.clashed(self.session.config)
                if clashed:
                    notes.append("这些必需区域与你自己的区域重名：" + "、".join(clashed))
                if self.session.prepared.no_longer_needed:
                    notes.append("代码不再引用这些必需区域，它们保留在配置里，标为“不再需要”："
                                 + "、".join(self.session.prepared.no_longer_needed))
            again = _again(self.session.config)
            if again:
                notes.append("这些区域所在的窗口与当前芯片对不上，请重新选择窗口：" + "、".join(again))
        if self.result is None:
            notes.append(NO_RESULT_NOTE)
        self.notes_label.setText("\n".join(notes))

    def placement(self, section: str) -> Optional[rl.Placement]:
        return self._placements.get(section)

    def filtered_rows(self) -> List[SectionRow]:
        module, core = self.module_combo.currentData(), self.core_combo.currentData()
        kind, status = self.kind_combo.currentData(), self.status_combo.currentData()
        shown = []
        for row in sorted(self.rows(), key=lambda r: r.output):
            if module is not None and module not in row.modules:
                continue
            if core is not None and row.core != (None if core == NO_CORE else core):
                continue
            if kind is not None and row.kind != kind:
                continue
            placed = self._placements.get(row.output)
            if status is not None and (placed is None or placed.status != status):
                continue
            shown.append(row)
        return shown

    def _fill_table(self, *_):
        selected = set(self.selected_names())
        self.table.setRowCount(0)
        shown = self.filtered_rows()
        self.table.setRowCount(len(shown))
        for index, row in enumerate(shown):
            placed = self._placements.get(row.output)
            status = placed.status if placed is not None else rl.NOT_PLACED
            target = (placed.target or "") if placed is not None else ""
            if placed is not None and placed.rule:
                target_tip = f"规则：{placed.rule}"
            else:
                target_tip = ""
            texts = [row.output, row.kind, "" if row.core is None else str(row.core), "、".join(row.modules),
                     rl.STATUS_LABELS[status], target]
            for column, text in enumerate(texts):
                item = QTableWidgetItem(text)
                if column == 0:
                    item.setData(Qt.UserRole, row)
                if column == 4 and status in STATUS_COLORS:
                    item.setForeground(STATUS_COLORS[status])
                if column == 5 and target_tip:
                    item.setToolTip(target_tip)
                self.table.setItem(index, column, item)
        self.select_sections([n for n in (r.output for r in shown) if n in selected])
        counts = {s: 0 for s in rl.STATUS_LABELS}
        for placed in self._placements.values():
            counts[placed.status] += 1
        self.summary_label.setText(
            f"输出段 {len(shown)} / {len(self.rows())}；"
            + "，".join(f"{rl.STATUS_LABELS[s]} {counts[s]}" for s in (rl.BY_RULE, rl.MANUAL, rl.NOT_PLACED, rl.AGAIN)))

    def _region_item(self, region, again: set, counts: Dict[str, int], orphan_reason: str = "") -> QTreeWidgetItem:
        marks = []
        if region.required:
            marks.append("必需")
        if region.origin == NO_LONGER_NEEDED:
            marks.append("不再需要")
        if region.origin == USER:
            marks.append("自定义")
        if region.name in again:
            marks.append("待重新放置")
        if orphan_reason:
            marks.append(orphan_reason)
        item = QTreeWidgetItem([region.name, KIND_LABELS.get(region.kind, region.kind), "，".join(marks),
                                str(counts.get(region.name, 0))])
        item.setData(0, Qt.UserRole, (REGION, region.name))
        item.setToolTip(0, f"{region.name}：{KIND_LABELS.get(region.kind, region.kind)}，"
                           f"窗口 {region.window or '（未选）'}，对齐 {region.align}")
        if region.name in again or orphan_reason:
            item.setForeground(2, QColor(ERROR_COLOR))
        return item

    def _fill_tree(self):
        current = self.selected_region()
        self.tree.clear()
        if self.session is None:
            return
        config = self.session.config
        again = set(_again(config))
        counts: Dict[str, int] = {}
        for placed in self._placements.values():
            if placed.status in (rl.BY_RULE, rl.MANUAL) and placed.target:
                counts[placed.target] = counts.get(placed.target, 0) + 1
        by_window: Dict[str, list] = {}
        for region in config.regions:
            by_window.setdefault(region.window, []).append(region)
        placed_windows = set()
        for group in group_memories(self.result.regions if self.result else []):
            top = QTreeWidgetItem([group.name])
            top.setData(0, Qt.UserRole, ("memory", group.name))
            self.tree.addTopLevelItem(top)
            used = False
            for window in group.windows:
                regions = sorted(by_window.get(window.name, []), key=lambda r: (r.order, r.name))
                placed_windows.add(window.name)
                child = QTreeWidgetItem([f"{window.name}（{window_attributes(window)}）", "", "",
                                         str(sum(counts.get(r.name, 0) for r in regions))])
                child.setData(0, Qt.UserRole, (WINDOW, group.name, window.name))
                top.addChild(child)
                for region in regions:
                    child.addChild(self._region_item(region, again, counts))
                child.setExpanded(bool(regions))
                used = used or bool(regions)
            top.setExpanded(used)
        orphans = sorted((r for r in config.regions if r.window not in placed_windows), key=lambda r: r.name)
        if orphans:
            top = QTreeWidgetItem([f"{ORPHAN_GROUP}（{len(orphans)}）"])
            top.setData(0, Qt.UserRole, ("orphans", ""))
            self.tree.addTopLevelItem(top)
            for region in orphans:
                reason = f"窗口 {region.window} 不在芯片上" if region.window else "未选窗口"
                top.addChild(self._region_item(region, again, counts, reason))
            top.setExpanded(True)
        if current:
            self.select_region(current)

    def _update_buttons(self):
        has = self.session is not None
        for button in (self.place_button, self.unplace_button, self.window_button, self.add_region_button,
                       self.rename_region_button, self.remove_region_button, self.rules_button, self.save_button):
            button.setEnabled(has)
        self.dirty_label.setText("有未保存的改动" if has and self.session.dirty else "")

    # --- selection --------------------------------------------------------------------------

    def selected_rows(self) -> List[SectionRow]:
        found = []
        for index in sorted(self.table.selectionModel().selectedRows(), key=lambda i: i.row()):
            item = self.table.item(index.row(), 0)
            if item is not None:
                found.append(item.data(Qt.UserRole))
        return found

    def selected_names(self) -> List[str]:
        return [r.output for r in self.selected_rows()]

    def select_sections(self, names):
        names = set(names)
        self.table.clearSelection()
        model, selection = self.table.model(), self.table.selectionModel()
        chosen = QItemSelection()
        for index in range(self.table.rowCount()):
            item = self.table.item(index, 0)
            if item is not None and item.data(Qt.UserRole).output in names:
                chosen.select(model.index(index, 0), model.index(index, self.table.columnCount() - 1))
        selection.select(chosen, QItemSelectionModel.Select)

    def region_item(self, name: str) -> Optional[QTreeWidgetItem]:
        stack = [self.tree.topLevelItem(i) for i in range(self.tree.topLevelItemCount())]
        while stack:
            item = stack.pop()
            if RegionTree.region_of(item) == name:
                return item
            stack.extend(item.child(i) for i in range(item.childCount()))
        return None

    def select_region(self, name: str) -> bool:
        item = self.region_item(name)
        if item is not None:
            self.tree.setCurrentItem(item)
        return item is not None

    def selected_region(self) -> Optional[str]:
        return RegionTree.region_of(self.tree.currentItem())

    def selected_window(self):
        """(memory, window) of the selected window, or of the window of the selected region."""
        item = self.tree.currentItem()
        data = item.data(0, Qt.UserRole) if item is not None else None
        if data and data[0] == WINDOW:
            return data[1], data[2]
        if data and data[0] == REGION and item.parent() is not None:
            parent = item.parent().data(0, Qt.UserRole)
            if parent and parent[0] == WINDOW:
                return parent[1], parent[2]
        return None

    # --- messages ------------------------------------------------------------------------------

    def clear_messages(self):
        self.message_label.setText("")
        self.message_list.clear()
        self.message_list.setVisible(False)

    def show_messages(self, heading: str, lines=(), error: bool = True):
        self.message_label.setText(heading)
        self.message_label.setStyleSheet(f"color: {ERROR_COLOR};" if error else "color: #1e7e34;")
        self.message_list.clear()
        self.message_list.addItems(list(lines))
        self.message_list.setVisible(bool(lines))

    def messages(self) -> List[str]:
        return [self.message_list.item(i).text() for i in range(self.message_list.count())]

    # --- placing ---------------------------------------------------------------------------------

    def apply_placement(self, sections: List[str], region: Optional[str]) -> List[str]:
        """The one placing operation: drag, "+" and "−" all come here.

        ``region`` None removes the manual placements of ``sections``; otherwise they are placed
        by hand in ``region``.  Returns the refusals (shown to the user)."""
        if self.session is None or not sections:
            return []
        by_name = {r.output: r for r in self.rows()}
        refused = []
        if region is None:
            manual = [s for s in sections if s in self.session.config.manual]
            self.session.unplace(sections)
            self.refresh()
            if manual:
                self.show_messages(f"已移除 {len(manual)} 个段的手动放置，回到规则的结果", error=False)
            else:
                self.show_messages("选中的段没有手动放置")
        else:
            rows = [by_name[s] for s in sections if s in by_name]
            refused = self.session.place(rows, region)
            self.refresh()
            placed = len(rows) - len(refused)
            if refused:
                self.show_messages(f"放到 {region}：{placed} 个已放置，{len(refused)} 个被拒绝", refused)
            else:
                self.show_messages(f"已把 {placed} 个段手动放到 {region}", error=False)
        self.config_changed.emit()
        return refused

    def place_selected(self) -> List[str]:
        sections, region = self.selected_names(), self.selected_region()
        if not sections:
            self.show_messages("请先在左边选择段")
            return []
        if not region:
            self.show_messages("请先在右边选择一个执行区域")
            return []
        return self.apply_placement(sections, region)

    def unplace_selected(self):
        sections = self.selected_names()
        if not sections:
            self.show_messages("请先在左边选择段")
            return
        self.apply_placement(sections, None)

    def handle_drop(self, mime, item) -> bool:
        region = RegionTree.region_of(item)
        if not region or not mime.hasFormat(MIME):
            return False
        names = [n for n in bytes(mime.data(MIME)).decode("utf-8").split("\n") if n]
        self.apply_placement(names, region)
        return True

    # --- regions -------------------------------------------------------------------------------------

    def _done(self, message: str = "") -> str:
        if self.session is not None:
            self.session.changed()
        self.refresh()
        if message:
            self.show_messages(message, error=False)
        self.config_changed.emit()
        return ""

    def _error(self, message: str) -> str:
        self.show_messages(message)
        return message

    def add_region(self, name: str, kind: str, memory: Optional[str] = None,
                   window: Optional[str] = None) -> str:
        """Add a user region (on the selected window when none is given).  Returns the error, or ''."""
        if self.session is None:
            return self._error("没有打开内存布局配置")
        if window is None:
            memory, window = self.selected_window() or ("", "")
        config = self.session.config
        order = max((r.order for r in config.regions if r.window == window and window), default=0) + 1
        region = ExecRegion(name.strip(), memory or "", window or "", kind, order,
                            align=8 if kind == STACK else 64, origin=USER)
        try:
            config.add_region(region)
        except ConfigError as e:
            return self._error(str(e))
        self._done(f"已新增区域 {region.name}")
        self.select_region(region.name)
        return ""

    def remove_region(self, name: str) -> str:
        if self.session is None:
            return self._error("没有打开内存布局配置")
        try:
            self.session.config.remove_region(name)
        except ConfigError as e:
            return self._error(str(e))
        return self._done(f"已删除区域 {name}；放在它里面的段保留，显示为待重新放置")

    def rename_region(self, old: str, new: str) -> str:
        """Rename a user region; manual placements and rules naming it follow the new name."""
        if self.session is None:
            return self._error("没有打开内存布局配置")
        config = self.session.config
        new = new.strip()
        try:
            config.rename_region(old, new)
        except ConfigError as e:
            return self._error(str(e))
        if new != old:
            for section, target in list(config.manual.items()):
                if target == old:
                    config.manual[section] = new
            for rule in list(config.rules):
                if rule.target == old:
                    rl.change_rule(config, rule.name, target=new)
            again = _again(config)
            if old in again:
                config.options[rl.AGAIN_KEY] = sorted(new if n == old else n for n in again)
        return self._done(f"已把区域 {old} 改名为 {new}")

    def set_window(self, region: str, memory: str, window: str) -> str:
        if self.session is None:
            return self._error("没有打开内存布局配置")
        try:
            rl.set_window(self.session.config, region, memory, window)
        except ConfigError as e:
            return self._error(str(e))
        self._done(f"区域 {region} 已放到窗口 {window}")
        self.select_region(region)
        return ""

    def _set_window_clicked(self):
        region, data = self.selected_region(), self.window_combo.currentData()
        if not region:
            self.show_messages("请先在右边选择一个执行区域")
        elif not data:
            self.show_messages("没有可选的窗口（芯片没有内存区域数据，或还没有扫描）")
        else:
            self.set_window(region, *data)

    def _add_region_clicked(self):
        name, ok = QInputDialog.getText(self, "新增区域", "区域名称（字母、数字、下划线）：")
        if not ok or not name.strip():
            return
        labels = [f"{KIND_LABELS[k]}（{k}）" for k in KINDS]
        label, ok = QInputDialog.getItem(self, "新增区域", "种类：", labels, 2, False)
        if ok:
            self.add_region(name, KINDS[labels.index(label)])

    def _rename_region_clicked(self):
        region = self.selected_region()
        if not region:
            self.show_messages("请先在右边选择一个执行区域")
            return
        name, ok = QInputDialog.getText(self, "区域改名", "新名称：", text=region)
        if ok and name.strip():
            self.rename_region(region, name)

    def _remove_region_clicked(self):
        region = self.selected_region()
        if not region:
            self.show_messages("请先在右边选择一个执行区域")
            return
        self.remove_region(region)

    # --- rules and saving --------------------------------------------------------------------------

    def open_rule_editor(self) -> Optional["RuleEditorDialog"]:
        if self.session is None:
            return None
        if self.rule_editor is not None:
            self.rule_editor.close()
        self.rule_editor = RuleEditorDialog(self.session, self.rows(), self.factory(), self)
        self.rule_editor.rules_changed.connect(self._rules_changed)
        self.rule_editor.show()
        return self.rule_editor

    def _rules_changed(self):
        self.refresh()
        self.config_changed.emit()

    def save(self) -> bool:
        if self.session is None:
            return False
        try:
            path = self.session.save()
        except ConfigError as e:
            self.show_messages(f"保存失败：{e}")
            return False
        self.refresh()
        self.show_messages(f"已保存：{path}", error=False)
        return True


# --- the rule editor ----------------------------------------------------------------------------

class RuleEditorDialog(QDialog):
    """The project's rules in their order (the first matching rule wins)."""

    rules_changed = Signal()
    CORE_ANY = "any"
    KEEP = object()         # set_fields: leave this field as it is

    def __init__(self, session, rows: List[SectionRow], factory=None, parent=None):
        super().__init__(parent)
        self.session, self.rows, self.factory = session, list(rows), factory
        self.setWindowTitle("放置规则")
        self.resize(1000, 640)
        outer = QVBoxLayout(self)
        hint = QLabel("规则按顺序尝试，第一条匹配且目标能接收的规则生效；手动放置优先于所有规则。")
        hint.setWordWrap(True)
        outer.addWidget(hint)
        self.factory_label = QLabel("")
        self.factory_label.setWordWrap(True)
        self.factory_label.setStyleSheet("color: #a65e00;")
        outer.addWidget(self.factory_label)

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["#", "名称", "条件", "目标", "来源", "标注", "段数"])
        self.tree.setRootIsDecorated(False)
        for column, width in enumerate((36, 180, 260, 170, 50, 220, 40)):
            self.tree.setColumnWidth(column, width)
        self.tree.currentItemChanged.connect(self._selection_changed)
        outer.addWidget(self.tree, 1)

        row = QHBoxLayout()
        self.up_button = QPushButton("上移")
        self.up_button.clicked.connect(lambda: self.move_selected(-1))
        self.down_button = QPushButton("下移")
        self.down_button.clicked.connect(lambda: self.move_selected(1))
        self.remove_button = QPushButton("删除")
        self.remove_button.clicked.connect(self.remove_selected)
        self.restore_button = QPushButton("恢复出厂规则…")
        self.restore_button.clicked.connect(self.restore_factory)
        for button in (self.up_button, self.down_button, self.remove_button):
            row.addWidget(button)
        row.addStretch()
        row.addWidget(self.restore_button)
        outer.addLayout(row)

        box = QGroupBox("规则内容（条件缺省即不限，所有条件同时满足才匹配）")
        form = QFormLayout(box)
        self.name_edit = QLineEdit()
        form.addRow("名称：", self.name_edit)
        self.target_combo = QComboBox()
        self.target_combo.setEditable(True)
        form.addRow("目标区域：", self.target_combo)
        self.pattern_edit = QLineEdit()
        self.pattern_edit.setPlaceholderText("输出段名通配，如 *_core0（不分大小写）")
        form.addRow("段名：", self.pattern_edit)
        kinds = QHBoxLayout()
        self.kind_checks = {}
        for kind in SECTION_KINDS:
            check = QCheckBox(kind)
            self.kind_checks[kind] = check
            kinds.addWidget(check)
        kinds.addStretch()
        form.addRow("种类：", kinds)
        self.core_combo = QComboBox()
        self.core_combo.addItem("不限", self.CORE_ANY)
        self.core_combo.addItem("无核", None)
        for core in range(4):
            self.core_combo.addItem(f"核心 {core}", core)
        form.addRow("核心：", self.core_combo)
        self.cache_combo = QComboBox()
        self.cache_combo.addItem("不限", None)
        self.cache_combo.addItem("可缓存", True)
        self.cache_combo.addItem("不可缓存", False)
        form.addRow("缓存：", self.cache_combo)
        self.module_edit = QLineEdit()
        form.addRow("模块：", self.module_edit)
        self.note_edit = QLineEdit()
        form.addRow("说明：", self.note_edit)
        buttons = QHBoxLayout()
        self.apply_button = QPushButton("修改所选规则")
        self.apply_button.clicked.connect(self.apply_edit)
        self.add_button = QPushButton("添加为新规则")
        self.add_button.clicked.connect(self.add_from_fields)
        buttons.addWidget(self.apply_button)
        buttons.addWidget(self.add_button)
        buttons.addStretch()
        form.addRow(buttons)
        outer.addWidget(box)

        self.message_label = QLabel("")
        self.message_label.setWordWrap(True)
        outer.addWidget(self.message_label)
        row = QHBoxLayout()
        row.addStretch()
        close = QPushButton("关闭")
        close.clicked.connect(self.close)
        row.addWidget(close)
        outer.addLayout(row)
        self.refill()

    @property
    def config(self):
        return self.session.config

    # --- list -----------------------------------------------------------------------------

    def marks(self, rule: Rule, info: Optional[rl.RuleInfo]) -> List[str]:
        found = []
        if rule.changed:
            original = rule.original or {}
            found.append(f"已修改（原：{match_text(original.get('match', {}))} → {original.get('target', '')}）")
        if info is not None and info.invalid:
            found.append(f"无效：{info.invalid}")
        elif info is not None and info.shadowed:
            found.append("被遮蔽（匹配的段都被前面的规则放置了）")
        return found

    def refill(self):
        current = self.selected_rule()
        self.tree.clear()
        info = rl.rule_info(self.config, self.rows)
        for index, rule in enumerate(self.config.rules):
            entry = info.get(rule.name)
            marks = self.marks(rule, entry)
            item = QTreeWidgetItem([str(index + 1), rule.name, match_text(rule.match), rule.target,
                                    "出厂" if rule.origin == rl.FACTORY else "用户", "；".join(marks),
                                    str(entry.matched if entry else 0)])
            item.setData(0, Qt.UserRole, rule.name)
            item.setToolTip(1, rule.note or rule.name)
            item.setToolTip(5, "；".join(marks))
            if entry is not None and (entry.invalid or entry.shadowed):
                item.setForeground(5, QColor(ERROR_COLOR))
            self.tree.addTopLevelItem(item)
        self.target_combo.blockSignals(True)
        text = self.target_combo.currentText()
        self.target_combo.clear()
        self.target_combo.addItems(sorted(r.name for r in self.config.regions))
        self.target_combo.setCurrentText(text)
        self.target_combo.blockSignals(False)
        notes = []
        if self.factory is None:
            notes.append("这个芯片没有出厂规则")
        elif rl.factory_update_available(self.config, self.factory.version):
            notes.append("出厂规则有更新：工程里的规则没有被覆盖；需要时可以“恢复出厂规则”")
        self.factory_label.setText("\n".join(notes))
        self.factory_label.setVisible(bool(notes))
        self.restore_button.setEnabled(self.factory is not None)
        if current:
            self.select_rule(current)

    def rule_names(self) -> List[str]:
        return [r.name for r in self.config.rules]

    def item_of(self, name: str) -> Optional[QTreeWidgetItem]:
        for i in range(self.tree.topLevelItemCount()):
            if self.tree.topLevelItem(i).data(0, Qt.UserRole) == name:
                return self.tree.topLevelItem(i)
        return None

    def select_rule(self, name: str) -> bool:
        item = self.item_of(name)
        if item is not None:
            self.tree.setCurrentItem(item)
        return item is not None

    def selected_rule(self) -> Optional[str]:
        item = self.tree.currentItem()
        return item.data(0, Qt.UserRole) if item is not None else None

    def _selection_changed(self, *_):
        name = self.selected_rule()
        rule = next((r for r in self.config.rules if r.name == name), None)
        if rule is not None:
            self.load_fields(rule)

    # --- fields ---------------------------------------------------------------------------------

    def load_fields(self, rule: Rule):
        match = rule.match
        self.name_edit.setText(rule.name)
        self.target_combo.setCurrentText(rule.target)
        self.pattern_edit.setText(str(match.get("name", "")))
        kinds = match.get("kind", [])
        kinds = kinds if isinstance(kinds, (list, tuple)) else [kinds]
        for kind, check in self.kind_checks.items():
            check.setChecked(kind in kinds)
        self.core_combo.setCurrentIndex(self.core_combo.findData(match["core"]) if "core" in match else 0)
        self.cache_combo.setCurrentIndex(self.cache_combo.findData(match["cacheable"]) if "cacheable" in match else 0)
        self.module_edit.setText(str(match.get("module", "")))
        self.note_edit.setText(rule.note)

    def set_fields(self, name=None, target=None, pattern=None, kinds=None, core=KEEP,
                   cacheable=KEEP, module=None, note=None):
        """Fill the fields (used by the tests and by callers that build a rule)."""
        if name is not None:
            self.name_edit.setText(name)
        if target is not None:
            self.target_combo.setCurrentText(target)
        if pattern is not None:
            self.pattern_edit.setText(pattern)
        if kinds is not None:
            for kind, check in self.kind_checks.items():
                check.setChecked(kind in kinds)
        if core is not self.KEEP:
            self.core_combo.setCurrentIndex(self.core_combo.findData(core))
        if cacheable is not self.KEEP:
            self.cache_combo.setCurrentIndex(self.cache_combo.findData(cacheable))
        if module is not None:
            self.module_edit.setText(module)
        if note is not None:
            self.note_edit.setText(note)

    def match_from_fields(self) -> dict:
        match = {}
        pattern = self.pattern_edit.text().strip()
        if pattern:
            match["name"] = pattern
        kinds = [k for k, check in self.kind_checks.items() if check.isChecked()]
        if kinds:
            match["kind"] = kinds
        core = self.core_combo.currentData()
        if core != self.CORE_ANY:
            match["core"] = core
        cacheable = self.cache_combo.currentData()
        if cacheable is not None:
            match["cacheable"] = cacheable
        module = self.module_edit.text().strip()
        if module:
            match["module"] = module
        return match

    def _show(self, text: str, error: bool = True) -> str:
        self.message_label.setText(text)
        self.message_label.setStyleSheet(f"color: {ERROR_COLOR};" if error else "color: #1e7e34;")
        return text if error else ""

    def _changed(self, message: str, select: Optional[str] = None) -> str:
        self.session.changed()
        self.refill()
        if select:
            self.select_rule(select)
        self.rules_changed.emit()
        return self._show(message, error=False)

    # --- editing ----------------------------------------------------------------------------------

    def apply_edit(self) -> str:
        """Change the selected rule to the fields.  Returns the error, or ''."""
        name = self.selected_rule()
        if not name:
            return self._show("请先选择一条规则")
        target = self.target_combo.currentText().strip()
        if not target:
            return self._show("目标区域不能为空")
        new_name = self.name_edit.text().strip()
        if new_name and new_name != name:
            return self._show("规则名称不能修改（它用来对照出厂规则）；要换名称请添加为新规则")
        try:
            rl.change_rule(self.config, name, match=self.match_from_fields(), target=target,
                           note=self.note_edit.text().strip())
        except ConfigError as e:
            return self._show(str(e))
        return self._changed(f"已修改规则 {name}", name)

    def add_from_fields(self) -> str:
        """Add the fields as a new rule, at the end.  Returns the error, or ''."""
        name, target = self.name_edit.text().strip(), self.target_combo.currentText().strip()
        if not name or not target:
            return self._show("新规则需要名称和目标区域")
        try:
            rl.add_rule(self.config, Rule(name, self.match_from_fields(), target, note=self.note_edit.text().strip()))
        except ConfigError as e:
            return self._show(str(e))
        return self._changed(f"已添加规则 {name}（在最后，可以上移）", name)

    def move_selected(self, delta: int) -> str:
        name = self.selected_rule()
        if not name:
            return self._show("请先选择一条规则")
        position = self.rule_names().index(name) + delta
        if position < 0 or position >= len(self.config.rules):
            return ""
        rl.move_rule(self.config, name, position)
        return self._changed(f"已移动规则 {name}", name)

    def remove_selected(self) -> str:
        name = self.selected_rule()
        if not name:
            return self._show("请先选择一条规则")
        rl.remove_rule(self.config, name)
        return self._changed(f"已删除规则 {name}")

    # --- restoring the factory rules ----------------------------------------------------------------

    def restore_text(self, preview: rl.RestorePreview) -> str:
        lines = ["恢复出厂规则会把规则列表整体换回出厂的规则，手动放置不受影响。", ""]
        if preview.changed:
            lines.append("会丢失的修改：" + "、".join(preview.changed))
        if preview.added:
            lines.append("会删除的自己添加的规则：" + "、".join(preview.added))
        if preview.removed:
            lines.append("会恢复的已删除出厂规则：" + "、".join(preview.removed))
        lines += ["", "确定恢复吗？"]
        return "\n".join(lines)

    def _confirm(self, text: str) -> bool:
        return QMessageBox.question(self, "恢复出厂规则", text, QMessageBox.Yes | QMessageBox.No,
                                    QMessageBox.No) == QMessageBox.Yes

    def restore_factory(self) -> bool:
        """Show what would be lost, restore only after the user confirms."""
        if self.factory is None:
            self._show("这个芯片没有出厂规则")
            return False
        preview = rl.restore_preview(self.config, self.factory.rules)
        order_same = [r.name for r in self.config.rules] == [r.name for r in self.factory.rules]
        if not preview.any and order_same:
            self._show("规则与出厂规则一致，不需要恢复", error=False)
            return False
        text = self.restore_text(preview)
        if not preview.any:
            text = text.replace("\n\n确定", "\n规则的顺序与出厂不同。\n\n确定")
        if not self._confirm(text):
            self._show("已取消，规则没有变化", error=False)
            return False
        rl.restore_factory(self.config, self.factory.rules)
        self.config.options[rl.FACTORY_VERSION_KEY] = self.factory.version
        self._changed("已恢复出厂规则；手动放置没有变化")
        return True
