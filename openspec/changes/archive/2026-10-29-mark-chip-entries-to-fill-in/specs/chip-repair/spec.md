## MODIFIED Requirements

### Requirement: Change Selection In The Wizard
The difference step SHALL list the changes grouped by module with kind, old and new value, mark type-only differences, preselect added and changed keys but neither removed ones nor entries still to fill in (keys added without a value because the modules reference them), and let the user select by module or by key.

#### Scenario: Default selection
- **WHEN** the sources add one key, change one and remove one
- **THEN** the added and changed keys are selected and the removed key is not

#### Scenario: Module selection
- **WHEN** the user unchecks the `Port` module
- **THEN** no `Port` key is applied

#### Scenario: Entry to fill in not preselected
- **WHEN** a `.properties` source changes `Port.B` and the key scan finds `Os.Missing` referenced by the modules but absent from the chip
- **THEN** `Port.B` is selected, and `Os.Missing` is listed as added with the value "（待填写）" but not selected

### Requirement: Saving From The Wizard
The save step SHALL require a source text and an author, prefill the next version and the git user name, ask before saving when the repair adds entries still to fill in, and keep the wizard open with a message when the chip file changed since the wizard loaded it.

#### Scenario: File changed meanwhile
- **WHEN** the chip file is saved by the designer while the wizard is open and the user finishes the wizard
- **THEN** nothing is written, a message explains that the file changed, and the wizard stays open

#### Scenario: Saved
- **WHEN** the user finishes the wizard
- **THEN** the chip is saved with a backup and a history entry and the library returns the repaired chip

#### Scenario: Entries to fill in
- **WHEN** the user selected the entry to fill in `Os.Missing` and finishes the wizard
- **THEN** the wizard states that one entry is still to fill in and asks whether to save; if the user declines, nothing is written and the wizard stays on the save step

## ADDED Requirements

### Requirement: Entries To Fill In Are Marked
When a repair (wizard or command line) or the chip definition designer adds an entry without a value because the modules reference its key, the chip SHALL mark `ecu_resources.<module>.<key>` under `metadata.unconfirmed` with the note `待填写`, so that the chip is reported as incomplete and a project using the chip warns about the entry. A `待填写` mark SHALL be removed when its entry has a value or no longer exists, and the history SHALL list it as confirmed. Empty values read from a source file SHALL NOT be marked, and marks with any other note SHALL NOT be removed by this rule.

#### Scenario: Saved without a value
- **WHEN** a repair selects `Os.Missing` found by the key scan and saves the chip
- **THEN** `metadata.unconfirmed` lists `ecu_resources.Os.Missing` with the note `待填写`, the chip is reported as incomplete, and the history entry lists the field as marked

#### Scenario: Filled in later
- **WHEN** `Os.Missing` is given a value in the designer, or by a later repair from a `.properties` file, and the chip is saved
- **THEN** `ecu_resources.Os.Missing` is no longer marked and the history entry lists it as confirmed

#### Scenario: Empty value from a vendor file
- **WHEN** a `.properties` source holds `Gtm.TriggerXModule4:` without a value and the repair applies it
- **THEN** the entry is saved without a value and is not marked

#### Scenario: Other marks kept
- **WHEN** `ecu_resources.Intc` is marked with another note and the chip is saved
- **THEN** the mark is kept

#### Scenario: Project warned
- **WHEN** a project whose chip marks `ecu_resources.Os.Missing` as `待填写` is opened
- **THEN** the ECU resource diagnosis has a warning naming `Os.Missing` as still to fill in
