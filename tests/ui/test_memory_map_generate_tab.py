"""Memory map workbench, tab "配置": generating the linker file (add-linker-file-generation,
section 6): the compiler choice, the reserve option, refusals, the preview with confirm and
cancel, writing with a backup, and the self-check shown after writing."""
import pytest
from PySide6.QtCore import Qt

from autosar_configurator.core.memmap import linkfile as lf
from autosar_configurator.core.memmap.plan import reserve_missing_cores
from autosar_configurator.core.memmap.scatter import parse_scatter
from autosar_configurator.core.memmap.session import LayoutSession
from autosar_configurator.ui.dialogs.memory_map_config_tab import (
    GenerationPreviewDialog,
    generation_preview_lines,
)

from tests.ui.test_memory_map_config_tab import (  # noqa: F401 - fixtures
    BSS0,
    TEXT,
    _open,
    _project,
    chip_regions,
    no_question,
)


def _tab(qtbot, tmp_path, chip_regions, project=None):
    return _open(qtbot, tmp_path, chip_regions, project).config_tab


def _target(tmp_path):
    return tmp_path / "IntegrationProject" / "linkedFile" / "Ads" / "scatter.scat"


@pytest.fixture
def confirm(monkeypatch):
    """Answer the generation preview; records what it was shown."""
    shown = []

    def answer(value=True):
        def confirm_generation(tab, generation, preview):
            shown.append((generation, preview))
            return value
        from autosar_configurator.ui.dialogs.memory_map_config_tab import ConfigTab
        monkeypatch.setattr(ConfigTab, "confirm_generation", confirm_generation)
        return shown
    return answer


# --- the choice -----------------------------------------------------------------------------------

def test_only_ads_can_be_chosen(qtbot, tmp_path, chip_regions, no_question):
    tab = _tab(qtbot, tmp_path, chip_regions)
    combo = tab.compiler_combo
    keys = [combo.itemData(i) for i in range(combo.count())]
    assert keys == ["ads", "ghs", "hightec", "iar", "tasking"]
    assert tab.compiler_key() == "ads"
    enabled = [combo.model().item(i).isEnabled() for i in range(combo.count())]
    assert enabled == [True, False, False, False, False]
    assert "尚未支持" in combo.itemText(1)
    assert "尚未支持" in combo.itemData(1, Qt.ToolTipRole)       # the reason


def test_the_reserve_option_is_on_and_saved_when_switched_off(qtbot, tmp_path, chip_regions, no_question):
    project = _project(tmp_path)
    tab = _tab(qtbot, tmp_path, chip_regions, project)
    assert tab.reserve_check.isChecked()
    tab.session.dirty = False
    tab.reserve_check.setChecked(False)
    assert not reserve_missing_cores(tab.session.config) and tab.session.dirty
    assert tab.save()
    assert not reserve_missing_cores(LayoutSession.open(project).config)


# --- generating ---------------------------------------------------------------------------------------

def test_generate_writes_the_file_after_the_preview(qtbot, tmp_path, chip_regions, no_question, confirm):
    shown = confirm(True)
    tab = _tab(qtbot, tmp_path, chip_regions)
    path = tab.generate_linker_file()
    assert path == _target(tmp_path) and path.is_file()
    (generation, preview), = shown
    assert preview.path == path and not preview.replaces
    assert path.read_text(encoding="utf-8") == generation.file.text
    regions = {r.name for r in parse_scatter(generation.file.text, "scatter.scat").regions}
    assert {"PRIVATE_BSS_CORE0", "EX_CODE", "UNDEFINE_RAM_BSS"} <= regions
    assert tab.open_dir_button.isEnabled() and tab.generated_path == path


def test_the_self_check_is_shown_with_its_limits(qtbot, tmp_path, chip_regions, no_question, confirm):
    confirm(True)
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.generate_linker_file()
    assert tab.last_self_check.clean
    assert "自检通过" in tab.message_label.text()
    assert any("不能证明" in line for line in tab.messages())
    assert any("缺少链接符号 0 处，没有区域接收的段 0 个" in line for line in tab.messages())


