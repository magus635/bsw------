## ADDED Requirements

### Requirement: vBRS Files Generated From An EB Template Pack
The system SHALL generate `vBrsCfg.h`, `vBrs_Lcfg.h`, `vBrs_Lcfg.c` and `Makefile.config.generated`, under exactly those file names, from EB templates in the `template_packs/vBRS/` template pack when the project uses that pack as a template directory and has a vBRS module. The system SHALL NOT ship the pack as a built-in default template.

#### Scenario: Pack not selected
- **WHEN** the project does not use the vBRS template pack
- **THEN** no vBRS file is generated

### Requirement: vBRS Inputs From The Tool's Own Data
The vBRS templates SHALL take the vBRS configuration, the chip data (derivative id, core type, maximum frequency, core count), the Os core mapping (`OsCoreIdMappingConfig`, `OsApplicationCoreRef`) and the size of each core's start-up stack region in the memory layout.

#### Scenario: Sample configuration
- **WHEN** a THA6206 project has the vBRS values of the StartApplication sample, two Os cores mapped to physical cores 0 and 1, and `STACK_C0`/`STACK_C1` of 1024 bytes
- **THEN** the four files are generated and `vBrs_Lcfg.c` lists two cores with `StartupStackSize` 1024

### Requirement: vBRS Output Matches DaVinci
For every vBRS configuration in the reference matrix, the file bodies the system generates SHALL be byte-identical to the DaVinci Configurator MSR vBRS generator's output for the same inputs, after the leading file-header comment block is removed and line endings are normalised. The matrix SHALL contain the sample and at least one case for every branch of the generator's templates. The generated files SHALL carry the tool's own file header, not Vector's copyright and licence text.

#### Scenario: A switch changed
- **WHEN** `vBRSEnableMultiCoreSupport` is false in a matrix case
- **THEN** the generated `vBrsCfg.h` body equals the DaVinci body for that case

#### Scenario: Own header
- **WHEN** `vBrsCfg.h` is generated
- **THEN** its header does not contain Vector's copyright or licence text

### Requirement: vBRS Generation Refused On Missing Input
The system SHALL refuse to generate the vBRS files, write none of them, and name the missing input when multi-core support is on but the Os has no core mapping, when a mapped core has no start-up stack region, or when the chip data lacks the core type, the derivative id or the maximum frequency. It SHALL NOT substitute default values for these inputs.

#### Scenario: Missing stack region
- **WHEN** core 1 is mapped in the Os but the memory layout has no `STACK_C1`
- **THEN** generation is refused and the reason names `STACK_C1`

#### Scenario: Missing core type
- **WHEN** the chip data has no core type
- **THEN** generation is refused and the reason names the core type

### Requirement: ADS Link Check Of The Generated BRS Configuration
A link check tool SHALL compile copies of the Vector static BrsMain/BrsHw sources together with the generated vBRS and init-table files and Os/EcuM stubs using ADS, and link them with the generated scatter file. It SHALL NOT modify the original static sources. Tests using it SHALL be skipped when the ADS paths are not configured.

#### Scenario: ADS not configured
- **WHEN** the ADS environment variables are not set
- **THEN** the link check tests are skipped

### Requirement: Link Check Findings From The Map
The link check tool SHALL report from the link map whether every label resolves, whether every init-table entry equals its region's bounds and load address, and whether every start-up stack end equals the limit of its `STACK_C<n>` region.

#### Scenario: THA6206 sample layout
- **WHEN** the tool runs on the THA6206 layout with ADS configured
- **THEN** it reports every label resolved and every table entry matching its region
