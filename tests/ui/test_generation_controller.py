"""Unit tests for GenerationController (P2-6 phase 6).

Exercise the mode-dispatch and config-collection logic with a stub window —
QMessageBox patched, no QApplication required.
"""
from types import SimpleNamespace
from unittest.mock import MagicMock, patch

from autosar_configurator.ui.controllers.generation_controller import (
    GenerationController, _template_sources)


def test_generate_code_dispatches_to_project_mode():
    win = MagicMock()
    win.current_project = MagicMock()
    ctrl = GenerationController(win)

    with patch.object(ctrl, "_generate_project_code") as proj, \
         patch.object(ctrl, "_generate_single_module_code") as single:
        ctrl.generate_code()
        proj.assert_called_once()
        single.assert_not_called()


def test_generate_code_dispatches_to_single_module():
    win = MagicMock()
    win.current_project = None
    win.config_manager = MagicMock()
    ctrl = GenerationController(win)

    with patch.object(ctrl, "_generate_project_code") as proj, \
         patch.object(ctrl, "_generate_single_module_code") as single:
        ctrl.generate_code()
        single.assert_called_once()
        proj.assert_not_called()


def test_generate_code_warns_without_configuration():
    win = MagicMock()
    win.current_project = None
    win.config_manager = None
    ctrl = GenerationController(win)

    with patch(
        "autosar_configurator.ui.controllers.generation_controller.QMessageBox"
    ) as mb:
        ctrl.generate_code()
        mb.warning.assert_called_once()


def test_get_all_project_configurations_collects_modules():
    mdef, cfg = object(), object()
    mgr = MagicMock()
    mgr.module_def = mdef
    mgr.configuration = cfg
    win = MagicMock()
    win.current_project.module_managers = {"Can": mgr}
    ctrl = GenerationController(win)

    result = ctrl._get_all_project_configurations()
    assert result == {"Can": (mdef, cfg)}


def test_get_all_project_configurations_empty_without_project():
    win = MagicMock()
    win.current_project = None
    ctrl = GenerationController(win)
    assert ctrl._get_all_project_configurations() == {}


def test_template_sources_project_without_path_is_safe():
    """A falsy ``project.path`` must not reach ``Path(None)`` (batch gen crashed)."""
    from autosar_configurator.core.project_paths import ProjectDirectories
    project = SimpleNamespace(path=None, format_version=8,
                              directories=ProjectDirectories.default_v8(), packages={})
    win = SimpleNamespace(current_project=project, current_project_file=None)
    assert _template_sources(win, "Dio") == (None, None, None)


def test_template_sources_eb_directory_project_passes_overlay_and_root(tmp_path):
    """EB project: ``path`` is the project dir, overlay comes from the project dir"""
    from autosar_configurator.core.project_paths import ProjectDirectories
    (tmp_path / "templates" / "Dio").mkdir(parents=True)
    project = SimpleNamespace(path=tmp_path, format_version=7,
                              directories=ProjectDirectories.legacy(), packages={})
    win = SimpleNamespace(current_project=project, current_project_file=None)

    overlay, package_dir, project_root = _template_sources(win, "Dio")
    assert overlay == tmp_path / "templates"
    assert package_dir is None
    assert project_root == tmp_path
