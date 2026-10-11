## ADDED Requirements

### Requirement: Non-C Module Templates
Template discovery SHALL accept module-prefixed template files with the suffixes `.arxml` and `.orti` in addition to `.c`, `.h` and `.tpl`, and SHALL write the output under the same file name, matching EB tresos `TemplateBasedCodeGenerator` behaviour. Files with other suffixes SHALL continue to be ignored.

#### Scenario: ARXML template discovered
- **WHEN** the Os template directory contains `Os_Arti.arxml` with EB template syntax
- **THEN** generation renders it with the EB template engine and writes `Os_Arti.arxml` to the output directory

#### Scenario: Unlisted suffix ignored
- **WHEN** the template directory contains `Os_Notes.txt`
- **THEN** the file is not treated as a template
