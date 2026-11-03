"""
Linker plan

What a linker file has to say, without the syntax of any compiler (design.md D1): one load
region, the execution regions in window order with their start (the window's base for the
first region of a window, else "after the previous region, aligned"), the output sections
each one takes, which of them need a ``<name>_LIMIT`` region, and the reserved regions for
cores the chip does not have.  A generator reads only the plan.

Built from the layout configuration, the scan rows (placed with ``rules.place_all``), the
chip's memory regions and the link symbol needs.  Same input, same plan: windows, regions
and sections are ordered by fixed keys, never by dictionary or set order.
"""
import re
from dataclasses import dataclass
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

from ..hardware.memory_regions import MemoryRegionDef
from .check import SectionRow
from .config import CONFIG_FILE, RESERVED, STACK, MemoryMapConfig
from .rules import AGAIN, BY_RULE, MANUAL, NOT_PLACED, Placement, place_all
from .symbols import LIMIT_REGION_SUFFIX, USES, RegionNeed

RESERVE_MISSING_CORES = "reserve_missing_cores"     # key in MemoryMapConfig.options, default on
LOAD_REGION_NAME = "ROM_CODE"                       # the vendor's name for its one load region
DEFAULT_STACK_SIZE = 0x1000                         # the vendor's stack size
RESERVED_ALIGN = 64                                 # the vendor's alignment for reserved regions
EMPTY_KINDS = (STACK, RESERVED)                     # regions written as EMPTY, taking no sections
FLASH = "flash"

_NOT_IDENTIFIER = re.compile(r"\W")


# --- the option ------------------------------------------------------------------------

def reserve_missing_cores(config: MemoryMapConfig) -> bool:
    """Whether regions of cores the chip lacks are written as reserved regions (default on)."""
    return bool(config.options.get(RESERVE_MISSING_CORES, True))


def set_reserve_missing_cores(config: MemoryMapConfig, on: bool) -> None:
    config.options[RESERVE_MISSING_CORES] = bool(on)


# --- the plan --------------------------------------------------------------------------

@dataclass(frozen=True)
class Window:
    """A memory window (a chip memory region) that holds at least one execution region."""
    name: str
    base: int
    size: int
    type: str

    @property
    def symbol(self) -> str:
        """The name its base address goes by in a linker file (``CPU0BTCM_ADDRESS``)."""
        return _NOT_IDENTIFIER.sub("_", self.name) + "_ADDRESS"


@dataclass(frozen=True)
class LoadRegion:
    name: str
    window: str                     # the window it starts at
    base: int
    size: int                       # upper bound: the window's size (no capacity is known)


@dataclass(frozen=True)
class PlanRegion:
    """One execution region."""
    name: str
    load_region: str
    window: str
    kind: str
    align: int
    start_window: Optional[str]     # starts at this window's base (first region of the window)
    after: Optional[str]            # else after this region, aligned to ``align``
    sections: Tuple[str, ...]       # output sections, sorted by name
    size: int                       # upper bound, or the EMPTY length of a stack/reserved region
    needs_limit: bool               # a <name>_LIMIT region has to follow
    uses: Tuple[str, ...]           # what code uses it for (symbols.USES), no syntax
    required: bool

    @property
    def empty(self) -> bool:
        return self.kind in EMPTY_KINDS


@dataclass(frozen=True)
class ReservedRegion:
    """An empty region for a core the chip does not have, so that code naming it links."""
    name: str
    after: Optional[str]            # the last execution region; None: the load region's base
    align: int
    needs_limit: bool
    uses: Tuple[str, ...]


@dataclass(frozen=True)
class Plan:
    chip: str
    source: str                                 # the configuration it comes from
    load_regions: Tuple[LoadRegion, ...]
    windows: Tuple[Window, ...]                 # in region order
    regions: Tuple[PlanRegion, ...]
    reserved: Tuple[ReservedRegion, ...]
    placements: Tuple[Placement, ...]           # every section's status, by section name
    no_window: Tuple[str, ...] = ()             # regions on no window: left out, refused
    unknown_windows: Tuple[Tuple[str, str], ...] = ()   # (region, window) not on the chip: refused
    missing_needed: Tuple[str, ...] = ()        # names code refers to that are not configured
    needs_scanned: bool = True                  # False: no code naming regions was scanned
    reserve_missing_cores: bool = True

    def region(self, name: str) -> Optional[PlanRegion]:
        return next((r for r in self.regions if r.name == name), None)

    def window(self, name: str) -> Optional[Window]:
        return next((w for w in self.windows if w.name == name), None)

    def limit_regions(self) -> List[str]:
        """Names of the regions that need a ``<name>_LIMIT`` region, in plan order."""
        return ([r.name for r in self.regions if r.needs_limit]
                + [r.name for r in self.reserved if r.needs_limit])

    def by_status(self, status: str) -> List[Placement]:
        return [p for p in self.placements if p.status == status]


def _window_key(region: MemoryRegionDef):
    """Flash windows first (the load region and the root region are there), then by address."""
    return (0 if region.type == FLASH else 1, region.start, region.name)


