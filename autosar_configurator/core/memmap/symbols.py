"""
Link symbol needs

Source and generated code refer to linker symbols by region name: the vendor
startup code through macros (``STARTUP_GETCOPYDATAINFO(UNDEFINE_RAM_DATA, x)``),
the OS generated code directly (``Image$$OS_DATA_CORE0$$Base``).  A linker file
has to provide those names.  This module reads the references, merges them per
region and keeps the compiler conventions in one table, so that the check and,
later, the generation of linker files use the same definitions.
"""
import re
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Tuple

from .usage import _C_COMMENT, _DIRECTIVE, _guard, _logical_lines

COPY = "copy"
CLEAR = "clear"
BASE = "base"
LIMIT = "limit"
LOAD = "load"
STACK = "stack"
USES = (COPY, CLEAR, BASE, LIMIT, LOAD, STACK)
USE_LABELS = {COPY: "复制", CLEAR: "清零", BASE: "基址", LIMIT: "界限", LOAD: "加载地址", STACK: "栈顶"}
LIMIT_USES = (CLEAR, LIMIT)

ADS = "ads"
GHS = "ghs"

# macro -> (index of the region name among its arguments, uses it asks for)
MACROS: Dict[str, Tuple[int, Tuple[str, ...]]] = {
    "STARTUP_GETCOPYDATAINFO": (0, (BASE, LIMIT, LOAD, COPY)),
    "STARTUP_GETBSSDATAINFO": (0, (BASE, CLEAR)),
    "STARTUP_GETIMAGEBASEADDR": (0, (BASE,)),
    "STARTUP_GETIMAGELIMITADDR": (0, (LIMIT,)),
    "STARTUP_GETIMAGEBSSLIMITADDR": (0, (CLEAR,)),
    "STARTUP_GETLOADBASEADDR": (0, (LOAD,)),
    "STARTUP_SETSTACK": (1, (STACK,)),
    "STARTUP_SETHYPMODESP": (0, (STACK,)),
}

# The symbols a region has to provide for each use, per compiler (``{r}`` is the region).
# ADS takes a cleared region's limit from the ``$$ZI`` variant; GHS uses one end symbol.
SYMBOLS: Dict[str, Dict[str, Tuple[str, ...]]] = {
    ADS: {
        BASE: ("Image$${r}$$Base",),
        LIMIT: ("Image$${r}_LIMIT$$Base",),
        CLEAR: ("Image$${r}_LIMIT$$ZI$$Base",),
        LOAD: ("Load$${r}$$Base",),
        STACK: ("Image$${r}$$ZI$$Limit",),
    },
    GHS: {
        BASE: ("__{r}_ADDRESS_START",),
        LIMIT: ("__{r}_ADDRESS_END",),
        CLEAR: ("__{r}_ADDRESS_END",),
        LOAD: ("__{r}_LOAD_ADDRESS_START",),
        STACK: ("__{r}_ADDRESS_END",),
    },
}
LIMIT_REGION_SUFFIX = "_LIMIT"

_NAME = r"[A-Za-z_]\w*"
_IDENT = re.compile(r"^" + _NAME + r"$")
_MACRO = re.compile(r"\b(" + "|".join(sorted(MACROS, key=len, reverse=True)) + r")\s*\(")
# Image$$R$$Base, Image$$R_LIMIT$$Base, Image$$R_LIMIT$$ZI$$Base, Image$$R$$ZI$$Limit,
# Load$$R$$Base, Load$$R$$Limit
_ADS = re.compile(r"\b(Image|Load)\$\$(" + _NAME + r")\$\$((?:ZI\$\$)?(?:Base|Limit))\b")
# __R_ADDRESS_START, __R_ADDRESS_END, __R_LOAD_ADDRESS_START.  The name is lazy: greedy, it
# would take "R_LOAD" of __R_LOAD_ADDRESS_START and read it as the base of a region R_LOAD.
_GHS = re.compile(r"\b__([A-Za-z_]\w*?)_(LOAD_ADDRESS_START|ADDRESS_START|ADDRESS_END)\b")
_GHS_USES = {"ADDRESS_START": BASE, "ADDRESS_END": LIMIT, "LOAD_ADDRESS_START": LOAD}


@dataclass(frozen=True)
class Reference:
    """One place that refers to a region."""
    region: str
    uses: Tuple[str, ...]
    path: str
    line: int
    how: str                        # the macro or the symbol as written
    conditional: bool = False


@dataclass
class RegionNeed:
    """Everything the code needs from one region name."""
    region: str
    uses: List[str] = field(default_factory=list)
    references: List[Reference] = field(default_factory=list)

    @property
    def conditional(self) -> bool:
        return all(r.conditional for r in self.references)

    def uses_text(self) -> str:
        return "、".join(USE_LABELS[u] for u in self.uses)

    def needs_limit_region(self) -> bool:
        """ADS takes a region's limit symbols from an empty ``<R>_LIMIT`` region.  A stack
        only asks for its top, so it needs none."""
        return any(u in LIMIT_USES for u in self.uses)


