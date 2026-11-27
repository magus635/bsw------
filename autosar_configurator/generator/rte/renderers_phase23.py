"""Deterministic ANSI/C99 renderers for Phase 2 SWC headers and Phase 3 multi-core Rte.c."""

import re
from typing import Dict, List, Optional, Sequence, Set, Tuple

from .model import (
    OsTaskScheduleModel,
    RteProjectModel,
    RteTypeDefEntry,
    SwcClientCallModel,
    SwcComponentModel,
    SwcDataEndpointModel,
)
from .renderers import _exclusive_area_expr, _header_banner


def _guard_ident(name: str) -> str:
    cleaned = re.sub(r"[^A-Za-z0-9_]", "_", (name or "").upper())
    return cleaned or "UNNAMED"


def _merge_swc_models(instances: Sequence[SwcComponentModel]) -> SwcComponentModel:
    """Merge multiple prototype instances of the same SwcType for a unified ``Rte_<Swc>.h``."""
    first = instances[0]
    if len(instances) == 1:
        return first
    seen_reads: Dict[Tuple[str, str], SwcDataEndpointModel] = {}
    seen_writes: Dict[Tuple[str, str], SwcDataEndpointModel] = {}
    seen_calls: Dict[Tuple[str, str], SwcClientCallModel] = {}
    seen_modes = {}
    seen_runs = {}
    seen_eas = {}
    for inst in instances:
        for r in inst.reads:
            seen_reads.setdefault((r.port_name, r.data_element_name), r)
        for w in inst.writes:
            seen_writes.setdefault((w.port_name, w.data_element_name), w)
        for c in inst.calls:
            seen_calls.setdefault((c.port_name, c.operation_name), c)
        for m in inst.mode_points:
            seen_modes.setdefault(m.port_name, m)
        for rn in inst.runnables:
            seen_runs.setdefault(rn.entry_name, rn)
        for ea in inst.exclusive_areas:
            seen_eas.setdefault(ea.short_name, ea)
    return SwcComponentModel(
        instance_name=first.instance_name,
        swc_type_name=first.swc_type_name,
        is_service=first.is_service,
        os_application=first.os_application,
        core_id=first.core_id,
        memmap_header=first.memmap_header,
        reads=list(seen_reads.values()),
        writes=list(seen_writes.values()),
        calls=list(seen_calls.values()),
        mode_points=list(seen_modes.values()),
        runnables=list(seen_runs.values()),
        exclusive_areas=list(seen_eas.values()),
    )


def render_rte_type_h_full(model: RteProjectModel) -> str:
    """Render full ``Rte_Type.h`` with topologically sorted AUTOSAR typedefs."""
    lines = _header_banner("Rte_Type.h", "Header file containing user defined AUTOSAR types and RTE structures")
    lines.extend([
        "",
        "#ifndef RTE_TYPE_H",
        "# define RTE_TYPE_H",
        "",
        '# include "Rte.h"',
        '# include "Rte_Cfg.h"',
        "",
        "# ifdef RTE_CORE",
        "typedef uint8 Rte_EventMaskType;",
        "# endif",
        "",
    ])

    for entry in model.rte_type_defs:
        guard = f"Rte_TypeDef_{entry.name}"
        lines.append(f"# ifndef {guard}")
        lines.append(f"#  define {guard}")
        if entry.category == "ARRAY":
            sz = entry.array_size or 1
            lines.append(f"typedef {entry.c_type} {entry.name}[{sz}];")
        elif entry.category in ("STRUCTURE", "UNION") and entry.fields:
            kw = "union" if entry.category == "UNION" else "struct"
            lines.append(f"typedef {kw}")
            lines.append("{")
            for fname, fc_type, fsize in entry.fields:
                if fsize is not None and fsize > 0:
                    lines.append(f"  {fc_type} {fname}[{fsize}];")
                else:
                    lines.append(f"  {fc_type} {fname};")
            lines.append(f"}} {entry.name};")
        else:
            lines.append(f"typedef {entry.c_type} {entry.name};")
        lines.append("# endif")
        for sym, lit_val in entry.enum_literals:
            lines.append(f"# ifndef {sym}")
            lines.append(f"#  define {sym} ({lit_val}U)")
            lines.append("# endif")
        lines.append("")

    # Also emit any mode typedef helpers referenced by SWC ModeSwitch points
    seen_mg: Set[str] = set()
    for swc in model.swc_components:
        for mp in swc.mode_points:
            mg = mp.mode_group_name
            if not mg or mg in seen_mg:
                continue
            seen_mg.add(mg)
            guard = f"Rte_TypeDef_Rte_ModeType_{mg}"
            lines.append(f"# ifndef {guard}")
            lines.append(f"#  define {guard}")
            lines.append(f"typedef uint8 Rte_ModeType_{mg};")
            lines.append("# endif")
            for idx, mname in enumerate(mp.modes):
                macro = f"RTE_MODE_{mg}_{mname}"
                lines.append(f"# ifndef {macro}")
                lines.append(f"#  define {macro} ({idx}U)")
                lines.append("# endif")
            lines.append("")

    lines.extend(["#endif /* RTE_TYPE_H */", ""])
    return "\n".join(lines)


