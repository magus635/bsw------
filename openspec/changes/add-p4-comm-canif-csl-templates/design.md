# Design: P4-2 Batch 2 MICROSAR CSL EB Templates (`ComM` + `CanIf`)

## Context

Both `ComM` and `CanIf` are pre-compile CSL-driven MICROSAR modules in `StartApplication1.dpa` whose headers (`ComM_Cfg.h`, `ComM_Private_Cfg.h`, `CanIf_Cfg.h`) expose exact `CONST`/`VAR` union structures (`ComM_ActiveComModeUType`, `CanIf_CtrlStatesUType`, `CanIf_TxQueueUType`, etc.) and whose `*_Lcfg.c` files bind cross-module callbacks and upper-layer PDU handles (`CanSM`, `CanTp`, `PduR`, `CanTrcv_30_Tle9255`).

## Goals / Non-Goals

- **Goals**:
  - Emit all 5 `CanIf` generated files (`CanIf_Can.h`, `CanIf_CanTrcv.h`, `CanIf_Cfg.h`, `CanIf_Lcfg.c`, `CanIf_PBcfg.c`) with dynamic sizing over HTH/HRH, controllers, transceivers, Tx buffers, and Tx/Rx PDUs, resolving `CanTpConf_*` / `PduRConf_*` when sibling modules exist and falling back cleanly otherwise.
  - Emit all 5 `ComM` generated files (`ComM_GenTypes.h`, `ComM_Lcfg.h`, `ComM_Cfg.h`, `ComM_Private_Cfg.h`, `ComM_Lcfg.c`) with dynamic multi-channel/multi-user struct generation, CSL switches, `ComM_Private_Cfg.h` accessors, and `ComM_MainFunction_<id>` definitions.
  - Achieve >=95% `#define` parity and 100% `CONST/VAR` symbol parity against `StartApplication/Appl/GenData/` and clean `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror` checks.
- **Non-Goals**:
  - Modifying `/Users/qlwang/Desktop/未命名文件夹/` or `/Users/qlwang/Desktop/test3/`.
  - Refining `Com`, `PduR`, `CanTp`, `BswM`, `Dcm`, or `Os` in this change.

## Decisions

1. **CanIf Cross-Module Upper-Layer PDU Resolution**:
   - `CanIf_RxPduConfig` and `CanIf_TxPduConfig` resolve upper-layer PDU symbolic names (`CanTpConf_*` / `PduRConf_*`) by matching `CanIfRxPduRef`/`CanIfTxPduRef` against `as:modconf('CanTp')[1]` and `as:modconf('PduR')[1]` container references, falling back to `<idx>u` in standalone module generation tests where `CanTp`/`PduR` are absent.
2. **CanIf Uppercase Hex ID Formatting**:
   - Combine `text:toupper(num:inttohex(..., 4))` for `CanIdOfTxPduConfig` and `RxPduCanIdOfRxPduConfig` so masks (`0x400007FFu`, `0x000007FFu`) and CAN IDs (`0x07DFu`) compile identically with MICROSAR conventions.
3. **ComM Per-Channel Struct Fields & Private Inline Accessors**:
   - `ComM_Cfg.h` generates `ComM_ActiveComModeStructSType`, `ComM_BusComModeReqStructSType`, `ComM_BusSmStateStructSType`, `ComM_ComAllowedStructSType`, and `ComM_DcmRequestActiveStructSType` dynamically over ordered `ComMConfigSet/ComMChannel/*` containers, while `ComM_Private_Cfg.h` provides all PCConfig/PCPartitionConfig `#define`s, active inline accessors, and matching `extern` declarations.
