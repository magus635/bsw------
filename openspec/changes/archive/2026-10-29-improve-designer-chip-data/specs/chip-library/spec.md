## ADDED Requirements

### Requirement: New Chip Basic Data Not Invented
A chip created in the designer SHALL NOT receive invented values for its CPU frequency, flash size or RAM size. A field left empty SHALL be left out of the chip file and marked `待填写` under `metadata.unconfirmed`; the mark SHALL be removed automatically once the field has a value.

#### Scenario: Saved with the fields empty
- **WHEN** a new chip is saved without a CPU frequency, flash size or RAM size
- **THEN** its file has none of the three fields, `metadata.unconfirmed` marks each of them `待填写`, and the chip is reported as incomplete

#### Scenario: Filled in later
- **WHEN** the flash size of that chip is entered and the chip is saved
- **THEN** the `待填写` mark of `metadata.flash_size` is gone and the other two marks remain
