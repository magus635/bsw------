# chip-repair Specification

## Purpose
How an existing chip of the chip library is repaired or supplemented. `ecu_resources` is the authority of a chip's data, and `resources`, `metadata.cores` and `ports` are views derived from it. A repair:

1. reads a source (vendor `.properties`, keys the modules reference);
2. shows the difference per flat key and applies only the selected changes;
3. synchronizes the views;
4. confirms or adds unconfirmed marks;
5. saves the chip with a backup and an entry in `data/chips/history/<name>.yaml`.

A repair never renames a chip, and it never removes data that is missing or unconfirmed. There are three ways to repair a chip:

- the core functions and `RepairSession` in `core/hardware/chip_repair.py`;
- the command line `python -m tools.chip_repair`;
- the repair wizard `ui/wizards/chip_repair_wizard.py`, opened from the Tools menu, the chip definition designer or Project Properties.

## Requirements

### Requirement: ECU Resource Difference
The system SHALL compare two `ecu_resources` by flat key (`<module>.<key>`) after normalizing their values, and SHALL report each differing key once as added, removed or changed, together with its old and new values, ordered by key. Values that are equal after range notation is expanded SHALL NOT be reported; values that differ only in type SHALL be reported as changed and marked as a type-only difference.

#### Scenario: Added, removed and changed keys
- **WHEN** the old resources have `Port.MaxAvailablePinID: 15` and `Mcu.ClockCount: 3`, and the new resources have `Port.MaxAvailablePinID: 16` and `Port.AvailableReadOnlyPorts: "_40_"`
- **THEN** the difference lists `Mcu.ClockCount` as removed, `Port.AvailableReadOnlyPorts` as added and `Port.MaxAvailablePinID` as changed from `15` to `16`, in that key order

#### Scenario: Range notation is not a change
- **WHEN** one side holds a key as the range mapping `{"0-3": 1}` and the other as the list `[1, 1, 1, 1]`
- **THEN** the key is not reported

#### Scenario: Type-only difference
- **WHEN** one side holds `OsResource.NumOfCores: 1` and the other `OsResource.NumOfCores: "1"`
- **THEN** the key is reported as changed and marked as a type-only difference

### Requirement: Repair Sources
The system SHALL read the ECU resources of one or more `.properties` files without changing any chip, later files replacing earlier values of the same key, and SHALL turn the keys that a project's or plugin directory's modules reference but a chip lacks into added changes with an empty value.

#### Scenario: Properties read for comparison only
- **WHEN** a vendor `.properties` file is read for chip `THA6412_BGA516`
- **THEN** the chip in the library and its file are unchanged

#### Scenario: Partial source
- **WHEN** a source holds only `Port` keys and the chip also has `Mcu` keys
- **THEN** the difference to that source compares only `Port` and reports no `Mcu` key as removed

#### Scenario: Keys referenced but missing
- **WHEN** the Os templates reference `OsResource.NumOfCores` and the chip has no such key
- **THEN** an added change for `OsResource.NumOfCores` with an empty value is produced

### Requirement: Selective Merge
The system SHALL apply to a copy of a chip only the changes whose keys the caller selects, removing a key only when its removal is selected; every unselected key and every other part of the chip SHALL stay unchanged. Existing keys SHALL keep their position; added keys SHALL be appended to the end of their module in key order, and new modules to the end of `ecu_resources`.

#### Scenario: Only selected keys applied
- **WHEN** a difference holds three changes and the caller selects one
- **THEN** only that key changes in the returned chip and the input chip is unchanged

#### Scenario: Removal not selected
- **WHEN** a difference reports `Mcu.ClockCount` as removed and the caller selects every other change
- **THEN** `Mcu.ClockCount` keeps its value

#### Scenario: Nothing selected
- **WHEN** no key is selected
- **THEN** the returned chip equals the input chip

