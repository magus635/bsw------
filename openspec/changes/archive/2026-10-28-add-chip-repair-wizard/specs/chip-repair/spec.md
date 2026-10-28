## ADDED Requirements

### Requirement: Repair Wizard
The application SHALL offer a chip repair wizard that repairs a chip of the chip library in six steps: choose the chip, choose the sources, select the changes, handle the unconfirmed marks, review the views and completeness, and save. Each step SHALL use the chip repair functions, and the wizard SHALL save only on its last step.

#### Scenario: Chip page
- **WHEN** the wizard opens for `THA610X_LFBGA180`
- **THEN** it shows the chip's `resource_version`, its completeness items and its latest history entry

#### Scenario: Marks only
- **WHEN** no source is chosen and `metadata.flash_size` is confirmed
- **THEN** the saved chip no longer marks `metadata.flash_size` and its ECU resources are unchanged

#### Scenario: Cancelled
- **WHEN** the wizard is cancelled on any page
- **THEN** the chip file, its backup and its history are unchanged

### Requirement: Change Selection In The Wizard
The difference step SHALL list the changes grouped by module with kind, old and new value, mark type-only differences, preselect added and changed keys but not removed ones, and let the user select by module or by key.

#### Scenario: Default selection
- **WHEN** the sources add one key, change one and remove one
- **THEN** the added and changed keys are selected and the removed key is not

#### Scenario: Module selection
- **WHEN** the user unchecks the `Port` module
- **THEN** no `Port` key is applied

### Requirement: Completeness Before And After
The review step SHALL show the view synchronization result and the chip's completeness items split into resolved, remaining and new, checked together with the open project's modules when a project is open.

#### Scenario: Confirmed mark resolved
- **WHEN** `metadata.flash_size` is confirmed in the wizard
- **THEN** the review step lists it as resolved

### Requirement: Saving From The Wizard
The save step SHALL require a source text and an author, prefill the next version and the git user name, and keep the wizard open with a message when the chip file changed since the wizard loaded it.

#### Scenario: File changed meanwhile
- **WHEN** the chip file is saved by the designer while the wizard is open and the user finishes the wizard
- **THEN** nothing is written, a message explains that the file changed, and the wizard stays open

#### Scenario: Saved
- **WHEN** the user finishes the wizard
- **THEN** the chip is saved with a backup and a history entry and the library returns the repaired chip

### Requirement: Repair Entry Points
The application SHALL open the repair wizard from the main window menu with the project's chip preselected, from the chip definition designer for the chip being edited, and from Project Properties for a chip whose data is incomplete. After a repair, the project's chip constraints SHALL be refreshed, and when the project keeps its own copy of the repaired chip the user SHALL be told to use "Update from Library".

#### Scenario: From Project Properties
- **WHEN** the selected chip is shown as `<name>（资料不完整）` and the user clicks "修复…"
- **THEN** the wizard opens with that chip selected

#### Scenario: Designer with unsaved edits
- **WHEN** the designer has unsaved edits and the user clicks "修复此芯片…"
- **THEN** the designer asks whether to discard them, and after a repair it reloads the repaired chip

#### Scenario: Project keeps a copy
- **WHEN** the repaired chip is the one the project keeps in `chips/`
- **THEN** the user is told that "Update from Library" brings the repair into the project, and the project copy is not changed automatically
