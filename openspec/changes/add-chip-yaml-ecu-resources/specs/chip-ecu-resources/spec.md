## ADDED Requirements

### Requirement: Chip YAML ECU Resources Section
The chip definition YAML SHALL support an optional `ecu_resources` section that groups key/value pairs by module, where the flat key `<Module>.<name>` equals the key a `.properties` file would use, and an optional `resource_version`. Scalar values SHALL be kept as scalars and multi-value entries as lists. A YAML file without these fields SHALL load exactly as before.

#### Scenario: Lossless YAML round trip
- **WHEN** a chip YAML containing `ecu_resources` with scalar values, list values and keys that contain dots is loaded and exported again
- **THEN** the exported YAML contains the same flat keys and values, and keys without a dedicated model field are not dropped

#### Scenario: Legacy YAML unchanged
- **WHEN** a chip YAML without `ecu_resources` is loaded
- **THEN** the chip loads with an empty `ecu_resources` and every other field has the same value as before this change

#### Scenario: Unsupported value type
- **WHEN** an `ecu_resources` entry holds a mapping or a nested list
- **THEN** loading that chip fails with an error naming the file and the key, and the chip is not added to the database

### Requirement: Index Range Notation For Long Lists
A list-valued `ecu_resources` entry SHALL be writable as a mapping from index ranges (`<first>-<last>`, inclusive) or single indexes to scalar values, and SHALL be expanded to the full list when the chip is loaded. The ranges SHALL cover indexes `0..N-1` exactly once; a gap, an overlap or an invalid key SHALL fail the load with an error naming the key.

#### Scenario: Range form equals plain list
- **WHEN** `Os.IsrTriggerMethodList` is written as `{0-1: 1, 2: 2, 3-4: 4}` in one chip and as `[1, 1, 2, 4, 4]` in another
- **THEN** both chips hold the same five-element list

#### Scenario: Gap in ranges
- **WHEN** a range mapping covers `0-3` and `5-7` only
- **THEN** loading fails with an error that names the list key and the missing index `4`

#### Scenario: Long list is written compactly
- **WHEN** a 992-element list with fewer runs than elements is exported to YAML
- **THEN** it is written in range form, and loading that YAML gives back the identical 992 elements

### Requirement: Properties Import Into Chip Definition
The system SHALL import one or more EB Tresos `.properties` files into a chip's `ecu_resources` without discarding any key, grouping each key by the text before its first dot and not requiring a dedicated model field for the key.

#### Scenario: Import a vendor resource file
- **WHEN** `Os_Resource_THA6412.properties` is imported into chip `THA6412_BGA516`
- **THEN** `OsResource.NumOfCores` equals `4`, `OsResource.AvailableCores` has four elements, and `Os.IsrTriggerMethodList` has 992 elements

#### Scenario: Multiple files for one chip
- **WHEN** two properties files that define the same key are imported in sequence
- **THEN** the later value replaces the earlier one and a log entry names the key and both values

### Requirement: Properties Export From Chip Definition
When a chip has `ecu_resources`, the exporter SHALL write one `.properties` file per module whose content comes only from `ecu_resources`, in the order the keys appear in the YAML, without adding default or hard-coded values. When a chip has no `ecu_resources`, the existing export output SHALL be unchanged.

#### Scenario: Round trip through properties
- **WHEN** a properties file is imported into a chip and the chip is exported to properties and imported again
- **THEN** the resulting flat key/value set is identical to the first import

#### Scenario: Deterministic output
- **WHEN** the same chip is exported twice
- **THEN** the two outputs are byte-identical

#### Scenario: No invented values
- **WHEN** a chip's `ecu_resources` does not define `Can.MaxHwObjects`
- **THEN** the exported files do not contain that key

### Requirement: Unified ECU Resource Resolution
The system SHALL build `project.ecu_resources` through a single resolver that merges plugin `.properties` values (lower priority) with the selected chip's YAML `ecu_resources` (higher priority), and SHALL run it when a project is created, opened or imported, when a module is added, and when the selected chip changes.

#### Scenario: New project receives chip resources
- **WHEN** the user creates a project and selects a chip whose YAML defines `OsResource.NumOfCores`
- **THEN** `ecu:get('OsResource.NumOfCores')` returns that value without importing any EB project

#### Scenario: YAML overrides properties
- **WHEN** a plugin properties file and the chip YAML define the same key with different values
- **THEN** the YAML value is used and an informational log entry names the key and both values

