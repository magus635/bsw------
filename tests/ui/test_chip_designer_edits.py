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
    # Freshly cloned chip with no further edits must not be marked dirty
    assert not dialog._has_unsaved_edits()
    dialog.reject()
    assert ask["questions"] == []
    assert dialog.finished_codes == [0]


def test_open_chip_loads_in_place_for_editing(dialog, ask):
    dialog.clone_combo.setCurrentIndex(dialog.clone_combo.findData("CHIP_Y"))
    dialog._on_open_clicked()
    assert ask["questions"] == []
    assert dialog.name_edit.text() == "CHIP_Y"
    assert dialog._editing_name == "CHIP_Y"
    assert dialog.repair_btn.isEnabled()
    assert not dialog._has_unsaved_edits()


def test_delete_chip_removes_file_and_unregisters(dialog, ask, tmp_path):
    assert (tmp_path / "CHIP_Y.yaml").is_file()
    ask["answer"] = QMessageBox.Yes
    dialog.clone_combo.setCurrentIndex(dialog.clone_combo.findData("CHIP_Y"))
    dialog._on_delete_chip_clicked()
    assert not (tmp_path / "CHIP_Y.yaml").exists()
    assert dialog.chip_database.get_chip("CHIP_Y") is None
    assert dialog.clone_combo.findData("CHIP_Y") == -1


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


def test_derivative_uuid_round_trips_and_database_lookup(dialog, ask, tmp_path):
    uuid = "B632B9EE-F23D-43CD-9C54-542178A058D9"
    dialog.derivative_uuid_edit.setText(uuid)
    dialog._on_save_clicked()

    reloaded_db = ChipDatabase(tmp_path)
    chip = reloaded_db.get_chip("CHIP_X")
    assert chip.derivative_uuid == uuid
    assert reloaded_db.find_chip_by_derivative_uuid(uuid.lower()).name == "CHIP_X"
    assert reloaded_db.find_chip_by_derivative_uuid("00000000-0000-0000-0000-000000000000") is None


def test_history_button_state_and_formatting(dialog, ask):
    assert dialog.history_btn.isEnabled()
    _clone(dialog, "CHIP_Y")
    assert not dialog.history_btn.isEnabled()

    formatted = dialog._format_history_entries([
        {"resource_version": {"old": "1.0.0", "new": "1.0.1"}, "timestamp": "2026-11-19", "author": "alice", "source": "设计器手工编辑"},
        {"resource_version": {"old": "1.0.1", "new": "1.0.2"}, "timestamp": "2026-11-20", "author": "bob", "source": "修复向导"},
    ])
    # Newest entry first
    assert formatted.index("bob") < formatted.index("alice")
    assert "1.0.1 → 1.0.2" in formatted and "1.0.0 → 1.0.1" in formatted
    assert dialog._format_history_entries([]) == "暂无修改历史记录。"


def test_one_click_sync_all_from_ecu_updates_ui_tabs(qtbot, ask, tmp_path):
    ecu_chip = (
        "name: CHIP_ECU\n"
        "metadata:\n"
        "  cores: {count: 1, available: [CORE0], master: CORE0}\n"
        "ecu_resources:\n"
        "  OsResource:\n"
        "    NumOfCores: 2\n"
        "    AvailableCores: [CORE0, CORE1]\n"
        "    MasterCore: OS_CORE_ID_0\n"
        "  Can:\n"
        "    MaxModules: 2\n"
        "  Port:\n"
        "    AvailablePortsID: _0_\n"
        "    Port0_AvailablePins: _0_ _1_\n"
    )
    (tmp_path / "CHIP_ECU.yaml").write_text(ecu_chip, encoding="utf-8")
    dlg = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="CHIP_ECU")
    qtbot.addWidget(dlg)

    dlg._on_sync_all_from_ecu_clicked()

    assert dlg.core_count_spin.value() == 2
    assert dlg.avail_cores_edit.text() == "CORE0, CORE1"
    assert len(dlg.peripheral_editor.resources().get("can_controller", [])) == 2
    assert [p.pin for p in dlg.current_ports.get("P00", [])] == [0, 1]


def test_batch_confirm_marks_clears_unconfirmed_on_save(qtbot, ask, tmp_path):
    from autosar_configurator.core.hardware.chip_completeness import unconfirmed_marks

    chip_yaml = (
        "name: CHIP_MARK\n"
        "ports:\n"
        "  P00:\n"
        "    - {name: P00_0, port: P00, pin: 0, alternate_functions: [GPIO], default_direction: INPUT}\n"
        "memory_regions:\n"
        "  - {name: PFLASH, start: 0x80000000, size: 0x100000, type: flash, cacheable: true}\n"
        "metadata:\n"
        "  cores: {count: 2, available: [CORE0, CORE1], master: CORE0}\n"
        "  unconfirmed:\n"
        "    ports: 待核对引脚列表\n"
        "    memory_regions: 待核对内存表\n"
        "    metadata.flash_size: 待填写\n"
    )
    (tmp_path / "CHIP_MARK.yaml").write_text(chip_yaml, encoding="utf-8")
    dlg = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="CHIP_MARK")
    qtbot.addWidget(dlg)

    # Empty TO_FILL_IN field must NOT be offered as directly confirmable
    confirmable = dlg._confirmable_marks()
    assert set(confirmable.keys()) == {"ports", "memory_regions"}

    confirmed = dlg.confirm_marks(["ports", "memory_regions", "metadata.flash_size"])
    assert confirmed == 2
    dlg._on_save_clicked()

    saved = ChipDatabase(tmp_path).get_chip("CHIP_MARK")
    marks = unconfirmed_marks(saved)
    assert "ports" not in marks
    assert "memory_regions" not in marks
    assert marks.get("metadata.flash_size") == "待填写"


def test_sc300_copy_not_in_builtin_chip_library():
    from autosar_configurator.core.hardware.chip_database import default_chips_dir

    db = ChipDatabase(default_chips_dir())
    assert "SC300_COPY" not in db.list_chips()
