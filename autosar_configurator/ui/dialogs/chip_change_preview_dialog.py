"""
Chip Change Preview Dialog (add-chip-switch-disabled-report)

Shows what a chip change would do before it is applied: the selector parameter
values written, and the configured containers that ENABLE conditions would disable
or enable again.  The user confirms or cancels the change.
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Tuple

from PySide6.QtWidgets import (
    QDialog,
    QDialogButtonBox,
    QGroupBox,
    QLabel,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
)


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


def group_containers(items) -> Dict[Tuple[str, str], List[str]]:
    """(module, definition) -> sorted paths, in module and definition order."""
    groups: Dict[Tuple[str, str], List[str]] = {}
    for item in items:
        groups.setdefault((item.module, item.definition), []).append(item.path)
    return {key: sorted(groups[key]) for key in sorted(groups)}


def summary_lines(items) -> List[str]:
    """One line per (module, definition), largest group first, e.g. 'Os: MemoryBlock x25'."""
    groups = group_containers(items)
    ordered = sorted(groups.items(), key=lambda kv: (-len(kv[1]), kv[0]))
    return [f"{module}: {definition} x{len(paths)}" for (module, definition), paths in ordered]


class ChipChangePreviewDialog(QDialog):
    """Preview of a chip change; accept() applies it, reject() cancels it."""

    def __init__(self, report: ChipChangeReport, parent=None, title: str = "Change Chip",
                 accept_text: str = "Switch"):
        super().__init__(parent)
        self.report = report
        self.setWindowTitle(title)
        self.resize(640, 520)
        layout = QVBoxLayout(self)

        if report.current_chip != report.chip_name:
            heading = f"Change the project's chip from {report.current_chip or '(none)'} to {report.chip_name}?"
        else:
            heading = f"Apply the selector values of chip {report.chip_name}?"
        self.heading_label = QLabel(heading)
        self.heading_label.setWordWrap(True)
        layout.addWidget(self.heading_label)

        selectors = QGroupBox("Selector parameters")
        selectors_layout = QVBoxLayout(selectors)
        lines = report.selector_lines()
        self.selector_label = QLabel("\n".join(lines) if lines else "No selector parameter changes.")
        self.selector_label.setWordWrap(True)
        selectors_layout.addWidget(self.selector_label)
        layout.addWidget(selectors)

        self.disabled_tree = self._tree(report.disabled)
        self.enabled_tree = self._tree(report.enabled)
        if report.error:
            self.status_label = QLabel(f"Disabled configuration could not be checked: {report.error}\n"
                                       f"(see the log)")
            self.status_label.setStyleSheet("color: #c0392b;")
        elif not report.disabled and not report.enabled:
            self.status_label = QLabel("No configured container will be disabled or enabled again.")
        else:
            self.status_label = QLabel(
                "Disabled containers stay in the project and are used again when the chip "
                "is changed back; they are left out of code generation and EPC export.")
        self.status_label.setWordWrap(True)
        layout.addWidget(self.status_label)

        if report.disabled:
            box = QGroupBox(f"Will be disabled ({len(report.disabled)} containers)")
            QVBoxLayout(box).addWidget(self.disabled_tree)
            box.setStyleSheet("QGroupBox { color: #c0392b; }")
            layout.addWidget(box, 1)
        if report.enabled:
            box = QGroupBox(f"Will be enabled again ({len(report.enabled)} containers)")
            QVBoxLayout(box).addWidget(self.enabled_tree)
            layout.addWidget(box, 1)

        note = QLabel("Template output that depends on the chip directly (e.g. scatter files) "
                      "is not covered by this preview.")
        note.setWordWrap(True)
        note.setStyleSheet("color: gray;")
        layout.addWidget(note)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        self.accept_button = buttons.button(QDialogButtonBox.Ok)
        self.accept_button.setText(accept_text)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)

    @staticmethod
    def _tree(items) -> QTreeWidget:
        tree = QTreeWidget()
        tree.setHeaderHidden(True)
        groups = group_containers(items)
        for (module, definition), paths in sorted(groups.items(), key=lambda kv: (-len(kv[1]), kv[0])):
            group = QTreeWidgetItem([f"{module}: {definition} x{len(paths)}"])
            for path in paths:
                QTreeWidgetItem(group, [path])
            tree.addTopLevelItem(group)
        return tree
