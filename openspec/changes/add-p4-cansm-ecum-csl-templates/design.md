# Design: P4-2 Batch 1 MICROSAR CSL EB Templates (`CanSM` + `EcuM`)

## Context

`StartApplication1.dpa` uses legacy project templates under `/Users/qlwang/Desktop/test3/StartApplication1/templates/` (strictly read-only). Inside this repository, `template_packs/davinci/` houses authoritative EB Tresos templates packaged alongside the configurator. To audit and verify repo template packs without modifying external `.dpa` projects, `template_audit.py` needs a read-only override mechanism (`template_pack_dir`).

## Goals / Non-Goals

- **Goals**:
  - Generate `CanSM_Cfg.h` and `CanSM_Lcfg.c` matching MICROSAR ComStackLib (`CSL`) macros, typedefs, single-channel `EQ2` optimization, multi-channel struct arrays, and `CanSM_MemMap.h` pragmas.
  - Generate all 9 `EcuM` files (`EcuM_Cfg.h`, `EcuM_PrivateCfg.h`, `EcuM_Generated_Types.h`, `EcuM_Init_Cfg.h/.c`, `EcuM_Init_PBcfg.h/.c`, `EcuM_Cfg.c`, `EcuM_PBcfg.c`) matching MICROSAR CSL macros, wakeup source masks ordered by `EcuMWakeupSourceId`, partition/core status arrays resolved via `OsApplication`, and `ComMChannelRefs` index ranges.
  - Achieve >=95% `#define` parity and 100% `CONST/VAR` symbol parity against `StartApplication/Appl/GenData/` while passing `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`.
- **Non-Goals**:
  - Modifying files under `/Users/qlwang/Desktop/未命名文件夹/` or `/Users/qlwang/Desktop/test3/`.
  - Refining Batch 2+ BSW modules (`ComM`, `CanIf`, `CanTp`, `PduR`, `Com`, `BswM`, `Dcm`, `Os`) in this change.

## Decisions

1. **Template Pack Replacement Semantics in `audit_project_templates()`**:
   - When `template_pack_dir` contains `<tpl_dir_name>/` or `<mod_name>/`, `audit_project_templates()` sets `overlay_root = Path(template_pack_dir)` and `pkg_tpl = None`. Clearing `pkg_tpl` ensures obsolete files from a stale package dir (such as `EcuM_Private_Cfg.h`) do not pollute generated outputs alongside the refined repo pack (`EcuM_PrivateCfg.h`).
2. **EB Template Compatibility With Both Minimal & Production ECUC Models**:
   - Every optional `node:ref(...)` lookup (such as `CanSMTransceiverId`, `CanSMControllerId`, `EcuMComMChannelRef`, `EcuMOSResource`, `EcuMDefaultAppMode`, `EcuMNormalMcuModeRef`, `OsApplication`) is guarded with `node:exists(...)` and `node:refvalid(...)` plus MICROSAR BSWMD fallbacks so minimal synthetic test configs and full production `.dpa` configs both render cleanly with zero unexpanded `[!` tags.
3. **CanSM Single-Channel Optimization vs Multi-Channel Scaling**:
   - When `count(CanSMManagerNetwork/*) <= 1`, CSL folds channel attributes into `CANSM_ISDEF_* = STD_ON` and `CANSM_EQ2_* = <literal>`, emitting `CanSM_ChannelConfigNeverUsed`. When `count > 1`, `CANSM_ISDEF_*` switches to `STD_OFF` and emits `CanSM_ChannelConfig[N]` in `CanSM_Lcfg.c` with `extern CONST(...)` in `CanSM_Cfg.h` and indexed field accessors.
4. **EcuM ID Ordering & ComM Reference Slice Computation**:
   - Wakeup sources in `EcuM.arxml` appear out of numerical order (`0, 3, 2, 1, 4, 5`). Templates iterate `wkId` from `0` to `count - 1` matching `EcuMWakeupSourceId = $wkId` (with safe fallback if IDs have gaps or are non-contiguous) so `EcuMConf_*`, `ECUM_WKSOURCE_*` bitmasks (`bit:shl(1, id)`), and `EcuM_WakeupSourceList[]` align deterministically.
