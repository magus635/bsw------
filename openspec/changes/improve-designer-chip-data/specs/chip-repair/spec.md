## ADDED Requirements

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
