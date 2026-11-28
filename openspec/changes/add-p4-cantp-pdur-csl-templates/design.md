# Design: CanTp and PduR CSL EB Template Packs

## Context
Both `CanTp` and `PduR` in Vector MICROSAR SIP rely heavily on ComStackLib (`CSL`) generated macros (`PCDataSwitches`, `ISDEF`, `EXISTS`, `Get*`, `Has*`, `SizeOf*`, `Set*`, `Inc*`, `Dec*`, `Sub*`, partition accessors) and linked ROM/RAM descriptor tables separated into `*_Cfg.h`, `*_Lcfg.h`, `*_Lcfg.c`, and `*_PBcfg.{h,c}` (plus upper/lower module facade headers for `PduR`).

## Architectural Decisions
1. **Exact File Surface Parity**:
   - `CanTp` emits the exact 5 reference files (`CanTp_Cfg.h`, `CanTp_Lcfg.h`, `CanTp_PBcfg.h`, `CanTp_Lcfg.c`, `CanTp_PBcfg.c`), replacing fragmented legacy stubs.
   - `PduR` emits the exact 10 reference files (`PduR_Types.h`, `PduR_Cfg.h`, `PduR_Lcfg.h`, `PduR_PBcfg.h`, `PduR_CanIf.h`, `PduR_CanTp.h`, `PduR_Com.h`, `PduR_Dcm.h`, `PduR_Lcfg.c`, `PduR_PBcfg.c`).
2. **Dynamic ECUC Resolution with Safe Cross-Module Fallbacks**:
   - `CanTp` resolves Rx/Tx NSdu symbolic IDs and timing ticks dynamically from `CanTpConfig/*/CanTpChannel/*` (`round(val / mainPeriod) + 1` for NAr/NBr/NCr/NAs/NBs/NCs, `round(val * 1000)` for STmin), sorted deterministically, and looks up sibling `CanIf`/`PduR`/`EcuC` handles when present with deterministic fallbacks when absent.
   - `PduR` orders `PduRBswModules` deterministically (alphabetical matching `PduR_MmRom`) and iterates `PduRRoutingTables/*/PduRRoutingTable/*/PduRRoutingPath/*` to construct `PduR_RmSrcRom`, `PduR_RmDestRom`, `PduR_RmGDestRom`, `PduR_RxTp2Src`, module-specific symbolic IDs, and CSL macros.
3. **Zero Unexpanded EB Tags & C89/AUTOSAR Compatibility**:
   - All templates use valid EB builtins (`num:i`, `num:inttohex` without duplicate `0x`, `text:replace`, `text:toupper`, `node:order`, `round`, etc.) and compile cleanly under `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror`.
