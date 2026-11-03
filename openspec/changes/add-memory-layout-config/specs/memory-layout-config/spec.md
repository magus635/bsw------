## ADDED Requirements

### Requirement: Layout Configuration In Three Layers
The system SHALL keep a memory layout configuration with execution regions placed on the windows of the chip's physical memories, and sections placed in execution regions. An execution region SHALL have a name, the memory and window it lies in, a kind (code, const, data, bss, noinit, stack or reserved), an order and an alignment. A section SHALL be placed only in an execution region whose kind accepts the section's kind, and a placement that does not fit SHALL be refused with the reason.

#### Scenario: Region kind decides what it accepts
- **WHEN** the user places a BSS section in an execution region of kind data
- **THEN** the placement is refused and the message says that a data region does not take BSS sections

#### Scenario: Stack region takes no sections
- **WHEN** the user places a section in an execution region of kind stack
- **THEN** the placement is refused

### Requirement: Required Execution Regions Cannot Be Removed Or Renamed
The execution regions that code refers to by name (the link symbol needs read from the added sources) SHALL be required: they SHALL NOT be removed or renamed, and the user SHALL be able to choose the window each lies in and what is placed in it.

#### Scenario: Required region from the code
- **WHEN** the scanned code asks for `PRIVATE_DATA_CORE0` for copy
- **THEN** the configuration has the required region `PRIVATE_DATA_CORE0`, and it cannot be removed or renamed

#### Scenario: No requirements found
- **WHEN** the scanned directories hold no code that refers to regions
- **THEN** the required regions come from the chip's default layout and the window says that they were not checked against code

#### Scenario: User region
- **WHEN** the user adds the region `MY_FAST_DATA` of kind data
- **THEN** it can be placed on a window, filled and removed again

