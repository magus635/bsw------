"""ECU resource editor page of the chip definition designer."""
import time
from pathlib import Path

import pytest
from PySide6.QtWidgets import QFileDialog, QInputDialog, QMessageBox

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.ecu_resource_data import flatten_ecu_resources
from autosar_configurator.ui.dialogs import ecu_resource_editor as editor_module
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import (
    ChipDefinitionDesignerDialog,
)
from autosar_configurator.ui.dialogs.ecu_resource_editor import EcuResourceEditor

FIXTURES = Path(__file__).resolve().parent.parent / "fixtures" / "ecu_resources"
OS_FILE = FIXTURES / "Os_Resource_THA6412.properties"
RES_FILE = FIXTURES / "CotexR52_THA6412_BGA516.properties"


@pytest.fixture
def messages(monkeypatch):
    """Record warnings; answer questions with Yes."""
    seen = {"warning": [], "info": []}
    monkeypatch.setattr(QMessageBox, "warning",
                        lambda *a, **k: seen["warning"].append(a[2]) or QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "information",
                        lambda *a, **k: seen["info"].append(a[2]) or QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Yes)
    return seen


def _editor(qtbot, resources):
    editor = EcuResourceEditor()
    qtbot.addWidget(editor)
    editor.set_resources(resources)
    return editor


def _select(editor, module, name):
    assert editor._select(module, name)


def _visible_keys(editor):
    keys = []
    for i in range(editor.tree.topLevelItemCount()):
        top = editor.tree.topLevelItem(i)
        for j in range(top.childCount()):
            child = top.child(j)
            if not child.isHidden() and not top.isHidden():
                module, name = child.data(0, 256)
                keys.append(f"{module}.{name}")
    return keys


# --- 2.x editing ---------------------------------------------------------------

def test_scalar_edit_is_stored_and_reported(qtbot, messages):
    editor = _editor(qtbot, {"OsResource": {"NumOfCores": 2}})
    _select(editor, "OsResource", "NumOfCores")
    with qtbot.waitSignal(editor.changed):
        editor.scalar_edit.setText("4")
        editor._apply_scalar()
    assert editor.resources() == {"OsResource": {"NumOfCores": 4}}


def test_type_is_inferred_and_can_be_kept_as_string(qtbot, messages):
    editor = _editor(qtbot, {"Mcu": {"A": 1, "B": 1}})
    _select(editor, "Mcu", "A")
    editor.scalar_edit.setText("0x10")
    assert "int" in editor.inferred_label.text()
    editor._apply_scalar()
    _select(editor, "Mcu", "B")
    editor.scalar_edit.setText("007")
    editor.keep_string_check.setChecked(True)
    editor._apply_scalar()
    assert editor.resources()["Mcu"] == {"A": 16, "B": "007"}


def test_add_module_and_key_and_list_value(qtbot, messages, monkeypatch):
    editor = _editor(qtbot, {})
    answers = iter([("Gtm", True), ("Tom0Channel0", True)])
    monkeypatch.setattr(QInputDialog, "getText", lambda *a, **k: next(answers))
    editor._add_module()
    editor._add_key()
    assert editor.resources() == {"Gtm": {"Tom0Channel0": None}}

    _select(editor, "Gtm", "Tom0Channel0")
    editor.scalar_edit.setText("TOM00CH00")
    editor._scalar_to_list()
    _select(editor, "Gtm", "Tom0Channel0")
    editor._list_add_row()
    editor.list_table.item(1, 0).setText("TOM00CH01")
    editor._apply_list()
    assert editor.resources()["Gtm"]["Tom0Channel0"] == ["TOM00CH00", "TOM00CH01"]


def test_invalid_names_are_refused_and_data_unchanged(qtbot, messages, monkeypatch):
    editor = _editor(qtbot, {"Os": {"A": 1}})
    monkeypatch.setattr(QInputDialog, "getText", lambda *a, **k: ("Os.X", True))
    editor._add_module()
    assert editor.resources() == {"Os": {"A": 1}}
    assert messages["warning"]

    monkeypatch.setattr(QInputDialog, "getText", lambda *a, **k: ("", True))
    editor._select("Os", None)
    editor._add_key()
    assert editor.resources() == {"Os": {"A": 1}}


def test_invalid_list_item_is_not_written(qtbot, messages):
    editor = _editor(qtbot, {"Os": {"L": ["a", "b"]}})
    _select(editor, "Os", "L")
    editor.list_table.item(0, 0).setText("")
    editor._apply_list()
    assert editor.resources() == {"Os": {"L": ["a", "b"]}}
    assert messages["warning"] and "empty" in messages["warning"][-1]


