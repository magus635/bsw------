"""Unit tests for ProjectController (P2-6 phase 8).

Exercise the recent-files list management with a stub window (settings + menu
update patched). The bulk of ProjectController is dialog-driven Qt I/O; these
tests cover the pure list logic. The full window construction path is covered
by test_davinci_integration.
"""
from unittest.mock import MagicMock, patch

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
    (tmp_path / "EbSource" / "EbSource.dpa").write_text("{}", encoding="utf-8")
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
