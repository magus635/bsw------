"""Template lookup: project overlay -> package (design §6.6, W6).

A format 8 project keeps ``templates/<Module>/`` as a user-editable overlay; the
module package's own template directory is the fallback.  Saving must not copy
the package into the overlay anymore.
"""
import json
from pathlib import Path

import pytest

from autosar_configurator.core import project_paths
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.packages.types import ModuleManifest
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator
from tests.core.test_eb_import_modes import write_dio_plugin

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
    # ChipName comes from Def (scanned first); DioBase exists ONLY in the package
    # properties, so it proves the package source was not skipped.
    assert generator.ecu_resources["ChipName"] == "THA6206"
    assert str(generator.ecu_resources["DioBase"]) == "7"
    assert generator.generate_all(tmp_path / "out") is True


def test_overlay_properties_win_over_package(tmp_path):
    """One precedence with the templates: the overlay's .properties value wins"""
    overlay_root = tmp_path / "templates"
    _write(overlay_root / "Dio" / "Dio_Cfg.h", "/* overlay */\n")
    _write(overlay_root / "Dio" / "overlay.properties", "ChipName=FROM_OVERLAY\n")
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(package_dir / "Dio" / "Dio_Cfg.h", "/* package */\n")
    _write(package_dir / "package.properties", "ChipName=FROM_PACKAGE\nDioBase=7\n")

    generator = CodeGenerator(_module_def(), _config(),
                              project_template_dir=overlay_root,
                              package_template_dir=package_dir)
    assert generator.ecu_resources["ChipName"] == "FROM_OVERLAY"
    # The package file is still read for keys the overlay does not define
    assert str(generator.ecu_resources["DioBase"]) == "7"


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
    write_dio_plugin(src_root / "Define" / "EbPlugins" / "eclipse" / "Dio_TS_T40D11M7I0R0")

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

    The imported project is loaded the way the UI loads one: from its ``.dpa``, Dio
    through the ``modules`` library.  Its template overlay is the user's, and the
    save must leave it alone.
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


def test_overlay_template_includes_macro_from_package(tmp_path):
    """An overlay template in templates/<Module>/ can INCLUDE macro files from the package."""
    overlay_root = tmp_path / "templates"
    _write(
        overlay_root / "Dio" / "Dio_PBcfg.c",
        '[!INCLUDE "Dio.m"!]\n/* overlay macro=[!"$MacroVal"!] */\n',
    )
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(package_dir / "Dio.m", '[!VAR "MacroVal" = "\'FROM_PKG\'"!]\n')
    _write(package_dir / "src" / "Dio_PBcfg.c", '/* original package */\n')

    generator = CodeGenerator(
        _module_def(),
        _config(),
        project_template_dir=overlay_root,
        package_template_dir=package_dir,
    )
    assert generator.generate_all(tmp_path / "out") is True

    out = tmp_path / "out" / "Dio" / "src" / "Dio_PBcfg.c"
    assert "/* overlay macro=FROM_PKG */" in out.read_text(encoding="utf-8")


def test_flat_gen_layout_writes_without_module_subdir(tmp_path):
    """Format 8 projects with explicit gen_layout='flat' write directly under gen/ via project_paths.gen_dir."""
    _, project = _v8_project(tmp_path)
    project.directories = project_paths.ProjectDirectories.from_dict(
        {"gen_layout": "flat"}, project_paths.ProjectDirectories.default_v8()
    )
    pkg_dir = tmp_path / "pkg" / "generate_PB"
    _write(pkg_dir / "Dio_Cfg.h", "/* flat */\n")

    gen_root = project_paths.gen_dir(project, "Dio")
    assert gen_root == tmp_path / "gen"

    generator = CodeGenerator(_module_def(), _config(), package_template_dir=pkg_dir)
    assert generator.generate_all(gen_root, variant="Default", flat=True) is True

    out = tmp_path / "gen" / "include" / "Dio_Cfg.h"
    assert out.is_file()
    assert out.read_text(encoding="utf-8") == "/* flat */\n"
    assert not (tmp_path / "gen" / "Dio").exists()


