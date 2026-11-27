"""Five tab widgets for the System Services & Diagnostics Workbench."""

from typing import Dict, List, Optional

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QBrush, QColor, QFont
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QDialog,
    QDialogButtonBox,
    QDoubleSpinBox,
    QFormLayout,
    QGridLayout,
    QGroupBox,
    QHBoxLayout,
    QHeaderView,
    QLabel,
    QLineEdit,
    QMessageBox,
    QPushButton,
    QSpinBox,
    QSplitter,
    QTableWidget,
    QTableWidgetItem,
    QTabWidget,
    QVBoxLayout,
    QWidget,
)

from ...core.config_manager import PreLockedError
from ...core.services import (
    ECUM_INIT_LIST_NAMES,
    UDS_SID_NAMES,
    BswMActionListItemRow,
    BswMModePortRow,
    BswMRuleRow,
    CddPlatformModuleRow,
    DcmServiceRow,
    DcmSessionRow,
    DiagChannelRow,
    EcuMInitItemRow,
    EcuMWakeupSourceRow,
    ModuleDetFlagRow,
    OsIsrRow,
    OsTaskRow,
    OsTimingRow,
    SystemServicesWorkbenchService,
)

_OK_COLOR = QColor("#1b7f37")
_WARN_COLOR = QColor("#a65e00")
_ERROR_COLOR = QColor("#b00020")
_MUTED_COLOR = QColor("#57606a")


def _ro_item(text: str, *, color: Optional[QColor] = None, bold: bool = False) -> QTableWidgetItem:
    item = QTableWidgetItem(text)
    item.setFlags(item.flags() & ~Qt.ItemIsEditable)
    if color is not None:
        item.setForeground(QBrush(color))
    if bold:
        f = QFont()
        f.setBold(True)
        item.setFont(f)
    return item


def _configure_table(table: QTableWidget) -> None:
    table.setSelectionBehavior(QAbstractItemView.SelectRows)
    table.setSelectionMode(QAbstractItemView.SingleSelection)
    table.setAlternatingRowColors(True)
    table.verticalHeader().setVisible(False)
    table.horizontalHeader().setStretchLastSection(True)


# ----------------------------------------------------------------------
# Tab 1: EcuM Startup & Shutdown
# ----------------------------------------------------------------------


class EcuMTab(QWidget):
    """Manage EcuM general settings, ordered DriverInit lists, wakeup sources, and causes."""

    config_changed = Signal()
    navigate_requested = Signal(str)

    def __init__(self, service: SystemServicesWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._init_rows: List[EcuMInitItemRow] = []
        self._ws_rows: List[EcuMWakeupSourceRow] = []

        root = QVBoxLayout(self)

        # General settings bar
        gen_box = QGroupBox("EcuM 全局启动/关闭参数")
        gl = QHBoxLayout(gen_box)
        self.period_spin = QDoubleSpinBox()
        self.period_spin.setDecimals(4)
        self.period_spin.setRange(0.0001, 10.0)
        self.period_spin.setSingleStep(0.005)
        self.period_spin.setSuffix(" s")

        self.dev_det_check = QCheckBox("EcuMDevErrorDetect")
        self.slave_core_check = QCheckBox("多核处理 (SlaveCoreHandling)")
        self.shutdown_combo = QComboBox()
        self.shutdown_combo.setEditable(True)
        self.shutdown_combo.addItems(["EcuMStateOff", "EcuMStateReset", "EcuMStateSleep"])

        self.btn_apply_gen = QPushButton("应用全局参数")
        self.btn_apply_gen.clicked.connect(self._on_apply_general)
        self.meta_label = QLabel("")
        self.meta_label.setStyleSheet("color: #57606a;")

        gl.addWidget(QLabel("主函数周期:"))
        gl.addWidget(self.period_spin)
        gl.addWidget(self.dev_det_check)
        gl.addWidget(self.slave_core_check)
        gl.addWidget(QLabel("默认关闭状态:"))
        gl.addWidget(self.shutdown_combo)
        gl.addWidget(self.btn_apply_gen)
        gl.addWidget(self.meta_label, 1)
        root.addWidget(gen_box)

        splitter = QSplitter(Qt.Vertical)

        # Top: Init lists
        init_box = QGroupBox("驱动初始化列表 (EcuMDriverInitListZero..Three)")
        il = QVBoxLayout(init_box)
        bar = QHBoxLayout()
        bar.addWidget(QLabel("列表过滤:"))
        self.init_list_combo = QComboBox()
        self.init_list_combo.addItem("全部列表", "")
        for ln in ECUM_INIT_LIST_NAMES:
            self.init_list_combo.addItem(ln, ln)
        self.init_list_combo.currentIndexChanged.connect(self._populate_init_table)
        bar.addWidget(self.init_list_combo)

        self.btn_move_up = QPushButton("上移 ↑")
        self.btn_move_down = QPushButton("下移 ↓")
        self.btn_add_init = QPushButton("新增初始化项...")
        self.btn_del_init = QPushButton("删除选中")
        self.btn_locate_init = QPushButton("定位")

        self.btn_move_up.clicked.connect(lambda: self._on_move_init(-1))
        self.btn_move_down.clicked.connect(lambda: self._on_move_init(1))
        self.btn_add_init.clicked.connect(self._on_add_init)
        self.btn_del_init.clicked.connect(self._on_del_init)
        self.btn_locate_init.clicked.connect(self._on_locate_init)

        bar.addStretch()
        bar.addWidget(self.btn_move_up)
        bar.addWidget(self.btn_move_down)
        bar.addWidget(self.btn_add_init)
        bar.addWidget(self.btn_del_init)
        bar.addWidget(self.btn_locate_init)
        il.addLayout(bar)

        self.init_table = QTableWidget(0, 7)
        self.init_table.setHorizontalHeaderLabels([
            "列表",
            "顺序",
            "条目名称",
            "ModuleID",
            "初始化函数 / 附加代码",
            "头文件",
            "模块状态",
        ])
        _configure_table(self.init_table)
        self.init_table.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.init_table.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeToContents)
        self.init_table.itemSelectionChanged.connect(self._update_init_buttons)
        il.addWidget(self.init_table)
        splitter.addWidget(init_box)

        # Bottom: Wakeup Sources & Reset/Shutdown Causes
        bottom_split = QSplitter(Qt.Horizontal)

        ws_box = QGroupBox("唤醒源 (EcuMWakeupSource)")
        wl = QVBoxLayout(ws_box)
        self.ws_table = QTableWidget(0, 6)
        self.ws_table.setHorizontalHeaderLabels([
            "名称",
            "ID",
            "轮询",
            "校验超时(s)",
            "检查超时(s)",
            "关联 ComM 通道",
        ])
        _configure_table(self.ws_table)
        wl.addWidget(self.ws_table)
        ws_edit = QHBoxLayout()
        self.ws_poll_check = QCheckBox("Polling")
        self.ws_val_spin = QDoubleSpinBox()
        self.ws_val_spin.setRange(0.0, 60.0)
        self.ws_val_spin.setDecimals(3)
        self.ws_apply_btn = QPushButton("更新选中唤醒源")
        self.ws_apply_btn.clicked.connect(self._on_apply_ws)
        ws_edit.addWidget(self.ws_poll_check)
        ws_edit.addWidget(QLabel("Validation(s):"))
        ws_edit.addWidget(self.ws_val_spin)
        ws_edit.addWidget(self.ws_apply_btn)
        ws_edit.addStretch()
        wl.addLayout(ws_edit)
        self.ws_table.itemSelectionChanged.connect(self._on_ws_sel)
        bottom_split.addWidget(ws_box)

        cause_box = QGroupBox("复位模式与关闭原因 (ResetMode / ShutdownCause)")
        cl = QVBoxLayout(cause_box)
        self.cause_table = QTableWidget(0, 3)
        self.cause_table.setHorizontalHeaderLabels(["类型", "名称", "ID"])
        _configure_table(self.cause_table)
        cl.addWidget(self.cause_table)
        bottom_split.addWidget(cause_box)

        splitter.addWidget(bottom_split)
        splitter.setSizes([380, 220])
        root.addWidget(splitter, 1)

        self.reload()

    def reload(self) -> None:
        info = self.service.get_ecum_summary()
        for w in (self.period_spin, self.dev_det_check, self.slave_core_check, self.shutdown_combo):
            w.blockSignals(True)
        self.period_spin.setEnabled(info.loaded)
        self.dev_det_check.setEnabled(info.loaded)
        self.slave_core_check.setEnabled(info.loaded)
        self.shutdown_combo.setEnabled(info.loaded)
        self.btn_apply_gen.setEnabled(info.loaded)
        if info.main_function_period is not None:
            self.period_spin.setValue(info.main_function_period)
        self.dev_det_check.setChecked(info.dev_error_detect)
        self.slave_core_check.setChecked(info.slave_core_handling)
        if info.default_shutdown_state:
            self.shutdown_combo.setCurrentText(info.default_shutdown_state)
        parts = ", ".join(info.partition_refs) if info.partition_refs else "-"
        self.meta_label.setText(f"分区: {parts}" if info.loaded else "未加载 EcuM")
        for w in (self.period_spin, self.dev_det_check, self.slave_core_check, self.shutdown_combo):
            w.blockSignals(False)

        self._init_rows = self.service.list_ecum_init_items()
        self._populate_init_table()

        self._ws_rows = self.service.list_ecum_wakeup_sources()
        self.ws_table.setRowCount(len(self._ws_rows))
        for i, r in enumerate(self._ws_rows):
            ch_txt = r.comm_channel_name or "-"
            if r.has_broken_ref:
                ch_txt = f"❌ {ch_txt} (引用失效)"
            items = [
                _ro_item(r.short_name, bold=True),
                _ro_item("-" if r.wakeup_id is None else str(r.wakeup_id)),
                _ro_item("Yes" if r.polling else "No"),
                _ro_item("-" if r.validation_timeout is None else f"{r.validation_timeout:g}"),
                _ro_item("-" if r.check_wakeup_timeout is None else f"{r.check_wakeup_timeout:g}"),
                _ro_item(ch_txt, color=_ERROR_COLOR if r.has_broken_ref else None),
            ]
            for j, it in enumerate(items):
                self.ws_table.setItem(i, j, it)

        causes = self.service.list_ecum_reset_and_causes()
        self.cause_table.setRowCount(len(causes))
        for i, c in enumerate(causes):
            self.cause_table.setItem(i, 0, _ro_item(c.kind))
            self.cause_table.setItem(i, 1, _ro_item(c.short_name, bold=True))
            self.cause_table.setItem(i, 2, _ro_item("-" if c.mode_or_cause_id is None else str(c.mode_or_cause_id)))
        self._on_ws_sel()

    def _populate_init_table(self) -> None:
        flt = self.init_list_combo.currentData() or ""
        rows = [r for r in self._init_rows if (not flt or r.list_name == flt)]
        self.init_table.setRowCount(len(rows))
        for i, r in enumerate(rows):
            svc_txt = r.service_name or (r.additional_code[:60] + ("..." if len(r.additional_code) > 60 else ""))
            if r.is_pseudo_module:
                status_txt, status_clr = "内嵌代码/伪模块", _MUTED_COLOR
            elif r.module_loaded:
                status_txt, status_clr = "✓ 已加载", _OK_COLOR
            else:
                status_txt, status_clr = "⚠️ 未在工程加载", _WARN_COLOR
            items = [
                _ro_item(r.list_name.replace("EcuMDriver", "")),
                _ro_item(str(r.order_index)),
                _ro_item(r.short_name, bold=True),
                _ro_item(r.module_id),
                _ro_item(svc_txt or "-"),
                _ro_item(r.header_file or "-"),
                _ro_item(status_txt, color=status_clr),
            ]
            items[0].setData(Qt.UserRole, (r.list_name, r.short_name, r.container_path))
            for j, it in enumerate(items):
                self.init_table.setItem(i, j, it)
        self._update_init_buttons()

    def _selected_init_meta(self):
        sel = self.init_table.selectionModel().selectedRows()
        if not sel:
            return None
        it = self.init_table.item(sel[0].row(), 0)
        return it.data(Qt.UserRole) if it is not None else None

    def _update_init_buttons(self) -> None:
        meta = self._selected_init_meta()
        has = meta is not None
        self.btn_move_up.setEnabled(has)
        self.btn_move_down.setEnabled(has)
        self.btn_del_init.setEnabled(has)
        self.btn_locate_init.setEnabled(bool(meta and meta[2]))

    def _on_apply_general(self) -> None:
        try:
            ok = self.service.update_ecum_general(
                main_function_period=self.period_spin.value(),
                dev_error_detect=self.dev_det_check.isChecked(),
                slave_core_handling=self.slave_core_check.isChecked(),
                default_shutdown_state=self.shutdown_combo.currentText(),
            )
            if ok:
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "参数受基线锁定", str(exc))

    def _on_move_init(self, delta: int) -> None:
        meta = self._selected_init_meta()
        if not meta:
            return
        list_name, short_name, _ = meta
        try:
            if self.service.move_ecum_init_item(list_name, short_name, delta):
                self.reload()
                self._select_init_item(list_name, short_name)
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "无法移动", str(exc))

    def _select_init_item(self, list_name: str, short_name: str) -> None:
        for r in range(self.init_table.rowCount()):
            it = self.init_table.item(r, 0)
            if it and it.data(Qt.UserRole)[:2] == (list_name, short_name):
                self.init_table.selectRow(r)
                break

    def _on_add_init(self) -> None:
        dlg = QDialog(self)
        dlg.setWindowTitle("新增 EcuM 初始化项")
        form = QFormLayout(dlg)
        list_cb = QComboBox()
        for ln in ECUM_INIT_LIST_NAMES:
            list_cb.addItem(ln)
        list_cb.setCurrentText(self.init_list_combo.currentData() or "EcuMDriverInitListOne")
        name_ed = QLineEdit()
        mod_ed = QLineEdit()
        svc_ed = QLineEdit()
        hdr_ed = QLineEdit()
        form.addRow("目标列表:", list_cb)
        form.addRow("条目名称:", name_ed)
        form.addRow("ModuleID:", mod_ed)
        form.addRow("初始化函数:", svc_ed)
        form.addRow("头文件:", hdr_ed)
        btns = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        btns.accepted.connect(dlg.accept)
        btns.rejected.connect(dlg.reject)
        form.addRow(btns)
        if dlg.exec() != QDialog.Accepted:
            return
        try:
            self.service.add_ecum_init_item(
                list_cb.currentText(),
                name_ed.text().strip() or f"{mod_ed.text().strip()}_Init",
                mod_ed.text().strip() or "Code",
                service_name=svc_ed.text().strip(),
                header=hdr_ed.text().strip(),
            )
            self.reload()
            self.config_changed.emit()
        except (PreLockedError, ValueError, RuntimeError) as exc:
            QMessageBox.warning(self, "新增失败", str(exc))

    def _on_del_init(self) -> None:
        meta = self._selected_init_meta()
        if not meta:
            return
        try:
            if self.service.remove_ecum_init_item(meta[0], meta[1]):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "删除受限", str(exc))

    def _on_locate_init(self) -> None:
        meta = self._selected_init_meta()
        if meta and meta[2]:
            self.navigate_requested.emit(meta[2])

    def _on_ws_sel(self) -> None:
        sel = self.ws_table.selectionModel().selectedRows()
        if not sel:
            self.ws_apply_btn.setEnabled(False)
            return
        row = self._ws_rows[sel[0].row()]
        self.ws_apply_btn.setEnabled(True)
        self.ws_poll_check.setChecked(row.polling)
        self.ws_val_spin.setValue(row.validation_timeout or 0.0)

    def _on_apply_ws(self) -> None:
        sel = self.ws_table.selectionModel().selectedRows()
        if not sel:
            return
        row = self._ws_rows[sel[0].row()]
        try:
            if self.service.update_ecum_wakeup_source(
                row.short_name,
                polling=self.ws_poll_check.isChecked(),
                validation_timeout=self.ws_val_spin.value(),
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "更新受限", str(exc))


