"""Memory map workbench, tab "配置" (update-linker-generator-authority, section 5): the
properties of an execution region (kind, start, size, load region, limit alignment), the load
region dialog, and importing a linker file with its preview."""
import pytest

from autosar_configurator.core.memmap.config import (
    AFTER,
    FIXED,
    KIND_UNCONFIRMED_KEY,
    OFFSET,
    config_dict,
)
from autosar_configurator.core.memmap.session import LayoutSession
from autosar_configurator.ui.dialogs.memory_map_config_tab import (
    UNCONFIRMED_MARK,
    ImportPreviewDialog,
    LoadRegionDialog,
    import_preview_lines,
)

from tests.ui.test_memory_map_config_tab import (  # noqa: F401 - fixtures
    BSS0,
    _open,
    _project,
    _status,
    chip_regions,
    no_question,
)

SCAT = """\
#define CPUXPFLASH0_ADDRESS    0x08000000
#define GMU_NORMAL_ADDRESS     0x10000000
#define CPU0BTCM_ADDRESS       0x30100000
#define DFLASH_ADDRESS         0x44000000

ROM_CODE CPUXPFLASH0_ADDRESS 0x300000
{
    MY_CODE CPUXPFLASH0_ADDRESS ALIGN 64 0x10000
    {
        *(.my_text)
    }
    MY_DATA GMU_NORMAL_ADDRESS+0x30000 ALIGN 64 0x1000
    {
        *(.my_data_x)
        *(+RW-DATA)
    }
    MY_GUESS CPU0BTCM_ADDRESS+0x20000 ALIGN 64 0x100
    {
        *(.weird)
    }
    MY_STACK 0x30128000 ALIGN 8 EMPTY 0x800 {}
    MY_STACK_LIMIT AlignExpr(ImageLimit(MY_STACK), 64) EMPTY 0x0 {}
    UNDEFINE_RAM_BSS AlignExpr(ImageLimit(MY_DATA), 64) ALIGN 64 0x1000
    {
        *(.mcal_bss_asil_d_unspecified_core0)
    }
}

DFLASH_X DFLASH_ADDRESS 0x10000
{
    MY_DFLASH DFLASH_ADDRESS ALIGN 64 0x1000
    {
        *(.my_dflash_const)
    }
}
"""


def _tab(qtbot, tmp_path, chip_regions, project=None):
    return _open(qtbot, tmp_path, chip_regions, project).config_tab


def _form(tab, start=None, offset=None, address=None, size=None, load=None, limit=None, kind=None):
    if kind is not None:
        tab.prop_kind.setCurrentIndex(tab.prop_kind.findData(kind))
    if start is not None:
        tab.prop_start.setCurrentIndex(tab.prop_start.findData(start))
    for edit, value in ((tab.prop_offset, offset), (tab.prop_address, address), (tab.prop_size, size),
                        (tab.prop_limit, limit)):
        if value is not None:
            edit.setText(value)
    if load is not None:
        tab.prop_load.setCurrentIndex(tab.prop_load.findData(load))


# --- region properties (5.1) -----------------------------------------------------------------------

