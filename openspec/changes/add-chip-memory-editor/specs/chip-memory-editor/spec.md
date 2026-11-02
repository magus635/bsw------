## ADDED Requirements

### Requirement: Memory Regions Grouped Into Physical Memories
A chip's `memory_regions` entries SHALL accept the optional fields `memory` (the physical memory the entry is an address window of), `window` (a label for the window's use) and `source` (where the data comes from). Entries with the same `memory` SHALL be windows of one physical memory; an entry without `memory` SHALL be a memory of its own named like the entry. An entry written without the new fields SHALL load and be written back unchanged.

#### Scenario: Two windows of one memory
- **WHEN** `GMU_NORMAL` at `0x10000000` and `GMU_DEVICE` at `0x82000000` both have `memory: GMU`
- **THEN** the chip has one physical memory `GMU` with two windows, one cacheable and one not

#### Scenario: Entry without the new fields
- **WHEN** a chip YAML has the entry `{name: CPU0ATCM, start: '0x30000000', size: '0x10000', type: ram, core: 0, cacheable: false}`
- **THEN** it loads as a memory named `CPU0ATCM` with one window, and saving writes it back without `memory`, `window` or `source`

#### Scenario: Library chips keep their checksum
- **WHEN** a library chip has no entry using the new fields
- **THEN** its checksum is the same as before the fields existed

### Requirement: Chip Designer Lists And Edits The Physical Memory
The chip definition designer SHALL have a page that lists the chip's physical memories with their windows (name, start address, size, type, core, cacheable, source) and lets the user add, change, rename and remove them, with addresses and sizes entered in hexadecimal. Saving an edit made elsewhere in the designer SHALL keep the chip's memory regions.

#### Scenario: Add a window
- **WHEN** the user adds a window `GMU_DEVICE` at `0x82000000`, size `0x40000`, not cacheable, to the memory `GMU` and saves the chip
- **THEN** the saved chip has that window under `GMU`, and loading it again gives the same values

#### Scenario: Rename a memory
- **WHEN** the user renames the memory `GMU` to `GMU0`
- **THEN** every window of that memory now has `memory: GMU0`

#### Scenario: Remove a window
- **WHEN** the user removes the window `GMU_DEVICE` and saves
- **THEN** the saved chip no longer has it and still has the other windows

#### Scenario: Saving an edit keeps the other data
- **WHEN** the user edits only the flash size on the basic data page of a chip with memory regions
- **THEN** the saved chip still has all its memory regions

### Requirement: Invalid Memory Data Stops The Save, Doubtful Data Does Not
A problem that makes the memory data unloadable (a number that is not a number, a size that is not positive, a repeated name, a type other than flash or ram) SHALL stop the save and name the entry. A problem that only makes the data doubtful (a window overlapping another memory, windows of one memory of different sizes or types) SHALL be listed and SHALL NOT stop the save.

#### Scenario: Invalid size stops the save
- **WHEN** the user enters the size `0` for a window and saves
- **THEN** the save is stopped and the message names the window and says the size must be positive

#### Scenario: Repeated name stops the save
- **WHEN** two windows of the chip have the name `GMU_NORMAL`
- **THEN** the save is stopped and the message names `GMU_NORMAL`

#### Scenario: Doubtful data is listed and saved
- **WHEN** the windows of one memory have the sizes `0x40000` and `0x20000`
- **THEN** the page lists the difference as a problem and the chip can still be saved

#### Scenario: Overlap with another memory
- **WHEN** a window of the memory `GMU` overlaps a window of the memory `LMU1`
- **THEN** the page lists the overlap and the chip can still be saved

### Requirement: Memory Regions Imported From A Linker File's Comment Table
The designer SHALL import memory regions from the comment table at the head of an ADS scatter file, reading lines of the forms `name start end - length` and `name start start + length`. The result SHALL be shown first and merged into the chip only after the user confirms. Imported entries SHALL carry their source and SHALL be marked to be confirmed.

#### Scenario: Import of the THA6206 table
- **WHEN** the user imports a scatter file whose comment table lists `CPU0BTCM  0x30100000  0x30100000 - 0x30130000 (192K)  AXI access CPU0BTCM address`
- **THEN** the preview shows a region `CPU0BTCM` at `0x30100000` of size `0x30000`, and nothing is added to the chip until the user confirms

#### Scenario: Offset form
- **WHEN** a line reads `CPUXATCM  0x00000000  0x00000000 + 64K  local access CPUXATCM address`
- **THEN** it is imported as a region of size `0x10000` marked as a core-local window

#### Scenario: Cancelled import
- **WHEN** the user cancels the preview
- **THEN** the chip is unchanged

### Requirement: Import Does Not Overwrite Or Guess
An entry whose name the chip already has SHALL NOT be overwritten by an import and SHALL be reported as skipped. Type, cacheability and core SHALL be taken from a line's trailing text only where it says so; where it does not, the field SHALL be left unset and the entry marked to be confirmed.

#### Scenario: Existing entry not overwritten
- **WHEN** the chip already has a region `CPU0BTCM` and the file lists it again with other values
- **THEN** the existing entry is kept and the import reports that `CPU0BTCM` was skipped

#### Scenario: Field the text does not state
- **WHEN** a line's trailing text says nothing about cacheability
- **THEN** the imported entry is marked to be confirmed and its cacheability is not guessed

### Requirement: Layout Shows Memories With Their Windows
The memory map workbench's layout page SHALL show the physical regions grouped by physical memory with their windows, and a chip whose entries have no `memory` field SHALL be shown as before.

#### Scenario: Grouped display
- **WHEN** the chip has `GMU_NORMAL` and `GMU_DEVICE` as windows of the memory `GMU`
- **THEN** the layout page shows `GMU` with both windows beneath it

#### Scenario: Chip without grouping
- **WHEN** the chip's entries have no `memory` field
- **THEN** every entry is shown as its own memory, as before
