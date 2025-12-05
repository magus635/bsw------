"""
DaVinci-style Main Window for ECUC Configuration
Dual-mode: loads DEF files and allows creating VALUE instances
"""
from PySide6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QSplitter, QMenuBar, QMenu, QToolBar, QStatusBar,
    QFileDialog, QMessageBox, QStyle, QLabel
)
from PySide6.QtCore import Qt, Signal, QSettings
from PySide6.QtGui import QAction, QKeySequence
from pathlib import Path
from typing import Optional

from ..core.parser.ecuc_def_parser import EcucDefParser
from ..core.config_manager import ConfigurationManager
from ..core.workspace_manager import WorkspaceManager, WorkspaceProject
from ..core.model.definition_model import EcucModuleDef, EcucContainerDef
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from .widgets.davinci_tree_view import DaVinciTreeView
from .widgets.davinci_config_panel import DaVinciConfigPanel
from .widgets.smart_search import SmartSearchWidget
from .widgets.dependency_graph import DependencyGraphWidget
from ..generator.generator import CodeGenerator


class DaVinciMainWindow(QMainWindow):
    """DaVinci Configurator-style main window"""
    
    def __init__(self):
        super().__init__()
        
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
        splitter.addWidget(self.tree_view)
        
        # Right: Config panel
        self.config_panel = DaVinciConfigPanel()
        self.config_panel.parameter_changed.connect(self._on_parameter_changed)
        splitter.addWidget(self.config_panel)
        
        # Set splitter proportions
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 2)
        
        layout.addWidget(splitter)
        
        # Dependency graph widget (in separate window)
        self.dep_graph_widget = None
        self.dep_graph_dialog = None
    
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
        edit_menu.addAction(self.validate_action)
        edit_menu.addAction(self.load_rules_action)
        
        # View menu
        view_menu = menubar.addMenu("View")
        view_menu.addAction(self.toggle_search_action)
        view_menu.addAction(self.show_dep_graph_action)
        
        # Generate menu
        gen_menu = menubar.addMenu("Generate")
        gen_menu.addAction(self.generate_action)
        
        # Wizards menu
        wizards_menu = menubar.addMenu("Wizards")
        wizards_menu.addAction(self.quick_config_action)
    
    def _create_toolbars(self):
        """Create toolbars"""
        toolbar = self.addToolBar("Main Toolbar")
        toolbar.setObjectName("MainToolbar")  # Fix QMainWindow::saveState() warning
        toolbar.addAction(self.open_def_action)
        toolbar.addAction(self.new_config_action)
        toolbar.addAction(self.save_value_action)
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
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to load project:\n{str(e)}")
            
    def save_project(self):
        """Save current project"""
        if not self.current_project:
            return
            
        self.workspace_manager.save_project()
        self.statusbar.showMessage(f"Project saved: {self.current_project.path}", 3000)
    
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
    
    def validate_configuration(self):
        """Validate current configuration"""
        if not self.config_manager:
            return
        
        result = self.config_manager.validate_configuration()
        
        if not result.is_valid:
            # Format error messages
            error_text = "\n".join(f"• {msg}" for msg in result.errors)
            
            # Show dialog
            QMessageBox.warning(
                self,
                "Validation Errors",
                f"Found {result.error_count} validation error(s):\n\n{error_text}"
            )
            
            # Update status
            self.validation_label.setText(f"❌ {result.error_count} errors")
            self.validation_label.setStyleSheet("color: red;")
        else:
            QMessageBox.information(
                self,
                "Validation Success",
                "✓ Configuration is valid!"
            )
            self.validation_label.setText("✓ Valid")
            self.validation_label.setStyleSheet("color: green;")
            
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
            
            # Set search engine context
            if self.config_manager:
                from ..core.search_engine import SearchEngine
                search_engine = SearchEngine(
                    self.module_def,
                    self.config_manager.configuration
                )
                self.search_widget.set_engine(search_engine)
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
            # Refresh existing graph and show
            self.dep_graph_widget.build_graph(
                self.module_def,
                self.config_manager.configuration
            )
            self.dep_graph_dialog.show()
            self.dep_graph_dialog.raise_()
            self.dep_graph_dialog.activateWindow()
    
    def _on_instance_selected(self, instance: EcucContainerValue, container_def: EcucContainerDef, manager=None):
        """Handle instance selection in tree"""
        # Update active context if manager provided (Project Mode)
        if manager:
            self._update_active_context(manager)
            
        self.config_panel.show_instance(instance, container_def, self.config_manager)
    
    def _on_def_selected(self, container_def: EcucContainerDef, manager=None):
        """Handle definition node selection in tree"""
        # Update active context if manager provided (Project Mode)
        if manager:
            self._update_active_context(manager)
            
        self.config_panel.show_definition(container_def)
        
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
        try:
            # Check if this is a reference parameter (indicated by 'ref:' prefix)
            if param_name.startswith('ref:'):
                # This is handled by the reference selector in config panel
                # Just mark as modified
                self._has_unsaved_changes = True
                self.statusbar.showMessage(f"Reference updated", 2000)
            else:
                # Regular parameter
                self.config_manager.set_parameter_value(instance, param_name, value)
                self.statusbar.showMessage(f"Set {param_name} = {value}", 2000)
                
                # Mark as modified
                self._has_unsaved_changes = True
        except Exception as e:
            QMessageBox.warning(self, "Invalid Value", str(e))
    
    def _load_last_session(self):
        """Load last opened DEF file"""
        last_def = self.settings.value("last_def_file")
        if last_def and Path(last_def).exists():
            # Auto-load on startup?
            pass  # For now, let user manually open
    
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
        
        # Save window geometry
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("windowState", self.saveState())
        event.accept()
