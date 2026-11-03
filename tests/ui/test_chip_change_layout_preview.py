"""Chip change preview, section "内存布局" (add-memory-layout-config, task 5.3): the report
carries the layout change, the dialog shows it only when there is one, computing it writes
nothing, and confirming applies it to the project's layout configuration."""
from types import SimpleNamespace
from unittest.mock import MagicMock, patch

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef
from autosar_configurator.core.memmap import chipchange
from autosar_configurator.core.memmap.config import (
    ExecRegion,
    MemoryMapConfig,
    config_path,
    load_config,
    save_config,
)
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.dialogs.chip_change_preview_dialog import (
    ChipChangePreviewDialog,
    ChipChangeReport,
)

OLD = [MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
       MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True, "GMU")]
NEW = [MemoryRegionDef("CPU0BTCM", 0x30100000, 0x30000, "ram", 0, False),
       MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, False, "GMU")]   # uncached now


def _config():
    config = MemoryMapConfig(chip="OLD_CHIP")
    config.regions = [ExecRegion("PRIVATE_BSS_CORE0", "CPU0BTCM", "CPU0BTCM", "bss", 1, required=True),
                      ExecRegion("UNDEFINE_RAM_BSS", "GMU", "GMU_NORMAL", "bss", 1, required=True)]
    config.manual = {".a": "UNDEFINE_RAM_BSS", ".b": "PRIVATE_BSS_CORE0"}
    return config


def _database():
    db = ChipDatabase()
    db.register_chip(ChipDefinition(name="OLD_CHIP", memory_regions=list(OLD)))
    db.register_chip(ChipDefinition(name="NEW_CHIP", memory_regions=list(NEW)))
    return db


def _project(tmp_path, with_config=True):
    project = SimpleNamespace(path=tmp_path / "p.dpa", selected_chip="OLD_CHIP", chip_database=_database())
    if with_config:
        save_config(_config(), config_path(tmp_path))
    return project


def _controller(project):
    win = MagicMock()
    win.current_project = project
    return ProjectController(win)


# --- report and dialog ---------------------------------------------------------------------------

def test_the_report_has_no_layout_section_by_default(qtbot):
    report = ChipChangeReport("NEW_CHIP", "OLD_CHIP")
    assert report.layout_lines == [] and report.layout_change is None
    dialog = ChipChangePreviewDialog(report)
    qtbot.addWidget(dialog)
    assert not dialog.layout_box.isVisibleTo(dialog)


def test_the_dialog_shows_the_layout_lines(qtbot):
    change = chipchange.compare(_config(), OLD, NEW)
    report = ChipChangeReport("NEW_CHIP", "OLD_CHIP", layout_lines=change.summary_lines(), layout_change=change)
    dialog = ChipChangePreviewDialog(report)
    qtbot.addWidget(dialog)
    assert dialog.layout_box.isVisibleTo(dialog) and dialog.layout_box.title() == "内存布局"
    text = dialog.layout_label.text()
    assert text.startswith("内存布局：保留 1 个执行区域，待重新放置 1 个")
    assert "待重新放置：UNDEFINE_RAM_BSS（可缓存 → 不可缓存）" in text
    assert ".a" in text and "不会被删除" in text


# --- the controller ------------------------------------------------------------------------------

def test_preview_computes_the_layout_change_and_writes_nothing(tmp_path):
    project = _project(tmp_path)
    path = config_path(tmp_path)
    before = path.read_bytes()
    report = ChipChangeReport("NEW_CHIP", "OLD_CHIP")
    ProjectController._layout_preview(project, "NEW_CHIP", report)
    assert report.layout_change.again == ["UNDEFINE_RAM_BSS"]
    assert report.layout_lines == chipchange.compare(_config(), OLD, NEW).summary_lines()
    assert path.read_bytes() == before and project.selected_chip == "OLD_CHIP"


def test_no_layout_file_no_section(tmp_path):
    project = _project(tmp_path, with_config=False)
    report = ChipChangeReport("NEW_CHIP", "OLD_CHIP")
    ProjectController._layout_preview(project, "NEW_CHIP", report)
    assert report.layout_lines == [] and not config_path(tmp_path).exists()