### Requirement: Regions Of Missing Cores And Limit Regions Left Out
A required region named after a core the chip does not have (a core number not below the chip's core count) SHALL be left out of the configuration, and its name SHALL be kept in a list of trimmed regions so that the generation of a linker file can still provide it. The limit region `<name>_LIMIT` of a region SHALL NOT be part of the configuration.

#### Scenario: Region of a core the chip lacks
- **WHEN** the scanned code refers to `PRIVATE_DATA_CORE2` and the chip has two cores
- **THEN** the configuration has no region `PRIVATE_DATA_CORE2`, and the list of trimmed regions has it

#### Scenario: Limit region not shown
- **WHEN** the code needs the limit of `PRIVATE_DATA_CORE0`
- **THEN** the configuration has no region `PRIVATE_DATA_CORE0_LIMIT`

### Requirement: Sections Placed By Rules And Manual Exceptions
Each scanned section SHALL have exactly one status: placed by a rule, placed by hand, not placed, or to be placed again. A manual placement SHALL take precedence over the rules; among the rules the first matching one in the list SHALL win. A rule matches by section name pattern, kind, core, cacheability and module, all given conditions having to hold. Removing a manual placement SHALL return the section to the result of the rules.

#### Scenario: Manual placement beats a rule
- **WHEN** a rule places `.mcal_bss_asil_d_unspecified_core0` in `PRIVATE_BSS_CORE0` and the user places it by hand in `UNDEFINE_RAM_BSS`
- **THEN** its status is manual and its target is `UNDEFINE_RAM_BSS`

#### Scenario: Removing the manual placement
- **WHEN** the user removes that manual placement
- **THEN** the section is placed in `PRIVATE_BSS_CORE0` by the rule

#### Scenario: First matching rule wins
- **WHEN** two rules both match a section
- **THEN** the first in the list places it, and the rule editor marks the second as shadowed

#### Scenario: No rule matches
- **WHEN** no rule matches a section and it has no manual placement
- **THEN** its status is not placed

#### Scenario: Rule with an invalid target
- **WHEN** a rule names an execution region that does not exist
- **THEN** the rule is marked invalid and places nothing

### Requirement: Rules Are Open To Change
The user SHALL be able to change, add, remove and reorder the rules of a project, and each rule SHALL say whether it is a factory rule or the user's own and MAY carry a note. A factory rule that the user changed SHALL be marked as changed with its original kept for comparison.

#### Scenario: Change a factory rule
- **WHEN** the user changes the target of a factory rule
- **THEN** the rule is marked as changed, its original target stays visible for comparison, and sections follow the new target

#### Scenario: Add and reorder
- **WHEN** the user adds a rule and moves it above a factory rule
- **THEN** it is tried first, and the factory rule is marked as shadowed for the sections the new rule matches

### Requirement: Factory Rules For THA6206 Copied Into The Project
For the chip THA6206 the system SHALL supply factory rules and a default layout taken from the vendor's linker script, each rule carrying a note on where it comes from. When the configuration page of a project is first opened, the factory rules SHALL be copied into the project's own configuration, and later changes SHALL only touch that copy. A chip without factory rules SHALL start with no rules, every section SHALL show as not placed, and the window SHALL say why.

#### Scenario: Core data goes to the core's private region
- **WHEN** the chip is THA6206 and a BSS section is named for core 0 and is cacheable
- **THEN** the factory rules place it in `PRIVATE_BSS_CORE0`

#### Scenario: Copy is the project's own
- **WHEN** the user changes a rule and the software later ships other factory rules
- **THEN** the project's rules are unchanged and the rule editor says that newer factory rules exist

#### Scenario: Chip without factory rules
- **WHEN** the project's chip is THA6412
- **THEN** every section is not placed and the window says that this chip has no factory rules

### Requirement: Factory Rules Can Be Restored
The user SHALL be able to restore the factory rules, which replaces the project's rule list by the factory one. The system SHALL first show which user changes would be lost and SHALL restore only after the user confirms. Manual placements SHALL NOT be affected.

#### Scenario: Preview before restoring
- **WHEN** the user has changed one factory rule and added one rule, and asks to restore
- **THEN** the preview lists the changed rule and the added rule as lost, and nothing changes until the user confirms

#### Scenario: Manual placements stay
- **WHEN** the user restores the factory rules
- **THEN** the manual placements are unchanged

### Requirement: Layout Configuration Saved As Text In The Integration Project
The layout configuration SHALL be saved as a text file `memorymap.json` in the `linkedFile` directory of the integration project directory `IntegrationProject` of the project, ordered by name so that versions compare cleanly, with a schema version and the chip's name. A project without the file SHALL load with an empty configuration, and an unreadable file SHALL be reported without stopping the project from opening.

#### Scenario: Saved and read back
- **WHEN** the user places sections, adds a rule and saves the configuration
- **THEN** reopening the project shows the same placements and rules

#### Scenario: Older project
- **WHEN** a project without `memorymap.json` is opened
- **THEN** it has an empty configuration and nothing is written

#### Scenario: Damaged file
- **WHEN** `memorymap.json` is not valid JSON
- **THEN** the project opens, and the window says that the configuration could not be read and names the file

### Requirement: Placement Configured In The Memory Map Window
The memory map window SHALL have a configuration page with the scanned sections on the left, each with its status and target, and the chip's physical memories, their windows and the execution regions on the right. The user SHALL be able to place sections by dragging them to an execution region or with the add and remove buttons, several at once, and the statuses SHALL follow each change at once.

#### Scenario: Other pages describe the file on disk
- **WHEN** the user changes a placement before generating a linker file
- **THEN** the diagnostics and layout pages are unchanged and the configuration page says that they describe the linker file on disk

#### Scenario: Drag a section
- **WHEN** the user drags `.mcal_bss_asil_d_unspecified_core0` to the region `PRIVATE_BSS_CORE0`
- **THEN** the section's status on the configuration page becomes manual with that target

#### Scenario: Remove with the button
- **WHEN** the user selects a manually placed section and uses the remove button
- **THEN** it returns to the result of the rules

#### Scenario: Refused placement
- **WHEN** the user drags a TEXT section to a region of kind bss
- **THEN** nothing changes and the reason is shown

#### Scenario: Unsaved changes
- **WHEN** the user closes the window with unsaved changes
- **THEN** the user is asked whether to save them

### Requirement: Chip Change Keeps The Layout And Names What No Longer Fits
When the project's chip is changed, the chip change preview SHALL list for the layout the placements that stay valid, the placements whose memory or window is not on the new chip or whose cacheability or core differs, and the changes of the required regions. Placements that no longer fit SHALL be marked to be placed again and SHALL NOT be removed. Computing the preview SHALL NOT change the project.

#### Scenario: Window with different attributes
- **WHEN** a section is placed in a window that is cacheable on the old chip and not cacheable on the new one
- **THEN** the placement is listed as to be placed again, and it is not moved to another window

#### Scenario: Placement stays
- **WHEN** the new chip has the same memory and window with the same attributes
- **THEN** the placement stays valid

#### Scenario: Required region no longer asked for
- **WHEN** the new chip's code no longer refers to a required region
- **THEN** the region is marked as no longer needed and kept in the configuration

#### Scenario: Preview cancelled
- **WHEN** the user cancels the preview
- **THEN** the layout configuration and the chip are unchanged
