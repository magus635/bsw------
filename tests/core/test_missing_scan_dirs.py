"""Scanning a directory that does not exist (or is a file) fails clearly or is skipped
with a message; it never yields an empty result that looks like success, and never
crashes with NotADirectoryError."""
import argparse
import logging
import shutil
import sys

import pytest

from autosar_configurator.core.config_manager import EpcFileScanner
from autosar_configurator.core.hardware.ecu_resource_diagnostics import collect_referenced_keys_in_dirs
from autosar_configurator.core.workspace_manager import WorkspaceManager
from tests.core.test_eb_import_modes import DIO_DEF_SAMPLE, DIO_EPC
from tools.arti import build_kernel_matrix
from tools.chip_repair import main as chip_repair_main
from tools.diff.analyzer import DiffAnalyzer
from tools.run import cmd_diff


@pytest.fixture
def existing(tmp_path):
    d = tmp_path / "existing"
    d.mkdir()
    (d / "a.c").write_text("int a;\n", encoding="utf-8")
    return d


# --- tools/diff + tools/run.py ------------------------------------------------------

@pytest.mark.parametrize("missing_side", ["reference", "generated"])
def test_diff_analyzer_rejects_missing_directory(existing, tmp_path, missing_side):
    missing = tmp_path / "missing"
    ref, gen = (missing, existing) if missing_side == "reference" else (existing, missing)
    with pytest.raises(FileNotFoundError, match=f"{missing_side} directory not found"):
        DiffAnalyzer("Os", str(ref), str(gen)).analyze()


def test_diff_analyzer_with_existing_directories_still_works(existing):
    report = DiffAnalyzer("Os", str(existing), str(existing)).analyze()
    assert report.is_clean and len(report.files) == 1


def test_run_diff_returns_error_for_missing_directory(existing, tmp_path, capsys):
    args = argparse.Namespace(module="Os", ref=str(tmp_path / "missing"), gen=str(existing),
                              json=False, output=None)
    assert cmd_diff(args) == 2
    assert "Reference directory not found" in capsys.readouterr().err


# --- tools/arti/build_kernel_matrix.py ----------------------------------------------

@pytest.mark.parametrize("option", ["--project", "--kernel", "--sdk", "--memmap",
                                    "--reference-kernel", "--vendor-dir"])
def test_kernel_matrix_rejects_missing_directory(existing, tmp_path, monkeypatch, capsys, option):
    argv = {"--project": str(existing), "--kernel": str(existing)}
    argv[option] = str(tmp_path / "missing")
    monkeypatch.setattr(sys, "argv", ["build_kernel_matrix.py",
                                      *[x for kv in argv.items() for x in kv]])
    # nothing must run (generation, compiling, deleting --work) before the check
    monkeypatch.setattr(build_kernel_matrix.shutil, "rmtree",
                        lambda *a, **k: pytest.fail("work directory touched"))
    with pytest.raises(SystemExit) as exc:
        build_kernel_matrix.main()
    assert exc.value.code == 2
    assert f"{option} directory not found" in capsys.readouterr().err


# --- tools/chip_repair.py + ecu_resource_diagnostics --------------------------------

def test_chip_repair_cli_rejects_missing_scan_dir(tmp_path, capsys):
    with pytest.raises(SystemExit) as exc:
        chip_repair_main(["diff", "ANY", "--scan-dir", str(tmp_path / "missing")])
    assert exc.value.code == 2
    assert "--scan-dir directory not found" in capsys.readouterr().err


def test_missing_plugin_dir_is_skipped_with_warning(existing, tmp_path, caplog):
    missing = tmp_path / "missing"
    with caplog.at_level(logging.WARNING):
        assert collect_referenced_keys_in_dirs([missing, existing]) == {}
    assert any(str(missing) in r.getMessage() for r in caplog.records)


# --- a file where a directory is expected -------------------------------------------

def test_config_file_instead_of_directory_does_not_crash(tmp_path):
    (tmp_path / "Config").write_text("not a directory", encoding="utf-8")
    assert EpcFileScanner.detect_available_chips(tmp_path) == []
    assert EpcFileScanner.find_epc_files(tmp_path) == {}


def test_eb_import_falls_back_when_plugin_path_is_a_file(tmp_path):
    src = tmp_path / "EbSource"
    (src / "Define" / "EbPlugins").mkdir(parents=True)
    (src / "Define" / "EbPlugins" / "eclipse").write_text("not a directory", encoding="utf-8")
    plugin = src / "Def" / "plugins" / "Dio_TS_T40D11M7I0R0"
    (plugin / "autosar").mkdir(parents=True)
    shutil.copy(DIO_DEF_SAMPLE, plugin / "autosar" / "Dio_THA6206_LFBGA292.arxml")
    output = src / "Config" / "THA6206" / "output"
    output.mkdir(parents=True)
    (output / "Dio.epc").write_text(DIO_EPC, encoding="utf-8")
    target = tmp_path / "Imported"
    target.mkdir()

    _, loaded, failed = WorkspaceManager().import_eb_project(src, target_dir=target)
    assert "Dio" in loaded, f"failed: {failed}"


def test_new_project_rejects_file_as_folder(tmp_path, monkeypatch):
    from unittest.mock import MagicMock, patch

    from autosar_configurator.core.config_manager import ProjectType
    from autosar_configurator.ui.controllers import project_controller
    from autosar_configurator.ui.controllers.project_controller import ProjectController

    folder = tmp_path / "proj"
    folder.write_text("not a directory", encoding="utf-8")
    win = MagicMock()
    win.chip_constraint_service = None
    warnings = []
    monkeypatch.setattr(project_controller.QMessageBox, "warning",
                        lambda *a, **k: warnings.append(a))

    with patch("autosar_configurator.ui.wizards.new_project_wizard.NewProjectWizard") as wiz_cls:
        wiz_cls.Accepted = 1
        wizard = wiz_cls.return_value
        wizard.exec.return_value = 1
        wizard.get_result.return_value = {
            "project_name": "demo", "project_type": ProjectType.VECTOR,
            "folder_path": folder, "selected_chip": None,
        }
        ProjectController(win).new_project()

    assert warnings and "not a folder" in warnings[0][2]
    win.workspace_manager.create_project.assert_not_called()
