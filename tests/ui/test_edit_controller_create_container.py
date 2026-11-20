from types import SimpleNamespace
from unittest.mock import MagicMock, patch
from PySide6.QtGui import QUndoStack

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucModuleDef,
    EcucParameterDef,
    EcucParameterType,
)
from autosar_configurator.ui.controllers.edit_controller import EditController


def _make_win(active_cm, module_managers):
    """Build a minimal window stub matching DaVinciMainWindow attributes (uses current_project, no project)."""
    win = SimpleNamespace(
        config_manager=active_cm,
        current_project=SimpleNamespace(module_managers=module_managers),
        undo_stack=QUndoStack(),
        _has_unsaved_changes=False,
        statusbar=MagicMock(),
        tree_view=MagicMock(),
        config_panel=SimpleNamespace(current_instance=None, clear=MagicMock(), refresh=MagicMock()),
        dep_graph_controller=MagicMock(),
    )
    return win


def _build_bswm_and_rte():
    bswm_def = EcucModuleDef(short_name="BswM", definition_ref="/MICROSAR/BswM")
    bswm_cfg_def = EcucContainerDef(
        short_name="BswMConfig",
        lower_multiplicity=0,
        upper_multiplicity=1,
        definition_ref="/MICROSAR/BswM/BswMConfig",
    )
    bswm_def.containers["BswMConfig"] = bswm_cfg_def
    bswm_cm = ConfigurationManager(bswm_def)

    rte_def = EcucModuleDef(short_name="Rte", definition_ref="/MICROSAR/Rte")
    rte_sub_def = EcucContainerDef(
        short_name="RteSub",
        lower_multiplicity=0,
        upper_multiplicity=10,
        definition_ref="/MICROSAR/Rte/RteBswGeneral/RteSub",
    )
    rte_param_def = EcucParameterDef(
        short_name="RteVersionInfoApi",
        param_type=EcucParameterType.BOOLEAN,
        default_value=False,
        definition_ref="/MICROSAR/Rte/RteBswGeneral/RteVersionInfoApi",
    )
    rte_general_def = EcucContainerDef(
        short_name="RteBswGeneral",
        lower_multiplicity=1,
        upper_multiplicity=2,
        definition_ref="/MICROSAR/Rte/RteBswGeneral",
        parameters={"RteVersionInfoApi": rte_param_def},
        sub_containers={"RteSub": rte_sub_def},
    )
    rte_def.containers["RteBswGeneral"] = rte_general_def
    rte_cm = ConfigurationManager(rte_def)

    return bswm_cm, rte_cm, rte_general_def, rte_sub_def


def test_create_and_undo_container_in_non_active_module(qapp):
    """Creating a container in Rte while BswM is active must target rte_cm and undo cleanly."""
    bswm_cm, rte_cm, rte_general_def, _ = _build_bswm_and_rte()
    win = _make_win(bswm_cm, {"BswM": bswm_cm, "Rte": rte_cm})
    controller = EditController(win)

    with patch("autosar_configurator.ui.controllers.edit_controller.QMessageBox") as mock_msg:
        controller.handle_create_container(rte_general_def, None, "RteBswGeneral")

    mock_msg.warning.assert_not_called()
    assert len(bswm_cm.configuration.containers) == 0
    assert len(rte_cm.configuration.containers) == 1
    assert rte_cm.configuration.containers[0].definition_ref == "/MICROSAR/Rte/RteBswGeneral"

    win.undo_stack.undo()
    assert len(rte_cm.configuration.containers) == 0


def test_create_container_matches_standard_ecucdefs_ref(qapp):
    """Container defs with /AUTOSAR/EcucDefs/<Module>/... must still resolve to target module."""
    bswm_cm, _, _, _ = _build_bswm_and_rte()

    cantrcv_def = EcucModuleDef(
        short_name="CanTrcv",
        definition_ref="/MICROSAR/CanTrcv_GenericCan/CanTrcv",
    )
    cantrcv_cfg_def = EcucContainerDef(
        short_name="CanTrcvConfigSet",
        lower_multiplicity=1,
        upper_multiplicity=1,
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv/CanTrcvConfigSet",
    )
    cantrcv_def.containers["CanTrcvConfigSet"] = cantrcv_cfg_def
    cantrcv_cm = ConfigurationManager(cantrcv_def)

    win = _make_win(bswm_cm, {"BswM": bswm_cm, "CanTrcv": cantrcv_cm})
    controller = EditController(win)

    with patch("autosar_configurator.ui.controllers.edit_controller.QMessageBox") as mock_msg:
        controller.handle_create_container(cantrcv_cfg_def, None, "CanTrcvConfigSet")

    mock_msg.warning.assert_not_called()
    assert len(bswm_cm.configuration.containers) == 0
    assert len(cantrcv_cm.configuration.containers) == 1


def test_create_sub_container_resolves_via_parent_instance(qapp):
    """Creating a sub-container while another module is active must use parent's config_manager."""
    bswm_cm, rte_cm, rte_general_def, rte_sub_def = _build_bswm_and_rte()
    parent_inst = rte_cm.create_container_instance(rte_general_def, instance_name="RteBswGeneral")

    win = _make_win(bswm_cm, {"BswM": bswm_cm, "Rte": rte_cm})
    controller = EditController(win)

    with patch("autosar_configurator.ui.controllers.edit_controller.QMessageBox") as mock_msg:
        controller.handle_create_container(rte_sub_def, parent_inst, "RteSub_0")

    mock_msg.warning.assert_not_called()
    assert len(parent_inst.sub_containers) == 1
    assert parent_inst.sub_containers[0].short_name == "RteSub_0"

    win.undo_stack.undo()
    assert len(parent_inst.sub_containers) == 0


def test_delete_and_undo_container_in_non_active_module(qapp):
    """Deleting a container in Rte while BswM is active must not raise ValueError: x not in list."""
    bswm_cm, rte_cm, rte_general_def, _ = _build_bswm_and_rte()
    inst = rte_cm.create_container_instance(rte_general_def, instance_name="RteBswGeneral")

    win = _make_win(bswm_cm, {"BswM": bswm_cm, "Rte": rte_cm})
    controller = EditController(win)

    controller.handle_delete_container(inst, None)
    assert len(rte_cm.configuration.containers) == 0

    win.undo_stack.undo()
    assert len(rte_cm.configuration.containers) == 1
    assert rte_cm.configuration.containers[0] is inst


def test_rename_move_and_param_change_in_non_active_module(qapp):
    """Rename, move, and parameter change must resolve Rte's config_manager even when BswM is active."""
    bswm_cm, rte_cm, rte_general_def, _ = _build_bswm_and_rte()
    inst0 = rte_cm.create_container_instance(rte_general_def, instance_name="RteBswGeneral_0")
    inst1 = rte_cm.create_container_instance(rte_general_def, instance_name="RteBswGeneral_1")

    win = _make_win(bswm_cm, {"BswM": bswm_cm, "Rte": rte_cm})
    controller = EditController(win)

    # Parameter change in Rte
    controller.handle_parameter_change(inst0, "RteVersionInfoApi", True)
    assert inst0.parameter_values["RteVersionInfoApi"].value is True

    # Rename in Rte
    controller.handle_rename_container(inst0, "RteBswGeneral_Renamed")
    assert inst0.short_name == "RteBswGeneral_Renamed"

    # Move top-level container in Rte
    controller.handle_move_container(inst1, None, 0)
    assert rte_cm.configuration.containers == [inst1, inst0]
