#!/usr/bin/env python3
"""
AUTOSAR BSW Configurator - Application Entry Point
"""
import sys
from PySide6.QtWidgets import QApplication
from autosar_configurator.ui.main_window import MainWindow


def main():
    """Main application entry point"""
    app = QApplication(sys.argv)

    # Set application metadata
    app.setApplicationName("AUTOSAR BSW Configurator")
    app.setOrganizationName("AUTOSAR")
    app.setOrganizationDomain("autosar.org")

    # Create and show main window
    window = MainWindow()
    window.show()

    sys.exit(app.exec())


if __name__ == "__main__":
    main()
