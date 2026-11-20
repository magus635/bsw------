from unittest.mock import MagicMock
from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView


def test_get_instances_for_def_uses_target_config_manager_module_name(qapp):
    """Reproduce bug: _definition_refs_match used self.config_manager instead of target config_manager."""
    tree = DaVinciTreeView()

    # Active config_manager is CanIf, NOT CanTrcv
    canif_cm = MagicMock()
    canif_cm.module_def.short_name = "CanIf"
    tree.config_manager = canif_cm
    tree.module_def = None

    # Target config_manager is CanTrcv
    cantrcv_cm = MagicMock()
    cantrcv_cm.module_def.short_name = "CanTrcv"

    inst = MagicMock()
    inst.short_name = "CanTrcvConfigSet"
    inst.definition_ref = "/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvConfigSet"
    inst.variant = None
    cantrcv_cm.configuration.containers = [inst]

    container_def = MagicMock()
    container_def.short_name = "CanTrcvConfigSet"
    container_def.definition_ref = "/AUTOSAR/EcucDefs/CanTrcv/CanTrcvConfigSet"

    instances = tree._get_instances_for_def(container_def, cantrcv_cm)
    assert len(instances) == 1
    assert instances[0] is inst

