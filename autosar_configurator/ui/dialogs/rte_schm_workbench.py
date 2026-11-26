"""4-tab RTE / SchM Configuration & Generation Workbench."""

import logging
from pathlib import Path
from typing import List, Optional

from PySide6.QtCore import Qt, QUrl, Signal
from PySide6.QtGui import QColor, QDesktopServices, QFont
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QDialog,
    QFileDialog,
    QGridLayout,
    QGroupBox,
    QHBoxLayout,
    QHeaderView,
    QLabel,
    QListWidget,
    QListWidgetItem,
    QMessageBox,
    QPlainTextEdit,
    QPushButton,
    QSplitter,
    QTabWidget,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...generator.rte.model import RtePreviewFile
from ...generator.rte.workbench_service import (
    BswInstanceRow,
    GENERATION_MODES,
    OPTIMIZATION_MODES,
    RteGenerationSettings,
    RteWorkbenchService,
)
from .rte_schm_tabs import (
    ExclusiveAreasTab,
    TaskMappingTab,
    _ERROR_COLOR,
    _OK_COLOR,
    _WARN_COLOR,
)

logger = logging.getLogger(__name__)

_STATUS_LABELS = {
    "active": ("活跃 (将生成 SchM)", QColor("#1b7f37")),
    "unloaded": ("未加载 (将跳过)", QColor("#b00020")),
    "unregistered": ("未在 Rte 注册", QColor("#a65e00")),
}

_PREVIEW_STATUS_LABELS = {
    "new": ("新建", QColor("#1b7f37")),
    "updated": ("更新", QColor("#1f5fbf")),
    "unchanged": ("未变化", QColor("#666666")),
    "preserved": ("保留桩文件", QColor("#7a5c00")),
    "overlay": ("工程覆盖层", QColor("#6a1b9a")),
}


