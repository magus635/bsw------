# definition-chip-expressions Specification

## Purpose
Evaluate the chip expressions in vendor module definitions (defaults, enumeration ranges and maximum counts) against the ECU resources of the project's chip, so that a project behaves as the chip it uses, without changing configured values.

## Requirements

### Requirement: Definition Chip Expressions Follow The Project's Chip
Whenever a project computes its ECU resources, chip expressions in the loaded module definitions SHALL be evaluated against those resources: a default value, an enumeration range and a container's maximum count. An expression that cannot be evaluated SHALL leave the static default, no options and no upper limit.

#### Scenario: Opening a project
- **WHEN** a project for THA6412 is opened and its Adc definition gives the hardware unit list `MAX = num:i(count(ecu:list('Adc.HwUnitId')))`
- **THEN** at most 12 hardware units can be added, and a thirteenth is reported by validation

#### Scenario: Chip default for an unconfigured parameter
- **WHEN** a parameter's default is `ecu:get('Wdg.WdgDeviceInitialTimeout')` and the parameter has no configured value
- **THEN** generation and a newly created container use the chip's value, converted to the parameter's type

#### Scenario: Changing the chip
- **WHEN** the project's chip is changed
- **THEN** the defaults, ranges and maximum counts are evaluated again for the new chip

#### Scenario: Expression not evaluated
- **WHEN** an expression has a form that is not supported or its key is missing
- **THEN** the parameter keeps its static default, if any, and the container has no upper limit

### Requirement: Configured Values Are Not Changed By Chip Expressions
Evaluating chip expressions SHALL change only the loaded definitions; values stored in the configuration SHALL stay as they are.

#### Scenario: Configured value differs from the chip default
- **WHEN** `WdgDeviceInitialTimeout` is configured as `10.0` and the chip default is `2`
- **THEN** the configured value stays `10.0` and generation uses `10.0`