def test_empty_or_damaged_layout_file_no_section(tmp_path):
    project = _project(tmp_path, with_config=False)
    save_config(MemoryMapConfig(), config_path(tmp_path))
    report = ChipChangeReport("NEW_CHIP", "OLD_CHIP")
    ProjectController._layout_preview(project, "NEW_CHIP", report)
    assert report.layout_lines == []
    config_path(tmp_path).write_text("{bad", encoding="utf-8")
    ProjectController._layout_preview(project, "NEW_CHIP", report)
    assert report.layout_lines == []


def test_a_failure_skips_the_section_and_does_not_raise(tmp_path):
    project = _project(tmp_path)
    report = ChipChangeReport("NEW_CHIP", "OLD_CHIP")
    with patch.object(chipchange, "compare", side_effect=RuntimeError("boom")):
        ProjectController._layout_preview(project, "NEW_CHIP", report)
    assert report.layout_lines == [] and report.layout_change is None


def test_same_chip_has_no_layout_section(tmp_path):
    project = _project(tmp_path)
    report = ChipChangeReport("OLD_CHIP", "OLD_CHIP")
    ProjectController._layout_preview(project, "OLD_CHIP", report)
    assert report.layout_lines == []


def test_preview_chip_change_puts_the_section_on_the_report(tmp_path):
    project = _project(tmp_path)
    preview = SimpleNamespace(selector_result=SimpleNamespace(changed=[]), current_modules={}, modules={},
                              current_ecu_resources={}, ecu_resources={})
    project.module_managers, project.module_defs = {}, {}
    with patch("autosar_configurator.core.hardware.chip_selectors.preview_chip_change", return_value=preview), \
            patch("autosar_configurator.generator.eb.enable_conditions.disabled_containers", return_value=[]):
        report = _controller(project).preview_chip_change("NEW_CHIP")
    assert report.error is None
    assert report.layout_lines and "UNDEFINE_RAM_BSS" in report.layout_lines[1]


def test_confirmed_change_applies_and_saves_the_layout(tmp_path):
    project = _project(tmp_path)
    controller = _controller(project)
    report = ChipChangeReport("NEW_CHIP", "OLD_CHIP")
    controller._layout_preview(project, "NEW_CHIP", report)
    project.selected_chip = "NEW_CHIP"
    assert controller.apply_layout_change(report) is True
    config = load_config(config_path(tmp_path))
    assert config.chip == "NEW_CHIP" and config.options[chipchange.AGAIN_KEY] == ["UNDEFINE_RAM_BSS"]
    assert config.manual == _config().manual and len(config.regions) == 2      # nothing removed


def test_nothing_applied_without_a_layout_change(tmp_path):
    project = _project(tmp_path)
    before = config_path(tmp_path).read_bytes()
    assert _controller(project).apply_layout_change(ChipChangeReport("NEW_CHIP", "OLD_CHIP")) is False
    assert _controller(project).apply_layout_change(None) is False
    assert config_path(tmp_path).read_bytes() == before


def test_project_properties_applies_the_layout_only_on_confirm(tmp_path):
    from autosar_configurator.ui.dialogs import project_properties_dialog as ppd

    for confirm in (False, True):
        project = _project(tmp_path)
        controller = _controller(project)
        report = ChipChangeReport("NEW_CHIP", "OLD_CHIP")
        controller._layout_preview(project, "NEW_CHIP", report)
        data = {"name": "p", "version": "1", "author": "", "description": "", "selected_chip": "NEW_CHIP"}
        dialog = MagicMock()
        dialog.exec.return_value = True
        dialog.get_data.return_value = data
        with patch("importlib.reload", side_effect=lambda m: m), \
                patch.object(ppd, "ProjectPropertiesDialog", return_value=dialog), \
                patch.object(ProjectController, "preview_chip_change", return_value=report), \
                patch.object(ProjectController, "_show_chip_change_preview", return_value=confirm), \
                patch.object(ProjectController, "apply_project_chip"), \
                patch.object(ProjectController, "_ecu_resource_status", return_value=""), \
                patch.object(ProjectController, "_selector_status", return_value=""), \
                patch("PySide6.QtWidgets.QApplication.setOverrideCursor"), \
                patch("PySide6.QtWidgets.QApplication.restoreOverrideCursor"):
            controller.show_project_properties()
        config = load_config(config_path(tmp_path))
        if confirm:
            assert config.chip == "NEW_CHIP" and config.options[chipchange.AGAIN_KEY] == ["UNDEFINE_RAM_BSS"]
        else:
            assert config.chip == "OLD_CHIP" and chipchange.AGAIN_KEY not in config.options