# ----------------------------------------------------------------------
# Tab 2: BswM Rules & Mode Control
# ----------------------------------------------------------------------


class BswMTab(QWidget):
    """Visualize and edit BswM module switches, rules/expressions, action lists, and mode ports."""

    config_changed = Signal()
    navigate_requested = Signal(str)

    def __init__(self, service: SystemServicesWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._switch_checks: Dict[str, QCheckBox] = {}
        self._all_rules: List[BswMRuleRow] = []
        self._visible_rules: List[BswMRuleRow] = []
        self._action_items: List[BswMActionListItemRow] = []
        self._mode_ports: List[BswMModePortRow] = []

        root = QVBoxLayout(self)

        # Top switches group
        sw_box = QGroupBox("BswMGeneral 模块使能开关")
        self._sw_layout = QHBoxLayout(sw_box)
        self._sw_layout.addStretch()
        root.addWidget(sw_box)

        split = QSplitter(Qt.Vertical)

        # Rules section
        rule_box = QGroupBox("仲裁规则 (BswMRule 与条件表达式解码)")
        rl = QVBoxLayout(rule_box)

        fbar = QHBoxLayout()
        self.rule_search = QLineEdit()
        self.rule_search.setPlaceholderText("搜索规则名 / 表达式 / ActionList...")
        self.rule_search.textChanged.connect(self._apply_rule_filter)
        self.only_issue_rules = QCheckBox("仅看问题")
        self.only_issue_rules.toggled.connect(self._apply_rule_filter)
        fbar.addWidget(self.rule_search, 1)
        fbar.addWidget(self.only_issue_rules)
        rl.addLayout(fbar)

        self.rules_table = QTableWidget(0, 7)
        self.rules_table.setHorizontalHeaderLabels([
            "规则名",
            "RuleId",
            "初始状态",
            "仅嵌套",
            "解码逻辑表达式",
            "True ActionList",
            "False ActionList",
        ])
        _configure_table(self.rules_table)
        self.rules_table.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.rules_table.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeToContents)
        self.rules_table.itemSelectionChanged.connect(self._on_rule_selected)
        rl.addWidget(self.rules_table)

        edit_bar = QHBoxLayout()
        self.rule_init_combo = QComboBox()
        self.rule_init_combo.addItems(["BSWM_FALSE", "BSWM_TRUE", "BSWM_UNDEFINED"])
        self.rule_nested_check = QCheckBox("NestedOnly")
        self.rule_true_combo = QComboBox()
        self.rule_false_combo = QComboBox()
        self.rule_apply_btn = QPushButton("应用选中规则")
        self.rule_locate_btn = QPushButton("定位")
        self.rule_apply_btn.clicked.connect(self._on_apply_rule)
        self.rule_locate_btn.clicked.connect(self._on_locate_rule)
        edit_bar.addWidget(QLabel("InitState:"))
        edit_bar.addWidget(self.rule_init_combo)
        edit_bar.addWidget(self.rule_nested_check)
        edit_bar.addWidget(QLabel("True AL:"))
        edit_bar.addWidget(self.rule_true_combo, 1)
        edit_bar.addWidget(QLabel("False AL:"))
        edit_bar.addWidget(self.rule_false_combo, 1)
        edit_bar.addWidget(self.rule_apply_btn)
        edit_bar.addWidget(self.rule_locate_btn)
        rl.addLayout(edit_bar)
        split.addWidget(rule_box)

        # Lower sub-tabs: ActionLists & ModeRequestPorts
        lower_tabs = QTabWidget()

        al_page = QWidget()
        al_l = QVBoxLayout(al_page)
        al_top = QHBoxLayout()
        al_top.addWidget(QLabel("动作列表 (BswMActionList):"))
        self.action_lists_combo = QComboBox()
        self.action_lists_combo.currentIndexChanged.connect(self._reload_action_items)
        self.al_exec_combo = QComboBox()
        self.al_exec_combo.addItems(["BSWM_CONDITION", "BSWM_TRIGGER"])
        self.al_exec_btn = QPushButton("更新执行模式")
        self.al_exec_btn.clicked.connect(self._on_update_al_exec)
        self.btn_action_up = QPushButton("动作上移 ↑")
        self.btn_action_down = QPushButton("动作下移 ↓")
        self.btn_action_abort = QPushButton("切换 AbortOnFail")
        self.btn_action_up.clicked.connect(lambda: self._on_move_action(-1))
        self.btn_action_down.clicked.connect(lambda: self._on_move_action(1))
        self.btn_action_abort.clicked.connect(self._on_toggle_abort)
        al_top.addWidget(self.action_lists_combo, 1)
        al_top.addWidget(self.al_exec_combo)
        al_top.addWidget(self.al_exec_btn)
        al_top.addWidget(self.btn_action_up)
        al_top.addWidget(self.btn_action_down)
        al_top.addWidget(self.btn_action_abort)
        al_l.addLayout(al_top)

        self.action_items_table = QTableWidget(0, 6)
        self.action_items_table.setHorizontalHeaderLabels([
            "Idx",
            "动作项名",
            "类型",
            "AbortOnFail",
            "目标",
            "动作详情",
        ])
        _configure_table(self.action_items_table)
        al_l.addWidget(self.action_items_table)
        lower_tabs.addTab(al_page, "动作列表序列 (BswMActionList)")

        mp_page = QWidget()
        mp_l = QVBoxLayout(mp_page)
        self.ports_table = QTableWidget(0, 5)
        self.ports_table.setHorizontalHeaderLabels(["请求端口", "处理方式", "启动仲裁", "源类型", "初始值"])
        _configure_table(self.ports_table)
        mp_l.addWidget(self.ports_table)
        mp_bar = QHBoxLayout()
        self.port_proc_combo = QComboBox()
        self.port_proc_combo.addItems(["BSWM_IMMEDIATE", "BSWM_DEFERRED"])
        self.port_init_check = QCheckBox("ArbitrateOnInit")
        self.port_apply_btn = QPushButton("更新选中 ModePort")
        self.port_apply_btn.clicked.connect(self._on_apply_port)
        mp_bar.addWidget(QLabel("Processing:"))
        mp_bar.addWidget(self.port_proc_combo)
        mp_bar.addWidget(self.port_init_check)
        mp_bar.addWidget(self.port_apply_btn)
        mp_bar.addStretch()
        mp_l.addLayout(mp_bar)
        self.ports_table.itemSelectionChanged.connect(self._on_port_selected)
        lower_tabs.addTab(mp_page, "模式请求端口 (ModeRequestPort)")

        split.addWidget(lower_tabs)
        split.setSizes([380, 260])
        root.addWidget(split, 1)

        self.reload()

    def reload(self) -> None:
        # Rebuild module switches cleanly
        while self._sw_layout.count():
            item = self._sw_layout.takeAt(0)
            if item.widget():
                item.widget().deleteLater()
        self._switch_checks.clear()

        switches = self.service.get_bswm_module_switches()
        for pname, val in switches.items():
            cb = QCheckBox(pname.replace("BswM", "").replace("Enabled", ""))
            cb.setToolTip(pname)
            cb.setChecked(val)
            cb.toggled.connect(lambda checked, key=pname: self._on_toggle_switch(key, checked))
            self._switch_checks[pname] = cb
            self._sw_layout.addWidget(cb)
        if not switches:
            self._sw_layout.addWidget(QLabel("未加载 BswM"))
        self._sw_layout.addStretch()

        # Populate ActionList combos
        als = self.service.list_bswm_action_lists()
        cur_al = self.action_lists_combo.currentData()
        for cb in (self.rule_true_combo, self.rule_false_combo, self.action_lists_combo):
            cb.blockSignals(True)
            cb.clear()
        self.rule_true_combo.addItem("(无)", "")
        self.rule_false_combo.addItem("(无)", "")
        for al in als:
            label = f"★ {al.short_name} (Init, {al.item_count})" if al.is_init_list else f"{al.short_name} ({al.item_count})"
            self.action_lists_combo.addItem(label, al.short_name)
            self.rule_true_combo.addItem(al.short_name, al.short_name)
            self.rule_false_combo.addItem(al.short_name, al.short_name)
        if cur_al:
            idx = self.action_lists_combo.findData(cur_al)
            if idx >= 0:
                self.action_lists_combo.setCurrentIndex(idx)
        for cb in (self.rule_true_combo, self.rule_false_combo, self.action_lists_combo):
            cb.blockSignals(False)

        self._all_rules = self.service.list_bswm_rules()
        self._apply_rule_filter()
        self._reload_action_items()

        self._mode_ports = self.service.list_bswm_mode_ports()
        self.ports_table.setRowCount(len(self._mode_ports))
        for i, p in enumerate(self._mode_ports):
            self.ports_table.setItem(i, 0, _ro_item(p.short_name, bold=True))
            self.ports_table.setItem(i, 1, _ro_item(p.processing or "-"))
            self.ports_table.setItem(i, 2, _ro_item("Yes" if p.arbitrate_on_init else "No"))
            self.ports_table.setItem(i, 3, _ro_item(p.source_kind or "-"))
            self.ports_table.setItem(i, 4, _ro_item(p.init_value or "-"))
        self._on_port_selected()

    def _apply_rule_filter(self) -> None:
        q = self.rule_search.text().strip().lower()
        only_iss = self.only_issue_rules.isChecked()
        self._visible_rules = [
            r
            for r in self._all_rules
            if (not only_iss or r.has_broken_ref or r.has_cycle)
            and (
                not q
                or q in r.short_name.lower()
                or q in r.decoded_expression.lower()
                or q in r.true_action_list.lower()
                or q in r.false_action_list.lower()
            )
        ]
        self.rules_table.setRowCount(len(self._visible_rules))
        for i, r in enumerate(self._visible_rules):
            expr_clr = _ERROR_COLOR if (r.has_broken_ref or r.has_cycle) else None
            expr_txt = f"🔁 {r.decoded_expression}" if r.has_cycle else r.decoded_expression
            items = [
                _ro_item(r.short_name, bold=True, color=expr_clr),
                _ro_item("-" if r.rule_id is None else str(r.rule_id)),
                _ro_item(r.init_state),
                _ro_item("Yes" if r.nested_only else "No"),
                _ro_item(expr_txt, color=expr_clr),
                _ro_item(r.true_action_list or "-"),
                _ro_item(r.false_action_list or "-"),
            ]
            for j, it in enumerate(items):
                self.rules_table.setItem(i, j, it)
        self._on_rule_selected()

    def _selected_rule(self) -> Optional[BswMRuleRow]:
        sel = self.rules_table.selectionModel().selectedRows()
        if not sel:
            return None
        idx = sel[0].row()
        return self._visible_rules[idx] if 0 <= idx < len(self._visible_rules) else None

    def _on_rule_selected(self) -> None:
        r = self._selected_rule()
        has = r is not None
        self.rule_apply_btn.setEnabled(has)
        self.rule_locate_btn.setEnabled(bool(r and r.container_path))
        if not r:
            return
        idx_init = self.rule_init_combo.findText(r.init_state)
        if idx_init >= 0:
            self.rule_init_combo.setCurrentIndex(idx_init)
        self.rule_nested_check.setChecked(r.nested_only)
        self.rule_true_combo.setCurrentIndex(max(0, self.rule_true_combo.findData(r.true_action_list)))
        self.rule_false_combo.setCurrentIndex(max(0, self.rule_false_combo.findData(r.false_action_list)))

    def _on_apply_rule(self) -> None:
        r = self._selected_rule()
        if not r:
            return
        try:
            if self.service.update_bswm_rule(
                r.short_name,
                init_state=self.rule_init_combo.currentText(),
                nested_only=self.rule_nested_check.isChecked(),
                true_action_list=self.rule_true_combo.currentData() or "",
                false_action_list=self.rule_false_combo.currentData() or "",
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "规则受基线锁定", str(exc))

    def _on_locate_rule(self) -> None:
        r = self._selected_rule()
        if r and r.container_path:
            self.navigate_requested.emit(r.container_path)

    def _reload_action_items(self) -> None:
        al_name = self.action_lists_combo.currentData()
        if not al_name:
            self.action_items_table.setRowCount(0)
            self._action_items = []
            return
        als = {a.short_name: a for a in self.service.list_bswm_action_lists()}
        cur_al = als.get(al_name)
        if cur_al:
            idx = self.al_exec_combo.findText(cur_al.execution)
            if idx >= 0:
                self.al_exec_combo.setCurrentIndex(idx)
        self._action_items = self.service.list_bswm_action_list_items(al_name)
        self.action_items_table.setRowCount(len(self._action_items))
        for i, it in enumerate(self._action_items):
            clr = _ERROR_COLOR if it.has_broken_ref else None
            row_items = [
                _ro_item(str(it.item_index)),
                _ro_item(it.short_name, bold=True, color=clr),
                _ro_item(it.action_kind),
                _ro_item("Yes" if it.abort_on_fail else "No"),
                _ro_item(it.target_name or "-"),
                _ro_item(it.action_summary, color=clr),
            ]
            for j, cell in enumerate(row_items):
                self.action_items_table.setItem(i, j, cell)

    def _on_update_al_exec(self) -> None:
        al_name = self.action_lists_combo.currentData()
        if not al_name:
            return
        try:
            if self.service.update_bswm_action_list(al_name, execution=self.al_exec_combo.currentText()):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "修改受限", str(exc))

    def _on_move_action(self, delta: int) -> None:
        al_name = self.action_lists_combo.currentData()
        sel = self.action_items_table.selectionModel().selectedRows()
        if not al_name or not sel:
            return
        item = self._action_items[sel[0].row()]
        try:
            if self.service.move_bswm_action_item(al_name, item.short_name, delta):
                self._reload_action_items()
                for idx, row in enumerate(self._action_items):
                    if row.short_name == item.short_name:
                        self.action_items_table.selectRow(idx)
                        break
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "移动受限", str(exc))

    def _on_toggle_abort(self) -> None:
        al_name = self.action_lists_combo.currentData()
        sel = self.action_items_table.selectionModel().selectedRows()
        if not al_name or not sel:
            return
        item = self._action_items[sel[0].row()]
        try:
            if self.service.update_bswm_action_item(al_name, item.short_name, abort_on_fail=not item.abort_on_fail):
                self._reload_action_items()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "修改受限", str(exc))

    def _on_port_selected(self) -> None:
        sel = self.ports_table.selectionModel().selectedRows()
        if not sel:
            self.port_apply_btn.setEnabled(False)
            return
        p = self._mode_ports[sel[0].row()]
        self.port_apply_btn.setEnabled(True)
        idx = self.port_proc_combo.findText(p.processing)
        if idx >= 0:
            self.port_proc_combo.setCurrentIndex(idx)
        self.port_init_check.setChecked(p.arbitrate_on_init)

    def _on_apply_port(self) -> None:
        sel = self.ports_table.selectionModel().selectedRows()
        if not sel:
            return
        p = self._mode_ports[sel[0].row()]
        try:
            if self.service.update_bswm_mode_port(
                p.short_name,
                processing=self.port_proc_combo.currentText(),
                arbitrate_on_init=self.port_init_check.isChecked(),
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "修改受限", str(exc))

    def _on_toggle_switch(self, param_name: str, checked: bool) -> None:
        try:
            if self.service.set_bswm_module_switch(param_name, checked):
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "开关受基线锁定", str(exc))
            self.reload()


