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
from ..core.config_manager import ConfigurationManager, ValidationError
from ..core.workspace_manager import WorkspaceManager, WorkspaceProject
from ..core.model.definition_model import EcucModuleDef, EcucContainerDef
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from .widgets.davinci_tree_view import DaVinciTreeView
from .widgets.davinci_config_panel import DaVinciConfigPanel
from .widgets.smart_search import SmartSearchWidget
from .widgets.dependency_graph import DependencyGraphWidget
from ..core.chip_constraint_service import ChipConstraintService
from ..generator.generator import CodeGenerator
from .async_workers import AIWorkerSignals
from .controllers.ai_assistant_controller import AiAssistantController
from .controllers.wizard_controller import WizardController
from .controllers.navigation_controller import NavigationController
from .controllers.dependency_graph_controller import DependencyGraphController
from .controllers.impact_problems_controller import ImpactProblemsController
from .controllers.generation_controller import GenerationController
from .controllers.validation_controller import ValidationController
from .controllers.project_controller import ProjectController
from .controllers.edit_controller import EditController


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
        
        # Model-editing command handlers (P2-6 phase 9).
        self.edit_controller = EditController(self)

        # Undo Stack
        self.undo_stack = QUndoStack(self)
        self.undo_stack.cleanChanged.connect(self.edit_controller._on_undo_clean_changed)
        self.undo_stack.indexChanged.connect(lambda idx: self.dep_graph_controller._update_dependency_graph_if_open())

        # Internal Clipboard
        self.clipboard_instance: Optional[EcucContainerValue] = None
        
        # Chip Constraint Service - manages chip-specific ECU constraints
        self.chip_constraint_service = ChipConstraintService(parent=self)
        self.chip_constraint_service.constraints_changed.connect(self._on_chip_constraints_changed)

        # AI assistant behaviour lives in a dedicated controller (P2-6 phase 1).
        self.ai_controller = AiAssistantController(self)

        # Wizard launch/completion lives in a dedicated controller (P2-6 phase 2).
        self.wizard_controller = WizardController(self)

        # Search-result navigation lives in a dedicated controller (P2-6 phase 3).
        self.nav_controller = NavigationController(self)

        # Dependency graph / analysis / validation (P2-6 phase 4).
        self.dep_graph_controller = DependencyGraphController(self)

        # Impact Analysis + Problems docks (P2-6 phase 5).
        self.impact_problems_controller = ImpactProblemsController(self)

        # Code generation (single module / project) (P2-6 phase 6).
        self.generation_controller = GenerationController(self)

        # Validation + custom rules (P2-6 phase 7).
        self.validation_controller = ValidationController(self)

        # Project I/O, session, recent files (P2-6 phase 8).
        self.project_controller = ProjectController(self)

        self._setup_ui()
        self._create_actions()
        self._create_menus()
        self._create_toolbars()
        self._create_statusbar()
        
        # Auto-load last project after a short delay to allow UI to show
        QTimer.singleShot(100, self.project_controller._auto_load_last_project)
        
        self.setWindowTitle("AUTOSAR DaVinci Configurator")
        self.resize(1400, 900)
        
        # Load last opened DEF file
        self.project_controller._load_last_session()
    
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
        self.search_widget.result_selected.connect(self.nav_controller._on_search_result_selected)
        self.search_widget.setMaximumHeight(200)
        self.search_widget.hide()  # Hidden by default
        layout.addWidget(self.search_widget)
        
        # Splitter for tree view and config panel
        splitter = QSplitter(Qt.Horizontal)
        
        # Left: Tree view
        self.tree_view = DaVinciTreeView()
        self.tree_view.chip_constraint_service = self.chip_constraint_service
        self.tree_view.instance_selected.connect(self._on_instance_selected)
        self.tree_view.def_selected.connect(self._on_def_selected)
        self.tree_view.module_selected.connect(self._on_module_selected)
        self.tree_view.create_instance_requested.connect(self.edit_controller.handle_create_container)
        self.tree_view.delete_instance_requested.connect(self.edit_controller.handle_delete_container)
        self.tree_view.delete_instances_requested.connect(self.edit_controller.handle_delete_containers_batch)
        self.tree_view.delete_module_requested.connect(self.edit_controller.handle_delete_module)
        self.tree_view.move_instance_requested.connect(self.edit_controller.handle_move_container)
        self.tree_view.rename_instance_requested.connect(self.edit_controller.handle_rename_container)
        self.tree_view.view_references_requested.connect(self.nav_controller._show_reverse_references)
        splitter.addWidget(self.tree_view)
        
        # Right: Config panel
        self.config_panel = DaVinciConfigPanel()
        self.config_panel.chip_constraint_service = self.chip_constraint_service
        self.config_panel.parameter_changed.connect(self._on_parameter_changed)
        self.config_panel.ai_help_requested.connect(self.ai_controller.on_help_requested)
        self.config_panel.check_impact_requested.connect(self.impact_problems_controller._handle_check_impact)
        self.config_panel.reference_jump_requested.connect(self.nav_controller._on_reference_jump_requested)
        self.config_panel.instance_variant_changed.connect(self._on_instance_variant_changed)
        splitter.addWidget(self.config_panel)
        
        # Set splitter proportions
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 2)
        
        layout.addWidget(splitter)
        
        # Dependency graph widget (in separate window)
        
        # AI Assistant (Dock Widget)
        self.ai_assistant_widget = None
        self.ai_assistant_dock = None
        
        # Initialize AI Assistant (logic lives in AiAssistantController)
        self.ai_controller.setup_dock()
        
        # Impact View (Dock Widget)
        self.impact_problems_controller._setup_impact_view()
        
        # Problems View (Bottom Dock)
        self.impact_problems_controller._setup_problems_view()

    def _create_actions(self):
        """Create actions"""
        # Project actions
        self.new_project_action = QAction("New Project...", self)
        self.new_project_action.setShortcut(QKeySequence("Ctrl+Shift+N"))
        self.new_project_action.setStatusTip("Create a new AUTOSAR project")
        self.new_project_action.triggered.connect(self.project_controller.new_project)
        
        self.open_project_action = QAction("Open Project...", self)
        self.open_project_action.setShortcut(QKeySequence("Ctrl+Shift+O"))
        self.open_project_action.setStatusTip("Open an existing project (.dpa file)")
        self.open_project_action.triggered.connect(self.project_controller.open_project)
        
        self.save_project_action = QAction("Save Project", self)
        self.save_project_action.setShortcut(QKeySequence("Ctrl+Shift+S"))
        self.save_project_action.setEnabled(False)
        self.save_project_action.triggered.connect(self.project_controller.save_project)
        
        self.project_properties_action = QAction("Project Properties...", self)
        self.project_properties_action.setEnabled(False)
        self.project_properties_action.triggered.connect(self.project_controller.show_project_properties)
        
        self.manage_variants_action = QAction("Manage Variants...", self)
        self.manage_variants_action.setEnabled(False)
        self.manage_variants_action.triggered.connect(self.project_controller.manage_variants)
        
        self.add_module_action = QAction("Add Module to Project...", self)
        self.add_module_action.setEnabled(False)
        self.add_module_action.triggered.connect(self.project_controller.add_module_to_project)
        
        self.load_recommended_action = QAction("Load Recommended Values...", self)
        self.load_recommended_action.setEnabled(False)
        self.load_recommended_action.triggered.connect(self.project_controller.load_recommended_values)

        self.import_eb_project_action = QAction("Import EB Tresos Project...", self)
        self.import_eb_project_action.setStatusTip("Batch import an EB Tresos project (auto-discover defines + EPC configs)")
        self.import_eb_project_action.triggered.connect(self.project_controller.import_eb_project)

        self.export_epc_action = QAction("Export EPC Files...", self)
        self.export_epc_action.setStatusTip("Export module configurations as EB Tresos-compatible .epc files")
        self.export_epc_action.setEnabled(False)
        self.export_epc_action.triggered.connect(self.project_controller.export_epc_files)

        # File actions
        # Open DEF removed - use Add Module within a project instead
        # self.open_def_action removed
        
        # Single module mode actions (Removed - use Projects instead)
        # self.new_config_action removed
        # self.open_value_action removed
        # save_value actions removed
        
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
        self.validate_action.triggered.connect(self.validation_controller.validate_configuration)

        self.load_rules_action = QAction("Load Custom Rules...", self)
        self.load_rules_action.setEnabled(False)
        self.load_rules_action.triggered.connect(self.validation_controller.load_custom_rules)

        # Copy/Paste Actions
        self.copy_action = QAction("Copy", self)
        self.copy_action.setShortcut(QKeySequence.Copy)
        self.copy_action.setStatusTip("Copy selected container")
        self.copy_action.triggered.connect(self.edit_controller.copy_container)
        
        self.paste_action = QAction("Paste", self)
        self.paste_action.setShortcut(QKeySequence.Paste)
        self.paste_action.setStatusTip("Paste container from clipboard")
        self.paste_action.triggered.connect(self.edit_controller.paste_container)
        
        # Undo/Redo actions
        self.undo_action = self.undo_stack.createUndoAction(self, "Undo")
        self.undo_action.setShortcut(QKeySequence.Undo)
        
        self.redo_action = self.undo_stack.createRedoAction(self, "Redo")
        self.redo_action.setShortcut(QKeySequence.Redo)
        
        # Generate actions
        self.generate_action = QAction("Generate Code", self)
        self.generate_action.setShortcut(QKeySequence("Ctrl+G"))
        self.generate_action.setEnabled(False)
        self.generate_action.triggered.connect(self.generation_controller.generate_code)
        
        # Wizard actions
        self.quick_config_action = QAction("Quick Configuration...", self)
        self.quick_config_action.setShortcut(QKeySequence("Ctrl+Q"))
        self.quick_config_action.setEnabled(False)
        self.quick_config_action.triggered.connect(self.wizard_controller.launch_quick_config_wizard)

        self.batch_create_action = QAction("Batch Create...", self)
        self.batch_create_action.setShortcut(QKeySequence("Ctrl+Shift+B"))
        self.batch_create_action.setEnabled(False)
        self.batch_create_action.triggered.connect(self.wizard_controller.launch_batch_create_wizard)

        self.hardware_mapping_action = QAction("Hardware Mapping...", self)
        self.hardware_mapping_action.setShortcut(QKeySequence("Ctrl+Shift+H"))
        self.hardware_mapping_action.setEnabled(False)
        self.hardware_mapping_action.triggered.connect(self.wizard_controller.launch_hardware_mapping_wizard)

        self.template_action = QAction("Apply Template...", self)
        self.template_action.setShortcut(QKeySequence("Ctrl+T"))
        self.template_action.setEnabled(False)
        self.template_action.triggered.connect(self.wizard_controller.launch_template_wizard)

        self.import_config_action = QAction("Import Configuration...", self)
        self.import_config_action.setShortcut(QKeySequence("Ctrl+I"))
        self.import_config_action.setEnabled(False)
        self.import_config_action.triggered.connect(self.wizard_controller.launch_import_wizard)

        # View actions
        self.toggle_search_action = QAction("Search...", self)
        self.toggle_search_action.setShortcut(QKeySequence.Find)  # Ctrl+F
        self.toggle_search_action.setStatusTip("Show/hide search panel (Ctrl+F)")
        self.toggle_search_action.setCheckable(True)
        self.toggle_search_action.triggered.connect(self.nav_controller.toggle_search)
        
        self.show_dep_graph_action = QAction("Dependency Graph", self)
        self.show_dep_graph_action.setShortcut(QKeySequence("Ctrl+D"))
        self.show_dep_graph_action.setEnabled(False)
        self.show_dep_graph_action.triggered.connect(self.dep_graph_controller.show_dependency_graph)

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
        file_menu.addAction(self.import_eb_project_action)
        file_menu.addAction(self.export_epc_action)
        # Open DEF removed - use Add Module
        file_menu.addSeparator()
        # Recent Files submenu
        self.recent_files_menu = file_menu.addMenu("Recent Files")
        self.project_controller._update_recent_files_menu()
        # Single module actions removed - use Project workflow
        file_menu.addSeparator()
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
        self.analyze_dependencies_action.triggered.connect(self.dep_graph_controller._analyze_cross_module_dependencies)
        analysis_menu.addAction(self.analyze_dependencies_action)
        
        self.validate_dependencies_action = QAction("✅ 验证跨模块依赖...", self)
        self.validate_dependencies_action.triggered.connect(self.dep_graph_controller._validate_cross_module_dependencies)
        analysis_menu.addAction(self.validate_dependencies_action)
        
        analysis_menu.addSeparator()
        analysis_menu.addAction(self.show_dep_graph_action)
        
        # Wizards menu
        wizards_menu = menubar.addMenu("Wizards")
        wizards_menu.addAction(self.quick_config_action)
        wizards_menu.addSeparator()
        wizards_menu.addAction(self.batch_create_action)
        wizards_menu.addAction(self.hardware_mapping_action)
        wizards_menu.addAction(self.template_action)
        wizards_menu.addSeparator()
        wizards_menu.addAction(self.import_config_action)

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
        toolbar.addAction(self.save_project_action)
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
        
        # Global variant selector (no more Base button - using pure variant model)
        variant_view_label = QLabel("Variant:")
        variant_view_label.setToolTip("Select the active variant for configuration and code generation.")
        toolbar.addWidget(variant_view_label)
        self.variant_selector = QComboBox()
        self.variant_selector.setMinimumWidth(150)
        self.variant_selector.addItem("Default")
        self.variant_selector.setEnabled(True)
        self.variant_selector.currentTextChanged.connect(self._on_variant_changed)
        toolbar.addWidget(self.variant_selector)
        
        # Quick manage button
        self.manage_variants_btn = QPushButton()
        self.manage_variants_btn.setIcon(self.style().standardIcon(QStyle.SP_FileDialogDetailedView))
        self.manage_variants_btn.setToolTip("Manage Variants...")
        self.manage_variants_btn.setFixedWidth(30)
        self.manage_variants_btn.clicked.connect(self.project_controller.manage_variants)
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
            self.statusbar.showMessage("对比参考: 默认配置", 2000)
    
    def _update_variant_selector(self):
        """Update the Variant selector dropdown with project variants"""
        self.variant_selector.blockSignals(True)
        self.variant_selector.clear()
        
        # Also update reference variant selector
        self.reference_variant_selector.blockSignals(True)
        self.reference_variant_selector.clear()
        self.reference_variant_selector.addItem("Default (默认)")
        
        if self.current_project and self.current_project.variants:
            # Always enable variant selector (no more has_base check)
            self.variant_selector.setEnabled(True)
            self.reference_variant_selector.setEnabled(True)
            self.manage_variants_btn.setEnabled(True)
            
            for variant in self.current_project.variants:
                self.variant_selector.addItem(variant)
                if variant != "Default":  # Already added as reference
                    self.reference_variant_selector.addItem(variant)
            
            # Select active variant
            active = self.current_project.active_variant or "Default"
            idx = self.variant_selector.findText(active)
            if idx >= 0:
                self.variant_selector.setCurrentIndex(idx)
            
            self.variant_label.setText(f"Variant: {active}")
        else:
            self.variant_selector.addItem("Default")
            self.variant_selector.setEnabled(True)
            self.reference_variant_selector.setEnabled(True)
            self.manage_variants_btn.setEnabled(True)
            self.variant_label.setText("Variant: Default")
            self.reference_variant_selector.setEnabled(False)
            self.variant_label.setText("Variant: None")
        
        self.variant_selector.blockSignals(False)
        self.reference_variant_selector.blockSignals(False)
    
    # Project operations
    
    def _on_instance_selected(self, instance: EcucContainerValue, container_def: EcucContainerDef, manager=None):
        """Handle instance selection in tree"""
        # Update active context if manager provided (Project Mode)
        if manager:
            self._update_active_context(manager)
        
        # Pass chip constraint service to config panel for dynamic constraints
        self.config_panel.chip_constraint_service = self.chip_constraint_service
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
            
            # Update actions for the selected module (use save_project)
            self.save_project_action.setEnabled(True)
            self.validate_action.setEnabled(True)
            self.load_rules_action.setEnabled(True)
            self.generate_action.setEnabled(True)
            self.quick_config_action.setEnabled(True)
            self.batch_create_action.setEnabled(True)
            self.template_action.setEnabled(True)
            self.import_config_action.setEnabled(True)
            self.show_dep_graph_action.setEnabled(True)
            self.load_recommended_action.setEnabled(True)
            self.export_epc_action.setEnabled(True)

            self.value_file_label.setText(f"Config: {manager.configuration.short_name}")
        
        self.config_panel.clear()
        self.dep_graph_controller._update_dependency_graph_if_open()
        
    def _update_active_context(self, manager):
        """Update active configuration context (for Project Mode)"""
        if self.config_manager != manager:
            self.config_manager = manager
            self.module_def = manager.module_def
            
            # Update status bar
            self.def_file_label.setText(f"DEF: {self.module_def.short_name}")
            self.value_file_label.setText(f"Config: {self.config_manager.configuration.short_name}")
            
            # Enable actions (use save_project)
            self.save_project_action.setEnabled(True)
            self.validate_action.setEnabled(True)
            self.load_rules_action.setEnabled(True)
            self.generate_action.setEnabled(True)
            self.quick_config_action.setEnabled(True)
            self.batch_create_action.setEnabled(True)
            self.template_action.setEnabled(True)
            self.import_config_action.setEnabled(True)
            self.show_dep_graph_action.setEnabled(True)
            self.export_epc_action.setEnabled(True)

    def _on_parameter_changed(self, instance: EcucContainerValue, param_name: str, value: Any):
        """Handle parameter value change"""
        # Delegate to command handler
        self.edit_controller.handle_parameter_change(instance, param_name, value)
        
        # Detect chip variant change (ResourceSubderivative in Resource module)
        if param_name == "ResourceSubderivative" and value:
            logger.info(f"Chip variant changed to: {value}")
            self.chip_constraint_service.set_chip(str(value))
            self.statusbar.showMessage(f"芯片型号已切换为: {value}，约束已重新加载", 5000)
    
    def _on_chip_constraints_changed(self, chip_name: str):
        """Handle chip constraints change - refresh UI to show new constraints"""
        logger.info(f"Chip constraints reloaded for: {chip_name}")

        # Update parser's expression resolver with new constraints
        constraints = self.chip_constraint_service.get_all_constraints()
        self.def_parser._resolver.set_constraints(constraints)

        # Update window title to show current chip
        self._update_window_title()
        
        # Show prominent status bar message
        self.statusbar.showMessage(f"🔧 芯片型号: {chip_name} | 约束已加载", 10000)
        
        # Refresh tree view for instance counts
        self.tree_view.refresh()
        
        # Refresh config panel if showing a container instance
        if hasattr(self.config_panel, 'current_instance') and self.config_panel.current_instance:
            # Update chip constraint service reference first
            self.config_panel.chip_constraint_service = self.chip_constraint_service
            # Re-display current instance to update constraint column
            self.config_panel.show_instance(
                self.config_panel.current_instance,
                self.config_panel.current_def,
                self.config_manager,
                self.current_project
            )
        
        # Update project's selected_chip field
        if self.current_project and chip_name:
            self.current_project.selected_chip = chip_name
            self._has_unsaved_changes = True

    
    def _get_resource_subderivative(self) -> Optional[str]:
        """Get the ResourceSubderivative parameter value from Resource module"""
        if not self.current_project:
            return None
        
        resource_manager = self.current_project.module_managers.get('Resource')
        if not resource_manager:
            return None
        
        # Look for ResourceGeneral container
        for container in resource_manager.configuration.containers:
            if container.short_name == 'ResourceGeneral' or 'General' in container.short_name:
                # Get ResourceSubderivative parameter
                param = container.parameter_values.get('ResourceSubderivative')
                if param and param.value:
                    return str(param.value)
        
        return None

    
    def _update_window_title(self):
        """Update window title to show project name and chip variant"""
        base_title = "AUTOSAR DaVinci Configurator"
        
        parts = [base_title]
        
        # Add project name if loaded
        if self.current_project:
            parts.append(f"- {self.current_project.name}")
        
        # Add chip variant if set
        chip_name = None
        if hasattr(self, 'chip_constraint_service') and self.chip_constraint_service:
            chip_name = self.chip_constraint_service.current_chip
        
        if chip_name:
            parts.append(f"[{chip_name}]")
        
        self.setWindowTitle(" ".join(parts))
    
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
    
    def _update_mode_actions(self):
        """Enable/disable actions based on whether a project is loaded"""
        is_project_mode = self.current_project is not None
        
        # === Project actions ===
        self.save_project_action.setEnabled(is_project_mode)
        self.project_properties_action.setEnabled(is_project_mode)
        self.manage_variants_action.setEnabled(is_project_mode)
        self.add_module_action.setEnabled(is_project_mode)
        self.load_recommended_action.setEnabled(is_project_mode)
        self.show_dep_graph_action.setEnabled(is_project_mode)
        
        # === Common configuration actions ===
        has_config = is_project_mode or (self.config_manager is not None)
        self.validate_action.setEnabled(has_config)
        self.generate_action.setEnabled(has_config)
        self.quick_config_action.setEnabled(has_config)
        self.batch_create_action.setEnabled(has_config)
        self.template_action.setEnabled(has_config)
        self.import_config_action.setEnabled(has_config)
        self.load_rules_action.setEnabled(has_config)
        # Hardware mapping needs a project
        self.hardware_mapping_action.setEnabled(is_project_mode)

    
    def closeEvent(self, event):
        """Handle window close event - check for unsaved changes"""
        unsaved_items = []
        
        single_module_unsaved = False
        # Check for unsaved changes
        if self.current_project:
            # Project mode: check all modules
            for module_name, manager in self.current_project.module_managers.items():
                if manager.configuration.is_modified:
                    unsaved_items.append(f"Module: {module_name}")
        elif self.config_manager and getattr(
                self.config_manager.configuration, 'is_modified', False):
            # Single-module mode: the lone config manager may have pending edits
            # that would otherwise be silently discarded on close.
            single_module_unsaved = True
            name = getattr(self.config_manager.module_def, 'short_name', 'configuration')
            unsaved_items.append(f"Module: {name}")

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
                if self.current_project:
                    self.project_controller.save_project()
                    # Check if all succeeded
                    still_unsaved = [
                        name for name, mgr in self.current_project.module_managers.items()
                        if mgr.configuration.is_modified
                    ]
                    if still_unsaved:
                        event.ignore()
                        return
                elif single_module_unsaved:
                    # Save the single-module configuration back to its source file.
                    target = getattr(self, 'current_value_file', None)
                    if target:
                        self.project_controller._save_configuration(Path(target))
                    if getattr(self.config_manager.configuration, 'is_modified', False):
                        # No known target path, or save failed — don't lose data.
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
            
        # Cleanup background processes (AI help subprocess lives on the controller)
        if hasattr(self, 'ai_controller') and self.ai_controller:
            self.ai_controller.cleanup()
        
        # Save window geometry
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("windowState", self.saveState())
        event.accept()