def render_rte_data_handle_type_h(model: RteProjectModel) -> str:
    """Render ``Rte_DataHandleType.h`` for Phase 2 component contracts."""
    lines = _header_banner("Rte_DataHandleType.h", "Header file containing Data Handle type declarations")
    lines.extend([
        "",
        "#ifndef RTE_DATA_HANDLE_TYPE_H",
        "# define RTE_DATA_HANDLE_TYPE_H",
        "",
        '# include "Rte_Type.h"',
        "",
        "typedef struct",
        "{",
        "  uint8 _dummy;",
        "} Rte_DE_DummyType;",
        "",
        "#endif /* RTE_DATA_HANDLE_TYPE_H */",
        "",
    ])
    return "\n".join(lines)


def render_swc_type_h(swc: SwcComponentModel) -> str:
    """Render ``Components/Rte_<SwcType>_Type.h`` with mode & enum constants."""
    fn = f"Rte_{swc.swc_type_name}_Type.h"
    guard = f"RTE_{_guard_ident(swc.swc_type_name)}_TYPE_H"
    lines = _header_banner(fn, f"Application types header file for SW-C '{swc.swc_type_name}'")
    lines.extend([
        "",
        f"#ifndef {guard}",
        f"# define {guard}",
        "",
        '# ifdef __cplusplus',
        'extern "C" {',
        "# endif",
        "",
        '# include "Rte_Type.h"',
        "",
    ])
    for mp in swc.mode_points:
        mg = mp.mode_group_name
        for idx, mname in enumerate(mp.modes):
            macro = f"RTE_MODE_{mg}_{mname}"
            lines.append(f"# ifndef {macro}")
            lines.append(f"#  define {macro} ({idx}U)")
            lines.append("# endif")
        lines.append("")
    lines.extend([
        "# ifdef __cplusplus",
        "} /* extern \"C\" */",
        "# endif",
        "",
        f"#endif /* {guard} */",
        "",
    ])
    return "\n".join(lines)


def _cs_param_list_str(call: SwcClientCallModel, appl_var_macro: str) -> str:
    if not call.arguments:
        return "void"
    parts: List[str] = []
    for arg in call.arguments:
        d = (arg.direction or "IN").upper()
        if d == "OUT":
            parts.append(f"P2VAR({arg.c_type}, AUTOMATIC, {appl_var_macro}) {arg.name}")
        elif d == "INOUT":
            parts.append(f"P2VAR({arg.c_type}, AUTOMATIC, {appl_var_macro}) {arg.name}")
        else:
            parts.append(f"{arg.c_type} {arg.name}")
    return ", ".join(parts)


