"""
DaVinci-style Main Window for ECUC Configuration
Dual-mode: loads DEF files and allows creating VALUE instances
"""
from PySide6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QSplitter, QMenuBar, QMenu, QToolBar, QStatusBar,
    QFileDialog, QMessageBox, QStyle, QLabel, QInputDialog, QLineEdit,
    QPushButton, QToolButton, QDialog
)
from PySide6.QtCore import Qt, Signal, QSettings, QRunnable, QThreadPool, QObject, Slot, QTimer
from PySide6.QtGui import QAction, QKeySequence, QUndoStack, QIcon
from PySide6.QtWidgets import QDockWidget
from pathlib import Path
from typing import Optional, Dict, Any, List
import logging

logger = logging.getLogger(__name__)

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
    result = Signal(object)  # Emits the response (str or complex object)
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
        self.undo_stack.indexChanged.connect(lambda idx: self._update_dependency_graph_if_open())

        # Internal Clipboard
        self.clipboard_instance: Optional[EcucContainerValue] = None
        
        self._setup_ui()
        self._create_actions()
        self._create_menus()
        self._create_toolbars()
        self._create_statusbar()
        
        # Auto-load last project after a short delay to allow UI to show
        QTimer.singleShot(100, self._auto_load_last_project)
        
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
        self.tree_view.view_references_requested.connect(self._show_reverse_references)
        splitter.addWidget(self.tree_view)
        
        # Right: Config panel
        self.config_panel = DaVinciConfigPanel()
        self.config_panel.parameter_changed.connect(self._on_parameter_changed)
        self.config_panel.ai_help_requested.connect(self._on_ai_help_requested)
        self.config_panel.check_impact_requested.connect(self._handle_check_impact)
        self.config_panel.reference_jump_requested.connect(self._on_reference_jump_requested)
        self.config_panel.instance_variant_changed.connect(self._on_instance_variant_changed)
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
        
        # Impact View (Dock Widget)
        self._setup_impact_view()
        
        # Problems View (Bottom Dock)
        self._setup_problems_view()
    
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
            # Update key if it changed
            if self.ai_processor.gemini_client.api_key != api_key:
                 self.ai_processor.gemini_client.configure(api_key)
            # Update handler
            self.ai_processor.action_handler = self._handle_ai_action

        # Process Message Asynchronously
        logger.debug(f"Processing AI message (async): '{text}'")
        self.ai_assistant_widget.set_status("Thinking...", busy=True)
        
        # Get context from selection (Safely)
        context_instance = None
        try:
            if hasattr(self.tree_view, 'get_selected_instance'):
                context_instance = self.tree_view.get_selected_instance()
            else:
                logger.debug("tree_view missing get_selected_instance")
        except Exception as e:
            logger.debug(f"Context error: {e}")
        
        # Create worker and connect signals
        worker = AIWorker(self.ai_processor, text, context_instance)
        worker.signals.result.connect(self._on_ai_response)
        worker.signals.error.connect(self._on_ai_error)
        
        # Submit to thread pool (non-blocking)
        self.thread_pool.start(worker)
    
    def _on_ai_response(self, response: str):
        """Handle AI response from worker thread"""
        logger.debug(f"AI Response received: '{response[:50]}...'")
        self.ai_assistant_widget.append_message("AI", response)
        self.ai_assistant_widget.set_status("Ready")
    
    def _on_ai_error(self, error_msg: str):
        """Handle AI error from worker thread"""
        logger.debug(f"AI Error: {error_msg}")
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
        
        self.manage_variants_action = QAction("Manage Variants...", self)
        self.manage_variants_action.setEnabled(False)
        self.manage_variants_action.triggered.connect(self.manage_variants)
        
        self.add_module_action = QAction("Add Module to Project...", self)
        self.add_module_action.setEnabled(False)
        self.add_module_action.triggered.connect(self.add_module_to_project)
        
        self.load_recommended_action = QAction("Load Recommended Values...", self)
        self.load_recommended_action.setEnabled(False)
        self.load_recommended_action.triggered.connect(self.load_recommended_values)
        
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
        self.validate_action.triggered.connect(self.validate_configuration)

        self.load_rules_action = QAction("Load Custom Rules...", self)
        self.load_rules_action.setEnabled(False)
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
        file_menu.addAction(self.manage_variants_action)
        file_menu.addSeparator()
        file_menu.addAction(self.add_module_action)
        file_menu.addAction(self.load_recommended_action)
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
        
        user_manual_action = QAction("使用手册 (User Manual)", self)
        user_manual_action.setShortcut("F1")
        user_manual_action.triggered.connect(self._show_user_manual)
        help_menu.addAction(user_manual_action)
        
        help_menu.addSeparator()
        
        about_action = QAction("关于 DaVinci Configurator", self)
        about_action.triggered.connect(self._show_about_dialog)
        help_menu.addAction(about_action)
    
    def _create_toolbars(self):
        """Create toolbars"""
        from PySide6.QtWidgets import QComboBox
        
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
        toolbar.addSeparator()
        
        # Base configuration button
        self.base_btn = QPushButton("📋 Base")
        self.base_btn.setToolTip("创建或修改 Base 配置")
        self.base_btn.clicked.connect(self._on_base_btn_clicked)
        self.base_btn.setEnabled(False)
        toolbar.addWidget(self.base_btn)
        
        # Global variant selector
        variant_view_label = QLabel("View Variant (当前视图):")
        variant_view_label.setToolTip("Select the active variant for filtering the configuration tree and for code generation.")
        toolbar.addWidget(variant_view_label)
        self.variant_selector = QComboBox()
        self.variant_selector.setMinimumWidth(150)
        self.variant_selector.addItem("(No Variants)")
        self.variant_selector.setEnabled(False)
        self.variant_selector.currentTextChanged.connect(self._on_variant_changed)
        toolbar.addWidget(self.variant_selector)
        
        # Quick manage button
        self.manage_variants_btn = QPushButton()
        self.manage_variants_btn.setIcon(self.style().standardIcon(QStyle.SP_FileDialogDetailedView))
        self.manage_variants_btn.setToolTip("Manage Variants...")
        self.manage_variants_btn.setFixedWidth(30)
        self.manage_variants_btn.clicked.connect(self.manage_variants)
        self.manage_variants_btn.setEnabled(False)
        toolbar.addWidget(self.manage_variants_btn)
        
        # Reference variant selector for comparison
        toolbar.addWidget(QLabel(" vs "))
        self.reference_variant_selector = QComboBox()
        self.reference_variant_selector.setMinimumWidth(120)
        self.reference_variant_selector.addItem("Base (基础)")
        self.reference_variant_selector.setToolTip("选择参考变体进行对比 (高亮显示差异)")
        self.reference_variant_selector.setEnabled(False)
        self.reference_variant_selector.currentTextChanged.connect(self._on_reference_variant_changed)
        toolbar.addWidget(self.reference_variant_selector)
        
        toolbar.addSeparator()
        
        # AI Assistant toggle button
        self.ai_toggle_btn = QPushButton()
        self.ai_toggle_btn.setIcon(self.style().standardIcon(QStyle.SP_MessageBoxQuestion))
        self.ai_toggle_btn.setToolTip("Toggle AI Assistant")
        self.ai_toggle_btn.setFixedWidth(30)
        self.ai_toggle_btn.clicked.connect(self.toggle_ai_action.trigger)
        toolbar.addWidget(self.ai_toggle_btn)
        
        toolbar.addSeparator()
    
    def _create_statusbar(self):
        """Create status bar with permanent indicators"""
        self.statusbar = QStatusBar()
        self.setStatusBar(self.statusbar)
        
        # Mode indicator (left side - permanent)
        self.mode_label = QLabel("Mode: Single Module")
        self.mode_label.setStyleSheet("QLabel { padding: 2px 10px; }")
        self.statusbar.addPermanentWidget(self.mode_label)
        
        # Variant indicator
        self.variant_label = QLabel("Variant: None")
        self.variant_label.setStyleSheet("QLabel { padding: 2px 10px; }")
        self.statusbar.addPermanentWidget(self.variant_label)
        
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
    
    def _on_variant_changed(self, variant_name: str):
        """Handle Variant selector change"""
        if not self.current_project or variant_name == "(No Variants)":
            return
        
        if self.current_project:
            self.current_project.active_variant = variant_name
            # Notify tree view to filter instances
            self.tree_view.set_active_variant(variant_name)
            
        self.variant_label.setText(f"Variant: {variant_name}")
        
        # Count overrides for this variant across all modules
        total_overrides = 0
        if self.current_project:
            for manager in self.current_project.module_managers.values():
                total_overrides += manager.configuration.get_variant_overrides_count(variant_name)
        
        # Check if current config panel instance is still valid for the new variant
        if hasattr(self, 'config_panel') and self.config_panel and self.config_panel.current_instance:
            instance = self.config_panel.current_instance
            # Clear config panel if instance belongs to a different variant (not current and not global)
            if instance.variant is not None and instance.variant != variant_name:
                self.config_panel.clear()
                self.statusbar.showMessage(
                    f"已清空：实例 '{instance.short_name}' 不属于变体 '{variant_name}'", 
                    5000
                )
            else:
                # Refresh to show variant-specific values
                self.config_panel.refresh()
        
        msg = f"Switched to Variant: {variant_name}"
        if total_overrides > 0:
            msg += f" ({total_overrides} parameter overrides)"
        self.statusbar.showMessage(msg, 3000)
    
    def _on_reference_variant_changed(self, reference_name: str):
        """Handle Reference Variant selector change for comparison"""
        if not self.current_project:
            return
        
        # Set reference variant on config panel (None = Base)
        ref_variant = None if reference_name == "Base (基础)" else reference_name
        
        if hasattr(self, 'config_panel') and self.config_panel:
            self.config_panel.reference_variant = ref_variant
            self.config_panel.refresh()
        
        if ref_variant:
            self.statusbar.showMessage(f"对比参考变体: {ref_variant}", 2000)
        else:
            self.statusbar.showMessage("对比参考: 基础配置", 2000)
    
    def _on_base_btn_clicked(self):
        """Handle Base button click - create or modify Base configuration"""
        if not self.current_project:
            return
        
        from .widgets.base_config_dialog import BaseConfigDialog
        
        is_modify = self.current_project.has_base
        dialog = BaseConfigDialog(self, is_modify=is_modify)
        
        if dialog.exec():
            method = dialog.get_selected_method()
            self.current_project.create_base(init_method=method)
            
            # Update UI
            self._update_variant_selector()
            
            # Status message
            method_names = {"arxml": "ARXML 配置", "defaults": "定义默认值", "empty": "空白"}
            if is_modify:
                self.statusbar.showMessage(f"Base 配置已更新 (来源: {method_names.get(method, method)})", 3000)
            else:
                self.statusbar.showMessage(f"Base 配置已创建 (来源: {method_names.get(method, method)})", 3000)
                QMessageBox.information(
                    self, "Base 已创建",
                    "Base 配置已创建！\n\n"
                    "现在您可以：\n"
                    "1. 创建和配置变体\n"
                    "2. 使用 '⚡ Check Diff' 对比变体差异"
                )
    
    def _update_variant_selector(self):
        """Update the Variant selector dropdown with project variants"""
        self.variant_selector.blockSignals(True)
        self.variant_selector.clear()
        
        # Also update reference variant selector
        self.reference_variant_selector.blockSignals(True)
        self.reference_variant_selector.clear()
        self.reference_variant_selector.addItem("Base (基础)")
        
        # Update Base button state
        if self.current_project:
            self.base_btn.setEnabled(True)
            if self.current_project.has_base:
                self.base_btn.setText("📋 修改 Base")
                self.base_btn.setToolTip("修改 Base 配置")
            else:
                self.base_btn.setText("📋 创建 Base")
                self.base_btn.setToolTip("创建 Base 配置 (必须先创建才能配置变体)")
        else:
            self.base_btn.setEnabled(False)
            self.base_btn.setText("📋 Base")
        
        if self.current_project and self.current_project.variants:
            # Only enable variant selector if Base exists
            has_base = self.current_project.has_base
            self.variant_selector.setEnabled(has_base)
            self.reference_variant_selector.setEnabled(has_base)
            self.manage_variants_btn.setEnabled(has_base)
            
            for variant in self.current_project.variants:
                self.variant_selector.addItem(variant)
                self.reference_variant_selector.addItem(variant)
            
            # Select active variant
            if self.current_project.active_variant:
                idx = self.variant_selector.findText(self.current_project.active_variant)
                if idx >= 0:
                    self.variant_selector.setCurrentIndex(idx)
            
            if has_base:
                self.variant_label.setText(f"Variant: {self.current_project.active_variant or self.current_project.variants[0]}")
            else:
                self.variant_label.setText("⚠️ 请先创建 Base")
        else:
            self.variant_selector.addItem("(No Variants)")
            self.variant_selector.setEnabled(False)
            self.reference_variant_selector.setEnabled(False)
            self.variant_label.setText("Variant: None")
        
        self.variant_selector.blockSignals(False)
        self.reference_variant_selector.blockSignals(False)
    
    # Project operations
    
    def new_project(self):
        """Create a new project"""
        from PySide6.QtWidgets import QInputDialog, QComboBox, QDialog, QVBoxLayout, QDialogButtonBox, QFormLayout
        from ..core.config_manager import ProjectType, ConfigLoader
        
        # Project type selection dialog
        dialog = QDialog(self)
        dialog.setWindowTitle("New Project")
        layout = QVBoxLayout(dialog)
        
        form = QFormLayout()
        
        name_edit = QLineEdit()
        form.addRow("Project Name:", name_edit)
        
        type_combo = QComboBox()
        type_combo.addItem("Vector DaVinci", ProjectType.VECTOR)
        type_combo.addItem("EB Tresos", ProjectType.EB_TRESOS)
        form.addRow("Project Type:", type_combo)
        
        layout.addLayout(form)
        
        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(dialog.accept)
        buttons.rejected.connect(dialog.reject)
        layout.addWidget(buttons)
        
        if dialog.exec() != QDialog.Accepted:
            return
            
        name = name_edit.text().strip()
        project_type = type_combo.currentData()
        
        if not name:
            QMessageBox.warning(self, "Error", "Project name cannot be empty")
            return
        
        # Choose save location based on type
        if project_type == ProjectType.VECTOR:
            file_path, _ = QFileDialog.getSaveFileName(
                self,
                "Save Project As",
                str(Path.home() / f"{name}.dpa"),
                "DaVinci Project (*.dpa);;All Files (*)"
            )
            if not file_path:
                return
            project_path = Path(file_path)
        else:
            # EB: Select folder
            folder_path = QFileDialog.getExistingDirectory(
                self,
                "Select EB Project Folder",
                str(Path.home()),
                QFileDialog.ShowDirsOnly
            )
            if not folder_path:
                return
            project_path = Path(folder_path) / f"{name}.dpa"
            
            # Create .tresos marker folder for EB
            tresos_marker = Path(folder_path) / ".tresos"
            tresos_marker.mkdir(exist_ok=True)
            
        self.current_project = self.workspace_manager.create_project(name, project_path)
        self.current_project.project_type = project_type
        self.current_project.def_search_paths = ConfigLoader.get_def_search_paths(project_path.parent)
        self.current_project_file = project_path
        self.tree_view.set_project(self.current_project)
        
        self.save_project_action.setEnabled(True)
        self.add_module_action.setEnabled(True)
        self.manage_variants_action.setEnabled(True)
        self.manage_variants_btn.setEnabled(True)
        
        # Update variant selector
        self._update_variant_selector()
        
        # Update mode label
        self.mode_label.setText(f"Project: {project_type.value}")
        
        self.statusbar.showMessage(f"Created {project_type.value} project: {name}", 3000)
        
    def open_project(self):
        """Open an existing project (Vector .dpa or EB folder)"""
        from ..core.config_manager import ProjectTypeDetector, ConfigLoader, ProjectType
        
        # Allow selecting a file (.dpa) OR a folder (for EB projects)
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open Project (.dpa) or select a folder",
            str(Path.home()),
            "DaVinci Project (*.dpa);;All Files (*)"
        )
        
        # If user cancelled file dialog, try folder dialog
        if not file_path:
            folder_path = QFileDialog.getExistingDirectory(
                self,
                "Open Project Folder (EB Tresos)",
                str(Path.home()),
                QFileDialog.ShowDirsOnly
            )
            if not folder_path:
                return
            project_path = Path(folder_path)
        else:
            project_path = Path(file_path)
            
        self._load_project_at_path(project_path)

    def _load_project_at_path(self, path: Path):
        """Unified logic to load a project from a path (file or folder)"""
        from ..core.config_manager import ProjectTypeDetector, ConfigLoader, ProjectType
        
        if not path.exists():
            return

        if path.is_file():
            project_root = path.parent
            file_path = str(path)
        else:
            project_root = path
            file_path = None
            
        # Detect project type
        project_type = ProjectTypeDetector.detect(project_root)
        
        if project_type == ProjectType.UNKNOWN:
            QMessageBox.warning(
                self,
                "Unknown Project Type",
                f"Could not detect project type for:\n{project_root}\n\n"
                "Expected: .dpa file (Vector) or .tresos/.project marker (EB)"
            )
            return
            
        self.statusbar.showMessage(f"Detected {project_type.value} project, loading...")
        
        # Get search paths for definitions
        def_search_paths = ConfigLoader.get_def_search_paths(project_root)
        
        try:
            if project_type == ProjectType.VECTOR and (file_path or path.is_file()):
                # Use existing .dpa loading logic
                load_path = Path(file_path) if file_path else path
                self.current_project, failed_modules = self.workspace_manager.load_project(load_path)
                self.current_project_file = load_path
            else:
                # EB project: Create a new project from folder
                # For now, we just set up the search paths and let user add modules manually
                # A more advanced implementation would scan for .xdm files
                project_name = project_root.name
                self.current_project = self.workspace_manager.create_project(
                    project_name,
                    project_root / f"{project_name}.dpa"  # Virtual path
                )
                self.current_project_file = project_root
                failed_modules = []
                
                # Store search paths for later use when adding modules
                self.current_project.def_search_paths = def_search_paths
                
                QMessageBox.information(
                    self,
                    "EB Project Loaded",
                    f"EB Tresos project detected.\n\n"
                    f"Definition search paths:\n" + "\n".join([f"• {p}" for p in def_search_paths]) +
                    f"\n\nUse 'Add Module to Project' to add modules."
                )
            
            self.tree_view.set_project(self.current_project)
            
            # Set project type on loaded project
            self.current_project.project_type = project_type
            
            # Enable project actions
            self.save_project_action.setEnabled(True)
            self.project_properties_action.setEnabled(True)
            self.manage_variants_action.setEnabled(True)
            self.manage_variants_btn.setEnabled(True)
            self.add_module_action.setEnabled(True)
            
            # Update variant selector
            self._update_variant_selector()
            
            # Update mode label
            self.mode_label.setText(f"Project: {project_type.value}")
            
            # Update menu/toolbar states for project mode
            self._update_mode_actions()
            
            status_msg = f"Loaded project: {self.current_project.name} ({project_type.value})"
            
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
            
            # Save as last loaded project for auto-loading next time
            self.settings.setValue("last_project_path", str(self.current_project_file))

            # Add to recent files
            self._add_to_recent_files(str(self.current_project_file))
            
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
    
    def manage_variants(self):
        """Show improved dialog to manage project variants"""
        if not self.current_project:
            return
            
        from .widgets.variant_management_dialog import VariantManagementDialog
        
        dialog = VariantManagementDialog(self.current_project, self)
        if dialog.exec() == QDialog.Accepted:
            # Update UI
            self._update_variant_selector()
            self.statusbar.showMessage(f"Variants updated: {len(self.current_project.variants)} defined", 3000)
    
    def add_module_to_project(self):
        """Add a module to the current project"""
        if not self.current_project:
            return
            
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Select Module DEF File",
            str(Path.home()),
            "All Supported Files (*.arxml *.xdm);;ARXML Files (*.arxml);;EB Tresos Files (*.xdm);;All Files (*)"
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
    
    def load_recommended_values(self):
        """Load and apply recommended values from _rec.arxml file"""
        from ..core.config_manager import RecFileScanner
        from PySide6.QtWidgets import (QDialog, QVBoxLayout, QTableWidget, QTableWidgetItem,
                                       QDialogButtonBox, QHeaderView, QCheckBox)
        
        # Need an active configuration
        if not self.config_manager:
            QMessageBox.warning(self, "No Module Loaded", "Please load a module first.")
            return
        
        # Find rec files
        if self.current_project and self.current_project.path:
            project_root = self.current_project.path.parent
        else:
            project_root = Path.home()
        
        # Let user select rec file
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Select Recommended Values File",
            str(project_root),
            "Rec Files (*_rec.arxml *.xdm);;ARXML Files (*.arxml);;EB Tresos Files (*.xdm);;All Files (*)"
        )
        
        if not file_path:
            return
        
        # Load recommended values
        rec_config = self.config_manager.load_recommended_values(Path(file_path))
        if not rec_config:
            QMessageBox.warning(self, "Load Failed", "Could not parse recommended values file.")
            return
        
        # Get comparison
        comparisons = self.config_manager.get_recommended_value_comparison(rec_config)
        
        if not comparisons:
            QMessageBox.information(self, "No Values", "No comparable values found in rec file.")
            return
        
        # Show comparison dialog
        dialog = QDialog(self)
        dialog.setWindowTitle("Recommended Values Comparison")
        dialog.setMinimumSize(700, 400)
        layout = QVBoxLayout(dialog)
        
        # Table
        table = QTableWidget()
        table.setColumnCount(4)
        table.setHorizontalHeaderLabels(["Parameter", "Current", "Recommended", "Different"])
        table.setRowCount(len(comparisons))
        
        for row, comp in enumerate(comparisons):
            table.setItem(row, 0, QTableWidgetItem(comp['param_path']))
            table.setItem(row, 1, QTableWidgetItem(str(comp['current_value'] or "")))
            table.setItem(row, 2, QTableWidgetItem(str(comp['recommended_value'] or "")))
            table.setItem(row, 3, QTableWidgetItem("Yes" if comp['differs'] else ""))
            
            # Highlight differing rows
            if comp['differs']:
                for col in range(4):
                    table.item(row, col).setBackground(Qt.yellow)
        
        table.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        layout.addWidget(table)
        
        # Checkbox for only_empty option
        only_empty_cb = QCheckBox("Only apply to empty/unset parameters")
        only_empty_cb.setChecked(True)
        layout.addWidget(only_empty_cb)
        
        # Buttons
        buttons = QDialogButtonBox(QDialogButtonBox.Apply | QDialogButtonBox.Cancel)
        buttons.button(QDialogButtonBox.Apply).clicked.connect(dialog.accept)
        buttons.rejected.connect(dialog.reject)
        layout.addWidget(buttons)
        
        if dialog.exec() == QDialog.Accepted:
            only_empty = only_empty_cb.isChecked()
            updated = self.config_manager.apply_recommended_values(rec_config, only_empty)
            
            # Refresh UI
            if self.tree_view.currentItem():
                self.tree_view._on_item_clicked(self.tree_view.currentItem(), 0)
            
            QMessageBox.information(self, "Applied", f"Updated {updated} parameter(s) with recommended values.")
            self.statusbar.showMessage(f"Applied {updated} recommended values", 3000)
    
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
            "All Supported Files (*.arxml *.xdm);;ARXML Files (*.arxml);;EB Tresos Files (*.xdm);;All Files (*)"
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
            
            # Update mode label for single-module mode
            self.mode_label.setText(f"Module: {self.module_def.short_name}")
            
            # Update menu/toolbar states
            self._update_mode_actions()
            
            # Save to settings
            self.settings.setValue("last_def_file", str(file_path))

            # Add to recent files
            self._add_to_recent_files(str(file_path))
            
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
        self.validate_action.setEnabled(True)
        self.load_rules_action.setEnabled(True)
        self.generate_action.setEnabled(True)
        self.quick_config_action.setEnabled(True)
        
        # Update mode actions to ensure consistency
        self._update_mode_actions()
        self.show_dep_graph_action.setEnabled(True)
        self.load_recommended_action.setEnabled(True)
        
        self.value_file_label.setText("New configuration (unsaved)")
        self.current_value_file = None
        
        self.statusbar.showMessage("New configuration created", 3000)
        self._update_dependency_graph_if_open()
    
    def open_value_file(self):
        """Open existing ECUC-VALUE file"""
        if not self.config_manager:
            QMessageBox.warning(self, "No DEF File", "Please open an ECUC-DEF file first.")
            return

        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open Configuration File",
            str(Path.home()),
            "All Supported Files (*.arxml *.xdm);;ARXML Files (*.arxml);;EB Tresos Files (*.xdm);;All Files (*)"
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
            self._update_dependency_graph_if_open()
            
            # Enable actions
            self.save_value_action.setEnabled(True)
            self.validate_action.setEnabled(True)
            self.load_rules_action.setEnabled(True)
            self.generate_action.setEnabled(True)
            self.quick_config_action.setEnabled(True)
            self.show_dep_graph_action.setEnabled(True)
            self.load_recommended_action.setEnabled(True)
            
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
            "ARXML Files (*.arxml);;EB Tresos Files (*.xdm)"
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

    def handle_parameter_change(self, instance: EcucContainerValue, param_name: str, value: Any):
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
        
        try:
            self.undo_stack.push(command)
            self._has_unsaved_changes = True
            self.statusbar.showMessage(f"Set {param_name}", 2000)
        except Exception as e:
            # Handle validation errors gracefully
            error_msg = str(e)
            # Extract the meaningful part of the error message
            if "Error calling Python override" in error_msg:
                # Extract the actual validation message
                parts = error_msg.split(":")
                if len(parts) >= 2:
                    error_msg = ":".join(parts[-2:]).strip()
            
            QMessageBox.warning(self, "验证失败", f"参数值无效:\n{error_msg}")
            self.statusbar.showMessage(f"验证失败: {param_name}", 3000)
            return
        
        # Refresh UI if needed (e.g. if reference changed, might need to update other views)
        # For now, config panel updates itself, but tree view might need refresh if name changed (not supported yet)
        self._update_dependency_graph_if_open()
        
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
        
        self._update_dependency_graph_if_open()
            
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

        self._update_dependency_graph_if_open()

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
        
        self._update_dependency_graph_if_open()
        
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
            
            self._update_dependency_graph_if_open()
            
        except Exception as e:
            QMessageBox.critical(self, "Paste Error", f"Failed to paste:\n{str(e)}")
    
    def validate_configuration(self):
        """Validate all modules in the project and show results in the Problems View"""
        if not self.current_project:
            return
        
        from ..core.validation_engine import ValidationResult
        all_results = ValidationResult()
        
        # 1. Run validation for each module
        for module_name, manager in self.current_project.module_managers.items():
            if manager.configuration and manager.module_def:
                # Use manager's engine or create one
                from ..core.validation_engine import ValidationEngine
                engine = ValidationEngine(manager.module_def, manager.configuration, self.current_project)
                engine.register_default_rules()
                
                # Execute validation
                module_result = engine.validate()
                all_results.merge(module_result)
        
        # 2. Add cross-module AI rules validation (if implemented in engine)
        # For now, these are already merged if rules handle them.
        
        # 3. Update Problems View
        self.problems_view.set_messages(all_results.messages)
        self.problems_dock.show()
        self.problems_dock.raise_()
        
        # 4. Update status bar/icons
        if all_results.is_valid:
            self.statusBar().showMessage(f"✅ Validation complete: No errors found in {len(self.current_project.module_managers)} modules.", 5000)
            self.validation_status_label.setText("✅ Valid")
            self.validation_status_label.setStyleSheet("QLabel { color: green; padding: 2px 10px; }")
        else:
            self.statusBar().showMessage(f"❌ Validation complete: Found {all_results.error_count} errors, {all_results.warning_count} warnings.", 5000)
            self.validation_status_label.setText(f"❌ {all_results.error_count} Errors")
            self.validation_status_label.setStyleSheet("QLabel { color: red; padding: 2px 10px; }")

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
            "Custom Rules (*.json *.py);;JSON Files (*.json);;Python Scripts (*.py);;All Files (*)"
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
                "Load Rules Error",
                f"Failed to load custom rules:\n{str(e)}"
            )

    def _get_all_project_configurations(self) -> Dict[str, Any]:
        """Collect all module configurations in the current project for cross-module access."""
        all_configs = {}
        if self.current_project:
            for name, manager in self.current_project.module_managers.items():
                if manager.module_def and manager.configuration:
                    all_configs[name] = (manager.module_def, manager.configuration)
        return all_configs

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
            
            # Get variant overrides if in project mode with active variant
            variant_overrides = {}
            variant_name = None
            project_template_dir = None

            if hasattr(self, 'current_project') and self.current_project:
                variant_name = self.current_project.active_variant
                if variant_name and self.config_manager.configuration:
                    variant_overrides = self.config_manager.configuration.variant_overrides.get(variant_name, {})

                # Calculate project template directory (project_dir/templates)
                if self.current_project_file:
                    project_dir = self.current_project_file.parent
                    project_template_dir = project_dir / "templates"
                    if not project_template_dir.exists():
                        logger.info(f"Project template directory not found at: {project_template_dir}")
                        project_template_dir = None
                    else:
                        logger.info(f"Using project template directory: {project_template_dir}")
            
            generator = CodeGenerator(
                self.module_def,
                self.config_manager.configuration,
                project_template_dir=project_template_dir,
                variant_overrides=variant_overrides,
                all_configurations=self._get_all_project_configurations()
            )
            
            # Pass parent output directory; generator.generate_all() will handle the ModuleName/ subdirectory
            generator.generate_all(Path(output_dir), variant=variant_name)
            
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
        """Generate code for all modules in project (Incremental & Parallel)"""
        if not self.current_project:
            return
        
        # Default output directory is project_path/generateCode
        project_dir = self.current_project.path.parent if self.current_project.path else Path.home()
        default_output = project_dir / "generateCode"
        
        # Ask user to confirm or change output directory
        # Use project_dir as base for dialog, but suggest generateCode
        output_dir = QFileDialog.getExistingDirectory(
            self,
            "选择代码生成输出目录",
            str(project_dir)
        )
        
        # If user cancels or selects project root, default to generateCode
        if not output_dir or Path(output_dir) == project_dir:
            output_dir = str(default_output)
        
        from ..generator.generator import CodeGenerator
        from PySide6.QtWidgets import QProgressDialog
        from PySide6.QtCore import Qt as QtCore_Qt, QObject, Signal, QRunnable, Slot
        
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)
        modules = list(self.current_project.module_managers.items())
        
        if not modules:
            QMessageBox.information(self, "No Modules", "Project has no modules to generate.")
            return

        # --- Worker Classes ---
        class GenSignals(QObject):
            finished = Signal(str, str, str) # module_name, status (GEN/SKIP/FAIL), message

        class GenWorker(QRunnable):
            def __init__(self, name, manager, out_path, variant_name=None, variant_overrides=None, project_template_dir=None, all_configs=None):
                super().__init__()
                self.name = name
                self.manager = manager
                self.out_path = out_path
                self.variant_name = variant_name
                self.variant_overrides = variant_overrides or {}
                self.project_template_dir = project_template_dir
                self.all_configs = all_configs
                self.signals = GenSignals()
                
            @Slot()
            def run(self):
                try:
                    import logging
                    logger = logging.getLogger(__name__)
                    logger.debug(f"Starting generation for: {self.name}")
                    
                    # Generate with variant overrides, project templates, and directory structure
                    generator = CodeGenerator(
                        self.manager.module_def, 
                        self.manager.configuration,
                        project_template_dir=self.project_template_dir,
                        variant_overrides=self.variant_overrides,
                        variant_name=self.variant_name,
                        all_configurations=self.all_configs
                    )
                    # Pass parent output path; generator.generate_all() will handle the ModuleName/ subdirectory
                    generated = generator.generate_all(self.out_path, force=False, variant=self.variant_name)
                    
                    status = "GEN" if generated else "SKIP"
                    self.signals.finished.emit(self.name, status, "")
                except Exception as e:
                    import traceback
                    traceback.print_exc()
                    self.signals.finished.emit(self.name, "FAIL", str(e))

        # --- Setup Progress ---
        self._gen_progress = QProgressDialog(
            "Initializing code generation...",
            "Cancel",
            0,
            len(modules),
            self
        )
        self._gen_progress.setWindowModality(QtCore_Qt.WindowModal)
        self._gen_progress.setMinimumDuration(0)
        self._gen_progress.setValue(0)
        
        # Stats tracking
        self._gen_stats = {
            'generated': [],
            'skipped': [],
            'failed': []
        }
        self._gen_processed = 0
        self._gen_total = len(modules)
        
        # --- Completion Handler ---
        def on_module_done(name, status, msg):
            # Capture reference at start to avoid race condition
            progress = self._gen_progress
            stats = self._gen_stats
            
            # Check if already cleaned up (race condition with multiple signals)
            if progress is None or stats is None:
                return
            if progress.wasCanceled():
                return
                
            self._gen_processed += 1
            
            # Update progress UI safely
            try:
                progress.setValue(self._gen_processed)
                progress.setLabelText(f"Processed {name} ({status})...")
            except RuntimeError:
                # Widget may have been deleted
                pass
            
            if status == "GEN":
                stats['generated'].append(name)
            elif status == "SKIP":
                stats['skipped'].append(name)
            else:
                stats['failed'].append((name, msg))
            
            # Check if all done
            if self._gen_processed >= self._gen_total:
                finalize_generation()

        def finalize_generation():
            # Guard against multiple calls
            if self._gen_stats is None:
                return
            
            # Show summary
            stats = self._gen_stats
            
            # Cleanup first to prevent re-entry
            self._gen_progress = None
            self._gen_stats = None
            self._gen_workers = None
            
            summary = "Code generation completed!\n\n"
            
            if stats['generated']:
                summary += f"✅ Generated: {len(stats['generated'])} module(s)\n"
            if stats['skipped']:
                summary += f"⏩ Skipped (Unchanged): {len(stats['skipped'])} module(s)\n"
            if stats['failed']:
                summary += f"❌ Failed: {len(stats['failed'])} module(s)\n"
                for m, err in stats['failed']:
                    summary += f"  - {m}: {err}\n"
                    
            summary += f"\nOutput: {output_dir}"
            
            if stats['failed']:
                QMessageBox.warning(self, "Generation Completed with Errors", summary)
            else:
                QMessageBox.information(self, "Generation Successful", summary)
                
            self.statusbar.showMessage(
                f"Generated: {len(stats['generated'])}, Skipped: {len(stats['skipped'])}, Failed: {len(stats['failed'])}",
                5000
            )

        # --- Start Workers ---
        # Get current variant info
        variant_name = self.current_project.active_variant if self.current_project else None
        
        # Calculate project template directory (project_dir/templates)
        project_template_dir = None
        if self.current_project and self.current_project.path:
            project_dir = self.current_project.path.parent
            project_template_dir = project_dir / "templates"
            if not project_template_dir.exists():
                logger.info(f"Project template directory not found at: {project_template_dir}")
                project_template_dir = None
            else:
                logger.info(f"Using project template directory: {project_template_dir}")
        
        # Keep references to prevent garbage collection
        self._gen_workers = []
        all_configs = self._get_all_project_configurations()
        
        for name, manager in modules:
            if not manager.configuration:
                # Should not happen if strictly managed, but handle safe
                self._gen_stats['skipped'].append(name + " (No Config)")
                self._gen_processed += 1
                continue
            
            # Get variant overrides for this module
            mod_variant_overrides = {}
            if variant_name and manager.configuration:
                mod_variant_overrides = manager.configuration.variant_overrides.get(variant_name, {})
                
            worker = GenWorker(
                name, manager, output_path, 
                variant_name=variant_name, 
                variant_overrides=mod_variant_overrides,
                project_template_dir=project_template_dir,
                all_configs=all_configs
            )
            worker.setAutoDelete(False)  # Prevent automatic deletion
            # Use QueuedConnection for cross-thread signal delivery
            worker.signals.finished.connect(on_module_done, QtCore_Qt.QueuedConnection)
            self._gen_workers.append(worker)  # Keep reference
            self.thread_pool.start(worker)
    
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
            if self.current_project:
                # Project mode: Index all modules
                self.search_widget.build_project_index(self.current_project)
            elif self.config_manager:
                # Single module mode
                self.search_widget.build_search_index(
                    self.module_def,
                    self.config_manager.configuration,
                    clear=True
                )
        else:
            self.search_widget.hide()
    
    def _on_search_result_selected(self, result_type: str, path: str):
        """Handle search result selection"""
        try:
            self.statusbar.showMessage(f"🔍 Navigating to: {path}", 3000)
            
            # Different handling based on result type
            if result_type == 'container_def':
                # For container definitions, navigate in tree
                self._navigate_to_definition(path)
            elif result_type == 'parameter_def':
                # For parameter definitions, navigate to its container definition
                container_path = '/'.join(path.split('/')[:-1]) if '/' in path else path
                self._navigate_to_definition(container_path)
            elif result_type == 'container':
                # For container instances, select in tree
                self._navigate_to_container(path)
            elif result_type in ['parameter', 'reference']:
                # For parameter/ref values, select parent container
                container_path = '/'.join(path.split('/')[:-1]) if '/' in path else path
                self._navigate_to_container(container_path)
            else:
                self.statusbar.showMessage(f"⚠️ Unhandled result type '{result_type}' for {path}", 5000)
                
        except Exception as e:
            import traceback
            error_msg = f"Navigation Error: {str(e)}\n{traceback.format_exc()}"
            print(error_msg)
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.warning(self, "Search Navigation Failed", f"An error occurred while navigating to:\n{path}\n\nError: {str(e)}")
    
    def _navigate_to_definition(self, path: str):
        """Navigate to a definition in tree view"""
        parts = path.split('/')
        if not parts:
            return
            
        module_name = parts[0]
        container_path = '/'.join(parts[1:])
        
        # Find correct module definition
        target_module_def = None
        if self.current_project and module_name in self.current_project.module_managers:
            target_module_def = self.current_project.module_managers[module_name].module_def
        elif self.module_def and self.module_def.short_name == module_name:
            target_module_def = self.module_def
            
        if not target_module_def:
            self.statusbar.showMessage(f"Could not find module definition for {module_name}", 3000)
            return

        container_def = target_module_def.get_container_def(container_path)
        if container_def:
            if self.tree_view.select_definition(container_def.definition_ref):
                self.statusbar.showMessage(f"✓ Navigated to definition: {container_path}", 3000)
            else:
                self.statusbar.showMessage(f"✗ Definition found in model but failed to locate in Tree View: {container_path}", 5000)
        else:
            self.statusbar.showMessage(f"✗ Definition not found in module '{module_name}': {container_path}", 5000)

    def _show_definition_info(self, result_type: str, path: str):
        """Show definition information in a dialog"""
        from PySide6.QtWidgets import QMessageBox
        
        parts = path.split('/')
        module_name = parts[0]
        
        # Find correct module definition
        target_module_def = None
        if self.current_project and module_name in self.current_project.module_managers:
            target_module_def = self.current_project.module_managers[module_name].module_def
        elif self.module_def and self.module_def.short_name == module_name:
            target_module_def = self.module_def
            
        if not target_module_def:
            self.statusbar.showMessage(f"Could not find module definition for {module_name}", 3000)
            return

        if result_type == 'container_def':
            # Path is Module/Path
            container_path = '/'.join(parts[1:])
            container_def = target_module_def.get_container_def(container_path)
            if container_def:
                info = f"Container: {container_def.short_name}\n"
                info += f"Description: {container_def.description or 'N/A'}\n"
                info += f"Multiplicity: {container_def.lower_multiplicity}..{container_def.upper_multiplicity}\n"
                info += f"Parameters: {len(container_def.parameters)}\n"
                info += f"Sub-containers: {len(container_def.sub_containers)}"
                QMessageBox.information(self, "Container Definition", info)
        elif result_type == 'parameter_def':
            # Path is Module/ContainerPath/Param
            container_path = '/'.join(parts[1:-1])
            param_name = parts[-1]
            container_def = target_module_def.get_container_def(container_path)
            if container_def and param_name in container_def.parameters:
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
        parts = path.split('/')
        if not parts:
            return
            
        module_name = parts[0]
        
        # Find correct module manager
        target_manager = None
        if self.current_project and module_name in self.current_project.module_managers:
            target_manager = self.current_project.module_managers[module_name]
        elif self.config_manager and self.config_manager.module_def.short_name == module_name:
            target_manager = self.config_manager
            
        if not target_manager:
            self.statusbar.showMessage(f"Could not find module {module_name}", 3000)
            return

        # Registry lookup needs leading slash prefix: /Module/ContainerPath
        full_path = f"/{path}"
        instance = target_manager.configuration.get_instance_by_path(full_path)
        
        if instance:
            if self.tree_view._select_instance(instance):
                self.statusbar.showMessage(f"✓ Navigated to: {path}", 3000)
            else:
                self.statusbar.showMessage(f"✗ Instance found in model but failed to locate in Tree View: {path}", 5000)
        else:
            self.statusbar.showMessage(f"✗ Container instance not found: {path}", 5000)
    
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
        if not self.current_project and (not self.config_manager or not self.module_def):
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
            
            # Show dialog
            self.dep_graph_dialog.show()
        else:
            self.dep_graph_dialog.raise_()
            self.dep_graph_dialog.activateWindow()
            if self.dep_graph_dialog.isHidden():
                self.dep_graph_dialog.show()

        # Always update graph data when showing
        if self.dep_graph_widget:
            if self.current_project:
                self.dep_graph_widget.build_graph_project(self.current_project)
            else:
                self.dep_graph_widget.build_graph(
                    self.module_def,
                    self.config_manager.configuration
                )

    
    def _update_dependency_graph_if_open(self):
        """Update dependency graph if the widget is open/visible"""
        if (hasattr(self, 'dep_graph_dialog') and 
            self.dep_graph_dialog is not None and 
            self.dep_graph_dialog.isVisible() and
            hasattr(self, 'dep_graph_widget') and 
            self.dep_graph_widget is not None):
            
            if self.current_project:
                self.dep_graph_widget.build_graph_project(self.current_project)
            elif self.module_def and self.config_manager:
                self.dep_graph_widget.build_graph(
                    self.module_def,
                    self.config_manager.configuration
                )

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
                    self.signals.result.emit((dependencies, str(self.output_path)))
                except Exception as e:
                    self.signals.error.emit(str(e))
        
        # Create worker with signals
        worker = DependencyWorker(analyzer, params, output_path, AIWorkerSignals())
        worker.signals.result.connect(self._on_dependency_analysis_done)
        worker.signals.error.connect(self._on_dependency_analysis_error)
        
        # Submit to thread pool
        self.thread_pool.start(worker)
    
    def _on_dependency_analysis_done(self, result: object):
        """Handle completed dependency analysis"""
        if isinstance(result, tuple):
            dependencies, output_path = result
            count = len(dependencies)
        else:
            # Fallback for string format (legacy)
            parts = str(result).split("|", 1)
            count = int(parts[0])
            output_path = parts[1]
            dependencies = []
        
        self.statusBar().showMessage(f"依赖分析完成，发现 {count} 条潜在规则", 5000)
        
        if not dependencies:
            QMessageBox.information(self, "分析完成", "未发现明显的跨模块依赖关系。")
            return

        # Use the new graphical review dialog
        from .dialogs.dependency_review_dialog import DependencyReviewDialog
        dialog = DependencyReviewDialog(dependencies, self)
        
        # If dialog is accepted, store the confirmed rules
        if dialog.exec() == QDialog.Accepted:
            confirmed_rules = dialog.confirmed_rules
            if self.current_project:
                self.current_project.dependency_rules = confirmed_rules
                
                # Regenerate markdown with confirmed status
                from ..core.ai.dependency_analyzer import DependencyAnalyzer
                analyzer = DependencyAnalyzer()
                
                # Update status for all dependencies based on confirmation
                confirmed_ids = {(r.get('source_param'), r.get('target_param')) for r in confirmed_rules}
                for dep in dependencies:
                    key = (dep.get('source_param'), dep.get('target_param'))
                    if key in confirmed_ids:
                        dep['status'] = 'confirmed'
                    else:
                        dep['status'] = 'rejected'
                
                # Regenerate the file
                analyzer.generate_markdown(dependencies, Path(output_path))
                
            QMessageBox.information(
                self, 
                "规则已应用", 
                f"已成功应用 {len(confirmed_rules)} 条确认的依赖规则。\n"
                f"已更新 {Path(output_path).name} 文件标记确认状态。"
            )
        
        # Optionally still offer to open the full report doc
        if output_path and Path(output_path).exists():
            reply = QMessageBox.question(
                self,
                "查看完整报告",
                f"分析报告已生成并包含详细原因建议。\n\n是否打开 {Path(output_path).name} 查阅原始报告？",
                QMessageBox.Yes | QMessageBox.No,
                QMessageBox.No
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
            self.config_manager = manager
            self.module_def = module_def
            
            # Update actions for the selected module
            self.save_value_action.setEnabled(True)
            self.save_value_as_action.setEnabled(True)
            self.validate_action.setEnabled(True)
            self.load_rules_action.setEnabled(True)
            self.generate_action.setEnabled(True)
            self.quick_config_action.setEnabled(True)
            self.show_dep_graph_action.setEnabled(True)
            self.load_recommended_action.setEnabled(True)
            
            self.value_file_label.setText(f"Config: {manager.configuration.short_name}")
        
        self.config_panel.clear()
        self._update_dependency_graph_if_open()
        
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
    
    def _on_parameter_changed(self, instance: EcucContainerValue, param_name: str, value: Any):
        """Handle parameter value change"""
        # Delegate to command handler
        self.handle_parameter_change(instance, param_name, value)
    
    def _on_instance_variant_changed(self, instance: EcucContainerValue):
        """Handle when an instance's assigned variant changes - refresh tree to update filtering"""
        # Refresh tree to show/hide the instance based on the current view variant
        self.tree_view.refresh()
        
        # Check if the instance is now assigned to a variant different from current view
        current_view_variant = self.current_project.active_variant if self.current_project else None
        
        if instance.variant is not None and instance.variant != current_view_variant:
            # Instance now belongs to a different variant - clear config panel to prevent accidental editing
            self.config_panel.clear()
            self.statusbar.showMessage(
                f"实例 '{instance.short_name}' 已归属到变体 '{instance.variant}'，当前视图为 '{current_view_variant}'，配置面板已清空", 
                5000
            )
        else:
            self.statusbar.showMessage(f"Instance '{instance.short_name}' variant updated, tree refreshed", 3000)
    
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
    
    def _show_user_manual(self):
        """Show user manual dialog"""
        from .dialogs.user_manual_dialog import UserManualDialog
        dialog = UserManualDialog(self)
        dialog.exec()
        
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
        self.recent_files_menu.clear()

        # Get recent files from settings
        recent_files = self.settings.value("recent_files", [])

        # Handle case where settings returns a string instead of list
        if isinstance(recent_files, str):
            recent_files = [recent_files] if recent_files else []

        if not recent_files:
            no_files_action = QAction("(No recent files)", self)
            no_files_action.setEnabled(False)
            self.recent_files_menu.addAction(no_files_action)
            return

        # Add recent files to menu (limit to max_recent_files)
        for file_path in recent_files[:self.max_recent_files]:
            if Path(file_path).exists():
                action = QAction(file_path, self)
                action.triggered.connect(lambda checked, path=file_path: self._open_recent_file(path))
                self.recent_files_menu.addAction(action)

        # Add separator and clear action if there are files
        if self.recent_files_menu.actions():
            self.recent_files_menu.addSeparator()
            clear_action = QAction("Clear Recent Files", self)
            clear_action.triggered.connect(self._clear_recent_files)
            self.recent_files_menu.addAction(clear_action)

    def _open_recent_file(self, file_path: str):
        """Open a file from recent files menu"""
        path = Path(file_path)
        if not path.exists():
            QMessageBox.warning(self, "File Not Found", f"The file no longer exists:\n{file_path}")
            self._remove_from_recent_files(file_path)
            return

        # Determine file type and open accordingly
        if path.suffix.lower() == '.dpa':
            self._load_project_at_path(path)
        elif path.suffix.lower() in ('.arxml', '.xdm'):
            self._load_def_file_at_path(path)

    def _load_def_file_at_path(self, path: Path):
        """Load a DEF file from a specific path (used by recent files)"""
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
                return

            # User chose to close project
            self.current_project = None
            self.current_project_file = None
            self.tree_view.clear()
            self.save_project_action.setEnabled(False)
            self.add_module_action.setEnabled(False)

        try:
            # Show loading cursor
            from PySide6.QtWidgets import QApplication
            from PySide6.QtCore import Qt as QtCore_Qt
            QApplication.setOverrideCursor(QtCore_Qt.WaitCursor)
            self.statusbar.showMessage("Loading DEF file...")

            # Parse DEF file
            self.module_def = self.def_parser.parse_module_def_file(path)
            self.current_def_file = path

            # Create configuration manager
            self.config_manager = ConfigurationManager(self.module_def)

            # Update UI
            self.tree_view.set_module_def(self.module_def, self.config_manager)
            self.def_file_label.setText(f"DEF: {self.module_def.short_name}")

            # Enable actions
            self.new_config_action.setEnabled(True)
            self.open_value_action.setEnabled(True)

            self.statusbar.showMessage(f"Loaded DEF: {self.module_def.short_name}", 5000)

            # Update mode label for single-module mode
            self.mode_label.setText(f"Module: {self.module_def.short_name}")

            # Update menu/toolbar states
            self._update_mode_actions()

            # Save to settings
            self.settings.setValue("last_def_file", str(path))

            # Add to recent files
            self._add_to_recent_files(str(path))

        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to load DEF file:\n{e}")
            self.statusbar.showMessage("Failed to load DEF file", 5000)
        finally:
            from PySide6.QtWidgets import QApplication
            QApplication.restoreOverrideCursor()

    def _add_to_recent_files(self, file_path: str):
        """Add a file to recent files list"""
        recent_files = self.settings.value("recent_files", [])

        if isinstance(recent_files, str):
            recent_files = [recent_files] if recent_files else []

        # Remove if already exists (to move to top)
        if file_path in recent_files:
            recent_files.remove(file_path)

        # Add to beginning
        recent_files.insert(0, file_path)

        # Limit to max_recent_files
        recent_files = recent_files[:self.max_recent_files]

        # Save and update menu
        self.settings.setValue("recent_files", recent_files)
        self._update_recent_files_menu()

    def _remove_from_recent_files(self, file_path: str):
        """Remove a file from recent files list"""
        recent_files = self.settings.value("recent_files", [])

        if isinstance(recent_files, str):
            recent_files = [recent_files] if recent_files else []

        if file_path in recent_files:
            recent_files.remove(file_path)
            self.settings.setValue("recent_files", recent_files)
            self._update_recent_files_menu()

    def _clear_recent_files(self):
        """Clear all recent files"""
        self.settings.setValue("recent_files", [])
        self._update_recent_files_menu()
        
    def _auto_load_last_project(self):
        """Automatically load the last project from settings"""
        last_path = self.settings.value("last_project_path")
        if last_path:
            path = Path(last_path)
            if path.exists():
                self.statusbar.showMessage(f"Auto-loading last project: {path.name}...")
                self._load_project_at_path(path)
    
    def _update_mode_actions(self):
        """Enable/disable actions based on current mode (project vs single-module)
        
        This ensures menu items and toolbar buttons are only active when appropriate:
        - Project mode: project-related actions enabled, single-module actions disabled
        - Single-module mode: single-module actions enabled, project actions disabled
        """
        is_project_mode = self.current_project is not None
        is_single_module_mode = (self.config_manager is not None) and not is_project_mode
        has_module_def = self.module_def is not None
        
        # === Project-only actions (already correctly managed, but ensure consistency) ===
        self.save_project_action.setEnabled(is_project_mode)
        self.project_properties_action.setEnabled(is_project_mode)
        self.manage_variants_action.setEnabled(is_project_mode)
        self.add_module_action.setEnabled(is_project_mode)
        self.load_recommended_action.setEnabled(is_project_mode)
        
        # === Single-module only actions ===
        self.save_value_action.setEnabled(is_single_module_mode)
        self.save_value_as_action.setEnabled(is_single_module_mode)
        self.open_value_action.setEnabled(is_single_module_mode and has_module_def)
        self.new_config_action.setEnabled(is_single_module_mode and has_module_def)
        
        # === Actions available in both modes (when config is available) ===
        has_any_config = is_project_mode or is_single_module_mode
        self.validate_action.setEnabled(has_any_config)
        self.generate_action.setEnabled(has_any_config)
        self.show_dep_graph_action.setEnabled(is_project_mode)  # Cross-module graph needs project
        self.quick_config_action.setEnabled(has_any_config)
        self.load_rules_action.setEnabled(has_any_config)

    
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
            
        # Cleanup background processes
        if hasattr(self, '_ai_help_process') and self._ai_help_process:
            if self._ai_help_process.state() != QProcess.NotRunning:
                self._ai_help_process.terminate()
                self._ai_help_process.waitForFinished(1000)
        
        # Save window geometry
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("windowState", self.saveState())
        event.accept()

    def _on_reference_jump_requested(self, target_path: str):
        """Navigate to the referenced container in the tree view"""
        if not target_path:
            return
        
        # Try to find the container in tree
        target_container = None
        
        # First try exact path
        if self.current_project:
            target_container = self.current_project.get_instance_by_path(target_path)
        elif self.config_manager:
            target_container = self.config_manager.configuration.get_instance_by_path(target_path)
        
        if target_container:
            # Find and select the item in the tree
            self.tree_view.select_container(target_container)
            self.statusbar.showMessage(f"Navigated to: {target_path}", 3000)
        else:
            self.statusbar.showMessage(f"Could not find: {target_path}", 3000)
    
    def _setup_impact_view(self):
        """Setup Impact Analysis dock widget"""
        self.impact_dock = QDockWidget("Impact Analysis", self)
        self.impact_dock.setObjectName("ImpactAnalysisDock")
        self.impact_dock.setAllowedAreas(Qt.RightDockWidgetArea | Qt.LeftDockWidgetArea | Qt.BottomDockWidgetArea)
        
        from .widgets.impact_view import ImpactView
        self.impact_view = ImpactView()
        self.impact_view.item_requested.connect(self._on_impact_item_requested)
        self.impact_dock.setWidget(self.impact_view)
        
        self.addDockWidget(Qt.RightDockWidgetArea, self.impact_dock)
        self.impact_dock.hide()
        
        # Add to view menu
        self.toggle_impact_action = self.impact_dock.toggleViewAction()
        self.toggle_impact_action.setText("Impact Analysis")
        self.toggle_impact_action.setShortcut(QKeySequence("Ctrl+Shift+I"))
        
        # Find view menu and add action
        menubar = self.menuBar()
        for action in menubar.actions():
            if action.text() == "View":
                action.menu().addAction(self.toggle_impact_action)
                break

    def _on_impact_item_requested(self, logical_path: str):
        """Navigate to an item from the impact view"""
        if '.' not in logical_path:
            return
            
        # For now, use search to find it
        if hasattr(self, 'search_widget'):
            self.search_widget.search_input.setText(logical_path.split('.')[-1])
            self.toggle_search_action.setChecked(True)
            self.search_widget.show()
            self.search_widget.focus_search()

    def _handle_check_impact(self, container_path: str, param_name: str):
        """Analyze and show impact of changing a parameter using the ImpactView dock"""
        if not self.config_manager or not self.current_project:
            return

        from ..core.analysis.impact_analyzer import ImpactAnalyzer
        
        # Initialize analyzer
        analyzer = ImpactAnalyzer()
        
        # Build structure from all modules in project
        for module_name, manager in self.current_project.module_managers.items():
            if manager.configuration:
                analyzer.build_from_configuration(manager.configuration, module_name)
                
        # Load AI rules
        if hasattr(self.current_project, 'dependency_rules') and self.current_project.dependency_rules:
            analyzer.load_dependencies(self.current_project.dependency_rules)
            
        # Determine source node path
        module_name = self.config_manager.module_def.short_name
        clean_cont_path = container_path.lstrip('/')
        source_node = f"{module_name}.{clean_cont_path}.{param_name}"
        
        # Analyze
        impacts = analyzer.analyze_impact(source_node)
        
        # Show in dock
        self.impact_view.display_impacts(source_node, impacts)
        self.impact_dock.show()
        self.impact_dock.raise_()

    def _show_reverse_references(self, container):
        """Show dialog listing all containers that reference this container
        
        Part of the Object Graph Context Builder feature: enables users to
        understand 'who depends on me?' for any container.
        """
        from PySide6.QtWidgets import QDialog, QVBoxLayout, QListWidget, QLabel, QDialogButtonBox, QListWidgetItem
        
        # Get reverse references
        refs = getattr(container, 'referenced_by', [])
        
        # Create dialog
        dialog = QDialog(self)
        dialog.setWindowTitle(f"🔍 谁引用了 {container.short_name}?")
        dialog.resize(600, 400)
        
        layout = QVBoxLayout(dialog)
        
        if refs:
            layout.addWidget(QLabel(f"<b>{container.short_name}</b> 被 {len(refs)} 个位置引用:"))
            list_widget = QListWidget()
            
            for ref_val in refs:
                # Find the source container holding this reference
                source = self._find_reference_source(ref_val)
                if source:
                    ref_name = ref_val.definition_ref.split('/')[-1] if ref_val.definition_ref else "Unknown"
                    item_text = f"📎 {source.get_path()} (via {ref_name})"
                    item = QListWidgetItem(item_text)
                    item.setData(Qt.UserRole, source.get_path())
                    list_widget.addItem(item)
                else:
                    list_widget.addItem(f"📎 (未知来源) via {ref_val.definition_ref}")
            
            # Enable click-to-navigate
            list_widget.itemDoubleClicked.connect(lambda item: self._navigate_to_path(item.data(Qt.UserRole)))
            
            layout.addWidget(list_widget)
            layout.addWidget(QLabel("<i>双击可跳转到引用位置</i>"))
        else:
            layout.addWidget(QLabel(f"<b>{container.short_name}</b> 没有被任何容器引用。"))
            layout.addWidget(QLabel("<i>提示: 确保项目已加载并解析了跨模块引用。</i>"))
            
        buttons = QDialogButtonBox(QDialogButtonBox.Ok)
        buttons.accepted.connect(dialog.accept)
        layout.addWidget(buttons)
        
        dialog.exec()
    
    def _find_reference_source(self, ref_val):
        """Find the container that holds a given reference value"""
        if not self.current_project:
            return None
        
        for manager in self.current_project.module_managers.values():
            result = self._search_for_ref_in_containers(ref_val, manager.configuration.containers)
            if result:
                return result
        return None
    
    def _search_for_ref_in_containers(self, ref_val, containers):
        """Recursively search for the container holding a reference"""
        for container in containers:
            for ref_name, stored_ref in container.reference_values.items():
                if stored_ref is ref_val:
                    return container
            # Recurse
            result = self._search_for_ref_in_containers(ref_val, container.sub_containers)
            if result:
                return result
        return None
    
    def _navigate_to_path(self, path: str):
        """Navigate to a container by path"""
        if path:
            self.tree_view.select_item_by_path(path)

    def _setup_problems_view(self):
        """Setup the centralized Problems View bottom dock"""
        self.problems_dock = QDockWidget("Problems", self)
        self.problems_dock.setObjectName("ProblemsDock")
        self.problems_dock.setAllowedAreas(Qt.BottomDockWidgetArea | Qt.TopDockWidgetArea)
        
        from .widgets.problems_view import ProblemsView
        self.problems_view = ProblemsView()
        self.problems_view.item_requested.connect(self._on_problems_item_requested)
        self.problems_dock.setWidget(self.problems_view)
        
        self.addDockWidget(Qt.BottomDockWidgetArea, self.problems_dock)
        self.problems_dock.hide()
        
        # Add to view menu
        self.toggle_problems_action = self.problems_dock.toggleViewAction()
        self.toggle_problems_action.setText("Problems")
        self.toggle_problems_action.setShortcut(QKeySequence("Ctrl+Shift+M"))
        
        menubar = self.menuBar()
        for action in menubar.actions():
            if action.text() == "View":
                action.menu().addAction(self.toggle_problems_action)
                break

    def _on_problems_item_requested(self, container_path: str, parameter_name: str):
        """Navigate to a problem source"""
        if not container_path:
            return
            
        # 1. Expand/select in tree
        self.tree_view.select_item_by_path(container_path)
        
        # 2. Highlight in config panel if it's a parameter
        if parameter_name:
            # Note: We rely on the selection triggering the load
            pass

