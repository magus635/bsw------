## ADDED Requirements

### Requirement: Memory Layout View Is Read-Only
The system SHALL provide a memory layout view that shows, for the memory sections used by the project's source and generated code, their output sections, source modules, attributes and current placement, and the view SHALL NOT change the project configuration or any file it reads.

#### Scenario: View leaves everything unchanged
- **WHEN** the user opens the view and changes grouping and filters on a project with source directories, a MemMap header directory and a scatter file
- **THEN** the configuration and every file read are unchanged afterwards

#### Scenario: View cancelled
- **WHEN** the user cancels a running view load
- **THEN** loading stops and no partial result is shown or exported

### Requirement: One Row Per Output Section With Its Placement
The view SHALL list one row per output section, with its kind (TEXT, RODATA, DATA or BSS), the set of source modules taken from the `<X>` of `<X>_START_SEC_<Y>`, the core and non-cacheable attribute taken from the section names, the places where it is used, and its placement: the execution region and the chip region containing that region's base, and whether the section is selected by name or only caught by a wildcard selector.

#### Scenario: Section shared by several modules
- **WHEN** the Can and Spi MemMap headers both map a section to `.mcal_bss_asil_d_unspecified_core0`
- **THEN** the view has one row for `.mcal_bss_asil_d_unspecified_core0` whose source modules are Can and Spi

#### Scenario: Section caught by a wildcard
- **WHEN** no selector names `.mcal_bss_asil_d_unspecified_core0` and the region `UNDEFINE_RAM_BSS` contains `*(+BSS)`
- **THEN** the row shows the region `UNDEFINE_RAM_BSS`, the chip region `GMU_NORMAL` and that the section is only caught by the wildcard `+BSS`

#### Scenario: Region base cannot be resolved
- **WHEN** the base of an execution region cannot be resolved to an address
- **THEN** its sections are listed under the execution region with the chip region shown as unknown, and the result states which region could not be resolved

### Requirement: Two Groupings Of The Same Rows
The view SHALL group the rows by physical region (chip region, then execution region, then section) or by module (module, then section), switchable by the user, with physical region as the default. Both groupings SHALL be built from the same rows and the same findings. Within a grouping the order SHALL be deterministic: chip regions by start address, modules and sections by name.

#### Scenario: Group by physical region
- **WHEN** the view groups by physical region and the scatter file places sections in `PRIVATE_BSS_CORE0` at `0x30100000` and in `UNDEFINE_RAM_BSS` at `0x10000000`
- **THEN** the view shows the chip region `GMU_NORMAL` before `CPU0BTCM`, as `0x10000000` is below `0x30100000`, and each lists its execution regions and their sections

#### Scenario: Group by module
- **WHEN** the user switches the grouping to module
- **THEN** the view shows each module with its sections, and each section shows the region it lands in

#### Scenario: Chip without memory regions
- **WHEN** the project's chip has no `memory_regions`
- **THEN** the physical region grouping lists the execution regions without chip regions, and the view states that the chip has no memory regions

### Requirement: Findings Shown With The Section They Concern
The view SHALL attach to each row the findings of the memory map check that concern that section, SHALL NOT judge sections on its own, and SHALL let the user show only rows with findings, or filter rows by module, core and kind.

#### Scenario: Show only rows with findings
- **WHEN** the user turns on "only rows with findings"
- **THEN** only sections that have at least one finding remain, and each shows its findings and their source file and line

#### Scenario: Same conclusion as the check
- **WHEN** the check reports core 0 data placed outside core 0 memory for a section
- **THEN** the view shows the same finding on that section's row

### Requirement: Duplicate Placement Reported
The memory map check SHALL report an output section that is selected by name in more than one execution region, listing all of those regions, and SHALL NOT decide which of them the linker uses.

#### Scenario: Section selected in two regions
- **WHEN** `*(.mcal_bss_asil_d_unspecified_core0)` appears in both `PRIVATE_BSS_CORE0` and `UNDEFINE_RAM_BSS`
- **THEN** the result reports the duplicate placement and names both regions

### Requirement: Data In Flash Reported
When the chip has memory regions, the memory map check SHALL report a DATA or BSS section whose execution region lies in a chip region of type flash, and SHALL NOT report TEXT or RODATA sections placed in RAM. Without chip regions this check SHALL be skipped with a note.

#### Scenario: BSS placed in flash
- **WHEN** a BSS output section lands in a region whose base is in the chip region `PFLASH0_NORMAL` of type flash
- **THEN** the result reports the section as data placed in flash

#### Scenario: Code placed in RAM
- **WHEN** a TEXT output section lands in the region `RAM_CODE` at `GMU_DEVICE`, a RAM region
- **THEN** the result reports nothing for that section

### Requirement: Layout View Exported
The view SHALL export the rows of the current grouping and filters as a Markdown table, with the scanned directories, file counts, linker file and whether the chip regions are still to be confirmed listed at the top.

#### Scenario: Export respects the filter
- **WHEN** the user filters to core 0 sections with findings and exports
- **THEN** the file contains only those rows, grouped as shown, and the header lists the scanned directories and the linker file
