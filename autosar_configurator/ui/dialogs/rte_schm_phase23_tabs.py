"""Phase 2/3 tabs for RteSchmWorkbench: Data Mapping (Tab 4) and Service Mapping (Tab 5)."""

from typing import List, Optional, Tuple

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QGroupBox,
    QHBoxLayout,
    QHeaderView,
    QLabel,
    QLineEdit,
    QPushButton,
    QSplitter,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...generator.rte.workbench_service import (
    DataMappingRow,
    RteWorkbenchService,
    ServicePortRow,
    SwcInstanceSummaryRow,
)

_OK_COLOR = QColor("#1b7f37")
_WARN_COLOR = QColor("#a65e00")
_ERR_COLOR = QColor("#b00020")
_INFO_COLOR = QColor("#1f5fbf")
_MUTED_COLOR = QColor("#6e7781")

_DM_STATUS = {
    "mapped": ("已映射 Com", _OK_COLOR),
    "inter_swc": ("核内/核间连接", _INFO_COLOR),
    "unmapped": ("未映射", _MUTED_COLOR),
    "broken_com": ("ComSignal 缺失/断链", _ERR_COLOR),
    "direction_mismatch": ("收发方向冲突", _ERR_COLOR),
}

_SP_STATUS = {
    "connected": ("已连接", _OK_COLOR),
    "unconnected": ("未连接", _WARN_COLOR),
    "broken": ("连接失效", _ERR_COLOR),
}


def _ro_item(text: str, *, color: Optional[QColor] = None, bold: bool = False) -> QTableWidgetItem:
    it = QTableWidgetItem(text)
    it.setFlags(it.flags() & ~Qt.ItemIsEditable)
    if color is not None:
        it.setForeground(color)
    if bold:
        f = it.font()
        f.setBold(True)
        it.setFont(f)
    return it


