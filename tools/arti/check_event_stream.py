"""Check an ARTI event stream recorded by the generated strict mock (Os_Arti_Mock.h).

openspec change add-arti-hook-tracing, design D9 / task 5.3. Run from the repository root:

    python -m tools.arti.check_event_stream --mock Os_Arti_Mock.h --csv events.csv
    python -m tools.arti.check_event_stream --mock Os_Arti_Mock.h --log-bin log.bin --count-bin count.bin

Inputs
  --mock       the generated Os_Arti_Mock.h: its event table (ARTI_MOCK_EVENT <id> <context> <class> <event>)
               maps event IDs to names, OS_ARTI_MOCK_CORES / the state model line give the layout
  --csv        one record per line: core,seq,time,event,instance,param (header line optional)
  --log-bin    raw little-endian memory dump of Os_ArtiMockLog (cores x depth records of 5 uint32)
  --count-bin  raw dump of Os_ArtiMockCount (cores uint32); --depth gives OS_ARTI_MOCK_DEPTH (default 512)

Checks (per core, in sequence order; every object is handled by the core it belongs to)
  - task state machine of the model (SWS OS 7.17.2, EXP ARTI Fig 3.1 / 3.2); Terminate from a state other
    than Running is the OS's forced termination (design D10) and is counted, not reported as an error
  - at most one Running task per core
  - no task dispatch / preemption while a Cat2 ISR is active on that core (Stop precedes the rescheduling)
  - Cat2 ISR state machine; spinlock Locked / Released alternate; hook and service call Start / Return pair up
    (TerminateTask, ChainTask, StartOS, ShutdownOS and ShutdownAllCores may not return); application
    transitions of SWS OS 7.17.1
A ring buffer that wrapped starts in the middle of the stream: the first event of every object then only
synchronises its state (no error), unless --strict-start is given.
"""
import argparse
import csv
import re
import struct
import sys
from collections import defaultdict
from dataclasses import dataclass, field

TASK_ENHANCED = {
    ("Suspended", "Activate"): "Activated",
    ("Activated", "Start"): "Running",
    ("Running", "Preempt"): "Preempted",
    ("Preempted", "Resume"): "Running",
    ("Running", "Wait"): "Waiting",
    ("Waiting", "Release"): "Released",
    ("Released", "Continue"): "Running",
    ("Running", "Terminate"): "Suspended",
}
TASK_STANDARD = {
    ("Suspended", "Activate"): "Ready",
    ("Ready", "Start"): "Running",
    ("Running", "Preempt"): "Ready",
    ("Running", "Wait"): "Waiting",
    ("Waiting", "Release"): "Ready",
    ("Running", "Terminate"): "Suspended",
}
ISR_ENHANCED = {
    ("Inactive", "Activate"): "Activated",
    ("Activated", "Start"): "Running",
    ("Running", "Preempt"): "Preempted",
    ("Preempted", "Resume"): "Running",
    ("Running", "Stop"): "Inactive",
}
ISR_STANDARD = {("Inactive", "Start"): "Running", ("Running", "Stop"): "Inactive"}
APPLICATION = {
    ("Initial", "Start"): "Accessible",
    ("Accessible", "Restart"): "Restarting",
    ("Restarting", "AllowAccess"): "Accessible",
    ("Accessible", "Terminate"): "Terminated",
    ("Restarting", "Terminate"): "Terminated",  # TerminateApplication while restarting, from the restart task
}
NO_RETURN = {"TerminateTask", "ChainTask", "StartOS", "ShutdownOS", "ShutdownAllCores"}
DISPATCH = {"Start", "Resume", "Continue"}


@dataclass
class Record:
    core: int
    seq: int
    time: int
    event: int
    instance: int
    param: int


@dataclass
class Result:
    errors: list = field(default_factory=list)
    forced_terminations: int = 0
    events: int = 0

    def error(self, rec, name, text):
        self.errors.append(f"core {rec.core} seq {rec.seq} {name}({rec.param}): {text}")


def parse_mock(text):
    """{event id: (context, class, event)}, number of cores, enhanced?"""
    table = {int(m.group(1)): m.group(2, 3, 4)
             for m in re.finditer(r"ARTI_MOCK_EVENT (\d+) (\w+) (\w+) (\w+)", text)}
    cores = int(re.search(r"#define OS_ARTI_MOCK_CORES\s+\((\d+)UL\)", text).group(1))
    enhanced = "state model: ENHANCED" in text
    return table, cores, enhanced


def read_csv(path):
    out = []
    with open(path, newline="", encoding="utf-8") as f:
        for row in csv.reader(f):
            if not row or not row[0].strip().lstrip("-").isdigit():
                continue
            out.append(Record(*(int(x, 0) for x in row[:6])))
    return out


def read_bin(log_path, count_path, cores, depth):
    log = open(log_path, "rb").read()
    counts = struct.unpack(f"<{cores}I", open(count_path, "rb").read()[:4 * cores])
    out = []
    for core in range(cores):
        n = counts[core]
        first = max(0, n - depth)
        for seq in range(first, n):
            off = (core * depth + seq % depth) * 20
            s, t, ev, inst, par = struct.unpack_from("<5I", log, off)
            out.append(Record(core, s, t, ev, inst, par))
    return out


