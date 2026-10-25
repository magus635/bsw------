## ADDED Requirements

### Requirement: One Kernel Source For Cortex-R52 And SC300
The Os kernel SHALL build for the SC300 (Arm Cortex-M3) from the same source as for the Cortex-R52 chips, selected by the compile macro `__OS_SUPPORT_CORTEX_M3__`; without that macro the Cortex-R52 build SHALL be unchanged.

#### Scenario: Cortex-R52 objects unchanged
- **WHEN** the kernel and the THA6206 generated configuration are compiled for Cortex-R52 before and after the change with the same compiler and options
- **THEN** every object file is byte-identical

#### Scenario: SC300 build
- **WHEN** the kernel and the code generated for an Os-only SC300 project are compiled with `__OS_SUPPORT_CORTEX_M3__` for Cortex-M3
- **THEN** they compile and link without errors

### Requirement: Cortex-M3 Context And Interrupt Model
On the SC300 the kernel SHALL mask interrupts with `BASEPRI` (3 priority bits, `priority << 5`), switch privilege with `svc`, run interrupts that preempt thread mode through `OsIsr_InterruptHandler` in thread mode as the HSM port does, and perform task switches synchronously through `Os_Hal_ContextSwitch_Asm`, so that the kernel's common code is the same for both architectures.

#### Scenario: Task switch at the end of an ISR
- **WHEN** a Cat2 ISR that interrupted a task activates a higher-priority task
- **THEN** the higher-priority task runs after the ISR ends, and the interrupted task later resumes with its registers, `BASEPRI` and `CONTROL` restored

#### Scenario: Nested interrupt
- **WHEN** a higher-priority Cat2 ISR interrupts a running Cat2 ISR
- **THEN** it is handled in handler mode and both ISRs complete in priority order

#### Scenario: System tick
- **WHEN** an alarm is driven by a hardware counter on SysTick (exception 15)
- **THEN** the alarm expires after the configured number of ticks

### Requirement: SC300 Configuration Limits
When `OsResourceSubderivative` is `Os_SC300`, the Os definition SHALL report as invalid a scalability class other than SC1, an `OsIsrPriority` outside 1–7, a hardware counter that is high-resolution or not on SysTick (source 15), and `OsNumberOfCores` other than 1, without changing any value and without affecting the other chips.

#### Scenario: Priority out of range
- **WHEN** an SC300 project has an ISR with `OsIsrPriority` 12
- **THEN** the limit on ISR priorities is reported and the value stays 12

#### Scenario: Counter on the R52 generic timer
- **WHEN** an SC300 project has a hardware counter whose ISR uses interrupt source 30
- **THEN** the counter limit is reported

#### Scenario: Other chips
- **WHEN** a THA6206 project uses SC3, two cores, ISR priority 0 and a high-resolution counter on interrupt source 30
- **THEN** none of the SC300 limits is reported

### Requirement: Os Sections Without A Memory Layout On SC300
For `Os_SC300`, which has no memory layout configuration, the generated `Os_memmap.h` SHALL accept every Os section symbol and leave the sections in the default sections, so that the kernel compiles and the project's linker script places them; the output for the other chips SHALL be unchanged.

#### Scenario: SC300 memory map
- **WHEN** Os code is generated for an SC300 project
- **THEN** the kernel and the generated configuration compile without the "no valid memory mapping symbol" error
