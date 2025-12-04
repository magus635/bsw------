"""
Dependency Graph Widget for AUTOSAR Configurator
Visualizes container and reference dependencies
"""
from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton, 
    QLabel, QComboBox, QGraphicsView, QGraphicsScene,
    QGraphicsEllipseItem, QGraphicsLineItem, QGraphicsTextItem,
    QGraphicsItem
)
from PySide6.QtCore import Qt, QPointF, QRectF, Signal
from PySide6.QtGui import QPen, QBrush, QColor, QPainter, QFont
from typing import Dict, List, Set, Tuple
import math


class DependencyNode(QGraphicsEllipseItem):
    """Represents a container node in the dependency graph"""
    
    def __init__(self, name: str, node_type: str, x: float, y: float, radius: float = 40):
        super().__init__(-radius, -radius, radius * 2, radius * 2)
        
        self.name = name
        self.node_type = node_type
        self.radius = radius
        
        # Set position
        self.setPos(x, y)
        
        # Make it movable
        self.setFlag(QGraphicsItem.ItemIsMovable)
        self.setFlag(QGraphicsItem.ItemSendsGeometryChanges)
        
        # Set colors based on type
        if node_type == 'module':
            color = QColor(0, 120, 215)  # Blue
        elif node_type == 'container':
            color = QColor(76, 201, 176)  # Teal
        else:
            color = QColor(206, 145, 120)  # Orange
        
        self.setBrush(QBrush(color))
        self.setPen(QPen(QColor(255, 255, 255), 2))
        
        # Add text label
        self.text = QGraphicsTextItem(name, self)
        self.text.setDefaultTextColor(Qt.white)
        font = QFont("Arial", 10, QFont.Bold)
        self.text.setFont(font)
        
        # Center text
        text_rect = self.text.boundingRect()
        self.text.setPos(-text_rect.width() / 2, -text_rect.height() / 2)
        
        # Tooltip
        self.setToolTip(f"{node_type}: {name}")
    
    def itemChange(self, change, value):
        """Handle item changes"""
        if change == QGraphicsItem.ItemPositionHasChanged:
            # Notify edges to update
            scene = self.scene()
            if scene and hasattr(scene, 'update_edges'):
                scene.update_edges()
        
        return super().itemChange(change, value)


class DependencyEdge(QGraphicsLineItem):
    """Represents a dependency edge (reference) between nodes"""
    
    def __init__(self, source: DependencyNode, target: DependencyNode, label: str = ""):
        super().__init__()
        
        self.source = source
        self.target = target
        self.label = label
        
        # Set pen
        self.setPen(QPen(QColor(150, 150, 150), 2, Qt.SolidLine))
        
        # Add arrow
        self.setZValue(-1)  # Draw behind nodes
        
        # Add label if provided
        if label:
            self.label_item = QGraphicsTextItem(label)
            self.label_item.setDefaultTextColor(QColor(100, 100, 100))
            font = QFont("Arial", 8)
            self.label_item.setFont(font)
        else:
            self.label_item = None
        
        self.update_position()
    
    def update_position(self):
        """Update edge position based on node positions"""
        source_pos = self.source.scenePos()
        target_pos = self.target.scenePos()
        
        # Calculate line from edge of circles
        dx = target_pos.x() - source_pos.x()
        dy = target_pos.y() - source_pos.y()
        distance = math.sqrt(dx * dx + dy * dy)
        
        if distance == 0:
            return
        
        # Offset by radius
        offset = self.source.radius
        start_x = source_pos.x() + (dx / distance) * offset
        start_y = source_pos.y() + (dy / distance) * offset
        
        offset = self.target.radius
        end_x = target_pos.x() - (dx / distance) * offset
        end_y = target_pos.y() - (dy / distance) * offset
        
        self.setLine(start_x, start_y, end_x, end_y)
        
        # Update label position
        if self.label_item:
            mid_x = (start_x + end_x) / 2
            mid_y = (start_y + end_y) / 2
            self.label_item.setPos(mid_x, mid_y)


