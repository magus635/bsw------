"""The baseline Arti.h, Os_Arti.h and Arti.c in doc/ARTI/vendor_example, the files every trace tool vendor starts from.

They must define every event the generated kernel header (Os_ArtiHooks.h) can emit, keep the event numbers of the
traced words consistent, and let the kernel wrappers compile without the Mock.
"""
import re
import subprocess
from pathlib import Path

import pytest

from .os_templates import requires_templates
from .test_os_arti_hooks import GCC, _all_wrappers, needs_gcc, render

pytestmark = requires_templates

BASELINE = Path(__file__).resolve().parents[2] / "doc" / "ARTI" / "vendor_example"
HOOKS_ALL_ON = {"OsVendorArtiTraceServiceCalls": True}
ALL_CONFIGS = [{}, {"OsVendorArtiStateModel": "STANDARD", **HOOKS_ALL_ON}, HOOKS_ALL_ON]


def os_arti_h():
    return (BASELINE / "Os_Arti.h").read_text(encoding="utf-8")


def baseline_enumerators():
    """{name: value expression} of every enumerator of Os_Arti.h"""
    return {m.group(1): m.group(2).strip() for m in re.finditer(r"^\s+(Os\w+)\s*=\s*([^,\n]+),?\s*$", os_arti_h(), re.M)}


def emitted_events(out):
    hdr = (out / "include" / "Os_ArtiHooks.h").read_text(encoding="utf-8")
    return set(re.findall(r"#define OS_ARTI_EV_(\w+)\(core, param\)", hdr)), hdr


def test_the_three_files_are_there():
    for name in ("Arti.h", "Os_Arti.h", "Arti.c"):
        assert (BASELINE / name).is_file(), name


@pytest.mark.parametrize("arti", ALL_CONFIGS)
def test_every_emitted_event_has_a_number(tmp_path, arti):
    """Each event the kernel emits is an enumerator of Os_Arti.h, or one of the generated numbers of the hooks of the
    OS-Applications"""
    events, hdr = emitted_events(render(tmp_path, **arti))
    known = set(baseline_enumerators())
    generated = set(re.findall(r"^\s+(OsHook_\w+_(?:Start|Return))\s*=\s*\d+,", hdr, re.M))
    assert generated, "the fixture has application hooks"
    missing = sorted(events - known - generated)
    assert not missing, missing


def test_application_hook_event_numbers_are_generated_after_the_hooks_of_the_os(tmp_path):
    hdr = emitted_events(render(tmp_path))[1]
    numbers = [(n, int(v)) for n, v in re.findall(r"^\s+(OsHook_\w+_(?:Start|Return))\s*=\s*(\d+),", hdr, re.M)]
    assert [n for n, _ in numbers][:2] == ["OsHook_ErrorHook_App_Core0_Start", "OsHook_ErrorHook_App_Core0_Return"]
    values = [v for _, v in numbers]
    assert values == list(range(64, 64 + len(values))), "numbered in order from 64"
    assert max(values) < 128, "the event number has 7 bits in the traced word"
    assert "OS_ARTI_APPHOOK_EVENT_END = %d" % (64 + len(values)) in hdr


def test_no_application_hook_numbers_without_application_hooks(tmp_path):
    hdr = emitted_events(render(tmp_path, OsVendorArtiTraceHook=False))[1]
    assert "OS_ARTI_APPHOOK_EVENT_END" not in hdr


def test_event_numbers_fit_the_traced_word_and_do_not_clash():
    """OS events share arti_os_trace: 7 bit event number, unique over all classes except the 8 task events that the
    standard model reports with the same numbers. Service calls have their own variable."""
    values = {}
    for name, expr in baseline_enumerators().items():
        if name.startswith("OsServiceCall_"):
            continue
        values[name] = int(expr, 0)
    assert all(0 <= v < 64 for v in values.values()), "0..63 are the numbers of the OS, 64.. are generated"
    by_value = {}
    for n, v in values.items():
        by_value.setdefault(v, []).append(n)
    assert all(len(ns) == 1 for ns in by_value.values()), by_value


