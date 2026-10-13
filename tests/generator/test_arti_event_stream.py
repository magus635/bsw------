"""tools/arti/check_event_stream.py (openspec add-arti-hook-tracing, task 5.3) on synthetic event streams.

The sequences follow the required test cases of doc/2026-10-06_自研OS原生支持ARTI开发说明.md section 7.3.
"""
import shutil
import struct
from pathlib import Path

import pytest

from tools.arti.check_event_stream import Checker, Record, main, parse_mock, read_bin

EVENTS = [
    ("NOSUSP", "AR_CP_OSARTI_TASK", "OsTask_" + e)
    for e in ("Activate", "Start", "Preempt", "Resume", "Wait", "Release", "Continue", "Terminate")
] + [
    ("NOSUSP", "AR_CP_OSARTI_CAT2ISR", "OsCat2Isr_" + e) for e in ("Activate", "Start", "Preempt", "Resume", "Stop")
] + [
    ("NOSUSP", "AR_CP_OS_SPINLOCK", "OsSpinlock_Locked"), ("NOSUSP", "AR_CP_OS_SPINLOCK", "OsSpinlock_Released"),
    ("SPRVSR", "AR_CP_OS_SERVICECALLS", "OsServiceCall_ActivateTask_Start"),
    ("SPRVSR", "AR_CP_OS_SERVICECALLS", "OsServiceCall_ActivateTask_Return"),
    ("SPRVSR", "AR_CP_OS_SERVICECALLS", "OsServiceCall_TerminateTask_Start"),
    ("NOSUSP", "AR_CP_OS_HOOK", "OsHook_ErrorHook_Start"), ("NOSUSP", "AR_CP_OS_HOOK", "OsHook_ErrorHook_Return"),
    ("NOSUSP", "AR_CP_OS_APPLICATION", "OsApplication_Start"),
    ("NOSUSP", "AR_CP_OS_APPLICATION", "OsApplication_Terminate"),
]
TABLE = {i + 1: e for i, e in enumerate(EVENTS)}
ID = {name: i for i, (_, _, name) in TABLE.items()}
STANDARD = {i + 1: ("NOSUSP", "AR_CP_OS_TASK", "OsTask_" + e) for i, e in enumerate(
    ("Activate", "Start", "Preempt", "Wait", "Release", "Terminate"))}
SID = {name: i for i, (_, _, name) in STANDARD.items()}


def stream(*events, core=0, ids=ID):
    """events: (short name, param); OsTask_/OsCat2Isr_ prefixes may be left out as T./I."""
    out = []
    for seq, (name, param) in enumerate(events):
        full = name.replace("T.", "OsTask_").replace("I.", "OsCat2Isr_")
        out.append(Record(core, seq, 0, ids[full], core, param))
    return out


def check(*events, enhanced=True, strict=True, **kw):
    table, ids = (TABLE, ID) if enhanced else (STANDARD, SID)
    return Checker(table, enhanced, strict_start=strict).run(stream(*events, ids=ids, **kw))


A, B = 0, 1     # task IDs
X, Y = 5, 6     # ISR IDs


def test_basic_chain():
    res = check(("T.Activate", A), ("T.Start", A), ("T.Activate", B), ("T.Preempt", A), ("T.Start", B),
                ("T.Terminate", B), ("T.Resume", A), ("T.Terminate", A))
    assert res.errors == []


def test_wait_release_continue():
    res = check(("T.Activate", A), ("T.Start", A), ("T.Wait", A), ("T.Release", A), ("T.Continue", A))
    assert res.errors == []


@pytest.mark.parametrize("bad", ["T.Start", "T.Resume", "T.Continue"])
def test_waiting_cannot_run_directly(bad):
    res = check(("T.Activate", A), ("T.Start", A), ("T.Wait", A), (bad, A))
    assert len(res.errors) == 1 and "Waiting" in res.errors[0]


def test_reason_of_readiness_selects_the_dispatch_event():
    assert check(("T.Activate", A), ("T.Start", A), ("T.Wait", A), ("T.Release", A), ("T.Resume", A)).errors
    assert check(("T.Activate", A), ("T.Start", A), ("T.Preempt", A), ("T.Continue", A)).errors
    assert check(("T.Activate", A), ("T.Resume", A)).errors


def test_isr_without_rescheduling_leaves_the_task_running():
    res = check(("T.Activate", A), ("T.Start", A), ("I.Activate", X), ("I.Start", X), ("I.Stop", X),
                ("T.Terminate", A))
    assert res.errors == []


def test_isr_exit_rescheduling_order():
    ok = check(("T.Activate", A), ("T.Start", A), ("I.Activate", X), ("I.Start", X), ("T.Activate", B),
               ("I.Stop", X), ("T.Preempt", A), ("T.Start", B))
    assert ok.errors == []
    late_stop = check(("T.Activate", A), ("T.Start", A), ("I.Activate", X), ("I.Start", X), ("T.Activate", B),
                      ("T.Preempt", A), ("T.Start", B), ("I.Stop", X))
    assert len(late_stop.errors) == 2 and all("Cat2 ISR" in e for e in late_stop.errors)