def _blank_comments(text: str) -> str:
    """Comments replaced by blanks so that line numbers stay."""
    return _C_COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def _line_of(text: str, index: int) -> int:
    return text.count("\n", 0, index) + 1


def _arguments(text: str, start: int) -> Optional[List[str]]:
    """The arguments of the call whose ``(`` sits just before ``start``."""
    depth, args, current = 1, [], []
    for char in text[start:]:
        if char == "(":
            depth += 1
            current.append(char)
        elif char == ")":
            depth -= 1
            if depth == 0:
                args.append("".join(current).strip())
                return args
            current.append(char)
        elif char == "," and depth == 1:
            args.append("".join(current).strip())
            current = []
        else:
            current.append(char)
    return None


def _directives(text: str):
    """(line number, kind) of every preprocessor directive, and the include guard's lines."""
    directives = [(n, line) for n, line in _logical_lines(text) if line.lstrip().startswith("#")]
    kinds: Dict[int, str] = {}
    for number, line in directives:
        m = _DIRECTIVE.match(line)
        kinds[number] = m.group(1) if m else ""
    guard_line = _guard(directives)
    guard_end = None
    if guard_line is not None:
        depth = 0
        for number, _ in directives:
            if number < guard_line:
                continue
            kind = kinds[number]
            if kind in ("if", "ifdef", "ifndef"):
                depth += 1
            elif kind == "endif":
                depth -= 1
                if depth == 0:
                    guard_end = number
                    break
    return kinds, guard_line, guard_end


def _conditional_lines(text: str, kinds: Dict[int, str], guard_line, guard_end) -> set:
    """Lines inside an ``#if`` branch, leaving out the file's include guard."""
    inside, depth = set(), 0
    for number in range(1, text.count("\n") + 2):
        if number == guard_line or number == guard_end:
            continue
        kind = kinds.get(number)
        if kind in ("if", "ifdef", "ifndef"):
            depth += 1
        elif kind == "endif":
            depth = max(depth - 1, 0)
        elif depth:
            inside.add(number)
    return inside


def scan_needs(text: str, path: str) -> List[Reference]:
    """The region references of one C file.

    A reference inside a ``#define`` is a macro definition, not a use, and is not
    recorded: the startup headers define the macros in terms of parameter names.
    """
    clean = _blank_comments(text)
    kinds, guard_line, guard_end = _directives(clean)
    inside = _conditional_lines(clean, kinds, guard_line, guard_end)
    definitions = set()             # every physical line of every #define, continuations included
    logical = _logical_lines(clean)
    for index, (number, _) in enumerate(logical):
        if kinds.get(number) == "define":
            end = logical[index + 1][0] if index + 1 < len(logical) else number + 1
            definitions.update(range(number, max(end, number + 1)))
    found: List[Reference] = []

    def add(region: str, uses, index: int, how: str):
        line = _line_of(clean, index)
        if line in definitions:
            return
        found.append(Reference(region, uses, path, line, how, line in inside))

    for m in _MACRO.finditer(clean):
        index, uses = MACROS[m.group(1)]
        args = _arguments(clean, m.end())
        if args is None or index >= len(args) or not _IDENT.match(args[index]):
            continue                # an expression or a parameter name: no region to look for
        add(args[index], uses, m.start(), m.group(1))
    for m in _ADS.finditer(clean):
        kind, region, tail = m.group(1), m.group(2), m.group(3)
        if kind == "Load":
            add(region, (LOAD,), m.start(), m.group(0))
        elif tail == "ZI$$Limit":
            add(region, (STACK,), m.start(), m.group(0))
        elif tail == "ZI$$Base":
            add(region[:-len(LIMIT_REGION_SUFFIX)] if region.endswith(LIMIT_REGION_SUFFIX)
                else region, (CLEAR,), m.start(), m.group(0))
        elif tail == "Base":
            if region.endswith(LIMIT_REGION_SUFFIX):
                add(region[:-len(LIMIT_REGION_SUFFIX)], (LIMIT,), m.start(), m.group(0))
            else:
                add(region, (BASE,), m.start(), m.group(0))
    for m in _GHS.finditer(clean):
        add(m.group(1), (_GHS_USES[m.group(2)],), m.start(), m.group(0))
    return found


def merge(references: List[Reference]) -> List[RegionNeed]:
    """One entry per region name, sorted by name, its references in file order."""
    needs: Dict[str, RegionNeed] = {}
    for ref in references:
        needs.setdefault(ref.region, RegionNeed(ref.region)).references.append(ref)
    for need in needs.values():
        need.uses = sorted({u for ref in need.references for u in ref.uses}, key=USES.index)
        need.references.sort(key=lambda r: (r.path.lower(), r.line, r.how))
    return [needs[name] for name in sorted(needs)]


def symbols_for(compiler: str, region: str, uses) -> List[str]:
    """The linker symbols ``region`` has to provide for ``uses`` under ``compiler``."""
    table = SYMBOLS[compiler]
    found: List[str] = []
    for use in uses:
        for pattern in table.get(use, ()):
            symbol = pattern.format(r=region)
            if symbol not in found:
                found.append(symbol)
    return found
