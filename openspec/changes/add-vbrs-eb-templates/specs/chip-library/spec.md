## ADDED Requirements

### Requirement: Chip Data Carries Start-Up Code Facts
The chip data SHALL be able to give a chip's Vector derivative id, its core type, its maximum CPU frequency, and for each memory window its ECC granularity and whether, and by which core, the window is block-initialised at start-up. The THA6206 data SHALL give `Tongxin_THA6206`, `CORTEX_R52` and 400 MHz. Its TCM windows SHALL have ECC granularity 8. Its other RAM windows SHALL have 4 and be listed as unconfirmed. Its block-init windows SHALL follow the vendor start-up code's ITMU list.

#### Scenario: THA6206 frequency
- **WHEN** the THA6206 chip data is loaded
- **THEN** the maximum CPU frequency is 400000000 Hz

#### Scenario: Unconfirmed granularity flagged
- **WHEN** the THA6206 chip data is loaded
- **THEN** the LMU windows' ECC granularity is 4 and appears in the unconfirmed list

#### Scenario: Field absent on another chip
- **WHEN** a chip without a core type is loaded
- **THEN** the chip loads, and the core type is reported as missing rather than invented
