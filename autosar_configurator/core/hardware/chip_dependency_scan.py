"""
Chip dependency scan

Lists the places that depend on a particular chip, as a checklist for adding a
new one: chip-name checks in definitions, templates and C sources, the default
branches a new chip would fall into, address-like constants templates write out,
and the coverage of each selector value by chips and ECU resource files.

The scan only reads.  It is static: chip names built by string concatenation and
checks made through ``ecu:get`` are not found.
"""
import html
import logging
import os
import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Callable, Dict, Iterable, List, Optional, Set, Tuple

from .ecu_resource_data import flatten_ecu_resources
from .ecu_resource_diagnostics import (
    _module_sources, collect_referenced_keys, collect_referenced_keys_in_dirs)
from .tresos_properties_parser import TresosPropertiesParser, resource_file_matches_chip

logger = logging.getLogger(__name__)

CHECK = "check"
DEFAULT_BRANCH = "default_branch"
HARDCODED = "hardcoded"
COVERAGE = "coverage"
CATEGORIES = (CHECK, DEFAULT_BRANCH, HARDCODED, COVERAGE)
CATEGORY_LABELS = {
    CHECK: "芯片名判断",
    DEFAULT_BRANCH: "隐含默认分支",
    HARDCODED: "疑似写死的数值",
    COVERAGE: "资源覆盖",
}
STATIC_NOTE = ("静态扫描：用字符串拼接得到的芯片名、通过 ecu:get 间接读取的判断不会被发现；"
               "“疑似写死的数值”需人工确认。")

MAX_SCAN_BYTES = 2 * 1024 * 1024
MAX_HARDCODED_PER_FILE = 50
HARDCODED_MIN = 0x10000
# a path further up than this from the project is shown absolute
MAX_PARENT_LEVELS = 3

C_SUFFIXES = {".c", ".h", ".s", ".asm", ".inc", ".ld", ".lsl", ".scat", ".icf", ".lcf"}
TEMPLATE_SUFFIXES = C_SUFFIXES | {".ebt", ".m", ".mak", ".txt", ".xml", ".arxml"}
SKIPPED_DIRS = {".git", ".svn", "__pycache__", ".codegraph"}

_MODEL_TOKEN = re.compile(r"^[A-Z]+\d+[A-Z0-9]*$")
_FAMILY = re.compile(r"^([A-Z]+\d)")
_WORD = re.compile(r"[A-Za-z0-9_]+")
_COMPARE = re.compile(r"""(?:!=|=)\s*(['"])([^'"]*)\1|(['"])([^'"]*)\3\s*(?:!=|=)""")
_NOT_EQUAL = re.compile(r"""!=\s*(['"])([^'"]*)\1|(['"])([^'"]*)\3\s*!=""")
_NOT_DEFINED = re.compile(r"!\s*defined\s*\(?\s*([A-Za-z0-9_]+)")
# the first argument may hold quoted strings itself: as:modconf('Resource')[1]/...
_STRING_FN = re.compile(r"""\b(?:contains|starts-with)\s*\((?:'[^']*'|"[^"]*"|[^'",])*?,\s*(['"])([^'"]*)\1""")
_XDM_EXPR = re.compile(r'\bexpr\s*=\s*"([^"]*)"', re.S)
# "[!//" comments run to the end of the line
_DIRECTIVE = re.compile(r"\[!//[^\n]*|\[!(?!//)(.*?)!\]", re.S)
_COMMENT_LINE = re.compile(r"^\s*(?:;|//|/\*|\*)")
_DIRECTIVE_KIND = re.compile(r"^\s*(IF|ELSEIF|ELSE|ENDIF)\b")
_HEX = re.compile(r"\b0[xX]([0-9A-Fa-f]+)[uUlL]*\b")
_PP = re.compile(r"^\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)$")
_C_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)


class ScanCancelled(Exception):
    """Raised when the progress callback asks to stop."""


@dataclass(frozen=True)
class Finding:
    category: str
    path: str            # POSIX, relative to the project directory when possible
    line: int            # 0 when the finding has no line (coverage)
    text: str
    chips: Tuple[str, ...] = ()
    note: str = ""

    def sort_key(self):
        return (CATEGORIES.index(self.category), self.path.lower(), self.line, self.text)


