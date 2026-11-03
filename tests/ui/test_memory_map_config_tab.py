"""Memory map workbench, tab "配置" (add-memory-layout-config, tasks 6.x): placing sections
by "+", "−" and drag, refusals, statuses, regions and windows, the rule editor, restoring the
factory rules, saving, and the question on close."""
from types import SimpleNamespace

import pytest
from PySide6.QtWidgets import QMessageBox

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    default_chips_dir,
)
from autosar_configurator.core.memmap import rules as rl
from autosar_configurator.core.memmap.check import CheckResult, SectionRow
from autosar_configurator.core.memmap.config import config_dict, config_path
from autosar_configurator.core.memmap.session import LayoutSession
from autosar_configurator.ui.dialogs import memory_map_config_tab as tab_module
from autosar_configurator.ui.dialogs.memory_map_config_tab import (
    RuleEditorDialog,
    section_mime,
)
from autosar_configurator.ui.dialogs.memory_map_workbench import (
    CONFIG,
    MemoryMapWorkbench,
)

CHIP = "THA6206_LFBGA292"
BSS0 = ".mcal_bss_asil_d_unspecified_core0"
BSS = ".mcal_bss_asil_d_unspecified"
TEXT = ".mcal_text_asil_d"
DATA1 = ".mcal_data_asil_d_core1"
CONST = ".mcal_const_asil_d"


@pytest.fixture(scope="module")
def chip_regions():
    return ChipDatabase(default_chips_dir()).get_chip(CHIP).memory_regions


def _row(output, kind, core=None, modules=("CAN",)):
    return SectionRow(output=output, kind=kind, names=(), modules=modules, core=core,
                      non_cacheable=False, uses=())


def _result(regions):
    rows = [_row(BSS0, "BSS", 0), _row(BSS, "BSS"), _row(TEXT, "TEXT"),
            _row(DATA1, "DATA", 1, ("SPI",)), _row(CONST, "RODATA", modules=("CAN", "SPI"))]
    return CheckResult(rows=rows, regions=list(regions))


def _project(tmp_path):
    return SimpleNamespace(path=tmp_path / "p.dpa", selected_chip=CHIP, chip_database=None,
                           memmap_source_dirs=[], memmap_header_dirs=[], memmap_linker_file=None)


def _open(qtbot, tmp_path, regions, project=None):
    workbench = MemoryMapWorkbench(project or _project(tmp_path))
    qtbot.addWidget(workbench)
    workbench.show_result(_result(regions))
    return workbench


def _status(tab, section):
    placed = tab.placement(section)
    return placed.status, placed.target


def _table_row(tab, section):
    for index in range(tab.table.rowCount()):
        if tab.table.item(index, 0).text() == section:
            return [tab.table.item(index, c).text() for c in range(tab.table.columnCount())]
    return None


@pytest.fixture
def no_question(monkeypatch):
    """Closing a test window never blocks on the unsaved-changes question."""
    monkeypatch.setattr(MemoryMapWorkbench, "_ask_save", lambda self: QMessageBox.No)


# --- the tab ------------------------------------------------------------------------------------

def test_the_config_tab_is_the_third(qtbot, tmp_path, chip_regions, no_question):
    workbench = _open(qtbot, tmp_path, chip_regions)
    assert CONFIG == 2 and workbench.tabs.tabText(CONFIG) == "配置"
    assert workbench.tabs.widget(CONFIG) is workbench.config_tab
    assert [workbench.tabs.tabText(i) for i in range(3)] == ["诊断", "布局", "配置"]