def render_swc_h(swc: SwcComponentModel, shared_buffers_for_swc: Optional[Sequence[SwcDataEndpointModel]] = None) -> str:
    """Render Phase 2 contract header ``Components/Rte_<SwcType>.h``."""
    fn = f"Rte_{swc.swc_type_name}.h"
    swc_upper = _guard_ident(swc.swc_type_name)
    guard = f"RTE_{swc_upper}_H"
    appl_var = f"RTE_{swc_upper}_APPL_VAR"
    code_sec = f"{swc.swc_type_name}_START_SEC_CODE"
    stop_sec = f"{swc.swc_type_name}_STOP_SEC_CODE"
    memmap_hdr = swc.memmap_header or f"{swc.swc_type_name}_MemMap.h"

    lines = _header_banner(fn, f"Application header file for SW-C '{swc.swc_type_name}'")
    lines.extend([
        "",
        f"#ifndef {guard}",
        f"# define {guard}",
        "",
        "# ifndef RTE_CORE",
        "#  ifdef RTE_APPLICATION_HEADER_FILE",
        "#   error Multiple application header files included.",
        "#  endif",
        "#  define RTE_APPLICATION_HEADER_FILE",
        "#  ifndef RTE_PTR2ARRAYBASETYPE_PASSING",
        "#   define RTE_PTR2ARRAYBASETYPE_PASSING",
        "#  endif",
        "# endif",
        "",
        "# ifdef __cplusplus",
        'extern "C" {',
        "# endif",
        "",
        f'# include "Rte_{swc.swc_type_name}_Type.h"',
        '# include "Rte_DataHandleType.h"',
        "",
    ])

    # Shared inter-SWC variables visible when !RTE_CORE or RTE_CORE
    shared_vars: Dict[str, SwcDataEndpointModel] = {}
    for ep in list(swc.reads) + list(swc.writes) + list(shared_buffers_for_swc or []):
        if ep.binding_kind == "INTER_SWC" and ep.shared_var_name:
            shared_vars.setdefault(ep.shared_var_name, ep)

    if shared_vars:
        lines.extend([
            "# define RTE_START_SEC_VAR_INIT_UNSPECIFIED",
            '# include "Rte_MemMap.h"',
            "",
        ])
        for vname in sorted(shared_vars):
            ep = shared_vars[vname]
            lines.append(f"extern VAR({ep.c_type}, RTE_VAR_INIT) {vname};")
        lines.extend([
            "",
            "# define RTE_STOP_SEC_VAR_INIT_UNSPECIFIED",
            '# include "Rte_MemMap.h"',
            "",
        ])

    # Init value macros
    lines.append("# ifndef RTE_CORE")
    for ep in list(swc.writes) + list(swc.reads):
        if not ep.is_array:
            lines.append(f"#  define Rte_InitValue_{ep.port_name}_{ep.data_element_name} ({ep.init_value})")
    lines.append("# endif")
    lines.append("")

    # Function prototypes for COM & C/S endpoints
    com_eps = [ep for ep in list(swc.reads) + list(swc.writes) if ep.binding_kind == "COM"]
    if com_eps or swc.calls:
        lines.extend([
            "# define RTE_START_SEC_CODE",
            '# include "Rte_MemMap.h"',
            "",
        ])
        for ep in swc.reads:
            if ep.binding_kind != "COM":
                continue
            full_fn = f"Rte_Read_{swc.swc_type_name}_{ep.port_name}_{ep.data_element_name}"
            if ep.is_array:
                lines.append(f"FUNC(Std_ReturnType, RTE_CODE) {full_fn}({ep.c_type} data);")
            else:
                lines.append(f"FUNC(Std_ReturnType, RTE_CODE) {full_fn}(P2VAR({ep.c_type}, AUTOMATIC, {appl_var}) data);")
        for ep in swc.writes:
            if ep.binding_kind != "COM":
                continue
            full_fn = f"Rte_Write_{swc.swc_type_name}_{ep.port_name}_{ep.data_element_name}"
            lines.append(f"FUNC(Std_ReturnType, RTE_CODE) {full_fn}({ep.c_type} data);")
        for call in swc.calls:
            full_fn = f"Rte_Call_{swc.swc_type_name}_{call.port_name}_{call.operation_name}"
            params_s = _cs_param_list_str(call, appl_var)
            lines.append(f"FUNC(Std_ReturnType, RTE_CODE) {full_fn}({params_s});")
        lines.extend([
            "",
            "# define RTE_STOP_SEC_CODE",
            '# include "Rte_MemMap.h"',
            "",
        ])

    # Shorthand macros & inline shared/unconnected macros under !RTE_CORE
    lines.append("# ifndef RTE_CORE")
    lines.append("/* Rte_Read_<p>_<d> */")
    for ep in swc.reads:
        short_m = f"Rte_Read_{ep.port_name}_{ep.data_element_name}"
        full_m = f"Rte_Read_{swc.swc_type_name}_{ep.port_name}_{ep.data_element_name}"
        lines.append(f"#  define {short_m} {full_m}")
        if ep.binding_kind == "INTER_SWC" and ep.shared_var_name:
            if ep.is_array:
                lines.append(f"#  define {full_m}(data) ((void)(data), (Std_ReturnType)RTE_E_OK)")
            else:
                lines.append(f"#  define {full_m}(data) (*(data) = {ep.shared_var_name}, ((Std_ReturnType)RTE_E_OK))")
        elif ep.binding_kind == "UNCONNECTED":
            if ep.is_array:
                lines.append(f"#  define {full_m}(data) ((void)(data), (Std_ReturnType)RTE_E_UNCONNECTED)")
            else:
                lines.append(f"#  define {full_m}(data) (*(data) = ({ep.init_value}), ((Std_ReturnType)RTE_E_UNCONNECTED))")

    lines.append("")
    lines.append("/* Rte_Write_<p>_<d> */")
    for ep in swc.writes:
        short_m = f"Rte_Write_{ep.port_name}_{ep.data_element_name}"
        full_m = f"Rte_Write_{swc.swc_type_name}_{ep.port_name}_{ep.data_element_name}"
        lines.append(f"#  define {short_m} {full_m}")
        if ep.binding_kind == "INTER_SWC" and ep.shared_var_name:
            if not ep.is_array:
                lines.append(f"#  define {full_m}(data) ({ep.shared_var_name} = (data), ((Std_ReturnType)RTE_E_OK))")
        elif ep.binding_kind == "UNCONNECTED":
            lines.append(f"#  define {full_m}(data) ((void)(data), (Std_ReturnType)RTE_E_OK)")

    if swc.calls:
        lines.append("")
        lines.append("/* Rte_Call_<p>_<o> */")
        for call in swc.calls:
            short_m = f"Rte_Call_{call.port_name}_{call.operation_name}"
            full_m = f"Rte_Call_{swc.swc_type_name}_{call.port_name}_{call.operation_name}"
            lines.append(f"#  define {short_m} {full_m}")

    if swc.mode_points:
        lines.append("")
        lines.append("/* Rte_Mode / Rte_Switch */")
        for mp in swc.mode_points:
            init_m = f"RTE_MODE_{mp.mode_group_name}_{mp.initial_mode}" if mp.initial_mode else "0U"
            if mp.kind == "SWITCH":
                lines.append(f"#  define Rte_Switch_{mp.port_name}_{mp.mode_group_name}(mode) ((void)(mode), (Std_ReturnType)RTE_E_OK)")
            else:
                lines.append(f"#  define Rte_Mode_{mp.port_name}_{mp.mode_group_name}() ({init_m})")

    if swc.exclusive_areas:
        lines.append("")
        lines.append("/* Rte_Enter / Rte_Exit */")
        for ea in swc.exclusive_areas:
            enter_expr, exit_expr = _exclusive_area_expr(ea)
            lines.append(f"#  define Rte_Enter_{ea.short_name}() {enter_expr}")
            lines.append(f"#  define Rte_Exit_{ea.short_name}() {exit_expr}")

    lines.extend(["# endif /* !defined(RTE_CORE) */", ""])

    # Runnable entities
    if swc.runnables:
        lines.extend([
            f"# define {code_sec}",
            f'# include "{memmap_hdr}"',
            "",
            "# ifndef RTE_CORE",
        ])
        for rn in swc.runnables:
            lines.append(f"#  define RTE_RUNNABLE_{rn.short_name} {rn.entry_name}")
        lines.extend(["# endif", ""])
        for rn in swc.runnables:
            params: List[str] = []
            for idx, pt in enumerate(getattr(rn, "port_arg_types", []) or []):
                params.append(f"{pt} parg{idx}")
            for arg in getattr(rn, "arguments", []) or []:
                d = (arg.direction or "IN").upper()
                if d in ("OUT", "INOUT"):
                    params.append(f"P2VAR({arg.c_type}, AUTOMATIC, {appl_var}) {arg.name}")
                else:
                    params.append(f"{arg.c_type} {arg.name}")
            param_s = ", ".join(params) if params else "void"
            ret_t = getattr(rn, "return_type", "void") or "void"
            lines.append(f"FUNC({ret_t}, {swc.swc_type_name}_CODE) {rn.entry_name}({param_s});")
        lines.extend([
            "",
            f"# define {stop_sec}",
            f'# include "{memmap_hdr}"',
            "",
        ])

    lines.extend([
        "# ifdef __cplusplus",
        "} /* extern \"C\" */",
        "# endif",
        "",
        f"#endif /* {guard} */",
        "",
    ])
    return "\n".join(lines)


