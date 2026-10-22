# project-chip-selection Specification

## Purpose
The project's `selected_chip` is the single source of the chip. Every way of choosing a chip (new project wizard, Project Properties, EB import, opening a project) takes effect through one path, so ECU resources, UI constraints and the chip's selector parameters (e.g. `Resource.ResourceSubderivative`, `Os.OsResourceSubderivative`) stay consistent. Selector values are written only on an explicit chip choice; opening or importing a project only checks them.

## Requirements

### Requirement: Single Chip Selection Path
The project's selected chip SHALL be the single source of the chip for ECU resources, user-interface constraints and selector parameters, and every way of changing it (new project wizard, Project Properties, EB project import, opening a project) SHALL apply it through one operation that sets `selected_chip`, recomputes the ECU resources and reloads the user-interface constraints for that chip.

#### Scenario: Chip changed in Project Properties
- **WHEN** the user changes the chip from `THA6206_LFBGA292` to `THA6412_BGA516` in Project Properties and confirms
- **THEN** `selected_chip` is `THA6412_BGA516`, `ecu:list('Adc.HwUnitId')` returns the THA6412 values, and the constraints shown in the configuration panel are those of `THA6412_BGA516`

#### Scenario: EB project imported with a chip
- **WHEN** an EB project is imported with chip `THA6412_BGA516`
- **THEN** the user-interface constraints are those of `THA6412_BGA516` without opening Project Properties

### Requirement: Selector Parameters Written On Explicit Chip Selection
When the user explicitly selects a chip (new project wizard, a chip change confirmed in Project Properties, or the "Apply Chip Selectors" action), the system SHALL set every selector parameter declared in the chip's `selectors` section, in each loaded module, to the declared value, for both container parameters and module-level parameters, and SHALL report each value it changed and each selector it could not write with the reason.

#### Scenario: Resource and Os selectors written
- **WHEN** a project with Resource and Os loaded has `ResourceSubderivative = THA6206_LFBGA292` and `OsResourceSubderivative = Os_THA6206`, and the user selects `THA6412_BGA516` whose `selectors` declare `THA6412_BGA516` and `Os_THA6412`
- **THEN** `Resource.ResourceSubderivative` is `THA6412_BGA516`, the module-level `Os.OsResourceSubderivative` is `Os_THA6412`, and both changes are reported

#### Scenario: Module not loaded
- **WHEN** the selected chip declares `Os.OsResourceSubderivative` and the project has no Os module
- **THEN** no error occurs and the Os selector is skipped

#### Scenario: Module added later
- **WHEN** the project's chip is `THA6412_BGA516` and the user adds the Os module
- **THEN** the added module's `OsResourceSubderivative` is `Os_THA6412`

#### Scenario: Chip without selectors
- **WHEN** the selected chip's YAML has no `selectors` section
- **THEN** no configuration value is changed

### Requirement: Configuration Not Changed When Opening Or Importing
Opening a project or importing an EB project SHALL NOT change selector parameter values; when they differ from the values declared by the selected chip, the system SHALL warn and the user SHALL be able to apply the declared values with the "Apply Chip Selectors" action in Project Properties.

#### Scenario: Imported configuration differs
- **WHEN** an EB project is imported with chip `THA6412_BGA516` and its Resource EPC has `ResourceSubderivative = THA6206_LFBGA292`
- **THEN** the imported value is kept, a warning names the parameter, the configured value and the declared value

#### Scenario: Apply Chip Selectors
- **WHEN** the user then chooses "Apply Chip Selectors" in Project Properties
- **THEN** `ResourceSubderivative` becomes `THA6412_BGA516` and the warning no longer appears

### Requirement: Selector Parameters Read-Only In The Configuration Panel
A parameter declared as a selector by the selected chip SHALL be shown read-only in the configuration panel with a hint that it is determined by the project's chip in Project Properties, and editing configuration values SHALL NOT change the project's chip.

#### Scenario: Selector shown read-only
- **WHEN** the selected chip declares `Resource.ResourceSubderivative` and the user opens the Resource container holding it
- **THEN** the parameter cannot be edited and its hint names Project Properties

#### Scenario: Older project without a selected chip
- **WHEN** a project has no `selected_chip` and its configuration has `ResourceSubderivative = THA6412_BGA516`, which exactly one library chip declares
- **THEN** the project's chip is taken as `THA6412_BGA516` and no configuration value is changed
