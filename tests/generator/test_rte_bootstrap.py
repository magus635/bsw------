"""Unit tests for built-in Rte BSWMD, source discovery, and project bootstrap."""

from pathlib import Path

from autosar_configurator.core.davinci_importer import SipPackageWriter
from autosar_configurator.core.model.definition_model import EcucParameterType
from autosar_configurator.core.packages.library import LibraryRef
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.validation_engine import ValidationEngine
from autosar_configurator.core.workspace_manager import WorkspaceManager, WorkspaceProject
from autosar_configurator.generator.rte import (
    EA_MECHANISMS,
    GENERATION_MODES,
    OPTIMIZATION_MODES,
    RteWorkbenchService,
    bootstrap_rte_module,
    builtin_rte_bswmd_path,
    discover_rte_sources,
)
from tests.generator.test_rte_workbench_service import _com_ib_xml, _write_ib_arxml


def _minimal_module_def_arxml(module_name: str, *, pkg_prefix: str = "AUTOSAR/EcucDefs", body: str = "") -> bytes:
    parts = [p for p in pkg_prefix.split("/") if p]
    inner = (
        "    <ELEMENTS>\n"
        "      <ECUC-MODULE-DEF>\n"
        f"        <SHORT-NAME>{module_name}</SHORT-NAME>\n"
        f"        <CONTAINERS>{body}</CONTAINERS>\n"
        "      </ECUC-MODULE-DEF>\n"
        "    </ELEMENTS>\n"
    )
    wrapped = inner
    for seg in reversed(parts):
        if wrapped is inner:
            wrapped = (
                "  <AR-PACKAGE>\n"
                f"    <SHORT-NAME>{seg}</SHORT-NAME>\n"
                f"{wrapped}"
                "  </AR-PACKAGE>\n"
            )
        else:
            wrapped = (
                "  <AR-PACKAGE>\n"
                f"    <SHORT-NAME>{seg}</SHORT-NAME>\n"
                "    <AR-PACKAGES>\n"
                f"{wrapped}"
                "    </AR-PACKAGES>\n"
                "  </AR-PACKAGE>\n"
            )
    xml = (
        '<?xml version="1.0" encoding="UTF-8"?>\n'
        '<AUTOSAR xmlns="http://autosar.org/schema/r4.0">\n'
        "  <AR-PACKAGES>\n"
        f"{wrapped}"
        "  </AR-PACKAGES>\n"
        "</AUTOSAR>\n"
    )
    return xml.encode("utf-8")


def test_builtin_rte_bswmd_parses_and_validates_cleanly():
    def_path = builtin_rte_bswmd_path()
    assert def_path.is_file()

    module_def = EcucDefParser().parse_module_def_file(def_path)
    assert module_def is not None
    assert module_def.short_name == "Rte"
    assert module_def.ar_path == "/AUTOSAR/EcucDefs/Rte"
    assert module_def.definition_ref == "/AUTOSAR/EcucDefs/Rte"

    expected_top = {
        "RteGeneration",
        "RteBswGeneral",
        "RteBswModuleInstance",
        "RteOsInteraction",
        "RteSwComponentInstance",
    }
    assert set(module_def.containers.keys()) == expected_top
    for cname in expected_top:
        assert module_def.containers[cname].lower_multiplicity == 0

    gen_def = module_def.containers["RteGeneration"]
    assert gen_def.parameters["RteGenerationMode"].param_type == EcucParameterType.ENUMERATION
    assert tuple(gen_def.parameters["RteGenerationMode"].literals) == GENERATION_MODES
    assert tuple(gen_def.parameters["RteOptimizationMode"].literals) == OPTIMIZATION_MODES

    inst_def = module_def.containers["RteBswModuleInstance"]
    assert set(inst_def.sub_containers.keys()) == {
        "RteBswExclusiveAreaImpl",
        "RteBswEventToTaskMapping",
    }
    ea_def = inst_def.sub_containers["RteBswExclusiveAreaImpl"]
    mech_def = ea_def.parameters["RteExclusiveAreaImplMechanism"]
    assert mech_def.param_type == EcucParameterType.ENUMERATION
    assert tuple(mech_def.literals) == EA_MECHANISMS


