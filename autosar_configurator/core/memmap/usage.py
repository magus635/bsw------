"""
Memory section usage in C sources

Collects the ``#define <X>_START_SEC_<Y>`` / ``<X>_STOP_SEC_<Y>`` pairs of AUTOSAR
memory mapping and checks how they are written: every START has its STOP at the
same ``#if`` level before the next START, and each definition is followed by the
``#include`` of a MemMap header.  Files with template directives (``[!``) are not
scanned; their generated output is.
"""
import re
from dataclasses import dataclass
from typing import List, Optional, Tuple

_DEFINE = re.compile(r"^\s*#\s*define\s+(\w+?_(START|STOP)_SEC_\w+)\b")
_INCLUDE = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]')
_DIRECTIVE = re.compile(r"^\s*#\s*(\w+)\s*(.*)$")
_C_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
_GUARD_IFNDEF = re.compile(r"^\s*#\s*(?:ifndef\s+(\w+)|if\s+!\s*defined\s*\(?\s*(\w+)\s*\)?)\s*$")
_GUARD_DEFINE = re.compile(r"^\s*#\s*define\s+(\w+)\s*$")

TEMPLATE_MARK = "[!"


@dataclass(frozen=True)
class SectionUse:
    """One START definition and where its STOP was found."""
    name: str                   # <X>_START_SEC_<Y>
    path: str
    line: int
    header: str = ""            # file name of the MemMap header included after it
    conditional: bool = False   # inside an #if branch (other than the include guard)


@dataclass(frozen=True)
class UsageProblem:
    path: str
    line: int
    text: str
    conditional: bool = False


def stop_name(start: str) -> str:
    return start.replace("_START_SEC_", "_STOP_SEC_", 1)


def start_name(stop: str) -> str:
    return stop.replace("_STOP_SEC_", "_START_SEC_", 1)


def is_memmap_header(name: str) -> bool:
    return "memmap" in name.lower().replace("_", "")


def _logical_lines(text: str) -> List[Tuple[int, str]]:
    """(first line number, text) with comments removed and ``\\`` continuations joined."""
    lines = _C_COMMENT.sub(lambda m: "\n" * m.group(0).count("\n"), text).split("\n")
    result = []
    number = 0
    while number < len(lines):
        start, line = number, lines[number]
        while line.endswith("\\") and number + 1 < len(lines):
            number += 1
            line = line[:-1] + " " + lines[number]
        number += 1
        result.append((start + 1, line))
    return result


def _guard(directives: List[Tuple[int, str]]) -> Optional[int]:
    """Line of the include guard ``#ifndef X`` / ``#define X`` when the file starts with one."""
    if len(directives) < 2:
        return None
    m = _GUARD_IFNDEF.match(directives[0][1])
    d = _GUARD_DEFINE.match(directives[1][1])
    if m and d and (m.group(1) or m.group(2)) == d.group(1):
        return directives[0][0]
    return None


Branch = Tuple[Tuple[int, int], ...]      # (#if chain id, branch index) from outer to inner


def exclusive(a: Branch, b: Branch) -> bool:
    """Whether two places lie in different branches of one ``#if`` chain (never both compiled)."""
    for (chain_a, branch_a), (chain_b, branch_b) in zip(a, b):
        if chain_a != chain_b:
            return False
        if branch_a != branch_b:
            return True
    return False


def scan_source(text: str, path: str) -> Tuple[List[SectionUse], List[UsageProblem]]:
    """Section uses and writing problems of one C file.

    A definition may sit in one branch of an ``#if``/``#elif`` chain with the
    ``#include`` after the chain's ``#endif`` (choosing the section per core);
    STARTs in different branches of one chain are alternatives, not a missing STOP.
    """
    directives = [(n, line) for n, line in _logical_lines(text) if line.lstrip().startswith("#")]
    guard_line = _guard(directives)
    kinds = []
    for _, line in directives:
        m = _DIRECTIVE.match(line)
        kinds.append(m.group(1) if m else "")
    uses: List[SectionUse] = []
    problems: List[UsageProblem] = []
    opened: List[Tuple[str, int, int, Branch]] = []     # open STARTs: name, line, depth, branch

    def included_header(index: int) -> Optional[str]:
        """File name of the MemMap header included when the branch of ``index`` is taken:
        the next directive, after leaving the rest of the enclosing chains."""
        j, depth = index + 1, 0
        while j < len(directives):
            kind = kinds[j]
            if depth == 0 and kind in ("elif", "else"):
                depth = 1           # skip the other branches up to this chain's #endif
            elif depth > 0 and kind in ("if", "ifdef", "ifndef"):
                depth += 1
            elif kind == "endif":
                depth = max(depth - 1, 0)
            elif depth == 0:
                m = _INCLUDE.match(directives[j][1])
                name = m.group(1).replace("\\", "/").rsplit("/", 1)[-1] if m else ""
                return name if is_memmap_header(name) else None
            j += 1
        return None

    stack: List[List[int]] = []     # per open #if: [chain id, branch index]
    chains = 0
    for index, (number, line) in enumerate(directives):
        kind = kinds[index]
        if kind in ("if", "ifdef", "ifndef"):
            if number != guard_line:
                chains += 1
                stack.append([chains, 0])
            continue
        if kind in ("elif", "else"):
            if stack:
                stack[-1][1] += 1
            continue
        if kind == "endif":
            if stack:
                stack.pop()
            continue
        d = _DEFINE.match(line)
        if not d:
            continue
        name, which = d.group(1), d.group(2)
        branch: Branch = tuple((c, b) for c, b in stack)
        conditional = bool(stack)
        header = included_header(index)
        if header is None:
            problems.append(UsageProblem(path, number, f"{name} 之后没有 #include MemMap 头文件",
                                         conditional))
        if which == "START":
            for other in [o for o in opened if not exclusive(o[3], branch)]:
                problems.append(UsageProblem(
                    path, other[1], f"{other[0]} 没有对应的 STOP，第 {number} 行又开始了 {name}",
                    conditional))
                opened.remove(other)
            uses.append(SectionUse(name, path, number, header or "", conditional))
            opened.append((name, number, len(stack), branch))
            continue
        match = next((o for o in opened if o[0] == start_name(name)
                      and not exclusive(o[3], branch)), None)
        if match is None:
            problems.append(UsageProblem(path, number, f"{name} 前面没有对应的 START", conditional))
            continue
        if match[2] != len(stack):
            problems.append(UsageProblem(
                path, match[1], f"{match[0]} 与第 {number} 行的 STOP 不在同一 #if 层级",
                conditional))
        opened.remove(match)
    for name, line, depth, _ in opened:
        problems.append(UsageProblem(path, line, f"{name} 没有对应的 STOP", depth > 0))
    return uses, problems
