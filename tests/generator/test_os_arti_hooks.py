"""ARTI hook tracing (openspec change add-arti-hook-tracing): the ArtiHook description in Os_Arti.arxml,
the kernel wrapper header Os_ArtiHooks.h and the strict mock Os_Arti_Mock.h, all generated from
templates/Os/Os_ArtiEvents.m with the synthetic Os configuration of os_arti_fixture.

The compile checks use arm-none-eabi-gcc and are skipped when it is not installed.
"""
import re
import shutil
import subprocess
from pathlib import Path

import pytest

from autosar_configurator.generator.generator import CodeGenerator

from .os_arti_fixture import build_os_config

etree = pytest.importorskip("lxml.etree")

ROOT = Path(__file__).resolve().parents[2]
TPL = ROOT / "templates" / "Os"
APP_COMMON = ROOT / "doc" / "ARTI" / "Os_AppCommon.m"
NS = {"a": "http://autosar.org/schema/r4.0"}
A = "{http://autosar.org/schema/r4.0}"
FILES = ("Os_Arti.arxml", "Os_ArtiEvents.m", "Os_ArtiCfg.h", "Os_ArtiHooks.h", "Os_Arti_Mock.h", "Os_Arti_Mock.c")

ENHANCED_TASK = ["OsTask_Activate", "OsTask_Start", "OsTask_Preempt", "OsTask_Resume", "OsTask_Wait",
                 "OsTask_Release", "OsTask_Continue", "OsTask_Terminate"]
STANDARD_TASK = ["OsTask_Activate", "OsTask_Start", "OsTask_Preempt", "OsTask_Wait", "OsTask_Release",
                 "OsTask_Terminate"]


def _gcc():
    found = shutil.which("arm-none-eabi-gcc")
    if found:
        return found
    for p in Path("C:/Program Files (x86)").glob("Arm GNU Toolchain arm-none-eabi/*/bin/arm-none-eabi-gcc.exe"):
        return str(p)
    return None


GCC = _gcc()
needs_gcc = pytest.mark.skipif(GCC is None, reason="arm-none-eabi-gcc not installed")


def render(tmp_path, use_arti=True, **arti):
    module_def, mgr = build_os_config(use_arti=use_arti, arti=arti)
    tpl = tmp_path / "tpl" / "Os"
    tpl.mkdir(parents=True)
    for name in FILES:
        shutil.copy(TPL / name, tpl / name)
    shutil.copy(APP_COMMON, tpl / APP_COMMON.name)
    assert CodeGenerator(module_def, mgr.configuration, project_template_dir=tmp_path / "tpl").generate_all(
        tmp_path / "out")
    return tmp_path / "out" / "Os"


def _def(el):
    return el.findtext("a:DEFINITION-REF", namespaces=NS)


def _param(c, name):
    for p in c.xpath("a:PARAMETER-VALUES/*", namespaces=NS):
        if _def(p).endswith("/" + name):
            return p.findtext("a:VALUE", namespaces=NS)
    return None


def _ref(c, name):
    for r in c.xpath("a:REFERENCE-VALUES/*", namespaces=NS):
        if _def(r).endswith("/" + name):
            return r.findtext("a:VALUE-REF", namespaces=NS)
    return None


def described_hooks(out):
    """{(context, class, instance, event): (event type map, instance type map)} of Os_Arti.arxml"""
    text = (out / "Os_Arti.arxml").read_text(encoding="utf-8")
    if "<AR-PACKAGES>" not in text:
        return {}
    root = etree.fromstring(text.encode("utf-8"))
    hooks = {}
    for c in root.iter(A + "ECUC-CONTAINER-VALUE"):
        if _def(c).endswith("/ArtiValues/ArtiHook"):
            key = tuple(_param(c, p) for p in ("ArtiHookContext", "ArtiHookClass", "ArtiHookInstance",
                                                "ArtiHookEventName"))
            hooks[key] = (_ref(c, "ArtiHookEventParameterTypeRef"), _ref(c, "ArtiHookInstanceParameterTypeRef"))
    return hooks


def header_tokens(out):
    """(context, class, instance, event) of every OS_ARTI_EV_* macro of Os_ArtiHooks.h"""
    text = (out / "include" / "Os_ArtiHooks.h").read_text(encoding="utf-8")
    return {tuple(m.groups()) for m in re.finditer(
        r"ARTI_TRACE\((\w+), (\w+), (\w+), \(core\), (\w+), \(param\)\)", text)}


def mock_table(out):
    text = (out / "include" / "Os_Arti_Mock.h").read_text(encoding="utf-8")
    return [m.groups() for m in re.finditer(r"ARTI_MOCK_EVENT (\d+) (\w+) (\w+) (\w+)", text)]