class BswInstancesTab(QWidget):
    """Tab 1: Manage BSW module instances and sync with loaded modules / IB metadata."""

    config_changed = Signal()

    def __init__(self, service: RteWorkbenchService, parent=None) -> None:
        super().__init__(parent)
        self.service = service
        self._rows: List[BswInstanceRow] = []

        outer = QVBoxLayout(self)

        top = QHBoxLayout()
        self.add_btn = QPushButton("添加到 Rte 实例")
        self.add_btn.setEnabled(False)
        self.add_btn.clicked.connect(self._on_add_selected)
        top.addWidget(self.add_btn)

        self.remove_btn = QPushButton("移除实例")
        self.remove_btn.setEnabled(False)
        self.remove_btn.clicked.connect(self._on_remove_selected)
        top.addWidget(self.remove_btn)

        top.addSpacing(12)
        self.chk_sync_ea = QCheckBox("补齐缺失临界区")
        self.chk_sync_ea.setChecked(True)
        top.addWidget(self.chk_sync_ea)

        self.chk_add_missing = QCheckBox("补齐未注册 BSW 模块")
        self.chk_add_missing.setChecked(False)
        top.addWidget(self.chk_add_missing)

        self.chk_clean_unloaded = QCheckBox("清理未加载实例")
        self.chk_clean_unloaded.setChecked(False)
        top.addWidget(self.chk_clean_unloaded)

        self.sync_btn = QPushButton("一键同步")
        self.sync_btn.clicked.connect(self._on_sync)
        top.addWidget(self.sync_btn)

        top.addStretch()
        self.summary_label = QLabel("")
        self.summary_label.setStyleSheet("color: gray;")
        top.addWidget(self.summary_label)
        outer.addLayout(top)

        self.table = QTableWidget(0, 8)
        self.table.setHorizontalHeaderLabels([
            "模块",
            "状态",
            "SchM API 名称",
            "MemMap 头文件",
            "调度实体",
            "临界区 (已配/IB)",
            "Task 映射",
            "IB 来源",
        ])
        self.table.verticalHeader().setVisible(False)
        self.table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.table.setSelectionMode(QAbstractItemView.SingleSelection)
        self.table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        header = self.table.horizontalHeader()
        header.setSectionResizeMode(QHeaderView.Interactive)
        for col, width in enumerate((110, 145, 165, 195, 75, 115, 80, 230)):
            self.table.setColumnWidth(col, width)
        self.table.itemSelectionChanged.connect(self._update_buttons)
        outer.addWidget(self.table, 1)

        self.reload()

    def reload(self) -> None:
        self._rows = self.service.list_bsw_instance_rows()
        self.table.setRowCount(len(self._rows))

        active_cnt = sum(1 for r in self._rows if r.status == "active")
        unloaded_cnt = sum(1 for r in self._rows if r.status == "unloaded")
        unreg_cnt = sum(1 for r in self._rows if r.status == "unregistered")
        self.summary_label.setText(
            f"活跃 {active_cnt} | 未加载 {unloaded_cnt} | 未注册 {unreg_cnt}"
        )

        for r_idx, row in enumerate(self._rows):
            mod_item = QTableWidgetItem(row.module_name)
            mod_item.setData(Qt.UserRole, row)
            self.table.setItem(r_idx, 0, mod_item)

            st_text, st_color = _STATUS_LABELS.get(row.status, (row.status, QColor("black")))
            st_item = QTableWidgetItem(st_text)
            st_item.setForeground(st_color)
            self.table.setItem(r_idx, 1, st_item)

            self.table.setItem(r_idx, 2, QTableWidgetItem(row.api_name))
            self.table.setItem(r_idx, 3, QTableWidgetItem(row.memmap_header))
            self.table.setItem(r_idx, 4, QTableWidgetItem(str(row.entity_count)))
            self.table.setItem(r_idx, 5, QTableWidgetItem(f"{row.ea_configured_count} / {row.ea_ib_count}"))
            self.table.setItem(r_idx, 6, QTableWidgetItem(str(row.mapping_count)))
            self.table.setItem(r_idx, 7, QTableWidgetItem(row.ib_source or "-"))

        self._update_buttons()

    def _selected_row(self) -> Optional[BswInstanceRow]:
        r_idx = self.table.currentRow()
        if r_idx < 0:
            return None
        item = self.table.item(r_idx, 0)
        return item.data(Qt.UserRole) if item is not None else None

    def _update_buttons(self) -> None:
        row = self._selected_row()
        self.add_btn.setEnabled(row is not None and row.status == "unregistered")
        self.remove_btn.setEnabled(row is not None and row.status in ("active", "unloaded"))

    def _on_add_selected(self) -> None:
        row = self._selected_row()
        if row is None or row.status != "unregistered":
            return
        self.service.add_bsw_instance(row.module_name, populate_exclusive_areas=True)
        self.reload()
        self.config_changed.emit()

    def _on_remove_selected(self) -> None:
        row = self._selected_row()
        if row is None or row.status not in ("active", "unloaded"):
            return
        if self.service.remove_bsw_instance(row.instance_name):
            self.reload()
            self.config_changed.emit()

    def _on_sync(self) -> None:
        summary = self.service.sync_bsw_instances(
            add_missing_modules=self.chk_add_missing.isChecked(),
            sync_exclusive_areas=self.chk_sync_ea.isChecked(),
            remove_unloaded=self.chk_clean_unloaded.isChecked(),
        )
        self.reload()
        changed = bool(
            summary.added_instances or summary.added_exclusive_areas or summary.removed_instances
        )
        if changed:
            self.config_changed.emit()
        QMessageBox.information(
            self,
            "BSW 实例同步",
            f"新增实例 {summary.added_instances} 个，补齐临界区 {summary.added_exclusive_areas} 项，清理未加载实例 {summary.removed_instances} 个。",
        )


