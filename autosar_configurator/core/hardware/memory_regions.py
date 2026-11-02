"""
Chip memory regions

The optional ``memory_regions`` section of a chip YAML: the chip's address map as
a list of regions, used by the memory map check to tell which core a linker
region belongs to and whether it is cached::

    memory_regions:
    - {name: CPU0BTCM, start: '0x30100000', size: '0x30000', type: ram, core: 0, cacheable: false}
    - {name: CPUXATCM, start: '0x0', size: '0x10000', type: ram, core: local, cacheable: false}
    - {name: GMU_NORMAL, start: '0x10000000', size: '0x40000', type: ram, cacheable: true,
       memory: GMU, window: normal}

``core`` is absent for memory shared by all cores, and ``local`` for an alias
through which each core sees its own memory.  Addresses are written as hex text.

One physical memory can be reached through several address windows (the same
flash cached, uncached and core-local).  The optional ``memory`` field names the
physical memory an entry is a window of; entries with the same ``memory`` are
windows of one memory, and an entry without it is a memory of its own.  ``window``
is a label for the window's use and ``source`` says where the entry's data comes
from.  All three are optional and are written only when set, so entries without
them keep their old form and their checksum.
"""
from dataclasses import dataclass, field, replace
from typing import Any, Dict, List, Optional, Set, Tuple, Union

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
    memory: Optional[str] = None        # the physical memory this is a window of
    window: Optional[str] = None        # label of the window's use: local, normal, device, ...
    source: Optional[str] = None        # where the data comes from

    @property
    def end(self) -> int:
        return self.start + self.size

    @property
    def memory_name(self) -> str:
        """The physical memory: ``memory``, or the entry's own name when it has none."""
        return self.memory or self.name

    def contains(self, address: int) -> bool:
        return self.start <= address < self.end

    def core_text(self) -> str:
        if self.core is None:
            return "共享"
        return "核心本地" if self.core == LOCAL else f"核心 {self.core}"


@dataclass
class MemoryGroup:
    """The windows of one physical memory, in file order."""
    name: str
    windows: List[MemoryRegionDef] = field(default_factory=list)

    @property
    def start(self) -> int:
        return min(w.start for w in self.windows)

    @property
    def sizes(self) -> Set[int]:
        return {w.size for w in self.windows}


def _number(value: Any, what: str) -> int:
    if isinstance(value, bool):
        raise ValueError(f"{what} must be a number")  # noqa: TRY004 - callers handle ValueError only
    if isinstance(value, int):
        return value
    try:
        return int(str(value).strip(), 0)
    except ValueError:
        raise ValueError(f"{what} must be a number, not {value!r}") from None


def _optional_text(entry: dict, key: str, where: str) -> Optional[str]:
    value = entry.get(key)
    if value is None:
        return None
    if not isinstance(value, str):
        raise ValueError(f"{where}.{key} must be text")  # noqa: TRY004 - callers handle ValueError only
    return value.strip() or None


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
            raise ValueError(f"{where}.cacheable must be true or false")  # noqa: TRY004 - callers handle ValueError only
        size = _number(entry.get("size"), f"{where}.size")
        if size <= 0:
            raise ValueError(f"{where}.size must be positive")
        regions.append(MemoryRegionDef(
            name, _number(entry.get("start"), f"{where}.start"), size, region_type, core, cacheable,
            _optional_text(entry, "memory", where), _optional_text(entry, "window", where),
            _optional_text(entry, "source", where)))
    return regions


def memory_region_dict(region: MemoryRegionDef) -> dict:
    """One region as written to the YAML (inverse of parse_memory_regions).

    The optional fields are written only when set, and ``memory`` not when it equals the
    entry's name, so an entry without grouping is written exactly as before.
    """
    data = {"name": region.name, "start": hex(region.start), "size": hex(region.size),
            "type": region.type}
    if region.core is not None:
        data["core"] = region.core
    data["cacheable"] = region.cacheable
    if region.memory and region.memory != region.name:
        data["memory"] = region.memory
    if region.window:
        data["window"] = region.window
    if region.source:
        data["source"] = region.source
    return data


def region_at(regions: List[MemoryRegionDef], address: int) -> Optional[MemoryRegionDef]:
    """The region containing ``address`` (the smallest when regions overlap)."""
    found = [r for r in regions if r.contains(address)]
    return min(found, key=lambda r: r.size) if found else None


# --- physical memories ----------------------------------------------------------------

def group_memories(regions: List[MemoryRegionDef]) -> List[MemoryGroup]:
    """The physical memories with their windows, each placed where its first window is."""
    groups: Dict[str, MemoryGroup] = {}
    for region in regions:
        groups.setdefault(region.memory_name, MemoryGroup(region.memory_name)).windows.append(region)
    return list(groups.values())


def rename_memory(regions: List[MemoryRegionDef], old: str, new: str) -> List[MemoryRegionDef]:
    """``regions`` with the memory ``old`` named ``new`` in every window of it.

    Raises:
        ValueError: ``new`` is empty or already names another memory
    """
    new = new.strip()
    if not new:
        raise ValueError("memory name must not be empty")
    if new != old and any(r.memory_name == new for r in regions):
        raise ValueError(f"memory {new} already exists")
    return [replace(r, memory=new) if r.memory_name == old else r for r in regions]


# --- checks ---------------------------------------------------------------------------

def region_problems(regions: List[MemoryRegionDef]) -> Tuple[List[str], List[str]]:
    """``(errors, doubts)`` of a list of regions.

    Errors make the data unusable and stop the save: a repeated name (numbers and types
    are already checked when the entries are read).  Doubts only make it questionable and
    are listed: windows of one memory of different sizes or types, and overlapping windows
    (the entries of a vendor table are partly unconfirmed, so a doubt must never keep the
    user from entering what they are not sure of).
    """
    errors: List[str] = []
    seen: Set[str] = set()
    for r in regions:
        if r.name in seen and f"名称重复：{r.name}" not in errors:
            errors.append(f"名称重复：{r.name}")
        seen.add(r.name)

    doubts: List[str] = []
    for group in group_memories(regions):
        if len(group.windows) < 2:
            continue
        if len(group.sizes) > 1:
            sizes = "，".join(f"{w.name} {w.size:#x}" for w in group.windows)
            doubts.append(f"存储 {group.name} 的窗口大小不一致：{sizes}")
        if len({w.type for w in group.windows}) > 1:
            types = "，".join(f"{w.name} {w.type}" for w in group.windows)
            doubts.append(f"存储 {group.name} 的窗口类型不一致：{types}")
    for index, a in enumerate(regions):
        for b in regions[index + 1:]:
            if a.start < b.end and b.start < a.end:
                same = a.memory_name == b.memory_name
                doubts.append(f"窗口重叠：{a.name} 与 {b.name}（"
                              + ("同一存储，别名不应相互重叠" if same else "不同存储") + "）")
    return errors, doubts