def by_class(hooks):
    out = {}
    for ctx, cls, inst, ev in hooks:
        out.setdefault(cls, []).append(ev)
    return out


# --------------------------------------------------------------------------- ARTI description

def test_enhanced_model_is_the_default(tmp_path):
    hooks = by_class(described_hooks(render(tmp_path)))
    assert hooks["AR_CP_OSARTI_TASK"] == ENHANCED_TASK
    assert hooks["AR_CP_OSARTI_CAT2ISR"] == ["OsCat2Isr_Activate", "OsCat2Isr_Start", "OsCat2Isr_Preempt",
                                             "OsCat2Isr_Resume", "OsCat2Isr_Stop"]
    assert hooks["AR_CP_OS_APPLICATION"] == ["OsApplication_Start", "OsApplication_Restart",
                                             "OsApplication_AllowAccess", "OsApplication_Terminate"]
    assert hooks["AR_CP_OS_SPINLOCK"] == ["OsSpinlock_Locked", "OsSpinlock_Released"]
    assert "AR_CP_OS_SERVICECALLS" not in hooks, "service calls are off by default"


def test_standard_model(tmp_path):
    hooks = by_class(described_hooks(render(tmp_path, OsVendorArtiStateModel="STANDARD")))
    assert hooks["AR_CP_OS_TASK"] == STANDARD_TASK
    assert hooks["AR_CP_OS_CAT2ISR"] == ["OsCat2Isr_Start", "OsCat2Isr_Stop"]
    assert "AR_CP_OSARTI_TASK" not in hooks and "AR_CP_OSARTI_CAT2ISR" not in hooks


def test_hooks_follow_the_configured_os_hooks(tmp_path):
    """Fixture: OsErrorHook, OsStartupHook; App_Core0 ErrorHook; App_Core1 StartupHook, ShutdownHook."""
    hooks = by_class(described_hooks(render(tmp_path)))["AR_CP_OS_HOOK"]
    assert hooks == ["OsHook_ErrorHook_Start", "OsHook_ErrorHook_Return",
                     "OsHook_StartupHook_Start", "OsHook_StartupHook_Return",
                     "OsHook_ErrorHook_App_Core0_Start", "OsHook_ErrorHook_App_Core0_Return",
                     "OsHook_StartupHook_App_Core1_Start", "OsHook_StartupHook_App_Core1_Return",
                     "OsHook_ShutdownHook_App_Core1_Start", "OsHook_ShutdownHook_App_Core1_Return"]


def test_service_calls(tmp_path):
    hooks = described_hooks(render(tmp_path, OsVendorArtiTraceServiceCalls=True))
    sc = {ev: tm for (ctx, cls, inst, ev), (tm, _) in hooks.items() if cls == "AR_CP_OS_SERVICECALLS"}
    assert all(ctx == "SPRVSR" for ctx, cls, *_ in hooks if cls == "AR_CP_OS_SERVICECALLS")
    assert sc["OsServiceCall_ActivateTask_Start"].endswith("/TM_TaskId")
    assert sc["OsServiceCall_ActivateTask_Return"].endswith("/TM_LastError")
    assert sc["OsServiceCall_GetSpinlock_Start"].endswith("/TM_SpinlockId")
    assert sc["OsServiceCall_GetResource_Start"].endswith("/TM_ResourceId")
    assert "OsServiceCall_StartOS_Start" in sc and "OsServiceCall_StartOS_Return" not in sc
    assert "OsServiceCall_StartNonAutosarCore_Start" not in sc, "not implemented by the kernel"


@pytest.mark.parametrize("cls, switch", [("AR_CP_OS_APPLICATION", "Application"), ("AR_CP_OSARTI_TASK", "Task"),
                                         ("AR_CP_OSARTI_CAT2ISR", "Cat2Isr"), ("AR_CP_OS_SPINLOCK", "Spinlock"),
                                         ("AR_CP_OS_HOOK", "Hook")])
def test_class_switch(tmp_path, cls, switch):
    hooks = by_class(described_hooks(render(tmp_path, **{f"OsVendorArtiTrace{switch}": False})))
    assert cls not in hooks
    assert len(hooks) == 4


def test_arti_disabled(tmp_path):
    out = render(tmp_path, use_arti=False)
    assert described_hooks(out) == {}
    cfg = (out / "include" / "Os_ArtiCfg.h").read_text(encoding="utf-8")
    assert "#define OS_ARTI_ON                      (STD_OFF)" in cfg
    assert "#define OS_ARTI_TRACE_TASK              (STD_OFF)" in cfg
    hdr = (out / "include" / "Os_ArtiHooks.h").read_text(encoding="utf-8")
    assert "ARTI_TRACE(" not in hdr.split("Kernel wrapper macros")[1]
    assert '#include "Os_Arti.h"' not in hdr


