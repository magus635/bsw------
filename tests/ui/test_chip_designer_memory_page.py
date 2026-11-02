"""The designer's physical memory page: editing, checks that stop the save and ones that
do not, import preview and merge, and a save that keeps the data and the marks."""
import pytest
from PySide6.QtWidgets import QDialog, QMessageBox

from autosar_configurator.core.hardware.chip_completeness import unconfirmed_marks
from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.core.hardware.memory_regions import LOCAL, MemoryRegionDef
from autosar_configurator.ui.dialogs import memory_region_editor as editor_module
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog
from autosar_configurator.ui.dialogs.memory_region_editor import MemoryRegionEditor, parse_hex

CHIP = ("name: CHIP_X\nresource_version: 1.0.0\n"
        "metadata:\n  cpu_frequency: 300000000\n  flash_size: 512KB\n  ram_size: 64KB\n"
        "  cores: {count: 1, available: [CORE0], master: CORE0}\n"
        "  unconfirmed:\n    memory_regions: 按链接脚本的注释表填写\n"
        "memory_regions:\n"
        "- {name: GMU_NORMAL, start: '0x10000000', size: '0x40000', type: ram, cacheable: true, memory: GMU}\n"
        "- {name: GMU_DEVICE, start: '0x82000000', size: '0x40000', type: ram, cacheable: false, memory: GMU}\n")
SCAT = """\
;        CPU0BTCM                0x30100000                0x30100000 - 0x30130000 (192K)         AXI access CPU0BTCM address
;        GMU_NORMAL              0x10000000                0x10000000 - 0x10040000 (256K)         AXI access global memory address(Cacheable)
;        CPUXATCM                0x00000000                0x00000000 + 64K          local access CPUXATCM address
"""


@pytest.fixture
def boxes(monkeypatch):
    shown = {"warning": [], "information": []}
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: shown["information"].append(a[2]))
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: shown["warning"].append(a[2]))
    monkeypatch.setattr(QMessageBox, "critical", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Yes)
    return shown


@pytest.fixture
def library(tmp_path):
    lib = tmp_path / "lib"
    lib.mkdir()
    (lib / "CHIP_X.yaml").write_text(CHIP, encoding="utf-8")
    return lib


def _open(qtbot, library):
    dialog = ChipDefinitionDesignerDialog(chip_database=ChipDatabase(library), initial_chip="CHIP_X")
    qtbot.addWidget(dialog)
    return dialog


def _names(editor):
    return [r.name for r in editor.regions()]


# --- hexadecimal input -------------------------------------------------------------------

@pytest.mark.parametrize("text, value", [("0x10000000", 0x10000000), ("10000000", 0x10000000),
                                         ("  0X40000 ", 0x40000), ("ff", 255)])
def test_hex_input(text, value):
    assert parse_hex(text, "x") == value


@pytest.mark.parametrize("text", ["", "  ", "0xZZ", "12G", "1.5"])
def test_bad_hex_input_names_the_field(text):
    with pytest.raises(ValueError, match="起始地址"):
        parse_hex(text, "起始地址")


# --- the page in the designer ---------------------------------------------------------------

