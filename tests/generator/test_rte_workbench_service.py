"""Unit tests for BswIbIndex events, RteSchMGenerator.preview(), and RteWorkbenchService."""

from pathlib import Path
from types import SimpleNamespace

import pytest

from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
)
from autosar_configurator.core.model.definition_model import EcucModuleDef
from autosar_configurator.core.project_paths import ProjectDirectories
from autosar_configurator.core.serializer.ecuc_serializer import EcucValueSerializer
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.rte import (
    BswIbIndex,
    RteGenerationSettings,
    RteSchMGenerator,
    RteWorkbenchService,
)

REAL_START_APP = Path("/Users/qlwang/Desktop/test3/StartApplication1")


def _write_ib_arxml(path: Path, body: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(
        '<?xml version="1.0" encoding="UTF-8"?>\n'
        '<AUTOSAR xmlns="http://autosar.org/schema/r4.0">\n'
        "  <AR-PACKAGES>\n"
        f"{body}\n"
        "  </AR-PACKAGES>\n"
        "</AUTOSAR>\n",
        encoding="utf-8",
    )


def _com_ib_xml() -> str:
    return """
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>Com_Impl</SHORT-NAME>
          <VENDOR-ID>30</VENDOR-ID>
          <AR-RELEASE-VERSION>4.03.00</AR-RELEASE-VERSION>
          <BEHAVIOR-REF DEST="BSW-INTERNAL-BEHAVIOR">/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior</BEHAVIOR-REF>
        </BSW-IMPLEMENTATION>
      </ELEMENTS>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>Com_ib_bswmd</SHORT-NAME>
          <AR-PACKAGES>
            <AR-PACKAGE>
              <SHORT-NAME>BswModuleDescriptions</SHORT-NAME>
              <ELEMENTS>
                <BSW-MODULE-DESCRIPTION>
                  <SHORT-NAME>Com</SHORT-NAME>
                  <INTERNAL-BEHAVIORS>
                    <BSW-INTERNAL-BEHAVIOR>
                      <SHORT-NAME>ComBehavior</SHORT-NAME>
                      <EXCLUSIVE-AREAS>
                        <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_RX</SHORT-NAME></EXCLUSIVE-AREA>
                        <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_TX</SHORT-NAME></EXCLUSIVE-AREA>
                      </EXCLUSIVE-AREAS>
                      <ENTITYS>
                        <BSW-SCHEDULABLE-ENTITY>
                          <SHORT-NAME>Com_MainFunctionRx_SE</SHORT-NAME>
                          <IMPLEMENTED-ENTRY-REF DEST="BSW-MODULE-ENTRY">/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com_MainFunctionRx</IMPLEMENTED-ENTRY-REF>
                        </BSW-SCHEDULABLE-ENTITY>
                        <BSW-SCHEDULABLE-ENTITY>
                          <SHORT-NAME>Com_MainFunctionTx_SE</SHORT-NAME>
                          <IMPLEMENTED-ENTRY-REF DEST="BSW-MODULE-ENTRY">/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com_MainFunctionTx</IMPLEMENTED-ENTRY-REF>
                        </BSW-SCHEDULABLE-ENTITY>
                      </ENTITYS>
                      <EVENTS>
                        <BSW-TIMING-EVENT>
                          <SHORT-NAME>Com_MainFunctionRxTimingEvent0</SHORT-NAME>
                          <STARTS-ON-EVENT-REF DEST="BSW-SCHEDULABLE-ENTITY">/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/Com_MainFunctionRx_SE</STARTS-ON-EVENT-REF>
                          <PERIOD>0.01</PERIOD>
                        </BSW-TIMING-EVENT>
                        <BSW-TIMING-EVENT>
                          <SHORT-NAME>Com_MainFunctionTxTimingEvent0</SHORT-NAME>
                          <STARTS-ON-EVENT-REF DEST="BSW-SCHEDULABLE-ENTITY">/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/Com_MainFunctionTx_SE</STARTS-ON-EVENT-REF>
                          <PERIOD>0.02</PERIOD>
                        </BSW-TIMING-EVENT>
                      </EVENTS>
                    </BSW-INTERNAL-BEHAVIOR>
                  </INTERNAL-BEHAVIORS>
                </BSW-MODULE-DESCRIPTION>
                <BSW-MODULE-ENTRY><SHORT-NAME>Com_MainFunctionRx</SHORT-NAME></BSW-MODULE-ENTRY>
                <BSW-MODULE-ENTRY><SHORT-NAME>Com_MainFunctionTx</SHORT-NAME></BSW-MODULE-ENTRY>
              </ELEMENTS>
            </AR-PACKAGE>
          </AR-PACKAGES>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
    """


def _dcm_ib_xml() -> str:
    return """
    <AR-PACKAGE>
      <SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>Dcm_Impl</SHORT-NAME>
          <VENDOR-ID>30</VENDOR-ID>
          <AR-RELEASE-VERSION>4.03.00</AR-RELEASE-VERSION>
          <BEHAVIOR-REF DEST="BSW-INTERNAL-BEHAVIOR">/MICROSAR/Dcm_ib_bswmd/BswModuleDescriptions/Dcm/DcmBehavior</BEHAVIOR-REF>
        </BSW-IMPLEMENTATION>
      </ELEMENTS>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>Dcm_ib_bswmd</SHORT-NAME>
          <AR-PACKAGES>
            <AR-PACKAGE>
              <SHORT-NAME>BswModuleDescriptions</SHORT-NAME>
              <ELEMENTS>
                <BSW-MODULE-DESCRIPTION>
                  <SHORT-NAME>Dcm</SHORT-NAME>
                  <INTERNAL-BEHAVIORS>
                    <BSW-INTERNAL-BEHAVIOR>
                      <SHORT-NAME>DcmBehavior</SHORT-NAME>
                      <EXCLUSIVE-AREAS>
                        <EXCLUSIVE-AREA><SHORT-NAME>DCM_EXCLUSIVE_AREA_0</SHORT-NAME></EXCLUSIVE-AREA>
                      </EXCLUSIVE-AREAS>
                      <ENTITYS>
                        <BSW-SCHEDULABLE-ENTITY>
                          <SHORT-NAME>Dcm_MainFunction_SE</SHORT-NAME>
                          <IMPLEMENTED-ENTRY-REF DEST="BSW-MODULE-ENTRY">/MICROSAR/Dcm_ib_bswmd/BswModuleDescriptions/Dcm_MainFunction</IMPLEMENTED-ENTRY-REF>
                        </BSW-SCHEDULABLE-ENTITY>
                      </ENTITYS>
                      <EVENTS>
                        <BSW-TIMING-EVENT>
                          <SHORT-NAME>Dcm_MainFunctionTimingEvent0</SHORT-NAME>
                          <STARTS-ON-EVENT-REF DEST="BSW-SCHEDULABLE-ENTITY">/MICROSAR/Dcm_ib_bswmd/BswModuleDescriptions/Dcm/DcmBehavior/Dcm_MainFunction_SE</STARTS-ON-EVENT-REF>
                          <PERIOD>0.01</PERIOD>
                        </BSW-TIMING-EVENT>
                      </EVENTS>
                    </BSW-INTERNAL-BEHAVIOR>
                  </INTERNAL-BEHAVIORS>
                </BSW-MODULE-DESCRIPTION>
                <BSW-MODULE-ENTRY><SHORT-NAME>Dcm_MainFunction</SHORT-NAME></BSW-MODULE-ENTRY>
              </ELEMENTS>
            </AR-PACKAGE>
          </AR-PACKAGES>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
    """


def _build_synthetic_project(tmp_path: Path):
    proj_dir = tmp_path / "proj"
    _write_ib_arxml(proj_dir / "system" / "InternalBehavior" / "Com_ib_bswmd.arxml", _com_ib_xml())
    _write_ib_arxml(proj_dir / "system" / "InternalBehavior" / "Dcm_ib_bswmd.arxml", _dcm_ib_xml())

    rte_cfg = EcucModuleConfiguration(short_name="Rte", definition_ref="/MICROSAR/Rte")
    com_inst = EcucContainerValue(
        short_name="Com",
        definition_ref="/MICROSAR/Rte/RteBswModuleInstance",
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    com_inst.set_reference_value(
        "RteBswModuleConfigurationRef",
        "/ActiveEcuC/Com",
        "/MICROSAR/Rte/RteBswModuleInstance/RteBswModuleConfigurationRef",
        dest_type="ECUC-FOREIGN-REFERENCE-DEF",
        value_ref_dest="ECUC-MODULE-CONFIGURATION-VALUES",
    )
    com_inst.set_reference_value(
        "RteBswImplementationRef",
        "/MICROSAR/Com_Impl",
        "/MICROSAR/Rte/RteBswModuleInstance/RteBswImplementationRef",
        dest_type="ECUC-FOREIGN-REFERENCE-DEF",
        value_ref_dest="BSW-IMPLEMENTATION",
    )
    # Configure only RX EA initially; leave TX EA as IB-only!
    ea_rx = EcucContainerValue(
        short_name="COM_EXCLUSIVE_AREA_RX",
        definition_ref="/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl",
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    ea_rx.set_parameter_value(
        "RteExclusiveAreaImplMechanism",
        "ALL_INTERRUPT_BLOCKING",
        "/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl/RteExclusiveAreaImplMechanism",
    )
    ea_rx.set_reference_value(
        "RteBswExclusiveAreaRef",
        "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/COM_EXCLUSIVE_AREA_RX",
        "/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl/RteBswExclusiveAreaRef",
        dest_type="ECUC-FOREIGN-REFERENCE-DEF",
        value_ref_dest="EXCLUSIVE-AREA",
    )
    com_inst.add_sub_container(ea_rx)
    rte_cfg.add_container(com_inst)

    # Unloaded instance (CanNm)
    cannm_inst = EcucContainerValue(
        short_name="CanNm",
        definition_ref="/MICROSAR/Rte/RteBswModuleInstance",
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    cannm_inst.set_reference_value(
        "RteBswModuleConfigurationRef",
        "/ActiveEcuC/CanNm",
        "/MICROSAR/Rte/RteBswModuleInstance/RteBswModuleConfigurationRef",
    )
    rte_cfg.add_container(cannm_inst)

    # Read-only SWC mapping inside OsTask_10ms at position 1
    swc_inst = EcucContainerValue(
        short_name="AppSwc_EcuSwComposition",
        definition_ref="/MICROSAR/Rte/RteSwComponentInstance",
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    swc_ev = EcucContainerValue(
        short_name="SwcTimerEvent",
        definition_ref="/MICROSAR/Rte/RteSwComponentInstance/RteEventToTaskMapping",
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    swc_ev.set_parameter_value(
        "RtePositionInTask",
        1,
        "/MICROSAR/Rte/RteSwComponentInstance/RteEventToTaskMapping/RtePositionInTask",
    )
    swc_ev.set_reference_value(
        "RteMappedToTaskRef",
        "/ActiveEcuC/Os/OsTask_10ms",
        "/MICROSAR/Rte/RteSwComponentInstance/RteEventToTaskMapping/RteMappedToTaskRef",
    )
    swc_inst.add_sub_container(swc_ev)
    rte_cfg.add_container(swc_inst)

    # Os configuration with tasks, resource, spinlock
    os_cfg = EcucModuleConfiguration(short_name="Os", definition_ref="/MICROSAR/Os")
    for task_name, prio in (("OsTask_10ms", 10), ("OsTask_20ms", 20)):
        tc = EcucContainerValue(short_name=task_name, definition_ref="/MICROSAR/Os/OsTask")
        tc.set_parameter_value("OsTaskPriority", prio, "/MICROSAR/Os/OsTask/OsTaskPriority")
        tc.set_parameter_value("OsTaskType", "BASIC", "/MICROSAR/Os/OsTask/OsTaskType")
        os_cfg.add_container(tc)
    os_cfg.add_container(EcucContainerValue(short_name="OsCore0", definition_ref="/MICROSAR/Os/OsCore"))
    os_cfg.add_container(EcucContainerValue(short_name="OsCore1", definition_ref="/MICROSAR/Os/OsCore"))
    os_cfg.add_container(EcucContainerValue(short_name="SystemApplication_OsCore0", definition_ref="/MICROSAR/Os/OsApplication"))
    os_cfg.add_container(EcucContainerValue(short_name="OsResource_Can", definition_ref="/MICROSAR/Os/OsResource"))
    os_cfg.add_container(EcucContainerValue(short_name="OsSpinlock_Com", definition_ref="/MICROSAR/Os/OsSpinlock"))

    com_cfg = EcucModuleConfiguration(short_name="Com", definition_ref="/MICROSAR/Com")
    dcm_cfg = EcucModuleConfiguration(short_name="Dcm", definition_ref="/MICROSAR/Dcm")

    def _mgr(cfg):
        return SimpleNamespace(
            module_def=EcucModuleDef(short_name=cfg.short_name, definition_ref=cfg.definition_ref),
            configuration=cfg,
        )

    project = SimpleNamespace(
        name="SynthRteProj",
        path=proj_dir / "SynthRteProj.dpa",
        directories=ProjectDirectories.default_v8(),
        module_managers={
            "Rte": _mgr(rte_cfg),
            "Os": _mgr(os_cfg),
            "Com": _mgr(com_cfg),
            "Dcm": _mgr(dcm_cfg),  # loaded but initially unregistered in Rte!
        },
        packages={},
        is_modified=False,
    )
    return project, proj_dir, rte_cfg


def test_ib_parser_extracts_timing_events_and_periods(tmp_path):
    sys_dir = tmp_path / "system" / "InternalBehavior"
    _write_ib_arxml(sys_dir / "Com_ib_bswmd.arxml", _com_ib_xml())

    idx = BswIbIndex.load_directory(tmp_path / "system")
    rx_path = "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/Com_MainFunctionRxTimingEvent0"
    assert rx_path in idx.events_by_path
    ev = idx.events_by_path[rx_path]
    assert ev.short_name == "Com_MainFunctionRxTimingEvent0"
    assert ev.event_kind == "BSW-TIMING-EVENT"
    assert ev.entity_name == "Com_MainFunctionRx"
    assert ev.period_sec == pytest.approx(0.01)


def test_rte_generator_preview_is_non_mutating_and_detects_statuses(tmp_path):
    project, proj_dir, _ = _build_synthetic_project(tmp_path)
    out_dir = proj_dir / "gen"

    gen = RteSchMGenerator(project)
    files1, rep1 = gen.preview(out_dir, flat=False)
    assert not out_dir.exists()
    assert rep1.skipped_modules == [("CanNm", "模块尚未加载到当前工程")]
    by_name1 = {f.filename: f for f in files1}
    assert by_name1["Rte.h"].status == "new"
    assert by_name1["SchM_Com.h"].status == "new"
    assert by_name1["Rte_Type.h"].status == "new" and by_name1["Rte_Type.h"].source == "stub"

    # Generate on disk, then modify Rte_UserTypes.h and add project overlay
    gen.generate(out_dir, flat=False)
    (out_dir / "Rte" / "include" / "Rte_UserTypes.h").write_text("/* user custom */\n", encoding="utf-8")
    overlay_dir = proj_dir / "templates"
    (overlay_dir / "Rte" / "include").mkdir(parents=True)
    (overlay_dir / "Rte" / "include" / "Rte_Cfg.h").write_text("/* custom overlay */\n", encoding="utf-8")

    files2, _ = gen.preview(out_dir, flat=False, overlay_root=overlay_dir)
    by_name2 = {f.filename: f for f in files2}
    assert by_name2["Rte.h"].status == "unchanged"
    assert by_name2["Rte_UserTypes.h"].status == "preserved"
    assert "user custom" in by_name2["Rte_UserTypes.h"].content
    assert by_name2["Rte_Cfg.h"].status == "overlay"
    assert by_name2["Rte_Cfg.h"].source == "overlay"


def test_workbench_service_tab1_instances_add_remove_and_sync(tmp_path):
    project, proj_dir, rte_cfg = _build_synthetic_project(tmp_path)
    svc = RteWorkbenchService(project)

    rows = {r.module_name: r for r in svc.list_bsw_instance_rows()}
    assert rows["Com"].status == "active"
    assert rows["Com"].ea_configured_count == 1
    assert rows["Com"].ea_ib_count == 2
    assert rows["CanNm"].status == "unloaded"
    assert rows["Dcm"].status == "unregistered"

    # Add Dcm & verify refs + EA population
    dcm_inst = svc.add_bsw_instance("Dcm", populate_exclusive_areas=True)
    assert dcm_inst.reference_values["RteBswModuleConfigurationRef"].value_ref == "/ActiveEcuC/Dcm"
    assert dcm_inst.reference_values["RteBswImplementationRef"].value_ref == "/MICROSAR/Dcm_Impl"
    assert len(dcm_inst.sub_containers) == 1
    assert dcm_inst.sub_containers[0].short_name == "DCM_EXCLUSIVE_AREA_0"

    # Remove unloaded CanNm and sync missing EAs for Com
    summary = svc.sync_bsw_instances(add_missing_modules=False, sync_exclusive_areas=True, remove_unloaded=True)
    assert summary.removed_instances == 1
    assert summary.added_exclusive_areas == 1

    rows2 = {r.module_name: r for r in svc.list_bsw_instance_rows()}
    assert "CanNm" not in rows2
    assert rows2["Com"].ea_configured_count == 2
    assert rows2["Dcm"].status == "active"

    # ARXML serialization preserves reference metadata cleanly
    out_xml = proj_dir / "Rte_saved.arxml"
    EcucValueSerializer().serialize_to_file(rte_cfg, out_xml)
    xml = out_xml.read_text(encoding="utf-8")
    assert "/ActiveEcuC/Dcm" in xml
    assert 'DEST="BSW-IMPLEMENTATION"' in xml
    assert "DCM_EXCLUSIVE_AREA_0" in xml


def test_workbench_service_tab2_exclusive_areas_and_batch(tmp_path):
    project, proj_dir, _ = _build_synthetic_project(tmp_path)
    svc = RteWorkbenchService(project)

    assert svc.list_os_resources() == ["OsResource_Can"]
    assert svc.list_os_spinlocks() == ["OsSpinlock_Com"]

    # Missing OsResource causes validation_error
    svc.update_exclusive_area("Com", "COM_EXCLUSIVE_AREA_TX", mechanism="OS_RESOURCE", os_resource=None)
    ea_rows = {r.ea_name: r for r in svc.list_exclusive_area_rows()}
    assert ea_rows["COM_EXCLUSIVE_AREA_TX"].validation_error is not None

    # Preview reflects error while still returning model preview
    files_err, rep_err = svc.preview_generation(output_dir=proj_dir / "gen", flat=False)
    assert not rep_err.ok
    assert any("OS_RESOURCE" in e for e in rep_err.errors)
    assert len(files_err) > 0

    # Fix with OsResource_Can -> preview generates GetResource/ReleaseResource
    svc.update_exclusive_area(
        "Com",
        "COM_EXCLUSIVE_AREA_TX",
        mechanism="OS_RESOURCE",
        os_resource="OsResource_Can",
        generate_function=False,
    )
    files_ok, rep_ok = svc.preview_generation(output_dir=proj_dir / "gen", flat=False)
    assert rep_ok.ok
    schm_com = next(f.content for f in files_ok if f.filename == "SchM_Com.h")
    assert "GetResource(OsResource_Can)" in schm_com
    assert "ReleaseResource(OsResource_Can)" in schm_com

    # Batch set to OS_SPINLOCK
    changed = svc.batch_set_mechanism([("Com", "COM_EXCLUSIVE_AREA_RX")], "OS_SPINLOCK", os_spinlock="OsSpinlock_Com")
    assert changed == 1
    files_spin, _ = svc.preview_generation(output_dir=proj_dir / "gen", flat=False)
    schm_com2 = next(f.content for f in files_spin if f.filename == "SchM_Com.h")
    assert "GetSpinlock(OsSpinlock_Com)" in schm_com2


def test_workbench_service_tab3_task_mapping_and_ordering(tmp_path):
    project, _, _ = _build_synthetic_project(tmp_path)
    svc = RteWorkbenchService(project)

    tasks = {t.name: t for t in svc.list_os_tasks()}
    assert "OsTask_10ms" in tasks and not tasks["OsTask_10ms"].missing_in_os
    assert tasks["OsTask_10ms"].priority == 10

    mapped, unmapped = svc.list_task_mappings(include_swc=True)
    # Initially SWC event is mapped in OsTask_10ms, and Com RX/TX are IB unmapped
    assert len(mapped["OsTask_10ms"]) == 1
    assert mapped["OsTask_10ms"][0].is_swc is True
    assert [u.event_name for u in unmapped] == [
        "Com_MainFunctionRxTimingEvent0",
        "Com_MainFunctionTxTimingEvent0",
    ]

    # Map both Com events to OsTask_10ms cleanly
    rx = next(u for u in unmapped if u.event_name == "Com_MainFunctionRxTimingEvent0")
    tx = next(u for u in unmapped if u.event_name == "Com_MainFunctionTxTimingEvent0")
    svc.map_event_to_task("Com", rx.event_name, "OsTask_10ms", event_ref=rx.event_ref, event_kind=rx.event_kind)
    svc.map_event_to_task("Com", tx.event_name, "OsTask_10ms", event_ref=tx.event_ref, event_kind=tx.event_kind)

    mapped2, unmapped2 = svc.list_task_mappings(include_swc=True)
    assert unmapped2 == []
    bsw_in_10ms = [r for r in mapped2["OsTask_10ms"] if not r.is_swc]
    assert [r.event_name for r in bsw_in_10ms] == [
        "Com_MainFunctionRxTimingEvent0",
        "Com_MainFunctionTxTimingEvent0",
    ]
    assert [r.position for r in bsw_in_10ms] == [2, 3]

    # Move TX up past RX -> positions swap while SWC pos stays 1
    assert svc.move_event_in_task("OsTask_10ms", "Com", tx.mapping_name, -1) is True
    mapped3, _ = svc.list_task_mappings(include_swc=True)
    bsw_in_10ms3 = [r for r in mapped3["OsTask_10ms"] if not r.is_swc]
    assert [r.event_name for r in bsw_in_10ms3] == [
        "Com_MainFunctionTxTimingEvent0",
        "Com_MainFunctionRxTimingEvent0",
    ]
    swc_in_10ms = [r for r in mapped3["OsTask_10ms"] if r.is_swc]
    assert swc_in_10ms[0].position == 1

    # Unmap RX -> returns to unmapped pool with ECUC container retained
    assert svc.unmap_event("Com", rx.mapping_name) is True
    _, unmapped4 = svc.list_task_mappings(include_swc=True)
    assert len(unmapped4) == 1
    assert unmapped4[0].event_name == "Com_MainFunctionRxTimingEvent0"
    assert unmapped4[0].has_ecuc_container is True


def test_workbench_service_tab4_settings_preview_and_run_generation(tmp_path):
    project, proj_dir, _ = _build_synthetic_project(tmp_path)
    svc = RteWorkbenchService(project)

    s0 = svc.read_rte_generation_settings()
    assert s0.enable_multi_core is False
    assert s0.dev_error_detect is False

    svc.update_rte_generation_settings(
        RteGenerationSettings(
            enable_multi_core=True,
            enable_memory_protection=True,
            dev_error_detect=True,
            generation_mode="VENDOR_MODE",
            optimization_mode="MEMORY",
        )
    )
    files, _ = svc.preview_generation(output_dir=proj_dir / "gen", flat=False)
    rte_h = next(f.content for f in files if f.filename == "Rte.h")
    rte_main_h = next(f.content for f in files if f.filename == "Rte_Main.h")
    assert svc.read_rte_generation_settings().enable_multi_core is True
    assert svc.read_rte_generation_settings().dev_error_detect is True
    assert "Rte_CallDetReportError" in rte_h
    assert "SchM_StartTimingCore0" in rte_main_h
    assert "SchM_StartTimingCore1" in rte_main_h
    assert "Rte_InitMemory_SystemApplication_OsCore0" in rte_main_h

    ok, rep, detail = svc.run_generation(output_dir=proj_dir / "gen", flat=False)
    assert ok is True
    assert rep.ok
    assert "CanNm" in detail
    assert (proj_dir / "gen" / "Rte" / "include" / "Rte.h").is_file()
    assert (proj_dir / "gen" / "Rte" / "include" / "SchM_Com.h").is_file()


@pytest.mark.skipif(not REAL_START_APP.is_dir(), reason="StartApplication1 fixture absent")
def test_workbench_service_real_startapplication_readonly(tmp_path):
    ws = WorkspaceManager()
    project, _ = ws.load_project(REAL_START_APP / "StartApplication1.dpa")
    svc = RteWorkbenchService(project)

    inst_rows = svc.list_bsw_instance_rows()
    by_mod = {r.module_name: r for r in inst_rows}
    by_api = {r.api_name: r for r in inst_rows}
    assert by_mod["CanNm"].status == "unloaded"
    assert by_api["CanTrcv_30_Tle9255"].status == "active"

    mapped, unmapped = svc.list_task_mappings(include_swc=True)
    assert "OsTask_10ms_Core0" in mapped
    com_rx_rows = [
        r
        for r in mapped["OsTask_10ms_Core0"]
        if (not r.is_swc) and r.module_name == "Com" and "MainFunctionRx" in r.event_name
    ]
    assert com_rx_rows
    assert com_rx_rows[0].period_sec == pytest.approx(0.01)

    preview_files, _ = svc.preview_generation(output_dir=tmp_path / "gen_out", flat=False)
    names = {f.filename for f in preview_files}
    assert {"Rte.h", "Rte_Cfg.h", "SchM_Com.h", "SchM_CanTrcv_30_Tle9255.h"}.issubset(names)


def test_ib_index_caching_reused_across_operations(tmp_path, monkeypatch):
    project, proj_dir, _ = _build_synthetic_project(tmp_path)
    load_calls = 0
    orig_load = BswIbIndex.load_directory

    def _counting_load(system_dir: Path):
        nonlocal load_calls
        load_calls += 1
        return orig_load(system_dir)

    monkeypatch.setattr(BswIbIndex, "load_directory", staticmethod(_counting_load))
    svc = RteWorkbenchService(project)

    svc.list_bsw_instance_rows()
    svc.update_exclusive_area("Com", "COM_EXCLUSIVE_AREA_TX", mechanism="NONE")
    svc.list_bsw_instance_rows()
    svc.preview_generation(output_dir=proj_dir / "gen", flat=False)
    assert load_calls == 1

    svc.reload_ib_index()
    svc.list_bsw_instance_rows()
    assert load_calls == 2


def test_pre_lock_enforced_and_reported(tmp_path):
    from autosar_configurator.core.config_manager import PreLockedError

    project, _, rte_cfg = _build_synthetic_project(tmp_path)

    def _guard(instance, name=None):
        sn = getattr(instance, "short_name", "")
        if sn in ("COM_EXCLUSIVE_AREA_RX", "CanNm"):
            raise PreLockedError(f"P:/Rte/Rte/{sn}/{name or ''}")

    project.module_managers["Rte"].check_editable = _guard
    svc = RteWorkbenchService(project)

    with pytest.raises(PreLockedError):
        svc.update_exclusive_area("Com", "COM_EXCLUSIVE_AREA_RX", mechanism="NONE")
    ea_rx = next(r for r in svc.list_exclusive_area_rows() if r.ea_name == "COM_EXCLUSIVE_AREA_RX")
    assert ea_rx.mechanism == "ALL_INTERRUPT_BLOCKING"

    with pytest.raises(PreLockedError):
        svc.remove_bsw_instance("CanNm")
    assert svc._find_bsw_instance("CanNm") is not None

    summary = svc.sync_bsw_instances(
        add_missing_modules=False,
        sync_exclusive_areas=True,
        remove_unloaded=True,
    )
    assert summary.removed_instances == 0
    assert summary.added_exclusive_areas == 1  # COM_EXCLUSIVE_AREA_TX still created
    assert len(summary.skipped_locked) == 1
    assert rte_cfg.is_modified is True


def test_eb_tresos_prefix_and_snapshot_roundtrip_fidelity(tmp_path):
    from autosar_configurator.core.config_manager import ProjectType
    from autosar_configurator.core.model.configuration_model import EcucParameterValue

    project, _, rte_cfg = _build_synthetic_project(tmp_path)
    project.project_type = ProjectType.EB_TRESOS
    com_inst = next(c for c in rte_cfg.containers if c.short_name == "Com")
    com_inst.uuid = "keep-uuid-1234"
    com_inst.unknown_parameters["LegacyFlag"] = EcucParameterValue("/MICROSAR/Rte/LegacyFlag", "X")
    rte_cfg.is_modified = False

    resolve_calls = []
    reverse_calls = []
    project.resolve_all_references = lambda force=False: resolve_calls.append(force) or (0, 0)
    project.build_reverse_reference_index = lambda: reverse_calls.append(True) or 0

    svc = RteWorkbenchService(project)
    snap = svc.capture_snapshot()

    dcm_inst = svc.add_bsw_instance("Dcm")
    assert dcm_inst.reference_values["RteBswModuleConfigurationRef"].value_ref == "/Dcm/Dcm"
    svc.remove_bsw_instance("CanNm")
    assert rte_cfg.is_modified is True

    svc.restore_snapshot(snap)
    assert rte_cfg.is_modified is False
    assert svc._find_bsw_instance("Dcm") is None
    assert svc._find_bsw_instance("CanNm") is not None
    restored_com = svc._find_bsw_instance("Com")
    assert restored_com.uuid == "keep-uuid-1234"
    assert restored_com.unknown_parameters["LegacyFlag"].value == "X"
    assert resolve_calls == [True]
    assert reverse_calls == [True]


def test_p1_batch_map_events_period_recommendation_and_preview_diff(tmp_path):
    from autosar_configurator.core.config_manager import PreLockedError
    from autosar_configurator.core.model.configuration_model import EcucContainerValue
    from autosar_configurator.generator.rte import OsTaskInfo, compute_preview_diff

    project, proj_dir, _ = _build_synthetic_project(tmp_path)
    svc = RteWorkbenchService(project)

    _, unmapped = svc.list_task_mappings(include_swc=False)
    com_rx = next(r for r in unmapped if r.module_name == "Com" and r.period_sec == pytest.approx(0.01))
    com_tx = next(r for r in unmapped if r.module_name == "Com" and r.period_sec == pytest.approx(0.02))

    # Empty selection & single-period recommendations
    assert svc.recommend_task_for_events([])[0] is None
    rec_10, msg_10 = svc.recommend_task_for_events([com_rx])
    assert rec_10 == "OsTask_10ms"
    assert "10 ms" in msg_10

    rec_20, msg_20 = svc.recommend_task_for_events([com_tx])
    assert rec_20 == "OsTask_20ms"
    assert "20 ms" in msg_20

    # Mixed periods warn user instead of recommending a single task
    rec_mix, msg_mix = svc.recommend_task_for_events([com_rx, com_tx])
    assert rec_mix is None
    assert "多种周期" in msg_mix

    # Fallback recommendation via existing same-period mapping when task name has no period token
    custom_tasks = [OsTaskInfo(name="OsTask_Fast"), OsTaskInfo(name="OsTask_Slow")]
    fallback_rec, fallback_msg = svc.recommend_task_for_events(
        [com_rx],
        tasks=custom_tasks,
        mapped_by_task={"OsTask_Fast": [com_rx]},
    )
    assert fallback_rec == "OsTask_Fast"
    assert "同周期" in fallback_msg

    # Batch mapping respects PreLockedError and skips locked entries cleanly
    def _lock_tx(instance, name=None):
        if getattr(instance, "short_name", "") == "Com_MainFunctionTxTimingEvent0":
            raise PreLockedError("P:/Rte/Rte/Com/Com_MainFunctionTxTimingEvent0")

    project.module_managers["Rte"].check_editable = _lock_tx
    mapped_cnt, skipped = svc.batch_map_events_to_task([com_rx, com_tx], "OsTask_10ms")
    assert mapped_cnt == 1
    assert len(skipped) == 1

    # Restore editable check and batch-map remaining event cleanly
    project.module_managers["Rte"].check_editable = lambda *_a, **_kw: None
    svc2 = RteWorkbenchService(project)
    _, unmapped2 = svc2.list_task_mappings(include_swc=False)
    com_tx_rem = next(r for r in unmapped2 if r.event_name == "Com_MainFunctionTxTimingEvent0")
    mapped_cnt2, skipped2 = svc2.batch_map_events_to_task([com_tx_rem], "OsTask_20ms")
    assert mapped_cnt2 == 1
    assert skipped2 == []

    # Preview diff for new -> unchanged / preserved -> updated without touching disk on preview
    gen_out = proj_dir / "gen"
    previews_new, _ = svc2.preview_generation(output_dir=gen_out, flat=False)
    schm_new = next(p for p in previews_new if p.filename == "SchM_Com.h")
    assert schm_new.status == "new"
    diff_new = compute_preview_diff(schm_new)
    assert "--- /dev/null" in diff_new
    assert "+++ generated/SchM_Com.h" in diff_new
    assert "+#ifndef SCHM_COM_H" in diff_new
    assert not schm_new.target_path.exists()

    ok, _, _ = svc2.run_generation(output_dir=gen_out, flat=False)
    assert ok is True

    previews_clean, _ = svc2.preview_generation(output_dir=gen_out, flat=False)
    schm_unchanged = next(p for p in previews_clean if p.filename == "SchM_Com.h")
    assert schm_unchanged.status == "unchanged"
    assert "无差异" in compute_preview_diff(schm_unchanged)
    rte_type_stub = next(p for p in previews_clean if p.filename == "Rte_Type.h")
    assert rte_type_stub.status == "preserved"
    assert "保留原文件" in compute_preview_diff(rte_type_stub)

    # Update RX EA mechanism and verify unified diff reflects the exact line change
    svc2.update_exclusive_area(
        "Com",
        "COM_EXCLUSIVE_AREA_RX",
        mechanism="OS_RESOURCE",
        os_resource="OsResource_Can",
    )
    previews_upd, _ = svc2.preview_generation(output_dir=gen_out, flat=False)
    schm_upd = next(p for p in previews_upd if p.filename == "SchM_Com.h")
    assert schm_upd.status == "updated"
    disk_before = schm_upd.target_path.read_text(encoding="utf-8")
    diff_upd = compute_preview_diff(schm_upd)
    assert "--- disk/SchM_Com.h" in diff_upd
    assert "+++ generated/SchM_Com.h" in diff_upd
    assert "GetResource(OsResource_Can)" in diff_upd
    assert schm_upd.target_path.read_text(encoding="utf-8") == disk_before


def test_p2_collect_diagnostics_stage3_os_interaction_and_validation_rule(tmp_path):
    from autosar_configurator.core.rules import RteSchmValidationRule
    from autosar_configurator.core.validation_engine import ValidationEngine, ValidationSeverity

    project, _, rte_cfg = _build_synthetic_project(tmp_path)
    svc = RteWorkbenchService(project)

    base_diags = svc.collect_diagnostics()
    base_codes = {d.code for d in base_diags}
    assert {"UNLOADED_INSTANCE", "EA_UNCONFIGURED", "UNMAPPED_EVENT"}.issubset(base_codes)
    assert any(d.workbench_tab == 0 for d in base_diags if d.code == "UNLOADED_INSTANCE")
    assert any(d.workbench_tab == 1 for d in base_diags if d.code == "EA_UNCONFIGURED")
    assert any(d.workbench_tab == 2 for d in base_diags if d.code == "UNMAPPED_EVENT")

    # Add EXTENDED task, register Dcm, map Dcm event without OsEventRef, and mix Com periods on OsTask_10ms
    os_cfg = project.module_managers["Os"].configuration
    ext_task = EcucContainerValue(short_name="OsTask_Ext", definition_ref="/MICROSAR/Os/OsTask")
    ext_task.set_parameter_value("OsTaskPriority", 30, "/MICROSAR/Os/OsTask/OsTaskPriority")
    ext_task.set_parameter_value("OsTaskType", "EXTENDED", "/MICROSAR/Os/OsTask/OsTaskType")
    os_cfg.add_container(ext_task)

    svc.add_bsw_instance("Dcm", populate_exclusive_areas=True)
    _, unmapped = svc.list_task_mappings(include_swc=False)
    for ev in unmapped:
        if ev.module_name == "Dcm":
            svc.map_event_to_task(
                ev.instance_name,
                ev.event_name,
                "OsTask_Ext",
                event_ref=ev.event_ref,
                event_kind=ev.event_kind,
            )
        elif ev.module_name == "Com":
            svc.map_event_to_task(
                ev.instance_name,
                ev.event_name,
                "OsTask_10ms",
                event_ref=ev.event_ref,
                event_kind=ev.event_kind,
            )

    # Add RteOsInteraction with missing source and dangling/mismatched tick activation
    os_inter = EcucContainerValue(short_name="RteOsInteraction", definition_ref="/MICROSAR/Rte/RteOsInteraction")
    act_missing = EcucContainerValue(
        short_name="Act_NoSource",
        definition_ref="/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation",
    )
    act_missing.set_reference_value(
        "RteActivationOsTaskRef",
        "/ActiveEcuC/Os/OsTask_20ms",
        "/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation/RteActivationOsTaskRef",
    )
    os_inter.add_sub_container(act_missing)

    act_bad = EcucContainerValue(
        short_name="Act_BadTickAndAlarm",
        definition_ref="/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation",
    )
    act_bad.set_reference_value(
        "RteActivationOsTaskRef",
        "/ActiveEcuC/Os/OsTask_10ms",
        "/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation/RteActivationOsTaskRef",
    )
    act_bad.set_reference_value(
        "RteActivationOsAlarmRef",
        "/ActiveEcuC/Os/NonExistentAlarm",
        "/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation/RteActivationOsAlarmRef",
    )
    act_bad.set_parameter_value(
        "RteExpectedTickDuration",
        0.03,
        "/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation/RteExpectedTickDuration",
    )
    os_inter.add_sub_container(act_bad)
    rte_cfg.add_container(os_inter)

    # Create EA error (OS_RESOURCE without resource ref)
    svc.update_exclusive_area("Com", "COM_EXCLUSIVE_AREA_RX", mechanism="OS_RESOURCE")

    diags = svc.collect_diagnostics()
    codes = {d.code for d in diags}
    assert {
        "UNLOADED_INSTANCE",
        "EA_INVALID_CONFIG",
        "EA_UNCONFIGURED",
        "MIXED_TASK_PERIOD",
        "EXTENDED_TASK_MISSING_EVENT",
        "TASK_MISSING_ACTIVATION",
        "ACTIVATION_MISSING_SOURCE",
        "DANGLING_OS_ACTIVATION",
        "ACTIVATION_PERIOD_MISMATCH",
    }.issubset(codes)

    # Registered in ValidationEngine.register_default_rules() for Rte only
    rte_mgr = project.module_managers["Rte"]
    engine = ValidationEngine(rte_mgr.module_def, rte_mgr.configuration, project_context=project)
    engine.register_default_rules()
    val_res = engine.validate()
    rte_msgs = [m for m in val_res.messages if m.rule_name == "RteSchmRule"]
    assert rte_msgs
    assert any(m.severity == ValidationSeverity.ERROR for m in rte_msgs)
    assert all("workbench_tab=" in (m.details or "") and m.suggested_fix for m in rte_msgs)

    # Single-module mode (no project_context) and non-Rte module produce 0 RteSchmRule messages
    rule = RteSchmValidationRule()
    assert rule.validate(rte_mgr.module_def, rte_mgr.configuration, project_context=None).messages == []
    com_mgr = project.module_managers["Com"]
    assert rule.validate(com_mgr.module_def, com_mgr.configuration, project_context=project).messages == []


@pytest.mark.skipif(not REAL_START_APP.is_dir(), reason="StartApplication1 fixture absent")
def test_p2_real_startapplication_validation_rule():
    from autosar_configurator.core.rules import RteSchmValidationRule

    ws = WorkspaceManager()
    project, _ = ws.load_project(REAL_START_APP / "StartApplication1.dpa")
    rte_mgr = project.module_managers["Rte"]
    res = RteSchmValidationRule().validate(rte_mgr.module_def, rte_mgr.configuration, project_context=project)
    assert res.error_count == 0
    diags = RteWorkbenchService(project).collect_diagnostics()
    assert not any(
        d.code == "TASK_MISSING_ACTIVATION" and "OsTask_10ms_Core0" in d.message
        for d in diags
    )
