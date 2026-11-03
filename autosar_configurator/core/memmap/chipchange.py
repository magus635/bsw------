"""
A chip change and the memory layout

When the project's chip changes, the windows the execution regions lie on may not exist on
the new chip, or exist with other attributes.  This module compares the configuration with the
old and the new chip's memory regions and says, per execution region:

* kept: the window is on the new chip with the same type, core and cache attribute;
* to be placed again: it is not, or one of those differs.  Such a region is **never moved to
  another window by itself** (silently picking the uncached window, say, would change the
  program's behaviour) and its placements are never removed;
* not placed: it had no window yet.

``compare`` changes nothing, so the chip change preview can show it before anything is applied;
``apply`` records the outcome on the configuration, again without removing anything.
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional

from ..hardware.memory_regions import MemoryRegionDef
from .config import MemoryMapConfig
from .rules import AGAIN_KEY

KEPT, AGAIN, UNPLACED = "kept", "again", "unplaced"


@dataclass(frozen=True)
class RegionChange:
    region: str
    window: str
    status: str
    reason: str = ""


@dataclass(frozen=True)
class LostPlacement:
    section: str
    region: str


@dataclass
class LayoutChange:
    regions: List[RegionChange] = field(default_factory=list)
    lost: List[LostPlacement] = field(default_factory=list)        # manual placements in regions to place again
    kept_manual: List[str] = field(default_factory=list)

    @property
    def again(self) -> List[str]:
        return [r.region for r in self.regions if r.status == AGAIN]

    def summary_lines(self) -> List[str]:
        kept = sum(1 for r in self.regions if r.status == KEPT)
        lines = [f"内存布局：保留 {kept} 个执行区域，待重新放置 {len(self.again)} 个"]
        lines += [f"  待重新放置：{r.region}（{r.reason}）" for r in self.regions if r.status == AGAIN]
        if self.lost:
            lines.append("  手动放置在这些区域里的段会显示为待重新放置，不会被删除："
                         + "、".join(p.section for p in self.lost))
        return lines


def _difference(old: MemoryRegionDef, new: Optional[MemoryRegionDef]) -> str:
    """Why a window does not carry over; empty when it does."""
    if new is None:
        return f"新芯片没有窗口 {old.name}"
    reasons = []
    if new.type != old.type:
        reasons.append(f"类型 {old.type} → {new.type}")
    if new.core != old.core:
        reasons.append(f"核心 {old.core_text()} → {new.core_text()}")
    if new.cacheable != old.cacheable:
        reasons.append(f"{'可缓存' if old.cacheable else '不可缓存'} → {'可缓存' if new.cacheable else '不可缓存'}")
    return "；".join(reasons)


def compare(config: MemoryMapConfig, old_regions: List[MemoryRegionDef],
            new_regions: List[MemoryRegionDef]) -> LayoutChange:
    """What a change from ``old_regions`` to ``new_regions`` does to the layout.  Nothing is changed."""
    old: Dict[str, MemoryRegionDef] = {r.name: r for r in old_regions}
    new: Dict[str, MemoryRegionDef] = {r.name: r for r in new_regions}
    change = LayoutChange()
    for region in sorted(config.regions, key=lambda r: r.name):
        if not region.window:
            change.regions.append(RegionChange(region.name, "", UNPLACED))
            continue
        before = old.get(region.window) or new.get(region.window)
        if before is None:
            reason = f"旧芯片也没有窗口 {region.window}"
        else:
            reason = _difference(before, new.get(region.window))
        change.regions.append(RegionChange(region.name, region.window, AGAIN if reason else KEPT, reason))
    again = set(change.again)
    for section, target in sorted(config.manual.items()):
        if target in again:
            change.lost.append(LostPlacement(section, target))
        else:
            change.kept_manual.append(section)
    return change


def apply(config: MemoryMapConfig, chip: str, change: LayoutChange) -> None:
    """Record ``change`` on ``config`` for the new ``chip``: the regions to be placed again are
    listed, nothing is removed and no region is moved."""
    config.chip = chip
    again = sorted(change.again)
    if again:
        config.options[AGAIN_KEY] = again
    else:
        config.options.pop(AGAIN_KEY, None)
