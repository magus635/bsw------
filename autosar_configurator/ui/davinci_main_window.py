"""
DaVinci-style Main Window for ECUC Configuration
Dual-mode: loads DEF files and allows creating VALUE instances
"""
from PySide6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QSplitter, QMenuBar, QMenu, QToolBar, QStatusBar,
    QFileDialog, QMessageBox, QStyle, QLabel, QInputDialog, QLineEdit,
    QPushButton, QToolButton, QDialog, QStackedWidget
)
from PySide6.QtCore import Qt, Signal, QSettings, QRunnable, QThreadPool, QObject, Slot, QTimer
from PySide6.QtGui import QAction, QKeySequence, QUndoStack, QIcon
from PySide6.QtWidgets import QDockWidget
from pathlib import Path
from typing import Optional, Dict, Any, List, Tuple
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
from .widgets.navigation_bar import LeftNavigationBar
from .widgets.home_dashboard import HomeDashboardWidget
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


def _project_uses_ecu_variants(project) -> bool:
    """Return True when a project actively uses legacy project-level ECU variants."""
    if project is None:
        return False
    variants = getattr(project, "variants", None) or []
    if len(variants) > 1:
        return True
    if (getattr(project, "active_variant", None) or "Default") != "Default":
        return True
    for ov in (getattr(project, "unloaded_variant_overrides", None) or {}).values():
        if isinstance(ov, dict) and any(bool(v) for k, v in ov.items() if k != "Default"):
            return True

    def _has_container_variant(containers) -> bool:
        for c in containers or ():
            if getattr(c, "variant", None) not in (None, "", "Default"):
                return True
            if _has_container_variant(getattr(c, "sub_containers", None)):
                return True
        return False

    for mgr in (getattr(project, "module_managers", None) or {}).values():
        cfg = getattr(mgr, "configuration", None)
        if cfg is None:
            continue
        ov_map = getattr(cfg, "variant_overrides", None) or {}
        if any(bool(v) for k, v in ov_map.items() if k != "Default"):
            return True
        if _has_container_variant(getattr(cfg, "containers", None)):
            return True
    return False


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

        # Navigation & Home dashboard tracking
        self._nav_last_project: Optional[WorkspaceProject] = None
        self._validation_counts: Optional[Tuple[int, int]] = None

        self._setup_ui()
        self._create_actions()
        self._create_menus()
        self._create_toolbars()
        self._create_statusbar()
        self._update_mode_actions()
        
        # Auto-load last project after a short delay to allow UI to show
        QTimer.singleShot(100, self.project_controller._auto_load_last_project)
        
        self.setWindowTitle("AUTOSAR DaVinci Configurator")
        self.resize(1400, 900)
        
        # Load last opened DEF file
        self.project_controller._load_last_session()
    
    def _setup_ui(self):
        """Setup the UI layout"""
        # Central widget: left functional navigation rail + workspace stack (Home / Basic Editor)
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        central_layout = QHBoxLayout(central_widget)
        central_layout.setContentsMargins(0, 0, 0, 0)
        central_layout.setSpacing(0)

        self.nav_bar = LeftNavigationBar(self)
        self.nav_bar.page_selected.connect(self._on_nav_page_selected)
        self.nav_bar.action_triggered.connect(self._on_nav_action_triggered)
        central_layout.addWidget(self.nav_bar)

        self.workspace_stack = QStackedWidget(self)
        central_layout.addWidget(self.workspace_stack, 1)

        # Page 0: Home dashboard
        self.home_dashboard = HomeDashboardWidget(self)
        self.home_dashboard.new_project_requested.connect(self.project_controller.new_project)
        self.home_dashboard.open_project_requested.connect(self.project_controller.open_project)
        self.home_dashboard.import_davinci_requested.connect(self.project_controller.import_davinci_project)
        self.home_dashboard.import_eb_requested.connect(self.project_controller.import_eb_project)
        self.home_dashboard.recent_file_requested.connect(self.project_controller._open_recent_file)
        self.home_dashboard.open_basic_editor_requested.connect(self.show_basic_editor)
        self.home_dashboard.module_open_requested.connect(self._open_module_from_home)
        self.home_dashboard.add_or_integrate_module_requested.connect(self._add_or_integrate_from_home)
        self.home_dashboard.communication_workbench_requested.connect(self._launch_communication_workbench)
        self.home_dashboard.rte_workbench_requested.connect(self._launch_rte_schm_workbench)
        self.home_dashboard.memmap_requested.connect(self._launch_memory_map)
        self.home_dashboard.hw_mapping_requested.connect(self.wizard_controller.launch_hardware_mapping_wizard)
        self.home_dashboard.chip_designer_requested.connect(self._launch_chip_definition_designer)
        self.home_dashboard.validate_requested.connect(self.validation_controller.validate_configuration)
        self.home_dashboard.dep_graph_requested.connect(self.dep_graph_controller.show_dependency_graph)
        self.home_dashboard.generate_requested.connect(self.generation_controller.generate_code)
        self.home_dashboard.project_properties_requested.connect(self.project_controller.show_project_properties)
        self.workspace_stack.addWidget(self.home_dashboard)

        # Page 1: Basic Editor (SmartSearch + Module Tree / Config Panel splitter)
        self.basic_editor_page = QWidget(self)
        layout = QVBoxLayout(self.basic_editor_page)
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
        self.tree_view.switch_module_variant_requested.connect(self.project_controller.switch_module_variant)
        self.tree_view.move_instance_requested.connect(self.edit_controller.handle_move_container)
        self.tree_view.rename_instance_requested.connect(self.edit_controller.handle_rename_container)
        self.tree_view.view_references_requested.connect(self.nav_controller._show_reverse_references)
        self.tree_view.change_module_config_variant_requested.connect(self._on_tree_module_config_variant_requested)
        self.tree_view.open_communication_workbench_requested.connect(self._launch_communication_workbench)
        self.tree_view.open_rte_workbench_requested.connect(self._launch_rte_schm_workbench)
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
        self.workspace_stack.addWidget(self.basic_editor_page)

        # Default to Home on startup until a project is opened/created
        self.workspace_stack.setCurrentWidget(self.home_dashboard)
        self.nav_bar.set_active_page("home")
        
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
        self.manage_variants_action.setVisible(False)
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

        self.import_davinci_project_action = QAction("Import from DaVinci Project...", self)
        self.import_davinci_project_action.setStatusTip("Import BSW modules and MCAL resources from a DaVinci .dpa project")
        self.import_davinci_project_action.triggered.connect(self.project_controller.import_davinci_project)

        self.integrate_modules_action = QAction("Integrate Modules...", self)
        self.integrate_modules_action.setEnabled(False)
        self.integrate_modules_action.setStatusTip("Add BSW modules from libraries with baseline merge")
        self.integrate_modules_action.triggered.connect(self.project_controller.integrate_modules)

        self.restore_deleted_action = QAction("Restore Deleted Module...", self)
        self.restore_deleted_action.setEnabled(False)
        self.restore_deleted_action.setStatusTip("Restore a previously deleted module configuration from .history/deleted/")
        self.restore_deleted_action.triggered.connect(self.project_controller.restore_deleted_module)

        self.upgrade_project_action = QAction("Upgrade Project Structure...", self)
        self.upgrade_project_action.setEnabled(False)
        self.upgrade_project_action.setStatusTip("Upgrade a legacy project structure (format <= 7) to Format 8")
        self.upgrade_project_action.triggered.connect(self.project_controller.upgrade_project_structure)

        self.import_value_action = QAction("Import Value File...", self)
        self.import_value_action.setStatusTip("Replace the current module's configuration with an EB value file (.epc/.arxml/.xdm)")
        self.import_value_action.setEnabled(False)
        self.import_value_action.triggered.connect(self.project_controller.import_value_file)

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

        self.import_config_action = QAction("Import from Excel / CSV / DBC...", self)
        self.import_config_action.setShortcut(QKeySequence("Ctrl+I"))
        self.import_config_action.setStatusTip("Batch import configuration data from Excel, CSV, or CAN DBC file")
        self.import_config_action.setEnabled(False)
        self.import_config_action.triggered.connect(self.wizard_controller.launch_import_wizard)

        self.chip_designer_action = QAction("Chip Definition Designer...", self)
        self.chip_designer_action.setStatusTip("Open Chip Definition Designer to author, edit, or import MCU hardware definitions")
        self.chip_designer_action.triggered.connect(self._launch_chip_definition_designer)

        self.chip_repair_action = QAction("修复芯片...", self)
        self.chip_repair_action.setStatusTip("按厂商数据和插件所需键修复、补充芯片库中已有的芯片，并处理待确认项")
        self.chip_repair_action.triggered.connect(lambda: self._launch_chip_repair_wizard())

        self.chip_scan_action = QAction("芯片依赖扫描...", self)
        self.chip_scan_action.setStatusTip("列出依赖具体芯片的判断、默认分支、写死数值和资源覆盖，作为新增芯片的检查清单")
        self.chip_scan_action.triggered.connect(self._launch_chip_dependency_scan)

        self.memmap_action = QAction("内存映射...", self)
        self.memmap_action.setStatusTip("扫描段声明、MemMap 头映射和链接文件：在“诊断”页签看问题，在“布局”页签按物理区域或模块看段放在哪里（只读）")
        self.memmap_action.triggered.connect(self._launch_memory_map)

        self.communication_workbench_action = QAction("通信配置工作台...", self)
        self.communication_workbench_action.setStatusTip(
            "统一查看与编辑 CAN 通道、报文、信号位域、PduR 路由及从 DBC 一键派生通信栈"
        )
        self.communication_workbench_action.setEnabled(False)
        self.communication_workbench_action.triggered.connect(self._launch_communication_workbench)

        self.rte_workbench_action = QAction("RTE / SchM 工作台...", self)
        self.rte_workbench_action.setStatusTip("图形化配置 BSW 实例、SchM 临界区保护、Task 调度映射并预览/生成 RTE 与 SchM 头文件")
        self.rte_workbench_action.setEnabled(False)
        self.rte_workbench_action.triggered.connect(self._launch_rte_schm_workbench)

        # View actions
        self.toggle_nav_bar_action = QAction("Navigation Bar", self)
        self.toggle_nav_bar_action.setCheckable(True)
        self.toggle_nav_bar_action.setChecked(True)
        self.toggle_nav_bar_action.setStatusTip("Show/hide left functional navigation bar")
        self.toggle_nav_bar_action.toggled.connect(lambda visible: self.nav_bar.setVisible(visible))

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
        file_menu.addAction(self.integrate_modules_action)
        file_menu.addAction(self.restore_deleted_action)
        file_menu.addAction(self.load_recommended_action)
        file_menu.addAction(self.upgrade_project_action)
        file_menu.addSeparator()

        # Import submenu under File
        self.import_menu = file_menu.addMenu("Import")
        self.import_menu.addAction(self.import_eb_project_action)
        self.import_menu.addAction(self.import_davinci_project_action)
        self.import_menu.addAction(self.import_value_action)
        self.import_menu.addSeparator()
        self.import_menu.addAction(self.import_config_action)

        # Export submenu under File
        self.export_menu = file_menu.addMenu("Export")
        self.export_menu.addAction(self.export_epc_action)

        file_menu.addSeparator()
        # Recent Files submenu
        self.recent_files_menu = file_menu.addMenu("Recent Files")
        self.project_controller._update_recent_files_menu()
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
        view_menu.addAction(self.toggle_nav_bar_action)
        view_menu.addSeparator()
        view_menu.addAction(self.toggle_search_action)
        view_menu.addAction(self.show_dep_graph_action)
        view_menu.addSeparator()
        view_menu.addAction(self.toggle_ai_action)
        
        # Generate menu
        gen_menu = menubar.addMenu("Generate")
        gen_menu.addAction(self.generate_action)
        gen_menu.addSeparator()
        gen_menu.addAction(self.rte_workbench_action)
        
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

        # Tools menu
        tools_menu = menubar.addMenu("Tools")
        tools_menu.addAction(self.chip_designer_action)
        tools_menu.addAction(self.chip_repair_action)
        tools_menu.addAction(self.chip_scan_action)
        tools_menu.addAction(self.memmap_action)
        tools_menu.addAction(self.communication_workbench_action)
        tools_menu.addAction(self.rte_workbench_action)
        tools_menu.addAction(self.hardware_mapping_action)

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
        
        # Legacy project-variant controls are kept hidden for backward compatibility
        variant_view_label = QLabel("Variant:")
        variant_view_label.setToolTip("Select the active variant for configuration and code generation.")
        v_lbl_act = toolbar.addWidget(variant_view_label)
        v_lbl_act.setVisible(False)
        self.variant_selector = QComboBox()
        self.variant_selector.setMinimumWidth(150)
        self.variant_selector.addItem("Default")
        self.variant_selector.setEnabled(True)
        self.variant_selector.currentTextChanged.connect(self._on_variant_changed)
        v_sel_act = toolbar.addWidget(self.variant_selector)
        v_sel_act.setVisible(False)
        
        # Quick manage button
        self.manage_variants_btn = QPushButton()
        self.manage_variants_btn.setIcon(self.style().standardIcon(QStyle.SP_FileDialogDetailedView))
        self.manage_variants_btn.setToolTip("Manage Variants...")
        self.manage_variants_btn.setFixedWidth(30)
        self.manage_variants_btn.clicked.connect(self.project_controller.manage_variants)
        self.manage_variants_btn.setEnabled(False)
        v_btn_act = toolbar.addWidget(self.manage_variants_btn)
        v_btn_act.setVisible(False)
        
        # Reference variant selector for comparison
        vs_act = toolbar.addWidget(QLabel(" vs "))
        vs_act.setVisible(False)
        self.reference_variant_selector = QComboBox()
        self.reference_variant_selector.setMinimumWidth(120)
        self.reference_variant_selector.addItem("Base (基础)")
        self.reference_variant_selector.setToolTip("选择参考变体进行对比 (高亮显示差异)")
        self.reference_variant_selector.setEnabled(False)
        self.reference_variant_selector.currentTextChanged.connect(self._on_reference_variant_changed)
        ref_sel_act = toolbar.addWidget(self.reference_variant_selector)
        ref_sel_act.setVisible(False)
        self._variant_toolbar_actions = [v_lbl_act, v_sel_act, v_btn_act, vs_act, ref_sel_act]
        
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
        
        # Variant indicator (hidden with legacy project-variant UI)
        self.variant_label = QLabel("Variant: None")
        self.variant_label.setStyleSheet("QLabel { padding: 2px 10px; }")
        self.statusbar.addPermanentWidget(self.variant_label)
        self.variant_label.setVisible(False)
        
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
        
        # Set reference variant on config panel (None = Base / Default)
        ref_variant = (
            None
            if reference_name in ("Default (默认)", "Base (基础)", "Default", "")
            else reference_name
        )
        
        if hasattr(self, 'config_panel') and self.config_panel:
            self.config_panel.reference_variant = ref_variant
            self.config_panel.refresh()
        
        if ref_variant:
            self.statusbar.showMessage(f"对比参考变体: {ref_variant}", 2000)
        else:
            self.statusbar.showMessage("对比参考: 默认配置", 2000)
    
    def _update_variant_selector(self):
        """Update the Variant selector dropdown with project variants"""
        show_variants = _project_uses_ecu_variants(self.current_project)
        for act in getattr(self, "_variant_toolbar_actions", ()):
            act.setVisible(show_variants)
        if hasattr(self, "variant_label") and self.variant_label is not None:
            self.variant_label.setVisible(show_variants)

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
            if hasattr(self, "tree_view") and self.tree_view is not None:
                self.tree_view.set_active_variant(active)
        else:
            self.variant_selector.addItem("Default")
            self.variant_selector.setEnabled(False)
            self.reference_variant_selector.setEnabled(False)
            self.manage_variants_btn.setEnabled(False)
            self.variant_label.setText("Variant: None")
            if hasattr(self, "tree_view") and self.tree_view is not None:
                self.tree_view.set_active_variant(None)
        
        self.variant_selector.blockSignals(False)
        self.reference_variant_selector.blockSignals(False)
    
    # Project operations
    
    def _on_instance_selected(self, instance: EcucContainerValue, container_def: EcucContainerDef, manager=None):
        """Handle instance selection in tree"""
        self.show_basic_editor()
        # Update active context if manager provided (Project Mode)
        if manager:
            self._update_active_context(manager)
        
        # Pass chip constraint service to config panel for dynamic constraints
        self.config_panel.chip_constraint_service = self.chip_constraint_service
        self.config_panel.show_instance(instance, container_def, self.config_manager, self.current_project)
    
    def _on_def_selected(self, container_def: EcucContainerDef, manager=None):
        """Handle definition node selection in tree"""
        self.show_basic_editor()
        # Update active context if manager provided (Project Mode)
        if manager:
            self._update_active_context(manager)
            
        self.config_panel.show_definition(container_def)
        
    def _on_module_selected(self, module_def: EcucModuleDef, manager=None):
        """Handle module node selection in tree"""
        self.show_basic_editor()
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
            self.import_value_action.setEnabled(True)
            self.export_epc_action.setEnabled(True)
            self._sync_nav_bar_states()

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
            self.import_value_action.setEnabled(True)
            self.export_epc_action.setEnabled(True)
            self._sync_nav_bar_states()

    def _on_parameter_changed(self, instance: EcucContainerValue, param_name: str, value: Any):
        """Handle parameter value change"""
        # Delegate to command handler
        # The project's chip is changed only in Project Properties
        # (ProjectController.apply_project_chip); chip selector parameters are read-only
        self.edit_controller.handle_parameter_change(instance, param_name, value)

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
        
        self._refresh_config_views()

    def _refresh_config_views(self):
        """Redisplay the tree and the shown container instance (values, constraints)."""
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
        self.refresh_home_dashboard()

    
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
        from ..core.config_manager import PreLockedError
        from .commands import SetContainerVariantCommand
        from .controllers.edit_controller import _report_pre_locked

        panel = getattr(self, "config_panel", None)
        consume = getattr(panel, "_consume_pending_instance_variant_undo", None)
        pending = consume(instance) if callable(consume) else None
        mgr = self.edit_controller._resolve_config_manager_for_instance(instance)
        if pending is not None:
            old_var, new_var = pending
            try:
                cmd = SetContainerVariantCommand(
                    mgr, instance, new_var, old_variant=old_var, has_old_variant=True
                )
            except PreLockedError as exc:
                instance.variant = old_var
                if (
                    panel is not None
                    and getattr(panel, "current_instance", None) is instance
                    and hasattr(panel, "_update_variant_selector")
                ):
                    panel._update_variant_selector(instance)
                _report_pre_locked(self, exc)
                return
            if hasattr(self, "undo_stack") and self.undo_stack is not None:
                self.undo_stack.push(cmd)
        elif mgr is not None and hasattr(mgr, "check_editable"):
            try:
                mgr.check_editable(instance)
            except PreLockedError as exc:
                _report_pre_locked(self, exc)
                return
        self._has_unsaved_changes = True
        if hasattr(self, "_update_window_title"):
            self._update_window_title()

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

    def _on_tree_module_config_variant_requested(self, module_name: str, new_variant: str):
        """Handle change of a module's IMPLEMENTATION-CONFIG-VARIANT from the tree context menu."""
        from .commands import SetModuleConfigVariantCommand
        from ..core.model.configuration_model import normalize_config_variant

        mgr = None
        if self.current_project and hasattr(self.current_project, "module_managers"):
            mgr = self.current_project.module_managers.get(module_name)
        elif self.config_manager and getattr(getattr(self.config_manager, "module_def", None), "short_name", None) == module_name:
            mgr = self.config_manager
        if mgr is None or getattr(mgr, "configuration", None) is None:
            return
        cfg = mgr.configuration
        new_icv = normalize_config_variant(new_variant)
        old_icv = normalize_config_variant(getattr(cfg, "implementation_config_variant", None))
        if old_icv == new_icv:
            return
        cmd = SetModuleConfigVariantCommand(mgr, cfg, new_icv, old_variant=old_icv)
        if hasattr(self, "undo_stack") and self.undo_stack is not None:
            self.undo_stack.push(cmd)
        else:
            cmd.redo()
        if self.current_project:
            self.current_project.is_modified = True
        self._has_unsaved_changes = True
        update_title = getattr(self, "_update_window_title", None)
        if callable(update_title):
            update_title()
        self.tree_view.refresh()
        if hasattr(self, "config_panel") and self.config_panel and self.config_panel.current_instance:
            self.config_panel.refresh()
        self.statusbar.showMessage(
            f"Module '{module_name}' IMPLEMENTATION-CONFIG-VARIANT → {new_icv}",
            3000,
        )
    
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
        self.integrate_modules_action.setEnabled(is_project_mode)
        self.restore_deleted_action.setEnabled(
            is_project_mode and getattr(self.current_project, "format_version", 0) >= 8
        )
        self.upgrade_project_action.setEnabled(
            is_project_mode and getattr(self.current_project, "format_version", 0) < 8
        )
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
        # Hardware mapping, Communication and RTE/SchM workbenches need a project
        self.hardware_mapping_action.setEnabled(is_project_mode)
        self.communication_workbench_action.setEnabled(is_project_mode)
        self.rte_workbench_action.setEnabled(is_project_mode)

        self._sync_nav_bar_states()

        # A1 transition: Home by default when idle; Basic Editor on newly loaded/created project
        last_proj = getattr(self, "_nav_last_project", None)
        if self.current_project is not last_proj:
            self._nav_last_project = self.current_project
            self._validation_counts = None
            if hasattr(self, "nav_bar") and self.nav_bar is not None:
                self.nav_bar.set_item_badge("validate", "")
            if self.current_project is not None:
                self.show_basic_editor()
            elif self.config_manager is None and last_proj is not None:
                self.show_home()

        self.refresh_home_dashboard()

    def _sync_nav_bar_states(self):
        """Synchronize left navigation bar button enabled states with main actions."""
        if not hasattr(self, "nav_bar") or self.nav_bar is None:
            return
        is_project_mode = self.current_project is not None
        has_config = is_project_mode or (self.config_manager is not None)
        self.nav_bar.set_item_enabled("communication", is_project_mode)
        self.nav_bar.set_item_enabled("rte_workbench", is_project_mode)
        self.nav_bar.set_item_enabled("memmap", is_project_mode)
        self.nav_bar.set_item_enabled("hw_mapping", is_project_mode)
        self.nav_bar.set_item_enabled("settings", is_project_mode)
        self.nav_bar.set_item_enabled("validate", has_config or self.validate_action.isEnabled())
        self.nav_bar.set_item_enabled(
            "dep_graph", is_project_mode or has_config or self.show_dep_graph_action.isEnabled()
        )
        self.nav_bar.set_item_enabled("generate", has_config or self.generate_action.isEnabled())

    def show_home(self):
        """Switch central workspace stack to the Home dashboard."""
        if not hasattr(self, "workspace_stack") or not hasattr(self, "home_dashboard"):
            return
        self.workspace_stack.setCurrentWidget(self.home_dashboard)
        if hasattr(self, "nav_bar") and self.nav_bar is not None:
            self.nav_bar.set_active_page("home")
        self.refresh_home_dashboard()

    def show_basic_editor(self):
        """Switch central workspace stack to Basic Editor (tree + config panel)."""
        if not hasattr(self, "workspace_stack") or not hasattr(self, "basic_editor_page"):
            return
        self.workspace_stack.setCurrentWidget(self.basic_editor_page)
        if hasattr(self, "nav_bar") and self.nav_bar is not None:
            self.nav_bar.set_active_page("basic_editor")

    def _on_nav_page_selected(self, page_id: str):
        if page_id == "home":
            self.show_home()
        elif page_id == "basic_editor":
            self.show_basic_editor()

    def _on_nav_action_triggered(self, action_id: str):
        dispatch = {
            "communication": self._launch_communication_workbench,
            "rte_workbench": self._launch_rte_schm_workbench,
            "memmap": self._launch_memory_map,
            "hw_mapping": self.wizard_controller.launch_hardware_mapping_wizard,
            "validate": self.validation_controller.validate_configuration,
            "dep_graph": self.dep_graph_controller.show_dependency_graph,
            "generate": self.generation_controller.generate_code,
            "settings": self.project_controller.show_project_properties,
            "help": self._show_user_manual,
        }
        handler = dispatch.get(action_id)
        if handler is not None:
            handler()

    def _open_module_from_home(self, module_name: str):
        self.show_basic_editor()
        if hasattr(self, "tree_view") and self.tree_view is not None:
            self.tree_view.select_module(module_name)

    def _add_or_integrate_from_home(self):
        if (
            self.current_project is not None
            and getattr(self.current_project, "format_version", 0) >= 8
            and hasattr(self, "integrate_modules_action")
            and self.integrate_modules_action.isEnabled()
        ):
            self.project_controller.integrate_modules()
        else:
            self.project_controller.add_module_to_project()

    def refresh_home_dashboard(self):
        """Refresh the Home dashboard using in-memory project state and cached recent files."""
        if not hasattr(self, "home_dashboard") or self.home_dashboard is None:
            return
        raw_recent = self.settings.value("recent_files", []) if hasattr(self, "settings") else []
        if isinstance(raw_recent, str):
            raw_recent = [raw_recent] if raw_recent else []
        existing_recent = [p for p in (raw_recent or []) if Path(p).exists()]
        chip_name = None
        if hasattr(self, "chip_constraint_service") and self.chip_constraint_service:
            chip_name = self.chip_constraint_service.current_chip
        self.home_dashboard.refresh(
            self.current_project,
            recent_files=existing_recent,
            chip_name=chip_name,
            validation_summary=getattr(self, "_validation_counts", None),
            has_unsaved=bool(getattr(self, "_has_unsaved_changes", False)),
        )

    def update_validation_badge(self, error_count: int, warning_count: int):
        """Update validation badge on the navigation rail and Home summary."""
        self._validation_counts = (error_count, warning_count)
        if hasattr(self, "nav_bar") and self.nav_bar is not None:
            if error_count > 0:
                self.nav_bar.set_item_badge("validate", str(error_count), color="#b00020")
            elif warning_count > 0:
                self.nav_bar.set_item_badge("validate", f"{warning_count}W", color="#a65e00")
            else:
                self.nav_bar.set_item_badge("validate", "")
        self.refresh_home_dashboard()

    def _launch_chip_definition_designer(self):
        """Open Chip Definition Designer dialog"""
        from .dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog
        initial_chip = None
        if hasattr(self, 'chip_constraint_service') and self.chip_constraint_service:
            initial_chip = self.chip_constraint_service.current_chip

        from ..core.hardware.chip_database import get_default_chip_database
        # The library the project resolves its chip from, so the designer edits what the project reads
        database = getattr(self.current_project, 'chip_database', None) or get_default_chip_database()
        dialog = ChipDefinitionDesignerDialog(chip_database=database, initial_chip=initial_chip,
                                              parent=self, project=self.current_project)
        dialog.chip_saved.connect(self._on_designer_chip_saved)
        dialog.exec()

    def _launch_chip_repair_wizard(self, chip_name=None):
        """Open the chip repair wizard, preselecting the project's chip."""
        from ..core.hardware.chip_database import get_default_chip_database
        from .wizards.chip_repair_wizard import ChipRepairWizard

        project = self.current_project
        if chip_name is None:
            service = getattr(self, 'chip_constraint_service', None)
            chip_name = (service.current_chip if service else None) or getattr(project, 'selected_chip', None)
        database = getattr(project, 'chip_database', None) or get_default_chip_database()
        wizard = ChipRepairWizard(database, chip_name, project, parent=self)
        wizard.chip_repaired.connect(lambda name: self._on_chip_repaired(name, database))
        wizard.exec()

    def _on_chip_repaired(self, chip_name: str, database):
        from .wizards.chip_repair_wizard import project_copy_notice

        self._on_designer_chip_saved(chip_name)
        notice = project_copy_notice(self.current_project, database, chip_name)
        if notice:
            QMessageBox.information(self, "芯片已修复", notice)

    def _launch_chip_dependency_scan(self):
        """Open the chip dependency scan (read-only)."""
        if not self.current_project:
            QMessageBox.information(self, "芯片依赖扫描", "请先打开一个项目。")
            return
        from .dialogs.chip_dependency_scan_dialog import ChipDependencyScanDialog
        dialog = ChipDependencyScanDialog(self.current_project, parent=self)
        # the scan directories and keywords are saved with the project
        dialog.settings_changed.connect(lambda: self.save_project_action.setEnabled(True))
        dialog.exec()

    def _launch_memory_map(self):
        """Open the memory map workbench: the scan, its findings and the layout (read-only)."""
        if not self.current_project:
            QMessageBox.information(self, "内存映射", "请先打开一个项目。")
            return
        from .dialogs.memory_map_workbench import MemoryMapWorkbench
        dialog = MemoryMapWorkbench(self.current_project, parent=self)
        # the directories and the linker file are saved with the project
        dialog.settings_changed.connect(lambda: self.save_project_action.setEnabled(True))
        dialog.exec()

    def _launch_communication_workbench(self, _checked: bool = False, *, initial_tab: Optional[int] = None):
        """Open the 5-tab Communication Configuration & DBC Derivation workbench."""
        if not self.current_project:
            QMessageBox.information(self, "通信配置工作台", "请先打开一个项目。")
            return

        from ..core.communication import CommunicationWorkbenchService
        from .commands import ReplaceMultipleModulesCommand
        from .dialogs.communication_workbench import CommunicationWorkbench

        svc = CommunicationWorkbenchService(self.current_project)
        if not svc.has_comm_modules():
            msg = QMessageBox(self)
            msg.setWindowTitle("未检测到通信栈模块")
            msg.setIcon(QMessageBox.Question)
            msg.setText(
                "当前项目尚未加载 CAN 通信栈模块（Can / CanTrcv / CanIf / CanSM / ComM / PduR / Com / CanTp / EcuC）。"
            )
            msg.setInformativeText("您可以先集成或添加通信栈模块，也可以直接打开空白工作台查看。")
            btn_add = msg.addButton("添加 / 集成模块...", QMessageBox.AcceptRole)
            btn_open = msg.addButton("直接打开工作台", QMessageBox.ActionRole)
            btn_cancel = msg.addButton("取消", QMessageBox.RejectRole)
            msg.exec()
            clicked = msg.clickedButton()
            if clicked is btn_cancel or clicked is None:
                return
            if clicked is btn_add:
                self._add_or_integrate_from_home()
                if not CommunicationWorkbenchService(self.current_project).has_comm_modules():
                    return
            elif clicked is not btn_open:
                return

        dialog = CommunicationWorkbench(self.current_project, parent=self)
        if initial_tab is not None and hasattr(dialog, "select_tab"):
            dialog.select_tab(initial_tab)
        if hasattr(dialog, "navigate_to_path_requested") and hasattr(self, "nav_controller"):
            dialog.navigate_to_path_requested.connect(self.nav_controller._on_reference_jump_requested)

        if dialog.exec() == QDialog.Accepted and getattr(dialog, "has_edits", False):
            after_snapshots = dialog.service.capture_snapshots()
            initial_snapshots = getattr(dialog, "initial_snapshots", None)
            if initial_snapshots is not None and after_snapshots is not None:
                cmd = ReplaceMultipleModulesCommand(
                    self.current_project,
                    initial_snapshots,
                    after_snapshots,
                    text="编辑通信配置",
                    on_applied=self._on_communication_workbench_changed,
                )
                if hasattr(self, "undo_stack") and self.undo_stack is not None:
                    self.undo_stack.push(cmd)
                else:
                    cmd.redo()
            else:
                self._on_communication_workbench_changed()

    def _on_communication_workbench_changed(self):
        """Synchronize dirty state, reference indexes, and views after Communication workbench edits."""
        from ..core.communication import COMM_MODULES

        self._has_unsaved_changes = True
        if hasattr(self, "save_project_action"):
            self.save_project_action.setEnabled(True)
        if hasattr(self, "current_project") and self.current_project is not None:
            resolve_fn = getattr(self.current_project, "resolve_all_references", None)
            if callable(resolve_fn):
                resolve_fn(force=True)
            build_fn = getattr(self.current_project, "build_reverse_reference_index", None)
            if callable(build_fn):
                build_fn()
        panel = getattr(self, "config_panel", None)
        cur_inst = getattr(panel, "current_instance", None) if panel is not None else None
        if cur_inst is not None and getattr(cur_inst, "module_name", None) in set(COMM_MODULES) and hasattr(panel, "clear"):
            panel.clear()
        if hasattr(self, "_update_window_title"):
            self._update_window_title()
        if hasattr(self, "_refresh_config_views"):
            self._refresh_config_views()
        if hasattr(self, "statusbar") and self.statusbar is not None:
            self.statusbar.showMessage("通信配置已更新", 3000)

    def _launch_rte_schm_workbench(self, _checked: bool = False, *, initial_tab: Optional[int] = None):
        """Open the 4-tab RTE / SchM configuration and generation workbench."""
        if not self.current_project:
            QMessageBox.information(self, "RTE / SchM 工作台", "请先打开一个项目。")
            return
        rte_mgr = getattr(self.current_project, "module_managers", {}).get("Rte")
        if rte_mgr is None or getattr(rte_mgr, "configuration", None) is None:
            if not self._prompt_and_setup_missing_rte():
                return
            rte_mgr = getattr(self.current_project, "module_managers", {}).get("Rte")
            if rte_mgr is None or getattr(rte_mgr, "configuration", None) is None:
                return
        from .commands import ReplaceModuleContainersCommand
        from .dialogs.rte_schm_workbench import RteSchmWorkbench

        dialog = RteSchmWorkbench(self.current_project, parent=self)
        if initial_tab is not None and hasattr(dialog, "select_tab"):
            dialog.select_tab(initial_tab)
        if hasattr(dialog, "memmap_settings_changed"):
            def _on_memmap_changed():
                self._has_unsaved_changes = True
                if hasattr(self, "save_project_action"):
                    self.save_project_action.setEnabled(True)
                if hasattr(self, "_update_window_title"):
                    self._update_window_title()

            dialog.memmap_settings_changed.connect(_on_memmap_changed)
        if dialog.exec() == QDialog.Accepted and getattr(dialog, "has_edits", False):
            after_snapshot = dialog.service.capture_snapshot()
            initial_snapshot = getattr(dialog, "initial_snapshot", None)
            if initial_snapshot is not None and after_snapshot is not None:
                cmd = ReplaceModuleContainersCommand(
                    self.current_project,
                    rte_mgr.configuration,
                    initial_snapshot,
                    after_snapshot,
                    text="编辑 RTE / SchM 配置",
                    on_applied=self._on_rte_workbench_changed,
                )
                if hasattr(self, "undo_stack") and self.undo_stack is not None:
                    self.undo_stack.push(cmd)
                else:
                    cmd.redo()
            else:
                self._on_rte_workbench_changed()

    def _on_rte_workbench_changed(self):
        """Synchronize dirty state, reference indexes, and views after RTE workbench edits."""
        self._has_unsaved_changes = True
        if hasattr(self, "save_project_action"):
            self.save_project_action.setEnabled(True)
        if hasattr(self, "current_project") and self.current_project is not None:
            resolve_fn = getattr(self.current_project, "resolve_all_references", None)
            if callable(resolve_fn):
                resolve_fn(force=True)
            build_fn = getattr(self.current_project, "build_reverse_reference_index", None)
            if callable(build_fn):
                build_fn()
        panel = getattr(self, "config_panel", None)
        cur_inst = getattr(panel, "current_instance", None) if panel is not None else None
        if cur_inst is not None and getattr(cur_inst, "module_name", None) == "Rte" and hasattr(panel, "clear"):
            panel.clear()
        if hasattr(self, "_update_window_title"):
            self._update_window_title()
        if hasattr(self, "_refresh_config_views"):
            self._refresh_config_views()
        if hasattr(self, "statusbar") and self.statusbar is not None:
            self.statusbar.showMessage("RTE / SchM 配置已更新", 3000)

    def _prompt_and_setup_missing_rte(self) -> bool:
        """Guide the user to activate, restore, initialize, or import ``Rte`` when missing."""
        project = self.current_project
        if project is None:
            return False

        from ..generator.rte import bootstrap_rte_module, discover_rte_sources

        sources = discover_rte_sources(project)

        box = QMessageBox(self)
        box.setWindowTitle("未加载 Rte 模块")
        box.setIcon(QMessageBox.Icon.Question)

        if sources.library_packages:
            first_pkg = sources.library_packages[0][1]
            lines = [
                f"当前项目尚未加载 Rte 模块，但在模块库中发现了 {len(sources.library_packages)} 个可用的 Rte 定义包：",
                f"  • {first_pkg.manifest.definition}",
                "",
                "可直接从模块库激活 Rte 并打开 RTE / SchM 工作台。",
            ]
        else:
            lines = [
                "当前项目未加载 Rte 模块（常见于仅包含 MCAL 插件的 EB Tresos 工程或新建工程）。",
                "",
                "可点击「初始化内置 Rte 并打开工作台」一键添加内置标准 AUTOSAR Rte 模块，或手动导入 Rte 定义文件（.arxml / .xdm）。",
            ]
        if sources.has_failed_entry:
            lines.append("\n注：工程记录中存在未能加载的 Rte 模块条目（可能因原定义包缺失）。")
        if sources.deleted_archives:
            lines.append("\n注：检测到 .history/deleted/ 下存在已删除的 Rte 配置归档，也可直接恢复。")
        box.setText("\n".join(lines))

        activate_btn = None
        builtin_btn = None
        restore_btn = None
        if sources.library_packages:
            activate_btn = box.addButton("从模块库激活 Rte 并打开", QMessageBox.ButtonRole.AcceptRole)
            box.setDefaultButton(activate_btn)
        else:
            builtin_btn = box.addButton("初始化内置 Rte 并打开工作台", QMessageBox.ButtonRole.AcceptRole)
            box.setDefaultButton(builtin_btn)
        if sources.deleted_archives:
            restore_btn = box.addButton("恢复已删除的 Rte", QMessageBox.ButtonRole.ActionRole)
        import_btn = box.addButton("手动导入 Rte 定义/模块...", QMessageBox.ButtonRole.ActionRole)
        cancel_btn = box.addButton("取消", QMessageBox.ButtonRole.RejectRole)

        box.exec()
        clicked = box.clickedButton()
        if clicked is None or clicked is cancel_btn:
            return False

        confirm_fn = getattr(getattr(self, "project_controller", None), "_confirm_merge", None)

        if clicked is activate_btn:
            chosen_pkg = sources.library_packages[0]
            if len(sources.library_packages) > 1:
                labels = [
                    f"{pkg.manifest.definition} ({pkg.root.name})"
                    for _idx, pkg in sources.library_packages
                ]
                selected, ok = QInputDialog.getItem(
                    self,
                    "选择 Rte 模块包变体",
                    "模块库中存在多个 Rte 定义，请选择要激活的一个：",
                    labels,
                    0,
                    False,
                )
                if not ok or not selected:
                    return False
                chosen_pkg = sources.library_packages[labels.index(selected)]
            try:
                _mgr, source = bootstrap_rte_module(
                    project,
                    library_package=chosen_pkg,
                    confirm=confirm_fn,
                )
            except Exception as exc:
                QMessageBox.critical(self, "初始化 Rte 失败", f"无法添加 Rte 模块：\n{exc}")
                return False
            self._finalize_added_rte_module(source)
            return True

        if clicked is builtin_btn:
            try:
                _mgr, source = bootstrap_rte_module(project, confirm=confirm_fn)
            except Exception as exc:
                QMessageBox.critical(self, "初始化 Rte 失败", f"无法添加 Rte 模块：\n{exc}")
                return False
            self._finalize_added_rte_module(source)
            return True

        if clicked is restore_btn:
            chosen_archive = sources.deleted_archives[0]
            if len(sources.deleted_archives) > 1:
                labels = [p.name for p in sources.deleted_archives]
                selected, ok = QInputDialog.getItem(
                    self,
                    "恢复已删除的 Rte 模块",
                    "选择要恢复的 Rte 配置归档：",
                    labels,
                    0,
                    False,
                )
                if not ok or not selected:
                    return False
                chosen_archive = sources.deleted_archives[labels.index(selected)]
            try:
                _mgr, source = bootstrap_rte_module(
                    project,
                    restore_archive=chosen_archive,
                    confirm=confirm_fn,
                )
            except Exception as exc:
                QMessageBox.critical(self, "初始化 Rte 失败", f"无法添加 Rte 模块：\n{exc}")
                return False
            self._finalize_added_rte_module(source)
            return True

        if clicked is import_btn:
            self.project_controller.add_module_to_project()
            rte_mgr = getattr(self.current_project, "module_managers", {}).get("Rte")
            if rte_mgr is not None and getattr(rte_mgr, "configuration", None) is not None:
                if hasattr(self, "refresh_home_dashboard"):
                    self.refresh_home_dashboard()
                return True
            return False

        return False

    def _finalize_added_rte_module(self, source: str) -> None:
        """Sync UI, references, chip selectors, and dirty state after adding ``Rte``."""
        project = self.current_project
        if project is None:
            return
        self._has_unsaved_changes = True
        if hasattr(project, "is_modified"):
            project.is_modified = True
        if hasattr(self, "save_project_action"):
            self.save_project_action.setEnabled(True)

        load_res = getattr(project, "load_ecu_resources", None)
        if callable(load_res):
            try:
                load_res()
            except Exception as exc:
                logger.warning("ECU resources reload after Rte bootstrap failed: %s", exc)
        apply_sel = getattr(project, "apply_chip_selectors", None)
        if callable(apply_sel):
            try:
                apply_sel(modules=["Rte"])
            except Exception as exc:
                logger.warning("Apply chip selectors after Rte bootstrap failed: %s", exc)
        resolve_fn = getattr(project, "resolve_all_references", None)
        if callable(resolve_fn):
            try:
                resolve_fn(force=True)
            except Exception as exc:
                logger.warning("Reference resolution after Rte bootstrap failed: %s", exc)
        build_fn = getattr(project, "build_reverse_reference_index", None)
        if callable(build_fn):
            try:
                build_fn()
            except Exception as exc:
                logger.warning("Reverse reference index rebuild after Rte bootstrap failed: %s", exc)

        if hasattr(self, "tree_view") and self.tree_view is not None:
            self.tree_view.set_project(project)
        if hasattr(self, "_update_window_title"):
            self._update_window_title()
        if hasattr(self, "refresh_home_dashboard"):
            self.refresh_home_dashboard()
        dep_ctrl = getattr(self, "dep_graph_controller", None)
        if dep_ctrl is not None and hasattr(dep_ctrl, "_update_dependency_graph_if_open"):
            dep_ctrl._update_dependency_graph_if_open()

        msg_map = {
            "builtin": "已初始化内置 Rte 模块（可在工作台页签 1 点击「一键同步」注册 BSW/MCAL 模块）",
            "library": "已从模块库激活 Rte 模块",
            "restored": "已从归档恢复 Rte 模块",
        }
        if hasattr(self, "statusbar") and self.statusbar is not None:
            self.statusbar.showMessage(msg_map.get(source, "已加载 Rte 模块"), 5000)

    def _on_designer_chip_saved(self, chip_name: str):
        """Handle new chip saved from designer"""
        self.statusbar.showMessage(f"芯片库已更新: {chip_name}", 5000)
        project = self.current_project
        if project is not None and hasattr(project, "load_ecu_resources"):
            project.load_ecu_resources()
        # Update chip constraint service if available
        if hasattr(self, 'chip_constraint_service') and self.chip_constraint_service:
            if project and project.path:
                self.chip_constraint_service.set_project(project)
                if getattr(project, "selected_chip", None) == chip_name:
                    self.chip_constraint_service.constraints_changed.emit(chip_name)
        if (
            project is not None
            and getattr(project, "selected_chip", None) == chip_name
            and hasattr(self, "config_panel")
            and self.config_panel is not None
            and getattr(self.config_panel, "current_instance", None) is not None
        ):
            self.config_panel.refresh()

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