def test_the_form_follows_the_selected_region(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    assert not tab.props.isEnabled()                    # nothing selected
    tab.select_region("CORE0_USER_STACK")               # factory: fixed 0x30129000, size 0x1000
    assert tab.props.isEnabled() and tab.prop_name.text() == "CORE0_USER_STACK"
    assert tab.prop_start.currentData() == FIXED
    assert tab.prop_address.text() == "0x30129000" and tab.prop_address.isEnabled()
    assert not tab.prop_offset.isEnabled()
    assert tab.prop_size.text() == "0x1000" and tab.prop_limit.text() == "64"
    assert not tab.prop_kind.isEnabled()                # a required region keeps its kind
    tab.select_region("UNDEFINE_RAM_DATA")              # factory: offset 0x20000
    assert (tab.prop_start.currentData(), tab.prop_offset.text()) == (OFFSET, "0x20000")
    assert tab.prop_offset.isEnabled() and not tab.prop_address.isEnabled()


def test_offset_size_and_limit_applied_and_shown_in_the_tree(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.select_region("UNDEFINE_RAM_BSS")
    _form(tab, start=OFFSET, offset="30000", size="8000", limit="0x100")
    assert tab.apply_properties() == ""
    region = tab.session.config.region("UNDEFINE_RAM_BSS")
    assert (region.start_mode, region.offset, region.address, region.size, region.limit_align) == (
        OFFSET, 0x30000, None, 0x8000, 0x100)
    item = tab.region_item("UNDEFINE_RAM_BSS")
    assert (item.text(4), item.text(5)) == ("窗口+0x30000", "0x8000")
    assert tab.session.dirty and "已更新" in tab.message_label.text()
    assert tab.selected_region() == "UNDEFINE_RAM_BSS"


def test_fixed_address_outside_the_window_is_applied_with_a_doubt(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.select_region("PRIVATE_BSS_CORE0")              # on CPU0BTCM
    _form(tab, start=FIXED, address="0x10000000")
    assert tab.apply_properties() == ""
    assert tab.session.config.region("PRIVATE_BSS_CORE0").address == 0x10000000
    assert "请核对" in tab.message_label.text()
    assert any("不在窗口" in line for line in tab.messages())


def test_back_to_after_clears_offset_and_address(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.select_region("CORE0_USER_STACK")
    _form(tab, start=AFTER)
    assert tab.apply_properties() == ""
    region = tab.session.config.region("CORE0_USER_STACK")
    assert (region.start_mode, region.offset, region.address) == (AFTER, 0, None)
    assert tab.region_item("CORE0_USER_STACK").text(4) == "接上一个"


def test_clearing_the_size_goes_back_to_the_default(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.select_region("CORE0_USER_STACK")
    _form(tab, size="")
    assert tab.apply_properties() == ""
    assert tab.session.config.region("CORE0_USER_STACK").size is None


@pytest.mark.parametrize("fields, message", [
    (dict(start=OFFSET, offset="xyz"), "偏移"),
    (dict(start=FIXED, address=""), "固定地址"),
    (dict(size="-1"), "大小"),
    (dict(size="0"), "大小必须为正数"),
    (dict(limit="48"), "2 的幂"),
    (dict(limit="abc"), "界限对齐"),
])
def test_bad_input_changes_nothing(qtbot, tmp_path, chip_regions, no_question, fields, message):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.select_region("UNDEFINE_RAM_BSS")
    before = config_dict(tab.session.config)
    dirty = tab.session.dirty
    _form(tab, **fields)
    error = tab.apply_properties()
    assert message in error and message in tab.message_label.text()
    assert config_dict(tab.session.config) == before and tab.session.dirty == dirty


def test_load_region_choice_lists_the_configured_ones(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.select_region("UNDEFINE_RAM_BSS")
    choices = [tab.prop_load.itemData(i) for i in range(tab.prop_load.count())]
    assert choices == ["", "ROM_CODE", "DFLASH_CODE"]       # factory load regions, first by default
    assert "第一个：ROM_CODE" in tab.prop_load.itemText(0)
    _form(tab, load="DFLASH_CODE")
    assert tab.apply_properties() == ""
    assert tab.session.config.region("UNDEFINE_RAM_BSS").load_region == "DFLASH_CODE"
    assert tab.region_item("UNDEFINE_RAM_BSS").text(6) == "DFLASH_CODE"


def test_no_change_is_said_and_not_dirty(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.session.dirty = False
    tab.select_region("UNDEFINE_RAM_BSS")
    assert tab.apply_properties() == ""
    assert "没有改动" in tab.message_label.text() and not tab.session.dirty


def test_kind_of_a_user_region_can_change(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.select_region("UNDEFINE_RAM_DATA")
    assert tab.add_region("MY_BUF", "data") == ""
    tab.select_region("MY_BUF")
    assert tab.prop_kind.isEnabled()
    _form(tab, kind="noinit")
    assert tab.apply_properties() == ""
    assert tab.session.config.region("MY_BUF").kind == "noinit"


def test_properties_survive_save_and_reopen(qtbot, tmp_path, chip_regions, no_question):
    project = _project(tmp_path)
    tab = _tab(qtbot, tmp_path, chip_regions, project)
    tab.select_region("UNDEFINE_RAM_BSS")
    _form(tab, start=OFFSET, offset="30000", size="8000", load="DFLASH_CODE", limit="128")
    assert tab.apply_properties() == ""
    assert tab.save()
    region = LayoutSession.open(project).config.region("UNDEFINE_RAM_BSS")
    assert (region.start_mode, region.offset, region.size, region.load_region, region.limit_align) == (
        OFFSET, 0x30000, 0x8000, "DFLASH_CODE", 128)


# --- load regions (5.2) ------------------------------------------------------------------------------

def _loads(qtbot, tab) -> LoadRegionDialog:
    dialog = tab.open_load_regions()
    qtbot.addWidget(dialog)
    return dialog


def _rows(dialog):
    return [[dialog.tree.topLevelItem(i).text(c) for c in range(1, 5)]
            for i in range(dialog.tree.topLevelItemCount())]


def test_the_dialog_lists_the_load_regions_in_order(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    dialog = _loads(qtbot, tab)
    assert _rows(dialog) == [["ROM_CODE", "CPUXPFLASH0", "0x08000000", "0x300000"],
                             ["DFLASH_CODE", "DFLASH_NORMAL", "0x44000000", "0x10000"]]


def test_add_a_load_region_with_the_window_size_by_default(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    dialog = _loads(qtbot, tab)
    dialog.set_fields(name="PFLASH1_CODE", window="CPUXPFLASH1", size="")
    assert dialog.add_from_fields() == ""
    load = tab.session.config.load_region("PFLASH1_CODE")
    assert (load.window, load.size) == ("CPUXPFLASH1", 0x300000)
    assert tab.session.dirty
    tab.select_region("UNDEFINE_RAM_BSS")               # the tab's choice follows
    assert tab.prop_load.findData("PFLASH1_CODE") >= 0


@pytest.mark.parametrize("name, size, message", [
    ("ROM_CODE", "", "已存在"),
    ("1BAD", "", "名称不对"),
    ("GOOD", "zz", "大小上限"),
])
def test_bad_load_region_refused(qtbot, tmp_path, chip_regions, no_question, name, size, message):
    tab = _tab(qtbot, tmp_path, chip_regions)
    dialog = _loads(qtbot, tab)
    before = config_dict(tab.session.config)
    dialog.set_fields(name=name, window="CPUXPFLASH1", size=size)
    assert message in dialog.add_from_fields()
    assert config_dict(tab.session.config) == before


def test_rename_a_load_region_and_its_regions_follow(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    assert tab.session.config.region("DFLASH_DATA").load_region == "DFLASH_CODE"
    dialog = _loads(qtbot, tab)
    assert dialog.select("DFLASH_CODE")
    assert dialog.name_edit.text() == "DFLASH_CODE" and dialog.size_edit.text() == "0x10000"
    dialog.set_fields(name="DF_CODE", size="40000")
    assert dialog.apply_edit() == ""
    assert tab.session.config.region("DFLASH_DATA").load_region == "DF_CODE"
    assert tab.session.config.load_region("DF_CODE").size == 0x40000


def test_rename_onto_an_existing_name_changes_nothing(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    dialog = _loads(qtbot, tab)
    dialog.select("DFLASH_CODE")
    before = config_dict(tab.session.config)
    dialog.set_fields(name="ROM_CODE", size="40000")
    assert "已存在" in dialog.apply_edit()
    assert config_dict(tab.session.config) == before


def test_move_and_remove_load_regions(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    dialog = _loads(qtbot, tab)
    dialog.select("DFLASH_CODE")
    assert dialog.move_selected(-1) == ""
    assert dialog.names() == ["DFLASH_CODE", "ROM_CODE"]
    assert "到头" in dialog.move_selected(-1)
    assert dialog.remove_selected() == ""
    assert dialog.names() == ["ROM_CODE"]
    assert tab.session.config.region("DFLASH_DATA").load_region == ""       # back to the first one
    assert "回到第一个加载区域 ROM_CODE" in dialog.message.text()


# --- import (5.3) -------------------------------------------------------------------------------------

@pytest.fixture
def scat(tmp_path):
    path = tmp_path / "vendor.scat"
    path.write_text(SCAT, encoding="utf-8")
    return path


def test_import_preview_then_confirm(qtbot, tmp_path, chip_regions, no_question, scat, monkeypatch):
    tab = _tab(qtbot, tmp_path, chip_regions)
    shown = []
    monkeypatch.setattr(tab, "confirm_import", lambda preview: shown.append(preview) or True)
    preview = tab.import_file(str(scat))
    assert shown == [preview]
    config = tab.session.config
    assert [l.name for l in preview.load_regions] == ["DFLASH_X"]
    assert config.load_region("DFLASH_X").window == "DFLASH_NORMAL"
    data = config.region("MY_DATA")
    assert (data.window, data.start_mode, data.offset, data.size) == ("GMU_NORMAL", OFFSET, 0x30000, 0x1000)
    stack = config.region("MY_STACK")
    assert (stack.kind, stack.start_mode, stack.address, stack.size) == ("stack", FIXED, 0x30128000, 0x800)
    assert config.region("MY_DFLASH").load_region == "DFLASH_X"
    assert config.manual[".my_text"] == "MY_CODE"
    # the configuration's own region is kept as it is; the section the file selects in it is
    # placed there by hand (nothing placed it by hand before)
    assert "UNDEFINE_RAM_BSS" in preview.skipped_regions
    assert config.region("UNDEFINE_RAM_BSS").origin != "imported"
    assert _status(tab, BSS0) == ("manual", "UNDEFINE_RAM_BSS")
    assert config.region("MY_STACK_LIMIT") is None
    assert tab.session.dirty and "已从 vendor.scat 导入" in tab.message_label.text()
    assert tab.region_item("MY_DATA") is not None


def test_a_guessed_kind_is_marked_until_confirmed(qtbot, tmp_path, chip_regions, no_question, scat, monkeypatch):
    tab = _tab(qtbot, tmp_path, chip_regions)
    monkeypatch.setattr(tab, "confirm_import", lambda preview: True)
    preview = tab.import_file(str(scat))
    assert "MY_GUESS" in preview.unconfirmed
    config = tab.session.config
    assert "MY_GUESS" in config.options[KIND_UNCONFIRMED_KEY]
    assert UNCONFIRMED_MARK in tab.region_item("MY_GUESS").text(2)
    assert "种类是导入时猜的" in tab.notes_label.text()
    tab.select_region("MY_GUESS")
    assert UNCONFIRMED_MARK in tab.prop_name.text()
    _form(tab, kind="const")
    assert tab.apply_properties() == ""
    assert config.region("MY_GUESS").kind == "const"
    assert "MY_GUESS" not in config.kind_unconfirmed()
    assert UNCONFIRMED_MARK not in tab.region_item("MY_GUESS").text(2)


def test_a_guessed_kind_is_confirmed_by_applying_it_unchanged(qtbot, tmp_path, chip_regions, no_question, scat,
                                                              monkeypatch):
    tab = _tab(qtbot, tmp_path, chip_regions)
    monkeypatch.setattr(tab, "confirm_import", lambda preview: True)
    tab.import_file(str(scat))
    tab.session.dirty = False
    tab.select_region("MY_GUESS")
    assert tab.apply_properties() == ""
    assert "MY_GUESS" not in tab.session.config.kind_unconfirmed() and tab.session.dirty


def test_cancelled_import_changes_nothing(qtbot, tmp_path, chip_regions, no_question, scat, monkeypatch):
    tab = _tab(qtbot, tmp_path, chip_regions)
    before = config_dict(tab.session.config)
    dirty = tab.session.dirty
    monkeypatch.setattr(tab, "confirm_import", lambda preview: False)
    tab.import_file(str(scat))
    assert config_dict(tab.session.config) == before and tab.session.dirty == dirty
    assert "已取消导入" in tab.message_label.text()


def test_import_needs_the_chip_windows(qtbot, tmp_path, chip_regions, no_question, scat):
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.result = None
    assert tab.import_file(str(scat)) is None
    assert "先在上方开始扫描" in tab.message_label.text()


def test_unreadable_file(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    assert tab.import_file(str(tmp_path / "missing.scat")) is None
    assert "无法读取" in tab.message_label.text()


def test_the_preview_dialog_lists_everything(qtbot, tmp_path, chip_regions, no_question, scat, monkeypatch):
    tab = _tab(qtbot, tmp_path, chip_regions)
    captured = []
    monkeypatch.setattr(tab, "confirm_import", lambda preview: captured.append(preview) or False)
    tab.import_file(str(scat))
    lines = import_preview_lines(captured[0])
    text = "\n".join(lines)
    assert "新增加载区域（1）" in text and "DFLASH_X：窗口 DFLASH_NORMAL" in text
    assert "MY_DATA：窗口 GMU_NORMAL" in text and "窗口起点加偏移 0x30000" in text
    assert "MY_STACK：窗口 CPU0BTCM" in text and "固定地址 0x30128000" in text
    assert "MY_GUESS" in text and UNCONFIRMED_MARK in text
    assert "配置里已有、不覆盖的执行区域" in text and "UNDEFINE_RAM_BSS" in text
    assert ".my_text → MY_CODE" in text
    assert "不能导入" in text and "MY_STACK_LIMIT" in text and "+RW-DATA" in text
    assert "导入不改规则" in text
    dialog = ImportPreviewDialog(captured[0])
    qtbot.addWidget(dialog)
    assert dialog.text.toPlainText() == text and dialog.text.isReadOnly()
