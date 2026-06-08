"""
Unit tests for the QUndoCommand subclasses in autosar_configurator/ui/commands.py.

These are the commands used by the live DaVinci UI (a separate system from the
legacy core/command.py CommandManager covered by tests/core/test_command.py).
Each test verifies that redo() applies the change and undo() fully reverts it,
including reverse-reference bookkeeping (SetReferenceCommand) and instance-
registry / structural consistency (Rename/Move/Create/Delete).
"""
import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucReferenceDef,
    EcucParameterType,
)
from autosar_configurator.core.model.configuration_model import EcucContainerValue
from autosar_configurator.ui.commands import (
    SetParameterCommand, SetReferenceCommand, CreateContainerCommand,
    DeleteContainerCommand, MoveContainerCommand, PasteContainerCommand,
    RenameContainerCommand,
)


MODULE_REF = "/AUTOSAR/EcucDefs/TestModule"
SRC_DEF_REF = MODULE_REF + "/SrcContainer"
TGT_DEF_REF = MODULE_REF + "/TgtContainer"
PARAM_DEF_REF = SRC_DEF_REF + "/TestParam"
REF_DEF_REF = SRC_DEF_REF + "/TestRef"


@pytest.fixture
def manager():
    """ConfigurationManager with a source container (param + reference) and a
    target container that the reference can point at."""
    module = EcucModuleDef(short_name="TestModule", definition_ref=MODULE_REF)

    src_def = EcucContainerDef(
        short_name="SrcContainer", definition_ref=SRC_DEF_REF,
        lower_multiplicity=0, upper_multiplicity=10,
    )
    src_def.add_parameter(EcucParameterDef(
        short_name="TestParam", param_type=EcucParameterType.INTEGER,
        lower_multiplicity=0, upper_multiplicity=1,
        default_value=7, definition_ref=PARAM_DEF_REF,
    ))
    src_def.add_reference(EcucReferenceDef(
        short_name="TestRef", destination_ref=TGT_DEF_REF,
        lower_multiplicity=0, upper_multiplicity=1, definition_ref=REF_DEF_REF,
    ))

    tgt_def = EcucContainerDef(
        short_name="TgtContainer", definition_ref=TGT_DEF_REF,
        lower_multiplicity=0, upper_multiplicity=10,
    )

    module.add_container(src_def)
    module.add_container(tgt_def)

    return ConfigurationManager(module)


@pytest.fixture
def src_instance(manager):
    inst = EcucContainerValue(short_name="Src_0", definition_ref=SRC_DEF_REF)
    manager.configuration.add_container(inst)
    return inst


@pytest.fixture
def tgt_instance(manager):
    inst = EcucContainerValue(short_name="Tgt_0", definition_ref=TGT_DEF_REF)
    manager.configuration.add_container(inst)
    return inst


class TestSetParameterCommand:
    def test_redo_undo(self, manager, src_instance):
        src_instance.set_parameter_value("TestParam", 10, PARAM_DEF_REF)
        cmd = SetParameterCommand(manager, src_instance, "TestParam", 99)

        cmd.redo()
        assert src_instance.parameter_values["TestParam"].value == 99

        cmd.undo()
        assert src_instance.parameter_values["TestParam"].value == 10


class TestSetReferenceCommand:
    def test_redo_undo_reverse_reference(self, manager, src_instance, tgt_instance):
        target_path = tgt_instance.get_path()
        cmd = SetReferenceCommand(manager, src_instance, "TestRef", target_path)

        cmd.redo()
        ref_value = src_instance.reference_values["TestRef"]
        assert ref_value.value_ref == target_path
        assert ref_value.target is tgt_instance
        # Reverse reference must be registered on the target
        assert ref_value in tgt_instance.referenced_by

        cmd.undo()
        # Reference cleared and reverse bookkeeping cleaned up
        assert "TestRef" not in src_instance.reference_values
        assert all(rv.value_ref != target_path for rv in tgt_instance.referenced_by)


class TestCreateAndDeleteContainerCommand:
    def test_create_redo_undo(self, manager):
        src_def = manager.module_def.get_container_def("SrcContainer")
        cmd = CreateContainerCommand(manager, src_def, None, "NewSrc")

        cmd.redo()
        created = cmd.created_instance
        assert created is not None
        assert created in manager.configuration.containers

        cmd.undo()
        assert created not in manager.configuration.containers

        # redo again must restore the SAME object (so other stacked commands stay valid)
        cmd.redo()
        assert cmd.created_instance is created
        assert created in manager.configuration.containers

    def test_delete_redo_undo(self, manager, src_instance):
        cmd = DeleteContainerCommand(manager, src_instance, None)

        cmd.redo()
        assert src_instance not in manager.configuration.containers

        cmd.undo()
        assert src_instance in manager.configuration.containers


class TestMoveContainerCommand:
    def test_move_to_parent_and_back(self, manager, src_instance, tgt_instance):
        # Move src under tgt at index 0, then undo back to top level
        cmd = MoveContainerCommand(manager, src_instance, tgt_instance, 0)

        cmd.redo()
        assert src_instance in tgt_instance.sub_containers
        assert src_instance not in manager.configuration.containers
        assert src_instance.parent is tgt_instance

        cmd.undo()
        assert src_instance not in tgt_instance.sub_containers
        assert src_instance in manager.configuration.containers
        assert src_instance.parent is None


class TestPasteContainerCommand:
    def test_paste_redo_undo(self, manager):
        new_inst = EcucContainerValue(short_name="Pasted_0", definition_ref=SRC_DEF_REF)
        cmd = PasteContainerCommand(manager, None, new_inst)

        cmd.redo()
        assert new_inst in manager.configuration.containers

        cmd.undo()
        assert new_inst not in manager.configuration.containers


class TestRenameContainerCommand:
    def test_rename_redo_undo(self, manager, src_instance):
        old_name = src_instance.short_name
        cmd = RenameContainerCommand(manager, src_instance, "Renamed_0")

        cmd.redo()
        assert src_instance.short_name == "Renamed_0"
        assert manager.configuration.is_modified

        cmd.undo()
        assert src_instance.short_name == old_name

    def test_rename_with_none_config_manager_raises(self, src_instance):
        # Guards in the UI layer must resolve a real manager; a None manager
        # would crash on configuration access — documents the UI-4 contract.
        cmd = RenameContainerCommand(None, src_instance, "X")
        with pytest.raises(AttributeError):
            cmd.redo()
