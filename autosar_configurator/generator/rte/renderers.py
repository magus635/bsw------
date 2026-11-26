"""Deterministic C header renderers for Phase 1 RTE/SchM synthesis."""

from typing import List, Tuple

from .model import BswModuleSchmModel, ExclusiveAreaModel, RteProjectModel


def _header_banner(filename: str, description: str) -> List[str]:
    return [
        "/**********************************************************************************************************************",
        " *  FILE DESCRIPTION",
        " *  -------------------------------------------------------------------------------------------------------------------",
        f" *             File:  {filename}",
        " *        Generator:  AUTOSAR BSW Configurator (Model-Driven RTE/SchM Phase 1)",
        f" *      Description:  {description}",
        " *********************************************************************************************************************/",
    ]


def _exclusive_area_expr(ea: ExclusiveAreaModel) -> Tuple[str, str]:
    mech = ea.mechanism
    if mech == "ALL_INTERRUPT_BLOCKING":
        return "SuspendAllInterrupts()", "ResumeAllInterrupts()"
    if mech == "OS_INTERRUPT_BLOCKING":
        return "SuspendOSInterrupts()", "ResumeOSInterrupts()"
    if mech == "OS_RESOURCE":
        res = ea.os_resource or "UNKNOWN_OS_RESOURCE"
        return f"GetResource({res})", f"ReleaseResource({res})"
    if mech == "OS_SPINLOCK":
        lock = ea.os_spinlock or "UNKNOWN_OS_SPINLOCK"
        return f"GetSpinlock({lock})", f"ReleaseSpinlock({lock})"
    return "((void)0)", "((void)0)"


