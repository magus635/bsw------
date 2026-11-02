"""
MemMap headers

Reads the section mapping of ``<Msn>_MemMap.h`` style headers: a branch
``#if defined <X>_START_SEC_<Y>`` or ``#elif defined <X>_START_SEC_<Y>`` followed by
``MEMMAP_START_TEXT|RODATA|DATA|BSS("<output section>")``.  Both the vendor's static
headers and generated ones (``Os_memmap.h``) use this form; the compiler-specific
pragma behind ``MEMMAP_START_*`` lives in ``Compiler.h`` and does not matter here.
"""
import re
from dataclasses import dataclass
from typing import Dict, List, Tuple

from .usage import Branch, _logical_lines, exclusive

KINDS = ("TEXT", "RODATA", "DATA", "BSS")

_DIRECTIVE = re.compile(r"^\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)$")
_START_DEFINED = re.compile(r"^defined\s*\(?\s*(\w+_START_SEC_\w+)\s*\)?\s*$")
_MAPPING = re.compile(r'\bMEMMAP_START_(TEXT|RODATA|DATA|BSS)\s*\(\s*"([^"]+)"\s*\)')


@dataclass(frozen=True)
class SectionMapping:
    name: str            # <X>_START_SEC_<Y>
    kind: str            # TEXT, RODATA, DATA or BSS
    output: str          # output section, e.g. .mcal_bss_asil_d_unspecified_core0
    path: str
    line: int


def parse_header(text: str, path: str) -> Tuple[List[SectionMapping], List[SectionMapping]]:
    """(mappings, repeated mappings) of one header, in file order.

    A section mapped in two branches of one ``#if``/``#elif`` chain (one per chip, say)
    is mapped once for each build, so it is not repeated; the same section mapped twice
    where both can be compiled is.
    """
    mappings: List[SectionMapping] = []
    repeated: List[SectionMapping] = []
    seen: Dict[str, List[Branch]] = {}       # section -> the branches it is mapped in
    current = None          # (START name, line, #if depth of its branch)
    depth = 0
    chains = 0
    stack: List[List[int]] = []              # per open #if: [chain id, branch index]
    for number, line in _logical_lines(text):
        directive = _DIRECTIVE.match(line)
        kind = directive.group(1) if directive else None
        if kind in ("if", "ifdef", "ifndef"):
            depth += 1
            chains += 1
            stack.append([chains, 0])
        elif kind in ("elif", "else") and stack:
            stack[-1][1] += 1
        if kind in ("if", "elif"):
            m = _START_DEFINED.match(directive.group(2).strip())
            if m:
                current = (m.group(1), number, depth)
                continue
        if kind in ("elif", "else", "endif") and current is not None and depth == current[2]:
            current = None
        if kind == "endif":
            depth = max(depth - 1, 0)
            if stack:
                stack.pop()
        if current is None or kind is not None:
            continue
        m = _MAPPING.search(line)
        if not m:
            continue
        mapping = SectionMapping(current[0], m.group(1), m.group(2), path, current[1])
        # The branch that selects the section (``#elif defined X_START_SEC_Y``) does not
        # count: two of those in one chain are alternatives only on paper, the second is
        # never taken.  What makes two mappings exclusive is an enclosing branch, e.g. one per chip.
        branch: Branch = tuple((c, b) for c, b in stack[:current[2] - 1])
        current = None
        earlier = seen.setdefault(mapping.name, [])
        if any(not exclusive(branch, other) for other in earlier):
            repeated.append(mapping)
        else:
            mappings.append(mapping)
        earlier.append(branch)
    return mappings, repeated
