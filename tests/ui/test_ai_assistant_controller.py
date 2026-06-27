"""Unit tests for AiAssistantController (P2-6 phase 1).

These exercise the controller's pure dispatch logic with a stub window, with no
QApplication required — demonstrating that AI behaviour is now testable in
isolation from the 3500-line main window.
"""
from unittest.mock import MagicMock

from autosar_configurator.ui.controllers.ai_assistant_controller import AiAssistantController


def test_handle_action_dispatches_to_window():
    win = MagicMock()
    ctrl = AiAssistantController(win)

    ctrl.handle_action("validate")
    win.validate_configuration.assert_called_once()

    ctrl.handle_action("save")
    win.save_project.assert_called_once()

    ctrl.handle_action("generate")
    win.generation_controller.generate_code.assert_called_once()


def test_handle_action_ignores_unknown():
    win = MagicMock()
    ctrl = AiAssistantController(win)

    ctrl.handle_action("nonexistent")
    win.validate_configuration.assert_not_called()
    win.save_project.assert_not_called()
    win.generation_controller.generate_code.assert_not_called()


def test_cleanup_is_safe_without_process():
    ctrl = AiAssistantController(MagicMock())
    # No subprocess started — cleanup must be a no-op, not raise.
    ctrl.cleanup()


def test_on_help_requested_without_api_key_shows_hint():
    win = MagicMock()
    win.settings.value.return_value = None  # no gemini_api_key
    ctrl = AiAssistantController(win)

    ctrl.on_help_requested("CanController", "CanBaudrate")

    win.config_panel.update_ai_help.assert_called_once()
    msg = win.config_panel.update_ai_help.call_args[0][0]
    assert "API Key" in msg
