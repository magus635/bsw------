"""Unit tests for ProjectController (P2-6 phase 8).

Exercise the recent-files list management with a stub window (settings + menu
update patched). The bulk of ProjectController is dialog-driven Qt I/O; these
tests cover the pure list logic. The full window construction path is covered
by test_davinci_integration.
"""
from unittest.mock import MagicMock, patch

import pytest

from autosar_configurator.ui.controllers.project_controller import ProjectController


def _controller_with_recent(initial):
    win = MagicMock()
    win.max_recent_files = 3
    store = {"recent_files": list(initial)}
    win.settings.value.side_effect = lambda key, default=None: store.get(key, default)
    win.settings.setValue.side_effect = lambda key, val: store.__setitem__(key, val)
    ctrl = ProjectController(win)
    return ctrl, win, store


def test_add_to_recent_files_inserts_at_front():
    ctrl, win, store = _controller_with_recent(["b", "c"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._add_to_recent_files("a")
    assert store["recent_files"] == ["a", "b", "c"]


def test_add_to_recent_files_moves_existing_to_front():
    ctrl, win, store = _controller_with_recent(["b", "a", "c"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._add_to_recent_files("a")
    assert store["recent_files"] == ["a", "b", "c"]


def test_add_to_recent_files_respects_max():
    ctrl, win, store = _controller_with_recent(["b", "c", "d"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._add_to_recent_files("a")
    assert store["recent_files"] == ["a", "b", "c"]  # capped at max_recent_files=3


def test_remove_from_recent_files():
    ctrl, win, store = _controller_with_recent(["a", "b", "c"])
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._remove_from_recent_files("b")
    assert store["recent_files"] == ["a", "c"]


def test_remove_missing_is_noop():
    ctrl, win, store = _controller_with_recent(["a", "b"])
    with patch.object(ctrl, "_update_recent_files_menu") as upd:
        ctrl._remove_from_recent_files("zzz")
    assert store["recent_files"] == ["a", "b"]
    upd.assert_not_called()


def test_import_eb_project_asks_before_pre_changes_imported_values(tmp_path, monkeypatch):
    """The EB import passes a confirm: Pre changes EPC values only behind the dialog."""
    from PySide6.QtWidgets import QApplication

    from autosar_configurator.ui.controllers import project_controller

    source, parent = tmp_path / "EbSource", tmp_path / "out"
    source.mkdir()
    parent.mkdir()
    folders = iter([str(source), str(parent)])
    monkeypatch.setattr(project_controller.QFileDialog, "getExistingDirectory",
                        lambda *a, **k: next(folders))
    monkeypatch.setattr(project_controller.QInputDialog, "getItem",
                        lambda parent, title, label, items, *a: (items[1], True))   # link
    shown = []
    monkeypatch.setattr(project_controller.QMessageBox, "information",
                        lambda *a: shown.append(a[2]))
    for name in ("setOverrideCursor", "restoreOverrideCursor", "processEvents"):
        monkeypatch.setattr(QApplication, name, staticmethod(lambda *a: None))

    win = MagicMock()
    win.workspace_manager.import_eb_project.return_value = (MagicMock(), ["Mcu"], [])
    win.workspace_manager.last_import_report = tmp_path / "out" / "r_import.md"
    ctrl = ProjectController(win)
    with patch.object(ctrl, "apply_project_chip"), \
            patch.object(ctrl, "selector_mismatches", return_value=[]), \
            patch.object(ctrl, "_ecu_resource_status", return_value=""), \
            patch.object(ctrl, "_update_recent_files_menu"):
        ctrl.import_eb_project()

    kwargs = win.workspace_manager.import_eb_project.call_args.kwargs
    assert kwargs["mode"] == "link"
    assert kwargs["confirm"] == ctrl._confirm_import_merge
    assert "r_import.md" in shown[0]


def _run_import(tmp_path, monkeypatch, chosen):
    """Run the Import EB menu action with ``chosen`` as the destination folder."""
    from PySide6.QtWidgets import QApplication

    from autosar_configurator.ui.controllers import project_controller

    source = tmp_path / "EbSource"
    source.mkdir(exist_ok=True)
    folders = iter([str(source), str(chosen)])
    monkeypatch.setattr(project_controller.QFileDialog, "getExistingDirectory",
                        lambda *a, **k: next(folders))
    monkeypatch.setattr(project_controller.QInputDialog, "getItem",
                        lambda parent, title, label, items, *a: (items[0], True))
    warnings = []
    monkeypatch.setattr(project_controller.QMessageBox, "warning", lambda *a: warnings.append(a[2]))
    monkeypatch.setattr(project_controller.QMessageBox, "information", lambda *a: None)
    for name in ("setOverrideCursor", "restoreOverrideCursor", "processEvents"):
        monkeypatch.setattr(QApplication, name, staticmethod(lambda *a: None))
    win = MagicMock()
    win.workspace_manager.import_eb_project.return_value = (MagicMock(), [], [])
    ctrl = ProjectController(win)
    with patch.object(ctrl, "apply_project_chip"), \
            patch.object(ctrl, "selector_mismatches", return_value=[]), \
            patch.object(ctrl, "_ecu_resource_status", return_value=""), \
            patch.object(ctrl, "_update_recent_files_menu"):
        ctrl.import_eb_project()
    return source, win, warnings


def test_import_eb_project_never_targets_the_eb_tree(tmp_path, monkeypatch):
    source, win, warnings = _run_import(tmp_path, monkeypatch, tmp_path / "EbSource")
    win.workspace_manager.import_eb_project.assert_not_called()
    assert warnings and "EB" in warnings[0]


def test_import_eb_project_refuses_an_existing_project_as_source(tmp_path, monkeypatch):
    (tmp_path / "EbSource").mkdir()
    (tmp_path / "EbSource" / "EbSource.dpa").write_text(
        '{"format_version": 8, "name": "EbSource", "modules": []}', encoding="utf-8")
    source, win, warnings = _run_import(tmp_path, monkeypatch, tmp_path)
    win.workspace_manager.import_eb_project.assert_not_called()
    assert warnings and "EbSource.dpa" in warnings[0]
    assert sorted(p.name for p in tmp_path.iterdir()) == ["EbSource"]


def test_import_eb_project_next_to_the_eb_tree_gets_a_sibling(tmp_path, monkeypatch):
    source, win, warnings = _run_import(tmp_path, monkeypatch, tmp_path)
    assert warnings == []
    kwargs = win.workspace_manager.import_eb_project.call_args.kwargs
    assert kwargs["target_dir"] == tmp_path / "EbSource_imported"


def test_save_as_relocates_a_project_living_in_the_eb_tree(tmp_path, monkeypatch):
    from types import SimpleNamespace

    from autosar_configurator.ui.controllers import project_controller

    eb_root = tmp_path / "Eb"
    project = SimpleNamespace(eb_source_root=eb_root, path=eb_root / "P.dpa", name="P",
                              module_managers={})
    monkeypatch.setattr(project_controller.QFileDialog, "getExistingDirectory",
                        lambda *a, **k: str(tmp_path / "Out"))
    win = MagicMock()
    win.current_project = project
    ctrl = ProjectController(win)
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl.save_project()

    win.workspace_manager.relocate_project.assert_called_once_with(tmp_path / "Out" / "P.dpa")
    win.workspace_manager.save_project.assert_called_once()
    assert win.current_project_file == tmp_path / "Out" / "P.dpa"


def test_save_as_points_recent_files_and_last_project_at_the_new_dpa(tmp_path, monkeypatch):
    from types import SimpleNamespace

    from autosar_configurator.ui.controllers import project_controller

    eb_root = tmp_path / "Eb"
    old, new = eb_root / "P.dpa", tmp_path / "Out" / "P.dpa"
    project = SimpleNamespace(eb_source_root=eb_root, path=old, name="P", module_managers={})
    monkeypatch.setattr(project_controller.QFileDialog, "getExistingDirectory",
                        lambda *a, **k: str(tmp_path / "Out"))
    ctrl, win, store = _controller_with_recent([str(old), "other.dpa"])
    store["last_project_path"] = str(old)
    win.current_project = project
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl.save_project()

    assert store["recent_files"] == [str(new), "other.dpa"]
    assert store["last_project_path"] == str(new)


def test_save_as_that_fails_leaves_recent_files_alone(tmp_path, monkeypatch):
    from types import SimpleNamespace

    from autosar_configurator.ui.controllers import project_controller

    eb_root = tmp_path / "Eb"
    old = eb_root / "P.dpa"
    project = SimpleNamespace(eb_source_root=eb_root, path=old, name="P", module_managers={})
    monkeypatch.setattr(project_controller.QFileDialog, "getExistingDirectory",
                        lambda *a, **k: str(tmp_path / "Out"))
    monkeypatch.setattr(project_controller.QMessageBox, "critical", lambda *a: None)
    ctrl, win, store = _controller_with_recent([str(old)])
    store["last_project_path"] = str(old)
    win.current_project = project
    win.workspace_manager.relocate_project.side_effect = OSError("disk full")
    with patch.object(ctrl, "_update_recent_files_menu"):
        ctrl.save_project()

    assert store["recent_files"] == [str(old)]
    assert store["last_project_path"] == str(old)


def test_open_folder_of_an_imported_project_opens_it(tmp_path, monkeypatch):
    """N1: a folder holding a .dpa is a project, even one typed EB Tresos — never re-imported."""
    import json

    from autosar_configurator.core.workspace_manager import WorkspaceManager
    from autosar_configurator.ui.controllers import project_controller
    from tests.core.test_eb_import_modes import DIO_EPC, write_dio_plugin

    src = tmp_path / "EbSource"
    write_dio_plugin(src / "Define" / "EbPlugins" / "eclipse" / "Dio_TS")
    (src / "Config" / "C1" / "output").mkdir(parents=True)
    (src / "Config" / "C1" / "output" / "Dio.epc").write_text(DIO_EPC, encoding="utf-8")
    project, _, _ = WorkspaceManager().import_eb_project(src, target_dir=tmp_path / "Imported")
    folder = project.path.parent
    assert json.loads(project.path.read_text(encoding="utf-8"))["project_type"] == "EB Tresos"

    monkeypatch.setattr(project_controller.QMessageBox, "information", lambda *a: None)
    monkeypatch.setattr(project_controller.QMessageBox, "warning", lambda *a: None)
    monkeypatch.setattr(project_controller.QMessageBox, "critical",
                        lambda *a: (_ for _ in ()).throw(AssertionError(a[2])))
    monkeypatch.setattr(project_controller.QFileDialog, "getExistingDirectory",
                        lambda *a, **k: (_ for _ in ()).throw(AssertionError("asked for a target")))
    win = MagicMock()
    win.workspace_manager = WorkspaceManager()
    ctrl = ProjectController(win)
    with patch.object(ctrl, "apply_project_chip"), \
            patch.object(ctrl, "_ecu_resource_status", return_value=""), \
            patch.object(ctrl, "_selector_status", return_value=""), \
            patch.object(ctrl, "_update_recent_files_menu"):
        ctrl._load_project_at_path(folder)

    assert win.current_project_file == project.path
    assert "Dio" in win.current_project.module_managers
    assert sorted(p.name for p in tmp_path.iterdir()) == ["EbSource", "Imported"]


# --- round 3: a folder is a project only by a .dpa of this tool ------------------------------

_DAVINCI_XML_DPA = """<?xml version="1.0" encoding="UTF-8"?>
<DaVinciProject><Folders><ECUC>Config/ECUC</ECUC></Folders></DaVinciProject>
"""


def _eb_tree(root):
    """A small EB tree (one Dio plugin, one EPC) at ``root``."""
    from tests.core.test_eb_import_modes import DIO_EPC, write_dio_plugin

    write_dio_plugin(root / "Define" / "EbPlugins" / "eclipse" / "Dio_TS")
    (root / "Config" / "C1" / "output").mkdir(parents=True)
    (root / "Config" / "C1" / "output" / "Dio.epc").write_text(DIO_EPC, encoding="utf-8")
    return root


def _tool_dpa(path, **extra):
    import json

    data = {"format_version": 7, "name": path.stem, "project_type": "EB Tresos", "modules": []}
    data.update(extra)
    path.write_text(json.dumps(data), encoding="utf-8")
    return path


class _Ui:
    """Patched dialogs of one controller run; records what was shown and asked."""

    def __init__(self, monkeypatch, folders, choice=None, items_choice=None):
        from PySide6.QtWidgets import QApplication

        from autosar_configurator.ui.controllers import project_controller as pc

        self.warnings, self.questions, self.item_lists = [], [], []
        self.choice, self.items_choice = choice, items_choice
        it = iter(folders)
        monkeypatch.setattr(pc.QFileDialog, "getExistingDirectory", lambda *a, **k: str(next(it)))
        monkeypatch.setattr(pc.QMessageBox, "warning", lambda *a: self.warnings.append(a[2]))
        monkeypatch.setattr(pc.QMessageBox, "information", lambda *a: None)
        monkeypatch.setattr(pc.QMessageBox, "critical",
                            lambda *a: (_ for _ in ()).throw(AssertionError(a[2])))
        monkeypatch.setattr(pc.QInputDialog, "getItem", self._get_item)
        for name in ("setOverrideCursor", "restoreOverrideCursor", "processEvents"):
            monkeypatch.setattr(QApplication, name, staticmethod(lambda *a: None))
        monkeypatch.setattr(pc.ProjectController, "_ask_open_or_import",
                            lambda ctrl, folder, project_file: self._ask(folder, project_file))

    def _get_item(self, parent, title, label, items, *a):
        items = list(items)
        self.item_lists.append((title, items))
        if title == "Import Mode":
            return items[0], True                                   # copy
        if self.items_choice is not None:
            return self.items_choice(items)
        return items[0], True

    def _ask(self, folder, project_file):
        self.questions.append((folder, project_file))
        return self.choice


def _controller(win_manager=None):
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    win = MagicMock()
    win.workspace_manager = win_manager or WorkspaceManager()
    ctrl = ProjectController(win)
    patches = [patch.object(ctrl, "apply_project_chip"),
               patch.object(ctrl, "selector_mismatches", return_value=[]),
               patch.object(ctrl, "_ecu_resource_status", return_value=""),
               patch.object(ctrl, "_selector_status", return_value=""),
               patch.object(ctrl, "_update_recent_files_menu")]
    return win, ctrl, patches


def _run(ctrl, patches, action):
    from contextlib import ExitStack

    with ExitStack() as stack:
        for p in patches:
            stack.enter_context(p)
        action()


@pytest.mark.parametrize("entry", ["open_folder", "import_menu"])
@pytest.mark.parametrize("dpa_kind", ["davinci_xml", "corrupt"])
def test_a_dpa_that_is_not_ours_does_not_stop_the_import(tmp_path, monkeypatch, entry, dpa_kind):
    """(i) DaVinci XML .dpa and (iv) corrupt .dpa beside EB plugins: the import proceeds."""
    src = _eb_tree(tmp_path / "EbSource")
    content = _DAVINCI_XML_DPA if dpa_kind == "davinci_xml" else "{ broken"
    (src / "EbSource.dpa").write_text(content, encoding="utf-8")
    out = tmp_path / "Out"
    out.mkdir()
    folders = [out] if entry == "open_folder" else [src, out]
    ui = _Ui(monkeypatch, folders)
    win, ctrl, patches = _controller()
    _run(ctrl, patches, (lambda: ctrl._load_project_at_path(src)) if entry == "open_folder"
         else ctrl.import_eb_project)

    assert ui.warnings == [] and ui.questions == []
    project = win.current_project
    assert project.path == out / "EbSource" / "EbSource.dpa"
    assert "Dio" in project.module_managers
    assert (src / "EbSource.dpa").read_text(encoding="utf-8") == content       # left as it was


@pytest.mark.parametrize("entry", ["open_folder", "import_menu"])
@pytest.mark.parametrize("answer", ["open", "import", None])
def test_a_folder_that_is_both_asks(tmp_path, monkeypatch, entry, answer):
    """(ii) A pre-fix <root>/<root>.dpa (valid JSON) inside an EB tree: the user decides."""
    src = _eb_tree(tmp_path / "EbSource")
    old = _tool_dpa(src / "EbSource.dpa")
    before = old.read_bytes()
    out = tmp_path / "Out"
    out.mkdir()
    folders = [out] if entry == "open_folder" else [src, out]
    ui = _Ui(monkeypatch, folders, choice=answer)
    win, ctrl, patches = _controller()
    _run(ctrl, patches, (lambda: ctrl._load_project_at_path(src)) if entry == "open_folder"
         else ctrl.import_eb_project)

    assert ui.questions == [(src, old)]
    assert ui.warnings == []
    imported = out / "EbSource" / "EbSource.dpa"
    if answer == "open":
        assert win.current_project_file == old
        assert win.current_project.path == old
        assert not imported.exists()
    elif answer == "import":
        assert imported.is_file()
        assert win.current_project.path == imported
        assert "Dio" in win.current_project.module_managers
    else:                                                          # cancelled: nothing happens
        assert not imported.exists()
        assert win.workspace_manager.current_project is None
    assert old.read_bytes() == before                                # never rewritten


def test_open_folder_with_only_a_project_file_opens_it(tmp_path, monkeypatch):
    """(iii) A valid tool .dpa and no EB content: opened, nothing asked, nothing imported."""
    folder = tmp_path / "Proj"
    folder.mkdir()
    dpa = _tool_dpa(folder / "Proj.dpa", project_type="Vector DaVinci")
    ui = _Ui(monkeypatch, [])
    win, ctrl, patches = _controller()
    _run(ctrl, patches, lambda: ctrl._load_project_at_path(folder))
    assert ui.questions == [] and ui.warnings == []
    assert win.current_project_file == dpa
    assert sorted(p.name for p in tmp_path.iterdir()) == ["Proj"]


@pytest.mark.parametrize("marker", [None, ".project"])
def test_open_folder_with_only_a_dpa_that_is_not_ours(tmp_path, monkeypatch, marker):
    """A DaVinci XML .dpa and no EB content: the .dpa does not make the folder anything.
    Without an EB marker it is said to be unknown (nothing opened, nothing imported); with
    one it is an EB tree as before."""
    folder = tmp_path / "DaVinci"
    folder.mkdir()
    (folder / "DaVinci.dpa").write_text(_DAVINCI_XML_DPA, encoding="utf-8")
    if marker:
        (folder / marker).write_text("<projectDescription/>", encoding="utf-8")
    ui = _Ui(monkeypatch, [tmp_path / "Out"])
    win, ctrl, patches = _controller(MagicMock())
    win.workspace_manager.import_eb_project.return_value = (MagicMock(module_managers={}), [], [])
    _run(ctrl, patches, lambda: ctrl._load_project_at_path(folder))

    assert ui.questions == []
    win.workspace_manager.load_project.assert_not_called()
    if marker:
        assert ui.warnings == []
        win.workspace_manager.import_eb_project.assert_called_once()
    else:
        assert len(ui.warnings) == 1 and str(folder) in ui.warnings[0]
        win.workspace_manager.import_eb_project.assert_not_called()
        assert sorted(p.name for p in tmp_path.iterdir()) == ["DaVinci"]
    assert (folder / "DaVinci.dpa").read_text(encoding="utf-8") == _DAVINCI_XML_DPA


def test_import_menu_on_a_project_only_folder_refuses(tmp_path, monkeypatch):
    """A valid tool .dpa and no EB content: not an EB tree — the menu says to open it."""
    folder = tmp_path / "Proj"
    folder.mkdir()
    dpa = _tool_dpa(folder / "Proj.dpa")
    ui = _Ui(monkeypatch, [folder])
    win, ctrl, patches = _controller()
    with patch.object(win.workspace_manager, "import_eb_project") as imp:
        _run(ctrl, patches, ctrl.import_eb_project)
    imp.assert_not_called()
    assert ui.questions == []
    assert len(ui.warnings) == 1 and str(dpa) in ui.warnings[0]


@pytest.mark.parametrize("picked", [0, 1, None])
def test_several_project_files_ask_which_one(tmp_path, monkeypatch, picked):
    folder = tmp_path / "Proj"
    folder.mkdir()
    lower_b = _tool_dpa(folder / "b.dpa")
    upper_a = _tool_dpa(folder / "A.dpa")
    (folder / "z.dpa").write_text(_DAVINCI_XML_DPA, encoding="utf-8")       # not ours: not offered
    choose = (lambda items: (items[picked], True)) if picked is not None else (lambda items: ("", False))
    ui = _Ui(monkeypatch, [], items_choice=choose)
    win, ctrl, patches = _controller(MagicMock())
    win.workspace_manager.load_project.return_value = (MagicMock(module_managers={}), [])
    _run(ctrl, patches, lambda: ctrl._load_project_at_path(folder))

    ((title, items),) = [t for t in ui.item_lists if t[0] != "Import Mode"]
    assert items == ["A.dpa", "b.dpa"]                                       # sorted, ours only
    if picked is None:
        win.workspace_manager.load_project.assert_not_called()
    else:
        loaded = win.workspace_manager.load_project.call_args.args[0]
        assert loaded == [upper_a, lower_b][picked]
