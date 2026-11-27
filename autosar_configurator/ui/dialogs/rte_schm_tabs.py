"""Tabs 2 & 3 of the RTE / SchM Configuration Workbench."""

from typing import Dict, List, Optional, Tuple

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QHBoxLayout,
    QHeaderView,
    QInputDialog,
    QLabel,
    QLineEdit,
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

from ...core.config_manager import PreLockedError
from ...generator.rte.workbench_service import (
    EA_MECHANISMS,
    ExclusiveAreaRow,
    RteWorkbenchService,
    TaskEventMappingRow,
)

_ALL_MODULES = "全部模块"
_ERROR_COLOR = QColor("#b00020")
_WARN_COLOR = QColor("#a65e00")
_OK_COLOR = QColor("#1b7f37")
_MUTED_COLOR = QColor("#666666")


def _centered_checkbox(checked: bool) -> Tuple[QWidget, QCheckBox]:
    container = QWidget()
    layout = QHBoxLayout(container)
    layout.setContentsMargins(0, 0, 0, 0)
    layout.setAlignment(Qt.AlignCenter)
    checkbox = QCheckBox()
    checkbox.setChecked(checked)
    layout.addWidget(checkbox)
    return container, checkbox


def _format_period(period_sec: Optional[float]) -> str:
    if period_sec is None:
        return "-"
    if period_sec == 0:
        return "0 s"
    if period_sec < 1.0:
        return f"{period_sec * 1000:g} ms"
    return f"{period_sec:g} s"


