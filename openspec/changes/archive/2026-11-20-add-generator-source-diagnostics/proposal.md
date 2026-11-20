## Why

When rendering complex EB Tresos templates, syntax, evaluation, or XPath errors are frequently reported as raw Python exceptions without accurate template file names, line numbers, column offsets, or code snippets. This makes debugging template issues in large MCAL modules extremely difficult.

## What Changes

- Add `TemplateExecutionError` in `errors.py` with source file, line number, column offset, and snippet context.
- Update `Renderer` in `generator/eb/renderer.py` to track the active token during execution and wrap uncaught errors in `TemplateExecutionError`.
- Enhance `CodeGenerator` in `generator.py` to format template errors with exact line and column locations in logs and UI status.
- Add tracking for unhandled/unimplemented template functions in `BuiltinFunctions` to warn developers of silent fallbacks.

## Impact

- Affected specs: `code-generation`
- Affected code: `autosar_configurator/generator/eb/errors.py`, `autosar_configurator/generator/eb/renderer.py`, `autosar_configurator/generator/eb/builtins.py`, `autosar_configurator/generator/generator.py`
