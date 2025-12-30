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



class ZoomableGraphicsView(QGraphicsView):
    """Graphics view with zoom support"""
    def __init__(self, scene, parent=None):
        super().__init__(scene, parent)
        self.setRenderHint(QPainter.Antialiasing)
        self.setDragMode(QGraphicsView.ScrollHandDrag)
        self.setTransformationAnchor(QGraphicsView.AnchorUnderMouse)
        self.setResizeAnchor(QGraphicsView.AnchorUnderMouse)
        
    def wheelEvent(self, event):
        """Handle zoom with mouse wheel (or forward to items for resize with Ctrl)"""
        # If Ctrl is held, forward the event to items (for node resizing)
        if event.modifiers() & Qt.ControlModifier:
            # Get item under cursor
            pos = event.position() if hasattr(event, 'position') else event.pos()
            scene_pos = self.mapToScene(pos.toPoint())
            item = self.scene().itemAt(scene_pos, self.transform())
            
            if item and hasattr(item, 'wheelEvent'):
                # Convert to scene event and forward
                # The item's wheelEvent expects a QGraphicsSceneWheelEvent but we have QWheelEvent
                # We need to handle this differently - call a custom resize method instead
                if hasattr(item, 'set_radius'):
                    delta = event.angleDelta().y()
                    scale_factor = 1.1 if delta > 0 else 0.9
                    new_radius = item.radius * scale_factor
                    item.set_radius(new_radius)
                    event.accept()
                    return
        
        # Default: zoom the view
        zoom_in_factor = 1.15
        zoom_out_factor = 1 / zoom_in_factor
        
        if event.angleDelta().y() > 0:
            zoom_factor = zoom_in_factor
        else:
            zoom_factor = zoom_out_factor
            
        self.scale(zoom_factor, zoom_factor)