class DependencyGraphWidget(QWidget):
    """Widget for displaying dependency graph"""
    
    node_clicked = Signal(str)  # Emits node name when clicked
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.nodes = {}  # name -> DependencyNode
        self.edges = []  # List of DependencyEdge
        
        self._setup_ui()
    
    def _setup_ui(self):
        """Setup the UI"""
        layout = QVBoxLayout(self)
        
        # Toolbar
        toolbar = QHBoxLayout()
        
        toolbar.addWidget(QLabel("Dependency Graph:"))
        
        # Layout selector
        self.layout_combo = QComboBox()
        self.layout_combo.addItems(["Circular", "Hierarchical", "Force-Directed"])
        self.layout_combo.currentTextChanged.connect(self._on_layout_changed)
        toolbar.addWidget(self.layout_combo)
        
        # Refresh button
        refresh_btn = QPushButton("🔄 Refresh")
        refresh_btn.clicked.connect(self.refresh_graph)
        toolbar.addWidget(refresh_btn)
        
        # Export button
        export_btn = QPushButton("💾 Export")
        export_btn.clicked.connect(self.export_graph)
        toolbar.addWidget(export_btn)
        
        toolbar.addStretch()
        
        layout.addLayout(toolbar)
        
        # Graphics view
        self.scene = QGraphicsScene()
        self.scene.update_edges = self._update_all_edges
        
        self.view = QGraphicsView(self.scene)
        self.view.setRenderHint(QPainter.Antialiasing)
        self.view.setDragMode(QGraphicsView.ScrollHandDrag)
        self.view.setStyleSheet("""
            QGraphicsView {
                background-color: #f5f5f5;
                border: 1px solid #ccc;
            }
        """)
        
        layout.addWidget(self.view)
        
        # Info label
        self.info_label = QLabel("No data loaded")
        self.info_label.setStyleSheet("color: gray; font-size: 10px;")
        layout.addWidget(self.info_label)
    
    def build_graph(self, module_def, configuration):
        """Build dependency graph from configuration"""
        self.scene.clear()
        self.nodes.clear()
        self.edges.clear()
        
        # Analyze dependencies
        dependencies = self._analyze_dependencies(configuration, module_def.short_name)
        
        # Create nodes
        node_names = set()
        for container in configuration.containers:
            self._collect_container_names(container, node_names)
        
        # Add module node
        module_name = module_def.short_name
        node_names.add(module_name)
        
        # Layout nodes
        self._layout_nodes(list(node_names), self.layout_combo.currentText())
        
        # Create edges for dependencies
        for source, targets in dependencies.items():
            if source in self.nodes:
                for target, ref_name in targets:
                    if target in self.nodes:
                        edge = DependencyEdge(
                            self.nodes[source],
                            self.nodes[target],
                            ref_name
                        )
                        self.scene.addItem(edge)
                        if edge.label_item:
                            self.scene.addItem(edge.label_item)
                        self.edges.append(edge)
        
        # Update info
        self.info_label.setText(
            f"Nodes: {len(self.nodes)} | Edges: {len(self.edges)}"
        )
        
        # Fit in view
        self.view.fitInView(self.scene.sceneRect(), Qt.KeepAspectRatio)
    
    def _collect_container_names(self, container, names: Set[str], prefix=""):
        """Recursively collect container names"""
        full_name = f"{prefix}/{container.short_name}" if prefix else container.short_name
        names.add(full_name)
        
        for sub in container.sub_containers:
            self._collect_container_names(sub, names, full_name)
    
    def _analyze_dependencies(self, configuration, module_name: str) -> Dict[str, List[Tuple[str, str]]]:
        """Analyze reference dependencies"""
        dependencies = {}
        
        for container in configuration.containers:
            self._analyze_container_deps(container, dependencies, module_name)
        
        return dependencies
    
    def _analyze_container_deps(self, container, deps: Dict, module_name: str, prefix=""):
        """Recursively analyze container dependencies"""
        full_name = f"{prefix}/{container.short_name}" if prefix else container.short_name
        
        # Check references
        for ref_name, ref_value in container.reference_values.items():
            target = ref_value.value_ref
            if target:
                print(f"🔗 Found reference: {full_name} --[{ref_name}]--> {target}")
                
                # Extract target container name
                # Expected format: /Config/{ModuleName}/{ContainerPath}
                target_parts = target.split('/')
                
                # Remove empty parts
                parts = [p for p in target_parts if p]
                
                target_name = None
                
                # Check if it starts with Config/ModuleName
                if len(parts) > 2 and parts[0] == 'Config' and parts[1] == module_name:
                    # Strip Config and ModuleName
                    target_name = '/'.join(parts[2:])
                elif len(parts) > 0:
                    # Fallback: try to match by suffix or just use as is
                    # If it's a relative path or different format
                    target_name = '/'.join(parts)
                
                if target_name:
                    print(f"   → Parsed target: {target_name}")
                    
                    if full_name not in deps:
                        deps[full_name] = []
                    deps[full_name].append((target_name, ref_name))
        
        # Recurse
        for sub in container.sub_containers:
            self._analyze_container_deps(sub, deps, module_name, full_name)
    
    def _layout_nodes(self, names: List[str], layout_type: str):
        """Layout nodes using specified algorithm"""
        if layout_type == "Circular":
            self._layout_circular(names)
        elif layout_type == "Hierarchical":
            self._layout_hierarchical(names)
        else:
            self._layout_force_directed(names)
    
    def _layout_circular(self, names: List[str]):
        """Circular layout"""
        center_x, center_y = 0, 0
        radius = 200
        
        for i, name in enumerate(names):
            angle = 2 * math.pi * i / len(names)
            x = center_x + radius * math.cos(angle)
            y = center_y + radius * math.sin(angle)
            
            node_type = 'module' if '/' not in name else 'container'
            node = DependencyNode(name.split('/')[-1], node_type, x, y)
            self.scene.addItem(node)
            self.nodes[name] = node
    
    def _layout_hierarchical(self, names: List[str]):
        """Hierarchical layout (tree-like)"""
        # Group by depth
        levels = {}
        for name in names:
            depth = name.count('/')
            if depth not in levels:
                levels[depth] = []
            levels[depth].append(name)
        
        y_offset = -200
        y_spacing = 150
        
        for depth in sorted(levels.keys()):
            nodes_at_level = levels[depth]
            x_spacing = 800 / (len(nodes_at_level) + 1)
            
            for i, name in enumerate(nodes_at_level):
                x = -400 + x_spacing * (i + 1)
                y = y_offset + depth * y_spacing
                
                node_type = 'module' if depth == 0 else 'container'
                node = DependencyNode(name.split('/')[-1], node_type, x, y)
                self.scene.addItem(node)
                self.nodes[name] = node
    
    def _layout_force_directed(self, names: List[str]):
        """Simple force-directed layout"""
        # Start with random positions
        import random
        for name in names:
            x = random.uniform(-300, 300)
            y = random.uniform(-300, 300)
            
            node_type = 'module' if '/' not in name else 'container'
            node = DependencyNode(name.split('/')[-1], node_type, x, y)
            self.scene.addItem(node)
            self.nodes[name] = node
    
    def _update_all_edges(self):
        """Update all edge positions"""
        for edge in self.edges:
            edge.update_position()
    
    def _on_layout_changed(self, layout_type: str):
        """Handle layout change"""
        # Re-layout existing nodes
        if self.nodes:
            names = list(self.nodes.keys())
            
            # Remove old nodes
            for node in self.nodes.values():
                self.scene.removeItem(node)
            self.nodes.clear()
            
            # Re-layout
            self._layout_nodes(names, layout_type)
            
            # Update edges
            self._update_all_edges()
    
    def refresh_graph(self):
        """Refresh the graph"""
        # Trigger rebuild from parent
        pass
    
    def export_graph(self):
        """Export graph as image"""
        from PySide6.QtWidgets import QFileDialog
        from PySide6.QtGui import QImage, QPainter
        
        filename, _ = QFileDialog.getSaveFileName(
            self,
            "Export Graph",
            "",
            "PNG Image (*.png);;SVG Image (*.svg)"
        )
        
        if filename:
            if filename.endswith('.png'):
                # Export as PNG
                rect = self.scene.sceneRect()
                image = QImage(int(rect.width()), int(rect.height()), 
                             QImage.Format_ARGB32)
                image.fill(Qt.white)
                
                painter = QPainter(image)
                painter.setRenderHint(QPainter.Antialiasing)
                self.scene.render(painter)
                painter.end()
                
                image.save(filename)
            else:
                # Export as SVG
                from PySide6.QtSvg import QSvgGenerator
                
                generator = QSvgGenerator()
                generator.setFileName(filename)
                rect = self.scene.sceneRect()
                generator.setSize(rect.size().toSize())
                generator.setViewBox(rect)
                
                painter = QPainter(generator)
                self.scene.render(painter)
                painter.end()