class GeneratePreviewTab(QWidget):
    """Tab 4: RteGeneration flags, live header preview, diagnostics, and standalone generation."""

    config_changed = Signal()
    generation_completed = Signal(object)

    def __init__(self, service: RteWorkbenchService, parent=None) -> None:
        super().__init__(parent)
        self.service = service
        self._reloading = False
        self._custom_output_dir: Optional[Path] = None
        self._preview_files: List[RtePreviewFile] = []

        outer = QVBoxLayout(self)

        # Global settings group
        settings_box = QGroupBox("RteGeneration / RteBswGeneral 全局配置")
        grid = QGridLayout(settings_box)

        self.chk_multi_core = QCheckBox("RteEnableMultiCore (多核支持)")
        self.chk_mem_prot = QCheckBox("RteEnableMemoryProtection (内存保护)")
        self.chk_det = QCheckBox("RteDevErrorDetect (DET 开发错误检测)")
        self.chk_det_uninit = QCheckBox("RteDevErrorDetectUninit (未初始化检测)")
        self.chk_disable_init_mem = QCheckBox("RteDisableRteInitMemory (禁用 Rte_InitMemory)")
        self.chk_vfb_trace = QCheckBox("RteVfbTraceEnabled (VFB 跟踪)")
        self.chk_schm_version_info = QCheckBox("RteSchMVersionInfoApi (SchM 版本查询 API)")

        self.combo_gen_mode = QComboBox()
        for mode in GENERATION_MODES:
            self.combo_gen_mode.addItem(mode, mode)

        self.combo_opt_mode = QComboBox()
        for mode in OPTIMIZATION_MODES:
            self.combo_opt_mode.addItem(mode, mode)

        grid.addWidget(self.chk_multi_core, 0, 0)
        grid.addWidget(self.chk_mem_prot, 0, 1)
        grid.addWidget(self.chk_det, 0, 2)
        grid.addWidget(self.chk_det_uninit, 1, 0)
        grid.addWidget(self.chk_disable_init_mem, 1, 1)
        grid.addWidget(self.chk_vfb_trace, 1, 2)
        grid.addWidget(self.chk_schm_version_info, 2, 0)

        mode_row = QHBoxLayout()
        mode_row.addWidget(QLabel("RteGenerationMode："))
        mode_row.addWidget(self.combo_gen_mode)
        grid.addLayout(mode_row, 2, 1)

        opt_row = QHBoxLayout()
        opt_row.addWidget(QLabel("RteOptimizationMode："))
        opt_row.addWidget(self.combo_opt_mode)
        grid.addLayout(opt_row, 2, 2)

        for chk in (
            self.chk_multi_core,
            self.chk_mem_prot,
            self.chk_det,
            self.chk_det_uninit,
            self.chk_disable_init_mem,
            self.chk_vfb_trace,
            self.chk_schm_version_info,
        ):
            chk.stateChanged.connect(self._on_setting_edited)
        self.combo_gen_mode.currentIndexChanged.connect(self._on_setting_edited)
        self.combo_opt_mode.currentIndexChanged.connect(self._on_setting_edited)

        outer.addWidget(settings_box)

        # Output options & action bar
        gen_bar = QHBoxLayout()
        self.output_dir_label = QLabel("")
        gen_bar.addWidget(self.output_dir_label, 1)

        self.browse_dir_btn = QPushButton("切换目录...")
        self.browse_dir_btn.clicked.connect(self._on_browse_dir)
        gen_bar.addWidget(self.browse_dir_btn)

        self.chk_type_stub = QCheckBox("生成 Rte_Type.h 桩")
        self.chk_type_stub.setChecked(True)
        self.chk_type_stub.stateChanged.connect(lambda: self.refresh_preview())
        gen_bar.addWidget(self.chk_type_stub)

        self.chk_apply_overlay = QCheckBox("应用 templates/Rte/ 覆盖层")
        self.chk_apply_overlay.setChecked(True)
        self.chk_apply_overlay.stateChanged.connect(lambda: self.refresh_preview())
        gen_bar.addWidget(self.chk_apply_overlay)

        self.chk_force = QCheckBox("强制覆写未变更文件")
        self.chk_force.setChecked(False)
        gen_bar.addWidget(self.chk_force)

        self.refresh_btn = QPushButton("刷新预览")
        self.refresh_btn.clicked.connect(lambda: self.refresh_preview())
        gen_bar.addWidget(self.refresh_btn)

        self.generate_btn = QPushButton("立即生成 RTE / SchM")
        self.generate_btn.clicked.connect(self._on_generate)
        gen_bar.addWidget(self.generate_btn)

        self.open_dir_btn = QPushButton("打开输出目录")
        self.open_dir_btn.clicked.connect(self._on_open_dir)
        gen_bar.addWidget(self.open_dir_btn)
        outer.addLayout(gen_bar)

        # Preview splitter
        splitter = QSplitter(Qt.Horizontal)

        left = QWidget()
        left_layout = QVBoxLayout(left)
        left_layout.setContentsMargins(0, 0, 0, 0)
        left_layout.addWidget(QLabel("输出文件清单"))

        self.files_table = QTableWidget(0, 3)
        self.files_table.setHorizontalHeaderLabels(["文件名", "状态", "来源"])
        self.files_table.verticalHeader().setVisible(False)
        self.files_table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.files_table.setSelectionMode(QAbstractItemView.SingleSelection)
        self.files_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        f_header = self.files_table.horizontalHeader()
        f_header.setSectionResizeMode(QHeaderView.Interactive)
        self.files_table.setColumnWidth(0, 210)
        self.files_table.setColumnWidth(1, 95)
        self.files_table.setColumnWidth(2, 75)
        self.files_table.itemSelectionChanged.connect(self._on_file_selected)
        left_layout.addWidget(self.files_table, 3)

        left_layout.addWidget(QLabel("模型诊断与告警"))
        self.diag_list = QListWidget()
        left_layout.addWidget(self.diag_list, 1)
        splitter.addWidget(left)

        right = QWidget()
        right_layout = QVBoxLayout(right)
        right_layout.setContentsMargins(0, 0, 0, 0)
        self.preview_path_label = QLabel("请选择左侧文件预览生成内容")
        self.preview_path_label.setStyleSheet("color: gray;")
        right_layout.addWidget(self.preview_path_label)

        self.preview_edit = QPlainTextEdit()
        self.preview_edit.setReadOnly(True)
        mono = QFont("Menlo")
        mono.setStyleHint(QFont.Monospace)
        mono.setPointSize(11)
        self.preview_edit.setFont(mono)
        right_layout.addWidget(self.preview_edit, 1)
        splitter.addWidget(right)

        splitter.setSizes([410, 730])
        outer.addWidget(splitter, 1)

        self.reload()

    def reload(self) -> None:
        self._load_settings()
        self.refresh_preview()

    def _load_settings(self) -> None:
        self._reloading = True
        try:
            s = self.service.read_rte_generation_settings()
            self.chk_multi_core.setChecked(s.enable_multi_core)
            self.chk_mem_prot.setChecked(s.enable_memory_protection)
            self.chk_det.setChecked(s.dev_error_detect)
            self.chk_det_uninit.setChecked(s.dev_error_detect_uninit)
            self.chk_disable_init_mem.setChecked(s.disable_rte_init_memory)
            self.chk_vfb_trace.setChecked(s.vfb_trace_enabled)
            self.chk_schm_version_info.setChecked(s.schm_version_info_api)

            if self.combo_gen_mode.findData(s.generation_mode) < 0:
                self.combo_gen_mode.addItem(s.generation_mode, s.generation_mode)
            self.combo_gen_mode.setCurrentIndex(self.combo_gen_mode.findData(s.generation_mode))

            if self.combo_opt_mode.findData(s.optimization_mode) < 0:
                self.combo_opt_mode.addItem(s.optimization_mode, s.optimization_mode)
            self.combo_opt_mode.setCurrentIndex(self.combo_opt_mode.findData(s.optimization_mode))
        finally:
            self._reloading = False

    def _collect_settings(self) -> RteGenerationSettings:
        return RteGenerationSettings(
            enable_multi_core=self.chk_multi_core.isChecked(),
            enable_memory_protection=self.chk_mem_prot.isChecked(),
            dev_error_detect=self.chk_det.isChecked(),
            dev_error_detect_uninit=self.chk_det_uninit.isChecked(),
            disable_rte_init_memory=self.chk_disable_init_mem.isChecked(),
            vfb_trace_enabled=self.chk_vfb_trace.isChecked(),
            schm_version_info_api=self.chk_schm_version_info.isChecked(),
            generation_mode=self.combo_gen_mode.currentData() or self.combo_gen_mode.currentText(),
            optimization_mode=self.combo_opt_mode.currentData() or self.combo_opt_mode.currentText(),
        )

    def _on_setting_edited(self) -> None:
        if self._reloading:
            return
        self.service.update_rte_generation_settings(self._collect_settings())
        self.refresh_preview()
        self.config_changed.emit()

    def _effective_output_root(self) -> Path:
        if self._custom_output_dir is not None:
            return self._custom_output_dir
        default_dir, _, _, _ = self.service.default_output_layout()
        return default_dir

    def refresh_preview(self) -> None:
        _, is_flat, _, _ = self.service.default_output_layout()
        out_root = self._effective_output_root()
        target_inc = out_root / ("include" if is_flat else "Rte/include")
        layout_label = "flat" if is_flat else "per-module"
        self.output_dir_label.setText(f"输出目录 ({layout_label})：{target_inc}")

        prev_filename: Optional[str] = None
        cur_row = self.files_table.currentRow()
        if 0 <= cur_row < len(self._preview_files):
            prev_filename = self._preview_files[cur_row].filename

        files, report = self.service.preview_generation(
            output_dir=out_root,
            flat=is_flat,
            generate_type_stub=self.chk_type_stub.isChecked(),
            apply_overlay=self.chk_apply_overlay.isChecked(),
        )
        self._preview_files = files

        self.files_table.setRowCount(len(files))
        reselect_row = 0 if files else -1
        for r_idx, pf in enumerate(files):
            name_item = QTableWidgetItem(pf.filename)
            name_item.setData(Qt.UserRole, pf)
            self.files_table.setItem(r_idx, 0, name_item)

            st_text, st_color = _PREVIEW_STATUS_LABELS.get(pf.status, (pf.status, QColor("black")))
            st_item = QTableWidgetItem(st_text)
            st_item.setForeground(st_color)
            self.files_table.setItem(r_idx, 1, st_item)

            self.files_table.setItem(r_idx, 2, QTableWidgetItem(pf.source))
            if prev_filename and pf.filename == prev_filename:
                reselect_row = r_idx

        self.diag_list.clear()
        for err in report.errors:
            item = QListWidgetItem(f"[错误] {err}")
            item.setForeground(_ERROR_COLOR)
            self.diag_list.addItem(item)
        for warn in report.warnings:
            item = QListWidgetItem(f"[告警] {warn}")
            item.setForeground(_WARN_COLOR)
            self.diag_list.addItem(item)
        if not report.errors and not report.warnings:
            item = QListWidgetItem("校验通过：无错误或告警")
            item.setForeground(_OK_COLOR)
            self.diag_list.addItem(item)

        self.generate_btn.setEnabled(not report.errors)
        if reselect_row >= 0:
            self.files_table.selectRow(reselect_row)
            self._show_preview_row(reselect_row)
        else:
            self.preview_path_label.setText("无预览文件")
            self.preview_edit.clear()

    def _on_file_selected(self) -> None:
        r_idx = self.files_table.currentRow()
        if r_idx >= 0:
            self._show_preview_row(r_idx)

    def _show_preview_row(self, row_idx: int) -> None:
        if not (0 <= row_idx < len(self._preview_files)):
            return
        pf = self._preview_files[row_idx]
        self.preview_path_label.setText(f"{pf.target_path} ({pf.status} / {pf.source})")
        self.preview_edit.setPlainText(pf.content)

    def _on_browse_dir(self) -> None:
        chosen = QFileDialog.getExistingDirectory(
            self,
            "选择 RTE / SchM 生成输出目录",
            str(self._effective_output_root()),
        )
        if chosen:
            self._custom_output_dir = Path(chosen)
            self.refresh_preview()

    def _on_generate(self) -> None:
        out_root = self._effective_output_root()
        ok, report, detail = self.service.run_generation(
            output_dir=out_root,
            generate_type_stub=self.chk_type_stub.isChecked(),
            force=self.chk_force.isChecked(),
            apply_overlay=self.chk_apply_overlay.isChecked(),
        )
        self.refresh_preview()
        if not ok:
            QMessageBox.critical(
                self,
                "RTE / SchM 生成失败",
                f"生成失败：\n{detail or '; '.join(report.errors)}",
            )
            return
        self.generation_completed.emit(report)
        QMessageBox.information(
            self,
            "RTE / SchM 生成完成",
            f"生成成功！\n写入 {len(report.generated_files)} 个文件，未变 {len(report.unchanged_files)} 个，保留桩 {len(report.preserved_files)} 个。"
            + (f"\n\n提示：{detail}" if detail else ""),
        )

    def _on_open_dir(self) -> None:
        _, is_flat, _, _ = self.service.default_output_layout()
        target = self._effective_output_root() / ("include" if is_flat else "Rte/include")
        if not target.exists():
            target = self._effective_output_root()
        if not target.exists():
            QMessageBox.information(self, "打开输出目录", f"输出目录尚未生成：\n{target}")
            return
        QDesktopServices.openUrl(QUrl.fromLocalFile(str(target)))