def test_a_section_not_placed_is_warned_and_found_by_the_self_check(qtbot, tmp_path, chip_regions, no_question,
                                                                   confirm):
    shown = confirm(True)
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.session.config.rules = [r for r in tab.session.config.rules if r.target != "EX_CODE"]
    tab.refresh()
    assert tab.placement(TEXT).status == "not-placed"
    assert tab.generate_linker_file() is not None
    (generation, _), = shown
    assert any(TEXT in w for w in generation.warnings)
    assert not tab.last_self_check.clean
    assert [f.text.split("（")[0] for f in tab.last_self_check.unplaced] == [TEXT]
    assert "自检发现问题" in tab.message_label.text()


def test_refused_generation_writes_nothing(qtbot, tmp_path, chip_regions, no_question, confirm):
    shown = confirm(True)
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.session.config.manual[BSS0] = "GONE"
    tab.refresh()
    assert tab.generate_linker_file() is None
    assert shown == [] and not (tmp_path / "IntegrationProject").exists()
    assert "无法生成" in tab.message_label.text()
    assert any(BSS0 in line and "待重新放置" in line for line in tab.messages())


def test_cancel_at_the_preview_writes_nothing(qtbot, tmp_path, chip_regions, no_question, confirm):
    shown = confirm(False)
    tab = _tab(qtbot, tmp_path, chip_regions)
    assert tab.generate_linker_file() is None
    assert len(shown) == 1 and not (tmp_path / "IntegrationProject").exists()
    assert "已取消生成" in tab.message_label.text()


def test_an_existing_file_is_backed_up_and_an_unchanged_one_said(qtbot, tmp_path, chip_regions, no_question,
                                                                confirm):
    shown = confirm(True)
    tab = _tab(qtbot, tmp_path, chip_regions)
    target = _target(tmp_path)
    target.parent.mkdir(parents=True)
    target.write_text("old\n", encoding="utf-8")
    tab.generate_linker_file()
    assert shown[-1][1].replaces and target.with_name("scatter.scat.bak").read_text(encoding="utf-8") == "old\n"
    tab.generate_linker_file()
    assert shown[-1][1].unchanged and "内容未变" in tab.message_label.text()


def test_a_failed_write_is_shown(qtbot, tmp_path, chip_regions, no_question, confirm, monkeypatch):
    confirm(True)
    tab = _tab(qtbot, tmp_path, chip_regions)

    def broken(path, text):
        raise lf.LinkFileError("磁盘已满")

    monkeypatch.setattr(lf, "write_linker_file", broken)
    assert tab.generate_linker_file() is None
    assert "生成失败" in tab.message_label.text() and "磁盘已满" in tab.message_label.text()
    assert not tab.open_dir_button.isEnabled()


def test_generation_needs_a_scan(qtbot, tmp_path, chip_regions, no_question, confirm):
    shown = confirm(True)
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.result = None
    assert tab.generate_linker_file() is None
    assert shown == [] and "先在上方开始扫描" in tab.message_label.text()


def test_the_preview_dialog(qtbot, tmp_path, chip_regions, no_question, confirm):
    shown = confirm(False)
    tab = _tab(qtbot, tmp_path, chip_regions)
    tab.generate_linker_file()
    (generation, preview), = shown
    text = "\n".join(generation_preview_lines(generation, preview))
    assert f"写入：{preview.path}" in text and "新建文件" in text
    assert "不需要、也不参照厂商脚本" in text
    assert "警告" in text                                   # no needs scanned: default layout warning
    dialog = GenerationPreviewDialog(generation, preview)
    qtbot.addWidget(dialog)
    assert dialog.text.toPlainText() == generation.file.text and dialog.text.isReadOnly()
