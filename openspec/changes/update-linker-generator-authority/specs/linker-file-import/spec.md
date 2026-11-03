## ADDED Requirements

### Requirement: Layout Imported From An ADS Linker File
The user SHALL be able to import a layout from an existing ADS scatter file as a starting point: its load regions and execution regions become regions of the configuration (window by the address a region lies at, start as after, offset or fixed address, alignment, size, kind), and each section an execution region selects by name becomes a manual placement. The import SHALL be optional: everything it gives can also be configured by hand.

#### Scenario: Regions and placements imported
- **WHEN** the user imports a file whose region `PRIVATE_BSS_CORE0` on `CPU0BTCM` selects `*(.mcal_bss_asil_d_unspecified_core0)`
- **THEN** the configuration has the region `PRIVATE_BSS_CORE0` on the window `CPU0BTCM`, and `.mcal_bss_asil_d_unspecified_core0` is placed in it by hand

#### Scenario: Start kinds
- **WHEN** the file starts one region at `AlignExpr(ImageLimit(A), 64)`, one at `GMU_NORMAL_ADDRESS+0x20000` and one at `0x30129000`
- **THEN** the imported regions start after `A`, at an offset of `0x20000` and at the fixed address `0x30129000`

#### Scenario: Limit regions are not imported
- **WHEN** the file has an empty region `PRIVATE_DATA_CORE0_LIMIT`
- **THEN** it is not imported, since the generator writes limit regions itself

### Requirement: Import Previewed And Never Overwrites
The import SHALL first show what it would add, what it would skip and what it cannot import, and SHALL change the configuration only after the user confirms. A region whose name the configuration already has and a section already placed by hand SHALL NOT be overwritten and SHALL be reported. The import SHALL NOT change the rules.

#### Scenario: Existing region kept
- **WHEN** the configuration already has `UNDEFINE_RAM_BSS` and the file has it too
- **THEN** the existing region is kept and the preview lists it as skipped

#### Scenario: Cancelled
- **WHEN** the user cancels the preview
- **THEN** the configuration is unchanged

### Requirement: What Cannot Be Imported Is Reported
Wildcard selectors, `.ANY`, selectors bound to an object file, `+First` and regions whose address lies on no chip window SHALL NOT be imported, and the preview SHALL list each with the reason. A region whose kind cannot be inferred SHALL be imported marked to be confirmed.

#### Scenario: Wildcard selector
- **WHEN** a region selects `*(+BSS)`
- **THEN** no placement is made from it and the preview says that a wildcard selector is not imported

#### Scenario: Selector bound to a file
- **WHEN** a region selects `exception.o(.IRQ_init_vector)`
- **THEN** no placement is made from it and the preview names the selector

#### Scenario: Kind not inferred
- **WHEN** a region has selectors from which no kind can be told
- **THEN** it is imported marked to be confirmed
