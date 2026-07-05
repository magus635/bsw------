# Remove Default Templates

## Why

The generator silently falls back to built-in templates (`generator/templates/`, see `generator.py:34,376`) and to hardcoded string fallbacks for `Cfg.h`/`PBcfg.c` (`generator.py:380-391`) when no project/user template is found. Built-in module templates (Adc, Mcu, Port, ...) almost never match the user's vendor/chip/define version, so the tool can generate plausible-looking but **wrong** code without any warning. Failing loudly is safer than silently generating incorrect output.

## What Changes

- **BREAKING**: Remove `DEFAULT_TEMPLATE_DIR` from the template search path in `CodeGenerator._discover_template_types()` and `_load_template_with_path()`. Only `project_template_dir` and `user_template_dir` are searched.
- **BREAKING**: Remove the hardcoded string fallback entries for `Cfg.h` and `PBcfg.c` (the `original_path=None` mechanism). Modules with no discovered template generate **no files** (this includes modules like EcuC that previously relied on the fallback — confirmed with the user).
- When a module has no templates, generation reports an explicit, user-visible warning: "No templates found for module X — skipped", and `generate_all()` returns a distinct "skipped" status (not silent success, not failure).
- Relocate `autosar_configurator/generator/templates/` contents to `tests/fixtures/templates/` so existing generator unit tests keep working with an explicit template dir.
- Update fingerprint/regression tests that depended on fallback output.

## Impact

- Affected specs: `code-generation` (new capability spec)
- Affected code:
  - `autosar_configurator/generator/generator.py` (template discovery, fallback removal, skip reporting)
  - `autosar_configurator/ui/controllers/generation_controller.py` (surface skip warnings in UI)
  - `autosar_configurator/generator/templates/` → moved to `tests/fixtures/templates/`
  - `tests/generator/` (fixture paths, fingerprint tests)
- Migration: users relying on built-in templates must provide a project or user template directory. EB-imported projects are unaffected as long as `generate_PB` template copying succeeded; a copy failure now surfaces as "module skipped" instead of silently degraded output.