class DependencyNode(QGraphicsEllipseItem):
    """Represents a container node in the dependency graph"""
    
    def __init__(self, name: str, node_type: str, x: float, y: float, radius: float = 40):
        super().__init__(-radius, -radius, radius * 2, radius * 2)
        
        self.name = name
        self.node_type = node_type
        self.radius = radius
        self._base_color = None
        self._collapsed = False
        self._saved_children_visibility = {}
        
        # Set position
        self.setPos(x, y)
        
        # Make it movable and selectable
        self.setFlag(QGraphicsItem.ItemIsMovable)
        self.setFlag(QGraphicsItem.ItemIsSelectable)
        self.setFlag(QGraphicsItem.ItemSendsGeometryChanges)
        self.setAcceptHoverEvents(True)
        
        # Set colors based on type
        if node_type == 'module':
            color = QColor(0, 120, 215)  # Blue
        elif node_type == 'container':
            color = QColor(76, 201, 176)  # Teal
        else:
            color = QColor(206, 145, 120)  # Orange
        
        self._base_color = color
        self.setBrush(QBrush(color))
        self.setPen(QPen(QColor(255, 255, 255), 2))
        
        # Track if this is a container (has children) - initialized before text update
        self._is_container = False
        
        # Add text label with dynamic sizing
        self.text = QGraphicsTextItem(name, self)
        self.text.setDefaultTextColor(Qt.white)
        self._update_text_size()
        
        # Tooltip
        self.setToolTip(f"{node_type}: {name}\n(Ctrl+滚轮调整大小, 双击展开/折叠)")
    
    def set_is_container(self, is_container: bool):
        """Mark if this node is a container with children (affects label positioning)"""
        self._is_container = is_container
        self._position_text()
    
    def _update_text_size(self):
        """Update text size based on node radius"""
        # Calculate appropriate font size based on radius
        font_size = max(6, min(14, int(self.radius / 4)))
        
        # Hide text if circle is too small
        if self.radius < 25:
            self.text.setVisible(False)
        else:
            self.text.setVisible(True)
            font = QFont("Arial", font_size, QFont.Bold)
            self.text.setFont(font)
            
            # Truncate text if too long for the circle
            max_chars = max(3, int(self.radius / 5))
            display_name = self.name[:max_chars] + "..." if len(self.name) > max_chars else self.name
            self.text.setPlainText(display_name)
        
        self._position_text()
    
    def _position_text(self):
        """Position the text label - at TOP edge for containers, centered for leaves"""
        text_rect = self.text.boundingRect()
        
        if self._is_container:
            # Place label at the TOP edge of the circle (inside the border)
            # This prevents overlap with children's labels
            x = -text_rect.width() / 2
            y = -self.radius + 5  # 5px padding from top
            self.text.setPos(x, y)
        else:
            # Leaf nodes: center the text
            self.text.setPos(-text_rect.width() / 2, -text_rect.height() / 2)
    
    def _center_text(self):
        """Legacy method - calls _position_text"""
        self._position_text()
    
    def set_radius(self, new_radius: float):
        """Update the node's radius"""
        if new_radius < 20:
            new_radius = 20  # Minimum size
        if new_radius > 500:
            new_radius = 500  # Maximum size
            
        self.radius = new_radius
        self.setRect(-new_radius, -new_radius, new_radius * 2, new_radius * 2)
        self._update_text_size()
        
        # Notify edges to update
        scene = self.scene()
        if scene and hasattr(scene, 'update_edges'):
            scene.update_edges()
    
    def mouseDoubleClickEvent(self, event):
        """Double-click to expand/collapse children"""
        children = self.childItems()
        # Filter only DependencyNode children (not text labels)
        node_children = [c for c in children if isinstance(c, DependencyNode)]
        
        if node_children:
            self._collapsed = not self._collapsed
            for child in node_children:
                child.setVisible(not self._collapsed)
            
            # Update visual to show collapsed state
            if self._collapsed:
                self.setPen(QPen(QColor(255, 200, 0), 4))  # Yellow border when collapsed
            else:
                # Restore original pen based on depth
                self.setPen(QPen(QColor(255, 255, 255), 2))
            
            # Update edges
            scene = self.scene()
            if scene and hasattr(scene, 'update_edges'):
                scene.update_edges()
        
        super().mouseDoubleClickEvent(event)
    
    def get_scene_center(self):
        """Get the center position in scene coordinates (handles nested items)"""
        return self.mapToScene(0, 0)
    
    def wheelEvent(self, event):
        """Handle mouse wheel for resizing (with Ctrl key)"""
        if event.modifiers() & Qt.ControlModifier:
            # Resize the node
            delta = event.delta() if hasattr(event, 'delta') else event.angleDelta().y()
            scale_factor = 1.1 if delta > 0 else 0.9
            new_radius = self.radius * scale_factor
            self.set_radius(new_radius)
            event.accept()
        else:
            # Pass to view for zooming
            event.ignore()
    
    def itemChange(self, change, value):
        """Handle item changes"""
        if change == QGraphicsItem.ItemPositionHasChanged:
            # Notify edges to update
            scene = self.scene()
            if scene and hasattr(scene, 'update_edges'):
                scene.update_edges()
        
        return super().itemChange(change, value)


class DependencyEdge(QGraphicsLineItem):
    """Represents a dependency edge (reference or containment) between nodes"""
    
    def __init__(self, source: DependencyNode, target: DependencyNode, label: str = "", edge_type: str = "reference"):
        super().__init__()
        
        self.source = source
        self.target = target
        self.label = label
        self.edge_type = edge_type
        self.label_offset = QPointF(0, 0)  # User-adjusted offset for label position
        
        # Set pen based on type
        if edge_type == "containment":
            # Solid line for parent-child relationship
            self.setPen(QPen(QColor(100, 100, 100), 2, Qt.SolidLine))
            self.setZValue(-2)  # Draw behind reference edges
        else:
            # Dashed line for references (more visible color)
            self.setPen(QPen(QColor(200, 100, 100), 2, Qt.DashLine))
            self.setZValue(-1)
        
        # Add draggable label if provided
        if label:
            self.label_item = DraggableLabel(label, self)
            self.label_item.setDefaultTextColor(QColor(80, 80, 80))
            font = QFont("Arial", 9)
            self.label_item.setFont(font)
            # Style the label with background
            self.label_item.setToolTip(f"Reference: {label}\n(可拖动调整位置)")
        else:
            self.label_item = None
        
        self.update_position()
    
    def update_position(self):
        """Update edge position based on node positions"""
        # Skip if source or target is hidden (collapsed)
        if not self.source.isVisible() or not self.target.isVisible():
            self.setVisible(False)
            if self.label_item:
                self.label_item.setVisible(False)
            return
        else:
            self.setVisible(True)
            if self.label_item:
                self.label_item.setVisible(True)
        
        # Use get_scene_center for correct nested item positioning
        source_pos = self.source.get_scene_center() if hasattr(self.source, 'get_scene_center') else self.source.scenePos()
        target_pos = self.target.get_scene_center() if hasattr(self.target, 'get_scene_center') else self.target.scenePos()
        
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
        
        # Update label position (midpoint + user offset)
        if self.label_item and not self.label_item.is_being_dragged:
            mid_x = (start_x + end_x) / 2
            mid_y = (start_y + end_y) / 2
            # Apply user offset
            self.label_item.setPos(mid_x + self.label_offset.x(), mid_y + self.label_offset.y())


