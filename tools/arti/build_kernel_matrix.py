"""Compile the real OS kernel for every combination of the ARTI vendor parameters.

For each combination the Os module of a project is generated (OsUseArti and the seven OsVendorArti* parameters of
OsOS are set in memory, nothing is saved), then every kernel source is compiled (no link) with arm-none-eabi-gcc
-Wall -Wextra and the strict Mock (-DOS_ARTI_USE_MOCK).  A combination passes when

  * every kernel source and the generated Os_Arti_Mock.c compile,
  * it adds no warning to those of the reference build: the kernel without ARTI instrumentation, built with the
    configuration of the same OsUseArti state (with OsUseArti on, the kernel's own orti runtime is compiled in and
    brings warnings of its own, e.g. Os_orti.c "changes value from '418' to '162'"; they are not ours),
  * for the combinations that must not change the kernel (OsUseArti off, every trace class off) the allocated
    sections of every object are byte-identical to the reference build.

usage:
  python tools/arti/build_kernel_matrix.py --project <dir with *.dpa> --kernel <kernel Os dir> \
         [--reference-kernel <Os dir of the kernel without ARTI>] [--gcc <arm-none-eabi-gcc>] \
         [--sdk <dir>] [--memmap <dir>] [--work <dir>] [--only <substring>]

--reference-kernel defaults to --kernel (then OsUseArti off is the reference, which is also what the kernel
guarantees).  The kernel is not modified.  Exit code = number of failing combinations.
"""
import argparse
import collections
import hashlib
import logging
import re
import shutil
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

SWITCHES = ("Application", "Task", "Cat2Isr", "Spinlock", "Hook", "ServiceCalls")
DEFAULT_ON = {s: s != "ServiceCalls" for s in SWITCHES}
CFLAGS = ["-mcpu=cortex-r52", "-mfpu=neon-fp-armv8", "-mfloat-abi=hard", "-O2", "-std=gnu99", "-ffunction-sections",
          "-fdata-sections", "-Wall", "-Wextra", "-D__HIGHTEC__", "-DOS_ARTI_USE_MOCK", "-c"]
WARNING = re.compile(r"^(?P<file>.+?):\d+:\d+: warning: (?P<msg>.*)$", re.M)     # the path may start with "D:\"


def combinations():
    """(name, use_arti, state model, {switch: bool}, must be identical to the reference build)"""
    def sw(**on):
        return {s: on.get(s, False) for s in SWITCHES}

    yield "arti-off", False, "ENHANCED", dict(DEFAULT_ON), True
    yield "all-trace-off", True, "ENHANCED", sw(), True
    yield "default", True, "ENHANCED", dict(DEFAULT_ON), False
    yield "default-standard", True, "STANDARD", dict(DEFAULT_ON), False
    yield "all-on-enhanced", True, "ENHANCED", {s: True for s in SWITCHES}, False
    yield "all-on-standard", True, "STANDARD", {s: True for s in SWITCHES}, False
    for s in SWITCHES[:-1]:
        yield f"default-without-{s}", True, "ENHANCED", {**DEFAULT_ON, s: False}, False
    for s in SWITCHES:
        for model in ("ENHANCED", "STANDARD"):
            yield f"only-{s}-{model.lower()}", True, model, sw(**{s: True}), False


def generate(project, combo, out):
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    from autosar_configurator.generator.generator import CodeGenerator

    dpa = next(Path(project).glob("*.dpa"))
    p, _failed = WorkspaceManager().load_project(dpa)
    m = p.get_manager("Os")
    osos = next(c for c in m.configuration.containers if c.definition_ref.endswith("/OsOS"))
    _name, use_arti, model, switches, _same = combo
    m.set_parameter_value(osos, "OsUseArti", use_arti)
    m.set_parameter_value(osos, "OsVendorArtiStateModel", model)
    for s, on in switches.items():
        m.set_parameter_value(osos, f"OsVendorArtiTrace{s}", on)
    allc = {x.module_def.short_name: (x.module_def, x.configuration) for x in p.get_all_managers()}
    g = CodeGenerator(module_def=m.module_def, configuration=m.configuration,
                      project_template_dir=Path(project) / "templates", all_configurations=allc,
                      selected_chip=p.selected_chip, ecu_resources=p.ecu_resources)
    assert g.generate_all(out), g.last_status
    return Path(out) / "Os" / "Os"


def include_dirs(kernel, config, sdk, memmap):
    dirs = [memmap] if memmap else []
    dirs += [d for d in sorted(config.rglob("*")) if d.is_dir() and d.name != "orti"] + [config]
    dirs += [d for d in sorted(kernel.rglob("*")) if d.is_dir() and ".svn" not in d.parts] + [kernel]
    if sdk:
        dirs += [d for d in sorted(sdk.rglob("*")) if d.is_dir() and ".svn" not in d.parts] + [sdk]
    return dirs


