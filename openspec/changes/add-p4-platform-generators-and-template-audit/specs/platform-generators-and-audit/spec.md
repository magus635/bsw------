# Platform Generators & Template Audit Capability

## ADDED Requirements

### Requirement: RTE Companion Headers and Per-SWC MemMap Wrappers
`RteSchMGenerator` SHALL generate `Rte_Compiler_Cfg.h`, `Rte_Hook.h`, and `Components/<Swc>_MemMap.h` when `include_phase2_3=True` (while preserving Phase-1 `include_phase2_3=False` output stability), defining SWC memory-class macros (`<Swc>_CODE`, `<Swc>_CONST`, `<Swc>_VAR_*`, `RTE_<SWC>_APPL_*`) and mapping SWC RAM sections to OS application `MemMap.h` sections when an owning `OsApplication` is present.

#### Scenario: Generating RTE Phase 2/3 outputs emits companion headers and SWC MemMap files
- **WHEN** `RteSchMGenerator(project, include_phase2_3=True).generate(out_dir)` runs on a project with configured SWC components
- **THEN** `Rte_Compiler_Cfg.h`, `Rte_Hook.h`, and `Components/<Swc>_MemMap.h` are generated alongside `Rte.h`, `Rte.c`, and `Components/Rte_<Swc>.h`

### Requirement: EcuC ComStack_Cfg.h Generation
`render_comstack_cfg_h()` and `generate_platform_artifacts()` SHALL read `EcuC/EcucPduCollection` (`PduIdTypeEnum` and `PduLengthTypeEnum`) and emit `ComStack_Cfg.h` defining `PduIdType` and `PduLengthType`.

#### Scenario: Deriving PduIdType and PduLengthType from EcuC
- **WHEN** `EcuC/EcucPduCollection` sets `PduIdTypeEnum=UINT8` and `PduLengthTypeEnum=UINT16`
- **THEN** `render_comstack_cfg_h(project)` emits `typedef uint8 PduIdType;` and `typedef uint16 PduLengthType;` inside `#if !defined (COMSTACK_CFG_H)`

### Requirement: Batch Module MemMap Header Generation with LlvmHighTec Pragmas
`render_module_memmap_h()` and `generate_platform_artifacts()` SHALL generate `<Mod>_MemMap.h` headers for loaded BSW/MCAL/CDD modules and `Rte`, enforcing `MEMMAP_ERROR` and nested-section guards (`MEMMAP_SECTION_OPEN`) and emitting `# pragma clang section` directives when targeting `LlvmHighTec`.

#### Scenario: Compiling C code with generated LlvmHighTec <Mod>_MemMap.h
- **WHEN** a C translation unit opens and closes `<MOD>_START_SEC_CODE`, `<MOD>_START_SEC_CONST_16`, and `<MOD>_START_SEC_VAR_NOINIT_UNSPECIFIED` with `LlvmHighTec` `#pragma clang section` output
- **THEN** `clang -fsyntax-only -Wall -Wextra -Werror` compiles the translation unit with zero errors and clears `MEMMAP_ERROR`

### Requirement: vBRS Headers and LlvmHighTec Makefile.config.generated Generation
`render_vbrs_files()` SHALL aggregate `vBRS`, `vBaseEnv`, and `Os` configurations to emit `vBrsCfg.h`, `vBrs_Lcfg.h`, `vBrs_Lcfg.c`, and `Makefile.config.generated` converting Hz clock frequencies into MHz constants and sizing `BrsMain_CoreConfig` to match active OS cores.

#### Scenario: Generating vBRS configuration and Makefile snippet for dual-core THA6206
- **WHEN** `vBRS` (`vBRSTimebaseClock=400000000`, `vBRSOscClock=25000000`, `vBRSEnableMultiCoreSupport=True`), `vBaseEnv` (`Tongxin_THA6206`, `CORTEX_R52`, `2` cores), and dual-core `Os` are loaded
- **THEN** `vBrsCfg.h` defines `BRS_TIMEBASE_CLOCK 400`, `BRS_OSC_CLK 25`, `BRS_CPU_CORE_CORTEX_R52`, `BRS_DERIVATIVE_Tongxin_THA6206`, `BRS_CPU_CORE_AMOUNT 2`, and `Makefile.config.generated` sets `BRS_CPU_CORE_0_USED = 1` and `BRS_CPU_CORE_1_USED = 1`

### Requirement: Non-Destructive Template Audit Service and CLI
`audit_project_templates()` and `tools/audit_templates.py` SHALL load a `.dpa` project read-only, dry-run per-module `CodeGenerator` (using `project_paths.package_dir_name` so variant modules such as `CanTrcv_Tle9255` resolve accurately), `RteSchMGenerator`, and `generate_platform_artifacts()`, report unexpanded `[!` tags, measure `#define`/symbol parity against reference `GenData`, and optionally execute `clang -fsyntax-only` over generated `.c` files.

#### Scenario: Auditing StartApplication1.dpa routes CanTrcv_Tle9255 and reports full parity metrics
- **WHEN** `audit_project_templates()` runs on `StartApplication1.dpa` with reference `GenData`
- **THEN** `CanTrcv` resolves via `CanTrcv_Tle9255` with status `OK`, zero modules report `ERROR` or unexpanded `[!` tags, and JSON/Markdown parity summaries are produced without modifying the source project
