#!/usr/bin/env python3
"""
DaVinci-style AUTOSAR Configurator launcher
"""
import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent))

from PySide6.QtWidgets import QApplication
from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow


def main():
    app = QApplication(sys.argv)
    app.setApplicationName("AUTOSAR DaVinci Configurator")
    app.setOrganizationName("AUTOSAR")
    
    window = DaVinciMainWindow()
    window.show()
    
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
