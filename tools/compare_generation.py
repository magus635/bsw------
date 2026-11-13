#!/usr/bin/env python3
"""Generate a project's code twice and compare the two results file by file.

Regression check for code generation (design 2026-11-09 §12 acceptance 5): an
existing project must generate byte-identical code before and after a change, apart
from the generation timestamp in the file headers.

Usage::

    # Generate <dpa> into OUT_A and into OUT_B, then compare.  Each generation runs
    # in its own subprocess with the code of --code-a / --code-b (default: the
    # repository this script lives in), so a git worktree of an older commit can be
    # compared against the current checkout:
    python tools/compare_generation.py <dpa> <out_A> <out_B> [--code-a DIR] [--code-b DIR]

    # The two halves on their own:
    python tools/compare_generation.py --generate-only <dpa> <out> [--code DIR]
    python tools/compare_generation.py --compare-only <out_A> <out_B>

Generation mirrors the UI's "generate whole project" batch path
(``GenerationController._generate_project_code``): the project is loaded with
``WorkspaceManager().load_project(dpa)`` (no confirm callback, so a format 8 project
does not apply a reconcile merge; format <= 7 never reconciles), and every module that
has a configuration is generated with ``CodeGenerator`` using the same arguments as the
UI worker -- ``all_configurations``, ``selected_chip``, ``ecu_resources`` from
``project.load_ecu_resources()``, the active variant and its overrides, and the
template sources of the checked-out code: ``project_paths.template_sources`` +
``project_root`` where that module exists, otherwise ``<dpa dir>/templates`` (the
behaviour before it existed).  Keyword arguments the loaded ``CodeGenerator`` does not
accept (``package_template_dir``, ``project_root`` on older commits) are left out.
Modules are generated one after another, in project order.

The project is only read: nothing is saved and nothing is written into the project
directory.  Output goes to the given directory, which must be new or empty so that
stale files cannot hide a missing one.  Next to the generated code the script writes
``_generation_status.json`` (module -> GEN/SKIP/FAIL, modules that failed to load);
it is compared like any generated file, so a status change counts as a difference.

Comparison: every file under both directories is compared byte for byte.  A file that
differs is still counted as equal when it has the same number of lines and every
differing line becomes identical after replacing the generation timestamp, i.e. the
text matched by ``TIMESTAMP_RE`` (``YYYY-MM-DD HH:MM:SS``, the format of the template
variable ``$datetime`` set in ``CodeGenerator._prepare_context``), with ``<TIMESTAMP>``.
The last line printed is ``N differences``; the exit status is 0 only for 0.

This script does not import PySide6.
"""
import argparse
import difflib
import inspect
import json
import os
import re
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional, Tuple

REPO_ROOT = Path(__file__).resolve().parent.parent
STATUS_FILE = "_generation_status.json"
# The only time-dependent text the generator writes: context['datetime'] =
# datetime.now().strftime("%Y-%m-%d %H:%M:%S") (templates print it as [!"$datetime"!]).
TIMESTAMP_RE = re.compile(rb"\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}")
EXCERPT_LINES = 20


# --------------------------------------------------------------------------- generate

def _template_sources(project, module: str, project_paths) -> Tuple[Optional[Path], Optional[Path], Optional[Path]]:
    """(overlay root, package template dir, project root) the UI passes for ``module``."""
    if project_paths is not None and hasattr(project_paths, "template_sources"):
        # generation_controller._template_sources (project.path is the .dpa)
        overlay, package = project_paths.template_sources(project, module)
        root = project_paths.project_root(project)
    else:
        # Before project_paths: <project dir>/templates, no package, no project root
        overlay, package, root = Path(project.path).parent / "templates", None, None
    if overlay is not None and not Path(overlay).exists():
        overlay = None
    return overlay, package, root


