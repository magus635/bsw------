"""
DaVinci-style Main Window for ECUC Configuration
Dual-mode: loads DEF files and allows creating VALUE instances
"""
from PySide6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QSplitter, QMenuBar, QMenu, QToolBar, QStatusBar,
    QFileDialog, QMessageBox, QStyle, QLabel, QInputDialog, QLineEdit
)
from PySide6.QtCore import Qt, Signal, QSettings, QRunnable, QThreadPool, QObject, Slot
from PySide6.QtGui import QAction, QKeySequence, QUndoStack
from PySide6.QtWidgets import QDockWidget
from pathlib import Path
from typing import Optional

from .commands import (
    SetParameterCommand, SetReferenceCommand,
    CreateContainerCommand, DeleteContainerCommand,
    MoveContainerCommand, PasteContainerCommand
)

from ..core.parser.ecuc_def_parser import EcucDefParser
from ..core.config_manager import ConfigurationManager
from ..core.workspace_manager import WorkspaceManager, WorkspaceProject
from ..core.model.definition_model import EcucModuleDef, EcucContainerDef
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from .widgets.davinci_tree_view import DaVinciTreeView
from .widgets.davinci_config_panel import DaVinciConfigPanel
from .widgets.smart_search import SmartSearchWidget
from .widgets.dependency_graph import DependencyGraphWidget
from .widgets.ai_assistant import AIAssistantWidget
from ..core.ai.nlp_processor import NaturalLanguageProcessor
from ..generator.generator import CodeGenerator


class AIWorkerSignals(QObject):
    """Signals for AI worker thread"""
    result = Signal(str)  # Emits the response text
    error = Signal(str)   # Emits error message


class AIWorker(QRunnable):
    """Worker thread for non-blocking AI API calls"""
    
    def __init__(self, processor, text: str, context_instance):
        super().__init__()
        self.signals = AIWorkerSignals()
        self.processor = processor
        self.text = text
        self.context_instance = context_instance
    
    @Slot()
    def run(self):
        """Execute the AI processing in background thread"""
        try:
            response = self.processor.process_message(self.text, self.context_instance)
            self.signals.result.emit(response)
        except Exception as e:
            self.signals.error.emit(str(e))


