#!/usr/bin/env python3
"""
diff-driven auto-fix 系统的统一入口。

用法:
    python3 tools/run.py diff --module Os \
        --ref /path/to/reference/Os \
        --gen /path/to/generated/Os \
        [--json]

    python3 tools/run.py diff --module Os   # 使用默认路径（从 CLAUDE.md 约定的测试路径）
"""

import argparse
import sys
from pathlib import Path

# 让 tools/ 下的模块可以 import autosar_configurator
ROOT = Path(__file__).parent.parent
sys.path.insert(0, str(ROOT))

# --- 默认路径（对应 CLAUDE.md 中的测试项目） ---
DEFAULT_GENERATED = (
    "/Users/qlwang/Desktop/ImportEB_1"
    "/MCAL_R440_FuSa/generateCode/Os/Default/Os"
)
DEFAULT_REFERENCE = (
    "/Users/qlwang/Downloads/Os_Configuration/output/Os"
)


def cmd_diff(args: argparse.Namespace) -> int:
    from tools.diff.analyzer import DiffAnalyzer

    ref  = args.ref  or DEFAULT_REFERENCE
    gen  = args.gen  or DEFAULT_GENERATED

    print(f"Analyzing module '{args.module}'")
    print(f"  Reference : {ref}")
    print(f"  Generated : {gen}")
    print()

    report = DiffAnalyzer(
        module=args.module,
        reference_root=ref,
        generated_root=gen,
    ).analyze()

    if args.json:
        print(report.to_json())
    else:
        print(report.summary())

    if args.output:
        out_path = Path(args.output)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        out_path.write_text(report.to_json(), encoding='utf-8')
        print(f"\nReport written to: {out_path}")

    return 0 if report.is_clean else 1


def main() -> None:
    parser = argparse.ArgumentParser(
        prog="tools/run.py",
        description="Diff-driven auto-fix system for AUTOSAR BSW generators",
    )
    sub = parser.add_subparsers(dest="command", required=True)

    # ---- diff subcommand ----
    p_diff = sub.add_parser("diff", help="Analyze differences between reference and generated code")
    p_diff.add_argument("--module", default="Os", help="BSW module name (default: Os)")
    p_diff.add_argument("--ref",    default=None,  help="Reference code root directory")
    p_diff.add_argument("--gen",    default=None,  help="Generated code root directory")
    p_diff.add_argument("--json",   action="store_true", help="Output as JSON")
    p_diff.add_argument("--output", default=None,  help="Write JSON report to this file")

    args = parser.parse_args()

    if args.command == "diff":
        sys.exit(cmd_diff(args))


if __name__ == "__main__":
    main()
