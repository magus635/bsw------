# Change: Add P4-2 Batch 1 MICROSAR CSL EB Templates (`CanSM` + `EcuM`)

## Why

The P4-1 audit of `StartApplication1.dpa` against real `StartApplication/Appl/GenData/` established exact `#define` and `CONST/VAR` parity baselines:
- `CanSM`: only `16/195` `#define`s matched (`CanSM_Cfg.h`, `CanSM_Lcfg.c` lack Vector MICROSAR ComStackLib PCDataSwitches, `Has*`/`IsDef*`/`Eq2*` macros, ChannelConfig getters, timing tick derivations, and CSL typedefs).
- `EcuM`: only `17/177` `#define`s matched, `EcuM_Generated_Types.h` is missing, and the existing template emits `EcuM_Private_Cfg.h` instead of Vector's `EcuM_PrivateCfg.h`, lacking CSL wakeup source bitmasks, driver init tables, partition data, and per-core status arrays.

Authoring full MICROSAR CSL EB templates inside `template_packs/davinci/{CanSM,EcuM}` and enabling `--template-pack` dry-run overrides in `template_audit.py` closes Batch 1 cleanly without mutating external read-only fixtures.

## What Changes

- **Template Audit Pack Override (`autosar_configurator/generator/template_audit.py`, `tools/audit_templates.py`)**:
  - Add optional `template_pack_dir: Optional[Path] = None` to `audit_project_templates()` and `--template-pack` to `tools/audit_templates.py` so repo template packs under `template_packs/davinci/` cleanly supersede stale project overlays during dry-run audits.
- **`CanSM` CSL EB Template Pack (`template_packs/davinci/CanSM/`)**:
  - Author `include/CanSM_Cfg.h` and `src/CanSM_Lcfg.c` generating MICROSAR feature switches, timing tick conversions (`CanSMMainFunctionTimePeriod`), PCConfig / ChannelConfig CSL accessors, `CANSM_*` switches, `CANSM_ISDEF_*`, `CANSM_EQ2_*`, single-channel optimization vs multi-channel `CanSM_ChannelConfig[]` arrays, CSL typedefs, and `CanSM_ChannelVarRecord[]`.
- **`EcuM` CSL EB Template Pack (`template_packs/davinci/EcuM/`)**:
  - Author all 9 MICROSAR generated headers and sources (`include/EcuM_Cfg.h`, `include/EcuM_PrivateCfg.h`, `include/EcuM_Generated_Types.h`, `include/EcuM_Init_Cfg.h`, `include/EcuM_Init_PBcfg.h`, `src/EcuM_Cfg.c`, `src/EcuM_Init_Cfg.c`, `src/EcuM_Init_PBcfg.c`, `src/EcuM_PBcfg.c`) with ID-ordered wakeup sources/bitmasks, OS application partition arrays, `EcuM_DriverInitOne`, `EcuM_WakeupSourceList`, and CSL access macros.

## Impact

- Affected specs: `cansm-ecum-csl-templates` (new capability)
- Affected code:
  - `autosar_configurator/generator/template_audit.py`
  - `tools/audit_templates.py`
  - `template_packs/davinci/CanSM/{include/CanSM_Cfg.h,src/CanSM_Lcfg.c}`
  - `template_packs/davinci/EcuM/{include/*.h,src/*.c}`
  - `tests/generator/test_p4_cansm_ecum_templates.py`
