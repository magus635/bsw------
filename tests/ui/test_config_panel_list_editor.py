"""The list editor of multi-valued parameters opens its edit dialog and writes the value back."""
import pytest
from PySide6.QtWidgets import QDialog

from autosar_configurator.core.model.definition_model import EcucParameterDef, EcucParameterType
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel, ListEditorWidget


@pytest.fixture
def editor(qtbot, monkeypatch):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    definition = EcucParameterDef(short_name="Priority", param_type=EcucParameterType.INTEGER,
                                  upper_multiplicity=-1)
    widget = ListEditorWidget("Priority", definition, [1, 2], panel)
    qtbot.addWidget(widget)
    return widget


def _accept_with(monkeypatch, text):
    """Run the dialog: type `text` into its line edit and press OK."""
    def run(dialog):
        from PySide6.QtWidgets import QLineEdit
        edit = dialog.findChild(QLineEdit)
        edit.setText(text)
        return 1
    monkeypatch.setattr(QDialog, "exec", run)


def test_editing_an_item_writes_the_new_value(editor, monkeypatch):
    seen = []
    editor.valueChanged.connect(seen.append)
    _accept_with(monkeypatch, "7")
    editor._edit_item(editor.list_widget.item(0))
    assert editor.values == [7, 2]
    assert editor.list_widget.item(0).text() == "7"
    assert seen and seen[-1] == [7, 2]


def test_cancelled_edit_keeps_the_value(editor, monkeypatch):
    monkeypatch.setattr(QDialog, "exec", lambda dialog: 0)
    editor._edit_item(editor.list_widget.item(1))
    assert editor.values == [1, 2]


def test_add_appends_a_value_that_can_be_edited(editor, monkeypatch):
    _accept_with(monkeypatch, "9")
    editor._add_item()
    assert editor.values == [1, 2, 9]
