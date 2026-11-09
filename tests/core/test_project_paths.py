"""Project directory resolution (ProjectDirectories / project_paths)."""
from pathlib import Path

import pytest

from autosar_configurator.core import project_paths
from autosar_configurator.core.project_paths import (
    ProjectDirectories,
    config_file,
    dirs,
    gen_dir,
    project_root,
    resolve,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject


def _project(tmp_path: Path, directories=None) -> WorkspaceProject:
    project = WorkspaceProject("P", tmp_path / "P.dpa")
    project.directories = directories
    return project


def test_legacy_dirs_match_old_names(tmp_path):
    p = _project(tmp_path)
    assert p.directories is None
    assert dirs(p) == ProjectDirectories.legacy()
    assert config_file(p, "Mcu") == tmp_path / "ConfigValue" / "Mcu_Config.arxml"
    assert gen_dir(p, "Mcu") == tmp_path / "generateCode" / "Mcu"
    assert resolve(p, "templates") == tmp_path / "templates"
    assert resolve(p, "legacy_plugins") == tmp_path / "Def" / "plugins"


def test_v8_dirs_flat_gen(tmp_path):
    p = _project(tmp_path, ProjectDirectories.default_v8())
    assert gen_dir(p, "Mcu") == tmp_path / "gen"
    assert config_file(p, "Mcu") == tmp_path / "config" / "Mcu.arxml"
    assert resolve(p, "base") == tmp_path / "config" / "base"
    assert resolve(p, "history") == tmp_path / ".history"


def test_default_v8_values():
    d = ProjectDirectories.default_v8()
    assert d.to_dict() == {
        "config": "config", "base": "config/base", "templates": "templates", "gen": "gen",
        "gen_layout": "flat", "chips": "chips", "integration": "integration",
        "system": "system", "history": ".history", "modules": "modules",
    }


def test_from_dict_fills_missing_and_normalises():
    d = ProjectDirectories.from_dict(
        {"config": "cfg\\values", "gen": 5, "unknown": "x"}, ProjectDirectories.default_v8())
    assert d.config == "cfg/values"
    assert d.gen == "gen"          # non-string falls back
    assert d.templates == "templates"
    assert ProjectDirectories.from_dict(None, ProjectDirectories.legacy()) == ProjectDirectories.legacy()


def test_project_root_handles_dpa_and_directory(tmp_path):
    assert project_root(_project(tmp_path)) == tmp_path
    eb = WorkspaceProject("EB", tmp_path)
    assert project_root(eb) == tmp_path


def test_resolve_rejects_unknown_key(tmp_path):
    with pytest.raises(KeyError):
        resolve(_project(tmp_path), "gen_layout")
    with pytest.raises(KeyError):
        resolve(_project(tmp_path), "nope")


def test_legacy_plugins_dir_for_path_only_callers(tmp_path):
    assert project_paths.legacy_plugins_dir(tmp_path) == tmp_path / "Def" / "plugins"


def _write_props(path: Path, text: str):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def test_generator_uses_given_project_root(tmp_path):
    from autosar_configurator.generator.generator import CodeGenerator

    outer = tmp_path / "outer"
    proj = outer / "proj"
    templates = proj / "templates"
    templates.mkdir(parents=True)
    _write_props(outer / "Def" / "plugins" / "X" / "resource" / "outer.properties", "Outer.Key=1\n")
    _write_props(proj / "Def" / "plugins" / "Y" / "resource" / "inner.properties", "Inner.Key=2\n")

    gen = CodeGenerator(None, None, project_template_dir=templates, project_root=proj)
    assert "Inner.Key" in gen.ecu_resources
    assert "Outer.Key" not in gen.ecu_resources

    # Without Def/ under proj/, the old upward search (project_root=None) climbs to outer/;
    # a given project_root never does.
    (proj / "Def").rename(proj / "Def_moved")
    gen = CodeGenerator(None, None, project_template_dir=templates, project_root=proj)
    assert "Outer.Key" not in gen.ecu_resources
    legacy = CodeGenerator(None, None, project_template_dir=templates)
    assert "Outer.Key" in legacy.ecu_resources


def test_project_paths_does_not_import_pyside6():
    import subprocess
    import sys

    code = ("import sys, autosar_configurator.core.project_paths; "
            "print('PySide6' in sys.modules)")
    out = subprocess.run([sys.executable, "-c", code], capture_output=True, text=True,
                         cwd=Path(__file__).resolve().parents[2], check=True)
    assert out.stdout.strip() == "False"
