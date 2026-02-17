#!/usr/bin/env python3
"""
DaVinci-style AUTOSAR Configurator launcher
"""
import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent))

import logging

# Configure logging to see diagnostic output in terminal
logging.basicConfig(
    level=logging.INFO,
    format='%(levelname)s: %(message)s',
    stream=sys.stdout
)
logger = logging.getLogger(__name__)

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
