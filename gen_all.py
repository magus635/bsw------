#!/usr/bin/env python3
"""
多模块代码生成 + 回归对比工具。

用法:
    # 生成并对比所有模块
    python3 gen_all.py

    # 只生成+对比指定模块
    python3 gen_all.py Uart Wdg Gpt

    # 只生成，不对比
    python3 gen_all.py --no-diff

    # 只对比，不重新生成（用已有的生成文件）
    python3 gen_all.py --diff-only

    # 输出详细差异
    python3 gen_all.py Uart --verbose
"""
import argparse
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

# === 路径配置 ===
DPA_PATH = Path("/Users/qlwang/Desktop/🔴 Automotive_MCAL/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa")
TEMPLATE_BASE = Path("/Users/qlwang/Desktop/🔴 Automotive_MCAL/ImportEB_1/MCAL_R440_FuSa/templates")
GEN_BASE = Path("/Users/qlwang/Desktop/🔴 Automotive_MCAL/ImportEB_1/MCAL_R440_FuSa/generateCode")
REF_BASE = Path("/Users/qlwang/Desktop/🔴 Automotive_MCAL/generateCode_标准文件")

# Os 使用独立的参考路径
OS_REF = Path("/Users/qlwang/Downloads/Os_Configuration/output/Os")

# 所有已知模块
ALL_MODULES = [
    "Adc", "Can", "Dio", "Dma", "Dsadc", "Eth", "Fee", "Fls",
    "Gpt", "I2c", "Icu", "Intc", "Iom", "Lin", "Mcu", "Msc",
    "Ocu", "Os", "Port", "Pwm", "Resource", "Sent", "Spi", "Uart", "Wdg",
]


def get_ref_dir(module: str) -> Path:
    """获取模块的标准参考目录"""
    if module == "Os":
        return OS_REF
    # 非 Os 模块: generateCode_标准文件/<Module>/Default/
    return REF_BASE / module / "Default"


def get_gen_dir(module: str) -> Path:
    """获取模块的生成代码目录"""
    if module == "Os":
        return GEN_BASE / "Os" / "Default" / "Os"
    # 非 Os 模块: generateCode/<Module>/Default/
    # generate_all 输出到 GEN_BASE/<Module>/<variant=Default>/ 下的 include/ 和 src/
    return GEN_BASE / module / "Default"


def get_template_dir(module: str) -> Path:
    """获取模块的模板目录"""
    if module == "Os":
        # Os 使用 templates/Os（有嵌套 Os/ 子目录）
        return TEMPLATE_BASE / "Os"
    # 其他模块使用 templates/ 基目录（generator 自动查找模块子目录）
    return TEMPLATE_BASE


def generate_module(module: str, project, all_cfgs) -> bool:
    """生成单个模块的代码"""
    mgr = project.get_manager(module)
    if not mgr:
        return False

    gen = CodeGenerator(
        module_def=mgr.module_def,
        configuration=mgr.configuration,
        project_template_dir=get_template_dir(module),
        all_configurations=all_cfgs,
        selected_chip=project.selected_chip,
        ecu_resources=project.ecu_resources,
    )

    # generate_all 自动创建 GEN_BASE/<module_name>/ 子目录
    if module == "Os":
        # Os 模板有嵌套 Os/Os/ 结构，generate_all 会自动加 module_name
        # 输出: GEN_BASE/Os/Default/Os/alarm/... (与标准一致)
        out_dir = GEN_BASE / module / "Default"
        gen.generate_all(out_dir)
    else:
        # 非 Os 模块: 传入 variant="Default" 使输出路径为 GEN_BASE/<module>/Default/include|src/
        # builtins.variant_size() 对 "Default" 返回 0（无实际 PB 变体）
        gen.generate_all(GEN_BASE, variant="Default")
    return True


