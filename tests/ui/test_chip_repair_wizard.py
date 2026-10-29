"""add-chip-repair-wizard: the chip repair wizard and its entry points."""
import copy

import pytest
import yaml
from PySide6.QtCore import Qt
from PySide6.QtWidgets import QDialog

from autosar_configurator.core.hardware import chip_repair as repair
from autosar_configurator.core.hardware.chip_completeness import check_chip, unconfirmed_marks
from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition
from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter, chip_checksum
from autosar_configurator.ui.wizards import chip_repair_wizard as wiz

CHIP = ChipDefinition(name="C", resource_version="1.0.0",
                      metadata={"unconfirmed": {"metadata.flash_size": "x", "ports": "y"}},
                      ecu_resources={"Port": {"A": 1, "B": 2, "Gone": 0}, "Mcu": {"M": 1}})


@pytest.fixture
def messages(monkeypatch):
    shown = []
    for kind in ("warning", "critical", "information"):
        monkeypatch.setattr(wiz.QMessageBox, kind,
                            lambda *a, _k=kind, **k: shown.append((_k, a[2] if len(a) > 2 else "")))
    monkeypatch.setattr(repair, "git_author", lambda cwd=None: "tester")
    return shown


@pytest.fixture
def library(tmp_path):
    lib = tmp_path / "chips"
    lib.mkdir()
    ChipDefinitionExporter().save_yaml(CHIP, lib / "C.yaml")
    ChipDefinitionExporter().save_yaml(ChipDefinition(name="D"), lib / "D.yaml")
    return ChipDatabase(lib)


@pytest.fixture
def source(tmp_path):
    path = tmp_path / "Port.properties"
    path.write_text("Port.A: 1\nPort.B: 5\nPort.New: 7\n", encoding="utf-8")
    return path


def _wizard(qtbot, library, chip="C", project=None):
    wizard = wiz.ChipRepairWizard(library, chip, project)
    qtbot.addWidget(wizard)
    wizard.restart()
    return wizard


def _to_changes(wizard, *files):
    assert wizard.currentPage() is wizard.chip_page
    wizard.next()
    for f in files:
        wizard.sources_page.add_file(f)
    wizard.next()
    assert wizard.currentPage() is wizard.changes_page


def _checked(wizard):
    return {i.data(0, Qt.UserRole) for i in wizard.changes_page.key_items() if i.checkState(0) == Qt.Checked}


def _finish(wizard, messages):
    """Like the Finish button: QWizard.accept() validates (and so saves) the last page."""
    while wizard.currentPage() is not wizard.save_page:
        wizard.next()
    wizard.accept()
    assert wizard.result() == QDialog.Accepted
    assert messages == []


def test_validated_then_accepted_saves_once(qtbot, library, source, messages):
    wizard = _wizard(qtbot, library)
    _to_changes(wizard, source)
    while wizard.currentPage() is not wizard.save_page:
        wizard.next()
    assert wizard.save_page.validatePage()
    wizard.accept()
    assert messages == [] and wizard.result() == QDialog.Accepted
    entries = yaml.safe_load((library.data_dir / "history" / "C.yaml").read_text(encoding="utf-8"))["entries"]
    assert len(entries) == 1


def test_chip_page_shows_version_completeness_and_history(qtbot, library, messages):
    base = copy.deepcopy(library.get_chip("C"))
    chip = copy.deepcopy(base)
    chip.ecu_resources["Mcu"]["M"] = 2
    repair.save_repaired_chip(library, chip, base, repair.RepairRecord(source="earlier", note="n"))
    wizard = _wizard(qtbot, library)
    text = wizard.chip_page.info.toPlainText()
    assert "resource_version: 1.0.1" in text
    assert "metadata.flash_size 待确认" in text
    assert "earlier" in text and "tester" in text


