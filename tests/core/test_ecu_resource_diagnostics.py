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


def test_os_master_core_outside_core_list():
    msgs = check_consistency({
        "OsResource.AvailableCores": ["CORE0", "CORE1", "CORE2", "CORE3"],
        "OsResource.MasterCore": "OS_CORE_ID_5",
    })
    assert len(msgs) == 1
    assert "OsResource.MasterCore" in msgs[0] and "CORE0" in msgs[0]


def test_os_master_core_in_os_macro_form_is_accepted():
    assert check_consistency({
        "OsResource.AvailableCores": ["CORE0", "CORE1"],
        "OsResource.MasterCore": "OS_CORE_ID_0",
    }) == []


def test_os_master_core_in_core_form_warns_because_templates_emit_it_verbatim():
    resources = {
        "OsResource.AvailableCores": ["CORE0", "CORE1"],
        "OsResource.MasterCore": "CORE0",
    }
    msgs = check_consistency(resources)
    assert len(msgs) == 1
    assert "not in OS_CORE_ID_<n> form" in msgs[0]
    assert resources["OsResource.MasterCore"] == "CORE0"      # never converted


def test_resource_master_core_must_be_core_form():
    msgs = check_consistency({
        "Resource.AvailableCores": ["CORE0", "CORE1"],
        "Resource.MasterCore": "OS_CORE_ID_0",
    })
    assert len(msgs) == 1 and "not in CORE<n> form" in msgs[0]


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


def test_key_defined_only_for_other_chips_is_information_not_warning(tmp_path):
    project = _project_with_xdm(tmp_path, "ecu:get('Port.AvailableGTMModule') ecu:get('Port.Gone')")
    report = diagnose(project, {}, other_chip_keys={"port.availablegtmmodule": ["CotexR52_THA610X"]})
    assert report.chip_specific == {"Port.AvailableGTMModule": ["CotexR52_THA610X"]}
    assert list(report.missing) == ["Port.Gone"]
    assert not any("AvailableGTMModule" in line for line in report.warning_lines())


def test_other_chip_keys_come_from_unselected_resource_files_and_chip_yaml(tmp_path):
    from autosar_configurator.core.hardware.chip_database import ChipDatabase, ChipDefinition
    from autosar_configurator.core.hardware.ecu_resource_resolver import other_chip_keys

    res = tmp_path / "Def" / "plugins" / "R" / "resource"
    res.mkdir(parents=True)
    (res / "CotexR52_THA610X_LFBGA180.properties").write_text("Port.OnlySmall: _1_\n", encoding="utf-8")
    (res / "CotexR52_THA6412_BGA516.properties").write_text("Port.Own: 1\n", encoding="utf-8")
    db = ChipDatabase()
    db.register_chip(ChipDefinition(name="OTHER", ecu_resources={"Os": {"Extra": 1}}))
    db.register_chip(ChipDefinition(name="THA6412_BGA516", ecu_resources={"Os": {"Mine": 1}}))

    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.selected_chip = "THA6412_BGA516"
    keys = other_chip_keys(project, db)
    assert keys["port.onlysmall"] == ["CotexR52_THA610X_LFBGA180"]
    assert keys["os.extra"] == ["OTHER"]
    assert "port.own" not in keys and "os.mine" not in keys


def test_same_findings_are_not_logged_twice(tmp_path, caplog):
    import logging

    project = _project_with_xdm(tmp_path, "ecu:get('Os.Missing')")
    project.ecu_resources = {}
    with caplog.at_level(logging.WARNING):
        project.diagnose_ecu_resources()
        project.diagnose_ecu_resources()
    assert sum("Os.Missing" in r.message for r in caplog.records) == 1


def test_collect_referenced_keys_scans_variant_overlay(tmp_path):
    from autosar_configurator.core.packages.package import ModulePackage
    from autosar_configurator.core.packages.types import ModuleManifest
    from autosar_configurator.core.project_paths import ProjectDirectories

    pkg_root = tmp_path / "modules" / "davinci" / "CanTrcv_Tle9255"
    (pkg_root / "config").mkdir(parents=True)
    def_file = pkg_root / "config" / "CanTrcv.arxml"
    def_file.write_text("<AUTOSAR/>", encoding="utf-8")

    variant_tpl = tmp_path / "templates" / "CanTrcv_Tle9255" / "CanTrcv_Cfg.h"
    variant_tpl.parent.mkdir(parents=True)
    variant_tpl.write_text('[!"ecu:get(\'CanTrcv.Tle9255SpiChannel\')"!]', encoding="utf-8")

    project = WorkspaceProject("p", tmp_path / "p.dpa", format_version=8)
    project.directories = ProjectDirectories.default_v8()
    project.packages = {
        "CanTrcv": ModulePackage(
            pkg_root,
            ModuleManifest(module="CanTrcv", definition="/MICROSAR/CanTrcv_Tle9255/CanTrcv"),
        )
    }
    project.module_defs = {"CanTrcv": def_file}

    keys = collect_referenced_keys(project)
    assert keys.get("CanTrcv.Tle9255SpiChannel") == {"CanTrcv"}


def test_ecu_has_guarded_key_is_not_reported_missing_or_unused(tmp_path):
    """Optional ecu:get() keys guarded by ecu:has() in the same file must not trigger missing warnings,
    nor be flagged as unused when defined."""
    project = _project_with_xdm(
        tmp_path,
        "<x/>",
        '[!IF "ecu:has(\'Det.Compiler\')"!][!VAR "c" = "ecu:get(\'Det.Compiler\')"!][!ENDIF!]',
    )
    report_empty = diagnose(project, {}, log=False)
    assert report_empty.missing == {}
    assert not report_empty.has_warnings

    report_defined = diagnose(project, {"Det.Compiler": "GCC"}, log=False)
    assert report_defined.missing == {}
    assert report_defined.unused == []


def test_ecu_has_guard_is_per_file_and_does_not_hide_unguarded_use(tmp_path):
    """Guarding ecu:get('Det.Compiler') with ecu:has() in one module/file must not suppress
    missing warnings for another module/file that accesses it without ecu:has()."""
    plugin_det = tmp_path / "Def" / "plugins" / "Det_X"
    (plugin_det / "config").mkdir(parents=True)
    (plugin_det / "generate_PB").mkdir()
    det_xdm = plugin_det / "config" / "Det.xdm"
    det_xdm.write_text("<x/>", encoding="utf-8")
    (plugin_det / "generate_PB" / "Det_Cfg.h").write_text(
        '[!IF "ecu:has(\'Det.Compiler\')"!][!"ecu:get(\'Det.Compiler\')"!][!ENDIF!]',
        encoding="utf-8",
    )

    plugin_can = tmp_path / "Def" / "plugins" / "Can_X"
    (plugin_can / "config").mkdir(parents=True)
    (plugin_can / "generate_PB").mkdir()
    can_xdm = plugin_can / "config" / "Can.xdm"
    can_xdm.write_text("<x/>", encoding="utf-8")
    (plugin_can / "generate_PB" / "Can_Cfg.h").write_text(
        '[!"ecu:get(\'Det.Compiler\')"!]',
        encoding="utf-8",
    )

    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.module_defs = {"Det": det_xdm, "Can": can_xdm}
    report = diagnose(project, {}, log=False)
    assert report.missing == {"Det.Compiler": ["Can"]}

