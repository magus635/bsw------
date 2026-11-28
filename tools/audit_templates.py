#!/usr/bin/env python3
"""CLI tool to dry-run templates in a .dpa project and report coverage/parity/clang checks."""

import argparse
import json
from pathlib import Path
import sys

_REPO_ROOT = Path(__file__).resolve().parent.parent
if str(_REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(_REPO_ROOT))

from autosar_configurator.generator.template_audit import audit_project_templates


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description="Audit .dpa templates, platform generation, and GenData parity.")
    parser.add_argument("--dpa", type=Path, required=True, help="Path to target .dpa file (read-only)")
    parser.add_argument("--ref-gendata", type=Path, default=None, help="Optional reference GenData directory")
    parser.add_argument("--template-pack", type=Path, default=None, help="Optional repository template pack override dir")
    parser.add_argument("--no-platform-gen", action="store_true", help="Disable ComStack/MemMap/vBRS generators")
    parser.add_argument("--no-rte-phase23", action="store_true", help="Audit Phase 1 RTE only")
    parser.add_argument("--clang", action="store_true", help="Run clang -fsyntax-only on generated .c files")
    parser.add_argument("--target", type=str, default=None, help="Optional clang --target triple")
    parser.add_argument("--include", type=Path, action="append", default=[], help="Extra -I include directory")
    parser.add_argument("--json", type=Path, default=None, help="Write full JSON report to path")
    parser.add_argument("--md", type=Path, default=None, help="Write Markdown summary report to path")
    parser.add_argument("--fail-on-error", action="store_true", help="Exit 1 if any module errors or has unexpanded tags")
    args = parser.parse_args(argv)

    rep = audit_project_templates(
        args.dpa,
        ref_gendata_dir=args.ref_gendata,
        template_pack_dir=args.template_pack,
        include_platform_gen=not args.no_platform_gen,
        include_rte_phase2_3=not args.no_rte_phase23,
        run_clang=args.clang,
        clang_target=args.target,
        extra_include_dirs=args.include,
    )
    md_text = rep.to_markdown()
    print(md_text)

    if args.json is not None:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(rep.to_dict(), indent=2, ensure_ascii=False), encoding="utf-8")
    if args.md is not None:
        args.md.parent.mkdir(parents=True, exist_ok=True)
        args.md.write_text(md_text, encoding="utf-8")

    if args.fail_on_error and (rep.error_modules > 0 or rep.skipped_modules > 0 or rep.total_unexpanded_files > 0):
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
