## ADDED Requirements

### Requirement: OS Generator Exports ARTI Debug Description
The Os template set SHALL generate an ECUC value file `Os_Arti.arxml` for module definition `/AUTOSAR/EcucDefs/Arti`, derived from the Os configuration, covering `ArtiValues`, `ArtiOs` and `ArtiHardware` for static debugging.

#### Scenario: Tasks and ISRs described
- **WHEN** the Os configuration contains OsTask and CATEGORY_2 OsIsr containers and `OsUseArti` is enabled
- **THEN** the output contains one `ArtiOsTaskInstance` per OsTask and one `ArtiOsIsrInstance` per CATEGORY_2 OsIsr, each with an `EcucRef` to the corresponding Os container

#### Scenario: Output is schema and definition valid
- **WHEN** the generated file is validated against `AUTOSAR_00047.xsd` and loaded with `definitions/Arti/Arti_ParamDef.arxml`
- **THEN** validation passes and no unknown parameters or containers are reported

### Requirement: ARTI Object IDs Match OS Type IDs
`ArtiOsTaskInstanceId`, `ArtiOsIsrInstanceId` and the `ArtiParameterTypeMapPairInput` values of the task and ISR TypeMaps SHALL equal the `TaskType` / `ISRType` values generated in `Os_Cfg.h` and the ENUM indices of the ORTI `RUNNINGTASK` / `RUNNINGISR2` attributes.

#### Scenario: Consistent task numbering
- **WHEN** ARTI, ORTI and `Os_Cfg.h` are generated from the same Os configuration
- **THEN** every task has the same numeric ID in all three outputs

### Requirement: Per-Core Hardware Description
The generated description SHALL contain one `ArtiHardwareCoreInstance` per configured OS core, whose current-task, current-ISR and last-error expressions index the per-core kernel data with that core's index.

#### Scenario: Multi-core derivative
- **WHEN** the Os configuration has 4 cores
- **THEN** the output contains 4 `ArtiHardwareCoreInstance` containers with `ArtiHardwareCoreInstanceCoreId` 0 to 3 and expressions using indices `[0]` to `[3]`

### Requirement: ARTI Description Controlled by OsUseArti
When `OsUseArti` is disabled, the template SHALL emit a valid AUTOSAR document that contains no `Arti` module configuration.

#### Scenario: ARTI disabled
- **WHEN** `OsUseArti` is disabled
- **THEN** the output file exists, is schema valid, and contains no `ECUC-MODULE-CONFIGURATION-VALUES`

### Requirement: Template Portable Between EB tresos and Configurator
The `Os_Arti.arxml` template SHALL use only template directives and functions supported by both EB tresos and the configurator's EB template engine, and SHALL produce the same output in both for the same configuration.

#### Scenario: Rendering in the configurator
- **WHEN** the configurator renders the template with the sample Os configuration
- **THEN** rendering succeeds without template errors and without unimplemented-function warnings
