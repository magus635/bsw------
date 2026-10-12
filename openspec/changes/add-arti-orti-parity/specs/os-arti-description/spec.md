## ADDED Requirements

### Requirement: ARTI Description Covers All ORTI Objects And Attributes
The generated `Os_Arti.arxml` SHALL contain a counterpart for every object type and attribute of the reference ORTI description (`Os_Trace_Core0.ORTI`), using ARTI generic components where the ARTI definition has no dedicated container, except for attributes listed in the documented exception list.

#### Scenario: Task extension attributes present
- **WHEN** the Os configuration contains OsTask containers and `OsUseArti` is enabled
- **THEN** each task has a generic component instance providing `OSTASKTYPE`, `OSTASKSCHEDULE`, `OSTASKMAXACTIVATION`, `REMAININGACTIVATIONS`, `EVENTMASK`, `EVENTSETFLAG` and `LOCKED`

#### Scenario: Event, ScheduleTable, Spinlock and OS_CONFIG described
- **WHEN** the Os configuration contains OsEvent, OsScheduleTable and OsSpinlock containers
- **THEN** the output contains a generic component instance for each of them, and one OS-level instance carrying `ScalabilityClass`, `StatusLevel` and `OsStackMonitoring`

### Requirement: ARTI Expressions Match ORTI Expressions
For every ORTI attribute that has a counterpart in the ARTI output, the `ArtiExpressionString` or `ArtiConstantString` SHALL equal the ORTI attribute value, and enumerated values SHALL map to the same names as the ORTI ENUM.

#### Scenario: Same kernel symbol
- **WHEN** the ORTI attribute `STATE` of task `Task_A` is `Task_A_RunningData.State`
- **THEN** the ARTI expression for the same task state is `Task_A_RunningData.State`

#### Scenario: Same enumeration
- **WHEN** the ORTI `ACTION` enumeration maps 0 to `ALARM_ACTIVATETASK` and 3 to `ALARM_INCREMENTCOUNTER`
- **THEN** the ARTI type map for the alarm action contains the same pairs

### Requirement: ORTI Parity Report With Explicit Exceptions
The test suite SHALL compare the rendered ARTI against the reference ORTI and report every missing object or attribute, and SHALL fail on any gap that is not on the documented exception list.

#### Scenario: Gap outside the exception list
- **WHEN** an ORTI attribute has no ARTI counterpart and is not on the exception list
- **THEN** the parity test fails and names the object kind and attribute

#### Scenario: Deferred owner attributes
- **WHEN** the parity test runs
- **THEN** `RESOURCE_OWNER` and `SPINLOCK_OWNER` appear on the exception list with a reference to the follow-up change

### Requirement: Generic Component Output Is Definition Valid
All generic component classes, instances and parameters SHALL satisfy the `Arti_ParamDef.arxml` definition (multiplicities, reference targets) and resolve when loaded in the configurator workspace.

#### Scenario: Validation of extended output
- **WHEN** the extended output is validated against `AUTOSAR_00047.xsd` and `Arti_ParamDef.arxml`
- **THEN** validation passes and every `VALUE-REF` resolves to an existing container