def diff_module(module: str, verbose: bool = False) -> dict:
    """对比单个模块的生成代码与标准文件，返回差异统计"""
    ref_dir = get_ref_dir(module)
    gen_dir = get_gen_dir(module)

    if not ref_dir.exists():
        return {"status": "NO_REF", "message": f"参考目录不存在: {ref_dir}"}
    if not gen_dir.exists():
        return {"status": "NO_GEN", "message": f"生成目录不存在: {gen_dir}"}

    # 收集文件
    ref_files = {}
    for f in ref_dir.rglob("*"):
        if f.is_file() and f.suffix in ('.c', '.h', '.s', '.scat'):
            rel = f.relative_to(ref_dir)
            ref_files[str(rel)] = f

    gen_files = {}
    for f in gen_dir.rglob("*"):
        if f.is_file() and f.suffix in ('.c', '.h', '.s', '.scat'):
            rel = f.relative_to(gen_dir)
            gen_files[str(rel)] = f

    # 忽略 .meta 和 ORTI 文件
    missing = sorted(set(ref_files) - set(gen_files))
    extra = sorted(set(gen_files) - set(ref_files))
    common = sorted(set(ref_files) & set(gen_files))

    diff_lines = 0
    diff_files = []
    for rel in common:
        ref_text = ref_files[rel].read_text(encoding='utf-8', errors='replace')
        gen_text = gen_files[rel].read_text(encoding='utf-8', errors='replace')

        # 去除尾部空白再比较
        ref_clean = "\n".join(l.rstrip() for l in ref_text.splitlines())
        gen_clean = "\n".join(l.rstrip() for l in gen_text.splitlines())

        if ref_clean != gen_clean:
            # 统计差异行数
            import difflib
            diffs = list(difflib.unified_diff(
                ref_clean.splitlines(), gen_clean.splitlines(),
                lineterm='', n=0,
            ))
            n_diff = sum(1 for l in diffs if l.startswith('+') or l.startswith('-'))
            diff_lines += n_diff
            diff_files.append((rel, n_diff))

    return {
        "status": "OK" if not diff_files and not missing else "DIFF",
        "total_ref": len(ref_files),
        "total_gen": len(gen_files),
        "common": len(common),
        "missing": len(missing),
        "extra": len(extra),
        "diff_files": len(diff_files),
        "diff_lines": diff_lines,
        "details": diff_files if verbose else diff_files[:5],
        "missing_files": missing[:5],
    }


def main():
    parser = argparse.ArgumentParser(description="多模块代码生成+回归对比")
    parser.add_argument("modules", nargs="*", help="要处理的模块（默认全部）")
    parser.add_argument("--no-diff", action="store_true", help="只生成，不对比")
    parser.add_argument("--diff-only", action="store_true", help="只对比，不生成")
    parser.add_argument("--verbose", "-v", action="store_true", help="显示详细差异")
    args = parser.parse_args()

    modules = args.modules if args.modules else ALL_MODULES

    # 验证模块名
    for m in modules:
        if m not in ALL_MODULES:
            print(f"未知模块: {m}  (可用: {', '.join(ALL_MODULES)})")
            sys.exit(1)

    # 加载项目（只需一次）
    project = None
    all_cfgs = None
    if not args.diff_only:
        print("加载项目...")
        workspace = WorkspaceManager()
        project, failed = workspace.load_project(DPA_PATH)
        all_cfgs = {
            mgr.module_def.short_name: (mgr.module_def, mgr.configuration)
            for mgr in project.get_all_managers()
        }
        if failed:
            print(f"  警告: {len(failed)} 个模块加载失败")

    # 生成
    gen_results = {}
    if not args.diff_only:
        print(f"\n{'='*60}")
        print(f"生成 {len(modules)} 个模块...")
        print(f"{'='*60}")
        for m in modules:
            t0 = time.time()
            try:
                ok = generate_module(m, project, all_cfgs)
                elapsed = time.time() - t0
                gen_results[m] = "OK" if ok else "NO_MGR"
                status = "OK" if ok else "SKIP(no manager)"
                print(f"  {m:12s}  {status:20s}  {elapsed:.1f}s")
            except Exception as e:
                elapsed = time.time() - t0
                gen_results[m] = f"ERR: {e}"
                print(f"  {m:12s}  ERROR: {e}  {elapsed:.1f}s")

    # 对比
    if not args.no_diff:
        print(f"\n{'='*60}")
        print(f"对比 {len(modules)} 个模块...")
        print(f"{'='*60}")
        print(f"{'Module':12s} {'Files':>6s} {'Diff':>6s} {'Lines':>7s} {'Missing':>8s} {'Extra':>6s}  Status")
        print("-" * 70)

        total_diff_files = 0
        total_diff_lines = 0
        total_ok = 0

        for m in modules:
            r = diff_module(m, verbose=args.verbose)
            if r["status"] in ("NO_REF", "NO_GEN"):
                print(f"{m:12s} {'—':>6s} {'—':>6s} {'—':>7s} {'—':>8s} {'—':>6s}  {r['message']}")
                continue

            total_diff_files += r["diff_files"]
            total_diff_lines += r["diff_lines"]
            if r["diff_files"] == 0 and r["missing"] == 0:
                total_ok += 1

            status = "PASS" if r["diff_files"] == 0 and r["missing"] == 0 else "FAIL"
            print(
                f"{m:12s} {r['common']:>6d} {r['diff_files']:>6d} "
                f"{r['diff_lines']:>7d} {r['missing']:>8d} {r['extra']:>6d}  {status}"
            )

            if args.verbose and r.get("details"):
                for fname, nlines in r["details"]:
                    print(f"             ↳ {fname} ({nlines} diff lines)")
            if args.verbose and r.get("missing_files"):
                for fname in r["missing_files"]:
                    print(f"             ↳ MISSING: {fname}")

        print("-" * 70)
        print(f"{'TOTAL':12s} {'':>6s} {total_diff_files:>6d} {total_diff_lines:>7d}")
        print(f"  PASS: {total_ok}/{len(modules)}")


if __name__ == "__main__":
    main()