def test_rename_and_delete_keep_order(qtbot, messages, monkeypatch):
    editor = _editor(qtbot, {"M": {"a": 1, "b": 2, "c": 3}})
    _select(editor, "M", "b")
    monkeypatch.setattr(QInputDialog, "getText", lambda *a, **k: ("z", True))
    editor._rename()
    assert list(editor.resources()["M"]) == ["a", "z", "c"]
    _select(editor, "M", "a")
    editor._delete()
    assert list(editor.resources()["M"]) == ["z", "c"]


def test_leading_space_of_a_string_value_survives_other_edits(qtbot, messages):
    value = " ASI0_ATX ASI10_ATX ASI11_ATX"
    editor = _editor(qtbot, {"Port": {"OutputModesXDMxx": value, "N": 1}})
    _select(editor, "Port", "OutputModesXDMxx")
    assert editor.stack.currentIndex() == 2             # multi-line editor, not the stripped one
    _select(editor, "Port", "N")
    editor.scalar_edit.setText("2")
    editor._apply_scalar()
    assert editor.resources()["Port"]["OutputModesXDMxx"] == value
    _select(editor, "Port", "OutputModesXDMxx")
    editor._apply_text()                                # applying unchanged text keeps the space
    assert editor.resources()["Port"]["OutputModesXDMxx"] == value


# --- search and filters ----------------------------------------------------------

def test_search_by_key_and_by_value(qtbot):
    editor = _editor(qtbot, {"Os": {"IsrTriggerMethodList": [1, 2], "Other": "hello"},
                             "Mcu": {"PllFreq": 80}})
    editor.search_edit.setText("IsrTrigger")
    assert _visible_keys(editor) == ["Os.IsrTriggerMethodList"]
    editor.search_edit.setText("hello")
    assert _visible_keys(editor) == ["Os.Other"]
    editor.search_edit.setText("")
    assert len(_visible_keys(editor)) == 3


def test_filter_entries_to_fill_in_and_with_problems(qtbot):
    editor = _editor(qtbot, {
        "Os": {"Empty": None, "Fine": 1},
        "OsResource": {"NumOfCores": 4, "AvailableCores": ["CORE0", "CORE1"]},
    })
    editor.filter_combo.setCurrentIndex(1)
    assert _visible_keys(editor) == ["Os.Empty"]
    editor.filter_combo.setCurrentIndex(2)
    assert set(_visible_keys(editor)) == {"OsResource.NumOfCores", "OsResource.AvailableCores"}
    assert "OsResource.NumOfCores" in editor.hint_label.text()


# --- 3.x range view -----------------------------------------------------------------

def _isr_list():
    return [1] * 16 + [2] * 3 + [4] * 3 + [2] * 970          # 992 elements


def test_range_view_edit_changes_only_that_range(qtbot, messages):
    values = _isr_list()
    editor = _editor(qtbot, {"Os": {"IsrTriggerMethodList": values}})
    _select(editor, "Os", "IsrTriggerMethodList")
    editor.range_view_btn.setChecked(True)
    assert editor.list_table.rowCount() == 4
    assert editor.list_table.item(1, 0).text() == "16-18"
    editor.list_table.item(1, 1).setText("3")
    editor._apply_list()
    edited = editor.resources()["Os"]["IsrTriggerMethodList"]
    assert len(edited) == 992
    assert edited[16:19] == [3, 3, 3]
    assert edited[:16] == values[:16] and edited[19:] == values[19:]


def test_range_gap_is_rejected_and_previous_list_kept(qtbot, messages):
    values = _isr_list()
    editor = _editor(qtbot, {"Os": {"IsrTriggerMethodList": values}})
    _select(editor, "Os", "IsrTriggerMethodList")
    editor.range_view_btn.setChecked(True)
    editor.list_table.item(1, 0).setText("17-18")               # index 16 is now covered by nothing
    editor._apply_list()
    assert editor.resources()["Os"]["IsrTriggerMethodList"] == values
    assert "missing index 16" in messages["warning"][-1]


def test_switching_views_does_not_change_the_value(qtbot, messages):
    values = _isr_list()
    editor = _editor(qtbot, {"Os": {"IsrTriggerMethodList": values}})
    _select(editor, "Os", "IsrTriggerMethodList")
    editor.range_view_btn.setChecked(True)
    editor.range_view_btn.setChecked(False)
    assert editor.list_table.rowCount() == 992
    editor._apply_list()
    assert editor.resources()["Os"]["IsrTriggerMethodList"] == values


