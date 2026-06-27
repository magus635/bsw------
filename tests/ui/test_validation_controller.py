"""Unit tests for ValidationController (P2-6 phase 7).

Exercise the single-module validation flow and custom-rule loading guards with
a stub window — no QApplication required.
"""
from unittest.mock import MagicMock, patch

from autosar_configurator.ui.controllers.validation_controller import ValidationController


def test_validate_single_module_publishes_results_to_problems_view():
    win = MagicMock()
    win.current_project = None
    # config_manager present so the engine path runs
    win.config_manager = MagicMock()

    fake_result = MagicMock()
    fake_result.is_valid = True
    fake_result.messages = ["m1"]
    engine = MagicMock()
    engine.validate.return_value = fake_result
    ctrl = ValidationController(win)

    with patch(
        "autosar_configurator.core.validation_engine.ValidationEngine",
        return_value=engine,
    ):
        ctrl.validate_configuration()

    win.problems_view.set_messages.assert_called_once_with(fake_result.messages)
    win.problems_dock.show.assert_called_once()


def test_load_custom_rules_guards_without_config_manager():
    win = MagicMock()
    win.config_manager = None
    ctrl = ValidationController(win)

    with patch(
        "autosar_configurator.ui.controllers.validation_controller.QFileDialog"
    ) as fd:
        ctrl.load_custom_rules()
        fd.getOpenFileName.assert_not_called()


def test_load_custom_rules_cancelled_dialog_is_noop():
    win = MagicMock()
    win.config_manager = MagicMock()
    ctrl = ValidationController(win)

    with patch(
        "autosar_configurator.ui.controllers.validation_controller.QFileDialog"
    ) as fd:
        fd.getOpenFileName.return_value = ("", "")  # user cancelled
        ctrl.load_custom_rules()
        win.config_manager.add_custom_rule_file.assert_not_called()
