"""
Memory map check

Compares the memory sections the code uses (``usage``), their mapping to output
sections in MemMap headers (``headers``) and the placement of those output
sections in an ADS scatter file (``scatter``), and, with the chip's memory
regions, whether core data and non-cacheable data land in suitable memory.

The check only reads.  Who wrote the linker file does not matter: OS, MCAL, SDK
and application sections are checked alike.
"""
import logging
import os
import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable, Dict, Iterable, List, Optional, Tuple

from .. import project_paths
from ..hardware.chip_dependency_scan import (
    MAX_SCAN_BYTES,
    SKIPPED_DIRS,
    ScanCancelled,
    display_path,
    resolve_scan_dir,
)
from ..hardware.memory_regions import LOCAL, MemoryRegionDef, region_at
from .headers import SectionMapping, parse_header
from .scatter import ScatterFile, parse_scatter, placements
from .symbols import LIMIT_REGION_SUFFIX, Reference, RegionNeed, merge, scan_needs
from .usage import TEMPLATE_MARK, SectionUse, is_memmap_header, scan_source

logger = logging.getLogger(__name__)

UNMAPPED = "unmapped"
USAGE = "usage"
DUPLICATE = "duplicate"
UNPLACED = "unplaced"
MULTIPLE = "multiple"
CORE = "core"
CACHE = "cache"
FLASH = "flash"
WILDCARD = "wildcard"
SYMBOL = "symbol"
CATEGORIES = (UNMAPPED, USAGE, DUPLICATE, UNPLACED, MULTIPLE, CORE, CACHE, FLASH, WILDCARD, SYMBOL)
CATEGORY_LABELS = {
    UNMAPPED: "用到但没有映射的段",
    USAGE: "段声明写法问题",
    DUPLICATE: "重复映射的段",
    UNPLACED: "没有区域接收的段",
    MULTIPLE: "被多个区域显式选中的段",
    CORE: "核心数据不在本核心内存",
    CACHE: "不可缓存的段在可缓存内存",
    FLASH: "数据段放在 flash",
    WILDCARD: "未显式放置的段",
    SYMBOL: "链接符号缺失",
}
NO_REGIONS_NOTE = "芯片没有内存区域数据（memory_regions），核心、缓存和 flash 类型检查已跳过"
DATA_KINDS = ("DATA", "BSS")
# why the placement was not looked up (shown where a section's placement would be)
NO_LINKER_FILE = "没有链接文件"
NOT_ADS_FILE = "链接文件不是 ADS 格式"
UNREADABLE_FILE = "链接文件无法读取"

ERROR = "error"
WARNING = "warning"
INFO = "info"
SEVERITIES = (ERROR, WARNING, INFO)
SEVERITY_RANK = {ERROR: 0, WARNING: 1, INFO: 2}
SEVERITY_LABELS = {ERROR: "错误", WARNING: "警告", INFO: "提示"}
# One level per category (design.md of add-memory-map-workbench, D3).  The levels follow what
# the finding means for the build: errors stop the compiler or the linker, or make the
# program wrong at run time; warnings are probably misconfigurations; info is a static guess.
SEVERITY = {
    UNMAPPED: ERROR,        # MemMap.h #error at compile time
    SYMBOL: ERROR,          # undefined symbol at link time
    FLASH: ERROR,           # data in flash cannot be written
    USAGE: ERROR,           # an unpaired START/STOP shifts every section after it
    UNPLACED: WARNING,
    MULTIPLE: WARNING,
    CORE: WARNING,
    CACHE: WARNING,
    DUPLICATE: WARNING,
    WILDCARD: INFO,
}
# These findings belong to no output section, so no section row can hold them.
NO_SECTION_CATEGORIES = (UNMAPPED, USAGE, DUPLICATE, SYMBOL)
STATIC_NOTE = ("静态检查：#if 分支一律当作会编译，其中的问题标为“可能”；"
               "通配选择器的归属按段的种类推断，与链接器的实际结果可能不同。")

SOURCE_SUFFIXES = {".c", ".h"}
SCATTER_SUFFIXES = {".scat", ".sct"}
# Generation output directory name of legacy projects (shown in the UI)
GENERATION_DIR = project_paths.ProjectDirectories.legacy().gen
MAX_USES_SHOWN = 3

