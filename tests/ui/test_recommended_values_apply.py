"""Load Recommended Values: the Apply button of the comparison dialog writes into the right module."""
from pathlib import Path
from types import SimpleNamespace

import pytest
from PySide6.QtGui import QUndoStack
from PySide6.QtWidgets import QDialog, QFileDialog, QMessageBox, QWidget

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType,
)
from autosar_configurator.ui.controllers.project_controller import ProjectController


def _ecuc_def() -> EcucModuleDef:
    module = EcucModuleDef(short_name="EcuC", definition_ref="/MICROSAR/EcuC")
    general = EcucContainerDef(short_name="EcucGeneral", definition_ref="/MICROSAR/EcuC/EcucGeneral",
                               lower_multiplicity=1, upper_multiplicity=1)
    general.add_parameter(EcucParameterDef(
        short_name="CPUType", param_type=EcucParameterType.ENUMERATION,
        definition_ref="/MICROSAR/EcuC/EcucGeneral/CPUType",
        literals=["CPU8Bit", "CPU16Bit", "CPU32Bit", "CPU64Bit"]))
    general.add_parameter(EcucParameterDef(
        short_name="ByteOrder", param_type=EcucParameterType.ENUMERATION,
        definition_ref="/MICROSAR/EcuC/EcucGeneral/ByteOrder", literals=["BIG_ENDIAN", "LITTLE_ENDIAN"]))
    general.add_parameter(EcucParameterDef(
        short_name="DummyFunction", param_type=EcucParameterType.BOOLEAN,
        definition_ref="/MICROSAR/EcuC/EcucGeneral/DummyFunction"))
    module.add_container(general)
    return module


def _mcu_def() -> EcucModuleDef:
    module = EcucModuleDef(short_name="Mcu", definition_ref="/AUTOSAR/Mcu")
    general = EcucContainerDef(short_name="McuGeneral", definition_ref="/AUTOSAR/Mcu/McuGeneral",
                               lower_multiplicity=1, upper_multiplicity=1)
    general.add_parameter(EcucParameterDef(
        short_name="McuDevErrorDetect", param_type=EcucParameterType.BOOLEAN,
        definition_ref="/AUTOSAR/Mcu/McuGeneral/McuDevErrorDetect"))
    module.add_container(general)
    return module


def _rec_file(tmp_path: Path, textual: dict, numerical: dict = None) -> Path:
    def value(kind, dest, name, val):
        return (f"<ECUC-{kind}-PARAM-VALUE><DEFINITION-REF DEST=\"{dest}\">"
                f"/MICROSAR/EcuC/EcucGeneral/{name}</DEFINITION-REF><VALUE>{val}</VALUE></ECUC-{kind}-PARAM-VALUE>")
    params = "".join(value("TEXTUAL", "ECUC-ENUMERATION-PARAM-DEF", n, v) for n, v in textual.items())
    params += "".join(value("NUMERICAL", "ECUC-BOOLEAN-PARAM-DEF", n, v) for n, v in (numerical or {}).items())
    path = tmp_path / "EcuC_preo.arxml"
    path.write_text(f"""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"><AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
<ECUC-MODULE-CONFIGURATION-VALUES><SHORT-NAME>EcuC_Rec</SHORT-NAME>
<DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/EcuC</DEFINITION-REF><CONTAINERS>
<ECUC-CONTAINER-VALUE><SHORT-NAME>EcucGeneral</SHORT-NAME>
<DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/EcuC/EcucGeneral</DEFINITION-REF>
<PARAMETER-VALUES>{params}</PARAMETER-VALUES></ECUC-CONTAINER-VALUE>
</CONTAINERS></ECUC-MODULE-CONFIGURATION-VALUES></ELEMENTS></AR-PACKAGE></AR-PACKAGES></AUTOSAR>
""", encoding="utf-8")
    return path


class _Win(QWidget):
    pass


@pytest.fixture
def dialogs(monkeypatch):
    """Stub the file chooser, accept the comparison dialog and record the message boxes."""
    shown = SimpleNamespace(rec_file=None, info=[], warnings=[], comparison_opened=False)

    def accept(dialog):
        shown.comparison_opened = True
        return QDialog.Accepted

    monkeypatch.setattr(QFileDialog, "getOpenFileName", staticmethod(lambda *a, **k: (str(shown.rec_file), "")))
    monkeypatch.setattr(QDialog, "exec", accept)
    monkeypatch.setattr(QMessageBox, "information", staticmethod(lambda parent, title, text: shown.info.append(text)))
    monkeypatch.setattr(QMessageBox, "warning", staticmethod(lambda parent, title, text: shown.warnings.append(text)))
    return shown


