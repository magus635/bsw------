# code-generation — Delta

## ADDED Requirements

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
