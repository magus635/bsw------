from pathlib import Path
from lxml import etree

from autosar_configurator.core.model.configuration_model import EcucContainerValue
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.generator.generator import CodeGenerator

REPO_ROOT = Path(__file__).resolve().parents[2]
DET_TEMPLATE_DIR = REPO_ROOT / "template_packs" / "davinci" / "Det"

DET_BSWMD = Path(r"D:\davinci\mcuapp\Components\Det\BSWMD\Det_bswmd.arxml")
DET_ECUC = Path(r"D:\davinci\mcuapp\Applications\SipAddon\StartApplication\Config\ECUC\StartApplication_Det_Det_ecuc.arxml")
DET_REF_H = Path(r"D:\davinci\mcuapp\Applications\SipAddon\StartApplication\Appl\GenData\Det_Cfg.h")
DET_REF_C = Path(r"D:\davinci\mcuapp\Applications\SipAddon\StartApplication\Appl\GenData\Det_Cfg.c")

VSET_BSWMD = Path(r"D:\davinci\mcuapp\Components\vSet\BSWMD\vSet_bswmd.arxml")
VSET_ECUC = Path(r"D:\davinci\mcuapp\Applications\SipAddon\StartApplication\Config\ECUC\StartApplication_vSet_vSet_ecuc.arxml")

ECUC_BSWMD = Path(r"D:\davinci\mcuapp\Components\EcuC\BSWMD\EcuC_bswmd.arxml")
ECUC_ECUC = Path(r"D:\davinci\mcuapp\Applications\SipAddon\StartApplication\Config\ECUC\StartApplication_EcuC_EcuC_ecuc.arxml")


def _parse_ecuc(arxml_path: Path):
    tree = etree.parse(str(arxml_path))
    elem = tree.xpath('//*[local-name()="ECUC-MODULE-CONFIGURATION-VALUES"]')[0]
    return ArxmlParser().parse_ecuc_configuration_values(elem)


def _load_det():
    mod_def = EcucDefParser().parse_module_def_file(DET_BSWMD)
    cfg = _parse_ecuc(DET_ECUC)
    return mod_def, cfg


def _load_vset():
    mod_def = EcucDefParser().parse_module_def_file(VSET_BSWMD)
    cfg = _parse_ecuc(VSET_ECUC)
    return mod_def, cfg


def _load_ecuc():
    mod_def = EcucDefParser().parse_module_def_file(ECUC_BSWMD)
    cfg = _parse_ecuc(ECUC_ECUC)
    return mod_def, cfg


def _extract_body(text: str, marker: str) -> str:
    idx = text.index(marker)
    return text[idx:].replace("\r\n", "\n")


def test_det_cfg_h_and_c_match_davinci_reference_body_byte_for_byte(tmp_path):
    mod_def, cfg = _load_det()
    gen = CodeGenerator(mod_def, cfg, package_template_dir=DET_TEMPLATE_DIR)

    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    out_h = tmp_path / "include" / "Det_Cfg.h"
    out_c = tmp_path / "src" / "Det_Cfg.c"
    assert out_h.is_file()
    assert out_c.is_file()

    generated_h = out_h.read_text(encoding="utf-8")
    generated_c = out_c.read_text(encoding="utf-8")
    reference_h = DET_REF_H.read_text(encoding="utf-8")
    reference_c = DET_REF_C.read_text(encoding="utf-8")

    for text in (generated_h, generated_c):
        assert "Vector Informatik GmbH" not in text
        assert "BETA VERSION" not in text

    assert _extract_body(generated_h, "#if !defined(DET_CFG_H)") == _extract_body(
        reference_h, "#if !defined(DET_CFG_H)"
    )
    assert _extract_body(generated_c, "#define DET_CFG_SOURCE") == _extract_body(
        reference_c, "#define DET_CFG_SOURCE"
    )


