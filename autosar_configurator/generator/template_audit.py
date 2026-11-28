"""Non-destructive template coverage, quality, and reference-parity audit service."""

from dataclasses import asdict, dataclass, field
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from typing import Any, Dict, List, Optional, Sequence, Set, Tuple

from ..core import project_paths
from ..core.workspace_manager import WorkspaceManager
from .generator import CodeGenerator
from .platform_gen import generate_platform_artifacts
from .rte import RteSchMGenerator

_DEFINE_RE = re.compile(r"^\s*#\s*define\s+([A-Za-z0-9_]+)", re.M)
_CSL_SYM_RE = re.compile(r"\b(?:CONST|VAR)\s*\([^)]+\)\s+([A-Za-z0-9_]+)")
_EXCLUDED_REF_DIRS = ("RteCache", "RteAnalyzer")


@dataclass
class FileParityDetail:
    """Per-file quality and parity metrics."""

    filename: str
    module_name: str
    status: str  # "matched" | "extra"
    gen_lines: int = 0
    ref_lines: int = 0
    define_match: int = 0
    define_total: int = 0
    sym_match: int = 0
    sym_total: int = 0
    unexpanded_tags: bool = False
    has_todo: bool = False
    clang_ok: Optional[bool] = None
    clang_error: str = ""


@dataclass
class ModuleAuditResult:
    """Aggregated audit metrics for one loaded ECUC module."""

    module_name: str
    template_dir_name: str
    status: str  # "OK" | "SKIPPED" | "ERROR"
    generated_count: int = 0
    unexpanded_files: List[str] = field(default_factory=list)
    todo_files: List[str] = field(default_factory=list)
    error_message: str = ""
    generated_files: List[str] = field(default_factory=list)
    matched_ref_count: int = 0
    define_match_total: int = 0
    define_ref_total: int = 0
    sym_match_total: int = 0
    sym_ref_total: int = 0