class ExclusiveAreasTab(QWidget):
    """Tab 2: Matrix editor for BSW SchM ExclusiveAreas."""

    config_changed = Signal()

    def __init__(self, service: RteWorkbenchService, parent=None) -> None:
        super().__init__(parent)
        self.service = service
        self._reloading = False
        self._rows: List[ExclusiveAreaRow] = []

        outer = QVBoxLayout(self)

        # Filter + action bar
        top = QHBoxLayout()
        top.addWidget(QLabel("模块："))
        self.module_filter = QComboBox()
        self.module_filter.addItem(_ALL_MODULES, None)
        self.module_filter.currentIndexChanged.connect(self._apply_filter_display)
        top.addWidget(self.module_filter)

        self.search_edit = QLineEdit()
        self.search_edit.setPlaceholderText("按 ExclusiveArea / 模块搜索...")
        self.search_edit.textChanged.connect(self._apply_filter_display)
        top.addWidget(self.search_edit, 1)

        self.only_issues_check = QCheckBox("仅看未配置/有错误")
        self.only_issues_check.stateChanged.connect(self._apply_filter_display)
        top.addWidget(self.only_issues_check)

        self.sync_btn = QPushButton("同步缺失临界区")
        self.sync_btn.clicked.connect(self._on_sync_missing)
        top.addWidget(self.sync_btn)
        outer.addLayout(top)

        batch_bar = QHBoxLayout()
        batch_bar.addWidget(QLabel("选中行批量设置保护机制："))
        self.batch_mech_combo = QComboBox()
        for mech in EA_MECHANISMS:
            self.batch_mech_combo.addItem(mech, mech)
        self.batch_mech_combo.currentIndexChanged.connect(self._sync_batch_target_combo)
        batch_bar.addWidget(self.batch_mech_combo)

        self.batch_target_combo = QComboBox()
        self.batch_target_combo.setMinimumWidth(160)
        batch_bar.addWidget(self.batch_target_combo)

        self.batch_apply_btn = QPushButton("应用到选中行")
        self.batch_apply_btn.clicked.connect(self._on_batch_apply)
        batch_bar.addWidget(self.batch_apply_btn)
        batch_bar.addStretch()
        self.summary_label = QLabel("")
        self.summary_label.setStyleSheet("color: gray;")
        batch_bar.addWidget(self.summary_label)
        outer.addLayout(batch_bar)

        self.table = QTableWidget(0, 8)
        self.table.setHorizontalHeaderLabels([
            "模块",
            "API 名称",
            "ExclusiveArea",
            "来源",
            "保护机制",
            "OsResource / OsSpinlock",
            "生成函数",
            "状态/校验",
        ])
        self.table.verticalHeader().setVisible(False)
        self.table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.table.setSelectionMode(QAbstractItemView.ExtendedSelection)
        self.table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        header = self.table.horizontalHeader()
        header.setSectionResizeMode(QHeaderView.Interactive)
        for col, width in enumerate((95, 145, 220, 95, 220, 175, 75, 190)):
            self.table.setColumnWidth(col, width)
        outer.addWidget(self.table, 1)

        self.reload()

    def reload(self) -> None:
        self._reloading = True
        try:
            self._rows = self.service.list_exclusive_area_rows()
            self._row_by_key: Dict[Tuple[str, str], ExclusiveAreaRow] = {
                (r.instance_name, r.ea_name): r for r in self._rows
            }
            os_resources = self.service.list_os_resources()
            os_spinlocks = self.service.list_os_spinlocks()
            self._os_resources = os_resources
            self._os_spinlocks = os_spinlocks

            prev_mod = self.module_filter.currentData()
            mods = sorted({r.module_name for r in self._rows})
            self.module_filter.clear()
            self.module_filter.addItem(_ALL_MODULES, None)
            for mod in mods:
                self.module_filter.addItem(mod, mod)
            if prev_mod in mods:
                self.module_filter.setCurrentIndex(self.module_filter.findData(prev_mod))

            self._sync_batch_target_combo()
            self._populate_table()
        finally:
            self._reloading = False

    def _sync_batch_target_combo(self) -> None:
        mech = self.batch_mech_combo.currentData() or self.batch_mech_combo.currentText()
        self.batch_target_combo.clear()
        if mech == "OS_RESOURCE":
            self.batch_target_combo.setEnabled(True)
            self.batch_target_combo.addItem("(请选择 OsResource)", "")
            for name in getattr(self, "_os_resources", []):
                self.batch_target_combo.addItem(name, name)
        elif mech == "OS_SPINLOCK":
            self.batch_target_combo.setEnabled(True)
            self.batch_target_combo.addItem("(请选择 OsSpinlock)", "")
            for name in getattr(self, "_os_spinlocks", []):
                self.batch_target_combo.addItem(name, name)
        else:
            self.batch_target_combo.setEnabled(False)
            self.batch_target_combo.addItem("-", "")

    def _apply_filter_display(self) -> None:
        if self._reloading:
            return
        self._reloading = True
        try:
            self._populate_table()
        finally:
            self._reloading = False

    def _filtered_rows(self) -> List[ExclusiveAreaRow]:
        mod_filter = self.module_filter.currentData()
        query = self.search_edit.text().strip().lower()
        only_issues = self.only_issues_check.isChecked()
        filtered: List[ExclusiveAreaRow] = []
        for row in self._rows:
            if mod_filter and row.module_name != mod_filter:
                continue
            if only_issues and row.configured and not row.validation_error:
                continue
            if query and query not in row.ea_name.lower() and query not in row.module_name.lower() and query not in row.api_name.lower():
                continue
            filtered.append(row)
        return filtered

    def _refresh_summary_label(self) -> None:
        err_count = sum(1 for r in self._rows if r.validation_error)
        unconf_count = sum(1 for r in self._rows if not r.configured)
        self.summary_label.setText(
            f"共 {len(self._rows)} 项 | 未同步 {unconf_count} | 错误 {err_count}"
        )

    @staticmethod
    def _apply_gen_checkbox_rule(gen_chk: QCheckBox, mechanism: str, generate_function: bool) -> None:
        if mechanism == "CUSTOM":
            gen_chk.setChecked(True)
            gen_chk.setEnabled(False)
            gen_chk.setToolTip("CUSTOM 机制始终生成函数声明")
        else:
            gen_chk.setEnabled(True)
            gen_chk.setToolTip("")
            gen_chk.setChecked(bool(generate_function))

    def _find_table_row_by_key(self, inst_name: str, ea_name: str) -> Optional[int]:
        for r in range(self.table.rowCount()):
            item = self.table.item(r, 0)
            if item is not None:
                data = item.data(Qt.UserRole)
                if data and (data[0], data[1]) == (inst_name, ea_name):
                    return r
        return None

    def _apply_row_visuals(
        self,
        r_idx: int,
        row: ExclusiveAreaRow,
        mech_combo: QComboBox,
        target_combo: QComboBox,
        gen_chk: QCheckBox,
        *,
        rebuild_target: bool = True,
    ) -> None:
        src_item = QTableWidgetItem("ECUC" if row.configured else "仅 IB (待同步)")
        if not row.configured:
            src_item.setForeground(_WARN_COLOR)
        self.table.setItem(r_idx, 3, src_item)

        if mech_combo.findData(row.mechanism) < 0:
            mech_combo.addItem(row.mechanism, row.mechanism)
        mech_combo.setCurrentIndex(mech_combo.findData(row.mechanism))

        if rebuild_target:
            self._configure_target_combo(target_combo, row.mechanism, row.os_resource, row.os_spinlock)

        self._apply_gen_checkbox_rule(gen_chk, row.mechanism, row.generate_function)

        if row.validation_error:
            st_item = QTableWidgetItem(row.validation_error)
            st_item.setForeground(_ERROR_COLOR)
        elif not row.configured:
            st_item = QTableWidgetItem("将按 IB 默认生成")
            st_item.setForeground(_WARN_COLOR)
        else:
            st_item = QTableWidgetItem("正常")
            st_item.setForeground(_OK_COLOR)
        self.table.setItem(r_idx, 7, st_item)

    def _populate_table(self) -> None:
        scroll_val = self.table.verticalScrollBar().value()
        filtered = self._filtered_rows()
        self.table.setRowCount(len(filtered))

        self._refresh_summary_label()

        for r_idx, row in enumerate(filtered):
            mod_item = QTableWidgetItem(row.module_name)
            mod_item.setData(Qt.UserRole, (row.instance_name, row.ea_name, row.ea_ref))
            self.table.setItem(r_idx, 0, mod_item)
            self.table.setItem(r_idx, 1, QTableWidgetItem(row.api_name))
            self.table.setItem(r_idx, 2, QTableWidgetItem(row.ea_name))

            mech_combo = QComboBox()
            for mech in EA_MECHANISMS:
                mech_combo.addItem(mech, mech)
            self.table.setCellWidget(r_idx, 4, mech_combo)

            target_combo = QComboBox()
            self.table.setCellWidget(r_idx, 5, target_combo)

            chk_wrapper, gen_chk = _centered_checkbox(row.generate_function)
            self.table.setCellWidget(r_idx, 6, chk_wrapper)

            self._apply_row_visuals(r_idx, row, mech_combo, target_combo, gen_chk, rebuild_target=True)

            inst_name = row.instance_name
            ea_name = row.ea_name
            ea_ref = row.ea_ref

            def _commit(_val=None, i=inst_name, e=ea_name, ref=ea_ref, mc=mech_combo, tc=target_combo, gc=gen_chk):
                if self._reloading:
                    return
                prev_row = getattr(self, "_row_by_key", {}).get((i, e))
                mech_val = mc.currentData() or mc.currentText()
                tgt_val = tc.currentData() or ""
                os_res = tgt_val if (mech_val == "OS_RESOURCE" and tgt_val) else None
                os_spin = tgt_val if (mech_val == "OS_SPINLOCK" and tgt_val) else None
                gen_fn_val = True if mech_val == "CUSTOM" else gc.isChecked()
                try:
                    self.service.update_exclusive_area(
                        i,
                        e,
                        mechanism=mech_val,
                        os_resource=os_res,
                        os_spinlock=os_spin,
                        generate_function=gen_fn_val,
                        ea_ref=ref,
                    )
                except PreLockedError as exc:
                    QMessageBox.warning(
                        self,
                        "受基线 Pre 锁保护",
                        f"无法修改临界区 '{e}'：\n{exc}\n\n请先在主界面属性面板中解锁对应 Pre 项。",
                    )
                    if prev_row is not None:
                        r_pos = self._find_table_row_by_key(i, e)
                        if r_pos is not None:
                            self._reloading = True
                            try:
                                self._apply_row_visuals(r_pos, prev_row, mc, tc, gc, rebuild_target=True)
                            finally:
                                self._reloading = False
                    return

                # Refresh backing row cache cleanly in-place without rebuilding whole table
                self._rows = self.service.list_exclusive_area_rows()
                self._row_by_key = {(r.instance_name, r.ea_name): r for r in self._rows}
                new_row = self._row_by_key.get((i, e))
                r_pos = self._find_table_row_by_key(i, e)
                if new_row is not None and r_pos is not None:
                    self._reloading = True
                    try:
                        same_target_domain = (
                            prev_row is not None
                            and (prev_row.mechanism in ("OS_RESOURCE", "OS_SPINLOCK") or new_row.mechanism in ("OS_RESOURCE", "OS_SPINLOCK"))
                            and prev_row.mechanism == new_row.mechanism
                        )
                        self._apply_row_visuals(
                            r_pos,
                            new_row,
                            mc,
                            tc,
                            gc,
                            rebuild_target=not same_target_domain,
                        )
                        self._refresh_summary_label()
                    finally:
                        self._reloading = False
                self.config_changed.emit()

            mech_combo.currentIndexChanged.connect(_commit)
            target_combo.currentIndexChanged.connect(_commit)
            gen_chk.stateChanged.connect(_commit)

        self.table.verticalScrollBar().setValue(scroll_val)

    def _configure_target_combo(
        self,
        combo: QComboBox,
        mechanism: str,
        os_resource: Optional[str],
        os_spinlock: Optional[str],
    ) -> None:
        combo.clear()
        if mechanism == "OS_RESOURCE":
            combo.setEnabled(True)
            combo.addItem("(请选择 OsResource)", "")
            names = list(getattr(self, "_os_resources", []))
            if os_resource and os_resource not in names:
                names.append(os_resource)
            for n in names:
                combo.addItem(n, n)
            idx = combo.findData(os_resource or "")
            combo.setCurrentIndex(max(0, idx))
        elif mechanism == "OS_SPINLOCK":
            combo.setEnabled(True)
            combo.addItem("(请选择 OsSpinlock)", "")
            names = list(getattr(self, "_os_spinlocks", []))
            if os_spinlock and os_spinlock not in names:
                names.append(os_spinlock)
            for n in names:
                combo.addItem(n, n)
            idx = combo.findData(os_spinlock or "")
            combo.setCurrentIndex(max(0, idx))
        else:
            combo.setEnabled(False)
            combo.addItem("-", "")

    def _on_sync_missing(self) -> None:
        count, locked = self.service._sync_missing_exclusive_areas_detailed()
        self.reload()
        if count > 0:
            self.config_changed.emit()
        if count:
            msg = f"已创建 {count} 条缺失的 RteBswExclusiveAreaImpl 配置。"
        elif locked:
            msg = "未创建新配置（部分项受基线 Pre 锁保护已跳过）。"
        else:
            msg = "所有 IB 临界区均已同步到 Rte ECUC。"
        if locked and count:
            msg += f"\n跳过受 Pre 锁保护的项：{len(locked)} 处。"
        QMessageBox.information(self, "同步临界区", msg)

    def _on_batch_apply(self) -> None:
        selected_rows = sorted({idx.row() for idx in self.table.selectedIndexes()})
        if not selected_rows:
            QMessageBox.information(self, "批量设置", "请先在表格中选择至少一行临界区。")
            return
        targets: List[Tuple[str, str]] = []
        for r_idx in selected_rows:
            item = self.table.item(r_idx, 0)
            if item is None:
                continue
            inst_name, ea_name, _ = item.data(Qt.UserRole)
            targets.append((inst_name, ea_name))
        if not targets:
            return
        mech = self.batch_mech_combo.currentData() or self.batch_mech_combo.currentText()
        tgt = self.batch_target_combo.currentData() or None
        updated = self.service.batch_set_mechanism(
            targets,
            mech,
            os_resource=tgt if mech == "OS_RESOURCE" else None,
            os_spinlock=tgt if mech == "OS_SPINLOCK" else None,
        )
        self.reload()
        if updated > 0:
            self.config_changed.emit()
        if updated < len(targets):
            QMessageBox.warning(
                self,
                "部分项受 Pre 锁保护",
                f"已更新 {updated}/{len(targets)} 项；其余项受基线 Pre 锁保护未修改。",
            )


