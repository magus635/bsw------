"""The chip designer keeps the chip's ``memory_regions`` (it has no editor for them yet)."""
import pytest
from PySide6.QtWidgets import QMessageBox

from autosar_configurator.core.hardware.chip_database import ChipDatabase
from autosar_configurator.core.hardware.memory_regions import LOCAL, MemoryRegionDef
from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

CHIP = ("name: CHIP_X\nresource_version: 1.0.0\n"
        "metadata:\n  cpu_frequency: 300000000\n  flash_size: 512KB\n  ram_size: 64KB\n"
        "  cores: {count: 1, available: [CORE0], master: CORE0}\n"
        "  unconfirmed:\n    memory_regions: 按链接脚本的注释表填写\n"
        "memory_regions:\n"
        "- {name: CPUXATCM, start: '0x0', size: '0x10000', type: ram, core: local, cacheable: false}\n"
        "- {name: GMU_NORMAL, start: '0x10000000', size: '0x40000', type: ram, cacheable: true}\n")
REGIONS = [MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", LOCAL, False),
           MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True)]


@pytest.fixture
def boxes(monkeypatch):
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: None)
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: None)
    monkeypatch.setattr(QMessageBox, "critical", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Yes)


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


def test_built_chip_carries_the_memory_regions(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    assert dialog._build_current_chip().memory_regions == REGIONS


def test_saving_an_unrelated_edit_keeps_the_regions_and_their_mark(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    dialog.basic_edits["flash_size"].setText("4MB")
    dialog._on_save_clicked()
    saved = ChipDatabase(library).get_chip("CHIP_X")
    assert saved.metadata["flash_size"] == "4MB"
    assert saved.memory_regions == REGIONS
    assert saved.metadata["unconfirmed"] == {"memory_regions": "按链接脚本的注释表填写"}


def test_regions_do_not_make_an_untouched_chip_look_edited(qtbot, library, boxes):
    dialog = _open(qtbot, library)
    assert not dialog._has_unsaved_edits()


def test_a_chip_without_regions_stays_without(qtbot, tmp_path, boxes):
    lib = tmp_path / "lib2"
    lib.mkdir()
    (lib / "CHIP_X.yaml").write_text(CHIP.split("memory_regions:")[0].replace(
        "  unconfirmed:\n    memory_regions: 按链接脚本的注释表填写\n", ""), encoding="utf-8")
    dialog = _open(qtbot, lib)
    assert dialog._build_current_chip().memory_regions == []
    dialog.basic_edits["flash_size"].setText("4MB")
    dialog._on_save_clicked()
    assert "memory_regions" not in (lib / "CHIP_X.yaml").read_text(encoding="utf-8")
