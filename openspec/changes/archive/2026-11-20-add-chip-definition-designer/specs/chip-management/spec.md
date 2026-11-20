## ADDED Requirements

### Requirement: Pinout Table Import from Excel and CSV
The system SHALL support importing pinout and alternate function definitions from Excel (`.xlsx`) and CSV files into a structured chip definition model.

#### Scenario: Import pinout from Excel spreadsheet
- **WHEN** the user provides an Excel file containing columns for Port, Pin, Pin Name, and Alternate Functions
- **THEN** `PinoutTableImporter` parses the rows, detects column headers, and constructs a port-to-pin mapping with multiplexing functions
- **AND** any unmapped or malformed rows are reported gracefully without crashing

### Requirement: Chip Definition Serialization and Export
The system SHALL support exporting chip definitions to standard YAML schema in `data/chips/` and to EB Tresos compatible `.properties` files.

#### Scenario: Export chip definition to YAML and properties
- **WHEN** a valid chip definition is exported
- **THEN** the exporter generates a YAML file matching the schema used by `ChipDatabase`
- **AND** it optionally generates a `.properties` file containing resource counts (cores, CAN modules, ADC units) and port pin mode definitions

### Requirement: Graphical Chip Definition Designer
The UI SHALL provide a multi-tab graphical designer dialog for authoring, editing, cloning, and reviewing MCU chip definitions.

#### Scenario: Authoring a new chip variant with clone and save
- **WHEN** the user opens the Chip Definition Designer and clones an existing chip
- **THEN** the dialog populates all fields, peripheral counts, and pin multiplexing tables
- **AND** the user can modify parameters, add or delete pins, import new pinout data, and save the result directly into the active chip database