def generate(dpa: Path, out: Path, code_root: Path) -> int:
    """Generate every module of ``dpa`` into ``out`` with the code at ``code_root``."""
    import logging

    logging.basicConfig(level=logging.WARNING, stream=sys.stderr,
                        format="%(levelname)s %(name)s: %(message)s")
    sys.path.insert(0, str(code_root))

    import autosar_configurator
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    from autosar_configurator.core.model.configuration_model import override_layer
    from autosar_configurator.generator.generator import CodeGenerator
    try:
        from autosar_configurator.core import project_paths
    except ImportError:
        project_paths = None

    print(f"code:    {Path(autosar_configurator.__file__).resolve().parent}")
    print(f"project: {dpa}")
    print(f"output:  {out}")

    project, failed = WorkspaceManager().load_project(dpa)
    for name, reason in failed:
        print(f"  LOAD-FAILED {name}: {reason}")

    # GenerationController._get_all_project_configurations / _project_ecu_resources
    all_configs = {name: (mgr.module_def, mgr.configuration)
                   for name, mgr in project.module_managers.items()
                   if mgr.module_def and mgr.configuration}
    try:
        resources = project.load_ecu_resources()
        ecu_resources = dict(resources) if resources else None
    except Exception as exc:  # noqa: BLE001 - the UI falls back to the generator's scan
        print(f"  ecu resources unavailable ({exc}); generator scans itself")
        ecu_resources = None

    variant_name = project.active_variant
    accepted = set(inspect.signature(CodeGenerator.__init__).parameters)
    out.mkdir(parents=True, exist_ok=True)

    statuses: Dict[str, str] = {}
    for name, manager in project.module_managers.items():
        if not manager.configuration:
            statuses[name] = "SKIP (no config)"
            print(f"  {name:12s} SKIP (no config)")
            continue
        overrides = {}
        if override_layer(variant_name):
            overrides = manager.configuration.variant_overrides.get(variant_name, {})
        overlay, package, root = _template_sources(project, name, project_paths)
        kwargs = dict(project_template_dir=overlay, package_template_dir=package,
                      variant_overrides=overrides, variant_name=variant_name,
                      all_configurations=all_configs, selected_chip=project.selected_chip,
                      ecu_resources=ecu_resources, project_root=root)
        kwargs = {k: v for k, v in kwargs.items() if k in accepted}
        try:
            generator = CodeGenerator(manager.module_def, manager.configuration, **kwargs)
            ok = generator.generate_all(out, force=False, variant=variant_name or "Default")
            if ok:
                status = "GEN"
            elif generator.last_status == "skipped":
                status = "SKIP (no templates)"
            else:
                status = "FAIL"
            detail = ""
        except Exception as exc:  # noqa: BLE001 - the UI worker reports and continues
            status, detail = "FAIL", f" {type(exc).__name__}: {exc}"
        statuses[name] = status
        print(f"  {name:12s} {status}{detail}")

    status_doc = {"load_failed": sorted(name for name, _ in failed),
                  "modules": dict(sorted(statuses.items()))}
    (out / STATUS_FILE).write_text(json.dumps(status_doc, indent=2, sort_keys=True) + "\n",
                                   encoding="utf-8")
    print(f"PySide6 imported: {'PySide6' in sys.modules}")
    return 0


# ---------------------------------------------------------------------------- compare

def _files(root: Path) -> Dict[str, Path]:
    return {p.relative_to(root).as_posix(): p for p in sorted(root.rglob("*")) if p.is_file()}


def _mask(line: bytes) -> bytes:
    return TIMESTAMP_RE.sub(b"<TIMESTAMP>", line)


def _equal_ignoring_timestamps(a: bytes, b: bytes) -> Tuple[bool, int]:
    """(equal apart from timestamps, number of lines that differed only by a timestamp)"""
    lines_a, lines_b = a.splitlines(keepends=True), b.splitlines(keepends=True)
    if len(lines_a) != len(lines_b):
        return False, 0
    masked = 0
    for la, lb in zip(lines_a, lines_b):
        if la == lb:
            continue
        if _mask(la) != _mask(lb):
            return False, 0
        masked += 1
    return True, masked


def _excerpt(a: bytes, b: bytes, name_a: str, name_b: str) -> List[str]:
    text_a = a.decode("utf-8", errors="replace").splitlines()
    text_b = b.decode("utf-8", errors="replace").splitlines()
    diff = list(difflib.unified_diff(text_a, text_b, name_a, name_b, lineterm="", n=1))
    if len(diff) > EXCERPT_LINES:
        diff = diff[:EXCERPT_LINES] + [f"... ({len(diff) - EXCERPT_LINES} more diff lines)"]
    return diff


