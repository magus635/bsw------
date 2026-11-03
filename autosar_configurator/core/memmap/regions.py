"""
Required execution regions

The regions that code refers to by name (the link symbol needs the scan read from
``startup.c``, the Os code and so on) have to exist in the linker file, so they are
*required* in the configuration: the user chooses where they lie and what they take, but
cannot remove or rename them.

Two things shape the list:

* a region named after a core the chip does not have (``PRIVATE_DATA_CORE2`` on a two-core
  chip) is **trimmed**: it is not offered in the configuration, and its name is kept so that
  the generator can still provide an empty one for startup code that refers to it;
* with no needs at all (the directory with ``startup.c`` was not added) the chip's default
  layout stands in, and the result says it was not checked against code.

The ``<name>_LIMIT`` regions are never part of this: the generator makes them.
"""
import re
from dataclasses import dataclass, field
from typing import Dict, Iterable, List, Optional

from .config import (
    BSS,
    CODE,
    DATA,
    LIMIT_SUFFIX,
    REQUIRED_ORIGIN,
    RESERVED,
    STACK,
    ExecRegion,
    MemoryMapConfig,
)
from .symbols import CLEAR, COPY, STACK as USE_STACK, RegionNeed

FROM_CODE = "code"
FROM_DEFAULT = "default"
NO_LONGER_NEEDED = "no-longer-needed"

_CORE = re.compile(r"(?:^|_)CORE(\d+)(?:_|$)", re.I)
_STACK_NAME = re.compile(r"(?:^|_)STACK(?:_|$)", re.I)
_CODE_NAME = re.compile(r"(?:^|_)CODE(?:_|$)|VECTOR", re.I)


@dataclass
class RequiredRegions:
    regions: List[ExecRegion] = field(default_factory=list)
    trimmed: List[str] = field(default_factory=list)
    source: str = FROM_CODE

    def source_note(self) -> str:
        if self.source == FROM_DEFAULT:
            return "必需区域来自芯片的默认布局，未经代码核对（没有扫描到引用链接符号的代码）"
        return "必需区域来自扫描到的代码引用"

    def clashed(self, config: MemoryMapConfig) -> List[str]:
        """Required names that the configuration already has as a user's own region."""
        return sorted(r.name for r in self.regions
                      if (own := config.region(r.name)) is not None and not own.required)


def core_of(name: str) -> Optional[int]:
    m = _CORE.search(name)
    return int(m.group(1)) if m else None


def kind_for(need: RegionNeed) -> str:
    """The kind of region a need implies: from the use, and from the name where the use does
    not say (the vendor startup asks for a stack region's base or cleared limit, which looks
    like a copy or a clear region)."""
    if USE_STACK in need.uses or _STACK_NAME.search(need.region):
        return STACK
    if COPY in need.uses:
        return CODE if _CODE_NAME.search(need.region) else DATA
    if CLEAR in need.uses:
        return BSS
    return CODE if _CODE_NAME.search(need.region) else RESERVED


def _region(name: str, kind: str, layout: Dict[str, dict]) -> ExecRegion:
    """A required region placed as the factory layout says (window, order, start, size, load
    region), or with no window yet when the layout does not know it."""
    entry = layout.get(name)
    if entry is None:
        return ExecRegion(name, "", "", kind, 0, 8 if kind == STACK else 64,
                          required=True, origin=REQUIRED_ORIGIN)
    from .factory import layout_region          # the factory module imports this one
    return layout_region({**entry, "kind": entry.get("kind", kind)})


def required_regions(needs: Iterable[RegionNeed], cores: Optional[int],
                     default_layout: Optional[List[dict]] = None) -> RequiredRegions:
    """The required regions for ``needs`` on a chip with ``cores`` cores (None: unknown, so
    nothing is trimmed), placed on the windows ``default_layout`` gives them where it knows them.
    """
    layout = {e["name"]: e for e in (default_layout or [])}
    result = RequiredRegions()
    named: Dict[str, str] = {}
    for need in sorted(needs, key=lambda n: n.region):
        if need.region.endswith(LIMIT_SUFFIX):
            continue
        named[need.region] = kind_for(need)
    if not named and layout:
        result.source = FROM_DEFAULT
        named = {name: entry.get("kind", DATA) for name, entry in layout.items()}
    for name in sorted(named):
        core = core_of(name)
        if cores is not None and core is not None and core >= cores:
            result.trimmed.append(name)
            continue
        result.regions.append(_region(name, named[name], layout))
    return result


def merge_required(config: MemoryMapConfig, result: RequiredRegions) -> List[str]:
    """Bring ``config``'s required regions up to date with ``result``.

    A region that is already there keeps what the user chose (window, order); a new one is
    added; one no longer asked for is kept and marked, never deleted; a user's own region is
    never touched.  The trimmed names replace the configuration's list.

    Returns:
        the names of required regions that are no longer needed
    """
    wanted = {r.name for r in result.regions}
    for region in result.regions:
        have = config.region(region.name)
        if have is None:
            config.regions.append(region)
        elif have.required:
            if have.origin == NO_LONGER_NEEDED:
                have.origin = REQUIRED_ORIGIN
    gone = []
    for region in config.regions:
        if region.required and region.name not in wanted:
            region.origin = NO_LONGER_NEEDED
            gone.append(region.name)
    config.trimmed = sorted(result.trimmed)
    return sorted(gone)
