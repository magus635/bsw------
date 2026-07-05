#!/usr/bin/env python3
"""EPC 导出/导入回环验证工具。

对一个已导入的 .dpa 项目验证:
1. 语义回环: 全模块 export_epc -> 每个 EPC 用全新 manager 再导入 ->
   逐容器展平对比 (definition_ref / 单多值参数 / 单多值引用 / 层级路径)
2. 功能回环 (--codegen Os): 用导出的 EPC 整体替换该模块配置后重新生成代码,
   与原配置的生成结果 diff (忽略时间戳), 必须逐字节一致

用法:
    ./venv/bin/python tools/verify_epc_roundtrip.py                # 默认 MCAL_R440 项目
    ./venv/bin/python tools/verify_epc_roundtrip.py --dpa <path>   # 指定项目
    ./venv/bin/python tools/verify_epc_roundtrip.py --codegen Os   # 附加代码生成对比

退出码: 0 = 全部一致, 1 = 存在差异。
"""
import argparse
import logging
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.generator.generator import CodeGenerator

DEFAULT_DPA = Path(
    "/Users/qlwang/Desktop/🔴 Automotive_MCAL/ImportEB_1/MCAL_R440_FuSa/MCAL_R440_FuSa.dpa"
)


def snapshot(container, path=""):
    """把容器树展平为可比较的行 (路径 / 类型 / 名称 / 值)"""
    p = f"{path}/{container.short_name}"
    rows = [(p, "ctr", container.definition_ref)]
    for name, pv in sorted(container.parameter_values.items()):
        rows.append((p, "param", name, str(pv.value)))
    for name, plist in sorted(container.multi_parameter_values.items()):
        for pv in sorted(plist, key=lambda x: (x.index if x.index is not None else 0, str(x.value))):
            rows.append((p, "mparam", name, str(pv.value), pv.index))
    for name, rv in sorted(container.reference_values.items()):
        rows.append((p, "ref", name, rv.value_ref))
    for name, rlist in sorted(container.multi_reference_values.items()):
        for rv in sorted(rlist, key=lambda x: (x.index if x.index is not None else 0, str(x.value_ref))):
            rows.append((p, "mref", name, rv.value_ref, rv.index))
    for sub in container.sub_containers:
        rows.extend(snapshot(sub, p))
    return rows


def config_snapshot(config):
    rows = []
    for c in config.containers:
        rows.extend(snapshot(c))
    return sorted(map(repr, rows))


def semantic_roundtrip(project, wm, epc_dir):
    """全模块 export -> re-import -> 语义对比; 返回差异模块列表"""
    written = wm.export_epc(epc_dir)
    print(f"Exported {len(written)} EPC files -> {epc_dir}")

    bad = []
    for name, mgr in sorted(project.module_managers.items()):
        before = config_snapshot(mgr.configuration)

        fresh = ConfigurationManager(mgr.module_def, def_missing=mgr.def_missing)
        try:
            fresh.load_configuration(epc_dir / f"{name}.epc", skip_cleanup=mgr.def_missing)
        except Exception as e:
            bad.append((name, f"re-import failed: {e}"))
            continue

        after = config_snapshot(fresh.configuration)
        if before != after:
            b, a = set(before), set(after)
            bad.append((name, f"{len(b - a)} rows lost, {len(a - b)} rows gained"))
            for r in sorted(b - a)[:3]:
                print(f"  [{name}] LOST:   {r[:150]}")
            for r in sorted(a - b)[:3]:
                print(f"  [{name}] GAINED: {r[:150]}")

    n_ok = len(project.module_managers) - len(bad)
    print(f"Semantic round-trip: {n_ok} identical, {len(bad)} differ")
    for name, msg in bad:
        print(f"  DIFF {name}: {msg}")
    return bad


def codegen_roundtrip(dpa, module, epc_dir, work_dir):
    """替换模块配置为导出的 EPC 后重新生成, diff 代码输出 (忽略时间戳)"""
    template_dir = dpa.parent / "templates" / module

    def generate(project, out):
        mgr = project.module_managers[module]
        all_cfgs = {n: (m.module_def, m.configuration) for n, m in project.module_managers.items()}
        gen = CodeGenerator(
            mgr.module_def, mgr.configuration,
            project_template_dir=template_dir,
            all_configurations=all_cfgs,
            selected_chip=project.selected_chip,
            ecu_resources=project.ecu_resources,
        )
        gen.generate_all(out, variant="Default")

    # 生成前后各用独立加载的项目, 避免状态串扰
    project, _ = WorkspaceManager().load_project(dpa)
    generate(project, work_dir / "gen_before")

    project2, _ = WorkspaceManager().load_project(dpa)
    project2.module_managers[module].load_configuration(epc_dir / f"{module}.epc")
    project2.resolve_all_references()
    generate(project2, work_dir / "gen_after")

    r = subprocess.run(
        ["diff", "-r", "-I", "Genaration Time",
         str(work_dir / "gen_before"), str(work_dir / "gen_after")],
        capture_output=True, text=True,
    )
    status = "IDENTICAL" if r.returncode == 0 else "DIFFERS"
    print(f"Codegen round-trip ({module}), ignoring timestamps: {status}")
    if r.returncode:
        print(r.stdout[:3000])
    return r.returncode != 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dpa", type=Path, default=DEFAULT_DPA, help="项目 .dpa 文件路径")
    ap.add_argument("--codegen", metavar="MODULE", default=None,
                    help="附加: 用导出的 EPC 替换该模块后重新生成代码并对比 (如 Os)")
    ap.add_argument("--keep", action="store_true", help="保留临时输出目录")
    args = ap.parse_args()

    logging.basicConfig(level=logging.ERROR)  # 静默 unknown-parameter 等已知警告

    if not args.dpa.exists():
        print(f"ERROR: dpa not found: {args.dpa}")
        return 1

    work_dir = Path(tempfile.mkdtemp(prefix="epc_roundtrip_"))
    try:
        wm = WorkspaceManager()
        project, failed = wm.load_project(args.dpa)
        print(f"Loaded {len(project.module_managers)} modules from {args.dpa.name}"
              + (f" ({len(failed)} failed)" if failed else ""))

        bad = semantic_roundtrip(project, wm, work_dir / "epc")

        codegen_diff = False
        if args.codegen:
            codegen_diff = codegen_roundtrip(args.dpa, args.codegen, work_dir / "epc", work_dir)

        return 1 if (bad or codegen_diff) else 0
    finally:
        if args.keep:
            print(f"Outputs kept at: {work_dir}")
        else:
            shutil.rmtree(work_dir, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
