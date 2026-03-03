"""
Structured diff models for the diff-driven auto-fix system.

DiffItem  →  one logical difference between generated and reference code
FileDiff  →  all differences within one file
DiffReport →  all differences across all files in a module
"""

from __future__ import annotations
from dataclasses import dataclass, field
from enum import Enum
from typing import List, Optional
import json


class DiffType(Enum):
    # --- Functional bugs (must fix) ---
    WRONG_VALUE        = "wrong_value"         # Numeric literal differs (e.g. 3UL vs 0UL)
    WRONG_COUNTER_REF  = "wrong_counter_ref"   # Counter mask wrong (COUNTER_INVALID vs COUNTER1)
    WRONG_CORE_REF     = "wrong_core_ref"      # Core ID mask wrong (CORE0 vs CORE1)
    WRONG_IDENTIFIER   = "wrong_identifier"    # General identifier/symbol differs
    MISSING_LINES      = "missing_lines"       # Lines present in reference, absent in generated
    EXTRA_LINES        = "extra_lines"         # Lines present in generated, absent in reference

    # --- Style / format differences (lower priority) ---
    EXTRA_CAST         = "extra_cast"          # Spurious (uint32) cast in generated code
    BLANK_LINES        = "blank_lines"         # Blank line count differs
    TIMESTAMP          = "timestamp"           # Generation timestamp (auto-ignored)

    # --- Fallback ---
    CONTENT_MISMATCH   = "content_mismatch"    # Unclassified content difference


class Severity(Enum):
    BLOCKING = "blocking"   # Functional difference — must fix before code is correct
    WARNING  = "warning"    # Style/format — does not affect runtime behaviour
    IGNORED  = "ignored"    # Known noise (timestamps, etc.)


# Severity defaults per diff type
_TYPE_SEVERITY: dict[DiffType, Severity] = {
    DiffType.WRONG_VALUE:       Severity.BLOCKING,
    DiffType.WRONG_COUNTER_REF: Severity.BLOCKING,
    DiffType.WRONG_CORE_REF:    Severity.BLOCKING,
    DiffType.WRONG_IDENTIFIER:  Severity.BLOCKING,
    DiffType.MISSING_LINES:     Severity.BLOCKING,
    DiffType.EXTRA_LINES:       Severity.BLOCKING,
    DiffType.EXTRA_CAST:        Severity.WARNING,
    DiffType.BLANK_LINES:       Severity.WARNING,
    DiffType.TIMESTAMP:         Severity.IGNORED,
    DiffType.CONTENT_MISMATCH:  Severity.BLOCKING,
}


@dataclass
class DiffItem:
    diff_id: str                        # Unique ID, e.g. "Os/application/Os_application_Lcfg.c#003"
    file_path: str                      # Relative path from module root
    line_in_reference: int              # 1-based line number in reference file (0 = N/A)
    line_in_generated: int              # 1-based line number in generated file  (0 = N/A)
    diff_type: DiffType
    severity: Severity
    expected_content: str               # What the reference file has
    actual_content: str                 # What our engine generated
    context_before: List[str] = field(default_factory=list)   # Up to 3 lines before
    context_after: List[str]  = field(default_factory=list)   # Up to 3 lines after
    notes: str = ""                     # Extra human-readable notes

    def to_dict(self) -> dict:
        return {
            "diff_id":            self.diff_id,
            "file_path":          self.file_path,
            "line_in_reference":  self.line_in_reference,
            "line_in_generated":  self.line_in_generated,
            "diff_type":          self.diff_type.value,
            "severity":           self.severity.value,
            "expected_content":   self.expected_content,
            "actual_content":     self.actual_content,
            "context_before":     self.context_before,
            "context_after":      self.context_after,
            "notes":              self.notes,
        }


