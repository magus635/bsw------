## MODIFIED Requirements

### Requirement: Chip Change Preview Explains Why
For each listed kind of container, the chip change preview SHALL show the definition ENABLE condition that changes its state, together with the inputs that condition reads which the change alters: selector parameters with their current and new values, and chip resources read through `ecu:get`, `ecu:list` or `ecu:has` with their values for the current and the new chip, and the definition file (relative to the project) and line where that condition is written.

#### Scenario: Condition reads a selector
- **WHEN** `MemoryBlock` is disabled by `node:value(./../OsResourceSubderivative) = 'Os_THA6206'` and the change sets `OsResourceSubderivative` from `Os_THA6206` to `Os_THA6412`
- **THEN** the preview states that this condition no longer holds and shows `OsResourceSubderivative：Os_THA6206 → Os_THA6412`

#### Scenario: Condition reads a chip resource
- **WHEN** a core configuration is disabled by a condition reading `ecu:get('OsResource.NumOfCores')` and the change goes from a 4-core to a 2-core chip
- **THEN** the preview shows `芯片资源 OsResource.NumOfCores：4 → 2`

#### Scenario: Input not identified
- **WHEN** the condition reads neither a changed selector nor a changed chip resource
- **THEN** the preview shows the condition and states that the changed input could not be identified

#### Scenario: Location of the condition
- **WHEN** `MemoryBlock` of the Os module is disabled by the ENABLE condition written on line 3989 of the project's `Os.xdm`
- **THEN** the reason for `Os：MemoryBlock` shows `Os.xdm 第 3989 行`, and the summary of that condition lists the lines of every kind it disables