@dataclass
class ScanResult:
    findings: List[Finding] = field(default_factory=list)
    truncated: Dict[str, int] = field(default_factory=dict)   # path -> hard-coded lines not listed
    skipped: List[str] = field(default_factory=list)          # files over the size limit
    keywords: List[str] = field(default_factory=list)
    files_scanned: int = 0

    def by_category(self, category: str) -> List[Finding]:
        return [f for f in self.findings if f.category == category]

    def chips(self) -> List[str]:
        return sorted({c for f in self.findings for c in f.chips})


# --- chip keywords ------------------------------------------------------------

def model_token(name: str) -> Optional[str]:
    """First ``[A-Z]+digits...`` part of a chip name or selector value
    (``THA6206_LFBGA292`` -> ``THA6206``, ``Os_THA6412`` -> ``THA6412``)."""
    for part in name.upper().split("_"):
        if _MODEL_TOKEN.match(part):
            return part
    return None


class ChipKeywords:
    """Recognises chip names: full names and selector values, model tokens, words
    of a model family (prefix followed by at least one digit or ``X``) and words
    containing a user keyword."""

    def __init__(self, names: Iterable[str], extra: Iterable[str] = ()):
        self.names = {n.upper() for n in names if n}
        self.tokens = {t for t in (model_token(n) for n in self.names) if t}
        self.prefixes = {m.group(1) for m in (_FAMILY.match(t) for t in self.tokens) if m}
        self.extra = {e.strip().upper() for e in extra if e and e.strip()}

    def all(self) -> List[str]:
        return sorted(self.names | self.tokens | {p + "*" for p in self.prefixes} | self.extra)

    def _part_matches(self, part: str) -> bool:
        if part in self.tokens:
            return True
        return any(part.startswith(p) and re.fullmatch(r"[0-9X][A-Z0-9]*", part[len(p):])
                   for p in self.prefixes)

    def chips_in(self, word: str) -> List[str]:
        """Chip names in one word or string literal ([] when none)."""
        upper = word.strip().upper()
        if not upper:
            return []
        if upper in self.names:
            return [word.strip()]
        found = [p for p in upper.split("_") if self._part_matches(p)]
        found += [e for e in self.extra if e in upper and e not in found]
        return found

    def chips_in_words(self, text: str) -> List[str]:
        found: List[str] = []
        for word in _WORD.findall(text):
            for chip in self.chips_in(word):
                if chip not in found:
                    found.append(chip)
        return found


def chip_names(project, chips: Iterable[Any]) -> List[str]:
    """Chip names and selector values of the library chips, plus the declared values
    of the loaded modules' selector parameters."""
    names: Set[str] = set()
    selectors: Set[str] = set()
    for chip in chips:
        names.add(chip.name)
        for key, value in (getattr(chip, "selectors", {}) or {}).items():
            names.add(str(value))
            selectors.add(key)
    for key in selectors:
        names.update(selector_values(project, key))
    return sorted(names)


# --- XPath comparisons ---------------------------------------------------------

def _literals(expr: str) -> List[str]:
    found = []
    for m in _COMPARE.finditer(expr):
        found.append(m.group(2) if m.group(1) else m.group(4))
    found.extend(m.group(2) for m in _STRING_FN.finditer(expr))
    return found


def _negated_chips(expr: str, keywords: ChipKeywords) -> List[str]:
    """Chips an expression checks with ``!=``: every other chip, a new one too,
    takes the branch it guards."""
    chips: List[str] = []
    for m in _NOT_EQUAL.finditer(expr):
        chips += keywords.chips_in(m.group(2) if m.group(1) else m.group(4))
    return list(dict.fromkeys(chips))


def _check_expr_lines(raw: str, first_line: int, keywords: ChipKeywords,
                      unescape: bool) -> List[Tuple[int, str, List[str]]]:
    """(line, text, chips) of each line of an expression comparing against a chip name."""
    hits = []
    for offset, line in enumerate(raw.split("\n")):
        text = html.unescape(line) if unescape else line
        chips: List[str] = []
        for literal in _literals(text):
            for chip in keywords.chips_in(literal):
                if chip not in chips:
                    chips.append(chip)
        if chips:
            hits.append((first_line + offset, text.strip(), chips))
    return hits


