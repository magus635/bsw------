"""Template lookup: project overlay -> package (design §6.6, W6).

A format 8 project keeps ``templates/<Module>/`` as a user-editable overlay; the
module package's own template directory is the fallback.  Saving must not copy
the package into the overlay anymore.
"""
import json
import shutil
from pathlib import Path

import pytest

from autosar_configurator.core import project_paths
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.packages.types import ModuleManifest
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

REPO_ROOT = Path(__file__).resolve().parents[2]
DIO_DEF_SAMPLE = REPO_ROOT / "Dio_Definition_Test.arxml"

DIO_EPC = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Dio</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Dio</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Dio</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DioConfig</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_AS440_FuSa/Dio/DioConfig</DEFINITION-REF>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


def _write(path: Path, text: str) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    return path


def _config():
    """Minimal configuration whose module short name is 'Dio' (no parameters needed)."""
    from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
    return EcucModuleConfiguration(short_name="Dio", definition_ref="/THA6_AS440_FuSa/Dio")


def _module_def():
    from autosar_configurator.core.model.definition_model import EcucModuleDef
    return EcucModuleDef(short_name="Dio", definition_ref="/THA6_AS440_FuSa/Dio")


# --- CodeGenerator: overlay wins over package -----------------------------------

def test_overlay_wins_over_package(tmp_path):
    """Flat overlay vs a NESTED package (EB generate_PB/Dio/...): overlay wins outright.

    Source precedence must dominate the old ``rel_dir/type`` key: the package copy
    has rel_dir ``Dio`` and the overlay copy rel_dir ``.``, so keying both together
    would leave two entries and the type pass would pick the package.
    """
    overlay_root = tmp_path / "templates"
    _write(overlay_root / "Dio" / "Dio_Cfg.h", "/* overlay */\n")
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(package_dir / "Dio" / "Dio_Cfg.h", "/* package */\n")

    generator = CodeGenerator(_module_def(), _config(),
                              project_template_dir=overlay_root,
                              package_template_dir=package_dir)
    [entry] = [t for t in generator._discover_template_types("Dio") if t['type'] == "Cfg.h"]
    assert entry['original_path'] == str((overlay_root / "Dio" / "Dio_Cfg.h").resolve())

    assert generator.generate_all(tmp_path / "out") is True

    # Root-level overlay template: promoted into include/ (the package's nested
    # rel_dir would have placed it under out/Dio/Dio/)
    out = tmp_path / "out" / "Dio" / "include" / "Dio_Cfg.h"
    assert out.read_text(encoding="utf-8") == "/* overlay */\n"
    assert not (tmp_path / "out" / "Dio" / "Dio").exists()


def test_package_used_when_no_overlay(tmp_path):
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(package_dir / "Dio" / "Dio_Cfg.h", "/* package */\n")
    (tmp_path / "templates").mkdir()

    generator = CodeGenerator(_module_def(), _config(),
                              project_template_dir=tmp_path / "templates",
                              package_template_dir=package_dir)
    assert generator.generate_all(tmp_path / "out") is True

    out = tmp_path / "out" / "Dio" / "Dio" / "Dio_Cfg.h"
    assert out.read_text(encoding="utf-8") == "/* package */\n"


def test_package_only_module_still_scans_ecu_resources(tmp_path):
    """I2: no overlay dir at all — the package is still scanned, .properties too"""
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(package_dir / "Dio" / "Dio_Cfg.h", "/* package */\n")
    _write(package_dir / "params.properties", "DioBase=7\n")
    project_root = tmp_path / "Project"
    _write(project_root / "Def" / "chip.properties", "ChipName=THA6206\n")

    generator = CodeGenerator(_module_def(), _config(),
                              package_template_dir=package_dir,
                              project_root=project_root)
    assert generator.ecu_resources["ChipName"] == "THA6206"
    assert generator.generate_all(tmp_path / "out") is True


def test_package_dir_is_not_an_overlay_root(tmp_path):
    """``package_template_dir`` IS the module dir: no ``<Module>/`` subdir inside it"""
    package_dir = tmp_path / "generate_PB"
    _write(package_dir / "Dio_Cfg.h", "/* package */\n")
    _write(package_dir / "Dio" / "Nested_Cfg.h", "ignored\n")

    generator = CodeGenerator(_module_def(), _config(), package_template_dir=package_dir)
    types = sorted(t['type'] for t in generator._discover_template_types("Dio"))
    assert types == ["Cfg.h"]


# --- fingerprint independent of where the template lives ------------------------

def test_fingerprint_independent_of_template_location(tmp_path):
    content = "/* same content */\n"
    overlay_root = tmp_path / "overlay"
    _write(overlay_root / "Dio" / "Dio_Cfg.h", content)
    package_dir = tmp_path / "pkg" / "templates"
    _write(package_dir / "Dio_Cfg.h", content)

    from_overlay = CodeGenerator(_module_def(), _config(),
                                 project_template_dir=overlay_root)
    from_package = CodeGenerator(_module_def(), _config(),
                                 package_template_dir=package_dir)

    overlay_types = from_overlay._discover_template_types("Dio")
    package_types = from_package._discover_template_types("Dio")
    # Only the file location differs; the fingerprint input is the file content
    assert [(t['type'], t['rel_dir']) for t in overlay_types] == [
        (t['type'], t['rel_dir']) for t in package_types]
    assert from_overlay._calculate_fingerprint(
        template_types=overlay_types) == from_package._calculate_fingerprint(
        template_types=package_types)


