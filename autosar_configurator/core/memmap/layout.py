"""
Memory layout view data

Arranges the rows of a memory map check (``CheckResult.rows``) for display: by
physical region (chip region -> execution region -> section) or by module
(module -> section).  Both are built from the same rows and the same findings;
nothing here judges a section, the findings come from the check.  Order is
deterministic: chip regions by start address, everything else by name.
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Tuple

from ..hardware.memory_regions import region_at
from .check import MAX_USES_SHOWN, CheckResult, SectionRow
from .symbols import LIMIT_REGION_SUFFIX, RegionNeed

BY_REGION = "region"
BY_MODULE = "module"
UNKNOWN_CHIP_REGION = "未识别的芯片区域"
UNPLACED_GROUP = "没有区域接收"
NOT_CHECKED_GROUP = "未检查放置"
NO_MODULE = "（未知模块）"
UNREFERENCED = "无代码引用"
MISSING_GROUP = "链接文件缺少的区域"


@dataclass(frozen=True)
class LayoutFilter:
    module: Optional[str] = None
    core: Optional[int] = None
    kind: Optional[str] = None
    only_findings: bool = False

    def accepts(self, row: SectionRow) -> bool:
        return ((self.module is None or self.module in (row.modules or (NO_MODULE,)))
                and (self.core is None or row.core == self.core)
                and (self.kind is None or row.kind == self.kind)
                and (not self.only_findings or bool(row.findings)))

    @property
    def active(self) -> bool:
        return (self.module, self.core, self.kind) != (None, None, None) or self.only_findings


@dataclass
class ExecGroup:
    name: str                       # execution region
    address: Optional[int]
    rows: List[SectionRow] = field(default_factory=list)
    need: Optional[RegionNeed] = None       # what the code needs from this region
    unreferenced: bool = False              # code refers to regions, but not to this one

    @property
    def note(self) -> str:
        if self.need is not None:
            return need_text(self.need)
        return UNREFERENCED if self.unreferenced else ""


@dataclass
class RegionGroup:
    name: str                       # chip region, or UNKNOWN_CHIP_REGION / UNPLACED_GROUP
    start: Optional[int]
    attributes: str                 # core, cacheable and type text; empty when not known
    executions: List[ExecGroup] = field(default_factory=list)

    @property
    def row_count(self) -> int:
        return sum(len(e.rows) for e in self.executions)


@dataclass
class ModuleGroup:
    name: str
    rows: List[SectionRow] = field(default_factory=list)


def filter_rows(result: CheckResult, flt: Optional[LayoutFilter] = None) -> List[SectionRow]:
    flt = flt or LayoutFilter()
    return [row for row in result.rows if flt.accepts(row)]


def modules_of(result: CheckResult) -> List[str]:
    return sorted({m for row in result.rows for m in (row.modules or (NO_MODULE,))})


def cores_of(result: CheckResult) -> List[int]:
    return sorted({row.core for row in result.rows if row.core is not None})


def _attributes(result: CheckResult, name: str) -> Tuple[Optional[int], str]:
    region = next((r for r in result.regions if r.name == name), None)
    if region is None:
        return None, ""
    cache = "可缓存" if region.cacheable else "不可缓存"
    return region.start, f"{region.core_text()}，{cache}，{region.type}"


def need_text(need: RegionNeed) -> str:
    """Who refers to a region and for what, in one line."""
    places = "、".join(f"{r.path}:{r.line}" for r in need.references[:MAX_USES_SHOWN])
    if len(need.references) > MAX_USES_SHOWN:
        places += f" 等 {len(need.references)} 处"
    return f"被引用：{need.uses_text()}（{places}）"


def _is_limit_region(result: CheckResult, name: str) -> bool:
    """``<R>_LIMIT`` of a region ``R`` in the linker file: bookkeeping for the limit symbols."""
    return name.endswith(LIMIT_REGION_SUFFIX) and name[:-len(LIMIT_REGION_SUFFIX)] in result.scatter_addresses


def by_region(result: CheckResult, flt: Optional[LayoutFilter] = None) -> List[RegionGroup]:
    """Chip regions by start address, then regions whose chip region is unknown, then
    sections nothing receives, then regions the code needs and the linker file lacks;
    inside, execution regions by base then name.

    Execution regions without sections (stacks, limit markers excepted) are listed too,
    unless a filter is on: a filter is about sections.
    """
    needs: Dict[str, RegionNeed] = {n.region: n for n in result.needs}
    groups = {}
    executions = {}

    def execution_group(key: str, start, attrs: str, name: str, address) -> ExecGroup:
        group = groups.setdefault(key, RegionGroup(key, start, attrs))
        execution = executions.get((key, name))
        if execution is None:
            execution = executions[(key, name)] = ExecGroup(
                name, address, need=needs.get(name),
                unreferenced=bool(name) and bool(needs) and name not in needs)
            group.executions.append(execution)
        return execution

    for row in filter_rows(result, flt):
        place = row.placement
        if place is None:
            # without a checked linker file nothing was placed because nothing was looked up
            key = UNPLACED_GROUP if result.placement_checked else NOT_CHECKED_GROUP
            start, attrs = None, ""
        elif place.chip_region is None:
            key, start, attrs = UNKNOWN_CHIP_REGION, None, ""
        else:
            key = place.chip_region
            start, attrs = _attributes(result, key)
        execution_group(key, start, attrs, place.region if place else "",
                        place.address if place else None).rows.append(row)

    if not (flt and flt.active):
        for name, address in result.scatter_addresses.items():
            if _is_limit_region(result, name):
                continue
            memory = region_at(result.regions, address) if address is not None else None
            if memory is None:
                execution_group(UNKNOWN_CHIP_REGION, None, "", name, address)
            else:
                execution_group(memory.name, memory.start, _attributes(result, memory.name)[1],
                                name, address)
        if result.scatter_read:
            for need in result.needs:
                if need.region not in result.scatter_addresses:
                    execution_group(MISSING_GROUP, None, "", need.region, None)

    def order(group: RegionGroup):
        if group.name == MISSING_GROUP:
            return (3, 0, group.name)
        if group.name in (UNPLACED_GROUP, NOT_CHECKED_GROUP):
            return (2, 0, group.name)
        if group.start is None:
            return (1, 0, group.name)
        return (0, group.start, group.name)

    ordered = sorted(groups.values(), key=order)
    for group in ordered:
        group.executions.sort(key=lambda e: (e.address is None, e.address or 0, e.name))
        for execution in group.executions:
            execution.rows.sort(key=lambda r: r.output)
    return ordered


def by_module(result: CheckResult, flt: Optional[LayoutFilter] = None) -> List[ModuleGroup]:
    """Modules by name; a section used by several modules is listed under each, or only
    under the module the filter names."""
    groups = {}
    for row in filter_rows(result, flt):
        for module in row.modules or (NO_MODULE,):
            if flt is not None and flt.module is not None and module != flt.module:
                continue
            groups.setdefault(module, ModuleGroup(module)).rows.append(row)
    ordered = sorted(groups.values(), key=lambda g: g.name)
    for group in ordered:
        group.rows.sort(key=lambda r: r.output)
    return ordered


def placement_text(row: SectionRow, result: Optional[CheckResult] = None) -> str:
    """Where the row lands, in one line.  Given the result, a section that was never looked
    up (no linker file, or one that is not ADS) says so instead of "no region receives it"."""
    place = row.placement
    if place is None:
        if result is not None and not result.placement_checked and result.unchecked_reason:
            return f"未检查放置（{result.unchecked_reason}）"
        return "没有区域接收"
    how = "显式" if place.explicit else f"通配 {place.selector}"
    chip = place.chip_region or "芯片区域未知"
    more = f"；另被 {'、'.join(place.also)} 选中" if place.also else ""
    return f"{place.region}（{chip}，{how}）{more}"


def row_attributes(row: SectionRow) -> str:
    parts = [row.kind]
    if row.core is not None:
        parts.append(f"核心 {row.core}")
    if row.non_cacheable:
        parts.append("不可缓存")
    return "，".join(parts)


def _cell(text: str) -> str:
    return text.replace("|", "\\|").replace("\n", " ")


def to_markdown(result: CheckResult, mode: str = BY_REGION, flt: Optional[LayoutFilter] = None,
                title: str = "内存布局") -> str:
    """The current grouping and filter as Markdown tables."""
    flt = flt or LayoutFilter()
    active = [f"模块 {flt.module}" if flt.module else "", f"核心 {flt.core}" if flt.core is not None else "",
              f"种类 {flt.kind}" if flt.kind else "", "只看有问题的" if flt.only_findings else ""]
    shown = filter_rows(result, flt)
    lines = [f"# {title}", "",
             f"- 源码目录：{', '.join(result.source_dirs) or '无'}",
             f"- MemMap 头目录：{', '.join(result.header_dirs) or '无'}",
             f"- 链接文件：{result.linker_file or '无'}",
             f"- 分组：{'按物理区域' if mode == BY_REGION else '按模块'}；"
             f"过滤：{'、'.join(a for a in active if a) or '无'}；输出段 {len(shown)} / {len(result.rows)}"]
    lines += [f"- {n}" for n in result.notes] + [""]
    header = ["| 输出段 | 属性 | 来源模块 | 放置 | 问题 |", "|---|---|---|---|---|"]

    def table(rows: List[SectionRow]) -> List[str]:
        out = list(header)
        for row in rows:
            problems = "；".join(f.text + ("（可能）" if f.possible else "") for f in row.findings)
            out.append(f"| {_cell(row.output)} | {_cell(row_attributes(row))} | "
                       f"{_cell('、'.join(row.modules))} | {_cell(placement_text(row, result))} | {_cell(problems)} |")
        return out + [""]

    if mode == BY_MODULE:
        for module in by_module(result, flt):
            lines += [f"## {module.name}（{len(module.rows)}）", ""] + table(module.rows)
    else:
        for group in by_region(result, flt):
            suffix = f"（{group.attributes}）" if group.attributes else ""
            lines += [f"## {group.name}{suffix}（{group.row_count}）", ""]
            for execution in group.executions:
                if execution.name:
                    address = f" @ {execution.address:#x}" if execution.address is not None else ""
                    lines += [f"### {execution.name}{address}", ""]
                    if execution.note:
                        lines += [f"- {execution.note}", ""]
                if execution.rows:
                    lines += table(execution.rows)
    return "\n".join(lines)
