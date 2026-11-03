"""
Importing a layout from an ADS scatter file (update-linker-generator-authority, design.md D5)

An existing ``.scat`` is an optional starting point for the configuration: its load
regions, its execution regions (window, start, alignment, size, kind) and the sections
its regions select by name.  Two steps, so that the user sees everything first:

``preview_import``
    reads the file and the configuration and says what would be added, what is skipped
    because the configuration already has it, and what cannot be imported and why; it
    never changes the configuration;
``apply_import``
    adds exactly what a preview lists, never overwrites, never touches the rules.

The file is read with ``scatter.parse_scatter`` (the checker's parser).  It keeps of each
region header only the name and base, so the rest of a header (``ALIGN``, ``EMPTY``, the
size) and the load region headers are read here by walking the same blocks again.

What comes out is a starting point, not a constraint: after the import the configuration
is edited as usual, and generating always follows the configuration.
"""
import re
from collections import Counter
from dataclasses import dataclass, field, replace
from typing import Dict, List, Optional, Sequence, Tuple

from autosar_configurator.core.hardware.memory_regions import MemoryRegionDef, region_at
from autosar_configurator.core.memmap.config import (
    AFTER,
    BSS,
    CODE,
    CONST,
    DATA,
    DEFAULT_LIMIT_ALIGN,
    FIXED,
    LIMIT_SUFFIX,
    NOINIT,
    OFFSET,
    RESERVED,
    STACK,
    ConfigError,
    ExecRegion,
    LoadRegion,
    MemoryMapConfig,
    check_region_name,
)
from autosar_configurator.core.memmap.scatter import (
    _SELECTOR,
    ScatterFile,
    _base_terms,
    _define_value,
    _split_header,
    _strip_comments,
    _term_value,
    parse_scatter,
)

IMPORTED = "imported"           # origin of a region that came from an imported file
DEFAULT_ALIGN = 64
DEFAULT_STACK_ALIGN = 8

# words of a region header after the base; those in _WITH_ARGUMENT take the next word
_KEYWORDS = {"ABSOLUTE", "PI", "RELOC", "OVERLAY", "FIXED", "NOCOMPRESS", "UNINIT", "ZEROPAD",
             "EMPTY", "ALIGN", "ALIGNALL", "PADVALUE", "FILL", "SORTTYPE", "PROTECTED"}
_WITH_ARGUMENT = {"ALIGNALL", "PADVALUE", "FILL", "SORTTYPE"}
_IDENT = re.compile(r"^[A-Za-z_]\w*$")

# kind inference (D5): what a selector word says about the kind of the region.
# Names are tested in this order, so ``_no_init`` wins over ``_bss`` and so on.
_ATTRIBUTE_KINDS = {"+RO-CODE": CODE, "+CODE": CODE, "+TEXT": CODE, "+XO": CODE,
                    "+RO-DATA": CONST, "+CONST": CONST,
                    "+ZI": BSS, "+BSS": BSS,
                    "+RW-DATA": DATA, "+DATA": DATA}
_NAME_KINDS = ((NOINIT, ("_no_init",)),
               (BSS, ("_bss", "_cleared")),
               (CONST, ("_const",)),
               (CODE, ("_text", "_code", "ramcode")),
               (DATA, ("_data",)))
_KIND_ORDER = (CODE, CONST, DATA, BSS, NOINIT)      # breaks ties of a guess
FALLBACK_KIND = DATA


@dataclass(frozen=True)
class NotImported:
    """Something of the file that the import leaves out, with the reason."""
    what: str
    reason: str
    line: int = 0

    def text(self) -> str:
        where = f"第 {self.line} 行：" if self.line else ""
        return f"{where}{self.what} —— {self.reason}"


@dataclass(frozen=True)
class SkippedPlacement:
    section: str
    region: str                 # where the file puts it
    existing: str               # where the configuration already places it


@dataclass
class ImportPreview:
    path: str
    load_regions: List[LoadRegion] = field(default_factory=list)          # to add, in file order
    skipped_load_regions: List[str] = field(default_factory=list)         # the configuration has the name
    regions: List[ExecRegion] = field(default_factory=list)               # to add, in file order
    skipped_regions: List[str] = field(default_factory=list)              # the configuration has the name
    placements: List[Tuple[str, str]] = field(default_factory=list)       # (section, region) to add
    skipped_placements: List[SkippedPlacement] = field(default_factory=list)
    not_imported: List[NotImported] = field(default_factory=list)
    unconfirmed: List[str] = field(default_factory=list)                  # regions whose kind is a guess
    notes: List[str] = field(default_factory=list)                        # imported, but only approximately

    @property
    def empty(self) -> bool:
        return not (self.load_regions or self.regions or self.placements)