def test_default_selection_and_module_unchecked(qtbot, library, source, messages):
    wizard = _wizard(qtbot, library)
    _to_changes(wizard, source)
    assert _checked(wizard) == {"Port.B", "Port.New"}          # removal Port.Gone not preselected
    port = wizard.changes_page.tree.topLevelItem(0)
    assert port.text(0) == "Port"
    port.setCheckState(0, Qt.Unchecked)
    assert wizard.session.selected == set()
    port.child(0).setCheckState(0, Qt.Checked)
    assert len(wizard.session.selected) == 1


def test_filter_shows_only_one_kind(qtbot, library, source, messages):
    wizard = _wizard(qtbot, library)
    _to_changes(wizard, source)
    wizard.changes_page.filter_combo.setCurrentText("删除")
    visible = [i.data(0, Qt.UserRole) for i in wizard.changes_page.key_items() if not i.isHidden()]
    assert visible == ["Port.Gone"]


def test_saved_with_backup_and_history(qtbot, library, source, messages):
    wizard = _wizard(qtbot, library)
    repaired = []
    wizard.chip_repaired.connect(repaired.append)
    _to_changes(wizard, source)
    wizard.next()
    wizard.marks_page.set_action("metadata.flash_size", wiz.CONFIRM, "按 SDK 核对")
    wizard.next()
    review = wizard.review_page.text.toPlainText()
    assert "已解决:\n  • metadata.flash_size" in review
    wizard.next()
    assert wizard.save_page.source_edit.text() == "Port.properties"
    assert wizard.save_page.version_edit.text() == "1.0.1"
    assert wizard.save_page.author_edit.text() == "tester"
    _finish(wizard, messages)

    assert repaired == ["C"]
    chip = library.get_chip("C")
    assert chip.ecu_resources["Port"] == {"A": 1, "B": 5, "Gone": 0, "New": 7}
    assert "metadata.flash_size" not in unconfirmed_marks(chip)
    assert (library.data_dir / "C.yaml.bak").exists()
    entry = yaml.safe_load((library.data_dir / "history" / "C.yaml").read_text(encoding="utf-8"))["entries"][0]
    assert entry["confirmed"] == [{"field": "metadata.flash_size", "note": "按 SDK 核对"}]
    assert entry["author"] == "tester"


def test_marks_only(qtbot, library, messages):
    wizard = _wizard(qtbot, library)
    _to_changes(wizard)
    assert "没有差异" in wizard.changes_page.count_label.text()
    wizard.next()
    wizard.marks_page.set_action("ports", wiz.CONFIRM, "ok")
    wizard.marks_page.add_mark("ecu_resources.Mcu", "待核对")
    _finish(wizard, messages)
    chip = library.get_chip("C")
    assert unconfirmed_marks(chip) == {"metadata.flash_size": "x", "ecu_resources.Mcu": "待核对"}
    assert chip.ecu_resources == CHIP.ecu_resources


def test_cancel_writes_nothing(qtbot, library, source, messages):
    before = sorted(p.name for p in library.data_dir.iterdir())
    wizard = _wizard(qtbot, library)
    _to_changes(wizard, source)
    wizard.next()
    wizard.next()
    wizard.reject()
    assert sorted(p.name for p in library.data_dir.iterdir()) == before


def test_file_changed_meanwhile_keeps_wizard_open(qtbot, library, source, messages):
    wizard = _wizard(qtbot, library)
    _to_changes(wizard, source)
    ChipDefinitionExporter().save_yaml(ChipDefinition(name="C", ecu_resources={"Port": {"A": 9}}),
                                       library.data_dir / "C.yaml")
    while wizard.currentPage() is not wizard.save_page:
        wizard.next()
    assert not wizard.save_page.validatePage()
    assert messages and messages[-1][0] == "warning"
    assert not (library.data_dir / "C.yaml.bak").exists()


def test_save_requires_source_and_author(qtbot, library, source, messages):
    wizard = _wizard(qtbot, library)
    _to_changes(wizard, source)
    while wizard.currentPage() is not wizard.save_page:
        wizard.next()
    wizard.save_page.author_edit.setText("")
    assert not wizard.save_page.validatePage()
    assert not (library.data_dir / "history").exists()