_CORE = re.compile(r"(?:^|_)CORE(\d+)(?:_|$)", re.I)
_NON_CACHEABLE = re.compile(r"NO_?CACHEABLE|NON_?CACHEABLE|UNCACHED|NOCACHE", re.I)


@dataclass(frozen=True)
class Finding:
    category: str
    path: str
    line: int
    text: str
    note: str = ""
    possible: bool = False      # inside an #if branch: may not be compiled

    @property
    def severity(self) -> str:
        """The category's level, one lower when the finding sits in an ``#if`` branch (info
        stays info).  Derived, never stored, so it cannot disagree with the category."""
        level = SEVERITY[self.category]
        if self.possible and level != INFO:
            return SEVERITIES[SEVERITIES.index(level) + 1]
        return level

    def sort_key(self):
        return (CATEGORIES.index(self.category), self.path.lower(), self.line, self.text)


@dataclass(frozen=True)
class RowPlacement:
    """Where the linker file puts one output section."""
    region: str                     # execution region
    line: int                       # line of the selecting selector in the linker file
    selector: str                   # e.g. *(+BSS)
    explicit: bool                  # selected by name, not only caught by a wildcard
    address: Optional[int] = None   # base of the execution region, None when unresolved
    chip_region: Optional[str] = None       # chip region containing that base
    also: Tuple[str, ...] = ()      # further execution regions selecting it by name


@dataclass
class SectionRow:
    """One output section: what maps to it, who uses it and where it is placed."""
    output: str
    kind: str                       # TEXT, RODATA, DATA or BSS
    names: Tuple[str, ...]          # <X>_START_SEC_<Y> names mapped to it
    modules: Tuple[str, ...]        # the <X> of those names
    core: Optional[int]
    non_cacheable: bool
    uses: Tuple[Tuple[str, int], ...]       # (path, line) of the uses
    placement: Optional[RowPlacement] = None
    findings: List[Finding] = field(default_factory=list)


@dataclass
class CheckResult:
    findings: List[Finding] = field(default_factory=list)
    source_dirs: List[str] = field(default_factory=list)
    header_dirs: List[str] = field(default_factory=list)
    linker_file: str = ""
    files_scanned: int = 0
    headers_read: int = 0
    sections_used: int = 0
    templates_skipped: int = 0
    skipped: List[str] = field(default_factory=list)       # over the size limit
    notes: List[str] = field(default_factory=list)
    rows: List[SectionRow] = field(default_factory=list)   # one per mapped output section
    regions: List[MemoryRegionDef] = field(default_factory=list)
    regions_unconfirmed: bool = False
    needs: List[RegionNeed] = field(default_factory=list)  # regions the code refers to
    scatter_regions: List[str] = field(default_factory=list)    # execution regions of the linker file
    scatter_addresses: Dict[str, Optional[int]] = field(default_factory=dict)   # their resolved bases
    scatter_read: bool = False                              # an ADS linker file was read
    placement_checked: bool = False         # the sections were looked up in an ADS linker file
    unchecked_reason: str = ""              # why not: no linker file, or a format not supported

    def by_category(self, category: str) -> List[Finding]:
        return [f for f in self.findings if f.category == category]

    def findings_without_section(self) -> List[Finding]:
        """The findings no section row holds: a missing mapping has no output section, a
        missing link symbol belongs to an execution region, a declaration problem to a file."""
        attached = {id(f) for row in self.rows for f in row.findings}
        return [f for f in self.findings if id(f) not in attached]

    def severity_counts(self, findings: Optional[List[Finding]] = None) -> Dict[str, int]:
        """Findings per severity (all findings of the result when none are given)."""
        counts = {severity: 0 for severity in SEVERITIES}
        for f in self.findings if findings is None else findings:
            counts[f.severity] += 1
        return counts


def section_core(*names: str) -> Optional[int]:
    for name in names:
        m = _CORE.search(name)
        if m:
            return int(m.group(1))
    return None


def is_non_cacheable(*names: str) -> bool:
    return any(_NON_CACHEABLE.search(n) for n in names)