def test_per_module_gen_layout_default_and_custom_variant(tmp_path):
    """Format 8 projects default to per-module; Default omits variant subdir while custom variants keep it."""
    _, project = _v8_project(tmp_path)
    assert project_paths.dirs(project).gen_layout == "per-module"
    assert project_paths.gen_dir(project, "Dio") == tmp_path / "gen" / "Dio"

    pkg_dir = tmp_path / "pkg" / "generate_PB"
    _write(pkg_dir / "Dio_Cfg.h", "/* per-module */\n")

    generator = CodeGenerator(_module_def(), _config(), package_template_dir=pkg_dir)
    assert generator.generate_all(tmp_path / "gen", variant="Default", flat=False) is True
    assert (tmp_path / "gen" / "Dio" / "include" / "Dio_Cfg.h").is_file()
    assert not (tmp_path / "gen" / "Dio" / "Default").exists()

    assert generator.generate_all(tmp_path / "gen", variant="VariantA", flat=False) is True
    assert (tmp_path / "gen" / "Dio" / "VariantA" / "include" / "Dio_Cfg.h").is_file()


# --- Step 3: variant-scoped overlay (templates/<pkg_dir_name>/) -----------------

def _cantrcv_module_def():
    from autosar_configurator.core.model.definition_model import EcucModuleDef
    return EcucModuleDef(short_name="CanTrcv", definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv")


def _cantrcv_config():
    from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
    return EcucModuleConfiguration(short_name="CanTrcv", definition_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv")


def test_package_dir_name_v8_and_legacy(tmp_path):
    pkg_root = tmp_path / "modules" / "davinci" / "CanTrcv_Tle9255"
    (pkg_root / "templates").mkdir(parents=True)
    pkg = ModulePackage(
        pkg_root,
        ModuleManifest(
            module="CanTrcv",
            definition="/MICROSAR/CanTrcv_Tle9255/CanTrcv",
            templates="templates",
        ),
    )
    _, v8_project = _v8_project(tmp_path, packages={"CanTrcv": pkg})
    assert project_paths.package_dir_name(v8_project, "CanTrcv") == "CanTrcv_Tle9255"
    assert project_paths.package_dir_name(v8_project, "Missing") is None
    sources = project_paths.template_sources(v8_project, "CanTrcv")
    assert isinstance(sources, tuple) and len(sources) == 2

    v7_project = WorkspaceManager().create_project("V7", tmp_path / "V7.dpa", format_version=7)
    v7_project.packages = {"CanTrcv": pkg}
    assert project_paths.package_dir_name(v7_project, "CanTrcv") is None


def test_variant_overlay_precedence_and_fallback(tmp_path):
    overlay_root = tmp_path / "templates"
    _write(overlay_root / "CanTrcv_Tle9255" / "CanTrcv_Cfg.h", "/* variant overlay */\n")
    _write(overlay_root / "CanTrcv_GenericCan" / "CanTrcv_Cfg.h", "/* sibling variant */\n")
    _write(overlay_root / "CanTrcv" / "CanTrcv_Cfg.h", "/* generic overlay */\n")
    _write(overlay_root / "CanTrcv" / "CanTrcv_Lcfg.c", "/* generic lcfg */\n")

    pkg_dir = tmp_path / "pkg" / "templates"
    _write(pkg_dir / "CanTrcv_Cfg.h", "/* package cfg */\n")
    _write(pkg_dir / "CanTrcv_Lcfg.c", "/* package lcfg */\n")
    _write(pkg_dir / "CanTrcv_PBcfg.c", "/* package pbcfg */\n")

    generator = CodeGenerator(
        _cantrcv_module_def(),
        _cantrcv_config(),
        project_template_dir=overlay_root,
        package_template_dir=pkg_dir,
        package_dir_name="CanTrcv_Tle9255",
    )
    assert generator.generate_all(tmp_path / "out") is True

    assert (tmp_path / "out" / "CanTrcv" / "include" / "CanTrcv_Cfg.h").read_text(encoding="utf-8") == "/* variant overlay */\n"
    assert (tmp_path / "out" / "CanTrcv" / "src" / "CanTrcv_Lcfg.c").read_text(encoding="utf-8") == "/* generic lcfg */\n"
    assert (tmp_path / "out" / "CanTrcv" / "src" / "CanTrcv_PBcfg.c").read_text(encoding="utf-8") == "/* package pbcfg */\n"


def test_variant_overlay_include_macro_precedence(tmp_path):
    overlay_root = tmp_path / "templates"
    variant_macro = _write(
        overlay_root / "CanTrcv_Tle9255" / "CanTrcv.m",
        '[!VAR "MacroVal" = "\'FROM_VARIANT\'"!]\n',
    )
    generic_macro = _write(
        overlay_root / "CanTrcv" / "CanTrcv.m",
        '[!VAR "MacroVal" = "\'FROM_GENERIC\'"!]\n',
    )
    pkg_dir = tmp_path / "pkg" / "templates"
    _write(pkg_dir / "CanTrcv.m", '[!VAR "MacroVal" = "\'FROM_PKG\'"!]\n')
    _write(pkg_dir / "CanTrcv_PBcfg.c", '[!INCLUDE "CanTrcv.m"!]\n/* val=[!"$MacroVal"!] */\n')

    generator = CodeGenerator(
        _cantrcv_module_def(),
        _cantrcv_config(),
        project_template_dir=overlay_root,
        package_template_dir=pkg_dir,
        package_dir_name="CanTrcv_Tle9255",
    )
    out_file = tmp_path / "out" / "CanTrcv" / "src" / "CanTrcv_PBcfg.c"

    assert generator.generate_all(tmp_path / "out") is True
    assert "/* val=FROM_VARIANT */" in out_file.read_text(encoding="utf-8")

    variant_macro.unlink()
    assert generator.generate_all(tmp_path / "out") is True
    assert "/* val=FROM_GENERIC */" in out_file.read_text(encoding="utf-8")

    generic_macro.unlink()
    assert generator.generate_all(tmp_path / "out") is True
    assert "/* val=FROM_PKG */" in out_file.read_text(encoding="utf-8")


def test_variant_overlay_fingerprint_matches_generic_and_package(tmp_path):
    content = "/* identical template content */\n"
    overlay_root = tmp_path / "templates"
    _write(overlay_root / "CanTrcv_Tle9255" / "CanTrcv_Cfg.h", content)
    generic_overlay = tmp_path / "generic_templates"
    _write(generic_overlay / "CanTrcv" / "CanTrcv_Cfg.h", content)
    pkg_dir = tmp_path / "pkg" / "templates"
    _write(pkg_dir / "CanTrcv_Cfg.h", content)

    from_variant = CodeGenerator(
        _cantrcv_module_def(),
        _cantrcv_config(),
        project_template_dir=overlay_root,
        package_dir_name="CanTrcv_Tle9255",
    )
    from_generic = CodeGenerator(
        _cantrcv_module_def(),
        _cantrcv_config(),
        project_template_dir=generic_overlay,
    )
    from_package = CodeGenerator(
        _cantrcv_module_def(),
        _cantrcv_config(),
        package_template_dir=pkg_dir,
    )

    fp_variant = from_variant._calculate_fingerprint(
        template_types=from_variant._discover_template_types("CanTrcv")
    )
    fp_generic = from_generic._calculate_fingerprint(
        template_types=from_generic._discover_template_types("CanTrcv")
    )
    fp_package = from_package._calculate_fingerprint(
        template_types=from_package._discover_template_types("CanTrcv")
    )
    assert fp_variant == fp_generic == fp_package


def test_eb_template_engine_preserves_template_dir_over_fallback_and_supports_priority(tmp_path):
    """Direct EBTemplateEngine keeps template_dir ahead of fallback include_search_paths,
    allows explicit priority_include_paths ahead of template_dir, and never inserts Path('.') ahead
    of explicit search paths when template_dir=None."""
    from autosar_configurator.generator.eb_template_engine import EBTemplateEngine

    prio_dir = tmp_path / "prio"
    tpl_dir = tmp_path / "tpl"
    extra_dir = tmp_path / "extra"
    _write(prio_dir / "M.m", '[!VAR "V" = "\'PRIO\'"!]\n')
    _write(tpl_dir / "M.m", '[!VAR "V" = "\'TPL\'"!]\n')
    _write(extra_dir / "M.m", '[!VAR "V" = "\'EXTRA\'"!]\n')

    tpl_text = '[!INCLUDE "M.m"!][!"$V"!]'
    ctx = {"module_def": _module_def(), "configuration": _config()}

    # Direct caller without priority_include_paths: template_dir > include_search_paths
    direct = EBTemplateEngine(strict=False, template_dir=tpl_dir, include_search_paths=[extra_dir])
    assert direct.render(tpl_text, ctx).strip() == "TPL"

    # Caller with priority_include_paths: priority > template_dir > include_search_paths
    layered = EBTemplateEngine(
        strict=False,
        template_dir=tpl_dir,
        include_search_paths=[extra_dir],
        priority_include_paths=[prio_dir],
    )
    assert layered.render(tpl_text, ctx).strip() == "PRIO"

    (prio_dir / "M.m").unlink()
    layered_after_prio = EBTemplateEngine(
        strict=False,
        template_dir=tpl_dir,
        include_search_paths=[extra_dir],
        priority_include_paths=[prio_dir],
    )
    assert layered_after_prio.render(tpl_text, ctx).strip() == "TPL"

    (tpl_dir / "M.m").unlink()
    layered_after_tpl = EBTemplateEngine(
        strict=False,
        template_dir=tpl_dir,
        include_search_paths=[extra_dir],
        priority_include_paths=[prio_dir],
    )
    assert layered_after_tpl.render(tpl_text, ctx).strip() == "EXTRA"

    # template_dir=None must NOT put Path('.') at index 0 over explicit include_search_paths
    no_tpl = EBTemplateEngine(strict=False, template_dir=None, include_search_paths=[extra_dir])
    assert no_tpl.renderer.include_search_paths[0].resolve() == extra_dir.resolve()
    assert Path(".") not in no_tpl.renderer.include_search_paths


def test_build_include_search_paths_does_not_expose_package_parent_or_duplicate_overlay_root(tmp_path):
    """_build_include_search_paths keeps pkg_root private and keeps overlay_root behind package_dir."""
    overlay_root = tmp_path / "templates"
    variant_dir = overlay_root / "CanTrcv_Tle9255"
    generic_dir = overlay_root / "CanTrcv"
    variant_dir.mkdir(parents=True)
    generic_dir.mkdir(parents=True)

    pkg_root = tmp_path / "pkg_root"
    pkg_tpl_dir = pkg_root / "templates"
    (pkg_tpl_dir / "sub").mkdir(parents=True)

    gen = CodeGenerator(
        _cantrcv_module_def(),
        _cantrcv_config(),
        project_template_dir=overlay_root,
        package_template_dir=pkg_tpl_dir,
        package_dir_name="CanTrcv_Tle9255",
    )

    from_pkg = [p.resolve() for p in gen._build_include_search_paths("CanTrcv", pkg_tpl_dir.resolve())]
    assert pkg_root.resolve() not in from_pkg
    assert variant_dir.resolve() in from_pkg
    assert generic_dir.resolve() in from_pkg
    assert from_pkg.index(variant_dir.resolve()) < from_pkg.index(pkg_tpl_dir.resolve())

    from_variant = [p.resolve() for p in gen._build_include_search_paths("CanTrcv", variant_dir.resolve())]
    assert from_variant.index(pkg_tpl_dir.resolve()) < from_variant.index(overlay_root.resolve())
    assert len(from_variant) == len(set(from_variant))


def test_renderer_normalizes_str_template_dir_and_search_paths(tmp_path):
    """Direct Renderer callers passing str template_dir/include_search_paths should work cleanly."""
    from autosar_configurator.generator.eb.renderer import Renderer

    tpl_dir = tmp_path / "tpl"
    extra_dir = tmp_path / "extra"
    _write(tpl_dir / "M.m", '[!VAR "VM" = "\'TPL\'"!]\n')
    _write(extra_dir / "E.m", '[!VAR "VE" = "\'EXTRA\'"!]\n')

    r = Renderer(strict=False, template_dir=str(tpl_dir), include_search_paths=[str(extra_dir)])
    assert isinstance(r.template_dir, Path)
    assert all(isinstance(p, Path) for p in r.include_search_paths)
    r.load_module(_module_def(), _config())
    rendered = r.render('[!INCLUDE "M.m"!][!INCLUDE "E.m"!][!"$VM"!]:[!"$VE"!]', module_name="Dio")
    assert rendered.strip() == "TPL:EXTRA"


def test_generator_ecu_resources_excludes_inactive_variant_overlay_properties(tmp_path):
    """CodeGenerator._load_ecu_resources skips .properties in inactive sibling variant dirs under templates/
    while keeping generic module, active variant, and unrelated module .properties."""
    overlay_root = tmp_path / "templates"
    _write(overlay_root / "CanTrcv" / "common.properties", "CanTrcv.Shared=FROM_GENERIC\nCanTrcv.CommonOnly=1\n")
    _write(overlay_root / "CanTrcv_Tle9255" / "active.properties", "CanTrcv.Shared=FROM_TLE\nCanTrcv.TleOnly=2\n")
    _write(overlay_root / "CanTrcv_GenericCan" / "inactive.properties", "CanTrcv.Shared=FROM_INACTIVE\nCanTrcv.InactiveOnly=99\n")
    _write(overlay_root / "Os" / "os.properties", "Os.CrossMod=5\n")

    gen = CodeGenerator(
        _cantrcv_module_def(),
        _cantrcv_config(),
        project_template_dir=overlay_root,
        package_dir_name="CanTrcv_Tle9255",
    )
    assert gen.ecu_resources["CanTrcv.Shared"] == "FROM_TLE"
    assert gen.ecu_resources["CanTrcv.CommonOnly"] == 1
    assert gen.ecu_resources["CanTrcv.TleOnly"] == 2
    assert gen.ecu_resources["Os.CrossMod"] == 5
    assert "CanTrcv.InactiveOnly" not in gen.ecu_resources


