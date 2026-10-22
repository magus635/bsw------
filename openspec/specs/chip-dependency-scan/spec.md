# chip-dependency-scan Specification

## Purpose
A read-only scan that lists every place in the module definitions, templates and added source directories (EB plugins, kernel, SDK, MCAL) that depends on a particular chip: chip-name checks, implicit default branches a new chip would take, suspected hard-coded chip values, and the coverage of each selector value by library chips and ECU resource files. Its Markdown checklist is the starting point for adding a new chip.

## Requirements

### Requirement: Chip Dependency Scan Is Read-Only
The system SHALL provide a chip dependency scan that lists every place in the project's module definitions and templates, and in user-added source directories, that depends on a particular chip, and the scan SHALL NOT change the project configuration or any scanned file.

#### Scenario: Scan leaves everything unchanged
- **WHEN** the user runs the scan on a project with Os and Port loaded and the Os plugin, kernel, SDK and MCAL directories added
- **THEN** the configuration, the project's selected chip and every scanned file are unchanged after the scan

#### Scenario: Scan cancelled
- **WHEN** the user cancels a running scan
- **THEN** the scan stops and no partial result is exported

### Requirement: Chip Keywords Derived From The Chip Library
The scan SHALL recognise chip names from the chip library's chip names and selector values, the declared values of selector parameters in the loaded definitions, the model token of each name and its family prefix, plus keywords added by the user; a word SHALL match a family prefix only when at least one digit or `X` follows the prefix.

#### Scenario: Family wildcard recognised
- **WHEN** the library has `THA6104_*`, `THA6206_LFBGA292` and `THA6412_BGA516` and a template has `contains(node:value(ResourceSubderivative), 'THA610X')`
- **THEN** the comparison is reported as a chip-name check naming `THA610X`

#### Scenario: Prefix alone not a chip name
- **WHEN** a C file has `#ifdef THA6_REG_PROTECT`
- **THEN** it is not reported unless the identifier contains a model token such as `THA6412` or a user keyword

### Requirement: Chip-Name Checks Reported With Location
The scan SHALL report each XPath comparison (`=`, `!=`, `contains`, `starts-with`) against a chip name in definition files and templates, and each preprocessor condition (`#if`, `#ifdef`, `#ifndef`, `#elif`) naming a chip in C, assembler and linker files, with its file as a POSIX path relative to the project, its line number, its text and the chips it names; comments, descriptions and include paths SHALL NOT be reported.

#### Scenario: Not-equal comparison in a template
- **WHEN** `Port_PBcfg.c` line 81 has `[!IF "node:value(ResourceSubderivative) != 'THA6206_LFBGA292'"]`
- **THEN** the scan reports a chip-name check at that file and line naming `THA6206_LFBGA292`

#### Scenario: Kernel preprocessor check
- **WHEN** an added kernel directory has `Os/isr/Os_isr_hal.c` with `#ifdef OS_THA6206` at line 215
- **THEN** the scan reports it with that path and line

#### Scenario: Chip name in a description
- **WHEN** a definition's DESC text mentions `THA6206`
- **THEN** nothing is reported for it

### Requirement: Implicit Default Branches Reported
The scan SHALL report the `[!ELSE]` of a template IF chain, and the `#else` of a preprocessor chain, whose conditions contain a chip-name check, and the branch of a negated chip check (`!=` against a chip name, `#ifndef` or `!defined(...)` of a chip macro), because a new chip would take that branch.

#### Scenario: Negated check
- **WHEN** a template has `[!IF "OsResourceSubderivative != 'Os_SC300'"!]`
- **THEN** that IF line is reported as an implicit default branch

#### Scenario: GIC address table
- **WHEN** a template has `[!IF "... = 'Os_THA6206'"]` with 6206 addresses followed by `[!ELSE]` with other addresses
- **THEN** the `[!ELSE]` line is reported as an implicit default branch, linked to the line of its IF

### Requirement: Suspected Hard-Coded Chip Values Reported
The scan SHALL report hexadecimal constants of at least `0x10000` in the text a template outputs (outside directives and outside comment lines), including linker-script templates, as values to be confirmed manually, listing at most 50 lines per file and the count of the rest.

#### Scenario: GIC address table
- **WHEN** `Os_isr_Lcfg.c` outputs `0xF0200000U,` in the ELSE branch of the GIC address table
- **THEN** that line is reported as a suspected hard-coded value

#### Scenario: Address in a comment
- **WHEN** `scatter.scat` outputs `;        CPU0ATCM                0x30000000 ...` as a comment line
- **THEN** that line is not reported

### Requirement: Resource Coverage Checked Per Selector Value
For each selector parameter of the loaded modules and each of its declared values, the scan SHALL report whether a library chip declares the value, whether `plugin.xml` registers an ECU resource file for it and the file exists, whether the file the configurator matches by name is the registered one, and which `ecu:get`/`ecu:list` keys referenced by the module are missing from that resource.

#### Scenario: Value without a chip
- **WHEN** `OsResourceSubderivative` declares `Os_SC300` and no library chip declares it
- **THEN** the scan reports that `Os_SC300` has no chip in the library

#### Scenario: Registered file differs from the matched file
- **WHEN** `plugin.xml` registers `resource/Os_Resource_THA6412.properties` for `Os_THA6412` and the configurator would match a different file for that chip
- **THEN** the scan reports both file names

#### Scenario: Missing key
- **WHEN** the Os templates reference `ecu:get('OsResource.NumOfCores')` and the resource for `Os_SC300` does not define it
- **THEN** the scan reports `OsResource.NumOfCores` missing for `Os_SC300`

### Requirement: Scan Settings Saved And Result Exported
The added scan directories and user keywords SHALL be saved in the project as POSIX paths relative to the project directory (projects without them load with none), the result SHALL be ordered by category, path and line so repeated scans give the same output, and the result SHALL be exportable as a Markdown checklist with one unchecked item per finding.

#### Scenario: Directories saved
- **WHEN** the user adds `../OS_Kernel` as a scan directory and saves the project
- **THEN** reopening the project shows `../OS_Kernel` in the scan directories

#### Scenario: Checklist export
- **WHEN** the user exports a result with the Port and kernel findings above
- **THEN** the file contains `- [ ]` items with the file path, line and text of each, grouped by category
