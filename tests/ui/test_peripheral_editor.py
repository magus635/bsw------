"""Designer peripheral page: instances of any type, per-instance properties."""
import pytest
from PySide6.QtWidgets import QInputDialog, QMessageBox

from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.core.hardware.generic_resource import GenericResourceDef
from autosar_configurator.core.hardware.mapping_rule import rule_resource_requirements
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import (
    ChipDefinitionDesignerDialog,
)
from autosar_configurator.ui.dialogs.peripheral_editor import PeripheralEditor


@pytest.fixture
def boxes(monkeypatch):
    seen = {"warning": []}
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: seen["warning"].append(a[2]) or QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Yes)
    return seen


def _editor(qtbot, resources=None):
    editor = PeripheralEditor(requirements=rule_resource_requirements())
    qtbot.addWidget(editor)
    editor.set_resources(resources or {})
    return editor


def _select_type(editor, res_type):
    for i in range(editor.type_list.count()):
        if editor.type_list.item(i).data(256) == res_type:
            editor.type_list.setCurrentRow(i)
            return
    raise AssertionError(res_type)


def _cell(editor, row, header):
    headers = [editor.table.horizontalHeaderItem(c).text() for c in range(editor.table.columnCount())]
    col = next(c for c, h in enumerate(headers) if h.rstrip(" *") == header)
    return editor.table.item(row, col)


def test_add_a_rule_type_with_prefilled_columns(qtbot, boxes, monkeypatch):
    editor = _editor(qtbot)
    monkeypatch.setattr(QInputDialog, "getItem", lambda *a, **k: ("gpt_channel (Gpt)", True))
    editor._add_type()
    assert editor._current == "gpt_channel"
    headers = [editor.table.horizontalHeaderItem(c).text() for c in range(editor.table.columnCount())]
    assert headers == ["resource_id", "display_name", "channel_id *"]


def test_free_type_and_pin_types_refused(qtbot, boxes, monkeypatch):
    editor = _editor(qtbot)
    monkeypatch.setattr(QInputDialog, "getItem", lambda *a, **k: ("crc_unit", True))
    editor._add_type()
    assert "crc_unit" in editor.resources()
    monkeypatch.setattr(QInputDialog, "getItem", lambda *a, **k: ("gpio_pin", True))
    editor._add_type()
    assert "gpio_pin" not in editor.resources()
    assert boxes["warning"]


def test_batch_add_numbers_the_id_property(qtbot, boxes):
    editor = _editor(qtbot)
    editor._data["can_controller"] = []
    editor._columns["can_controller"] = editor._rule_props("can_controller")
    assert editor.add_numbered("can_controller", "CAN", 0, 6) == 6
    cans = editor.resources()["can_controller"]
    assert [c.resource_id for c in cans] == [f"CAN{i}" for i in range(6)]
    assert [c.properties["controller_id"] for c in cans] == list(range(6))
    assert editor.add_numbered("can_controller", "CAN", 4, 4) == 2      # CAN4/5 exist already


def test_cell_edits_are_typed_and_lists_are_split(qtbot, boxes):
    editor = _editor(qtbot, {"adc_unit": [GenericResourceDef("adc_unit", "ADC0", "ADC0", {"unit_id": 0})]})
    _select_type(editor, "adc_unit")
    _cell(editor, 0, "channels").setText("0, 1, 2")
    _cell(editor, 0, "resolution_bits").setText("0x0C")
    props = editor.resources()["adc_unit"][0].properties
    assert props["channels"] == [0, 1, 2] and props["resolution_bits"] == 12


def test_unchanged_text_keeps_the_original_value(qtbot, boxes):
    editor = _editor(qtbot, {"x_unit": [GenericResourceDef("x_unit", "X0", "X0", {"code": "007", "n": 1})]})
    _select_type(editor, "x_unit")
    _cell(editor, 0, "n").setText("2")
    assert editor.resources()["x_unit"][0].properties == {"code": "007", "n": 2}


def test_missing_rule_property_is_pointed_out(qtbot, boxes):
    editor = _editor(qtbot, {"gpt_channel": [GenericResourceDef("gpt_channel", "GPT0", "GPT0", {})]})
    assert any("GPT0" in p and "channel_id" in p for p in editor.problems())
    assert "channel_id" in editor.hint_label.text()


