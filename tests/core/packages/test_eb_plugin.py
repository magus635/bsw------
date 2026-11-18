"""Tests for EB plugin.xml inference."""

from pathlib import Path
import pytest

from autosar_configurator.core.packages import (
    infer_package,
    ModuleManifest,
    PackageError,
)
from autosar_configurator.core.packages.eb_plugin import infer_from_plugin_xml


# Use tracked fixture plugins
REPO_ROOT = Path(__file__).resolve().parents[3]
MCU_PLUGIN = REPO_ROOT / "test_import_project" / "Def" / "plugins" / "Mcu_THA6_AS440"
CAN_PLUGIN = REPO_ROOT / "test_import_project" / "Def" / "plugins" / "Can_THA6_AS440"


def test_mcu_plugin_inferred():
    """Mcu plugin: definition, pre, files, exchange_copies, templates."""
    manifest = infer_from_plugin_xml(MCU_PLUGIN)

    assert manifest.definition == "/THA6_AS440_FuSa/Mcu"
    assert manifest.module == "Mcu"
    assert manifest.pre == ["/THA6_AS440_FuSa/McuPreConfiguration"]
    assert manifest.rec == []
    assert manifest.inferred is True
    assert manifest.templates == "generate_PB"

    # Files: config/Mcu.xdm and config/McuPreConfiguration.xdm
    file_paths = {f.path for f in manifest.files}
    assert file_paths == {"config/Mcu.xdm", "config/McuPreConfiguration.xdm"}

    # Exchange copies: 3 arxml files
    assert len(manifest.exchange_copies) == 3
    assert "autosar/Mcu_THA610X_LFBGA180.arxml" in manifest.exchange_copies
    assert "autosar/Mcu_THA6206_LFBGA292.arxml" in manifest.exchange_copies
    assert "autosar/Mcu_THA6412_BGA516.arxml" in manifest.exchange_copies


def test_can_plugin_has_no_pre():
    """Can plugin: no preconfig section → empty pre."""
    manifest = infer_from_plugin_xml(CAN_PLUGIN)

    assert manifest.definition == "/THA6_AS440_FuSa/Can"
    assert manifest.module == "Can"
    assert manifest.pre == []
    assert manifest.rec == []
    assert manifest.inferred is True
    assert manifest.templates == "generate_PB"

    # Files: only config/Can.xdm
    file_paths = {f.path for f in manifest.files}
    assert file_paths == {"config/Can.xdm"}


def test_infer_package_from_plugin():
    """infer_package falls back to plugin.xml when no module.json."""
    manifest = infer_package(MCU_PLUGIN)
    assert manifest.definition == "/THA6_AS440_FuSa/Mcu"
    assert manifest.inferred is True


def test_infer_package_missing_both(tmp_path):
    """infer_package raises PackageError if neither manifest nor plugin.xml."""
    nonexistent = tmp_path / "nonexistent"
    with pytest.raises(PackageError, match="No module.json or plugin.xml"):
        infer_package(nonexistent)


def test_arxml_only_plugin_infers_chip_conditions(tmp_path):
    """Plugin with only autosar/*.arxml (no xdm) infers chip conditions from filenames."""
    plugin_dir = tmp_path / "Foo_THA6_AS440"
    (plugin_dir / "autosar").mkdir(parents=True)
    (plugin_dir / "autosar" / "Foo_THA6206_LFBGA292.arxml").write_text("<AUTOSAR/>", encoding="utf-8")
    (plugin_dir / "autosar" / "Foo_THA6412_BGA516.arxml").write_text("<AUTOSAR/>", encoding="utf-8")
    (plugin_dir / "plugin.xml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<plugin>
  <extension point="dreisoft.tresos.launcher2.plugin.configuration">
    <configuration>
      <schema/>
      <data>
        <schemaNode path="ASPath:/THA6_AS440_FuSa/Foo"/>
      </data>
    </configuration>
  </extension>
</plugin>
""", encoding="utf-8")

    manifest = infer_from_plugin_xml(plugin_dir)
    assert manifest.module == "Foo"
    assert manifest.definition == "/THA6_AS440_FuSa/Foo"
    assert manifest.exchange_copies == []
    assert [(pf.path, pf.chips) for pf in manifest.files] == [
        ("autosar/Foo_THA6206_LFBGA292.arxml", ["THA6206_LFBGA292"]),
        ("autosar/Foo_THA6412_BGA516.arxml", ["THA6412_BGA516"]),
    ]
