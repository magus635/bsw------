"""show-out-of-range-enum-value: the enumeration editor shows the stored value as it is."""
from pathlib import Path

import pytest

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel

PORT_XDM = (Path(__file__).resolve().parent.parent.parent
            / "test_import_project/Def/plugins/Port_THA6_AS440/config/Port.xdm")
MARK = "（不在可选范围）"


@pytest.fixture
def panel(qtbot):
    widget = DaVinciConfigPanel()
    qtbot.addWidget(widget)
    return widget


@pytest.fixture(scope="module")
def pin_params():
    module = EcucDefParser().parse_module_def_file(PORT_XDM)
    return module.containers["PortConfigSet"].sub_containers["PortContainer"].sub_containers["PortPin"].parameters


def _items(combo):
    return [combo.itemText(i) for i in range(combo.count())]


def test_stored_value_outside_the_options_is_shown_marked(panel, pin_params):
    combo, getter, _ = panel._create_single_value_editor("PortPinMode", pin_params["PortPinMode"],
                                                         "PORT_PIN_MODE_GPIO")
    assert combo.currentText() == "PORT_PIN_MODE_GPIO" + MARK
    assert "PORT_PIN_MODE_ALL" in combo.toolTip()
    assert getter() == "PORT_PIN_MODE_GPIO"


def test_marked_entry_writes_back_the_stored_value(panel, pin_params):
    combo, getter, signal = panel._create_single_value_editor("PortPinMode", pin_params["PortPinMode"],
                                                              "PORT_PIN_MODE_GPIO")
    seen = []
    signal.connect(lambda *_: seen.append(getter()))
    combo.setCurrentText("PORT_PIN_MODE_ALL")
    combo.setCurrentIndex(combo.count() - 1)
    assert seen == ["PORT_PIN_MODE_ALL", "PORT_PIN_MODE_GPIO"]


@pytest.mark.parametrize("stored", ["PORT_PIN_MODE_ALL", None])
def test_valid_or_missing_value_is_unchanged(panel, pin_params, stored):
    combo, getter, _ = panel._create_single_value_editor("PortPinMode", pin_params["PortPinMode"], stored)
    assert not any(MARK in text for text in _items(combo))
    assert combo.toolTip() == ""
    assert getter() == (stored if stored else combo.itemText(0))


def test_value_removed_by_the_chip_constraint_is_shown(panel, pin_params):
    class Service:
        def get_enum_constraint(self, path):
            return ["PORT_PIN_MODE_ALL"]

        def get_all_constraints(self):
            return {}

    panel.chip_constraint_service = Service()
    panel._get_allowed_literals = lambda *a, **k: ["OTHER"]      # filters every literal away
    combo, getter, _ = panel._create_single_value_editor("PortPinMode", pin_params["PortPinMode"],
                                                         "PORT_PIN_MODE_ALL")
    assert combo.currentText() == "PORT_PIN_MODE_ALL"
    assert getter() == "PORT_PIN_MODE_ALL"


def test_no_options_at_all_shows_the_value_without_a_mark(panel, pin_params):
    # PortPinInitialMode takes its range from ECU data at run time: no static literals
    combo, getter, _ = panel._create_single_value_editor("PortPinInitialMode",
                                                         pin_params["PortPinInitialMode"], "CAN10_TXD")
    assert combo.currentText() == "CAN10_TXD"
    assert getter() == "CAN10_TXD"