class DaVinciMainWindow(QMainWindow):
    """DaVinci Configurator-style main window"""
    
    def __init__(self):
        super().__init__()
        
        # Thread pool for async AI calls
        self.thread_pool = QThreadPool()
        
        # Core state
        self.module_def: Optional[EcucModuleDef] = None
        self.config_manager: Optional[ConfigurationManager] = None
        self.current_def_file: Optional[Path] = None
        self.current_value_file: Optional[Path] = None
        
        # Workspace state
        self.workspace_manager = WorkspaceManager()
        self.current_project: Optional[WorkspaceProject] = None
        self.current_project_file: Optional[Path] = None
        
        # Parsers
        self.def_parser = EcucDefParser()
        
        # Settings
        self.settings = QSettings("AUTOSAR", "DaVinciConfigurator")
        
        # Unsaved changes tracking
        self._has_unsaved_changes = False
        
        # Undo Stack
        self.undo_stack = QUndoStack(self)
        self.undo_stack.cleanChanged.connect(self._on_undo_clean_changed)

        # Internal Clipboard
        self.clipboard_instance: Optional[EcucContainerValue] = None
        
        self._setup_ui()
        self._create_actions()
        self._create_menus()
        self._create_toolbars()
        self._create_statusbar()
        
        self.setWindowTitle("AUTOSAR DaVinci Configurator")
        self.resize(1400, 900)
        
        # Load last opened DEF file
        self._load_last_session()
    
    def _setup_ui(self):
        """Setup the UI layout"""
        # Central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Main layout
        layout = QVBoxLayout(central_widget)
        layout.setContentsMargins(0, 0, 0, 0)
        
        # Add search widget at top
        self.search_widget = SmartSearchWidget()
        self.search_widget.result_selected.connect(self._on_search_result_selected)
        self.search_widget.setMaximumHeight(200)
        self.search_widget.hide()  # Hidden by default
        layout.addWidget(self.search_widget)
        
        # Splitter for tree view and config panel
        splitter = QSplitter(Qt.Horizontal)
        
        # Left: Tree view
        self.tree_view = DaVinciTreeView()
        self.tree_view.instance_selected.connect(self._on_instance_selected)
        self.tree_view.def_selected.connect(self._on_def_selected)
        self.tree_view.module_selected.connect(self._on_module_selected)
        self.tree_view.create_instance_requested.connect(self.handle_create_container)
        self.tree_view.delete_instance_requested.connect(self.handle_delete_container)
        self.tree_view.move_instance_requested.connect(self.handle_move_container)
        splitter.addWidget(self.tree_view)
        
        # Right: Config panel
        self.config_panel = DaVinciConfigPanel()
        self.config_panel.parameter_changed.connect(self._on_parameter_changed)
        self.config_panel.ai_help_requested.connect(self._on_ai_help_requested)
        splitter.addWidget(self.config_panel)
        
        # Set splitter proportions
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 2)
        
        layout.addWidget(splitter)
        
        # Dependency graph widget (in separate window)
        self.dep_graph_widget = None
        self.dep_graph_dialog = None
        
        # AI Assistant (Dock Widget)
        self.ai_assistant_widget = None
        self.ai_assistant_dock = None
        
        # Initialize AI Assistant
        self._setup_ai_assistant()
    
    def _setup_ai_assistant(self):
        """Setup AI Assistant dock widget"""
        self.ai_assistant_dock = QDockWidget("AI Assistant", self)
        self.ai_assistant_dock.setObjectName("AIAssistantDock")  # Required for saveState()
        self.ai_assistant_dock.setAllowedAreas(Qt.RightDockWidgetArea | Qt.LeftDockWidgetArea)
        
        self.ai_assistant_widget = AIAssistantWidget()
        self.ai_assistant_dock.setWidget(self.ai_assistant_widget)
        
        self.addDockWidget(Qt.RightDockWidgetArea, self.ai_assistant_dock)
        
        # Connect signals
        self.ai_assistant_widget.message_sent.connect(self._handle_ai_message)
        self.ai_assistant_widget.settings_clicked.connect(self._configure_ai_settings)
        
        # Hide by default
        self.ai_assistant_dock.hide()
        
        # Initialize Backend (Lazy load or init here if fast)
        self.ai_processor = None  # Will init when config_manager is available

    def _configure_ai_settings(self):
        """Ensure AI processor is initialized when Settings button is clicked.
        This is called BEFORE the KnowledgeBaseDialog opens.
        """
        api_key = self.settings.value("gemini_api_key")
        
        # Initialize AI processor if not already done
        if not self.ai_processor:
            self.ai_processor = NaturalLanguageProcessor(
                api_key=api_key,
                config_manager=self.config_manager,
                undo_stack=self.undo_stack,
                action_handler=self._handle_ai_action
            )
        
        # Always ensure KB reference is set on the widget
        if self.ai_processor and hasattr(self.ai_processor, 'knowledge_base'):
            self.ai_assistant_widget.knowledge_base = self.ai_processor.knowledge_base

    def _handle_ai_message(self, text: str):
        """Handle message from AI Assistant Widget"""
        # Init processor if needed (Always init to allow general chat)
        if not self.ai_processor:
             # Can be initialized with None config_manager
             pass
            
        # Check/Get API Key (Optional now)
        api_key = self.settings.value("gemini_api_key")
        # if not api_key: ... (Removed blocking check)

        # Init processor if needed
        if not self.ai_processor:
            self.ai_processor = NaturalLanguageProcessor(
                api_key=api_key,
                config_manager=self.config_manager,
                undo_stack=self.undo_stack,
                action_handler=self._handle_ai_action
            )
            # Set knowledge base reference on the widget for Settings dialog
            self.ai_assistant_widget.knowledge_base = self.ai_processor.knowledge_base
        else:
            # Update config manager reference if it changed
            self.ai_processor.config_manager = self.config_manager
            # Update key if it changed AND new key is valid
            # If settings key is empty, keep using current key (e.g. from env)
            if api_key and self.ai_processor.gemini_client.api_key != api_key:
                 self.ai_processor.gemini_client.configure(api_key)
            # Update handler
            self.ai_processor.action_handler = self._handle_ai_action

        # Process Message Asynchronously
        print(f"DEBUG: Processing AI message (async): '{text}'")
        self.ai_assistant_widget.set_status("Thinking...", busy=True)
        
        # Get context from selection (Safely)
        context_instance = None
        try:
            if hasattr(self.tree_view, 'get_selected_instance'):
                context_instance = self.tree_view.get_selected_instance()
            else:
                print("DEBUG: tree_view missing get_selected_instance")
        except Exception as e:
            print(f"DEBUG: Context error: {e}")
        
        # Create worker and connect signals
        worker = AIWorker(self.ai_processor, text, context_instance)
        worker.signals.result.connect(self._on_ai_response)
        worker.signals.error.connect(self._on_ai_error)
        
        # Submit to thread pool (non-blocking)
        self.thread_pool.start(worker)
    
    def _on_ai_response(self, response: str):
        """Handle AI response from worker thread"""
        print(f"DEBUG: AI Response received: '{response[:50]}...'")
        self.ai_assistant_widget.append_message("AI", response)
        self.ai_assistant_widget.set_status("Ready")
    
    def _on_ai_error(self, error_msg: str):
        """Handle AI error from worker thread"""
        print(f"DEBUG: AI Error: {error_msg}")
        self.ai_assistant_widget.append_message("System", f"❌ Error: {error_msg}")
        self.ai_assistant_widget.set_status("Error")

    def _handle_ai_action(self, action_name: str):
        """Execute action requested by AI"""
        if action_name == "validate":
            self.validate_configuration()
        elif action_name == "save":
            if self.current_project:
                self.save_project()
            else:
                self.save_value_file()
        elif action_name == "generate":
            self.generate_code()

    def _create_actions(self):
        """Create actions"""
        # Project actions
        self.new_project_action = QAction("New Project...", self)
        self.new_project_action.setShortcut(QKeySequence("Ctrl+Shift+N"))
        self.new_project_action.setStatusTip("Create a new AUTOSAR project")
        self.new_project_action.triggered.connect(self.new_project)
        
        self.open_project_action = QAction("Open Project...", self)
        self.open_project_action.setShortcut(QKeySequence("Ctrl+Shift+O"))
        self.open_project_action.setStatusTip("Open an existing project (.dpa file)")
        self.open_project_action.triggered.connect(self.open_project)
        
        self.save_project_action = QAction("Save Project", self)
        self.save_project_action.setShortcut(QKeySequence("Ctrl+Shift+S"))
        self.save_project_action.setEnabled(False)
        self.save_project_action.triggered.connect(self.save_project)
        
        self.project_properties_action = QAction("Project Properties...", self)
        self.project_properties_action.setEnabled(False)
        self.project_properties_action.triggered.connect(self.show_project_properties)
        
        self.add_module_action = QAction("Add Module to Project...", self)
        self.add_module_action.setEnabled(False)
        self.add_module_action.triggered.connect(self.add_module_to_project)
        
        # File actions
        self.open_def_action = QAction("Open DEF File...", self)
        self.open_def_action.setShortcut(QKeySequence.Open)
        self.open_def_action.setStatusTip("Open a module definition file (ARXML)")
        self.open_def_action.triggered.connect(self.open_def_file)
        
        self.new_config_action = QAction("New Configuration", self)
        self.new_config_action.setShortcut(QKeySequence.New)
        self.new_config_action.setEnabled(False)  # Enable after DEF loaded
        self.new_config_action.triggered.connect(self.new_configuration)
        
        self.open_value_action = QAction("Open VALUE File...", self)
        self.open_value_action.setEnabled(False)
        self.open_value_action.triggered.connect(self.open_value_file)
        
        self.save_value_action = QAction("Save Configuration", self)
        self.save_value_action.setShortcut(QKeySequence.Save)
        self.save_value_action.setStatusTip("Save current configuration to file")
        self.save_value_action.setEnabled(False)
        self.save_value_action.triggered.connect(self.save_value_file)
        
        self.save_value_as_action = QAction("Save Configuration As...", self)
        self.save_value_as_action.setEnabled(False)
        self.save_value_as_action.triggered.connect(self.save_value_file_as)
        
        self.exit_action = QAction("Exit", self)
        self.exit_action.setShortcut(QKeySequence.Quit)
        self.exit_action.setStatusTip("Exit the application")
        self.exit_action.triggered.connect(self.close)
        
        # Recent files will be added dynamically
        self.recent_file_actions = []
        self.max_recent_files = 10
        
        # Edit actions  
        self.validate_action = QAction("Validate Configuration", self)
        self.validate_action.setShortcut(QKeySequence("Ctrl+Shift+V"))
        self.validate_action.setEnabled(False)
        self.validate_action.setEnabled(False)
        self.validate_action.triggered.connect(self.validate_configuration)
        
        self.load_rules_action = QAction("Load Custom Rules...", self)
        self.load_rules_action.setEnabled(False)
        self.load_rules_action.triggered.connect(self.load_custom_rules)
        
        self.load_rules_action.triggered.connect(self.load_custom_rules)

        # Copy/Paste Actions
        self.copy_action = QAction("Copy", self)
        self.copy_action.setShortcut(QKeySequence.Copy)
        self.copy_action.setStatusTip("Copy selected container")
        self.copy_action.triggered.connect(self.copy_container)
        
        self.paste_action = QAction("Paste", self)
        self.paste_action.setShortcut(QKeySequence.Paste)
        self.paste_action.setStatusTip("Paste container from clipboard")
        self.paste_action.triggered.connect(self.paste_container)
        
        # Undo/Redo actions
        self.undo_action = self.undo_stack.createUndoAction(self, "Undo")
        self.undo_action.setShortcut(QKeySequence.Undo)
        
        self.redo_action = self.undo_stack.createRedoAction(self, "Redo")
        self.redo_action.setShortcut(QKeySequence.Redo)
        
        # Generate actions
        self.generate_action = QAction("Generate Code", self)
        self.generate_action.setShortcut(QKeySequence("Ctrl+G"))
        self.generate_action.setEnabled(False)
        self.generate_action.triggered.connect(self.generate_code)
        
        # Wizard actions
        self.quick_config_action = QAction("Quick Configuration...", self)
        self.quick_config_action.setShortcut(QKeySequence("Ctrl+Q"))
        self.quick_config_action.setEnabled(False)
        self.quick_config_action.triggered.connect(self.launch_quick_config_wizard)
        
        # View actions
        self.toggle_search_action = QAction("Search...", self)
        self.toggle_search_action.setShortcut(QKeySequence.Find)  # Ctrl+F
        self.toggle_search_action.setStatusTip("Show/hide search panel (Ctrl+F)")
        self.toggle_search_action.setCheckable(True)
        self.toggle_search_action.triggered.connect(self.toggle_search)
        
        self.show_dep_graph_action = QAction("Dependency Graph", self)
        self.show_dep_graph_action.setShortcut(QKeySequence("Ctrl+D"))
        self.show_dep_graph_action.setEnabled(False)
        self.show_dep_graph_action.setEnabled(False)
        self.show_dep_graph_action.triggered.connect(self.show_dependency_graph)

        self.toggle_ai_action = self.ai_assistant_dock.toggleViewAction()
        self.toggle_ai_action.setText("AI Assistant")
        self.toggle_ai_action.setShortcut(QKeySequence("Ctrl+Shift+A"))
        self.toggle_ai_action.setStatusTip("Show/Hide AI Assistant")
    
    def _create_menus(self):
        """Create menus"""
        menubar = self.menuBar()
        
        # File menu
        file_menu = menubar.addMenu("File")
        file_menu.addAction(self.new_project_action)
        file_menu.addAction(self.open_project_action)
        file_menu.addAction(self.save_project_action)
        file_menu.addAction(self.project_properties_action)
        file_menu.addSeparator()
        file_menu.addAction(self.add_module_action)
        file_menu.addSeparator()
        file_menu.addAction(self.open_def_action)
        file_menu.addSeparator()
        # Recent Files submenu
        self.recent_files_menu = file_menu.addMenu("Recent Files")
        self._update_recent_files_menu()
        file_menu.addSeparator()
        file_menu.addAction(self.new_config_action)
        file_menu.addAction(self.open_value_action)
        file_menu.addAction(self.save_value_action)
        file_menu.addAction(self.save_value_as_action)
        file_menu.addSeparator()
        file_menu.addAction(self.exit_action)
        
        # Edit menu
        edit_menu = menubar.addMenu("Edit")
        edit_menu.addAction(self.undo_action)
        edit_menu.addAction(self.redo_action)
        edit_menu.addSeparator()
        edit_menu.addAction(self.copy_action)
        edit_menu.addAction(self.paste_action)
        edit_menu.addSeparator()
        edit_menu.addAction(self.validate_action)
        edit_menu.addAction(self.load_rules_action)
        
        # View menu
        view_menu = menubar.addMenu("View")
        view_menu.addAction(self.toggle_search_action)
        view_menu.addAction(self.show_dep_graph_action)
        view_menu.addSeparator()
        view_menu.addAction(self.toggle_ai_action)
        
        # Generate menu
        gen_menu = menubar.addMenu("Generate")
        gen_menu.addAction(self.generate_action)
        
        # Analysis menu (new)
        analysis_menu = menubar.addMenu("Analysis")
        self.analyze_dependencies_action = QAction("🔍 分析跨模块依赖...", self)
        self.analyze_dependencies_action.triggered.connect(self._analyze_cross_module_dependencies)
        analysis_menu.addAction(self.analyze_dependencies_action)
        
        self.validate_dependencies_action = QAction("✅ 验证跨模块依赖...", self)
        self.validate_dependencies_action.triggered.connect(self._validate_cross_module_dependencies)
        analysis_menu.addAction(self.validate_dependencies_action)
        
        analysis_menu.addSeparator()
        analysis_menu.addAction(self.show_dep_graph_action)
        
        # Wizards menu
        wizards_menu = menubar.addMenu("Wizards")
        wizards_menu.addAction(self.quick_config_action)
        
        # Help menu
        help_menu = menubar.addMenu("Help")
        about_action = QAction("关于 DaVinci Configurator", self)
        about_action.triggered.connect(self._show_about_dialog)
        help_menu.addAction(about_action)
    
    def _create_toolbars(self):
        """Create toolbars"""
        toolbar = self.addToolBar("Main Toolbar")
        toolbar.setObjectName("MainToolbar")  # Fix QMainWindow::saveState() warning
        toolbar.addAction(self.open_def_action)
        toolbar.addAction(self.new_config_action)
        toolbar.addAction(self.save_value_action)
        toolbar.addSeparator()
        toolbar.addAction(self.undo_action)
        toolbar.addAction(self.redo_action)
        toolbar.addSeparator()
        toolbar.addAction(self.copy_action)
        toolbar.addAction(self.paste_action)
        toolbar.addSeparator()
        toolbar.addAction(self.validate_action)
        toolbar.addSeparator()
        toolbar.addAction(self.generate_action)
    
    def _create_statusbar(self):
        """Create status bar with permanent indicators"""
        self.statusbar = QStatusBar()
        self.setStatusBar(self.statusbar)
        
        # Mode indicator (left side - permanent)
        self.mode_label = QLabel("Mode: Single Module")
        self.mode_label.setStyleSheet("QLabel { padding: 2px 10px; }")
        self.statusbar.addPermanentWidget(self.mode_label)
        
        # Validation status (right side - permanent)
        self.validation_status_label = QLabel("Not validated")
        self.validation_status_label.setStyleSheet("QLabel { padding: 2px 10px; }")
        self.statusbar.addPermanentWidget(self.validation_status_label)
        
        # Temporary message area (left side)
        self.def_file_label = QLabel("No DEF file loaded")
        self.value_file_label = QLabel("No configuration")
        self.validation_label = QLabel("")
        
        self.statusbar.addWidget(self.def_file_label)
        self.statusbar.addWidget(QLabel("|"))
        self.statusbar.addWidget(self.value_file_label)
        self.statusbar.addPermanentWidget(self.validation_label)
    
    # Project operations
    
    def new_project(self):
        """Create a new project"""
        from PySide6.QtWidgets import QInputDialog
        
        name, ok = QInputDialog.getText(self, "New Project", "Project name:")
        if not ok or not name:
            return
            
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save Project As",
            str(Path.home() / f"{name}.dpa"),
            "DaVinci Project (*.dpa);;All Files (*)"
        )
        
        if not file_path:
            return
            
        self.current_project = self.workspace_manager.create_project(name, Path(file_path))
        self.current_project_file = Path(file_path)
        self.tree_view.set_project(self.current_project)
        
        self.save_project_action.setEnabled(True)
        self.add_module_action.setEnabled(True)
        self.statusbar.showMessage(f"Created project: {name}", 3000)
        
    def open_project(self):
        """Open an existing project"""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open Project",
            str(Path.home()),
            "DaVinci Project (*.dpa);;All Files (*)"
        )
        
        if not file_path:
            return
            
        try:
            self.statusbar.showMessage("Loading project...")
            self.current_project, failed_modules = self.workspace_manager.load_project(Path(file_path))
            self.current_project_file = Path(file_path)
            self.tree_view.set_project(self.current_project)
            
            # Enable project actions
            self.save_project_action.setEnabled(True)
            self.project_properties_action.setEnabled(True)
            self.add_module_action.setEnabled(True)
            
            status_msg = f"Loaded project: {self.current_project.name}"
            
            # Show warning if some modules failed to load
            if failed_modules:
                error_details = "\n".join([f"• {name}: {error}" for name, error in failed_modules])
                QMessageBox.warning(
                    self,
                    "Project Loaded with Errors",
                    f"Project loaded, but {len(failed_modules)} module(s) failed:\n\n{error_details}\n\n"
                    f"Successfully loaded: {len(self.current_project.module_managers)} module(s)"
                )
                status_msg += f" ({len(failed_modules)} errors)"
            
            self.statusbar.showMessage(status_msg, 5000)
            
            # Auto-select first module
            self.tree_view.select_first_module()
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to load project:\n{str(e)}")
            
    def save_project(self):
        """Save current project and all modified modules"""
        if not self.current_project:
            return
        
        try:
            saved_count = 0
            failed_modules = []
            
            # Save each modified module configuration
            for module_name, manager in self.current_project.module_managers.items():
                if manager.configuration.is_modified:
                    try:
                        # Use same naming convention as WorkspaceManager.save_project()
                        config_file = self.current_project.path.parent / f"{module_name}_Config.arxml"
                        
                        # Save the module configuration file
                        manager.save_configuration(config_file)
                        # mark_saved() is called inside save_configuration
                        saved_count += 1
                    except Exception as e:
                        failed_modules.append((module_name, str(e)))
            
            # Save project metadata file (.dpa)
            self.workspace_manager.save_project()
            
            # Show result
            if failed_modules:
                error_details = "\n".join([f"  • {name}: {err}" for name, err in failed_modules])
                QMessageBox.warning(
                    self,
                    "Project Saved with Errors",
                    f"Saved {saved_count} module(s), but {len(failed_modules)} failed:\n\n{error_details}"
                )
            else:
                if saved_count > 0:
                    self.statusbar.showMessage(f"Project saved: {saved_count} module(s) updated", 3000)
                else:
                    self.statusbar.showMessage(f"Project saved (no changes)", 3000)
                    
        except Exception as e:
            QMessageBox.critical(self, "Save Error", f"Failed to save project:\n{str(e)}")
    
    def show_project_properties(self):
        """Show project properties dialog"""
        if not self.current_project:
            return
        
        from .dialogs.project_properties_dialog import ProjectPropertiesDialog
        
        dialog = ProjectPropertiesDialog(self.current_project, self)
        if dialog.exec():
            # Update project with new data
            data = dialog.get_data()
            self.current_project.name = data['name']
            self.current_project.version = data['version']
            self.current_project.author = data['author']
            self.current_project.description = data['description']
            
            # Update tree header
            self.tree_view.setHeaderLabel(f"Project: {self.current_project.name}")
            
            self.statusbar.showMessage("Project properties updated", 3000)
    
    def add_module_to_project(self):
        """Add a module to the current project"""
        if not self.current_project:
            return
            
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Select Module DEF File",
            str(Path.home()),
            "ARXML Files (*.arxml);;All Files (*)"
        )
        
        if not file_path:
            return
            
        try:
            module_def = self.def_parser.parse_module_def_file(Path(file_path))
            self.current_project.add_module(module_def, Path(file_path))
            self.tree_view.set_project(self.current_project)
            self.statusbar.showMessage(f"Added module: {module_def.short_name}", 3000)
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to add module:\n{str(e)}")
    
    # File operations
    
    def open_def_file(self):
        """Open ECUC-DEF ARXML file"""
        # Check if project is active
        if self.current_project:
            reply = QMessageBox.question(
                self,
                "Close Project?",
                "Opening a DEF file will close the current project.\n\n"
                "Do you want to:\n"
                "• Close project and open DEF file (single-module mode)\n"
                "• Cancel and use 'Add Module to Project' instead",
                QMessageBox.Ok | QMessageBox.Cancel,
                QMessageBox.Cancel
            )
            
            if reply == QMessageBox.Cancel:
                # Suggest using Add Module instead
                QMessageBox.information(
                    self,
                    "Tip",
                    "To add modules to your project, use:\n"
                    "File → Add Module to Project"
                )
                return
            
            # User chose to close project
            self.current_project = None
            self.current_project_file = None
            self.tree_view.clear()
            self.save_project_action.setEnabled(False)
            self.add_module_action.setEnabled(False)
        
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open DEF File",
            str(Path.home()),
            "ARXML Files (*.arxml);;All Files (*)"
        )
        
        if not file_path:
            return
        
        try:
            # Show loading cursor
            from PySide6.QtWidgets import QApplication
            from PySide6.QtCore import Qt as QtCore_Qt
            QApplication.setOverrideCursor(QtCore_Qt.WaitCursor)
            self.statusbar.showMessage("Loading DEF file...")
            
            # Parse DEF file
            self.module_def = self.def_parser.parse_module_def_file(Path(file_path))
            self.current_def_file = Path(file_path)
            
            # Create configuration manager
            self.config_manager = ConfigurationManager(self.module_def)
            
            # Update UI
            self.tree_view.set_module_def(self.module_def, self.config_manager)
            self.def_file_label.setText(f"DEF: {self.module_def.short_name}")
            
            # Enable actions
            self.new_config_action.setEnabled(True)
            self.open_value_action.setEnabled(True)
            
            self.statusbar.showMessage(f"Loaded DEF: {self.module_def.short_name}", 5000)
            
            # Save to settings
            self.settings.setValue("last_def_file", str(file_path))
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to load DEF file:\n{e}")
            self.statusbar.showMessage("Failed to load DEF file", 5000)
        finally:
            # Restore cursor
            QApplication.restoreOverrideCursor()
    
    def new_configuration(self):
        """Create new configuration based on loaded DEF"""
        if not self.config_manager:
            return
        
        # Create new configuration (reset)
        self.config_manager.configuration = EcucModuleConfiguration(
            short_name=self.module_def.short_name,
            definition_ref=self.module_def.definition_ref
        )
        
        # Refresh tree view
        self.tree_view.refresh()
        
        # Enable save actions
        self.save_value_action.setEnabled(True)
        self.save_value_as_action.setEnabled(True)
        self.save_value_action.setEnabled(True)
        self.save_value_as_action.setEnabled(True)
        self.validate_action.setEnabled(True)
        self.load_rules_action.setEnabled(True)
        self.generate_action.setEnabled(True)
        self.quick_config_action.setEnabled(True)
        self.show_dep_graph_action.setEnabled(True)
        
        self.value_file_label.setText("New configuration (unsaved)")
        self.current_value_file = None
        
        self.statusbar.showMessage("New configuration created", 3000)
    
    def open_value_file(self):
        """Open existing ECUC-VALUE file"""
        if not self.config_manager:
            QMessageBox.warning(self, "No DEF File", "Please open an ECUC-DEF file first.")
            return

        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open Configuration File",
            str(Path.home()),
            "ARXML Files (*.arxml);;All Files (*)"
        )
        
        if not file_path:
            return
            
        try:
            self.statusbar.showMessage("Loading configuration...")
            self.config_manager.load_configuration(Path(file_path))
            
            # Update UI
            self.current_value_file = Path(file_path)
            self.value_file_label.setText(f"Config: {self.current_value_file.name}")
            self.tree_view.refresh()
            self.config_panel.clear()
            
            # Enable actions
            self.save_value_action.setEnabled(True)
            self.save_value_action.setEnabled(True)
            self.validate_action.setEnabled(True)
            self.load_rules_action.setEnabled(True)
            self.generate_action.setEnabled(True)
            self.quick_config_action.setEnabled(True)
            self.show_dep_graph_action.setEnabled(True)
            
            self.statusbar.showMessage("Configuration loaded successfully", 3000)
            
        except Exception as e:
            QMessageBox.critical(self, "Load Error", f"Failed to load configuration:\n{str(e)}")
            self.statusbar.showMessage("Load failed", 3000)
    
    def save_value_file(self):
        """Save configuration to VALUE file"""
        if self.current_value_file:
            self._save_configuration(self.current_value_file)
        else:
            self.save_value_file_as()
    
    def save_value_file_as(self):
        """Save configuration as new VALUE file"""
        if not self.config_manager:
            return
            
        default_name = f"{self.config_manager.configuration.short_name}_Config.arxml"
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save Configuration As",
            str(Path.home() / default_name),
            "ARXML Files (*.arxml)"
        )
        
        if not file_path:
            return
        
        self._save_configuration(Path(file_path))
    
    def _save_configuration(self, file_path: Path):
        """Save configuration to file"""
        try:
            self.statusbar.showMessage("Saving configuration...")
            self.config_manager.save_configuration(file_path)
            
            self.current_value_file = Path(file_path)
            self.value_file_label.setText(f"Config: {Path(file_path).name}")
            self.statusbar.showMessage(f"Saved to {file_path}", 3000)
            
            # Clear unsaved changes flag
            self._has_unsaved_changes = False
            
            # Save to recent files
            self.settings.setValue("last_value_file", str(file_path))
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to save configuration:\n{str(e)}")
            self.statusbar.showMessage("Save failed", 3000)
            
    def _on_undo_clean_changed(self, clean):
        """Handle undo stack clean state change"""
        # If stack is clean, it means we are back to saved state (if we set clean on save)
        # But we handle is_modified manually for now, so maybe just update UI?
        pass

    def handle_parameter_change(self, instance: EcucContainerValue, param_name: str, value: any):
        """Handle parameter change request via command"""
        if not self.config_manager:
            return
            
        if param_name.startswith('ref:'):
            # Reference change
            ref_name = param_name[4:]
            command = SetReferenceCommand(self.config_manager, instance, ref_name, value)
        else:
            # Parameter change
            command = SetParameterCommand(self.config_manager, instance, param_name, value)
            
        self.undo_stack.push(command)
        self._has_unsaved_changes = True
        self.statusbar.showMessage(f"Set {param_name}", 2000)
        
        # Refresh UI if needed (e.g. if reference changed, might need to update other views)
        # For now, config panel updates itself, but tree view might need refresh if name changed (not supported yet)
        
    def handle_create_container(self, container_def: EcucContainerDef, parent_instance: Optional[EcucContainerValue], name: str):
        """Handle container creation request via command"""
        if not self.config_manager:
            return
            
        command = CreateContainerCommand(self.config_manager, container_def, parent_instance, name)
        self.undo_stack.push(command)
        
        self._has_unsaved_changes = True
        self.statusbar.showMessage(f"Created {name}", 2000)
        
        # Refresh tree view
        self.tree_view.refresh()
        
        # Select the new instance
        if command.created_instance:
            self.tree_view._select_instance(command.created_instance)
            
    def handle_delete_container(self, instance: EcucContainerValue, parent_instance: Optional[EcucContainerValue]):
        """Handle container deletion request via command"""
        if not self.config_manager:
            return
        
        # PRE-VALIDATE deletion to provide user feedback
        try:
            # Check if instance is referenced by others
            refs = self.config_manager._find_references_to(instance)
            if refs:
                ref_list = '\n'.join([f"  • {src.short_name}.{ref_name}" for src, ref_name in refs])
                QMessageBox.warning(
                    self,
                    "Cannot Delete Container",
                    f"Cannot delete '{instance.short_name}' because it is referenced by:\n\n"
                    f"{ref_list}\n\n"
                    f"Please remove these references first."
                )
                return
            
            # Check multiplicity constraint
            container_def = self.config_manager.get_container_def(instance.definition_ref)
            if container_def and parent_instance:
                current_count = self.config_manager._count_instances_in_parent(container_def, parent_instance)
                if current_count <= container_def.lower_multiplicity:
                    QMessageBox.warning(
                        self,
                        "Cannot Delete Container",
                        f"Cannot delete '{instance.short_name}'.\n\n"
                        f"The parent requires at least {container_def.lower_multiplicity} "
                        f"instance(s) of '{container_def.short_name}'."
                    )
                    return
        except Exception as e:
            # If validation check fails, show error and abort
            QMessageBox.critical(
                self,
                "Validation Error",
                f"Failed to validate deletion:\n{str(e)}\n\nDeletion cancelled."
            )
            return
            
        command = DeleteContainerCommand(self.config_manager, instance, parent_instance)
        self.undo_stack.push(command)
        
        self._has_unsaved_changes = True
        self.statusbar.showMessage(f"Deleted {instance.short_name}", 2000)
        
        # Refresh tree view
        self.tree_view.refresh()
        # Clear config panel if deleted instance was selected
        if self.config_panel.current_instance == instance:
            self.config_panel.clear()

    def handle_move_container(self, instance: EcucContainerValue, new_parent, new_index):
        """Handle container move request via command"""
        if not self.config_manager:
            return
            
        command = MoveContainerCommand(self.config_manager, instance, new_parent, new_index)
        self.undo_stack.push(command)
        
        self._has_unsaved_changes = True
        self.statusbar.showMessage(f"Moved {instance.short_name}", 2000)
        
        # Refresh tree view
        self.tree_view.refresh()
        
        # Reselect
        self.tree_view._select_instance(instance)
        
    def copy_container(self):
        """Copy selected container to internal clipboard"""
        current_instance = self.tree_view.get_selected_instance()
        if not current_instance:
            self.statusbar.showMessage("Select a container to copy", 2000)
            return
            
        self.clipboard_instance = current_instance
        self.statusbar.showMessage(f"Copied {current_instance.short_name} to clipboard", 2000)
        
    def paste_container(self):
        """Paste container from internal clipboard"""
        if not self.clipboard_instance:
            self.statusbar.showMessage("Clipboard is empty", 2000)
            return
            
        if not self.config_manager:
            return
            
        # Determine target parent
        target_parent = None
        selected_instance = self.tree_view.get_selected_instance()
        
        # Try to prepare paste
        # Logic: 
        # 1. If selected allows child of clipboard type -> Target = Selected
        # 2. Else -> Target = Selected.parent (sibling paste)
        
        clip_def_ref = self.clipboard_instance.definition_ref
        clip_def = self.config_manager.get_container_def(clip_def_ref)
        if not clip_def:
             self.statusbar.showMessage("Error: Definition of copied item not found", 3000)
             return

        if selected_instance:
             # Check if selected can hold this type
             selected_def = self.config_manager.get_container_def(selected_instance.definition_ref)
             if selected_def and clip_def.short_name in selected_def.sub_containers:
                 target_parent = selected_instance
             else:
                 target_parent = selected_instance.parent
        else:
             # If top level selected or nothing selected (paste to root if allowed)
             # Basic logic: Paste to root if clipboard item is allowed at root
             # Check if clipboard item is a root container
             is_root_allowed = clip_def.short_name in self.config_manager.module_def.containers
             
             if is_root_allowed:
                 target_parent = None
             else:
                 self.statusbar.showMessage("Cannot paste here: Select a valid parent container", 3000)
                 return
                 
        # Clone and Rename
        try:
            new_instance = self.clipboard_instance.clone()
            
            # Auto-rename to avoid collision
            base_name = new_instance.short_name
            # If it looks like "Name_Copy", strip suffix to avoid "Name_Copy_Copy" duplication if desired?
            # Or just append. Windows style: Copy -> Copy (2).
            # Let's keep it simple: Ensure unique name.
            if "_Copy" not in base_name:
                base_name += "_Copy"
            
            # Generate unique name
            counter = 0
            candidate_name = base_name
            while self.config_manager._instance_exists(candidate_name, clip_def, target_parent):
                counter += 1
                candidate_name = f"{base_name}{counter}"
            
            new_instance.short_name = candidate_name
             
            # Command
            command = PasteContainerCommand(self.config_manager, target_parent, new_instance)
            self.undo_stack.push(command)
            
            self._has_unsaved_changes = True
            self.statusbar.showMessage(f"Pasted {new_instance.short_name}", 2000)
            
            # Refresh and select
            self.tree_view.refresh()
            self.tree_view._select_instance(new_instance)
            
        except Exception as e:
            QMessageBox.critical(self, "Paste Error", f"Failed to paste:\n{str(e)}")
    
    def validate_configuration(self):
        """Validate current configuration with rich GUI dialog"""
        if not self.config_manager:
            return
        
        result = self.config_manager.validate_configuration()
        
        # Always show dialog if there are errors, or just success message if valid
        if not result.is_valid:
            from .dialogs.validation_results_dialog import ValidationResultsDialog
            
            dialog = ValidationResultsDialog(result.errors, self)
            dialog.navigate_requested.connect(self._navigate_to_path)
            dialog.exec()
            
            # Update status
            self.validation_status_label.setText(f"❌ {result.error_count} Error(s)")
            self.validation_status_label.setStyleSheet("QLabel { color: red; padding: 2px 10px; }")
        else:
            QMessageBox.information(
                self,
                "Validation Success",
                "✅ Configuration is valid!"
            )
            self.validation_status_label.setText("✅ Valid")
            self.validation_status_label.setStyleSheet("QLabel { color: green; padding: 2px 10px; }")

    def _navigate_to_path(self, path: str):
        """Navigate to a specific path in the configuration tree"""
        self.statusbar.showMessage(f"Navigating to: {path}", 3000)
        
        # Use robust path selection in tree view
        # This returns the parameter name if the path points to a parameter
        param_name = self.tree_view.select_item_by_path(path)
        
        # If a parameter was returned, highlight it in the config panel
        if param_name and self.config_panel:
            self.config_panel.highlight_parameter(param_name)
            
    def load_custom_rules(self):
        """Load custom validation rules from file"""
        if not self.config_manager:
            return
            
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Load Custom Rules",
            str(Path.home()),
            "JSON Files (*.json);;All Files (*)"
        )
        
        if not file_path:
            return
            
        try:
            self.config_manager.add_custom_rule_file(Path(file_path))
            self.statusbar.showMessage(f"Loaded custom rules from {Path(file_path).name}", 3000)
            
            # Trigger validation to see effect
            self.validate_configuration()
            
        except Exception as e:
            QMessageBox.critical(
                self,
            )

    def generate_code(self):
        """Generate C/C++ code for current module or entire project"""
        # Check if in Project mode
        if self.current_project:
            self._generate_project_code()
        elif self.config_manager:
            self._generate_single_module_code()
        else:
            QMessageBox.warning(self, "No Configuration", "Please load a configuration first.")
    
    def _generate_single_module_code(self):
        """Generate code for single module"""
        if not self.config_manager:
            return
            
        # Select output directory
        output_dir = QFileDialog.getExistingDirectory(
            self,
            "Select Output Directory",
            str(Path.home())
        )
        
        if not output_dir:
            return
        
        try:
            from ..generator.generator import CodeGenerator
            
            self.statusbar.showMessage("Generating code...")
            
            generator = CodeGenerator(
                self.module_def,
                self.config_manager.configuration
            )
            
            generator.generate_all(Path(output_dir))
            
            QMessageBox.information(
                self,
                "Code Generated",
                f"Code generated successfully in:\n{output_dir}"
            )
            self.statusbar.showMessage("Code generation completed", 3000)
            
        except Exception as e:
            QMessageBox.critical(
                self,
                "Code Generation Error",
                f"Failed to generate code:\n{str(e)}"
            )
            self.statusbar.showMessage("Code generation failed", 3000)
    
    def _generate_project_code(self):
        """Generate code for all modules in project"""
        if not self.current_project:
            return
        
        # Select output directory
        output_dir = QFileDialog.getExistingDirectory(
            self,
            "Select Project Output Directory",
            str(Path.home())
        )
        
        if not output_dir:
            return
        
        try:
            from ..generator.generator import CodeGenerator
            from PySide6.QtWidgets import QProgressDialog
            from PySide6.QtCore import Qt as QtCore_Qt
            
            output_path = Path(output_dir)
            modules = list(self.current_project.module_managers.items())
            
            # Create progress dialog
            progress = QProgressDialog(
                "Generating code for project modules...",
                "Cancel",
                0,
                len(modules),
                self
            )
            progress.setWindowModality(QtCore_Qt.WindowModal)
            progress.setMinimumDuration(0)
            
            generated_modules = []
            failed_modules = []
            
            for i, (module_name, manager) in enumerate(modules):
                if progress.wasCanceled():
                    break
                
                progress.setValue(i)
                progress.setLabelText(f"Generating {module_name}...")
                
                try:
                    # Create module-specific output directory
                    module_output = output_path / module_name
                    module_output.mkdir(exist_ok=True)
                    
                    # Generate code
                    generator = CodeGenerator(
                        manager.module_def,
                        manager.configuration
                    )
                    generator.generate_all(module_output)
                    
                    generated_modules.append(module_name)
                    
                except Exception as e:
                    failed_modules.append((module_name, str(e)))
            
            progress.setValue(len(modules))
            
            # Show summary
            summary = f"Code generation completed!\n\n"
            summary += f"✅ Generated: {len(generated_modules)} module(s)\n"
            if generated_modules:
                summary += "  - " + "\n  - ".join(generated_modules) + "\n\n"
            
            if failed_modules:
                summary += f"❌ Failed: {len(failed_modules)} module(s)\n"
                for mod, err in failed_modules:
                    summary += f"  - {mod}: {err}\n"
            
            summary += f"\nOutput: {output_dir}"
            
            if failed_modules:
                QMessageBox.warning(self, "Code Generation Completed with Errors", summary)
            else:
                QMessageBox.information(self, "Code Generation Successful", summary)
            
            self.statusbar.showMessage(
                f"Project code generated: {len(generated_modules)}/{len(modules)} modules",
                5000
            )
            
        except Exception as e:
            QMessageBox.critical(
                self,
                "Project Code Generation Error",
                f"Failed to generate project code:\n{str(e)}"
            )
            self.statusbar.showMessage("Project code generation failed", 3000)
    
    def launch_quick_config_wizard(self):
        """Launch the quick configuration wizard"""
        if not self.config_manager or not self.module_def:
            return
            
        from .wizards.quick_config_wizard import QuickConfigWizard
        
        wizard = QuickConfigWizard(self.module_def, self.config_manager, self)
        wizard.wizard_completed.connect(self._on_wizard_completed)
        wizard.exec()
    
    def _on_wizard_completed(self, data: dict):
        """Handle wizard completion"""
        # Refresh tree view to show new instance
        self.tree_view.refresh()
        
        # Select the newly created instance
        instance = data.get("instance")
        if instance:
            self.tree_view._select_instance(instance)
        
        self.statusbar.showMessage("Configuration created successfully", 3000)
    
    def toggle_search(self, checked: bool):
        """Toggle search widget visibility"""
        if checked:
            self.search_widget.show()
            self.search_widget.focus_search()
            
            # Build search index with current module and configuration
            if self.config_manager:
                self.search_widget.build_search_index(
                    self.module_def,
                    self.config_manager.configuration
                )
        else:
            self.search_widget.hide()
    
    def _on_search_result_selected(self, result_type: str, path: str):
        """Handle search result selection"""
        self.statusbar.showMessage(f"Navigating to: {path}", 3000)
        
        # Different handling based on result type
        if result_type in ['container_def', 'parameter_def']:
            # For definitions, show info dialog
            self._show_definition_info(result_type, path)
        elif result_type == 'container':
            # For container instances, select in tree
            self._navigate_to_container(path)
        elif result_type == 'parameter':
            # For parameter values, select container
            container_path = '/'.join(path.split('/')[:-1])
            self._navigate_to_container(container_path)
        elif result_type == 'reference':
            # For references, select container
            container_path = '/'.join(path.split('/')[:-1])
            self._navigate_to_container(container_path)
    
    def _show_definition_info(self, result_type: str, path: str):
        """Show definition information in a dialog"""
        from PySide6.QtWidgets import QMessageBox
        
        parts = path.split('/')
        if result_type == 'container_def':
            container_name = parts[0]
            if self.module_def and container_name in self.module_def.containers:
                container_def = self.module_def.containers[container_name]
                info = f"Container: {container_name}\n"
                info += f"Description: {container_def.description or 'N/A'}\n"
                info += f"Multiplicity: {container_def.lower_multiplicity}..{container_def.upper_multiplicity}\n"
                info += f"Parameters: {len(container_def.parameters)}\n"
                info += f"Sub-containers: {len(container_def.sub_containers)}"
                QMessageBox.information(self, "Container Definition", info)
        elif result_type == 'parameter_def':
            container_name = parts[0]
            param_name = parts[-1]
            if self.module_def and container_name in self.module_def.containers:
                container_def = self.module_def.containers[container_name]
                if param_name in container_def.parameters:
                    param_def = container_def.parameters[param_name]
                    info = f"Parameter: {param_name}\n"
                    info += f"Type: {param_def.param_type}\n"
                    info += f"Description: {param_def.description or 'N/A'}\n"
                    if param_def.min_value is not None:
                        info += f"Min: {param_def.min_value}\n"
                    if param_def.max_value is not None:
                        info += f"Max: {param_def.max_value}\n"
                    if param_def.default_value is not None:
                        info += f"Default: {param_def.default_value}"
                    QMessageBox.information(self, "Parameter Definition", info)
    
    def _navigate_to_container(self, path: str):
        """Navigate to a container instance in tree view"""
        if not self.config_manager:
            self.statusbar.showMessage("No configuration loaded", 3000)
            return
        
        # Find the container by path
        parts = path.split('/')
        container = self._find_container_by_path(parts)
        
        if container:
            # Get container definition
            container_def = self.module_def.get_container_def(
                container.definition_ref.split('/')[-1] if '/' in container.definition_ref 
                else container.definition_ref
            )
            
            if container_def:
                # Select in tree view (this will trigger the selection signal)
                self.tree_view._select_instance(container)
                
                # Also show in config panel
                self.config_panel.show_instance(container, container_def, self.config_manager)
                
                self.statusbar.showMessage(f"✓ Navigated to: {path}", 3000)
        else:
            self.statusbar.showMessage(f"✗ Container not found: {path}", 3000)
    
    def _find_container_by_path(self, path_parts):
        """Find container instance by path"""
        if not self.config_manager:
            return None
        
        containers = self.config_manager.configuration.containers
        current = None
        
        for part in path_parts:
            found = None
            for container in containers:
                if container.short_name == part:
                    found = container
                    current = container
                    containers = container.sub_containers
                    break
            if not found:
                return None
        
        return current
    
    def show_dependency_graph(self):
        """Show dependency graph in a new window"""
        if not self.config_manager or not self.module_def:
            QMessageBox.warning(
                self,
                "No Configuration",
                "Please load a configuration first."
            )
            return
        
        # Create graph dialog if not exists or was closed
        if not hasattr(self, 'dep_graph_dialog') or not self.dep_graph_dialog:
            from PySide6.QtWidgets import QDialog, QVBoxLayout
            
            self.dep_graph_dialog = QDialog(self)
            self.dep_graph_dialog.setWindowTitle("Dependency Graph")
            self.dep_graph_dialog.resize(800, 600)
            
            layout = QVBoxLayout(self.dep_graph_dialog)
            
            self.dep_graph_widget = DependencyGraphWidget()
            layout.addWidget(self.dep_graph_widget)
            
            # Build graph
            self.dep_graph_widget.build_graph(
                self.module_def,
                self.config_manager.configuration
            )
            
            # Show dialog
            self.dep_graph_dialog.show()
        else:
            self.dep_graph_dialog.raise_()
            self.dep_graph_dialog.activateWindow()
    
    def _analyze_cross_module_dependencies(self):
        """Analyze project to find potential cross-module dependencies using AI"""
        if not self.current_project:
            QMessageBox.warning(
                self,
                "需要项目",
                "请先打开一个包含多个模块的项目。\n\n"
                "此功能用于分析跨模块依赖，需要加载多模块项目。"
            )
            return
        
        from pathlib import Path
        from ..core.ai.dependency_analyzer import DependencyAnalyzer
        
        # Get API key  
        api_key = self.settings.value("gemini_api_key")
        gemini_client = None
        if api_key:
            from ..core.ai.gemini_client import GeminiClient
            gemini_client = GeminiClient(api_key)
        
        # Create analyzer
        analyzer = DependencyAnalyzer(gemini_client)
        
        # Show progress
        self.statusBar().showMessage("正在分析跨模块依赖（后台运行中）...")
        
        # Extract parameters (this is fast)
        params = analyzer.extract_project_parameters(self.current_project)
        
        if not params:
            QMessageBox.information(
                self,
                "无参数",
                "未找到可分析的参数。请确保已加载模块配置。"
            )
            return
        
        # Store for later use
        project_dir = Path(self.current_project.path).parent if self.current_project.path else Path.cwd()
        output_path = project_dir / "dependencies.md"
        
        # Run AI analysis in background thread
        class DependencyWorker(QRunnable):
            def __init__(self, analyzer, params, output_path, signals):
                super().__init__()
                self.analyzer = analyzer
                self.params = params
                self.output_path = output_path
                self.signals = signals
            
            @Slot()
            def run(self):
                try:
                    # This is the slow AI call
                    dependencies = self.analyzer.analyze_with_ai(self.params)
                    # Generate markdown
                    self.analyzer.generate_markdown(dependencies, self.output_path)
                    self.signals.result.emit(f"{len(dependencies)}|{str(self.output_path)}")
                except Exception as e:
                    self.signals.error.emit(str(e))
        
        # Create worker with signals
        worker = DependencyWorker(analyzer, params, output_path, AIWorkerSignals())
        worker.signals.result.connect(self._on_dependency_analysis_done)
        worker.signals.error.connect(self._on_dependency_analysis_error)
        
        # Submit to thread pool
        self.thread_pool.start(worker)
    
    def _on_dependency_analysis_done(self, result: str):
        """Handle completed dependency analysis"""
        parts = result.split("|", 1)
        count = int(parts[0])
        output_path = parts[1]
        
        self.statusBar().showMessage(f"依赖分析完成，发现 {count} 条潜在规则", 5000)
        
        # Ask to open file
        reply = QMessageBox.question(
            self,
            "分析完成",
            f"发现 {count} 条潜在的跨模块依赖关系。\n\n"
            f"结果已保存到:\n{output_path}\n\n"
            "是否打开文件进行审核？",
            QMessageBox.Yes | QMessageBox.No,
            QMessageBox.Yes
        )
        
        if reply == QMessageBox.Yes:
            import subprocess
            import sys
            if sys.platform == 'darwin':
                subprocess.run(['open', str(output_path)])
            elif sys.platform == 'win32':
                subprocess.run(['start', str(output_path)], shell=True)
            else:
                subprocess.run(['xdg-open', str(output_path)])
    
    def _on_dependency_analysis_error(self, error: str):
        """Handle dependency analysis error"""
        self.statusBar().showMessage("依赖分析失败", 3000)
        QMessageBox.critical(
            self,
            "分析失败",
            f"依赖分析过程中出错：\n\n{error}"
        )
    
    def _validate_cross_module_dependencies(self):
        """Validate project against confirmed dependency rules"""
        if not self.current_project:
            QMessageBox.warning(
                self,
                "需要项目",
                "请先打开一个包含多个模块的项目。"
            )
            return
        
        from pathlib import Path
        from ..core.rules.cross_module_validator import CrossModuleValidator
        
        # Find dependencies.md
        project_dir = Path(self.current_project.path).parent if self.current_project.path else Path.cwd()
        dep_file = project_dir / "dependencies.md"
        
        if not dep_file.exists():
            QMessageBox.warning(
                self,
                "规则文件未找到",
                f"未找到依赖规则文件:\n{dep_file}\n\n"
                "请先执行 '分析跨模块依赖' 生成规则文件，\n"
                "然后在文件中确认规则（将 [ ] 改为 [x]）。"
            )
            return
        
        # Load and validate
        validator = CrossModuleValidator()
        rule_count = validator.load_rules_from_markdown(dep_file)
        
        if rule_count == 0:
            QMessageBox.information(
                self,
                "无确认的规则",
                f"文件 {dep_file.name} 中没有已确认的规则。\n\n"
                "请编辑该文件，将要启用的规则状态从 [ ] 改为 [x]。"
            )
            return
        
        # Validate project
        result = validator.validate_project(self.current_project)
        
        # Show results
        if result.is_valid:
            QMessageBox.information(
                self,
                "验证通过 ✅",
                f"跨模块依赖验证通过！\n\n"
                f"已检查 {rule_count} 条规则，未发现违规。"
            )
        else:
            # Build error message
            errors = [m for m in result.messages if m.severity == 'error']
            warnings = [m for m in result.messages if m.severity == 'warning']
            
            error_text = "\n\n".join([
                f"❌ {e.message}\n   建议: {e.suggested_fix}" for e in errors[:5]
            ])
            
            if len(errors) > 5:
                error_text += f"\n\n...还有 {len(errors) - 5} 个错误"
            
            QMessageBox.critical(
                self,
                "验证失败 ❌",
                f"发现 {len(errors)} 个错误, {len(warnings)} 个警告:\n\n"
                f"{error_text}"
            )
    
    def _on_instance_selected(self, instance: EcucContainerValue, container_def: EcucContainerDef, manager=None):
        """Handle instance selection in tree"""
        # Update active context if manager provided (Project Mode)
        if manager:
            self._update_active_context(manager)
            
        self.config_panel.show_instance(instance, container_def, self.config_manager, self.current_project)
    
    def _on_def_selected(self, container_def: EcucContainerDef, manager=None):
        """Handle definition node selection in tree"""
        # Update active context if manager provided (Project Mode)
        if manager:
            self._update_active_context(manager)
            
        self.config_panel.show_definition(container_def)
        
    def _on_module_selected(self, module_def: EcucModuleDef, manager=None):
        """Handle module node selection in tree"""
        if manager:
            self._update_active_context(manager)
        
        # Show module info in panel? Or just clear?
        # For now, let's clear or show basic module info
        # self.config_panel.clear() 
        # Or better:
        # self.config_panel.show_module_info(module_def) (If implemented)
        self.config_panel.clear()
        
    def _update_active_context(self, manager):
        """Update active configuration context (for Project Mode)"""
        if self.config_manager != manager:
            self.config_manager = manager
            self.module_def = manager.module_def
            
            # Update status bar
            self.def_file_label.setText(f"DEF: {self.module_def.short_name}")
            self.value_file_label.setText(f"Config: {self.config_manager.configuration.short_name}")
            
            # Enable actions
            self.save_value_action.setEnabled(True)
            self.validate_action.setEnabled(True)
            self.load_rules_action.setEnabled(True)
            self.generate_action.setEnabled(True)
            self.quick_config_action.setEnabled(True)
            self.show_dep_graph_action.setEnabled(True)
    
    def _on_parameter_changed(self, instance: EcucContainerValue, param_name: str, value: any):
        """Handle parameter value change"""
        # Delegate to command handler
        self.handle_parameter_change(instance, param_name, value)
    
    def _load_last_session(self):
        """Load last opened DEF file"""
        last_def = self.settings.value("last_def_file")
        if last_def and Path(last_def).exists():
            # Auto-load on startup?
            pass  # For now, let user manually open
    
    def _on_ai_help_requested(self, container_name: str, param_name: str):
        """Handle AI help request for a parameter - provide contextual guidance"""
        api_key = self.settings.value("gemini_api_key")
        if not api_key:
            self.config_panel.update_ai_help("⚠️ 请先在 AI Assistant 中配置 API Key")
            return
        
        # Initialize AI processor if needed
        if not self.ai_processor:
            self.ai_processor = NaturalLanguageProcessor(
                api_key=api_key,
                config_manager=self.config_manager,
                undo_stack=self.undo_stack,
                action_handler=self._handle_ai_action
            )
        
        # Build prompt for AI - handle both parameters and references
        if param_name.startswith("REF:"):
            # Reference request - format: "REF:ref_name:dest_type"
            parts = param_name.split(":", 2)
            ref_name = parts[1] if len(parts) > 1 else param_name
            dest_type = parts[2] if len(parts) > 2 else "unknown"
            
            prompt = f"""你是一个AUTOSAR BSW配置专家。请针对以下引用(Reference)提供简洁的配置指导：

容器: {container_name}
引用名: {ref_name}
目标类型: {dest_type}

请用2-3句话说明：
1. 这个引用的作用是什么？它连接什么模块或资源？
2. 配置时需要注意什么？如何选择正确的目标？

请直接给出指导，不要有多余的开场白。使用中文回答。"""
        else:
            # Parameter request
            prompt = f"""你是一个AUTOSAR BSW配置专家。请针对以下参数提供简洁的配置指导：

容器: {container_name}
参数: {param_name}

请用2-3句话说明：
1. 这个参数的作用是什么？它影响什么功能？
2. 配置时需要注意什么？有什么常见错误要避免？

请直接给出指导，不要有多余的开场白。使用中文回答。"""
        
        # Use subprocess via QProcess for truly killable AI requests
        from PySide6.QtCore import QProcess
        import json
        import sys
        
        # Create the QProcess
        process = QProcess(self)
        self.config_panel.current_ai_process = process  # Store for cancellation
        
        # Build Python script to run in subprocess
        script = f'''
import sys
import google.generativeai as genai

api_key = sys.argv[1]
prompt = sys.argv[2]
model_name = sys.argv[3] if len(sys.argv) > 3 else "gemini-2.0-flash"

try:
    genai.configure(api_key=api_key)
    model = genai.GenerativeModel(model_name)
    response = model.generate_content(prompt, request_options={{"timeout": 15}})
    print(response.text)
except Exception as e:
    print(f"ERROR: {{str(e)}}", file=sys.stderr)
'''
        
        def on_finished(exit_code, exit_status):
            if self.config_panel.ai_request_cancelled:
                self._ai_help_process = None
                return
            
            try:
                if self._ai_help_process:
                    output = self._ai_help_process.readAllStandardOutput().data().decode('utf-8').strip()
                    error = self._ai_help_process.readAllStandardError().data().decode('utf-8').strip()
                    
                    if exit_code == 0 and output:
                        self.config_panel.update_ai_help(output)
                        self.config_panel.cache_ai_help(container_name, param_name, output)
                    elif error:
                        self.config_panel.update_ai_help(f"❌ {error}")
                    else:
                        self.config_panel.update_ai_help("❌ 请求失败，请重试")
            except RuntimeError:
                pass  # Process already deleted
            finally:
                self.config_panel.current_ai_process = None
                self._ai_help_process = None
        
        process.finished.connect(on_finished)
        
        # Store reference to prevent garbage collection
        self._ai_help_process = process
        
        # Get current model name
        model_name = "gemini-2.0-flash"
        if self.ai_processor and self.ai_processor.gemini_client:
            model_name = self.ai_processor.gemini_client.get_current_model()
        
        # Start subprocess
        process.start(sys.executable, ["-c", script, api_key, prompt, model_name])
    
    def _show_about_dialog(self):
        """Show about dialog with version information"""
        version = "1.0.0"
        QMessageBox.about(
            self,
            "关于 DaVinci Configurator",
            f"""<h3>DaVinci Configurator</h3>
            <p><b>版本:</b> {version}</p>
            <p><b>描述:</b> AUTOSAR BSW 配置工具</p>
            <p>支持模块定义解析、配置编辑、代码生成和AI辅助验证。</p>
            <p><b>主要功能:</b></p>
            <ul>
            <li>📋 模块定义和配置管理</li>
            <li>🔍 跨模块依赖分析</li>
            <li>🤖 AI 智能验证和帮助</li>
            <li>📊 依赖关系可视化</li>
            <li>⚙️ 代码自动生成</li>
            </ul>
            <p><b>技术栈:</b> Python 3, PySide6, Google Gemini AI</p>
            """
        )
    
    def _update_recent_files_menu(self):
        """Update recent files menu with current list"""
        # TODO: Implement fully
        self.recent_files_menu.clear()
        no_files_action = QAction("(No recent files)", self)
        no_files_action.setEnabled(False)
        self.recent_files_menu.addAction(no_files_action)
    
    def closeEvent(self, event):
        """Handle window close event - check for unsaved changes"""
        unsaved_items = []
        
        # Check for unsaved changes
        if self.current_project:
            # Project mode: check all modules
            for module_name, manager in self.current_project.module_managers.items():
                if manager.configuration.is_modified:
                    unsaved_items.append(f"Module: {module_name}")
        elif self._has_unsaved_changes:
            # Single module mode
            unsaved_items.append("Current configuration")
        
        if unsaved_items:
            items_text = "\n  • ".join(unsaved_items)
            reply = QMessageBox.question(
                self,
                "Unsaved Changes",
                f"You have unsaved changes in:\n  • {items_text}\n\n"
                "Do you want to save before closing?",
                QMessageBox.Save | QMessageBox.Discard | QMessageBox.Cancel,
                QMessageBox.Save
            )
            
            if reply == QMessageBox.Save:
                # Try to save
                if self.current_project:
                    self.save_project()
                    # Check if all succeeded
                    still_unsaved = [
                        name for name, mgr in self.current_project.module_managers.items()
                        if mgr.configuration.is_modified
                    ]
                    if still_unsaved:
                        event.ignore()
                        return
                else:
                    self.save_value_file()
                    if self._has_unsaved_changes:
                        event.ignore()
                        return
            elif reply == QMessageBox.Cancel:
                event.ignore()
                return
            # If Discard, continue with close
        
        # Cleanup thread pool to ensure all workers stop
        if hasattr(self, 'thread_pool') and self.thread_pool:
            self.thread_pool.clear()  # Clear pending tasks
            self.thread_pool.waitForDone(1000)  # Wait max 1 second for running tasks
        
        # Save window geometry
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("windowState", self.saveState())
        event.accept()