def test_det_cfg_with_vset_and_ecuc_matches_reference_and_reflects_overrides(tmp_path):
    det_def, det_cfg = _load_det()
    vset_def, vset_cfg = _load_vset()
    ecuc_def, ecuc_cfg = _load_ecuc()

    all_configs = {
        "vSet": (vset_def, vset_cfg),
        "EcuC": (ecuc_def, ecuc_cfg),
    }

    base_dir = tmp_path / "base"
    gen = CodeGenerator(
        det_def,
        det_cfg,
        package_template_dir=DET_TEMPLATE_DIR,
        all_configurations=all_configs,
    )
    assert gen.generate_all(base_dir, flat=True) is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    base_h = (base_dir / "include" / "Det_Cfg.h").read_text(encoding="utf-8")
    base_c = (base_dir / "src" / "Det_Cfg.c").read_text(encoding="utf-8")
    assert _extract_body(base_h, "#if !defined(DET_CFG_H)") == _extract_body(
        DET_REF_H.read_text(encoding="utf-8"), "#if !defined(DET_CFG_H)"
    )
    assert _extract_body(base_c, "#define DET_CFG_SOURCE") == _extract_body(
        DET_REF_C.read_text(encoding="utf-8"), "#define DET_CFG_SOURCE"
    )

    # Mutate vSet & EcuC parameters and verify overrides
    vset_general = next(c for c in vset_cfg.containers if c.short_name == "vSetGeneral")
    vset_platform = next(c for c in vset_cfg.containers if c.short_name == "vSetPlatform")
    ecuc_general = next(c for c in ecuc_cfg.containers if c.short_name == "EcucGeneral")

    ecuc_general.set_parameter_value(
        "AtomicBitAccessInBitfield",
        True,
        "/MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield",
    )
    ecuc_general.set_parameter_value(
        "AtomicVariableAccess",
        "Atomic16BitAccess",
        "/MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess",
    )
    vset_platform.set_parameter_value(
        "vSetBitOrder",
        "MSB_to_LSB",
        "/MICROSAR/vSet/vSetPlatform/vSetBitOrder",
    )
    vset_general.set_parameter_value(
        "vSetDummyStatementKind",
        "VoidCast",
        "/MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind",
    )

    ovr_dir = tmp_path / "override_voidcast"
    gen_ovr = CodeGenerator(
        det_def,
        det_cfg,
        package_template_dir=DET_TEMPLATE_DIR,
        all_configurations=all_configs,
        ecu_resources={
            "Det.Processor": "DET_PROCESSOR_CUSTOM_CORE",
            "Det.Compiler": "DET_COMP_CUSTOM_CC",
        },
    )
    assert gen_ovr.generate_all(ovr_dir, flat=True) is True
    ovr_h = (ovr_dir / "include" / "Det_Cfg.h").read_text(encoding="utf-8")

    assert "#define DET_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON" in ovr_h
    assert "#define DET_ATOMIC_VARIABLE_ACCESS 16u" in ovr_h
    assert "#define DET_CPUTYPE_BITORDER_MSB2LSB" in ovr_h
    assert "DET_CPUTYPE_BITORDER_LSB2MSB" not in ovr_h
    assert "#define DET_USE_DUMMY_STATEMENT STD_ON" in ovr_h
    assert "#define DET_DUMMY_STATEMENT(v) (void)(v)" in ovr_h
    assert "#define DET_DUMMY_STATEMENT_CONST(v) (void)(v)" in ovr_h
    assert "#define DET_PROCESSOR_CUSTOM_CORE" in ovr_h
    assert "#define DET_COMP_CUSTOM_CC" in ovr_h

    # Test DummyStatementKind = None & EcuC-only fallback
    ecuc_general.set_parameter_value(
        "DummyStatement",
        False,
        "/MICROSAR/EcuC/EcucGeneral/DummyStatement",
    )
    ecuc_general.set_parameter_value(
        "BitOrder",
        "MSB_to_LSB",
        "/MICROSAR/EcuC/EcucGeneral/BitOrder",
    )
    ecuc_general.set_parameter_value(
        "AtomicVariableAccess",
        "Atomic64BitAccess",
        "/MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess",
    )
    none_dir = tmp_path / "ecuc_only_none"
    gen_ecuc_only = CodeGenerator(
        det_def,
        det_cfg,
        package_template_dir=DET_TEMPLATE_DIR,
        all_configurations={"EcuC": (ecuc_def, ecuc_cfg)},
    )
    assert gen_ecuc_only.generate_all(none_dir, flat=True) is True
    none_h = (none_dir / "include" / "Det_Cfg.h").read_text(encoding="utf-8")

    assert "#define DET_USE_DUMMY_STATEMENT STD_OFF" in none_h
    assert "#define DET_DUMMY_STATEMENT(v) /* PRQA S 3453 */" in none_h
    assert "#define DET_DUMMY_STATEMENT_CONST(v) /* PRQA S 3453 */" in none_h
    assert "#define DET_ATOMIC_VARIABLE_ACCESS 64u" in none_h
    assert "#define DET_CPUTYPE_BITORDER_MSB2LSB" in none_h


