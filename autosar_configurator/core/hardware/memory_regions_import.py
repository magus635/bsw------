"""
Memory regions from the comment table of an ADS scatter file

The head of a vendor scatter file lists the chip's memory in a comment table::

    ;        CPU0BTCM    0x30100000    0x30100000 - 0x30130000 (192K)    AXI access CPU0BTCM address
    ;        GMU_DEVICE  0x82000000    0x82000000 - 0x82040000 (256K)    ... (Non-Cacheable)
    ;        CPUXATCM    0x00000000    0x00000000 + 64K                  local access CPUXATCM address

(the first form is the vendor's LinkerAdsPf.scat, the second the Os template's scatter.scat).
This module reads such a table into memory regions.  It takes the start and the size from
the numbers, the type, the core and the cache attribute from the name and the trailing text
**only where they say so**; what they do not say is left at the loader's default and
reported, never guessed, so that the entry can be marked to be confirmed.
"""
import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional, Tuple

from .memory_regions import LOCAL, MemoryRegionDef

_SIZE = re.compile(r"^(0[xX][0-9A-Fa-f]+|\d+)\s*([KMG]?)B?$", re.I)
_UNITS = {"": 1, "K": 1 << 10, "M": 1 << 20, "G": 1 << 30}
_NUMBER = r"0[xX][0-9A-Fa-f]+"
# ;  NAME  start  end - length (size)  text      or      ;  NAME  start  start + size  text
_LINE = re.compile(
    r"^;\s+(?P<name>[A-Za-z_]\w*)\s+(?P<start>" + _NUMBER + r")\s+"
    r"(?:(?P<end_from>" + _NUMBER + r")\s*-\s*(?P<end>" + _NUMBER + r")(?:\s*\((?P<bracket>[^)]*)\))?"
    r"|(?P<plus_from>" + _NUMBER + r")\s*\+\s*(?P<plus>\S+))"
    r"(?P<text>.*)$")
_NON_CACHEABLE = re.compile(r"non[-\s]?cacheable|uncached|device", re.I)
_CACHEABLE = re.compile(r"cacheable", re.I)
_CORE_IN_NAME = re.compile(r"^CPU(\d+)", re.I)
_LOCAL_TEXT = re.compile(r"local\s+access", re.I)


@dataclass
class ImportResult:
    """The regions read from a file, and what the text left unsaid."""
    regions: List[MemoryRegionDef] = field(default_factory=list)
    source: str = ""
    unstated_cache: List[str] = field(default_factory=list)      # no word about the cache attribute
    unstated_type: List[str] = field(default_factory=list)       # neither the name nor the text says flash or ram

    def unconfirmed_note(self) -> str:
        """The note to put on the chip's ``unconfirmed.memory_regions`` mark."""
        note = f"按 {self.source} 填写"
        if self.unstated_cache:
            note += f"；缓存属性原文未说明，待确认：{'、'.join(self.unstated_cache)}"
        if self.unstated_type:
            note += f"；flash 或 ram 原文未说明，待确认：{'、'.join(self.unstated_type)}"
        return note


@dataclass
class MergeReport:
    added: List[str] = field(default_factory=list)
    skipped: List[str] = field(default_factory=list)       # names the chip already has, or repeated in the file


def parse_size(text: str) -> Optional[int]:
    """``64K``, ``16KB``, ``3MB``, ``0x1000``, ``4096`` as a byte count; None when it is not a size."""
    m = _SIZE.match((text or "").strip())
    if not m:
        return None
    number, unit = int(m.group(1), 0), m.group(2).upper()
    return number * _UNITS[unit] if number > 0 else None


def _kind_from(name: str, text: str) -> Tuple[Optional[str], bool]:
    """``(type or None when not stated, whether it was stated)``."""
    if re.search(r"FLASH", name, re.I) or re.search(r"\b(PF\d|DF)\b|flash", text, re.I):
        return "flash", True
    if re.search(r"TCM|GMU|LMU|RAM", name, re.I):
        return "ram", True
    return None, False


def _core_from(name: str, text: str):
    m = _CORE_IN_NAME.match(name)
    if m:
        return int(m.group(1))
    if re.match(r"^CPUX", name, re.I) or _LOCAL_TEXT.search(text):
        return LOCAL
    return None


def parse_comment_table(text: str, path: str) -> ImportResult:
    """The memory regions listed in the comment table of ``text`` (an ADS scatter file).

    Only comment lines of the table's two forms are read; everything else, preprocessor
    lines and code included, is left alone.
    """
    source = f"{Path(path).name} 注释表"
    result = ImportResult(source=source)
    for line in text.splitlines():
        m = _LINE.match(line)
        if not m:
            continue
        start = int(m.group("start"), 0)
        if m.group("end"):
            size = int(m.group("end"), 0) - int(m.group("end_from"), 0)
        else:
            size = parse_size(m.group("plus"))
        if not size or size <= 0:
            continue
        name, trailing = m.group("name"), m.group("text") or ""
        kind, stated = _kind_from(name, trailing)
        cacheable_word = _NON_CACHEABLE.search(trailing) or _CACHEABLE.search(trailing)
        if not cacheable_word:
            result.unstated_cache.append(name)
        if not stated:
            result.unstated_type.append(name)
        # "Non-Cacheable" contains "Cacheable": test the negative first
        cacheable = not _NON_CACHEABLE.search(trailing) if cacheable_word else True
        result.regions.append(MemoryRegionDef(
            name, start, size, kind or "ram", _core_from(name, trailing), cacheable, source=source))
    return result


def merge_import(existing: List[MemoryRegionDef],
                 imported: ImportResult) -> Tuple[List[MemoryRegionDef], MergeReport]:
    """``existing`` plus the imported entries it does not have yet, and what was added or skipped.

    An entry whose name the chip already has is never overwritten; the same name repeated
    inside the file is added once (its first line).  Neither input is changed.
    """
    report = MergeReport()
    merged = list(existing)
    names = {r.name for r in existing}
    for region in imported.regions:
        if region.name in names:
            if region.name not in report.skipped:
                report.skipped.append(region.name)
            continue
        names.add(region.name)
        merged.append(region)
        report.added.append(region.name)
    return merged, report
