"""
Search dialog for finding configuration elements
"""
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLineEdit, QPushButton,
    QListWidget, QListWidgetItem, QLabel, QComboBox, QCheckBox,
    QGroupBox, QMessageBox
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QKeySequence, QShortcut
from typing import Optional, List

from ...core.search_engine import SearchEngine, SearchMode, SearchResult
from ...core.model.container import Container


class SearchDialog(QDialog):
    """Dialog for searching configuration elements"""
    
    # Signal emitted when user wants to navigate to a result
    navigate_to_result = Signal(SearchResult)
    
    def __init__(self, root_container: Optional[Container] = None, parent=None):
        super().__init__(parent)
        
        self.root_container = root_container
        self.search_engine = SearchEngine()
        self.current_results: List[SearchResult] = []
        self.current_index = -1
        
        self._setup_ui()
        self._connect_signals()
        
        # Set dialog properties
        self.setWindowTitle("Search Configuration")
        self.setMinimumSize(600, 500)
        self.setModal(False)  # Allow interaction with main window
    
    def _setup_ui(self):
        """Setup the user interface"""
        layout = QVBoxLayout(self)
        
        # Search input group
        search_group = QGroupBox("Search")
        search_layout = QVBoxLayout(search_group)
        
        # Search input row
        input_layout = QHBoxLayout()
        
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Enter search query...")
        input_layout.addWidget(self.search_input)
        
        self.search_button = QPushButton("Search")
        self.search_button.setDefault(True)
        input_layout.addWidget(self.search_button)
        
        search_layout.addLayout(input_layout)
        
        # Search options row
        options_layout = QHBoxLayout()
        
        # Search mode
        options_layout.addWidget(QLabel("Search in:"))
        self.mode_combo = QComboBox()
        self.mode_combo.addItem("All Fields", SearchMode.ALL)
        self.mode_combo.addItem("Name", SearchMode.NAME)
        self.mode_combo.addItem("Description", SearchMode.DESCRIPTION)
        self.mode_combo.addItem("Value", SearchMode.VALUE)
        options_layout.addWidget(self.mode_combo)
        
        # Case sensitive
        self.case_sensitive_check = QCheckBox("Case Sensitive")
        options_layout.addWidget(self.case_sensitive_check)
        
        # Regex
        self.regex_check = QCheckBox("Use Regex")
        options_layout.addWidget(self.regex_check)
        
        options_layout.addStretch()
        
        search_layout.addLayout(options_layout)
        layout.addWidget(search_group)
        
        # Results group
        results_group = QGroupBox("Results")
        results_layout = QVBoxLayout(results_group)
        
        # Results count label
        self.results_label = QLabel("No results")
        results_layout.addWidget(self.results_label)
        
        # Results list
        self.results_list = QListWidget()
        self.results_list.setAlternatingRowColors(True)
        results_layout.addWidget(self.results_list)
        
        layout.addWidget(results_group)
        
        # Navigation buttons
        nav_layout = QHBoxLayout()
        
        self.prev_button = QPushButton("Previous")
        self.prev_button.setEnabled(False)
        nav_layout.addWidget(self.prev_button)
        
        self.next_button = QPushButton("Next")
        self.next_button.setEnabled(False)
        nav_layout.addWidget(self.next_button)
        
        nav_layout.addStretch()
        
        self.goto_button = QPushButton("Go To Selected")
        self.goto_button.setEnabled(False)
        nav_layout.addWidget(self.goto_button)
        
        self.close_button = QPushButton("Close")
        nav_layout.addWidget(self.close_button)
        
        layout.addLayout(nav_layout)
        
        # Setup keyboard shortcuts
        self.search_shortcut = QShortcut(QKeySequence(Qt.Key_Return), self.search_input)
        self.search_shortcut.activated.connect(self._perform_search)
    
    def _connect_signals(self):
        """Connect widget signals"""
        self.search_button.clicked.connect(self._perform_search)
        self.search_input.returnPressed.connect(self._perform_search)
        self.results_list.itemDoubleClicked.connect(self._on_result_double_clicked)
        self.results_list.currentRowChanged.connect(self._on_selection_changed)
        self.prev_button.clicked.connect(self._navigate_previous)
        self.next_button.clicked.connect(self._navigate_next)
        self.goto_button.clicked.connect(self._goto_selected)
        self.close_button.clicked.connect(self.close)
    
    def set_root_container(self, container: Container):
        """Set the root container to search in"""
        self.root_container = container
    
    def _perform_search(self):
        """Perform the search"""
        if not self.root_container:
            QMessageBox.warning(
                self,
                "No Configuration",
                "Please open or create a configuration first."
            )
            return
        
        query = self.search_input.text().strip()
        if not query:
            return
        
        # Get search parameters
        mode = self.mode_combo.currentData()
        case_sensitive = self.case_sensitive_check.isChecked()
        use_regex = self.regex_check.isChecked()
        
        # Perform search
        try:
            self.current_results = self.search_engine.search(
                self.root_container,
                query,
                mode,
                case_sensitive,
                use_regex
            )
        except Exception as e:
            QMessageBox.critical(
                self,
                "Search Error",
                f"An error occurred during search:\n{str(e)}"
            )
            return
        
        # Update results display
        self._display_results()
    
    def _display_results(self):
        """Display search results in the list"""
        self.results_list.clear()
        
        count = len(self.current_results)
        self.results_label.setText(f"Found {count} result{'s' if count != 1 else ''}")
        
        for result in self.current_results:
            # Create display text
            item_text = f"[{result.element_type}] {result.display_name}"
            item_text += f"\n  Path: {result.path}"
            item_text += f"\n  Matched: {result.match_field} = '{result.match_text}'"
            
            item = QListWidgetItem(item_text)
            item.setData(Qt.UserRole, result)
            self.results_list.addItem(item)
        
        # Update navigation buttons
        self._update_navigation_buttons()
        
        # Select first result if available
        if count > 0:
            self.results_list.setCurrentRow(0)
            self.current_index = 0
    
    def _update_navigation_buttons(self):
        """Update navigation button states"""
        has_results = len(self.current_results) > 0
        self.prev_button.setEnabled(has_results and self.current_index > 0)
        self.next_button.setEnabled(has_results and self.current_index < len(self.current_results) - 1)
        self.goto_button.setEnabled(has_results)
    
    def _on_selection_changed(self, current_row: int):
        """Handle selection change in results list"""
        if current_row >= 0:
            self.current_index = current_row
            self._update_navigation_buttons()
    
    def _navigate_previous(self):
        """Navigate to previous result"""
        if self.current_index > 0:
            self.current_index -= 1
            self.results_list.setCurrentRow(self.current_index)
            self._goto_current()
    
    def _navigate_next(self):
        """Navigate to next result"""
        if self.current_index < len(self.current_results) - 1:
            self.current_index += 1
            self.results_list.setCurrentRow(self.current_index)
            self._goto_current()
    
    def _goto_selected(self):
        """Go to the selected result"""
        self._goto_current()
    
    def _goto_current(self):
        """Navigate to current result"""
        if 0 <= self.current_index < len(self.current_results):
            result = self.current_results[self.current_index]
            self.navigate_to_result.emit(result)
    
    def _on_result_double_clicked(self, item: QListWidgetItem):
        """Handle double-click on result item"""
        result = item.data(Qt.UserRole)
        if result:
            self.navigate_to_result.emit(result)
    
    def focus_search_input(self):
        """Focus the search input field"""
        self.search_input.setFocus()
        self.search_input.selectAll()
