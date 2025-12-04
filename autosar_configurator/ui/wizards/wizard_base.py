"""
Wizard Framework Base Classes
Provides base classes for creating configuration wizards
"""
from PySide6.QtWidgets import (
    QWizard, QWizardPage, QVBoxLayout, QLabel, 
    QLineEdit, QComboBox, QPushButton, QFormLayout
)
from PySide6.QtCore import Qt, Signal
from typing import Optional, Dict, Any
from abc import ABC, abstractmethod


class WizardPage(QWizardPage, ABC):
    """Base class for wizard pages"""
    
    def __init__(self, title: str, subtitle: str = ""):
        super().__init__()
        self.setTitle(title)
        if subtitle:
            self.setSubTitle(subtitle)
        
        self.layout = QVBoxLayout()
        self.setLayout(self.layout)
        
        self._setup_ui()
    
    @abstractmethod
    def _setup_ui(self):
        """Setup page UI - to be implemented by subclasses"""
        pass
    
    @abstractmethod
    def get_data(self) -> Dict[str, Any]:
        """Get data entered on this page"""
        pass
    
    def validatePage(self) -> bool:
        """Validate page data before proceeding"""
        return True


class ConfigWizard(QWizard):
    """Base class for configuration wizards"""
    
    # Signal emitted when wizard completes
    wizard_completed = Signal(dict)  # Emits collected data
    
    def __init__(self, parent=None, title: str = "Configuration Wizard"):
        super().__init__(parent)
        self.setWindowTitle(title)
        self.setWizardStyle(QWizard.ModernStyle)
        self.setOption(QWizard.HaveHelpButton, False)
        
        # Store collected data
        self.collected_data: Dict[str, Any] = {}
        
        self._setup_pages()
    
    @abstractmethod
    def _setup_pages(self):
        """Setup wizard pages - to be implemented by subclasses"""
        pass
    
    def accept(self):
        """Called when wizard is finished"""
        # Collect data from all pages
        for page_id in self.pageIds():
            page = self.page(page_id)
            if isinstance(page, WizardPage):
                self.collected_data.update(page.get_data())
        
        # Emit signal with collected data
        self.wizard_completed.emit(self.collected_data)
        
        super().accept()