### Requirement: Views Synchronized From ECU Resources
The system SHALL rebuild a chip's peripherals, core fields and pin table from its `ecu_resources`, replacing only what can be derived and keeping the rest, and SHALL report each view as unchanged, updated (with instance counts) or not derived (with the reason).

#### Scenario: Derived and kept peripheral types
- **WHEN** the ECU resources describe 12 CAN controllers and the chip also has hand-made `pwm_channel` instances
- **THEN** `can_controller` holds the 12 derived controllers, `pwm_channel` is unchanged, and the report lists `resources` as updated

#### Scenario: Core key absent
- **WHEN** the ECU resources have no core count key
- **THEN** `metadata.cores.count` is unchanged

#### Scenario: Pin derivation not available
- **WHEN** pin table derivation is not available
- **THEN** `ports` is unchanged and the report lists it as not derived

### Requirement: Unconfirmed Marks Confirmed Or Added
The system SHALL let a caller confirm a field listed under `metadata.unconfirmed`, removing only its mark and keeping the confirmation note for the repair history, and SHALL let a caller add a mark with a note; neither SHALL change the marked data.

#### Scenario: Field confirmed
- **WHEN** `metadata.flash_size` of `THA610X_LFBGA180` is confirmed with the note "按 SDK 链接脚本核对"
- **THEN** `metadata.flash_size` is no longer listed under `metadata.unconfirmed`, its value is unchanged, and the note is recorded in the history entry of the next save

#### Scenario: Field marked
- **WHEN** `ecu_resources.Intc` is marked with a note
- **THEN** it is listed under `metadata.unconfirmed` with that note and the chip is reported as incomplete

### Requirement: Repaired Chip Saved Safely
Saving a repaired chip SHALL refuse a renamed chip or a chip file changed since loading; otherwise it SHALL back up the file to `<name>.yaml.bak`, write the chip with a new `resource_version` (the given one, else the last numeric part incremented, else `1.0.0`) and checksum, and update the library.

#### Scenario: Saved with backup and version
- **WHEN** a repaired `THA610X_LFBGA180` with `resource_version` `1.0.0` is saved without a given version
- **THEN** `THA610X_LFBGA180.yaml.bak` holds the previous file, the new file has `resource_version` `1.0.1` and a valid checksum, and the library returns the repaired chip

#### Scenario: Rename refused
- **WHEN** the repaired chip's name is changed before saving
- **THEN** nothing is written and the save reports that renaming is not part of a repair

#### Scenario: File changed meanwhile
- **WHEN** the chip file is edited by someone else after the chip was loaded for repair
- **THEN** nothing is written and the save reports that the file has changed

#### Scenario: Projects see the repaired chip
- **WHEN** a project uses a copy of the chip from before the repair and is opened
- **THEN** it reports that the library's chip differs from its copy and points to "Update from Library"

### Requirement: Repair History
Each save of a repaired chip SHALL append one entry to `data/chips/history/<name>.yaml` with the date, author, source, note, version change, applied ECU resource changes with values, view report, confirmed and marked fields, and resulting checksum. Existing entries SHALL NOT change; the history SHALL NOT affect the checksum or be loaded as a chip.

#### Scenario: First repair
- **WHEN** a chip without a history file is saved after a repair
- **THEN** `history/<name>.yaml` is created with one entry for that repair

#### Scenario: Later repair appends
- **WHEN** the same chip is repaired and saved again
- **THEN** the history holds two entries, the first unchanged

#### Scenario: Library ignores history
- **WHEN** the chip library is loaded from a directory containing `history/`
- **THEN** the set of chips is the same as without it

### Requirement: Command-Line Repair
A command-line tool SHALL show the ECU resource difference between a library chip and `.properties` files without writing anything, and SHALL apply the selected changes, synchronize the views, confirm the given fields and save with history; removals SHALL be applied only when explicitly requested. It SHALL exit with 0 on success, 1 on invalid arguments or a changed file, and 2 when there is nothing to change.