def render_rte_h(model: RteProjectModel) -> str:
    """Render ``Rte.h`` containing version macros, status codes, Det helpers, and Service IDs."""
    m = model.meta
    lines = _header_banner("Rte.h", "Header file containing RTE types, status codes, and Service IDs")
    lines.extend([
        "",
        "/* double include prevention */",
        "#ifndef RTE_H",
        "# define RTE_H",
        "",
        f"# define RTE_SW_MAJOR_VERSION (0x{m.sw_major:02X}U)",
        f"# define RTE_SW_MINOR_VERSION (0x{m.sw_minor:02X}U)",
        f"# define RTE_SW_PATCH_VERSION (0x{m.sw_patch:02X}U)",
        "",
        f"# define RTE_VENDOR_ID (0x{m.vendor_id:04X}U)",
        f"# define RTE_MODULE_ID (0x{m.module_id:04X}U)",
        "",
        f"# define RTE_AR_RELEASE_MAJOR_VERSION     (0x{m.ar_major:02X}U)",
        f"# define RTE_AR_RELEASE_MINOR_VERSION     (0x{m.ar_minor:02X}U)",
        f"# define RTE_AR_RELEASE_REVISION_VERSION  (0x{m.ar_patch:02X}U)",
        "",
        '# include "Std_Types.h"',
        '# include "Rte_UserTypes.h"',
        '# include "Platform_Types.h"',
        "",
        "# if !defined (TYPEDEF) && defined (AUTOMATIC)",
        "#  define TYPEDEF AUTOMATIC",
        "# endif",
        "",
        "# if !defined (FUNC_P2CONST)",
        "#  define FUNC_P2CONST(rettype, ptrclass, memclass) FUNC(P2CONST(rettype, AUTOMATIC, ptrclass), memclass)",
        "# endif",
        "",
        "# if !defined (FUNC_P2VAR)",
        "#  define FUNC_P2VAR(rettype, ptrclass, memclass) FUNC(P2VAR(rettype, AUTOMATIC, ptrclass), memclass)",
        "# endif",
        "",
        "/* common errors */",
        "# define RTE_E_OK               (0U)",
        "# define RTE_E_INVALID          (1U)",
        "",
        "/* overlayed errors */",
        "# define RTE_E_LOST_DATA        (64U)",
        "# define RTE_E_MAX_AGE_EXCEEDED (64U)",
        "",
        "# define Rte_HasOverlayedError(status) (((status) & 64U) != 0U)",
        "",
        "/* immediate infrastructure errors */",
        "# define RTE_E_COM_STOPPED            (128U)",
        "# define RTE_E_TIMEOUT                (129U)",
        "# define RTE_E_LIMIT                  (130U)",
        "# define RTE_E_NO_DATA                (131U)",
        "# define RTE_E_TRANSMIT_ACK           (132U)",
        "# define RTE_E_NEVER_RECEIVED         (133U)",
        "# define RTE_E_UNCONNECTED            (134U)",
        "# define RTE_E_IN_EXCLUSIVE_AREA      (135U)",
        "# define RTE_E_SEG_FAULT              (136U)",
        "# define RTE_E_OUT_OF_RANGE           (137U)",
        "# define RTE_E_SERIALIZATION_ERROR    (138U)",
        "# define RTE_E_HARD_TRANSFORMER_ERROR (138U)",
        "# define RTE_E_SERIALIZATION_LIMIT    (139U)",
        "# define RTE_E_TRANSFORMER_LIMIT      (139U)",
        "# define RTE_E_SOFT_TRANSFORMER_ERROR (140U)",
        "# define RTE_E_COM_BUSY               (141U)",
        "",
        "/* common SchM errors */",
        "# define SCHM_E_OK                    (0U)",
        "# define SCHM_E_TIMEOUT               (129U)",
        "# define SCHM_E_LIMIT                 (130U)",
        "# define SCHM_E_NO_DATA               (131U)",
        "# define SCHM_E_TRANSMIT_ACK          (132U)",
        "# define SCHM_E_IN_EXCLUSIVE_AREA     (135U)",
        "",
        "# define Rte_IsInfrastructureError(status) (((status) & 128U) != 0U)",
        "# define Rte_IsHardTransformerError Rte_IsInfrastructureError",
        "# define Rte_ApplicationError(status) ((status) & 63U)",
        "",
        "/**********************************************************************************************************************",
        " * Macros for reporting Det Errors",
        " *********************************************************************************************************************/",
        "# define Rte_CheckDetErrorReturnVoid( CONDITION, API_ID, ERROR_CODE )            { if(!(CONDITION)) { (void)Det_ReportError( RTE_MODULE_ID, 0, (API_ID), (ERROR_CODE)); return; } }",
        "# define Rte_CheckDetErrorReturnValue( CONDITION, API_ID, ERROR_CODE, RET_VAL )  { if(!(CONDITION)) { (void)Det_ReportError( RTE_MODULE_ID, 0, (API_ID), (ERROR_CODE)); return (RET_VAL); } }",
        "# define Rte_CheckDetErrorContinue( CONDITION, API_ID, ERROR_CODE )              { if(!(CONDITION)) { (void)Det_ReportError( RTE_MODULE_ID, 0, (API_ID), (ERROR_CODE)); } }",
        "# define Rte_CallDetReportError( API_ID, ERROR_CODE )                            ((void)Det_ReportError( RTE_MODULE_ID, 0, (API_ID), (ERROR_CODE)))",
        "",
        "/**********************************************************************************************************************",
        " * Service IDs of Rte APIs",
        " *********************************************************************************************************************/",
        "# define SCHM_INIT_SERVICE_ID                      (0x00U)",
        "# define SCHM_DEINIT_SERVICE_ID                    (0x01U)",
        "# define SCHM_ENTER_SERVICE_ID                     (0x03U)",
        "# define SCHM_EXIT_SERVICE_ID                      (0x04U)",
        "# define SCHM_START_SERVICE_ID                     (0x70U)",
        "# define SCHM_STARTTIMING_SERVICE_ID               (0x76U)",
        "# define RTE_SEND_SERVICE_ID                       (0x13U)",
        "# define RTE_WRITE_SERVICE_ID                      (0x14U)",
        "# define RTE_SWITCH_SERVICE_ID                     (0x15U)",
        "# define RTE_INVALIDATE_SERVICE_ID                 (0x16U)",
        "# define RTE_FEEDBACK_SERVICE_ID                   (0x17U)",
        "# define RTE_SWITCHACK_SERVICE_ID                  (0x18U)",
        "# define RTE_READ_SERVICE_ID                       (0x19U)",
        "# define RTE_DREAD_SERVICE_ID                      (0x1AU)",
        "# define RTE_RECEIVE_SERVICE_ID                    (0x1BU)",
        "# define RTE_CALL_SERVICE_ID                       (0x1CU)",
        "# define RTE_RESULT_SERVICE_ID                     (0x1DU)",
        "# define RTE_CDATA_SERVICE_ID                      (0x1FU)",
        "# define RTE_PRM_SERVICE_ID                        (0x20U)",
        "# define RTE_IRVREAD_SERVICE_ID                    (0x28U)",
        "# define RTE_IRVWRITE_SERVICE_ID                   (0x29U)",
        "# define RTE_ENTER_SERVICE_ID                      (0x2AU)",
        "# define RTE_EXIT_SERVICE_ID                       (0x2BU)",
        "# define RTE_MODE_SERVICE_ID                       (0x2CU)",
        "# define RTE_TRIGGER_SERVICE_ID                    (0x2DU)",
        "# define RTE_IRTRIGGER_SERVICE_ID                  (0x2EU)",
        "# define RTE_ISUPDATED_SERVICE_ID                  (0x30U)",
        "# define RTE_START_SERVICE_ID                      (0x70U)",
        "# define RTE_STOP_SERVICE_ID                       (0x71U)",
        "# define RTE_PARTITIONTERMINATED_SERVICE_ID        (0x72U)",
        "# define RTE_PARTITIONRESTARTING_SERVICE_ID        (0x73U)",
        "# define RTE_RESTARTPARTITION_SERVICE_ID           (0x74U)",
        "# define RTE_INIT_SERVICE_ID                       (0x75U)",
        "# define RTE_STARTTIMING_SERVICE_ID                (0x76U)",
        "# define RTE_COMCBKTACK_SN_SERVICE_ID              (0x90U)",
        "# define RTE_COMCBKTERR_SN_SERVICE_ID              (0x91U)",
        "# define RTE_COMCBKINV_SN_SERVICE_ID               (0x92U)",
        "# define RTE_COMCBKRXTOUT_SN_SERVICE_ID            (0x93U)",
        "# define RTE_COMCBKTXTOUT_SN_SERVICE_ID            (0x94U)",
        "# define RTE_COMCBK_SG_SERVICE_ID                  (0x95U)",
        "# define RTE_COMCBKTACK_SG_SERVICE_ID              (0x96U)",
        "# define RTE_COMCBKTERR_SG_SERVICE_ID              (0x97U)",
        "# define RTE_COMCBKINV_SG_SERVICE_ID               (0x98U)",
        "# define RTE_COMCBKRXTOUT_SG_SERVICE_ID            (0x99U)",
        "# define RTE_COMCBKTXTOUT_SG_SERVICE_ID            (0x9AU)",
        "# define RTE_SETMIRROR_SERVICE_ID                  (0x9BU)",
        "# define RTE_GETMIRROR_SERVICE_ID                  (0x9CU)",
        "# define RTE_NVMNOTIFYJOBFINISHED_SERVICE_ID       (0x9DU)",
        "# define RTE_NVMNOTIFYINITBLOCK_SERVICE_ID         (0x9EU)",
        "# define RTE_COMCBK_SN_SERVICE_ID                  (0x9FU)",
        "# define RTE_LDCOMCBKRXINDICATION_SERVICE_ID       (0xA0U)",
        "# define RTE_LDCOMCBKSTARTOFRECEPTION_SERVICE_ID   (0xA1U)",
        "# define RTE_LDCOMCBKCOPYRXDATA_SERVICE_ID         (0xA2U)",
        "# define RTE_LDCOMCBKTPRXINDICATION_SERVICE_ID     (0xA3U)",
        "# define RTE_LDCOMCBKCOPYTXDATA_SERVICE_ID         (0xA4U)",
        "# define RTE_LDCOMCBKTPTXCONFIRMATION_SERVICE_ID   (0xA5U)",
        "# define RTE_LDCOMCBKTRIGGERTRANSMIT_SERVICE_ID    (0xA6U)",
        "# define RTE_LDCOMCBKTXCONFIRMATION_SERVICE_ID     (0xA7U)",
        "# define RTE_TASK_SERVICE_ID                       (0xF0U)",
        "# define RTE_INCDISABLEFLAGS_SERVICE_ID            (0xF1U)",
        "# define RTE_DECDISABLEFLAGS_SERVICE_ID            (0xF2U)",
        "",
        "/**********************************************************************************************************************",
        " * Det Error Values",
        " *********************************************************************************************************************/",
        "# define RTE_E_DET_ILLEGAL_SIGNAL_ID               (0x01U)",
        "# define RTE_E_DET_ILLEGAL_VARIANT_CRITERION_VALUE (0x02U)",
        "# define RTE_E_DET_ILLEGAL_INVOCATION              (0x03U)",
        "# define RTE_E_DET_ILLEGAL_NESTED_EXCLUSIVE_AREA   (0x05U)",
        "# define RTE_E_DET_UNINIT                          (0x07U)",
        "# define RTE_E_DET_MODEARGUMENT                    (0x20U)",
        "# define RTE_E_DET_TRIGGERDISABLECOUNTER           (0x21U)",
        "# define RTE_E_DET_TRANSITIONSTATE                 (0x22U)",
        "# define RTE_E_DET_BLOCKSIZECHECK                  (0x23U)",
        "# define RTE_E_DET_MULTICORE_STARTUP               (0x24U)",
        "# define RTE_E_DET_MODESTATE                       (0x25U)",
        "# define RTE_E_DET_SCHM_STARTUP                    (0x26U)",
        "",
        "#endif /* RTE_H */",
        "",
    ])
    return "\n".join(lines)