def test_det_cfg_h_reflects_all_det_general_switches_and_limits(tmp_path):
    mod_def, cfg = _load_det()
    det_general = next(c for c in cfg.containers if c.short_name == "DetGeneral")
    params = det_general.parameter_values

    params["DetEnableDet"].value = False
    params["DetVersionInfoApi"].value = True
    params["DetExtDebugSupport"].value = True
    params["DetDltFilterSize"].value = 3
    params["DetGlobalFilterSize"].value = 8
    params["DetBreakFilterSize"].value = 4
    params["DetLogBufferSize"].value = 16
    params["DetReportErrorRecursionLimit"].value = 2
    params["DetReportRuntimeErrorRecursionLimit"].value = 5
    params["DetReportTransientFaultRecursionLimit"].value = 7

    det_general.set_parameter_value(
        "DetForwardToDlt", True, "/MICROSAR/Det/DetGeneral/DetForwardToDlt"
    )
    det_general.set_parameter_value(
        "DetUserConfigFile",
        "Det_UserCfg.h",
        "/MICROSAR/Det/DetGeneral/DetUserConfigFile",
    )

    gen = CodeGenerator(mod_def, cfg, package_template_dir=DET_TEMPLATE_DIR)
    assert gen.generate_all(tmp_path, flat=True) is True
    assert gen.last_status == "generated"

    text = (tmp_path / "include" / "Det_Cfg.h").read_text(encoding="utf-8")
    assert "#define DET_ENABLED                              STD_OFF" in text
    assert "#define DET_VERSION_INFO_API                     STD_ON" in text
    assert "#define DET_DEBUG_ENABLED                        STD_ON" in text
    assert "#define DET_DLTFILTERSIZE                        3u" in text
    assert "#define DET_GLOBALFILTERSIZE                     8u" in text
    assert "#define DET_BREAKFILTERSIZE                      4u" in text
    assert "#define DET_LOGBUFFERSIZE                        16u" in text
    assert "#define DET_FORWARD_TO_DLT                       STD_ON" in text
    assert "#define DET_REPORT_ERROR_RECURSIONLIMIT          2u" in text
    assert "#define DET_REPORT_RUNTIMEERROR_RECURSIONLIMIT   5u" in text
    assert "#define DET_REPORT_TRANSIENTFAULT_RECURSIONLIMIT 7u" in text
    assert '#include "Det_UserCfg.h"\n#endif /* DET_CFG_H */' in text.replace("\r\n", "\n")


