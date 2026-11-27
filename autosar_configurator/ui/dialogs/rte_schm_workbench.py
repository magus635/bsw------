"""4-tab RTE / SchM Configuration & Generation Workbench."""

import logging
import re
from pathlib import Path
from typing import List, Optional, Tuple

from PySide6.QtCore import Qt, QUrl, Signal
from PySide6.QtGui import QColor, QDesktopServices, QFont, QSyntaxHighlighter, QTextCharFormat
from PySide6.QtWidgets import (
    QAbstractItemView,
    QCheckBox,
    QComboBox,
    QDialog,
    QDialogButtonBox,
    QFileDialog,
    QFrame,
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
    QTextBrowser,
    QVBoxLayout,
    QWidget,
)

from ...core.config_manager import PreLockedError
from ...generator.rte.model import RtePreviewFile
from ...generator.rte.workbench_service import (
    BswInstanceRow,
    GENERATION_MODES,
    OPTIMIZATION_MODES,
    RteGenerationSettings,
    RteWorkbenchService,
    compute_preview_diff,
)
from .rte_schm_phase23_tabs import DataMappingTab, ServiceMappingTab
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

_STAGE3_DIAG_CODES = frozenset({
    "MIXED_TASK_PERIOD",
    "EXTENDED_TASK_MISSING_EVENT",
    "DANGLING_OS_EVENT",
    "ACTIVATION_MISSING_SOURCE",
    "DANGLING_OS_ACTIVATION",
    "ACTIVATION_PERIOD_MISMATCH",
    "TASK_MISSING_ACTIVATION",
    "MISSING_OS_TASK",
})

_FALLBACK_GUIDE_MD = """# RTE / SchM 配置与生成工作台使用指南

1. **页签 1（BSW 实例与同步）**：检查活跃、未加载与未注册 BSW 模块，勾选需要项后点击 **一键同步**。
2. **页签 2（临界区矩阵）**：为各 ExclusiveArea 选择保护机制（初学者建议保持 `ALL_INTERRUPT_BLOCKING`），若选 `OS_RESOURCE` / `OS_SPINLOCK` 需同时选择目标 OS 对象。
3. **页签 3（Task 调度映射）**：支持 `Ctrl`/`Shift` 多选未映射 BSW 事件并查看智能周期推荐，点击 **映射到选中 Task**；勾选 **编辑 SWC 事件映射** 后也可调整 SWC Runnable 在各 Task 中的顺序。
4. **页签 4（数据映射 SWC↔Com）**：查看与编辑 SWC Sender/Receiver 端口与 `ComSignal` 的绑定关系，支持一键按信号名/方向自动匹配（写入 `.dpa` 覆盖层，不修改只读 System ARXML）。
5. **页签 5（服务与端口连接）**：连接 ServiceComponent（`ComM`/`EcuM`/`BswM`/`Det` 等）与 Client-Server / Mode / SWC 核间端口，查看双核 `OsApplication` 分区总览。
6. **页签 6（全局开关与生成预览）**：配置 `RteGeneration` 开关，预览阶段 1 头文件与阶段 2/3 SWC 契约头（`Components/Rte_*.h`）及多核 `Rte.c` / `Rte_<OsApp>.c` 源码，确认无误后点击 **立即生成 RTE / SchM**。
7. **保存与撤销**：点击 **确定** 会推入主窗口撤销栈（`Ctrl+Z` / `Cmd+Z`），点击 **取消** 或 **恢复打开前状态** 会一键回滚（含数据映射与服务连接覆盖层）。
"""


