"""
ADS (armlink) scatter files

Reads what the memory map check needs from a ``.scat`` file: the ``#define``
values, the execution regions with their base address, and the input section
selectors of each region.  The base address is resolved to a number where
possible: a ``#define`` name or number, or the region it follows
(``AlignExpr(ImageLimit(X), n)``, ``ImageLimit(X)``, ``+offset``).  Only the first
term of an expression counts, which is enough to tell which memory a region
lies in.  Preprocessor conditions (``#if``) are not evaluated.
"""
import fnmatch
import re
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Tuple

_DEFINE = re.compile(r"^\s*#\s*define\s+(\w+)\s+(.+?)\s*$")
_NUMBER = re.compile(r"^(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*$")
_TERM = re.compile(r"0[xX][0-9A-Fa-f]+|\d+|[A-Za-z_]\w*")
_FOLLOWS = re.compile(r"\bImage(?:Limit|Base)\s*\(\s*(\w+)\s*\)")
_SELECTOR = re.compile(r"([^\s(){}]+)\s*\(([^()]*)\)")
_FUNCTIONS = {"AlignExpr", "ImageLimit", "ImageBase", "ImageLength", "LoadLimit", "LoadBase"}

ALL_FILES = {"*", "*.o", "*.obj", "*.*"}

# input section attributes that take sections of each kind (D5)
KIND_ATTRIBUTES = {
    "TEXT": ("+RO-CODE", "+RO", "+CODE", "+TEXT", "+XO"),
    "RODATA": ("+RO-DATA", "+RO", "+CONST"),
    "DATA": ("+RW-DATA", "+RW", "+DATA"),
    "BSS": ("+BSS", "+ZI"),
}


@dataclass(frozen=True)
class Selector:
    files: str                  # file pattern, or .ANY
    names: Tuple[str, ...]      # section name patterns (.name, may hold * and ?)
    attributes: Tuple[str, ...]  # +RO-CODE, +BSS, ... (upper case)
    line: int

    @property
    def is_any(self) -> bool:
        return self.files.upper() == ".ANY"

    @property
    def all_files(self) -> bool:
        return self.is_any or self.files in ALL_FILES

    def text(self) -> str:
        return f"{self.files}({', '.join(self.names + self.attributes)})"


@dataclass
class ExecRegion:
    name: str
    base: str                   # the base address expression as written
    line: int
    load_region: str
    selectors: List[Selector] = field(default_factory=list)
    address: Optional[int] = None       # resolved base, None when unknown
    follows: Optional[str] = None       # region whose limit or base it is placed at


@dataclass
class ScatterFile:
    path: str
    defines: Dict[str, str] = field(default_factory=dict)
    regions: List[ExecRegion] = field(default_factory=list)

    def region(self, name: str) -> Optional[ExecRegion]:
        return next((r for r in self.regions if r.name == name), None)


def _strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", lambda m: "\n" * m.group(0).count("\n"), text, flags=re.S)
    lines = []
    for line in text.split("\n"):
        if line.lstrip().startswith("#"):
            lines.append(line)      # #define / #! / #if: kept for the define table
            continue
        line = re.sub(r"//.*$", "", line)
        lines.append(line.split(";", 1)[0])
    return "\n".join(lines)


def _split_header(header: str) -> Tuple[str, str]:
    """(name, base expression) of a region header ``NAME base [attributes] [size]``.

    The expression ends at the first space outside parentheses, unless a ``+`` sits
    next to that space: ``RAM + OFFSET`` and ``RAM +0x10`` are one expression.
    """
    header = header.strip()
    m = re.match(r"(\S+)\s+", header)
    if not m:
        return header, ""
    rest = header[m.end():]
    depth = 0
    for index, char in enumerate(rest):
        if char == "(":
            depth += 1
        elif char == ")":
            depth -= 1
        elif char.isspace() and depth == 0:
            before = rest[:index].rstrip()
            after = rest[index:].lstrip()
            if before.endswith("+") or after.startswith("+"):
                continue
            return m.group(1), rest[:index]
    return m.group(1), rest


def _selectors(body: str, first_line: int) -> List[Selector]:
    found = []
    for m in _SELECTOR.finditer(body):
        names, attributes = [], []
        for item in re.split(r"[,\s]+", m.group(2)):
            if item.startswith("+"):
                if item.upper() not in ("+FIRST", "+LAST"):
                    attributes.append(item.upper())
            elif item.startswith(".") or "*" in item or "?" in item:
                names.append(item)
        line = first_line + body.count("\n", 0, m.start())
        found.append(Selector(m.group(1), tuple(names), tuple(attributes), line))
    return found


