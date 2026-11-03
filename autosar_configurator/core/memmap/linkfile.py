"""
Writing a generated linker file

Generation in three steps, each usable on its own (design.md D5, D6, D8):

1. ``prepare_generation`` builds the plan, checks it and, when nothing refuses, asks the
   generator for the text; nothing is written;
2. ``preview`` describes what writing it would do (path, whether a file is replaced and backed
   up, byte count); a pure function, the window shows it and asks;
3. ``write_linker_file`` writes it only when called: an existing file is first copied to
   ``<name>.bak``, the new text goes to a temporary file in the same directory that is then
   renamed, so a failure leaves the old file as it was and no half file.

``self_check`` then runs the memory map check against the written (or any) text.  It shows
that the generator and the check agree, not that the compiler links the file.
"""
import os
import shutil
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable, List, Optional, Sequence

from ..hardware.memory_regions import MemoryRegionDef
from .check import SYMBOL, UNPLACED, CheckResult, run_check
from .config import INTEGRATION_DIR, LINKED_FILE_DIR, MemoryMapConfig
from .generators import GeneratedFile, UnsupportedCompiler, compiler, generate
from .plan import Plan, build_plan, check_plan

BACKUP_SUFFIX = ".bak"
ENCODING = "utf-8"
SELF_CHECK_NOTE = ("自检只说明生成器与检查器的理解一致，不能证明编译器能链接这个文件；"
                   "最终要在编译器里实际链接一次")


class LinkFileError(OSError):
    """The linker file could not be written; the message says why.  The old file is unchanged."""


@dataclass
class Generation:
    """A generation ready to be previewed and written."""
    compiler: str
    plan: Plan
    refusals: List[str] = field(default_factory=list)
    warnings: List[str] = field(default_factory=list)
    file: Optional[GeneratedFile] = None        # None when refused

    @property
    def refused(self) -> bool:
        return bool(self.refusals)


@dataclass(frozen=True)
class Preview:
    path: Path
    replaces: bool                  # a file is there and will be replaced
    backup: Optional[Path]          # where the old file will be kept
    size: int                       # bytes to write
    unchanged: bool                 # the file there already has exactly these bytes


def target_path(project_dir: Path, compiler_key: str) -> Path:
    """``<project>/IntegrationProject/linkedFile/<Ads>/<scatter.scat>`` for the compiler."""
    entry = compiler(compiler_key)
    return Path(project_dir) / INTEGRATION_DIR / LINKED_FILE_DIR / entry.directory / entry.file_name


def prepare_generation(compiler_key: str, config: MemoryMapConfig, rows, chip_regions: Sequence[MemoryRegionDef],
                       needs: Iterable = (), layout: Optional[List[dict]] = None, source: str = "memorymap.json"
                       ) -> Generation:
    """Plan, check and generate the text.  Nothing is written.

    Raises:
        UnsupportedCompiler: the compiler has no generator (no plan is checked, no text made)
    """
    entry = compiler(compiler_key)
    if not entry.supported:
        raise UnsupportedCompiler(f"{entry.label} {entry.reason}")
    plan = build_plan(config, rows, chip_regions, needs, layout, source)
    refusals, warnings = check_plan(plan)
    generation = Generation(entry.key, plan, refusals, warnings)
    if not refusals:
        generation.file = generate(entry.key, plan)
    return generation


def _bytes(text: str) -> bytes:
    return text.encode(ENCODING)


def preview(path: Path, text: str) -> Preview:
    """What writing ``text`` to ``path`` would do.  Reads only."""
    path = Path(path)
    data = _bytes(text)
    exists = path.is_file()
    unchanged = False
    if exists:
        try:
            unchanged = path.read_bytes() == data
        except OSError:
            unchanged = False
    return Preview(path, exists, path.with_name(path.name + BACKUP_SUFFIX) if exists else None,
                   len(data), unchanged)


def write_linker_file(path: Path, text: str) -> Preview:
    """Write ``text`` to ``path``: back up an existing file as ``<name>.bak``, then write a
    temporary file next to it and rename it into place.

    Raises:
        LinkFileError: the backup or the file could not be written; the old file is unchanged
            and no temporary file is left
    """
    path = Path(path)
    shown = preview(path, text)
    temp = None
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        fd, temp = tempfile.mkstemp(dir=path.parent, prefix=path.name + ".", suffix=".tmp")
        with os.fdopen(fd, "wb") as handle:
            handle.write(_bytes(text))
        if shown.backup is not None:
            shutil.copy2(path, shown.backup)
        os.replace(temp, path)
        temp = None
    except OSError as e:
        raise LinkFileError(f"无法写入 {path}：{e}") from e
    finally:
        if temp is not None:
            try:
                os.unlink(temp)
            except OSError:
                pass
    return shown


# --- self-check ----------------------------------------------------------------------------

@dataclass
class SelfCheck:
    result: CheckResult
    note: str = SELF_CHECK_NOTE

    @property
    def missing_symbols(self):
        return self.result.by_category(SYMBOL)

    @property
    def unplaced(self):
        return self.result.by_category(UNPLACED)

    @property
    def clean(self) -> bool:
        """No missing link symbol and no section without a receiving region (the acceptance)."""
        return not self.missing_symbols and not self.unplaced


def self_check(linker_file: Path, source_dirs: Iterable[Path], header_dirs: Iterable[Path] = (),
               regions: Optional[List[MemoryRegionDef]] = None, base: Optional[Path] = None) -> SelfCheck:
    """Run the memory map check with ``linker_file`` as the linker file."""
    return SelfCheck(run_check(source_dirs, header_dirs, Path(linker_file), regions, False, base))


def self_check_text(text: str, source_dirs: Iterable[Path], header_dirs: Iterable[Path] = (),
                    regions: Optional[List[MemoryRegionDef]] = None, base: Optional[Path] = None,
                    file_name: str = "scatter.scat") -> SelfCheck:
    """Run the check against ``text`` before it is written (a temporary copy is checked)."""
    with tempfile.TemporaryDirectory() as directory:
        path = Path(directory) / file_name
        path.write_bytes(_bytes(text))
        return self_check(path, source_dirs, header_dirs, regions, base)