def test_nothing_to_save(qtbot, library, messages):
    wizard = _wizard(qtbot, library, chip="D")
    _to_changes(wizard)
    while wizard.currentPage() is not wizard.save_page:
        wizard.next()
    assert "没有任何改动" in wizard.save_page.summary.text()
    assert not wizard.save_page.validatePage()


def test_changing_the_chip_starts_a_new_session(qtbot, library, source, messages):
    wizard = _wizard(qtbot, library)
    _to_changes(wizard, source)
    wizard.back()
    wizard.back()
    wizard.chip_page.chip_combo.setCurrentIndex(wizard.chip_page.chip_combo.findData("D"))
    wizard.next()
    assert wizard.session.base.name == "D" and not wizard.session.diff


def test_port_tree_of_thA6412_builds_quickly(qtbot, tmp_path, messages):
    import shutil
    import time

    from autosar_configurator.core.hardware.chip_database import default_chips_dir

    lib = tmp_path / "chips"
    lib.mkdir()
    shutil.copy2(default_chips_dir() / "THA6412_BGA516.yaml", lib)
    db = ChipDatabase(lib)
    wizard = _wizard(qtbot, db, "THA6412_BGA516")
    wizard.next()
    session = wizard.session
    # every Port key changed: the largest difference a vendor update produces
    session.diff = repair.EcuDiff([repair.KeyChange(f"Port.{k}", repair.CHANGED, v, "x")
                                   for k, v in sorted(session.base.ecu_resources["Port"].items())])
    session.selected = set(session.default_selection())
    start = time.perf_counter()
    wizard.changes_page.initializePage()
    elapsed = time.perf_counter() - start
    assert sum(1 for _ in wizard.changes_page.key_items()) == len(session.base.ecu_resources["Port"])
    assert elapsed < 1.0, elapsed


# --- entries to fill in (mark-chip-entries-to-fill-in) --------------------------------

@pytest.fixture
def scanned(monkeypatch, tmp_path):
    """A plugin directory whose modules reference Os.Missing, which chip C lacks."""
    from autosar_configurator.core.hardware import ecu_resource_diagnostics

    monkeypatch.setattr(ecu_resource_diagnostics, "collect_referenced_keys_in_dirs",
                        lambda dirs: {"Os.Missing": {"Os"}})
    return tmp_path


@pytest.fixture
def answer(monkeypatch):
    state = {"questions": [], "reply": wiz.QMessageBox.Yes}

    def question(*a, **k):
        state["questions"].append(a[1])
        return state["reply"]

    monkeypatch.setattr(wiz.QMessageBox, "question", question)
    return state


def _to_changes_scanning(wizard, directory, *files):
    wizard.next()
    for f in files:
        wizard.sources_page.add_file(f)
    wizard.sources_page.add_dir(directory)
    wizard.next()
    assert wizard.currentPage() is wizard.changes_page


def _key_item(wizard, key):
    return next(i for i in wizard.changes_page.key_items() if i.data(0, Qt.UserRole) == key)


def test_entry_to_fill_in_is_listed_but_not_preselected(qtbot, library, source, scanned, messages):
    wizard = _wizard(qtbot, library)
    _to_changes_scanning(wizard, scanned, source)
    assert _checked(wizard) == {"Port.B", "Port.New"}
    assert _key_item(wizard, "Os.Missing").text(wizard.changes_page.COL_NEW) == "（待填写）"