def _line_at(text: str, pos: int) -> int:
    return text.count("\n", 0, pos) + 1


def scan_xdm(text: str, path: str, keywords: ChipKeywords) -> List[Finding]:
    findings = []
    for m in _XDM_EXPR.finditer(text):
        for line, line_text, chips in _check_expr_lines(m.group(1), _line_at(text, m.start(1)),
                                                        keywords, unescape=True):
            findings.append(Finding(CHECK, path, line, line_text, tuple(chips)))
    return findings


def scan_template(text: str, path: str, keywords: ChipKeywords,
                  hardcoded: bool = True) -> Tuple[List[Finding], int]:
    """Chip-name checks in directives, ELSE branches of chip IF chains, and
    address-like constants in the output text.  Returns (findings, hard-coded
    lines not listed)."""
    findings: List[Finding] = []
    stack: List[Dict[str, Any]] = []
    for m in _DIRECTIVE.finditer(text):
        body = m.group(1)
        if body is None or body.lstrip().startswith("/*"):
            continue
        line = _line_at(text, m.start())
        hits = _check_expr_lines(body, line, keywords, unescape=False)
        for hit_line, hit_text, chips in hits:
            findings.append(Finding(CHECK, path, hit_line, hit_text, tuple(chips)))
        kind = _DIRECTIVE_KIND.match(body)
        kind = kind.group(1) if kind else None
        negated = _negated_chips(body, keywords) if kind in ("IF", "ELSEIF") else []
        if negated:
            findings.append(Finding(DEFAULT_BRANCH, path, line, body.strip().splitlines()[0],
                                    tuple(negated), "条件是“不等于”；新芯片会进入这个分支"))
        if kind == "IF":
            stack.append({"line": line, "chips": [c for h in hits for c in h[2]]})
        elif kind == "ELSEIF" and stack:
            stack[-1]["chips"].extend(c for h in hits for c in h[2])
        elif kind == "ELSE" and stack and stack[-1]["chips"]:
            top = stack[-1]
            findings.append(Finding(DEFAULT_BRANCH, path, line, "[!ELSE!]",
                                    tuple(dict.fromkeys(top["chips"])),
                                    f"对应第 {top['line']} 行的 IF；新芯片会走这个分支"))
        elif kind == "ENDIF" and stack:
            stack.pop()
    if not hardcoded:
        return findings, 0

    # output text: directives blanked out, line breaks kept
    output = _DIRECTIVE.sub(lambda d: "\n" * d.group(0).count("\n"), text)
    listed = more = 0
    for number, line_text in enumerate(output.split("\n"), 1):
        if _COMMENT_LINE.match(line_text) or not any(
                int(h, 16) >= HARDCODED_MIN for h in _HEX.findall(line_text)):
            continue
        if listed < MAX_HARDCODED_PER_FILE:
            findings.append(Finding(HARDCODED, path, number, line_text.strip()))
            listed += 1
        else:
            more += 1
    return findings, more


def _strip_c_comments(text: str) -> str:
    return _C_COMMENT.sub(lambda m: "\n" * m.group(0).count("\n"), text)


def scan_c(text: str, path: str, keywords: ChipKeywords) -> List[Finding]:
    """Preprocessor conditions naming a chip, and the ``#else`` of such chains."""
    findings: List[Finding] = []
    stack: List[Dict[str, Any]] = []
    lines = _strip_c_comments(text).split("\n")
    number = 0
    while number < len(lines):
        start = number
        line = lines[number]
        while line.endswith("\\") and number + 1 < len(lines):
            number += 1
            line = line[:-1] + " " + lines[number]
        number += 1
        m = _PP.match(line)
        if not m:
            continue
        kind, rest = m.group(1), m.group(2)
        chips = keywords.chips_in_words(rest) if kind in ("if", "ifdef", "ifndef", "elif") else []
        if chips:
            findings.append(Finding(CHECK, path, start + 1, line.strip(), tuple(chips)))
        if kind == "ifndef" and chips:
            negated = chips
        elif kind in ("if", "elif"):
            negated = [c for m in _NOT_DEFINED.finditer(rest) for c in keywords.chips_in(m.group(1))]
        else:
            negated = []
        if negated:
            findings.append(Finding(DEFAULT_BRANCH, path, start + 1, line.strip(),
                                    tuple(dict.fromkeys(negated)),
                                    "条件是“未定义”；新芯片会进入这个分支"))
        if kind in ("if", "ifdef", "ifndef"):
            stack.append({"line": start + 1, "chips": list(chips)})
        elif kind == "elif" and stack:
            stack[-1]["chips"].extend(chips)
        elif kind == "else" and stack and stack[-1]["chips"]:
            top = stack[-1]
            findings.append(Finding(DEFAULT_BRANCH, path, start + 1, line.strip(),
                                    tuple(dict.fromkeys(top["chips"])),
                                    f"对应第 {top['line']} 行的 #if；新芯片会走这个分支"))
        elif kind == "endif" and stack:
            stack.pop()
    return findings