def test_invalid_ids_are_reported_and_rejected_strictly(qtbot, boxes):
    editor = _editor(qtbot, {"can_controller": [
        GenericResourceDef("can_controller", "CAN0", "CAN0", {"controller_id": 0}),
        GenericResourceDef("can_controller", "CAN1", "CAN1", {"controller_id": 1})]})
    _select_type(editor, "can_controller")
    editor.table.item(1, 0).setText("CAN0")
    assert any("重复" in p for p in editor.problems())
    with pytest.raises(ValueError):
        editor.validated_resources()
    assert len(editor.resources()["can_controller"]) == 1        # lenient view skips the duplicate


def test_copy_delete_and_property_columns(qtbot, boxes, monkeypatch):
    editor = _editor(qtbot, {"wdg_unit": [GenericResourceDef("wdg_unit", "WDG0", "WDG0", {"unit_id": 0})]})
    _select_type(editor, "wdg_unit")
    editor.table.setCurrentCell(0, 0)
    editor._copy_instance()
    assert [w.resource_id for w in editor.resources()["wdg_unit"]] == ["WDG0", "WDG0_COPY"]

    monkeypatch.setattr(QInputDialog, "getText", lambda *a, **k: ("timeout_ms", True))
    editor._add_property()
    _cell(editor, 0, "timeout_ms").setText("100")
    assert editor.resources()["wdg_unit"][0].properties["timeout_ms"] == 100

    col = [editor.table.horizontalHeaderItem(c).text() for c in range(editor.table.columnCount())].index("timeout_ms")
    editor.table.setCurrentCell(0, col)
    editor._delete_property()
    assert "timeout_ms" not in editor.resources()["wdg_unit"][0].properties

    editor.table.setCurrentCell(1, 0)
    editor._delete_instances()
    assert [w.resource_id for w in editor.resources()["wdg_unit"]] == ["WDG0"]
    editor._delete_type()
    assert editor.resources() == {}


# --- in the designer ----------------------------------------------------------------------

def test_per_instance_properties_survive_save_and_load(qtbot, tmp_path, boxes):
    (tmp_path / "C.yaml").write_text("""name: C
resources:
  can_controller:
    - {resource_id: CAN0, properties: {controller_id: 0, supports_fd: true}}
    - {resource_id: CAN1, properties: {controller_id: 1, supports_fd: false}}
""", encoding="utf-8")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="C")
    qtbot.addWidget(dialog)
    dialog._on_save_clicked()
    cans = ChipDatabase(tmp_path).get_chip("C").resources["can_controller"]
    assert [c.properties["supports_fd"] for c in cans] == [True, False]


def test_legacy_chip_opens_with_all_its_peripherals(qtbot, tmp_path, boxes):
    (tmp_path / "OLD.yaml").write_text("""name: OLD
can_resources: [{name: CAN0, controller_id: 0, supports_fd: true}]
intc_sources: [{name: IRQ_X, vector_number: 7}]
""", encoding="utf-8")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="OLD")
    qtbot.addWidget(dialog)
    res = dialog.peripheral_editor.resources()
    assert [r.resource_id for r in res["intc_source"]] == ["IRQ_X"]      # editable now
    dialog._on_save_clicked()
    saved = ChipDatabase(tmp_path).get_chip("OLD")
    assert saved.resources["intc_source"][0].properties["vector_number"] == 7


def test_invalid_instance_blocks_saving(qtbot, tmp_path, boxes):
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path))
    qtbot.addWidget(dialog)
    dialog.name_edit.setText("NEW")
    dialog.peripheral_editor.set_resources({"can_controller": [
        GenericResourceDef("can_controller", "CAN0", "CAN0", {}),
        GenericResourceDef("can_controller", "CAN1", "CAN1", {})]})
    _select_type(dialog.peripheral_editor, "can_controller")
    dialog.peripheral_editor.table.item(1, 0).setText("")
    dialog._on_save_clicked()
    assert not (tmp_path / "NEW.yaml").exists()
    assert dialog.tabs.currentIndex() == 1
    assert any("resource_id" in w for w in boxes["warning"])


