"""
Chip memory regions

The optional ``memory_regions`` section of a chip YAML: the chip's address map as
a list of regions, used by the memory map check to tell which core a linker
region belongs to and whether it is cached::

    memory_regions:
    - {name: CPU0BTCM, start: '0x30100000', size: '0x30000', type: ram, core: 0, cacheable: false}
    - {name: CPUXATCM, start: '0x0', size: '0x10000', type: ram, core: local, cacheable: false}
    - {name: GMU_NORMAL, start: '0x10000000', size: '0x40000', type: ram, cacheable: true}

``core`` is absent for memory shared by all cores, and ``local`` for an alias
through which each core sees its own memory.  Addresses are written as hex text.
"""
from dataclasses import dataclass
from typing import Any, List, Optional, Union

REGION_TYPES = ("flash", "ram")
LOCAL = "local"

Core = Union[int, str, None]      # core index, LOCAL, or None (shared)


@dataclass(frozen=True)
class MemoryRegionDef:
    name: str
    start: int
    size: int
    type: str = "ram"
    core: Core = None
    cacheable: bool = True

    @property
    def end(self) -> int:
        return self.start + self.size

    def contains(self, address: int) -> bool:
        return self.start <= address < self.end

    def core_text(self) -> str:
        if self.core is None:
            return "共享"
        return "核心本地" if self.core == LOCAL else f"核心 {self.core}"


def _number(value: Any, what: str) -> int:
    if isinstance(value, bool):
        raise ValueError(f"{what} must be a number")
    if isinstance(value, int):
        return value
    try:
        return int(str(value).strip(), 0)
    except ValueError:
        raise ValueError(f"{what} must be a number, not {value!r}") from None


def parse_memory_regions(data: Any) -> List[MemoryRegionDef]:
    """Validate the ``memory_regions`` section (absent -> empty list)."""
    if data is None:
        return []
    if not isinstance(data, list):
        raise ValueError("memory_regions must be a list")  # noqa: TRY004 - callers handle ValueError only
    regions = []
    for index, entry in enumerate(data):
        where = f"memory_regions[{index}]"
        if not isinstance(entry, dict) or not str(entry.get("name", "")).strip():
            raise ValueError(f"{where} must be a mapping with a name")
        name = str(entry["name"]).strip()
        where = f"memory_regions.{name}"
        region_type = str(entry.get("type", "ram")).strip().lower()
        if region_type not in REGION_TYPES:
            raise ValueError(f"{where}.type must be one of {', '.join(REGION_TYPES)}")
        core = entry.get("core")
        if core is not None:
            core = LOCAL if str(core).strip().lower() == LOCAL else _number(core, f"{where}.core")
        cacheable = entry.get("cacheable", True)
        if not isinstance(cacheable, bool):
            raise ValueError(f"{where}.cacheable must be true or false")
        size = _number(entry.get("size"), f"{where}.size")
        if size <= 0:
            raise ValueError(f"{where}.size must be positive")
        regions.append(MemoryRegionDef(name, _number(entry.get("start"), f"{where}.start"),
                                       size, region_type, core, cacheable))
    return regions


def memory_region_dict(region: MemoryRegionDef) -> dict:
    """One region as written to the YAML (inverse of parse_memory_regions)."""
    data = {"name": region.name, "start": hex(region.start), "size": hex(region.size),
            "type": region.type}
    if region.core is not None:
        data["core"] = region.core
    data["cacheable"] = region.cacheable
    return data


def region_at(regions: List[MemoryRegionDef], address: int) -> Optional[MemoryRegionDef]:
    """The region containing ``address`` (the smallest when regions overlap)."""
    found = [r for r in regions if r.contains(address)]
    return min(found, key=lambda r: r.size) if found else None
