"""5-tab System Services & Diagnostics Workbench dialog."""

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

from ...core.services import SystemServicesWorkbenchService
from .system_services_tabs import (
    BswMTab,
    DetCddTab,
    DiagDcmCanTpTab,
    EcuMTab,
    OsResourcesTab,
)


class SystemServicesWorkbench(QDialog):
    """Unified 5-tab workbench for EcuM, BswM, Os, Dcm+CanTp, and Det/CDD services."""

    config_changed = Signal()
    navigate_to_path_requested = Signal(str)

    def __init__(self, project: Any, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.project = project
        self.service = SystemServicesWorkbenchService(project)
        self.initial_snapshots = self.service.capture_snapshots()
        self.has_edits = False
        self._dirty_tabs = set()

        proj_name = getattr(project, "name", "Project")
        self.setWindowTitle(f"系统服务与诊断工作台 (System Services & Diagnostics) — {proj_name}")
        self.resize(1240, 800)

        root = QVBoxLayout(self)

        # Header summary & clickable health pills
        header = QVBoxLayout()
        header.setSpacing(4)

        self.header_summary_label = QLabel("")
        self.header_summary_label.setStyleSheet("font-weight: bold; font-size: 13px; color: #1f2328;")
        header.addWidget(self.header_summary_label)

        health_row = QHBoxLayout()
        health_row.setSpacing(6)
        health_title = QLabel("健康检查:")
        health_title.setStyleSheet("color: #555; font-size: 12px;")
        health_row.addWidget(health_title)

        self.health_ok_label = QLabel("✅ 系统服务与诊断链路检查通过")
        self.health_ok_label.setStyleSheet(
            "color: #1b7f37; background-color: #e8f5e9; padding: 3px 8px; border-radius: 3px; font-size: 12px;"
        )
        health_row.addWidget(self.health_ok_label)

        self.btn_fix_ecum = QPushButton("")
        self.btn_fix_bswm = QPushButton("")
        self.btn_fix_os = QPushButton("")
        self.btn_fix_diag = QPushButton("")
        for tab_idx, btn in (
            (0, self.btn_fix_ecum),
            (1, self.btn_fix_bswm),
            (2, self.btn_fix_os),
            (3, self.btn_fix_diag),
        ):
            btn.setStyleSheet(
                "color: #a65e00; background-color: #fff3e0; border: 1px solid #ffcc80; "
                "padding: 2px 8px; border-radius: 3px; font-size: 12px;"
            )
            btn.clicked.connect(lambda _c=False, idx=tab_idx: self.select_tab(idx))
            health_row.addWidget(btn)

        health_row.addStretch()
        header.addLayout(health_row)
        root.addLayout(header)

        # 5 Tabs
        self.tabs = QTabWidget()
        self.ecum_tab = EcuMTab(self.service, self)
        self.bswm_tab = BswMTab(self.service, self)
        self.os_tab = OsResourcesTab(self.service, self)
        self.diag_tab = DiagDcmCanTpTab(self.service, self)
        self.det_cdd_tab = DetCddTab(self.service, self)

        self.tabs.addTab(self.ecum_tab, "1. EcuM 启动与休眠")
        self.tabs.addTab(self.bswm_tab, "2. BswM 规则与模式")
        self.tabs.addTab(self.os_tab, "3. Os 多核与调度资源")
        self.tabs.addTab(self.diag_tab, "4. Dcm 与 CanTp 诊断")
        self.tabs.addTab(self.det_cdd_tab, "5. Det / CDD 与平台服务")
        self.tabs.currentChanged.connect(self._on_current_tab_changed)
        root.addWidget(self.tabs, 1)

        # Footer
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

        for tab in (self.ecum_tab, self.bswm_tab, self.os_tab, self.diag_tab, self.det_cdd_tab):
            tab.navigate_requested.connect(self.navigate_to_path_requested.emit)
            tab.config_changed.connect(lambda src=tab: self._on_tab_config_changed(src))

        self._update_header_summary()

    def select_tab(self, index: int) -> None:
        if 0 <= index < self.tabs.count():
            self.tabs.setCurrentIndex(index)

    def reload_all(self) -> None:
        self._dirty_tabs.clear()
        self.ecum_tab.reload()
        self.bswm_tab.reload()
        self.os_tab.reload()
        self.diag_tab.reload()
        self.det_cdd_tab.reload()
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
        for tab in (self.ecum_tab, self.bswm_tab, self.os_tab, self.diag_tab, self.det_cdd_tab):
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

    def _update_header_summary(self) -> None:
        proj_name = getattr(self.project, "name", "Project")
        mods = self.service.loaded_service_modules()
        rules_cnt = len(self.service.list_bswm_rules())
        tasks_cnt = len(self.service.list_os_tasks())
        isrs_cnt = len(self.service.list_os_isrs())
        diag_cnt = len(self.service.list_diag_channels())

        self.header_summary_label.setText(
            f"工程：{proj_name}  |  已加载服务/平台模块：{', '.join(mods[:10]) or '无'}"
            f"{'...' if len(mods) > 10 else ''}  |  "
            f"BswM 规则：{rules_cnt}  |  Os Task/ISR：{tasks_cnt}/{isrs_cnt}  |  诊断通道：{diag_cnt}"
        )

        diags = self.service.collect_diagnostics()
        tab_counts = {0: [0, 0], 1: [0, 0], 2: [0, 0], 3: [0, 0]}
        for d in diags:
            if d.workbench_tab in tab_counts:
                if d.severity == "error":
                    tab_counts[d.workbench_tab][0] += 1
                else:
                    tab_counts[d.workbench_tab][1] += 1

        err_style = (
            "color: #b00020; background-color: #ffebee; border: 1px solid #ef9a9a; "
            "padding: 2px 8px; border-radius: 3px; font-weight: bold; font-size: 12px;"
        )
        warn_style = (
            "color: #a65e00; background-color: #fff3e0; border: 1px solid #ffcc80; "
            "padding: 2px 8px; border-radius: 3px; font-size: 12px;"
        )

        total_issues = 0
        for tab_idx, label_prefix, btn in (
            (0, "EcuM", self.btn_fix_ecum),
            (1, "BswM", self.btn_fix_bswm),
            (2, "Os", self.btn_fix_os),
            (3, "Dcm/CanTp", self.btn_fix_diag),
        ):
            errs, warns = tab_counts[tab_idx]
            cnt = errs + warns
            total_issues += cnt
            btn.setVisible(cnt > 0)
            if cnt > 0:
                icon = "❌" if errs > 0 else "⚠️"
                btn.setStyleSheet(err_style if errs > 0 else warn_style)
                btn.setText(f"{icon} {label_prefix}: {cnt} 项 [去查看]")

        self.health_ok_label.setVisible(total_issues == 0)
