"""
Validation Results Dialog
Displays validation errors in a structured tree view with navigation capabilities.
"""
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QTreeWidget, QTreeWidgetItem,
    QLabel, QPushButton, QTextEdit, QSplitter, QWidget, QHeaderView
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QIcon, QColor, QBrush

class ValidationResultsDialog(QDialog):
    """Dialog for displaying validation results"""
    
    # Signal emitted when user requests to navigate to an error location
    # Arguments: path (str)
    navigate_requested = Signal(str)
    
    def __init__(self, errors, parent=None):
        super().__init__(parent)
        self.errors = errors
        self.setWindowTitle("Validation Results")
        self.resize(900, 600)
        
        self._setup_ui()
        self._populate_errors()
        
    def _setup_ui(self):
        """Setup the user interface"""
        layout = QVBoxLayout(self)
        
        # Header
        header_layout = QHBoxLayout()
        self.status_label = QLabel()
        self.status_label.setStyleSheet("font-size: 14px; font-weight: bold;")
        header_layout.addWidget(self.status_label)
        header_layout.addStretch()
        layout.addLayout(header_layout)
        
        # Main content splitter
        splitter = QSplitter(Qt.Vertical)
        layout.addWidget(splitter)
        
        # Error Tree
        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["Type", "Location", "Issue", "Suggestion"])
        self.tree.setAlternatingRowColors(True)
        self.tree.setSelectionMode(QTreeWidget.SingleSelection)
        self.tree.itemSelectionChanged.connect(self._on_selection_changed)
        self.tree.itemDoubleClicked.connect(self._on_item_double_clicked)
        
        # Configure columns
        header = self.tree.header()
        header.setSectionResizeMode(0, QHeaderView.ResizeToContents) # Type
        header.setSectionResizeMode(1, QHeaderView.Interactive)      # Location
        header.setSectionResizeMode(2, QHeaderView.Stretch)          # Issue
        header.setSectionResizeMode(3, QHeaderView.Stretch)          # Suggestion
        header.resizeSection(1, 250)
        
        splitter.addWidget(self.tree)
        
        # Details Panel
        details_widget = QWidget()
        details_layout = QVBoxLayout(details_widget)
        details_layout.setContentsMargins(0, 0, 0, 0)
        
        details_label = QLabel("Error Details:")
        details_label.setStyleSheet("font-weight: bold;")
        details_layout.addWidget(details_label)
        
        self.details_text = QTextEdit()
        self.details_text.setReadOnly(True)
        self.details_text.setStyleSheet("font-family: Consolas, monospace;")
        details_layout.addWidget(self.details_text)
        
        splitter.addWidget(details_widget)
        
        # Set initial splitter sizes (70% tree, 30% details)
        splitter.setSizes([400, 150])
        
        # Buttons
        button_layout = QHBoxLayout()
        
        self.goto_btn = QPushButton("Go to Element")
        self.goto_btn.clicked.connect(self._on_goto_clicked)
        self.goto_btn.setEnabled(False)
        
        close_btn = QPushButton("Close")
        close_btn.clicked.connect(self.accept)
        
        button_layout.addStretch()
        button_layout.addWidget(self.goto_btn)
        button_layout.addWidget(close_btn)
        layout.addLayout(button_layout)
        
    def _populate_errors(self):
        """Populate the error tree"""
        error_count = len(self.errors)
        
        if error_count == 0:
            self.status_label.setText("✅ Configuration is valid")
            self.status_label.setStyleSheet("color: green; font-size: 14px; font-weight: bold;")
            return
            
        self.status_label.setText(f"❌ Found {error_count} validation error(s)")
        self.status_label.setStyleSheet("color: red; font-size: 14px; font-weight: bold;")
        
        # Group errors by category
        categories = {
            "Invalid Value": [],
            "Missing Container": [],
            "Out of Range": [],
            "Other": []
        }
        
        for error in self.errors:
            msg = error.message
            if "not in allowed" in msg:
                categories["Invalid Value"].append(error)
            elif "requires at least" in msg:
                categories["Missing Container"].append(error)
            elif "out of range" in msg or ">" in msg or "<" in msg:
                categories["Out of Range"].append(error)
            else:
                categories["Other"].append(error)
        
        # Add items to tree
        for category, error_list in categories.items():
            if not error_list:
                continue
                
            cat_item = QTreeWidgetItem(self.tree)
            cat_item.setText(0, category)
            cat_item.setExpanded(True)
            # Make category row bold
            font = cat_item.font(0)
            font.setBold(True)
            cat_item.setFont(0, font)
            
            for error in error_list:
                item = QTreeWidgetItem(cat_item)
                
                # Parse error details
                path = getattr(error, 'path', 'Unknown')
                msg = error.message
                suggestion = self._get_suggestion(msg)
                
                # Set columns
                item.setText(0, "❌")
                item.setText(1, path)
                item.setText(2, self._clean_message(msg))
                item.setText(3, suggestion)
                
                # Store full error object
                item.setData(0, Qt.UserRole, error)
                
    def _clean_message(self, msg):
        """Clean up error message for table display"""
        # Remove path prefix if present in message
        if "][" in msg:
            if "] " in msg:
                return msg.split("] ", 1)[1]
        return msg
        
    def _get_suggestion(self, msg):
        """Generate suggestion based on error message"""
        if "not in allowed" in msg:
            return "Select a valid value from the dropdown list"
        elif "requires at least" in msg:
            return "Add required container instance"
        elif "out of range" in msg:
            return "Adjust value to be within allowed range"
        elif "must be of type" in msg:
            return "Enter a value of the correct type"
        return "Check configuration"
        
    def _on_selection_changed(self):
        """Handle item selection"""
        items = self.tree.selectedItems()
        if not items:
            self.details_text.clear()
            self.goto_btn.setEnabled(False)
            return
            
        item = items[0]
        error = item.data(0, Qt.UserRole)
        
        if error:
            # Show full details
            details = f"Location: {getattr(error, 'path', 'Unknown')}\n\n"
            details += f"Error: {error.message}\n\n"
            details += f"Suggestion: {self._get_suggestion(error.message)}"
            
            # Add specific details for enums
            if "allowed literals:" in error.message:
                try:
                    allowed = error.message.split("allowed literals:")[1].strip()
                    details += f"\n\nAllowed Values: {allowed}"
                except:
                    pass
                    
            self.details_text.setText(details)
            self.goto_btn.setEnabled(True)
        else:
            # Category item
            self.details_text.clear()
            self.goto_btn.setEnabled(False)
            
    def _on_item_double_clicked(self, item, column):
        """Handle double click to navigate"""
        error = item.data(0, Qt.UserRole)
        if error:
            self._navigate_to_error(error)
            
    def _on_goto_clicked(self):
        """Handle go to button click"""
        items = self.tree.selectedItems()
        if items:
            error = items[0].data(0, Qt.UserRole)
            if error:
                self._navigate_to_error(error)
                
    def _navigate_to_error(self, error):
        """Emit navigation signal"""
        path = getattr(error, 'path', None)
        if path:
            self.navigate_requested.emit(path)
