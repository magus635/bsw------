"""Designer: unsaved edits are not dropped silently; core fields stay consistent."""
import pytest
from PySide6.QtWidgets import QMessageBox

from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

CHIP = ("name: CHIP_X\nresource_version: 2.0.0\n"
        "metadata:\n  cores: {count: 2, available: [CORE0, CORE1], master: CORE0}\n")
OTHER = "name: CHIP_Y\ndescription: other chip\n"


@pytest.fixture
def ask(monkeypatch):
    state = {"questions": [], "answer": QMessageBox.No}
    for kind in ("information", "warning", "critical"):
        monkeypatch.setattr(QMessageBox, kind, lambda *a, **k: QMessageBox.Ok)

    def question(*a, **k):
        if a[1] == "引脚表为空":           # the test chips have no pins; not what is tested here
            return QMessageBox.Yes
        state["questions"].append((a[1], a[2]))
        return state["answer"]

    monkeypatch.setattr(QMessageBox, "question", question)
    return state


@pytest.fixture
def dialog(qtbot, tmp_path):
    (tmp_path / "CHIP_X.yaml").write_text(CHIP, encoding="utf-8")
    (tmp_path / "CHIP_Y.yaml").write_text(OTHER, encoding="utf-8")
    dlg = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="CHIP_X")
    qtbot.addWidget(dlg)
    finished = []
    dlg.finished.connect(finished.append)
    dlg.finished_codes = finished
    return dlg


# --- closing -----------------------------------------------------------------------

def test_close_without_edits_asks_nothing(dialog, ask):
    dialog.reject()
    assert ask["questions"] == []
    assert dialog.finished_codes == [0]


def test_close_with_edits_asks_and_no_keeps_the_dialog_open(dialog, ask):
    dialog.desc_edit.setPlainText("edited")
    dialog.reject()
    assert [q[0] for q in ask["questions"]] == ["放弃未保存的修改"]
    assert dialog.finished_codes == []
    assert dialog.desc_edit.toPlainText() == "edited"


def test_close_with_edits_and_yes_closes(dialog, ask):
    dialog.desc_edit.setPlainText("edited")
    ask["answer"] = QMessageBox.Yes
    dialog.reject()
    assert dialog.finished_codes == [0]


# --- cloning -----------------------------------------------------------------------

def _clone(dialog, name):
    dialog.clone_combo.setCurrentIndex(dialog.clone_combo.findData(name))
    dialog._on_clone_clicked()


def test_clone_with_edits_and_no_keeps_the_edits(dialog, ask):
    dialog.desc_edit.setPlainText("edited")
    _clone(dialog, "CHIP_Y")
    assert [q[0] for q in ask["questions"]] == ["放弃未保存的修改"]
    assert "CHIP_Y" in ask["questions"][0][1]
    assert dialog.name_edit.text() == "CHIP_X"
    assert dialog.desc_edit.toPlainText() == "edited"


def test_clone_with_edits_and_yes_loads_the_clone(dialog, ask):
    dialog.desc_edit.setPlainText("edited")
    ask["answer"] = QMessageBox.Yes
    _clone(dialog, "CHIP_Y")
    assert dialog.name_edit.text() == "CHIP_Y_COPY"
    assert dialog.desc_edit.toPlainText() == "other chip"


def test_clone_without_edits_asks_nothing(dialog, ask):
    _clone(dialog, "CHIP_Y")
    assert ask["questions"] == []
    assert dialog.name_edit.text() == "CHIP_Y_COPY"


# --- core fields -------------------------------------------------------------------

def test_core_count_follows_a_generated_list(dialog):
    dialog.core_count_spin.setValue(3)
    assert dialog.avail_cores_edit.text() == "CORE0, CORE1, CORE2"


def test_core_count_keeps_a_hand_written_list(dialog):
    dialog.avail_cores_edit.setText("CORE0, CORE2")
    dialog.core_count_spin.setValue(3)
    assert dialog.avail_cores_edit.text() == "CORE0, CORE2"


@pytest.mark.parametrize("count, cores, master, expected", [
    (3, "CORE0, CORE2", "CORE0", "CPU 核数为 3"),
    (2, "CORE0, CORE0", "CORE0", "重复"),
    (2, "CORE0, CORE1", "CORE5", "主核 CORE5"),
])
def test_inconsistent_core_fields_are_asked_about_before_saving(dialog, ask, tmp_path,
                                                                 count, cores, master, expected):
    before = (tmp_path / "CHIP_X.yaml").read_text(encoding="utf-8")
    dialog.core_count_spin.blockSignals(True)
    dialog.core_count_spin.setValue(count)
    dialog.core_count_spin.blockSignals(False)
    dialog.avail_cores_edit.setText(cores)
    dialog.master_core_edit.setText(master)
    dialog._on_save_clicked()
    titles = [q[0] for q in ask["questions"]]
    assert titles == ["核心信息不一致"]
    assert expected in ask["questions"][0][1]
    assert (tmp_path / "CHIP_X.yaml").read_text(encoding="utf-8") == before


def test_consistent_core_fields_save_without_asking(dialog, ask, tmp_path):
    dialog.core_count_spin.setValue(3)
    dialog._on_save_clicked()
    assert ask["questions"] == []
    assert ChipDatabase(tmp_path).get_chip("CHIP_X").metadata["cores"]["available"] == ["CORE0", "CORE1", "CORE2"]