def _window(qtbot, tmp_path, active, managers, variant=None):
    win = _Win()
    qtbot.addWidget(win)
    win.config_manager = active
    win.current_project = SimpleNamespace(path=tmp_path / "project.json", module_managers=managers,
                                          active_variant=variant)
    win.undo_stack = QUndoStack()
    win.selected = []
    win.tree_view = SimpleNamespace(refresh=lambda: None, select_container=win.selected.append,
                                    currentItem=lambda: None)
    win.statusbar = SimpleNamespace(showMessage=lambda *a: None)
    win._has_unsaved_changes = False
    return win


def _general(manager):
    return next(c for c in manager.configuration.containers if c.short_name == "EcucGeneral")


def test_apply_writes_the_recommended_values_as_one_undo_step(qtbot, tmp_path, dialogs):
    ecuc = ConfigurationManager(_ecuc_def())
    general = ecuc.create_container_instance(ecuc.module_def.containers["EcucGeneral"])
    ecuc.set_parameter_value(general, "CPUType", "CPU64Bit")
    dialogs.rec_file = _rec_file(tmp_path, {"CPUType": "CPU32Bit"}, {"DummyFunction": "1"})
    win = _window(qtbot, tmp_path, ecuc, {"EcuC": ecuc})

    ProjectController(win).load_recommended_values()

    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert general.parameter_values["DummyFunction"].value is True
    assert dialogs.info and "Updated 2" in dialogs.info[0]
    assert win.selected == [general]
    assert win._has_unsaved_changes is True
    assert win.undo_stack.count() == 1
    win.undo_stack.undo()
    assert general.parameter_values["CPUType"].value == "CPU64Bit"


def test_rec_file_is_applied_to_its_own_module_not_the_selected_one(qtbot, tmp_path, dialogs):
    mcu = ConfigurationManager(_mcu_def())
    ecuc = ConfigurationManager(_ecuc_def())
    dialogs.rec_file = _rec_file(tmp_path, {"CPUType": "CPU32Bit"})
    win = _window(qtbot, tmp_path, mcu, {"Mcu": mcu, "EcuC": ecuc})

    ProjectController(win).load_recommended_values()

    assert _general(ecuc).parameter_values["CPUType"].value == "CPU32Bit"
    assert mcu.configuration.containers == []
    assert not dialogs.warnings


def test_a_value_that_fails_validation_is_skipped_and_reported(qtbot, tmp_path, dialogs):
    ecuc = ConfigurationManager(_ecuc_def())
    general = ecuc.create_container_instance(ecuc.module_def.containers["EcucGeneral"])
    ecuc.set_parameter_value(general, "CPUType", "CPU8Bit")
    before = general.parameter_values["CPUType"].value
    dialogs.rec_file = _rec_file(tmp_path, {"CPUType": "NOT_A_LITERAL", "ByteOrder": "LITTLE_ENDIAN"})
    win = _window(qtbot, tmp_path, ecuc, {"EcuC": ecuc})

    ProjectController(win).load_recommended_values()

    assert general.parameter_values["ByteOrder"].value == "LITTLE_ENDIAN"
    assert general.parameter_values["CPUType"].value == before
    assert "Updated 1" in dialogs.info[0]
    assert "EcucGeneral/CPUType" in dialogs.info[0]
    assert win.undo_stack.count() == 1


def test_rec_file_for_a_module_missing_from_the_project_is_refused(qtbot, tmp_path, dialogs):
    mcu = ConfigurationManager(_mcu_def())
    dialogs.rec_file = _rec_file(tmp_path, {"CPUType": "CPU32Bit"})
    win = _window(qtbot, tmp_path, mcu, {"Mcu": mcu})

    ProjectController(win).load_recommended_values()

    assert dialogs.warnings and "EcuC" in dialogs.warnings[0]
    assert dialogs.comparison_opened is False
    assert mcu.configuration.containers == []


def test_apply_writes_the_base_configuration_and_leaves_variant_overrides_alone(qtbot, tmp_path, dialogs):
    """"Default" is the base configuration; another variant's overrides are that variant's own."""
    ecuc = ConfigurationManager(_ecuc_def())
    general = ecuc.create_container_instance(ecuc.module_def.containers["EcucGeneral"])
    path = f"{general.get_path()}.CPUType"
    ecuc.configuration.variant_overrides = {"V2": {path: "CPU16Bit"}}
    dialogs.rec_file = _rec_file(tmp_path, {"CPUType": "CPU32Bit"})
    win = _window(qtbot, tmp_path, ecuc, {"EcuC": ecuc}, variant="Default")

    ProjectController(win).load_recommended_values()

    assert general.parameter_values["CPUType"].value == "CPU32Bit"
    assert ecuc.configuration.variant_overrides == {"V2": {path: "CPU16Bit"}}
    assert win.undo_stack.count() == 1
