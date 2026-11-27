"""Home dashboard widget shown inside DaVinciMainWindow when Home rail item is active."""

from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

from PySide6.QtCore import Qt, Signal
from PySide6.QtWidgets import (
    QFrame,
    QGridLayout,
    QHBoxLayout,
    QLabel,
    QListWidget,
    QListWidgetItem,
    QPushButton,
    QScrollArea,
    QStackedWidget,
    QVBoxLayout,
    QWidget,
)


def _card_frame(object_name: str = "HomeCard") -> QFrame:
    card = QFrame()
    card.setObjectName(object_name)
    card.setStyleSheet(
        f"QFrame#{object_name} {{ "
        "background-color: #ffffff; border: 1px solid #d0d7de; border-radius: 6px; }"
    )
    return card


def _clear_grid(grid: QGridLayout) -> None:
    while grid.count():
        item = grid.takeAt(0)
        widget = item.widget()
        if widget is not None:
            widget.deleteLater()


class HomeDashboardWidget(QScrollArea):
    """Scrollable Home landing dashboard for empty and project-loaded states."""

    new_project_requested = Signal()
    open_project_requested = Signal()
    import_davinci_requested = Signal()
    import_eb_requested = Signal()
    recent_file_requested = Signal(str)

    open_basic_editor_requested = Signal()
    module_open_requested = Signal(str)
    add_or_integrate_module_requested = Signal()
    communication_workbench_requested = Signal()
    rte_workbench_requested = Signal()
    system_services_workbench_requested = Signal()
    memmap_requested = Signal()
    hw_mapping_requested = Signal()
    chip_designer_requested = Signal()
    validate_requested = Signal()
    dep_graph_requested = Signal()
    generate_requested = Signal()
    project_properties_requested = Signal()

    def __init__(self, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.setObjectName("HomeDashboardWidget")
        self.setWidgetResizable(True)
        self.setFrameShape(QFrame.NoFrame)
        self.setStyleSheet("QScrollArea#HomeDashboardWidget { background-color: #f6f8fa; }")

        container = QWidget()
        container.setStyleSheet("background-color: #f6f8fa;")
        outer = QVBoxLayout(container)
        outer.setContentsMargins(24, 20, 24, 24)
        outer.setSpacing(16)

        self.stack = QStackedWidget()
        self.empty_page = self._build_empty_page()
        self.project_page = self._build_project_page()
        self.stack.addWidget(self.empty_page)
        self.stack.addWidget(self.project_page)
        outer.addWidget(self.stack)

        self.module_buttons: Dict[str, QPushButton] = {}
        self.setWidget(container)

    def _build_empty_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(16)

        title = QLabel("AUTOSAR DaVinci Configurator")
        title.setStyleSheet("font-size: 22px; font-weight: bold; color: #1f2328;")
        layout.addWidget(title)

        subtitle = QLabel("AUTOSAR Classic BSW / MCAL / RTE / SchM 图形化配置与代码生成工作台")
        subtitle.setStyleSheet("font-size: 13px; color: #57606a;")
        layout.addWidget(subtitle)

        # Quick-start card
        quick_card = _card_frame("QuickStartCard")
        ql = QVBoxLayout(quick_card)
        ql.setContentsMargins(16, 14, 16, 16)
        ql.setSpacing(10)
        q_title = QLabel("快速开始")
        q_title.setStyleSheet("font-size: 15px; font-weight: bold; color: #1f2328; border: none;")
        ql.addWidget(q_title)

        btn_row = QHBoxLayout()
        btn_row.setSpacing(10)
        self.btn_new_project = QPushButton("📄 新建项目...")
        self.btn_open_project = QPushButton("📂 打开项目...")
        self.btn_import_davinci = QPushButton("📥 导入 DaVinci 项目 (.dpa)...")
        self.btn_import_eb = QPushButton("📥 导入 EB Tresos 项目...")
        for btn in (
            self.btn_new_project,
            self.btn_open_project,
            self.btn_import_davinci,
            self.btn_import_eb,
        ):
            btn.setMinimumHeight(40)
            btn.setCursor(Qt.PointingHandCursor)
            btn_row.addWidget(btn)
        btn_row.addStretch()

        self.btn_new_project.clicked.connect(self.new_project_requested.emit)
        self.btn_open_project.clicked.connect(self.open_project_requested.emit)
        self.btn_import_davinci.clicked.connect(self.import_davinci_requested.emit)
        self.btn_import_eb.clicked.connect(self.import_eb_requested.emit)
        ql.addLayout(btn_row)
        layout.addWidget(quick_card)

        # Recent projects card
        recent_card = _card_frame("RecentProjectsCard")
        rl = QVBoxLayout(recent_card)
        rl.setContentsMargins(16, 14, 16, 16)
        rl.setSpacing(8)
        r_title = QLabel("最近打开的项目（点击快速打开）")
        r_title.setStyleSheet("font-size: 15px; font-weight: bold; color: #1f2328; border: none;")
        rl.addWidget(r_title)

        self.recent_list = QListWidget()
        self.recent_list.setMinimumHeight(180)
        self.recent_list.setStyleSheet(
            "QListWidget { border: 1px solid #e1e4e8; border-radius: 4px; background: #ffffff; }"
            "QListWidget::item { padding: 6px 8px; }"
        )
        self.recent_list.itemClicked.connect(self._on_recent_item_triggered)
        self.recent_list.itemActivated.connect(self._on_recent_item_triggered)
        rl.addWidget(self.recent_list)
        layout.addWidget(recent_card)

        layout.addStretch(1)
        return page

    def _build_project_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(14)

        # Project overview header card
        summary_card = _card_frame("ProjectSummaryCard")
        sl = QHBoxLayout(summary_card)
        sl.setContentsMargins(18, 14, 18, 14)

        info_col = QVBoxLayout()
        info_col.setSpacing(4)
        self.proj_name_label = QLabel("Project")
        self.proj_name_label.setStyleSheet("font-size: 20px; font-weight: bold; color: #1f2328; border: none;")
        info_col.addWidget(self.proj_name_label)

        self.proj_meta_label = QLabel("")
        self.proj_meta_label.setStyleSheet("font-size: 12px; color: #57606a; border: none;")
        info_col.addWidget(self.proj_meta_label)

        self.proj_validation_label = QLabel("校验状态：未运行")
        self.proj_validation_label.setStyleSheet("font-size: 12px; color: #57606a; border: none;")
        info_col.addWidget(self.proj_validation_label)
        sl.addLayout(info_col, 1)

        action_col = QHBoxLayout()
        action_col.setSpacing(8)
        self.btn_enter_basic = QPushButton("🌳 进入基础编辑器 →")
        self.btn_enter_basic.setMinimumHeight(36)
        self.btn_enter_basic.setCursor(Qt.PointingHandCursor)
        self.btn_enter_basic.clicked.connect(self.open_basic_editor_requested.emit)
        action_col.addWidget(self.btn_enter_basic)

        self.btn_proj_props = QPushButton("📁 工程属性...")
        self.btn_proj_props.setMinimumHeight(36)
        self.btn_proj_props.setCursor(Qt.PointingHandCursor)
        self.btn_proj_props.clicked.connect(self.project_properties_requested.emit)
        action_col.addWidget(self.btn_proj_props)
        sl.addLayout(action_col)
        layout.addWidget(summary_card)

        # 4-step workflow card
        wf_card = _card_frame("WorkflowCard")
        wl = QVBoxLayout(wf_card)
        wl.setContentsMargins(16, 12, 16, 14)
        wl.setSpacing(10)
        w_title = QLabel("推荐配置工作流")
        w_title.setStyleSheet("font-size: 14px; font-weight: bold; color: #1f2328; border: none;")
        wl.addWidget(w_title)

        wf_row = QHBoxLayout()
        wf_row.setSpacing(10)
        self.wf_add_mod_btn = QPushButton("① 添加 / 集成模块")
        self.wf_rte_btn = QPushButton("② RTE / SchM 工作台")
        self.wf_val_btn = QPushButton("③ 配置验证 (Ctrl+Shift+V)")
        self.wf_gen_btn = QPushButton("④ 代码生成 (Ctrl+G)")
        for btn in (self.wf_add_mod_btn, self.wf_rte_btn, self.wf_val_btn, self.wf_gen_btn):
            btn.setMinimumHeight(38)
            btn.setCursor(Qt.PointingHandCursor)
            wf_row.addWidget(btn)
        wf_row.addStretch()

        self.wf_add_mod_btn.clicked.connect(self.add_or_integrate_module_requested.emit)
        self.wf_rte_btn.clicked.connect(self.rte_workbench_requested.emit)
        self.wf_val_btn.clicked.connect(self.validate_requested.emit)
        self.wf_gen_btn.clicked.connect(self.generate_requested.emit)
        wl.addLayout(wf_row)
        layout.addWidget(wf_card)

        # Loaded modules grid card
        mods_card = _card_frame("LoadedModulesCard")
        ml = QVBoxLayout(mods_card)
        ml.setContentsMargins(16, 12, 16, 16)
        ml.setSpacing(10)
        self.mods_title_label = QLabel("已加载 BSW / MCAL 模块（点击跳转到基础编辑器）")
        self.mods_title_label.setStyleSheet("font-size: 14px; font-weight: bold; color: #1f2328; border: none;")
        ml.addWidget(self.mods_title_label)

        self.modules_grid = QGridLayout()
        self.modules_grid.setSpacing(8)
        ml.addLayout(self.modules_grid)
        layout.addWidget(mods_card)

        # Quick domain tools card
        tools_card = _card_frame("QuickToolsCard")
        tl = QVBoxLayout(tools_card)
        tl.setContentsMargins(16, 12, 16, 14)
        tl.setSpacing(10)
        t_title = QLabel("常用专用工作台与分析工具")
        t_title.setStyleSheet("font-size: 14px; font-weight: bold; color: #1f2328; border: none;")
        tl.addWidget(t_title)

        tools_row = QHBoxLayout()
        tools_row.setSpacing(10)
        self.tool_comm_btn = QPushButton("📡 通信配置工作台")
        self.tool_rte_btn = QPushButton("⚡ RTE / SchM 工作台")
        self.tool_sys_btn = QPushButton("🛠️ 服务与诊断工作台")
        self.tool_memmap_btn = QPushButton("🧭 内存映射工作台")
        self.tool_hw_btn = QPushButton("📌 硬件映射向导")
        self.tool_chip_btn = QPushButton("🔧 芯片定义设计器")
        self.tool_dep_btn = QPushButton("🕸️ 跨模块依赖图")
        for btn in (
            self.tool_comm_btn,
            self.tool_rte_btn,
            self.tool_sys_btn,
            self.tool_memmap_btn,
            self.tool_hw_btn,
            self.tool_chip_btn,
            self.tool_dep_btn,
        ):
            btn.setMinimumHeight(34)
            btn.setCursor(Qt.PointingHandCursor)
            tools_row.addWidget(btn)
        tools_row.addStretch()

        self.tool_comm_btn.clicked.connect(self.communication_workbench_requested.emit)
        self.tool_rte_btn.clicked.connect(self.rte_workbench_requested.emit)
        self.tool_sys_btn.clicked.connect(self.system_services_workbench_requested.emit)
        self.tool_memmap_btn.clicked.connect(self.memmap_requested.emit)
        self.tool_hw_btn.clicked.connect(self.hw_mapping_requested.emit)
        self.tool_chip_btn.clicked.connect(self.chip_designer_requested.emit)
        self.tool_dep_btn.clicked.connect(self.dep_graph_requested.emit)
        tl.addLayout(tools_row)
        layout.addWidget(tools_card)

        layout.addStretch(1)
        return page

    def _on_recent_item_triggered(self, item: QListWidgetItem) -> None:
        file_path = item.data(Qt.UserRole)
        if file_path:
            self.recent_file_requested.emit(str(file_path))

    def refresh(
        self,
        project,
        *,
        recent_files: Sequence[str] = (),
        chip_name: Optional[str] = None,
        validation_summary: Optional[Tuple[int, int]] = None,
        has_unsaved: bool = False,
    ) -> None:
        self.recent_list.clear()
        existing_recent = [p for p in recent_files if p][:8]
        if existing_recent:
            for p_str in existing_recent:
                p_obj = Path(p_str)
                item = QListWidgetItem(f"{p_obj.name}   —   {p_str}")
                item.setData(Qt.UserRole, p_str)
                self.recent_list.addItem(item)
        else:
            placeholder = QListWidgetItem("暂无最近打开的项目")
            placeholder.setFlags(Qt.NoItemFlags)
            self.recent_list.addItem(placeholder)

        if project is None:
            self.module_buttons.clear()
            _clear_grid(self.modules_grid)
            self.stack.setCurrentWidget(self.empty_page)
            return

        self.stack.setCurrentWidget(self.project_page)
        proj_name = getattr(project, "name", "Project")
        dirty_suffix = " *" if has_unsaved else ""
        self.proj_name_label.setText(f"{proj_name}{dirty_suffix}")

        fmt = getattr(project, "format_version", 0)
        fmt_label = f"Format {fmt}" if fmt else "Project"
        chip_label = chip_name or getattr(project, "selected_chip", None) or "未指定芯片"
        managers = getattr(project, "module_managers", {}) or {}
        path_str = str(getattr(project, "path", "") or "")
        meta_parts = [fmt_label, f"芯片：{chip_label}", f"模块：{len(managers)} 个"]
        if path_str:
            meta_parts.append(path_str)
        self.proj_meta_label.setText("  |  ".join(meta_parts))

        if validation_summary is None:
            self.proj_validation_label.setText("校验状态：尚未运行（Ctrl+Shift+V）")
            self.proj_validation_label.setStyleSheet("font-size: 12px; color: #57606a; border: none;")
        else:
            err_cnt, warn_cnt = validation_summary
            if err_cnt > 0:
                self.proj_validation_label.setText(f"❌ 校验发现 {err_cnt} 个错误，{warn_cnt} 个告警")
                self.proj_validation_label.setStyleSheet(
                    "font-size: 12px; font-weight: bold; color: #b00020; border: none;"
                )
            elif warn_cnt > 0:
                self.proj_validation_label.setText(f"⚠️ 校验通过（{warn_cnt} 个告警）")
                self.proj_validation_label.setStyleSheet(
                    "font-size: 12px; font-weight: bold; color: #a65e00; border: none;"
                )
            else:
                self.proj_validation_label.setText("✅ 校验通过：0 错误，0 告警")
                self.proj_validation_label.setStyleSheet(
                    "font-size: 12px; font-weight: bold; color: #1b7f37; border: none;"
                )

        has_rte = "Rte" in managers
        self.wf_rte_btn.setEnabled(True)
        self.tool_rte_btn.setEnabled(True)
        if has_rte:
            self.wf_rte_btn.setText("② RTE / SchM 工作台")
            self.tool_rte_btn.setText("⚡ RTE / SchM 工作台")
            rte_tip = "打开 4 页签 RTE / SchM 配置与生成工作台"
        else:
            self.wf_rte_btn.setText("② 初始化 / 打开 RTE 工作台")
            self.tool_rte_btn.setText("⚡ 初始化 RTE / SchM 工作台")
            rte_tip = "当前项目尚未加载 Rte 模块，点击可从模块库激活或一键初始化内置 Rte 模块并打开工作台"
        self.wf_rte_btn.setToolTip(rte_tip)
        self.tool_rte_btn.setToolTip(rte_tip)

        self.module_buttons.clear()
        _clear_grid(self.modules_grid)
        sorted_mods = sorted(managers.keys())
        self.mods_title_label.setText(f"已加载 BSW / MCAL 模块 ({len(sorted_mods)}) — 点击跳转到基础编辑器")
        if not sorted_mods:
            empty_lbl = QLabel("当前工程尚未添加模块，点击上方「① 添加 / 集成模块」开始。")
            empty_lbl.setStyleSheet("color: #57606a; border: none;")
            self.modules_grid.addWidget(empty_lbl, 0, 0)
            return

        cols = 4
        for idx, mod_name in enumerate(sorted_mods):
            mgr = managers[mod_name]
            cfg = getattr(mgr, "configuration", None)
            cnt = len(getattr(cfg, "containers", []) or []) if cfg is not None else 0
            badge = " ⚡" if mod_name == "Rte" else ""
            btn = QPushButton(f"{mod_name}{badge}\n{cnt} 个顶层容器")
            btn.setMinimumHeight(50)
            btn.setCursor(Qt.PointingHandCursor)
            if mod_name == "Rte":
                btn.setToolTip("点击在基础编辑器中查看 Rte；或点左侧 ⚡ RTE/SchM 打开专用工作台")
            else:
                btn.setToolTip(f"点击切换到基础编辑器并选中 {mod_name}")
            btn.clicked.connect(lambda _c=False, m=mod_name: self.module_open_requested.emit(m))
            self.module_buttons[mod_name] = btn
            self.modules_grid.addWidget(btn, idx // cols, idx % cols)
