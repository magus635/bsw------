## ADDED Requirements

### Requirement: Chip Change Previewed Before It Is Applied
When the user changes the project's chip in Project Properties or uses the "Apply Chip Selectors" action, the system SHALL first show a preview of the change and SHALL apply it only after the user confirms. Computing the preview SHALL NOT change the project.

#### Scenario: User cancels the preview
- **WHEN** the user cancels the preview
- **THEN** `selected_chip`, the ECU resources, the selector parameter values, the configuration and the project's `chips/` directory are unchanged

#### Scenario: User confirms the preview
- **WHEN** the user confirms the preview
- **THEN** the chip is applied with its selector values, and the 25 `MemoryBlock` containers are still in the configuration but no longer used for generation or EPC export

#### Scenario: No preview when no chip is changed
- **WHEN** a project is opened, an EB project is imported, a new project is created or a module is added
- **THEN** no preview is shown

### Requirement: Chip Change Preview Lists Disabled Configuration
The chip change preview SHALL list the selector parameter values that would change, the configured containers that would become disabled by definition ENABLE conditions, and those that would become enabled again, listing only the topmost container of each disabled subtree, grouped by module and container definition.

#### Scenario: Memory layout would be disabled by switching to THA6412
- **WHEN** the Os definition enables `MemoryBlock` only when `OsResourceSubderivative = 'Os_THA6206'`, the project has 25 `MemoryBlock` containers, and the user changes the chip from `THA6206_LFBGA292` to `THA6412_BGA516` in Project Properties
- **THEN** before anything is applied, the preview lists `OsResourceSubderivative` changing to `Os_THA6412` and `Os: MemoryBlock` with 25 containers that would be disabled

#### Scenario: Switching back
- **WHEN** the chip is `THA6412_BGA516` with those containers disabled and the user changes it back to `THA6206_LFBGA292`
- **THEN** the preview lists the 25 `MemoryBlock` containers as enabled again

#### Scenario: Containers disabled under both chips are not listed
- **WHEN** a container is disabled under both the current and the new chip
- **THEN** it does not appear in the preview

#### Scenario: Nothing would be disabled
- **WHEN** the chip change neither disables nor enables any configured container
- **THEN** the preview states that no configuration would be disabled and still asks for confirmation

#### Scenario: Evaluation fails
- **WHEN** the ENABLE conditions cannot be evaluated because of an error
- **THEN** the error is logged, the preview states that disabled configuration could not be checked, and the user can still confirm the change

### Requirement: Chip Change Preview Warns About Unavailable Kinds Of Container
The chip change preview SHALL warn prominently when a kind of container (a container definition of a module) has configured instances and none of them would remain enabled after the change, and SHALL show the container definition's description for each listed kind.

#### Scenario: Whole memory layout unavailable on THA6412
- **WHEN** every configured `MemoryBlock` of the Os module would be disabled by the change
- **THEN** the preview shows a warning naming `Os：MemoryBlock` and stating that generated code depending on it may be missing and the project may not compile or link, and marks the group as fully disabled

#### Scenario: Some instances remain
- **WHEN** a change from 4 to 2 cores disables core configurations 2 and 3 but keeps 0 and 1
- **THEN** the core configuration kind is listed as disabled but is not part of the warning

#### Scenario: Description of a kind
- **WHEN** the user points at a listed kind whose definition has the description "EN: Memory Block indicate the data block in the memory Region."
- **THEN** the tooltip shows "Memory Block indicate the data block in the memory Region." without the language prefix and markup

### Requirement: Chip Change Preview Explains Why
For each listed kind of container, the chip change preview SHALL show the definition ENABLE condition that changes its state, together with the inputs that condition reads which the change alters: selector parameters with their current and new values, and chip resources read through `ecu:get`, `ecu:list` or `ecu:has` with their values for the current and the new chip.

#### Scenario: Condition reads a selector
- **WHEN** `MemoryBlock` is disabled by `node:value(./../OsResourceSubderivative) = 'Os_THA6206'` and the change sets `OsResourceSubderivative` from `Os_THA6206` to `Os_THA6412`
- **THEN** the preview states that this condition no longer holds and shows `OsResourceSubderivative：Os_THA6206 → Os_THA6412`

#### Scenario: Condition reads a chip resource
- **WHEN** a core configuration is disabled by a condition reading `ecu:get('OsResource.NumOfCores')` and the change goes from a 4-core to a 2-core chip
- **THEN** the preview shows `芯片资源 OsResource.NumOfCores：4 → 2`

#### Scenario: Input not identified
- **WHEN** the condition reads neither a changed selector nor a changed chip resource
- **THEN** the preview shows the condition and states that the changed input could not be identified
