"""add-chip-ports-from-ecu-resources: the designer generates the pin table from ECU resources."""
import pytest

from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition, PortPinDef
from autosar_configurator.ui.dialogs import chip_definition_designer_dialog as designer

PORT = {"Port": {"AvailablePortsID": "_0_ _10_", "Port0_AvailablePins": "_0_ _1_",
                 "Port10_AvailablePins": "_0_ _13_", "OutputModesXDM0": "GPIO A",
                 "InputModesXDMad": "GPIO B"}}
DEMO = {"PORT_A": [PortPinDef(name="PA0", port="PORT_A", pin=0)],
        "PORT_B": [PortPinDef(name="PB0", port="PORT_B", pin=0)]}


@pytest.fixture
def asked(monkeypatch):
    state = {"questions": [], "infos": [], "answer": designer.QMessageBox.No}

    def question(*a, **k):
        state["questions"].append(a[2])
        return state["answer"]

    monkeypatch.setattr(designer.QMessageBox, "question", question)
    monkeypatch.setattr(designer.QMessageBox, "information", lambda *a, **k: state["infos"].append(a[2]))
    return state


def _dialog(qtbot, ports=None, ecu=PORT):
    db = ChipDatabase()
    db.register_chip(ChipDefinition(name="C", ports=ports or {}, ecu_resources=ecu))
    dialog = designer.ChipDefinitionDesignerDialog(chip_database=db, initial_chip="C")
    qtbot.addWidget(dialog)
    return dialog


def _ports(dialog):
    return {port: [p.pin for p in pins] for port, pins in dialog.pin_model.ports_dict().items()}


def test_confirmed_replacement(qtbot, asked):
    dialog = _dialog(qtbot, DEMO)
    asked["answer"] = designer.QMessageBox.Yes
    dialog._on_derive_pins_clicked()
    assert "2 个端口、2 个引脚" in asked["questions"][0] and "2 个端口、4 个引脚" in asked["questions"][0]
    assert _ports(dialog) == {"P00": [0, 1], "P10": [0, 13]}
    assert dialog.pin_model.ports_dict()["P10"][1].alternate_functions == ["GPIO", "B"]
    assert dialog.pin_warning_label.isHidden()


def test_declined_replacement(qtbot, asked):
    dialog = _dialog(qtbot, DEMO)
    dialog._on_derive_pins_clicked()
    assert asked["questions"]
    assert _ports(dialog) == {"PORT_A": [0], "PORT_B": [0]}


def test_empty_pin_table_applied_without_asking(qtbot, asked):
    dialog = _dialog(qtbot)
    dialog._on_derive_pins_clicked()
    assert asked["questions"] == []
    assert _ports(dialog) == {"P00": [0, 1], "P10": [0, 13]}


def test_no_port_data(qtbot, asked):
    dialog = _dialog(qtbot, DEMO, ecu={"Mcu": {"A": 1}})
    dialog._on_derive_pins_clicked()
    assert asked["infos"] and _ports(dialog) == {"PORT_A": [0], "PORT_B": [0]}


def test_warning_for_demo_pins_on_pin_and_preview_pages(qtbot, asked):
    dialog = _dialog(qtbot, DEMO)
    assert not dialog.pin_warning_label.isHidden()
    # PORT_A is port 0 (declared); PORT_B is port 1, not in Port.AvailablePortsID (0, 10)
    assert dialog.pin_warning_label.text().splitlines() == [
        "⚠ pin table lacks ports of Port.AvailablePortsID: P10",
        "⚠ pin table has ports not in Port.AvailablePortsID: PORT_B"]
    dialog.tabs.setCurrentIndex(4)
    assert "pin table lacks ports" in dialog.consistency_label.text()
