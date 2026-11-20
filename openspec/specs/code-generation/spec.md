# code-generation Specification

## Purpose
Govern code generation template resolution without built-in defaults, overlay-over-package lookup precedence, and generator source diagnostics.

## Requirements

### Requirement: Explicit Template Resolution

The code generator SHALL resolve templates only from the project template directory and the user template directory, in that priority order. The generator SHALL NOT ship or consult any built-in default templates, and SHALL NOT synthesize output from hardcoded fallback content.

#### Scenario: Template found in project directory

- **WHEN** a module has templates under `{project}/templates/{ModuleName}/`
- **THEN** those templates are used for generation, preserving their relative directory structure

#### Scenario: No template found for a module

- **WHEN** neither the project nor the user template directory contains any template for a module
- **THEN** no output files are generated for that module
- **AND** the generator reports a user-visible warning identifying the module and the directories that were searched
- **AND** the overall generation result distinguishes "skipped (no templates)" from "generated" and "failed"

#### Scenario: EB template copy failure becomes visible

- **WHEN** an EB-imported project's `generate_PB` templates were not copied successfully for a module
- **THEN** generating that module yields the "skipped (no templates)" warning instead of silently falling back to any other template source

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

### Requirement: Template Lookup From Overlay And Package

对 format 8 工程中来自模块包的模块，生成器 SHALL 按“工程覆盖层 `templates/<Module>/` → 包内模板目录”的顺序查找模板：覆盖层中的同名文件优先，其余文件取自包内模板目录。format 8 工程保存时 SHALL NOT 把包内模板复制到工程中。生成器指纹 SHALL 只按模板内容计算，模板来源路径的变化不得改变指纹。format ≤7 工程的模板查找保持不变。

#### Scenario: 工程覆盖层中的修改不被覆盖

- **WHEN** 用户修改 `templates/<Module>/` 中的一个模板后保存工程
- **THEN** 修改后的文件不被包内模板覆盖
- **AND** 生成时使用修改后的模板，其余模板取自包内模板目录

#### Scenario: 模板来源变化不改变指纹

- **WHEN** 同一份模板内容从工程内副本改为直接取自包内模板目录
- **THEN** 生成器指纹不变