def test_service_call_numbers():
    numbers = {}
    for name, expr in baseline_enumerators().items():
        if name.startswith("OsServiceCall_"):
            m = re.fullmatch(r"\((ARTI_OSSC_OSEK|ARTI_OSSC_AR) \+ +(\d+)U\) \| (ARTI_OSSC_START|ARTI_OSSC_RETURN)", expr)
            assert m, (name, expr)
            numbers[name] = (0x00 if m.group(1) == "ARTI_OSSC_OSEK" else 0x20) + int(m.group(2)) + \
                (0x80 if m.group(3) == "ARTI_OSSC_RETURN" else 0)
    assert len(numbers) == 2 * 71 and len(set(numbers.values())) == len(numbers), "unique per service and direction"
    # the numbers the Lauterbach ARTI implementation uses for the services it knows
    assert numbers["OsServiceCall_EnableAllInterrupts_Start"] == 7
    assert numbers["OsServiceCall_SuspendOSInterrupts_Return"] == 12 + 0x80
    assert numbers["OsServiceCall_TryToGetSpinlock_Start"] == 0x20 + 29
    assert max(v & 0x7F for v in numbers.values()) < 0x7F
    assert numbers["OsServiceCall_ActivateTask_Start"] == 1 and numbers["OsServiceCall_GetResource_Start"] == 13


def test_the_numbers_of_the_tasks_and_isrs_are_the_ones_of_the_lauterbach_implementation():
    e = {n: int(v, 0) for n, v in baseline_enumerators().items() if not n.startswith("OsServiceCall_")}
    assert [e[f"OsTask_{x}"] for x in ("Activate", "Start", "Wait", "Release", "Preempt", "Terminate", "Resume",
                                        "Continue")] == list(range(8))
    assert [e[f"OsCat2Isr_{x}"] for x in ("Start", "Stop", "Activate", "Preempt", "Resume")] == list(range(16, 21))
    assert (e["OsSpinlock_Locked"], e["OsApplication_Start"], e["OsHook_ErrorHook_Start"]) == (24, 32, 40)


@needs_gcc
@pytest.mark.parametrize("arti", ALL_CONFIGS)
def test_the_kernel_wrappers_compile_against_the_baseline(tmp_path, arti):
    out = render(tmp_path, **arti)
    inc = out / "include"
    (inc / "Std_Types.h").write_text(
        "#ifndef STD_TYPES_H_\n#define STD_TYPES_H_\n"
        "#define STD_ON 1U\n#define STD_OFF 0U\ntypedef unsigned long uint32;\ntypedef unsigned short uint16;\n"
        "typedef unsigned char uint8;\ntypedef unsigned char CoreIdType;\n"
        "typedef struct { uint16 vendorID; uint16 moduleID; uint8 sw_major_version; uint8 sw_minor_version; "
        "uint8 sw_patch_version; } Std_VersionInfoType;\n"
        "static inline CoreIdType Os_Inf_GetCoreId(void) { return 0U; }\n#endif\n", encoding="utf-8")
    (out / "t.c").write_text('#include "Os_ArtiHooks.h"\nvoid f(unsigned long c, unsigned long x)\n{\n' + _all_wrappers(out)
                             + "    (void)c; (void)x;\n}\n", encoding="utf-8")
    for src in (out / "t.c", BASELINE / "Arti.c"):
        r = subprocess.run([GCC, "-mcpu=cortex-r52", "-std=c99", "-Wall", "-Wextra", "-Werror", "-I", str(BASELINE),
                            "-I", str(inc), "-c", str(src), "-o", str(out / (src.stem + ".o"))],
                           capture_output=True, text=True, cwd=out)
        assert r.returncode == 0, r.stderr


@needs_gcc
def test_a_class_switched_off_in_arti_h_still_compiles_without_warnings(tmp_path):
    """A macro that drops its parameter must still evaluate it: the kernel passes locals that are used for nothing else"""
    body = ('#define ARTI_ENABLE_OS_TASK (STD_OFF)\n#define ARTI_ENABLE_OS_SERVICECALLS (STD_OFF)\n'
            '#include "Os_Arti.h"\nvoid f(unsigned long c)\n{\n    unsigned long t = c;\n'
            '    ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, OsOS, c, OsTask_Start, t);\n'
            '    ARTI_TRACE(SPRVSR, AR_CP_OS_SERVICECALLS, OsOS, c, OsServiceCall_ActivateTask_Start, t);\n}\n')
    (tmp_path / "Std_Types.h").write_text(
        "#define STD_ON 1U\n#define STD_OFF 0U\ntypedef unsigned long uint32;\ntypedef unsigned short uint16;\n"
        "typedef unsigned char uint8;\ntypedef struct { uint16 vendorID; uint16 moduleID; uint8 sw_major_version; "
        "uint8 sw_minor_version; uint8 sw_patch_version; } Std_VersionInfoType;\n", encoding="utf-8")
    (tmp_path / "t.c").write_text(body, encoding="utf-8")
    r = subprocess.run([GCC, "-mcpu=cortex-r52", "-std=c99", "-Wall", "-Wextra", "-Werror", "-I", str(BASELINE), "-I",
                        str(tmp_path), "-c", str(tmp_path / "t.c"), "-o", str(tmp_path / "t.o")],
                       capture_output=True, text=True)
    assert r.returncode == 0, r.stderr