def test_hooks_are_referenced_by_the_os_instance(tmp_path):
    root = etree.parse(str(render(tmp_path) / "Os_Arti.arxml")).getroot()
    hooks = {c.findtext("a:SHORT-NAME", namespaces=NS) for c in root.iter(A + "ECUC-CONTAINER-VALUE")
             if _def(c).endswith("/ArtiValues/ArtiHook")}
    (os_inst,) = [c for c in root.iter(A + "ECUC-CONTAINER-VALUE") if _def(c).endswith("/ArtiOs/ArtiOsInstance")]
    refs = {r.findtext("a:VALUE-REF", namespaces=NS).rsplit("/", 1)[1] for r in os_inst.xpath(
        "a:REFERENCE-VALUES/*", namespaces=NS) if _def(r).endswith("/ArtiOsInstanceHookRef")}
    assert hooks and refs == hooks


def test_hook_type_maps_exist_and_fit_in_16_bits(tmp_path):
    """ECUC_Arti_00024: inputs of a type map used by an ArtiHook are within 0..65535."""
    out = render(tmp_path, OsVendorArtiTraceServiceCalls=True)
    root = etree.parse(str(out / "Os_Arti.arxml")).getroot()
    maps = {}
    for tm in root.iter(A + "ECUC-CONTAINER-VALUE"):
        if _def(tm).endswith("/ArtiValues/ArtiParameterTypeMap"):
            maps[tm.findtext("a:SHORT-NAME", namespaces=NS)] = [
                _param(p, "ArtiParameterTypeMapPairInput") for p in tm.xpath("a:SUB-CONTAINERS/*", namespaces=NS)]
    used = {ref.rsplit("/", 1)[1] for refs in described_hooks(out).values() for ref in refs if ref}
    assert used >= {"TM_ArtiCoreIndex", "TM_TaskId", "TM_Isr2Id", "TM_ApplicationId", "TM_SpinlockId",
                    "TM_LastError", "TM_ResourceId"}
    for name in used:
        assert maps[name], name
        assert all(v is not None and 0 <= int(v) <= 65535 for v in maps[name]), (name, maps[name])


def test_object_id_type_maps(tmp_path):
    root = etree.parse(str(render(tmp_path) / "Os_Arti.arxml")).getroot()

    def pairs(name):
        (tm,) = [t for t in root.iter(A + "ECUC-CONTAINER-VALUE") if t.findtext("a:SHORT-NAME", namespaces=NS) == name]
        return {_param(p, "ArtiParameterTypeMapPairOutput"): int(_param(p, "ArtiParameterTypeMapPairInput"))
                for p in tm.xpath("a:SUB-CONTAINERS/*", namespaces=NS)}

    assert pairs("TM_ArtiCoreIndex") == {"Core0": 0, "Core1": 1}
    assert pairs("TM_SpinlockId") == {"Spin_Shared": 0, "INVALID_SPINLOCK": 1}
    assert pairs("TM_ResourceId") == {"Res_Shared": 0, "INVALID_RESOURCE": 1}
    assert pairs("TM_ProtectionReaction")["PRO_SHUTDOWN"] == 4


# --------------------------------------------------------------------------- one event list, three outputs

@pytest.mark.parametrize("arti", [{}, {"OsVendorArtiStateModel": "STANDARD"},
                                  {"OsVendorArtiTraceServiceCalls": True, "OsVendorArtiTraceHook": False}])
def test_header_mock_and_description_list_the_same_events(tmp_path, arti):
    out = render(tmp_path, **arti)
    described = set(described_hooks(out))
    assert header_tokens(out) == described
    assert {tuple(row[1:3]) + ("OsOS", row[3]) for row in mock_table(out)} == described
    assert [int(row[0]) for row in mock_table(out)] == list(range(1, len(described) + 1))


def test_standard_model_wrappers_report_start(tmp_path):
    hdr = (render(tmp_path, OsVendorArtiStateModel="STANDARD") / "include" / "Os_ArtiHooks.h").read_text(encoding="utf-8")
    assert "#define OS_ARTI_TASK_RESUME(core, task)    OS_ARTI_EV_OsTask_Start(core, task)" in hdr
    assert "#define OS_ARTI_TASK_CONTINUE(core, task)    OS_ARTI_EV_OsTask_Start(core, task)" in hdr
    assert "#define OS_ARTI_ISR2_PREEMPT(core, isr)    ((void)0)" in hdr