# --- reading the parts of the file parse_scatter leaves out ----------------------------

@dataclass
class _Header:
    name: str
    base: str
    align: Optional[int] = None
    empty: bool = False
    size: Optional[int] = None
    negative: bool = False      # EMPTY -length: grows down from the base


@dataclass
class _Block:
    header: _Header
    line: int
    body: str = ""


def _number_or_define(scatter: ScatterFile, word: str) -> Optional[int]:
    try:
        return int(word, 0)
    except ValueError:
        pass
    if _IDENT.match(word):
        return _define_value(scatter.defines, word)
    return None


def _header(scatter: ScatterFile, text: str) -> _Header:
    name, base = _split_header(text)
    rest = text.strip()[len(name):].lstrip()[len(base):]
    header = _Header(name, base)
    words = rest.split()
    index = 0
    while index < len(words):
        word = words[index]
        upper = word.upper()
        following = words[index + 1] if index + 1 < len(words) else None
        if upper == "ALIGN" and following is not None:
            header.align = _number_or_define(scatter, following)
            index += 2
            continue
        if upper == "EMPTY":
            header.empty = True
        elif upper in _WITH_ARGUMENT:
            index += 2
            continue
        elif upper not in _KEYWORDS:
            value = _number_or_define(scatter, word)
            if value is not None:
                header.negative = value < 0
                header.size = abs(value)
        index += 1
    return header


def _blocks(scatter: ScatterFile, text: str) -> Tuple[List[_Block], List[_Block]]:
    """(load region blocks, execution region blocks) in file order, walked exactly as
    ``parse_scatter`` walks them, so the execution blocks pair with ``scatter.regions``."""
    body = "\n".join("" if line.lstrip().startswith("#") else line
                     for line in _strip_comments(text).split("\n"))
    loads: List[_Block] = []
    execs: List[_Block] = []
    depth, mark = 0, 0
    current: Optional[_Block] = None
    for index, char in enumerate(body):
        if char == "{":
            header = body[mark:index]
            line = body.count("\n", 0, mark + len(header) - len(header.lstrip())) + 1
            if depth == 0:
                loads.append(_Block(_header(scatter, header), line))
            elif depth == 1:
                current = _Block(_header(scatter, header), line)
                execs.append(current)
            depth += 1
            mark = index + 1
        elif char == "}":
            if depth == 2 and current is not None:
                current.body = body[mark:index]
                current = None
            depth = max(depth - 1, 0)
            mark = index + 1
    return loads, execs


def _expression_value(scatter: ScatterFile, expr: str) -> Optional[int]:
    terms = _base_terms(expr)
    if not terms or not terms[0]:
        return None
    base = _term_value(scatter, terms[0])
    if base is None:
        return None
    return base + sum(v for v in (_term_value(scatter, t) for t in terms[1:]) if v is not None)


def _leading_term(scatter: ScatterFile, expr: str) -> Tuple[Optional[str], Optional[int]]:
    """The first term of a base expression and its value: ``GMU_NORMAL_ADDRESS+0x20000``
    gives the define; ``ImageLimit(X)`` and ``+0`` give nothing."""
    terms = _base_terms(expr)
    if not terms or not terms[0]:
        return None, None
    return terms[0], _term_value(scatter, terms[0])


# --- kind ---------------------------------------------------------------------------------

def _word_kind(word: str) -> Optional[str]:
    if word.startswith("+"):
        return _ATTRIBUTE_KINDS.get(word.upper())
    lower = word.lower()
    for kind, parts in _NAME_KINDS:
        if any(p in lower for p in parts):
            return kind
    return None


def infer_kind(selectors) -> Tuple[str, bool]:
    """(kind, sure) of a region with these selectors: each attribute and section name that
    says a kind votes for it; more than half of the votes is sure.  Otherwise the most voted
    kind (or data, when nothing votes) and not sure."""
    votes = Counter(k for s in selectors for w in s.attributes + s.names
                    for k in (_word_kind(w),) if k is not None)
    if not votes:
        return FALLBACK_KIND, False
    best = max(_KIND_ORDER, key=lambda k: (votes[k], -_KIND_ORDER.index(k)))
    return best, votes[best] * 2 > sum(votes.values())


# --- preview -------------------------------------------------------------------------------