def build_plan(config: MemoryMapConfig, rows: Iterable[SectionRow],
               chip_regions: Sequence[MemoryRegionDef], needs: Iterable[RegionNeed] = (),
               layout: Optional[List[dict]] = None, source: str = CONFIG_FILE) -> Plan:
    """The linker plan for ``config``.

    Args:
        rows: the scan's section rows; each is placed with ``rules.place_all``
        chip_regions: the chip's memory regions; an execution region's window is one of them
        needs: the link symbol needs of the scanned code (``CheckResult.needs``)
        layout: the chip's factory layout (``FactoryData.layout``); an entry's ``size`` is the
            region's upper bound (a stack's length); without it the window's size (a stack: 0x1000)
    """
    placements = tuple(place_all(config, rows))
    by_target: Dict[str, List[str]] = {}
    for p in placements:
        if p.status in (BY_RULE, MANUAL) and p.target:
            by_target.setdefault(p.target, []).append(p.section)

    needs = list(needs)
    # Code naming "<R>_LIMIT" itself (a macro called with the limit region's name) asks for
    # R's limit region: that name is made by the generator, never configured.
    named_limits = {n.region[:-len(LIMIT_REGION_SUFFIX)] for n in needs
                    if n.region.endswith(LIMIT_REGION_SUFFIX)}
    needs = [n for n in needs if not n.region.endswith(LIMIT_REGION_SUFFIX)]
    needs_scanned = bool(needs) or bool(named_limits)
    uses_of: Dict[str, Tuple[str, ...]] = {
        n.region: tuple(sorted(set(n.uses), key=USES.index)) for n in needs}
    limited = {n.region for n in needs if n.needs_limit_region()} | named_limits

    def needs_limit(name: str) -> bool:
        # Without any scanned code nothing says which regions need a limit: every region gets
        # one, the safe side (an unused empty region is harmless, a missing one fails to link).
        return name in limited if needs_scanned else True

    sizes = {e["name"]: int(str(e["size"]), 0) for e in (layout or []) if e.get("size") is not None}
    chip = {r.name: r for r in chip_regions}

    no_window, unknown, placeable = [], [], []
    for region in sorted(config.regions, key=lambda r: r.name):
        if not region.window:
            no_window.append(region.name)
        elif region.window not in chip:
            unknown.append((region.name, region.window))
        else:
            placeable.append(region)

    windows = sorted({chip[r.window].name: chip[r.window] for r in placeable}.values(), key=_window_key)
    load = None
    if windows:
        first = next((w for w in windows if w.type == FLASH), windows[0])
        load = LoadRegion(LOAD_REGION_NAME, first.name, first.start, first.size)

    plan_regions: List[PlanRegion] = []
    for window in windows:
        members = sorted((r for r in placeable if r.window == window.name), key=lambda r: (r.order, r.name))
        previous: Optional[str] = None
        for region in members:
            if region.kind == STACK:
                size = sizes.get(region.name, DEFAULT_STACK_SIZE)
            elif region.kind == RESERVED:
                size = sizes.get(region.name, 0)
            else:
                size = sizes.get(region.name, window.size)
            plan_regions.append(PlanRegion(
                name=region.name, load_region=load.name, window=window.name, kind=region.kind,
                align=region.align, start_window=None if previous else window.name, after=previous,
                sections=tuple(sorted(by_target.get(region.name, ()))),
                size=size, needs_limit=needs_limit(region.name),
                uses=uses_of.get(region.name, ()), required=region.required))
            previous = region.name

    reserved: Tuple[ReservedRegion, ...] = ()
    on = reserve_missing_cores(config)
    if on:
        last = plan_regions[-1].name if plan_regions else None
        reserved = tuple(ReservedRegion(name, last, RESERVED_ALIGN, needs_limit(name), uses_of.get(name, ()))
                         for name in sorted(set(config.trimmed)))

    configured = {r.name for r in config.regions} | set(config.trimmed)
    missing = tuple(sorted(name for name in set(uses_of) | named_limits if name not in configured))

    return Plan(chip=config.chip, source=source, load_regions=(load,) if load else (),
                windows=tuple(Window(w.name, w.start, w.size, w.type) for w in windows),
                regions=tuple(plan_regions), reserved=reserved, placements=placements,
                no_window=tuple(no_window), unknown_windows=tuple(unknown),
                missing_needed=missing, needs_scanned=needs_scanned, reserve_missing_cores=on)


def plan_from_check(config: MemoryMapConfig, result, layout: Optional[List[dict]] = None,
                    source: str = CONFIG_FILE) -> Plan:
    """The plan for a scan result (``check.CheckResult``): its rows, chip regions and needs."""
    return build_plan(config, result.rows, result.regions, result.needs, layout, source)


# --- before generating -------------------------------------------------------------------

DEFAULT_LAYOUT_WARNING = ("必需区域来自芯片的默认布局，未经代码核对（没有扫描到引用链接符号的代码）；"
                          "因此无法知道哪些区域需要界限区域，已为每个区域写界限区域")


def check_plan(plan: Plan) -> Tuple[List[str], List[str]]:
    """(refusals, warnings).  With any refusal nothing is generated (design.md D5)."""
    refusals: List[str] = []
    warnings: List[str] = []
    if not plan.regions:
        refusals.append("配置里没有落在芯片存储窗口上的执行区域，无法生成")
    for p in plan.by_status(AGAIN):
        refusals.append(f"段 {p.section} 待重新放置（指向 {p.target}，该区域已不存在或不接收它）")
    for name in plan.no_window:
        refusals.append(f"区域 {name} 没有落到任何存储窗口，生成不出它的起点")
    for name, window in plan.unknown_windows:
        refusals.append(f"区域 {name} 所在的窗口 {window} 不在当前芯片的存储里")
    for p in plan.by_status(NOT_PLACED):
        warnings.append(f"段 {p.section} 未放置：生成的文件里没有区域按名字接收它")
    if not plan.needs_scanned:
        warnings.append(DEFAULT_LAYOUT_WARNING)
    for name in plan.missing_needed:
        warnings.append(f"代码引用了区域 {name}，但配置里没有它，生成的文件里也不会有")
    return refusals, warnings