def test_bootstrap_builtin_rte_v8_save_reload_validate_and_generate(tmp_path: Path):
    proj_dir = tmp_path / "v8_proj"
    proj_dir.mkdir(parents=True)
    dpa_path = proj_dir / "V8Proj.dpa"

    wm = WorkspaceManager()
    project = wm.create_project("V8Proj", dpa_path, format_version=8)

    com_def_path = tmp_path / "Com_bswmd.arxml"
    com_def_path.write_bytes(_minimal_module_def_arxml("Com"))
    project.add_custom_module_from_file(com_def_path)

    _write_ib_arxml(proj_dir / "system" / "InternalBehavior" / "Com_ib_bswmd.arxml", _com_ib_xml())
    wm.save_project()

    sources = discover_rte_sources(project)
    assert sources.library_packages == []
    assert sources.deleted_archives == []
    assert sources.has_failed_entry is False

    mgr, source = bootstrap_rte_module(project)
    assert source == "builtin"
    assert mgr is not None
    assert "Rte" in project.module_managers
    assert (proj_dir / "modules" / "custom" / "Rte" / "module.json").is_file()

    # Defaults seeded for RteGeneration & RteBswGeneral
    svc = RteWorkbenchService(project)
    top_names = {c.short_name for c in mgr.configuration.containers}
    assert {"RteGeneration", "RteBswGeneral"}.issubset(top_names)

    # Register Com BSW instance with IB ExclusiveAreas
    svc.add_bsw_instance("Com", populate_exclusive_areas=True)
    project.resolve_all_references(force=True)

    # Full ValidationEngine run on Rte must report 0 errors
    engine = ValidationEngine(mgr.module_def, mgr.configuration, project_context=project)
    engine.register_default_rules()
    val_result = engine.validate()
    assert val_result.errors == []

    # Save and reload cleanly with a fresh WorkspaceManager
    wm.save_project()
    assert (proj_dir / "config" / "Rte.arxml").is_file()

    reloaded, failed = WorkspaceManager().load_project(dpa_path)
    assert failed == []
    assert "Rte" in reloaded.module_managers
    reloaded_rte = reloaded.module_managers["Rte"]
    assert reloaded_rte.def_missing is False
    reloaded_top = {c.short_name for c in reloaded_rte.configuration.containers}
    assert {"RteGeneration", "RteBswGeneral", "Com"}.issubset(reloaded_top)

    # Phase 1 generation succeeds on reloaded project
    ok, report, _ = RteWorkbenchService(reloaded).run_generation()
    assert ok is True
    assert not report.errors
    assert (proj_dir / "gen" / "Rte" / "include" / "Rte.h").is_file()
    assert (proj_dir / "gen" / "Rte" / "include" / "SchM_Com.h").is_file()


def test_bootstrap_activates_existing_library_rte_without_duplicating_custom(tmp_path: Path):
    proj_dir = tmp_path / "lib_proj"
    proj_dir.mkdir(parents=True)
    dpa_path = proj_dir / "LibProj.dpa"

    wm = WorkspaceManager()
    project = wm.create_project("LibProj", dpa_path, format_version=8)

    lib_root = proj_dir / "modules" / "davinci"
    SipPackageWriter.write_package(
        module_name="Rte",
        definition_content=_minimal_module_def_arxml("Rte", pkg_prefix="MICROSAR"),
        output_dir=lib_root,
        seed_builtin_templates=False,
    )
    project.module_libraries.append(LibraryRef(path="modules/davinci", kind="package", exclude=[]))
    wm.save_project()

    sources = discover_rte_sources(project)
    assert len(sources.library_packages) == 1
    assert sources.library_packages[0][1].manifest.definition == "/MICROSAR/Rte"

    mgr, source = bootstrap_rte_module(project, library_package=sources.library_packages[0])
    assert source == "library"
    assert "Rte" in project.module_managers
    assert mgr.module_def.ar_path == "/MICROSAR/Rte"
    assert not (proj_dir / "modules" / "custom" / "Rte").exists()

    wm.save_project()
    reloaded, failed = WorkspaceManager().load_project(dpa_path)
    assert failed == []
    assert "Rte" in reloaded.module_managers
    assert reloaded.module_managers["Rte"].module_def.ar_path == "/MICROSAR/Rte"


def test_bootstrap_builtin_rte_v7_save_reload_and_unsaved(tmp_path: Path):
    # Saved Format 7 project
    v7_dir = tmp_path / "v7_proj"
    v7_dir.mkdir(parents=True)
    v7_dpa = v7_dir / "V7Proj.dpa"

    wm = WorkspaceManager()
    proj7 = wm.create_project("V7Proj", v7_dpa, format_version=7)
    mgr7, source7 = bootstrap_rte_module(proj7)
    assert source7 == "builtin"
    assert (v7_dir / "Def" / "Rte_bswmd.arxml").is_file()
    assert mgr7 is proj7.module_managers["Rte"]

    wm.save_project()
    reloaded7, failed7 = WorkspaceManager().load_project(v7_dpa)
    assert failed7 == []
    assert "Rte" in reloaded7.module_managers
    assert reloaded7.module_managers["Rte"].def_missing is False

    # Unsaved / in-memory project (path=None)
    mem_proj = WorkspaceProject("InMemoryProj", path=None, format_version=8)
    mgr_mem, source_mem = bootstrap_rte_module(mem_proj)
    assert source_mem == "builtin"
    assert "Rte" in mem_proj.module_managers
    top_names = {c.short_name for c in mgr_mem.configuration.containers}
    assert {"RteGeneration", "RteBswGeneral"}.issubset(top_names)
