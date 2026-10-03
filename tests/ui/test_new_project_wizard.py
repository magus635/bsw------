"""
Tests for the New Project Wizard
"""
import pytest
from pathlib import Path
from unittest.mock import MagicMock, patch
from PySide6.QtCore import Qt

from autosar_configurator.ui.wizards.new_project_wizard import (
    NewProjectWizard, ProjectInfoPage, ChipSelectionPage, ProjectSummaryPage
)
from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition
from autosar_configurator.core.config_manager import ProjectType


@pytest.fixture
def chip_db(tmp_path):
    """Create a chip database with test data"""
    db = ChipDatabase()
    chip = ChipDefinition(
        name="TEST_MCU_100",
        family="TEST",
        package="LQFP100",
        description="Test MCU for wizard tests"
    )
    db.register_chip(chip)

    chip2 = ChipDefinition(
        name="TEST_MCU_200",
        family="TEST",
        package="BGA200",
        description="Second test MCU"
    )
    db.register_chip(chip2)
    return db


def test_wizard_creates_with_pages(qtbot, chip_db):
    """Test wizard initializes with correct page structure"""
    wizard = NewProjectWizard(chip_database=chip_db)
    qtbot.addWidget(wizard)

    # Should have 3 pages
    assert len(wizard.pageIds()) == 3
    assert isinstance(wizard.info_page, ProjectInfoPage)
    assert isinstance(wizard.chip_page, ChipSelectionPage)
    assert isinstance(wizard.summary_page, ProjectSummaryPage)


def test_project_info_page_validation(qtbot, chip_db):
    """Test ProjectInfoPage requires name and folder"""
    wizard = NewProjectWizard(chip_database=chip_db)
    qtbot.addWidget(wizard)
    wizard.show()

    page = wizard.info_page

    # Initially incomplete (no name, no folder)
    assert not page.isComplete()

    # Add name but no folder — still incomplete
    page.name_edit.setText("MyProject")
    assert not page.isComplete()

    # Set folder — now complete
    page._folder_path = Path("/tmp/test_project")
    page.completeChanged.emit()
    assert page.isComplete()

    # Verify getters
    assert page.get_project_name() == "MyProject"
    assert page.get_folder_path() == Path("/tmp/test_project")
    assert page.get_project_type() in (ProjectType.EB_TRESOS, ProjectType.VECTOR)


def test_chip_selection_page_lists_chips(qtbot, chip_db):
    """Test ChipSelectionPage populates from database"""
    wizard = NewProjectWizard(chip_database=chip_db)
    qtbot.addWidget(wizard)

    page = wizard.chip_page

    # Should list our 2 test chips
    assert page.chip_list.count() == 2

    # Initially no selection
    assert page.get_selected_chip() is None
    assert not page.isComplete()


def test_chip_selection_page_select_chip(qtbot, chip_db):
    """Test selecting a chip makes page complete and shows info"""
    wizard = NewProjectWizard(chip_database=chip_db)
    qtbot.addWidget(wizard)

    page = wizard.chip_page

    # Select first chip
    page.chip_list.setCurrentRow(0)

    # Should be complete now
    assert page.isComplete()
    assert page.get_selected_chip() is not None

    # Info panel should have content
    info_text = page.chip_info.toPlainText()
    assert "TEST" in info_text


def test_chip_selection_page_skip(qtbot, chip_db):
    """Test skip checkbox allows proceeding without chip"""
    wizard = NewProjectWizard(chip_database=chip_db)
    qtbot.addWidget(wizard)

    page = wizard.chip_page

    # No chip selected, not complete
    assert not page.isComplete()

    # Check skip — should be complete
    page.skip_check.setChecked(True)
    assert page.isComplete()
    assert page.get_selected_chip() is None


def test_wizard_get_result(qtbot, chip_db):
    """Test collecting results from all pages"""
    wizard = NewProjectWizard(chip_database=chip_db)
    qtbot.addWidget(wizard)
    wizard.show()

    # Fill page 1
    wizard.info_page.name_edit.setText("TestProject")
    wizard.info_page._folder_path = Path("/tmp/testdir")

    # Select chip on page 2
    wizard.chip_page.chip_list.setCurrentRow(0)

    result = wizard.get_result()
    assert result["project_name"] == "TestProject"
    assert result["folder_path"] == Path("/tmp/testdir")
    assert result["selected_chip"] is not None
    assert result["project_type"] in (ProjectType.EB_TRESOS, ProjectType.VECTOR)


def test_wizard_empty_chip_database(qtbot):
    """Test wizard works gracefully with empty chip database"""
    empty_db = ChipDatabase()
    wizard = NewProjectWizard(chip_database=empty_db)
    qtbot.addWidget(wizard)

    page = wizard.chip_page

    # Should show placeholder item
    assert page.chip_list.count() == 1
    item = page.chip_list.item(0)
    assert not (item.flags() & Qt.ItemIsSelectable)

    # Skip should still work
    page.skip_check.setChecked(True)
    assert page.isComplete()