def _files_in(directory: Path, suffixes) -> List[Path]:
    found = []
    for root, dirs, files in os.walk(directory):
        dirs[:] = sorted(d for d in dirs if d not in SKIPPED_DIRS)
        found.extend(Path(root) / name for name in sorted(files)
                     if Path(name).suffix.lower() in suffixes)
    return found


def _read(path: Path) -> Optional[str]:
    try:
        return path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return None


def section_module(name: str) -> str:
    """The module of ``<X>_START_SEC_<Y>`` (or ``_STOP_SEC_``): ``<X>``."""
    return re.split(r"_(?:START|STOP)_SEC_", name, maxsplit=1)[0]


def _where(use: SectionUse) -> str:
    return f"{use.path}:{use.line}"


def _uses_text(uses: List[SectionUse]) -> str:
    shown = "、".join(_where(u) for u in uses[:MAX_USES_SHOWN])
    return f"使用于 {shown}" + (f" 等 {len(uses)} 处" if len(uses) > MAX_USES_SHOWN else "")


def run_check(source_dirs: Iterable[Path], header_dirs: Iterable[Path] = (),
              linker_file: Optional[Path] = None,
              regions: Optional[List[MemoryRegionDef]] = None, regions_unconfirmed: bool = False,
              base: Optional[Path] = None,
              progress: Optional[Callable[[int, int, str], bool]] = None) -> CheckResult:
    """Check the sources in ``source_dirs`` against the MemMap headers found there and
    in ``header_dirs`` and against ``linker_file``.

    Args:
        regions: the chip's memory regions (None or empty: no core and cache checks)
        base: project directory, for the paths shown
        progress: called before each file with (index, total, path); returning
            False cancels the check (ScanCancelled)
    """
    source_dirs, header_dirs = list(source_dirs), list(header_dirs)
    result = CheckResult(source_dirs=[display_path(d, base) for d in source_dirs],
                         header_dirs=[display_path(d, base) for d in header_dirs])
    sources: Dict[Path, Path] = {}
    headers: Dict[Path, Path] = {}
    for directory in source_dirs:
        if not directory.is_dir():
            result.notes.append(f"源码目录不存在，已跳过：{display_path(directory, base)}")
            continue
        for f in _files_in(directory, SOURCE_SUFFIXES):
            (headers if is_memmap_header(f.name) else sources).setdefault(f.resolve(), f)
    for directory in header_dirs:
        if not directory.is_dir():
            result.notes.append(f"MemMap 头目录不存在，已跳过：{display_path(directory, base)}")
            continue
        for f in _files_in(directory, {".h"}):
            if is_memmap_header(f.name):
                headers.setdefault(f.resolve(), f)
    ordered = sorted(list(headers.values()) + list(sources.values()),
                     key=lambda p: display_path(p, base).lower())

    uses: List[SectionUse] = []
    references: List[Reference] = []
    mappings: Dict[str, List[Dict[str, SectionMapping]]] = {}     # header file name -> maps
    for index, path in enumerate(ordered):
        shown = display_path(path, base)
        if progress is not None and progress(index, len(ordered), shown) is False:
            raise ScanCancelled()
        try:
            too_big = path.stat().st_size > MAX_SCAN_BYTES
        except OSError:
            continue
        if too_big:
            result.skipped.append(shown)
            continue
        text = _read(path)
        if text is None:
            continue
        if TEMPLATE_MARK in text:
            result.templates_skipped += 1
            continue
        result.files_scanned += 1
        if path.resolve() in headers:
            found, repeated = parse_header(text, shown)
            mappings.setdefault(path.name.lower(), []).append({m.name: m for m in found})
            result.headers_read += 1
            for m in repeated:
                result.findings.append(Finding(DUPLICATE, m.path, m.line,
                                               f"{m.name} 重复映射到 {m.output}"))
            continue
        found_uses, problems = scan_source(text, shown)
        uses.extend(found_uses)
        references.extend(scan_needs(text, shown))
        result.findings.extend(Finding(USAGE, p.path, p.line, p.text, possible=p.conditional)
                               for p in problems)
    result.needs = merge(references)

    # --- mapping ---------------------------------------------------------------
    everywhere: Dict[str, SectionMapping] = {}
    for name in sorted(mappings):
        for table in mappings[name]:
            for section, mapping in table.items():
                everywhere.setdefault(section, mapping)
    outputs: Dict[str, Tuple[SectionMapping, List[SectionUse]]] = {}
    names: Dict[str, set] = {}                    # output section -> <X>_START_SEC_<Y> names
    missing_headers: Dict[str, List[SectionUse]] = {}
    for use in uses:
        if use.header and use.header.lower() not in mappings:
            missing_headers.setdefault(use.header, []).append(use)
            continue
        if use.header:
            mapping = next((t[use.name] for t in mappings[use.header.lower()] if use.name in t), None)
        else:
            mapping = everywhere.get(use.name)
        if mapping is None:
            where = f"在 {use.header} 中" if use.header else "在任何 MemMap 头中都"
            result.findings.append(Finding(UNMAPPED, use.path, use.line,
                                           f"{use.name} {where}没有映射", "编译时会触发 MemMap 的 #error",
                                           use.conditional))
            continue
        outputs.setdefault(mapping.output, (mapping, []))[1].append(use)
        names.setdefault(mapping.output, set()).add(use.name)
    result.rows = _rows(outputs, names)
    result.regions, result.regions_unconfirmed = list(regions or []), regions_unconfirmed
    for header, header_uses in sorted(missing_headers.items()):
        first = header_uses[0]
        result.findings.append(Finding(UNMAPPED, first.path, first.line,
                                       f"找不到 {header}（已添加的目录中没有）",
                                       f"{len(header_uses)} 处段声明包含它，这些段都无法检查映射"))
    result.sections_used = len({u.name for u in uses})

    # --- placement -------------------------------------------------------------
    # The notes about the chip's memory regions do not depend on the linker file: they say
    # what the core, cache and flash checks can rest on, and are wanted before one is set.
    if not regions:
        result.notes.append(NO_REGIONS_NOTE)
    elif regions_unconfirmed:
        result.notes.append("芯片的内存区域数据标记为待确认，核心、缓存和 flash 类型检查的结论需人工核对")
    if linker_file is None:
        result.unchecked_reason = NO_LINKER_FILE
        result.notes.append("没有设置链接文件，放置检查已跳过")
        return _finish(result, progress, len(ordered))
    result.linker_file = display_path(linker_file, base)
    if linker_file.suffix.lower() not in SCATTER_SUFFIXES:
        result.unchecked_reason = NOT_ADS_FILE
        result.notes.append(f"目前只支持 ADS 分散加载文件（.scat、.sct），"
                            f"{linker_file.name} 的放置检查已跳过")
        return _finish(result, progress, len(ordered))
    text = _read(linker_file)
    if text is None:
        result.unchecked_reason = UNREADABLE_FILE
        result.notes.append(f"链接文件无法读取，放置检查已跳过：{result.linker_file}")
        return _finish(result, progress, len(ordered))
    scatter = parse_scatter(text, result.linker_file)
    result.scatter_regions = [r.name for r in scatter.regions]
    result.scatter_addresses = {r.name: r.address for r in scatter.regions}
    result.scatter_read = True
    result.placement_checked = True
    _check_symbols(result, scatter)
    _check_placement(result, scatter, outputs, regions or [])
    return _finish(result, progress, len(ordered))


