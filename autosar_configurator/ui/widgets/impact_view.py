from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QTreeWidget, QTreeWidgetItem, 
    QLabel, QHeaderView, QPushButton, QHBoxLayout
)
from PySide6.QtCore import Qt, Signal
from typing import List
from ...core.analysis.impact_analyzer import ImpactPath

class ImpactView(QWidget):
    """
    Widget to display the cascading impact of a configuration change.
    Shows which parameters or containers are affected by a change in another part of the system.
    """
    
    item_requested = Signal(str)  # Emits the path of the item to navigate to
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self._setup_ui()
        
    def _setup_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(5, 5, 5, 5)
        
        # Header
        self.title_label = QLabel("Change Impact Analysis")
        self.title_label.setStyleSheet("font-weight: bold; font-size: 14px;")
        layout.addWidget(self.title_label)
        
        self.source_label = QLabel("Source: None")
        self.source_label.setStyleSheet("color: gray;")
        self.source_label.setWordWrap(True)
        layout.addWidget(self.source_label)
        
        # Impact Tree
        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["Affected Item", "Dependency Type", "Reason"])
        self.tree.header().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.tree.setAlternatingRowColors(True)
        self.tree.itemDoubleClicked.connect(self._on_item_double_clicked)
        
        layout.addWidget(self.tree)
        
        # Actions
        btn_layout = QHBoxLayout()
        self.clear_btn = QPushButton("Clear")
        self.clear_btn.clicked.connect(self.clear)
        btn_layout.addStretch()
        btn_layout.addWidget(self.clear_btn)
        
        layout.addLayout(btn_layout)
        
    def display_impacts(self, source_path: str, impacts: List[ImpactPath]):
        """Populate the tree with impact data"""
        self.clear()
        self.source_label.setText(f"Source: {source_path}")
        
        if not impacts:
            item = QTreeWidgetItem(["No impacts discovered"])
            self.tree.addTopLevelItem(item)
            return
            
        # Group by target to avoid duplication in case of multiple paths?
        # For now, just list them.
        for impact in impacts:
            item = QTreeWidgetItem([
                impact.target,
                impact.dependency_type.capitalize(),
                impact.reason
            ])
            item.setToolTip(0, f"Full path: {impact.target}")
            item.setData(0, Qt.UserRole, impact.target)
            
            # Highlight by type
            if impact.dependency_type == 'structural':
                item.setForeground(1, Qt.blue)
            elif impact.dependency_type == 'logical':
                item.setForeground(1, Qt.darkGreen)
                
            self.tree.addTopLevelItem(item)
            
        self.tree.expandAll()

    def clear(self):
        """Clear the view"""
        self.tree.clear()
        self.source_label.setText("Source: None")

    def _on_item_double_clicked(self, item, column):
        """Handle item double click for navigation"""
        path = item.data(0, Qt.UserRole)
        if path:
            self.item_requested.emit(path)