def test_det_cfg_h_generates_multiple_det_modules_and_instances(tmp_path):
    mod_def, cfg = _load_det()
    config_set = next(c for c in cfg.containers if c.short_name == "DetConfigSet")

    inst0 = EcucContainerValue(
        short_name="SwcA_Inst0",
        definition_ref="/MICROSAR/Det/DetConfigSet/DetModule/DetModuleInstance",
    )
    inst0.set_parameter_value(
        "DetInstanceId",
        0,
        "/MICROSAR/Det/DetConfigSet/DetModule/DetModuleInstance/DetInstanceId",
    )
    inst1 = EcucContainerValue(
        short_name="SwcA_Inst1",
        definition_ref="/MICROSAR/Det/DetConfigSet/DetModule/DetModuleInstance",
    )
    inst1.set_parameter_value(
        "DetInstanceId",
        7,
        "/MICROSAR/Det/DetConfigSet/DetModule/DetModuleInstance/DetInstanceId",
    )
    config_set.sub_containers[0].add_sub_container(inst0)
    config_set.sub_containers[0].add_sub_container(inst1)

    mod_b = EcucContainerValue(
        short_name="SwcModuleB",
        definition_ref="/MICROSAR/Det/DetConfigSet/DetModule",
    )
    mod_b.set_parameter_value(
        "DetModuleId", 4097, "/MICROSAR/Det/DetConfigSet/DetModule/DetModuleId"
    )
    inst_b = EcucContainerValue(
        short_name="SwcB_Inst0",
        definition_ref="/MICROSAR/Det/DetConfigSet/DetModule/DetModuleInstance",
    )
    inst_b.set_parameter_value(
        "DetInstanceId",
        2,
        "/MICROSAR/Det/DetConfigSet/DetModule/DetModuleInstance/DetInstanceId",
    )
    mod_b.add_sub_container(inst_b)
    config_set.add_sub_container(mod_b)

    gen = CodeGenerator(mod_def, cfg, package_template_dir=DET_TEMPLATE_DIR)
    assert gen.generate_all(tmp_path, flat=True) is True

    text = (tmp_path / "include" / "Det_Cfg.h").read_text(encoding="utf-8")
    assert "#define DetConf_DetModule_DetModule (4096u) " in text
    assert "#define DetConf_DetModule_SwcModuleB (4097u) " in text
    assert "#define DetConf_DetModule 4096u " in text
    assert "#define DetConf_SwcModuleB 4097u " in text
    assert "#define DetConf_DetModuleInstance_SwcA_Inst0 (0u)" in text
    assert "#define DetConf_DetModuleInstance_SwcA_Inst1 (7u)" in text
    assert "#define DetConf_DetModuleInstance_SwcB_Inst0 (2u)" in text


def _build_det_cfg_with_notifications(param_entries_xml: str):
    xml = f"""<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>ActiveEcuC</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Det</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/Det</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DetGeneral</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Det/DetGeneral</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/Det/DetGeneral/DetEnableDet</DEFINITION-REF>
                  <VALUE>true</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>DetNotification</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/Det/DetNotification</DEFINITION-REF>
              <PARAMETER-VALUES>
                {param_entries_xml}
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>"""
    elem = etree.fromstring(xml.encode("utf-8")).xpath(
        '//*[local-name()="ECUC-MODULE-CONFIGURATION-VALUES"]'
    )[0]
    return ArxmlParser().parse_ecuc_configuration_values(elem)


def _fn_param_xml(param_name: str, value: str) -> str:
    return f"""
<ECUC-TEXTUAL-PARAM-VALUE>
  <DEFINITION-REF DEST="ECUC-FUNCTION-NAME-DEF">/MICROSAR/Det/DetNotification/{param_name}</DEFINITION-REF>
  <VALUE>{value}</VALUE>
</ECUC-TEXTUAL-PARAM-VALUE>
"""