@dataclass
class TemplateAuditReport:
    """Complete dry-run and reference parity audit report for a .dpa project."""

    project_name: str
    dpa_path: str
    total_loaded_modules: int = 0
    ok_modules: int = 0
    skipped_modules: int = 0
    error_modules: int = 0
    total_generated_files: int = 0
    total_unexpanded_files: int = 0
    ref_gendata_dir: str = ""
    ref_total_files: int = 0
    ref_matched_files: int = 0
    ref_missing_files: List[str] = field(default_factory=list)
    define_match_total: int = 0
    define_ref_total: int = 0
    clang_checked_files: int = 0
    clang_passed_files: int = 0
    clang_failures: List[Tuple[str, str]] = field(default_factory=list)
    module_results: List[ModuleAuditResult] = field(default_factory=list)
    file_details: List[FileParityDetail] = field(default_factory=list)

    def to_dict(self) -> Dict[str, Any]:
        return asdict(self)

    def to_markdown(self) -> str:
        lines: List[str] = [
            f"# Template Audit Report: {self.project_name}",
            "",
            f"- DPA: `{self.dpa_path}`",
            f"- Modules: {self.ok_modules}/{self.total_loaded_modules} OK, {self.skipped_modules} SKIPPED, {self.error_modules} ERROR",
            f"- Generated files: {self.total_generated_files} (unexpanded EB tags: {self.total_unexpanded_files})",
        ]
        if self.ref_gendata_dir:
            pct = (100 * self.define_match_total // self.define_ref_total) if self.define_ref_total else 100
            lines.extend([
                f"- Reference GenData: `{self.ref_gendata_dir}`",
                f"- File coverage: {self.ref_matched_files}/{self.ref_total_files} matched, {len(self.ref_missing_files)} missing",
                f"- `#define` parity across matched files: {self.define_match_total}/{self.define_ref_total} ({pct}%)",
            ])
        if self.clang_checked_files:
            lines.append(f"- Clang syntax check: {self.clang_passed_files}/{self.clang_checked_files} passed")
        lines.extend([
            "",
            "## Modules",
            "",
            "| Module | Template Dir | Status | Files | Unexpanded | #define Parity |",
            "|--------|--------------|--------|------:|-----------:|---------------:|",
        ])
        for m in self.module_results:
            dp = f"{m.define_match_total}/{m.define_ref_total}" if m.define_ref_total else "-"
            lines.append(
                f"| {m.module_name} | {m.template_dir_name} | {m.status} | {m.generated_count} | {len(m.unexpanded_files)} | {dp} |"
            )
        if self.clang_failures:
            lines.extend(["", "## Clang Syntax Failures", ""])
            for fn, err in self.clang_failures:
                lines.append(f"- `{fn}`: {err}")
        lines.append("")
        return "\n".join(lines)


def _collect_ref_gendata(ref_dir: Path) -> Dict[str, Path]:
    refs: Dict[str, Path] = {}
    if not ref_dir.is_dir():
        return refs
    for p in sorted(ref_dir.rglob("*"), key=lambda x: x.as_posix()):
        if not p.is_file():
            continue
        if p.name == ".DS_Store" or p.name.endswith((".bak", ".1")):
            continue
        rel = p.relative_to(ref_dir).as_posix()
        if any(rel.startswith(f"{ex}/") for ex in _EXCLUDED_REF_DIRS):
            continue
        refs[p.name] = p
    return refs


def _run_clang_on_c_files(
    gen_by_name: Dict[str, Tuple[str, Path]],
    out_root: Path,
    *,
    clang_target: Optional[str] = None,
    extra_include_dirs: Sequence[Path] = (),
) -> Dict[str, Tuple[bool, str]]:
    clang_bin = shutil.which("clang")
    results: Dict[str, Tuple[bool, str]] = {}
    if not clang_bin:
        return results

    inc_dirs: List[Path] = []
    for p in sorted(out_root.rglob("*"), key=lambda x: x.as_posix()):
        if p.is_dir() and p.name in ("include", "Components"):
            inc_dirs.append(p)
    inc_flags: List[str] = []
    seen_inc: Set[Path] = set()
    for d in inc_dirs + [Path(x) for x in extra_include_dirs]:
        res = d.resolve()
        if res.is_dir() and res not in seen_inc:
            seen_inc.add(res)
            inc_flags.append(f"-I{res}")

    base_cmd = [clang_bin, "-fsyntax-only"]
    if clang_target:
        base_cmd.extend(["--target", clang_target])
    base_cmd.extend(inc_flags)

    for fname, (_mod, cpath) in sorted(gen_by_name.items()):
        if cpath.suffix.lower() != ".c":
            continue
        proc = subprocess.run(base_cmd + [str(cpath)], capture_output=True, text=True)
        if proc.returncode == 0:
            results[fname] = (True, "")
        else:
            first_err = next((l.strip() for l in proc.stderr.splitlines() if "error:" in l), "")
            if not first_err:
                first_err = (proc.stderr.splitlines() or ["clang failed"])[0].strip()
            results[fname] = (False, first_err)
    return results


def audit_project_templates(
    dpa_path: Path,
    *,
    ref_gendata_dir: Optional[Path] = None,
    template_pack_dir: Optional[Path] = None,
    include_platform_gen: bool = True,
    include_rte_phase2_3: bool = True,
    run_clang: bool = False,
    clang_target: Optional[str] = None,
    extra_include_dirs: Sequence[Path] = (),
) -> TemplateAuditReport:
    """Load ``dpa_path`` read-only, dry-run generation, and audit templates/outputs."""
    dpa = Path(dpa_path)
    proj, _warnings = WorkspaceManager().load_project(dpa)
    pack_dir = Path(template_pack_dir) if template_pack_dir is not None else None
    report = TemplateAuditReport(
        project_name=getattr(proj, "name", dpa.stem),
        dpa_path=str(dpa),
        total_loaded_modules=len(getattr(proj, "module_managers", {}) or {}),
    )

    ref_files = _collect_ref_gendata(Path(ref_gendata_dir)) if ref_gendata_dir else {}
    if ref_gendata_dir:
        report.ref_gendata_dir = str(ref_gendata_dir)
        report.ref_total_files = len(ref_files)

    all_cfgs = {
        k: (m.module_def, m.configuration)
        for k, m in (proj.module_managers or {}).items()
        if m.configuration is not None
    }
    proj_root = project_paths.project_root(proj)

    with tempfile.TemporaryDirectory() as td:
        out_root = Path(td)
        gen_by_name: Dict[str, Tuple[str, Path]] = {}
        mod_file_paths: Dict[str, List[Path]] = {}
        mod_status: Dict[str, Tuple[str, str, str]] = {}  # mod -> (tpl_dir_name, status, err)

        for mod_name, mgr in sorted((proj.module_managers or {}).items()):
            mod_out = out_root / mod_name
            tpl_dir_name = project_paths.package_dir_name(proj, mod_name) or mod_name

            if mod_name == "Rte":
                try:
                    rrep = RteSchMGenerator(proj, include_phase2_3=include_rte_phase2_3).generate(
                        out_root, flat=False
                    )
                    rfiles = sorted(p for p in (out_root / "Rte").rglob("*") if p.is_file()) if (out_root / "Rte").exists() else []
                    mod_file_paths[mod_name] = rfiles
                    for f in rfiles:
                        gen_by_name[f.name] = (mod_name, f)
                    st = "OK" if rrep.ok and rfiles else ("ERROR" if not rrep.ok else "SKIPPED")
                    mod_status[mod_name] = ("Rte", st, "; ".join(rrep.errors[:2]))
                except Exception as exc:
                    mod_file_paths[mod_name] = []
                    mod_status[mod_name] = ("Rte", "ERROR", f"{type(exc).__name__}: {exc}")
                continue

            try:
                if pack_dir is not None and (
                    (pack_dir / tpl_dir_name).is_dir() or (pack_dir / mod_name).is_dir()
                ):
                    overlay_root, pkg_tpl = pack_dir, None
                else:
                    overlay_root, pkg_tpl = project_paths.template_sources(proj, mod_name)
                gen = CodeGenerator(
                    mgr.module_def,
                    mgr.configuration,
                    project_template_dir=overlay_root,
                    package_template_dir=pkg_tpl,
                    all_configurations=all_cfgs,
                    ecu_resources=getattr(proj, "ecu_resources", None),
                    selected_chip=getattr(proj, "selected_chip", None),
                    project_root=proj_root,
                    package_dir_name=tpl_dir_name,
                )
                gen.generate_all(mod_out, force=True)
                files = sorted(p for p in mod_out.rglob("*") if p.is_file()) if mod_out.exists() else []
                mod_file_paths[mod_name] = files
                for f in files:
                    gen_by_name[f.name] = (mod_name, f)
                mod_status[mod_name] = (tpl_dir_name, "OK" if files else "SKIPPED", "")
            except Exception as exc:
                mod_file_paths[mod_name] = []
                mod_status[mod_name] = (tpl_dir_name, "ERROR", f"{type(exc).__name__}: {exc}")

        if include_platform_gen:
            plat_rep = generate_platform_artifacts(proj, out_root, flat=False, force=True)
            for p in plat_rep.generated_files:
                rel = p.relative_to(out_root)
                owner = rel.parts[0] if len(rel.parts) > 1 else ("vBRS" if p.name.startswith("Makefile") else "Platform")
                if owner not in mod_file_paths:
                    mod_file_paths[owner] = []
                if p not in mod_file_paths[owner]:
                    mod_file_paths[owner].append(p)
                gen_by_name[p.name] = (owner, p)

        clang_map: Dict[str, Tuple[bool, str]] = {}
        if run_clang:
            clang_map = _run_clang_on_c_files(
                gen_by_name,
                out_root,
                clang_target=clang_target,
                extra_include_dirs=extra_include_dirs,
            )
            report.clang_checked_files = len(clang_map)
            report.clang_passed_files = sum(1 for ok, _e in clang_map.values() if ok)
            report.clang_failures = [(fn, err) for fn, (ok, err) in sorted(clang_map.items()) if not ok]

        # Analyze generated files per module
        for mod_name in sorted((proj.module_managers or {}).keys()):
            tpl_dir_name, st, err_msg = mod_status.get(mod_name, (mod_name, "SKIPPED", ""))
            files = sorted(mod_file_paths.get(mod_name, []), key=lambda x: x.name)
            mres = ModuleAuditResult(
                module_name=mod_name,
                template_dir_name=tpl_dir_name,
                status=st,
                generated_count=len(files),
                error_message=err_msg,
                generated_files=[str(f.relative_to(out_root)) for f in files],
            )
            for f in files:
                gtxt = f.read_text(encoding="utf-8", errors="ignore")
                has_unexp = "[!" in gtxt or "!]" in gtxt
                has_todo = "TODO" in gtxt or "placeholder" in gtxt.lower()
                if has_unexp:
                    mres.unexpanded_files.append(f.name)
                if has_todo:
                    mres.todo_files.append(f.name)

                rp = ref_files.get(f.name)
                d_match = d_total = s_match = s_total = ref_l = 0
                if rp is not None:
                    mres.matched_ref_count += 1
                    rtxt = rp.read_text(encoding="utf-8", errors="ignore")
                    ref_l = len(rtxt.splitlines())
                    gd, rd = set(_DEFINE_RE.findall(gtxt)), set(_DEFINE_RE.findall(rtxt))
                    gs, rs = set(_CSL_SYM_RE.findall(gtxt)), set(_CSL_SYM_RE.findall(rtxt))
                    d_match, d_total = len(gd & rd), len(rd)
                    s_match, s_total = len(gs & rs), len(rs)
                    mres.define_match_total += d_match
                    mres.define_ref_total += d_total
                    mres.sym_match_total += s_match
                    mres.sym_ref_total += s_total

                c_ok, c_err = clang_map.get(f.name, (None, ""))
                report.file_details.append(
                    FileParityDetail(
                        filename=f.name,
                        module_name=mod_name,
                        status="matched" if rp is not None else "extra",
                        gen_lines=len(gtxt.splitlines()),
                        ref_lines=ref_l,
                        define_match=d_match,
                        define_total=d_total,
                        sym_match=s_match,
                        sym_total=s_total,
                        unexpanded_tags=has_unexp,
                        has_todo=has_todo,
                        clang_ok=c_ok,
                        clang_error=c_err,
                    )
                )
            report.module_results.append(mres)

    report.ok_modules = sum(1 for m in report.module_results if m.status == "OK")
    report.skipped_modules = sum(1 for m in report.module_results if m.status == "SKIPPED")
    report.error_modules = sum(1 for m in report.module_results if m.status == "ERROR")
    report.total_generated_files = len(report.file_details)
    report.total_unexpanded_files = sum(1 for d in report.file_details if d.unexpanded_tags)

    if ref_files:
        gen_names = {d.filename for d in report.file_details}
        matched_names = [n for n in ref_files if n in gen_names]
        report.ref_matched_files = len(matched_names)
        report.ref_missing_files = sorted(n for n in ref_files if n not in gen_names)
        report.define_match_total = sum(m.define_match_total for m in report.module_results)
        report.define_ref_total = sum(m.define_ref_total for m in report.module_results)

    return report