def test_sync_peripherals_from_ecu_in_designer(qtbot, tmp_path, boxes):
    (tmp_path / "C.yaml").write_text("""name: C
resources:
  intc_source:
    - {resource_id: IRQ0, properties: {vector_number: 10, is_configurable: true}}
ecu_resources:
  Can:
    HwUnitNode: [CAN0, CAN1]
    FDSupport: true
  Wdg:
    WdgInstance: WDOG0
""", encoding="utf-8")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="C")
    qtbot.addWidget(dialog)
    dialog.peripheral_editor.sync_ecu_btn.click()
    res = dialog.peripheral_editor.resources()
    assert [r.resource_id for r in res["can_controller"]] == ["CAN0", "CAN1"]
    assert [r.resource_id for r in res["wdg_unit"]] == ["WDOG0"]
    assert [r.resource_id for r in res["intc_source"]] == ["IRQ0"]   # preserved


_CHIP_WITH_CAN = """name: C
resources:
  can_controller:
    - {resource_id: CAN0, properties: {controller_id: 0, supports_fd: false, note: tuned}}
  intc_source:
    - {resource_id: IRQ0, properties: {vector_number: 10, is_configurable: true}}
ecu_resources:
  Can:
    HwUnitNode: [CAN_CONTROLLER_00, CAN_CONTROLLER_01]
  Wdg:
    WdgInstance: WDOG0
"""


def _designer_with_can(qtbot, tmp_path, monkeypatch, answer):
    asked = []
    monkeypatch.setattr(QMessageBox, "question",
                        lambda *a, **k: asked.append(a[2]) or answer)
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)
    (tmp_path / "C.yaml").write_text(_CHIP_WITH_CAN, encoding="utf-8")
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(tmp_path), initial_chip="C")
    qtbot.addWidget(dialog)
    return dialog, asked


def test_sync_from_ecu_keeps_existing_peripherals_when_declined(qtbot, tmp_path, monkeypatch):
    dialog, asked = _designer_with_can(qtbot, tmp_path, monkeypatch, QMessageBox.No)
    dialog.peripheral_editor.sync_ecu_btn.click()
    assert len(asked) == 1 and "can_controller" in asked[0] and "wdg_unit" not in asked[0]
    res = dialog.peripheral_editor.resources()
    assert [r.resource_id for r in res["can_controller"]] == ["CAN0"]
    assert res["can_controller"][0].properties["note"] == "tuned"
    assert "wdg_unit" not in res          # nothing is applied when declined


def test_sync_from_ecu_replaces_existing_peripherals_when_confirmed(qtbot, tmp_path, monkeypatch):
    dialog, asked = _designer_with_can(qtbot, tmp_path, monkeypatch, QMessageBox.Yes)
    dialog.peripheral_editor.sync_ecu_btn.click()
    assert len(asked) == 1
    res = dialog.peripheral_editor.resources()
    assert [r.resource_id for r in res["can_controller"]] == ["CAN_CONTROLLER_00", "CAN_CONTROLLER_01"]
    assert [r.resource_id for r in res["wdg_unit"]] == ["WDOG0"]
    assert [r.resource_id for r in res["intc_source"]] == ["IRQ0"]


def test_sync_from_ecu_does_not_ask_when_only_new_types_are_added(qtbot, tmp_path, monkeypatch):
    dialog, asked = _designer_with_can(qtbot, tmp_path, monkeypatch, QMessageBox.No)
    dialog.peripheral_editor.set_resources({
        "can_controller": [GenericResourceDef(
            resource_type="can_controller", resource_id=f"CAN_CONTROLLER_0{i}",
            display_name=f"CAN Controller {i}",
            properties={"controller_id": i, "max_baudrate": 1000000, "supports_fd": False})
            for i in range(2)],
    })
    dialog.peripheral_editor.sync_ecu_btn.click()
    assert asked == []                    # can_controller already matches, wdg_unit is new
    assert [r.resource_id for r in dialog.peripheral_editor.resources()["wdg_unit"]] == ["WDOG0"]