class Checker:
    def __init__(self, table, enhanced, strict_start=False):
        self.table = table
        self.task_sm = TASK_ENHANCED if enhanced else TASK_STANDARD
        self.isr_sm = ISR_ENHANCED if enhanced else ISR_STANDARD
        self.strict = strict_start
        self.res = Result()
        self.task = {}                      # task id -> state
        self.isr = {}                       # isr id -> state
        self.app = {}
        self.spin = {}                      # spinlock id -> locked?
        self.running = {}                   # core -> running task
        self.active_isrs = defaultdict(set)  # core -> isr ids not Inactive
        self.hooks = defaultdict(list)      # core -> stack of hook names
        self.services = defaultdict(list)   # core -> stack of service names

    def _sm(self, states, sm, key, rec, name, ev, initial):
        cur = states.get(key)
        if cur is None:
            if self.strict:
                cur = initial
            else:
                # first event of the object in this capture: take the state it leads to
                targets = [to for (frm, e), to in sm.items() if e == ev]
                states[key] = targets[0] if targets else initial
                return True
        nxt = sm.get((cur, ev))
        if nxt is None:
            return False
        states[key] = nxt
        return True

    def feed(self, rec):
        self.res.events += 1
        if rec.event not in self.table:
            self.res.error(rec, f"event#{rec.event}", "unknown event ID (not in the mock event table)")
            return
        ctx, cls, name = self.table[rec.event]
        prefix, _, ev = name.partition("_")
        if prefix == "OsTask":
            self._task(rec, name, ev)
        elif prefix == "OsCat2Isr":
            self._isr(rec, name, ev)
        elif prefix == "OsSpinlock":
            locked = self.spin.get(rec.param)
            if ev == "Locked":
                if locked:
                    self.res.error(rec, name, "spinlock locked twice")
                self.spin[rec.param] = True
            else:
                if locked is False or (locked is None and self.strict):
                    self.res.error(rec, name, "spinlock released while not locked")
                self.spin[rec.param] = False
        elif prefix == "OsApplication":
            if not self._sm(self.app, APPLICATION, rec.param, rec, name, ev, "Initial"):
                self.res.error(rec, name, f"application: no transition {self.app.get(rec.param)} --{ev}-->")
        elif prefix == "OsHook":
            self._pair(self.hooks[rec.core], rec, name, name.rsplit("_", 1)[0], name.endswith("_Start"), set())
        elif prefix == "OsServiceCall":
            api = name[len("OsServiceCall_"):].rsplit("_", 1)[0]
            self._pair(self.services[rec.core], rec, name, api, name.endswith("_Start"), NO_RETURN)

    def _task(self, rec, name, ev):
        t, core = rec.param, rec.core
        before = self.task.get(t)
        if ev in DISPATCH or ev == "Preempt":
            if self.active_isrs[core]:
                self.res.error(rec, name, f"task event while Cat2 ISR {sorted(self.active_isrs[core])} is active")
        if ev in DISPATCH:
            other = self.running.get(core)
            if other is not None and other != t:
                self.res.error(rec, name, f"task {other} is still Running on this core")
        if ev == "Terminate" and before not in (None, "Running"):
            # forced termination (protection / TerminateApplication) from a state other than Running
            self.res.forced_terminations += 1
            self.task[t] = "Suspended"
        elif not self._sm(self.task, self.task_sm, t, rec, name, ev, "Suspended"):
            self.res.error(rec, name, f"task {t}: no transition {before} --{ev}-->")
        state = self.task.get(t)
        if state == "Running":
            self.running[core] = t
        elif self.running.get(core) == t:
            del self.running[core]

    def _isr(self, rec, name, ev):
        i, core = rec.param, rec.core
        before = self.isr.get(i)
        if not self._sm(self.isr, self.isr_sm, i, rec, name, ev, "Inactive"):
            self.res.error(rec, name, f"ISR {i}: no transition {before} --{ev}-->")
        if self.isr.get(i) == "Inactive":
            self.active_isrs[core].discard(i)
        else:
            self.active_isrs[core].add(i)

    def _pair(self, stack, rec, name, key, start, no_return):
        if start:
            stack.append(key)
            return
        while stack and stack[-1] != key and stack[-1] in no_return:
            stack.pop()
        if stack and stack[-1] == key:
            stack.pop()
        elif self.strict or stack:
            self.res.error(rec, name, f"Return without matching Start (open: {stack})")

    def run(self, records):
        for core in sorted({r.core for r in records}):
            for rec in sorted((r for r in records if r.core == core), key=lambda r: r.seq):
                if rec.instance != rec.core:
                    self.res.error(rec, f"event#{rec.event}", f"instance parameter {rec.instance} != recording core")
                self.feed(rec)
        return self.res


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--mock", required=True)
    ap.add_argument("--csv")
    ap.add_argument("--log-bin")
    ap.add_argument("--count-bin")
    ap.add_argument("--depth", type=int, default=512)
    ap.add_argument("--strict-start", action="store_true", help="the capture starts at system start")
    a = ap.parse_args(argv)
    table, cores, enhanced = parse_mock(open(a.mock, encoding="utf-8").read())
    if a.csv:
        records = read_csv(a.csv)
    elif a.log_bin and a.count_bin:
        records = read_bin(a.log_bin, a.count_bin, cores, a.depth)
    else:
        ap.error("give --csv or --log-bin with --count-bin")
    res = Checker(table, enhanced, a.strict_start).run(records)
    for e in res.errors:
        print("ERROR", e)
    print(f"{res.events} events, {len(res.errors)} errors, {res.forced_terminations} forced terminations "
          f"({'enhanced' if enhanced else 'standard'} model)")
    return 1 if res.errors else 0


if __name__ == "__main__":
    sys.exit(main())
