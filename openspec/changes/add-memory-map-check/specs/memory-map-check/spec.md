## ADDED Requirements

### Requirement: Memory Map Check Is Read-Only
The system SHALL provide a memory map check that compares the memory sections used by source and generated code, the section mapping in MemMap headers and the placement in a linker file, and the check SHALL NOT change the project configuration or any file it reads.

#### Scenario: Check leaves everything unchanged
- **WHEN** the user runs the check on a project with MCAL, SDK and OS kernel directories, a MemMap header directory and a scatter file added
- **THEN** the configuration and every file read by the check are unchanged afterwards

#### Scenario: Check cancelled
- **WHEN** the user cancels a running check
- **THEN** the check stops and no partial result is exported

### Requirement: Section Usage Collected With Pairing Checks
The check SHALL collect every `<X>_START_SEC_<Y>` and `<X>_STOP_SEC_<Y>` definition with file and line from the added source directories and the generation output directory, skipping files containing template syntax `[!`. It SHALL report unpaired START or STOP, START and STOP at different `#if` levels, and a definition not followed by a MemMap `#include`; findings inside a conditional branch SHALL be marked possible.

#### Scenario: Missing STOP
- **WHEN** a C file defines `CAN_START_SEC_CODE_ASIL_D_GLOBAL` and includes `Can_MemMap.h` but never defines `CAN_STOP_SEC_CODE_ASIL_D_GLOBAL`
- **THEN** the result reports the missing STOP with the file and line of the START

#### Scenario: Template files skipped
- **WHEN** an added directory contains the template `Can_PBcfg.c` with `CAN_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED`
- **THEN** the template is not scanned, and the sections are taken from the generated `Can_PBcfg.c` in the generation output directory

### Requirement: Used Sections Must Be Mapped
The check SHALL read the MemMap headers in the added header directories, where a mapping is a `#if defined` or `#elif defined <X>_START_SEC_<Y>` followed by `MEMMAP_START_TEXT`, `MEMMAP_START_RODATA`, `MEMMAP_START_DATA` or `MEMMAP_START_BSS` with an output section name. It SHALL report every used section without a mapping, as it would stop compilation with the MemMap `#error`, and every section mapped more than once.

#### Scenario: Used section without mapping
- **WHEN** generated code uses `ADC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED` and no added header maps it
- **THEN** the result reports the section as unmapped with the file and line where it is used

#### Scenario: Mapping read from the vendor header
- **WHEN** `Can_MemMap.h` maps `CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED` with `MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_core0")`
- **THEN** the section is mapped to the BSS output section `.mcal_bss_asil_d_unspecified_core0`

### Requirement: Placement Checked Against An ADS Scatter File
The check SHALL read an ADS scatter file: `#define` values, execution regions with their base address (a base relative to region `X` follows `X`), explicit `*(.name)` selectors and wildcard selectors. For each mapped output section it SHALL report whether it is explicitly placed, only caught by a wildcard matching its kind (naming the region and wildcard), or not placed at all. Other linker file formats SHALL be reported as not supported.

#### Scenario: Relative base follows its region
- **WHEN** `UNDEFINE_RAM_BSS` has the base `AlignExpr(ImageLimit(UNDEFINE_RAM_DATA), 64)` and `UNDEFINE_RAM_DATA` has the base `GMU_NORMAL` defined as `0x10000000`
- **THEN** both regions are treated as lying at `GMU_NORMAL`

#### Scenario: MCAL section only caught by a wildcard
- **WHEN** the T1 scatter file has no selector for `.mcal_bss_asil_d_unspecified_core0` and its region `UNDEFINE_RAM_BSS` contains `*(+BSS)`
- **THEN** the result reports the section as not explicitly placed and caught by `+BSS` in `UNDEFINE_RAM_BSS`

#### Scenario: Unsupported linker file
- **WHEN** the selected linker file is a GHS `.ld` file
- **THEN** the placement part is skipped and the result states that only ADS scatter files are supported

### Requirement: Region Attributes Checked From Chip Memory Regions
Using the chip `memory_regions` that contain each execution region's base, the check SHALL report a core `n` DATA or BSS section (`_CORE<n>_` or `_core<n>`) placed outside core `n` memory (a `local` region counts as the core's own) and a non-cacheable section (`NO_CACHEABLE` or `_uncached`) placed in cacheable memory. Without chip regions these checks SHALL be skipped with a note; regions still to be confirmed SHALL be named in the result.

#### Scenario: Core data in global memory
- **WHEN** `.mcal_bss_asil_d_unspecified_core0` lands in `UNDEFINE_RAM_BSS`, whose base `GMU_NORMAL` lies in the chip region `GMU_NORMAL` with no core and cacheable
- **THEN** the result reports that core 0 data is placed outside core 0 memory

#### Scenario: Chip without memory regions
- **WHEN** the project's chip has no `memory_regions`
- **THEN** the core and cache checks are skipped and the result says that the chip has no memory regions

### Requirement: Memory Map Check Settings Saved And Result Exported
The source directories, MemMap header directories and linker file SHALL be saved in the project as POSIX paths relative to the project directory, and projects without them SHALL load with none. The result SHALL be ordered by category, path and line, list the scanned directories, file counts and linker file, and be exportable as a Markdown checklist with one unchecked item per finding.

#### Scenario: Settings saved
- **WHEN** the user adds `../Mcal/Code` as a source directory and `../CommonFile/Memmap` as a header directory and saves the project
- **THEN** reopening the project shows both directories in the check settings

#### Scenario: Checklist export
- **WHEN** the user exports a result with an unmapped section and a wildcard placement
- **THEN** the file contains a `- [ ]` item for each with the section, file and line or region, grouped by category
