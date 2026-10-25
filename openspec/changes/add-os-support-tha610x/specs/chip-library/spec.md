## ADDED Requirements

### Requirement: THA610X Runs Os On One Core
The chip `THA610X_LFBGA180` SHALL be supported by the Os module: its selector value `Os_THA610X` SHALL be a declared value of `OsResourceSubderivative`, the Os ECU resources for it SHALL describe one core and one GIC at `0xF0000000`, and the memory layout configuration SHALL be available for it as for `THA6206_LFBGA292`.

#### Scenario: Chip selected
- **WHEN** a project with the Os module changes its chip to `THA610X_LFBGA180`
- **THEN** `OsResourceSubderivative` is written as `Os_THA610X` without a skipped-selector report, and `ecu:get('OsResource.NumOfCores')` is `1`

#### Scenario: Memory layout kept
- **WHEN** the chip change preview is shown for a change from `THA6206_LFBGA292` to `THA610X_LFBGA180` in a project with `MemoryBlock` containers
- **THEN** no memory layout container is listed as disabled

#### Scenario: Single-core GIC table
- **WHEN** Os code is generated for `THA610X_LFBGA180`
- **THEN** `Os_IsrGICAddr` has the single entry `0xF0000000U`

#### Scenario: Existing chips unchanged
- **WHEN** Os code is generated for `THA6206_LFBGA292` and for `THA6412_BGA516` after the change
- **THEN** the output is byte-identical to the output before the change

#### Scenario: Coverage clean
- **WHEN** the chip dependency scan runs on a project with the Os plugin
- **THEN** no resource coverage finding is reported for `Os_THA610X`
