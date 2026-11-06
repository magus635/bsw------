"""A parameter whose definition asks for HEX is shown and read back in hex."""
import pytest
from PySide6.QtWidgets import QLineEdit, QSpinBox

from autosar_configurator.core.model.definition_model import EcucParameterDef, EcucParameterType
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel

UNSET = "(未配置)"


@pytest.fixture
def panel(qtbot):
    widget = DaVinciConfigPanel()
    qtbot.addWidget(widget)
    return widget


def _param(**kw):
    kw.setdefault("definition_ref", "/V/M/G/P")
    kw.setdefault("lower_multiplicity", 0)
    return EcucParameterDef(short_name="P", param_type=EcucParameterType.INTEGER, **kw)


def test_hex_range_shows_and_reads_hex(panel):
    """A 64-bit address range keeps the free-text editor, now in hex."""
    widget, getter, _ = panel._create_single_value_editor(
        "P", _param(min_value=0, max_value=18446744073709551615, display_format="HEX"), 0x30000000)
    assert isinstance(widget, QLineEdit)
    assert widget.text() == "0x30000000"
    assert getter() == "0x30000000"


def test_hex_text_is_read_back_unchanged(panel):
    widget, getter, _ = panel._create_single_value_editor(
        "P", _param(min_value=0, max_value=18446744073709551615, display_format="HEX"), None)
    widget.setText("0x10000")
    assert getter() == "0x10000"


def test_an_unset_hex_parameter_still_reads_as_unset(panel):
    widget, getter, _ = panel._create_single_value_editor(
        "P", _param(min_value=0, max_value=18446744073709551615, display_format="HEX"), None)
    assert widget.text() == ""
    assert getter() == UNSET


def test_hex_within_32_bit_uses_a_spin_box_in_hex(panel):
    widget, getter, _ = panel._create_single_value_editor(
        "P", _param(min_value=0, max_value=4294967295), 0x10000)
    # 4294967295 exceeds the signed 32-bit limit -> free text
    assert isinstance(widget, QLineEdit)


def test_a_small_hex_parameter_uses_a_hex_spin_box(panel):
    widget, getter, _ = panel._create_single_value_editor(
        "P", _param(min_value=0, max_value=0xFFFF, display_format="HEX"), 0x1000)
    assert isinstance(widget, QSpinBox)
    assert widget.displayIntegerBase() == 16
    assert widget.text().lower() in ("1000", "0x1000")
    assert getter() == 0x1000


def test_a_decimal_parameter_keeps_decimal(panel):
    widget, getter, _ = panel._create_single_value_editor(
        "P", _param(min_value=0, max_value=10), 5)
    assert isinstance(widget, QSpinBox)
    assert widget.displayIntegerBase() == 10
    assert widget.text() == "5"
