## ADDED Requirements

### Requirement: Unified Derived-Field Sync From ECU Resources
The system SHALL provide a single-pass synchronization operation that updates a chip definition's derived views (`metadata.cores`, `resources`, and `ports`) from its authoritative `ecu_resources`, leaving any derived section unchanged when `ecu_resources` does not supply data for that section.

#### Scenario: One-click sync updates cores, peripherals, and pins together
- **WHEN** a chip has `ecu_resources` defining core counts, peripheral hardware units, and `Port.AvailablePortsID` / pin lists, and the user triggers unified ECU synchronization in the Chip Definition Designer
- **THEN** `metadata.cores`, `resources`, and `ports` are all updated in one step from `ecu_resources` and the UI reflects the synchronized values across tabs

#### Scenario: Partial ECU resources preserve unaffected derived sections
- **WHEN** a chip has only `OsResource.NumOfCores` in `ecu_resources` (no Port or peripheral keys) and unified ECU synchronization runs
- **THEN** `metadata.cores` is updated while existing `ports` and `resources` remain unchanged

### Requirement: Batch Confirmation of Unconfirmed Chip Metadata in Designer
The Chip Definition Designer SHALL allow users to review and confirm `metadata.unconfirmed` entries directly inside the designer without switching to `ChipRepairWizard`, while rejecting confirmation of entries still marked `待填写` whose values remain empty.

#### Scenario: Confirming non-empty unconfirmed items clears their marks on save
- **WHEN** a chip has non-empty fields listed under `metadata.unconfirmed` (such as `memory_regions` or `ports`) and the user checks them in the designer's batch confirmation dialog and saves
- **THEN** the confirmed keys are removed from `metadata.unconfirmed` in the saved chip YAML

### Requirement: Built-in Chip Library Excludes Stray Copy Artifacts
The built-in `data/chips/` directory SHALL NOT contain temporary `*_COPY.yaml` test artifacts.

#### Scenario: SC300_COPY is absent from the chip library
- **WHEN** the built-in `ChipDatabase` loads `data/chips/`
- **THEN** `SC300_COPY` is not present in `list_chips()`
