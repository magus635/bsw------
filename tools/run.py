#!/usr/bin/env python3
"""
diff-driven auto-fix 系统的统一入口。

用法:
    # 差异分析
    python3 tools/run.py diff --module Os
    python3 tools/run.py diff --module Os --output /tmp/os_diff.json

    # 带 trace 的代码生成（用于 Agent 2 溯源）
    python3 tools/run.py trace
    python3 tools/run.py trace --output /tmp/os_trace.json --fns node_ref,_find_context_loop_index

    # 修复建议生成（根据 trace + diff 输出引擎修复方案）
    python3 tools/run.py fix --trace /tmp/os_trace.json
    python3 tools/run.py fix --trace /tmp/os_trace.json --diff /tmp/os_diff.json --output /tmp/fixes.json
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
DPA_PATH     = "/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa"
TEMPLATE_DIR = "/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/templates/Os"
GEN_OUT_DIR  = "/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/generateCode/Os/Default"


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


def cmd_trace(args: argparse.Namespace) -> int:
    """运行带 trace hook 的代码生成，输出执行轨迹 + source map。"""
    from tools.trace.eval_tracer import Tracer
    from tools.trace.source_map import SourceMapTracer

    # 1. 安装类级 patch（只做一次）
    Tracer.install()
    SourceMapTracer.install()

    Tracer.enable()
    SourceMapTracer.enable()

    # 2. 触发 OS 代码生成（复用 gen_os.py 逻辑）
    print("[Trace] Running code generation with tracing + source map enabled...")
    from pathlib import Path as _Path
    from autosar_configurator.core.workspace_manager import WorkspaceManager
    from autosar_configurator.generator.generator import CodeGenerator

    dpa_path = _Path(args.dpa)
    workspace = WorkspaceManager()
    project, _ = workspace.load_project(dpa_path)

    os_mgr   = project.get_manager(args.module)
    all_cfgs = {
        mgr.module_def.short_name: (mgr.module_def, mgr.configuration)
        for mgr in project.get_all_managers()
    }

    gen = CodeGenerator(
        module_def=os_mgr.module_def,
        configuration=os_mgr.configuration,
        project_template_dir=_Path(args.template_dir),
        all_configurations=all_cfgs,
    )

    out_dir = _Path(args.out_dir)
    gen.generate_all(out_dir)
    Tracer.disable()
    SourceMapTracer.disable()

    # 3. 打印摘要
    print()
    print(Tracer.summary())
    print()
    print(SourceMapTracer.summary())

    # 4. 过滤 trace events（如果指定了 --fns）
    events = Tracer.events()
    if args.fns:
        wanted = {fn.strip() for fn in args.fns.split(',')}
        events = [e for e in events if e.fn in wanted]
        print(f"\n[Trace] Filtered to {len(events)} events for fns: {wanted}")

    # 5. 写入 trace 文件
    if args.output:
        out_path = _Path(args.output)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        import json as _json
        out_path.write_text(
            _json.dumps([e.to_dict() for e in events], indent=2, ensure_ascii=False),
            encoding='utf-8',
        )
        print(f"[Trace] Written to {out_path}")

    # 6. 写入 source map 文件
    if args.source_map:
        SourceMapTracer.dump_json(args.source_map)

    return 0


def cmd_fix(args: argparse.Namespace) -> int:
    """根据 trace + diff + source_map JSON 生成引擎修复建议。"""
    from tools.fix.fix_generator import FixGenerator

    print(f"[Fix] Generating fix suggestions...")
    print(f"  Trace      : {args.trace}")
    print(f"  Diff       : {args.diff or '(none)'}")
    print(f"  Source Map  : {args.source_map or '(none)'}")
    print()

    gen = FixGenerator(
        trace_path=args.trace,
        diff_path=args.diff or "",
        source_map_path=args.source_map or "",
    )
    report = gen.generate()

    print()
    print(report.summary())

    if args.output:
        report.dump(args.output)
    elif args.json:
        print(report.to_json())

    return 0


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

    # ---- trace subcommand ----
    p_trace = sub.add_parser("trace", help="Run code generation with engine trace hooks")
    p_trace.add_argument("--module",       default="Os",
                         help="BSW module name (default: Os)")
    p_trace.add_argument("--dpa",          default=DPA_PATH,
                         help="Path to .dpa project file")
    p_trace.add_argument("--template-dir", default=TEMPLATE_DIR, dest="template_dir",
                         help="Template directory for the module")
    p_trace.add_argument("--out-dir",      default=GEN_OUT_DIR,  dest="out_dir",
                         help="Output directory for generated code")
    p_trace.add_argument("--fns",          default=None,
                         help="Comma-separated function names to include (default: all). "
                              "E.g. node_ref,_find_context_loop_index")
    p_trace.add_argument("--output",       default=None,
                         help="Write trace JSON to this file")
    p_trace.add_argument("--source-map",   default=None, dest="source_map",
                         help="Write source map JSON to this file")

    # ---- fix subcommand ----
    p_fix = sub.add_parser("fix", help="Generate engine fix suggestions from trace & diff")
    p_fix.add_argument("--trace",  required=True,
                       help="Path to trace JSON (from 'run.py trace --output')")
    p_fix.add_argument("--diff",   default=None,
                       help="Path to diff JSON (from 'run.py diff --output'), optional")
    p_fix.add_argument("--source-map", default=None, dest="source_map",
                       help="Path to source map JSON (from 'run.py trace --source-map'), optional")
    p_fix.add_argument("--json",   action="store_true", help="Output as JSON to stdout")
    p_fix.add_argument("--output", default=None,
                       help="Write fix suggestions JSON to this file")

    args = parser.parse_args()

    if args.command == "diff":
        sys.exit(cmd_diff(args))
    elif args.command == "trace":
        sys.exit(cmd_trace(args))
    elif args.command == "fix":
        sys.exit(cmd_fix(args))


if __name__ == "__main__":
    main()