def compile_all(gcc, kernel, config, sdk, memmap, objdir, extra_sources=()):
    """-> (failures {source: first error lines}, warnings Counter[(file, message)])"""
    objdir.mkdir(parents=True, exist_ok=True)
    args = [gcc] + CFLAGS
    for d in include_dirs(kernel, config, sdk, memmap):
        args += ["-I", str(d)]
    failures, warnings = {}, collections.Counter()
    sources = [s for s in sorted(kernel.rglob("*.c")) if ".svn" not in s.parts] + list(extra_sources)
    for src in sources:
        rel = src.relative_to(kernel) if kernel in src.parents else Path("extra") / src.name
        obj = objdir / (str(rel).replace("\\", "__").replace("/", "__")[:-2] + ".o")
        r = subprocess.run(args + [str(src), "-o", str(obj)], capture_output=True, text=True)
        for w in WARNING.finditer(r.stderr):
            warnings[(Path(w["file"]).name, w["msg"])] += 1
        if r.returncode:
            failures[src.name] = [l for l in r.stderr.splitlines() if "error" in l][:3]
    return failures, warnings


def section_digest(binutils, obj):
    """{section: sha1 of the allocated contents (or size for nobits)}"""
    out = subprocess.run([binutils + "objdump", "-h", str(obj)], capture_output=True, text=True).stdout.splitlines()
    result = {}
    for i, line in enumerate(out):
        parts = line.split()
        if len(parts) >= 7 and parts[0].isdigit() and "ALLOC" in out[i + 1]:
            if "CONTENTS" in out[i + 1]:
                data = subprocess.run([binutils + "objcopy", "-O", "binary", "--only-section=" + parts[1], str(obj),
                                       "-"], capture_output=True).stdout
                result[parts[1]] = hashlib.sha1(data).hexdigest()
            else:
                result[parts[1]] = "bss:" + parts[2]
    return result


def objects_differ(binutils, a, b):
    """names of kernel objects of dir b (the reference) whose allocated sections differ in dir a"""
    diff = []
    for ob in sorted(b.glob("*.o")):
        oa = a / ob.name
        if not oa.exists() or section_digest(binutils, oa) != section_digest(binutils, ob):
            diff.append(ob.name)
    return diff


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--project", required=True)
    ap.add_argument("--kernel", required=True)
    ap.add_argument("--reference-kernel")
    ap.add_argument("--gcc", default="arm-none-eabi-gcc")
    ap.add_argument("--sdk")
    ap.add_argument("--memmap", help="directory with a complete Os_memmap.h, placed first on the include path")
    ap.add_argument("--work", default=str(REPO / "build" / "arti_matrix"))
    ap.add_argument("--only", help="run only the combinations whose name contains this text")
    a = ap.parse_args()
    logging.basicConfig(level=logging.ERROR)

    work = Path(a.work)
    shutil.rmtree(work, ignore_errors=True)
    kernel = Path(a.kernel)
    ref_kernel = Path(a.reference_kernel) if a.reference_kernel else kernel
    sdk = Path(a.sdk) if a.sdk else None
    memmap = Path(a.memmap) if a.memmap else None
    binutils = a.gcc.rpartition("gcc")[0]                           # ".../arm-none-eabi-"

    ref_combo = next(c for c in combinations() if c[0] == "arti-off")
    ref_cfg = generate(a.project, ref_combo, work / "gen_reference")
    fails, ref_warn = compile_all(a.gcc, ref_kernel, ref_cfg, sdk, memmap, work / "obj_reference")
    print(f"reference build: {len(list((work / 'obj_reference').glob('*.o')))} objects, "
          f"{len(fails)} failures, {sum(ref_warn.values())} warnings")
    if fails:
        print("  reference does not compile:", fails)
        return 1

    on_combo = next(c for c in combinations() if c[0] == "all-trace-off")
    on_cfg = generate(a.project, on_combo, work / "gen_reference_on")
    fails, ref_warn_on = compile_all(a.gcc, ref_kernel, on_cfg, sdk, memmap, work / "obj_reference_on")
    print(f"reference build, OsUseArti on: {len(fails)} failures, {sum(ref_warn_on.values())} warnings "
          f"({sum((ref_warn_on - ref_warn).values())} more than with OsUseArti off)")
    if fails:
        return 1

    bad = 0
    for combo in combinations():
        name, _use, _model, switches, same = combo
        if a.only and a.only not in name:
            continue
        cfg = generate(a.project, combo, work / f"gen_{name}")
        mock = [cfg / "kernel" / "Os_Arti_Mock.c"] if (cfg / "kernel" / "Os_Arti_Mock.c").exists() else []
        fails, warn = compile_all(a.gcc, kernel, cfg, sdk, memmap, work / f"obj_{name}", mock)
        added = warn - (ref_warn_on if combo[1] else ref_warn)
        problems = []
        if fails:
            problems.append(f"{len(fails)} source(s) do not compile: {fails}")
        if added:
            problems.append("new warnings: " + "; ".join(f"{f}: {m} (x{n})" for (f, m), n in added.items()))
        if same:
            diff = objects_differ(binutils, work / f"obj_{name}", work / "obj_reference")
            if diff:
                problems.append(f"{len(diff)} object(s) differ from the reference: {diff[:5]}")
        on = ",".join(s for s, v in switches.items() if v) or "-"
        print(f"{'FAIL' if problems else 'ok  '} {name:34s} classes: {on}")
        for pr in problems:
            print("     ", pr)
        bad += bool(problems)
    print(f"{bad} failing combination(s)")
    return bad


if __name__ == "__main__":
    sys.exit(main())
