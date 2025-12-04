"""
Smart Search Widget for AUTOSAR Configurator
Provides fuzzy search across containers, parameters, and values
"""
from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QLineEdit, 
    QListWidget, QListWidgetItem, QLabel, QPushButton
)
from PySide6.QtCore import Qt, Signal, QTimer
from PySide6.QtGui import QIcon
from typing import List, Dict, Any, Optional
import re


class SearchResult:
    """Represents a search result"""
    
    def __init__(self, result_type: str, path: str, name: str, 
                 value: Any = None, score: float = 0.0):
        self.type = result_type  # 'container', 'parameter', 'reference'
        self.path = path  # Full path to the item
        self.name = name  # Display name
        self.value = value  # Current value (for parameters)
        self.score = score  # Relevance score
    
    def __repr__(self):
        return f"SearchResult({self.type}, {self.path}, score={self.score})"


class SmartSearchWidget(QWidget):
    """Smart search widget with fuzzy matching"""
    
    # Signal emitted when user selects a result
    result_selected = Signal(str, str)  # (result_type, path)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.search_index = []  # List of searchable items
        self.search_timer = QTimer()
        self.search_timer.setSingleShot(True)
        self.search_timer.timeout.connect(self._perform_search)
        
        self._setup_ui()
    
    def _setup_ui(self):
        """Setup the search UI"""
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        
        # Search input
        search_layout = QHBoxLayout()
        
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("🔍 Search containers, parameters, values...")
        self.search_input.textChanged.connect(self._on_search_text_changed)
        self.search_input.returnPressed.connect(self._on_enter_pressed)
        search_layout.addWidget(self.search_input)
        
        # Clear button
        self.clear_btn = QPushButton("✕")
        self.clear_btn.setMaximumWidth(30)
        self.clear_btn.clicked.connect(self.clear_search)
        search_layout.addWidget(self.clear_btn)
        
        layout.addLayout(search_layout)
        
        # Results count label
        self.results_label = QLabel("Type to search...")
        self.results_label.setStyleSheet("color: gray; font-size: 10px;")
        layout.addWidget(self.results_label)
        
        # Results list
        self.results_list = QListWidget()
        self.results_list.itemDoubleClicked.connect(self._on_result_double_clicked)
        self.results_list.setStyleSheet("""
            QListWidget {
                border: 1px solid #ccc;
                border-radius: 3px;
            }
            QListWidget::item {
                padding: 5px;
            }
            QListWidget::item:selected {
                background-color: #0078d4;
                color: white;
            }
            QListWidget::item:hover {
                background-color: #e5e5e5;
            }
        """)
        layout.addWidget(self.results_list)
    
    def build_search_index(self, module_def, configuration=None):
        """Build search index from module definition and configuration
        
        Args:
            module_def: Module definition (always required)
            configuration: Configuration (optional, if None only indexes definitions)
        """
        self.search_index = []
        
        # Always index DEF file definitions
        self._index_definitions(module_def)
        
        # Index configuration values if available
        if configuration:
            for container in configuration.containers:
                self._index_container(container, module_def)
        
        print(f"📚 Search index built: {len(self.search_index)} items")
    
    def _index_definitions(self, module_def):
        """Index container and parameter definitions from DEF file"""
        for container_name, container_def in module_def.containers.items():
            # Index container definition
            self.search_index.append({
                'type': 'container_def',
                'path': container_name,
                'name': container_name,
                'description': container_def.description or "",
                'definition': f"Definition: {container_name}"
            })
            
            # Index parameter definitions
            for param_name, param_def in container_def.parameters.items():
                param_path = f"{container_name}/{param_name}"
                
                self.search_index.append({
                    'type': 'parameter_def',
                    'path': param_path,
                    'name': param_name,
                    'description': param_def.description or "",
                    'container': container_name,
                    'param_type': str(param_def.param_type) if param_def.param_type else "UNKNOWN"
                })
            
            # Recursively index sub-container definitions
            self._index_subcontainer_defs(container_def, container_name)
    
    def _index_subcontainer_defs(self, container_def, parent_path=""):
        """Recursively index sub-container definitions"""
        for sub_name, sub_def in container_def.sub_containers.items():
            sub_path = f"{parent_path}/{sub_name}"
            
            # Index sub-container
            self.search_index.append({
                'type': 'container_def',
                'path': sub_path,
                'name': sub_name,
                'description': sub_def.description or "",
                'definition': f"Definition: {sub_path}"
            })
            
            # Index its parameters
            for param_name, param_def in sub_def.parameters.items():
                param_path = f"{sub_path}/{param_name}"
                
                self.search_index.append({
                    'type': 'parameter_def',
                    'path': param_path,
                    'name': param_name,
                    'description': param_def.description or "",
                    'container': sub_path,
                    'param_type': str(param_def.param_type) if param_def.param_type else "UNKNOWN"
                })
            
            # Recurse
            self._index_subcontainer_defs(sub_def, sub_path)
    
    def _index_container(self, container, module_def, parent_path=""):
        """Recursively index a container and its contents"""
        # Get container definition
        container_def = module_def.get_container_def(
            container.definition_ref.split('/')[-1] if '/' in container.definition_ref 
            else container.definition_ref
        )
        
        if not container_def:
            return
        
        # Build path
        current_path = f"{parent_path}/{container.short_name}" if parent_path else container.short_name
        
        # Index the container itself
        self.search_index.append({
            'type': 'container',
            'path': current_path,
            'name': container.short_name,
            'description': container_def.description if container_def else "",
            'definition': container.definition_ref
        })
        
        # Index parameters
        for param_name, param_value in container.parameter_values.items():
            param_path = f"{current_path}/{param_name}"
            param_def = container_def.parameters.get(param_name) if container_def else None
            
            self.search_index.append({
                'type': 'parameter',
                'path': param_path,
                'name': param_name,
                'value': param_value.value,
                'description': param_def.description if param_def else "",
                'container': current_path
            })
        
        # Index references
        for ref_name, ref_value in container.reference_values.items():
            ref_path = f"{current_path}/{ref_name}"
            
            self.search_index.append({
                'type': 'reference',
                'path': ref_path,
                'name': ref_name,
                'value': ref_value.value_ref,
                'container': current_path
            })
        
        # Recursively index sub-containers
        for sub_container in container.sub_containers:
            self._index_container(sub_container, module_def, current_path)
    
    def _on_search_text_changed(self, text: str):
        """Handle search text changes with debouncing"""
        if not text:
            self.results_list.clear()
            self.results_label.setText("Type to search...")
            return
        
        # Debounce search (wait 300ms after user stops typing)
        self.search_timer.stop()
        self.search_timer.start(300)
    
    def _perform_search(self):
        """Perform the actual search"""
        query = self.search_input.text().strip()
        if not query:
            return
        
        # Search and rank results
        results = self._fuzzy_search(query)
        
        # Display results
        self._display_results(results)
    
    def _fuzzy_search(self, query: str) -> List[SearchResult]:
        """Perform fuzzy search with scoring"""
        query_lower = query.lower()
        query_parts = query_lower.split()
        
        results = []
        
        for item in self.search_index:
            score = 0.0
            
            # Search in name
            name_lower = item['name'].lower()
            if query_lower in name_lower:
                score += 10.0
                if name_lower.startswith(query_lower):
                    score += 5.0
            
            # Search in path
            path_lower = item['path'].lower()
            if query_lower in path_lower:
                score += 5.0
            
            # Search in description
            desc_lower = item.get('description', '').lower()
            if query_lower in desc_lower:
                score += 3.0
            
            # Search in value (for parameters)
            if 'value' in item and item['value']:
                value_str = str(item['value']).lower()
                if query_lower in value_str:
                    score += 7.0
            
            # Multi-word search (all words must match somewhere)
            if len(query_parts) > 1:
                all_match = True
                for part in query_parts:
                    if not (part in name_lower or part in path_lower or 
                           part in desc_lower):
                        all_match = False
                        break
                if all_match:
                    score += 8.0
            
            # Fuzzy matching (simple Levenshtein-like)
            if score == 0:
                # Check if query is a subsequence of name
                if self._is_subsequence(query_lower, name_lower):
                    score += 2.0
            
            if score > 0:
                results.append(SearchResult(
                    result_type=item['type'],
                    path=item['path'],
                    name=item['name'],
                    value=item.get('value'),
                    score=score
                ))
        
        # Sort by score (descending)
        results.sort(key=lambda r: r.score, reverse=True)
        
        # Limit to top 50 results
        return results[:50]
    
    def _is_subsequence(self, subseq: str, seq: str) -> bool:
        """Check if subseq is a subsequence of seq"""
        it = iter(seq)
        return all(c in it for c in subseq)
    
    def _display_results(self, results: List[SearchResult]):
        """Display search results in the list"""
        self.results_list.clear()
        
        if not results:
            self.results_label.setText("No results found")
            return
        
        self.results_label.setText(f"Found {len(results)} result(s)")
        
        for result in results:
            # Create list item
            item = QListWidgetItem()
            
            # Format display text
            icon = self._get_type_icon(result.type)
            text = f"{icon} {result.name}"
            
            if result.value is not None:
                text += f" = {result.value}"
            
            text += f"\n   📍 {result.path}"
            
            item.setText(text)
            item.setData(Qt.UserRole, result)
            
            self.results_list.addItem(item)
    
    def _get_type_icon(self, result_type: str) -> str:
        """Get icon for result type"""
        icons = {
            'container': '📦',
            'container_def': '📋',
            'parameter': '⚙️',
            'parameter_def': '📝',
            'reference': '🔗'
        }
        return icons.get(result_type, '📄')
    
    def _on_result_double_clicked(self, item: QListWidgetItem):
        """Handle result double-click"""
        result = item.data(Qt.UserRole)
        if result:
            self.result_selected.emit(result.type, result.path)
    
    def _on_enter_pressed(self):
        """Handle Enter key in search box"""
        if self.results_list.count() > 0:
            # Select first result
            first_item = self.results_list.item(0)
            self._on_result_double_clicked(first_item)
    
    def clear_search(self):
        """Clear search input and results"""
        self.search_input.clear()
        self.results_list.clear()
        self.results_label.setText("Type to search...")
    
    def focus_search(self):
        """Focus the search input"""
        self.search_input.setFocus()
        self.search_input.selectAll()