def render_rte_main_h(model: RteProjectModel) -> str:
    """Render ``Rte_Main.h`` declaring SchM and RTE lifecycle APIs."""
    lines = _header_banner("Rte_Main.h", "Lifecycle Header File")
    lines.extend([
        "",
        "/* double include prevention */",
        "#ifndef RTE_MAIN_H",
        "# define RTE_MAIN_H",
        "",
        '# include "Rte.h"',
        "",
        "# ifdef __cplusplus",
        'extern "C" {',
        "# endif /* __cplusplus */",
        "",
        "# define RTE_START_SEC_CODE",
        '# include "Rte_MemMap.h"',
        "",
        "/* BSW Scheduler Life-Cycle API */",
        "FUNC(void, RTE_CODE) SchM_Init(void);",
        "FUNC(void, RTE_CODE) SchM_Start(void);",
        "FUNC(void, RTE_CODE) SchM_StartTiming(void);",
    ])

    if model.meta.enable_multi_core and len(model.os_cores) > 1:
        for core_suffix in model.os_cores:
            lines.append(f"FUNC(void, RTE_CODE) SchM_StartTiming{core_suffix}(void);")

    lines.extend([
        "FUNC(void, RTE_CODE) SchM_Deinit(void);",
        "",
        "/* RTE Life-Cycle API */",
        "FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void);",
        "FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void);",
    ])

    if not model.meta.disable_rte_init_memory:
        lines.extend([
            "",
            "/* Extended Life-Cycle API */",
            "FUNC(void, RTE_CODE) Rte_InitMemory(void);",
        ])
        for app_name in model.os_applications:
            lines.append(f"FUNC(void, RTE_CODE) Rte_InitMemory_{app_name}(void);")

    lines.extend([
        "",
        "# define RTE_STOP_SEC_CODE",
        '# include "Rte_MemMap.h"',
        "",
        "# ifdef __cplusplus",
        '} /* extern "C" */',
        "# endif /* __cplusplus */",
        "",
        "#endif /* RTE_MAIN_H */",
        "",
    ])
    return "\n".join(lines)


