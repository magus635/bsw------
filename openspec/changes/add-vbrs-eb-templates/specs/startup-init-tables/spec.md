## ADDED Requirements

### Requirement: Init Tables Generated From The Linker Plan
The linker file generator SHALL generate `vLinkGen_Cfg.h`, `vLinkGen_Lcfg.h` and `vLinkGen_Lcfg.c` from the same linker plan and the same per-compiler label table as the linker file. The files SHALL declare vLinkGen version 2.19, the `vLinkGen_MemArea`/`vLinkGen_RamMemArea` types, every table and set the Vector start-up code reads, each table's count including its terminating empty entry, and an empty table as a single `{0u,0u,0u,0u}` entry. Entries SHALL be sorted by region name.

#### Scenario: Same structure as vLinkGen
- **WHEN** the files are generated for any layout
- **THEN** their types, version macros, table and set names, count macros and empty-table form match the StartApplication sample line by line

#### Scenario: Deterministic
- **WHEN** the files are generated twice from the same layout
- **THEN** the two outputs are identical

### Requirement: Init Table Entry Kinds Cover All Start-Up Memory Work
The system SHALL write:
- a copy (Init) entry for every region whose execution address differs from its load address, whether code or data;
- a zero (ZeroInit) entry for every bss region and for the ZI part of a data region;
- no entry for noinit and stack regions or for code and constants executed in place.

It SHALL refuse to generate, naming the region, when an RW, ZI or copied region has no entry.

#### Scenario: Shared bss
- **WHEN** `GLOBAL_UNCACHED_BSS` lies on an LMU window
- **THEN** the stage-One ZeroInit table has one entry for it, owned by the start-up core

#### Scenario: Region left out
- **WHEN** a data region would get no entry because of an override
- **THEN** generation is refused and the reason names the region

### Requirement: Init Table Entry Owner And Stage
A region on a core-private window SHALL belong to that core. A region on a core-local alias window SHALL get one entry per core with the same addresses. Any other region SHALL belong to the start-up core. The init stage SHALL default to ONE. Stage and owning core SHALL be overridable per region in the memory layout configuration, and configurations without these fields SHALL load unchanged.

#### Scenario: Clone code copied on every core
- **WHEN** `CODE_CLONE` runs from the core-local alias ATCM window and is loaded from flash, on a two-core chip
- **THEN** the stage-One Init table has two `CODE_CLONE` entries, for core 0 and core 1

#### Scenario: Stage overridden
- **WHEN** a bss region's init stage is set to HARD_RESET_ONLY in the layout configuration
- **THEN** its entry is in the HardReset ZeroInit table and not in the One table

### Requirement: ECC Memory Cleared Through Early Blocks
For every chip window the chip data marks for block initialisation, the system SHALL write an Early zero-init block entry covering the whole window, owned by the core the chip data names, with that window's ECC alignment. Windows not marked SHALL NOT get a block entry. The One and HardReset block tables SHALL be empty.

#### Scenario: THA6206 TCMs
- **WHEN** the THA6206 layout is generated
- **THEN** the Early block table has, for each core, entries for that core's ATCM, BTCM0, BTCM1 and CTCM with alignment 8, and core 0 also has entries for LMU1, LMU2 and LMU3

### Requirement: Init Entry Alignment From The ECC Granularity
An Early block entry's alignment SHALL be the ECC granularity of its window, as given by the chip data. A group entry on a block-initialised window SHALL have alignment 4. The memory layout configuration MAY override a group entry's alignment to 0 or 4; any other value SHALL be refused, and the region's linker alignment SHALL NOT be used instead.

#### Scenario: TCM block
- **WHEN** CPU0's BTCM is block-initialised and has ECC granularity 8
- **THEN** its Early block entry has alignment 8, and the zero entry of `PRIVATE_BSS_CORE0` on that window has alignment 4

#### Scenario: Invalid override
- **WHEN** a region's alignment is overridden to 16
- **THEN** generation is refused and the reason names the region

### Requirement: No 8-Byte Group Loop Past A Region End
A group entry on a window with ECC granularity 8 that is not block-initialised SHALL be refused, because an 8-byte loop can write up to 4 bytes past a region end that is not 8-byte aligned.

#### Scenario: Unsafe 8-byte group
- **WHEN** a bss region lies on a window with ECC granularity 8 that is not block-initialised
- **THEN** generation is refused and the reason names the region and the window

### Requirement: Start-Up Stack Region Per Core
The memory layout SHALL have, for each core the Os maps, a `STACK_C<n>` start-up stack region in that core's TCM, and `_STACK_C<n>_LIMIT` SHALL resolve to its limit. The system SHALL refuse to generate when one is missing or smaller than six mode stacks plus the configured margin.

#### Scenario: Stack too small
- **WHEN** `STACK_C0` is smaller than six mode stacks plus the margin
- **THEN** generation is refused and the reason names `STACK_C0`

### Requirement: Vector Region Named Per Core
The memory layout configuration SHALL name, for each core the Os maps, the region holding its exception vector table (default `OS_EXCVEC_CORE<n>_CODE`), and `_OS_EXCVEC_CORE<n>_CODE_START` SHALL resolve to that region's base. The system SHALL refuse to generate when the named region does not exist.

#### Scenario: Shared vector table
- **WHEN** both cores name `INT_VECTOR_TABLE` as their vector region
- **THEN** `_OS_EXCVEC_CORE0_CODE_START` and `_OS_EXCVEC_CORE1_CODE_START` both resolve to the base of `INT_VECTOR_TABLE`

### Requirement: ADS Init Entry Symbols
For ADS, a copy entry SHALL span `Image$$<R>$$Base` to `Image$$<R>$$ZI$$Base`, loaded from `Load$$<R>$$Base` to `Load$$<R>$$Limit`, and SHALL NOT end at `Image$$<R>$$Limit`, which includes the ZI part. A zero entry SHALL span `Image$$<R>$$ZI$$Base` to `Image$$<R>$$ZI$$Limit`.

#### Scenario: Copy entry under ADS
- **WHEN** the ADS init tables are generated for the data region `PRIVATE_DATA_CORE0`
- **THEN** its Init entry is `Image$$PRIVATE_DATA_CORE0$$Base`, `Image$$PRIVATE_DATA_CORE0$$ZI$$Base`, `Load$$PRIVATE_DATA_CORE0$$Base`, `Load$$PRIVATE_DATA_CORE0$$Limit`

### Requirement: ADS Label Mapping And Link Options
The labels the static code names (`_STACK_C<n>_LIMIT`, `_OS_EXCVEC_CORE<n>_CODE_START`) SHALL be mapped to armlink symbols in a generated file the link uses, by the mechanism the feasibility spike confirmed. The generated scatter file and the generation report SHALL state that the image must be linked with `--datacompressor=off` and started without `__scatterload`.

#### Scenario: Link option stated
- **WHEN** the ADS scatter file is generated together with init tables
- **THEN** the scatter file comment and the generation report both name `--datacompressor=off`
