# Change: Add P4-2 Batch 3 CanTp and PduR CSL EB Template Packs

## Why
The legacy overlay templates for `CanTp` and `PduR` cover only a tiny fraction of Vector MICROSAR ComStackLib (`CSL`) generated output (`18/936` defines for `CanTp`, `16/970` defines for `PduR`, and mismatched file lists), failing real-project header/table parity against `StartApplication/Appl/GenData/` and lacking valid ARMv8-R syntax verification.

Adding complete, data-driven Vector MICROSAR CSL EB Tresos template packs for `CanTp` and `PduR` under `template_packs/davinci/` closes Batch 3 of P4-2 module generation parity.

## What Changes
- **CanTp CSL template pack** (`template_packs/davinci/CanTp/` — 5 files):
  - `include/CanTp_Cfg.h`, `include/CanTp_Lcfg.h`, `include/CanTp_PBcfg.h`
  - `src/CanTp_Lcfg.c`, `src/CanTp_PBcfg.c`
  - Generates General switches, symbolic names, CSL PC data switches, `MIN`/`MAX`/`NO`/`EXISTS`/`SIZE` macros, `ISDEF` flags, pointer/getter/setter macros, partition/channel/RxSdu/TxSdu/RxPduMap structures, and tick-converted timing parameters.
- **PduR CSL template pack** (`template_packs/davinci/PduR/` — 10 files):
  - `include/PduR_Types.h`, `include/PduR_Cfg.h`, `include/PduR_Lcfg.h`, `include/PduR_PBcfg.h`
  - `include/PduR_CanIf.h`, `include/PduR_CanTp.h`, `include/PduR_Com.h`, `include/PduR_Dcm.h`
  - `src/PduR_Lcfg.c`, `src/PduR_PBcfg.c`
  - Generates BSW module dispatch descriptors (`PduR_MmRom`), global/destination/source routing tables (`PduR_RmGDestRom`, `PduR_RmDestRom`, `PduR_RmSrcRom`, `PduR_RxTp2Src`), exclusive area tables, `ISDEF` & `GET` getter/accessor CSL macros, wrapper dispatch functions, and IF/TP symbolic names.
- **Verification suite** (`tests/generator/test_p4_cantp_pdur_templates.py`):
  - Synthetic generation + `clang --target=armv8r-none-eabi -fsyntax-only -Wall -Wextra -Werror` compilation checks for both `CanTp` and `PduR`.
  - Read-only `StartApplication1.dpa` parity audit asserting file parity, `>=95%` `#define` parity, `100%` `CONST/VAR` symbol parity, and zero unexpanded EB tags.

## Impact
- Affected template packs: `template_packs/davinci/CanTp/**`, `template_packs/davinci/PduR/**`
- New tests: `tests/generator/test_p4_cantp_pdur_templates.py`
- Non-breaking to existing Batch 1 (`CanSM`, `EcuM`), Batch 2 (`CanIf`, `ComM`), and P4-1 platform/audit tests.