def _check_symbols(result: CheckResult, scatter: ScatterFile):
    """Regions the code refers to that the scatter file does not provide, and regions
    needed for a limit that have no ``<R>_LIMIT`` region."""
    have = {r.name for r in scatter.regions}
    for need in result.needs:
        first = need.references[0]
        uses = need.uses_text()
        places = "、".join(f"{r.path}:{r.line}" for r in need.references[:MAX_USES_SHOWN])
        if len(need.references) > MAX_USES_SHOWN:
            places += f" 等 {len(need.references)} 处"
        if need.region not in have:
            result.findings.append(Finding(
                SYMBOL, first.path, first.line, f"链接文件缺少执行区域 {need.region}",
                f"用途：{uses}；引用于 {places}", need.conditional))
        elif need.needs_limit_region() and need.region + LIMIT_REGION_SUFFIX not in have:
            result.findings.append(Finding(
                SYMBOL, first.path, first.line,
                f"链接文件缺少界限区域 {need.region}{LIMIT_REGION_SUFFIX}",
                f"用途：{uses}；引用于 {places}", need.conditional))


def _rows(outputs: Dict[str, Tuple[SectionMapping, List[SectionUse]]],
          names: Dict[str, set]) -> List[SectionRow]:
    rows = []
    for output in sorted(outputs):
        mapping, uses = outputs[output]
        section_names = tuple(sorted(names[output]))
        rows.append(SectionRow(
            output=output, kind=mapping.kind, names=section_names,
            modules=tuple(sorted({section_module(n) for n in section_names})),
            core=section_core(*section_names, output),
            non_cacheable=is_non_cacheable(*section_names, output),
            uses=tuple(sorted({(u.path, u.line) for u in uses}))))
    return rows


