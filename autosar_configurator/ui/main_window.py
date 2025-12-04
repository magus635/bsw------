"""
Main window for AUTOSAR BSW Configurator
"""
from PySide6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QSplitter, QMenuBar, QMenu, QToolBar, QStatusBar,
    QFileDialog, QMessageBox, QStyle
)
from PySide6.QtCore import Qt, Signal, QSettings
from PySide6.QtGui import QAction, QKeySequence
from pathlib import Path
from typing import Optional

from ..core.parser.arxml_parser import ArxmlParser
from ..core.serializer.arxml_serializer import ArxmlSerializer
from ..core.model.container import Container, Parameter
from ..core.command import CommandManager
from .widgets.tree_view import ModuleTreeView
from .widgets.config_panel import ConfigPanel
from .widgets.search_dialog import SearchDialog


class MainWindow(QMainWindow):
    """Main application window"""

    # Signals
    file_opened = Signal(Path)
    file_saved = Signal(Path)
    container_changed = Signal(Container)

    def __init__(self):
        super().__init__()

        self.current_file: Optional[Path] = None
        self.root_container: Optional[Container] = None
        self.is_modified = False

        self.parser = ArxmlParser()
        self.serializer = ArxmlSerializer(use_namespaces=True, pretty_print=True)
        self.command_manager = CommandManager(max_stack_size=50)
        self.search_dialog: Optional[SearchDialog] = None

        self.settings = QSettings("AUTOSAR", "BSWConfigurator")

        self._setup_ui()
        self._create_actions()
        self._create_menus()
        self._create_toolbars()
        self._create_statusbar()
        self._apply_stylesheet()
        self._restore_settings()

    def _setup_ui(self):
        """Setup the UI layout"""
        self.setWindowTitle("AUTOSAR BSW Configurator")
        self.setMinimumSize(1200, 800)

        # Create central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Main layout
        main_layout = QHBoxLayout(central_widget)
        main_layout.setContentsMargins(0, 0, 0, 0)

        # Create splitter for resizable panels
        self.splitter = QSplitter(Qt.Horizontal)
        main_layout.addWidget(self.splitter)

        # Left panel - Module tree view
        self.tree_view = ModuleTreeView()
        self.tree_view.container_selected.connect(self._on_container_selected)
        self.tree_view.parameter_selected.connect(self._on_parameter_selected)
        self.splitter.addWidget(self.tree_view)

        # Right panel - Configuration panel
        self.config_panel = ConfigPanel()
        self.config_panel.parameter_changed.connect(self._on_parameter_changed)
        self.config_panel.container_changed.connect(self._on_container_changed)
        self.splitter.addWidget(self.config_panel)

        # Set initial splitter sizes (30% left, 70% right)
        self.splitter.setSizes([360, 840])

    def _create_actions(self):
        """Create menu and toolbar actions"""
        style = self.style()
        
        # File actions
        self.new_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_FileIcon), "&New", self)
        self.new_action.setShortcut(QKeySequence.New)
        self.new_action.setStatusTip("Create a new configuration")
        self.new_action.triggered.connect(self.new_file)

        self.open_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_DialogOpenButton), "&Open...", self)
        self.open_action.setShortcut(QKeySequence.Open)
        self.open_action.setStatusTip("Open an existing ARXML file")
        self.open_action.triggered.connect(self.open_file)

        self.save_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_DialogSaveButton), "&Save", self)
        self.save_action.setShortcut(QKeySequence.Save)
        self.save_action.setStatusTip("Save the current configuration")
        self.save_action.triggered.connect(self.save_file)
        self.save_action.setEnabled(False)

        self.save_as_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_DialogSaveButton), "Save &As...", self)
        self.save_as_action.setShortcut(QKeySequence.SaveAs)
        self.save_as_action.setStatusTip("Save the configuration to a new file")
        self.save_as_action.triggered.connect(self.save_file_as)
        self.save_as_action.setEnabled(False)

        self.exit_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_DialogCloseButton), "E&xit", self)
        self.exit_action.setShortcut(QKeySequence.Quit)
        self.exit_action.setStatusTip("Exit the application")
        self.exit_action.triggered.connect(self.close)

        # Edit actions
        self.undo_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_ArrowBack), "&Undo", self)
        self.undo_action.setShortcut(QKeySequence.Undo)
        self.undo_action.setStatusTip("Undo last action")
        self.undo_action.setEnabled(False)
        self.undo_action.triggered.connect(self.undo)

        self.redo_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_ArrowForward), "&Redo", self)
        self.redo_action.setShortcut(QKeySequence.Redo)
        self.redo_action.setStatusTip("Redo last undone action")
        self.redo_action.setEnabled(False)
        self.redo_action.triggered.connect(self.redo)

        # View actions
        self.refresh_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_BrowserReload), "&Refresh", self)
        self.refresh_action.setShortcut(QKeySequence.Refresh)
        self.refresh_action.setStatusTip("Refresh the view")
        self.refresh_action.triggered.connect(self.refresh_view)
        
        self.find_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_FileDialogContentsView), "&Find...", self)
        self.find_action.setShortcut(QKeySequence.Find)
        self.find_action.setStatusTip("Search for configuration elements")
        self.find_action.triggered.connect(self.show_search_dialog)

        # Help actions
        self.about_action = QAction(style.standardIcon(QStyle.StandardPixmap.SP_MessageBoxInformation), "&About", self)
        self.about_action.setStatusTip("About AUTOSAR BSW Configurator")
        self.about_action.triggered.connect(self.show_about)

    def _apply_stylesheet(self):
        """Apply application stylesheet"""
        self.setStyleSheet("""
            QMainWindow {
                background-color: #f0f0f0;
            }
            QTreeWidget {
                background-color: white;
                border: 1px solid #ccc;
            }
            QGroupBox {
                font-weight: bold;
                border: 1px solid #ccc;
                border-radius: 5px;
                margin-top: 10px;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 3px;
            }
            QLineEdit, QComboBox, QSpinBox, QTextEdit {
                padding: 5px;
                border: 1px solid #ccc;
                border-radius: 3px;
                background-color: white;
            }
            QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QTextEdit:focus {
                border: 1px solid #3a86ff;
            }
            QPushButton {
                padding: 5px 15px;
                background-color: #e0e0e0;
                border: 1px solid #ccc;
                border-radius: 3px;
            }
            QPushButton:hover {
                background-color: #d0d0d0;
            }
            QPushButton:pressed {
                background-color: #c0c0c0;
            }
            QStatusBar {
                background-color: #e0e0e0;
                border-top: 1px solid #ccc;
            }
            QToolBar {
                background-color: #f0f0f0;
                border-bottom: 1px solid #ccc;
                spacing: 5px;
            }
        """)

    def _create_menus(self):
        """Create menu bar"""
        menubar = self.menuBar()

        # File menu
        file_menu = menubar.addMenu("&File")
        file_menu.addAction(self.new_action)
        file_menu.addAction(self.open_action)
        file_menu.addSeparator()
        file_menu.addAction(self.save_action)
        file_menu.addAction(self.save_as_action)
        file_menu.addSeparator()
        file_menu.addAction(self.exit_action)

        # Edit menu
        edit_menu = menubar.addMenu("&Edit")
        edit_menu.addAction(self.undo_action)
        edit_menu.addAction(self.redo_action)

        # View menu
        view_menu = menubar.addMenu("&View")
        view_menu.addAction(self.refresh_action)
        view_menu.addSeparator()
        view_menu.addAction(self.find_action)

        # Help menu
        help_menu = menubar.addMenu("&Help")
        help_menu.addAction(self.about_action)

    def _create_toolbars(self):
        """Create toolbars"""
        toolbar = self.addToolBar("Main Toolbar")
        toolbar.setMovable(False)

        toolbar.addAction(self.new_action)
        toolbar.addAction(self.open_action)
        toolbar.addAction(self.save_action)
        toolbar.addSeparator()
        toolbar.addAction(self.undo_action)
        toolbar.addAction(self.redo_action)
        toolbar.addSeparator()
        toolbar.addAction(self.find_action)
        toolbar.addSeparator()
        toolbar.addAction(self.refresh_action)

    def _create_statusbar(self):
        """Create status bar"""
        self.statusBar().showMessage("Ready")

    def new_file(self):
        """Create a new configuration"""
        if self.is_modified and not self._confirm_discard_changes():
            return

        self.root_container = Container(short_name="RootConfiguration")
        self.current_file = None
        self.is_modified = False
        self.command_manager.clear()  # Clear command history for new file
        self._update_window_title()
        self.save_action.setEnabled(True)
        self.save_as_action.setEnabled(True)
        self._update_undo_redo_actions()

        # Update UI
        self.tree_view.set_root_container(self.root_container)
        self.tree_view.set_command_manager(self.command_manager)  # Pass command manager to tree view
        self.config_panel.clear()

        self.container_changed.emit(self.root_container)
        self.statusBar().showMessage("New configuration created")

    def open_file(self):
        """Open an ARXML file"""
        if self.is_modified and not self._confirm_discard_changes():
            return

        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open ARXML File",
            str(self._get_last_directory()),
            "ARXML Files (*.arxml);;All Files (*)"
        )

        if file_path:
            self._open_file(Path(file_path))

    def _open_file(self, file_path: Path):
        """Open a specific file"""
        try:
            self.root_container = self.parser.parse_file(file_path)
            self.current_file = file_path
            self.is_modified = False
            self.command_manager.clear()  # Clear command history for opened file
            self._save_last_directory(file_path.parent)
            self._update_window_title()
            self.save_action.setEnabled(True)
            self.save_as_action.setEnabled(True)
            self._update_undo_redo_actions()

            # Update UI
            self.tree_view.set_root_container(self.root_container)
            self.tree_view.set_command_manager(self.command_manager)  # Pass command manager to tree view
            self.config_panel.clear()

            self.file_opened.emit(file_path)
            self.container_changed.emit(self.root_container)
            self.statusBar().showMessage(f"Opened: {file_path.name}")
        except Exception as e:
            QMessageBox.critical(
                self,
                "Error Opening File",
                f"Failed to open file:\n{str(e)}"
            )

    def save_file(self):
        """Save the current configuration"""
        if self.current_file is None:
            return self.save_file_as()

        try:
            self.serializer.serialize_to_file(self.root_container, self.current_file)
            self.is_modified = False
            self._update_window_title()
            self.file_saved.emit(self.current_file)
            self.statusBar().showMessage(f"Saved: {self.current_file.name}")
            return True
        except Exception as e:
            QMessageBox.critical(
                self,
                "Error Saving File",
                f"Failed to save file:\n{str(e)}"
            )
            return False

    def save_file_as(self):
        """Save the configuration to a new file"""
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save ARXML File",
            str(self._get_last_directory()),
            "ARXML Files (*.arxml);;All Files (*)"
        )

        if file_path:
            path = Path(file_path)
            if path.suffix != '.arxml':
                path = path.with_suffix('.arxml')

            try:
                self.serializer.serialize_to_file(self.root_container, path)
                self.current_file = path
                self.is_modified = False
                self._save_last_directory(path.parent)
                self._update_window_title()
                self.file_saved.emit(path)
                self.statusBar().showMessage(f"Saved as: {path.name}")
                return True
            except Exception as e:
                QMessageBox.critical(
                    self,
                    "Error Saving File",
                    f"Failed to save file:\n{str(e)}"
                )
                return False

        return False

    def refresh_view(self):
        """Refresh the current view"""
        if self.root_container:
            self.container_changed.emit(self.root_container)
            self.statusBar().showMessage("View refreshed")

    def show_about(self):
        """Show about dialog"""
        QMessageBox.about(
            self,
            "About AUTOSAR BSW Configurator",
            "<h3>AUTOSAR BSW Configurator</h3>"
            "<p>Version 1.0.0</p>"
            "<p>A Python-based graphical configuration tool for AUTOSAR BSW modules.</p>"
            "<p>Built with PySide6 and lxml.</p>"
        )

    def mark_modified(self):
        """Mark the current file as modified"""
        if not self.is_modified:
            self.is_modified = True
            self._update_window_title()

    def closeEvent(self, event):
        """Handle window close event"""
        if self.is_modified and not self._confirm_discard_changes():
            event.ignore()
        else:
            self._save_settings()
            event.accept()

    def _confirm_discard_changes(self) -> bool:
        """Ask user to confirm discarding changes"""
        reply = QMessageBox.question(
            self,
            "Unsaved Changes",
            "The configuration has been modified.\nDo you want to discard the changes?",
            QMessageBox.Save | QMessageBox.Discard | QMessageBox.Cancel,
            QMessageBox.Save
        )

        if reply == QMessageBox.Save:
            return self.save_file()
        elif reply == QMessageBox.Discard:
            return True
        else:
            return False

    def _update_window_title(self):
        """Update the window title"""
        title = "AUTOSAR BSW Configurator"

        if self.current_file:
            title += f" - {self.current_file.name}"

        if self.is_modified:
            title += " *"

        self.setWindowTitle(title)

    def _get_last_directory(self) -> Path:
        """Get the last used directory"""
        last_dir = self.settings.value("last_directory", "")
        if last_dir and Path(last_dir).exists():
            return Path(last_dir)
        return Path.home()

    def _save_last_directory(self, directory: Path):
        """Save the last used directory"""
        self.settings.setValue("last_directory", str(directory))

    def _save_settings(self):
        """Save window settings"""
        self.settings.setValue("geometry", self.saveGeometry())
        self.settings.setValue("window_state", self.saveState())
        self.settings.setValue("splitter_state", self.splitter.saveState())

    def _restore_settings(self):
        """Restore window settings"""
        geometry = self.settings.value("geometry")
        if geometry:
            self.restoreGeometry(geometry)

        window_state = self.settings.value("window_state")
        if window_state:
            self.restoreState(window_state)

        splitter_state = self.settings.value("splitter_state")
        if splitter_state:
            self.splitter.restoreState(splitter_state)

    def _on_container_selected(self, container: Container):
        """Handle container selection in tree view"""
        self.config_panel.show_container(container)

    def _on_parameter_selected(self, parameter: Parameter):
        """Handle parameter selection in tree view"""
        self.config_panel.show_parameter(parameter)

    def _on_parameter_changed(self, parameter: Parameter):
        """Handle parameter change in config panel"""
        self.mark_modified()
        # Tree view will be updated via observer pattern

    def _on_container_changed(self, container: Container):
        """Handle container change in config panel"""
        self.mark_modified()
        # Tree view will be updated via observer pattern
    
    def undo(self):
        """Undo the last command"""
        if self.command_manager.undo():
            self.mark_modified()
            self._update_undo_redo_actions()
            desc = self.command_manager.get_redo_description()
            self.statusBar().showMessage(f"Undone: {desc}" if desc else "Undone")
    
    def redo(self):
        """Redo the last undone command"""
        if self.command_manager.redo():
            self.mark_modified()
            self._update_undo_redo_actions()
            desc = self.command_manager.get_undo_description()
            self.statusBar().showMessage(f"Redone: {desc}" if desc else "Redone")
    
    def _update_undo_redo_actions(self):
        """Update undo/redo action states"""
        can_undo = self.command_manager.can_undo()
        can_redo = self.command_manager.can_redo()
        
        self.undo_action.setEnabled(can_undo)
        self.redo_action.setEnabled(can_redo)
        
        # Update tooltips with command descriptions
        if can_undo:
            desc = self.command_manager.get_undo_description()
            self.undo_action.setStatusTip(f"Undo: {desc}")
        else:
            self.undo_action.setStatusTip("Undo last action")
        
        if can_redo:
            desc = self.command_manager.get_redo_description()
            self.redo_action.setStatusTip(f"Redo: {desc}")
        else:
            self.redo_action.setStatusTip("Redo last undone action")
    
    def get_command_manager(self) -> CommandManager:
        """Get the command manager instance"""
        return self.command_manager
    
    def show_search_dialog(self):
        """Show the search dialog"""
        if not self.root_container:
            QMessageBox.information(
                self,
                "No Configuration",
                "Please open or create a configuration first."
            )
            return
        
        # Create search dialog if it doesn't exist
        if not self.search_dialog:
            self.search_dialog = SearchDialog(self.root_container, self)
            self.search_dialog.navigate_to_result.connect(self._navigate_to_search_result)
        else:
            self.search_dialog.set_root_container(self.root_container)
        
        # Show and focus the dialog
        self.search_dialog.show()
        self.search_dialog.raise_()
        self.search_dialog.activateWindow()
        self.search_dialog.focus_search_input()
    
    def _navigate_to_search_result(self, result):
        """Navigate to a search result in the tree view"""
        self.tree_view.navigate_to_element(result.element)
        self.statusBar().showMessage(f"Navigated to: {result.path}")
