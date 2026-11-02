## ADDED Requirements

### Requirement: Linker Plan Independent Of The Compiler
The system SHALL build, from the layout configuration, the chip and the link symbol needs, a linker plan that lists load regions and execution regions with their name, start (an absolute address, or after the previous region with an alignment), kind, alignment and the output sections they take sorted by name, and SHALL NOT contain syntax of any compiler. A generator SHALL read only the plan.

#### Scenario: Plan from a configuration
- **WHEN** the configuration places `.mcal_bss_asil_d_unspecified_core0` in `PRIVATE_BSS_CORE0`, a region on the memory window `CPU0BTCM`
- **THEN** the plan has the execution region `PRIVATE_BSS_CORE0` starting after the previous region in that window, with that section in it

#### Scenario: Same input, same plan
- **WHEN** the plan is built twice from the same configuration
- **THEN** the two plans are equal

### Requirement: Regions Of Missing Cores Reserved On Request
A required region that was left out of the configuration because it is named after a core the chip does not have SHALL appear in the plan as a reserved region that takes no sections when the option to reserve regions for missing cores is on, so that code that refers to it still links. The option SHALL be on by default, SHALL be saved with the project, and SHALL be switchable off for a startup code that does not refer to those regions.

#### Scenario: Reserved region for core 2
- **WHEN** the option is on, the code refers to `PRIVATE_DATA_CORE2` and the chip has two cores
- **THEN** the plan has a reserved region `PRIVATE_DATA_CORE2` with no sections

#### Scenario: Option off
- **WHEN** the user switches the option off
- **THEN** the plan has no reserved regions

#### Scenario: Option kept
- **WHEN** the user switches the option off, saves the project and opens it again
- **THEN** the option is still off

### Requirement: Generation Refused Or Warned
The system SHALL refuse to generate, writing nothing and listing the reasons, when a section is to be placed again, when a required region lies on no window, or when a region lies on a window the chip does not have. It SHALL warn, and still generate, for sections that are not placed and for required regions that come from the default layout without being checked against code.

#### Scenario: Section to be placed again
- **WHEN** a section is marked to be placed again after a chip change
- **THEN** generation is refused and the reason names the section

#### Scenario: Section not placed
- **WHEN** a section is not placed
- **THEN** generation goes ahead and the preview lists the section as not placed

### Requirement: Compiler Chosen From A Registry
The system SHALL offer the compilers ADS, GHS, HighTec, IAR and Tasking, SHALL mark those without a generator as not yet supported with the reason, and SHALL only generate for a supported one. Only ADS SHALL be supported.

#### Scenario: Unsupported compiler
- **WHEN** the user looks at the compiler choice
- **THEN** ADS can be chosen and the others are disabled with the note that they are not yet supported

#### Scenario: Unsupported compiler requested in code
- **WHEN** a generator is requested for GHS
- **THEN** an error says that GHS is not yet supported and no text is produced

### Requirement: ADS Scatter File Generated From The Plan
For ADS the system SHALL generate a scatter file whose first line is `#! armclang --target=arm-arm-none-eabi -march=armv8-a -E -x c`, which defines the window base addresses, writes the execution regions in plan order with `AlignExpr(ImageLimit(<previous>), <alignment>)` as start, and selects each output section with `*(.name)` in name order.

#### Scenario: Output read back
- **WHEN** a generated file is read with the scatter file reader of the memory map check
- **THEN** it has the execution regions of the plan with the same selectors

#### Scenario: Region start
- **WHEN** the plan has a region that follows `PRIVATE_DATA_CORE0` with alignment 64
- **THEN** its start in the file is `AlignExpr(ImageLimit(PRIVATE_DATA_CORE0), 64)`

### Requirement: ADS Limit, Stack And Reserved Regions Written
The generated ADS file SHALL write a limit region `<name>_LIMIT … EMPTY 0x0 {}` for each region that needs one, stack regions as `EMPTY` regions, and reserved regions as empty regions with a comment saying why they are there.

#### Scenario: Limit region for a copy region
- **WHEN** the plan has the region `PRIVATE_DATA_CORE0` needed for a limit
- **THEN** the file has `PRIVATE_DATA_CORE0_LIMIT` as an empty region after it

#### Scenario: Reserved region
- **WHEN** the plan has a reserved region `PRIVATE_DATA_CORE2`
- **THEN** the file has it as an empty region with a comment that it is reserved for a core the chip does not have and may be switched off when the startup code does not refer to it

### Requirement: Generated Output Is Deterministic
The generated file SHALL NOT contain a time stamp, and the same plan SHALL give the same file byte for byte.

#### Scenario: Byte for byte
- **WHEN** the file is generated twice from the same plan
- **THEN** the two files are identical

### Requirement: Generated File Checked At Once
After generating, the system SHALL run the memory map check on the generated file and show the result. The generated file SHALL have no finding of the kind missing link symbol or section without a receiving region, and the window SHALL say that this check shows that the generator and the check agree and does not show that the file links.

#### Scenario: Clean result
- **WHEN** the configuration places every section and covers every required region
- **THEN** the check of the generated file has no missing link symbol and no section without a receiving region

#### Scenario: Honest wording
- **WHEN** the check result is shown after generating
- **THEN** the window states that it does not prove that the compiler links the file

### Requirement: File Written Safely In The Integration Project
The system SHALL write the generated file to `scatter.scat` in `Ads` under the `linkedFile` directory of the integration project directory `IntegrationProject`, after showing what will be written and whether an existing file will be replaced, and only after the user confirms. An existing file SHALL be kept as `scatter.scat.bak`, and the new file SHALL be written to a temporary file and renamed so that a failure leaves no half-written file.

#### Scenario: Existing file backed up
- **WHEN** `scatter.scat` already exists and the user confirms
- **THEN** the old file is kept as `scatter.scat.bak` and the new one is in place

#### Scenario: Cancelled
- **WHEN** the user cancels at the preview
- **THEN** no file is written, backed up or created

#### Scenario: Write fails
- **WHEN** writing the temporary file fails
- **THEN** the existing `scatter.scat` is unchanged and the error is shown