class TaskMappingTab(QWidget):
    """Tab 3: BSW Event-to-Task mapping & in-task ordering (with read-only SWC context)."""

    config_changed = Signal()

    def __init__(self, service: RteWorkbenchService, parent=None) -> None:
        super().__init__(parent)
        self.service = service
        self._reloading = False
        self._mapped_by_task: Dict[str, List[TaskEventMappingRow]] = {}
        self._unmapped: List[TaskEventMappingRow] = []

        outer = QVBoxLayout(self)

        top = QHBoxLayout()
        self.filter_edit = QLineEdit()
        self.filter_edit.setPlaceholderText("过滤 Task / 模块 / 事件 / MainFunction...")
        self.filter_edit.textChanged.connect(self._apply_filter_display)
        top.addWidget(self.filter_edit, 1)

        self.include_swc_check = QCheckBox("显示 SWC 映射（只读上下文）")
        self.include_swc_check.setChecked(True)
        self.include_swc_check.stateChanged.connect(lambda: self.reload())
        top.addWidget(self.include_swc_check)

        self.summary_label = QLabel("")
        self.summary_label.setStyleSheet("color: gray;")
        top.addWidget(self.summary_label)
        outer.addLayout(top)

        splitter = QSplitter(Qt.Horizontal)

        # Left pane: OsTask tree
        left = QWidget()
        left_layout = QVBoxLayout(left)
        left_layout.setContentsMargins(0, 0, 0, 0)
        left_layout.addWidget(QLabel("已映射调度顺序（按 OsTask 分组）"))

        self.mapped_tree = QTreeWidget()
        self.mapped_tree.setHeaderLabels([
            "Task / 事件",
            "模块",
            "实体 / MainFunction",
            "序号",
            "周期",
            "来源",
        ])
        self.mapped_tree.setColumnWidth(0, 235)
        self.mapped_tree.setColumnWidth(1, 90)
        self.mapped_tree.setColumnWidth(2, 185)
        self.mapped_tree.setColumnWidth(3, 55)
        self.mapped_tree.setColumnWidth(4, 70)
        self.mapped_tree.setColumnWidth(5, 85)
        self.mapped_tree.currentItemChanged.connect(self._on_tree_selection_changed)
        left_layout.addWidget(self.mapped_tree, 1)

        left_btns = QHBoxLayout()
        self.move_up_btn = QPushButton("上移")
        self.move_up_btn.clicked.connect(lambda: self._on_move(-1))
        self.move_down_btn = QPushButton("下移")
        self.move_down_btn.clicked.connect(lambda: self._on_move(1))
        self.set_pos_btn = QPushButton("修改序号...")
        self.set_pos_btn.clicked.connect(self._on_set_position)
        self.unmap_btn = QPushButton("取消映射")
        self.unmap_btn.clicked.connect(self._on_unmap)
        for btn in (self.move_up_btn, self.move_down_btn, self.set_pos_btn, self.unmap_btn):
            btn.setEnabled(False)
            left_btns.addWidget(btn)
        left_btns.addStretch()
        left_layout.addLayout(left_btns)
        splitter.addWidget(left)

        # Right pane: Unmapped BSW events
        right = QWidget()
        right_layout = QVBoxLayout(right)
        right_layout.setContentsMargins(0, 0, 0, 0)
        right_layout.addWidget(QLabel("未映射 BSW 调度事件"))

        self.unmapped_table = QTableWidget(0, 5)
        self.unmapped_table.setHorizontalHeaderLabels([
            "模块",
            "事件",
            "实体 / MainFunction",
            "周期",
            "来源",
        ])
        self.unmapped_table.verticalHeader().setVisible(False)
        self.unmapped_table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.unmapped_table.setSelectionMode(QAbstractItemView.SingleSelection)
        self.unmapped_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        u_header = self.unmapped_table.horizontalHeader()
        u_header.setSectionResizeMode(QHeaderView.Interactive)
        for col, width in enumerate((90, 190, 190, 65, 110)):
            self.unmapped_table.setColumnWidth(col, width)
        self.unmapped_table.itemSelectionChanged.connect(self._update_map_button_state)
        self.unmapped_table.doubleClicked.connect(self._on_map_selected)
        right_layout.addWidget(self.unmapped_table, 1)

        assign_bar = QHBoxLayout()
        assign_bar.addWidget(QLabel("目标 OsTask："))
        self.target_task_combo = QComboBox()
        self.target_task_combo.currentIndexChanged.connect(self._update_map_button_state)
        assign_bar.addWidget(self.target_task_combo, 1)
        self.map_btn = QPushButton("映射到选中 Task")
        self.map_btn.setEnabled(False)
        self.map_btn.clicked.connect(self._on_map_selected)
        assign_bar.addWidget(self.map_btn)
        right_layout.addLayout(assign_bar)

        splitter.addWidget(right)
        splitter.setSizes([660, 480])
        outer.addWidget(splitter, 1)

        self.reload()

    def reload(self) -> None:
        self._reloading = True
        try:
            include_swc = self.include_swc_check.isChecked()
            self._tasks = self.service.list_os_tasks()
            self._mapped_by_task, self._unmapped = self.service.list_task_mappings(
                include_swc=include_swc
            )

            prev_task = self.target_task_combo.currentData()
            self.target_task_combo.clear()
            for t in self._tasks:
                label = f"{t.name} (prio={t.priority})" if t.priority is not None else t.name
                if t.missing_in_os:
                    label = f"{t.name} [Os中未定义]"
                self.target_task_combo.addItem(label, t.name)
            if prev_task:
                idx = self.target_task_combo.findData(prev_task)
                if idx >= 0:
                    self.target_task_combo.setCurrentIndex(idx)

            self._populate_views()
        finally:
            self._reloading = False
        self._update_tree_buttons()
        self._update_map_button_state()

    def _apply_filter_display(self) -> None:
        if self._reloading:
            return
        self._reloading = True
        try:
            self._populate_views()
        finally:
            self._reloading = False
        self._update_tree_buttons()
        self._update_map_button_state()

    def _populate_views(self) -> None:
        query = self.filter_edit.text().strip().lower()
        selected_key = self._selected_mapping_key()

        self.mapped_tree.clear()
        total_mapped = 0
        item_to_select: Optional[QTreeWidgetItem] = None
        for task_info in self._tasks:
            task_rows = self._mapped_by_task.get(task_info.name, [])
            total_mapped += len(task_rows)
            task_matches = not query or query in task_info.name.lower()
            matching_children = [
                r
                for r in task_rows
                if task_matches
                or query in r.event_name.lower()
                or query in r.module_name.lower()
                or (r.entity_name and query in r.entity_name.lower())
            ]
            if query and not matching_children and not task_matches:
                continue

            desc_parts = []
            if task_info.priority is not None:
                desc_parts.append(f"prio={task_info.priority}")
            if task_info.task_type:
                desc_parts.append(task_info.task_type)
            if task_info.missing_in_os:
                desc_parts.append("Os未定义")
            desc_parts.append(f"{len(task_rows)} 项")

            parent_item = QTreeWidgetItem([
                task_info.name,
                "",
                ", ".join(desc_parts),
                "",
                "",
                "",
            ])
            parent_item.setData(0, Qt.UserRole, ("task", task_info.name))
            if task_info.missing_in_os:
                parent_item.setForeground(0, _WARN_COLOR)

            for r in matching_children if query else task_rows:
                child = QTreeWidgetItem([
                    r.event_name,
                    r.module_name,
                    r.entity_name or "-",
                    "-" if r.position is None else str(r.position),
                    _format_period(r.period_sec),
                    "SWC (只读)" if r.is_swc else "BSW",
                ])
                child.setData(0, Qt.UserRole, ("mapping", r))
                if r.is_swc:
                    for col in range(6):
                        child.setForeground(col, _MUTED_COLOR)
                parent_item.addChild(child)
                if selected_key is not None and (not r.is_swc) and (r.instance_name, r.mapping_name) == selected_key:
                    item_to_select = child

            self.mapped_tree.addTopLevelItem(parent_item)
            if matching_children or task_rows:
                parent_item.setExpanded(True)

        if item_to_select is not None:
            self.mapped_tree.setCurrentItem(item_to_select)

        # Unmapped BSW table
        filtered_unmapped = [
            r
            for r in self._unmapped
            if not query
            or query in r.module_name.lower()
            or query in r.event_name.lower()
            or (r.entity_name and query in r.entity_name.lower())
        ]
        self.unmapped_table.setRowCount(len(filtered_unmapped))
        for r_idx, row in enumerate(filtered_unmapped):
            mod_item = QTableWidgetItem(row.module_name)
            mod_item.setData(Qt.UserRole, row)
            self.unmapped_table.setItem(r_idx, 0, mod_item)
            self.unmapped_table.setItem(r_idx, 1, QTableWidgetItem(row.event_name))
            self.unmapped_table.setItem(r_idx, 2, QTableWidgetItem(row.entity_name or "-"))
            self.unmapped_table.setItem(r_idx, 3, QTableWidgetItem(_format_period(row.period_sec)))
            src_item = QTableWidgetItem("ECUC (未映射)" if row.has_ecuc_container else "仅 IB")
            if not row.has_ecuc_container:
                src_item.setForeground(_WARN_COLOR)
            self.unmapped_table.setItem(r_idx, 4, src_item)

        self.summary_label.setText(
            f"OsTask {len(self._tasks)} 个 | 已映射事件 {total_mapped} | 未映射 BSW 事件 {len(self._unmapped)}"
        )

    def _selected_mapping_key(self) -> Optional[Tuple[str, str]]:
        item = self.mapped_tree.currentItem()
        if item is None:
            return None
        payload = item.data(0, Qt.UserRole)
        if not payload or payload[0] != "mapping":
            return None
        row: TaskEventMappingRow = payload[1]
        if row.is_swc:
            return None
        return (row.instance_name, row.mapping_name)

    def _selected_bsw_mapping(self) -> Optional[TaskEventMappingRow]:
        item = self.mapped_tree.currentItem()
        if item is None:
            return None
        payload = item.data(0, Qt.UserRole)
        if not payload or payload[0] != "mapping":
            return None
        row: TaskEventMappingRow = payload[1]
        return None if row.is_swc else row

    def _on_tree_selection_changed(self, current: Optional[QTreeWidgetItem], _prev) -> None:
        if current is not None:
            payload = current.data(0, Qt.UserRole)
            target_task: Optional[str] = None
            if payload and payload[0] == "task":
                target_task = payload[1]
            elif payload and payload[0] == "mapping":
                target_task = payload[1].task_name
            if target_task:
                idx = self.target_task_combo.findData(target_task)
                if idx >= 0:
                    self.target_task_combo.setCurrentIndex(idx)
        self._update_tree_buttons()

    def _update_tree_buttons(self) -> None:
        row = self._selected_bsw_mapping()
        is_bsw = row is not None
        self.move_up_btn.setEnabled(is_bsw)
        self.move_down_btn.setEnabled(is_bsw)
        self.set_pos_btn.setEnabled(is_bsw)
        self.unmap_btn.setEnabled(is_bsw)

    def _update_map_button_state(self) -> None:
        has_unmapped = self.unmapped_table.currentRow() >= 0
        has_task = bool(self.target_task_combo.currentData())
        self.map_btn.setEnabled(has_unmapped and has_task)

    def _on_map_selected(self) -> None:
        row_idx = self.unmapped_table.currentRow()
        task_name = self.target_task_combo.currentData()
        if row_idx < 0 or not task_name:
            return
        item = self.unmapped_table.item(row_idx, 0)
        if item is None:
            return
        ev_row: TaskEventMappingRow = item.data(Qt.UserRole)
        try:
            self.service.map_event_to_task(
                ev_row.instance_name,
                ev_row.event_name,
                task_name,
                event_ref=ev_row.event_ref,
                event_kind=ev_row.event_kind,
            )
        except PreLockedError as exc:
            QMessageBox.warning(self, "受基线 Pre 锁保护", f"无法映射到 Task：\n{exc}")
            self.reload()
            return
        self.reload()
        self.config_changed.emit()

    def _on_move(self, delta: int) -> None:
        row = self._selected_bsw_mapping()
        if row is None or not row.task_name:
            return
        try:
            moved = self.service.move_event_in_task(
                row.task_name, row.instance_name, row.mapping_name, delta
            )
        except PreLockedError as exc:
            QMessageBox.warning(self, "受基线 Pre 锁保护", f"无法调整调度顺序：\n{exc}")
            self.reload()
            return
        if moved:
            self.reload()
            self.config_changed.emit()

    def _on_set_position(self) -> None:
        row = self._selected_bsw_mapping()
        if row is None:
            return
        cur_pos = row.position if row.position is not None else 0
        new_pos, ok = QInputDialog.getInt(
            self,
            "设置调度序号",
            f"为 {row.module_name}.{row.event_name} 设置 RteBswPositionInTask：",
            cur_pos,
            0,
            99999,
        )
        if not ok:
            return
        try:
            changed = self.service.set_event_position(row.instance_name, row.mapping_name, new_pos)
        except PreLockedError as exc:
            QMessageBox.warning(self, "受基线 Pre 锁保护", f"无法修改调度序号：\n{exc}")
            self.reload()
            return
        if changed:
            self.reload()
            self.config_changed.emit()

    def _on_unmap(self) -> None:
        row = self._selected_bsw_mapping()
        if row is None:
            return
        try:
            changed = self.service.unmap_event(row.instance_name, row.mapping_name)
        except PreLockedError as exc:
            QMessageBox.warning(self, "受基线 Pre 锁保护", f"无法取消映射：\n{exc}")
            self.reload()
            return
        if changed:
            self.reload()
            self.config_changed.emit()
