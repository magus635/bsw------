from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QTreeWidget, QTreeWidgetItem, 
    QLabel, QHeaderView, QPushButton, QHBoxLayout
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QColor
from typing import List, Optional, Dict
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
        self.title_label = QLabel("🔍 配置变更影响分析 (Change Impact Analysis)")
        self.title_label.setStyleSheet("font-weight: bold; font-size: 14px;")
        layout.addWidget(self.title_label)
        
        self.source_label = QLabel("Source: None")
        self.source_label.setStyleSheet("color: gray;")
        self.source_label.setWordWrap(True)
        layout.addWidget(self.source_label)
        
        # Stats label
        self.stats_label = QLabel("")
        self.stats_label.setStyleSheet("color: #666; font-size: 11px;")
        layout.addWidget(self.stats_label)
        
        # Impact Tree
        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["受影响项 (Affected Item)", "依赖类型 (Type)", "原因 (Reason)"])
        self.tree.header().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.tree.setAlternatingRowColors(True)
        self.tree.itemDoubleClicked.connect(self._on_item_double_clicked)
        
        layout.addWidget(self.tree)
        
        # Actions
        btn_layout = QHBoxLayout()
        self.clear_btn = QPushButton("清除 (Clear)")
        self.clear_btn.clicked.connect(self.clear)
        btn_layout.addStretch()
        btn_layout.addWidget(self.clear_btn)
        
        layout.addLayout(btn_layout)
        
    def display_impacts(self, source_path: str, impacts: List[ImpactPath], stats: Optional[Dict] = None):
        """Populate the tree with impact data"""
        self.clear()
        self.source_label.setText(f"📍 源参数: {source_path}")
        
        # Show stats if provided
        if stats:
            self.stats_label.setText(
                f"📊 依赖图: {stats.get('total_nodes', 0)} 个节点, "
                f"{stats.get('total_edges', 0)} 条边 "
                f"(结构: {stats.get('structural_edges', 0)}, 推断: {stats.get('inferred_edges', 0)}, 逻辑: {stats.get('logical_edges', 0)})"
            )
            self.stats_label.show()
        else:
            self.stats_label.hide()
        
        if not impacts:
            # Show helpful message when no impacts found
            item = QTreeWidgetItem(["❌ 未发现受影响的配置项"])
            item.setForeground(0, QColor("#999"))
            self.tree.addTopLevelItem(item)
            
            # Add hint items
            hint1 = QTreeWidgetItem(["💡 提示: 此参数可能没有被其他配置项引用"])
            hint1.setForeground(0, QColor("#666"))
            self.tree.addTopLevelItem(hint1)
            
            hint2 = QTreeWidgetItem(["💡 提示: 运行 '分析跨模块依赖' 可发现更多逻辑依赖"])
            hint2.setForeground(0, QColor("#666"))
            self.tree.addTopLevelItem(hint2)
            return
            
        # Group impacts by dependency type for better visualization
        structural_impacts = [i for i in impacts if i.dependency_type == 'structural']
        logical_impacts = [i for i in impacts if i.dependency_type == 'logical']
        inferred_impacts = [i for i in impacts if i.dependency_type == 'inferred']
        
        # Add structural impacts
        if structural_impacts:
            structural_header = QTreeWidgetItem([f"🔗 结构依赖 ({len(structural_impacts)})"])
            structural_header.setExpanded(True)
            structural_header.setForeground(0, QColor("#0066cc"))
            self.tree.addTopLevelItem(structural_header)
            
            for impact in structural_impacts:
                # Extract short display name
                parts = impact.target.split('.')
                short_name = '.'.join(parts[-2:]) if len(parts) >= 2 else impact.target
                
                item = QTreeWidgetItem([
                    short_name,
                    "结构 (Structural)",
                    impact.reason
                ])
                item.setToolTip(0, f"完整路径: {impact.target}\n双击可导航到此配置项")
                item.setData(0, Qt.UserRole, impact.target)
                item.setForeground(1, QColor("#0066cc"))
                structural_header.addChild(item)
        
        # Add inferred impacts (pattern-based)
        if inferred_impacts:
            inferred_header = QTreeWidgetItem([f"🔍 推断依赖 ({len(inferred_impacts)})"])
            inferred_header.setExpanded(True)
            inferred_header.setForeground(0, QColor("#9932CC"))
            self.tree.addTopLevelItem(inferred_header)
            
            for impact in inferred_impacts:
                # Extract short display name: last two parts of path (Container.Param)
                parts = impact.target.split('.')
                short_name = '.'.join(parts[-2:]) if len(parts) >= 2 else impact.target
                
                item = QTreeWidgetItem([
                    short_name,
                    "推断 (Inferred)",
                    impact.reason
                ])
                # Store full path for navigation
                item.setToolTip(0, f"完整路径: {impact.target}\n双击可导航到此配置项")
                item.setData(0, Qt.UserRole, impact.target)
                item.setForeground(1, QColor("#9932CC"))
                inferred_header.addChild(item)
        
        # Add logical impacts (from AI)
        if logical_impacts:
            logical_header = QTreeWidgetItem([f"🧠 逻辑依赖 ({len(logical_impacts)})"])
            logical_header.setExpanded(True)
            logical_header.setForeground(0, QColor("#228B22"))
            self.tree.addTopLevelItem(logical_header)
            
            for impact in logical_impacts:
                # Extract short display name
                parts = impact.target.split('.')
                short_name = '.'.join(parts[-2:]) if len(parts) >= 2 else impact.target
                
                item = QTreeWidgetItem([
                    short_name,
                    "逻辑 (Logical)",
                    impact.reason
                ])
                item.setToolTip(0, f"完整路径: {impact.target}\n双击可导航到此配置项")
                item.setData(0, Qt.UserRole, impact.target)
                item.setForeground(1, QColor("#228B22"))
                logical_header.addChild(item)
            
        self.tree.expandAll()

    def clear(self):
        """Clear the view"""
        self.tree.clear()
        self.source_label.setText("Source: None")
        self.stats_label.setText("")

    def _on_item_double_clicked(self, item, column):
        """Handle item double click for navigation"""
        path = item.data(0, Qt.UserRole)
        if path:
            self.item_requested.emit(path)