def parse_scatter(text: str, path: str) -> ScatterFile:
    result = ScatterFile(path)
    for line in text.split("\n"):
        m = _DEFINE.match(line)
        if m:
            result.defines[m.group(1)] = m.group(2)
    body = "\n".join("" if line.lstrip().startswith("#") else line
                     for line in _strip_comments(text).split("\n"))

    depth, mark, load_region = 0, 0, ""
    region: Optional[ExecRegion] = None
    for index, char in enumerate(body):
        if char == "{":
            header = body[mark:index]
            line = body.count("\n", 0, mark + len(header) - len(header.lstrip())) + 1
            name, base = _split_header(header)
            if depth == 0:
                load_region = name
            elif depth == 1:
                region = ExecRegion(name, base, line, load_region)
                result.regions.append(region)
            depth += 1
            mark = index + 1
        elif char == "}":
            if depth == 2 and region is not None:
                region.selectors = _selectors(body[mark:index], body.count("\n", 0, mark) + 1)
                region = None
            depth = max(depth - 1, 0)
            mark = index + 1
    _resolve_addresses(result)
    return result


def _define_value(defines: Dict[str, str], name: str, seen=()) -> Optional[int]:
    value = defines.get(name)
    if value is None or name in seen:
        return None
    term = _TERM.search(value)
    if term is None:
        return None
    if _NUMBER.match(term.group(0)):
        return int(term.group(0), 0)
    return _define_value(defines, term.group(0), seen + (name,))


def _term_value(scatter: ScatterFile, term: str) -> Optional[int]:
    return int(term, 0) if _NUMBER.match(term) else _define_value(scatter.defines, term)


def _base_terms(expr: str) -> Optional[List[str]]:
    """The terms of ``A + B + ...`` once the wrapping function calls are peeled off:
    ``AlignExpr(RAM + ImageLength(X), 64)`` gives ``[RAM]`` plus nothing the check can
    use; ``RAM+0x1000`` gives ``[RAM, 0x1000]``.  Region-relative parts (``ImageLimit``,
    ``ImageLength``) end the list: their size is only known after linking."""
    inner = expr.strip()
    while True:
        m = re.match(r"^AlignExpr\s*\((.*)\)\s*$", inner, re.S)
        if not m:
            break
        args, depth, start = [], 0, 0
        for index, char in enumerate(m.group(1)):
            if char == "(":
                depth += 1
            elif char == ")":
                depth -= 1
            elif char == "," and depth == 0:
                args.append(m.group(1)[start:index])
                start = index + 1
        args.append(m.group(1)[start:])
        inner = args[0].strip()
    terms = []
    for part in re.split(r"\+", inner):
        part = part.strip()
        if not part:
            terms.append("")            # a leading "+" : relative to the previous region
            continue
        if re.match(r"^(ImageLimit|ImageBase|ImageLength|LoadLimit|LoadBase)\b", part):
            break
        terms.append(part)
    return terms


def _resolve_addresses(scatter: ScatterFile):
    previous: Optional[ExecRegion] = None
    for region in scatter.regions:
        expr = region.base.strip()
        follows = _FOLLOWS.search(expr)
        terms = _base_terms(expr)
        if follows:
            region.follows = follows.group(1)
        elif terms and terms[0] == "":
            # "+offset" (also "AlignExpr(+0, 8)"): after the previous region of the same load region
            if previous is not None and previous.load_region == region.load_region:
                region.follows = previous.name
        elif terms:
            base = _term_value(scatter, terms[0])
            if base is not None:
                offsets = [_term_value(scatter, t) for t in terms[1:]]
                region.address = base + sum(o for o in offsets if o is not None)
        previous = region

    def address_of(region: ExecRegion, seen=()) -> Optional[int]:
        if region.address is not None or region.follows is None or region.name in seen:
            return region.address
        target = scatter.region(region.follows)
        return address_of(target, seen + (region.name,)) if target is not None else None

    for region in scatter.regions:
        region.address = address_of(region)


# --- placement -----------------------------------------------------------------

@dataclass(frozen=True)
class Placement:
    region: ExecRegion
    selector: Selector
    explicit: bool              # selected by name, not only by attribute or .ANY


def _name_matches(pattern: str, name: str) -> bool:
    return fnmatch.fnmatchcase(name.lower(), pattern.lower())


def placements(scatter: ScatterFile, output: str, kind: str) -> List[Placement]:
    """Where output section ``output`` of ``kind`` goes: the regions selecting it by
    name, else those taking it by attribute (``*(+BSS)``), else ``.ANY``."""
    explicit, by_attribute, by_any = [], [], []
    accepted = KIND_ATTRIBUTES.get(kind, ())
    for region in scatter.regions:
        for selector in region.selectors:
            if any(_name_matches(p, output) for p in selector.names):
                explicit.append(Placement(region, selector, True))
            elif not selector.names and selector.all_files:
                takes = (not selector.attributes if selector.is_any else False) or any(
                    a in accepted for a in selector.attributes)
                if takes:
                    (by_any if selector.is_any else by_attribute).append(
                        Placement(region, selector, False))
    return explicit or by_attribute or by_any
