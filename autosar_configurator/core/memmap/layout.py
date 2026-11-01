"""
Memory layout view data

Arranges the rows of a memory map check (``CheckResult.rows``) for display: by
physical region (chip region -> execution region -> section) or by module
(module -> section).  Both are built from the same rows and the same findings;
nothing here judges a section, the findings come from the check.  Order is
deterministic: chip regions by start address, everything else by name.
"""
from dataclasses import dataclass, field
from typing import List, Optional, Tuple

from .check import CheckResult, SectionRow

BY_REGION = "region"
BY_MODULE = "module"
UNKNOWN_CHIP_REGION = "未识别的芯片区域"
UNPLACED_GROUP = "没有区域接收"
NO_MODULE = "（未知模块）"


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


@dataclass
class ExecGroup:
    name: str                       # execution region
    address: Optional[int]
    rows: List[SectionRow] = field(default_factory=list)


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


def by_region(result: CheckResult, flt: Optional[LayoutFilter] = None) -> List[RegionGroup]:
    """Chip regions by start address, then regions whose chip region is unknown, then
    sections nothing receives; inside, execution regions by base then name."""
    groups = {}
    for row in filter_rows(result, flt):
        place = row.placement
        if place is None:
            key, start, attrs = UNPLACED_GROUP, None, ""
        elif place.chip_region is None:
            key, start, attrs = UNKNOWN_CHIP_REGION, None, ""
        else:
            key = place.chip_region
            start, attrs = _attributes(result, key)
        group = groups.setdefault(key, RegionGroup(key, start, attrs))
        exec_name = place.region if place else ""
        address = place.address if place else None
        execution = next((e for e in group.executions if e.name == exec_name), None)
        if execution is None:
            execution = ExecGroup(exec_name, address)
            group.executions.append(execution)
        execution.rows.append(row)

    def order(group: RegionGroup):
        if group.name == UNPLACED_GROUP:
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


def placement_text(row: SectionRow) -> str:
    """Where the row lands, in one line."""
    place = row.placement
    if place is None:
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
                       f"{_cell('、'.join(row.modules))} | {_cell(placement_text(row))} | {_cell(problems)} |")
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
                lines += table(execution.rows)
    return "\n".join(lines)
