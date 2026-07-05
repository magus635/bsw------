# Add EB Import Modes and Module Provenance to .dpa

## Why

`import_eb_project()` (`workspace_manager.py:858`) always copies entire EB plugin directories into `Def/plugins/` (large, duplicated with `_copy_eb_templates`), stores `eb_source_root` as an absolute path (breaks the all-paths-relative convention and project relocation), and records no per-module provenance — after the first save, the link between a module's config and its source EPC file is lost, making "re-sync from EB" impossible.

## What Changes

- Add an **import mode** choice to EB project import:
  - **Copy (self-contained)** — current behavior: plugins copied into `Def/plugins/`, `generate_PB` into `templates/`. Default.
  - **Link (reference original)** — no plugin copy; `def_path` and templates resolve against the original EB tree via `eb_source_root`, with `TRESOS_PLUGINS_PATH` as fallback. The .dpa records the mode.
- Store `eb_source_root` as a project-root-relative path when possible; keep absolute only when the source tree is outside the project (link mode), and validate it on load with a clear "EB source tree not found" error.
- Add per-module provenance to `.dpa` `modules[]`: `origin` (`native` | `eb-import`), `source_epc` (original EPC path, relative to `eb_source_root`), `imported_at` (ISO timestamp).
- Bump `.dpa` `format_version` to 7 with backward-compatible migration: v6 and older load normally; missing provenance fields default to `origin: "native"`.
- Simplify `_resolve_path()` Windows-anchor heuristics where the new relative `eb_source_root` makes them unnecessary (keep as last-resort fallback for legacy files).

## Impact

- Affected specs: `project-file` (new capability spec)
- Affected code:
  - `autosar_configurator/core/workspace_manager.py` (`import_eb_project`, `save_project`, `load_project`, `_copy_eb_templates`, `_resolve_path`)
  - `autosar_configurator/ui/controllers/project_controller.py` (import dialog: mode selection)
  - `tests/core/` (format v7 round-trip, migration from v6, link-mode load)
- Migration: existing v6 projects open unchanged; re-saving upgrades them to v7 with `origin: "native"` defaults (or `eb-import` when `eb_source_root` is present and the config file matches a known EPC name).
