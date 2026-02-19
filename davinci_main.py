#!/usr/bin/env python3
"""
DaVinci-style AUTOSAR Configurator launcher
"""
import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent))

import logging
import os
import builtins

# 调试模式：DAVINCI_DEBUG=1 python davinci_main.py
DEBUG_MODE = os.getenv('DAVINCI_DEBUG', '0') == '1'

logging.basicConfig(
    level=logging.DEBUG if DEBUG_MODE else logging.WARNING,
    format='%(levelname)s: %(message)s',
    stream=sys.stdout
)
logger = logging.getLogger(__name__)

# 生产模式下屏蔽所有 print（stderr 的 error 输出保留）
if not DEBUG_MODE:
    _real_print = builtins.print
    def _silent_print(*args, **kwargs):
        if kwargs.get('file') is sys.stderr:
            _real_print(*args, **kwargs)
    builtins.print = _silent_print

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
