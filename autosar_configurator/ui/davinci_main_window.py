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
from ..core.model.definition_model import EcucModuleDef, EcucContainerDef
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from .widgets.davinci_tree_view import DaVinciTreeView
from .widgets.davinci_config_panel import DaVinciConfigPanel
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
        
        # Parsers
        self.def_parser = EcucDefParser()
        
        # Settings
        self.settings = QSettings("AUTOSAR", "DaVinciConfigurator")
        
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
    
    def _create_actions(self):
        """Create actions"""
        # File actions
        self.open_def_action = QAction("Open DEF File...", self)
        self.open_def_action.setShortcut(QKeySequence.Open)
        self.open_def_action.setStatusTip("Open ECUC-DEF ARXML file")
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
        self.save_value_action.setEnabled(False)
        self.save_value_action.triggered.connect(self.save_value_file)
        
        self.save_value_as_action = QAction("Save Configuration As...", self)
        self.save_value_as_action.setShortcut(QKeySequence("Ctrl+Shift+S"))
        self.save_value_as_action.setEnabled(False)
        self.save_value_as_action.triggered.connect(self.save_value_file_as)
        
        self.exit_action = QAction("Exit", self)
        self.exit_action.setShortcut(QKeySequence.Quit)
        self.exit_action.triggered.connect(self.close)
        
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
    
    def _create_menus(self):
        """Create menus"""
        menubar = self.menuBar()
        
        # File menu
        file_menu = menubar.addMenu("File")
        file_menu.addAction(self.open_def_action)
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
        edit_menu.addSeparator()
        edit_menu.addAction(self.load_rules_action)
        
        # Generate menu
        gen_menu = menubar.addMenu("Generate")
        gen_menu.addAction(self.generate_action)
    
    def _create_toolbars(self):
        """Create toolbars"""
        toolbar = self.addToolBar("Main Toolbar")
        toolbar.addAction(self.open_def_action)
        toolbar.addAction(self.new_config_action)
        toolbar.addAction(self.save_value_action)
        toolbar.addSeparator()
        toolbar.addAction(self.validate_action)
        toolbar.addSeparator()
        toolbar.addAction(self.generate_action)
    
    def _create_statusbar(self):
        """Create status bar"""
        self.statusbar = QStatusBar()
        self.setStatusBar(self.statusbar)
        
        # Status labels
        self.def_file_label = QLabel("No DEF file loaded")
        self.value_file_label = QLabel("No configuration")
        self.validation_label = QLabel("")
        
        self.statusbar.addWidget(self.def_file_label)
        self.statusbar.addWidget(QLabel("|"))
        self.statusbar.addWidget(self.value_file_label)
        self.statusbar.addPermanentWidget(self.validation_label)
    
    # File operations
    
    def open_def_file(self):
        """Open ECUC-DEF ARXML file"""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open ECUC-DEF File",
            str(Path.home()),
            "ARXML Files (*.arxml);;All Files (*)"
        )
        
        if not file_path:
            return
        
        try:
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
            
            self.statusbar.showMessage(f"Loaded DEF: {self.module_def.short_name}", 3000)
            
            # Save to settings
            self.settings.setValue("last_def_file", str(file_path))
            
        except Exception as e:
            QMessageBox.critical(
                self,
                "Error Loading DEF File",
                f"Failed to load DEF file:\n{str(e)}"
            )
            self.statusbar.showMessage("Error loading DEF file")
    
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
            self.tree_view.refresh_tree()
            self.config_panel.clear_panel()
            
            # Enable actions
            self.save_value_action.setEnabled(True)
            self.save_value_action.setEnabled(True)
            self.validate_action.setEnabled(True)
            self.load_rules_action.setEnabled(True)
            self.generate_action.setEnabled(True)
            
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
            
            self.current_value_file = file_path
            self.value_file_label.setText(f"Config: {file_path.name}")
            self.statusbar.showMessage("Configuration saved successfully", 3000)
            
        except Exception as e:
            QMessageBox.critical(self, "Save Error", f"Failed to save configuration:\n{str(e)}")
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
                "Error Loading Rules",
                f"Failed to load rules:\n{str(e)}"
            )

    def generate_code(self):
        """Generate C/C++ code"""
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
            self.statusbar.showMessage("Generating code...")
            
            # Create generator and run
            generator = CodeGenerator(self.module_def, self.config_manager.configuration)
            generator.generate_all(Path(output_dir))
            
            QMessageBox.information(
                self,
                "Generation Success",
                f"Code generated successfully in:\n{output_dir}"
            )
            self.statusbar.showMessage("Code generation successful", 3000)
            
        except Exception as e:
            QMessageBox.critical(
                self,
                "Generation Error",
                f"Failed to generate code:\n{str(e)}"
            )
            self.statusbar.showMessage("Code generation failed", 3000)
    
    def _on_instance_selected(self, instance: EcucContainerValue, container_def: EcucContainerDef):
        """Handle instance selection in tree"""
        self.config_panel.show_instance(instance, container_def, self.config_manager)
    
    def _on_def_selected(self, container_def: EcucContainerDef):
        """Handle definition node selection in tree"""
        self.config_panel.show_definition(container_def)
    
    def _on_parameter_changed(self, instance: EcucContainerValue, param_name: str, value: any):
        """Handle parameter value change"""
        try:
            self.config_manager.set_parameter_value(instance, param_name, value)
            self.statusbar.showMessage(f"Set {param_name} = {value}", 2000)
            
            # Mark as modified
            self.value_file_label.setText(f"{self.value_file_label.text()} *")
        except Exception as e:
            QMessageBox.warning(self, "Invalid Value", str(e))
    
    def _load_last_session(self):
        """Load last opened DEF file"""
        last_def = self.settings.value("last_def_file")
        if last_def and Path(last_def).exists():
            # Auto-load on startup?
            pass  # For now, let user manually open