class DraggableLabel(QGraphicsTextItem):
    """A text label that can be dragged by the user"""
    
    def __init__(self, text: str, parent_edge=None):
        super().__init__(text)
        self.parent_edge = parent_edge
        self.is_being_dragged = False
        
        # Make it movable
        self.setFlag(QGraphicsItem.ItemIsMovable)
        self.setFlag(QGraphicsItem.ItemIsSelectable)
        self.setFlag(QGraphicsItem.ItemSendsGeometryChanges)
        
        # Add background for visibility
        self.setZValue(10)  # Draw above edges
    
    def paint(self, painter, option, widget):
        """Custom paint to add background"""
        # Draw semi-transparent background
        rect = self.boundingRect()
        painter.setBrush(QBrush(QColor(255, 255, 220, 200)))  # Light yellow background
        painter.setPen(QPen(QColor(180, 180, 150), 1))
        painter.drawRoundedRect(rect, 3, 3)
        
        # Draw text
        super().paint(painter, option, widget)
    
    def mousePressEvent(self, event):
        """Track drag start"""
        self.is_being_dragged = True
        super().mousePressEvent(event)
    
    def mouseReleaseEvent(self, event):
        """Track drag end and save offset"""
        self.is_being_dragged = False
        
        # Calculate and save the offset from midpoint
        if self.parent_edge:
            line = self.parent_edge.line()
            mid_x = (line.x1() + line.x2()) / 2
            mid_y = (line.y1() + line.y2()) / 2
            current_pos = self.pos()
            self.parent_edge.label_offset = QPointF(
                current_pos.x() - mid_x,
                current_pos.y() - mid_y
            )
        
        super().mouseReleaseEvent(event)


