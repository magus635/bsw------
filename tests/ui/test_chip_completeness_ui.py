"""add-sc300-chip: Project Properties flags chips with incomplete data; they stay selectable."""
from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.ui.dialogs.project_properties_dialog import ProjectPropertiesDialog

COMPLETE = ChipDefinition(name="THA6206_LFBGA292", metadata={"cores": {"count": 2}},
                          ecu_resources={"OsResource": {"NumOfCores": 2}})
MARKED = ChipDefinition(name="THA610X_LFBGA180", metadata={"unconfirmed": {
    "metadata.flash_size": "SDK: PFLASH0/1 2 MB each", "ports": "placeholder"}})


def _dialog(qtbot, tmp_path, selected=None):
    db = ChipDatabase()
    db.register_chip(COMPLETE)
    db.register_chip(MARKED)
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = selected
    dialog = ProjectPropertiesDialog(project, None)
    qtbot.addWidget(dialog)
    return dialog


def _labels(dialog):
    return {dialog.chip_combo.itemData(i): dialog.chip_combo.itemText(i)
            for i in range(dialog.chip_combo.count())}


def test_incomplete_chip_is_marked_in_the_combo(qtbot, tmp_path):
    labels = _labels(_dialog(qtbot, tmp_path))
    assert labels["THA610X_LFBGA180"] == "THA610X_LFBGA180（资料不完整）"
    assert labels["THA6206_LFBGA292"] == "THA6206_LFBGA292"


def test_choosing_it_lists_the_items_and_it_can_be_applied(qtbot, tmp_path):
    dialog = _dialog(qtbot, tmp_path)
    assert dialog.completeness_label.isHidden()
    dialog.chip_combo.setCurrentIndex(dialog.chip_combo.findData("THA610X_LFBGA180"))
    text = dialog.completeness_label.text()
    assert not dialog.completeness_label.isHidden()
    assert "metadata.flash_size 待确认：SDK: PFLASH0/1 2 MB each" in text
    assert "ports 待确认：placeholder" in text
    assert dialog.get_data()["selected_chip"] == "THA610X_LFBGA180"

    dialog.chip_combo.setCurrentIndex(dialog.chip_combo.findData("THA6206_LFBGA292"))
    assert dialog.completeness_label.isHidden()


def test_selected_incomplete_chip_is_shown_on_open(qtbot, tmp_path):
    dialog = _dialog(qtbot, tmp_path, selected="THA610X_LFBGA180")
    assert dialog.chip_combo.currentData() == "THA610X_LFBGA180"
    assert not dialog.completeness_label.isHidden()
