"""Five tab widgets for the Communication Configuration Workbench."""

from pathlib import Path
from typing import Dict, List, Optional

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QBrush, QColor, QFont
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QDoubleSpinBox,
    QFileDialog,
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
    QVBoxLayout,
    QWidget,
)

from ...core.communication import (
    CAN_ID_TYPES,
    COM_ENDIANNESS,
    COM_SIGNAL_TYPES,
    COM_TRANSFER_PROPS,
    COM_TX_MODES,
    CommChannelRow,
    CommMessageRow,
    CommSignalRow,
    CommunicationWorkbenchService,
    DbcSyncPlan,
    PduRRoutingRow,
    apply_dbc_sync,
    plan_dbc_sync,
)
from ...core.config_manager import PreLockedError
from ...core.importers.dbc_importer import DbcParser

_OK_COLOR = QColor("#1b7f37")
_WARN_COLOR = QColor("#a65e00")
_ERROR_COLOR = QColor("#b00020")
_MUTED_COLOR = QColor("#57606a")
_OVERLAP_BG = QColor("#ffcdd2")
_OOB_BG = QColor("#ffe0b2")
_EMPTY_BG = QColor("#fafafa")

_SIG_PALETTE = (
    QColor("#e3f2fd"),
    QColor("#e8f5e9"),
    QColor("#fff3e0"),
    QColor("#f3e5f5"),
    QColor("#e0f7fa"),
    QColor("#fce4ec"),
    QColor("#f1f8e9"),
    QColor("#ede7f6"),
)


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
# Tab 1: Channels & Physical Topology
# ----------------------------------------------------------------------


