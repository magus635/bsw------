## ADDED Requirements

### Requirement: Generated Hook Wrapper Header
The Os generator SHALL produce `Os_ArtiHooks.h` from the same event list as the `ArtiHook` containers, defining one private wrapper macro per class that expands to `ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter)` in the SWS_Arti_00018 parameter order with literal tokens, and that expands to `((void)0)` when `OsUseArti` or the class switch is off.

#### Scenario: Tokens match the description
- **WHEN** `Os_Arti.arxml` and `Os_ArtiHooks.h` are generated from the same configuration
- **THEN** the set of (context, class, instance, event) tokens in the header equals the set described by the `ArtiHook` containers

#### Scenario: Application-specific hooks
- **WHEN** an OS-Application has its own ErrorHook, StartupHook or ShutdownHook
- **THEN** the header dispatches on the application ID to a literal event token containing that application's hook name

### Requirement: Zero Overhead When Disabled
With `OsUseArti` off, the kernel SHALL compile to the same object code as without this change; hook calls, the variables prepared only for hooks and the ARTI shadow-state fields SHALL all be removed by the preprocessor.

#### Scenario: Object code unchanged
- **WHEN** the kernel is compiled with `OsUseArti` false before and after the change, with the same toolchain and options
- **THEN** the `.text`, `.data` and `.bss` contents of every object file are identical

### Requirement: Kernel Task And ISR Events
The kernel SHALL emit the task and Cat2 ISR events of the selected state model at the atomic moment of each state transition, on the core that executes the transition, selecting the dispatch event from a per-object ARTI shadow state rather than from the kernel task state.

#### Scenario: ISR interrupts a task without rescheduling
- **WHEN** a Cat2 ISR interrupts a running task and returns to the same task
- **THEN** the trace on that core shows `OsCat2Isr_Start` and `OsCat2Isr_Stop` and no task event

#### Scenario: ISR exit causes preemption
- **WHEN** a Cat2 ISR activates a higher-priority task and returns
- **THEN** the order on that core is `OsCat2Isr_Stop`, `OsTask_Preempt` of the interrupted task, then `OsTask_Start` of the activated task

#### Scenario: Wait and release in the enhanced model
- **WHEN** a task waits for an event that another task sets later
- **THEN** the task emits `OsTask_Wait`, then `OsTask_Release`, then `OsTask_Continue` when dispatched again, and never goes from Waiting to Running directly

#### Scenario: Cross-core activation
- **WHEN** a task on core 0 activates a task assigned to core 1
- **THEN** `OsTask_Activate` is emitted on core 1 with instanceParameter equal to core 1's OS core index

### Requirement: Spinlock, Application, Hook And Service Call Events
The kernel SHALL emit `OsSpinlock_Locked` / `OsSpinlock_Released` when a spinlock actually changes owner, `OsApplication_*` when an OS-Application changes state, `OsHook_<name>_Start` / `_Return` around every OS hook function, and `OsServiceCall_<API>_Start` / `_Return` on entry and exit of every OS service called from application context, each with the event parameter defined in SWS OS R21-11 §7.17.

#### Scenario: Spinlock requested but busy
- **WHEN** a task calls `GetSpinlock` while another core holds the lock
- **THEN** `OsSpinlock_Locked` is emitted only once the lock is obtained

#### Scenario: Service call from OS context
- **WHEN** the kernel terminates a task internally after a missing `TerminateTask`
- **THEN** no `OsServiceCall_TerminateTask_*` event is emitted

#### Scenario: ProtectionHook return
- **WHEN** the ProtectionHook returns
- **THEN** `OsHook_ProtectionHook_Return` is emitted after the OS has evaluated the return value, with the action actually taken as event parameter

### Requirement: Mock And Event Stream Check
The generator SHALL produce `Os_Arti_Mock.h` that concatenates all four literal tokens and defines only the combinations listed in the `ArtiHook` containers, recording events per core; a checker SHALL validate a recorded event stream against the transition table of the selected model.

#### Scenario: Wrong token fails the build
- **WHEN** a kernel call site uses an event token or parameter order not listed in the `ArtiHook` description
- **THEN** compiling the kernel against `Os_Arti_Mock.h` fails

#### Scenario: Illegal transition detected
- **WHEN** the recorded stream contains `OsTask_Resume` for a task in state Released
- **THEN** the checker reports the event as an illegal transition

### Requirement: Static Debugging Without A Trace Tool
With `OsUseArti` on and every `OsVendorArtiTrace<Class>` off, the generated headers SHALL NOT require the trace tool's `Os_Arti.h`, and the kernel SHALL compile to the same object code as with all trace classes absent.

#### Scenario: Only stop-mode debugging
- **WHEN** `OsUseArti` is true and all six trace classes are false
- **THEN** `Os_ArtiHooks.h` does not include `Os_Arti.h`, no `ArtiHook` is described, and the kernel object code equals that of the unmodified kernel with `OsUseArti` true
