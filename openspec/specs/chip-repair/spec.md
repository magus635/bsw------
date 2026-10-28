# chip-repair Specification

## Purpose
How an existing chip of the chip library is repaired or supplemented. `ecu_resources` is the authority of a chip's data, and `resources`, `metadata.cores` and `ports` are views derived from it. A repair:

1. reads a source (vendor `.properties`, keys the modules reference);
2. shows the difference per flat key and applies only the selected changes;
3. synchronizes the views;
4. confirms or adds unconfirmed marks;
5. saves the chip with a backup and an entry in `data/chips/history/<name>.yaml`.

A repair never renames a chip, and it never removes data that is missing or unconfirmed. The core is `core/hardware/chip_repair.py`; the command line is `python -m tools.chip_repair`.

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
