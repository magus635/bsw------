"""Unit tests for DependencyGraphController (P2-6 phase 4).

QMessageBox is patched so the guard paths can be exercised headless, without a
QApplication or real modal dialogs.
"""
from unittest.mock import MagicMock, patch

from autosar_configurator.ui.controllers.dependency_graph_controller import (
    DependencyGraphController,
)


def test_update_graph_noop_when_dialog_closed():
    win = MagicMock()
    ctrl = DependencyGraphController(win)
    # No dialog created yet → must be a no-op, not touch any graph widget.
    ctrl._update_dependency_graph_if_open()
    # Nothing to assert beyond "did not raise"; widget stays None.
    assert ctrl.dep_graph_widget is None


def test_show_graph_guards_without_configuration():
    win = MagicMock()
    win.current_project = None
    win.config_manager = None
    win.module_def = None
    ctrl = DependencyGraphController(win)

    with patch(
        "autosar_configurator.ui.controllers.dependency_graph_controller.QMessageBox"
    ) as mb:
        ctrl.show_dependency_graph()
        mb.warning.assert_called_once()
    # Guarded out before any dialog/widget was created.
    assert ctrl.dep_graph_dialog is None


def test_analyze_guards_without_project():
    win = MagicMock()
    win.current_project = None
    ctrl = DependencyGraphController(win)

    with patch(
        "autosar_configurator.ui.controllers.dependency_graph_controller.QMessageBox"
    ) as mb:
        ctrl._analyze_cross_module_dependencies()
        mb.warning.assert_called_once()
    # No background worker submitted.
    win.thread_pool.start.assert_not_called()


def test_validate_guards_without_project():
    win = MagicMock()
    win.current_project = None
    ctrl = DependencyGraphController(win)

    with patch(
        "autosar_configurator.ui.controllers.dependency_graph_controller.QMessageBox"
    ) as mb:
        ctrl._validate_cross_module_dependencies()
        mb.warning.assert_called_once()
