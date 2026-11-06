"""Two definitions that share a SHORT-NAME in different scopes are different
definitions (vBaseEnv defines vBaseEnvMemLayoutHwRegion both directly under
vBaseEnvGeneral and under vBaseEnvDerivativeInformation)."""
from autosar_configurator.core.model import definition_refs as defrefs

NAME = "vBaseEnvMemLayoutHwRegion"
STUB = "vBaseEnvGeneral/" + NAME
NESTED = "vBaseEnvGeneral/vBaseEnvDerivativeInformation/" + NAME


def test_nested_instance_matches_only_the_nested_definition():
    ref = "/MICROSAR/vBaseEnv/" + NESTED
    assert defrefs.matches_container_def(ref, NESTED, NAME, "vBaseEnv")
    assert not defrefs.matches_container_def(ref, STUB, NAME, "vBaseEnv")


def test_stub_instance_matches_only_the_stub_definition():
    ref = "/MICROSAR/vBaseEnv/" + STUB
    assert defrefs.matches_container_def(ref, STUB, NAME, "vBaseEnv")
    assert not defrefs.matches_container_def(ref, NESTED, NAME, "vBaseEnv")


def test_definition_ref_written_by_the_tool_matches_its_definition():
    ref = "/MICROSAR/vBaseEnv/" + STUB
    assert defrefs.matches_container_def(ref, STUB, NAME)


def test_eb_tresos_instance_index_still_matches():
    assert defrefs.matches_container_def(
        "/THA6_ASR21/Os/OsOS/OsAlarm_0", "OsOS/OsAlarm", "OsAlarm", "Os")


def test_eb_tresos_vendor_package_path_still_matches():
    assert defrefs.matches_container_def(
        "/THA6_ASR21/Os/OsOS/OsHooks", "OsOS/OsHooks", "OsHooks", "Os")


def test_top_level_container_matches():
    assert defrefs.matches_container_def(
        "/MICROSAR/vBaseEnv/vBaseEnvGeneral", "vBaseEnvGeneral", "vBaseEnvGeneral", "vBaseEnv")


def test_a_bare_short_name_still_matches_a_scoped_definition():
    """Value files written by older tools name only the last segment."""
    assert defrefs.matches_container_def(
        "/SomePackage/SomeModule/" + NAME, STUB, NAME, "SomeModule")


def test_a_scoped_ref_does_not_match_a_different_scope():
    assert not defrefs.matches_container_def(
        "/MICROSAR/vBaseEnv/vBaseEnvGeneral/vBaseEnvInterruptHandling",
        "vBaseEnvGeneral/vBaseEnvPeripheralClocks", "vBaseEnvPeripheralClocks", "vBaseEnv")
