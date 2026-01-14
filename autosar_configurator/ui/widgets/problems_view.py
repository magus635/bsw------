from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QTreeWidget, 
    QTreeWidgetItem, QLabel, QHeaderView, QToolButton,
    QFrame
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QIcon, QColor
from typing import List
from ...core.validation_engine import ValidationMessage, ValidationSeverity

class ProblemsView(QWidget):
    """
    Centralized view for displaying all validation errors, warnings, and info messages.
    Features filtering by severity and navigation to source.
    """
    
    item_requested = Signal(str, str)  # container_path, parameter_name
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.messages: List[ValidationMessage] = []
        self._setup_ui()
        
    def _setup_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(2, 2, 2, 2)
        layout.setSpacing(0)
        
        # Toolbar
        toolbar = QFrame()
        toolbar.setStyleSheet("QFrame { background-color: #f3f3f3; border-bottom: 1px solid #dcdcdc; }")
        toolbar_layout = QHBoxLayout(toolbar)
        toolbar_layout.setContentsMargins(5, 2, 5, 2)
        
        self.error_btn = QToolButton()
        self.error_btn.setText("0 Errors")
        self.error_btn.setCheckable(True)
        self.error_btn.setChecked(True)
        self.error_btn.toggled.connect(self._refresh_view)
        
        self.warning_btn = QToolButton()
        self.warning_btn.setText("0 Warnings")
        self.warning_btn.setCheckable(True)
        self.warning_btn.setChecked(True)
        self.warning_btn.toggled.connect(self._refresh_view)
        
        self.info_btn = QToolButton()
        self.info_btn.setText("0 Info")
        self.info_btn.setCheckable(True)
        self.info_btn.setChecked(True)
        self.info_btn.toggled.connect(self._refresh_view)
        
        toolbar_layout.addWidget(self.error_btn)
        toolbar_layout.addWidget(self.warning_btn)
        toolbar_layout.addWidget(self.info_btn)
        toolbar_layout.addStretch()
        
        layout.addWidget(toolbar)
        
        # Tree Table
        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["Description", "Resource", "Path", "Rule"])
        self.tree.header().setSectionResizeMode(QHeaderView.Interactive)
        self.tree.header().setStretchLastSection(True)
        self.tree.setAlternatingRowColors(True)
        self.tree.setRootIsDecorated(False)
        self.tree.itemDoubleClicked.connect(self._on_item_double_clicked)
        
        layout.addWidget(self.tree)
        
    def set_messages(self, messages: List[ValidationMessage]):
        """Update the list of messages and refresh display"""
        self.messages = messages
        self._update_counts()
        self._refresh_view()
        
    def _update_counts(self):
        errors = sum(1 for m in self.messages if m.severity == ValidationSeverity.ERROR)
        warnings = sum(1 for m in self.messages if m.severity == ValidationSeverity.WARNING)
        infos = sum(1 for m in self.messages if m.severity == ValidationSeverity.INFO)
        
        self.error_btn.setText(f"{errors} Errors")
        self.warning_btn.setText(f"{warnings} Warnings")
        self.info_btn.setText(f"{infos} Info")
        
    def _refresh_view(self):
        self.tree.clear()
        
        show_errors = self.error_btn.isChecked()
        show_warnings = self.warning_btn.isChecked()
        show_infos = self.info_btn.isChecked()
        
        for msg in self.messages:
            if msg.severity == ValidationSeverity.ERROR and not show_errors:
                continue
            if msg.severity == ValidationSeverity.WARNING and not show_warnings:
                continue
            if msg.severity == ValidationSeverity.INFO and not show_infos:
                continue
                
            severity_str = "Error" if msg.severity == ValidationSeverity.ERROR else \
                          "Warning" if msg.severity == ValidationSeverity.WARNING else "Info"
            
            # Icon/Text color based on severity
            color = QColor("red") if msg.severity == ValidationSeverity.ERROR else \
                    QColor("orange") if msg.severity == ValidationSeverity.WARNING else QColor("blue")
            
            resource = msg.parameter_name if msg.parameter_name else (msg.container_path.split('/')[-1] if msg.container_path else "Module")
            
            item = QTreeWidgetItem([
                msg.message,
                resource,
                msg.container_path or "",
                msg.rule_name
            ])
            
            item.setForeground(0, color)
            item.setData(0, Qt.UserRole, (msg.container_path, msg.parameter_name))
            
            self.tree.addTopLevelItem(item)
            
        self.tree.resizeColumnToContents(1)
        self.tree.resizeColumnToContents(2)

    def _on_item_double_clicked(self, item, column):
        """Handle item double click for navigation"""
        data = item.data(0, Qt.UserRole)
        if data:
            path, param = data
            self.item_requested.emit(path or "", param or "")
