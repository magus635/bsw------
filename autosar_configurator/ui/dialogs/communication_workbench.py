"""5-tab Communication Configuration & DBC Derivation Workbench dialog."""

from typing import Any, Optional

from PySide6.QtCore import Signal
from PySide6.QtWidgets import (
    QDialog,
    QDialogButtonBox,
    QHBoxLayout,
    QLabel,
    QPushButton,
    QTabWidget,
    QVBoxLayout,
    QWidget,
)

from ...core.communication import CommunicationWorkbenchService
from .communication_tabs import (
    ChannelsTab,
    DbcSyncTab,
    MessagesTab,
    PduRRoutingTab,
    SignalsTab,
)


class CommunicationWorkbench(QDialog):
    """Unified 5-tab workbench for CAN channels, messages, signals, PduR routing, and DBC sync."""

    config_changed = Signal()
    navigate_to_path_requested = Signal(str)

    def __init__(self, project: Any, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.project = project
        self.service = CommunicationWorkbenchService(project)
        self.initial_snapshots = self.service.capture_snapshots()
        self.has_edits = False
        self._dirty_tabs = set()

        proj_name = getattr(project, "name", "Project")
        self.setWindowTitle(f"通信配置工作台 (Communication) — {proj_name}")
        self.resize(1200, 780)

        root = QVBoxLayout(self)

        # Header summary & clickable health-check banner
        header = QVBoxLayout()
        header.setSpacing(4)

        top_row = QHBoxLayout()
        self.header_summary_label = QLabel("")
        self.header_summary_label.setStyleSheet("font-weight: bold; font-size: 13px; color: #1f2328;")
        top_row.addWidget(self.header_summary_label, 1)
        header.addLayout(top_row)

        health_row = QHBoxLayout()
        health_row.setSpacing(6)
        health_title = QLabel("健康检查:")
        health_title.setStyleSheet("color: #555; font-size: 12px;")
        health_row.addWidget(health_title)

        self.health_ok_label = QLabel("✅ 通信链路与信号位域检查通过")
        self.health_ok_label.setStyleSheet(
            "color: #1b7f37; background-color: #e8f5e9; padding: 3px 8px; border-radius: 3px; font-size: 12px;"
        )
        health_row.addWidget(self.health_ok_label)

        self.btn_fix_sig_errors = QPushButton("")
        self.btn_fix_sig_errors.setStyleSheet(
            "color: #b00020; background-color: #ffebee; border: 1px solid #ef9a9a; "
            "padding: 2px 8px; border-radius: 3px; font-weight: bold; font-size: 12px;"
        )
        self.btn_fix_sig_errors.clicked.connect(self._jump_to_signal_errors)
        health_row.addWidget(self.btn_fix_sig_errors)

        self.btn_fix_msg_errors = QPushButton("")
        self.btn_fix_msg_errors.setStyleSheet(
            "color: #b00020; background-color: #ffebee; border: 1px solid #ef9a9a; "
            "padding: 2px 8px; border-radius: 3px; font-weight: bold; font-size: 12px;"
        )
        self.btn_fix_msg_errors.clicked.connect(self._jump_to_message_issues)
        health_row.addWidget(self.btn_fix_msg_errors)

        self.btn_fix_warnings = QPushButton("")
        self.btn_fix_warnings.setStyleSheet(
            "color: #a65e00; background-color: #fff3e0; border: 1px solid #ffcc80; "
            "padding: 2px 8px; border-radius: 3px; font-size: 12px;"
        )
        self.btn_fix_warnings.clicked.connect(self._jump_to_warnings)
        health_row.addWidget(self.btn_fix_warnings)

        health_row.addStretch()
        header.addLayout(health_row)
        root.addLayout(header)

        # Tabs
        self.tabs = QTabWidget()
        self.channels_tab = ChannelsTab(self.service, self)
        self.messages_tab = MessagesTab(self.service, self)
        self.signals_tab = SignalsTab(self.service, self)
        self.pdur_tab = PduRRoutingTab(self.service, self)
        self.dbc_tab = DbcSyncTab(self.service, self)

        self.tabs.addTab(self.channels_tab, "1. 总线与通道")
        self.tabs.addTab(self.messages_tab, "2. 报文与全链路")
        self.tabs.addTab(self.signals_tab, "3. 信号矩阵与位图")
        self.tabs.addTab(self.pdur_tab, "4. PduR 路由矩阵")
        self.tabs.addTab(self.dbc_tab, "5. DBC 同步派生")
        self.tabs.currentChanged.connect(self._on_current_tab_changed)
        root.addWidget(self.tabs, 1)

        # Footer buttons
        btn_row = QHBoxLayout()
        self.revert_btn = QPushButton("恢复打开前状态")
        self.revert_btn.setEnabled(False)
        self.revert_btn.clicked.connect(self._on_revert)
        btn_row.addWidget(self.revert_btn)
        btn_row.addStretch()

        button_box = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        button_box.button(QDialogButtonBox.Ok).setText("确定")
        button_box.button(QDialogButtonBox.Cancel).setText("取消")
        button_box.accepted.connect(self.accept)
        button_box.rejected.connect(self.reject)
        btn_row.addWidget(button_box)
        root.addLayout(btn_row)

        # Signal wiring
        for tab in (self.channels_tab, self.messages_tab, self.signals_tab, self.pdur_tab):
            tab.navigate_requested.connect(self.navigate_to_path_requested.emit)
        for tab in (self.messages_tab, self.signals_tab, self.pdur_tab, self.dbc_tab):
            tab.config_changed.connect(lambda src=tab: self._on_tab_config_changed(src))
        self.messages_tab.inspect_signals_requested.connect(self._open_signals_for_ipdu)

        self._update_header_summary()

    def select_tab(self, index: int) -> None:
        if 0 <= index < self.tabs.count():
            self.tabs.setCurrentIndex(index)

    def reload_all(self) -> None:
        self._dirty_tabs.clear()
        self.channels_tab.reload()
        self.messages_tab.reload()
        self.signals_tab.reload()
        self.pdur_tab.reload()
        self.dbc_tab.reload()
        self._update_header_summary()

    def _on_current_tab_changed(self, _index: int) -> None:
        cur = self.tabs.currentWidget()
        if cur in self._dirty_tabs:
            self._dirty_tabs.discard(cur)
            if hasattr(cur, "reload"):
                cur.reload()

    def _on_tab_config_changed(self, source: QWidget) -> None:
        self.has_edits = True
        self.revert_btn.setEnabled(True)
        for tab in (self.channels_tab, self.messages_tab, self.signals_tab, self.pdur_tab, self.dbc_tab):
            if tab is source:
                continue
            if self.tabs.currentWidget() is tab:
                tab.reload()
            else:
                self._dirty_tabs.add(tab)
        self._update_header_summary()
        self.config_changed.emit()

    def _on_revert(self) -> None:
        if self.initial_snapshots:
            self.service.restore_snapshots(self.initial_snapshots)
        self.has_edits = False
        self.revert_btn.setEnabled(False)
        self.reload_all()

    def reject(self) -> None:
        if self.has_edits and self.initial_snapshots:
            self.service.restore_snapshots(self.initial_snapshots)
            self.has_edits = False
        super().reject()

    def _open_signals_for_ipdu(self, ipdu_name: str) -> None:
        if self.signals_tab in self._dirty_tabs:
            self._dirty_tabs.discard(self.signals_tab)
            self.signals_tab.reload()
        self.tabs.setCurrentWidget(self.signals_tab)
        self.signals_tab.focus_ipdu(ipdu_name)

    def _jump_to_signal_errors(self) -> None:
        if self.signals_tab in self._dirty_tabs:
            self._dirty_tabs.discard(self.signals_tab)
            self.signals_tab.reload()
        self.tabs.setCurrentWidget(self.signals_tab)
        self.signals_tab.ipdu_combo.setCurrentIndex(0)
        self.signals_tab.search_edit.clear()
        self.signals_tab.only_issues_check.setChecked(True)

    def _jump_to_message_issues(self) -> None:
        if self.messages_tab in self._dirty_tabs:
            self._dirty_tabs.discard(self.messages_tab)
            self.messages_tab.reload()
        self.tabs.setCurrentWidget(self.messages_tab)
        self.messages_tab.direction_combo.setCurrentIndex(0)
        self.messages_tab.category_combo.setCurrentIndex(0)
        self.messages_tab.search_edit.clear()
        self.messages_tab.only_issues_check.setChecked(True)

    def _jump_to_warnings(self) -> None:
        diags = [d for d in self.service.collect_diagnostics() if d.severity != "error"]
        if not diags:
            return
        tab = diags[0].workbench_tab
        self.select_tab(tab)
        if tab == 1:
            self.messages_tab.only_issues_check.setChecked(True)

    def _update_header_summary(self) -> None:
        proj_name = getattr(self.project, "name", "Project")
        mods = self.service.loaded_comm_modules()
        ch_cnt = len(self.service.list_channel_rows())
        msg_cnt = len(self.service.list_message_rows())
        sig_cnt = len(self.service.list_signal_rows())
        route_cnt = len(self.service.list_pdur_routing_rows())

        diags = self.service.collect_diagnostics()
        sig_errs = sum(1 for d in diags if d.severity == "error" and d.workbench_tab == 2)
        msg_errs = sum(1 for d in diags if d.severity == "error" and d.workbench_tab == 1)
        warn_cnt = sum(1 for d in diags if d.severity != "error")

        self.header_summary_label.setText(
            f"工程：{proj_name}  |  已加载模块：{', '.join(mods) or '无'}  |  "
            f"通道：{ch_cnt}  |  报文：{msg_cnt}  |  信号：{sig_cnt}  |  路由：{route_cnt}"
        )

        self.btn_fix_sig_errors.setText(f"❌ {sig_errs} 个信号位域错误 [去调整]")
        self.btn_fix_sig_errors.setVisible(sig_errs > 0)

        self.btn_fix_msg_errors.setText(f"❌ {msg_errs} 个 ID/句柄冲突 [去修复]")
        self.btn_fix_msg_errors.setVisible(msg_errs > 0)

        self.btn_fix_warnings.setText(f"⚠️ {warn_cnt} 个链路/长度告警 [去查看]")
        self.btn_fix_warnings.setVisible(warn_cnt > 0)

        self.health_ok_label.setVisible(sig_errs == 0 and msg_errs == 0 and warn_cnt == 0)
