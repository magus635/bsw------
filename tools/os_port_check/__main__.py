"""python -m tools.os_port_check <command> ...   (run from the repository root; see README.md)"""
import argparse
import sys
from pathlib import Path

from . import common, r52, sc300


def _paths(args):
    kernel = common.directory(args.kernel, "OS_KERNEL_DIR", "kernel Os directory")
    t1 = common.directory(args.t1, "OS_T1_DIR", "T1 project directory")
    return kernel, t1


def _sdk(args, kernel: Path) -> Path:
    return common.directory(args.sdk or str(kernel.parent / "SDK"), "OS_R52_SDK_DIR", "R52 SDK directory")


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(prog="python -m tools.os_port_check", description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    for name, text in (("sc300", "build the SC300 example, link it with the kernel and run it on QEMU"),
                       ("r52-save", "build the kernel for the Cortex-R52 and save the objects"),
                       ("r52-compare", "build the kernel for the Cortex-R52 and compare with saved objects")):
        p = sub.add_parser(name, help=text)
        p.add_argument("--kernel", help="the kernel's Os directory (or OS_KERNEL_DIR)")
        p.add_argument("--t1", help="the T1 project directory (or OS_T1_DIR)")
        if name == "sc300":
            p.add_argument("--work", help="keep the generated code, objects and image here")
            p.add_argument("--warn", action="store_true", help="show compiler warnings")
        else:
            p.add_argument("--sdk", help="SDK directory for the R52 (default: <kernel>/../SDK, or OS_R52_SDK_DIR)")
            p.add_argument("--objects", required=True,
                           help="directory the objects are saved to / compared with")
    args = parser.parse_args(argv)

    try:
        kernel, t1 = _paths(args)
        if args.command == "sc300":
            ok, output = sc300.check(kernel, t1, Path(args.work) if args.work else None, args.warn)
            print(output)
            return 0 if ok else 1
        sdk = _sdk(args, kernel)
        objects = Path(args.objects)
        if args.command == "r52-save":
            failures = r52.build(kernel, t1, sdk, objects)
            print("\n".join(failures) if failures else f"saved {len(list(objects.glob('*.o')))} objects to {objects}")
            return 1 if failures else 0
        current = objects.parent / (objects.name + "_current")
        failures = r52.build(kernel, t1, sdk, current)
        if failures:
            print("build failed:\n  " + "\n  ".join(failures))
            return 1
        problems = common.compare_objects(objects, current)
        print("\n".join(problems) if problems else f"identical: {len(list(current.glob('*.o')))} objects")
        return 1 if problems else 0
    except common.CheckError as e:
        print(f"setup problem: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
