"""Designer side of complete-chip-yaml-as-single-source: selectors, typed-field hints, checksum."""
import yaml
from PySide6.QtWidgets import QMessageBox, QTableWidgetItem

from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import (
    ChipDefinitionDesignerDialog,
)


def _quiet(monkeypatch):
    warnings = []
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: warnings.append(a[2]) or QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Yes)
    return warnings


def _dialog(qtbot, tmp_path, initial=None, **files):
    for name, text in files.items():
        (tmp_path / f"{name}.yaml").write_text(text, encoding="utf-8")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip=initial)
    qtbot.addWidget(dialog)
    return dialog


def _set_row(dialog, row, key, value):
    table = dialog.selectors_table
    while table.rowCount() <= row:
        table.insertRow(table.rowCount())
    table.setItem(row, 0, QTableWidgetItem(key))
    table.setItem(row, 1, QTableWidgetItem(value))


def test_selectors_are_loaded_edited_and_saved(qtbot, tmp_path, monkeypatch):
    _quiet(monkeypatch)
    dialog = _dialog(qtbot, tmp_path, "C",
                     C="name: C\nselectors:\n  Resource.ResourceSubderivative: C\n")
    assert dialog.selectors_table.rowCount() == 1
    _set_row(dialog, 1, "Os.OsResourceSubderivative", "Os_THA6412")
    dialog._on_save_clicked()
    saved = yaml.safe_load((tmp_path / "C.yaml").read_text(encoding="utf-8"))
    assert saved["selectors"] == {"Os.OsResourceSubderivative": "Os_THA6412",
                                  "Resource.ResourceSubderivative": "C"}
    assert saved["checksum"].startswith("sha256:")
    assert not ChipDatabase(tmp_path).get_chip("C").content_modified


def test_invalid_selector_row_blocks_saving(qtbot, tmp_path, monkeypatch):
    warnings = _quiet(monkeypatch)
    dialog = _dialog(qtbot, tmp_path)
    dialog.name_edit.setText("NEW")
    _set_row(dialog, 0, "NoModulePart", "x")
    dialog._on_save_clicked()
    assert not (tmp_path / "NEW.yaml").exists()
    assert warnings and "NoModulePart" in warnings[-1]
    assert dialog.tabs.currentIndex() == 0


def test_typed_fields_differ_from_ecu_resources_and_can_be_overwritten(qtbot, tmp_path, monkeypatch):
    _quiet(monkeypatch)
    dialog = _dialog(qtbot, tmp_path, "C", C=(
        "name: C\nmetadata:\n  cores: {count: 2, available: [CORE0, CORE1], master: CORE0}\n"
        "ecu_resources:\n  OsResource:\n    NumOfCores: 4\n"
        "    AvailableCores: [CORE0, CORE1, CORE2, CORE3]\n    MasterCore: OS_CORE_ID_0\n"))
    messages = dialog._refresh_typed_differences()
    assert any("NumOfCores" in m for m in messages)
    assert dialog.typed_diff_btn.isEnabled()

    dialog._overwrite_typed_fields_from_ecu()
    assert dialog.core_count_spin.value() == 4
    assert dialog.avail_cores_edit.text() == "CORE0, CORE1, CORE2, CORE3"
    assert dialog.master_core_edit.text() == "CORE0"
    assert dialog._refresh_typed_differences() == []
    assert not dialog.typed_diff_btn.isEnabled()


def test_preview_lists_typed_field_differences(qtbot, tmp_path, monkeypatch):
    _quiet(monkeypatch)
    dialog = _dialog(qtbot, tmp_path, "C", C=(
        "name: C\nmetadata:\n  cores: {count: 2, available: [CORE0, CORE1], master: CORE0}\n"
        "ecu_resources:\n  Resource:\n    NumOfCores: 4\n"))
    dialog.tabs.setCurrentIndex(4)
    assert "Resource.NumOfCores" in dialog.consistency_label.text()
