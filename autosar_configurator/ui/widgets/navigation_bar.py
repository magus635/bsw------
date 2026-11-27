"""DaVinci Configurator-style vertical left functional navigation bar."""

from typing import Dict, List, Optional, Tuple

from PySide6.QtCore import Qt, Signal
from PySide6.QtWidgets import (
    QButtonGroup,
    QFrame,
    QHBoxLayout,
    QLabel,
    QSizePolicy,
    QToolButton,
    QVBoxLayout,
    QWidget,
)


def _separator() -> QFrame:
    line = QFrame()
    line.setFrameShape(QFrame.HLine)
    line.setFrameShadow(QFrame.Plain)
    line.setStyleSheet("color: #d0d7de; background-color: #d0d7de; max-height: 1px; margin: 2px 8px;")
    return line


class NavRailButton(QToolButton):
    """Compact vertical icon + label button with optional status badge pill."""

    def __init__(
        self,
        item_id: str,
        icon_text: str,
        label_text: str,
        tooltip: str = "",
        *,
        checkable: bool = False,
        parent: Optional[QWidget] = None,
    ) -> None:
        super().__init__(parent)
        self.item_id = item_id
        self.base_label = label_text
        self._badge_text = ""
        self._badge_color = "#b00020"

        self.setObjectName(f"NavRailButton_{item_id}")
        self.setCheckable(checkable)
        self.setFixedSize(84, 46)
        self.setCursor(Qt.PointingHandCursor)
        if tooltip:
            self.setToolTip(tooltip)

        # Keep QToolButton accessible text accurate while rendering custom layout inside
        self.setText(label_text)

        inner = QVBoxLayout(self)
        inner.setContentsMargins(4, 5, 4, 4)
        inner.setSpacing(2)

        top_row = QHBoxLayout()
        top_row.setContentsMargins(0, 0, 0, 0)
        top_row.setSpacing(2)
        top_row.addStretch()

        self._icon_label = QLabel(icon_text)
        self._icon_label.setAlignment(Qt.AlignCenter)
        self._icon_label.setStyleSheet("font-size: 16px; background: transparent; border: none;")
        self._icon_label.setAttribute(Qt.WA_TransparentForMouseEvents)
        top_row.addWidget(self._icon_label)

        self._badge_label = QLabel("")
        self._badge_label.setAlignment(Qt.AlignCenter)
        self._badge_label.setAttribute(Qt.WA_TransparentForMouseEvents)
        self._badge_label.hide()
        top_row.addWidget(self._badge_label)

        top_row.addStretch()
        inner.addLayout(top_row)

        self._text_label = QLabel(label_text)
        self._text_label.setAlignment(Qt.AlignCenter)
        self._text_label.setStyleSheet("font-size: 11px; background: transparent; border: none;")
        self._text_label.setAttribute(Qt.WA_TransparentForMouseEvents)
        inner.addWidget(self._text_label)

        self._apply_style()

    def setText(self, text: str) -> None:  # pragma: no cover - keeps accessibility text synced
        super().setText("")
        self._accessible_label = text

    def text(self) -> str:
        return self._accessible_label if hasattr(self, "_accessible_label") else self.base_label

    def badge(self) -> str:
        return self._badge_text

    def set_badge(self, badge_text: str = "", *, color: str = "#b00020") -> None:
        self._badge_text = badge_text.strip()
        self._badge_color = color or "#b00020"
        if self._badge_text:
            self._badge_label.setText(self._badge_text)
            self._badge_label.setStyleSheet(
                f"background-color: {self._badge_color}; color: #ffffff; "
                "border-radius: 7px; padding: 0px 4px; font-size: 9px; font-weight: bold;"
            )
            self._badge_label.show()
        else:
            self._badge_label.clear()
            self._badge_label.hide()

    def setEnabled(self, enabled: bool) -> None:
        super().setEnabled(enabled)
        self._apply_style()

    def nextCheckState(self) -> None:
        if self.isCheckable():
            # Preserve group exclusivity; clicks are controlled by button group / set_active_page
            super().nextCheckState()

    def _apply_style(self) -> None:
        self.setStyleSheet(
            """
            QToolButton {
                background-color: transparent;
                border: none;
                border-left: 3px solid transparent;
                border-radius: 4px;
            }
            QToolButton:hover:enabled {
                background-color: #e2e8f0;
            }
            QToolButton:checked {
                background-color: #ffffff;
                border-left: 3px solid #1f5fbf;
            }
            QToolButton:disabled {
                color: #9aa0a6;
            }
            """
        )
        if not self.isEnabled():
            self._text_label.setStyleSheet("font-size: 11px; color: #9aa0a6; background: transparent;")
            self._icon_label.setStyleSheet("font-size: 16px; color: #9aa0a6; background: transparent;")
        elif self.isChecked():
            self._text_label.setStyleSheet(
                "font-size: 11px; font-weight: bold; color: #1f5fbf; background: transparent;"
            )
            self._icon_label.setStyleSheet("font-size: 16px; color: #1f5fbf; background: transparent;")
        else:
            self._text_label.setStyleSheet("font-size: 11px; color: #24292f; background: transparent;")
            self._icon_label.setStyleSheet("font-size: 16px; color: #24292f; background: transparent;")

    def refresh_visual_state(self) -> None:
        self._apply_style()