def test_application_hook_dispatch(tmp_path):
    hdr = (render(tmp_path) / "include" / "Os_ArtiHooks.h").read_text(encoding="utf-8")
    start = hdr.index("#define OS_ARTI_APPHOOK_ERRORHOOK_START")
    body = hdr[start:hdr.index("while (0)", start)]
    assert "case 0U: OS_ARTI_EV_OsHook_ErrorHook_App_Core0_Start((core), (param)); break;" in body
    assert "App_Core1" not in body
    assert "#define OS_ARTI_APPHOOK_SHUTDOWNHOOK_START(core, app, param) \\" in hdr


# --------------------------------------------------------------------------- compile checks (mock)

# Std_Types.h plus what the service-call helpers expand to in the kernel (uint32, CoreIdType, Os_Inf_GetCoreId)
STD_TYPES_STUB = ("#define STD_ON 1U\n#define STD_OFF 0U\ntypedef unsigned long uint32;\n"
                  "typedef unsigned char CoreIdType;\nstatic inline CoreIdType Os_Inf_GetCoreId(void) { return 0U; }\n")


def _compile(out, body, mock=True):
    inc = out / "include"
    (inc / "Std_Types.h").write_text(STD_TYPES_STUB, encoding="utf-8")
    (out / "t.c").write_text('#include "Os_ArtiHooks.h"\nvoid f(unsigned long c, unsigned long x)\n{\n'
                             + body + "    (void)c; (void)x;\n}\n", encoding="utf-8")
    srcs = [out / "t.c"] + list(out.rglob("Os_Arti_Mock.c"))
    flags = ["-DOS_ARTI_USE_MOCK"] if mock else []
    r = subprocess.run([GCC, "-mcpu=cortex-r52", "-std=c99", "-Wall", "-Wextra", "-Werror", *flags, "-I", str(inc),
                        "-c", *map(str, srcs)], capture_output=True, text=True, cwd=out)
    return r.returncode, r.stderr


def _all_wrappers(out):
    hdr = (out / "include" / "Os_ArtiHooks.h").read_text(encoding="utf-8")
    names = re.findall(r"#define (OS_ARTI_(?:TASK|ISR2|APPLICATION|SPINLOCK|HOOK|APPHOOK|SC)_\w+)\(([\w, ]+)\)", hdr)
    calls = "".join(f"    {n}({', '.join('c' if a == 'core' else 'x' for a in args.split(', '))});\n"
                    for n, args in names if n not in ("OS_ARTI_SC_BEGIN", "OS_ARTI_SC_END"))
    # the service-call helpers as the kernel uses them
    return calls + ("    {\n        OS_ARTI_SC_DECL\n        OS_ARTI_SC_BEGIN(ActivateTask, x);\n"
                    "        OS_ARTI_SC_END(ActivateTask, x);\n    }\n")


@needs_gcc
@pytest.mark.parametrize("arti", [{}, {"OsVendorArtiStateModel": "STANDARD", "OsVendorArtiTraceServiceCalls": True}])
def test_every_wrapper_compiles_against_the_strict_mock(tmp_path, arti):
    out = render(tmp_path, **arti)
    rc, err = _compile(out, _all_wrappers(out))
    assert rc == 0, err


@needs_gcc
@pytest.mark.parametrize("call", [
    "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, OsOS, c, OsTask_Activat, x);",     # misspelt event
    "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, OsOS, OsTask_Activate, c, x);",    # EXP parameter order
    "ARTI_TRACE(SPRVSR, AR_CP_OSARTI_TASK, OsOS, c, OsTask_Activate, x);",    # context not described
    "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, c, OsTask_Activate, x);",      # instance name differs
    "ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, OsOS, c, OsTask_Activate, x);",        # class of the other model
])
def test_undescribed_hook_does_not_compile(tmp_path, call):
    rc, _ = _compile(render(tmp_path), "    " + call + "\n")
    assert rc != 0


@needs_gcc
def test_arti_disabled_compiles_without_any_hook_implementation(tmp_path):
    out = render(tmp_path, use_arti=False)
    (out / "include" / "Os_Arti_Mock.h").unlink()
    rc, err = _compile(out, _all_wrappers(out), mock=False)
    assert rc == 0, err


def test_static_only_configuration_needs_no_trace_tool_header(tmp_path):
    """OsUseArti on, every trace class off: static ARTI debugging without a hook implementation."""
    out = render(tmp_path, **{f"OsVendorArtiTrace{c}": False
                              for c in ("Application", "Task", "Cat2Isr", "ServiceCalls", "Spinlock", "Hook")})
    hdr = (out / "include" / "Os_ArtiHooks.h").read_text(encoding="utf-8")
    assert '#include "Os_Arti.h"' not in hdr and "OS_ARTI_EV_" not in hdr
    assert described_hooks(out) == {}
    if GCC:
        (out / "include" / "Os_Arti_Mock.h").unlink()
        rc, err = _compile(out, _all_wrappers(out), mock=False)
        assert rc == 0, err