def _render_task_function(task: OsTaskScheduleModel) -> List[str]:
    lines = [
        "/**********************************************************************************************************************",
        f" * Task:     {task.task_name}",
        f" * Priority: {task.priority}",
        f" * Type:     {task.task_type}",
        " *********************************************************************************************************************/",
        f"TASK({task.task_name})",
        "{",
    ]
    if task.task_type == "EXTENDED" and task.os_events:
        mask_expr = " | ".join(task.os_events)
        lines.extend([
            "  EventMaskType ev = 0U;",
            "  for (;;)",
            "  {",
            f"    (void)WaitEvent({mask_expr});",
            f"    (void)GetEvent({task.task_name}, &ev);",
            "    (void)ClearEvent(ev);",
        ])
        for call in task.calls:
            lines.append(f"    {call.symbol}();")
        lines.append("  }")
    else:
        for call in task.calls:
            lines.append(f"  {call.symbol}();")
    lines.extend([
        "  (void)TerminateTask();",
        "}",
        "",
    ])
    return lines


def render_rte_c(model: RteProjectModel) -> str:
    """Render Phase 3 ``Rte.c`` containing lifecycle APIs and core startup logic."""
    lines = _header_banner("Rte.c", "RTE core lifecycle, SchM timing control, and shared SchM functions")
    lines.extend([
        "",
        "#define RTE_CORE",
        "",
        '#include "Rte.h"',
        '#include "Rte_Main.h"',
        '#include "Rte_Cfg.h"',
        '#include "Rte_Cbk.h"',
        '#include "Rte_Type.h"',
        '#include "Os.h"',
    ])
    for bsw in model.bsw_modules:
        lines.append(f'#include "SchM_{bsw.api_name}.h"')

    seen_swc_hdrs: Set[str] = set()
    for swc in model.swc_components:
        if swc.swc_type_name not in seen_swc_hdrs:
            seen_swc_hdrs.add(swc.swc_type_name)
            lines.append(f'#include "Components/Rte_{swc.swc_type_name}.h"')
    lines.append("")

    # Lifecycle state flags
    lines.extend([
        "#define RTE_STATE_UNINIT      (0U)",
        "#define RTE_STATE_SCHM_START  (1U)",
        "#define RTE_STATE_SCHM_INIT   (2U)",
        "#define RTE_STATE_INIT        (3U)",
        "",
        "VAR(uint8, RTE_VAR_INIT) Rte_StartTiming_InitState = RTE_STATE_UNINIT;",
    ])

    core_ids: List[int] = sorted(
        {c.core_id for c in model.swc_components}
        | {t.core_id for t in model.task_schedules}
        | {a.core_id for a in model.os_activations}
        | {0}
    )
    if model.meta.enable_multi_core and len(model.os_cores) > 1:
        core_ids = sorted(set(core_ids) | set(range(len(model.os_cores))))

    for cid in core_ids:
        lines.append(f"VAR(uint8, RTE_VAR_INIT) Rte_InitState_Core{cid} = RTE_STATE_UNINIT;")
    lines.append("")

    # SchM_Start / SchM_Init / SchM_StartTiming / SchM_StartTimingCoreX / Rte_Start / Rte_Stop / SchM_Deinit
    def _emit_core_guard(cid: int, body_lines: List[str]) -> None:
        if len(core_ids) > 1:
            lines.append(f"  if (id == (uint32){cid}U)")
            lines.append("  {")
            lines.extend([f"  {b}" for b in body_lines])
            lines.append("  }")
        else:
            lines.extend(body_lines)

    lines.extend(["FUNC(void, RTE_CODE) SchM_Start(void)", "{"])
    if len(core_ids) > 1:
        lines.append("  uint32 id = (uint32)GetCoreID();")
    for cid in core_ids:
        _emit_core_guard(cid, [f"  Rte_InitState_Core{cid} = RTE_STATE_SCHM_START;"])
    lines.extend(["}", ""])

    lines.extend(["FUNC(void, RTE_CODE) SchM_Init(void)", "{"])
    if len(core_ids) > 1:
        lines.append("  uint32 id = (uint32)GetCoreID();")
    for cid in core_ids:
        _emit_core_guard(cid, [f"  Rte_InitState_Core{cid} = RTE_STATE_SCHM_INIT;"])
    lines.extend(["}", ""])

    # Per-core SchM_StartTiming helpers
    if model.meta.enable_multi_core and len(model.os_cores) > 1:
        for idx, suffix in enumerate(model.os_cores):
            lines.extend([f"FUNC(void, RTE_CODE) SchM_StartTiming{suffix}(void)", "{"])
            acts = [a for a in model.os_activations if a.core_id == idx and a.is_bsw]
            schtbls: Set[str] = set()
            for a in acts:
                if a.alarm_name:
                    lines.append(f"  (void)SetRelAlarm({a.alarm_name}, (TickType)1U, (TickType){max(1, int(round(a.period_ms)))}U);")
                elif a.schedule_table_name and a.schedule_table_name not in schtbls:
                    schtbls.add(a.schedule_table_name)
                    lines.append(f"  (void)StartScheduleTableRel({a.schedule_table_name}, (TickType)1U);")
            lines.extend(["}", ""])

        lines.extend(["FUNC(void, RTE_CODE) SchM_StartTiming(void)", "{", "  uint32 id = (uint32)GetCoreID();"])
        for idx, suffix in enumerate(model.os_cores):
            lines.extend([
                f"  if (id == (uint32){idx}U)",
                "  {",
                f"    SchM_StartTiming{suffix}();",
                "  }",
            ])
        lines.extend(["}", ""])
    else:
        lines.extend(["FUNC(void, RTE_CODE) SchM_StartTiming(void)", "{"])
        schtbls: Set[str] = set()
        for a in model.os_activations:
            if not a.is_bsw:
                continue
            if a.alarm_name:
                lines.append(f"  (void)SetRelAlarm({a.alarm_name}, (TickType)1U, (TickType){max(1, int(round(a.period_ms)))}U);")
            elif a.schedule_table_name and a.schedule_table_name not in schtbls:
                schtbls.add(a.schedule_table_name)
                lines.append(f"  (void)StartScheduleTableRel({a.schedule_table_name}, (TickType)1U);")
        lines.extend(["}", ""])

    # Rte_Start
    lines.extend(["FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void)", "{"])
    if len(core_ids) > 1:
        lines.append("  uint32 id = (uint32)GetCoreID();")
    for cid in core_ids:
        body: List[str] = []
        for t in model.task_schedules:
            if t.core_id == cid and t.is_init_task:
                body.append(f"  (void)ActivateTask({t.task_name});")
        for a in model.os_activations:
            if a.core_id == cid and not a.is_bsw and a.alarm_name:
                body.append(f"  (void)SetRelAlarm({a.alarm_name}, (TickType)1U, (TickType){max(1, int(round(a.period_ms)))}U);")
        if cid == 0:
            body.append("  Rte_StartTiming_InitState = RTE_STATE_INIT;")
        body.append(f"  Rte_InitState_Core{cid} = RTE_STATE_INIT;")
        _emit_core_guard(cid, body)
    lines.extend(["  return RTE_E_OK;", "}", ""])

    # Rte_Stop
    lines.extend(["FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void)", "{"])
    if len(core_ids) > 1:
        lines.append("  uint32 id = (uint32)GetCoreID();")
    for cid in core_ids:
        body = []
        if cid == 0:
            body.append("  Rte_StartTiming_InitState = RTE_STATE_UNINIT;")
        for a in model.os_activations:
            if a.core_id == cid and not a.is_bsw and a.alarm_name:
                body.append(f"  (void)CancelAlarm({a.alarm_name});")
        body.append(f"  Rte_InitState_Core{cid} = RTE_STATE_SCHM_INIT;")
        _emit_core_guard(cid, body)
    lines.extend(["  return RTE_E_OK;", "}", ""])

    # SchM_Deinit
    lines.extend(["FUNC(void, RTE_CODE) SchM_Deinit(void)", "{"])
    if len(core_ids) > 1:
        lines.append("  uint32 id = (uint32)GetCoreID();")
    for cid in core_ids:
        _emit_core_guard(cid, [f"  Rte_InitState_Core{cid} = RTE_STATE_UNINIT;"])
    lines.extend(["}", ""])

    # Rte_InitMemory & Rte_InitMemory_<OsApplication>
    if not model.meta.disable_rte_init_memory:
        for app_name in model.os_applications:
            lines.extend([f"FUNC(void, RTE_CODE) Rte_InitMemory_{app_name}(void)", "{"])
            for buf in model.shared_buffers:
                if buf.owner_os_application == app_name and "[" not in buf.c_type:
                    lines.append(f"  {buf.var_name} = {buf.init_value};")
            lines.extend(["}", ""])
        lines.extend(["FUNC(void, RTE_CODE) Rte_InitMemory(void)", "{"])
        for app_name in model.os_applications:
            lines.append(f"  Rte_InitMemory_{app_name}();")
        lines.extend(["}", ""])

    # Function-mode ExclusiveAreas
    for bsw in model.bsw_modules:
        for ea in bsw.exclusive_areas:
            if not ea.generate_function:
                continue
            enter_expr, exit_expr = _exclusive_area_expr(ea)
            lines.extend([
                f"FUNC(void, RTE_CODE) SchM_Enter_{bsw.api_name}_{ea.short_name}(void)",
                "{",
                f"  {enter_expr};",
                "}",
                "",
                f"FUNC(void, RTE_CODE) SchM_Exit_{bsw.api_name}_{ea.short_name}(void)",
                "{",
                f"  {exit_expr};",
                "}",
                "",
            ])

    return "\n".join(lines)


