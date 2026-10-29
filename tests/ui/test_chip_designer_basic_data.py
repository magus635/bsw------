"""improve-designer-chip-data: basic data, no invented values, and the project's copy."""
from types import SimpleNamespace

import pytest
from PySide6.QtWidgets import QMessageBox

from autosar_configurator.core.hardware.chip_completeness import check_chip, unconfirmed_marks
from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.core.hardware.chip_repair import read_history
from autosar_configurator.core.hardware.project_chip_store import ProjectChipStore
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

CHIP = ("name: CHIP_X\nresource_version: 1.0.0\n"
        "metadata:\n  cpu_frequency: 300000000\n  flash_size: 512KB\n  ram_size: 64KB\n"
        "  cores: {count: 1, available: [CORE0], master: CORE0}\n"
        "  unconfirmed:\n    metadata.ram_size: 按 SDK 核对\n")


@pytest.fixture
def boxes(monkeypatch):
    shown = {"information": [], "warning": []}
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: shown["information"].append(a[1]))
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: shown["warning"].append(a[2]))
    monkeypatch.setattr(QMessageBox, "critical", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Yes)   # e.g. empty pin table
    return shown


@pytest.fixture
def library(tmp_path):
    lib = tmp_path / "lib"
    lib.mkdir()
    (lib / "CHIP_X.yaml").write_text(CHIP, encoding="utf-8")
    return lib


def _project(tmp_path, copy_text=None):
    store = ProjectChipStore(tmp_path / "proj")
    if copy_text is not None:
        store.directory.mkdir(parents=True, exist_ok=True)
        (store.directory / "CHIP_X.yaml").write_text(copy_text, encoding="utf-8")
    return SimpleNamespace(chip_store=store)


def _open(qtbot, library, project=None, chip="CHIP_X"):
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(library), initial_chip=chip, project=project)
    qtbot.addWidget(dialog)
    return dialog


# --- the project's copy ----------------------------------------------------------------

def test_differing_project_copy_is_named_on_load_and_after_save(qtbot, tmp_path, library, boxes):
    project = _project(tmp_path, CHIP.replace("512KB", "256KB"))
    dialog = _open(qtbot, library, project)
    assert not dialog.copy_notice_label.isHidden()
    assert "编辑的是芯片库" in dialog.copy_notice_label.text()

    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()
    assert "工程副本未更新" in boxes["information"]


def test_no_notice_without_a_project_copy(qtbot, tmp_path, library, boxes):
    dialog = _open(qtbot, library, _project(tmp_path))
    assert dialog.copy_notice_label.isHidden()
    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()
    assert "工程副本未更新" not in boxes["information"]


def test_equal_copy_shows_nothing_until_the_library_moves_on(qtbot, tmp_path, library, boxes):
    project = _project(tmp_path, (library / "CHIP_X.yaml").read_text(encoding="utf-8"))
    dialog = _open(qtbot, library, project)
    assert dialog.copy_notice_label.isHidden()
    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()          # the copy now holds the data from before the save
    assert "工程副本未更新" in boxes["information"]
    assert not dialog.copy_notice_label.isHidden()


# --- basic data ------------------------------------------------------------------------

def test_basic_fields_loaded_and_mark_shown(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    assert dialog.basic_edits["cpu_frequency"].text() == "300000000"
    assert dialog.basic_edits["flash_size"].text() == "512KB"
    assert dialog.basic_mark_labels["flash_size"].isHidden()
    assert not dialog.basic_mark_labels["ram_size"].isHidden()
    assert "按 SDK 核对" in dialog.basic_mark_labels["ram_size"].text()
    assert not dialog._has_unsaved_edits()


def test_flash_size_saved_and_listed_in_history(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.basic_edits["flash_size"].setText("4MB")
    dialog._on_save_clicked()

    saved = ChipDatabase(library).get_chip("CHIP_X")
    assert saved.metadata["flash_size"] == "4MB"
    assert saved.metadata["cpu_frequency"] == 300000000                  # type kept
    assert unconfirmed_marks(saved) == {"metadata.ram_size": "按 SDK 核对"}  # edits never confirm
    entry = read_history(library / "CHIP_X.yaml")[-1]
    assert entry["metadata"] == [{"field": "flash_size", "old": "512KB", "new": "4MB"}]


@pytest.mark.parametrize("field, text", [
    ("ram_size", "512"), ("flash_size", "4 TB"), ("cpu_frequency", "300MHz"), ("cpu_frequency", "0"),
])
def test_wrong_format_stops_the_save(qtbot, library, boxes, field, text):
    before = (library / "CHIP_X.yaml").read_text(encoding="utf-8")
    dialog = _open(qtbot, library)
    dialog.basic_edits[field].setText(text)
    dialog._on_save_clicked()
    assert len(boxes["warning"]) == 1 and f"'{text}'" in boxes["warning"][0]
    assert (library / "CHIP_X.yaml").read_text(encoding="utf-8") == before


def test_history_entry_without_basic_changes_has_empty_metadata(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()
    assert read_history(library / "CHIP_X.yaml")[-1]["metadata"] == []


# --- new chips -------------------------------------------------------------------------

def test_new_chip_saved_empty_is_marked_then_filled(qtbot, tmp_path, boxes):
    lib = tmp_path / "lib"
    lib.mkdir()
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(lib))
    qtbot.addWidget(dialog)
    dialog.name_edit.setText("NEW_CHIP")
    dialog._on_save_clicked()

    saved = ChipDatabase(lib).get_chip("NEW_CHIP")
    for field in ("cpu_frequency", "flash_size", "ram_size"):
        assert field not in saved.metadata
    assert unconfirmed_marks(saved) == {f"metadata.{f}": "待填写" for f in ("cpu_frequency", "flash_size", "ram_size")}
    assert {i.field for i in check_chip(saved)} >= {"metadata.flash_size"}
    assert dialog.basic_mark_labels["flash_size"].text() == "⚠ 待填写"

    dialog.basic_edits["flash_size"].setText("2MB")
    dialog._on_save_clicked()
    saved = ChipDatabase(lib).get_chip("NEW_CHIP")
    assert saved.metadata["flash_size"] == "2MB"
    assert set(unconfirmed_marks(saved)) == {"metadata.cpu_frequency", "metadata.ram_size"}


def test_existing_chip_without_the_fields_gets_no_marks(qtbot, tmp_path, boxes):
    lib = tmp_path / "lib"
    lib.mkdir()
    (lib / "OLD.yaml").write_text("name: OLD\nmetadata:\n  cores: {count: 1, available: [CORE0], master: CORE0}\n",
                                  encoding="utf-8")
    dialog = _open(qtbot, lib, chip="OLD")
    assert unconfirmed_marks(dialog._build_current_chip()) == {}