def compare(out_a: Path, out_b: Path) -> int:
    """Print the differing files of ``out_a`` vs ``out_b``; return their number."""
    files_a, files_b = _files(out_a), _files(out_b)
    differences = 0
    identical = timestamp_only = masked_lines = 0
    print(f"A: {out_a} ({len(files_a)} files)")
    print(f"B: {out_b} ({len(files_b)} files)")
    for rel in sorted(set(files_a) | set(files_b)):
        if rel not in files_b:
            differences += 1
            print(f"ONLY IN A: {rel}")
            continue
        if rel not in files_a:
            differences += 1
            print(f"ONLY IN B: {rel}")
            continue
        data_a, data_b = files_a[rel].read_bytes(), files_b[rel].read_bytes()
        if data_a == data_b:
            identical += 1
            continue
        equal, masked = _equal_ignoring_timestamps(data_a, data_b)
        if equal:
            timestamp_only += 1
            masked_lines += masked
            continue
        differences += 1
        print(f"DIFFERS:   {rel}")
        for line in _excerpt(data_a, data_b, f"A/{rel}", f"B/{rel}"):
            print(f"    {line}")
    print(f"identical: {identical}, equal apart from timestamps: {timestamp_only} "
          f"({masked_lines} timestamp lines ignored)")
    print(f"{differences} differences")
    return differences


# -------------------------------------------------------------------------------- cli

def _check_output_dir(out: Path) -> None:
    if out.exists() and any(out.iterdir()):
        raise SystemExit(f"output directory is not empty: {out}")


def _run_generation(dpa: Path, out: Path, code_root: Path) -> None:
    cmd = [sys.executable, str(Path(__file__).resolve()), "--generate-only",
           str(dpa), str(out), "--code", str(code_root)]
    env = dict(os.environ, PYTHONIOENCODING="utf-8")
    result = subprocess.run(cmd, cwd=str(code_root), env=env)
    if result.returncode != 0:
        raise SystemExit(f"generation failed (exit {result.returncode}): {' '.join(cmd)}")


def main(argv: Optional[List[str]] = None) -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    parser = argparse.ArgumentParser(
        description="Generate a project twice and compare the outputs file by file.")
    parser.add_argument("paths", nargs="+", type=Path,
                        help="<dpa> <out_A> <out_B> | --generate-only <dpa> <out> | "
                             "--compare-only <out_A> <out_B>")
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--generate-only", action="store_true")
    mode.add_argument("--compare-only", action="store_true")
    parser.add_argument("--code", type=Path, default=REPO_ROOT,
                        help="code root for --generate-only (default: this repository)")
    parser.add_argument("--code-a", type=Path, default=REPO_ROOT,
                        help="code root that generates OUT_A (default: this repository)")
    parser.add_argument("--code-b", type=Path, default=REPO_ROOT,
                        help="code root that generates OUT_B (default: this repository)")
    args = parser.parse_args(argv)

    if args.generate_only:
        if len(args.paths) != 2:
            parser.error("--generate-only takes <dpa> <out>")
        dpa, out = (p.resolve() for p in args.paths)
        _check_output_dir(out)
        return generate(dpa, out, args.code.resolve())
    if args.compare_only:
        if len(args.paths) != 2:
            parser.error("--compare-only takes <out_A> <out_B>")
        return 1 if compare(*(p.resolve() for p in args.paths)) else 0
    if len(args.paths) != 3:
        parser.error("expected <dpa> <out_A> <out_B>")
    dpa, out_a, out_b = (p.resolve() for p in args.paths)
    _check_output_dir(out_a)
    _check_output_dir(out_b)
    _run_generation(dpa, out_a, args.code_a.resolve())
    _run_generation(dpa, out_b, args.code_b.resolve())
    return 1 if compare(out_a, out_b) else 0


if __name__ == "__main__":
    sys.exit(main())
