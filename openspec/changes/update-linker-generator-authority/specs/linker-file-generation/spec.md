## ADDED Requirements

### Requirement: Execution Region Start Is Configurable
An execution region SHALL start, at the user's choice, after the previous region of its window (the default; the first region of a window starts at the window's base), at the window's base plus an offset, or at a fixed address. A fixed address outside the region's window SHALL be warned about and SHALL NOT stop generation.

#### Scenario: Offset from the window base
- **WHEN** `UNDEFINE_RAM_DATA` lies on `GMU_NORMAL` with an offset of `0x20000`
- **THEN** the generated ADS file starts it at `GMU_NORMAL_ADDRESS+0x20000`

#### Scenario: Fixed address
- **WHEN** `CORE0_USER_STACK` has the fixed address `0x30129000`
- **THEN** the generated file defines that address and starts the region there, and the stacks that follow it start after it

#### Scenario: Address outside the window
- **WHEN** a region on `CPU0BTCM` has the fixed address `0x10000000`
- **THEN** the check before generating warns that the address is outside the window and generation goes ahead

### Requirement: Execution Region Size Is Configurable
An execution region MAY have a size: the upper bound of a region that takes sections, the length of a stack or reserved region. Without one, the window's size SHALL be the upper bound and a stack SHALL be `0x1000` long.

#### Scenario: Stack size
- **WHEN** `CORE0_IRQ_STACK` has the size `0x2000`
- **THEN** the generated file writes it as `EMPTY 0x2000`

#### Scenario: No size given
- **WHEN** a data region has no size
- **THEN** its upper bound is the size of its window

### Requirement: Several Load Regions
The configuration SHALL hold an ordered list of load regions, each with a name, a window and an upper bound, and each execution region SHALL belong to one of them, the first by default. With no load region configured, one load region `ROM_CODE` on the first flash window SHALL be generated, as before.

#### Scenario: A second load region for data flash
- **WHEN** the configuration has the load regions `ROM_CODE` on `CPUXPFLASH0` and `DFLASH_CODE` on `DFLASH_NORMAL`, and `DFLASH_DATA` belongs to `DFLASH_CODE`
- **THEN** the generated file has two load regions, with `DFLASH_DATA` inside the second

#### Scenario: Older configuration
- **WHEN** a configuration written before this change is generated
- **THEN** the output has one load region `ROM_CODE`, and apart from the limit region alignment it is byte for byte what it was

### Requirement: Limit Region Alignment Is Configurable
The limit region of an execution region SHALL be aligned to the region's limit alignment, 64 by default.

#### Scenario: Default
- **WHEN** a stack region with alignment 8 needs a limit region and has no limit alignment set
- **THEN** its limit region is written with `AlignExpr(ImageLimit(<name>), 64)`

### Requirement: The Configuration Is The Source Of The Linker File
The generated linker file SHALL follow the configuration only. No vendor linker file SHALL be needed to generate, and none SHALL be used to judge the result; the check after generating SHALL say that it shows the configuration and the file agree.

#### Scenario: No vendor file
- **WHEN** a project has no vendor linker file and the user configures the layout by hand
- **THEN** a linker file is generated from the configuration alone
