"""Locating tools and compiling C / assembler sources for the port checks."""
import os
import shutil
import subprocess
from pathlib import Path
from typing import Iterable, List, Optional, Sequence, Tuple

HERE = Path(__file__).resolve().parent
STUBS_R52 = HERE / "stubs_r52"
STUBS_M3 = HERE / "stubs_m3"
TARGET_M3 = HERE / "target_sc300"

DEFAULT_GCC = "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.2 Rel1/bin/arm-none-eabi-gcc.exe"
DEFAULT_QEMU = "C:/Program Files/qemu/qemu-system-arm.exe"


class CheckError(Exception):
    """A problem with the setup (missing tool or directory); not a failed check."""


def _tool(env_name: str, program: str, default: str) -> str:
    found = os.environ.get(env_name) or shutil.which(program) or (default if Path(default).is_file() else None)
    if not found:
        raise CheckError(f"{program} not found: install it, put it on PATH or set {env_name}")
    return found


def gcc() -> str:
    return _tool("ARM_NONE_EABI_GCC", "arm-none-eabi-gcc", DEFAULT_GCC)


def qemu() -> str:
    return _tool("QEMU_SYSTEM_ARM", "qemu-system-arm", DEFAULT_QEMU)


def directory(value: Optional[str], env_name: str, what: str) -> Path:
    value = value or os.environ.get(env_name)
    if not value:
        raise CheckError(f"{what}: give it as an argument or set {env_name}")
    path = Path(value)
    if not path.is_dir():
        raise CheckError(f"{what} is not a directory: {path}")
    return path


def subdirs(root: Path, skip: Iterable[str] = ()) -> List[Path]:
    """root and all directories below it (sorted), without .svn and the names in skip"""
    skipped = {".svn", *skip}
    found = [d for d in sorted(root.rglob("*")) if d.is_dir() and not (skipped & set(d.relative_to(root).parts))]
    return found + [root]


def include_args(dirs: Iterable[Path]) -> List[str]:
    args: List[str] = []
    for d in dirs:
        args += ["-I", str(d)]
    return args


def sources(root: Path, pattern: str) -> List[Path]:
    return sorted(p for p in root.rglob(pattern) if ".svn" not in p.parts)


def object_name(prefix: str, root: Path, src: Path) -> str:
    rel = str(src.relative_to(root)).replace("\\", "__").replace("/", "__")
    return f"{prefix}__{rel.rsplit('.', 1)[0]}.o"


def compile_files(flags: Sequence[str], includes: Sequence[str], jobs: Sequence[Tuple[Path, Path]],
                  show_warnings: bool = False) -> List[str]:
    """Compile (source, object) pairs; returns one message per failed file"""
    failures = []
    for src, obj in jobs:
        obj.parent.mkdir(parents=True, exist_ok=True)
        lang = ["-x", "assembler-with-cpp"] if src.suffix.lower() == ".s" else []
        result = subprocess.run([gcc(), *flags, *includes, *lang, "-c", str(src), "-o", str(obj)],
                                capture_output=True, text=True)
        if show_warnings and result.stderr:
            print(result.stderr)
        if result.returncode:
            errors = [line for line in result.stderr.splitlines() if "error" in line][:4]
            failures.append(f"{src.name}: " + " | ".join(errors))
    return failures


def compare_objects(baseline: Path, current: Path) -> List[str]:
    """Differences between two object directories, byte for byte; empty when identical"""
    a = {p.name for p in baseline.glob("*.o")}
    b = {p.name for p in current.glob("*.o")}
    problems = [f"only in baseline: {n}" for n in sorted(a - b)] + [f"only in current: {n}" for n in sorted(b - a)]
    problems += [f"differs: {n}" for n in sorted(a & b) if (baseline / n).read_bytes() != (current / n).read_bytes()]
    return problems
