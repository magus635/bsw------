# Tasks

## 1. Data model & persistence

- [x] 1.1 `WorkspaceProject`: `import_mode` ('copy'|'link') + `module_provenance` (origin / source_epc / imported_at)
- [x] 1.2 `save_project()`: format_version 7, relative `eb_source_root` (when inside project root), `import_mode`, per-module provenance
- [x] 1.3 `load_project()`: accepts versions ≤7; missing provenance defaults to `origin: "native"`, missing mode to "copy"; `eb_source_root` resolved relative-first

## 2. Import flow

- [x] 2.1 `import_eb_project(mode=)`: copy mode unchanged; link mode creates ONE symlink `Def/plugins` → source plugins dir (all downstream code — def loading, resource scan, chip discovery — works unchanged through the link) and skips all copying
- [x] 2.2 `source_epc` (relative to EB source root) and `imported_at` recorded per module during import
- [x] 2.3 Link mode load: missing `eb_source_root` → single clear "EB source tree not found" error; if `TRESOS_PLUGINS_PATH` is set and exists, the broken `Def/plugins` symlink is repaired to point there
- [x] 2.4 Template handling per mode: link mode symlinks `templates/{Module}` → plugin `generate_PB` at import time and never copies; copy mode copies from the project-local plugin tree at save (one copy from the source, materialized locally)

## 3. UI

- [x] 3.1 EB import dialog asks Copy/Link with one-line trade-off descriptions (default Copy); import summary shows the mode

## 4. Cleanup

- [x] 4.1 `_resolve_path()` Windows-anchor heuristics documented as legacy-only fallback (v7 projects store relative paths and never hit it)

## 5. Tests & verification

- [x] 5.1 Round-trip tests both modes: import → save → load → module set + provenance intact (tests/core/test_eb_import_modes.py)
- [x] 5.2 Migration tests: v6 loads and re-saves as valid v7; format_version 8 rejected
- [x] 5.3 Relocation test: copy-mode project moved to a new directory loads fully; link-mode missing source fails with the clear error
- [x] 5.4 Full suite 426 passed / 2 skipped; MCAL_R440 oracle regression unchanged (3018 == baseline, v6 reference .dpa loads through the v7 code path)
