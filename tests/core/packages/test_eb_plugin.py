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
MCU_PLUGIN = Path("D:/bsw-------main/bsw------/test_import_project/Def/plugins/Mcu_THA6_AS440")
CAN_PLUGIN = Path("D:/bsw-------main/bsw------/test_import_project/Def/plugins/Can_THA6_AS440")


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


def test_infer_package_missing_both():
    """infer_package raises PackageError if neither manifest nor plugin.xml."""
    nonexistent = Path("D:/bsw-------main/bsw------/tests/core/packages/nonexistent")
    with pytest.raises(PackageError, match="No module.json or plugin.xml"):
        infer_package(nonexistent)