# --- template_sources ----------------------------------------------------------

def _v8_project(tmp_path, **kwargs):
    manager = WorkspaceManager()
    project = manager.create_project("V8", tmp_path / "V8.dpa", format_version=8)
    for key, value in kwargs.items():
        setattr(project, key, value)
    return manager, project


def test_template_sources_v8_without_package(tmp_path):
    _, project = _v8_project(tmp_path)
    overlay_root, package_dir = project_paths.template_sources(project, "Dio")
    assert overlay_root == tmp_path / "templates"
    assert package_dir is None


def test_template_sources_v8_uses_package_dir(tmp_path):
    pkg_root = tmp_path / "modules" / "Dio"
    (pkg_root / "templates").mkdir(parents=True)
    pkg = ModulePackage(pkg_root, ModuleManifest(
        module="Dio", definition="/THA6_AS440_FuSa/Dio", templates="templates"))
    _, project = _v8_project(tmp_path, packages={"Dio": pkg})

    overlay_root, package_dir = project_paths.template_sources(project, "Dio")
    assert overlay_root == tmp_path / "templates"
    assert package_dir == pkg_root / "templates"


def test_template_sources_legacy_project(tmp_path):
    """Format <= 7: ``(<root>/templates, None)`` — identical to today"""
    manager = WorkspaceManager()
    project = manager.create_project("V7", tmp_path / "V7.dpa", format_version=7)
    overlay_root, package_dir = project_paths.template_sources(project, "Dio")
    assert overlay_root == tmp_path / "templates"
    assert package_dir is None


# --- saving never copies templates into the overlay ----------------------------

def _import_eb_project(eb_source_tree, tmp_path, mode, format_version):
    manager = WorkspaceManager()
    target = tmp_path / f"Imported_{mode}_v{format_version}"
    target.mkdir()
    project, loaded, failed = manager.import_eb_project(
        eb_source_tree, chip_name=None, target_dir=target, mode=mode)
    project.format_version = format_version
    if format_version >= 8:
        from autosar_configurator.core.project_paths import ProjectDirectories
        project.directories = ProjectDirectories.default_v8()
    return manager, project, target


@pytest.fixture
def eb_source_tree(tmp_path):
    src_root = tmp_path / "EbSource"
    plugin = src_root / "Define" / "EbPlugins" / "eclipse" / "Dio_TS_T40D11M7I0R0"
    (plugin / "autosar").mkdir(parents=True)
    shutil.copy(DIO_DEF_SAMPLE, plugin / "autosar" / "Dio_THA6206_LFBGA292.arxml")
    (plugin / "generate_PB" / "Dio").mkdir(parents=True)
    (plugin / "generate_PB" / "Dio" / "Dio_Cfg.h.tpl").write_text("/* tpl */", encoding="utf-8")

    output = src_root / "Config" / "THA6206" / "output"
    output.mkdir(parents=True)
    (output / "Dio.epc").write_text(DIO_EPC, encoding="utf-8")
    return src_root


def test_v8_save_does_not_copy_templates(eb_source_tree, tmp_path):
    """Acceptance 6: an edited overlay survives a save; no plugin copy appears"""
    manager, project, target = _import_eb_project(eb_source_tree, tmp_path, "copy", 8)

    edited = _write(target / "templates" / "Dio" / "Dio_Cfg.h", "/* user edit */\n")
    manager.save_project()

    assert edited.read_text(encoding="utf-8") == "/* user edit */\n"
    # Only the overlay file the user created; the plugin's generate_PB was not copied
    assert sorted(p.name for p in (target / "templates" / "Dio").iterdir()) == ["Dio_Cfg.h"]


def test_v7_save_still_copies_templates(eb_source_tree, tmp_path):
    """Legacy regression: format <= 7 keeps the byte-identical copy behaviour"""
    manager, project, target = _import_eb_project(eb_source_tree, tmp_path, "copy", 7)

    manager.save_project()

    copied = target / "templates" / "Dio" / "Dio" / "Dio_Cfg.h.tpl"
    assert copied.is_file()
    assert copied.read_text(encoding="utf-8") == "/* tpl */"


def test_v8_import_then_save_does_not_copy_templates(eb_source_tree, tmp_path):
    """M5: the real save path — a v8 project LOADED from disk, saved, copies nothing.

    ``import_eb_project`` still writes format 7 (it has no packages), so the v8
    project is loaded the way the UI loads one: from its ``.dpa``.  Dio fails to
    load (no library provides its definition) but its template overlay is still the
    user's, and the save must leave it alone.
    """
    manager, project, target = _import_eb_project(eb_source_tree, tmp_path, "copy", 8)
    overlay = _write(target / "templates" / "Dio" / "Dio_Cfg.h", "/* user edit */\n")
    manager.save_project()

    manager2 = WorkspaceManager()
    loaded, _failed = manager2.load_project(project.path)
    assert loaded.format_version == 8
    manager2.save_project()

    assert overlay.read_text(encoding="utf-8") == "/* user edit */\n"
    assert not (target / "templates" / "Dio" / "Dio").exists()