def _check_placement(result: CheckResult, scatter: ScatterFile,
                     outputs: Dict[str, Tuple[SectionMapping, List[SectionUse]]],
                     regions: List[MemoryRegionDef]):
    unresolved, outside = set(), set()
    rows = {row.output: row for row in result.rows}

    def report(output: str, finding: Finding):
        result.findings.append(finding)
        rows[output].findings.append(finding)

    for output in sorted(outputs):
        mapping, uses = outputs[output]
        note = f"{mapping.name}；{_uses_text(uses)}"
        possible = all(u.conditional for u in uses)
        found = placements(scatter, output, mapping.kind)
        if not found:
            first = uses[0]
            report(output, Finding(UNPLACED, first.path, first.line,
                                   f"{output}（{mapping.kind}）没有被任何执行区域接收", note, possible))
            continue
        chosen = found[0]
        region, selector = chosen.region, chosen.selector
        others = tuple(dict.fromkeys(p.region.name for p in found[1:] if p.region.name != region.name))
        row = rows[output]
        row.placement = RowPlacement(region.name, selector.line, selector.text(), chosen.explicit,
                                     region.address, None, others)
        if chosen.explicit and others:
            report(output, Finding(
                MULTIPLE, scatter.path, selector.line,
                f"{output} 被多个执行区域显式选中：{region.name}、{'、'.join(others)}",
                f"{note}；链接器取哪一个由其选择规则决定，请只保留一处", possible))
        if not chosen.explicit:
            more = "；另有 " + "、".join(f"{p.region.name} 的 {p.selector.text()}" for p in found[1:]) \
                if len(found) > 1 else ""
            report(output, Finding(WILDCARD, scatter.path, selector.line,
                                   f"{output} 未显式放置，由 {region.name} 的 {selector.text()} 接收",
                                   note + more, possible))
        if not regions:
            continue
        if region.address is None:
            unresolved.add(region.name)
            continue
        memory = region_at(regions, region.address)
        if memory is None:
            outside.add((region.name, region.address))
            continue
        row.placement = RowPlacement(region.name, selector.line, selector.text(), chosen.explicit,
                                     region.address, memory.name, others)
        core = section_core(mapping.name, output)
        if (core is not None and mapping.kind in DATA_KINDS and memory.core != LOCAL
                and memory.core != core):
            report(output, Finding(
                CORE, scatter.path, selector.line,
                f"核心 {core} 的 {output} 放在 {region.name}，位于 {memory.name}（{memory.core_text()}）",
                note, possible))
        if is_non_cacheable(mapping.name, output) and memory.cacheable:
            report(output, Finding(
                CACHE, scatter.path, selector.line,
                f"不可缓存的 {output} 放在 {region.name}，位于可缓存的 {memory.name}", note, possible))
        if mapping.kind in DATA_KINDS and memory.type == "flash":
            report(output, Finding(
                FLASH, scatter.path, selector.line,
                f"{mapping.kind} 段 {output} 放在 {region.name}，位于 flash 区域 {memory.name}",
                note, possible))
    for name in sorted(unresolved):
        result.notes.append(f"执行区域 {name} 的基址无法解析，其中的段未做核心和缓存检查")
    for name, address in sorted(outside):
        result.notes.append(f"执行区域 {name} 的基址 {address:#x} 不在芯片的任何内存区域内")