# --- files ---------------------------------------------------------------------

def _project_dir(project) -> Optional[Path]:
    path = getattr(project, "path", None)
    if not path:
        return None
    path = Path(path)
    return path.parent if path.suffix == ".dpa" else path


def display_path(path: Path, base: Optional[Path]) -> str:
    """POSIX path relative to ``base`` (``../`` allowed); absolute when on another drive."""
    if base is not None:
        try:
            relative = Path(os.path.relpath(path, base)).as_posix()
        except ValueError:      # another drive
            relative = None
        if relative is not None and not relative.startswith("../" * (MAX_PARENT_LEVELS + 1)):
            return relative
    return Path(path).as_posix()


def resolve_scan_dir(entry: str, base: Optional[Path]) -> Path:
    path = Path(entry)
    return path if path.is_absolute() or base is None else (base / path).resolve()


def _files_in(directory: Path) -> List[Path]:
    found = []
    for root, dirs, files in os.walk(directory):
        dirs[:] = sorted(d for d in dirs if d not in SKIPPED_DIRS)
        for name in sorted(files):
            path = Path(root) / name
            suffix = path.suffix.lower()
            if suffix == ".xdm" or suffix in TEMPLATE_SUFFIXES:
                found.append(path)
    return found


def _read(path: Path) -> Optional[str]:
    try:
        return path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return None


def scan_file(path: Path, shown: str, keywords: ChipKeywords) -> Tuple[List[Finding], int]:
    """Findings of one file, by its kind: xdm, template (has ``[!`` directives),
    C / assembler / linker script."""
    text = _read(path)
    if text is None:
        return [], 0
    suffix = path.suffix.lower()
    if suffix == ".xdm":
        return scan_xdm(text, shown, keywords), 0
    findings: List[Finding] = []
    more = 0
    if "[!" in text:
        findings, more = scan_template(text, shown, keywords)
    if suffix in C_SUFFIXES:
        findings += scan_c(text, shown, keywords)
    return findings, more


# --- resource coverage ---------------------------------------------------------

@dataclass(frozen=True)
class EcuResourceEntry:
    """One ``ecuresource`` registration of a plugin.xml."""
    plugin_xml: Path
    line: int
    module_id: str
    subderivative: str
    file: Path

    @property
    def module(self) -> str:
        return self.module_id.split("_", 1)[0]


def read_plugin_xml(path: Path) -> List[EcuResourceEntry]:
    from lxml import etree
    try:
        root = etree.parse(str(path)).getroot()
    except (OSError, etree.XMLSyntaxError) as e:
        logger.warning("plugin.xml %s could not be read: %s", path, e)
        return []
    lines = (_read(path) or "").split("\n")

    def start_line(end_line: int) -> int:
        # libxml2 gives the line where the start tag ends; report where it begins
        for number in range(min(end_line, len(lines)), 0, -1):
            if "<ecuresource" in lines[number - 1]:
                return number
        return end_line

    entries = []
    for element in root.iter("ecuresource"):
        value = next((p.get("value") for p in element.iter("parameter")
                      if p.get("name") == "subderivative"), None)
        if value and element.get("file"):
            entries.append(EcuResourceEntry(path, start_line(element.sourceline or 0),
                                            element.get("moduleId", ""), value,
                                            path.parent / element.get("file")))
    return entries


