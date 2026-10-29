"""record-designer-saves-in-history: saving a library chip in the designer is a repair."""
import pytest
from PySide6.QtWidgets import QMessageBox

from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.core.hardware.chip_repair import read_history
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

CHIP = ("name: CHIP_X\nresource_version: 2.0.0\n"
        "ecu_resources:\n  OsResource:\n    NumOfCores: 2\n")


@pytest.fixture
def ask(monkeypatch):
    state = {"questions": [], "answer": QMessageBox.No}
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "critical", lambda *a, **k: QMessageBox.Ok)

    def question(*a, **k):
        state["questions"].append(a[1])
        return state["answer"] if a[1] == "文件已被改动" else QMessageBox.Yes

    monkeypatch.setattr(QMessageBox, "question", question)
    return state


def _open(qtbot, tmp_path):
    (tmp_path / "CHIP_X.yaml").write_text(CHIP, encoding="utf-8")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="CHIP_X")
    qtbot.addWidget(dialog)
    return dialog


def test_edit_and_save_writes_backup_version_and_history(qtbot, tmp_path, ask):
    dialog = _open(qtbot, tmp_path)
    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()

    assert (tmp_path / "CHIP_X.yaml.bak").is_file()
    entries = read_history(tmp_path / "CHIP_X.yaml")
    assert len(entries) == 1 and entries[0]["source"] == "设计器手工编辑"
    assert entries[0]["resource_version"] == {"old": "2.0.0", "new": "2.0.1"}
    assert ChipDatabase(tmp_path).get_chip("CHIP_X").resource_version == "2.0.1"
    assert "2.0.1" in dialog.status_label.text()


def test_second_save_continues_from_the_new_version(qtbot, tmp_path, ask):
    dialog = _open(qtbot, tmp_path)
    dialog.desc_edit.setPlainText("one")
    dialog._on_save_clicked()
    dialog.desc_edit.setPlainText("two")
    dialog._on_save_clicked()

    assert [e["resource_version"]["new"] for e in read_history(tmp_path / "CHIP_X.yaml")] == ["2.0.1", "2.0.2"]
    assert ChipDatabase(tmp_path).get_chip("CHIP_X").description == "two"


def test_save_without_changes_writes_nothing(qtbot, tmp_path, ask):
    dialog = _open(qtbot, tmp_path)
    dialog._on_save_clicked()

    assert not (tmp_path / "CHIP_X.yaml.bak").exists()
    assert read_history(tmp_path / "CHIP_X.yaml") == []
    assert ChipDatabase(tmp_path).get_chip("CHIP_X").resource_version == "2.0.0"
    assert "没有改动" in dialog.status_label.text()
    assert "没有改动" in dialog.status_label.text()


def test_new_chip_has_no_history(qtbot, tmp_path, ask):
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path))
    qtbot.addWidget(dialog)
    dialog.name_edit.setText("BRAND_NEW")
    dialog._on_save_clicked()

    assert (tmp_path / "BRAND_NEW.yaml").is_file()
    assert read_history(tmp_path / "BRAND_NEW.yaml") == []


def test_file_changed_outside_asks_and_cancel_keeps_it(qtbot, tmp_path, ask):
    dialog = _open(qtbot, tmp_path)
    outside = CHIP.replace("NumOfCores: 2", "NumOfCores: 4")
    (tmp_path / "CHIP_X.yaml").write_text(outside, encoding="utf-8")
    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()

    assert "文件已被改动" in ask["questions"]
    assert (tmp_path / "CHIP_X.yaml").read_text(encoding="utf-8") == outside


def test_file_changed_outside_can_be_overwritten_without_history(qtbot, tmp_path, ask):
    ask["answer"] = QMessageBox.Yes
    dialog = _open(qtbot, tmp_path)
    (tmp_path / "CHIP_X.yaml").write_text(CHIP.replace("NumOfCores: 2", "NumOfCores: 4"), encoding="utf-8")
    dialog.desc_edit.setPlainText("edited")
    dialog._on_save_clicked()

    assert ChipDatabase(tmp_path).get_chip("CHIP_X").description == "edited"
    assert read_history(tmp_path / "CHIP_X.yaml") == []


# --- mark-chip-entries-to-fill-in ----------------------------------------------------

def test_entry_added_by_the_guide_is_marked_until_filled(qtbot, tmp_path, ask):
    from autosar_configurator.core.hardware.chip_completeness import unconfirmed_marks
    from autosar_configurator.core.hardware.chip_repair import FILLED_NOTE, TO_FILL_IN

    field = "ecu_resources.Os.Missing"
    dialog = _open(qtbot, tmp_path)
    assert dialog.ecu_editor.add_placeholders(["Os.Missing"]) == 1
    dialog._on_save_clicked()
    assert "ECU 资源待填写" in ask["questions"]
    chip = ChipDatabase(tmp_path).get_chip("CHIP_X")
    assert chip.ecu_resources["Os"] == {"Missing": None}
    assert unconfirmed_marks(chip) == {field: TO_FILL_IN}
    assert read_history(tmp_path / "CHIP_X.yaml")[-1]["marked"] == [{"field": field, "note": TO_FILL_IN}]

    assert dialog.ecu_editor._select("Os", "Missing")
    dialog.ecu_editor.scalar_edit.setText("3")
    dialog.ecu_editor._apply_scalar()
    dialog._on_save_clicked()
    chip = ChipDatabase(tmp_path).get_chip("CHIP_X")
    assert chip.ecu_resources["Os"]["Missing"] == 3
    assert "unconfirmed" not in chip.metadata
    assert read_history(tmp_path / "CHIP_X.yaml")[-1]["confirmed"] == [{"field": field, "note": FILLED_NOTE}]


def test_loaded_empty_values_are_not_marked(qtbot, tmp_path, ask):
    (tmp_path / "CHIP_X.yaml").write_text(CHIP + "  Gtm:\n    TriggerXModule4: null\n", encoding="utf-8")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="CHIP_X")
    qtbot.addWidget(dialog)
    assert "unconfirmed" not in dialog._build_current_chip().metadata
