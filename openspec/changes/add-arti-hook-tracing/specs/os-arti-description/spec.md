## ADDED Requirements

### Requirement: ARTI Hook Descriptions
The generated `Os_Arti.arxml` SHALL contain one `ArtiHook` container for every enabled (class, event) combination of SWS OS R21-11 §7.17, with `ArtiHookContext`, `ArtiHookClass`, `ArtiHookInstance` and `ArtiHookEventName` equal to the literal tokens used by the kernel, `ArtiHookInstanceParameterTypeRef` referring to a type map from the OS core index to the core name, and `ArtiHookEventParameterTypeRef` referring to the type map of the event parameter where one exists. The `ArtiOsInstance` SHALL reference every generated hook through `ArtiOsInstanceHookRef`.

#### Scenario: Enhanced task model
- **WHEN** `OsUseArti` is true and `OsVendorArtiStateModel` is `ENHANCED`
- **THEN** the task hooks use class `AR_CP_OSARTI_TASK` with the events `OsTask_Activate`, `OsTask_Start`, `OsTask_Preempt`, `OsTask_Resume`, `OsTask_Wait`, `OsTask_Release`, `OsTask_Continue`, `OsTask_Terminate`
- **AND** `ArtiStatesTaskEnhanced` is true

#### Scenario: Standard task model
- **WHEN** `OsVendorArtiStateModel` is `STANDARD`
- **THEN** the task hooks use class `AR_CP_OS_TASK` without `OsTask_Resume` and `OsTask_Continue`, the Cat2 hooks use `AR_CP_OS_CAT2ISR` with `OsCat2Isr_Start` and `OsCat2Isr_Stop` only
- **AND** `ArtiStatesTaskEnhanced` is false

#### Scenario: Class disabled
- **WHEN** a class switch `OsVendorArtiTrace<Class>` is false
- **THEN** no `ArtiHook` of that class is generated

#### Scenario: ARTI disabled
- **WHEN** `OsUseArti` is false
- **THEN** no `ArtiHook` is generated

### Requirement: Hook Type Maps Within 16 Bits
Every `ArtiParameterTypeMap` referenced by an `ArtiHook` SHALL have all `ArtiParameterTypeMapPairInput` values within 0..65535 (ECUC_Arti_00024), and object IDs in these maps SHALL equal the IDs the kernel passes as event parameter (`TaskType`, `ISRType`, `ApplicationType`, `SpinlockIdType`).

#### Scenario: Task IDs in a hook type map
- **WHEN** the task hooks reference `TM_TaskId`
- **THEN** every pair input equals the `TaskType` value generated for that task and is at most 65535
