# Implementation Tasks

- [x] 1. Core Services & Importers
  - [x] 1.1 Implement `PinoutTableImporter` supporting `.xlsx` (via openpyxl) and `.csv` with auto-column matching
  - [x] 1.2 Implement `ChipDefinitionExporter` for YAML and Tresos `.properties` serialization
  - [x] 1.3 Add unit tests for pinout table importing and chip definition export
- [x] 2. UI Components & Dialog
  - [x] 2.1 Implement `ChipDefinitionDesignerDialog` with 4 tabs: Basic Info, Peripherals, Pinout Matrix, Preview & Export
  - [x] 2.2 Implement "Clone from Existing Chip" functionality
  - [x] 2.3 Implement Excel/CSV file picker and pinout table loader
  - [x] 2.4 Implement live YAML and `.properties` preview with syntax styling
- [x] 3. Toolchain & Menu Integration
  - [x] 3.1 Add `Tools -> Chip Definition Designer...` action in `DaVinciMainWindow`
  - [x] 3.2 Add `+ New Chip Definition...` button in `HardwareMappingWizard` (ChipSelectionPage)
  - [x] 3.3 Ensure saving dynamically registers the new chip into `ChipDatabase` and UI dropdowns
- [x] 4. Validation & Verification
  - [x] 4.1 Run unit tests and verify end-to-end chip creation, saving, and selection
  - [x] 4.2 Validate OpenSpec strict compliance