def test_invalid_ranges_keep_the_view_when_switching(qtbot, messages):
    editor = _editor(qtbot, {"Os": {"L": [1, 1, 2]}})
    _select(editor, "Os", "L")
    editor.range_view_btn.setChecked(True)
    editor.list_table.item(0, 0).setText("5-6")
    editor.range_view_btn.setChecked(False)               # cannot expand: stays in range view
    assert editor.range_view_btn.isChecked()
    assert messages["warning"]


# --- 4.x needed keys -----------------------------------------------------------------

def _plugin(root: Path, module: str, xdm: str):
    config = root / f"{module}_X" / "config"
    config.mkdir(parents=True)
    (config / f"{module}.xdm").write_text(xdm, encoding="utf-8")


def test_needed_keys_exclude_existing_and_other_chip_keys(qtbot):
    db = ChipDatabase()
    db.register_chip(ChipDefinition(name="OTHER", ecu_resources={"Port": {"OnlyOther": 1}}))
    editor = _editor(qtbot, {"Os": {"Have": 1}})
    editor.set_context(db, "MINE")
    referenced = {"Os.Have": {"Os"}, "Os.Need": {"Os"}, "Port.OnlyOther": {"Port"},
                  "OS.HAVE": {"Os"}}
    assert editor._needed_keys(referenced) == [("Os.Need", ["Os"])]


def test_directory_scan_lists_missing_keys_and_adds_placeholders(qtbot, tmp_path, monkeypatch, messages):
    _plugin(tmp_path, "Mcu", "ecu:get('Mcu.PllFreq') ecu:get(concat('Adc.', $x))")
    _plugin(tmp_path, "Os", "ecu:get('Os.Have')")
    editor = _editor(qtbot, {"Os": {"Have": 1}})
    editor.set_context(ChipDatabase(), "MINE")
    monkeypatch.setattr(QFileDialog, "getExistingDirectory", lambda *a, **k: str(tmp_path))

    class FakeDialog:
        listed = None

        def __init__(self, keys, parent=None):
            FakeDialog.listed = keys

        def exec(self):
            return True

        def selected_keys(self):
            return [k for k, _ in FakeDialog.listed]

    monkeypatch.setattr(editor_module, "NeededKeysDialog", FakeDialog)
    editor._scan_directory()
    assert FakeDialog.listed == [("Mcu.PllFreq", ["Mcu"])]        # dynamic key not listed
    assert editor.resources()["Mcu"] == {"PllFreq": None}
    editor.filter_combo.setCurrentIndex(1)
    assert _visible_keys(editor) == ["Mcu.PllFreq"]


def test_directory_scan_with_nothing_missing_says_so(qtbot, tmp_path, monkeypatch, messages):
    _plugin(tmp_path, "Os", "ecu:get('Os.Have')")
    editor = _editor(qtbot, {"Os": {"Have": 1}})
    monkeypatch.setattr(QFileDialog, "getExistingDirectory", lambda *a, **k: str(tmp_path))
    editor._scan_directory()
    assert messages["info"] and "concatenation" in messages["info"][-1]


# --- designer integration ---------------------------------------------------------------

def _designer(qtbot, tmp_path, **chips):
    for name, yaml_text in chips.items():
        (tmp_path / f"{name}.yaml").write_text(yaml_text, encoding="utf-8")
    db = ChipDatabase(tmp_path)
    dialog = ChipDefinitionDesignerDialog(chip_database=db)
    qtbot.addWidget(dialog)
    return dialog, db


def test_edit_in_the_page_is_saved_to_yaml(qtbot, tmp_path, messages):
    dialog, _ = _designer(qtbot, tmp_path)
    dialog.name_edit.setText("MY_CHIP")
    editor = dialog.ecu_editor
    editor.set_resources({"OsResource": {"NumOfCores": 2}})
    _select(editor, "OsResource", "NumOfCores")
    editor.scalar_edit.setText("4")
    editor._apply_scalar()
    editor._select("OsResource", None)
    dialog._on_save_clicked()
    assert ChipDatabase(tmp_path).get_chip("MY_CHIP").ecu_resources == {
        "OsResource": {"NumOfCores": 4}}


