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