def render_rte_osapp_c(model: RteProjectModel, os_app: str) -> str:
    """Render ``Rte_<OsApplication>.c`` containing SWC API implementations and OS TASK bodies."""
    fn = f"Rte_{os_app}.c"
    lines = _header_banner(fn, f"RTE OS-Application partition implementation for '{os_app}'")
    lines.extend([
        "",
        "#define RTE_CORE",
        "",
        '#include "Rte.h"',
        '#include "Rte_Main.h"',
        '#include "Rte_Cfg.h"',
        '#include "Rte_Type.h"',
        '#include "Os.h"',
    ])

    app_swcs = [s for s in model.swc_components if s.os_application == os_app]
    app_tasks = [t for t in model.task_schedules if t.os_application == os_app]
    app_bufs = [b for b in model.shared_buffers if b.owner_os_application == os_app]

    uses_com = any(
        ep.binding_kind == "COM"
        for swc in app_swcs
        for ep in (list(swc.reads) + list(swc.writes))
    )
    if uses_com and model.has_com:
        lines.append('#include "Com.h"')

    for bsw in model.bsw_modules:
        lines.append(f'#include "SchM_{bsw.api_name}.h"')

    seen_swc_types: Set[str] = set()
    for swc in model.swc_components:
        if swc.swc_type_name not in seen_swc_types:
            seen_swc_types.add(swc.swc_type_name)
            lines.append(f'#include "Components/Rte_{swc.swc_type_name}.h"')
    lines.append("")

    # Shared buffer definitions owned by this OsApplication
    if app_bufs:
        lines.extend([
            "#define RTE_START_SEC_VAR_INIT_UNSPECIFIED",
            '#include "Rte_MemMap.h"',
            "",
        ])
        for buf in app_bufs:
            lines.append(f"VAR({buf.c_type}, RTE_VAR_INIT) {buf.var_name} = {buf.init_value};")
        lines.extend([
            "",
            "#define RTE_STOP_SEC_VAR_INIT_UNSPECIFIED",
            '#include "Rte_MemMap.h"',
            "",
        ])

    # Deduplicate function definitions by C symbol (in case multiple instances share SwcType)
    emitted_fns: Set[str] = set()
    for swc in app_swcs:
        swc_upper = _guard_ident(swc.swc_type_name)
        appl_var = f"RTE_{swc_upper}_APPL_VAR"

        for ep in swc.writes:
            if ep.binding_kind != "COM":
                continue
            fname = f"Rte_Write_{swc.swc_type_name}_{ep.port_name}_{ep.data_element_name}"
            if fname in emitted_fns:
                continue
            emitted_fns.add(fname)
            arg_ref = "(const void *)(data)" if ep.is_array else "(const void *)(&data)"
            lines.extend([
                f"FUNC(Std_ReturnType, RTE_CODE) {fname}({ep.c_type} data)",
                "{",
                f"  Std_ReturnType ret = Com_SendSignal({ep.com_signal_macro}, {arg_ref});",
                "  return ret;",
                "}",
                "",
            ])

        for ep in swc.reads:
            if ep.binding_kind != "COM":
                continue
            fname = f"Rte_Read_{swc.swc_type_name}_{ep.port_name}_{ep.data_element_name}"
            if fname in emitted_fns:
                continue
            emitted_fns.add(fname)
            if ep.is_array:
                lines.extend([
                    f"FUNC(Std_ReturnType, RTE_CODE) {fname}({ep.c_type} data)",
                    "{",
                    f"  return Com_ReceiveSignal({ep.com_signal_macro}, (void *)(data));",
                    "}",
                    "",
                ])
            else:
                lines.extend([
                    f"FUNC(Std_ReturnType, RTE_CODE) {fname}(P2VAR({ep.c_type}, AUTOMATIC, {appl_var}) data)",
                    "{",
                    f"  {ep.c_type} local_val = {ep.init_value};",
                    f"  Std_ReturnType ret = Com_ReceiveSignal({ep.com_signal_macro}, (void *)(&local_val));",
                    "  *(data) = local_val;",
                    "  return ret;",
                    "}",
                    "",
                ])

        for call in swc.calls:
            fname = f"Rte_Call_{swc.swc_type_name}_{call.port_name}_{call.operation_name}"
            if fname in emitted_fns:
                continue
            emitted_fns.add(fname)
            params_s = _cs_param_list_str(call, appl_var)
            lines.append(f"FUNC(Std_ReturnType, RTE_CODE) {fname}({params_s})")
            lines.append("{")
            if call.connected and call.server_symbol:
                call_args = list(call.port_defined_args) + [a.name for a in call.arguments]
                arg_str = ", ".join(call_args)
                if call.has_errors:
                    lines.append(f"  return {call.server_symbol}({arg_str});")
                else:
                    lines.append(f"  {call.server_symbol}({arg_str});")
                    lines.append("  return RTE_E_OK;")
            else:
                for a in call.arguments:
                    lines.append(f"  (void){a.name};")
                lines.append("  return RTE_E_UNCONNECTED;")
            lines.extend(["}", ""])

    for task in app_tasks:
        lines.extend(_render_task_function(task))

    return "\n".join(lines)
