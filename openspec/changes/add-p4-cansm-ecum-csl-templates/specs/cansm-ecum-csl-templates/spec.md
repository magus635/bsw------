# CanSM and EcuM MICROSAR CSL Templates Capability

## ADDED Requirements

### Requirement: Repository Template Pack Override in Template Audit
`audit_project_templates()` and `tools/audit_templates.py` SHALL accept an optional `template_pack_dir` / `--template-pack` directory override so repository-resident templates under `template_packs/davinci/` can cleanly replace stale project overlays during non-destructive `.dpa` audits.

#### Scenario: Auditing with `--template-pack` supersedes stale project overlay files
- **WHEN** `audit_project_templates(dpa_path, template_pack_dir=pack_dir)` runs for a module whose directory exists inside `pack_dir`
- **THEN** `CodeGenerator` renders exclusively from `pack_dir/<ModuleOrPackageDir>` without invoking obsolete project overlay templates or writing to the source `.dpa` directory

### Requirement: CanSM MICROSAR CSL Header and Lcfg Generation
`template_packs/davinci/CanSM` SHALL generate `CanSM_Cfg.h` and `CanSM_Lcfg.c` with full Vector MICROSAR ComStackLib (`CSL`) macros, timing conversions in main-function ticks, PCDataSwitches, `ISDEF`/`EQ2` constants, single-channel optimization vs multi-channel `CanSM_ChannelConfig[]` arrays, typedefs, and `CanSM_ChannelVarRecord[]` definitions.

#### Scenario: Rendering CanSM CSL outputs from single-channel and multi-channel ECUC configs
- **WHEN** `CodeGenerator.generate_all()` renders `template_packs/davinci/CanSM` on single-channel or multi-channel `CanSM` configurations
- **THEN** `CanSM_Cfg.h` and `CanSM_Lcfg.c` contain zero unexpanded `[!` tags, compile cleanly under `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`, and match >=95% of `StartApplication` `#define`s and 100% of `CONST/VAR` symbols

### Requirement: EcuM MICROSAR CSL Header and Source Generation
`template_packs/davinci/EcuM` SHALL generate all nine Vector MICROSAR headers and sources (`EcuM_Cfg.h`, `EcuM_PrivateCfg.h`, `EcuM_Generated_Types.h`, `EcuM_Init_Cfg.h/.c`, `EcuM_Init_PBcfg.h/.c`, `EcuM_Cfg.c`, and `EcuM_PBcfg.c`) with ID-ordered wakeup source constants/bitmasks, OS application partition status arrays, `EcuM_DriverInitOne`, and ComM channel reference indices.

#### Scenario: Rendering EcuM CSL outputs from multi-partition ECUC configs
- **WHEN** `CodeGenerator.generate_all()` renders `template_packs/davinci/EcuM` on `EcuM` configurations with wakeup sources and OS partitions
- **THEN** all nine files emit with exact filenames (including `EcuM_PrivateCfg.h` and `EcuM_Generated_Types.h`), zero unexpanded `[!` tags, clean `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror` checks, >=95% `#define` parity, and 100% `CONST/VAR` symbol parity against `StartApplication` reference `GenData`
