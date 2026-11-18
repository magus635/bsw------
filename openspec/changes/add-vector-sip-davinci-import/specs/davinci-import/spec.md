## ADDED Requirements

### Requirement: DaVinci XML Project Parsing

The system SHALL parse DaVinci XML `.dpa` files (format `<ProjectAssistant Version=...>`) and extract project metadata.

#### Scenario: Parse DaVinci project XML

- **WHEN** user selects a DaVinci XML `.dpa` (e.g., `StartApplication.dpa` with `<ProjectAssistant Version="5.30.35 SP2">`)
- **THEN** the tool reads and extracts:
  - `<SIP>` path (relative to `.dpa` directory, resolved to absolute)
  - `<Derivative>` name and UUID
  - `<Folders>` (ECUC, GenData, Source, etc.)
  - `<Input>` SystemExtract paths (recorded but not parsed)
  - `<EcucSplitter>` module-to-file mapping
  - `<ECUC><Active>` the active `ECUC-VALUE-COLLECTION` and `<ModuleDefinitionMappings>`

#### Scenario: Extract module list and active modules

- **WHEN** parsing `<EcucSplitter>` and `<ECUC><Active>`
- **THEN** the tool builds a list of 28 BSW modules in the project
- **AND** identifies which modules are actively configured (via `<Active><ModuleRef>`)
- **AND** maps each module to its definition file (via `<ModuleDefinitionMappings>`)

### Requirement: DaVinci Project Import to Format 8

The system SHALL import a DaVinci project into a format-8 JSON `.dpa` with module packages, BSW definitions, and MCAL configuration.

#### Scenario: Import BSW modules from DaVinci

- **WHEN** user invokes "Import DaVinci Project" and provides:
  - DaVinci `.dpa` path (e.g., `D:\davinci\mcuapp\Applications\SipAddon\StartApplication\StartApplication.dpa`)
  - SIP module library path (ingested by tool, e.g., `D:\prj\sip_lib`)
  - Target project directory (new directory for the format-8 project)
- **THEN** the tool:
  1. Parses the DaVinci `.dpa` and extracts metadata (derivative UUID, folder paths, etc.)
  2. Reads each `*_ecuc.arxml` in `<ECUC><Active>` (28 files in the sample)
  3. Binds each module to a definition from the SIP library by `DEFINITION-REF` path
  4. Imports all container/parameter values into the format-8 project
  5. Writes a new `<project-name>.dpa` (JSON format_version 8) to the target directory
  6. Preserves original DaVinci project directory untouched

#### Scenario: EB MCAL module selection and import

- **WHEN** importing a DaVinci project whose `<ECUC><Active>` includes MCAL modules (Can, Dio, Mcu, Port, Resource, Spi with paths like `/THA6_AS440_FuSa/<Module>`)
- **AND** the user provides an EB MCAL configuration directory (e.g., `TresosMcalProject/THA6206_LFBGA292_AS440/config`)
- **THEN** the tool:
  1. Imports the EB MCAL modules using the existing EB import flow (Phase 1)
  2. **Skips** reading MCAL values from DaVinci ARXMLs (use EB config directory as the source)
  3. Verifies that BSW modules can resolve their MCAL references (e.g., EcuC → Can, Port)
  4. Lists skipped DaVinci MCAL modules in the import report

#### Scenario: Resolve cross-module references

- **WHEN** a BSW module (e.g., Com) has references to other modules (e.g., PduR, CanIf)
- **THEN** after import, the tool resolves all references in the format-8 project
- **AND** reports any unresolved references in the import report

### Requirement: EB MCAL Directory Selection

The system SHALL prompt the user to specify the EB MCAL configuration directory and offer auto-detected candidates.

#### Scenario: Auto-detect MCAL directories

- **WHEN** user imports a DaVinci project
- **AND** the tool scans the DaVinci project directory and common sibling locations for EB MCAL directories
- **THEN** the tool suggests candidate directories (e.g., `TresosMcalProject/THA6206_LFBGA292_AS440/config`)
- **AND** displays each candidate with its detected modules (Adc, Can, Dio, etc.)

