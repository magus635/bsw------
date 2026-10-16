"""ECU resource diagnostics: missing/unused keys and consistency rules."""
from pathlib import Path

from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
    check_consistency,
    collect_referenced_keys,
    diagnose,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject


def _project_with_xdm(tmp_path: Path, xdm_text: str, template_text: str = "") -> WorkspaceProject:
    plugin = tmp_path / "Def" / "plugins" / "Os_X"
    (plugin / "config").mkdir(parents=True)
    (plugin / "generate_PB").mkdir()
    xdm = plugin / "config" / "Os.xdm"
    xdm.write_text(xdm_text, encoding="utf-8")
    if template_text:
        (plugin / "generate_PB" / "Os_Cfg.h").write_text(template_text, encoding="utf-8")
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.module_defs = {"Os": xdm}
    return project


def test_missing_key_names_key_and_module(tmp_path):
    project = _project_with_xdm(
        tmp_path, """<a:da expr="ecu:get('OsResource.NumOfCores')"/>""")
    report = diagnose(project, {})
    assert report.missing == {"OsResource.NumOfCores": ["Os"]}
    assert report.has_warnings
    assert "OsResource.NumOfCores" in report.warning_lines()[0]
    assert "Os" in report.warning_lines()[0]


def test_keys_in_templates_are_scanned_too(tmp_path):
    project = _project_with_xdm(
        tmp_path, "<x/>", "#define N ([!\"ecu:get('Os.FromTemplate')\"!])")
    assert collect_referenced_keys(project) == {"Os.FromTemplate": {"Os"}}


def test_defined_and_referenced_key_is_neither_missing_nor_unused(tmp_path):
    project = _project_with_xdm(tmp_path, "ecu:list('OsResource.AvailableCores')")
    report = diagnose(project, {"OsResource.AvailableCores": ["CORE0"]})
    assert report.missing == {} and report.unused == []


def test_lookup_is_case_insensitive_like_ecu_get(tmp_path):
    project = _project_with_xdm(tmp_path, "ecu:get('os.numofcores')")
    assert diagnose(project, {"Os.NumOfCores": 1}).missing == {}


def test_unreferenced_key_is_information_only(tmp_path):
    project = _project_with_xdm(tmp_path, "<x/>")
    report = diagnose(project, {"Os.Spare": 1})
    assert report.unused == ["Os.Spare"]
    assert not report.has_warnings


def test_dynamic_key_is_not_scanned_and_noted(tmp_path):
    project = _project_with_xdm(
        tmp_path, "<x/>", "[!\"ecu:get(concat('Adc.SyncGroup.', $unit))\"!]")
    report = diagnose(project, {})
    assert report.missing == {}
    assert "concatenation" in report.note


def test_count_mismatch_names_both_keys_and_values():
    msgs = check_consistency({
        "OsResource.NumOfCores": 4,
        "OsResource.AvailableCores": ["CORE0", "CORE1", "CORE2"],
    })
    assert len(msgs) == 1
    assert "OsResource.NumOfCores" in msgs[0] and "OsResource.AvailableCores" in msgs[0]
    assert "4" in msgs[0] and "3" in msgs[0]


def test_master_core_outside_core_list():
    msgs = check_consistency({
        "OsResource.AvailableCores": ["CORE0", "CORE1", "CORE2", "CORE3"],
        "OsResource.MasterCore": "CORE5",
    })
    assert len(msgs) == 1
    assert "OsResource.MasterCore" in msgs[0] and "CORE0" in msgs[0]


def test_master_core_in_other_notation_warns_and_is_not_converted():
    resources = {
        "OsResource.AvailableCores": ["CORE0", "CORE1"],
        "OsResource.MasterCore": "OS_CORE_ID_0",
    }
    msgs = check_consistency(resources)
    assert len(msgs) == 1
    assert "not in CORE<n> form" in msgs[0]
    assert resources["OsResource.MasterCore"] == "OS_CORE_ID_0"


def test_resource_master_core_list_checks_every_element():
    msgs = check_consistency({
        "Resource.AvailableCores": ["CORE0", "CORE1"],
        "Resource.MasterCore": ["CORE0", "CORE1"],
    })
    assert msgs == []


def test_ioc_type_count_rule():
    ok = {"Os.IocPrimitiveDataTypeNum": 2, "Os.IocPrimitiveDataType": ["uint8", "uint16"]}
    bad = {"Os.IocPrimitiveDataTypeNum": 3, "Os.IocPrimitiveDataType": ["uint8", "uint16"]}
    assert check_consistency(ok) == []
    assert len(check_consistency(bad)) == 1


def test_rules_need_both_keys():
    assert check_consistency({"OsResource.NumOfCores": 4}) == []
    assert check_consistency({}) == []


def test_project_stores_report(tmp_path):
    project = _project_with_xdm(tmp_path, "ecu:get('Os.Missing')")
    project.ecu_resources = {}
    report = project.diagnose_ecu_resources()
    assert report is project.ecu_resource_report
    assert "Os.Missing" in report.missing