def test_saving_with_entries_to_fill_in_asks_first(qtbot, tmp_path, monkeypatch):
    asked = []
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: QMessageBox.Ok)
    # first save: empty pin table -> yes, entries to fill in -> no; second save: both yes
    answers = iter([QMessageBox.Yes, QMessageBox.No, QMessageBox.Yes, QMessageBox.Yes])

    def question(*a, **k):
        asked.append(a[2])
        return next(answers)

    monkeypatch.setattr(QMessageBox, "question", question)
    dialog, _ = _designer(qtbot, tmp_path)
    dialog.name_edit.setText("MY_CHIP")
    dialog._set_ecu_resources({"Mcu": {"PllFreq": None, "Ok": 1}})
    dialog._on_save_clicked()                          # pins: yes, fill-in: no -> not saved
    assert not (tmp_path / "MY_CHIP.yaml").exists()
    assert any("1 个 ECU 资源条目" in text for text in asked)
    assert dialog.tabs.currentIndex() == 3
    dialog._on_save_clicked()                          # fill-in: yes -> saved with the empty value
    assert ChipDatabase(tmp_path).get_chip("MY_CHIP").ecu_resources == {
        "Mcu": {"PllFreq": None, "Ok": 1}}


def test_preview_page_labels_the_fallback_and_shows_consistency(qtbot, tmp_path, messages):
    dialog, _ = _designer(qtbot, tmp_path)
    dialog.tabs.setCurrentIndex(4)
    assert dialog.prop_preview.toPlainText().startswith("# 兜底推导，非权威数据")

    dialog.ecu_editor.set_resources({
        "OsResource": {"NumOfCores": 4, "AvailableCores": ["CORE0", "CORE1", "CORE2"]}})
    dialog.ecu_editor.changed.emit()
    dialog.tabs.setCurrentIndex(0)
    dialog.tabs.setCurrentIndex(4)
    assert not dialog.prop_preview.toPlainText().startswith("# 兜底推导")
    assert "OsResource.NumOfCores" in dialog.consistency_label.text()
    assert "OsResource.NumOfCores" in dialog.ecu_editor.hint_label.text()


def test_import_fills_the_page_and_the_page_keeps_scrolling_data(qtbot, tmp_path, monkeypatch, messages):
    dialog, _ = _designer(qtbot, tmp_path)
    monkeypatch.setattr(QFileDialog, "getOpenFileNames", lambda *a, **k: ([str(OS_FILE)], ""))
    dialog._on_import_properties_clicked()
    flat = flatten_ecu_resources(dialog.ecu_editor.resources())
    assert flat["OsResource.NumOfCores"] == 4
    assert len(flat["Os.IsrTriggerMethodList"]) == 992


def test_designer_opened_from_a_project_can_scan_its_modules(qtbot, tmp_path):
    from autosar_configurator.core.workspace_manager import WorkspaceProject

    project = WorkspaceProject("p", tmp_path / "p.dpa")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(), project=project)
    qtbot.addWidget(dialog)
    assert dialog.ecu_editor.scan_project_btn.isEnabled()
    standalone = ChipDefinitionDesignerDialog(chip_database=ChipDatabase())
    qtbot.addWidget(standalone)
    assert not standalone.ecu_editor.scan_project_btn.isEnabled()


def test_page_copes_with_the_full_vendor_resource_file(qtbot, tmp_path):
    chip = ChipDefinition(name="BIG")
    ChipDatabase().import_ecu_resources_from_properties(chip, [RES_FILE, OS_FILE])
    editor = EcuResourceEditor()
    qtbot.addWidget(editor)
    start = time.monotonic()
    editor.set_resources(chip.ecu_resources)
    editor.search_edit.setText("Tom0Channel0")
    _select(editor, "Gtm", "Tom0Channel0")
    elapsed = time.monotonic() - start
    assert len(flatten_ecu_resources(editor.resources())) > 2400
    assert _visible_keys(editor)
    assert elapsed < 20, f"loading, filtering and opening a long list took {elapsed:.1f}s"


def test_needed_keys_dialog_returns_the_checked_keys(qtbot):
    from PySide6.QtCore import Qt

    from autosar_configurator.ui.dialogs.ecu_resource_editor import NeededKeysDialog

    dialog = NeededKeysDialog([("Mcu.A", ["Mcu"]), ("Os.B", ["Os", "Port"])])
    qtbot.addWidget(dialog)
    assert dialog.selected_keys() == []
    dialog.list.item(1).setCheckState(Qt.Checked)
    assert dialog.selected_keys() == ["Os.B"]
    dialog._check_all(Qt.Checked)
    assert dialog.selected_keys() == ["Mcu.A", "Os.B"]
