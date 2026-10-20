"""An unset optional BOOLEAN parameter shows its definition default in the check box (the value
the generator uses, e.g. OsVendorArtiTraceTask DEFAULT true), without writing it to the
configuration."""
import pytest
from PySide6.QtWidgets import QCheckBox

from autosar_configurator.core.model.configuration_model import EcucContainerValue
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucParameterDef, EcucParameterType)
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel


class _Manager:
    class configuration:
        containers = []


@pytest.fixture
def panel(qtbot):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    return panel


def _container_def():
    c = EcucContainerDef(short_name="OsOS", definition_ref="/Os/OsOS")
    for name, default in (("TraceOnByDefault", True), ("TraceOffByDefault", False), ("NoDefault", None)):
        c.parameters[name] = EcucParameterDef(
            short_name=name, param_type=EcucParameterType.BOOLEAN, definition_ref=f"/Os/OsOS/{name}",
            lower_multiplicity=0, upper_multiplicity=1, default_value=default)
    return c


def _check_boxes(panel):
    boxes = {}
    for row in range(panel.params_table.rowCount()):
        name = panel.params_table.item(row, 0).text()
        widget = panel.params_table.cellWidget(row, 1)
        box = widget.findChild(QCheckBox) if widget is not None else None
        if box is not None:
            boxes[name] = box
    return boxes


def test_unset_boolean_shows_definition_default(panel):
    instance = EcucContainerValue(short_name="OsOS", definition_ref="/Os/OsOS")
    panel.show_instance(instance, _container_def(), _Manager())
    boxes = _check_boxes(panel)
    by_name = {next(n for n in boxes if key in n): key for key in ("TraceOnByDefault", "TraceOffByDefault", "NoDefault")}
    state = {key: boxes[label].isChecked() for label, key in by_name.items()}
    assert state == {"TraceOnByDefault": True, "TraceOffByDefault": False, "NoDefault": False}
    assert instance.parameter_values == {}          # display only, nothing written


def test_configured_boolean_wins_over_default(panel):
    instance = EcucContainerValue(short_name="OsOS", definition_ref="/Os/OsOS")
    from autosar_configurator.core.model.configuration_model import EcucParameterValue
    instance.parameter_values["TraceOnByDefault"] = EcucParameterValue(
        definition_ref="/Os/OsOS/TraceOnByDefault", value=False)
    panel.show_instance(instance, _container_def(), _Manager())
    boxes = _check_boxes(panel)
    label = next(n for n in boxes if "TraceOnByDefault" in n)
    assert boxes[label].isChecked() is False