def _find_parameter(module_def, name: str):
    if module_def is None:
        return None
    if name in (getattr(module_def, "parameters", {}) or {}):
        return module_def.parameters[name]

    def walk(container):
        if name in container.parameters:
            return container.parameters[name]
        for sub in container.sub_containers.values():
            found = walk(sub)
            if found is not None:
                return found
        return None

    for container in module_def.containers.values():
        found = walk(container)
        if found is not None:
            return found
    return None


def _module_def(project, module: str):
    manager = (getattr(project, "module_managers", {}) or {}).get(module)
    return getattr(manager, "module_def", None) if manager else None


def selector_values(project, key: str) -> List[str]:
    """Declared values (literals) of the selector parameter ``Module.Param``."""
    module, _, param = key.partition(".")
    definition = _find_parameter(_module_def(project, module), param)
    return [str(v) for v in (getattr(definition, "literals", None) or [])]


def _resource_keys(entries: List[EcuResourceEntry], chips: List[Any]) -> Set[str]:
    keys: Set[str] = set()
    parser = TresosPropertiesParser()
    for entry in entries:
        if entry.file.is_file():
            try:
                keys.update(k.lower() for k in parser.parse_file(entry.file).properties)
            except Exception as e:  # noqa: BLE001 - one bad file must not hide the others
                logger.warning("Failed to parse %s: %s", entry.file, e)
    for chip in chips:
        keys.update(k.lower() for k in flatten_ecu_resources(chip.ecu_resources or {}))
    return keys


def scan_coverage(project, chips: List[Any], entries: List[EcuResourceEntry],
                  referenced: Dict[str, Set[str]], base: Optional[Path]) -> List[Finding]:
    """Coverage of each declared value of each selector parameter."""
    findings: List[Finding] = []
    keys = sorted({k for c in chips for k in (getattr(c, "selectors", {}) or {})})
    defs = getattr(project, "module_defs", {}) or {}
    for key in keys:
        module = key.split(".", 1)[0]
        if _module_def(project, module) is None:
            continue
        where = display_path(Path(defs[module]), base) if defs.get(module) else module
        declared_by = {}
        for chip in chips:
            value = (getattr(chip, "selectors", {}) or {}).get(key)
            if value:
                declared_by.setdefault(value, []).append(chip)
        values = list(dict.fromkeys(selector_values(project, key) + sorted(declared_by)))
        registered = {v: [e for e in entries if e.subderivative == v] for v in values}
        modules_registering = sorted({e.module_id for v in values for e in registered[v]})
        resource_keys = {v: _resource_keys(registered[v], declared_by.get(v, [])) for v in values}

        def add(value, text, path=where, line=0):
            findings.append(Finding(COVERAGE, path, line, f"{key} = {value}：{text}", (value,)))

        for value in values:
            owners = declared_by.get(value, [])
            if not owners:
                add(value, "芯片库中没有声明此值的芯片")
            for module_id in modules_registering:
                if not any(e.module_id == module_id for e in registered[value]):
                    add(value, f"{module_id} 的 plugin.xml 没有为此值登记资源文件")
            for entry in registered[value]:
                shown = display_path(entry.plugin_xml, base)
                if not entry.file.is_file():
                    add(value, f"{entry.module_id} 登记的资源文件不存在：{display_path(entry.file, base)}",
                        shown, entry.line)
                for chip in owners:
                    if not chip.ecu_resources and not resource_file_matches_chip(
                            entry.file.stem, chip.name.lower()):
                        add(value, f"EB 登记 {entry.file.name}，本工具按文件名不会为芯片 "
                                   f"{chip.name} 加载它", shown, entry.line)
            have = resource_keys[value]
            if not have:
                continue
            relevant = {module} | {e.module for e in registered[value]}
            elsewhere = set().union(*(resource_keys[v] for v in values if v != value)) if len(values) > 1 else set()
            for ref, ref_modules in sorted(referenced.items(), key=lambda kv: kv[0].lower()):
                if ref.lower() in have or ref.lower() not in elsewhere or not (ref_modules & relevant):
                    continue
                add(value, f"缺少 {ref}（{', '.join(sorted(ref_modules))} 引用，其他取值有定义）")
    return findings


# --- scan ----------------------------------------------------------------------

