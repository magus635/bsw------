"""Tests for Phase 1 model-driven RTE/SchM header generator."""

import json
import re
import shutil
import subprocess
from pathlib import Path
from types import SimpleNamespace

import pytest

from autosar_configurator.core import project_paths
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
)
from autosar_configurator.core.model.definition_model import EcucModuleDef
from autosar_configurator.core.packages.manifest import load_manifest
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.rte import RteModelExtractor, RteSchMGenerator


def _make_cfg(short_name: str, def_ref: str | None = None) -> EcucModuleConfiguration:
    return EcucModuleConfiguration(short_name=short_name, definition_ref=def_ref or f"/MICROSAR/{short_name}")


def _write_ib_file(path: Path, xml_body: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(
        '<?xml version="1.0" encoding="UTF-8"?>\n'
        '<AUTOSAR xmlns="http://autosar.org/schema/r4.0">\n'
        "  <AR-PACKAGES>\n"
        f"{xml_body}\n"
        "  </AR-PACKAGES>\n"
        "</AUTOSAR>\n",
        encoding="utf-8",
    )


def _write_pkg(root: Path, dir_name: str, module: str, impl_meta: dict) -> ModulePackage:
    pkg_dir = root / "modules" / "davinci" / dir_name
    (pkg_dir / "config").mkdir(parents=True, exist_ok=True)
    (pkg_dir / "config" / f"{module}.arxml").write_text("<AUTOSAR/>", encoding="utf-8")
    manifest_data = {
        "schema": 1,
        "module": module,
        "definition": f"/MICROSAR/{module}",
        "files": [f"config/{module}.arxml"],
        "origin": {
            "source": "davinci",
            "implementation": impl_meta,
            "sw_version": impl_meta.get("sw_version", "1.0.0"),
        },
        "version": impl_meta.get("sw_version", "1.0.0"),
        "implementation_path": impl_meta.get("ar_path"),
    }
    (pkg_dir / "module.json").write_text(json.dumps(manifest_data, indent=2), encoding="utf-8")
    return ModulePackage(pkg_dir, load_manifest(pkg_dir))


def _make_mgr(mod_cfg: EcucModuleConfiguration) -> SimpleNamespace:
    return SimpleNamespace(
        module_def=EcucModuleDef(short_name=mod_cfg.short_name, definition_ref=mod_cfg.definition_ref),
        configuration=mod_cfg,
    )


def _add_bsw_instance(
    rte_cfg: EcucModuleConfiguration,
    name: str,
    *,
    impl_ref: str,
    cfg_ref: str,
    ea_specs: list[tuple[str, str, str | None, str | None, str | None, bool]] | None = None,
) -> EcucContainerValue:
    inst = EcucContainerValue(short_name=name, definition_ref="/MICROSAR/Rte/RteBswModuleInstance")
    inst.set_reference_value("RteBswImplementationRef", impl_ref, "/MICROSAR/Rte/RteBswModuleInstance/RteBswImplementationRef")
    inst.set_reference_value("RteBswModuleConfigurationRef", cfg_ref, "/MICROSAR/Rte/RteBswModuleInstance/RteBswModuleConfigurationRef")
    for ea_name, mech, ea_ref, res_ref, spin_ref, gen_fn in ea_specs or []:
        sub = EcucContainerValue(
            short_name=ea_name,
            definition_ref="/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl",
            parent=inst,
        )
        sub.set_parameter_value(
            "RteExclusiveAreaImplMechanism",
            mech,
            "/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl/RteExclusiveAreaImplMechanism",
        )
        if gen_fn:
            sub.set_parameter_value(
                "RteExclusiveAreaGenerateFunction",
                True,
                "/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl/RteExclusiveAreaGenerateFunction",
            )
        if ea_ref:
            sub.set_reference_value(
                "RteBswExclusiveAreaRef",
                ea_ref,
                "/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl/RteBswExclusiveAreaRef",
            )
        if res_ref:
            sub.set_reference_value(
                "RteBswExclusiveAreaOsResourceRef",
                res_ref,
                "/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl/RteBswExclusiveAreaOsResourceRef",
            )
        if spin_ref:
            sub.set_reference_value(
                "RteBswExclusiveAreaOsSpinlockRef",
                spin_ref,
                "/MICROSAR/Rte/RteBswModuleInstance/RteBswExclusiveAreaImpl/RteBswExclusiveAreaOsSpinlockRef",
            )
        inst.add_sub_container(sub)
    rte_cfg.containers.append(inst)
    return inst


def _build_synthetic_project(tmp_path: Path, *, multi_core: bool = True, disable_init_mem: bool = False):
    proj_root = tmp_path / "DemoProj"
    proj_root.mkdir(parents=True)
    dpa = proj_root / "DemoProj.dpa"
    dpa.write_text("{}", encoding="utf-8")

    rte_pkg = _write_pkg(
        proj_root,
        "Rte",
        "Rte",
        {
            "ar_path": "/MICROSAR/Rte_Impl",
            "sw_version": "4.38.02",
            "ar_release_version": "4.03.01",
            "vendor_id": "30",
        },
    )
    com_pkg = _write_pkg(
        proj_root,
        "Com",
        "Com",
        {
            "ar_path": "/MICROSAR/Com_Impl",
            "sw_version": "26.02.02",
            "ar_release_version": "4.00.03",
            "vendor_id": "30",
        },
    )
    canif_pkg = _write_pkg(
        proj_root,
        "CanIf",
        "CanIf",
        {
            "ar_path": "/MICROSAR/CanIf_Impl",
            "sw_version": "12.00.00",
            "ar_release_version": "4.00.03",
            "vendor_id": "30",
        },
    )
    trcv_pkg = _write_pkg(
        proj_root,
        "CanTrcv_Tle9255",
        "CanTrcv",
        {
            "ar_path": "/MICROSAR/CanTrcv_Tle9255/CanTrcv_Impl",
            "sw_version": "1.01.00",
            "ar_release_version": "4.00.03",
            "vendor_id": "30",
            "vendor_api_infix": "Tle9255",
        },
    )
    bswm_pkg = _write_pkg(
        proj_root,
        "BswM",
        "BswM",
        {
            "ar_path": "/MICROSAR/BswM_Impl",
            "sw_version": "19.02.00",
            "ar_release_version": "4.00.03",
            "vendor_id": "30",
            "required_artifacts": [{"short_label": "Custom_BswM_MemMap.h", "category": "MEMMAP"}],
        },
    )
    det_pkg = _write_pkg(
        proj_root,
        "Det",
        "Det",
        {
            "ar_path": "/MICROSAR/Det_Impl",
            "sw_version": "14.00.01",
            "ar_release_version": "4.05.00",
            "vendor_id": "30",
        },
    )

    _write_ib_file(
        proj_root / "system" / "InternalBehavior" / "Com_ib_bswmd.arxml",
        """
    <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME>
      <ELEMENTS>
        <BSW-IMPLEMENTATION>
          <SHORT-NAME>Com_Impl</SHORT-NAME>
          <VENDOR-ID>30</VENDOR-ID>
          <AR-RELEASE-VERSION>4.00.03</AR-RELEASE-VERSION>
          <RESOURCE-CONSUMPTION><MEMORY-SECTIONS><MEMORY-SECTION><SHORT-NAME>CODE</SHORT-NAME></MEMORY-SECTION></MEMORY-SECTIONS></RESOURCE-CONSUMPTION>
        </BSW-IMPLEMENTATION>
      </ELEMENTS>
      <AR-PACKAGES>
        <AR-PACKAGE><SHORT-NAME>Com_ib_bswmd</SHORT-NAME><AR-PACKAGES>
          <AR-PACKAGE><SHORT-NAME>BswModuleDescriptions</SHORT-NAME><ELEMENTS>
            <BSW-MODULE-DESCRIPTION>
              <SHORT-NAME>Com</SHORT-NAME>
              <INTERNAL-BEHAVIORS>
                <BSW-INTERNAL-BEHAVIOR>
                  <SHORT-NAME>ComBehavior</SHORT-NAME>
                  <EXCLUSIVE-AREAS>
                    <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_TX</SHORT-NAME></EXCLUSIVE-AREA>
                    <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_RX</SHORT-NAME></EXCLUSIVE-AREA>
                    <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_BOTH</SHORT-NAME></EXCLUSIVE-AREA>
                    <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_RES</SHORT-NAME></EXCLUSIVE-AREA>
                    <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_SPIN</SHORT-NAME></EXCLUSIVE-AREA>
                    <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_COOP</SHORT-NAME></EXCLUSIVE-AREA>
                    <EXCLUSIVE-AREA><SHORT-NAME>COM_EXCLUSIVE_AREA_CUSTOM</SHORT-NAME></EXCLUSIVE-AREA>
                  </EXCLUSIVE-AREAS>
                  <ENTITYS>
                    <BSW-SCHEDULABLE-ENTITY>
                      <SHORT-NAME>Com_MainFunctionTx_Entity</SHORT-NAME>
                      <IMPLEMENTED-ENTRY-REF DEST="BSW-MODULE-ENTRY">/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com_MainFunctionTx_ComMainFunctionTx</IMPLEMENTED-ENTRY-REF>
                    </BSW-SCHEDULABLE-ENTITY>
                    <BSW-SCHEDULABLE-ENTITY>
                      <SHORT-NAME>Com_MainFunctionRx_Entity</SHORT-NAME>
                      <IMPLEMENTED-ENTRY-REF DEST="BSW-MODULE-ENTRY">/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com_MainFunctionRx_ComMainFunctionRx</IMPLEMENTED-ENTRY-REF>
                    </BSW-SCHEDULABLE-ENTITY>
                  </ENTITYS>
                </BSW-INTERNAL-BEHAVIOR>
              </INTERNAL-BEHAVIORS>
            </BSW-MODULE-DESCRIPTION>
            <BSW-MODULE-ENTRY><SHORT-NAME>Com_Virtual</SHORT-NAME></BSW-MODULE-ENTRY>
            <BSW-MODULE-ENTRY><SHORT-NAME>Com_MainFunctionTx_ComMainFunctionTx</SHORT-NAME></BSW-MODULE-ENTRY>
            <BSW-MODULE-ENTRY><SHORT-NAME>Com_MainFunctionRx_ComMainFunctionRx</SHORT-NAME></BSW-MODULE-ENTRY>
          </ELEMENTS></AR-PACKAGE>
        </AR-PACKAGES></AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>""",
    )

    _write_ib_file(
        proj_root / "system" / "InternalBehavior" / "CanTrcv_30_Tle9255_ib_bswmd.arxml",
        """
    <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
      <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255_ib_bswmd</SHORT-NAME><AR-PACKAGES>
        <AR-PACKAGE><SHORT-NAME>BswModuleDescriptions</SHORT-NAME><ELEMENTS>
          <BSW-MODULE-DESCRIPTION>
            <SHORT-NAME>CanTrcv</SHORT-NAME>
            <INTERNAL-BEHAVIORS>
              <BSW-INTERNAL-BEHAVIOR>
                <SHORT-NAME>CanTrcv_Tle9255_Behavior</SHORT-NAME>
                <EXCLUSIVE-AREAS>
                  <EXCLUSIVE-AREA><SHORT-NAME>CANTRCV_30_TLE9255_EXCLUSIVE_AREA_0</SHORT-NAME></EXCLUSIVE-AREA>
                </EXCLUSIVE-AREAS>
                <ENTITYS>
                  <BSW-SCHEDULABLE-ENTITY>
                    <SHORT-NAME>CanTrcv_30_Tle9255_MainFunction</SHORT-NAME>
                    <IMPLEMENTED-ENTRY-REF DEST="BSW-MODULE-ENTRY">/MICROSAR/CanTrcv_Tle9255_ib_bswmd/BswModuleDescriptions/CanTrcv_30_Tle9255_MainFunction</IMPLEMENTED-ENTRY-REF>
                  </BSW-SCHEDULABLE-ENTITY>
                </ENTITYS>
              </BSW-INTERNAL-BEHAVIOR>
            </INTERNAL-BEHAVIORS>
          </BSW-MODULE-DESCRIPTION>
          <BSW-MODULE-ENTRY><SHORT-NAME>CanTrcv_30_Tle9255_MainFunction</SHORT-NAME></BSW-MODULE-ENTRY>
        </ELEMENTS></AR-PACKAGE>
      </AR-PACKAGES></AR-PACKAGE>
    </AR-PACKAGES></AR-PACKAGE>""",
    )

    _write_ib_file(
        proj_root / "system" / "InternalBehavior" / "CanIf_ib_bswmd.arxml",
        """
    <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
      <AR-PACKAGE><SHORT-NAME>CanIf_ib_bswmd</SHORT-NAME><AR-PACKAGES>
        <AR-PACKAGE><SHORT-NAME>BswModuleDescriptions</SHORT-NAME><ELEMENTS>
          <BSW-MODULE-DESCRIPTION>
            <SHORT-NAME>CanIf</SHORT-NAME>
            <INTERNAL-BEHAVIORS>
              <BSW-INTERNAL-BEHAVIOR>
                <SHORT-NAME>CanIf_Behavior</SHORT-NAME>
                <EXCLUSIVE-AREAS>
                  <EXCLUSIVE-AREA><SHORT-NAME>CANIF_EXCLUSIVE_AREA_0</SHORT-NAME></EXCLUSIVE-AREA>
                </EXCLUSIVE-AREAS>
              </BSW-INTERNAL-BEHAVIOR>
            </INTERNAL-BEHAVIORS>
          </BSW-MODULE-DESCRIPTION>
          <BSW-MODULE-ENTRY><SHORT-NAME>CanIf_Virtual</SHORT-NAME></BSW-MODULE-ENTRY>
        </ELEMENTS></AR-PACKAGE>
      </AR-PACKAGES></AR-PACKAGE>
    </AR-PACKAGES></AR-PACKAGE>""",
    )

    _write_ib_file(
        proj_root / "system" / "InternalBehavior" / "BswM_ib_bswmd.arxml",
        """
    <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
      <AR-PACKAGE><SHORT-NAME>BswM_ib_bswmd</SHORT-NAME><AR-PACKAGES>
        <AR-PACKAGE><SHORT-NAME>BswModuleDescriptions</SHORT-NAME><ELEMENTS>
          <BSW-MODULE-DESCRIPTION>
            <SHORT-NAME>BswM</SHORT-NAME>
            <INTERNAL-BEHAVIORS>
              <BSW-INTERNAL-BEHAVIOR>
                <SHORT-NAME>BswMBehavior</SHORT-NAME>
                <EXCLUSIVE-AREAS>
                  <EXCLUSIVE-AREA><SHORT-NAME>BSWM_EXCLUSIVE_AREA_0</SHORT-NAME></EXCLUSIVE-AREA>
                </EXCLUSIVE-AREAS>
                <ENTITYS>
                  <BSW-SCHEDULABLE-ENTITY>
                    <SHORT-NAME>BswM_MainFunction</SHORT-NAME>
                    <IMPLEMENTED-ENTRY-REF DEST="BSW-MODULE-ENTRY">/MICROSAR/BswM_ib_bswmd/BswModuleDescriptions/BswM_MainFunction</IMPLEMENTED-ENTRY-REF>
                  </BSW-SCHEDULABLE-ENTITY>
                </ENTITYS>
              </BSW-INTERNAL-BEHAVIOR>
            </INTERNAL-BEHAVIORS>
          </BSW-MODULE-DESCRIPTION>
          <BSW-MODULE-ENTRY><SHORT-NAME>BswM_MainFunction</SHORT-NAME></BSW-MODULE-ENTRY>
        </ELEMENTS></AR-PACKAGE>
      </AR-PACKAGES></AR-PACKAGE>
    </AR-PACKAGES></AR-PACKAGE>""",
    )

    _write_ib_file(
        proj_root / "system" / "InternalBehavior" / "Det_ib_bswmd.arxml",
        """
    <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
      <AR-PACKAGE><SHORT-NAME>Det_ib_bswmd</SHORT-NAME><AR-PACKAGES>
        <AR-PACKAGE><SHORT-NAME>BswModuleDescriptions</SHORT-NAME><ELEMENTS>
          <BSW-MODULE-DESCRIPTION>
            <SHORT-NAME>Det</SHORT-NAME>
            <INTERNAL-BEHAVIORS>
              <BSW-INTERNAL-BEHAVIOR>
                <SHORT-NAME>DetBehavior</SHORT-NAME>
                <EXCLUSIVE-AREAS>
                  <EXCLUSIVE-AREA><SHORT-NAME>DET_EXCLUSIVE_AREA_0</SHORT-NAME></EXCLUSIVE-AREA>
                </EXCLUSIVE-AREAS>
              </BSW-INTERNAL-BEHAVIOR>
            </INTERNAL-BEHAVIORS>
          </BSW-MODULE-DESCRIPTION>
        </ELEMENTS></AR-PACKAGE>
      </AR-PACKAGES></AR-PACKAGE>
    </AR-PACKAGES></AR-PACKAGE>""",
    )

    rte_cfg = _make_cfg("Rte")
    gen_c = EcucContainerValue(short_name="RteGeneration", definition_ref="/MICROSAR/Rte/RteGeneration")
    gen_c.set_parameter_value("RteEnableMultiCore", multi_core, "/MICROSAR/Rte/RteGeneration/RteEnableMultiCore")
    gen_c.set_parameter_value("RteDisableRteInitMemory", disable_init_mem, "/MICROSAR/Rte/RteGeneration/RteDisableRteInitMemory")
    rte_cfg.containers.append(gen_c)

    # Self-instance Rte should never produce SchM_Rte.h
    _add_bsw_instance(rte_cfg, "Rte", impl_ref="/MICROSAR/Rte_Impl", cfg_ref="/ActiveEcuC/Rte")

    # Unloaded CanNm should be cleanly skipped with warning
    _add_bsw_instance(rte_cfg, "CanNm", impl_ref="/MICROSAR/CanNm_Impl", cfg_ref="/ActiveEcuC/CanNm")

    _add_bsw_instance(
        rte_cfg,
        "Com",
        impl_ref="/MICROSAR/Com_Impl",
        cfg_ref="/ActiveEcuC/Com",
        ea_specs=[
            ("COM_EXCLUSIVE_AREA_TX", "ALL_INTERRUPT_BLOCKING", "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/COM_EXCLUSIVE_AREA_TX", None, None, False),
            ("COM_EXCLUSIVE_AREA_RX", "OS_INTERRUPT_BLOCKING", "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/COM_EXCLUSIVE_AREA_RX", None, None, False),
            ("COM_EXCLUSIVE_AREA_RES", "OS_RESOURCE", "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/COM_EXCLUSIVE_AREA_RES", "/ActiveEcuC/Os/OsResource_Com", None, False),
            ("COM_EXCLUSIVE_AREA_SPIN", "OS_SPINLOCK", "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/COM_EXCLUSIVE_AREA_SPIN", None, "/ActiveEcuC/Os/OsSpinlock_Com", False),
            ("COM_EXCLUSIVE_AREA_COOP", "COOPERATIVE_RUNNABLE_PLACEMENT", "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/COM_EXCLUSIVE_AREA_COOP", None, None, False),
            ("COM_EXCLUSIVE_AREA_CUSTOM", "CUSTOM", "/MICROSAR/Com_ib_bswmd/BswModuleDescriptions/Com/ComBehavior/COM_EXCLUSIVE_AREA_CUSTOM", None, None, False),
            # Note: COM_EXCLUSIVE_AREA_BOTH intentionally omitted from Rte ECUC -> tests IB fallback default + warning
        ],
    )
    _add_bsw_instance(
        rte_cfg,
        "CanIf",
        impl_ref="/MICROSAR/CanIf_Impl",
        cfg_ref="/ActiveEcuC/CanIf",
        ea_specs=[("CANIF_EXCLUSIVE_AREA_0", "NONE", "/MICROSAR/CanIf_ib_bswmd/BswModuleDescriptions/CanIf/CanIf_Behavior/CANIF_EXCLUSIVE_AREA_0", None, None, False)],
    )
    _add_bsw_instance(
        rte_cfg,
        "CanTrcv",
        impl_ref="/MICROSAR/CanTrcv_Tle9255/CanTrcv_Impl",
        cfg_ref="/ActiveEcuC/CanTrcv",
        ea_specs=[("CANTRCV_30_TLE9255_EXCLUSIVE_AREA_0", "ALL_INTERRUPT_BLOCKING", "/MICROSAR/CanTrcv_Tle9255_ib_bswmd/BswModuleDescriptions/CanTrcv/CanTrcv_Tle9255_Behavior/CANTRCV_30_TLE9255_EXCLUSIVE_AREA_0", None, None, False)],
    )
    _add_bsw_instance(
        rte_cfg,
        "BswM",
        impl_ref="/MICROSAR/BswM_Impl",
        cfg_ref="/ActiveEcuC/BswM",
        ea_specs=[("BSWM_EXCLUSIVE_AREA_0", "ALL_INTERRUPT_BLOCKING", "/MICROSAR/BswM_ib_bswmd/BswModuleDescriptions/BswM/BswMBehavior/BSWM_EXCLUSIVE_AREA_0", None, None, False)],
    )
    _add_bsw_instance(
        rte_cfg,
        "Det",
        impl_ref="/MICROSAR/Det_Impl",
        cfg_ref="/ActiveEcuC/Det",
        ea_specs=[("DET_EXCLUSIVE_AREA_0", "ALL_INTERRUPT_BLOCKING", "/MICROSAR/Det_ib_bswmd/BswModuleDescriptions/Det/DetBehavior/DET_EXCLUSIVE_AREA_0", None, None, True)],
    )

    os_cfg = _make_cfg("Os")
    if multi_core:
        os_cfg.containers.append(EcucContainerValue(short_name="OsCore0", definition_ref="/MICROSAR/Os/OsCore"))
        os_cfg.containers.append(EcucContainerValue(short_name="OsCore1", definition_ref="/MICROSAR/Os/OsCore"))
    else:
        os_cfg.containers.append(EcucContainerValue(short_name="OsCore0", definition_ref="/MICROSAR/Os/OsCore"))
    os_cfg.containers.append(EcucContainerValue(short_name="SystemApplication_OsCore0", definition_ref="/MICROSAR/Os/OsApplication"))
    if multi_core:
        os_cfg.containers.append(EcucContainerValue(short_name="SystemApplication_OsCore1", definition_ref="/MICROSAR/Os/OsApplication"))

    proj = SimpleNamespace(
        path=dpa,
        format_version=8,
        directories=project_paths.ProjectDirectories.default_v8(),
        packages={
            "Rte": rte_pkg,
            "Com": com_pkg,
            "CanIf": canif_pkg,
            "CanTrcv": trcv_pkg,
            "BswM": bswm_pkg,
            "Det": det_pkg,
        },
        module_managers={
            "Rte": _make_mgr(rte_cfg),
            "Com": _make_mgr(_make_cfg("Com")),
            "CanIf": _make_mgr(_make_cfg("CanIf")),
            "CanTrcv": _make_mgr(_make_cfg("CanTrcv", "/MICROSAR/CanTrcv_Tle9255/CanTrcv")),
            "BswM": _make_mgr(_make_cfg("BswM")),
            "Det": _make_mgr(_make_cfg("Det")),
            "Os": _make_mgr(os_cfg),
        },
    )
    return proj, proj_root


def test_phase1_synthesizes_schm_and_core_rte_headers(tmp_path):
    proj, proj_root = _build_synthetic_project(tmp_path, multi_core=True, disable_init_mem=False)
    gen_root = proj_root / "gen"

    report = RteSchMGenerator(proj).generate(gen_root, flat=False)
    assert report.ok
    assert report.skipped_modules == [("CanNm", "模块尚未加载到当前工程")]
    assert any("COM_EXCLUSIVE_AREA_BOTH" in w for w in report.warnings)

    inc = gen_root / "Rte" / "include"
    assert not (inc / "SchM_Rte.h").exists()

    # Core headers
    rte_h = (inc / "Rte.h").read_text(encoding="utf-8")
    assert "# define RTE_SW_MAJOR_VERSION (0x04U)" in rte_h
    assert "# define RTE_SW_MINOR_VERSION (0x26U)" in rte_h
    assert "# define RTE_SW_PATCH_VERSION (0x02U)" in rte_h
    assert "# define RTE_VENDOR_ID (0x001EU)" in rte_h
    assert "# define RTE_AR_RELEASE_MAJOR_VERSION     (0x04U)" in rte_h
    assert "# define RTE_AR_RELEASE_MINOR_VERSION     (0x03U)" in rte_h
    assert "# define RTE_AR_RELEASE_REVISION_VERSION  (0x01U)" in rte_h

    rte_cfg_h = (inc / "Rte_Cfg.h").read_text(encoding="utf-8")
    assert "# define RTE_CFG_H" in rte_cfg_h
    assert '# include "Std_Types.h"' in rte_cfg_h
    assert "COMPATIBILITY_MODE" not in rte_cfg_h

    rte_main_h = (inc / "Rte_Main.h").read_text(encoding="utf-8")
    assert "FUNC(void, RTE_CODE) SchM_StartTimingCore0(void);" in rte_main_h
    assert "FUNC(void, RTE_CODE) SchM_StartTimingCore1(void);" in rte_main_h
    assert "FUNC(void, RTE_CODE) Rte_InitMemory(void);" in rte_main_h
    assert "FUNC(void, RTE_CODE) Rte_InitMemory_SystemApplication_OsCore0(void);" in rte_main_h
    assert "FUNC(void, RTE_CODE) Rte_InitMemory_SystemApplication_OsCore1(void);" in rte_main_h

    assert '# include "Com.h"' in (inc / "Rte_Cbk.h").read_text(encoding="utf-8")
    assert "# define RTE_TYPE_H" in (inc / "Rte_Type.h").read_text(encoding="utf-8")
    assert "# define RTE_USERTYPES_H" in (inc / "Rte_UserTypes.h").read_text(encoding="utf-8")

    # VENDOR-API-INFIX + legacy MemMap fallback
    trcv_h = (inc / "SchM_CanTrcv_30_Tle9255.h").read_text(encoding="utf-8")
    assert "# define SCHM_CANTRCV_30_TLE9255_H" in trcv_h
    assert '# include "MemMap.h"' in trcv_h
    assert "FUNC(void, CANTRCV_30_TLE9255_CODE) CanTrcv_30_Tle9255_MainFunction(void);" in trcv_h
    assert "# define SchM_Enter_CanTrcv_30_Tle9255_CANTRCV_30_TLE9255_EXCLUSIVE_AREA_0() SuspendAllInterrupts()" in trcv_h

    # Explicit MEMMAP artifact overrides standard <Mod>_MemMap.h
    bswm_h = (inc / "SchM_BswM.h").read_text(encoding="utf-8")
    assert '# include "Custom_BswM_MemMap.h"' in bswm_h

    # Zero-entity + NONE EA omits Os.h and START_SEC_CODE
    canif_h = (inc / "SchM_CanIf.h").read_text(encoding="utf-8")
    assert '# include "Os.h"' not in canif_h
    assert "START_SEC_CODE" not in canif_h
    assert "# define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0() ((void)0)" in canif_h

    # Generate-function EA emits RTE_CODE prototype instead of macro
    det_h = (inc / "SchM_Det.h").read_text(encoding="utf-8")
    assert '# include "Os.h"' not in det_h
    assert "FUNC(void, RTE_CODE) SchM_Enter_Det_DET_EXCLUSIVE_AREA_0(void);" in det_h
    assert "FUNC(void, RTE_CODE) SchM_Exit_Det_DET_EXCLUSIVE_AREA_0(void);" in det_h

    # All mechanism types + schedulable entity filtering (excludes Com_Virtual)
    com_h = (inc / "SchM_Com.h").read_text(encoding="utf-8")
    assert "Com_Virtual" not in com_h
    assert "FUNC(void, COM_CODE) Com_MainFunctionRx_ComMainFunctionRx(void);" in com_h
    assert "FUNC(void, COM_CODE) Com_MainFunctionTx_ComMainFunctionTx(void);" in com_h
    assert '# include "Com_MemMap.h"' in com_h
    assert "SuspendAllInterrupts()" in com_h
    assert "SuspendOSInterrupts()" in com_h
    assert "GetResource(OsResource_Com)" in com_h
    assert "GetSpinlock(OsSpinlock_Com)" in com_h
    assert "# define SchM_Enter_Com_COM_EXCLUSIVE_AREA_COOP() ((void)0)" in com_h
    assert "FUNC(void, RTE_CODE) SchM_Enter_Com_COM_EXCLUSIVE_AREA_CUSTOM(void);" in com_h

    # Optional C syntax compilation check using clang
    clang = shutil.which("clang")
    if clang:
        stub_dir = tmp_path / "c_stubs"
        stub_dir.mkdir()
        (stub_dir / "Std_Types.h").write_text(
            "typedef unsigned char uint8; typedef unsigned short uint16; typedef unsigned int uint32;\n"
            "typedef uint8 Std_ReturnType;\n"
            "#define FUNC(rettype, memclass) rettype\n"
            "#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *\n"
            "#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *\n",
            encoding="utf-8",
        )
        (stub_dir / "Platform_Types.h").write_text("/* stub */\n", encoding="utf-8")
        (stub_dir / "Os.h").write_text(
            "void SuspendAllInterrupts(void); void ResumeAllInterrupts(void);\n"
            "void SuspendOSInterrupts(void); void ResumeOSInterrupts(void);\n"
            "typedef int ResourceType; typedef int SpinlockIdType;\n"
            "extern ResourceType OsResource_Com; extern SpinlockIdType OsSpinlock_Com;\n"
            "void GetResource(ResourceType r); void ReleaseResource(ResourceType r);\n"
            "void GetSpinlock(SpinlockIdType s); void ReleaseSpinlock(SpinlockIdType s);\n",
            encoding="utf-8",
        )
        (stub_dir / "Com.h").write_text("/* stub */\n", encoding="utf-8")
        for mm in ("MemMap.h", "Com_MemMap.h", "Custom_BswM_MemMap.h", "Rte_MemMap.h"):
            (stub_dir / mm).write_text("/* stub */\n", encoding="utf-8")

        tu = tmp_path / "compile_check.c"
        tu.write_text(
            '#include "Rte.h"\n'
            '#include "Rte_Main.h"\n'
            '#include "Rte_Cbk.h"\n'
            '#include "SchM_BswM.h"\n'
            '#include "SchM_CanIf.h"\n'
            '#include "SchM_CanTrcv_30_Tle9255.h"\n'
            '#include "SchM_Com.h"\n'
            '#include "SchM_Det.h"\n'
            "int rte_phase1_smoke(void) { return 0; }\n",
            encoding="utf-8",
        )
        proc = subprocess.run(
            [clang, "-fsyntax-only", "-Wall", "-Wextra", "-Werror", f"-I{stub_dir}", f"-I{inc}", str(tu)],
            capture_output=True,
            text=True,
        )
        assert proc.returncode == 0, f"clang failed:\n{proc.stderr}"


def test_single_core_disable_init_memory_and_flat_idempotent_stubs(tmp_path):
    proj, proj_root = _build_synthetic_project(tmp_path, multi_core=False, disable_init_mem=True)
    proj.directories = project_paths.ProjectDirectories.from_dict(
        {"gen_layout": "flat"}, project_paths.ProjectDirectories.default_v8()
    )
    proj.module_managers.pop("Com")
    proj.packages.pop("Com")
    # Remove Com instance so only active modules run cleanly
    proj.module_managers["Rte"].configuration.containers = [
        c for c in proj.module_managers["Rte"].configuration.containers if c.short_name != "Com"
    ]

    gen_root = proj_root / "gen"
    inc = gen_root / "include"
    inc.mkdir(parents=True)
    custom_user_types = "/* user types preserved */\n"
    custom_rte_type = "/* phase2 type header preserved */\n"
    (inc / "Rte_UserTypes.h").write_text(custom_user_types, encoding="utf-8")
    (inc / "Rte_Type.h").write_text(custom_rte_type, encoding="utf-8")

    report1 = RteSchMGenerator.generate_from_project(proj, gen_root)
    assert report1.ok
    assert (inc / "Rte_UserTypes.h").read_text(encoding="utf-8") == custom_user_types
    assert (inc / "Rte_Type.h").read_text(encoding="utf-8") == custom_rte_type
    assert {inc / "Rte_UserTypes.h", inc / "Rte_Type.h"}.issubset(set(report1.preserved_files))

    rte_main_h = (inc / "Rte_Main.h").read_text(encoding="utf-8")
    assert "SchM_StartTimingCore0" not in rte_main_h
    assert "Rte_InitMemory" not in rte_main_h
    assert '# include "Com.h"' not in (inc / "Rte_Cbk.h").read_text(encoding="utf-8")

    # Second run is incremental and rewrites nothing
    report2 = RteSchMGenerator.generate_from_project(proj, gen_root)
    assert report2.ok
    assert report2.generated_files == []
    assert len(report2.unchanged_files) > 0


def test_missing_os_resource_or_spinlock_ref_returns_error(tmp_path):
    proj, proj_root = _build_synthetic_project(tmp_path)
    com_inst = next(
        c for c in proj.module_managers["Rte"].configuration.containers if c.short_name == "Com"
    )
    for sub in com_inst.sub_containers:
        if sub.short_name == "COM_EXCLUSIVE_AREA_RES":
            sub.reference_values.pop("RteBswExclusiveAreaOsResourceRef", None)

    report = RteSchMGenerator(proj).generate(proj_root / "gen", flat=False)
    assert not report.ok
    assert any("OS_RESOURCE" in e for e in report.errors)
    assert report.generated_files == []


_REAL_DPA = Path("/Users/qlwang/Desktop/test3/StartApplication1/StartApplication1.dpa")
_REAL_GENDATA = Path("/Users/qlwang/Desktop/未命名文件夹/mcuapp/Applications/SipAddon/StartApplication/Appl/GenData")


def _extract_schm_signature(text: str):
    funcs = set(re.findall(r"FUNC\s*\([^)]+\)\s+[A-Za-z0-9_]+\s*\([^)]*\)\s*;", text))
    macros = {}
    for m in re.finditer(r"#\s*define\s+(SchM_(?:Enter|Exit)_[A-Za-z0-9_]+)\(\)\s+([^\r\n/]+)", text):
        macros[m.group(1)] = m.group(2).strip()
    memmap_incs = set(re.findall(r'#\s*include\s+"([^"]*MemMap\.h)"', text))
    return funcs, macros, memmap_incs


@pytest.mark.skipif(
    not (_REAL_DPA.is_file() and _REAL_GENDATA.is_dir()),
    reason="Real StartApplication1 project or Vector Appl/GenData fixture not available",
)
def test_real_startapplication_golden_parity(tmp_path):
    wm = WorkspaceManager()
    proj, _ = wm.load_project(_REAL_DPA)

    report = RteSchMGenerator(proj).generate(tmp_path / "gen", flat=True)
    assert report.ok
    assert [m for m, _ in report.skipped_modules] == ["CanNm"]

    inc = tmp_path / "gen" / "include"
    expected_bsw = [
        "BswM",
        "CanIf",
        "CanSM",
        "CanTp",
        "CanTrcv_30_Tle9255",
        "Com",
        "ComM",
        "Dcm",
        "Det",
        "EcuM",
        "PduR",
    ]
    for mod_api in expected_bsw:
        gen_h = inc / f"SchM_{mod_api}.h"
        ref_h = _REAL_GENDATA / f"SchM_{mod_api}.h"
        gen_th = inc / f"SchM_{mod_api}_Type.h"
        ref_th = _REAL_GENDATA / f"SchM_{mod_api}_Type.h"
        assert gen_h.is_file(), f"Missing {gen_h}"
        assert gen_th.is_file(), f"Missing {gen_th}"

        g_funcs, g_macros, g_mm = _extract_schm_signature(gen_h.read_text(encoding="utf-8"))
        r_funcs, r_macros, r_mm = _extract_schm_signature(ref_h.read_text(encoding="utf-8"))
        assert g_funcs == r_funcs, f"Func mismatch in SchM_{mod_api}.h"
        assert g_macros == r_macros, f"Macro mismatch in SchM_{mod_api}.h"
        assert g_mm == r_mm, f"MemMap mismatch in SchM_{mod_api}.h"

    gen_main = (inc / "Rte_Main.h").read_text(encoding="utf-8")
    ref_main = (_REAL_GENDATA / "Rte_Main.h").read_text(encoding="utf-8")
    main_re = r"FUNC\s*\([^)]+\)\s+[A-Za-z0-9_]+\s*\([^)]*\)\s*;"
    assert set(re.findall(main_re, gen_main)) == set(re.findall(main_re, ref_main))

    gen_rte_h = (inc / "Rte.h").read_text(encoding="utf-8")
    assert "# define RTE_SW_MAJOR_VERSION (0x04U)" in gen_rte_h
    assert "# define RTE_SW_MINOR_VERSION (0x26U)" in gen_rte_h
    assert "# define RTE_SW_PATCH_VERSION (0x02U)" in gen_rte_h
    assert "# define RTE_VENDOR_ID (0x001EU)" in gen_rte_h

    gen_cfg_h = (inc / "Rte_Cfg.h").read_text(encoding="utf-8")
    assert '# include "Std_Types.h"' in gen_cfg_h
    assert "COMPATIBILITY_MODE" not in gen_cfg_h
    assert '# include "Com.h"' in (inc / "Rte_Cbk.h").read_text(encoding="utf-8")
