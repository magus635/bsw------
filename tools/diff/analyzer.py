"""
Structured diff analyzer for AUTOSAR BSW generated C code.

Usage:
    from tools.diff.analyzer import DiffAnalyzer

    report = DiffAnalyzer(
        module="Os",
        reference_root="/path/to/reference/Os",
        generated_root="/path/to/generated/Os",
    ).analyze()

    print(report.summary())
    # report.to_json() for machine-readable output
"""

from __future__ import annotations

import os
import re
import difflib
from pathlib import Path
from typing import List, Tuple

from .models import (
    DiffItem, DiffType, FileDiff, DiffReport, Severity, _TYPE_SEVERITY
)

# ---------------------------------------------------------------------------
# Patterns for classifying diff lines
# ---------------------------------------------------------------------------

# Lines whose differences are always ignored (timestamps, build info)
_IGNORE_PATTERNS = [
    re.compile(r'Genaration\s*Time', re.IGNORECASE),
    re.compile(r'Generation\s*Time', re.IGNORECASE),
    re.compile(r'\*\s+Build\s+Version', re.IGNORECASE),
]

# Counter mask: APPLICATION_COUNTER_INVALID_ID_MASK vs APPLICATION_COUNTER\d+_ID_MASK
_COUNTER_REF_RE = re.compile(r'APPLICATION_COUNTER(?:_INVALID|\d+)_ID_MASK')

# Core ID mask: CORE0_ID_MASK vs CORE1_ID_MASK
_CORE_REF_RE = re.compile(r'CORE(\d+)_ID_MASK')

# Extra (uint32) cast: (uint32)MACRO vs MACRO
_EXTRA_CAST_RE = re.compile(r'\(uint32\)')

# Numeric literal suffix (UL, U, L)
_NUMERIC_RE = re.compile(r'\b\d+(?:UL|U|L)?\b')

# Pointer name with core prefix: Core0_Xxx vs Core1_Xxx
_CORE_PTR_RE = re.compile(r'(?:Core|core)(\d+)_\w+')

# File extensions we care about
_C_EXTENSIONS = {'.c', '.h', '.s', '.scat', '.orti'}

CONTEXT_LINES = 3   # lines of context to capture around each diff


def _normalize(text: str) -> List[str]:
    """Strip CRLF, split into lines, preserve trailing spaces stripped."""
    return [line.rstrip('\r\n') for line in text.splitlines()]


def _is_ignored(line: str) -> bool:
    return any(p.search(line) for p in _IGNORE_PATTERNS)


def _is_blank(line: str) -> bool:
    return line.strip() == ""


def _classify(expected: str, actual: str) -> Tuple[DiffType, str]:
    """
    Classify a single-line substitution (expected vs actual).
    Returns (DiffType, notes).
    """
    # Timestamp noise
    if _is_ignored(expected) or _is_ignored(actual):
        return DiffType.TIMESTAMP, "timestamp line"

    # Extra (uint32) cast in generated code
    actual_no_cast = _EXTRA_CAST_RE.sub('', actual)
    if actual_no_cast.strip() == expected.strip():
        return DiffType.EXTRA_CAST, f"spurious (uint32) cast added in generated"

    # Counter reference mismatch
    exp_counters = set(_COUNTER_REF_RE.findall(expected))
    act_counters = set(_COUNTER_REF_RE.findall(actual))
    if exp_counters != act_counters and (exp_counters or act_counters):
        return DiffType.WRONG_COUNTER_REF, (
            f"expected counter refs {exp_counters}, got {act_counters}"
        )

    # Core ID mismatch (CORE0 vs CORE1 in mask or pointer)
    exp_cores = set(_CORE_REF_RE.findall(expected)) | set(_CORE_PTR_RE.findall(expected))
    act_cores = set(_CORE_REF_RE.findall(actual))   | set(_CORE_PTR_RE.findall(actual))
    if exp_cores != act_cores and (exp_cores or act_cores):
        return DiffType.WRONG_CORE_REF, (
            f"expected core ids {exp_cores}, got {act_cores}"
        )

    # Pure numeric value difference (same structure, different number)
    exp_nums = _NUMERIC_RE.findall(expected)
    act_nums = _NUMERIC_RE.findall(actual)
    if exp_nums != act_nums and len(exp_nums) == len(act_nums) and len(exp_nums) > 0:
        exp_no_nums = _NUMERIC_RE.sub('N', expected)
        act_no_nums = _NUMERIC_RE.sub('N', actual)
        if exp_no_nums.strip() == act_no_nums.strip():
            return DiffType.WRONG_VALUE, f"values differ: {exp_nums} vs {act_nums}"

    # Generic identifier mismatch — tokenise and compare
    exp_words = set(re.findall(r'\b[A-Za-z_]\w*\b', expected))
    act_words = set(re.findall(r'\b[A-Za-z_]\w*\b', actual))
    if exp_words != act_words:
        added   = act_words - exp_words
        removed = exp_words - act_words
        return DiffType.WRONG_IDENTIFIER, (
            f"identifiers removed={removed} added={added}"
        )

    return DiffType.CONTENT_MISMATCH, "unclassified content difference"