class CAndDiffHighlighter(QSyntaxHighlighter):
    """Lightweight C/AUTOSAR syntax highlighter with optional unified-diff highlighting mode."""

    def __init__(self, document) -> None:
        super().__init__(document)
        self._diff_mode = False

        self._diff_header_fmt = QTextCharFormat()
        self._diff_header_fmt.setForeground(QColor("#555555"))
        self._diff_header_fmt.setFontWeight(QFont.Bold)

        self._diff_hunk_fmt = QTextCharFormat()
        self._diff_hunk_fmt.setForeground(QColor("#6a1b9a"))
        self._diff_hunk_fmt.setFontWeight(QFont.Bold)

        self._diff_add_fmt = QTextCharFormat()
        self._diff_add_fmt.setForeground(QColor("#1b7f37"))
        self._diff_add_fmt.setBackground(QColor("#e8f5e9"))

        self._diff_del_fmt = QTextCharFormat()
        self._diff_del_fmt.setForeground(QColor("#b00020"))
        self._diff_del_fmt.setBackground(QColor("#ffebee"))

        pp_fmt = QTextCharFormat()
        pp_fmt.setForeground(QColor("#7b1fa2"))
        pp_fmt.setFontWeight(QFont.Bold)

        kw_fmt = QTextCharFormat()
        kw_fmt.setForeground(QColor("#1565c0"))
        kw_fmt.setFontWeight(QFont.Bold)

        str_fmt = QTextCharFormat()
        str_fmt.setForeground(QColor("#a31515"))

        num_fmt = QTextCharFormat()
        num_fmt.setForeground(QColor("#098658"))

        self._comment_fmt = QTextCharFormat()
        self._comment_fmt.setForeground(QColor("#5c7a5c"))
        self._comment_fmt.setFontItalic(True)

        self._c_rules: List[Tuple[re.Pattern, QTextCharFormat]] = [
            (
                re.compile(
                    r"^\s*#\s*(?:include|define|undef|ifdef|ifndef|if|elif|else|endif|error|pragma)\b"
                ),
                pp_fmt,
            ),
            (
                re.compile(
                    r"\b(?:void|const|extern|static|typedef|struct|enum|union|unsigned|signed|"
                    r"int|char|short|long|return|if|else|while|for|FUNC|P2VAR|P2CONST|VAR|CONST|STATIC|INLINE)\b"
                ),
                kw_fmt,
            ),
            (re.compile(r'"[^"\n]*"'), str_fmt),
            (re.compile(r"(?<=#include)\s*<[^>\n]+>"), str_fmt),
            (re.compile(r"\b(?:0x[0-9A-Fa-f]+|[0-9]+[uUlL]*)\b"), num_fmt),
            (re.compile(r"//[^\n]*"), self._comment_fmt),
        ]
        self._block_comment_start = re.compile(r"/\*")
        self._block_comment_end = re.compile(r"\*/")

    def set_diff_mode(self, enabled: bool) -> None:
        if self._diff_mode != enabled:
            self._diff_mode = enabled
            self.rehighlight()

    def highlightBlock(self, text: str) -> None:
        if self._diff_mode:
            self.setCurrentBlockState(0)
            if text.startswith("+++") or text.startswith("---"):
                self.setFormat(0, len(text), self._diff_header_fmt)
            elif text.startswith("@@"):
                self.setFormat(0, len(text), self._diff_hunk_fmt)
            elif text.startswith("+"):
                self.setFormat(0, len(text), self._diff_add_fmt)
            elif text.startswith("-"):
                self.setFormat(0, len(text), self._diff_del_fmt)
            return

        for pattern, fmt in self._c_rules:
            for match in pattern.finditer(text):
                self.setFormat(match.start(), match.end() - match.start(), fmt)

        self.setCurrentBlockState(0)
        start_idx = 0
        if self.previousBlockState() != 1:
            m = self._block_comment_start.search(text)
            start_idx = m.start() if m else -1
        while start_idx >= 0:
            end_m = self._block_comment_end.search(text, start_idx + 2)
            if end_m is not None:
                comment_len = end_m.end() - start_idx
                self.setFormat(start_idx, comment_len, self._comment_fmt)
                next_m = self._block_comment_start.search(text, end_m.end())
                start_idx = next_m.start() if next_m else -1
            else:
                self.setCurrentBlockState(1)
                self.setFormat(start_idx, len(text) - start_idx, self._comment_fmt)
                break