#### Scenario: Chip change recomputes
- **WHEN** the selected chip changes from chip A to chip B
- **THEN** `project.ecu_resources` contains no key that only chip A defined

#### Scenario: Imported EB project unchanged
- **WHEN** an EB project whose chips have no `ecu_resources` is opened
- **THEN** `project.ecu_resources` equals the value computed before this change and generated output and fingerprints are unchanged

### Requirement: Project-Local Chip Definition
Each project SHALL keep its own copy of the selected chip's YAML under `<project dir>/chips/<chip>.yaml`, written when the chip is selected for a new project or changed, and the resolver SHALL read the chip's `ecu_resources` from that copy, falling back to the packaged chip library only when the project has no copy. Changes to the packaged chip library SHALL NOT change an existing project's resources until the user explicitly updates the project's copy.

#### Scenario: New project stores its chip
- **WHEN** a project is created with chip `THA6412_BGA516` selected
- **THEN** `<project dir>/chips/THA6412_BGA516.yaml` exists and `project.ecu_resources` is built from it

#### Scenario: Project moved to another directory
- **WHEN** the project directory is copied to a new location and opened there
- **THEN** `project.ecu_resources` is identical and no absolute path is stored in the project file

#### Scenario: Library change does not affect existing project
- **WHEN** the packaged YAML of the selected chip is edited after the project stored its copy
- **THEN** the project's resources stay unchanged until the user runs the explicit update

#### Scenario: Old project keeps reading the library until the user acts
- **WHEN** a project without a `chips/` directory is opened, used and saved
- **THEN** nothing is written to `<project dir>/chips/`, the chip data is read from the library, and the status bar says the chip is not saved in the project yet

#### Scenario: User saves the chip to the project
- **WHEN** the user chooses "Save Chip to Project" for the selected chip
- **THEN** the library's YAML (or, if the library lacks the chip, a chip built from the project's resource `.properties` files without build configs) is written to `<project dir>/chips/<chip>.yaml` and later loads use it

#### Scenario: User updates the copy from the library
- **WHEN** the user chooses "Update from Library"
- **THEN** the dialog lists the ECU resource keys that differ and replaces the project's copy only after confirmation

### Requirement: Generator Uses Project ECU Resources
Every code generation entry that has a project SHALL pass `project.ecu_resources` to `CodeGenerator`, and `CodeGenerator` SHALL NOT rescan `.properties` files when `ecu_resources` is provided.

#### Scenario: Generation without Def directory
- **WHEN** a newly created project with no `Def/` directory generates code for a module whose template calls `ecu:get('OsResource.NumOfCores')`
- **THEN** the rendered output contains the value from the chip YAML

### Requirement: Missing And Inconsistent Key Diagnostics
When modules are loaded, the system SHALL collect the keys referenced by `ecu:get` and `ecu:list` in the loaded xdm files and templates, report keys that have no value in `project.ecu_resources` as warnings, report defined keys that nothing references as information, and check declared consistency rules. Diagnostics SHALL NOT block generation.

#### Scenario: Referenced key missing
- **WHEN** a loaded xdm references `ecu:get('OsResource.NumOfCores')` and the chip defines no such key
- **THEN** a warning names the key and the module that references it

#### Scenario: Count mismatch
- **WHEN** `OsResource.NumOfCores` is `4` and `OsResource.AvailableCores` has three elements
- **THEN** a consistency warning names both keys and both values

#### Scenario: Master core outside the core list
- **WHEN** `OsResource.AvailableCores` is `CORE0..CORE3` and `OsResource.MasterCore` is `OS_CORE_ID_5`
- **THEN** a consistency warning names `OsResource.MasterCore` and lists the available cores

#### Scenario: Os master core in the Os macro notation
- **WHEN** `OsResource.AvailableCores` is `CORE0, CORE1` and `OsResource.MasterCore` is `OS_CORE_ID_0`
- **THEN** no warning is raised, because the Os templates emit the value verbatim as a C macro name

#### Scenario: Os master core in CORE notation
- **WHEN** `OsResource.MasterCore` is `CORE0`
- **THEN** a warning states that the value is not in `OS_CORE_ID_<n>` form, and the stored value is not changed

#### Scenario: Resource master core
- **WHEN** `Resource.MasterCore` is `OS_CORE_ID_0`
- **THEN** a warning states that the value is not in `CORE<n>` form

#### Scenario: Dynamically built key
- **WHEN** a template builds a key by string concatenation
- **THEN** no missing-key warning is raised for that reference and the report states that dynamic keys are not scanned
