## ADDED Requirements

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