class ChannelsTab(QWidget):
    """Display ComM <-> CanSM <-> CanIf <-> CanController <-> CanTrcv channel topology."""

    navigate_requested = Signal(str)

    def __init__(self, service: CommunicationWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._rows: List[CommChannelRow] = []

        layout = QVBoxLayout(self)
        top_bar = QHBoxLayout()
        info = QLabel("展示当前工程的物理通道、总线类型、波特率与收发器关联链路。")
        info.setStyleSheet("color: #57606a;")
        top_bar.addWidget(info, 1)

        self.locate_btn = QPushButton("在基础编辑器中定位")
        self.locate_btn.setEnabled(False)
        self.locate_btn.clicked.connect(self._on_locate)
        top_bar.addWidget(self.locate_btn)
        layout.addLayout(top_bar)

        self.table = QTableWidget(0, 10)
        self.table.setHorizontalHeaderLabels([
            "通道名称",
            "总线类型",
            "Channel ID",
            "NM 策略",
            "CanSM 网络",
            "CanIf 控制器",
            "Can 控制器 (硬件)",
            "波特率 (kbps)",
            "收发模式 (Rx/Tx)",
            "CanTrcv / 链路状态",
        ])
        _configure_table(self.table)
        self.table.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.table.horizontalHeader().setSectionResizeMode(6, QHeaderView.ResizeToContents)
        self.table.itemSelectionChanged.connect(self._on_sel_changed)
        layout.addWidget(self.table)

        self.reload()

    def reload(self) -> None:
        self._rows = self.service.list_channel_rows()
        self.table.setRowCount(len(self._rows))
        for r_idx, row in enumerate(self._rows):
            baud_txt = "-"
            if row.baudrate_kbps is not None:
                baud_txt = f"{row.baudrate_kbps:g}"
                if row.fd_baudrate_kbps is not None:
                    baud_txt += f" / FD {row.fd_baudrate_kbps:g}"
            proc_txt = f"{row.rx_processing or '-'} / {row.tx_processing or '-'}"
            trcv_txt = row.trcv_channel_name or "-"
            if row.trcv_init_state:
                trcv_txt += f" ({row.trcv_init_state})"
            if row.has_broken_link:
                trcv_txt = f"⚠️ 链路不完整 | {trcv_txt}"

            items = [
                _ro_item(row.channel_name, bold=True),
                _ro_item(row.bus_type),
                _ro_item("-" if row.comm_channel_id is None else str(row.comm_channel_id)),
                _ro_item(row.nm_variant),
                _ro_item(row.cansm_network_name or "-"),
                _ro_item(row.canif_ctrl_name or "-"),
                _ro_item(
                    f"{row.can_controller_name or '-'} ({row.hardware_channel or '-'})"
                    if row.can_controller_name
                    else "-"
                ),
                _ro_item(baud_txt),
                _ro_item(proc_txt),
                _ro_item(trcv_txt, color=_WARN_COLOR if row.has_broken_link else _OK_COLOR),
            ]
            items[0].setData(Qt.UserRole, row.primary_container_path)
            for c_idx, it in enumerate(items):
                self.table.setItem(r_idx, c_idx, it)
        self._on_sel_changed()

    def _on_sel_changed(self) -> None:
        rows = self.table.selectionModel().selectedRows()
        if not rows:
            self.locate_btn.setEnabled(False)
            return
        idx = rows[0].row()
        path = self._rows[idx].primary_container_path if 0 <= idx < len(self._rows) else ""
        self.locate_btn.setEnabled(bool(path))

    def _on_locate(self) -> None:
        rows = self.table.selectionModel().selectedRows()
        if not rows:
            return
        idx = rows[0].row()
        if 0 <= idx < len(self._rows) and self._rows[idx].primary_container_path:
            self.navigate_requested.emit(self._rows[idx].primary_container_path)


# ----------------------------------------------------------------------
# Tab 2: End-to-End Messages & Inline Editor
# ----------------------------------------------------------------------


class MessagesTab(QWidget):
    """Display TX/RX CAN messages end-to-end with inline CAN ID / DLC / period editing."""

    config_changed = Signal()
    navigate_requested = Signal(str)
    inspect_signals_requested = Signal(str)

    def __init__(self, service: CommunicationWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._all_rows: List[CommMessageRow] = []
        self._visible_rows: List[CommMessageRow] = []
        self._loading = False

        layout = QVBoxLayout(self)

        # Filter bar
        flt = QHBoxLayout()
        self.search_edit = QLineEdit()
        self.search_edit.setPlaceholderText("搜索报文名、CAN ID（如 0x224）或 PDU...")
        self.search_edit.textChanged.connect(self._apply_filters)
        flt.addWidget(self.search_edit, 1)

        self.direction_combo = QComboBox()
        self.direction_combo.addItem("全部方向", "")
        self.direction_combo.addItem("TX (发送)", "TX")
        self.direction_combo.addItem("RX (接收)", "RX")
        self.direction_combo.currentIndexChanged.connect(self._apply_filters)
        flt.addWidget(self.direction_combo)

        self.category_combo = QComboBox()
        self.category_combo.addItem("全部分类", "")
        self.category_combo.addItem("COM 信号报文", "COM")
        self.category_combo.addItem("DIAG_TP 诊断", "DIAG_TP")
        self.category_combo.addItem("ORPHAN 断链/未映射", "ORPHAN")
        self.category_combo.currentIndexChanged.connect(self._apply_filters)
        flt.addWidget(self.category_combo)

        self.only_issues_check = QCheckBox("仅显示异常")
        self.only_issues_check.toggled.connect(self._apply_filters)
        flt.addWidget(self.only_issues_check)

        self.recompute_btn = QPushButton("一键重排 HandleId")
        self.recompute_btn.clicked.connect(self._on_recompute_ids)
        flt.addWidget(self.recompute_btn)

        self.signals_btn = QPushButton("查看信号位图")
        self.signals_btn.setEnabled(False)
        self.signals_btn.clicked.connect(self._on_open_signals)
        flt.addWidget(self.signals_btn)

        self.locate_btn = QPushButton("在基础编辑器中定位")
        self.locate_btn.setEnabled(False)
        self.locate_btn.clicked.connect(self._on_locate)
        flt.addWidget(self.locate_btn)

        layout.addLayout(flt)

        # Messages table
        self.table = QTableWidget(0, 11)
        self.table.setHorizontalHeaderLabels([
            "方向",
            "分类",
            "报文名称",
            "CAN ID",
            "帧类型",
            "CanIf DLC",
            "EcuC PDU 长度",
            "发送模式",
            "周期 (ms)",
            "所属通道",
            "信号数 / 链路状态",
        ])
        _configure_table(self.table)
        self.table.horizontalHeader().setSectionResizeMode(2, QHeaderView.Stretch)
        self.table.itemSelectionChanged.connect(self._on_selection_changed)
        self.table.cellDoubleClicked.connect(lambda _r, _c: self._on_open_signals())
        layout.addWidget(self.table, 1)

        # Inline edit bar
        edit_box = QGroupBox("选中报文快速编辑（同步更新 CanIf / EcuC / Com）")
        eb_layout = QHBoxLayout(edit_box)

        eb_layout.addWidget(QLabel("CAN ID:"))
        self.edit_can_id = QLineEdit()
        self.edit_can_id.setFixedWidth(96)
        self.edit_can_id.setPlaceholderText("0x123")
        eb_layout.addWidget(self.edit_can_id)

        eb_layout.addWidget(QLabel("帧类型:"))
        self.combo_id_type = QComboBox()
        for t in CAN_ID_TYPES:
            self.combo_id_type.addItem(t, t)
        eb_layout.addWidget(self.combo_id_type)

        eb_layout.addWidget(QLabel("DLC:"))
        self.spin_dlc = QSpinBox()
        self.spin_dlc.setRange(0, 64)
        eb_layout.addWidget(self.spin_dlc)

        eb_layout.addWidget(QLabel("发送模式:"))
        self.combo_tx_mode = QComboBox()
        self.combo_tx_mode.addItem("(不修改)", "")
        for m in COM_TX_MODES:
            self.combo_tx_mode.addItem(m, m)
        eb_layout.addWidget(self.combo_tx_mode)

        eb_layout.addWidget(QLabel("周期(ms):"))
        self.spin_cycle_ms = QDoubleSpinBox()
        self.spin_cycle_ms.setRange(0.0, 600000.0)
        self.spin_cycle_ms.setDecimals(2)
        self.spin_cycle_ms.setSingleStep(10.0)
        eb_layout.addWidget(self.spin_cycle_ms)

        self.apply_btn = QPushButton("应用报文修改")
        self.apply_btn.setEnabled(False)
        self.apply_btn.clicked.connect(self._on_apply_edit)
        eb_layout.addWidget(self.apply_btn)
        eb_layout.addStretch()

        layout.addWidget(edit_box)
        self.reload()

    def reload(self) -> None:
        self._all_rows = self.service.list_message_rows()
        self._apply_filters()

    def _row_has_issue(self, r: CommMessageRow) -> bool:
        return bool(
            r.has_length_mismatch
            or r.has_broken_chain
            or (
                r.direction == "TX"
                and r.com_ipdu_name
                and r.tx_mode.upper() in ("PERIODIC", "MIXED")
                and (r.cycle_time_ms is None or r.cycle_time_ms <= 0)
            )
        )

    def _apply_filters(self) -> None:
        q = self.search_edit.text().strip().lower()
        dir_flt = self.direction_combo.currentData() or ""
        cat_flt = self.category_combo.currentData() or ""
        only_issues = self.only_issues_check.isChecked()

        self._visible_rows = []
        for r in self._all_rows:
            if dir_flt and r.direction != dir_flt:
                continue
            if cat_flt and r.category != cat_flt:
                continue
            if only_issues and not self._row_has_issue(r):
                continue
            if q:
                hay = f"{r.name} {r.can_id_hex} {r.canif_pdu_name} {r.com_ipdu_name} {r.pdur_path_name}".lower()
                if q not in hay:
                    continue
            self._visible_rows.append(r)

        self._loading = True
        try:
            self.table.setRowCount(len(self._visible_rows))
            for idx, r in enumerate(self._visible_rows):
                if r.category == "DIAG_TP":
                    status_txt = f"诊断 TP ({r.cantp_nsdu_name or 'CanTp'})"
                    st_color = _MUTED_COLOR
                elif r.has_length_mismatch:
                    status_txt = f"❌ 长度不一致 ({r.signal_count} 信号)"
                    st_color = _ERROR_COLOR
                elif r.has_broken_chain:
                    status_txt = f"⚠️ 链路不完整 ({r.signal_count} 信号)"
                    st_color = _WARN_COLOR
                else:
                    status_txt = f"✅ {r.signal_count} 信号 | 链路完整"
                    st_color = _OK_COLOR

                cycle_txt = f"{r.cycle_time_ms:g}" if r.cycle_time_ms is not None else "-"
                items = [
                    _ro_item(r.direction, bold=True),
                    _ro_item(r.category),
                    _ro_item(r.name),
                    _ro_item(r.can_id_hex, bold=True),
                    _ro_item(r.can_id_type if r.canif_pdu_name else "-"),
                    _ro_item("-" if r.canif_dlc is None else str(r.canif_dlc)),
                    _ro_item("-" if r.ecuc_pdu_length is None else str(r.ecuc_pdu_length)),
                    _ro_item(r.tx_mode or "-"),
                    _ro_item(cycle_txt),
                    _ro_item(r.channel_name or "-"),
                    _ro_item(status_txt, color=st_color),
                ]
                for c_idx, it in enumerate(items):
                    self.table.setItem(idx, c_idx, it)
        finally:
            self._loading = False
        self._on_selection_changed()

    def _current_row(self) -> Optional[CommMessageRow]:
        sel = self.table.selectionModel().selectedRows()
        if not sel:
            return None
        idx = sel[0].row()
        if 0 <= idx < len(self._visible_rows):
            return self._visible_rows[idx]
        return None

    def _on_selection_changed(self) -> None:
        if self._loading:
            return
        row = self._current_row()
        has_row = row is not None
        self.apply_btn.setEnabled(has_row and bool(row.canif_pdu_name or row.com_ipdu_name))
        self.locate_btn.setEnabled(has_row and bool(row.primary_container_path))
        self.signals_btn.setEnabled(has_row and bool(row.com_ipdu_name))
        if row is None:
            return

        has_canif = bool(row.canif_pdu_name)
        self.edit_can_id.setEnabled(has_canif)
        self.combo_id_type.setEnabled(has_canif)
        self.spin_dlc.setEnabled(has_canif or bool(row.ecuc_upper_pdu_name))
        self.edit_can_id.setText(row.can_id_hex if row.can_id is not None else "")
        it_idx = self.combo_id_type.findData(row.can_id_type)
        if it_idx >= 0:
            self.combo_id_type.setCurrentIndex(it_idx)
        dlc_val = row.canif_dlc if row.canif_dlc is not None else (row.ecuc_pdu_length or 8)
        self.spin_dlc.setValue(int(dlc_val))

        is_tx_com = bool(row.com_ipdu_name and row.direction == "TX")
        self.combo_tx_mode.setEnabled(is_tx_com)
        self.spin_cycle_ms.setEnabled(is_tx_com)
        tm_idx = self.combo_tx_mode.findData(row.tx_mode)
        self.combo_tx_mode.setCurrentIndex(tm_idx if tm_idx >= 0 else 0)
        self.spin_cycle_ms.setValue(float(row.cycle_time_ms or 0.0))

    def _on_apply_edit(self) -> None:
        row = self._current_row()
        if row is None:
            return
        can_id_val: Optional[int] = None
        can_id_type_val: Optional[str] = None
        if row.canif_pdu_name:
            raw_id = self.edit_can_id.text().strip()
            if raw_id and raw_id != "-":
                try:
                    can_id_val = int(raw_id, 0)
                except ValueError:
                    QMessageBox.warning(self, "输入无效", f"无效的 CAN ID: {raw_id}")
                    return
            can_id_type_val = self.combo_id_type.currentData()

        tx_mode_val = self.combo_tx_mode.currentData() or None
        cycle_val = self.spin_cycle_ms.value() if (row.com_ipdu_name and row.direction == "TX") else None

        try:
            self.service.update_message_properties(
                row.canif_pdu_name or None,
                row.com_ipdu_name or None,
                can_id=can_id_val,
                can_id_type=can_id_type_val,
                dlc=self.spin_dlc.value(),
                tx_mode=tx_mode_val,
                cycle_time_ms=cycle_val,
            )
        except (PreLockedError, ValueError) as exc:
            QMessageBox.warning(self, "无法修改报文", str(exc))
            return

        self.reload()
        self.config_changed.emit()

    def _on_recompute_ids(self) -> None:
        counts = self.service.recompute_handle_ids()
        total = sum(counts.values())
        self.reload()
        if total > 0:
            self.config_changed.emit()
        QMessageBox.information(self, "重排 HandleId", f"已重排并更新 {total} 个句柄 ID（{counts}）。")

    def _on_locate(self) -> None:
        row = self._current_row()
        if row and row.primary_container_path:
            self.navigate_requested.emit(row.primary_container_path)

    def _on_open_signals(self) -> None:
        row = self._current_row()
        if row and row.com_ipdu_name:
            self.inspect_signals_requested.emit(row.com_ipdu_name)


# ----------------------------------------------------------------------
# Tab 3: Signal Matrix & 8xN Visual Bit Layout Grid
# ----------------------------------------------------------------------


class SignalsTab(QWidget):
    """ComSignal editor paired with an 8xN Motorola/Intel bit occupancy visualization."""

    config_changed = Signal()
    navigate_requested = Signal(str)

    def __init__(self, service: CommunicationWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._all_rows: List[CommSignalRow] = []
        self._visible_rows: List[CommSignalRow] = []
        self._loading = False

        layout = QVBoxLayout(self)

        # Filter bar
        flt = QHBoxLayout()
        flt.addWidget(QLabel("所属 ComIPdu:"))
        self.ipdu_combo = QComboBox()
        self.ipdu_combo.currentIndexChanged.connect(self._apply_filters)
        flt.addWidget(self.ipdu_combo)

        self.search_edit = QLineEdit()
        self.search_edit.setPlaceholderText("搜索信号名...")
        self.search_edit.textChanged.connect(self._apply_filters)
        flt.addWidget(self.search_edit, 1)

        self.only_issues_check = QCheckBox("仅显示位域冲突")
        self.only_issues_check.toggled.connect(self._apply_filters)
        flt.addWidget(self.only_issues_check)

        self.locate_btn = QPushButton("在基础编辑器中定位")
        self.locate_btn.setEnabled(False)
        self.locate_btn.clicked.connect(self._on_locate)
        flt.addWidget(self.locate_btn)
        layout.addLayout(flt)

        vsplit = QSplitter(Qt.Vertical)

        # Signal matrix table
        self.table = QTableWidget(0, 10)
        self.table.setHorizontalHeaderLabels([
            "信号名称",
            "所属 ComIPdu",
            "方向",
            "起始位",
            "位长",
            "字节序",
            "数据类型",
            "初值",
            "发送属性 / 超时",
            "位域状态",
        ])
        _configure_table(self.table)
        self.table.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        self.table.itemSelectionChanged.connect(self._on_signal_selected)
        vsplit.addWidget(self.table)

        # Bottom area: 8xN Bit Grid + inline editor
        bottom = QSplitter(Qt.Horizontal)

        grid_box = QGroupBox("帧位域布局图（Byte × Bit 7..0）")
        gl = QVBoxLayout(grid_box)
        self.grid_info_label = QLabel("请选择或筛选 ComIPdu 查看位域占用")
        self.grid_info_label.setStyleSheet("color: #57606a; font-size: 11px;")
        gl.addWidget(self.grid_info_label)

        self.bit_grid_table = QTableWidget(8, 8)
        self.bit_grid_table.setHorizontalHeaderLabels([f"Bit {b}" for b in range(7, -1, -1)])
        self.bit_grid_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.bit_grid_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        gl.addWidget(self.bit_grid_table)
        bottom.addWidget(grid_box)

        edit_box = QGroupBox("选中信号属性编辑")
        el = QVBoxLayout(edit_box)
        form = QGridLayout()

        self.spin_bit_pos = QSpinBox()
        self.spin_bit_pos.setRange(0, 511)
        self.spin_bit_size = QSpinBox()
        self.spin_bit_size.setRange(1, 64)

        self.combo_endian = QComboBox()
        for e in COM_ENDIANNESS:
            self.combo_endian.addItem(e, e)

        self.combo_sig_type = QComboBox()
        for st in COM_SIGNAL_TYPES:
            self.combo_sig_type.addItem(st, st)

        self.edit_init_val = QLineEdit("0")

        self.combo_transfer = QComboBox()
        for tp in COM_TRANSFER_PROPS:
            self.combo_transfer.addItem(tp, tp)

        self.spin_timeout = QDoubleSpinBox()
        self.spin_timeout.setRange(0.0, 3600.0)
        self.spin_timeout.setDecimals(3)
        self.spin_timeout.setSingleStep(0.01)

        form.addWidget(QLabel("起始位 (ComBitPosition):"), 0, 0)
        form.addWidget(self.spin_bit_pos, 0, 1)
        form.addWidget(QLabel("位长 (ComBitSize):"), 1, 0)
        form.addWidget(self.spin_bit_size, 1, 1)
        form.addWidget(QLabel("字节序:"), 2, 0)
        form.addWidget(self.combo_endian, 2, 1)
        form.addWidget(QLabel("类型:"), 3, 0)
        form.addWidget(self.combo_sig_type, 3, 1)
        form.addWidget(QLabel("初始值:"), 4, 0)
        form.addWidget(self.edit_init_val, 4, 1)
        form.addWidget(QLabel("发送属性:"), 5, 0)
        form.addWidget(self.combo_transfer, 5, 1)
        form.addWidget(QLabel("超时 (s):"), 6, 0)
        form.addWidget(self.spin_timeout, 6, 1)
        el.addLayout(form)

        self.apply_sig_btn = QPushButton("应用信号修改")
        self.apply_sig_btn.setEnabled(False)
        self.apply_sig_btn.clicked.connect(self._on_apply_signal)
        el.addWidget(self.apply_sig_btn)
        el.addStretch()
        bottom.addWidget(edit_box)
        bottom.setStretchFactor(0, 3)
        bottom.setStretchFactor(1, 1)

        vsplit.addWidget(bottom)
        vsplit.setStretchFactor(0, 2)
        vsplit.setStretchFactor(1, 2)
        layout.addWidget(vsplit)

        self.reload()

    def focus_ipdu(self, ipdu_name: str) -> None:
        self.search_edit.clear()
        self.only_issues_check.setChecked(False)
        idx = self.ipdu_combo.findData(ipdu_name)
        if idx >= 0:
            self.ipdu_combo.setCurrentIndex(idx)
        self._render_bit_grid(ipdu_name)

    def reload(self) -> None:
        self._all_rows = self.service.list_signal_rows()
        prev_ipdu = self.ipdu_combo.currentData() or ""
        ipdus = sorted({r.ipdu_name for r in self._all_rows if r.ipdu_name})
        self.ipdu_combo.blockSignals(True)
        self.ipdu_combo.clear()
        self.ipdu_combo.addItem("全部报文 (信号总览)", "")
        for ipdu in ipdus:
            self.ipdu_combo.addItem(ipdu, ipdu)
        idx = self.ipdu_combo.findData(prev_ipdu)
        self.ipdu_combo.setCurrentIndex(idx if idx >= 0 else 0)
        self.ipdu_combo.blockSignals(False)
        self._apply_filters()

    def _apply_filters(self) -> None:
        ipdu_flt = self.ipdu_combo.currentData() or ""
        q = self.search_edit.text().strip().lower()
        only_issues = self.only_issues_check.isChecked()

        self._visible_rows = []
        for r in self._all_rows:
            if ipdu_flt and r.ipdu_name != ipdu_flt:
                continue
            if only_issues and not (r.has_overlap or r.out_of_bounds):
                continue
            if q and q not in r.signal_name.lower() and q not in r.ipdu_name.lower():
                continue
            self._visible_rows.append(r)

        self._loading = True
        try:
            self.table.setRowCount(len(self._visible_rows))
            for idx, r in enumerate(self._visible_rows):
                tp_txt = r.transfer_property
                if r.timeout_sec is not None:
                    tp_txt += f" | T={r.timeout_sec:g}s"
                if r.has_overlap and r.out_of_bounds:
                    st_txt, st_col = "❌ 重叠且越界", _ERROR_COLOR
                elif r.has_overlap:
                    st_txt, st_col = "❌ 位域重叠", _ERROR_COLOR
                elif r.out_of_bounds:
                    st_txt, st_col = "❌ 超出 DLC", _ERROR_COLOR
                else:
                    st_txt, st_col = "✅ 正常", _OK_COLOR

                items = [
                    _ro_item(r.signal_name, bold=True),
                    _ro_item(r.ipdu_name or "-"),
                    _ro_item(r.direction or "-"),
                    _ro_item("-" if r.bit_position is None else str(r.bit_position)),
                    _ro_item("-" if r.bit_size is None else str(r.bit_size)),
                    _ro_item(r.endianness),
                    _ro_item(r.signal_type),
                    _ro_item(r.init_value),
                    _ro_item(tp_txt),
                    _ro_item(st_txt, color=st_col),
                ]
                for c_idx, it in enumerate(items):
                    self.table.setItem(idx, c_idx, it)
        finally:
            self._loading = False

        if ipdu_flt:
            self._render_bit_grid(ipdu_flt)
        elif self._visible_rows and self._visible_rows[0].ipdu_name:
            self._render_bit_grid(self._visible_rows[0].ipdu_name)
        else:
            self._render_bit_grid("")
        self._on_signal_selected()

    def _current_row(self) -> Optional[CommSignalRow]:
        sel = self.table.selectionModel().selectedRows()
        if not sel:
            return None
        idx = sel[0].row()
        if 0 <= idx < len(self._visible_rows):
            return self._visible_rows[idx]
        return None

    def _on_signal_selected(self) -> None:
        if self._loading:
            return
        row = self._current_row()
        self.apply_sig_btn.setEnabled(row is not None)
        self.locate_btn.setEnabled(row is not None and bool(row.container_path))
        if row is None:
            return
        self.spin_bit_pos.setValue(int(row.bit_position or 0))
        self.spin_bit_size.setValue(int(max(row.bit_size or 1, 1)))
        e_idx = self.combo_endian.findData(row.endianness)
        self.combo_endian.setCurrentIndex(e_idx if e_idx >= 0 else 0)
        st_idx = self.combo_sig_type.findData(row.signal_type)
        self.combo_sig_type.setCurrentIndex(st_idx if st_idx >= 0 else 0)
        self.edit_init_val.setText(row.init_value)
        tp_idx = self.combo_transfer.findData(row.transfer_property)
        self.combo_transfer.setCurrentIndex(tp_idx if tp_idx >= 0 else 0)
        self.spin_timeout.setValue(float(row.timeout_sec or 0.0))
        if row.ipdu_name:
            self._render_bit_grid(row.ipdu_name, highlight_signal=row.signal_name)

    def _render_bit_grid(self, ipdu_name: str, *, highlight_signal: Optional[str] = None) -> None:
        if not ipdu_name:
            self.grid_info_label.setText("未选中 ComIPdu")
            self.bit_grid_table.setRowCount(0)
            return

        byte_len, grid, overlaps, oob = self.service.get_ipdu_bit_grid(ipdu_name)
        self.grid_info_label.setText(
            f"ComIPdu: {ipdu_name}  |  显示长度: {byte_len} Byte  |  "
            f"重叠信号: {len(overlaps)}  |  越界信号: {len(oob)}"
        )
        self.bit_grid_table.setRowCount(byte_len)
        self.bit_grid_table.setVerticalHeaderLabels([f"Byte {b}" for b in range(byte_len)])

        sig_colors: Dict[str, QColor] = {}
        for occupants in grid.values():
            for s in occupants:
                if s not in sig_colors:
                    sig_colors[s] = _SIG_PALETTE[len(sig_colors) % len(_SIG_PALETTE)]

        for byte_idx in range(byte_len):
            for bit_idx in range(7, -1, -1):
                col = 7 - bit_idx
                occupants = grid.get((byte_idx, bit_idx), [])
                if not occupants:
                    item = _ro_item(".", color=_MUTED_COLOR)
                    item.setBackground(_EMPTY_BG)
                elif len(occupants) > 1:
                    short_names = [s.split("_o", 1)[0][:10] for s in occupants]
                    item = _ro_item("⚠️ " + "/".join(short_names), color=_ERROR_COLOR, bold=True)
                    item.setBackground(_OVERLAP_BG)
                    item.setToolTip(f"Byte {byte_idx} Bit {bit_idx} 重叠: {', '.join(occupants)}")
                else:
                    sname = occupants[0]
                    short_s = sname.split("_o", 1)[0][:12]
                    is_hl = bool(highlight_signal and sname == highlight_signal)
                    is_oob = sname in oob
                    item = _ro_item(
                        short_s,
                        color=_ERROR_COLOR if is_oob else QColor("#1f2328"),
                        bold=is_hl or is_oob,
                    )
                    item.setBackground(_OOB_BG if is_oob else sig_colors[sname])
                    item.setToolTip(f"Byte {byte_idx} Bit {bit_idx}: {sname}")
                item.setTextAlignment(Qt.AlignCenter)
                self.bit_grid_table.setItem(byte_idx, col, item)

    def _on_apply_signal(self) -> None:
        row = self._current_row()
        if row is None:
            return
        try:
            self.service.update_signal_properties(
                row.signal_name,
                bit_position=self.spin_bit_pos.value(),
                bit_size=self.spin_bit_size.value(),
                endianness=self.combo_endian.currentData(),
                signal_type=self.combo_sig_type.currentData(),
                init_value=self.edit_init_val.text().strip(),
                transfer_property=self.combo_transfer.currentData(),
                timeout_sec=self.spin_timeout.value(),
            )
        except (PreLockedError, ValueError) as exc:
            QMessageBox.warning(self, "无法修改信号", str(exc))
            return

        sel_sig = row.signal_name
        sel_ipdu = row.ipdu_name
        self.reload()
        if sel_ipdu:
            self._render_bit_grid(sel_ipdu, highlight_signal=sel_sig)
        self.config_changed.emit()

    def _on_locate(self) -> None:
        row = self._current_row()
        if row and row.container_path:
            self.navigate_requested.emit(row.container_path)


# ----------------------------------------------------------------------
# Tab 4: PduR Routing Matrix
# ----------------------------------------------------------------------


class PduRRoutingTab(QWidget):
    """View, add, update, and remove PduRRoutingPath entries."""

    config_changed = Signal()
    navigate_requested = Signal(str)

    def __init__(self, service: CommunicationWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._all_rows: List[PduRRoutingRow] = []
        self._visible_rows: List[PduRRoutingRow] = []

        layout = QVBoxLayout(self)

        top = QHBoxLayout()
        self.search_edit = QLineEdit()
        self.search_edit.setPlaceholderText("搜索路由名、源/目的模块或 PDU...")
        self.search_edit.textChanged.connect(self._apply_filters)
        top.addWidget(self.search_edit, 1)

        self.remove_btn = QPushButton("删除选中路由")
        self.remove_btn.setEnabled(False)
        self.remove_btn.clicked.connect(self._on_remove)
        top.addWidget(self.remove_btn)

        self.locate_btn = QPushButton("在基础编辑器中定位")
        self.locate_btn.setEnabled(False)
        self.locate_btn.clicked.connect(self._on_locate)
        top.addWidget(self.locate_btn)
        layout.addLayout(top)

        self.table = QTableWidget(0, 9)
        self.table.setHorizontalHeaderLabels([
            "路由路径 (PduRRoutingPath)",
            "通信类型",
            "方向",
            "CAN ID",
            "源模块",
            "源 EcuC PDU",
            "源 HandleId",
            "目的模块",
            "目的 EcuC PDU / 状态",
        ])
        _configure_table(self.table)
        self.table.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        self.table.itemSelectionChanged.connect(self._on_selection_changed)
        layout.addWidget(self.table, 1)

        add_box = QGroupBox("新建 / 调整 PduR 路由路径")
        al = QHBoxLayout(add_box)
        al.addWidget(QLabel("路径名:"))
        self.edit_path_name = QLineEdit()
        self.edit_path_name.setPlaceholderText("NewMsg_Tx")
        al.addWidget(self.edit_path_name)

        al.addWidget(QLabel("源模块:"))
        self.combo_src_mod = QComboBox()
        for m in ("Com", "CanIf", "CanTp", "Dcm"):
            self.combo_src_mod.addItem(m, m)
        al.addWidget(self.combo_src_mod)

        al.addWidget(QLabel("源PDU:"))
        self.edit_src_pdu = QLineEdit()
        self.edit_src_pdu.setPlaceholderText("UpperOrLower_Pdu")
        al.addWidget(self.edit_src_pdu)

        al.addWidget(QLabel("目的模块:"))
        self.combo_dest_mod = QComboBox()
        for m in ("CanIf", "Com", "CanTp", "Dcm"):
            self.combo_dest_mod.addItem(m, m)
        al.addWidget(self.combo_dest_mod)

        al.addWidget(QLabel("目的PDU:"))
        self.edit_dest_pdu = QLineEdit()
        self.edit_dest_pdu.setPlaceholderText("Dest_Pdu")
        al.addWidget(self.edit_dest_pdu)

        self.add_btn = QPushButton("添加路由")
        self.add_btn.clicked.connect(self._on_add_route)
        al.addWidget(self.add_btn)
        layout.addWidget(add_box)

        self.reload()

    def reload(self) -> None:
        self._all_rows = self.service.list_pdur_routing_rows()
        self._apply_filters()

    def _apply_filters(self) -> None:
        q = self.search_edit.text().strip().lower()
        self._visible_rows = []
        for r in self._all_rows:
            if q:
                hay = f"{r.path_name} {r.src_module} {r.src_pdu_name} {r.dest_module} {r.dest_pdu_name} {r.can_id_hex}".lower()
                if q not in hay:
                    continue
            self._visible_rows.append(r)

        self.table.setRowCount(len(self._visible_rows))
        for idx, r in enumerate(self._visible_rows):
            dest_txt = f"⚠️ 断链 | {r.dest_pdu_name}" if r.has_broken_ref else (r.dest_pdu_name or "-")
            items = [
                _ro_item(r.path_name, bold=True),
                _ro_item(r.comm_type),
                _ro_item(r.direction or "-"),
                _ro_item(r.can_id_hex),
                _ro_item(r.src_module or "-"),
                _ro_item(r.src_pdu_name or "-"),
                _ro_item("-" if r.src_handle_id is None else str(r.src_handle_id)),
                _ro_item(r.dest_module or "-"),
                _ro_item(dest_txt, color=_WARN_COLOR if r.has_broken_ref else _OK_COLOR),
            ]
            for c_idx, it in enumerate(items):
                self.table.setItem(idx, c_idx, it)
        self._on_selection_changed()

    def _current_row(self) -> Optional[PduRRoutingRow]:
        sel = self.table.selectionModel().selectedRows()
        if not sel:
            return None
        idx = sel[0].row()
        if 0 <= idx < len(self._visible_rows):
            return self._visible_rows[idx]
        return None

    def _on_selection_changed(self) -> None:
        row = self._current_row()
        self.remove_btn.setEnabled(row is not None)
        self.locate_btn.setEnabled(row is not None and bool(row.container_path))

    def _on_add_route(self) -> None:
        path_name = self.edit_path_name.text().strip()
        src_pdu = self.edit_src_pdu.text().strip()
        dest_pdu = self.edit_dest_pdu.text().strip()
        if not path_name or not src_pdu or not dest_pdu:
            QMessageBox.warning(self, "参数缺失", "请填写路径名、源 EcuC PDU 和目的 EcuC PDU。")
            return
        src_mod = self.combo_src_mod.currentData()
        dest_mod = self.combo_dest_mod.currentData()
        direction = "RECEIVE" if src_mod == "CanIf" else "TRANSMIT"
        comm_type = (
            "TRANSPORT_PROTOCOL"
            if ("Tp" in str(src_mod) or "Tp" in str(dest_mod))
            else "COMMUNICATION_INTERFACE"
        )
        try:
            self.service.add_pdur_routing_path(
                path_name, src_mod, src_pdu, dest_mod, dest_pdu, comm_type=comm_type, direction=direction
            )
        except (PreLockedError, ValueError) as exc:
            QMessageBox.warning(self, "添加路由失败", str(exc))
            return
        self.reload()
        self.config_changed.emit()

    def _on_remove(self) -> None:
        row = self._current_row()
        if row is None:
            return
        try:
            ok = self.service.remove_pdur_routing_path(row.path_name)
        except PreLockedError as exc:
            QMessageBox.warning(self, "删除受限", str(exc))
            return
        if ok:
            self.reload()
            self.config_changed.emit()

    def _on_locate(self) -> None:
        row = self._current_row()
        if row and row.container_path:
            self.navigate_requested.emit(row.container_path)


# ----------------------------------------------------------------------
# Tab 5: DBC Multi-Module Sync & Derivation
# ----------------------------------------------------------------------


_SYNC_ACTION_LABELS = {
    "create": ("新建", _OK_COLOR),
    "update": ("更新", QColor("#1f5fbf")),
    "unchanged": ("未变化", _MUTED_COLOR),
    "skip": ("跳过", _WARN_COLOR),
}


class DbcSyncTab(QWidget):
    """Select DBC + ECU node, preview multi-module diffs, and derive EcuC/CanIf/PduR/Com."""

    config_changed = Signal()

    def __init__(self, service: CommunicationWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._current_plan: Optional[DbcSyncPlan] = None

        layout = QVBoxLayout(self)

        cfg_box = QGroupBox("DBC 通信矩阵导入与多模块自动派生")
        cl = QVBoxLayout(cfg_box)

        file_row = QHBoxLayout()
        file_row.addWidget(QLabel("DBC 文件:"))
        self.edit_dbc_path = QLineEdit()
        self.edit_dbc_path.setPlaceholderText("选择 .dbc 文件路径...")
        self.edit_dbc_path.editingFinished.connect(self._load_dbc_metadata)
        file_row.addWidget(self.edit_dbc_path, 1)

        self.browse_btn = QPushButton("浏览...")
        self.browse_btn.clicked.connect(self._on_browse_dbc)
        file_row.addWidget(self.browse_btn)
        cl.addLayout(file_row)

        opt_row = QHBoxLayout()
        opt_row.addWidget(QLabel("本机 ECU 节点 (BU_):"))
        self.ecu_combo = QComboBox()
        opt_row.addWidget(self.ecu_combo)

        opt_row.addWidget(QLabel("目标通道:"))
        self.channel_combo = QComboBox()
        opt_row.addWidget(self.channel_combo)

        self.chk_update_existing = QCheckBox("更新已存在报文/信号")
        self.chk_update_existing.setChecked(True)
        opt_row.addWidget(self.chk_update_existing)

        self.chk_include_diag = QCheckBox("包含诊断 TP 报文")
        self.chk_include_diag.setChecked(False)
        opt_row.addWidget(self.chk_include_diag)

        self.preview_btn = QPushButton("预览派生差异")
        self.preview_btn.clicked.connect(self._on_preview_sync)
        opt_row.addWidget(self.preview_btn)

        self.apply_btn = QPushButton("执行多模块派生")
        self.apply_btn.setEnabled(False)
        self.apply_btn.clicked.connect(self._on_apply_sync)
        opt_row.addWidget(self.apply_btn)
        cl.addLayout(opt_row)

        self.summary_label = QLabel("请选择 DBC 文件并点击「预览派生差异」。")
        self.summary_label.setStyleSheet("color: #57606a;")
        cl.addWidget(self.summary_label)

        layout.addWidget(cfg_box)

        self.preview_table = QTableWidget(0, 8)
        self.preview_table.setHorizontalHeaderLabels([
            "操作",
            "方向",
            "分类",
            "DBC 报文",
            "CAN ID",
            "DLC",
            "周期 (ms)",
            "派生作用域 / 差异摘要",
        ])
        _configure_table(self.preview_table)
        self.preview_table.horizontalHeader().setSectionResizeMode(7, QHeaderView.Stretch)
        layout.addWidget(self.preview_table, 1)

        self.reload()
        self._auto_detect_project_dbc()

    def reload(self) -> None:
        prev_ch = self.channel_combo.currentData()
        self.channel_combo.clear()
        self.channel_combo.addItem("(自动选择首个通道)", "")
        for row in self.service.list_channel_rows():
            self.channel_combo.addItem(row.channel_name, row.channel_name)
        idx = self.channel_combo.findData(prev_ch)
        if idx >= 0:
            self.channel_combo.setCurrentIndex(idx)

    def _auto_detect_project_dbc(self) -> None:
        proj_path = getattr(self.service.project, "path", None)
        if not proj_path:
            return
        root = Path(proj_path).parent
        candidates = sorted(root.glob("DemoDatabase/*.dbc")) + sorted(root.glob("system/**/*.dbc"))
        if candidates and not self.edit_dbc_path.text().strip():
            self.edit_dbc_path.setText(str(candidates[0]))
            self._load_dbc_metadata()

    def _on_browse_dbc(self) -> None:
        proj_path = getattr(self.service.project, "path", None)
        start = str(Path(proj_path).parent) if proj_path else str(Path.home())
        file_path, _ = QFileDialog.getOpenFileName(
            self, "选择 DBC 通信矩阵文件", start, "DBC Files (*.dbc);;All Files (*)"
        )
        if file_path:
            self.edit_dbc_path.setText(file_path)
            self._load_dbc_metadata()

    def _load_dbc_metadata(self) -> None:
        raw = self.edit_dbc_path.text().strip()
        if not raw or not Path(raw).is_file():
            return
        try:
            db = DbcParser().parse_database(Path(raw))
        except Exception as exc:
            self.summary_label.setText(f"❌ 无法解析 DBC: {exc}")
            return
        prev = self.ecu_combo.currentText()
        self.ecu_combo.clear()
        for node in db.ecu_nodes:
            self.ecu_combo.addItem(node, node)
        if prev:
            idx = self.ecu_combo.findText(prev)
            if idx >= 0:
                self.ecu_combo.setCurrentIndex(idx)
        elif "MCU" in db.ecu_nodes:
            self.ecu_combo.setCurrentText("MCU")
        self.summary_label.setText(
            f"已加载 DBC：{db.db_name} | 节点: {', '.join(db.ecu_nodes) or '-'} | 共 {len(db.messages)} 条报文"
        )

    def _on_preview_sync(self) -> None:
        raw = self.edit_dbc_path.text().strip()
        if not raw or not Path(raw).is_file():
            QMessageBox.warning(self, "DBC 预览", "请先选择一个有效的 .dbc 文件。")
            return
        if self.ecu_combo.count() == 0:
            self._load_dbc_metadata()
        ecu_node = self.ecu_combo.currentText().strip()
        if not ecu_node:
            QMessageBox.warning(self, "DBC 预览", "DBC 中未检测到 ECU 节点（BU_）。")
            return
        plan = plan_dbc_sync(
            self.service.project,
            Path(raw),
            ecu_node=ecu_node,
            channel_name=self.channel_combo.currentData() or None,
            include_diag=self.chk_include_diag.isChecked(),
            update_existing=self.chk_update_existing.isChecked(),
        )
        self._current_plan = plan
        self._populate_preview(plan)

    def _populate_preview(self, plan: DbcSyncPlan) -> None:
        self.preview_table.setRowCount(len(plan.items))
        create_cnt = sum(1 for i in plan.items if i.action == "create")
        update_cnt = sum(1 for i in plan.items if i.action == "update")
        unchanged_cnt = sum(1 for i in plan.items if i.action == "unchanged")
        skip_cnt = sum(1 for i in plan.items if i.action == "skip")

        for idx, item in enumerate(plan.items):
            lbl, col = _SYNC_ACTION_LABELS.get(item.action, (item.action, _MUTED_COLOR))
            items = [
                _ro_item(lbl, color=col, bold=True),
                _ro_item(item.direction),
                _ro_item(item.category),
                _ro_item(item.message_name),
                _ro_item(item.can_id_hex),
                _ro_item(str(item.dlc)),
                _ro_item(f"{item.cycle_time_ms:g}" if item.cycle_time_ms is not None else "-"),
                _ro_item(item.target_summary),
            ]
            for c_idx, it in enumerate(items):
                self.preview_table.setItem(idx, c_idx, it)

        mods_str = ", ".join(plan.target_modules) or "无"
        self.summary_label.setText(
            f"预览完成（节点 {plan.ecu_node} → 目标模块 [{mods_str}]）："
            f"新建 {create_cnt}，更新 {update_cnt}，未变化 {unchanged_cnt}，跳过 {skip_cnt}"
        )
        self.apply_btn.setEnabled(create_cnt + update_cnt > 0)

    def _on_apply_sync(self) -> None:
        if self._current_plan is None:
            return
        res = apply_dbc_sync(self.service.project, self._current_plan)
        if res.skipped_locked:
            QMessageBox.warning(
                self,
                "部分项受 Pre 锁跳过",
                "\n".join(res.skipped_locked[:5]),
            )
        self.config_changed.emit()
        self._on_preview_sync()
        QMessageBox.information(
            self,
            "DBC 派生完成",
            f"新建 EcuC PDU: {res.created_ecuc_pdus}\n"
            f"CanIf PDU: +{res.created_canif_pdus} / 更新 {res.updated_canif_pdus}\n"
            f"PduR 路由: +{res.created_pdur_paths}\n"
            f"ComIPdu: +{res.created_com_ipdus} / 更新 {res.updated_com_ipdus}\n"
            f"ComSignal: +{res.created_com_signals} / 更新 {res.updated_com_signals}",
        )
