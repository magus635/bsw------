from unittest.mock import MagicMock
from autosar_configurator.core.workspace_manager import WorkspaceProject


def test_get_instance_by_path_resolves_active_ecuc_module_root():
    """Reproduce bug: /ActiveEcuC/<Module> module root references fail to resolve."""
    project = WorkspaceProject(name="StartApplication")
    os_mgr = MagicMock()
    os_mgr.configuration.short_name = "Os"
    os_mgr.configuration.definition_ref = "/MICROSAR/Os"
    os_mgr.configuration.get_instance_by_path.return_value = None

    project.module_managers = {"Os": os_mgr}

    target = project.get_instance_by_path("/ActiveEcuC/Os")
    assert target is not None
    assert target.short_name == "Os"
    assert target.module_name == "Os"
