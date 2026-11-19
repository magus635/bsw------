"""Dialog to preview and confirm baseline merge changes during DaVinci import"""

from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QPushButton, QTextEdit, QLabel
)
from PySide6.QtGui import QFont


class MergePreviewDialog(QDialog):
    """Display baseline merge preview (Pre/Rec conflicts) and let user accept/reject"""

    def __init__(self, parent, module_name: str, preview_markdown: str, merge_result):
        super().__init__(parent)
        self.setWindowTitle(f"基线合并预览 — {module_name}")
        self.setGeometry(100, 100, 700, 500)
        self.merge_result = merge_result
        self._setup_ui(module_name, preview_markdown)

    def _setup_ui(self, module_name: str, preview_markdown: str):
        """Build UI with preview and buttons"""
        layout = QVBoxLayout(self)

        # Title
        title = QLabel(f"模块 <b>{module_name}</b> 的基线需要合并")
        layout.addWidget(title)

        # Preview text area
        preview = QTextEdit()
        preview.setMarkdown(preview_markdown)
        preview.setReadOnly(True)
        preview.setFont(QFont("Courier", 9))
        layout.addWidget(QLabel("合并内容预览："))
        layout.addWidget(preview)

        # Summary
        summary_lines = []
        if self.merge_result.items:
            from ...core.baseline.merge import MergeKind
            for kind in MergeKind:
                items = self.merge_result.of_kind(kind)
                if items:
                    from ...core.baseline.merge import _KIND_LABELS
                    count = len(items)
                    summary_lines.append(f"{_KIND_LABELS[kind]}: {count} 项")

        if summary_lines:
            summary = QLabel("摘要：" + "，".join(summary_lines))
            layout.addWidget(summary)

        # Buttons
        button_layout = QHBoxLayout()

        reject_btn = QPushButton("拒绝（跳过此模块）")
        reject_btn.clicked.connect(self.reject)
        button_layout.addWidget(reject_btn)

        accept_btn = QPushButton("接受（应用合并）")
        accept_btn.setDefault(True)
        accept_btn.clicked.connect(self.accept)
        button_layout.addWidget(accept_btn)

        layout.addLayout(button_layout)

    def exec(self) -> int:
        """Show dialog and return result (QDialog.Accepted or QDialog.Rejected)"""
        return super().exec()
