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