@dataclass
class FileDiff:
    file_path: str              # Relative path from module root
    reference_path: str         # Absolute path to reference file
    generated_path: str         # Absolute path to generated file
    items: List[DiffItem] = field(default_factory=list)

    @property
    def blocking(self) -> List[DiffItem]:
        return [d for d in self.items if d.severity == Severity.BLOCKING]

    @property
    def warnings(self) -> List[DiffItem]:
        return [d for d in self.items if d.severity == Severity.WARNING]

    @property
    def is_clean(self) -> bool:
        return len(self.blocking) == 0

    def summary(self) -> str:
        b = len(self.blocking)
        w = len(self.warnings)
        status = "CLEAN" if self.is_clean else "FAIL"
        return f"[{status}] {self.file_path}  blocking={b}  warnings={w}"


@dataclass
class DiffReport:
    module: str
    reference_root: str         # Absolute path to reference directory
    generated_root: str         # Absolute path to generated directory
    files: List[FileDiff] = field(default_factory=list)
    missing_files: List[str] = field(default_factory=list)   # In reference but not generated
    extra_files: List[str]  = field(default_factory=list)    # In generated but not reference

    @property
    def all_items(self) -> List[DiffItem]:
        return [item for f in self.files for item in f.items]

    @property
    def blocking_items(self) -> List[DiffItem]:
        return [item for f in self.files for item in f.blocking]

    @property
    def total_blocking(self) -> int:
        return len(self.blocking_items)

    @property
    def is_clean(self) -> bool:
        return self.total_blocking == 0 and not self.missing_files

    def type_breakdown(self) -> dict[str, int]:
        """Count blocking items by diff_type (warnings excluded)."""
        counts: dict[str, int] = {}
        for item in self.blocking_items:
            counts[item.diff_type.value] = counts.get(item.diff_type.value, 0) + 1
        return dict(sorted(counts.items(), key=lambda kv: -kv[1]))

    def summary(self, show_details: bool = True, max_items_per_file: int = 5) -> str:
        lines = [
            f"=== DiffReport: {self.module} ===",
            f"  Reference : {self.reference_root}",
            f"  Generated : {self.generated_root}",
            f"  Files checked : {len(self.files)}",
            f"  Missing files : {len(self.missing_files)}",
            f"  Extra files   : {len(self.extra_files)}",
            f"  Blocking diffs: {self.total_blocking}",
            f"  Status        : {'PASS' if self.is_clean else 'FAIL'}",
        ]

        # Breakdown by type
        breakdown = self.type_breakdown()
        if breakdown:
            lines.append("  Breakdown by type:")
            for dtype, count in breakdown.items():
                lines.append(f"    {dtype:<24} {count:>5}")

        if self.missing_files:
            lines.append("  Missing files:")
            for p in self.missing_files:
                lines.append(f"    - {p}")

        if show_details:
            for fd in self.files:
                if not fd.is_clean:
                    lines.append(f"  {fd.summary()}")
                    shown = 0
                    for item in fd.blocking:
                        if shown >= max_items_per_file:
                            remaining = len(fd.blocking) - shown
                            lines.append(f"    ... and {remaining} more blocking items")
                            break
                        lines.append(
                            f"    [{item.diff_type.value}] ref:L{item.line_in_reference}"
                            f"  expected: {item.expected_content.strip()!r}"
                        )
                        lines.append(
                            f"      actual:   {item.actual_content.strip()!r}"
                        )
                        shown += 1

        return "\n".join(lines)

    def to_json(self, indent: int = 2) -> str:
        data = {
            "module":         self.module,
            "reference_root": self.reference_root,
            "generated_root": self.generated_root,
            "missing_files":  self.missing_files,
            "extra_files":    self.extra_files,
            "files": [
                {
                    "file_path":      fd.file_path,
                    "reference_path": fd.reference_path,
                    "generated_path": fd.generated_path,
                    "items": [item.to_dict() for item in fd.items],
                }
                for fd in self.files
            ],
        }
        return json.dumps(data, indent=indent, ensure_ascii=False)