def test_the_page_is_the_sixth_tab_and_shows_the_chip(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    assert dialog.tabs.tabText(5).startswith("6. 物理存储")
    assert dialog.tabs.tabText(4).startswith("5. 预览")          # the preview kept its place
    assert _names(dialog.memory_editor) == ["GMU_NORMAL", "GMU_DEVICE"]
    top = dialog.memory_editor.tree.topLevelItem(0)
    assert top.text(0).startswith("GMU") and top.childCount() == 2


def test_add_a_window_and_save(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.add_region(MemoryRegionDef("LMU1_NORMAL", 0x10054000, 0x4000, "ram", None, True))
    dialog._on_save_clicked()
    saved = ChipDatabase(library).get_chip("CHIP_X")
    assert [r.name for r in saved.memory_regions] == ["GMU_NORMAL", "GMU_DEVICE", "LMU1_NORMAL"]
    assert saved.memory_regions[2].size == 0x4000


def test_rename_a_memory_changes_every_window(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.rename("GMU", "GMU0")
    dialog._on_save_clicked()
    saved = ChipDatabase(library).get_chip("CHIP_X")
    assert [r.memory for r in saved.memory_regions] == ["GMU0", "GMU0"]


def test_remove_a_window(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.remove_window("GMU_DEVICE")
    dialog._on_save_clicked()
    assert [r.name for r in ChipDatabase(library).get_chip("CHIP_X").memory_regions] == ["GMU_NORMAL"]


def test_remove_a_whole_memory(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.remove_memory("GMU")
    assert dialog.memory_editor.regions() == []


def test_edit_a_window(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.replace_region(
        "GMU_DEVICE", MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x20000, "ram", None, False, "GMU"))
    assert dialog.memory_editor.regions()[1].size == 0x20000


def test_editing_elsewhere_keeps_the_regions_and_their_mark(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.basic_edits["flash_size"].setText("4MB")
    dialog._on_save_clicked()
    saved = ChipDatabase(library).get_chip("CHIP_X")
    assert len(saved.memory_regions) == 2
    assert unconfirmed_marks(saved)["memory_regions"] == "按链接脚本的注释表填写"


def test_an_untouched_page_does_not_make_the_chip_look_edited(qtbot, library, boxes):
    assert not _open(qtbot, library)._has_unsaved_edits()


def test_a_memory_edit_counts_as_an_unsaved_edit(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.remove_window("GMU_DEVICE")
    assert dialog._has_unsaved_edits()


# --- problems -------------------------------------------------------------------------------

def test_a_repeated_name_stops_the_save_and_names_it(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.add_region(MemoryRegionDef("GMU_NORMAL", 0x20000000, 0x1000))
    before = (library / "CHIP_X.yaml").read_text(encoding="utf-8")
    dialog._on_save_clicked()
    assert any("名称重复：GMU_NORMAL" in text for text in boxes["warning"])
    assert (library / "CHIP_X.yaml").read_text(encoding="utf-8") == before
    assert dialog.tabs.currentIndex() == 5


def test_doubtful_data_is_listed_and_saved(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.replace_region(
        "GMU_DEVICE", MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x20000, "ram", None, False, "GMU"))
    assert any("窗口大小不一致" in dialog.memory_editor.problems.item(i).text()
               for i in range(dialog.memory_editor.problems.count()))
    assert dialog.memory_editor.blocking_problems() == []
    dialog._on_save_clicked()
    assert boxes["warning"] == []
    assert ChipDatabase(library).get_chip("CHIP_X").memory_regions[1].size == 0x20000


def test_overlap_is_listed_and_saved(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.memory_editor.add_region(MemoryRegionDef("LMU1_NORMAL", 0x10001000, 0x4000))
    texts = [dialog.memory_editor.problems.item(i).text() for i in range(dialog.memory_editor.problems.count())]
    assert any("窗口重叠：GMU_NORMAL 与 LMU1_NORMAL" in t for t in texts)
    dialog._on_save_clicked()
    assert boxes["warning"] == []


def test_the_window_dialog_refuses_a_size_of_zero(qtbot):
    dialog = editor_module.RegionDialog(None, ["GMU"])
    qtbot.addWidget(dialog)
    dialog.name_edit.setText("X")
    dialog.start_edit.setText("0x1000")
    dialog.size_edit.setText("0")
    dialog._accept()
    assert dialog.result_region is None and "必须为正数" in dialog.error_label.text()


def test_the_window_dialog_builds_a_region(qtbot):
    dialog = editor_module.RegionDialog(None, ["GMU"])
    qtbot.addWidget(dialog)
    dialog.name_edit.setText("GMU_DEVICE")
    dialog.memory_combo.setCurrentText("GMU")
    dialog.start_edit.setText("82000000")
    dialog.size_edit.setText("40000")
    dialog.cacheable.setChecked(False)
    dialog.core_combo.setCurrentIndex(dialog.core_combo.findData(LOCAL))
    dialog._accept()
    assert dialog.result_region == MemoryRegionDef(
        "GMU_DEVICE", 0x82000000, 0x40000, "ram", LOCAL, False, "GMU")


# --- import --------------------------------------------------------------------------------

def _scat(tmp_path):
    path = tmp_path / "LinkerAdsPf.scat"
    path.write_text(SCAT, encoding="utf-8")
    return str(path)


def test_cancelled_preview_changes_nothing(qtbot, library, boxes, tmp_path, monkeypatch):
    dialog = _open(qtbot, library)
    monkeypatch.setattr(MemoryRegionEditor, "_confirm_import", lambda self, parsed, report: False)
    assert dialog.memory_editor.import_file(_scat(tmp_path)) is False
    assert _names(dialog.memory_editor) == ["GMU_NORMAL", "GMU_DEVICE"]
    assert not dialog._has_unsaved_edits()


def test_confirmed_import_adds_and_skips(qtbot, library, boxes, tmp_path, monkeypatch):
    dialog = _open(qtbot, library)
    monkeypatch.setattr(MemoryRegionEditor, "_confirm_import", lambda self, parsed, report: True)
    assert dialog.memory_editor.import_file(_scat(tmp_path)) is True
    assert _names(dialog.memory_editor) == ["GMU_NORMAL", "GMU_DEVICE", "CPU0BTCM", "CPUXATCM"]
    kept = dialog.memory_editor.regions()[0]
    assert kept.start == 0x10000000 and kept.memory == "GMU"        # the existing entry is untouched


def test_the_preview_lists_what_is_added_and_skipped(qtbot, library, boxes, tmp_path, monkeypatch):
    dialog = _open(qtbot, library)
    seen = {}

    def preview(self, parsed, report):
        seen["added"], seen["skipped"] = list(report.added), list(report.skipped)
        return False

    monkeypatch.setattr(MemoryRegionEditor, "_confirm_import", preview)
    dialog.memory_editor.import_file(_scat(tmp_path))
    assert seen == {"added": ["CPU0BTCM", "CPUXATCM"], "skipped": ["GMU_NORMAL"]}


def test_the_import_preview_dialog_shows_the_rows(qtbot, library, boxes, tmp_path):
    from autosar_configurator.core.hardware.memory_regions_import import merge_import, parse_comment_table
    parsed = parse_comment_table(SCAT, "LinkerAdsPf.scat")
    _, report = merge_import([], parsed)
    preview = editor_module.ImportPreviewDialog(parsed, report)
    qtbot.addWidget(preview)
    rows = [preview.list.item(i).text() for i in range(preview.list.count())]
    assert len(rows) == 3 and rows[0].startswith("加入  CPU0BTCM")
    assert "缓存属性原文未说明" in rows[0]


def test_imported_data_is_saved_with_its_source_and_a_mark(qtbot, library, boxes, tmp_path, monkeypatch):
    dialog = _open(qtbot, library)
    monkeypatch.setattr(MemoryRegionEditor, "_confirm_import", lambda self, parsed, report: True)
    dialog.memory_editor.import_file(_scat(tmp_path))
    dialog._on_save_clicked()
    saved = ChipDatabase(library).get_chip("CHIP_X")
    imported = next(r for r in saved.memory_regions if r.name == "CPU0BTCM")
    assert imported.source == "LinkerAdsPf.scat 注释表"
    note = unconfirmed_marks(saved)["memory_regions"]
    assert "LinkerAdsPf.scat" in note and "CPU0BTCM" in note


def test_a_file_without_a_table_says_so(qtbot, library, boxes, tmp_path):
    dialog = _open(qtbot, library)
    path = tmp_path / "empty.scat"
    path.write_text("LR 0x0 0x100 { }\n", encoding="utf-8")
    assert dialog.memory_editor.import_file(str(path)) is False
    assert any("没有找到内存区域表" in text for text in boxes["information"])


def test_an_unreadable_file_is_reported(qtbot, library, boxes, tmp_path):
    dialog = _open(qtbot, library)
    assert dialog.memory_editor.import_file(str(tmp_path / "missing.scat")) is False
    assert any("无法读取文件" in text for text in boxes["warning"])


def test_dialog_accepted_constant_is_the_qt_one():
    assert QDialog.Accepted is not None