def preview_import(config: MemoryMapConfig, text: str, path: str,
                   chip_regions: Sequence[MemoryRegionDef]) -> ImportPreview:
    """What importing scatter file ``text`` into ``config`` would do.  Changes nothing."""
    chip = list(chip_regions)
    scatter = parse_scatter(text, path)
    load_blocks, exec_blocks = _blocks(scatter, text)
    preview = ImportPreview(path)
    if len(exec_blocks) != len(scatter.regions):        # cannot happen: same walk
        raise ValueError("scatter file blocks do not match the parsed regions")

    # load regions: the ones a region may refer to, i.e. imported or already configured
    usable_loads = set()
    for block in load_blocks:
        name = block.header.name
        if config.load_region(name) is not None:
            preview.skipped_load_regions.append(name)
            usable_loads.add(name)
            continue
        if not _IDENT.match(name):
            preview.not_imported.append(NotImported(f"加载区域 {name}", "名称不是合法的标识符", block.line))
            continue
        base = _expression_value(scatter, block.header.base)
        window = region_at(chip, base) if base is not None else None
        if window is None:
            reason = (f"基址 {block.header.base} 无法解析" if base is None
                      else f"基址 {base:#x} 不在芯片的任何存储窗口上")
            preview.not_imported.append(NotImported(f"加载区域 {name}", reason, block.line))
            continue
        size = block.header.size
        if not size:
            size = window.end - base
            preview.notes.append(f"加载区域 {name} 没有写大小，取到窗口 {window.name} 末尾：{size:#x}")
        preview.load_regions.append(LoadRegion(name, window.name, size))
        usable_loads.add(name)

    # per window: what is there already, in order, then what the import adds
    in_window: Dict[str, List[str]] = {}
    next_order: Dict[str, int] = {}
    for region in sorted(config.regions, key=lambda r: (r.order, r.name)):
        in_window.setdefault(region.window, []).append(region.name)
        next_order[region.window] = max(next_order.get(region.window, 0), region.order)

    window_of: Dict[str, str] = {r.name: r.window for r in config.regions}   # name -> window
    taken = dict(config.manual)          # section -> region: by hand, or earlier in the file
    seen_names = set()
    for region, block in zip(scatter.regions, exec_blocks):
        header = block.header
        what = f"区域 {region.name}"
        if region.name.endswith(LIMIT_SUFFIX):
            preview.not_imported.append(NotImported(what, "界限区域由生成器自己产出，不导入", region.line))
            continue
        if region.name in config.trimmed:
            preview.not_imported.append(NotImported(
                what, "为芯片缺少的核保留的区域，由生成器按保留选项自己产出，不导入", region.line))
            _selectors_dropped(region, preview)
            continue
        try:
            check_region_name(region.name)
        except ConfigError as error:
            preview.not_imported.append(NotImported(what, str(error), region.line))
            _selectors_dropped(region, preview)
            continue
        if region.name in seen_names:
            preview.not_imported.append(NotImported(what, "文件里同名区域出现了不止一次，只取第一个", region.line))
            _selectors_dropped(region, preview)
            continue
        seen_names.add(region.name)

        existing = config.region(region.name) is not None
        if existing:
            preview.skipped_regions.append(region.name)
        else:
            converted = _convert(scatter, region, header, chip, in_window, next_order, window_of,
                                 usable_loads, preview)
            if converted is None:
                _selectors_dropped(region, preview)
                continue
            preview.regions.append(converted)

        _placements(region, block, taken, preview)
    return preview


def _selectors_dropped(region, preview: ImportPreview) -> None:
    for selector in region.selectors:
        preview.not_imported.append(NotImported(
            f"{region.name} 的选择器 {selector.text()}", "所在区域没有导入", selector.line))