class DataMappingTab(QWidget):
    """Tab 4: Interactive SWC Sender-Receiver Port <-> ComSignal Data Mapping editor."""

    config_changed = Signal()

    def __init__(self, service: RteWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._all_rows: List[DataMappingRow] = []
        self._visible_rows: List[DataMappingRow] = []

        layout = QVBoxLayout(self)

        # Filter & quick-action bar
        flt = QHBoxLayout()
        self.search_edit = QLineEdit()
        self.search_edit.setPlaceholderText("搜索 SWC 组件、端口、数据类型或 ComSignal...")
        self.search_edit.textChanged.connect(self._apply_filters)
        flt.addWidget(self.search_edit, 1)

        self.dir_combo = QComboBox()
        self.dir_combo.addItem("全部方向", "")
        self.dir_combo.addItem("TX (P-Port 发送)", "TX")
        self.dir_combo.addItem("RX (R-Port 接收)", "RX")
        self.dir_combo.currentIndexChanged.connect(self._apply_filters)
        flt.addWidget(self.dir_combo)

        self.status_combo = QComboBox()
        self.status_combo.addItem("全部状态", "")
        self.status_combo.addItem("未映射 / 异常", "issues")
        self.status_combo.addItem("仅错误 (断链/方向冲突)", "errors")
        self.status_combo.addItem("已映射 ComSignal", "mapped")
        self.status_combo.addItem("SWC 内部连接", "inter_swc")
        self.status_combo.currentIndexChanged.connect(self._apply_filters)
        flt.addWidget(self.status_combo)

        self.auto_match_btn = QPushButton("自动匹配 ComSignal")
        self.auto_match_btn.setToolTip("按信号名与 TX/RX 方向自动为未映射或断链 SWC 端口匹配 ComSignal")
        self.auto_match_btn.clicked.connect(self._on_auto_match)
        flt.addWidget(self.auto_match_btn)

        self.summary_label = QLabel("")
        self.summary_label.setStyleSheet("color: #57606a;")
        flt.addWidget(self.summary_label)
        layout.addLayout(flt)

        # Data Mapping Table
        self.table = QTableWidget(0, 8)
        self.table.setHorizontalHeaderLabels([
            "SWC 组件",
            "端口",
            "数据元素",
            "方向",
            "C 类型",
            "SystemSignal",
            "目标 ComSignal",
            "状态",
        ])
        self.table.verticalHeader().setVisible(False)
        self.table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.table.setSelectionMode(QAbstractItemView.SingleSelection)
        self.table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.table.setAlternatingRowColors(True)
        hdr = self.table.horizontalHeader()
        hdr.setSectionResizeMode(QHeaderView.Interactive)
        hdr.setStretchLastSection(False)
        hdr.setSectionResizeMode(6, QHeaderView.Stretch)
        self.table.itemSelectionChanged.connect(self._on_selection_changed)
        layout.addWidget(self.table, 1)

        # Inline mapping editor
        eb = QGroupBox("选中端口 ComSignal 映射（写入工程覆盖层，不修改只读 System ARXML）")
        el = QHBoxLayout(eb)
        self.sel_label = QLabel("未选中端口")
        self.sel_label.setMinimumWidth(220)
        el.addWidget(self.sel_label)

        el.addWidget(QLabel("目标 ComSignal:"))
        self.combo_com_signal = QComboBox()
        self.combo_com_signal.setMinimumWidth(340)
        el.addWidget(self.combo_com_signal, 1)

        self.bind_btn = QPushButton("绑定 ComSignal")
        self.bind_btn.setEnabled(False)
        self.bind_btn.clicked.connect(self._on_bind)
        el.addWidget(self.bind_btn)

        self.unbind_btn = QPushButton("解除映射")
        self.unbind_btn.setEnabled(False)
        self.unbind_btn.clicked.connect(self._on_unbind)
        el.addWidget(self.unbind_btn)
        layout.addWidget(eb)

        self.reload()

    def reload(self) -> None:
        self._all_rows = self.service.list_data_mapping_rows()
        self._apply_filters()

    def _apply_filters(self) -> None:
        q = self.search_edit.text().strip().lower()
        d_flt = self.dir_combo.currentData() or ""
        s_flt = self.status_combo.currentData() or ""

        prev = self._current_row()
        prev_key = (prev.component_name, prev.port_name, prev.data_element_name) if prev else None

        filtered: List[DataMappingRow] = []
        for r in self._all_rows:
            if d_flt and r.direction != d_flt:
                continue
            if s_flt == "issues" and r.status in ("mapped", "inter_swc"):
                continue
            elif s_flt == "errors" and r.status not in ("broken_com", "direction_mismatch"):
                continue
            elif s_flt in ("mapped", "inter_swc") and r.status != s_flt:
                continue
            if q:
                hay = " ".join([
                    r.component_name,
                    r.port_name,
                    r.data_element_name,
                    r.c_type,
                    r.system_signal_name,
                    r.com_signal_name,
                ]).lower()
                if q not in hay:
                    continue
            filtered.append(r)

        self._visible_rows = filtered
        self.table.setRowCount(len(filtered))
        reselect = -1
        for idx, r in enumerate(filtered):
            st_lbl, st_col = _DM_STATUS.get(r.status, (r.status, _MUTED_COLOR))
            src_tag = " [覆盖]" if r.source == "overlay" else ""
            items = [
                _ro_item(r.component_name),
                _ro_item(r.port_name),
                _ro_item(r.data_element_name),
                _ro_item(r.direction, color=_INFO_COLOR if r.direction == "TX" else _WARN_COLOR, bold=True),
                _ro_item(r.c_type),
                _ro_item(r.system_signal_name or "-"),
                _ro_item(r.com_signal_name or "-"),
                _ro_item(st_lbl + src_tag, color=st_col, bold=r.status in ("broken_com", "direction_mismatch")),
            ]
            for c_idx, it in enumerate(items):
                if c_idx == 0:
                    it.setData(Qt.UserRole, r)
                self.table.setItem(idx, c_idx, it)
            if prev_key == (r.component_name, r.port_name, r.data_element_name):
                reselect = idx

        mapped_cnt = sum(1 for r in self._all_rows if r.status == "mapped")
        err_cnt = sum(1 for r in self._all_rows if r.status in ("broken_com", "direction_mismatch"))
        self.summary_label.setText(f"总计 {len(self._all_rows)} | 已映射 Com {mapped_cnt} | 错误 {err_cnt}")

        if reselect >= 0:
            self.table.selectRow(reselect)
        else:
            self._on_selection_changed()

    def _current_row(self) -> Optional[DataMappingRow]:
        sel = self.table.selectionModel().selectedRows() if self.table.selectionModel() else []
        if not sel:
            return None
        idx = sel[0].row()
        return self._visible_rows[idx] if 0 <= idx < len(self._visible_rows) else None

    def _on_selection_changed(self) -> None:
        row = self._current_row()
        self.combo_com_signal.clear()
        if row is None:
            self.sel_label.setText("未选中端口")
            self.bind_btn.setEnabled(False)
            self.unbind_btn.setEnabled(False)
            return

        self.sel_label.setText(f"{row.component_name}.{row.port_name} ({row.direction})")
        avail = self.service.list_available_com_signals(direction=row.direction)
        if not avail:
            avail = self.service.list_available_com_signals(direction=None)
        for sig_name, sig_dir, sys_leaf in avail:
            label = f"{sig_name} [{sig_dir or '?'}]" + (f" ({sys_leaf})" if sys_leaf else "")
            self.combo_com_signal.addItem(label, sig_name)

        if row.com_signal_name:
            idx = self.combo_com_signal.findData(row.com_signal_name)
            if idx >= 0:
                self.combo_com_signal.setCurrentIndex(idx)

        self.bind_btn.setEnabled(self.combo_com_signal.count() > 0)
        self.unbind_btn.setEnabled(row.status in ("mapped", "broken_com", "direction_mismatch"))

    def _on_bind(self) -> None:
        row = self._current_row()
        sig_name = self.combo_com_signal.currentData()
        if row is None or not sig_name:
            return
        self.service.set_data_mapping(
            row.component_name,
            row.port_name,
            sig_name,
            data_element=row.data_element_name,
            direction=row.direction,
        )
        self.reload()
        self.config_changed.emit()

    def _on_unbind(self) -> None:
        row = self._current_row()
        if row is None:
            return
        if self.service.clear_data_mapping(row.component_name, row.port_name):
            self.reload()
            self.config_changed.emit()

    def _on_auto_match(self) -> None:
        matched = self.service.auto_match_data_mappings()
        self.reload()
        if matched > 0:
            self.config_changed.emit()


class ServiceMappingTab(QWidget):
    """Tab 5: ServiceComponent / Assembly Port Connections & SWC Core Partition Overview."""

    config_changed = Signal()

    def __init__(self, service: RteWorkbenchService, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.service = service
        self._all_ports: List[ServicePortRow] = []
        self._visible_ports: List[ServicePortRow] = []
        self._swcs: List[SwcInstanceSummaryRow] = []

        layout = QVBoxLayout(self)
        splitter = QSplitter(Qt.Vertical)

        # Top pane: R-Port connections
        top_w = QWidget()
        tl = QVBoxLayout(top_w)
        tl.setContentsMargins(0, 0, 0, 0)

        flt = QHBoxLayout()
        self.search_edit = QLineEdit()
        self.search_edit.setPlaceholderText("搜索请求组件/端口、接口或 Provider...")
        self.search_edit.textChanged.connect(self._apply_filters)
        flt.addWidget(self.search_edit, 1)

        self.only_service_check = QCheckBox("仅看 Service 接口")
        self.only_service_check.toggled.connect(self._apply_filters)
        flt.addWidget(self.only_service_check)

        self.only_issues_check = QCheckBox("仅看未连接/断链")
        self.only_issues_check.toggled.connect(self._apply_filters)
        flt.addWidget(self.only_issues_check)

        self.auto_connect_btn = QPushButton("自动连接服务端口")
        self.auto_connect_btn.setToolTip("按接口名及服务端口名（如 UR_* -> ComM）自动绑定唯一兼容 Provider 端口")
        self.auto_connect_btn.clicked.connect(self._on_auto_connect)
        flt.addWidget(self.auto_connect_btn)

        self.summary_label = QLabel("")
        self.summary_label.setStyleSheet("color: #57606a;")
        flt.addWidget(self.summary_label)
        tl.addLayout(flt)

        self.ports_table = QTableWidget(0, 8)
        self.ports_table.setHorizontalHeaderLabels([
            "请求组件",
            "请求 R-Port",
            "接口名称",
            "类型",
            "提供方 (Provider)",
            "提供方 P-Port",
            "服务端 API",
            "状态",
        ])
        self.ports_table.verticalHeader().setVisible(False)
        self.ports_table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.ports_table.setSelectionMode(QAbstractItemView.SingleSelection)
        self.ports_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.ports_table.setAlternatingRowColors(True)
        hdr = self.ports_table.horizontalHeader()
        hdr.setSectionResizeMode(QHeaderView.Interactive)
        hdr.setSectionResizeMode(6, QHeaderView.Stretch)
        self.ports_table.itemSelectionChanged.connect(self._on_port_selection_changed)
        tl.addWidget(self.ports_table, 1)

        eb = QGroupBox("选中 R-Port 连接配置（支持 ServiceComponent 如 ComM / EcuM / BswM / Det 与 SWC 核间端口）")
        ebl = QHBoxLayout(eb)
        self.sel_port_label = QLabel("未选中请求端口")
        self.sel_port_label.setMinimumWidth(220)
        ebl.addWidget(self.sel_port_label)

        ebl.addWidget(QLabel("兼容 Provider P-Port:"))
        self.combo_provider = QComboBox()
        self.combo_provider.setMinimumWidth(340)
        ebl.addWidget(self.combo_provider, 1)

        self.connect_btn = QPushButton("建立连接")
        self.connect_btn.setEnabled(False)
        self.connect_btn.clicked.connect(self._on_connect)
        ebl.addWidget(self.connect_btn)

        self.disconnect_btn = QPushButton("断开连接")
        self.disconnect_btn.setEnabled(False)
        self.disconnect_btn.clicked.connect(self._on_disconnect)
        ebl.addWidget(self.disconnect_btn)
        tl.addWidget(eb)
        splitter.addWidget(top_w)

        # Bottom pane: SWC Instances & OsApplication summary
        bot_w = QGroupBox("SWC 与 ServiceComponent 实例核间分区总览")
        bl = QVBoxLayout(bot_w)
        self.swc_table = QTableWidget(0, 7)
        self.swc_table.setHorizontalHeaderLabels([
            "实例名称",
            "SWC 类型",
            "组件类别",
            "所属 OsApplication",
            "Core",
            "端口 / Runnable",
            "事件映射 (已配 / 未配)",
        ])
        self.swc_table.verticalHeader().setVisible(False)
        self.swc_table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.swc_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.swc_table.setAlternatingRowColors(True)
        bhdr = self.swc_table.horizontalHeader()
        bhdr.setSectionResizeMode(QHeaderView.Interactive)
        bhdr.setSectionResizeMode(3, QHeaderView.Stretch)
        bl.addWidget(self.swc_table)
        splitter.addWidget(bot_w)

        splitter.setStretchFactor(0, 3)
        splitter.setStretchFactor(1, 2)
        layout.addWidget(splitter)
        self.reload()

    def reload(self) -> None:
        self._all_ports = self.service.list_service_port_rows()
        self._swcs = self.service.list_swc_instance_rows()
        self._apply_filters()
        self._populate_swc_table()

    def _populate_swc_table(self) -> None:
        self.swc_table.setRowCount(len(self._swcs))
        for idx, swc in enumerate(self._swcs):
            cat_lbl = "Service" if swc.is_service else "Application"
            items = [
                _ro_item(swc.instance_name),
                _ro_item(swc.swc_type_name),
                _ro_item(cat_lbl, color=_INFO_COLOR if swc.is_service else _OK_COLOR),
                _ro_item(swc.os_application),
                _ro_item(f"Core {swc.core_id}"),
                _ro_item(f"{swc.port_count} / {swc.runnable_count}"),
                _ro_item(
                    f"{swc.mapped_events} / {swc.unmapped_events}",
                    color=_WARN_COLOR if swc.unmapped_events > 0 else _OK_COLOR,
                ),
            ]
            for c_idx, it in enumerate(items):
                self.swc_table.setItem(idx, c_idx, it)

    def _apply_filters(self) -> None:
        q = self.search_edit.text().strip().lower()
        only_srv = self.only_service_check.isChecked()
        only_iss = self.only_issues_check.isChecked()

        prev = self._current_port()
        prev_key = (prev.requester_component, prev.requester_port) if prev else None

        filtered: List[ServicePortRow] = []
        for r in self._all_ports:
            if only_srv and not r.is_service:
                continue
            if only_iss and r.status == "connected":
                continue
            if q:
                hay = " ".join([
                    r.requester_component,
                    r.requester_port,
                    r.interface_name,
                    r.provider_component,
                    r.provider_port,
                    r.server_symbol,
                ]).lower()
                if q not in hay:
                    continue
            filtered.append(r)

        self._visible_ports = filtered
        self.ports_table.setRowCount(len(filtered))
        reselect = -1
        for idx, r in enumerate(filtered):
            st_lbl, st_col = _SP_STATUS.get(r.status, (r.status, _MUTED_COLOR))
            src_tag = " [覆盖]" if r.source == "overlay" else ""
            kind_lbl = f"{r.interface_kind}{'(Srv)' if r.is_service else ''}"
            items = [
                _ro_item(r.requester_component),
                _ro_item(r.requester_port),
                _ro_item(r.interface_name),
                _ro_item(kind_lbl, color=_INFO_COLOR if r.is_service else None),
                _ro_item(r.provider_component or "-"),
                _ro_item(r.provider_port or "-"),
                _ro_item(r.server_symbol or "-"),
                _ro_item(st_lbl + src_tag, color=st_col, bold=r.status == "broken"),
            ]
            for c_idx, it in enumerate(items):
                if c_idx == 0:
                    it.setData(Qt.UserRole, r)
                self.ports_table.setItem(idx, c_idx, it)
            if prev_key == (r.requester_component, r.requester_port):
                reselect = idx

        conn_cnt = sum(1 for r in self._all_ports if r.status == "connected")
        unconn_cnt = sum(1 for r in self._all_ports if r.status != "connected")
        self.summary_label.setText(f"总计 {len(self._all_ports)} | 已连接 {conn_cnt} | 待连接/断链 {unconn_cnt}")

        if reselect >= 0:
            self.ports_table.selectRow(reselect)
        else:
            self._on_port_selection_changed()

    def _current_port(self) -> Optional[ServicePortRow]:
        sel = self.ports_table.selectionModel().selectedRows() if self.ports_table.selectionModel() else []
        if not sel:
            return None
        idx = sel[0].row()
        return self._visible_ports[idx] if 0 <= idx < len(self._visible_ports) else None

    def _on_port_selection_changed(self) -> None:
        row = self._current_port()
        self.combo_provider.clear()
        if row is None:
            self.sel_port_label.setText("未选中请求端口")
            self.connect_btn.setEnabled(False)
            self.disconnect_btn.setEnabled(False)
            return

        self.sel_port_label.setText(f"{row.requester_component}.{row.requester_port}")
        cands = self.service.list_compatible_provider_ports(row.requester_component, row.requester_port)
        for prov_c, prov_p, ifn in cands:
            self.combo_provider.addItem(f"{prov_c}.{prov_p} ({ifn})", (prov_c, prov_p))

        if row.provider_component and row.provider_port:
            idx = self.combo_provider.findData((row.provider_component, row.provider_port))
            if idx >= 0:
                self.combo_provider.setCurrentIndex(idx)

        self.connect_btn.setEnabled(self.combo_provider.count() > 0)
        self.disconnect_btn.setEnabled(row.status in ("connected", "broken"))

    def _on_connect(self) -> None:
        row = self._current_port()
        target = self.combo_provider.currentData()
        if row is None or not target:
            return
        prov_c, prov_p = target
        self.service.connect_ports(row.requester_component, row.requester_port, prov_c, prov_p)
        self.reload()
        self.config_changed.emit()

    def _on_disconnect(self) -> None:
        row = self._current_port()
        if row is None:
            return
        if self.service.disconnect_port(row.requester_component, row.requester_port):
            self.reload()
            self.config_changed.emit()

    def _on_auto_connect(self) -> None:
        connected = self.service.auto_connect_service_ports()
        self.reload()
        if connected > 0:
            self.config_changed.emit()
