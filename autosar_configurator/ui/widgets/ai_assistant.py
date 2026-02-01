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
    api_key_changed = Signal(str) # Emitted when API key is updated elsewhere
    
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.knowledge_base = None  # Set by main window after AI processor init
        
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
        self.settings_btn.clicked.connect(self._open_settings)
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
        
    def _open_settings(self):
        """Open the Knowledge Base settings dialog"""
        # Emit signal to tell main window to ensure AI processor is initialized
        # This will set self.knowledge_base before we open the dialog
        self.settings_clicked.emit()
        
        dialog = KnowledgeBaseDialog(self, knowledge_base=self.knowledge_base)
        if dialog.exec():
            # Check if API key was changed in the dialog
            if dialog.api_key_changed:
                new_key = dialog.api_key_input.text().strip()
                self.api_key_changed.emit(new_key)
                self.append_message("System", "✅ API Key updated from Settings.")
        
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
        bg_color = "#E3F2FD" if is_user else "#F1F8E9"
        
        # Convert Markdown to HTML if available
        if HAS_MARKDOWN:
            formatted_text = markdown.markdown(text, extensions=['fenced_code', 'tables', 'nl2br']) if hasattr(markdown, 'markdown') else text.replace('\n', '<br>')
        else:
            formatted_text = text.replace('\n', '<br>')
        
       # Create message bubble 
        # Use CSS margins for spacing to achieve "one line" interval
        html = f"""
        <div style="display: block; margin-top: 8px; margin-bottom: 8px;">
            <div style="color: {color}; font-weight: bold;">{sender}</div>
            <div style="background-color: {bg_color}; padding: 8px; border-left: 4px solid {color}; margin-top: 4px;">
                {formatted_text}
            </div>
        </div>
        <br>
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



from PySide6.QtWidgets import (
    QDialog, QFileDialog, QListWidget, QPushButton, 
    QVBoxLayout, QHBoxLayout, QLabel, QGroupBox, 
    QLineEdit, QFormLayout, QCheckBox
)
from PySide6.QtCore import QSettings, Signal

class KnowledgeBaseDialog(QDialog):
    """
    Dialog to manage Knowledge Base files and API Configuration.
    """
    def __init__(self, parent=None, knowledge_base=None):
        super().__init__(parent)
        self.setWindowTitle("AI Assistant Settings")
        self.setMinimumWidth(500)
        self.setMinimumHeight(400)
        
        self.settings = QSettings("AUTOSAR", "DaVinciConfigurator")
        self.api_key_changed = False # Track if changed
        self.knowledge_base = knowledge_base  # Reference to KnowledgeBase for loading files
        
        layout = QVBoxLayout(self)
        
        # --- API Key Section ---
        config_group = QGroupBox("Configuration")
        config_layout = QFormLayout()
        
        self.api_key_input = QLineEdit()
        self.api_key_input.setEchoMode(QLineEdit.Password)
        self.api_key_input.setPlaceholderText("Enter Google Gemini API Key")
        
        # Load existing key
        current_key = self.settings.value("gemini_api_key", "")
        self.api_key_input.setText(current_key)
        
        config_layout.addRow("API Key:", self.api_key_input)
        
        # AI Config Suggestions Toggle (default OFF)
        self.ai_suggestions_checkbox = QCheckBox("启用参数配置建议 (点击参数名获取 AI 建议)")
        self.ai_suggestions_checkbox.setToolTip(
            "启用后，点击参数表中的参数名称或引用名称时，将自动请求 AI 提供配置建议。\n"
            "该功能需要有效的 API Key，且会产生 API 调用费用。\n"
            "默认关闭，因为大多数用户可能不需要此功能。"
        )
        # Load saved setting (default to False)
        ai_suggestions_enabled = self.settings.value("ai_suggestions_enabled", False, type=bool)
        self.ai_suggestions_checkbox.setChecked(ai_suggestions_enabled)
        config_layout.addRow("", self.ai_suggestions_checkbox)
        
        config_group.setLayout(config_layout)
        layout.addWidget(config_group)
        
        # --- Knowledge Base Section ---
        kb_group = QGroupBox("Knowledge Base Documents")
        kb_layout = QVBoxLayout()
        
        self.file_list = QListWidget()
        # Show documents currently loaded in knowledge base
        if self.knowledge_base and hasattr(self.knowledge_base, 'loaded_files'):
            import os
            if self.knowledge_base.loaded_files:
                for filepath in self.knowledge_base.loaded_files:
                    filename = os.path.basename(filepath)
                    self.file_list.addItem(f"✅ {filename}")
            else:
                self.file_list.addItem("(No documents loaded)")
        else:
            self.file_list.addItem("(Knowledge Base not ready)")
        kb_layout.addWidget(self.file_list)
        
        btn_layout = QHBoxLayout()
        self.add_btn = QPushButton("📄 Add Datasheet...")
        self.add_btn.clicked.connect(self._add_file)
        btn_layout.addWidget(self.add_btn)
        
        kb_layout.addLayout(btn_layout)
        
        # Status label for feedback
        self.status_label = QLabel("")
        self.status_label.setStyleSheet("color: #666;")
        kb_layout.addWidget(self.status_label)
        
        kb_group.setLayout(kb_layout)
        layout.addWidget(kb_group)
        
        # --- Buttons ---
        action_layout = QHBoxLayout()
        action_layout.addStretch()
        
        self.save_btn = QPushButton("Save & Close")
        self.save_btn.clicked.connect(self._save_and_close)
        self.save_btn.setDefault(True)
        action_layout.addWidget(self.save_btn)
        
        self.cancel_btn = QPushButton("Cancel")
        self.cancel_btn.clicked.connect(self.reject)
        action_layout.addWidget(self.cancel_btn)
        
        layout.addLayout(action_layout)
        
    def _save_and_close(self):
        """Save settings and close"""
        new_key = self.api_key_input.text().strip()
        old_key = self.settings.value("gemini_api_key", "")
        
        if new_key != old_key:
            self.settings.setValue("gemini_api_key", new_key)
            self.api_key_changed = True
        
        # Save AI suggestions toggle setting
        self.settings.setValue("ai_suggestions_enabled", self.ai_suggestions_checkbox.isChecked())
        
        # Save knowledge base to disk for persistence
        if self.knowledge_base and self.knowledge_base.documents:
            self.knowledge_base.save_to_disk()
            
        self.accept()

    def _add_file(self):
        """Add a file to the knowledge base"""
        file_path, _ = QFileDialog.getOpenFileName(
            self, 
            "Select Datasheet/Image", 
            "", 
            "Documents (*.txt *.md *.pdf *.png *.jpg *.jpeg);;All Files (*)"
        )
        if file_path:
            # Try to load into knowledge base
            if self.knowledge_base:
                try:
                    self.status_label.setText(f"Loading: {file_path}...")
                    self.status_label.repaint()  # Force UI update
                    
                    self.knowledge_base.load_document(file_path)
                    
                    # Update list with success
                    import os
                    filename = os.path.basename(file_path)
                    self.file_list.addItem(f"✅ {filename}")
                    self.status_label.setText(f"✅ Loaded: {filename}")
                    
                    # Auto-save to disk for persistence
                    self.knowledge_base.save_to_disk()
                    
                except Exception as e:
                    self.status_label.setText(f"❌ Error: {str(e)}")
                    self.file_list.addItem(f"❌ {file_path} (Error)")
            else:
                # No knowledge base available - just show in list
                self.file_list.addItem(f"{file_path} (⚠️ KB not available)")
                self.status_label.setText("⚠️ Knowledge Base not initialized")
