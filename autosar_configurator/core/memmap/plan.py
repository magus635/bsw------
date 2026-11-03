"""
Linker plan

What a linker file has to say, without the syntax of any compiler (design.md D1): the load
regions (the configured ones in their order; none configured: one ``ROM_CODE`` on the first
flash window), the execution regions of each in window order with their start, the output
sections each one takes, which of them need a ``<name>_LIMIT`` region, and the reserved
regions for cores the chip does not have (in the first load region).  A generator reads only
the plan.

update-linker-generator-authority: a region starts (D1) after the previous region of its
window, aligned (the default; the first region of a window at the window's base), at the
window's base plus an offset, or at a fixed address.  Its size (D2) is the configured one,
else the window's size (a stack 0x1000, a reserved region 0).  Its limit region is aligned to
its ``limit_align`` (D4, default 64).

Built from the layout configuration, the scan rows (placed with ``rules.place_all``), the
chip's memory regions and the link symbol needs.  Same input, same plan: windows, regions
and sections are ordered by fixed keys, never by dictionary or set order.
"""
import re
from dataclasses import dataclass
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

from ..hardware.memory_regions import MemoryRegionDef
from .check import SectionRow
from .config import (AFTER, CONFIG_FILE, DEFAULT_LIMIT_ALIGN, FIXED, OFFSET, RESERVED, STACK, MemoryMapConfig,
                     region_doubts)
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
    size: int                       # upper bound: the configured one, else the window's size