# ----------------------------------------------------------------------
# Tab 3: Os Multi-Core & Resources
# ----------------------------------------------------------------------


class OsResourcesTab(QWidget):
    """Display and edit OsOS, multi-core stack summary, Tasks, ISRs, Alarms/ScheduleTables, and Spinlocks."""

    config_changed = Signal()
    navigate_requested = Signal(str)

    def __init__(self, service: SystemServicesWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._tasks: List[OsTaskRow] = []
        self._isrs: List[OsIsrRow] = []
        self._timings: List[OsTimingRow] = []

        root = QVBoxLayout(self)

        # Global OS bar
        os_box = QGroupBox("OsOS 全局内核与 Hook 配置")
        ol = QHBoxLayout(os_box)
        self.os_status_combo = QComboBox()
        self.os_status_combo.addItems(["STANDARD", "EXTENDED"])
        self.os_sc_combo = QComboBox()
        self.os_sc_combo.addItems(["SC1", "SC2", "SC3", "SC4"])
        self.os_stack_mon = QCheckBox("StackMonitoring")
        self.os_err_hook = QCheckBox("ErrorHook")
        self.os_start_hook = QCheckBox("StartupHook")
        self.os_shut_hook = QCheckBox("ShutdownHook")
        self.btn_apply_os = QPushButton("应用 OS 全局设置")
        self.btn_apply_os.clicked.connect(self._on_apply_general)
        self.os_meta_lbl = QLabel("")
        self.os_meta_lbl.setStyleSheet("color: #57606a;")

        ol.addWidget(QLabel("Status:"))
        ol.addWidget(self.os_status_combo)
        ol.addWidget(QLabel("SC:"))
        ol.addWidget(self.os_sc_combo)
        ol.addWidget(self.os_stack_mon)
        ol.addWidget(self.os_err_hook)
        ol.addWidget(self.os_start_hook)
        ol.addWidget(self.os_shut_hook)
        ol.addWidget(self.btn_apply_os)
        ol.addWidget(self.os_meta_lbl, 1)
        root.addWidget(os_box)

        # Multi-core summary table
        core_box = QGroupBox("多核与系统应用栈预算概览")
        cl = QVBoxLayout(core_box)
        self.cores_table = QTableWidget(0, 8)
        self.cores_table.setHorizontalHeaderLabels([
            "Core",
            "CoreID",
            "SystemApplication",
            "Partition",
            "IdleTask",
            "Tasks",
            "ISRs",
            "总栈预算 (Bytes)",
        ])
        _configure_table(self.cores_table)
        self.cores_table.setMaximumHeight(135)
        cl.addWidget(self.cores_table)
        root.addWidget(core_box)

        # Subtabs
        self.os_subtabs = QTabWidget()

        # Tasks subtab
        t_page = QWidget()
        tl = QVBoxLayout(t_page)
        self.tasks_table = QTableWidget(0, 9)
        self.tasks_table.setHorizontalHeaderLabels([
            "Task 名称",
            "所属 Core",
            "OsApplication",
            "优先级",
            "栈大小(B)",
            "Activation",
            "调度策略",
            "类型",
            "激活来源 (Alarm / ScheduleTable)",
        ])
        _configure_table(self.tasks_table)
        self.tasks_table.itemSelectionChanged.connect(self._on_task_selected)
        tl.addWidget(self.tasks_table)

        t_edit = QHBoxLayout()
        self.task_prio_spin = QSpinBox()
        self.task_prio_spin.setRange(0, 1024)
        self.task_stack_spin = QSpinBox()
        self.task_stack_spin.setRange(0, 1048576)
        self.task_stack_spin.setSingleStep(128)
        self.task_act_spin = QSpinBox()
        self.task_act_spin.setRange(1, 255)
        self.task_sched_combo = QComboBox()
        self.task_sched_combo.addItems(["FULL", "NON"])
        self.task_type_combo = QComboBox()
        self.task_type_combo.addItems(["BASIC", "EXTENDED"])
        self.btn_task_apply = QPushButton("应用选中 Task")
        self.btn_task_apply.clicked.connect(self._on_apply_task)
        t_edit.addWidget(QLabel("优先级:"))
        t_edit.addWidget(self.task_prio_spin)
        t_edit.addWidget(QLabel("栈(B):"))
        t_edit.addWidget(self.task_stack_spin)
        t_edit.addWidget(QLabel("Activation:"))
        t_edit.addWidget(self.task_act_spin)
        t_edit.addWidget(QLabel("Schedule:"))
        t_edit.addWidget(self.task_sched_combo)
        t_edit.addWidget(QLabel("Type:"))
        t_edit.addWidget(self.task_type_combo)
        t_edit.addWidget(self.btn_task_apply)
        t_edit.addStretch()
        tl.addLayout(t_edit)
        self.os_subtabs.addTab(t_page, "Tasks")

        # ISRs subtab
        i_page = QWidget()
        il = QVBoxLayout(i_page)
        self.isrs_table = QTableWidget(0, 8)
        self.isrs_table.setHorizontalHeaderLabels([
            "ISR 名称",
            "所属 Core",
            "OsApplication",
            "类别",
            "中断源",
            "优先级",
            "栈大小(B)",
            "Nesting / InitEn",
        ])
        _configure_table(self.isrs_table)
        self.isrs_table.itemSelectionChanged.connect(self._on_isr_selected)
        il.addWidget(self.isrs_table)
        i_edit = QHBoxLayout()
        self.isr_cat_combo = QComboBox()
        self.isr_cat_combo.addItems(["CATEGORY_2", "CATEGORY_1"])
        self.isr_src_spin = QSpinBox()
        self.isr_src_spin.setRange(0, 65535)
        self.isr_prio_spin = QSpinBox()
        self.isr_prio_spin.setRange(0, 1024)
        self.isr_stack_spin = QSpinBox()
        self.isr_stack_spin.setRange(0, 1048576)
        self.isr_stack_spin.setSingleStep(128)
        self.btn_isr_apply = QPushButton("应用选中 ISR")
        self.btn_isr_apply.clicked.connect(self._on_apply_isr)
        i_edit.addWidget(QLabel("Category:"))
        i_edit.addWidget(self.isr_cat_combo)
        i_edit.addWidget(QLabel("Source:"))
        i_edit.addWidget(self.isr_src_spin)
        i_edit.addWidget(QLabel("优先级:"))
        i_edit.addWidget(self.isr_prio_spin)
        i_edit.addWidget(QLabel("栈(B):"))
        i_edit.addWidget(self.isr_stack_spin)
        i_edit.addWidget(self.btn_isr_apply)
        i_edit.addStretch()
        il.addLayout(i_edit)
        self.os_subtabs.addTab(i_page, "ISRs")

        # Counters / Alarms / ScheduleTables subtab
        tm_page = QWidget()
        tml = QVBoxLayout(tm_page)
        self.timing_table = QTableWidget(0, 7)
        self.timing_table.setHorizontalHeaderLabels([
            "类型",
            "名称",
            "OwnerApp",
            "Counter / ISR",
            "Duration / Max",
            "Repeating / Tick",
            "动作与激活明细",
        ])
        _configure_table(self.timing_table)
        self.timing_table.itemSelectionChanged.connect(self._on_timing_selected)
        tml.addWidget(self.timing_table)
        tm_edit = QHBoxLayout()
        self.st_dur_spin = QSpinBox()
        self.st_dur_spin.setRange(1, 1000000)
        self.st_rep_check = QCheckBox("Repeating")
        self.btn_st_apply = QPushButton("应用选中 ScheduleTable")
        self.btn_st_apply.clicked.connect(self._on_apply_st)
        tm_edit.addWidget(QLabel("ScheduleTable Duration:"))
        tm_edit.addWidget(self.st_dur_spin)
        tm_edit.addWidget(self.st_rep_check)
        tm_edit.addWidget(self.btn_st_apply)
        tm_edit.addStretch()
        tml.addLayout(tm_edit)
        self.os_subtabs.addTab(tm_page, "Counters / Alarms / ScheduleTables")

        # Resources / Spinlocks / IOC subtab
        sy_page = QWidget()
        syl = QVBoxLayout(sy_page)
        self.sync_table = QTableWidget(0, 5)
        self.sync_table.setHorizontalHeaderLabels(["类型", "名称", "策略 / 锁方法", "访问应用", "通信关系"])
        _configure_table(self.sync_table)
        syl.addWidget(self.sync_table)
        self.os_subtabs.addTab(sy_page, "Resources / Spinlocks / IOC")

        root.addWidget(self.os_subtabs, 1)
        self.reload()

    def reload(self) -> None:
        info = self.service.get_os_general()
        for w in (self.os_status_combo, self.os_sc_combo, self.os_stack_mon, self.os_err_hook, self.os_start_hook, self.os_shut_hook):
            w.blockSignals(True)
        self.btn_apply_os.setEnabled(info.loaded)
        if info.status:
            self.os_status_combo.setCurrentText(info.status)
        if info.scalability_class:
            self.os_sc_combo.setCurrentText(info.scalability_class)
        self.os_stack_mon.setChecked(info.stack_monitoring)
        self.os_err_hook.setChecked(info.error_hook)
        self.os_start_hook.setChecked(info.startup_hook)
        self.os_shut_hook.setChecked(info.shutdown_hook)
        self.os_meta_lbl.setText(
            f"Master={info.master_core or '-'} | Cores={info.actual_core_count}/{info.number_of_cores or '-'}"
            if info.loaded
            else "未加载 Os"
        )
        for w in (self.os_status_combo, self.os_sc_combo, self.os_stack_mon, self.os_err_hook, self.os_start_hook, self.os_shut_hook):
            w.blockSignals(False)

        cores = self.service.list_os_core_summaries()
        self.cores_table.setRowCount(len(cores))
        for i, c in enumerate(cores):
            self.cores_table.setItem(i, 0, _ro_item(c.core_name, bold=True))
            self.cores_table.setItem(i, 1, _ro_item("-" if c.core_id is None else str(c.core_id)))
            self.cores_table.setItem(i, 2, _ro_item(c.system_app or "-"))
            self.cores_table.setItem(i, 3, _ro_item(c.partition_name or "-"))
            self.cores_table.setItem(i, 4, _ro_item(c.idle_task or "-"))
            self.cores_table.setItem(i, 5, _ro_item(str(c.task_count)))
            self.cores_table.setItem(i, 6, _ro_item(str(c.isr_count)))
            self.cores_table.setItem(i, 7, _ro_item(f"{c.total_stack_bytes} B", color=_OK_COLOR))

        self._tasks = self.service.list_os_tasks()
        self.tasks_table.setRowCount(len(self._tasks))
        for i, t in enumerate(self._tasks):
            clr = _ERROR_COLOR if t.has_invalid_stack else (_WARN_COLOR if not t.owner_app else None)
            items = [
                _ro_item(t.short_name, bold=True, color=clr),
                _ro_item(t.core_name or "-"),
                _ro_item(t.owner_app or "⚠️ 未归属"),
                _ro_item("-" if t.priority is None else str(t.priority)),
                _ro_item("-" if t.stack_size is None else str(t.stack_size), color=_ERROR_COLOR if t.has_invalid_stack else None),
                _ro_item("-" if t.activation is None else str(t.activation)),
                _ro_item(t.schedule or "-"),
                _ro_item(t.task_type or "-"),
                _ro_item(", ".join(t.triggers) or "-"),
            ]
            for j, cell in enumerate(items):
                self.tasks_table.setItem(i, j, cell)

        self._isrs = self.service.list_os_isrs()
        self.isrs_table.setRowCount(len(self._isrs))
        for i, isr in enumerate(self._isrs):
            clr = _ERROR_COLOR if isr.has_invalid_stack else None
            items = [
                _ro_item(isr.short_name, bold=True, color=clr),
                _ro_item(isr.core_name or "-"),
                _ro_item(isr.owner_app or "-"),
                _ro_item(isr.category or "-"),
                _ro_item("-" if isr.interrupt_source is None else str(isr.interrupt_source)),
                _ro_item("-" if isr.priority is None else str(isr.priority)),
                _ro_item("-" if isr.stack_size is None else str(isr.stack_size), color=clr),
                _ro_item(f"Nest={isr.enable_nesting} / Init={isr.initial_enable}"),
            ]
            for j, cell in enumerate(items):
                self.isrs_table.setItem(i, j, cell)

        self._timings = self.service.list_os_counters_alarms_schedtables()
        self.timing_table.setRowCount(len(self._timings))
        for i, tm in enumerate(self._timings):
            clr = _ERROR_COLOR if tm.has_broken_ref else None
            rep_txt = "-"
            if tm.repeating is not None:
                rep_txt = "Repeating" if tm.repeating else "OneShot"
            elif tm.seconds_per_tick is not None:
                rep_txt = f"{tm.seconds_per_tick:g} s/tick"
            self.timing_table.setItem(i, 0, _ro_item(tm.kind))
            self.timing_table.setItem(i, 1, _ro_item(tm.short_name, bold=True, color=clr))
            self.timing_table.setItem(i, 2, _ro_item(tm.owner_app or "-"))
            self.timing_table.setItem(i, 3, _ro_item(tm.counter_ref_name or "-", color=clr))
            self.timing_table.setItem(i, 4, _ro_item("-" if tm.duration_or_max is None else str(tm.duration_or_max)))
            self.timing_table.setItem(i, 5, _ro_item(rep_txt))
            self.timing_table.setItem(i, 6, _ro_item(tm.detail))

        sync_rows = self.service.list_os_resources_spinlocks()
        self.sync_table.setRowCount(len(sync_rows))
        for i, s in enumerate(sync_rows):
            self.sync_table.setItem(i, 0, _ro_item(s.kind))
            self.sync_table.setItem(i, 1, _ro_item(s.short_name, bold=True))
            self.sync_table.setItem(i, 2, _ro_item(s.policy_or_method or "-"))
            self.sync_table.setItem(i, 3, _ro_item(", ".join(s.accessing_apps) or "-"))
            self.sync_table.setItem(i, 4, _ro_item(s.detail or "-"))

        self._on_task_selected()
        self._on_isr_selected()
        self._on_timing_selected()

    def _on_apply_general(self) -> None:
        try:
            if self.service.update_os_general(
                status=self.os_status_combo.currentText(),
                scalability_class=self.os_sc_combo.currentText(),
                stack_monitoring=self.os_stack_mon.isChecked(),
                error_hook=self.os_err_hook.isChecked(),
                startup_hook=self.os_start_hook.isChecked(),
                shutdown_hook=self.os_shut_hook.isChecked(),
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "参数受限", str(exc))

    def _on_task_selected(self) -> None:
        sel = self.tasks_table.selectionModel().selectedRows()
        if not sel:
            self.btn_task_apply.setEnabled(False)
            return
        t = self._tasks[sel[0].row()]
        self.btn_task_apply.setEnabled(True)
        self.task_prio_spin.setValue(t.priority or 0)
        self.task_stack_spin.setValue(t.stack_size or 0)
        self.task_act_spin.setValue(max(1, t.activation or 1))
        if t.schedule:
            self.task_sched_combo.setCurrentText(t.schedule)
        if t.task_type:
            self.task_type_combo.setCurrentText(t.task_type)

    def _on_apply_task(self) -> None:
        sel = self.tasks_table.selectionModel().selectedRows()
        if not sel:
            return
        t = self._tasks[sel[0].row()]
        try:
            if self.service.update_os_task(
                t.short_name,
                priority=self.task_prio_spin.value(),
                stack_size=self.task_stack_spin.value(),
                activation=self.task_act_spin.value(),
                schedule=self.task_sched_combo.currentText(),
                task_type=self.task_type_combo.currentText(),
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "Task 修改受限", str(exc))

    def _on_isr_selected(self) -> None:
        sel = self.isrs_table.selectionModel().selectedRows()
        if not sel:
            self.btn_isr_apply.setEnabled(False)
            return
        isr = self._isrs[sel[0].row()]
        self.btn_isr_apply.setEnabled(True)
        if isr.category:
            self.isr_cat_combo.setCurrentText(isr.category)
        self.isr_src_spin.setValue(isr.interrupt_source or 0)
        self.isr_prio_spin.setValue(isr.priority or 0)
        self.isr_stack_spin.setValue(isr.stack_size or 0)

    def _on_apply_isr(self) -> None:
        sel = self.isrs_table.selectionModel().selectedRows()
        if not sel:
            return
        isr = self._isrs[sel[0].row()]
        try:
            if self.service.update_os_isr(
                isr.short_name,
                category=self.isr_cat_combo.currentText(),
                interrupt_source=self.isr_src_spin.value(),
                priority=self.isr_prio_spin.value(),
                stack_size=self.isr_stack_spin.value(),
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "ISR 修改受限", str(exc))

    def _on_timing_selected(self) -> None:
        sel = self.timing_table.selectionModel().selectedRows()
        if not sel:
            self.btn_st_apply.setEnabled(False)
            return
        tm = self._timings[sel[0].row()]
        is_st = tm.kind == "ScheduleTable"
        self.btn_st_apply.setEnabled(is_st)
        if is_st:
            self.st_dur_spin.setValue(max(1, tm.duration_or_max or 1))
            self.st_rep_check.setChecked(bool(tm.repeating))

    def _on_apply_st(self) -> None:
        sel = self.timing_table.selectionModel().selectedRows()
        if not sel:
            return
        tm = self._timings[sel[0].row()]
        if tm.kind != "ScheduleTable":
            return
        try:
            if self.service.update_os_schedule_table(
                tm.short_name, duration=self.st_dur_spin.value(), repeating=self.st_rep_check.isChecked()
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "ScheduleTable 修改受限", str(exc))


# ----------------------------------------------------------------------
# Tab 4: Dcm + CanTp Diagnostics
# ----------------------------------------------------------------------


class DiagDcmCanTpTab(QWidget):
    """Display and edit end-to-end UDS Diagnostic Channels (CanIf-CanTp-PduR-Dcm), Services, and Sessions."""

    config_changed = Signal()
    navigate_requested = Signal(str)

    def __init__(self, service: SystemServicesWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._channels: List[DiagChannelRow] = []
        self._services: List[DcmServiceRow] = []
        self._sessions: List[DcmSessionRow] = []

        root = QVBoxLayout(self)

        # Top: end-to-end diagnostic channel chain
        ch_box = QGroupBox("诊断通信全链路 (CanIf CAN ID ↔ CanTp NSdu/FC ↔ PduR TP ↔ Dcm Protocol)")
        cl = QVBoxLayout(ch_box)
        self.diag_channels_table = QTableWidget(0, 10)
        self.diag_channels_table.setHorizontalHeaderLabels([
            "通道名",
            "方向",
            "寻址",
            "CAN ID",
            "CanIf PDU",
            "CanTp NSdu",
            "PduR TP",
            "Dcm Buffer",
            "BS / STmin / Pad",
            "链路状态",
        ])
        _configure_table(self.diag_channels_table)
        self.diag_channels_table.itemSelectionChanged.connect(self._on_ch_selected)
        cl.addWidget(self.diag_channels_table)

        edit_row = QHBoxLayout()
        self.cantp_bs_spin = QSpinBox()
        self.cantp_bs_spin.setRange(0, 255)
        self.cantp_stmin_spin = QDoubleSpinBox()
        self.cantp_stmin_spin.setRange(0.0, 1.0)
        self.cantp_stmin_spin.setDecimals(4)
        self.cantp_stmin_spin.setSingleStep(0.005)
        self.cantp_pad_combo = QComboBox()
        self.cantp_pad_combo.addItems(["CANTP_ON", "CANTP_OFF"])
        self.dcm_buf_spin = QSpinBox()
        self.dcm_buf_spin.setRange(8, 65535)
        self.btn_diag_apply = QPushButton("应用 CanTp / DcmBuffer 参数")
        self.btn_diag_apply.clicked.connect(self._on_apply_diag_channel)
        self.btn_diag_locate = QPushButton("定位")
        self.btn_diag_locate.clicked.connect(self._on_locate_channel)

        edit_row.addWidget(QLabel("BS:"))
        edit_row.addWidget(self.cantp_bs_spin)
        edit_row.addWidget(QLabel("STmin(s):"))
        edit_row.addWidget(self.cantp_stmin_spin)
        edit_row.addWidget(QLabel("Padding:"))
        edit_row.addWidget(self.cantp_pad_combo)
        edit_row.addWidget(QLabel("DcmBuffer(B):"))
        edit_row.addWidget(self.dcm_buf_spin)
        edit_row.addWidget(self.btn_diag_apply)
        edit_row.addWidget(self.btn_diag_locate)
        edit_row.addStretch()
        cl.addLayout(edit_row)
        root.addWidget(ch_box, 1)

        # Lower subtabs: UDS Services / Sessions & Security / DID & Routine
        subtabs = QTabWidget()

        # UDS Services
        svc_page = QWidget()
        sl = QVBoxLayout(svc_page)
        sbar = QHBoxLayout()
        self.btn_add_service = QPushButton("新增 UDS 服务...")
        self.btn_toggle_svc_used = QPushButton("切换启用 (Used)")
        self.btn_add_service.clicked.connect(self._on_add_service)
        self.btn_toggle_svc_used.clicked.connect(self._on_toggle_service_used)
        sbar.addWidget(self.btn_add_service)
        sbar.addWidget(self.btn_toggle_svc_used)
        sbar.addStretch()
        sl.addLayout(sbar)

        self.dcm_services_table = QTableWidget(0, 6)
        self.dcm_services_table.setHorizontalHeaderLabels([
            "服务名",
            "SID",
            "标准服务名",
            "SubFunc",
            "启用",
            "子服务 (DcmDsdSubService)",
        ])
        _configure_table(self.dcm_services_table)
        sl.addWidget(self.dcm_services_table)
        subtabs.addTab(svc_page, "UDS 服务表 (DcmDsdService)")

        # Sessions & Security
        sess_page = QWidget()
        ssl = QVBoxLayout(sess_page)
        sess_split = QSplitter(Qt.Horizontal)

        s_left = QWidget()
        sll = QVBoxLayout(s_left)
        self.sessions_table = QTableWidget(0, 5)
        self.sessions_table.setHorizontalHeaderLabels(["会话名", "Level", "P2Max(s)", "P2*Max(s)", "Boot 模式"])
        _configure_table(self.sessions_table)
        self.sessions_table.itemSelectionChanged.connect(self._on_session_sel)
        sll.addWidget(self.sessions_table)

        s_edit = QHBoxLayout()
        self.p2_spin = QDoubleSpinBox()
        self.p2_spin.setRange(0.001, 10.0)
        self.p2_spin.setDecimals(3)
        self.p2s_spin = QDoubleSpinBox()
        self.p2s_spin.setRange(0.01, 60.0)
        self.p2s_spin.setDecimals(3)
        self.btn_sess_apply = QPushButton("更新会话时序")
        self.btn_sess_add = QPushButton("新增会话...")
        self.btn_sess_apply.clicked.connect(self._on_apply_session)
        self.btn_sess_add.clicked.connect(self._on_add_session)
        s_edit.addWidget(QLabel("P2(s):"))
        s_edit.addWidget(self.p2_spin)
        s_edit.addWidget(QLabel("P2*(s):"))
        s_edit.addWidget(self.p2s_spin)
        s_edit.addWidget(self.btn_sess_apply)
        s_edit.addWidget(self.btn_sess_add)
        sll.addLayout(s_edit)
        sess_split.addWidget(s_left)

        s_right = QWidget()
        srl = QVBoxLayout(s_right)
        self.sec_table = QTableWidget(0, 5)
        self.sec_table.setHorizontalHeaderLabels(["安全等级名", "Level", "AttDelay", "Delay(s)", "Seed/Key"])
        _configure_table(self.sec_table)
        srl.addWidget(self.sec_table)
        sess_split.addWidget(s_right)
        ssl.addWidget(sess_split)
        subtabs.addTab(sess_page, "会话与安全等级")

        # DID & Routine
        did_page = QWidget()
        dl = QVBoxLayout(did_page)
        self.did_table = QTableWidget(0, 5)
        self.did_table.setHorizontalHeaderLabels(["类型", "名称", "ID (Hex)", "启用", "详情"])
        _configure_table(self.did_table)
        dl.addWidget(self.did_table)
        subtabs.addTab(did_page, "DID / Routine")

        root.addWidget(subtabs, 1)
        self.reload()

    def reload(self) -> None:
        self._channels = self.service.list_diag_channels()
        self.diag_channels_table.setRowCount(len(self._channels))
        for i, ch in enumerate(self._channels):
            buf_txt = f"{ch.buffer_name} ({ch.buffer_size}B)" if ch.buffer_size is not None else (ch.buffer_name or "-")
            tp_params = f"BS={ch.bs if ch.bs is not None else '-'}, ST={ch.stmin if ch.stmin is not None else '-'}, {ch.padding or '-'}"
            st_txt, st_clr = ("✓ 完整", _OK_COLOR) if ch.chain_complete else (f"⚠️ {ch.chain_note}", _WARN_COLOR)
            items = [
                _ro_item(ch.name, bold=True),
                _ro_item(ch.direction),
                _ro_item(ch.addr_type or "-"),
                _ro_item(ch.can_id_hex),
                _ro_item(ch.canif_pdu_name or "-"),
                _ro_item(ch.cantp_nsdu_name or "-"),
                _ro_item(ch.pdur_path_name or "-"),
                _ro_item(buf_txt),
                _ro_item(tp_params),
                _ro_item(st_txt, color=st_clr),
            ]
            for j, cell in enumerate(items):
                self.diag_channels_table.setItem(i, j, cell)

        self._services = self.service.list_dcm_services()
        self.dcm_services_table.setRowCount(len(self._services))
        for i, s in enumerate(self._services):
            self.dcm_services_table.setItem(i, 0, _ro_item(s.short_name, bold=True))
            self.dcm_services_table.setItem(i, 1, _ro_item(s.sid_hex))
            self.dcm_services_table.setItem(i, 2, _ro_item(s.service_label))
            self.dcm_services_table.setItem(i, 3, _ro_item("Yes" if s.subfunc_avail else "No"))
            self.dcm_services_table.setItem(i, 4, _ro_item("Yes" if s.used else "No", color=_OK_COLOR if s.used else _MUTED_COLOR))
            self.dcm_services_table.setItem(i, 5, _ro_item(s.subservice_summary or "-"))

        self._sessions = self.service.list_dcm_sessions()
        self.sessions_table.setRowCount(len(self._sessions))
        for i, sess in enumerate(self._sessions):
            self.sessions_table.setItem(i, 0, _ro_item(sess.short_name, bold=True))
            self.sessions_table.setItem(i, 1, _ro_item(sess.level_hex))
            self.sessions_table.setItem(i, 2, _ro_item("-" if sess.p2_server_max is None else f"{sess.p2_server_max:g}"))
            self.sessions_table.setItem(i, 3, _ro_item("-" if sess.p2_star_server_max is None else f"{sess.p2_star_server_max:g}"))
            self.sessions_table.setItem(i, 4, _ro_item(sess.for_boot))

        sec_rows = self.service.list_dcm_security_levels()
        self.sec_table.setRowCount(len(sec_rows))
        for i, sr in enumerate(sec_rows):
            self.sec_table.setItem(i, 0, _ro_item(sr.short_name, bold=True))
            self.sec_table.setItem(i, 1, _ro_item("-" if sr.level is None else f"0x{sr.level:02X}"))
            self.sec_table.setItem(i, 2, _ro_item("-" if sr.num_attempts is None else str(sr.num_attempts)))
            self.sec_table.setItem(i, 3, _ro_item("-" if sr.delay_time is None else f"{sr.delay_time:g}"))
            self.sec_table.setItem(i, 4, _ro_item(f"{sr.seed_size or '-'}/{sr.key_size or '-'}"))

        did_rows = self.service.list_dcm_dids_and_routines()
        self.did_table.setRowCount(len(did_rows))
        for i, dr in enumerate(did_rows):
            self.did_table.setItem(i, 0, _ro_item(dr.kind))
            self.did_table.setItem(i, 1, _ro_item(dr.short_name, bold=True))
            self.did_table.setItem(i, 2, _ro_item(dr.identifier_hex))
            self.did_table.setItem(i, 3, _ro_item("Yes" if dr.used else "No"))
            self.did_table.setItem(i, 4, _ro_item(dr.detail or "-"))

        self._on_ch_selected()
        self._on_session_sel()

    def _selected_channel(self) -> Optional[DiagChannelRow]:
        sel = self.diag_channels_table.selectionModel().selectedRows()
        if not sel:
            return None
        return self._channels[sel[0].row()] if 0 <= sel[0].row() < len(self._channels) else None

    def _on_ch_selected(self) -> None:
        ch = self._selected_channel()
        has = ch is not None
        self.btn_diag_apply.setEnabled(bool(ch and (ch.cantp_nsdu_name or ch.buffer_name)))
        self.btn_diag_locate.setEnabled(bool(ch and (ch.dcm_container_path or ch.cantp_nsdu_path)))
        if not ch:
            return
        self.cantp_bs_spin.setEnabled(ch.direction == "RX" and bool(ch.cantp_nsdu_name))
        self.cantp_stmin_spin.setEnabled(ch.direction == "RX" and bool(ch.cantp_nsdu_name))
        self.cantp_bs_spin.setValue(ch.bs or 0)
        self.cantp_stmin_spin.setValue(ch.stmin or 0.0)
        if ch.padding:
            self.cantp_pad_combo.setCurrentText(ch.padding)
        self.dcm_buf_spin.setEnabled(bool(ch.buffer_name))
        self.dcm_buf_spin.setValue(max(8, ch.buffer_size or 64))

    def _on_apply_diag_channel(self) -> None:
        ch = self._selected_channel()
        if not ch:
            return
        changed = False
        try:
            if ch.cantp_nsdu_name:
                kw = {"padding": self.cantp_pad_combo.currentText()}
                if ch.direction == "RX":
                    kw["bs"] = self.cantp_bs_spin.value()
                    kw["stmin"] = self.cantp_stmin_spin.value()
                if self.service.update_cantp_nsdu(ch.cantp_nsdu_name, **kw):
                    changed = True
            if ch.buffer_name:
                if self.service.update_dcm_buffer(ch.buffer_name, self.dcm_buf_spin.value()):
                    changed = True
            if changed:
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "修改受限", str(exc))

    def _on_locate_channel(self) -> None:
        ch = self._selected_channel()
        if ch:
            path = ch.dcm_container_path or ch.cantp_nsdu_path
            if path:
                self.navigate_requested.emit(path)

    def _on_add_service(self) -> None:
        dlg = QDialog(self)
        dlg.setWindowTitle("新增 UDS 服务 (DcmDsdService)")
        form = QFormLayout(dlg)
        sid_combo = QComboBox()
        sid_combo.setEditable(True)
        for sid, lbl in sorted(UDS_SID_NAMES.items()):
            sid_combo.addItem(f"0x{sid:02X} - {lbl}", sid)
        name_ed = QLineEdit()
        subf_cb = QCheckBox("支持 SubFunction")
        subf_cb.setChecked(True)
        used_cb = QCheckBox("启用 (Used)")
        used_cb.setChecked(True)
        form.addRow("SID:", sid_combo)
        form.addRow("服务容器名(可选):", name_ed)
        form.addRow(subf_cb)
        form.addRow(used_cb)
        btns = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        btns.accepted.connect(dlg.accept)
        btns.rejected.connect(dlg.reject)
        form.addRow(btns)
        if dlg.exec() != QDialog.Accepted:
            return
        raw_sid = sid_combo.currentData()
        if raw_sid is None:
            txt = sid_combo.currentText().split("-")[0].strip()
            raw_sid = int(txt, 0)
        tbl_name = self._services[0].table_name if self._services else "DcmDsdServiceTable"
        short_n = name_ed.text().strip() or f"{UDS_SID_NAMES.get(raw_sid, 'Service')}_0x{raw_sid:02X}"
        try:
            self.service.add_dcm_service(
                tbl_name, short_n, int(raw_sid), subfunc_avail=subf_cb.isChecked(), used=used_cb.isChecked()
            )
            self.reload()
            self.config_changed.emit()
        except (PreLockedError, ValueError, RuntimeError) as exc:
            QMessageBox.warning(self, "添加失败", str(exc))

    def _on_toggle_service_used(self) -> None:
        sel = self.dcm_services_table.selectionModel().selectedRows()
        if not sel:
            return
        svc = self._services[sel[0].row()]
        try:
            if self.service.update_dcm_service(svc.short_name, used=not svc.used):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "修改受限", str(exc))

    def _on_session_sel(self) -> None:
        sel = self.sessions_table.selectionModel().selectedRows()
        if not sel:
            self.btn_sess_apply.setEnabled(False)
            return
        s = self._sessions[sel[0].row()]
        self.btn_sess_apply.setEnabled(True)
        self.p2_spin.setValue(s.p2_server_max or 0.05)
        self.p2s_spin.setValue(s.p2_star_server_max or 5.0)

    def _on_apply_session(self) -> None:
        sel = self.sessions_table.selectionModel().selectedRows()
        if not sel:
            return
        s = self._sessions[sel[0].row()]
        try:
            if self.service.update_dcm_session(
                s.short_name, p2_max=self.p2_spin.value(), p2_star_max=self.p2s_spin.value()
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "修改受限", str(exc))

    def _on_add_session(self) -> None:
        dlg = QDialog(self)
        dlg.setWindowTitle("新增 Dcm 会话")
        form = QFormLayout(dlg)
        name_ed = QLineEdit("DcmDspSessionRow_Programming")
        lvl_spin = QSpinBox()
        lvl_spin.setRange(1, 127)
        lvl_spin.setValue(2)
        p2_sp = QDoubleSpinBox()
        p2_sp.setRange(0.001, 10.0)
        p2_sp.setValue(0.05)
        p2s_sp = QDoubleSpinBox()
        p2s_sp.setRange(0.01, 60.0)
        p2s_sp.setValue(5.0)
        form.addRow("容器名称:", name_ed)
        form.addRow("Session Level:", lvl_spin)
        form.addRow("P2ServerMax(s):", p2_sp)
        form.addRow("P2*ServerMax(s):", p2s_sp)
        btns = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        btns.accepted.connect(dlg.accept)
        btns.rejected.connect(dlg.reject)
        form.addRow(btns)
        if dlg.exec() != QDialog.Accepted:
            return
        try:
            self.service.add_dcm_session(
                name_ed.text().strip(), lvl_spin.value(), p2_max=p2_sp.value(), p2_star_max=p2s_sp.value()
            )
            self.reload()
            self.config_changed.emit()
        except (PreLockedError, ValueError, RuntimeError) as exc:
            QMessageBox.warning(self, "新增失败", str(exc))