class RteSchmWorkbench(QDialog):
    """4-tab graphical RTE / SchM configuration and standalone generation workbench."""

    config_changed = Signal()
    generation_completed = Signal(object)

    def __init__(self, project, parent=None) -> None:
        super().__init__(parent)
        self.project = project
        self.service = RteWorkbenchService(project)

        self.setWindowTitle("RTE / SchM 配置与生成工作台")
        self.resize(1180, 760)

        root = QVBoxLayout(self)

        header = QHBoxLayout()
        proj_name = getattr(project, "name", "Project")
        self.header_summary_label = QLabel(f"工程：{proj_name}")
        header.addWidget(self.header_summary_label, 1)
        root.addLayout(header)

        self.tabs = QTabWidget()
        self.modules_tab = BswInstancesTab(self.service, self)
        self.ea_tab = ExclusiveAreasTab(self.service, self)
        self.task_tab = TaskMappingTab(self.service, self)
        self.generate_tab = GeneratePreviewTab(self.service, self)

        self.tabs.addTab(self.modules_tab, "1. BSW 实例与同步")
        self.tabs.addTab(self.ea_tab, "2. 临界区矩阵 (SchM)")
        self.tabs.addTab(self.task_tab, "3. Task 调度映射")
        self.tabs.addTab(self.generate_tab, "4. 全局开关与生成预览")
        root.addWidget(self.tabs, 1)

        bottom = QHBoxLayout()
        bottom.addStretch()
        self.close_btn = QPushButton("关闭")
        self.close_btn.clicked.connect(self.accept)
        bottom.addWidget(self.close_btn)
        root.addLayout(bottom)

        self.modules_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.modules_tab))
        self.ea_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.ea_tab))
        self.task_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.task_tab))
        self.generate_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.generate_tab))
        self.generate_tab.generation_completed.connect(self.generation_completed.emit)

        self._update_header_summary()

    def _on_tab_config_changed(self, source: QWidget) -> None:
        if source is not self.modules_tab:
            self.modules_tab.reload()
        if source is not self.ea_tab:
            self.ea_tab.reload()
        if source is not self.task_tab:
            self.task_tab.reload()
        if source is not self.generate_tab:
            self.generate_tab.reload()
        self._update_header_summary()
        self.config_changed.emit()

    def _update_header_summary(self) -> None:
        proj_name = getattr(self.project, "name", "Project")
        rows = self.modules_tab._rows
        active = sum(1 for r in rows if r.status == "active")
        unloaded = sum(1 for r in rows if r.status == "unloaded")
        ea_rows = self.ea_tab._rows
        ea_err = sum(1 for r in ea_rows if r.validation_error)
        self.header_summary_label.setText(
            f"工程：{proj_name}  |  活跃 BSW 实例：{active}  |  未加载：{unloaded}  |  临界区：{len(ea_rows)}（错误 {ea_err}）"
        )