class DiffAnalyzer:
    def __init__(
        self,
        module: str,
        reference_root: str,
        generated_root: str,
        extensions: set[str] | None = None,
    ):
        self.module = module
        self.ref_root = Path(reference_root)
        self.gen_root = Path(generated_root)
        self.extensions = extensions or _C_EXTENSIONS

    # ------------------------------------------------------------------
    # Public API
    # ------------------------------------------------------------------

    def analyze(self) -> DiffReport:
        report = DiffReport(
            module=self.module,
            reference_root=str(self.ref_root),
            generated_root=str(self.gen_root),
        )

        ref_files = self._collect_files(self.ref_root)
        gen_files = self._collect_files(self.gen_root)

        for rel in sorted(ref_files):
            if rel not in gen_files:
                report.missing_files.append(rel)
            else:
                fd = self._diff_file(
                    rel_path=rel,
                    ref_abs=str(self.ref_root / rel),
                    gen_abs=str(self.gen_root / rel),
                )
                report.files.append(fd)

        for rel in sorted(gen_files):
            if rel not in ref_files:
                report.extra_files.append(rel)

        return report

    # ------------------------------------------------------------------
    # Internal helpers
    # ------------------------------------------------------------------

    def _collect_files(self, root: Path) -> dict[str, Path]:
        """Return {relative_path_str: absolute_Path} for all matching files."""
        result = {}
        for dirpath, _, filenames in os.walk(root):
            for fn in filenames:
                if Path(fn).suffix.lower() in self.extensions:
                    abs_path = Path(dirpath) / fn
                    rel = str(abs_path.relative_to(root))
                    result[rel] = abs_path
        return result

    def _diff_file(self, rel_path: str, ref_abs: str, gen_abs: str) -> FileDiff:
        fd = FileDiff(
            file_path=rel_path,
            reference_path=ref_abs,
            generated_path=gen_abs,
        )

        ref_lines = _normalize(Path(ref_abs).read_text(encoding='utf-8', errors='replace'))
        gen_lines = _normalize(Path(gen_abs).read_text(encoding='utf-8', errors='replace'))

        matcher = difflib.SequenceMatcher(
            isjunk=None,
            a=ref_lines,
            b=gen_lines,
            autojunk=False,
        )

        item_counter = 0

        def make_id() -> str:
            nonlocal item_counter
            item_counter += 1
            safe = rel_path.replace(os.sep, '/').replace(' ', '_')
            return f"{self.module}/{safe}#{item_counter:03d}"

        for tag, i1, i2, j1, j2 in matcher.get_opcodes():
            if tag == 'equal':
                continue

            if tag == 'replace':
                # Pair up lines 1:1 where possible, overflow → insert/delete
                ref_seg = ref_lines[i1:i2]
                gen_seg = gen_lines[j1:j2]
                min_len = min(len(ref_seg), len(gen_seg))

                for k in range(min_len):
                    exp = ref_seg[k]
                    act = gen_seg[k]
                    ref_lineno = i1 + k + 1
                    gen_lineno = j1 + k + 1

                    # Both blank → blank line diff
                    if _is_blank(exp) and _is_blank(act):
                        continue

                    dtype, notes = _classify(exp, act)
                    sev = _TYPE_SEVERITY[dtype]

                    fd.items.append(DiffItem(
                        diff_id=make_id(),
                        file_path=rel_path,
                        line_in_reference=ref_lineno,
                        line_in_generated=gen_lineno,
                        diff_type=dtype,
                        severity=sev,
                        expected_content=exp,
                        actual_content=act,
                        context_before=ref_lines[max(0, i1+k-CONTEXT_LINES): i1+k],
                        context_after=ref_lines[i1+k+1: i1+k+1+CONTEXT_LINES],
                        notes=notes,
                    ))

                # Leftover reference lines → MISSING
                for k in range(min_len, len(ref_seg)):
                    exp = ref_seg[k]
                    if _is_blank(exp):
                        dtype, sev, notes = DiffType.BLANK_LINES, Severity.WARNING, "blank line missing"
                    elif _is_ignored(exp):
                        dtype, sev, notes = DiffType.TIMESTAMP, Severity.IGNORED, "timestamp"
                    else:
                        dtype, sev, notes = DiffType.MISSING_LINES, Severity.BLOCKING, "line in reference, not in generated"
                    ref_lineno = i1 + k + 1
                    fd.items.append(DiffItem(
                        diff_id=make_id(),
                        file_path=rel_path,
                        line_in_reference=ref_lineno,
                        line_in_generated=0,
                        diff_type=dtype,
                        severity=sev,
                        expected_content=exp,
                        actual_content="",
                        context_before=ref_lines[max(0, i1+k-CONTEXT_LINES): i1+k],
                        context_after=ref_lines[i1+k+1: i1+k+1+CONTEXT_LINES],
                        notes=notes,
                    ))

                # Leftover generated lines → EXTRA
                for k in range(min_len, len(gen_seg)):
                    act = gen_seg[k]
                    if _is_blank(act):
                        dtype, sev, notes = DiffType.BLANK_LINES, Severity.WARNING, "extra blank line"
                    elif _is_ignored(act):
                        dtype, sev, notes = DiffType.TIMESTAMP, Severity.IGNORED, "timestamp"
                    else:
                        dtype, sev, notes = DiffType.EXTRA_LINES, Severity.BLOCKING, "extra line in generated"
                    gen_lineno = j1 + k + 1
                    fd.items.append(DiffItem(
                        diff_id=make_id(),
                        file_path=rel_path,
                        line_in_reference=0,
                        line_in_generated=gen_lineno,
                        diff_type=dtype,
                        severity=sev,
                        expected_content="",
                        actual_content=act,
                        context_before=gen_lines[max(0, j1+k-CONTEXT_LINES): j1+k],
                        context_after=gen_lines[j1+k+1: j1+k+1+CONTEXT_LINES],
                        notes=notes,
                    ))

            elif tag == 'delete':
                # Lines in reference not in generated
                for k, exp in enumerate(ref_lines[i1:i2]):
                    if _is_blank(exp):
                        dtype, sev, notes = DiffType.BLANK_LINES, Severity.WARNING, "blank line missing"
                    elif _is_ignored(exp):
                        dtype, sev, notes = DiffType.TIMESTAMP, Severity.IGNORED, "timestamp"
                    else:
                        dtype, sev, notes = DiffType.MISSING_LINES, Severity.BLOCKING, "line in reference, not in generated"
                    ref_lineno = i1 + k + 1
                    fd.items.append(DiffItem(
                        diff_id=make_id(),
                        file_path=rel_path,
                        line_in_reference=ref_lineno,
                        line_in_generated=0,
                        diff_type=dtype,
                        severity=sev,
                        expected_content=exp,
                        actual_content="",
                        context_before=ref_lines[max(0, i1+k-CONTEXT_LINES): i1+k],
                        context_after=ref_lines[i1+k+1: i1+k+1+CONTEXT_LINES],
                        notes=notes,
                    ))

            elif tag == 'insert':
                # Lines in generated not in reference
                for k, act in enumerate(gen_lines[j1:j2]):
                    if _is_blank(act):
                        dtype, sev, notes = DiffType.BLANK_LINES, Severity.WARNING, "extra blank line"
                    elif _is_ignored(act):
                        dtype, sev, notes = DiffType.TIMESTAMP, Severity.IGNORED, "timestamp"
                    else:
                        dtype, sev, notes = DiffType.EXTRA_LINES, Severity.BLOCKING, "extra line in generated"
                    gen_lineno = j1 + k + 1
                    fd.items.append(DiffItem(
                        diff_id=make_id(),
                        file_path=rel_path,
                        line_in_reference=0,
                        line_in_generated=gen_lineno,
                        diff_type=dtype,
                        severity=sev,
                        expected_content="",
                        actual_content=act,
                        context_before=gen_lines[max(0, j1+k-CONTEXT_LINES): j1+k],
                        context_after=gen_lines[j1+k+1: j1+k+1+CONTEXT_LINES],
                        notes=notes,
                    ))

        return fd