class RteSchmGuideDialog(QDialog):
    """Built-in documentation dialog rendering ``docs/RTE_SCHM_WORKBENCH_GUIDE.md``."""

    def __init__(self, parent=None) -> None:
        super().__init__(parent)
        self.setWindowTitle("RTE / SchM 工作台使用指南")
        self.setMinimumSize(860, 640)

        layout = QVBoxLayout(self)
        self.browser = QTextBrowser()
        self.browser.setOpenExternalLinks(True)
        self.browser.setMarkdown(self._load_guide_markdown())
        layout.addWidget(self.browser, 1)

        buttons = QDialogButtonBox(QDialogButtonBox.Close)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)

    @staticmethod
    def _load_guide_markdown() -> str:
        guide_path = Path(__file__).resolve().parents[3] / "docs" / "RTE_SCHM_WORKBENCH_GUIDE.md"
        if guide_path.is_file():
            try:
                return guide_path.read_text(encoding="utf-8")
            except OSError:
                pass
        return _FALLBACK_GUIDE_MD


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
        try:
            self.service.add_bsw_instance(row.module_name, populate_exclusive_areas=True)
        except PreLockedError as exc:
            QMessageBox.warning(self, "受基线 Pre 锁保护", f"无法添加实例 '{row.module_name}'：\n{exc}")
            return
        self.reload()
        self.config_changed.emit()

    def _on_remove_selected(self) -> None:
        row = self._selected_row()
        if row is None or row.status not in ("active", "unloaded"):
            return
        try:
            removed = self.service.remove_bsw_instance(row.instance_name)
        except PreLockedError as exc:
            QMessageBox.warning(self, "受基线 Pre 锁保护", f"无法移除实例 '{row.instance_name}'：\n{exc}")
            return
        if removed:
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
        msg = (
            f"新增实例 {summary.added_instances} 个，"
            f"补齐临界区 {summary.added_exclusive_areas} 项，"
            f"清理未加载实例 {summary.removed_instances} 个。"
        )
        if summary.skipped_locked:
            msg += f"\n\n跳过受 Pre 锁保护项：{len(summary.skipped_locked)} 处。"
        QMessageBox.information(self, "BSW 实例同步", msg)


