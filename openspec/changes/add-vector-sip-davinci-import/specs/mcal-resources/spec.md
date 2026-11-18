## ADDED Requirements

### Requirement: EB MCAL autosar/ ARXML Parsing

The system SHALL parse EB plugin `autosar/<Module>_<Chip>.arxml` files to extract chip-specific ECU resources.

#### Scenario: Parse Port resources from EB plugin

- **WHEN** loading an EB MCAL plugin (e.g., `Def/plugins/Port_THA6_AS440`)
- **AND** the plugin contains `autosar/Port_THA6206_LFBGA292.arxml` with `ECUC-MODULE-DEF` elements
- **THEN** the system parses the file to extract:
  - `Port.AvailableEXTIModule` (list of EXTI module names)
  - `Port.AvailableEXTIModuleNodeNumber` (corresponding node numbers)
  - `Port.AvailableGTMModule` (GTM module names)
  - `Port.AvailableGTMModuleNodeNumber` (corresponding node numbers)
  - `Port.AvailableIOMPINModule`, `Port.AvailableIOMPINModuleNodeNumber`
  - `Port.AvailablePSI5Module`, `Port.AvailablePSI5ModuleNodeNumber`
  - `Port.AvailablePortsID` (list of available port identifiers: P00, P01, ..., P40)

#### Scenario: Identify chip from filename

- **WHEN** encountering `autosar/Port_THA6206_LFBGA292.arxml`
- **THEN** the system extracts chip identifier `THA6206_LFBGA292` from the filename
- **AND** associates extracted resources with that chip in the database

### Requirement: ECU Resource Extraction and Merging

The system SHALL extract ECU resources from `autosar/*.arxml` and merge them into the tool's chip database.

#### Scenario: Add Port resources to chip YAML

- **WHEN** Port resources are extracted from `autosar/Port_THA6206_LFBGA292.arxml`
- **THEN** the system updates `autosar_configurator/data/chips/THA6206_LFBGA292.yaml` with the new resources under the `Port` key
- **AND** preserves existing chip data (memory regions, CPU config, etc.)

#### Scenario: Record source for traceability

- **WHEN** extracting ECU resources from an ARXML file
- **THEN** each resource includes a `_source` field with the path to the originating ARXML file
- **EXAMPLE**:
  ```yaml
  Port:
    AvailableEXTIModule: [EXTI0, EXTI1, EXTI2, EXTI3]
    _source: "Def/plugins/Port_THA6_AS440/autosar/Port_THA6206_LFBGA292.arxml"
  ```

### Requirement: Resource Conflict Detection

The system SHALL detect conflicting ECU resources from multiple sources.

#### Scenario: Duplicate resource with same value

- **WHEN** two `autosar/*.arxml` files for the same chip define the same resource (e.g., `Port.AvailableEXTIModule`) with identical values
- **THEN** the system accepts the first and logs a debug message: "Duplicate resource Port.AvailableEXTIModule from <file2>, matches existing"

#### Scenario: Duplicate resource with different value

- **WHEN** two files define the same resource with different values
- **THEN** the system raises `ResourceConflictError` naming the resource, both values, and both source files
- **AND** does not silently overwrite

### Requirement: Elimination of Startup Warnings

The system SHALL eliminate all chip resource warnings after MCAL import.

#### Scenario: Port warnings resolved

- **WHEN** user imports a DaVinci project with EB MCAL (including Port)
- **AND** the `autosar/Port_THA6206_LFBGA292.arxml` is parsed and merged
- **THEN** on next application startup with that project:
  - No warnings about missing `Port.AvailableEXTIModule`
  - No warnings about missing `Port.AvailableGTMModule`
  - No warnings about missing `Port.AvailableIOMPINModule`
  - No warnings about missing `Port.AvailablePSI5Module`
  - No warnings about missing `Port.AvailablePortsID` entries (P10-P15, P20-P23, P32-P34, P40)

#### Scenario: Other MCAL resources extracted

- **WHEN** importing other MCAL modules (Adc, Can, Dio, Fls, Gpt, Icu, Mcu, Pwm, Spi, Wdg)
- **THEN** the system extracts any chip-specific ECU resources defined in their respective `autosar/*.arxml` files
- **AND** merges them into the chip database with source traceability

### Requirement: Backward Compatibility

The system SHALL not break existing projects or EB plugin loading.

#### Scenario: Existing EB import still works

- **WHEN** user opens an existing format-7 or format-8 project with EB MCAL modules
- **THEN** the project loads correctly
- **AND** MCAL modules are configured as before
- **AND** `autosar/*.arxml` resource extraction runs if the files exist

#### Scenario: Plugin without autosar/ directory

- **WHEN** loading an EB plugin that has no `autosar/` subdirectory
- **THEN** the system continues without error
- **AND** logs a debug message: "No autosar/ directory found in <plugin>"

### Requirement: Resource Validation

The system SHALL validate extracted resources before merging.

#### Scenario: Resource type validation

- **WHEN** extracting a list resource (e.g., `AvailablePortsID`) from an ARXML
- **THEN** the system verifies each element is a valid identifier (non-empty string)
- **AND** rejects invalid entries with a warning

#### Scenario: Required resource presence

- **WHEN** Port module is imported but `autosar/Port_<chip>.arxml` is missing key resources
- **THEN** the system logs warnings for each missing resource
- **AND** does not prevent loading, but startup warnings remain

### Requirement: CLI Support for Resource Extraction

The system SHALL provide a CLI command to extract and merge MCAL resources without a full import.

#### Scenario: Standalone resource extraction

- **WHEN** user runs `python -m autosar_configurator.tools.extract_mcal_resources --eb-plugins-dir D:\Mcal\Def\plugins --chip THA6206_LFBGA292`
- **THEN** the tool scans all plugins for `autosar/*_THA6206_LFBGA292.arxml`
- **AND** extracts ECU resources for each MCAL module
- **AND** updates `autosar_configurator/data/chips/THA6206_LFBGA292.yaml`
- **AND** writes a summary report listing extracted resources and their sources