# ----------------------------------------------------------------------
# Tab 5: Det, CDD & Platform Services
# ----------------------------------------------------------------------


class DetCddTab(QWidget):
    """Manage Det settings, cross-module DevErrorDetect matrix, and CDD/platform extensions."""

    config_changed = Signal()
    navigate_requested = Signal(str)

    def __init__(self, service: SystemServicesWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._det_rows: List[ModuleDetFlagRow] = []
        self._cdd_rows: List[CddPlatformModuleRow] = []

        root = QVBoxLayout(self)

        # DetGeneral bar
        det_box = QGroupBox("Det (Development Error Tracer) 全局开关与缓存")
        dl = QHBoxLayout(det_box)
        self.det_enable_cb = QCheckBox("DetEnableDet")
        self.det_ver_cb = QCheckBox("VersionInfoApi")
        self.det_dbg_cb = QCheckBox("ExtDebugSupport")
        self.det_log_spin = QSpinBox()
        self.det_log_spin.setRange(0, 65535)
        self.btn_apply_det_gen = QPushButton("应用 Det 参数")
        self.btn_apply_det_gen.clicked.connect(self._on_apply_det_gen)
        dl.addWidget(self.det_enable_cb)
        dl.addWidget(self.det_ver_cb)
        dl.addWidget(self.det_dbg_cb)
        dl.addWidget(QLabel("LogBufferSize:"))
        dl.addWidget(self.det_log_spin)
        dl.addWidget(self.btn_apply_det_gen)
        dl.addStretch()
        root.addWidget(det_box)

        split = QSplitter(Qt.Horizontal)

        # Left: Cross-module DET matrix
        m_box = QGroupBox("全模块 DevErrorDetect 状态矩阵")
        ml = QVBoxLayout(m_box)
        mbar = QHBoxLayout()
        self.btn_det_all_on = QPushButton("全部开启 DET")
        self.btn_det_all_off = QPushButton("全部关闭 DET")
        self.btn_toggle_det_row = QPushButton("切换选中开关")
        self.btn_det_all_on.clicked.connect(lambda: self._on_batch_det(True))
        self.btn_det_all_off.clicked.connect(lambda: self._on_batch_det(False))
        self.btn_toggle_det_row.clicked.connect(self._on_toggle_selected_det)
        mbar.addWidget(self.btn_det_all_on)
        mbar.addWidget(self.btn_det_all_off)
        mbar.addWidget(self.btn_toggle_det_row)
        mbar.addStretch()
        ml.addLayout(mbar)

        self.det_modules_table = QTableWidget(0, 4)
        self.det_modules_table.setHorizontalHeaderLabels(["模块", "参数名", "当前状态", "锁状态"])
        _configure_table(self.det_modules_table)
        ml.addWidget(self.det_modules_table)
        split.addWidget(m_box)

        # Right: CDD & Platform Services
        c_box = QGroupBox("CDD 与平台服务扩展模块 (vBRS / vBaseEnv / vSet / VX1000 / Crc / CDD)")
        cl = QVBoxLayout(c_box)
        cbar = QHBoxLayout()
        self.btn_reg_ecum = QPushButton("注册选中模块到 EcuM InitListOne")
        self.btn_locate_cdd = QPushButton("在基础编辑器中定位")
        self.btn_reg_ecum.clicked.connect(self._on_reg_ecum)
        self.btn_locate_cdd.clicked.connect(self._on_locate_cdd)
        cbar.addWidget(self.btn_reg_ecum)
        cbar.addWidget(self.btn_locate_cdd)
        cbar.addStretch()
        cl.addLayout(cbar)

        self.cdd_table = QTableWidget(0, 7)
        self.cdd_table.setHorizontalHeaderLabels([
            "模块",
            "分类",
            "配置变体",
            "容器数",
            "EcuM Init",
            "Rte BSW / PduR",
            "摘要",
        ])
        _configure_table(self.cdd_table)
        self.cdd_table.itemSelectionChanged.connect(self._on_cdd_sel)
        cl.addWidget(self.cdd_table)
        split.addWidget(c_box)

        root.addWidget(split, 1)
        self.reload()

    def reload(self) -> None:
        info = self.service.get_det_info()
        self.btn_apply_det_gen.setEnabled(info.loaded)
        self.det_enable_cb.setEnabled(info.loaded)
        self.det_ver_cb.setEnabled(info.loaded)
        self.det_dbg_cb.setEnabled(info.loaded)
        self.det_log_spin.setEnabled(info.loaded)
        self.det_enable_cb.setChecked(info.enable_det)
        self.det_ver_cb.setChecked(info.version_info_api)
        self.det_dbg_cb.setChecked(info.ext_debug_support)
        self.det_log_spin.setValue(info.log_buffer_size or 0)

        self._det_rows = self.service.list_module_det_flags()
        self.det_modules_table.setRowCount(len(self._det_rows))
        for i, r in enumerate(self._det_rows):
            self.det_modules_table.setItem(i, 0, _ro_item(r.module_name, bold=True))
            self.det_modules_table.setItem(i, 1, _ro_item(r.param_name))
            self.det_modules_table.setItem(
                i, 2, _ro_item("Enabled" if r.enabled else "Disabled", color=_OK_COLOR if r.enabled else _MUTED_COLOR)
            )
            self.det_modules_table.setItem(i, 3, _ro_item("🔒 PreLocked" if r.locked else "可编辑"))

        self._cdd_rows = self.service.list_cdd_and_platform_modules()
        self.cdd_table.setRowCount(len(self._cdd_rows))
        for i, r in enumerate(self._cdd_rows):
            links = []
            if r.in_rte_bsw:
                links.append("Rte")
            if r.in_pdur:
                links.append("PduR")
            self.cdd_table.setItem(i, 0, _ro_item(r.module_name, bold=True))
            self.cdd_table.setItem(i, 1, _ro_item(r.kind))
            self.cdd_table.setItem(i, 2, _ro_item(r.config_variant or "-"))
            self.cdd_table.setItem(i, 3, _ro_item(str(r.container_count)))
            self.cdd_table.setItem(i, 4, _ro_item("✓ 已注册" if r.in_ecum_init else "-", color=_OK_COLOR if r.in_ecum_init else None))
            self.cdd_table.setItem(i, 5, _ro_item(", ".join(links) or "-"))
            self.cdd_table.setItem(i, 6, _ro_item(r.summary or "-"))
        self._on_cdd_sel()

    def _on_apply_det_gen(self) -> None:
        try:
            if self.service.update_det_general(
                enable_det=self.det_enable_cb.isChecked(),
                version_info_api=self.det_ver_cb.isChecked(),
                ext_debug_support=self.det_dbg_cb.isChecked(),
                log_buffer_size=self.det_log_spin.value(),
            ):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "Det 修改受限", str(exc))

    def _on_batch_det(self, enabled: bool) -> None:
        if self.service.set_all_module_det_flags(enabled) > 0:
            self.reload()
            self.config_changed.emit()

    def _on_toggle_selected_det(self) -> None:
        sel = self.det_modules_table.selectionModel().selectedRows()
        if not sel:
            return
        row = self._det_rows[sel[0].row()]
        try:
            if self.service.set_module_det_flag(row.module_name, not row.enabled):
                self.reload()
                self.config_changed.emit()
        except PreLockedError as exc:
            QMessageBox.warning(self, "修改受限", str(exc))

    def _selected_cdd(self) -> Optional[CddPlatformModuleRow]:
        sel = self.cdd_table.selectionModel().selectedRows()
        if not sel:
            return None
        return self._cdd_rows[sel[0].row()] if 0 <= sel[0].row() < len(self._cdd_rows) else None

    def _on_cdd_sel(self) -> None:
        row = self._selected_cdd()
        has = row is not None
        self.btn_reg_ecum.setEnabled(bool(row and not row.in_ecum_init))
        self.btn_locate_cdd.setEnabled(bool(row and row.first_container_path))

    def _on_reg_ecum(self) -> None:
        row = self._selected_cdd()
        if not row:
            return
        try:
            self.service.add_ecum_init_item(
                "EcuMDriverInitListOne",
                f"{row.module_name}_Init",
                row.module_name,
                service_name=f"{row.module_name}_Init",
                header=f"{row.module_name}.h",
            )
            self.reload()
            self.config_changed.emit()
        except (PreLockedError, ValueError, RuntimeError) as exc:
            QMessageBox.warning(self, "注册失败", str(exc))

    def _on_locate_cdd(self) -> None:
        row = self._selected_cdd()
        if row and row.first_container_path:
            self.navigate_requested.emit(row.first_container_path)