class GeneratePreviewTab(QWidget):
    """Tab 4: RteGeneration flags, live header preview, diagnostics, and standalone generation."""

    config_changed = Signal()
    generation_completed = Signal(object)
    memmap_settings_changed = Signal()

    def __init__(self, service: RteWorkbenchService, parent=None) -> None:
        super().__init__(parent)
        self.service = service
        self._reloading = False
        self._custom_output_dir: Optional[Path] = None
        self._preview_files: List[RtePreviewFile] = []

        outer = QVBoxLayout(self)

        # Global settings split into Phase-1 active vs ECUC-only groups
        phase1_box = QGroupBox("阶段 1 生效开关（实时影响 Rte_Main.h 生成结果）")
        phase1_row = QHBoxLayout(phase1_box)
        self.chk_multi_core = QCheckBox("RteEnableMultiCore (多核支持)")
        self.chk_disable_init_mem = QCheckBox("RteDisableRteInitMemory (禁用 Rte_InitMemory)")
        phase1_row.addWidget(self.chk_multi_core)
        phase1_row.addWidget(self.chk_disable_init_mem)
        phase1_row.addStretch()
        outer.addWidget(phase1_box)

        ecuc_box = QGroupBox("ECUC 预留参数（写入 Rte.arxml，供后续阶段 2/3 或外部生成器使用，不改变阶段 1 预览）")
        grid = QGridLayout(ecuc_box)

        self.chk_mem_prot = QCheckBox("RteEnableMemoryProtection (内存保护)")
        self.chk_det = QCheckBox("RteDevErrorDetect (DET 开发错误检测)")
        self.chk_det_uninit = QCheckBox("RteDevErrorDetectUninit (未初始化检测)")
        self.chk_vfb_trace = QCheckBox("RteVfbTraceEnabled (VFB 跟踪)")
        self.chk_schm_version_info = QCheckBox("RteSchMVersionInfoApi (SchM 版本查询 API)")

        self.combo_gen_mode = QComboBox()
        for mode in GENERATION_MODES:
            self.combo_gen_mode.addItem(mode, mode)

        self.combo_opt_mode = QComboBox()
        for mode in OPTIMIZATION_MODES:
            self.combo_opt_mode.addItem(mode, mode)

        grid.addWidget(self.chk_mem_prot, 0, 0)
        grid.addWidget(self.chk_det, 0, 1)
        grid.addWidget(self.chk_det_uninit, 0, 2)
        grid.addWidget(self.chk_vfb_trace, 1, 0)
        grid.addWidget(self.chk_schm_version_info, 1, 1)

        mode_row = QHBoxLayout()
        mode_row.addWidget(QLabel("RteGenerationMode："))
        mode_row.addWidget(self.combo_gen_mode)
        grid.addLayout(mode_row, 2, 0)

        opt_row = QHBoxLayout()
        opt_row.addWidget(QLabel("RteOptimizationMode："))
        opt_row.addWidget(self.combo_opt_mode)
        grid.addLayout(opt_row, 2, 1)

        for chk in (self.chk_multi_core, self.chk_disable_init_mem):
            chk.stateChanged.connect(lambda _s=None: self._on_setting_edited(affect_phase1=True))
        for chk in (
            self.chk_mem_prot,
            self.chk_det,
            self.chk_det_uninit,
            self.chk_vfb_trace,
            self.chk_schm_version_info,
        ):
            chk.stateChanged.connect(lambda _s=None: self._on_setting_edited(affect_phase1=False))
        self.combo_gen_mode.currentIndexChanged.connect(
            lambda _i=None: self._on_setting_edited(affect_phase1=False)
        )
        self.combo_opt_mode.currentIndexChanged.connect(
            lambda _i=None: self._on_setting_edited(affect_phase1=False)
        )

        outer.addWidget(ecuc_box)

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

        self.chk_phase2_3 = QCheckBox("生成阶段 2/3 SWC 契约与 Rte.c")
        self.chk_phase2_3.setChecked(True)
        self.chk_phase2_3.setToolTip("同时生成 Components/Rte_<Swc>.h、Rte_Type.h 完整定义、Rte.c 与按核划分的 Rte_<OsApp>.c")
        self.chk_phase2_3.stateChanged.connect(lambda: self.refresh_preview())
        gen_bar.addWidget(self.chk_phase2_3)

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

        self.check_memmap_btn = QPushButton("在内存映射工作台中校验")
        self.check_memmap_btn.setToolTip("打开内存映射工作台扫描生成的 SchM_*.h 与 MemMap.h 段定义")
        self.check_memmap_btn.clicked.connect(self._on_check_memmap)
        gen_bar.addWidget(self.check_memmap_btn)
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
        preview_header = QHBoxLayout()
        self.preview_path_label = QLabel("请选择左侧文件预览生成内容")
        self.preview_path_label.setStyleSheet("color: gray;")
        preview_header.addWidget(self.preview_path_label, 1)
        self.chk_diff_mode = QCheckBox("仅看差异 (Diff)")
        self.chk_diff_mode.setChecked(False)
        self.chk_diff_mode.stateChanged.connect(self._on_diff_mode_toggled)
        preview_header.addWidget(self.chk_diff_mode)
        right_layout.addLayout(preview_header)

        self.preview_edit = QPlainTextEdit()
        self.preview_edit.setReadOnly(True)
        mono = QFont("Menlo")
        mono.setStyleHint(QFont.Monospace)
        mono.setPointSize(11)
        self.preview_edit.setFont(mono)
        self.preview_highlighter = CAndDiffHighlighter(self.preview_edit.document())
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

    def _on_setting_edited(self, *, affect_phase1: bool = True) -> None:
        if self._reloading:
            return
        try:
            self.service.update_rte_generation_settings(self._collect_settings())
        except PreLockedError as exc:
            QMessageBox.warning(
                self,
                "受基线 Pre 锁保护",
                f"无法修改全局配置参数：\n{exc}\n\n请先在主界面属性面板中解锁对应 Pre 项。",
            )
            self._load_settings()
            return
        if affect_phase1:
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
            include_phase2_3=self.chk_phase2_3.isChecked(),
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
        stage3_warnings = [
            d.message
            for d in self.service.collect_diagnostics()
            if d.workbench_tab == 2 and d.code in _STAGE3_DIAG_CODES
        ]
        for s3_warn in stage3_warnings:
            item = QListWidgetItem(f"[阶段3调度告警] {s3_warn}")
            item.setForeground(_WARN_COLOR)
            self.diag_list.addItem(item)
        if not report.errors and not report.warnings and not stage3_warnings:
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

    def _on_diff_mode_toggled(self, _state=None) -> None:
        r_idx = self.files_table.currentRow()
        if 0 <= r_idx < len(self._preview_files):
            self._show_preview_row(r_idx)
        else:
            self.preview_highlighter.set_diff_mode(self.chk_diff_mode.isChecked())

    def _show_preview_row(self, row_idx: int) -> None:
        if not (0 <= row_idx < len(self._preview_files)):
            return
        pf = self._preview_files[row_idx]
        diff_mode = self.chk_diff_mode.isChecked()
        self.preview_highlighter.set_diff_mode(diff_mode)
        if diff_mode:
            self.preview_path_label.setText(f"[Diff] {pf.target_path} ({pf.status} / {pf.source})")
            self.preview_edit.setPlainText(compute_preview_diff(pf))
        else:
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
            include_phase2_3=self.chk_phase2_3.isChecked(),
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

    def _on_check_memmap(self) -> None:
        out_root = self._effective_output_root()
        if not out_root.is_dir():
            QMessageBox.information(
                self,
                "内存映射校验",
                f"目标输出目录尚未生成：\n{out_root}\n\n请先点击「立即生成 RTE / SchM」产出头文件后再校验。",
            )
            return
        from .memory_map_workbench import MemoryMapWorkbench

        dlg = MemoryMapWorkbench(self.service.project, parent=self, auto_scan=True)
        if self._custom_output_dir is not None:
            default_dir, _, _, _ = self.service.default_output_layout()
            if self._custom_output_dir.resolve() != default_dir.resolve():
                dlg.source_dirs.add(str(self._custom_output_dir))
        dlg.settings_changed.connect(self.memmap_settings_changed.emit)
        dlg.exec()


