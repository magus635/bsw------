# Change: Add P4-2 Batch 2 MICROSAR CSL EB Templates (`ComM` + `CanIf`)

## Why

After achieving 100% `#define` and `CONST/VAR` symbol parity on `CanSM` (`195/195`) and `EcuM` (`314/314`), the next core communication infrastructure blockers in `StartApplication1.dpa` are:
- `CanIf`: currently `68/673` `#define`s matched; missing CSL switch tables (`CanIf_MailBoxConfig`, `CanIf_RxPduConfig`, `CanIf_TxPduConfig`, `CanIf_TxBufferPrioByCanIdConfig`), PDU symbolic handles, indication/confirmation function pointer tables, and `CanIf_Lcfg.c` definitions.
- `ComM`: currently `23/1089` `#define`s matched; missing CSL partition/channel/user switches, `ComM_Private_Cfg.h` accessors, `ComM_ActiveComMode` / `ComM_BusComModeReq` / `ComM_BusSmState` / `ComM_ComAllowed` / `ComM_DcmRequestActive` unions, and `ComM_Lcfg.c` / `ComM_Lcfg.h` / `ComM_GenTypes.h` definitions.

## What Changes

- **`CanIf` CSL EB Template Pack (`template_packs/davinci/CanIf/`)**:
  - Author `include/CanIf_Can.h`, `include/CanIf_CanTrcv.h`, `include/CanIf_Cfg.h`, `src/CanIf_Lcfg.c`, and `src/CanIf_PBcfg.c` generating MICROSAR `CanIf` CSL switches, symbolic PDU/controller/transceiver handles, upper-layer callback dispatch lists, priority-by-CAN-ID Tx buffers, mailbox/Rx/Tx PDU tables, and union RAM state structures.
- **`ComM` CSL EB Template Pack (`template_packs/davinci/ComM/`)**:
  - Author `include/ComM_GenTypes.h`, `include/ComM_Lcfg.h`, `include/ComM_Cfg.h`, `include/ComM_Private_Cfg.h`, and `src/ComM_Lcfg.c` generating MICROSAR `ComM` CSL switches, symbolic user/channel IDs, channel/user/partition structures, inhibition defaults, and `ComM_MainFunction_<Ch>` dispatchers.

## Impact

- Affected specs: `comm-canif-csl-templates` (new capability)
- Affected code:
  - `template_packs/davinci/CanIf/{include/*.h,src/*.c}`
  - `template_packs/davinci/ComM/{include/*.h,src/*.c}`
  - `tests/generator/test_p4_comm_canif_templates.py`