#### Scenario: User confirms MCAL directory

- **WHEN** the tool presents the list of candidates
- **THEN** user selects one or browses to a custom directory
- **AND** the tool uses that directory for MCAL import

### Requirement: Import Report

The system SHALL produce a detailed import report accounting for every module, container, parameter, and reference.

#### Scenario: Import report structure

- **WHEN** import completes (successfully or with warnings)
- **THEN** the tool writes a Markdown report to `<target-project>/.import_report.md` with:
  - Import timestamp and source/target paths
  - Per-module statistics: number of containers, parameters, references
  - Derivative UUID and SIP module library used
  - List of BSW modules imported with definition resolution status
  - List of MCAL modules skipped (with reason) and their EB configuration source
  - List of unresolved references (with module path and target path)
  - List of dropped content (if any) with reason
  - Warnings (e.g., missing Pre/Rec references, version mismatches)

#### Scenario: No silent data loss

- **WHEN** a configuration value from DaVinci cannot be imported (e.g., unsupported definition type)
- **THEN** the value is listed in the report under "Dropped content"
- **AND** import does not silently discard it

#### Scenario: Cross-module reference validation

- **WHEN** the report lists unresolved references
- **THEN** user can inspect each one and decide whether to:
  - Acknowledge it as acceptable (missing optional module)
  - Re-run import with a different MCAL directory
  - Manually add the missing module

### Requirement: UI Integration

The system SHALL add an "Import DaVinci Project" command to the File menu.

#### Scenario: Import menu entry

- **WHEN** user opens the application
- **THEN** File menu contains "Import DaVinci Project..." entry (after "Open Project")

#### Scenario: Import workflow in UI

- **WHEN** user clicks "Import DaVinci Project..."
- **THEN** the application shows a wizard or dialog sequence:
  1. Select DaVinci `.dpa` file (file picker, filter `.dpa` or all files)
  2. Select or confirm SIP library directory
  3. Select or confirm EB MCAL configuration directory
  4. Select target directory for new format-8 project
  5. Review summary and click "Import"
  6. Show progress and final report in a dialog with a link to the full report file

### Requirement: Derivative UUID Recording

The system SHALL record the derivative UUID and name in the format-8 project for future updates.

#### Scenario: Derivative info in project

- **WHEN** import completes
- **THEN** the format-8 `.dpa` contains:
  - `derivative_uuid`: "B632B9EE-F23D-43CD-9C54-542178A058D9"
  - `derivative_name`: "Tongxin_THA6206"
- **AND** future operations (e.g., adding modules from the SIP library) use this UUID to select correct definitions

### Requirement: Pre-Configuration Handling

The system SHALL recognize and apply Pre configurations imported from DaVinci as read-only values.

#### Scenario: BSW module with Pre configuration

- **WHEN** a BSW module (e.g., vBRS) is imported with Pre values from DaVinci
- **THEN** those values are classified as `origin=PRE` in the baseline (Phase 1 semantics)
- **AND** are marked read-only until the user unlocks them individually
- **AND** appear with a lock icon in the UI

#### Scenario: Pre values persist on save

- **WHEN** user saves the project
- **THEN** Pre values are written to the configuration file
- **AND** remain editable only after explicit unlock

### Requirement: Validation and Error Reporting

The system SHALL validate the import and report all errors clearly.

#### Scenario: Missing definitions

- **WHEN** a module in DaVinci has `DEFINITION-REF` that cannot be resolved in the SIP library
- **THEN** the import fails with error: "Module <name> definition not found: <ref>"
- **AND** user is prompted to re-run ingestion or select a different SIP library

#### Scenario: Empty DaVinci ECUC

- **WHEN** DaVinci `.dpa` has no `<ECUC><Active>` or is empty
- **THEN** import succeeds but creates a format-8 project with no modules
- **AND** report notes: "No modules found in active ECUC"

#### Scenario: MCAL directory validation

- **WHEN** user selects an EB MCAL directory that contains no valid `config/*.xdm` files
- **THEN** the tool warns: "No MCAL configuration found in <dir>"
- **AND** allows user to retry or skip MCAL import