class RteSchmWorkbench(QDialog):
    """4-tab graphical RTE / SchM configuration and standalone generation workbench."""

    config_changed = Signal()
    generation_completed = Signal(object)
    memmap_settings_changed = Signal()

    def __init__(self, project, parent=None) -> None:
        super().__init__(parent)
        self.project = project
        self.service = RteWorkbenchService(project)
        self.initial_snapshot = self.service.capture_snapshot()
        self.has_edits = False
        self._dirty_tabs = set()

        self.setWindowTitle("RTE / SchM 配置与生成工作台")
        self.resize(1180, 760)

        root = QVBoxLayout(self)

        header = QHBoxLayout()
        proj_name = getattr(project, "name", "Project")
        self.header_summary_label = QLabel(f"工程：{proj_name}")
        header.addWidget(self.header_summary_label, 1)

        active_var = getattr(project, "active_variant", None)
        self.variant_notice_label = QLabel()
        self.variant_notice_label.setStyleSheet("color: #a65e00; font-weight: bold;")
        if active_var and active_var != "Default":
            self.variant_notice_label.setText(f"当前变体：{active_var}（工作台修改作用于基础层）")
        else:
            self.variant_notice_label.hide()
        header.addWidget(self.variant_notice_label)

        self.reload_ib_btn = QPushButton("重新扫描 IB")
        self.reload_ib_btn.clicked.connect(lambda: self.reload_all(rescan_ib=True))
        header.addWidget(self.reload_ib_btn)
        root.addLayout(header)

        self.health_bar = QFrame()
        self.health_bar.setStyleSheet(
            "QFrame { background-color: #f6f8fa; border: 1px solid #d0d7de; border-radius: 4px; }"
        )
        hb_layout = QHBoxLayout(self.health_bar)
        hb_layout.setContentsMargins(8, 4, 8, 4)
        hb_layout.setSpacing(6)
        hb_title = QLabel("健康检查：")
        hb_title.setStyleSheet("font-weight: bold; border: none;")
        hb_layout.addWidget(hb_title)

        self.health_ok_label = QLabel("✅ 当前配置健康，可直接预览并生成头文件")
        self.health_ok_label.setStyleSheet("color: #1b7f37; border: none;")
        hb_layout.addWidget(self.health_ok_label)

        self.btn_fix_ea_errors = QPushButton()
        self.btn_fix_ea_errors.setStyleSheet(
            "QPushButton { color: #b00020; background: #ffebee; border: 1px solid #f5c2c7; border-radius: 3px; padding: 2px 8px; }"
        )
        self.btn_fix_ea_errors.clicked.connect(self._jump_to_ea_issues)
        hb_layout.addWidget(self.btn_fix_ea_errors)

        self.btn_clean_unloaded = QPushButton()
        self.btn_clean_unloaded.setStyleSheet(
            "QPushButton { color: #8a4b00; background: #fff4e5; border: 1px solid #f5d09c; border-radius: 3px; padding: 2px 8px; }"
        )
        self.btn_clean_unloaded.clicked.connect(self._jump_to_unloaded_instances)
        hb_layout.addWidget(self.btn_clean_unloaded)

        self.btn_sync_missing_ea = QPushButton()
        self.btn_sync_missing_ea.setStyleSheet(
            "QPushButton { color: #8a4b00; background: #fff4e5; border: 1px solid #f5d09c; border-radius: 3px; padding: 2px 8px; }"
        )
        self.btn_sync_missing_ea.clicked.connect(self._quick_sync_missing_eas)
        hb_layout.addWidget(self.btn_sync_missing_ea)

        self.btn_assign_unmapped = QPushButton()
        self.btn_assign_unmapped.setStyleSheet(
            "QPushButton { color: #1f5fbf; background: #eef4ff; border: 1px solid #b6d0ff; border-radius: 3px; padding: 2px 8px; }"
        )
        self.btn_assign_unmapped.clicked.connect(self._jump_to_unmapped_events)
        hb_layout.addWidget(self.btn_assign_unmapped)

        self.btn_fix_data_map = QPushButton()
        self.btn_fix_data_map.setStyleSheet(
            "QPushButton { color: #b00020; background: #ffebee; border: 1px solid #f5c2c7; border-radius: 3px; padding: 2px 8px; }"
        )
        self.btn_fix_data_map.clicked.connect(self._jump_to_data_mapping)
        hb_layout.addWidget(self.btn_fix_data_map)

        self.btn_fix_service_map = QPushButton()
        self.btn_fix_service_map.setStyleSheet(
            "QPushButton { color: #8a4b00; background: #fff4e5; border: 1px solid #f5d09c; border-radius: 3px; padding: 2px 8px; }"
        )
        self.btn_fix_service_map.clicked.connect(self._jump_to_service_mapping)
        hb_layout.addWidget(self.btn_fix_service_map)

        hb_layout.addStretch()
        self.btn_goto_generate = QPushButton("前往生成预览 →")
        self.btn_goto_generate.clicked.connect(lambda: self.tabs.setCurrentWidget(self.generate_tab))
        hb_layout.addWidget(self.btn_goto_generate)
        root.addWidget(self.health_bar)

        self.tabs = QTabWidget()
        self.modules_tab = BswInstancesTab(self.service, self)
        self.ea_tab = ExclusiveAreasTab(self.service, self)
        self.task_tab = TaskMappingTab(self.service, self)
        self.data_mapping_tab = DataMappingTab(self.service, self)
        self.service_mapping_tab = ServiceMappingTab(self.service, self)
        self.generate_tab = GeneratePreviewTab(self.service, self)

        self.tabs.addTab(self.modules_tab, "1. BSW 实例与同步")
        self.tabs.addTab(self.ea_tab, "2. 临界区矩阵 (SchM)")
        self.tabs.addTab(self.task_tab, "3. Task 调度映射")
        self.tabs.addTab(self.data_mapping_tab, "4. 数据映射 (SWC↔Com)")
        self.tabs.addTab(self.service_mapping_tab, "5. 服务与端口连接")
        self.tabs.addTab(self.generate_tab, "6. 全局开关与生成预览")
        self.tabs.currentChanged.connect(self._on_current_tab_changed)
        root.addWidget(self.tabs, 1)

        bottom = QHBoxLayout()
        self.revert_btn = QPushButton("恢复打开前状态")
        self.revert_btn.setEnabled(False)
        self.revert_btn.clicked.connect(self._on_revert)
        bottom.addWidget(self.revert_btn)
        self.help_btn = QPushButton("使用说明 (?)")
        self.help_btn.clicked.connect(self._on_open_help)
        bottom.addWidget(self.help_btn)
        bottom.addStretch()
        self.cancel_btn = QPushButton("取消")
        self.cancel_btn.clicked.connect(self.reject)
        bottom.addWidget(self.cancel_btn)
        self.ok_btn = QPushButton("确定")
        self.ok_btn.setDefault(True)
        self.ok_btn.clicked.connect(self.accept)
        bottom.addWidget(self.ok_btn)
        self.close_btn = self.ok_btn
        root.addLayout(bottom)

        self.modules_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.modules_tab))
        self.ea_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.ea_tab))
        self.task_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.task_tab))
        self.data_mapping_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.data_mapping_tab))
        self.service_mapping_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.service_mapping_tab))
        self.generate_tab.config_changed.connect(lambda: self._on_tab_config_changed(self.generate_tab))
        self.generate_tab.generation_completed.connect(self.generation_completed.emit)
        self.generate_tab.memmap_settings_changed.connect(self.memmap_settings_changed.emit)

        self._update_header_summary()

    def select_tab(self, index: int) -> None:
        if 0 <= index < self.tabs.count():
            self.tabs.setCurrentIndex(index)

    def reload_all(self, *, rescan_ib: bool = False) -> None:
        if rescan_ib:
            self.service.reload_ib_index()
            self.service.reload_swc_index()
        self._dirty_tabs.clear()
        self.modules_tab.reload()
        self.ea_tab.reload()
        self.task_tab.reload()
        self.data_mapping_tab.reload()
        self.service_mapping_tab.reload()
        self.generate_tab.reload()
        self._update_header_summary()

    def _on_current_tab_changed(self, _index: int) -> None:
        cur = self.tabs.currentWidget()
        if cur in self._dirty_tabs:
            self._dirty_tabs.discard(cur)
            if cur is self.generate_tab:
                cur.refresh_preview()
            elif hasattr(cur, "reload"):
                cur.reload()

    def _on_tab_config_changed(self, source: QWidget) -> None:
        self.has_edits = True
        self.revert_btn.setEnabled(True)

        if source is self.modules_tab:
            self.ea_tab.reload()
            if self.tabs.currentWidget() is self.task_tab:
                self.task_tab.reload()
            else:
                self._dirty_tabs.add(self.task_tab)
            self.generate_tab.refresh_preview()
        elif source is self.ea_tab:
            self.modules_tab.reload()
            self.generate_tab.refresh_preview()
        elif source is self.task_tab:
            self.modules_tab.reload()
            self._dirty_tabs.add(self.service_mapping_tab)
            self._dirty_tabs.add(self.generate_tab)
        elif source is self.data_mapping_tab:
            self._dirty_tabs.add(self.service_mapping_tab)
            self._dirty_tabs.add(self.generate_tab)
        elif source is self.service_mapping_tab:
            self._dirty_tabs.add(self.data_mapping_tab)
            self._dirty_tabs.add(self.generate_tab)
        elif source is self.generate_tab:
            pass

        self._update_header_summary()
        self.config_changed.emit()

    def _on_revert(self) -> None:
        if self.initial_snapshot is not None:
            self.service.restore_snapshot(self.initial_snapshot)
        self.has_edits = False
        self.revert_btn.setEnabled(False)
        self.reload_all(rescan_ib=False)

    def reject(self) -> None:
        if self.has_edits and self.initial_snapshot is not None:
            self.service.restore_snapshot(self.initial_snapshot)
            self.has_edits = False
        super().reject()

    def _on_open_help(self) -> None:
        RteSchmGuideDialog(self).exec()

    def _jump_to_ea_issues(self) -> None:
        self.tabs.setCurrentWidget(self.ea_tab)
        self.ea_tab.module_filter.setCurrentIndex(0)
        self.ea_tab.search_edit.clear()
        self.ea_tab.only_issues_check.setChecked(True)

    def _jump_to_unloaded_instances(self) -> None:
        self.tabs.setCurrentWidget(self.modules_tab)
        for r_idx, row in enumerate(self.modules_tab._rows):
            if row.status == "unloaded":
                self.modules_tab.table.selectRow(r_idx)
                break

    def _quick_sync_missing_eas(self) -> None:
        self.tabs.setCurrentWidget(self.ea_tab)
        self.ea_tab._on_sync_missing()

    def _jump_to_unmapped_events(self) -> None:
        self.tabs.setCurrentWidget(self.task_tab)
        self.task_tab.filter_edit.clear()
        if self.task_tab.unmapped_table.rowCount() > 0:
            self.task_tab.unmapped_table.selectRow(0)

    def _jump_to_data_mapping(self) -> None:
        self.tabs.setCurrentWidget(self.data_mapping_tab)
        idx = self.data_mapping_tab.status_combo.findData("errors")
        if idx >= 0:
            self.data_mapping_tab.status_combo.setCurrentIndex(idx)

    def _jump_to_service_mapping(self) -> None:
        self.tabs.setCurrentWidget(self.service_mapping_tab)
        self.service_mapping_tab.only_issues_check.setChecked(True)

    def _update_header_summary(self) -> None:
        proj_name = getattr(self.project, "name", "Project")
        rows = self.modules_tab._rows
        active = sum(1 for r in rows if r.status == "active")
        unloaded = sum(1 for r in rows if r.status == "unloaded")
        ea_rows = self.ea_tab._rows
        ea_err = sum(1 for r in ea_rows if r.validation_error)
        ea_unconf = sum(1 for r in ea_rows if not r.configured)
        if self.task_tab in self._dirty_tabs:
            _, unmapped_rows = self.service.list_task_mappings(include_swc=False)
            unmapped_cnt = len(unmapped_rows)
        else:
            unmapped_cnt = sum(1 for r in self.task_tab._unmapped if not r.is_swc)

        dm_rows = self.service.list_data_mapping_rows() if self.data_mapping_tab in self._dirty_tabs else self.data_mapping_tab._all_rows
        dm_err = sum(1 for r in dm_rows if r.status in ("broken_com", "direction_mismatch"))
        sp_rows = self.service.list_service_port_rows() if self.service_mapping_tab in self._dirty_tabs else self.service_mapping_tab._all_ports
        sp_issues = sum(1 for r in sp_rows if r.status == "broken" or (r.status == "unconnected" and (r.is_service or r.interface_kind in ("CS", "MODE"))))

        self.header_summary_label.setText(
            f"工程：{proj_name}  |  活跃 BSW 实例：{active}  |  未加载：{unloaded}  |  临界区：{len(ea_rows)}（错误 {ea_err}）"
        )

        self.btn_fix_ea_errors.setText(f"❌ {ea_err} 个临界区报错 [去修复]")
        self.btn_fix_ea_errors.setVisible(ea_err > 0)

        self.btn_clean_unloaded.setText(f"⚠️ {unloaded} 个未加载实例 [去清理]")
        self.btn_clean_unloaded.setVisible(unloaded > 0)

        self.btn_sync_missing_ea.setText(f"⚠️ {ea_unconf} 个未同步临界区 [一键同步]")
        self.btn_sync_missing_ea.setVisible(ea_unconf > 0)

        self.btn_assign_unmapped.setText(f"ℹ️ {unmapped_cnt} 个未映射事件 [去分配]")
        self.btn_assign_unmapped.setVisible(unmapped_cnt > 0)

        self.btn_fix_data_map.setText(f"❌ {dm_err} 个数据映射冲突 [去绑定]")
        self.btn_fix_data_map.setVisible(dm_err > 0)

        self.btn_fix_service_map.setText(f"⚠️ {sp_issues} 个未连/异常服务端口 [去连接]")
        self.btn_fix_service_map.setVisible(sp_issues > 0)

        all_healthy = (
            ea_err == 0
            and unloaded == 0
            and ea_unconf == 0
            and unmapped_cnt == 0
            and dm_err == 0
            and sp_issues == 0
        )
        self.health_ok_label.setVisible(all_healthy)
        self.btn_goto_generate.setVisible(ea_err == 0)