def _finish(result: CheckResult, progress, total: int) -> CheckResult:
    result.findings = sorted(set(result.findings), key=Finding.sort_key)
    if progress is not None:
        progress(total, total, "")
    return result


# --- project -------------------------------------------------------------------

def _project_dir(project) -> Optional[Path]:
    path = getattr(project, "path", None)
    if not path:
        return None
    path = Path(path)
    return path.parent if path.suffix == ".dpa" else path


def project_regions(project) -> Tuple[List[MemoryRegionDef], bool, str]:
    """(memory regions of the project's chip, whether they are marked unconfirmed, a note
    when the project's own chip copy has no regions but the library's chip does)."""
    from ..hardware.chip_completeness import unconfirmed_marks
    from ..hardware.ecu_resource_resolver import chip_for_project
    from ..hardware.project_chip_store import SOURCE_PROJECT

    try:
        source, chip = chip_for_project(project, getattr(project, "chip_database", None))
    except Exception as e:  # noqa: BLE001 - the check runs without chip data
        logger.warning("Chip data not available for the memory map check: %s", e)
        return [], False, ""
    if chip is None:
        return [], False, ""
    regions = list(getattr(chip, "memory_regions", []) or [])
    note = ""
    if not regions and source == SOURCE_PROJECT:
        library = project._chip_library().get_chip(chip.name)
        if library is not None and getattr(library, "memory_regions", None):
            note = (f"工程的芯片副本 chips/{chip.name}.yaml 没有内存区域，芯片库中的有；"
                    f"可在工程属性中从芯片库更新")
    return regions, any(k.split(".", 1)[0] == "memory_regions" for k in unconfirmed_marks(chip)), note


def check_project(project, progress=None) -> CheckResult:
    """Run the check with the project's settings; the generation output
    (``generateCode``) is always scanned as a source directory."""
    base = _project_dir(project)
    dirs = [resolve_scan_dir(d, base) for d in getattr(project, "memmap_source_dirs", []) or []]
    gen = base / project_paths.dirs(project).gen if base is not None else None
    if gen is not None and gen.is_dir():
        dirs.append(gen)
    header_dirs = [resolve_scan_dir(d, base) for d in getattr(project, "memmap_header_dirs", []) or []]
    linker = getattr(project, "memmap_linker_file", None)
    regions, unconfirmed, note = project_regions(project)
    result = run_check(dirs, header_dirs, resolve_scan_dir(linker, base) if linker else None,
                       regions, unconfirmed, base, progress)
    if note:
        result.notes.append(note)
    return result


# --- checklist -----------------------------------------------------------------

def to_markdown(result: CheckResult, title: str = "内存映射检查清单",
                findings: Optional[List[Finding]] = None) -> str:
    """Markdown checklist: one unchecked item per finding, grouped by category."""
    findings = result.findings if findings is None else findings
    lines = [f"# {title}", "", f"> {STATIC_NOTE}", "",
             f"- 源码目录：{', '.join(result.source_dirs) or '无'}",
             f"- MemMap 头目录：{', '.join(result.header_dirs) or '无'}",
             f"- 链接文件：{result.linker_file or '无'}",
             (f"- 扫描文件 {result.files_scanned} 个（其中 MemMap 头 {result.headers_read} 个），"
              f"跳过模板 {result.templates_skipped} 个，用到的段 {result.sections_used} 个")]
    lines += [f"- {n}" for n in result.notes]
    counts = result.severity_counts(findings)
    lines += [f"- 发现：" + "，".join(f"{SEVERITY_LABELS[s]} {counts[s]}" for s in SEVERITIES), ""]
    for category in CATEGORIES:
        items = [f for f in findings if f.category == category]
        if not items:
            continue
        lines += [f"## {CATEGORY_LABELS[category]}（{len(items)}）", ""]
        for f in items:
            where = f"{f.path}:{f.line}" if f.line else f.path
            possible = "（可能）" if f.possible else ""
            note = f" — {f.note}" if f.note else ""
            lines.append(f"- [ ] `{where}` {f.text.replace('`', chr(39))}{possible}{note}")
        lines.append("")
    if result.skipped:
        lines += ["## 未扫描（超过 2 MB）", ""] + [f"- `{p}`" for p in result.skipped] + [""]
    return "\n".join(lines)
