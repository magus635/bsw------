"""Manual check of the EB import (a script, not a pytest test: it has no test functions).

Imports an EB Tresos project into a fresh temporary directory, so nothing is written into
the EB tree or into this repository, and prints the failed modules and the report path.

Run from the repository root:

    python test_eb_import.py <EB project root> [chip folder] [--mode copy|link]

e.g. ``python test_eb_import.py /Users/qlwang/Desktop/ImportEB_1 MCAL_R440_FuSa``.
"""
import argparse
import sys
import tempfile
from pathlib import Path


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("eb_root", type=Path, help="root directory of the EB Tresos project")
    parser.add_argument("chip", nargs="?", default=None, help="chip / sub-project folder")
    parser.add_argument("--mode", choices=("copy", "link"), default="copy")
    args = parser.parse_args(argv)

    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    target = Path(tempfile.mkdtemp(prefix="eb_import_")) / args.eb_root.name
    manager = WorkspaceManager()
    project, loaded, failed = manager.import_eb_project(
        args.eb_root, args.chip, target_dir=target, mode=args.mode, progress_callback=print)

    print()
    print(f"Project: {project.path}")
    print(f"Report:  {manager.last_import_report}")
    print(f"Loaded:  {len(loaded)} module(s)")
    print()
    print("--- Failed Modules ---")
    for mod, err in failed:
        print(f"- {mod}: {err}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
