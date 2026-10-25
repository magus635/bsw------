## ADDED Requirements

### Requirement: SC300 Is An Os-Only Chip
The chip library SHALL contain the chip `SC300`, a single-core Arm Cortex-M3 that runs the Os module but not MCAL: it SHALL declare only the selector `Os.OsResourceSubderivative = Os_SC300`, and its Os ECU resources SHALL describe one core and the interrupt counts of the Os templates' SC300 branch instead of a copy of another chip's values.

#### Scenario: SC300 selected
- **WHEN** a project with the Os, Resource and Port modules changes its chip to `SC300`
- **THEN** `OsResourceSubderivative` is `Os_SC300`, the Resource and Port configurations are unchanged, and `ecu:get('OsResource.NumOfCores')` is `1`

#### Scenario: No peripherals is not missing data
- **WHEN** the completeness of `SC300` is checked
- **THEN** its empty pins and peripherals are not reported

### Requirement: Incomplete Chip Data Is Flagged, Never Removed
The system SHALL report a chip's data as incomplete when its YAML lists fields under `metadata.unconfirmed`, when a declared selector value is not a declared value of that parameter in the loaded definition, when it declares an Os selector without any Os resources, or when its declared core counts disagree; the report SHALL NOT change or remove any chip or chip data, and the chip SHALL remain selectable.

#### Scenario: Unconfirmed fields
- **WHEN** `THA610X_LFBGA180.yaml` lists `metadata.flash_size` and `ports` under `metadata.unconfirmed`
- **THEN** the chip is reported as incomplete, naming those fields, and its file is unchanged

#### Scenario: Selector value outside the definition
- **WHEN** a chip declares `Os.OsResourceSubderivative = Os_NEW` and the loaded Os definition does not declare `Os_NEW`
- **THEN** the chip is reported as incomplete, naming `Os_NEW`

#### Scenario: Shown when choosing a chip
- **WHEN** the user opens Project Properties
- **THEN** an incomplete chip appears as `<name>（资料不完整）`, choosing it shows the missing items, and the chip can still be applied