def test_nested_isr():
    res = check(("I.Activate", X), ("I.Start", X), ("I.Preempt", X), ("I.Activate", Y), ("I.Start", Y),
                ("I.Stop", Y), ("I.Resume", X), ("I.Stop", X))
    assert res.errors == []


def test_two_running_tasks_on_one_core():
    res = check(("T.Activate", A), ("T.Start", A), ("T.Activate", B), ("T.Start", B))
    assert len(res.errors) == 1 and "still Running" in res.errors[0]


def test_multiple_activation_keeps_the_preempted_state():
    """An activation of an already ready task is not reported: the task still resumes."""
    res = check(("T.Activate", A), ("T.Start", A), ("T.Preempt", A), ("T.Resume", A), ("T.Terminate", A),
                ("T.Start", A))
    assert len(res.errors) == 1   # Start after Terminate without Activate
    pending = check(("T.Activate", A), ("T.Start", A), ("T.Terminate", A), ("T.Activate", A), ("T.Start", A))
    assert pending.errors == []


def test_forced_termination_is_counted_not_reported():
    res = check(("T.Activate", A), ("T.Start", A), ("T.Activate", B), ("T.Preempt", A), ("T.Start", B),
                ("T.Terminate", A))
    assert res.errors == [] and res.forced_terminations == 1


def test_spinlock_double_lock():
    assert check(("OsSpinlock_Locked", 0), ("OsSpinlock_Released", 0)).errors == []
    assert check(("OsSpinlock_Locked", 0), ("OsSpinlock_Locked", 0)).errors


def test_service_calls_and_hooks_pair_up():
    assert check(("OsServiceCall_ActivateTask_Start", A), ("OsHook_ErrorHook_Start", 3),
                 ("OsHook_ErrorHook_Return", 0), ("OsServiceCall_ActivateTask_Return", 0)).errors == []
    # a successful TerminateTask does not return
    assert check(("OsServiceCall_TerminateTask_Start", A), ("OsServiceCall_ActivateTask_Start", B),
                 ("OsServiceCall_ActivateTask_Return", 0)).errors == []
    assert check(("OsServiceCall_ActivateTask_Return", 0)).errors


def test_application_transitions():
    assert check(("OsApplication_Start", 1), ("OsApplication_Terminate", 1)).errors == []
    assert check(("OsApplication_Terminate", 1),).errors      # Initial --Terminate-->


def test_standard_model():
    ok = check(("T.Activate", A), ("T.Start", A), ("T.Preempt", A), ("T.Start", A), ("T.Wait", A),
               ("T.Release", A), ("T.Start", A), ("T.Terminate", A), enhanced=False)
    assert ok.errors == []


def test_wrapped_capture_synchronises_on_the_first_event():
    events = (("T.Resume", A), ("T.Wait", A), ("T.Release", A), ("T.Continue", A))
    assert check(*events, strict=False).errors == []
    assert check(*events, strict=True).errors


def test_instance_parameter_must_be_the_recording_core():
    rec = stream(("T.Activate", A))[0]
    rec.instance = 1
    assert Checker(TABLE, True, True).run([rec]).errors


def test_binary_dump(tmp_path):
    cores, depth = 2, 4
    log = bytearray(cores * depth * 20)
    counts = [6, 1]     # core 0 wrapped: records 2..5 remain
    seqs = {0: [("T.Activate", A), ("T.Start", A), ("T.Activate", B), ("T.Preempt", A), ("T.Start", B),
                ("T.Terminate", B)], 1: [("I.Activate", X)]}
    for core, evs in seqs.items():
        for rec in stream(*evs, core=core):
            struct.pack_into("<5I", log, (core * depth + rec.seq % depth) * 20, rec.seq, 0, rec.event, core, rec.param)
    (tmp_path / "log.bin").write_bytes(bytes(log))
    (tmp_path / "count.bin").write_bytes(struct.pack("<2I", *counts))
    recs = read_bin(tmp_path / "log.bin", tmp_path / "count.bin", cores, depth)
    assert [r.seq for r in recs if r.core == 0] == [2, 3, 4, 5]
    assert Checker(TABLE, True, strict_start=False).run(recs).errors == []


def test_command_line_with_the_generated_mock(tmp_path):
    """Integration: event table of Os_Arti_Mock.h rendered from the ARTI fixture, CSV input."""
    from .test_os_arti_hooks import render
    out = render(tmp_path / "gen")
    mock = out / "include" / "Os_Arti_Mock.h"
    table, cores, enhanced = parse_mock(mock.read_text(encoding="utf-8"))
    assert enhanced and cores == 2
    ids = {name: i for i, (_, _, name) in table.items()}
    rows = ["core,seq,time,event,instance,param"]
    for seq, name in enumerate(("OsTask_Activate", "OsTask_Start", "OsTask_Terminate")):
        rows.append(f"1,{seq},0,{ids[name]},1,2")
    (tmp_path / "ev.csv").write_text("\n".join(rows), encoding="utf-8")
    assert main(["--mock", str(mock), "--csv", str(tmp_path / "ev.csv"), "--strict-start"]) == 0
    (tmp_path / "bad.csv").write_text(rows[0] + f"\n1,0,0,{ids['OsTask_Start']},1,2", encoding="utf-8")
    assert main(["--mock", str(mock), "--csv", str(tmp_path / "bad.csv"), "--strict-start"]) == 1
