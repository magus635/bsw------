"""The panel shows a parameter without a value as "(未配置)", not as its first option or 0."""
import pytest
from PySide6.QtWidgets import QComboBox, QDoubleSpinBox, QSpinBox

from autosar_configurator.core.model.definition_model import EcucParameterDef, EcucParameterType
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel

UNSET = "(未配置)"


@pytest.fixture
def panel(qtbot):
    widget = DaVinciConfigPanel()
    qtbot.addWidget(widget)
    return widget


def _param(kind, required=True, **kw):
    return EcucParameterDef(short_name="P", param_type=kind, definition_ref="/V/M/G/P",
                            lower_multiplicity=1 if required else 0, **kw)


def test_required_enum_without_value_shows_unset(panel):
    combo, getter, _ = panel._create_single_value_editor(
        "P", _param(EcucParameterType.ENUMERATION, literals=["A", "B"]), None)
    assert combo.currentText() == UNSET
    combo.setCurrentText("B")
    assert getter() == "B"


def test_required_enum_with_value_offers_no_unset_entry(panel):
    combo, _, _ = panel._create_single_value_editor(
        "P", _param(EcucParameterType.ENUMERATION, literals=["A", "B"]), "B")
    assert combo.currentText() == "B"
    assert [combo.itemText(i) for i in range(combo.count())] == ["A", "B"]


@pytest.mark.parametrize("required", [True, False])
def test_integer_without_value_shows_unset_and_reads_back_as_unset(panel, required):
    spin, getter, _ = panel._create_single_value_editor(
        "P", _param(EcucParameterType.INTEGER, required, min_value=1, max_value=10), None)
    assert isinstance(spin, QSpinBox)
    assert spin.text() == UNSET
    assert getter() == UNSET
    spin.setValue(1)
    assert getter() == 1


def test_integer_with_value_is_shown_as_it_is(panel):
    spin, getter, _ = panel._create_single_value_editor(
        "P", _param(EcucParameterType.INTEGER, min_value=1, max_value=10), 1)
    assert spin.value() == 1 and spin.text() == "1"
    assert getter() == 1


def test_float_without_value_shows_unset(panel):
    spin, getter, _ = panel._create_single_value_editor(
        "P", _param(EcucParameterType.FLOAT, min_value=0.0, max_value=5.0), None)
    assert isinstance(spin, QDoubleSpinBox)
    assert spin.text() == UNSET
    assert getter() == UNSET
    spin.setValue(2.5)
    assert getter() == 2.5
