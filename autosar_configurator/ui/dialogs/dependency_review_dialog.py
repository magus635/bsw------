from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QTableWidget, 
    QTableWidgetItem, QPushButton, QLabel, QHeaderView,
    QCheckBox, QAbstractItemView, QMessageBox, QWidget
)
from PySide6.QtCore import Qt, Signal
from typing import List, Dict, Any

class DependencyReviewDialog(QDialog):
    """
    Dialog for reviewing AI-discovered cross-module dependencies.
    Allows users to confirm, reject, or edit rules before they are applied.
    """
    
    confirmed = Signal(list)  # Emits list of confirmed dependency rules
    
    def __init__(self, dependencies: List[Dict[str, Any]], parent=None):
        super().__init__(parent)
        self.dependencies = dependencies
        self.confirmed_rules = []
        
        self.setWindowTitle("AI Dependency Review")
        self.resize(1000, 600)
        
        self._setup_ui()
        self._populate_table()
        
    def _setup_ui(self):
        layout = QVBoxLayout(self)
        
        # Header
        header_label = QLabel("The AI has discovered the following potential dependencies. "
                             "Please review and select the rules you want to apply.")
        header_label.setWordWrap(True)
        header_label.setStyleSheet("font-weight: bold; margin-bottom: 10px;")
        layout.addWidget(header_label)
        
        # Table
        self.table = QTableWidget()
        self.table.setColumnCount(7)
        self.table.setHorizontalHeaderLabels([
            "Apply", "Origin", "Source Parameter", "Condition", "Target Parameter", "Requirement", "Reason"
        ])
        
        # Table properties
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Interactive)
        self.table.horizontalHeader().setStretchLastSection(True)
        self.table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.table.setAlternatingRowColors(True)
        
        layout.addWidget(self.table)
        
        # Select All / None buttons
        btn_layout = QHBoxLayout()
        select_all_btn = QPushButton("Select All")
        select_all_btn.clicked.connect(self._select_all)
        select_none_btn = QPushButton("Select None")
        select_none_btn.clicked.connect(self._select_none)
        btn_layout.addWidget(select_all_btn)
        btn_layout.addWidget(select_none_btn)
        btn_layout.addStretch()
        
        # Action buttons
        apply_btn = QPushButton("Apply Selected Rules")
        apply_btn.setStyleSheet("background-color: #0078d4; color: white; font-weight: bold; padding: 5px 15px;")
        apply_btn.clicked.connect(self._on_apply)
        cancel_btn = QPushButton("Cancel")
        cancel_btn.clicked.connect(self.reject)
        
        btn_layout.addWidget(apply_btn)
        btn_layout.addWidget(cancel_btn)
        
        layout.addLayout(btn_layout)

    def _populate_table(self):
        self.table.setRowCount(len(self.dependencies))
        
        for i, dep in enumerate(self.dependencies):
            # 1. Apply Checkbox
            checkbox_widget = QWidget()
            checkbox_layout = QHBoxLayout(checkbox_widget)
            checkbox = QCheckBox()
            checkbox.setChecked(dep.get('status') == 'confirmed' or dep.get('origin') == '📋 定义')
            checkbox_layout.addWidget(checkbox)
            checkbox_layout.setAlignment(Qt.AlignCenter)
            checkbox_layout.setContentsMargins(0, 0, 0, 0)
            self.table.setCellWidget(i, 0, checkbox_widget)
            
            # 2. Origin
            origin_item = QTableWidgetItem(dep.get('origin', '❓ 未知'))
            origin_item.setFlags(origin_item.flags() & ~Qt.ItemIsEditable)
            self.table.setItem(i, 1, origin_item)
            
            # 3. Source Parameter
            src_item = QTableWidgetItem(dep.get('source_param', ''))
            self.table.setItem(i, 2, src_item)
            
            # 4. Condition
            cond_item = QTableWidgetItem(f"{dep.get('source_condition', '')} {dep.get('source_value', '')}")
            self.table.setItem(i, 3, cond_item)
            
            # 5. Target Parameter
            target_item = QTableWidgetItem(dep.get('target_param', ''))
            self.table.setItem(i, 4, target_item)
            
            # 6. Requirement
            req_item = QTableWidgetItem(f"{dep.get('target_condition', '')} {dep.get('target_value', '')}")
            self.table.setItem(i, 5, req_item)
            
            # 7. Reason
            reason_item = QTableWidgetItem(dep.get('reason', ''))
            self.table.setItem(i, 6, reason_item)
            
        self.table.resizeColumnsToContents()

    def _select_all(self):
        for i in range(self.table.rowCount()):
            widget = self.table.cellWidget(i, 0)
            if widget:
                checkbox = widget.layout().itemAt(0).widget()
                checkbox.setChecked(True)

    def _select_none(self):
        for i in range(self.table.rowCount()):
            widget = self.table.cellWidget(i, 0)
            if widget:
                checkbox = widget.layout().itemAt(0).widget()
                checkbox.setChecked(False)

    def _on_apply(self):
        self.confirmed_rules = []
        for i in range(self.table.rowCount()):
            widget = self.table.cellWidget(i, 0)
            if widget:
                checkbox = widget.layout().itemAt(0).widget()
                if checkbox.isChecked():
                    # Reconstruct the dependency dict from table items (allowing for potential edits)
                    rule = self.dependencies[i].copy()
                    rule['source_param'] = self.table.item(i, 2).text()
                    # Parsing condition/value back is tricky if edited as one string, 
                    # but for now we trust the raw data or simple edits.
                    # In a more robust version, we'd have separate columns/editors.
                    rule['target_param'] = self.table.item(i, 4).text()
                    rule['reason'] = self.table.item(i, 6).text()
                    rule['status'] = 'confirmed'
                    self.confirmed_rules.append(rule)
        
        if not self.confirmed_rules:
            QMessageBox.information(self, "No Rules Selected", "Please select at least one rule to apply.")
            return
            
        self.confirmed.emit(self.confirmed_rules)
        self.accept()