class LeftNavigationBar(QFrame):
    """Fixed-width left functional navigation rail matching DaVinci Configurator workflow."""

    page_selected = Signal(str)
    action_triggered = Signal(str)

    PAGE_ITEMS: Tuple[Tuple[str, str, str, str], ...] = (
        ("home", "🏠", "首页", "工程总览、最近项目与快捷工作流"),
        ("basic_editor", "🌳", "基础编辑", "AUTOSAR ECUC 模块树与参数编辑器 (Basic Editor)"),
    )
    WORKBENCH_ITEMS: Tuple[Tuple[str, str, str, str], ...] = (
        ("communication", "📡", "通信配置", "打开 5 页签 CAN 通信矩阵、PduR 路由与 DBC 一键派生工作台"),
        ("rte_workbench", "⚡", "RTE/SchM", "打开 6 页签 RTE / SchM / 数据映射 / 服务连接与代码生成工作台"),
        ("system_services", "🛠️", "服务与诊断", "打开 5 页签 EcuM / BswM / Os / Dcm+CanTp / Det 与 CDD 系统服务工作台"),
        ("memmap", "🧭", "内存映射", "打开内存映射检查、布局与链接脚本工作台"),
        ("hw_mapping", "📌", "硬件映射", "打开硬件引脚/外设资源映射向导 (Ctrl+Shift+H)"),
    )
    VERIFY_GEN_ITEMS: Tuple[Tuple[str, str, str, str], ...] = (
        ("validate", "✅", "配置验证", "运行全局配置验证并在 Problems 面板查看结果 (Ctrl+Shift+V)"),
        ("dep_graph", "🕸️", "依赖图", "打开跨模块依赖关系可视化图 (Ctrl+D)"),
        ("generate", "⚙️", "代码生成", "执行代码生成 (Ctrl+G)"),
    )
    BOTTOM_ITEMS: Tuple[Tuple[str, str, str, str], ...] = (
        ("settings", "📁", "工程设置", "打开工程属性与芯片设置 (Project Properties)"),
        ("help", "❓", "使用手册", "打开使用手册 (F1)"),
    )

    def __init__(self, parent: Optional[QWidget] = None) -> None:
        super().__init__(parent)
        self.setObjectName("LeftNavigationBar")
        self.setFixedWidth(92)
        self.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Expanding)
        self.setStyleSheet(
            "QFrame#LeftNavigationBar { "
            "background-color: #f0f2f5; border: none; border-right: 1px solid #d0d7de; }"
        )

        self.buttons: Dict[str, NavRailButton] = {}
        self._active_page = "home"

        self._page_group = QButtonGroup(self)
        self._page_group.setExclusive(True)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(4, 8, 4, 8)
        layout.setSpacing(4)

        for item_id, icon_text, label_text, tooltip in self.PAGE_ITEMS:
            btn = NavRailButton(item_id, icon_text, label_text, tooltip, checkable=True, parent=self)
            self._page_group.addButton(btn)
            btn.clicked.connect(lambda _checked=False, pid=item_id: self._handle_page_click(pid))
            self.buttons[item_id] = btn
            layout.addWidget(btn, 0, Qt.AlignHCenter)

        layout.addWidget(_separator())

        for item_id, icon_text, label_text, tooltip in self.WORKBENCH_ITEMS:
            btn = NavRailButton(item_id, icon_text, label_text, tooltip, checkable=False, parent=self)
            btn.clicked.connect(lambda _checked=False, aid=item_id: self.action_triggered.emit(aid))
            self.buttons[item_id] = btn
            layout.addWidget(btn, 0, Qt.AlignHCenter)

        layout.addWidget(_separator())

        for item_id, icon_text, label_text, tooltip in self.VERIFY_GEN_ITEMS:
            btn = NavRailButton(item_id, icon_text, label_text, tooltip, checkable=False, parent=self)
            btn.clicked.connect(lambda _checked=False, aid=item_id: self.action_triggered.emit(aid))
            self.buttons[item_id] = btn
            layout.addWidget(btn, 0, Qt.AlignHCenter)

        layout.addStretch(1)
        layout.addWidget(_separator())

        for item_id, icon_text, label_text, tooltip in self.BOTTOM_ITEMS:
            btn = NavRailButton(item_id, icon_text, label_text, tooltip, checkable=False, parent=self)
            btn.clicked.connect(lambda _checked=False, aid=item_id: self.action_triggered.emit(aid))
            self.buttons[item_id] = btn
            layout.addWidget(btn, 0, Qt.AlignHCenter)

        self.set_active_page("home")

    def _handle_page_click(self, page_id: str) -> None:
        self.set_active_page(page_id)
        self.page_selected.emit(page_id)

    def set_active_page(self, page_id: str) -> None:
        if page_id not in ("home", "basic_editor"):
            return
        self._active_page = page_id
        for pid in ("home", "basic_editor"):
            btn = self.buttons[pid]
            btn.blockSignals(True)
            btn.setChecked(pid == page_id)
            btn.blockSignals(False)
            btn.refresh_visual_state()

    def active_page(self) -> str:
        return self._active_page

    def set_item_enabled(self, item_id: str, enabled: bool) -> None:
        btn = self.buttons.get(item_id)
        if btn is not None:
            btn.setEnabled(enabled)

    def set_item_badge(self, item_id: str, badge_text: str = "", *, color: str = "#b00020") -> None:
        btn = self.buttons.get(item_id)
        if btn is not None:
            btn.set_badge(badge_text, color=color)
