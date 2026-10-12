## ADDED Requirements

### Requirement: ARTI Shows Resource And Spinlock Owners
The generated `Os_Arti.arxml` SHALL describe the owner of every resource and spinlock with the `RESOURCE_OWNER` / `SPINLOCK_OWNER` expression `Os_<name>_RunningData.OwnerObjectID` and a type map from the kernel object ID to the owner name, using the same object numbering as the ORTI `RESOURCE_OWNER` / `SPINLOCK_OWNER` enumeration.

#### Scenario: Owner names match the ORTI enumeration
- **WHEN** ORTI and ARTI are generated from the same Os configuration
- **THEN** every `Task <name>` and `ISR <name>` entry of the ORTI owner enumeration appears in the ARTI owner type map with the same numeric value

#### Scenario: No owner
- **WHEN** a resource or spinlock is not held
- **THEN** its owner value 0xFFFFFFFF is mapped to `-`, as in ORTI

### Requirement: Single Object Numbering Rule
The object numbering used by the ARTI owner type maps SHALL be derived by the same macros as the ORTI template, so that the ORTI and ARTI numbering cannot diverge.

#### Scenario: Applications with hooks, IOC callbacks, counters and alarms
- **WHEN** an application contains hooks, IOC receive callbacks, counters, alarms and schedule tables
- **THEN** the object numbers of the following application start after all of them, identically in ORTI and ARTI