def render_rte_cfg_h(_model: RteProjectModel) -> str:
    """Render Vector-compatible minimal ``Rte_Cfg.h``."""
    lines = _header_banner("Rte_Cfg.h", "RTE configuration header file")
    lines.extend([
        "",
        "/* double include prevention */",
        "#ifndef RTE_CFG_H",
        "# define RTE_CFG_H",
        "",
        '# include "Std_Types.h"',
        "",
        "#endif /* RTE_CFG_H */",
        "",
    ])
    return "\n".join(lines)


def render_rte_cbk_h(model: RteProjectModel) -> str:
    """Render ``Rte_Cbk.h`` callback header file."""
    lines = _header_banner("Rte_Cbk.h", "Callback header file")
    lines.extend([
        "",
        "/* double include prevention */",
        "#ifndef RTE_CBK_H",
        "# define RTE_CBK_H",
        "",
    ])
    if model.has_com:
        lines.extend(['# include "Com.h"', ""])
    lines.extend([
        "#endif /* RTE_CBK_H */",
        "",
    ])
    return "\n".join(lines)


def render_rte_user_types_h() -> str:
    """Render non-destructive stub ``Rte_UserTypes.h``."""
    lines = _header_banner("Rte_UserTypes.h", "User-defined AUTOSAR helper types header")
    lines.extend([
        "",
        "#ifndef RTE_USERTYPES_H",
        "# define RTE_USERTYPES_H",
        "",
        "#endif /* RTE_USERTYPES_H */",
        "",
    ])
    return "\n".join(lines)


