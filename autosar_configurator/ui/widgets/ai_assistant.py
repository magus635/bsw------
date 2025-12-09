"""
AI Assistant Widget for DaVinci Configurator
Provides a chat interface for the user to interact with the AI assistant.
"""
from PySide6.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QTextEdit, 
    QLineEdit, QPushButton, QLabel, QFrame, QScrollArea
)
from PySide6.QtCore import Qt, Signal, Slot
from PySide6.QtGui import QColor, QTextCharFormat, QFont, QTextCursor

try:
    import markdown
    HAS_MARKDOWN = True
except ImportError:
    HAS_MARKDOWN = False

class AIAssistantWidget(QWidget):
    """
    Widget providing the chat interface for AI assistance.
    """
    
    # Signal emitted when user sends a message
    # args: message_text
    message_sent = Signal(str)
    settings_clicked = Signal()
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self._setup_ui()
        self._welcome_message()
        
    def _setup_ui(self):
        """Setup the UI layout"""
        layout = QVBoxLayout(self)
        layout.setContentsMargins(10, 10, 10, 10)
        layout.setSpacing(10)
        
        # Header / Status
        header_layout = QHBoxLayout()
        self.status_label = QLabel("🤖 AI Assistant Ready")
        self.status_label.setStyleSheet("color: #666; font-weight: bold;")
        header_layout.addWidget(self.status_label)
        
        header_layout.addStretch()
        
        self.settings_btn = QPushButton("⚙️ Settings")
        self.settings_btn.setFlat(True)
        self.settings_btn.setCursor(Qt.PointingHandCursor)
        self.settings_btn.clicked.connect(self.settings_clicked)
        header_layout.addWidget(self.settings_btn)
        
        layout.addLayout(header_layout)
        
        # Chat History (Read-only)
        self.chat_history = QTextEdit()
        self.chat_history.setReadOnly(True)
        self.chat_history.setStyleSheet("""
            QTextEdit {
                background-color: #f5f5f5;
                border: 1px solid #ddd;
                border-radius: 4px;
                padding: 5px;
            }
        """)
        layout.addWidget(self.chat_history)
        
        # Input Area
        input_layout = QHBoxLayout()
        
        self.input_field = QLineEdit()
        self.input_field.setPlaceholderText("Ask me to create containers or explain config...")
        self.input_field.returnPressed.connect(self._handle_send)
        input_layout.addWidget(self.input_field)
        
        self.send_btn = QPushButton("Send")
        self.send_btn.clicked.connect(self._handle_send)
        # Style the send button
        self.send_btn.setStyleSheet("""
            QPushButton {
                background-color: #0078D7;
                color: white;
                border: none;
                border-radius: 4px;
                padding: 6px 12px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #0063B1;
            }
            QPushButton:pressed {
                background-color: #005A9E;
            }
        """)
        input_layout.addWidget(self.send_btn)
        
        layout.addLayout(input_layout)
        
    def _handle_send(self):
        """Handle send button click or return press"""
        text = self.input_field.text().strip()
        if not text:
            return
            
        # Add user message to chat
        self.append_message("You", text, is_user=True)
        
        # Clear input
        self.input_field.clear()
        
        # Emit signal for processing
        self.message_sent.emit(text)
        
        # Set status to processing
        self.set_status("Thinking...", busy=True)
        
    def set_status(self, text: str, busy: bool = False):
        """Update status label"""
        icon = "⏳" if busy else "🤖"
        self.status_label.setText(f"{icon} {text}")
        
    def append_message(self, sender: str, text: str, is_user: bool = False):
        """Append a message to the chat history"""
        # Format styles
        color = "#0078D7" if is_user else "#2E7D32"  # Blue for user, Green for AI
        align = "right" if is_user else "left"
        
        # Create HTML formatted message
        # We use a simple table or div structure to align
        
        timestamp = "" # Optional: Add timestamp
        
        html = f"""
        <div style="margin-bottom: 10px;">
            <div style="color: {color}; font-weight: bold; text-align: {align};">
                {sender}:
            </div>
            <div style="
                background-color: {'#E3F2FD' if is_user else '#FFFFFF'}; 
                padding: 10px; 
                border-radius: 8px; 
                border: 1px solid #E0E0E0;
                text-align: left;
            ">
        """
        
        if HAS_MARKDOWN:
            # Convert Markdown to HTML
            # extensions=['fenced_code', 'tables'] could be useful
            md_html = markdown.markdown(text, extensions=['fenced_code', 'tables']) if hasattr(markdown, 'markdown') else text
            html += md_html
        else:
            # Fallback
            html += text.replace('\n', '<br>')
            
        html += """
            </div>
        </div>
        """
        
        # Append to text edit
        cursor = self.chat_history.textCursor()
        cursor.movePosition(QTextCursor.MoveOperation.End)
        self.chat_history.setTextCursor(cursor)
        self.chat_history.insertHtml(html)
        
        # Scroll to bottom
        self.chat_history.verticalScrollBar().setValue(
            self.chat_history.verticalScrollBar().maximum()
        )

    def _welcome_message(self):
        """Show initial welcome message"""
        welcome_text = (
            "Hello! I am your DaVinci AI Assistant.<br><br>"
            "I can help you with:<br>"
            "• <b>Configuration</b>: 'Create 5 AdcHwUnits'<br>"
            "• <b>Validation</b>: 'Fix all errors'<br>"
            "• <b>Explanation</b>: 'What is this parameter?'<br><br>"
            "<i>Note: I am currently in prototype mode.</i>"
        )
        self.append_message("AI", welcome_text, is_user=False)