def test_rules_place_the_sections_and_the_table_shows_status_and_target(qtbot, tmp_path, chip_regions,
                                                                       no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    assert _status(tab, BSS0) == (rl.BY_RULE, "PRIVATE_BSS_CORE0")
    assert _status(tab, TEXT) == (rl.BY_RULE, "EX_CODE")
    assert _table_row(tab, DATA1) == [DATA1, "DATA", "1", "SPI", "规则", "PRIVATE_DATA_CORE1"]
    assert "诊断、布局页签描述的是磁盘上的链接文件" in tab.disk_note.text()
    assert "出厂初始规则" in tab.notes_label.text()          # session.prepared.notes()
    assert "默认布局" in tab.notes_label.text()              # no needs scanned


def test_the_tree_shows_memory_window_region_required_and_counts(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    item = tab.region_item("PRIVATE_BSS_CORE0")
    assert item is not None and item.text(2) == "必需" and item.text(3) == "1"
    assert item.parent().text(0).startswith("CPU0BTCM")
    assert item.parent().parent().text(0) == "CPU0BTCM"
    assert tab.region_item("UNDEFINE_RAM_BSS").text(3) == "1"


# --- placing --------------------------------------------------------------------------------------

def test_place_by_the_plus_button(qtbot, tmp_path, chip_regions, no_question):
    workbench = _open(qtbot, tmp_path, chip_regions)
    tab = workbench.config_tab
    tab.select_sections([BSS0])
    assert tab.select_region("UNDEFINE_RAM_BSS")
    tab.place_button.click()
    assert _status(tab, BSS0) == (rl.MANUAL, "UNDEFINE_RAM_BSS")
    assert _table_row(tab, BSS0)[4:] == ["手动", "UNDEFINE_RAM_BSS"]
    assert tab.region_item("UNDEFINE_RAM_BSS").text(3) == "2"
    assert workbench.session.dirty and tab.dirty_label.text() == "有未保存的改动"


def test_place_several_at_once_through_the_shared_method(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.select_sections([BSS0, BSS])
    assert tab.selected_names() == [BSS, BSS0]
    tab.select_region("PRIVATE_BSS_CORE1")
    assert tab.place_selected() == []
    assert _status(tab, BSS0) == _status(tab, BSS) == (rl.MANUAL, "PRIVATE_BSS_CORE1")


def test_drop_goes_through_the_same_placing(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    calls = []
    original = tab.apply_placement
    tab.apply_placement = lambda sections, region: calls.append((sections, region)) or original(sections, region)
    assert tab.handle_drop(section_mime([BSS0]), tab.region_item("UNDEFINE_RAM_BSS"))
    assert calls == [([BSS0], "UNDEFINE_RAM_BSS")]
    assert _status(tab, BSS0) == (rl.MANUAL, "UNDEFINE_RAM_BSS")
    assert not tab.handle_drop(section_mime([BSS]), tab.region_item("UNDEFINE_RAM_BSS").parent())  # a window


def test_the_table_drags_the_selected_sections(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.select_sections([BSS, TEXT])
    items = [tab.table.item(i, 0) for i in range(tab.table.rowCount()) if tab.table.item(i, 0).isSelected()]
    mime = tab.table.mimeData(items)
    assert bytes(mime.data(tab_module.MIME)).decode("utf-8").split("\n") == [BSS, TEXT]


def test_a_refused_placement_changes_nothing_and_shows_why(qtbot, tmp_path, chip_regions, no_question):
    workbench = _open(qtbot, tmp_path, chip_regions)
    tab = workbench.config_tab
    tab.select_sections([TEXT, BSS])
    tab.select_region("UNDEFINE_RAM_BSS")
    refused = tab.place_selected()
    assert len(refused) == 1 and refused[0].startswith(f"{TEXT}：") and "TEXT" in refused[0]
    assert tab.messages() == refused and "1 个被拒绝" in tab.message_label.text()
    assert _status(tab, TEXT) == (rl.BY_RULE, "EX_CODE")            # unchanged
    assert _status(tab, BSS) == (rl.MANUAL, "UNDEFINE_RAM_BSS")      # the one that fits is placed
    assert TEXT not in workbench.session.config.manual


def test_minus_returns_to_the_rules(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.apply_placement([BSS0], "UNDEFINE_RAM_BSS")
    tab.select_sections([BSS0])
    tab.unplace_button.click()
    assert _status(tab, BSS0) == (rl.BY_RULE, "PRIVATE_BSS_CORE0")
    assert "回到规则" in tab.message_label.text()


def test_filters(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.module_combo.setCurrentIndex(tab.module_combo.findData("SPI"))
    assert tab.table.rowCount() == 2
    tab.module_combo.setCurrentIndex(0)
    tab.core_combo.setCurrentIndex(tab.core_combo.findData(0))
    assert [tab.table.item(i, 0).text() for i in range(tab.table.rowCount())] == [BSS0]
    tab.core_combo.setCurrentIndex(tab.core_combo.findData(tab_module.NO_CORE))
    assert tab.table.rowCount() == 3
    tab.core_combo.setCurrentIndex(0)
    tab.kind_combo.setCurrentIndex(tab.kind_combo.findData("TEXT"))
    assert tab.table.rowCount() == 1
    tab.kind_combo.setCurrentIndex(0)
    tab.apply_placement([BSS], "PRIVATE_BSS_CORE1")
    tab.status_combo.setCurrentIndex(tab.status_combo.findData(rl.MANUAL))
    assert [tab.table.item(i, 0).text() for i in range(tab.table.rowCount())] == [BSS]


# --- regions -----------------------------------------------------------------------------------------

def test_a_required_region_cannot_be_removed_or_renamed(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.select_region("PRIVATE_BSS_CORE0")
    tab.remove_region_button.click()
    assert "必需区域" in tab.message_label.text() and "不能删除" in tab.message_label.text()
    assert tab.region_item("PRIVATE_BSS_CORE0") is not None
    assert "不能改名" in tab.rename_region("PRIVATE_BSS_CORE0", "X")


def test_user_region_added_filled_renamed_and_removed(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.select_region("UNDEFINE_RAM_DATA")                      # on GMU_NORMAL
    assert tab.add_region("MY_FAST_DATA", "data") == ""
    region = tab.session.config.region("MY_FAST_DATA")
    assert (region.memory, region.window, region.required) == ("GMU", "GMU_NORMAL", False)
    assert "自定义" in tab.region_item("MY_FAST_DATA").text(2)
    assert tab.apply_placement([DATA1], "MY_FAST_DATA") == []
    assert tab.rename_region("MY_FAST_DATA", "MY_DATA") == ""
    assert _status(tab, DATA1) == (rl.MANUAL, "MY_DATA")          # the placement follows the name
    assert tab.remove_region("MY_DATA") == ""
    assert _status(tab, DATA1) == (rl.AGAIN, "MY_DATA")           # kept, to be placed again
    assert "已存在" in tab.add_region("EX_CODE", "code")


def test_choosing_a_window_clears_to_be_placed_again(qtbot, tmp_path, chip_regions, no_question):
    project = _project(tmp_path)
    workbench = _open(qtbot, tmp_path, chip_regions, project)
    tab = workbench.config_tab
    tab.session.config.options[rl.AGAIN_KEY] = ["PRIVATE_BSS_CORE0"]
    tab.refresh()
    assert _status(tab, BSS0) == (rl.AGAIN, "PRIVATE_BSS_CORE0")
    assert "待重新放置" in tab.region_item("PRIVATE_BSS_CORE0").text(2)
    assert "重新选择窗口" in tab.notes_label.text()
    tab.select_region("PRIVATE_BSS_CORE0")
    tab.window_combo.setCurrentIndex(tab.window_combo.findData(("CPU0ATCM", "CPU0ATCM")))
    tab.window_button.click()
    region = tab.session.config.region("PRIVATE_BSS_CORE0")
    assert (region.memory, region.window) == ("CPU0ATCM", "CPU0ATCM")
    assert rl.AGAIN_KEY not in tab.session.config.options
    assert _status(tab, BSS0) == (rl.BY_RULE, "PRIVATE_BSS_CORE0")
    assert tab.region_item("PRIVATE_BSS_CORE0").parent().text(0).startswith("CPU0ATCM")


# --- the rule editor ------------------------------------------------------------------------------------

def _editor(qtbot, tab) -> RuleEditorDialog:
    editor = tab.open_rule_editor()
    qtbot.addWidget(editor)
    return editor


def _marks(editor, name):
    return editor.item_of(name).text(5)


def test_rule_editor_change_marks_changed_and_sections_follow(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    editor = _editor(qtbot, tab)
    name = next(r.name for r in tab.session.config.rules if r.target == "PRIVATE_BSS_CORE0")
    assert editor.item_of(name).text(4) == "出厂"
    editor.select_rule(name)
    editor.set_fields(target="UNDEFINE_RAM_BSS")
    assert editor.apply_edit() == ""
    assert _marks(editor, name).startswith("已修改（原：") and "PRIVATE_BSS_CORE0" in _marks(editor, name)
    assert _status(tab, BSS0) == (rl.BY_RULE, "UNDEFINE_RAM_BSS")     # the tab follows
    editor.set_fields(target="PRIVATE_BSS_CORE0")
    editor.apply_edit()
    assert _marks(editor, name) == ""                                  # changed back


def test_rule_editor_add_move_up_shadows_and_remove(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    editor = _editor(qtbot, tab)
    editor.set_fields(name="我的 BSS", target="UNCLEAR_RAM_BSS", pattern="*core0", kinds=["BSS"])
    assert editor.add_from_fields() == ""
    assert editor.rule_names()[-1] == "我的 BSS" and editor.item_of("我的 BSS").text(4) == "用户"
    assert "被遮蔽" in _marks(editor, "我的 BSS")                       # factory rules take it first
    while editor.rule_names()[0] != "我的 BSS":
        editor.move_selected(-1)
    assert _status(tab, BSS0) == (rl.BY_RULE, "UNCLEAR_RAM_BSS")
    factory = next(r.name for r in tab.session.config.rules if r.target == "PRIVATE_BSS_CORE0")
    assert "被遮蔽" in _marks(editor, factory)
    editor.move_selected(1)
    assert editor.rule_names()[1] == "我的 BSS"
    editor.select_rule("我的 BSS")
    editor.remove_selected()
    assert "我的 BSS" not in editor.rule_names()
    assert _status(tab, BSS0) == (rl.BY_RULE, "PRIVATE_BSS_CORE0")


def test_rule_editor_marks_an_invalid_rule(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    editor = _editor(qtbot, tab)
    editor.set_fields(name="坏规则", target="NO_SUCH_REGION", kinds=["DATA"])
    editor.add_from_fields()
    assert _marks(editor, "坏规则") == "无效：没有区域 NO_SUCH_REGION"


def test_rule_editor_match_fields_round_trip(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    editor = _editor(qtbot, tab)
    editor.set_fields(name="r", target="GLOBAL_UNCACHED_DATA", pattern="*_x", kinds=["DATA"], core=None,
                      cacheable=False, module="SPI")
    assert editor.match_from_fields() == {"name": "*_x", "kind": ["DATA"], "core": None, "cacheable": False,
                                          "module": "SPI"}
    editor.add_from_fields()
    rule = tab.session.config.rules[-1]
    editor.select_rule("r")
    editor.load_fields(rule)
    assert editor.match_from_fields() == rule.match


def test_rule_editor_says_when_factory_rules_are_newer(qtbot, tmp_path, chip_regions, no_question):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.session.config.options[rl.FACTORY_VERSION_KEY] = 0
    editor = _editor(qtbot, tab)
    assert "出厂规则有更新" in editor.factory_label.text()


def test_restore_factory_previews_and_cancel_changes_nothing(qtbot, tmp_path, chip_regions, no_question,
                                                              monkeypatch):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    editor = _editor(qtbot, tab)
    changed = next(r.name for r in tab.session.config.rules if r.target == "PRIVATE_BSS_CORE0")
    editor.select_rule(changed)
    editor.set_fields(target="UNDEFINE_RAM_BSS")
    editor.apply_edit()
    editor.set_fields(name="我的", target="UNCLEAR_RAM_BSS", kinds=["BSS"])
    editor.add_from_fields()
    before = config_dict(tab.session.config)
    asked = []
    monkeypatch.setattr(RuleEditorDialog, "_confirm", lambda self, text: asked.append(text) or False)
    assert editor.restore_factory() is False
    assert f"会丢失的修改：{changed}" in asked[0] and "会删除的自己添加的规则：我的" in asked[0]
    assert config_dict(tab.session.config) == before


def test_restore_factory_on_confirm_keeps_manual_placements(qtbot, tmp_path, chip_regions, no_question,
                                                           monkeypatch):
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    tab.apply_placement([BSS0], "UNDEFINE_RAM_BSS")
    editor = _editor(qtbot, tab)
    editor.set_fields(name="我的", target="UNCLEAR_RAM_BSS", kinds=["BSS"])
    editor.add_from_fields()
    monkeypatch.setattr(RuleEditorDialog, "_confirm", lambda self, text: True)
    assert editor.restore_factory() is True
    assert [r.name for r in tab.session.config.rules] == [r.name for r in editor.factory.rules]
    assert tab.session.config.manual == {BSS0: "UNDEFINE_RAM_BSS"}
    assert _status(tab, BSS0) == (rl.MANUAL, "UNDEFINE_RAM_BSS")
    assert editor.restore_factory() is False                          # nothing left to restore


# --- saving and closing ---------------------------------------------------------------------------------

def test_save_then_reopen_gives_the_same_configuration(qtbot, tmp_path, chip_regions, no_question):
    project = _project(tmp_path)
    workbench = _open(qtbot, tmp_path, chip_regions, project)
    tab = workbench.config_tab
    tab.apply_placement([BSS0], "UNDEFINE_RAM_BSS")
    editor = _editor(qtbot, tab)
    editor.set_fields(name="我的", target="UNCLEAR_RAM_BSS", kinds=["BSS"])
    editor.add_from_fields()
    tab.save_button.click()
    assert config_path(tmp_path).is_file() and not workbench.session.dirty
    assert tab.dirty_label.text() == "" and "已保存" in tab.message_label.text()
    saved = config_dict(workbench.session.config)

    again = _open(qtbot, tmp_path, chip_regions, project)
    assert config_dict(again.session.config) == saved and not again.session.dirty
    assert _status(again.config_tab, BSS0) == (rl.MANUAL, "UNDEFINE_RAM_BSS")
    assert LayoutSession.open(project).config.rules[-1].name == "我的"


def _closing(qtbot, tmp_path, chip_regions, monkeypatch, answer):
    workbench = _open(qtbot, tmp_path, chip_regions)
    workbench.config_tab.apply_placement([BSS0], "UNDEFINE_RAM_BSS")
    asked = []
    monkeypatch.setattr(MemoryMapWorkbench, "_ask_save", lambda self: asked.append(1) or answer)
    closed = []
    workbench.rejected.connect(lambda: closed.append(1))
    workbench.reject()
    return workbench, asked, closed


def test_close_with_unsaved_changes_yes_saves(qtbot, tmp_path, chip_regions, monkeypatch):
    workbench, asked, closed = _closing(qtbot, tmp_path, chip_regions, monkeypatch, QMessageBox.Yes)
    assert asked and closed and not workbench.session.dirty
    assert LayoutSession.open(_project(tmp_path)).config.manual == {BSS0: "UNDEFINE_RAM_BSS"}


def test_close_with_unsaved_changes_no_discards(qtbot, tmp_path, chip_regions, monkeypatch):
    _workbench, asked, closed = _closing(qtbot, tmp_path, chip_regions, monkeypatch, QMessageBox.No)
    assert asked and closed and not config_path(tmp_path).exists()


def test_close_with_unsaved_changes_cancel_keeps_the_window(qtbot, tmp_path, chip_regions, monkeypatch):
    workbench, asked, closed = _closing(qtbot, tmp_path, chip_regions, monkeypatch, QMessageBox.Cancel)
    assert asked and not closed and workbench.session.dirty
    assert not config_path(tmp_path).exists()
    monkeypatch.setattr(MemoryMapWorkbench, "_ask_save", lambda self: QMessageBox.No)


def test_close_without_changes_does_not_ask(qtbot, tmp_path, monkeypatch):
    workbench = MemoryMapWorkbench(_project(tmp_path))
    qtbot.addWidget(workbench)
    monkeypatch.setattr(MemoryMapWorkbench, "_ask_save", lambda self: pytest.fail("asked"))
    workbench.reject()
    assert workbench.config_tab.table.rowCount() == 0 and tab_module.NO_RESULT_NOTE in (
        workbench.config_tab.notes_label.text())


def test_a_damaged_file_is_named_on_the_tab(qtbot, tmp_path, chip_regions, no_question):
    path = config_path(tmp_path)
    path.parent.mkdir(parents=True)
    path.write_text("{bad", encoding="utf-8")
    tab = _open(qtbot, tmp_path, chip_regions).config_tab
    assert "无法读取" in tab.notes_label.text() and "memorymap.json" in tab.notes_label.text()
