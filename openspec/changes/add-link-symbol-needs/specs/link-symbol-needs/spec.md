## ADDED Requirements

### Requirement: Link Symbol Needs Read From Code
The system SHALL read the linker symbols that source and generated code refer to by region name, from the added source directories and the generation output directory, skipping files containing template syntax `[!` and text inside comments, and SHALL NOT change any file. It SHALL recognise the startup macros and the direct ADS and GHS symbols listed in the design.

#### Scenario: Copy and clear macros
- **WHEN** `startup.c` contains `STARTUP_GETCOPYDATAINFO(UNDEFINE_RAM_DATA, (globalData))` and `STARTUP_GETBSSDATAINFO(UNDEFINE_RAM_BSS, (globalBss))`
- **THEN** the region `UNDEFINE_RAM_DATA` is needed for copy with its file and line, and `UNDEFINE_RAM_BSS` for clear

#### Scenario: Direct ADS symbol in generated OS code
- **WHEN** a generated `Os_link_Lcfg.c` contains `extern uint32 Image$$OS_DATA_CORE0$$Base;` and `extern uint32 Image$$OS_DATA_CORE0_LIMIT$$Base;`
- **THEN** the region `OS_DATA_CORE0` is needed for base and limit, with those lines as sources

#### Scenario: Reference in a comment or template
- **WHEN** a macro call appears inside a comment, or the file contains `[!`
- **THEN** it is not recorded

### Requirement: Uses And Sources Recorded Per Region
For each region name the system SHALL record the set of uses (copy, clear, base, limit, load address, stack top) and every place the region is referenced. Each recognised macro and symbol SHALL map to one fixed use, as listed in the design.

#### Scenario: Several uses merge
- **WHEN** one region is referenced once for base and once for limit
- **THEN** the result has one entry for the region with both uses and both source places

#### Scenario: Stack macros
- **WHEN** `startup.c` contains `STARTUP_SETSTACK(MODE_SYS, CORE0_USER_STACK)` or `STARTUP_SETHYPMODESP(CORE0_HYP_STACK)`
- **THEN** the regions `CORE0_USER_STACK` and `CORE0_HYP_STACK` are needed as a stack top

#### Scenario: Macro and symbol give the same use
- **WHEN** `startup.c` calls `STARTUP_GETIMAGELIMITADDR(PRIVATE_DATA_CORE0, x)` and generated code refers to `Image$$PRIVATE_DATA_CORE0_LIMIT$$Base`
- **THEN** both are recorded as a limit of `PRIVATE_DATA_CORE0`

#### Scenario: Load address
- **WHEN** code refers to `Load$$OS_DATA_CORE0$$Base` or `__OS_DATA_CORE0_LOAD_ADDRESS_START`
- **THEN** the region `OS_DATA_CORE0` is needed for its load address

### Requirement: Compiler Symbol Convention In One Place
The mapping from a use to the linker symbol it needs SHALL be defined in one place for each supported compiler (ADS and GHS), and SHALL be the source both for recognising direct symbols and for later generation of linker files. A GHS limit symbol, which is the same for copy and clear regions, SHALL be recorded as a limit without telling the two apart.

#### Scenario: Same macro, two compilers
- **WHEN** the region `PRIVATE_DATA_CORE0` is needed for copy
- **THEN** the convention gives `Image$$PRIVATE_DATA_CORE0$$Base`, `Image$$PRIVATE_DATA_CORE0_LIMIT$$Base` and `Load$$PRIVATE_DATA_CORE0$$Base` for ADS, and `__PRIVATE_DATA_CORE0_ADDRESS_START`, `__PRIVATE_DATA_CORE0_ADDRESS_END` and `__PRIVATE_DATA_CORE0_LOAD_ADDRESS_START` for GHS

### Requirement: Needed Regions Checked Against An ADS Scatter File
Against an ADS scatter file the check SHALL report a needed region that is not an execution region of the file, and a region needed for a limit that has no execution region named `<R>_LIMIT`, except regions needed only as a stack top. References inside a conditional branch SHALL be marked possible. Execution regions of the file that no code refers to SHALL NOT be reported as problems.

#### Scenario: Region missing from the linker file
- **WHEN** `startup.c` needs `LMU2_CACHED_DATA` and the scatter file has no execution region of that name
- **THEN** the result reports the missing region with the use and the file and line of the reference

#### Scenario: Limit region missing
- **WHEN** `PRIVATE_DATA_CORE0` is needed for a limit and the scatter file has `PRIVATE_DATA_CORE0` but no `PRIVATE_DATA_CORE0_LIMIT`
- **THEN** the result reports the missing limit region

#### Scenario: Stack region needs no limit region
- **WHEN** `CORE0_USER_STACK` is needed only as a stack top and the scatter file has it declared with `EMPTY` and no `CORE0_USER_STACK_LIMIT`
- **THEN** nothing is reported for it

#### Scenario: Unreferenced region
- **WHEN** the scatter file has an execution region that no code refers to
- **THEN** it is not reported as a problem

### Requirement: Needs Shown In The Layout View And Export
The memory layout view SHALL show on each execution region which code refers to it and for which uses, SHALL list needed regions missing from the linker file as a separate group, and SHALL mark execution regions no code refers to. The Markdown export SHALL include the same information.

#### Scenario: Region with references
- **WHEN** the view shows the execution region `UNDEFINE_RAM_DATA` that `startup.c` needs for copy
- **THEN** the region row shows that it is referenced for copy and where

#### Scenario: Missing region listed apart
- **WHEN** `LMU2_CACHED_DATA` is needed but not in the scatter file
- **THEN** the view lists it in a separate group of missing regions with its references

### Requirement: Needs Read Without An ADS Linker File
The needs SHALL be read and shown whether or not an ADS scatter file is set. When there is none, or it is another format, the comparison SHALL be skipped and the result SHALL say so.

#### Scenario: No linker file
- **WHEN** no linker file is set
- **THEN** the needed regions are listed, no missing-region findings are made, and the result states that the comparison was skipped
