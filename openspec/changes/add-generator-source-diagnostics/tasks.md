## 1. Error Model & Execution Context
- [x] 1.1 Define `TemplateExecutionError` in `generator/eb/errors.py`
- [x] 1.2 Track active execution token in `Renderer._execute_tokens` and wrap errors with file, line, col, and snippet
- [x] 1.3 Add tracking and aggregated summary for unimplemented functions in `BuiltinFunctions`

## 2. Generator Logging & Diagnostics
- [x] 2.1 Update `CodeGenerator._generate_single_file` to catch `TemplateExecutionError` and output structured line-level diagnostic logs
- [x] 2.2 Add unit test verifying that template runtime errors raise `TemplateExecutionError` with accurate file and line information

## 3. Verification & Validation
- [x] 3.1 Run `python -m pytest tests/generator -q`
- [x] 3.2 Run `openspec validate add-generator-source-diagnostics --strict`