@dataclass(frozen=True)
class PlanRegion:
    """One execution region."""
    name: str
    load_region: str
    window: str
    kind: str
    align: int
    start_window: Optional[str]     # starts at this window's base (+ ``offset``): the first region
                                    # of a window, or start mode "offset"
    after: Optional[str]            # else after this region, aligned to ``align``
    sections: Tuple[str, ...]       # output sections, sorted by name
    size: int                       # upper bound, or the EMPTY length of a stack/reserved region
    needs_limit: bool               # a <name>_LIMIT region has to follow
    uses: Tuple[str, ...]           # what code uses it for (symbols.USES), no syntax
    required: bool
    start_mode: str = AFTER         # config.AFTER, OFFSET or FIXED
    offset: int = 0                 # start mode "offset": added to the window's base
    address: Optional[int] = None   # start mode "fixed": the start (start_window, after are None)
    limit_align: int = DEFAULT_LIMIT_ALIGN      # alignment of its <name>_LIMIT region

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
    unknown_load_regions: Tuple[Tuple[str, str], ...] = ()  # (region, load region) not configured: refused
    unknown_load_windows: Tuple[Tuple[str, str], ...] = ()  # (load region, window) not on the chip: refused
    empty_load_regions: Tuple[str, ...] = ()    # configured but holding nothing: left out, warned
    forward_after: Tuple[Tuple[str, str], ...] = ()     # (region, previous) in a later load region: warned
    doubts: Tuple[str, ...] = ()                # config.region_doubts: warned, never refused

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

    # the load regions: the configured ones in their order, else one ROM_CODE (made below)
    configured_loads = list(config.load_regions)
    load_names = [l.name for l in configured_loads] or [LOAD_REGION_NAME]
    unknown_load_windows = tuple((l.name, l.window) for l in configured_loads if l.window not in chip)

    no_window, unknown, unknown_load, placeable = [], [], [], []
    for region in sorted(config.regions, key=lambda r: r.name):
        if not region.window:
            no_window.append(region.name)
        elif region.window not in chip:
            unknown.append((region.name, region.window))
        elif region.load_region and region.load_region not in load_names:
            unknown_load.append((region.name, region.load_region))
        else:
            placeable.append(region)

    # windows holding a region, and those a configured load region starts at (its base symbol)
    load_windows = [chip[l.window] for l in configured_loads if l.window in chip]
    windows = sorted({w.name: w for w in [chip[r.window] for r in placeable] + load_windows}.values(),
                     key=_window_key)
    loads: List[LoadRegion] = []
    if configured_loads:
        loads = [LoadRegion(l.name, l.window, chip[l.window].start, l.size)
                 for l in configured_loads if l.window in chip]
    elif windows:
        first = next((w for w in windows if w.type == FLASH), windows[0])
        loads = [LoadRegion(LOAD_REGION_NAME, first.name, first.start, first.size)]
    load_of = {r.name: (r.load_region or load_names[0]) for r in placeable}

    # The chain inside a window is by order, then name, whatever the load region and start
    # mode: an "after" region follows the region before it in its window (D1).
    previous_of: Dict[str, Optional[str]] = {}
    for window in windows:
        previous: Optional[str] = None
        for region in sorted((r for r in placeable if r.window == window.name), key=lambda r: (r.order, r.name)):
            previous_of[region.name] = previous
            previous = region.name

    def size_of(region, window) -> int:
        if region.size is not None:
            return region.size
        if region.kind == STACK:
            return sizes.get(region.name, DEFAULT_STACK_SIZE)
        if region.kind == RESERVED:
            return sizes.get(region.name, 0)
        return sizes.get(region.name, window.size)

    plan_regions: List[PlanRegion] = []
    for load in loads:
        for window in windows:
            members = sorted((r for r in placeable if r.window == window.name and load_of[r.name] == load.name),
                             key=lambda r: (r.order, r.name))
            for region in members:
                previous = previous_of[region.name]
                mode, start_window, after, offset, address = AFTER, None, None, 0, None
                if region.start_mode == FIXED and region.address is not None:
                    mode, address = FIXED, region.address
                elif region.start_mode == OFFSET:
                    mode, start_window, offset = OFFSET, window.name, region.offset
                elif previous is None:
                    start_window = window.name
                else:
                    after = previous
                plan_regions.append(PlanRegion(
                    name=region.name, load_region=load.name, window=window.name, kind=region.kind,
                    align=region.align, start_window=start_window, after=after,
                    sections=tuple(sorted(by_target.get(region.name, ()))),
                    size=size_of(region, window), needs_limit=needs_limit(region.name),
                    uses=uses_of.get(region.name, ()), required=region.required,
                    start_mode=mode, offset=offset, address=address, limit_align=region.limit_align))

    # A load region with no execution region in it is left out (armlink needs at least one);
    # the first one stays when it takes the reserved regions.
    on = reserve_missing_cores(config)
    has_reserved = on and bool(config.trimmed)
    filled = {r.load_region for r in plan_regions}
    empty_loads = tuple(l.name for index, l in enumerate(loads)
                        if l.name not in filled and not (index == 0 and has_reserved))
    loads = [l for l in loads if l.name not in empty_loads]

    position = {name: index for index, name in enumerate(load_names)}
    load_index = {r.name: position[r.load_region] for r in plan_regions}
    forward = tuple((r.name, r.after) for r in plan_regions
                    if r.after is not None and load_index[r.after] > load_index[r.name])

    reserved: Tuple[ReservedRegion, ...] = ()
    if on:
        # in the first load region, after its last execution region (none: at its base)
        in_first = [r.name for r in plan_regions if loads and r.load_region == loads[0].name]
        last = in_first[-1] if in_first else None
        reserved = tuple(ReservedRegion(name, last, RESERVED_ALIGN, needs_limit(name), uses_of.get(name, ()))
                         for name in sorted(set(config.trimmed)))

    configured = {r.name for r in config.regions} | set(config.trimmed)
    missing = tuple(sorted(name for name in set(uses_of) | named_limits if name not in configured))

    return Plan(chip=config.chip, source=source, load_regions=tuple(loads),
                windows=tuple(Window(w.name, w.start, w.size, w.type) for w in windows),
                regions=tuple(plan_regions), reserved=reserved, placements=placements,
                no_window=tuple(no_window), unknown_windows=tuple(unknown),
                missing_needed=missing, needs_scanned=needs_scanned, reserve_missing_cores=on,
                unknown_load_regions=tuple(unknown_load), unknown_load_windows=unknown_load_windows,
                empty_load_regions=empty_loads, forward_after=forward,
                doubts=tuple(region_doubts(config, chip_regions)))


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
    for name, load in plan.unknown_load_regions:
        refusals.append(f"区域 {name} 所属的加载区域 {load} 不存在")
    for load, window in plan.unknown_load_windows:
        refusals.append(f"加载区域 {load} 所在的窗口 {window} 不在当前芯片的存储里")
    window_symbols = {w.symbol: w.name for w in plan.windows}
    for region in plan.regions:
        symbol = fixed_symbol(region.name)
        if region.address is not None and symbol in window_symbols:
            refusals.append(f"区域 {region.name} 的固定地址名 {symbol} 与窗口 {window_symbols[symbol]} 的地址名相同")
    for p in plan.by_status(NOT_PLACED):
        warnings.append(f"段 {p.section} 未放置：生成的文件里没有区域按名字接收它")
    if not plan.needs_scanned:
        warnings.append(DEFAULT_LAYOUT_WARNING)
    for name in plan.missing_needed:
        warnings.append(f"代码引用了区域 {name}，但配置里没有它，生成的文件里也不会有")
    warnings.extend(plan.doubts)
    for name in plan.empty_load_regions:
        warnings.append(f"加载区域 {name} 里没有执行区域，生成的文件里不写它")
    for name, previous in plan.forward_after:
        warnings.append(f"区域 {name} 接在 {previous} 之后，但 {previous} 属于后面的加载区域，"
                        f"链接器可能不接受这个向后引用")
    return refusals, warnings


def fixed_symbol(region: str) -> str:
    """The name a fixed start address goes by in a linker file (``CORE0_USER_STACK_ADDRESS``)."""
    return _NOT_IDENTIFIER.sub("_", region) + "_ADDRESS"