def _convert(scatter, region, header: _Header, chip, in_window, next_order, window_of, usable_loads,
             preview: ImportPreview) -> Optional[ExecRegion]:
    what = f"区域 {region.name}"
    lead, lead_value = _leading_term(scatter, region.base)

    # the window
    windows = {w.name: w for w in chip}
    if region.follows is not None and lead_value is not None:
        # "<BASE>+AlignExpr(ImageLimit(X), n)": it lies where <BASE> is, whatever X is
        window = region_at(chip, lead_value)
        address = lead_value
    elif region.follows is not None:
        # the window of the region it follows, as imported (or configured); parse_scatter's
        # resolved address would follow the chain to its first absolute base instead
        window = windows.get(window_of.get(region.follows, ""))
        address = None
        if window is None and region.follows not in window_of:
            window = region_at(chip, region.address) if region.address is not None else None
            address = region.address
    else:
        address = region.address
        window = region_at(chip, address) if address is not None else None
    if window is None:
        if region.follows is not None and address is None:
            reason = f"接在 {region.follows} 之后，而 {region.follows} 没有导入，定不出窗口"
        elif address is None:
            reason = f"起点 {region.base} 无法解析成地址"
        else:
            reason = f"地址 {address:#x} 不在芯片的任何存储窗口上"
        preview.not_imported.append(NotImported(what, reason, region.line))
        return None

    members = in_window.setdefault(window.name, [])
    previous = members[-1] if members else None

    # the start
    offset, address = 0, None
    if region.follows is not None:
        mode = AFTER
        if region.follows != previous:
            preview.notes.append(
                f"区域 {region.name} 在文件里接在 {region.follows} 之后，导入后接在窗口 {window.name} 里"
                f"{'的上一个区域 ' + previous if previous else '的起点'}之后")
    elif (lead is not None and _IDENT.match(lead) and lead_value == window.start
          and region.address is not None):
        offset = region.address - window.start
        mode = AFTER if offset == 0 and previous is None else OFFSET
    else:
        mode, address = FIXED, region.address

    # kind, alignment, size
    if header.empty and not header.size:
        kind, sure = RESERVED, True
        if "STACK" in region.name.upper():
            preview.notes.append(f"区域 {region.name} 是长度为 0 的空区域，导入为保留区域而不是栈"
                                 "（栈没有大小时生成器会取缺省栈大小）")
    elif header.empty:
        kind, sure = (STACK if "STACK" in region.name.upper() else RESERVED), True
        if header.negative:
            preview.notes.append(f"区域 {region.name} 是向下增长的空区域（EMPTY -{header.size:#x}），"
                                 "导入后按向上增长、同样大小处理")
    else:
        kind, sure = infer_kind(region.selectors)
    if not sure:
        preview.unconfirmed.append(region.name)
    align = header.align
    if not align or align <= 0:
        align = DEFAULT_STACK_ALIGN if kind == STACK else DEFAULT_ALIGN

    order = next_order.get(window.name, 0) + 1
    next_order[window.name] = order
    members.append(region.name)
    window_of[region.name] = window.name
    return ExecRegion(
        name=region.name, memory=window.memory_name, window=window.name, kind=kind, order=order,
        align=align, required=False, origin=IMPORTED, start_mode=mode, offset=offset, address=address,
        size=header.size or None, load_region=region.load_region if region.load_region in usable_loads else "",
        limit_align=DEFAULT_LIMIT_ALIGN)


def _placements(region, block: _Block, taken: Dict[str, str], preview: ImportPreview) -> None:
    raws = [m.group(2) for m in _SELECTOR.finditer(block.body)]
    for index, selector in enumerate(region.selectors):
        raw = raws[index] if index < len(raws) else ""
        label = f"{region.name} 的选择器 {selector.files}({raw.strip()})"
        if selector.is_any:
            preview.not_imported.append(NotImported(label, ".ANY 选择器按剩余空间分配，不导入为放置", selector.line))
            continue
        if not selector.all_files:
            preview.not_imported.append(NotImported(
                label, f"按文件选择（{selector.files}），放置只按段名，不导入", selector.line))
            continue
        ordering = [w for w in re.split(r"[,\s]+", raw) if w.upper() in ("+FIRST", "+LAST")]
        if ordering:
            preview.not_imported.append(NotImported(
                label, f"{ordering[0]} 要求段排在区域首尾，放置表达不了，不导入", selector.line))
            continue
        if not selector.names:
            preview.not_imported.append(NotImported(label, "通配选择器（只按属性取段），不导入为放置", selector.line))
            continue
        for name in selector.names:
            if "*" in name or "?" in name:
                preview.not_imported.append(NotImported(
                    f"{region.name} 的段名模式 {name}", "是模式不是段名，不导入为放置", selector.line))
                continue
            if name in taken:
                preview.skipped_placements.append(SkippedPlacement(name, region.name, taken[name]))
                continue
            taken[name] = region.name
            preview.placements.append((name, region.name))


# --- apply ---------------------------------------------------------------------------------

def apply_import(config: MemoryMapConfig, preview: ImportPreview) -> List[str]:
    """Add what ``preview`` lists to ``config``.  Nothing that the configuration has by then
    is overwritten; such items are skipped and returned as messages (empty normally).
    The rules are not touched."""
    skipped: List[str] = []
    for load in preview.load_regions:
        if config.load_region(load.name) is not None:
            skipped.append(f"加载区域 {load.name} 已存在，未覆盖")
            continue
        config.add_load_region(replace(load))
    added = []
    for region in preview.regions:
        if config.region(region.name) is not None:
            skipped.append(f"区域 {region.name} 已存在，未覆盖")
            continue
        copy = replace(region)
        if copy.load_region and config.load_region(copy.load_region) is None:
            copy.load_region = ""
        config.add_region(copy)
        added.append(region.name)
    # a guessed kind stays marked in the configuration until the user sets the kind
    config.mark_kind_unconfirmed(n for n in preview.unconfirmed if n in added)
    for section, region in preview.placements:
        if section in config.manual:
            skipped.append(f"段 {section} 已手动放在 {config.manual[section]}，未覆盖")
            continue
        config.manual[section] = region
    return skipped