def test_det_notification_callouts_generate_tables_macros_and_deduped_prototypes(tmp_path):
    mod_def = EcucDefParser().parse_module_def_file(DET_BSWMD)

    # Case 1: Single unindexed callout in DetErrorHook (stored in parameter_values)
    cfg_single = _build_det_cfg_with_notifications(
        _fn_param_xml("DetErrorHook", "Appl_SingleErrorHook")
    )
    single_dir = tmp_path / "single"
    gen_single = CodeGenerator(mod_def, cfg_single, package_template_dir=DET_TEMPLATE_DIR)
    assert gen_single.generate_all(single_dir, flat=True) is True

    h_single = (single_dir / "include" / "Det_Cfg.h").read_text(encoding="utf-8")
    c_single = (single_dir / "src" / "Det_Cfg.c").read_text(encoding="utf-8")

    assert "#define DET_ERRORHOOKTABLE                                                                          STD_ON" in h_single
    assert "#define DET_SIZEOFERRORHOOKTABLE                                                                    STD_ON" in h_single
    assert "#define DET_RUNTIMEERRORCALLOUTTABLE                                                                STD_OFF" in h_single
    assert "#define DET_TRANSIENTFAULTCALLOUTTABLE                                                              STD_OFF" in h_single
    assert "#define Det_HasErrorHookTable()" in h_single
    assert "#define Det_HasSizeOfErrorHookTable()" in h_single
    assert "#define Det_GetErrorHookTable(Index) (Det_ErrorHookTable[(Index)])" in h_single
    assert "#define Det_GetSizeOfErrorHookTable() 1u" in h_single
    assert "extern CONST(Det_CalloutTableType, DET_CONST) Det_ErrorHookTable[1];" in h_single
    assert "extern CONST(Det_CalloutTableType, DET_CONST) Det_RuntimeErrorCalloutTable" not in h_single
    assert "FUNC(Std_ReturnType, DET_CODE) Appl_SingleErrorHook(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);" in h_single

    assert "CONST(Det_CalloutTableType, DET_CONST) Det_ErrorHookTable[1] = {\n  Appl_SingleErrorHook\n};" in c_single.replace("\r\n", "\n")
    assert "Det_RuntimeErrorCalloutTable" not in c_single

    # Case 2: Multiple unindexed callouts across all 3 lists with a shared hook name
    entries_xml = (
        _fn_param_xml("DetErrorHook", "Appl_ErrorHook1")
        + _fn_param_xml("DetErrorHook", "Appl_SharedHook")
        + _fn_param_xml("DetReportRuntimeErrorCallout", "Appl_SharedHook")
        + _fn_param_xml("DetReportRuntimeErrorCallout", "Appl_RuntimeHook2")
        + _fn_param_xml("DetReportTransientFaultCallout", "Appl_TransientHook1")
        + _fn_param_xml("DetReportTransientFaultCallout", "Appl_TransientHook2")
    )
    cfg_multi = _build_det_cfg_with_notifications(entries_xml)
    multi_dir = tmp_path / "multi"
    gen_multi = CodeGenerator(mod_def, cfg_multi, package_template_dir=DET_TEMPLATE_DIR)
    assert gen_multi.generate_all(multi_dir, flat=True) is True

    h_multi = (multi_dir / "include" / "Det_Cfg.h").read_text(encoding="utf-8")
    c_multi = (multi_dir / "src" / "Det_Cfg.c").read_text(encoding="utf-8").replace("\r\n", "\n")

    assert "#define DET_ERRORHOOKTABLE                                                                          STD_ON" in h_multi
    assert "#define DET_RUNTIMEERRORCALLOUTTABLE                                                                STD_ON" in h_multi
    assert "#define DET_TRANSIENTFAULTCALLOUTTABLE                                                              STD_ON" in h_multi
    assert "#define DET_SIZEOFERRORHOOKTABLE                                                                    STD_ON" in h_multi
    assert "#define DET_SIZEOFRUNTIMEERRORCALLOUTTABLE                                                          STD_ON" in h_multi
    assert "#define DET_SIZEOFTRANSIENTFAULTCALLOUTTABLE                                                        STD_ON" in h_multi

    assert "#define Det_HasErrorHookTable()" in h_multi
    assert "#define Det_HasSizeOfErrorHookTable()" in h_multi
    assert "#define Det_HasRuntimeErrorCalloutTable()" in h_multi
    assert "#define Det_HasSizeOfRuntimeErrorCalloutTable()" in h_multi
    assert "#define Det_HasTransientFaultCalloutTable()" in h_multi
    assert "#define Det_HasSizeOfTransientFaultCalloutTable()" in h_multi

    assert "#define Det_GetErrorHookTable(Index) (Det_ErrorHookTable[(Index)])" in h_multi
    assert "#define Det_GetSizeOfErrorHookTable() 2u" in h_multi
    assert "#define Det_GetRuntimeErrorCalloutTable(Index) (Det_RuntimeErrorCalloutTable[(Index)])" in h_multi
    assert "#define Det_GetSizeOfRuntimeErrorCalloutTable() 2u" in h_multi
    assert "#define Det_GetTransientFaultCalloutTable(Index) (Det_TransientFaultCalloutTable[(Index)])" in h_multi
    assert "#define Det_GetSizeOfTransientFaultCalloutTable() 2u" in h_multi

    assert "extern CONST(Det_CalloutTableType, DET_CONST) Det_ErrorHookTable[2];" in h_multi
    assert "extern CONST(Det_CalloutTableType, DET_CONST) Det_RuntimeErrorCalloutTable[2];" in h_multi
    assert "extern CONST(Det_CalloutTableType, DET_CONST) Det_TransientFaultCalloutTable[2];" in h_multi

    for fn in (
        "Appl_ErrorHook1",
        "Appl_SharedHook",
        "Appl_RuntimeHook2",
        "Appl_TransientHook1",
        "Appl_TransientHook2",
    ):
        proto = f"FUNC(Std_ReturnType, DET_CODE) {fn}(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);"
        assert h_multi.count(proto) == 1

    assert "#define DET_START_SEC_CONST_UNSPECIFIED" in c_multi
    assert '#include "Det_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */' in c_multi
    assert "CONST(Det_CalloutTableType, DET_CONST) Det_ErrorHookTable[2] = {\n  Appl_ErrorHook1,\n  Appl_SharedHook\n};" in c_multi
    assert "CONST(Det_CalloutTableType, DET_CONST) Det_RuntimeErrorCalloutTable[2] = {\n  Appl_SharedHook,\n  Appl_RuntimeHook2\n};" in c_multi
    assert "CONST(Det_CalloutTableType, DET_CONST) Det_TransientFaultCalloutTable[2] = {\n  Appl_TransientHook1,\n  Appl_TransientHook2\n};" in c_multi
    assert "#define DET_STOP_SEC_CONST_UNSPECIFIED" in c_multi


