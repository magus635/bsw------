## ADDED Requirements

### Requirement: Enumeration Values Checked Against The Chip Range
When a project is validated, an enumeration parameter whose definition range is a plain `ecu:list('<key>')` SHALL be checked against the list the project's current ECU resources give for that key. A value outside that list SHALL be reported as an error naming the key, the chip and the allowed values.

#### Scenario: Value not available on the selected chip
- **WHEN** the project's chip is THA610X, whose `Adc.HwUnitId` is `SARADC0` to `SARADC3`, and an `AdcHwUnitId` (range `ecu:list('Adc.HwUnitId')`) stores `SARADC8`
- **THEN** validation reports an error for `AdcHwUnitId` that names `Adc.HwUnitId` and THA610X and lists the allowed values

#### Scenario: Current chip prevails over the parsed options
- **WHEN** the definition was parsed while another chip was selected, so its options differ from the current chip's list
- **THEN** the value is checked against the current chip's list only

#### Scenario: Key matched like ecu:get
- **WHEN** the resource key differs from the expression only in letter case, or its value is a comma-separated string
- **THEN** the key is still found and the string is split into the allowed values

#### Scenario: Range not taken from the chip
- **WHEN** there is no project, the range is not a plain `ecu:list`, the ECU resources have no value for the key, or the list is empty
- **THEN** the parameter is checked against its definition options as before, and not checked if it has none

#### Scenario: Vendor demo configuration on its own chip
- **WHEN** the vendor THA6412 demo configuration is validated with the THA6412 chip
- **THEN** no error comes from the chip range
