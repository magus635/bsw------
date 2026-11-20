"""Regression tests for MCAL Resource (Mcall_Cfg.h) discovery and [!INCLUDE!][!ERROR!] propagation."""
from pathlib import Path

import pytest

from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
from autosar_configurator.core.model.definition_model import EcucModuleDef
from autosar_configurator.generator.eb.errors import TemplateExecutionError
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
from autosar_configurator.generator.generator import CodeGenerator


def _write(path: Path, text: str) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    return path


def _make_module(name: str):
    def_ref = f"/THA6_AS440_FuSa/{name}"
    return (
        EcucModuleDef(short_name=name, definition_ref=def_ref),
        EcucModuleConfiguration(short_name=name, definition_ref=def_ref),
    )


def test_resource_discovers_and_generates_mcall_cfg_h(tmp_path):
    """Resource module package templates named Mcall_Cfg.h must be discovered and generated."""
    mod_def, cfg = _make_module("Resource")
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(
        package_dir / "Resource_Cfg_Common.m",
        '[!NOCODE!][!VAR "TestFlag"="\'1\'"!][!ENDNOCODE!]\n',
    )
    _write(
        package_dir / "include" / "Mcall_Cfg.h",
        '[!NOCODE!][!INCLUDE "Resource_Cfg_Common.m"!][!ENDNOCODE!]'
        '#define MCAL_FLAG ([!"$TestFlag"!]U)\n',
    )

    generator = CodeGenerator(mod_def, cfg, package_template_dir=package_dir)
    ok = generator.generate_all(tmp_path / "gen", variant="Default", flat=False)

    assert ok is True
    assert generator.last_status == "generated"
    out_file = tmp_path / "gen" / "Resource" / "include" / "Mcall_Cfg.h"
    assert out_file.read_text(encoding="utf-8").strip() == "#define MCAL_FLAG (1U)"
    assert not (tmp_path / "gen" / "Resource" / "include" / "Resource_Mcall_Cfg.h").exists()


def test_resource_overlay_overrides_package_mcall_cfg_h(tmp_path):
    """Project overlay templates/Resource/Mcall_Cfg.h wins over package Mcall_Cfg.h."""
    mod_def, cfg = _make_module("Resource")
    package_dir = tmp_path / "pkg" / "generate_PB"
    overlay_root = tmp_path / "templates"
    _write(package_dir / "include" / "Mcall_Cfg.h", "/* pkg */\n")
    _write(overlay_root / "Resource" / "Mcall_Cfg.h", "/* overlay */\n")

    generator = CodeGenerator(
        mod_def,
        cfg,
        project_template_dir=overlay_root,
        package_template_dir=package_dir,
    )
    ok = generator.generate_all(tmp_path / "gen")

    assert ok is True
    out_file = tmp_path / "gen" / "Resource" / "include" / "Mcall_Cfg.h"
    assert out_file.read_text(encoding="utf-8") == "/* overlay */\n"


def test_resource_mcall_tpl_suffix_stripped(tmp_path):
    """Resource template Mcall_Cfg.h.tpl strips .tpl for output and is resolvable by output name."""
    mod_def, cfg = _make_module("Resource")
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(package_dir / "Mcall_Cfg.h.tpl", "/* from tpl */\n")

    generator = CodeGenerator(mod_def, cfg, package_template_dir=package_dir)
    ok = generator.generate_all(tmp_path / "gen")

    assert ok is True
    out_file = tmp_path / "gen" / "Resource" / "include" / "Mcall_Cfg.h"
    assert out_file.read_text(encoding="utf-8") == "/* from tpl */\n"
    assert generator._load_template_with_path("Mcall_Cfg.h", "Resource")[0] == "/* from tpl */\n"


def test_non_resource_module_still_ignores_mcall_prefix(tmp_path):
    """Extra mcall_ prefix is scoped strictly to Resource and must not leak to other modules."""
    mod_def, cfg = _make_module("Dio")
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(package_dir / "include" / "Mcall_Cfg.h", "/* ignored */\n")

    generator = CodeGenerator(mod_def, cfg, package_template_dir=package_dir)
    assert generator._discover_template_types("Dio") == []


def test_include_explicit_error_propagates_in_non_strict_mode(tmp_path):
    """Explicit [!ERROR!] in an [!INCLUDE!]d file must abort rendering even when strict=False."""
    common_m = _write(
        tmp_path / "Common.m",
        "[!NOCODE!]\n[!ERROR!]080-00-04-ERROR: missing ref[!ENDERROR!]\n[!ENDNOCODE!]\n",
    )
    can_cfg = _write(
        tmp_path / "Can_Cfg.h",
        '[!NOCODE!][!INCLUDE "Common.m"!][!ENDNOCODE!]\n/* tail */\n',
    )

    renderer = Renderer(strict=False, template_dir=tmp_path)
    can_root = ConfigurationNode(short_name="Can", node_type="module", path="/Can")
    renderer.symbol_table.register_module("Can", can_root)

    with pytest.raises(TemplateExecutionError) as exc_info:
        renderer.render_file(can_cfg, module_name="Can")

    assert "080-00-04-ERROR" in str(exc_info.value)
    assert Path(exc_info.value.template_file).resolve() == common_m.resolve()


def test_include_missing_file_still_ignored_in_non_strict_mode(tmp_path):
    """Missing include files in non-strict mode keep legacy non-fatal behavior."""
    renderer = Renderer(strict=False, template_dir=tmp_path)
    can_root = ConfigurationNode(short_name="Can", node_type="module", path="/Can")
    renderer.symbol_table.register_module("Can", can_root)

    out = renderer.render('[!INCLUDE "DoesNotExist.m"!]OK', module_name="Can")
    assert out == "OK"


def test_code_generator_fails_when_included_macro_raises_error(tmp_path):
    """CodeGenerator must fail and avoid writing partial output if included macro throws [!ERROR!]."""
    mod_def, cfg = _make_module("Can")
    package_dir = tmp_path / "pkg" / "generate_PB"
    _write(
        package_dir / "Can_Cfg_Common.m",
        "[!NOCODE!][!ERROR!]080-00-04-ERROR: bad config[!ENDERROR!][!ENDNOCODE!]\n",
    )
    _write(
        package_dir / "include" / "Can_Cfg.h",
        '[!NOCODE!][!INCLUDE "Can_Cfg_Common.m"!][!ENDNOCODE!]\n/* bad */\n',
    )

    generator = CodeGenerator(mod_def, cfg, package_template_dir=package_dir)
    ok = generator.generate_all(tmp_path / "gen")

    assert ok is False
    assert generator.last_status == "failed"
    assert not (tmp_path / "gen" / "Can" / "include" / "Can_Cfg.h").exists()