def render_rte_type_h_stub() -> str:
    """Render non-destructive Phase 1 compile stub ``Rte_Type.h``."""
    lines = _header_banner("Rte_Type.h", "Phase 1 compile stub for AUTOSAR RTE data types")
    lines.extend([
        "",
        "/* double include prevention */",
        "#ifndef RTE_TYPE_H",
        "# define RTE_TYPE_H",
        "",
        '# include "Rte.h"',
        '# include "Rte_Cfg.h"',
        "",
        "#endif /* RTE_TYPE_H */",
        "",
    ])
    return "\n".join(lines)


def render_schm_h(bsw_mod: BswModuleSchmModel) -> str:
    """Render ``SchM_<ApiName>.h`` for a single BSW module instance."""
    filename = f"SchM_{bsw_mod.api_name}.h"
    guard = f"SCHM_{bsw_mod.upper_prefix}_H"
    lines = _header_banner(filename, f"Header of BSW Scheduler for BSW Module <{bsw_mod.api_name}>")
    lines.extend([
        "",
        f"#ifndef {guard}",
        f"# define {guard}",
        "",
        "# ifdef __cplusplus",
        'extern "C" {',
        "# endif /* __cplusplus */",
        "",
        f'# include "SchM_{bsw_mod.api_name}_Type.h"',
        "",
    ])

    if bsw_mod.requires_os_header:
        lines.extend(['# include "Os.h"', ""])

    if bsw_mod.schedulable_entities:
        lines.append(f"# define {bsw_mod.upper_prefix}_START_SEC_CODE")
        lines.append(f'# include "{bsw_mod.memmap_header}"')
        lines.append("")
        for entity in bsw_mod.schedulable_entities:
            lines.append(f"FUNC(void, {bsw_mod.upper_prefix}_CODE) {entity.entry_name}(void);")
        lines.append("")
        lines.append(f"# define {bsw_mod.upper_prefix}_STOP_SEC_CODE")
        lines.append(f'# include "{bsw_mod.memmap_header}"')
        lines.append("")

    macro_eas = [
        ea for ea in bsw_mod.exclusive_areas
        if not ea.generate_function and ea.mechanism != "CUSTOM"
    ]
    func_eas = [
        ea for ea in bsw_mod.exclusive_areas
        if ea.generate_function or ea.mechanism == "CUSTOM"
    ]

    for ea in macro_eas:
        enter_expr, exit_expr = _exclusive_area_expr(ea)
        lines.append(
            f"# define SchM_Enter_{bsw_mod.api_name}_{ea.short_name}() {enter_expr}"
        )
        lines.append("")
        lines.append(
            f"# define SchM_Exit_{bsw_mod.api_name}_{ea.short_name}() {exit_expr}"
        )
        lines.append("")

    if func_eas:
        lines.append("# define RTE_START_SEC_CODE")
        lines.append('# include "Rte_MemMap.h"')
        lines.append("")
        for ea in func_eas:
            lines.append(
                f"FUNC(void, RTE_CODE) SchM_Enter_{bsw_mod.api_name}_{ea.short_name}(void);"
            )
            lines.append(
                f"FUNC(void, RTE_CODE) SchM_Exit_{bsw_mod.api_name}_{ea.short_name}(void);"
            )
        lines.append("")
        lines.append("# define RTE_STOP_SEC_CODE")
        lines.append('# include "Rte_MemMap.h"')
        lines.append("")

    lines.extend([
        "# ifdef __cplusplus",
        '} /* extern "C" */',
        "# endif /* __cplusplus */",
        "",
        f"#endif /* {guard} */",
        "",
    ])
    return "\n".join(lines)


def render_schm_type_h(bsw_mod: BswModuleSchmModel) -> str:
    """Render ``SchM_<ApiName>_Type.h`` for a single BSW module instance."""
    filename = f"SchM_{bsw_mod.api_name}_Type.h"
    guard = f"SCHM_{bsw_mod.upper_prefix}_TYPE_H"
    lines = _header_banner(
        filename,
        f"Module Interlink Types Header for BSW Module <{bsw_mod.api_name}>",
    )
    lines.extend([
        "",
        f"#ifndef {guard}",
        f"# define {guard}",
        "",
        "# ifdef __cplusplus",
        'extern "C" {',
        "# endif /* __cplusplus */",
        "",
        '# include "Rte_Type.h"',
        "",
        "# ifdef __cplusplus",
        '} /* extern "C" */',
        "# endif /* __cplusplus */",
        "",
        f"#endif /* {guard} */",
        "",
    ])
    return "\n".join(lines)
