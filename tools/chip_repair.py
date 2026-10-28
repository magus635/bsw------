"""Repair an existing chip of the chip library from vendor .properties files (add-chip-repair-core).

    python -m tools.chip_repair diff  <chip> [file.properties ...] [--scan-dir DIR ...]
    python -m tools.chip_repair apply <chip> [file.properties ...] [--scan-dir DIR ...]
            (--keys K1,K2 | --all-added --all-changed [--include-removed])
            --source TEXT [--note TEXT] [--version V] [--confirm FIELD=NOTE ...]

``diff`` prints the ECU resource changes and writes nothing.  ``apply`` merges the
selected changes, synchronizes the views, confirms the given unconfirmed fields
and saves the chip with a backup and a repair history entry.  Removals are applied
only with ``--include-removed`` (or when named in ``--keys``).

Exit codes: 0 done, 1 invalid arguments or the chip file changed, 2 nothing to change.
"""
import argparse
import copy
import sys
from pathlib import Path

if __package__ in (None, ""):       # run as a script: make the repository importable
    sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from autosar_configurator.core.hardware import chip_repair as repair  # noqa: E402
from autosar_configurator.core.hardware.chip_database import ChipDatabase, default_chips_dir  # noqa: E402
from autosar_configurator.core.hardware.ecu_resource_diagnostics import (  # noqa: E402
    collect_referenced_keys_in_dirs,
)

EXIT_OK, EXIT_ERROR, EXIT_NOTHING = 0, 1, 2
_MAX_VALUE_TEXT = 80


def _short(value) -> str:
    if value is repair.PLACEHOLDER:
        return "（待填写）"
    text = repr(value)
    return text if len(text) <= _MAX_VALUE_TEXT else text[:_MAX_VALUE_TEXT - 3] + "..."


def _print_diff(diff: repair.EcuDiff) -> None:
    for c in diff.changes:
        if c.kind == repair.ADDED:
            print(f"+ {c.key} = {_short(c.new)}")
        elif c.kind == repair.REMOVED:
            print(f"- {c.key} = {_short(c.old)}")
        else:
            note = "  (仅类型不同)" if c.type_only else ""
            print(f"~ {c.key}: {_short(c.old)} -> {_short(c.new)}{note}")
    counts = {k: len(diff.keys(k)) for k in (repair.ADDED, repair.CHANGED, repair.REMOVED)}
    print(f"新增 {counts['added']}，变化 {counts['changed']}，删除 {counts['removed']}")


def _difference(chip, args) -> repair.EcuDiff:
    """Changes from the .properties files (whole ECU resources) plus keys missing for the scanned modules."""
    changes = {}
    if args.properties:
        source = repair.ecu_resources_from_properties([Path(p) for p in args.properties])
        for c in repair.diff_from_source(chip.ecu_resources, source).changes:
            changes[c.key] = c
    if args.scan_dir:
        referenced = collect_referenced_keys_in_dirs([Path(d) for d in args.scan_dir])
        for c in repair.missing_key_changes(chip, referenced).changes:
            changes.setdefault(c.key, c)
    return repair.EcuDiff([changes[k] for k in sorted(changes)])


def _selected(diff: repair.EcuDiff, args):
    if args.keys:
        return [k.strip() for k in args.keys.split(",") if k.strip()]
    kinds = [kind for kind, wanted in ((repair.ADDED, args.all_added), (repair.CHANGED, args.all_changed),
                                       (repair.REMOVED, args.include_removed)) if wanted]
    return diff.keys(*kinds) if kinds else []


def _confirmations(items):
    notes = {}
    for item in items or []:
        field_path, sep, note = item.partition("=")
        if not sep or not field_path.strip():
            raise ValueError(f"--confirm expects FIELD=NOTE, got '{item}'")
        notes[field_path.strip()] = note.strip()
    return notes


def _apply(database, base, args) -> int:
    diff = _difference(base, args)
    selected = _selected(diff, args)
    confirm_notes = _confirmations(args.confirm)
    if not diff and not confirm_notes:
        print(f"{base.name} 与来源没有差异")
        return EXIT_NOTHING
    if not selected and not confirm_notes:
        print("没有选中任何改动（用 --keys、--all-added、--all-changed、--include-removed 或 --confirm）")
        return EXIT_NOTHING

    chip = repair.apply_changes(base, diff, selected)
    chip, views = repair.derive_views(chip)
    if confirm_notes:
        chip = repair.confirm_fields(chip, confirm_notes)
    record = repair.RepairRecord(source=args.source, note=args.note or "", version=args.version or "",
                                 views=views, confirm_notes=confirm_notes)
    result = repair.save_repaired_chip(database, chip, base, record)
    if not result.saved:
        print(f"{base.name} 没有变化，未保存")
        return EXIT_NOTHING
    applied = repair.diff_ecu_resources(base.ecu_resources, chip.ecu_resources)
    _print_diff(applied)
    for v in views:
        print(f"视图 {v.view}: {repair.view_text(v)}")
    print(f"已保存 {result.path}（resource_version {base.resource_version or '-'} -> {result.version}）")
    print(f"备份 {result.backup}；修改记录 {result.history}")
    return EXIT_OK


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(prog="python -m tools.chip_repair", description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("diff", "apply"):
        p = sub.add_parser(name)
        p.add_argument("chip", help="chip name in the library")
        p.add_argument("properties", nargs="*", help="vendor .properties files (later ones win)")
        p.add_argument("--scan-dir", action="append", help="plugin directory whose referenced keys must exist")
        p.add_argument("--chips-dir", help="chip library directory (default: the built-in data/chips)")
        if name == "apply":
            p.add_argument("--keys", help="comma separated flat keys to apply")
            p.add_argument("--all-added", action="store_true")
            p.add_argument("--all-changed", action="store_true")
            p.add_argument("--include-removed", action="store_true")
            p.add_argument("--source", required=True, help="where the data comes from, for the history")
            p.add_argument("--note")
            p.add_argument("--version", help="new resource_version (default: last part + 1)")
            p.add_argument("--confirm", action="append", metavar="FIELD=NOTE",
                           help="remove the unconfirmed mark of FIELD, recording NOTE")
    args = parser.parse_args(argv)
    if not args.properties and not args.scan_dir and not getattr(args, "confirm", None):
        parser.error("give .properties files, --scan-dir or --confirm")

    database = ChipDatabase(Path(args.chips_dir) if args.chips_dir else default_chips_dir())
    base = database.get_chip(args.chip)
    if base is None:
        print(f"芯片库中没有 {args.chip}", file=sys.stderr)
        return EXIT_ERROR
    base = copy.deepcopy(base)
    if base.content_modified:
        print(f"注意：{args.chip} 的文件在芯片设计器之外被修改过", file=sys.stderr)

    try:
        if args.command == "diff":
            diff = _difference(base, args)
            if not diff:
                print(f"{args.chip} 与来源没有差异")
                return EXIT_NOTHING
            _print_diff(diff)
            return EXIT_OK
        return _apply(database, base, args)
    except (ValueError, repair.ChipFileChanged) as e:
        print(f"错误：{e}", file=sys.stderr)
        return EXIT_ERROR


if __name__ == "__main__":
    sys.exit(main())
