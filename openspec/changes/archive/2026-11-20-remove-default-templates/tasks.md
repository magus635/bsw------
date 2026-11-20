# Tasks

## 1. Generator core

- [x] 1.1 Remove `DEFAULT_TEMPLATE_DIR` scan from `_discover_template_types()` (attribute deleted; `_load_template_with_path` shares the same discovery so it is covered too)
- [x] 1.2 Remove the `Cfg.h`/`PBcfg.c` string-fallback block, the three `_get_*_template()` methods, and the flat-emit special case in `generate_all()`
- [x] 1.3 `generate_all()`: `last_status` attribute ('generated'|'skipped'|'failed'); empty discovery → warning listing searched directories, no output directory created, returns False with last_status='skipped'

## 2. UI surfacing

- [x] 2.1 `generation_controller.py`: single-module path shows a "skipped (no templates)" warning dialog with searched paths; project-wide path reports SKIP with "no templates found" detail in the summary stats

## 3. Templates relocation

- [x] 3.1 `git mv autosar_configurator/generator/templates tests/fixtures/templates`
- [x] 3.2 No remaining references to `DEFAULT_TEMPLATE_DIR`/fallback methods; `test_can_template.py` repointed to the fixture path

## 4. Tests & verification

- [x] 4.1 Rewrote generator tests to pass explicit `project_template_dir` (templates written per-test)
- [x] 4.2 Added tests: module with no templates → skipped status, no files; template dir without the module's subdir → skipped
- [x] 4.3 Full suite: 418 passed, 2 skipped
- [x] 4.4 MCAL_R440 oracle regression: 3018 diff lines == baseline exactly (EB-imported projects use their own copied generate_PB templates, unaffected)
