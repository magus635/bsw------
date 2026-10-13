"""Resource .properties files named after the device only still match a device_package chip."""
import pytest

from autosar_configurator.core.hardware.tresos_properties_parser import resource_file_matches_chip as match


@pytest.mark.parametrize("stem,expected", [
    ("CotexR52_THA6206_LFBGA292", True),
    ("Os_Resource_THA6206", True),
    ("CotexR52_THA6206_BGA999", True),
    ("CotexR52_THA610X_LFBGA180", False),
    ("Os_Resource_THA6412", False),
    ("Os_Resource_THA62060x", False),
])
def test_device_package_chip(stem, expected):
    assert match(stem, "tha6206_lfbga292") is expected


def test_device_only_chip_needs_whole_token():
    assert match("Os_Resource_THA6206", "tha6206")
    assert not match("Os_Resource_THA62060x", "tha6206")