#### Scenario: Diff only
- **WHEN** `chip_repair.py diff THA6412_BGA516 Port.properties` is run
- **THEN** the differences are printed and no file changes

#### Scenario: Apply without removals
- **WHEN** `chip_repair.py apply` is run with `--all-added --all-changed` and the difference contains removed keys
- **THEN** the removed keys keep their values and the history entry lists no removed keys

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

### Requirement: Completeness Before And After
The review step SHALL show the view synchronization result and the chip's completeness items split into resolved, remaining and new, checked together with the open project's modules when a project is open.

#### Scenario: Confirmed mark resolved
- **WHEN** `metadata.flash_size` is confirmed in the wizard
- **THEN** the review step lists it as resolved

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

### Requirement: Repair Entry Points
The application SHALL open the repair wizard from the main window menu (project's chip preselected), from the chip definition designer, from Project Properties for a chip with incomplete data, and from the chip pages of the new-project and hardware-mapping wizards. After a repair the project's chip constraints SHALL be refreshed, and when the project keeps its own copy of the chip the user SHALL be told to use "Update from Library".
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

### Requirement: Designer Saves Are Recorded
Saving a chip of the library in the chip definition designer SHALL be recorded like a repair: the previous file kept as a backup, the version raised, and one history entry added whose source names the designer. A file changed since it was loaded SHALL not be overwritten without asking, and a save without edits SHALL write nothing.

#### Scenario: Edit and save
- **WHEN** a library chip is edited in the designer and saved
- **THEN** `<name>.yaml.bak` exists, `resource_version` is the next version, and the history has one entry from "设计器手工编辑" with the old and new version

#### Scenario: Save without edits
- **WHEN** a library chip is opened and saved without any edit
- **THEN** no file, backup or history entry is written

#### Scenario: New chip
- **WHEN** a chip that is not in the library is saved
- **THEN** it is written without a backup or history

#### Scenario: File changed since loading
- **WHEN** the file changed on disk after the designer loaded it and the user declines to overwrite
- **THEN** the file keeps its content from outside
- **WHEN** the user agrees to overwrite
- **THEN** the chip is written without a backup or history

### Requirement: Designer Names The Copy It Edits
The chip definition designer SHALL edit the chip library used by the project it was opened from. When the project keeps its own copy of the chip that differs from the library, the designer SHALL say so when the chip is loaded, and SHALL show the same notice as the repair wizard after a save.

#### Scenario: Project copy differs
- **WHEN** the project's `chips/` holds a copy of the chip that differs from the library and the chip is opened in the designer
- **THEN** the designer shows that the project uses its own differing copy and that the library is being edited
- **WHEN** the chip is saved
- **THEN** the user is told the project copy still holds the old data and can be updated with "Update from Library"

#### Scenario: No differing copy
- **WHEN** the project has no copy of the chip, or its copy equals the library chip
- **THEN** neither notice is shown

### Requirement: Designer Edits Basic Chip Data
The designer SHALL let the user edit the CPU frequency, the flash size and the RAM size of a chip, check their format before saving, and show the note of an unconfirmed mark on such a field.

#### Scenario: Edit flash size
- **WHEN** the flash size of a library chip is changed from `512KB` to `4MB` and saved
- **THEN** the chip file holds `flash_size: 4MB`

#### Scenario: Wrong format
- **WHEN** the RAM size is `512` without a unit, or the CPU frequency is not a positive whole number
- **THEN** saving stops with a message naming the field

#### Scenario: Marked field
- **WHEN** `metadata.flash_size` is marked unconfirmed
- **THEN** the note of the mark is shown next to the flash size

### Requirement: History Lists Basic Data Changes
A repair history entry SHALL list each changed `metadata` field other than `unconfirmed`, with its old and new value.

#### Scenario: Flash size changed in the designer
- **WHEN** the flash size is changed from `512KB` to `4MB` and the chip is saved
- **THEN** the new history entry lists `flash_size` with old `512KB` and new `4MB`

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