class DependencyGraphWidget(QWidget):
    """Widget for displaying dependency graph"""
    
    node_clicked = Signal(str)  # Emits node name when clicked
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.nodes = {}  # name -> DependencyNode
        self.edges = []  # List of DependencyEdge
        
        # Data storage
        self.module_def = None
        self.configuration = None
        self.active_project = None
        
        self._setup_ui()
    
    def _setup_ui(self):
        """Setup the UI"""
        layout = QVBoxLayout(self)
        
        # Toolbar
        toolbar = QHBoxLayout()
        
        toolbar.addWidget(QLabel("Dependency Graph:"))
        
        # Layout selector
        self.layout_combo = QComboBox()
        self.layout_combo.addItems(["Circular", "Hierarchical", "Force-Directed", "Nested Clusters"])
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
        
        self.view = ZoomableGraphicsView(self.scene)
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
    
    def build_graph_project(self, project):
        """Build dependency graph for entire project"""
        self.active_project = project
        self.module_def = None
        self.configuration = None
        
        self.scene.clear()
        self.nodes.clear()
        self.edges.clear()
        
        if not project:
            return
            
        all_configs = []
        all_deps = {} # source -> targets
        all_containers = set() # full names of all internal containers
        
        # 1. Collect data from all modules
        for module_name, manager in project.module_managers.items():
            if manager.configuration:
                all_configs.append((manager.module_def, manager.configuration))
                
                # Analyze deps for this module
                module_deps = self._analyze_dependencies(manager.configuration, module_name)
                # Merge deps
                for src, targets in module_deps.items():
                    if src not in all_deps:
                        all_deps[src] = []
                    all_deps[src].extend(targets)
                
                # Collect internal container names to identify external nodes
                for container in manager.configuration.containers:
                    self._collect_container_names(container, all_containers, prefix=module_name)
                all_containers.add(module_name)
        
        # 2. Create Nodes
        node_names = set()
        
        # Add internal nodes (modules + containers)
        for mod_def, config in all_configs:
             node_names.add(mod_def.short_name)
             for container in config.containers:
                 self._collect_container_names(container, node_names, prefix=mod_def.short_name)
        
        # Add reference targets (some might be external/missing)
        for source, targets in all_deps.items():
            for target, ref_name in targets:
                node_names.add(target)
                
        # 3. Layout Nodes
        self._layout_nodes(list(node_names), self.layout_combo.currentText())
        
        # 4. Create Nodes (GraphicsItems) & Containment Edges
        # Reuse layout logic which created nodes in self.nodes, but we need to color them
        for name, node in self.nodes.items():
            if name not in all_containers:
                # Truly external to the project (or missing)
                 node.setBrush(QBrush(QColor(150, 150, 150))) # Gray
            elif '/' not in name:
                 # Module node
                 node.setBrush(QBrush(QColor(0, 120, 215))) # Blue
        
        # Create Containment Edges for all configs
        for mod_def, config in all_configs:
            self._add_containment_edges(config, mod_def.short_name)
            
        # 5. Create Reference Edges
        for source, targets in all_deps.items():
            if source in self.nodes:
                for target, ref_name in targets:
                    if target in self.nodes and source != target:
                        edge = DependencyEdge(
                            self.nodes[source],
                            self.nodes[target],
                            ref_name,
                            edge_type="reference"
                        )
                        self.scene.addItem(edge)
                        if edge.label_item:
                            self.scene.addItem(edge.label_item)
                        self.edges.append(edge)

        # Update info
        self.info_label.setText(
            f"Project: {len(all_configs)} Modules | Nodes: {len(self.nodes)} | Edges: {len(self.edges)}"
        )
        self.view.fitInView(self.scene.sceneRect(), Qt.KeepAspectRatio)

    def build_graph(self, module_def, configuration):
        """Build dependency graph from configuration"""
        # Store data for refresh/layout change
        self.module_def = module_def
        self.configuration = configuration
        self.active_project = None
        
        self.scene.clear()
        self.nodes.clear()
        self.edges.clear()
        
        if not module_def or not configuration:
            return
        
        # Analyze dependencies
        dependencies = self._analyze_dependencies(configuration, module_def.short_name)
        
        # Create nodes
        node_names = set()
        for container in configuration.containers:
            self._collect_container_names(container, node_names, prefix=module_def.short_name)
        
        # Add module node
        module_name = module_def.short_name
        node_names.add(module_name)
        
        # Add external reference targets as nodes
        for source, targets in dependencies.items():
            for target, ref_name in targets:
                node_names.add(target)
        
        # Layout nodes
        self._layout_nodes(list(node_names), self.layout_combo.currentText())
        
        # Assign node types based on whether they contain '/' to distinguish external nodes
        for name, node in self.nodes.items():
            # Mark external nodes (cross-module references) differently
            if '/' in name and not any(name.startswith(c.short_name + '/') for c in configuration.containers):
                # This is likely an external reference
                # BUT wait, with prefix=ModuleName, internal nodes ALSO look like path
                # We need better check: does it start with ModuleName?
                if not name.startswith(module_name + '/'):
                     node.setBrush(QBrush(QColor(150, 150, 150)))  # Gray for external
        
        # 1. Create Containment Edges (Parent -> Child)
        self._add_containment_edges(configuration, module_name)
        
        # 2. Create Reference Edges (Dependency)
        for source, targets in dependencies.items():
            if source in self.nodes:
                for target, ref_name in targets:
                    if target in self.nodes:
                        # Avoid self-loops if source == target (rare but possible)
                        if source == target:
                            continue
                            
                        edge = DependencyEdge(
                            self.nodes[source],
                            self.nodes[target],
                            ref_name,
                            edge_type="reference"
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

    def _add_containment_edges(self, configuration, module_name):
        """Add edges for containment relationships (Parent -> Child)"""
        # Skip if using Nested layout (redundant)
        if self.layout_combo.currentText() == "Nested Clusters":
            return

        # Module -> Top-level Containers
        for container in configuration.containers:
            full_name = f"{module_name}/{container.short_name}"

            if module_name in self.nodes and full_name in self.nodes:
                edge = DependencyEdge(
                    self.nodes[module_name],
                    self.nodes[full_name],
                    edge_type="containment"
                )
                self.scene.addItem(edge)
                self.edges.append(edge)
            
            # Recurse for sub-containers
            self._add_container_containment_edges(container, full_name)
    
    def _add_container_containment_edges(self, container, parent_full_name):
        """Recursively add edges for sub-containers"""
        for sub in container.sub_containers:
            full_name = f"{parent_full_name}/{sub.short_name}"
            
            if parent_full_name in self.nodes and full_name in self.nodes:
                edge = DependencyEdge(
                    self.nodes[parent_full_name],
                    self.nodes[full_name],
                    edge_type="containment"
                )
                self.scene.addItem(edge)
                self.edges.append(edge)
            
            # Recurse
            self._add_container_containment_edges(sub, full_name)
    
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
            self._analyze_container_deps(container, dependencies, module_name, prefix=module_name)
        
        return dependencies
    
    def _analyze_container_deps(self, container, deps: Dict, module_name: str, prefix=""):
        """Recursively analyze container dependencies"""
        full_name = f"{prefix}/{container.short_name}" if prefix else container.short_name
        
        # Check references
        for ref_name, ref_value in container.reference_values.items():
            target = ref_value.value_ref
            if target:
                # Extract target container name
                # Expected formats:
                # - Same module: /Config/Adc/AdcConfigSet/AdcHwUnit_0/AdcChannel_0
                # - Cross-module: /Config/Mcu/McuModuleConfiguration/McuClockSettingConfig/McuClockReferencePoint_ADC
                target_parts = target.split('/')
                
                # Remove empty parts
                parts = [p for p in target_parts if p]
                
                target_name = None
                
                # Skip 'Config' prefix if present
                if len(parts) > 0 and parts[0] == 'Config':
                    parts = parts[1:]  # Remove 'Config'
                
                # Now parts should be: [ModuleName, ContainerPath...]
                # We ALWAYS want ModuleName/ContainerPath to support correct nesting and unique IDs
                if len(parts) > 0:
                    target_name = '/'.join(parts)
                
                if target_name:
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
        elif layout_type == "Nested Clusters":
            self._layout_nested_clusters(names)
        else:
            self._layout_force_directed(names)
    
    def _layout_nested_clusters(self, names: List[str]):
        """Nested circle packing layout - children are visually inside parent circles"""
        
        # 1. Build Tree Structure from path names
        node_map = {}  # full_name -> {name, full_name, children, radius, depth}
        roots = []
        
        # Create entries for all names
        for name in names:
            depth = name.count('/')
            node_map[name] = {
                'name': name.split('/')[-1],  # Short name for display
                'full_name': name,
                'children': [],
                'radius': 0,
                'depth': depth
            }
        
        # Link children to parents based on path structure
        for name in names:
            node = node_map[name]
            if '/' in name:
                parent_path = name.rsplit('/', 1)[0]
                if parent_path in node_map:
                    node_map[parent_path]['children'].append(node)
                else:
                    # Parent not in graph (external reference), treat as root
                    roots.append(node)
            else:
                # Top-level node (module)
                roots.append(node)
        
        # 2. Calculate Radii (Bottom-Up)
        BASE_RADIUS = 35
        PADDING = 25
        
        def calc_radius(node):
            if not node['children']:
                node['radius'] = BASE_RADIUS
                return BASE_RADIUS
            
            # Calculate children radii first
            child_radii = [calc_radius(child) for child in node['children']]
            
            n = len(child_radii)
            max_r = max(child_radii)
            sum_r = sum(child_radii)
            
            # For single child: parent just needs to be larger
            if n == 1:
                node['radius'] = max_r + PADDING * 2
                return node['radius']
            
            # For multiple children arranged in a ring:
            # The ring radius is the distance from parent center to child centers
            # Each child occupies an arc of angle = 2*pi/n
            # The chord between adjacent children must be >= 2*max_r + padding
            # Chord length = 2 * ring_radius * sin(pi/n)
            # So: ring_radius >= (max_r + padding/2) / sin(pi/n)
            
            min_chord = 2 * max_r + PADDING
            ring_radius = min_chord / (2 * math.sin(math.pi / n)) if n > 1 else 0
            
            # Parent radius = ring_radius + max_child_radius + padding
            radius = ring_radius + max_r + PADDING
            
            # Ensure minimum radius
            node['radius'] = max(radius, max_r + PADDING * 3)
            return node['radius']
        
        for root in roots:
            calc_radius(root)
        
        # 3. Place Nodes (Top-Down, Recursive) with Parent-Child hierarchy
        def place_node(node, local_x, local_y, parent_item=None, depth_offset=0):
            """
            Place a node at (local_x, local_y) relative to parent_item.
            If parent_item is None, coordinates are in scene space.
            Children are set as QGraphicsItem children so they move with parent.
            """
            r = node['radius']
            node_type = 'module' if node['depth'] == 0 else 'container'
            
            # Create the visual node at LOCAL coordinates (relative to parent)
            # If no parent, the local coords are scene coords
            item = DependencyNode(node['name'], node_type, local_x, local_y, r)
            
            # Set parent-child relationship for grouped movement
            if parent_item:
                item.setParentItem(parent_item)
            else:
                # Root node: add to scene directly
                self.scene.addItem(item)
            
            # Style based on depth and whether it has children
            # Use different colors for different nesting levels
            depth = node['depth']
            
            if node['children']:
                # Container with children: semi-transparent with colored border
                # Color varies by depth for visual distinction
                if depth == 0:
                    # Module level - blue
                    fill_color = QColor(0, 120, 215, 50)
                    border_color = QColor(0, 80, 180)
                elif depth == 1:
                    # First level container - teal
                    fill_color = QColor(76, 201, 176, 60)
                    border_color = QColor(50, 160, 140)
                elif depth == 2:
                    # Second level - purple
                    fill_color = QColor(180, 120, 200, 70)
                    border_color = QColor(140, 80, 160)
                else:
                    # Deeper levels - orange
                    fill_color = QColor(220, 160, 100, 80)
                    border_color = QColor(180, 120, 60)
                
                item.setBrush(QBrush(fill_color))
                item.setPen(QPen(border_color, 3))
                item.setZValue(-100 + depth_offset)
            else:
                # Leaf node: solid color
                if depth == 1:
                    fill_color = QColor(76, 201, 176)
                elif depth == 2:
                    fill_color = QColor(180, 120, 200)
                else:
                    fill_color = QColor(220, 160, 100)
                
                item.setBrush(QBrush(fill_color))
                item.setPen(QPen(QColor(255, 255, 255), 2))
                item.setZValue(0 + depth_offset)
            
            # Set container flag for proper label positioning (top edge vs center)
            item.set_is_container(bool(node['children']))
            
            self.nodes[node['full_name']] = item
            
            # Place children inside this node's circle
            if not node['children']:
                return item
            
            children = node['children']
            n = len(children)
            
            if n == 1:
                # Single child: place at center (0, 0 relative to parent)
                place_node(children[0], 0, 0, parent_item=item, depth_offset=depth_offset + 1)
            else:
                # Multiple children: arrange in a circle inside the parent
                max_child_r = max(c['radius'] for c in children)
                inner_ring_radius = r - max_child_r - PADDING
                
                if inner_ring_radius < 0:
                    inner_ring_radius = r * 0.5
                
                for i, child in enumerate(children):
                    angle = 2 * math.pi * i / n
                    # Local coordinates relative to this parent's center
                    child_local_x = inner_ring_radius * math.cos(angle)
                    child_local_y = inner_ring_radius * math.sin(angle)
                    place_node(child, child_local_x, child_local_y, parent_item=item, depth_offset=depth_offset + 1)
            
            return item
        
        # 4. Place Root Nodes (Arrange horizontally with spacing) in scene coordinates
        roots = sorted(roots, key=lambda x: x['radius'], reverse=True)
        
        current_x = 0
        spacing = 50
        
        for i, root in enumerate(roots):
            r = root['radius']
            # Scene coordinates for root center
            cx = current_x + r
            cy = 0
            
            # Create root node and its children recursively
            root_item = place_node(root, cx, cy, parent_item=None, depth_offset=0)
            
            # Move x for next root
            current_x += 2 * r + spacing

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
        # Rebuild graph with new layout
        if self.active_project:
            self.build_graph_project(self.active_project)
        elif self.module_def and self.configuration:
            self.build_graph(self.module_def, self.configuration)
    
    def refresh_graph(self):
        """Refresh the graph"""
        if self.active_project:
            self.build_graph_project(self.active_project)
        elif self.module_def and self.configuration:
            self.build_graph(self.module_def, self.configuration)
    
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