def test_saving_an_entry_to_fill_in_asks_first_and_marks_it(qtbot, library, scanned, messages, answer):
    wizard = _wizard(qtbot, library)
    _to_changes_scanning(wizard, scanned)
    _key_item(wizard, "Os.Missing").setCheckState(0, Qt.Checked)
    assert wizard.session.selected == {"Os.Missing"}
    wizard.next()
    wizard.next()
    assert "新出现:\n  • ecu_resources.Os.Missing 待确认：待填写" in wizard.review_page.text.toPlainText()
    wizard.next()
    assert "1 个条目没有值" in wizard.save_page.summary.text()

    answer["reply"] = wiz.QMessageBox.No
    assert not wizard.save_page.validatePage()
    assert answer["questions"] == ["ECU 资源待填写"]
    assert not (library.data_dir / "C.yaml.bak").exists()

    answer["reply"] = wiz.QMessageBox.Yes
    _finish(wizard, messages)
    chip = library.get_chip("C")
    assert chip.ecu_resources["Os"] == {"Missing": None}
    assert unconfirmed_marks(chip)["ecu_resources.Os.Missing"] == repair.TO_FILL_IN
    assert any(i.field == "ecu_resources.Os.Missing" for i in check_chip(chip))


# --- entry points -------------------------------------------------------------------

@pytest.fixture
def opened(monkeypatch):
    """Replace the wizard's exec(): record the wizard and, when ``repair`` is set, confirm
    every unconfirmed mark of its chip and report it as repaired."""
    state = {"wizards": [], "repair": False}

    def fake_exec(self):
        state["wizards"].append(self)
        if state["repair"]:
            session = repair.RepairSession(self.database, self.initial_chip, self.project)
            session.confirm_notes = {f: "ok" for f in unconfirmed_marks(session.base)}
            self.session = session
            self.result_info = session.save(repair.RepairRecord(source="t", author="t"))
            self.chip_repaired.emit(session.base.name)
        return 0

    monkeypatch.setattr(wiz.ChipRepairWizard, "exec", fake_exec)
    return state


def _project(tmp_path, library, chip="C"):
    from autosar_configurator.core.workspace_manager import WorkspaceProject

    project_dir = tmp_path / "proj"
    project_dir.mkdir(exist_ok=True)
    project = WorkspaceProject("p", project_dir / "p.dpa")
    project.chip_database = library
    project.selected_chip = chip
    return project


def test_main_window_menu_preselects_project_chip_and_tells_about_project_copy(
        monkeypatch, qtbot, tmp_path, library, messages, opened):
    from PySide6.QtWidgets import QMessageBox

    from autosar_configurator.ui import davinci_main_window as main_module
    from autosar_configurator.ui.davinci_main_window import DaVinciMainWindow

    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: QMessageBox.Discard)
    notices = []
    monkeypatch.setattr(main_module.QMessageBox, "information", lambda *a, **k: notices.append(a[2]))
    window = DaVinciMainWindow()
    qtbot.addWidget(window)
    project = _project(tmp_path, library)
    project.adopt_selected_chip()               # the project keeps its own copy of C
    window.current_project = project
    from PySide6.QtWidgets import QMenu

    assert any(isinstance(o, QMenu) for o in window.chip_repair_action.associatedObjects())
    copy_before = chip_checksum(project.chip_store.load("C"))

    opened["repair"] = True
    window.chip_repair_action.trigger()
    wizard = opened["wizards"][-1]
    assert wizard.initial_chip == "C" and wizard.database is library
    assert notices and "Update from Library" in notices[-1]
    assert chip_checksum(project.chip_store.load("C")) == copy_before        # copy untouched
    assert unconfirmed_marks(project.chip_store.load("C"))                    # still the old data
    assert not unconfirmed_marks(library.get_chip("C"))                       # the library is repaired


def test_designer_button_only_for_a_library_chip(qtbot, library, messages, opened):
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

    blank = ChipDefinitionDesignerDialog(chip_database=library)
    qtbot.addWidget(blank)
    assert not blank.repair_btn.isEnabled()

    dialog = ChipDefinitionDesignerDialog(chip_database=library, initial_chip="C")
    qtbot.addWidget(dialog)
    assert dialog.repair_btn.isEnabled()
    dialog.clone_combo.setCurrentIndex(dialog.clone_combo.findData("C"))
    dialog._on_clone_clicked()
    assert not dialog.repair_btn.isEnabled()