def test_det_cfg_uses_bswmd_defaults_when_containers_omitted(tmp_path):
    mod_def, cfg = _load_det()
    cfg.containers.clear()

    gen = CodeGenerator(mod_def, cfg, package_template_dir=DET_TEMPLATE_DIR)
    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is True
    assert gen.last_status == "generated"
    assert gen.warnings == []

    text_h = (tmp_path / "include" / "Det_Cfg.h").read_text(encoding="utf-8")
    text_c = (tmp_path / "src" / "Det_Cfg.c").read_text(encoding="utf-8")
    assert "#define DET_ENABLED                              STD_ON" in text_h
    assert "#define DET_VERSION_INFO_API                     STD_OFF" in text_h
    assert "#define DET_DEBUG_ENABLED                        STD_OFF" in text_h
    assert "#define DET_FORWARD_TO_DLT                       STD_OFF" in text_h
    assert "#define DET_DLTFILTERSIZE                        0u" in text_h
    assert "#define DET_REPORT_ERROR_RECURSIONLIMIT          0u" in text_h
    assert "DetConf_DetModule_" not in text_h
    assert "#define DET_CFG_SOURCE" in text_c


def test_det_cfg_errors_when_det_general_missing(tmp_path):
    mod_def, cfg = _load_det()
    mod_def.containers.pop("DetGeneral", None)
    cfg.containers.clear()

    gen = CodeGenerator(mod_def, cfg, package_template_dir=DET_TEMPLATE_DIR)
    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is False
    assert gen.last_status == "failed"