def scan_project(project, chips: Optional[List[Any]] = None,
                 extra_dirs: Iterable[str] = (), extra_keywords: Iterable[str] = (),
                 progress: Optional[Callable[[int, int, str], bool]] = None) -> ScanResult:
    """Scan the project's definitions and templates and ``extra_dirs``.

    Args:
        chips: library chips (default: the project's chip library)
        extra_dirs: directories as saved in the project (relative to it, or absolute)
        progress: called before each file with (index, total, path); returning
            False cancels the scan (ScanCancelled)
    """
    if chips is None:
        library = project._chip_library()
        chips = [library.get_chip(n) for n in library.list_chips()]
        chips = [c for c in chips if c is not None]
    base = _project_dir(project)
    keywords = ChipKeywords(chip_names(project, chips), extra_keywords)
    result = ScanResult(keywords=keywords.all())

    files: List[Path] = []
    for module, def_path in sorted((getattr(project, "module_defs", {}) or {}).items()):
        if def_path:
            files.extend(_module_sources(project, module, Path(def_path)))
    dirs = [resolve_scan_dir(d, base) for d in extra_dirs]
    for directory in dirs:
        if directory.is_dir():
            files.extend(_files_in(directory))
        else:
            logger.warning("Chip scan directory not found: %s", directory)
    unique: Dict[Path, Path] = {}
    for f in files:
        unique.setdefault(f.resolve(), f)
    ordered = sorted(unique.values(), key=lambda p: display_path(p, base).lower())

    for index, path in enumerate(ordered):
        shown = display_path(path, base)
        if progress is not None and progress(index, len(ordered), shown) is False:
            raise ScanCancelled()
        try:
            too_big = path.stat().st_size > MAX_SCAN_BYTES
        except OSError:
            continue
        if too_big:
            result.skipped.append(shown)
            continue
        found, more = scan_file(path, shown, keywords)
        result.findings.extend(found)
        if more:
            result.truncated[shown] = more
        result.files_scanned += 1

    plugin_xmls: Dict[Path, Path] = {}
    for def_path in (getattr(project, "module_defs", {}) or {}).values():
        if def_path:
            candidate = Path(def_path).parent.parent / "plugin.xml"
            if candidate.is_file():
                plugin_xmls.setdefault(candidate.resolve(), candidate)
    for directory in dirs:
        if directory.is_dir():
            for candidate in directory.rglob("plugin.xml"):
                plugin_xmls.setdefault(candidate.resolve(), candidate)
    entries = [e for p in sorted(plugin_xmls) for e in read_plugin_xml(plugin_xmls[p])]
    referenced = collect_referenced_keys(project)
    for key, modules in collect_referenced_keys_in_dirs([d for d in dirs if d.is_dir()]).items():
        referenced.setdefault(key, set()).update(modules)
    result.findings.extend(scan_coverage(project, chips, entries, referenced, base))

    result.findings = sorted(set(result.findings), key=Finding.sort_key)
    if progress is not None:
        progress(len(ordered), len(ordered), "")
    return result


# --- checklist -----------------------------------------------------------------

def to_markdown(result: ScanResult, title: str = "新增芯片检查清单",
                findings: Optional[List[Finding]] = None) -> str:
    """Markdown checklist: one unchecked item per finding, grouped by category."""
    findings = result.findings if findings is None else findings
    lines = [f"# {title}", "", f"> {STATIC_NOTE}", "",
             f"芯片关键字：{', '.join(result.keywords)}", ""]
    for category in CATEGORIES:
        items = [f for f in findings if f.category == category]
        if not items:
            continue
        lines += [f"## {CATEGORY_LABELS[category]}（{len(items)}）", ""]
        for f in items:
            where = f"{f.path}:{f.line}" if f.line else f.path
            extra = f"（芯片：{', '.join(f.chips)}）" if f.chips and category != COVERAGE else ""
            note = f" — {f.note}" if f.note else ""
            text = f.text.replace("`", "'")
            lines.append(f"- [ ] `{where}` {text}{extra}{note}")
        if category == HARDCODED:
            for path, more in sorted(result.truncated.items()):
                lines.append(f"- [ ] `{path}` 另有 {more} 行未列出")
        lines.append("")
    if result.skipped:
        lines += ["## 未扫描（超过 2 MB）", ""] + [f"- `{p}`" for p in result.skipped] + [""]
    return "\n".join(lines)
