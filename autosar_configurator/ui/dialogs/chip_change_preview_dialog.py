"""
Chip Change Preview Dialog (add-chip-switch-disabled-report)

Shows what a chip change would do before it is applied: the selector parameter
values written, and the configured containers that ENABLE conditions would disable
or enable again.  The user confirms or cancels the change.  The dialog is in Chinese.
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Tuple

from PySide6.QtCore import Qt
from PySide6.QtWidgets import (
    QAbstractItemView,
    QDialog,
    QDialogButtonBox,
    QGroupBox,
    QHeaderView,
    QLabel,
    QTableWidget,
    QTableWidgetItem,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
)

UNSET = "（未设置）"


@dataclass
class ChipChangeReport:
    """Effect of a chip change, computed on copies of the project.

    ``disabled`` / ``enabled`` hold DisabledContainer items (module, path,
    definition): the topmost configured containers that the change would disable
    or enable again.  ``error`` is set when the effect could not be computed.
    """
    chip_name: Optional[str]
    current_chip: Optional[str] = None
    selector_result: object = None
    disabled: list = field(default_factory=list)
    enabled: list = field(default_factory=list)
    error: Optional[str] = None

    def selector_lines(self) -> List[str]:
        result = self.selector_result
        return result.messages() if result is not None else []

    def selector_rows(self) -> List[Tuple[str, str, str]]:
        """(parameter, current value, new value) per selector, in Chinese."""
        result = self.selector_result
        if result is None:
            return []
        rows = [(key, UNSET if old is None else str(old), str(new)) for key, old, new in result.changed]
        rows += [(key, "", f"不写入：{reason}") for key, reason in result.skipped]
        return rows


def _path_key(path: str):
    return path.lower(), path


def group_containers(items) -> Dict[Tuple[str, str], List[str]]:
    """(module, definition) -> paths (case-insensitive order), in module and definition order."""
    groups: Dict[Tuple[str, str], List[str]] = {}
    for item in items:
        groups.setdefault((item.module, item.definition), []).append(item.path)
    return {key: sorted(groups[key], key=_path_key) for key in sorted(groups)}


def _ordered_groups(items):
    """Groups, largest first."""
    return sorted(group_containers(items).items(), key=lambda kv: (-len(kv[1]), kv[0]))


def summary_lines(items) -> List[str]:
    """One line per (module, definition), largest group first, e.g. 'Os: MemoryBlock x25'
    (for the log)."""
    return [f"{module}: {definition} x{len(paths)}" for (module, definition), paths in _ordered_groups(items)]


class ChipChangePreviewDialog(QDialog):
    """Preview of a chip change; accept() applies it, reject() cancels it."""

    def __init__(self, report: ChipChangeReport, parent=None, title: str = "切换芯片",
                 accept_text: str = "切换"):
        super().__init__(parent)
        self.report = report
        self.setWindowTitle(title)
        self.resize(760, 600)
        layout = QVBoxLayout(self)

        if report.current_chip != report.chip_name:
            heading = (f"将项目芯片从 {report.current_chip or UNSET} 切换为 {report.chip_name}，"
                       f"切换前请确认以下影响。")
        else:
            heading = f"将芯片 {report.chip_name} 声明的选择器取值写入配置，写入前请确认以下影响。"
        self.heading_label = QLabel(heading)
        self.heading_label.setWordWrap(True)
        layout.addWidget(self.heading_label)

        # Selector parameters: parameter | current | new
        selectors = QGroupBox("选择器参数")
        selectors_layout = QVBoxLayout(selectors)
        rows = report.selector_rows()
        self.selector_table = QTableWidget(len(rows), 3)
        self.selector_table.setHorizontalHeaderLabels(["参数", "当前值", "切换后"])
        self.selector_table.verticalHeader().setVisible(False)
        self.selector_table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.selector_table.setSelectionMode(QAbstractItemView.NoSelection)
        self.selector_table.setFocusPolicy(Qt.NoFocus)
        header = self.selector_table.horizontalHeader()
        header.setSectionResizeMode(QHeaderView.ResizeToContents)
        header.setStretchLastSection(True)
        for r, row in enumerate(rows):
            for c, text in enumerate(row):
                self.selector_table.setItem(r, c, QTableWidgetItem(text))
        self.selector_table.setFixedHeight(
            self.selector_table.horizontalHeader().sizeHint().height()
            + sum(self.selector_table.rowHeight(r) for r in range(len(rows))) + 4)
        self.selector_table.setVisible(bool(rows))
        selectors_layout.addWidget(self.selector_table)
        self.selector_empty_label = QLabel("选择器参数没有变化。")
        self.selector_empty_label.setVisible(not rows)
        selectors_layout.addWidget(self.selector_empty_label)
        layout.addWidget(selectors)

        # What happens to the configured containers
        self.status_label = QLabel(self._status_text(report))
        self.status_label.setWordWrap(True)
        if report.error or report.disabled:
            self.status_label.setStyleSheet("color: #c0392b;")
        layout.addWidget(self.status_label)

        self.disabled_tree = self._tree(report.disabled)
        self.enabled_tree = self._tree(report.enabled)
        if report.disabled:
            box = QGroupBox(f"将失效（{len(report.disabled)} 个容器）")
            QVBoxLayout(box).addWidget(self.disabled_tree)
            layout.addWidget(box, 1)
        if report.enabled:
            box = QGroupBox(f"将恢复生效（{len(report.enabled)} 个容器）")
            QVBoxLayout(box).addWidget(self.enabled_tree)
            layout.addWidget(box, 1)
        if not report.disabled and not report.enabled:
            layout.addStretch(1)

        note = QLabel("只统计定义中 ENABLE 条件的结果；模板中直接按芯片分支生成的内容"
                      "（如 scatter 文件）不在预览范围内。每个失效子树只列出最上层容器。")
        note.setWordWrap(True)
        note.setStyleSheet("color: gray;")
        layout.addWidget(note)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        self.accept_button = buttons.button(QDialogButtonBox.Ok)
        self.accept_button.setText(accept_text)
        buttons.button(QDialogButtonBox.Cancel).setText("取消")
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)

    @staticmethod
    def _status_text(report: ChipChangeReport) -> str:
        if report.error:
            return f"无法检查会失效的配置：{report.error}（详见日志）。仍可以继续切换。"
        if report.disabled and report.enabled:
            return ("部分已配置的容器将失效，另一部分将恢复生效。失效的容器仍保留在项目中，"
                    "但不参与代码生成和 EPC 导出；切回原芯片后自动恢复。")
        if report.disabled:
            return ("以下已配置的容器将失效：它们仍保留在项目中，但不参与代码生成和 EPC 导出；"
                    "切回原芯片后自动恢复。")
        if report.enabled:
            return "以下已配置的容器在当前芯片下未生效，切换后将重新参与代码生成和 EPC 导出。"
        return "没有已配置的容器会因此失效或恢复生效。"

    @staticmethod
    def _tree(items) -> QTreeWidget:
        tree = QTreeWidget()
        tree.setHeaderHidden(True)
        for (module, definition), paths in _ordered_groups(items):
            group = QTreeWidgetItem([f"{module}：{definition} × {len(paths)}"])
            for path in paths:
                QTreeWidgetItem(group, [path])
            tree.addTopLevelItem(group)
        return tree
