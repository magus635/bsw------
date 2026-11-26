## ADDED Requirements

### Requirement: Model-Driven BSW Scheduler Header Generation
The generator SHALL synthesize `SchM_<ApiName>.h` and `SchM_<ApiName>_Type.h` from loaded `Rte` ECUC `RteBswModuleInstance` configurations, `system/**/*_ib_bswmd.arxml` InternalBehavior models, and `BSW-IMPLEMENTATION` package metadata.

#### Scenario: Vendor API infix and schedulable entity derivation
- **WHEN** an active loaded BSW module defines `vendor_id` and `vendor_api_infix` (e.g., `CanTrcv`, `30`, `Tle9255`) and declares `BSW-SCHEDULABLE-ENTITY` entries referencing `BSW-MODULE-ENTRY` items
- **THEN** the generator emits `SchM_<Module>_<VendorId>_<Infix>.h` and `_Type.h` declaring only implemented `BSW-SCHEDULABLE-ENTITY` prototypes wrapped in `MemMap` sections while excluding unimplemented virtual entries

#### Scenario: Exclusive area implementation mechanisms
- **WHEN** a `RteBswExclusiveAreaImpl` specifies `ALL_INTERRUPT_BLOCKING`, `OS_INTERRUPT_BLOCKING`, `OS_RESOURCE`, `OS_SPINLOCK`, `COOPERATIVE_RUNNABLE_PLACEMENT`/`NONE`, or `CUSTOM`/`RteExclusiveAreaGenerateFunction=true`
- **THEN** the generator emits the matching `SchM_Enter_<ApiName>_<EA>` and `SchM_Exit_<ApiName>_<EA>` interrupt/resource/spinlock/noop macros or `FUNC(void, RTE_CODE)` declarations
- **AND** includes `"Os.h"` only when OS interrupt or resource/spinlock primitives are used
- **AND** reports an error without emitting invalid code if `OS_RESOURCE` or `OS_SPINLOCK` lacks its required reference

#### Scenario: Three-tier MemMap header resolution and unloaded module skipping
- **WHEN** generating `SchM_<ApiName>.h` for modules with and without module-specific `MemMap` artifacts or for an `RteBswModuleInstance` targeting an unloaded module
- **THEN** modules with explicit `MEMMAP` artifacts, `MEMORY-SECTIONS`, `MemMap` config entries, or `AR >= 4.03.00` use `<ApiName>_MemMap.h`, and legacy modules fall back to `MemMap.h`
- **AND** unloaded target modules are skipped with an explicit entry in `skipped_modules` and warnings

### Requirement: Core RTE Header Synthesis
The generator SHALL synthesize core RTE headers (`Rte.h`, `Rte_Main.h`, `Rte_Cfg.h`, `Rte_Cbk.h`) and non-destructive compile stubs (`Rte_UserTypes.h`, `Rte_Type.h`).

#### Scenario: Version macros and multi-core lifecycle declarations
- **WHEN** `Rte` implementation metadata provides `sw_version`, `vendor_id`, and `ar_release_version`, `RteEnableMultiCore` is enabled across multiple `OsCore` containers, and `RteDisableRteInitMemory` is false
- **THEN** `Rte.h` reflects the extracted hex version/vendor macros alongside standard `RTE_E_*`, `SCHM_E_*`, Service ID, and Det definitions
- **AND** `Rte_Main.h` declares `SchM_StartTimingCore<N>` for each core and `Rte_InitMemory_<OsApplication>` for each configured `OsApplication`

#### Scenario: Vector-compatible minimal Rte_Cfg.h and non-destructive stubs
- **WHEN** core headers are generated and `Rte_UserTypes.h` or `Rte_Type.h` already exists on disk
- **THEN** `Rte_Cfg.h` contains only the include guard and `# include "Std_Types.h"` without bare undefined enum macros
- **AND** existing `Rte_UserTypes.h` and `Rte_Type.h` files on disk are preserved unchanged

### Requirement: Output Layout and Project Overlay Precedence
The RTE/SchM generator SHALL honor project `gen_layout` output paths, skip rewriting identical content cleanly, and allow project `templates/Rte/` overlays to override matching generated files in `GenerationController`.

#### Scenario: Per-module vs flat output and overlay override
- **WHEN** generating for `Rte` in `per-module` or `flat` layout with custom templates present under `{project}/templates/Rte/`
- **THEN** headers are written to `Rte/include/` in `per-module` mode or `include/` in `flat` mode
- **AND** matching files from `{project}/templates/Rte/` override the synthesized headers after model-driven generation completes
