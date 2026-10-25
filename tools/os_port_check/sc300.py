"""SC300 (Cortex-M3) check: build the single-core example, link it with the kernel and run it on QEMU.

The test program (target_sc300/test_app.c) records 16 steps; the run passes when they all happen in
the expected order.  QEMU machine mps2-an385 is a Cortex-M3 with semihosting for the output.
"""
import shutil
import subprocess
import tempfile
from pathlib import Path
from typing import List, Optional, Tuple

from . import common
from .t1_example import generate_sc300_example

M3_FLAGS = ["-mcpu=cortex-m3", "-mthumb", "-mfloat-abi=soft", "-O2", "-g", "-std=gnu11",
            "-ffunction-sections", "-fdata-sections", "-D__HIGHTEC__", "-D__OS_SUPPORT_CORTEX_M3__"]
QEMU_ARGS = ["-machine", "mps2-an385", "-cpu", "cortex-m3", "-nographic", "-monitor", "none", "-serial", "none",
             "-semihosting-config", "enable=on,target=native"]


def build(kernel: Path, t1: Path, work: Path, show_warnings: bool = False) -> Tuple[List[str], Path]:
    """Generate the example, compile everything and link; returns (failure messages, elf path)"""
    config = generate_sc300_example(t1, work / "t1", work / "gen")
    objects = work / "obj"
    if objects.exists():
        shutil.rmtree(objects)
    flags = M3_FLAGS + (["-Wall", "-Wextra"] if show_warnings else ["-w"])
    dirs = common.subdirs(config) + common.subdirs(kernel)
    includes = ["-I", str(common.STUBS_M3)] + common.include_args(dirs)

    jobs = [(src, objects / common.object_name("k", kernel, src)) for src in common.sources(kernel, "*.c")]
    jobs += [(src, objects / common.object_name("k", kernel, src)) for src in common.sources(kernel, "*_cm3.s")]
    jobs += [(src, objects / common.object_name("c", config, src)) for src in common.sources(config, "*.c")]
    jobs += [(common.TARGET_M3 / name, objects / f"t__{Path(name).stem}.o")
             for name in ("test_app.c", "startup_an385.c")]
    failures = common.compile_files(flags, includes, jobs, show_warnings)
    if failures:
        return failures, work / "test.elf"

    elf = work / "test.elf"
    link = subprocess.run(
        [common.gcc(), "-mcpu=cortex-m3", "-mthumb", "-nostartfiles", "-T", str(common.TARGET_M3 / "an385.ld"),
         "-Wl,--gc-sections", f"-Wl,-Map={work / 'test.map'}", *map(str, sorted(objects.glob("*.o"))),
         "-lgcc", "-lc", "-lnosys", "-o", str(elf)], capture_output=True, text=True)
    if link.returncode:
        return ["link: " + " | ".join(link.stderr.splitlines()[:6])], elf
    return [], elf


def run(elf: Path, timeout: int = 60) -> Tuple[bool, str]:
    """Run the image on QEMU; returns (passed, output)"""
    # QEMU writes the semihosting console to stderr; stdout is merged in case that differs by version
    try:
        result = subprocess.run([common.qemu(), *QEMU_ARGS, "-kernel", str(elf)], stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, text=True, timeout=timeout)
    except subprocess.TimeoutExpired as e:
        partial = e.stdout.decode(errors="replace") if isinstance(e.stdout, bytes) else (e.stdout or "")
        return False, partial + f"\nTIMEOUT after {timeout} s"
    return result.returncode == 0 and "RESULT: PASS" in result.stdout, result.stdout


def check(kernel: Path, t1: Path, work: Optional[Path] = None, show_warnings: bool = False) -> Tuple[bool, str]:
    own_work = work is None
    work = work or Path(tempfile.mkdtemp(prefix="os_port_sc300_"))
    try:
        failures, elf = build(kernel, t1, work, show_warnings)
        if failures:
            return False, "build failed:\n  " + "\n  ".join(failures)
        return run(elf)
    finally:
        if own_work:
            shutil.rmtree(work, ignore_errors=True)
