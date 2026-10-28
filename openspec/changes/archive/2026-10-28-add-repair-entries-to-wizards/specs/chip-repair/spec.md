## MODIFIED Requirements

### Requirement: Repair Entry Points
The application SHALL open the repair wizard from the main window menu with the project's chip preselected, from the chip definition designer for the chip being edited, from Project Properties for a chip whose data is incomplete, and from the chip pages of the new-project and hardware-mapping wizards for the chosen chip of the library. After a repair, the project's chip constraints SHALL be refreshed, and when the project keeps its own copy of the repaired chip the user SHALL be told to use "Update from Library".

#### Scenario: From Project Properties
- **WHEN** the selected chip is shown as `<name>（资料不完整）` and the user clicks "修复…"
- **THEN** the wizard opens with that chip selected

#### Scenario: Designer with unsaved edits
- **WHEN** the designer has unsaved edits and the user clicks "修复此芯片…"
- **THEN** the designer asks whether to discard them, and after a repair it reloads the repaired chip

#### Scenario: Project keeps a copy
- **WHEN** the repaired chip is the one the project keeps in `chips/`
- **THEN** the user is told that "Update from Library" brings the repair into the project, and the project copy is not changed automatically

#### Scenario: From the new-project wizard
- **WHEN** a chip of the library is selected on the chip page and the user clicks "修复所选…"
- **THEN** the wizard opens with that chip, and after a repair the list is refreshed with the same chip still selected

#### Scenario: From the hardware-mapping wizard
- **WHEN** the chosen chip is in the library and the user clicks "Repair..."
- **THEN** the wizard opens with that chip and the project, and after a repair the chip list is reloaded with the same chip chosen
