## ADDED Requirements

### Requirement: Template Execution Source Diagnostics
The EB template rendering engine SHALL associate runtime execution errors with the originating template filename, line number, column offset, and source directive snippet.

#### Scenario: Runtime error in template tag
- **WHEN** an evaluation error (such as undefined variable or syntax error) occurs inside a template tag
- **THEN** the renderer raises a `TemplateExecutionError` containing the template file path, 1-based line number, column offset, and offending tag snippet
- **AND** the generator logs a formatted diagnostic message indicating the exact source location

### Requirement: Unimplemented Builtin Function Warning
The template engine SHALL track any attempted calls to unsupported or unimplemented builtin functions during non-strict generation.

#### Scenario: Unrecognized function invocation in non-strict mode
- **WHEN** a template invokes a function that is not registered in `BuiltinFunctions` in non-strict mode
- **THEN** the function dispatcher records the function name and emits a warning identifying the unhandled function
