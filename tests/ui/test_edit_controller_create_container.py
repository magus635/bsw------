from unittest.mock import MagicMock, patch
from autosar_configurator.ui.controllers.edit_controller import EditController


def test_handle_create_container_uses_target_module_config_manager():
    """Reproduce bug: creating a container in another module uses wrong active config_manager."""
    win = MagicMock()
    active_cm = MagicMock()
    active_cm._instance_exists.return_value = True  # Active module happens to have same name

    target_cm = MagicMock()
    target_cm._instance_exists.return_value = False  # Target module (CanTrcv) does NOT have it

    container_def = MagicMock()
    container_def.short_name = "CanTrcvConfigSet"
    container_def.definition_ref = "/AUTOSAR/EcucDefs/CanTrcv/CanTrcvConfigSet"

    # Simulate multi-module project where CanTrcv has its own config_manager
    win.config_manager = active_cm
    win.workspace = MagicMock()
    win.workspace.get_manager_for_definition.return_value = target_cm

    controller = EditController(win)
    with patch("autosar_configurator.ui.controllers.edit_controller.QMessageBox") as mock_msg, \
         patch("autosar_configurator.ui.controllers.edit_controller.CreateContainerCommand") as mock_cmd:
        controller.handle_create_container(container_def, None, "CanTrcvConfigSet")

    # Should NOT show duplicate warning because target_cm does not have it
    mock_msg.warning.assert_not_called()
    mock_cmd.assert_called_once_with(target_cm, container_def, None, "CanTrcvConfigSet")