def test_designer_asks_before_dropping_unsaved_edits_then_reloads(monkeypatch, qtbot, library, messages, opened):
    from autosar_configurator.ui.dialogs import chip_definition_designer_dialog as designer

    dialog = designer.ChipDefinitionDesignerDialog(chip_database=library, initial_chip="C")
    qtbot.addWidget(dialog)
    saved = []
    dialog.chip_saved.connect(saved.append)

    dialog._on_repair_clicked()                 # nothing edited: no question
    assert len(opened["wizards"]) == 1

    dialog.desc_edit.setPlainText("edited")
    answers = []
    monkeypatch.setattr(designer.QMessageBox, "question",
                        lambda *a, **k: answers.append(a[2]) or designer.QMessageBox.No)
    dialog._on_repair_clicked()
    assert answers and len(opened["wizards"]) == 1          # declined: no wizard

    monkeypatch.setattr(designer.QMessageBox, "question", lambda *a, **k: designer.QMessageBox.Yes)
    opened["repair"] = True
    dialog._on_repair_clicked()
    assert saved == ["C"]
    assert dialog._resource_version == "1.0.1"
    assert dialog.desc_edit.toPlainText() == ""              # reloaded from the library
    assert not dialog._has_unsaved_edits()


def test_project_properties_repair_button(monkeypatch, qtbot, tmp_path, library, messages, opened):
    from autosar_configurator.ui.dialogs import project_properties_dialog as props

    notices = []
    monkeypatch.setattr(props.QMessageBox, "information", lambda *a, **k: notices.append(a[2]))
    project = _project(tmp_path, library, chip=None)
    dialog = props.ProjectPropertiesDialog(project, None)
    qtbot.addWidget(dialog)
    dialog.chip_combo.setCurrentIndex(dialog.chip_combo.findData("D"))
    assert dialog.repair_chip_btn.isHidden()                  # complete chip
    dialog.chip_combo.setCurrentIndex(dialog.chip_combo.findData("C"))
    assert dialog.chip_combo.currentText() == "C（资料不完整）"
    assert not dialog.repair_chip_btn.isHidden()

    opened["repair"] = True
    dialog.repair_chip_btn.click()
    assert opened["wizards"][-1].initial_chip == "C"
    assert dialog.chip_combo.currentData() == "C"
    assert dialog.chip_combo.currentText() == "C"            # no longer incomplete
    assert dialog.repair_chip_btn.isHidden()
    assert notices == []                                      # the project has no copy of C


# --- entries in the new-project and hardware-mapping wizards -------------------------

def test_new_project_wizard_repair_button(qtbot, library, messages, opened):
    from PySide6.QtCore import Qt
    from autosar_configurator.ui.wizards.new_project_wizard import ChipSelectionPage

    page = ChipSelectionPage(library)
    qtbot.addWidget(page)
    assert not page.repair_btn.isEnabled()                      # nothing selected
    page.chip_list.setCurrentRow(next(r for r in range(page.chip_list.count())
                                      if page.chip_list.item(r).data(Qt.UserRole) == "C"))
    assert page.repair_btn.isEnabled()

    opened["repair"] = True
    page.repair_btn.click()
    assert opened["wizards"][-1].initial_chip == "C"
    assert page.chip_list.currentItem().data(Qt.UserRole) == "C"      # still selected after the repair
    assert "ports" not in (library.get_chip("C").metadata.get("unconfirmed") or {})


def test_hardware_mapping_wizard_repair_button(qtbot, tmp_path, library, messages, opened):
    from autosar_configurator.ui.wizards.hardware_mapping_wizard import ChipSelectionPage

    project = _project(tmp_path, library, chip="C")
    page = ChipSelectionPage(library, None, project)
    qtbot.addWidget(page)
    assert page.chip_combo.currentData() == "C" and page.repair_btn.isEnabled()

    opened["repair"] = True
    page.repair_btn.click()
    wizard = opened["wizards"][-1]
    assert wizard.initial_chip == "C" and wizard.project is project
    assert page.chip_combo.currentData() == "C"
    assert library.get_chip("C").resource_version != "1.0.0"
