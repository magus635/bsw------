from unittest.mock import MagicMock, patch
from autosar_configurator.ui.controllers.edit_controller import EditController


def test_handle_create_container_uses_target_module_config_manager():
    """Verify creating a container in another module resolves config_manager from win.project.module_managers."""
    win = MagicMock()
    active_cm = MagicMock()
    active_cm._instance_exists.return_value = True
    active_cm.module_def.definition_ref = "/MICROSAR/CanIf"

    target_cm = MagicMock()
    target_cm._instance_exists.return_value = False
    target_cm.module_def.definition_ref = "/MICROSAR/CanTrcv_GenericCan/CanTrcv"

    container_def = MagicMock()
    container_def.short_name = "CanTrcvConfigSet"
    container_def.definition_ref = "/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvConfigSet"

    win.config_manager = active_cm
    win.project = MagicMock()
    win.project.module_managers = {
        "CanIf": active_cm,
        "CanTrcv": target_cm,
    }

    controller = EditController(win)
    with patch("autosar_configurator.ui.controllers.edit_controller.QMessageBox") as mock_msg, \
         patch("autosar_configurator.ui.controllers.edit_controller.CreateContainerCommand") as mock_cmd:
        controller.handle_create_container(container_def, None, "CanTrcvConfigSet")

    mock_msg.warning.assert_not_called()
    mock_cmd.assert_called_once_with(target_cm, container_def, None, "CanTrcvConfigSet")
